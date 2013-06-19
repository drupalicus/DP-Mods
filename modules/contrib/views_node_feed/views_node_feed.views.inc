<?php
// $Id: views_node_feed.views.inc,v 1.1.2.1 2008/12/07 05:33:02 andrewlevine Exp $

/**
 * @file
 * views_node_feed.views.inc
 * Defines the views plugins
 */

/**
 * Implementation of hook_views_plugins().
 */
function views_node_feed_views_plugins() {
  return array(
    // 'module' => 'views_node_feed',
    'style' => array(
      'views_node_feed' => array(
        'title' => t('Views Node Feed'),
        'handler' => 'views_node_feed_plugin_style_feed',
        'theme' => 'views_node_feed_view_feed',
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'type' => 'feed',
        'help topic' => 'style-rss',
      ),
    ),
  );
}