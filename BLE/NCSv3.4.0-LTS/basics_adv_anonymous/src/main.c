#include <zephyr/kernel.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>

static struct bt_le_ext_adv *adv;

/* Example manufacturer payload */
static const uint8_t mfg_data[] = {
    0x34, 0x12,             /* Company ID: 0x1234 */
    0xDE, 0xAD, 0xBE, 0xEF  /* Data: 0x DE AD BE EF */
};

static const struct bt_data ad[] = {
    BT_DATA(BT_DATA_MANUFACTURER_DATA,
            mfg_data,
            sizeof(mfg_data)),
};


int main (void) {
    int err;

    printk("Starting MyBeacon application!\n");

    /* Initialize the Bluetooth Subsystem */
    err = bt_enable(NULL);
    if (err) {
        printk("Bluetooth init failed (err %d)\n", err);
        return 0;
    }

    printk("Bluetooth initialized\n");

    struct bt_le_adv_param param = {
        .id = BT_ID_DEFAULT,

        /* IMPORTANT:
         * EXT_ADV is required for ANONYMOUS
         */
        .options =
            BT_LE_ADV_OPT_EXT_ADV |   /* use Exxtended Advertising */
            BT_LE_ADV_OPT_ANONYMOUS,  /* make it anonymous */

        /* 100 ms */
        .interval_min = BT_GAP_ADV_FAST_INT_MIN_2,
        .interval_max = BT_GAP_ADV_FAST_INT_MAX_2,
    };

    err = bt_le_ext_adv_create(&param, NULL, &adv);
    if (err) {
        printk("Failed to create advertiser (err %d)\n", err);
        return 0;
    }

    err = bt_le_ext_adv_set_data(
        adv,
        ad,
        ARRAY_SIZE(ad),
        NULL,
        0
    );
    if (err) {
        printk("Failed to set advertising data (err %d)\n", err);
        return 0;
    }

    err = bt_le_ext_adv_start(
        adv,
        BT_LE_EXT_ADV_START_DEFAULT
    );
    if (err) {
        printk("Failed to start advertising (err %d)\n", err);
        return 0;
    }
    printk("Anonymous advertising started\n");


    return 0;
}
