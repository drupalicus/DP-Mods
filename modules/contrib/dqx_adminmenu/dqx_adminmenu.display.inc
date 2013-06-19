<?php
/*
 * This file contains the plugins for table- and tab-style submenus.
 */


class _dqx_adminmenu_MenuTree {
  protected $_submenus;
  protected $_items;

  function __construct(array $submenus, array $items) {
    $this->_submenus = $submenus;
    $this->_items = $items;
  }

  function renderMenu($parent_path) {
    return $this->_renderSubmenu($parent_path, $ul_attr);
  }

  function pathAccess($path) {
    $item = $this->_items[$path];
    if ($item && isset($item['access'])) {
      return $item['access'];
    }
    else {
      $router_item = menu_get_item($path);
      return $router_item['access'];
    }
  }

  function getItem($key) {
    return isset($this->_items[$key]) ? $this->_items[$key] : NULL;
  }

  function getSubmenu($key) {
    return isset($this->_submenus[$key]) ? $this->_submenus[$key] : NULL;
  }

  protected function _renderSubmenu($parent_path) {
    $html = '';
    $submenu = $this->_submenus[$parent_path];
    if (is_object($submenu)) {
      return $submenu->render($this);
    }
    else if (is_array($submenu)) {

      $sort = array();
      $pieces = array();
      foreach ($submenu as $k => $path) {
        if ($item = $this->_items[$path]) {

          // late access check
          if (!isset($item['access'])) {
            $router_item = menu_get_item($item['link_path']);
            $item['access'] = $router_item['access'];
          }

          $subtree_html = $this->_renderSubmenu($path);

          $options = $item['localized_options'];
          $options = is_array($options) ? $options : array();

          $link_attr = dqx_adminmenu_link_attributes($item['link_path'], $options);
          $li_attr = dqx_adminmenu_extract_attributes($item, 'item_attributes');

          if (!$item['access']) {
            if (!$subtree_html) {
              continue;
            }
            // no access, but still want to reveal some of the subtree items
            $li_attr->addClass('no-access');
            $link_attr->addClass('no-access');
            $link_attr->removeAttribute('href');
          }

          if ($subtree_html) {
            $li_attr->addClass('expandable');
            $link_attr->addClass('expandable');
          }

          $sort[$k] = (50000 + $item['weight']) .' '. $item['title'];

          $link_html = $link_attr->A($item['title'], $options['html']);
          $pieces[$k] = $li_attr->LI($link_html . $subtree_html);
        }
      }
      array_multisort($sort, $pieces);
    }
    $ul_attr = dqx_adminmenu_extract_attributes($this->_items[$parent_path], 'submenu_attributes');
    if (count($pieces)) {
      return $ul_attr->UL(implode('', $pieces));
    }
    else {
      return '';
    }
  }
}


/**
 * This only makes sense in combination with admin_views.
 * I recommend this module anyway, so we assume that it is enabled.
 */
class _dqx_adminmenu_ContentTablePlugin {

  protected function _getColumns() {
    $cols = array();
    $cols['list'] = 'List';
    $cols['create'] = 'Create';
    if (user_access('administer content types')) {
      $cols['submenu'] = '';
    }
    return $cols;
  }

  protected function _buildMatrix(array $types, array &$cols, _dqx_adminmenu_MenuTree $tree) {
    $cols_cellcount = array();
    $matrix = array();
    foreach ($types as $type) {
      $type->slug = str_replace('_', '-', $type->type);
      $type->attr = dqx_adminmenu_class_attribute('node-type node-type-'. $type->type);
      foreach ($cols as $key => $title) {
        $method = '_cell__'. $key;
        if ($key === 'space') {
          $matrix[$type->type]['space'] = '';
        }
        else if (method_exists($this, $method)) {
          $cell = $this->$method($type, $tree);
          if ($cell) {
            ++ $cols_cellcount[$key];
            $matrix[$type->type][$key] = $cell;
          }
        }
      }
    }
    foreach ($cols_cellcount as $key => $count) {
      if (!$count) {
        unset($cols[$key]);
      }
    }
    $keys_reverse = array_reverse(array_keys($cols));
    if ($keys_reverse[0] === 'space') {
      unset($cols['space']);
    }
    if ($keys_reverse[0] === 'submenu' && $keys_reverse[1] === 'space') {
      unset($cols['space']);
    }
    return $matrix;
  }

  protected function _renderHeader(array $cols) {
    $html = '';
    foreach ($cols as $key => $title) {
      if ($key === 'submenu') {
        $html .= '<td class="td-submenu"></td>';
      }
      else {
        $html .= '<td class="no-link">'. $title .'</td>';
      }
    }
    return '<thead><tr>'. $html .'</tr></thead>';
  }

