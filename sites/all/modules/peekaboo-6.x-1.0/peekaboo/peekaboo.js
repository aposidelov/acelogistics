// $Id: peekaboo.js,v 1.1 2009/12/24 08:44:14 danielb Exp $

Drupal.behaviors.peekaboo = function(context) {

  $("a.peekaboo-link", context).click(function(e) {
    // Prevent the default action of clicking a link.
    e.preventDefault();
    // Determine what the ID of this link is.
    var link_id = $(this).attr('id'); 
    // Work out the ID of the div.
    var div_id = link_id.replace('-link', '');
    if ($(this).hasClass("peekaboo-processed")) {
      // Toggle it.
      $("div#"+div_id).toggle(0);
      // Remove the expanded class from the link.
      $("a#"+link_id).removeClass("peekaboo-expanded");
      // Add the collapsed class to the link.
      $("a#"+link_id).addClass("peekaboo-collapsed");
      // Remove the expanded class from the div.
      $("div#"+div_id).removeClass("peekaboo-expanded");
      // Add the collapsed class to the div.
      $("div#"+div_id).addClass("peekaboo-collapsed");
    }
    else {
      // Add the Ajax spinner after the link.
      $(this).after(
        '<span id="'+link_id+'-throb" class="peekaboo-throbber"></span>'
      );
      // Generate the Ajax callback path.
      var path = div_id.replace('-', '/').replace('-', '/').split("").reverse()
        .join("").replace('-', '/').split("").reverse().join("");
      // Add a random token to the path, to bypass IE caching.
      path = path + "/" + Math.floor((1000000000*Math.random())).toString(16);
      // Generate the full URI from the basePath and path.
      var uri = Drupal.settings.basePath + "?q=" + path;
      // Make the Ajax call and load the result into the div.
      $("div#"+div_id).load(uri, null, function(){
        // Remove the collapsed class from the div.
        $("div#"+div_id).removeClass("peekaboo-collapsed");
        // Add the expanded class to the div.
        $("div#"+div_id).addClass("peekaboo-expanded");
        // Remove the unprocessed class from the div.
        $("div#"+div_id).removeClass("peekaboo-unprocessed");
        // Add the processed class to the div.
        $("div#"+div_id).addClass("peekaboo-processed");
        // Remove the Ajax spinner.
        $("span#"+link_id+"-throb").remove();
        if ($("a#"+link_id).hasClass("peekaboo-link-removable")) {
          // Remove the link.
          $("a#"+link_id).remove();
        }
        else {
          // Remove the collapsed class from the link.
          $("a#"+link_id).removeClass("peekaboo-collapsed");
          // Add the expanded class to the link.
          $("a#"+link_id).addClass("peekaboo-expanded");
          // Remove the unprocessed class from the link.
          $("a#"+link_id).removeClass("peekaboo-unprocessed");
          // Add the processed class to the link.
          $("a#"+link_id).addClass("peekaboo-processed");
        }
        // Reattach this behaviour.
        Drupal.attachBehaviors("div#"+div_id);
      });
    }
  });

};