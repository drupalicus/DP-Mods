<?php
/**
 * @file
 */

function saic_menu_tree_find_active($below,$parent,$menu_name) {
  $active_item = array();
  if(!isset($below) || !is_array($below)) {
    return $active_item;
  }
  foreach($below as $menu_item => $menu_data) {
    if(isset($menu_data['link']['active_item']) && $menu_data['link']['active_item'] == TRUE) {
      $active_item['parent'][$menu_name] = $parent;
      
      $active_item['active'][$menu_item] = $parent['below'][$menu_item];
      $active_item['data'] = $menu_data['link'];
      return $active_item;
    }
  
    $active_item = saic_menu_tree_find_active($menu_data['below'],$below[$menu_item],$menu_name);
    if(!empty($active_item)) {
      return $active_item;
      break;
    }
  }
  return $active_item;
}

//Trim menu to 2 levels, hide the hidden ones
function saic_menu_unset_children_children(&$tree, $show_children = false) {
  foreach($tree as $menu_item => &$menu_data) {
    if(isset($tree[$menu_item]['below'])) {
      foreach($tree[$menu_item]['below'] as $key => &$data) {
        if(isset($data['below'])) {
          if(!$show_children) {
            unset($data['below']);
          }
          else {
            foreach($data['below'] as $below_key => $below_item) {
              if(abs($below_item['link']['hidden']) == 1) {
                unset($data['below'][$below_key]);
              }
            }
          }
        }
        
        if(abs($data['link']['hidden']) == 1) {
          unset($tree[$menu_item]['below'][$key]);
        }
      }
    }
  }
}


/**
 * "Main" function to build the menu tree.
 */
function saic_menu_tree_build($config) {

  // Set Menu Cache CID.
  $cid = implode(':', array('saic_menu', $config['menu_name'], $config['menu_delta'], $config['link_path']));

  // Bypass Cache?
  if (!isset($config['no-cache'])) {
    // Does cache exist?
    $cached = cache_get($cid, 'cache_menu');
    if (!empty($cached)) {
      // Return cached menu.
      return $cached->data;
    }
  }

  // Get the full, un-pruned tree.
  $tree = menu_tree_all_data($config['menu_name']);

  // Get the depth of the tree
  $config['tree_depth'] = saic_menu_get_depth($tree);

  // Add the active trail data to the full tree.
  $active_found = saic_menu_tree_add_active_path($tree, $config);

  // If active item not found, return null.
  if (!$active_found && $config['menu_delta'] != 'topnav') {
    return NULL;
  }

  // Localize the tree.
  if (module_exists('i18nmenu')) {
    i18nmenu_localize_tree($tree);
  }

  $trim_links = FALSE;
  if($config['menu_delta'] != 'primary-links') {
    $prune = saic_menu_config($config['menu_delta']);
    saic_menu_tree_prune_parse($config, $prune);
    unset($prune);
    saic_menu_tree_prune_parse($config, $prune);
    saic_menu_tree_prune_eval_actions($config);
    saic_menu_tree_prune($tree, $config, 0);
  }
  else {
    //Find what item is active, set in a array for use below
    $active_item = array();
    foreach($tree as $menu_item => $menu_data) {
      if($menu_data['link']['active_item'] == TRUE) {
        $active_item['parent'][$menu_item] = $menu_data;
        $active_item['active'][$menu_item] = $menu_data['below'][$menu_item];
        $active_item['data'] = $menu_data['link'];
         break;
      }
       if(!empty($menu_data['below'])) {
          $active_item = saic_menu_tree_find_active($menu_data['below'],$tree[$menu_item],$menu_item);
       }
      if(!empty($active_item)) {
        break;
      }
    }

    //Logic for primary-links 
    $prune = saic_menu_config($config['menu_delta']);
    
    if($active_item['data']['has_children'] == 0) {
      $tree = $active_item['parent'];
    }
    elseif(($active_item['data']['has_children'] == 1 && $active_item['data']['expanded'] == 0)) {
      $trim_links = FALSE;
      $tree = $active_item['parent'];
    }
    //Set the current item as tree, with children.
    elseif(($active_item['data']['has_children'] == 1 && $active_item['data']['expanded'] == 1)) {
      //Show only children, not children of children
      foreach($active_item['active'] as $parent => $data) {
        foreach($data['below'] as $menu_item => $data_menu){
          $data_menu['below'] = FALSE;
        }
      }
      $tree = $active_item['active'];
    }
    unset($prune);
    saic_menu_unset_children_children(&$tree, $config['show_children']);
    if($tree['link']['hidden'] == 1) {
      unset($tree);
    }
  }

  //Trim the top nav to the first 5 items
  if($config['menu_delta'] == 'topnav') {
    $tree = array_slice($tree,0,6);
  }

  if($config['menu_delta'] == 'featured-links') {
    saic_menu_tree_add_classes_featured($tree);
  } 
  else {
    saic_menu_tree_add_classes($tree);
  }

  // Theme the branches.
  $content = saic_menu_tree_branch_theme($tree, $config);

  // Set the block body.
  $hooks = array(
    'saic_menu_block__' . preg_replace('/-/', '_', $config['menu_delta']),
    'saic_menu_block__' . preg_replace('/-/', '_', $config['menu_name']),
    'saic_menu_block'
  );

  // Theme the tree.
  $themed = theme($hooks, $tree, $config, $content);

  // Set the Cache.
  cache_set($cid, $themed, 'cache_menu');

  return $themed;
}


