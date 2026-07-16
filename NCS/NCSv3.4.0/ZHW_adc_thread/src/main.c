#include <zephyr/kernel.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/devicetree.h>

static const struct adc_dt_spec adc_channel = ADC_DT_SPEC_GET(DT_PATH(zephyr_user));    

int main(void)
{
    int err;
    int val_mv;
    int16_t buf;
    struct adc_sequence sequence = {
        .buffer = &buf,
        /* buffer size in bytes, not number of samples */
        .buffer_size = sizeof(buf),
    };

    printk("Hello World!\n");

    if (!adc_is_ready_dt(&adc_channel)) {
        printk("ADC controller device %s not ready\n", adc_channel.dev->name);
        return 0;
    }

    err = adc_channel_setup_dt(&adc_channel);
    if (err < 0) {
        printk("Could not setup channel #%d (%d)\n", 0, err);
        return 0;
    }

    err = adc_sequence_init_dt(&adc_channel, &sequence);
    if (err < 0) {
        printk("Could not initalize sequnce\n");
        return 0;
    }

    while(1){
        err = adc_read(adc_channel.dev, &sequence);
        if (err < 0) {
            printk("Could not read (%d)\n", err);
            continue;
        }
        val_mv = (int)buf;

        printk("ADC result: %s, channel %d: Raw: %i ", adc_channel.dev->name, adc_channel.channel_id, val_mv);

        err = adc_raw_to_millivolts_dt(&adc_channel, &val_mv);
        /* conversion to mV may not be supported, skip if not */
        if (err < 0) {
            printk(" (value in mV not available)\n");
        } else {
            printk(" = %d mV\n", val_mv);
        }

        k_sleep(K_MSEC(1000));
    }
    return 0;
}