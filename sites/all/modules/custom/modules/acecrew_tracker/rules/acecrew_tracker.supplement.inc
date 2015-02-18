<?php

//*************************
// RULE SUPPLEMENTS ACTIONS
//*************************
function at_supplement_create_action($supplement) {
  $type = 'supplement';
  $item_title = acecrew_get_title_field_by_type($type, $supplement);

  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $supplement->nid, 
    '',
    $item_title,
    '',
    "!username has created new '!item_title' !item_type" 
  );
}

function at_supplement_edit_action($supplement_before, $supplement_after) {
  $type = 'supplement';  
  // Supplement Label  
  acecrew_tracker_cck_text_log($type, 'title', $supplement_before, $supplement_after);
  // Supplement Short Label  
  acecrew_tracker_cck_text_log($type, 'field_supplement_short', $supplement_before, $supplement_after);  
  // 0-4 hours
  // Client Per Hour
  acecrew_tracker_cck_text_log($type, 'field_supp_0to4_client_hour', $supplement_before, $supplement_after);
  // Client Single Payment
  acecrew_tracker_cck_text_log($type, 'field_supp_0to4_client_single', $supplement_before, $supplement_after);
  // Crew Per Hour
  acecrew_tracker_cck_text_log($type, 'field_supp_0to4_crew_hour', $supplement_before, $supplement_after);
  // Crew Single Payment
  acecrew_tracker_cck_text_log($type, 'field_supp_0to4_crew_single', $supplement_before, $supplement_after);

  // 5-8 hours
  // Client Per Hour
  acecrew_tracker_cck_text_log($type, 'field_supp_5to8_client_hour', $supplement_before, $supplement_after);
  // Client Single Payment
  acecrew_tracker_cck_text_log($type, 'field_supp_5to8_client_single', $supplement_before, $supplement_after);
  // Crew Per Hour
  acecrew_tracker_cck_text_log($type, 'field_supp_5to8_crew_hour', $supplement_before, $supplement_after);
  // Crew Single Payment
  acecrew_tracker_cck_text_log($type, 'field_supp_5to8_crew_single', $supplement_before, $supplement_after);

  // 9-12 hours
  // Client Per Hour
  acecrew_tracker_cck_text_log($type, 'field_supp_9to12_client_hour', $supplement_before, $supplement_after);
  // Client Single Payment
  acecrew_tracker_cck_text_log($type, 'field_supp_9to12_client_single', $supplement_before, $supplement_after);
  // Crew Per Hour
  acecrew_tracker_cck_text_log($type, 'field_supp_9to12_crew_hour', $supplement_before, $supplement_after);
  // Crew Single Payment
  acecrew_tracker_cck_text_log($type, 'field_supp_9to12_crew_single', $supplement_before, $supplement_after);

  // 12+ hours
  // Client Per Hour
  acecrew_tracker_cck_text_log($type, 'field_supp_12plus_client_hour', $supplement_before, $supplement_after);
  // Client Single Payment
  acecrew_tracker_cck_text_log($type, 'field_supp_12plus_client_single', $supplement_before, $supplement_after);
  // Crew Per Hour
  acecrew_tracker_cck_text_log($type, 'field_supp_12plus_crew_hour', $supplement_before, $supplement_after);
  // Crew Single Payment
  acecrew_tracker_cck_text_log($type, 'field_supp_12plus_crew_single', $supplement_before, $supplement_after);

  // Per Hour
  acecrew_tracker_cck_text_log($type, 'field_supp_per_hour', $supplement_before, $supplement_after);
  // Single Payment
  acecrew_tracker_cck_text_log($type, 'field_supp_single_payment', $supplement_before, $supplement_after);
}

function at_supplement_delete_action($supplement) {
  $type = 'supplement';
  $item_title = acecrew_get_title_field_by_type($type, $supplement);  
  
  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $supplement->nid, 
    '',
    $item_title,
    '',
    "!username has deleted '!item_title' !item_type" 
  );
}