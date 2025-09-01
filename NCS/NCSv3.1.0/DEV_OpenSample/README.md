<sup>SDK version: NCS v3.1.0</sup>

# Getting started: Creating a new Project from existing Sample

## Introduction

The _nRF Connect SDK_ contains directories (e.g. zephyr/samples or nrf/samples) that provide various sample programs. You can open these samples directly 
in the sample directories, but this would have the disadvantage that only the modified samples would be available later if changes were made to this code. 
In order to have access to unmodified samples later, it makes more sense to copy a sample project into a separate workspace directory and then work with the copy.

The following explains how you can create your own project in your workspace folder based on an existing sample by copying an existing sample and working with the copied project in Visual Studio Code.


## Required Hardware/Software
- install the _nRF Connect SDK_ v3.1.0 and _Visual Studio Code_. The installation process is described [here](https://academy.nordicsemi.com/courses/nrf-connect-sdk-fundamentals/lessons/lesson-1-nrf-connect-sdk-introduction/topic/exercise-1-1/).


## Step-by-step description 

### Create your own project by copying an existing sample to your own Workspace

1) First, start Visual Studio Code and click on the _nRF Connect_ extension. 

   ![image](images/DEV_OpenSample/nRFConnect.jpg)

2) Then we click on _Create a new application_. 

    ![image](images/DEV_OpenSample/CreateNewApp.jpg)

3) Click on _Copy a sample_.

    ![image](images/DEV_OpenSample/CreateNewSample.jpg)

4) If you have several _nRF Connect SDK_ versions installed on your computer, you will be asked from which SDK version you would like to copy the sample project. In my case, I clicked on the latest version (v3.1.0).

  > __NOTE:__ If you only have one SDK version installed, this selection will not be shown!

   ![image](images/DEV_OpenSample/sdkVersion.jpg)

5) Now, you get a list of existing sample projects. 

    ![image](images/DEV_OpenSample/SearchSample.jpg)

6) Use the "Select a sample to crate a new application from..." text box to filter the provided list. e.g. enter "hello world"

    ![image](images/DEV_OpenSample/helloWorld.jpg)

7) While entering the search string you will se that the sample project list is automatically updated depending on your search text. We look for the "hello world" project, which is stored in folder _zephyr/samples/hello_world_. Click on this list entry.

    ![image](images/DEV_OpenSample/ClickHelloWorld.jpg)   

8) Now, you are asked to define the path where you would like to copy the sample project to. Use the folder icon to open File Explorer, which allows you to select the Workspace folder (e.g. C:/Nordic/Workspace) you would like to store this project and add the "project folder" name to this workspace (e.g. C:/Nordic/Workspace/hello_word).

    ![image](images/DEV_OpenSample/ProjectFolder.jpg)   

9) A window opens and asks if the Project should be opened in a existing VS Code ("Open") or a new VS Code window ("Open in New Window"). We click here the "Open" button.

    ![image](images/DEV_OpenSample/Open.jpg)   

10) Click on the __nRF Connect__ tab again. You should now see in the "Applications" section the copy of the "hello_world" project.

    ![image](images/DEV_OpenSample/SampleInNrfConnect.jpg)   

11) Now we need to __Add build configuration__ by clicking on the line. 

    ![image](images/DEV_OpenSample/AddBuildConfiguration.jpg)   

12) The _Add Build Configuration_ window allows us to define the settings for our project. Let's start with SDK and Toolchain version. In case you have installed several SDK versions and toolchain versions on your computer, you can select the appropriate versions. This may be helpful, because there could be several build configuration for a project.

> __NOTE:__ I focus here on the minimal settings. Further information can be found in the [nRF Connect for VS Code documnetation](https://docs.nordicsemi.com/bundle/nrf-connect-vscode/page/guides/build_config.html).

   ![image](images/DEV_OpenSample/SdkToolchain.jpg)   

13) Next we select the _Board_. Note that below the drop-down list you find filter options. Available filter may depend on your installation (e.g. is there a custom board folder). Here we select either __Nordic SoC__ or __Nordic Kits__ and look for __nRF52840DK/nRF52840__.

    ![image](images/DEV_OpenSample/BoardTarget.jpg)   

 > __NOTE:__ The board name is using Hardware Modle V2 implementation from Zephyr. This means that beside the board name, the input also includes the emulated SoC, and if available the core which is used. In above example only the board (__nRF52840DK__) and the SoC (__nRF52840__) is used.

14) Finally, we generate and build the project by scrolling down and clicking the button. 

    ![image](images/DEV_OpenSample/GenerateAndBuild.jpg)   

> __NOTE:__ By default the checkbox __Generate only__ is not selected. This means that after clicking the __Generate and Build__ button a complete build is done. This may take some time. In case you would like first change the code before downloading to a hardware you may set the tick on __Generate only__. This would speed up the project generation, because the final binaries are not generated. 

15) Now you are ready to work with the project.
