<?php

function acecrew_report_timesheets() {
    $my_settings = array(
        'basepath' => drupal_get_path('module', 'acecrew'),
    );
    drupal_add_js(drupal_get_path('module', 'acecrew') . '/theme/acecrew-timesheets.js');

    $output = drupal_get_form('acecrew_reports_timesheets_from', $users);
    return $output;
}

function acecrew_reports_timesheets_from(){
    $users = getCrewMembers();
    $users_active = getActiveCrewMembers();
    $users_non_active = getInactiveActiveCrewMembers();

    $form['#action'] = url("timesheets/generate/csv");

    $form['timesheets'] = array(
        '#type' => 'fieldset',
        '#title' => t('Please Select'),
        '#tree' => TRUE,
    );

    $form['timesheets']['start_date'] = array(
        '#type' => 'date_popup',
        '#title' => t('Start Date'),
        '#date_format' => 'Y-m-d',
        '#default_value' => date ("Y-m-d"),
        '#attributes' => array('id' => 'timesheets_start'),
    );

    $form['timesheets']['end_date'] = array(
        '#type' => 'date_popup',
        '#title' => t('End Date'),
        '#date_format' => 'Y-m-d',
        '#default_value' => date ("Y-m-d"),
        '#attributes' => array('id' => 'timesheets_end'),
    );

    $form['timesheets']['crews'] = array(
        '#type' => 'select',
        '#title' => t('All Crew Members'),
        '#default_value' => $users,
        '#options' => $users,
        '#multiple' => true,
        '#attributes' => array('size'=>10),
    );

    $form['timesheets']['crews_active'] = array(
        '#type' => 'select',
        '#title' => t('Active Crew Members'),
        '#options' => $users_active,
        '#multiple' => true,
        '#attributes' => array('size'=>10),
    );
    $form['timesheets']['crews_inactive'] = array(
        '#type' => 'select',
        '#title' => t('Inactive Crew Members'),
        '#options' => $users_non_active,
        '#multiple' => true,
        '#attributes' => array('size'=>10),
    );

    $form['timesheets']['show'] = array(
        '#type' => 'radios',
        '#title' => t('Filter Crew'),
        '#options' => array(1 => "Show all", 2 => "Show active only", 3 => "Show non active"),
        '#default_value' => 1
    );

    $form['timesheets']['submit'] = array(
        '#type' => 'button',
        '#value' => t('Submit'),
        '#attributes' => array('id' => 'acecrew_timesheets_submit'),
    );

    return $form;
}

function getCrewMembers() {
    $users = array();
    $query = "SELECT users.uid AS uid, users.name AS users_name
            FROM drupal_users users
            INNER JOIN drupal_users_roles users_roles ON users.uid = users_roles.uid
            WHERE users_roles.rid = 5 ORDER BY users_name ASC";
    $results = db_query($query);
    while($row = db_fetch_object($results)) {
        $users[(int) $row->uid] = $row->users_name;
    }

    return $users;
}

function getActiveCrewMembers() {
    $users = array();
    $query = "SELECT users.uid AS uid, users.name AS users_name
            FROM drupal_users users
            INNER JOIN drupal_users_roles users_roles ON users.uid = users_roles.uid
            WHERE users.status = 1
            AND users_roles.rid = 5 ORDER BY users_name ASC";
    $results = db_query($query);
    while($row = db_fetch_object($results)) {
        $users[(int) $row->uid] = $row->users_name;
    }

    return $users;
}

function getInactiveActiveCrewMembers() {
    $users = array();
    $query = "SELECT users.uid AS uid, users.name AS users_name
            FROM drupal_users users
            INNER JOIN drupal_users_roles users_roles ON users.uid = users_roles.uid
            WHERE users.status = 0
            AND users_roles.rid = 5 ORDER BY users_name ASC";
    $results = db_query($query);
    while($row = db_fetch_object($results)) {
        $users[(int) $row->uid] = $row->users_name;
    }

    return $users;
}

