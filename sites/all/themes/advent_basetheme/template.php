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

function adVENT_Basetheme_form_comment_form_alter(&$form, &$form_state, $form_id) {

	$form['comment_body'][LANGUAGE_NONE][0]['#title'] = t('Question');
	/*dpm($form);*/

	$form['actions']['submit']['#value'] = t('SUBMIT');
  
  $label = t('Name');
  if (isset($form['author']['_author'])) {
    $form['author']['_author']['#title'] = $label;
  }
  else {
    $form['author']['name']['#title'] = $label;
  }
}


function adVENT_Basetheme_theme(&$existing, $type, $theme, $path) {
   $hooks['user_login_block'] = array(
     'template' => 'templates/user-login-block',
     'render element' => 'form',
   );
   return $hooks;
 }
function adVENT_Basetheme_preprocess_user_login_block(&$vars) {
  $vars['name'] = render($vars['form']['name']);
  $vars['pass'] = render($vars['form']['pass']);
  $vars['submit'] = render($vars['form']['actions']['submit']);
  
  $vars['form']['links']['#markup'] = '';
  $vars['rendered'] = drupal_render_children($vars['form']);
}




?>