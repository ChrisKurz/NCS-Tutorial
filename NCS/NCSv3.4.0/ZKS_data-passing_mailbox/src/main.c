/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>

K_MBOX_DEFINE(my_mailbox);

#define STACKSIZE 1024
#define PRIORITY 5

void sender_thread(void *a, void *b, void *c)
{
    char message[] = "Hello from sender";
    struct k_mbox_msg tx_msg;

    while (1) {
        tx_msg.info = 1234;
        tx_msg.size = strlen(message) + 1;
        tx_msg.tx_data = message;
        tx_msg.tx_target_thread = K_ANY;

        printk("Sending message...\n");

        k_mbox_put(&my_mailbox, &tx_msg, K_FOREVER);

        k_sleep(K_SECONDS(2));
    }
}

void receiver_thread(void *a, void *b, void *c)
{
    struct k_mbox_msg rx_msg;
    char buffer[100];

    while (1) {
        rx_msg.size = sizeof(buffer);
        rx_msg.rx_source_thread = K_ANY;

        k_mbox_get(&my_mailbox,
                   &rx_msg,
                   buffer,
                   K_FOREVER);

        printk("Received: %s\n", buffer);
        printk("Info field: %d\n", rx_msg.info);
    }
}

K_THREAD_STACK_DEFINE(sender_stack, STACKSIZE);
K_THREAD_STACK_DEFINE(receiver_stack, STACKSIZE);

struct k_thread sender_thread_data;
struct k_thread receiver_thread_data;

int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

    k_thread_create(&sender_thread_data,
                    sender_stack,
                    STACKSIZE,
                    sender_thread,
                    NULL, NULL, NULL,
                    PRIORITY,
                    0,
                    K_NO_WAIT);

    k_thread_create(&receiver_thread_data,
                    receiver_stack,
                    STACKSIZE,
                    receiver_thread,
                    NULL, NULL, NULL,
                    PRIORITY,
                    0,
                    K_NO_WAIT);
						
	return 0;
}
