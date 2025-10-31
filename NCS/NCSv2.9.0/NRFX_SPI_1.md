<sup>SDK version: NCS v2.7.0  -  Link to Hands-on solution: https://github.com/ChrisKurz/nRF_Connect_SDK/tree/main/Workspace/NCSv2.7.0/NRFX_SPI_1</sup>

# NRFX Driver: SPI - Basic SPI implementation (blocking)

## Introduction

This exercise demonstrates the use of Nordic's NRFX SPI driver. A simple example is realized, which uses the SPI driver in blocking mode. 

## Required Hardware/Software
- Development kit [nRF52840DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52840-DK), [nRF52833DK](https://www.nordicsemi.com/Products/Development-hardware/nRF52833-DK), or [nRF52DK](https://www.nordicsemi.com/Products/Development-hardware/nrf52-dk), (nRF54L15DK)
- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v2.7.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).

## Hands-on step-by-step description 
We will write and read a single character via SPI. 

### Create a new Project
1) Create a new project based on Zephyr's hello_world sample. (zephyr/samples/hello_world)


### Add the NRFX Software Library
2) Add the NRFX SPI driver to the project. We will use the SPI module instance 1.

	<sup>_prj.conf_</sup>

       CONFIG_NRFX_SPI1=y

3) In order to use the SPI driver API we also need to add the corresponding header file to our _main.c_ file:

	<sup>_src/main.c_</sup>

       #include <zephyr/kernel.h>
       #include <nrfx_spi.h>

   Note: kernel.h is included here to allow usage of certain kernal specific functions, e.g. k_msleep().


### SPI initialization
4) Let's prepare the Variable that allows us to access the SPI instance:

	<sup>_src/main.c_</sup>

       #define SPI_INSTANCE  1              /**< SPI instance index. */
       static const nrfx_spi_t spi = NRFX_SPI_INSTANCE(SPI_INSTANCE);  /**< SPI instance. */

5) We prepare the structure with the configuration of the SPI module in the main function:

	<sup>_src/main.c_ => main function</sup>

           	nrfx_spi_config_t spi_config = NRFX_SPI_DEFAULT_CONFIG(28, 29,31, 30);

   Note: We choose here P0.28 for SCK, P0.29 for MOSI, P031 for MISO, and P030 for CS.

6) Let's initialize the SPI driver.

	<sup>_src/main.c_ => main() function</sup>

           nrfx_spi_init(&spi, &spi_config, NULL, NULL); 

7) Let's prepare the data that should be sent. We have to store this info in a sturcture based on _nrfx_spi_xfer_dec_t_.

	<sup>_src/main.c_</sup>

       #define TEST_STRING "A"
       static uint8_t       m_tx_buf[] = TEST_STRING;           /**< TX buffer. */
       static uint8_t       m_rx_buf[sizeof(TEST_STRING) + 1];    /**< RX buffer. */
       static const uint8_t m_length = sizeof(m_tx_buf);        /**< Transfer length. */

       nrfx_spi_xfer_desc_t txbuffer={
	            m_tx_buf,
	            m_length,
	            m_rx_buf,
	            m_length
       };

8) And finally sent the data in an entire loop in main function:

	<sup>_src/main.c_ => main() function</sup>

           	while(1)
	          {	
			           nrfx_spi_xfer(&spi, &txbuffer, 0);
                 printf("SPI write: %i\n", m_tx_buf[0];
                 printf("SPI read : %i\n", m_rx_buf[0];
   
                 nrfx_spi_xfer(&spi, &txbuffer, 0);
                 printf("SPI write: %i\n", m_tx_buf[0];
                 printf("SPI read : %i\n", m_rx_buf[0];

                 k_msleep(1000);
	          }


## Testing

9) Build and flash the application to your development kit.

10) Check the output on the Serial Terminal.

11) Check with a scope the SPI signals on pin P0.28, P0.29, P0.30 and P0.31.
