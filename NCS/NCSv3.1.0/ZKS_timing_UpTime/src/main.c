/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>

int main(void)
{
	int64_t reftime;

	printf("Hello World! %s\n", CONFIG_BOARD);

	printk("CONFIG_SYS_CLOCK_TICKS_PER_SEC = %i\n",CONFIG_SYS_CLOCK_TICKS_PER_SEC);
	
	reftime=k_uptime_get();
	
	while(1){
		printk("Uptime (64-bit) = %llu ms\n",k_uptime_get());
		printk("Uptime (32-bit) = %i ms\n",k_uptime_get_32());
		printk("Uptime (64-bit) = %llu ticks\n",k_uptime_ticks());
		printk("Uptime (32-bit) = %i cycles\n",k_cycle_get_32());
		printk("Uptime (64-bit) = %llu cycles\n",k_cycle_get_64());
		printk("-----\n");
		printk("Delta Time = %llu ms\n-----\n",k_uptime_delta(&reftime));
		k_msleep(5000 -16);
		reftime=k_uptime_get();
	}

	return 0;
}
