<?php


/**
 * Page callback for js/admin_menu/cache
 * Output administration menu for HTTP caching via AJAX request.
 */
function dqx_adminmenu_json() {
  if (!user_access('use dqx_adminmenu')) {
    $js = <<<EOT
      alert('dqx_adminmenu access denied.');
EOT;
  }
  else if ($GLOBALS['user']->uid != $_GET['uid']) {
    $uid_session = $GLOBALS['user']->uid;
    $uid_request = $_GET['uid'];
    $js = <<<EOT
      alert('dqx_adminmenu access denied. $uid_session != $uid_request.');
EOT;
  }
  else {
    $cid = 'dqx_adminmenu:json:' . $GLOBALS['user']->uid . ':' . $GLOBALS['language']->language;
    $timestamp = variable_get('dqx_adminmenu_timestamp', 0);
    $cache = cache_get($cid)->data;
    if (!is_array($cache) || $cache['timestamp'] != $timestamp) {
      $json = _dqx_adminmenu_json();
      $cache = array('timestamp' => $timestamp, 'json' => $json);
      cache_set($cid, $cache, 'cache', CACHE_TEMPORARY);
    }
    else {
      $json = $cache['json'];
    }
  }

  header("Content-type: application/json");
  header("Cache-Control: ''");  // HTTP/1.1
  $expires = date('D, d M Y H:i:s GMT', time() + 3600 * 24 * 2);  // two days ahead
  header("Expires: $expires");

  print $json;

  exit();
}


function _dqx_adminmenu_json() {
  $html = _dqx_adminmenu_router_tree_html();

  $html = !$html ? '' : <<<EOT
    <div id="dqx_adminmenu">$html</div>
EOT;

  $json = json_encode(array('html' => trim($html)));

  return $json;
}


/**
 * Page callback for admin/dqx_adminmenu-data.js
 */
function dqx_adminmenu_js() {
  if (!user_access('use dqx_adminmenu')) {
    $js = <<<EOT
      alert('dqx_adminmenu access denied.');
EOT;
  }
  else if ($GLOBALS['user']->uid != $_GET['uid']) {
    $uid_session = $GLOBALS['user']->uid;
    $uid_request = $_GET['uid'];
    $js = <<<EOT
      alert('dqx_adminmenu access denied. $uid_session != $uid_request.');
EOT;
  }
  else {
    $cid = 'dqx_adminmenu:' . $GLOBALS['user']->uid . ':' . $GLOBALS['language']->language;
    $timestamp = variable_get('dqx_adminmenu_timestamp', 0);
    $cache = cache_get($cid)->data;
    if (!is_array($cache) || $cache['timestamp'] != $timestamp) {
      $js = _dqx_adminmenu_js();
      $cache = array('timestamp' => $timestamp, 'js' => $js);
      cache_set($cid, $cache, 'cache', CACHE_TEMPORARY);
      $js = <<<EOT
        // DQX AdminMenu Data (not from cache)
        $js
EOT;
    }
    else {
      $js = $cache['js'];
      $js = <<<EOT
        // DQX AdminMenu Data (from cache)
        $js
EOT;
    }
  }

  header("Content-type: text/javascript");
  header("Cache-Control: ''"); // HTTP/1.1
  $expires = date('D, d M Y H:i:s GMT', time() + 3600 * 24 * 2);  // two days ahead
  header("Expires: $expires");

  print $js;

  exit();
}


function _dqx_adminmenu_js() {
  $html = _dqx_adminmenu_router_tree_html();

  $html = !$html ? '' : <<<EOT
  <div id="dqx_adminmenu-wrapper">
    <div id="dqx_adminmenu">$html</div>
  </div>
EOT;

  $json = json_encode(trim($html));

  return <<<EOT
    $(function(){
      var divRoot = $($json);
      $('body').prepend(divRoot);
      Drupal.dqx_adminmenu.init(divRoot);
    });
EOT;
}


