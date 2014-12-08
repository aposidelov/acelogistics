<?php

/**
 * Implementation of hook_menu_default_menu_custom().
 */
function job_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-ace-crew-menu
  $menus['menu-ace-crew-menu'] = array(
    'menu_name' => 'menu-ace-crew-menu',
    'title' => 'Ace Crew Menu',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Ace Crew Menu');


  return $menus;
}
