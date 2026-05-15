# Creating a Version of a Custom Board 

## Introduction

Sometimes it is necessary to modify a printed-circuit-board that has already been created in order to add new features or fix problems. However, to ensure that the original board definition remains accessible, it is often a good idea to generate a new revision of the board with a new version number. This is also supported in Zephyr with the Hardware Model V2. 

In this hands-on session, we will update the custom board we created in the previous hands-on session with a new version. The only change we are making here is to use a different LED on a different GPIO pin. 

## Required Hardware/Software
- Development kit 
[nRF54LM20DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54LM20-DK),
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk), (nRF54L15DK)
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.3.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Use previous developed custom board and blinky example

1) Please ensure that the board definition we created in the [previous hands-on](../DEV_NewBoard/README.md) session is available on your computer. 
2) Ensure the blniky sample is running with the original board definition from previous hands-on. 

### Adding a new Board Revision

3) Add the new revision to C:/Nordic/MyBoards/boards/ChrisKurz/mein_Board/board.yaml (or the path based on the Vendor and Board name you used) to inform the build system of the new options. Following section should be place in the __board:__ structure:

   <sup>__board.yml__</sup>

         revision:
           format: major.minor.patch
           default: 1.0.0
           exact: true
           revisions:
           - name: 1.0.0   # original version
           - name: 1.1.0   # new version
   
5) Add a new file in the Board folder which uses the same board name as the orignal board. We just add a version number by adding "_1_1_0" at the end of the board name. The file extension must now be __.overlay__.

   Example:    mein_Board_nrf5340_cpuapp_1_1_0.overlay

6) We now add the changes in this overlay file:

   <sup>__mein_Board_nrf5340_cpuapp_1_1_0.overlay__</sup>

       &led0{
           gpios = <&gpio0 31 GPIO_ACTIVE_LOW>;
       };

 7) In case, any changes would be done in the KCONFIG definition, then we would need a new KCONFIG file that also mentiones the version number (_<board name>_1_1_0_defconfig).

    Example: mein_board_nrf5340_cpuapp_1_1_0_defconfig

  > __Note:__ We are not changing any KCONFIG settings. Because of this this file is empty. 


## Testing

8) Enter revision 1.0.0 when adding build configuration. Do a pristine build and flash the project to the development kit. LED1 should blink. 

9) Use the revision 1.1.0 when adding build configuration. Do a pristine Build and flash the project to the development kit. You should see the LED blinking (e.g. LED4).

10) Check which LED is toggling when Revision field is blank in add build configuration.
