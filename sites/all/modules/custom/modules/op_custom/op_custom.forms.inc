<?php

function op_custom_bookoff_repeat_form(&$form_state) {
  	$form = array();  	

  	jquery_ui_add('ui.core');
  	jquery_ui_add('ui.datepicker');

  	drupal_add_js(drupal_get_path('module', 'acecrew') . '/theme/datetimepicker.js');    
  	drupal_add_js(drupal_get_path('module', 'acecrew') . '/theme/jquery.blockui.js');
   	drupal_add_js(drupal_get_path('module', 'op_custom') . '/js/bookoff.js');
  
  	$form['label'] = array(
  		'#type' => 'textfield',
  		'#default_value' => 'Bookoff reason',
  		'#title' => t('Label'),
  		'#description' => t(''),
  	);
  	$form['crew_uid'] = array(
  		'#type' => 'textfield',
  		'#default_value' => 304,
  		'#title' => t('Crew uid'),
  		'#description' => t(''),
  	);
	$form['start_datetime'] = array(
		'#type' => 'textfield',
		'#default_value' => isset($form_state['values']) ? $form_state['values']['start_datetime'] : '',
		'#title' => t('Start DateTime'),    
		'#required' => TRUE,
	);
	$form['end_datetime'] = array(
		'#type' => 'textfield',
		'#default_value' => isset($form_state['values']) ? $form_state['values']['end_datetime'] : '',
		'#title' => t('End DateTime (optional)'),    
	);

	$numbers = array();
	for ($number = 0; $number<= 31; $number++) {
		$numbers[$number] = $number;
	}

	$type = array(
		'days' => t('Days'),
		'weeks' => t('Weeks'),
		'months' => t('Months'),
	);

	$form['periodicity'] = array(
		'#type' => 'fieldset',
		'#title' => t('Periodicity'),
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
	);
	$form['periodicity_number'] = array(
		'#type' => 'select',
		'#default_value' => isset($form_state['values']) ? $form_state['values']['periodicity_number'] : 1,
		'#title' => t('Number'),		
		'#options' => $numbers,				
	);
	$form['periodicity_type'] = array(
	    '#type' => 'select',
	    '#default_value' => isset($form_state['values']) ? $form_state['values']['periodicity_type'] : 'weeks',
	    '#title' => t('Type'),
	    '#description' => t(''),
	    '#options' => $type,
	);

	$form['range'] = array(
		'#type' => 'fieldset',
		'#title' => t('Range'),
		'#collapsible' => FALSE,
		'#collapsed' => FALSE,
	);
	$form['range_number'] = array(
		'#type' => 'select',
		'#default_value' => isset($form_state['values']) ? $form_state['values']['range_number'] : 1,
		'#title' => t('Number'),
		'#options' => $numbers,
	);
	$form['range_type'] = array(
	    '#type' => 'select',
	    '#default_value' => isset($form_state['values']) ? $form_state['values']['range_type'] : 'weeks',
	    '#title' => t('Type'),
	    '#description' => t(''),
	    '#options' => $type,
	);
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Add new range'),
	);
	$form['crews_overload'] = array(
		'#type' => 'submit',
		'#value' => t('Check date'),
	);

	return $form;
}

function op_custom_bookoff_repeat_form_submit($form, &$form_state) {
	//watchdog('fs', '<pre>'.print_r($form_state['clicked_button']['#parents'][0], TRUE).'</pre>');
	$form_state['rebuild'] = 1;

	if ($form_state['clicked_button']['#parents'][0] == 'submit') {	
		
		$label 				= $form_state['values']['label'];
		$crew_uid 			= $form_state['values']['crew_uid'];
		$start_date 		= $form_state['values']['start_datetime'];
		$end_date 			= $form_state['values']['end_datetime'];
		$periodicity_number = $form_state['values']['periodicity_number'];
		$periodicity_type 	= $form_state['values']['periodicity_type'];
		$range_number 		= $form_state['values']['range_number'];
		$range_type 		= $form_state['values']['range_type'];
		$timezone			= 'Europe/London';

		acecrew_add_bookoff($crew_uid, $start_date, $end_date, $label, 
			$periodicity_number, $periodicity_type, 
			$range_number, $range_type,	$timezone);

	} elseif ($form_state['clicked_button']['#parents'][0] == 'crews_overload') {
		drupal_set_message(t('over load'));
	}
}

function acecrew_bookoff_is_date_valid($date = '') {
	$output = '';
	
		

	return $output;
}

