Extend form elements checkboxes & radios to display in multi-column

CCK support:
-----------
Multicolumn option settings is in the CCK field, content taxonomy or nodereference
 field configuration screen if they use the check boxes/radio buttons widget.

More CCK widget type can be added in your site's settings.php.

  $conf['multicolumncheckboxesradios_extra_widget_types'] = array('some_cck_widget_type');


Webforms Usage:
--------------
See http://drupal.org/project/multicolumncheckboxesradios


Code Usage:
----------
A new property '#multicolumn' can be specified to make checkboxes and radios
display in columns. This property takes an array:

  'width' => number           (required): the number of column desired
  'minimum height' => number  (optional): make sure columns are not shorter than this
  'row-major' => TRUE         (optional): go across the screen first, then down

In the definition of form element checkboxes/radios, add the '#multicolumn' property:
 
  $form['multicolumn_checkboxes'] = array(
   '#type' => 'checkboxes',
   '#multicolumn' => array('width' => 3),
     .
     .
     .
  );

or

  $form['multicolumn_checkboxes'] = array(
   '#type' => 'checkboxes',
   '#multicolumn' => array('width' => 5, 'row-major' => TRUE),
     .
     .
     .
  );

  
Example:
  
5 checkboxes, set '#multicolumn' => array('width' => 3), it will be
shown in 3 columns:
 
       A    C   E
       B    D
 
set '#multicolumn' => array('width' => 3, 'row-major' => TRUE), it will be

       A    B    C
       D    E

with '#multicolumn' => array('width' => 3, 'minimum height' => 4), it will be adjusted to:
 
       A    E
       B
       C
       D
       
In raw-major display, 'minimum height' cannnot always be satisfied. Like in the example
above, it will *not* be displayed this way:

       A    B
       C
       D
       E
       
It wil be displayed this way:

       A    B
       C    D
       E
         
it basically tried to maixmize the column height to the minimum but keep the row filled first.

WARNING: because row-major display is done by re-arranging the checkbox children elements, the
$form_state['values'][] array will not be in the same order as the '#options' array. If you want
to fetch checkbox state in the original '#options' order, iterate the $form_state['values'][]
array using the keys from '#options' array.

This will also mess up jQuery shift-click checkbox if you use that to let user check
a range of check: it will not behave the you you expect in row-major layout because
it's only visually in row-major, the HTML markup is actually contain in column-major.

This reason this is done so is because we want to keep the to layout to look
exactly the same visually with only the content re-arranged. If we had layout
row-major row by row, HTML margin collapse will make each row to have extra
gap.

Multi-column layout is done by putting groups of individual checkbox/radio inside
a fixed-width div and setting them to float:left.
 
The markup is like this:
 
 <div class="multicolumncheckboxesradios-wrapper clear-block">
   <div class="multicolumncheckboxesradios-column-first multicolumncheckboxesradios-column">
     #
     #
     #
     #
   </div>
   <div class="multicolumncheckboxesradios-column">
     #
     #
     #
     #
   </div>
   ...
   <div class="multicolumncheckboxesradios-column multicolumncheckboxesradios-column-last">
     #
     #
   </div>
 </div>

Default stylesheet:

.multicolumncheckboxesradios-column
{
  float: left;
  width: 10em;
}
