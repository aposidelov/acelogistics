<?php

//*******************
// RULES CREW ACTIONS
//*******************
function at_crew_create_action($crew) {
  $type = 'profile';      

  $item_title = $crew->name;

  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $crew->uid, 
    '',
    $item_title,
    '',
    "!username has created new '!item_title' !item_type" 
  );  
}

/**
 * All logics of this hook has been moved to hook_user_profile_sumbit
 */
function at_crew_edit_action($crew_before, $crew_after) {
  $type = 'profile';  
}

function at_crew_delete_action($crew) {
  $type = 'profile';
  
  $item_title = $crew->name;
  
  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $crew->uid, 
    '',
    $item_title,
    '',
    "!username has deleted '!item_title' !item_type" 
  );
}