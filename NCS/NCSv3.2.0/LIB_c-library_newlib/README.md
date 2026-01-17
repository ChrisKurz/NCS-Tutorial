<sup>SDK version: NCS v3.2.0 </sup>

# Zephyr's C Libraries:  Newlib

## Introduction

The C standard library provides macros, type definitions and functions for tasks such as string manipulation, mathematical computation, input/output processing, memory managenet, and input/output. 

Zephyr allows to select one for the following C libraries:

   ![image](images/picolib_kconfig.jpg)

[Newlib](https://docs.nordicsemi.com/bundle/ncs-latest/page/zephyr/develop/languages/c/newlib.html) is a complete C library implementation written for the embedded systems. It is a separate open source project and is not included in source code form with Zephyr. Instead, the Zephyr SDK includes a precompiled library for each supported architecture (libc.a and libm.a).

Newlib is an older standard C library. There are newer standard C libraries, such as Picolibc, which is also based on Newlib. 


## Required Hardware/Software
- Development kit 
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Create needed Folders and Files

1) Create a new application. Use the _zephyr/samples/hello_world_ sample.  

2) Let's have a look on how the C library is usually selected. You can use the __nRF KCONFIG GUI__ tool to check which C library is selected in this project. 

   ![image](images/picolibc_selectedLibc.jpg)

   The Picolibc library is included in the Zephyr toolchain and it is selected by default as the standard C library. 

3) You can explicitly add Picolibc to your project by inlcuding following line in __prj.conf__ file.

   <sup>__prj.conf__</sup>

       # select C library PICOLIBC
       CONFIG_PICOLIBC=y
