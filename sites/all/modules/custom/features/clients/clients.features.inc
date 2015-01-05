<?php

/**
 * Implementation of hook_imagecache_default_presets().
 */
function clients_imagecache_default_presets() {
  $items = array(
    'listing_image' => array(
      'presetname' => 'listing_image',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '75',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function clients_node_info() {
  $items = array(
    'client' => array(
      'name' => t('Client'),
      'module' => 'features',
      'description' => t('Create a new client here.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
    'client_contact' => array(
      'name' => t('Client Contact'),
      'module' => 'features',
      'description' => t('Do not use this - this is used by system to create new contact for clients. To create a new contact, find the relevant client, edit that client and there you will the button to add new contact.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function clients_views_api() {
  return array(
    'api' => '2',
  );
}
