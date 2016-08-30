<?php

jquery_ui_add('ui.core');
jquery_ui_add('ui.datepicker');
drupal_add_js(drupal_get_path('module', 'acecrew') . '/theme/acecrew_profile_supplement.js');  

$params = explode('/', $_GET['q']);
$uid = $params[1];
$username = db_result(db_query("SELECT name FROM {users} WHERE uid = '%s'", $uid));

$skills = '';
$payrate = 1;

if (isset($_POST['edit_submit_save'])) {  
  foreach ($_POST as $key=>$value) {
    $element = preg_replace('/profile_crew_skill_/', '', $key);
    if (is_numeric($element)) {
      $skills .= $element . ',';
    } else if ($element == 'acecrew_payrate_id') {
      $payrate = $value;
    }
  }
  if (strlen($skills) != 0) {
    $skills = substr($skills, 0, strlen($skills)-1);
  }
  $skills_after = explode(',', $skills);  
  $payrate_after = $payrate;
  // get skills
  $skills_before = db_result(db_query("SELECT value FROM {profile_values} WHERE fid = 41 AND uid = %d", $uid));
  $skills_before = explode(',', $skills_before);
  // set supplement
  $query = "SELECT * FROM {profile_values} WHERE fid=41 AND uid=$uid";
  $results = db_query($query);
  $isnew = TRUE;
  while ($row = db_fetch_object($results)) {
    $isnew = FALSE;
  }
  if ($isnew) {
    $query = "INSERT INTO  {profile_values} (`fid` ,`uid` ,`value`) VALUES ('41', '$uid', '$skills');";
    db_query($query);
  } else {
    $query = "UPDATE  {profile_values} SET `value` = '$skills'  WHERE fid=41 AND uid=$uid;";
    db_query($query);
  }
  // get payrate
  $payrate_before = db_result(db_query("SELECT value FROM {profile_values} WHERE fid = 28 AND uid = %d", $uid));
  // set payrate
  $query = "SELECT * FROM {profile_values} WHERE fid=28 AND uid=$uid";
  $results = db_query($query);
  $isnew = TRUE;
  while ($row = db_fetch_object($results)) {
    $isnew = FALSE;
  }
  if ($isnew) {
    $query = "INSERT INTO  {profile_values} (`fid` ,`uid` ,`value`) VALUES ('28', '$uid', '$payrate');";
    db_query($query);
  } else {
    $query = "UPDATE  {profile_values} SET `value` = '$payrate'  WHERE fid = 28 AND uid=$uid;";
    db_query($query);
  }
  // set rate date
  $rate_date_before = '';
  $rate_date = serialize($_POST['profile_rate_date']);
  $query = "SELECT * FROM {profile_values} WHERE fid=48 AND uid=$uid";
  $results = db_query($query);
  $isnew = TRUE;
  while ($row = db_fetch_object($results)) {
    $isnew = FALSE;
    $rate_date_before = $row->value;
  } 
  if ($isnew) {    
    $query = "INSERT INTO  {profile_values} (`fid` ,`uid` ,`value`) VALUES ('48', '$uid', '%s');";
    db_query($query, $rate_date);
  } else {    
    $query = "UPDATE  {profile_values} SET `value` = '%s'  WHERE fid = 48 AND uid=$uid;";
    db_query($query, $rate_date);
  }
  module_invoke_all('crew_supplement_skills', $skills_before, $skills, $uid);
  module_invoke_all('crew_supplement_payrate', $payrate_before, $payrate, $uid);
}

$skills = db_result(db_query("SELECT value FROM {profile_values} WHERE fid = 41 AND uid = %d", $uid));
$skills = explode(',', $skills);
// remove empty element if no selected skills was found for crew
if (sizeof($skills) == 1 && isset($skills[0]) && empty($skills[0])) {
  $skills = array();
}

$payrate = db_result(db_query("SELECT value FROM {profile_values} WHERE fid = 28 AND uid = %d", $uid));

$rate_date = db_result(db_query("SELECT value FROM {profile_values} WHERE fid = 48 AND uid = %d", $uid));

watchdog('rd1', '<pre>'.print_r($rate_date, TRUE).'</pre>');
$rate_date_before_unser = unserialize($rate_date_before);

