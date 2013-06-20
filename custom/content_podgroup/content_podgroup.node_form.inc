<?php
// $Id$

/**
 * @file
 * Implementation of node edit functions for content podgroup.
 */
require_once "content_podgroup.admin.inc";

/**
 * Helper function to build the list of available parent options for a
 * given pod.
 */
function content_podgroup_parent_options($group_name, $node) {
  $group_table = "content_" . $group_name;
  $node_groups = content_podgroup_load_podgroups($node->type);
  $vid = $node->clone_from_original_vid ? $node->clone_from_original_vid : $node->vid;

  $options = array();

  if (!empty($node_groups) && isset($node_groups[$group_name])) {
    foreach ($node_groups[$group_name]["settings"]["podgroup"]["nesting"] as $nesting_group => $enabled) {
      if ($enabled && $nesting_group == 'group_parent') {
        $options['group_parent|0'] = 'Parent';
      }
      elseif ($enabled) {
        $query = "SELECT title, delta FROM {%s} WHERE vid = %d and type = '%s'";
        $result = db_query($query, "content_type_" . $node->type . "_podgroup", $vid, $nesting_group);
        while ($row = db_fetch_array($result)) {
          $parent_title = $row['title'];
          $parent_key = $nesting_group . '|' . $row['delta'];

          $options[$parent_key] = $parent_title;
        }
      }
    }
  }

  return $options;
}

/**
 * Implementation of hook_fieldgroup_form().
 *
 * Align the delta values of each field in the podgroup.
 *
 * Swap the field name and delta for each podgroup so we can
 * d-n-d each collection of fields as a single delta item.
 */
function _content_podgroup_fieldgroup_form(&$form, &$form_state, $form_id, $group) {
  $node = $form['#node'];
  $group_name = $group['group_name'];
  $content_type = content_types($group['type_name']);

  // Build list of accessible fields in this group.
  $group_fields = array();
  foreach ($content_type['fields'] as $field_name => $field) {
    if (isset($group['fields'][$field_name]) && isset($form[$group_name][$field_name])) {
      if (!isset($form[$group_name][$field_name]['#access']) || $form[$group_name][$field_name]['#access']) {
        $group_fields[$field_name] = $field;
      }
    }
  }

  // Quit if there are no field in the form for this group.
  if (empty($group_fields)) {
    return;
  }

  // Compute unique deltas from all deltas used by fields in this podgroup.
  $group_deltas = array();
  $max_delta = -1;
  foreach (array_keys($group_fields) as $field_name) {
    if (!empty($node->$field_name) && is_array($node->$field_name)) {
      foreach (array_keys($node->$field_name) as $delta) {
        $group_deltas[$delta] = $delta;
      }
      sort($group_deltas);
      $max_delta = max($max_delta, max($group_deltas));
    }
  }
  $current_item_count = isset($form_state['item_count'][$group_name]) ? $form_state['item_count'][$group_name] : max(1, count($group_deltas));
  while (count($group_deltas) < $current_item_count) {
    $max_delta++;
    $group_deltas[] = $max_delta;
  }

  $form[$group_name]['#theme'] = 'content_podgroup_node_form';
  $form[$group_name]['#item_count'] = count($group_deltas);
  $form[$group_name]['#type_name'] = $group['type_name'];
  $form[$group_name]['#group_name'] = $group_name;
  $form[$group_name]['#group_label'] = $group['label'];
  $form[$group_name]['#group_fields'] = $group_fields;
  $form[$group_name]['#tree'] = TRUE;

  if (!isset($form['#podgroups'])) {
    $form['#podgroups'] = array();
  }
  $form['#podgroups'][$group_name] = $group_fields;
  // Added the values in to the #multigroups key for compatibility with filefield
  if (!isset($form['#multigroups'])) {
    $form['#multigroups'] = array();
  }
  $form['#multigroups'][$group_name] = $group_fields;

  // Add a visual indication to the fieldgroup title if the podgroup is required.
  if (!empty($group['settings']['podgroup']['required'])) {
    $form[$group_name]['#title'] .= '&nbsp;<span class="form-required" title="'. t('This group requires one collection of fields minimum.') .'">*</span>';
  }

  // Attach our own after build handler to the form, used to fix posting data
  // and the form structure, moving fields back to their original positions.
  // That is, move them from group->delta->field back to field->delta.
  if (!isset($form['#after_build'])) {
    $form['#after_build'] = array();
  }
  if (!in_array('content_podgroup_node_form_after_build', $form['#after_build'])) {
    array_unshift($form['#after_build'], 'content_podgroup_node_form_after_build');
  }
  if (!in_array('content_podgroup_node_form_after_build_remove_temp', $form['#after_build'])) {
    $form['#after_build'][] = 'content_podgroup_node_form_after_build_remove_temp';
  }

  // Attach our own validation handler to the form, used to check for empty fields.
  if (!isset($form['#validate'])) {
    $form['#validate'] = array();
  }
  if (!in_array('content_podgroup_node_form_validate', $form['#validate'])) {
    array_unshift($form['#validate'], 'content_podgroup_node_form_validate');
  }

  // Attach our own pre_render handler to the form, used to fix the required
  // attribute of all fields in podgroups.
  if (!isset($form['#pre_render'])) {
    $form['#pre_render'] = array();
  }
  if (!in_array('content_podgroup_node_form_pre_render', $form['#pre_render'])) {
    array_unshift($form['#pre_render'], 'content_podgroup_node_form_pre_render');
  }

  $nid = $node->clone_from_original_nid ? $node->clone_from_original_nid : $node->nid;
  $vid = $node->clone_from_original_vid ? $node->clone_from_original_vid : $node->vid;

  foreach ($group_deltas as $delta) {
    $is_valid_podgroup = FALSE;

    if (!empty($nid) && empty($form_state['values'])) {
      $query = "SELECT count(*) FROM {content_type_" . $node->type . "_podgroup} WHERE vid = %d AND type = '%s' AND delta = %d";
      $result = db_query($query, $vid, $group['group_name'], $delta);
      $row_count = db_result($result);
      if ($row_count > 0) {
        $is_valid_podgroup = TRUE;
      }
    }
    else {
      if (isset($form_state['values'][$group['group_name']][$delta])) {
        $is_valid_podgroup = TRUE;
      }
    }

    if ($is_valid_podgroup) {
      content_podgroup_group_form($form, $form_state, $group, $delta);
    }
    else {
      // We don't want to display the fields to the end user but we need them
      // for now so that the field modules add the required JS to the page.
      // The fields are unset in the after_build hook.
      if (!isset($form['podgroups_temp'])) {
        $form['podgroups_temp'] = array();
      }
      if (!isset($form['podgroups_temp'][$delta])) {
        $form['podgroups_temp'][$delta] = array();
      }
      foreach(array_keys($group_fields) as $field_name) {
        $field_form = content_field_form($form, $form_state, $content_type['fields'][$field_name], $delta);
        $form['podgroups_temp'][$delta][$field_name] = $field_form[$field_name];
      }
    }
  }

  // Unset the original group field values now that we've moved them.
  foreach (array_keys($group_fields) as $field_name) {
    unset($form[$group_name][$field_name]);
  }

  if (($add_more = content_podgroup_add_more($form, $form_state, $group)) !== FALSE) {
    $form[$group_name] += $add_more;
  }

}

