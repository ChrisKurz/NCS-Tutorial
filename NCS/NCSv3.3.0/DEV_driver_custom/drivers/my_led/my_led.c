#include "my_led.h"

#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/devicetree.h>

#define LED_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

static struct k_timer blink_timer;

static bool blinking = false;
static bool led_state = false;

static void blink_timer_handler(struct k_timer *timer)
{
    ARG_UNUSED(timer);

    led_state = !led_state;
    gpio_pin_set_dt(&led, led_state);
}

int my_led_init(void)
{
    if (!gpio_is_ready_dt(&led)) {
        return -ENODEV;
    }

    int ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        return ret;
    }
    k_timer_init(&blink_timer, blink_timer_handler, NULL);

    return 0;
}

int my_led_on(void)
{
    blinking = false;
    k_timer_stop(&blink_timer);
    led_state = true;
    return gpio_pin_set_dt(&led, 1);
}  

int my_led_off(void)
{
    blinking = false;
    k_timer_stop(&blink_timer);
    led_state = false;
    return gpio_pin_set_dt(&led, 0);
}

void my_led_blink_start(uint32_t interval_ms)
{
    blinking = true;

    k_timer_start(
        &blink_timer,
        K_MSEC(interval_ms),
        K_MSEC(interval_ms));
}

void my_led_blink_stop(void)
{
    blinking = false;
    k_timer_stop(&blink_timer);
   gpio_pin_set_dt(&led, 0);
   led_state = false;
}