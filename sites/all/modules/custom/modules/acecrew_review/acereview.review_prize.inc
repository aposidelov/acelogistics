<?php
/*
 * $type == crew | generate научиться как сабмитать форму чтоб в ней был action
 */
function acecrew_review_prize_form(&$form_state) {  
  if (isset($_GET['timesheets'])) {
    $date_start = $_GET['timesheets']['start_date']['date'];
    $date_end = $_GET['timesheets']['end_date']['date'];
  } else {
    $date_start = isset($_POST['timesheets']) ? $_POST['timesheets']['start_date']['date'] : '';
    $date_end = isset($_POST['timesheets']) ? $_POST['timesheets']['end_date']['date'] : '';
  }


  $form['timesheets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Please Select'),
    '#tree' => TRUE,
  );
  $form['timesheets']['start_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start Date'),
    '#date_format' => 'Y-m-d',
    '#default_value' => empty($date_start) ? date("Y-m-d") : $date_start,
    '#attributes' => array('id' => 'timesheets_start'),
  );
  $form['timesheets']['end_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('End Date'),
    '#date_format' => 'Y-m-d',
    '#default_value' => empty($date_end) ? date("Y-m-d") : $date_end,
    '#attributes' => array('id' => 'timesheets_end'),
  );

  $form['timesheets']['filter'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#attributes' => array('id' => 'acecrew_timesheets_submit'),
  );  
  $count_query = acecrew_review_prize_query($date_start, $date_end, TRUE);
  $count = db_result(db_query($count_query));

  $form['reviews_count'] = array('#type' => 'markup', '#value' => '<div>Reviews number: '.$count.'</div><br/>');


  $form['reviews'] = array('#type' => 'markup', '#value' => acecrew_review_prize_get_table($date_start, $date_end));


  $form['draw_prize'] = array(
    '#type' => 'submit',
    '#value' => t('Draw Prize'),
    '#attributes' => array('id' => 'acecrew_timesheets_submit'),
  );  

  return $form;
}

function acecrew_review_prize_get_header() {
  return array(
    t('Job number'),
    t('Client'),
    t('Created'),
    t('Reviewed'),    
    t('Submitted by'),
    t('Link'),    
  );  
}

function acecrew_review_prize_get_table($date_from, $date_to) {
  //drupal_set_message('$date_start = '. $date_from);
  //drupal_set_message('$date_end = '. $date_to);

  $output = '<div>';

  $header = acecrew_review_prize_get_header(); 

  $count_query = acecrew_review_prize_query($date_from, $date_to, TRUE);
  $count = db_result(db_query($count_query));
  //drupal_set_message('$query_count = '. $count);
  $query = acecrew_review_prize_query($date_from, $date_to, FALSE);

  //$result = db_query($query);
  $result = pager_query($query, 10, 0, $count_query);  
  $rows = array();
  while ($row = db_fetch_array($result)) {
    $rows[] = array(
      $row['job_number'],
      $row['client_name'],
      $row['created_date'],
      $row['reviewed_date'],          
      $row['submitted_by'],
      l('node/'.$row['review_nid'].'/edit', 'node/'.$row['review_nid'].'/edit'),
    );
  }  

  $output .= theme('table', $header, $rows, '');
  $output .= theme('pager', NULL, 10, 0);

  $output .= '</div>';

  return $output;
}

function acecrew_review_prize_query($date_from, $date_to, $count = FALSE) {
  if ($count) {
    $select = 'COUNT(*)';
  } else {
    $select = "j.field_job_number_value AS job_number, 
    c.field_client_name_value AS client_name,
    DATE_FORMAT(FROM_UNIXTIME(n.created), '%Y-%m-%%d') AS created_date,
    DATE_FORMAT(FROM_UNIXTIME(n.changed), '%Y-%m-%%d') AS reviewed_date,
    DATE_FORMAT(FROM_UNIXTIME(r.field_review_expiration_date_value), '%Y-%m-%%d') AS expiration_date,
    r.field_review_status_value AS review_status,
    r.field_review_submitted_by_value AS submitted_by,
    n.nid AS review_nid";    
  }

  $query = "SELECT $select    
  FROM {content_type_review} r 
  INNER JOIN {node} n ON r.nid = n.nid 
  INNER JOIN {content_type_job} j ON j.nid = r.field_job_id_value
  INNER JOIN {content_type_client} c ON c.field_client_id_value = j.field_job_client_name_value WHERE r.field_review_status_value = 2";

  if (!empty($date_from) && !empty($date_to)) {    
    $date_from = strtotime($date_from . ' 00:00');
    $date_to = strtotime($date_to . ' 23:59');
    $query .= " AND n.changed BETWEEN $date_from AND $date_to";
    //$query .= " AND DATE_FORMAT(FROM_UNIXTIME(r.field_review_date_value), '%Y-%m-%%d') BETWEEN '$date_from' AND '$date_to'";
  }
  $query .= " ORDER BY n.changed DESC";

  //drupal_set_message($query);

  return $query;
}

function acecrew_review_prize_form_submit(&$form, &$form_state) {
  $form_state['rebuild'] = 1;
  if ($form_state['clicked_button']['#parents'][0] == 'draw_prize') {
    
    $date_start = '';
    $date_end = '';
    if (isset($form_state['values']['timesheets'])) {
      $date_start = trim($form_state['values']['timesheets']['start_date']);
      $date_start = substr($date_start, 0, 10);
      $date_end = trim($form_state['values']['timesheets']['end_date']);
      $date_end = substr($date_end, 0, 10);

      $query = acecrew_review_prize_query($date_start, $date_end, FALSE);

      $result = db_query($query);
      
      $reviews = array();
      while ($row = db_fetch_array($result)) {
        $reviews[$row['review_nid']] = array(
          $row['job_number'],
          $row['client_name'],
          $row['created_date'],
          $row['reviewed_date'],
          $row['submitted_by'],
          l('node/'.$row['review_nid'].'/edit', 'node/'.$row['review_nid'].'/edit'),
        );
      }
             
      $random_index = array_rand($reviews);       
      $random_review_row = $reviews[$random_index];      
      $header = acecrew_review_prize_get_header();
      $table = theme('table', $header, array($random_review_row), '');

      drupal_set_message($table);    
    }
  } 
}