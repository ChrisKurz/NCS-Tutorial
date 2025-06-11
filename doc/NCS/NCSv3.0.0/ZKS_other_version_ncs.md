<sup>SDK version: NCS v3.0.0  -  Link to Hands-on solution: https://github.com/ChrisKurz/NCS-Tutorial/tree/main/Workspace/NCS/NCSv3.0.0/version_ncs</sup>

# nRF Connect SDK Version 

## Introduction

Maybe you want also to read out the version number of the used _nRF Conned SDK_. This hands-on describes how this can be done. 

## Required Hardware/Software
- Development kit [nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.0.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Create a new Project

1) Make a copy of the [hello_world](https://github.com/ChrisKurz/nRF-Connect-SDK-HandsOn/tree/main/Workspace/NCS/NCSv3.0.0/hello_world) project. 


### Use in C Code

2) To use the version information in application code, you must first include the _nRF Connect SDK_ version file. Add the following line in main.c file:

	<sup>_src/main.c_</sup>

       #include "ncs_version.h"

3) Then the version numbers of the _nRF Connect SDK_ can be read out using the defines shown in this example:

	<sup>_src/main.c_ => main() function</sup>

            printk("nRF Connect SDK version (NCS_VERSION_MAJOR|NCS_VERSION_MINOR|NCS_PATCHLEVEL): %d\n", NCS_VERSION_NUMBER);
            printk("nRF Connect SDK version major (NCS_VERSION_MAJOR): %i\n", NCS_VERSION_MAJOR);
            printk("nRF Connect SDK version minor (NCS_VERSION_MINOR): %i\n", NCS_VERSION_MINOR);
            printk("nRF Connect SDK version Patchlevel (NCS_PATCHLEVEL): %i\n", NCS_PATCHLEVEL);
            printk("nRF Connect SDK version string (NCS_VERSION_MAJOR.NCS_VERSION_MINOR.NCS_PATCHLEVEL): %s\n", NCS_VERSION_STRING);


## Testing
4) Build the project and donwload it to your development kit. 
5) In the terminal you should see following outuput:

   ![image](images/ZKS_other_version_ncs/Terminal.jpg)

Note: You can read the nRF Connect SDK version number better if you convert them to hexadecimal. 

  133376 (decimal) = 0x020900 (hexadecimal)
