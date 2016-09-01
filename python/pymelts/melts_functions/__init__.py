#!/usr/bin/env 
""" file:pymelts/bindings/__init__.py
    author: Mark S. Ghiorso
    date: August 30, 2016

    description: Bindings to the MELTSdynamic library.
"""

from melts_bindings import *

__all__ = [get_oxide_names, get_phase_names, get_status_string, get_phase_properties, set_calculation_mode, drive_melts]