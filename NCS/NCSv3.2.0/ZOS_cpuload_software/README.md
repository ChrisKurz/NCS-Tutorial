<sup>SDK version: NCS v3.2.0 </sup>

# Zephyr CPU Load - Software handling

## Introduction

Sometimes it can be helpful to determine how much CPU load a piece of software is consuming. Zephyr offers several ways to measure CPU load. The thread analyzer is one option. CPU Load is another, which is more accurate because it also takes into account the time spent in interrupt context. 

In this hands-on session, we'll take a look at how the user software can read the CPU load.


## Required Hardware/Software
- Development kit 
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk)
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Create a new Project

1) Make a copy of the Zephyr sample _blink_. 

### Adding _CPU Load_ Module

2) The CPU Load module can be used in different ways, like handling it in software or periodically getting a measure. In this hands-on we use the handling via user software. Add following KCONFIG settings to your prj.conf file.

   <sup>__prj.conf__</sup>

       # Zephyr Logging must be enabled to allow CPU Load module to output result
       CONFIG_LOG=y

       # Enable CPU Load
       CONFIG_CPU_LOAD=y

3) Include the CPU Load header file to your <code>main.c</code>.

   <sup>__main.c__</sup>

       #include <zephyr/debug/cpu_load.h>

4) Let's define a varaiable that is used to store the CPU Load measure result.

   <sup>__main.c__ => in <code>int main(void)</code> function</sup>

           int cpu_load_value;

5) In main's <code>while (1)</code> loop add folling instruction after the <code>k_msleep(SLEEP_TIME_MS);</code> line.

   <sup>__main.c__ => in main's entire loop</sup>

           cpu_load_value = cpu_load_get(true); /* Print CPU load */

6) And finally output the result in the serial termina.

   <sup>__main.c__ => after calling <code>cpu_load_value = cpu_load_get(true);</code>

           uint32_t percent = cpu_load_value / 10;
           uint32_t fraction = cpu_load_value % 10;
           printf("CPU load: %d.%03d%% \n", percent, fraction);


## Testing

3) Build the projecet (-> pristine build!) and flash it on your dev kit.
4) Check the Serial Terminal output.

   ![image](images/terminal.jpg)
