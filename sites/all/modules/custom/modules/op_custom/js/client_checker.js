$(document).ready(function() {
    $('#edit-save-call').click(function() {
        console.log('checking');

        console.log(Drupal.settings.jobNid);

        var intervalId = setInterval(function() {
            $.getJSON('/admin/ajax/client-is-editing/' + Drupal.settings.jobNid, function(data) {
                if (data.isClientEditing) {
                    console.log('editing');
                    return false;
                } else {
                    clearInterval(intervalId);
                    console.log('edited');
                    $('#edit-save-call').submit();
                    return true;
                }
            });

        }, 3000);

        return false;
    });    
});