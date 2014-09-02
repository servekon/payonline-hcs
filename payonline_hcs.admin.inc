<?php
/**
 * @file payonline_hcs.admin.inc
 * Functions that are only called on the admin pages.
 */

/**
 * Implementation of hook_admin().
 */
function payonline_hcs_admin() {
 	global $user;
    $arrFileEncode = _payonline_hcs_encodes();
 	$hcsPoArrPatt = _payonline_hcs_pack_patterns();
    $lng	= $user->language;
    
    $form['group_settings'] = array(
		'#type' => 'vertical_tabs',
	);
    
    $form['pay_hcs_main_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Basic settings'),
      '#weight' => -1,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#group' => 'group_settings',
    );
    
 	$form['pay_hcs_main_fieldset']['payonline_hcs_mid'] = array(
		'#type' => 'textfield',
		'#title' => t('Merchant ID exchange system Payonline'),
		'#default_value' => variable_get('payonline_hcs_mid', ''),
		'#attributes'	=> array('autocomplete'=>array('off')),
        '#required' => TRUE,
    );
 	
 	$form['pay_hcs_main_fieldset']['payonline_hcs_private_key'] = array(
		'#type' => 'textfield',
		'#title' => t('Secret key exchange system Payonline'),
		'#default_value' => variable_get('payonline_hcs_private_key', ''),
		'#attributes'	=> array('autocomplete'=>array('off')),
        '#required' => TRUE,
    );
 	$form['pay_hcs_main_fieldset']['payonline_hcs_form_payment_page'] = array(
		'#type' => 'select',
		'#title' => t('The form of the method of payment'),
		'#options' => array(
			'https://secure.payonlinesystem.com/'.$lng.'/payment/select/' => t('Selection form of payment instrument'),
			'https://secure.payonlinesystem.com/'.$lng.'/payment/select/qiwi/' => 'QIWI',
			'https://secure.payonlinesystem.com/'.$lng.'/payment/select/webmoney/' => 'WebMoney',
			'https://secure.payonlinesystem.com/'.$lng.'/payment/select/yandexmoney/' => 'YandexMoney',
			'https://secure.payonlinesystem.com/'.$lng.'/payment/' => t('Form of payment by credit card'),
		),
		'#default_value' => variable_get('payonline_hcs_form_payment_page', 'https://secure.payonlinesystem.com/ru/payment/select/'),
    );
 	
    $form['pay_hcs_main_fieldset']['payonline_hcs_format_type_name_pack'] = array(
		'#type' => 'select',
		'#title' => t('Pattern to form the of name packs payment'),
		'#options' => $hcsPoArrPatt,
		'#default_value' => variable_get('payonline_hcs_format_type_name_pack', 1),
    );
    
    $form['pay_hcs_main_fieldset']['payonline_hcs_offer_node_id'] = array(
		'#type' => 'textfield',
        '#required' => TRUE,
		'#title' => t('Node ID with contract offer'),
		'#default_value' => variable_get('payonline_hcs_offer_node_id', 0),
    );
    
    $form['pay_hcs_main_fieldset']['payonline_hcs_commission'] = array(
		'#type' => 'textfield',
		'#title' => t('Commission fee charged to users').'(%)',
		'#description' => t('If a user fee is not charged, the commission should be 0(zero)'),
		'#default_value' => variable_get('payonline_hcs_commission', 0),
    );
    
    $form['pay_hcs_main_fieldset']['payonline_hcs_use_handbook_verify'] = array(
		'#type' => 'checkbox',
		'#title' => t('Use an additional check on the room flats'),
		'#return_value' => 1, 
		'#default_value' => (int)variable_get('payonline_hcs_use_handbook_verify', 0),
    );
    
    $form['pay_hcs_strah_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Insurance'),
      '#weight' => 5,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#group' => 'group_settings',
    );
    
    $form['pay_hcs_strah_fieldset']['payonline_hcs_home_insurance'] = array(
		'#type' => 'textfield',
		'#title' => t('Home insurance'),
		'#default_value' => variable_get('payonline_hcs_home_insurance', 0),
    );
    
    $form['pay_hcs_strah_fieldset']['payonline_hcs_liability_insurance'] = array(
		'#type' => 'textfield',
		'#title' => t('Third party liability insurance'),
		'#default_value' => variable_get('payonline_hcs_liability_insurance', 0),
    );
    
    $form['pay_hcs_strah_fieldset']['payonline_hcs_full_insurance'] = array(
		'#type' => 'textfield',
		'#title' => t('Full insurance'),
		'#default_value' => variable_get('payonline_hcs_full_insurance', 0),
    );
    
    $form['pay_hcs_additional_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Additional payments'),
      '#weight' => 10,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#group' => 'group_settings',
    );
    
    $form['pay_hcs_additional_fieldset']['payonline_hcs_electric'] = array(
		'#type' => 'checkbox',
		'#title' => t('Electric power'),
        '#weight' => 1,
		'#default_value' => variable_get('payonline_hcs_electric', 0),
    );
    
    $form['pay_hcs_additional_fieldset']['payonline_hcs_gas'] = array(
		'#type' => 'checkbox',
		'#title' => t('Gas'),
        '#weight' => 2,
		'#default_value' => variable_get('payonline_hcs_gas', 0),
    );
    
    $form['pay_hcs_additional_fieldset']['payonline_hcs_entry_phone'] = array(
		'#type' => 'checkbox',
		'#title' => t('Entry phone'),
        '#weight' => 3,
		'#default_value' => variable_get('payonline_hcs_entry_phone', 0),
    );
    
    $form['pay_hcs_export_fieldset'] = array(
      '#type' => 'fieldset',
      '#title' => t('Export settings'),
      '#weight' => 15,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#group' => 'group_settings',
    );
    
    $form['pay_hcs_export_fieldset']['payonline_hcs_export_first_row_is_header'] = array(
		'#type' => 'checkbox',
		'#title' => t('Add in the first row the name of columns'),
        '#weight' => 1,
		'#default_value' => variable_get('payonline_hcs_export_first_row_is_header', 0),
    );
    
    $form['pay_hcs_export_fieldset']['payonline_hcs_export_translate_columns'] = array(
		'#type' => 'checkbox',
		'#title' => t('Translate column names'),
        '#weight' => 2,
		'#default_value' => variable_get('payonline_hcs_export_translate_columns', 0),
        '#states' => array(
            'visible' => array(
                ':input[name="payonline_hcs_export_first_row_is_header"]' => array('checked' => TRUE),
            ),
            'disabled' => array(
                ':input[name="payonline_hcs_export_first_row_is_header"]' => array('checked' => FALSE),
            ),
        ),
    );
    
    $form['pay_hcs_export_fieldset']['payonline_hcs_export_file_encode'] = array(
        '#type' => 'select',
        '#title' => t('File encoding'),
        '#required' => TRUE,
        '#default_value' => variable_get('payonline_hcs_export_file_encode', 1),
        '#weight' => 3,
        '#options' => $arrFileEncode,
    );
    
    $form['#validate'][] = 'payonline_hcs_admin_validate';
    
    return system_settings_form($form);
}

