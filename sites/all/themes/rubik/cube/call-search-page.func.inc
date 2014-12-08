<?php
function search_page() {
    echo drupal_get_form('call_search_form');
    get_form_data($data);
    clear_form_data();
    fetch_calls($data);
}

function call_search_form($form, &$form_state) {
    $form = array();

    $form['call_search_form'] = array(
        '#type' => 'fieldset',
        '#title' => t('Call Search'),
    );

    $form['call_search_form']['client_name'] = array(
        '#type' => 'textfield',
        '#autocomplete_path' => 'acecrew/client/autocomplete',
        '#size' => '100',
        '#value' => variable_get('client_name'),
        '#maxlength' => '100',
        '#title' => t('Client Name'),
    );

    $form['call_search_form']['venue_name'] = array(
        '#type' => 'textfield',
        '#autocomplete_path' => 'acecrew/venue/autocomplete',
        '#size' => '100',
        '#value' => variable_get('venue_name'),
        '#maxlength' => '100',
        '#title' => t('Venue Name'),
    );

    $form['call_search_form']['invoice_number'] = array(
        '#type' => 'textfield',
        '#size' => '100',
        '#value' => variable_get('invoice_number'),
        '#maxlength' => '100',
        '#title' => t('Invoice Number'),
    );

    $form['call_search_form']['po_number'] = array(
        '#type' => 'textfield',
        '#size' => '100',
        '#value' => variable_get('po_number'),
        '#maxlength' => '100',
        '#title' => t('PO Number'),
    );

    $form['call_search_form']['date_from'] = array(
        '#type' => 'date_popup',
        '#title' => t('Date From'),
        '#date_format' => 'Y-m-d',
        '#value' => variable_get('date_from'),
    );

    $form['call_search_form']['date_to'] = array(
        '#type' => 'date_popup',
        '#title' => t('Date To'),
        '#date_format' => 'Y-m-d',
        '#value' => variable_get('date_to'),
    );

    $form['call_search_form']['job_number'] = array(
        '#type' => 'textfield',
        '#size' => '20',
        '#value' => variable_get('job_number'),
        '#maxlength' => '100',
        '#title' => t('Job Number'),
    );

    $form['call_search_form']['job_status'] = array(
        '#type' => 'select',
        '#value' => variable_get('job_status'),
        '#options' => array(0=> 'All', 1 => 'Awaiting PO', 2 => 'Quote', 3 => 'Confirmed', 4 => 'Cancelled', 5 => 'Pencil', 6 => 'Invoiced', 7 => 'Invoice Sent'),
        '#title' => t('Job Status'),
    );

    $form['call_search_form']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Search'),
    );

    return $form;
}

function call_search_form_submit($form, &$form_state) {
    form_keep('set', $form['#post']);
    return;
}

function form_keep($type, $arr) {
    $func = 'variable_' . $type;
    foreach ($arr as $key => $value) {
        if ($key !== 'form_build_id' && $key !== 'form_id' && $key !== 'form_token' && $op !== 'Search') {
            $value = is_array($value) ? $value['date'] : $value;
            $data[$key] = $func($key, $value);
        }
    }

    return $data;
}

function get_form_data(&$data) {
    $arr = array('client_name' => NULL,
        'venue_name' => NULL,
        'invoice_number' => NULL,
        'po_number' => NULL,
        'date_from' => NULL,
        'date_to' => NULL,
        'job_number' => NULL,
        'job_status' => NULL);
    $data = form_keep('get', $arr);
}

function clear_form_data() {
    $arr = array('client_name' => NULL,
        'venue_name' => NULL,
        'invoice_number' => NULL,
        'po_number' => NULL,
        'date_from' => NULL,
        'date_to' => NULL,
        'job_number' => NULL,
        'job_status' => NULL);
    form_keep('del', $arr);
}

function fetch_calls($condition) {
    $header = array(t('Call Number'), t('Client Name'), t('Number of Crew'), t('Number of Hours'), t('Link to Job'), );
    $data = array();

    $query = "SELECT job_session.* FROM {content_type_job_session} job_session WHERE 1=1";
    $query .= $condition['date_from'] != NULL ? " AND job_session.field_job_session_date_time_value >= '" . $condition['date_from'] ."'": "";
    $query .= $condition['date_to'] != NULL ? " AND job_session.field_job_session_date_time_value <= '" . $condition['date_to'] ."'" : "";

    $result = db_query($query);

    while($row = db_fetch_object($result)) {

        $job_id = $row->field_session_job_nid_value;

        $job_status = get_status_by_id($job_id);
        if($condition['job_status']) {
            if ($condition['job_status'] != "" && $condition['job_status'] != $job_status)  continue;
        }

        $client_name = get_client_name_by_id(get_clientid_by_id($job_id));
        if ($condition['client_name'] != "" && $condition['client_name'] != $client_name)  continue;

        $venue_name = get_venue_name_by_id(get_venueid_by_id($job_id));
        if ($condition['venue_name'] != "" && $condition['venue_name'] != $venue_name)  continue;

        $job_number = get_jobnumber_by_id($job_id);
        if ($condition['job_number'] != "" && $condition['job_number'] != $job_number)  continue;

        $invoice_number = _get_invoice_number($job_id);
        if ($condition['invoice_number'] != "" && $condition['invoice_number'] != $invoice_number)  continue;

        $call[] = $row->field_session_callid_value; // call number
        $call[] = $client_name; // client name
        $call[] = $row->field_job_session_crew_value; // number of crew
        $call[] = $row->field_job_session_hours_value; // number of hours
        $call[] = '<a href="/node/' . $row->field_session_job_nid_value . '" type="_blank">Link to Job</a>'; // link to job page
        $data[] = array('data' => $call);
        unset($call);
    }

    echo theme_table($header, $data);
}

function get_client_name_by_id($logo_fid) {
    $query = "SELECT * FROM {content_type_client} client WHERE field_client_id_value=$logo_fid";
    $result = db_query($query);
    $row = db_fetch_object($result);
    return $row->field_client_name_value;
}

function get_venue_name_by_id($venue_id) {
    $query = "SELECT * FROM {content_type_venue} venue WHERE venue.field_venue_id_value=$venue_id";
    $result = db_query($query);
    $row = db_fetch_object($result);
    return $row->field_venue_name_value;
}



function get_status_by_id($job_id) {
    $query = "SELECT field_job_status_value FROM {content_type_job} WHERE nid = $job_id";
    $result = db_query($query);
    $row = db_fetch_object($result);
    return $row->field_job_status_value;
}

function get_clientid_by_id($job_id) {
    $query = "SELECT field_job_client_name_value FROM {content_type_job} WHERE nid = $job_id";
    $result = db_query($query);
    $row = db_fetch_object($result);
    return $row->field_job_client_name_value;
}

function get_venueid_by_id($job_id) {
    $query = "SELECT field_job_venue_value FROM {content_type_job} WHERE nid = $job_id";
    $result = db_query($query);
    $row = db_fetch_object($result);
    return $row->field_job_venue_value;
}

function get_jobnumber_by_id($job_id) {
    $query = "SELECT field_job_number_value FROM {content_type_job} WHERE nid = $job_id";
    $result = db_query($query);
    $row = db_fetch_object($result);
    return $row->field_job_number_value;
}