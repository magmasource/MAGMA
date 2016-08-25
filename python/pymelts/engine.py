#!/usr/bin/env python
""" 
 .. module: engine.py
 .. mmoduleauthor: Jess Robertson, CSIRO Earth Science and Resource Engineering
    date: Tuesday 16 October 2012

    :synopsis: Implements a class to store the global details of the MELTS 
        solver. This class is generally only called internally by pymelts.Melts instances.
"""

import melts_functions
# import numpy

class Engine(object):

    """ Engine stores the (global) details of the MELTS engine state.

        This class is implemented using a 'Borg' singleton pattern (see http://bit.ly/Pz9fFi), i.e. all instances of Engine share the same data. This is becuase there should only be one instance of MELTS running on your machine at any time. However you can create instances with impunity and know that their data will just reflect the global state.

        It also simplifies generating MeltCollection arrays - if you have a new config file you want to read in then you can just do it, and the new calculations will be assigned node names etc in the global MELTS state without you having to worry.

        Generally you don't have to worry about the melts engine - it will be called internally by Melt instances.
    """

    __shared_state = {}

    def __init__(self):
        # Implement Borg link
        self.__dict__ = self.__shared_state

        # Initialize library if required
        if not self.is_initialized():
            melts_functions.initialize_library()
            self.melts = {}
            self.node_indices = [-1]

    def register_melt(self, melt_instance):
        """ Generates a new node number which links to the solver.
        """
        # Get a new node id
        node_index = self.node_indices[-1] + 1
        self.node_indices.append(node_index)

        # Make a new Melt instance, crosslink with stored melts instances
        melt_instance.node_index = node_index
        self.melts[node_index] = melt_instance

    def get_phase_names(self):
        """ Returns the phase names for the solid and liquid phases used by 
            MELTS.
        
            Returns a list of strings, each of which contains one phase used by MELTS. These phase names are also used to structure the data dictionaries in PyMELTS, so this function can be useful for generating a list of phase names.
            
            Returns:
                    A list of phase strings.
        """
        try:
            return self.phase_names
        except AttributeError:
            self.phase_names = melts_functions.get_phase_names()
            return self.phase_names

    def get_oxide_names(self):
        """ Returns the oxide names for the chemical species used by MELTS.
        
            Returns a list of strings, each of which contains one oxide used by MELTS. These oxide names are also used to structure the data dictionaries in PyMELTS, so this function can be useful for generating a list of oxide names.
            
            Returns:
                    A list of oxide strings.
        """
        try:
            return self.oxide_names
        except AttributeError:
            self.oxide_names = melts_functions.get_oxide_names()
            return self.oxide_names

    def is_initialized(self):
        """ Checks whether MELTS has been initialised.
        """
        return melts_functions.is_melts_initialized()

    def clear(self):
        """ Clear all stored data and melt IDs, and reinitialize the melts 
            library.
        """
        del self.melts
        del self.node_indices
        melts_functions.initialize_library()