#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>

static const struct bt_data ad[] = {
      BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
      BT_DATA_BYTES(BT_DATA_UUID16_ALL, 
                    0x84, 0xaa, 0x60, 0x74, 0x52, 0x8a, 0x8b, 0x86,
                    0xd3, 0x4c, 0xb7, 0x1d, 0x1d, 0xdc, 0x53, 0x8d),
};

void start_advertising(void)
{
    int err;

    err = bt_le_adv_start(BT_LE_ADV_CONN_NAME, ad, ARRAY_SIZE(ad), NULL, 0);
    if (err) {
        printk("Advertising failed to start (err %d)\n", err);
        return;
    }
    printk("McuMgr SMP Advertising successfully started\n");
}

static void connected(struct bt_conn *conn, uint8_t err)
{
    if (err) {
        printk("Connection failed (err 0x%02x)\n", err);
    } else {
        printk("Connected\n");
    }
}

static void disconnected(struct bt_conn *conn, uint8_t reason)
{
    printk("Disconnected (reason 0x%02x)\n", reason);
    start_advertising();
}

/* Register a callback structure for connection events. */
BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected = connected,
    .disconnected = disconnected,
};

void start_mcumgr_smp_bluetooth(void)
{
    int err;

    /* Initialize the Bluetooth Subsystem */
    err = bt_enable(NULL);

    if (err != 0) {
        printk("Bluetooth init failed (err %d)\n", err);
        return;
    }
    printk("Bluetooth initialized\n");
    start_advertising();
}
