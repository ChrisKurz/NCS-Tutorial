<sup>SDK version: NCS v3.2.0 </sup>

# Zephyr Device Driver: Adding BME280 Sensor Driver to an nRF52480 Project

There are a large of drivers in the Zephyr RTOS. In this hands-on exercise, we will take a closer look at the Sensor Drivers, specifically the BME280 sensor driver.

## Required Hardware and Software
- [nRF54LM20DK development kit](https://www.nordicsemi.com/Products/Development-hardware/nRF54LM20-DK)
- LPS22HB break-out board (e.g. from [Adafruit](https://www.adafruit.com/product/4633))
- QWICC Cable to connect sensor board to dev kit (e.g. from [Digikey](https://www.digikey.de/de/products/detail/sparkfun-electronics/17261/13629019?gclsrc=aw.ds&gad_source=1&gad_campaignid=20179590413&gbraid=0AAAAADrbLlgdC5gLnngSLmZOp0lk_C87F&gclid=EAIaIQobChMIpOuGyrnCkQMVXKb9BR30wzLREAQYCiABEgLT7PD_BwE))
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Connecting the LPS22HB Breakout Board to the nRF54LM20DK

1) First connect the LP22HB breakout board to the nRF54LM20DK as shown in the picture:

    ![image not found](images/LPS22_nRF54LM20DK.jpg)


### Create your own Project based on _hello_world_ Example

2) Create a new project based on Zephyr's _hello_world_ example (zephyr/samples/hello_world).

3) The Zephyr _hello_world_ example does not include the __zephyr/kernel.h__ header file. We include this header file in the main.c file:

   <sup>_src/main.c_ </sup>

       #include <zephyr/kernel.h>

### Definition of Hardware Usage in DeviceTree Files

4) Let us now configure the BME280 sensor driver in an DeviceTree Overlay file. The Overlay file allows us to overwrite definitions made in the pre-defined board file __nRF52840DK_nRF52840.dts__. We will use the I2C definition of the Arduino Shield and modify it as described in the following text. 
 
    Create the file __nRF52840DK_nRF52840.overlay__ in your project folder. (IMPORTANT: Make sure you use exactly this name, as we will overwrite the file __nRF52840DK_nRF52840.dts__ with this name!)

    Then add following content to this file:

    <sup>_nrf54lm20dk_nrf54lm20a_cpuapp.overlay_</sup>
    
       /* Configuration of a LPS22HB device
          -------------------------------------------------------
          Device Address 0x5d is used here. 
          Selected pins:
               SCL  ->  P1.12
               SDA  ->  P1.13
       */    
       &i2c21 {
              status = "okay";
              pinctrl-0 = <&i2c21_default>;
              pinctrl-1 = <&i2c21_sleep>;
              pinctrl-names = "default", "sleep";
              clock-frequency = <I2C_BITRATE_STANDARD>;

              lps22hb: lps22hb@5d{
                      compatible = "st,lps22hb-press";
                      reg = <0x5d>;
              };
       };

       &pinctrl {
                i2c21_default: i2c21_default {
                     group1  {
                         psels = <NRF_PSEL(TWIM_SCL, 1, 12)>,
                                 <NRF_PSEL(TWIM_SDA, 1, 13)>;
                     };
                };

                i2c21_sleep: i2c21_sleep {
                     group1  {
                         psels = <NRF_PSEL(TWIM_SCL, 1, 12)>,
                                 <NRF_PSEL(TWIM_SDA, 1, 13)>;
                         low-power-enable;
                     };
                };
       };

   __Note:__ You must perform an __pristine build__ after you have created the *.overlay file in Visual Studio Code. 

### Using the DeviceTree Definitions in our C-Code
In the previous step, we defined the hardware usage for the LPS22HB sensor. Now we need to use these definitions in our C code. This is done in the following steps:

5) Get the device structure from the DeviceTree node with node label "lps22hb". This is done by adding following line in main function:

    <sup>_src/main.c_ - add following lines in __void main(void)__ function </sup>


           #define SENSOR_NODE DT_NODELABEL(lps22hb)
           const struct device *const dev = DEVICE_DT_GET(SENSOR_NODE);    
           if (!device_is_ready(dev)) {
              printk("Sensor is not ready %s\n", dev->name);
              return 0;
           }
           printk("Sensor is ready!\n");

