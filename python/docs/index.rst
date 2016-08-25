.. pymelts documentation master file, created by
   sphinx-quickstart on Fri Oct 19 11:34:51 2012.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

.. _intro:

Welcome to PyMELTS!
*******************

Jess Robertson, CSIRO Earth Science and Resource Engineering (email: `jesse.robertson` with CSIRO's domain)

This is a simple wrapper to the dynamic MELTS library for calculating phase equilibria in Python using MELTS. Things are pretty bare-bones at the moment - hopefully this will change as we decide how we want to use this library.

The basic bindings to libMELTS are stored in pymelts.melts_function namespace. Most of then have docstrings, so you should be able to do `help(pymelts.melts_functions)` in a Python interpreter to find out more information about each function. Most of these functions are simply wrappers which expose information from MELTS to Python, to make it easier to write most of your code in Python with occasional calls to MELTS when you actually want something solved.

The plan (as of version 0.1) is to have a couple of simple classes in the base pymelts, one to represent the state of a calculation, and one to represent the MELTS solver itself, so that users will only have to instantiated instances of these classes to use the library.

Probably the easiest way to get a feel for the behavior of the library is to have a look at the use cases supplied in this documentation. 

Documentation
-------------

.. toctree::
   :maxdepth: 2

   building
   examples
   pymelts


Indices and tables
------------------

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`