  protected function _renderFooter(array $cols, _dqx_adminmenu_MenuTree $tree) {
    if ($tree->pathAccess('admin/content/types/add')) {
      $link = l('Add type', 'admin/content/types/add');
      $row = '<td class="no-link"></td><td class="admin-content-type-add">' . $link . '</td>';
      if (count($cols) > 2) {
        $row .= '<td class="td-submenu"></td>';
      }
      $space_row = '<td class="no-link" colspan="' . count($cols) . '">&nbsp;</td>';
      return '<tfoot><tr class="space">' . $space_row . '</tr><tr>' . $row . '</tr></tfoot>';
    }
  }

  function render(_dqx_adminmenu_MenuTree $tree) {
    $cols = $this->_getColumns();
    $types = array();
    foreach (node_get_types() as $type) {
      $types[$type->type] = clone $type;
    }

    $matrix = $this->_buildMatrix($types, $cols, $tree);

    $html = '';
    foreach ($types as $type) {
      $row_html = '';
      foreach ($cols as $key => $title) {
        $class = 'td-'. $key;
        $cell = $matrix[$type->type][$key];
        $row_html .= '<td class="'. $class .'">'. $cell .'</td>';
      }
      $html .= $type->attr->TR($row_html);
    }
    $tbody = '<tbody>'. $html .'</tbody>';

    $thead = $this->_renderHeader($cols);
    $tfoot = $this->_renderFooter($cols, $tree);
    return '<table>'. $thead . $tfoot . $tbody .'</table>';
  }

  protected function _cell__list($type) {
    $q = db_query("SELECT COUNT(nid) n FROM {node} WHERE type = '%s'", $type->type);
    if ($row = db_fetch_object($q)) {
      $title = '<span class="node-count">' . $row->n . '</span>';
    }
    else {
      $title = 'list';
    }
    return l($title, 'admin/content/node', array(
      'query' => array('type' => $type->type),
      'html' => TRUE,
    ));
  }

  protected function _cell__create($type) {
    return l('<strong>'. $type->name .'</strong>', 'node/add/' . $type->slug, array('html' => TRUE));
  }

  protected function _cell__configure($type) {
    return l('conf', 'admin/content/node-type/' . $type->slug);
  }

  protected function _cell__fields($type) {
    return l('fields', 'admin/content/node-type/' . $type->slug .'/fields');
  }

  protected function _cell__display($type) {
    return l('display', 'admin/content/node-type/' . $type->slug .'/display');
  }

  protected function _cell__submenu($type, $tree) {
    $submenu_key = 'admin/content/node-type/' . $type->slug;
    $submenu = $tree->renderMenu($submenu_key);
    if ($submenu) {
      $type->attr->addClass('expandable');
      return '<div>' . $submenu . '</div>';
    }
  }
}


class _dqx_adminmenu_DisplayFieldsTablePlugin {

  protected $_type;
  protected $_typePath;
  protected $_displayPath;
  protected $_ndPath;

  function __construct($type) {
    $this->_type = $type;
    $this->_typePath = 'admin/content/node-type/'. str_replace('_', '-', $type->type);
    $this->_displayPath = $type_path .'/display';
    $this->_ndPath = 'admin/build/ds/layout/'. str_replace('_', '-', $type->type);
  }

  function render(_dqx_adminmenu_MenuTree $tree) {
    $type_path = 'admin/content/node-type/'. str_replace('_', '-', $this->_type->type);
    $nd_root = 'admin/build/ds/layout/'. str_replace('_', '-', $this->_type->type);
    $cck_root = $type_path . '/display';
    $all_build_modes = ds_get_build_modes(NULL, TRUE);
    $build_modes = $all_build_modes['nd'];
    if (!empty($build_modes)) {
      $exclude_matrix = variable_get('nd_buildmodes_exclude', array());
      $excluded_build_modes = $exclude_matrix[$this->_type->type];

      $nd_items = array();
      $cck_item_groups = array();
      foreach ($build_modes as $key => $build_mode) {
        $cck_path = $this->_cckBuildModePath($key, $type_path);
        $nd_item_groups[$cck_path][$key] = $tree->getItem($nd_root .'/'. $key);
      }

      $html = '';
      foreach ($nd_item_groups as $cck_path => $nd_items) {
        $cck_item = $tree->getItem($cck_path);
        $options = is_array($cck_item['localized_options']) ? $cck_item['localized_options'] : array();
        $cck_link = $cck_item ? l('cck', $cck_item['link_path'], $options) : '';
        $rowspan = count($nd_items);
        $tbody = '';
        $cck_cell = '<td class="dqx_adminmenu-display-cck" rowspan="'. $rowspan .'">'. $cck_link .'</td>';
        foreach ($nd_items as $key => $nd_item) {
          // Check if build mode is excluded for this object type.
          $tr_attr = dqx_adminmenu_tag_attributes();
          $excluded = TRUE && isset($exclude_build_modes[$key]) && ($exclude_build_modes[$key] == TRUE);
          if ($excluded) {
            $tr_attr->addClass('nd-excluded');
          }
          $options = is_array($nd_item['localized_options']) ? $nd_item['localized_options'] : array();
          $nd_link = $nd_item ? l($nd_item['title'], $nd_item['link_path'], $options) : '';
          $tbody .= '<tr>'. $cck_cell .'<td class="dqx_adminmenu-display-nd">'. $nd_link .'</td></tr>';
          $cck_cell = '';
        }
        $html .= '<tbody>' . $tbody . '</tbody>';
      }

      $thead = '<thead><tr><td class="no-link">CCK</td><td class="no-link">Display Suite (nd)</td></tr></thead>';
      return '<table class="dqx_adminmenu-table">' . $thead . $html . '</table>';
    }
  }

