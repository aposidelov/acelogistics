<?php
//echo $label_title.'<br>'; 
 if(trim($label_title)=="Title:"){?>
<div style="clear:both"></div>
<br />
<h4>Personal Information:</h4>
<?php }elseif(trim($label_title)=="Telephone:"){?>
<div style="clear:both"></div>
<br />
<h4>Contact Information:</h4>
<?php }elseif(trim($label_title)=="Payrate ID:"){?>
<div style="clear:both"></div>
<br />
<h4>Crew Skills:</h4>
<?php }elseif(trim($label_title)=="Employed:"){?>
<div style="clear:both"></div>
<br />
<h4>Employment Type:</h4>
<?php }elseif(trim($label_title)=="Notes:"){?>
<div style="clear:both"></div>
<br />
<h4>Miscellaneous:</h4>
<?php }elseif(trim($label_title)=="Passport Number:"){?>
<div style="clear:both"></div>
<br />
<h4>Passport & Licence:</h4>
<?php }elseif(trim($label_title)=="Visa Type:"){?>
<div style="clear:both"></div>
<br />
<h4>Visa Details:</h4>
<?php }elseif(trim($label_title)=="Shirt Size:"){?>
<div style="clear:both"></div>
<br />
<h4>Crew Sizes:</h4>
<?php }?>

<?php if(trim($label_title)=="Status:"){?>
<div style="clear:both"></div>
<?php }?>

<div <?php if (!empty($attr)) print drupal_attributes($attr) ?>>
  <?php if (!empty($label_title)): ?>
    <label <?php if (!empty($label_attr)) print drupal_attributes($label_attr) ?>><?php print $label_title ?></label>
  <?php endif; ?>
  <?php if (!empty($value)) print $value ?>
  <?php if (!empty($description)): ?>
    <div class='description'><?php print $description ?></div>
  <?php endif; ?>
</div>


