<sup>SDK version: NCS v3.0.0  -  Link to Hands-on solution: https://github.com/ChrisKurz/nRF-Connect-SDK-HandsOn/tree/main/Workspace/NCS/NCSv3.0.0/serialRecovery_UART</sup>

# MCUboot: Serial Recovery - UART

## Introduction

MCUboot is usually not taking care about upgrade image download. This is usually handled in application software. However, there is a serial recovery feature in MCUboot. This includes simple communication software modules that allow to download an upgrade image via UART. We take a look on this in this hands-on.

## Required Hardware/Software
- Development kit [nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.0.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Let's start with our previous done _helloWorld_ project

1) Make a copy of the previouse [_helloWorld_ project](mcuboot_AddToProject.md). 


### Add DFU over UART to MCUboot

2) The serial recovery feature is enabled in the MCUboot project. So we have to do the appropriate settings in MCUboot's __prj.conf__ file. This is done by adding a __sysbuild__ folder in our project. In the sysbuild folder we need the file __mcuboot.conf__. This configuration file is used to overwrite the default MCUboot settings.

> __NOTE:__ We could change the MCUboot prj.conf file in the SDK folder, but this would change the SDK and possibly cause problems later on. What we want to do here is to implement the MCUboot configuration in our own project. This leaves the SDK unchanged and the MCUboot setting is contained in our own project.

3) And add following KCONIFGs to enable serial recovery.

    <sup>sysbuild/mcuboot.conf</sup>

       CONFIG_MCUBOOT_SERIAL=y
       CONFIG_BOOT_SERIAL_UART=y

4) MCUboot should not use console, because the serial recovery handles the communication. Any log message would cause problems. So, let's disable Console for MCUboot.

    <sup>sysbuild/mcuboot.conf</sup>
    
       CONFIG_UART_CONSOLE=n


### Enable Logging for MCUboot (optional)

5) While during development the logging might be quite helpful, you may disable Logging for your software release. Enabling is done by adding following lines to __mcuboot.conf__ file.

    <sup>sysbuild/mcuboot.conf</sup>
    
       CONFIG_LOG=y
       CONFIG_MCUBOOT_LOG_LEVEL_INF=y

> __Note:__ In this case, the Logging is using RTT, because UART will be used by McuMgr for firmware download.
> 


### Bootloader indication LED and button

We use a button press while a reset to start serial recovery. Moreover we use the bootloader LED indication to highlight when bootloader is in Serial Recovery mode.

6) Adding LED indication is done by the following MCUboot KCONFIG.

    <sup>sysbuild/mcuboot.conf</sup>

       CONFIG_MCUBOOT_INDICATION_LED=y

7) We also have to define in DeviceTree which button and which LED is used by MCUboot. So first add in folder __sysbuild__ the file __mcuboot.overlay__.

    <sup>sysbuild/mcuboot.overlay</sup>

       / {
         aliases {
                 mcuboot-button0 = &button1;
                 mcuboot-led0 = &led1;
                 };
        };


### Version number of our application

8) Add the file __VERSION__ to the project folder (same folder where __CMakeLists.txt__ file is stored).
9) And add following to the __VERSION__ file.

    <sup>VERSION</sup>   

        VERSION_MAJOR = 1
        VERSION_MINOR = 2
        PATCHLEVEL = 3
        VERSION_TWEAK = 4
        EXTRAVERSION = 
