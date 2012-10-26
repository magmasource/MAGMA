const char *subSolidusMuO2_ver(void) { return "$Id: subSolidusMuO2.c,v 1.4 2007/11/29 05:32:14 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: subSolidusMuO2.c,v $
MELTS Source Code: RCS Revision 1.4  2007/11/29 05:32:14  ghiorso
MELTS Source Code: RCS Majorite testMaj corrections.  Fixed "O2" in sol_struct_data.h to "o2".
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2006/08/17 20:47:54  ghiorso
MELTS Source Code: RCS Clarified variable initialization issues in routines.  Problems discovered
MELTS Source Code: RCS when compiler optimization is turned on.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2006/08/17 16:47:19  ghiorso
MELTS Source Code: RCS Made modifications to protect strings.  These modifications allow removal
MELTS Source Code: RCS of the flag -fwritable-strings during gcc compilation.  This brings the
MELTS Source Code: RCS code up to gcc 4.x standards.
MELTS Source Code: RCS
MELTS Source Code: RCS Other minor rearrangements and cleanup.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:36  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2003/05/03 18:43:56  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2003/04/28 20:44:46  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 1.6  1997/06/21  22:49:24  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 1.5  1997/05/03  20:23:04  ghiorso
 * *** empty log message ***
 *
 * Revision 1.4  1997/03/27  17:03:08  ghiorso
 * *** empty log message ***
 *
 * Revision 1.3  1996/09/24  20:33:19  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 1.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 1.1  1995/11/01  22:40:27  ghiorso
 * Initial revision
 *
 * Revision 1.1  1995/11/01  22:40:27  ghiorso
 * Initial revision
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**  Function subsolidusmuO2 now serves many masters, and replaces
**  subsoliduslog10fo2, since the output can just be divided by RTln10
**  to give log10fO2.  It uses a bitwise output flag to specify which
**  behavior to perform:
**
**	ZERO:	Takes input muO2 and forces system to this buffer; this
**      	operation is mutually exclusive from all the others.
**		Presently acts directly on silminState and uses T and P
**		directly from silminState.  If liquid is available, uses
**		internal function, not conLiq (i.e. Kress and Carmichael).
**		NOTE: BUFFERS TO FIXED muO2, NOT fO2 !!!
**	FIRST:	computes and returns muO2 for solid, liquid, or solid+liquid;
**		uses method described below; only works for equilibrium
**		assemblage.  DOES NOT USE KRESS and CARMICHAEL
**	SECOND: returns dmuO2dm, where m refers to all phase components
**		present in the solid assemblage, whether liquid is present or not.
**	        Repeated entries for multiple coexisting solids are inserted in
**		phase order, not component by component.
**	THIRD:  returns dmuO2dt.		\
**	FOURTH: returns dmuO2dp.		|
**	FIFTH:	returns d2muO2dm2.		|
**	SIXTH:	returns d2muO2dmdt.		| These use Kress and Carmichael
**	SEVENTH: returns d2muO2dmdp.		| if liquid is present.
**	EIGHTH: returns d2muO2dt2.		|
**	NINTH:	returns d2muO2dtdp.		|
**	TENTH:	returns d2muO2dp2.		/
**
**  The method for obtaining fO2 is as follows:
**
**  If liquid is present, uses the reaction
**
**	2 Fe2SiO4 (l) + O2 (g) = 2 Fe2O3 (l) + 2 SiO2 (l),
**
**  for options ZERO and FIRST only.  All others are referred to muO2Liq. If
**  liquid is absent, uses subsolidus assemblage.  For subsolidus calculations,
**  checks that FeO and Fe2O3 are present and then finds a balanced
**  stoichiometric redox reaction by SVD of the (usually) underconstrained 
**  system
**
**	/			\ / \   /  \
**	|1 0 0...		| |s|   |-1| <- O2
**	|0			| |t|   | 2| <- FE2O3
**	|0	**SolToOx	| |o| = |-4| <- FEO
**	|.			| |i|   | 0|  
**	|.			| |c|   | 0| <- all others zero
**	\			/ \ /   \  /
**
**  where the matrix has an extra row and column for O2 as a component and as a 
**  phase, and otherwise includes rows and columns for each oxide and each solid
**  component actually present in the assemblage (with repetition for coexisting
**  solids).  Any solution to this system is a suitably balanced redox reaction,
**  so WLOG the particular solution is used.
**
**  MODIFICATION HISTORY:
**
**  (1) See above
**--
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef BATCH_VERSION
#include <Xm/Xm.h>
#else
#define True '\001'
#endif

#include "recipes.h"                
#include "silmin.h"

#ifdef DEBUG
#undef DEBUG
#endif

#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))
#define SQUARE(x) ((x)*(x))

static double integer_power(double y, int x) {
  if (x > 0) return (y * integer_power(y, x-1));
  else if (x < 0) return (integer_power(y, x+1) / y);
  else return 1.0;
}

int subsolidusmuO2(int mask,
  double *muO2, /* muO2      = mu*O2                 BINARY MASK: 0000000001 */
  double *dm,   /* dm[i]     = d mu*O2/dm[i]         BINARY MASK: 0000000010 */
  double *dt,   /* dt        = d mu*O2/d T           BINARY MASK: 0000000100 */
  double *dp,   /* dp        = d mu*O2/d P           BINARY MASK: 0000001000 */
  double **d2m, /* d2m[i][j] = d mu*O2/dm[i][j]      BINARY MASK: 0000010000 */
  double *d2mt, /* d2mt[i]   = d mu*O2/dm[i]dt       BINARY MASK: 0000100000 */
  double *d2mp, /* d2mp[i]   = d mu*O2/dm[i]dp       BINARY MASK: 0001000000 */
  double *d2t2, /* d2t2      = d mu*O2/dt2           BINARY MASK: 0010000000 */ 
  double *d2tp, /* d2tp      = d mu*O2/dtdp          BINARY MASK: 0100000000 */
  double *d2p2) /* d2p2      = d mu*O2/dp2           BINARY MASK: 1000000000 */
{
  int i, j, k, l, nreact, *stoich, fe, acceptable, ns, z, y;
  int *oxide, *phaseIndex, *nCoexist, mm, n;
  static int *oldPhaseIndex, *oldNCoexist, oldMm, oldN;
  double *m , *r, *activities;
  double **stMatrix, *dstoich, *RHS;
  static double *olddstoich;
  double fudge = 1.0, error0 = 0.0, molesO2 = 0.0;
  int iter = 0;

  m = vector(0, nlc);
  r = vector(0, nlc);
  activities = vector(0, nlc);
  
  if (silminState->liquidMass != 0.0) for (ns=0; ns<silminState->nLiquidCoexist; ns++) for (i=0; i<nlc; i++) 
    molesO2 += (oxygen.liqToOx)[i]*(silminState->liquidComp)[ns][i];
  for (i=0; i<npc; i++) for (ns=0; ns<(silminState->nSolidCoexist)[i]; ns++) {
    if (solids[i].na == 1) molesO2 += (silminState->solidComp)[i][ns]*(oxygen.solToOx)[i];
    else for (j=0; j<solids[i].na; j++) molesO2 += (silminState->solidComp)[i+1+j][ns]*(oxygen.solToOx)[i+1+j];
  }

  /* liquid is absent -> need subsolidus reaction */
  if (silminState->liquidMass == 0.0) {
    for (n=1, i=0; i<npc; i++) n += silminState->nSolidCoexist[i]*solids[i].na;
    if (n == 1) {
      free_vector(m, 0, nlc); 
      free_vector(r, 0, nlc); 
      free_vector(activities, 0, nlc);
      *muO2 = 0.0;
      return TRUE;
    }

    oxide      = (int *)    calloc((size_t) (nc+1),sizeof(int));
    phaseIndex = (int *)    calloc((size_t) (n+1), sizeof(int));
    nCoexist   = (int *)    calloc((size_t) (n+1), sizeof(int));
    RHS        = (double *) calloc((size_t) (nc+1),sizeof(double));

    /* Construct reduced stoichiometry matrix -- rows for included oxide
        components plus oxygen, columns for phase-componentes present
        in the solid assemblage plus oxygen gas -- elements are solToOx */
    RHS[1] = -1.0;
    for (i=0, mm=1, fe=0; i<nc; i++) {
      if (silminState->bulkComp[i] != 0.0) {
        oxide[++mm] = i;
        if (bulkSystem[i].type == FEO)   {fe++; RHS[mm] = -4.0;}
        if (bulkSystem[i].type == FE2O3) {fe++; RHS[mm] =  2.0;}
      }
    }
    for (i=0, n=1; i<npc; i++) {
      if (silminState->nSolidCoexist[i] != 0) {
        if (solids[i].na == 1) {
          phaseIndex[++n] = i; nCoexist[n] = 0;
        } else {
          for (k=0; k<silminState->nSolidCoexist[i];k++) {
            for (j=0;j<solids[i].na;j++) {
              if (silminState->solidComp[i+1+j][k] != 0.0) {
                phaseIndex[++n] = i+1+j; nCoexist[n] = k;
              }
            }
          }
        }
      }
    }

    /* Decide whether a new reaction is needed */
    acceptable = TRUE;
    if (olddstoich != NULL) {
      acceptable = acceptable & (n  == oldN);
      acceptable = acceptable & (mm == oldMm);
      for (i=2;i<MIN(n, oldN);i++) {
	acceptable = acceptable & (phaseIndex[i] == oldPhaseIndex[i]);
	acceptable = acceptable & (nCoexist[i]   == oldNCoexist[i]);
      }
    } else acceptable = FALSE;

    if (acceptable == FALSE) {
      stMatrix = matrix(1, mm, 1, n);
      dstoich  = vector(1, n);
      for (j=2, stMatrix[1][1]=1; j<=n; j++) stMatrix[1][j]=0;
      for (i=2; i<=mm; i++) stMatrix[i][1]=0;
      for (i=2; i<=mm; i++) for (j=2; j<=n; j++) stMatrix[i][j] = solids[phaseIndex[j]].solToOx[oxide[i]];

      /* If FeO and Fe2O3 are both nonzero in the bulk composition,
       weight the solToOx matrix to emphasize abundant components,
       take the SVD, zero small singular values, backsub
       to get particular solution of stoichiometric values for the
       buffer, unweight it */
      if (fe == 2) {
        double *w, **v;
        char *valid;
        w = vector(1, n);
        v = matrix(1, n, 1, n);
        valid = (char *) malloc((size_t) n*sizeof(char));
        for (i=1;i<=mm;i++) {
          stMatrix[i][1] *= 10.0;
          valid[i] = True;
          for (j=2;j<=n;j++) stMatrix[i][j] *= silminState->solidComp[phaseIndex[j]][nCoexist[j]];
        }
        svdcmp(stMatrix, mm, n, w, v);
        for (i=1;i<=n;i++) if (w[i] < 1.0e-08) w[i] = 0.0;
        svbksb(stMatrix, w, v, mm, n, RHS, valid, dstoich);
        if (dstoich[1] != 0.0) {
          dstoich[1] *= 10.0;
          for (j=2; j<=n; j++) dstoich[j] *= silminState->solidComp[phaseIndex[j]][nCoexist[j]];
          for (j=1;j<=n;j++) dstoich[j] /= -dstoich[1];
        } else {
          printf("Failed to find buffering reaction\n");
          *muO2 = 0.0;
          return FALSE;
        }
        free_matrix(v, 1, n, 1, n);
        free_vector(w, 1, n);
        free(valid);
      } else {
        printf("Can't compute fO2 without FEO and FE2O3\n");
        *muO2 = 0.0;
        return FALSE;
      }
      free_matrix(stMatrix, 1, mm, 1, n);

      /* save info for next time */
      olddstoich    = (double *) REALLOC(olddstoich,    (size_t) (n+1)*sizeof(double));
      oldPhaseIndex = (int *)    REALLOC(oldPhaseIndex, (size_t) (n+1)*sizeof(int));
      oldNCoexist   = (int *)    REALLOC(oldNCoexist,   (size_t) (n+1)*sizeof(int));
      for (i=1;i<=n;i++) {
	olddstoich[i]    = dstoich[i];
	oldPhaseIndex[i] = phaseIndex[i];
	oldNCoexist[i]   = nCoexist[i];
      }
      oldN = n; oldMm = mm;
    } else {	/* use reaction from last time */
      dstoich = vector(1, n);
      for (i=1; i<=n; i++) dstoich[i] = olddstoich[i];
    }
    free(RHS);

    gibbs(silminState->T, silminState->P, "o2", &(oxygen.ref), NULL, NULL, &(oxygen.cur));

    while (mask & FIRST || !mask) {   /* calculate *muO2, return or iterate to buffer*/
      double *g0 = (double *) malloc((size_t) (n+1)*sizeof(double));
      double *a  = (double *) malloc((size_t) (n+1)*sizeof(double));
      double delta_g0, activity_product, tempmuO2, xi;

      g0[1] = oxygen.cur.g;

      for (i=2, xi=0.0; i<=n; i++) { /* now obtain g0 and activity for each reactant
				        and first-order reaction progress variable xi */
        if (solids[phaseIndex[i]].type == PHASE) {
          gibbs(silminState->T, silminState->P, (char *) solids[phaseIndex[i]].label, &(solids[phaseIndex[i]].ref), NULL, NULL, &(solids[phaseIndex[i]].cur));
          g0[i] = solids[phaseIndex[i]].cur.g;
          a[i] = 1.0;
        } else { /* reactant is a component -- step backwards to find phase */
	  double dadm, **dadr, **drdm;
          j=phaseIndex[i]; while(solids[--j].type != PHASE);
          dadr = matrix(0, solids[j].na, 0, solids[j].nr);
          drdm = matrix(0, solids[j].nr, 0, solids[j].na);
          for (k=0;k<solids[j].na;k++) {
            gibbs(silminState->T, silminState->P, (char *) solids[j+1+k].label, &(solids[j+1+k].ref), NULL, NULL, &(solids[j+1+k].cur));
            m[k] = silminState->solidComp[j+1+k][nCoexist[i]];
          }
          (*solids[j].convert)(SECOND, THIRD | FIFTH, silminState->T, silminState->P, NULL, m, r, NULL, drdm, NULL, NULL, NULL);
          (*solids[j].activity)(FIRST | THIRD, silminState->T, silminState->P, r, activities, NULL, dadr);
	  for (k=0,l=0; k<solids[j].na; k++) {
	    if (phaseIndex[i+l] == j+1+k && nCoexist[i+l] == nCoexist[i]) {
              g0[i+l] = solids[phaseIndex[i+l]].cur.g;
              a[i+l] = activities[k];
	      for (z=0, dadm=0.0; z<solids[j].nr; z++) dadm += dadr[k][z]*drdm[z][k];
              xi += SQUARE(dstoich[i+l])*dadm/a[i+l];
	      l++;
	    }
	  }
	  i += l-1;
          free_matrix(dadr,0, solids[j].na, 0, solids[j].nr);
          free_matrix(drdm,0, solids[j].nr, 0, solids[j].na);
        }
      }
      for (i=2, activity_product=1.0; i<=n; i++) activity_product *= pow(a[i],dstoich[i]);
      for (i=1, delta_g0=0.0; i<=n; i++) delta_g0 += dstoich[i]*g0[i];

      tempmuO2 = delta_g0 +  R*silminState->T * log(activity_product);
      if (mask & FIRST) {  /* just return *muO2 */
        *muO2 = tempmuO2;
        break;
      } else if (fabs(tempmuO2 - *muO2) >= sqrt(DBL_EPSILON)) {
        /* run the buffer reaction towards desired fO2 as far as legal */
        acceptable = FALSE;
        xi = fudge*(*muO2-tempmuO2)/(R*silminState->T*xi);
	if (!(iter & 3)) error0 = tempmuO2 - *muO2;
        if (!((iter-1) & 3)) {
	  if (error0 != (tempmuO2-*muO2)) fudge *= error0/(error0 - tempmuO2 + *muO2);
        }
	iter++;
        while (acceptable == FALSE) {
          acceptable = TRUE;
          if ((molesO2 -= xi) < 0.0) {
	    acceptable = FALSE;
#ifdef DEBUG
            printf("...subsolidusfO2: In while loop, Failure for oxygen.\n");
#endif
	  }
          for (i=2; i<n; i++) silminState->solidComp[phaseIndex[i]][nCoexist[i]] += xi * dstoich[i];
          for (i=0; i<npc; i++) { /* recompute phase abundance, check phases */
            if (solids[i].type == PHASE) {
              if (solids[i].na == 1) {
                if (silminState->solidComp[i][0] < 0.0) {
		  acceptable = FALSE;
#ifdef DEBUG
                  printf("...subsolidusfO2: In while loop, Failure for phase %s.\n", solids[i].label);
#endif
		}
              } else {
                double *mmm = (double *) malloc((size_t) solids[i].na*sizeof(double));
                for (k=0; k<silminState->nSolidCoexist[i]; k++) {
                  for (silminState->solidComp[i][k]=0.0, j=0; j<solids[i].na; j++)
                    silminState->solidComp[i][k] += (mmm[j] = silminState->solidComp[i+1+j][k]);
                  if (!(*solids[i].test)(SIXTH,silminState->T,silminState->P, solids[i].na, solids[i].nr, NULL, NULL, NULL, mmm)) {
		    acceptable = FALSE;
#ifdef DEBUG
                    printf("...subsolidusfO2: In while loop, Failure for phase %s.\n", solids[i].label);
#endif
		  }
                }
                free(mmm);
              }
            }
          }
          for (i=0; i<nc; i++) { /* recompute bulk composition */
            for ((silminState->bulkComp)[i] = 0.0,j=0; j<npc; j++) {
              for (ns=0; ns<(silminState->nSolidCoexist)[j]; ns++) {
                if (solids[j].na == 1) (silminState->bulkComp)[i] += (silminState->solidComp)[j][ns]*(solids[j].solToOx)[i]; 
                else {
                  for (k=0; k<solids[j].na; k++) (silminState->bulkComp)[i] += (silminState->solidComp)[j+1+k][ns]*(solids[j+1+k].solToOx)[i];
                }
              }
            }
            if (silminState->bulkComp[i] < 0.0) {
	      acceptable = FALSE;
#ifdef DEBUG
              printf("...subsolidusfO2: In while loop, Failure for oxide %s.\n", bulkSystem[i].label);
#endif
	    }
          }
          if (acceptable == FALSE) {    /* went too far, undo */
            molesO2 += xi;
            for (i=1; i<n; i++) silminState->solidComp[phaseIndex[i]][nCoexist[i]] -= xi * dstoich[i];
            xi /= 2.0;  /* On next attempt, step half as far */
#ifdef DEBUG
            printf("...subsolidusfO2: In while loop, xi = %20.13g.\n", xi);
#endif
            if (fabs(xi) < 100.0*DBL_EPSILON) {
	      printf("Can't compute a viable solution in subSolidusMuO2. Exiting.\n");
              return FALSE;
	    }
          }
        }
      } else break; /* converged */
      free(a); free(g0);
    }

    if (mask & SECOND) {
      double *a     = (double *) malloc((size_t) (n+1)*sizeof(double));
      double **dadm = matrix(1,n,1,n);

      for (i=2; i<=n; i++) { /* now obtain a and da/dmj for each reactant */
        if (solids[phaseIndex[i]].type == PHASE) {
          gibbs(silminState->T, silminState->P, (char *) solids[phaseIndex[i]].label, &(solids[phaseIndex[i]].ref), NULL, NULL, &(solids[phaseIndex[i]].cur));
          a[i] = 1.0;
          for (j=1; j<=n; j++) dadm[i][j] = 0.0;
        } else { /* reactant is a component -- step backwards to find phase */
          double **dadr, **drdm;
	  int y;

          j = phaseIndex[i]; while(solids[--j].type != PHASE);
          dadr = matrix(0, solids[j].na, 0, solids[j].nr);
          drdm = matrix(0, solids[j].nr, 0, solids[j].na);

          for (k=0;k<solids[j].na;k++) {
            gibbs(silminState->T, silminState->P, (char *) solids[j+1+k].label, &(solids[j+1+k].ref), NULL, NULL, &(solids[j+1+k].cur));
            m[k] = (silminState->solidComp)[j+1+k][nCoexist[i]];
          }
          (*solids[j].convert)(SECOND, THIRD | FIFTH, silminState->T, silminState->P, NULL, m, r, NULL, drdm, NULL, NULL, NULL);
          (*solids[j].activity)(FIRST | THIRD, silminState->T, silminState->P, r, activities, NULL, dadr);
	  for (y=0,z=0; y<solids[j].na; y++) {
	    if (phaseIndex[i+z] == j+1+y && nCoexist[i+z] == nCoexist[i]) { 
              a[i+z] = activities[y];
              for (k=2; k<=n; k++) { /* dadm[i][j] is zero if i,j are from different phases */
                if (solids[phaseIndex[k]].type == PHASE) dadm[i+z][k] = 0.0;
                else if ((phaseIndex[k] - j <= solids[j].na) && phaseIndex[k]>j && nCoexist[k]==nCoexist[i]) {
                  for (l=0,dadm[i+z][k]=0.0;l<solids[j].nr;l++) dadm[i+z][k] += drdm[l][phaseIndex[k]-j-1] * dadr[y][l];
                } else dadm[i+z][k] = 0.0;
              }
	      z++;
	    }
	  }
	  i += z-1;
          free_matrix(drdm, 0, solids[j].nr, 0, solids[j].na);
          free_matrix(dadr, 0, solids[j].na, 0, solids[j].nr);
        }
      }
      for (i=2; i<=n; i++) {
        for (j=2, dm[i-2]=0.0; j<=n; j++)
          dm[i-2] += dstoich[j]*dadm[j][i]/a[j];
        dm[i-2] *= R * silminState->T;
      }

      free_matrix(dadm,1,n,1,n); free(a);
    }

    if (mask & THIRD) {
      double *s0       = (double *) malloc((size_t) (n+1)*sizeof(double));
      double *dsmixdmi = (double *) malloc((size_t) (n+1)*sizeof(double));
      double delta_s0, dsmixdmi_sum;

      s0[1] = oxygen.cur.s;

      for (i=2; i<=n; i++) { /* now obtain s0 and dsmix/dmi for each reactant */
        if (solids[phaseIndex[i]].type == PHASE) {
          gibbs(silminState->T, silminState->P, (char *) solids[phaseIndex[i]].label, &(solids[phaseIndex[i]].ref), NULL, NULL, &(solids[phaseIndex[i]].cur));
          s0[i] = solids[phaseIndex[i]].cur.s;
          dsmixdmi[i] = 0.0;
        } else { /* reactant is a component -- step backwards to find phase */
          double mTotal, smix, *dsmixdrj, **drdm;

          j = phaseIndex[i]; while(solids[--j].type != PHASE);
          dsmixdrj = vector(0, solids[j].nr);
          drdm     = matrix(0, solids[j].nr, 0, solids[j].na);

          for (k=0, mTotal=0.0; k<solids[j].na; k++) {
            gibbs(silminState->T, silminState->P, (char *) solids[j+1+k].label, &(solids[j+1+k].ref), NULL, NULL, &(solids[j+1+k].cur));
            mTotal += (m[k] = (silminState->solidComp)[j+1+k][nCoexist[i]]);
          }
          (*solids[j].convert)(SECOND, THIRD | FIFTH, silminState->T, silminState->P, NULL, m, r, NULL, drdm, NULL, NULL, NULL);
          (*solids[j].smix)(FIRST | SECOND, silminState->T, silminState->P, r, &smix, dsmixdrj, NULL);
	  for (l=0,z=0; l<solids[j].na; l++) {
	    if (phaseIndex[i+z] == j+1+l && nCoexist[i+z] == nCoexist[i]) {
              s0[i+z] = solids[phaseIndex[i+z]].cur.s;
              /* Intensive dr to extensive dm conversion */
              for (k=0, dsmixdmi[i+z]=0.0; k<solids[j].nr; k++) dsmixdmi[i+z] += drdm[k][l] * dsmixdrj[k];
              dsmixdmi[i+z] = mTotal*dsmixdmi[i+z] + smix;
	      z++;
	    }
	  }
	  i += z-1;
          free_matrix(drdm, 0, solids[j].nr, 0, solids[j].na);
          free_vector(dsmixdrj, 0, solids[j].nr);
        }
      }
      for (i=2, dsmixdmi_sum=0.0; i<=n; i++) dsmixdmi_sum += dstoich[i]*dsmixdmi[i];
      for (i=1, delta_s0=0.0; i<=n; i++) delta_s0 += dstoich[i]*s0[i];

      *dt = -delta_s0 - dsmixdmi_sum;
      free(dsmixdmi); free(s0);
    }

    if (mask & FOURTH) {
      double *v0       = (double *) malloc((size_t) (n+1)*sizeof(double));
      double *dvmixdmi = (double *) malloc((size_t) (n+1)*sizeof(double));
      double delta_v0, dvmixdmi_sum;

      v0[1] = 0.0;

      for (i=2; i<=n; i++) { /* now obtain v0 and dvmix/dmi for each reactant */
        if (solids[phaseIndex[i]].type == PHASE) {
          gibbs(silminState->T, silminState->P, (char *) solids[phaseIndex[i]].label, &(solids[phaseIndex[i]].ref), NULL, NULL, &(solids[phaseIndex[i]].cur));
          v0[i] = solids[phaseIndex[i]].cur.v;
          dvmixdmi[i] = 0.0;
        } else { /* reactant is a component -- step backwards to find phase */
          double mTotal, vmix, *dvmixdrj, **drdm;

          j=phaseIndex[i]; while(solids[--j].type != PHASE);
          dvmixdrj = vector(0, solids[j].nr);
          drdm     = matrix(0, solids[j].nr, 0, solids[j].na);

          for (k=0,mTotal=0.0;k<solids[j].na;k++) {
            gibbs(silminState->T, silminState->P, (char *) solids[j+1+k].label, &(solids[j+1+k].ref), NULL, NULL, &(solids[j+1+k].cur));
            mTotal += (m[k] = (silminState->solidComp)[j+1+k][nCoexist[i]]);
          }
          (*solids[j].convert)(SECOND, THIRD | FIFTH, silminState->T, silminState->P, NULL, m, r, NULL, drdm, NULL, NULL, NULL);
          (*solids[j].vmix)(FIRST | SECOND, silminState->T, silminState->P, r, &vmix, dvmixdrj, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	  for (l=0,z=0; l<solids[j].na; l++) {
	    if (phaseIndex[i+z] == j+1+l && nCoexist[i+z] == nCoexist[i]) {
              v0[i+z] = solids[phaseIndex[i+z]].cur.v;
              /* Intensive dr to extensive dm conversion */
              for (k=0, dvmixdmi[i+z]=0.0; k<solids[j].nr; k++) dvmixdmi[i+z] += drdm[k][l] * dvmixdrj[k];
              dvmixdmi[i+z] = mTotal*dvmixdmi[i+z] + vmix;
	      z++;
	    }
	  }
	  i += z-1;
          free_matrix(drdm, 0, solids[j].nr,0, solids[j].na);
          free_vector(dvmixdrj, 0, solids[j].nr);
        }
      }
      for (i=2, dvmixdmi_sum=0.0; i<=n; i++) dvmixdmi_sum += dstoich[i]*dvmixdmi[i];
      for (i=1, delta_v0=0.0; i<=n; i++) delta_v0 += dstoich[i]*v0[i];

      *dp = delta_v0 + dvmixdmi_sum;
      free(dvmixdmi); free(v0);
    }

    if (mask & FIFTH) {
      double ***d3gmixdm3;
      int o, p, q;
      d3gmixdm3 = (double ***) malloc((size_t) (n+1)*sizeof(double **));
      for (i=1; i<=n; i++) d3gmixdm3[i] = matrix(1, n, 1, n);

      for (i=2; i<=n; i++) { /* now obtain d3gmixdm3 for each reactant */
        if (solids[phaseIndex[i]].type == PHASE) {
          for (j=1; j<=n; j++) for (k=1; k<=n; k++) d3gmixdm3[i][j][k] = 0.0;
        } else { /* reactant is a component -- step backwards to find phase */
          double mTotal, *dgmixdr, **d2gmixdr2, ***d3gmixdr3, **drdm, ***d2rdm2, ****d3rdm3;

          j = phaseIndex[i]; while(solids[--j].type != PHASE);
          dgmixdr   = vector(0, solids[j].nr);
          d2gmixdr2 = matrix(0, solids[j].nr, 0, solids[j].nr);
          d3gmixdr3 = (double ***) malloc((size_t) solids[j].nr*sizeof(double **));
          for (k=0; k<solids[j].nr; k++) d3gmixdr3[k] = matrix(0, solids[j].nr, 0, solids[j].nr);
          drdm = matrix(0, solids[j].nr, 0, solids[j].na);
          d2rdm2 = (double ***) malloc((size_t) solids[j].nr*sizeof(double **));
          for (k=0; k<solids[j].nr; k++) d2rdm2[k] = matrix(0,solids[j].na,0,solids[j].na);
          d3rdm3 = (double ****) malloc((size_t) solids[j].nr*sizeof(double ***));
          for (k=0; k<solids[j].nr; k++) {
            d3rdm3[k] = (double ***) malloc((size_t) solids[j].na*sizeof(double **));
            for (l=0; l<solids[j].na; l++) d3rdm3[k][l] = matrix(0,solids[j].na,0,solids[j].na);
          }

          for (k=0,mTotal=0.0;k<solids[j].na;k++) {
            gibbs(silminState->T, silminState->P, (char *) solids[j+1+k].label, &(solids[j+1+k].ref), NULL, NULL, &(solids[j+1+k].cur));
            mTotal += (m[k] = (silminState->solidComp)[j+1+k][nCoexist[i]]);
          }
          (*solids[j].convert)(SECOND, THIRD | FIFTH | SIXTH | EIGHTH, silminState->T, silminState->P, NULL, m, r, NULL, drdm, d2rdm2, NULL, d3rdm3);
          (*solids[j].gmix)(SECOND | THIRD | FOURTH, silminState->T, silminState->P, r, NULL, dgmixdr, d2gmixdr2, d3gmixdr3);
	  for (y=0,z=0; y<solids[j].na; y++) {
	    if (phaseIndex[i+z] == j+1+y && nCoexist[i+z] == nCoexist[i]) {
              /* d3gmixdm3[i][q][k] is zero if q,k,or i are from other phases */
              for (k=2;k<=n;k++) {
                if (solids[phaseIndex[k]].type == PHASE) for (l=2; l<=n; l++) d3gmixdm3[i+z][k][l] = 0.0;
                else if (phaseIndex[k] - j <= solids[j].na && phaseIndex[k]>j && nCoexist[k]==nCoexist[i]) {
                  double temp_o, temp_p;
                  for (q=2;q<=n;q++) {
                    if (phaseIndex[q] - j <= solids[j].na && phaseIndex[q]>j && nCoexist[q]==nCoexist[i]) {
                      for (l=0,d3gmixdm3[i+z][k][q]=0.0;l<solids[j].nr;l++) {
                        for (o=0,temp_o=0.0;o<solids[j].nr;o++) {
                          for (p=0, temp_p=0.0; p<solids[j].nr; p++) temp_p += drdm[p][phaseIndex[k]-j-1] * d3gmixdr3[p][o][l];
                          temp_o += mTotal*((d2rdm2[o][phaseIndex[q]-j-1][phaseIndex[k]-j-1]
                              *drdm[l][y] + d2rdm2[l][y][phaseIndex[k]-j-1]
                              * drdm[o][phaseIndex[q]-j-1] + d2rdm2[l][y][phaseIndex[q]-j-1]
                              * drdm[o][phaseIndex[k]-j-1]) * d2gmixdr2[o][l]
			      + drdm[o][phaseIndex[q]-j-1] * drdm[l][y]*temp_p);
                          temp_o += d2gmixdr2[o][l]*
                            (drdm[o][phaseIndex[k]-j-1]*drdm[l][y] +
                            drdm[o][phaseIndex[k]-j-1]*drdm[l][phaseIndex[q]-j-1] +
                            drdm[o][phaseIndex[q]-j-1]*drdm[l][y]);
                        }
                        d3gmixdm3[i+z][k][q] += temp_o + dgmixdr[l]*(mTotal*
                          d3rdm3[l][y][phaseIndex[k]-j-1][phaseIndex[q]-j-1]
                          + d2rdm2[l][y][phaseIndex[k]-j-1]
                          + d2rdm2[l][phaseIndex[k]-j-1][phaseIndex[q]-j-1]
                          + d2rdm2[l][phaseIndex[q]-j-1][y]);
                      }
                    }  else d3gmixdm3[i+z][k][q] = 0.0;
                  }
                } else for (q=2;q<=n;q++) d3gmixdm3[i+z][k][q] = 0.0;
              }
	      z++;
	    }
	  }
	  i += z-1;

          for (k=0; k<solids[j].nr; k++) {
            for (l=0; l<solids[j].na; l++) free_matrix(d3rdm3[k][l], 0, solids[j].na, 0, solids[j].na);
            free(d3rdm3[k]);
          }
          free(d3rdm3);
          for (k=0; k<solids[j].nr; k++) free_matrix(d2rdm2[k], 0, solids[j].na, 0, solids[j].na);
          free(d2rdm2);
          for (k=0; k<solids[j].nr; k++) free_matrix(d3gmixdr3[k], 0, solids[j].nr, 0, solids[j].nr);
          free(d3gmixdr3);
          free_matrix(drdm, 0, solids[j].nr, 0, solids[j].na);
          free_matrix(d2gmixdr2, 0, solids[j].nr, 0, solids[j].nr);
          free_vector(dgmixdr, 0, solids[j].nr);
        }
      }
      for (k=2; k<=n; k++) for (q=2; q<=n; q++) for (i=2, d2m[k-2][q-2]=0.0; i<=n; i++) d2m[k-2][q-2] += dstoich[i]*d3gmixdm3[i][q][k];
      for (i=1; i<=n; i++) free_matrix(d3gmixdm3[i], 1, n, 1, n);
      free(d3gmixdm3);
    }
 
    if (mask & SIXTH) {
      double **d2smixdm2 = matrix(1, n, 1, n);

      for (i=2; i<=n; i++) { /* now obtain d2smixdm2 for each reactant */
        if (solids[phaseIndex[i]].type == PHASE) {
          for (j=1; j<=n; j++) d2smixdm2[i][j] = 0.0;
        } else { /* reactant is a component -- step backwards to find phase */
          double mTotal, *dsmixdr, **d2smixdr2, **drdm, ***d2rdm2;

          j = phaseIndex[i]; while(solids[--j].type != PHASE);
          dsmixdr   = vector(0, solids[j].nr);
          d2smixdr2 = matrix(0, solids[j].nr, 0, solids[j].nr);
          drdm      = matrix(0, solids[j].nr, 0, solids[j].na);
          d2rdm2    = (double ***) malloc((size_t) solids[j].nr*sizeof(double **));
          for (k=0; k<solids[j].nr; k++) d2rdm2[k] = matrix(0, solids[j].na, 0, solids[j].na);

          for (k=0,mTotal=0.0;k<solids[j].na;k++) {
            gibbs(silminState->T, silminState->P, (char *) solids[j+1+k].label, &(solids[j+1+k].ref), NULL, NULL, &(solids[j+1+k].cur));
            mTotal += (m[k] = (silminState->solidComp)[j+1+k][nCoexist[i]]);
          }
          (*solids[j].convert)(SECOND, THIRD | FIFTH | SIXTH, silminState->T, silminState->P, NULL, m, r, NULL, drdm, d2rdm2, NULL, NULL);
          (*solids[j].smix)(SECOND | THIRD, silminState->T, silminState->P, r, NULL, dsmixdr, d2smixdr2);
	  for (y=0,z=0; y<solids[j].na; y++) {
	    if (phaseIndex[i+z] == j+1+y && nCoexist[i+z] == nCoexist[i]) {
              /* intensive dr to extensive dm conversion; 
                 d2smixdm2[i][k] is zero if k or i are from other phases */
              for (k=2; k<=n; k++) {
                if (solids[phaseIndex[k]].type == PHASE) d2smixdm2[i+z][k] = 0.0;
                else if(phaseIndex[k] - j <= solids[j].na && phaseIndex[k]>j && nCoexist[i]==nCoexist[k]) {
                  double temp;
                  int o;
                  for (l=0, d2smixdm2[i+z][k]=0.0; l<solids[j].nr; l++) {
                    for (o=0, temp=0.0; o<solids[j].nr; o++) temp += drdm[o][y] * d2smixdr2[o][l];
                    d2smixdm2[i+z][k] += dsmixdr[l]*(mTotal*
                      d2rdm2[l][y][phaseIndex[k]-j-1]
                      + drdm[l][y] + drdm[l][phaseIndex[k]-j-1]) +
                      mTotal*drdm[l][phaseIndex[k]-j-1]*temp;
                  }
                } else d2smixdm2[i+z][k] = 0.0;
              }
	      z++;
	    }
	  }
	  i += z-1;

          for (k=0; k<solids[j].nr; k++) free_matrix(d2rdm2[k], 0, solids[j].na, 0, solids[j].na);
          free(d2rdm2);
          free_matrix(drdm, 0, solids[j].nr, 0, solids[j].na);
          free_matrix(d2smixdr2, 0, solids[j].nr, 0, solids[j].nr);
          free_vector(dsmixdr, 0, solids[j].nr);
        }
      }
      for (i=2; i<=n; i++) for (k=2, d2mt[i-2]=0.0; k<=n; k++) d2mt[i-2] -= dstoich[k]*d2smixdm2[i][k];

      free_matrix(d2smixdm2, 1, n, 1, n);
    }

    if (mask & SEVENTH) {
      double **d2vmixdm2 = matrix(1, n, 1, n); 

      for (i=2; i<=n; i++) { /* now obtain d2vmixdm2 for each reactant */
        if (solids[phaseIndex[i]].type == PHASE) {
          for (j=1; j<=n; j++) d2vmixdm2[i][j] = 0.0;
        } else { /* reactant is a component -- step backwards to find phase */
          double mTotal, *dvmixdr, **d2vmixdr2, **drdm, ***d2rdm2;

          j = phaseIndex[i]; while(solids[--j].type != PHASE);
          dvmixdr   = vector(0, solids[j].nr);
          d2vmixdr2 = matrix(0, solids[j].nr, 0, solids[j].nr);
          drdm      = matrix(0, solids[j].nr, 0, solids[j].na);
          d2rdm2    = (double ***) malloc((size_t) solids[j].nr*sizeof(double **));
          for (k=0; k<solids[j].nr; k++) d2rdm2[k] = matrix(0, solids[j].na, 0, solids[j].na);

          for (k=0,mTotal=0.0;k<solids[j].na;k++) {
            gibbs(silminState->T, silminState->P, (char *) solids[j+1+k].label, &(solids[j+1+k].ref), NULL, NULL, &(solids[j+1+k].cur));
            mTotal += (m[k] = (silminState->solidComp)[j+1+k][nCoexist[i]]);
          }
          (*solids[j].convert)(SECOND, THIRD | FIFTH | SIXTH, silminState->T, silminState->P, (double *) NULL, m, r, NULL, drdm, d2rdm2, NULL, NULL);
          (*solids[j].vmix)(SECOND | THIRD, silminState->T, silminState->P, r, NULL, dvmixdr, d2vmixdr2, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	  for (y=0,z=0; y<solids[j].na; y++) {
	    if (phaseIndex[i+z] == j+1+y && nCoexist[i+z] == nCoexist[i]) {
              /* intensive dr to extensive dm conversion;
                 d2vmixdm2[i][k] is zero if k or i are from other phases */
              for (k=2; k<=n; k++) {
                if (solids[phaseIndex[k]].type == PHASE) d2vmixdm2[i+z][k] = 0.0;
                else if(phaseIndex[k] - j <= solids[j].na && phaseIndex[k]>j && nCoexist[i]==nCoexist[k]) {
                  double temp;
                  int o;
                  for (l=0, d2vmixdm2[i+z][k]=0.0; l<solids[j].nr; l++) {
                    for (o=0, temp=0.0; o<solids[j].nr; o++) temp += drdm[o][y] * d2vmixdr2[o][l];
                    d2vmixdm2[i+z][k] += dvmixdr[l]*(mTotal*
                      d2rdm2[l][y][phaseIndex[k]-j-1]
                      + drdm[l][y] + drdm[l][phaseIndex[k]-j-1]) +
                      mTotal*drdm[l][phaseIndex[k]-j-1]*temp;
                  }
                } else d2vmixdm2[i+z][k] = 0.0;
              }
	      z++;
	    }
	  }
	  i += z-1;

          for (k=0; k<solids[j].nr; k++) free_matrix(d2rdm2[k], 0, solids[j].na, 0, solids[j].na);
          free(d2rdm2);
          free_matrix(drdm, 0, solids[j].nr, 0, solids[j].na);
          free_matrix(d2vmixdr2, 0, solids[j].nr, 0, solids[j].nr);
          free_vector(dvmixdr, 0, solids[j].nr);
        }
      }
      for (i=2; i<=n; i++) for (k=2, d2mp[i-2]=0.0; k<=n; k++) d2mp[i-2] += dstoich[k]*d2vmixdm2[i][k];

      free_matrix(d2vmixdm2,1,n,1,n);
    }

    if (mask & EIGHTH) {
      double *Cp0      = (double *) malloc((size_t) (n+1)*sizeof(double));
      double *dCpmixdm = (double *) malloc((size_t) (n+1)*sizeof(double));
      double delta_Cp0, dCpmixdm_sum;

      Cp0[1] = oxygen.cur.cp;

      for (i=2; i<=n; i++) { /* obtain Cp0 and dCpmix/dmi for each reactant */
        if (solids[phaseIndex[i]].type == PHASE) {
          gibbs(silminState->T, silminState->P, (char *) solids[phaseIndex[i]].label, &(solids[phaseIndex[i]].ref), NULL, NULL, &(solids[phaseIndex[i]].cur));
          Cp0[i] = solids[phaseIndex[i]].cur.cp;
          dCpmixdm[i] = 0.0;
        } else { /* reactant is a component -- step backwards to find phase */
          double mTotal, cpmix, *dCpmixdr, **drdm;

          j = phaseIndex[i]; while(solids[--j].type != PHASE);
          dCpmixdr = vector(0, solids[j].nr);
          drdm     = matrix(0, solids[j].nr, 0, solids[j].na);

          for (k=0, mTotal=0.0; k<solids[j].na; k++) {
            gibbs(silminState->T, silminState->P, (char *) solids[j+1+k].label, &(solids[j+1+k].ref), NULL, NULL, &(solids[j+1+k].cur));
            mTotal += (m[k] = (silminState->solidComp)[j+1+k][nCoexist[i]]);
          }
          (*solids[j].convert)(SECOND, THIRD | FIFTH, silminState->T, silminState->P, NULL, m, r, NULL, drdm, NULL, NULL, NULL);
          (*solids[j].cpmix)(FIRST | THIRD, silminState->T, silminState->P, r, &cpmix, (double *) NULL, dCpmixdr);
	  for (y=0, z=0; y<solids[j].na; y++) {
	    if (phaseIndex[i+z] == j+1+y && nCoexist[i+z] == nCoexist[i]) {
              Cp0[i+z] = solids[phaseIndex[i+z]].cur.cp;
              /* intensive dr to extensive dm conversion */
              for (k=0, dCpmixdm[i+z]=0.0; k<solids[j].nr; k++) dCpmixdm[i+z] += drdm[k][y] * dCpmixdr[k];
              dCpmixdm[i+z] = mTotal*dCpmixdm[i+z] + cpmix;
	      z++;
	    }
	  }
	  i += z-1;
          free_matrix(drdm, 0, solids[j].nr, 0, solids[j].na);
          free_vector(dCpmixdr, 0, solids[j].nr);
        }
      }
      for (i=2, dCpmixdm_sum=0.0; i<=n; i++) dCpmixdm_sum += dstoich[i]*dCpmixdm[i];
      for (i=1, delta_Cp0=0.0; i<=n; i++) delta_Cp0 += dstoich[i]*Cp0[i];

      *d2t2 = -(delta_Cp0 + dCpmixdm_sum)/silminState->T;
      free(dCpmixdm); free(Cp0);
    }

    if (mask & NINTH) {
      double *dvdt0      = (double *) malloc((size_t) (n+1)*sizeof(double));
      double *d2vmixdmdt = (double *) malloc((size_t) (n+1)*sizeof(double));
      double delta_dvdt0, d2vmixdmdt_sum;

      dvdt0[1] = 0.0;

      for (i=2; i<=n; i++) { /* now obtain dvdt0 and d2vmix/dmdt for each reactant */
        if (solids[phaseIndex[i]].type == PHASE) {
          gibbs(silminState->T, silminState->P, (char *) solids[phaseIndex[i]].label, &(solids[phaseIndex[i]].ref), NULL, NULL, &(solids[phaseIndex[i]].cur));
          dvdt0[i] = solids[phaseIndex[i]].cur.dvdt;
          d2vmixdmdt[i] = 0.0;
        } else { /* reactant is a component -- step backwards to find phase */
          double mTotal, dvdt, *d2vmixdrdt, **drdm;

          j = phaseIndex[i]; while(solids[--j].type != PHASE);
          d2vmixdrdt = vector(0, solids[j].nr);
          drdm       = matrix(0, solids[j].nr, 0, solids[j].na);

          for (k=0,mTotal=0.0;k<solids[j].na;k++) {
            gibbs(silminState->T, silminState->P, (char *) solids[j+1+k].label, &(solids[j+1+k].ref), NULL, NULL, &(solids[j+1+k].cur));
            mTotal += (m[k] = (silminState->solidComp)[j+1+k][nCoexist[i]]);
          }
          (*solids[j].convert)(SECOND, THIRD | FIFTH, silminState->T, silminState->P, NULL, m, r, NULL, drdm, NULL, NULL, NULL);
          (*solids[j].vmix)(FOURTH | NINTH, silminState->T, silminState->P, r, NULL, NULL, NULL, &dvdt, NULL, NULL, NULL, NULL, d2vmixdrdt, NULL);
	  for (y=0, z=0; y<solids[j].na; y++) {
	    if (phaseIndex[i+z] == j+1+y && nCoexist[i+z] == nCoexist[i]) {
              dvdt0[i+z] = solids[phaseIndex[i+z]].cur.dvdt;
              /* intensive dr to extensive dm conversion */
              for (k=0, d2vmixdmdt[i+z]=0.0; k<solids[j].nr; k++) d2vmixdmdt[i+z] += drdm[k][y] * d2vmixdrdt[k];
              d2vmixdmdt[i+z] = mTotal*d2vmixdmdt[i+z] + dvdt;
	      z++;
	    }
	  }
	  i += z-1;
          free_matrix(drdm, 0, solids[j].nr, 0, solids[j].na);
          free_vector(d2vmixdrdt, 0, solids[j].nr);
        }
      }
      for (i=2, d2vmixdmdt_sum=0.0; i<=n; i++) d2vmixdmdt_sum += dstoich[i]*d2vmixdmdt[i];
      for (i=1, delta_dvdt0=0.0; i<=n; i++) delta_dvdt0 += dstoich[i]*dvdt0[i];

      *d2tp = delta_dvdt0 + d2vmixdmdt_sum;
      free(d2vmixdmdt); free(dvdt0);
    }

    if (mask & TENTH) {
      double *dvdp0      = (double *) malloc((size_t) (n+1)*sizeof(double));
      double *d2vmixdmdp = (double *) malloc((size_t) (n+1)*sizeof(double));
      double delta_dvdp0, d2vmixdmdp_sum;

      dvdp0[1] = 0.0;

      for (i=2; i<=n; i++) { /* now obtain dvdp0 and d2vmix/dmdp for each reactant */
        if (solids[phaseIndex[i]].type == PHASE) {
          gibbs(silminState->T, silminState->P, (char *) solids[phaseIndex[i]].label, &(solids[phaseIndex[i]].ref), NULL, NULL, &(solids[phaseIndex[i]].cur));
          dvdp0[i] = solids[phaseIndex[i]].cur.dvdp;
          d2vmixdmdp[i] = 0.0;
        } else { /* reactant is a component -- step backwards to find phase */
          double mTotal, dvdp, *d2vmixdrdp, **drdm;

          j = phaseIndex[i]; while(solids[--j].type != PHASE);
          d2vmixdrdp = vector(0, solids[j].nr);
          drdm       = matrix(0, solids[j].nr, 0, solids[j].na);

          for (k=0, mTotal=0.0; k<solids[j].na; k++) {
            gibbs(silminState->T, silminState->P, (char *) solids[j+1+k].label, &(solids[j+1+k].ref), NULL, NULL, &(solids[j+1+k].cur));
            mTotal += (m[k] = (silminState->solidComp)[j+1+k][nCoexist[i]]);
          }
          (*solids[j].convert)(SECOND, THIRD | FIFTH, silminState->T, silminState->P, NULL, m, r, NULL, drdm, NULL, NULL, NULL);
          (*solids[j].vmix)(FIFTH | TENTH, silminState->T, silminState->P, r, NULL, NULL, NULL, NULL, &dvdp, NULL, NULL, NULL, NULL, d2vmixdrdp);
	  for (y=0, z=0; y<solids[j].na; y++) {
	    if (phaseIndex[i+z] == j+1+y && nCoexist[i+z] == nCoexist[i]) {
              dvdp0[i+z] = solids[phaseIndex[i+z]].cur.dvdp;
              /* intensive dr to extensive dm conversion */
              for (k=0, d2vmixdmdp[i+z]=0.0; k<solids[j].nr; k++) d2vmixdmdp[i+z] += drdm[k][y] * d2vmixdrdp[k];
              d2vmixdmdp[i+z] = mTotal*d2vmixdmdp[i+z] + dvdp;
	      z++;
	    }
	  }
	  i += z-1;
          free_matrix(drdm, 0, solids[j].nr, 0, solids[j].na);
          free_vector(d2vmixdrdp, 0, solids[j].nr);
        }
      }
      for (i=2, d2vmixdmdp_sum=0.0; i<=n; i++) d2vmixdmdp_sum += dstoich[i]*d2vmixdmdp[i];
      for (i=1, delta_dvdp0=0.0; i<=n; i++) delta_dvdp0 += dstoich[i]*dvdp0[i];

      *d2p2 = delta_dvdp0 + d2vmixdmdp_sum;
      free(d2vmixdmdp); free(dvdp0);
    }

    free_vector(dstoich, 1, n); free(oxide); free(phaseIndex); free(nCoexist);

  } else {  /* if liquid is present use it */
    while (mask & FIRST || !mask) {
      double *xLiq  = (double *) malloc((size_t) nlc*sizeof(double));
      double *oxLiq = (double *) malloc((size_t) nc*sizeof(double));
      double *g0, xi, *a, delta_g0, activity_product, tempmuO2;
      int *liqNum;

      nreact = 4; 
      g0     = (double *) malloc((size_t) nreact*sizeof(double));
      a      = (double *) malloc((size_t) nreact*sizeof(double));
      stoich = (int *)    malloc((size_t) nreact*sizeof(int));
      liqNum = (int *)    malloc((size_t) nreact*sizeof(int));

      gibbs(silminState->T, silminState->P, "o2", &(oxygen.ref), NULL, NULL, &(oxygen.cur));
      g0[0] = oxygen.cur.g;
      stoich[0] = -1;

      for (i=0, fe=0; i<nc; i++) if (bulkSystem[i].type == FEO || bulkSystem[i].type == FE2O3) fe++;
      for (i=0; i<nlc; i++) gibbs(silminState->T, silminState->P, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
      if (fe != 2) {
        printf("Can't compute fO2 without FEO and FE2O3\n");
        *muO2 = 0.0;
        free(xLiq); free(oxLiq); free(g0); free(a); free(stoich); free(liqNum);
        return FALSE;
      }
      conLiq(SECOND, THIRD | FOURTH, silminState->T, silminState->P, NULL, (silminState->liquidComp)[0], r, xLiq, NULL, NULL, NULL);
      for (i=0; i<nc; i++) {
        for (j=0, oxLiq[i]=0.0; j<nlc; j++) oxLiq[i] += xLiq[j]*liquid[j].liqToOx[i];
      }

      actLiq(FIRST, silminState->T, silminState->P, r, activities, NULL, NULL, NULL);
      for (i=0;i<nlc;i++) {
        if (!strcmp(liquid[i].label,"SiO2")) {
          a[1] = activities[i];
          g0[1] = liquid[i].cur.g;
          stoich[1] = 2; liqNum[1] = i;
        } else if (!strcmp(liquid[i].label,"Fe2O3")) {
          a[2] = activities[i];
          g0[2] = liquid[i].cur.g;
          stoich[2] = 2; liqNum[2] = i;
        } else if (!strcmp(liquid[i].label,"Fe2SiO4")) {
          a[3] = activities[i];
          g0[3] = liquid[i].cur.g;
          stoich[3] = -2; liqNum[3] = i;
        }
      }
 
      for (i=1, activity_product=1.0; i<nreact; i++) activity_product *= integer_power(a[i],stoich[i]);
      for (i=0, delta_g0=0.0; i<nreact; i++) delta_g0 += stoich[i]*g0[i];

      tempmuO2 = delta_g0 + R*silminState->T * log(activity_product);
      if (mask & FIRST) {  /* just return *muO2 */
        *muO2 = tempmuO2;
        break;
      } else if (fabs(xi = (tempmuO2 - *muO2)) >= DBL_EPSILON) {
        /* run the buffer reaction towards desired fO2 as far as legal */
        acceptable = FALSE;
        while (acceptable == FALSE) {
          acceptable = TRUE;
          if ((molesO2 -= xi) < 0.0) acceptable = FALSE;
          for (i=1;i<nreact;i++) {
            (silminState->liquidComp)[0][liqNum[i]] += xi * stoich[i];
            if ((silminState->liquidComp)[0][liqNum[i]] < 0.0) acceptable = FALSE;
            for (j=0; j<nc; j++)  /* recompute bulk composition */
              silminState->bulkComp[j] += xi *stoich[i] * (liquid[liqNum[i]].liqToOx)[j];
          }
          if (acceptable == FALSE) {    /* went too far, undo */
            molesO2 += xi;
            for (i=1; i<nreact; i++) (silminState->liquidComp)[0][liqNum[i]] -= xi * stoich[i];
            for (j=0; j<nc; j++)  /* recompute bulk composition */
              silminState->bulkComp[j] -= xi *stoich[i] * (liquid[liqNum[i]].liqToOx)[j];
            xi /= 2.0;  /* On next attempt, step half as far */
          }
        }
      } else break; /* converged */
      free(a); free(g0); free(stoich); free(xLiq); free(oxLiq); free(liqNum);
    }
    /* Pass other liquid jobs on to muO2Liq */
    if (mask & (SECOND | THIRD | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH | NINTH | TENTH))
      muO2Liq(mask, silminState->T, silminState->P, (silminState->liquidComp)[0], muO2, dm, dt, dp, d2m, d2mt, d2mp, d2t2, d2tp, d2p2);
  }

  free_vector(m, 0, nlc); free_vector(r, 0, nlc); free_vector(activities, 0, nlc);

  return TRUE;
}

/* end of file SUBSOLIDUSMUO2.C */
