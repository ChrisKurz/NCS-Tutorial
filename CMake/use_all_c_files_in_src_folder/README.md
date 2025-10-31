# CMake: Specify a folder where all *.c files will be automatically added to your project

## Introduction

In the "Creating a project from scratch" chapter, we saw how you can add *.c files to your project. However, instead of adding each C file manually, we can also define a folder, and all C files that we copy to this folder will be automatically added to our project. This chapter describes how to do this. 

## Required Hardware/Software for Hands-on
- development kit (e.g. nRF54LM20DK, nRF54L15DK, nrF54H20DK, nRF7002DK, nRF52840DK, nRF52833DK, or nRF52DK)
- install the _nRF Connect SDK_ and _Visual Studio Code_.

## Hands-on step-by-step description 

1) make a copy of one of the "Creating a Project from Scratch" project. 
2) Add in its project folder the file src/function.c. 
3) Open Visual Studio Code and add this project to your APPLICATIONS. 
4) Check in VS Code which C files were added to the project. (take a look into the project / Source files / Application / src folder)
5) Now replace in the CMakeLists.txt file the __target_sources(app PRIVATE src/main.c)__ instruction by the following one:

       FILE(GLOB app_sources src/*.c)
          target_sources(app PRIVATE ${app_sources})
                     
3) After changing the CMakeLists.txt file do a "build". Can you see the "function.c" file in your Application folder now?
4) Click on "Pristine build" and check again the src file list. 
