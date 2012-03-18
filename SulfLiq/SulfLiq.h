/* SulfLiq header file
 * $Id: SulfLiq.h,v 1.24 2007/11/21 01:48:30 kress Exp $
 * by Victor Kress
 */

#ifndef SULFLIQ_H
#define SULFLIQ_H


#include "Phase.h"
#include "SpecSolNID.h"
#include "VinetEOS.h"

/**
   Structure to hold 1300K standard state data for SLSSPhase
   @author Victor Kress
   @version $Revision: 1.24 $
   @see SLSSPhase
   @see SulfLiq
*/
struct SLSSData {
  /// component name
  char *name;
  /// component formula
  char *formula;
  /// component molecular weight
  double mw;
  /// Gf at 1300K
  double g0;
  /// S at 1300K
  double s;
  /// Cp at 1300K
  double cp;
  /// apparent G at 1300K
  double ge1300;
  /// molar volume at 1300K
  double v1300;
  /// molar dvdt at 1300K
  double dvdt;
  /// dvdp at 1300K
  double dvdp;
  /// d2vdpdt at 1300K
  double d2vdpdt;
};

/**
   Phase to translate 1300K standard state data to STP apparent
   properties. 
   @author Victor Kress
   @version $Revision: 1.24 $
   @see SulfLiq
*/
class SLSSPhase: public Phase {
 public:
  /// normal constructor
  SLSSPhase(SLSSData *ldat);
  /// returns Gibbs free energy from elements at STP
  virtual double getGibbs();  
  /// returns enthalpy
  virtual double getEnthalpy();
  /// returns entropy
  virtual double getEntropy();
  /// returns Cp
  virtual double getCp();
  /// temperature derivative of Cp
  virtual double getdCpdT();
  /// returns volume in m^3
  virtual double getVolume();
  /// returns dv/dt in m^3/K
  virtual double getdVdT();
  /// returns d2v/dt2 in m^3/K
  virtual double getd2VdT2();
  /// returns dv/dp
  virtual double getdVdP();
  /// returns d2V/dPdT
  virtual double getd2VdTdP();
  /// returns d2V/dP2
  virtual double getd2VdP2();
  /// pointer to parameters for this phase
  SLSSData *dat;
  /// peculiar standard state temperature.
  const double STR;
 protected:
  /// VinetEOS instance
  VinetEOS Vinet;
  /// update state
  virtual void update();
};

/**
   Sulfide liquid class.  Using model and data from Kress (1997),
   Kress (2000) and Kress (2001)
   @author Victor Kress
   @version $Revision: 1.24 $
   @see SLSSPhase
   @see SLSSData
 */
class SulfLiq: public SpecSolNID {
 public:
  // public variables ////////////////////////////////
  /// number of components
  const int NCOMP;
  /// number of species
  const int NSPEC;
  /// O index
  const int ODEX;
  /// S index
  const int SDEX;
  /// Fe index
  const int FDEX;
  /// Ni index
  const int NDEX;
  /// Cu index
  const int CDEX;
  /// FeO index
  const int WUDEX;
  /// FeO1.5 index
  const int HMDEX;
  /// NiO index
  const int BUDEX;
  /// FeS index
  const int TTDEX;
  /// NiS index
  const int MIDEX;
  /// Cu2S index
  const int DJDEX;
  /// FeOS index
  const int OPDEX;
  /// Ni(.25)S(.25)O index
  const int NSDEX;
  /// CuS index
  const int CVDEX;
  /// CuO index
  const int TEDEX;
  /// reference temperature (must be same as SLSSPhase)
  const double STR;
  // creation/distruction ////////////////////////////////
  /// constructor
  SulfLiq();
  /// destructor
  virtual ~SulfLiq();
  
  // setting methods ////////////////////////////////////
  /// set temperature in Kelvins
  virtual void setTk(double ltk);
  /// set pressure in Pascals
  virtual void setPa(double lpq);
  /**
     Adjusts O and S corresponding to input log10(fo2) and log10(fS2).
     @param logfo2 = log10(fo2)
     @param logfs2 = log10(fs2)
     @param verbose = if true, print progress
     @return number of iterations or -1 if unsuccessful
  */
  virtual int setFugacity(double logfo2,double logfs2,int verbose);
  /// defaults to quiet
  virtual int setFugacity(double logfo2,double logfs2);
  /// sets log10 oxygen fugacity by adjusting oxygen content
  virtual int setlogfo2(double logfo2);
  /// sets log10 sulfur fugacity by adjusting sulfur content
  virtual int setlogfs2(double logfs2);
  
  // getting methods ///////////////////////////////////
  /// returns phase volume in M^3
  double getVolume();
  /// returns dVdT in M^3/K
  double getdVdT();
  /// returns log10(fO2)
  double getlogfo2();
  /// returns log10(fS2)
  double getlogfs2();
  
 protected:
  /// allocates space and initializes variables
  virtual void init();
  /// pointer to O2 gas phase
  Phase *po2;
  /// pointer to S2 gas phase
  Phase *ps2;
  /// matrix of species stoichiometries
  static double allstoich[15][5];
};
  
#endif















