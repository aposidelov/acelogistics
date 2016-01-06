jQuery(document).ready(function() {    
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

            /*$('#' + currId.replace('_use_', '_crew_ph_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_crew_of_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_client_ph_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_client_of_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_comment_')).css("background-color", "white");*/
        }
        else{
            $('#' + currId.replace('_use_', '_crew_ph_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_crew_of_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_client_ph_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_client_of_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_comment_')).attr("disabled","disabled");

            /*$('#' + currId.replace('_use_', '_crew_ph_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_crew_of_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_client_ph_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_client_of_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_comment_')).css("background-color", "#cccccc");*/
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
    $('.tr_client_ph').bind("propertychange input paste", function() {
        var currId = $(this).attr('id');
        var rivalId = currId.replace('_ph_', '_of_');
        if($('#'+ rivalId).val().length != 0 && $(this).val().length != 0)
        {
            alert("Cannot write both of ph and client!");
            $(this).val('');

        }
    });
    $(".tr_check").click(function() {    
        var checkboxInput   = $(this);
        var currId          = checkboxInput.attr('id');
        var crewPH          = $('#' + currId.replace('_use_', '_crew_ph_'));
        var crewOF          = $('#' + currId.replace('_use_', '_crew_of_'));
        var clientPH        = $('#' + currId.replace('_use_', '_client_ph_'));
        var clientOF        = $('#' + currId.replace('_use_', '_client_of_'));
        var comment         = $('#' + currId.replace('_use_', '_comment_'));

        if ($(this).is(":checked")) {
            var crewId = $(this).attr('data-uid');                        
            var additionalHours = $('#additional_hours_' + crewId).val();
            // refresh data after enabling supplement checkbox
            supplementRowRefresh(checkboxInput, additionalHours);
            

            crewPH.removeAttr("disabled");
            crewOF.removeAttr("disabled");
            clientPH.removeAttr("disabled");
            clientOF.removeAttr("disabled");
            comment.removeAttr("disabled");

            /*$('#' + currId.replace('_use_', '_crew_ph_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_crew_of_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_client_ph_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_client_of_')).css("background-color", "white");
            $('#' + currId.replace('_use_', '_comment_')).css("background-color", "white");*/
        } else {

            crewPH.attr("disabled","disabled");
            crewOF.attr("disabled","disabled");
            clientPH.attr("disabled","disabled");
            clientOF.attr("disabled","disabled");
            comment.attr("disabled","disabled");

            /*$('#' + currId.replace('_use_', '_crew_ph_')).attr("disabled","disabled"); // .val('')
            $('#' + currId.replace('_use_', '_crew_of_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_client_ph_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_client_of_')).attr("disabled","disabled");
            $('#' + currId.replace('_use_', '_comment_')).attr("disabled","disabled");*/

            /*
            $('#' + currId.replace('_use_', '_crew_ph_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_crew_of_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_client_ph_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_client_of_')).css("background-color", "#cccccc");
            $('#' + currId.replace('_use_', '_comment_')).css("background-color", "#cccccc");            
            */
        }
    });

    $('#accordion label, input[type="checkbox"]').click(function(e) {
        e.stopPropagation();
    });

    $('.additional_hours > input').keyup(function() {
        // pass additional hours to Refresh Supplement Row function
        var hrs = parseInt($(this).val());
        var crewId = $(this).attr('data-uid');
        var supplementRowSelector = 'input[name*="supp_use_' + crewId + '"]';

        if (confirm("Would you like to refresh supplement values?")) {
            delay(function() {
                if (isInt(hrs)) {    
                    // go through each supplement row      
                    // all supplements of current crew
                    $(supplementRowSelector).each(function() {
                        var checkboxInput = $(this);
                        // check what supplements are checked
                        if (checkboxInput.is(":checked")) {  
                            // refresh data for checked supplements          
                            supplementRowRefresh(checkboxInput, hrs, true);
                        }
                    }); 
                }            
            }, 1000 );        
        }
    });

    function supplementRowRefresh(checkboxInput, additionalHours, rewrite) {
        rewrite = rewrite || false;

        var currId      = checkboxInput.attr('id');
        var crewPH     = $('#' + currId.replace('_use_', '_crew_ph_'));
        var crewOF     = $('#' + currId.replace('_use_', '_crew_of_'));
        var clientPH   = $('#' + currId.replace('_use_', '_client_ph_'));
        var clientOF   = $('#' + currId.replace('_use_', '_client_of_'));
        var comment     = $('#' + currId.replace('_use_', '_comment_'));

        var supplementId = currId.split('_')[3];
        var callHours = Drupal.settings.callHours;
                
        var totalHours = parseInt(callHours) + parseInt(additionalHours);        
        //
        if (rewrite) {
            crewPH.val('');
            crewOF.val('');
            clientPH.val('');
            clientOF.val('');
        }

        if ((crewPH.val() == '' && crewOF.val() == '') ||
            (clientPH.val() == '' && clientOF.val() == '')) {
            
            $.getJSON('/admin/ajax/supplement/' + supplementId +'/'+ totalHours, 
                function(data) {                        
                    if (data.crewType !== '' && data.clientType !== '') {                                         
                        var tr = checkboxInput.parent().parent().parent();                        

                        if (crewPH.val() == '' && crewOF.val() == '') {
                            tr.find('.tr_crew_' + data.crewType).val(data.crewValue);
                        }

                        if (clientPH.val() == '' && clientOF.val() == '') {
                            tr.find('.tr_client_' + data.clientType).val(data.clientValue);
                        }
                    }
                }
            );
                            
        } 
    }

    var delay = (function(){
        var timer = 0;
        return function(callback, ms){
            clearTimeout (timer);
            timer = setTimeout(callback, ms);
        };
    })();

    function isInt(n) {
        return +n === n && !(n % 1);
    }
});
