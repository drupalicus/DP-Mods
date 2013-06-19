<?php

/**
 * Implementation of hook_user_default_roles().
 */
function eeandi_content_user_default_roles() {
  $roles = array();

  // Exported role: EE&I User
  $roles['EE&I User'] = array(
    'name' => 'EE&I User',
  );

  return $roles;
}
