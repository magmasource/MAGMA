/*
 * Exception classes for phases class hierarchy
 * Victor Kress
 * Seatle, 2004
 */

#include "PhaseExceptions.h"
#include <string.h>
#include <iostream>

using namespace std;

PhaseError::PhaseError(errorType _type,errorSeverity _severity,
			    char *_caller,char *_description) {
  int l;
  type = _type;
  severity = _severity;
  if (_caller) {
    l = strlen(_caller);
    caller = new char[l+1];
    strncpy(caller,_caller,l);
    caller[l]='\0';
  }
  else {
    caller = NULL;
  }
  if (_description) {
    l = strlen(_description);
    description = new char[l+1];
    strncpy(description,_description,l);
    caller[l]='\0';
  }
  else {
    description = NULL;
  }
  return;
}
PhaseError::~PhaseError() {
  delete []caller;
  delete []description;
  return;
}

void PhaseError::printErr() {
  /// severity
  if (severity==WARNING) {
    cout << endl << "Warning: ";
  }
  else if (severity==SERIOUS) {
    cout << endl << "Serious error: ";
  }
  else if (severity==FATAL) {
    cout << endl << "Fatal error: ";
  }
  // type
  if (type == INVALID) {
    cout << "Invalid data error ";
  }
  else if (type == BOUNDS) {
    cout << "Data out of bounds error ";
  }
  else if (type == STATE) {
    cout << "Phase state error ";
  }
  else if (type == CALCULATION) {
    cout << "Calculation error ";
  }
  // caller
  if (caller) {
    cout << "called by " << caller << ":" << endl;
  }
  // description
  if (description) {
    cout << description << endl;
  }
  return;
}
