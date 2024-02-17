# MELTS software #

**MELTS** is a software package designed to facilitate thermodynamic modeling of phase equilibria in magmatic systems. It provides the ability to compute equilibrium phase relations for igneous systems over the temperature range 500-2000 °C and the pressure range 0-2 GPa.

This repository is a fork of the **MAGMA** branch of Mark Ghiorso's **[xMELTS](https://gitlab.com/ENKI-portal/xMELTS)** repository on GitLab. It is maintained by Paula Antoshechkina and includes edits made for the [MAGMA@Caltech](magmasource.caltech.edu) effort (including early work on [MELTS for MATLAB](https://ui.adsabs.harvard.edu/abs/2018AGUFMED44B..23A%2F/abstract)) and for the [Magma Chamber Simulator](https://mcs.geol.ucsb.edu/) ([MCS](https://mcs.geol.ucsb.edu/)). Melts-batch executables for MacOS, Windows and Linux, like those used by the MCS, can be found in the MCS-Melts-batch and Linux-Melts-batch directories.

In this repository the original standalone rhyolite-MELTS (v 1.0.2, 1.1.x, 1.2.x) and pMELTS (v 5.6.1) graphical user interface (GUI) is replaced by Einari Suikkanen's easyMelts software, which has the same capabilities - plus working plots - in a modern and easy-to-use package.

