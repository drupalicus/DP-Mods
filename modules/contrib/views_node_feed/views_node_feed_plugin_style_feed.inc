<?php
// $Id: views_node_feed_plugin_style_feed.inc,v 1.1.2.1 2008/12/07 05:33:02 andrewlevine Exp $

/**
 * @file
 * views_node_feed_plugin_style_feed.inc
 * Provides a configurable feed formatted by the selected views_node_feed template
 */
class views_node_feed_plugin_style_feed extends views_plugin_style {

  function options(&$options) {
    $options['format'] = 'Feed';
  }

  /*
   * Provide a form for setting options.
   *
   * @param array $form
   * @param array $form_state
   */
  function options_form(&$form, &$form_state) {
    $form['format'] = array(
      '#type' => 'select',
      '#title' => t('Views Node Feed Template'),
      '#options' => views_node_feed_get_feeds(),
      '#default_value' => $this->options['format'],
    );
  }
  function render() {
    $rows = array();
    $feed = views_node_feed_get_feeds($this->options['format']);
    $nodes = array();
    foreach ($this->view->result as $row) {
      $node = node_load($row->nid);
      ob_start();
      eval('?>'. $feed['node']);
      $evaluated_row = ob_get_contents();
      ob_end_clean();
      $node_output .= $evaluated_row;
      $nodes[] = $node;
    }
    ob_start();
    eval('?>'. $feed['wrapper']);
    $wrapper_output = ob_get_contents();
    ob_end_clean();
    //combine wrapper and nodes
    $output = str_replace('***VIEWS_NODE_FEED_ITEMS***', $node_output, $wrapper_output);
    // print $output;
    return $output;
    // return theme($this->theme_functions(), $this->view, $this->options, $node_output);
  }
}