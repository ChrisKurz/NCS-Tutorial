<sup>SDK version: NCS v3.0.0  -  Link to Hands-on solution: https://github.com/ChrisKurz/NCS-Tutorial/tree/main/Workspace/NCS/NCSv3.0.0/logging_kconfig</sup>


# Defining own KCONFIG symbols

## Introduction

> _NOTE: You should do first the [Zephyr Logging](https://github.com/ChrisKurz/NCS-Tutorial/blob/main/NCS/NCSv3.0.0/ZOS_logging.md) hands-on before doing this course._

We had looked at the use of _Zephyr Logging_. There we had seen how debug messages can be sent during runtime. We talked about how to activate the logging and set the log level. These settings, logging activation and log level selection, were made in the C source file. However, it would also be interesting to make these settings in the __prj.conf__ file via user-defined KCONFIG symbols. 

This is exactly what we will look at on this page. 

## Required Hardware/Software
- Development kit [nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.0.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Create a new Project

1) Make a copy of the [Zephyr Logging](https://github.com/ChrisKurz/NCS-Tutorial/tree/main/Workspace/NCS/NCSv3.0.0/logging) project. Store the new project in your workspace folder, e.g. __C:/Nordic/Workspace/logging_kconfig__

2) Start _Visual Studio Code_ and open the project.


### Define new CONFIG symbols

3) We want to define own CONIFG symbols. These symbols are:

     _CONFIG_MYAPP_LOG_ENABLE_: 
     This should be a boolean, that activates or deactivates logging. 
     
     _CONFIG_MYAPP_LOG_LEVEL_: 
     You have already seen that the Zephyr Logging allows to define different Log Levels. This user defined symbol is used to allow setting the log level. 

     Defining of these symbols is done in a __Kconfig.__ (blank extension in Windows! Use __Kconfig__ in Linux and do not enter the "." in Linux) file. So let's add the following file to our project folder:

     <sup>_Kconfig._</sup>
  
       # MyApp configuration
       menu "MyApp Settings"
          menu "Logging"
             config MYAPP_LOG_ENABLED
  	            bool "Enable MyApp Logging"
	            default y

             module = MYAPP
             module-str = MyApp sample
             source "${ZEPHYR_BASE}/subsys/logging/Kconfig.template.log_config"
          endmenu
       endmenu

       menu "Zephyr Kernel"
         source "Kconfig.zephyr"
       endmenu

3) Now let us use these new symbols. In our main.c file we have to replace the LOG_MODULE_REGISTER instruction by following lines:
   
	<sup>_src/main.c_</sup>   
   
       /*
        * The following CONFIGs from prj.conf control the log messages:
        * - CONFIG_MYAPP_LOG_ENABLED 
        *          0: logging messages are disabled. Use Log_Level None
        *          1: logging messages are enabled
        * - CONFIG_MYAPP_LOG_LEVEL 
        *          severity level of the logging messages that are to be output
        */
       #if IS_ENABLED(CONFIG_MYAPP_LOG_ENABLED) 
           #define LOG_LEVEL CONFIG_MYAPP_LOG_LEVEL
       #else
           #define LOG_LEVEL 0
       #endif
       LOG_MODULE_REGISTER(MyApp, LOG_LEVEL);
       
4) Now we can define the application logging in the prj.conf file by setting the new CONFIG sympbols. 

   _prj.conf_

       # MyApp Logging settings
       CONFIG_MYAPP_LOG_ENABLED=y
       #CONFIG_MYAPP_LOG_LEVEL_ERR=y
       #CONFIG_MYAPP_LOG_LEVEL_WRN=y
       CONFIG_MYAPP_LOG_LEVEL_INF=y
       #CONFIG_MYAPP_LOG_LEVEL_DBG=y
       
   > **_Note:_** prj.conf lines that start with # are comments only! Only one of the __CONFIG_MYAPP_LOG_LEVEL__ should be used at a time.

## Testing

5) Build the project and download to a development kit.

6) Check the logging output in a terminal program, e.g. _Serial Terminal_. 

7) Open also __nRF KCONFIG GUI__ or __GUICONFIG__ tool in _Visual Studio Code_ and check the CONFIG settings.
