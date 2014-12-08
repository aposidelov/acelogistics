<?php
// $Id: user-profile.tpl.php,v 1.2.2.2 2009/10/06 11:50:06 goba Exp $

/**
 * @file user-profile.tpl.php
 * Default theme implementation to present all user profile data.
 *
 * This template is used when viewing a registered member's profile page,
 * e.g., example.com/user/123. 123 being the users ID.
 *
 * By default, all user profile data is printed out with the $user_profile
 * variable. If there is a need to break it up you can use $profile instead.
 * It is keyed to the name of each category or other data attached to the
 * account. If it is a category it will contain all the profile items. By
 * default $profile['summary'] is provided which contains data on the user's
 * history. Other data can be included by modules. $profile['user_picture'] is
 * available by default showing the account picture.
 *
 * Also keep in mind that profile items and their categories can be defined by
 * site administrators. They are also available within $profile. For example,
 * if a site is configured with a category of "contact" with
 * fields for of addresses, phone numbers and other related info, then doing a
 * straight print of $profile['contact'] will output everything in the
 * category. This is useful for altering source order and adding custom
 * markup for the group.
 *
 * To check for all available data within $profile, use the code below.
 * @code
 *   print '<pre>'. check_plain(print_r($profile, 1)) .'</pre>';
 * @endcode
 *
 * Available variables:
 *   - $user_profile: All user profile data. Ready for print.
 *   - $profile: Keyed array of profile categories and their items or other data
 *     provided by modules.
 *
 * @see user-profile-category.tpl.php
 *   Where the html is handled for the group.
 * @see user-profile-item.tpl.php
 *   Where the html is handled for each item in the group.
 * @see template_preprocess_user_profile()
 */
 
 /*
 available values
  0:  $template_files
  1:  $account
  2:  $zebra
  3:  $id
  4:  $directory
  5:  $is_admin
  6:  $is_front
  7:  $logged_in
  8:  $db_is_active
  9:  $user
  10: $profile
  11: $user_profile
  12: $content_profile

 
 */
 
?>
<div class="profile">
  <?php //print $user_profile; ?>
  <?php 
  //var_dump($account); 
  //var_dump($user); 
  ?>
</div>

<?php
 // return;
$user_view=$_GET;
$user_view=explode('/',$user_view['q']);
drupal_add_js(drupal_get_path('module', 'acecrew') . '/theme/datetimepicker.js');
drupal_add_js(drupal_get_path('module', 'acecrew') . '/theme/jquery.blockui.js');

if($user_view[3] == t('current-activity'))
{
    $uid =    $user_view[1];
    $vars['curr_activities'] = array();
    $sql = db_query("SELECT * FROM {crew_call} WHERE uid = %d ", $uid);
    $count = 0;
    while($row = db_fetch_object($sql))
    {
        // here, get the call id.
        $vars['curr_activities'][$count]['call_id'] = $row->cid;
        // next get other info
        $row_js = db_fetch_object(db_query("SELECT * FROM {content_type_job_session} WHERE field_session_callid_value = '%s' AND vid = %d", $row->cid, $row->jsid));
        
        // how can get datetime type variable?
        $vars['curr_activities'][$count]['date_time'] = $row_js->field_job_session_date_time_value;
        
        $row_job = db_fetch_object(db_query("SELECT * FROM {content_type_job} WHERE nid = %d", $row_js->field_session_job_nid_value));
        
        // link require only job id.
        // first, need to know about create number
        // url_alias contains the needed info. nod/750 -> content/job-create-21
        $alias_link = db_result(db_query("SELECT dst FROM {url_alias} WHERE src='%s'", "node/".$row_job->nid));
        $vars['curr_activities'][$count]['link'] = $alias_link;
        
        // get the names
        $row_ctv = db_fetch_object(db_query("SELECT field_venue_name_value FROM {content_type_venue} WHERE field_venue_id_value = %d", $row_job->field_job_venue_value));
        
        $vars['curr_activities'][$count]['venue'] = $row_ctv->field_venue_name_value;

        $row_ctc = db_fetch_object(db_query("SELECT field_client_name_value FROM {content_type_client} WHERE field_client_id_value = %d", $row_job->field_job_client_name_value));

        $vars['curr_activities'][$count]['client'] = $row_ctc->field_client_name_value;

        $count++;
    }
}
    