/**
 * Create a new delta value for the group.
 *
 * Called in form_alter and by AHAH add more.
 */
function content_podgroup_group_form(&$form, &$form_state, $group, $delta) {
  $type_name = $group['type_name'];
  $group_name = $group['group_name'];
  if ($group['group_type'] != 'podgroup' || empty($form[$group_name]) || empty($form['#podgroups']) || empty($form['#podgroups'][$group_name])) {
    return;
  }
  module_load_include('inc', 'content', 'includes/content.node_form');

  $node = $form['#node'];
  $group_fields = $form['#podgroups'][$group_name];

  // If this is the initial load, then load values from the database
  if (empty($form_state['item_count'])) {
    $podgroup = content_podgroup_find_in_tree($node, $group_name, $delta);

    // Load nesting options from the database
    $nesting_options = content_podgroup_parent_options($group['group_name'], $form['#node']);
    $nesting_options = array('' => 'Nesting Options') + $nesting_options;
  }
  // Else if this is a submit load, then load the values from the form state
  else {
    $podgroup = content_podgroup_find_in_form_state($form, $form_state, $group_name, $delta);

    // Load nesting options based on values in the form state
    $nesting_options = array('' => 'Nesting Options');
    $nesting_types = array_keys($group['settings']['podgroup']['nesting'], TRUE);
    foreach ($nesting_types as $type) {
      if ($type == 'group_parent') {
        $nesting_options['group_parent|0'] = 'Parent';
        continue;
      }

      if (empty($form_state['values'][$type])) {
        continue;
      }

      // @todo: Dale - This should come from form_state instead of POST
      //foreach ($form_state['values'][$type] as $delta => $option) {
      if(!empty($form_state['values'][$type])){
        foreach ($form_state['values'][$type] as $parent_delta => $option) {
          if (!is_numeric($parent_delta) || !is_array($option) || !isset($option['_weight'])) {
            continue;
          }
          $nesting_options[$type . '|' . $parent_delta] = $option['_title'];
        }
      }
    }
  }

  if (empty($podgroup)) {
    $podgroup = array();
    $podgroup['title'] = $group['settings']['podgroup']['title_default'];
    $podgroup['delta'] = $delta;
    $podgroup['weight'] = 0;
    $podgroup['type'] = $group_name;
    $podgroup['parent_type'] = '';
    $podgroup['parent_delta'] = '';
    $podgroup['subpages'] = FALSE;
  }

  // In all cases load the region options from the database since they never change
  $region_options = content_podgroup_region_options($type_name, $group_name);
  $region_options = array('' => 'Region Options') + $region_options;

  foreach ($group_fields as $field_name => $field) {
    if (empty($form[$group_name][$delta])) {
      $form[$group_name] += array($delta => array($field_name => array()));
    }
    else {
      $form[$group_name][$delta][$field_name] = array();
    }

    $item_count = (isset($form_state['item_count'][$group_name]) ? $form_state['item_count'][$group_name] : $form[$group_name]['#item_count']);

    $form[$group_name][$delta]['_weight'] = array(
      '#type' => 'weight',
      '#delta' => $item_count, // this 'delta' is the 'weight' element's property
      '#default_value' => $podgroup['weight'],
      '#weight' => 100,
      '#attributes' => array('class' => 'content-podgroup-weight'),
    );

    // Add a checkbox to allow users remove a single delta subgroup.
    // See content_set_empty() and theme_content_podgroup_node_form().
    $form[$group_name][$delta]['_remove'] = array(
      '#type' => 'checkbox',
      '#default_value' => isset($form_state['values'][$group_name][$delta]['_remove']) ? $form_state['values'][$group_name][$delta]['_remove'] : 0,
      '#attributes' => array('class' => 'content-podgroup-parent-remove'),
    );
    $form[$group_name][$delta]['_parent'] = array(
      '#type' => 'select',
      '#options' => $nesting_options,
      '#default_value' => isset($form_state['values'][$group_name][$delta]['_parent']) ? $form_state['values'][$group_name][$delta]['_parent'] : $podgroup['parent_type'] . '|' . $podgroup['parent_delta'],
      '#attributes' => array('class' => 'content-podgroup-parent-select'),
    );
    $form[$group_name][$delta]['_region'] = array(
      '#type' => 'select',
      '#options' => $region_options,
      '#default_value' => isset($form_state['values'][$group_name][$delta]['_region']) ? $form_state['values'][$group_name][$delta]['_region'] : $podgroup['region'],
      '#attributes' => array('class' => 'content-podgroup-region-select'),
    );
    if (!isset($group['settings']['podgroup']['title_label']) || !empty($group['settings']['podgroup']['title_label'])) {
      $form[$group_name][$delta]['_title'] = array(
        '#weight' => -99,
        '#type' => 'textfield',
        '#description' => !empty($group['settings']['podgroup']['title_description']) ? $group['settings']['podgroup']['title_description'] : '',
        '#title' => !empty($group['settings']['podgroup']['title_label']) ? $group['settings']['podgroup']['title_label'] : t('Title'),
	'#default_value' => ((isset($form_state['values'][$group_name][$delta])) ? $form_state['values'][$group_name][$delta]['_title'] : $podgroup['title']),
        '#attributes' => array('class' => 'content-podgroup-title'),
      );
    }
    if (isset($group['settings']['podgroup']['subpages']) && $group['settings']['podgroup']['subpages'] == TRUE) {
      $form[$group_name][$delta]['_subpages'] = array(
        '#weight' => 99,
        '#type' => 'checkbox',
        '#title' => t('Display on subpages'),
        '#description' => t('If checked and this is a top level podgroup, then it will be displayed on this page as well as all of its subpages.'),
        '#default_value' => isset($form_state['values'][$group_name][$delta]['_subpages']) ? $form_state['values'][$group_name][$delta]['_subpages'] : $podgroup['subpages'],
        '#attributes' => array('class' => 'content-podgroup-subpages'),
      );
    }

    // Make each field into a pseudo single value field
    // with the right delta value.
    $field['multiple'] = 0;

    $form['#field_info'][$field_name] = $field;
    $node_copy = drupal_clone($node);

    // Set the form '#node' to the delta value we want so the Content
    // module will feed the right $items to the field module in
    // content_field_form().

    // There may be missing delta values for fields that were
    // never created, so check first.
    if (!empty($node->$field_name) && isset($node->{$field_name}[$delta])) {
      $node_copy->$field_name = array($delta => $node->{$field_name}[$delta]);
    }
    else {
      $value = NULL;
      // Try to obtain default values only if the node is being created.
      if (!isset($node->nid) && content_callback('widget', 'default value', $field) != CONTENT_CALLBACK_NONE) {
        // If a module wants to insert custom default values here,
        // it should provide a hook_default_value() function to call,
        // otherwise the content module's content_default_value() function
        // will be used.
        $callback = content_callback('widget', 'default value', $field) == CONTENT_CALLBACK_CUSTOM ? $field['widget']['module'] .'_default_value' : 'content_default_value';
        if (function_exists($callback)) {
          $items = $callback($form, $form_state, $field, 0);
          $value = $items[0];
        }
      }
      $node_copy->$field_name = array($delta => $value);
    }
    $form['#node'] = $node_copy;

    // Place the new element into the $delta position in the group form.
    if (content_handle('widget', 'multiple values', $field) == CONTENT_HANDLE_CORE) {
      $field_form = content_field_form($form, $form_state, $field, $delta);
      $value = array_key_exists($delta, $field_form[$field_name]) ? $delta : 0;
      $form[$group_name][$delta][$field_name] = $field_form[$field_name][$value];
    }
    else {
      // When the form is submitted, get the element data from the form values.
      if (isset($form_state['values'][$field_name])) {
        $form_state_copy = $form_state;
        if (isset($form_state_copy['values'][$field_name][$delta])) {
          $form_state_copy['values'][$field_name] = array($delta => $form_state_copy['values'][$field_name][$delta]);
        }
        else {
          $form_state_copy['values'][$field_name] = array($delta => NULL);
        }
        $field_form = content_field_form($form, $form_state_copy, $field, $delta);
      }
      else {
        $field_form = content_field_form($form, $form_state, $field, $delta);
      }

      // Multiple value fields have an additional level in the array form that
      // needs to get fixed in $form_state['values'].
      if (!isset($field_form[$field_name]['#element_validate'])) {
        $field_form[$field_name]['#element_validate'] = array();
      }
      $field_form[$field_name]['#element_validate'][] = 'content_podgroup_fix_multivalue_fields';

      $form[$group_name][$delta][$field_name] = $field_form[$field_name];
    }
    $form[$group_name][$delta][$field_name]['#weight'] = $field['widget']['weight'];

    $form[$group_name][$delta]['#attributes']['class'] = $group_name . '-' . $delta;
  }

  // Reset the form '#node' back to its original value.
  $form['#node'] = $node;
}

