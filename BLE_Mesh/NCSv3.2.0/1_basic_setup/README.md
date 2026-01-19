<sup>SDK version: NCS v2.3.0  -  Link to Hands-on solution: TBD</sup>

# Bluetooth Mesh: Creating a Bluetooth Mesh basic template application from scratch

## Introduction

Let's start with preparing a basic setup for a Bluetooth Mesh solution. There are some mandatory functions that we need to include in our project. We will do that in this excercise.

Here we focus on running the complete Bluetooth LE and Mesh stack on the same CPU. To use Bluetooth mesh with a separate Bluetooth controller, additional settings are required. 

## Required Hardware/Software
- two (or three) nRF52 development kit (e.g. nRF52DK, nRF52833DK, or nRF52840DK)
- a smartphone ([Android](https://play.google.com/store/apps/details?id=no.nordicsemi.android.mcp&hl=de&gl=US&pli=1) or [iOS](https://apps.apple.com/de/app/nrf-connect-for-mobile/id1054362403)), which runs the __nRF Connect__ app 

  We also need the Bluetooth Mesh app (for [Android](https://play.google.com/store/apps/details?id=no.nordicsemi.android.nrfmeshprovisioner&hl=de&gl=US) or [iOS](https://apps.apple.com/de/app/nrf-mesh/id1380726771))
   
- install the _nRF Connect SDK_ v2.3.0 and _Visual Studio Code_. The description of the installation can be found [here](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/2.3.0/nrf/getting_started/assistant.html#).

## Hands-on step-by-step descrition 

### Create the project (copy existing sample)

1) Let's start with the [__blinky__ sample](https://developer.nordicsemi.com/nRF_Connect_SDK/doc/latest/zephyr/samples/basic/blinky/README.html). Copy the __blinky__ sample folder into your own Workspace folder. It can be found in the following _nRF Connect SDK_ folder: <_nRF Connect SDK_ install folder> /v2.3.0/zephyr/samples/basic/blinky

  > __NOTE:__ A simple way is to use the _Visual Studio Code_ extension _nRF Connect_ and its __Create a new application__.

2) After you have added the project to _Visual Studio Code_, add the build configuration. 


### Add Files to Project
We could put all the Bluetooth Mesh-specific code in the main.c file, as is often done in the Zephyr and nRF Connect SDK samples. To make this Bluetooth Mesh project easier to reuse in other projects, we will place the Bluetooth Mesh code in its own C file. 

3) We will split the code into following parts:
   - __main.c__: This is the main application that processes the application-specific parts. It has also started the Bluetooth mesh stack. 
   - __App_BTMesh.c__: this file contains the complete Bluetooth Mesh application code. 

   So add these C files to the _src_ folder. And also create the appropriate __App_BTMesh.h__ header files. The file structure should look like this:

   ![image](images/01_ProjectFiles.jpg)

4) We have to add these files to our project. This is done by adding following lines to the __CMakeLists.txt__ file and its __target_sources()__ definition. 

   <sup>_CMakeLists.txt_</sup>    
   
                   src/App_BTMesh.c
                   

   So the __CMakeLists.txt__ file should look like this:
   
   ![image](images/01_CMakeLists.jpg)

5) You should see the files in your project after doing a _build_ in Visual Studio Code. 

   ![image](images/01_VscProject.jpg)

### Enable debug capability by activating Zephyr Logging

6) Zephyr Logging allows to send debug messages during runtime via UART or Debug interface. We will use this feature to get debug messages, which allows us to check correct execution of our code. 

   First, we have to add following CONFIGs to our prj.conf file:
   
   <sup>_prj.conf_</sup>
   
       # Zephyr Logging
       CONFIG_LOG=y   

