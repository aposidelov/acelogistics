
jQuery(document).ready(function() {    
    $("#-crew-allocation-top-form .form-checkbox").click(function() {
        if (!$(this).is(":checked")) {
            var group = this.name;            
            $('input:checkbox[name="'+ group + '"][checked]').attr('checked', false);
        } else {            
            var call_vid = Drupal.settings.call_vid;
            var crew_id = $(this).attr('id').substring(5);
            var crew_name = this.name;                        
            
            $.getJSON('/admin/ajax/client-call-crew-is-blocked/' + call_vid + '/' + crew_id, function(data) {
                if (!data.is_blocked) {
                    var client_name = Drupal.settings.client_name;

                    alert('"{0}" crew has been blocked for "{1}" client!'.format(crew_name, client_name));                    
                }
            }); 

            $.getJSON('/admin/ajax/venue-call-crew-is-blocked/' + call_vid + '/' + crew_id, function(data) {
                if (!data.is_blocked) {
                    var venue_name = Drupal.settings.venue_name;

                    alert('"{0}" crew has been blocked for "{1}" venue!'.format(crew_name, venue_name));                    
                }
            }); 
        }                           
    });

    $("#-crew-allocation-top-form").submit(function(event) {
        var totalCount = $('#crew_number_hidden').val(),
            checkedItemCount = 0,
            selected_crew_names = [];
        $('.form-checkbox').each(function(index) {
            if ($(this).is(":checked")){

                //Crew member name can appear in available and also in unavailable 120-61 group
                //To make sure we do not check the same member twice, we first check if name
                //is not already in our selected_crew_name list
                if ($.inArray($(this).parent().text(), selected_crew_names) == -1) {
                    selected_crew_names.push($(this).parent().text());
                    checkedItemCount++;
                }
            }
        });

        if (checkedItemCount > totalCount) {            
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