/**
 * Fix required flag during form rendering stage.
 *
 * Required fields should display the required star in the rendered form.
 */
function content_podgroup_node_form_pre_render(&$form) {
  foreach ($form['#podgroups'] as $group_name => $group_fields) {
    $required_fields = array();
    foreach ($group_fields as $field_name => $field) {
      if ($field['required']) {
        $required_fields[] = $field_name;
      }
    }
    if (!empty($required_fields)) {
      content_podgroup_node_form_fix_required($form[$group_name], $required_fields, TRUE);
    }
  }
  return $form;
}

/**
 * Fix form and posting data when the form is submitted.
 *
 * FormAPI uses form_builder() during form processing to map incoming $_POST
 * data to the proper elements in the form. It builds the '#parents' array,
 * copies the $_POST array to the '#post' member of all form elements, and it
 * also builds the $form_state['values'] array. Then the '#after_build' hook is
 * invoked to allow custom processing of the form structure, and that happens
 * just before validation and submit handlers are executed.
 *
 * During hook_form_alter(), the podgroup module altered the form structure
 * moving elements from field->delta to podgroup->delta->field position,
 * which is what has been processed by FormAPI to build the form structures,
 * but field validation (and submit) handlers expect their data to be located
 * in their original positions.
 *
 * We now need to move the fields back to their original positions in the form,
 * and we need to do so without altering the form rendering process, which is
 * now reflecting the structure the podgroup is interested in. We just need
 * to fix the parts of the form that affect validation and submit processing.
 */
function _content_podgroup_node_form_after_build($form, &$form_state) {
  // Disable required flag during FormAPI validation, except when building the
  // form for an 'Add more values' request.
  $required = !empty($form_state['podgroup_add_more']);
  foreach ($form['#podgroups'] as $group_name => $group_fields) {
    $required_fields = array();
    foreach ($group_fields as $field_name => $field) {
      if ($field['required']) {
        $required_fields[] = $field_name;
      }
    }
    if (!empty($required_fields)) {
      content_podgroup_node_form_fix_required($form[$group_name], $required_fields, $required);
    }
  }

  // Disable required and needs validation flags for all the temp fields
  $required_fields = array();
  foreach ($form['podgroups_temp'][0] as $field_name => $field) {
    if (preg_match('/^#.*/', $field_name)) {
      continue;
    }

    $form['#field_info'][$field_name]['required'] = FALSE;
    $required_fields[] = $field_name;

    unset($form['podgroups_temp'][0][$field_name]['#needs_validation']);
    unset($form['podgroups_temp'][0][$field_name]['value']['#needs_validation']);
  }

  content_podgroup_node_form_fix_required($form['podgroups_temp'][0], $required_fields, FALSE);

  if ($form_state['submitted'] && ($form_state['clicked_button']['#value'] == 'Save' || array_search('node_form_submit', $form_state['clicked_button']['#submit']) !== FALSE)) {
    // Fix weights and parent values in $form_state for the fields in podgroups.
    $weight_mappings = array();
    $weight_mappings['group_parent'] = array(0 => 0);
    foreach (array_keys($form['#podgroups']) as $group_name) {
      // Traverse all the podgroups and ensure there are no duplicate weight values
      $podgroups = array();
      foreach ($form_state['values'][$group_name] as $delta => $items) {
        if (!is_array($items) || !isset($items['_weight'])) {
          continue;
        }
        $podgroups[$delta] = $items['_weight'];
      }
      // asort($podgroups);
      $weight_mappings[$group_name] = array();
      foreach ($podgroups as $delta => $weight) {
        $weight_mappings[$group_name][$delta] = count($weight_mappings[$group_name]);
      }

      // Update the weights for the groups in the form_state
      foreach ($form_state['values'][$group_name] as $delta => $items) {
        if (!is_array($items) || !isset($items['_weight'])) {
          continue;
        }
        $form_state['values'][$group_name][$delta]['_submitted_weight'] = $form_state['values'][$group_name][$delta]['_weight'];
        $form_state['values'][$group_name][$delta]['_weight'] = $weight_mappings[$group_name][$delta];
      }
    }

    //40702:problem node is not highlighted when I get the error - "List Group: this post can't be referenced.
    if (!empty($form_state['values']['group_list_node_item'])) {
      foreach ($form_state['values']['group_list_node_item'] as $delta => &$item) {
        if(!empty($item['field_list_node_item_list_group']['_error_element'])) {
           $item['field_list_node_item_list_group']['_error_element'] = "field_list_node_item_list_group][$delta][nid][nid";
        }
      }
    }

    // Now that we have the new deltas, loop through all podgroups and map the
    // old parent deltas to the new values
    foreach (array_keys($form['#podgroups']) as $group_name) {
      foreach ($form_state['values'][$group_name] as $delta => $items) {
        if (!is_array($items) || !isset($items['_weight'])) {
          continue;
        }
        $parent_parts = explode('|', $form_state['values'][$group_name][$delta]['_parent']);
        $parent_type = $parent_parts[0];
        $parent_delta = $parent_parts[1];
        $form_state['values'][$group_name][$delta]['_parent'] = $parent_type . '|' . $weight_mappings[$parent_type][$parent_delta];
      }
    }

    // Fix value positions in $form_state for the fields in podgroups.
    foreach (array_keys($form['#podgroups']) as $group_name) {
      content_podgroup_node_form_transpose_elements($form, $form_state, $form['#node']->type, $group_name);
    }

    // Fix form element parents for all fields in podgroups.
    content_podgroup_node_form_fix_parents($form, $form['#podgroups']);

    // Update posting data to reflect delta changes in the form structure.
    if (!empty($_POST)) {
      content_podgroup_node_form_fix_post($form);
    }

    content_podgroup_node_form_disable_validation($form);

  }
  else {
    //content_podgroup_form_alter_deltas($form);
  }

  return $form;
}

