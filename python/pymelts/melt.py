#!/usr/bin/env python
""" 
 .. module: melt.py
 .. moduleauthor: Mark S. Ghiorso (original: Jess Robertson, CSIRO Earth Science and Resource Engineering)
    date: August 30, 2016

    :synopsis: Implementations of a single MELTS calculation (Melt) and 
        classes to generate collections of these (MeltCollection)
"""

from collections import defaultdict
import itertools
import numpy
import melts_functions
from composition import Composition
from engine import Engine

class Melt(object):

    """ Stores the details of a single 'node' in the MELTS solver. 

        Many of the methods defined here are just simple bindings to drive the 
        underlying MELTS solver, however having them defined as Python 
        functions means that we get all the Python function goodies (keywords, 
        default arguments etc) for free.

        On initialization the Melt instance registers itself with the 
        underlying MELTS solver and sets up some basic attributes, which can 
        be set directly::

            >>> melt = Melt()
            >>> melt.temperature, melt.pressure = 1250, 1
            >>> melt.composition = Composition(SiO2=56.6, MgO=23.4) 
            >>> melt.solve()

        All attributes are set to None on initialization if no values are 
        specified.

        Arguments:
            composition - a dictionary with the composition given as oxide weight percentages and the oxide values as keys. Optional - the default is None 
            mode - a string which specifies the calculation space. This can be one of 'ptx' (pressure-temperature-composition space), 'phx' (pressure-enthalpy-composition), 
            'psx' (pressure-entropy-composition), 'vtx' (volume-temperature-composition) or 'liquidus' (find liquidus fuction). Optional - the default is 'ptx'.
            solve - whether to call the MELTS solver to calculate phase equilibria on initialization. Optional - the default is False.
            calculationString - calculation database, one of MELTS_v1.0.2, MELTS_v1.1.x, MELTS_v1.2.x, pMELTS_v5.6.1
            kwargs - optional arguments which set any attributes of the class on initialization. These can also be set by accessing these attributes directly after initialization.
    """
    # Allowed modes for the calculation
    mode_keys = ['liquidus', 'ptx', 'phx', 'psx', 'vtx']
    
    # This is the list of keys in the results dictionary from the bindings 
    # which are not phase properties.
    nonphase_keys = ['system', 'system variables', 'status']
            
    def __init__(self, composition=None, mode='ptx', solve=False, calculationString='MELTS_v1.0.2', **kwargs):
        super(Melt, self).__init__()

        # Choose database for MELTS calculations
        if calculationString == 'MELTS_v1.0.2':
            melts_functions.set_calculation_mode('MELTS_v1.0.2')
        elif calculationString == 'MELTS_v1.1.x':
            melts_functions.set_calculation_mode('MELTS_v1.1.x')
        elif calculationString == 'MELTS_v1.2.x':
            melts_functions.set_calculation_mode('MELTS_v1.2.x')
        elif calculationString == 'pMELTS_v5.6.1':
            melts_functions.set_calculation_mode('pMELTS_v5.6.1')
        else:
            err = "calculationString is not one of MELTS_v1.0.2, MELTS_v1.1.x, MELTS_v1.2.x, pMELTS_v5.6.1"
            raise ValueError(err)

        # Set up link to MELTS engine
        self.engine = Engine()
        self.node_index = None
        self.engine.register_melt(self)
        if self.node_index is None:
            raise ValueError('Error initializing node with MELTS engine')
        self.oxides = self.engine.get_oxide_names()
        self.all_phases = self.engine.get_phase_names()

        # Set up attributes, calculation flags etc
        self.composition = Composition(**composition)
        self.properties = {}
        self.phases = []
        self.pressure = None
        self.temperature = None
        self.enthalpy = None
        self.entropy = None
        self.volume = None
        self.__dict__.update(kwargs)
        self.set_mode(mode)
        self.calculationDatabase = calculationString

        # Solve if required
        if solve:
            self.solve()

    def __repr__(self):
        """ Pretty printing so that things make sense.
         ARE THESE UNITS REALLY CORRECT??
        """
        output_string = ("\nMelt parameters: P = {0.pressure} kPa, " 
                         + "T = {0.temperature} deg C, "
                         + self.enthalpy and "H = {0.enthalpy} J"
                         + self.entropy and "S = {0.entropy} J/K"
                         + self.volume and "V = {0.volume} cc"
                         + "\nBulk composition:\n{0.composition}"
                         + "\nPhases present:\n{0.phases}")
        return output_string.format(self)

    def solve(self):
        """ Solve using MELTS.
        """
        # Convert NoneTypes to zeros
        pressure = self.pressure or 0
        temperature = self.temperature or 0

        # For backwards compatibility make sure enthalpy = 0 for 'find liquidus'        
        reference = self.get_ref(self.mode_index)
        
        # Pass arguments through to the drive_melts C function
        results = melts_functions.drive_melts(self.node_index, 
            self.mode_index, pressure, temperature, reference, 
            self.composition)
        # import pdb; pdb.set_trace()
        self.status = results['status']
        self.phases = [k for k in results.keys() if k != self.nonphase_keys]
        self.pressure = results['system variables']['pressure']
        self.temperature = results['system variables']['temperature']
        self.enthalpy = results['system variables']['enthalpy'] or None
        self.entropy = results['system variables']['entropy'] or None
        self.volume = results['system variables']['volume'] or None
        
        # For each phase we need to cut out the oxide values and stick them 
        # back into a Composition instance
        oxide_names = self.engine.get_oxide_names()
        for phase in self.phases:
            self.properties[phase] = {'composition': {}}
            for key, value in results[phase].iteritems():
                if key in oxide_names:
                    self.properties[phase]['composition'][key] = value
                else:
                    self.properties[phase][key] = results[phase][key]
            self.properties[phase]['composition'] = \
                Composition(**self.properties[phase]['composition'])

    def set_mode(self, modestring):
        """ Sets the mode for the calculation. 

            Arguments:
                modestring - a string which specifies the calculation space. This can be one of 'ptx' (pressure-temperature-composition space),
                'phx' (pressure-enthalpy-composition), 'psx' (pressure-entropy-composition), 'vtx' (volume-temperature-composition) or 'liquidus' (find liquidus fuction).

        """
        if modestring == 'liquidus':
            self.mode_index = 0
        elif modestring == 'ptx':
            self.mode_index = 1
        elif modestring == 'phx':
            self.mode_index = 2
        elif modestring == 'psx':
            self.mode_index = 3
        elif modestring == 'vtx':
            self.mode_index = 4
        else:
            err = "Mode {0} is not one of {1}"
            raise ValueError(err.format(modestring, self.mode_keys))
 
    def get_ref(self, modeindex):
        """ Sets the mode for the calculation. 

            Arguments:
                modestring - a string which specifies the calculation space. This can be one of 'ptx' (pressure-temperature-composition space),
                'phx' (pressure-enthalpy-composition), 'psx' (pressure-entropy-composition), 'vtx' (volume-temperature-composition) or 'liquidus' (find liquidus fuction).

        """
        if modeindex == 0:
            ref_value = 0
        elif modeindex == 1:
            ref_value = 0
        elif modeindex == 2:
            ref_value = self.enthalpy or 0
        elif modeindex == 3:
            ref_value = self.entropy or 0
        elif modeindex == 4:
            ref_value = self.volume or 0
        else:
            ref_value = 0
        return ref_value
        
    def get_properties(self, phase):
        """ Returns the properties of the given phase.
        """     
        # Check that phase name is valid
        if phase not in self.engine.get_phase_names():
            raise ValueError("Phase {0} is not one of {1}".format(
                phase, self.engine.get_phase_names()))
        return self.properties[phase]

