$Id

Content Levels
---------------

package: 'CCK'

This module provides the content_level CCK field-type and field-widget 
which can be placed on any content type, and shared across multiple 
content types (in the normal way with CCK).

In the global settings for this field the user defines an ordered series of
content levels, and sets one of them as default.

In the field-instance specific (widget) settings for the field the user may
define, for each content level in her series, which fields are visible and
which are editable when the node has that content level.

All settings for this module are found only on the CCK field settings page
for each instance of a field. In other words, add a content_levels field to 
a content type and then click its 'configure' link.

Dependencies
-------------

This module is dependent on the following modules:

- content (CCK)
- date_api (Date): Used for handling the 'degrade on' date/time form widget
and timezones.