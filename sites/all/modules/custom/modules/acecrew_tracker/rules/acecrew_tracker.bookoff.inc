<?php

//**********************
// RULES BOOKOFF ACTIONS
//**********************
function at_bookoff_create_action($bookoff) {
  $type = 'bookoff';
  $item_title = acecrew_get_title_field_by_type($type, $bookoff);

  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $bookoff->nid, 
    '',
    $item_title,
    '',
    "!username has created new '!item_title' !item_type" 
  );
}

function at_bookoff_edit_action($bookoff_before, $bookoff_after) {
  $type = 'bookoff';  

  // LABEL
  acecrew_tracker_cck_text_log($type, 'field_ub_label', $bookoff_before, $bookoff_after);
  // Date Time Start
  acecrew_tracker_cck_datetime_log($type, 'field_ub_date_start', $bookoff_before, $bookoff_after);
  // Date Time End
  acecrew_tracker_cck_datetime_log($type, 'field_ub_date_end', $bookoff_before, $bookoff_after);
  // COMMENT BOX
  acecrew_tracker_cck_text_log($type, 'field_comment_box', $bookoff_before, $bookoff_after);
}

function at_bookoff_delete_action($bookoff) {
  $type = 'bookoff';
  $item_title = acecrew_get_title_field_by_type($type, $bookoff);  
  
  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $bookoff->nid, 
    '',
    $item_title,
    '',
    "!username has deleted '!item_title' !item_type" 
  );
}