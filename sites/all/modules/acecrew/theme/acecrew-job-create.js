function fill_client_contacts_selectbox(selected_contact){
    $("#edit-field-job-client-contact-value").html('');
    var client_name = $('#edit-field-job-client-name-0-value').val();

    client_name = escape(encodeURIComponent(client_name));

    $.get(Drupal.settings.basePath + "acecrew/ajax/client_contacts/" + client_name, function(data){
        var result = Drupal.parseJson(data);

        $.each(result, function(val, text) {

            if(selected_contact == val) {
                $("#edit-field-job-client-contact-value").append($('<option selected="selected"></option>').val(val).html(text));
            } else {
                $("#edit-field-job-client-contact-value").append($('<option></option>').val(val).html(text));
            }

        });
    });

}

function clear_client_contacts_selectbox(){
    var selected_contact = $("#edit-field-job-client-contact-value option:selected").val();
    fill_client_contacts_selectbox(selected_contact);
}

function fill_client_contacts_second_selectbox(selected_contact){
    $("#edit-field-job-client-contact-second-value").html('');
    var client_name = $('#edit-field-job-client-name-0-value').val();

    client_name = escape(encodeURIComponent(client_name));

    $.get(Drupal.settings.basePath + "acecrew/ajax/client_contacts/" + client_name, function(data){
        var result = Drupal.parseJson(data);
        //result = $.extend({}, result,  { '': 'None' });
        console.log(result);
        var arr = Object.keys(result).map(function (key) {var pKey = key; var obj = {}; obj[key] = result[key]; return obj; });        
        arr.unshift({'': '--None--'});
        $.each(arr, function(index, obj) {            
            var val = Object.keys(obj)[0], text = obj[val];
            if(selected_contact == val) {
                $("#edit-field-job-client-contact-second-value").append($('<option selected="selected"></option>').val(val).html(text));
            } else {
                $("#edit-field-job-client-contact-second-value").append($('<option></option>').val(val).html(text));
            }

        });
    });
}

function clear_client_contacts_second_selectbox() {
    var selected_contact = $("#edit-field-job-client-contact-second-value option:selected").val();

    fill_client_contacts_second_selectbox(selected_contact);
}

$(document).ready(function() {    
    clear_client_contacts_selectbox();
    clear_client_contacts_second_selectbox();

    $("#edit-field-job-client-name-0-value").change(function() {
        fill_client_contacts_selectbox();
        fill_client_contacts_second_selectbox();
    });
});