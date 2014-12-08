<?php
print drupal_render($form); ?>
<!-- add by andrey -->
<script type="text/javascript">
    $("#edit-field-supp-per-hour-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-single-payment-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field!");
            $(this).val('');
            $(this).text('');
        }
    });

    $("#edit-field-supp-single-payment-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-per-hour-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field!!!");
            $(this).val('');
            $(this).text('');
        }
    });


    $(".node-type-supplements #node-form").submit(function(e) {

        var error = false;

        //Check if required fields are set, if not display message on submission
        if ($("#edit-field-supp-0to4-client-hour-0-value").val() == '' && $("#edit-field-supp-0to4-client-single-0-value").val() == '') {
            alert("Please set 0 - 4 Hours Defaults for Client");
            error = true;
        }
        else if ($("#edit-field-supp-0to4-crew-hour-0-value").val() == '' && $("#edit-field-supp-0to4-crew-single-0-value").val() == '') {
            alert("Please set 0 - 4 Hours Defaults for Crew");
            error = true;
        }
        else if ($("#edit-field-supp-5to8-client-hour-0-value").val() == '' && $("#edit-field-supp-5to8-client-single-0-value").val() == '') {
            alert("Please set 5 - 8 Hours Defaults for Client");
            error = true;
        }
        else if ($("#edit-field-supp-5to8-crew-hour-0-value").val() == '' && $("#edit-field-supp-5to8-crew-single-0-value").val() == '') {
            alert("Please set 5 - 8 Hours Defaults for Crew");
            error = true;
        }
        else if ($("#edit-field-supp-9to12-client-hour-0-value").val() == '' && $("#edit-field-supp-9to12-client-single-0-value").val() == '') {
            alert("Please set 9 - 12 Hours Defaults for Client");
            error = true;
        }
        else if ($("#edit-field-supp-9to12-crew-hour-0-value").val() == '' && $("#edit-field-supp-9to12-crew-single-0-value").val() == '') {
            alert("Please set 9 - 12 Hours Defaults for Crew");
        }
        else if ($("#edit-field-supp-12plus-client-hour-0-value").val() == '' && $("#edit-field-supp-12plus-client-single-0-value").val() == '') {
            alert("Please set 12 + Hours Defaults for Client");
            error = true;
        }
        else if ($("#edit-field-supp-12plus-crew-hour-0-value").val() == '' && $("#edit-field-supp-12plus-crew-single-0-value").val() == '') {
            alert("Please set 12 + Hours Defaults for Crew");
            error = true;
        }

        if(error) {
            return false;
        } else {
            return true;
        }

    });

    /* 0 - 4 */
    //Client
    $("#edit-field-supp-0to4-client-hour-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-0to4-client-single-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    $("#edit-field-supp-0to4-client-single-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-0to4-client-hour-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    //Crew
    $("#edit-field-supp-0to4-crew-hour-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-0to4-crew-single-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field from Client!");
            $(this).val('');
            $(this).text('');
        }
    });

    $("#edit-field-supp-0to4-crew-single-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-0to4-crew-hour-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field!!!");
            $(this).val('');
            $(this).text('');
        }
    });

    /* 5 - 8 */
    //Client
    $("#edit-field-supp-5to8-client-hour-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-5to8-client-single-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    $("#edit-field-supp-5to8-client-single-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-5to8-client-hour-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    //Crew
    $("#edit-field-supp-5to8-crew-hour-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-5to8-crew-single-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    $("#edit-field-supp-5to8-crew-single-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-5to8-crew-hour-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    /* 9 - 12 */
    //Client
    $("#edit-field-supp-9to12-client-hour-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-9to12-client-single-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    $("#edit-field-supp-9to12-client-single-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-9to12-client-hour-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    //Crew
    $("#edit-field-supp-9to12-crew-hour-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-9to12-crew-single-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    $("#edit-field-supp-9to12-crew-single-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-9to12-crew-hour-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    /* 12 +  */
    //Client
    $("#edit-field-supp-12plus-client-hour-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-12plus-client-single-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    $("#edit-field-supp-12plus-client-single-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-12plus-client-hour-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    //Crew
    $("#edit-field-supp-12plus-crew-hour-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-12plus-crew-single-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

    $("#edit-field-supp-12plus-crew-single-0-value").bind("paste keyup", function() {
        if($("#edit-field-supp-12plus-crew-hour-0-value").val() != '')
        {
            alert("Cannot put values to both of per hour and amount field.");
            $(this).val('');
            $(this).text('');
        }
    });

</script>