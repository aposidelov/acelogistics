$(document).ready(function() {
    $('#acecrew-report-form').submit(function(){
        
        $("#acecrew_report_output").html('<img src="' + Drupal.settings.basePath + Drupal.settings.acecrew.basepath + '/theme/ajax-loader.gif" />');
        
        var acecrew_start_date = $('#edit-timer-datepicker-popup-0').val();
        var acecrew_end_date = $('#edit-timer1-datepicker-popup-0').val();
        
        $.get(Drupal.settings.basePath + "acecrew/ajax/report/" + acecrew_start_date + "/" + acecrew_end_date + "/" + Drupal.settings.acecrew.report_uid, function(data){
            var result = Drupal.parseJson(data);
            $("#acecrew_report_output").html(result.html);
        });
        
        return false;
    });
});
