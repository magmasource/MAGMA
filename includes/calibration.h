#ifndef _Calibration_h
#define _Calibration_h

/*
MELTS Source Code: RCS $Log: calibration.h,v $
MELTS Source Code: RCS Revision 1.4  2007/08/26 21:38:30  ghiorso
MELTS Source Code: RCS Normalized residuals (for xMELTS calibration) to the number of atoms in the
MELTS Source Code: RCS endmember mineral formula.  Revised residual-statistics.out file accordingly.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2007/05/07 18:23:19  ghiorso
MELTS Source Code: RCS Modifications to LEPR and calibration algorithms following visit by
MELTS Source Code: RCS Marc and Tim.  Mostly work on cpx and opx inclusion and reclassification.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2006/08/17 16:47:18  ghiorso
MELTS Source Code: RCS Made modifications to protect strings.  These modifications allow removal
MELTS Source Code: RCS of the flag -fwritable-strings during gcc compilation.  This brings the
MELTS Source Code: RCS code up to gcc 4.x standards.
MELTS Source Code: RCS
MELTS Source Code: RCS Other minor rearrangements and cleanup.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:35  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2004/09/19 20:20:20  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2004/09/15 02:47:56  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:48:56  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Include file for intercommunication of global variables
**      between PRECLB and POSTCLB (file: CALIBRATION.H)
**
**--
*/

/*===================================================================================================================================================*/

#define SCALE 1000.0  /* Scale factor for dependent variable       								                     */
#define	DIETAG		1
#define WORKTAG		2
#define REPLYTAG	3
#define INTPARAMSTAG    4
#define DOUBLEPARAMSTAG 5

/*===================================================================================================================================================*/

extern int nEqn;           /* Number of equations in the regression matrix                                                                            */
extern int nLiquid;        /* Number of experimets, equals number of instances of residualDataOutput and residualOutput */
extern int useTregression; /* resdual computed on delta T */


/*===================================================================================================================================================*/

typedef struct _extraSolids {
  const char *phase;	  /* phase name. Identical to solid solution phase name in sol_struct_data.h							*/
  const char *species;    /* species name for *phase*													*/ 
  const char *formula;    /* character string formula													*/
  double     threshold;   /* threshold on mole fraction for species inclusion										*/
  double     mLimits[10]; /* vector of limits on component mole fractions. zero means no limit. 10 is assumed to be naMax				*/
  int        index;	  /* index of *phase* in solids[] structure											*/
  double     *m;	  /* pointer to an array of length [solids[].na] which expresses *species* in terms of moles of endmember components in *phase* */
  double     norm;	  /* squared norm of m[]													*/
  double     oxygen;	  /* Moles of oxygen in formula unit												*/
  double     *solToLiq;   /* converts 1 mole of solid phase to one mole of liquid                                                                       */
  double     nAtoms;      /* number of atoms in the formula unit of the phase                                                                           */
} ExtraSolids;
extern ExtraSolids extraSolids[];
extern int nes;

/*===================================================================================================================================================*/

typedef struct _residualDataInput {
  int    LEPRnum;    /* LEPRnum,                 unique LEPR database experiment index number                                                        */
  double t;          /* t,                       temperature of the experiment in Kelvin                                       			     */
  double p;          /* p,                       pressure of the experiment in bars                                            			     */
  double fo2;        /* fo2,                     log 10 fo2 of the experiment                                                  			     */
  int    nLiq;       /* nLiq,                    number of liquids in this experiment                                          			     */
  double **rLiq;     /* rLiq[0->nLiq][0->nc-1],  vector of independent composition variables for liquid(s) in this experiment  			     */
  int    nSol;       /* nSol,                    number of solids in this experiment                                           			     */
  int    *pIndex;    /* pIndex[0->nSol],         phase index of solid                                                          			     */
  int    *cIndex;    /* pIndex[0->nSol],         component index of solid                                                      			     */
  double **rSol;     /* rSol[0->nSol][0->nr],    vector of independent composition variables for solid(s) in this experiment   			     */
  int    *isEqual;   /* isEqual[0->nSol],        TRUE if equality constraint; FALSE if bound                                   			     */  
  double *depenG;    /* depen[0->nsol],          Dependent variable in regresion problem (Gibbs free energy)                                         */
  double *dependGdT; /* depen[0->nsol],          Dependent variable in regresion problem (negative of the entropy)                                   */
} ResidualDataInput;
extern ResidualDataInput *residualDataInput;

/*===================================================================================================================================================*/

typedef struct _residualOutput {
  int flag;          /* flag, TRUE if valid output retuned; false otherwise     								     */
  double *residuals; /* vector of returned residuals. Undef if valid == FALSE   								     */
  double *dr;        /* vector of residual derivatives d(r[i])/d(params).  Undef if valid == FALSE                                                   */
} ResidualOutput;
extern ResidualOutput *residualOutput;

/*===================================================================================================================================================*/

#ifndef USE_MPI
void calculateResidualPack(ResidualDataInput *residualDataInput, ResidualOutput *residualOutput);
#endif

#endif /* _Calibration_h */
