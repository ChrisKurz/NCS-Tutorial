<sup>SDK version: NCS v3.2.0</sup>

# Zephyr Kernel Services: Timing - Timers

## Introduction

The Zephyr kernel provides a _Timer_ object that can be used to generate timings. The _Timer_ object uses the system clock and generates callback function calls when the timer expires or when it is stopped. 


## Required Hardware/Software
- Development kit 
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Create a new Project

1) Create a new application. Use the zephyr/samples/hello_world sample. 

### Define k_timer Variable

2) The number of timers that can be created is limited only by the amount of ram available. For each timer a variable of type _k_timer_ must be defined. Each timer is referenced by its memory address. So let's define this variable:

 	<sup>_src/main.c_</sup>   
   
       struct k_timer MyTimer;

### Initialize the Timer

3) Now we will initialize the timer by calling _k_timer_init()_ function: 
  
  <sup>_src/main.c_ => main() function</sup>   
  
        k_timer_init(&MyTimer, TimerExpire, TimerStopped);

   _k_timer_init()_ function description:
   
   ![image](images/KTimerInit.jpg)
   
   <sup>https://docs.nordicsemi.com/bundle/ncs-3.0.0/page/zephyr/kernel/services/timing/timers.html#c.k_timer_init</sup>


### Define expireation callback function

4) In the timer initialization we also defined a callback function, which should be called as soon as the timer expires. So we have to add this function.

  <sup>_src/main.c_</sup>   
  
    static void TimerExpire(struct k_timer *timer) {
        static uint16_t count;
    
        count++;
        printk("timer expired [%d]: %u\n",count, timer->status);
           
        if (count == 10)
            k_timer_stop(timer);
    }

   _k_timer_stop()_ function description:
   
   ![image](images/KTimerStop.jpg)
   
   <sup>https://docs.nordicsemi.com/bundle/ncs-3.0.0/page/zephyr/kernel/services/timing/timers.html#c.k_timer_stop</sup>


### Define stop timer callback function

5) And there is another callback function that has to be called as soon as the timer was stopped. 

  <sup>_src/main.c_</sup>   

    static void TimerStopped(struct k_timer *timer) {
        printk("Timer was stopped!\n");       
    }

### Start Timer

6) The timer was not yet started. This is done with following line:

  <sup>_src/main.c_ => main() function</sup>   

        k_timer_start(&MyTimer, K_MSEC(5000), K_MSEC(1000)); // wait 5 seconds, period 1 second
       
   _k_timer_start()_ function description:
   
   ![image](images/KTimerStart.jpg)
   
   <sup>https://docs.nordicsemi.com/bundle/ncs-3.0.0/page/zephyr/kernel/services/timing/timers.html#c.k_timer_start</sup>
       
       
## Testing

7) Build the project.
8) Open a terminal program (e.g. Putty - 115200 baud, 8 data bits, 1 stop bit, no flow control).
9) Flash the project to your development kit. 
10) Check the output in your terminal program. You should see something like this:

   ![image](images/Terminal.jpg)
   
   Note that first timer expiration should happen around 5 seconds after program start. Afterwards you should see timer expiration each second.
   