/**
 * Add the active trail indicators into the tree.
 *
 * The data returned by menu_tree_page_data() has link['in_active_trail'] set to
 * TRUE for each menu item in the active trail. The data returned from
 * menu_tree_all_data() does not contain the active trail indicators. This is a
 * helper function that adds it back in with an added bonus, the 'active_item'.
 * We also take this opportunity to gather information about the active item and
 * apply that to the $config.
 *
 * @param $tree
 *   array The menu tree.
 * @return
 *   void
 */
function saic_menu_tree_add_active_path(&$tree, &$config) {
  $active_mlid = NULL;
  $active_href = NULL;
  $active_flag = FALSE;

  // Get the active Items.
  $tree_with_trail = menu_tree_page_data($config['menu_name']);

  // Query for active item mlid.
  $active_mlid = db_result(db_query('
    SELECT mlid
    FROM {menu_links}
    WHERE menu_name = "%s"
      AND link_path = "%s"',
    $config['menu_name'], $config['link_path']));

  // If the active mlid is not found, check for alternative method
  // for setting the active item.
  $tmp_tree = $tree;
  // Check for Special Cases.
  $active_mlid = _saic_menu_active_path($config, $tmp_tree);
  if (!empty($active_mlid)) {
    $tree_with_trail = $tmp_tree;
  }
  // If we still do not have a mlid, try menutrails.
  else {
    // Is the active item set with a different module?
    if (module_exists('menutrails')) {
      if ('node' == arg(0) && preg_match('/^[0-9]+$/', arg(1))) {
        $node = node_load(arg(1));
        $active_item = menutrails_node_location($node);
        $active_href = $active_item['href'];
      }
    }
  }

  // Update in_active_trail in tree.

  // To traverse the original tree down the active trail, we use a pointer.
  $subtree_pointer =& $tree;

  // Find each key in the active trail.
  while ($tree_with_trail) {
    foreach (array_keys($tree_with_trail) AS $key) {
      if ($tree_with_trail[$key]['link']['in_active_trail']) {
        // Set the active trail info in the original tree.
        $subtree_pointer[$key]['link']['in_active_trail'] = TRUE;
        // Set the active item in the original tree.
        if ($active_mlid == $tree_with_trail[$key]['link']['mlid'] ||
            $active_href == $tree_with_trail[$key]['link']['href']) {
          $active_flag = TRUE;
          $subtree_pointer[$key]['link']['active_item'] = TRUE;
          // Set additional link info in the $config.
          $config['link_depth'] = (int)$subtree_pointer[$key]['link']['depth'];
          $config['link_children'] = (!empty($subtree_pointer[$key]['below'])) ? TRUE : FALSE;
        }
        // Continue in the subtree, if it exists.
        $tree_with_trail =& $tree_with_trail[$key]['below'];
        $subtree_pointer =& $subtree_pointer[$key]['below'];
        break;
      }
      else {
        unset($tree_with_trail[$key]);
      }
    }
  }
  return $active_flag;
}


