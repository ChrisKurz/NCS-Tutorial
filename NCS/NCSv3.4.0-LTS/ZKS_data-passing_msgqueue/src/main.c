/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>

struct sensor_msg {
    int id;
    int value;
};

K_MSGQ_DEFINE(sensor_msgq,                /* Queue name */
              sizeof(struct sensor_msg),  /* Size of each meassage */
              10,                         /* Maximum messages */
              4);                         /* Memory alignment */

K_THREAD_STACK_DEFINE(prod_stack, 1024);
K_THREAD_STACK_DEFINE(cons_stack, 1024);

struct k_thread prod_thread;
struct k_thread cons_thread;

void producer(void *a, void *b, void *c)
{
    struct sensor_msg msg;
    int counter = 0;

    while (1) {
        msg.id = 1;
        msg.value = counter++;

        k_msgq_put(&sensor_msgq,  /* Queue object */
                   &msg,          /* Pointer to message */
                   K_FOREVER);    /* How long to wait if full */

        k_sleep(K_SECONDS(1));
    }
}

void consumer(void *a, void *b, void *c)
{
    struct sensor_msg msg;

    while (1) {
        k_msgq_get(&sensor_msgq,  
                   &msg,
                   K_FOREVER);

        printk("ID=%d Value=%d\n",
               msg.id,
               msg.value);
    }
}

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

    k_thread_create(&prod_thread,
                    prod_stack,
                    K_THREAD_STACK_SIZEOF(prod_stack),
                    producer,
                    NULL, NULL, NULL,
                    5, 0, K_NO_WAIT);

    k_thread_create(&cons_thread,
                    cons_stack,
                    K_THREAD_STACK_SIZEOF(cons_stack),
                    consumer,
                    NULL, NULL, NULL,
                    5, 0, K_NO_WAIT);

	return 0;
}
