<?php
/*
 * $type == crew | generate научиться как сабмитать форму чтоб в ней был action
 */
function acecrew_review_report_spreadsheet(&$form_state, $crew_id = '') {

  drupal_add_js(drupal_get_path('module', 'acereview') . '/acereview-timesheets.js');

  $users = getCrewMembers();
  $users_active = getActiveCrewMembers();
  $users_non_active = getInactiveActiveCrewMembers();

  if (!isset($form_state['values']) && !empty($crew_id)) {
    $form_state['values']['timesheets']['crews'][$crew_id] = $crew_id;
    $form_state['values']['timesheets']['crews_active'][$crew_id] = $crew_id;
    $form_state['values']['timesheets']['crews_inactive'][$crew_id] = $crew_id;
    $form_state['values']['timesheets']['show'] = 1;

    $header = acecrew_report_get_table_header();
    $rows = acecrew_report_get_table_rows(array($crew_id));
    $table = theme('table', $header, $rows, '');
    unset($_SESSION['messages']['status']);
    drupal_set_message($table, 'status', FALSE);
  }

  if (sizeof($messages['status']) > 1) {
    unset($messages['status'][1]);
  }

  $form['timesheets'] = array(
    '#type' => 'fieldset',
    '#title' => t('Please Select'),
    '#tree' => TRUE,
  );
  $form['timesheets']['filter_by_date'] = array(
    '#type' => 'checkbox',
    '#title' => t('Filter by date'),
    '#default_value' => isset($form_state['values']) ? $form_state['values']['timesheets']['filter_by_date'] : 0,
  );
  $form['timesheets']['start_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('Start Date'),
    '#date_format' => 'Y-m-d',
    '#default_value' => isset($_POST['timesheets']) ? $_POST['timesheets']['start_date']['date'] : date("Y-m-d"),
    '#attributes' => array('id' => 'timesheets_start'),
  );
  $form['timesheets']['end_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('End Date'),
    '#date_format' => 'Y-m-d',
    '#default_value' => isset($_POST['timesheets']) ? $_POST['timesheets']['end_date']['date'] : date("Y-m-d"),
    '#attributes' => array('id' => 'timesheets_end'),
  );
  $form['timesheets']['crews'] = array(
    '#type' => 'select',
    '#title' => t('All Crew Members'),
    '#default_value' => isset($form_state['values']) ? $form_state['values']['timesheets']['crews'] : $users,
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
    '#default_value' => isset($form_state['values']) ? $form_state['values']['timesheets']['crews_active'] : $users_active,
  );
  $form['timesheets']['crews_inactive'] = array(
    '#type' => 'select',
    '#title' => t('Inactive Crew Members'),
    '#options' => $users_non_active,
    '#multiple' => true,
    '#attributes' => array('size'=>10),
    '#default_value' => isset($form_state['values']) ? $form_state['values']['timesheets']['crews_inactive'] : $users_inactive,
  );
  $form['timesheets']['show'] = array(
    '#type' => 'radios',
    '#title' => t('Filter Crew'),
    '#options' => array(1 => "Show all", 2 => "Show active only", 3 => "Show non active"),
    '#default_value' => isset($form_state['values']) ? $form_state['values']['timesheets']['show'] : 1,
  );
  $form['timesheets']['preview'] = array(
    '#type' => 'submit',
    '#value' => t('Preview'),
    '#attributes' => array('id' => 'acecrew_timesheets_submit'),
  );
  $form['timesheets']['generate'] = array(
    '#type' => 'submit',
    '#value' => t('Generate CSV file'),
    '#attributes' => array('id' => 'acecrew_timesheets_submit'),
  );

  return $form;
}

