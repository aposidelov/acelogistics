$(document).ready(function() {
    $("#edit-field-fine-staff-id-value-wrapper").hide();
    
    $('#edit-field-fine-job-number-0-value-wrapper').after('<div id="acecrew_fines_info"><p id="client_id"><span class="bold">Client: </span><span id="acecrew_client_id_val"></span></p> <p id="venue_id"><span class="bold">Venue: </span><span id="acecrew_venue_id_val"></span></p></div>');
    $("#acecrew_fines_info").hide();
    
    $('#node-form').after('<div id="acecrew_ajax_loader"> </div>');
    $("#acecrew_ajax_loader").hide();
    $("#acecrew_ajax_loader").html('<img src="' + Drupal.settings.basePath + Drupal.settings.acecrew.basepath + '/theme/ajax-loader.gif" />');
    $('#edit-field-fine-job-number-0-value').change(function(){
        $('#node-form').hide();
        $("#acecrew_ajax_loader").show();
        
        $("#acecrew_fines_info").show();
        $("#edit-field-fine-staff-id-value-wrapper").show();
        
        $.get(Drupal.settings.basePath + "acecrew/ajax/fines/" + this.value, function(data){
            var result = Drupal.parseJson(data);
            $('#edit-field-fine-client-id-value').val(result.client_id);
            $('#edit-field-fine-venue-id-value').val(result.venue_id);
            
            var client_text = $("#edit-field-fine-client-id-value option:selected").text();
            var venue_text = $("#edit-field-fine-venue-id-value option:selected").text();
            $('#acecrew_client_id_val').html(client_text);
            $('#acecrew_venue_id_val').html(venue_text);
            
            $('#edit-field-fine-staff-id-value').html('');
            $.each(result.staff_ids, function(val, text) {
                $('#edit-field-fine-staff-id-value').append(
                    $('<option></option>').val(val).html(text)
                );
            });
            
            $('#node-form').show();
            $("#acecrew_ajax_loader").hide();
        });
        
    });
});