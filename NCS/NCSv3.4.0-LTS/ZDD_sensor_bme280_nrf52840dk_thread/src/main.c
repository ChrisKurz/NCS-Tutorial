/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>

#define MYTHREAD_STACK_SIZE 500
#define MYTHREAD_PRIORITY 5

void Thread_BME280(void *arg1, void *arg2, void *arg3)
{
    struct sensor_value temp, press, humidity;
    const struct device *dev = DEVICE_DT_GET_ANY(bosch_bme280);
    if (dev==NULL){
        /* No such node, or the node does not have status "okay". */
        printk("\nError: Device \"%s\" is not ready.\n", dev->name);
        /* You can also use Zephyr Logging instead of printk() instruction, if Logging is enabled in your project. */
        // LOG_ERR("Error: Device \"%s\" is not ready.", dev->name);
        return;
    }

    /* Initialization done. Now sensor handling can be done in following entire loop. */
    while (1){
        sensor_sample_fetch(dev);
        sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
        sensor_channel_get(dev, SENSOR_CHAN_PRESS, &press);
        sensor_channel_get(dev, SENSOR_CHAN_HUMIDITY, &humidity);
        printk("temp: %d.%06d; press: %d.%06d; humidity: %d.%06d\n",
                temp.val1, temp.val2, press.val1, press.val2,
                humidity.val1, humidity.val2);
        k_sleep(K_MSEC(1000)); 						
    }
	    
}

K_THREAD_DEFINE(
           my_tid,              /* Name of the thread                          */
           MYTHREAD_STACK_SIZE, /* Stack size in bytes                       */
           Thread_BME280,       /* Thread entry function                       */
           NULL, NULL, NULL,    /* Passing parameters for entry point function */
           MYTHREAD_PRIORITY,   /* Thread priority                             */
           0,                   /* Thread options                              */
           0);                  /* Scheduling delay (0 for no delay)           */

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD);
	return 0;
}
