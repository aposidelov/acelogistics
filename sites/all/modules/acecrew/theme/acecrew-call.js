$(document).ready(function() {	       
	$('.form-submit.ajax-trigger').click(function() {
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
        var result = true;
        if (call_date < new Date()) {
            result = confirm('The session you are creating have a date that is set in the past.');
        }

        if (!result) {
            return false;
        }
       

		var button = $(this);
		var fid = function() {
			if (button.attr('value') == 'Save') {				
				parent.window.location.reload();
				button.attr('value', 'Reloading...');				
			}
		}
		setInterval(fid, 2000);
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