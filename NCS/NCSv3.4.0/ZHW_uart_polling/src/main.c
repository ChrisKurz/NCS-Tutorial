#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/devicetree.h>

const struct device *const my_uart = DEVICE_DT_GET(DT_NODELABEL(uart1));    

struct k_timer MyTimer;

static void TimerExpire(struct k_timer *timer) {
    printk("transmit data byte \n");
    uart_poll_out(my_uart, (unsigned char) '1');
}

static void TimerStopped(struct k_timer *timer) {
    printk("Timer was stopped!\n");       
}

int main(void)
{
    unsigned char data;

    printk("Hello World!\n");

	if (!device_is_ready(my_uart)) {
		printk("UART device not ready\n");
		return 0;
	}

    k_timer_init(&MyTimer, TimerExpire, TimerStopped);
    k_timer_start(&MyTimer, K_MSEC(0), K_MSEC(1000)); // period 1 second

    while(1){
        while(uart_poll_in(my_uart, &data) <0){
            /* Allow other thread/workqueue to work. */
            k_yield();            
        }
        printk("received byte: %c \n", data); 
    }
    return 0;
}
