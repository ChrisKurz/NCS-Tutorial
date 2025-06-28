<sup>SDK version: NCS v2.6.0  -  Link to Hands-on solution: https://github.com/ChrisKurz/NCS-Tutorial/tree/main/Workspace/NCS/NCSv2.6.0/hello_world</sup>

# Getting started: Creating a Project from Scratch

## Introduction

Creating a project from scratch is quite simple with Zephyr. Here is a description how to create the simplest version of a project. We use Visual Studio Code in this example.

## Required Hardware/Software
- Development kit [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk), or [nRF7002DK](https://www.nordicsemi.com/Products/Development-hardware/nRF7002-DK), nRF54H20PDK, nRF54L15PDK
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v2.6.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Create needed Folders and Files

1) First we create a __Workspace__ directory. This is where we will add all our projects. It is important that no spaces are used in the directory name and that the project directory paths are not too long, i.e. the Workspace should be close to the root directory. For example:   __C:/Nordic/Workspace__

2) Our first project is "Hello World". So we create a project folder __hello_world__ in our workspace directory:    __C:/Nordic/Workspace/hello_world__

    __NOTE: Folder name should start with a letter and there should be no spaces in the folder name!__

3) We need the following files in our project folder:

   ![image](images/01_ProjectFolder.jpg)

   __NOTE: You can create these files in Windows File Explorer as follow: open a folder, then click inside this folder with the right mouse button. In context menu select "New" and "Text Document". It is important that the file extension is also changed for some files! You have to enable the file name extensions in the Windows File Explorer menu "View" and ensure a tick is set at "File name extensions".__

4) Create the following three files in our project directory:

    _c:/Nordic/Workspace/hello_world/CMakeLists.txt_
    
       # SPDX-License-Identifier: Apache-2.0

       cmake_minimum_required(VERSION 3.21.0)

       # Find external Zephyr project, and load its settings
       find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

       # Set project name
       project (MyApp)

       # Add sources
       target_sources(app PRIVATE src/main.c)             

    _c:/Nordic/Workspace/hello_world/prj.conf_
    
       # This line is just a comment. In this simple project we can use the default configuration. 
       
    and create main.c in the subfolder _src_ ->
         _c:/Nordic/Workspace/hello_world/src/main.c_
    
       #include <zephyr/kernel.h>

       int main(void)
       {
            printk("Hello World!\n");

            return 0;
       }

   NOTE: In the __main.c__ file we use the _printk()_ instruction. To be able to use this function, we must insert the line __#include <zephyr/sys/printk.h>__. Please note that the header file __kernel.h__ also includes other header files, such as the __printk.h__ file. For this reason, we only include the __kernel.h__ file in the main.c file above.

## Testing

5) Start Visual Studio Code.

6) Ensure the toolchain version __v2.6.0__ and SDK version __v2.6.0__ is selected.

   ![image](images/01_SelectSDKversion-NCSv2.6.0.jpg)   

7) Click on "+ Open an existing application" and select the __hello_world__ folder. (our project folder is the folder in which the files __CMakeLists.txt__ and __prj.conf__ are located.)

   ![image](images/01_AddApplicationToWorkspace-NCSv2.6.0.jpg)

8) Before we can compile our project, we have to __add build configuration__. This is done by clicking the folder icon behind our project in the APPLICATIONS section. You can also click on the line "+ Create new build configuration" instead of clicking the icon.

   ![image](images/01_GenerateConfiguration-NCSv2.6.0.jpg)

9) In the __Board__ drop down list enter the board name of your development kit. When you enter the name you should see that the list will be filtered. 

   ![image](images/01_BuildConfiguration-NCSv2.6.0.jpg)

   __NOTE: Beside the developement kit name, the board name mentions also a chip name. This is done, because smaller devices may be emulated by using a development kit with a bigger devices. For example, the board name "nRF52840DK_nRF52811" shows that the nRF52840DK kit is used to emulate an nRF52811.__

10) Let's use the default settings for the rest. Click __Build Configuration__ button.

11) After the project build is completed, check all the available files in the hello_world folder.

   ![image](images/01_GeneratedFiles-NCSv2.5.2.jpg)

12) Ensure that the connected kit is found and click __Flash__ in the ACTIONS menu. The code download is downloaded to the kit. 

   ![image](images/01_Flash-2.jpg)

13) Open a terminal program, for example the _Serial Terminal_ that is available in _nRF Connect for Desktop_
 
    Settings: 115200 baud, 8 data bits, 1 stop bit, no parity, no flow control
    
    __NOTE: These are the default settings of _Serial Terminal_ program that is available in _nRF Connect for Desktop_.__

15) Reset the kit. The Zephyr boot message and "Hello World" string is shown in the terminal. 

   ![image](images/01_NrfTerminal-NCSv2.6.0.jpg)
