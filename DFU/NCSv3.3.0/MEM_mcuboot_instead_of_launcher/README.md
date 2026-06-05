# !!! WORK IN PROGRESS !!!
-----
# Memory Partitions:  Replace Launcher with MCUboot

## Introduction

In the [previous hands-on session](../MEM_move_start_address/README.md), we defined our own memory partition and launched the actual project using a launcher app. Here, we will now replace the launcher with MCUboot.
 
> __Important Notes:__
>
> - The definition in the DeviceTree file depends on the MCU family being used. Here, we will focus on the nRF54L series.
> 
> - In the _nRF Connect SDK_, the Partition Manager has been marked as deprecated. The recommended approach for defining a memory partition is now via a Zephyr DTS file. In this hands-on, we will work exclusively with Zephyr DTS.


## Required Hardware/Software

- Development kit
[nRF54LM20DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54LM20-DK),
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK),

- install the _nRF Connect SDK_ v3.3.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Copy the <code>hello_world_10000</code> app from previous hands-on

1) Let's start with the [previous project](../MEM_move_start_address/hello_world_10000). Make a copy and add following build configuration. 

   > __Build Configuration__:
   >
   > _Board Target:_ nrf54l15dk/nrf54l15/cpuapp
   >
   > _System build (sysbuild)_: Use sysbuild

### Add MCUboot
   
2) Add MCUboot.

   <sup>_sysbuild.conf_</sup>

       # Add MCUboot to the project
       SB_CONFIG_BOOTLOADER_MCUBOOT=y

### DeviceTree Overlay File

Let's use a common memory partition definition for the application and MCUboot. 

3) Create a new folder and add the file <code>nrf54l15dk_nrf54l15_cpuapp_memory_partition.dtsi</code> file. We just copy the previous overlay file.

   <sup>_../common/nrf541l5dk_nrf54l15_cpuapp_memory_partition.dtsi_</sup>

       / {
          chosen {
              zephyr,code-partition = &app_slot;
          };
       };

       &cpuapp_rram {

           partitions {
               compatible = "fixed-partitions";
               #address-cells = <1>;
               #size-cells = <1>;

               app_slot: partition@10000 {
                   label = "app_slot";
                   reg = <0x00010000 0x00070000>;
               };
           };
       };

> __Note:__ Lateron we will do some changes in this file. 

4) The original DeviceTree overlay file will just link to the new DTSI file.

   <sup>_boards/nrf54l15dk_nrf54l15_cpuapp.overlay_</sup>

       #include "../common/nrf54l15dk_nrf54l15_cpuapp_memory_partition.dtsi"
   

### ...

    
## Testing

x) abc

  ![image](images/programmer.jpg)

