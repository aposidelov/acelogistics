<?php
  
function client_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $result = db_query_range("SELECT field_client_name_value as name FROM {content_type_client} WHERE LOWER(field_client_name_value) LIKE LOWER('%s%%')", $string, 0, 10);
    while ($user = db_fetch_object($result)) {
      $matches[$user->name] = check_plain($user->name);
    }
  }

  drupal_json($matches);
}

function venue_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $result = db_query_range("SELECT field_venue_name_value as name FROM {content_type_venue} WHERE LOWER(field_venue_name_value) LIKE LOWER('%s%%')", $string, 0, 10);
    while ($user = db_fetch_object($result)) {
      $matches[$user->name] = check_plain($user->name);
    }
  }

  drupal_json($matches);
}
