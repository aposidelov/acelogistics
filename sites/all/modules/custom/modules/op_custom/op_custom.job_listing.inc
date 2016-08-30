<?php

function op_custom_job_listing_form(&$form_state) {	
	$form = array();
	// get all venues
	$result = db_query("SELECT field_venue_id_value AS id, field_venue_name_value	AS name FROM {content_type_venue} ORDER BY field_venue_name_value");	
	$venues = array();
	$venues['any'] = '<Any>';
	while ($row = db_fetch_object($result)) {
	  $venues[$row->id] = $row->name;
	}
	// get all clients
	$result = db_query("SELECT field_client_id_value AS id, field_client_name_value	AS name FROM {content_type_client} ORDER BY field_client_name_value");	
	$clients = array();
	$clients['any'] = '<Any>';
	while ($row = db_fetch_object($result)) {
	  $clients[$row->id] = $row->name;
	}

  $form['job_listing']['job_number'] = array(
    '#title' => t('Job Number'),
    '#type' => 'textfield',        
  	'#default_value' => isset($form_state['values']['job_number']) ? $form_state['values']['job_number'] : array(),
  );

  $statuses['any'] = '<Any>';
  $statuses += acecrew_get_statuses(FALSE,TRUE);
  $form['job_listing']['job_status'] = array(
    '#title' => t('Job Status'),
    '#type' => 'select',
    '#options' => $statuses,    
  	'#default_value' => isset($form_state['values']['job_status']) ? $form_state['values']['job_status'] : array(),
  );
  $form['job_listing']['venue'] = array(
    '#title' => t('Venue'),
    '#type' => 'select',
    '#options' => $venues,    
  	'#default_value' => isset($form_state['values']['venue']) ? $form_state['values']['venue'] : array(),
  );  
  $form['job_listing']['client'] = array(
    '#title' => t('Client'),
    '#type' => 'select',
    '#options' => $clients,    
  	'#default_value' => isset($form_state['values']['client']) ? $form_state['values']['client'] : array(),
  );
  $form['job_listing']['date']['#prefix'] = '<div class="date-filter">';
  $form['job_listing']['date']['#suffix'] = '</div>';
  $form['job_listing']['date']['date_title'] = array('#type' => 'markup', '#value' => '<strong>'.t('Date').'</strong>');
  $form['job_listing']['date']['from_date'] = array(
		'#type' => 'date_popup',
		'#date_format' => 'Y-m-d',
		'#default_value' => isset($form_state['values']['from_date']) ? $form_state['values']['from_date'] : '',
		'#title' => t('From Date'),		
	);
	$form['job_listing']['date']['to_date'] = array(
		'#type' => 'date_popup',
		'#date_format' => 'Y-m-d',
		'#default_value' => isset($form_state['values']['to_date']) ? $form_state['values']['to_date'] : '',
		'#title' => t('To Date'),
	);
  $form['job_listing']['po_number'] = array(
    '#title' => t('PO Number'),
    '#type' => 'textfield',        
  	'#default_value' => isset($form_state['values']['po_number']) ? $form_state['values']['po_number'] : array(),
  );
  $form['job_listing']['invoice_number'] = array(
    '#title' => t('Invoice number'),
    '#type' => 'textfield',        
  	'#default_value' => isset($form_state['values']['invoice_number']) ? $form_state['values']['invoice_number'] : array(),
  );

  $form['job_listing']['preview'] = array(
    '#type' => 'submit',
    '#value' => t('Apply'),    
  );
    
  $form['job_listing']['results'] = array(
    '#type' => 'markup',
    '#value' => op_custom_job_listing_build_table($form, $form_state['values']),    
  );
  
	return $form;
}

function op_custom_job_listing_form_submit(&$form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  if ($form_state['clicked_button']['#parents'][0] == 'preview') {
		//  	
	} elseif ($form_state['clicked_button']['#parents'][0] == 'generate') {
		op_custom_job_listing_generate($form, $form_state['values']);
	}
}

function op_custom_job_listing_build_table_header($exclude_link = FALSE) {
  $header = array();
  
  $header['job_number'] = t('Job Number');
  $header['job_status'] = t('Job status');
  $header['venue'] = t('Venue');
  $header['date'] = t('Date');
  $header['client_name'] = t('Client name');
  $header['invoice_number'] = t('Invoice number');  
  $header['delete'] = t('Delete link');
  $header['edit'] = t('Edit link');
  $header['view'] = t('View');

  return $header;
}

function op_custom_job_listing_build_table($form, $fs_values) {
	$header = op_custom_job_listing_build_table_header();
	$rows = op_custom_job_listing_build_rows($form, $fs_values);
	$destination = drupal_get_destination();
	$statuses = acecrew_get_statuses(FALSE,TRUE);
	foreach ($rows as $key => $row) {
		$rows[$key]['data']['job_status'] = $statuses[$row['data']['job_status']];
		$rows[$key]['data']['date'] = date('D, d/m/Y', $row['data']['date']);		
	}	

	$table = '<br><br>'.theme('table', $header, $rows, '');	
	$table .= theme('pager', NULL, 25, 0); //, NULL, 25, 0

	return $table;
}

