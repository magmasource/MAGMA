/* ShomateIdealGas header file
 * Victor Kress
 * Seattle 2004
 * $Id: ShomateIdealGas.h,v 1.2 2004/10/21 03:23:21 kress Exp $
 */

#ifndef SHOMATEIDEALGAS_H
#define SHOMATEIDEALGAS_H

#include "ShomatePhase.h"

/**
   Shomate Ideal Gas
   @author Victor Kress
   @version 1.0
*/
class ShomateIdealGas: public ShomatePhase {
 public:
   ShomateIdealGas();
  /// constructor using ShomateData structure.
  ShomateIdealGas(ShomateData *sd);
  /// destructor
  virtual ~ShomateIdealGas();

  /// third law entropy
  virtual double getEntropy();
  /// derivative of entropy with respect to moles (Joules/(mole.Kelvin).
  /// @param dsdm ncomp vector to store result
  virtual void getdSdm(double *dsdm);
  /// second derivative of entropy with respect to moles 
  /// (Joules/(mole^2.Kelvin).
  /// @param d2sdm2 ncomp by ncomp array to store result
  virtual void getd2Sdm2(double **d2sdm2);

  // Volume and derivatives
  /// volume in cubic meters = Joules/Pascal
  virtual double getVolume();
  /// derivative of volume with respect to composition.
  virtual void getdVdm(double *dvdm);
  /// second derivative of volume with respect to composition.
  virtual void getd2Vdm2(double **d2vdm2);
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
  /// d2VdmdT in M^3/KelvinMole
  virtual void getd2VdmdT(double *d2vdmdt);
  /// d2VdmdP in M^3/PascalMole
  virtual void getd2VdmdP(double *d2vdmdp);
};

#endif

