<?php

function op_custom_job_timezone_listing_form(&$form_state) {	
	$form = array();	

  $timezone['any'] = '<Any>';
  $timezone['Europe/London'] = 'Europe/London';
  $default_timezone = variable_get('date_default_timezone', 0);
  $timezone[$default_timezone] = $default_timezone . ' (default timezone)';
  $timezone['else'] = '<Else>';  
  $form['job_timezone_listing']['timezone'] = array(
    '#title' => t('Timezone'),
    '#type' => 'select',
    '#options' => $timezone,
    '#default_value' => isset($form_state['values']['timezone']) ? $form_state['values']['timezone'] : array('any'),
  );
  
  $form['job_timezone_listing']['date']['#prefix'] = '<div class="date-filter">';
  $form['job_timezone_listing']['date']['#suffix'] = '</div>';
  $form['job_timezone_listing']['date']['date_title'] = array('#type' => 'markup', '#value' => '<strong>'.t('Last Updated').'</strong>');
  $form['job_timezone_listing']['date']['from_date'] = array(
		'#type' => 'date_popup',
		'#date_format' => 'Y-m-d',
		'#default_value' => isset($form_state['values']['from_date']) ? $form_state['values']['from_date'] : date('Y-m-d', strtotime('-3 weeks')),
		'#title' => t('From Date'),		
	);
	$form['job_timezone_listing']['date']['to_date'] = array(
		'#type' => 'date_popup',
		'#date_format' => 'Y-m-d',
		'#default_value' => isset($form_state['values']['to_date']) ? $form_state['values']['to_date'] : date('Y-m-d'),
		'#title' => t('To Date'),
	);
  $form['job_timezone_listing']['limit'] = array(
    '#title' => t('Limit'),
    '#type' => 'textfield',        
  	'#default_value' => isset($form_state['values']['limit']) ? $form_state['values']['limit'] : 50,
  );  

  $form['job_timezone_listing']['preview'] = array(
    '#type' => 'submit',
    '#value' => t('Apply'),    
  );
    
  $form['job_timezone_listing']['results'] = array(
    '#type' => 'markup',
    '#value' => op_custom_job_timezone_listing_build_table($form, $form_state['values']),    
  );
  
	return $form;
}

function op_custom_job_timezone_listing_form_submit(&$form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  if ($form_state['clicked_button']['#parents'][0] == 'preview') {
		//  	
	} elseif ($form_state['clicked_button']['#parents'][0] == 'generate') {
		op_custom_job_timezone_listing_generate($form, $form_state['values']);
	}
}

function op_custom_job_timezone_listing_build_table_header($exclude_link = FALSE) {
  $header = array();
  
  $header['job_number'] = t('Job Number');
  $header['job_status'] = t('Job status');
  $header['venue'] = t('Venue');
  $header['date'] = t('Date');  
  $header['timezone'] = t('Timezone');
  $header['date_changed'] = t('Updated');    
  $header['client_name'] = t('Client name');
  $header['invoice_number'] = t('Invoice number');  
  $header['delete'] = t('Delete link');
  $header['edit'] = t('Edit link');
  $header['view'] = t('View');

  return $header;
}

function op_custom_job_timezone_listing_build_table($form, $fs_values) {
	$header = op_custom_job_timezone_listing_build_table_header();
	$rows = op_custom_job_timezone_listing_build_rows($form, $fs_values);
	$destination = drupal_get_destination();
	$statuses = acecrew_get_statuses(FALSE,TRUE);
	foreach ($rows as $key => $row) {
		$rows[$key]['data']['job_status'] = $statuses[$row['data']['job_status']];
		$rows[$key]['data']['date'] = date('D, d/m/Y', $row['data']['date']);
    $rows[$key]['data']['date_changed'] = date('d/m/Y H:i', $row['data']['date_changed']); 		
	}	

	$table = '<br><br>'.theme('table', $header, $rows, '');	
	$table .= theme('pager', NULL, 25, 0); //, NULL, 25, 0

	return $table;
}

