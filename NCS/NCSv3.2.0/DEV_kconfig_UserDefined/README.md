<sup>SDK version: NCS v3.2.0</sup>


# Defining own KCONFIG symbols

## Introduction

In Zephyr RTOS, KCONFIG is used to add software modules to a project and to configure these software modules accordingly. It is of course also possible to create your own KCONFIG symbols and use them in the code. This example shows how this is done.


## Required Hardware/Software
- Development kit 
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Create a new Project

1) Create a new project based on the Zephyr example __hello_world_ (./zephyr/samples/hello_world). Name this project for example __C:/Nordic/Workspace/kconfig__

### Define new CONFIG symbols

2) In this example, we want to add a software module to the project via the CONFIG symbol __CONFIG_MYFUNC__. If this software module is added, we can define a name for it using another CONFIGsymbol (__CONFIG_MYFUNC_NAME__). __CONFIG_MXFUNC_NAME__ should only be usable if __CONFIG_MYFUNC__ has also been activated (CONFIG_myFunc=y). So there is a dependency for __CONFIG_MYFUNC_NAME__.

   Let's define these two CONIFG symbols. These symbols are:

     _CONFIG_MYFUNC_: 
     This should be a boolean, that activates or deactivates the user-defined software module. 
     
     _CONFIG_MYFUNC_NAME_: 
     This symbol defines a string, which is output on a terminal program.  

     Defining of these symbols is done in a __Kconfig.__ (blank extension in Windows! Use __Kconfig__ in Linux and do not enter the "." in Linux) file. So let's add the following file to our project folder:

     <sup>_Kconfig._</sup>
  
       # MyApp configuration
       menu "MyApp Settings"
          config MYFUNC
  	            bool "Enable MyFunc software module"
	            default y
                    help 
                        Include the user-defined software
   
          config MYFUNC_NAME
                string "Name of my function."
               default "name is not defined"
               depends on MYFUNC
               help 
                   Name of the user-defined software.
       endmenu

       menu "Zephyr Kernel"
         source "Kconfig.zephyr"
       endmenu

4) Now let us use these new symbols. In our main.c file we include the my_func() function only if it is enabled via __CONFIG_MYFUNC__.

     <sup>_main.c_</sup>

       #include <zephyr/kernel.h>

       #if IS_ENABLED(CONFIG_MYFUNC)
       void my_func(void){
	         printf("My function is included in the build\n");
	         printf("its name is: %s\n", CONFIG_MYFUNC_NAME);
       }
       #endif

    > __NOTE:__  We have to include _zephyr/kernel.h_, which allows us to use _IS_ENABLED()_ macro. 

5) And in main function we call __my_func()__ when it is enabled. Add these lines:

     <sup>_main.c_ => main() function</sup>
     
       #if IS_ENABLED(CONFIG_MYFUNC)
           my_func();
       #endif

## Testing

5) Build the project and download it to a development kit. You should see that the my_func() specific printf() strings are shown in a serial terminal. The reason why this is already displayed is the default settings that we have defined.
       
6) Now let's change these settings by adding following lines in prj.conf file:

   _prj.conf_

       # MyApp settings
       CONFIG_MYFUNC=n
       
   > **_Note:_** prj.conf lines that start with # are comments only!


7) Build the project and download to a development kit. Check the serial terminal output. This time the my_func() specific printf strings are not shown in the terminal, because we have removed this software part from the build by setting CONFIG_MYFUNC=n.

8) Use following settings in prj.conf file. And check the output strings with these settings. 

       # MyApp settings
       CONFIG_MYFUNC=y
       CONFIG_MYFUNC_NAME="My Board"

9) Open the "nRF KCONFIG GUI Tool" and check the KCONFIG settings.