/**
 * Remove validation for all deleted fields
 */
function content_podgroup_node_form_disable_validation(&$form, $force = null) {
  if($form['#removed'] == 1 || $force) {
    unset($form['#needs_validation']);
    unset($form['#element_validate']);
  
    //force validation disable for all children elements as well
    $force = TRUE;
  }
  else{
    $force = FALSE;
  }

  // Recursively check children elements
  foreach (element_children($form) as $key) {
    if (isset($form[$key]) && $form[$key]) {
      content_podgroup_node_form_disable_validation($form[$key], $force);
    }
  }
}

/**
 * Fix required flag for required fields.
 *
 * We need to let the user enter an empty set of fields for a delta subgroup,
 * even if it contains required fields, which is equivalent to say a subgroup
 * should be ignored, not to be stored into the database.
 * So, we need to check for required fields, but only for non-empty subgroups.
 *
 * When the form is processed for rendering, the required flag is enabled for
 * all required fields, so the user can see what's required and what's not.
 *
 * When the form is processed for validation, the required flag is disabled,
 * so that FormAPI does not report errors for empty fields.
 *
 * @see content_podgroup_node_form_validate()
 */
function content_podgroup_node_form_fix_required(&$elements, $required_fields, $required) {
  foreach (element_children($elements) as $key) {
    if (isset($elements[$key]) && $elements[$key]) {

      if (count($elements[$key]['#array_parents']) >= 3 && in_array($elements[$key]['#array_parents'][2], $required_fields) && isset($elements[$key]['#required'])) {
        $elements[$key]['#required'] = $required;
      }

      // Recurse through all children elements.
      content_podgroup_node_form_fix_required($elements[$key], $required_fields, $required);
    }
  }
}

/**
 * Node form validation handler.
 *
 * Perform validation for empty fields ignoring subgroups flagged for removal.
 * Note that FormAPI validation for required fields is disabled because we need
 * to accept empty fields that are flagged for removal.
 */
function content_podgroup_node_form_validate($form, &$form_state) {

  _content_podgroup_node_form_add_js($form);

  $groups = content_podgroup_load_podgroups($form['#node']->type);

  foreach ($form['#podgroups'] as $group_name => $group_fields) {
    $group = $groups[$group_name];
    $group_required = isset($group['settings']['podgroup']['required']) ? $group['settings']['podgroup']['required'] : 0;

    $non_empty_subgroups = $non_removed_subgroups = $required_field_errors = array();
    foreach ($group_fields as $field_name => $field) {
      // Tell the content module that it is not needed to enforce requirement
      // of fields in this podgroup because we are doing it here.
      // See content_multiple_value_nodeapi_validate().
      $form_state['values']['_content_ignore_required_fields'][$field_name] = TRUE;

      if (!empty($form_state['values'][$field_name])) {
        foreach ($form_state['values'][$field_name] as $delta => $item) {
          // Ignore subgroups flagged for removal.
          if ($form_state['podgroup_removed'][$group_name][$delta]) {
            continue;
          }
          // Keep track of non-removed subgroups.
          $non_removed_subgroups[$delta] = TRUE;

          $is_empty_function = $field['module'] .'_content_is_empty';

          // If this element is empty, or element is one that can never be empty
          if ($is_empty_function($form_state['values'][$field_name][$delta], $field) 
            || $field['widget']['type'] == 'optionwidgets_onoff'
            || $field['widget']['type'] == 'hiddenwidget'
            || $field['widget']['type'] == 'content_type_tag_widget'
          ) {
            // Ignore fields that are not required.
            if (!$field['required']) {
              continue;
            }

            // Build an error message for this field in this subgroup, but do
            // not flag it, yet.
            if (!empty($item['_error_element'])) {
              // Here we don't know the number of elements and subelements a
              // widget could have added to the form, so we need to extract
              // components from the top, where we have group/delta/field, and
              // then push back field/delta on top of the list.
              $error_element = explode('][', $item['_error_element']);
              array_shift($error_element);
              array_shift($error_element);
              array_shift($error_element);
              array_unshift($error_element, $field_name, $delta);
              $error_element = implode('][', $error_element);
            }
            else {
              $error_element = '';
            }
            $required_field_errors[$delta][$field_name] = array(
              'element' => $error_element,
              'message' => t('!name field is required in group @group.', array(
                '!name' => $form[$group_name][$delta][$field_name]['#title'],
                '@group' => t($group['label']),
              )),
            );
          }
          else {
            $non_empty_subgroups[$delta] = TRUE;
          }
        }
      }
    }

    // Required podgroups require at least one non-empty subgroup of fields.
    if ($group_required && empty($non_empty_subgroups)) {
      form_set_error('', t('Group @name requires one collection of fields minimum.', array('@name' => t($group['label']))));
      continue;
    }

    // Do not enforce field requirements if there is only one non-removed
    // subgroup of fields, and that subgroup is empty.
    if (count($non_removed_subgroups) == 1) {
      $delta = key($non_removed_subgroups);
      if (isset($required_field_errors[$delta]) && !isset($non_empty_subgroups[$delta])) {
        unset($required_field_errors[$delta]);
      }
    }

    // Ok, now we can flag errors for all required fields that have not been
    // filled in when they should.
    foreach ($required_field_errors as $delta => $error_list) {
      foreach ($error_list as $field_name => $error_info) {
        form_set_error($error_info['element'], $error_info['message']);
      }
    }
  }

  // Make sure all podgroups are in a legal heirarchy
  content_podgroup_node_form_validate_parents($form, $form_state);
}

/**
 * Validate that all podgroups have legal parents and regions
 */
function content_podgroup_node_form_validate_parents(&$form, &$form_state) {

  $groups = content_podgroup_load_podgroups($form_state['values']['type']);

  // Loop through all groups for this content type
  foreach($groups as $group){
    // Loop through all podgroups in this group
    foreach($form_state['values'][$group['group_name']] as $id => $podgroup){
      
      // Check that this podgroup is valid
      if(is_numeric($id) && !$podgroup['_remove']){

        // Validate region
        if(empty($podgroup['_region'])){
          form_set_error($group['group_name'] . '_' . $id, 'The "' . $podgroup['_title'] . '" ' . $group['label'] . ' podgroup does not have a valid region selected');
        }
        else if($group['settings']['podgroup']['regions'][$podgroup['_region']] == 0){
          form_set_error($group['group_name'] . '_' . $id, 'Podgroups of type ' . $group['group_name'] . ' are not allowed in the region ' . $podgroup['_region']);
        }

        // Validate parent
        $parent = explode('|', $podgroup['_parent']);
        if(empty($parent[0]) || $parent[1] == ''){
          form_set_error($group['group_name'] . '_' . $id, 'The "' . $podgroup['_title'] . '" ' . $group['label'] . ' podgroup does not have a valid parent selected');
        }
        else if($group['settings']['podgroup']['nesting'][$parent[0]] == 0){
          form_set_error($group['group_name'] . '_' . $id, 'Podgroups of type ' . $group['group_name'] . ' are not allowed to have the parent ' . $parent[0]);
        }

      }
    }
  }
}

