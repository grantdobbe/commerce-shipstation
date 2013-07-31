<?php

/**
 * Implements hook_rules_action_info().
 */
function commerce_fulfilment_shipstation_rules_action_info() {
}

/**
 * Implements hook_rules_event_info()
 */
function commerce_fulfilment_shipstation_rules_event_info() {
}

/**
 * Action: Fulfill order.
 */
function commerce_fulfilment_shipstation_rules_complete_order($order, $context = array()) {

}

/**
 * Get tracking URL
 *
 * Should be provided by a hook ... or we build up a list of possible shipping services.
 */
function commerce_fulfilment_shipstation_get_tracking_url($method, $trackingnumber) {
}
