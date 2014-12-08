<?php

/**
 * Implementation of hook_imagecache_default_presets().
 */
function review_imagecache_default_presets() {
  $items = array(
    'user_picture' => array(
      'presetname' => 'user_picture',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale',
          'data' => array(
            'width' => '100',
            'height' => '',
            'upscale' => 0,
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function review_node_info() {
  $items = array(
    'review' => array(
      'name' => t('Review'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
    'user_review' => array(
      'name' => t('Review user'),
      'module' => 'features',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_rules_defaults().
 */
function review_rules_defaults() {
  return array(
    'rules' => array(
      'rules_job_has_been_completed' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Job has been completed',
        '#active' => 0,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'review',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Updated content is Job Create',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => array(
              'type' => array(
                'job' => 'job',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
          '1' => array(
            '#type' => 'condition',
            '#settings' => array(
              'field_name' => 'field_job_status',
              '#argument map' => array(
                'node' => 'node',
              ),
              'value' => array(
                '0' => array(
                  'value' => '6',
                ),
              ),
              'code' => '',
              'vars' => array(),
            ),
            '#name' => 'content_rules_field_has_value',
            '#info' => array(
              'label' => 'Updated content\'s field \'field_job_status\' has value',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'eval input' => array(
                '0' => 'code',
                '1' => 'value|0|value',
              ),
              'module' => 'CCK',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Execute my custom Acecrew code',
              'arguments' => array(
                'job' => array(
                  'type' => 'node',
                  'label' => 'Job',
                ),
              ),
              'module' => 'Acecrew Review',
            ),
            '#name' => 'acereview_rule_custom_code_execute',
            '#settings' => array(
              '#argument map' => array(
                'job' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_review_is_created' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Review is created',
        '#active' => 0,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'review',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Created content is Review',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#name' => 'rules_condition_content_is_type',
            '#settings' => array(
              'type' => array(
                'review' => 'review',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#type' => 'action',
            '#settings' => array(
              'field_name' => 'field_review_status',
              '#argument map' => array(
                'node' => 'node',
              ),
              'value' => array(
                '0' => array(
                  'value' => '1',
                ),
              ),
              'code' => '',
              'vars' => array(),
            ),
            '#name' => 'content_rules_action_populate_field',
            '#info' => array(
              'label' => 'Populate created content\'s field \'field_review_status\'',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'eval input' => array(
                '0' => 'code',
                '1' => 'value|0|value',
              ),
              'module' => 'CCK',
            ),
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'rules_review_is_updated' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Review is updated',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'review',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '0' => array(
              '#weight' => 0,
              '#info' => array(
                'label' => 'Updated content is Review',
                'arguments' => array(
                  'node' => array(
                    'type' => 'node',
                    'label' => 'Content',
                  ),
                ),
                'module' => 'Node',
              ),
              '#name' => 'rules_condition_content_is_type',
              '#settings' => array(
                'type' => array(
                  'review' => 'review',
                ),
                '#argument map' => array(
                  'node' => 'node',
                ),
              ),
              '#type' => 'condition',
            ),
            '#type' => 'OR',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#type' => 'action',
            '#settings' => array(
              'field_name' => 'field_review_status',
              '#argument map' => array(
                'node' => 'node',
              ),
              'value' => array(
                '0' => array(
                  'value' => '2',
                ),
              ),
              'code' => '',
              'vars' => array(),
            ),
            '#name' => 'content_rules_action_populate_field',
            '#info' => array(
              'label' => 'Populate updated content\'s field \'field_review_status\'',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'eval input' => array(
                '0' => 'code',
                '1' => 'value|0|value',
              ),
              'module' => 'CCK',
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
function review_views_api() {
  return array(
    'api' => '2',
  );
}
