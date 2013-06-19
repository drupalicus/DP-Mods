<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function projects_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_page_settings
  $groups['project-group_page_settings'] = array(
    'group_type' => 'standard',
    'type_name' => 'project',
    'group_name' => 'group_page_settings',
    'label' => 'Page Settings',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsible',
        'description' => '',
      ),
      'display' => array(
        'weight' => '47',
        'parent' => '',
        'label' => 'hidden',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'hidden',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '47',
    'parent' => '',
    'fields' => array(
      '0' => 'field_page_left_menu',
      '1' => 'field_page_breadcrumb',
      '2' => 'field_parent_menu',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_project_images
  $groups['project-group_project_images'] = array(
    'group_type' => 'multigroup',
    'type_name' => 'project',
    'group_name' => 'group_project_images',
    'label' => 'Images',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsible',
        'description' => '',
      ),
      'display' => array(
        'weight' => '39',
        'parent' => '',
        'label' => 'hidden',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 1,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'settings' => array(),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
      'multigroup' => array(
        'subgroup' => array(
          'weight' => -20,
          'label' => 'hidden',
          'teaser' => array(
            'format' => 'simple',
            'exclude' => 0,
          ),
          'full' => array(
            'format' => 'simple',
            'exclude' => 0,
          ),
          '4' => array(
            'format' => 'fieldset',
            'exclude' => 0,
          ),
          'token' => array(
            'format' => 'fieldset',
            'exclude' => 0,
          ),
        ),
        'multiple-columns' => 0,
        'required' => 0,
        'multiple' => '1',
        'labels' => array(
          '0' => '',
          '1' => '',
          '2' => '',
          '3' => '',
          '4' => '',
          '5' => '',
          '6' => '',
          '7' => '',
          '8' => '',
          '9' => '',
        ),
      ),
    ),
    'weight' => '39',
    'parent' => '',
    'fields' => array(
      '0' => 'field_project_images',
      '1' => 'field_project_image_description',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_project_private
  $groups['project-group_project_private'] = array(
    'group_type' => 'standard',
    'type_name' => 'project',
    'group_name' => 'group_project_private',
    'label' => 'Private Data',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'weight' => '34',
        'parent' => '',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'description' => '',
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '34',
    'parent' => '',
    'fields' => array(
      '0' => 'field_project_date',
      '1' => 'field_project_poc',
      '2' => 'field_project_value',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_rotator
  $groups['project-group_rotator'] = array(
    'group_type' => 'standard',
    'type_name' => 'project',
    'group_name' => 'group_rotator',
    'label' => 'Rotator',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'label' => 'above',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
      ),
    ),
    'weight' => '38',
    'parent' => '',
    'fields' => array(),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Images');
  t('Page Settings');
  t('Private Data');
  t('Rotator');

  return $groups;
}
