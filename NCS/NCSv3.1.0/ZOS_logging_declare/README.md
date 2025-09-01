<sup>SDK version: NCS v3.1.0 </sup>

# Zephyr Logging - In Case the Software Module consists of multiple Files

## Introduction

In order to use logging in the module, a unique name of a module must be specified and module must be registered using LOG_MODULE_REGISTER. We have used this in the [previous hands-on](ZOS_logging.md). 

If the module consists of multiple files, then LOG_MODULE_REGISTER() should appear in exactly one of them. Each other file should use LOG_MODULE_DECLARE to declare its membership in the module. This case is described in the hands-on on this page.


## Required Hardware/Software for Hands-on
- Development kit [nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.1.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Copy Zephyr Logging Project

1) Let's make a copy of the previous zephyr Logging hands-on project. The previous project can also be found [here](https://github.com/ChrisKurz/NCS-Tutorial/tree/main/Workspace/NCS/NCSv3.0.0/logging). 


### Add another C File to the project

2) Let's add another C file to your project. So in src folder add the file _functions.c_. 

3) We have to include this file via the CMakeLists.txt file. So add the _src/function.c_ file name to the target_source list. The CMakeLists.txt file should then look like this:

   ![image](images/ZOS_logging_declare/CMakeLists.jpg)

4) The function.c is still blank. Let's add some dummy code.

   <sup>__src/function.c__</sup>
   
       #include <zephyr/kernel.h>
       
       void function(void) {
          printk("function is called!\n");   
   
       }

5) We have to declare the new, extern function im main.c file. 

   <sup>__src/main.c__</sup>
   
       extern void function(void);

6) And we should call the new function in main() function.

   <sup>__src/main.c__ => main() function</sup>

           function();


### Include the New Function File in our Module and use the same Zephyr Logging Registration 
   
7) To show that the new function belongs to the same software module as our file where Zephyr Logging has already been registered, a Logging declaration is added to the new file. We do this by inserting the following lines into our new function.c file.

   <sup>__src/function.c__</sup>

       #include <zephyr/logging/log.h>
       
       LOG_MODULE_DECLARE(MyApp, LOG_LEVEL_DBG);

   __NOTE__: We have to use the same software module name in the LOG_MODULE_DECLARE() macro. So in our main.c function we used "MyApp" when the LOG_MODULE_REGISTRATION was done. The second parameter in the LOG_MODULE_DECLARE macro is the log level. Default log level (CONFIG_LOG_DEFAULT_LEVEL) is used if custom log level is not provided. In our example we have set the log level for the function.c file to LOG_LEVEL_DBG. Note that it can be different than the definition in the main.c file.

8) To test if the Logging now works in the new file we will simply add some log output to the function.

   <sup>__src/function.c__</sup>

           LOG_INF("2-This is a test");
           LOG_ERR("2-ERROR: test");
           LOG_WRN("2-WARNING: test");
           LOG_DBG("2-DEBUG: test");



## Testing

9) Build and flash the project to your development kit. 

10) Use a terminal program on your computer and check the output. Note that some lines are printed after a reset. So you may press the RESET button to see it. 

   ![image](images/ZOS_logging_declare/Terminal.jpg)

   What you can see here is that the same "MyApp" software module is used here as output module and that the log level of the new C file is set differently than in the main file.
   
