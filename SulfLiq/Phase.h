/* Phase header file
 * Generic phase class.  Parent to all phases.
 * Revised with added setting methods and general components 7/1/04
 * Victor Kress
 */
#ifndef PHASE_H
#define PHASE_H

#include "Chem.h"
#include "PhaseExceptions.h"

/**
   Generic Phase class. Parent class to all Phases.
   SI units throughout with Tr=273.15 and Pr=1.e5 Pa.  As a general rule,
   space is to be allocated and values initialized in init() routine
   and destroyed in destructor.
   Parent init() should be called by each child.  Parent
   destructor is called automatically if all destructors are virtual.
   Whole hierarchy converted to extensive quantities 4/14/03.
   Solution methods added 7/31/03
   $Id: Phase.h,v 1.36 2007/11/13 06:37:16 kress Exp $
   @author Victor Kress
   @version $Revision: 1.36 $
*/
class Phase {
 public:
  /// blank constructor.  STP assumed.
  Phase(void);
  /// generic destructor
  virtual ~Phase();

  // persistent phase properties //////
  /// name of phase.
  char *name; 
  /// formula of phase.
  char *formula;
  /// Returns number of components (1 for base class)
  virtual int getNcomp(void);
  /// Return molecular weight for phase (grams/mol)
  virtual double getMW(void);
  /// gets component number for input string.  Match must be exact.
  /// @param lab char* to name of phase to match
  /// @return integer index or -1 if not found.
  virtual int getCompNo(char *lab);
  /// get component name corresponding to string.
  /// Caution: string destroyed with Phase object.
  /// @param i integer component number.
  /// @return pointer to component name string or NULL if not found. 
  virtual const char *getCompName(int i);
  /// get component formula.
  /// Caution: string destroyed with Phase object.
  /// @param i integer component number.
  /// @return pointer to component formula or NULL if not found. 
  virtual const char *getCompFormula(int i);
  /// get number of generic (1-2 element) components
  virtual int getGenericNcomp(void);
  /// Get string formula for generic component.
  /// Caution: string destroyed with Phase object.
  /// @param icomp component number < gncomp
  virtual char *getGenericCompFormula(int icomp);
  /// returns logical indicating if this phase can be treated as oxide
  virtual int isOxide();

  // setting methods ////////////////////
  /// set temperature in Kelvins.
  virtual void setTk(double ltk);
  /// set pressure in Pascals.
  virtual void setPa(double lpa);
  /// set total number of moles.
  virtual void setMoles(double lm) throw(PhaseError *);
  /// set total mass in grams.
  virtual void setMass(double w);
  /// Set component moles.  For single-component phase, just sets moles.
  /// @param rawcomps ncomp array of moles of each component.
  virtual void setComps(double *rawcomps);
  /// sets component weights in grams.
  /// @param wt ncomp array of grams of each component.
  virtual void setCompWeights(double *wt);
  /// sets components from vector in weight percent (nmoles set to 1.0)
  /// Maintained for backward compatibility (deprecated)
  virtual void setCompWtPct(double *wt);
  /// sets generic component (1-2 element) weights in grams
  /// @param wt gncomp array of grams of each generic component
  virtual void setGenericCompWts(double *wt) throw(PhaseError *);
  /// Set moles of elements.
  /// @param ele Moles of elements on entry, remainder after max phase comp removed on exit.
  virtual void setElements(double *ele) throw(PhaseError *);
  /// used to reset default bounds for temperature and pressure.
  /// @param lowTbound new lower temperature bound
  /// @param hiTbound new upper temperature bound
  /// @param lowPbound new lower pressure bound
  /// @param hiPbound new upper pressure bound
  virtual void resetTPbounds(double lowTbound,double hiTbound,
			     double lowPbound,double hiPbound);

  // getting methods /////
  /// return temperature in Kelvins
  virtual double getTk();
  /// return pressure in Pascals
  virtual double getPa();
  /// return total number of moles
  virtual double getMoles();
  /// return total mass in grams
  virtual double getMass();
  /// return density in grams per cubic centimeter
  virtual double getDensity();
  /// Returns component moles in caller-allocated vector.
  virtual void getComps(double *rawcomps);
  /// Returns component grams in caller-allocated vector
  virtual void getCompWeights(double *wt);
  /// Returns components in weight percent (deprecated).Does not allocate space.
  virtual void getCompWtPct(double *wt);
  /// Returns grams generic components (1-2 element) in caller-allocated space.
  virtual void getGenericCompWts(double *wt);
  /// Returns moles of elements in caller-allocated space
  virtual void getElements(double *ele);
  /// Same as getElements but adds nmoles of phase elements to input array.
  /// Only known use is in Solution class
  virtual void getAddElements(double *ele,double mol);

