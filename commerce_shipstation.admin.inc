<?php
/**
 * @file
 *
 * Admin settings page.
 */

/**
 *
 * Implements hook_admin_page().
 *
 * Provides an interface for configuring module options.
 */
function commerce_shipstation_admin_page() {
  $form = array();

  $options = commerce_shipstation_shipping_methods(commerce_shipping_methods());

  if (empty($options)) {
    $form['commerce_shipstation_error_message'] = array(
      '#markup' => t('You\'ll need at least one shipping method module turned on. e.g., Commerce Flatrate shipping'),
    );
  }
  else {
    // shipstation username
    $form['commerce_shipstation_username'] = array(
      '#type' => 'textfield',
      '#title' => t('ShipStation Username'),
      '#required' => TRUE,
      '#default_value' => variable_get('commerce_shipstation_username', ''),
    );

    // shipstation password
    $form['commerce_shipstation_password'] = array(
      '#type' => 'password',
      '#title' => t('ShipStation Password'),
      '#required' => TRUE,
      '#default_value' => variable_get('commerce_shipstation_password', ''),
      '#attributes' => array('autocomplete' => 'off'),
    );

    // shipstation logging
    $form['commerce_shipstation_logging'] = array(
      '#type' => 'checkbox',
      '#title' => t('Log requests to ShipStation'),
      '#description' => t('If this is set, all API requests to ShipStation will be logged to Drupal watchdog.'),
      '#default_value' => variable_get('commerce_shipstation_logging', 0),
    );

    // shipstation alternate authentication
    $form['commerce_shipstation_alternate_auth'] = array(
      '#type' => 'textfield',
      '#title' => t('Alternate Authentication'),
      '#description' => t('Use this field if your web server uses CGI to run PHP.'),
      '#default_value' => variable_get('commerce_shipstation_alternate_auth', ''),
    );

    // shipstation export paging
    $form['commerce_shipstation_export_paging'] = array(
      '#type' => 'select',
      '#title' => t('Number of Records to Export per Page'),
      '#description' => t('Sets the number of orders to send to ShipStation at a time. Change this setting if you experience import timeouts.'),
      '#options' => array( 50 => 50, 75 => 75, 100 => 100, 150 => 150 ),
      '#default_value' => variable_get('commerce_shipstation_export_paging', '100'),
    );

    // select phone number field
    $form['commerce_shipstation_billing_phone_number_field'] = array(
      '#type' => 'select',
      '#title' => t('Field for billing phone number'),
      '#required' => FALSE,
      '#description' => t('Select the field you are using for phone numbers in order data here.'),
      '#options' => _commerce_shipstation_load_field_options(),
      '#default_value' => variable_get('commerce_shipstation_billing_phone_number_field', ''),
    );

    // select phone number field
    $form['commerce_shipstation_shipping_phone_number_field'] = array(
      '#type' => 'select',
      '#title' => t('Field for shipping phone number'),
      '#required' => FALSE,
      '#description' => t('Select the field you are using for phone numbers in order data here.'),
      '#options' => _commerce_shipstation_load_field_options(),
      '#default_value' => variable_get('commerce_shipstation_shipping_phone_number_field', ''),
    );

    // product bundle field to import
    $form['commerce_shipstation_bundle_field'] = array(
      '#type' => 'select',
      '#title' => t('Field used for bundled products'),
      '#required' => FALSE,
      '#description' => t('Set this if you are using an Entity Reference field on line items to create a product bundle. This will ensure that your bundled products are imported by ShipStation.'),
      '#options' => _commerce_shipstation_load_field_options(),
      '#default_value' => variable_get('commerce_shipstation_bundle_field', ''),
    );

    // shipstation order export status
    $form['commerce_shipstation_export_status'] = array(
      '#type' => 'select',
      '#title' => t('Order Status to Export into ShipStation'),
      '#required' => TRUE,
      '#options' => commerce_order_status_options_list(),
      '#default_value' => variable_get('commerce_shipstation_export_status', ''),
    );

    // shipstation order import status
    $form['commerce_shipstation_import_status'] = array(
      '#type' => 'select',
      '#title' => t('Order Status to Set After ShipStation Import'),
      '#required' => TRUE,
      '#options' => commerce_order_status_options_list(),
      '#default_value' => variable_get('commerce_shipstation_import_status', ''),
    );

    // shipstation available shipping methods
    $form['commerce_shipstation_exposed_shipping_methods'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Shipping Methods Available to ShipStation'),
      '#required' => TRUE,
      '#options' => $options, // may need to be drupal_map_assoc
      '#default_value' => variable_get('commerce_shipstation_exposed_shipping_methods', array()),
    );

    $form['actions']['#type'] = 'actions';
    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save configuration'),
    );

    $form['#submit'][] = 'commerce_shipstation_admin_page_submit';

    return $form;
  }

  return $form;
}

/**
 * Submit handler for the admin settings form.
 *
 * This submit handler is basically a copy of system_settings_form_submit
 * handler. The reason we aren't using the system_settings_form_submit handler,
 * is because we need to do something special with one of the fields (password)
 * before we store it into the variables table.
 */
function commerce_shipstation_admin_page_submit($form, &$form_state) {
  // Exclude unnecessary elements.
  form_state_values_clean($form_state);

  foreach ($form_state['values'] as $key => $value) {
    if (is_array($value) && isset($form_state['values']['array_filter'])) {
      $value = array_keys(array_filter($value));
    }
    if ($key == 'commerce_shipstation_password') {
      variable_set($key, md5($value));
    }
    else {
      variable_set($key, $value);
    }
  }

  drupal_set_message(t('The configuration options have been saved.'));
}


/**
 * Builds a list of all fields available on the site.
 */
function _commerce_shipstation_load_field_options() {
  $options = array();
  $options['None'] = t('None');
  foreach (field_info_fields() as $field_name => $field) {
    $options[$field_name] = $field_name;
  }
  return $options;
}
