# --- WORK IN PROGRESS!!! ---
-----
# Bluetooth Low Energy: Security - Privacy

## Introduction

Normally, a Bluetooth device has a fixed address. If this address never changes, anyone can track the device over time. Bluetooth Privacy solves this problem by periodically generating temporary addresses called _Resolvable Private Addresses (RPA)_. An RPA changes automatically, cannot be tracked easily, and can still be resolved by trusted bonded devices. 

This project demonstrates how to use Bluetooth Low Energy Privacy in the Nordic Semiconductor _nRF Connect SDK_. 


## Required Hardware/Software

- Development kit 
[nRF54LM20DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54LM20-DK),
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
[nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), 
[nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or 
[nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk) 
- install the _nRF Connect SDK_ v3.3.0 and _Visual Studio Code_.


## Hands-on step-by-step description

### Let's start with the existing example

1) Make a copy of the project [DIS Service](../peripheral_service_DIS). 


### Configure Bluetooth Privacy

2) Let's add the needed KCONFIG symbols to prj.conf file.

  <sup>__prj.conf__</sup>

    # Enable bonding support
    CONFIG_SETTINGS=y
    CONFIG_BT_SETTINGS=y

    # Enable SMP pairing
    CONFIG_BT_SMP=y

    # Enable privacy feature
    CONFIG_BT_PRIVACY=y

    # Number of Bluetooth identities
    CONFIG_BT_ID_MAX=1

3) To use the settings library, we habe to include the settings.h file.

  <sup>__main.c__</sup>   

    #include <zephyr/settings/settings.h>

4) Before we start advertising, add following lines.

  <sup>__main.c__</sup>   

         /* Load stored settings. 
          * Required for bonding information and IRKs. 
          */
         settings_load();

> __Note:__ The <code>settings_load()</code> function loads bonding information, IRKs, and identity data. This is needed for Bluetooth LE Privacy. Without stored IRKs, trusted devices cannot resolve RPAs.

5) Add following while loop in main() function to read current address and output on Serial Terminal. 

  <sup>__main.c__</sup>   
  
         while (1) {
             /*
              * Print current identity address.  
              *  
              * With privacy enabled, 
              * this address changes periodically. 
              */ 
             bt_addr_le_t addr; 
             size_t count = 1; 
            
             bt_id_get(&addr, &count); 
            
             char addr_str[BT_ADDR_LE_STR_LEN]; 
            
             bt_addr_le_to_str(&addr, addr_str, sizeof(addr_str)); 
            
             printk("Current address: %s\n", addr_str); k_sleep(K_SECONDS(30)); 
         }


### Adding Passkey Handling 

6) When a successful connection was done, we request higher security level.

  <sup>__main.c__</sup>   

        /* 
         * Request security level 2. 
         * 
         * This triggers pairing if needed. 
         * 
         * Security level 2: 
         * - Encryption enabled 
         * - Unauthenticated pairing 
         * 
         * Level 3 would require authenticated pairing. 
         */ 
        err = bt_conn_set_security(conn, BT_SECURITY_L2); 
        if (err) { 
            printk("Failed to set security (err %d)\n", err); 
        } else { 
            printk("Security requested\n"); 
        }

7) Let's add the security_changed callback function.
   
  <sup>__main.c__</sup>   

    /* 
     * Callback called when security changes. 
    */ 
    static void security_changed(struct bt_conn *conn, bt_security_t level, enum bt_security_err err) 
    { 
        if (err) 
        { 
            printk("Security failed (err %d)\n", err);
        } else { 
            printk("Security changed: level %u\n", level);
        }
    } 
    
    /*
     * Register connection callbacks. 
    */ 
    BT_CONN_CB_DEFINE(conn_callbacks) = {
        .connected = connected, 
        .disconnected = disconnected, 
        .security_changed = security_changed, 
    };

> __Note:__ The definition of connected and disconnected callback function exists already in the DIS sample. Replace it by the definition used above.

8) Let's add the handling of the passkey.

  <sup>__main.c__</sup>   

    /*
     * Display passkey callback. 
     * 
     * Called when the stack wants to display 
     * a passkey to the user. 
     */ 
    static void passkey_display(struct bt_conn *conn, unsigned int passkey) 
    { 
        char addr[BT_ADDR_LE_STR_LEN]; 
        bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr)); 
        printk("Passkey for %s: %06u\n", addr, passkey);
    } 
    
    /* 
     * Pairing complete callback. 
     */ 
    static void pairing_complete(struct bt_conn *conn, bool bonded) 
    {
        char addr[BT_ADDR_LE_STR_LEN]; 
        bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr)); 
        printk("Pairing completed with %s, bonded: %d\n", addr, bonded); 
    } 
    
    /*
     * Pairing failed callback. 
     */ 
    static void pairing_failed(struct bt_conn *conn, enum bt_security_err reason) 
    {
        char addr[BT_ADDR_LE_STR_LEN]; 
        bt_addr_le_to_str(bt_conn_get_dst(conn), addr, sizeof(addr)); 
        printk("Pairing failed with %s, reason %d\n", addr, reason); 
    } 
    
    /*
     * Authentication callbacks. 
     * 
     * These handle passkey display and pairing. 
     */ 
    static struct bt_conn_auth_cb auth_cb_display = { 
        .passkey_display = passkey_display,
    }; 
    
    /* * Pairing information callbacks. */ static struct bt_conn_auth_info_cb auth_info_cb = { .pairing_complete = pairing_complete, .pairing_failed = pairing_failed, };


   
## Testing

6) Build the project and download it to your development kit.

7) Check the output in the Serial Terminal.

   ![image](images/terminal.jpg)
