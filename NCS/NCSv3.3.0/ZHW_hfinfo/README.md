# Zephyr Hardware Driver: Hardware Infromation driver

## Introduction

The HW Info API provides access to hardware information such as device identifiers and reset cause flags. 


## Required Hardware/Software
- Development kit 
[nRF54LM20DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54LM20-DK),
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK),
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk)
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.3.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Create a new Project

1) Create a new project based on Zephyr's hello_world (zephyr/samples/hello_world).


### Add the HWINFO driver

2) Now we add the Zephyr Hardware Information driver to our project. Add following lines to the _prj.conf_ file:

	<sup>_prj.conf_</sup>

       # Enable HWINFO driver
       CONFIG_HWINFO=y

3) In order to use the Hardware Information driver API we also need to add the corresponding header file to our _main.c_ file:

	<sup>_src/main.c_</sup>

       #include <zephyr/drivers/hwinfo.h>


### Read the Reset Cause

4) Add following lines in the <code>main()</code> function of _main.c_ file:

	<sup>_src/main.c_ => in main() function</sup>

       uint32_t reset_cause;
       uint8_t dev_id[16];
       ssize_t length;
   
       /* --- Read Reset Cause --- */
       if (hwinfo_get_reset_cause(&reset_cause) == 0) {
           print_reset_cause(reset_cause);

           /* Afterwards clear Reset cause (optional) */
           hwinfo_clear_reset_cause();
       } else {
           printf("Failed to read reset cause\n");
       }

5) We call the function <code>print_reset_cause(reset_caues)</code> in the code we have just added. So let's insert also this function before the <code>main()</code>.

   <sup>_src/main.c_</sup>

       static void print_reset_cause(uint32_t cause)
       {
           printf("Reset cause(s):\n");

           if (cause == 0) {
               printf("  Unknown or no reset reason reported\n");
               return;
           }

           if (cause & RESET_POR) {
               printf("  - Power-on Reset (POR)\n");
           }
           if (cause & RESET_PIN) {
               printf("  - External pin reset\n");
           }
           if (cause & RESET_WATCHDOG) {
               printf("  - Watchdog reset\n");
           }
           if (cause & RESET_SOFTWARE) {
               printf("  - Software reset\n");
           }
           if (cause & RESET_CPU_LOCKUP) {
               printf("  - CPU lockup\n");
           }
           if (cause & RESET_LOW_POWER_WAKE) {
               printf("  - Wake from low power\n");
           }
       }


## Testing

6) Build and flash the application on your development kit.

7) Check the output on the Serial Termnial. Note that the Reset Cause as well as device ID is only printed once after power-up or reset. So you might press the Reset button on your development kit.

   ![image](images/terminal.jpg)