/**
 * Transpose element positions in $form_state for the fields in a podgroup.
 */
function content_podgroup_node_form_transpose_elements(&$form, &$form_state, $type_name, $group_name) {
  $group_fields = $form['#podgroups'][$group_name];

  // Save the remove state of podgroup items in the $form_state array.
  if (!isset($form_state['podgroup_removed'])) {
    $form_state['podgroup_removed'] = array();
  }
  if (!isset($form_state['podgroup_removed'][$group_name])) {
    $form_state['podgroup_removed'][$group_name] = array();
  }

  // Move group data from group->delta->field to field->delta.
  $group_data = array();
  foreach ($form_state['values'][$group_name] as $delta => $items) {
    // Skip 'add more' button.
    if (!is_array($items) || !isset($items['_weight'])) {
      continue;
    }
    foreach ($group_fields as $field_name => $field) {
      if (!isset($group_data[$field_name])) {
        $group_data[$field_name] = array();
      }
      // Get field weight and remove state from the group and keep track of the
      // current delta for each field item.
      $item_defaults = array(
        '_weight' => $items['_weight'],
        '_remove' => $items['_remove'],
        '_old_delta' => $delta,
      );
      $group_data[$field_name][$delta] = (is_array($items[$field_name]) ? array_merge($items[$field_name], $item_defaults) : $item_defaults);
      // Store the remove state and the element weight in the form element as
      // well, so we can restore them later.
      // See content_podgroup_fix_multivalue_fields().
      // See content_podgroup_fix_element_values().
      $form[$group_name][$delta][$field_name]['#_weight'] = $items['_weight'];
      $form[$group_name][$delta][$field_name]['#removed'] = $items['_remove'];

      // Insert an element validation callback of our own at the end of the
      // list to ensure the drag'n'drop weight of the element is not lost by
      // a form_set_value() operation made by the validation callback of the
      // widget element.
      if (!isset($form[$group_name][$delta][$field_name]['#element_validate'])) {
        $form[$group_name][$delta][$field_name]['#element_validate'] = array();
      }
      $form[$group_name][$delta][$field_name]['#element_validate'][] = 'content_podgroup_fix_element_values';
    }
    $form_state['podgroup_removed'][$group_name][$delta] = $items['_remove'];
  }

  $form_group_sorted = FALSE;
  foreach ($group_data as $field_name => $items) {

    // Sort field items according to drag-n-drop reordering. Deltas are also
    // rebuilt to start counting from 0 to n. Note that since all fields in the
    // group share the same weight, their deltas remain in sync.
    usort($items, '_content_sort_items_helper');

    // Now we need to apply the same ordering to the form elements. Also,
    // note that deltas have changed during the sort operation, so we need
    // to reflect this delta conversion in the form.
    if (!$form_group_sorted) {
      $form_group_items = array();
      $form_deltas = array();
      foreach ($items as $new_delta => $item) {
        $form_deltas[$item['_old_delta']] = $new_delta;
        $form_group_items[$new_delta] = $form[$group_name][$item['_old_delta']];
        unset($form[$group_name][$item['_old_delta']]);
      }
      foreach ($form_group_items as $new_delta => $form_group_item) {
        $form[$group_name][$new_delta] = $form_group_item;
      }
      content_podgroup_node_form_fix_deltas($form[$group_name], $form_deltas);
      $form_group_sorted = TRUE;
    }

    // Get rid of the old delta value.
    foreach (array_keys($items) as $delta) {
      unset($items[$delta]['_old_delta']);
    }

    // Fix field and delta positions in the $_POST array.
    if (!empty($_POST)) {
      $_POST[$field_name] = array();
      foreach ($items as $new_delta => $item) {
        $_POST[$field_name][$new_delta] = $item;
      }
      if (isset($_POST[$group_name])) {
        unset($_POST[$group_name]);
      }
    }

    // Move field items back to their original positions.
    $form_state['values'][$field_name] = $items;
  }

  // Copy fields in form from form[group_name][delta][field] to form[group_name][field][delta]
  // filefield module is expecting this
  foreach ($form[$group_name] as $delta => $items) {
    if(is_numeric($delta)){
      foreach($form[$group_name]['#group_fields'] as $field){
        $form[$group_name][$field['field_name']][$delta] = $form[$group_name][$delta][$field['field_name']];
      }
    }
  }
}

/**
 * Fix deltas for all affected form elements.
 */
function content_podgroup_node_form_fix_deltas(&$elements, $form_deltas) {
  foreach (element_children($elements) as $key) {
    if (isset($elements[$key]) && $elements[$key]) {

      // Fix the second item, the delta value, of the element's '#parents' array.
      $elements[$key]['#parents'][1] = $form_deltas[$elements[$key]['#parents'][1]];

      // If present, fix delta value in '#delta' attribute of the element.
      if (isset($elements[$key]['#delta']) && isset($form_deltas[$elements[$key]['#delta']])) {
        $elements[$key]['#delta'] = $form_deltas[$elements[$key]['#delta']];
      }

      // Recurse through all children elements.
      content_podgroup_node_form_fix_deltas($elements[$key], $form_deltas);
    }
  }
}

/**
 * Fix form element parents for all fields in podgroups.
 *
 * The $element['#parents'] array needs to reflect the position of the fields
 * in the $form_state['values'] array so that form_set_value() can be safely
 * used by field validation handlers.
 */
function content_podgroup_node_form_fix_parents(&$elements, $podgroups) {
  foreach (element_children($elements) as $key) {
    if (isset($elements[$key]) && $elements[$key]) {

      // Check if the current element is child of a podgroup. The #parents
      // array for field values has, at least, 3 parent elements, being the
      // first one the name of a podgroup.
      if (count($elements[$key]['#parents']) >= 3 && isset($podgroups[$elements[$key]['#parents'][0]])) {

        // Extract group name, delta and field name from the #parents array.
        array_shift($elements[$key]['#parents']);
        $delta = array_shift($elements[$key]['#parents']);
        $field_name = array_shift($elements[$key]['#parents']);

        // Now, insert field name and delta to the #parents array.
        array_unshift($elements[$key]['#parents'], $field_name, $delta);
      }

      // Recurse through all children elements.
      content_podgroup_node_form_fix_parents($elements[$key], $podgroups);
    }
  }
}

/**
 * Update posting data to reflect delta changes in the form structure.
 *
 * The $_POST array is fixed in content_podgroup_node_form_transpose_elements().
 */
function content_podgroup_node_form_fix_post(&$elements) {
  foreach (element_children($elements) as $key) {
    if (isset($elements[$key]) && $elements[$key]) {

      // Update the element copy of the $_POST array.
      $elements[$key]['#post'] = $_POST;

      // Recurse through all children elements.
      content_podgroup_node_form_fix_post($elements[$key]);
    }
  }

  // Update the form copy of the $_POST array.
  $elements['#post'] = $_POST;
}

