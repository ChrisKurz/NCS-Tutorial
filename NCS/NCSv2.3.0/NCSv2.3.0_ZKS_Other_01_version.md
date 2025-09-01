<sup>SDK version: NCS v2.3.0  -  Link to Hands-on solution: https://github.com/ChrisKurz/NCS-Tutorial/tree/main/Workspace/NCS/NCSv2.3.0/ZKS_Other_Version</sup>

# Zephyr Kernel Service: Other - Version

## Introduction

Sometimes it might be helpful to provide the application software with the information of the used Zephyr version. There are different ways in the _nRF Connect SDK_:
- using the Zephyr Kernel Service
- using the generated version.h header file

In this hands-on we will try both. 

## Required Hardware/Software
- one nRF52 development kit (e.g. nRF52DK, nRF52833DK, or nRF52840DK)
- install the _nRF Connect SDK_ v2.3.0 and _Visual Studio Code_. The description of the installation can be found [here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/2.3.0/nrf/getting_started/assistant.html#).

## Hands-on step-by-step description 

### Create a new Project

1) Make a copy of the "hello_world" project. Here is the link to this project: https://github.com/ChrisKurz/nRF_Connect_SDK/tree/main/Workspace/NCSv2.3.0/hello_world

### Add Zephyr Kernel Serivce function calls to get Zephyr Version

2) First, let's define a few variables for the version. Add following lines in __main.c__ file in _main()_ function:

	<sup>_src/main.c_ => main() function</sup>   
  
            uint32_t kernel_version;
            uint8_t  Version_Major;
            uint8_t  Version_Minor;
            uint8_t  Version_Patch;

3) Output the different parts of the version number. 

	<sup>_src/main.c_ => main() function</sup>   

            printk("USING ZEPHYR'S SYSTEM FUNCTIONS:\n");
            kernel_version=sys_kernel_version_get();
            Version_Major=SYS_KERNEL_VER_MAJOR(kernel_version);
            Version_Minor=SYS_KERNEL_VER_MINOR(kernel_version);
            Version_Patch=SYS_KERNEL_VER_PATCHLEVEL(kernel_version);
            printk("Zephyr Version: %d\n",kernel_version);
            printk("Zephyr Version - Major: %i\n",Version_Major);
            printk("Zephyr Version - Minor: %i\n",Version_Minor);
            printk("Zephyr Version - Patchlevel: %i\n",Version_Patch);
            printk("\n");

   _NOTE: This part does not need to include the version.h header file!_

### Add version.h header file to get Zephyr version numbers

And here is another way to use Zephyr Version numbers.

4) The version.h is a generated header file, which is created when a build is done. The generated header file can be found in the build folder ./build/zephyr/include/generated/version.h
   
   So we have to include this file by adding following instruction to main.c file:
   
	<sup>_src/main.c_</sup>   
   
       #include <version.h>   
   
5) Several symbols are defined in the version.h header file. The following lines use all these symbols:

	<sup>_src/main.c_ => main() function</sup>   

           printk("----------------------------------------------------------\n");
           printk("USING VERSION.H HEADER FILE:\n");
           printk("Zephyr Version Code: %d\n", ZEPHYR_VERSION_CODE);
           printk("Zephyr Kernel Version Major: %i\n", KERNEL_VERSION_MAJOR);
           printk("Zephyr Kernel Version Minor: %i\n", KERNEL_VERSION_MINOR);
           printk("Zephyr Kernel Version Patch-Level: %i\n", KERNEL_PATCHLEVEL);
           printk("Zephyr Kernel Version Sting: %s\n",KERNEL_VERSION_STRING);
           printk("Nordic Semiconductor's Zephyr build version: %s\n", STRINGIFY(BUILD_VERSION));

## Testing
6) Build the project and donwload it to your development kit. 
7) In the terminal you should see following outuput:

   ![image](images/ZKS_Other_01_version.jpg)
