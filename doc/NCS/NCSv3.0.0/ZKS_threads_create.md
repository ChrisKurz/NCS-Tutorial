<sup>SDK version: NCS v3.0.0  -  Link to Hands-on solution: https://github.com/ChrisKurz/NCS-Tutorial/tree/main/Workspace/NCS/NCSv3.0.0/threads_create</sup>

# Zephyr Kernel Services - Threads

## Introduction

This example demonstrates how to create threads. There are two ways to create a thread. So we will use both. 

## Required Hardware/Software
- Development kit [nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.0.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 

### Create your own Project based on _hello_world_ Example

1) Create a new project based on Zephyr's _hello_world_ example (./zephyr/samples/hello_world). e.g. rename the _hello_world_ project folder to C:/Nordic/Workspace/threads_create.

2) The Zephyr _hello_world_ example does not include the __zephyr/kernel.h__ header file. We add this include in the main.c file:

   <sup>_C:/Nordic/Workspace/threads_create/src/main.c_ </sup>

       #include <zephyr/kernel.h>


### Create first Thread (myThread1)

Here we will create an new thread during runtime. This way may be used to create a new thread during application code execution. 

3) Create the Thread by adding following lines in the main() function:

   <sup>_C:/Nordic/Workspace/threads_create/src/main.c_ => main() function</sup>
   
           k_tid_t my_tid1 = k_thread_create(
                  &myThread1_data,    /* Thread Control Block                        */
                  mythread1_stack_area, /* Stack Area                                */
                  K_THREAD_STACK_SIZEOF(mythread1_stack_area),
                  myThread1,          /* Thread Entry Function                       */
                  NULL, NULL, NULL,   /* Passing parameters for entry point function */
                  MYTHREAD1_PRIORITY, /* Thread priority                             */
                  0,                  /* Thread options                              */
                  K_NO_WAIT);         /* Scheduling delay (K_NO_WAIT for no delay)   */

4) Some of these parameters have to be defined now. Let's start with _my_thread_data_. Here we have to define a Variable based on __k_thread__ type. 

   <sup>_C:/Nordic/Workspace/threads_create/src/main.c_</sup>

       struct k_thread myThread1_data;

5) Beside this, we also have to define the stack area for the thread. 

   <sup>_C:/Nordic/Workspace/threads_create/src/main.c_</sup>

       #define MYTHREAD1_STACK_SIZE 500

       K_THREAD_STACK_DEFINE(mythread1_stack_area, MYTHREAD1_STACK_SIZE);

6) The code that is processed with respect to this thread is written in a function. When creating the thread, the entry point address of this function is given. 

   <sup>_C:/Nordic/Workspace/threads_create/src/main.c_</sup>

       void myThread1(void *arg1, void *arg2, void *arg3) {
        
           while(1) {
               k_msleep(1000);
               printk("executing myThread1\n");
           }
       }

7) And finally, the thread priority has to be defined.

   <sup>_C:/Nordic/Workspace/threads_create/src/main.c_</sup>

       #define MYTHREAD1_PRIORITY 5

   > __NOTE:__ In this simple example, we have not really considered the thread priority. We will take a closer look at this in a later hands-on. Since a priority must also be specified for the definition of a thread, we simply use priority level 5 here. 


### Create second Thread (myThread2)

In case the thread can be created during OS initialization, then using the K_THREAD_DEFINE() macro is another possibility to create a thread. 

8) Create the Thread by adding following lines in the main() function:

   <sup>_C:/Nordic/Workspace/threads_create/src/main.c_</sup>

       K_THREAD_DEFINE(
                  my_tid2,            /* Name of the thread                          */
                  MYTHREAD2_STACK_SIZE, /* Stack size in bytes                       */
                  myThread2,          /* Thread entry function                       */
                  NULL, NULL, NULL,   /* Passing parameters for entry point function */
                  MYTHREAD2_PRIORITY, /* Thread priority                             */
                  0,                  /* Thread options                              */
                  0);                 /* Scheduling delay (0 for no delay)           */

9) We have to define here also the stack size.

   <sup>_C:/Nordic/Workspace/threads_create/src/main.c_</sup>

       #define MYTHREAD2_STACK_SIZE 500

10) Let's define the Thread function. 

   <sup>_C:/Nordic/Workspace/threads_create/src/main.c_</sup> 

       void myThread2(void *arg1, void *arg2, void *arg3) {
        
           while(1) {
               k_msleep(700);
               printk("executing myThread2\n");
           }
       }

11) And finally, define the Thread priority. 

   <sup>_C:/Nordic/Workspace/threads_create/src/main.c_</sup>

    #define MYTHREAD2_PRIORITY 5

   > __NOTE:__ In this simple example, we have not really considered the thread priority. We will take a closer look at this in a later hands-on. Since a priority must also be specified for the definition of a thread, we simply use priority level 5 here. 


## Testing

12) Download the project to the connect nRF52 development board. Use a terminal program to check the debug ouptut. You should see something like this:

   ![image](images/ZKS_threads_create/Testing.jpg)
   
   Thread 1 is printing each second, while Thread 2 is printing each 700 ms. That's why Thread 2 is sometimes output twice in a row. 
