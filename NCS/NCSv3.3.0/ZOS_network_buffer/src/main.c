/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/net_buf.h>

/*
 * Create a pool with:
 * - 4 buffers
 * - each buffer can hold 128 bytes
 */
NET_BUF_POOL_DEFINE(my_buf_pool,  /* Pool name */
                    4,            /* Number of buffers */
                    128,          /* Payload size per buffer */
                    4,            /* Optional user metadata */
                    NULL);        /* Cleanup callback */

int main(void)
{
     
    


	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

	/* Allocate a buffer from the pool */
	struct net_buf *buf;  

    buf = net_buf_alloc(&my_buf_pool, K_NO_WAIT);
    if (!buf) {
        printk("Buffer allocation failed\n");
        return 0;
    }
    printk("Buffer allocated\n");

	/* Add Data to Network Buffer */
	const char *message = "Hello from net_buf";

    net_buf_add_mem(buf, message, strlen(message));
    printk("Buffer length: %d\n", buf->len);
    printk("Stored message: %s\n", buf->data);
	
    /* Read data from the buffer */
    char rx_data[64];

    memcpy(rx_data, buf->data, buf->len);
    printk("Received data: %s\n", rx_data);

    /*
     * Release the buffer back to the pool
     */
    net_buf_unref(buf);
    printk("Buffer released\n");
	
	return 0;
}
