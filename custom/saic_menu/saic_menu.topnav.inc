<?php
/**
 * @file
 */

/**
 * Block 'View' callback for 'Top Navigation Menu' block.
 */
function saic_menu_block_topnav() {
  $block = array('subject' => '', 'content' => '');

  // Config
  $config = array(
    'menu_title'      => NULL,
    'menu_name'       => 'primary-links',
    'menu_delta'      => 'topnav',
    'link_path'       => implode('/',arg()),
    'link_url'        => url(implode('/',arg())),
  );

  // Should we render this block?
  if (FALSE == saic_menu_block_render_check($config['menu_name'])) {
    return $block;
  }

  // Get the tree.
  $block['content'] = saic_menu_tree_build($config);

  // Set the block title.
  $block['subject'] = $config['menu_title'];

  return $block;
}