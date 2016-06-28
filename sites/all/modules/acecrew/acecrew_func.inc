<?php
                    
define('AWAITING_PO', 1);
define('QUOTE', 2);
define('CONFIRMED', 3);
define('CANCELLED', 4);
define('PENCIL', 5);
define('INVOICED', 6);
define('INVOICE_SENT', 7);

class acecrewmodule {
    // object instance
    private static $instance;

    private $currentJobId = null;
    private $currentClientId = null;
    private $nextJobCallId = null;
    private $mileAge = null;
    private $vatRate = null;
    private $boundaryCharge = null;

    private function __construct() { }

    private function __clone() { }

    public static function getInstance() {
        if (self::$instance === null) {
            self::$instance = new acecrewmodule();
        }
        return self::$instance;
    }

    public function getCurrentJobId()
    {
      return $this->currentJobId;
    }

    public function getCurrentClientId()
    {
      return $this->currentClientId;
    }
     //saf added
    public function getNextJobCallId()
    {
      return $this->nextJobCallId;
    }

    //anton added
    public function getMileAge() {
      return $this->mileAge;
    }

    public function getVatRate() {
      return $this->vatRate;
    }

    public function getBoundaryCharge() {
      return $this->boundaryCharge;
    }

    public function setCurrentJobId($id)
    {
      $this->currentJobId = $id;
    }

    public function setCurrentClientId($id)
    {
      $this->currentClientId = $id;
    }
     //saf added
    public function setNextJobCallId($callId)
    {
      $this->nextJobCallId = $callId;
    }

    //anton added
    public function setMileAge($mileage) {
      $this->mileAge = $mileage;
    }

    public function setVatRate($vatRate) {
      $this->vatRate = $vatRate;
    }

    public function setBoundaryCharge($boundaryCharge) {
      $this->boundaryCharge = $boundaryCharge;
    }

}
//saf added
function _acecrew_get_jobclient_contacts() {
    $curClientId = acecrewmodule::getInstance()->getCurrentClientId();

    $client = node_load($curClientId);

    $contacts = array();
    // If Default Contact is set - add it as first option to the list;
    // 0 (zero) is an index of Default Contact
    if (!empty($client->field_client_company_contact[0]['value'])) {
      $contacts[0] = $client->field_client_company_contact[0]['value'];
    }    
    if (isset($client->field_client_contact)) {
      foreach ($client->field_client_contact as $contact) {
        $contacts[$contact['item_id']] = $contact['value']['field_client_contact_name']['0']['value'];
      }
    }
    
    return $contacts;
}

function _acecrew_get_assigned_job_sessions_iterator($nid) {
    $query = "SELECT js.nid FROM {content_type_job_session} js
        JOIN {node} n ON js.field_session_job_nid_value = n.nid
        WHERE n.nid = '%d' ORDER BY js.field_job_session_date_time_value";
    $query_result =  db_query($query, $nid);

    return $query_result;
}

function _acecrew_get_assigned_job_sessions($nid) {
    $query_result =  _acecrew_get_assigned_job_sessions_iterator($nid);
    $sessions = array();
    while ($row = db_fetch_object($query_result)) {
        $node = node_load(array('nid' => $row->nid));

        //If call is not a plus call, do not render it
        if(!$node->field_job_session_plus_call[0]['value']) unset($node->field_job_session_plus_call);

        $node_rendered = node_view($node);
        $sessions[$row->nid]['content'] = $node_rendered;

        // required for Drupal 6
        module_load_include('inc', 'node', 'node.pages');

        // which nodeform you want
        $node_type = 'job_session';
        $form_id = $node_type . '_node_form';
        $form_state = array('type' => $node_type);

        $edit_form = '';//drupal_get_form($form_id, $node);

        $sessions[$row->nid]['form'] = $edit_form;
    }

    return $sessions;
}

function _acecrew_get_assigned_job_docs($nid) {
    $docs = array();

    $query = "SELECT ctj.field_job_number_value AS job_id, ctj.nid AS job_nid FROM {content_type_job} ctj WHERE ctj.nid = '%d' LIMIT 1";
    $query_result =  db_query($query, $nid);
    $row = db_fetch_object($query_result);
    $docs['job_id'] = $row->job_id;
    $docs['job_nid'] = $row->job_nid;

    $docs['invoices'] = array();
    /*$query = "SELECT ji.job_id, ji.invoice_id, n.created  FROM {content_type_job} ctj
        JOIN {acecrew_job_invoices} ji ON ctj.field_job_number_value = ji.job_id
        JOIN {invoice_invoices} ii ON ji.invoice_id = ii.iid
        JOIN {node} n ON ii.nid = n.nid WHERE ctj.nid = '%d'";*/
    $query = "SELECT aji.* FROM {acecrew_job_invoices} aji WHERE aji.job_id IN (SELECT ctj.field_job_number_value FROM {content_type_job} ctj WHERE ctj.nid = '%d') ORDER BY aji.created DESC";

    $query_result =  db_query($query, $nid);

    while ($row = db_fetch_object($query_result)){
        $docs['invoices'][$row->acecrew_job_invoice_id] = date('Y-m-d H:i:s', $row->created);
    }

    $docs['quotes'] = array();
    $query = "SELECT * FROM {acecrew_job_quotes} jq WHERE jq.job_id IN (SELECT ctj.field_job_number_value FROM {content_type_job} ctj WHERE ctj.nid = '%d') ORDER BY jq.created DESC";
    $query_result =  db_query($query, $nid);

    while ($row = db_fetch_object($query_result)){
        $docs['quotes'][$row->acecrew_job_quote_id] = date('Y-m-d H:i:s', $row->created);
    }

    $docs['costs'] = array();
    $query = "SELECT ajc.acecrew_job_cost_id, ajc.created FROM {acecrew_job_costs} ajc 
    INNER JOIN {content_type_job} ctj ON  ajc.job_id = ctj.field_job_number_value
    WHERE ctj.field_job_number_value = %d ORDER BY ajc.created DESC";
    $query_result =  db_query($query, $docs['job_id']);
    while ($row = db_fetch_object($query_result)){
        $docs['costs'][$row->acecrew_job_cost_id] = date('Y-m-d H:i:s', $row->created);
    }

    $docs['pro_inv'] = array();
    $query = "SELECT ajpi.acecrew_job_pro_inv_id, ajpi.created FROM {acecrew_job_pro_inv} ajpi 
    INNER JOIN {content_type_job} ctj ON  ajpi.job_id = ctj.field_job_number_value
    WHERE ctj.field_job_number_value = %d ORDER BY ajpi.created DESC";
    $query_result =  db_query($query, $docs['job_id']);
    while ($row = db_fetch_object($query_result)){
        $docs['pro_inv'][$row->acecrew_job_pro_inv_id] = date('Y-m-d H:i:s', $row->created);
    }

    return $docs;
}

//clear invoice module buffer
function _acecrew_clear_invoice_items($uid){
    $query = "DELETE FROM {invoice_items}
        WHERE uid = '%d'
        AND invoice_id = '0'";
    $query_result =  db_query($query, $uid);
}

//insert item in invoice module buffer
function _acecrew_add_invoice_item($description, $quantity, $unit_cost, $uid, $weight = 0){
    $vat = variable_get('invoice_vat', 0);
    $query = "INSERT INTO {invoice_items}
        (description, quantity, unitcost, vat, weight, invoice_id, uid, created) VALUES
        ('%s','%d','%f','%f','%d','%d','%d', NOW())";
    $query_result =  db_query($query, $description, $quantity, $unit_cost, $vat, $weight, 0, $uid);

}

function _get_invoice_number($job_id) {
  $result = db_query("SELECT invoice_number FROM {acecrew_job_invoices} WHERE job_id=%d", $job_id);
  $row = db_fetch_object($result);

  return $row->invoice_number;
}

