<sup>SDK version: NCS v3.2.0</sup>

# Command Line Tool: west - Installation and Update

## Introduction

The Zephyr project includes a swiss-army knife command line tool named (west)[https://docs.nordicsemi.com/bundle/ncs-latest/page/zephyr/develop/west/index.html#west-name]. West is developed in its own (repository)[https://github.com/zephyrproject-rtos/west].

West is written in Python 3 and distributed through (PyPI)[https://pypi.org/project/west/]. Use pip3 to install or upgrade west:

> __Note:__ Here we focus on Windows only.


## Required Hardware/Software
- install the _nRF Connect SDK_ v3.2.0 and _Visual Studio Code_. 


## Step-by-step description 

### Installing west

1) Open Command line window (cmd.exe) on your computer. 

2) Use __pip3__ to install or upgrade west. 

       pip3 install -U west

3) Afterwards, you can run the following command for information on where the west binary and related files were installed.

       pip3 show -f west 


### Updating west

4) Check the installed west version.

       west -V

   or

       west --version

5) Updating west is done with the same instruction that is used for installation.

       pip3 install -U west
