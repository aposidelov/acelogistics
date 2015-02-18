<?php

//****************
// USER FIELD LOGS
//****************
function acecrew_tracker_profile_text_log($type, $field_name, $crew_before, $crew_after, $use_none = FALSE) {
  $type = 'profile';
  $item_id = $crew_before->uid;
  $item_title = acecrew_get_title_field_by_type($type, $crew_before);
  $before_field_value = $crew_before->{$field_name};
  $after_field_value = $crew_after->{$field_name};

  if ($before_field_value != $after_field_value) {    
    if ($use_none) {
      $before_field_value = !empty($before_field_value) ? $before_field_value : 'None';
      $after_field_value = !empty($after_field_value) ? $after_field_value : 'None';
    } 

    acecrew_tracker_profile_log(
      $type, 
      $before_field_value, 
      $after_field_value, 
      $item_id, 
      $field_name,
      $item_title                  
    );
  }
}

function acecrew_tracker_profile_pass_log($type, $field_name, $crew_before, $crew_after) {
  $type = 'profile';
  $item_id = $crew_before->uid;
  $item_title = acecrew_get_title_field_by_type($type, $crew_before);
  $before_field_value = $crew_before->{$field_name};
  $after_field_value = $crew_after->{$field_name};

  if (!empty($after_field_value)) {

    acecrew_tracker_profile_log(
      $type, 
      $before_field_value, 
      $after_field_value, 
      $item_id, 
      $field_name,
      $item_title,
      '',
      "!username has changed 'Pass' to !after_value for '!item_title' !item_type"                   
    );
  }
}

function acecrew_tracker_profile_picture_log($type, $field_name, $crew_before, $crew_after) {
  $type = 'profile';
  $item_id = $crew_before->uid;
  $item_title = acecrew_get_title_field_by_type($type, $crew_before);
  $before_field_value = $crew_before->{$field_name};
  $after_field_value = $crew_after->{$field_name};

  $run_log = FALSE;
  if ($crew_after->picture_delete) {
    $run_log = TRUE;
    $message = "!username has removed picture for '!item_title' !item_type";
  } elseif (isset($crew_after->picture)) {
    $run_log = TRUE;
    $message = "!username has changed picture for '!item_title' !item_type";
  }

  if ($run_log) {    
    acecrew_tracker_profile_log(
      $type,
      '',
      '',
      $item_id,
      $field_name,
      $item_title,
      '',
      $message
    );
  }
}

function acecrew_tracker_profile_select_log($type, $field_name, $crew_before, $crew_after, $valueTitles = array()) {
  $type = 'profile';  
  if (!sizeof($valueTitles)) {
    $valueTitles = acecrew_get_profile_list($field_name);
  }
  $item_id = $crew_before->uid;
  $item_title = acecrew_get_title_field_by_type($type, $crew_before);
  $before_field_value = $crew_before->{$field_name};
  $after_field_value = $crew_after->{$field_name};

  if ($before_field_value != $after_field_value) {    
    acecrew_tracker_profile_log(
      $type,
      $valueTitles[$before_field_value],
      $valueTitles[$after_field_value],
      $item_id,
      $field_name,
      $item_title
    );
  }
}

function acecrew_tracker_profile_date_log($type, $field_name, $crew_before, $crew_after) {
  $type = 'profile';
  $item_id = $crew_before->uid;
  $item_title = acecrew_get_title_field_by_type($type, $crew_before);
  $before_field_value = $crew_before->{$field_name};
  $after_field_value = $crew_after->{$field_name};

  if ($before_field_value['day'] != $after_field_value['day'] ||
      $before_field_value['month'] != $after_field_value['month'] ||
      $before_field_value['year'] != $after_field_value['year']) {    
    acecrew_tracker_profile_log(
      $type,
      $before_field_value['year'].'-'.$before_field_value['month'].'-'.$before_field_value['day'],
      $after_field_value['year'].'-'.$after_field_value['month'].'-'.$after_field_value['day'],
      $item_id,
      $field_name,
      $item_title
    );
  }
}

