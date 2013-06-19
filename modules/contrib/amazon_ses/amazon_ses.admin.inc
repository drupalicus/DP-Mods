<?php
// $Id$
/**
 * @file
 * Administrative forms for Amazon SES module.
 */

/**
 * Administrative settings.
 *
 * @return
 *   An array containing form items to place on the module settings page.
 */
function amazon_ses_admin_settings() {
  $form = array();

  $form['aws-info'] = array(
    '#type' => 'fieldset',
    '#title' => t('AWS Information'),
  );
  $form['aws-info']['info'] = array(
    '#value' => amazon_ses_admin_info(),
  );

  $form['onoff'] = array(
    '#type' => 'fieldset',
    '#title' => t('Install options'),
  );
  $form['onoff']['amazon_ses_on'] = array(
    '#type' => 'radios',
    '#title' => t('Turn this module on or off'),
    '#default_value' => variable_get('amazon_ses_on', 0),
    '#options' => array(1 => t('On'), 0 => t('Off')),
    '#description' => t('To uninstall this module you must turn it off here first.'),
  );
  $form['onoff']['amazon_ses_debugging'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable debugging'),
    '#default_value' => variable_get('amazon_ses_debugging', 0),
    '#description' => t('Checking this box will print Amazon SES messages from the server for every email that is sent.'),
  );

  $form['email_options'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Email options'),
  );
  $form['email_options']['amazon_ses_from'] = array(
    '#type' => 'select',
    '#title' => t('Email from address'),
    '#default_value' => variable_get('amazon_ses_from', ''),
    '#description' => t('Select a verified email address. All email will be sent as this address.'),
    '#options' => amazon_ses_verified_addresses(),
  );
  $form['email_options']['amazon_ses_from_new'] = array(
    '#type' => 'fieldset',
    '#title' => t('Verify a new email address'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['email_options']['amazon_ses_from_new']['new_address'] = array(
    '#type' => 'textfield',
    '#title' => 'New Email address',
  );
  $form['email_options']['amazon_ses_from_new']['new_address_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array('amazon_ses_admin_new_address_submit'),
  );
  $formats = filter_formats();
  $options = array();
  foreach ($formats AS $v => $format) {
    $options[$v] = $format->name;
  }
  $form['email_options']['amazon_ses_filter_format'] = array(
    '#type' => 'select',
    '#title' => t('Input format'),
    '#description' => t('Email bodies must be converted to HTML prior to sending. Please select an Input Format to use. Full HTML recommended.'),
    '#options' => $options,
    '#default_value' => array(variable_get('amazon_ses_filter_format', 2)),
  );

  $form['email_test'] = array(
    '#type'  => 'fieldset',
    '#title' => t('Send test email'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['email_test']['amazon_ses_test_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address to send a test email to'),
    '#default_value' => '',
    '#description' => t('Type in an address to have a test email sent there.'),
  );
  $form['email_test']['amazon_ses_test_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Test body contents'),
    '#default_value' => t('If you receive this message it means your site is capable of using Amazon SES to send email.'),
  );

  $form['#submit'][] = 'amazon_ses_admin_settings_submit';
  return system_settings_form($form);
}

/**
 * Validataion for the administrative settings form.
 *
 * @param form
 *   An associative array containing the structure of the form.
 * @param form_state
 *   A keyed array containing the current state of the form.
 */
function amazon_ses_admin_settings_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Submit') && !valid_email_address($form_state['values']['new_address'])) {
    form_set_error('new_address', t('This email address is not valid.'));
  }
}

/**
 * Submission for the administrative settings form.
 *
 * @param form
 *   An associative array containing the structure of the form.
 * @param form_state
 *   A keyed array containing the current state of the form.
 */
function amazon_ses_admin_settings_submit($form, &$form_state) {
  $values = $form_state['values'];

  // If an address was given, send a test email message.
  $test_address = $values['amazon_ses_test_address'];
  if ($test_address != '') {
    global $language;
    // Clear the variable so only one message is sent.
    variable_del('amazon_ses_test_address');
    $params['subject'] = t('Drupal Amazon SES test email');
    $params['body'] = $values['amazon_ses_test_body'];
    drupal_mail('amazon_ses', 'amazon-ses-test', $test_address, $language, $params);
    drupal_set_message(t('A test email has been sent to @email.', array('@email' => $test_address)));
  }

  if ($values['amazon_ses_on']) {
    variable_set('smtp_library', drupal_get_filename('module', 'amazon_ses'));
    drupal_set_message(t('Amazon SES will be used to deliver all site e-mails.'));
    watchdog('amazon-ses', 'Aamazon SES has been enabled.');
  }
  else {
    variable_del('smtp_library');
    drupal_set_message(t('Amazon SES has been disabled.'));
    watchdog('amazon-ses', 'Amazon SES has been disabled.');
  }
}