function payonline_hcs_admin_validate($form, &$form_state){
    if(empty($form_state['values']['payonline_hcs_offer_node_id'])){
        form_set_error('payonline_hcs_offer_node_id', t('Offer node ID must be greater than zero.'));
    }
}

function payonline_hcs_viewpayment($form = array(), &$form_state){
	global $user;
	$pathModule = $icoFilter = '';
    $collapsed = true;
    
    if($user->uid == 0){
        drupal_access_denied();
        drupal_exit();
    }
    
	$proc = 0;
	$summWithoutProc = 0;
	$isAdmin	= user_access('administer_payonline_hcs');
	
    if($isAdmin){
		$pathModule = AP_PAYONLINE_PATH_MODULE.'/images/';
        $icoFilter	= '<img src="'.$pathModule.'filter.png" alt="Filter" title="Filter" width="10" align="middle" />';
        $arg = (string)payonline_hcs_isset_var($form_state['input']['pay_hcs_filter_text']);
		$argType = (int)payonline_hcs_isset_var($form_state['input']['pay_hcs_filter_type']);
		
		if((((bool)$arg) == true) or ($argType == 3 and ((bool)$arg) == false)){
			$collapsed = false;
		}
		
		$form['pay_hcs_filter_payonline'] = array(
		  '#type' => 'fieldset',
		  '#title' => t('Filter'),
		  '#weight' => -5,
		  '#collapsible' => TRUE,
		  '#collapsed' =>$collapsed,
		);
		
		$form['pay_hcs_filter_payonline']['pay_hcs_filter_type'] = array(
			'#type' => 'select',
			'#title' => t('Filter'),
			'#options' => array(
				1 => t('Personal account number'),
				2 => t('Account number'),
				3 => t('Made by anonymous'),
			),
			'#default_value' => $argType,
			'#weight' => 1,
		);
		$form['pay_hcs_filter_payonline']['pay_hcs_filter_text'] = array(
			'#type' => 'textfield',
			'#value' => $arg,
			'#title' => t('Search'),
			'#weight' => 2,
            '#states' => array(
                'disabled' => array(
                    'select[name="pay_hcs_filter_type"]' => array('value' => 3),
                ),
            ),
		);
		
		$form['pay_hcs_filter_payonline']['actions'] = array(
			'#type' => 'actions',
			'#attributes' => array('class' => array('container-inline')),
		);
		$form['pay_hcs_filter_payonline']['actions']['submit'] = array(
				'#type' => 'submit',
				'#value' => t('Filter'),
		);
		$form['pay_hcs_filter_payonline']['actions']['reset'] = array(
				'#type' => 'submit',
				'#value' => t('Cancel'),
		);
	}
	
	$arrProv['ru'] = array(
		0 => 'Нет данных',
		'Card' => 'Кредитная карта',
		'Qiwi' => 'Qiwi',
		'WebMoney' => 'WebMoney',
		'YandexMoney' => 'YandexMoney',
	);
	
	$arrProv['en'] = array(
		0 => 'Empty data',
		'Card' => 'Credit card',
		'Qiwi' => 'Qiwi',
		'WebMoney' => 'WebMoney',
		'YandexMoney' => 'YandexMoney',
	);
	
	$header = array();
	
	if($isAdmin){
		$header[] = array('data' => t('User'));
	}
	
	$headArr = array(
		array('data' => t('Personal account number'), 'field' => 'lc_fkey'),
		array('data' => t('Order number'), 'field' => 'order_id'),
		array('data' => t('Date adoption payment'), 'field' => 'date_adoption_payment_in_payonline','sort' => 'desc'),
		array('data' => t('Payment tool'), 'field' => 'provider'),
		array('data' => t('Currency'), 'field' => 'currency'),
		array('data' => t('Sum'), 'field' => 'summ'),
		array('data' => t('Insurance')),
		array('data' => t('Additional payments')),
		array('data' => t('Peni')),
		array('data' => t('Commission')),
		array('data' => t('Sum').' + '.t('Commission')),
		array('data' => t('Pack of payment number')),
	);
	
	foreach($headArr as $hval){
		$header[] = $hval;
	}
	unset($hval);
	
	$rows = array();
	
	try{
		$query 	= db_select('payonline_hcs_payments', 'pays')->extend('PagerDefault')	//Pager Extender
		->limit(25)
		->extend('TableSort')
		->orderByHeader($header);
		
		if($isAdmin){
			$query->leftJoin('users', 'u', 'pays.uid = u.uid');
			$query->leftJoin('payonline_hcs_payments_packs', 'pack', 'pack.pp_id = pays.status_payment');
			$query->fields('u', array('uid','name'));
		}
		
		$query->fields('pays', array('lc_fkey', 'order_id', 'date_adoption_payment_in_payonline', 'provider', 'currency', 'summ', 'home_insurance', 'liability_insurance', 'full_insurance', 'electric', 'gas', 'electric_pin', 'gas_pin', 'entry_phone', 'peni', 'commis'))
		->condition('pays.payment_adopted_status', 1, '=');
		
        //Allow for administrator view all payments
		if(!$isAdmin){
			$query->condition('pays.uid', $user->uid);
		}
        if($isAdmin){
            $query->fields('pack', array('pp_id','pp_pack_num'));
        }
        
		if(!$collapsed){
			switch($argType){
				case 1: default:
					$query->condition('pays.lc_fkey', '%'.db_like($arg).'%', 'LIKE');
				break;
				case 2:
					$query->condition('pays.order_id', '%'.db_like($arg).'%', 'LIKE');
				break;
				case 3:
					$query->condition('pays.uid', 0);
				break;
			}
		}
		
		$result = $query->execute();
	}
	catch(Exception $e){
		watchdog_exception('payonline-hcs-error', $e);
		drupal_set_message('Error. More information in '.l('syslog','admin/reports/dblog').'.<br />'.check_plain($e->getMessage()), 'error', FALSE);
		return $form;
	}
	$noBalans = 0;
    $gTxt = t('Anonymous');
    foreach($result as $key=>$val){
		$val->date_adoption_payment_in_payonline	= format_date(strtotime($val->date_adoption_payment_in_payonline)+date('Z'), 'custom', 'd.m.Y H:i:s', 'Europe/Moscow');
		$val->lc_fkey								= l($val->lc_fkey, 'javascript:', array('attributes'=>array('class'=>array('hcs-filter-link'),'onclick'=>'javascript:jQuery("#edit-pay-hcs-filter-text").val("'.$val->lc_fkey.'"); jQuery("#edit-pay-hcs-filter-payonline").removeClass("collapsed"); jQuery("#edit-pay-hcs-filter-type").val("1"); jQuery(".fieldset-wrapper").show(); return false;')));
		$val->order_id								= l($val->order_id, 'javascript:', array('attributes'=>array('class'=>array('hcs-filter-link'),'onclick'=>'javascript:jQuery("#edit-pay-hcs-filter-text").val("'.$val->order_id.'"); jQuery("#edit-pay-hcs-filter-payonline").removeClass("collapsed"); jQuery("#edit-pay-hcs-filter-type").val("2"); jQuery(".fieldset-wrapper").show(); return false;')));
		$val->provider 								= $arrProv[$user->language][(string)$val->provider];
		if($isAdmin){
			if(empty($val->uid)){
                $val->name = l($gTxt, 'javascript:', array('attributes'=>array('class'=>array('hcs-filter-link'),'onclick'=>'javascript:jQuery("#edit-pay-hcs-filter-payonline").removeClass("collapsed"); jQuery("#edit-pay-hcs-filter-type").val("3").change(); jQuery(".fieldset-wrapper").show(); return false;')));
            }
            else{
                $val->name	 							= l($val->name, 'user/'.$val->uid.'/edit');
            }
		}
		$noBalans									= $val->home_insurance+$val->liability_insurance+$val->full_insurance+$val->peni+$val->electric+$val->gas+$val->entry_phone;
		$val->summCommis							= number_format((($val->summ+$noBalans)*$val->commis)/100, 2, '.', ',');
		$val->summItog								= number_format(((($val->summ+$noBalans)*$val->commis/100)+($val->summ+$noBalans)), 2, '.', ',');
		$val->summ	 								= number_format((float)payonline_hcs_isset_var($val->summ), 2, '.', ',');
		if(!empty($val->commis)){
            $val->commis                            .= '%,&nbsp;'.$val->summCommis;
        }
        
        if(!empty($val->home_insurance)){
            $val->home_insurance = t('Home insurance short').':'.$val->home_insurance;
        }
        else{
            $val->home_insurance = '';
        }
		if(!empty($val->liability_insurance)){
            $val->home_insurance .= '<br />'.t('Third party liability insurance short').':'.$val->liability_insurance;
        }
		if(!empty($val->full_insurance)){
            $val->home_insurance .= '<br />'.t('Full insurance short').':'.$val->full_insurance;
        }
        //~ Additional payments
        if(!empty($val->electric)){
            $val->electric = t('Electric power').':'.l($val->electric, 'javascript:', array('attributes'=>array('title'=>$val->electric_pin,'class'=>array('hcs-filter-link'),'onclick'=>'return false;')));
        }
        else{
            $val->electric = '';
        }
        if(!empty($val->gas)){
            $val->electric .= '<br />'.t('Gas').':'.l($val->gas, 'javascript:', array('attributes'=>array('title'=>$val->gas_pin,'class'=>array('hcs-filter-link'),'onclick'=>'return false;')));
        }
        if(!empty($val->entry_phone)){
            $val->electric .= '<br />'.t('Entry phone').':'.$val->entry_phone;
        }
        
        if($isAdmin){
            $val->pack_num  	 						= l($val->pp_pack_num, 'admin/payonline_hcs/packs/view/'.$val->pp_id).'('.$val->pp_id.')';
        }
        $arrUnset = array(
            'uid', 'pp_pack_num', 'summCommis', 'pp_id',
            'liability_insurance', 'full_insurance', 'electric_pin',
            'gas', 'gas_pin', 'entry_phone',
        );
        $row	= (array)($val);
		foreach($arrUnset as $uVal){
            unset($row[$uVal]);
        }
        $rows[] = $row;
	}
	unset($key,$val);
	
	$form['payonline_payments'] = array(
		'#theme' => 'table',
		'#header' => $header,
		'#rows' => $rows,
		'#pager' => theme('pager'),
		'#empty' => t('No data.'),
	);
	$form['pager'] = array('#markup' => theme('pager'));
    
    return $form;
}