/**
 * Active Path Helper Function.
 *
 * Set the Active Menu Item using "special cases" configuration.
 */
function _saic_menu_active_path(&$config, &$tree) {
  $success = NULL;
  $show_children = false;
  $cases = saic_menu_special_cases($config['menu_name']);

  // Check each config for a match.
  if (empty($cases)) {
    return;
  }
  foreach ($cases as $key => $c) {
    $flag = FALSE;
    // Check for matching arguments.
    foreach ($c['arguments'] as $arg => $val) {
      switch ($arg) {
        case 'custom_pages':
            $flag = TRUE;
        break;
        case 'custom_pages_args':
           if(arg(0) == $val)
            $flag = TRUE;
        break;
        case 'href':
          $current_path = drupal_get_path_alias($config['link_path']);
          if (preg_match('/' . $val . '/', $current_path)) {
            $flag = TRUE;
          }
          break;
        case 'node_type':
          if (preg_match('/^node\/[0-9]+$/', $config['link_path'])) {
            $nid = preg_replace('/^node\//', '', $config['link_path']);
            $node = node_load($nid);
            if ($node->type == $val) {
              $flag = TRUE;
            }
          }
          break;
        case 'node_reference':
          if (preg_match('/^node\/[0-9]+$/', $config['link_path'])) {
            $nid = preg_replace('/^node\//', '', $config['link_path']);
            $node = node_load($nid);
            if ($node->type == $val) {
              $flag = TRUE;
            }
          }
          break;
      }
    }
    // If all arguments match, set the success actions.
    if (TRUE == $flag) {
      if ($c['actions']['show_children']) {
        $show_children = true;
      }
      if (array_key_exists('mlid', $c['actions'])) {
        $success = $c['actions'];
        break;
      }
      elseif (array_key_exists('nid_from_field', $c['actions'])) {
        switch($c['actions']['nid_from_field']) {
          case 'field_magazine_issue_magazine[0][nid]':
            $mid = get_mid_from_nid($node->field_magazine_issue_magazine[0]['nid']);
            $c['actions']['mlid'] = $mid;
            $success = $c['actions'];
          break;
         case 'field_magazine_article_issue[0][nid]':
           $parent_mid =  saic_magazine_get_magazine_nid_from_issue_nid($node->field_magazine_article_issue[0]['nid']);
           $mid = get_mid_from_nid($parent_mid['field_magazine_issue_magazine_nid']);
           $c['actions']['mlid'] = $mid;
           $success = $c['actions'];
          break;
        }
      }
      elseif (array_key_exists('nid_from_path', $c['actions'])) {
        $mid = get_mid_from_path($c['actions']['nid_from_path']);
        $c['actions']['mlid'] = $mid;
        $success = $c['actions'];
        break;
      }
    }
  }

  // Set the active trail if we have a special case match.
  if (!empty($success)) {

    if (!empty($success['mlid'])) {
      $active_trail = db_fetch_array(db_query('
        SELECT mlid,p1,p2,p3,p4,p5,p6,p7,p8,p9
        FROM {menu_links}
        WHERE menu_name = "%s"
          AND mlid = "%s"',
        $config['menu_name'], $success['mlid']));
    }
    elseif (!empty($success['href'])) {
      $active_trail = db_fetch_array(db_query('
        SELECT mlid,p1,p2,p3,p4,p5,p6,p7,p8,p9
        FROM {menu_links}
        WHERE menu_name = "%s"
          AND link_path = "%s"',
        $config['menu_name'], $success['href']));
    }

    // Make sure we have a trail
    if (!empty($active_trail)) {
      if ($show_children) {
        $config['show_children'] = true;
      }

      // To traverse the original tree down the active trail, we use a pointer.
      $subtree_pointer =& $tree;

      // Find each key in the active trail.
      $tree_with_trail = $tree;
      while ($tree_with_trail) {
        foreach (array_keys($tree_with_trail) AS $key) {
          if (in_array($tree_with_trail[$key]['link']['mlid'], $active_trail)) {
            // Set the active trail info in the original tree.
            $subtree_pointer[$key]['link']['in_active_trail'] = TRUE;
            // Continue in the subtree, if it exists.
            $tree_with_trail =& $tree_with_trail[$key]['below'];
            $subtree_pointer =& $subtree_pointer[$key]['below'];
            break;
          }
          else {
            unset($tree_with_trail[$key]);
          }
        }
      }
      return $active_trail['mlid'];
    }
  }
  return NULL;
}


