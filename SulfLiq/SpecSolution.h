/* SpecSolution header file
 * Generic class to deal with species involving homogenious speciation
 * 7/17/06 added capability to handle charge balance constraints.
 * $Id: SpecSolution.h,v 1.35 2007/11/30 09:25:52 kress Exp $
 */

#ifndef SPECSOLUTION_H
#define SPECSOLUTION_H

#include <float.h>
#include <stdio.h>
#include "Solution.h"

/**
 Generic class to deal with associated solutions.  
 In generic case ideal mixing assumed.
 First ncomp species MUST correspond to components. nmoles is total
 of component moles.  This will NOT correspond to sum of species moles.
 version 1.1 added RAND algorithm.  Moved some stuff here from SpecSolNID.
`version 1.33 added capability to handle charge balance constraints.
 @author Victor Kress
 @version $Revision: 1.35 $
 */
class SpecSolution: public Solution {
 public:
  /// generic constructor.
  SpecSolution();
  /// generic destructor.
  virtual ~SpecSolution();

  // persistent phase properties ///////////
  /// returns number of species
  int getNspec(void);    
  /// returns pointer to species name
  virtual const char *getSpecName(int i);
  /// returns pointer to species formula
  virtual const char *getSpecFormula(int i);

  // setting methods //////////////////////
  /// set phase temperature in Kelvins
  virtual void setTk(double ltk);
  /// set phase pressure in Pascals
  virtual void setPa(double lpa);
  /** set total moles. This is sum of component moles. Sum of species
      moles will be different, and dependent on speciation.
  */
  virtual void setMoles(double m) throw(PhaseError *);
  /** Set component vector in moles. 
      Species filled but not equilibrated. */ 
  virtual void setComps(double *lcomps);
  /** Set species vector in moles.
      Components set automatically. Not automatically equilibrated.
      Only non-zero species will be included in calculations. */
  virtual void setSpecs(double *lspecs);
  /// like setSpecs except all potential species are activated
  virtual void setSpecsFull(double *lspecs);

  // getting methods ///////////////////////
  /// Get phase species abundances in moles
  virtual void getSpecs(double *lspecs);

  // Gibbs and derivatives
  /// Gibbs free energy at T,P,X
  double getGibbs();		    // Overrides Solution
  /// standard-state chemical potential at T and P. 
  virtual double getMu0(int ispec);
  /// chemical potential of component in J/mole. Calls getCompMu() 
  virtual double getMu(int i);
  /// chemical potential of component
  virtual double getCompMu(int i);
  /// chemical potential of species
  virtual double getSpecMu(int i);
  /// dMu[i]/dX[j] for components.
  virtual double getdMudX(int i,int j);
  /// get second derivative of G with respect to component vector.
  virtual void getd2Gdm2(double **d2gdm2);
  /// third derivative of G with respect to composition. Not yet implemented.
  virtual void getd3Gdm3(double ***d3Gdm3);
  /// mixing component of Gibbs free energy in Joules
  double getGmix();                 // Overrides Solution

  // enthalpy and derivatives
  /// enthalpy at T,P,X
  virtual double getEnthalpy();		    // Overrides Solution
  /// enthalpy of mixing in Joules
  virtual double getHmix();                 // Overrides Solution

  // entropy and derivatives
  /// entropy at T,P,X
  virtual double getEntropy();              // Overrides Solution
  /// derivative of entropy with respect to mole vector
  virtual void  getdSdm(double *dsdm);
  /// second derivative of entropy with respect to mole vector
  virtual void  getd2Sdm2(double **d2sdm2);
  /// entropy of mixing in Joules/Kelvin
  virtual double getSmix();                 // Overrides Solution

  // heat capacity and derivatives
  /// heat capacity.
  virtual double getCp();
  /// dCp/dT
  virtual double getdCpdT();
  /// heat capacity of mixing.
  virtual double getCpmix();
  /// dCp/dT of mixing
  virtual double getdCpdTmix();

  // volume and derivatives
  /// volume in cubic meters
  virtual double getVolume();               // Overrides Solution
  /// volume of mixing in cubic meters (Joules/Pascal)
  virtual double getVmix();
  /// dVdt in M^3/K
  virtual double getdVdT();
  /// dVdt of mixing in M^3/K
  virtual double getdVdTmix();