class MeltCollection(list):

    """ Stores MELTS calculated information for a number of different 
        calculations but using the same composition.

        MeltCollections acts like a sequence of MELTS calculations, but with a 
        few helper methods to make it easier to obtain lists of data varying 
        over a given set of parameters (e.g. temperature/pressure/enthalpy), 
        while using the ability of MELTS to remember prior calculations.

        Arguments:
            composition - a pymelts.Composition instance specifying the composition for all the melts
            **variables - a dictionary of variables to vary. Each member of the variables dict should contain a minimum value, maximum value and the step sizea. These are expanded into an array of values using numpy.arange.
    """

    def __init__(self, composition, **variables):
        # Initialise data sequences
        super(MeltCollection, self).__init__([])
        self.variables = {}
        self.composition = composition

        # Generate melts variables
        for key, values in variables.items():
            if type(values) is tuple:
                if values[2] < 1e-6:
                    self.variables[key] = [values[0]]
                else:
                    minv, maxv, stepv = values
                    numbersteps = int((minv - maxv) / float(stepv))
                    self.variables[key] = numpy.linspace(minv, maxv, 
                        numbersteps)
            else:
                self.variables[key] = [values]

        # Generate product array of Melts instances over variables
        keys = self.variables.keys()
        # import pdb; pdb.set_trace()
        for values in itertools.product(*self.variables.values()):
            print values
            self.append(Melt(
                composition=self.composition,
                **dict(zip(keys, values))))
