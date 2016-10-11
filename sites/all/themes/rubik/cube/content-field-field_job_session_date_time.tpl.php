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
  //watchdog('nn', '<pre>'.print_r($node, TRUE).'</pre>');

?>
<?php if (!$field_empty) : ?>
  <?php if (!$teaser) : ?>
  <div class="field field-type-<?php print $field_type_css ?> field-<?php print $field_name_css ?>">
    <?php if ($label_display == 'above') : ?>
      <div class="field-label"><?php print t($label) ?>:&nbsp;</div>
    <?php endif;?>
    <div class="field-items hours">
      <?php $count = 1;
      foreach ($items as $delta => $item) :
        if (!$item['empty']) : ?>
          <div class="field-item <?php print ($count % 2 ? 'odd' : 'even') ?>">
            <?php if ($label_display == 'inline') { ?>
              <div class="field-label-inline<?php print($delta ? '' : '-first')?>">
                <?php print t($label) ?>:&nbsp;</div>
            <?php } ?>
            <?php if (!empty($node->field_call_time_tbc[0]['value']) && $node->field_call_time_tbc[0]['value']) : ?>
              <span class="tbc"><?php print substr($item['view'], 0, -12) ?>TBC</span></span>
            <?php else : ?>          
              <?php print substr($item['view'], 0, -7) ?>fu            
            <?php endif; ?>
          </div>
        <?php $count++;
        endif;
      endforeach;?>
    </div>
  </div>
  <?php else : ?>
    <?php foreach ($items as $delta => $item) : ?>
      <?php if (!empty($node->field_call_time_tbc[0]['value']) && $node->field_call_time_tbc[0]['value']) : ?>
        <span class="tbc"><?php print substr($item['view'], 0, -12) ?>TBC</span></span>
      <?php else : ?>          
        <?php watchdog('vv', '<pre>'.print_r($item, TRUE).'</pre>'); ?>
        <?php print $item['view'] ?>|<?php print substr($item['view'], 0, -7) ?>ts            
      <?php endif; ?>
    <?php endforeach; ?>
  <?php endif; ?>
<?php endif; ?>
