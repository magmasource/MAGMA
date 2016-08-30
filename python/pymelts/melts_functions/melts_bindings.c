/*  file: melts_bindings.c
    author: Jess Robertson, CSIRO Earth Science and Resource Engineering
    date: Wednesday 10 October 2012

    description: Implementation file for Python bindings to MELTS library
*/

#include "melts_bindings.h"

// DATA TRANSFER CODE
/*  Prints an aribtrary PyObject instance using the str method (same as 
    print statement in Python).
*/
void pyprint(PyObject* object) {
    char* str = PyString_AsString(PyObject_Str(object));
    if (PyErr_Occurred()) PyErr_Print();
    else { 
        printf("%s\n", str);
    }
}

/*  Convert a Composition object into a list of oxide values as doubles
    Note that the order of oxide values is maintained by the Composition 
    instance within Python, so we can just pull out a direct list of 
    values and copy over to oxideValues.
*/
static void convert_composition(PyObject* composition, double* oxideValues)
{
    // Set up memory
    int i, length = PySequence_Length(composition);
    if (PyErr_Occurred()) PyErr_Print();

    // Copy over data and return
    for (i = 0; i < length; i++) {
        oxideValues[i] = PyFloat_AsDouble(PyList_GetItem(composition, i));
        if (PyErr_Occurred()) PyErr_Print();
    }
}

// Getting MELTS solver status strings
static PyObject* py_get_status_string(PyObject* self, PyObject* args)
{
    // Set up some storage
    int flag, stringLength = 100;
    char errorString[stringLength];

    // Parse arguments
    PyArg_ParseTuple(args, "i", &flag);
    if (PyErr_Occurred()) PyErr_Print();

    // Pass info through to MELTSdynamic
    meltsgeterrorstring_(&flag, errorString, &stringLength);
    return PyString_FromString(errorString);
}

// Getting names from MELTS
static PyObject* py_get_oxide_names(PyObject* self, PyObject* args) 
{
    int i;
    
    // Allocate a list to return to Python.
    PyObject *nameList = PyList_New(0);

    // Convert labels to Python strings, add to list
    for (i = 0; i < nc; i++) {
        PyObject* oxideString = PyString_FromString(bulkSystem[i].label);
        PyList_Append(nameList, oxideString);
        if (PyErr_Occurred()) PyErr_Print();
        Py_DECREF(oxideString); // Release reference to object on heap
    }
    Py_INCREF(nameList); // Python expects a new reference on return
    return nameList;
}
static PyObject* py_get_phase_names(PyObject* self, PyObject* args)
{
    int i;

    // Allocate a list to return to Python. 
    PyObject* phaseList = PyList_New(0);

    // Convert phase names to Python strings, append to list
    for (i = 0; i < npc; i++)
        if (solids[i].type == PHASE) {
            PyObject* phaseString = PyString_FromString(solids[i].label);
            if (PyErr_Occurred()) PyErr_Print();
            PyList_Append(phaseList, phaseString);
            if (PyErr_Occurred()) PyErr_Print();
            Py_DECREF(phaseString); // Release reference to object on heap
        }
    PyList_Append(phaseList, PyString_FromString("system"));
    PyList_Append(phaseList, PyString_FromString("liquid"));

    // Return reference to return
    Py_INCREF(phaseList); // Python expects a new reference on return
    return phaseList;
}