function acecrew_tracker_profile_roles_log($type, $field_name, $crew_before, $crew_after) {    
  $roles_before = $crew_before->roles;  
  $roles = user_roles();
  foreach ($crew_after->roles as $rid => $data) {
    $roles_after[$rid] = $roles[$rid];
  }

  if ($roles_before != $roles_after) {
    $type = 'profile';
    $item_id = $crew_before->uid;
    $item_title = $crew_before->name;    
    $roles_before_names = implode(', ', $roles_before);
    $roles_after_names = implode(', ', $roles_after);

    acecrew_tracker_profile_log(
      $type, 
      $roles_before_names, 
      $roles_after_names, 
      $item_id, 
      $field_name,
      $item_title                  
    );
  }
}

function acecrew_tracker_profile_supplement_skills_log($skills_before, $skills_after, $uid, $field_name) {    
  if ($skills_before != $skills_after) {
    $type = 'profile';
    $item_id = $uid;
    $item_title = acecrew_get_username($uid);
    $skills_before_names = array();
    $skills_after_names = array();
    foreach ($skills_before as $skill_nid) {
      $skills_before_names[] = get_node_title($skill_nid);
    }
    foreach ($skills_after as $skill_nid) {
      $skills_after_names[] = get_node_title($skill_nid);
    }
    $skills_before_names = implode(', ', $skills_before_names);
    $skills_after_names = implode(', ', $skills_after_names);

    acecrew_tracker_profile_log(
      $type, 
      $skills_before_names, 
      $skills_after_names, 
      $item_id, 
      $field_name,
      $item_title                  
    );
  }
}

function acecrew_tracker_profile_supplement_payrate_log($payrate_before, $payrate_after, $uid, $field_name) {
  if ($payrate_before != $payrate_after) {
    $type = 'profile';
    $item_id = $uid;
    $item_title = acecrew_get_username($uid);

    acecrew_tracker_profile_log(
      $type, 
      $payrate_before, 
      $payrate_after, 
      $item_id, 
      $field_name,
      $item_title                  
    );
  }
}


//****************
// NODE FIELD LOGS
//****************
function acecrew_tracker_cck_text_log($type, $field_name, $node_before, $node_after, $use_none = FALSE, $multivalue = FALSE) {  
  $item_id = $node_before->nid;   
  $item_title = acecrew_get_title_field_by_type($type, $node_before);  
  $before_field = $node_before->{$field_name};
  $after_field = $node_after->{$field_name};
  if ($field_name == 'title') {
    $before_field_value = $before_field;
    $after_field_value = $after_field;
  } else {
    $before_field_value = $before_field[0]['value'];
    $after_field_value = $after_field[0]['value'];  
  }
  
  if ($before_field_value != $after_field_value) {    
    if ($use_none) {
      $before_value = !empty($before_field_value) ? $before_field_value : 'None';
      $after_value = !empty($after_field_value) ? $after_field_value : 'None';
    } else {
      $before_value = $before_field_value;
      $after_value = $after_field_value;
    }

    acecrew_tracker_node_log(
      $type, 
      $before_value, 
      $after_value, 
      $item_id, 
      $field_name,
      $item_title                  
    );
  }
        
  if ($multivalue) {
    $before_field_items_count = sizeof($before_field);
    $after_field_items_count = sizeof($after_field);
    if ($before_field_items_count > $after_field_items_count) {
      acecrew_tracker_node_log(
        $type, 
        '',
        $before_field_items_count - $after_field_items_count,
        $item_id, 
        $field_name, 
        $item_title,
        '',
        "!username has removed !after_value item(s) in '!field_label' for '!item_title' !item_type"  
      );
    } elseif ($before_field_items_count < $after_field_items_count) {
      acecrew_tracker_node_log(
        $type, 
        '',
        $after_field_items_count - $before_field_items_count,
        $item_id, 
        $field_name, 
        $item_title,
        '',
        "!username has added !after_value item(s) in '!field_label' for '!item_title' !item_type"  
      );
    }
  }    
  
  return TRUE;
}

