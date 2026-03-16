# Bootloader and Device Firmware Updates (DFU)

A firmware update consists of several steps. First, an update image must be loaded into the MCU. Once this is complete, the image can be verified and, if necessary, applied. 

Here, we will first look at the bootloader — specifically MCUboot. For now, we will skip downloading the image via software and use the _Programmer_ tool from _nRF Connect for Desktop_ instead. Later, we will add the software that handles the firmware update (see DFU chapter). 


## MCUboot

1) [Adding MCUboot to a project](mcuboot_AddToProject/README.md)

[Create Update Image that uses Swap Type "Permanent"]()

[Using on Signature Key for Application Image]()

[Using External Flash]()

[Image Encryption]()

[Downgrade prevention]()

[Swap with Scratch ???]()


## Device Firmware Update (DFU) 

The firmware update image is typically downloaded by the application. This is particularly useful for applications that use a wireless stack. This way, the wireless stack does not need to be included a second time in the MCUBoot project, thereby avoiding wasted memory. However, there are exceptions. For example, MCUBoot offers a serial recovery feature that allows MCUBoot to download upgrade images via serial interfaces. 

Here, we'll take a look at both this serial recovery solution and a few solutions via the application.

### DFU handled within MCUboot (Serial Recovery)

1) [Adding Serial Recovery via UART](mcuboot_SerialRecoveryUART/README.md) to previous project

### DFU handled by application firmware

