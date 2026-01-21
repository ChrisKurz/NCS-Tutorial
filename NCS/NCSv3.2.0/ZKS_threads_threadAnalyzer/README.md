<sup>SDK version: NCS v3.2.0 </sup>

# Zephyr Kernel Services - Thread Analyzer

## Introduction

The Thread Analyzer module activates all Zephyr options required to track Thread information, such as Thread stack size usage and other runtime statistics related to Threads. 

There are various ways to use the Thread Analyzer. The analysis is performed on demand when the application calls thread_analyzer_run() or thread_analyzer_print(). Alternatively, it is also possible to output the current statistics at regular intervals. We will use this second method here.


## Required Hardware/Software
- Development kit 
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Create your own Project based on _create Thread_ Example

1) Create a copy of the [create Thread](../ZKS_threads_create/README.md) project. 


### Adding Thread Analyzer

2) We add the Thread Analyzer by adding following KCONFIG setting in pjr.con.

   <sup>_prj.conf_</sup>

       # Enable Thread analyzer
       CONFIG_THREAD_ANALYZER=y

3) In our example, the thread analyzer should output the thread statistics every 20 seconds via the console. 

   <sup>_prj.conf_</sup>

       CONFIG_THREAD_ANALYZER_AUTO=y
       CONFIG_THREAD_ANALYZER_AUTO_INTERVAL=20


## Testing

3) Build and download the project to the connect development kit. 

4) Check the output on your _Serial Terminal_.
