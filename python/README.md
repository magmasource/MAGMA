# PyMELTS - MELTS Python Package

This is a simple wrapper to the dynamic MELTS library for calculating phase equilibria in Python using rhyolite-MELTS (1.0.2, 1.1.x, 1.2.x) and pMELTS (5.6.1). This is version 1.0 of PyMELTS, which is built upon the standard C MELTS engine.  Later versions of this package will be built iusing teh objective-C code base  

## Package Structure

The primary bindings to the MELTS function library are stored in pymelts.melts_function namespace. Most of then have docstrings, so you should be able to type `help(pymelts.melts_functions)` in a Python interpreter to find out more information about each function. Most of these functions are simply wrappers which expose information from MELTS C data structures to Python.

Probably the easiest way to understand what is available in the package is to build it and then run some of the examples contained in the three Jupyter (iPython) notebooks included with the source code. 

## Building and installing PyMELTS

To build this package you must first build the dynamic melts library target of the main C package using the Makefile located in the directory above the python directory:

    make Melts-dynamic

which will create the dynamic library named libMELTSdynamic.so in that location.

After building the library move down into the python directory

    cd ./python

There are two ways to build the library.  The preferred method can be used if the Anaconda Python environment is installed. At the terminal prompt type:

    conda build .
    conda install --use-local pymelts

In the Anaconda environment, if you ever need to uninstall the PyMELTS package (perhaps prior to installing a never version of the package), then type this command at the terminal prompt:

    conda uninstall pymelts

Alternately, the package can be installed into a generic python environment with the commands:

    ./setup.py build
    sudo ./setup.py install

## Building PyMELTS package documentation

If you want to build the documentation for PyMELTS then you will need to have a version of `sphinx <http://sphinx.pocoo.org/>`_ installed.  The Anaconda Python environment already has sphinx and its dependencies installed. 

You can check on the avaiability of sphinx in a generic Python environment by typing in a terminal window:

    python -c 'import sphinx'

If that command fails, then install the latest  with the commands:

    sudo easy_install -U Sphinx

To build the documentation, move down into the docs directory and execute the html target of the sphinx Makefile:

    cd docs
    make html

(or `make latexpdf` if you want a latex version - type `make` to see all the options). The documentation will be assembled into teh directory build/<format>. For HTML, if you point a browser to `build/html/index.html`, you should view documentation for PyMELTS.