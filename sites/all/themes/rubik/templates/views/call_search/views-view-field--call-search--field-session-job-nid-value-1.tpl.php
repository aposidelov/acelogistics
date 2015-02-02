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

$job_nid = $row->node_data_field_job_session_date_time_field_session_job_nid_value; 
$client = db_fetch_object(db_query("SELECT field_client_id_value, field_client_name_value 
  FROM {content_type_client} c 
  INNER JOIN {content_type_job} j ON c.field_client_id_value = j.field_job_client_name_value
  WHERE j.nid = %d", $job_nid));
$client_id = $client->field_client_id_value;
$client_name = $client->field_client_name_value;

$client_credit_exists = acecrew_client_is_credit_exists($client_id);
$red_class = !$client_credit_exists ? 'client-credit-warning' : '';

?>
<div class="client <?php print $red_class; ?>">
  <?php print $client_name; ?>
</div>

