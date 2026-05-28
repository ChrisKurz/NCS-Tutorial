# Zephyr OS Services: Storage - Zephyr Memory Storage (ZMS)

## Introduction

Zephyr Memory Storage (ZMS) is a lightweight flash-based sstorage backend insdie Zephyr. It is designed for example persistent settings, configuration storage, calibration parameters, runtime parameters, small databases, and device state information. ZMS internally handles flash sector management, wear leveling, record allocation, and data integrity. 

ZMS works similarly to NVS, but with a newer architecture optimized for Zephyr.

Further information about ZMS can be found [here](https://docs.nordicsemi.com/bundle/ncs-latest/page/zephyr/services/storage/zms/zms.html).

## Required Hardware/Software

- Development kit 
[nRF54LM20DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54LM20-DK),
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- install the _nRF Connect SDK_ v3.3.0 and _Visual Studio Code_.


## Hands-on step-by-step description

### Let's start with hello_world Project

1) Make a copy of Zephyr's _hello_word_ project.
2) Include the Zephyr kernel.h header file.

   <sup>__main.c__</sup>

       #include <zephyr/kernel.h>

### Disable Partition Manager

3) Partition Manager is deprecated in _nRF Connect SDK v3.3.0_. Because of this, we disable Partition Manager.

      <sup>__sysbuild.conf__</sup>

       SB_CONFIG_PARTITION_MANAGER=n

### Enable Flash and ZMS Support

4) Enable Flash support.

   <sup>__prj.conf__</sup>

       # Enable Flash support
       CONFIG_FLASH=y
       CONFIG_FLASH_MAP=y
       CONFIG_FLASH_PAGE_LAYOUT=y
       CONFIG_MPU_ALLOW_FLASH_WRITE=y
   
6) Enable ZMS support.

   <sup>__prj.conf__</sup>

       # Enable ZMS support
       CONFIG_ZMS=y


### Include Header Files for Storage (ZMS, Flash)

7) Inside __main.c__ we first include the necessary Zephyr header files.
   
   <sup>__main.c__</sup>

       #include <zephyr/storage/zms/zms.h>
       #include <zephyr/drivers/flash.h>
       #include <zephyr/storage/flash_map.h>


### Define a Flash Area

8) ZMS needs a flahs area where it stores data. We use one of the available fixed flash partitions. The <code>storage_paritition</code> exists in the nRF54L15DK board DTS configuration.

   <sup>__main.c__</sup>   

       #define ZMS_PARTITION FIXED_PARTITION_ID(storage_partition)

### Create a ZMS Filesystem Instance

9) This structure represents the ZMS filesystem.

   <sup>__main.c__</sup>   

       static struct zms_fs fs;

### Initialize ZMS

10) Before using ZMS, the filesystem must be configured. 

   <sup>__main.c__</sup>   

        fs.flash_device = FIXED_PARTITION_DEVICE(storage_partition);
        fs.offset = FIXED_PARTITION_OFFSET(storage_partition);
        fs.sector_size = 4096;
        fs.sector_count = 4;

11) And then we initialize the file system.

   <sup>__main.c__</sup>   
    
        int rc = zms_mount(&fs);
        if (rc < 0) {
            printk("Failed to mount ZMS: %d\n", rc);
            return 0;
        }
        printk("ZMS mounted successfully\n");

### Write and Read Data

12) We now store a string in flash memory.

   <sup>__main.c__</sup>   

        /* Write Data */
        const char write_data[] = "Hello ZMS!";
        
        rc = zms_write(&fs,     /* file system */
                       1,       /* key ID */
                       data,    /* data pointer */
                       strlen(data) + 1);  /* data size */  
        if (rc < 0) {
            printk("Failed to write data: %d\n", rc);
            return 0;
        }
        printk("Data written successfully\n");

13) And now we read data.

   <sup>__main.c__</sup>   

        /* Read Data */
        char read_buffer[64];
        memset(read_buffer, 0, sizeof(read_buffer));
        
        rc = zms_read(&fs, 
                      1, 
                      buffer, 
                      sizeof(buffer));
        if (rc < 0) {
            printk("Failed to read data: %d\n", rc);
            return 0;
        }
        printk("Read data: %s\n", read_buffer);
        
14) 

### Use Identity Address

2) Change the start advertising code line <code>err = bt_le_adv_start(BT_LE_ADV_NCONN, ad, ARRAY_SIZE(ad), NULL, 0);</code> to the following:

	<sup>_main.c_ => in <code>bt_ready()</code> function</sup>

       err = bt_le_adv_start(BT_LE_ADV_NCONN_IDENTITY, ad, ARRAY_SIZE(ad), NULL, 0);

 > __Note:__ The key difference between <code>BT_LE_ADV_NCONN</code> and <code>BT_LE_ADV_NCONN_IDENTITY</code> lies in the Bluetooth address used during advertising. While <code>BT_LE_ADV_NCONN</code> uses a private (random) address, <code>BT_LE_ADV_NCONN_IDENTIY</code> uses the static identity address that is stored in the device FICR control registers.

> __Warning: Using a fixed identity address makes your device trackable.__
>
> Using <code>BT_LE_ADV_NCONN_IDENTITY</code> will compromise the privacy of the device. A fixed identity address (public or random static) never changes, so anyone with a Bluetooth scanner can detect and track the physical location of the device over time, since the same address always appears in the advertising packets. 


### Get the Address with Zephyr Bluetooth API

3) In the beacon application, use the Zephyr Bluetooth API to read the Bluetooth address.

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

4) Call the <code>print_bt_addr()</code> function after the Bluetooth Stack was successfully enabled.

	<sup>_main.c_ => after successful <code>bt_enable()</code> call</sup>
   
           print_bt_addr();

   
## Testing

5) Build the project and download it to your development kit.

6) Check the output in the Serial Terminal.

   ![image](images/terminal.jpg)

7) Check on Smartphone by using _nRF Connect for Mobile_ app (note that only the Anrdoid app shows the Bluetooth address when scanning).

   ![image](images/smartphone.jpg)
