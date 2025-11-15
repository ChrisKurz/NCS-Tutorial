<sup>SDK version: NCS v2.3.0 - Link to Hands-on solution: [MCUboot2_confirm](https://github.com/ChrisKurz/MCUboot/tree/main/Workspace/NCSv2.3.0/01a_MCUboot2_confirm)</sup>

# MCUboot Hands-on:  Create Image that uses Swap Type "Permanent"

## Introduction

In the previous hands-on we saw that the default setting when generating an upgrade image uses the swap type "test". This is ideal if you want the application to run tests after an image swap and then decide whether to keep the new image or go back to the old image. 

It is of course also possible to create an upgrade image that uses the swap type "permanent". This hands-on shows how to do it.

## Required Hardware/Software for Hands-on
- one nRF52 development kit (e.g. nRF52DK, nRF52833DK, or nRF52840DK)
- install the _nRF Connect SDK_ v2.3.0 and _Visual Studio Code_. The description of the installation can be found [here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/2.3.0/nrf/getting_started/assistant.html#).

## Hands-on step-by-step description 

### Create new project

1) Copy the [MCUboot2](https://github.com/ChrisKurz/MCUboot/tree/main/Workspace/NCSv2.5.0/01_MCUboot2) project (e.g. name of new project: "MCUboot2_confirm")

2) add the following line to main function:

	<sup>_src/main.c_ => main() function</sup>

           printk("Image: MCUboot2 (confirmed) \n");

3) Open KCONFIG tool and look for the "Extra arguments to pass to imgtool" KCONFIG symbol. Enter "--confirm" in its text box.

   ![image](images/H01a_ImgtoolConfirm.jpg)
   
   _NOTE:_ CONFIG_MCUBOOT_EXTRA_IMGTOOL_ARGS allows us to pass further arguments when the build process uses the imgtool. We can either enter here "--confirm" and press "Save" button and do only Builds. Important to know is that a "pristine build" would erase this setting! If this KCONFIG symbol should permanently be set then add following line to the prj.conf file:
   
	<sup>_prj.conf_</sup>
	
       # Confirm the upgrade image. This causes to use swap type "permanent"
       CONFIG_MCUBOOT_EXTRA_IMGTOOL_ARGS="--confirm"
   
4) Build the project.     

5) Let's use the __Programmer__ tool within __nRF Connect for Desktop_ and add the MCUboot1 _[merged.hex](https://github.com/ChrisKurz/MCUboot/tree/main/Workspace/NCSv2.3.0/01_MCUboot2)_ image and the image from this hands-on.

6) Ensure the Terminal program is running on your computer.

7) In the __Programmer__ tool click the "Erase & Write" button.
8) Now check the Terminal window. Especially take a look to "Swap type".

   ![image](images/H01a_terminal_start.jpg)

  Note that the swap type now shows "perm". This means that a permanet swap was done. 
  
9) Press again RESET button on your development kit.
  
   ![image](images/H01a_terminal_reset.jpg)  
  
   Any furhter RESETs will not cause another swap, except a new upgrade image was downloaded.
