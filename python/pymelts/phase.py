#!/usr/bin/env python
""" 
 .. module: phase.py
 .. moduleauthor: Mark S. Ghiorso
    date: October 24, 2016

    :synopsis: Calculates thermodynamic properties of a phase in the MELTS collection
"""

import melts_functions
from composition import Composition
from engine import Engine

class Phase(object):

    """ Retrieves properties of a phase in the MELTS collection

        Arguments:
        	nameString - name of the phase  
            composition - a dictionary with the composition given as oxide weight percentages and the oxide values as keys. Optional - the default is None 
            calculationString - calculation database, one of MELTS_v1.0.2, MELTS_v1.1.x, MELTS_v1.2.x, pMELTS_v5.6.1
            kwargs - optional arguments which set any attributes of the class on initialization. These can also be set by accessing these attributes directly after initialization.
    """

    def __init__(self, nameString='none', composition=None, calculationString='MELTS_v1.0.2', **kwargs):
        super(Phase, self).__init__()

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
        self.oxides = self.engine.get_oxide_names()
        self.all_phases = self.engine.get_phase_names()

        if nameString not in self.all_phases:
            raise ValueError("Phase {0} is not one of {1}".format(nameString, self.all_phases))

        # Set up attributes, calculation flags etc
        self.phaseName = nameString
        self.composition = Composition(**composition)
        self.properties = {}
        self.__dict__.update(kwargs)
        self.calculationDatabase = calculationString

    def get_properties(self, temperature, pressure):
    	results = melts_functions.get_phase_properties(self.phaseName, temperature, pressure, self.composition)
    	return results

    def get_phase_component_number(self, nameString='none', calculationString='MELTS_v1.0.2', **kwargs):
    	if nameString not in self.all_phases:
            raise ValueError("Phase {0} is not one of {1}".format(nameString, self.all_phases))
        return melts_functions.get_phase_component_number(nameString)
    
    def get_phase_component_names(self, nameString='none', calculationString='MELTS_v1.0.2', **kwargs):
     	if nameString not in self.all_phases:
            raise ValueError("Phase {0} is not one of {1}".format(nameString, self.all_phases))
        return melts_functions.get_phase_component_names(nameString)

    def get_phase_component_formulas(self, nameString='none', calculationString='MELTS_v1.0.2', **kwargs):
     	if nameString not in self.all_phases:
            raise ValueError("Phase {0} is not one of {1}".format(nameString, self.all_phases))
        return melts_functions.get_phase_component_formulas(nameString)