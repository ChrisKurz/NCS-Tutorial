# !!! WORK IN PROGRESS !!!
-----
# Writing a user-defined driver located in a separate driver directory outside the SDK

## Introduction

This hands-on shows how to create a simple custom LED driver in Zephyr that:
- Turns an LED on
- Turns an LED off
- Blinks an LED
- Allows configurable blink timing

The driver is done as a Zephyr external module stored in its own folder outside the _nRF Connect SDK_ tree. 

## Required Hardware/Software
- Development kit 
[nRF54LM20DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54LM20-DK),
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk), (nRF54L15DK)
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.3.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Project Structure

1) Create the following structure:
   
  ![image](images/folder_structure.jpg)
   

### Register the Folder as a Zephyr Module

In Zephyr, external drivers are typically integrated as __modules__. This means your driver can be located entirely outside the Zephyr or _nRF Connect SDK_ repository.

How does Zephyr find external modules? During the build, Zephyr scans the main project and all registered modules. A module is identified by the <code>zephyr/module.yml</code> file. This <code>module.yml</code> file tells Zephyr where Kconfig is located, where CMake is located, and any optional additional metadata.

2) Zephyr discovers external code through __zephyr/module.yml__. Create <code>modules/app_led_driver/zephyr/module.yml</code>.

   <sup>__modules/app_led_driver/zephyr/module.yml__</sup>

```yaml
name: my_led_driver
build:
  kconfig: Kconfig
  cmake: .
  settings:
    dts_root: .
```

> __Note:__
> - <code>cmake</code> and <code>kconfig</code> point to the module root build files
> - <code>dts_root</code> tells Zephyr to pick up custom DeviceTree bindings from this module

> __Note:__ _Why are the fields <code>cmake</code> and <code>kconfig</code> differently handled?_
>
> Both fields live under <code>build:</code> in <code>module.yml</code>, but they do not mean the same thing. That's why we use <code>cmake: .</code> together with <code>kconfig: Kconfig</code>, despite both files are located in the same folder.
>
> The <code>cmake:</code> field expects a directory in which the file <code>CMakeLists.txt</code> can be found. While the field <code>kconfig:</code> expects a file path to the Kconfig file to include.
>
> <code>build:</code> <br>
> <code>  cmake: .          # directory → ./CMakeLists.txt </code> <br>
> <code>  kconfig: Kconfig  # file      → ./Kconfig </code> 

### Integrate the Module into CMake and Kconfig

3) Here are the required CMakeLists.txt files. 

  ![image](images/cmake.jpg)

   <sup>__myDrivers/CMakeLists.txt__</sup>

    add_subdirectory(drivers)
    zephyr_include_directories(include)

-----
   <sup>__myDrivers/drivers/CMakeLists.txt__</sup>

    add_subdirectory_ifdef(CONFIG_APP_LED led)
-----
   <sup>__myDrivers/drivers/CMakeLists.txt__</sup>

    add_subdirectory_ifdef(CONFIG_APP_LED_GPIO gpio)

4) And here are the required Kconfig files.

   ![image](images/kconfig.jpg)






-----------------------------------------------------
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


### Create the main Application

4) Add following test code in the main.c file.

   <sup>__src/main.c__</sup>

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

               my_led_on();
               k_sleep(K_SECONDS(2));

               my_led_off();
               k_sleep(K_SECONDS(2));
  
               my_led_blink_start(500);
               k_sleep(K_SECONDS(5));

               my_led_blink_stop();
               k_sleep(K_SECONDS(2));
           }

           return 0;
       }


### Create the Top-Level CMake File

5) Add following lines in CMakeLists.txt file.

   <sup>__CMakeLists.txt__</sup>

       cmake_minimum_required(VERSION 3.20.0)

       find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

       project(my_led_project)

       target_sources(app PRIVATE src/main.c
                                  drivers/my_led/my_led.c)

       target_include_directories(app PRIVATE drivers/my_led)

### Create prj.conf

6) Enable GPIO support.

   <sup>__prj.conf__</sup>

       CONFIG_GPIO=y

## Testing

7) Build the project and download to a development kit.
8) Check the LED on your development kit. You should see:
   - LED on for 2 seconds
   - LED off for 2 seconds
   - LED blinks every 500ms for 5 seconds
   - Repeat forever
