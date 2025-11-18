# nRF Connect SDK (NCS)

The _nRF Connect SDK_ version used here is NCS version 3.1.0.

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

- [Zephyr Hardware Drivers](#zephyr-hardware-drivers)
  
- [NRFX Drivers](#nrfx-drivers)
  
- [Libraries](#libraries)

- [Tools](#tools)
  
--------

## Basics - Developing with _nRF Connect SDK_ and Zephyr

### First Steps

- [__Installation of _nRF Connect SDK___](DEV_installation/README.md) - This step-by-step description explains how to install the _nRF Connect SDK_.

- [__Opening an existing sample__](DEV_OpenSample/README.md) - This step-by-step description explains how to create a copy of an existing sample project and open this copy.

- [__Creating a Project from Scratch__](DEV_ProjectFromScratch/README.md) - This hands-on shows how to create a minimal project from scratch.

- [__Defining a new Board__](DEV_NewBoard/README.md)

### KConfig

- [__User-defined KCONFIG symbols__](DEV_kconfig_UserDefined/README.md) - You can use KCONFIG to add software modules from Zephyr repository or other repositories. You can also define your own KCONFIG symbols. This practical exercise demonstrates how to do this. It uses custom KCONFIG in C code.

### DeviceTree

- [__Getting DeviceTree Properties__](DEV_DeviceTree/README.md) - This example shows how to read DeviceTree properties from C code. 
- [__Delete a property__](DEV_DeviceTree_delete-property/README.md) 

## Zephyr Kernel Services

### Data Passing

- [__FIFO__](ZKS_data-passing_fifo/README.md)


### Threads

- [__Creating a Thread__](ZKS_threads_create/README.md) - This hands-on shows how to create a Thread.
- [__Suspend and Resume a Thread__](ZKS_threads_suspend/README.md) - This hands-on shows how to suspend and resume a Thread.

### Timing

- [__Timers__](ZKS_timing_timers/README.md) - This hands-on shows how Zephyr's Timing Kernel Service can be used (Timer for Function trigger).

- [__UpTime__](ZKS_timing_UpTime/README.md) - Zephyr enables the application to access an operating time counter. This example demonstrates the available API functions.


### Other

#### Version

- [__Getting Zephyr version from application software__](ZKS_other_version_zephyr/README.md) - This example shows how the version number of Zephyr can be retrieved in an application software.

- [__Getting _nRF Connect SDK_ version__](ZKS_other_version_ncs/README.md) - The application software can also read out the _nRF Connect SDK_ version used in the project. This example shows how.

- [__Getting Application Firmware Version__](ZKS_other_version_app/README.md) - Zephyr contains a version management for applications  since _nRF Connect SDK v2.5.0_. This example shows how to use it.


## Zephyr OS Services

### Logging

- [__Adding Zephyr Logging__](ZOS_logging_uart/README.md) - Here we add Zephyr Logging to our project. This allows us to get debug messages during runtime. In this sample we use UART backend.


- [__Zephyr Logging in modules with multiple files__](ZOS_logging_declare/README.md) - This hands-on shows how to add Logging to a module that consist of multiple files.

- [__Zephyr Logging with minimal Memory Footprint__](ZOS_logging_minimal/README.md) - This hands-on shows how to optimize memory footprint of Zephyr Logging.

- [__User-defined Log Level KCONFIG__](ZOS_logging_userKconfig/README.md) - This practical examples shows how to use the KCONFIG Logging template to allow users to define Log Level via a user-define KCONFIG.


### Shell

- [__Adding Zephyr Shell__](ZOS_shell/README.md) - Here we add Zephyr Shell to our project. It is a UNIX-like shell. In this simple hands-on we add our own commands to switch on/off a LED on the used development kit. 

- [__I2C Shell__](ZOS_shell_i2c/README.md) - This hands-on shows how to enable I2C shell. It is shown how to scan for I2C devices on the bus and reading a byte from the connected sensor.


## Zephyr Device Drivers

### Sensor Device Drivers

- [__Basics: Initializing Sensor Driver during Zephyr Start-up__](ZDD_sensor_basics_initZephyr/README.md) - In this first basic hands-on we will explain how to initialize and start the sensor driver. There are various ways to start the driver. Here we look at how the driver is automatically started during Zephyr RTOS startup.

- [__Basics: Initializing Sensor Driver within user Code__](ZDD_sensor_basics_initApp/README.md) - Here we describe another way to initialize and start the sensor driver. In this case, the driver is started in the user application.

- [__BME280: using sensor with nRF52840DK (sensor handling in main function)__](ZDD_sensor_bme280_nrf52840dk/README.md)

- [__BME280: using sensor with nRF52840DK (sensor handling in Thread)__](ZDD_sensor_bme280_nrf52840dk_thread/README.md)

## Zephyr Hardware Drivers

- [__ADC - single channel__](ZHW_adc/README.md) 

- [__ADC - handling in a thread__](ZHW_adc_thread/README.md)

- [__UART using polling__](ZHW_uart_polling/README.md)

- [__UART with interrupt support__](ZHW_uart_interrupt/README.md)
  

## NRFX Drivers

- [__ADC__](NRFX_adc/README.md)

- [__SPI__](NRFX_spi/README.md)

## Libraries

### Standard C Libraries

- [__Using PICOLIBC__](LIB_c-library_picolibc/README.md) 

### ZCBOR 

- [__Add ZCBOR to project and handling of Encoding/Decoding__](LIB_zcbor_HelloWorld/README.md)


## Tools

- [__Software Bill of Material: License Report__](TOOL_LicenseReport/README.md)
  
