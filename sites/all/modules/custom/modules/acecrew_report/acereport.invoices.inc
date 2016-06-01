<?php

function acecrew_report_invoices_form(&$form_state) {  
  $day_in_sec = 3386400;
  $date_start_sec = time() - ($day_in_sec * 7);
  if (isset($_GET['timesheets'])) {
    $date_start = $_GET['timesheets']['start_date']['date'];
    $date_end = $_GET['timesheets']['end_date']['date'];
  } else {
    $date_start = isset($_POST['timesheets']) ? $_POST['timesheets']['start_date']['date'] : date("Y-m-d", $date_start_sec);    
    $date_end = isset($_POST['timesheets']) ? $_POST['timesheets']['end_date']['date'] : date("Y-m-d");
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
    '#default_value' => empty($date_start) ? date("Y-m-d", $date_start_sec) : $date_start,
    '#attributes' => array('id' => 'timesheets_start'),
  );
  $form['timesheets']['end_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('End Date'),
    '#date_format' => 'Y-m-d',
    '#default_value' => empty($date_end) ? date("Y-m-d") : $date_end,
    '#attributes' => array('id' => 'timesheets_end'),
    '#suffix' => '<br/>',
  );

  $form['timesheets']['filter'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
    '#attributes' => array('id' => 'acecrew_timesheets_submit'),
  );  
  $form['timesheets']['generate'] = array(
    '#type' => 'submit',
    '#value' => t('Generate CSV'),
    '#attributes' => array('id' => 'acecrew_timesheets_submit'),
  ); 
  
  //watchdog('ds', '<pre>'.print_r($date_start, TRUE).'</pre>');
  //watchdog('de', '<pre>'.print_r($date_end, TRUE).'</pre>');
  $count_query = acecrew_report_invoice_query($date_start, $date_end, TRUE);
  $count = db_result(db_query($count_query));

  $form['sales_invoice_count'] = array('#type' => 'markup', '#value' => '<div>Sales invoices number: '.$count.'</div><br/>');

  $form['sales_invoice'] = array('#type' => 'markup', '#value' => acecrew_report_invoice_get_table($date_start, $date_end));

  return $form;
}

function acecrew_report_invoice_get_header() {
  return array(
    t('Customer Name'),
    t('Customer ID code'),
    t('Purchase Order Number'),
    t('Job Number'),    
    t('Sales Invoice Number'),
    t('Date of Invoice'),
    t('Venue'),
    t('Subtotal excluding VAT'),
    t('VAT 20%'),
    t('TOTAL'),    
  );  
}

function acecrew_report_invoice_get_table($date_from, $date_to) {
  $output = '<div>';

  $header = acecrew_report_invoice_get_header(); 
  
  $rows = acecrew_report_invoice_get_rows($date_from, $date_to);   

  $output .= theme('table', $header, $rows, '');  

  $output .= '</div>';

  return $output;
}

function acecrew_report_invoice_get_rows($date_from, $date_to) {
  $query = acecrew_report_invoice_query($date_from, $date_to, FALSE);

  $result = db_query($query);
  //$result = pager_query($query, 10, 0, $count_query);  
  $rows = array();
  
  while ($row = db_fetch_object($result)) {  

    $sum = acecrew_get_invoice_sum($row);


    $vat = round(getVAT() * $sum / 100, 2); 

    $rows[] = array(
      $row->customer_name,
      $row->customer_id,
      $row->po_number,
      $row->job_number,
      $row->invoice_number,
      $row->invoice_date,
      $row->venue_name,
      sprintf("%01.2f", acecrew_cancellation_price($sum, 'excluding_vat')),
      sprintf("%01.2f", acecrew_cancellation_price($vat, 'vat')),
      sprintf("%01.2f", acecrew_cancellation_price($sum + $vat, 'including_vat')),
    );
  }

  return $rows; 
}

function acecrew_report_invoice_query($date_from, $date_to, $count = FALSE) {
  if ($count) {
    $select = 'COUNT(*)';
  } else {    
    $select = "j.field_job_number_value AS job_number, 
    c.field_client_name_value AS customer_name,
    c.field_client_id_value AS customer_id,
    c.field_client_rate_value,
    c.field_2_hour_default_value,
    c.field_3_hour_default_value,    
    i.invoice_number,
    DATE_FORMAT(FROM_UNIXTIME(i.created), '%Y-%m-%%d') AS invoice_date,   
    v.field_venue_name_value AS venue_name, 
    j.nid AS job_nid,
    j.vid AS vid,
    j.field_client_2h_default_value,
    j.field_client_2h_default_value,
    cs.field_cancellation_status_value AS cancellation_status,
    j.field_job_discount_value,
    j.field_job_po_number_value AS po_number";
  }

  $query = "SELECT $select    
  FROM {acecrew_job_invoices} i  
  INNER JOIN {content_type_job} j ON i.job_id = j.field_job_number_value
  INNER JOIN {content_type_client} c ON c.field_client_id_value = j.field_job_client_name_value 
  INNER JOIN {content_type_venue} v ON v.field_venue_id_value = j.field_job_venue_value
  LEFT JOIN {content_field_cancellation_status} cs ON j.nid = cs.nid";

  if (!empty($date_from) && !empty($date_to)) {    
    $date_from = strtotime($date_from . ' 00:00');
    $date_to = strtotime($date_to . ' 23:59');
    $query .= " WHERE i.created BETWEEN $date_from AND $date_to";
  }
  $query .= " ORDER BY i.created ASC";

  return $query;
}

