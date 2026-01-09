<sup>SDK version: NCS v3.2.0 </sup>

# Zephyr Kernel Services: Data Passing - LIFO

## Introduction

A LIFO is a kernel object that implements a traditional last in, first out (LIFO) queue, allowing threads and ISRs to add and remove data items of any size.

The LIFO in Zephyr is implemented as a queue and uses a single-linked list. 

Detailed description can be found [here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/2.3.0/zephyr/kernel/services/data_passing/lifos.html).


## Required Hardware/Software for Hands-on
- development kit (e.g. nRF54L20DK, nRF54L15DK, nRF52DK, nRF52833DK, or nRF52840DK)
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. 


## Hands-on step-by-step description 

### Create a new Project

1) Create a new project based on the Zephyr button example (/zephyr/samples/basic/button)

### Defining a LIFO

2) A LIFO is defined using a variable of type k_lifo. It must then be initialized by calling k_lifo_init(). The following code defines and initializes an empty LIFO.

	<sup>_src/main.c_</sup>   
  
       struct k_lifo my_lifo;

3) And in main loop add:

	<sup>_src/main.c_ => main() function</sup>   

           k_lifo_init(&my_lifo);

4) Define a Data item:

	<sup>_src/main.c_</sup>   

       struct data_item_t{
               void *lifo_reserved;  
               int counter;
       };
       struct data_item_t my_data1 = {NULL, 1, 0};
       struct data_item_t my_data2 = {NULL, 2, 0};
       struct data_item_t my_data3 = {NULL, 3, 0};

4) In the button_pressed function we write the counter variable to the LIFO:

	<sup>_src/main.c_ => button_pressed() function</sup>   
  
           	my_data1.counter=my_data1.counter+1;
            k_lifo_put(&my_lifo, &my_data1);

	        my_data2.counter=my_data2.counter+2;
            k_lifo_put(&my_lifo, &my_data2);

	        my_data3.counter=my_data3.counter+3;
            k_lifo_put(&my_lifo, &my_data3);

5) Reading from the LIFO. A data item is removed from a LIFO by calling k_lifo_get(). The following code uses the LIFO to obtain data items from a producer thread, which are then processed in some manner.

   Add following lines in the main entire loop:

	<sup>_src/main.c_ => main() function</sup>   

           struct data_item_t *my_getData1;
           struct data_item_t *my_getData2;
           struct data_item_t *my_getData3;

           printk("------\n");

           my_getData1 = k_lifo_get(&my_lifo, K_FOREVER);
           printk("ID: %i, Counter: %d\n",my_getData1->id, my_getData1->counter);

           my_getData2 = k_lifo_get(&my_lifo, K_FOREVER);
           printk("ID: %i, Counter: %d\n",my_getData2->id, my_getData2->counter);

           my_getData3 = k_lifo_get(&my_lifo, K_FOREVER);
           printk("ID: %i, Counter: %d\n",my_getData3->id, my_getData3->counter);

           printk("------\n");

6) Change the __SLEEP_TIME_MS__ value in line 19 to 5000.

	<sup>_src/main.c_</sup>   

       #define SLEEP_TIME_MS 10000

> __Note:__ We set the sleep time to a relatively high value so that we have the option of pressing the button while the CPU is still sleeping. This is important because the button_pressed function does not check whether the variable has already been set in the LIFO and has not yet been retrieved. Please also note the comment in the LIFO description: _Any attempt to re-add a LIFO data item to a queue before it has been removed from the queue to which it was previously added will result in undefined behavior._


## Testing

6) Build the project and download to an nRF52 development kit.

7) Check the output sent via virtual COM port.
8) Note that the Button 0 on the development kit should be pressed before the "------" is shown in the terminal! The output in the serial terminal should then look like this:

   ![images](images/terminal.jpg)
