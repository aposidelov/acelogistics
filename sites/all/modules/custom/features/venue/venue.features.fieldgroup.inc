<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function venue_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_venue_config
  $groups['venue-group_venue_config'] = array(
    'group_type' => 'standard',
    'type_name' => 'venue',
    'group_name' => 'group_venue_config',
    'label' => 'Venue Configuration',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
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
        'label' => 'above',
        'modalframe_cck_editor' => array(
          'status' => '0',
        ),
      ),
    ),
    'weight' => '34',
    'fields' => array(
      '0' => 'field_boundary_charge',
      '1' => 'field_boundary_round_trip',
    ),
  );

  // Exported group: group_venue_contact
  $groups['venue-group_venue_contact'] = array(
    'group_type' => 'standard',
    'type_name' => 'venue',
    'group_name' => 'group_venue_contact',
    'label' => 'Venue Details',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
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
        'label' => 'above',
        'modalframe_cck_editor' => array(
          'status' => '0',
        ),
      ),
    ),
    'weight' => '33',
    'fields' => array(
      '0' => 'field_venue_id',
      '1' => 'field_venue_name',
      '2' => 'field_venue_address',
      '3' => 'field_venue_post_code',
      '4' => 'field_venue_notes',
    ),
  );

  // Exported group: group_venue_contacts
  $groups['venue-group_venue_contacts'] = array(
    'group_type' => 'standard',
    'type_name' => 'venue',
    'group_name' => 'group_venue_contacts',
    'label' => 'Venue Contact Details',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_vertical_tab',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
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
        'label' => 'above',
        'modalframe_cck_editor' => array(
          'status' => '0',
        ),
      ),
    ),
    'weight' => '35',
    'fields' => array(
      '0' => 'field_venue_email',
      '1' => 'field_venue_contact',
      '2' => 'field_venue_contact_telephone',
      '3' => 'field_venue_telephone',
      '4' => 'field_nearest_station',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Venue Configuration');
  t('Venue Contact Details');
  t('Venue Details');

  return $groups;
}
