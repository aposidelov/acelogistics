<?php

function op_custom_field_type_update_form($form_state) {
	$form = array();
	
	$form['field_name'] = array(
		'#type' => 'textfield',
		'#default_value' => 'field_session_job_nid',
		'#title' => t('Field Name'),
		'#description' => t('Field for that you are going to change a type'),
	);

	$form['save'] = array(
		'#type' => 'submit',
		'#value' => 'Save',  
	);

	return $form;
}

function op_custom_field_type_update_form_submit($form, &$form_state) {
	$int_field_name = $form_state['values']['field_name'];	
	$ret = array();
	// content_type_job_session - job_nid
	/*acecrew_update_cck_field_type(
		'field_session_job_nid',
		'content_type_job_session', 
		'integer', 
		'field_job_number'
	);
	db_add_index($ret, 'content_type_job_session', 'job_id', array('field_session_job_nid_value'));
	
	// content_type_job - client_id
	acecrew_update_cck_field_type(
		'field_job_client_name',
		'content_type_job',
		'integer', 
		'field_job_number'
	);
	db_add_index($ret, 'content_type_job', 'client', array('field_job_client_name_value'));
	// content_type_job - venue_id
	acecrew_update_cck_field_type(
		'field_job_venue',
		'content_type_job', 
		'integer', 
		'field_job_number'
	);
	db_add_index($ret, 'content_type_job', 'venue', array('field_job_venue_value'));	
	// content_type_client - field_client_id
	acecrew_update_cck_field_type(
		'field_client_id',
		'content_type_client', 
		'integer', 
		'field_job_number'
	);
	db_add_index($ret, 'content_type_client', 'field_client_id_value', array('field_client_id_value'));
	// content_type_venue - field_venue_id
	acecrew_update_cck_field_type(
		'field_venue_id',
		'content_type_venue', 
		'integer', 
		'field_job_number'
	);
	db_add_index($ret, 'content_type_venue', 'field_venue_id_value', array('field_venue_id_value'));
	
	db_add_index($ret, 'acecrew_job_invoices', 'job_id', array('job_id'));	
	db_add_index($ret, 'crew_call', 'uid', array('uid'));
	db_add_index($ret, 'crew_call', 'jsid', array('jsid'));
	db_add_index($ret, 'crew_call', 'uid_jsid', array('uid','jsid'));
	db_add_index($ret, 'crew_js_supplement', 'jsid', array('jsid'));
	db_add_index($ret, 'crew_js_supplement', 'uid_jsid', array('uid','jsid'));
	*/

	drupal_set_message($ret);
}