7) We want to handle the Logging in our Bluetooth Mesh implementation. So we have to register Logging in App_BTMesh.c file and declare it in the other files. 

   Let's add the Logging registration to App_BTMesh.c file:

   <sup>_src/App_BTMesh.c_</sup>

       #include <zephyr/logging/log.h>
       /** LOG MODULE REGISTRATION:
           - First parameter: module name
           - Second Parameter (optional): log level
                Following Log-Levels can be used:
                    LOG_LEVEL_NONE  => OFF:     log will not be active. 
                    LOG_LEVEL_ERR   => ERROR:   write only LOG_ERR messages
                    LOG_LEVEL_WRN   => WARNING: write LOG_WRN and LOG_ERR messages
                    LOG_LEVEL_INF   => INFO:    write LOG_INF, LOG_WRN, and LOG_ERR 
                                                messages
                    LOG_LEVEL_DBG   => DEBUG:   write LOG_DBF, LOG_INF, LOG_WRN, and 
                                                LOG_ERR messages
       **/
       LOG_MODULE_REGISTER(MyApp_BTMesh, LOG_LEVEL_INF);


### Add Bluetooth LE functionality

8) Bluetooth Mesh is based on Bluetooth LE. Or in other words: Bluetooth Mesh uses Bluetooth LE as a transport layer. Therefore we will first activate Bluetooth LE.

   <sup>_prj.conf_</sup>
   
       # Bluetooth LE
       CONFIG_BT=y   

9) Bluetooth Mesh uses _advertising_ and _scanning_ to receive and transmit message. So we need to support _broadcasting_ and _observer_ roles. In our project we will use a smartphone for provisioning. To allow this, we have to enable the GATT provision bearer, which is using peripheral role. 

   <sup>_prj.conf_</sup> 

       #--- Bluetooth Roles
       CONFIG_BT_BROADCASTER=y
       CONFIG_BT_OBSERVER=y
       CONFIG_BT_PERIPHERAL=y


10) We have to include the bluetooth header file. Add following line in __App_BTMesh.c__:

   <sup>_src/App_BTMesh.c_</sup>   

    #include <zephyr/bluetooth/bluetooth.h>

11) And we have to enable the Bluetooth stack by adding following function:

    <sup>_src/App_BTMesh.c_</sup>


        /*===========================================================================*/
        /*---  Bluetooth Mesh Initialization                                         */
        void app_btmesh_start(void) {
            int err;

            /* Initialize the Bluetooth Subsystem */
            err = bt_enable(NULL);
            if (err) {
                LOG_ERR("Bluetooth init failed (error %d)", err);
                return;
            }
            LOG_INF("Bluetooth initialized");
        }

12) This function will be used to allow main code to initialize Bluetooth LE as well as Bluetooth Mesh. So we have to declare it in the header file:
   
    <sup>_src/App_BTMesh.h_</sup>
   
        void app_btmesh_start(void);   
   
13) The function __app_btmesh_start()__ is not yet complete. We will add further code later on. However, let's add the line in main.c file that calls this initialization code. First, include the header file to main.c:

   <sup>_src/main.c_</sup>

    #include "App_BTMesh.h"
   
14) And then call the init function in main() function - just before entire loop:
   
   <sup>_src/main.c_ => main() function</sup>

        /* Initialize and start Bluetooth Mesh */
        app_btmesh_start();


### Enable Bluetooth Mesh 

15) Now, add Bluetooth Mesh to your project:

   <sup>_prj.conf_</sup>
   
    # Bluetooth Mesh
    CONFIG_BT_MESH=y

16) We have to include the Bluetooth Mesh header file. This allows us to use the appropriate Bluetooth Mesh functions. 

	<sup>_src/App_BTMesh.c_</sup>

        #include <zephyr/bluetooth/mesh.h>

17) Initialize the Bluetooth Mesh after Bluetooth LE was successfully enabled. 

	<sup>_src/App_BTMesh.c_ => app_btmesh_start() function</sup>
   
            err = bt_mesh_init(&prov, &comp);
            if (err) {
                LOG_ERR("bt_mesh_init failed with error %d", err);
                return;
            }
            LOG_INF("Bluetooth Mesh initialised");

   > __NOTE:__ The function call _bt_mesh_init()_ initializes Bluetooth Mesh support. However, the node will not automatically advertise as unprovisioned. Another API function call will be added later, which starts advertisement.

   > __NOTE:__ _prov_ and _comp_ are node provisioning information and node composition. We will define these parameters during the next steps. 