/**
 * Make sure the '_weight' and '_remove' attributes of the element exist.
 *
 * @see content_podgroup_node_form_transpose_elements()
 */
function content_podgroup_fix_element_values($element, &$form_state) {
  $field_name = $element['#field_name'];
  $delta = $element['#delta'];
  if (!isset($form_state['values'][$field_name][$delta]['_weight']) || !isset($form_state['values'][$field_name][$delta]['_remove'])) {
    $value = array('_weight' => $element['#_weight'], '_remove' => $element['#removed']);
    if (isset($form_state['values'][$field_name][$delta]) && is_array($form_state['values'][$field_name][$delta])) {
      $value = array_merge($form_state['values'][$field_name][$delta], $value);
    }
    form_set_value($element, $value, $form_state);
  }
}

/**
 * Fix the value for fields that deal with multiple values themselves.
 */
function content_podgroup_fix_multivalue_fields($element, &$form_state) {
  $field_name = $element['#field_name'];
  $delta = $element['#delta'];
  if (isset($form_state['values'][$field_name][$delta][0]) && is_array($form_state['values'][$field_name][$delta][0])) {
    $value = array_merge($form_state['values'][$field_name][$delta][0], array('_remove' => $element['#removed']));
  }
  else {
    $value = array('_remove' => $element['#removed']);
  }
  form_set_value($element, $value, $form_state);
}

/**
 * Add AHAH add more button, if not working with a programmed form.
 */
function content_podgroup_add_more(&$form, &$form_state, $group) {
  if (!empty($form['#programmed'])) {
    return FALSE;
  }

  // Make sure the form is cached so ahah can work.
  $form['#cache'] = TRUE;
  $content_type = content_types($group['type_name']);
  $group_name = $group['group_name'];
  $group_name_css = str_replace('_', '-', $group_name);

  $form_element = array();
  $form_element[$group_name .'_add_more'] = array(
    '#type' => 'submit',
    '#name' => $group_name .'_add_more',
    '#value' => t('Add more values'),
    '#weight' => 2,
    '#submit' => array('content_podgroup_add_more_submit'),
    '#ahah' => array(
      'path' => 'content_podgroup/js_add_more/'. $content_type['url_str'] .'/'. $group_name,
      'wrapper' => $group_name_css .'-items',
      'method' => 'replace',
      'effect' => 'fade',
    ),
    // When JS is disabled, the content_podgroup_add_more_submit handler will
    // find the relevant group information using these entries.
    '#group_name' => $group_name,
    '#type_name' => $group['type_name'],
    '#item_count' => $form[$group_name]['#item_count'],
  );

  // Add wrappers for the group and 'more' button.
  $form_element['#prefix'] = '<div id="'. $group_name_css .'-items">';
  $form_element['#suffix'] = '</div>';
  $form_element[$group_name .'_add_more']['#prefix'] = '<div class="content-add-more clear-block">';
  $form_element[$group_name .'_add_more']['#suffix'] = '</div>';

  return $form_element;
}

/**
 * Submit handler to add more choices to a content form. This handler is used when
 * JavaScript is not available. It makes changes to the form state and the
 * entire form is rebuilt during the page reload.
 */
function content_podgroup_add_more_submit($form, &$form_state) {
  // Set the form to rebuild and run submit handlers.
  node_form_submit_build_node($form, $form_state);
  $group_name = $form_state['clicked_button']['#group_name'];
  $type_name = $form_state['clicked_button']['#type_name'];

  // Make the changes we want to the form state.
  if (isset($form_state['clicked_button']['#item_count'])) {
    $form_state['item_count'][$group_name] = $form_state['clicked_button']['#item_count'] + 1;
  }
}

/**
 * Menu callback for AHAH addition of new empty widgets.
 *
 * Adapted from content_add_more_js to work with groups instead of fields.
 */
function content_podgroup_add_more_js($type_name_url, $group_name) {
  $content_type = content_types($type_name_url);
  $groups = content_podgroup_load_podgroups($content_type['type']);
  $group = $groups[$group_name];

  if (empty($_POST['form_build_id'])) {
    // Invalid request.
    drupal_json(array('data' => ''));
    exit;
  }

  // Retrieve the cached form.
  $form_state = array('submitted' => FALSE);
  $form_build_id = $_POST['form_build_id'];
  $form = form_get_cache($form_build_id, $form_state);
  if (!$form) {
    // Invalid form_build_id.
    drupal_json(array('data' => ''));
    exit;
  }

  // We don't simply return a new empty widget to append to existing ones, because
  // - ahah.js won't simply let us add a new row to a table
  // - attaching the 'draggable' behavior won't be easy
  // So we resort to rebuilding the whole table of widgets including the existing ones,
  // which makes us jump through a few hoops.

  // The form that we get from the cache is unbuilt. We need to build it so that
  // _value callbacks can be executed and $form_state['values'] populated.
  // We only want to affect $form_state['values'], not the $form itself
  // (built forms aren't supposed to enter the cache) nor the rest of $form_data,
  // so we use copies of $form and $form_data.
  $form_copy = $form;
  $form_state_copy = $form_state;
  $form_copy['#post'] = array();
  form_builder($_POST['form_id'], $form_copy, $form_state_copy);

  // Just grab the data we need.
  $form_state['values'] = $form_state_copy['values'];
  // Reset cached ids, so that they don't affect the actual form we output.
  form_clean_id(NULL, TRUE);

  // Sort the $form_state['values'] we just built *and* the incoming $_POST data
  // according to d-n-d reordering.
  unset($form_state['values'][$group_name][$group['group_name'] .'_add_more']);
  if (isset($_POST[$group_name])) {
    foreach ($_POST[$group_name] as $delta => $item) {
      $form_state['values'][$group_name][$delta]['_weight'] = $item['_weight'];
      $form_state['values'][$group_name][$delta]['_remove'] = isset($item['_remove']) ? $item['_remove'] : 0;
    }
  }

  $form_state['values'][$group_name] = _content_sort_items($group, $form_state['values'][$group_name]);
  $_POST[$group_name] = _content_sort_items($group, $_POST[$group_name]);

  // Build our new form element for the whole group, asking for one more element.
  if (isset($_POST[$group_name])) {
    $delta = max(array_keys($_POST[$group_name])) + 1;
  }
  else {
    $delta = 0;
  }

  $form_state['item_count'] = array($group_name => count($_POST[$group_name]) + 1);

  content_podgroup_group_form($form, $form_state, $group, $delta);

  // Calculate the number podgroup instances on the page
  $count = 0;
  foreach ($groups as $g_name => $g_info) {
    if (isset($form_state['values'][$g_name])) {
      foreach ($form_state['values'][$g_name] as $idx => $values) {
        if (is_numeric($idx)) {
          $count++;
        }
      }
    }
  }

  // Rebuild weight deltas to make sure they all are equally dimensioned.
  foreach ($form[$group_name] as $key => $item) {
    if (is_numeric($key) && isset($item['_weight']) && is_array($item['_weight'])) {
      $form[$group_name][$key]['_weight']['#delta'] = $count;
    }
  }

  // Save the new definition of the form.
  $form_state['values'] = array();
  form_set_cache($form_build_id, $form, $form_state);

  // Build the new form against the incoming $_POST values so that we can
  // render the new element.
  $_POST[$group_name][$delta]['_weight'] = $delta;
  $form_state = array('submitted' => FALSE, 'podgroup_add_more' => TRUE);
  $form += array(
    '#post' => $_POST,
    '#programmed' => FALSE,
  );

  // Ticket #34437
  // Setting $form['#post'] is needed for AJAX textfield bug in core http://drupal.org/node/678158
  //$orig_post = $form['#post'];
  //$form['#post'] = array();
  $form = form_builder($_POST['form_id'], $form, $form_state);

  // Ticket #34437
  // Reset the weight for the group instances
  //foreach ($orig_post[$group_name] as $delta => $values) {
  //  $form[$group_name][$delta]['_weight']['#value'] = $values['_weight'];
  //}

  // Render the new output.
  $group_form = $form[$group_name];
  // Prevent duplicate wrapper
  unset($group_form['#prefix'], $group_form['#suffix']);
  // We're in the AHAH handler, so the fieldset was expanded.
  $group_form['#collapsed'] = FALSE;

  // If a newly inserted widget contains AHAH behaviors, they normally won't
  // work because AHAH doesn't know about those - it just attaches to the exact
  // form elements that were initially specified in the Drupal.settings object.
  // The new ones didn't exist then, so we need to update Drupal.settings
  // by ourselves in order to let AHAH know about those new form elements.
  $javascript = drupal_add_js(NULL, NULL);
  $output_js = isset($javascript['setting']) ? '<script type="text/javascript">jQuery.extend(Drupal.settings, '. drupal_to_js(call_user_func_array('array_merge_recursive', $javascript['setting'])) .');</script>' : '';

  $output = theme('status_messages') . drupal_render($group_form) . $output_js;

  // Using drupal_json() breaks filefield's file upload, because the jQuery
  // Form plugin handles file uploads in a way that is not compatible with
  // 'text/javascript' response type.
  $GLOBALS['devel_shutdown'] =  FALSE;
  print drupal_to_js(array('status' => TRUE, 'data' => $output));
  exit;
}

