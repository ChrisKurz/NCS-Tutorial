/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include "app_version.h"
#include <zephyr/kernel.h>

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
	printf("Image: MCUboot2 \n");	
    printf("Application version: %s\n", APP_VERSION_TWEAK_STRING);

	return 0;
}
