# Defining own KCONFIG symbols that depends on _nRF Connect SDK_ Version

## Introduction

While it's relatively easy to create a KCONFIG symbol definition with a dependency on the Zephyr version, you'll need to pull out some tricks when querying the version of the __nRF Connect SDK__. This hands-on guide shows you how to do it.


## Required Hardware/Software

- Micro USB Cable (Note that the cable is not included in the previous mentioned development kits.)
- install the _nRF Connect SDK_ v3.4.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).
> __NOTE:__ No Development kit required for this hands-on!

## Hands-on step-by-step description 

### Create a new Project

1) Create a new project based on the "[Defining own KCONFIG symbols](../DEV_kconfig_UserDefined/)" hands-on project.

### Define new CONFIG symbols

2) Here, we define two KConfig symbols. The first (<code>CONFIG_NCS_VERSION_NUMBER</code>) is used to store the NCS version in a KConfig symbol. This requires calling a separate Python script. The second KConfig symbol (<code>CONFIG_MY_FEATURE_NEEDING_NEW_API</code>) then uses this first invisible KConfig to check the version number via a dependency.

   Add the following definition to the MyApp section.:
   
     <sup>_Kconfig_</sup>

     ``` 
     config NCS_VERSION_NUMBER
         int
         default $(shell, python C:/Nordic/lab/DEV_kconfig_checkZephyrVersion/scripts/print_ncs_version_number.py $(ZEPHYR_NRF_MODULE_DIR)/VERSION)
     
     config MY_FEATURE_NEEDING_NEW_API
         bool "My feature"
         depends on NCS_VERSION_NUMBER >= 30400
     ```

3) Here is the required Python script. Place this file in the path that is defined in the pyhton script call above.

   ```python
   import os
   import sys

   # Locate nrf/VERSION relative to this script, or hardcode/pass a path
   version_file = sys.argv[1] if len(sys.argv) > 1 else None
   if not version_file:
       sys.exit(1)
     
   values = {}
   with open(version_file) as f:
       for line in f:
           line = line.strip()
           if "=" in line:
                k, v = line.split("=", 1)
                values[k.strip()] = v.strip()
          
   major = int(values.get("VERSION_MAJOR", 0))
   minor = int(values.get("VERSION_MINOR", 0))
   patch = int(values.get("PATCHLEVEL", 0))

   print(major * 10000 + minor * 100 + patch)
   ```


## Testing

4) Create two build configurations, one using _nRF Connect SDK_ v3.3.0 and the other one _nRF Connect SDK_ v3.4.0. Build both projects.

5) Check the <code>CONFIG_MY_FEATURE_NEEDING_NEW_API</code> KCONFIG symbol in _nRF KCONFIG GUI_ tool.
   
