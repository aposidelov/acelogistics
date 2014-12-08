<?php
/**
 * @file
 * Callback page that serves custom JavaScript requests on a Drupal installation.
 */

/**
 * @name JavaScript callback status codes.
 * @{
 * Status codes for JavaScript callbacks.
 *
 * @todo Use regular defines from menu.inc.
 */

define('JS_FOUND', 1);
define('JS_NOT_FOUND', 2);
define('JS_ACCESS_DENIED', 3);
define('JS_SITE_OFFLINE', 4);

/**
 * @} End of "Menu status codes".
 */

require_once './includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_PATH);
require_once './includes/common.inc';
require_once './includes/locale.inc';

// Prevent caching of JS output.
$GLOBALS['conf']['cache'] = FALSE;
// Prevent Devel from hi-jacking our output in any case.
$GLOBALS['devel_shutdown'] = FALSE;

/**
 * Loads the requested module and executes the requested callback.
 *
 * @param $phase
 *   Determins which execution phase to run.
 * @return
 *   The callback function's return value or one of the JS_* constants.
 */
function js_execute_callback($phase = 1) {
  global $locale;
  
  // remember between phases
  static $full_bootstrap, $modules, $info, $args, $dependencies; 
  
  // first phase bootstraps, loads includes
  // and prepares the module list to determine whether 
  // function filter_xss_bad_protocol needs to be redefined or not. 
  switch($phase) {
    case 1:
      $args = explode('/', $_GET['q']);

      // Strip first argument 'js'.
      array_shift($args);

      // Determine module to load.
      $module = check_plain(array_shift($args));
      if (!$module || !drupal_load('module', $module)) {
        return JS_ACCESS_DENIED;
      }

      // Get info hook function name.
      $function = $module .'_js';
      if (!function_exists($function)) {
        return JS_NOT_FOUND;
      }

      // Get valid callbacks.
      $valid_callbacks = $function();

      $callback_args = $args;
      // Remove callback name from function arguments.
      array_shift($args);
      
      $callback_valid = FALSE;
      while (!empty($callback_args)) {
       $callback = check_plain(implode('/', $callback_args));
       if (isset($valid_callbacks[$callback])) {
         $callback_valid = TRUE;
         break;
       }
       else {
         // pop another parameter off the incoming args and check again
         array_pop($callback_args);
       }
      }

      if (!$callback_valid) {
        return JS_NOT_FOUND;
      }

      $info = $valid_callbacks[$callback];
      $full_bootstrap = FALSE;

      // Bootstrap to required level.
      if (!empty($info['bootstrap'])) {
        drupal_bootstrap($info['bootstrap']);
        $full_bootstrap = ($info['bootstrap'] == DRUPAL_BOOTSTRAP_FULL);
      }

      if (!$full_bootstrap) {

        // The following mimics the behavior of _drupal_bootstrap_full().
        // @see _drupal_bootstrap_full(), common.inc

        // Load required include files.
        if (isset($info['includes']) && is_array($info['includes'])) {
          foreach ($info['includes'] as $include) {
            if (file_exists("./includes/$include.inc")) {
              require_once "./includes/$include.inc";
            }
          }
        }
        // Always load locale.inc.
        require_once "./includes/locale.inc";

        // Set the Drupal custom error handler.
        set_error_handler('drupal_error_handler');
        // Detect string handling method.
        if (function_exists('unicode_check')) {
          unicode_check();
        }
        // Undo magic quotes.
        fix_gpc_magic();

        // Load required modules.
        $modules = array($module => 0);
        if (isset($info['dependencies']) && is_array($info['dependencies'])) {
          // Intersect list with active modules to avoid loading uninstalled ones.
          $dependencies = array_intersect(module_list(TRUE, FALSE), $info['dependencies']);
        }
        // determine and return whether "filter" module is included:
        return $dependencies['filter'] == 'filter';
      }
      return $full_bootstrap == true;
      break;
    case 2:
      if (!$full_bootstrap) {
        if (is_array($dependencies) && !empty($dependencies)) {
          foreach ($dependencies as $dependency) {
            drupal_load('module', $dependency);
            $modules[$dependency] = 0;
          }
        }
        // Reset module list.
        module_list(FALSE, TRUE, FALSE, $modules);

        // Initialize the localization system.
        // @todo We actually need to query the database whether the site has any
        // localization module enabled, and load it automatically.
        $locale = drupal_init_language();
        if (empty($info['skip_hook_init'])) {
          // Invoke implementations of hook_init().
          module_invoke_all('init');
        }
      }
      // Invoke callback function.
      return call_user_func_array($info['callback'], $args);
      break;
  }
}

// run first phase to find out whether xss filter function 
// is already included.
$filter_exists = js_execute_callback(1);

// Unless phase 1 has detected that filter.module is included anyway
if (!$filter_exists) {

    /**
     * l() calls check_url(), which needs to check for XSS attacks.
     */
    function filter_xss_bad_protocol($string, $decode = TRUE) {
      static $allowed_protocols;
      if (!isset($allowed_protocols)) {
        $allowed_protocols = array_flip(variable_get('filter_allowed_protocols', array('http', 'https', 'ftp', 'news', 'nntp', 'telnet', 'mailto', 'irc', 'ssh', 'sftp', 'webcal')));
      }

      // Get the plain text representation of the attribute value (i.e. its meaning).
      if ($decode) {
        $string = decode_entities($string);
      }

      // Iteratively remove any invalid protocol found.

      do {
        $before = $string;
        $colonpos = strpos($string, ':');
        if ($colonpos > 0) {
          // We found a colon, possibly a protocol. Verify.
          $protocol = substr($string, 0, $colonpos);
          // If a colon is preceded by a slash, question mark or hash, it cannot
          // possibly be part of the URL scheme. This must be a relative URL,
          // which inherits the (safe) protocol of the base document.
          if (preg_match('![/?#]!', $protocol)) {
            break;
          }
          // Per RFC2616, section 3.2.3 (URI Comparison) scheme comparison must be case-insensitive.
          // Check if this is a disallowed protocol.
          if (!isset($allowed_protocols[strtolower($protocol)])) {
            $string = substr($string, $colonpos + 1);
          }
        }
      } while ($before != $string);
      return check_plain($string);
    }
}

// continue with phase 2 to engage modules
$return = js_execute_callback(2);

// Menu status constants are integers; page content is a string.
if (is_int($return)) {
  drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
  switch ($return) {
    case JS_NOT_FOUND:
      drupal_not_found();
      break;

    case JS_ACCESS_DENIED:
      drupal_access_denied();
      break;

    case JS_SITE_OFFLINE:
      drupal_site_offline();
      break;
  }
}
elseif (isset($return)) {
  // If JavaScript callback did not exit, print any value (including an empty
  // string) except NULL or undefined:
  drupal_json($return);
}

