$(document).ready(function() {		

	if ($('#edit-field-ub-date-start-0-value-datepicker-popup-0').length) {
		$('#edit-field-ub-date-start-0-value-datepicker-popup-0').datepicker({
			dateFormat: 'yy-mm-dd',
			onSelect: function (e, t) {
				var date = $(this).val();   
		      	$.getJSON('/acecrew/ajax/checkbookoff/' + date, function(data) {      		
		      		if (data.message != '') {
		      			alert('At least ' + data.max_crews_count + ' crew are booked off for ' + date + '\nList:\n' + data.message);
		      		}
		      	});
			}
		});
	}

	if ($('#edit-field-ub-date-end-0-value-datepicker-popup-0').length) {
		$('#edit-field-ub-date-end-0-value-datepicker-popup-0').datepicker({
			dateFormat: 'yy-mm-dd',
			onSelect: function (e, t) {
				var date = $(this).val();   
		      	$.getJSON('/acecrew/ajax/checkbookoff/' + date, function(data) {      		
		      		if (data.message != '') {
		      			alert('At least ' + data.max_crews_count + ' crew are booked off for ' + date + '\nList:\n' + data.message);
		      		}
		      	});
			}
		});
	}

	if ($('#edit-start-datetime').length) {
	    $('#edit-start-datetime').datetimepicker({ 
	      dateFormat: 'yy-mm-dd',
	      timeFormat: 'hh:ii',
	      onSelect: function (e, t) {
	      	var date = $(this).val();   
	      	$.getJSON('/acecrew/ajax/checkbookoff/' + date, function(data) {      		
	      		if (data.message != '') {
	      			alert('At least ' + data.max_crews_count + ' crew are booked off for ' + date + '\nList:\n' + data.message);
	      		}
	      	});
	      }
	    });
	}

	if ($('#edit-end-datetime').length) {
	    $('#edit-end-datetime').datetimepicker({ 
	      dateFormat: 'yy-mm-dd',
	      timeFormat: 'hh:ii',
	      onSelect: function (e, t) {
	      	var date = $(this).val();   
	      	$.getJSON('/acecrew/ajax/checkbookoff/' + date, function(data) {      		
	      		if (data.message != '') {
	      			alert('At least ' + data.max_crews_count + ' crew are booked off for ' + date + '\nList:\n' + data.message);
	      		}
	      	});
	      }  
	    });
	}
});