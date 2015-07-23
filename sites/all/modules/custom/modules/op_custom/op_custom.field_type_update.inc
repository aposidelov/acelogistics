<?php

function op_custom_field_type_update_form($form_state) {
	$form = array();
	
	$form['field_name'] = array(
		'#type' => 'textfield',
		'#default_value' => 'field_test_int',
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
	$decimal_field_name = 'field_fine_rate_amount';

	// we will copy decimal settings from another decimal field
	$decimal_field_data = db_fetch_array(db_query('SELECT * 
																	FROM {content_node_field} 
																	WHERE field_name = "%s"', 
																	$decimal_field_name));

	// we will copy decimal settings from another decimal field instance
	$decimal_field_instance_data = db_fetch_array(db_query('SELECT * 
																	FROM {content_node_field_instance} 
																	WHERE field_name = "%s"', 
																	$decimal_field_name));

	// update field in content_node_field table with existing 
	// data of another decimal field
	db_query('UPDATE {content_node_field} 
		SET type = "%s", 
		global_settings = "%s", 
		db_columns = "%s"
		WHERE field_name = "%s"', 
		$decimal_field_data['type'],
		$decimal_field_data['global_settings'],
		$decimal_field_data['db_columns'],
		$int_field_name);
	
	// update field in content_node_field_istance table with
	// existing data of another decimal field
	db_query('UPDATE {content_node_field_instance} 
		SET display_settings = "%s"
		WHERE field_name = "%s"', 
		$decimal_field_instance_data['display_settings'],
		$int_field_name
	);
	
	$ret = array();
	$field_name = $int_field_name . '_value';
	
	db_change_field($ret, 'content_type_story', 
		$field_name, $field_name, 
		array('type' => 'numeric', 'precision' => 10, 
			'scale' => 2, 'not null' => FALSE)
	);	
	
	//dsm($int_field_data);
	//dsm($decimal_field_data);

	//dsm($int_field_instance_data);
	//dsm($decimal_field_instance_data);

	//{content_node_field_instance}



	drupal_set_message('sss');
}