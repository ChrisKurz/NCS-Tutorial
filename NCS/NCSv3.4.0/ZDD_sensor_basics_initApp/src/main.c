/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>

#define SENSOR_NODE DT_NODELABEL(bme280)

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

	const struct device *sensor = DEVICE_DT_GET(SENSOR_NODE);
    if (sensor == NULL)
    {
        /* No such node, or the node does not have status "okay" */
        printk("Error: No device \"%s\" found in DeviceTree.\n", sensor->name);
        return -1;
    }
    printk("Device \"%s\" is ready\n",sensor->name);

    if (!device_is_ready(sensor))
    {
        printk("Sensor device not ready!\n");
    } else {
        printk("Sensor device is ready\n");
    }

    /* The BME280 Sensor Driver is started here */
    device_init(sensor);

    if (!device_is_ready(sensor))
    {
        printk("Sensor device not ready!\n");
    } else {
        printk("Sensor device is ready\n");
    }

    return 0;
}
