<?php
// $Id$

/**
 * @file
 * Implementation of node type administration functions for content podgroup.
 */

// @todo: Add hook to delete the content_type_<type>_podgroup table when the content type is deleted

/**
 * Helper function to build the multiple values options for podgroups.
 */
function content_podgroup_nesting_options($content_type = 'page') {
  // @todo: $content_type shouldn't be an optional param!
  $query = "SELECT group_name, label FROM {content_group} WHERE type_name = '%s' AND group_type = 'podgroup'";
  $result = db_query($query, $content_type);

  $options = array();
  $options['group_parent'] = t('Parent');
  while ($row = db_fetch_array($result)) {
    $options[$row['group_name']] = $row['label'];
  }
  return $options;
}

/**
 * Helper function to build the multiple values options for podgroups.
 */
function content_podgroup_region_options($content_type = 'page', $podgroup_type = NULL) {
  $options = array();

  if ($podgroup_type != NULL) {
    // Return an array with all the regions that a particular pod group can be placed in
    $query = "SELECT group_name, label, settings FROM {content_group} WHERE type_name = '%s' AND group_type = 'podgroup' AND group_name = '%s'";
    $result = db_query($query, $content_type, $podgroup_type);

    $options = array();
    if ($result) {
      $row = db_fetch_array($result);
      $temp = unserialize($row['settings']);
      $enabled_regions = array_flip(array_keys($temp['podgroup']['regions'], 1));

      $regions = array();
      if ($default_theme = variable_get('theme_default', NULL)) {
        $regions = system_region_list($default_theme);
      }

      $regions = array_merge(array('content' => ('Content')), $regions);
      $options = array_intersect_key($regions, $enabled_regions);
    }
  }
  else {
    // Return an array of all the regions for the given theme
    $options['content'] = t('Content');
    if ($default_theme = variable_get('theme_default', 'garland')) {
      $regions = system_region_list($default_theme);
      $options = array_merge($options, $regions);
    }
  }

  return $options;
}

/**
 * Validation for creating/moving fields and groups on the Manage Fields screen.
 */
function content_podgroup_field_overview_form_validate($form, &$form_state) {
  $form_values = $form_state['values'];

  $type_name = $form['#type_name'];
  $fields = array();
  $groups = array();

  $group = $form_values['_add_new_group'];
  if (array_filter(array($group['label'], $group['group_name']))) {
    $group['settings'] = field_group_default_settings($group['group_type']);
    $validation = fieldgroup_validate_name($group, $form['#type_name']);

    // If there's something wrong with the new group,
    // don't bother doing any more validation, further
    // processing will be stopped by the fieldgroup module.
    if (!empty($validation['errors'])) {
      return;
    }
    $group['group_name'] = $validation['group_name'];
    $new_group_name = $group['group_name'];
    $groups['_add_new_group'] = $group;
  }

  // See if we have fields moving into or out of a podgroup.
  // Set any fields to use the new name here so they will get processed
  // correctly by the fieldgroup module when saved.
  foreach ($form_values as $key => $values) {
    if ($values['parent'] == '_add_new_group') {
      $values['parent'] = $new_group_name;
      $form_values[$key] = $values;
    }

    if (!empty($form[$key]['#row_type']) && $form[$key]['#row_type'] == 'group') {
      // Gather up info about all groups.
      $group_name = $form_values[$key]['group']['group_name'];
      $groups[$group_name] = $form_values[$key]['group'];
    }
    if (!empty($form[$key]['#row_type']) && $form[$key]['#row_type'] == 'field') {
      if ($values['prev_parent'] != $values['parent']) {
        // Gather up fields that have moved in or out of a group.
        $fields[$key] = $form_values[$key]['field'];
      }
    }
  }

  $rebuild = FALSE;
  foreach ($fields as $field_name => $field) {
    $new_group = $form_values[$field_name]['parent'];
    $old_group = $form_values[$field_name]['prev_parent'];
    if (!empty($new_group) && isset($groups[$new_group]) && $groups[$new_group]['group_type'] == 'podgroup') {
      $allowed_in = content_podgroup_allowed_in($field, $groups[$new_group]);
      if (!$allowed_in['allowed']) {
        form_set_error($field_name, $allowed_in['message']);
      }
      else {
        if (!empty($allowed_in['message'])) {
          drupal_set_message($allowed_in['message']);
        }
        module_load_include('inc', 'content', 'includes/content.crud');
        $content_type = content_types($type_name);
        $multiple_values = content_podgroup_nesting_options();
        $field = $content_type['fields'][$field_name];
        $field['multiple'] = TRUE;
        $field = content_field_instance_collapse($field);
        content_field_instance_update($field, FALSE);
        $rebuild = TRUE;
        drupal_set_message(t('The field %field has been updated to use multiple values needed for the %group podgroup.', array(
          '%field' => $field['label'], '%group' => $groups[$new_group]['label'])));
      }
    }
    elseif (!empty($old_group) && isset($groups[$old_group]) && $groups[$old_group]['group_type'] == 'podgroup') {
      $allowed_out = content_podgroup_allowed_out($field, $groups[$old_group]);
      if (!$allowed_out['allowed']) {
        form_set_error($field_name, $allowed_out['message']);
      }
      elseif (!empty($allowed_out['message'])) {
        drupal_set_message($allowed_out['message']);
      }
    }
  }

  // Clear caches and rebuild menu only if any field has been updated.
  if ($rebuild) {
    content_clear_type_cache(TRUE);
    menu_rebuild();
  }
}

