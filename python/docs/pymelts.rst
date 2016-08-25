.. _pymelts:

PyMELTS Reference
*****************
.. _base_namespace:
.. py:module:: pymelts

This is a general reference for the PyMELTS API. For examples of how to use it, see the examples page.

Engine
------
.. _melts_engine:

.. autoclass:: pymelts.Engine
   :members:
   :undoc-members:

Calculation classes
-------------------
.. _calculation_classes:

These classes store the details of a MELTS calculation, and expose methods to call MELTS from Python

.. autoclass:: pymelts.Melt
   :members:
   :undoc-members:

.. autoclass:: pymelts.MeltCollection
   :members:
   :undoc-members:

Data classes
------------
.. _data_classes:

.. autoclass:: pymelts.Composition
   :members:
   :undoc-members:


Reading files
-------------
.. _reading_files:
.. py:module:: pymelts.readers

Some functions to read in a MELTS output folder and make it available to Python. The functions here are designed for a MELTS run which has already been done with the standalone MELTS solver, and all you want to do is read in the data.

.. autofunction::read_config_file
.. autoclass:: pymelts.readers.Reader
    :members:

Other utilities
---------------
.. _utilities:
.. py:module:: pymelts.utilities

Some other useful functions which don't really fit anywhere else

.. autofunction:: pymelts.utilities.celsius
.. autofunction:: pymelts.utilities.kelvin
.. autofunction:: pymelts.utilities.cycle_cmap

Raw bindings to libMELTSdynamic
-------------------------------
.. _raw_bindings:
.. py:module:: pymelts.melts_functions

You shouldn't need to call these functions directly, as their functionality is bound up in the other classes and their methods. But they're included here if you're interested in extending what I've done already

TODO: complete this
