<?php

function acecrew_review_crewmonth_form(&$form_state, $crew_id = '') {	
	$form = array();
	
	if (!isset($form_state['values'])) {

		$header = acecrew_review_crewmonth_get_table_header();
	    $rows 	= acecrew_review_crewmonth_get_table_rows();
	    $table 	= theme('table', $header, $rows, '');

		unset($_SESSION['messages']['status']);		
	}

	if (sizeof($messages['status']) > 1) {
    unset($messages['status'][1]);
	}
	
	//drupal_set_message('<pre>'.print_r($schema, TRUE).'</pre>');

	$form['month'] = array(
	    '#type' => 'date_popup',
	    '#title' => t('Month'),
	    '#date_format' => 'Y-m',
	    '#default_value' => isset($form_state['values']) ? $form_state['values']['month'] : date("Y-m"),
	    '#attributes' => array('id' => 'timesheets_start'),
	    '#suffix' => '<br>',
	);
	$form['timesheets']['preview'] = array(
	    '#type' => 'submit',
	    '#value' => t('Preview'),
	    '#attributes' => array('id' => 'acecrew_timesheets_submit'),
	);
  	$form['timesheets']['generate'] = array(
		'#type' => 'submit',
		'#value' => t('Generate CSV file'),
		'#attributes' => array('id' => 'acecrew_timesheets_submit'),
  	);

  	return $form;
}

function acecrew_review_crewmonth_form_submit($form, &$form_state) {	
	$form_state['rebuild'] = 1;
	$date = $form_state['values']['month'];

	$first_date = date("Y-m-01", strtotime($date));
	$last_date = date("Y-m-t", strtotime($date));

	if ($form_state['clicked_button']['#parents'][0] == 'preview') {		
		//drupal_set_message('preview: first :' . $first_date);
		//drupal_set_message('preview: last :' . $last_date);

		$header = acecrew_review_crewmonth_get_table_header();
	    $rows 	= acecrew_review_crewmonth_get_table_rows($first_date, $last_date);		

		$table = theme('table', $header, $rows, '');
		unset($_SESSION['messages']['status']);
		drupal_set_message($table, 'status', FALSE);

	} elseif ($form_state['clicked_button']['#parents'][0] == 'generate') {
		//drupal_set_message('generate: first :' . $first_date);
		//drupal_set_message('generate: last :' . $last_date);

		acecrew_review_crewmonth_report_generate($first_date, $last_date);
	    unset($_SESSION['messages']['status']);
	}	
}