/**
 * Submit the Fieldgroup edit form.
 *
 * Update multiple values of fields contained in podgroups.
 */
function content_podgroup_field_overview_form_submit($form, &$form_state) {
  if (isset($form_state['values']['_add_new_group']) && $form_state['values']['_add_new_group']['group_type'] == 'podgroup') {

    $podgroup_table_name = 'content_type_' . $form['#type_name'] . '_podgroup';
    $query = "show tables like '$podgroup_table_name'";
    $result = db_query($query);

    if (db_affected_rows($result) == 0) {
      content_podgroup_create_podgroups_table($form['#type_name']);
    }
  }
}

/**
 * create empty content_type_X_podgroups table where X is the $content_type
 */
function content_podgroup_create_podgroups_table($content_type){
  $podgroup_table_name = 'content_type_' . $content_type . '_podgroup';

  // Create the DB table to store podgroups
  // Using preorder tree traversal method
  // http://articles.sitepoint.com/article/hierarchical-data-database/2
  $schema = array();
  $schema['description'] = "Stores each podgroup, its parent info, and its preorder tree traversal information";
  $schema['fields'] = array(
    'nid' => array('type' => 'int', 'not null' => TRUE, 'views' => TRUE),
    'vid' => array('type' => 'int', 'not null' => TRUE, 'views' => TRUE),
    'type' => array('type' => 'varchar', 'length' => 255, 'not null' => TRUE, 'views' => TRUE),
    'delta' => array('type' => 'int', 'not null' => TRUE, 'views' => TRUE),
    'title' => array('type' => 'varchar', 'length' => 255, 'not null' => TRUE, 'default' => ''),
    'parent_type' => array('type' => 'varchar', 'length' => 255, 'not null' => TRUE, 'views' => TRUE),
    'parent_delta' => array('type' => 'int', 'not null' => TRUE, 'views' => TRUE),
    'region' => array('type' => 'varchar', 'length' => 255, 'not null' => TRUE, 'views' => TRUE),
    'theme' => array('type' => 'varchar', 'length' => 255, 'not null' => TRUE, 'default' => ''),
    'subpages' => array('type' => 'int', 'not null' => TRUE, 'views' => TRUE, 'default' => 0),
    'tt_left' => array('type' => 'int', 'not null' => TRUE, 'views' => TRUE),
    'tt_right' => array('type' => 'int', 'not null' => TRUE, 'views' => TRUE),
  );
  db_create_table($ret, $podgroup_table_name, $schema);
}

/**
 * Helper function for deciding if a field is allowed into a podgroup.
 */