/**
 * Find the applicable pruning configuration.
 *
 * Add a single prune configuration array to the $config.
 */
function saic_menu_tree_prune_parse(&$config, $prune) {
  // Find the applicable prune configuration.
  foreach ($prune as $p) {
    // Set a flag to determine config match.
    $flag = TRUE;

    foreach ($p['arguments'] as $op => $arg) {
      switch ($op) {

        case 'menu_size':
          if (!eval('return (' . _saic_menu_eval_vals($config['link_depth'], $arg['value']) . ' ' . $arg['operator'] . ' ' . $config['tree_depth'] . ');')) {
            $flag = FALSE;
            break 2;
          }
          break;

        case 'has_children':
          if (!((empty($config['link_children']) && empty($arg['value'])) || (!empty($config['link_children']) && !empty($arg['value'])))) {
            $flag = FALSE;
            break 2;
          }
          break;

        case 'node_type':
          if (preg_match('/^node\/[0-9]+$/', $config['link_path'])) {
            $nid = preg_replace('/^node\//', '', $config['link_path']);
            $node = node_load($nid);
            if ($node->type == $arg['value']) {
              // No need to set the flag, just break to bypass FALSE below.
              break;
            }
          }
          $flag = FALSE;
          break 2;
      }
    }

    // Set the active prune configuration if it meets all requirements.
    if ($flag == TRUE) {
      $config['prune'] = $p;
      break;
    }
  }

}


/**
 * Prune the Menu Tree.
 *
 * Prunes the tree according to specification defined in $config.
 */
