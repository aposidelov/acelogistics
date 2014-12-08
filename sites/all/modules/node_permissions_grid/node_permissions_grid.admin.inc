<?php
// $Id: node_permissions_grid.admin.inc,v 1.2 2009/07/24 14:06:31 joachim Exp $

/**
 * @file
 * Admin page callback file for the node permissions grid pages.
 */

/**
 * @file
 *
 * This module works by extracting permissions of the form:
 *     ACTION PREFIX content-type name CONTENT SUFFIX
 * eg: create        page              content
 * eg: edit any      blog              entry
 */

/**
 * Define action prefix strings for permissions.
 *
 * This sets the order in the grid.
 */
function action_prefixes() {
  return array(
    'create',
    'edit own',
    'delete own',
    'edit any',
    'delete any',
  );
}

/**
 * Define content suffix strings for permissions.
 */
function content_suffixes() {
  return array(
    'content', 
    'entry', 'entries', // for blog module
    'topic', 'topics',  // for forum module
  );
}

/**
 * Menu callback: administer permissions.
 */
function node_permissions_grid_admin_content_perm($form_state, $rid = NULL) {
  // Some information about content permissions
  // the actions. these are the prefixes for permission names.
  $action_prefixes = action_prefixes();
  $action_prefixes_regexp = implode('|', $action_prefixes);

  // The content words. these are the suffixes.
  $content_suffixes = content_suffixes();
  $content_suffixes_regexp = implode('|', $content_suffixes);

  if (is_numeric($rid)) {
    $result = db_query('SELECT r.rid, p.perm FROM {role} r LEFT JOIN {permission} p ON r.rid = p.rid WHERE r.rid = %d', $rid);
  }
  else {
    $form['#theme'] = 'node_permissions_grid_admin_roles';
    return $form;
  }

  // Compile role array:
  // Add a comma at the end so when searching for a permission, we can
  // always search for "$perm," to make sure we do not confuse
  // permissions that are substrings of each other.
  while ($role = db_fetch_object($result)) {
    $role_permissions[$role->rid] = $role->perm .',';
  }

  $role_names = user_roles();
  if (is_numeric($rid)) {
    $role_names = array($rid => $role_names[$rid]);
  }

  // Render role/permission overview:
  $options = array();
  foreach (module_list(FALSE, FALSE, TRUE) as $module) {
    if ($permissions = module_invoke($module, 'perm')) {

      $form['permission'][] = array(
        '#value' => $module, // the module label.
      );

      foreach ($permissions as $perm) {
        $matches = array();

        // Get only the perms we care about.
        preg_match("/^($action_prefixes_regexp) (.+) ($content_suffixes_regexp)\$/", $perm, $matches);
        if ($matches) {
          // have (whole string, action, content type).
          //dsm($matches);
          $action  = $matches[1];
          $content = $matches[2];
          // autovivify so we don't clobber in another loop iteration
          $form['permission'][$content]['#value'] = $content; // the content type label

          // the last one of these to be stashed end up in form_values... but never mind.
          $form['permission'][$content]['perms']['#type']    = 'value';
          $form['permission'][$content]['perms']['#value'][] = $perm;

          $content_types[$content] = $content;
          $options[$perm] = '';
          if (strpos($role_permissions[$rid], $perm .',') !== FALSE) {
            $status[$rid][] = $perm;
          }

        } // if matches
        else {
          $other_permissions[] = $perm;
        }
      } // foreach perm

      if (is_numeric(key(array_slice($form['permission'], -1, 1, TRUE)))) {
        // if the last key in the permissions array is numeric, then it's a module label
        // and that means that this module gave us no interesting permissions
        // so remove it.
        array_pop($form['permission']);
      }
    }
  }

  // Have to build checkboxes here after checkbox arrays are built
  foreach ($role_names as $rid => $name) {
    $form['checkboxes'][$rid] = array('#type' => 'checkboxes', '#options' => $options, '#default_value' => isset($status[$rid]) ? $status[$rid] : array());

    $form['role_names'][$rid] = array('#value' => $name, '#tree' => TRUE);

    $form['other_perms'][$rid] = array(
      '#type' => 'value',
      '#tree' => TRUE,
    );
    foreach ($other_permissions as $perm) {
      // a perm we don't care about. stash its current value anyway for merging on submit.
      if (strpos($role_permissions[$rid], $perm .',') !== FALSE) {
        $form['other_perms'][$rid][$perm]['#type']  = 'value';
        $form['other_perms'][$rid][$perm]['#value'] = $perm;
      }
    }
  }
  foreach ($action_prefixes as $action) {
    $form['action_names'][$action] = array('#value' => $action, '#tree' => TRUE);
  }

  $form['submit'] = array('#type' => 'submit', '#value' => t('Save permissions'));

  return $form;
}


/**
 * Theme the administer permissions page.
 */
