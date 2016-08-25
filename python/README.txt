Introduction to PyMELTS
=======================

author: Jess Robertson, CSIRO Earth Science and Resource Engineering

email: jesse.robertson with CSIRO's domain (google it)

date: Monday 15 October 2012

This is a simple wrapper to the dynamic MELTS library for calculating phase equilibria in Python using MELTS. Things are pretty bare-bones at the moment - hopefully this will change as we decide how we want to use this library.

Structure
---------

The basic bindings to libMELTS are stored in pymelts.melts_function namespace. Most of then have docstrings, so you should be able to do `help(pymelts.melts_functions)` in a Python interpreter to find out more information about each function. Most of these functions are simply wrappers which expose information from MELTS to Python, to make it easier to write most of your code in Python with occasional calls to MELTS when you actually want something solved.

The plan (as of version 0.1) is to have a couple of simple classes in the base pymelts, one to represent the state of a calculation, and one to represent the MELTS solver itself, so that users will only have to instantiated instances of these classes to use the library.

Probably the easiest way to get a feel for the behavior of the library is to have a look at the use cases supplied in this documentation. 

Building and installing PyMELTS
-------------------------------

To build this you need to have first installed the dynamic melts library (libMELTSdynamic.so) and have it available on your path somewhere so that the linker can find it. For example, I have libMELTSdynamic sitting in /usr/local/lib, and my path is:

    jrobertson@barracuda >: echo $PATH
    /usr/local/texlive/2012/bin/x86_64-linux:/usr/local/texlive/2012/bin/x86_64-linux:/usr/local/bin:/usr/bin:/bin:/usr/local/games:/usr/games

so gcc can find libMELTSdynamic.so.

Then all you should need to do is enter the python directory, and execute

    jrobertson@barracuda >: ./setup.py build && sudo ./setup.py install

which should build and install the Python bindings for your system.

Building documentation
----------------------

If you want to build the documentation for PyMELTS then you will need to have a version of `sphinx <http://sphinx.pocoo.org/>`_ installed -- you can check by doing::

  python -c 'import sphinx'

If that fails grab the latest version of and install it with::

  > sudo easy_install -U Sphinx

Now you are ready to build a template for your docs, using
sphinx-quickstart::

  > cd docs && make html

(or latexpdf if you want a latex version - type `make` to see all the options). The documentation will be dumped under build/<format>. For HTML, if you point a browser to `build/html/index.html`, you should see a basic sphinx site with the documentation for PyMELTS.