function timesheets_reports_generate() {
    define (REPORT_DIR, 'sites/default/files/');
    define (CSV, '.csv');
    define (ZIP, '.zip');

    // get selected dates and crew members
    $start = $_POST['timesheets']['start_date']['date'];
    $end = $_POST['timesheets']['end_date']['date'];

    $all = $_POST['timesheets']['crews'] ? $_POST['timesheets']['crews'] : array();
    $active = $_POST['timesheets']['crews_active'] ? $_POST['timesheets']['crews_active'] : array();
    $inactive = $_POST['timesheets']['crews_inactive'] ? $_POST['timesheets']['crews_inactive'] : array();

    $crews = array_merge($all, $active, $inactive);

    // create csv files
    foreach ($crews as $crew) {
        $user = user_load($crew);
        $fname = $user->name . "(" . $crew . ")" . CSV;
        $path = REPORT_DIR . $fname;
        $fp = fopen($path, 'w+');

        // get payment data
        $content = get_payment_of_crew($start, $end, $crew);
        $extr = array_splice($content, 4, -1);
        usort($extr, "cmp_timesheet_time");
        array_splice($content, 4, -1, $extr);

        //echo "<pre>";
        //die(var_dump($content));
        //echo "</pre>";

        foreach ($content as $fields) {
            fputcsv($fp, $fields, ';');
        }
        $content = array();

        fclose($fp);

        $csvs[$path] = $fname;
    }

    // create zip file
    $zip_file = new ZipArchive();
    $zip_path = REPORT_DIR . 'timesheets(' . date('Y-m-d') . ')'. ZIP;
    $zip_name = 'timesheets(' . date('Y-m-d') . ')'. ZIP;

    if ($zip_file->open($zip_path, ZIPARCHIVE::CREATE)!==TRUE) {
        exit("cannot open <$zip_path>\n");
    }

    foreach ($csvs as $csvpath => $name) {
        $zip_file->addFile($csvpath, $name);
    }
    $zip_file->close();

    // delete csv files
    foreach ($csvs as $csvpath => $name) {
        unlink($csvpath);
    }

    header("Content-type: application/zip");
    header("Content-Disposition: attachment; filename=$zip_name");
    header("Pragma: no-cache");
    header("Expires: 0");
    readfile("$zip_path");

    unlink($zip_path);

    /*header("Content-type: application/zip");
    header("Content-Disposition: attachment; filename=$zip_name");
    header("Pragma: no-cache");
    header("Expires: 0");
    // output data to the browser
    readfile("$zip_name");*/

//    drupal_goto($_SERVER['HTTP_REFERER']);
}

