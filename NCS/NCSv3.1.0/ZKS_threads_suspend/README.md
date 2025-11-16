<sup>SDK version: NCS v3.1.0 </sup>

# Zephyr Kernel Services - Suspend and Resume Threads

## Introduction

This example demonstrates how to suspend a thread. 

## Required Hardware/Software
- Development kit [nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.1.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Create your own Project based on previous project

1) Create a new project based on previous hands-on [_Create a Thread_](../ZKS_threads_create/README.md). e.g. C:/Nordic/Workspace/threads_suspend.

### Suspend and resume Thread (my_tid1)

2) Suspend the Thread my_tid1 by adding following lines in the main() function:

   <sup>_C:/Nordic/Workspace/threads_create/src/main.c_ => main() function</sup>
   
           k_tid_t my_tid1 = k_thread_create(
           while (1)
           {
               k_msleep(15000);           // sleep 15 seconds
               k_thread_suspend(my_tid1); // suspend 1. Thread
               k_msleep(10000);           // sleep 10 seconds
               k_thread_resume(my_tid1);  // resume 1. Thread
               k_msleep(15000);           // sleep 15 seconds
    }

## Testing

3) Download the project to the connect nRF52 development board. Use a terminal program to check the debug ouptut. You should see something like this:

   ![image](images/Terminal.jpg)
   
   Thread 1 is printing each second, while Thread 2 is printing each 700 ms. 15 seconds after start the Thread 1 is suspended. Only Thread 2 is active. After 10 seconds Thread 1 is resumed again. Now the same Thread 1/Thread 2 pattern can be seen again.
