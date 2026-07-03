/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <stdio.h>

#define MYTHREAD1_STACK_SIZE 500
#define MYTHREAD1_PRIORITY 5

#define MYTHREAD2_STACK_SIZE 500
#define MYTHREAD2_PRIORITY 5

K_THREAD_STACK_DEFINE(mythread1_stack_area, MYTHREAD1_STACK_SIZE);

struct k_thread myThread1_data;


void myThread1(void *arg1, void *arg2, void *arg3) {
 
    while(1) {
        k_msleep(1000);
        printk("executing myThread1\n");
    }
}

void myThread2(void *arg1, void *arg2, void *arg3) {
 
    while(1) {
        k_msleep(700);
        printk("executing myThread2\n");
    }
}

K_THREAD_DEFINE(
           my_tid2,            /* Name of the thread                          */
           MYTHREAD2_STACK_SIZE, /* Stack size in bytes                       */
           myThread2,          /* Thread entry function                       */
           NULL, NULL, NULL,   /* Passing parameters for entry point function */
           MYTHREAD2_PRIORITY, /* Thread priority                             */
           0,                  /* Thread options                              */
           0);                 /* Scheduling delay (0 for no delay)           */


int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD);

    k_tid_t my_tid1 = k_thread_create(
           &myThread1_data,    /* Thread Control Block                        */
           mythread1_stack_area, /* Stack Area                                */
           K_THREAD_STACK_SIZEOF(mythread1_stack_area),
           myThread1,          /* Thread Entry Function                       */
           NULL, NULL, NULL,   /* Passing parameters for entry point function */
           MYTHREAD1_PRIORITY, /* Thread priority                             */
           0,                  /* Thread options                              */
           K_NO_WAIT);         /* Scheduling delay (K_NO_WAIT for no delay)   */

	return 0;
}
