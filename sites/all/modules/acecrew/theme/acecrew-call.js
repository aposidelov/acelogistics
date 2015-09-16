$(document).ready(function() {	
	$('.form-submit.ajax-trigger').click(function() {
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