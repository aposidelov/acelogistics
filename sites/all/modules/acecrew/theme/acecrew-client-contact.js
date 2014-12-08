//display contact that selected in #select_client_contact selectbox
function show_client_contact()
{
    var selected_contact_id = $('#select_client_contact option:selected').val();
    $('.client_contact_item').hide(1);
    $('#client_contact_id_' + selected_contact_id).show(1);
}
$(document).ready(function() {
    show_client_contact();
    $('#select_client_contact').change(function(){
        show_client_contact();
    });
    $('#select_client_contact').keypress(function(){
        show_client_contact();
    });
});