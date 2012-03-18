/* 
 * NiLiq class header file
 * Data from JANAF (Chase et al. 1985)
 * Victor Kress
 * $Id: NiLiq.h,v 1.5 2007/12/04 05:15:16 kress Exp $
 */
#ifndef NILIQ_H
#define NILIQ_H

#include "ShomateVinetPhase.h"

/**
   Ni liquid class
   Data from JANAF (Chase et al. 1985)
   Converted to ShomateVinetPhase 11/7/07
   @author Victor Kress
   @version $Revision: 1.5 $
*/
class NiLiq: public ShomateVinetPhase {
 public:
  /// blank constructor
  NiLiq();
  /// destructor
  virtual ~NiLiq();
 private:
  /// melting point and reference temperature
  const double tmp;
  /// get volume in M^3 at 1 bar
  virtual double getVolume(double ttk);
  /// get dVdT in M^3/K at 1 bar
  virtual double getdVdT(double ttk);
  /// get d2VdT2 in M^3/K^2 at 1 bar
  virtual double getd2VdT2(double ttk);
};

#endif