function payonline_hcs_viewpayment_submit($form, &$form_state){
	$op = $form_state['values']['op'];
	switch ($op) {
		case t('Filter'):
			$form_state['rebuild'] = TRUE;
		break;
		case t('Reset'):
			$form_state['rebuild'] = FALSE;
		break;
	}
}

/**
 * Add the pack of payment form
 * */
 
function payonline_hcs_add_pack_form(){
	drupal_add_library('system','ui.datepicker');
	drupal_add_js('jQuery(document).ready(function(){jQuery( ".pickadate" ).datepicker({
      dateFormat: "yy-mm-dd",
      autoSize: true
    });});', 'inline'); 
	
	$coutnPay	= 0;
	$summ 		= 0;
    $form = array();
	
    if(payonline_hcs_avaliable_payments_for_packs($coutnPay, $summ)){
		$form['payonline_hcs_pack_operating_day'] = array(
			'#type' => 'textfield',
			'#title' => t('Operating day'),
			'#value' => date('Y-m-d'),
			'#size' => 10,
			'#maxlength' => 10,
			'#attributes' => array('class' => array('pickadate')),
		);
		
		$form['payonline_hcs_pack_count_payments'] = array(
			'#type' => 'hidden',
			'#default_value' => $coutnPay,
		);
		
		$form['payonline_hcs_pack_summ'] = array(
			'#type' => 'hidden',
			'#default_value' => $summ,
		);
		
		$form['submit'] = array(
			'#type' => 'submit',
			'#value' => t('Add pack of payment'),
		);
		$form['pay_hcs_konsalt_cancel'] = array(
			'#type' => 'link',
			'#title' => t('Cancel'),
			'#href' => 'admin/payonline_hcs/packs',
			'#weight' => 2,
		);
	}
	return $form;
}

