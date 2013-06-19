<?php

function saic_menu_action_info() {
  return array('saic_menu_action' => array(
    'type' => 'node',
    'description' => t('Add/Remove menu item'),
    'configurable' => true,
    'behavior' => array('changes_node_property'),
  ));
}

function saic_menu_action(&$node, $context) {
  $menu_item = db_fetch_array(
    db_query("SELECT * from {menu_links} WHERE link_path = 'node/$node->nid'")
  );
  if ($menu_item) {
    if ($context['action'] == 'remove') {
      db_query("DELETE from {menu_links} WHERE link_path = 'node/$node->nid'");
      unset($node->menu);
    }
  }
  else {
    $menu = array();
    $menu['menu_name'] = 'primary-links';
    $menu['plid'] = $context['parent'];
    $menu['link_path'] = 'node/'.$node->nid;
    $menu['link_title'] = $node->title;
    $menu['module'] = 'menu';
    $menu['hidden'] = $context['hidden'];
    $node->menu = $menu;
  }

  menu_cache_clear_all();
}

function saic_menu_action_form($context) {
  $form['action'] = array(
    '#type' => 'select',
    '#multiple' => false,
    '#title' => t('Menu item action'),
    '#description' => t('Add or remove menu item(s), based on the title and parent node.'),
    '#default_value' => 'add',
    '#options' => array(
      'add' => 'Add menu item',
      'remove' => 'Remove menu item',
    ),
  );
  $form['parent'] = array(
    '#type' => 'textfield',
    '#title' => t('Parent menu path'),
    '#description' => t('Enter a menu path, ex: "content/my-page"'),
    '#default_value' => '',
  );
  $form['hidden'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hidden menu item.'),
    '#default_value' => false,
  );
  return $form;
}

function saic_menu_action_validate($form, $form_state) {
  if (!$form_state['values']['action']) {
    form_set_error('action', t('You have not chosen to add or remove a menu item.'));
  }
}

function saic_menu_action_submit($form, $form_state) {
  // Validation will not work unless it is specified here
  $parent_id = 0;
  $link_path = $form_state['values']['parent'];
  if (!empty($link_path)) {
    $source_path = drupal_lookup_path('source', $link_path);
    if (!empty($source_path)) {
      $parent_menu_item = db_fetch_array(db_query("SELECT mlid from {menu_links} WHERE link_path = '$source_path' and hidden = 0"));
      if (isset($parent_menu_item['mlid'])) {
        $parent_id = (int) $parent_menu_item['mlid'];
      }
    }
    else {
      $parent_menu_item = db_fetch_array(db_query("SELECT mlid from {menu_links} WHERE link_path = '$link_path' and hidden = 0"));
      if (isset($parent_menu_item['mlid'])) {
        $parent_id = (int) $parent_menu_item['mlid'];
      }
      else {
        form_set_error('parent', t('Could not find a menu item for "@path"', array('@path' => $link_path)));
      }
    }
  }

  return array(
    'action' => $form_state['values']['action'],
    'hidden' => $form_state['values']['hidden'] ? 1 : 0,
    'parent' => $parent_id,
  );
}