18) Finally, we start the Bluetooth mesh stack here, which also starts advertising for provisioning.

	<sup>_src/App_BTMesh.c_ => app_btmesh_start() function</sup>

	/* This will be a no-op if settings_load() loaded provisioning info */
	bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);


#### Define Device Name and enable Provisioning Bearer

19) Let's define a Device Name, which allows us to easier find the device. 

   <sup>_prj.conf_</sup>
   
    CONFIG_BT_DEVICE_NAME="My Mesh Device"

20) A Provisioning Bearer enables the transportation of provisioning information between a Provisioner and an unprovisioned device. Two Provisioning Bearers are defined in the Bluetooth Mesh standard:

- __Advertising Provisioning Bearer (PB-ADV):__ This provisioning bearer is used to provision a device over the Bluetooth advertising channels. The PB-ADV bearer is used for transmitting Generic provisioning PDUs. A device supporting PB_ADV should perform passive scanning with a duty cycle as close to 100% as possible in order to avoid missing any incoming Generic Provisioning PDUs.

- __GATT Provisioning Bearer (PB-GATT):__ This provisioning bearer is used to provision a device using Bluetooth mesh Proxy PDUs from the proxy protocol. The proxy protocol enables nodes to send and receive network PDUs, mesh beacons, proxy configuration messages, and provisioning PDUs over a connection-oriented, Bluetooth LE bearer. PB-GATT encapsulates provisioning PDUs within GATT operations, involving the GATT provisioning service and it is provided for use when a provisioner does not support PB-ADV. 

   Setting the following CONFIG allows the device to be provisioned over GATT.

   <sup>_prj.conf_</sup>

      # Bluetooth Mesh Device Roles
      CONFIG_BT_MESH_GATT_PROXY=y
      
      # Bluetooth Mesh Provision Bearer
      CONFIG_BT_MESH_PB_GATT=y


#### Node Provisioning Information

Provisioning is the secure process of adding an "unprovisioned device" to a Bluetooth mesh network, thereby transforming it into a "node". This is a mandatory step for any device to participate in mesh communication. 

Provisioning typically follows a standardized five-step sequence: 
- __Beaconing__: The unprovisioned device broadcasts "Unprovisioned Device Beacons" (via PB-ADV) or advertises a Mesh Provisioning Service (via PB-GATT) to indicate it is ready to be added.
- __Invitation__: The provisioner (usually a smartphone or tablet) scans for these beacons and sends an invitation to start the process.
- __Public Key Exchange__: The devices exchange public keys (ECC Diffie-Hellman) to establish a secure channel.
- __Authentication__: The provisioner verifies the identity of the device using Out-of-Band (OOB) methods, such as entering a code displayed on the device (Output OOB) or flashing an LED.
- __Provisioning Data Transfer__: Once authenticated, the provisioner securely sends essential network data to the device.

In step 17, we used the _bt_mesh_init()_ function. _bt_mesh_init()_ in Bluetooth Mesh initializes the mesh stack using the __prov__ (provisioning information) and __comp__ (composition data) structures as parameters. __prov__ defines the node identity/OOB data for joining. And __comp__ describes the elements and models of the node, both of which are essential for the node's function and its detection in the network after provisioning by a provisioner. 

