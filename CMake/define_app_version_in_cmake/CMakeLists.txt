# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

# Set project name:
project (MyApp
         VERSION 2.3.4.5)
		 
# Configure a header file to pass the version number to the source code
configure_file(AppVersion.h.in include/AppVersion.h)		 
	
# add include directroies to the build
include_directories(MyApp PUBLIC "${PROJECT_BINARY_DIR}/include")

target_sources(app PRIVATE src/main.c)