/**
 * Function convert number of input days, weeks, months to output number depending on passed parameters.
 * For example: 
 * [params: 2, 'weeks', 'days'] = 14 (days); 
 * [params: 5, 'days', 'days'] = 5 (days); 
 * [params: 3, 'months', 'weeks'] = 12 (weeks)
 * @param  [integer] $input_number [description]
 * @param  ['days', 'weeks', 'months'] [description]
 * @param  ['days', 'weeks', 'months'] [description]
 * @return [integer] [output number]
 */
function acecrew_get_date_items_by_type($input_number, $input_type, $output_type = 'days') {	
	if ($output_type == 'days') {
		if ($input_type == 'weeks') {
			return $input_number * 7;
		} elseif ($input_type == 'months') {
			return $input_number * 30;
		}
	}

	if ($output_type == 'weeks') {
		if ($input_type == 'months') {
			return $input_number * 4;
		}
	}
	
	return $input_number;
}

function acecrew_add_bookoff(
	$crew_uid, 
	$start_date, 
	$end_date, 
	$label, 
	$periodicity_number = 0, 
	$periodicity_type = '', 
	$range_number = 0, 
	$range_type = '', 
	$timezone = 'Europe/London') {

	watchdog('dd1', '<pre>'.print_r('yes', TRUE).'</pre>');

	// если задана только начальная дата то растягиваем локальный промежуток 
	// на весь текущий день вне зависимости от выбранного времени
	if ($end_date == '') {
		$date = explode(' ', $start_date);
		$start_date = $date[0] . ' 00:00';
		$end_date 	= $date[0] . ' 23:59';
	}
	
	// инициализируем начальную дату
	$start_date = date_make_date($start_date, $timezone);
	// инициализируем начальную дату
	$end_date = date_make_date($end_date, $timezone);
	// если ты единиц разные - приводим к periodicity типу
	if ($periodicity_type != $range_type) {
		$range_number = acecrew_get_date_items_by_type($range_number, $range_type, $periodicity_type);
	}
	// вычисляем количество	line item которые должны быть сгенерены
	$iterations = $periodicity_number ? floor($range_number / $periodicity_number) : 0;
	
	// if periodicity > range - don't do anything
	/*if (!$iterations) { 
		return; 
	}*/

	// cоздаем промежутки для каждого line item	
	$line_items[] = array(
		'start_date' => date_format($start_date, 'Y-m-d H:i:s'), 
		'end_date' => date_format($end_date, 'Y-m-d H:i:s'), 
		'crew_uid' => $crew_uid,
	);
	for ($i = 0; $i < $iterations; $i++) {
		date_modify($start_date, '+'.$periodicity_number.' '.$periodicity_type);
		date_modify($end_date, '+'.$periodicity_number.' '.$periodicity_type);		

		$line_items[] = array(
			'start_date' => date_format($start_date, 'Y-m-d H:i:s'), 
			'end_date' => date_format($end_date, 'Y-m-d H:i:s'), 
			'crew_uid' => $crew_uid,
		);
	}

	foreach ($line_items as $line_item) {
		// проверить существование нод с текущими параметрами		
		if (is_bookoff_exists(
			$line_item['crew_uid'], 
			$line_item['start_date'], 
			$line_item['end_date']
		)) {
			continue;
		}

		$node = new StdClass();
	    $node->title = $node->field_ub_label[0]['value'] 	= $label;
	    $node->field_ub_date_start[0]['value'] 				= $line_item['start_date'];
	    $node->field_ub_date_start[0]['value2'] 			= $line_item['start_date'];
	    $node->field_ub_date_start[0]['timezone'] 			= $timezone;	   
	    $node->field_ub_date_end[0]['value'] 				= $line_item['end_date'];
	    $node->field_ub_date_end[0]['value2'] 				= $line_item['end_date'];
	    $node->field_ub_date_end[0]['timezone'] 			= $timezone;
	    $node->field_ub_owner 								= array(0 => array('uid' => $line_item['crew_uid']));
	    $node->type 										= 'user_bookedoff';	    
	    node_save($node);		    
	}	
}

function is_bookoff_exists($crew_uid, $start_date, $end_date) {
	$is_exists = db_result(db_query("SELECT COUNT(*) 
		FROM `drupal_content_type_user_bookedoff` ub 
		WHERE ub.field_ub_owner_uid = %d AND 
		ub.field_ub_date_start_value = '%s' AND 
		ub.field_ub_date_end_value = '%s'", $crew_uid, $start_date, $end_date));

	return $is_exists;
}