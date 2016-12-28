# PyMELTS - MELTS Python Package

PyMELTS is a python package for calculating phase equilibria using rhyolite-MELTS (1.0.2, 1.1.x, 1.2.x) and pMELTS (5.6.1). This is version 1.0 of PyMELTS, which is built upon the standard C MELTS engine.  Later versions of this package will be built iusing the objective-C code base.

## Package Structure

The primary bindings to the MELTS function library are stored in the pymelts.melts_function namespace. Most of then have docstrings, so you should be able to type `help(pymelts.melts_functions)` in a Python interpreter to find out more information about each function. Most of these functions are simply wrappers which expose information from MELTS C data structures as Python dictionaries.

Probably the easiest way to understand what is available in the package is to build it and then run some of the examples contained in the interactive Jupyter (iPython) notebooks included with the source code (within the python folder). 

## Installing PyMELTS pre-compiled packages

Pre-compiled PyMELTS python packages are available for Anaconda installations running in MacOS, Windows and Linux operating environments.  Download the package from the conda-forge channel using either the Anaconda user interface apploication or the command line.

#### From the Anaconda user interface:

1. Launch anaconda Navigator.
1. Set Environments from the left panel.
1. Click the “Channels” button (top of right panel).
1. Add conda-forge as a channel.
1. Select “Not installed” from the dropdown menu and search for the package pymelts.
1. Click on the box next to the package pymelts to select it and then click on the “Apply” button (bottom right) to install the package.
1. Select “Installed” from the dropdown menu and clear the package search.  You should now see pymelts (v. 0.1.1 or later) installed in your list of installed packages.
1. Return to the home screen of Anaconda Navigator (found on the left panel).
1. Launch Jupyter, navigate to the python sub folder of the project root folder, and open one of the iPython example notebooks.  These notebooks illustrate various features of the pymelts package.

#### From the command line type:

    conda config --add channels conda-forge 
    conda install pymelts
    
Then, from the command line launch a Jupyter notebook server in the browser:

    jupyter notebook
    
and navigate to the python sub folder of the project root folder; open one of the iPython example notebooks.

## Building and installing PyMELTS

Alternatively, the package can be built directly from the source "C" and python files.

There are two ways to build the library.  The preferred method can be used if the Anaconda Python environment is installed. In the rrot directory of the project at the terminal prompt type:

    conda build .
    conda install --use-local pymelts

In the Anaconda environment, if you ever need to uninstall the PyMELTS package (perhaps prior to installing a newer version of the package), then type this command at the terminal prompt:

    conda uninstall pymelts

Alternately, the package can be installed into a generic python environment with the commands executed from the root directory of the project:

    ./setup.py build
    sudo ./setup.py install
    
## Building the package for multiple platforms at conda-forge

If you modify the source and wish to distribute a new version of the PyMELTS package from conda-forge that is pre-packaed for MacOS, Windows and Linux systems, then follow the instructions below on a MacOS or Ubuntu system:

1. Create an account on GitHub (if you do not already have one).
2. At GitHub, fork the respository https://github.com/conda-forge/staged-recipes, and then clone it to the desktop
3. Within the newly cloned "staged-recipes" repository, create a sub folder called pymelts inside the recipes folder, and copy the file meta.yaml.conda-forge from the xMelts repository root folder into this folder, renaming it afterwards to meta.yaml.
4. Edit this copy of meta.yaml to update the version maintainer entry.
5. Return to the xMelts repository directory and edit the top level Makefile (Makefile.MacOS or Makefile.ubuntu) to update the version number of the PyMELTS package build.  Symlink the appropriate makefile, as `ln -s Makefile.MacOS Makefile`. In addition, edit the information as to the server location where the compressed source tar ball will be uploaded and made publically assessible to the conda-forge build process. An encrypted web server is ideally suited for this purpose.  
6. Then, execute `make pymelts` from the command line, followed by `make pymelts-install`.  Note the value of the checksum hash output from the second make command.
7. Return to the staged-recipes repository directory and edit the meta.yaml file to reflect the correct version number of the package, also updating the hash string to reflect the value noted above.
8. Make any other changes to the conda recipe in the meta.yaml file that reflect your modifications to the package source. (Perhaps adding additional python package dependences that are required for teh build.)
9. Now, push the local repository modifications back to git hub.  From the root of the repository execute the commands: `git add recipes` and `git push origin`
10. Return to GitHub and create a Pull Request to conda-forge/staged-recipes from your master branch.
11. The conda-forge linter bot will post a message about any potential issues or style suggestions it has on your recipe.
12. Continuous Integration scripts at conda-forge will automatically build against Linux, MacOS, and Windows.
13. When all builds succeed, the package is ready to be reviewed by a community moderator for merge.
14. The moderator will review and merge your new staged-recipes. From here, automated scripts create a new repo (called a feedstock) just for your package, with the github id’s from the recipe-maintainers section added as maintainers.
15. The package will now be available for download from conda-forge on all suppported systems and python versions.

For additional information on conda-forge and the build process read the blog post at https://www.continuum.io/blog/developer-blog/anaconda-build-migration-conda-forge.

## Building PyMELTS package documentation

If you want to build the documentation for PyMELTS then you will need a version of the `sphinx <http://sphinx.pocoo.org/>` python package.  The Anaconda Python environment already has sphinx and its dependencies installed.

You can check on the avaiability of sphinx in a generic Python environment by typing in a terminal window:

    python -c 'import sphinx'

If that command fails, then install the latest  with the commands:

    sudo easy_install -U Sphinx

To build the documentation, move down into the python/docs folder and execute the html target of the sphinx Makefile:

    cd docs
    make html

(or `make latexpdf` if you want a latex version - type `make` to see all the options). The documentation will be assembled into the directory build. For HTML, if you point a browser to `build/html/index.html`, you should be able to view documentation for PyMELTS.