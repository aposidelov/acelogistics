<?php

/**
 * Implementation of hook_rules_defaults().
 */
function tracker_log_rules_defaults() {
  return array(
    'rules' => array(
      'rules_acetracker_jobs_edit' => array(
        '#type' => 'rule',
        '#set' => 'event_node_presave',
        '#label' => 'Ace Tracker Jobs Edit',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Saved content is Job Create',
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
            '#weight' => 0,
            '0' => array(
              '#type' => 'AND',
              '#weight' => 0,
            ),
            '#type' => 'OR',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#type' => 'action',
            '#settings' => array(
              '#argument map' => array(
                'job_before' => 'node_unchanged',
                'job_after' => 'node',
              ),
            ),
            '#name' => 'at_job_edit_action',
            '#info' => array(
              'label' => 'Job: Job status log',
              'arguments' => array(
                'job_before' => array(
                  'type' => 'node',
                  'label' => 'Job Before',
                ),
                'job_after' => array(
                  'type' => 'node',
                  'label' => 'Job After',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_bookoff_create' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Ace Tracker Bookoff Create',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'user_bookedoff' => 'user_bookedoff',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Created content is User-Booked off',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Bookoff Create log',
              'arguments' => array(
                'bookoff' => array(
                  'type' => 'node',
                  'label' => 'Bookoff',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_bookoff_create_action',
            '#settings' => array(
              '#argument map' => array(
                'bookoff' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_bookoff_delete' => array(
        '#type' => 'rule',
        '#set' => 'event_node_delete',
        '#label' => 'Ace Tracker Bookoff Delete',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'user_bookedoff' => 'user_bookedoff',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Deleted content is User-Booked off',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Bookoff Delete log',
              'arguments' => array(
                'bookoff' => array(
                  'type' => 'node',
                  'label' => 'Bookoff',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_bookoff_delete_action',
            '#settings' => array(
              '#argument map' => array(
                'bookoff' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_bookoff_edit' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Ace Tracker Bookoff Edit',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'user_bookedoff' => 'user_bookedoff',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Updated content is User-Booked off',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Bookoff Edit log',
              'arguments' => array(
                'bookoff_before' => array(
                  'type' => 'node',
                  'label' => 'Bookoff Before',
                ),
                'bookoff_after' => array(
                  'type' => 'node',
                  'label' => 'Bookoff After',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_bookoff_edit_action',
            '#settings' => array(
              '#argument map' => array(
                'bookoff_before' => 'node_unchanged',
                'bookoff_after' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_calls_create' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Ace Tracker Calls Create',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'job_session' => 'job_session',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Created content is Job Call',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Call Create log',
              'arguments' => array(
                'call' => array(
                  'type' => 'node',
                  'label' => 'Call',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_call_create_action',
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
      'rules_ace_tracker_calls_delete' => array(
        '#type' => 'rule',
        '#set' => 'event_node_delete',
        '#label' => 'Ace Tracker Calls Delete',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'job_session' => 'job_session',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Deleted content is Job Call',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Call Delete log',
              'arguments' => array(
                'call' => array(
                  'type' => 'node',
                  'label' => 'Call',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_call_delete_action',
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
      'rules_ace_tracker_calls_edit' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Ace Tracker Calls Edit',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Updated content is Job Call',
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
                'job_session' => 'job_session',
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
              '#argument map' => array(
                'call_before' => 'node_unchanged',
                'call_after' => 'node',
              ),
            ),
            '#name' => 'at_call_edit_action',
            '#info' => array(
              'label' => 'Call log',
              'arguments' => array(
                'call_before' => array(
                  'type' => 'node',
                  'label' => 'Call Before',
                ),
                'call_after' => array(
                  'type' => 'node',
                  'label' => 'Call After',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_client_create' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Ace Tracker Client Create',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'client' => 'client',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Created content is Client',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Client Create log',
              'arguments' => array(
                'client' => array(
                  'type' => 'node',
                  'label' => 'Client',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_client_create_action',
            '#settings' => array(
              '#argument map' => array(
                'client' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_client_delete' => array(
        '#type' => 'rule',
        '#set' => 'event_node_delete',
        '#label' => 'Ace Tracker Client Delete',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'client' => 'client',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Deleted content is Client',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Client Delete log',
              'arguments' => array(
                'client' => array(
                  'type' => 'node',
                  'label' => 'Client',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_client_delete_action',
            '#settings' => array(
              '#argument map' => array(
                'client' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_client_edit' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Ace Tracker Client Edit',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'client' => 'client',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Updated content is Client',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Client Edit log',
              'arguments' => array(
                'client_before' => array(
                  'type' => 'node',
                  'label' => 'Client Before',
                ),
                'client_after' => array(
                  'type' => 'node',
                  'label' => 'Client After',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_client_edit_action',
            '#settings' => array(
              '#argument map' => array(
                'client_before' => 'node_unchanged',
                'client_after' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_crew_create' => array(
        '#type' => 'rule',
        '#set' => 'event_user_insert',
        '#label' => 'Ace Tracker Crew Create',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'User has role(s)',
              'arguments' => array(
                'user' => array(
                  'type' => 'user',
                  'label' => 'User',
                ),
              ),
              'module' => 'User',
            ),
            '#name' => 'rules_condition_user_hasrole',
            '#settings' => array(
              'roles' => array(
                '0' => 5,
              ),
              'operation' => 'OR',
              '#argument map' => array(
                'user' => 'account',
              ),
            ),
            '#type' => 'condition',
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Crew Create log',
              'arguments' => array(
                'crew' => array(
                  'type' => 'user',
                  'label' => 'Crew',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_crew_create_action',
            '#settings' => array(
              '#argument map' => array(
                'crew' => 'account',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_crew_delete' => array(
        '#type' => 'rule',
        '#set' => 'event_user_delete',
        '#label' => 'Ace Tracker Crew Delete',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'User has role(s)',
              'arguments' => array(
                'user' => array(
                  'type' => 'user',
                  'label' => 'User',
                ),
              ),
              'module' => 'User',
            ),
            '#name' => 'rules_condition_user_hasrole',
            '#settings' => array(
              'roles' => array(
                '0' => 5,
              ),
              'operation' => 'OR',
              '#argument map' => array(
                'user' => 'account',
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
                'crew' => 'account',
              ),
            ),
            '#name' => 'at_crew_delete_action',
            '#info' => array(
              'label' => 'Crew Delete log',
              'arguments' => array(
                'crew' => array(
                  'type' => 'user',
                  'label' => 'Crew',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_crew_edit' => array(
        '#type' => 'rule',
        '#set' => 'event_user_update',
        '#label' => 'Ace Tracker Crew Edit',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'OR',
            '0' => array(
              '#weight' => 0,
              '#info' => array(
                'label' => 'User has role(s)',
                'arguments' => array(
                  'user' => array(
                    'type' => 'user',
                    'label' => 'User',
                  ),
                ),
                'module' => 'User',
              ),
              '#name' => 'rules_condition_user_hasrole',
              '#settings' => array(
                'roles' => array(
                  '0' => 5,
                ),
                'operation' => 'OR',
                '#argument map' => array(
                  'user' => 'account',
                ),
              ),
              '#type' => 'condition',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#type' => 'action',
            '#settings' => array(
              '#argument map' => array(
                'crew_before' => 'account_unchanged',
                'crew_after' => 'account',
              ),
            ),
            '#name' => 'at_crew_edit_action',
            '#info' => array(
              'label' => 'Crew Edit log',
              'arguments' => array(
                'crew_before' => array(
                  'type' => 'user',
                  'label' => 'Crew Before',
                ),
                'crew_after' => array(
                  'type' => 'user',
                  'label' => 'Crew After',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#weight' => 0,
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_jobs_create' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Ace Tracker Jobs Create',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'job' => 'job',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Created content is Job Create',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Job Create log',
              'arguments' => array(
                'job' => array(
                  'type' => 'node',
                  'label' => 'Job',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_job_create_action',
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
      'rules_ace_tracker_jobs_delete' => array(
        '#type' => 'rule',
        '#set' => 'event_node_delete',
        '#label' => 'Ace Tracker Jobs Delete',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'job' => 'job',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Deleted content is Job Create',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Job Delete log',
              'arguments' => array(
                'job' => array(
                  'type' => 'node',
                  'label' => 'Job',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_job_delete_action',
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
      'rules_ace_tracker_supplement_create' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Ace Tracker Supplement Create',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'supplements' => 'supplements',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Created content is Supplements',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Supplement Create log',
              'arguments' => array(
                'supplement' => array(
                  'type' => 'node',
                  'label' => 'Supplement',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_supplement_create_action',
            '#settings' => array(
              '#argument map' => array(
                'supplement' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_supplement_delete' => array(
        '#type' => 'rule',
        '#set' => 'event_node_delete',
        '#label' => 'Ace Tracker Supplement Delete',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'supplements' => 'supplements',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Deleted content is Supplements',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Supplement Delete log',
              'arguments' => array(
                'supplement' => array(
                  'type' => 'node',
                  'label' => 'Supplement',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_supplement_delete_action',
            '#settings' => array(
              '#argument map' => array(
                'supplement' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_supplement_edit' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Ace Tracker Supplement Edit',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'supplements' => 'supplements',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Updated content is Supplements',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Supplement Edit log',
              'arguments' => array(
                'supplement_before' => array(
                  'type' => 'node',
                  'label' => 'Supplement Before',
                ),
                'supplement_after' => array(
                  'type' => 'node',
                  'label' => 'Supplement After',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_supplement_edit_action',
            '#settings' => array(
              '#argument map' => array(
                'supplement_before' => 'node_unchanged',
                'supplement_after' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_upload_crew_create' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Ace Tracker Upload Crew Create',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'crew_file_uploads' => 'crew_file_uploads',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Created content is Crew Uploads And Payrates',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Upload Crew Create log',
              'arguments' => array(
                'uploadcrew' => array(
                  'type' => 'node',
                  'label' => 'Upload Crew',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_uploadcrew_create_action',
            '#settings' => array(
              '#argument map' => array(
                'uploadcrew' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_upload_crew_edit' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Ace Tracker Upload Crew Edit',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'crew_file_uploads' => 'crew_file_uploads',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Updated content is Crew Uploads And Payrates',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Upload Crew Edit log',
              'arguments' => array(
                'uploadcrew_before' => array(
                  'type' => 'node',
                  'label' => 'Upload Crew Before',
                ),
                'uploadcrew_after' => array(
                  'type' => 'node',
                  'label' => 'Upload Crew After',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_uploadcrew_edit_action',
            '#settings' => array(
              '#argument map' => array(
                'uploadcrew_before' => 'node_unchanged',
                'uploadcrew_after' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_venue_create' => array(
        '#type' => 'rule',
        '#set' => 'event_node_insert',
        '#label' => 'Ace Tracker Venue Create',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'venue' => 'venue',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Created content is Venue',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Venue Create log',
              'arguments' => array(
                'venue' => array(
                  'type' => 'node',
                  'label' => 'Venue',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_venue_create_action',
            '#settings' => array(
              '#argument map' => array(
                'venue' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_venue_delete' => array(
        '#type' => 'rule',
        '#set' => 'event_node_delete',
        '#label' => 'Ace Tracker Venue Delete',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'venue' => 'venue',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Deleted content is Venue',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Venue Delete log',
              'arguments' => array(
                'venue' => array(
                  'type' => 'node',
                  'label' => 'Venue',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_venue_delete_action',
            '#settings' => array(
              '#argument map' => array(
                'venue' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_ace_tracker_venue_edit' => array(
        '#type' => 'rule',
        '#set' => 'event_node_update',
        '#label' => 'Ace Tracker Venue Edit',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'Tracker',
          'tracker_log' => 'tracker_log',
        ),
        '#status' => 'default',
        '#conditions' => array(
          '0' => array(
            '#type' => 'condition',
            '#settings' => array(
              'type' => array(
                'venue' => 'venue',
              ),
              '#argument map' => array(
                'node' => 'node',
              ),
            ),
            '#name' => 'rules_condition_content_is_type',
            '#info' => array(
              'label' => 'Updated content is Venue',
              'arguments' => array(
                'node' => array(
                  'type' => 'node',
                  'label' => 'Content',
                ),
              ),
              'module' => 'Node',
            ),
            '#weight' => 0,
          ),
        ),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Venue Edit log',
              'arguments' => array(
                'venue_before' => array(
                  'type' => 'node',
                  'label' => 'Venue Before',
                ),
                'venue_after' => array(
                  'type' => 'node',
                  'label' => 'Venue After',
                ),
              ),
              'module' => 'Acecrew Tracker',
            ),
            '#name' => 'at_venue_edit_action',
            '#settings' => array(
              '#argument map' => array(
                'venue_before' => 'node_unchanged',
                'venue_after' => 'node',
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}
