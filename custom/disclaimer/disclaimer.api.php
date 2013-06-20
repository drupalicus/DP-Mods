<?php


/**
 * Implementation of hook_disclaimer().
 *
 * Allow other modules to alter the list of nids
 * who's disclaimers will be added before they are added
 */
function mymodule_disclaimer(&$nids) {
  $query = db_query('
    SELECT n.nid AS nid
    FROM {node} n
    WHERE n.type = "mytype"
    ');

  $nids = array();
  foreach (db_fetch_array($query)) {
    $nids[] = $row['nid'];
  }

  return $nids;
}


/**
 * Add nids to the list of nids whos disclaimers will be rendered
 */
disclaimer_add_nids($nids = array());
