/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>

/* Get the Start Address of hello_world app from DeviceTree */
#define TARGET_NODE DT_CHOSEN(myapp_target_partition)
#define TARGET_ADDRESS DT_REG_ADDR(TARGET_NODE)

typedef void (*entry_t)(void);

static void start_application(uint32_t addr)
{
    uint32_t *vector_table = (uint32_t *)addr;

    uint32_t stack_pointer = vector_table[0];
    uint32_t reset_handler = vector_table[1];

    printf("Jumping to 0x%08x\n", reset_handler);

    __disable_irq();
    __set_MSP(stack_pointer);
    SCB->VTOR = addr;
    entry_t entry = (entry_t)reset_handler;
    entry();
}

int main(void)
{
	printf("Launcher started! %s\n", CONFIG_BOARD_TARGET);
	start_application(TARGET_ADDRESS);

	return 0;
}
