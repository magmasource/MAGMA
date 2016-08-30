/*  file: melts_bindings.h
    author: Jess Robertson, CSIRO Earth Science and Resource Engineering
    date: Wednesday 10 October 2012

    description: Header file for Python bindings to MELTS library. These are eventually exposed in Python under the pymelts.melts_functions submodule.
*/

#ifndef _PYMELTS_BINDINGS_H_123491543
#define _PYMELTS_BINDINGS_H_123491543

/*  Gotta include Python first.
    Also pulls in the following general headers from system: 

        stdio.h, string.h, errono.h, limits.h, assert.h and stdlib.h 

    See docs.python.org/c-api/intro.html#include-files for details
*/    
#include <Python.h>

// Headers from MELTS
#include "silmin.h"
#include "status.h"

// Relevant state variables
MeltsStatus meltsStatus;

// Some declarations from library.c which stop the implicit function warnings 
// when compiling.
void meltsgetoxidenames_(char oxideNames[], int *nCharInName, int *numberOxides);
void meltsgetphasenames_(char phaseNames[], int *nCharInName, int *numberPhases, int phaseIndices[]);
void meltsgeterrorstring_(int *status, char *errorString, int *nCharInName);
void getMeltsPhaseProperties(char *phaseName, double *temperature, 
    double *pressure, double *bulkComposition, double *phaseProperties);
void meltsprocess_(int *nodeIndex, int *mode, double *pressure, 
    double *bulkComposition, double *enthalpy, double *temperature, 
    char phaseNames[], int *nCharInName, int *numberPhases, int *iterations, 
    int *status, double *phaseProperties, int phaseIndices[]);
void meltssetsystemproperty_(int *nodeIndex, char *property);
void meltsgetphaseproperties_(char *phaseName, double *temperature, 
         double *pressure, double *bulkComposition, double *phaseProperties);

/*  Functions available in Python - note that these are static but exposed 
    during initialization of the Python extension. In the Python namespace, 
    these have the py_* prefix removed. It's here to distinguish between 
    python and C functions of the same name.
*/
static PyObject* py_get_status_string(PyObject* self, PyObject* args);
static PyObject* py_get_oxide_names(PyObject* self, PyObject* args);
static PyObject* py_get_phase_names(PyObject* self, PyObject* args);
static PyObject* py_get_phase_properties(PyObject* self, PyObject* args);
static PyObject* py_drive_melts(PyObject* self, PyObject* args);

// This is the boilerplate function which generate the Python module for us
void initmelts_bindings(void);

#endif