#!/usr/bin/env python
""" file: utilities.py
    author: Mark S. Ghiorso (original: Jess Robertson, CSIRO Earth Science and Resource Engineering)
    date: August 31, 2016 

    description: Some utilities for plotting with Matplotlib and other miscellaneous routines.
"""

import numpy
import matplotlib.pyplot

# Functions to convert things
def celsius(kelvin_temp):
    """ Convert degrees Kelvin to degrees Celsius

        Arguments:
            kelvin_temp: the temperature in degrees Kelvin

        Returns:
            the temperature in degrees Celsius
    """
    return kelvin_temp - 273.15

def kelvin(celsius_temp):
    """ Convert degrees Celsius to degrees Kelvin

        Arguments:
            celsius_temp: the temperature in degrees Celsius

        Returns:
            the temperature in degrees Kelvin
    """
    return celsius_temp + 273.15

# Plotting functions
def cycle_cmap(cmap='YlOrBr', length=50, verbose=False):
    """ Set default color cycle of matplotlib to a given colormap `cmap`.
    
        The default color cycle of matplotlib is set to evenly distribute colors in color cycle over specified colormap. Colormaps listed in `REVERSE_CMAP` will be cycled in reverse order. Certain colormaps have pre-specified color ranges in `cmap_range`. These variables ensure that colors cycle from light to dark and light colors are not too close to white. Note that when `length` is large (> ~10), it is difficult to distinguish between successive lines because successive colors are very similar.

        This function has been stolen blatantly from an example shared by Tony Yu on the Matplotlib mailing list: `http://www.mail-archive.com/matplotlib-users@lists.sourceforge.net/msg20979.html`.

        Arguments:
            cmap: name of a matplotlib colormap (see matplotlib.pyplot.cm)
            length: the number of colors used before cycling back to first color. 
        
        Returns:
            a list of RGBA color values to pass to `matplotlib.axes.set_color_cycle`.          
    """
    reverse_cmap = ['summer', 'autumn', 'winter', 'spring', 'copper']
    cmap_range = dict(
        gray    = {'start':200, 'stop':0},
        Blues   = {'start':60, 'stop':255},
        Oranges = {'start':60, 'stop':255},
        OrRd    = {'start':60, 'stop':255},
        BuGn    = {'start':60, 'stop':255},
        PuRd    = {'start':60, 'stop':255},
        YlGn    = {'start':60, 'stop':255},
        YlGnBu  = {'start':60, 'stop':255},
        YlOrBr  = {'start':60, 'stop':255},
        YlOrRd  = {'start':60, 'stop':255},
        hot     = {'start':230, 'stop':0},
        bone    = {'start':200, 'stop':0},
        pink    = {'start':160, 'stop':0}
    )
    
    # Generate color list
    if cmap in reverse_cmap:
        crange = dict(start=255, stop=0)
    elif cmap in cmap_range:
        crange = cmap_range[cmap]
    else:
        if verbose:
            print ('{0} not in list of preset colormaps;' +
                'will use whole range of map').format(cmap)
        crange = dict(start=0, stop=255)
    if length > abs(crange['start'] - crange['stop']):
        if verbose:
            print ('The input length is greater than the number of' +
               'colors in the colormap; some colors will be repeated')
    idx = [int(i) for i in
        numpy.linspace(crange['start'], crange['stop'], length)]
    colors = getattr(matplotlib.pyplot.cm, cmap)(idx)
    
    # Update current axes with default colors
    return colors.tolist()