/**
 * Theme an individual form element.
 *
 * Combine multiple values into a table with drag-n-drop reordering.
 */
function theme_content_podgroup_node_form($element) {

  $group_name = $element['#group_name'];
  $groups = content_podgroup_load_podgroups($element['#type_name']);
  $group = $groups[$group_name];
  $group['settings']['podgroup']['regions']['header'] = 1;
  $group_fields = $element['#group_fields'];

  $table_id = $element['#group_name'] .'_values';
  $table_class = 'content-podgroup-table';
  $order_class = $element['#group_name'] .'-delta-order';
  $subgroup_settings = isset($group['settings']['podgroup']['subgroup']) ? $group['settings']['podgroup']['subgroup'] : array();
  $show_label = isset($subgroup_settings['label']) ? $subgroup_settings['label'] : 'above';
  $subgroup_labels = isset($group['settings']['podgroup']['labels']) ? $group['settings']['podgroup']['labels'] : array();

  $headers = array();
  $headers[] = array('data' => "Fields", 'class' => 'content-podgroup-fields-header');

  $headers[0]['colspan'] = 2;
  $table_class .= ' content-podgroup-edit-table-single-column';

  $headers[] = array('data' => t('Parent'), 'class' => 'content-podgroup-parent-header');
  $headers[] = array('data' => t('Region'), 'class' => 'content-podgroup-region-header');
  $headers[] = array('data' => t('Order'), 'class' => 'content-podgroup-weight-header');
  $headers[] = array('data' => t('Remove'), 'class' => 'content-podgroup-remove-header');

  $rows = array();

  //get errors as local array
  $errors = form_get_errors();

  $i = 0;
  foreach (element_children($element) as $delta => $key) {
    if (is_numeric($key)) {
      $cells = array();
      $label = ($show_label == 'above' && !empty($subgroup_labels[$i]) ? theme('content_podgroup_node_label', check_plain(t($subgroup_labels[$i]))) : '');
      $element[$key]['_weight']['#attributes']['class'] .= ' ' . $order_class;

      $cells[] = array('data' => '', 'class' => 'content-podgroup-drag');
      $parent_element = drupal_render($element[$key]['_parent']);
      $region_element = drupal_render($element[$key]['_region']);
      $delta_element = drupal_render($element[$key]['_weight']);
      $remove_element = drupal_render($element[$key]['_remove']);

      $cells[] = array('data' => '<div id="' . $order_class . '_' . $key . '">' . $label . drupal_render($element[$key]) . '</div>', 'class' => 'content-podgroup-fields-cell');

      $row_class = 'content-podgroup-instance ' . $group_name . '-' . $key;
      $cells[] = array('data' => $parent_element, 'class' => 'content-podgroup-parent-cell');
      $cells[] = array('data' => $region_element, 'class' => 'content-podgroup-region-cell');
      $cells[] = array('data' => $delta_element, 'class' => 'content-podgroup-weight-cell');
      if (!empty($element[$key]['_remove']['#value'])) {
        $row_class .= ' content-podgroup-removed-row';
      }
      $cells[] = array('data' => $remove_element, 'class' => 'content-podgroup-remove-cell');

      $row_class .= empty($errors[$group_name . '_' . $key]) ? '' : ' error';

      $rows[] = array('data' => $cells, 'class' => $row_class);
    }
    $i++;
  }

  if (empty($rows)) {
    $rows[] = array(array('data' => 'No podgroups currently exist', 'colspan' => count($headers)+1));
  }

  drupal_add_css(drupal_get_path('module', 'content_multigroup') .'/content_multigroup.css');
  $output = theme('table', $headers, $rows, array('id' => $table_id, 'class' => $table_class));
  $output .= drupal_render($element[$group_name .'_add_more']);

  // Enable drag-n-drop only if the group really allows multiple values.
  //drupal_add_tabledrag($table_id, 'order', 'sibling', $order_class);
  //drupal_add_js(drupal_get_path('module', 'content') .'/js/content.node_form.js');

  return $output;
}

/**
 * Theme the sub group label in the node form.
 */
function theme_content_podgroup_node_label($text) {
  return !empty($text) ? '<h3>'. $text .'</h3>' : '';
}

/**
 * Compute list of parent items base on the form and form state.
 *
 * Since the nesting options can vary during content entry we need to build the
 * list of nesting options based on the form state.
 */
