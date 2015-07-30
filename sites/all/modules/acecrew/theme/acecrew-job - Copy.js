var acecrew_current_edit_item = null;

function acecrew_session_edit(ses_id)
{
    acecrew_current_edit_item = 'acecrew_session_form_' + ses_id;
    $('#acecrew_session_content_' + ses_id).hide('fast');
    $('#acecrew_session_buttons_' + ses_id).hide('fast');
    $('.acecrew_session_add_block').hide('fast');
    $('#acecrew_session_form_' + ses_id).show('fast');
}

function acecrew_session_del(ses_id)
{
    $.get(Drupal.settings.basePath + "acecrew/ajax/delsession/" + ses_id, function(data){
        window.location.reload();
    });
}

function acecrew_change_crew_status(session_crew_status_select_id)
{
        var crew_at_ses_status =  $('#' + session_crew_status_select_id + ' option:selected').val();
        session_crew_status_select_id = session_crew_status_select_id.split('_');
        crew_at_ses_nid = session_crew_status_select_id[4];
        crew_at_ses_uid = session_crew_status_select_id[5];
                
        $("#session_crew_status_ajax_" + crew_at_ses_nid + '_' + crew_at_ses_uid).html('<img src="' + Drupal.settings.basePath + Drupal.settings.acecrew.basepath + '/theme/ajax-loader-small.gif" />');
        $("#session_crew_status_form_" + crew_at_ses_nid + '_' + crew_at_ses_uid).hide(1);
        $("#session_crew_status_ajax_" + crew_at_ses_nid + '_' + crew_at_ses_uid).show(1);
        
        $.get(Drupal.settings.basePath + "acecrew/set_crew_session_status/" + crew_at_ses_nid + '/' + crew_at_ses_uid + '/' + crew_at_ses_status , function(data){
            var result = Drupal.parseJson(data);
            if(result.status == 'ok'){
                $("#session_crew_status_form_" + crew_at_ses_nid + '_' + crew_at_ses_uid).show(1);
                $("#session_crew_status_ajax_" + crew_at_ses_nid + '_' + crew_at_ses_uid).hide(1);
                
                $("#session_crew_statused_name_" + crew_at_ses_nid + '_' + crew_at_ses_uid).removeClass('session_crew_statused_name_deny session_crew_statused_name_sms session_crew_statused_name_confirm');
                $("#session_crew_statused_name_" + crew_at_ses_nid + '_' + crew_at_ses_uid).addClass('session_crew_statused_name_' + crew_at_ses_status);
            }
        });
}

$(document).ready(function() {    
    $('#acecrew_session_add_button').click(function(){
        acecrew_current_edit_item = 'acecrew_session_add_form';        
        $('#acecrew_session_add_form').show('fast');
        $('#acecrew_session_add_buttons').hide('fast');
        $('.acecrew_session_buttons').hide('fast');
    });
    
    $('.email_inv_quo').click(function(){
        var id = $(this).attr("id");
        id = id.substring(10);
        $('#client_emails_form_' + id).submit();
        return false;
    });
    
    
    $('.session_crew_status_select').change(function(){
        var session_crew_status_select_id = $(this).attr('id');
        acecrew_change_crew_status(session_crew_status_select_id);
    });
    
    
    //session crews generation
    $('#acecrew_session_add_form #edit-field-job-session-crews-items').hide();
    $('#acecrew_session_add_form #edit-field-job-session-crews-items').before('<button id="create_crew_boxes" type="button">Create crew boxes</button>');
    $('#create_crew_boxes').click(function(){
        $('#acecrew_session_add_form #edit-field-job-session-crews-field-job-session-crews-add-more').parent().hide();
        $('#acecrew_session_add_form #edit-field-job-session-crews-field-job-session-crews-add-more').trigger('mousedown');
        $('#acecrew_session_add_form #edit-field-job-session-crews-items').show();
        $('#acecrew_session_add_form #edit-field-job-session-crews-field-job-session-crews-add-more').parent().hide();
        return false;
    });
    
    
    $('body').ajaxComplete(function(){
        //set default values for edit forms.  session crews generation
        $('#acecrew_session_add_form #edit-field-job-session-crews-field-job-session-crews-add-more').parent().hide();
        var def_val = $('#edit-field-job-session-hours-value').val();
        if(def_val != ''){
            for(i = 0; i <= 100; i = i + 1){
                var curr_element = $('#edit-field-job-session-crews-' + i + '-value-field-crew-job-session-hours-quo-0-value');
                var curr_val = curr_element.val();
                if(curr_val == ''){
                    curr_element.val(def_val);
                }
            }
        }
        
    });
    
    
    Drupal.Ajax.plugins.acecrew = function(hook, args){
        if (hook == 'complete'){
            window.location.reload();
        }
        if (hook == 'scrollFind'){            
            document.getElementById(acecrew_current_edit_item).scrollIntoView(true);
            return false;
        }
    }
});