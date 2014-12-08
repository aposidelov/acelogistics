<?php
// $Id: content_levels_cck.inc,v 1.6 2010/02/16 23:29:07 jamsilver Exp $

/**
 * @file
 * Defines the Content Level CCK field type, the Content level select list
 * cck widget and some CCK formatters for content level fields
 */

/* --- CCK FIELD TYPE ------------------------------------------------------- */

/**
 * Implementation of hook_field_settings().
 */
function content_levels_field_settings($op, $field) {

  switch ($op) {

    // Global field settings form
    case 'form':
      $form = array();

      // Get last value of content series
      $content_series = $field['content_series'];
      if (!$content_series) {
        $content_series =  array();
      }

      // We need to theme this form fragment ourselves
      $form['content_series'] = array(
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#title' => t('Content Series'),
        '#description' => t('Leave a field blank to delete it. Submit the form and return to get more blank fields.'),
        '#theme' => 'content_levels_series',
        '#tree' => TRUE,
        '#element_validate' => array('_content_levels_content_series_validate'),
        '#headings' => array('Title', 'Weight', 'Default'),
        '#old_value' => $content_series,
        '#required' => TRUE,
      );

      $is_default_options = array();

      // Add the list of currently defined content levels
      $max_weight;
      $max_id = 0;
      foreach ($content_series as $level_id => $level) {

        // We want to exit this loop knowing what the maximum weight & id is
        if (!isset($max_weight) || ($level['weight'] > $max_weight)) {
          $max_weight = $level['weight'];
        }
        if (!isset($max_id) || ($level['id'] > $max_id)) {
          $max_id = $level['id'];
        }

        $content_series_form[$level['id']] = array(
          'id' => array('#type' => 'value', '#value' => $level['id']),
          'title' => array('#type' => 'textfield', '#default_value' => $level['title'], '#size' => 15),
          'weight' => array('#type' => 'weight', '#default_value' => $level['weight']),
          '#weight' => $level['weight'],
        );

        $is_default_options[$level['id']] = '';
      }
      // Add an extra empty fields for new levels
      $new_id = $max_id + 1;
      $new_weight = $max_weight + 1;

      $num_empties = 4;
      for ($i=0; $i < $num_empties; $i++) {
        $content_series_form[$new_id] = array(
          'id' => array('#type' => 'value', '#value' => $new_id),
          'title' => array('#type' => 'textfield', '#default_value' => '', '#size' => 15),
          'weight' => array('#type' => 'weight', '#default_value' => $new_weight),
          '#weight' => $new_weight,
        );
        $is_default_options[$new_id] = '';
        $new_id++;
        $new_weight++;
      }
      $form['content_series']['default_level'] = array(
        '#type' => 'radios',
        '#options' => $is_default_options,
        '#parents' => array('default_level'),
        '#default_value' => $field['default_level'],
      );

      $form['content_series'] = array_merge($form['content_series'], $content_series_form);
      $form['#element_validate'] = array('_content_levels_field_settings_validate');

      return $form;
    break;

    // The names of the form elements whose values correspond
    // to settings we need to remember. They are passed around in $field
    case 'save':

      return array('content_series', 'default_level');
      break;

    // The database columns for this field. Schema API format
    //  'views', to define a Views field
    //  'sortable', to add a Views sort field
    case 'database columns':
      $columns['value'] = array(
        'type' => 'int',
        'not null' => FALSE,
        'sortable' => FALSE,
        'views' => TRUE,
      );
      $columns['degrade'] = array(
        'type' => 'int',
        'size' => 'tiny',
        'not null' => FALSE,
        'sortable' => TRUE,
        'views' => FALSE,
      );
      $columns['degrade_on'] = array(
        'type' => 'int',
        'not null' => FALSE,
        'sortable' => TRUE,
        'views' => FALSE,
      );
      //Used to help views to sort content levels by the order (weight)
      //they appear in their content series, rather than by content
      //level id, which is arbitrary
      $columns['weight'] = array(
        'type' => 'int',
        'not null' => FALSE,
        'sortable' => TRUE,
        'views' => TRUE,
      );
      return $columns;
    break;

    // Can define what gets passed to views
    case 'views data':
      /*
       Note: This code was nabbed from the cck/modules/number field
      */
      $allowed_values = content_levels_allowed_values($field);
      if (count($allowed_values)) {
        $data = content_views_field_views_data($field);
        $db_info = content_database_info($field);
        $table_alias = content_views_tablename($field);

        // Filter: Add a 'many to one' filter.
        $copy = $data[$table_alias][$field['field_name'] .'_value'];
        $copy['title'] = t('@label (!name) - Allowed values', array('@label' => t($field['widget']['label']), '!name' => $field['field_name']));
        $copy['filter']['handler'] = 'content_handler_filter_many_to_one';
        $copy['filter']['numeric'] = FALSE;
        unset($copy['field'], $copy['argument'], $copy['sort']);
        $data[$table_alias][$field['field_name'] .'_value_many_to_one'] = $copy;
        // Argument: swap the handler to the 'many to one' operator
        $data[$table_alias][$field['field_name'] .'_value']['argument']['handler'] = 'content_handler_argument_many_to_one';
        $data[$table_alias][$field['field_name'] .'_value']['argument']['numeric'] = FALSE;
        return $data;
      }
    break;
  }
}

