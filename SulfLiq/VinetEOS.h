/* PhaseVinetEOS header file
 * Implementation of Vinet pressure EOS for Phase class group.
 * Designed in such a way that it can be easily replaced with other
 * equations of state.
 * Based on code from gibbs.c in Ghiorso's lates xMelts implementation 10/24/07
 * Victor Kress
 */
#ifndef VINETEOS_H
#define VINETEOS_H

#include "PhaseExceptions.h"

/**
   VinetEOS: Class implements Vinet (Universal) pressure equation of state.
   SI units throughout with all properties set by implementer. 
   All properties are molar or partial molar.
   Helper class to provide pressure integrals for one bar phases.
   Based on code from gibbs.c in Ghiorso's latest xMelts 10/24/07
   $Id: VinetEOS.h,v 1.4 2007/11/16 18:30:12 kress Exp $
   @author Victor Kress
   @version $Revision: 1.4 $
*/
class VinetEOS {
 public:
  /// blank constructor.  STP assumed.
  VinetEOS(void);
  /// generic destructor
  virtual ~VinetEOS(void);
  /// temperature in K
  double tk;
  /// pressure in Pa
  double pa;
  /// reference temperature
  double tr;
  /// reference pressure
  double pr;
  /// molar volume at Tr and Pr
  double V0;
  /// 1/V(dV/dT) evaluated at reference pressure
  double alphaT;
  /// bulk modulus in pascals
  double K;
  /// pressure derivative if bulk modulus
  double Kprime;
  /// updates values for (V/V0)^(1/3) and derivatives
  virtual void update(void) throw(PhaseError *);
  /// returns molar volume.
  double getMolarVolume(void);
  /// returns molar pressure integral of Gibbs free energy
  double getMolarGibbsPTerm(void);
  /// returns molar pressure integral of enthalpy
  double getMolarEnthalpyPTerm(void);
  /// returns molar pressure integral of entropy
  double getMolarEntropyPTerm(void);
  /// returns molar pressure integral of Cp
  double getMolarCpPTerm(void);
  /// returns molar pressure integral of dCp/dT term
  double getMolardCpdTPTerm(void);
  /// returns molar dV/dT
  double getMolardVdT(void);
  /// returns molar dV/dP
  double getMolardVdP(void);
  /// returns d2V/dT2
  double getMolard2VdT2(void);
  /// returns molar d2V/dTdP
  double getMolard2VdTdP(void);
  /// returns molar d2V/dP2
  double getMolard2VdP2(void);

 private:
  /// (V/V0)^(1/3) at P
  double x;
  /// (V/V0)^(1/3) at P0
  double x0;
  /// derivatives of x
  double dxdt,d2xdt2,dxdp,d2xdtdp,d2xdp2,dx0dt,d2x0dt2;
};

#endif
