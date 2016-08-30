<?php

function op_custom_crew_listing_form(&$form_state) {	
	$form = array();
	

	$result = db_query("SELECT nid, title FROM {node}  WHERE type = 'supplements'");
	$supplements = array();
	while ($row = db_fetch_object($result)) {
	  $supplements[$row->nid] = $row->title;
	}

	$form['crew_listing']['supplements'] = array(
    '#title' => t('Supplements'),
    '#type' => 'checkboxes',
    '#options' => $supplements, 
    '#default_value' => isset($form_state['values']['supplements']) ? array_filter($form_state['values']['supplements']) : array(),
  );

  $form['crew_listing']['employment_type'] = array(
    '#title' => t('Employment Type'),
    '#type' => 'select',
    '#options' => array(
    	'any'				=> 'Any',
    	'Part Time' => 'Part Time',
    	'Full Time' => 'Full Time',
  	),    
  	'#default_value' => isset($form_state['values']['employment_type']) ? $form_state['values']['employment_type'] : array(),
  );  

  $form['crew_listing']['crew_status'] = array(
    '#title' => t('Crew Status'),
    '#type' => 'select',
    '#options' => array(
    	'any'	=> 'Any',
    	0 => 'Blocked',
    	1 => 'Active',
  	),    
  	'#default_value' => isset($form_state['values']['crew_status']) ? $form_state['values']['crew_status'] : array(),
  );  

  $form['crew_listing']['preview'] = array(
    '#type' => 'submit',
    '#value' => t('Preview'),    
  );
  $form['crew_listing']['generate'] = array(
    '#type' => 'submit',
    '#value' => t('Generate CSV file'),    
  );
  watchdog('name', '<pre>'.print_r($form_state['values'], TRUE).'</pre>');
  $form['crew_listing']['results'] = array(
    '#type' => 'markup',
    '#value' => op_custom_crew_listing_build_table($form, $form_state['values']),    
  );
  
	return $form;
}

function op_custom_crew_listing_form_submit(&$form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  if ($form_state['clicked_button']['#parents'][0] == 'preview') {
		//  	
	} elseif ($form_state['clicked_button']['#parents'][0] == 'generate') {
		op_custom_crew_listing_generate($form, $form_state['values']);
	}
}

function op_custom_crew_listing_build_table_header($exclude_link = FALSE) {
  $header = array();
  
  $header['username'] = t('Name');
  $header['mail'] = t('E-mail');
  $header['mobile'] = t('Mobile Number');
  $header['address'] = t('Address');
  $header['postcode'] = t('Post Code');
  $header['supplements'] = t('Skills');
  if (!$exclude_link) {
  	$header['uid'] = t('Edit link');
  }
  $header['employed'] = t('Employed');

  return $header;
}

function op_custom_crew_listing_build_table($form, $fs_values) {
	$header = op_custom_crew_listing_build_table_header();
	$rows = op_custom_crew_listing_build_rows($form, $fs_values);

	foreach ($rows as $key => $row) {
		$rows[$key]['mail'] = l($row['mail'], 'mailto:'.$row['mail']);
		$rows[$key]['username'] = l($row['username'], 'user/'.$row['uid']);
		$rows[$key]['postcode'] = l($row['postcode'], 'user/'.$row['uid']);
		$rows[$key]['uid'] = l(t('Edit'), 'user/'.$row['uid'].'/edit');
	}
	$count = sizeof($rows);
	unset($_SESSION['messages']['status']);
	drupal_set_message(format_plural($count, '1 crew found', '@count crews found'));

	$table = '<br><br>'.theme('table', $header, $rows, '');	

	return $table;
}

function op_custom_crew_listing_build_rows($form, $fs_values, $exclude_link = FALSE) {	
	$supplement_values = $form['crew_listing']['supplements']['#options'];
	$supplements 		 = array_filter($fs_values['supplements']);
	$employment_type = isset($fs_values['employment_type']) ? $fs_values['employment_type'] : 'any';
	$crew_status = isset($fs_values['crew_status']) ? $fs_values['crew_status'] : 'any';
	//
	$where_supplements = '';
	if (sizeof($supplements)) {
		$where_supplements = '';
		foreach ($supplements as $sup) {
			$where_supplements .= " AND FIND_IN_SET($sup,sp.value)";
		}
	}	
	$where_employed = "";
	if ($employment_type !== 'any') {
		$where_employed = " AND et.value = '$employment_type'";
	}
	$where_crew_status = "";
	if ($crew_status !== 'any') {
		$where_crew_status = " AND u.status = $crew_status";
	}
	$query = "SELECT u.uid, u.name AS username, u.mail, sp.value AS supplements, m.value AS mobile, ad.value AS address, pc.value AS postcode, et.value AS employed
		FROM `drupal_users` u LEFT JOIN `drupal_profile_values` sp ON u.uid = sp.uid
		LEFT JOIN `drupal_profile_values` m ON u.uid = m.uid AND m.fid = 12
		LEFT JOIN `drupal_profile_values` ad ON u.uid = ad.uid AND ad.fid = 5
		LEFT JOIN `drupal_profile_values` pc ON u.uid = pc.uid AND pc.fid = 4
		LEFT JOIN `drupal_profile_values` et ON u.uid = et.uid AND et.fid = 39
		WHERE sp.fid = 41 $where_supplements $where_employed $where_crew_status ORDER BY u.name";	
	watchdog('qq', '<pre>'.print_r($query, TRUE).'</pre>');
	$result = db_query($query);			
	$items = array();
  while ($data = db_fetch_array($result)) {  	
  	$supplements_array = array();
  	foreach (explode(',', $data['supplements']) as $id) {
  		$supplements_array[] = $supplement_values[$id];
  	}
  	$row = array();
		$row['username'] = $data['username'];
		$row['mail'] = $data['mail'];
		$row['mobile'] = $data['mobile'];
		$row['address'] = $data['address'];
		$row['postcode'] = $data['postcode'];
		$row['supplements'] = implode(' | ', $supplements_array);		
		if (!$exclude_link) {
			$row['uid'] = $data['uid'];
		}		
		$row['employed'] = $data['employed'];
		
		$items[] = $row;
  }	  

  return $items;
}

function op_custom_crew_listing_generate($form, $fs_values) {
	$file_desc = '';

	define (REPORT_DIR, 'sites/default/files/');
	define (CSV, '.csv');
	define (ZIP, '.zip');
  
	$header = op_custom_crew_listing_build_table_header(TRUE);
  $rows 	= op_custom_crew_listing_build_rows($form, $fs_values, TRUE);
  unset($header['uid']);  
 
	$fname = "crew-view" . CSV;
	$path = REPORT_DIR . $fname;
	$fp = fopen($path, 'w+');
	fputcsv($fp, $header, ';');
	foreach ($rows as $row) {
	  fputcsv($fp, $row, ';');
	}

	fclose($fp);

	header("Content-type: application/csv");
	header("Content-Disposition: attachment; filename=$fname");
	header("Pragma: no-cache");
	header("Expires: 0");
	readfile($path);

	unlink($path);
	exit();
}