/**
 * Called by content's filter many_to_one handler to allow
 * filtering by content_level.
 * We do this so the views user gets a drop down list of titles
 * rather than being required to enter the id of a level.
 */
function content_levels_allowed_values($field) {

  //Grab the content series
  $content_series = $field['content_series'];

  if (empty($content_series)) {
    return array();
  }

  //Order by weight, so it appears to the user as expected
  _content_levels_sort_by_weight($content_series);

  //Construct assoc array of options
  $options = array();
  foreach ($content_series as $content_level) {
    $options[$content_level['id']] = $content_level['title'];
  }
  return $options;
}

/**
 * Validation for the content series field settings.
 * Removes empty levels.
 * Triggers a function that propogates weight changes accross all
 * relevant field instances if the order of content levels changed
 */
function _content_levels_content_series_validate($element, &$form_state) {

  //Remove all content levels that have empty titles
  $content_series = $form_state['values']['content_series'];
  $new_content_series = array();
  foreach ($content_series as $key => $level) {
    $level['title'] = trim($level['title']);
    if (empty($level['title'])) {
      unset($content_series[$key]);
    }
    else {
      $new_content_series[$level['id']] = $level;
    }
  }
  $content_series = $new_content_series;

  //If there were no content levels specified, trigger an error - we need 'em!
  if (empty($content_series)) {
    form_set_error('content_series', t('Global Settings: At least one level must be defined in the content series.'));
  }

  else {

    //Save them sorted
    _content_levels_sort_by_weight($content_series);

    form_set_value($element, $content_series, $form_state);

    //Check if the order of content levels changed
    $old_series = $element['#old_value'];
    $new_series = $form_state['values']['content_series'];

    //Compare weights of old levels in new series
    foreach ($old_series as $key => $old_value) {
      if ($new_series[$key]['weight'] != $old_series[$key]['weight']) {
        $weights_have_changed = TRUE;
        break;
      }
    }

    //If the weights have been changed, we need to propogate this across
    //any fields that already had one of these
    if ($weights_have_changed) {
      _content_levels_propogate_series_weights($form_state['values']['field_name'], $new_series);
    }
  }
}

/**
 * Validates the whole field settings form.
 * Validate the default level to make sure it is one of the
 * valid content levels (i.e. not one with a blank title that was ignored)
 */
function _content_levels_field_settings_validate($element, &$form_state) {

  $default_level = $form_state['values']['default_level'];
  $content_series = $form_state['values']['content_series'];

  //If the content series is empty the form will be rejected in the
  //above validation function anyway.
  if (!empty($content_series)) {
    //If a valid default level was not set, set it explicitly to
    //the lowest content level in the series
    if (!isset($default_level) || !isset($content_series[$default_level])) {
      $default_level = end(array_keys($content_series));
      form_set_value($element['content_series']['default_level'], $default_level, $form_state);
    }
  }

}

/**
 * Implementation of hook_field().
 */
