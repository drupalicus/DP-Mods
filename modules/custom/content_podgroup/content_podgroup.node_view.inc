<?php
// $Id$
/**
 * @file
 * Theming functionality for pod groups.
 */

/**
 * Implementation of hook_fieldgroup_view().
 */
function _content_podgroup_fieldgroup_view(&$node, &$element, $group, $context) {
  static $cache = array();
  $key = md5($node->nid . '||' . implode('-', array_keys($element)) . '||' . $group['group_name'] . '-' . $group['type_name'] . '||' . $context);

  if (isset($cache[$key])) {
    $node = drupal_clone($cache[$key]['node']);
    $element = $cache[$key]['element'];
  }
  else {
    drupal_add_css(drupal_get_path('module', 'content_podgroup') .'/content_podgroup.css');

    // Setup variables for easier access.
    $node_copy = drupal_clone($node);
    $group_name = $group['group_name'];
    $group_class = 'content-podgroup-'. str_replace('_', '-', $group_name);
    $subgroup_settings = isset($group['settings']['podgroup']['subgroup']) ? $group['settings']['podgroup']['subgroup'] : array();
    $show_label = isset($subgroup_settings['label']) ? $subgroup_settings['label'] : 'above';
    $subgroup_labels = isset($group['settings']['podgroup']['labels']) ? $group['settings']['podgroup']['labels'] : array();
    $subgroup_format = isset($subgroup_settings[$context]['format']) ? $subgroup_settings[$context]['format'] : 'fieldset';
    $content_type = content_types($group['type_name']);

    // Build list of accessible fields in this group.
    $group_fields = array();
    foreach ($content_type['fields'] as $field_name => $field) {
      if (isset($group['fields'][$field_name]) && isset($element[$field_name])) {
        if (!isset($element[$field_name]['#access']) || $element[$field_name]['#access']) {
          $group_fields[$field_name] = $field;
        }
      }
    }

    // Compute unique deltas from all deltas used by fields in this podgroup.
    $group_deltas = array();
    foreach (array_keys($group_fields) as $field_name) {
      if (is_array($node->content[$field_name]['field']['items'])) {
        foreach (array_keys($node->content[$field_name]['field']['items']) as $delta) {
          $group_deltas[$delta] = $delta;
        }
      }
    }
    sort($group_deltas);

    foreach ($group_deltas as $index => $delta) {

      $element[$delta] = array(
        '#title' => ($show_label == 'above' && !empty($subgroup_labels[$index]) ? check_plain(t($subgroup_labels[$index])) : ''),
        '#attributes' => array('class' => 'content-podgroup-wrapper content-podgroup-'. $index . '-' . $delta),
        '#weight' => $delta,
        '#delta' => $delta,
      );

      foreach (array_keys($group_fields) as $field_name) {
        if (isset($node->content[$field_name])) {
          $node_copy->content[$field_name]['field']['items'] = array(
            1 => isset($node->content[$field_name]['field']['items'][$delta]) ? $node->content[$field_name]['field']['items'][$delta] : NULL,
          );
          $element[$delta][$field_name] = $node_copy->content[$field_name];
          $element[$delta][$field_name]['#delta'] = $delta;
        }
      }

      $element['#attributes']['class'] = $group_class;
      $element[$delta]['#type'] = 'content_podgroup';
      $element[$delta]['#group_name'] = $group_name;
      $element[$delta]['#fields'] = $group_fields;

      // Unset the original group field values now that we've moved them.
      foreach (array_keys($group_fields) as $field_name) {
        if (isset($element[$field_name])) {
          unset($element[$field_name]);
        }
      }
    }
    $cache[$key] = array('node' => drupal_clone($node), 'element' => $element);
  }
}

/**
 * Preprocess function for podgroups.
 */
function template_preprocess_content_podgroup(&$vars) {
  $element = $vars['element'];
  $vars['title'] = $element['#title'];
  $vars['class'] = isset($element['#attributes']['class']) ? $element['#attributes']['class'] : '';
  $vars['template_files'] = array(
    $element['#type'],
    $element['#type'] . '-' . $element['#group_name'],
    $element['#type'] . '-' . $element['#group_name'] . '-' . $element['#region'],
  );

  if (isset($vars['children'])) {
    $content = '';
    foreach (element_children($element) as $name => $child) {
      $vars[$child] = $element[$child]['field']['items'][1]['#item'];
      $content .= drupal_render($element[$child]);
    }
    $vars['content'] = isset($content) ? $content : '';
  }
  else {
    $vars['children'] = $element['children']['#children'];
    unset($element['children']);

    $content = '';
    foreach (element_children($element) as $name => $child) {
      $vars[$child] = $element[$child]['field']['items'][1]['#item'];
      $content .= $element[$child]['#children'];
    }
    $vars['content'] = isset($content) ? $content : '';

    if (isset($element['#parent'])) {
      $parent = array();
      foreach (element_children($element['#parent']) as $name => $child) {
        $parent[$child] = $element['#parent'][$child]['field']['items'][1]['#item'];
      }
      $vars['parent'] = $parent;
      unset($vars['element']['#parent']);
    }
  }
  
  $vars['podgroup_id'] = $vars['element']['#region'] . '-' . $vars['element']['#group_name'] . '-' . $vars['element']['#delta'];
}

function theme_content_podgroup_null($element) {
  // Do nothing.
}

function theme_content_podgroup_block($element) {
  $children = '';
  if (!empty($element['children'])) {
    unset($element['children']['#weight']);
    $element['#children'] = $element['children'];
    foreach ($element['children'] as $child) {
      $children .= drupal_render($child);
    }
    unset($element['children']);
  }
  return theme('content_podgroup', $element, $children);
}

function template_preprocess_content_podgroup_display_wrapper(&$vars) {
  $element = $vars['element'];

  $vars['title'] = $element['#title'];
  $vars['class'] = isset($element['#attributes']['class']) ? $element['#attributes']['class'] : '';

  $vars['template_files'] = array(
    $element['#type'],
    $element['#type'] . '-' . $element['#group_name'],
  );

  $content = '';
  foreach (element_children($element) as $name => $child) {
    $vars[$child] = $element[$child]['field']['items'][1]['#item'];
    $content .= drupal_render($element[$child]);
  }
  $vars['content'] = isset($content) ? $content : '';
}

/**
 * Theme function for wrapping the main table for moving things around on the backend.
 */

function theme_content_podgroup_form_wrapper($element) {
  $output = '<div class="podgroup-wrapper">';
  $output .= '</div>';

  return $output;
}

function theme_content_podgroup_display_simple($element) {
  $output = '<div class="podgroup-simple">';
  $output .= '</div>';

  return $output;
}

function theme_content_podgroup_display_hr($element) {
  $output = '<div class="podgroup-hr">';
  $output .= '</div>';

  return $output;
}

function theme_content_podgroup_display_table_single($element) {
  $output = '<div class="podgroup-table-single">';
  $output .= '</div>';

  return $output;
}

function theme_content_podgroup_display_table_multiple($element) {
  $output = '<div class="podgroup-table-multiple">';
  $output .= '</div>';

  return $output;
}
