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
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/zephyr/arch/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/zephyr/lib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/zephyr/soc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/zephyr/boards/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/zephyr/subsys/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/zephyr/drivers/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/nrf/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/hostap/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/mcuboot/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/mbedtls/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/trusted-firmware-m/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/cjson/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/azure-sdk-for-c/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/cirrus-logic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/openthread/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/memfault-firmware-sdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/canopennode/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/chre/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/lz4/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/zscilib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/cmsis/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/cmsis-dsp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/cmsis-nn/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/cmsis_6/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/fatfs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/hal_nordic/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/hal_st/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/hal_tdk/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/hal_wurthelektronik/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/liblc3/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/libmetal/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/littlefs/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/loramac-node/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/lvgl/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/mipi-sys-t/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/nanopb/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/nrf_wifi/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/open-amp/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/percepio/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/picolibc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/segger/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/uoscore-uedhoc/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/zcbor/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/nrfxlib/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/nrf_hw_models/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/modules/connectedhomeip/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/zephyr/kernel/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/zephyr/cmake/flash/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/zephyr/cmake/usage/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Nordic/Github/NCS-Tutorial/NCS/NCSv3.2.0/DEV_DeviceTree/build/DEV_DeviceTree/zephyr/cmake/reports/cmake_install.cmake")
endif()

