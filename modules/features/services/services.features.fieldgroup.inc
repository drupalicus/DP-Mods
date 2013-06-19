<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function services_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_block_ref
  $groups['service-group_block_ref'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_block_ref',
    'label' => 'Block Reference',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => '',
        'title_description' => '',
        'title_default' => '',
        'category' => 'General',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => FALSE,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 1,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 1,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 1,
          'content_top' => 1,
          'breadcrumb_top' => FALSE,
          'left_content' => 1,
          'right_content' => 1,
          'left' => 0,
          'content_bottom' => 1,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '22',
    'parent' => '',
    'fields' => array(
      '0' => 'field_pod_block_ref',
      '1' => 'field_block_openhtml_class_wrap',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_list_group_tags
  $groups['service-group_list_group_tags'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_list_group_tags',
    'label' => 'List Tags Group ',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => 'The title will be used as the podgroup\'s block header',
        'title_default' => '',
        'category' => 'List',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 0,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 1,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 1,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 1,
          'breadcrumb_top' => 0,
          'left_content' => 1,
          'right_content' => 1,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '6',
    'parent' => '',
    'fields' => array(
      '0' => 'field_list_group_description',
      '1' => 'field_list_group_tags',
      '2' => 'field_list_group_heading_link',
      '3' => 'field_list_group_display',
      '4' => 'field_list_group_tags_show_date',
      '5' => 'field_list_group_tags_m',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_page_settings
  $groups['service-group_page_settings'] = array(
    'group_type' => 'standard',
    'type_name' => 'service',
    'group_name' => 'group_page_settings',
    'label' => 'Page Settings',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '25',
    'parent' => '',
    'fields' => array(
      '0' => 'field_page_layout',
      '1' => 'field_page_left_menu',
      '2' => 'field_page_breadcrumb',
      '3' => 'field_disclaimer',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_callout
  $groups['service-group_pod_callout'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_callout',
    'label' => 'Callouts',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => '',
        'title_default' => '',
        'category' => 'General',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 1,
          'group_pod_sbs' => 1,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 1,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 1,
          'breadcrumb_top' => 0,
          'left_content' => 1,
          'right_content' => 0,
          'left' => 0,
          'content_bottom' => 1,
          'footer_left' => 0,
          'footer_right' => 0,
          'search_block' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '21',
    'parent' => '',
    'fields' => array(
      '0' => 'field_pod_callout_desc',
      '1' => 'field_pod_callout_image',
      '2' => 'field_pod_callout_link',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_content_top_image
  $groups['service-group_pod_content_top_image'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_content_top_image',
    'label' => 'Content Top Single Image',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => 'The title will be used as the podgroup\'s block header',
        'title_default' => '',
        'category' => 'General',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => FALSE,
          'group_list_group_tags' => FALSE,
          'group_pod_callout' => FALSE,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => FALSE,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => FALSE,
          'group_pod_sbs' => FALSE,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 0,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 1,
          'breadcrumb_top' => FALSE,
          'left_content' => 0,
          'right_content' => 0,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '18',
    'parent' => '',
    'fields' => array(
      '0' => 'field_pod_content_top_image',
      '1' => 'field_content_top_image_link',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_content_top_t_i
  $groups['service-group_pod_content_top_t_i'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_content_top_t_i',
    'label' => 'Content Top Text + Image',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => '',
        'title_default' => '',
        'category' => 'General',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => FALSE,
          'group_pod_callout' => FALSE,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => FALSE,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => FALSE,
          'group_pod_sbs' => FALSE,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 0,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 1,
          'breadcrumb_top' => FALSE,
          'left_content' => 0,
          'right_content' => 0,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '19',
    'parent' => '',
    'fields' => array(
      '0' => 'field_pod_content_top_text',
      '1' => 'field_pod_content_top_img',
      '2' => 'field_content_top_t_i_link',
      '3' => 'field_content_top_t_i_line',
      '4' => 'field_content_top_t_i_border',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_faq_item
  $groups['service-group_pod_faq_item'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_faq_item',
    'label' => 'FAQ Item',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Question',
        'title_description' => '',
        'title_default' => '',
        'category' => 'FAQ',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 0,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 1,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 0,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 1,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 0,
          'breadcrumb_top' => 0,
          'left_content' => 0,
          'right_content' => 0,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '17',
    'parent' => '',
    'fields' => array(
      '0' => 'field_pod_faq_item_answer',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_faq_wrapper
  $groups['service-group_pod_faq_wrapper'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_faq_wrapper',
    'label' => 'FAQ Wrapper',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => '',
        'title_default' => '',
        'category' => 'FAQ',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 0,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 1,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 0,
          'breadcrumb_top' => 0,
          'left_content' => 0,
          'right_content' => 0,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '16',
    'parent' => '',
    'fields' => array(
      '0' => 'field_h',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_ft_img_btn_subnav
  $groups['service-group_pod_ft_img_btn_subnav'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_ft_img_btn_subnav',
    'label' => 'Feature Image with Button and Sub Navigation',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => '',
        'title_default' => '',
        'category' => 'Header Features',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 0,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 0,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 1,
          'content_top' => 0,
          'breadcrumb_top' => 0,
          'left_content' => 0,
          'right_content' => 0,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '20',
    'parent' => '',
    'fields' => array(
      '0' => 'field_pod_ft_i_b_sn_image',
      '1' => 'field_pod_ft_i_b_sn_button',
      '2' => 'field_pod_ft_i_b_sn_move_nav',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_gold_btn
  $groups['service-group_pod_gold_btn'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_gold_btn',
    'label' => 'Gold Button Form',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => 'The title will be used as the podgroup\'s block header',
        'title_default' => '',
        'category' => 'General',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 1,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_gold_btn' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 0,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 1,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 1,
          'breadcrumb_top' => 0,
          'left_content' => 0,
          'right_content' => 0,
          'left' => 0,
          'content_bottom' => 0,
          'footer' => 0,
          'search_block' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '9',
    'parent' => '',
    'fields' => array(
      '0' => 'field_pod_gold_btn_fields',
      '1' => 'field_pod_gold_btn_text',
      '2' => 'field_pod_gold_btn_action',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_header
  $groups['service-group_pod_header'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_header',
    'label' => 'Header',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => 'The title will be used as the podgroup\'s block header',
        'title_default' => '',
        'category' => 'General',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 1,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 1,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 1,
          'content_top' => 1,
          'breadcrumb_top' => 0,
          'left_content' => 1,
          'right_content' => 1,
          'left' => 1,
          'content_bottom' => 1,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '4',
    'parent' => '',
    'fields' => array(
      '0' => 'field_k',
      '1' => 'field_pod_header_header_style',
      '2' => 'field_pod_header_subtitle',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_list_group
  $groups['service-group_pod_list_group'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_list_group',
    'label' => 'List Wrapper',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => 'The title will be used as the podgroup\'s block header',
        'title_default' => '',
        'category' => 'List',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 1,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 1,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 1,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 1,
          'breadcrumb_top' => 0,
          'left_content' => 1,
          'right_content' => 1,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '5',
    'parent' => '',
    'fields' => array(
      '0' => 'field_b',
      '1' => 'field_pod_list_group_description',
      '2' => 'field_pod_list_group_display',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_list_node_item
  $groups['service-group_pod_list_node_item'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_list_node_item',
    'label' => 'List Node Item',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => '',
        'title_description' => '',
        'title_default' => '',
        'category' => 'List',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 0,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 1,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 0,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 1,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 1,
          'breadcrumb_top' => 0,
          'left_content' => 1,
          'right_content' => 1,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '7',
    'parent' => '',
    'fields' => array(
      '0' => 'field_pod_l_n_i_list_group',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_list_open_item
  $groups['service-group_pod_list_open_item'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_list_open_item',
    'label' => 'List Open Item',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => '',
        'title_default' => '',
        'category' => 'List',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 0,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 1,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 0,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 1,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 1,
          'breadcrumb_top' => 0,
          'left_content' => 1,
          'right_content' => 1,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '8',
    'parent' => '',
    'fields' => array(
      '0' => 'field_c',
      '1' => 'field_pod_list_open_item_desc',
      '2' => 'field_pod_list_open_item_image',
      '3' => 'field_pod_list_open_item_url',
      '4' => 'field_pod_list_open_item_file',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_open_html
  $groups['service-group_pod_open_html'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_open_html',
    'label' => 'Open HTML',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => 'The title will be used as the podgroup\'s block header',
        'title_default' => '',
        'category' => 'General',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 1,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 1,
          'group_pod_sbs' => 1,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 1,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 1,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 1,
          'content_top' => 1,
          'breadcrumb_top' => 0,
          'left_content' => 1,
          'right_content' => 1,
          'left' => 1,
          'content_bottom' => 1,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '12',
    'parent' => '',
    'fields' => array(
      '0' => 'field_pod_open_html_content',
      '1' => 'field_page_openhtml_class_wrap',
      '2' => 'field_page_openhtml_showborder',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_pse_cont_right
  $groups['service-group_pod_pse_cont_right'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_pse_cont_right',
    'label' => 'Pseudo Content Right',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => 'The title will be used as the podgroup\'s block header',
        'title_default' => '',
        'category' => 'General',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => FALSE,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 0,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 1,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 0,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 1,
          'breadcrumb_top' => FALSE,
          'left_content' => 0,
          'right_content' => 0,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '24',
    'parent' => '',
    'fields' => array(
      '0' => 'field_i',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_sbs
  $groups['service-group_pod_sbs'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_sbs',
    'label' => 'Side by Side Wrapper',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => 'The title will be used as the podgroup\'s block header',
        'title_default' => '',
        'category' => 'General',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 0,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 1,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 1,
          'breadcrumb_top' => 0,
          'left_content' => 1,
          'right_content' => 0,
          'left' => 0,
          'content_bottom' => 1,
          'footer_left' => 0,
          'footer_right' => 0,
          'search_block' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '23',
    'parent' => '',
    'fields' => array(
      '0' => 'field_j',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_spotlight
  $groups['service-group_pod_spotlight'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_spotlight',
    'label' => 'Spotlight',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => '',
        'title_description' => '',
        'title_default' => '',
        'category' => 'Spotlight',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 0,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 0,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 0,
          'breadcrumb_top' => 0,
          'left_content' => 1,
          'right_content' => 1,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '10',
    'parent' => '',
    'fields' => array(
      '0' => 'field_d',
      '1' => 'field_pod_spotlight_desc',
      '2' => 'field_pod_spotlight_bg_image',
      '3' => 'field_pod_spotlight_img_align',
      '4' => 'field_pod_spotlight_file',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_tab
  $groups['service-group_pod_tab'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_tab',
    'label' => 'Tab',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => 'The title will be used as the podgroup\'s block header',
        'title_default' => '',
        'category' => 'Tabs',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 0,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 0,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 1,
        ),
        'regions' => array(
          'content' => 0,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 1,
          'breadcrumb_top' => 0,
          'left_content' => 0,
          'right_content' => 0,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '15',
    'parent' => '',
    'fields' => array(
      '0' => 'field_g',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_pod_tabs_wrapper
  $groups['service-group_pod_tabs_wrapper'] = array(
    'group_type' => 'podgroup',
    'type_name' => 'service',
    'group_name' => 'group_pod_tabs_wrapper',
    'label' => 'Tabs Wrapper',
    'settings' => array(
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'content_podgroup_display_wrapper',
          'exclude' => 0,
        ),
        'label' => NULL,
      ),
      'podgroup' => array(
        'required' => 0,
        'title_label' => 'Title',
        'title_description' => 'The title will be used as the podgroup\'s block header',
        'title_default' => '',
        'category' => 'Tabs',
        'subpages' => 0,
        'nesting' => array(
          'group_parent' => 1,
          'group_block_ref' => 0,
          'group_list_group_tags' => 0,
          'group_pod_callout' => 0,
          'group_pod_content_top_image' => 0,
          'group_pod_content_top_t_i' => 0,
          'group_pod_faq_item' => 0,
          'group_pod_faq_wrapper' => 0,
          'group_pod_ft_img_btn_subnav' => 0,
          'group_pod_header' => 0,
          'group_pod_list_group' => 0,
          'group_pod_list_node_item' => 0,
          'group_pod_list_open_item' => 0,
          'group_pod_open_html' => 0,
          'group_pod_pse_cont_right' => 0,
          'group_pod_sbs' => 0,
          'group_pod_spotlight' => 0,
          'group_pod_tab' => 0,
          'group_pod_tabs_wrapper' => 0,
        ),
        'regions' => array(
          'content' => 0,
          'header' => 0,
          'top_nav' => 0,
          'featured_content' => 0,
          'content_top' => 1,
          'breadcrumb_top' => 0,
          'left_content' => 0,
          'right_content' => 0,
          'left' => 0,
          'content_bottom' => 0,
          'footer_left' => 0,
          'footer_right' => 0,
        ),
      ),
      'form' => array(
        'description' => NULL,
      ),
    ),
    'weight' => '14',
    'parent' => '',
    'fields' => array(
      '0' => 'field_f',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Exported group: group_service_teaser_content
  $groups['service-group_service_teaser_content'] = array(
    'group_type' => 'standard',
    'type_name' => 'service',
    'group_name' => 'group_service_teaser_content',
    'label' => 'Teaser Content',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsible',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '-4',
    'parent' => '',
    'fields' => array(
      '0' => 'field_service_teaser',
      '1' => 'field_service_image',
    ),
    'depth' => 0,
    'parents' => array(
      '0' => '',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Block Reference');
  t('Callouts');
  t('Content Top Single Image');
  t('Content Top Text + Image');
  t('FAQ Item');
  t('FAQ Wrapper');
  t('Feature Image with Button and Sub Navigation');
  t('Gold Button Form');
  t('Header');
  t('List Node Item');
  t('List Open Item');
  t('List Tags Group ');
  t('List Wrapper');
  t('Open HTML');
  t('Page Settings');
  t('Pseudo Content Right');
  t('Side by Side Wrapper');
  t('Spotlight');
  t('Tab');
  t('Tabs Wrapper');
  t('Teaser Content');

  return $groups;
}
