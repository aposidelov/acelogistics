<?php

function acecrew_report_noshows_form(&$form_state) {

  drupal_add_js(drupal_get_path('module', 'acereport') . '/acereport-noshows.js');
  
  if (!isset($form_state['values'])) {    
    $header = acecrew_report_noshows_get_table_header();
    $rows = acecrew_report_noshows_get_table_rows();
    $table = theme('table', $header, $rows, '');
    unset($_SESSION['messages']['status']);
    drupal_set_message($table, 'status', FALSE);
  }

  if (sizeof($messages['status']) > 1) {
    unset($messages['status'][1]);
  }

  $form['timesheets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Please Select'),
    '#tree' => TRUE,
  );
  $form['timesheets']['filter_by_date'] = array(
    '#type' => 'checkbox',
    '#title' => t('Filter by date'),
    '#default_value' => isset($form_state['values']) ? $form_state['values']['timesheets']['filter_by_date'] : 0,
    '#suffix' => '<br>',
  );
  $form['timesheets']['start_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start Date'),
    '#date_format' => 'Y-m-d',
    '#default_value' => isset($_POST['timesheets']) ? $_POST['timesheets']['start_date']['date'] : date("Y-m-d"),
    '#attributes' => array('id' => 'timesheets_start'),
  );
  $form['timesheets']['end_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('End Date'),
    '#date_format' => 'Y-m-d',
    '#default_value' => isset($_POST['timesheets']) ? $_POST['timesheets']['end_date']['date'] : date("Y-m-d"),
    '#attributes' => array('id' => 'timesheets_end'),
  );  
  $form['timesheets']['preview'] = array(
    '#type' => 'submit',
    '#value' => t('Preview'),
    '#attributes' => array('id' => 'acecrew_report_noshows_form_submit'),
  );
  $form['timesheets']['generate'] = array(
    '#type' => 'submit',
    '#value' => t('Generate CSV file'),
    '#attributes' => array('id' => 'acecrew_report_noshows_form_submit'),
  );

  return $form;
}

function acecrew_report_noshows_form_submit(&$form, &$form_state) {
  if ($form_state['clicked_button']['#parents'][1] == 'preview') {
    // to save the state in form.. it should be rebuilt
    $form_state['rebuild'] = 1;
    $filter_by_date = $form_state['values']['timesheets']['filter_by_date'];
    $date_from      = $_POST['timesheets']['start_date']['date'];
    $date_to        = $_POST['timesheets']['end_date']['date'];    

    $rows   = array();
    // One Crew Type Report    
    $header = acecrew_report_noshows_get_table_header();
    if ($filter_by_date) {
      $rows = acecrew_report_noshows_get_table_rows($date_from, $date_to);
    } else {
      $rows = acecrew_report_noshows_get_table_rows();
    }
        
    
    $table = theme('table', $header, $rows, '');
    unset($_SESSION['messages']['status']);
    drupal_set_message($table, 'status', FALSE);

  } elseif ($form_state['clicked_button']['#parents'][1] == 'generate') {
    $filter_by_date = $form_state['values']['timesheets']['filter_by_date'];
    $date_from      = $filter_by_date ? $_POST['timesheets']['start_date']['date'] : '';
    $date_to        = $filter_by_date ? $_POST['timesheets']['end_date']['date'] : '';
    
    acecrew_report_noshows_generate($date_from, $date_to);
    unset($_SESSION['messages']['status']);
  }
}

function acecrew_report_noshows_get_table_header() {
  $header = array();
  $header[] = t('Date');
  $header[] = t('Crew Name');
  $header[] = t('Call Number');  
  $header[] = t('No Show');
  $header[] = t('Description');  

  return $header;
}

function acecrew_report_noshows_get_table_rows($date_from = '', $date_to = '') {
  $rows = array();

  $data = acecrew_report_noshows_get_rows($date_from, $date_to);

  foreach ($data as $row) {
    $rows[] = array(
      'data' => array(
        $row['date'],
        $row['crew_name'],
        $row['call_number'],
        $row['no_show'],
        $row['no_show_desc'],
      ),
    );
  }

  return $rows;
}

function acecrew_report_noshows_get_rows($date_from = '', $date_to = '') {    
  // cc.no_show
  $date_where = '';
  if (!empty($date_from) && !empty($date_to)) {
    $date_where = " AND js.field_job_session_date_time_value BETWEEN '%s' AND '%s' ";
  }

  $sql = "SELECT  
    js.field_job_session_date_time_value AS date, 
    c.name AS crew_name,
    js.field_session_callid_value AS call_number,
    cc.no_show,
    cc.no_show_desc 
    FROM `drupal_crew_call` cc
    INNER JOIN `drupal_content_type_job_session` js ON cc.jsid = js.vid
    INNER JOIN `drupal_users` c ON c.uid = cc.uid
    WHERE cc.no_show <> 0 $date_where
    ORDER BY js.field_job_session_date_time_value";

  if (!empty($date_from) && !empty($date_to)) {    
    $result = db_query($sql, $date_from, $date_to);
  } else {
    $result = db_query($sql);
  }
    
  $rows = array();
  while ($row = db_fetch_array($result)) {    
    $row['date'] = substr($row['date'], 0, -3);
    $rows[] = $row;
  }

  return $rows;
}

function acecrew_report_noshows_generate($date_from, $date_to) {  
  define (REPORT_DIR, 'sites/default/files/');
  define (CSV, '.csv');
  define (ZIP, '.zip');

  $header = acecrew_report_noshows_get_table_header();
  $rows   = acecrew_report_noshows_get_rows($date_from, $date_to);
  
  $fname = "Acecrew-noshows" . CSV;
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