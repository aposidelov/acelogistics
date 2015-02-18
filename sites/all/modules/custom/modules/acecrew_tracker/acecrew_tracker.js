
AcecrewTracker = {
    init: function( options ) {
        var self = this;
        
    },

    bindDateFilter: function () {

        if (!$("#edit-filter-by-date").is(':checked')) {            
            $('.container-inline-date').hide();            
        }
        $("#edit-filter-by-date").change(function() {
            $('.container-inline-date').toggle();
        });
    }
};

$(document).ready(function() {
    var o = AcecrewTracker;
    o.init();    
    o.bindDateFilter();
});

