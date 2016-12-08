$(document).ready(function() {	       
	$('.form-submit.ajax-trigger').click(function() {
        var button = $(this);        
        console.log(Drupal.settings.jobNid);
        // add loader above button if it does not exist
        if (!$('.loader').length) {
            $('body').append('<div class="loader"></div>');
            //$('.buttons').prepend('<div class="loader"></div>');            
        } 
        $.blockUI({message: $('.loader')});
        $('.loader').html('<h4>Check if a client is being editing...<span class="views-throbbing">&nbsp;</span></h4>');
        var isEditing = false;
        var intervalId = setInterval(function() {
            $.getJSON('/admin/ajax/client-is-editing/' + Drupal.settings.jobNid, function(data) {
                if (data.isClientEditing) {
                    isEditing = true;                    
                    $('.loader').html('<h4>Client is being editing by another user please wait...<span class="views-throbbing">&nbsp;</span></h4>');                
                } else {
                    clearInterval(intervalId);
                    acecrew_refresh_contacts(Drupal.settings.jobNid, 
                        '#edit-field-call-contact-value', 
                        '#edit-field-call-contact-second-value', 
                        $('.loader'), false,
                        function() {
                            // check if setup datetime is bigger than current datetime. 
                            // if it's - show confirmation message
                            var date = $('#edit-field-job-session-date-time-0-value-datepicker-popup-0').val(),
                                time = $('#edit-field-job-session-date-time-0-value-timeEntry-popup-1').val();

                            var year = date.substr(6, 4),
                                month = parseInt(date.substr(3, 2)) - 1,
                                day = date.substr(0, 2),
                                hour = time.substr(0, 2),
                                min = time.substr(3, 2);                            
                            var callDate = new Date(year, month, day, hour, min);
                            //////////////////////////////////////////////////////////////////
                            /*var months = {
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
                            var callDate = new Date(year, months[month], day, hour, min);
                            */
                            //////////////////////////////////////////////////////////////////
                            var currentDate = new Date();
                            console.log('callDate', callDate);
                            console.log('currentDate', currentDate);
                            var result = true;
                            if (callDate < currentDate) {
                                result = confirm('The session you are creating have a date that is set in the past.');
                            }
                            if (!result) {
                                $('.loader').html('');
                                $.unblockUI();
                                return false;
                            }
                            $('.loader').html('<h4>The call is being saving...<span class="views-throbbing">&nbsp;</span></h4>');
                            // submit a form 
                            $('.modalframe-page-content #node-form').submit();                                            
                            var fid = function() {
                                if (button.attr('value') == 'Save') {               
                                    parent.window.location.reload();
                                    button.attr('value', 'Reloading...');               
                                }
                            }
                            setInterval(fid, 2000);
                        }
                    );
                    // if client was edited...
                    if (isEditing) {                        
                        /*$('.loader').html('<h4>New contacts are being taken from the updated client...<span class="views-throbbing">&nbsp;</span></h4>');
                        $.getJSON('/admin/ajax/client-get-contacts/' + Drupal.settings.jobNid, function(data) {
                            var oldContacts = {};
                            var contactFirstSelector = '#edit-field-call-contact-value';
                            var contactSecondSelector = '#edit-field-call-contact-second-value';
                            $(contactFirstSelector + ' option').each(function() {
                                var self = $(this);
                                oldContacts['' + self.val()] = self.text();
                            });                            
                            var updatedContacts = data.updatedContacts;
                            //console.log('oldContacts', oldContacts);
                            //console.log('updatedContacts', updatedContacts);
                            // get old selected value of contact
                            var contactFirstValueOld = $(contactFirstSelector + ' option:selected').text();                                                                                    
                            // populate contact select with new data
                            var contactsList = $(contactFirstSelector);
                            contactsList.html('');
                            $.each(updatedContacts, function(index, value) {
                                if (value === contactFirstValueOld) {                                    
                                    contactsList.append($("<option />").val(index).text(value).attr('selected', 'selected'));                                    
                                } else {
                                    contactsList.append($("<option />").val(index).text(value));
                                }
                            });
                            var contactFirstValueNew = $(contactFirstSelector + ' option:selected').text();

                            // update second contact field
                            contactsListSecond = $(contactSecondSelector);
                            contactSecondValueOld = contactsListSecond.find('option:selected').text();
                            contactsListSecond.html('');
                            if (contactSecondValueOld === '') {
                                contactsListSecond.append($("<option />").val('').text('- None -').attr('selected', 'selected'));
                            } else {
                                contactsListSecond.append($("<option />").val('').text('- None -'));    
                            }                            
                            $.each(updatedContacts, function(index, value) {
                                if (value === contactSecondValueOld) {                                    
                                    contactsListSecond.append($("<option />").val(index).text(value).attr('selected', 'selected'));                                    
                                } else {
                                    contactsListSecond.append($("<option />").val(index).text(value));
                                }
                            });
                            var contactSecondValueNew = contactsListSecond.find('option:selected').text();
                            var message = 'Client contacts have been updated.';
                            if (contactFirstValueOld === contactFirstValueNew) {
                                //message += '\nClient contact: ' + contactFirstValueNew;
                            } else {
                                message += '\nClient contact: ' + contactFirstValueOld + ' was changed - select a new one';
                            }
                            if (contactSecondValueOld === contactSecondValueNew) {
                                //message += '\nClient contact second: ' + contactSecondValueNew;
                            } else {
                                message += '\nClient contact second: ' + contactSecondValueOld + ' was changed - select a new one';
                            }
                            $('.loader').html('');                            
                            alert(message);
                        });
                        */
                    } else {                        
                        /*// check if setup datetime is bigger than current datetime. 
                        // if it's - show confirmation message
                        var date = $('#edit-field-job-session-date-time-0-value-datepicker-popup-0').val(),
                            time = $('#edit-field-job-session-date-time-0-value-timeEntry-popup-1').val();

                        var year = date.substr(6, 4),
                            month = date.substr(3, 2),
                            day = date.substr(0, 2),
                            hour = time.substr(0, 2),
                            min = time.substr(3, 2);
                        var callDate = new Date(year, month, day, hour, min);
                        var currentDate = new Date();
                    
                        var result = true;
                        if (callDate < currentDate) {
                            result = confirm('The session you are creating have a date that is set in the past.');
                        }
                        if (!result) {
                            $('.loader').html('');
                            return false;
                        }
                        $('.loader').html('<h4>The call is being saving...<span class="views-throbbing">&nbsp;</span></h4>');
                        // submit a form 
                        $('.modalframe-page-content #node-form').submit();                                            
                        var fid = function() {
                            if (button.attr('value') == 'Save') {               
                                parent.window.location.reload();
                                button.attr('value', 'Reloading...');               
                            }
                        }
                        setInterval(fid, 2000);
                        */
                    }

                }            
            });
        }, 3000);
        
        return false;

        /*var date = $('#edit-field-job-session-date-time-0-value-datepicker-popup-0').val(),
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
        var result = true;
        if (call_date < new Date()) {
            result = confirm('The session you are creating have a date that is set in the past.');
        }

        if (!result) {
            return false;
        }
        */

		/*var button = $(this);
		var fid = function() {
			if (button.attr('value') == 'Save') {				
				parent.window.location.reload();
				button.attr('value', 'Reloading...');				
			}
		}
		setInterval(fid, 2000);
        */
	});

	var jobNid = $('input[id*="job-nid-0-value"]').val();	
	var venueName = $('[name*="field_job_session_venue"]').val();
	var commentDiv = $('div[id*="job-session-comment"]');                    
    var commentField = commentDiv.find('textarea');
    $('[name*="field_job_session_venue"]').change(function() {
            venueName = $(this).val();            
        });

    $('<a class="update_comment" href="#">Client & Venue comments update</a>')
        .appendTo(commentDiv.find('label'))
        .click(function() {                                 
            acecrewUpdateComments(commentField, jobNid, venueName);
            return false;
        });
});


function acecrewUpdateComments(commentField, jobNid, venueName) {
    var comment = commentField.val();   
    if (comment == '' || comment == undefined) {
        //return '';
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

function getKeyByValue(obj, value ) {
    for ( var prop in obj ) {
        if ( obj.hasOwnProperty(prop) ) {
             if ( obj[ prop ] === value ) {
                 return prop;
             }
        }
    }
}