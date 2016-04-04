<?php

/**
 * Implementation of hook_node_info().
 */
function call_node_info() {
  $items = array(
    'job_session' => array(
      'name' => t('Job Call'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_rules_defaults().
 */
function call_rules_defaults() {
  return array(
    'rules' => array(
      'rules_revert_crews_status_call_is_updated' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Revert crews status : Call is updated',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'crew statuses',
          'call' => 'call',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Updated content\'s field \'field_job_session_venue\' has been changed',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content containing changes',
                ),
                'node_unchanged' => array(
                  'type' => 'node',
                  'label' => 'Content not containing changes',
                ),
              ),
              'module' => 'CCK',
            ),
            '#name' => 'content_rules_field_changed',
            '#settings' => array(
              'field_name' => 'field_job_session_venue',
              '#argument map' => array(
                'node' => 'node',
                'node_unchanged' => 'node_unchanged',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '1' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Acecrew: revert statuses of Call crews',
              'arguments' => array(
                'call' => array(
                  'type' => 'node',
                  'label' => 'Call',
                ),
              ),
              'module' => 'Acecrew Custom',
            ),
            '#name' => 'acercrew_rule_call_crews_status_revert',
            '#settings' => array(
              '#argument map' => array(
                'call' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_revert_crews_status_job_is_updated' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Revert crews status : Job is updated',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'crew statuses',
          'call' => 'call',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Updated content\'s field \'field_job_venue\' has been changed',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content containing changes',
                ),
                'node_unchanged' => array(
                  'type' => 'node',
                  'label' => 'Content not containing changes',
                ),
              ),
              'module' => 'CCK',
            ),
            '#name' => 'content_rules_field_changed',
            '#settings' => array(
              'field_name' => 'field_job_venue',
              '#argument map' => array(
                'node' => 'node',
                'node_unchanged' => 'node_unchanged',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#type' => 'action',
            '#settings' => array(
              '#argument map' => array(
                'job' => 'node',
              ),
            ),
            '#name' => 'acercrew_rule_job_crews_status_revert',
            '#info' => array(
              'label' => 'Acecrew: revert statuses of Job crews',
              'arguments' => array(
                'job' => array(
                  'type' => 'node',
                  'label' => 'Job',
                ),
              ),
              'module' => 'Acecrew Custom',
            ),
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}

/**
 * Implementation of hook_views_api().
 */
function call_views_api() {
  return array(
    'api' => '2',
  );
}
