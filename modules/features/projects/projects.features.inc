<?php

/**
 * Implementation of hook_imagecache_default_presets().
 */
function projects_imagecache_default_presets() {
  $items = array(
    'project_detail_thumb' => array(
      'presetname' => 'project_detail_thumb',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '96',
            'height' => '56',
          ),
        ),
      ),
    ),
    'project_featured_thumb' => array(
      'presetname' => 'project_featured_thumb',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '42',
            'height' => '42',
          ),
        ),
      ),
    ),
    'project_main_image' => array(
      'presetname' => 'project_main_image',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '192',
            'height' => '192',
          ),
        ),
      ),
    ),
    'project_popup' => array(
      'presetname' => 'project_popup',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '250',
            'height' => '123',
          ),
        ),
      ),
    ),
    'project_thumb' => array(
      'presetname' => 'project_thumb',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '125',
            'height' => '73',
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
function projects_node_info() {
  $items = array(
    'project' => array(
      'name' => t('Project'),
      'module' => 'features',
      'description' => '',
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
function projects_views_api() {
  return array(
    'api' => '3.0',
  );
}
