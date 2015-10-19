/* ShomateVinetPhase header file
 * implements Phase using ShomatePhase for T and VinetEOS for pressure integrals.
 * $Id: ShomateVinetPhase.h,v 1.5 2007/11/16 18:30:12 kress Exp $
 * Victor Kress, San Francisco, 10/26/07
 */

#ifndef SHOMATEVINETPHASE_H
#define SHOMATEVINETPHASE_H

#include "ShomatePhase.h"
#include "VinetEOS.h"

/**
   Shomate-Vinet class
   Uses Shomate equations for 1-bar properties and Vinet Equation for high pressure.
   @author Victor Kress
   @version $Revision: 1.5 $
*/
class ShomateVinetPhase: public ShomatePhase {
 public:
  /// constructor
  ShomateVinetPhase(void);
  /// destructor
  virtual ~ShomateVinetPhase(void);

  /// apparent Gibbs free energy
  virtual double getGibbs();
  /// apparent enthalpy
  virtual double getEnthalpy();
  /// third law entropy
  virtual double getEntropy();
  /// heat capacity
  virtual double getCp();
  /// derivative of Cp with respect to T
  virtual double getdCpdT();
  // Volume and derivatives
  /// volume in cubic meters = Joules/Pascal
  virtual double getVolume();
  /// dV/dT in M^3/Kelvin
  virtual double getdVdT();
  /// dV/dP in M^3/Pascal
  virtual double getdVdP();
  /// d2V/dT2 in M^3/Kelvin^2
  virtual double getd2VdT2();
  /// d2V/dTdP in M^3/KelvinPascal
  virtual double getd2VdTdP();
  /// d2V/dP2 in M^3/Pascal^2
  virtual double getd2VdP2();

 protected:
  /// Vinet equation of state implementation object
  VinetEOS Vinet;
  /// molar volume properties at Tr and Pr in SI units

  /// initialization function
  virtual void init(void);
  /// update function
  virtual void update(void);
};
#endif
