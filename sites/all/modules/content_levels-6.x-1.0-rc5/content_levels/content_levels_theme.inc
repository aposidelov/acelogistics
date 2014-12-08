<?php
// $Id: content_levels_theme.inc,v 1.3 2009/09/21 09:19:47 darthsteven Exp $

/**
 * @file
 * Theme functions for the content_levels module.
 */

/**
 * Theme hook for the global field settings content_series form fragment.
 */
function theme_content_levels_series($form) {

  $rows = _content_levels_theme_form_table($form, TRUE, 'content-level-weight');

  $headings = $form['#headings'];

  drupal_add_tabledrag('content-levels-content-series-table', 'order', 'sibling', 'content-level-weight');

  return theme('table', $headings, $rows, array('id' => 'content-levels-content-series-table'));
}

/**
 * Theme hook for the field-instance (widget) settings visibility matrix form
 * fragment.
 */
function theme_content_levels_visibility_matrix($form) {

  $rows = _content_levels_theme_form_table($form);

  $headings = $form['#headings'];

  return theme('table', $headings, $rows, array('id' => 'content-levels-visibility-matrix-table', 'width' => '300'));

}

/**
 * Helper function that themes a form into rows.
 */
function _content_levels_theme_form_table($form, $draggable = FALSE, $weight_class = 'weight') {

  $rows = array();
  foreach ($form as $element_id => $element) {

    if ($element_id[0] != '#') {

      $new_row_data = array();
      if (($element_id === 'default_level')) {
        continue;
      }

      if (isset($form['default_level']) && isset($form['default_level'][$form[$element_id]['id']['#value']])) {
        $element['is_default'] = $form['default_level'][$form[$element_id]['id']['#value']];
      }

      foreach ($element as $col_id => $col) {

        if ($col_id[0] != '#') {
          if ($col_id == 'weight' && isset($weight_class)) {
            $col['#attributes']['class'] = $weight_class;
          }
          $data = drupal_render($col);
          if ($data) {
            $new_row_data[] = $data;
          }
        }
      }
      $new_row = array();
      $new_row['data'] = $new_row_data;
      if ($draggable) {
        $new_row['class'] = 'draggable';
      }
      $rows[] = $new_row;
    }
  }

  return $rows;
}