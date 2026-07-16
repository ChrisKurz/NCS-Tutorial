#include <zephyr/kernel.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>

uint16_t my_value = 1234;


/* READ Callback */
static ssize_t read_my_value(struct bt_conn *conn,
                             const struct bt_gatt_attr *attr,
                             void *buf,
                             uint16_t len,
                             uint16_t offset)
{
    return bt_gatt_attr_read(conn, attr, buf, len, offset,
                             &my_value, sizeof(my_value));
}

/* Note that UUIDs have Least Significant Byte ordering */
#define CUSTOM_SERVICE_UUID        0xF0, 0x86, 0x48, 0x24, 0x54, 0xB3, 0x43, 0xA1, 0xBC, 0x20, 0x97, 0x8F, 0xC3, 0x76, 0xC2, 0x75                       
#define CUSTOM_CHARACTERISTIC_UUID 0xF1, 0xAA, 0x20, 0x11, 0x92, 0xE7, 0x43, 0x5A, 0xAA, 0xE9, 0x94, 0x43, 0x35, 0x6A, 0xD4, 0xD3

#define BT_UUID_CUSTOM_SERIVCE         BT_UUID_DECLARE_128(CUSTOM_SERVICE_UUID)
#define BT_UUID_CUSTOM_CHARACTERISTIC  BT_UUID_DECLARE_128(CUSTOM_CHARACTERISTIC_UUID)

/* Custom Service Declaration and Registration */
BT_GATT_SERVICE_DEFINE(CustomService_read,
                BT_GATT_PRIMARY_SERVICE(BT_UUID_CUSTOM_SERIVCE),
                BT_GATT_CHARACTERISTIC(BT_UUID_CUSTOM_CHARACTERISTIC,
                                       BT_GATT_CHRC_READ,
                                       BT_GATT_PERM_READ, 
                                       read_my_value, NULL, NULL),
);


void CustomService_read_init(void)
{
    printk("CustomService_read initialized\n");
}