function acecrew_tracker_cck_bool_log($type, $field_name, $node_before, $node_after) {  
  $item_id = $node_before->nid;
  $item_title = acecrew_get_title_field_by_type($type, $node_after); 

  if ($node_before->{$field_name}[0]['value'] != $node_after->{$field_name}[0]['value']) {    
    $before_value = $node_before->{$field_name}[0]['value'] ? 'ticked' : 'unticked';
    $after_value = $node_after->{$field_name}[0]['value'] ? 'ticked' : 'unticked';

    acecrew_tracker_node_log(
      $type, 
      $before_value, 
      $after_value, 
      $item_id, 
      $field_name,
      $item_title  
    );

    return TRUE;
  }
  return FALSE;
}

function acecrew_tracker_cck_file_log($type, $field_name, $node_before, $node_after) {  
  $item_id = $node_before->nid;
  $item_title = acecrew_get_title_field_by_type($type, $node_after); 

  //watchdog('db', '<pre>'.print_r($node_before->{$field_name}, TRUE).'</pre>');
  //watchdog('da', '<pre>'.print_r($node_after->{$field_name}, TRUE).'</pre>');

  $before_empty = FALSE;
  // check if file field is empty
  if (empty($node_before->{$field_name}[0]) || 
    (!empty($node_before->{$field_name}[0]) && 
      empty($node_before->{$field_name}[0]['fid']))) {
    $before_empty = TRUE;
  }

  $after_empty = FALSE;
  // check if file field is empty
  if (empty($node_after->{$field_name}[0]) || 
    (!empty($node_after->{$field_name}[0]) && 
      empty($node_after->{$field_name}[0]['fid']))) {
    $after_empty = TRUE;
  }

  foreach ($node_after->{$field_name} as $key => $data) {
    if (isset($node_after->{$field_name}[$key]['filefield_upload'])) {
      unset($node_after->{$field_name}[$key]['filefield_upload']);
    }
    if (isset($node_after->{$field_name}[$key]['filefield_remove'])) {
      unset($node_after->{$field_name}[$key]['filefield_remove']);
    }
    if (isset($node_after->{$field_name}[$key]['upload'])) {
      unset($node_after->{$field_name}[$key]['upload']);
    }
    if (isset($node_after->{$field_name}[$key]['alt'])) {
      unset($node_after->{$field_name}[$key]['alt']);
    }
    if (isset($node_after->{$field_name}[$key]['title'])) {
      unset($node_after->{$field_name}[$key]['title']);
    }
  }

  if ((!$before_empty && !$after_empty && $node_before->{$field_name} != $node_after->{$field_name}) ||
    $before_empty != $after_empty) {        

    acecrew_tracker_node_log(
      $type, 
      $before_value, 
      $after_value, 
      $item_id, 
      $field_name,
      $item_title,
      '',
      "!username has updated attached file(s) for '!item_title' !item_type"
    );

    return TRUE;
  }
  return FALSE;
}

