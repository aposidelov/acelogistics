$(document).ready(function() {	
	console.log($('#edit-start-datetime').attr('id'));
    $('#edit-start-datetime').datetimepicker({ 
      dateFormat: 'yy-mm-dd',
      timeFormat: ' hh:ii' 
    });

    $('#edit-end-datetime').datetimepicker({ 
      dateFormat: 'yy-mm-dd',
      timeFormat: ' hh:ii' 
    });
});