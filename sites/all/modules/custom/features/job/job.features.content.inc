<?php

/**
 * Implementation of hook_content_default_fields().
 */
function job_content_default_fields() {
  $fields = array();

  // Exported field: field_invoice_notes
  $fields['job-field_invoice_notes'] = array(
    'field_name' => 'field_invoice_notes',
    'type_name' => 'job',
    'display_settings' => array(
      'weight' => '31',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
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
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '5',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_invoice_notes][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Invoice Notes',
      'weight' => '58',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_job_booked_by
  $fields['job-field_job_booked_by'] = array(
    'field_name' => 'field_job_booked_by',
    'type_name' => 'job',
    'display_settings' => array(
      'weight' => '32',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
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
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_job_booked_by][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Booked By',
      'weight' => '59',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_job_client_contact
  $fields['job-field_job_client_contact'] = array(
    'field_name' => 'field_job_client_contact',
    'type_name' => 'job',
    'display_settings' => array(
      'weight' => '24',
      'parent' => '',
      'label' => array(
        'format' => 'inline',
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
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '$result = db_query(db_rewrite_sql("SELECT `vid`, `field_client_contact_name_value` FROM {content_type_client_contact}"));
$items[0] = \'D\';
while ($item = db_fetch_object($result)) {
$items[$item->vid] = $item->field_client_contact_name_value;
}
return $items;',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Client contact',
      'weight' => '49',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_job_client_name
  $fields['job-field_job_client_name'] = array(
    'field_name' => 'field_job_client_name',
    'type_name' => 'job',
    'display_settings' => array(
      'weight' => '23',
      'parent' => '',
      'label' => array(
        'format' => 'inline',
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
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => 0,
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '$result = db_query(db_rewrite_sql("SELECT `nid`, `field_client_name_value`,  `field_client_id_value` FROM `drupal_content_type_client` WHERE 1 ORDER BY `field_client_name_value` ASC"));
while ($item = db_fetch_object($result)) {
$items[$item->field_client_id_value] = $item->field_client_name_value;
}
return $items;',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_job_client_name][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'size' => '60',
      'autocomplete_match' => 'contains',
      'autocomplete_case' => '0',
      'i18n_flddata' => 0,
      'label' => 'Client name',
      'weight' => '48',
      'description' => '',
      'type' => 'autocomplete_widgets_allowvals',
      'module' => 'autocomplete_widgets',
    ),
  );

  // Exported field: field_job_comments
  $fields['job-field_job_comments'] = array(
    'field_name' => 'field_job_comments',
    'type_name' => 'job',
    'display_settings' => array(
      'weight' => '30',
      'parent' => '',
      'label' => array(
        'format' => 'above',
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
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => '1',
      'size' => 60,
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_job_comments][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Comments',
      'weight' => '57',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_job_created_by
  $fields['job-field_job_created_by'] = array(
    'field_name' => 'field_job_created_by',
    'type_name' => 'job',
    'display_settings' => array(
      'weight' => '33',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
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
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_job_created_by][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Created By',
      'weight' => '60',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_job_date
  $fields['job-field_job_date'] = array(
    'field_name' => 'field_job_date',
    'type_name' => 'job',
    'display_settings' => array(
      'weight' => '27',
      'parent' => '',
      'label' => array(
        'format' => 'inline',
      ),
      'teaser' => array(
        'format' => 'medium',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'medium',
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
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'datestamp',
    'required' => '1',
    'multiple' => '0',
    'module' => 'date',
    'active' => '1',
    'granularity' => array(
      'year' => 'year',
      'month' => 'month',
      'day' => 'day',
    ),
    'timezone_db' => '',
    'tz_handling' => 'none',
    'todate' => '',
    'repeat' => 0,
    'repeat_collapsed' => '',
    'default_format' => 'medium',
    'widget' => array(
      'default_value' => 'blank',
      'default_value_code' => '',
      'default_value2' => 'same',
      'default_value_code2' => '',
      'input_format' => 'j M Y',
      'input_format_custom' => '',
      'increment' => '1',
      'text_parts' => array(),
      'year_range' => '-3:+3',
      'label_position' => 'above',
      'label' => 'Date',
      'weight' => '52',
      'description' => '',
      'type' => 'date_popup',
      'module' => 'date',
    ),
  );

  // Exported field: field_job_discount
  $fields['job-field_job_discount'] = array(
    'field_name' => 'field_job_discount',
    'type_name' => 'job',
    'display_settings' => array(
      'weight' => '29',
      'parent' => '',
      'label' => array(
        'format' => 'inline',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
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
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_job_discount][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Discount',
      'weight' => '55',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_job_discount_desc
  $fields['job-field_job_discount_desc'] = array(
    'field_name' => 'field_job_discount_desc',
    'type_name' => 'job',
    'display_settings' => array(
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
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
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
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_job_discount_desc][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Discount description',
      'weight' => '56',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_job_number
  $fields['job-field_job_number'] = array(
    'field_name' => 'field_job_number',
    'type_name' => 'job',
    'display_settings' => array(
      'weight' => '22',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
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
    ),
    'widget_active' => '1',
    'type' => 'number_integer',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_job_number][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Job Number',
      'weight' => '47',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_job_po_number
  $fields['job-field_job_po_number'] = array(
    'field_name' => 'field_job_po_number',
    'type_name' => 'job',
    'display_settings' => array(
      'weight' => '28',
      'parent' => '',
      'label' => array(
        'format' => 'inline',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
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
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_job_po_number][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'PO Number',
      'weight' => '53',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_job_status
  $fields['job-field_job_status'] = array(
    'field_name' => 'field_job_status',
    'type_name' => 'job',
    'display_settings' => array(
      'weight' => '26',
      'parent' => '',
      'label' => array(
        'format' => 'inline',
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
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => 'return acecrew_get_statuses();',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Job status',
      'weight' => '51',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_job_venue
  $fields['job-field_job_venue'] = array(
    'field_name' => 'field_job_venue',
    'type_name' => 'job',
    'display_settings' => array(
      'weight' => '25',
      'parent' => '',
      'label' => array(
        'format' => 'inline',
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
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '101' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => 0,
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => '$result = db_query(db_rewrite_sql("SELECT `nid`, `field_venue_name_value`,  `field_venue_id_value` FROM `drupal_content_type_venue` WHERE 1 ORDER BY `field_venue_name_value` ASC"));
while ($item = db_fetch_object($result)) {
$items[$item->field_venue_id_value] = $item->field_venue_name_value;
}
return $items;',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_job_venue][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'size' => '60',
      'autocomplete_match' => 'contains',
      'autocomplete_case' => '0',
      'i18n_flddata' => 0,
      'label' => 'Venue',
      'weight' => '50',
      'description' => '',
      'type' => 'autocomplete_widgets_allowvals',
      'module' => 'autocomplete_widgets',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Booked By');
  t('Client contact');
  t('Client name');
  t('Comments');
  t('Created By');
  t('Date');
  t('Discount');
  t('Discount description');
  t('Invoice Notes');
  t('Job Number');
  t('Job status');
  t('PO Number');
  t('Venue');

  return $fields;
}
