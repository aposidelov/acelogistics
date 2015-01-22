<?php

define('DEFAULT_2_RATE', '_per_hour');
define('DEFAULT_3_RATE', '_per_hour_3');

//define('DEFAULT_2_GROUP', 'group_default_2');
define('DEFAULT_2_GROUP', 'group_default_crew_payments');
//define('DEFAULT_3_GROUP', 'group_default_3');
define('DEFAULT_3_GROUP', 'group_default_crew_payme_3');
//define('ADMIN_CONTENT_TYPE', 'page');
define('ADMIN_CONTENT_TYPE', 'admin_settings');

//define('ADMIN_NID', 10184);
define('ADMIN_NID', 752);

//define('ADMIN_CREW_RATES_TEXTAREA', 'field_admins_crewrates2');
define('ADMIN_CREW_RATES_TEXTAREA', 'field_admins_crewrates');

function op_custom_admin_settins_cck_form($form_state) {
  $form = array();
  $form['rate_index'] = array(
    '#type' => 'textfield',
    '#default_value' => '0.0',
    '#title' => t('Rate index (per hour)'),
    '#prefix' => '£',
    '#description' => t('For example: 5.5, 7, 10, 10.0, 12.5'),
  );
  $form['rate_value_2'] = array(
    '#type' => 'textfield',
    '#default_value' => '0',
    '#prefix' => '£',
    '#title' => t('Rate value (per hour) for Default 2'),
    '#description' => t('For example: 25, 30, 45'),
  );

  $form['rate_value_3'] = array(
    '#type' => 'textfield',
    '#default_value' => '0',
    '#prefix' => '£',
    '#title' => t('Rate value (per hour)  for Default 3'),
    '#description' => t('For example: 25, 30, 45'),
  );
  $form['type'] = array(
    '#type' => 'radios',
    '#title' => t('Type'),
    '#options' => array(
      'both' => t('Both'),
      DEFAULT_2_RATE => t('Default 2 hour'),
      DEFAULT_3_RATE => t('Default 3 hour'),
    ),
    '#default_value' => 'both',
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

  return $form;
}

function op_admin_get_rates($input_group) {
  $result = array();
  foreach (fieldgroup_groups(ADMIN_CONTENT_TYPE) as $group_name => $group) {
    if ($group_name == $input_group) {
      $fields = array_keys($group['fields']);
    }
  }
  foreach ($fields as $value) {
    $value = str_replace('field_', '', $value);
    $value = str_replace('_per_hour', '', $value);
    $value = str_replace('_', '.', $value);
    $result[] = $value;
  }
  asort($result);

  return implode("\r\n", $result);
  //drupal_set_message('<pre>'.print_r($result, TRUE).'</pre>');
  //$node = node_load(752);
  //drupal_set_message('<pre>'.print_r($node, TRUE).'</pre>');
}

function op_custom_admin_settins_cck_form_submit($form, &$form_state) {
  //$is = content_fields('field_test_decimal', ADMIN_CONTENT_TYPE);
  //drupal_set_message('<pre>'.print_r($is, TRUE).'</pre>');
  //return;

  $rate_index = $form_state['values']['rate_index'];
  $rate_value_2 = $form_state['values']['rate_value_2'];
  $rate_value_3 = $form_state['values']['rate_value_3'];
  $type = $form_state['values']['type'];

  if (empty($rate_index) || !$rate_index || $rate_index == '0.0')  {
    drupal_set_message(t('Rate index has not been sent correctly.'));
    return;
  }
  $default_2_rate = DEFAULT_2_RATE;
  $default_3_rate = DEFAULT_3_RATE;
  $default_2_group = DEFAULT_2_GROUP;
  $default_3_group = DEFAULT_3_GROUP;
  $admin_content_type = ADMIN_CONTENT_TYPE;
  $field_textarea = ADMIN_CREW_RATES_TEXTAREA;
  $field_name_2  = op_admin_get_field_name($rate_index, $default_2_rate);
  $field_name_3  = op_admin_get_field_name($rate_index, $default_3_rate);
  $is_field_name_2 = content_fields($field_name_2, $admin_content_type);
  $is_field_name_3 = content_fields($field_name_3, $admin_content_type);

  //$is = content_fields('field_8_per_hour', $admin_content_type);
  //drupal_set_message('<pre>'.print_r($is, TRUE).'</pre>');
  //return;

  $node = new stdClass();
  if ($type == 'both') {
    $node = node_load(ADMIN_NID);
    if (empty($is_field_name_2)) {
      op_create_rate_field($rate_index, $rate_value_2, $default_2_rate);
      fieldgroup_update_fields(array('type_name' => $admin_content_type, 'field_name' => $field_name_2, 'group' => $default_2_group));
    }
    $label = op_admin_get_field_label($rate_index, $default_2_rate);
    $node->{$field_name_2}[0]['value'] = $rate_value_2;
    $rates = op_admin_get_rates(DEFAULT_2_GROUP);
    $node->{$field_textarea}[0]['value'] = $rates;
    drupal_set_message($label . ' (' . $field_name_2 . ') field has been created.');
    if (empty($is_field_name_3)) {
      op_create_rate_field($rate_index, $rate_value_2, $default_3_rate);
      fieldgroup_update_fields(array('type_name' => $admin_content_type, 'field_name' => $field_name_3, 'group' => $default_3_group));
    }
    $label = op_admin_get_field_label($rate_index, $default_3_rate);
    $node->{$field_name_3}[0]['value'] = $rate_value_3;
    drupal_set_message($label . ' (' . $field_name_3 . ') field has been created.');
    node_save($node);
    $rate = op_admin_get_rates(DEFAULT_2_GROUP);
    db_query('UPDATE {content_type_admin_settings} SET field_admins_crewrates_value = "%s" WHERE nid = %d', $rate, $node->nid);
  } else {
    if ($type == $default_2_rate) {
      $field_name = $field_name_2;
      $group =  $default_2_group;
      $rate_value = $rate_value_2;
    } elseif ($type == $default_3_rate) {
      $field_name = $field_name_3;
      $group =  $default_3_group;
      $rate_value = $rate_value_3;
    }
    $label = op_admin_get_field_label($rate_index, $type);
    $is_field_name = content_fields($field_name, $admin_content_type);
    if (empty($is_field_name)) {
      op_create_rate_field($rate_index, $rate_value, $type);
      fieldgroup_update_fields(array('type_name' => $admin_content_type, 'field_name' => $field_name, 'group' => $group));
    }
    op_admin_set_value($field_name, $rate_value);
    drupal_set_message($label . ' (' . $field_name .') field has been created.');
  }
  drupal_set_message('Place fields in right order');
  drupal_goto('admin/content/node-type/'.str_replace('_', '-', ADMIN_CONTENT_TYPE).'/fields');
}

function op_admin_set_value($field_name, $value) {
  $node = node_load(ADMIN_NID);
  $node->{$field_name}[0]['value'] = $value;
  node_save($node);
  $rate = op_admin_get_rates(DEFAULT_2_GROUP);
  db_query('UPDATE {content_type_admin_settings} SET field_admins_crewrates_value = "%s" WHERE nid = %d', $rate, $node->nid);
}

function op_admin_get_field_name($rate_index, $type) {
  // remove .0 string: if 20.0 = 20, 10.0 = 10, 1.5 = 1.5
  $rate_index   = (float)$rate_index;
  $rate_index   = str_replace('.0','', $rate_index);
  // replace dots with cemi-colons
  $rate_index   = str_replace('.','_', $rate_index);
  // conbine field name
  $field_name   = 'field_' . $rate_index . $type;

  return $field_name;
}

function op_admin_get_field_label($rate_index, $type) {
  // generate label
  $rate_index   = (float)$rate_index;
  $field_label  = str_replace('field_','', $rate_index);
  $field_label  = str_replace('_',' ', $field_label);
  $field_label  = '£' . $field_label . ' Per Hour';

  return $field_label;
}

function op_create_rate_field($rate_index, $rate_value, $type) {

  /*
  **1) Если выбрать 20.0 то генерится field_20_0_per_hour а должно генериться field_20_per_hour;
  **2) Если выбрать 20.0 то название поля генерится '20 0' а должно '£20 Per Hour';
  **3) Если выбрать 20.5 то название поля генерится '20 5' а должно '£20.5 Per Hour';
  ***4) Поле Default 2 должно ложиться в группу 'group_default_crew_payments', Поле Default 3 должно ложиться в группу 'group_default_crew_payme_3'.
  **5) В ноде 752 должно заполняться только что созданное поле значением по умолчанию;
  ***6) Поле CREW RATES должно быть заполнено Rate index значением .. причем значения должно быть отсортированы qsort ?
   */

  $field_name  = op_admin_get_field_name($rate_index, $type);
  $field_label  = op_admin_get_field_label($rate_index, $type);

  $type         = ADMIN_CONTENT_TYPE;

  $field = array(
  'field_name' => $field_name,
  'type_name' => $type,
  'display_settings' =>
    array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'inline' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'modal' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      2 => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      3 => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      4 => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      5 => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      100 => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      101 => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => 1,
    'type' => 'number_decimal',
    'required' => 0,
    'multiple' => 0,
    'db_storage' => 1,
    'module' => 'number',
    'active' => 1,
    'locked' => 0,
    'columns' =>
      array(
        'value' =>
        array (
          'type' => 'numeric',
          'precision' => 10,
          'scale' => 2,
          'not null' => false,
          'sortable' => true,
        ),
      ),
    'prefix' => '£',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'precision' => 10,
    'scale' => 2,
    'decimal' => '.',
    'widget' => array(
      'default_value' => array(
        array(
          'value' => '',
          '_error_element' => 'default_value_widget]['.$field_name.'][0][value'
        ),
      ),
      'default_value_php' => NULL,
      'label' => $field_label,
      'weight' => 32,
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  module_load_include('inc', 'content', 'includes/content.crud');
  content_field_instance_create($field);

  return true;
}
