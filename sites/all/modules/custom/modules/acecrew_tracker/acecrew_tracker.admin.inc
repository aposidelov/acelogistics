<?php

function acecrew_tracker_log_form($form_state) {
	drupal_add_js(drupal_get_path('module', 'acecrew_tracker') . '/acecrew_tracker.js');

	$form = array();

	$admins = getAdmins();
	
	$form['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#default_value' => isset($form_state['values']) ? $form_state['values']['type'] : '',
    '#options' => acecrew_tracker_log_types(),       
  );
  $form['admins'] = array(
    '#type' => 'select',
    '#title' => t('Admins'),
    '#default_value' => isset($form_state['values']) ? $form_state['values']['admins'] : '',
    '#options' => $admins,
    '#multiple' => true,
    '#attributes' => array('size' => 2),
  );
  $form['filter_by_date'] = array(
    '#type' => 'checkbox',
    '#title' => t('Filter by date'),
    '#default_value' => isset($form_state['values']) ? $form_state['values']['filter_by_date'] : 0,
  );
  $form['start_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start Date'),
    '#date_format' => 'Y-m-d',
    '#default_value' => isset($_POST['start_date']) ? $_POST['start_date']['date'] : date("Y-m-d"),
    '#attributes' => array('id' => 'timesheets_start'),
  );
  $form['end_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('End Date'),
    '#date_format' => 'Y-m-d',
    '#default_value' => isset($_POST['end_date']) ? $_POST['end_date']['date'] : date("Y-m-d"),
    '#attributes' => array('id' => 'timesheets_end'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),    
  );

  $filter_by_date = $form_state['values']['filter_by_date'];
  $type = $form_state['values']['type'];
  $admin_ids = $form_state['values']['admins'];
  $date_from = '';
  $date_to = '';
  if ($filter_by_date) {
	  $date_from = isset($_POST['start_date']) ? $_POST['start_date']['date'] : '';
	  $date_to = isset($_POST['end_date']) ? $_POST['end_date']['date'] : '';
	}
  $header = acecrew_tracker_get_logs_header();
  $rows = acecrew_tracker_get_logs_rows($type, $admin_ids, $date_from, $date_to);
  
  if (sizeof($rows)) {
  	$table = theme('table', $header, $rows);
  } else {
  	$table = 'No log activity has been found by this request';
  }

  $form['table'] = array(    
  	'#prefix' => '<div class="logs">',
    '#value' => $table . theme('pager'),
    '#suffix' => '</div>',
  );
		

	return $form;
}

function acecrew_tracker_get_logs_header() {
	return array(
		'Type',		
		'Message',		
		'Date',
		'Admin',
		'Link',
	);
}

function acecrew_tracker_get_logs_rows($type, $admin_ids, $date_from = '', $date_to = '') {
	$count = 15;
	$date_from = str_replace('-', '', $date_from);
	$date_to = str_replace('-', '', $date_to);
	$admin_ids = implode(',' , $admin_ids);
	$where = '';	

  if (!empty($date_from) && !empty($date_to)) {
    $where .= " AND DATE_FORMAT(FROM_UNIXTIME(l.created), '%Y%m%%d') BETWEEN $date_from AND $date_to";
  }

  if (!empty($admin_ids)) {
  	$where .= " AND l.uid IN ('$crew_ids')";
  }

  if (!empty($type)) {
  	$where .= " AND l.type IN ('$type')";
  }

  $sql = "SELECT l.uid, u.name AS username, l.message, l.type, l.item1_id, l.field_name,
      DATE_FORMAT(FROM_UNIXTIME(l.created), '%Y-%m-%%d %H:%i') AS date      
    FROM `drupal_acecrew_tracker_log` l
    INNER JOIN `drupal_users` u ON l.uid = u.uid    
    WHERE l.uid > 0 $where    
    ORDER BY date DESC";  
  $result = pager_query($sql, $count);

  $i=0;
  $rows = array();
  while ($row = db_fetch_object($result)) {
  	$link = l('view', 'node/'.$row->item1_id);
  	if ($row->type == 'profile') {
  		$link = l('view', 'user/'.$row->item1_id);
  	} 
  	$types = acecrew_tracker_log_types();
  	$rows[] = array(
  		'type' => $types[$row->type],
  		'message' => $row->message,  		
  		'date' => $row->date,
  		'username' => l($row->username, 'user/'.$row->uid),
  		'link' => $link,
		);
  }

  return $rows;
}

function acecrew_tracker_log_form_submit(&$form, &$form_state) {
	if ($form_state['clicked_button']['#parents'][0] == 'submit') {
    // to save the state in form.. it should be rebuilt
    $form_state['rebuild'] = 1;
  }
}

function acecrew_tracker_log_types() {	
	return array(
  	'' => '- Any -',
  	'job' => 'Job',
  	'call' => 'Call',
  	'client' => 'Client',
  	'venue' => 'Venue',
  	'profile' => 'Crew',
  	'bookoff' => 'Bookoff',
  	'supplement' => 'Supplements',
	);
}