<?php

/**
 * Implements hook_rules_action_info().
 * 
 * The main action we have to implement here is assigning a tracking number to the order.
 * 
 */
function commerce_fulfilment_shipstation_rules_action_info() {
  $actions = array();
  
  $actions['commerce_fulfilment_shipstation_rules_assign_tracking_method'] = array (
    'label' => t('Assign a tracking number to an order'),
    'group' => t('Commerce ShipStation'),
    'parameter' => array(
      'order_number' = array(
	'type' => 'integer',
	'label' => 'Drupal Commerce Order Number',
      ),
      'tracking_number' = array(
	'type' => 'text',
	'label' => 'Shipping tracking number',
      ),
    ),
  );

}

/**
 * Implements hook_rules_event_info()
 */
function commerce_fulfilment_shipstation_rules_event_info() {
  $events = array();
  
  $events['commerce_fulfilment_shipstation_order_success'] = array(
    'label' => t('ShipStation reports an order has completed successfully'),
    'group' => t('Commerce ShipStation'),
    'variables' = array(
       'order_number' = array(
	'type' => 'integer',
	'label' => 'Drupal Commerce Order Number',
      ),
      'tracking_number' = array(
	'type' => 'text',
	'label' => 'Shipping tracking number',
      ),
    ),
  );
  
}

/**
 * Get tracking URL
 *
 * Should be provided by a hook ... or we build up a list of possible shipping services.
 */
function commerce_fulfilment_shipstation_rules_assign_tracking_number($order_number, $tracking_number) {
}
