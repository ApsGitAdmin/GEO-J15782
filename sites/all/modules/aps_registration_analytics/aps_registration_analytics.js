/**
 * @file
 * Loads report blocks via ajax.  This is done because the API requests to Google
 * Analytics can add signifigant latency to page loads otherwise.
 */
(function ($) {

Drupal.behaviors.apsAnalyticsReports = {
  attach: function (context, settings) {
    $('#block-aps-registration-analytics-aps-analytics, #block-aps-registration-analytics-common-browser, #block-aps-registration-analytics-geo-location', context).show();
    if ($('.aps-registration-analytics', context).length) {
      $.ajax({
        url: Drupal.settings.googleAnalyticsReportsAjaxUrl + '/aps-analytics',
        dataType: 'json',
        data: ({ path: window.location.pathname + window.location.search }),
        success: function(data) {
          $('.aps-registration-analytics', context).html(data.content).hide().slideDown('fast');
        },
        error: function(data) {
          // @TODO
        }
      });
    }

    if ($('.aps-common-browser', context).length) {
      $.ajax({
        url: Drupal.settings.googleAnalyticsReportsAjaxUrl + '/common-browser',
        dataType: 'json',
        success: function(data) {
          $('.aps-common-browser', context).html(data.content);
        },
        error: function(data) {
          // @TODO
        }
      });
    }

    if ($('.aps-geo-location', context).length) {
      $.ajax({
        url: Drupal.settings.googleAnalyticsReportsAjaxUrl + '/geo-location',
        dataType: 'json',
        success: function(data) {
          $('.aps-geo-location', context).html(data.content);
        },
        error: function(data) {
          // @TODO
        }
      });
    }
  }
}

})(jQuery);