# PyMELTS - MELTS Python Package

PyMELTS is a Python package for calculating phase equilibria using rhyolite-MELTS (1.0.2, 1.1.x, 1.2.x) and pMELTS (5.6.1). This 1.0 version of PyMELTS is built upon the standard C MELTS engine.  Later versions of this package will be built using the Objective-C code base.

## Contents 
[Package structure](#package-structure)  
[Installing PyMELTS pre-compiled packages](#installing-pymelts-pre-compiled-packages)  
[Building and installing PyMELTS](#building-and-installing-pymelts)  
[Building the package for multiple platforms at conda-forge](#building-the-package-for-multiple-platforms-at-conda-forge)  
[Building PyMELTS package documentation](#building-pymelts-package-documentation)  

## Package structure

The primary bindings to the MELTS function library are stored in the pymelts.melts_function namespace. Most of them have docstrings, so you can type **help(pymelts.melts_functions)** in a Python interpreter to find out more information about each function. Most of these functions are simply wrappers that expose information from MELTS C data structures as Python dictionaries.

Probably the easiest way to understand what is available in the package is to build it and then run some of the examples contained in the interactive Jupyter (iPython) notebooks included with the source code (within the python folder). 

## Installing PyMELTS pre-compiled packages

Pre-compiled PyMELTS Python packages are available for Anaconda installations running in MacOS, Windows, and Linux operating environments.  Download the package from the conda-forge channel using either the Anaconda user interface application or the command line.

#### Using the Anaconda user interface:

1. In Anaconda Navigator, click **Environments** in the left panel.
1. Click the **Channels** button (top of right panel).
1. Add conda-forge as a channel.
1. Select **Not installed** from the dropdown menu, and search for the package **pymelts**.
1. Select the **pymelts** check box, and then click **Apply** (bottom right) to install the package.
1. Select **Installed** from the dropdown menu, and clear the package search. **pymelts** (v. 0.1.1 or later) is now in the list of installed packages.

**Explore the Jupyter notebooks:**  
1. Return to the home screen of Anaconda Navigator by clicking **Home** on the left panel.  
2. Launch Jupyter, navigate to the python subfolder of the project root folder, and open one of the iPython example notebooks. These notebooks illustrate various features of the pymelts package.

#### Using the command line:
From the command line, type:
    
    conda config --add channels conda-forge  
    conda install pymelts

    
**Explore the Jupyter notebooks:**

1. From the command line, launch a Jupyter notebook server in the browser:

    
    ```
    jupyter notebook
    ```

    
3. Navigate to the python subfolder of the project root folder, and open one of the iPython example notebooks.  These notebooks illustrate various features of the pymelts package.

## Building and installing PyMELTS

Alternatively, instead of installing pre-compiled packages, you can build the package directly from the source "C" and Python files.

There are two ways to build the library: 
- Anaconda environment (preferred)
- Generic Python environment

**Anaconda environment**  
You can use this preferred method if the Anaconda Python environment is installed. In the root directory of the project, at the terminal prompt type:

    conda build .
    conda install --use-local pymelts

If Anaconda is installed and if the root environment is based upon Python 3.x then you must create a new environment based on Python 2.7, and modify the build command to ensure that it is used:

    conda create -n python27 python=2.7 
    conda build --python=2.7 .

To activate the Python 2.7 environment before running PyMELTS, execute the following:

    source activate python27

If you want to switch back to the original Python 3.x environment, execute either one of these commands:

    source deactivate python27
    source activate root

If you ever need to uninstall the PyMELTS package (perhaps prior to installing a newer version of the package), then type this command at the terminal prompt:

    conda uninstall pymelts

**Generic Python environment**  
Alternately, you can install the package into a generic Python environment with the commands executed from the root directory of the project:

    ./setup.py build
    sudo ./setup.py install
    
## Building the package for multiple platforms at conda-forge

If you modify the source and wish to distribute a new version of the PyMELTS package from conda-forge that is pre-packaged for MacOS, Windows, and Linux systems, then follow these instructions on a MacOS or Ubuntu system.

1. Create an account on GitHub (unless you already have one).
2. At GitHub, fork the respository https://github.com/conda-forge/staged-recipes, and then clone it to the desktop.
3. Within the newly cloned **staged-recipes** repository, create a subfolder called **pymelts** inside the recipes folder, and copy the file **meta.yaml.conda-forge** from the xMelts repository root folder into this folder, and then rename the file to **meta.yaml**.
4. Edit this copy of meta.yaml to update the version maintainer entry.
5. Return to the xMelts repository directory, and edit the top level Makefile (Makefile.MacOS or Makefile.ubuntu) to update the version number of the PyMELTS package build.  Symlink the appropriate makefile, as `ln -s Makefile.MacOS Makefile`. In addition, edit the information as to the server location where the compressed source tar ball will be uploaded and made publically assessible to the conda-forge build process. An encrypted web server is ideally suited for this purpose.  
6. Execute `make pymelts` from the command line, followed by `make pymelts-install`.  Note the value of the checksum hash output from the second make command.
7. Return to the staged-recipes repository directory, and edit the meta.yaml file to reflect the correct version number of the package, also updating the hash string to reflect the value noted above.
8. Make any other changes to the conda recipe in the meta.yaml file that reflect your modifications to the package source (perhaps adding additional python package dependences that are required for the build).
9. Push the local repository modifications back to Github. From the root of the repository, execute these commands:  
   
    ```
    git add recipes
    git push origin
    ```

10. Return to GitHub, and create a pull request to conda-forge/staged-recipes from your master branch.  
 
<p style="margin-left:6%">The conda-forge linter bot posts a message about any potential issues or style suggestions it has on your recipe.  </p>
<p style="margin-left:6%;>Continuous Integration scripts at conda-forge will automatically build against Linux, MacOS, and Windows.  </p>
<p style="margin-left:6%">When all builds succeed, the package is ready for review by a community moderator for merge. The moderator will review and merge your new staged-recipes. From here, automated scripts create a new repository (called a feedstock) just for your package, with the Github id’s from the recipe-maintainers section added as maintainers.  </p>
<p style="margin-left:6%">The package will then be available for download from conda-forge on all suppported systems and Python versions.</p>

For additional information on conda-forge and the build process, read the Anaconda blog post, [ANACONDA BUILD MIGRATION TO CONDA-FORGE](https://www.continuum.io/blog/developer-blog/anaconda-build-migration-conda-forge).

## Building PyMELTS package documentation

If you want to build the documentation for PyMELTS, you need the [Sphinx Python package](http://sphinx.pocoo.org). The Anaconda Python environment already has Sphinx and its dependencies installed.

You can check the availability of Sphinx in a generic Python environment by typing this command in a terminal window:

    python -c 'import sphinx'

If that command fails, then install the latest version with the command:

    sudo easy_install -U Sphinx

To build the documentation, move down into the python/docs folder and execute the html target of the Sphinx Makefile:

    cd docs
    make html

(Or use `make latexpdf` if you want a LaTeX version. Type `make` to see all the options.) The documentation is assembled into the directory build. For HTML, point a browser to `build/html/index.html` to view documentation for PyMELTS.
