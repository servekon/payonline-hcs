<?php
// $Id: payonline_hcs.user.inc,v 1.0 2013/11/02 00:35:12 servekon Exp $
/**
 * Callback to payonline
 * */
function payonline_hcs_confirm_payment(){
	$secKeyArr = array();
	
	$uid			= (int)payonline_hcs_isset_var($_GET['pay_hcs_uid']);
	$dateTime		= (string)check_plain(payonline_hcs_isset_var($_GET['DateTime']));
	$currency		= (string)check_plain(payonline_hcs_isset_var($_GET['Currency']));
	$lcoc			= (string)check_plain(payonline_hcs_isset_var($_GET['OrderId']));
	$trans			= (int)payonline_hcs_isset_var($_GET['TransactionID'],0);
	$payProv		= (string)check_plain(payonline_hcs_isset_var($_GET['Provider']));
	$summ			= (string)check_plain(payonline_hcs_isset_var($_GET['Amount']));
	$commis			= (string)check_plain(payonline_hcs_isset_var($_GET['pay_hcs_commis']));
	$homeIns		= (float)payonline_hcs_isset_var($_GET['pay_hcs_home_insurance']);
	$liabIns		= (float)payonline_hcs_isset_var($_GET['pay_hcs_liability_insurance']);
	$fullIns		= (float)payonline_hcs_isset_var($_GET['pay_hcs_full_insurance']);
	$peni			= (float)payonline_hcs_isset_var($_GET['pay_hcs_peni']);
	$lcFkey			= (string)payonline_hcs_isset_var($_GET['pay_hcs_lc_fkey']);
	
	$summWithoutProc = $summ;
	$proc = 0;
	$commisSum = 0;
	
	if($commis > 0){
		$proc = (float)$commis+100;
		$summWithoutProc = round(($summ*100)/$proc,2);
	}
	
	if((bool)AK_PAY_ONL_HCS__PRIV_SEC_KEY === false){
		watchdog('payonline-hcs-error', 'Payment false. Secret key is empty');
		drupal_access_denied();
		drupal_exit();
	}
	
	$arrHash = array(
		'DateTime' => $dateTime,
		'TransactionID' => $trans,
		'OrderId' => $lcoc,
		'Amount' => $summ,
		'Currency' => $currency,
		'PrivateSecurityKey' => AK_PAY_ONL_HCS__PRIV_SEC_KEY,
	);
	
	foreach($arrHash as $key=>$val){
		$secKeyArr[] = $key.'='.$val;
	}
	unset($key,$val);
	
	$arrHashdBlog = $arrHash;
	
	$hashMd = md5(implode('&', $secKeyArr));
	
	if(!empty($_GET) and payonline_hcs_isset_var($_GET['SecurityKey']) == $hashMd){
		try{
			$qCheck	= db_select('payonline_hcs_payments', 'pp')
			->fields('pp', array('id'))
			->condition('lcoc_key', $lcoc)
			->condition('date_adoption_payment_in_payonline', format_date(strtotime($dateTime)+date('Z'), 'custom', 'Y-m-d H:i:s', 'Europe/Moscow'))
			->execute()->fetchField();
			
			$qCheck = (bool)$qCheck;
			
			if($qCheck){
				watchdog('payonline-hcs-error', 'Payment false. Payment exists in the database.');
				drupal_access_denied();
				drupal_exit();
			}
			
			$summWithoutProc = $summWithoutProc-$homeIns-$liabIns-$fullIns-$peni;
			
			$nid = db_insert('payonline_hcs_payments')
			->fields(array(
				'uid' => $uid,
				'lcoc_key' => $lcoc,
				'lc_fkey' => $lcFkey,
				'currency' => $currency,
				'provider' => $payProv,
				'transaction' => $trans,
				'summ' => (float)$summWithoutProc,
				'commis' => (float)$commis,
				'home_insurance' => $homeIns,
				'liability_insurance' => $liabIns,
				'full_insurance' => $fullIns,
				'peni' => $peni,
				'merchant_id' => AK_PAY_ONL_HCS_MID,
				'payment_adopted_status' => 1,
				'date_adoption_payment' => date('Y-m-d H:i:s'),
				'date_adoption_payment_in_payonline' => format_date(strtotime($dateTime)+date('Z'), 'custom', 'Y-m-d H:i:s', 'Europe/Moscow'),
			  ))
			->execute();
			watchdog('payonline-hcs-info', 'Payment successful. Account number for payment: '.$lcoc.'; Provider: '.$payProv.'; Summ: '. $summ.'.');
			return 'Payment processing is completed.';
		}
		catch(Exception $e){
			watchdog_exception('payonline-hcs-error', $e);
			drupal_access_denied();
			drupal_exit();
		}
	}
	else{
		watchdog('payonline-hcs-info', 'Payment false. Empty Data. Account number for payment: '.$lcoc.'; Number account number: '.$lcFkey.'; Summ: '. $summ.'.');
		drupal_access_denied();
		drupal_exit();
	}
}
