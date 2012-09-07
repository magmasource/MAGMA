/* 
 * S liquid class header file
 * Data from JANAF (Chase et al. 1985)
 * $Id: SLiq.h,v 1.6 2007/12/04 05:15:16 kress Exp $
 * Victor Kress
 */
#ifndef SLIQ_H
#define SLIQ_H

#include "ShomateVinetPhase.h"

/**
   S liquid class
   Data from JANAF (Chase et al. 1985)
   Converted to ShomateVinetPhase 11/7/07
   @author Victor Kress
   @version $Revision: 1.6 $
*/
class SLiq: public ShomateVinetPhase {
 public:
  /// Constructor
  SLiq();
  /// set temperature in Kelvins
  virtual void setTk(double ltk);  // Overrides ShomatePhase
 private:
  /// get volume in M^3 at 1 bar
  virtual double getVolume(double ttk);
  /// get dVdT in M^3/K at 1 bar
  virtual double getdVdT(double ttk);
  /// get d2VdT2 in M^3/K^2 at 1 bar
  virtual double getd2VdT2(double ttk);
};

#endif
