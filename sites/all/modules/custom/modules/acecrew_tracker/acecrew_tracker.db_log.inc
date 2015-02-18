<?php

function acecrew_tracker_review_log($type, $contact_email, $contact_name, $job_nid = '', $job_number = '', $message_template = '', $uid = '') {
  $created = time();
  if (empty($message_template)) {
    $message_template = "!username sent a review to !contact_name (!contact_email) for '!job_number' job";    
  }
  
  $user = acecrew_get_user($uid);  

  $message = t($message_template, 
    array(
      '!username'       => $user->name,           
      '!job_number'     => $job_number,
      '!item_type'      => $type,
      '!contact_email'  => $contact_email,
      '!contact_name'   => $contact_name,
    )
  );

  db_query("INSERT INTO {acecrew_tracker_log} (uid, type, message, created, field_name, item1_id) 
    VALUES (%d, '%s', '%s', %d, '%s', %d)", 
    $user->uid, 
    $type, 
    $message, 
    $created,
    '',    
    $job_nid
  );
}

/**
 * [acecrew_tracker_iq_log description]
 * @param  [type] $type       variants: 'invoice' or 'quote'
 * @param  string $inv_quo_id [description]
 * @param  string $job_nid    [description]
 * @param  string $uid        [description]
 * @return [type]             [description]
 */
function acecrew_tracker_iq_log($type, $inv_quo_id = '', $job_nid = '', $job_number = '', $message_template = '', $uid = '') {
  $created = time();
  if (empty($message_template)) {
    $message_template = "!username generated !item_type (!inv_quo_id) for '!job_number' job";    
  }
  
  $user = acecrew_get_user($uid);  

  $message = t($message_template, 
    array(
      '!username'   => $user->name,           
      '!job_number' => $job_number,
      '!item_type'  => $type,
      '!inv_quo_id' => $inv_quo_id,
    )
  );

  db_query("INSERT INTO {acecrew_tracker_log} (uid, type, message, created, field_name, item1_id, item2_id) 
    VALUES (%d, '%s', '%s', %d, '%s', %d, %d)", 
    $user->uid, 
    $type, 
    $message, 
    $created,
    '',
    $inv_quo_id,
    $job_nid
  );
}

/**
 * Log for common nodes (job, call, client, venue, supplement)
 * @param  [string] $type             [variants: job, call, client, venue, supplement]
 * @param  [type] $before_value     [description]
 * @param  [type] $after_value      [description]
 * @param  string $item_id          [description]
 * @param  string $field_name       [description]
 * @param  string $item_title       [description]
 * @param  string $field_label      [description]
 * @param  string $message_template [description]
 * @param  string $uid              [description]
 * @return [type]                   [description]
 */
function acecrew_tracker_node_log($type, $before_value, $after_value, $item_nid = '', $field_name = '', $item_title = '', $field_label = '', $message_template = '', $uid = '') {
  $created = time();
  if (empty($message_template)) {
    $message_template = "!username changed '!field_label' from '!before_value' to '!after_value' for '!item_title' !item_type";    
  }
  
  $user = acecrew_get_user($uid);

  if ($field_name == 'title') {
    $field_label = 'Title';
  } elseif (empty($field_label)) {
    $field_label = acecrew_get_label_by_fieldname($field_name);  
  }

  $message = t($message_template, 
    array(
      '!username'      => $user->name, 
      '!field_label'     => $field_label, 
      '!before_value'   => $before_value, 
      '!after_value'    => $after_value,
      '!item_title' => $item_title,
      '!item_type' => $type,
    )
  );

  db_query("INSERT INTO {acecrew_tracker_log} (uid, type, message, created, field_name, item1_id) 
    VALUES (%d, '%s', '%s', %d, '%s', %d)", 
    $user->uid, 
    $type, 
    $message, 
    $created,
    $field_name,
    $item_nid
  );
}

/**
 * Log for user profile fields
 * @param  [string] $type             [variants: job, call, client, venue, supplement]
 * @param  [type] $before_value     [description]
 * @param  [type] $after_value      [description]
 * @param  string $item_id          [description]
 * @param  string $field_name       [description]
 * @param  string $item_title       [description]
 * @param  string $field_label      [description]
 * @param  string $message_template [description]
 * @param  string $uid              [description]
 * @return [type]                   [description]
 */
function acecrew_tracker_profile_log($type, $before_value, $after_value, $item_nid = '', $field_name = '', $item_title = '', $field_label = '', $message_template = '', $uid = '') {
  $created = time();
  if (empty($message_template)) {
    $message_template = "!username changed '!field_label' from '!before_value' to '!after_value' for '!item_title' !item_type";    
  }
  
  $user = acecrew_get_user($uid);

  if (empty($field_label)) {
    $field_label = acecrew_get_profile_label($field_name);  
  }
  if (empty($field_label)) {
    $field_label = ucfirst($field_name);
  }


  $message = t($message_template, 
    array(
      '!username'      => $user->name, 
      '!field_label'     => $field_label, 
      '!before_value'   => $before_value, 
      '!after_value'    => $after_value,
      '!item_title' => $item_title,
      '!item_type' => $type,
    )
  );

  db_query("INSERT INTO {acecrew_tracker_log} (uid, type, message, created, field_name, item1_id) 
    VALUES (%d, '%s', '%s', %d, '%s', %d)", 
    $user->uid, 
    $type, 
    $message, 
    $created,
    $field_name,
    $item_nid
  );
}