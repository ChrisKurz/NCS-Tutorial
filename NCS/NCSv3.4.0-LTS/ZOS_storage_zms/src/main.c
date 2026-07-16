/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/kvss/zms.h>
#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>

#define ZMS_PARTITION FIXED_PARTITION_ID(storage_partition)

static struct zms_fs fs;


int main(void)
{
	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

    fs.flash_device = PARTITION_DEVICE(storage_partition);
    fs.offset = PARTITION_OFFSET(storage_partition);
    fs.sector_size = 4096;
    fs.sector_count = 4;

    int rc = zms_mount(&fs);
    if (rc < 0) {
        printk("Failed to mount ZMS: %d\n", rc);
        return 0;
    }
    printk("ZMS mounted successfully\n");

    /* Write Data */
    const char write_data[] = "Hello ZMS!";
    
    rc = zms_write(&fs,          /* file system */
                   1,            /* key ID */
                   write_data,   /* data pointer */
                   strlen(write_data) + 1);  /* data size */  
    if (rc < 0) {
        printk("Failed to write data: %d\n", rc);
        return 0;
    }
    printk("Data written successfully\n");

    /* Read Data */
    char read_buffer[64];
    memset(read_buffer, 0, sizeof(read_buffer));
    
    rc = zms_read(&fs, 
                  1, 
                  read_buffer, 
                  sizeof(read_buffer));
    if (rc < 0) {
        printk("Failed to read data: %d\n", rc);
        return 0;
    }
    printk("Read data: %s\n", read_buffer);	

	return 0;
}
