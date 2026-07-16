#include <zephyr/kernel.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/devicetree.h>

static const struct device *const my_uart = DEVICE_DT_GET(DT_NODELABEL(uart1)); 

#define DATA_LEN   (sizeof(fifo_data) - 1)
static const char fifo_data[] = "This is a test.\r\n";
static int char_sent;    

static void uart_callback(const struct device *dev, void *user_data){
     uint8_t recvData;
     static int tx_data_idx;
     int ret;


     if (uart_irq_tx_ready(dev) && tx_data_idx < DATA_LEN) {
          ret = uart_fifo_fill(dev, (uint8_t *)&fifo_data[tx_data_idx], DATA_LEN-char_sent);
          if (ret > 0) {
               char_sent += ret;
               tx_data_idx += ret;
          } else {
               uart_irq_tx_disable(dev);
               return;
          }

          if (tx_data_idx == DATA_LEN) {
               /* If we transmitted everything, disable the interrupt.
                * otherwise main app might never run.
                */
               uart_irq_tx_disable(dev);
          }
     }

     if (uart_irq_rx_ready(dev)) {
          uart_fifo_read(dev, &recvData, 1);
          printk("%c", recvData); 
     }
}

int main(void)
{
     printk("Hello World!\n");

     if (!device_is_ready(my_uart)) {
          printk("UART device not ready\n");
          return 0;
     }

     uart_irq_callback_set(my_uart, uart_callback);

     uart_irq_rx_enable(my_uart);

     while(1){
          /* Enable Tx/Rx interrupt before using fifo */
          uart_irq_tx_enable(my_uart);

          k_msleep(1000);
     }

     return 0;
}