function op_custom_job_timezone_listing_build_rows($form, $fs_values, $exclude_link = FALSE) {			
	$where_date = '';
	$from_date = (isset($fs_values['from_date']) && $fs_values['from_date'] !== '') ? substr($fs_values['from_date'], 0, -9) . ' 00:00' : '';
	$to_date = (isset($fs_values['to_date']) && $fs_values['to_date'] !== '') ? substr($fs_values['to_date'], 0, -9) . ' 23:59' : '';
	if (!empty($from_date) && !empty($to_date)) {
		$from_date = strtotime($from_date);
		$to_date = strtotime($to_date);
		$where_date = " AND jnode.changed BETWEEN $from_date AND $to_date";
	}

  $limit = (isset($fs_values['limit']) && $fs_values['limit'] !== '') ? ' LIMIT 0,'.$fs_values['limit'] : 'LIMIT 0,5';
	
	$query = "SELECT j.nid AS job_nid, j.field_job_number_value AS job_number, j.field_job_date_value AS date, jnode.changed, c.field_client_name_value AS client, c.nid AS client_nid, IF( c.field_credit_limit_box_value IS NULL , 0, c.field_credit_limit_box_value ) AS client_credit_exists, v.field_venue_name_value AS venue, v.nid AS venue_nid, i.invoice_number, j.field_job_po_number_value AS po_number, j.field_job_status_value AS job_status 
    FROM `drupal_content_type_job` j
    INNER JOIN `drupal_node` jnode ON j.nid = jnode.nid
		LEFT JOIN `drupal_content_type_client` c ON c.field_client_id_value = j.field_job_client_name_value
		LEFT JOIN `drupal_content_type_venue` v ON v.field_venue_id_value = j.field_job_venue_value
		LEFT JOIN `drupal_acecrew_job_invoices` i ON i.job_id = j.field_job_number_value
		WHERE 1=1 $where_date GROUP BY j.field_job_number_value ORDER BY jnode.changed DESC $limit";		
	$count_query = "SELECT COUNT(*) FROM ($query) AS count_query";
	$result = db_query($query);
  //$result = pager_query($query, 50, 0, $count_query);	
	$items = array();
  $count = 0;
  while ($data = db_fetch_array($result)) {
  	$node = node_load($data['job_nid']);    
    $row = array();
  	if ($data['job_status'] == CONFIRMED) {
  		$row['class'] = 'status_confirmed';
  	}
  	//watchdog('ttzz', '<pre>'.print_r($node, TRUE).'</pre>');
		$row['data']['job_number'] = $data['job_number'];
		$row['data']['job_status'] = $data['job_status'];
		$row['data']['venue'] = l($data['venue'], 'node/'.$data['venue_nid']);
		$row['data']['date'] = $data['date'];
    $row['data']['timezone'] = $node->field_job_date[0]['timezone'];
    $row['data']['date_changed'] = $data['changed'];    
		$row['data']['client'] = l($data['client'], 'node/'.$data['client_nid']);
		if (!$row['client_credit_exists']) {
			$row['data']['client'] = '<div class="client client-credit-warning">'. $row['data']['client'] . '</div>';
		}		
		$row['data']['invoice_number'] = $data['invoice_number'];
		$row['data']['delete'] = l(t('delele'), 'node/'.$data['job_nid'].'/delete', array('query' => $destination));
		$row['data']['edit'] = l(t('edit'), 'node/'.$data['job_nid'].'/edit', array('query' => $destination));
		$row['data']['view'] = l(t('view'), 'node/'.$data['job_nid']);
		$count++;
		$items[] = $row;
  }

  // show message with total number of filtered items
  //$count = db_result(db_query($count_query));
  unset($_SESSION['messages']['status']);
  drupal_set_message(format_plural($count, '1 job found', '@count jobs found'));
  //drupal_set_message($query);
  return $items;
}