function acecrew_review_crewmonth_report_generate($first_date = '', $last_date = '') {
	$file_desc = '';

	define (REPORT_DIR, 'sites/default/files/');
	define (CSV, '.csv');
	define (ZIP, '.zip');
  
  	$header = acecrew_review_crewmonth_get_table_header();
    $rows 	= acecrew_review_crewmonth_get_rows($first_date, $last_date);
 
	$fname = "Acecrew-crewmonth-review-(" . substr($last_date, 0, 7) . ")" . CSV;
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

function acecrew_review_crewmonth_get_table_header() {
  $header = array();
  $header[] = t('Crew Member');
  //$header[] = t('Timekeeping');  
  $header[] = t('Reviewed (count)');
  $header[] = t('Late (count)');  
  $header[] = t('Work Ethic');
  $header[] = t('Work Ability');
  $header[] = t('Manner');
  $header[] = t('Communication Skills');  
  $header[] = t('Average');
  //$header[] = t('Average upd');

  return $header;
}

function acecrew_review_crewmonth_get_table_rows($date_from = '', $date_to = '') {
  $rows = array();

  $data = acecrew_review_crewmonth_get_rows($date_from, $date_to);

  foreach ($data as $row) {
    $rows[] =
    array('data' => array(
      $row['crew_name'],            
      $row['reviewed_count'],
      $row['late_count'],      
      $row['work_ethic'],
      $row['work_ability'],
      $row['manner'],
      $row['com_skills'],
      //$row['average'],
      $row['average_upd'],      
      ),
    );
  }

  return $rows;
}

function acecrew_review_crewmonth_get_rows($date_from = '', $date_to = '') {  
  	$sql = "SELECT u.name AS crew_name, 
  	SUM( IF( ur.field_user_review_time_keeping_value =1, 1, 0 ) ) AS late_count, 
  	COUNT(*) AS reviewed_count,
	ur.field_user_review_time_keeping_value AS time_keeping, 
	AVG(IF(ur.field_user_review_work_ethic_value=0, NULL, ur.field_user_review_work_ethic_value)) AS work_ethic, 
	AVG(IF(ur.field_user_review_work_ability_value=0, NULL, ur.field_user_review_work_ability_value)) AS work_ability, 
	AVG(IF(ur.field_user_review_manner_value=0, NULL, ur.field_user_review_manner_value)) AS manner, 
	AVG(IF(ur.field_user_review_com_skills_value=0, NULL, ur.field_user_review_com_skills_value)) AS com_skills,
	(
	IFNULL(AVG(IF(ur.field_user_review_work_ethic_value=0, NULL, ur.field_user_review_work_ethic_value)),0) +
	IFNULL(AVG(IF(ur.field_user_review_work_ability_value=0, NULL, ur.field_user_review_work_ability_value)),0) +
	IFNULL(AVG(IF(ur.field_user_review_com_skills_value=0, NULL, ur.field_user_review_com_skills_value)),0) + 
	IFNULL(AVG(IF(ur.field_user_review_com_skills_value=0, NULL, ur.field_user_review_com_skills_value)),0)
	) AS average
	FROM `drupal_content_type_user_review` ur 
	INNER JOIN `drupal_content_type_review` r ON ur.field_related_review_id_value = r.nid 
	INNER JOIN `drupal_users` u ON ur.field_user_review_user_id_value = u.uid 
	INNER JOIN `drupal_content_type_job` j ON r.field_job_id_value = j.nid
	WHERE j.field_job_date_value BETWEEN UNIX_TIMESTAMP('%s') AND UNIX_TIMESTAMP('%s')
	GROUP BY u.uid
	ORDER BY average DESC";
	
	$result = db_query($sql, $date_from, $date_to);
	//$result = db_query($sql, '2013-01-31', '2015-01-31');

  	$i=0;
  	$rows = array();
  	while ($row = db_fetch_array($result)) {
	    $average_i = 0;
	    if ($row['manner'] > 0) {      
	    	++$average_i;
	    }
	    if ($row['work_ethic'] > 0) {      
	    	++$average_i;
	    }
	    if ($row['work_ability'] > 0) {      
	    	++$average_i;
	    }
	    if ($row['com_skills'] > 0) {      
	    	++$average_i;
	    }

	    $average = ($row['manner'] + $row['work_ethic'] + $row['work_ability'] + $row['com_skills'])/$average_i;

	    $rows[$i]['crew_name']    		= $row['crew_name'];
	    $rows[$i]['late_count']    		= $row['late_count'];
	    $rows[$i]['reviewed_count']    	= $row['reviewed_count'];	    
	    //$rows[$i]['time_keeping']      	= $row['time_keeping'] ? $row['time_keeping'] : t('No Opinion');
	    $rows[$i]['work_ethic']       	= $row['manner'] ? $row['manner'] : t('No Opinion');
	    $rows[$i]['work_ability']   	= $row['work_ethic'] ? $row['work_ethic'] : t('No Opinion');
	    $rows[$i]['manner'] 			= $row['work_ability'] ? $row['work_ability'] : t('No Opinion');
	    $rows[$i]['com_skills']   		= $row['com_skills'] ? $row['com_skills'] : t('No Opinion');
	    //$rows[$i]['average']      		= $row['average'] ? $row['average'] : t('No Opinion');
	    $rows[$i]['average_upd']      	= $average;
	    $i++;
	}

  return $rows;
}