function get_payment_of_crew($start, $end, $crew_id) {
    $content = array();

    // title
    $content[] = array('ACE CREW TIMESHEET');

    // name
    $crew = user_load($crew_id);
    $content[] = array('Name', $crew->name);

    // month, start date, end date
    $start_date = date_parse($start);
    $end_date = date_parse($end);

    for ($m = $start_date['month']; $m < $end_date['month']; $m++) {
        $months .= $m . ' , ';
    }

    $months .= $end_date['month'];
    $content[] = array('Month', $months, 'Start Date', $start, 'End Date', $end);

    // fields and supplements name
    $fields = array('Date', 'Job No', 'Time', 'Client', 'Venue', '2Hrs Call', '3hr Call','Hours quoted', 'Extra Hours', );
    $field_count = count($fields);
    $supplement = '';
    $query = "SELECT value FROM {profile_values} WHERE fid=41 AND uid=$crew_id";
    $results = db_query($query);
    while ($row = db_fetch_object($results)) {
        $supplement = $row->value;
    }
    $supplement = explode(',', $supplement);

    $query4 = "SELECT * FROM {profile_values} WHERE fid=28 AND uid=$crew_id";
    $result4 = db_query($query4);
    $row4 = db_fetch_object($result4);
    $pay_rate = $row4->value;

    $query = "SELECT node.nid AS nid, node.title AS node_title FROM {node} node  WHERE node.type in ('supplements') AND (";
    for ($i = 0; $i < count($supplement); $i++) {
        $query .= "nid=$supplement[$i]";
        if ($i < count($supplement) - 1) $query .= " OR ";
    }
    $query .= ")";
    $results = db_query($query);
    $supplements = array();
    while ($row = db_fetch_object($results)) {
        $supplements[] = $row;
    }
    foreach ($supplements as $supp) {
        $fields[] = $supp->node_title;
        $field_count++;
    }

    $fields[] = 'Boundary Charge';
    $field_count++;
    $fields[] = 'Fine';
    $field_count++;
    $fields[] = 'No Show';
    $field_count++;

    $fields[] = 'Amount';
    $total_amount = 0;

    $content[] = $fields;


    // crew payment data
    $mkstart = converttomktime($start);
    $mkend = converttomktime($end);
    $mkend += (60 * 60 * 24);

    $sql = "SELECT DISTINCT job_session.field_session_job_nid_value FROM drupal_content_type_job_session job_session
              WHERE (unix_timestamp(job_session.field_job_session_date_time_value) >= $mkstart AND unix_timestamp(job_session.field_job_session_date_time_value) <= $mkend) AND job_session.vid IN (
                SELECT crew_call.jsid FROM drupal_crew_call crew_call WHERE crew_call.uid=$crew_id GROUP BY crew_call.jsid
              )";
    $results = db_query($sql);

    while ($row = db_fetch_object($results)) {
        $session_nids[] = $row->field_session_job_nid_value;
    }
    $session_nids = implode(', ', $session_nids);

    $query = "SELECT job.nid FROM drupal_content_type_job job
            WHERE job.nid IN ($session_nids) ORDER BY job.field_job_date_value ASC";
    $results = db_query($query);
    while ($row = db_fetch_object($results)) {
        // get job
        //$job = node_load($row->nid);
        $job = acecrew_get_job_row_by_id($row->nid);

        //$job_no = $job->field_job_number[0]['value']; // job no
        $job_no = $job->field_job_number_value; // job no

        // time
        $time = ''; // time

        // get client information
        $query1 = "SELECT * FROM {content_type_client} WHERE field_client_id_value=" . $job->field_job_client_name_value;
        $results1 = db_query($query1);
        while ($row1 = db_fetch_object($results1)) {
            $client = $row1;
        }

        // get venue information
        $query1 = "SELECT * FROM {content_type_venue} WHERE field_venue_id_value=" . $job->field_job_venue_value;
        $results1 = db_query($query1);
        while ($row1 = db_fetch_object($results1)) {
            $venue = $row1->field_venue_name_value;
        }

        // get 2hrs call
        $call_2hurs = ''; // 2hrs call

        // get 3hrs call
        $call_3hurs = ''; // 3hrs call

        // get extra hrs on 2/3 hrs call
        $call_extra_hrs= ''; // extra hrs on 2/3 hrs call

        // get job session information in current job
        $query1 = "SELECT nid FROM {content_type_job_session} WHERE field_session_job_nid_value=$row->nid ORDER BY field_session_callid_value ASC";
        $results1 = db_query($query1);
        while ($row1 = db_fetch_object($results1)) {
            $call = node_load($row1->nid);

            $datetime = $call->field_job_session_date_time[0]['value'];

            if(strtotime($datetime) >= ($mkend)) continue;
            if(strtotime($datetime) < $mkstart) continue;

            $tmp = explode(' ', $datetime);

            $data[] = $tmp[0];  // date
            $data[] = $job_no;  // job no
            $data[] = substr($tmp[1], 0, 5);  // time
            $data[] = $client->field_client_name_value;  // client
            $data[] = $venue;   // venue

            $query2 = "SELECT * FROM {crew_call} WHERE uid=$crew_id AND jsid=" . $call->vid;
            $result2 = db_query($query2);
            $row2 = db_fetch_object($result2);
            if (!$row2) { // || $row2->standard_crew != 1
                unset($data); continue;
            }
            if ($row2->standard_crew != 1) {
                $crew_rate = 0;
            } else {
                $crew_rate = _get_crew_payrate($call->vid, $crew->uid);
            }
            $hours_quoted = $call->field_job_session_hours[0]['value'];
            $extra_hours = $row2->additional_hours;
            $hours_worked = $hours_quoted + $extra_hours;   // hours worked
            $additional_crew_pay = $row2->additional_crew_pay;
             //$crew->profile_payrateid;
            //Fine
            $fine = $row2->fine;
            //No Show
            $no_show = $row2->no_show;
            //Total adjustment
            $total_add = $row2->crew_total_add;
            $total_reduce = $row2->crew_total_reduce;

            $call_amount = 0;
            $_2hrs_call_amount = 0;
            $_3hrs_call_amount = 0;
            if ($hours_quoted <= 2) {
              $_2hrs_call_amount = _get_2hrs_call_crew_payment_amount($job, $crew, $call);
              $call_amount += $_2hrs_call_amount;
            } else if ($hours_quoted <= 3) {
              $_3hrs_call_amount = _get_3hrs_call_crew_payment_amount($job, $crew, $call);
              $call_amount += $_3hrs_call_amount;
            } else {
              $call_amount += $crew_rate * $hours_quoted;
            }
            $data[] = $_2hrs_call_amount;       // 2hrs call
            $data[] = $_3hrs_call_amount;                 // 3hurs call
            $data[] = $hours_quoted <= 3 ? NULL : $hours_quoted;      // hours quoted
            $data[] = $extra_hours;       // extra hours

            $call_amount += $crew_rate * $extra_hours;
            $call_amount += $additional_crew_pay;

            // get supplement amount
            foreach ($supplements as $supp) {
                $query3 = "SELECT * FROM {crew_js_supplement} WHERE uid=$crew_id AND jsid=" . $call->vid . " AND supplement_id=" . $supp->nid;
                $result3 = db_query($query3);
                $row = db_fetch_object($result3);
                $ph = $row->crew_ph;
                $of = $row->crew_of;
                $supp_amount = $ph == NULL ? $of : $ph * $hours_worked;
                $data[] = $supp_amount;
                $call_amount += $supp_amount;
            }
            if ($call->field_add_boundary_charge[0]['value']) {
                $boundary_charge = $call->field_session_boundary_charge[0]['value'];
            } else {
                $boundary_charge = "0";
            }
            $data[] = $boundary_charge;
            $call_amount += $boundary_charge;
            $data[] = $fine;
            $call_amount -= $fine;
            $data[] = $no_show;

            $call_amount -= $no_show;

            $call_amount = $call_amount + $total_add - $total_reduce;

            $data[] = $call_amount;
            $total_amount += $call_amount;

            // add data row
            $content[] = $data;
            $data = array();

        }
        /*$jobs[$job_index]['job_session'] = $job_sessions;*/
    }

    for ($i = 1; $i < $field_count; $i++) {
        $total[] = '';
    }
    $total[] = 'Total: ';
    $total[] = $total_amount;
    $content[] = $total;

    return $content;
}

function converttomktime($date) {
    $arr = explode("-", $date);
    return mktime(0, 0, 0, $arr[1], $arr[2], $arr[0]);
}

//Helper function to sort crew members array by names
function cmp_timesheet_time($a, $b) {
    return strtotime($a[0]) - strtotime($b[0]);
}