function op_custom_job_listing_build_rows($form, $fs_values, $exclude_link = FALSE) {	
	$where_job_number = (isset($fs_values['job_number']) && $fs_values['job_number'] !== '') ? " AND j.field_job_number_value = '".$fs_values['job_number']."'" : '';	
	$where_job_status = (isset($fs_values['job_status']) && $fs_values['job_status'] !== 'any') ? " AND j.field_job_status_value = ".$fs_values['job_status'] : '';	
	$where_venue = (isset($fs_values['venue']) && $fs_values['venue'] !== 'any') ? " AND j.field_job_venue_value = ".$fs_values['venue'] : '';	
	$where_client = (isset($fs_values['client']) && $fs_values['client'] !== 'any') ? " AND j.field_job_client_name_value = ".$fs_values['client'] : '';	
	$where_date = '';
	$from_date = (isset($fs_values['from_date']) && $fs_values['from_date'] !== '') ? substr($fs_values['from_date'], 0, -9) . ' 00:00' : '';
	$to_date = (isset($fs_values['to_date']) && $fs_values['to_date'] !== '') ? substr($fs_values['to_date'], 0, -9) . ' 23:59' : '';
	if (!empty($from_date) && !empty($to_date)) {
		$from_date = strtotime($from_date);
		$to_date = strtotime($to_date);
		$where_date = " AND UNIX_TIMESTAMP(js.field_job_session_date_time_value) BETWEEN $from_date AND $to_date";
	}
	$where_po_number = (isset($fs_values['po_number']) && $fs_values['po_number'] !== '') ? " AND j.field_job_po_number_value = '".$fs_values['po_number']."'" : '';
	$where_invoice_number = (isset($fs_values['invoice_number']) && $fs_values['invoice_number'] !== '') ? " AND i.invoice_number = '".$fs_values['invoice_number']."'" : '';	
	
	$query = "SELECT j.nid AS job_nid, j.field_job_number_value AS job_number, j.field_job_date_value AS date, c.field_client_name_value AS client, c.nid AS client_nid, IF( c.field_credit_limit_box_value IS NULL , 0, c.field_credit_limit_box_value ) AS client_credit_exists, v.field_venue_name_value AS venue, v.nid AS venue_nid, i.invoice_number, j.field_job_po_number_value AS po_number, j.field_job_status_value AS job_status FROM `drupal_content_type_job` j
		LEFT JOIN `drupal_content_type_client` c ON c.field_client_id_value = j.field_job_client_name_value
		LEFT JOIN `drupal_content_type_venue` v ON v.field_venue_id_value = j.field_job_venue_value
		LEFT JOIN `drupal_acecrew_job_invoices` i ON i.job_id = j.field_job_number_value
		LEFT JOIN `drupal_content_type_job_session` js ON js.field_session_job_nid_value = j.nid
		WHERE 1=1 $where_job_number $where_job_status $where_po_number $where_venue $where_client $where_invoice_number $where_date GROUP BY j.field_job_number_value ORDER BY j.field_job_number_value";	
	
	$count_query = "SELECT COUNT(*) FROM ($query) AS count_query";
	$result = pager_query($query, 25, 0, $count_query);		

	// show message with total number of filtered items
	$count = db_result(db_query($count_query));
	unset($_SESSION['messages']['status']);
	drupal_set_message(format_plural($count, '1 job found', '@count jobs found'));

	$items = array();
  $statuses = acecrew_get_statuses(FALSE,TRUE);
  while ($data = db_fetch_array($result)) {  	  	
  	$row = array();
  	if ($data['job_status'] == CONFIRMED) {
  		$row['class'] = 'status_confirmed';	
  	}
  	
		$row['data']['job_number'] = $data['job_number'];		
		$row['data']['job_status'] = $data['job_status'];
		$row['data']['venue'] = l($data['venue'], 'node/'.$data['venue_nid']);		
		$row['data']['date'] = $data['date'];
		$row['data']['client'] = l($data['client'], 'node/'.$data['client_nid']);
		if (!$row['client_credit_exists']) {
			$row['data']['client'] = '<div class="client client-credit-warning">'. $row['data']['client'] . '</div>';
		}		
		$row['data']['invoice_number'] = $data['invoice_number'];		
		$row['data']['delete'] = l(t('delele'), 'node/'.$data['job_nid'].'/delete', array('query' => $destination));
		$row['data']['edit'] = l(t('edit'), 'node/'.$data['job_nid'].'/edit', array('query' => $destination));
		$row['data']['view'] = l(t('view'), 'node/'.$data['job_nid']);
		
		$items[] = $row;
  }	  

  return $items;
}