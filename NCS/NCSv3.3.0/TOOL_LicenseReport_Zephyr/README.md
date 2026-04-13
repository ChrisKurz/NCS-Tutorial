# Getting started: Generating a License Report

## Introduction

At some point in your development process you will probably also be concerned about the different licenses of the software you are using. In addition to Nordic’s solution, Zephyr also offers a similar solution. This tool scans comments containing SPDX license identifiers in source files and then lists them in the generated SPDX documents. It generates SPDX tag-value documents and establishes relationships between source files and the corresponding generated build files.

Further details about licenses can be found [here](https://docs.nordicsemi.com/bundle/ncs-latest/page/nrf/dev_model_and_contributions/licenses.html) and information about the Zephyr _Software Bill of Materials_ tool can be found [here](https://docs.nordicsemi.com/bundle/ncs-3.1.0/page/zephyr/develop/west/zephyr-cmds.html#software_bill_of_materials_west_spdx). 


## Required Hardware/Software
- install the _nRF Connect SDK_ v3.3.0 and _Visual Studio Code_. 


## Step-by-step description 

1) Before we build the project, we first need to set up the build directory. We do this using the following command-line instruction:

       west spdx --init -d build_sbom/< project name >

   > __Note:__ Replace <code>< project name ></code> with your own project name. For example, if a <code>hello_world</code> project includes MCUBoot, then both the <code>hello_world</code> and <code>mcuboot</code> projects would be found within this SYSBUILD project. In that case, we would use <code>hello_world</code> as the < project name >. 

2) Now, let's build the project. However, we have to set CONFIG_BUILD_OUTPUT_META=y to generated the required data during build.

       west build -d buld_sbom -b nrf54l15dk/nrf54l15/cpuapp -- -DCONFIG_BUILD_OUTPUT_META=y

3) And finally, we generate the SPDX documents based on this build directory.

       west spdx -d build_sbom


This generates the following SPDX bill-of-material (BOM) documents in <code>build_som/spdx</code> folder:
- __app.spdx__: BOM for the application source files used for the build
- __zephyr.spdx__: BOM for the specific Zephyr source code files used for the build
- __build.spdx__: BOM for the built output files
- __modules-dpes.spdx__: BOM for the modules dependencies.

> __Note:__ Above command line instructions generate SPDX documents covering compiled source code files (e.g. <code>.c</code>, <code>.s</code>). Header files can be included by using <code>--analyze-includes</code> in the <code>west spdx -d build_sbom</code> instruction.

Further information can be found here:
- [EmbeddedOSSummit: "Practical SBOM Management with Zephyr and SPDX"](https://zephyrproject.org/practical-sbom-management-with-zephyr-and-spdx-benjamin-cabe-the-linux-foundation/)
