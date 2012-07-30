/*
 * Exception classes for phases class hierarchy
 * Victor Kress
 * Seatle, 2004
 */
#ifndef PHASEEXCEPTIONS_H
#define PHASEEXCEPTIONS_H

/**
   valid error types.
   INVALID: input data not valid
   BOUNDS: input data out of bounds for this phase
   STATE: Phase is in invalid state for requested calculation
   CALCULATION: internal calculation error
*/
enum errorType {INVALID,BOUNDS,STATE,CALCULATION};

/**
   valid error severities
   WARNING: Phase remains in usable state.  Retry with valid data.
   SERIOUS: Phase may not be in usable state. Future calcs suspect.
   FATAL: All hell has broken loose.  Start over.
*/
enum errorSeverity {WARNING,SERIOUS,FATAL};

/**
   Generic phase exception
   $Id: PhaseExceptions.h,v 1.6 2006/10/17 03:43:00 kress Exp $
   @author Victor Kress
   @version $Revision: 1.6 $
*/
class PhaseError {
 public:
  /// type of error.
  errorType type;
  /// severity of error.
  errorSeverity severity;
  /// string to hold caller name. Space allocated in constructor
  char *caller;
  /// string to hold error description. Space allocated in constructor.
  char *description;
  /// Constructor
  /// @param _type error type.
  /// @param _severity error severity.
  /// @param _caller name of class::method throwing error
  /// @param _description description of error being thrown
  PhaseError(errorType _type, errorSeverity _severity,
	     char *_caller,char *_description);
  /// destructor
  virtual ~PhaseError();
  /// prints our error
  virtual void printErr();
};

#endif
