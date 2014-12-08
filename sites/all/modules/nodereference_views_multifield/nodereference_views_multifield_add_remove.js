$(document).ready(function() {
	// transform any add/remove widgets from tables (i.e., how they're rendered in PHP, and how the form data is submitted) into add/remove widgets
	$('fieldset.nodereference-views-multifield-add-remove').each( function() {
		var table = $(this).children('table');
		table.hide();

		var availableItems = $(this).append("<div style='float: left;'><label>Available Items</label><br /><input type='text' id='nodereference-views-multifield-available-search' autocomplete='off' /><br /><select style='height: 12em; width: 17em' class='nodereference-views-multifield-available' multiple='multiple'></select></div>");
		var availableItemsSelect = availableItems.find('select.nodereference-views-multifield-available');

		$(this).append("<div style='float: left; margin: 2em;'><button id='nodereference-views-multifield-add-item'>Add Item -&gt;</button><br /><button id='nodereference-views-multifield-remove-item'>&lt;- Remove Item</button></div>");

		var selectedItems = $(this).append("<div style='float: left;'><label>Selected Items</label><br /><select style='margin-top: 1.7em; height: 12em; width: 17em' class='nodereference-views-multifield-selected' multiple='multiple'></select></div>");
		var selectedItemsSelect = selectedItems.find('select.nodereference-views-multifield-selected');

		table.find('tbody tr').each( function() {
			var nid = $(this).find('input.nodereference-views-multifield-nid').val();
			var title = $(this).text();

			if(!$(this).find('input[type=checkbox]').attr('checked'))
				availableItemsSelect.append("<option value='"+nid+"'>"+title+"</option>");
			else
				selectedItemsSelect.append("<option value='"+nid+"'>"+title+"</option>");
		});
	});

	$('#nodereference-views-multifield-available-search').keyup(function() {
		var availableWidget = $(this).parent('div').find('select.nodereference-views-multifield-available');
		var searchText = $(this).val().toLowerCase();

		// Setting the 'display' attribute only works in Firefox (not IE or WebKit-based browsers)
		// $(this).css('display', matched?'block':'none');
		// so instead we have to actually remove options from the list.

		availableWidget.empty();
		var table = $(this).parent('div').parent('fieldset');
		table.find('tbody tr').each( function() {
			var nid = $(this).find('input.nodereference-views-multifield-nid').val();
			var title = $(this).text();

			var matched = title.toLowerCase().indexOf(searchText)>=0;

			if (matched && !$(this).find('input[type=checkbox]').attr('checked'))
				availableWidget.append("<option value='"+nid+"'>"+title+"</option>");
		});
	});

	$('#nodereference-views-multifield-add-item').click(function() {
		var table = $(this).parent('div').parent('fieldset');
		var availableWidget = $(this).parent('div').parent('fieldset').find('select.nodereference-views-multifield-available');
		var selectedWidget = $(this).parent('div').parent('fieldset').find('select.nodereference-views-multifield-selected');
	
		availableWidget.find('option:selected').each( function() {
			// mark the checkbox in the hidden table (this is what's actually submitted back to Drupal)
			var hiddenNidWidget = table.find('tbody tr input.nodereference-views-multifield-nid[value='+$(this).val()+']');
			hiddenNidWidget.parent('td').parent('tr').find('input[type=checkbox]').attr('checked', 'checked');

			// add it to Selected Items...
			selectedWidget.append("<option value='"+$(this).val()+"'>"+$(this).text()+"</option>");
			// ...and remove it from Available Items
			$(this).remove();
		});
	
		return false;
	});

	$('#nodereference-views-multifield-remove-item').click(function() {
		var table = $(this).parent('div').parent('fieldset');
		var availableWidget = $(this).parent('div').parent('fieldset').find('select.nodereference-views-multifield-available');
		var selectedWidget = $(this).parent('div').parent('fieldset').find('select.nodereference-views-multifield-selected');
	
		selectedWidget.find('option:selected').each( function() {
			// clear the checkbox in the hidden table (this is what's actually submitted back to Drupal)
			var hiddenNidWidget = table.find('tbody tr input.nodereference-views-multifield-nid[value='+$(this).val()+']');
			hiddenNidWidget.parent('td').parent('tr').find('input[type=checkbox]').attr('checked', '');

			// add it to Available Items...
			availableWidget.append("<option value='"+$(this).val()+"'>"+$(this).text()+"</option>");
			// ...and remove it from Selected Items
			$(this).remove();
		});
	
		return false;
	});
});

