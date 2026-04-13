/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>

#if IS_ENABLED(CONFIG_MYFUNC)
void my_func(void){
	printf("My function is included in the build\n");
	printf("its name is: %s\n", CONFIG_MYFUNC_NAME);
}
#endif

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

#if IS_ENABLED(CONFIG_MYFUNC)	
	my_func();
#endif

	return 0;
}
