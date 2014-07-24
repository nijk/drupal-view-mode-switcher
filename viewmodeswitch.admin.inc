<?php

/**
 * Implements hook_form().
 * @param $form
 * @param $form_state
 * @return mixed
 */
function view_mode_switch_edit_form($form, &$form_state) {

  //@todo: Allow for settings that toggle View Mode Switcher by entity

  $enabled_bundles = variable_get('viewmodeswitch_enabled_bundles', array());

  $form['entities'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Entities'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $node_bundles = get_bundles_by_type('node');

  $form['entities']['node'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#description' => t('Enable View Mode Switcher on these content types.'),
    '#options' => $node_bundles,
    '#default_value' => isset($enabled_bundles['node']) ? $enabled_bundles['node'] : array(),
  );

  $user_bundles = get_bundles_by_type('user');

  $form['entities']['user'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Users'),
    '#description' => t('Enable View Mode Switcher on these user types.'),
    '#options' => $user_bundles,
    '#default_value' => isset($enabled_bundles['user']) ? $enabled_bundles['user'] : array(),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}


function view_mode_switch_edit_form_submit($form, &$form_state) {
  variable_set('viewmodeswitch_enabled_bundles', $form_state['values']['entities']);
  drupal_set_message(t('View Mode Switcher settings saved'), 'status');
}

/**
 * Returns bundles by type for select lists, radios, checkboxes
 * @param $type
 * @return mixed
 */
function get_bundles_by_type($type){
  $all_bundles = field_info_bundles();
  $bundles = array();
  foreach($all_bundles[$type] as $bundle_name => $bundle_type){
    $bundles[$bundle_name] = $bundle_type['label'];
  }
  return $bundles;
}
