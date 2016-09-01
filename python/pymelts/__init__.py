#!/usr/bin/env 
""" file:pymelts/bindings/__init__.py
    author: Mark S. Ghiorso (original: Jess Robertson, CSIRO Earth Sciences and Resource Engineering)
    date: Thursday August 25, 2016

    description: Bindings to the MELTSdynamic library.
"""

import melts_functions
import readers
import utilities
from composition import Composition
from engine import Engine
from melt import Melt, MeltCollection

base_classes = [Composition, Engine, Melt, MeltCollection]
__all__ = base_classes + [melts_functions, readers]

# Reassign the base classes to the base namespace
for obj in base_classes:
    obj.__module__ = 'pymelts'
