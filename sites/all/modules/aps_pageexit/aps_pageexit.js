(function($) {
  Drupal.aps_pageexit = {};
  var click = false; // Allow Submit/Edit button

  Drupal.behaviors.apsPageExit = {
    attach : function(context) {
      // Catch all links and buttons EXCEPT for "#" links
      //$("a, button, input[type='submit']:not(.node-edit-protection-processed)")
      $("a, button, input[type='submit']")
          .each(function() {
            $(this).click(function() {
              // return when a "#" link is clicked so as to skip the
              // window.onbeforeunload function
              if ($(this).attr("href") != "#") {
                return 0;
              }
            });
          });

      // Handle backbutton, exit etc.
      window.onbeforeunload = function() {
        if (!click) {
          click = false;
          return (Drupal.t("This webcast has not ended yet."));
        }
      }

      window.onunload = function () {
        $.ajax({
          type: 'POST',
          async: false,
          url: Drupal.settings.basePath + 'aps_pageexit/timeout',
          dataType: 'json',
          data: 'js=1'
        });
      }
    }
  };
})(jQuery);