function content_podgroup_allowed_in($field, $group) {
  if ($group['group_type'] != 'podgroup') {
    return array('allowed' => TRUE, 'message' => '');
  }

  // We can't allow fields with more multiple values than the group has
  // to be moved into it.
  $max_existing = content_max_delta($field['field_name']);
  $multiple_values = content_podgroup_nesting_options();

  // Fields that handle their own multiple values may not have the same values
  // in Multigroup fields and normal fields. We don't know if they will work or not.

  // Adding a hook here where widgets that handle their own multiple values
  // that will work correctly in Multigroups can allow their fields in.

  if (content_handle('widget', 'multiple values', $field) != CONTENT_HANDLE_CORE) {
    $allowed_widgets = array(
      'optionwidgets_select',
      'optionwidgets_buttons',
      'optionwidgets_onoff',
      'nodereference_buttons',
      'nodereference_select',
      'userreference_buttons',
      'userreference_select',
    );
    $allowed_widgets = array_merge($allowed_widgets, module_invoke_all('content_multigroup_allowed_widgets'));
    if (!in_array($field['widget']['type'], $allowed_widgets)) {
      return array(
        'allowed' => FALSE,
        'message' => t('This change is not allowed. The field %field handles multiple values differently than the Content module. Making this change could result in the loss of data.', array('%field' => $field['widget']['label']))
      );
    }
  }

  // Allow other modules to intervene.
  // Any failure will prevent this action.
  foreach (module_implements('content_podgroup_allowed_in') as $module) {
    $function = $module .'_content_podgroup_allowed_in';
    $result = $function($field, $group);
    if ($result['allowed'] === FALSE) {
      return array('allowed' => FALSE, 'message' => $result['message']);
    }
  }

  $message = t('You are moving the field %field into a Podgroup.', array('%field' => $field['widget']['label']));

  return array('allowed' => TRUE, 'message' => $message);
}

/**
 * Helper function for deciding if a field is allowed out of a podgroup.
 */
function content_podgroup_allowed_out($field, $group) {
  if ($group['group_type'] != 'podgroup') {
    return array('allowed' => TRUE, 'message' => '');
  }
  // Optionwidgets do not behave the same in a Multigroup field as out of it.
  // In a Multigroup the same option can be selected multiple times,
  // but that is not possible in a normal group.

  // Adding a hook here where widgets that handle their own multiple values
  // can indicate their fields should not be removed from Multigroups.

  $max_existing = content_max_delta($field['field_name']);
  $no_remove_widgets = array(
    'optionwidgets_select',
    'optionwidgets_buttons',
    'optionwidgets_onoff',
    'nodereference_buttons',
    'nodereference_select',
    'userreference_buttons',
    'userreference_select',
  );
  $no_remove_widgets = array_merge($no_remove_widgets, module_invoke_all('content_multigroup_no_remove_widgets'));
  if (in_array($field['widget']['type'], $no_remove_widgets) && $max_existing > 0) {
    return array(
      'allowed' => FALSE,
      'message' => t('This change is not allowed. The field %field already has data created and uses a widget that stores data differently in a Standard group than in a podgroup. Making this change could result in the loss of data.', array('%field' => $field['widget']['label']))
    );
  }

  // Allow other modules to intervene.
  // Any failure will prevent this action.
  foreach (module_implements('content_podgroup_allowed_out') as $module) {
    $function = $module .'_content_podgroup_allowed_out';
    $result = $function($field, $group);
    if ($result['allowed'] === FALSE) {
      return array('allowed' => FALSE, 'message' => $result['message']);
    }
  }

  $message = t('You are moving the field %field out of a podgroup.', array('%field' => $field['widget']['label']));

  return array('allowed' => TRUE, 'message' => $message);
}

/**
 * Alter the basic field settings form.
 *
 * It should not be possible to choose a widget type that is not compatible
 * with multigroups.
 */