//echo '<pre>'.print_r($user_view,1);

//echo '<pre>'. print_r($account,1);
//echo '<pre>';print_r(unserialize($account->data));

$skills = $account->profile_crew_skills;
$skills = explode(",", $skills);
?>

<script type="text/javascript">
$(document).ready(function(){
    $('.profile_item').hide();
    $('.profile_item').filter(':first').show();

    $('.profile_title').click(function(){
        $('.profile_item').hide('slow');
        var id=$(this).attr('title');
        $('.'+id).show('slow');
    });
});

</script>

<div id='tabs'>
<div class="scroller-anchor"></div>
<div class="page-tabs limiter clear-block acecrew-profile-tabs">
<ul class="links secondary-tabs">
<li <?php if(!isset($user_view[3]))echo 'class="active"';?>><a href="/user/<?=$account->uid?>/view">Account</a></li>
<li <?php if(isset($user_view[3]) && $user_view[3]=='profile-information')echo 'class="active"';?>><a href="/user/<?=$account->uid?>/view/profile-information">Profile Information</a></li>
<li <?php if(isset($user_view[3]) && $user_view[3]=='current-activity')echo 'class="active"';?>><a href="/user/<?=$account->uid?>/view/current-activity">Current Activity</a></li>
<li <?php if(isset($user_view[3]) && $user_view[3]=='booked-off')echo 'class="active"';?>><a href="/user/<?=$account->uid?>/view/booked-off">Booked Off</a></li>
</ul>
</div>
</div>
<br />