function acecrew_tracker_cck_image_log($type, $field_name, $node_before, $node_after) {  
  $item_id = $node_before->nid;
  $item_title = acecrew_get_title_field_by_type($type, $node_after);   

  $before_empty = FALSE;
  // check if file field is empty
  if (empty($node_before->{$field_name}[0]) || 
    (!empty($node_before->{$field_name}[0]) && 
      empty($node_before->{$field_name}[0]['fid']))) {
    $before_empty = TRUE;
  }

  $after_empty = FALSE;
  // check if file field is empty
  if (empty($node_after->{$field_name}[0]) || 
    (!empty($node_after->{$field_name}[0]) && 
      empty($node_after->{$field_name}[0]['fid']))) {
    $after_empty = TRUE;
  }

  foreach ($node_after->{$field_name} as $key => $data) {
    if (isset($node_after->{$field_name}[$key]['filefield_upload'])) {
      unset($node_after->{$field_name}[$key]['filefield_upload']);
    }
    if (isset($node_after->{$field_name}[$key]['filefield_remove'])) {
      unset($node_after->{$field_name}[$key]['filefield_remove']);
    }
    if (isset($node_after->{$field_name}[$key]['upload'])) {
      unset($node_after->{$field_name}[$key]['upload']);
    }
    if (isset($node_after->{$field_name}[$key]['alt'])) {
      unset($node_after->{$field_name}[$key]['alt']);
    }
    if (isset($node_after->{$field_name}[$key]['title'])) {
      unset($node_after->{$field_name}[$key]['title']);
    }
  }

  if ((!$before_empty && !$after_empty && $node_before->{$field_name} != $node_after->{$field_name}) ||
    $before_empty != $after_empty) {        

    acecrew_tracker_node_log(
      $type, 
      $before_value, 
      $after_value, 
      $item_id, 
      $field_name,
      $item_title,
      '',
      "!username has updated image(s) for '!item_title' !item_type"
    );

    return TRUE;
  }
  return FALSE;
}

function acecrew_tracker_cck_date_log($type, $field_name, $node_before, $node_after) {  
  $item_id = $node_before->nid;  
  $item_title = acecrew_get_title_field_by_type($type, $node_after);

  if ($node_before->{$field_name}[0]['value'] != $node_after->{$field_name}[0]['value']) {    
    $before_value = date('Y-m-d', $node_before->{$field_name}[0]['value']);
    $after_value = date('Y-m-d', $node_after->{$field_name}[0]['value']);

    acecrew_tracker_node_log(
      $type, 
      $before_value, 
      $after_value, 
      $item_id, 
      $field_name,
      $item_title  
    );

    return TRUE;
  }
  return FALSE;
}

function acecrew_tracker_cck_datetime_log($type, $field_name, $node_before, $node_after) {  
  $item_id = $node_before->nid;   
  $item_title = acecrew_get_title_field_by_type($type, $node_after);

  if ($node_before->{$field_name}[0]['value'] != $node_after->{$field_name}[0]['value']) {    
    $before_value = $node_before->{$field_name}[0]['value'];//date('Y-m-d H:i', $node_before->{$field_name}[0]['value']);
    $after_value = $node_after->{$field_name}[0]['value'];//date('Y-m-d H:i', $node_after->{$field_name}[0]['value']);

    acecrew_tracker_node_log(
      $type, 
      $before_value, 
      $after_value, 
      $item_id, 
      $field_name,
      $item_title  
    );

    return TRUE;
  }
  return FALSE;
}

function acecrew_tracker_cck_select_log($type, $field_name, $valueTitles, $node_before, $node_after) {  
  $item_id = $node_before->nid;   
  $item_title = acecrew_get_title_field_by_type($type, $node_after);

  if ($node_before->{$field_name}[0]['value'] != $node_after->{$field_name}[0]['value']) {    
    $before_value = !empty($valueTitles[$node_before->{$field_name}[0]['value']]) ? $valueTitles[$node_before->{$field_name}[0]['value']] : 'None';
    $after_value = !empty($valueTitles[$node_after->{$field_name}[0]['value']]) ? $valueTitles[$node_after->{$field_name}[0]['value']] : 'None';

    acecrew_tracker_node_log(
      $type, 
      $before_value, 
      $after_value, 
      $item_id, 
      $field_name, 
      $item_title 
    );

    return TRUE;
  }
  return FALSE;
}

