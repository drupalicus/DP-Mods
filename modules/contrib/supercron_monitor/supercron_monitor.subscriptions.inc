<?php
/**
 * implementation of hook_notifications
 */
function supercron_monitor_notifications($op, &$arg0 = NULL, $arg1 = NULL, $arg2 = NULL) {

  switch ($op) {
    case 'subscription types':
      $types['supercron'] = array(
        'event_type' => 'supercron',
        'title' => t('Supercron'),
        'access' => 'subscribe to supercron notifications',
        'page callback' => 'supercron_monitor_user_subscriptions',
        'user page' => 'user/%user/notifications/supercron',
        'fields' => array('supercron_id'),
        'description' => t('Subscribe to supercron events')
      );
      return $types;
      break;
    case 'names':
      $subs = &$arg0;
      if ($subs->event_type == 'supercron') {
        $subs->type_name = t('Supercron');
        if (!empty($subs->fields['supercron'])) {
          $subs->names['supercron'] = 'Supercron type name';
        }
      }
      break;
   case 'subscription fields':
      // Information about available fields for subscriptions
      $fields['supercron_id'] = array(
        'name' => t('Supercron Module'),
        'field' => 'supercron_id',
        'type' => 'int',
        'options callback' => 'supercron_monitor_modules_list',
      );
      return $fields;

#    case 'node options':

#    break;
    case 'digest methods':
      $info['short'] = array(
        'type' => 'short',
        'name' => t('Short'),
        'description' => t('Produces one line per event, grouped by object'),
        'digest callback' => 'supercron_monitor_process_digest_short',
      );
      return $info;
      break;
    case 'event types':
      $types[] = array(
        'type' => 'supercron',
        'action' => 'supercron_monitor',
        'name' => t('Supercron monitor has been run'),
        'line' => t('Supercron monitor has been run line'),
        'digest' => array('supercron'),
        'description' => t('Supercron monitor'),
      );
      break;
#    case 'event trigger':

#      break;
#    case 'event queued':

#      break;
#    case 'event load':
#  
#      break;
    case 'access':
      return array(true);
      break;
    case 'query':
      if ($arg0 == 'event' && $arg1 == 'supercron' && ($params = $arg2->params)){
          $query[]['fields']['supercron_id'] = $params['supercron_id'];
          return $query;
      }
      break;
#    case 'insert':

#      break;
#    case 'update':
# 
#      break;
    default:
      break;
  }
}

/**
 * create message for digest messages
 * TODO: make this use the built in template parts (ie. the notifications_message_part() function)
 */
function supercron_monitor_process_digest_short($account, $events, $subscriptions, $send_interval, $send_method, $module = 'notifications') {

 // Create message. Do all this in one replacement, then strip out the subject
  $text['subject'] = 'Supercron Notifications'; //notifications_message_part('digest', 'subject', $send_method, NULL, $module);
  $text['header'] = 'The Supercron module has processed the following problems:'; //notifications_message_part('digest', 'header', $send_method, NULL, $module);
  $text['footer'] = 'You can manage these from http://' . qualcomm_hooks_server() . '/admin/settings/supercron'; //notifications_message_part('digest', 'footer', $send_method, NULL, $module);

  $body = array();
  $body['header'] = $text['header'];

  //process each event
  foreach ($events as $event) {
    $sql = 'select s.id, s.module_name, s.timestamp, sm.last_exec_warn
            from {supercron_enabled_mods} s
            join {supercron_monitor} sm on sm.id = s.id
            where s.id = %d
            order by s.weight;';
    $result = db_query($sql, $event->params['supercron_id']);

    if($row = db_fetch_object($result)){
      $time_since = round((time() - $row->timestamp) / 60);
      $body['content'][] = $row->module_name . ' has not run for ' . $time_since . ' minutes.';
    }
  }

  $body['footer'] = $text['footer'];
    
  if(!empty($body['content'])){
    // Build the final digested message, and return in an array
    $message = array(
      'subject' => $text['subject'], 
      'body' => $body,
      'events' => $events,
      'subscriptions' => $subscriptions,
      'digest' => 'short',
    );
  }  

  return array($message);
}

/**
 * User Subscriptions page callback: List thread subscriptions
 */
function supercron_monitor_user_subscriptions($account = NULL) {
  global $user;
  if (is_null($account)) {
    $account = $user;
  }

  // query string for node subscriptions
  $query = "SELECT s.*, f.value AS supercron_id, sc.module_name
            FROM notifications s 
            INNER JOIN notifications_fields f ON s.sid = f.sid 
            LEFT JOIN supercron_enabled_mods sc ON f.value = CAST(sc.id AS CHAR)
            WHERE s.uid = %d 
            AND s.type = 'supercron' 
            AND s.event_type = 'supercron' 
            AND s.conditions = 1 
            AND f.field = 'supercron_id'
            ORDER BY sc.module_name;";
  $results =  db_query($query,  $account->uid);


  $subscriptions = $list = array();
  while ($subscription = db_fetch_object($results)) {
    $subscriptions[$subscription->supercron_id] = $subscription;
    $list[$subscription->supercron_id] = $subscription->module_name;
  }

  if (!$subscriptions) {
    $output = t('You are not currently subscribed to any supercron modules');
  }
  else {
    $output = t('You are currently subscribed to the following supercron modules:');
    $defaults = array('type' => 'supercron', 'event_type' => 'node');
    $options = array('title' => t('Module'));
    $output .= drupal_get_form('notifications_user_form', $account, 'supercron', $subscriptions, $list, $defaults, $options);
  }
  return $output;
}

/**
 * get list of modules for 'subscription fields' 'options callback'
 */
function supercron_monitor_modules_list(){
  $modules = array();
  $list = supercron_modules_list_from_db(0, 1);
  while ($row = db_fetch_object($list)) {
    $modules[$row->id] = $row->module_name;  
  }

  return $modules;
}
?>
