/* ShomatePhase header file
 * generic data class for calculating thermodynamic data from Shomate equations
 * Victor Kress
 */
#ifndef SHOMATEPHASE_H
#define SHOMATEPHASE_H

#include "Phase.h"

/**
   structure to hold data for ShomatePhase class.  Form often used by NIST
   $Id: ShomatePhase.h,v 1.7 2005/03/31 00:56:30 kress Exp $
   @author Victor Kress
   $Revision: 1.7 $
   @see ShomatePhase
*/
struct ShomateData{
  /// name of referenced phase
  char *name;
  /// formula of referenced phase
  char *formula;
  /// molecular weight of referenced phase
  double mw;
  /// Shomate A
  double A;
  /// Shomate B
  double B;
  /// Shomate C
  double C;
  /// Shomate D
  double D;
  /// Shomate E
  double E;
  /// Shomate F
  double F;
  /// Shomate G
  double G;
  /// Enthalpy of formation at STP (kJ)
  double Hf;
};

/**
   Generic Phase using Shomate formulation.  Form often used by NIST.
   only defined at one bar
   @author Victor Kress
   @version 1.0
   @see ShomateData
*/
class ShomatePhase: public Phase {
 public:
  /// generic constructor
  ShomatePhase();
  /// constructor using ShomateData structure.
  ShomatePhase(ShomateData *sd);
  /// destructor
  virtual ~ShomatePhase();

  /// set temperature in Kelvins
  virtual void setTk(double ltk);  // Overrides Phase
  /// set new thermo data
  void setData(ShomateData *sd);    // set data

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
 protected:
  /// reduced temperature (=tk/1000)
  double t;                        // tk/1000
  /// class data set
  ShomateData *dat;
  /// initialization function
  virtual void init(void);
};

#endif