function content_levels_field($op, &$node, $field, &$items, $teaser, $page) {
  switch ($op) {

    // Validation code for values submitted to this field
    // This code is run after the submission has passed widget validation
    case 'validate':

      if (is_array($items)) {
        foreach ($items as $delta => $item) {
          // The error_element is needed so that CCK can
          // set an error on the right sub-element when
          // fields are deeply nested in the form.
          $error_element = isset($item['_error_element']) ? $item['_error_element'] : '';
          if (is_array($item) && isset($item['_error_element'])) unset($item['_error_element']);

          //Check that the submitted value is part of the content series
          if (!empty($item['value'])) {
            if (!in_array($item['value'], array_keys($field['content_series']))) {
              form_set_error($error_element,
                t('@name: the value must be in the content series: @series).',
                  array(
                    '@name' => $field['widget']['label'],
                    '@series' => implode(', ', $field['content_series'])
                  )
                )
              );
            }
          }
        }
      }

      return $items;

    // This is where you make sure that user-provided
    // data is sanitized before being displayed.
    case 'sanitize':

      foreach ($items as $delta => $item) {
        if (empty($item['value'])) {
          $items[$delta]['safe'] = '';
        }
        else {

          //Make sure we pass the title to be displayed, not the internal id
          $item['title'] = $field['content_series'][$item['value']]['title'];

          $content_level = check_plain($item['title']);
          $items[$delta]['safe'] = $content_level;
        }
      }
  }
}

/**
 * Implementation of hook_content_is_empty().
 * Just because CCK can't be sure what value means 'empty'
 */
function content_levels_content_is_empty($item, $field) {
  if (drupal_strlen(trim($item['value'])) == 0) {
    return TRUE;
  }
  return FALSE;
}



/* --- CCK WIDGET ----------------------------------------------------------- */

/**
 * Implementation of hook_widget_info().
 */
function content_levels_widget_info() {

  return array(

    'content_levels_select_list' => array(
      'label' => t('Content levels select list'),
      'field types' => array('content_levels'),
      'multiple values' => CONTENT_HANDLE_CORE,
      'callbacks' => array(
        //Let's not bother with a default value since it
        //adds confusion as to what the default level is
        //since it is specified in the global content_series
        'default value' => CONTENT_CALLBACK_NONE,
      ),
    ),
  );
}

/**
 * Implementation of hook_widget_settings().
 *
 * Note: We actually call this hook from our own form_alter function with
 * the extra field_name parameter. CCK's calling of the form operation is
 * ignored here, rather the form is form altered in later in the pipeline
 * with our own form alter function.
 * This is necessary because:
 * 1) We need to know which exact field we are working on, so we can get
 *    the content series (which is tied to individual fields)
 * 2) CCK does not tell a widget which particular field it is displaying.
 *    It would be helpful if it passed it in this $widget parameter here,
 *    but it doesn't.
 */
function content_levels_widget_settings($op, $widget, $field_name = NULL, $type_name = NULL) {

  switch ($op) {

    // The form instance specific settings on the field settings page
    case 'form':

      /**
       * NOTE: We _do_ add stuff to the widget settings page (namely the
       * visibility matrix of (fields vs. visibility settings) and the option
       * to let content_levels be downgradable), but we just don't make these
       * changes here (even though CCK intends us to).
       *
       * Instead we add all of our settings to this form slightly later in the
       * process in the hook_form_alter in content_levels.module file.
       * This is necessary because in order to construct the visibility
       * matrix, we need to know about:
       *   a) the field-specific ('global') settings (i.e. the content series)
       *   b) node-type specific settings (i.e. the other fields in this node type)
       * And CCK does not pass either of those pieces of information on
       * to this function.
       *
       * It doesn't seem to make any difference to CCK that we do it this way.
       * It still picks up the values we set - providing we don't return from
       * this function with an empty array.
       *
       * @see content_levels_form_alter()
       */

      return array('visibility' => array(), 'level_scheduling' => array());

    // The array of settings to save from the above form
    case 'save':
      return array('visibility', 'level_scheduling');
  }
}

/**
 * Sorts an array by weight
 */
function _content_levels_sort_by_weight(&$array) {

  if (!is_array($array) || (empty($array))) {
    return;
  }

  $maxweight = 0;
  $to_set_to_max = array();

  //Prepend the weight to the key
  $new_array = array();
  foreach ($array as $key => $value) {

    if (is_array($value)) {
      if (isset($value['#weight'])) {
        $weight = $value['#weight'];
      }
      elseif (isset($value['weight'])) {
        $weight = $value['weight'];
      }
      elseif ((is_array($value['widget'])) && (isset($value['widget']['weight']))) {
        $weight = $value['widget']['weight'];
      }
      else {
        $weight = NULL;
        $to_set_to_max[] = $key;
      }
    }

    //Keep track of the max weight
    if ($weight > $maxweight) {
      $maxweight = $weight;
    }

    if (isset($weight)) {
      //Ensure weight is positive
      $weight += 50000;
      $new_key = $weight . $key;
      $new_array[$new_key] = $value;
      //Remember the old key
      $new_array[$new_key]['_content_level_key'] = $key;
    }
  }

  //Set the failures to consecutive weights larger than max
  foreach ($to_set_to_max as $key) {

    $value = $array[$key];
    $weight = ++$maxweight + 50000;
    $new_array[$weight . $key] = $value;
  }

  //Sort by key
  ksort($new_array);

  //Apply to the original array
  $array = array();
  foreach ($new_array as $key => $value) {
    $array[$value['_content_level_key']] = $value;
    unset($array[$value['_content_level_key']]['_content_level_key']);
  }
}

