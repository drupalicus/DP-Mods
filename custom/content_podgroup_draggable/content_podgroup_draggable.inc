<?php
/**
 * page callback for ajax submit page for draggable podgroups
 * we need to populate each podgroup with its current database values 
 * then make the changes that we need to send to the database
 */
function content_podgroup_draggable_js_submit(){

  //convert json post to php object
  $json_post = json_decode($_POST['podgroups']);

  //load the node
  if(!empty($json_post->nid)){
    $node = node_load($json_post->nid); 
  }
  else{
    return;
  }

  //create form_values array for submitting form to drupal_execute
  $form_values =  array(
    'values' => array(
      'op' => 'Save'
    )  
  );

  //load groups from db
  $content_type_fieldgroups = fieldgroup_groups($node->type);
  foreach ($content_type_fieldgroups as $group) {
    if ($group['group_type'] == 'podgroup') {
      $form_values['values'][$group['group_name']] = content_podgroup_draggable_get_podgroup($node, $group);
    }
  }

  //Iterate over podgroups from json_post find matching group in $form_values from db, and update the weight
  foreach($json_post->podgroups as $group){
    foreach($group as $key => $field){
      $form_values['values'][$field->group_name][$field->delta]['_weight'] = $key;
    }
  }

  //This is the part that does the actual save
  module_load_include('inc', 'node', 'node.pages');
  drupal_execute('page_node_form', $form_values, $node);
}

/**
 * get a podgroup for a node by its type populated with values from the db
 */
function content_podgroup_draggable_get_podgroup($node, $group){

  //get all podgroups for node by type
  $sql = "select nid, vid, type, delta, title, parent_type, parent_delta, region, theme,tt_left, tt_right
          from content_type_page_podgroup
          where nid = %d
          and vid = %d
          and type = '%s'
          order by delta;";

  $result = db_query($sql, $node->nid, $node->vid, $group['group_name']);

  //load podgroup from db into array
  $group_data = array();
  while ($item = db_fetch_array($result)) {
    $group_item = array();
    $group_item['_title'] = $item['title'];
    $group_item['_parent'] = $item['parent_type'] . '|' . $item['parent_delta'];
    $group_item['_region'] = $item['region'];
    $group_item['_weight'] = $item['delta'];

    //add extra fields into podgroup from node
    if(!empty($group['fields'])){
      foreach($group['fields'] as $content_type_field => $content_type_field_data){
        $group_item[$content_type_field] = $node->{$content_type_field}[$item['delta']];
      }
    }  
    $group_data[] = $group_item;
  }

  return $group_data;
}



