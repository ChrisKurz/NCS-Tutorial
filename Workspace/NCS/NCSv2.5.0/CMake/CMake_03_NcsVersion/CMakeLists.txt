# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

# Check NCS Version
set(NRF $ENV{ZEPHYR_BASE}/../nrf/)
file(READ "${NRF}/VERSION" version)
message("Used nRF Connect SDK Version: "${version})

set (ExpectedNcsVersion "2.4.0")

if(NOT version VERSION_EQUAL ExpectedNcsVersion)
   message(FATAL_ERROR "Incorrect nRF Connect SDK version! Please use nRF Connect SDK Version: "${ExpectedNcsVersion})
endif()

# Find external Zephyr project, and load its settings:
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Set project name:
project (MyApp)

# add sources
target_sources(app PRIVATE src/main.c)             