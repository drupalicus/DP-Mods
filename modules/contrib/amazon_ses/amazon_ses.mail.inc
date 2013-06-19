<?php
// $Id$

/**
 * @file
 * The code processing mail in the Amazon SES module.
 *
 */

/**
 * Modify the drupal mail system to use Amazon SES when sending emails.
 */


  /**
   * Send the email message.
   *
   * @see drupal_mail()
   *
   * @param $message
   *   A message array, as described in hook_mail_alter().
   * @return
   *   TRUE if the mail was successfully accepted, otherwise FALSE.
   */
  function amazon_ses_send($message) {
    $source = variable_get('amazon_ses_from', '');
    if (!$source) {
      drupal_set_message(t('Amazon SES can\'t send email. Please <a href="!config">configure a valid From address', array('!from' => url('admin/settings/amazon_ses'))), 'error');
      return FALSE;
    }
    $destination = array();
    $opt = array();

    $destination['ToAddresses'] = (count(explode(',', $message['to']) > 1) ? explode(',', $message['to']) : $message['to']);

    if (is_array($message['body'])) {
      $message['body'] = implode("\n\n", $message['body']);
    }

    $ses_message = array(
      'Subject.Data' => $message['subject'],
      'Body.Text.Data' => $message['body'],
      'Body.Html.Data' => check_markup($message['body'], variable_get('amazon_ses_filter_format', 2), FALSE),
    );

    $opt['ReturnPath'] = $source;
    if (isset($message['headers']['Reply-To']) && !empty($message['headers']['Reply-To'])) {
      if (strpos($message['headers']['Reply-To'], '<')) {
        $opt['ReturnPath'] = preg_replace('/>.*/', '', preg_replace('/.*</', '', $message['headers']['Reply-To']));
      }
      else {
        $opt['ReturnPath'] = $message['headers']['Reply-To'];
      }
    }

    // Parse the headers of the message
    foreach ($message['headers'] as $key => $value) {
      switch (drupal_strtolower($key)) {
        case 'content-type':
          $vars = explode('; ', $value);
          foreach ($vars as $i => $var) {
            if ($cut = strpos($var, '=')) {
              $new_var = drupal_strtolower(drupal_substr($var, $cut + 1));
              $new_key = drupal_substr($var, 0, $cut);
              unset($vars[$i]);
              $vars[$new_key] = $new_var;
            }
          }
          // Set the charset based on the provided value, if there is one.
          $charset = $vars['charset'];
          if ($charset) {
            $ses_message['Subject.Text.Charset'] = $charset;
            $ses_message['Body.Text.Charset'] = $charset;
            $ses_message['Body.Html.Charset'] = $charset;
          }
        break;

        case 'cc':
          $destination['CcAddresses'] = split(',', $value);
        break;

        case 'bcc':
          $destination['BccAddresses'] = split(',', $value);
        break;
      }
    }

    if (variable_get('amazon_ses_debugging', 0)) {
      watchdog('amazon-ses', 'Sending mail to: @to', array('@to' => $destination['ToAddresses'][0]));
      drupal_set_message(t('Sending mail to: @to.', array('@to' => $destination['ToAddresses'][0])), 'notice');
    }

    $mailer = new AmazonSES();
    $status = $mailer->send_email($source, $destination, $ses_message, $opt);

    if (!$status->isOK()) {
      watchdog('amazon-ses', 'Error sending email from @from to @to : !error_message', array('@from' => $source, '@to' => print_r($destination['ToAddresses'], TRUE), '!error_message' => (string) $status->body->Error->Message), WATCHDOG_ERROR);
      watchdog('amazon-ses', '<pre>Source: !source <br />Destination: !destination <br />Message: !message', array('!source' => print_r($source, TRUE), '!destination' => print_r($destination, TRUE), '!message' => print_r($ses_message, TRUE)), WATCHDOG_ERROR);
      return FALSE;
    }
    return TRUE;
  }