<div class="profile">
 <?php if(!isset($user_view[3])){?>
  <h2 class="profile_title" title="account_information">Account Information:</h2>
  <div class="account_information profile_item">
  <div>Username: <?=$account->name?></div>
  <div>Email: <?=$account->mail?></div>
  <div>Status: <?=$account->status?'Active':'Blocked'?></div>
  <div>Roles: <?php $i=0; foreach($account->roles as $item){ echo $item; if($i<count($account->roles)-1) echo ', ';$i++;}?></div>
  </div>
  <?php }?>    
      
  <?php if(isset($user_view[3]) && $user_view[3]=='profile-information'){?>
  <h2 class="profile_title" title="personal_information">Personal Information:</h2>
  <div class="personal_information profile_item">
  <div>Full Name: <?php echo ($account->profile_title?$account->profile_title.' ':'').$account->profile_crew_fullname?></div>
  <div>Nationality: <?=$account->profile_nationality?></div>
  <div>Date Of Birth: <?=$account->profile_crew_dob['day'].'-'.$account->profile_crew_dob['month'].'-'.$account->profile_crew_dob['year'];?></div>
  <div>Address: <?=$account->profile_crew_address;?></div>
  <div>Post Code: <?=$account->profile_crew_postcode;?></div>
  <div>Mother's Maiden Name: <?=$account->profile_crew_mothers_name;?></div>
  <div>NI Number: <?=$account->profile_crew_ni_number;?></div>
  <div>Emergency Details: <?=$account->profile_crew_nok;?></div>
  <div>Emergency Telephone: <?=$account->profile_crew_nok_telephone;?></div>
  </div>
  
  <br />    
  <h2 class="profile_title" title="contact_information">Contact Information:</h2>
  <div class="contact_information profile_item">  
  <div>Telephone: <?=$account->profile_crew_telephone;?></div>
  <div>Mobile Number: <?=$account->profile_crew_mobile;?></div>
  <div>Nearest Station/Tube: <?=$account->profile_crew_mobile;?></div>
  </div>

  <br />    
  <h2 class="profile_title" title="crew_skills">Crew Skills:</h2>
  <div class="crew_skills profile_item">
  <div>
      <?php
      $skills_count = count($skills);
      for($i = 0; $i < $skills_count; $i++) {
          $node = node_load($skills[$i]);
          echo $node->title;
          echo ($i == $skills_count - 1) ? "" : ", ";
      }
      ?>
  </div>
      <!--    <div>-->
      <!--        Pay Rate: --><?php //echo $account->profile_crew_mobile; ?>
      <!--    </div>-->
  </div>

  <br />    
  <h2 class="profile_title" title="employment_type">Employment Type:</h2>
  <div class="employment_type profile_item">
  <div><?=$account->profile_employment_type;?></div>
  </div>
  
  <br />    
  <h2 class="profile_title" title="miscellaneous">Miscellaneous:</h2>
  <div class="miscellaneous profile_item">
  <div>Notes: <?=$account->profile_notes;?></div>
  <div>Strength: <?=$account->profile_strength;?></div>
  </div>

  <br />    
  <h2 class="profile_title" title="passport" >Passport & Licence:</h2>
  <div class="passport profile_item">
  <div>Passport Number: <?=$account->profile_passport_number;?></div>
  <div>Licence Number: <?=$account->profile_licence;?></div>
  </div>

  <br />    
  <h2 class="profile_title" title="visa_details">Visa Details:</h2>
  <div class="visa_details profile_item">
  <div>Visa Type: <?=$account->profile_visa_type;?></div>
  <div>Visa Start Date: <?=$account->profile_visa_start['day'].'-'.$account->profile_visa_start['month'].'-'.$account->profile_visa_start['year'];?></div>
  <div>Visa End Date: <?=$account->profile_visa_end_date['day'].'-'.$account->profile_visa_end_date['month'].'-'.$account->profile_visa_end_date['year'];?></div>
  </div>


  <br />    
  <h2 class="profile_title" title="crew_sizes">Crew Sizes:</h2>
  <div class="crew_sizes profile_item">
  <div>Shirt Size: <?=$account->profile_crew_shirt;?></div>
  <div>Trouser Size: <?=$account->profile_crew_trouser;?></div>
  <div>Length Of Leg: <?=$account->profile_length_leg;?></div>
  <div>Height: <?=$account->profile_crew_height;?></div>
  </div>
  <?php }?>
      
      
  <?php 
  if(isset($user_view[3]) && $user_view[3]=='current-activity'){?>
  <h2 class="profile_title" title="current_activity">Current Activity:</h2>
  <div class="current_activity profile_item">
  <div><?=$account->profile_activity;?></div>
  <table>
  <tr class="table-columns">
  <td>Client</td>
  <td>Venue</td>
  <td>Date+Time</td>
  <td>Call ID</td>
  <td>Job Link</td>
  </tr>
  <?php 
  // how can arrange $vars with date desc?
  $arranged_array = array();
  foreach($vars[curr_activities] as $key => $row)
  {
        $dateTime[$key] = $row['date_time'];
        $arranged_array[$key] = $row;

  }
  array_multisort($dateTime, SORT_DESC, SORT_STRING, $arranged_array);

  // foreach($vars['curr_activities'] as $activity){
  foreach($arranged_array as $activity){
  ?>
  <tr>
  <td>
  <?php
    echo $activity['client'];
?>
  </td>
  <td>
  <?php
    echo $activity['venue'];
?>
  </td>
  <td>
  <?php
    echo $activity['date_time']
?>
  </td>
  <td>
  <?php
    echo $activity['call_id'];
?>
  </td>
  <td>
  <a href= "<?php echo $GLOBALS['base_url']."/".$activity['link'] ?>">Job View</a>
  </td>
  </tr>
  <?php
  }
  ?>
  </table>
  </div>
  <?php }?>
      
  <?php if(isset($user_view[3]) && $user_view[3]=='booked-off'):?>    
  <script type="text/javascript">
  $(document).ready(function(){
    $('#ub_date_start').datetimepicker({ 
      dateFormat: 'mm/dd/yy',
      timeFormat: ' hh:ii' 
    });
    $('#ub_date_end').datetimepicker({ 
      dateFormat: 'mm/dd/yy',
      timeFormat: ' hh:ii' 
    });
    
     $(document).ajaxStart(function(){
        //$(this).show();
        $('#msgboard').hide()
        $.blockUI();
     }).ajaxStop(function(){
        //$(this).hide();
        $.unblockUI();
     });
 
    
  });

  function formValidate(){
	  if ( $('#ub_label').val().length<1 ||
          $('#ub_date_start').val().length<1 ||
          $('#ub_date_end').val().length < 1 ) { 
		  return false;
	  }else{
		  return true;
	  }
  }
  function addBookedOff(){
	  if (! formValidate())
	  {				
		  $('#msgboard').html("invalid input value");
		  $('#msgboard').addClass("error");
		  $('#msgboard').removeClass('status');
		  $('#msgboard').show(1000)
		  return;
	  }
      postData = {
          uid:'<?php echo $account->uid?>', //$('[name=uid]').val()
          ub_label:$('#ub_label').val(),
          ub_date_start:$('#ub_date_start').val(),
          ub_date_end:$('#ub_date_end').val(),
      }
      
      $.post(Drupal.settings.basePath + "acecrew/ajax/usr/addbookedoff/uid:<?php echo $account->uid?>",
            postData,
            function(data){
                var result = Drupal.parseJson(data);
                
                if ( result.result == 1){
                    $('#msgboard').html(result.msg);
                    $('#msgboard').addClass("status");
                    //add new row to the end
                    $rowHtml = "<tr id='tr_ub_"+ result.node_id + "'><td>"
                        + postData['ub_label']+ '</td> <td>'
                        + postData['ub_date_start']+ '</td> <td>'
                        + postData['ub_date_end'] + '</td>  <td>'
                        + "<a href='#' onclick=\"delBookedOff('" +result.node_id +"')\">delete</a></td>"
                        + "</tr>"
                    $($rowHtml).insertAfter('#ub-list-0').fadeOut(500).fadeIn(500)
                    
                }else if ( result.result== 0){
                    $('#msgboard').html(result.msg);
                    $('#msgboard').addClass("error")
                }
                
                $('#msgboard').show(1000)
            }); 
  }
  
  function delBookedOff(nid){
        $.get(Drupal.settings.basePath + "acecrew/ajax/usr/delbookedoff/"+nid, function(data){
           
            var result = Drupal.parseJson(data);
            
            if ( result.result == 1){
                $('#msgboard').html(result.msg);
                $('#msgboard').addClass("status")
                
                //remove node
                 $('#tr_ub_'+nid).css('background-color', "red")
                $('#tr_ub_'+nid).fadeOut(1000);
                setTimeout("$('#tr_ub_"+nid+"').remove()", 1000);
            }else if ( result.result== 0){
                $('#msgboard').html(result.msg);
                $('#msgboard').addClass("error")
            }
            
            $('#msgboard').show(1000)
        });
  }
 
 
  </script>
  <!--
  <h2 class="profile_title" title="booked_off">Booked Off:</h2>
  <div class="booked_off profile_item">
  <div><?=$account->profile_booked;?></div>
  </div>
  -->
  
  <div id='msgboard' class="messages" style="display:none">Notification message</div>
  <!-- add form -->
  <div>
    <form action="" method="POST">
    <input type="hidden" name="uid" value="<?php echo $account->uid?>"/>
    <fieldset>
    <legend> Add New:</legend>
    <label>Label</label>
    <span><input type="text" name="ub_label" id="ub_label" class="ub-text"></span>
    <label>Start Date+Time</label>
    <span><input type="text" id="ub_date_start" name="ub_date_start" class="ub-calendar"></span>
    <label>End Date+Time</label>
    <span><input type="text" id="ub_date_end" name="ub_date_end" class="ub-calendar"></span>
    <span><input type="button" value="Add new line" class="form-submit" onclick="addBookedOff()"/></span>
    </fieldset>
    </form>
  </div>
  
  <?php
      module_load_include('inc', 'node', 'node.pages');
      $node_ub_type = 'user_bookedoff';
      $boForm = drupal_get_form($node_ub_type.'_node_form', array('type'=>$node_ub_type));
      //echo $boForm;
  ?>
  

  <hr style="display:block"/>
  <table id="ub-list">
  <tr id="ub-list-0" tclass="table-columns">
      <th>Label</th>
      <th>Date and time from</th>
      <th>Date and time to</th>
      <th></th>
  </tr>
  <?php foreach($account->bookoff_list as $row ){
   $nid = $row['nid'];
   
   echo <<<TABLE_ROW
    <tr id="tr_ub_$nid">
    <td>$row[field_ub_label_value] </td>
    <td>$row[field_ub_date_start_value]</td>
    <td>$row[field_ub_date_end_value]</td>
    <td><a href="#" onclick="delBookedOff('$nid')">delete</a></td>
  </tr>
TABLE_ROW;
  }?>
  
  </table>
  <?php endif;?>
  
</div>




