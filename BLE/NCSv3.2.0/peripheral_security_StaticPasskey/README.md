<sup>SDK version: NCS v3.2.0 </sup>

# Bluetooth Low Energy: Enable Security with a static Passkey on a Bluetooth Peripheral

## Introduction

In the previous hands-on session, we looked at a solution using a passkey, whereby the passkey was a random number. However, it can sometimes be helpful to use a predefined passkey. We will implement this in this example.


## Required Hardware/Software
- Development kit [nRF54LM20DK](), [nRF54L15DK](), [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk)
- a smartphone ([Android](https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp\&hl=de\&gl=US\&pli=1) or [iOS](https://apps.apple.com/de/app/nrf-connect-for-mobile/id1054362403)), which runs the __nRF Connect__ app 
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description

### Prepare the project

1. Let's start with the previous [Bluetooth Security](../peripheral\_security/README.md) project.

### Enable and defining static passkey

2. The needed software modules are included in the project by setting the appropriate KCONFIG symbol.

   <sup>prj.conf</sup>

       # use static passkey
       CONFIG\_BT\_FIXED\_PASSKEY=y

3. We use the Bluetooth API function __bt_passkey_set()__ to define the static passkey. This is done once during initialization in the main() function.

   <sup>main.c </sup>

       /* Set a fixed passkey */
       err = bt\_passkey\_set(123456);
       if (err) {
           printk("Definition of static passkey failed! (err %d)\n", err);
           return 0;
       }


### Testing

14) Finally, build the project ("Pristine Build"!!!). 

15) Use the _Serial Terminal_ to check the debug output. 
