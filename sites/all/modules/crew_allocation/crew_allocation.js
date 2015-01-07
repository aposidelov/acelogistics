/*function onSubmitCallbackExample()
 {
 alert("Ya!!");
 $("#acecrew_calendar_output", window.parent.document).html('<img class="loading-gif" src="/site/all/modules/acecrew/theme/ajax-loader.gif" />');
 forward = $('#acecrew_calendar_forward_days', window.parent.document).val();
 $.get(Drupal.settings.basePath + "acecrew/calendar/" + $('#edit-date-timer-datepicker-popup-0', window.parent.document).val() + "/" + forward, function(data){
 var result = Drupal.parseJson(data);
 $("#acecrew_calendar_output", window.parent.document).html(result.html);
 window.close();
 });
 <<<<<<< HEAD
 }
 =======
 }


 >>>>>>> 242e667f3d6ec9d3e101990fba6141dc88a4bb5c
 */
//jQuery(document).ready(function(){
//      var totalCount = $('#crew_number_hidden').val();
//      var checkedItemCount = 0;
//
//      $('.form-checkbox').click (function ()
//      {
//        if($(this).is(":checked"))
//        {
//        // Do stuff
//            checkedItemCount = 0;
//            $('.form-checkbox').each(function(index) {
//                if($(this).is(":checked")){
//                    checkedItemCount++;
//                }
//            });
//            if(checkedItemCount > totalCount)
//            {
//                 alert("You can select only " + totalCount + " crews or less for this call.");
//                 $(this).attr('checked', false);
//            }
//        }
//      });
//
//});

jQuery(document).ready(function() {    
    $("#-crew-allocation-top-form .form-checkbox").click(function() {
        if (!$(this).is(":checked")) {
            var group = this.name;            
            $('input:checkbox[name="'+ group + '"][checked]').attr('checked', false);
        } else {            
            var call_vid = Drupal.settings.call_vid;
            var crew_id = $(this).attr('id').substring(5);
            var crew_name = this.name;            
            /*
            $.ajax({
                url: '/admin/ajax/client-call-crew-is-blocked/' + call_vid + '/' + crew_id,
                async: false,
                type: 'jsonp',
                success: function(data) {
                    if (data.is_blocked) {
                        var client_name = Drupal.settings.client_name;
                        alert('"{0}" crew is blocked for "{1}" client!'.format(crew_name, client_name));                                                     
                    }
                }
            });
            $.ajax({
                url: '/admin/ajax/venue-call-crew-is-blocked/' + call_vid + '/' + crew_id,
                async: false,
                type: 'jsonp',
                success: function(data) {
                    if (data.is_blocked) {
                        var venue_name = Drupal.settings.venue_name;
                        alert('"{0}" crew is blocked for "{1}" venue!'.format(crew_name, venue_name));
                    }
                }
            });   
            */
            
            $.getJSON('/admin/ajax/client-call-crew-is-blocked/' + call_vid + '/' + crew_id, function(data) {
                if (!data.is_blocked) {
                    var client_name = Drupal.settings.client_name;

                    alert('"{0}" crew is blocked for "{1}" client!'.format(crew_name, client_name));                    
                }
            }); 

            $.getJSON('/admin/ajax/venue-call-crew-is-blocked/' + call_vid + '/' + crew_id, function(data) {
                if (!data.is_blocked) {
                    var venue_name = Drupal.settings.venue_name;

                    alert('"{0}" crew is blocked for "{1}" venue!'.format(crew_name, venue_name));                    
                }
            }); 

            /*
            
            */ 
        }                           
    });


    $("#-crew-allocation-top-form").submit(function(event) {

        var totalCount = $('#crew_number_hidden').val(),
            checkedItemCount = 0,
            selected_crew_names = [];

        $('.form-checkbox').each(function(index) {
            if($(this).is(":checked")){

                //Crew member name can appear in available and also in unavailable 120-61 group
                //To make sure we do not check the same member twice, we first check if name
                //is not already in our selected_crew_name list
                if($.inArray($(this).parent().text(), selected_crew_names) == -1) {
                    selected_crew_names.push($(this).parent().text());
                    checkedItemCount++;
                }


            }
        });

        if(checkedItemCount > totalCount) {
            /*
             alert("The call only required " + totalCount +" crew member" + (totalCount > 1 ? "s" : "") +
             " - you have currently allocated " + checkedItemCount +  " crew members.");
             */

            var result = confirm("The call only required " + totalCount +" crew member" + (totalCount > 1 ? "s" : "") +
                " - you have currently allocated " + checkedItemCount +  " crew members.");
            if (result == true) {
                return true;
            } else {
                return false;
            }


        }

    })
})

// First, checks if it isn't implemented yet.
if (!String.prototype.format) {
  String.prototype.format = function() {
    var args = arguments;
    return this.replace(/{(\d+)}/g, function(match, number) { 
      return typeof args[number] != 'undefined'
        ? args[number]
        : match
      ;
    });
  };
}