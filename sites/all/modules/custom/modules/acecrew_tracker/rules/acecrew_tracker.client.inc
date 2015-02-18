<?php

//*********************
// RULES CLIENT ACTIONS
//*********************
function at_client_create_action($client) {
  $type = 'client';
  $item_title = acecrew_get_title_field_by_type($type, $client);

  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $client->nid, 
    '',
    $item_title,
    '',
    "!username has created new '!item_title' !item_type" 
  );
}

function at_client_edit_action($client_before, $client_after) {
  $type = 'client';  
  // LOGO
  acecrew_tracker_cck_image_log($type, 'field_client_logo', $client_before, $client_after);
  // CLIENT CONTACT
  acecrew_tracker_cck_contacts_flexifield_log($type, 'field_client_contact', $client_before, $client_after);
  // ACCOUNTS
  acecrew_tracker_cck_accounts_flexifield_log($type, 'field_add_accounts', $client_before, $client_after);
  // OFFICES
  acecrew_tracker_cck_offices_flexifield_log($type, 'field_add_offices', $client_before, $client_after);
  // CREDIT LIMIT BOX
  acecrew_tracker_cck_text_log($type, 'field_credit_limit_box', $client_before, $client_after);
  // NAME
  acecrew_tracker_cck_text_log($type, 'field_client_name', $client_before, $client_after);
  // COMPANY NUMBER
  acecrew_tracker_cck_text_log($type, 'field_client_company_number', $client_before, $client_after);
  // VAT NUMBER
  acecrew_tracker_cck_text_log($type, 'field_client_vatnumber', $client_before, $client_after);
  // WEBSITE URL
  acecrew_tracker_cck_text_log($type, 'field_client_website', $client_before, $client_after);
  // RATE
  acecrew_tracker_cck_text_log($type, 'field_client_rate', $client_before, $client_after);
  // 2 HOUR DEFAULT
  acecrew_tracker_cck_text_log($type, 'field_2_hour_default', $client_before, $client_after);
  // 3 HOUR DEFAULT
  acecrew_tracker_cck_text_log($type, 'field_3_hour_default', $client_before, $client_after);
  // EMAIL
  acecrew_tracker_cck_text_log($type, 'field_client_company_email', $client_before, $client_after);
  // TELEPHONE
  acecrew_tracker_cck_text_log($type, 'field_client_company_telephone', $client_before, $client_after);
  // FAX
  acecrew_tracker_cck_text_log($type, 'field_client_company_fax', $client_before, $client_after);
  // CLIENT JOB CALL COMMENTS BOX
  acecrew_tracker_cck_text_log($type, 'field_client_job_call_cb', $client_before, $client_after);
  // ADDRESS
  acecrew_tracker_cck_text_log($type, 'field_client_company_address', $client_before, $client_after);
  // POST CODE
  acecrew_tracker_cck_text_log($type, 'field_client_company_postcode', $client_before, $client_after);
  // DEFAULT CONTACT
  acecrew_tracker_cck_text_log($type, 'field_client_company_contact', $client_before, $client_after);
  // DEFAULT CONTACT MOBILE
  acecrew_tracker_cck_text_log($type, 'field_default_contact_mobile', $client_before, $client_after);
  // NOTES 
  acecrew_tracker_cck_text_log($type, 'field_client_company_notes', $client_before, $client_after, FALSE, TRUE);
  // BLOCKED CREWS
  acecrew_tracker_cck_usereference_log($type, 'field_blocked_crews', $client_before, $client_after);  
}

function at_client_delete_action($client) {
  $type = 'client';
  $item_title = acecrew_get_title_field_by_type($type, $client);  
  
  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $client->nid, 
    '',
    $item_title,
    '',
    "!username has deleted '!item_title' !item_type" 
  );
}