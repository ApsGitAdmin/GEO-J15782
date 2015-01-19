<?php
/**
 * @file
 * Theme preprocess functions for google analytics.
 */

/**
 * Theme function for aps Analytics block.
 */
function theme_aps_registration_analytics_aps_analytics($report) {
  return $report['chart'] . '<p>' . $report['views'] . '</p>';
}

/**
 * Theme function for common browser block.
 */
function theme_aps_registration_analytics_common_browser($report) {
  return $report['graph'];
}

/**
 * Theme function for geo-location block.
 */
function theme_aps_registration_analytics_geo_location($report) {
  return $report['map'];
}