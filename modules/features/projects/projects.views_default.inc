<?php

/**
 * Implementation of hook_views_default_views().
 */
function projects_views_default_views() {
  $views = array();

  // Exported view: featured_projects
  $view = new view;
  $view->name = 'featured_projects';
  $view->description = 'Displays a list of featured projects.';
  $view->tag = 'project';
  $view->base_table = 'node';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Featured Projects';
  $handler->display->display_options['use_more_text'] = 'View all';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = '';
  $handler->display->display_options['header']['area']['empty'] = FALSE;
  $handler->display->display_options['header']['area']['content'] = '<div class="morenews"><a href="/eeandi/solutions">View all Projects »</a></div>
<h3>Featured Projects</h3>';
  /* Field: Content: Main image (field_project_main_image) */
  $handler->display->display_options['fields']['field_project_main_image_fid']['id'] = 'field_project_main_image_fid';
  $handler->display->display_options['fields']['field_project_main_image_fid']['table'] = 'node_data_field_project_main_image';
  $handler->display->display_options['fields']['field_project_main_image_fid']['field'] = 'field_project_main_image_fid';
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['label_type'] = 'none';
  $handler->display->display_options['fields']['field_project_main_image_fid']['format'] = 'project_featured_thumb_linked';
  /* Field: Content: Customer name (field_project_customer) */
  $handler->display->display_options['fields']['field_project_customer_value']['id'] = 'field_project_customer_value';
  $handler->display->display_options['fields']['field_project_customer_value']['table'] = 'node_data_field_project_customer';
  $handler->display->display_options['fields']['field_project_customer_value']['field'] = 'field_project_customer_value';
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['max_length'] = '40';
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['link_to_node'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value']['label_type'] = 'none';
  /* Field: Node: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '84';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['title']['alter']['html'] = 1;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Sort criterion: Node: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter: Node: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter: Node: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  /* Filter: Content: Featured (field_project_featured) - Allowed values */
  $handler->display->display_options['filters']['field_project_featured_value_many_to_one']['id'] = 'field_project_featured_value_many_to_one';
  $handler->display->display_options['filters']['field_project_featured_value_many_to_one']['table'] = 'node_data_field_project_featured';
  $handler->display->display_options['filters']['field_project_featured_value_many_to_one']['field'] = 'field_project_featured_value_many_to_one';
  $handler->display->display_options['filters']['field_project_featured_value_many_to_one']['value'] = array(
    1 => '1',
  );
  /* Filter: Taxonomy: Term */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'term_data';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['value'] = 'eeandi';
  $handler->display->display_options['filters']['name']['case'] = 1;

  $views[$view->name] = $view;

  // Exported view: project_index
  $view = new view;
  $view->name = 'project_index';
  $view->description = 'Displays a list of projects.';
  $view->tag = 'project';
  $view->base_table = 'node';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_more_text'] = 'View all';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Go';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Empty text: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no projects that match your criteria.';
  /* Relationship: Taxonomy: Node */
  $handler->display->display_options['relationships']['vid']['id'] = 'vid';
  $handler->display->display_options['relationships']['vid']['table'] = 'term_node';
  $handler->display->display_options['relationships']['vid']['field'] = 'vid';
  $handler->display->display_options['relationships']['vid']['label'] = 'node_private_tags';
  $handler->display->display_options['relationships']['vid']['required'] = 1;
  /* Field: Content: Main image (field_project_main_image) */
  $handler->display->display_options['fields']['field_project_main_image_fid']['id'] = 'field_project_main_image_fid';
  $handler->display->display_options['fields']['field_project_main_image_fid']['table'] = 'node_data_field_project_main_image';
  $handler->display->display_options['fields']['field_project_main_image_fid']['field'] = 'field_project_main_image_fid';
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid']['label_type'] = 'none';
  $handler->display->display_options['fields']['field_project_main_image_fid']['format'] = 'project_thumb_linked';
  /* Field: Content: Customer name (field_project_customer) */
  $handler->display->display_options['fields']['field_project_customer_value']['id'] = 'field_project_customer_value';
  $handler->display->display_options['fields']['field_project_customer_value']['table'] = 'node_data_field_project_customer';
  $handler->display->display_options['fields']['field_project_customer_value']['field'] = 'field_project_customer_value';
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['max_length'] = '35';
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['element_class'] = 'views-field-title';
  $handler->display->display_options['fields']['field_project_customer_value']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value']['link_to_node'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value']['label_type'] = 'none';
  /* Field: Content: Main image (field_project_main_image) */
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['id'] = 'field_project_main_image_fid_1';
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['table'] = 'node_data_field_project_main_image';
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['field'] = 'field_project_main_image_fid';
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['label_type'] = 'none';
  $handler->display->display_options['fields']['field_project_main_image_fid_1']['format'] = 'project_popup_default';
  /* Field: Content: Customer name (field_project_customer) */
  $handler->display->display_options['fields']['field_project_customer_value_1']['id'] = 'field_project_customer_value_1';
  $handler->display->display_options['fields']['field_project_customer_value_1']['table'] = 'node_data_field_project_customer';
  $handler->display->display_options['fields']['field_project_customer_value_1']['field'] = 'field_project_customer_value';
  $handler->display->display_options['fields']['field_project_customer_value_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_customer_value_1']['link_to_node'] = 1;
  $handler->display->display_options['fields']['field_project_customer_value_1']['label_type'] = 'none';
  /* Field: Content: Intro text (field_project_intro) */
  $handler->display->display_options['fields']['field_project_intro_value']['id'] = 'field_project_intro_value';
  $handler->display->display_options['fields']['field_project_intro_value']['table'] = 'node_data_field_project_intro';
  $handler->display->display_options['fields']['field_project_intro_value']['field'] = 'field_project_intro_value';
  $handler->display->display_options['fields']['field_project_intro_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_intro_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_intro_value']['alter']['max_length'] = '280';
  $handler->display->display_options['fields']['field_project_intro_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_intro_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_intro_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_intro_value']['alter']['trim'] = 1;
  $handler->display->display_options['fields']['field_project_intro_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_intro_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_intro_value']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_intro_value']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_project_intro_value']['label_type'] = 'none';
  /* Field: Content: Lower body text (field_project_bottom_text) */
  $handler->display->display_options['fields']['field_project_bottom_text_value']['id'] = 'field_project_bottom_text_value';
  $handler->display->display_options['fields']['field_project_bottom_text_value']['table'] = 'node_data_field_project_bottom_text';
  $handler->display->display_options['fields']['field_project_bottom_text_value']['field'] = 'field_project_bottom_text_value';
  $handler->display->display_options['fields']['field_project_bottom_text_value']['label'] = 'Lower body text';
  $handler->display->display_options['fields']['field_project_bottom_text_value']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_bottom_text_value']['link_to_node'] = 0;
  /* Field: Content: Quick links (field_project_quick_links) */
  $handler->display->display_options['fields']['field_project_quick_links_value']['id'] = 'field_project_quick_links_value';
  $handler->display->display_options['fields']['field_project_quick_links_value']['table'] = 'node_data_field_project_quick_links';
  $handler->display->display_options['fields']['field_project_quick_links_value']['field'] = 'field_project_quick_links_value';
  $handler->display->display_options['fields']['field_project_quick_links_value']['label'] = 'Quick links';
  $handler->display->display_options['fields']['field_project_quick_links_value']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_project_quick_links_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_quick_links_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_quick_links_value']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_project_quick_links_value']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_project_quick_links_value']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_project_quick_links_value']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_project_quick_links_value']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_project_quick_links_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_quick_links_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_quick_links_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_quick_links_value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_project_quick_links_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_quick_links_value']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_project_quick_links_value']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_project_quick_links_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_quick_links_value']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_quick_links_value']['link_to_node'] = 0;
  /* Field: Content: Quick project facts (field_project_facts) */
  $handler->display->display_options['fields']['field_project_facts_value']['id'] = 'field_project_facts_value';
  $handler->display->display_options['fields']['field_project_facts_value']['table'] = 'node_data_field_project_facts';
  $handler->display->display_options['fields']['field_project_facts_value']['field'] = 'field_project_facts_value';
  $handler->display->display_options['fields']['field_project_facts_value']['label'] = 'Quick project facts';
  $handler->display->display_options['fields']['field_project_facts_value']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_project_facts_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_facts_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_facts_value']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_project_facts_value']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_project_facts_value']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_project_facts_value']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_project_facts_value']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_project_facts_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_facts_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_facts_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_facts_value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_project_facts_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_facts_value']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_project_facts_value']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_project_facts_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_facts_value']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_facts_value']['link_to_node'] = 0;
  /* Field: Content: Overview (field_project_overview) */
  $handler->display->display_options['fields']['field_project_overview_value']['id'] = 'field_project_overview_value';
  $handler->display->display_options['fields']['field_project_overview_value']['table'] = 'node_data_field_project_overview';
  $handler->display->display_options['fields']['field_project_overview_value']['field'] = 'field_project_overview_value';
  $handler->display->display_options['fields']['field_project_overview_value']['label'] = 'Overview';
  $handler->display->display_options['fields']['field_project_overview_value']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_project_overview_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_project_overview_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_project_overview_value']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_project_overview_value']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_project_overview_value']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_project_overview_value']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_project_overview_value']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_project_overview_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_project_overview_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_project_overview_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_project_overview_value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_project_overview_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_project_overview_value']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_project_overview_value']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_project_overview_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_project_overview_value']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_project_overview_value']['link_to_node'] = 0;
  /* Sort criterion: Node: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Argument: Taxonomy: Term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'term_node';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['style_plugin'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['wildcard'] = 'showall';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['tid']['validate_type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['tid']['validate_options']['vids'] = array(
    11 => 11,
  );
  $handler->display->display_options['arguments']['tid']['validate_options']['transform'] = 0;
  $handler->display->display_options['arguments']['tid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['tid']['add_table'] = 0;
  $handler->display->display_options['arguments']['tid']['require_value'] = 0;
  $handler->display->display_options['arguments']['tid']['reduce_duplicates'] = 1;
  $handler->display->display_options['arguments']['tid']['set_breadcrumb'] = 0;
  $handler->display->display_options['arguments']['tid']['use_synonym_for_summary_links'] = 0;
  /* Argument: Node: Title */
  $handler->display->display_options['arguments']['title']['id'] = 'title';
  $handler->display->display_options['arguments']['title']['table'] = 'node';
  $handler->display->display_options['arguments']['title']['field'] = 'title';
  $handler->display->display_options['arguments']['title']['style_plugin'] = 'default_summary';
  $handler->display->display_options['arguments']['title']['wildcard'] = 'showall';
  $handler->display->display_options['arguments']['title']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['title']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['title']['glossary'] = 0;
  $handler->display->display_options['arguments']['title']['ignorecase'] = 0;
  $handler->display->display_options['arguments']['title']['limit'] = '0';
  $handler->display->display_options['arguments']['title']['transform_dash'] = 0;
  $handler->display->display_options['arguments']['title']['break_phrase'] = 0;
  /* Argument: Taxonomy: Term ID */
  $handler->display->display_options['arguments']['tid_1']['id'] = 'tid_1';
  $handler->display->display_options['arguments']['tid_1']['table'] = 'term_node';
  $handler->display->display_options['arguments']['tid_1']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid_1']['style_plugin'] = 'default_summary';
  $handler->display->display_options['arguments']['tid_1']['wildcard'] = 'showall';
  $handler->display->display_options['arguments']['tid_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['tid_1']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['tid_1']['break_phrase'] = 1;
  $handler->display->display_options['arguments']['tid_1']['add_table'] = 0;
  $handler->display->display_options['arguments']['tid_1']['require_value'] = 0;
  $handler->display->display_options['arguments']['tid_1']['reduce_duplicates'] = 1;
  $handler->display->display_options['arguments']['tid_1']['set_breadcrumb'] = 0;
  $handler->display->display_options['arguments']['tid_1']['use_synonym_for_summary_links'] = 0;
  /* Filter: Node: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter: Node: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'project' => 'project',
  );
  /* Filter: Taxonomy: Term */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'term_data';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['relationship'] = 'vid';
  $handler->display->display_options['filters']['name']['value'] = 'eeandi';
  $handler->display->display_options['filters']['name']['expose']['optional'] = 1;
  $handler->display->display_options['filters']['name']['case'] = 1;
  /* Filter: Node revision: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'node_revisions';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );

  $views[$view->name] = $view;

  return $views;
}
