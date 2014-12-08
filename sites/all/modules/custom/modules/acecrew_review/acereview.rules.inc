<?php
/**
 * Implements hook_rules_action_info().
 */
function acereview_rules_action_info() {
  $actions = array();

  $actions['acereview_rule_custom_code_execute'] = array(
    'label' => t('Execute my custom Acecrew code'),
    'arguments' => array(
      'job' => array(
        'type' => 'node',
        'label' => 'Job',
      ),
    ),
    'module' => 'Acecrew Review'
  );

  return $actions;
}

/**
 * Action: Executes after Job has been saved
 */
function acereview_rule_custom_code_execute($job) {
  global $base_url;
  // create review node by job and send email to client
  $job_nid = $job->nid;
  $review_id  = acecrew_get_review_by_job($job_nid);
  if (!$review_id) {
    // create Review by Job
    $url    = acereview_get_link_by_job($job_nid);
    $email  = acereview_get_client_email($job_nid);
    acereview_sent_email_to_client($email, $url, $job->field_job_number[0]['value']);
  }
}

/*
// Implementation of hook_rules_action_info()
function acereview_rules_action_info() {
    $actions = array(
        'acereview_action_create' => array(
            'group' => t('Ace Crew Rules'),
            'label' => t('Create new Review page'),
            'arguments' => array(
                'node' => array(
                    'type' => 'node',
                    'label' => t('Review Node'),
                )
            ),
            'module' => 'Ace Crew'
        ),
        'acereview_action_delete' => array(
            'group' => t('Ace Crew Rules'),
            'label' => t('Delete user reviews associated with deleted Review node'),
            'arguments' => array(
                'node' => array(
                    'type' => 'node',
                    'label' => t('Review Node'),
                )
            ),
            'module' => 'Ace Crew'
        ),
    );
    return $actions;
}


// Create review and user_review nodes, email the client
function acereview_action_create($node) {
    global $user, $base_url;

    //Store the Job ID in $nid variable
    $nid = $node->nid;

    $result = "";

    //First check if there is already a review for this job
    $query = "SELECT nid FROM {content_type_review} WHERE field_job_related_id_value = '%d'";
    $result = db_query($query, $nid);

    if(db_affected_rows($result) > 0) {
        drupal_set_message(t('Job review is not created: there is already a review for this job.'), "warning");
    } else {

        //In order to find users (crew members), find the call id's
        $query = "SELECT vid, field_session_callid_value FROM {content_type_job_session} WHERE field_session_job_nid_value = '%d'";
        $result = db_query($query, $nid);

        //One job can have many calls. Store them in array
        //Also store vid from content_type_job_session
        $cid = array();
        $jsid = array();
        while ($row = db_fetch_object($result)) {
            $cid[] = $row->field_session_callid_value;
            $jsid[] = $row->vid;
        }

        //Escape the values
        $cid = array_map( 'mysql_real_escape_string', $cid);
        $jsid = array_map( 'intval', $jsid);

        //Than find the users (crew members) associated with that call id
        $query = 'SELECT DISTINCT uid FROM {crew_call} WHERE cid IN ("' . implode('", "', $cid) . '")
            AND jsid IN (' . implode(', ', $jsid) . ')';
        $result = db_query($query);

        //If no users (crew members) found for this job do not create review
        if(db_affected_rows($result) < 1) {
            drupal_set_message(t('Job review is not created: there are no members assigned to this job.'), "warning");
        } else {

            //Create a Review
            $review_node = new stdClass;
            $review_node->type = 'review';
            $review_node->title = $nid . " - Review";

            $token = md5(uniqid(rand(),1));

            $review_node->field_job_related_id[0]['value'] = $node->nid;
            $review_node->field_review_date[0]['value'] = time();
            $review_node->field_review_status[0]['value'] = "Pending";
            $review_node->field_review_expiration_date[0]['value'] = 60 * 60 * 24;
            $review_node->field_review_code[0]['value'] =  $token;

            node_object_prepare($review_node);
            node_save($review_node);

            drupal_set_message(t("Review created"));

            //Create User Review (for each crew member)
            while ($row = db_fetch_object($result)) {
                $user_review_node = new stdClass;
                $user_review_node->type = 'user_review';
                $user_review_node->title = $nid . " - " . acereview_get_user_name_by_uid($row->uid) . " - Review";
                $user_review_node->field_related_review_id[0]['value'] = $review_node->nid;
                $user_review_node->field_user_review_user_id[0]['value'] = $row->uid;

                node_object_prepare($user_review_node);
                node_save($user_review_node);
            }

            //Send email to the client with link to review page
            $email_address = acereview_get_client_email($nid);
            $email_link = $base_url . "/crew-review/" . $token;
            acereview_sent_email_to_client($email_address, $email_link, $nid);
        }
    }

}


// Delete all user review nodes that are related to deleted review
function acereview_action_delete($node) {
    //Store the Review ID in $nid
    $nid = $node->nid;

    //Find all users (crew members) that are related to $nid
    $query = "SELECT * FROM {content_type_user_review} WHERE field_related_review_id_value = '%s'";
    $result = db_query($query, $nid);

    if(db_affected_rows($result) > 0) {
        while ($row = db_fetch_object($result)) {
            node_delete($row->nid);
        }
    }
}
*/
