<sup>SDK version: NCS v3.1.0 </sup>

# Zephyr Kernel Services: Timing - Uptime

## Introduction

The Zephyr kernel tracks a system uptime count. There are different API functions that allow to access this uptime. Most important is the k_uptime_get() function, which provides an uptime value in milliseconds since system boot. 


## Required Hardware/Software
- Development kit [nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk)
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.1.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Create a new Project

1) Create a new application. Use the zephyr/samples/hello_world sample. 

2) The Zephyr hello_world example uses the PicoLib library and includes because of this the __stdio.h__ header file. Since we want to work with Zephyr functionality, we have to include the zephyr/kernel.h header file. Add following line in main.c file. 
 
 	<sup>_src/main.c_</sup>   
   
       #include <zephyr/kernel.h>


### Uptime resolution

3) The resolution of the uptime depends on the hardware implementation. The kconfig symbol __CONFIG_SYS_CLOCK_TICKS_PER_SEC__ allows to define the resolution of the timer. Let's check the setting value.
  
  <sup>_src/main.c_ => add in main() function</sup>   
  
        printk("CONFIG_SYS_CLOCK_TICKS_PER_SEC = %i\n",CONFIG_SYS_CLOCK_TICKS_PER_SEC);


### Get the Uptime in ms

4) The uptime can be read as a value given in milli seconds when the default setting of CONFIG_SYS_CLOCK_TICKS_PER_SEC is used. The Zephyr counter is a 64-bit counter. However, the value can be read as a 32-bit value or 64-bit value.

  <sup>_src/main.c_ => add in main function</sup>   
  
        while(1){
            printk("Uptime (64-bit) = %llu ms\n",k_uptime_get());
            printk("Uptime (32-bit) = %i ms\n",k_uptime_get_32());
        }


### Get the Uptime in ticks

5) Since the uptime in ms depends on the kconfig settings, another way would be to read out the uptime as a value given in ticks. 

  <sup>_src/main.c_ => add in main fuction's while loop</sup>   

            printk("Uptime (64-bit) = %llu ticks\n",k_uptime_ticks());


### Get the Uptime in cycles that are measured by the system's hardware clock

6) The system's hardware clock value can be read with this function call.

  <sup>_src/main.c_ => main() function's while loop</sup>   

            printk("Uptime (32-bit) = %i cycles\n",k_cycle_get_32());
            printk("Uptime (64-bit) = %llu cycles\n",k_cycle_get_64());


### Get Delta Time

The kernel also provides a function that allows to get the elapsed time between the current system uptime and an earlier reference time. 

7) We will store the reference time in a 64-bit variable _reftime_. 

  <sup>_src/main.c_ => main() function</sup>   

        int64_t reftime;

8) And add following line before the while(1) loop: 

  <sup>_src/main.c_ => main() function</sup>   

        reftime=k_uptime_get();

9) To allow some testing we will use the k_msleep() function to get the main Thread sleeping for a defined time. Before entering the k_msleep funtion we do the calculation of the elapsed time. And first instruction aber wake-up we store the reference time. By this we get the time the software spends for all the printk outputs and the scheduler handling.

  <sup>_src/main.c_ => main() function's while loop</sup>   

            printk("-----\n");
            printk("Delta Time = %llu ms\n-----\n",k_uptime_delta(&reftime));
            k_msleep(5000 -16);
            reftime=k_uptime_get();

   NOTE: In k_msleep() function call we do a correction by subratcting 16 of the total sleep time. This is done to adjust the time when the first k_uptime_get() function call is done. By this you should see that the update time is closely around 5 seconds. 

       
## Testing

10) Build the project.
11) Open a terminal program (e.g. Putty - 115200 baud, 8 data bits, 1 stop bit, no flow control).
12) Flash the project to your development kit. 
13) Check the output in your terminal program. You should see something like this:

   ![image](images/Terminal.jpg)

  > __NOTE:__ Above Serial Terminal screen shot shows the output of an nRF54L15DK. When you use an nRF52840DK you find in the terminal output the line "Uptime (64-bit) = 0 cycles". The API function k_cycle_get_64() is used here. This would read out a hardware counter value. However, on the nRF52840DK board the MCU does not have a 64-bit counter. Because of that the value shown in the terminal is 0. You can also check if such a 64-bit counter is available by checking __CONFIG_TIMER_HAS_64BIT_CYCLE_COUNTER__. 
