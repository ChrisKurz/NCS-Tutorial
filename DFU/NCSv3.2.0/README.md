# Bootloader and Device Firmware Updates (DFU)

A firmware update consists of several steps. First, an update image must be loaded into the MCU. Once this is complete, the image can be checked and, if verified as correct, used as the new application image. 


## MCUboot

Here, we will first look at the bootloader — specifically MCUboot. For now, we will skip downloading the image via the application firmware and use the _Programmer_ tool from _nRF Connect for Desktop_ instead. Later, we will add the software that handles the firmware update (see DFU chapter). 

1) [Adding MCUboot to a project](mcuboot_AddToProject/README.md)

2) [Defining an Appication Image Version](mcuboot_ApplikationImageVersion/README.md)

3) [Create Update Image that uses Swap Type "Permanent"](mcuboot_SwapType_perm/README.md) - creating a confirmed update image.


## Device Firmware Update (DFU) 

The firmware update image is typically downloaded by the application. This is particularly useful for applications that use a wireless stack. This way, the wireless stack does not need to be included a second time in the MCUBoot project, thereby avoiding wasted memory. However, there are exceptions. For example, MCUBoot offers a serial recovery feature that allows MCUBoot to download upgrade images via serial interfaces. 


### DFU handled within MCUboot (Serial Recovery)

In this chapter, we will look at the solution for serial recovery.

1) [Adding Serial Recovery via UART](mcuboot_SerialRecoveryUART/README.md) to previous project

### DFU handled by application firmware

Here, we'll look at some examples of how to download the update image from the application firmware.
