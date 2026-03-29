<sup>SDK version: NCS v3.2.0 </sup>

# MCUboot's Swap Type "Test"

## Introduction

At startup, MCUboot checks the contents of the flash memory to determine which of these “swap types” should be executed for the current image. This decision then determines the subsequent sequence of events.

The possible swap types, and their meanings, are:
- BOOT_SWAP_TYPE_NONE: The “usual” or “no upgrade” case; attempt to boot the contents of the primary slot.
- BOOT_SWAP_TYPE_TEST: Boot the contents of the secondary slot by swapping images. Unless the swap is made permanent, revert back on the next boot.
- BOOT_SWAP_TYPE_PERM: Permanently swap images, and boot the upgraded image firmware.
- BOOT_SWAP_TYPE_REVERT: A previous test swap was not made permanent; swap back to the old image whose data are now in the secondary slot. If the old image marks itself “OK” when it boots, the next boot will have swap type BOOT_SWAP_TYPE_NONE.
- BOOT_SWAP_TYPE_FAIL: Swap failed because image to be run is not valid.
- BOOT_SWAP_TYPE_PANIC: Swapping encountered an unrecoverable error.

In this hands-on we take a closer look at swap type "permanent". 


## Required Hardware/Software

- Development kit
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK),
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK),
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 

- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Original Application Image

1) Let's use the previous project as the original application image. The Intel Hex file of previous project can be downloaded [here](Intel_Hex_Files/AppImage_merged.hex).

   > __Note:__ This image is the one we prepared in the hands-on [Defining an Appication Image Version](../mcuboot_ApplikationImageVersion/README.md).


### Update Image

#### Copy previous project

2) Copy the previous project and rename it. 

   > __Note:__ Do not use "mcuboot" as your project folder name here! 

   Use the same Build Configuration as in previous project.

#### Update Version and output in main function

3) Update VERSION file:

    <sup>VERSION</sup>   

        VERSION_MAJOR = 6
        VERSION_MINOR = 7
        PATCHLEVEL = 8
        VERSION_TWEAK = 9
        EXTRAVERSION = test-2

4) And change output string "Image: MCUboot1" to the following:

   <sup>_src/main.c_ => main() function</sup>

       printf("Image: MCUboot2 \n");

5) Finally, we need to ensure that this image is marked as "permanent". To do this, we must set the status to "confirmed". The easiest way to do this is to use the corresponding KCONFIG symbol.

   <sup>prj.conf</sup>

       CONFIG_MCUBOOT_GENERATE_CONFIRMED_IMAGE=y

6) Now build the project.

### Update Intel Hex file to place Update Image in slot 1

7) The build has generated the file __zephyr.signed.confirmed.hex__. 

   <sup>ommand line instruction</sup>

       arm-zephyr-eabi-objcopy --change-addresses 0xA6000 zephyr.signed.confirmed.hex zephyr.signed.confirmed.moved.hex



## Testing

5) Start "Programmer" in nRF Connect for Desktop. 

6) Connect to your development kit. 

7) Click "Add File" and select the original Application Image file [AppImage_merged.hex](Intel_Hex_Files/AppImage_merged.hex).

8) In the Programmer you should see two blocks:

   ![missing image](images/Programmer_AppImage.jpg)

9) Click "Erase & Write" button.
10) You should see in the Serial Terminal that first MCUboot starts and then the application image is executed.

   ![image](images/Terminal_AppImage.jpg)










11) Let's add the update Image in the programmer. Click "Add File" and select in your project folder /build/<_project folder name_>/zephyr/zephyr.hex file. 

=> VS code does not generate intel hex file that is placed in upper memory... => can imgtool be used to generate a address corrected file?


   use following command line instruction to change the start address of the intel hex file image. 

    arm-none-eabi-objcopy --change-addresses <offset> input.hex output.hex

    <offset> =   0x10000

    if in the input.hex file the start address is 0x080000000 then the start address in output.hex is 0x08010000

    note that the <offset> can also be negative.









8) In the Programmer you should see two blocks:

   ![missing image](images/Programmer.jpg)

&nbsp;  The orange block at the bottom is the bootloader image. It is located at address 0x0000. Starting at address 0xC000 you find the green block, which is the _hello world_ application image. 

9) In the Programmer tool click "Earse all" and afterwards "Erase & write".

10) When programming is completed, check the Terminal output. In case nothing is shown in the terminal, press the RESET button on the development kit.

  ![missing image](images/Terminal.jpg)
  
__Note__: The application is printing just once after a reset. So you have to press the Reset button on the development kit to see the output in the terminal window.

