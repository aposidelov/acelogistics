var calendar_popup_sms_click = function(baseurl,call_nid){
    $url = baseurl + "/acecrew/calendar-popup/sms/" + call_nid;
    options = {
        url : $url,
        width: 300,
        height: 400,
        autoFit: true
    }
    Drupal.modalFrame.open(options);
    return false;
}

var udpate_status_onclick = function(){

    $("html, body").animate({ scrollTop: 0 }, "slow");

    var types = $(".supplements-type");
    var args = $('#job-session-id').val();

    types.each(function() {
        args +=  ":" + $(this).attr("id")+ ":" + $(this).val();
    });
    $("#block-block-2").fadeOut(1000);
    $.get(Drupal.settings.basePath + "acecrew/calendar/set-status/" + args, function(data){
        var li_id = $("#block-block-2 #job-session-id").val();

        $("#acecrew_calendar_output").html('<img class="loading-gif" src="' + Drupal.settings.basePath + Drupal.settings.acecrew.basepath + '/theme/ajax-loader.gif" />');
        forward = $('#acecrew_calendar_forward_days').val();

        $.get(Drupal.settings.basePath + "js/acecrew/calendar/" + $('#edit-date-timer-datepicker-popup-0').val() + "/" + forward, function(data){
            var result = Drupal.parseJson(data);
            $("#acecrew_calendar_output").html(result.html);
            $("ul.call-listing li input[value=\"" + li_id + "\"]").parent().addClass("active-load-call");
            $("ul.call-listing li input[value=\"" + li_id + "\"]").parent().find(".loadbtn").click();
            $('html, body').animate({
                scrollTop: $("#call-listing-item-"+li_id).offset().top
            }, 1000);
        });
    });
}
