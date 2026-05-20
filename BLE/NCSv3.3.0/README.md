# nRF Connect SDK: Bluetooth 

There are step-by-step instructions for different versions of the _nRF Connect SDK_ (NCS). Older versions can be found in the corresponding GitHub directory named after the corresponding NCS version, e.g. NCSv3.0.0.  

The _nRF Connect SDK_ version used here is NCS version 3.3.0.

--------

## Table of Content

- [Broadcast and Advertising](#broadcast_and_advertising)

- [Peripheral](#peripheral)
--------

### Broadcast and Advertising

- [__iBeacon__](basics_beacon/README.md) - initialize Bluetooth stack and realize a broadcaster
- [__Advertising Interval__](basics/beacon_advInterval/README.md) - measure and adjust the Advertising Interval

### Peripheral

#### Generic Features

- [__Switch to 2M PHY__](peripheral_2mphy/README.md)

#### Security

- [__Enable Security within a connection and use a random passkey__](peripheral_security/README.md)
- [__Enable Security within a connection and use a static passkey__](peripheral_security_StaticPasskey/README.md)

#### Services

##### User-defined Services
- [__Custom Service using "Read"__](peripheral_service_custom_read/README.md) - "Read" data transfer operation
- [__Custom Service using "Write"__](peripheral_service_custom_write/README.md) - "Write" (with acknowledge) data transfer operation
- [__Custom Service using "Write without Response"__](peripheral_service_custom_writeWithoutResponse/README.md) - "Write without Response" (without acknowledge) data transfer operation
- [__Custom Service using "Notification"__](peripheral_service_custom_notification/README.md) - "Notification" data transfer operation (without acknowledge)
- [__Custom Service using "Indication"__](peripheral_service_custom_indication/README.md) - "Indication" data transfer operation (with acknowledge)

##### Bluetooth Services
- [__Bluetooth SIG-defined service: Battery Servcie (BAS)__](peripheral_service_BAS/README.md)
- [__Bluetooth SIG-defined service: Device Information Service (DIS)__](peripheral_service_DIS/README.md)
- [__Bluetooth SIG-defined service: Immediate Alert Service (IAS)__](peripheral_service_IAS/README.md)



