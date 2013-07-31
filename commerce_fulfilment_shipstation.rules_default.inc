<?php

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_fulfilment_shipstation_default_rules_configuration() {
  $items = array();

  $items['commerce_fulfilment_shipstation_order_fulfilment_success'] = entity_import('rules_config', '{
    "commerce_fulfilment_shipstation_order_fulfilment_success" : {
      "LABEL" : "Order has been fulfilled",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Commerce ShipStation" ],
      "REQUIRES" : [ "rules", "commerce_order", "commerce_fulfilment_oms" ],
      "ON" : [ "commerce_fulfilment_shipstation_order_success" ],
      "DO" : [
        { "commerce_order_update_status" : { "commerce_order" : [ "commerce_order" ], "order_status" : "completed" } }
      ]
    }
  }');

  return $items;
}
