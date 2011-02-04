const char *est_satState_revised_ver(void) { return "January 25, 2011"; }

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Routines to estimate the composition and chemical affinity for
**      saturation with a solid solution at a particular T and P.
**      (file: EST_SATSTATE_REVISED.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  January 25, 2011  Original Version
**--
*/

#include "silmin.h"

#ifndef DEBUG
#define DEBUG
#endif

#define SCALE   1000.0  /* Scaling factor for chemical affinities           */

#define SUCCESS TRUE
#define FAILURE FALSE

/***************************************************************************
 * Consider an ideal solution of n+1 endmembers:
 * - A + RT ln x[1] + RT ln g[1]                    = - mu[1],  
 * - A + RT ln x[2] + RT ln g[2]                    = - mu[2], 
 *   ...
 * - A + RT ln x[n] + RT ln g[n]                    = - mu[n],
 * - A + RT ln(1-x[1]-x[2]-...-x[n]) + RT ln g[n+1] = - mu[n+1].
 *
 * Setting: f[1] = exp(-(mu[1]-RTlng[1]-mu[n]+RTlng[n])/(R*t)),
 *          f[2] = exp(-(mu[2]-RTlng[2]-mu[n]+RTlng[n])/(R*t)),
 *          ...
 *          f[n] = exp(-(mu[n]-RTlng[n]-mu[n+1]+RTlng[n+1])/(R*t))
 *
 * A solution is given by:
 * x[n]   = f[n]/(1+f[n]*(1+f[1]+f[2]+...+f[n-1])
 * x[n-1] = f[n-1]*x[n]
 * x[n-2] = f[n-2]*x[n]
 * ....
 * x[2]   = f[2]*x[n]
 * x[1]   = f[1]*x[n]
 *
 * Any of the original equations may be used to compute A
 ***************************************************************************/

int getAffinityAndCompositionRevised( /* Returns a MODE flag for success or failure */
  double t,              /* temperature (K)					*/
  double p,              /* pressure (bars)					*/
  int index,             /* index of solid phase in the solids[] structure	*/
                         /* -1 indicates liquid 				*/
  int    *zeroX,         /* TRUE if endmember component has zero mole fraction  */
  double *muMinusMu0,    /* vector of end-member mu - mu0 i.e. A + RTln(a)	*/
  double *affinity,      /* returned value, chemical affinity (J)		*/
  double *indepVar)      /* returned vector, composition of phase (length nr)	*/
{
  int i, j, iter = 0, foundSolution = FALSE;
  static double *moleFrac = NULL, *bVec = NULL, *gVec = NULL, *activity = NULL, *mu = NULL;
  static int    *nullComp = NULL, *nullList = NULL;
  int    hasNull, na, ne, nr, nz, solidID = -1, liquidMode;

  if (activity == NULL) {
    activity  = (double *)  malloc((unsigned) nlc*sizeof (double));
    bVec      = (double *)  malloc((unsigned) nlc*sizeof (double));
    gVec      = (double *)  malloc((unsigned) nlc*sizeof (double));
    moleFrac  = (double *)  malloc((unsigned) nlc*sizeof (double));
    mu        = (double *)  malloc((unsigned) nlc*sizeof (double));
    nullComp  = (int *)     malloc((unsigned) nlc*sizeof (int));
    nullList  = (int *)     malloc((unsigned) nlc*sizeof (int));
  }

  /* Test input parameters */
  if (t <= 0.0) 		  return FAILURE;
  if (p <  0.0) 		  return FAILURE;
  if (index < -1 || index >= npc) return FAILURE;

  /* Check parameters for algorithmic assumptions */
  liquidMode = (index == -1);
  if (!liquidMode) {
    na = solids[index].na; 
    nr = solids[index].nr;
    if (na != (nr+1)) return FAILURE;
    solidID = index;
  } else {
    na = nlc; 
    nr = nlc-1;
  }
 
  /* remove excluded components for computation of mole fraction estimates.
     the static nz is initialized here.                                    */
  for (i=0, hasNull=FALSE, nz=0; i<na; i++) { 
    nullComp[i] = zeroX[i]; hasNull |= zeroX[i];
    if (!nullComp[i]) { nullList[nz] = i; mu[nz++] = muMinusMu0[i]; } 
  }
  if (nz == 0) return FAILURE;

  for (i=0; i<na; i++) gVec[i] = 1.0;
  *affinity = 100000.0;
  
  while (!foundSolution && (iter < 100)) {
    double sum;
  
    /* take appropriate action for the number of non-zero components */
         if (nz == 0)                      bVec[na-1] = 0.0;
    else if (nz == 1) { moleFrac[0] = 1.0; bVec[na-1] = (mu[0]-gVec[0])/SCALE; }
    else {
      /* condense the activity cofficient vector */
      for (i=0, j=0; i<na; i++) if (!nullComp[i]) gVec[j++] = R*t*log(gVec[i]);
    
      /* Compute the f[n] terms and store them temporarily in moleFrac[] */
      sum = 1.0;
      if (nz > 2) for (i=0; i<(nz-2); i++) {
        moleFrac[i] = exp(-(mu[i]-gVec[i]-mu[nz-2]+gVec[nz-2])/(R*t)); sum += moleFrac[i];
      }
      moleFrac[nz-2] = exp(-(mu[nz-2]-gVec[nz-2]-mu[nz-1]+gVec[nz-1])/(R*t));
  
      /* Solve for the composition variables (mole fractions) */
      moleFrac[nz-2] /= 1.0 + moleFrac[nz-2]*sum; 
      moleFrac[nz-1]  = 1.0 - moleFrac[nz-2];
      if (nz > 2) for (i=0; i<(nz-2); i++) { 
        moleFrac[i] *= moleFrac[nz-2]; moleFrac[nz-1] -= moleFrac[i]; 
      }

      /* compute the chemical affinity (choice of mu[] is arbitrary) */
      bVec[na-1] = (mu[0] + R*t*log(moleFrac[0]) + gVec[0])/SCALE;
    }

    /* Reassemble the mole fraction and chemical potential vectors with zeros for the absent endmembers */
    if (hasNull) for (i=na-1, j=nz; i>=0; i--) {
      if(!nullComp[i]) moleFrac[i] = moleFrac[--j]; 
      else             moleFrac[i] = 0.0;
    }

    /* convert mole fractions of endmembers into independent compos var */
    if (!liquidMode) (*solids[solidID].convert)(SECOND, THIRD, t, p, NULL, moleFrac, bVec, NULL, NULL, NULL, NULL, NULL);
    else                                 conLiq(SECOND, THIRD, t, p, NULL, moleFrac, bVec, NULL, NULL, NULL, NULL);

    if (fabs(*affinity-bVec[nr]) < 0.1) foundSolution = TRUE;
    else {    
      if (!liquidMode) (*solids[solidID].activity)(FIRST, t, p, bVec, activity, NULL, NULL);
      else                                  actLiq(FIRST, t, p, bVec, activity, NULL, NULL, NULL);
      for (i=0; i<na; i++) if (moleFrac[i] != 0.0) gVec[i] = activity[i]/moleFrac[i];
    }
#ifdef DEBUG
    printf("getAffinityAndCompositionRevised iter = %d\n", iter);
    printf("  mole fractions: %13.6g %13.6g %13.6g affinity: %13.6g\n", moleFrac[0], moleFrac[1], moleFrac[2], bVec[nr]);
#endif
  }
  for (i=0; i<nr; i++) indepVar[i] = bVec[i]; *affinity = bVec[nr]*SCALE;
    
  return (iter < 100) ? SUCCESS : FAILURE;
}

/* end of file EST_SATSTATE_REVISED.C */
