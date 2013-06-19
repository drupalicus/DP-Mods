<?php

/**
 * Implementation of hook_taxonomy_default_vocabularies().
 */
function projects_taxonomy_default_vocabularies() {
  return array(
    'project_type' => array(
      'name' => 'Project Type',
      'description' => '',
      'help' => '',
      'relations' => '1',
      'hierarchy' => '1',
      'multiple' => '1',
      'required' => '0',
      'tags' => '0',
      'module' => 'features_project_type',
      'weight' => '-10',
      'nodes' => array(
        'project' => 'project',
      ),
    ),
  );
}
