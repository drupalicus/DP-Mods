<?php

/**
 * hook_menu callback for Featured Content form
 */
function digi_twitter_featured_form() {
  module_load_include('inc', 'qualcomm_featured_content', 'qualcomm_featured_content.admin');
  $content = qualcomm_featured_content_get_node_form('tweet');
  return $content;
}

/**
 * Digi Twitter Admin Form
 */
function digi_twitter_admin_form() {

    drupal_add_js( drupal_get_path('module','maxlength') . '/maxlength.js' );
    drupal_add_js('
jQuery(function($) {
  $(document).ready(function() {
    var element = $("#edit-digi-twitter-banner-txt");
    element.attr("limit", 210);
    element.attr("count_dir", "1");
    Drupal.maxLength_limit(element);
    element.load(Drupal.maxLength_change);
    element.keyup(Drupal.maxLength_change);
    element.change(Drupal.maxLength_change);
  });
});', 'inline' );

    $form = array();
    $form['#attributes'] = array('enctype' => 'multipart/form-data');
    $form['#validate'][] = 'digi_twitter_admin_form_validate';
    $form['#submit'][]   = 'digi_twitter_admin_form_submit';

    // Add Image Form
    $form['image_list'] = array(
        '#type' => 'fieldset',
        '#title' => 'Preview',
        '#weight' => -12,
    );
    $form['image_list'][] = array(
        '#type' => 'markup',
        '#value' => theme('digi_twitter_banner',digi_twitter_banner_args()),
    );

    $form['digi_twitter_banner_disable'] = array(
        '#type' => 'checkbox',
        '#title' => t('Delete Image'),
        '#default_value' => '',
        '#weight' => -11,
    );

    $form['digi_twitter_banner_image'] = array(
        '#type' => 'file',
        '#title' => t('Upload New Image'),
        '#default_value' => variable_get('digi_twitter_banner_image', ''),
        '#description' => 'Maximum Filesize: 2 MB<br>Allowed Extensions: png gif jpg jpeg<br>Image will be resized to: 960x104px',
        '#weight' => -10,
    );

    $form['digi_twitter_banner_url'] = array(
        '#type' => 'textfield',
        '#title' => t('Link'),
        '#default_value' => variable_get('digi_twitter_banner_url', ''),
        '#weight' => -8,
    );

    // $form['digi_twitter_banner_title'] = array(
    //     '#type' => 'textfield',
    //     '#title' => t('Title'),
    //     '#default_value' => variable_get('digi_twitter_banner_title', ''),
    //     '#weight' => -6,
    // );

    $form['digi_twitter_banner_txt'] = array(
        '#type' => 'textarea',
        '#title' => t('Text'),
        '#default_value' => variable_get('digi_twitter_banner_txt', ''),
        '#maxlength' => 210,
        '#attributes' => array('class' => 'textarea-processed'),
        '#weight' => -4,
    );
    $form['digi_twitter_banner_txt_cnt'] = array(
        '#type' => 'markup',
        '#value' => '<div id="maxlength-digi-twitter-banner-txt" class="maxlength-counter">Content limited to 210 characters, remaining: <strong><span class="maxlength-counter-remaining">210</span></strong></div>',
        '#weight' => -3,
    );

    $form['digi_twitter_banner_txt_color'] = array(
        '#type' => 'textfield',
        '#title' => t('Text Color'),
        '#default_value' => variable_get('digi_twitter_banner_txt_color', '#FFFFFF'),
        '#weight' => -2,
    );

    $form['digi_twitter_banner_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save Settings'),
        '#weight' => 0,
    );


    return ($form);
}

/**
 * Digi Twitter Admin Form Validate
 */
function digi_twitter_admin_form_validate($form, &$form_state) {

    // No Image?
    if ($_FILES['files']['size']['digi_twitter_banner_image'] == 0) {
        return TRUE;
    }

    // File Error
    if ($_FILES['files']['error']['digi_twitter_banner_image'] == 1) {
        form_set_error('digi_twitter_banner_image', 'Error uploading file: Invalid File');
        return FALSE;
    }

    // File Type
    switch ($_FILES['files']['type']['digi_twitter_banner_image']) {
        case 'image/png':
        case 'image/gif':
        case 'image/jpg':
        case 'image/jpeg':
        break;
        default:
          form_set_error('digi_twitter_banner_image', 'Error uploading file: Invalid File Type ('.$_FILES['files']['type']['digi_twitter_banner_image'].')');
          return FALSE;
    }

    // File Size ( 2MB )
    if ($_FILES['files']['size']['digi_twitter_banner_image'] > (2097152)) {
        form_set_error('digi_twitter_banner_image', 'Error uploading file: Invalid File Size ('.$_FILES['files']['size']['digi_twitter_banner_image'].')');
        return FALSE;
    }

    return TRUE;
}