  protected function _cckBuildModePath($nd_key, $type_path) {
    if (is_numeric($nd_key) || $nd_key === 'sticky') {
      return $type_path .'/display/nd';
    }
    else if ($nd_key === 'full' || $nd_key === 'teaser') {
      return $type_path .'/display';
    }
    else {
      return $type_path .'/display/'. $nd_key;
    }
  }
}


function dqx_adminmenu_link_attributes($path, array $options) {
  $obj = dqx_adminmenu_extract_attributes($options, 'attributes', FALSE);
  $obj->setAttribute('href', url($path, $options));
  return $obj;
}


function dqx_adminmenu_extract_attributes(array $info_array, $array_key, $raw = TRUE) {
  $attr = array();
  if (is_array($info_array[$array_key])) {
    $attr = $info_array[$array_key];
  }
  return dqx_adminmenu_tag_attributes($attr, $raw);
}


function dqx_adminmenu_tag_attributes($attr = NULL, $raw = TRUE) {
  if (is_object($attr)) {
    return $attr;
  }
  else {
    $obj = new dqx_adminmenu_HtmlTagAttributes();
    if (is_array($attr)) {
      $obj->setAttributes($attr, $raw);
      if (isset($attr['class'])) {
        $obj->addClasses($attr['class']);
      }
    }
    return $obj;
  }
}


function dqx_adminmenu_class_attribute($classes) {
  if (!is_object($classes)) {
    $attr = new dqx_adminmenu_HtmlTagAttributes();
    $attr->addClasses($classes);
    return $attr;
  }
  else {
    // assume that it is already a TagAttributes object
    return $classes;
  }
}


class dqx_adminmenu_HtmlTagAttributes {
  protected $_attributes = array();
  protected $_classes = array();

  function setAttribute($key, $value, $raw = TRUE) {
    $this->_attributes[$key] = $raw ? $value : check_plain($value);
  }

  function unsetAttribute($key) {
    unset($this->_attributes[$key]);
  }

  function setAttributes(array $values, $raw = TRUE) {
    foreach ($values as $key => $value) {
      $this->_attributes[$key] = $raw ? $value : check_plain($value);
    }
  }

  function addClass($class) {
    $this->_classes[$class] = $class;
  }

  function addClassIf($cond, $class) {
    if ($cond) {
      $this->_classes[$class] = $class;
    }
  }

  function addClasses($classes) {
    if (!is_array($classes)) {
      $classes = explode(' ', $classes);
    }
    foreach ($classes as $class) {
      if ($class) {
        $this->_classes[$class] = $class;
      }
    }
  }

  function addClassesIf(array $classes_if) {
    foreach ($classes_if as $class => $cond) {
      if ($cond) {
        $this->_classes[$class] = $class;
      }
    }
  }

  function hasClass($class) {
    return isset($this->_classes[$class]);
  }

  function removeClass($class) {
    unset($this->_classes[$class]);
  }

  function getAttributes() {
    if (!empty($this->_classes)) {
      $this->_attributes['class'] = implode(' ', $this->_classes);
    }
    else {
      unset($this->_attributes['class']);
    }
    return $this->_attributes;
  }

  function __toString() {
    $t = '';
    foreach ($this->getAttributes() as $key => $value) {
      $t .= ' '. $key .'="'. $value .'"';
    }
    return $t;
  }

  function renderTag($tagname, $content = NULL, $raw = TRUE) {
    if (isset($content)) {
      if (!$raw) {
        $content = check_plain($content);
      }
      return '<'. $tagname . $this->__toString() .'>'. $content .'</'. $tagname .">\n";
    }
    else {
      return '<'. $tagname . $this->__toString() .' />';
    }
  }

  function __call($tagname, $args) {
    if (preg_match('/^[A-Z]+$/', $tagname)) {
      list($content, $raw) = $args + array(NULL, TRUE);
      $tagname = strtolower($tagname);
      return $this->renderTag($tagname, $content, $raw);
    }
  }
}