  // utility functions ////////////////////////
  /// suppress formation of species i. Cannot supress component.
  virtual void supressSpecies(int i);
  /// Set fractional convergence tolerance for homogeneous equilibrium calculation
  virtual void setSpeciateTolerance(double tol);
  /// Calculates homogenious equilibrium. Replaces dummy routine in Phase.
  virtual void update();
  /// returns error in last homogenious speciation calculation (Joules)
  virtual double getSpecCalcErr();
  /// returns boolean indicating if hom. eq. calculated for curr. conditions
  virtual int isUpdated();
  /// flag for verbose progress output during equilibration. 0 by default.
  int verbose; 
  /// prints most properties of phase
  virtual void printAll();

 protected:
  /// nspec array of boolean to indicate species should be suppressed
  int *supressSpec;
  /// Supress species because of T bound violation
  /// @see suppressSpec
  static const int TSUPRESS = 1; 
  /// Supress species because of P bound violation
  /// @see suppressSpec
  static const int PSUPRESS = 2;
  /// Supress species for any reason
  /// @see suppressSpec
  static const int SUPRESS = 4;
  /// indexing array used to eliminate unused reactions. r is recalculated
  /// from lcomp and lspec as needed.
  int *rdx;
  /// species chemical potentials
  double *mu;
  /// species hessian (indexed in reduced coordinates)
  double **dmuds;
  /// transform kernel for calculating most property derivatives.
  /// Indexed to non-zero species.
  double **K;
  /// generic working space
  double **m1,**m2,**m3,*v1,*v2,***mmm;
  /// Vector of species moles.
  double *specs;
  /// sum of species moles
  double specSum;
  /// Species stoichiometries [nspec][ncomp].First ncomp rows MUST be identity.
  double **spstoich;    
  /// reaction stoich. matrix. Indexed on non-zero species and reactions
  double **nu;
  /// rank of nu matrix
  int nuRank;
  /// vector of species charges (NULL if no charge balance constraints)
  double *specCharge;

  /// Calculates homogenious equilibrium. Invoked by update()
  /// @return number of iterations to convergence
  virtual int speciate();
  /**
     Guts of speciation routine. Ideal solution assumed.
     Implements RAND speciation algorithm as presented in:
     Smith and Missen (1982) Chemical Reaction Equilibrium Analysis:
     Theory and Algorithms. Krieger.
     Gf is vector of standard state chemical potentials at T
  */
  virtual int speciate_function(double tol);
  /// space allocation and variable initialization
  virtual void init();
  /// transfers comps to specs
  virtual int fillSpecs();
  /// transfers specs to comps
  virtual void fillComps();
  /// index non-zero species
  virtual void index();
  /// returns current d2G/ds2 at constant xi, where s is species vector.
  /// Reduced coordinates.
  virtual void getd2Gds2(double **d2gds2);
  /// derivative of dmu/ds (d2G/ds2) with respect to T
  virtual void getd3Gds2dT(double **d3gds2dt);
  /// returns current d3G/ds3 at constant xi, where s is species vector.
  /// Reduced coordinates.
  virtual void getd3Gds3(double ***d3gds3);
  /// returns dS/ds at constant xi, where s is species vector.
  /// Reduced coordinates.
  virtual void getdSds(double *dsds);
  /// returns dV/ds at constant xi, where s is species vector.
  /// Reduced coordinates.
  virtual void getdVds(double *dsds);
  /// update transform kernel for most property transforms.
  /// Reduced coordinates.
  /// @see K
  virtual void updateTransformKernel();
  /// function that returns dmu[m]/dx[p] for species.
  /// Maintained as separate function (not incorporated in d2Gds2())
  /// because flexibility required for speciation calculations.
  /// DEPRECATED! Do not use in new applications.
  /// @param m species number
  /// @param p species number
  /// @param s species moles
  virtual double dmufunc(int m,int p,double *s);

 private:
  /// tolerance for speciation
  double spectol;
  /// speciation variables and arrays
  double *rhs,*psi,*b,*bm,*delta;
};

#endif