/**
 * Submit add pack form
 * */
function payonline_hcs_add_pack_form_submit($form, &$form_state){
	global $user;
    
    $hcsPoArrPatt = _payonline_hcs_pack_patterns();
	
	$operDay	= check_plain($form_state['input']['payonline_hcs_pack_operating_day']);
	
    $packNum    = $hcsPoArrPatt[variable_get('payonline_hcs_format_type_name_pack', 1)];
    $packNum    = preg_replace('/(\(.*\))|(\[)|(\])/', '', $packNum);
    $packNum    = strftime($packNum);
    
    $packSum	= check_plain($form['payonline_hcs_pack_summ']['#default_value']);
	$packCount	= check_plain($form['payonline_hcs_pack_count_payments']['#default_value']);
	
	$packId		= payonline_hcs_add_new_pack($operDay, $packNum, $packSum, $packCount);
	
	if($packId > 0){
		try{
			//Fill payments reestr
			$result = db_query('INSERT INTO 
			{payonline_hcs_payments_reestr} 
			(`pr_order_id`, `pr_lc_fkey`, `pack_id`, `pr_merchant_id`, `pr_transaction`, `pr_date_adoption_payment`, `pr_date_adoption_payment_in_payonline`, `pr_summ`, `pr_commis`, `pr_home_insurance`, `pr_liability_insurance`, `pr_full_insurance`, `pr_peni`, `pr_electric`, `pr_gas`, `pr_electric_pin`, `pr_gas_pin`, `pr_entry_phone`)
			SELECT `order_id`, `lc_fkey`, '.$packId.', `merchant_id`, `transaction`, `date_adoption_payment`, `date_adoption_payment_in_payonline`, `summ`, `commis`, `home_insurance`, `liability_insurance`, `full_insurance`, `peni`, `electric`, `gas`, `electric_pin`, `gas_pin`, `entry_phone` FROM {payonline_hcs_payments} WHERE payment_adopted_status = 1 and status_payment = 0 and date_adoption_payment > \'1970-01-01\'
			')->rowCount();
			
			if(!empty($result)){
				$updRes = db_query("UPDATE {payonline_hcs_payments} as upd INNER JOIN {payonline_hcs_payments_reestr} as pay ON upd.order_id=pay.pr_order_id SET upd.date_added_payment_to_pack ='".date('Y-m-d H:i:s')."', upd.status_payment = ".$packId." WHERE pay.pack_id='".$packId."'");
				drupal_set_message(t('Pack of payment was added.'));
				drupal_goto('admin/payonline_hcs/packs');
			}
			watchdog('payonline-hcs-info', 'Fill of payments reestr for the pack #'.$packNum.' completed. Payonline HCS was <strong>'.$user->name.'</strong> at '.date('d.m.Y h:m:s'));
		}
		catch(Exception $e){
			watchdog_exception('payonline-hcs-error', $e);
			drupal_set_message('Error. More information in '.l('syslog','admin/reports/dblog').'.<br />'.check_plain($e->getMessage()), 'error', FALSE);
			return false;
		}
	}
	return true;
}

/**
 * Check whether previously not exported payments
 * */
function payonline_hcs_avaliable_payments_for_packs(&$countPay, &$summ){
	try{
		$result = db_query("SELECT GROUP_CONCAT(DATE_FORMAT(date_adoption_payment_in_payonline,'%d.%m.%Y')) as date, sum(summ) as allSumm, COUNT(*) as count, 1 as keyid FROM {payonline_hcs_payments} WHERE payment_adopted_status = 1 and status_payment = 0 and date_adoption_payment > '1970-01-01' ORDER BY date_adoption_payment_in_payonline ASC")->fetchAllAssoc('keyid');
	}
	catch(Exception $e){
		watchdog_exception('payonline-hcs-error', $e);
		drupal_set_message('Error. More information in '.l('syslog','admin/reports/dblog').'.<br />'.check_plain($e->getMessage()), 'error', FALSE);
		return false;
	}
	
	if(empty($result[1]->date) or empty($result[1]->allSumm) or empty($result[1]->count)){
		drupal_set_message(t('No data.'),'warning', FALSE);
		return false;
	}
	else{
		$countPay		= $result[1]->count;
		$summ			= $result[1]->allSumm;
		$arrMonth 		= array_unique(explode(",", $result[1]->date));
		if(sizeof($arrMonth) > 1){
			$msgMonth 	= 'Payment for the period of: %day.';
			$days		= min($arrMonth).'-'.max($arrMonth);
		}
		else{
			$msgMonth 	= 'Day of payment: %day.';
			$days		= $arrMonth[0];
		}
		drupal_set_message(t('This will create a pack of payment for a total of %sum and for a count payments of %count.', array('%sum'=>number_format($result[1]->allSumm, 2, '.', ' '),'%count'=>$result[1]->count)).'&nbsp;'.t($msgMonth, array('%day'=>$days)), 'status', FALSE);
		return true;
	}
}

/**
 * Add new payment pack. Summ and count payments gets from func. "avaliable_payments_for_packs"
 * */
function payonline_hcs_add_new_pack($operDay, $packNum, $packSum, $packCount){
	global $user;
	try{
		return (int)db_insert('payonline_hcs_payments_packs')->fields(array(
			'pp_operating_day' => $operDay,
			'pp_pack_num' => $packNum,
			'pp_summ' => $packSum,
			'pp_number_payments' => $packCount,
		))
		->execute();
		watchdog('info', 'Created a new pack of payment #'.$packNum.' completed. Count payments: '.$packCount.', pack summ: '.$packSum.'. Payonline HCS was <strong>'.$user->name.'</strong> at '.date('d.m.Y h:m:s'));
	}
	catch(Exception $e){
		watchdog_exception('payonline-hcs-error', $e);
		drupal_set_message('Error. More information in '.l('syslog','admin/reports/dblog').'.<br />'.check_plain($e->getMessage()), 'error', FALSE);
		return 0;
	}
}


/**
 * List all packs of payment
 * */
function payonline_hcs_viewpacks(){
	global $user;
	$pathModule = base_path().drupal_get_path('module', 'payonline_hcs').'/images/';
	$icoList	= '<img src="'.$pathModule.'list.gif" alt="" title="" width="20" />';
	$icoExcel	= '<img src="'.$pathModule.'excel.gif" alt="" title="" width="20" />';
	$icoRemove	= '<img src="'.$pathModule.'remove.gif" alt="" title="" width="20" />';
	
	$attrLinks	= array('html'=>true, 'attributes'=>array('style'=>'vertical-align:top'));
	
	$header = array(
			array('data' => t('Operating day'), 'field' => 'pp_operating_day', 'sort' => 'desc'),
			array('data' => t('Pack of payment number'), 'field' => 'pp_pack_num'),
			array('data' => t('Total payments packs payment'), 'field' => 'pp_summ'),
			array('data' => t('Number of payments'), 'field' => 'pp_number_payments'),
			array('data' => t('Actions')),
	);
	$rows = array();
	try{
		$query 	= db_select('payonline_hcs_payments_packs', 'packs')->extend('PagerDefault')	//Pager Extender
		->limit(25)
		->extend('TableSort')
		->orderByHeader($header);
		
		$query->fields('packs', array('pp_id','pp_operating_day', 'pp_pack_num', 'pp_summ', 'pp_number_payments'));
		
		$result = $query->execute();
	}
	catch(Exception $e){
		watchdog_exception('payonline-hcs-error', $e);
		drupal_set_message('Error. More information in '.l('syslog','admin/reports/dblog').'.<br />'.check_plain($e->getMessage()), 'error', FALSE);
		return '';
	}
	
	foreach($result as $key=>$val){
		$val->pp_operating_day = format_date(strtotime($val->pp_operating_day), 'custom', 'd.m.Y');
		$val->pp_summ = number_format($val->pp_summ, 2, '.', ',');
		$val->actions	= $icoList.'&nbsp;'.l(t('List payments'), 'admin/payonline_hcs/packs/view/'.$val->pp_id, $attrLinks);
		$val->actions	.= '&nbsp;'.$icoExcel.'&nbsp;'.l(t('Export to CSV'), 'admin/payonline_hcs/packs/export/'.$val->pp_id, $attrLinks);
		unset($val->pp_id);
        $row	= (array)($val);
		$rows[] = $row;
	}
	unset($key,$val);
	
	$output = theme('table', array('header'=>$header, 'rows'=>$rows, 'empty' => t('No data.')));
	
	$output .= theme('pager',
		array(
			'tags' => array()
		)
    );
    return $output;
}

/**
 * View payments by pack
 * */
function payonline_hcs_viewreestrpack($packId = 0){
	global $user;
	$namePack='';
	$header = array(
			array('data' => t('Personal account number'), 'field' => 'r.pr_lc_fkey'),
			array('data' => t('Account number'), 'field' => 'r.pr_order_id'),
			array('data' => 'Merchant ID', 'field' => 'r.pr_merchant_id'),
			array('data' => t('Sum'), 'field' => 'r.pr_summ'),
			array('data' => t('Insurance')),
            array('data' => t('Additional payments')),
			array('data' => t('Peni')),
			array('data' => t('Date adoption payment'), 'field' => 'r.pr_date_adoption_payment'),
			array('data' => t('Date adoption payment in Payonline system'), 'field' => 'r.pr_date_adoption_payment_in_payonline','sort' => 'desc'),
			array('data' => t('Transaction number'), 'field' => 'r.pr_transaction'),
			array('data' => t('Commission').' (%)', 'field' => 'r.pr_commis'),
			array('data' => t('The amount of commission').'(%)'),
			array('data' => t('Sum').' + '.t('Commission')),
	);
	$rows = array();
	
	try{
		$query 	= db_select('payonline_hcs_payments_reestr', 'r')->extend('PagerDefault')	//Pager Extender
		->limit(25)
		->extend('TableSort')
		->orderByHeader($header);
		
		$query->fields('r', array('id','pr_lc_fkey', 'pr_order_id', 'pr_merchant_id', 'pr_summ', 'pr_home_insurance', 'pr_liability_insurance', 'pr_full_insurance', 'pr_electric', 'pr_gas', 'pr_electric_pin', 'pr_gas_pin', 'pr_entry_phone', 'pr_peni', 'pr_date_adoption_payment', 'pr_date_adoption_payment_in_payonline', 'pr_transaction'));
		$query->condition('r.pack_id',$packId, '=');
		
		$query->innerJoin('payonline_hcs_payments_packs', 'pp', 'pp.pp_id = r.pack_id');
		$query->fields('pp', array('pp_pack_num'));
		$query->fields('r', array('pr_commis'));
		
		$result = $query->execute();
	}
	catch(Exception $e){
		watchdog_exception('payonline-hcs-error', $e);
		drupal_set_message('Error. More information in '.l('syslog','admin/reports/dblog').'.<br />'.check_plain($e->getMessage()), 'error', FALSE);
		return '';
	}
	$noBalans = 0;
	foreach($result as $key=>$val){
        $namePack = $val->pp_pack_num;
        $noBalans									= $val->pr_home_insurance+$val->pr_liability_insurance+$val->pr_full_insurance+$val->pr_peni+$val->pr_electric+$val->pr_gas+$val->pr_entry_phone;
		
        $val->pr_date_adoption_payment = format_date(strtotime($val->pr_date_adoption_payment), 'custom', 'd.m.Y H:i:s');
		$val->pr_date_adoption_payment_in_payonline = format_date(strtotime($val->pr_date_adoption_payment_in_payonline)+date('Z'), 'custom', 'd.m.Y H:i:s', 'Europe/Moscow');
		$val->summCommis							= number_format((($val->pr_summ+$noBalans)*$val->pr_commis)/100, 2, '.', ',');
		$val->summItog								= number_format(((($val->pr_summ+$noBalans)*$val->pr_commis/100)+($val->pr_summ+$noBalans)), 2, '.', ',');
		$val->pr_summ								= number_format($val->pr_summ, 2, '.', ',');
		if(!empty($val->pr_home_insurance)){
            $val->pr_home_insurance = t('Home insurance short').':'.$val->pr_home_insurance;
        }
        else{
            $val->pr_home_insurance = '';
        }
		if(!empty($val->pr_liability_insurance)){
            $val->pr_home_insurance .= '<br />'.t('Third party liability insurance short').':'.$val->pr_liability_insurance;
        }
		if(!empty($val->pr_full_insurance)){
            $val->pr_home_insurance .= '<br />'.t('Full insurance short').':'.$val->pr_full_insurance;
        }
        //~ Additional payments
        if(!empty($val->pr_electric)){
            $val->pr_electric = t('Electric power').':'.l($val->pr_electric, 'javascript:', array('attributes'=>array('title'=>$val->pr_electric_pin,'class'=>array('hcs-filter-link'),'onclick'=>'return false;')));
        }
        else{
            $val->pr_electric = '';
        }
        if(!empty($val->pr_gas)){
            $val->pr_electric .= '<br />'.t('Gas').':'.l($val->pr_gas, 'javascript:', array('attributes'=>array('title'=>$val->pr_gas_pin,'class'=>array('hcs-filter-link'),'onclick'=>'return false;')));
        }
        if(!empty($val->pr_entry_phone)){
            $val->pr_electric .= '<br />'.t('Entry phone').':'.$val->pr_entry_phone;
        }
        unset($val->id,$val->pp_pack_num,$val->pr_liability_insurance,$val->pr_full_insurance,$val->pr_electric_pin,$val->pr_gas,$val->pr_gas_pin,$val->pr_entry_phone);
        $row	= (array)($val);
		$rows[] = $row;
	}
	unset($key,$val);
	
    drupal_set_message(t('Pack of payment number').':&nbsp;<strong>'.$namePack.'</strong>.');
    
	$output = theme('table', array('header'=>$header, 'rows'=>$rows, 'empty' => t('No data.')));
	
	
	$output .= theme('pager',
		array(
			'tags' => array()
		)
    );
    
    return $output;
}

function _payonline_hcs_t_col(&$item, $key, $encode){
    $fencode = (int)variable_get('payonline_hcs_export_file_encode', 1);
    $item =  preg_replace('/pr_/', '', $item);
    $item =  preg_replace('/_/', ' ', $item);
    $item =  ucfirst($item);
    if(variable_get('payonline_hcs_export_translate_columns', 0) > 0){
        $item = t($item);
    }
    if($fencode > 1){
        $item = mb_convert_encoding($item, $encode, "UTF-8");
    }
}

/**
 * Export to CSV file
 * */
function payonline_hcs_export_pack($packId = 0){
	global $user;
    $arrFileEncode = _payonline_hcs_encodes();
    $fencode = (int)variable_get('payonline_hcs_export_file_encode', 1);
    $encode = $arrFileEncode[$fencode];
	try{
        $query 	= db_select('payonline_hcs_payments_reestr', 'r');
		$query->fields('r', array('id','pr_lc_fkey', 'pr_order_id', 'pr_summ', 'pr_date_adoption_payment', 'pr_date_adoption_payment_in_payonline', 'pr_home_insurance', 'pr_liability_insurance', 'pr_full_insurance', 'pr_peni', 'pr_electric', 'pr_gas', 'pr_electric_pin', 'pr_gas_pin', 'pr_entry_phone', 'pr_commis', 'pr_transaction'));
		$query->condition('r.pack_id',$packId, '=');
		$query->innerJoin('payonline_hcs_payments_packs', 'pp', 'pp.pp_id = r.pack_id');
		$query->fields('pp', array('pp_pack_num'));
		
		$result = $query->execute();
		
		$count  = $result->rowCount();
		if ($result == false OR empty($count)) {
				drupal_set_message(t("No data."), 'warning', FALSE);
				return false;
		}
		
		while($row = $result->fetchAssoc()){
			$rows[] = $row;
		}
		$filename 	=	$rows[0]['pp_pack_num'].'.csv';
        drupal_add_http_header('Content-Type', 'text/csv');
        drupal_add_http_header('Content-Disposition', 'attachment; filename='. $filename);
		drupal_send_headers();
		$noBalans = 0;
        $fp = fopen('php://output', 'w');
		if(variable_get('payonline_hcs_export_first_row_is_header', 0) > 0){
            $header = array_keys($rows[0]);
            array_pop($header);
            $header[] = 'sumCommis';
            array_walk($header, '_payonline_hcs_t_col', $encode);
            fputcsv($fp, $header, ';', ' ');
        }
        foreach($rows as $rKey=>$rVal){
			unset($rVal['pp_pack_num']);
            $noBalans = $rVal['pr_home_insurance']+$rVal['pr_liability_insurance']+$rVal['pr_full_insurance']+$rVal['pr_peni']+$rVal['pr_electric']+$rVal['pr_gas']+$rVal['pr_entry_phone'];
			$rVal['sumCommis'] = (($rVal['pr_summ']+$noBalans)*$rVal['pr_commis'])/100;
			foreach($rVal as $key=>$val){
			  $values[] = decode_entities(strip_tags($val)); 
			}
            $str = implode(';', $values);
            array_walk($values, '_payonline_hcs_t_col', $encode);
            fputcsv($fp, $values, ';', ' ');
            unset($values,$key,$val);
		}
		unset($rKey,$rVal);
		watchdog('payonline-hcs-info', 'Export pack #'.$filename.' completed. Payonline HCS was <strong>'.$user->name.'</strong> at '.date('d.m.Y h:m:s'));
		fclose($fp);
        drupal_exit();
	}
	catch(Exception $e){
		watchdog_exception('payonline-hcs-error', $e);
		drupal_set_message('Error. More information in '.l('syslog','admin/reports/dblog').'.<br />'.check_plain($e->getMessage()), 'error', FALSE);
		return '';
	}
}

/**
 * Export payments by date range
 * */
function payonline_hcs_export_by_date_form(){
	drupal_add_library('system','ui.datepicker');
	drupal_add_js('jQuery(document).ready(function(){jQuery( ".pickadate" ).datepicker({
      dateFormat: "yy-mm-dd",
      autoSize: true
    });});', 'inline'); 
    drupal_add_css('.form-item-pay-hcs-konsalt-payonline-pack-date-from {float: left; margin: 0 10px 0 0 !important;}',$option['type'] = 'inline');
    
	
	$coutnPay	= 0;
	$summ 		= 0;
	
	$form = array();
	$form['payonline_hcs_pack_date_from'] = array(
		'#type' => 'textfield',
		'#title' => t('Start date'),
		'#default_value' => date('Y-m-d'),
		'#size' => 10,
		'#maxlength' => 10,
		'#required' => TRUE,
		'#attributes' => array('class' => array('pickadate')),
	);
	
	$form['payonline_hcs_pack_date_to'] = array(
		'#type' => 'textfield',
		'#title' => t('End date'),
		'#default_value' => date('Y-m-d'),
		'#size' => 10,
		'#maxlength' => 10,
		'#required' => TRUE,
		'#attributes' => array('class' => array('pickadate')),
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Export'),
	);
	return $form;
}