function saic_menu_tree_prune(&$tree, $config) {
  // Set positive if any branches are trimmed. 1 = inactive, 2 = active
  $trimmed = 0;

  foreach ($tree as $branch_id => $branch) {

    // Trim the Tree.

    // Trim Hidden Items.
    if (!empty($branch['link']['hidden'])) {
      unset($tree[$branch_id]);
      continue;
    }

    // Prune Inactive Branch.
    if (FALSE == $branch['link']['in_active_trail']) {
      $expression = (preg_match('/current/', $config['prune']['actions']['prune_inactive_level']['eval'])) ? preg_replace('/current/', $branch['link']['depth'], $config['prune']['actions']['prune_inactive_level']['eval']) : $config['prune']['actions']['prune_inactive_level']['eval'];
      if (eval($expression)) {
        unset($tree[$branch_id]);
        // Set the trimmed, but don't overwrite 'active' trimmed setting.
        if (2 != $trimmed) {
          $trimmed = 1;
        }
        continue;
      }
    }
    // Prune Active Branch.
    elseif (TRUE == $branch['link']['in_active_trail']) {
      $expression = (preg_match('/current/', $config['prune']['actions']['prune_active_level']['eval'])) ? preg_replace('/current/', $branch['link']['depth'], $config['prune']['actions']['prune_active_level']['eval']) : $config['prune']['actions']['prune_active_level']['eval'];
    }
    
    if($expression == 'return () ? TRUE : FALSE;')
      continue;

    if (eval($expression) ) {
      unset($tree[$branch_id]);
      $trimmed = 2;
      continue;
    }
    // Prune Not-Active Items within the active Trail.
    if (TRUE == $branch['link']['in_active_trail']) {
      $expression = (preg_match('/current/', $config['prune']['actions']['prune_active_trail']['eval'])) ? preg_replace('/current/', $branch['link']['depth'], $config['prune']['actions']['prune_active_trail']['eval']) : $config['prune']['actions']['prune_active_trail']['eval'];
      if (eval($expression)) {
        unset($tree[$branch_id]['link']);
        $tree = $tree[$branch_id]['below'];
        $trimmed = 2;
        continue;
      }
    }


    // Recurse the branch if it has children.
    $child_trimmed = FALSE;
    if (!empty($branch['below'])) {
      $child_trimmed = saic_menu_tree_prune($tree[$branch_id]['below'], $config);
    }


    // Add some Classes.

    // The link level.
    $tree[$branch_id]['link']['classes_array'][] = 'level-' . $branch['link']['depth'];
    // If this is in the active trail: add active-trail class.
    if ($branch['link']['in_active_trail']) {
      $tree[$branch_id]['link']['classes_array'][] = 'active-trail';
    }
    // If this is the active item: add active class.
    if (isset($branch['link']['active_item']) && $branch['link']['active_item']) {
      $tree[$branch_id]['link']['classes_array'][] = 'active';
    }
    // If children are hidden: add has-children class.
    if ($branch['link']['has_children']){
      $tree[$branch_id]['link']['classes_array'][] = 'has-children';
      // If children are not hidden: add level-up class.
      if ($child_trimmed) {
        $tree[$branch_id]['link']['classes_array'][] = 'level-up';
      }
    }
    // If expanded is set: add 'expanded' class.
    // TODO: this should really be moved up as an else to child_trimmed, will need to alter the css.
    if ($branch['link']['expanded']) {
      $tree[$branch_id]['link']['classes_array'][] = 'expanded';
    }
    // If this is the bottom level: add bottom-level class.
    static $bottom_level;
    if (!isset($bottom_level)) {
      // If we don't already know it, find the lowest possible level.
      for ($i=0; $i<=$config['tree_depth']; $i++) {
        $expression = (preg_match('/current/', $config['prune']['actions']['prune_inactive_level']['eval'])) ? preg_replace('/current/', $i, $config['prune']['actions']['prune_inactive_level']['eval']) : $config['prune']['actions']['prune_inactive_level']['eval'];
        if (!eval($expression) && $bottom_level < $i) {
          $bottom_level = $i;
        }
        $expression = (preg_match('/current/', $config['prune']['actions']['prune_active_level']['eval'])) ? preg_replace('/current/', $i, $config['prune']['actions']['prune_active_level']['eval']) : $config['prune']['actions']['prune_active_level']['eval'];
        if (!eval($expression) && $bottom_level < $i) {
          $bottom_level = $i;
        }
      }
    }
    if ($bottom_level == $branch['link']['depth']) {
      $tree[$branch_id]['link']['classes_array'][] = 'bottom-level';
    }
  }

  return $trimmed;
}

/**
 * Apply Zebra and First/Last Classes to tree items
 */
function saic_menu_tree_add_classes_featured(&$tree) {

  $first_branch = 0;
  foreach ($tree as $branch_id => $branch) {
    if($first_branch !=0)
      break;
     $first = $branch_id;
    $first_branch++;
  }

  if(!empty($tree[$first]['below'])) {
    $tree = $tree[$first]['below'];
  }

  $zebra = 'odd';
  $max = count($tree);
  $cnt = 1;

  foreach ($tree as $branch_id => $branch) {
    
    if($tree[$branch_id]['below']) {
      $tree[$branch_id]['below'] = false;
    }

    $tree[$branch_id]['link']['classes_array'][] = $zebra;

    if ($cnt == 1) {
      $tree[$branch_id]['link']['classes_array'][] = 'first';
    }
    if ($cnt == $max) {
      $tree[$branch_id]['link']['classes_array'][] = 'last';
    }

    if(!empty($tree[$branch_id]['link']['localized_options']['attributes']['class'])) {
      $tree[$branch_id]['link']['classes_array'][] = $tree[$branch_id]['link']['localized_options']['attributes']['class'];
    }

    $zebra = ($zebra == 'odd') ? 'even' : 'odd';
    $cnt++;

  }
}



/**
 * Apply Zebra and First/Last Classes to tree items
 */