function _set_invoice_number() {
    /*$is_invoice_exists = db_result(db_query("SELECT COUNT(*) FROM {acecrew_job_invoices}"));
  
    if (!$is_invoice_exists) {
        variable_set('invoice_inc', 0);
    }*/

    $invoice_inc = variable_get('invoice_inc', 0);
    variable_set('invoice_inc', $invoice_inc + 1);
    $query = "SELECT field_invoice_number_value FROM {content_type_admin_settings} LIMIT 1";
    $result = db_query($query);
    $row = db_fetch_object($result);
    if ($invoice_inc) {                
        return $row->field_invoice_number_value + $invoice_inc;
    } else {
        return $row->field_invoice_number_value;
    }
}

//set relate between job and invoice
function _acecrew_add_invoice_job_relate($job_id) {

  $invoice_number = _set_invoice_number();  
  $date = mktime();
  $query = "SELECT * FROM {acecrew_job_invoices} WHERE job_id = %d";
  $result = db_query($query, $job_id);
  $row = db_fetch_object($result);

  if (!$row) {
    $query = "INSERT INTO {acecrew_job_invoices} (job_id, invoice_number, created) VALUES (%d, %d, %d)";
    $result = db_query($query, $job_id, $invoice_number, $date);
  } else {
    $query = "UPDATE {acecrew_job_invoices} SET created = '%d' WHERE job_id = %d";
    $result = db_query($query, $date, $job_id);
  }
  $count = db_result(db_query('SELECT COUNT(*) FROM {acecrew_job_invoices} WHERE invoice_number = %d', $invoice_number));
  if ($count > 1) {
    $max = db_result(db_query('SELECT MAX(invoice_number) FROM {acecrew_job_invoices}'));
    ++$max;
    $query = "UPDATE {acecrew_job_invoices} SET invoice_number = %d WHERE job_id = %d";
    $result = db_query($query, $max, $job_id);
  }
}

function _acecrew_invoice_raised_job_status($job_nid) {        
    acecrew_update_job_status($job_nid, INVOICED);
}