// Get phase data
static PyObject* py_get_phase_properties(PyObject* self, PyObject* args) 
{
    /*  Set up some storage for the phase properties - the docs for 
        the getMeltsPhaseProperties function is: 

        Input:
            phaseName    - string as returned from meltsGetPhaseNames 
            temperature  - Temperature in Kelvins of the node
            pressure     - Pressure in bars of the node 
            bulkComposition - Bulk composition of the phase in grams of
                                oxides    

        Output:
            1-d array, properties in the order G, H, S, V, Cp, dCpdT, dVdT, \
            dVdP, d2VdT2, d2VdTdP, d2VdP2
    */
 
    /*  Parse arguments to retrieve the phase name and properties as required
        Arguments come in from Python as phasename, temperature, pressure and 
        a composition dictionary.
    */
    char* phaseName;
    double temperature, pressure;
    PyObject* compositionObject;
    PyArg_ParseTuple(args, "sddO", &phaseName, &temperature, &pressure, 
        &compositionObject);
    if (PyErr_Occurred()) PyErr_Print();

    // Convert composition object from a dictionary type to a list of floats. 
    // Note that the python side code maintains the order of oxides for MELTS.
    double composition[nc];
    convert_composition(compositionObject, composition);

    // Pass result through to MELTS
    int numberProperties = 11;
    double phaseProperties[numberProperties];
    getMeltsPhaseProperties(phaseName, &temperature, &pressure, composition, phaseProperties);

    // Build dictionary to pass back to Python
    // We can parse the results using py_phase_property_keys
    char* phasePropertyKeys[] = {"G", "H", "S", "V", "Cp", "dCpdT", "dVdT", 
        "dVdP", "d2VdT2", "d2VdTdP", "d2VdP2"};
    PyObject* resultsDict = PyDict_New();
    int i;
    for (i = 0; i < numberProperties; ++i) {
        PyDict_SetItem(resultsDict, 
            PyString_FromString(phasePropertyKeys[i]),
            PyFloat_FromDouble(phaseProperties[i]));
        if (PyErr_Occurred()) PyErr_Print();
    }
    Py_INCREF(resultsDict);
    return resultsDict;
}

// Drive MELTS simulation
/*  TODO: need to rewrite this to make silmanState available from Python.
    
    The key here is to generate a silminstate structure from the Python input. Most of this is a rewritten interface from the library.c code, however we mirror some of the code here so that we can make a tighter binding to the Python data structures.

    Mainly we want to pull in the information from a Python dictionary on initialisation. This is because we don't have to worry about users wanting to set data after a call to the MELTS solver (since all this will be done in Python already). This reduces the amount of work that we have to do on the C side. On the flipside, we want to be able to assign a node number to the Melt instance on initialization, since this will not be exposed to the Python user anyway. So we have to seperate out the details of intiializing a SilmanState object, make it available to Python, have all the setting of a state in Python and then pass things back to C properly (see the details in Chapter 17.6 of Beginning Python, in Safari Books).

    This is all a bit complex at the moment. For the time being, we'll just write a simple function that takes a Melt instance, pulls out the relevant information and passes it to driveMeltsProcess.
*/
static PyObject* py_drive_melts(PyObject* self, PyObject* args) {
    // Get some information about struct sizes etc
    char* propertyKeys[] = {"G", "H", "S", "V", "Cp", "dCpdT", "dVdT", 
        "dVdP", "d2VdT2", "d2VdTdP", "d2VdP2", "SiO2", "TiO2", "Al2O3", 
        "Fe2O3", "Cr2O3", "FeO", "MnO", "MgO", "NiO", "CoO", "CaO", "Na2O", 
        "K2O", "P2O5", "H2O", "CO2", "SO3", "Cl2O-1", "F2O-1", "FeO1_3", 
        "volume fraction", "density", "viscosity"};
    const int numberProperties = nc + 14;

    // Parse arguments from Python side
    int nodeIndex, modeIndex;
    double pressure, temperature, enthalpy, composition[nc];
    PyObject* compositionObject;
    PyArg_ParseTuple(args, "iidddO", &nodeIndex, &modeIndex, &pressure, &temperature, &enthalpy, &compositionObject);
    if (PyErr_Occurred()) PyErr_Print();
    convert_composition(compositionObject, composition);
    if (PyErr_Occurred()) PyErr_Print();

    // Allocate return memory
    int propIndex, phaseIndex;
    int nCharInName = 20, numberPhases = 20;
    int iterations, status;
    int phaseIndices[numberPhases];
    double propertyArray[numberProperties * numberPhases];
    char phaseNames[numberPhases * nCharInName];

    // Pass through to library
    meltsprocess_(&nodeIndex, &modeIndex, &pressure, composition,
        &enthalpy, &temperature, phaseNames, &nCharInName, &numberPhases,
        &iterations, &status, propertyArray, phaseIndices);

    // Wrap results in a dictionary
    PyObject* resultsDict = PyDict_New();
    for (phaseIndex=0; phaseIndex < numberPhases; phaseIndex++) {
        PyObject* phaseDict = PyDict_New();
        char* phase = &phaseNames[phaseIndex * nCharInName];
        for (propIndex = 0; propIndex < numberProperties; ++propIndex) {
            PyDict_SetItem(phaseDict, 
                PyString_FromString(propertyKeys[propIndex]),
                PyFloat_FromDouble(
                    propertyArray[numberProperties * phaseIndex + propIndex]));
            if (PyErr_Occurred()) PyErr_Print();
        }
            
        // Push current dictionary to list of dicts
        Py_INCREF(phaseDict);
        PyObject* phaseName = PyString_FromString(phase);
        PyDict_SetItem(resultsDict, phaseName, phaseDict);
        if (PyErr_Occurred()) PyErr_Print();
    }

    // Add extrinsic system variables
    PyObject* systemDict = PyDict_New();
    PyDict_SetItem(systemDict, 
        PyString_FromString("pressure"), PyFloat_FromDouble(pressure));
    PyDict_SetItem(systemDict, 
        PyString_FromString("temperature"), PyFloat_FromDouble(temperature));
    PyDict_SetItem(systemDict, 
        PyString_FromString("enthalpy"), PyFloat_FromDouble(enthalpy));
    PyDict_SetItem(systemDict, 
        PyString_FromString("composition"), compositionObject);
    Py_INCREF(resultsDict);
    PyDict_SetItem(resultsDict, 
        PyString_FromString("system variables"), systemDict);

    // Wrap information about solution in another dictionary
    int nCharInString=150;
    char errorString[nCharInString];
    meltsgeterrorstring_(&status, errorString, &nCharInString);
    PyObject* infoDict = PyDict_New();
    PyDict_SetItem(infoDict, 
        PyString_FromString("status_msg"), PyString_FromString(errorString));
    PyDict_SetItem(infoDict, 
        PyString_FromString("iterations"), PyInt_FromLong(iterations));
    Py_INCREF(infoDict);
    PyDict_SetItem(resultsDict, PyString_FromString("status"), infoDict);

    // Send results back as dictionary to Python
    Py_DECREF(compositionObject);
    Py_INCREF(resultsDict);
    return resultsDict;
}

