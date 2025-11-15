<sup>SDK version: NCS v1.9.0</sup>

# Bluetooth Low Energy: Beacon

## Introduction

The simplest Bluetooth Low Energy solution is to realize a beacon. The wireless MCU will be used in transmit mode only and 
it will broadcast a defined message. So we have to take care to initialize the Bluetooth stack, define the message that 
should be broadcasted, and start the broadcast. 

## iBeacon

The iBeacon specification can be found on the following webpage:
https://developer.apple.com/ibeacon/

Let's start to work on our project:

1) Create a new project. 

	a) Create the project folder in your own Workspace directory. Example:    c:/MyWorkspace/iBeacon
	
	b) Create the needed files for a minimal project setup:
	
	  _CMakeLists.txt_
	  
       cmake_minimum_required(VERSION 3.17.3)

       find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
       project(MyBeacon)

       target_sources(app PRIVATE src/main.c)
				
	_prj.conf_
	   
       CONFIG_BT=y
	
	_src/main.c_
		        
       #include <bluetooth/bluetooth.h>
 
       void main (void) {
           printk("Starting MyBeacon application!");
       }
			
2) Enable the Bluetooth Stack in the main function:

       void main(void){
           int err;
               ...
           /* Initialize the Bluetooth Subsystem */
           err = bt_enable(bt_ready);
           if (err) {
               printk("Bluetooth init failed (err %d)\n", err);
           }
               ...
       }
	      
3) Add bt_ready function to main.c file:

       static void bt_ready(int err){
           if (err) {
               printk("Bluetooth init failed (err %d)\n", err);
                return;
           }

           printk("Bluetooth initialized\n");

           /* Start advertising */
           err = bt_le_adv_start(BT_LE_ADV_NCONN, ad, ARRAY_SIZE(ad), NULL, 0);
           if (err) {
               printk("Advertising failed to start (err %d)\n", err);
               return;
           }

           printk("iBeacon started\n");
       }
	      
4) The iBeacon specification defines a advertising rate. What advertisting interval has to be set? And what advertising interval has been set in our bt_le_adv_start function call? Define an own parameter for bt_le_adv_start function and use the correct advertising interval.

5) Another parameter in bt_le_adv_start function is 'ad'. This parameter allows us to define the broadcasting message. For the iBeacon the specification defines how this message has to look like. Create a 'struct bt_data ad[]' and define the values based on iBeacon specification:

        /*  RSSI Parameter has to be calibarted. Add here RSSI level measured at 1m distance */
        #define IBEACON_RSSI 0xc8

        /*
         * Set iBeacon demo advertisement data. These values are for
         * demonstration only and must be changed for production environments!
         * UUID:  ????????-????-????-????-????????????
         * Major: ???
         * Minor: ???
         * RSSI:  -56 dBm
         */
        static const struct bt_data ad[] = {
            BT_DATA_BYTES(BT_DATA_FLAGS,BT_LE_AD_NO_BREDR|BT_LE_AD_GENERAL),  // Flags[0..3]   
            // Length - NOTE: HANDLED AUTOMATICALLY BY bt_data!
            BT_DATA_BYTES(BT_DATA_MANUFACTURER_DATA,    // Type
            , ,  // Company ID (Apple)
            , , // Beacon Type - Proximity Beacons 
            , , , ,     // Proximity UUID - UUID[15..12] 
            , ,         // Proximity UUID - UUID[11..10] 
            , ,         // Proximity UUID - UUID[9..8] 
            , ,         // Proximity UUID - UUID[7..6] 
            , , , , , , // Proximity UUID - UUID[5..0] 
            , , // Major
            , , // Minor
            IBEACON_RSSI) // Measured Power
        };
	      
Note: please create a universal unique identifier on https://www.uuidgenerator.net/