 // Gibbs and derivatives
  /// Gibbs free energy in Joules
  virtual double getGibbs();
  /// standard state chemical potential in Joules.
  /// @param i component number
  /// @return potential in joules or zero if not found.
  virtual double getMu0(int i);
  /// standard state chemical potential in Joules.
  /// @return potential of all components in joules.
  virtual void getMu0(double *m0);
  /// standard state chemical potential in Joules. Same as getMu0 for 
  /// single-component phase.
  /// @param i component number
  /// @return potential in joules or zero if not found.
  virtual double getMu(int i);
  /// chemical potential in Joules.
  /// @return potential of all components in joules.
  virtual void getMu(double *m);
  /// component activities. 
  /// @return 1 for single-component condensed phase.
  virtual double getActivity(int icomp);
  /// component activities
  /// @param a user provide ncomp vector to hold results.
  virtual void getActivity(double *a);
  /// composition derivative of chemical potential
  /// @return dMu[i]/dX[j]) or zero if single-component phase.
  virtual double getdMudX(int i,int j);
  /// Returns partial molar volume in m^3
  virtual double getdMudP(int i);
  /// derivative of Gibbs free energy with respect to moles (Joules/mole). 
  /// param dgdm ncomp vector to hold results.
  virtual void getdGdm(double *dgdm);
  /// second derivative of Gibbs free energy with respect to moles 
  /// (Joules/mole).
  /// param d2gdm2 ncomp by ncomp array to hold results.
  virtual void getd2Gdm2(double **d2gdm2);
  /// third derivative of Gibbs free energy with respect to moles 
  /// (Joules/mole).
  /// param d3gdm3 ncomp by ncomp by ncomp array to hold results.
  virtual void getd3Gdm3(double ***d3gdm3);
  /// Mixing contribution to Gibbs free energy.  Ideal in generic case or
  /// zero for single-component.
  virtual double getGmix();
  /// calculates Gibbs Hessian and returns in user-allocated space.
  /// @param h ncomp by ncomp array to hold Gibbs Hessian.
  virtual void getHessian(double **h);

  // Enthalpy and derivatives
  /// enthalpy in Joules
  virtual double getEnthalpy();
  /// Enthalpy of mixing.  Zero in generic case or single component.
  virtual double getHmix();

  // Entropy and derivatives
  /// entropy in Joules/Kelvin
  virtual double getEntropy();
  /// derivative of entropy with respect to moles (Joules/(mole.Kelvin).
  /// @param dsdm ncomp vector to store result
  virtual void getdSdm(double *dsdm);
  /// second derivative of entropy with respect to moles 
  /// (Joules/(mole^2.Kelvin).
  /// @param d2sdm2 ncomp by ncomp array to store result
  virtual void getd2Sdm2(double **d2sdm2);
  /// Entropy of mixing.  Ideal in generic case.  Zero for single-component.
  virtual double getSmix();

  // Cp and derivatives
  /// constant-pressure heat capacity in Joules/Kelvin
  virtual double getCp();
  /// derivative of Cp with respect to temperature.
  virtual double getdCpdT();
  /// derivative of Cp with respect to composition.
  virtual void getdCpdm(double *dcpdm);

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
  /// Volume of mixing.  Zero in generic case or single-component.
  virtual double getVmix();

  // utilities //////
  /// Checks for phase stability by Hessian test.
  /// @return 1 for stable, 0 if not. Single-component phase always stable.
  virtual int isStable();
  /// print all properties of phase
  virtual void printAll();
  /// generic routine brings ordering, speciation, etc. current (if necessary).
  virtual void update();

 protected:
  /// number of components
  int ncomp;
  /// Array of element abundances.Working space. Never assume current.
  double *elarray;
  /// Soich structure for elements relevant to this phase
  Stoich eleStoich;
  /// Soich structure for oxides relevant to this phase (nele=0 if not oxide)
  Stoich oxStoich;
  /// Initialization function. Each child class must call parent init().
  /// In 1-comp phases, parent init() must be called after formula defined.
  /// Solutions must implement own init and not call parent Phase::init()
  /// and ss array filled.
  virtual void init();
  /// temperature in Kelvins
  double tk;
  /// pressure in Pascals
  double pa;
  /// total number of moles
  double nmoles;
  /// molecular weight in grams
  double mw; 
  /// J/Kmol
  const double R;
  /// reference temperature
  const double tr;
  /// reference pressure
  const double pr;
  /// low temperature limit (K)
  double lowT;
  /// high temperature limit (K)
  double highT;
  /// low pressure limit (Pa)
  double lowP;
  /// high pressure limit (Pa)
  double highP;
  /// method checks validity of argument as temperature
  virtual void checkT(double) throw(PhaseError *);
  /// method checks validity of argument as pressure
  virtual void checkP(double) throw(PhaseError *);
  /// method checks validity of argument as composition
  virtual void checkX(double *) throw(PhaseError *);
  /// boolean to indicate if state of system is self-consistent (if necessary)
  int updated;
};

#endif
