<?php
/**
 * Callback to payonline
 * */
function payonline_hcs_confirm_payment(){
  $secKeyArr = array();
  
  $uid          = (int)payonline_hcs_isset_var($_GET['pay_hcs_uid']);
  $dateTime     = (string)check_plain(payonline_hcs_isset_var($_GET['DateTime']));
  $currency     = (string)check_plain(payonline_hcs_isset_var($_GET['Currency']));
  $lcoc         = (string)check_plain(payonline_hcs_isset_var($_GET['OrderId']));
  $trans        = (int)payonline_hcs_isset_var($_GET['TransactionID'],0);
  $payProv      = (string)check_plain(payonline_hcs_isset_var($_GET['Provider']));
  $sum          = (string)check_plain(payonline_hcs_isset_var($_GET['Amount']));
  $commis       = (string)check_plain(payonline_hcs_isset_var($_GET['pay_hcs_commis']));
  $isCommis     = (int)payonline_hcs_isset_var($_GET['pay_hcs_include_commis']);
  $homeIns      = (float)payonline_hcs_isset_var($_GET['pay_hcs_home_insurance']);
  $liabIns      = (float)payonline_hcs_isset_var($_GET['pay_hcs_liability_insurance']);
  $fullIns      = (float)payonline_hcs_isset_var($_GET['pay_hcs_full_insurance']);
  $peni         = (float)payonline_hcs_isset_var($_GET['pay_hcs_peni']);
  $electric     = (float)payonline_hcs_isset_var($_GET['pay_hcs_electric_sum']);
  $gas          = (float)payonline_hcs_isset_var($_GET['pay_hcs_gas_sum']);
  $entry_phone  = (float)payonline_hcs_isset_var($_GET['pay_hcs_entry_phone_sum']);
  $lcFkey       = (string)payonline_hcs_isset_var($_GET['pay_hcs_lc_fkey']);
  $elec_pin     = (string)payonline_hcs_isset_var($_GET['pay_hcs_electric_pin']);
  $gas_pin      = (string)payonline_hcs_isset_var($_GET['pay_hcs_gas_pin']);
  
  $sumWithoutProc = $sum;
  $proc = 0;
  $commisSum = 0;
  
  if($commis > 0 and $isCommis == 0){
    $proc = (float)$commis+100;
    $sumWithoutProc = round(($sum*100)/$proc,2);
  }
  
  if((bool)variable_get('payonline_hcs_private_key', '') === false){
    watchdog('payonline-hcs-error', 'Payment false. Secret key is empty.');
    drupal_access_denied();
    drupal_exit();
  }
  
  if(empty($lcFkey)){
    watchdog('payonline-hcs-error', 'Payment false. LC_Fkey is empty.');
    drupal_access_denied();
    drupal_exit();
  }
  
  $arrHash = array(
    'DateTime' => $dateTime,
    'TransactionID' => $trans,
    'OrderId' => $lcoc,
    'Amount' => $sum,
    'Currency' => $currency,
    'PrivateSecurityKey' => variable_get('payonline_hcs_private_key', ''),
  );
  
  foreach($arrHash as $key=>$val){
    $secKeyArr[] = $key.'='.$val;
  }
  unset($key,$val);
  
  $arrHashdBlog = $arrHash;
  
  $hashMd = md5(implode('&', $secKeyArr));
  
  if(!empty($_GET) and payonline_hcs_isset_var($_GET['SecurityKey']) == $hashMd){
    try{
      $qCheck  = db_select('payonline_hcs_payments', 'pp')
      ->fields('pp', array('id'))
      ->condition('order_id', $lcoc)
      ->condition('date_adoption_payment_in_payonline', $dateTime)
      ->execute()->fetchField();
      
      $qCheck = (bool)$qCheck;
      
      if($qCheck){
        watchdog('payonline-hcs-error', 'Payment false. Payment exists in the database.');
        drupal_deliver_page(t('Payment false. Payment exists in the database.'));
        drupal_exit();
      }
      
      $sumWithoutProc = $sumWithoutProc-$homeIns-$liabIns-$fullIns-$peni-$electric-$gas-$entry_phone;
      
      $nid = db_insert('payonline_hcs_payments')
      ->fields(array(
          'uid' => $uid,
          'order_id' => trim($lcoc),
          'lc_fkey' => trim($lcFkey),
          'currency' => $currency,
          'provider' => $payProv,
          'transaction' => $trans,
          'summ' => (float)$sumWithoutProc,
          'commis' => (float)$commis,
          'include_commis' => $isCommis,
          'home_insurance' => $homeIns,
          'liability_insurance' => $liabIns,
          'full_insurance' => $fullIns,
          'peni' => $peni,
          'electric' => $electric,
          'gas' => $gas,
          'entry_phone' => $entry_phone,
          'electric_pin' => trim($elec_pin),
          'gas_pin' => trim($gas_pin),
          'merchant_id' => variable_get('payonline_hcs_mid', ''),
          'payment_adopted_status' => 1,
          'date_adoption_payment' => date('Y-m-d H:i:s'),
          'date_adoption_payment_in_payonline' => $dateTime,
          )
        )
      ->execute();
      watchdog('payonline-hcs-info', 'Payment successful. Account number for payment: '.$lcoc.'; Provider: '.$payProv.'; Summ: '. $sum.'.');
      drupal_deliver_page(t('Payment processing is completed.'));
      drupal_exit();
    }
    catch(Exception $e){
      watchdog_exception('payonline-hcs-error', $e);
      drupal_access_denied();
      drupal_exit();
    }
  }
  else{
    watchdog('payonline-hcs-error', 'Payment false. Empty Data. Account number for payment: '.$lcoc.'; Number account number: '.$lcFkey.'; Summ: '. $sum.'.');
    drupal_access_denied();
    drupal_exit();
  }
}
