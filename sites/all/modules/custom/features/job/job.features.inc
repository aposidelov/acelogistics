<?php

/**
 * Implementation of hook_node_info().
 */
function job_node_info() {
  $items = array(
    'job' => array(
      'name' => t('Job Create'),
      'module' => 'features',
      'description' => t('Use this to create a new job'),
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
function job_views_api() {
  return array(
    'api' => '2',
  );
}
