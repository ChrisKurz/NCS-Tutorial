/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>

struct k_timer MyTimer;

static void TimerExpire(struct k_timer *timer) {
    static uint16_t count;

    count++;
    printk("timer expired [%d]: %u\n",count, timer->status);
       
    if (count == 10)
        k_timer_stop(timer);
}

static void TimerStopped(struct k_timer *timer) {
    printk("Timer was stopped!\n");       
}

void main(void)
{
	printk("Hello World! %s\n", CONFIG_BOARD);

    k_timer_init(&MyTimer, TimerExpire, TimerStopped);
    k_timer_start(&MyTimer, K_MSEC(5000), K_MSEC(1000)); // wait 5 seconds, period 1 second
}
