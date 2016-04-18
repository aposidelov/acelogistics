$(document).ready(function(){	
	$('#edit-field-job-client-name-0-value').change(function() {
		//console.log($(this).val());
		var client_name = $(this).val();
		$.getJSON('/admin/ajax/client-rate/' + client_name, function(data) {			
			$('#edit-field-client-2h-default-0-value').val(data.hours_2);
			$('#edit-field-client-3h-default-0-value').val(data.hours_3);
			$('#edit-field-client-hourly-rate-default-value').val(data.hourly_rate);
		});
	});
});