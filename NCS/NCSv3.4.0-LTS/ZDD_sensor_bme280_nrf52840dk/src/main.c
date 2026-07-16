/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD);

    const struct device *dev = DEVICE_DT_GET_ANY(bosch_bme280);
    if (dev==NULL){
        /* No such node, or the node does not have status "okay". */
        printk("\nError: Device \"%s\" is not ready.\n", dev->name);
        return 0;
    }

    while(1){
        struct sensor_value temp, press, humidity;
     
        sensor_sample_fetch(dev);
        sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
        sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);
        sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);
         
        printk("temp: %d.%06d; press: %d.%06d; humidity: %d.%06d\n",
                temp.val1, temp.val2, press.val1, press.val2,
                humidity.val1, humidity.val2);

        k_sleep(K_MSEC(1000));                
    }	
	return 0;
}
