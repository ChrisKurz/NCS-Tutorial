/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>


/* select one of the following possibilities to get the node identifier: */
#define NODE_ID  DT_PATH(leds, led_0)
// #define NODE_ID  DT_NODELABEL(led1)
// #define NODE_ID  DT_ALIAS(led_blink)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(NODE_ID, gpios);

int main(void)
{
	printk("Hello World! %s\n", CONFIG_BOARD_TARGET);

	char string[20] = DT_PROP(NODE_ID, label);
	printk("property label = %s\n", string);

	printk("GPIO port: %s\n", led.port->name);
	printk("GPIO pin: %i\n", led.pin);
	printk("GPIO flags: %i\n", led.dt_flags);

	return 0;
}
