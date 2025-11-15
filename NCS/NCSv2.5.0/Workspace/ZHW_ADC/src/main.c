#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>

#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
    !DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif


#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
	ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

/* Data of ADC io-channels specified in devicetree. */
static const struct adc_dt_spec adc_channels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
			     DT_SPEC_AND_COMMA)
};

int main(void)
{
    printk("Hello World!\n");
    printk("\n");
    printk("ADC Configuration:\n");
    printk("-----------------------------\n");
    printk("Channel 0:\n");
    printk("channel-id:  %c \n",adc_channels[0].channel_id);
    printk("channel config exists: %c \n",adc_channels[0].channel_cfg_dt_node_exists);
    printk("Voltage of reference: %i \n",adc_channels[0].vref_mv);

    printk("-----------------------------\n");

    printk("Channel 1:\n");
    printk("channel-id:  %c \n",adc_channels[1].channel_id);
    printk("channel config exists: %c \n",adc_channels[1].channel_cfg_dt_node_exists);
    printk("Voltage of reference: %i \n",adc_channels[1].vref_mv);

    printk("-----------------------------\n");



    return 0;     
}
