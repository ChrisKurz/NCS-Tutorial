# nRF Connect SDK (NCS)

The _nRF Connect SDK_ version used here is NCS version 3.0.0.

--------
## Table of Content

- [Basics - Developing with _nRF Connect SDK_ and _Zephyr_](#first-steps)

- [Zephyr Kernel Services](#zephyr-kernel-services)
    > [Threads](#threads)
    >
    > [Timing](#timing)
    >
    > [Other](#other)
    >> [Version](#version)

- [Zephyr OS Services](#zephyr-os-services)
    > [Logging](#logging)
    >
    > [Shell](#shell)
  
- [Zephyr Device Drivers](#zephyr-device-drivers)

- [Libraries](#libraries)

--------

## Basics - Developing with _nRF Connect SDK_ and Zephyr

### First Steps

- [__Installation of _nRF Connect SDK___](NCSv3.0.0/DEV_installation.md) - This step-by-step description explains how to install the _nRF Connect SDK_.

- [__Opening an existing sample__](NCSv3.0.0/DEV_OpenSample.md) - This step-by-step description explains how to create a copy of an existing sample project and open this copy.

- [__Creating a Project from Scratch__](NCSv3.0.0/DEV_ProjectFromScratch.md) - This hands-on shows how to create a minimal project from scratch.

### KConfig

- [__User-defined KCONFIG symbols__](NCSv3.0.0/DEV_kconfig_UserDefined.md) - You can use KCONFIG to add software modules from Zephyr repository or other repositories. You can also define your own KCONFIG symbols. This practical exercise demonstrates how to do this. It uses custom KCONFIG in C code.

### DeviceTree

- [__Getting DeviceTree Properties__](NCSv3.0.0/DEV_DeviceTree.md) - This example shows how to read DeviceTree properties from C code. 


## Zephyr Kernel Services

### Threads

- [__Thread: Creating a Thread__](NCSv3.0.0/ZKS_threads_create.md) - This hands-on shows how to create a Thread.


### Timing

- [__Timers__](NCSv3.0.0/ZKS_timing_timers.md) - This hands-on shows how Zephyr's Timing Kernel Service can be used (Timer for Function trigger).

- [__UpTime__](NCSv3.0.0/ZKS_timing_UpTime.md) - Zephyr enables the application to access an operating time counter. This example demonstrates the available API functions.


### Other

#### Version

- [__Getting Zephyr version from application software__](NCSv3.0.0/ZKS_other_version_zephyr.md) - This example shows how the version number of Zephyr can be retrieved in an application software.

- [__Getting _nRF Connect SDK_ version__](NCSv3.0.0/ZKS_other_version_ncs.md) - The application software can also read out the _nRF Connect SDK_ version used in the project. This example shows how.

- [__Getting Application Firmware Version__](NCSv3.0.0/ZKS_other_version_app.md) - Zephyr contains a version management for applications  since _nRF Connect SDK v2.5.0_. This example shows how to use it.


## Zephyr OS Services

### Logging

- [__Adding Zephyr Logging__](NCSv3.0.0/ZOS_logging_uart.md) - Here we add Zephyr Logging to our project. This allows us to get debug messages during runtime. In this sample we use UART backend.


- [__Zephyr Logging in modules with multiple files__](NCSv3.0.0/ZOS_logging_declare.md) - This hands-on shows how to add Logging to a module that consist of multiple files.

- [__Zephyr Logging with minimal Memory Footprint__](NCSv3.0.0/ZOS_logging_minimal.md) - This hands-on shows how to optimize memory footprint of Zephyr Logging.

- [__User-defined Log Level KCONFIG__](NCSv3.0.0/ZOS_logging_userKconfig.md) - This practical examples shows how to use the KCONFIG Logging template to allow users to define Log Level via a user-define KCONFIG.


### Shell

- [__Adding Zephyr Shell__](NCSv3.0.0/ZOS_shell.md) - Here we add Zephyr Shell to our project. It is a UNIX-like shell. In this simple hands-on we add our own commands to switch on/off a LED on the used development kit. 

- [__I2C Shell__](NCSv3.0.0/ZOS_shell_i2c.md) - This hands-on shows how to enable I2C shell. It is shown how to scan for I2C devices on the bus and reading a byte from the connected sensor.


## Zephyr Device Drivers

### Sensor Device Drivers

- [**Basics: Initializing Sensor Driver during Zephyr Start-up**](NCSv3.0.0/ZDD_sensor_basics_initZephyr.md) - In this first basic hands-on we will explain how to initialize and start the sensor driver. There are various ways to start the driver. Here we look at how the driver is automatically started during Zephyr RTOS startup.

- [**Basics: Initializing Sensor Driver within user Code**](NCSv3.0.0/ZDD_sensor_basics_initApp.md) - Here we describe another way to initialize and start the sensor driver. In this case, the driver is started in the user application.


## Libraries

### ZCBOR 

- [__Add ZCBOR to project and handling of Encoding/Decoding__](NCSv3.0.0/LIB_zcbor_HelloWorld.md)