$rate_date_table = '';
if (module_exists('acetracker_profile')) {
  if (isset($_POST['edit_submit_save'])) {
    global $user;
    $created = time();
    
    if ($_POST['acecrew_payrate_id'] != $payrate_before ||
        ($_POST['profile_rate_date']['day'] != $rate_date_before_unser['day'] ||
         $_POST['profile_rate_date']['month'] != $rate_date_before_unser['month'] ||
         $_POST['profile_rate_date']['year'] != $rate_date_before_unser['year'])) {
      // profile_payrateid
      db_query("INSERT INTO {acetracker_profile} (crew_uid, author, type, field_name, value, created) 
        VALUES (%d, %d, '%s', '%s', %f, %d)", 
        $uid,
        $user->uid, 
        'rate_change', 
        'profile_payrateid', 
        $payrate,    
        $created
      );
      // profile_rate_date
      db_query("INSERT INTO {acetracker_profile} (crew_uid, author, type, field_name, value, created) 
        VALUES (%d, %d, '%s', '%s', '%s', %d)", 
        $uid,
        $user->uid, 
        'rate_change', 
        'profile_rate_date', 
        $rate_date,    
        $created
      );
    } 
  }
  $rows = acetracker_profile_get_rates_dates($uid);
  $rate_date_table = theme('table', array(t('Date'), t('Rate')), $rows);
}
if (!empty($rate_date)) {
  $rate_date = unserialize($rate_date);
} else {
  $rate_date['day'] = date('j');
  $rate_date['month'] = date('n');
  $rate_date['year'] = date('Y');
}

$monthes = array(
  1 => 'Jan',
  2 => 'Feb',
  3 => 'Mar',
  4 => 'Apr',
  5 => 'May',
  6 => 'Jun',
  7 => 'Jul',
  8 => 'Aug',
  9 => 'Sep',
  10 => 'Oct',
  11 => 'Nov',
  12 => 'Dec',
);

$query = "SELECT node.nid AS nid, node.title AS node_title FROM {node} node  WHERE node.type in ('supplements')";
$results = db_query($query);
$supplements = array();
while ($row = db_fetch_object($results)) {
  $supplements[] = $row;
}
$options = acecrew_get_ads('field_admins_crewrates');

function is_skill_checked($nid, $skills) {
  foreach ($skills as $skill) {
      if ($nid == $skill) return "checked='checked'";
  }
  return 0;
}

// save dates of skills
if (isset($_POST['edit_submit_save'])) {
  $fieldpart_date_start = 'acecrew_date_start_';
  $fieldpart_date_end = 'acecrew_date_end_';
  // clean all prev bindings for current crew and create new ones
  db_query('DELETE FROM {acecrew_user_supplement} WHERE uid = %d', $uid);
  foreach ($skills as $skill_nid) {
    $start_date = 0;
    $end_date = 0;
    $field_start_date = $fieldpart_date_start . $skill_nid;
    $field_end_date = $fieldpart_date_end . $skill_nid;
    if (isset($_POST[$field_start_date]) && !empty($_POST[$field_start_date]) && acecrew_is_valid_date_format($_POST[$field_start_date])) {
      $start_date = strtotime($_POST[$field_start_date] . ' 00:00');
    }

    if (isset($_POST[$field_end_date]) && !empty($_POST[$field_end_date]) && acecrew_is_valid_date_format($_POST[$field_end_date])) {
      $end_date = strtotime($_POST[$field_end_date] . ' 23:59');
    }

    // both dates have to be filled up
    if ($start_date || $end_date) {
      db_query("INSERT INTO {acecrew_user_supplement} (uid, sid, start_date, end_date)
          VALUES (%d, %d, %d, %d)",
          $uid,
          $skill_nid,
          $start_date,
          $end_date
        );  
    }
  }
}

$rows = array();
foreach ($skills as $skill_nid) {
  $title = db_result(db_query('SELECT title FROM {node} WHERE nid = %d',$skill_nid));

  $result = db_fetch_object(db_query('SELECT start_date, end_date FROM {acecrew_user_supplement} WHERE uid = %d AND sid = %d', $uid, $skill_nid));

  $start_date = $result->start_date ? date('Y-m-d', $result->start_date) : '';
  $end_date = $result->end_date ? date('Y-m-d', $result->end_date) : '';

  $rows[] = array(
    $title,
    '<input type="text" class="acecrew_date_field" name="acecrew_date_start_'.$skill_nid. '" value="'.$start_date.'" />',
    '<input type="text" class="acecrew_date_field" name="acecrew_date_end_'.$skill_nid. '" value="'.$end_date.'" />',
  );
}
//
$skill_table = '';
if (sizeof($rows)) {
  $skill_table = theme('table', array(t('Skill'), t('Date Start'), t('Date End')), $rows);
}

?>
<div id="tabs">
      <div class="page-tabs limiter clear-block"><ul class="links primary-tabs"><li><a href="/users/<?php echo $user->name; ?>">View</a></li>
<li class="active"><a href="/user/<?php echo $uid; ?>/edit">Edit</a></li>
</ul></div>
      <div class="page-tabs limiter clear-block"><ul class="links secondary-tabs"><li><a href="/user/<?php echo $uid; ?>/edit">Account</a></li>
