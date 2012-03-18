/* 
 * CuLiq class header file
 * Data from JANAF (Chase et al. 1985)
 * Converted to ShomateVinetPhase 11/7/07
 * Victor Kress
 * $Id: CuLiq.h,v 1.5 2007/12/04 05:15:16 kress Exp $
 */
#ifndef CULIQ_H
#define CULIQ_H

#include "ShomateVinetPhase.h"

/**
   Cu liquid class
   Data from JANAF (Chase et al. 1985)
   Converted to ShomateVinetPhase 11/7/07
   @author Victor Kress
   @version $Revision: 1.5 $
*/
class CuLiq: public ShomateVinetPhase {
 public:
  /// constructor
  CuLiq();
  /// destructor
  virtual ~CuLiq();
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



