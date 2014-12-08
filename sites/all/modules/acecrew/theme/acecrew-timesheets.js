$(document).ready(function() {

    $("#edit-timesheets-crews-active-wrapper, #edit-timesheets-crews-inactive-wrapper").hide();
    var select_all = 1,
        select_active = 2,
        select_inactive = 3;

    $('#acecrew-reports-timesheets-from input:radio').change(function(){

        if( $(this).val() == select_all ) {
            $("#acecrew-reports-timesheets-from option:selected").removeAttr("selected");
            $("#edit-timesheets-crews-wrapper").show();
            $("#edit-timesheets-crews-active-wrapper, #edit-timesheets-crews-inactive-wrapper").hide();
        }

        if( $(this).val() == select_active ) {
            $("#acecrew-reports-timesheets-from option:selected").removeAttr("selected");
            $("#edit-timesheets-crews-active-wrapper").show();
            $("#edit-timesheets-crews-wrapper, #edit-timesheets-crews-inactive-wrapper").hide();
        }

        if( $(this).val() == select_inactive ) {
            $("#acecrew-reports-timesheets-from option:selected").removeAttr("selected");
            $("#edit-timesheets-crews-inactive-wrapper").show();
            $("#edit-timesheets-crews-wrapper, #edit-timesheets-crews-active-wrapper").hide();
        }

        console.log( $(this).val() );
    });

});
