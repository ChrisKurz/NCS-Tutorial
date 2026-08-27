# Debugging: Profile each Boot Stage using GPIO

## Introduction

It is sometimes interesting to understand where time is spent during the start-up of a Zephyr application. The actual application starts in the `main()` function. However, quite a lot happens before that. Here, we look at one way of measuring the time it takes for Zephyr to boot through the EARLY, PRE_KERNEL_1, PRE_KERNEL_2 and POST_KERNEL states, and finally into `main()`. 


## Required Hardware/Software
- Development kit 
[nRF54LM20DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54LM20-DK),
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk)
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.4.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Create a new Project

1) Make a copy of the Zephyr sample _hello world_. 

### Profiling Boot Stages with GPIO Toggles

#### Step 1: Define the GPIO Pin in a DTS overlay. 

2) Create your application's _.overlay_ file to declare a debug GPIO pin.

   <sup>nrf54l15dk_nrf54l15_cpuapp.overlay</sup>
   
   ```
   / {
       user_dbg_pin: user-dbg-pin {
           compatible = "nordic,gpio-pins";
           gpios = <&gpio0 2 GPIO_ACTIVE_HIGH>;
           status = "okay";
       };
   };

   &gpio0 {
       status = "okay";
   };

   &gpiote0 {
       status = "okay";
   };
   ```

#### Step 2: Include the pin in your application code

3) Use the GPIO DeviceTree API to access and drive the pin.

   <sup>main.c</sup>
   
   ```c
   #include <zephyr/drivers/gpio.h>

   static const struct gpio_dt_spec pin_dbg = GPIO_DT_SPEC_GET_OR(DT_NODELABEL(user_dbg_pin), gpios, {0});
   ```

4) Initialize the pin.

   <sup>main.c</sup>
   
   ```c
   if (pin_dbg.port) {
       gpio_pin_configure_dt(&pin_dbg, GPIO_OUTPUT_INACTIVE);
   }
   ```

5) Toggle the pin to mark boot stages.

   <sup>main.c</sup>

   ```c
   if (pin_dbg.port) {
       gpio_pin_set_dt(&pin_dbg, 1);  /* stage start */
   }
   
   /* ... */
   
   if (pin_dbg.port) {
       gpio_pin_set_dt(&pin_dbg, 0);  /* stage end */
   }
   ```

#### Step 3: Place Markers at Each Boot Stage Using <code>SYS_INIT</code>

6) Register init functions at each boot level to toggle the pin, as shown in the boot time investigation example.

  <sup>main.c</sup>

   ```c
   int prek1_marker(const struct device *dev) {
       gpio_pin_configure(GPIO1_DEV, 2, GPIO_OUTPUT);
       gpio_pin_set(GPIO1_DEV, 2, 1);
       return 0;
   }
   SYS_INIT(prek1_marker, PRE_KERNEL_1, 0);

   int prek2_marker(const struct device *dev) {
       gpio_pin_set(GPIO1_DEV, 2, 0);
       return 0;
   }
   SYS_INIT(prek2_marker, PRE_KERNEL_2, 0);
  
   int postk_marker(const struct device *dev) {
       gpio_pin_set(GPIO1_DEV, 2, 1);
       return 0;
   }
   SYS_INIT(postk_marker, POST_KERNEL, 0);
   
   int main(void) {
       gpio_pin_set(GPIO1_DEV, 2, 0);
       /* ... */
   }   
   ```

> __NOTE:__
> - No extra Kconfig option is needed — the GPIO driver is enabled via the DTS overlay (status = "okay"). 
> - The if (pin_dbg.port) guard means the debug code is automatically inactive if you build without the user-dbg-pin DTS node — a clean way to disable it for production builds.
> - Observe the resulting square wave on a logic analyzer or oscilloscope to measure the time spent in each boot stage.
> - To inspect the full initialization sequence order, you can also run west build -t initlevels. 


## Testing

3) Build the projecet (-> pristine build!) and flash it on your dev kit.
4) Us a scope and check the Debug pin.