function payonline_hcs_export_by_date_form_submit($form, &$form_state){
	global $user;
    $arrFileEncode = _payonline_hcs_encodes();
    $fencode = (int)variable_get('payonline_hcs_export_file_encode', 1);
    $encode = $arrFileEncode[$fencode];
	$dFrom	= format_date(strtotime($form_state['input']['payonline_hcs_pack_date_from']), 'custom', 'Y-m-d H:i:s');
	$dTo	= format_date(strtotime($form_state['input']['payonline_hcs_pack_date_to']), 'custom', 'Y-m-d 23:59:59');
	try{
		$result	= db_select('payonline_hcs_payments', 'p')
		->fields('p',array('id', 'lc_fkey', 'order_id', 'summ', 'date_adoption_payment', 'date_adoption_payment_in_payonline', 'home_insurance', 'liability_insurance', 'full_insurance', 'peni', 'electric', 'gas', 'electric_pin', 'gas_pin', 'entry_phone', 'commis', 'transaction'))
		->condition('payment_adopted_status', array(1), '=')
		->condition('date_adoption_payment_in_payonline', array($dFrom, $dTo), 'BETWEEN')
		->execute();
		
		$count  = $result->rowCount();
	
		if ($result == false OR empty($count)) {
					drupal_set_message(t("No data."), 'warning', FALSE);
					return false;
		}
		$filename 	=	'export_payments_'.format_date(strtotime($dFrom), 'custom', 'd.m.Y').'-'.format_date(strtotime($dTo), 'custom', 'd.m.Y').'.csv';
		//~ drupal_add_http_header('Content-Type', 'text/csv; charset='.$encode);
        drupal_add_http_header('Content-Type', 'text/csv');
        drupal_add_http_header('Content-Disposition', 'attachment; filename='. $filename);
		drupal_send_headers();
		
        while($row = $result->fetchAssoc()){
			$rows[] = $row;
		}
        $noBalans = 0;
        $fp = fopen('php://output', 'w');
		if(variable_get('payonline_hcs_export_first_row_is_header', 0) > 0){
            $header = array_keys($rows[0]);
            $header[] = 'sumCommis';
            array_walk($header, '_payonline_hcs_t_col', $encode);
            fputcsv($fp, $header, ';', ' ');
        }
        
        foreach($rows as $rKey=>$rVal){
			$noBalans = $rVal['home_insurance']+$rVal['liability_insurance']+$rVal['full_insurance']+$rVal['peni']+$rVal['electric']+$rVal['gas']+$rVal['entry_phone'];
			$rVal['sumCommis'] = (($rVal['summ']+$noBalans)*$rVal['commis'])/100;
			foreach($rVal as $key=>$val){
			  if($key == 'id'){
					$keysArr[] = $val;
			  }
              $values[] = decode_entities(strip_tags($val)); 
			}
            array_walk($values, '_payonline_hcs_t_col', $encode);
            fputcsv($fp, $values, ';', ' ');
            unset($values,$key,$val);
		}
		unset($rKey,$rVal);
		
		db_update('payonline_hcs_payments')
		->fields(array('date_export_payment' => date('Y-m-d H:i:s')))
		->condition('id', $keysArr, 'IN')
		->execute();
		watchdog('payonline-hcs-info', 'Export payments by date range '.$dFrom.'-'.$dTo.' completed. Payonline HCS was <strong>'.$user->name.'</strong> at '.date('d.m.Y h:m:s'));
		fclose($fp);
        drupal_exit();
	}
	catch(Exception $e){
		watchdog_exception('payonline-hcs-error', $e);
		drupal_set_message('Error. More information in '.l('syslog','admin/reports/dblog').'.<br />'.check_plain($e->getMessage()), 'error', FALSE);
		return '';
	}
}

