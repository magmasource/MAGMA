# MELTS software 

Short summary of what MELTS is about

Additional software repositories of Objective-C code that implement the MELTS thermodynamic models and CT engine: PhasePlot, ThermoFit

Additional wiki documentation  
MELTS web site with pre-configured execuatbles for MacOS and Ubuntu platforms

## Building the software (MacOS and Linux)
The default **master** branch of the respository tracks the stable public releases of MELTS software. The **develop** branch tracks the latest development code, and may contain unpublished features.  Either branch may be forked in teh repository is cloned.  It is recommended that *GitFlow* protocols be followed and that feature and extension branches should be forked from the develop branch.

This discussion will focus on the following build targets:

- Standalone rhyolite-MELTS (v 1.0.2, 1.1.x, 1.2.x)  and pMELTS (5.6.1)
- Command line auxillary and testing programs
- Static and dynamic libraries encapsulating the MELTS CT engine
- Python package encapsulating the MELTS CT engine - OS agnostic

### Software build prerequisites
In order to build the standalone (GUI) version of MELTS, addiitional system and software resources are required, including

- The `port3` software library, which is included as a submodule in the MELTS git repository on GitLab
- An `X11` installation that includes the package `openmotif`
- Access to a `C` compiler (preferably `clang`, but `gcc` will do), as well as a `FORTRAN` compiler for the `port3` package

Proceed as follows:

+ Insure that both `C` and `FORTRAN` compliers are available on your system.  
+ Install `X11` and `openmotif`. On LINUX systems install the standard X11 and Motif packages, preferably into /usr/local.  On MacOS:
    - Install the latest version of `xQuartz` from https://www.xquartz.org, which will place X11 package files into subdirectories of /opt/X11 and install the Xquartz X11 server that standalone MELTS relies upoon for its graphical user interface
    - Install the `Homebrew` package manager from http://brew.sh, open a terminal window and type the command `brew install openmotif`, which will place the Motif package files into subdirectories of /usr/local
+ Open a terminal window and navigate down into the port3 subdirectory within the xMelts directory/folder.  Edit the file `makefile.top` to point to the correct FORTRAN compiler (here gfortran) and compiler flags (here -O3):  
~~~~
.SUFFIXES: .f .o
F77 = gfortran
FFLAGS = -O3

.f.o:
    $(F77) -c $(FFLAGS) $*.f
done: \
~~~~
+ Once the file is updated, then issue the `make` command to build the port3 library.

### Makefile configuration for non-Xcode builds

Many of the build targets for MELTS and its auxillary and testing programs can be built on MacOS using the Xcode Integrated Development Environment (IDE).  However most executables and in particular the standalone versions of MELTS must be built using traditional unix makefile-based build procedures. 

The file '`Makefile.ubuntu` is a master makefile that includes a *common* makefile, `Makefile.common`, and is intended for use on Ubuntu systems and as a template for other LINUX operating systems.  The script in `Makefile.common` is apropraite for use on both LINUX and MacOS operating systems.  If attempting to build targets in the MELTS software package on LINUX, edit this file as appropriate and in a terminal window generate a soft link with the command:
~~~~
ln -s ./Makefile.ubuntu Makefile
~~~~
Alternatively, on a MacOS system edit the file `Makefile.MacOS` as appropriate and in a terminal window generate a soft link with the command:
~~~~~
ln -s ./Makefile.MacOS Makefile
~~~~~
Typing the command `make` within the MELTS directory with no argument produces a list of possible build targets:
~~~~
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
~~~~
Some of these targets are no longer active or ae used only rarely to develop specialied applications.  The more relevant targets are discussed below.

