/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>

/* Getting the Start Address */
#define APP_PARTITION_NODE DT_CHOSEN(zephyr_code_partition)
#define APP_START_ADDRESS DT_REG_ADDR(APP_PARTITION_NODE)

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
	printf("Running at flash address 0x%08x\n", (uint32_t)APP_START_ADDRESS);

	return 0;
}