/**
 * Page with forms for filling handbooks with the 
 * numbers flats, electric PIN's, gas PIN's
 * */
function payonline_hcs_fill_handbooks_page(){
    $forms = array();
    $arrForms = array('flats', 'electric', 'gas');
    foreach($arrForms as $key=>$val){
        $forms[] = drupal_get_form('payonline_hcs_form_fill_handbooks_with_'.$val, $key);
    }
    return $forms;
}


/**
 * Form for filling handbooks
 * */
function payonline_hcs_fill_handbooks_form($form, &$form_state, $arg){
    $title = $form = array();
    $markup = '';
    $arg = (int)$arg;
    switch($arg){
        case 0:
            $title = array(t('Handbook with numbers flats'), t('The file with the account number and the room flats'));
            $markup = t('This handbook required for additional verify of personal account number input.');
        break;
        case 1:
            $title = array(t('Handbook with the electric personal identification numbers'), t('The file with the elrectric personal accounts numbers'));
            $markup = t('This handbook is required to enable users of the site could to pay for electricity.');
        break;
        case 2:
            $title = array(t('Handbook with the gas personal identification numbers'),t('The file with the gas personal accounts numbers'));
            $markup = t('This handbook is required to enable users of the site could to pay for gas.');
        break;
    }
    $form['hcs_fieldset'] = array(
        '#type' => 'fieldset',
        '#title' => $title[0],
        '#weight' => $arg,
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    if(!empty($markup)){
        $form['hcs_fieldset']['pay_hcs_markup'] = array(
            '#type'=>'item',
            '#title' => $markup,
            '#weight' => -1,
        );
    }
    
    $form['hcs_fieldset']['pay_hcs_file'] = array(
        '#type' => 'file', 
        '#title' => $title[1], 
        '#size' => 40,
        '#weight' => 1,
        '#description' => t('File size should not exceed <strong>%max_file_size</strong>(upload_max_filesize) or should not exceed <strong>%post_max_size</strong>(post_max_size).', array('%max_file_size'=>ini_get("upload_max_filesize").'b','%post_max_size'=>ini_get("post_max_size").'b')),
    );
    $form['hcs_fieldset']['pay_hcs_fileencode'] = array(
        '#type' => 'select',
        '#title' => t('File encoding'),
        '#required' => TRUE,
        '#default_value' => 'utf8',
        '#weight' => 2,
        '#options' => array('utf8' => 'UTF-8','cp1251' => 'cp1251'),
    );
    $form['#attributes'] = array('enctype' => "multipart/form-data");
    
    if(module_exists('alcom_konsalt') and $arg == 0){
        unset($form['hcs_fieldset']['pay_hcs_file']);
        unset($form['hcs_fieldset']['pay_hcs_fileencode']);
        $form['hcs_fieldset']['pay_hcs_markup_alcom'] = array(
            '#type'=>'item',
            '#title' => t('Module Alcom-Consult is on, so the data will be imported from the module.'),
            '#weight' => 1,
        );
    }
    
    $form['hcs_fieldset']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Fill handbook'),
        '#submit' => array('payonline_hcs_fill_pan_flats_form_submit'),
        '#weight' => 3,
    );
    
    $form['hcs_fieldset']['reset'] = array(
        '#type' => 'link',
        '#title' => t('Reset'),
        '#href' => 'admin/payonline_hcs/configure/import',
        '#weight' => 4,
    );
    
    return $form;
}