function acecrew_review_report_spreadsheet_submit(&$form, &$form_state) {
  if ($form_state['clicked_button']['#parents'][1] == 'preview') {
    // to save the state in form.. it should be rebuilt
    $form_state['rebuild'] = 1;
    $filter_by_date = $form_state['values']['timesheets']['filter_by_date'];
    $date_from      = $_POST['timesheets']['start_date']['date'];
    $date_to        = $_POST['timesheets']['end_date']['date'];
    $show           = $form_state['values']['timesheets']['show'];
    // show all
    if ($show == 1) {
      $crews = $form_state['values']['timesheets']['crews'];
    }
    // show active
    elseif ($show == 2) {
      $crews = $form_state['values']['timesheets']['crews_active'];
    }
    // show inactive
    elseif ($show == 3) {
      $crews = $form_state['values']['timesheets']['crews_inactive'];
    }
    $rows   = array();
    // One Crew Type Report
    if (sizeof($crews) == 1) {
      $header = acecrew_report_get_table_header();
      if ($filter_by_date) {
        $rows = acecrew_report_get_table_rows($crews, $date_from, $date_to);
      } else {
        $rows = acecrew_report_get_table_rows($crews);
      }
    }
    // One Crew Type Report
    else if (sizeof($crews) > 1) {
      $header = acecrew_report_multi_get_table_header();
      if ($filter_by_date) {
        $rows = acecrew_report_multi_get_table_rows($crews, $date_from, $date_to);
      } else {
        $rows = acecrew_report_multi_get_table_rows($crews);
      }
    }
    
    $table = theme('table', $header, $rows, '');
    unset($_SESSION['messages']['status']);
    drupal_set_message($table, 'status', FALSE);

  } elseif ($form_state['clicked_button']['#parents'][1] == 'generate') {
    $filter_by_date = $form_state['values']['timesheets']['filter_by_date'];
    $date_from      = $filter_by_date ? $_POST['timesheets']['start_date']['date'] : '';
    $date_to        = $filter_by_date ? $_POST['timesheets']['end_date']['date'] : '';
    $show           = $form_state['values']['timesheets']['show'];
    // show all
    if ($show == 1) {
      $crews = $form_state['values']['timesheets']['crews'];
    }
    // show active
    elseif ($show == 2) {
      $crews = $form_state['values']['timesheets']['crews_active'];
    }
    // show inactive
    elseif ($show == 3) {
      $crews = $form_state['values']['timesheets']['crews_inactive'];
    }
    acecrew_review_report_generate($crews, $date_from, $date_to);
    unset($_SESSION['messages']['status']);
  }
}

function acecrew_report_get_table_header() {
  $header = array();
  $header[] = t('Crew Member');
  $header[] = t('Job No.');
  $header[] = t('Date(First Call of job)');
  $header[] = t('Client');
  $header[] = t('Venue');
  $header[] = t('Timekeeping');
  $header[] = t('Manner');
  $header[] = t('Work Ethic');
  $header[] = t('Work Ability');
  $header[] = t('Communication Skills');
  $header[] = t('Comments');
  $header[] = t('Average');

  return $header;
}

function acecrew_report_get_table_rows($crew_ids, $date_from = '', $date_to = '') {
  $rows = array();

  $data = acecrew_report_get_rows($crew_ids, $date_from, $date_to);

  foreach ($data as $row) {
    $rows[] =
    array('data' => array(
      $row['crew_name'],
      $row['job_number'],
      $row['job_date'],
      $row['client_name'],
      $row['venue_name'],
      $row['keeping'],
      $row['manner'],
      $row['work_ethic'],
      $row['work_ability'],
      $row['com_skills'],
      $row['comments'],
      $row['average']
      ),
    );
  }

  return $rows;
}

