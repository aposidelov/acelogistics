<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function review_user_default_permissions() {
  $permissions = array();

  // Exported permission: access content
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      '0' => 'Admin',
      '1' => 'Crew',
      '2' => 'Super User',
      '3' => 'anonymous user',
      '4' => 'authenticated user',
    ),
  );

  // Exported permission: administer nodes
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(
      '0' => 'Admin',
      '1' => 'Super User',
    ),
  );

  // Exported permission: edit any review content
  $permissions['edit any review content'] = array(
    'name' => 'edit any review content',
    'roles' => array(
      '0' => 'Super User',
      '1' => 'anonymous user',
    ),
  );

  return $permissions;
}
