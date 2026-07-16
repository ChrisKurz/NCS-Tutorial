#include <zephyr/kernel.h>
#include <nrfx_saadc.h>

static nrfx_saadc_channel_t channel = NRFX_SAADC_DEFAULT_CHANNEL_SE(NRF_SAADC_INPUT_AIN1, 0);

int main(void)
{
    static nrf_saadc_value_t sample;

    printk("Hello World!\n");

    IRQ_CONNECT(DT_IRQN(DT_NODELABEL(adc)),
               DT_IRQ(DT_NODELABEL(adc), priority),
               nrfx_isr, nrfx_saadc_irq_handler, 0);

    nrfx_err_t err = nrfx_saadc_init(DT_IRQ(DT_NODELABEL(adc), priority));
    if (err != NRFX_SUCCESS) {
        printk("nrfx_saadc_init() error: %08x\n", err);
        return 0;
    }

    channel.channel_config.gain = NRF_SAADC_GAIN1_6;
    err = nrfx_saadc_channels_config(&channel, 1);
    if (err != NRFX_SUCCESS) {
        printk("nrfx_saadc_channels_config() error: %08x\n", err);
        return 0;
    }    

    err = nrfx_saadc_simple_mode_set(BIT(0),
                                     NRF_SAADC_RESOLUTION_12BIT,
                                     NRF_SAADC_OVERSAMPLE_DISABLED,
                                     NULL);
    if (err != NRFX_SUCCESS) {
        printk("nrfx_saadc_simple_mode_set8() error: %08x\n", err);
        return 0;
    }

    err = nrfx_saadc_buffer_set(&sample, 1);
    if (err != NRFX_SUCCESS) {
        printk("nrfx_saadc_buffer_set() error: %08x\n", err);
        return 0;
    }

    while(1){
        nrfx_err_t err = nrfx_saadc_mode_trigger();
        if (err != NRFX_SUCCESS) {
            printk("nrfx_saadc_mode_trigger error: %08x", err);
            return 0;
        }
        int battery_voltage = ((600*6) * sample) / ((1<<12));
        printk("SAADC sample: %d", sample);
        printk("  => Battery Voltage: %d mV\n", battery_voltage);
        k_sleep(K_MSEC(2000));
    }

    return 0;
}