function _dqx_adminmenu_router_tree_items() {
  $q = db_query("
    SELECT *
    FROM {menu_router}
    WHERE
      title != ''  AND
      (path LIKE '%s'  OR  path LIKE '%s'  OR  path = 'node/add'  OR  path = 'admin'  OR path = 'civicrm')
    ORDER BY weight ASC, title ASC
  ", 'admin/%', 'node/add/%');

  $items = array();
  $paths = array();
  $callback_items = array();
  while ($item = db_fetch_array($q)) {
    if (!strpos($item['path'], '%')) {
      if ($item['type'] & (MENU_VISIBLE_IN_TREE | MENU_IS_LOCAL_TASK)) {
        $item = _dqx_adminmenu_build_menu_item($item);
        $item['options'] = serialize($item['options']);
        $items[$item['path']] = $item;
        $paths[$item['path']] = $item['path'];
      }
      elseif ($item['type'] & MENU_VISIBLE_IN_BREADCRUMB && $item['number_parts'] > 2) {
        $callback_items[] = $item;
      }
    }
  }

  $parent_map =  _dqx_adminmenu_parent_map();
  foreach ($callback_items as $item) {
    $parent = substr($item['path'], 0, strrpos($item['path'], '/'));
    if (isset($parent_map[$parent])) {
      $parent = $parent_map[$parent];
    }
    if (!empty($items[$parent])) {
      $item = _dqx_adminmenu_build_menu_item($item);
      $item['options'] = serialize($item['options']);
      $items[$item['path']] = $item;
      $paths[$item['path']] = $item['path'];
    }
  }

  return $items;
}


function _dqx_adminmenu_parent_map() {
  $parent_map = array(
    'node' => 'admin/content',
    'admin/content/node-type' => 'admin/content/types',
    'admin/build/menu-customize' => 'admin/build/menu/list',
  );
  return $parent_map;
}


function dqx_adminmenu_build_items() {

  $items = _dqx_adminmenu_router_tree_items();

  unset($items['admin/by-module']);
  unset($items['admin/by-task']);
  unset($items['admin/compact']);

  _dqx_adminmenu_items_check_access($items);


  // add additional items..

  $icon_items = _dqx_adminmenu_icon_items();
  $user_items = _dqx_adminmenu_user_items();
  $menu_editor_items = _dqx_adminmenu_menu_editor_items();
  $items = array_merge($icon_items, $user_items, $items, $menu_editor_items);

  // add special items

  $items['admin/node-types'] = $items['node/add'];
  $items['admin/node-types']['weight'] = -9;

  if (module_exists('civicrm')) {
    $items['admin/civicrm'] = $items['civicrm'];
  }

  // change weights and titles
  $items['admin/node-types']['title'] = t('Node');
  $items['node/add']['weight'] = 0;
  $items['admin/build']['weight'] = -8;
  $items['admin/build']['title'] = t('Build');
  $items['admin/content']['title'] = t('Content');
  $items['admin/settings']['title'] = t('Configure');
  $items['admin/user']['title'] = t('People');

  return $items;
}


function dqx_adminmenu_build_structure(array $paths) {
  // Normally, we determine the parent of an item by chopping off the last path fragment.
  // Some items should have a parent different from that.
  $parent_map = _dqx_adminmenu_parent_map();

  if (module_exists('civicrm')) {
    $parent_map['civicrm'] = 'admin/civicrm';
  }

  $paths = array_combine($paths, $paths);

  $submenus = array();
  foreach ($paths as $path => $type) {
    _dqx_adminmenu_path_multisplit($submenus, $path, $parent_map + $paths);
  }

  $submenus['admin/node-types'] = $submenus['node/add'];

  return $submenus;
}


function _dqx_adminmenu_router_tree_html() {

  $items = dqx_adminmenu_build_items();

  $submenus = dqx_adminmenu_build_structure(array_keys($items));

  _dqx_adminmenu_alter_structure($items, $submenus);

  // alter the structure..

  module_load_include('display.inc', 'dqx_adminmenu');

  foreach (node_get_types() as $type) {
    $type_path = 'admin/content/node-type/' . str_replace('_', '-', $type->type);
    $fields_path = $type_path . '/fields';
    $display_path = $type_path . '/display';
    $nd_path = 'admin/build/ds/layout/' . str_replace('_', '-', $type->type);
    if (is_array($submenus[$type_path])) {
      if (module_exists('nd')) {
        $submenus[$display_path] = new _dqx_adminmenu_DisplayFieldsTablePlugin($type);
      }
      $items[$type_path]['submenu_attributes']['class'] = 'dqx_adminmenu-node-type';
      foreach ($submenus[$type_path] as $path) {
        switch ($path) {
          case $type_path . '/edit':
            $items[$path]['title'] = t('Edit type');
            // $items[$path]['title'] = $items[$type_path]['title'];
            $items[$path]['weight'] = 5;
            $items[$path]['item_attributes']['class'] = 'dqx_adminmenu-inline';
            $items[$path]['submenu_attributes']['class'] = 'dqx_adminmenu-inline';
            break;
          case $type_path . '/display':
            $items[$path]['title'] = 'Display';
            $items[$path]['weight'] = 10;
            $items[$path]['localized_options']['attributes']['class'] .= ' bold';
            break;
          case $type_path . '/fields':
            $items[$path]['title'] = t('Fields (!count)', array('!count' => count($submenus[$fields_path])));
            $items[$path]['weight'] = 15;
            $items[$path]['item_attributes']['class'] = 'dqx_adminmenu-inline';
            $items[$path]['submenu_attributes']['class'] = 'dqx_adminmenu-inline';
            break;
          default:
            // move one level deeper..
            $submenus[$type_path . '/edit'][$path] = $path;
            unset($submenus[$type_path][$path]);
        }
      }
    }
  }

  $submenus['admin/node-types'] = new _dqx_adminmenu_ContentTablePlugin();

  if (module_exists('nd') && FALSE) {
    foreach (node_get_types() as $type) {
      $nd_path = 'admin/build/ds/layout/' . str_replace('_', '-', $type->type);
      $type_path = 'admin/content/node-type/' . str_replace('_', '-', $type->type);
      $items[$type_path . '/nd'] = $items[$nd_path];
      $submenus[$type_path][$type_path . '/nd'] = $type_path . '/nd';
      $submenus[$type_path . '/nd'] = $submenus[$nd_path];
      $items[$type_path . '/nd']['title'] = 'Layout (ds)';
      $items[$type_path . '/nd']['link_title'] = 'Layout (ds)';
    }
  }

  $items['admin']['submenu_attributes']['id'] = 'dqx_adminmenu-admin';
  $items['dqx-adminmenu-user']['submenu_attributes']['id'] = 'dqx_adminmenu-user';

  $treeObject = new _dqx_adminmenu_MenuTree($submenus, $items);

  $ul_tree = $treeObject->renderMenu('admin');
  $ul_user = $treeObject->renderMenu('dqx-adminmenu-user');

  if ($ul_tree) {
    return $ul_user . $ul_tree;
  }
}


function _dqx_adminmenu_build_menu_item($item) {
  if ($item['type'] == MENU_CALLBACK) {
    $item['hidden'] = -1;
  }
  elseif ($item['type'] == MENU_SUGGESTED_ITEM) {
    $item['hidden'] = 1;
  }
  $item['module'] = 'adminmneu';
  $item += array(
    'menu_name' => 'dqx_adminmenu',
    'link_title' => $item['title'],
    'link_path' => $item['path'],
    'hidden' => 0,
    'options' => empty($item['description']) ? array() : array(
      'attributes' => array('title' => $item['description'])
    ),

    'router_path' => $item['path'],

    // this is taken from menu_item_save().
    'weight' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'customized' => 0,
    'updated' => 0,
  );
  return $item;
}


function _dqx_adminmenu_items_check_access(&$items) {
  foreach ($items as $path => &$item) {
    _menu_link_translate($item);
  }
  // Sort siblings in the tree based on the weights and localized titles.
  // ksort($new_tree);
}


function _dqx_adminmenu_path_multisplit(array &$multisplit, $path, array $prefix_map) {
  $fragments = explode('/', $path);
  $n = count($fragments);

  $i=1;
  $suffix = array_pop($fragments);
  while ($fragments) {
    $prefix = implode('/', $fragments);
    if (isset($prefix_map[$prefix])) {
      $prefix = $prefix_map[$prefix];
      $multisplit[$prefix][$path] = $path;
      return;
    }
    $suffix = array_pop($fragments) . '/' . $suffix;
    ++$i;
  }

  $multisplit[NULL][$path] = $path;
}





/**
 * Build user/action links; mostly account information and links.
 *
 * @see theme_admin_menu_links()
 */
function _dqx_adminmenu_user_items() {
  if (!$GLOBALS['user']->uid) {
    // Not logged in.
    // Anonymous is not supposed to get access to the dqx_adminmenu,
    // but let's do something safe nevertheless.
    return array();
  }
  // dummy parent item
  $items['dqx-adminmenu-user'] = array();
  $items['dqx-adminmenu-user/counter'] = array(
    'title' => _dqx_adminmenu_get_user_count(),
    'weight' => -90,
    'localized_options' => array('attributes' => array(
      'id' => 'dqx_adminmenu-user-counter',
      'title' => t('Current anonymous / authenticated users'),
    )),
    'link_path' => (user_access('administer users') ? 'admin/user/user' : 'user'),
    'access' => TRUE,
  );
  $items['dqx-adminmenu-user/account'] = array(
    'title' => $GLOBALS['user']->name,
    'weight' => -99,
    'localized_options' => array(
      'attributes' => array('id' => 'dqx_adminmenu-user-account'),
    ),
    'link_path' => 'user/' . $GLOBALS['user']->uid,
    'access' => TRUE,
  );
  $items['dqx-adminmenu-user/logout'] = array(
    'title' => t('Log out'),
    'weight' => -100,
    'attributes' => array('id' => 'dqx_adminmenu-user-logout'),
    'link_path' => 'logout',
    'access' => TRUE,
  );

  return $items;
}


function _dqx_adminmenu_get_user_count() {
  $interval = time() - variable_get('user_block_seconds_online', 900);
  $count_anon = sess_count($interval);
  $count_auth = db_result(db_query("SELECT COUNT(DISTINCT uid) FROM {sessions} WHERE uid > 0 AND timestamp >= %d", $interval));

  return t('@count-anon / @count-auth', array('@count-anon' => $count_anon, '@count-auth' => $count_auth));
}



/**
 * Build icon menu links; mostly containing maintenance helpers.
 *
 * @see theme_admin_menu_links()
 */
function _dqx_adminmenu_icon_items() {

  $icon_src = theme_get_setting('toggle_favicon') ? theme_get_setting('favicon') : base_path() . 'misc/favicon.ico';
  $icon_img = '<img id="dqx_adminmenu-icon-img" src="' . $icon_src . '" width="16" height="16" alt="' . t('Home') . '" />';

  $items = array();
  $items['admin/dqx-adminmenu'] = array(
    'title' => $icon_img,
    'access' => TRUE,  // everyone should see the front page
    'weight' => -100,
    'link_path' => '<front>',
    'localized_options' => array(
      'attributes' => array('id' => 'dqx_adminmenu-icon-link'),
      'html' => TRUE,
    ),
  );
  // Add link to manually run cron.
  $items['admin/dqx-adminmenu/cron'] = array(
    'title' => t('Run cron'),
    'weight' => 50,
    'access' => user_access('administer site configuration'),
    'link_path' => 'admin/reports/status/run-cron',
  );
  // Add link to run update.php.
  $items['admin/dqx-adminmenu/update'] = array(
    'title' => t('Run updates'),
    'weight' => 50,
    'access' => ($GLOBALS['user']->uid == 1 || !empty($GLOBALS['update_free_access'])),
    'link_path' => base_path() . 'update.php',
    'localized_options' => array(
      'external' => TRUE,
    ),
  );
  // Add items to flush caches.
  $items['admin/dqx-adminmenu/flush-cache'] = array(
    'title' => t('Flush all caches'),
    'weight' => 20,
    // @todo Add permission to flush cashes.
    'access' => user_access('administer site configuration'),
    'link_path' => 'admin/dqx-adminmenu/flush-cache',
    'localized_options' => array(
      'attributes' => array('class' => 'dqx_adminmenu-redirect'),
    ),
  );
  $caches = array(
    // 'admin_menu' => t('Administration menu'),
    'cache' => t('Cache tables'),
    'menu' => t('Menu'),
    'requisites' => t('Page requisites'),
    'theme' => t('Theme registry'),
  );
  foreach ($caches as $arg => $title) {
    $items['admin/dqx-adminmenu/flush-cache/' . $arg] = array(
      'title' => $title,
      'link_path' => 'admin/dqx-adminmenu/flush-cache/' . $arg,
      'localized_options' => array(
        'attributes' => array('class' => 'dqx_adminmenu-redirect'),
      ),
      'access' => user_access('administer site configuration'),
    );
  }
  // Add link to toggle developer modules (performance).
  $saved_state = variable_get('admin_menu_devel_modules_enabled', NULL);
  $items['admin/dqx-adminmenu/toggle-modules'] = array(
    'title' => isset($saved_state) ? t('Enable developer modules') : t('Disable developer modules'),
    'weight' => 88,
    'access' => user_access('administer site configuration'),
    'link_path' => 'admin/dqx-adminmenu/toggle-modules',
    'localized_options' => array(
      'attributes' => array('class' => 'dqx_adminmenu-redirect'),
    ),
  );

  // Add Devel module links.
  if (module_exists('devel')) {
    // Add variable editor.
    $items['admin/dqx-adminmenu/devel-variables'] = array(
      'title' => t('Variable editor'),
      'weight' => 20,
      'access' => user_access('access devel information'),
      'link_path' => 'devel/variable',
    );
  }

  return $items;
}


function _dqx_adminmenu_menu_editor_items() {
  $items = array();
  if (module_exists('menu_editor')) {
    $q = db_query("SELECT * FROM {menu_custom} ORDER BY title");
    while ($menu = db_fetch_array($q)) {
      $path = 'admin/build/menu-customize/' . $menu['menu_name'] . '/poweredit';
      $items[$path] = array(
        'title' => $menu['title'],
        'link_path' => $path,
        'weight' => 100,
      );
    }
  }
  return $items;
}


function _dqx_adminmenu_alter_structure(&$items, &$submenus) {

}


class dqx_adminmenu_StructureAlterWrapper {

  protected $_items;
  protected $_submenus;

  function __construct(&$items, &$submenus) {
    $this->_items = &$items;
    $this->_submenus = &$submenus;
  }

  function addItem($key, $item) {
    $this->_items[$key] = $item;
  }
}





