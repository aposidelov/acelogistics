<?php

if (count($_POST) != 0) {
    $requests = $_POST;
} else {
    $requests = $_GET;
}
$action = $requests['action'];
foreach ($requests as $key => $value) {
    if ($key == 'q' || $key == "action")    continue;
    if ($value != "All" && $value != "0")  {
        $condition[preg_replace("/value_/", "", $key)] = $value;
        $params .= $key . '=' . $value . '&';
    }
}


/*var_dump($condition);*/

$supplements = array();
$query = "SELECT * FROM {node} d WHERE type='supplements'";
$results = db_query($query);
$index = 0;
while ($row = db_fetch_object($results)) {
    $supplements[$index]['nid'] = $row->nid;
    $supplements[$index]['title'] = $row->title;
    $supplements[$index++]['name'] = preg_replace('/ /', '_', strtolower($row->title));
}

/*var_dump($supplements);*/


$query = "SELECT * FROM {profile_fields} WHERE name='profile_employment_type'";
$results = db_query($query);
$index = 0;
while ($row = db_fetch_object($results)) {
    $options = $row->options;
}

$employment_types = explode("\r\n", $options);
/*var_dump($employment_type);*/

$query = "SELECT * FROM {users} users ORDER BY name ASC;";
$results = db_query($query);
$index = 0;
while ($row = db_fetch_object($results)) {
    $user = user_load($row->uid);
    if ($user->uid == 0)    continue;
    $crew['name'] = $user->name;
    $crew['e-mail'] = $user->mail;
    $crew['mobile'] = $user->profile_crew_mobile;
    $crew['address'] = $user->profile_crew_address;
    $crew['post_code'] = $user->profile_crew_postcode;
    $crew['crew_skills'] = $user->profile_crew_skills;
    $crew['post_link'] = $base_url . '/users/' . preg_replace("/ /", "-", strtolower($user->name));
    $crew['nearest_station'] = $user->profile_crew_nearest_station;
    $crew['created_date'] = date('Y-m-d', $user->created);
    $crew['edit_link'] = $base_url . "/user/" . $user->uid . "/edit";
    $crew['employment-type'] = $user->profile_employment_type;
    foreach ($supplements as $supp) {
        $crew[$supp['name']] = preg_match("/" . $supp['nid'] . "/", $user->profile_crew_skills) ? "Yes" : "No";
    }
    
    if (is_matched_search_condition($condition, $crew)) {
        $filtered_crews[] = $crew;
    }
}
if ($action == "csv") {
    define (REPORT_DIR, 'sites/default/files/');
    define (CSV, '.csv');

    $path = REPORT_DIR . 'crew' . CSV;
    $fp = fopen($path, 'w+');
    
    $fields = array("Name","E-mail","Mobile Number","Address","Post Code","Nearest Station");
    foreach ($supplements as $supp) {
        $fields[] = $supp['title'];
    }
    $fields[] = "Created date";
    $fields[] = "Employed";
    
    // get payment data
    fputcsv($fp, $fields, ';');

    foreach ($filtered_crews as $crew) {
        $content[] = $crew['name'];
        $content[] = $crew['e-mail'];
        $content[] = $crew['mobile'];
        $content[] = $crew['address'];
        $content[] = $crew['post_code'];
        $content[] = $crew['nearest_station'];
        foreach ($supplements as $supp) {
            $content[] = $crew[$supp['name']];
        }
        $content[] = $crew['created_date'];
        $content[] = $crew['employment-type'];
        fputcsv($fp, $content, ';');
        $content = array();
    }

    fclose($fp);
    $csv = file_get_contents($path);
    unlink($path);
    
    drupal_set_header('Content-Type: text/csv');
    drupal_set_header('Content-Disposition: attachment; filename=crew-view.csv');
    
    echo $csv;
    exit;
}
function is_matched_search_condition($condition, $crew) {
    if ($condition == NULL) return true;
    foreach ($condition as $key => $value) {
        if(is_numeric($key)) {
            if (preg_match('/' . $key . '/', $crew['crew_skills'])) {
                if ($condition['employment-type'] == $crew['employment-type'])  return true;
            }
        }
    }
    if ($condition['employment-type'] == $crew['employment-type'])  return true;
    return false;
}
?>

