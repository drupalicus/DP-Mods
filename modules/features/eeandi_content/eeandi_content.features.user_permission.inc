<?php

/**
 * Implementation of hook_user_default_permissions().
 */
function eeandi_content_user_default_permissions() {
  $permissions = array();

  // Exported permission: view unpublished announcement content
  $permissions['view unpublished announcement content'] = array(
    'name' => 'view unpublished announcement content',
    'roles' => array(
      '0' => 'Content Admin',
      '1' => 'Content Editor',
      '2' => 'EE&I User',
      '3' => 'ISR User',
    ),
  );

  // Exported permission: view unpublished page content
  $permissions['view unpublished page content'] = array(
    'name' => 'view unpublished page content',
    'roles' => array(
      '0' => 'Content Admin',
      '1' => 'Content Editor',
      '2' => 'EE&I User',
      '3' => 'ISR User',
    ),
  );

  return $permissions;
}
