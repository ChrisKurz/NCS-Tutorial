#include <zephyr/kernel.h>
#include <zephyr/bluetooth/services/dis.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/conn.h> 
#include <zephyr/bluetooth/services/nus.h>


static void notif_enabled(bool enabled, void *ctx)
{
    ARG_UNUSED(ctx);

    printk("%s() - %s\n", __func__, (enabled ? "Enabled" : "Disabled"));
}

static void received(struct bt_conn *conn, const void *data, uint16_t len, void *ctx)
{
    ARG_UNUSED(conn);
    ARG_UNUSED(ctx);

    printk("%s() - Len: %d, Message: %.*s\n", __func__, len, len, (char *)data);
}

struct bt_nus_cb nus_listener = {
   .notif_enabled = notif_enabled,
   .received = received,
};

/* Set advertising data */
static const struct bt_data ad[] = {
     BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
     BT_DATA_BYTES(BT_DATA_UUID16_ALL, BT_UUID_16_ENCODE(BT_UUID_DIS_VAL)),
};

/* Set Scan Response data */
static const struct bt_data sd[] = {
	BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, sizeof(CONFIG_BT_DEVICE_NAME) - 1),
};

void start_advertising(void)
{
     int err;

     err = bt_le_adv_start(BT_LE_ADV_CONN_FAST_1, ad, ARRAY_SIZE(ad),
                                                  sd, ARRAY_SIZE(sd));
     if (err) {
         printk("Advertising failed to start (err %d)\n", err);
     }
     else {
         printk("Advertising successfully started\n");
     }
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

int main(void)
{
     printk("Hello World! Bluetooth DIS sample.\n");

     int err;

     /* Initialize the Bluetooth Subsystem */
     err = bt_enable(NULL);
     if (err) {
         printk("Bluetooth init failed (err %d)\n", err);
         return 0;
     }
     printk("Bluetooth initialized\n");

     err = bt_nus_cb_register(&nus_listener, NULL);
     if (err) {
         printk("Failed to register NUS callback: %d\n", err);
         return err;
     }

     start_advertising();

     while (true) {
         const char *hello_world = "Hello World!\n";

         err = bt_nus_send(NULL, hello_world, strlen(hello_world));
         printk("Data send - Result: %d\n", err);

         if (err < 0 && (err != -EAGAIN) && (err != -ENOTCONN)) {
             return err;
         }

         k_sleep(K_SECONDS(3));
     }

     return 0;
}