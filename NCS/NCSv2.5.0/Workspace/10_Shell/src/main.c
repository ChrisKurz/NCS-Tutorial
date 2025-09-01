/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#include <zephyr/shell/shell.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);


static int cmd_led_on(const struct shell *shell, size_t argc, char **argv)
{
   ARG_UNUSED(argc);   
   ARG_UNUSED(argv);

   printk("switch on LED0\n");
   gpio_pin_set_dt(&led,1);
   return 0;
}


static int cmd_led_off(const struct shell *shell, size_t argc, char **argv)
{
    ARG_UNUSED(argc);   
    ARG_UNUSED(argv);

    printk("switch off LED0\n");
    gpio_pin_set_dt(&led,0);
    return 0;
}

/* Creating subcommands (level 1 command) array for command "led". */
SHELL_STATIC_SUBCMD_SET_CREATE(sub_led,
        SHELL_CMD(on, NULL, "Switch on LED0", cmd_led_on),
        SHELL_CMD(off, NULL, "Switch off LED0", cmd_led_off),
        SHELL_SUBCMD_SET_END
);
/* Creating root (level 0) command "led" */
SHELL_CMD_REGISTER(led, &sub_led, "LED commands", NULL);

int main(void)
{
	int ret;

        if (!gpio_is_ready_dt(&led)) {
                return 0;
        }

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	while (1) {
//		ret = gpio_pin_toggle_dt(&led);
//		if (ret < 0) {
//			return 0;
//		}
		k_msleep(SLEEP_TIME_MS);
	}

        return 0;
}
