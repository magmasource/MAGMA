/*
 * header file for general chemistry data and functions
 * Victor Kress
 * Seattle, 7/4/04
 * $Id: Chem.h,v 1.7 2007/07/23 19:55:50 ghiorso Exp $
 */
#ifndef CHEM_H
#define CHEM_H

#include "PhaseExceptions.h"

/// structure to hold molecular stoichiometry
struct Stoich {
  /// number of elements
  int nele;
  /// vector of element indices
  int *ele;
  /// vector of stoichiometries
  double *stoich;
};
/// structure to hold element properties
struct EleProp {
  /// atomic symbol
  char *symbol;
  /// atomic weight
  double aw;
  /// name
  char *name;
};
/// structure to hold oxide properties
struct OxProp {
  /// formula string
  char *formula;
  /// cation atomic number
  int cation;
  /// number of cations
  double ncat;
  /// number of oxygens
  double nO;
  /// molecular weight
  double mw;
};

/**
   static class for data and methods associated with chemistry calculations.
   @author Victor Kress
   @version $Revision: 1.7 $
*/
class Chem {
 public:
  // constructor/destructor///////////////////////////
  /// constructor
  Chem(void);
  /// destructor;
  virtual ~Chem();

  // data ////////////////////////////////////////////
  /// number of elements considered in this class plus one (space allocation)
  static const int nele = 106;
  /// nele array of element properties
  static const EleProp ele[];
  /// number of oxides considered in this class
  static const int nox = 19;
  /// nox array of oxide properties
  static const OxProp ox[];

  // methods ///////////////////////////////////////////
  /// parse formula and return results in elememt array
  static void parseFormula(char *formula,double *elarray);
  /// given element array, calculate molecular weight
  static double mwt(double *elarray);
  /// given stoichiometry, calculate molecular weight
  static double mwt(Stoich *);
  /// given element array, return oxide abundances
  /// @param elarray elemant abundanced on entry.  Contains remainder on exit
  /// @param oxarray array of moles of oxides.
  static void elToOx(double *elarray,double *oxarray);
  /// given oxide array, return corresponding element array
  /// @param oxarray nox array of oxide moles
  /// @param elarray nele array of element moles
  static void oxToEl(double *oxarray,double *elarray) throw(PhaseError *);
  /// converts oxide array in moles to grams
  static void oxMolToWt(double *oxarray);
  /// converts oxide array in grams to moles
  static void oxWtToMol(double *oxarray);
 private:
  /// parses formula token.  May be called recursively by public parseFormula()
  static void parseFormulaToken(char *token,int len,double mult,
				double *elarray) throw(PhaseError *);
};
#endif
