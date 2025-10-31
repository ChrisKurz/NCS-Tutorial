<sup>SDK version: NCS v2.5.0  -  Link to Hands-on solution: https://github.com/ChrisKurz/nRF_Connect_SDK/tree/main/Workspace/NCSv2.5.0/02_Logging_minimal</sup>

# Zephyr Logging - Minimal Memory Footprint

## Introduction

Zephyr Logging helps a lot when debugging during runtime is needed. However, it also requires a lot of memory resources. Since all the debug messages has to be stored in the code, the memory footprint is much bigger in larger projects. 

Here is a simple comparison of a really simple project. I have used the [Zehpyr Logging](https://github.com/ChrisKurz/nRF_Connect_SDK/blob/main/doc/NCSv2.5.0_02_ZephyrLogging.md) hands-on example and modified the code in different ways. 

1) Original Memory Footprint of the Zephyr Logging example:

   ![image](images/02_Logging_NormalMemory_NCSv2.5.0.jpg)

2) Completely removing Zephyr Logging (CONFIG_LOG=n, removing Logging related code in main.c file):

   ![image](images/02_Logging_DisabledMemory_NCSv2.5.0.jpg)

3) In this hands-on we will enable minimal mode for Logging. Enable minimal logging has very little footprint overhead on top of the printk() implementation for standard logging macros. Hexdump macros are also supported, with a small amount of code pulled in if used. Build time filtering is supported, but not runtime filtering. There are no timestamps, prefixes, colors, or asynchronous logging, and all messages are simply sent to printk(). Enabling minimal logging mode results for our test in following memory footprint:

   ![image](images/02_Logging_MinimalMemory_NCSv2.5.0.jpg)

If you compare these three projects, you will notice that Zephyr Logging occupies 10996 additional bytes in flash, while minimal Zephyr Logging occupies only 2380 additional bytes in flash. For larger projects, the difference can be much higher due to the much larger number of debug messages. 

## Required Hardware/Software
- one nRF52 development kit (e.g. nRF52DK, nRF52833DK, or nRF52840DK)
- install the _nRF Connect SDK_ v2.5.0 and _Visual Studio Code_. The description of the installation can be found [here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/2.5.0/nrf/getting_started/assistant.html#).


## Hands-on step-by-step description 

### Copy existing Zephyr Logging Project

1) Make a copy of the [Zephyr Logging](https://github.com/ChrisKurz/nRF_Connect_SDK/tree/main/Workspace/NCSv2.5.0/02_Logging) project. 

2) Add in the __prj.conf__ file the following line. 

   <sup>__prj.conf__</sup>

       CONFIG_LOG_MODE_MINIMAL=y

3) build the project and flash it on your development kit. 

## Testing

4) When doing the build, check the memory footprint.
5) Check the termninal output. You should see that timestamp, prefix and color are no longer handled and the output string is minimized. 

   ![image](images/02_Logging_MinimalTerminal_NCSv2.5.0.jpg)
