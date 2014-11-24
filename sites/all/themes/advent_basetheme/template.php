<?php

/**
 * @file
 * This file is empty by default because the base theme chain (Alpha & Omega) provides
 * all the basic functionality. However, in case you wish to customize the output that Drupal
 * generates through Alpha & Omega this file is a good place to do so.
 * 
 * Alpha comes with a neat solution for keeping this file as clean as possible while the code
 * for your subtheme grows. Please read the README.txt in the /preprocess and /process subfolders
 * for more information on this topic.
 */
 
function adVENT_Basetheme_preprocess_html(&$vars) {
  $body_classes = array($vars['classes_array']);
  if ($vars['user']) {
    foreach($vars['user']->roles as $key => $role){
      $role_class = 'role-' . str_replace(' ', '-', $role);
      $vars['attributes_array']['class'][] = $role_class;
    }
  }
}
?>