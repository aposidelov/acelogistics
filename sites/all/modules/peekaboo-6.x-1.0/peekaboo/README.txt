// $Id: README.txt,v 1.1 2009/12/24 08:44:14 danielb Exp $

Peekaboo README

CONTENTS OF THIS FILE
----------------------

  * Introduction
  * Installation
  * Example Usage


INTRODUCTION
------------
Provides a CCK field that can be used in nodes, node templates, and views to
output the contents of another CCK field, from the same node, via Ajax.

This module was made when I had built a massive site structure using the book
module, although similar hierarchies are possible with other modules such as
node reference.  I used a viewfield to embed a view of the child nodes into
each node.  Each view also showed the output of the child node's viewfields.  
I discovered I could produce a massive tree of nodes, however it was very
slow to load.  I needed a solution that allows the user to load a minimal
version of the node, with the ability to produce and display the viewfield
at the user's discretion, thereby preventing memory or time limits exceeding
upon page load, especially once more nodes were added.   I messed around with
trying to create a new type of formatter for all CCK fields, but hit a dead
end, soon the peekaboo cck field was born, one field to point to another.

Maintainer: Daniel Braksator (http://drupal.org/user/134005)
Project page: http://drupal.org/project/peekaboo.


INSTALLATION
------------
1. Copy peekaboo folder to modules (usually sites/all/modules) directory.
2. At admin/build/modules enable the Peekaboo module.


EXAMPLE USAGE
-------------
0. Prior to using this module you have created some other CCK field on your
   content type.
1. Create a CCK field using the Peekaboo Select widget (See CCK module help).
2. Optionally, configure the default value of the CCK field to point to a
   target CCK field, and use the 'content permissions' module to disable the
   ability for node authors in certain roles to change this field.
3. Choose the wording for the link, and whether to hide the link upon use.  If
   the link is not hidden it will be usable as a 'toggle' for the content.
3. For optimal performance, hide and exclude the target field from being loaded
   in the node on the 'display fields' section when configuring your content
   type.
4. Choose the 'display fields' settings appropriate for your peekaboo field:
     Default - Gives the link and the empty container for the ajax.
     Plain (no link) - Gives only the empty container for the ajax.  You would
       have to theme/template your own link.  The resulting HTML output must contain
       the three classes as shown in the example below, as well as have the same ID
       as the div container except with -link appended to the end.
       <a href="#" id="[id of div]-link" class="peekaboo-link peekaboo-collapsed peekaboo-unprocessed">text</a>
     Link only - Gives only the link, you could use it in conjunction with the
       plain formatter in views, or provide the div container yourself,
       which involves using the 3 classes: peekaboo-container, 
       peekaboo-collapsed, and peekaboo-unprocessed, as well as the same ID
       as the link, except without the -link part at the end.
5. Optionally use CSS to turn the link into an image, for example:
   <style type="text/css">
   a.peekaboo-link {
     /* Give the link a bounding box */
     display: block;
     width: 100px; /* width of bg image */
     height: 100px;  /* height of bg image */

     /* Add the image - use your imagination */
     background: transparent url(images/my_image.png) no-repeat 0 0;

     /* Hide the text in most browsers */
     text-indent: -10000px;
     overflow: hidden;

     /* Hide the text in IE */
     line-height: 0;

     /* If your image simulates a button, use this cursor style */
     cursor: default;
   }
   </style>
6. Optionally use a different image for a.peekaboo-collapsed and 
   a.peekaboo-expanded selectors, e.g. an arrow that points to the right, and
   and arrow that points down.
7. Optionally override the styles in the .css file included with the module, 
   such as the throbber image.