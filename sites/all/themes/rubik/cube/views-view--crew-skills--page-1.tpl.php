<?php
$params = explode('/', $_GET['q']);
$uid = $params[1];

$skills = '';
$payrate = 1;
if (isset($_POST['edit_submit_save'])) {
  //watchdog('post', '<pre>'.print_r($_POST, TRUE).'</pre>');
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
  $rate_date = serialize($_POST['profile_rate_date']);
  $query = "SELECT * FROM {profile_values} WHERE fid=48 AND uid=$uid";
  $results = db_query($query);
  $isnew = TRUE;
  while ($row = db_fetch_object($results)) {
    $isnew = FALSE;
  } 
  if ($isnew) {
    watchdog('ins', '<pre>'.print_r($rate_date, TRUE).'</pre>');
    $query = "INSERT INTO  {profile_values} (`fid` ,`uid` ,`value`) VALUES ('48', '$uid', '%s');";
    db_query($query, $rate_date);
  } else {
    watchdog('upd', '<pre>'.print_r($rate_date, TRUE).'</pre>');
    $query = "UPDATE  {profile_values} SET `value` = '%s'  WHERE fid = 48 AND uid=$uid;";
    db_query($query, $rate_date);
  }
  module_invoke_all('crew_supplement_skills', $skills_before, $skills, $uid);
  module_invoke_all('crew_supplement_payrate', $payrate_before, $payrate, $uid);
}

$skills = db_result(db_query("SELECT value FROM {profile_values} WHERE fid = 41 AND uid = %d", $uid));
$skills = explode(',', $skills);

$payrate = db_result(db_query("SELECT value FROM {profile_values} WHERE fid = 28 AND uid = %d", $uid));

$rate_date = db_result(db_query("SELECT value FROM {profile_values} WHERE fid = 48 AND uid = %d", $uid));
watchdog('rd0', '<pre>'.print_r($rate_date, TRUE).'</pre>');
$rate_date = unserialize($rate_date);
watchdog('rd1', '<pre>'.print_r($rate_date, TRUE).'</pre>');



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
        <h1 class="supp-page" style="font-size: 20px; padding: 10px 0 10px 8px"><?php echo $user->name; ?><?php echo print_insert_link(); ?></h1>
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
        </div>
    </fieldset>
    <div class="buttons">
    <input type="submit" name="edit_submit_save" id="edit_submit_save" value="Save" class="form-submit">
    </div>
    </div></div>
    </div>
    </div>
</form>