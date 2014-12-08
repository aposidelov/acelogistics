jQuery(document).ready(function(){
    /* $('#accordion .head').click(function() {
     $(this).next().toggle('slow');
     return false;
     }).next().hide();  */

    //Disallow space to toggle accordion
    $.ui.accordion.prototype._keydown = function( event ) {
        return;
    };

    $('.tr_check').each(function(index) {
        var currId = $(this).attr('id');
        if($(this).is(":checked")){

            $('#' + currId.replace('_use_', '_crew_ph_')).removeAttr("disabled");
            $('#' + currId.replace('_use_', '_crew_of_')).removeAttr("disabled");
            $('#' + currId.replace('_use_', '_client_ph_')).removeAttr("disabled");
            $('#' + currId.replace('_use_', '_client_of_')).removeAttr("disabled");
            $('#' + currId.replace('_use_', '_comment_')).removeAttr("disabled");

            $('#' + currId.replace('_use_', '_crew_ph_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_crew_of_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_client_ph_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_client_of_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_comment_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('_use_', '_crew_ph_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_crew_of_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_client_ph_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_client_of_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_comment_')).attr("disabled","disabled");

            $('#' + currId.replace('_use_', '_crew_ph_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_crew_of_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_client_ph_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_client_of_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_comment_')).css("background-color", "#cccccc");
        }
    });
    // $('.tr_crew_of').keyup(function() {
    $(".fine_check").each(function(index){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){
            $('#' + currId.replace('fine_', 'fine_amount_')).removeAttr("disabled");
            $('#' + currId.replace('fine_', 'fine_amount_')).css("background-color", "white");

            $('#' + currId.replace('fine_', 'fine_desc_')).removeAttr("disabled");
            $('#' + currId.replace('fine_', 'fine_desc_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('fine_', 'fine_amount_')).attr("disabled","disabled");
            $('#' + currId.replace('fine_', 'fine_amount_')).css("background-color", "#cccccc");

            $('#' + currId.replace('fine_', 'fine_desc_')).attr("disabled","disabled");
            $('#' + currId.replace('fine_', 'fine_desc_')).css("background-color", "#cccccc");

        }
    });

    $(".fine_check").click(function(){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){
            $('#' + currId.replace('fine_', 'fine_amount_')).removeAttr("disabled");
            $('#' + currId.replace('fine_', 'fine_amount_')).css("background-color", "white");

            $('#' + currId.replace('fine_', 'fine_desc_')).removeAttr("disabled");
            $('#' + currId.replace('fine_', 'fine_desc_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('fine_', 'fine_amount_')).attr("disabled","disabled");
            $('#' + currId.replace('fine_', 'fine_amount_')).css("background-color", "#cccccc");

            $('#' + currId.replace('fine_', 'fine_desc_')).attr("disabled","disabled");
            $('#' + currId.replace('fine_', 'fine_desc_')).css("background-color", "#cccccc");
        }
    });

    $(".no_show_check").each(function(index){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){
            $('#' + currId.replace('no_show_', 'no_show_amount_')).removeAttr("disabled");
            $('#' + currId.replace('no_show_', 'no_show_amount_')).css("background-color", "white");

            $('#' + currId.replace('no_show_', 'no_show_desc_')).removeAttr("disabled");
            $('#' + currId.replace('no_show_', 'no_show_desc_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('no_show_', 'no_show_amount_')).attr("disabled","disabled");
            $('#' + currId.replace('no_show_', 'no_show_amount_')).css("background-color", "#cccccc");

            $('#' + currId.replace('no_show_', 'no_show_desc_')).attr("disabled","disabled");
            $('#' + currId.replace('no_show_', 'no_show_desc_')).css("background-color", "#cccccc");
        }
    });

    $(".no_show_check").click(function(){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){
            $('#' + currId.replace('no_show_', 'no_show_amount_')).removeAttr("disabled");
            $('#' + currId.replace('no_show_', 'no_show_amount_')).css("background-color", "white");

            $('#' + currId.replace('no_show_', 'no_show_desc_')).removeAttr("disabled");
            $('#' + currId.replace('no_show_', 'no_show_desc_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('no_show_', 'no_show_amount_')).attr("disabled","disabled");
            $('#' + currId.replace('no_show_', 'no_show_amount_')).css("background-color", "#cccccc");

            $('#' + currId.replace('no_show_', 'no_show_desc_')).attr("disabled","disabled");
            $('#' + currId.replace('no_show_', 'no_show_desc_')).css("background-color", "#cccccc");
        }
    });

    //Crew total add check
    $(".crew_total_add_check").each(function(index){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){
            $('#' + currId.replace('add_', 'add_amount_')).removeAttr("disabled");
            $('#' + currId.replace('add_', 'add_amount_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('add_', 'add_amount_')).attr("disabled","disabled");
            $('#' + currId.replace('add_', 'add_amount_')).css("background-color", "#cccccc");

        }
    });

    $(".crew_total_add_check").click(function(){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){
            $('#' + currId.replace('add_', 'add_amount_')).removeAttr("disabled");
            $('#' + currId.replace('add_', 'add_amount_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('add_', 'add_amount_')).attr("disabled","disabled");
            $('#' + currId.replace('add_', 'add_amount_')).css("background-color", "#cccccc");
        }
    });

    //Crew total reduce check
    $(".crew_total_reduce_check").each(function(index){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){
            $('#' + currId.replace('reduce_', 'reduce_amount_')).removeAttr("disabled");
            $('#' + currId.replace('reduce_', 'reduce_amount_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('reduce_', 'reduce_amount_')).attr("disabled","disabled");
            $('#' + currId.replace('reduce_', 'reduce_amount_')).css("background-color", "#cccccc");

        }
    });

    $(".crew_total_reduce_check").click(function(){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){
            $('#' + currId.replace('reduce_', 'reduce_amount_')).removeAttr("disabled");
            $('#' + currId.replace('reduce_', 'reduce_amount_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('reduce_', 'reduce_amount_')).attr("disabled","disabled");
            $('#' + currId.replace('reduce_', 'reduce_amount_')).css("background-color", "#cccccc");
        }
    });

    //Client total add check
    $(".client_total_add_check").each(function(index){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){
            $('#' + currId.replace('add_', 'add_amount_')).removeAttr("disabled");
            $('#' + currId.replace('add_', 'add_amount_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('add_', 'add_amount_')).attr("disabled","disabled");
            $('#' + currId.replace('add_', 'add_amount_')).css("background-color", "#cccccc");

        }
    });

    $(".client_total_add_check").click(function(){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){
            $('#' + currId.replace('add_', 'add_amount_')).removeAttr("disabled");
            $('#' + currId.replace('add_', 'add_amount_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('add_', 'add_amount_')).attr("disabled","disabled");
            $('#' + currId.replace('add_', 'add_amount_')).css("background-color", "#cccccc");
        }
    });

    //Client total reduce check
    $(".client_total_reduce_check").each(function(index){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){
            $('#' + currId.replace('reduce_', 'reduce_amount_')).removeAttr("disabled");
            $('#' + currId.replace('reduce_', 'reduce_amount_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('reduce_', 'reduce_amount_')).attr("disabled","disabled");
            $('#' + currId.replace('reduce_', 'reduce_amount_')).css("background-color", "#cccccc");

        }
    });

    $(".client_total_reduce_check").click(function(){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){
            $('#' + currId.replace('reduce_', 'reduce_amount_')).removeAttr("disabled");
            $('#' + currId.replace('reduce_', 'reduce_amount_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('reduce_', 'reduce_amount_')).attr("disabled","disabled");
            $('#' + currId.replace('reduce_', 'reduce_amount_')).css("background-color", "#cccccc");
        }
    });


    $('.tr_crew_of').bind("propertychange input paste", function() {
        var currId = $(this).attr('id');
        var rivalId = currId.replace('_of_', '_ph_');
        if($('#'+ rivalId).val().length != 0 && $(this).val().length != 0)
        {
            alert("Cannot write both of ph and client!");
            $(this).val('');

        }
    });

    $('.tr_client_of').bind("propertychange input paste", function()  {
        var currId = $(this).attr('id');
        var rivalId = currId.replace('_of_', '_ph_');
        if($('#'+ rivalId).val().length != 0 && $(this).val().length != 0)
        {
            alert("Cannot write both of ph and client!");
            $(this).val('');

        }
    });
    $('.tr_crew_ph').bind("propertychange input paste", function()  {
        var currId = $(this).attr('id');
        var rivalId = currId.replace('_ph_', '_of_');
        if($('#'+ rivalId).val().length != 0 && $(this).val().length != 0)
        {
            alert("Cannot write both of ph and client!");
            $(this).val('');

        }
    });
    $('.tr_client_ph').bind("propertychange input paste", function()  {
        var currId = $(this).attr('id');
        var rivalId = currId.replace('_ph_', '_of_');
        if($('#'+ rivalId).val().length != 0 && $(this).val().length != 0)
        {
            alert("Cannot write both of ph and client!");
            $(this).val('');

        }
    });
    $(".tr_check").click(function(){
        var currId = $(this).attr('id');
        if($(this).is(":checked")){

            $('#' + currId.replace('_use_', '_crew_ph_')).removeAttr("disabled");
            $('#' + currId.replace('_use_', '_crew_of_')).removeAttr("disabled");
            $('#' + currId.replace('_use_', '_client_ph_')).removeAttr("disabled");
            $('#' + currId.replace('_use_', '_client_of_')).removeAttr("disabled");
            $('#' + currId.replace('_use_', '_comment_')).removeAttr("disabled");

            $('#' + currId.replace('_use_', '_crew_ph_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_crew_of_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_client_ph_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_client_of_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_comment_')).css("background-color", "white");
        }
        else{
            $('#' + currId.replace('_use_', '_crew_ph_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_crew_of_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_client_ph_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_client_of_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_comment_')).attr("disabled","disabled");

            $('#' + currId.replace('_use_', '_crew_ph_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_crew_of_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_client_ph_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_client_of_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_comment_')).css("background-color", "#cccccc");
            /*
             $('#' + currId.replace('_use_', '_crew_ph_'))attr("disabled","disabled");
             $('#' + currId.replace('_use_', '_crew_of_'))attr("disabled","disabled");
             $('#' + currId.replace('_use_', '_client_ph_'))attr("disabled","disabled");
             $('#' + currId.replace('_use_', '_client_of_'))attr("disabled","disabled");

             $('#' + currId.replace('_use_', '_crew_ph_')).css("background-color", "#ffff00");
             $('#' + currId.replace('_use_', '_crew_of_')).css("background-color", "#ffff00");
             $('#' + currId.replace('_use_', '_client_ph_')).css("background-color", "#ffff00");
             $('#' + currId.replace('_use_', '_client_of_')).css("background-color", "#ffff00");
             */
        }
    });

    $('#accordion label, input[type="checkbox"]').click(function(e) {
        e.stopPropagation();
    });

    //If standard crew is unticked, than untick/disable any supplements allocated for
    //that crew member
    /*
    $(".crew_check").each(function(index){
        var currId = $(this).attr('id');
        if(!$(this).is(":checked")){

            var inputs = $(this).closest('h3').next().find('.tr_contents').eq(0).find('input');

            //Disable all inputs
            inputs.attr("disabled","disabled");
            inputs.css("background-color", "#cccccc");
            //Untick all ticket supplements
            $(inputs).each(function(index,elem) {
                if($(elem).is(':checkbox')) {
                    $(elem).removeAttr("checked");
                }
            });
        }
    });


    $(".crew_check").click(function(index){
        var currId = $(this).attr('id'),
            inputs = $(this).closest('h3').next().find('.tr_contents').eq(0).find('input');
        if($(this).is(":checked")){
            //Enable all inputs
            $(inputs).each(function(index,elem) {
                if($(elem).is(':checkbox')) {
                    $(elem).removeAttr("disabled");
                }
            });
        } else {
            //Disable all inputs
            inputs.attr("disabled","disabled");
            inputs.css("background-color", "#cccccc");
            $(inputs).each(function(index,elem) {
                if($(elem).is(':checkbox')) {
                    $(elem).removeAttr("checked");
                }
            });
        }
    });
    */


    /*
     function checkTextboxChanged() {
     var currentValue = $(\'#yourTextboxId\').val();
     if (currentValue != searchValue) {
     searchValue = currentValue;
     TextboxChanged();
     }
     }

     function TextboxChanged() {
     // do your magic here
     }


     $('.tr_crew_of').change(function(){
     var currId = $(this).attr('id');
     var rivalId = currId.replace('_of_', '_ph_');
     if($('#'+ rivalId).val().length != 0)
     {
     //$('#supp_crew_of_122_647').text('');
     // $('#'+ currId).text('');
     alert("Cannot write both of ph and client!");
     $(this).text('');
     }
     });
     */
    /*
     setInterval(function() {
     // Do something every 2 seconds

     // alert($(this).attr("id") + " has focus!");
     var currElement = $(':focus');
     var currId = currElement.attr('id');
     if(currId.search("tr_crew_") != -1 ||
     currId.search("tr_client_") != -1)
     {
     alert("21323");
     var rivalId = currId.replace('_ph_', '_of_');
     if($('#'+ rivalId).val().length != 0 && currElement.val().length != 0)
     {
     alert("Cannot write both of ph and of!");
     currElement.val('');
     }
     }
     }, 100);
     $(":focus").each(function() {
     alert($(this).attr("id") + " has focus!");
     }); */


    /* $('#supp_use_122_647').mousedown(function() {
     alert("dfads");
     var currId = $(this).attr(id);
     if($(this).is(:checked)){
     $('#' + currId.replace('_use_', '_crew_ph_')).prop("disabled", false);
     $('#' + currId.replace('_use_', '_crew_of_')).prop("disabled", false);
     $('#' + currId.replace('_use_', '_client_ph_')).prop("disabled", false);
     $('#' + currId.replace('_use_', '_client_of_')).prop("disabled", false);
     }
     else{
     $('#' + currId.replace('_use_', '_crew_ph_')).prop("disabled", true);
     $('#' + currId.replace('_use_', '_crew_of_')).prop("disabled", true);
     $('#' + currId.replace('_use_', '_client_ph_')).prop("disabled", true);
     $('#' + currId.replace('_use_', '_client_of_')).prop("disabled", true);
     }
     }); */
});
