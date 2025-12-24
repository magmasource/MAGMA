# MELTS software #

**MELTS** is a software package designed to facilitate thermodynamic modeling of phase equilibria in magmatic systems. The original MELTS model could compute equilibrium phase relations for igneous systems over the temperature range 500-2000 °C and the pressure range 0-2 GPa. The [Magma Chamber Simulator](https://mcs.geol.ucsb.edu/) ([MCS](https://mcs.geol.ucsb.edu/)) is the marriage between a computational thermodynamic engine and an executive brain. The thermodynamic engine (Melts-batch.exe) implements one of the MELTS models - rhyolite-MELTS v1.2.x, 1.1.x, 1.0.x, or pMELTS - for performing phase equilibria calculations. The executive brain or command and control element of the MCS is called IGOR and implements a particular recharge-assimilation-fractional crystallization (RnAFC) scenario specified by the user in an Excel input file.

This repository is a fork of the **MAGMA** branch of Mark Ghiorso's **[xMELTS](https://gitlab.com/ENKI-portal/xMELTS)** repository on GitLab. It is maintained by Paula Antoshechkina in collaboration with the Magma Chamber Simulator (MCS) developer team. It also includes edits made for the MELTS software support previously hosted at [MAGMA@Caltech](https://magmasource.caltech.edu) (including early work on [MELTS for MATLAB](https://ui.adsabs.harvard.edu/abs/2018AGUFMED44B..23A%2F/abstract)).

In this repository the original standalone rhyolite-MELTS (v 1.0.2, 1.1.x, 1.2.x) and pMELTS (v 5.6.1) graphical user interface (GUI) is replaced by Einari Suikkanen's easyMelts software, which has the same capabilities - plus working plots - in a modern and easy-to-use package. For additional documentation on the original GUI, visit the [MELTS website](http://melts.ofm-research.org/index.html). There you can find preconfigured executables for MacOS and Ubuntu platforms (though your mileage may vary, especially with the Linux ones).

Both easyMelts and Melts-batch are provided for all macOS, Linux and Windows platforms. The Melts-batch executable can be used outside of MCS to simulate the MELTS web services (see the [schema documentation](http://melts.ofm-research.org/web0services.html)) and will be integrated in an upcoming release of the [GeoChemical Data toolkit](https://gcdkit.org/index.php) ([GCDkit](https://gcdkit.org/index.php)). No installation should be required for easyMelts or Melts-batch but more details will be provided in the Wiki soon.

<!--## Downloading and running the software (MacOS, Linux or Windows) ##-->

easyMelts is a new GUI application for running MELTS models on Windows, MacOS, and Linux. It was written by Einari Suikkanen, who also developed the Magma Chamber Simulator Visualizer (MCSV) while at Helsinki University, Finland. easyMelts was designed with the philosphy that software tools should be as intuitive and easy as possible, and it should be an approachable alternative to more advanced tools in the MELTS family. easyMelts runs on Windows, macOS and Linux. Feature-wise, easyMelts is comparable to the the original GUI MELTS.


    easyMelts requires a 64-bit operating system, and OpenGL 3.3 compliant graphics (most computers produced in the last 10 years or so satisfy this requirement). Installation is as simple as unzipping the file.
    Feature-wise, easyMelts is comparable to the Rhyolite-MELTS GUI, and it works for the Rhyolite-MELTS (1.0.2, 1.1.0, 1.2.0) and pMELTS models. It writes input and output files with the same formats used by Rhyolite-MELTS and alphaMELTS 2. It allows you to browse details for all phases in each calculation step and displays plots at runtime.
    Like the GUI and Melts-batch (the MELTS part of the MCS) easyMelts is geared towards cooling and crystallization more than melting processes. alphaMELTS will likely be a better long term option for modelling mantle melting. Even if this your ultimate goal, though, easyMelts is an excellent introduction to MELTS in general, and the MELTS input file (.melts) format in particular.
    In easyMelts you always specify the number of steps, rather than e.g. a target temperature. To use .melts files output by easyMelts in other MELTS software you may need to add something like "Final Temperature: ...", but otherwise the file should run as is.



