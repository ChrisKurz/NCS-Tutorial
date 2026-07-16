#include "CustomService_notify.h"
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

/*Note that UUIDs have Least Significant Byte ordering */
#define CUSTOM_SERVICE_NOTIFY_UUID   0x6f, 0xAD, 0x86, 0xF9, 0xE8, 0x21, 0x63, 0x8B, 0x67, 0x46, 0x01, 0x38, 0x69, 0x7A, 0x61, 0xCA                       
#define CUSTOM_CHARACTERISTIC_TX_UUID 0xFD, 0x17, 0x2D, 0x6C, 0x63, 0xE3, 0x1D, 0x9C, 0xBF, 0x4A, 0x9C, 0x18, 0x64, 0x00, 0x7B, 0xFF

#define BT_UUID_CUSTOM_SERIVCE_NOTIFY   BT_UUID_DECLARE_128(CUSTOM_SERVICE_NOTIFY_UUID)
#define BT_UUID_CUSTOM_CHAR_NOTIFY      BT_UUID_DECLARE_128(CUSTOM_CHARACTERISTIC_TX_UUID)


bool notify_enabled = false;

/* Callback Functions */
void ccc_changed_cb(const struct bt_gatt_attr *attr, uint16_t value)
{
    notify_enabled = (value == BT_GATT_CCC_NOTIFY);
    printk("\nNotifications %s\n", notify_enabled ? "enabled" : "disabled");
}

/* Custom Service Declaration and Registration */
BT_GATT_SERVICE_DEFINE(CustomService_notify,                              
                BT_GATT_PRIMARY_SERVICE(BT_UUID_CUSTOM_SERIVCE_NOTIFY),   
                BT_GATT_CHARACTERISTIC(BT_UUID_CUSTOM_CHAR_NOTIFY,     
                                       BT_GATT_CHRC_NOTIFY,               
                                       BT_GATT_PERM_NONE,                 
                                       NULL, NULL, NULL),                 

BT_GATT_CCC(ccc_changed_cb,                                               
            BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),                      
);                                                                        

void CustomService_notify_send(struct bt_conn *conn, uint8_t *data, uint16_t len)
{
    if (notify_enabled) 
    {
        bt_gatt_notify(NULL, &CustomService_notify.attrs[1], data, len);
        printk("Notification sent with data: 0x%02x\r", *data);
    }
}