function payonline_hcs_fill_pan_flats_form_submit($form, $form_state){
	$arg = (int)$form_state['build_info']['args'][0];
    $isAlcom = module_exists('alcom_konsalt');
    $resCnt = 0;
    $upFields = array();
    $arrTbl = array(
        'payonline_hcs_pan_flats',
        'payonline_hcs_electric_pins',
        'payonline_hcs_gas_pins'
    );
    $arrFields = array(
        array('pf_lc_fkey', 'pf_flat'),
        array('ep_lc_fkey', 'ep_pin'),
        array('gp_lc_fkey', 'gp_pin'),
    );
    $table = $arrTbl[$arg];
    $fields = $arrFields[$arg];
    //~ Need for trim fields
    foreach($fields as $val){
        $upFields[] = '`'.$val.'`=TRIM(`'.$val.'`)';
    }
    $upFields = implode(', ',$upFields);
    
    try{
		if($isAlcom and $arg == 0){
            db_truncate('{'.$table.'}')->execute();
            $resCnt = db_query('INSERT INTO {payonline_hcs_pan_flats} (`pf_lc_fkey`, `pf_flat`) SELECT `lc_fkey`, Trim(`gfk_flat`) FROM {alcom_konsalt_bill}')->rowCount();
		}
		elseif(!$isAlcom or ($isAlcom and $arg > 0)){
			$file		= '';
			$lineTerm 	= '\\r\\n';
			$encode		= check_plain($form_state['input']['pay_hcs_fileencode']);
			
			if(isset($_FILES['files']) and is_uploaded_file($_FILES['files']['tmp_name']['pay_hcs_file'])){
				db_truncate('{'.$table.'}')->execute();
                $file = $_FILES['files']['tmp_name']['pay_hcs_file'];
                $empty = false;
				$lineR = payonline_hcs_get_first_row($file,$encode,$empty);
				if(!$empty){
                    if($lineR == 0){
                        $lineTerm = '\\n';
                    }
                    $loadSql = 'LOAD DATA LOCAL INFILE :file INTO TABLE {'.$table.'} CHARACTER SET :coding FIELDS TERMINATED BY \';\' ENCLOSED BY \'"\' ESCAPED BY \'\\\\\' LINES TERMINATED BY \''.$lineTerm.'\' (`'.implode('`, `',$fields).'`)';
                    $resCnt = db_query($loadSql, array(':file'=>$file, ':coding'=>$encode), array(PDO::MYSQL_ATTR_LOCAL_INFILE => 1))->rowCount();
                    if(!empty($upFields) and !empty($resCnt)){
                        db_query('UPDATE {'.$table.'} SET '.$upFields);
                    }
                }
                else{
                    drupal_set_message(t('Handbook was not filled. Uploaded file is empty.'), 'warning'); return false;
                }
			}
		}
        if($resCnt > 0){
            drupal_set_message(t('Filling the handbook successfully. Number of rows affected: %rows.', array('%rows'=>$resCnt)));
        }
        else{
            drupal_set_message(t('Handbook was not filled.'), 'warning');
        }
	}
	catch(Exception $e){
		watchdog_exception('payonline-hcs-error', $e);
		drupal_set_message('Error when fill handbook table. More information in '.l('syslog','admin/reports/dblog').'.<br />'.check_plain($e->getMessage()), 'error', FALSE); return false;
	}
}

