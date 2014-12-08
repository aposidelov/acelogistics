<?php
// $Id: template.php,v 1.16.2.2 2009/08/10 11:32:54 goba Exp $

/**
 * Sets the body-tag class attribute.
 *
 * Adds 'sidebar-left', 'sidebar-right' or 'sidebars' classes as needed.
 */
function phptemplate_body_class($left, $right) {
  if ($left != '' && $right != '') {
    $class = 'sidebars';
  }
  else {
    if ($left != '') {
      $class = 'sidebar-left';
    }
    if ($right != '') {
      $class = 'sidebar-right';
    }
  }

  if (isset($class)) {
    print ' class="'. $class .'"';
  }
}

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
function phptemplate_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    return '<div class="breadcrumb">'. implode(' › ', $breadcrumb) .'</div>';
  }
}

/**
 * Override or insert PHPTemplate variables into the templates.
 */
function phptemplate_preprocess_page(&$vars) {
  $vars['tabs2'] = menu_secondary_local_tasks();

  // Hook into color.module
  if (module_exists('color')) {
    _color_page_alter($vars);
  }
}

/**
 * Add a "Comments" heading above comments except on forum pages.
 */
function garland_preprocess_comment_wrapper(&$vars) {
  if ($vars['content'] && $vars['node']->type != 'forum') {
    $vars['content'] = '<h2 class="comments">'. t('Comments') .'</h2>'.  $vars['content'];
  }
}



/**
 * Returns the rendered local tasks. The default implementation renders
 * them as tabs. Overridden to split the secondary tasks.
 *
 * @ingroup themeable
 */
function phptemplate_menu_local_tasks() {
  return menu_primary_local_tasks();
}

function phptemplate_comment_submitted($comment) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $comment),
      '!datetime' => format_date($comment->timestamp)
    ));
}

function phptemplate_node_submitted($node) {
  return t('!datetime — !username',
    array(
      '!username' => theme('username', $node),
      '!datetime' => format_date($node->created),
    ));
}

/**
 * Generates IE CSS links for LTR and RTL languages.
 */
function phptemplate_get_ie_styles() {
  global $language;

  $iecss = '<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . path_to_theme() .'/fix-ie.css" />';
  if ($language->direction == LANGUAGE_RTL) {
    $iecss .= '<style type="text/css" media="all">@import "'. base_path() . path_to_theme() .'/fix-ie-rtl.css";</style>';
  }

  return $iecss;
}


//acecrew override. Added class to Order table header.
function garland_content_multiple_values($element) {
  $field_name = $element['#field_name'];
  $field = content_fields($field_name);
  $output = '';

  if ($field['multiple'] >= 1) {
    $table_id = $element['#field_name'] .'_values';
    $order_class = $element['#field_name'] .'-delta-order';
    $required = !empty($element['#required']) ? '<span class="form-required" title="'. t('This field is required.') .'">*</span>' : '';

    $header = array(
      array(
        'data' => t('!title: !required', array('!title' => $element['#title'], '!required' => $required)),
        'colspan' => 2
      ),
      array(
        'data' => t('Order'),
        'class' => 'delta-order-header'
      )
      
    );
    $rows = array();

    // Sort items according to '_weight' (needed when the form comes back after
    // preview or failed validation)
    $items = array();
    foreach (element_children($element) as $key) {
      if ($key !== $element['#field_name'] .'_add_more') {
        $items[] = &$element[$key];
      }
    }
    usort($items, '_content_sort_items_value_helper');

    // Add the items as table rows.
    foreach ($items as $key => $item) {
      $item['_weight']['#attributes']['class'] = $order_class;
      $delta_element = drupal_render($item['_weight']);
      $cells = array(
        array('data' => '', 'class' => 'content-multiple-drag'),
        drupal_render($item),
        array('data' => $delta_element, 'class' => 'delta-order'),
      );
      $rows[] = array(
        'data' => $cells,
        'class' => 'draggable',
      );
    }

    $output .= theme('table', $header, $rows, array('id' => $table_id, 'class' => 'content-multiple-table'));
    $output .= $element['#description'] ? '<div class="description">'. $element['#description'] .'</div>' : '';
    $output .= drupal_render($element[$element['#field_name'] .'_add_more']);

    drupal_add_tabledrag($table_id, 'order', 'sibling', $order_class);
  }
  else {
    foreach (element_children($element) as $key) {
      $output .= drupal_render($element[$key]);
    }
  }

  return $output;
}