#!/usr/bin/env python
""" 
 .. module: composition.py
 .. moduleauthor: Jess Robertson, CSIRO Earth Science and Resource Engineering

    :synposis: Composition class for MELTS solver
"""

import numpy
from collections import OrderedDict
from engine import Engine

class Composition(list):
    """ List/Dictionary class which stores a compsition in the right format 
        for MELTS.

        The list of oxides which can be stored is given in the oxide_keys 
        attribute. Any oxides which do not have a specified weight default 
        to zero, so you can just specify the non-zero ones.

        However because it's more useful to set oxide weights by name than by 
        their position in the vector, Composition uses dictionary semantics 
        when getting and setting values. Thus we can do something like:

            >>> c = pymelts.Composition()
            >>> c['SiO2'] = 42.9
            >>> print c['SiO2']
            42.9

        although the default setting for Compositions is to act like a list.

            >>> print c
            [42.9, 0., 0., 0. ... 0.]

        Input:
            verbose - a flag which sets whether Composition prints warnings 
                when you give it information which it doesn't understand.
            kwargs - a list of oxides and weight percentages. For the valid 
                keys, see the oxide_keys attribute. Keys which do not will be 
                ignored (silently if verbose=False).
    """
    
    print_columns = 3

    def __init__(self, verbose=True, **kwargs):
        # Get allowed oxide keys from melts_engine - the order returned is 
        # how MELTS expects to recieve oxides
        self.engine = Engine()
        self.oxide_keys = self.engine.get_oxide_names()
        self.verbose = verbose

        # Initialise an empty dictionary with the keys in order
        self.orderdict = OrderedDict(
            zip(self.oxide_keys, numpy.zeros(len(self.oxide_keys))))

        # Add the supplied values as required
        self.update(kwargs)

    def __getitem__(self, key):
        """ Returns the value associated with the given oxide.
        """
        if key in self.oxide_keys:
            return self.orderdict[key]
        elif self.verbose:
            print ("Warning: {0} is not a valid oxide key - I'm just"
                    + " going to ignore it.").format(key)
            return None

    def __setitem__(self, key, value):
        """ Sets the value associated with the given oxide key
        """
        if key in self.oxide_keys:
            self.orderdict[key] = value
        elif self.verbose:
            print ("Warning: {0} is not a valid oxide key - I'm just"
                    + " going to ignore it.").format(key)
        super(Composition, self).__init__(self.orderdict.values())

    def keys(self):
        """ Returns a list of oxide keys in order.
        """
        return self.oxide_keys

    def normalize(self, total=100):
        """ Normalises the weight percentages (in place) so that the sum 
            equals the given total.

            Input:
                total - the total which the weights should sum to (optional: 
                    defaults to 100[%])
        """
        cur_total = sum(self)
        self = [total * value / cur_total for value in self]

    def pretty_print(self):
        """ Pretty printer for composition dicts
        """
        output_string = ""
        for i, item in enumerate(zip(self.oxide_keys, self)):
            output_string += "\t{0}\t= {1:4f}".format(*item)
            if (i % self.print_columns == self.print_columns - 1):
                output_string += "\n"
        return output_string + "\n"

    def update(self, valuedict):
        """ Updates a Composition with the contents of the supplied dictionary
        """
        for key, value in valuedict.iteritems():
            self[key] = value
