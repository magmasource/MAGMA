# MELTS software #

[![DOI](https://zenodo.org/badge/724791962.svg)](https://doi.org/10.5281/zenodo.11406229)

**MELTS** is a software package designed to facilitate thermodynamic modeling of phase equilibria in magmatic systems. It provides the ability to compute equilibrium phase relations for igneous systems over the temperature range 500-2000 °C and the pressure range 0-2 GPa.

This repository is a fork of the **MAGMA** branch of Mark Ghiorso's **[xMELTS](https://gitlab.com/ENKI-portal/xMELTS)** repository on GitLab. It is maintained by Paula Antoshechkina and includes edits made for the [MAGMA@Caltech](https://magmasource.caltech.edu) effort (including early work on [MELTS for MATLAB](https://ui.adsabs.harvard.edu/abs/2018AGUFMED44B..23A%2F/abstract)) and for the [Magma Chamber Simulator](https://mcs.geol.ucsb.edu/) ([MCS](https://mcs.geol.ucsb.edu/)). Melts-batch executables for MacOS, Windows and Linux, like those used by the MCS, can be found in the MCS-Melts-batch and Linux-Melts-batch directories.

In this repository the original standalone rhyolite-MELTS (v 1.0.2, 1.1.x, 1.2.x) and pMELTS (v 5.6.1) graphical user interface (GUI) is replaced by Einari Suikkanen's easyMelts software, which has the same capabilities - plus working plots - in a modern and easy-to-use package.

For additional documentation on the original GUI, visit the [MELTS website](http://melts.ofm-research.org/index.html). There you can find preconfigured executables for MacOS and Ubuntu platforms (though your mileage may vary, especially with the Linux ones).

## Downloading and running the software (MacOS, Linux or Windows) ##

easyMelts is a brand new GUI application for running MELTS models on Windows, MacOS, and Linux. It was written by Einari Suikkanen, who also developed the Magma Chamber Simulator Visualizer (MCSV) while at Helsinki University, Finland (see right). easyMelts was designed with the philosphy that software tools should be as intuitive and easy as possible, and it should be an approachable alternative to more advanced tools in the MELTS family. Executables and operating instructions are currently hosted in a GitList repository on the MAGMA@Caltech site.

    easyMelts requires a 64-bit operating system, and OpenGL 3.3 compliant graphics (most computers produced in the last 10 years or so satisfy this requirement). Installation is as simple as unzipping the file.
    Feature-wise, easyMelts is comparable to the Rhyolite-MELTS GUI, and it works for the Rhyolite-MELTS (1.0.2, 1.1.0, 1.2.0) and pMELTS models. It writes input and output files with the same formats used by Rhyolite-MELTS and alphaMELTS 2. It allows you to browse details for all phases in each calculation step and displays plots at runtime.
    Like the GUI and Melts-batch (the MELTS part of the MCS) easyMelts is geared towards cooling and crystallization more than melting processes. alphaMELTS will likely be a better long term option for modelling mantle melting. Even if this your ultimate goal, though, easyMelts is an excellent introduction to MELTS in general, and the MELTS input file (.melts) format in particular.
    In easyMelts you always specify the number of steps, rather than e.g. a target temperature. To use .melts files output by easyMelts in other MELTS software you may need to add something like "Final Temperature: ...", but otherwise the file should run as is.

easyMelts is a GUI application for running MELTS on Windows, macOS and Linux. easyMelts is designed to be an approachable alternative for the more advanced tools in the MELTS family. Feature-wise, easyMelts is comparable to the the original GUI MELTS.

easyMelts will be posted here soon, but in the meantime it can be downloaded from the [MAGMA Source GitList server](https://magmasource.caltech.edu/gitlist/easyMelts.git/). No installation is requied (though it helps to put the easyMelts executable somewhere in your path). For instructions on how to run the software see the README.

Melts-batch will also be formally released, with version numbers, soon. In the meantime, it should be possible to run the binaries in the MCS-Melts-batch and Linux-Melts-batch folders as-is. Download the Melts-batch.zip file or Melts-batch.exe.zip file and make sure to expand it.


