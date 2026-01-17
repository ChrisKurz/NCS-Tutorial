<sup>SDK version: NCS v3.1.0 </sup>

# Zephyr Hardware Driver: Flash - External NOR Flash, sQSPI Interface

## Introduction



## Required Hardware/Software
- Development kit [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk), (nRF54L15DK)
  > __Note__: Two development kits allow to check communication between boards. It is also possible to test the software with one development kit; in this case the board receives the data byte it has sent.
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.1.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Create a new Project

1) Create a new project based on [_Creating a Project from Scratch_ exercise](../DEV_ProjectFromScratch). 


### Add needed Software Module _Flash_

2) The external NOR-Flash memory is handled by the Zephyr Flash driver. That's why we first need to add the Flash driver.

       # enable flash driver
       CONFIG_FLASH=y

3) In order to use the Flash hardware driver API we also need to add the corresponding header file to our _main.c_ file:

	<sup>_src/main.c_</sup>

       #include <zephyr/drivers/flash.h>


### Adding DeviceTree overlay file for Flash

4) Create an overlay file. (e.g. __nrf52840DK_nrf52840.overlay__)

5) UART0 is already usind on the development kit for the logging. It's usage is already defined in the board definition files. We will use UART1 in our example here for our own UART communication. Add following lines in the device tree overlay file of your project. 

	<sup>_nrf52840DK_nrf52840.overlay_</sup>

        &pinctrl {
	    sqspi_default: sqspi_default {
                group1 {
			psels = <NRF_PSEL(SDP_MSPI_SCK, 2, 1)>,
				<NRF_PSEL(SDP_MSPI_CS0, 2, 5)>,
				<NRF_PSEL(SDP_MSPI_DQ0, 2, 2)>;
			nordic,drive-mode = <NRF_DRIVE_E0E1>;
                };
                group2 {
			psels = <NRF_PSEL(SDP_MSPI_DQ1, 2, 4)>,
				<NRF_PSEL(SDP_MSPI_DQ2, 2, 3)>,
				<NRF_PSEL(SDP_MSPI_DQ3, 2, 0)>;
			nordic,drive-mode = <NRF_DRIVE_E0E1>;
			bias-pull-up;
                };
            };

            sqspi_sleep: sqspi_sleep {
		group1 {
			low-power-enable;
			psels = <NRF_PSEL(SDP_MSPI_SCK, 2, 1)>,
				<NRF_PSEL(SDP_MSPI_CS0, 2, 5)>,
				<NRF_PSEL(SDP_MSPI_DQ0, 2, 2)>,
				<NRF_PSEL(SDP_MSPI_DQ1, 2, 4)>,
				<NRF_PSEL(SDP_MSPI_DQ2, 2, 3)>,
				<NRF_PSEL(SDP_MSPI_DQ3, 2, 0)>;
		};
            };
        };

        &cpuflpr_vpr {
           pinctrl-0 = <&sqspi_default>;
           pinctrl-1 = <&sqspi_sleep>;
           pinctrl-names = "default", "sleep";
           interrupts = <76 NRF_DEFAULT_IRQ_PRIORITY>;
           status = "okay";
        };

        / {
	reserved-memory {
		#address-cells = <1>;
		#size-cells = <1>;
		ranges;

		softperipheral_ram: memory@2003c000 {
			reg = <0x2003c000 0x4000>;
			ranges = <0 0x2003c000 0x4000>;
			#address-cells = <1>;
			#size-cells = <1>;

			sqspi: sqspi@3b40 {
				compatible = "nordic,nrf-sqspi";
				#address-cells = <1>;
				#size-cells = <0>;
				reg = <0x3b40 0x200>;
				status = "okay";
				zephyr,pm-device-runtime-auto;
			};
		};
	};
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


### Let's add polling for received data

9)  The polling function allows to receive a single byte. So we will store the received by in the variable _data_.

	<sup>_src/main.c_ => main() function</sup>
 
            unsigned char data;

10) Let's add the while(1) loop in main function and call the _uart_poll_in()_ API function. 

	<sup>_src/main.c_ => main() function</sup>
 
            while(1){
                while(uart_poll_in(my_uart, &data) <0){
                    /* Allow other thread/workqueue to work. */
                    k_yield();            
                }
            }

11) Let's output the received byte in the PC's serial terminal program. 

	<sup>_src/main.c_ => main() function</sup>

            printk("received byte: %c \n", data); 

### Now add transmit 

12) We use a timer here to send one character each second. So let's setup the Timer. First define the k_timer variable.

	<sup>_src/main.c_</sup>

        struct k_timer MyTimer;
 
13) And then initialize the timer.

	<sup>_src/main.c_ => main() function</sup>

            k_timer_init(&MyTimer, TimerExpire, TimerStopped);
            k_timer_start(&MyTimer, K_MSEC(0), K_MSEC(1000)); // period 1 second

> __NOTE__: You can also check the [Timer](https://github.com/ChrisKurz/nRF_Connect_SDK/blob/main/doc/NCSv2.5.0_ZKS_Timing_02_Timers.md) hands-on.

14) Let's add in TimerExpire function the transmit command.

	<sup>_src/main.c_</sup>

        static void TimerExpire(struct k_timer *timer) {
            printk("transmit data byte \n");
            uart_poll_out(my_uart, (unsigned char) '1');
        }

        static void TimerStopped(struct k_timer *timer) {
            printk("Timer was stopped!\n");       
        }


## Testing

