#ifndef MY_LED_H
#define MY_LED_H

#include <zephyr/kernel.h>

int my_led_init(void);
int my_led_on(void);
int my_led_off(void);
void my_led_blink_start(uint32_t interval_ms);
void my_led_blink_stop(void);

#endif