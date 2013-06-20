<?php

function saic_menu_admin_form() {

  drupal_add_css(drupal_get_path('module','saic_menu') . '/saic_menu.css');

  $form = array();
  $menus = menu_get_menus();

  foreach ($menus as $menu => $menu_name) {
    $form['saic_menu'][$menu] = array();
  }

}

/*
* SAIC menu featured navigation settings form
*/
function saic_menu_settings_form() {
  $form = array();
  $featured_values = '';
  $saic_featured_menu_keys = variable_get("saic_menu_featured_nav_keys", "");
  $saic_featured_menus = explode('|', $saic_featured_menu_keys);
  foreach ($saic_featured_menus as $saic_featured_menu_key) {
  	$saic_featured_menu = variable_get("saic_menu_featured_nav['".$saic_featured_menu_key."']", '');
  	$featured_values .= $saic_featured_menu_key."|".$saic_featured_menu."\n";
  }
  $form['saic_menu_featured_nav'] = array(
    '#type' => 'textarea',
    '#title' => t('Featured Navigation'),
    '#default_value' => $featured_values,
  );

	$form['save'][] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['#submit'][] = 'saic_menu_settings_form_submit';

  return $form;
}


/**
 * SAIC menu featured navigation settings form submit handler
 */
function saic_menu_settings_form_submit($form, &$form_state) {
		$featured_menus = explode("\n", $form_state['values']['saic_menu_featured_nav']);
    // Set the new featured menu items
    $featured_nav_keys = '';
    $featured_nav = array();
		foreach ($featured_menus as $featured_menu) {
			if (empty($featured_menu)) {
				continue;
			}
			$menu_info = explode('|', $featured_menu);
			if (!empty($featured_nav)) {
				$featured_nav_keys .= '|';
			}
			$featured_nav_keys .= $menu_info[0];
			$featured_nav[$menu_info[0]] = (int) $menu_info[1];
			variable_set("saic_menu_featured_nav['".$menu_info[0]."']", (int) $menu_info[1]);
		}
		variable_set("saic_menu_featured_nav_keys", $featured_nav_keys);

    drupal_set_message('SAIC featured navigation settings have been updated','status');
}