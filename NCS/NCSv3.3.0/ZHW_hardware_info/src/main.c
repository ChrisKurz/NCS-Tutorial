/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/drivers/hwinfo.h>

#define BUFFER_LENGTH  8

int main(void)
{
	uint8_t buffer[BUFFER_LENGTH];
	ssize_t ret;
	int i;

	printf("Hello World! %s\n", CONFIG_BOARD_TARGET);

	for (i=0; i<=BUFFER_LENGTH-1; i++){
		buffer[i] = 0;
	}


	/*--- Get Device ID ---*/
	printf("\n> Get Device ID\n");

	ret = hwinfo_get_device_id(buffer, BUFFER_LENGTH);
	if (ret == -ENOTSUP){
		printf("hwinfo_get_device_id() not supported for this device! (err=%d)\n", ret);
		return 0;
	}
	else {
		if (ret < 0){
			printf("hwinfo_get_device_id() call caused an error! (err=%d)\n", ret);
			return 0;
		}
	}

	printf("Device ID length = %i \n", ret);

	printf("Device ID: ");
	for (i=0; i<=BUFFER_LENGTH-1; i++){
		printf("0x%02x ", buffer[i]);
	}	
	printf ("\n");


	/*--- Get device EUI64 ---*/
	printf("\n> Get Device EUI64\n");

	ret = hwinfo_get_device_eui64(buffer);
	if (ret == -ENOSYS){
		printf("hwinfo_get_device_eui64() not supported for this device! (err=%d)\n", ret);
	}
	else {
		if (ret < 0){
			printf("hwinfo_get_device_eui64() call caused an error! (err=%d)\n", ret);
		}
	}


	/*--- Get supported Reset Cause Flags ---*/
	printf("\n> Get supported Reset Cause Flags\n");

	uint32_t supportedFlags;

	ret = hwinfo_get_supported_reset_cause(&supportedFlags);
	if (ret == -ENOSYS){
		printf("hwinfo_get_supported_reset_cause() not supported for this device! (err=%d)\n", ret);
		return 0;
	}
	else {
		if (ret < 0){
			printf("hwinfo_get_supported_reset_cause() call caused an error! (err=%d)\n", ret);
			return 0;
		}
	}
	printf("Supported Reset Cause Flags:  0x%08x\n", supportedFlags);


	/*--- Check Reset Cause ---*/
	printf("\n> Get Reset Cause\n");

	uint32_t resetCause;

	ret = hwinfo_get_reset_cause(&resetCause);
	if (ret == -ENOSYS){
		printf("hwinfo_get_reset_cause() not supported for this device! (err=%d)\n", ret);
		return 0;
	}
	else {
		if (ret < 0){
			printf("hwinfo_get_reset_cause() call caused an error! (err=%d)\n", ret);
			return 0;
		}
	}
	printf("Reset cause: 0x%08x\n", resetCause);


	/*--- Clear Reset Cause Flag register*/
	printf("\n> Let's clear the Reset Cause Flag register\n");

	ret = hwinfo_clear_reset_cause();
	if (ret == -ENOSYS){
		printf("hwinfo_clear_reset_cause() not supported for this device! (err=%d)\n", ret);
		return 0;
	}
	else {
		if (ret < 0){
			printf("hwinfo_clear_reset_cause() call caused an error! (err=%d)\n", ret);
			return 0;
		}
	}
	printf("Reset Cause Flags register successfully cleared!\n");

	printf("\n> Get Reset Cause\n");

	

	ret = hwinfo_get_reset_cause(&resetCause);
	if (ret == -ENOSYS){
		printf("hwinfo_get_reset_cause() not supported for this device! (err=%d)\n", ret);
		return 0;
	}
	else {
		if (ret < 0){
			printf("hwinfo_get_reset_cause() call caused an error! (err=%d)\n", ret);
			return 0;
		}
	}
	printf("Reset cause: 0x%08x\n", resetCause);


	return 0;
}
