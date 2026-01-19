/*
 * Copyright (c) 2026 Nordic Semiconductor Germany 
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/mesh.h>

#include <zephyr/logging/log.h>
/** LOG MODULE REGISTRATION:
        - First parameter: module name
        - Second Parameter (optional): log level
          Following Log-Levels can be used:
            LOG_LEVEL_NONE  => OFF:     log will not be active. 
            LOG_LEVEL_ERR   => ERROR:   write only LOG_ERR messages
            LOG_LEVEL_WRN   => WARNING: write LOG_WRN and LOG_ERR messages
            LOG_LEVEL_INF   => INFO:    write LOG_INF, LOG_WRN, and LOG_ERR 
                                        messages
            LOG_LEVEL_DBG   => DEBUG:   write LOG_DBF, LOG_INF, LOG_WRN, and 
                                        LOG_ERR messages
**/
LOG_MODULE_REGISTER(MyApp_BTMesh, LOG_LEVEL_INF);


/*===========================================================================*/
/*---  Provisioning                                                          */

// device UUID
static const uint8_t dev_uuid[16] = { 
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

static int provisioning_output(bt_mesh_output_action_t action, uint8_t *number, size_t size) {
    LOG_INF("OOB Number: %d", *number);
    return 0;
}

static void provisioning_complete(uint16_t net_idx, uint16_t addr) {
    LOG_INF("Provisioning completed. NetKeyIndex and primary element address has been assigned.");
    LOG_INF("                      => NetKeyIndex: 0x%04x",net_idx);
    LOG_INF("                      => Primary element address: 0x%04x",addr);
}

static void provisioning_reset(void){
    LOG_INF("Node has been reset.");
    bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);
}    

/* Node provisioning information (properties and capabilities) */
const struct bt_mesh_prov prov = {
        .uuid = dev_uuid,
//       .uri = ,
//       .oob_info = ,
//       .public_key_be = ,
//       .private_key_be = ,
//       .static_val = ,
//       .static_val_len = ,
        .output_size = 4,
        .output_actions = BT_MESH_DISPLAY_NUMBER,
//       .input_size = ,
//       .input_actions = ,
//       .capabilities = ,
#if defined CONFIG_BT_MESH_PROV_OOB_API_LEGACY
//       .output_number = ,
#else
        .output_numeric = provisioning_output,
#endif
//       .output_string = ,
//       .input = ,
//       .input_complete = ,
//       .unprovisioned_beacon = ,
//       .unprovisioned_beacon_gatt = ,
//       .link_open = ,
//       .link_close = ,
        .complete = provisioning_complete,
//       .node_added = ,
        .reset = provisioning_reset,
};


/*===========================================================================*/
/*---  Bluetooth Mesh Model:  Health Server                                  */
        
BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);

static void attention_on(const struct bt_mesh_model *model) {
    LOG_INF("Attention on");
}

static void attention_off(const struct bt_mesh_model *model) {
    LOG_INF("Attention off");
}

const struct bt_mesh_health_srv_cb health_srv_cb = {
//    .fault_get_cur = ,          /**< Callback for fetching current faults */
//    .fault_get_reg = ,          /**< Callback for fetching all registered faults */	    
//    .fault_clear = ,            /**< Clear all registered faults associated with the given Company ID */
//    .fault_test = ,             /**< Run a self-test
    .attn_on = attention_on,    /**< Start calling attention to the device */
    .attn_off = attention_off,  /**< Stop the attention state */
};
	
struct bt_mesh_health_srv app_health_srv = {
//    .model = ,                  /**< Composition data model entry pointer */
    .cb = &health_srv_cb,       /**< Optional callback structure */
//    .attn_timer = ,             /**< Attention Timer state */
};


/*===========================================================================*/
/*---  Node Composition                                                      */
        
/* Models - an array of specific model definitions */
static struct bt_mesh_model sig_models[] = {
    BT_MESH_MODEL_CFG_SRV,
    BT_MESH_MODEL_HEALTH_SRV(&app_health_srv, &health_pub),
};
    
/* Elements - contains array of SIG models and vendor models (none in this case) */
static struct bt_mesh_elem elements[] = {
    BT_MESH_ELEM(
        0,                                /**< Location Descriptor */
        sig_models,                       /**< Array of SIG models */
        BT_MESH_MODEL_NONE                /**< Array of vendor models (none in this case) */
    ),    
};
    
/* Node composition - contains an array of elements */
const struct bt_mesh_comp comp = {
    .cid = 0xFFFF,                        /**< Company Identifier assigned by 
                                               Bluetooth SIG (https://www.bluetooth.com/specifications/assigned-numbers/) */
    .pid = 0x1234,                        /**< Vendor-assigned Product Identifier */
    .vid = 0x0001,                        /**< Vendor-assigned Version Identifier */
    .elem = elements,                     /**< List of elements */
    .elem_count = ARRAY_SIZE(elements),   /**< Number of elements in this device */
};


/*===========================================================================*/
/*---  Bluetooth Mesh Initialization                                         */
void app_btmesh_start(void) {
    int err;

    /* Initialize the Bluetooth Subsystem */
    err = bt_enable(NULL);
    if (err) {
        LOG_ERR("Bluetooth init failed (err %d)", err);
        return;
    }
    LOG_INF("Bluetooth initialized");

    err = bt_mesh_init(&prov, &comp);
    if (err) {
        LOG_ERR("bt_mesh_init failed with error %d", err);
        return;
    }
    LOG_INF("Bluetooth Mesh initialised");    

	/* This will be a no-op if settings_load() loaded provisioning info */
	bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);
}
