<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function clients_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_antoherab
  $groups['client-group_antoherab'] = array(
    'group_type' => 'standard',
    'type_name' => 'client',
    'group_name' => 'group_antoherab',
    'label' => 'Client Address Details',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'weight' => '160',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '100' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '101' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'inline' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'modal' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'modalframe_cck_editor' => array(
          'status' => '0',
        ),
      ),
    ),
    'weight' => '160',
    'fields' => array(
      '0' => 'field_client_company_address',
      '1' => 'field_client_company_postcode',
    ),
  );

  // Exported group: group_client_config
  $groups['client-group_client_config'] = array(
    'group_type' => 'standard',
    'type_name' => 'client',
    'group_name' => 'group_client_config',
    'label' => 'Client Configuration',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'weight' => '158',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '100' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '101' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'inline' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'modal' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'modalframe_cck_editor' => array(
          'status' => '0',
        ),
      ),
    ),
    'weight' => '158',
    'fields' => array(
      '0' => 'field_client_name',
      '1' => 'field_client_logo',
      '2' => 'field_client_company_number',
      '3' => 'field_client_vatnumber',
      '4' => 'field_client_id',
      '5' => 'field_client_website',
      '6' => 'field_client_rate',
      '7' => 'field_2_hour_default',
      '8' => 'field_3_hour_default',
    ),
  );

  // Exported group: group_client_contact
  $groups['client-group_client_contact'] = array(
    'group_type' => 'standard',
    'type_name' => 'client',
    'group_name' => 'group_client_contact',
    'label' => 'Client Contacts',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'weight' => '161',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '100' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '101' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'inline' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'modal' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'modalframe_cck_editor' => array(
          'status' => '0',
        ),
      ),
    ),
    'weight' => '161',
    'fields' => array(
      '0' => 'field_client_company_contact',
      '1' => 'field_add_accounts',
      '2' => 'field_default_contact_mobile',
    ),
  );

  // Exported group: group_client_contact_details
  $groups['client-group_client_contact_details'] = array(
    'group_type' => 'standard',
    'type_name' => 'client',
    'group_name' => 'group_client_contact_details',
    'label' => 'Client Contact Details',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'weight' => '159',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '100' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '101' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'inline' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'modal' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'modalframe_cck_editor' => array(
          'status' => '0',
        ),
      ),
    ),
    'weight' => '159',
    'fields' => array(
      '0' => 'field_client_company_email',
      '1' => 'field_client_company_telephone',
      '2' => 'field_client_company_fax',
      '3' => 'field_client_contact',
    ),
  );

  // Exported group: group_client_notes
  $groups['client-group_client_notes'] = array(
    'group_type' => 'standard',
    'type_name' => 'client',
    'group_name' => 'group_client_notes',
    'label' => 'Client Notes',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'weight' => '163',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '100' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '101' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'inline' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'modal' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'modalframe_cck_editor' => array(
          'status' => '0',
        ),
      ),
    ),
    'weight' => '163',
    'fields' => array(
      '0' => 'field_client_company_notes',
    ),
  );

  // Exported group: group_client_offices
  $groups['client-group_client_offices'] = array(
    'group_type' => 'standard',
    'type_name' => 'client',
    'group_name' => 'group_client_offices',
    'label' => 'Client Offices',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'weight' => '162',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '100' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '101' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'inline' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'modal' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'modalframe_cck_editor' => array(
          'status' => '0',
        ),
      ),
    ),
    'weight' => '162',
    'fields' => array(
      '0' => 'field_add_offices',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Client Address Details');
  t('Client Configuration');
  t('Client Contact Details');
  t('Client Contacts');
  t('Client Notes');
  t('Client Offices');

  return $groups;
}
