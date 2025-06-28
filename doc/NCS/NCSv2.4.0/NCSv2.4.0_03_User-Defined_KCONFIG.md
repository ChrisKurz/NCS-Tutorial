<sup>SDK version: NCS v2.4.0  -  Link to Hands-on solution: https://github.com/ChrisKurz/NCS-Tutorial/tree/main/Workspace/NCS/NCSv2.4.0/03_UserDefinedKconfig</sup>


# Defining own KCONFIG symbols

## Introduction

_NOTE: You should do first the [Zephyr Logging](https://github.com/ChrisKurz/nRF_Connect_SDK/blob/main/doc/NCSv2.4.0_02_ZephyrLogging.md) hands-on before doing this course._

We had looked at using Zephyr Logging. We had seen there how debug messages could be sent during runtime. We talked about how the logger can be activated and the log level can be set. These settings - logging activation and log level selection - were made in the C source file. However, it would also be interesting to make these settings in the prj.conf file via user-defined KCONFIG switches. 

This is exactly what we will look at in this chapter. 

## Required Hardware/Software for Hands-on
- one nRF52 development kit (e.g. nRF52DK, nRF52833DK, or nRF52840DK)
- install the _nRF Connect SDK_ v2.4.0 and _Visual Studio Code_. The description of the installation can be found [here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/2.4.0/nrf/getting_started/assistant.html#).

## Hands-on step-by-step description 

### Create a new Project

1) Make a copy of the "Zephyr Logging" project. Here is the link to this project: https://github.com/ChrisKurz/nRF_Connect_SDK/tree/main/Workspace/NCSv2.4.0/02_Logging

### Define new CONFIG symbols

2) We want to define own CONIFG symbols. These symbols are:

     _CONFIG_MYAPP_LOG_ENABLE_: 
     This should be a boolean, that activates or deactivates logging. 
     
     _CONFIG_MYAPP_LOG_LEVEL_: 
     You have already seen that the Zephyr Logging allows to define different Log Levels. This user defined symbol is used to allow setting the log level. 

     Defining of these symbols is done in a __kconfig.__ (blank extension in Windows! Do not enter the "." in Linux) file. So let's add the following kconfig. file to our project folder:

     <sup>_kconfig._</sup>
  
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
       #CONFIG_MYAPP_LOG_LEVEL_INF=y
       #CONFIG_MYAPP_LOG_LEVEL_DBG=y
       
Note: prj.conf lines that start with # are comments only! To use one of these CONFIG settings remove the "#". 

## Testing

5) Build the project and download to an nRF52 development kit (e.g. nRF52840-DK).

6) Check the output sent via virtual COM port. 

7) Open also "KCONFIG" tool in Visual Studio Code and test the CONFIG settings. 
