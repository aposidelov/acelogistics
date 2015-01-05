<?php
// $Id: views-view-field.tpl.php,v 1.1 2008/05/16 22:22:32 merlinofchaos Exp $
 /**
  * This template is used to print a single field in a view. It is not
  * actually used in default Views, as this is registered as a theme
  * function which has better performance. For single overrides, the
  * template is perfectly okay.
  *
  * Variables available:
  * - $view: The view object
  * - $field: The field handler object that can process the input
  * - $row: The raw SQL result that can be used
  * - $output: The processed output that will normally be used.
  *
  * When fetching output from the $row, this construct should be used:
  * $data = $row->{$field->field_alias}
  *
  * The above will guarantee that you'll always get the correct data,
  * regardless of any changes in the aliasing that might happen if
  * the view is modified.
  */

$client_name = $output; 
$client_id = '';
if ($client_name == 'Metro') {
  watchdog('name', '<pre>'.print_r($row, TRUE).'</pre>');
}
if (isset($row->node_data_field_client_name_field_client_id_value)) {
    $client_id = $row->node_data_field_client_name_field_client_id_value;
} elseif (isset($row->node_data_field_client_logo_field_client_id_value)) {
    $client_id = $row->node_data_field_client_logo_field_client_id_value;
}
$client_credit_exists = acecrew_client_is_credit_exists($client_id);
$red_class = !$client_credit_exists ? 'client-credit-warning' : '';
?>

<div class="client <?php print $red_class; ?>">
  <?php print $output; ?>
</div>
