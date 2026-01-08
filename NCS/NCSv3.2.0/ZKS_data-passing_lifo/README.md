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
       struct data_item_t my_data;

4) In the button_pressed function we write the counter variable to the LIFO:

	<sup>_src/main.c_ => button_pressed() function</sup>   
  
           my_data.counter=my_data.counter+1;
           k_lifo_put(&my_lifo, &my_data);

5) Reading from the LIFO. A data item is removed from a LIFO by calling k_lifo_get(). The following code uses the LIFO to obtain data items from a producer thread, which are then processed in some manner.

   Add following lines in the main entire loop:

	<sup>_src/main.c_ => main() function</sup>   

           struct data_item_t *my_getData;

                   my_getData = k_lifo_get(&my_lifo, K_FOREVER);
                   printk("Counter: %d\n",my_getData->counter);

## Testing

6) Build the project and download to an nRF52 development kit (e.g. nRF52840-DK).

7) Check the output sent via virtual COM port. 
