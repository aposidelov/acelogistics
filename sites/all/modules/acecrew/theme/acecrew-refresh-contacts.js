/**
 * Update client contacts on the job/call form.
 * @param {numeric or string} client        jobNid or Client name
 * @param {object} contactFirstSelector     jQuery object of first contact field
 * @param {object} contactSecondSelector    jQuery object of second contact field 
 * @param {object} $loader                  jQuery object of a load message 
 * @param {boolean} noRefresh               no need to refresh even if contacts are same
 * @param {function} sameContactCallback    same Contact callback
 * @param {function} diffContactCallback    different Contact callback
 */
function acecrew_refresh_contacts(client, contactFirstSelector, contactSecondSelector, $loader, noRefresh, sameContactCallback, diffContactCallback) {
    //$.blockUI();
    $loader.html('<h4>Check if client contacts were updated...<span class="views-throbbing">&nbsp;</span></h4>');
    $.getJSON('/admin/ajax/client-get-contacts/' + client, function(data) {
        var oldContacts = {};
        //var contactFirstSelector = '#edit-field-job-client-contact-value';
        //var contactSecondSelector = '#edit-field-job-client-contact-second-value';
        $(contactFirstSelector + ' option').each(function() {
            var self = $(this);
            var value = self.val();            
            oldContacts['' + self.val()] = self.text();                        
        });                            
        var updatedContacts = data.updatedContacts;
        console.log('oldContacts', oldContacts);
        console.log('updatedContacts', updatedContacts);
        if (!noRefresh && JSON.stringify(oldContacts) === JSON.stringify(updatedContacts)) {
            console.log('same');
            if (sameContactCallback && typeof(sameContactCallback) === "function") {
                sameContactCallback();
            }            
            return true;
        }

        // get old selected value of contact
        var contactFirstValueOld = $(contactFirstSelector + ' option:selected').text();                                                                                    
        // populate contact select with new data
        var contactsList = $(contactFirstSelector);
        contactsList.html('');
        $.each(updatedContacts, function(index, value) {
            if (value === contactFirstValueOld) {                                    
                contactsList.append($("<option />").val(index).text(value).attr('selected', 'selected'));                                    
            } else {
                contactsList.append($("<option />").val(index).text(value));
            }
        });
        var contactFirstValueNew = $(contactFirstSelector + ' option:selected').text();

        // update second contact field
        contactsListSecond = $(contactSecondSelector);
        contactSecondValueOld = contactsListSecond.find('option:selected').text();
        contactsListSecond.html('');
        if (contactSecondValueOld === '') {
            contactsListSecond.append($("<option />").val('').text('- None -').attr('selected', 'selected'));
        } else {
            contactsListSecond.append($("<option />").val('').text('- None -'));    
        }                            
        $.each(updatedContacts, function(index, value) {
            if (value === contactSecondValueOld) {                                    
                contactsListSecond.append($("<option />").val(index).text(value).attr('selected', 'selected'));                                    
            } else {
                contactsListSecond.append($("<option />").val(index).text(value));
            }
        });
        var contactSecondValueNew = contactsListSecond.find('option:selected').text();
        var message = 'Client contacts have been updated. Please check if contacts have been setup correctly and sumbit a form again.';
        if (contactFirstValueOld === contactFirstValueNew) {
            //message += '\nClient contact: ' + contactFirstValueNew;
        } else {
            message += '\nClient contact: ' + contactFirstValueOld + ' was changed - select a new one';
        }
        if (contactSecondValueOld === contactSecondValueNew) {
            //message += '\nClient contact second: ' + contactSecondValueNew;
        } else {
            message += '\nClient contact second: ' + contactSecondValueOld + ' was changed - select a new one';
        }
        $loader.html('');
        $.unblockUI();                            
        alert(message);
        if (diffContactCallback && typeof(diffContactCallback) === "function") {
            diffContactCallback();
        }
        return true;     
    });
}