/**
 * Digi Twitter Admin Form Submit
 */
function digi_twitter_admin_form_submit($form, &$form_state) {

    $dest_dir = 'sites/default/files/digi_twitter/';

    // Make sure the Dest_dir exists
    if (is_dir($_SERVER["DOCUMENT_ROOT"].'/'.$dest_dir) === FALSE) {
        mkdir($_SERVER["DOCUMENT_ROOT"].'/'.$dest_dir, 0775);
    }

    // Save the changes
    variable_set("digi_twitter_banner_txt", $form_state['values']['digi_twitter_banner_txt']);
    variable_set("digi_twitter_banner_txt_color", $form_state['values']['digi_twitter_banner_txt_color']);
    variable_set("digi_twitter_banner_url", $form_state['values']['digi_twitter_banner_url']);


    // Process the Image File
    if (isset($_FILES['files']) && is_uploaded_file($_FILES['files']['tmp_name']['digi_twitter_banner_image'])) {
        if ($file = file_save_upload('digi_twitter_banner_image', $validators = array(), $dest_dir)) {
                if(file_set_status($file, FILE_STATUS_PERMANENT)) {
                    drupal_set_message('Image \''.$_FILES['files']['name']['digi_twitter_banner_image'].'\' Successfully Updated.','status');
                    variable_set('digi_twitter_banner_image',$file->destination);
                    digi_twitter_admin_banner_flush($dest_dir,$file->destination);
                }
        } else {
            form_set_error('digi_twitter_banner_image', 'Error uploading file.');
        }
    }

    // Disable?
    if ($form['#post']['digi_twitter_banner_disable']) {
        digi_twitter_admin_banner_flush($dest_dir,'NULL');
        unlink($_SERVER["DOCUMENT_ROOT"].'/'.digitaria_imagecache_apply_preset('twitter_banner', variable_get('digi_twitter_banner_image', '')));
        variable_set('digi_twitter_banner_image',FALSE);
        drupal_set_message('Twitter Banner Disabled','status');
    }
}

/**
 * Remove old image files
 */
function digi_twitter_admin_banner_flush($dir,$newfile) {
    $return = array();
    if ($handle = opendir($_SERVER["DOCUMENT_ROOT"].'/'.$dir)) {
        while (false !== ($file = readdir($handle))) {
            if ($file != "." && $file != ".." && substr($file,0,1) != "." && ($file != "tout") && ($dir.$file != $newfile)) {
                global $user;
                watchdog("twitter_banner", "Would delete " . $dir . $file . '. This was done by ' . $user->name);
                //unlink($dir.$file);
            }
        }
    }
}


/**
 * Digi Twitter Admin Tout Form
 */
function digi_twitter_admin_tout_form() {


    $form = array();
    $form['#attributes'] = array('enctype' => 'multipart/form-data');
    $form['#validate'][] = 'digi_twitter_admin_tout_form_validate';
    $form['#submit'][]   = 'digi_twitter_admin_tout_form_submit';

    // Add Image Form
    $form['image_list'] = array(
        '#type' => 'fieldset',
        '#title' => 'Preview',
        '#weight' => -12,
    );
    $form['image_list'][] = array(
        '#type' => 'markup',
        '#value' => '<img src="/'.digitaria_imagecache_apply_preset('twitter_tout', variable_get('digi_twitter_tout_image', '')).'" />',
        '#value' => theme('digi_twitter_tout',digi_twitter_tout_args()),
    );

    $form['digi_twitter_tout_disable'] = array(
        '#type' => 'checkbox',
        '#title' => t('Delete Image'),
        '#default_value' => '',
        '#weight' => -11,
    );

    $form['digi_twitter_tout_image'] = array(
        '#type' => 'file',
        '#title' => t('Upload New Image'),
        '#default_value' => variable_get('digi_twitter_tout_image', ''),
        '#description' => 'Maximum Filesize: 2 MB<br>Allowed Extensions: png gif jpg jpeg<br>Image will be scaled to: 205px width',
        '#weight' => -10,
    );

    $form['digi_twitter_tout_url'] = array(
        '#type' => 'textfield',
        '#title' => t('Link'),
        '#default_value' => variable_get('digi_twitter_tout_url', ''),
        '#weight' => -8,
    );

    $form['digi_twitter_tout_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save Settings'),
        '#weight' => 0,
    );

    return ($form);
}