function theme_node_permissions_grid_admin_content_perm($form) {
/*
$form['permission'] is either:
  - numeric keys that are module name values
  - content type keys that hold:
    - numeric is the content type label

*/
  #dsm($form['permission']);

  $action_prefixes = action_prefixes();

  $roles = user_roles();
  foreach (element_children($form['role_names']) as $rid) {
    $output .= '<h3>Content permissions for ' . drupal_render($form['role_names'][$rid]) . '</h3>';
    foreach (element_children($form['permission']) as $key) {
      // Don't take form control structures
      // We are going through an array whose keys are either:
      //  - numeric, and represents a label for a module
      //  - a string, which is the content name for one or more permissions, eg 'blog', 'story'
      #dsm($key);
      if (is_array($form['permission'][$key])) {
        $row = array();
        if (is_numeric($key)) {
          // Module name: make a row for this module.
          $module_name = $form['permission'][$key]['#value'];
          #dsm($module_name);
          $row[] = array('data' => t('@module module', array('@module' => drupal_render($form['permission'][$key]))), 'class' => 'module', 'id' => 'module-'. $module_name, 'colspan' => 6);
        }
        else {
          // The content name: this begins the row.
          $content_name = $form['permission'][$key]['#value'];
          #dsm($content_suffix);

          $row[] = array('data' => drupal_render($form['permission'][$key]), 'class' => 'permission');
          // The perms are stored. Get them to match up with the right checkbox item, then render it.

          // These come in the order the module defined them (probably?)
          // We want them in the same order as the $action_prefixes array.
          $perms_ordered = array();
          foreach ($form['permission'][$key]['perms']['#value'] as $perm) {
            // create an arrray that looks like
            //action string => full perm name
            $pos = strpos($perm, $content_name);
            $action_prefix = substr($perm, 0, $pos-1);
            $perms_by_prefix[$action_prefix] = $perm;
          }

          #dsm($perms_by_prefix);
          // Iterate over this array to get the right order.
          foreach ($action_prefixes as $action_prefix) {
            $perm = $perms_by_prefix[$action_prefix];
            if (is_array($form['checkboxes'][$rid][$perm])) {
              $row[] = array('data' => drupal_render($form['checkboxes'][$rid][$perm]), 'class' => 'checkbox', 'title' => $roles[$rid] .' : '. t($perm));
            }
            else {
              $row[] = '';
            }
          }

        }
        $rows[] = $row;
      }
    }
  }
  $header[] = (t('Content'));
  foreach ($action_prefixes as $action) {
    $header[] = array('data' => drupal_render($form['action_names'][$action]), 'class' => 'checkbox');
  }
  $output .= theme('table', $header, $rows, array('id' => 'permissions'));
  $output .= drupal_render($form);
  return $output;
}


/**
 * Submit the form.
 */
function node_permissions_grid_admin_content_perm_submit($form, &$form_state) {
  // Save permissions:
  #dsm($form_state);
  $result = db_query('SELECT * FROM {role}');
  while ($role = db_fetch_object($result)) {
    if (isset($form_state['values'][$role->rid])) {
      $form_state['values'][$role->rid] = array_filter($form_state['values'][$role->rid]);
      // This contains the permissions featured on the form as well as all the others the role had set.
      // eg, 'access content'.
      #dsm($form_state['values'][$role->rid]);

      // Delete, so if we clear every checkbox we reset that role;
      // otherwise permissions are active and denied everywhere.
      db_query('DELETE FROM {permission} WHERE rid = %d', $role->rid);
      $form_state['values'][$role->rid] = array_filter($form_state['values'][$role->rid]);
      if (count($form_state['values'][$role->rid])) {
        db_query("INSERT INTO {permission} (rid, perm) VALUES (%d, '%s')", $role->rid, implode(', ', array_keys($form_state['values'][$role->rid])));
      }
    }
  }

  drupal_set_message(t('The changes have been saved.'));

  // Clear the cached pages
  cache_clear_all();
}

/**
 * Output for main page: role list.
 *
 * Switching the form's theme function to bring us here is kinda hacky.
 * If core provided a role_load we could switch to using that in hook_menu.
 */
function theme_node_permissions_grid_admin_roles($form) {
  $header = array(t('Name'), array('data' => t('Operations'), 'colspan' => 2));
  foreach (user_roles() as $rid => $name) {
    $edit_permissions = l(t('edit node permissions'), 'admin/user/node_permissions/'. $rid);
    if (!in_array($rid, array(DRUPAL_ANONYMOUS_RID, DRUPAL_AUTHENTICATED_RID))) {
      $rows[] = array($name, l(t('edit role'), 'admin/user/roles/edit/'. $rid), $edit_permissions);
    }
    else {
      $rows[] = array($name, t('locked'), $edit_permissions);
    }
  }

  $output = drupal_render($form);
  $output .= theme('table', $header, $rows);

  return $output;
}