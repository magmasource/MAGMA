/* Solution class header file
 * Generic class to deal with phases which are solutions
 * Victor Kress
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include "Phase.h"

/**
   solution class.
   Generic class for Phases which are simple solutions.
   In generic implementation, ideal mixing is assumed.
   Converted to extensive properties 4/14/03
   $Id: Solution.h,v 1.34 2008/05/30 01:15:14 kress Exp $
   @author Victor Kress
   @version $Revision: 1.34 $
 */
class Solution: public Phase {
 public:
  /// Generic constructor. Assumes STP.
  Solution();
  /// destructor
  virtual ~Solution();

  // persistent phase properties //////
  /// Returns number of components in system
  int getNcomp(void);
  /// Returns molecular weight of component i
  virtual double getMW(int i);
  /// Returns gram formula weight of solution
  virtual double getMW();   // overrides Phase
  /// gets component number for input string.  Match must be exact.
  /// @param lab char* to name of phase
  /// @return integer index or -1 if not found.
  virtual int getCompNo(char *lab);
  /// Returns pointer to component name. 
  /// Caution: string destroyed with Solution object.
  virtual const char *getCompName(int i);
  /// Returns pointer to component formula. 
  /// Caution: string destroyed with Solution object.
  virtual const char *getCompFormula(int i);

  // setting methods ///////////////////
  /// set temperature in Kelvins
  virtual void setTk(double ltk); //overrides Phase
  /// set pressure in Pascals
  virtual void setPa(double lpa); //overrides Phase
  /// set moles. In Solution and subclasses, 
  /// nmoles is total of component moles.
  virtual void setMoles(double m)  throw(PhaseError *);
  /// set total mass of solution in grams.
  virtual void setMass(double w);
  /// Set component moles.  Coppies values to internal array.
  virtual void setComps(double *rawcomps);
  /// sets component weights in kg
  /// @param wt ncomp array of grams of each component.
  virtual void setCompWeights(double *wt);
  /// sets components from vector in weight percent (nmoles set to 1.0)
  /// Maintained for backward compatibility
  virtual void setCompWtPct(double *wt);
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

  // getting methods //////////////////
  /// returns sum of moles of components
  double getMoles();
  /// returns total mass of phase in grams
  double getMass();
  /// Returns component moles in caller-allocated vector.
  virtual void getComps(double *rawcomps);
  /// Returns component grams in caller-allocated vector
  virtual void getCompWeights(double *wt);
  /// Returns components in weight percent.  Does not allocate space.
  virtual void getCompWtPct(double *wt);
  /// Returns moles of elements in caller-allocated space
  virtual void getElements(double *ele);
  /// Same as getElements but adds nmoles of phase elements to input array.
  /// Don't know why you would want this. Implemented for consistent behavior
  /// with single-component phases.
  virtual void getAddElements(double *ele,double mol);

  /// Returns Gibbs free energy relative to elements at STP in J
  virtual double getGibbs();     // overrides Phase
  /// returns single standard state chemical potential in J/mole
  virtual double getMu0(int icomp);
  /// standard state chemical potential in Joules.
  /// @return potential of all components in joules.
  virtual void getMu0(double *m0);
  /// Returns chemical potential in J/mole.
  virtual double getMu(int i);
  /// chemical potential in Joules.
  /// @return potential of all components in joules.
  virtual void getMu(double *m);
  /// Returns single activity
  virtual double getActivity(int icomp);
  /// component activities
  /// @param a user provide ncomp vector to hold results.
  virtual void getActivity(double *a);
  /// Returns dMu[i]/dX[j]).
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
  /// calculates Gubbs Hessian and returns in user-allocated space.
  /// @param h ncomp by ncomp array to hold Gibbs Hessian.
  virtual void getHessian(double **h);
  /// calculates and returns pointer to Gibbs Hessian.  This version is
  /// deprecated because it doesn't follow memory allocation standard.
  /// it will eventually become protected;
  virtual double** getHessian();
  /// Mixing contribution to Gibbs free energy.  Hmix - T*Smix
  virtual double getGmix();

  // Enthalpy and derivatives //////////////
  /// Returns enthalpy in Joules. Ideal solution assumed.
  virtual double getEnthalpy();

  // Entropy and derivatives ///////////////
  /// Returns entropy in Joules/Kelvin. Ideal solution assumed.
  virtual double getEntropy();
  /// derivative of entropy with respect to moles (Joules/(mole.Kelvin).
  /// Ideal mixing assumed.
  /// @param dsdm ncomp vector to store result
  virtual void getdSdm(double *dsdm);
  /// second derivative of entropy with respect to moles
  /// (Joules/(mole^2.Kelvin).  Ideal mixing assumed.
  /// @param d2sdm2 ncomp by ncomp array to store result
  virtual void getd2Sdm2(double **d2sdm2);
  /// Entropy of mixing.  Ideal in generic case.
  virtual double getSmix();

  // Cp and derivatives ///////////////////
  /// Constant-pressure heat capacity in Joules/Kelvin
  virtual double getCp();
  /// derivative of Cp with respect to temperature
  virtual double getdCpdT();
  /// derivative of Cp with respect to composition.
  virtual void getdCpdm(double *dcpdm);

  // Volume and derivatives ///////////////
  /// Volume in cubic meters = Joules/Pascal
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

  // utility functions ///////////
  /// Checks for phase stability by Hessian test.
  /// @return 1 for stable, 0 if not.
  virtual int isStable();
  /// Finite difference tester routine for hessian
  virtual void testHessian(double step);
  /// brings all internal variables to self-consistent equilibrium state
  virtual void update();
  /// prints almost everything about solution
  virtual void printAll();

 protected:
  /// number of species. In Solutions set equal to ncomp in init().
  int nspec;
  /// number of non-zero components. Set in index().
  int lcomp;
  /// number of non-zero species. In Solutions ALWAYS equal to lcomp.
  int lspec;
  /// indexing array used to eliminate zero species
  int *indx;
  /// vector of components
  double *comps; 
  /// vector of standard state properties
  Phase **ss;
  /// Gibbs Hessian
  double **hessian;
  /// working space for SVD calculations
  double **A,**v,*w;
  /// index non-zero species
  virtual void index();
  /// Space allocation and variable initialization
  /// Solution::init() called after number of ncomp etc defined.
  /// Must not call parent Phase::init().
  virtual void init();
  /// Initializes stoichiometric arrays from information in 
  /// ss  array.  Must be called after members of ss array initialized.
  virtual int initElOxArrays();
};

#endif