/**
 * Implementation of hook_widget().
 *
 * Attach a single form element to the form.
 *
 * CCK core fields only add a stub element and builds
 * the complete item in #process so reusable elements
 * created by hook_elements can be plugged into any
 * module that provides valid $field information.
 *
 * Custom widgets that don't care about using hook_elements
 * can be built out completely at this time.
 *
 * If there are multiple values for this field and CCK is
 * handling multiple values, the content module will call
 * this function as many times as needed.
 *
 * @param $form
 *   the entire form array,
 *   $form['#node'] holds node information
 * @param $form_state
 *   the form_state,
 *   $form_state['values'][$field['field_name']]
 *   holds the field's form values.
 * @param $field
 *   the field array
 * @param $items
 *   array of default values for this field
 * @param $delta
 *   the order of this item in the array of
 *   subelements (0, 1, 2, etc)
 *
 * @return
 *   the form item for a single element for this field
 */
function content_levels_widget(&$form, &$form_state, $field, $items, $delta = 0) {

  // Gather settings
  $content_series = $field['content_series'];

  // If the user hasn't entered a content series yet, we'll abandon all hope
  // and return before any more madness can happen!
  if (empty($content_series)) {
    return;
  }

  _content_levels_sort_by_weight($content_series);
  $allow_scheduling = $field['widget']['level_scheduling'];

  //Get the default level if there is one set
  if (isset($field['default_level']) && isset($content_series[$field['default_level']])) {
    $default_level =$field['default_level'];
  }
  else {
    //Just use the lowest rank as default
    $default_level = end(array_keys($content_series));
  }

  $current_level = isset($items[$delta]['value']) ? $items[$delta]['value'] : $default_level;

  //Generate the available options
  $options = array();
  if ($content_series) {
    foreach ($content_series as $content_level) {
      $options[$content_level['id']] = $content_level['title'];
    }
  }

  $element['value'] = array(
    '#type' => 'select',
    '#title' => $field['widget']['label'],
    '#default_value' => $current_level,
    '#options' => $options,
    '#attributes' => array('class' => 'content_levels'),
  );

  //Add hidden value to form to set weight
  //This weight is merely copied from the weight of this node's content
  //level in its content series and must be kept consistent with that
  $element['weight'] = array(
    '#type' => 'value',
    '#value' => isset($content_series[$default_level]['weight'])
                ? $content_series[$default_level]['weight']
                : 0,
    '#content_series' => $content_series,
  );

  //Add elements to deal with the scheduling
  if (module_exists('date_api')) {
	  $element['degrade'] = array(
	    '#type' => 'checkbox',
	    '#title' => t('Automatically degrade this to default (@default) in the future.', array('@default' => $content_series[$default_level]['title'])),
	    '#default_value' => isset($items[$delta]['degrade']) ? $items[$delta]['degrade'] : FALSE,
	    '#access' => $allow_scheduling,
	  );
	
	  $format = 'Y-m-d H:i';
	  $default_date = time();
	
	  //If there is a valid degrade_on value and the degrade box is ticked
	  //remember the current value and pass it on to the form
	  if (isset($items[$delta]['degrade_on']) && ($items[$delta]['degrade_on'])
	      && $element['degrade']['#default_value']) {
	    $current_date = $items[$delta]['degrade_on'];
	  }
	
	  //Notably, if the degrade checkbox is not ticked then we revert the
	  //degrade_on value to default (current time)
	  else {
	    $current_date = $default_date;
	  }
	
	  //Convert the UTC time stored in the db to local
	  //See http://drupal.org/node/291799
	  $date = date($format, $current_date);
	  $local_zone = date_default_timezone_name();
	  $date = date_make_date($date, 'UTC');
	  date_timezone_set($date, timezone_open($local_zone));
	  $date_value = date_format_date($date, 'custom', $format);
	
	  $element['degrade_on'] = array(
	    '#type' => 'date_select',
	    '#title' => t('Degrade on'),
	    '#default_value' => $date_value,
	    '#date_format' => $format,
	    '#date_label_position' => 'above',
	    '#date_increment' => 1,
	    '#date_year_range' => '0:+10',
	    '#access' => $allow_scheduling,
	    '#element_validate' => array('_content_levels_widget_degrade_on_validate'),
	  );
	  
      //CTools dependent visibility
	  if (module_exists('ctools')) {
        ctools_include('dependent');
        $degrade_id = 'edit-' . strtr($field['field_name'], array('_' => '-')) . '-' . $delta . '-degrade';
        $element['degrade_on']['#process'] = array('date_select_process', 'ctools_dependent_process');
        $element['degrade_on']['#dependency'] = array($degrade_id => array(1));
	  }
  }

  //Determine whether this field will be editable by the user
  $user_can_edit = $field['widget']['visibility'][$field['field_name']][$current_level]['editable']
    || user_access('edit content levels always');

  //HACK: There seems to be an error where, if a form is submitted when a date
  //select field is present but hidden (#access = false) then the year element
  //of the value is corrupted when it gets back to the php.
  //This fixes the problem by not bothering with a date_select element if
  //the user cannot access it, but just a standard hidden value
  if (!($user_can_edit && $allow_scheduling)) {
    $element['degrade_on'] = array(
      '#type' => 'value',
      '#value' => $date_value,
    );
  }

  // Used so that hook_field('validate') knows where to
  // flag an error in deeply nested forms.
  if (empty($form['#parents'])) {
    $form['#parents'] = array();
  }
  $element['_error_element'] = array(
    '#type' => 'value',
    '#value' => implode('][', array_merge($form['#parents'], array('value'))),
  );
  $element['#element_validate'] = array('_content_levels_widget_validate');

  return $element;
}

