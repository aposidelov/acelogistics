<?php

function acecrew_get_label_by_fieldname($field_name) {
  $field = content_fields($field_name);
  return $field['widget']['label'];
}

function acecrew_get_profile_label($field_name) {
	$label = db_result(db_query("SELECT title FROM {profile_fields} WHERE name = '%s'", $field_name));	
	return $label;
}

function acecrew_get_profile_list($field_name) {	
	// TODO: возвращает user profile список по id поля (тип Selection)
	$options = db_result(db_query("SELECT options FROM {profile_fields} WHERE name = '%s'", $field_name));	
	$options = trim($options);
	$options = explode("\n", $options);
	$options = array_filter($options, 'trim');	
	$result = array();
	foreach ($options as $option) {
		$option = trim($option);
		$result[$option] = $option;
	}
	$options = array('0' => '--') + $result;

	return $options;
}

function acecrew_get_title_field_by_type($type, $object) {
  if ($type == 'job') {    
    return $object->{'field_job_number'}[0]["value"];
  } elseif ($type == 'call') {
    return $object->{'field_session_callid'}[0]["value"];
  } elseif ($type == 'client') {
  	return $object->{'field_client_name'}[0]["value"];
  } elseif ($type == 'profile') {
  	return $object->{'name'};
  } elseif ($type == 'bookoff') {
  	$owner_uid = $object->{'field_ub_owner'}[0]["uid"];
  	return acecrew_get_username($owner_uid);
  }
  
  return $object->{'title'};
}

function acecrew_get_user($uid = '') {
  if (empty($uid)) {
    global $user;
  } else {
    $user = user_load($uid);
  }

  return $user;
}

function acecrew_get_username($uid) {
	$name = db_result(db_query("SELECT name FROM {users} WHERE uid = %d", $uid));
	return $name;
}