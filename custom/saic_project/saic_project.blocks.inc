<?php

/**
 * Renders the project details block.
 */
function saic_project_block_project_details($node) {
  $content = "";
  $content .= drupal_render($node->content['field_project_customer']);
  $content .= drupal_render($node->content['field_project_facts']);
  return $content;
}

/**
 * Renders the project quick links block.
 */
function saic_project_block_quick_links($node) {
  return drupal_render($node->content['field_project_quick_links']);
}

/**
 * Renders the project Google Earth block.
 */
function saic_project_block_google_earth($node) {
  $content = t('View this project on an interactive map in Google Earth.');
  $link = $node->field_project_google_earth[0];
  $url = empty($node->field_project_google_earth[0]['display_url']) ? $node->field_project_google_earth[0]['url'] : $node->field_project_google_earth[0]['display_url'];
  $content .= ' ' . l(t('Learn More') . ' &raquo;', $url);
  return $content;
}