/**
 * Submission for the administrative settings form - new address.
 *
 * @param form
 *   An associative array containing the structure of the form.
 * @param form_state
 *   A keyed array containing the current state of the form.
 */
function amazon_ses_admin_new_address_submit($form, &$form_state) {
  $address = $form_state['values']['new_address'];
  if ($address) {
    $amazon_ses = new AmazonSES();
    $new_address = $amazon_ses->verify_email_address($address);
    if ($new_address->isOK()) {
      drupal_set_message(t('The address %address has been verified. Please check your email for a confirmation message from Amazon.', array('%address' => $address)));
    }
  }
}

function amazon_ses_admin_info() {
  if ($addresses = amazon_ses_verified_addresses()) {
    $rows = array();
    if (in_array(variable_get('amazon_ses_from', ''), $addresses)) {
      $rows[] = array('Ready to send email', '<span style="color: #00ff00; font-weight: bold;">YES</span>');
    }
    else {
      $rows[] = array('Ready to send email', '<span style="color: #ff0000; font-weight: bold;">NO</span>');
      $rows[] = array(array('data' => 'You must specify an alternate Email from address below, or takes steps to verify your site\'s email address with Amazon AWS.', 'colspan' => 2));
    }
    $rows[] = array('Verified email addresses', theme('item_list', $addresses));
  }

  return theme('table', array(), $rows) . l(t('View Amazon SES statistics'), 'admin/reports/amazon_ses');
}

/**
 * Page callback -- admin/reports/amazon_ses
 */
function amazon_ses_admin_stats() {
  if ($quota = amazon_ses_quota()) {
    $rows = array();
    foreach (array(
        'SentLast24Hours' => t('Emails sent in the past 24 hours:'),
        'Max24HourSend' => t('Maximum number of emails you can send per 24 hours:'),
        'MaxSendRate' => t('Maximum number of emails you can send per second:'
      )) AS $k => $v) {
      $rows[] = array($v, str_replace('.0', '', (string) $quota->$k));
    }
    $output = theme('table', array(array('data' => 'Quota', 'colspan' => 2)), $rows);
  }

/*
  if ($stats = amazon_ses_send_statistics()) {
    $rows = array();
    // Doesn't work; can't access individual records here
    foreach ($stats->SendDataPoints->member AS $k => $stat) {
      $form['stats'][$k] = array(
        '#type' => 'fieldset',
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
        '#title' => $stat->Timestamp,
      );
      $items = array();
      foreach (array('DeliveryAttempts' => t('Delivery Attempts'), 'Rejects' => t('Rejects'), 'Bounces' => t('Bounces'), 'Complaints' => t('Complaints')) AS $k => $v) {
        $items[] = $v .': '. (string) $stat->$k;
      }
      $form['stats'][$k]['data'] = array(
        '#value' => theme('item_list', $items),
      );
    }
  }
  $output .= drupal_render_form('amazon_ses_stats', $form);
 */

  $output .= l(t('Configure Amazon SES'), 'admin/settings/amazon_ses');
  return $output;
}

function amazon_ses_verified_addresses() {
  $amazon_ses = new AmazonSES();
  $verified_addresses = $amazon_ses->list_verified_email_addresses();
  if ($verified_addresses->isOK()) {
    $items = array();
    foreach ($verified_addresses->body->ListVerifiedEmailAddressesResult->VerifiedEmailAddresses->member AS $address) {
      $mail = (string) $address;
      $items[$mail] = $mail;
    }
    return $items;
  }
  else {
    drupal_set_message(t('Amazon SES request failed. Please verify <a href="!config">Amazon AWS configuration</a>.', array('!config' => url('admin/settings/creeper', array('query' => drupal_get_destination())))));
    return array();
  }
}

function amazon_ses_quota() {
  $amazon_ses = new AmazonSES();
  $quota = $amazon_ses->get_send_quota();
  if ($quota->IsOK()) {
    return $quota->body->GetSendQuotaResult;
  }
}

function amazon_ses_send_statistics() {
  $amazon_ses = new AmazonSES();
  $stats = $amazon_ses->get_send_statistics();
  if ($stats->IsOK()) {
    return $stats->body->GetSendStatisticsResult;
  }
}
