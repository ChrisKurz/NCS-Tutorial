<sup>SDK version: NCS v2.3.0</sup>

# Getting started: Generating a License Report

## Introduction

At some point in your development process you will probably also be concerned about the different licenses of the software you are using. The _nRF Connect SDK_ provides a tool that allows you to browse the software modules you are using and it then generates a corresponding license report. 

Further details about licenses can be found [here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/introduction.html#licenses) and information about the _Software Bill of Materials_ tool can be found [here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/scripts/west_commands/sbom/README.html#). 


## Required Hardware/Software
- install the _nRF Connect SDK_ v2.3.0 and _Visual Studio Code_. The description of the installation can be found [here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/2.3.0/nrf/getting_started/assistant.html#).
- _Software Bill of Materials_ tool requires installation of additional Python packages. [Here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/scripts/west_commands/sbom/README.html#requirements) you find the installation desription.


## Step-by-step description 

### Ensure the needed software packages are installed on your computer

1) The _Software Bill of Materials_ tools requries additional Python packages. These has to be installed once. [Here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/nrf/scripts/west_commands/sbom/README.html#requirements) you find the installation desription.

2) You can check if the tool is installed by entering the following command in the command line. 

       ncs ncs-sbom -h
       
### First, build your Project

Before using the _Software Bill of Materials_ tool, you have to build the project that you would like to check. Build can be done in Visual Studio Code or in command line. Here I am showing how to do it the command line:

3) Go to the patch where your project is stored.

   ![image](images/sbom_ProjectPath.jpg)

4) Then build the project. 

   ![image](images/sbom_Build.jpg)
   
### Generate the License Report

5) And now you can run the _Software Bill of Materials_ tool by entering following command:

   ![image](images/sbom_sbom.jpg)
   
### License Report

6) The license report file _sbom_report.html_ is created in the project's folder _build_.

   ![image](images/sbom_ReportFile.jpg)

7) In our case the license report looks like this:

   ![image](images/sbom_Report.jpg)
 
