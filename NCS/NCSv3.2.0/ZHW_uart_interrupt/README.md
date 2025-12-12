<sup>SDK version: NCS v3.2.0 </sup>

# Zephyr Hardware Driver: UART - interrupt driven

## Introduction

There are different UART drivers in Zephyr. All have different API functions. The different drivers support:
- _communication using polling_: this one is the most basic method of using the UART peripheral. There is a read function (_uart_poll_in()_) that is a non-blocking function and it returns a character or -1 when no valid data is available. The write function (_uart_poll_out()_) is a blocking function and the user application waits until the character is sent. 
- _interrupt-driven communication_: the UART driver handles data via an interrupt service routine while the user application can continue other tasks. 
- _asynchronous communication_: this is the most efficient way. it allows to read and write data in the background by using EasyDMA. 

In this hands-on we take a look into the interrupt-driven solution. 

## Required Hardware/Software
- Development kit 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk), 
(nRF54L15DK)
  > __Note__: Two development kits allow to check communication between boards. It is also possible to test the software with one development kit; in this case the board receives the data byte it has sent.
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Create a new Project

1) Create a new project based on [Creating a Project from Scratch_ exercise](../DEV_ProjectFromScratch/README.md). 


### Add needed Software Module _UART_

2) We have to add the Zephyr UART hardware driver to our project. Note that this driver is usually by default enabled. In the board definition you find for example in the __nrf52840dk_nrf52840_defconfig__ file the following lines:

	<sup>_prj.conf_</sup>
 
       # enable uart driver
       CONFIG_SERIAL=y
       CONFIG_UART_INTERRUPT_DRIVEN=y

    > __NOTE:__ The UART driver (CONFIG_SERIAL=y) is by default selected when working with an nRF52 development kit. For completness it was added here. It can also be copied into your __prj.conf__ file. 

4) In order to use the UART hardware driver API we also need to add the corresponding header file to our _main.c_ file:

	<sup>_src/main.c_</sup>

       #include <zephyr/drivers/uart.h>

### Adding DeviceTree overlay file for UART

4) Create an overlay file. (e.g. __nrf52840DK_nrf52840.overlay__)

5) UART0 is already usind on the development kit for the logging. It's usage is already defined in the board definition files. Beside that we will use UART1 in our example for our own UART communication. Add following lines in the device tree overlay file of your project. 

	<sup>_nrf52840DK_nrf52840.overlay_</sup>

        &pinctrl {
                 uart1_default: uart1_default {
                      group1 {
                             psels = <NRF_PSEL(UART_RX, 1, 1)>;
                             bias-pull-up;
                      };
                      group2 {
                             psels = <NRF_PSEL(UART_TX, 1, 2)>;
                      };
                 };

                 uart1_sleep: uart1_sleep {
                      group1 {
                             psels = <NRF_PSEL(UART_RX, 1, 1)>,
                                     <NRF_PSEL(UART_TX, 1, 2)>;
                             low-power-enable;
                      };
                 };
       };

       &uart1 {
               compatible = "nordic,nrf-uart";
               status = "okay";
               current-speed = <115200>;
               pinctrl-0 = <&uart1_default>;
               pinctrl-1 = <&uart1_sleep>;
               pinctrl-names = "default", "sleep";
       };


### Including DeviceTree Configuration in C source code

6) First, include the devicetree header file into your project.

	<sup>_src/main.c_</sup>

       #include <zephyr/devicetree.h>

7) We need a variable of type __device__ for the UART instance. 

	<sup>_src/main.c_</sup>

       static const struct device *const my_uart = DEVICE_DT_GET(DT_NODELABEL(uart1)); 

8) Before we use the UART we should check if the UART peripheral driver is ready. 

	<sup>_src/main.c_ => main() function</sup>

            if (!device_is_ready(my_uart)) {
                 printk("UART device not ready\n");
                 return 0;
            }


### Let's add software parts for the interrupt-driven communication

9) The Zephyr RTOS is handling interrupts. Because of this, we have to define a callback function, which is executed as soon as the UART interrupt happens. Let's start and add first this callback function.

	<sup>_src/main.c_</sup>

       static void uart_callback(const struct device *dev, void *user_data){

       }

   > __Note__: Since we have to pass the _uart_callback_ function to the UART driver, this callback function should be copied before the _main()_ function. In _main()_ we will pass the _uart_callback_ to UART driver.

10) As just mentioned, now we add the pass the callback function entry point to the UART driver.

	<sup>_src/main.c_ => main() function</sup>

             uart_irq_callback_set(my_uart, uart_callback);

### Transmit data

11) The ineterrupt-driven UART driver provides the API function _uart_fifo_fill()_ that has to be called from an interrupt service routine. Because of this we enable the UART TX interrupt and put the data that should be sent in the ISR into the FIFO. So, first we enable the interrupt.

	<sup>_src/main.c_ => main() function</sup>

             while(1){
                  /* Enable Tx/Rx interrupt before using fifo */
                  uart_irq_tx_enable(my_uart);
    
                  k_msleep(1000);
             }

12) Let's define a string that should be sent. We use _char_sent_ as a pointer in the ISR, which points into the FIFO array and defines the next byte to sent. These are global definitions.

	<sup>_src/main.c_</sup>

        #define DATA_LEN   (sizeof(fifo_data) - 1)
	    static const char fifo_data[] = "This is a test.\r\n";
        static int char_sent;    

13) And the the software part that handles TX in the _uart_callback()_ callback function.

	<sup>_src/main.c_ => uart_callback() function</sup>

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

### Receive data

14) We enable the UART RX interrupt before the _while(1)_ loop in main function

	<sup>_src/main.c_ => main() function</sup>

             uart_irq_rx_enable(my_uart);

15) And add code in the uart_callback function that handles receiving of the individual bytes.

	<sup>_src/main.c_ => uart_callback() function</sup>

             if (uart_irq_rx_ready(dev)) {
                  uart_fifo_read(dev, &recvData, 1);
                  printk("%c", recvData); 
             }


## Testing

16) In case you have only one Developement kit, you could also short the RX and TX pin on your Dev Kit. So you will receive the data byte "1", which is sent each second. In this case the Serial Terminal looks like this:

    ![missing image](images/ZHW_UART_INT-RX-TX.jpg)
   
17) There are different ways to test the software. In case you have two development kits you can connect both boards as follow_
    -  __Dev Kit 1__ <----> __Dev Kit 2__
    -  GND <----> GND      
    -  TX pin <----> RX pin    
    -  RX pin <----> TX pin    

   Open two Serial Terminal windows and connect the each one with one of your dev kits boards. you should see the same output as in previous step. However, this time the received data comes from the other board.
