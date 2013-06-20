<?php
/**
 * @file
 */


/**
 * Block 'View' callback for 'Primary Menu' block.
 */
function saic_menu_block_primary() {
  $block = array('subject' => '', 'content' => '');

  // Config
  $config = array(
    'menu_title'      => NULL,
    'menu_name'       => 'primary-links',
    'menu_delta'      => 'primary-links',
    'link_path'       => implode('/',arg()),
    'link_url'        => url(implode('/',arg())),
  );

  if(arg(0) == 'media' || check_media_page()){
    return FALSE;
  }

  // Should we render this block?
  if (FALSE == saic_menu_block_render_check($config['menu_name'],$config['menu_delta'])) {
    return FALSE;
  }

  // Get the tree.
  $block['content'] = saic_menu_tree_build($config);

  // Set the block title.
  $block['subject'] = $config['menu_title'];

  drupal_alter('saic_menu_block', $block);

  return $block;
}

