<sup>SDK version: NCS v3.2.0 </sup>


# Zephyr Fuel Gauge Device Drivers: Using the Fuel Gauge driver for primary batteries

## Introduction

nRF Fuel Gauge processes battery measurements made by Power Management ICs (PMICs) and provides a state-of-charge (SOC) prediction, along with other metrics. For the most accurate results, use a battery model that matches the battery used in the product.

The fuel gauge library supports primary cell (non-rechargeable) and secondary cell (rechargeable) batteries. Only primary cell support is important for the nPM2100.
Several primary cell battery models are included in the library, such as Alkaline AA, Alkaline AAA, Alkaline coin cell LR44, and Lithium-manganese dioxide coin cell CR2032 batteries. 


## Required Hardware/Software
- Development kit 
[nRF54L15DK](https://www.nordicsemi.com/Products/Development-hardware/nRF54L15-DK), 
- [nPM2100EK](https://www.nordicsemi.com/Products/Development-hardware/nPM2100-EK)
- Jumper cables
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Hands-on step-by-step description 

### Create a copy of previous project

1) Let's start with the [Bluetooth LE LED and Button services (peripheral_lbs)](https://docs.nordicsemi.com/bundle/ncs-latest/page/nrf/samples/bluetooth/peripheral_lbs/README.html) project. Make a copy of this project and rename it.


### Hardware Preparation

2) Remove the jumper P6 ("VDDM Current Measure") from the nRF54L15DK. Then use jumper wires to connect the two dev boards as follows:

   ![image](images/BoardConnections.jpg)

    | __nPM2100EK__ | <-> | __nRF54L15DK__ |
    |---------------|-----|----------------|
    | VOUT/VDDIO    | <-> |     VDD        |   
    |    GND        | <-> |     GND        |
    |    SCL        | <-> |    P1.12       |
    |    SDA        | <-> |    P1.11       |


### Update DeviceTree

3) Create a DTS overlay file: nrf54l15dk_nrf54l15_cpuapp.overlay

4) Add following lines in the DeviceTree overlay file. 

     <sup>__nRF54L15DK_nRF54L15_cpuapp.overlay__</sup>  

       &i2c21 {
           status = "okay";
           pinctrl-0 = <&i2c21_default>;
           pinctrl-1 = <&i2c21_sleep>;
           pinctrl-names = "default", "sleep";

           // list i2c attached peripherals
           npm2100ek_pmic: pmic@74 {
               compatible = "nordic,npm2100";
               reg = <0x74>;

               npm2100ek_vbat: vbat {
                   compatible = "nordic,npm2100-vbat";
               };
           };
       };

       &pinctrl {
           i2c21_default: i2c21_default {
               group1 {
                   psels = <NRF_PSEL(TWIM_SDA, 1, 11)>,
                           <NRF_PSEL(TWIM_SCL, 1, 12)>;
                           bias-pull-up;
               }; //GPIO Port 1, Pin 11 & 12
	       };
       
           i2c21_sleep: i2c21_sleep {
               group1 {
                   psels = <NRF_PSEL(TWIM_SDA, 1, 11)>,
                           <NRF_PSEL(TWIM_SCL, 1, 12)>;
                           low-power-enable;
               };
           };
       };


### Update _prj.conf_ file

5) The following KCONFIG settings are required to enable the fuel gauage library. 

     <sup>__prj.conf__</sup>  

       CONFIG_SENSOR=y
       CONFIG_NRF_FUEL_GAUGE=y
       CONFIG_NRF_FUEL_GAUGE_VARIANT_PRIMARY_CELL=y
       CONFIG_REQUIRES_FLOAT_PRINTF=y


### Add needed Code Lines to main

6) Following header files are needed. 

     <sup>__main.c__</sup>  

       #include <zephyr/kernel.h>
       #include <zephyr/device.h>
       #include <zephyr/drivers/sensor.h>
       #include <nrf_fuel_gauge.h>

7) We use following global variables for fuel gauge.

     <sup>__main.c__</sup>  

       // Global variables for fuel gauge
       static int64_t ref_time;
       static const struct device *vbat = DEVICE_DT_GET(DT_NODELABEL(npm2100ek_vbat));
       static const struct battery_model_primary FG_model = {
           #include <battery_models/primary_cell/AA_Alkaline.inc>
       };
       /* Basic assumption of average battery current.
        * Using a non-zero value improves the fuel gauge accuracy, even if the number is not exact.
        */
       static const float battery_current = 5e-3f;

8) The library has to be initialized:

     <sup>__main.c__</sup>  

       int fuel_gauge_init(const struct device *vbat)
       {
           struct nrf_fuel_gauge_init_parameters parameters = {
               .model_primary = &FG_model,
               .i0 = 0.0f,
               .opt_params = NULL,
           };
           int ret;

           printk("nRF Fuel Gauge version: %s\n", nrf_fuel_gauge_version);

           ret = read_sensors(vbat, &parameters.v0, &parameters.t0);
           if (ret < 0) {
               return ret;
           }

           ret = nrf_fuel_gauge_init(&parameters, NULL);
           if (ret < 0) {
               return ret;
           }

           ref_time = k_uptime_get();

           return 0;
       }

9) The following function is used to read the measured battery voltage and the temperature. 

     <sup>__main.c__</sup>  

       static int read_sensors(const struct device *vbat, float *voltage, float *temp)
       {
           struct sensor_value value;
           int ret;

           ret = sensor_sample_fetch(vbat);
           if (ret < 0) {
               return ret;
           }

           sensor_channel_get(vbat, SENSOR_CHAN_GAUGE_VOLTAGE, &value);
           *voltage = (float)value.val1 + ((float)value.val2 / 1000000);

           sensor_channel_get(vbat, SENSOR_CHAN_DIE_TEMP, &value);
           *temp = (float)value.val1 + ((float)value.val2 / 1000000);

           return 0;
       }

10) The _state of charge_ (SoC) is calculated periodically by calling the fuel gauge library function <code>nrf_fuel_gauge_process()</code>.

     <sup>__main.c__</sup>  

        int fuel_gauge_update(const struct device *vbat) 
        {
            float voltage;
            float temp;
            float soc;
            float delta;
            int ret;

            ret = read_sensors(vbat, &voltage, &temp);
            if (ret < 0) {
                printk("Error: Could not read from vbat device\n");
                return ret;
            }

            delta = (float)k_uptime_delta(&ref_time) / 1000.f;
            soc = nrf_fuel_gauge_process(voltage, battery_current, temp, delta, NULL);
 
            printk("V: %.3f, T: %.2f, SoC: %.2f\n", (double)voltage, (double)temp, (double)soc);

            return 0;
        }

11) Finally, in the main function we initialize the fuel gauge software and call periodically the <fuel_gauge_update()</code> function.

     <sup>__main.c__ => main() function</sup>  

           printk("nPM2100 Fuel Gauge integration on %s\n", CONFIG_BOARD_TARGET);

           if (!device_is_ready(vbat)) {
               printk("vbat device not ready.\n");
               return -1;
           }
           printk("PMIC device ok, init fuel gauge\n");

           err = fuel_gauge_init(vbat);
           if (err < 0) {
               printk("Could not initialise fuel gauge.\n");
               return -1;
           }
           printk("Fuel gauge initialised using model %s\n", FG_model.name);
           // other initialisation functions

           // main infinite loop
           while (1) {
               fuel_gauge_update(vbat);
               k_msleep(1000);
           }


## Testing

12) Build and download the project.
13) Start Serial Terminal and check the output.
