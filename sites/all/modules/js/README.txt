------------------------------------------------------------------------------
  High performance JS callback handler | readme
  http://drupal.org/project/js
------------------------------------------------------------------------------

Contents:
=========
1. ABOUT/TECHNICAL
2. INSTALLATION
3. MODULE INTEGRATION API
4. CREDITS

1. ABOUT
========

This module is not really one. Actually it is mainly a conditional replacement
for Drupal's index.php based on Apache's .htaccess rules.

With mod_rewrite enabled ("clean urls"), it catches all calls to callback
paths starting with "js/" and passes them to a reduced loader instead of
the default index.php file. Invoking only the explicitely defined dependencies
instead of a complete Drupal load, it saves lots of processing time and thus
speeds up small Ajax requests.

Apache benchmark examples (example by sun, original author):

Using index.php as usual:
  ab -n20 -c1 http://example.com/index.php?q=js/mymodule/callback
  Requests per second: 2.24 [#/sec] (mean)
  Time per request:    446.846 [ms] (mean)

Using js.php:
  ab -n20 -c1 http://example.com/js.php?q=js/mymodule/callback
  Requests per second: 16.84 [#/sec] (mean)
  Time per request:    59.371 [ms] (mean)


2. INSTALLATION
===============

* Install as usual, see http://drupal.org/node/70151 for further information.
* Copy js.php to the root directory of your Drupal installation
  (the place where your Drupal .htaccess and index.php is located).
* Enable clean URLs in drupal at admin/settings/clean-urls.
* Alter your .htaccess file as follows (located near file end):
  
  ----original:----
  (...something before...)

  # Rewrite URLs of the form 'x' to the form 'index.php?q=x'.

  (...something after...)
  -----------------

  ----modified-----
  (...something before...)

  # Rewrite JavaScript callback URLs of the form 'js.php?q=x'.
  RewriteCond %{REQUEST_URI} ^\/js\/.*
  RewriteRule ^(.*)$ js.php?q=$1 [L,QSA]

  # Rewrite URLs of the form 'x' to the form 'index.php?q=x'.
  
  (...something after...)
  -----------------

3. MODULE INTEGRATION API
=========================

This module requires your server to point all paths starting with js/ to js.php
rather than index.php. See above for how to do this in apache.

To integrate your modules, they must point to specific callback paths:
The 2nd argument after the mandatory initial js/ determines the implementing
module, which must implement hook_js() for security reasons.
Apart from security, modules may also specify another bootstrap level than
the default DRUPAL_BOOTSTRAP_PATH, and additionally required includes files
and module dependencies to load.

As an example, we'll let example.module expose its function
example_somefunction() to js.php. Its hook_js() implementation might look like
this:

<code>
  function example_js() {
    return array(
      'somefunction' => array(
        'callback' => 'example_somefunction',
        'includes' => array('theme', 'unicode'),
        'dependencies' => array('locale', 'filter', 'user'),
      ),
    );
  }
</code>

The hook_js() implementation above makes JS accept the following URL:

  http://example.com/js/example/somefunction.
                        ^       ^
           module name -|       |
                info array key -|

When called, it loads the requested include files and modules and calls the
callback function.

Note that it is wise to also register a corresponding menu path in hook_menu()
to provide fallback functionality when js.php is not available:

<code>
  $items[] = array(
    'path' => 'js/example/somefunction',
    'callback' => 'example_somefunction',
    'type' => MENU_CALLBACK,
  );
</code>

As stated above, js.php bootstraps Drupal to DRUPAL_BOOTSTRAP_PATH and includes
common.inc and locale.inc.  This means that url(), l(), and t() functions are
available (t() lacks translation though, since that would require locale.module
to be loaded.  This can be easily "fixed" by adding locale to the dependencies
array).  Theme functions and potentially required functions of other modules,
however, are not available by default, which is the main reason for the speed
gain of js.php.  Since the session has been initialized, the global $user
object is also available (but may not be fully loaded).

Please note that js.php does NOT perform access checks like Drupal's menu
system.  If required, each callback function needs to do this on its own.

js.php outputs the return value of the callback function using drupal_to_js().
To use a custom output format, output the data on your own and exit()
afterwards, or simply return nothing.

4. CREDITS
==========

Current maintainers:
Michiel Nugtier - http://drupal.org/user/1023784
David Herminghaus - http://drupal.org/user/833794

Authors of the original module:
* Daniel F. Kudwien (sun) - http://drupal.org/user/54136
* Stefan M. Kudwien (smk-ka) - http://drupal.org/user/48898

Project page: http://drupal.org/project/js