function acecrew_tracker_cck_contacts_flexifield_log($type, $field_name, $node_before, $node_after) {
  $item_id = $node_before->nid;     
  $item_title = acecrew_get_title_field_by_type($type, $node_after);
  $field_name = 'field_client_contact';
  $before_contact_names = array();
  $after_contact_names = array();

  foreach ($node_before->{$field_name} as $key => $contact_before) {
    $before_contact_name = $node_before->{$field_name}[$key]['value']['field_client_contact_name'][0]['value'];
    $after_contact_name = $node_after->{$field_name}[$key]['value']['field_client_contact_name'][0]['value'];
    $before_contact_mobile = $node_before->{$field_name}[$key]['value']['field_client_contact_mobile'][0]['value'];
    $after_contact_mobile = $node_after->{$field_name}[$key]['value']['field_client_contact_mobile'][0]['value'];
    $before_contact_email = $node_before->{$field_name}[$key]['value']['field_client_contact_email'][0]['email'];
    $after_contact_email = $node_after->{$field_name}[$key]['value']['field_client_contact_email'][0]['email'];
    $before_contact_names[] = $before_contact_name;    
    // check difference of mobiles and emails only if name is same
    if ($before_contact_name == $after_contact_name) {
      if ($before_contact_mobile != $after_contact_mobile) {

        acecrew_tracker_node_log(
          $type, 
          $before_contact_mobile, 
          $after_contact_mobile, 
          $item_id, 
          $field_name, 
          $item_title,
          '',
          "!username has changed contact '$before_contact_name', 'mobile' from '!before_value' to '!after_value' '!item_title' !item_type"  
        );
      }

      if ($before_contact_email != $after_contact_email) {
        acecrew_tracker_node_log(
          $type, 
          $before_contact_email, 
          $after_contact_email, 
          $item_id, 
          $field_name, 
          $item_title,
          '',
          "!username has changed contact '$before_contact_name', 'email' from '!before_value' to '!after_value' '!item_title' !item_type"  
        );
      }
    }    
  }
  foreach ($node_after->{$field_name} as $key => $contact_after) {
    $after_contact_name = $node_after->{$field_name}[$key]['value']['field_client_contact_name'][0]['value'];
    $after_contact_names[] = $after_contact_name;
  }

  $removed_contacts = array_diff($before_contact_names, $after_contact_names);
  $added_contacts   = array_diff($after_contact_names, $before_contact_names);

  if (sizeof($removed_contacts)) {
    acecrew_tracker_node_log(
      $type, 
      '', 
      '', 
      $item_id, 
      $field_name, 
      $item_title,
      '',
      "!username has removed next contacts : [".implode(', ', $removed_contacts)."] for '!item_title' !item_type"  
    );
  }
  if (sizeof($added_contacts)) {
    acecrew_tracker_node_log(
      $type, 
      '', 
      '', 
      $item_id, 
      $field_name, 
      $item_title,
      '',
      "!username has added next contacts : [".implode(', ', $added_contacts)."] for '!item_title' !item_type"  
    );
  }
}

