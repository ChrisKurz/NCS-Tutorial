<sup>SDK version: NCS v3.2.0 </sup>



\# Getting started: DeviceTree



\## Introduction



A DeviceTree is a hierarchical data structure that is mainly used to describe hardware. Zephyr uses DeviceTree to describe hardware for the Device Driver Model and to provide the initial configuration of this hardware.



In this first example, we will look at how properties from the DeviceTree file can be used in C code.





\## Required Hardware/Software

\- Development kit 

\[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 

\[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 

\[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 

\[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 

\- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)

\- install the \_nRF Connect SDK\_ v3.2.0 and \_Visual Studio Code\_. The installation process is described \[here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).





\## Hands-on step-by-step description 



\### Create a new project



1\) Make a copy of the \[Creating a Project from Scratch](../DEV\_ProjectFromScratch) hands-on and store it in your workspace folder, e.g.  C:/Nordic/Workspace/DeviceTree





\### Create an DeviceTree Overlay File



2\) Add a DeviceTree overlay file to your project. The easiest way to do this is to open the \_hello\_word\_ directory \_\_Config files/Devicetree\_\_ in details window and click on “Create overlay file”.



&#x20;  !\[missing image](images/CreateOverlayFile.jpg)



3\) A devicetree entry requires a device driver that has assigned a struct device to this devicetree node. If this is not the case, a linker error occurs during the build because a pointer to an undefined device is requested.



&#x20;  Therefore we will work with the LED device tree entry.



&#x20;  <sup>\_\_nrf54l15dk\_nrf54l15\_cpuapp.overlay\_\_ </sup>



&#x20;      / {



&#x20;          aliases { 

&#x20;                   led-power  = \&led0;

&#x20;                   led-status = \&led1;

&#x20;                   led-blink  = \&led2;

&#x20;                   led-user   = \&led3;

&#x20;          };



&#x20;          leds {

&#x20;                compatible = "gpio-leds";



&#x20;                led0: led\_0 {

&#x20;                          gpios = <\&gpio2 9 GPIO\_ACTIVE\_HIGH>;

&#x20;                          label = "Green LED 0";

&#x20;                };



&#x20;                led1: led\_1 {

&#x20;                          gpios = <\&gpio1 10 GPIO\_ACTIVE\_HIGH>;

&#x20;                          label = "Green LED 1";

&#x20;                };



&#x20;                led2: led\_2 {

&#x20;                          gpios = <\&gpio2 7 GPIO\_ACTIVE\_HIGH>;

&#x20;                          label = "Green LED 2";

&#x20;                };



&#x20;                led3: led\_3 {

&#x20;                          gpios = <\&gpio1 14 GPIO\_ACTIVE\_HIGH>;

&#x20;                          label = "Green LED 3";

&#x20;                };

&#x20;          };

&#x20;      };

&#x20;  

\### Usage in C Code



\#### Reading \_label\_ Property



4\) Let's read the properties. In the overlay file we created earlier, there are several properties with the same name: e.g. \_gpios\_ or \_label\_



&#x20;  Therefore, we need to specify which \_\_Node Identifier\_\_ we want to access. This can be done in different ways.



&#x20;  <sup>\_\_src/mainc\_\_</sup>



&#x20;      #include <zephyr/devicetree.h>



&#x20;      /\* select one of the following possibilities to get the node identifier: \*/

&#x20;      #define NODE\_ID  DT\_PATH(leds, led\_0)

&#x20;      // #define NODE\_ID  DT\_NODELABEL(led1)

&#x20;      // #define NODE\_ID  DT\_ALIAS(led\_blink)



&#x20;  > \_\_Note:\_\_ It is important to understand that node identifiers are not values! There is no way to store them in a variable.



5\) The correct DeviceTree macro for reading property values depends on the node and the property. Let's try to read the \_\_label\_\_ property. For reading simple properties like integer-, boolean-, string-, numeric-array- and string-array-properties, you can use DT\_PROP(node\_id, property).



&#x20;  <sup>\_\_src/mainc\_\_ => main() function</sup>

&#x20;   

&#x20;          char string\[20] = DT\_PROP(NODE\_ID, label);

&#x20;          printk("property label = %s\\n", string);



\### Reading \_gpios\_ Property



6\) Accessing the \_\_gpios\_\_ property requires a corresponding driver that defines a struct that takes the information from the DeviceTree file. In the case of the GPIO driver, this is the struct \_\_gpio\_dt\_spec\_\_.



&#x20;  We have to include the gpio.h header file and read the gpios property with the DeviceTree macro \_\_GPIO\_DT\_SPEC\_GET()\_\_.



&#x20;  <sup>\_\_src/mainc\_\_</sup>



&#x20;      #include <zephyr/drivers/gpio.h>



&#x20;      static const struct gpio\_dt\_spec led = GPIO\_DT\_SPEC\_GET(NODE\_ID, gpios);



&#x20;  > \_\_Note:\_\_ The \_\_struct gpio\_dt\_spec\_\_ is defined in the gpio.h file, which takes over the information from the DeviceTree file.

&#x20;  >   !\[missing image](images/gpio\_dt\_spec.jpg)

&#x20;  > 

&#x20;  >   Here is the \_\_gpios\_\_ property entry from the DeviceTree file for comparison.

&#x20;  > 

&#x20;  >   !\[missing image](images/gpios.jpg)



7\) Let's take a look at what the C code has read in with the above line.



&#x20;  <sup>\_\_src/mainc\_\_ => main() function</sup>



&#x20;          printk("GPIO port: %s\\n", led.port->name);

&#x20;          printk("GPIO pin: %i\\n", led.pin);

&#x20;          printk("GPIO flags: %i\\n", led.dt\_flags);







\## Testing



\### Testing: Reading \_label\_ Property



Let's check the outputs for the various node identifiers.



8\) We start with \_\_DT\_PATH\_\_:



&#x20;  !\[missing image](images/usingPath.jpg)



&#x20;  The serial terminal output then looks like this:



&#x20;  !\[missing image](images/TerminalPath.jpg)



9\) Now use \_\_NODELABEL\_\_:



&#x20;  !\[missing image](images/usingNodelabel.jpg)



&#x20;  The serial terminal output then looks like this:



&#x20;  !\[missing image](images/TerminalNodelabel.jpg)



10\) And here we use \_\_ALIAS\_\_:



&#x20;  !\[missing image](images/usingAlias.jpg)



&#x20;  The serial terminal output then looks like this:



&#x20;  !\[missing image](images/TerminalAlias.jpg)





\### Testing: Reading \_gpios\_ Property



11\) Let's check what the output is:



&#x20;  !\[missing image](images/Terminal.jpg)

&#x20;  

