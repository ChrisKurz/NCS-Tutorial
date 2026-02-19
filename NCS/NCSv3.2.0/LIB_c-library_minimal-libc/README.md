<sup>SDK version: NCS v3.2.0 </sup>

# Zephyr's C Libraries:  Minimal Libc

## Introduction

The C standard library provides macros, type definitions and functions for tasks such as string manipulation, mathematical computation, input/output processing, memory managenet, and input/output. 

Zephyr allows to select one for the following C libraries:

   ![image](images/picolib_kconfig.jpg)

The most basic C library, named [minimal libc](https://docs.nordicsemi.com/bundle/ncs-latest/page/zephyr/develop/languages/c/minimal_libc.html), is part of the Zephyr codebase and provides the minimal subset of the standard C library required to meet the needs of Zephyr and its subsystems, primarily in the areas of string manipulation and display. It is very low footprint and is suitable for projects that do not rely on less frequently used portions of the ISO C standard library. It can also be used with a number of different toolchains.

The minimal libc implementation can be found in _lib/libc/minimal_ in the main Zephyr tree.



## Required Hardware/Software
- Development kit 
[nRF54LM20DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L20-DK),
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Create needed Folders and Files

1) Create a new application. Use the _zephyr/samples/hello_world_ sample.  

2) In the previous hands-on session on picolibc, we already saw that picolibc is selected by default. Therefore, we will now change this setting by selecting minimal libc.

   <sup>__prj.conf__</sup>

       # select C library: minimal libc
       CONFIG_MINIMAL_LIBC=y


3) Let's have a look on how the C library is usually selected. You can use the __nRF KCONFIG GUI__ tool to check which C library is selected in this project. 

   ![image](images/minimallibc_selectedLibC.jpg)

4) There are additional settings that allow you to enable or disable minimal libc library functions. Here is a list:

   | Kconfig Name                                 | Default | Description                       |
   |----------------------------------------------|---------|-----------------------------------|
   | CONFIG_MINIMAL_LIBC_RAND                     |   n     | Enable <code>rand_r()</code>      | 
   | CONFIG_MINIMAL_LIBC_TIME                     |   y     | Enable <code>time()</code> and <code>gmtime_r()</code>      |
   | CONFIG_MINIMAL_LIBC_LL_PRINTF                |   n     | Build with long long printf enabled. This will increase the size of the image. |
   | CONFIG_MINIMAL_LIBC_STRING_ERROR_TABLE       |   n     | Select this option to ensure that <code>strerror()</code>, <code>strerror_r()</code> produce strings corresponding to the descriptions in __errno.h__. The string error table can add ~2kiB to ROM. As such, it is disabled by default. In this case, <code>strerror()</code> and <code>strerror_r()</code> symbols are still present, but the functions produce an empty string. |
   | CONFIG_MINIMAL_LIBC_NON_REENTRANT_FUNCTIONS  |   y     | Enable non-reentrant functions that make use of the globals, e.g. <code>rand()</code> and <code>gmtime()</code>. The globals must be put into a dedicated C library memory partition when CONFIG_USERSPACE=y, and enabling this option may require an additional memory protection region. |
   | CONFIG_MINIMAL_LIBC_OPTIMIZE_STRING_FOR_SIZE |   y     | Enable smaller but potentially slower implementations of <code>memcpy</code> and <code>memset</code>. On the Cortex-M0+ this reduces the total code size by 120 bytes. |

   <sup>__prj.conf__</sup>

       CONFIG_MINIMAL_LIBC_RAND=n
       CONFIG_MINIMAL_LIBC_TIME=y
       CONFIG_MINIMAL_LIBC_LL_PRINTF=n
       CONFIG_MINIMAL_LIBC_STRING_ERROR_TABLE=n
       CONFIG_MINIMAL_LIBC_NON_REENTRANT_FUNCTIONS=y
       CONFIG_MINIMAL_LIBC_OPTIMIZE_STRING_FOR_SIZE=y