function acecrew_tracker_cck_accounts_flexifield_log($type, $field_name, $node_before, $node_after) {
  $item_id = $node_before->nid;     
  $item_title = acecrew_get_title_field_by_type($type, $node_after);
  $field_name = 'field_add_accounts';
  $before_account_names = array();
  $after_account_names = array();

  foreach ($node_before->{$field_name} as $key => $account_before) {
    $before_account_name = $node_before->{$field_name}[$key]['value']['field_accounts_contact'][0]['value'];
    $after_account_name = $node_after->{$field_name}[$key]['value']['field_accounts_contact'][0]['value'];
    $before_account_email = $node_before->{$field_name}[$key]['value']['field_accounts_email'][0]['email'];
    $after_account_email = $node_after->{$field_name}[$key]['value']['field_accounts_email'][0]['email'];
    $before_account_telephone = $node_before->{$field_name}[$key]['value']['field_accounts_telephone'][0]['value'];
    $after_account_telephone = $node_after->{$field_name}[$key]['value']['field_accounts_telephone'][0]['value'];
    $before_account_note = $node_before->{$field_name}[$key]['value']['field_accounts_notes'][0]['value'];
    $after_account_note = $node_after->{$field_name}[$key]['value']['field_accounts_notes'][0]['value'];
    $before_account_names[] = $before_account_name;    
    // check difference of mobiles and emails only if name is same
    if ($before_account_name == $after_account_name) {
      if ($before_account_email != $after_account_email) {

        acecrew_tracker_node_log(
          $type, 
          $before_account_email, 
          $after_account_email, 
          $item_id, 
          $field_name, 
          $item_title,
          '',
          "!username has changed account '$before_account_name', 'email' from '!before_value' to '!after_value' '!item_title' !item_type"  
        );
      }

      if ($before_account_telephone != $after_account_telephone) {
        acecrew_tracker_node_log(
          $type, 
          $before_account_telephone, 
          $after_account_telephone, 
          $item_id, 
          $field_name, 
          $item_title,
          '',
          "!username has changed account '$before_account_name', 'telephone' from '!before_value' to '!after_value' '!item_title' !item_type"  
        );
      }

      if ($before_account_note != $after_account_note) {
        acecrew_tracker_node_log(
          $type, 
          $before_account_note, 
          $after_account_note, 
          $item_id, 
          $field_name, 
          $item_title,
          '',
          "!username has changed account '$before_account_name', 'note' from '!before_value' to '!after_value' '!item_title' !item_type"  
        );
      }
    }
  }

  foreach ($node_after->{$field_name} as $key => $account_after) {
    $after_account_name = $node_after->{$field_name}[$key]['value']['field_accounts_contact'][0]['value'];
    $after_account_names[] = $after_account_name;
  }

  $removed_accounts = array_diff($before_account_names, $after_account_names);
  $added_accounts   = array_diff($after_account_names, $before_account_names);

  if (sizeof($removed_accounts)) {
    acecrew_tracker_node_log(
      $type, 
      '', 
      '', 
      $item_id, 
      $field_name, 
      $item_title,
      '',
      "!username has removed next accounts : [".implode(', ', $removed_accounts)."] for '!item_title' !item_type"  
    );
  }
  if (sizeof($added_accounts)) {
    acecrew_tracker_node_log(
      $type, 
      '', 
      '', 
      $item_id, 
      $field_name, 
      $item_title,
      '',
      "!username has added next accounts : [".implode(', ', $added_accounts)."] for '!item_title' !item_type"  
    );
  }
}

