<?php
// $Id: content-field.tpl.php,v 1.1.2.6 2009/09/11 09:20:37 markuspetrux Exp $

/**
 * @file content-field.tpl.php
 * Default theme implementation to display the value of a field.
 *
 * Available variables:
 * - $node: The node object.
 * - $field: The field array.
 * - $items: An array of values for each item in the field array.
 * - $teaser: Whether this is displayed as a teaser.
 * - $page: Whether this is displayed as a page.
 * - $field_name: The field name.
 * - $field_type: The field type.
 * - $field_name_css: The css-compatible field name.
 * - $field_type_css: The css-compatible field type.
 * - $label: The item label.
 * - $label_display: Position of label display, inline, above, or hidden.
 * - $field_empty: Whether the field has any valid value.
 *
 * Each $item in $items contains:
 * - 'view' - the themed view for that item
 *
 * @see template_preprocess_content_field()
 */

  $client = '';
  // if client name is set for Job
  if (!empty($node->field_job_client_name[0]['value'])) {
    $client_id            = $node->field_job_client_name[0]['value'];
    //watchdog('cl_id', '<pre>'.print_r($client_id, TRUE).'</pre>');
    $client_contact       = $node->field_job_client_contact[0]['value'];
    // if client_contact is 0 - we need to take Default contact name, otherwise - Normal contact name
    if (!$client_contact) {
      // get Default contact name
      $client_default_value = db_result(db_query('SELECT field_client_company_contact_value FROM {content_type_client} WHERE field_client_id_value = %d', $client_id));
    } else {
      // get Normal contact name
      $client_default_value = db_result(db_query('SELECT field_client_contact_name_value FROM {content_type_client_contact} WHERE vid = %d', $client_contact));
    }
    $items[0]['value']    = $client_id;
    $items[0]['safe']     = $client_id;
    $items[0]['#delta']   = 0;
    $items[0]['empty']    = '';
    $items[0]['view']     = $client_default_value;
  }

?>
<?php if (!$field_empty) : ?>
<div class="field field-type-<?php print $field_type_css ?> field-<?php print $field_name_css ?>">
  <?php if ($label_display == 'above') : ?>
    <div class="field-label"><?php print t($label) ?>:&nbsp;</div>
  <?php endif;?>
  <div class="field-items">
    <?php $count = 1; ?>
    <?php foreach ($items as $delta => $item) : ?>
      <?php if (!$item['empty']) : ?>
        <div class="field-item <?php print ($count % 2 ? 'odd' : 'even') ?>">
          <?php if ($label_display == 'inline') { ?>
            <div class="field-label-inline<?php print($delta ? '' : '-first')?>">
              <?php print t($label) ?>:&nbsp;</div>
          <?php } ?>
          <?php print $item['view'] ?>
        </div>
      <?php $count++;
      endif;
    endforeach;?>
  </div>
</div>
<?php endif; ?>