function _acecrew_invoice_sent_job_status($invoice_id) {
    $job_nid = db_result(db_query('SELECT j.nid FROM {content_type_job} j 
        INNER JOIN {acecrew_job_invoices} i ON j.field_job_number_value = i.job_id
        WHERE i.acecrew_job_invoice_id = %d', $invoice_id));
    acecrew_update_job_status($job_nid, INVOICE_SENT);    
}

function acecrew_update_job_status($job_nid, $status) {    
    db_query("UPDATE {content_type_job} 
        SET field_job_status_value = %d 
        WHERE nid = %d", $status, $job_nid);  
    db_query("DELETE FROM {cache_content} WHERE cid LIKE 'content:%s%%'", $job_nid); 
}

// set relate between job and quote
function _acecrew_add_quote_job_relate($job_id) {
  $date = mktime();  
  $is_quote_exists = db_result(db_query("SELECT COUNT(*) FROM {acecrew_job_quotes} WHERE job_id = %d", $job_id));    
  if (!$is_quote_exists) {
    $query = "INSERT INTO {acecrew_job_quotes} (job_id, created) VALUES (%d, %d)";
    db_query($query, $job_id, $date);
  } else {
    $query = "UPDATE {acecrew_job_quotes} SET created = %d WHERE job_id = %d";
    db_query($query, $date, $job_id);
  }
}

// set relate between job and cost
function _acecrew_add_cost_job_relate($job_id) {
  $date = mktime();  
  $is_quote_exists = db_result(db_query("SELECT COUNT(*) FROM {acecrew_job_costs} WHERE job_id = %d", $job_id));    
  if (!$is_quote_exists) {
    $query = "INSERT INTO {acecrew_job_costs} (job_id, created) VALUES (%d, %d)";
    db_query($query, $job_id, $date);
  } else {
    $query = "UPDATE {acecrew_job_costs} SET created = %d WHERE job_id = %d";
    db_query($query, $date, $job_id);
  }
}

// set relate between job and cost
function _acecrew_add_proinv_job_relate($job_id) {
  $date = mktime();  
  $is_quote_exists = db_result(db_query("SELECT COUNT(*) FROM {acecrew_job_pro_inv} WHERE job_id = %d", $job_id));    
  if (!$is_quote_exists) {
    $query = "INSERT INTO {acecrew_job_pro_inv} (job_id, created) VALUES (%d, %d)";
    db_query($query, $job_id, $date);
  } else {
    $query = "UPDATE {acecrew_job_pro_inv} SET created = %d WHERE job_id = %d";
    db_query($query, $date, $job_id);
  }
}

function _acecrew_get_supplement($supp_id) {
    return node_load(array('nid' => $supp_id));
}

function _acecrew_get_job_node_by_id($job_id) {
  $job = false;
  $query = "SELECT ctj.nid FROM {content_type_job} ctj WHERE ctj.field_job_number_value = '%d'";
  $query_result =  db_query($query, $job_id);
  $row = db_fetch_object($query_result);
  if (!empty($row)){
    $job = node_load(array('nid' => $row->nid));
  }
  return $job;
}

function _acecrew_get_job_id_by_number($job_number) {
  $query = "SELECT ctj.nid FROM {content_type_job} ctj WHERE ctj.field_job_number_value = '%d'";
  $job_nid =  db_result(db_query($query, $job_number));
  return $job_nid;
}

function acecrew_get_client_by_id($client_id)
{
    $client = false;
    $query = "SELECT ctc.nid FROM {content_type_client} ctc WHERE ctc.field_client_id_value = '%d'";
    $query_result =  db_query($query, $client_id);
    $row = db_fetch_object($query_result);
    if (!empty($row)){
        $client = node_load(array('nid' => $row->nid));
    }
    return $client;
}

function acecrew_get_client_by_name($client_id) {
    $client = false;
    $query = "SELECT ctc.nid FROM {content_type_client} ctc WHERE ctc.field_client_name_value = '%s'";
    $query_result =  db_query($query, $client_id);
    $row = db_fetch_object($query_result);
    if (!empty($row)){
        $client = node_load(array('nid' => $row->nid));
    }
    return $client;
}

function _acecrew_get_client_emails($client_param) {
    if (is_object($client_param)) {
        $client = &$client_param;
    } else { 
        $client = acecrew_get_client_by_id($client_param);
    }
    $clientEmails = array();
    foreach ((array)$client->field_add_accounts as $contact) {
        $clientEmails[$contact['value']['field_accounts_email'][0]['email']] = array('name' => $contact['value']['field_accounts_contact'][0]['value'], 'email' => $contact['value']['field_accounts_email'][0]['email']);
    }   
    $clientEmails[$client->field_client_company_email[0]['email']] = array('name' => $client->field_client_name[0]['value'], 'email' => $client->field_client_company_email[0]['email']);
    foreach ((array)$client->field_client_contact as $contact) {
        $clientEmails[$contact['value']['field_client_contact_email'][0]['email']] = array('name' => $contact['value']['field_client_contact_name'][0]['value'], 'email' => $contact['value']['field_client_contact_email'][0]['email']);
    }

    return $clientEmails;
}

function _acecrew_get_client_emails_data($client_param) {
    if (is_object($client_param)) {
        $client = &$client_param;
    } else { 
        $client = acecrew_get_client_by_id($client_param);
    }
    $clientEmails = array();
    foreach ((array)$client->field_add_accounts as $contact) {
        $clientEmails[$contact['item_id']] = array('name' => $contact['value']['field_accounts_contact'][0]['value'], 'email' => $contact['value']['field_accounts_email'][0]['email']);
    }   
    $clientEmails[0] = array('name' => $client->field_client_name[0]['value'], 'email' => $client->field_client_company_email[0]['email']);
    foreach ((array)$client->field_client_contact as $contact) {
        $clientEmails[$contact['item_id']] = array('name' => $contact['value']['field_client_contact_name'][0]['value'], 'email' => $contact['value']['field_client_contact_email'][0]['email']);
    }

    return $clientEmails;
}


function acecrew_get_venue_by_id($venue_id) {
    $venue = false;
    $query = "SELECT ctv.nid FROM {content_type_venue} ctv WHERE ctv.field_venue_id_value = '%d'";
    $query_result =  db_query($query, $venue_id);
    $row = db_fetch_object($query_result);
    if (!empty($row)){
        $venue = node_load(array('nid' => $row->nid));
    }
    return $venue;
}

function acecrew_get_client_by_invoice_id($invoice_id) {
    $query = "SELECT ctc.nid FROM drupal_acecrew_job_invoices ji
        JOIN drupal_content_type_job ctj ON ji.job_id = ctj.field_job_number_value
        JOIN drupal_content_type_client ctc ON ctj.field_job_client_name_value = ctc.field_client_id_value
        WHERE ji.acecrew_job_invoice_id = %d";
    $query_result =  db_query($query, $invoice_id);
    $row = db_fetch_object($query_result);
    if (!empty($row)) {
        $client = node_load(array('nid' => $row->nid));
    }
    return $client;
}

function acecrew_get_client_email_by_cost_id($cost_id) {
    $query = "SELECT ctc.field_client_company_email_email AS client_company_email FROM drupal_acecrew_job_costs ajc
        INNER JOIN drupal_content_type_job ctj ON ajc.job_id = ctj.field_job_number_value
        INNER JOIN drupal_content_type_client ctc ON ctj.field_job_client_name_value = ctc.field_client_id_value
        WHERE ajc.acecrew_job_cost_id = %d";
    $client_company_email = db_result(db_query($query, $cost_id));
    
    return $client_company_email;
}

function acecrew_get_client_email_by_proinv_id($proinv_id) {
    $query = "SELECT ctc.field_client_company_email_email AS client_company_email FROM drupal_acecrew_job_pro_inv ajpi
        INNER JOIN drupal_content_type_job ctj ON ajpi.job_id = ctj.field_job_number_value
        INNER JOIN drupal_content_type_client ctc ON ctj.field_job_client_name_value = ctc.field_client_id_value
        WHERE ajpi.acecrew_job_cost_id = %d";
    $client_company_email = db_result(db_query($query, $proinv_id));
    
    return $client_company_email;
}

function acecrew_get_job_by_invoice_id($invoice_id, $only_id = TRUE) {
    $result = FALSE;
    $query = "SELECT ji.job_id FROM drupal_acecrew_job_invoices ji WHERE ji.acecrew_job_invoice_id = %d";
    $query_result =  db_query($query, $invoice_id);
    $row = db_fetch_object($query_result);
    if (!empty($row)) {
        if ($only_id) {
            $result = $row->job_id;
        } else {
            // TODO: now $row->job_id == field_job_number
            $result = node_load(array('nid' => $row->job_id));
        }
    }
    return $result;
}

function acecrew_get_invoice_number_by_id($invoice_id) {
    $result = FALSE;
    $query = "SELECT ji.invoice_number FROM drupal_acecrew_job_invoices ji WHERE ji.acecrew_job_invoice_id = %d";
    $result = db_result(db_query($query, $invoice_id));

    return $result;
}

function acecrew_get_quote_by_job_number($job_number) {
  $query = "SELECT jq.acecrew_job_quote_id FROM {acecrew_job_quotes} jq WHERE jq.job_id = %d";
  $quote_number = db_result(db_query($query, $job_number));
  return $quote_number;
}

function acecrew_get_client_by_quote_id($quote_id) {
    $query = "SELECT ctc.nid FROM drupal_acecrew_job_quotes jq
        JOIN drupal_content_type_job ctj ON jq.job_id = ctj.field_job_number_value
        JOIN drupal_content_type_client ctc ON ctj.field_job_client_name_value = ctc.field_client_id_value
        WHERE jq.acecrew_job_quote_id = %d";
    $query_result =  db_query($query, $quote_id);
    $row = db_fetch_object($query_result);
    if (!empty($row)) {
        $client = node_load(array('nid' => $row->nid));
    }
    return $client;
}

function acecrew_get_job_by_quote_id($quote_id, $only_id = TRUE) {
    $result = FALSE;
    $query = "SELECT jq.job_id FROM drupal_acecrew_job_quotes jq WHERE jq.acecrew_job_quote_id = %d";
    $query_result =  db_query($query, $quote_id);
    $row = db_fetch_object($query_result);
    if (!empty($row)) {
        if ($only_id) {
            $result = $row->job_id;
        } else {
            // TODO: now $row->job_id == field_job_number
            $result = node_load(array('nid' => $row->job_id));
        }
    }
    return $result;
}

function acecrew_get_job_by_cost_id($cost_id) {
    $result = FALSE;
    $query = "SELECT jq.job_id FROM drupal_acecrew_job_costs jq WHERE jq.acecrew_job_cost_id = %d";
    $job_id =  db_result(db_query($query, $cost_id));
    
    return $job_id;
}

function acecrew_get_job_by_proinv_id($proinv_id) {
    $result = FALSE;
    $query = "SELECT jq.job_id FROM drupal_acecrew_job_pro_inv jq WHERE jq.acecrew_job_pro_inv_id = %d";
    $job_id =  db_result(db_query($query, $proinv_id));
    
    return $job_id;
}

//??saf modify
/**
* get ADmin-Setting values by field name
*
* @param mixed $field_name
*/
function acecrew_get_ads($field_name){
 $query = "SELECT n.nid
        FROM {node} n
        WHERE n.type = '%s'
        ORDER BY nid ASC LIMIT 1";
    $nid =  db_result(db_query($query, 'admin_settings'));

    $node = node_load($nid);
    $valueArr = explode("\r\n", $node->{$field_name}[0]['value']);    
    $options = array();
    //generate options
    foreach($valueArr as $v){
      $options["$v"] = "$v/ Hour";
      $c  = 0;
    }    

    return $options;
}

//get pay rate form element
//??saf modify
function _acecrew_get_rates_form($payrateid = null, $skills = null) {

    //select available variants
    /*$query = "SELECT n.nid,
            cpr.field_payrate_name_value as payrate_name,
            cpr.field_payrate_perhour_value as perhour
        FROM {node} n JOIN {content_type_crew_payrates} cpr ON n.nid = cpr.nid
        WHERE n.type = '%s'
        ORDER BY perhour ASC";
    $query_result =  db_query($query, 'crew_payrates');

    //generate options
    $options = array();
    while ($row = db_fetch_object($query_result)) {
        $options[$row->nid] = $row->perhour  ;
    } */
    $options = acecrew_get_ads('field_admins_crewrates');
    //create select form element
    $form['Supplement']['acecrew_payrate_id'] = array(
        '#type' => 'select',
        '#title' => t('Pay Rate'),
        '#options' => $options,
        '#required' => TRUE,
        '#weight' => 99,
    );

    //set default(selected) value
    if ($payrateid){
        $form['Supplement']['acecrew_payrate_id']['#default_value'] = $payrateid;
    }

    return $form;
}

function acecrew_get_payrate($nid, $with_name = false){

    //select rate
    //?? saf
    return $nid;

    $query = "SELECT n.nid,
            cpr.field_payrate_name_value as payrate_name,
            cpr.field_payrate_perhour_value as perhour
        FROM {node} n JOIN {content_type_crew_payrates} cpr ON n.nid = cpr.nid
        WHERE n.nid = '%d'";

    $query_result = db_query($query, $nid);
    $row = db_fetch_object($query_result);

    if(empty($row)){
        return '';
    }

    if($with_name){
        $string = $row->payrate_name . ' (' . $row->perhour . 'GBP)';
    } else {
        $string = $row->perhour;
    }

    return $string;
}

function acecrew_get_user_rate($uid){
    $user = user_load($uid);
    $rate = acecrew_get_payrate($user->profile_payrateid);
    return $rate;
}

function _acecrew_save_session_crews_relate($crews, $session_id){
    $query = "DELETE FROM {acecrew_session_crews} WHERE session_nid = '%d'";
    $query_result =  db_query($query, $session_id);
    foreach($crews as $crew){
        $query = "INSERT INTO {acecrew_session_crews}
            (session_nid, uid) VALUES
            ('%d', '%d')";
        $query_result =  db_query($query, $session_id, $crew);
    }
}

function acecrew_get_user_report($startDate, $endDate, $user, $is_html = false){
    $startDate = explode('-', $startDate);
    $endDate = explode('-', $endDate);
    $startDate = date("Y-m-d", mktime(0, 0, 0, $startDate[1], $startDate[2], $startDate[0]));
    $endDate = date("Y-m-d", mktime(0, 0, 0, $endDate[1], $endDate[2], $endDate[0]));
    $fines = acecrew_get_user_report_fines($startDate, $endDate, $user);
    $clothing = acecrew_get_user_report_clothing($startDate, $endDate, $user);
    $hours_quoted = acecrew_get_user_report_hours($startDate, $endDate, $user);

    $report = array(
        'hours' => $hours_quoted,
        'fines' => $fines,
        'clothing' => $clothing,
    );

    if ($is_html){
        $report = theme('acecrew_report_table', $report);
    }

    return $report;
}

function acecrew_get_user_report_fines($startDate, $endDate, $user){
    $fines = array();
    $query = "SELECT f.nid AS fine_id, fr.nid AS fine_rate_id FROM {content_type_fines} f
        JOIN {content_type_fines_rates} fr ON f.field_fine_amount_value = fr.nid
        WHERE DATE(f.field_fine_date_value) BETWEEN '%s' AND '%s'
            AND f.field_fine_staff_id_value = %d
        ORDER BY f.field_fine_date_value ASC";

    $query_result = db_query($query, $startDate, $endDate, $user);
    while($row = db_fetch_object($query_result)){
        $fine = node_load(array('nid' => $row->fine_id));
        $fine_rate = node_load(array('nid' => $row->fine_rate_id));

        $fines[$fine->nid] = array(
            'value' => floatval('-' . $fine_rate->field_fine_rate_amount[0]['value']),
            'name' =>  $fine_rate->field_fine_rate_name[0]['value'] . ' (' . substr($fine->field_fine_date[0]['value'], 0, 10) . ')',
        );
    }
    return $fines;
}

function acecrew_get_user_report_clothing($startDate, $endDate, $user){
    $uniforms = array();

    $query = "SELECT up.uniform_nid AS unid FROM {acecrew_uniform_pays} up
        WHERE DATE(up.pay_month) BETWEEN '%s' AND '%s'
            AND up.uid = %d";

    $query_result = db_query($query, $startDate, $endDate, $user);
    while($row = db_fetch_object($query_result)){
        $uniform = node_load(array('nid' => $row->unid));

        $value = $uniform->field_unif_amount[0]['value'] / $uniform->field_unif_payment[0]['value'];
        $value = round($value, 2);
        $value = floatval('-' . $value);

        $uniforms[$uniform->nid] = array(
            'value' => $uniforms[$uniform->nid]['value'] + $value,
            'name' => $uniform->field_unif_item[0]['value']
        );
    }

    return $uniforms;
}

function acecrew_get_user_report_hours($startDate, $endDate, $user){

    $query = "SELECT js.nid FROM drupal_content_type_job_session js
       JOIN drupal_acecrew_session_crews sc ON js.nid = sc.session_nid
       WHERE DATE(js.field_job_session_date_time_value) BETWEEN '%s' AND '%s'
        AND sc.uid = %d";


    $hours_enrolled = 0;
    $hours_worked = 0;
    $query_result = db_query($query, $startDate, $endDate, $user);
    while($row = db_fetch_object($query_result)){
        $session = node_load(array('nid' => $row->nid));
        foreach($session->field_job_session_crews as $session_crew){
            $crew_hours_worked = $session_crew['value']['field_crew_job_session_hours_wor'][0]['value'];
            $crew_name = $session_crew['value']['field_crew_job_session_name'][0]['value'];
            if(!empty($crew_hours_worked) && $crew_name == $user){

                $hours_worked += $crew_hours_worked;
                switch ($crew_hours_worked){
                    case 1:
                        $hours_enrolled += 3;
                        break;
                    case 2:
                        $hours_enrolled += 3;
                        break;
                    case 3:
                        $hours_enrolled += 4;
                        break;
                    default:
                        $hours_enrolled += $hours_worked;
                }
            }
        }
    }

    $user_rate = acecrew_get_user_rate($user);
    $hours_worked_cost = $user_rate * $hours_worked;
    $hours_worked_cost = round($hours_worked_cost, 2);

    $hours_enrolled_cost = $user_rate * $hours_enrolled;
    $hours_enrolled_cost = round($hours_enrolled_cost, 2);

    $crew_hours = array();
    $crew_hours[0] = array(
        'value' => $hours_enrolled_cost,
        'name' => $hours_enrolled . t('h. worked by ') . $user_rate . 'GBP',
    );

    return $crew_hours;
}

function _acecrew_get_client_nid_by_job_nid($job_nid){
    $query = "SELECT c.nid FROM drupal_content_type_job j
        JOIN drupal_content_type_client c ON j.field_job_client_name_value = c.field_client_id_value
        WHERE j.nid = '%d'";
    $query_result =  db_query($query, $job_nid);
    $row = db_fetch_object($query_result);
    return $row->nid;
}

function _quote_dompdf_include_lib() {
    require_once(dirname(__FILE__) .'/dompdf/dompdf_config.inc.php');
}

function _acecrew_quote_get_html($quote_id, $type = 'print') {    
    $job = NULL;
    $query = "SELECT ctj.*, ajq.*, cs.field_cancellation_status_value AS cancellation_status FROM {content_type_job} ctj LEFT JOIN `drupal_content_field_cancellation_status` cs ON cs.nid = ctj.nid, {acecrew_job_quotes} ajq WHERE ajq.job_id=ctj.field_job_number_value AND ajq.acecrew_job_quote_id='%s'";
    $job = db_fetch_object(db_query($query, $quote_id));

    $client = _get_client_by_job($job);
    $client_contact = _get_client_contact_by_id($job);
    $venue = _get_venue_by_job($job);
    $callings = _get_callings_by_job($job);

    $html = '<!doctype>';
    $html .= '<head>';
    $html .= '<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-15" />';
    $html .= '<html><head>';
    $html .= '<style>table {page-break-before:auto;font-size:8px;} td {height: 10px;}</style>';
    $html .= '</head><body>';

    $html .= theme_acecrew_quote_body($job, $client, $client_contact, $venue, $callings);

    // The eurosign is not supported as applicable character, so replace it with a ascii code

    $html .= '</body></html>';
    return $html;
}

function _acecrew_invoice_get_html($invoice_id, $type = 'print') {
    $job = NULL;
    
    $query = "SELECT ctj.*, aji.*, cs.field_cancellation_status_value AS cancellation_status FROM {content_type_job} ctj LEFT JOIN `drupal_content_field_cancellation_status` cs ON cs.nid = ctj.nid, {acecrew_job_invoices} aji WHERE aji.job_id=ctj.field_job_number_value AND aji.acecrew_job_invoice_id='%s'";
    $job = db_fetch_object(db_query($query, $invoice_id));

    $client = _get_client_by_job($job);
    $client_contact = _get_client_contact_by_id($job);
    $venue = _get_venue_by_job($job);
    $callings = _get_callings_for_invoice_by_job($job);

    $html = '<!doctype>';
    $html .= '<head>';
    $html .= '<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-15" />';
    $html .= '<html><head>';
    $html .= '<style>table {page-break-before:auto;font-size:8px;} td {height: 10px;}</style>';
    $html .= '</head>';
    $html .= '<body style="">';
    $html .= theme_acecrew_invoice_body($job, $client, $client_contact, $venue, $callings);
    $html .= '</body>';
    // The eurosign is not supported as applicable character, so replace it with a ascii code

    //$html .= '</html>';
    return $html;
}

function _acecrew_cost_get_html($cost_id, $type = 'print') {
    $job = NULL;
    
    $query = "SELECT ctj.*, ajc.*, cs.field_cancellation_status_value AS cancellation_status FROM {content_type_job} ctj LEFT JOIN `drupal_content_field_cancellation_status` cs ON cs.nid = ctj.nid, {acecrew_job_costs} ajc WHERE ajc.job_id=ctj.field_job_number_value AND ajc.acecrew_job_cost_id='%s'";
    $job = db_fetch_object(db_query($query, $cost_id));    

    $client = _get_client_by_job($job);
    $client_contact = _get_client_contact_by_id($job);
    $venue = _get_venue_by_job($job);
    $callings = _get_callings_for_invoice_by_job($job);

    $html = '<!doctype>';
    $html .= '<head>';
    $html .= '<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-15" />';
    $html .= '<html><head>';
    $html .= '<style>table {page-break-before:auto;font-size:8px;} td {height: 10px;}</style>';
    $html .= '</head><body>';

    $html .= theme_acecrew_cost_body($job, $client, $client_contact, $venue, $callings);

    // The eurosign is not supported as applicable character, so replace it with a ascii code

    $html .= '</body></html>';
    return $html;
}

function _acecrew_proinv_get_html($proinv_id, $type = 'print') {
    $job = NULL;
    
    $query = "SELECT ctj.*, ajc.*, cs.field_cancellation_status_value AS cancellation_status FROM {content_type_job} ctj LEFT JOIN `drupal_content_field_cancellation_status` cs ON cs.nid = ctj.nid, {acecrew_job_pro_inv} ajc WHERE ajc.job_id=ctj.field_job_number_value AND ajc.acecrew_job_pro_inv_id='%s'";
    $job = db_fetch_object(db_query($query, $proinv_id));    

    $client = _get_client_by_job($job);
    $client_contact = _get_client_contact_by_id($job);
    $venue = _get_venue_by_job($job);
    $callings = _get_callings_for_invoice_by_job($job);

    $html = '<!doctype>';
    $html .= '<head>';
    $html .= '<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-15" />';
    $html .= '<html><head>';
    $html .= '<style>table {page-break-before:auto;font-size:8px;} td {height: 10px;}</style>';
    $html .= '</head><body>';

    $html .= theme_acecrew_proinv_body($job, $client, $client_contact, $venue, $callings);

    // The eurosign is not supported as applicable character, so replace it with a ascii code

    $html .= '</body></html>';
    return $html;
}

function _get_client_by_job($job) {
    $client = NULL;
    $query = "SELECT * FROM {content_type_job} ctj, {content_type_client} ctc WHERE ctj.field_job_client_name_value = ctc.field_client_id_value and ctj.vid='%d'";
    $query_result = db_query($query, $job->vid);
    while($row = db_fetch_object($query_result)) {
        $client = $row;
    }

    return $client;
}

function _get_client_contact_for_sms($id, $job_id) {
    // Default client contact
    if (empty($id)) {

        /*
        SELECT ctc.field_client_company_contact_value AS default_contact_name,
        ctc.field_default_contact_mobile_value AS default_contact_mobile
        FROM `drupal_content_type_client` ctc
        INNER JOIN `drupal_content_type_job` ctj
        ON ctc.field_client_id_value = ctj.field_job_client_name_value
        WHERE ctj.nid = 6485


        SELECT *
        FROM `drupal_content_type_job` ctj
        WHERE ctj.nid = 6485

        SELECT *
        FROM `drupal_content_type_client` ctc
        WHERE ctc.nid = 106
        106

         */

        $query = "SELECT ctc.field_client_company_contact_value AS default_contact_name,
        ctc.field_default_contact_mobile_value AS default_contact_mobile
        FROM {content_type_client} ctc
        INNER JOIN {content_type_job} ctj ON ctc.field_client_id_value = ctj.field_job_client_name_value
        WHERE ctj.nid = %d";
        $query_result = db_query($query, $job_id);
        $row = db_fetch_object($query_result);
        return array(
            $row->default_contact_name,
            $row->default_contact_mobile,
        );
    }
    $client = NULL;
    $query = "SELECT field_client_contact_name_value, field_client_contact_mobile_value FROM {content_type_client_contact} WHERE vid = '%d'";
    $query_result = db_query($query, $id);
    $row = db_fetch_object($query_result);

    if($row->field_client_contact_name_value) {
        return array($row->field_client_contact_name_value, $row->field_client_contact_mobile_value);
    } else {

        $query = "SELECT cfcc.field_client_contact_value
                    FROM {content_type_job} ctj INNER JOIN {content_field_client_contact} cfcc
                    ON ctj.field_job_client_contact_value = cfcc.field_client_contact_item_id
                    WHERE ctj.nid  = '%d'";
        $query_result = db_query($query, $job_id);
        $row = db_fetch_object($query_result);
        $contact[] = unserialize($row->field_client_contact_value);

        return array($contact[0]['field_client_contact_name'][0]['value'], $contact[0]['field_client_contact_mobile'][0]['value']) ;

    }

}

function _get_contact_data_by_contact_vid($contact_vid, $job_nid = NULL) {    
    if ($contact_vid == 0 && is_numeric($contact_vid) && !is_null($job_nid)) {
        return db_fetch_array(db_query('SELECT ctc.field_client_company_telephone_value AS mobile, ctc.field_client_company_contact_value AS name FROM {content_type_job_session} js
                            INNER JOIN {content_type_job} ctj ON ctj.nid = js.field_session_job_nid_value
        INNER JOIN {content_type_client} ctc ON ctc.field_client_id_value = ctj.field_job_client_name_value
        WHERE ctj.nid = %d', $job_nid));
    }
    
    return db_fetch_array(db_query('SELECT field_client_contact_name_value AS name, field_client_contact_mobile_value AS mobile FROM {content_type_client_contact} WHERE vid = %d', $contact_vid));
}

function _get_client_contact_by_id($job) {
    $client_contact = NULL;

    $query = "SELECT * FROM {content_type_job} ctj, {content_type_client_contact} ctcc WHERE ctj.field_job_client_contact_value = ctcc.vid and ctj.vid='%d'";
    $query_result = db_query($query, $job->vid);
    while($row = db_fetch_object($query_result)) {
        $client_contact = $row;
    }

    return $client_contact;
}

function _get_venue_by_job($job) {
    $venue = NULL;

    $query = "SELECT * FROM {content_type_job} ctj, {content_type_venue} ctv WHERE ctj.field_job_venue_value = ctv.field_venue_id_value and ctj.vid='%d'";
    $query_result = db_query($query, $job->vid);
    while($row = db_fetch_object($query_result)) {
        $venue = $row;
    }

    return $venue;
}

function _get_callings_by_job($job) {
    $callings = array();

    $query = "SELECT ctjs.*, cs.field_cancellation_status_value AS cancellation_status
    FROM `drupal_content_type_job` ctj 
    INNER JOIN `drupal_content_type_job_session` ctjs ON ctjs.field_session_job_nid_value = ctj.nid
    LEFT JOIN `drupal_content_field_cancellation_status` cs ON cs.nid = ctjs.nid
    INNER JOIN `drupal_node` jsn ON jsn.nid = ctjs.nid
    WHERE jsn.status = 1 AND ctj.vid ='%d'
    ORDER BY ctjs.field_job_session_date_time_value"; //     
       
    //$query = "SELECT * FROM {content_type_job} ctj, {content_type_job_session} ctjs WHERE ctjs.field_session_job_nid_value = ctj.nid and ctj.vid='%d'";
    $query_result = db_query($query, $job->vid);
    while($row = db_fetch_object($query_result)) {
        $supplement = _get_call_supplement($row->nid);
        $call['data'] = $row;
        $call['supplements'] = $supplement;
        $callings[] = $call;
    }

    return $callings;
}

function _get_callings_for_invoice_by_job($job) {
    $callings = array();

    $query = "SELECT ctjs.*, cs.field_cancellation_status_value AS cancellation_status 
    FROM `drupal_content_type_job` ctj 
    INNER JOIN `drupal_content_type_job_session` ctjs ON ctjs.field_session_job_nid_value = ctj.nid
    LEFT JOIN `drupal_content_field_cancellation_status` cs ON cs.nid = ctjs.nid
    INNER JOIN `drupal_node` jsn ON jsn.nid = ctjs.nid
    WHERE jsn.status = 1 AND ctj.vid ='%d'
    ORDER BY ctjs.field_job_session_date_time_value";

    //$query = "SELECT ctjs.* FROM {content_type_job} ctj, {content_type_job_session} ctjs WHERE ctjs.field_session_job_nid_value = ctj.nid and ctj.vid='%d'";
    $query_result = db_query($query, $job->vid);
    while($row = db_fetch_object($query_result)) {
        $supplement = _get_call_supplement_invoice($row);
        $call['data'] = $row;
        $call['supplements'] = $supplement;
        $callings[] = $call;
    }

    return $callings;
}

function _get_call_supplement($job_session) {
    $supplement = array();
    $query = "SELECT cs.*, s.title AS supplement_title
    FROM {content_field_call_supplements} cs
    INNER JOIN {node} s ON cs.field_call_supplements_nid = s.nid
    WHERE cs.nid='%s'";
    $result = db_query($query, $job_session);
    while($row = db_fetch_object($result)) {
        $supplement[] = $row;
    }

    return $supplement;
}

function _get_call_supplement_invoice($job_session) {
    $supplement = array();
    $query = "SELECT * FROM {crew_js_supplement} WHERE jsid='%s'";
    $result = db_query($query, $job_session->vid);
    while($row = db_fetch_object($result)) {
      $node = node_load($row->supplement_id);
      $supplement[$row->supplement_id]['title'] = $node->title;
      $supplement[$row->supplement_id]['quantity'] += 1;
      $supplement[$row->supplement_id]['amount'] += _get_supplement_amount($row, $job_session->field_job_session_hours_value);
    }

    return $supplement;
}

function _get_supplement_amount($row, $hours_quoted) {
    $query = "SELECT * FROM {crew_call} WHERE uid=" . $row->uid . " AND jsid=" . $row->jsid;
    $result = db_query($query);
    $row1 = db_fetch_object($result);
    $extra_hours = $row1->additional_hours;

    if ($row->client_ph != NULL) {
        return $row->client_ph * ($extra_hours + $hours_quoted);
    } else if ($row->client_of != NULL)  {
        return $row->client_of;
    }
}

function theme_acecrew_quote_body($job, $client, $client_contact, $venue, $callings) {
    $node = array(
            'job' => $job,
            'client' => $client,
            'client_contact' => $client_contact,
            'venue' => $venue,
            'callings' => $callings);

    $content = '<div class="quote-wrapper">';

    require_once dirname(__FILE__) .'/templates/acecrewquo.inc';
    drupal_add_css(drupal_get_path('module', 'acecrew') .'/templates/acecrewquo.css', 'module');

    $content_function = '_acecrew_quote_get_template_output';
    $content .= $content_function($node, 'pdf');

    $content .= '</div>';

    return $content;
}

function theme_acecrew_invoice_body($job, $client, $client_contact, $venue, $callings) {
    $node = array(
            'job' => $job,
            'client' => $client,
            'client_contact' => $client_contact,
            'venue' => $venue,
            'callings' => $callings);

    $content = '<div class="quote-wrapper">';

    require_once dirname(__FILE__) .'/templates/acecrewinv.inc';
    drupal_add_css(drupal_get_path('module', 'acecrew') .'/templates/acecrewinv.css', 'module');

    $content_function = '_acecrew_invoice_get_template_output';
    $content .= $content_function($node, 'pdf');

    $content .= '</div>';

    return $content;
}

function theme_acecrew_cost_body($job, $client, $client_contact, $venue, $callings) {
    $node = array(
            'job' => $job,
            'client' => $client,
            'client_contact' => $client_contact,
            'venue' => $venue,
            'callings' => $callings);

    $content = '<div class="quote-wrapper">';

    require_once dirname(__FILE__) .'/templates/acecrewcosts.inc';
    //drupal_add_css(drupal_get_path('module', 'acecrew') .'/templates/acecrewcosts.css', 'module');

    $content_function = '_acecrew_cost_get_template_output';
    $content .= $content_function($node, 'pdf');

    $content .= '</div>';

    return $content;
}

function theme_acecrew_proinv_body($job, $client, $client_contact, $venue, $callings) {
    $node = array(
            'job' => $job,
            'client' => $client,
            'client_contact' => $client_contact,
            'venue' => $venue,
            'callings' => $callings);

    $content = '<div class="quote-wrapper">';

    require_once dirname(__FILE__) .'/templates/acecrewproinv.inc';
    //drupal_add_css(drupal_get_path('module', 'acecrew') .'/templates/acecrewcosts.css', 'module');

    $content_function = '_acecrew_proinv_get_template_output';
    $content .= $content_function($node, 'pdf');

    $content .= '</div>';

    return $content;
}

function get_additional_hours($call) {
    $query = "SELECT * FROM {crew_call} WHERE jsid=" . $call->vid;
    $result = db_query($query);
    while ($row = db_fetch_object($result)) {
        $extra_hours += $row->additional_hours;
    }

    return $extra_hours;
}

function get_additional_costs($call) {
    $query = "SELECT * FROM {crew_call} WHERE jsid=" . $call->vid;
    $result = db_query($query);
    while ($row = db_fetch_object($result)) {
        $additional_charge += $row->additional_charge;
    }

    return $additional_charge;
}
function _get_call_client_charge_amount($job, $client, $call) {
  $rate = $call->field_job_session_client_rate_value == NULL ? 1 : $call->field_job_session_client_rate_value;
  $hours_quoted = $call->field_job_session_hours_value;
  //watchdog('jjj1', '<pre>'.print_r($job, TRUE).'</pre>');

  if (!empty($job->field_client_2h_default_value)) {
    $_2hrs_call_override = $job->field_client_2h_default_value;
  } else {
    $_2hrs_call_override = $client->field_2_hour_default_value == NULL ? _get_2_hours_call_client_default($client, $hours_quoted) : $client->field_2_hour_default_value;
  }

  if (!empty($job->field_client_3h_default_value)) {
    $_3hrs_call_override = $job->field_client_3h_default_value;
  } else {
    $_3hrs_call_override = $client->field_3_hour_default_value == NULL ? _get_3_hours_call_client_default($client, $hours_quoted) : $client->field_3_hour_default_value;
  }  
  /*
  $_2hrs_call_override = $client->field_2_hour_default_value == NULL ? _get_2_hours_call_client_default($client, $hours_quoted) : $client->field_2_hour_default_value;
  $_3hrs_call_override = $client->field_3_hour_default_value == NULL ? _get_3_hours_call_client_default($client, $hours_quoted) : $client->field_3_hour_default_value;
*/

  if ($hours_quoted <= 2) {
    return $_2hrs_call_override;
  } else if ($hours_quoted <= 3) {
    return $_3hrs_call_override;
  } else {
    return $rate * $hours_quoted;
  }
}
function __get_call_client_charge_amount($job, $client, $call) {
  $rate = $call->field_job_session_client_rate[0]['value'] == NULL ? 1 : $call->field_job_session_client_rate[0]['value'];
  $hours_quoted = $call->field_job_session_hours[0]['value'];
  //watchdog('jjj2', '<pre>'.print_r($job, TRUE).'</pre>');
  
  if (!empty($job->field_client_2h_default[0]['value'])) {
    $_2hrs_call_override = $job->field_client_2h_default[0]['value'];
  } else {
    $_2hrs_call_override = $client->field_2_hour_default_value == NULL ? _get_2_hours_call_client_default($client, $hours_quoted) : $client->field_2_hour_default_value;
  }

  if (!empty($job->field_client_3h_default[0]['value'])) {
    $_3hrs_call_override = $job->field_client_3h_default[0]['value'];
  } else {
    $_3hrs_call_override = $client->field_3_hour_default_value == NULL ? _get_3_hours_call_client_default($client, $hours_quoted) : $client->field_3_hour_default_value;
  }  

  /*
  $_2hrs_call_override = $client->field_2_hour_default[0]['value'] == NULL ? _get_2_hours_call_client_default($client, $hours_quoted) : $client->field_2_hour_default[0]['value'];
  $_3hrs_call_override = $client->field_3_hour_default[0]['value'] == NULL ? _get_3_hours_call_client_default($client, $hours_quoted) : $client->field_3_hour_default[0]['value'];
    */
  if ($hours_quoted <= 2) {
    return $_2hrs_call_override;
  } else if ($hours_quoted <= 3) {
    return $_3hrs_call_override;
  } else {
    return $rate * $hours_quoted;
  }
}

function _get_2_hours_call_client_default($client, $hours_quoted) {
  $admin_settings = _get_admin_settings();
  $rate = $client->field_client_rate_value;
  $overrided_value = $admin_settings['field_2hrs_client_defaults_value'];
  return $overrided_value == NULL ? $rate * $hours_quoted : $overrided_value;
}

function _get_3_hours_call_client_default($client, $hours_quoted) {
  $admin_settings = _get_admin_settings();
  $rate = $client->field_client_rate_value;
  $overrided_value = $admin_settings['field_3hrs_client_defaults_value'];
  return $overrided_value == NULL ? $rate * $hours_quoted : $overrided_value;
}

function __get_2_hours_call_client_default($client, $hours_quoted) {
  $admin_settings = _get_admin_settings();
  $rate = $client->field_client_rate[0]['value'];
  $overrided_value = $admin_settings['field_2hrs_client_defaults_value'];
  return $overrided_value == NULL ? $rate * $hours_quoted : $overrided_value;
}

function __get_3_hours_call_client_default($client, $hours_quoted) {
  $admin_settings = _get_admin_settings();
  $rate = $client->field_client_rate[0]['value'];
  $overrided_value = $admin_settings['field_3hrs_client_defaults_value'];
  return $overrided_value == NULL ? $rate * $hours_quoted : $overrided_value;
}

function _get_admin_settings() {
  $query = "SELECT * FROM {content_type_admin_settings}";
  $result = db_query($query);
  $values = db_fetch_array($result);

  return $values;
}

function _get_2hrs_call_crew_payment_amount($job, $crew, $call) {
  $saved_2hrs_default = db_result(db_query('SELECT pay_default_2h FROM `drupal_crew_call` WHERE uid = %d AND jsid = %d', $crew->uid, $call->vid));  
  if ($saved_2hrs_default != 0) {
    return $saved_2hrs_default;
  }

  //watchdog('ss_2h_c', '<pre>'.print_r($crew, TRUE).'</pre>');

  if ($call->field_job_session_hours[0]['value'] > 2) return NULL;
  $rate = $crew->profile_payrateid == NULL ? 1 : $crew->profile_payrateid;  
  $_2hrs_call_override = $crew->profile_2_hour_default == NULL ? _get_2_hours_call_crew_default($crew) : $crew->profile_2_hour_default;  

  return $_2hrs_call_override;
}

function _get_3hrs_call_crew_payment_amount($job, $crew, $call) {
  $saved_3hrs_default = db_result(db_query('SELECT pay_default_3h FROM `drupal_crew_call` WHERE uid = %d AND jsid = %d', $crew->uid, $call->vid));
  //watchdog('ss_3h_1', '<pre>'.print_r($saved_3hrs_default, TRUE).'</pre>');
  if ($saved_3hrs_default != 0) {
    return $saved_3hrs_default;
  }

  $_3h_defs = _get_3_hours_call_crew_default($crew);
  //watchdog('ss_3h_defs', '<pre>'.print_r($_3h_defs, TRUE).'</pre>');


  if ($call->field_job_session_hours[0]['value'] > 3 || $call->field_job_session_hours[0]['value'] <= 2) return NULL;
  $rate = $crew->profile_payrateid == NULL ? 1 : $crew->profile_payrateid;
  $_3hrs_call_override = $crew->profile_3_hour_default == NULL ? _get_3_hours_call_crew_default($crew) : $crew->profile_3_hour_default;
  //watchdog('ss_3h_2', '<pre>'.print_r($_3hrs_call_override, TRUE).'</pre>');
  return $_3hrs_call_override;
}


function _get_2_hours_call_crew_default($crew) {
  $admin_settings = _get_admin_settings();
  /*
  if (isset($crew->profile_payrateid)) {
    $rate = $crew->profile_payrateid;
    watchdog('rr1', '<pre>'.print_r($rate, TRUE).'</pre>');
  } else {    
    $rate = db_result(db_query('SELECT value FROM {profile_values} WHERE uid = %d AND fid = 28 LIMIT 1', $crew->uid));
  } 
  */ 
  $rate = db_result(db_query('SELECT value FROM {profile_values} WHERE uid = %d AND fid = 28 LIMIT 1', $crew->uid));  
  
  $overrided_value = $crew->profile_2_hour_default == NULL ? $admin_settings['field_' . preg_replace('/\./', '_', $rate) . '_per_hour_value'] : $crew->profile_2_hour_default;
  return $overrided_value == NULL ? $crew->profile_payrateid * 2 : $overrided_value;
}

function _get_3_hours_call_crew_default($crew) {
  $admin_settings = _get_admin_settings();
  /*
  if (isset($crew->profile_payrateid)) {
    $rate = $crew->profile_payrateid;
  } else {
    $rate = db_result(db_query('SELECT value FROM {profile_values} WHERE uid = %d AND fid = 28 LIMIT 1', $crew->uid));
  }
  */
  $rate = db_result(db_query('SELECT value FROM {profile_values} WHERE uid = %d AND fid = 28 LIMIT 1', $crew->uid));
  $overrided_value = $crew->profile_3_hour_default == NULL ? $admin_settings['field_' . preg_replace('/\./', '_', $rate) . '_per_hour_3_value'] : $crew->profile_3_hour_default;
  return $overrided_value == NULL ? $crew->profile_payrateid * 3 : $overrided_value;
}

function get_default_boundary_charge() {
  $query = "SELECT * FROM {content_type_admin_settings}";
  $result = db_query($query);
  $values = db_fetch_object($result);

  return $values->field_boundary_charge_default_value;
}

function get_default_mileage_charge_value() {
  $query = "SELECT * FROM {content_type_admin_settings}";
  $result = db_query($query);
  $values = db_fetch_object($result);

  return $values->field_admins_milerate_value;
}

function _get_call_data($call) {
  $call_data = array();
  $query = "SELECT * FROM {crew_call} WHERE jsid=" . $call->vid . " AND standard_crew=1";
  $result = db_query($query);
  while ($row = db_fetch_object($result)) {
    $call_data[] = $row;
  }

  return $call_data;
}

function _get_crew_payrate($call_vid, $crew_uid) {
  $query = "SELECT payrate FROM {crew_call} WHERE uid=$crew_uid AND jsid=$call_vid";
  $result = db_query($query);
  $row = db_fetch_object($result);
  $payrate = $row->payrate;

  return $payrate;
}

function acecrew_get_venue_milage_by_venue_id($id) {
    $query = "SELECT field_boundary_round_trip_value FROM {content_type_venue} WHERE field_venue_id_value = '%d'";
    $result = db_query($query, $id);
    $row = db_fetch_object($result);
    return $row->field_boundary_round_trip_value;
}

function acecrew_get_job_row_by_id($id) {
    $query = "SELECT * FROM {content_type_job} WHERE nid = '%d'";
    $result = db_query($query, $id);
    $row = db_fetch_object($result);
    return $row;
}

function _acecrew_quote_rtf_get_html($quote_id) {
    $job = NULL;
    $query = "SELECT ctj.*, ajq.*, cs.field_cancellation_status_value AS cancellation_status 
    FROM {content_type_job} ctj LEFT JOIN `drupal_content_field_cancellation_status` cs ON cs.nid = ctj.nid, {acecrew_job_quotes} ajq WHERE ajq.job_id=ctj.field_job_number_value AND ajq.acecrew_job_quote_id='%s'";
    $job = db_fetch_object(db_query($query, $quote_id));

    $client = _get_client_by_job($job);
    $client_contact = _get_client_contact_by_id($job);
    $venue = _get_venue_by_job($job);
    $callings = _get_callings_by_job($job);

    $node = array(
        'job' => $job,
        'client' => $client,
        'client_contact' => $client_contact,
        'venue' => $venue,
        'callings' => $callings
    );

    require_once dirname(__FILE__) .'/templates/acecrewquo_rtf.inc';

    $content = _acecrew_quote_get_template_output($node, 'pdf');

    return $content;
}

function _acecrew_invoice_rtf_get_html($invoice_id) {    
    $job = NULL;
    $query = "SELECT ctj.*, aji.*, cs.field_cancellation_status_value AS cancellation_status
        FROM `drupal_content_type_job` ctj LEFT JOIN `drupal_content_field_cancellation_status` cs ON cs.nid = ctj.nid 
, `drupal_acecrew_job_invoices` aji         
        WHERE aji.job_id=ctj.field_job_number_value AND aji.acecrew_job_invoice_id='%s'";
    $job = db_fetch_object(db_query($query, $invoice_id));   

    $client = _get_client_by_job($job);
    $client_contact = _get_client_contact_by_id($job);
    $venue = _get_venue_by_job($job);
    $callings = _get_callings_for_invoice_by_job($job);

    $node = array(
        'job' => $job,
        'client' => $client,
        'client_contact' => $client_contact,
        'venue' => $venue,
        'callings' => $callings
    );

    require_once dirname(__FILE__) .'/templates/acecrewinv_rtf.inc';

    $content = _acecrew_invoice_get_template_output($node);

    return $content;
}

function _acecrew_proinv_rtf_get_html($proinv_id) {    
    $job = NULL;
    $query = "SELECT ctj.*, ajpi.*, cs.field_cancellation_status_value AS cancellation_status
        FROM `drupal_content_type_job` ctj LEFT JOIN `drupal_content_field_cancellation_status` cs ON cs.nid = ctj.nid 
, `drupal_acecrew_job_pro_inv` ajpi         
        WHERE ajpi.job_id = ctj.field_job_number_value AND ajpi.acecrew_job_pro_inv_id = '%s'";
    $job = db_fetch_object(db_query($query, $proinv_id));  
    //watchdog('jjj', '<pre>'.print_r($job, TRUE).'</pre>'); 

    $client = _get_client_by_job($job);
    $client_contact = _get_client_contact_by_id($job);
    $venue = _get_venue_by_job($job);
    $callings = _get_callings_for_invoice_by_job($job);

    $node = array(
        'job' => $job,
        'client' => $client,
        'client_contact' => $client_contact,
        'venue' => $venue,
        'callings' => $callings
    );

    require_once dirname(__FILE__) .'/templates/acecrewproinv_rtf.inc';

    $content = _acecrew_proinv_get_template_output($node);

    return $content;
}

function _acecrew_cost_rtf_get_html($cost_id) {    
    $job = NULL;
    $query = "SELECT ctj.*, ajc.*, cs.field_cancellation_status_value AS cancellation_status
        FROM `drupal_content_type_job` ctj LEFT JOIN `drupal_content_field_cancellation_status` cs ON cs.nid = ctj.nid 
, `drupal_acecrew_job_costs` ajc         
        WHERE ajc.job_id = ctj.field_job_number_value AND ajc.acecrew_job_cost_id = '%s'";
    $job = db_fetch_object(db_query($query, $cost_id));   

    $client = _get_client_by_job($job);
    $client_contact = _get_client_contact_by_id($job);
    $venue = _get_venue_by_job($job);
    $callings = _get_callings_for_invoice_by_job($job);

    $node = array(
        'job' => $job,
        'client' => $client,
        'client_contact' => $client_contact,
        'venue' => $venue,
        'callings' => $callings
    );

    require_once dirname(__FILE__) .'/templates/acecrewcosts_rtf.inc';

    $content = _acecrew_cost_get_template_output($node);

    return $content;
}

function acecrew_get_crew_with_supplements($ses_call_id) {
    $crew_with_supp = "";
    $query = "SELECT jsid FROM {crew_call} WHERE cid = '%s'";
    $result =  db_query($query, $ses_call_id);
    $jsid = db_fetch_object($result)->jsid;

    $query1 =  "SELECT u.name, u.uid FROM {users} u WHERE u.uid IN (SELECT uid FROM {crew_call} WHERE cid='%s');";
    $query_result1 =  db_query($query1, $ses_call_id);
    while ($row1 = db_fetch_object($query_result1)) {

        $result = db_query("SELECT supplement_id FROM {crew_js_supplement} WHERE uid = '%s' AND jsid = '%d'", $row1->uid, $jsid);
        while($row = db_fetch_object($result)) {

            $res = db_query("SELECT field_supplement_short_value FROM {content_type_supplements} WHERE nid = '%s'", $row->supplement_id);
            while($r = db_fetch_object($res)) {
                $supplements[] = $r->field_supplement_short_value;
            }
        }

        $crew_mobile = db_result(db_query("SELECT value FROM {profile_values} WHERE uid='%s' AND fid = 12", $row1->uid));
        $preferred_name = db_result(db_query("SELECT value FROM {profile_values} WHERE uid='%s' AND fid = 47", $row1->uid));
        $crew_mobile = trim($crew_mobile) != "" ? $crew_mobile : 'undefined';
        $crew_name = trim($preferred_name) != "" ? $preferred_name : $row1->name;
        
        $supp = "";
        if($supplements) {
            $supp = implode(', ', $supplements);
            $supp .= ': ';
            $supplements = array();
        }
        $crew_with_supp .= $supp ? $supp . "$crew_name $crew_mobile<br/>" : '';
    }

    return $crew_with_supp;

}

function acecrew_get_statuses($tbc_status = FALSE, $tbi_status = FALSE) {
    $statuses = array(
        AWAITING_PO => 'Awaiting PO',
        QUOTE => 'Quote',
        CONFIRMED => 'Confirmed',
        CANCELLED => 'Cancelled',
        PENCIL => 'Pencil',
        INVOICED => 'Invoiced',
        INVOICE_SENT => 'Invoice Sent'
    );
    if ($tbc_status) {
        $statuses['tbc'] = 'To be confirmed';
    }
    if ($tbi_status) {
        $statuses['tbi'] = 'To be invoiced';
    }

    return $statuses;
}

function acecrew_get_status_name($status_id) {
    $statuses = acecrew_get_statuses();
    return $statuses[$status_id];
}