/**
 * Butts in just after form submission to convert the submitted
 * degrade_on time to UTC (since it was submitted in accordance
 * with the user's local timezone).
 * Also updates the content_level_weight value to make sure
 * that it is consistent with the content_level just submitted.
 */
function _content_levels_widget_validate($element, &$form_state) {

  // This needs to work when validate is called from the field settings
  // page (for the default value) and the main page when there are
  // multiple values.
  $fields = isset($form_state['values'][$element['#field_name']])
              ? $form_state['values'][$element['#field_name']]
              : (isset($form_state['values']['default_value_widget'][$element['#field_name']])
                ? $form_state['values']['default_value_widget'][$element['#field_name']]
                : array() );

  if (module_exists('date_api')) {
	  foreach ($fields as $field) {
	    $degrade_on_str = $field['degrade_on'];
	
	    // Convert it to UTC timezone. See http://drupal.org/node/291799
	    $local_zone = date_default_timezone_name();
	    $date = date_make_date($degrade_on_str, $local_zone, DATE_DATETIME);
	    date_timezone_set($date, timezone_open('UTC'));
	    $date_str = date_format_date($date, 'custom', 'Y-m-d H:i');
	
	    $degrade_on_time = strtotime($date_str);
	
	    form_set_value($element['degrade_on'], $degrade_on_time, $form_state);
	  }
  }

  //Update the content_level_weight:
  $new_level = $form_state['values'][$element['#field_name']][0]['value'];
  $new_weight = $element['weight']['#content_series'][$new_level]['weight'];
  form_set_value($element['weight'], $new_weight, $form_state);
}


/* --- CCK FORMATTER -------------------------------------------------------- */

/**
 * Implementation of hook_field_formatter_info().
 * Return info about all the formatters we have
 */
function content_levels_field_formatter_info() {
  return array(
    'default' => array(
      'label' => t('Default'),
      'field types' => array('content_levels'),
      'multiple values' => CONTENT_HANDLE_CORE,
    ),
    'plain' => array(
      'label' => t('Plain text'),
      'field types' => array('content_levels'),
      'multiple values' => CONTENT_HANDLE_CORE,
    ),
  );
}

/**
 * Theme function for 'default' content_levels field formatter.
 */

function theme_content_levels_formatter_default($element) {
  return $element['#item']['safe'];
}

/**
 * Theme function for 'plain' content_levels field formatter.
 */
function theme_content_levels_formatter_plain($element) {
  return strip_tags($element['#item']['safe']);
}
