# Version number for Application Image

Using a version number for the application image is recommended and is even required for some enabled MCUboot features, such as Downgrade Protection. There are several ways to define a version number for the application. It is recommended to do this via a VERSION file.

## Required Hardware/Software

- Development kit
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK),
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK),
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 

- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Copy previous project

1) Copy the previous project and reanme it. 

   > __Note:__ Do not use "mcuboot" as your project name here! 

   Use the same Build Configuration as in previous project.

### Adding Version number 

2) Add the file __VERSION__ to the project folder (same folder where __CMakeLists.txt__ file is stored).
3) And add following to the __VERSION__ file.

    <sup>VERSION</sup>   

        VERSION_MAJOR = 1
        VERSION_MINOR = 2
        PATCHLEVEL = 3
        VERSION_TWEAK = 4
        EXTRAVERSION = test-1

  > __NOTE:__ The fields _VERSION_MAJOR_, _VERSION_MINOR_, _PATCHLEVEL_, and _VERSION_TWEAK_ require a numerical data type. Its value has to be in the range 0 to 255. The field _EXTRAVERSION_ requires a alphanumerical data type (Lower-case a-z and 0-9, and "." or "-").


### Output Version number

4) During the build process, the __VERSION__ file is processed and the header file __app_version.h__ is generated. 

	<sup>_src/main.c_</sup>

       #include "app_version.h"

5) The version numbers of the application are available in this header file.

	<sup>_src/main.c_ => main() function</sup>

           printf("Application version (VERSION_MAJOR|VERSION_MINOR|PATCHLEVEL|VERSION_TWEAK): %s\n", APPVERSION);

