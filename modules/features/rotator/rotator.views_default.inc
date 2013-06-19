<?php

/**
 * Implementation of hook_views_default_views().
 */
function rotator_views_default_views() {
  $views = array();

  // Exported view: rotator
  $view = new view;
  $view->name = 'rotator';
  $view->description = 'Rotators and slideshows';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = 'Rotator';
  $view->core = 6;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Image (field_rotator_image) */
  $handler->display->display_options['fields']['field_rotator_image_fid']['id'] = 'field_rotator_image_fid';
  $handler->display->display_options['fields']['field_rotator_image_fid']['table'] = 'node_data_field_rotator_image';
  $handler->display->display_options['fields']['field_rotator_image_fid']['field'] = 'field_rotator_image_fid';
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['label_type'] = 'none';
  $handler->display->display_options['fields']['field_rotator_image_fid']['format'] = 'rotator_image_default';
  /* Field: Content: Link (field_rotator_image_link) */
  $handler->display->display_options['fields']['field_rotator_image_link_url']['id'] = 'field_rotator_image_link_url';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['table'] = 'node_data_field_rotator_image_link';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['field'] = 'field_rotator_image_link_url';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['label_type'] = 'none';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['format'] = 'plain';
  /* Field: Content: Target (field_rotator_target) */
  $handler->display->display_options['fields']['field_rotator_target_value']['id'] = 'field_rotator_target_value';
  $handler->display->display_options['fields']['field_rotator_target_value']['table'] = 'node_data_field_rotator_target';
  $handler->display->display_options['fields']['field_rotator_target_value']['field'] = 'field_rotator_target_value';
  /* Sort criterion: Node: Post date */
  $handler->display->display_options['sorts']['created_1']['id'] = 'created_1';
  $handler->display->display_options['sorts']['created_1']['table'] = 'node';
  $handler->display->display_options['sorts']['created_1']['field'] = 'created';
  $handler->display->display_options['sorts']['created_1']['order'] = 'DESC';
  /* Argument: term */
  $handler->display->display_options['arguments']['name']['id'] = 'name';
  $handler->display->display_options['arguments']['name']['table'] = 'term_data';
  $handler->display->display_options['arguments']['name']['field'] = 'name';
  $handler->display->display_options['arguments']['name']['ui_name'] = 'term';
  $handler->display->display_options['arguments']['name']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['name']['style_plugin'] = 'default_summary';
  $handler->display->display_options['arguments']['name']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['name']['default_argument_options']['term_page'] = 0;
  $handler->display->display_options['arguments']['name']['default_argument_options']['node'] = 1;
  $handler->display->display_options['arguments']['name']['default_argument_options']['limit'] = 1;
  $handler->display->display_options['arguments']['name']['default_argument_options']['vids'] = array(
    10 => 10,
  );
  $handler->display->display_options['arguments']['name']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['name']['glossary'] = 0;
  $handler->display->display_options['arguments']['name']['ignorecase'] = 0;
  $handler->display->display_options['arguments']['name']['limit'] = '0';
  $handler->display->display_options['arguments']['name']['transform_dash'] = 0;
  $handler->display->display_options['arguments']['name']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['name']['add_table'] = 0;
  $handler->display->display_options['arguments']['name']['require_value'] = 0;
  /* Filter: Node: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'rotator_image' => 'rotator_image',
  );
  /* Filter: Node: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter: Content: Microsite rotator (field_rotator_microsite) */
  $handler->display->display_options['filters']['field_rotator_microsite_value']['id'] = 'field_rotator_microsite_value';
  $handler->display->display_options['filters']['field_rotator_microsite_value']['table'] = 'node_data_field_rotator_microsite';
  $handler->display->display_options['filters']['field_rotator_microsite_value']['field'] = 'field_rotator_microsite_value';
  $handler->display->display_options['filters']['field_rotator_microsite_value']['value']['value'] = '1';
  $handler->display->display_options['filters']['field_rotator_microsite_value']['allow_null'] = 1;

  /* Display: Slideshow */
  $handler = $view->new_display('block', 'Slideshow', 'slideshow');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Image (field_rotator_image) */
  $handler->display->display_options['fields']['field_rotator_image_fid']['id'] = 'field_rotator_image_fid';
  $handler->display->display_options['fields']['field_rotator_image_fid']['table'] = 'node_data_field_rotator_image';
  $handler->display->display_options['fields']['field_rotator_image_fid']['field'] = 'field_rotator_image_fid';
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['label_type'] = 'none';
  $handler->display->display_options['fields']['field_rotator_image_fid']['format'] = 'rotator_image_default';
  /* Field: Content: Link (field_rotator_image_link) */
  $handler->display->display_options['fields']['field_rotator_image_link_url']['id'] = 'field_rotator_image_link_url';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['table'] = 'node_data_field_rotator_image_link';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['field'] = 'field_rotator_image_link_url';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['label_type'] = 'none';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['format'] = 'plain';
  /* Field: Content: Target (field_rotator_target) */
  $handler->display->display_options['fields']['field_rotator_target_value']['id'] = 'field_rotator_target_value';
  $handler->display->display_options['fields']['field_rotator_target_value']['table'] = 'node_data_field_rotator_target';
  $handler->display->display_options['fields']['field_rotator_target_value']['field'] = 'field_rotator_target_value';
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['element_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_target_value']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_target_value']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_rotator_target_value']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_target_value']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_rotator_target_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['label_type'] = 'none';

  /* Display: Slideshow */
  $handler = $view->new_display('block', 'Slideshow', 'slideshow_center');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Image (field_rotator_image) */
  $handler->display->display_options['fields']['field_rotator_image_fid']['id'] = 'field_rotator_image_fid';
  $handler->display->display_options['fields']['field_rotator_image_fid']['table'] = 'node_data_field_rotator_image';
  $handler->display->display_options['fields']['field_rotator_image_fid']['field'] = 'field_rotator_image_fid';
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['label_type'] = 'none';
  $handler->display->display_options['fields']['field_rotator_image_fid']['format'] = 'rotator_image_small_default';
  /* Field: Content: Link (field_rotator_image_link) */
  $handler->display->display_options['fields']['field_rotator_image_link_url']['id'] = 'field_rotator_image_link_url';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['table'] = 'node_data_field_rotator_image_link';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['field'] = 'field_rotator_image_link_url';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_link_url']['label_type'] = 'none';
  $handler->display->display_options['fields']['field_rotator_image_link_url']['format'] = 'plain';
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
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 0;
  /* Field: Content: Description (field_rotator_image_description) */
  $handler->display->display_options['fields']['field_rotator_image_description_value']['id'] = 'field_rotator_image_description_value';
  $handler->display->display_options['fields']['field_rotator_image_description_value']['table'] = 'node_data_field_rotator_image_description';
  $handler->display->display_options['fields']['field_rotator_image_description_value']['field'] = 'field_rotator_image_description_value';
  $handler->display->display_options['fields']['field_rotator_image_description_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['element_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_description_value']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_description_value']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_description_value']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_description_value']['label_type'] = 'none';
  $handler->display->display_options['fields']['field_rotator_image_description_value']['format'] = 'plain';
  /* Field: Content: Target (field_rotator_target) */
  $handler->display->display_options['fields']['field_rotator_target_value']['id'] = 'field_rotator_target_value';
  $handler->display->display_options['fields']['field_rotator_target_value']['table'] = 'node_data_field_rotator_target';
  $handler->display->display_options['fields']['field_rotator_target_value']['field'] = 'field_rotator_target_value';
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['element_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_target_value']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_target_value']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_rotator_target_value']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_target_value']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_rotator_target_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_rotator_target_value']['label_type'] = 'none';
  /* Field: Content: Show caption (field_rotator_image_caption) */
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['id'] = 'field_rotator_image_caption_value';
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['table'] = 'node_data_field_rotator_image_caption';
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['field'] = 'field_rotator_image_caption_value';
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['element_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_caption_value']['label_type'] = 'none';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Argument: Taxonomy: Term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'term_node';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['tid']['style_plugin'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['default_argument_options']['term_page'] = 1;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['node'] = 0;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['limit'] = 0;
  $handler->display->display_options['arguments']['tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['tid']['break_phrase'] = 1;
  $handler->display->display_options['arguments']['tid']['add_table'] = 0;
  $handler->display->display_options['arguments']['tid']['require_value'] = 0;
  $handler->display->display_options['arguments']['tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['arguments']['tid']['set_breadcrumb'] = 0;
  $handler->display->display_options['arguments']['tid']['use_synonym_for_summary_links'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter: Node: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'rotator_image' => 'rotator_image',
  );
  /* Filter: Node: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';

  /* Display: Filmstrip */
  $handler = $view->new_display('block', 'Filmstrip', 'filmstrip');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Image (field_rotator_image) */
  $handler->display->display_options['fields']['field_rotator_image_fid']['id'] = 'field_rotator_image_fid';
  $handler->display->display_options['fields']['field_rotator_image_fid']['table'] = 'node_data_field_rotator_image';
  $handler->display->display_options['fields']['field_rotator_image_fid']['field'] = 'field_rotator_image_fid';
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_rotator_image_fid']['element_default_classes'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['link_to_node'] = 0;
  $handler->display->display_options['fields']['field_rotator_image_fid']['label_type'] = 'none';
  $handler->display->display_options['fields']['field_rotator_image_fid']['format'] = 'project_thumb_default';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Argument: Taxonomy: Term ID */
  $handler->display->display_options['arguments']['tid']['id'] = 'tid';
  $handler->display->display_options['arguments']['tid']['table'] = 'term_node';
  $handler->display->display_options['arguments']['tid']['field'] = 'tid';
  $handler->display->display_options['arguments']['tid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['tid']['style_plugin'] = 'default_summary';
  $handler->display->display_options['arguments']['tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['tid']['default_argument_options']['term_page'] = 1;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['node'] = 0;
  $handler->display->display_options['arguments']['tid']['default_argument_options']['limit'] = 0;
  $handler->display->display_options['arguments']['tid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['tid']['break_phrase'] = 1;
  $handler->display->display_options['arguments']['tid']['add_table'] = 0;
  $handler->display->display_options['arguments']['tid']['require_value'] = 0;
  $handler->display->display_options['arguments']['tid']['reduce_duplicates'] = 0;
  $handler->display->display_options['arguments']['tid']['set_breadcrumb'] = 0;
  $handler->display->display_options['arguments']['tid']['use_synonym_for_summary_links'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter: Node: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'rotator_image' => 'rotator_image',
  );
  /* Filter: Node: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';

  $views[$view->name] = $view;

  return $views;
}
