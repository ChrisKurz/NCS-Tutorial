# Bluetooth Low Energy: Changing Advertising Interval Time

## Introduction

In the [previous hands-on session](../basics_beacon/README.md), we implemented a beacon application. When we started advertising, we used a predefined setting in the parameter list that, among other things, defined the advertising interval. In this hands-on session, we’ll take a closer look at what was used here and how the advertising interval can be adjusted.

## Required Hardware/Software
- Development kit 
[nRF54LM20DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54LM20-DK),
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk)
- [Power Profiler Kit II](https://www.nordicsemi.com/Products/Development-hardware/Power-Profiler-Kit-2)
- 2 Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.3.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Create a new project

1) Copy the [beacon project](../basics_beacon) from the previous hands-on.
   
2) Build the project and download it to the devlopment kit, e.g. nRF54L15DK.

  
### Measuring Advertising Interval of Beacon sample

3) We determine the set advertising interval by measuring the time between two RF transmissions in the power profile.



### Change Advertising Interval and check again


