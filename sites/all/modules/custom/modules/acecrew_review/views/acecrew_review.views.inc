<?php
/**
* Implements hook_views_data_alter().
*
* @param $data
*   Information about Views' tables and fields.
*/
function fe_profile_views_data_alter(&$data) {
  //dsm($data);
  // Add the Title form field to
  $data['node']['title_edit'] = array(
    'field' => array(
      'title' => t('Title form field'),
      'help' => t('Edit the node title'),
      'handler' => 'fe_profile_field_handler_title_edit',
    ),
  );
  $data['file_managed']['delete_checkbox'] = array(
    'field' => array(
      'title' => t('Delete checkbox'),
      'help' => t('Delete checkbox description'),
      'handler' => 'fe_profile_field_handler_delete_checkbox_edit',
    ),
  );
}
