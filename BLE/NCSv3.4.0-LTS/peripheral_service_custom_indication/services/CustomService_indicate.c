#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

/*Note that UUIDs have Least Significant Byte ordering */
#define CUSTOM_SERVICE_NOTIFY_UUID   0x70, 0xAD, 0x86, 0xF9, 0xE8, 0x21, 0x63, 0x8B, 0x67, 0x46, 0x01, 0x38, 0x69, 0x7A, 0x61, 0xCA                       
#define CUSTOM_CHARACTERISTIC_TX_UUID 0xFE, 0x17, 0x2D, 0x6C, 0x63, 0xE3, 0x1D, 0x9C, 0xBF, 0x4A, 0x9C, 0x18, 0x64, 0x00, 0x7B, 0xFF

#define BT_UUID_CUSTOM_SERIVCE_INDICATE  BT_UUID_DECLARE_128(CUSTOM_SERVICE_NOTIFY_UUID)
#define BT_UUID_CUSTOM_CHAR_INDICATE     BT_UUID_DECLARE_128(CUSTOM_CHARACTERISTIC_TX_UUID)

static struct bt_gatt_indicate_params ind_params;

bool indicate_enabled = false;

static void ccc_changed_cb(const struct bt_gatt_attr *attr, uint16_t value)
{
    indicate_enabled = (value == BT_GATT_CCC_INDICATE);
    printk("\nIndications %s\n", indicate_enabled ? "enabled" : "disabled");
}

/* Custom Service Declaration and Registration */
BT_GATT_SERVICE_DEFINE(CustomService_indicate,
                BT_GATT_PRIMARY_SERVICE(BT_UUID_CUSTOM_SERIVCE_INDICATE),
                BT_GATT_CHARACTERISTIC(BT_UUID_CUSTOM_CHAR_INDICATE,
                                       BT_GATT_CHRC_INDICATE,
                                       BT_GATT_PERM_NONE, 
                                       NULL, NULL, NULL),
                BT_GATT_CCC(ccc_changed_cb,
                            BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),                                       
);


void indicate_cb(struct bt_conn *conn, struct bt_gatt_indicate_params *params, uint8_t err)
{
    if (err) {
        printk("Indication failed with error: 0x%02x\n", err);
    } else {
        printk("Indication acknowledged by client\n");
    }
}

void CustomService_indicate_send(struct bt_conn *conn, uint8_t *data)
{
    if (indicate_enabled) 
    {
        ind_params.attr = &CustomService_indicate.attrs[2]; // Assuming the characteristic is the second attribute in the service
        ind_params.data = data;
        ind_params.len = sizeof(*data);
        ind_params.destroy = NULL; // Optional: Set a callback function to be called when the indication is complete 
        ind_params.func = indicate_cb; // Optional: Set a callback function to be called when the indication is acknowledged by the client

        bt_gatt_indicate(NULL, &ind_params); // NULL can be used to indicate to all connected clients
        printk("Indication sent with data: 0x%02x\n", *data);
    }
}