function content_podgroup_field_basic_form(&$form, &$form_state) {
  $field_name = $form['basic']['field_name']['#value'];
  $type_name = $form['type_name']['#value'];

  // Ignore this field if it is not part of a field group.
  if (!($group_name = fieldgroup_get_group($type_name, $field_name))) {
    return;
  }

  // Retrieve information about the group the field is in.
  $groups = fieldgroup_groups($type_name);
  $group = $groups[$group_name];

  // Ignore this field if it is not part of a podgroup.
  if ($group['group_type'] != 'podgroup') {
    return;
  }

  // Retrieve information about the field itself.
  $field = content_fields($field_name, $type_name);

  // Check if the widget can be moved out of the podgroup.
  $allowed_out = content_podgroup_allowed_out($field, $group);
  if (!$allowed_out['allowed']) {
    $form['basic']['widget_type']['#disabled'] = TRUE;
    $form['basic']['widget_type']['#suffix'] = '<div class="warning">'. t('The widget type cannot be changed because the field %field already has data created and this widget stores data differently in a Standard group than in a Podgroup. Allowing this change could result in the loss of data.', array('%field' => $field['widget']['label'])) .'</div>';
    return;
  }

  // Remove from the list of available widgets those that are not
  // compatible with multigroups.
  $widget_types = _content_widget_types();
  foreach (array_keys($form['basic']['widget_type']['#options']) as $widget_type) {
    if ($field['widget']['type'] != $widget_type) {
      $field_copy = $field;
      $field_copy['widget']['type'] = $widget_type;
      $field_copy['widget']['module'] = $widget_types[$widget_type]['module'];
      $allowed_in = content_podgroup_allowed_in($field_copy, $group);
      if (!$allowed_in['allowed']) {
        unset($form['basic']['widget_type']['#options'][$widget_type]);
      }
    }
  }
}

/**
 * Alter the "Display fields" form.
 *
 * Add an additional selector for setting podgroup field display format.
 */
function content_podgroup_display_overview_form(&$form, &$form_state) {
  $type_name = $form['#type_name'];

  // Gather type information.
  $content_type = content_types($type_name);

  // The content module stops building the form if the type has no fields.
  if (empty($content_type['fields'])) {
    return;
  }

  foreach (content_podgroup_load_podgroups($type_name) as $group_name => $group) {
    $subgroup_name = $group_name .'_subgroup';
    unset($form[$group_name]);
    $index = array_search($group_name, $form['#groups']);
    unset($form['#groups'][$index]);
  }

  $form['#submit'] = array_merge(array('content_podgroup_display_overview_form_submit'), $form['#submit']);
}

/**
 * Alter the Fieldgroup edit form to add podgroup settings.
 */
