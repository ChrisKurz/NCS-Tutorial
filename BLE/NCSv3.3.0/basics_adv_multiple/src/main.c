#include <zephyr/kernel.h>
#include <zephyr/bluetooth/services/dis.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/conn.h> 

#define NON_CONNECTABLE_DEVICE_NAME "My Beacon"

#define NON_CONNECTABLE_ADV_IDX 0
#define CONNECTABLE_ADV_IDX     1

static int connectable_adv_create(void);

static struct bt_le_ext_adv *ext_adv[CONFIG_BT_EXT_ADV_MAX_ADV_SET];
static const struct bt_le_adv_param *non_connectable_adv_param =
    BT_LE_ADV_PARAM(BT_LE_ADV_OPT_SCANNABLE,
                    0x140, /* 200 ms */
                    0x190, /* 250 ms */
                    NULL);

static const struct bt_le_adv_param *connectable_adv_param =
    BT_LE_ADV_PARAM(BT_LE_ADV_OPT_CONN,
                    BT_GAP_ADV_FAST_INT_MIN_2, /* 100 ms */
                    BT_GAP_ADV_FAST_INT_MAX_2, /* 150 ms */
                    NULL);

static const struct bt_data non_connectable_ad_data[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
    BT_DATA_BYTES(BT_DATA_URI, /* The URI of the https://www.nordicsemi.com website */
                  0x17, /* UTF-8 code point for “https:” */
                  '/', '/', 'w', 'w', 'w', '.',
                  'n', 'o', 'r', 'd', 'i', 'c', 's', 'e', 'm', 'i', '.',
                  'c', 'o', 'm'),
};

static const struct bt_data non_connectable_sd_data[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, NON_CONNECTABLE_DEVICE_NAME,
            sizeof(NON_CONNECTABLE_DEVICE_NAME) - 1),
};

static const struct bt_data connectable_data[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR),
    BT_DATA_BYTES(BT_DATA_UUID16_ALL, BT_UUID_16_ENCODE(BT_UUID_DIS_VAL)),
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, sizeof(CONFIG_BT_DEVICE_NAME) - 1),
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

//void start_advertising(void)
//{
//     int err;
//
//     err = bt_le_adv_start(BT_LE_ADV_CONN_FAST_1, ad, ARRAY_SIZE(ad),
//                                                  sd, ARRAY_SIZE(sd));
//     if (err) {
//         printk("Advertising failed to start (err %d)\n", err);
//     }
//     else {
//         printk("Advertising successfully started\n");
//     }
//}

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
//     start_advertising();    
     int err = connectable_adv_create();
     if (err) {
         return 0;
     }
     printk("Connectable advertising started\n");
}

/* Register a callback structure for connection events. */
BT_CONN_CB_DEFINE(conn_callbacks) = {
    .connected = connected,
    .disconnected = disconnected,
};

static const struct bt_le_ext_adv_cb adv_cb = {
	.connected = connected
};

static int advertising_set_create(struct bt_le_ext_adv **adv,
     const struct bt_le_adv_param *param,
     const struct bt_data *ad, size_t ad_len,
     const struct bt_data *sd, size_t sd_len)
{
    int err;
    struct bt_le_ext_adv *adv_set;

    err = bt_le_ext_adv_create(param, &adv_cb, adv);
      if (err) {
        printk("Error while creating new advertising (err=%i)\n", err);
        return err;
    }
    adv_set = *adv;
    printk("Created adv: %p\n", adv_set);

    err = bt_le_ext_adv_set_data(adv_set, ad, ad_len, sd, sd_len);
    if (err) {
        printk("Failed to set advertising data (err %d)\n", err);
        return err;
    }

    return bt_le_ext_adv_start(adv_set, BT_LE_EXT_ADV_START_DEFAULT);
}

static int non_connectable_adv_create(void)
{
    int err;

    err = advertising_set_create(&ext_adv[NON_CONNECTABLE_ADV_IDX], non_connectable_adv_param,
                                 non_connectable_ad_data, ARRAY_SIZE(non_connectable_ad_data),
                                 non_connectable_sd_data, ARRAY_SIZE(non_connectable_sd_data));
    if (err) {
        printk("Failed to create a non-connectable advertising set (err %d)\n", err);
    }

    return err;
}

static int connectable_adv_create(void)
{
    int err;

    err = advertising_set_create(&ext_adv[CONNECTABLE_ADV_IDX], connectable_adv_param,
                                 connectable_data, ARRAY_SIZE(connectable_data),
                                 NULL, 0);
      if (err) {
            printk("Failed to create a connectable advertising set (err %d)\n", err);
      }

      return err;
}

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

     err = non_connectable_adv_create();
     if (err) {
         return 0;
     }
     printk("Non-connectable advertising started\n");

     err = connectable_adv_create();
     if (err) {
         return 0;
     }
     printk("Connectable advertising started\n");

//     start_advertising();

     return 0;
}