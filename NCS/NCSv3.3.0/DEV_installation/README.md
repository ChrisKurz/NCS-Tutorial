# Getting started: _nRF Connect SDK_ V3.3.0 Installation

## Introduction

This description covers to installation process of the _nRF Connect SDK_, its toolchain, and Visual Studio Code. 

## Installation: A Step-by-Step Description 

### 1) Install SEGGER J-Link v8.76
   
   > Download the installer for your platform from [SEGGER J-Link Software](https://www.segger.com/downloads/jlink/#J-LinkSoftwareAndDocumentationPack). Run the installer; when you reach the ‘Choose Optional Components’ window during installation, be sure to select ‘Install Legacy USB Driver for J-Link’ This driver is necessary for some supported Development Kits.
   >
   > ![image](images/jlink_v8.76.jpg)   
      
### 2) Install Visual Studio Code

> Go to [https://code.visualstudio.com/download](https://code.visualstudio.com/download) and install the version that matches your operating system.

### 3) Install _nRF Connect Extension Pack_ in Visual Studio Code

> In the __Activity Bar__, click the __Extensions__ icon, then type __nRF Connect for VS Code Extension Pack__ in the search field, and click on __Install__.

### 4) Install Toolchain in Visual Studio Code

> The first time you open nRF Connect for VS Code, it will prompt you to install a toolchain. This usually happens when the extension does not find any installed toolchain on your machine.
>
> Click on __Install Toolchain__. It will list the available versions of toolchains that can be downloaded and installed on your machine. Select the toolchain version that matches the nRF Connect SDK version you plan to use. We always recommend using the latest tagged version of the nRF Connect SDK.

### 5) Install _nRF Connect SDK_ in Visual Studio Code

> In nRF Connect for VS Code, click on __Manage SDKs__. Click on __Install SDK__. It will list the available versions of the nRF Connect SDK that can be downloaded and installed on your machine. Choose the nRF Connect SDK version you wish to use for your project development.


-----
## Optional Installations:

### 6) Install _nrfutil_ and the _nrfutil device_ command

nRF Util is a modular, unified command line utility for managing Nordic Semiconductor devices and supporting automation. Here's what it's good for:
- _Device programming_ – Flash firmware onto Nordic devices (DKs, dongles, Thingies, custom boards) via J-Link, MCUboot serial recovery, or nRF9160 modem upgrade
- _Device operations_ – List, erase, recover, reset, and perform various operations on connected Nordic devices 
- _nRF5 SDK support_ – DFU package generation, cryptographic key management, bootloader settings generation, and DFU over Bluetooth LE, UART, USB, Thread, and Zigbee via the nrf5sdk-tools command 
- _Toolchain management_ – Manage nRF Connect SDK toolchain versions via the sdk-manager command
- _Automation & scripting_ – Supports JSON output for scripting and CI/CD pipelines

When you install the Nordic _Visual Studio Code Extensions_ or _nRF Connect for Desktop_, nrfutil is installed as well. However, it can only be accessed within _Visual Studio Code_ or _nRF Connect for Desktop_. To gain general access to the tool, it must be installed on your computer. 
#### 6.1) Install _nrfutil_
##### 6.1.1) Download nrfutil
   > Download the binary compatible with your OS from the [nRF Util product page](https://www.nordicsemi.com/Products/Development-tools/nRF-Util/Download?lang=en#infotabs) and store it somewhere on your disk drive (For example C:\nordic_tools\nrfutil.exe for Windows).
   >
   > If you are running on macOS or Linux, you can store it in a folder that is already added in the system’s PATH (E.g. /usr/bin/ ), so that you can skip step 2.2
   >
   >  __NOTE:__ For Linux, keep in mind that nrfutil has some prerequisites that are listed in Installing [nRF Util prerequisites](https://docs.nordicsemi.com/bundle/nrfutil/page/guides/installing.html#prerequisites). Make sure you also download them, if you don’t have them on your machine already.
 
##### 6.1.2.) Update Systems's PATH

   > (Windows) Update your system’s PATH to include the location where nrfutil is stored. Open Edit environment variable for your account and add the path where you stored the nrfutil binary, as shown below:
   >
   > ![image](images/update_PATH.gif)

##### 6.1.3) Ensure the latest nrfutil Version is installed

   > To make sure we have the latest nrfutil version, run the following command in a terminal (Command Prompt or PowerShell). It doesn’t matter which terminal since nrfutil is set globally in step 2.1.2.

    nrfutil self-upgrade



 #### 6.2) Install _nrfutil device_ command
   > The nrfutil binary you just downloaded does not come with any pre-installed commands. In this step, we will upgrade the core nrfutil and download the device command.
   >
   > For this course, we will need the device command to flash binaries to development kits.
   >
   > In your active terminal, type:

    nrfutil install device
