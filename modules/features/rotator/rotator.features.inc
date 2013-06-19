<?php

/**
 * Implementation of hook_imagecache_default_presets().
 */
function rotator_imagecache_default_presets() {
  $items = array(
    'rotator_image' => array(
      'presetname' => 'rotator_image',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '920',
            'height' => '443',
          ),
        ),
      ),
    ),
    'rotator_image_small' => array(
      'presetname' => 'rotator_image_small',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '716',
            'height' => '368',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function rotator_node_info() {
  $items = array(
    'rotator_image' => array(
      'name' => t('Rotator Image'),
      'module' => 'features',
      'description' => t('An image that will be shown in a rotator/slideshow on the site.'),
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

/**
 * Implementation of hook_views_api().
 */
function rotator_views_api() {
  return array(
    'api' => '3.0',
  );
}
