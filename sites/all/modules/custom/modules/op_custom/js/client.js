$(document).ready(function(){
	console.log('sss');
    // do some fancy stuff
    //$('#edit-field-credit-limit-box-0-value-wrapper').hide();

    var value = $('#edit-field-credit-limit-box-0-value').val();
    var status = '';
    if (value !== '') {
    	status = 'checked';
    }

    $('<input style="display:inline-block;" type="checkbox" '+status+' name="limit-box-enabled" id="limit-box-enabled"><label style="vertical-align:top;display:inline-block;margin-left: 5px;" for="limit-box-enabled">Account status box</label>')
		.insertBefore('#edit-field-credit-limit-box-0-value-wrapper')
		.change(function() {
			var creditLimitBox = $('#edit-field-credit-limit-box-0-value-wrapper');
	        if ( $(this).is(':checked') ) {
	       		creditLimitBox.show();
	        } else {
	       		creditLimitBox.hide();
	       		creditLimitBox.find('#edit-field-credit-limit-box-0-value').val('');
	        }
	    }
    );    

	$('#limit-box-enabled').trigger('change');
    
    

});