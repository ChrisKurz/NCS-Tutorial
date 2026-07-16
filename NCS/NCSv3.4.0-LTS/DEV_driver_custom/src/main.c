#include <zephyr/kernel.h>
#include "my_led.h"

int main(void)
{
    int ret;

    ret = my_led_init();
    if (ret < 0) {
        return 0;
    }

    while (1) {

        ret = my_led_on();
        k_sleep(K_SECONDS(2));

        ret = my_led_off();
        k_sleep(K_SECONDS(2));

        my_led_blink_start(500);
        k_sleep(K_SECONDS(5));

        my_led_blink_stop();
        k_sleep(K_SECONDS(2));
    }

    return 0;
}