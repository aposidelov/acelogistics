<?php

//*******************
// RULES UPLOAD-CREW ACTIONS
//*******************
function at_uploadcrew_create_action($uploadcrew) {
  $type = 'profile';    

  $profile = acecrew_get_username($uploadcrew->uid);

  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $uploadcrew->id, 
    '',
    $item_title,
    '',
    "!username has created new 'Crew Uploads And Payrates' for '$profile' profile" 
  );  
}

/**
 * All logics of this hook has been moved to hook_user_profile_sumbit
 */
function at_uploadcrew_edit_action($uploadcrew_before, $uploadcrew_after) {
  $type = 'profile';    

  $profile = acecrew_get_username($uploadcrew_before->uid);

  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $uploadcrew->uid, 
    '',
    '',
    '',
    "!username has changed 'Crew Uploads And Payrates' for '$profile' profile" 
  );
}

function at_uploadcrew_delete_action($uploadcrew) {
  $type = 'profile';  

  $profile = acecrew_get_username($uploadcrew->uid);
  
  acecrew_tracker_node_log(
    $type, 
    '', 
    '', 
    $uploadcrew->uid, 
    '',
    '',
    '',
    "!username has deleted 'Crew Uploads And Payrates' for '$profile' profile" 
  );
}