/**
 * Digi Twitter Admin Tout Form Validate
 */
function digi_twitter_admin_tout_form_validate($form, &$form_state) {

    // No Image?
    if ($_FILES['files']['size']['digi_twitter_tout_image'] == 0) {
        return TRUE;
    }

    // File Error
    if ($_FILES['files']['error']['digi_twitter_tout_image'] == 1) {
        form_set_error('digi_twitter_tout_image', 'Error uploading file: Invalid File');
        return FALSE;
    }

    // File Type
    switch ($_FILES['files']['type']['digi_twitter_tout_image']) {
        case 'image/png':
        case 'image/gif':
        case 'image/jpg':
        case 'image/jpeg':
        break;
        default:
          form_set_error('digi_twitter_tout_image', 'Error uploading file: Invalid File Type ('.$_FILES['files']['type']['digi_twitter_tout_image'].')');
          return FALSE;
    }

    // File Size ( 2MB )
    if ($_FILES['files']['size']['digi_twitter_tout_image'] > (2097152)) {
        form_set_error('digi_twitter_banner_image', 'Error uploading file: Invalid File Size ('.$_FILES['files']['size']['digi_twitter_tout_image'].')');
        return FALSE;
    }

    return TRUE;
}

/**
 * Digi Twitter Admin Tout Form Submit
 */
function digi_twitter_admin_tout_form_submit($form, &$form_state) {

    $dest_dir = 'sites/default/files/digi_twitter/tout/';

    // Make sure the Dest_dir exists
    if (is_dir($_SERVER["DOCUMENT_ROOT"].'/'.$dest_dir) === FALSE) {
        mkdir($_SERVER["DOCUMENT_ROOT"].'/'.$dest_dir, 0775);
    }

    // Save the changes
    variable_set("digi_twitter_tout_url", $form_state['values']['digi_twitter_tout_url']);

    // Process the Image File
    if (isset($_FILES['files']) && is_uploaded_file($_FILES['files']['tmp_name']['digi_twitter_tout_image'])) {
        if ($file = file_save_upload('digi_twitter_tout_image', $validators = array(), $dest_dir)) {
                if(file_set_status($file, FILE_STATUS_PERMANENT)) {
                    drupal_set_message('Image \''.$_FILES['files']['name']['digi_twitter_tout_image'].'\' Successfully Updated.','status');
                    variable_set('digi_twitter_tout_image',$file->destination);
                    digi_twitter_admin_tout_flush($dest_dir,$file->destination);
                }
        } else {
            form_set_error('digi_twitter_tout_image', 'Error uploading file.');
        }
    }

    // Disable?
    if ($form['#post']['digi_twitter_tout_disable']) {
        digi_twitter_admin_tout_flush($dest_dir,'NULL');
        unlink($_SERVER["DOCUMENT_ROOT"].'/'.digitaria_imagecache_apply_preset('twitter_tout', variable_get('digi_twitter_tout_image', '')));
        variable_set('digi_twitter_tout_image',FALSE);
        drupal_set_message('Twitter Tout Disabled','status');
    }
}

/**
 * Remove old image files
 */
function digi_twitter_admin_tout_flush($dir,$newfile) {
    $return = array();
    if ($handle = opendir($_SERVER["DOCUMENT_ROOT"].'/'.$dir)) {
        while (false !== ($file = readdir($handle))) {
            if ($file != "." && $file != ".." && substr($file,0,1) != "." && ($dir.$file != $newfile)) {
                global $user;
                watchdog("twitter_banner", "Tout flush, Would delete " . $dir . $file . '. This was done by ' . $user->name);
                //unlink($dir.$file);
            }
        }
    }
}