// Bind the Python functions to the C functions 
static PyMethodDef melts_bindings_methods[] = 
{
    {"get_oxide_names", py_get_oxide_names, METH_NOARGS,
        "Returns the oxide names for the chemical species used by MELTS.\n\nReturns a list of strings, each of which contains one oxide used\nby MELTS. These oxide names are also used to structure the datan\ndictionaries in PyMELTS, so this function can be useful for\ngenerating a list of oxide names.\n\nReturns:\n\tA list of oxide strings."},
    {"get_phase_names", py_get_phase_names, METH_NOARGS,
        "Returns the phase names for the solid and liquid phases used by MELTS.\n\nReturns a list of strings, each of which contains one phase used\nby MELTS. These phase names are also used to structure the datan\ndictionaries in PyMELTS, so this function can be useful for\ngenerating a list of phase names.\n\nReturns:\n\tA list of phase strings."},
    {"get_status_string", py_get_status_string, METH_VARARGS,
        "Decode a MELTS status number\n\nTurns a status flag from melts into a nice human error string.\nAs an example:\n\n>>> from pymelts.melts_functions import *\n>>> get_status_string(0)\n'Successful run. No errors.'\n\n>>> [get_status_string(i) for i in range(100, 108)]\n['Steplength for linear search tending towards zero.',\n'Steplength for linear search tending towards maximum.',\n'Error condition detected in adding a liquid to the assemblage (1).',\n'Error condition detected in adding a liquid to the assemblage (2)',\n'Error condition detected in adding a liquid to the assemblage (3)',\n'Rank deficiency coondition detected.  Most likely a consequence of\nphase rule violation.',\n'Time limit exceeded.',\n'Unspecified internal fatal error.']\n\nArguments:\n\tflag - an integer flag returned from MELTS.\n\nReturns:\n\ta string containing the error message."},
    {"get_phase_properties", py_get_phase_properties, METH_VARARGS,
        "No docstring yet - fix me!"},
    {"drive_melts", py_drive_melts, METH_VARARGS,
        "No docstring yet - fix me!"},
    {NULL, NULL, 0, NULL}
};

// Python calls this to let us initialize our module
void initmelts_bindings() {
    (void) Py_InitModule("melts_bindings", melts_bindings_methods);
}