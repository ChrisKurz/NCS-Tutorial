# Bluetooth Low Energy: Get the Device Bluetooth Address at runtime

## Introduction

In an _nRF Connect SDK_ Bluetooth project, the Bluetooth device address (MAC address) can come from a few places depending on how the beacon is configured. Let's take a look at a few solutions here.


## Required Hardware/Software

- Development kit 
[nRF54LM20DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54LM20-DK),
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- install the _nRF Connect SDK_ v3.3.0 and _Visual Studio Code_.


## Hands-on step-by-step description

### Let's start with the existing Beacon example

1) Make a copy of the project [Beacon](basics/beacon). 


### Get the Address with Zephyr Bluetooth API

2) In the beacon application, use the Zephyr Bluetooth API to read the Bluetooth address.

	<sup>_main.c_</sup>
   
       #include <zephyr/bluetooth/bluetooth.h>
       #include <zephyr/bluetooth/hci.h>

       void print_bt_addr(void)
       {
           bt_addr_le_t addr;
           size_t count = 1;

           bt_id_get(&addr, &count);

           char addr_str[BT_ADDR_LE_STR_LEN];

           bt_addr_le_to_str(&addr, addr_str, sizeof(addr_str));

           printk("Bluetooth API -> BT Address: %s\n", addr_str);
       }

3) Call the <code>print_bt_addr()</code> function after the Bluetooth Stack was successfully enabled.

	<sup>_main.c_ => after successful <code>bt_enable()</code> call</sup>
   
           print_bt_addr();

### Get the Address by reading Nordic chip's FICR Register

4) Nordic chips store the public Bluetooth Address in FICR registers. Let's read the content of these registers.

	<sup>_main.c_</sup>

       #include <hal/nrf_ficr.h>

       uint32_t low  = NRF_FICR->DEVICEADDR[0];
       uint32_t high = NRF_FICR->DEVICEADDR[1];

5) And output the number to the Serial Terminal.

	<sup>_main.c_ => before main entire loop</sup>

           printk("FICR register content -> BT Address: %8x %8x\n", high, low);

   
## Testing

6) Build the project and download it to your development kit.

7) Check the output in the Serial Terminal.

   ![image](images/terminal.jpg)
   