function acecrew_report_invoices_form_submit(&$form, &$form_state) {
  $form_state['rebuild'] = 1;
  if ($form_state['clicked_button']['#parents'][1] == 'generate') {   
    $date_from      = $_POST['timesheets']['start_date']['date'];
    $date_to        = $_POST['timesheets']['end_date']['date'];
    
    acecrew_report_invoices_generate($date_from, $date_to);
    unset($_SESSION['messages']['status']);
  }
}

function acecrew_report_invoices_generate($date_from, $date_to) {  
  define (REPORT_DIR, 'sites/default/files/');
  define (CSV, '.csv');
  define (ZIP, '.zip');

  $header = acecrew_report_invoice_get_header();
  $rows   = acecrew_report_invoice_get_rows($date_from, $date_to);
  
  $fname = "Sales-invoice-". date('Y-m-d') . CSV;
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

/**
 * use $row object as $job and $client (contain gathered 
 * fields from custom SQL query)
 */
function acecrew_get_invoice_sum($row) {
  $callings = _get_callings_for_invoice_by_job($row);
  $sum = 0;
  foreach ($callings as $data) {
    $call_amount = 0;
    $call = $data['data'];
    // get call data from crew call table
    $call_data = _get_call_data($call);

    if (acecrew_is_cancellation_notice($call->cancellation_status) ||
        acecrew_is_cancellation_notice($row->cancellation_status)) {
      $number_of_standard_crews = $call->field_job_session_crew_value;
    } else {
      $number_of_standard_crews = count($call_data);          
    } 

    $quoted_amount = _get_call_client_charge_amount($row, $row, $call);
    $additional_hours = 0;
    $additional_charge = 0;
    $supplements = array();
    $total_adjust_add = 0;
    $total_adjust_reduce = 0;

    foreach ($call_data as $dat) {
      $additional_hours += $dat->additional_hours;
      $additional_charge += $dat->additional_charge;
      // total adjusted add
      $total_adjust_add += $dat->client_total_add;
      // total adjusted reduce
      $total_adjust_reduce += $dat->client_total_reduce;
      // supplements data
      $uid = $dat->uid;
      $jsid = $dat->jsid;
      $query = "SELECT * FROM {crew_js_supplement} WHERE uid=$uid AND jsid=$jsid";
      $supll_result = db_query($query);
      while ($supll_row = db_fetch_object($supll_result)) {
        $supp = node_load($supll_row->supplement_id);
        $supplements[$supll_row->supplement_id]['title'] = $supp->title;
        $supplements[$supll_row->supplement_id]['quantity']++;          
        if ($supll_row->client_ph != NULL) {
          $supplements[$supll_row->supplement_id]['amount'] += $supll_row->client_ph * ($call->field_job_session_hours_value + $dat->additional_hours);
          $call_amount += $supll_row->client_ph * ($call->field_job_session_hours_value + $dat->additional_hours);
        } else {
          $supplements[$supll_row->supplement_id]['amount'] += $supll_row->client_of;
          $call_amount += $supll_row->client_of;
        }
        //$call_amount += $supplements[$row->supplement_id]['amount'];
      }
    }
    // add additional charge
    $inc = 1;
    if ($additional_charge > 0) {
      $call_amount += $additional_charge;
      $inc++;
    }
    $client_rate = $call->field_job_session_client_rate_value == NULL ? 1 : $call->field_job_session_client_rate_value;
    // call amount
    $call_amount += $quoted_amount * $number_of_standard_crews;
    $call_amount += $client_rate * $additional_hours;
    // add call amount
    // client additional charge amount
    $additional_client_charge = (float) $call->field_additional_charge_ammount_value;
    $additional_client_desc = $call->field_additional_charge_desc_value;
    if ($additional_client_charge >= 1) $inc++;
    $call_amount += $additional_client_charge;
    // client discount
    $discount = (float) $row->field_job_discount_value;      
    // boundary charge
    $boundary_charge = 0;
    if ($call->field_add_boundary_charge_value == 1) {
      $boundary_charge = $call->field_session_boundary_charge_value * $number_of_standard_crews;
      $inc++;
    }
    $call_amount += $boundary_charge;
    // mileage charge
    $mileage_charge = 0;
    $mileage_unit = 0;
    //Venue distance
    $venue_mileage = (int) acecrew_get_venue_milage_by_venue_id($call->field_job_session_venue_value);
    if ($venue_mileage) {
        $distance = $venue_mileage;
    } else {
        $distance = 0;
    }

    // if vehicles are assigned to call
    if ($call->field_session_num_vehicles_value >= 1) {
      //Set mileage unit
      $mileage_unit = $call->field_job_session_mileage_value;
      //Calculate charge per miles, distance * num of vehicles * charge per mile
      $mileage_charge =  $distance * $call->field_session_num_vehicles_value * $mileage_unit;
      $inc++;
    }
    $call_amount += $mileage_charge;
    // if client total is adjusted, adjust the $call_amount
    if ($total_adjust_add || $total_adjust_reduce) {
      $call_amount = $call_amount + $total_adjust_add - $total_adjust_reduce;
      $total_adjusted = true;
    } 
    if ($call->cancellation_status == CANCELLATION_NORMAL ||
      ($row->cancellation_status == CANCELLATION_NORMAL &&
      $call->cancellation_status == CANCELLATION_NA)) {
      $call_amount = 0;
    }
    $sum += acecrew_cancellation_price_total($call_amount, 
                                             $call->cancellation_status, 
                                             $row->cancellation_status);
  }
  $sum -= $discount;

  return $sum;
}