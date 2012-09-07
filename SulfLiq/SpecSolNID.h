/* SpecSolNID header file
 * Generic class to deal with species involving homogenious speciation
 * must include speciation routine such as speciateNID.cc
 *  $Id: SpecSolNID.h,v 1.17 2006/08/29 21:47:35 kress Exp $
 */

#ifndef SPECSOLNID_H
#define SPECSOLNID_H

#include "SpecSolution.h"
#include "PhaseExceptions.h"

/**
   Associated solution class for non-ideal solutions.
   Member functions added to accomodate non-ideal solutions.
   Version 1.0 original working version.
   Version 1.1 speciate function significantly revamped to improve stability
   and convergence. 4/26/2000.
   Version 1.3 minor change to small species routine to only consider small
   components.  1/23/2001.
   $Id: SpecSolNID.h,v 1.17 2006/08/29 21:47:35 kress Exp $
   @author Victor Kress
   $Revision: 1.17 $
 */
class SpecSolNID: public SpecSolution {
 public:
  /// generic constructor
  SpecSolNID();
  /// destructor
  virtual ~SpecSolNID();

  // getting methods //////////////////////////////////////////
  /// Gibbs free energy in Joules
  virtual double getGibbs();	
  /// calculates chemical potential for species using non-ideal mixing
  virtual double getSpecMu(int ispec);
  /// enthalpy in Joules
  virtual double getEnthalpy();	
  /// entropy in Joules/Kelvin
  double getEntropy();  

 protected:
  /// nspec x nspec matrix of Margules parameters 
  double **Wh,**Ws;                                  // nspec x nspec **

  // protected utility methods ///////////////////////////////
  /// space allocation and variable initialization
  virtual void init();
  /// guts of speciation routine
  virtual int speciate_function(double tol) throw(PhaseError *) ;
  /// function that returns mu from provisional species mole frac estimate
  /// @param p species number
  /// @param x species mole fractions
  virtual double mufunc(int p,double *x);    //implements speciateNID form
  /// function that returns dmu[m]/dx[p] for current species
  /// @param m species number
  /// @param p species number
  /// @param x species mole fractions
  virtual double dmufunc(int m,int p,double *x);//implements speciateNID form
  /// excess part of chemical potential from provisional species estimate
  /// @param ispec species number
  /// @param x species mole fractions
  virtual double muxs(int ispec,double *x);
  /// excess part of dm/dxi from provisional species estimate
  /// @param m species number
  /// @param p species number
  /// @param x species mole fractions
  virtual double dmuxs(int m,int p,double *x);
  /// returns current d2G/ds2 at constant xi, where s is species vector.
  /// Reduced coordinates.
  virtual void getd2Gds2(double **d2gds2);
  /// derivative of dmu/ds (d2G/ds2) with respect to T
  virtual void getd3Gds2dT(double **d3gds2dt);
  /// returns current d3G/ds3 at constant xi, where s is species vector.
  /// Reduced coordinates.
  /// NOT YET IMPLEMENTED
  virtual void getd3Gds3(double ***d3gds3);
  /// returns dS/ds at constant xi, where s is species vector.
  /// Reduced coordinates.
  /// NOT YET IMPLEMENTED
 private:
  /// speciation variables and arrays
  double *grad,*delxi,**H,*delta,*test,*b,*d,*smalldelta;
};

#endif























