/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include "AppVersion.h"

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);
	
	printf("Project Version: %s \n",MyApp_VERSION);
	printf("Project Version, major: %i \n",MyApp_VERSION_MAJOR);
	printf("Project Version, minor: %i \n",MyApp_VERSION_MINOR);
	printf("Project Version, patch: %i \n",MyApp_VERSION_PATCH);
	printf("Project Version, tweak: %i \n",MyApp_VERSION_TWEAK);

	return 0;
}
