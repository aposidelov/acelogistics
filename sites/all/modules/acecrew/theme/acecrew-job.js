var acecrew_current_edit_item = null;

function acecrew_session_edit(ses_id) {
    acecrew_current_edit_item = 'acecrew_session_form_' + ses_id;
    $('#acecrew_session_content_' + ses_id).hide('fast');
    $('#acecrew_session_buttons_' + ses_id).hide('fast');
    $('.acecrew_session_add_block').hide('fast');
    $('#acecrew_session_form_' + ses_id).show('fast');
    $('#' + acecrew_current_edit_item + "  form").attr("action", "/node/" + ses_id +"/edit");
}

function acecrew_session_del(ses_id) {
    $.get(Drupal.settings.basePath + "acecrew/ajax/delsession/" + ses_id, function(data) {
        window.location.reload();
    });
}

function acecrew_session_status_toogle(ses_id) {
    $.get(Drupal.settings.basePath + "acecrew/ajax/status-session/" + ses_id, function(data) {
        window.location.reload();
    });
}

function acecrewUpdateComments(commentField, jobNid, venueName) {
    var comment = commentField.val();   
    if (comment == '' || comment == undefined) {
        return '';
    }
    var isClientCommentExists = comment.indexOf('Client:') !== -1;
    var isVenueCommentExists  = comment.indexOf('Venue:') !== -1;
    $.getJSON('/admin/ajax/client-comment/' + jobNid + '/job', function(data) {
        if (data.comment != '' && !isClientCommentExists) {             
            if (commentField.val() != '') {
                comment = comment + '\n';
            }
            comment += data.comment;                                    
            commentField.val(comment);
        }
        
        $.getJSON('/admin/ajax/venue-comment/' + venueName + '/name', function(data) {
            if (data.comment != '' && !isVenueCommentExists) {
                if (commentField.val() != '') {
                    comment = comment + '\n';
                }                                                                
                comment += data.comment;
                commentField.val(comment);
            }
        });
    });                            
 
}

