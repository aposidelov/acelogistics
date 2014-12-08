<?php

/**
 * Implementation of hook_node_info().
 */
function venue_node_info() {
  $items = array(
    'venue' => array(
      'name' => t('Venue'),
      'module' => 'features',
      'description' => t('Use this to add a new venue'),
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
