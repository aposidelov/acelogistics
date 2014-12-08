<?php

/**
 * @file
 * Helper functions for Ace Crew Review module
 */

/**
 * Return the field_job_related_id if the token is valid
 */
function acecrew_get_node_by_token($url_token) {
    $query = "SELECT * FROM {content_type_review} WHERE field_review_code_value = '%s' LIMIT 1";
    $result = db_query($query, $url_token);
    if(db_affected_rows($result) > 0) {
        $row = db_fetch_object($result);
        //Check if review was not already been made
        if($row->field_review_status_value != "Completed") {
            $current_time = time();
            $created = $row->field_review_date_value;
            $valid_for = $row->field_review_expiration_date_value;
            //Check if token is not expired
            if($current_time < $created + $valid_for) {
                return $row->nid;
            }
        }
    }
    return false;
}

/**
 * Return array of all crew members for select Review
 */
function acereview_get_crew_members_by_review_id($review_id) {
    $query = "SELECT * FROM {content_type_user_review} WHERE field_related_review_id_value = '%d'";
    $result = db_query($query, $review_id);
    $crew = array();
    if(db_affected_rows($result) > 0) {
        $i = 0;
        while ($row = db_fetch_object($result)) {
            $user_node = user_load($row->field_user_review_user_id_value);
            $crew[$i]["id"] = $user_node->uid;
            $crew[$i]["name"] = $user_node->name;
            $crew[$i]["picture"] = $user_node->picture ? $GLOBALS['base_url'] . '/' . $user_node->picture : "";
            $crew[$i]["time_keeping"] = $row->field_user_review_time_keeping_value;
            $crew[$i]["manner"] = $row->field_user_review_manner_value;
            $crew[$i]["work_ethic"] = $row->field_user_review_work_ethic_value;
            $crew[$i]["work_ability"] = $row->field_user_review_work_ability_value;
            $crew[$i]["communicational_skills"] = $row->field_user_review_com_skills_value;
            $crew[$i]["additional_comments"] = $row->field_user_review_add_comments_value;
            $i++;
        }
        return $crew;
    } else {
        return false;
    }
}

/**
 * Function for time keeping field
 */
function acereview_form_time_keeping($value) {
    $options = array("Early", "On Time", "Late");
    foreach($options as $option) {
        echo "<option value=\"$option\"";
        if($option == $value) echo 'selected="selected"';
        echo ">$option</option>";
    }
}

/**
 * Function for select fields
 */
function acereview_form_select_field($to, $value) {
    $options = range(1, $to);
    foreach($options as $option) {
        echo "<option value=\"$option\"";
        if($option == $value) echo 'selected="selected"';
        echo ">$option</option>";
    }
}

/**
 * Get venue name
 */
function acereview_get_venue($review_id) {
    $query = "SELECT field_venue_name_value FROM {content_type_venue} WHERE field_venue_id_value = (
        SELECT field_job_venue_value FROM {content_type_job} WHERE nid = (
            SELECT field_job_related_id_value FROM {content_type_review} WHERE nid = '%d'
        )
    ) LIMIT 1";
    $result = db_query($query, $review_id);

    if(db_affected_rows($result) > 0) {
        $row = db_fetch_object($result);
        return $row->field_venue_name_value;
    } else {
        return false;
    }
}

/**
 * Get job(session?) date
 */
function acereview_get_date($review_id) {
    $query = "SELECT field_job_session_date_time_value FROM {content_type_job_session} WHERE field_session_job_nid_value = (
            SELECT field_job_related_id_value FROM {content_type_review} WHERE nid = '%d'
        ) LIMIT 1";
    $result = db_query($query, $review_id);

    if(db_affected_rows($result) > 0) {
        $row = db_fetch_object($result);
        return $row->field_job_session_date_time_value;
    } else {
        return false;
    }
}

/**
 * Get user id (crew member) node from content_type_user_review table
 */
function acereview_get_user_node_id($review_id, $user_id) {
    $query = "SELECT nid FROM {content_type_user_review} WHERE field_related_review_id_value = '%d'
        AND field_user_review_user_id_value = '%d' LIMIT 1";
    $result = db_query($query, $review_id, $user_id);

    if(db_affected_rows($result) > 0) {
        $row = db_fetch_object($result);
        return $row->nid;
    }
}

/**
 * Update the review when form is saved
 */
function acereview_update_review_node($node_id) {
    $review_node = node_load($node_id);
    $review_node->field_review_status[0]['value'] = "Completed";
    node_object_prepare($review_node);
    node_save($review_node);
}

/**
 * Update users reviews (crew members) when form is saved
 */
function acereview_update_user_review_nodes($crew, $review_id) {
    foreach($crew as $key => $user) {
        $node_id = acereview_get_user_node_id($review_id, $key);
        $user_review_node = node_load($node_id);
        $user_review_node->field_user_review_time_keeping[0]['value'] = $user["time_keeping"];
        $user_review_node->field_user_review_manner[0]['value'] = $user["manner"];
        $user_review_node->field_user_review_work_ethic[0]['value'] = $user["work_ethic"];
        $user_review_node->field_user_review_work_ability[0]['value'] = $user["work_ability"];
        $user_review_node->field_user_review_com_skills[0]['value'] = $user["communicational_skills"];
        $user_review_node->field_user_review_add_comments[0]['value'] = $user["additional_comments"];
        node_object_prepare($user_review_node);
        node_save($user_review_node);
    }
}

