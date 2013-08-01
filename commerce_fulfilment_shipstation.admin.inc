<?php

/**
 * Admin settings page.
 */
function commerce_fulfilment_shipstation_admin_page() {
  $form = array();

  $options = commerce_fulfilment_shipstation_shipping_methods(commerce_shipping_methods());
  if (empty($options)) {
    $form['commerce_fulfilment_shipstation_error_message'] = array(
      '#markup' => t('You\'ll need at least one shipping method module turned on. e.g. Commerce Flatrate shipping'),
    );
  }
  else {
    // shipstation username
    $form['commerce_fulfilment_shipstation_username'] = array(
      '#type' => 'textfield',
      '#title' => t('ShipStation Username'),
      '#required' => TRUE,
      '#default_value' => variable_get('commerce_fulfilment_shipstation_username', ''),
    );

    // shipstation password
    $form['commerce_fulfilment_shipstation_password'] = array(
      '#type' => 'textfield',
      '#title' => t('ShipStation Password'),
      '#required' => TRUE,
      '#default_value' => variable_get('commerce_fulfilment_shipstation_password', ''),
    );

    // shipstation logging
    $form['commerce_fulfilment_shipstation_logging'] = array(
      '#type' => 'checkbox',
      '#title' => t('Log requests to ShipStation'),
      '#description' => t('If this is set, all API requests to ShipStation will be logged to Drupal watchdog.'),
      '#default_value' => variable_get('commerce_fulfilment_shipstation_logging', 0),
    );

    // shipstation alternate authentication
    $form['commerce_fulfilment_shipstation_alternate_auth'] = array(
      '#type' => 'textfield',
      '#title' => t('Alternate Authentication'),
      '#description' => t('Use this field if your web server uses CGI to run PHP.'),
      '#default_value' => variable_get('commerce_fulfilment_shipstation_alternate_auth', ''),
    );

    // shipstation export paging
    $form['commerce_fulfilment_shipstation_export_paging'] = array(
      '#type' => 'select',
      '#title' => t('Number of Records to Export per Page'),
      '#description' => t('Sets the number of orders to send to ShipStation at a time. Change this setting if you experience import timeouts.'),
      '#options' => array( 50 => 50, 75 => 75, 100 => 100, 150 => 150 ),
      '#default_value' => variable_get('commerce_fulfilment_shipstation_export_paging', '100'),
    );

    // shipstation order export status
    $form['commerce_fulfilment_shipstation_export_status'] = array(
      '#type' => 'select',
      '#title' => t('Order Status to Export into ShipStation'),
      '#required' => TRUE,
      '#options' => commerce_order_status_options_list(),
      '#default_value' => variable_get('commerce_fulfilment_shipstation_export_status', ''),
    );

    // shipstation order import status
    $form['commerce_fulfilment_shipstation_import_status'] = array(
      '#type' => 'select',
      '#title' => t('Order Status to Set After ShipStation Import'),
      '#required' => TRUE,
      '#options' => commerce_order_status_options_list(),
      '#default_value' => variable_get('commerce_fulfilment_shipstation_import_status', ''),
    );

    // shipstation available shipping methods
    $form['commerce_fulfilment_shipstation_exposed_shipping_methods'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Shipping Methods Available to ShipStation'),
      '#required' => TRUE,
      '#options' => $options, // may need to be drupal_map_assoc
      '#default_value' => variable_get('commerce_fulfilment_shipstation_exposed_shipping_methods', array()),
    );

    return system_settings_form($form);
  }

  return $form;
}