6) We use the __DEVICE_DT_GET__ macro here. This is a DeviceTree macro and is defined in the header file __device.h__. We must therefore include this header file in our project. Add the following line to the __main.c__ file

    <sup>_src/main.c_ </sup>
    
       #include <zephyr/device.h>

  __Note:__ The device.h header file is also included within the kernel.h. So there is no need to mention it again!


### KCONFIG: Adding the Sensor Driver and Interface Driver to our Project

7) The required software modules can be added to our project by setting the corresponding CONFIG symbols (KCONFIG). Let's consider which software modules are needed:
    > - I2C: The LPS22HB itself supports I2C and SPI interfaces. However, the breakout board is designed so that only I2C is used. 
    > - Sensor: Include the sensor drivers to get access to the LPS22HB sensor driver. 

   To enable these modules, we need to add following lines to the __prj.conf__ file.
    
   <sup>_prj.conf_</sup>
    
       # Enable Software Modules for Sensor Driver Usage
       CONFIG_I2C=y
       CONFIG_SENSOR=y

       # Enable Floating Point output 
       CONFIG_CBPRINTF_FP_SUPPORT=y
    
### Using the LPS22BH Sensor Driver in our own Application
We have included the driver with the previous steps. Now we will use the driver in our own Application software. 

8) We keep our software quite simple and handle the sensor measurements in the main entire loop. So insert following lines into the main function:

    <sup>_src/main.c_ - add following lines in __void main(void)__ function </sup>
    
           while(1){
               struct sensor_value pressure, temp;

               // Fetch a sample from the sensor and store it in an internal driver buffer
               if (sensor_sample_fetch(dev) < 0) {
                   printk("Error: Sensor sample update error\n");
                   return;
               }

               // Get a reading from a sensor device (read pressure)
               if (sensor_channel_get(dev, SENSOR_CHAN_PRESS, &pressure) < 0) {
                  printk("Error: Cannot read LPS22HB pressure channel\n");
                  return;
               }

               // Get a reading from a sensor device (read temperature)	
               if (sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temp) < 0) {
                   printk("Error: Cannot read LPS22HB temperature channel\n");
                   return;
               }
 
               /* display pressure */
               printk("pressure: %d.%d kPa, ", pressure.val1, pressure.val2);
               //printk("Pressure: %.1f kPa, ", sensor_value_to_double(&pressure));

               /* display temperature */
               printk("Temperature: %.1f C\n", sensor_value_to_double(&temp));

               k_sleep(K_MSEC(1000));                
           }



9) We use the functions __sensor_sample_fetch__ and __sensor_channel_get__ to trigger a measurement and read the conversion results. The use of these functions requires their declaration. This is done in the header file __sensor.h__. We must therefore include them in our project. Insert following line at the beginning of the main.c file:

    <sup>_src/main.c_ </sup>
    
       #include <zephyr/drivers/sensor.h>


## Testing

### Build the Project and Download to the Development Kit

10) Click on the "Build" button in the ACTIONS menu. 

11) Make sure that the connected kit has been found and click on __Flash__ in the ACTIONS menu. The code will now be downloaded to the kit. 

![image not found](images/BuildFlash.jpg)


### Open Terminal and check Output

12) Open the terminal. We recommend using the _Serial Terminal_ from Nordic, which can be found in the _Connect for Desktop_ application. With this terminal, the default setting can be used and the received data should be output immediately after a connection. 

       In case another terminal program is used, here are the necessary settings: 

       - Baud Rate: 115200 
       - Data bits: 8
       - Stop bits: 1
       - Parity:    none
       - Flow control: off
    
13) Reset the kit by pressing the Reset button on the board. The Zephyr boot message is displayed in the terminal, followed by the application startup output "LPS22HB Demo" and the measurement results. 
