<?php

/**
 * Implements hook_rules_event_info().
 */
function aps_pageexit_rules_event_info() {
  $events = array(
    'aps_pageexit_stopwatch' => array(
      'label' => t('User has finished watching Webcast'),
      'group' => t('aps'),
    ),
  );
  return $events;
}