### Building standalone rhyolite-MELTS (v 1.0.2, 1.1.x, 1.2.x)  and pMELTS (5.6.1) 
Standalone versions of MELTS can be built where the user interacts with the with the executable using a graphical user interface (GUI) or where the executable runs in batch mode, processing standard tagged XML files as input and generating structured XML output files.
#### Standalone MELTS - GUI interface
- Insure that the `port3` library and `X11` and `openMotif` are installed.
- In a terminal window migrate to the repository directory and type the command
~~~~
make Melts-rhyolite-public
~~~~
If there are no errors a new file will appear in the directory named `Melts-rhyolite-public`.   This is an executable image that may be run by typing the command:
~~~~
./Melts-rhyolite-public
~~~~
The database calibration of MELTS that is desired can be chosen on startup. The executable image can be moved to eany desired location in the system.
#### Standalone MELTS - batch execution, read-write XML files
- Insure that the port3 library is installed
- In a terminal window migrate to the repository directory and type the command
~~~~
make Melts-batch
~~~~
If there are no errors a new file will appear in the directory named `Melts-batch`.   This is an executable image that may be run by typing the command:
~~~~
./Melts-batch
~~~~
which generates the following output:
~~~~
Usage:
  Melts-batch input.melts
  Melts-batch input.xml
  Melts-batch inputDir outputDir [inputProcessedDir]
              Directories are stipulated relative to current directory
              with no trailing delimiter.
~~~~
detailing usage. The three usage scenarios are:
- The first usage style takes a standard MELTS input file as input on the command lien and processes it using MELTS version 1.0.2, placing output files in the current directory.  
- The second usage processes a MELTS input file formatted using teh standard MELTS input XML schema (contained in schema definition file `MELTSinput.xsd`) and processes it using the MELTS/pMELTS version specified in that file, placing output files in the current directory.
- The third usage places the executable in listening mode.  The program waits for a file to be placed in the specified `inputDir`, processes that file, and places output into the `outputDir`, moving the input file in the `inputProcessedDir` if one is specified.  This usage is appropriate if some other program (like Excel) is used to generate input files and waits until output is prodiuced for subsequent processes.  Input files must conform to the XML schema noted in teh second usage and output files are generated according to XML output schema specified in `MELTSoutput.xsd` and `MELTSstatus.xsd`. Detailed documentation files on all of teh XML schema may be found in teh WIKI.  These schema are also utilized in client-server communication involving the MELTS web services (see below).  A typical usage three command may look like:
~~~~
./Melts-batch ./inputXML ./outputXML ./processedXML
~~~~
where the various directories must exist prior to starting the batch process.
### Building command line auxillary and testing programs.
Command line exceutables for testing various aspects of the MELTS software library can be built by executing the command
~~~~
make Test_*
~~~~
where * refers to one of the targets listed above.  In particular the make targets `Test_a-x_relations`, `Test_liquid`, and `Test_gibbs` create execuatbles for testing new implementations or corrections to solid and fluid solution thermodynamic modules, liquid solution properties, and standard state thermodynamic property routines.

The somewhat mysteriously named make targets `Kevin`,  `KevinSolid`, `Marc`, `cpx-olv-rhm`, create executables for standalone command line geothermometers and oxybarometers.  Consult the source code in the sudirectory `./source` for more information.
### Building statically and dynamically linked libraries encapsulating the MELTS CT engine
A runtime statically linked library of phase properties and MELTS engine functions is built with the command:
~~~~
make MELTS-dynamic
~~~~
The build process creates a static library named `libMELTSdynamic.a` and two standalone executable files that are linked against this library, `Test_commandLib` and `Test_dynamicLib`. `Test_commandLib` is built from the source `./source/test_commandLib.c` and demonstrates how to  perform MELTS calculations by calling the static library functions from a *C* code front end.  `Test_dynamicLib` is built from the source `./source/test_dynamicLib.f` and demonstrates how to perform MELTS calculations by calling the static library functions from a *FORTRAN* code front end.  `Test_commandLib` also demonstrates how to specify MELTS input using command line arguments.  
### Building the Python package that encapsulaties the MELTS CT engine - operating system agnostic 
Building the python package and accessing associated Python notebooks and examples is described in teh Readme file contained in the python subdirectory.