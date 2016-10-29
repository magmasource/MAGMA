# MELTS software #

**MELTS** is a software package designed to facilitate thermodynamic modeling of phase equilibria in magmatic systems. It provides the ability to compute equilibrium phase relations for igneous systems over the temperature range 500-2000 °C and the pressure range 0-2 GPa.

**[PhasePlot](https://gitlab.com/ENKI-portal/PhasePlot)** and **[ThermoFit](https://gitlab.com/ENKI-portal/ThermoFit)** are additional software repositories of Objective-C code that implement the MELTS thermodynamic models and CT engine. 

 
For additional documentation, visit the [MELTS website](http://melts.ofm-research.org/index.html). There you can find preconfigured executables for MacOS and Ubuntu platforms.



## Building the software (MacOS or Linux) ##

This README focuses on the following build targets:

- Standalone rhyolite-MELTS (v 1.0.2, 1.1.x, 1.2.x)  and pMELTS (v 5.6.1)
- Command-line auxillary and testing programs
- Static and dynamic libraries encapsulating the MELTS CT engine

:point_right: To build the Python package that encapsulates the MELTS CT engine (OS agnostic) and to access associated Python notebooks and examples, refer to the [README file in the python subdirectory](https://gitlab.com/ENKI-portal/xMELTS/blob/master/python/README.md).

:point_right: For MacOS build targets configured with Xcode, simply open the project file, `MELTS.xcodeproj`, in Xcode and follow the instructions [Building Xcode targets in the MELTS project ](https://gitlab.com/ENKI-portal/xMELTS/blob/master/XCODE-README.md)(XCODE-README.md).


### Cloning the repository and populating the submodules ###
The default **master** branch of the respository tracks the stable public releases of MELTS software. The **develop** branch tracks the latest development code and may contain unpublished features.  You can fork either branch when you clone the repository. Make sure to follow *GitFlow* protocols and to fork feature and extension branches only from the **develop** branch.

When you clone the repository, the **master** branch is tracked by default. If you use a git client, such as [Tower](https://www.git-tower.com/), the client also populates the port3 submodules (i.e., subrepositories) required to perform the build procedures.

If you use command-line git instead of a git client, you must execute the following command in a terminal window after migrating to the project directory:
```
git submodule update --init --recursive
```
This command clones and populates the port3 submodule.

With command-line git, you can track the **develop** branch with this command:
```
git pull origin develop
```
Also, you can subsequently check out the **develop** branch, making it the HEAD branch, with this command:
```
git checkout develop
```


### Prerequisites ###
To build the standalone (GUI) version of MELTS on MacOS or Linux, you need the following additional system and software resources:

- PORT3 software library, available as a [submodule in the xMELTS git repository](https://gitlab.com/ENKI-portal/port3)
- An X11 installation that includes the package `openmotif`
- A C compiler (preferably clang, but [GCC](https://www.amazon.com/gp/product/B00SWS1KWO/ref=ox_sc_act_title_1?ie=UTF8&psc=1&smid=AAZG7FJ20LXBR) suffices), as well as a FORTRAN compiler for the `port3` package

**Install the build prerequisites:**

1. Ensure that a C compiler and a FORTRAN compiler are available on your system.  
1. Install `X11` and `openmotif`. 
    - (Linux) Install the standard X11 and Motif packages, preferably into 
`/usr/local`.  
    - (MacOS)
        - Install the latest version of [XQuartz](https://www.xquartz.org), which places X11 package files into subdirectories of `/opt/X11`, and install the XQuartz X11 server, which standalone MELTS relies upon for its graphical user interface.
        -  Install the [Homebrew package manager](http://brew.sh). In a terminal window, type the command `brew install openmotif`, which  places the Motif package files into subdirectories of `/usr/local`.
1. In a terminal window, navigate to the `port3` subdirectory within the `xMelts` directory.  Edit the file `makefile.top` to point to the correct FORTRAN compiler (*gfortran* in the example below) and compiler flags (*-O3* in the example below):   

```
.SUFFIXES: .f .o
F77 = gfortran
FFLAGS = -O3

.f.o:
    $(F77) -c $(FFLAGS) $*.f
done: \
```
4 Close the file, and run the `make` command to build the PORT3 library.  


### Makefile configuration ###

You can build many of the build targets for MELTS and its auxillary and testing programs on MacOS using the Xcode Integrated Development Environment (IDE). However, most executables—particularly the standalone versions of MELTS—must be built using traditional UNIX makefile-based build procedures. 

The file `Makefile.ubuntu` and `Makefile.MacOS` are master makefiles that each include a *common* makefile, `Makefile.common`. The script in `Makefile.common` is appropriate for use on both Linux and MacOS.  

- (Linux) If building targets in the MELTS software package on Linux, edit the `Makefile.ubuntu` file as appropriate for your system configuration, and in a terminal window generate a soft link with this command: 

    ```
    ln -s ./Makefile.ubuntu Makefile
    ```
- (MacOS) If building targets in the MELTS software package on MacOS, edit the file `Makefile.MacOS` as appropriate for your system configuration, and in a terminal window generate a soft link with this command:  

    ```
    ln -s ./Makefile.MacOS Makefile
    ```
*NOTE: Typing the command* `make` *within the MELTS directory with no argument produces a list of possible build targets:*  

```
make 
/Applications/Xcode.app/Contents/Developer/usr/bin/make -s usage
Usage: Melts Melts-MS Melts-SACNK
        Melts-batch
        Melts-mpi
        Melts-public
        Melts-rhyolite Melts-rhyolite-public
        Melts-dynamic
        Analyze-fusion Analyze-fusion-MS
        Analyze-water Analyze-water-MS
        Entropy_reg Entropy_reg-MS
        LinAndPelton
        Make-liquid-model
        Make_species_map
        Test_a-x_relations Test_a-x_relations-MS  Test_a-x_relations-SACNK
        Test_CCO_buffer Test_CCOH_buffer
        Test_database Test_database-MS Test_database-SACNK
        Test_entropy Test_entropy-MS Test_entropy-SACNK
        Test_dn2gb
        Test_fluid, Test_fluidRegression
        Test_fo2
        Test_gibbs Test_gibbs-MS Test_gibbs-SACNK
        Test_liquid Test_liquid-MS Test_liquid-SACNK
        Test_eos Test_eos-MS Test_eos-SACNK
        Test_mpi
        Test_speciation Test_speciation-MS Test_speciation-SACNK
        Test_SACNK
        Test_SAK
        Test_simann
        Test_sulfide_liquid
        Test_dynamicLib
        Test_water
        Kevin KevinSolid
        Marc
        cpx-olv-rhm
```
*Some of these targets are no longer active or are used only rarely to develop specialied applications.  The more relevant targets are discussed below.*  

### Building standalone rhyolite-MELTS (v 1.0.2, 1.1.x, 1.2.x)  and pMELTS (5.6.1)  ###
You can build standalone versions of MELTS in which you interact with the executable using a graphical user interface (GUI) or in which the executable runs in batch mode, processing standard tagged XML files as input and generating structured XML output files.  
#### Standalone MELTS - GUI ###
1. Ensure that the PORT3 library and `X11` and `openMotif` are installed.
1. In a terminal window, migrate to the repository directory, and type this command:

    ```
    make Melts-rhyolite-public
    ```
A new file appears in the directory named `Melts-rhyolite-public`.   This is an executable image that you can run by typing this command: 

```
./Melts-rhyolite-public
```
On startup, you can choose the database calibration of MELTS desired. You can move the executable image to any location in the system.  

#### Standalone MELTS - batch execution, read-write XML files ####
1. Ensure that the PORT3 library is installed.  
2. In a terminal window, migrate to the repository directory, and type this command:

    ```
    make Melts-batch
    ```
A new file appears in the directory named `Melts-batch`.   This is an executable image that you can run by typing this command:  

```
./Melts-batch
```
The command generates the following output detailing usage:  

```
Usage:
  Melts-batch input.melts
  Melts-batch input.xml
  Melts-batch inputDir outputDir [inputProcessedDir]
              Directories are stipulated relative to current directory
              with no trailing delimiter.
```
 The three usage scenarios are as follows:  
- First usage takes a standard MELTS input file as input on the command line and processes it using MELTS version 1.0.2, placing output files in the current directory.  
- Second usage processes a MELTS input file formatted using the standard MELTS input XML schema (contained in schema definition file [MELTSinput.xsd](https://gitlab.com/ENKI-portal/xMELTS/blob/master/MELTSinput.xsd)) and processes it using the MELTS/pMELTS version specified in that file, placing output files in the current directory.
- Third usage places the executable in listening mode.  The program waits for a file to be placed in the specified `inputDir`, processes that file, and places output into the `outputDir`, moving the input file in the `inputProcessedDir` if one is specified.  This usage is appropriate if some other program (like Excel) is used to generate input files and waits until output is produced for subsequent processes.  Input files must conform to the XML schema noted in the second usage, and output files are generated according to XML output schema specified in [MELTSoutput.xsd](https://gitlab.com/ENKI-portal/xMELTS/blob/master/MELTSoutput.xsd) and [MELTSstatus.xsd](https://gitlab.com/ENKI-portal/xMELTS/blob/master/MELTSstatus.xsd). Detailed documentation files on all of the XML schema may be found in [the Wiki](https://gitlab.com/ENKI-portal/xMELTS/wikis/home).  These schema are also utilized in client-server communication involving the MELTS web services (see below).  A typical command for this usage scenario may look like this:

    ```
    ./Melts-batch ./inputXML ./outputXML ./processedXML
    ```
    where the various directories must exist prior to starting the batch process.

### Building command-line auxillary and testing programs ###
You can build command-line executables for testing various aspects of the MELTS software library by executing this command:  

```
make Test_*
```
where * refers to one of the targets listed above.  In particular, the make targets **Test_a-x_relations**, **Test_liquid**, and **Test_gibbs** create executables for testing new implementations or corrections to solid and fluid solution thermodynamic modules, liquid solution properties, and standard state thermodynamic property routines.  

The somewhat mysteriously named make targets **Kevin**,  **KevinSolid**, **Marc**, and **cpx-olv-rhm** create executables for standalone command-line geothermometers and oxybarometers.  Consult the source code in the subdirectory `./source` for more information.  
### Building statically and dynamically linked libraries that encapsulate the MELTS CT engine
This command builds a runtime statically linked library of phase properties and MELTS engine functions:  

```
make MELTS-dynamic
```
The build process creates a static library named `libMELTSdynamic.a` and two standalone executable files that are linked against this library:
- **`Test_commandLib`** - Is built from the source `./source/test_commandLib.c` and demonstrates how to  perform MELTS calculations by calling the static library functions from a **C code** front end. `Test_commandLib` also demonstrates how to specify MELTS input using command line arguments[.](http://mdp.tylingsoft.com/)
- **`Test_dynamicLib`** - Is built from the source `./source/test_dynamicLib.f` and demonstrates how to perform MELTS calculations by calling the static library functions from a **FORTRAN code** front end.  
 
