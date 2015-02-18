<?php

//********************
// RULES VENUE ACTIONS
//********************
function at_venue_create_action($venue) {
  $type = 'venue';
  $item_title = acecrew_get_title_field_by_type($type, $venue);

  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $venue->nid, 
    '',
    $item_title,
    '',
    "!username has created new '!item_title' !item_type" 
  );
}

function at_venue_edit_action($venue_before, $venue_after) {
  $type = 'venue';  
  // NAME
  acecrew_tracker_cck_text_log($type, 'field_venue_name', $venue_before, $venue_after);
  // ADDRESS
  acecrew_tracker_cck_text_log($type, 'field_venue_address', $venue_before, $venue_after);
  // POST CODE
  acecrew_tracker_cck_text_log($type, 'field_venue_post_code', $venue_before, $venue_after);
  // Notes
  acecrew_tracker_cck_text_log($type, 'field_venue_notes', $venue_before, $venue_after);
  // BOUNDARY CHARGE
  acecrew_tracker_cck_text_log($type, 'field_boundary_charge', $venue_before, $venue_after);
  // Round Trip In Miles
  acecrew_tracker_cck_text_log($type, 'field_boundary_round_trip', $venue_before, $venue_after);
  // Email
  acecrew_tracker_cck_text_log($type, 'field_venue_email', $venue_before, $venue_after);
  // Contact
  acecrew_tracker_cck_text_log($type, 'field_venue_contact', $venue_before, $venue_after);
  // Contact Telephone
  acecrew_tracker_cck_text_log($type, 'field_venue_contact_telephone', $venue_before, $venue_after);
  // Telephone
  acecrew_tracker_cck_text_log($type, 'field_venue_telephone', $venue_before, $venue_after);
  // Nearest Station/Tube
  acecrew_tracker_cck_text_log($type, 'field_nearest_station', $venue_before, $venue_after);
  // Venue Job Call Comments Box
  acecrew_tracker_cck_text_log($type, 'field_venue_job_call_cb', $venue_before, $venue_after);
  // BLOCKED CREWS
  acecrew_tracker_cck_usereference_log($type, 'field_blocked_crews', $venue_before, $venue_after); 
}

function at_venue_delete_action($venue) {
  $type = 'venue';
  $item_title = acecrew_get_title_field_by_type($type, $venue);  
  
  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $venue->nid, 
    '',
    $item_title,
    '',
    "!username has deleted '!item_title' !item_type" 
  );
}
