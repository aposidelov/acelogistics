
<?php foreach ($acecrew_assigned_sessions as $ses_id => $session) : ?>
	<?php $node = node_load($ses_id); ?>
	<?php $status_label = $node->field_cancellation_status[0]['value'] == CANCELLATION_NA ? t('Cancel') : t('Activate'); ?>
    <?php $classes = !$node->status ? ' cancel-btn' : ''; ?>
    <?php $classes .= $node->field_cancellation_status[0]['value'] != CANCELLATION_NA ? ' cancel-notice' : ''; ?>
    <div class="acecrew_sessions_container">
        <div class="acecrew_session_content<?php print $classes; ?>" id="acecrew_session_content_<?php print $ses_id; ?>"> <?php print $session['content']; ?> </div>
        <div class="acecrew_session_form" id="acecrew_session_form_<?php print $ses_id; ?>"> <?php print $session['form']; ?> </div>
        <div class="acecrew_session_buttons" id="acecrew_session_buttons_<?php print $ses_id; ?>">
            <a href="javascript:void(0)" onclick="acecrew_session_edit('<?php print $ses_id; ?>')" class="acecrew_session_edit_button" id="acecrew_session_edit_button_$ses_id">Edit</a>
            <a href="javascript:void(0)" onclick="acecrew_session_del('<?php print $ses_id; ?>')" class="acecrew_session_del_button" id="acecrew_session_del_button_$ses_id">Delete</a>            
            <a href="javascript:void(0)" onclick="acecrew_session_status_toogle('<?php print $ses_id; ?>')" class="acecrew_session_status_button" id="acecrew_session_status_button_$ses_id"><?php print $status_label; ?></a>
        </div>
    </div>
<?php endforeach; ?>