function acecrew_tracker_cck_offices_flexifield_log($type, $field_name, $node_before, $node_after) {
  $item_id = $node_before->nid;     
  $item_title = acecrew_get_title_field_by_type($type, $node_after);
  $field_name = 'field_add_offices';
  $before_office_names = array();
  $after_office_names = array();
  
  foreach ($node_before->{$field_name} as $key => $office_before) {
    $before_office_name = $node_before->{$field_name}[$key]['value']['field_office_name'][0]['value'];
    $after_office_name = $node_after->{$field_name}[$key]['value']['field_office_name'][0]['value'];
    
    $before_office_address = $node_before->{$field_name}[$key]['value']['field_office_address'][0]['value'];
    $after_office_address = $node_after->{$field_name}[$key]['value']['field_office_address'][0]['value'];

    $before_office_tel = $node_before->{$field_name}[$key]['value']['field_office_tel'][0]['value'];
    $after_office_tel = $node_after->{$field_name}[$key]['value']['field_office_tel'][0]['value'];

    $before_office_mobile = $node_before->{$field_name}[$key]['value']['field_office_mobile'][0]['value'];
    $after_office_mobile = $node_after->{$field_name}[$key]['value']['field_office_mobile'][0]['value'];

    $before_office_postcode = $node_before->{$field_name}[$key]['value']['field_office_post_code'][0]['value'];
    $after_office_postcode = $node_after->{$field_name}[$key]['value']['field_office_post_code'][0]['value'];

    $before_office_contact = $node_before->{$field_name}[$key]['value']['field_office_contact'][0]['value'];
    $after_office_contact = $node_after->{$field_name}[$key]['value']['field_office_contact'][0]['value'];

    $before_office_email = $node_before->{$field_name}[$key]['value']['field_office_email'][0]['email'];
    $after_office_email = $node_after->{$field_name}[$key]['value']['field_office_email'][0]['email'];
    
    
    $before_office_names[] = $before_office_name;    
    // check difference of mobiles and emails only if name is same
    if ($before_office_name == $after_office_name) {
      if ($before_office_address != $after_office_address) {

        acecrew_tracker_node_log(
          $type, 
          $before_office_address, 
          $after_office_address, 
          $item_id, 
          $field_name, 
          $item_title,
          '',
          "!username has changed office '$before_account_name', 'address' from '!before_value' to '!after_value' '!item_title' !item_type"  
        );
      }

      if ($before_office_tel != $after_office_tel) {

        acecrew_tracker_node_log(
          $type, 
          $before_office_tel, 
          $after_office_tel, 
          $item_id, 
          $field_name, 
          $item_title,
          '',
          "!username has changed office '$before_account_name', 'telephone' from '!before_value' to '!after_value' '!item_title' !item_type"  
        );
      }

      if ($before_office_mobile != $after_office_mobile) {

        acecrew_tracker_node_log(
          $type, 
          $before_office_mobile, 
          $after_office_mobile, 
          $item_id, 
          $field_name, 
          $item_title,
          '',
          "!username has changed office '$before_account_name', 'mobile' from '!before_value' to '!after_value' '!item_title' !item_type"  
        );
      }

      if ($before_office_postcode != $after_office_postcode) {

        acecrew_tracker_node_log(
          $type, 
          $before_office_postcode, 
          $after_office_postcode, 
          $item_id, 
          $field_name, 
          $item_title,
          '',
          "!username has changed office '$before_account_name', 'postcode' from '!before_value' to '!after_value' '!item_title' !item_type"  
        );
      }

      if ($before_office_contact != $after_office_contact) {

        acecrew_tracker_node_log(
          $type, 
          $before_office_contact, 
          $after_office_contact, 
          $item_id, 
          $field_name, 
          $item_title,
          '',
          "!username has changed office '$before_account_name', 'contact' from '!before_value' to '!after_value' '!item_title' !item_type"  
        );
      }

      if ($before_office_email != $after_office_email) {

        acecrew_tracker_node_log(
          $type, 
          $before_office_email, 
          $after_office_email, 
          $item_id, 
          $field_name, 
          $item_title,
          '',
          "!username has changed office '$before_account_name', 'email' from '!before_value' to '!after_value' '!item_title' !item_type"  
        );
      }
    }
  }

  foreach ($node_after->{$field_name} as $key => $office_after) {
    $after_office_name = $node_after->{$field_name}[$key]['value']['field_office_name'][0]['value'];
    $after_office_names[] = $after_office_name;
  }

  $removed_offices = array_diff($before_office_names, $after_office_names);
  $added_offices   = array_diff($after_office_names, $before_office_names);

  if (sizeof($removed_offices)) {
    acecrew_tracker_node_log(
      $type, 
      '', 
      '', 
      $item_id, 
      $field_name, 
      $item_title,
      '',
      "!username has removed next offices : [".implode(', ', $removed_offices)."] for '!item_title' !item_type"  
    );
  }
  if (sizeof($added_offices)) {
    acecrew_tracker_node_log(
      $type, 
      '', 
      '', 
      $item_id, 
      $field_name, 
      $item_title,
      '',
      "!username has added next offices : [".implode(', ', $added_offices)."] for '!item_title' !item_type"  
    );
  }
}

