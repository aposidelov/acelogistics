$(document).ready(function(){
	console.log('jjj');

	$('#edit-field-job-client-name-0-value').change(function() {
		console.log($(this).val());
		var client_name = $(this).val();
		$.getJSON('/admin/ajax/client-account/' + client_name, function(data) {
			if (data.status) {
				console.log('exists');
			} else {
				alert('Client Does not have an account');
			}
		})
	});
});