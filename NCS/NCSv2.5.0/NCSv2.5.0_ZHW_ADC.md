<sup>SDK version: NCS v2.5.0  -  Link to Hands-on solution: https://github.com/ChrisKurz/nRF_Connect_SDK/tree/main/Workspace/NCSv2.5.0/ZHW_ADC</sup>

# Zephyr Hardware Driver: ADC

## Introduction

This exercise demonstrates the use of the Zephyr hardware ADC driver. Note that the functionality covered by this driver is limited to basic ADC functions. If advanced ADC functions supported by the peripheral module on the device are required, the Nordic Semiconductor ADC drivers available in the nrfx library should be used.

## Required Hardware/Software for Hands-on
- one nRF52 development kit (e.g. nRF52DK, nRF52833DK, or nRF52840DK)
- install the _nRF Connect SDK_ v2.5.0 and _Visual Studio Code_. The description of the installation can be found [here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/2.5.0/nrf/getting_started/assistant.html#).

## Hands-on step-by-step description 

### Create a new Project

1) Create a new project based on [_Creating a Project from Scracth_ exercise](https://github.com/ChrisKurz/nRF_Connect_SDK/blob/main/doc/NCSv2.5.0_01_ProjectFromScratch.md). 


### Add needed Software Module

2) Now we add the Zephyr ADC hardware driver to our project. Add following lines to the _prj.conf_ file:

	<sup>_prj.conf_</sup>

       # Enable Zephyr ADC Hardware driver
       CONFIG_ADC=y


3) In order to use the ADC hardware driver API we also need to add the corresponding header file to our _main.c_ file:

	<sup>_src/main.c_</sup>

       #include <zephyr/drivers/adc.h>

### Adding DeviceTree overlay file for ADC

The ADC peripheral and pinmux is configured in the DeviceTree file. Following definitions have to be added there:

- enabling of ADC by setting _status="okay";_. 
- ADC channels specified in the _io_channels_ property of the _zephyr,user_ node
- configuration of channels (settings like gain, reference, or acquisition time)
- ADC resolution
- oversampling settings (if used)

Let's prepare a DeviceTree overlay file with these settings:

4) Create an overlay file. (e.g. __nrf52840DK_nrf52840.overlay__)

5) Now add the _io_channels_ property in this file. Here we define to use one ADC peripheral (instance) and we define a channel sequence with different configurations.

	<sup>_nrf52840DK_nrf52840.overlay_</sup>

       / {
              zephyr,user {
                      io-channels = <&adc 0>, 
                                    <&adc 1>, 
                                    <&adc 7>;
              };
       };

       &adc {
              #address-cells = <1>;
              #size-cells = <0>;
   
              channel@0 {
                      reg = <0>;
		
	            };

              channel@1 {
                      reg = <1>;
              };

              channel@7 {
                      reg = <7>;
              };
       };

7) Let's add the configuration for channel 0. Add follwing lines to  __channel@0__:
   
	<sup>_nrf52840DK_nrf52840.overlay_ => add to __channel@0__ property</sup>

                      zephyr,gain = "ADC_GAIN_1_6";
                      zephyr,reference = "ADC_REF_INTERNAL";
                      zephyr,acquisition-time = <ADC_ACQ_TIME_DEFAULT>;
                      zephyr,input-positive = <NRF_SAADC_AIN1>; /* P0.03 */
                      zephyr,resolution = <12>;

8) Now, add the configuration for channel 1.

  <sup>_nrf52840DK_nrf52840.overlay_ => add to __channel@1__ property</sup>

                      zephyr,gain = "ADC_GAIN_1_6";
                      zephyr,reference = "ADC_REF_INTERNAL";
                      zephyr,acquisition-time = <ADC_ACQ_TIME_DEFAULT>;
                      zephyr,input-positive = <NRF_SAADC_VDD>;
                      zephyr,resolution = <14>;
                      zephyr,oversampling = <8>;

8) And finally add the configuration for channel 7:

  <sup>_nrf52840DK_nrf52840.overlay_ => add to __channel@7__ property</sup>

                      zephyr,gain = "ADC_GAIN_1_5";
                      zephyr,reference = "ADC_REF_VDD_1_4";
                      zephyr,vref-mv = <750>;
                      zephyr,acquisition-time = <ADC_ACQ_TIME_DEFAULT>;
                      zephyr,input-positive = <NRF_SAADC_AIN6>; /* P0.30 */
                      zephyr,input-negative = <NRF_SAADC_AIN7>; /* P0.31 */
                      zephyr,resolution = <12>;


So your DeviceTree overlay file should now look like this:

[image](images/ZHW_ADC_overlayFile.jpg)


### Including DeviceTree Configuration in C source code

9) First, include the devicetree header file into your project.

	<sup>_src/main.c_</sup>

       #include <zephyr/devicetree.h>


10) Let's add a check to test if an appropriate overlay file was added to the project. This is just for debug purpose and helps to identify a missing DeviceTree overlay file.

	<sup>_src/main.c_</sup>

        #if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
            !DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
        #error "No suitable devicetree overlay specified"
        #endif

11) We use a structure in our main file to store the ADC settings. We read these settings from the DeviveTree overlay file.

	<sup>_src/main.c_</sup>

        /* Data of ADC io-channels specified in devicetree. */
        static const struct adc_dt_spec adc_channels[] = {
                                         DT_FOREACH_PROP_ELEM(
                                                 DT_PATH(zephyr_user), 
                                                 io_channels,
                                                 ADC_DT_SPEC_GET_BY_IDX(node_id, idx),
                                         )
        };


13) 