function acecrew_tracker_cck_usereference_log($type, $field_name, $node_before, $node_after) {
  $item_id = $node_before->nid;     
  $item_title = acecrew_get_title_field_by_type($type, $node_after);
  $field_name = 'field_blocked_crews';
  $before_blocked_crews_uids = array();
  $after_blocked_crews_uids = array();

  $before_blocked_crews_field = $node_before->{$field_name};
  $after_blocked_crews_field = $node_after->{$field_name};

  foreach ($before_blocked_crews_field as $data) {
    $before_blocked_crews_uids[] = $data['uid'];
  }
  foreach ($after_blocked_crews_field as $data) {
    $after_blocked_crews_uids[] = $data['uid'];
  }

  $removed_crews = array_diff($before_blocked_crews_uids, $after_blocked_crews_uids);
  $added_crews   = array_diff($after_blocked_crews_uids, $before_blocked_crews_uids);

  $removed_crew_names = array();
  $added_crew_names = array();

  if (sizeof($removed_crews)) {
    foreach ($removed_crews as $uid) {
      $name = acecrew_get_username($uid);
      $removed_crew_names[] = $name;
    }

    acecrew_tracker_node_log(
      $type, 
      '', 
      '', 
      $item_id, 
      $field_name, 
      $item_title,
      '',
      "!username has removed next blocked crews : [".implode(', ', $removed_crew_names)."] for '!item_title' !item_type"  
    );
  }
  if (sizeof($added_crews)) {
    foreach ($added_crews as $uid) {
      $name = acecrew_get_username($uid);
      $added_crew_names[] = $name;
    }

    acecrew_tracker_node_log(
      $type, 
      '', 
      '', 
      $item_id, 
      $field_name, 
      $item_title,
      '',
      "!username has added next crews to blocked list : [".implode(', ', $added_crew_names)."] for '!item_title' !item_type"  
    );    
  }  
}

function acecrew_tracker_cck_supplements_multifield_log($type, $field_name, $node_before, $node_after) {
  $item_id = $node_before->nid;       
  $item_title = acecrew_get_title_field_by_type($type, $node_after);  

  $before_suppl_field = $node_before->{$field_name};
  $after_suppl_field = $node_after->{$field_name};

  foreach ($before_suppl_field as $item) {
    $before_suppl_items[$item['nid']] = $item['fields'];
  }
  foreach ($after_suppl_field as $item) {
    $after_suppl_items[$item['nid']] = $item['fields'];
  }
  
  $before_suppl_nids = array_unique(array_keys($before_suppl_items));
  $after_suppl_nids  = array_unique(array_keys($after_suppl_items));

  $removed_ids = array_diff($before_suppl_nids, $after_suppl_nids);
  $added_ids   = array_diff($after_suppl_nids, $before_suppl_nids);
  $common_ids  = array_intersect($after_suppl_nids, $before_suppl_nids);

  $removed_supplements = array();
  foreach ($removed_ids as $nid) {
    $removed_supplements[] = get_node_title($nid);
  }

  $added_supplements = array();
  foreach ($added_ids as $nid) {
    $added_supplements[] = get_node_title($nid);
  }

  if (sizeof($removed_ids)) {
    acecrew_tracker_node_log(
      $type, 
      $before_value, 
      $after_value, 
      $item_id, 
      $field_name,  
      $item_title,
      '',
      "!username unticked supplement '".implode(', ', $removed_supplements)."' for '!item_title' !item_type"
    );
  }
  if (sizeof($added_ids)) {
    acecrew_tracker_node_log(
      $type, 
      $before_value, 
      $after_value, 
      $item_title,       
      $item_id, 
      $field_name,
      $item_title,
      '',
      "!username ticked supplement '".implode(', ', $added_supplements)."' for '!item_title' !item_type"
    );
  }

  foreach ($common_ids as $nid) {
    if ($before_suppl_items[$nid] != $after_suppl_items[$nid]) {
      $supplement_title = get_node_title($nid);      
      $before_qty = json_decode($before_suppl_items[$nid]);      
      $after_qty = json_decode($after_suppl_items[$nid]);      
      acecrew_tracker_node_log(
        $type, 
        $before_qty->quantity, 
        $after_qty->quantity, 
        $item_id, 
        $field_name,
        $item_title,  
        '',
        "!username changed qty of supplement '$supplement_title' from '!before_value' to '!after_value' '!item_title' !item_type"
      );
    }
  } 
}
