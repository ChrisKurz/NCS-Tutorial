<sup>SDK version: NCS v3.0.0 - Link to Hands-on solution: \[MCUboot1](https://github.com/ChrisKurz/MCUboot/tree/main/Workspace/NCSv3.0.0/MCUboot1)</sup>



\# MCUboot:  Adding MCUboot to a Project



\## Introduction



MCUboot takes care about the boot process. It handles the authentification of the application images and handles to copy the upgrade image to the slot, which is used to execute the code. Download of the upgrade image is handled within the application. 

So, first we will take a look on how to add MCUboot to an own project. 





\## Required Hardware/Software

\- Development kit \[\[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), \[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or \[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 

\- install the \_nRF Connect SDK\_ v3.0.0 and \_Visual Studio Code\_. The installation process is described \[here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).





\## Hands-on step-by-step description 



\### Create first application (which will be replaced later by the firmware update)



1\) Create a new application based on the /zephyr/samples/hello\_world sample project. (e.g. name of new project: "MCUboot1")

&nbsp;  

&nbsp;  The Build Configuration should look like this:



&nbsp;  !\[missing image](images/mcuboot_AddToProject/AddBuildConfiguration.jpg)



&nbsp; It is important to select "Use sysbuild" for the System build! 

&nbsp; 

&nbsp; > \*\*NOTE\*\*: The \_nRF Connect SDK\_ versions up to version v2.6.2 used a multi-image build of the \_Child and Parent images\_, which is set to \[deprecated in \_nRF Connect SDK\_ version 2.7.0](https://docs.nordicsemi.com/bundle/ncs-2.7.0/page/nrf/config\_and\_build/multi\_image.html). It is replaced by the Zephyr's \_Sysbuild\_. In this hands-on we will use \_Sysbuild\_. Multi-image builds functionality based on parent-child images, which was deprecated in nRF Connect SDK v2.7.0 has been removed in _nRF Connect SDK_ V3.0.0. Existing projects must transition to sysbuild (System build).





2\) Add the following line to main function:



&nbsp;	<sup>\_src/main.c\_ => main() function</sup>



&nbsp;          printf("Image: MCUboot1 \\n");



&nbsp;  \_\_Note:\_\_ In previous hands-on we used the function \_\_printk()\_\_, which is included in the Zephyr kernel. In the Zephyr hello\_world example the \[PICOLIB](https://docs.nordicsemi.com/bundle/ncs-2.8.0/page/zephyr/develop/languages/c/picolibc.html) library is included. This library supports all standard C formatted input and output functions, like \_printf()\_. This is also the reason why \_#include <stdio.h>\_ is used in the code example.



3\) Now we want to add MCUboot to our project.



&nbsp;  \_Sysbuild\_ allows us to handle two independent projects within a single project build. So it is basically doing a multi-image build. The images are:

&nbsp;   - our own application image. In this hands-on it is the hello world project that also prints "Image: MCUboot1" and

&nbsp;   - the MCUboot project itself, which is provided by the \_nRF Connect SDK\_ installation. So here we will only use KCONFIG to define the features that we would like to use from the provided MCUboot project. We will not change the MCUboot source code!



&nbsp;  We will use a \_Sysbuild\_ KConfig file for doing all the needed sysbuild configurations. Add the file \_\_sysbuild.conf\_\_ to your project folder (this is the folder where the CMakeLists.txt file is located). The file structure of your project should look like this:



&nbsp;   \_Workspace folder\_/01\_MCUboot1<br>

&nbsp;   |--- src<br>

&nbsp;   |--- |--- main.c<br>

&nbsp;   |--- CMakeLists.txt<br>

&nbsp;   |--- prj.conf<br>

&nbsp;   |--- \*\*sysbuild.conf\*\*



&nbsp;  Adding MCUboot to our project is done by putting \*\*SB\_CONFIG\_BOOTLOADER\_MCUBOOT=y\*\* into the \_sysbuild.conf\_ file.



&nbsp;	<sup>\_sysbuild.conf\_</sup>



&nbsp;      SB\_CONFIG\_BOOTLOADER\_MCUBOOT=y



4\) Build the project and take a look at the \*\*build\*\*, \*\*build/MCUboot1/zephyr\*\*, and \*\*build/mcuboot/zephyr\*\* folders. Adding MCUboot and the associated activation of a multi-image build results in additional files being generated in these folders. The most important files are:



&nbsp;  - \_\_build/01\_MCUboot1/zephyr/zephyr.hex\_\_: This file contains the image of the application project.

&nbsp;  - \_\_build/mcuboot/zephyr/zephyr.hex\_\_: This file contains the image of the bootloader, the mcuboot project. 

&nbsp;  - \_\_build/merged.hex\_\_: The different zephyr.hex files of a multi-image build are merged together and stored in the \_\_merged.hex\_\_ file. So in our example the zephyr.hex files of the \_01\_MCUboot1\_ project and the mcuboot project are merged. 

&nbsp;  

&nbsp;  Further generated files are described \[here](https://docs.nordicsemi.com/bundle/ncs-latest/page/nrf/config\_and\_build/configuring\_app/output\_build\_files.html#common\_output\_build\_files).





\## Testing ###



5\) Start "Programmer" in nRF Connect for Desktop. 



6\) Connect to your development kit. 



7\) Click "Add File" and select in your project folder /build/merged.hex file.



8\) In the Programmer you should see two blocks:



&nbsp;  !\[missing image](images/mcuboot_AddToProject/Programmer.jpg)



&nbsp;  The orange block at the bottom is the bootloader image. It is located at address 0x0000. Starting at address 0xC000 you find the green block, which is the \_hello world\_ application image. 



9\) In the Programmer tool click "Earse all" and afterwards "Erase \& write".



10\) When programming is completed, check the Terminal output. In case nothing is shown in the terminal, press the RESET button on the development kit.



&nbsp;  !\[missing image](images/mcuboot_AddToProject/Terminal.jpg)



&nbsp;  \_\_Note\_\_: The application is printing just once after a reset. So you have to press the Reset button on the development kit to see the output in the terminal window.

