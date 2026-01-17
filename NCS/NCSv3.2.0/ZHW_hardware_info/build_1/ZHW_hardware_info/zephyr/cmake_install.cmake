# Install script for directory: C:/Nordic/NCS/v3.2.0/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Zephyr-Kernel")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/Nordic/NCS/toolchains/66cdf9b75e/opt/zephyr-sdk/arm-zephyr-eabi/bin/arm-zephyr-eabi-objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/cmsis_6/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/hal_tdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/nrf_wifi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/percepio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/ZHW_hardware_info/build_1/ZHW_hardware_info/zephyr/cmake/reports/cmake_install.cmake")
endif()

