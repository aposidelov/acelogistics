<?php

/**
 * Implementation of hook_content_default_fields().
 */
function clients_content_default_fields() {
  $fields = array();

  // Exported field: field_2_hour_default
  $fields['client-field_2_hour_default'] = array(
    'field_name' => 'field_2_hour_default',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '169',
      'parent' => 'group_client_config',
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
    'type' => 'number_decimal',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '£',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'precision' => '10',
    'scale' => '2',
    'decimal' => '.',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_2_hour_default][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => '2 Hour Default',
      'weight' => '40',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_3_hour_default
  $fields['client-field_3_hour_default'] = array(
    'field_name' => 'field_3_hour_default',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '170',
      'parent' => 'group_client_config',
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
    'type' => 'number_decimal',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '£',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'precision' => '10',
    'scale' => '2',
    'decimal' => '.',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_3_hour_default][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => '3 Hour Default',
      'weight' => '41',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_add_accounts
  $fields['client-field_add_accounts'] = array(
    'field_name' => 'field_add_accounts',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '161',
      'parent' => 'group_client_contact',
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
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'flexifield',
    'required' => '0',
    'multiple' => '1',
    'module' => 'flexifield',
    'active' => '1',
    'item_types' => array(
      'accounts_details' => 'accounts_details',
      'additional_offices' => 0,
      'client' => 0,
      'client_contact' => 0,
      'crew_job_session' => 0,
      'crew_payrates' => 0,
      'crew_file_uploads' => 0,
      'fines' => 0,
      'fines_rates' => 0,
      'hidden_pages' => 0,
      'image' => 0,
      'invoice' => 0,
      'job' => 0,
      'job_session' => 0,
      'job_supplement' => 0,
      'page' => 0,
      'panel' => 0,
      'product' => 0,
      'story' => 0,
      'uniform' => 0,
      'venue' => 0,
    ),
    'widget' => array(
      'disable_tabledrag' => 0,
      'disable_tabledrag_children' => NULL,
      'default_value' => array(
        '0' => '',
      ),
      'default_value_php' => NULL,
      'label' => 'Accounts',
      'weight' => '161',
      'description' => '',
      'type' => 'flexifield_default_widget',
      'module' => 'flexifield',
    ),
  );

  // Exported field: field_add_offices
  $fields['client-field_add_offices'] = array(
    'field_name' => 'field_add_offices',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '161',
      'parent' => 'group_client_offices',
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
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'flexifield',
    'required' => '0',
    'multiple' => '1',
    'module' => 'flexifield',
    'active' => '1',
    'item_types' => array(
      'additional_offices' => 'additional_offices',
      'accounts_details' => 0,
      'client' => 0,
      'client_contact' => 0,
      'crew_job_session' => 0,
      'crew_payrates' => 0,
      'crew_file_uploads' => 0,
      'fines' => 0,
      'fines_rates' => 0,
      'hidden_pages' => 0,
      'image' => 0,
      'invoice' => 0,
      'job' => 0,
      'job_session' => 0,
      'job_supplement' => 0,
      'page' => 0,
      'panel' => 0,
      'product' => 0,
      'story' => 0,
      'uniform' => 0,
      'venue' => 0,
    ),
    'widget' => array(
      'disable_tabledrag' => 0,
      'disable_tabledrag_children' => NULL,
      'default_value' => array(
        '0' => '',
      ),
      'default_value_php' => NULL,
      'label' => 'Offices',
      'weight' => '161',
      'description' => '',
      'type' => 'flexifield_default_widget',
      'module' => 'flexifield',
    ),
  );

  // Exported field: field_blocked_crews
  $fields['client-field_blocked_crews'] = array(
    'field_name' => 'field_blocked_crews',
    'type_name' => 'client',
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
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'userreference',
    'required' => '0',
    'multiple' => '1',
    'module' => 'userreference',
    'active' => '1',
    'referenceable_roles' => array(
      '2' => 0,
      '4' => 0,
      '5' => 0,
      '3' => 0,
    ),
    'referenceable_status' => '',
    'advanced_view' => 'crews_active',
    'advanced_view_args' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'uid' => NULL,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Blocked Crews',
      'weight' => '44',
      'description' => '',
      'type' => 'multiselect_select',
      'module' => 'multiselect',
    ),
  );

  // Exported field: field_client_company_address
  $fields['client-field_client_company_address'] = array(
    'field_name' => 'field_client_company_address',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '158',
      'parent' => 'group_antoherab',
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
          '_error_element' => 'default_value_widget][field_client_company_address][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Address',
      'weight' => '158',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_client_company_contact
  $fields['client-field_client_company_contact'] = array(
    'field_name' => 'field_client_company_contact',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '160',
      'parent' => 'group_client_contact',
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
      'rows' => 5,
      'size' => '20',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_client_company_contact][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Default Contact',
      'weight' => '160',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_client_company_email
  $fields['client-field_client_company_email'] = array(
    'field_name' => 'field_client_company_email',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '160',
      'parent' => 'group_client_contact_details',
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
    'type' => 'email',
    'required' => '0',
    'multiple' => '0',
    'module' => 'email',
    'active' => '1',
    'widget' => array(
      'size' => '20',
      'default_value' => array(
        '0' => array(
          'email' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Email',
      'weight' => '160',
      'description' => '',
      'type' => 'email_textfield',
      'module' => 'email',
    ),
  );

  // Exported field: field_client_company_fax
  $fields['client-field_client_company_fax'] = array(
    'field_name' => 'field_client_company_fax',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '162',
      'parent' => 'group_client_contact_details',
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
          '_error_element' => 'default_value_widget][field_client_company_fax][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Fax',
      'weight' => '162',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_client_company_notes
  $fields['client-field_client_company_notes'] = array(
    'field_name' => 'field_client_company_notes',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '162',
      'parent' => 'group_client_notes',
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
    'multiple' => '1',
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
          '_error_element' => 'default_value_widget][field_client_company_notes][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Notes',
      'weight' => '162',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_client_company_number
  $fields['client-field_client_company_number'] = array(
    'field_name' => 'field_client_company_number',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '164',
      'parent' => 'group_client_config',
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
          '_error_element' => 'default_value_widget][field_client_company_number][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Company Number',
      'weight' => '35',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_client_company_postcode
  $fields['client-field_client_company_postcode'] = array(
    'field_name' => 'field_client_company_postcode',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '159',
      'parent' => 'group_antoherab',
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
      'rows' => 5,
      'size' => '10',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_client_company_postcode][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Post Code',
      'weight' => '159',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_client_company_telephone
  $fields['client-field_client_company_telephone'] = array(
    'field_name' => 'field_client_company_telephone',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '161',
      'parent' => 'group_client_contact_details',
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
      'rows' => 5,
      'size' => '20',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_client_company_telephone][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Telephone',
      'weight' => '161',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_client_contact
  $fields['client-field_client_contact'] = array(
    'field_name' => 'field_client_contact',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '163',
      'parent' => 'group_client_contact_details',
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
    'type' => 'flexifield',
    'required' => '0',
    'multiple' => '1',
    'module' => 'flexifield',
    'active' => '1',
    'item_types' => array(
      'client_contact' => 'client_contact',
      'client' => 0,
      'crew_payrates' => 0,
      'crew_file_uploads' => 0,
      'hidden_pages' => 0,
      'image' => 0,
      'invoice' => 0,
      'page' => 0,
      'story' => 0,
    ),
    'widget' => array(
      'disable_tabledrag' => 0,
      'disable_tabledrag_children' => NULL,
      'default_value' => array(
        '0' => '',
      ),
      'default_value_php' => NULL,
      'label' => 'Contact',
      'weight' => '163',
      'description' => '',
      'type' => 'flexifield_default_widget',
      'module' => 'flexifield',
    ),
  );

  // Exported field: field_client_id
  $fields['client-field_client_id'] = array(
    'field_name' => 'field_client_id',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '36',
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
    'module' => 'serial',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'label' => 'Client ID',
      'weight' => '37',
      'description' => '',
      'type' => 'serial_widget',
      'module' => 'serial',
    ),
  );

  // Exported field: field_client_job_call_cb
  $fields['client-field_client_job_call_cb'] = array(
    'field_name' => 'field_client_job_call_cb',
    'type_name' => 'client',
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
      '5' => array(
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
          '_error_element' => 'default_value_widget][field_client_job_call_cb][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Client Job Call Comments Box',
      'weight' => '38',
      'description' => '',
      'type' => 'text_textarea',
      'module' => 'text',
    ),
  );

  // Exported field: field_client_logo
  $fields['client-field_client_logo'] = array(
    'field_name' => 'field_client_logo',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '163',
      'parent' => 'group_client_config',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'listing_image_linked',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'listing_image_linked',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '100' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '101' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '0',
      'min_resolution' => '0',
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'label' => 'Logo',
      'weight' => '34',
      'description' => '',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_client_name
  $fields['client-field_client_name'] = array(
    'field_name' => 'field_client_name',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '162',
      'parent' => 'group_client_config',
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
      'rows' => 5,
      'size' => '20',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_client_name][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Name',
      'weight' => '33',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_client_rate
  $fields['client-field_client_rate'] = array(
    'field_name' => 'field_client_rate',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '168',
      'parent' => 'group_client_config',
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
    'required' => '1',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '',
    'allowed_values_php' => 'return acecrew_get_ads(\'field_admins_clientrates\');',
    'widget' => array(
      'default_value' => NULL,
      'default_value_php' => 'return array(
0 => array(\'value\' => \'16.25\')
);',
      'label' => 'Rate',
      'weight' => '39',
      'description' => '',
      'type' => 'optionwidgets_select',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_client_vatnumber
  $fields['client-field_client_vatnumber'] = array(
    'field_name' => 'field_client_vatnumber',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '165',
      'parent' => 'group_client_config',
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
          '_error_element' => 'default_value_widget][field_client_vatnumber][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'VAT Number',
      'weight' => '36',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_client_website
  $fields['client-field_client_website'] = array(
    'field_name' => 'field_client_website',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '167',
      'parent' => 'group_client_config',
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
          '_error_element' => 'default_value_widget][field_client_website][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Website URL',
      'weight' => '38',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_credit_limit_box
  $fields['client-field_credit_limit_box'] = array(
    'field_name' => 'field_credit_limit_box',
    'type_name' => 'client',
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
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_decimal',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '£',
    'suffix' => '',
    'min' => '',
    'max' => '',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'precision' => '10',
    'scale' => '2',
    'decimal' => '.',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_credit_limit_box][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Credit limit box',
      'weight' => '32',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_default_contact_mobile
  $fields['client-field_default_contact_mobile'] = array(
    'field_name' => 'field_default_contact_mobile',
    'type_name' => 'client',
    'display_settings' => array(
      'weight' => '162',
      'parent' => 'group_client_contact',
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
          '_error_element' => 'default_value_widget][field_default_contact_mobile][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Default Contact Mobile',
      'weight' => '162',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_client_contact_email
  $fields['client_contact-field_client_contact_email'] = array(
    'field_name' => 'field_client_contact_email',
    'type_name' => 'client_contact',
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
    'type' => 'email',
    'required' => '0',
    'multiple' => '0',
    'module' => 'email',
    'active' => '1',
    'widget' => array(
      'size' => '20',
      'default_value' => array(
        '0' => array(
          'email' => '',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Email',
      'weight' => '33',
      'description' => '',
      'type' => 'email_textfield',
      'module' => 'email',
    ),
  );

  // Exported field: field_client_contact_mobile
  $fields['client_contact-field_client_contact_mobile'] = array(
    'field_name' => 'field_client_contact_mobile',
    'type_name' => 'client_contact',
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
      'rows' => 5,
      'size' => '20',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_client_contact_mobile][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Mobile',
      'weight' => '32',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_client_contact_name
  $fields['client_contact-field_client_contact_name'] = array(
    'field_name' => 'field_client_contact_name',
    'type_name' => 'client_contact',
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
      'rows' => 5,
      'size' => '20',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_client_contact_name][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Name',
      'weight' => '31',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('2 Hour Default');
  t('3 Hour Default');
  t('Accounts');
  t('Address');
  t('Blocked Crews');
  t('Client ID');
  t('Client Job Call Comments Box');
  t('Company Number');
  t('Contact');
  t('Credit limit box');
  t('Default Contact');
  t('Default Contact Mobile');
  t('Email');
  t('Fax');
  t('Logo');
  t('Mobile');
  t('Name');
  t('Notes');
  t('Offices');
  t('Post Code');
  t('Rate');
  t('Telephone');
  t('VAT Number');
  t('Website URL');

  return $fields;
}