$(document).ready(function() {

    console.log('job-page2');    
    var clientName = $('#edit-field-job-client-name-0-value').val();
    console.log('clientName', clientName);  
    if (clientName != undefined && clientName !== '') {
        $('body').append('<div class="loader"></div>');
            //$('.buttons').prepend('<div class="loader"></div>');
        $.blockUI({message: $('.loader')});
        //$('body').append('<div id="blockMessage"></div>');
        var isEditing = false;        
        $('.loader').html('<h4>Check if a client is being editing...<span class="views-throbbing">&nbsp;</span></h4>');
        var intId = setInterval(function() {            
            $.getJSON('/admin/ajax/client-is-editing/' + clientName, function(data) {
                console.log('data', data);
                if (data.isClientEditing) {
                    isEditing = true;
                    console.log('editing');                    
                    $('.loader').html('<h4>Client is being editing by another user please wait and reload page...<span class="views-throbbing">&nbsp;</span></h4>');                    
                } else {
                    console.log('no-edit');
                    clearInterval(intId);
                    if (isEditing) {
                        /*acecrew_refresh_contacts(clientName, 
                            '#edit-field-job-client-contact-value', 
                            '#edit-field-job-client-contact-second-value', 
                            $('#edit-submit-1'), $('#blockMessage'),
                            true,
                            function() {
                                $.unblockUI();
                                $('#blockMessage').html('');
                            }
                        );*/
                        window.location.reload(true);
                    } else {
                        $.unblockUI();
                        $('.loader').html('');
                    }                   
                }
            });
        }, 2000);
    } 

    //$.blockUI();
    //$.unblockUI();

    $('#edit-submit-1').click(function() {
        var button = $(this);
        var clientName = $('#edit-field-job-client-name-0-value').val();  
        console.log('clientName', clientName);        
        // add loader above button if it does not exist
        if (!$('.loader').length) {
            $('.buttons').prepend('<div class="loader"></div>');
        }  
        $.blockUI({message: $('.loader')});      
        $('.loader').html('<h4>Check if a client is being editing...<span class="views-throbbing">&nbsp;</span></h4>');
        var isEditing = false;
        var intervalId = setInterval(function() {
            $.getJSON('/admin/ajax/client-is-editing/' + clientName, function(data) {                
                if (data.isClientEditing) {
                    isEditing = true;                    
                    $('.loader').html('<h4>Client is editing by another user please wait...<span class="views-throbbing">&nbsp;</span></h4>');                
                } else {
                    clearInterval(intervalId);                    
                    // if client was edited...                    
                    acecrew_refresh_contacts(clientName, 
                        '#edit-field-job-client-contact-value', 
                        '#edit-field-job-client-contact-second-value', 
                        $('.loader'), false,
                        function() {
                            $('.loader').html('<h4>The job is being saving...<span class="views-throbbing">&nbsp;</span></h4>');
                            button.unbind('click');
                            button.trigger('click');
                        }
                    );
                                            
                }
            });
        }, 3000);
        return false;
    });

    $('.acecrewAddNewCall, .acecrew_session_edit_button').click(function() {
        var $self = $(this);

        if (!$('.loader').length) {
            $('body').append('<div class="loader"></div>');
            $.blockUI({message: $('.loader')});
            //$self.parent().after('<div style="float:right;text-align:right;" class="loader"></div>');
        }        
        $('.loader').html('<h4>Check if a client is being editing...<span class="views-throbbing">&nbsp;</span></h4>');
        var intervalId = setInterval(function() {
            $.getJSON('/admin/ajax/client-is-editing/' + Drupal.settings.jobNid, function(data) {
                if (data.isClientEditing) {                    
                    $('.loader').html('<h4>Client is editing by another user please wait...<span class="views-throbbing">&nbsp;</span></h4>');                
                } else {
                    clearInterval(intervalId);
                    $('.loader').html('');
                    $.unblockUI();
                    if ($self.hasClass('acecrewAddNewCall')) {                
                            Drupal.modalFrame.open({
                                url: '/acecrew/get_call_add_form/' + Drupal.settings.jobNid, 
                                width: 700,
                                height: 1200
                            });                            
                    } else if ($self.hasClass('acecrew_session_edit_button')) {            
                        var callNid = $self.attr('data-call-id');
                        Drupal.modalFrame.open({
                            url: '/acecrew/get_call_edit_form/' + callNid, 
                            width: 700, 
                            height: 1200
                        });
                    }
                    return false;
                }
            });
        }, 2000);        
    });

    var jobNid = $('#acecrew_session_add_buttons').attr('data-job-nid');

    $('.acecrew_sessions_container').each(function() {                
        var venueName = $(this).find('[name*="field_job_session_venue"]').val();         
        var commentDiv = $(this).find('div[id*="job-session-comment"]');                    
        var commentField = commentDiv.find('textarea');

        $(this).find('[name*="field_job_session_venue"]').change(function() {
            venueName = $(this).val();            
        });
        
        $('<a class="update_comment" href="#">Client & Venue comments update</a>')
            .appendTo(commentDiv.find('label'))
            .click(function() {                                     
                acecrewUpdateComments(commentField, jobNid, venueName);
                return false;
            });
    });

    /*
    $('[name*="field_job_session_venue"]').change(function() {
        callVenueName = $(this).val();
    });*/
    var venueName = $('#acecrew_session_add_form [name*="field_job_session_venue"]').val();    
    $('#acecrew_session_add_form [name*="field_job_session_venue"]').change(function() {
        venueName = $(this).val();
    });    
    var commentDiv = $('#acecrew_session_add_form div[id*="job-session-comment"]');                    
    var commentField = commentDiv.find('textarea');
    acecrewUpdateComments(commentField, jobNid, venueName);
                        
    $('<a class="update_comment" href="#">Client & Venue comments update</a>')
        .appendTo(commentDiv.find('label'))
        .click(function() {                                                
            acecrewUpdateComments(commentField, jobNid, venueName);
            return false;
        });
    

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
                if (data.indexOf('"internal_urls"') != -1) {                                                            

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
                } else {
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