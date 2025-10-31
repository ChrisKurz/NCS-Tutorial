<sup>SDK version: NCS v2.9.0  -  Link to Hands-on solution: https://github.com/ChrisKurz/nRF-Connect-SDK-HandsOn/tree/main/Workspace/NCS/NCSv2.9.0/version_app</sup>

# Application Version Management

## Introduction

Note that the Application Version Management is a functionality that was first time included in _nRF Connect SDK version 2.5.0_!

We have already talked about how to handle the [Zephyr Version](https://github.com/ChrisKurz/nRF_Connect_SDK/blob/main/doc/NCSv2.4.0_ZKS_Other_01_version.md). Beside that, it is also interesting to realize a version handling from the application firmware. Zephyr supports this with the [application Version management](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/2.5.0/zephyr/build/version/index.html).

In this hands-on we will use the application version management. 

## Required Hardware/Software
- Development kit [nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v2.9.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Create a new Project

1) Make a copy of the [hello_world](https://github.com/ChrisKurz/nRF-Connect-SDK-HandsOn/tree/main/Workspace/NCS/NCSv2.9.0/hello_world) project. 

### Add Application Version File

2) A new file is needed within the project folder. So add a file __VERSION__ (no extension in file name!) in the path where also the __CMakeLists.txt__ file is located.

	<sup>_VERSION_ </sup>

       VERSION_MAJOR = 1
       VERSION_MINOR = 2
       PATCHLEVEL = 3
       VERSION_TWEAK = 4
       EXTRAVERSION = unstable12

  NOTE: Use numbers for VERSION_MAJOR, VERSION_MINOR, PATCHLEVEL, and VERSION_TWEAK. You can use alphanumerical characters (lowercase a-z and 0-9) for EXTRAVERSION. 


### Use in C Code

3) To use the version information in application code, you must first include the version file. Add the following line in main.c file:

	<sup>_src/main.c_</sup>

       #include "app_version.h"

4) Then the version numbers of the application can be read out using the defines shown in this example:

	<sup>_src/main.c_ => main() function</sup>

            printk("Application version (VERSION_MAJOR|VERSION_MINOR|PATCHLEVEL|VERSION_TWEAK): %s\n", APPVERSION);
            printk("Application version number (VERSION_MAJOR|VERSION_MINOR|PATCHLEVEL): %s\n", APP_VERSION_NUMBER);
            printk("Application version major (VERSION_MAJOR): %i\n", APP_VERSION_MAJOR);
            printk("Application version minor (VERSION_MINOR): %i\n", APP_VERSION_MINOR);
            printk("Application version Patchlevel (PATCHLEVEL): %i\n", APP_PATCHLEVEL);
            printk("Application version string (VERSION_MAJOR.VERSION_MINOR.PATCHLEVEL.EXTRAVERSION): %s\n", APP_VERSION_STRING);
            printk("Application build version: %s\n", APP_BUILD_VERSION);


## Testing
5) Build the project and donwload it to your development kit. 
6) In the terminal you should see following outuput:

   ![image](images/DEV_version_app/App_Version_Terminal_NCSv2.9.0.jpg)

>__Note__: You can read the application version and application version number better if you convert them to hexadecimal.
>
>          16909060 (decimal) = 0x01020304 (hexadecimal)
>          66051 (decimal) = 0x010203 (hexadecimal)