function _content_podgroup_compute_nesting_options($form, $form_state) {
  // Get all the podgroups for a given node type
  $query = "SELECT group_name, settings FROM {content_group} WHERE type_name = '%s' AND group_type = 'podgroup'";
  $result = db_query($query, $form['type']['#value']);

  $podgroups = array();
  while ($row = db_fetch_array($result)) {
    $group_name = $row['group_name'];
    $settings = unserialize($row['settings']);
    $podgroups[$group_name] = array_keys($settings['podgroup']['nesting'], 1, TRUE);
  }

  // Get a list of all the nesting options per podgroup type
  if (!empty($form_state["clicked_button"]['#post'])) {
    // Since this is a post back we need to scan the form_state instead since
    // they could have added a nesting option
    $options = array();
    foreach ($podgroups as $group_name => $nesting_options) {
      foreach ($nesting_options as $parent_name) {
        if (empty($options[$group_name])) {
          $options[$group_name] == array();
          $options[$group_name][''] = t('Nesting Options');
        }

        if ($parent_name == 'group_parent') {
          $options[$group_name]['group_parent|0'] = t('Parent');
        }
        else {
          if (!empty($form_state["clicked_button"]['#post'][$parent_name])) {
            foreach ($form_state["clicked_button"]['#post'][$parent_name] as $delta => $fields) {
              $options[$group_name][$parent_name . '|' . $delta] = $fields['_title'];
            }
          }
        }
      }
    }

    // Traverse all the podgroups in the form and populate the nesting options
    foreach ($podgroups as $group_name => $nesting_options) {
      foreach ($form[$group_name] as $delta => $fields) {
        if (is_numeric($delta)) {
          $form[$group_name][$delta]['_parent']['#options'] = $options[$group_name];
        }
      }
    }

  }

  return $form;
}

/**
 * Add javascript files to the form
 */
function _content_podgroup_node_form_add_js($form){
  static $already_run = FALSE;

  // This is needed because this function is required to be called from several
  // locations and sometimes it is called multiple times, but it can only run
  // once, or the podgroup JS settings array becomes corrupted.
  if ($already_run) {
    return;
  }
  else {
    $already_run = TRUE;
  }

  $tree = content_podgroup_load_tree($form['#node']);

  $podgroups = array();
  $allowed_regions = array();
  $default_theme = variable_get('theme_default', 'garland');

  foreach (content_podgroup_load_podgroups($form['type']['#value']) as $group_name => $group) {
    foreach ($group['settings']['podgroup']['regions'] as $region => $enabled) {
      if ($enabled) {
        if (empty($allowed_regions[$region])) {
          $allowed_regions[$region] = array();
        }

        $regions = system_region_list($default_theme);
        $allowed_regions[$region]['label'] = $regions[$region];
        if (empty($allowed_regions[$region]['options'])) {
          $allowed_regions[$region]['options'] = array();
          $allowed_regions[$region]['options_by_category'] = array();
        }
        if (empty($allowed_regions[$region]['options'][$group_name])) {
          $allowed_regions[$region]['options'][$group_name] = array();
        }
        $allowed_regions[$region]['options'][$group_name]['label'] = $group['label'];
        $allowed_regions[$region]['options'][$group_name]['addButton'] = 'edit-' . strtr($group_name, '_', '-') . '-' . strtr($group_name, '_', '-') . '-add-more';
        $allowed_regions[$region]['options'][$group_name]['nesting'] = $group['settings']['podgroup']['nesting'];

        $category = !empty($group['settings']['podgroup']['category']) ? $group['settings']['podgroup']['category'] : "General";
        $allowed_regions[$region]['options'][$group_name]['category'] = $category;
        if (empty($allowed_regions[$region]['options_by_category'][$category])) {
          $allowed_regions[$region]['options_by_category'][$category] = array();
        }
        $allowed_regions[$region]['options_by_category'][$category][$group_name] = $allowed_regions[$region]['options'][$group_name];
      }
    }
    if (isset($form[$group_name])) {
      $podgroups[$group_name] = $form[$group_name];
      $podgroups[$group_name]['#disabled'] = TRUE;
    }
  }

  foreach ($allowed_regions as $region => $podgroup_types) {
    $safe_region = str_replace(' ', '-', drupal_strtolower($region));
    $table_id = 'podgroup-region-table-' . $safe_region;
    drupal_add_tabledrag($table_id, 'order', 'sibling', 'sort');
    drupal_add_tabledrag($table_id, 'match', 'parent', 'pgpid', 'pgpid', 'pgmid', TRUE);
  }
  /* Hard code the order for now */
  $allowed_regions_old = $allowed_regions;
  $allowed_regions = array();
  $allowed_regions['featured_content'] = $allowed_regions_old['featured_content'];
  $allowed_regions['content_top'] = $allowed_regions_old['content_top'];
  $allowed_regions['left_content'] = $allowed_regions_old['left_content'];
  $allowed_regions['content'] = $allowed_regions_old['content'];
  $allowed_regions['right_content'] = $allowed_regions_old['right_content'];
  $allowed_regions['left'] = $allowed_regions_old['left'];
  $allowed_regions['content_bottom'] = $allowed_regions_old['content_bottom'];

  drupal_add_css(drupal_get_path('module', 'content_podgroup') . '/content_podgroup.css');
  drupal_add_css(drupal_get_path('module', 'content_podgroup') . '/content_podgroup.ui.css');
  drupal_add_js(drupal_get_path('module', 'content_podgroup') . '/content_podgroup.node_form.js');
  jquery_ui_add('ui.dialog');

  // Add the active theme
  drupal_add_js(array('content_podgroup_node_form' => array('default_theme' => $default_theme)), 'setting');

  // Add a list of all the regions and their allowed podgroups per theme
  drupal_add_js(array('content_podgroup_node_form' => array('regions' => array($default_theme => $allowed_regions))), 'setting');

  // Add a the content type of the node
  drupal_add_js(array('content_podgroup_node_form' => array('content_type' => $form['#node']->type)), 'setting');

}

/**
 * Recursively walk tree data to add content to regions based on location in tree.
 */
function content_podgroup_render_podgroup_table($tree, &$tables, $depth = 0) {
  if (is_array($tree)) {
    foreach ($tree as $element) {
      if (isset($tables[$element['region']])) {
        $safe_region = str_replace(' ', '-', drupal_strtolower($element['region']));
        $order_class = $safe_region . '-delta-sort';
        $options = array();
        for ($i=$element['delta']-2; $i<=$element['delta']+2; $options[$i] = $i++);
        $weight_element = array(
          '#type' => 'weight',
          '#delta' => $element['delta'],
          '#attributes' => array(
            'class' => 'sort',
          )
        );
        $parent_element = array(
          '#type' => 'hidden',
          '#value' => $element['parent_type'] . '-' . $element['parent_delta'],
          '#attributes' => array(
            'class' => 'pgpid',
          ),
        );
        $podgroup_element = array(
          '#type' => 'hidden',
          '#value' => $element['type'] . '-' . $element['delta'],
          '#attributes' => array(
            'class' => 'pgid',
          ),
        );
        $row = array();
        $row[] = array('data' => theme('indentation', $depth) . $element['title'], 'class' => '');
        $row[] = array('data' =>
            drupal_render($weight_element)
          . drupal_render($parent_element)
          . drupal_render($podgroup_element),
          'class' => 'sort pgid pgpid ' . $order_class);
        $row[] = array('data' => l('Configure', '', array('attributes' => array('class' => 'podgroup-configure'))), 'class' => 'podgroup-configure-column');
        $tables[$element['region']]['#rows'][] = array('data' => $row, 'class' => 'draggable');
      }

      if (!empty($element['#children'])) {
        content_podgroup_render_podgroup_table($element['#children'], $tables, $depth + 1);
      }
    }
  }
}
