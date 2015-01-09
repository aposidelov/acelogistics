var acecrew_current_edit_item = null;

function acecrew_session_edit(ses_id)
{
    acecrew_current_edit_item = 'acecrew_session_form_' + ses_id;
    $('#acecrew_session_content_' + ses_id).hide('fast');
    $('#acecrew_session_buttons_' + ses_id).hide('fast');
    $('.acecrew_session_add_block').hide('fast');
    $('#acecrew_session_form_' + ses_id).show('fast');
    $('#' + acecrew_current_edit_item + "  form").attr("action", "/node/" + ses_id +"/edit");
}

function acecrew_session_del(ses_id)
{
    $.get(Drupal.settings.basePath + "acecrew/ajax/delsession/" + ses_id, function(data) {
        window.location.reload();
    });
}

function acecrew_session_status_toogle(ses_id)
{
    $.get(Drupal.settings.basePath + "acecrew/ajax/status-session/" + ses_id, function(data) {
        window.location.reload();
    });
}

$(document).ready(function() {
    $('#acecrew_session_add_button').click(function(){
        var url = $(location).attr('href');
        var n = url.split("/");
        var url_alias = n[n.length - 2] + "/" + n[n.length - 1];
        $.ajax({
            url: Drupal.settings.basePath + 'ajax/content_lock/checkbutton',  /*'node/786/edit', */
            data: {nodeurl: url_alias /* kajax: 'ajax' */},
            async: false,
            cache: false,
            success: function(data) {
                if(data.indexOf('"internal_urls"') != -1)
                {
                    $('#acecrew_session_add_form').show('fast');
                    $('#acecrew_session_add_buttons').hide('fast');
                    $('.acecrew_session_buttons').hide('fast');
                    $('#acecrew_job_lock_message').html('');
                    $('#acecrew_job_lock_message').css({
                        display: 'none'
                    });

                    $('#acecrew_session_add_form .buttons .form-submit').click(function() {

                        var date = $('#edit-field-job-session-date-time-0-value-datepicker-popup-0').val(),
                            time = $('#edit-field-job-session-date-time-0-value-timeEntry-popup-1').val();

                        var months = {
                            Jan: 0,
                            Feb: 1,
                            Mar: 2,
                            Apr: 3,
                            May: 4,
                            Jun: 5,
                            Jul: 6,
                            Aug: 7,
                            Sep: 8,
                            Oct: 9,
                            Nov: 10,
                            Dec: 11
                        }

                        var year = date.substr(0, 4),
                            month = date.substr(5, 3),
                            day = date.substr(9),
                            hour = time.substr(0, 2),
                            min = time.substr(3, 2);

                        var call_date = new Date(year, months[month], day, hour, min);

                        if(call_date < new Date()) {
                            var result = confirm('The session you are creating have a date that is set in the past.');

                            if(result) {
                                return true;
                            } else {
                                return false
                            }

                        } else {

                            return true;

                        }

                    })





                }
                else
                {
                    var start = data.indexOf('<div class="messages warning">');
                    var messagePart = data.substring(start);
                    var end = messagePart.indexOf('</div>');
                    messagePart = messagePart.substring(0, end + 6);
                    $('#acecrew_job_lock_message').html(messagePart);

                    $('#acecrew_job_lock_message').css({
                        display: 'block'
                    });
                }
            }
        });


        /*
         $('#acecrew_session_add_form').show('fast');
         $('#acecrew_session_add_buttons').hide('fast');
         $('.acecrew_session_buttons').hide('fast');
         */
    });


    $('.email_inv_quo').click(function(){
        var id = $(this).attr("id");
        id = id.substring(10);
        $('#client_emails_form_' + id).submit();
        return false;
    });


    /*$('.session_crew_status_select').change(function(){
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
     });*/




    $('body').ajaxComplete(function(){
        //set default values for edit forms.  session crews generation

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