<li><a href="/user/<?php echo $uid; ?>/edit/Personal%20Information">Personal Information</a></li>
<li><a href="/user/<?php echo $uid; ?>/edit/Contact%20Information">Contact Information</a></li>
<li><a href="/user/<?php echo $uid; ?>/edit/crew_file_uploads">Crew Uploads And Payrates</a></li>
<li><a href="/user/<?php echo $uid; ?>/edit/Default%20Payments">Default Payments</a></li>
<li><a href="/user/<?php echo $uid; ?>/edit/Employment%20Type">Employment Type</a></li>
<li><a href="/user/<?php echo $uid; ?>/edit/Miscellaneous">Miscellaneous</a></li>
<li><a href="/user/<?php echo $uid; ?>/edit/Passport%20%2526%20Licence">Passport &amp; Licence</a></li>
<li class="active"><a href="/user/<?php echo $uid; ?>/edit/CrewSupplement" class="active">Supplement</a></li>
<li><a href="/user/<?php echo $uid; ?>/edit/Visa%20Details">Visa Details</a></li>
<li><a href="/user/<?php echo $uid; ?>/edit/Crew%20Sizes">Crew Sizes</a></li>
</ul></div>    </div>


<form action="/user/<?php echo $uid; ?>/edit/CrewSupplement" accept-charset="UTF-8" method="post" id="user-profile-form" enctype="multipart/form-data">
    <div>
    <div class="form form-layout-default clear-block rubik-processed">
    <div class="column-main">
    <div class="column-wrapper clear-block">
        <h1 class="supp-page" style="font-size: 20px; padding: 10px 0 10px 8px"><?php echo $username; ?><?php echo print_insert_link(); ?></h1>
    <fieldset class=" fieldset titled">
        <legend><span class="fieldset-title">Crew Skills</span></legend>
        <div class="fieldset-content clear-block ">
            <?php foreach ($supplements as $supp) { ?>
            <?php $title = $supp->node_title; $nid = $supp->nid;?>
            <div class="form-item form-option" id="edit-profile-crew-skill-<?php echo $nid; ?>">
                <label class="option" for="profile_crew_skill_<?php echo $nid; ?>">
                    <input type="checkbox" name="profile_crew_skill_<?php echo $nid; ?>" id="profile_crew_skill_<?php echo $nid; ?>" <?php echo is_skill_checked($nid, $skills); ?> class="form-checkbox"> <?php echo $title; ?>
                </label>
            </div>
            <?php } ?>
            
            <?php if (!empty($skill_table)) : ?>              
              <div style="clear: both;">
              <strong>Date format: 2014-06-15, 2015-11-26</strong>
              <?php print $skill_table; ?>
              </div>
              <hr/>
              <br/>
            <?php endif; ?>

            <div class="form-item form-item-labeled" id="edit-acecrew-payrate-id-wrapper">
                <label for="edit-acecrew-payrate-id">Pay Rate: <span class="form-required" title="This field is required.">*</span></label>
                <select name="acecrew_payrate_id" class="form-select required" id="edit-acecrew-payrate-id">
                <?php foreach ($options as $key=>$value) { ?>
                    <option value="<?php echo $key; ?>" <?php if ($key==$payrate) echo "selected='selected'"; ?>><?php echo $value; ?></option>
                <?php } ?>
                </select>
            </div>
            <div class="form-item form-item-labeled" id="edit-profile-rate-date-wrapper">
      <label for="edit-profile-rate-date">Rate Date: </label>
    <div class="container-inline">

<div class="form-item" id="edit-profile-rate-date-day-wrapper">
  <select name="profile_rate_date[day]" class="form-select" id="edit-profile-rate-date-day">
    <?php for ($i=1; $i<= 31; $i++) : ?>
      <option value="<?php echo $i; ?>" <?php if ($i==$rate_date['day']) print "selected='selected'"; ?>><?php echo $i; ?></option>
    <?php endfor; ?>
  </select>  
</div>

<div class="form-item" id="edit-profile-rate-date-month-wrapper">
  <select name="profile_rate_date[month]" class="form-select" id="edit-profile-rate-date-month">
    <?php foreach ($monthes as $i => $name) : ?>
      <option value="<?php print $i; ?>" <?php if ($i==$rate_date['month']) print "selected='selected'"; ?>><?php print $name; ?></option>
    <?php endforeach; ?>
  </select>  
</div>

<div class="form-item" id="edit-profile-rate-date-year-wrapper">
  <select name="profile_rate_date[year]" class="form-select" id="edit-profile-rate-date-year">
    <?php for ($i=2005; $i<= 2050; $i++) : ?>
      <option value="<?php echo $i; ?>" <?php if ($i==$rate_date['year']) print "selected='selected'"; ?>><?php echo $i; ?></option>
    <?php endfor; ?>
  </select>  
</div>


</div>  </div>

<?php print $rate_date_table; ?>
        </div>
    </fieldset>
    <div class="buttons">
    <input type="submit" name="edit_submit_save" id="edit_submit_save" value="Save" class="form-submit">
    </div>
    </div></div>
    </div>
    </div>
</form>