/**
 * Get status of a review node
 */
function acereview_review_status($review_id) {
    if($review_id) {
        $review_node = node_load($review_id);
        $status = $review_node->field_review_status[0]['value'];
        return $status;
    }
    return false;
}

/**
 * Get client email for related job
 */
function acereview_get_client_email($job_id) {
    $query = "SELECT field_client_company_email_email FROM {content_type_client} WHERE field_client_id_value =
        (SELECT field_job_client_name_value FROM {content_type_job} WHERE nid = '%d') LIMIT 1";
    $result = db_query($query, $job_id);

    if(db_affected_rows($result) > 0) {
        $result = db_fetch_object($result);
        $email = $result->field_client_company_email_email;
        return $email;
    } else {
        drupal_set_message(t("Review email not sent to the client"), "warning");
    }
}

/**
 * Send email to client
 */
function acereview_sent_email_to_client($email_address, $link, $job_number) {
    module_load_include('inc', 'phpmailer', 'includes/phpmailer.drupal');
    $mail = new DrupalPHPMailer();
    $mail->IsMail();
    $mail->From = "crewreview@example.com";
    $mail->AddAddress($email_address);
    $mail->CreateBody();
    $mail->Subject  = t('Ace Crew Review Test');

    $contact_name = "";
    $message = "Dear $contact_name\n\n";
    $message .= "We recently completed job:$job_number and invoiced you. We would appreciate if you could take a few minutes to complete a review of the job for us.\n\n";
    $message .= "Please click here: $link\n\n";
    $message .= "Thank you\nAce Crew";


    /* ------------------------------------------------------------------------------------ delete from here */

    /*
    $message = "Dear $contact_name\r\n\r\n";
    $message .= "We recently completed job:$job_number and invoiced you. We would appreciate if you could take a few minutes to complete a review of the job for us.\r\n\r\n";
    $message .= "Please click here: \r\n$link\r\n\r\n";
    $message .= "Thank you\r\nAce Crew\r\n\r\n\r\n\r\n";

    $path = drupal_get_path('module', 'acereview');
    $file = $path . "/file.txt";

    dsm($file);

    file_put_contents($file, $message, FILE_APPEND);
    */

    /* --------------------------------------------------------------------------------------------- to here */


    $mail->Body = $message;

    if(!$mail->Send()) {
        drupal_set_message(t("Can't send email"));
    } else {
        drupal_set_message(t("Email sent to the client containing link to review page"));
    }
}

/**
 * Find username (crew member name) by id
 */
function acereview_get_user_name_by_uid($id) {
    $name = "";

    $query = "SELECT name FROM {users} WHERE uid = '%d'";
    $result = db_query($query, $id);

    if(db_affected_rows($result) > 0) {
        $result = db_fetch_object($result);
        $name = $result->name;
    }

    return $name;
}

/**
 * Get client (object) by id
 */
function acereview_get_client_by_id($id) {
    $client = "";

    $query = "SELECT * FROM {content_type_client} WHERE uid = '%d' LIMIT 1";
    $result = db_query($query, $id);

    if(db_affected_rows($result) > 0) {
        $client = db_fetch_object($result);
    }

    return $client;
}

/**
 * Get invoice number from job id
 */
function acereview_get_invoice_number_by_job_id($id) {
    $invoice_number = "";

    $query = "SELECT invoice_number
              FROM {acecrew_job_invoices} AS i, {content_type_job} AS j
              WHERE j.nid = '%d'
              AND j.field_job_number_value = i.job_id
              LIMIT 1";
    $result = db_query($query, $id);

    if(db_affected_rows($result) > 0) {
        $row = db_fetch_object($result);
        $invoice_number = $row->invoice_number;
    }

    return $invoice_number ? $invoice_number : 0;
}


/**
 * Get user name by user id
 */
function acereview_get_user_name_by_id($id) {
    $name = "";

    $query = "SELECT name FROM {users} WHERE uid = '%d' LIMIT 1";
    $result = db_query($query, $id);

    if(db_affected_rows($result) > 0) {
        $result = db_fetch_object($result);
        $name = $result->name;
    }

    return $name;
}

/**
 * Get user picture by user id
 */
function acereview_get_user_picture_by_id($id) {
    global $base_url;
    $picture_url = "";

    $query = "SELECT picture FROM {users} WHERE uid = '%d' LIMIT 1";
    $result = db_query($query, $id);

    if(db_affected_rows($result) > 0) {
        $result = db_fetch_object($result);
        $picture_url = $result->picture;
        if($picture_url) {
            $picture_url = $base_url . "/" . $picture_url;
        }
    }

    return $picture_url;
}

/**
 * Get venue name by user job id
 */
function acereview_get_venue_name_by_job_id($id) {
    $venue = "";

    $query = "SELECT field_venue_name_value
              FROM {content_type_venue} AS v, {content_type_job} AS j
              WHERE j.nid = '%d'
              AND j.field_job_venue_value = v.field_venue_id_value
              LIMIT 1";
    $result = db_query($query, $id);

    if(db_affected_rows($result) > 0) {
        $result = db_fetch_object($result);
        $venue = $result->field_venue_name_value;
    }

    return $venue;
}