<div id="view-filters">
<form id="views-exposed-form-crew-view-block-1" method="post" accept-charset="UTF-8" class="views-processed">
    <div>
        <div class="views-exposed-form">
            <div class="views-exposed-widgets clear-block">
                
                <?php foreach ($supplements as $supp) { ?>
                <div class="views-exposed-widget">
                    <label for="edit-value-<?php echo $supp['nid']; ?>"><?php echo $supp['title']; ?></label>
                    <div class="views-widget">
                        <div id="edit-value-<?php echo $supp['nid']; ?>-wrapper" class="form-item">
                            <select id="edit-value-<?php echo $supp['nid']; ?>" class="form-select" name="value_<?php echo $supp['nid']; ?>">
                                <option value="All" <?php if ($requests['value_'.$supp['nid']] == "All") echo "selected='selected'" ?>>&lt;Any&gt;</option>
                                <option value="1" <?php if ($requests['value_'.$supp['nid']] == "1") echo "selected='selected'" ?>>True</option>
                                <option value="0" <?php if ($requests['value_'.$supp['nid']] == "0") echo "selected='selected'" ?>>False</option>
                            </select>
                        </div>
                    </div>
                </div>
                <?php } ?>
                
                <div class="views-exposed-widget">
                    <label for="edit-value-employment-type">Employment Type</label>
                    <div class="views-widget">
                        <div id="edit-value-employment-type-wrapper" class="form-item">
                            <select id="edit-value-employment-type" class="form-select" name="value_employment-type">
                                <option value="All">&lt;Any&gt;</option>
                                <?php foreach ($employment_types as $type) { ?>
                                <option value="<?php echo $type; ?>" <?php if ($requests['value_employment-type'] == $type) echo "selected='selected'" ?>><?php echo $type; ?></option>
                                <?php } ?>
                            </select>
                        </div>
                    </div>
                </div>
                
                <div class="views-exposed-widget">
                    <input type="submit" class="form-submit" value="Apply" id="edit-submit-crew-view">
                </div>
            </div>
        </div>
    </div>
</form>
</div>
<div class="view-content">
    <table class="views-table">
        <thead>
            <tr>
                <th class="views-field views-field-name">Name</th>
                <th class="views-field views-field-mail">E-mail</th>
                <th class="views-field views-field-value">Mobile Number</th>
                <th class="views-field views-field-value">Address</th>
                <th class="views-field views-field-value">Post Code</th>
                <th class="views-field views-field-value">Skills</th>
                <th class="views-field views-field-edit-node">Edit link</th>
                <th class="views-field views-field-value">Employed</th>
            </tr>
        </thead>
        <tbody>
        <?php foreach ($filtered_crews as $crew) { ?>
        <tr class="odd views-row-last">
            <td class="views-field views-field-name">
                <a title="View user profile." class="username" href="<?php echo base_path(); ?>users/<?php echo strtolower(preg_replace('/[^a-zA-Z0-9-]+/', '-', $crew['name'])); ?>"><?php echo $crew['name'] ?></a>
            </td>
            <td class="views-field views-field-mail">
                <a href="mailto:<?php echo $crew['e-mail'] ?>"><?php echo $crew['e-mail'] ?></a>
            </td>
            <td class="views-field views-field-value">
                <?php echo $crew['mobile'] ?>
            </td>
            <td class="views-field views-field-value-6">
                <?php echo $crew['address'] ?>
            </td>
            <td class="views-field views-field-value-7">
                <a href="<?php echo $crew['post_link'] ?>"><?php echo $crew['post_code'] ?></a>
            </td>
            <td class="views-field views-field-value-2">
            <?php foreach ($supplements as $supp) { ?>
                 <?php 
				 
				 if($crew[$supp['name']] === "Yes") {
				 echo "<div>" . $supp['title'] . "</div>";
				 }
				  ?>
            <?php } ?>
            </td>            
            <td class="views-field views-field-edit-node">
                <a href="<?php echo $crew['edit_link'] ?>">edit</a>
            </td>
            <td class="views-field views-field-value-8">
                <?php echo $crew['employment-type'] ?>
            </td>
        </tr>
        <? } ?>
        </tbody>
    </table>
</div>
<div class="feed-icon">
    <a href="/content/employee-listing?action=csv&<?php echo $params; ?>">
        <img width="36" height="14" title="CSV" alt="CSV" src="/sites/all/modules/views_bonus/export/images/csv.png">
    </a>
</div>
<?php


?>