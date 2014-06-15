<?php

/**
 * Implements hook_field_info();
 */
function viewmodeswitch_field_info() {
  $fields['viewmodeswitch'] = array(
    'label' => t('View mode switcher'),
    'description' => t('Allows switching of default view mode on a per node basis'),
    'instance_settings' => array('view_modes' => array(), 'view_mode_list' => array()),
    'settings' => array(),
    'default_widget' => 'view_mode_picker',
    'default_formatter' => 'hidden',
  );
  return $fields;
}

/**
 * Implements hook_field_widget_info();
 */
function viewmodeswitch_field_widget_info() {
  return array(
    'view_mode_picker' => array(
      'label' => t('View mode picker'),
      'description' => t('Lists available view modes'),
      'field types' => array('viewmodeswitch'),
    )
  );
}

/**
 * Implements hook_field_widget_form().
 */
function viewmodeswitch_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {

  /*dpm($field,'$field');
  dpm($items,'$items');
  dpm($form,'$form');
  dpm($form_state,'$form_state');*/


  dpm($element,'$element');
  $settings = &$instance['settings'];
  $entity = entity_get_info($instance['entity_type']);
  dpm($entity, '$entity');
  $settings['view_mode_list'] = $entity['view modes'];

  dpm($instance,'$instance');
  dpm($field,'$field');

  $options = array('default' => 'Default');
  //Add selected view modes to options array
  if(isset($instance['settings']['view_modes'])){
    //Clear down any previous allowed values
    unset($instance['settings']['allowed_values']);
    //Add the new allowed values
    foreach($instance['settings']['view_modes'] as $key => $view_mode){
      $safe_view_mode = filter_xss_admin($view_mode);
      if(!empty($safe_view_mode)){
        $instance['settings']['allowed_values'][$safe_view_mode] = $safe_view_mode;
        $options[$safe_view_mode] = $settings['view_mode_list'][$safe_view_mode]['label'];
      }
    }
  }


  $element += array(
    '#type' => 'select',
    '#options' => $options,
    //'#default_value' => ,
  );


  dpm($instance,'$instance');
  return $element;
}

function viewmodeswitch_field_settings_form() {
  //dpm('viewmodeswitch_field_settings_form');
}

function viewmodeswitch_field_instance_settings_form($field, $instance) {
  $settings = &$instance['settings'];
  $entity = entity_get_info($instance['entity_type']);
  dpm($entity, '$entity');
  $settings['view_mode_list'] = $entity['view modes'];

  //Make Entity View Modes available
  $view_mode_options = array();
  foreach($settings['view_mode_list'] as $key => $value) {
    $view_mode_options[$key] = $value['label'];
  }

  dpm($settings,'$settings');
  dpm($field, '$field');

  $form['view_modes'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enabled view modes'),
    '#description' => t('These are view modes you want to appear on the entity edit page'),
    '#options' => $view_mode_options,
    '#default_value' => isset($settings['view_modes']) ? $settings['view_modes'] : array(),
  );
  return $form;
}

function viewmodeswitch_field_widget_view_mode_picker_form_alter(&$element, &$form_state, $context) {

}


function viewmodeswitch_form_alter(&$form, &$form_state, $form_id) {
}

/**
 * Implements hook_field_is_empty().
 */
function viewmodeswitch_field_is_empty($item, $field) {
  //Handle the possibility that value may be an array or a string
  if('string' === gettype($item)){
    //dpm($item, gettype($item));
    $item = array('value' => array($item));
  }
  dpm($item['value'], gettype($item));

  foreach($item['value'] as $value){
    if(!empty($value) || (string) $value === '0'){
      return FALSE;
    }
  }
  return TRUE;
}

function viewmodeswitch_field_widget_properties_alter(&$widget, $context) {


}
