$(document).ready(function(){	
	$('#edit-field-job-client-name-0-value').change(function() {		
		var client_name = $(this).val();
		var second_contact = $('#second-contact-label').text();
		//client_name = $.trim(client_name);		
		console.log(escape(client_name));		
		update_client_contact_link(client_name, second_contact, true);
	});

	$('#edit-field-job-client-contact-second-value').change(function() {
		var client_name = $('#edit-field-job-client-name-0-value').val();
		var contact = $(this).find('option:selected').text();
		$('#second-contact-label').text(contact);

		update_client_contact_link(client_name, contact, false);
	});
});

function update_client_contact_link(client_name, second_contact, show_alert) {
	$.getJSON('/admin/ajax/client-account/-?client_name=' + escape(client_name), function(data) {		
		if (data.client_nid) {
			second_contact = !show_alert ? second_contact : '-';
			var href = '/ace_modals/nojs/client_contact_add/' + data.client_nid + '/' + escape(second_contact);
			$('.client-contact-add-container a').attr('href', href);
			$('.client-contact-add-container').show();
		} else {
			$('.client-contact-add-container').hide();
		}
		if (show_alert && !data.status) {				
			alert('Client Does not have an account');
		}
	});
}