<?php

/**
 * Implements hook_rules_action_info().
 * 
 * The main action we have to implement here is assigning a tracking number to the order.
 * 
 */
function commerce_fulfilment_shipstation_rules_action_info() {
  $actions = array();
  
  $actions['commerce_fulfilment_shipstation_rules_assign_tracking_number'] = array (
    'label' => t('Assign a tracking number to an order'),
    'group' => t('Commerce ShipStation'),
    'parameter' => array(
      'order_number' => array(
	'type' => 'integer',
	'label' => 'Drupal Commerce Order Number',
      ),
      'tracking_number' => array(
	'type' => 'text',
	'label' => 'Shipping tracking number',
      ),
       'carrier' => array(
	'type' => 'text',
	'label' => 'Shipping carrier',
      ),
      'service' => array(
	'type' => 'text',
	'label' => 'Shipping service',
      ),
    ),
  );
  
  return $actions;

}

/**
 * Implements hook_rules_event_info()
 */
function commerce_fulfilment_shipstation_rules_event_info() {
  $events = array();
  
  $events['commerce_fulfilment_shipstation_order_success'] = array(
    'label' => t('ShipStation reports an order has completed successfully'),
    'group' => t('Commerce ShipStation'),
    'variables' => array(
      'commerce_order' => array(
        'label' => t('Order', array(), array('context' => 'a Drupal Commerce order')),
        'type' => 'commerce_order',
        'skip save' => TRUE,
      ),
      'tracking_number' => array(
	'type' => 'text',
	'label' => 'Shipping tracking number',
      ),
      'carrier' => array(
	'type' => 'text',
	'label' => 'Shipping carrier',
      ),
      'service' => array(
	'type' => 'text',
	'label' => 'Shipping service',
      ),
    ),
  );
  
  return $events;
  
}

/**
 * Get tracking URL
 *
 * Should be provided by a hook ... or we build up a list of possible shipping services.
 */
function commerce_fulfilment_shipstation_rules_assign_tracking_number($order_number, $tracking_number, $carrier, $service) {
  dargs();
  return t('Hello, world!');
}