21) Let's start and define the __prov__ structure. We add this before the _bt_mesh_init()_ function call:
   
 <sup>_src/App_BTMesh.c_</sup>

    /*===========================================================================*/
    /*---  Provisioning                                                          */

    /* Node provisioning information (properties and capabilities) */
    const struct bt_mesh_prov prov = {
           .uuid = dev_uuid,
    //       .uri = ,
    //       .oob_info = ,
    //       .public_key_be = ,
    //       .private_key_be = ,
    //       .static_val = ,
    //       .static_val_len = ,
           .output_size = 4,
           .output_actions = BT_MESH_DISPLAY_NUMBER,
    //       .input_size = ,
    //       .input_actions = ,
    //       .capabilities = ,
    #if defined CONFIG_BT_MESH_PROV_OOB_API_LEGACY
    //       .output_number = ,
    #else
           .output_numeric = provisioning_output,
    #endif
    //       .output_string = ,
    //       .input = ,
    //       .input_complete = ,
    //       .unprovisioned_beacon = ,
    //       .unprovisioned_beacon_gatt = ,
    //       .link_open = ,
    //       .link_close = ,
           .complete = provisioning_complete,
    //       .node_added = ,
           .reset = provisioning_reset,
    };

   Most of the definitions are not used here. We focus on the basic implementation. Here is a short description of the used parameters:
   - __.uuid__: The UUID that's used when advertising as unprovisioned. 
   - __.output_actions__: Supported output OOB actions. The Bluetooth Mesh stack includes already different possibilities for provisioning output authentication. In this example we select to display a number. (we will send this number via UART to the terminal program)
   - __.output_size__: Maximum size of output OOB supported. In our case this is the number of digits used for provisioning authentication.
   - __.output_number__: This callback function is used to notify the application that it should output the given number. 
   - __.complete__: This callback function is used to inform the application that provisioning has been successfully completed, and that the local node has been assigned the specified NetKeyIndex and primary element address.
   - __.reset__: This callback function is used to inform the application that the local node has been reset and needs to be reprovisioned. The node will not automatically advertise as unprovisioned.

22) __.uuid__ defines a UUID that will be used during advertising. UUIDs can be generated by using tools like https://www.uuidgenerator.net/. In our example here I will use a simple UUID, just for demonstration purpose. In a real product the UUID has to be changed.

 <sup>__src/App_BTMesh.c__ - _Provisioning_ section </sup>

    // device UUID
    static const uint8_t dev_uuid[16] = { 
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };

23) We have defined several callback functions in step 20. Let's add the function the outputs the number for provisioning authentication, the provisioning complete function, and the reset function. 

 <sup>_src/App_BTMesh.c_</sup>

    static int provisioning_output(bt_mesh_output_action_t action, uint8_t *number, size_t size) {
        LOG_INF("OOB Number: %u", number);
        return 0;
    }

    static void provisioning_complete(uint16_t net_idx, uint16_t addr) {
        LOG_INF("Provisioning completed. NetKeyIndex and primary element address has been assigned.");
        LOG_INF("                      => NetKeyIndex: 0x%04x",net_idx);
        LOG_INF("                      => Primary element address: 0x%04x",addr);
    }

    static void provisioning_reset(void){
        LOG_INF("Node has been reset.");
        bt_mesh_prov_enable(BT_MESH_PROV_ADV | BT_MESH_PROV_GATT);
    }

   > __NOTE:__ In our example we want to use the smartphone to add devices to the network. This requires to enable __BT_MESH_PROV_GATT__. 


#### Node Composition

24) The parameter __comp__ is also mentioned in step 17. So let's add the definition of the node composition. Here we define the Mesh Models that are used in our device. For the basic setup we have to use the mandatory health model and the configuration server.  

 <sup>_src/App_BTMesh.c_</sup>

    /*===========================================================================*/
    /*---  Node Composition                                                      */
        
    /* Models - an array of specific model definitions */
    static struct bt_mesh_model sig_models[] = {
        BT_MESH_MODEL_CFG_SRV,
        BT_MESH_MODEL_HEALTH_SRV(&app_health_srv, &health_pub),
    };
    
    /* Elements - contains array of SIG models and vendor models (none in this case) */
    static struct bt_mesh_elem elements[] = {
        BT_MESH_ELEM(
            0,                                /**< Location Descriptor */
            sig_models,                       /**< Array of SIG models */
            BT_MESH_MODEL_NONE                /**< Array of vendor models (none in this case) */
        ),    
    };
    
    /* Node composition - contains an array of elements */
    const struct bt_mesh_comp comp = {
        .cid = 0xFFFF,                        /**< Company Identifier assigned by Bluetooth SIG (https://www.bluetooth.com/specifications/assigned-numbers/) */
        .pid = 0x1234,                        /**< Vendor-assigned Product Identifier */
        .vid = 0x0001,                        /**< Vendor-assigned Version Identifier */
        .elem = elements,                     /**< List of elements */
        .elem_count = ARRAY_SIZE(elements),   /**< Number of elements in this device */
    };

   NOTE: The Configuration Server (__BT_MESH_MODEL_CFG_SRV__) is mandatory on all Bluetooth Mesh modes, and should be instantiated in the first element. And the health server is also mandatory and has to be added to the primary element. It can also be part of the secondary elements as well.  
   
   NOTE: The Company Identifier is an assigned number by Bluetooth SIG. __.cid__ has to be updated and you should use your assigned number here.


