<sup>SDK version: NCS v3.2.0 </sup>

# Zephyr Device Driver: Adding simulated Sensor Driver

The Zephyr RTOS includes a wide range of drivers. In this practical exercise, we will take a closer look at the simulated sensor drivers from Nordic Semiconductor.


## Required Hardware and Software
- Development kit 
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Create your own Project based on _hello_world_ Example

1) Create a new project based on [LPS22HB sensor example](../ZDD_sensor/lps22hb_nrf54LM20dk).


### Enable the _simulated sensor_ driver

This hands-on is based on the LPS22HB sensor hands-on that we did previously. The aim here is to show how easy it is to integrate a new sensor into a project. 

2) Nordic's simulated sensor driver was developed for the Zephyr sensor driver. Therefore, it is sufficient to use the standard sensor handling. The simulated sensor is then integrated via the device tree.

    <sup>_nrf54l15dk_nrf54l15_cpuapp.overlay_</sup>
    
       / {
            sensor_sim: sensor_sim{
                 compatible = "nordic,sensor-sim";
                 acc-signal = "wave";
                 base-temperature = < 20 >;
                 base-pressure = < 98 >;
            };
       };

   __Note:__ You must perform an __pristine build__ after you have created the *.overlay file in Visual Studio Code. 


### Using the DeviceTree Definitions in our C-Code

3) In the previous hands-on session, we included the LPS22hb sensor into our project. This was done using the line __#define SENSOR_NODE DT_NODELABEL(lps22hb)__. We will now change this and insert the simulated sensor instead. 

    <sup>_src/main.c_ </sup>

           #define SENSOR_NODE DT_NODELABEL(sensor_sim)


## Testing

4) Build the Project and Download to the Development Kit

5) check the output in the __Serial Terminal__. 
