$(document).ready(function(){	
	$('#edit-field-job-client-name-0-value').change(function() {		
		var client_name = $(this).val();
		//client_name = $.trim(client_name);		
		console.log(escape(client_name));		
		$.getJSON('/admin/ajax/client-account/-?client_name=' + escape(client_name), function(data) {
			console.log(data);
			if (data.client_nid) {								
				var href = '/ace_modals/nojs/client_contact_add/' + data.client_nid;
				$('.client-contact-add-container a').attr('href', href);
				$('.client-contact-add-container').show();
			} else {
				$('.client-contact-add-container').hide();
			}
			if (!data.status) {				
				alert('Client Does not have an account');
			}
		});
	});
});