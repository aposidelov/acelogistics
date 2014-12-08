<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function job_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-ace-crew-menu:jobs
  $menu_links['menu-ace-crew-menu:jobs'] = array(
    'menu_name' => 'menu-ace-crew-menu',
    'link_path' => 'jobs',
    'router_path' => 'jobs',
    'link_title' => 'All Jobs',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
    'parent_path' => 'node/add/job',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('All Jobs');


  return $menu_links;
}