#### Configuration Server

25) In this step, we define the Bluetooth mesh role to be assigned to this device. The following figure shows a typical mesh network topology and its node types.

 ![image](images/TopologyAndRoles.jpg)

   In our example here, we choose a simple node without additional functionalities such as relay, friend, or low power.

 <sup>_prj.conf_</sup>

    #--- Initial Configuration Server Settings
	
    # Bluetooth Mesh Device Roles
	#... All nodes can receive and transmit mesh messages. In addition, a node may possess special capabilities as 
	#... optional features. 
	#... Four optional features (roles) are available for Bluetooth Mesh nodes:
	#...  - Relay
    CONFIG_BT_MESH_RELAY=n
    CONFIG_BT_MESH_RELAY_ENABLED=n
    #...  - Friend
	CONFIG_BT_MESH_FRIEND=n
    CONFIG_BT_MESH_FRIEND_ENABLED=n
	#...  - Low Power
	CONFIG_BT_MESH_LOW_POWER=n
    #...  - Proxy
	CONFIG_BT_MESH_GATT_PROXY=y     #**< note that we have set this one already in step 19
    #...

26) Setting the initial values of Configuration Server is done via KCONFIG:

 <sup>_prj.conf_</sup>

	CONFIG_BT_MESH_BEACON_ENABLED=y
	
	# Settings
        CONFIG_BT_MESH_DEFAULT_TTL=7
        CONFIG_BT_MESH_NETWORK_TRANSMIT_COUNT=2
        CONFIG_BT_MESH_NETWORK_TRANSMIT_INTERVAL=20
        #------


#### Health Server

27) Let's add the Health Server model definition to the __App_BTMesh_HealthServer.c__ file:

    <sup>_src/App_BTMesh.c_</sup>

        /*===========================================================================*/
        /*---  Bluetooth Mesh Model:  Health Server                                  */
        
        BT_MESH_HEALTH_PUB_DEFINE(health_pub, 0);
	
        const struct bt_mesh_health_srv_cb health_srv_cb = {
        //    .fault_get_cur = ,          /**< Callback for fetching current faults */
        //    .fault_get_reg = ,          /**< Callback for fetching all registered faults */	    
        //    .fault_clear = ,            /**< Clear all registered faults associated with the given Company ID */
        //    .fault_test = ,             /**< Run a self-test
            .attn_on = attention_on,    /**< Start calling attention to the device */
            .attn_off = attention_off,  /**< Stop the attention state */
        };
	
        struct bt_mesh_health_srv app_health_srv = {
        //    .model = ,                  /**< Composition data model entry pointer */
            .cb = &health_srv_cb,       /**< Optional callback structure */
        //    .attn_timer = ,             /**< Attention Timer state */
        };


28) We have already added the health server to the node composition in step 25. However, the appropriate functions for starting and stopping attention were not yet added. 

   > __Note:__ “Bluetooth Mesh Attention” refers to the ability of devices in a Bluetooth Mesh network to attract attention, e.g. by flashing or beeping, often during provisioning or for status indication (health models), whereby a defined time span (TTL) is set for the attention to improve user-friendliness and troubleshooting.

    <sup>_src/App_BTMesh.c_</sup>

        static void attention_on(const struct bt_mesh_model *model) {
            LOG_INF("Attention on");
        }

        static void attention_off(const struct bt_mesh_model *model) {
            LOG_INF("Attention off");
        }
	

## Testing

28) build the project and download to a dev kit. Open Serial Terminal and check output.

29) use __nRF Mesh__ app on a smartphone and add the Bluetooth Mesh node to a network.

