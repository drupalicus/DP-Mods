<?php

/**
 * Implementation of hook_node_info().
 */
function submenu_node_info() {
  $items = array(
    'submenu' => array(
      'name' => t('Submenu'),
      'module' => 'features',
      'description' => t('A submenu for the main navigation.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