function acecrew_report_get_rows($crew_ids, $date_from = '', $date_to = '') {
  $crews_str = implode(',' , $crew_ids);
  // TODO:  - is not worked;
  $sql = "SELECT ur.field_user_review_time_keeping_value AS keeping,
      ur.field_user_review_manner_value AS manner,
      ur.field_user_review_work_ethic_value AS work_ethic,
      ur.field_user_review_work_ability_value AS work_ability,
      ur.field_user_review_com_skills_value AS com_skills,
      ur.field_user_review_add_comments_value AS comments,
      j.field_job_number_value AS job_number,
      c.field_client_name_value AS client_name,
      v.field_venue_name_value AS venue_name,
      crew.name AS crew_name,
      DATE_FORMAT(FROM_UNIXTIME(j.field_job_date_value), '%Y-%m-%%d') AS job_date,
      j.nid AS job_nid
    FROM `drupal_content_type_user_review` ur
    INNER JOIN `drupal_content_type_review` r ON ur.field_related_review_id_value = r.nid
    INNER JOIN `drupal_content_type_job` j ON r.field_job_id_value = j.nid
    INNER JOIN `drupal_content_type_client` c ON c.field_client_id_value = j.field_job_client_name_value
    INNER JOIN `drupal_content_type_venue` v ON v.field_venue_id_value = j.field_job_venue_value
    INNER JOIN `drupal_users` crew ON crew.uid = ur.field_user_review_user_id_value
    WHERE field_user_review_user_id_value IN ('%s')";

  if (!empty($date_from) && !empty($date_to)) {
    $sql .= " HAVING job_date BETWEEN '%s' AND '%s'";
    $result = db_query($sql, $crews_str, $date_from, $date_to);
  } else {
    $result = db_query($sql, $crews_str);
  }

  $average_manner = 0;
  $average_work_ethic = 0;
  $average_work_ability = 0;
  $average_com_skills = 0;
  $average_average = 0;
  $i=0;
  $rows = array();
  while ($row = db_fetch_array($result)) {    
    /*$average_i = 0;
    $average_manner       += $row['manner'];
    $average_work_ethic   += $row['work_ethic'];
    $average_work_ability += $row['work_ability'];
    $average_com_skills   += $row['com_skills'];
    $average = ($row['manner'] + $row['work_ethic'] + $row['work_ability'] + $row['com_skills'])/4;
    $average_average      += $average;
    */
    $average_i = 0;
    if ($row['manner'] > 0) {
      $average_manner       += $row['manner'];
      ++$average_i;
    }
    if ($row['work_ethic'] > 0) {
      $average_work_ethic   += $row['work_ethic'];
      ++$average_i;
    }
    if ($row['work_ability'] > 0) {
      $average_work_ability += $row['work_ability'];
      ++$average_i;
    }
    if ($row['com_skills'] > 0) {
      $average_com_skills   += $row['com_skills'];
      ++$average_i;
    }
    $average = ($row['manner'] + $row['work_ethic'] + $row['work_ability'] + $row['com_skills'])/$average_i;    
    $average_average      += $average;

    $rows[$i]['crew_name']    = $row['crew_name'];
    $rows[$i]['job_number']   = $row['job_number'];
    $rows[$i]['job_date']     = $row['job_date'];
    $rows[$i]['client_name']  = $row['client_name'];
    $rows[$i]['venue_name']   = $row['venue_name'];
    $rows[$i]['keeping']      = $row['keeping'] ? acereview_get_timeKeeping($row['keeping']) : t('No Opinion');
    $rows[$i]['manner']       = $row['manner'] ? $row['manner'] : t('No Opinion');
    $rows[$i]['work_ethic']   = $row['work_ethic'] ? $row['work_ethic'] : t('No Opinion');
    $rows[$i]['work_ability'] = $row['work_ability'] ? $row['work_ability'] : t('No Opinion');
    $rows[$i]['com_skills']   = $row['com_skills'] ? $row['com_skills'] : t('No Opinion');
    $rows[$i]['comments']     = $row['comments'];
    $rows[$i]['average']      = $average;
    $i++;
  }

  $rows[$i]['crew_name']    = '';
  $rows[$i]['job_number']   = '';
  $rows[$i]['job_date']     = '';
  $rows[$i]['client_name']  = '';
  $rows[$i]['venue_name']   = '';
  $rows[$i]['keeping']      = '';
  $rows[$i]['manner']       = ($average_manner && $average_i) ? $average_manner/$average_i : t('No Opinion');
  $rows[$i]['work_ethic']   = ($average_work_ethic && $average_i) ? $average_work_ethic/$average_i : t('No Opinion');
  $rows[$i]['work_ability'] = ($average_work_ability && $average_i) ? $average_work_ability/$average_i : t('No Opinion');
  $rows[$i]['com_skills']   = ($average_com_skills && $average_i) ? $average_com_skills/$average_i : t('No Opinion');
  $rows[$i]['comments']     = '';
  $rows[$i]['average']      = ($average_average && $average_i) ? $average_average/$average_i : t('No Opinion');

  return $rows;
}

function acecrew_report_multi_get_table_header() {
  $header = array();
  $header[] = t('Crew Member');
  $header[] = t('Job No.');
  $header[] = t('Timekeeping: 1 - Late, 2 - On time, 3 - Early');
  $header[] = t('Manner');
  $header[] = t('Work Ethic');
  $header[] = t('Work Ability');
  $header[] = t('Communication Skills');
  $header[] = t('Average');

  return $header;
}

