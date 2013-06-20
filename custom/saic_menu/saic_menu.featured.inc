<?php
/**
 * @file
 */

/**
 * Block 'View' callback for 'Primary Menu' block.
 */
function saic_menu_block_featured($nav_tag = NULL) {
  $block = array('subject' => '', 'content' => '');
  $nav_id = variable_get("saic_menu_featured_nav['".$nav_tag."']", null);

  if (!isset($nav_id)) {
    return $block;
  }

  $featured_nav = '<ul id="solutions_nav">';
  $result = db_query("SELECT * FROM {menu_links} WHERE plid='%s' order by weight ASC", $nav_id);
  if ($result) {
    $rows = array();
    $link_class = 'not-active';
    while ($row = db_fetch_array($result)) {
      $rows[] = $row;
    }
    $row_count = 0;
    foreach ($rows as $row) {
      if ($row_count == 0) {
        $li_class = 'first';
      }
      elseif ($row_count+1 == count($rows)) {
        $li_class = 'last';
      }
      else {
        $li_class = '';
      }

      if ($_GET['q'] == $row['link_path']) {
        $link_class = 'active';
      }
      else {
        $link_class = 'not-active';
      }

      $featured_nav .= '
      <li class="'.$li_class.' saic-menu-block-item-2">
        <a href="'.url($row['link_path']).'" title="'.$row['link_title'].'" class="'.$link_class.'">
          <div class="menu-container"></div>'.$row['link_title'].'
        </a>
      </li>';

      $row_count++;
    }
  }
  $featured_nav .= '</ul>';

  // Get the tree.
  $block['content'] = $featured_nav;

  // Set the block title.
  $block['subject'] = $config['menu_title'];

  return $block;
}

/**
 * Block 'View' callback for 'Submenu' block.
 */
function saic_menu_block_submenu($mlid = NULL) {
  $block = array('subject' => '', 'content' => '');
  if (!isset($mlid)) {
    return $block;
  }
  // Find a submenu content item for the given mlid
  $result = db_query("
    SELECT field_submenu_images_value, field_submenu_content_value
    FROM {content_type_submenu}
    WHERE field_submenu_parent_value = %d
    LIMIT 1",
    $mlid
  );

  $featured_nav = '';
  if ($result) {
    $row = db_fetch_array($result);
    if (!empty($row)) {
      $link_class = ($row['field_submenu_images_value']) ? ' images' : '';
      $featured_nav = '
      <ul class="sub_menu'.$link_class.'">
        '.$row['field_submenu_content_value'].'
      </ul>';
    }
  }

  // Get the tree.
  $block['content'] = $featured_nav;
  return $block;
}