function content_podgroup_group_edit_form(&$form, &$form_state) {
  $type_name = $form['#content_type']['type'];
  $group_name = $form['group_name']['#default_value'];

  $content_type = content_types($type_name);
  $groups = fieldgroup_groups($type_name);
  $group = $groups[$group_name];

  if ($group['group_type'] != 'podgroup') {
    return;
  }

  module_load_include('inc', 'content', 'includes/content.admin');
  module_load_include('inc', 'content', 'includes/content.crud');

  $form['group_type'] = array(
    '#type' => 'hidden',
    '#value' => $group['group_type'],
  );
  unset($form['settings']['form']);
  $form['settings']['podgroup'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pod group settings'),
    '#collapsed' => FALSE,
    '#collapsible' => TRUE,
  );

  if (isset($group['settings']['podgroup']['subgroup'])) {
    // Preserve subgroup display settings.
    $form['settings']['podgroup']['subgroup'] = array(
      '#type' => 'value',
      '#value' => $group['settings']['podgroup']['subgroup'],
    );
  }

  $form['settings']['podgroup']['required'] = array(
    '#type' => 'checkbox',
    '#title' => t('Required'),
    '#default_value' => isset($group['settings']['podgroup']['required']) ? $group['settings']['podgroup']['required'] : 0,
    '#description' => t('Enable this option to require a minimum of one collection of fields in this Podgroup.'),
  );

  $form['settings']['podgroup']['title_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Title label'),
    '#default_value' => isset($group['settings']['podgroup']['title_label']) ? $group['settings']['podgroup']['title_label'] : t('Title'),
    '#description' => t('Enter a the label text for the podgroup title field.  Note: If you leave this blank the title field will not be displayed on the front end.'),
  );
  $form['settings']['podgroup']['title_description'] = array(
    '#type' => 'textarea',
    '#title' => t('Title description'),
    '#default_value' => isset($group['settings']['podgroup']['title_description']) ? $group['settings']['podgroup']['title_description'] : t("The title will be used as the podgroup's block header"),
    '#description' => t('A description of the title field.'),
  );
  $form['settings']['podgroup']['title_default'] = array(
    '#type' => 'textfield',
    '#title' => t('Title default'),
    '#default_value' => isset($group['settings']['podgroup']['title_default']) ? $group['settings']['podgroup']['title_default'] : '',
    '#description' => t('Enter a the default title for all instances of this podgroup.'),
  );

  $form['settings']['podgroup']['category'] = array(
    '#type' => 'textfield',
    '#title' => t('Category'),
    '#default_value' => !empty($group['settings']['podgroup']['category']) ? $group['settings']['podgroup']['category'] : 'General',
    '#description' => t('Enter a category to group the podgroups by in the drop down on the node edit page.'),
  );

  $form['settings']['podgroup']['subpages'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable show on subpages option.'),
    '#default_value' => isset($group['settings']['podgroup']['subpages']) ? $group['settings']['podgroup']['subpages'] : 0,
    '#description' => t("Allow content administrators to opt to show this podgroup's block on subpages. (Ex: node/3/*)"),
  );

  $podgroup_nesting = isset($group['settings']['podgroup']['nesting']) ? $group['settings']['podgroup']['nesting'] : array();

  $form['settings']['podgroup']['nesting'] = array(
    '#type' => 'fieldset',
    '#title' => t('Nesting options'),
    '#description' => t('Select the pod types that this pod type can appear within.'),
  );

  foreach (content_podgroup_nesting_options($form['#content_type']['type']) as $key => $value) {
    $form['settings']['podgroup']['nesting'][$key] = array(
      '#type' => 'checkbox',
      '#title' => t('@value', array('@value' => $value)),
      '#default_value' => isset($podgroup_nesting[$key]) ? $podgroup_nesting[$key] : FALSE,
    );
  }

  $podgroup_regions = isset($group['settings']['podgroup']['regions']) ? $group['settings']['podgroup']['regions'] : array();

  $form['settings']['podgroup']['regions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Allowed regions'),
    '#description' => t('Select the regions where this pod types that can appear within.'),
  );

  foreach (content_podgroup_region_options($type_name) as $key => $value) {
    $form['settings']['podgroup']['regions'][$key] = array(
      '#type' => 'checkbox',
      '#title' => t('@value', array('@value' => $value)),
      '#default_value' => isset($podgroup_regions[$key]) ? $podgroup_regions[$key] : FALSE,
    );
  }

  $form['#validate'][] = 'content_podgroup_group_edit_form_validate';
  $form['#submit'][] = 'content_podgroup_group_edit_form_submit';
}

/**
 * Submit the Fieldgroup edit form.
 *
 * Update multiple values of fields contained in podgroups.
 */
function content_podgroup_group_edit_form_submit($form, &$form_state) {
  $form_values = $form_state['values'];
  $group_type = $form_values['group_type'];
  if ($group_type != 'podgroup') {
    return;
  }
  module_load_include('inc', 'content', 'includes/content.crud');
  $content_type = $form['#content_type'];
  $groups = fieldgroup_groups($content_type['type']);
  $group = $groups[$form_values['group_name']];
  $group_fields = array_intersect_key($content_type['fields'], $group['fields']);
  if (!empty($group_fields)) {
    foreach ($group_fields as $field_name => $field) {
      $field['multiple'] = TRUE;
      $field['nesting'] = $form_values['settings']['podgroup']['nesting'];
      $field['regions'] = $form_values['settings']['podgroup']['nesting'];
      $field = content_field_instance_collapse($field);
      content_field_instance_update($field, FALSE);
    }
    content_clear_type_cache(TRUE);
    menu_rebuild();
  }
}

/**
 * Callback for hook_fieldgroup_save().
 */
function _content_podgroup_fieldgroup_save($group) {
  drupal_set_message('Saved.');
  firep($group);
}
