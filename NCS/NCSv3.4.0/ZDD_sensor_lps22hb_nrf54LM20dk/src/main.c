/*
 * Copyright (c) 2025 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>


static void process_sample(const struct device *dev)
{
	struct sensor_value pressure, temp;

	// Fetch a sample from the sensor and store it in an internal driver buffer
	if (sensor_sample_fetch(dev) < 0) {
		printk("Error: Sensor sample update error\n");
		return;
	}

	// Get a reading from a sensor device (read pressure)
	if (sensor_channel_get(dev, SENSOR_CHAN_PRESS, &pressure) < 0) {
		printk("Error: Cannot read LPS22HB pressure channel\n");
		return;
	}

	// Get a reading from a sensor device (read temperature)	
	if (sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp) < 0) {
		printk("Error: Cannot read LPS22HB temperature channel\n");
		return;
	}

	/* display pressure */
	printk("pressure: %d.%d kPa, ", pressure.val1, pressure.val2);
	//printk("Pressure: %.1f kPa, ", sensor_value_to_double(&pressure));

	/* display temperature */
	printk("Temperature: %.1f C\n", sensor_value_to_double(&temp));
}


int main(void)
{
	printk("LPS22HB Demo\n");

	#define SENSOR_NODE DT_NODELABEL(lps22hb)
	const struct device *const dev = DEVICE_DT_GET(SENSOR_NODE);
	if (!device_is_ready(dev)) {
		printk("Sensor is not ready %s\n", dev->name);
		return 0;
	}
	printk("Sensor is ready!\n");

	while (true) {
		process_sample(dev);
		k_sleep(K_MSEC(2000));
	}
	return 0;
}
