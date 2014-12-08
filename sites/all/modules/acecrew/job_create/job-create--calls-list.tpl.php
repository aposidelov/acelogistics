
<?php foreach($acecrew_assigned_sessions as $ses_id => $session) : ?>
    <div class="acecrew_sessions_container">
        <div class="acecrew_session_content" id="acecrew_session_content_<?php print $ses_id; ?>"> <?php print $session['content']; ?> </div>
        <div class="acecrew_session_form" id="acecrew_session_form_<?php print $ses_id; ?>"> <?php print $session['form']; ?> </div>
        <div class="acecrew_session_buttons" id="acecrew_session_buttons_<?php print $ses_id; ?>">
            <a href="javascript:void(0)" onclick="acecrew_session_edit('<?php print $ses_id; ?>')" class="acecrew_session_edit_button" id="acecrew_session_edit_button_$ses_id">Edit</a>
            <a href="javascript:void(0)" onclick="acecrew_session_del('<?php print $ses_id; ?>')" class="acecrew_session_del_button" id="acecrew_session_del_button_$ses_id">Delete</a>
        </div>
    </div>
<?php endforeach; ?>