function acecrew_report_multi_get_rows($crew_ids, $date_from = '', $date_to = '') {
  $crews_str = implode(',' , $crew_ids);
  // TODO:  - is not worked;
  $sql = "SELECT AVG(ur.field_user_review_time_keeping_value) AS keeping,
      AVG(ur.field_user_review_manner_value) AS manner,
      AVG(ur.field_user_review_work_ethic_value) AS work_ethic,
      AVG(ur.field_user_review_work_ability_value) AS work_ability,
      AVG(ur.field_user_review_com_skills_value) AS com_skills,
      j.field_job_number_value AS job_number,
      crew.name AS crew_name,
      j.nid AS job_nid
    FROM `drupal_content_type_user_review` ur
    INNER JOIN `drupal_content_type_review` r ON ur.field_related_review_id_value = r.nid
    INNER JOIN `drupal_content_type_job` j ON r.field_job_id_value = j.nid
    INNER JOIN `drupal_content_type_client` c ON c.field_client_id_value = j.field_job_client_name_value
    INNER JOIN `drupal_content_type_venue` v ON v.field_venue_id_value = j.field_job_venue_value
    INNER JOIN `drupal_users` crew ON crew.uid = ur.field_user_review_user_id_value
    WHERE field_user_review_user_id_value IN (%s)";//'%s'

  if (!empty($date_from) && !empty($date_to)) {
    $sql .= " AND DATE_FORMAT(FROM_UNIXTIME(j.field_job_date_value), '%Y-%m-%%d') BETWEEN '%s' AND '%s'";
    $sql .= " GROUP BY field_user_review_user_id_value";
    $result = db_query($sql, $crews_str, $date_from, $date_to);
  } else {
    $sql .= " GROUP BY field_user_review_user_id_value";
    $result = db_query($sql, $crews_str);
  }

  $average_keeping = 0;
  $average_manner = 0;
  $average_work_ethic = 0;
  $average_work_ability = 0;
  $average_com_skills = 0;
  $average_average = 0;
  $i=0;
  $rows = array();
  while ($row = db_fetch_array($result)) {
    $average_i = 0;
    if ($row['manner'] > 0) {      
      ++$average_i;
    }
    if ($row['work_ethic'] > 0) {      
      ++$average_i;
    }
    if ($row['work_ability'] > 0) {      
      ++$average_i;
    }
    if ($row['com_skills'] > 0) {      
      ++$average_i;
    }

    $average = ($row['manner'] + $row['work_ethic'] + $row['work_ability'] + $row['com_skills'])/$average_i;        
    //$average = ($row['manner'] + $row['work_ethic'] + $row['work_ability'] + $row['com_skills'])/4;

    $rows[$i]['crew_name']    = $row['crew_name'];
    $rows[$i]['job_number']   = $row['job_number'];
    $rows[$i]['keeping']      = $row['keeping'] ? $row['keeping'] : t('No Opinion');
    $rows[$i]['manner']       = $row['manner'] ? $row['manner'] : t('No Opinion');
    $rows[$i]['work_ethic']   = $row['work_ethic'] ? $row['work_ethic'] : t('No Opinion');
    $rows[$i]['work_ability'] = $row['work_ability'] ? $row['work_ability'] : t('No Opinion');
    $rows[$i]['com_skills']   = $row['com_skills'] ? $row['com_skills'] : t('No Opinion');
    $rows[$i]['average']      = $average;
    $i++;
  }

  return $rows;
}

function acecrew_report_multi_get_table_rows($crew_ids, $date_from = '', $date_to = '') {
  $rows = array();

  $data = acecrew_report_multi_get_rows($crew_ids, $date_from, $date_to);

  foreach ($data as $row) {
    $rows[] =
    array('data' => array(
      $row['crew_name'],
      $row['job_number'],
      $row['keeping'],
      $row['manner'],
      $row['work_ethic'],
      $row['work_ability'],
      $row['com_skills'],
      $row['average']
      ),
    );
  }

  return $rows;
}


function acecrew_review_report_generate($crews, $date_from, $date_to) {
  $file_desc = '';
  $crews_count = sizeof($crews);
  if (!$crews_count) {
    return;
  }
  define (REPORT_DIR, 'sites/default/files/');
  define (CSV, '.csv');
  define (ZIP, '.zip');

  if ($crews_count == 1) {
    $header = acecrew_report_get_table_header();
    $rows   = acecrew_report_get_rows($crews, $date_from, $date_to);
    // create csv files
    $file_desc = $rows[0]['crew_name'];
  } else if ($crews_count > 1) {
    $header = acecrew_report_multi_get_table_header();
    $rows   = acecrew_report_multi_get_rows($crews, $date_from, $date_to);
    $file_desc = 'group-crews';
  }
  $fname = "Acecrew-review-(" . $file_desc . ")" . CSV;
  $path = REPORT_DIR . $fname;
  $fp = fopen($path, 'w+');
  fputcsv($fp, $header, ';');
  foreach ($rows as $row) {
      fputcsv($fp, $row, ';');
  }

  fclose($fp);

  header("Content-type: application/csv");
  header("Content-Disposition: attachment; filename=$fname");
  header("Pragma: no-cache");
  header("Expires: 0");
  readfile($path);

  unlink($path);
  exit();
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
