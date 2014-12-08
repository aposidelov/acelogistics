function fill_client_contacts_selectbox(){
    $("#edit-field-job-client-contact-value").html('');
    var client_name = $('#edit-field-job-client-name-0-value').val();
    
    $.get(Drupal.settings.basePath + "acecrew/ajax/client_contacts/" + client_name, function(data){
        var result = Drupal.parseJson(data);
        $.each(result, function(val, text) {
            $("#edit-field-job-client-contact-value").append(
                $('<option></option>').val(val).html(text)
            );
        });
    });
    
}

function clear_client_contacts_selectbox(){
    var selected_contact = $("#edit-field-job-client-contact-value option:selected").val();
    fill_client_contacts_selectbox();
    $("#edit-field-job-client-contact-value [value='" + selected_contact + "']").attr("selected", "selected");
}

$(document).ready(function() {
    clear_client_contacts_selectbox();
    
    $("#edit-field-job-client-name-0-value").change(function(){
        fill_client_contacts_selectbox();
    });
});