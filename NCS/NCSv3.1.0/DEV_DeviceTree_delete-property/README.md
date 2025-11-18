<sup>SDK version: NCS v3.1.0 </sup>

# DeviceTree: Delete a property

## Introduction

If you want to use an existing board definition for your own project, you can use an overlay file to extend the existing board definition or change definitions that have already been made. Sometimes it is also necessary to delete existing definitions. This can be done using __/delete-property/__. An example of this is shown in this hands-on guide. 


## Required Hardware/Software
- Development kit [nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.1.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Create a new project

1) Make a copy of the [Zephyr blinky project]([https://github.com/ChrisKurz/nRF-Connect-SDK-HandsOn/tree/main/Workspace/NCS/NCSv3.0.0/hello_world](https://docs.nordicsemi.com/bundle/ncs-latest/page/zephyr/samples/basic/blinky/README.html#blinky)).


### Build the project and check zephyr.dts

2) Add build configuration and build the project.

3) Check the defined aliases in the _zephyr.dts_ file. Please pay special attention to the alias __led3__.

   ![image](images/blinky_zephyr-dts.jpg)

> __Note:__ In a project, multiple files are often used for the definitions of the DeviceTree. Viewing these directly can sometimes make it difficult to understand which settings are ultimately used. During the build process, a _zephyr.dts_ file is therefore generated that contains the final settings of the DeviceTree. 


### Create an DeviceTree Overlay File and delete led3

4) Add a DeviceTree overlay file to your project.

5) The board definition files for the Nordic development kits define the available LEDs, like __led0__, __led1__, __led2__, and __led3__. Let's delete the definition of __led3__. 

   Therefore we will work with the LED device tree entry.

   <sup>__nrf54l15dk_nrf54l15_cpuapp.overlay__ </sup>

       / {
           aliases {
               /delete-property/ led3;
           };
       };

6) Do a pristine build.
7) Check the _zephyr.dts_ file.

   ![image](images/zpehyr-dts_delete.jpg)

  > __Note:__ As expected, the alias property __led3__ has been deleted and is no longer listed.