function payonline_hcs_get_first_row($file, $encode, &$empty=false){
	$line 	= '';
	$handle = fopen($file, 'r');
	$line 	= fgets($handle);
	
	fclose($handle);
	
	if($encode == 'utf8'){
		$line 	= iconv("windows-1251", "utf-8", $line);
	}
	$emptyLine 	= preg_replace('/^\R$/', '', $line);
    if(empty($emptyLine)){
        $empty = true;
    }
	$linePer = preg_match('/\\r/', $line);
	return (int)$linePer;
}

/**
 * Statistic page. Show active users.
 * */
function payonline_hcs_statistic_page(){
	$out = '';
	$rows = array();
	
    $countPayonline = db_select('payonline_hcs_payments');
    $countPayonline->addExpression('Count(*)', 'count');
    $countPayonline->addExpression('Sum(summ)', 'sum');
    $countPayonline = $countPayonline->execute()
    ->fetchAllAssoc('count');
    
    $countGuestPay = db_select('payonline_hcs_payments');
    $countGuestPay->addExpression('Count(*)', 'count');
    $countGuestPay->addExpression('Sum(summ)', 'sum');
    $countGuestPay = $countGuestPay->condition('uid', 0);
    $countGuestPay = $countGuestPay->execute()
    ->fetchAllAssoc('count');
    
    foreach(array_values($countPayonline) as $val){
        $rowsArr[t('Count payments')] = $val->count;
        $rowsArr[t('Sum payments')] = number_format($val->sum, 2, '.', ' ');
    }
    unset($val);
    
    foreach(array_values($countGuestPay) as $val){
        $rowsArr[t('Count payments made ​​by anonymous users')] = $val->count;
        $rowsArr[t('Sum payments made ​​by anonymous users')] = number_format($val->sum, 2, '.', ' ');
    }
    unset($val);

	foreach($rowsArr as $key=>$val){
		$rows[] = array(
			'data' => array(array('data'=>$key.':', 'style' => array('width:50%; text-align:right')), array('data'=>$val, 'class'=>array('bold'))),	
		);
	}
	
	$out = theme('table',
		array(
			'header' => array(),
			'rows'=>$rows,
			'empty' => t('No data.'),
		)
	);
	
	return $out;
}