function saic_menu_tree_add_classes(&$tree) {
  $zebra = 'odd';
  $max = count($tree);
  $cnt = 1;

  foreach ($tree as $branch_id => $branch) {

    $tree[$branch_id]['link']['classes_array'][] = $zebra;

    if ( arg(0) == 'node' && is_numeric(arg(1))) {
      $node_data = node_load(arg(1));
      $parent_menu_id = $node_data->field_parent_menu[0]['value'];
      if($tree[$branch_id]['link']['mlid'] == $parent_menu_id) {
        $tree[$branch_id]['link']['classes_array'][] = 'active-trail';
        $tree[$branch_id]['link']['classes_array'][] = 'active';
        $tree[$branch_id]['link']['active_item'] = TRUE;
        $tree[$branch_id]['link']['in_active_trail'] = TRUE;
      }
    }
    if(arg(0) == 'media' && $tree[$branch_id]['link']['mlid'] == '1315') {
        $tree[$branch_id]['link']['classes_array'][] = 'active-trail';
        $tree[$branch_id]['link']['classes_array'][] = 'active';
        $tree[$branch_id]['link']['active_item'] = TRUE;
        $tree[$branch_id]['link']['in_active_trail'] = TRUE;
    }
    if ($cnt == 1) {
      $tree[$branch_id]['link']['classes_array'][] = 'first';
    }
    if ($cnt == $max) {
      $tree[$branch_id]['link']['classes_array'][] = 'last';
    }

    if(!empty($tree[$branch_id]['link']['localized_options']['attributes']['class'])) {
      $tree[$branch_id]['link']['classes_array'][] = $tree[$branch_id]['link']['localized_options']['attributes']['class'];
    }

    $zebra = ($zebra == 'odd') ? 'even' : 'odd';
    $cnt++;
    if (!empty($branch['below'])) {
      $child_trimmed = saic_menu_tree_add_classes($tree[$branch_id]['below']);
    }
  }
}


/**
 * Apply Theme Hooks to the branches.
 *
 * Returns themed tree.
 */
function saic_menu_tree_branch_theme(&$tree, $config, $below = NULL) {
  $content = NULL;
  foreach ($tree as $branch_id => $branch) {
    $branch_content = NULL;
    $hooks = array(
      'saic_menu_block_item__' . preg_replace('/-/', '_', $config['menu_delta']),
      'saic_menu_block_item__' . preg_replace('/-/', '_', $config['menu_name']),
      'saic_menu_block_item'
    );
    if (!empty($branch['below'])) {
      $branch_content = saic_menu_tree_branch_theme($tree[$branch_id]['below'], $config, $below);
    }
    $tree[$branch_id]['link']['content'] = theme($hooks, $tree[$branch_id]['link'], $config, $branch_content);
    $content .= $tree[$branch_id]['link']['content'];
  }
  return $content;
}


/**
 * Helper function
 *
 * Sets active/max/min values in prune actions where applicable
 */
function saic_menu_tree_prune_eval_actions(&$config) {
  $variables = array(
    'active'  => $config['link_depth'],
    'max'     => $config['tree_depth'],
    'min'     => 0,
  );
  foreach ($config['prune']['actions'] as $action => $options) {
    // Initialize temporary 'eval'
    $tmp_eval = array();
    // Loop through the actions and build 'eval'
    foreach ($options as $operator => $value) {
      // Check for variables in value
      if (preg_match('/(active|max|min)/', $value)) {
        foreach ($variables as $variable => $var) {
          $value = preg_replace('/'.$variable.'/', $var, $value);
        }
      }
       
      // Prepend 'current' to value if the value contains an operator.
      $value = (preg_match('/^(\+\-)/', $value)) ? ('current' . $value) : $value;
      // Append to eval
      $tmp_eval[] = implode(' ', array('current', $operator, $value));
    }
    $config['prune']['actions'][$action]['eval'] = 'return (' . implode(' && ', $tmp_eval) . ') ? TRUE : FALSE;';
  }
}


/**
 * Find the total depth of menu.
 */
function saic_menu_get_depth(&$tree, $depth = 1) {
  if (is_array($tree)) {
    foreach ($tree as $branch) {
      if (is_array($branch)) {
        if (is_array($branch['below'])) {
          $depth = (int)max($depth, $branch['link']['depth'], saic_menu_get_depth($branch['below'], $depth));
        }
        else {
          $depth = (int)max($depth, $branch['link']['depth']);
        }
      }
    }
    return $depth;
  }
}