For additional documentation on the original GUI, visit the [MELTS website](http://melts.ofm-research.org/index.html). There you can find preconfigured executables for MacOS and Ubuntu platforms (though your mileage may vary, especially with the Linux ones).

## Downloading and running the software (MacOS, Linux or Windows) ##

easyMelts will be posted here soon, but in the meantime it can be downloaded from the [MAGMA Source GitList server](https://magmasource.caltech.edu/gitlist/easyMelts.git/). No installation is requied (though it helps to put the easyMelts executable somewhere in your path). For instructions on how to run the software see the README.

Melts-batch will also be formally released, with version numbers, soon. In the meantime, it should be possible to run the binaries in the MCS-Melts-batch and Linux-Melts-batch folders as-is. Download the Melts-batch.zip file or Melts-batch.exe.zip file and make sure to expand it.

## Building the software (MacOS, Linux or Windows) ##

This README focuses on the following build targets:

- Command-line auxillary and testing programs (Melts-batch)
- Static and dynamic libraries encapsulating the MELTS CT engine (same as included in easyMelts)

~~:point_right: To build the Python package that encapsulates the MELTS CT engine (OS agnostic) and to access associated Python notebooks and examples, refer to the [README file in the python subdirectory](https://gitlab.com/ENKI-portal/xMELTS/blob/master/python/README.md).~~

~~:point_right: For MacOS build targets configured with Xcode, simply open the project file, `MELTS.xcodeproj`, in Xcode and follow the instructions [Building Xcode targets in the MELTS project ](https://gitlab.com/ENKI-portal/xMELTS/blob/master/XCODE-README.md)(XCODE-README.md).~~


### Cloning the repository and populating the submodules ###
The default **main** branch of the respository tracks the stable public releases of MELTS software. The **mcs-develop** branch tracks the latest development code and may contain unpublished features.  You can fork either branch when you clone the repository. Make sure to follow *GitFlow* protocols and to fork feature and extension branches only from the **mcs-develop** branch.


When you clone the repository, the **main** branch is tracked by default. Unlike the original **[xMELTS](https://gitlab.com/ENKI-portal/xMELTS)** workflow, this fork does not require population of the port3 submodules (i.e., subrepositories), as those were only required to perform the build procedures for the standalone GUI.

### Prerequisites ###

To build the command line (Melts-batch) version of MELTS on MacOS, Linux or native Windows, you need only the C compiler. You should not need a FORTRAN compiler.

1. You will need a C compiler (preferably clang, but GCC suffices)
    - (Linux) A standard Linux installation, such as Ubuntu desktop, will normally have GCC installed, though possibly not clang.
        - For more lightweight installations, such as the Windows Subsystem for Linux (WSL) or [Multipass](https://multipass.run/), you may need to install the `binutils` and `make` (or equivalent) packages into standard locations.
        - Optionally install the `clang` package.
    - (MacOS) 
        - If you have Xcode installed, and it is up to date, then this includes the clang compiler.
        - If you have the [Homebrew package manager](https://brew.sh), then the Command Line Tools should already be installed and will work instead.
        - If you do not have Xcode or Homebrew you do not need to install Xcode, and you may not want to as it is huge(~10 GB)! Instead install just the Command Line Tools, which are < 1 GB; see [Install Xcode Command Line Tools](https://mac.install.guide/commandlinetools/4.html).    
    - (Windows) Install [MSYS2](https://www.msys2.org/), either directly, or by installing the [Rtools 4.3](https://cran.r-project.org/bin/windows/Rtools/rtools43/rtools.html) package.
        - For a standalone MSYS2 installation (no Rtools): open the MSYS2 MSYS terminal and type the commands `pacman -Su`, then `pacman -S --needed base-devel mingw-w64-x86_64-toolchain`.
        - Optionally install clang with the command `pacman -S mingw-w64-x86_64-clang`.
        - If you installed MSYS2 via Rtools then you will need to use GCC instead of clang in the following sections.
2. You will also need a terminal program.
    - (Linux) Use the terminal / console program included with your Linux desktop, or open the Windows Subsystem for Linux, or choose 'Open Shell' in the Multipass menu.
    - (MacOS) In Finder go to the Utilities folder and open Terminal.app. It is a good idea to keep the Terminal program in the dock.
    - (Windows) Open the MSYS2 MSYS terminal (a.k.a. Rtools43 Bash) or go to Tools->Terminal->New Terminal within [Rstudio](https://posit.co/download/rstudio-desktop/).

**Install the command line (Melts-batch) build requisites:**

1. Ensure that a C compiler is available on your system.
1. Install `libxml2` developer files, if they are not already installed.
    - (Linux) Install the `libxml2` and `libxml2-dev` (or equivalent) packages into the standard locations.
    - (MacOS) libxml2 is installed by default but you will need to have installed the Xcode tools, as described above, for the development files to be accessible.
    - (Windows) If you installed Rtools 4.3 then libxml2 is included by default, but in the standalone MSYS2 installation.
        - If you have a standalone MSYS2 installation: open the MSYS2 MSYS terminal and type the command `pacman -S libxml2`
        - Alternatively, you can get all the pre-built libraries that are bundled with Rtools 4.3 [here](https://cran.r-project.org/bin/windows/Rtools/rtools43/files) and add them to your MSYS2 installation (see [here](https://cran.r-project.org/bin/windows/Rtools/rtools43/rtools.html) for more details).

### Makefile configuration ###

You can build many of the build targets for MELTS and its auxillary and testing programs on MacOS using the Xcode Integrated Development Environment (IDE) (see the **[xMELTS](https://gitlab.com/ENKI-portal/xMELTS)** READMEs). However, the executables and libraries described here must be built using traditional UNIX makefile-based build procedures.

The file `Makefile.Linux`, `Makefile.MacOS`, `Makefile.Windows`, and `Makefile.Rtools` files are master makefiles that each include a *common* makefile, `Makefile.common`. The script in `Makefile.common` is appropriate for use on both Linux and MacOS, and Windows with MSYS2.

- (Linux) If building targets in the MELTS software package on Linux, edit the `Makefile.Linux` file as appropriate for your system configuration. If you do not have clang installed then you will need to replace `clang` with `gcc` and `clang++` with `g++`. In a terminal window generate a soft link with this command:

    ```
    ln -s ./Makefile.Linux Makefile
    ```
  There is also a debug Makefile for Linux `Makefile.debug`. You can invoke this rather than the standard Linux Makefile by replacing `make` with `make -f Makefile.debug` in the following secions. `Makefile.debug` defaults to using clang but you can switch to GCC on the fly by adding `USEGCC=true` to the end of the command line `make` command line.

- (MacOS) If building targets in the MELTS software package on MacOS, edit the file `Makefile.MacOS` to update the deployment target as appropriate for your system configuration, and in a terminal window generate a soft link with this command:

    ```
    ln -s ./Makefile.MacOS Makefile
    ```
- (Windows) If building targets in the MELTS software package on Windows / MSYS2, edit the file `Makefile.Windows` as appropriate for your system configuration. The default `ROOTDIR` is suitable for use from Rtools but for standalone MSYS2 you will need to change this to `mingw64`. From Rtools you need to use GCC, but for a standalone MSYS2 installation you can optionally replace `gcc` with `clang` and `g++` with `clang++`. In a terminal window generate a soft link with this command:

    ```
    ln -s ./Makefile.Windows Makefile
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
*Some of these targets are no longer active on this fork or are used only rarely to develop specialied applications.  The more relevant targets are discussed below.*

#### Standalone MELTS rhyolite-MELTS (v 1.0.2, 1.1.x, 1.2.x)  and pMELTS (5.6.1) - batch execution, read-write XML files ####
1. You should be able to build Melts-batch without the PORT3 library installed.
2. In a terminal window, migrate to the repository directory, and type this command:

    ```
    make Melts-batch
    ```
    A new file shuld appear in the directory named `Melts-batch` (or `Melts-batch.exe`). If it does not then try some of the following troubleshooting tips:
    - If you are using the Rtools MSYS2 MSYS terminal (a.k.a. Rtools43 Bash) then type this command, before trying the `make` command again:
    ```
    export PATH=/x86_64-w64-mingw32.static.posix/bin:$PATH
    ```
    - If you are using a standalone MSYS2 installation then type this command, before trying the `make` command again:
    ```
    export PATH=/mingw64/bin:$PATH
    ```
    - If you get linker errors then try adding `STATIC=true` to the make command line:
    ```
    make Melts-batch STATIC=true
    ```
    - 
    
3. Here (and on the MAGMA branch of **[xMELTS](https://gitlab.com/ENKI-portal/xMELTS)**) the `Melts-batch` executable will be for the pMELTS model by default (on the master/develop branches it will be rhyolite-MELTS 1.0.2 by default; the prebuilt executables in MCS-Melts-batch and Linux-Melts-batch are also rhyolite-MELTS 1.0.2. unless otherwise labeled). You may want to rename the file, e.g:

    ```
    mv Melts-batch Melts-batch-pMELTS-v5.6.1
    ```
4. You can build default rhyolite-MELTS versions 1.0.2, 1.1.0, and 1.2.0, respectively, using:

    ```
    make Melts-batch -DV102
    make Melts-batch -DV110
    make Melts-batch -DV120
    ```
The `Melts-batch` file is an executable image that you can run by typing this command:

```
./Melts-batch
```
The command generates the following output detailing usage:

```
Usage:
  Melts-batch input.melts
  Melts-batch input.xml
  Melts-batch inputDir outputDir [inputProcessedDir]
              Directories are stipulated relative to current directory with no trailing delimiter.
```
 The three usage scenarios are as follows:
- First usage takes a standard MELTS input file as input on the command line and processes it using MELTS version 1.0.2, placing output files in the current directory.
- Second usage processes a MELTS input file formatted using the standard MELTS input XML schema (contained in schema definition file [MELTSinput.xsd](https://github.com/magmasource/blob/MAGMA/main/MELTSinput.xsd)) and processes it using the MELTS/pMELTS version specified in that file, placing output files in the current directory.
    - The output file ending `*-out.xml` will contain output for the last step in the calculation sequence. On the MAGMA branch another file is produced ending `*-sequence.xml` which contains output for all steps, similar to the MELTS web services output (see below).
    - Note that changing MELTS/pMELTS model from the compiled default using the XML input file only works on the MAGMA branch.
- Third usage places the executable in listening mode.  The program waits for a file to be placed in the specified `inputDir`, processes that file, and places output into the `outputDir`, moving the input file in the `inputProcessedDir` if one is specified.  This usage is appropriate if some other program (like Excel) is used to generate input files and waits until output is produced for subsequent processes. A typical command for this usage scenario may look like this:

    ```
    ./Melts-batch ./inputXML ./outputXML ./processedXML
    ```
    where the various directories must exist prior to starting the batch process.

Input files for the second and third usage must conform to the XML schema noted in the second usage ([MELTSinput.xsd](https://gitlab.com/ENKI-portal/xMELTS/blob/MAGMA/MELTSinput.xsd)), and output files are generated according to XML output schema specified in [MELTSoutput.xsd](https://gitlab.com/ENKI-portal/xMELTS/blob/MAGMA/MELTSoutput.xsd) and [MELTSstatus.xsd](https://gitlab.com/ENKI-portal/xMELTS/blob/MAGMA/MELTSstatus.xsd).  These schema are also utilized in client-server communication involving the MELTS web services (see below).  Detailed documentation files on all of the XML schema may be found in [the MELTS Web Services page](https://melts.ofm-research.org/web-services.html).  The main difference between the MAGMA branch version of the MELTS input XML schema and the web services one is the introduction of a `<finalize />` tag that is used to complete and close the `*-seqence.xml` output file.

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

To build the 'libMELTSdynamic' library used with early versions of MELTS for MATLAB (later alphaMELTS for MATLAB/Python) use the following (you may get an error message if you do not have Fortran installed, but you can safely ignore it):

```
make realclean Melts-dynamicPrivate "BATCH=-DBATCH_VERSION -DRHYOLITE_ADJUSTMENTS" DYNAMIC=true
```

Rename the 'libMELTSdynamic' file, which will have a .dylib, .so or .dll suffix, to 'libalphamelts', with the same suffix. Finally, move the .dylib, .so or .dll library into the 'MELTS_Matlab/package' directory or wherever the .m or .py files are.

