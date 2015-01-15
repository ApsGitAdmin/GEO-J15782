<?php
/**
 * @file
 * Theme preprocess functions for google analytics.
 */

/**
 * Theme function for path_mini block.
 */
function theme_aps_registration_analytics_aps_analytics($report) {
  return $report['chart'] . '<p>' . $report['views'] . '</p>';
}