# CMake: Define a folder where header files are stored

## Introduction

Sometimes you want to store the header files in a separate directory, e.g., the _inc_ or _include_ directory. This hands-on shows how this can be done. 


## Required Hardware/Software for Hands-on
- development kit (e.g. nRF54LM20DK, nRF54L15DK, nrF54H20DK, nRF7002DK, nRF52840DK, nRF52833DK, or nRF52DK)
- install the _nRF Connect SDK_ and _Visual Studio Code_.


## Hands-on step-by-step description 

1) make a copy of one of the "Creating a Project from Scratch" project. 
2) Add a _include_ folder wihtin your project folder and create a file __my_header.h__ there.
3) The __my_header.h__ file may contain a <code>#define test "Test string"</code> definition. And in __main.c__ we add <code>printk("header: %s\n", test);</code>. 
4) A build would not find this new header file. We have to define where the build system may look for the __my_header.h__ file. This is done in __CMakeLists.txt__ file by adding following lines:

   <sup>__CMakeLists.txt__</sup>

        target_include_directories(app PRIVATE include)

  > __Note:__ this instruction add a custom header directroy for the app target. 


## Testing

5) Build the project and check the Serial Terminal output. 