$(document).ready(function(){	
	$('#edit-field-job-client-name-0-value').change(function() {
		//console.log($(this).val());
		var client_name = $(this).val();
		$.getJSON('/admin/ajax/client-rate/' + client_name, function(data) {
			$('#edit-field-client-2h-default-0-value').val(data.hours_2);
			$('#edit-field-client-3h-default-0-value').val(data.hours_3);
			alert('Client 2h, 3h charges have been added for this job (see below)');			
		});
	});
});