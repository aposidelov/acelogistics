AcecrewNoshow = {
    init: function( options ) {
        var self = this;
        $("#edit-timesheets-crews-active-wrapper, #edit-timesheets-crews-inactive-wrapper").hide();
    },    
    bindDateFilter: function () {
        if (!$("#edit-timesheets-filter-by-date").is(':checked')) {
            $('.container-inline-date').hide();
        }
        $("#edit-timesheets-filter-by-date").change(function() {
            $('.container-inline-date').toggle();
        });
    }
};

$(document).ready(function() {
    var o = AcecrewNoshow;
    o.init();    
    o.bindDateFilter();
});

