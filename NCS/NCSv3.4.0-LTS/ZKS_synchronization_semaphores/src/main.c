/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>

K_SEM_DEFINE(my_sem,  /* Name of the semaphore */
             0,       /* Semaphore starts unavailable */
             1);      /* Maximum semaphore count */

			 #define STACKSIZE 1024
#define PRIORITY 5

void producer_thread(void);
void consumer_thread(void);

K_THREAD_DEFINE(producer_id, STACKSIZE,
                producer_thread, NULL, NULL, NULL,
                PRIORITY, 0, 0);

K_THREAD_DEFINE(consumer_id, STACKSIZE,
                consumer_thread, NULL, NULL, NULL,
                PRIORITY, 0, 0);
			
void producer_thread(void)
{
    while (1) {
        printk("Producer: doing work...\n");
        k_sleep(K_SECONDS(2));
        printk("Producer: giving semaphore\n");
        k_sem_give(&my_sem);
    }
}				

void consumer_thread(void)
{
    while (1) {
       printk("Consumer: waiting for semaphore...\n");
       k_sem_take(&my_sem, K_FOREVER);
       printk("Consumer: semaphore received\n");
    }
}

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

	return 0;
}
