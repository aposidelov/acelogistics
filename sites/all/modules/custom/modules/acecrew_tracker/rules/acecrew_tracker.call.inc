<?php

//********************
// RULES CALL ACTIONS
//********************

function at_call_create_action($call) {
  $type = 'call';

  $item_title = acecrew_get_title_field_by_type($type, $call);  
  
  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $call->nid, 
    '',
    $item_title,
    '',
    "!username has created new '!item_title' !item_type" 
  );
}

function at_call_edit_action($call_before, $call_after) {    
  $type = 'call';      
  
  //************************
  // Check call status
  //************************
  if ($call_before->status != $call_after->status) {
    $item_title = acecrew_get_title_field_by_type($type, $call_after);
    $before_status = $call_before->status ? 'Activated' : 'Canceled';
    $after_status = $call_after->status ? 'Activated' : 'Canceled';
    acecrew_tracker_node_log(
      $type, 
      $before_status, 
      $after_status, 
      $call_after->nid, 
      'status',
      $item_title,
      'Status' 
    );
  }

  //************************
  // TEXT FIELDS
  //************************
  // Call Plus 
  acecrew_tracker_cck_bool_log($type, 'field_job_session_plus_call', $call_before, $call_after);
  // Date Time 
  acecrew_tracker_cck_datetime_log($type, 'field_job_session_date_time', $call_before, $call_after);
  // Date Time TBC
  acecrew_tracker_cck_bool_log($type, 'field_call_time_tbc', $call_before, $call_after);
  // Number of crew
  acecrew_tracker_cck_text_log($type, 'field_job_session_crew', $call_before, $call_after);
  // Number of crew TBC
  acecrew_tracker_cck_bool_log($type, 'field_call_crew_tbc', $call_before, $call_after);
  // Number of hours
  acecrew_tracker_cck_text_log($type, 'field_job_session_hours', $call_before, $call_after);
  // Number of hours TBC
  acecrew_tracker_cck_bool_log($type, 'field_call_hours_tbc', $call_before, $call_after);
  // Call id
  acecrew_tracker_cck_text_log($type, 'field_session_callid', $call_before, $call_after);
  // Call Contract TBC
  acecrew_tracker_cck_bool_log($type, 'field_call_contract_tbc', $call_before, $call_after);  
  // Number of vehicles
  acecrew_tracker_cck_text_log($type, 'field_session_num_vehicles', $call_before, $call_after, TRUE);  
  // MILEAGE
  acecrew_tracker_cck_text_log($type, 'field_job_session_mileage', $call_before, $call_after);
  // VAT RATE
  acecrew_tracker_cck_text_log($type, 'field_job_session_vat_rate', $call_before, $call_after);
  // BOUNDARY CHARGE
  acecrew_tracker_cck_text_log($type, 'field_session_boundary_charge', $call_before, $call_after);
  // Add Boundary Charge
  acecrew_tracker_cck_bool_log($type, 'field_add_boundary_charge', $call_before, $call_after);
  // Call Comments
  acecrew_tracker_cck_text_log($type, 'field_job_session_comment', $call_before, $call_after);
  // Additional charge amount
  acecrew_tracker_cck_text_log($type, 'field_additional_charge_ammount', $call_before, $call_after);
  // Additional charge description
  acecrew_tracker_cck_text_log($type, 'field_additional_charge_desc', $call_before, $call_after);
  // Supplements
  acecrew_tracker_cck_supplements_multifield_log($type, 'field_call_supplements', $call_before, $call_after);
  //************************
  // SPECIAL FIELDS
  //************************
  // Cancellation
  $cancellations = acecrew_get_cancellations();
  acecrew_tracker_cck_select_log($type, 'field_cancellation_status', $cancellations, $call_before, $call_after);
  // Venue
  $venue = acecrew_get_job_venue();
  acecrew_tracker_cck_select_log($type, 'field_job_session_venue', $venue, $call_before, $call_after);  
  // Client rate
  $client_rates = acecrew_get_ads('field_admins_clientrates');
  acecrew_tracker_cck_select_log($type, 'field_job_session_client_rate', $client_rates, $call_before, $call_after);
  // Client Contacts
  $client_contacts = _acecrew_get_jobclient_contacts();
  acecrew_tracker_cck_select_log($type, 'field_call_contact', $client_contacts, $call_before, $call_after);
  
}

function at_call_delete_action($call) {
  $type = 'call';

  $item_title = acecrew_get_title_field_by_type($type, $call);  
  
  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $call->nid, 
    '',
    $item_title,
    '',
    "!username has deleted '!item_title' !item_type" 
  );
}