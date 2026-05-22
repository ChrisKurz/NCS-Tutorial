# Bluetooth Low Energy: Get the Device Bluetooth Address at runtime

## Introduction

In an _nRF Connect SDK_ Bluetooth project, the Bluetooth device address (MAC address) can be read in different ways. Let's take a look at the most common way. 


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

           printk("Public Bluetooth Address: %s\n", addr_str);
       }

3) Call the <code>print_bt_addr()</code> function after the Bluetooth Stack was successfully enabled.

	<sup>_main.c_ => after successful <code>bt_enable()</code> call</sup>
   
           print_bt_addr();

   
## Testing

4) Build the project and download it to your development kit.

5) Check the output in the Serial Terminal.

   ![image](images/terminal.jpg)

6) Use a smartphone and the _nRF Connect for Mobile_ app to check the Bluetooth Address of the Beacon. You should see that a different address is used. Above we have read the public Bluetooth Address. By default, _nRF Connect SDK_ or Zephyr often uses privacy (resolvable private addresses). If privacy is enabled (CONFIG_BT_PRIVACY=y), the address you see in advertising will change and not match the public address you set. 
