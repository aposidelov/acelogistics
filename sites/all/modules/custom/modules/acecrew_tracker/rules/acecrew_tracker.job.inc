<?php

//******************
// RULES JOB ACTIONS
//******************
function at_job_create_action($job) {
  $type = 'job';

  $item_title = acecrew_get_title_field_by_type($type, $job);  
  
  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $job->nid, 
    '',
    $item_title,
    '',
    "!username has created new '!item_title' !item_type" 
  );
}

function at_job_edit_action($job_before, $job_after) {
  $type = 'job';    
  //************************
  // TEXT FIELDS
  //************************
  // Job number  
  acecrew_tracker_cck_text_log($type, 'field_job_number', $job_before, $job_after);
  // Job date  
  acecrew_tracker_cck_date_log($type, 'field_job_date', $job_before, $job_after);
  // Job po number  
  acecrew_tracker_cck_text_log($type, 'field_job_po_number', $job_before, $job_after);
  // Job Discount
  acecrew_tracker_cck_text_log($type, 'field_job_discount', $job_before, $job_after);
  // Job Discount Description
  acecrew_tracker_cck_text_log($type, 'field_job_discount_desc', $job_before, $job_after);
  // Comments
  acecrew_tracker_cck_text_log($type, 'field_job_comments', $job_before, $job_after);
  // Invoice notes
  acecrew_tracker_cck_text_log($type, 'field_invoice_notes', $job_before, $job_after);
  // Booked by
  acecrew_tracker_cck_text_log($type, 'field_job_booked_by', $job_before, $job_after);
  // Created by
  acecrew_tracker_cck_text_log($type, 'field_job_created_by', $job_before, $job_after);
  // Documents
  acecrew_tracker_cck_file_log($type, 'field_document', $job_before, $job_after);  

  //************************
  // SPECIAL FIELDS
  //************************
  // Job status
  $job_statuses = acecrew_get_statuses();
  acecrew_tracker_cck_select_log($type, 'field_job_status', $job_statuses, $job_before, $job_after);   
  // Cancellation
  $cancellations = acecrew_get_cancellations();
  acecrew_tracker_cck_select_log($type, 'field_cancellation_status', $cancellations, $job_before, $job_after);   
  // Client
  $clients = acecrew_get_job_clients();
  acecrew_tracker_cck_select_log($type, 'field_job_client_name', $clients, $job_before, $job_after);
  // Client contact
  $client_contacts = acecrew_get_job_client_contacts();
  acecrew_tracker_cck_select_log($type, 'field_job_client_contact', $client_contacts, $job_before, $job_after);
  // Venue
  $venue = acecrew_get_job_venue();
  acecrew_tracker_cck_select_log($type, 'field_job_venue', $venue, $job_before, $job_after);
}

function at_job_delete_action($job) {
  $type = 'job';

  $item_title = acecrew_get_title_field_by_type($type, $job);  
  
  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $job->nid, 
    '',
    $item_title,
    '',
    "!username has deleted '!item_title' !item_type" 
  );
}