<?php
function creeper_admin_settings(&$form_state) {

  $form = array();

  $form['aws-settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('AWS settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['aws-settings']['creeper_aws_id_key'] = array(
    '#type' => 'textfield',
    '#title' => t('AWS id key'),
    '#default_value' =>  variable_get('creeper_aws_id_key',''),
    '#size' => 50,
    '#maxlength' => 255,
    '#description' => t('<p>Your AWS id key.</p>'),
    '#required' => TRUE,
  );
  
  $form['aws-settings']['creeper_aws_secret_key'] = array(
    '#type' => 'textfield',
    '#title' => t('AWS Secret key'),
    '#default_value' =>  variable_get('creeper_aws_secret_key',''),
    '#size' => 50,
    '#maxlength' => 255,
    '#description' => t('<p>Your AWS secret key.</p>'),
    '#required' => TRUE,
  );
  
  $form['aws-settings']['creeper_aws_account_id'] = array(
    '#type' => 'textfield',
    '#title' => t('AWS Account ID'),
    '#default_value' =>  variable_get('creeper_aws_account_id','aws@ohmforce.com'),
    '#size' => 50,
    '#maxlength' => 255,
    '#description' => t('<p>Your AWS account id (email).</p>'),
    '#required' => TRUE,
  );


  return system_settings_form($form);
}

function creeper_admin_settings_submit($form,&$form_state) {
  variable_set('creeper_aws_id_key',$form_state['values']['creeper_aws_id_key']);
  variable_set('creeper_aws_secret_key',$form_state['values']['creeper_aws_secret_key']);
  variable_set('creeper_aws_account_id',$form_state['values']['creeper_aws_account_id']);
}
