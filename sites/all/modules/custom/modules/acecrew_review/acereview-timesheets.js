
AcecrewTimesheetsObject = {
    init: function( options ) {
        var self = this;
        $("#edit-timesheets-crews-active-wrapper, #edit-timesheets-crews-inactive-wrapper").hide();
    },
    bindRadiobuttons: function () {
        var select_all = 1,
        select_active = 2,
        select_inactive = 3;
        $('#acecrew-review-report-spreadsheet input:radio').change(function() {
            if ( $(this).val() == select_all ) {
                //$("#acecrew-review-report-spreadsheet option:selected").removeAttr("selected");
                $("#edit-timesheets-crews-wrapper").show();
                $("#edit-timesheets-crews-active-wrapper, #edit-timesheets-crews-inactive-wrapper").hide();
            }
            if ( $(this).val() == select_active ) {
                //$("#acecrew-review-report-spreadsheet option:selected").removeAttr("selected");
                $("#edit-timesheets-crews-active-wrapper").show();
                $("#edit-timesheets-crews-wrapper, #edit-timesheets-crews-inactive-wrapper").hide();
            }
            if ( $(this).val() == select_inactive ) {
                //$("#acecrew-review-report-spreadsheet option:selected").removeAttr("selected");
                $("#edit-timesheets-crews-inactive-wrapper").show();
                $("#edit-timesheets-crews-wrapper, #edit-timesheets-crews-active-wrapper").hide();
            }
        });
        $("#acecrew-review-report-spreadsheet input:radio:checked").trigger('change');
    },
    bindDateFilter: function () {
        if (!$("#edit-timesheets-filter-by-date").is(':checked')) {
            $('.container-inline-date').hide();
        }
        $("#edit-timesheets-filter-by-date").change(function() {
            $('.container-inline-date').toggle();
        });
    }
}

$(document).ready(function() {
    var o = AcecrewTimesheetsObject;
    o.init();
    o.bindRadiobuttons();
    o.bindDateFilter();
});

