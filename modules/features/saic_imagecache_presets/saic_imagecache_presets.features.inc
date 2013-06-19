<?php

/**
 * Implementation of hook_imagecache_default_presets().
 */
function saic_imagecache_presets_imagecache_default_presets() {
  $items = array(
    'list_item_center_play_thumb' => array(
      'presetname' => 'list_item_center_play_thumb',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '168',
            'height' => '104',
          ),
        ),
        '1' => array(
          'weight' => '0',
          'module' => 'imagecache_canvasactions',
          'action' => 'canvasactions_file2canvas',
          'data' => array(
            'xpos' => '147',
            'ypos' => '83',
            'alpha' => '100',
            'path' => 'images/play_overlay.png',
          ),
        ),
      ),
    ),
    'play_thumb' => array(
      'presetname' => 'play_thumb',
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
        '1' => array(
          'weight' => '0',
          'module' => 'imagecache_canvasactions',
          'action' => 'canvasactions_file2canvas',
          'data' => array(
            'xpos' => '75',
            'ypos' => '37',
            'alpha' => '100',
            'path' => 'images/play_overlay.png',
          ),
        ),
      ),
    ),
  );
  return $items;
}
