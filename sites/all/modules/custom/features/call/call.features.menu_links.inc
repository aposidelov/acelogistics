<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function call_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-ace-crew-menu:admin/admin-settings/cck-add
  $menu_links['menu-ace-crew-menu:admin/admin-settings/cck-add'] = array(
    'menu_name' => 'menu-ace-crew-menu',
    'link_path' => 'admin/admin-settings/cck-add',
    'router_path' => 'admin/admin-settings/cck-add',
    'link_title' => 'Add crew rate',
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
    'weight' => '0',
    'parent_path' => 'node/752/edit',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add crew rate');


  return $menu_links;
}
