<?php
/**
 * @file
 * Callbacks for building blocks.
 */

/**
 * Page callback for google-analytics-reports/ajax/aps-analytics.
 */
function aps_registration_analytics_ajax() {
  $path = isset($_GET['path']) ? $_GET['path'] : variable_get('google_analytics_reports_default_page', '/index.html');
  return drupal_json_output(array('content' => aps_registration_analytics_build($path)));
}

 /**
 * Generates a block with the current page statistics.
 */
function aps_registration_analytics_build($path) {
  if (!variable_get('google_analytics_reports_oauth_token', FALSE)) {
    return '<p>' . t('You must <a href="!url">authorize</a> Drupal to use your Analytics account before you can view reports.', array('!url' => url('admin/config/system/google-analytics-reports'))) . '</p>';
  }

  $filters = array();

  global $base_path;

  if (strpos($path, $base_path) !== FALSE) {
    $drupal_path = str_replace($base_path, '', $path);
    $path = str_replace($base_path, '/', $path);
  }
  if ($path == '/') {
    $path = variable_get('google_analytics_reports_default_page', '/index.html');
  }
  array_push($filters, _google_analytics_reports_path_filter($path));

  if ($node = menu_get_object('node', 1, drupal_get_normal_path($drupal_path))) {
    if ($node->type == 'events') {
      $start_date = $node->field_event_start_date[LANGUAGE_NONE][0]['value'];
      $end_date = $node->field_event_end_date[LANGUAGE_NONE][0]['value'];

      array_push($filters, _google_analytics_reports_live_filter($start_date, $end_date));
    }
  }

  $params = array(
    'metrics' => array('ga:users'),
    'dimensions' => array('ga:hour,ga:minute,ga:pagePath'),
    'sort_metric' => array('ga:hour,ga:minute'),
    'filters' => implode(';', $filters),
    'start_date' => isset($start_date) ? $start_date : strtotime('-1 day'),
    'end_date' => isset($end_date) ? $end_date : strtotime('-1 day'),
  );

  $feed = google_analytics_api_report_data($params);
  if ($feed->error) {
    return '<p>' . _google_analytics_reports_error_message() . '</p>';
  }
  $max_visits = 0;
  foreach ($feed->results->rows as $row) {
    $data[] = $row['users'];
    $max_visits = max($row['users'], $max_visits);
  }
  $chart = array(
    '#title' => '',
    '#chart_id' => 'users_event_live',
    '#data' => $data,
    '#type' => CHART_TYPE_LINE . ':nda',
    '#size' => chart_size(500, 80),
    '#adjust_resolution' => TRUE,
    '#data_colors' => array('E51837'),
    '#chart_fill' => chart_fill('bg', '00000000'),
    '#shape_markers' => array(chart_shape_marker(0, 0, 'B', 0, $color = 'EEEEEE')),
    '#line_styles' => array(chart_line_style(2, 10, 0)),
  );

  $last_day = end($feed->results->rows);
  $title = t('The most views during this period was @max.', array('@max' => $max_visits));

  $chart['#attributes'] = array(
    'title' => $title, 
    'style' => 'height:' . $chart['#size']['#height'] . 'px; width:100%'
  );
  $report['chart'] = l(theme('chart', array('chart' => $chart)), 'admin/reports/google-analytics/detail', array('query' => array('path' => $path), 'html' => TRUE));
  $report['views'] = t('@views viewer(s) for this time period', array('@views' => number_format($feed->results->totalsForAllResults['users'])));
  return theme('aps_registration_analytics_aps_analytics', $report);
}