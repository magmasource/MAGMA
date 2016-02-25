const char *test_a_x_relations_ver(void) { return "$Id: test_a-x_relations.c,v 1.4 2008/09/18 16:17:17 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: test_a-x_relations.c,v $
MELTS Source Code: RCS Revision 1.3  2006/10/20 00:59:23  ghiorso
MELTS Source Code: RCS (1) Made initial modifications for thread safe code.
MELTS Source Code: RCS (2) Added support for XML I/O in batch mode
MELTS Source Code: RCS (3) Added support for Melts-batch listener for eventual integration into VIGMCS
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
MELTS Source Code: RCS Revision 1.2  2005/01/24 03:38:05  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added new files and modifications to perform builds for MgO-SiO2 system
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2003/05/07 04:39:09  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2002/04/16 04:34:43  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 3.7  1997/06/21  22:49:23  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.6  1997/05/03  20:23:03  ghiorso
 * *** empty log message ***
 *
 * Revision 3.5  1997/03/27  17:03:07  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1996/09/24  20:33:18  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.3  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.2  1995/11/01  22:40:27  ghiorso
 * Implementation of subsolidus options after Asimow.
 * Additional implementation of nepheline solid solutions.
 *
 * Revision 3.2  1995/11/01  22:40:27  ghiorso
 * Implementation of subsolidus options after Asimow.
 * Additional implementation of nepheline solid solutions.
 *
 * Revision 3.1  1995/08/18  19:16:12  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Test routine to evaluate the functions defined for the computation
**      of activity composition relations in the sol_struct_data file
**      (file: TEST_A-X_RELATIONS.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  May 9, 1991 Original Version
**      V1.0-2  Mark S. Ghiorso  August 26, 1991
**              Added test for (*convert) (mask == THIRD)
**      V1.0-3  Mark S. Ghiorso  September 14, 1991
**              Revised call to (*solids[].convert) to reflect new
**              parameter list
**      V1.0-4  Mark S. Ghiorso  September 16, 1991
**              Inserted test calls to (*solids[].convert) for new options
**      V1.0-5  Mark S. Ghiorso  September 25, 1991
**              (1) Altered parameter list to (*solids[].test) to reflect
**                  new bounds constraints options. Note that the bounds 
**                  algorithms are not tested for consistency but are 
**                  called to check on their existence.
**              (2) Altered parameter list to (*solids[].convert) to
**                  test new derivative dx/dr (d(mole fractions of end-
**                  member components)/d(independent compositional variables)
**      V1.0-6  Mark S. Ghiorso  March 28, 1992
**              Defined RAND_MAX for non-ANSI implementations (SparcStation)
**      V2.0-1  Mark S. Ghiorso  May 10, 1994
**              (1) Added modifications to test new derivatives for 
**                  isenthalpic, isentropic and isochoric mode
**      V2.0-2  Mark S. Ghiorso  May 17, 1994
**              (1) Corrected test on the enthalpy
**      V2.0-3  Mark S. Ghiorso  March 21, 1995
**              Corrected allocation violation for vtemp
**      V3.0-1  Paul D. Adimow  July 31, 1995
**              (1) Added test of d3rdm3 option to (*convert)
**              (2) Added test of d3gdr3 option to (*gmix)
**--
*/

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include "interface.h"
Widget main_window, silmin_adb, topLevel;
MeltsEnviron meltsEnviron;

#include "silmin.h"
#include "recipes.h"

#ifdef BUILD_MGO_SIO2_VERSION
#include "liq_struct_data_MgO_SiO2.h"
#include "sol_struct_data_MgO_SiO2.h"
#include "param_struct_data_MgO_SiO2.h"

#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
#include "liq_struct_data_SiO2_Al2O3_CaO_Na2O_K2O.h"
#include "sol_struct_data_SiO2_Al2O3_CaO_Na2O_K2O.h"
#include "param_struct_data_SiO2_Al2O3_CaO_Na2O_K2O.h"

#else
#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"
#endif

int calculationMode = MODE_DEFAULT;
SilminState *silminState;

#ifndef RAND_MAX
#define RAND_MAX INT_MAX         /* SparcStations don't define this macro */
#endif

#define TEST(x) \
   flag = ( ABS(temp - (x)) <= sqrt(sqrt(TAU))*ABS(x) ) \
   ? "OK " : "BAD"

int main()
{
   int n, i, j, k, l, NC, NX, doRandom=TRUE;
   char *flag;
   char **names, **formulas, *dispForm;
   double t = 1200.0 + 273.15;
   double p = 1000.0;
   double *moles, *x, *a, *mu, **dadx, g, *dgdx, **d2gdx2, h, s, *dsdx,
      **d2sdx2, cp, dcpdt, v, *dvdx, **d2vdx2, dvdt, dvdp, d2vdt2,
      d2vdtdp, d2vdp2, deltaT, deltaP, *deltaX, *deltaM, temp, *xtemp,
      *mtemp, mtotal, *vtemp, **drdm, **dtemp, ***d2rdm2, **dxdr,
      *dcpdx, *d2vdxdt, *d2vdxdp, ****d3rdm3, ***d3gdx3, ***d2temp,
      **v2temp;
   float ftemp;

  printf("---> Default calculation mode is xMELTS.  Change this? (y or n): ");
  if (tolower(getchar()) == 'y') {
    getchar();
    printf("     Set calculation mode is MELTS (public release v 3.0.x)? (y or n): ");
    if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE__MELTS; }
    else {
      getchar();
      printf("     Set calculation mode is pMELTS (public release v 4.0.x)? (y or n): ");
      if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE_pMELTS; }
    }
  } else getchar();
  
  if (calculationMode == MODE_xMELTS) {
    printf("---> Calculation mode is xMELTS (experimental v 5.0.x).\n");
  } else if (calculationMode == MODE__MELTS) {
    printf("---> Calculation mode is MELTS (public release v 3.0.x).\n");
    liquid = meltsLiquid;
    solids = meltsSolids;
    nlc = meltsNlc;
    nls = meltsNls;
    npc = meltsNpc;
  } else if (calculationMode == MODE_pMELTS) {
    printf("---> Calculation mode is pMELTS (public release v 4.0.x).\n");
    liquid = pMeltsLiquid;
    solids = pMeltsSolids;
    nlc = pMeltsNlc;
    nls = pMeltsNls;
    npc = pMeltsNpc;
  }

   printf("Input test compositions (y or n)? ");
   if (tolower(getchar()) == 'y') doRandom = FALSE;
   getchar();

   printf("Do calculations at %7.2f C (y or n)? ", t-273.15);
   if (tolower(getchar()) != 'y') {
     getchar();
     printf("Input a temperature in (C):"); scanf("%f", &ftemp); t = ((double) ftemp) +273.15;
     getchar();
   } else getchar();
   
   printf("Do calculations at %7.2f bars (y or n)? ", p);
   if (tolower(getchar()) != 'y') {
     getchar();
     printf("Input a pressure in (bars):"); scanf("%f", &ftemp); p = (double) ftemp;
     getchar();
   } else getchar();

   printf("*******************************************************\n");
   printf("* Calculations at %7.2f (C) and %8.2f (bars) *\n", t-273.15, p);
   printf("*******************************************************\n\n");

   /**************************************************************************
    Compute constants for numerical differentiation                        
    **************************************************************************/
   
   deltaT = sqrt(TAU)*(1.0+ABS(t));
   deltaP = sqrt(TAU)*(1.0+ABS(p));

   /**************************************************************************
    Evaluate activity-composition relations for all solid phases          
    **************************************************************************/

   for (n=0; n<npc; n++) {
      if (solids[n].type == PHASE && solids[n].activity != NULL) {

         printf("Evaluate code for %s (y or n)? ", solids[n].label);
         if (tolower(getchar()) != 'y') { getchar(); continue; }
         getchar();

         for (i=n+1; solids[i].type == COMPONENT && i<npc; i++)
	   ; 
	 i--;

         NC =  i - n;   /* Number of end-member components in solid solution */
         NX = NC - 1;   /* Number of independent compositional variables     */

         /********************************************************************
          Allocate space for required vectors and matrices                 
          ********************************************************************/
         
         moles   = vector(0, NC-1);
         mtemp   = vector(0, NC-1);
         x       = vector(0, NX-1);
         xtemp   = vector(0, NX-1);
         vtemp   = vector(0, NC-1);
         deltaM  = vector(0, NC-1);
         deltaX  = vector(0, NX-1);
         a       = vector(0, NC-1);
         mu      = vector(0, NC-1);
         dgdx    = vector(0, NX-1);
         dsdx    = vector(0, NX-1);
         dvdx    = vector(0, NX-1);
         dcpdx   = vector(0, NX-1);
         d2vdxdt = vector(0, NX-1);
         d2vdxdp = vector(0, NX-1);

         drdm   = matrix(0, NX-1, 0, NC-1);
         dxdr   = matrix(0, NC-1, 0, NX-1);
         dtemp  = matrix(0, NX-1, 0, NC-1);
         dadx   = matrix(0, NC-1, 0, NX-1);
         d2gdx2 = matrix(0, NX-1, 0, NX-1);
         d2sdx2 = matrix(0, NX-1, 0, NX-1);
         d2vdx2 = matrix(0, NX-1, 0, NX-1);
         v2temp = matrix(0, NX-1, 0, NX-1);

         d2rdm2 = (double ***) malloc((unsigned) NX*sizeof(double **));
         for (i=0; i<NX; i++) d2rdm2[i] = matrix(0, NC-1, 0, NC-1);
         d2temp = (double ***) malloc((unsigned) NX*sizeof(double **));
         for (i=0; i<NX; i++) d2temp[i] = matrix(0, NC-1, 0, NC-1);

         d3rdm3 = (double ****) malloc((unsigned) NX*sizeof(double ***));
         for (i=0; i<NX; i++) {
           d3rdm3[i] = (double ***) malloc((unsigned) NC*sizeof(double **));
           for (j=0; j<NC; j++) d3rdm3[i][j] = matrix(0, NC-1, 0, NC-1);
         }

         d3gdx3 = (double ***) malloc((unsigned) NX*sizeof(double **));
         for (i=0; i<NX; i++) d3gdx3[i] = matrix(0, NX-1, 0, NX-1);

         names    = (char **) malloc((unsigned) NC*sizeof(char *));
         formulas = (char **) malloc((unsigned) NC*sizeof(char *));
         for (i=0; i<NC; i++) {
           names[i]    = (char *) malloc((unsigned) 
                         (strlen(solids[n+1+i].label)+1)*sizeof(char));
           formulas[i] = (char *) malloc((unsigned) 
                         (strlen(solids[n+1+i].formula)+1)*sizeof(char));
         }

         /********************************************************************
          Test internal consistency of SOL_STRUCT_DATA.H include file
          and conventions adopted in coding the routine. Do not check bounds
          constraints, since there is no a priori way of knowing what they 
          may be.
          ********************************************************************/

         for (i=0; i<NC; i++) {
           names[i]    = strcpy(names[i], solids[n+1+i].label);
           formulas[i] = strcpy(formulas[i], solids[n+1+i].formula);
         }
         if (!(*solids[n].test)(FIRST | SECOND | THIRD | FOURTH, t, p, 
           NC, NX, names, formulas, (double *) NULL, (double *) NULL)) exit(0);

         /******************************************************************** 
          Compute composition of the solid phase (moles) 
          ********************************************************************/

         if (doRandom) 
           for (i=0; i<NC; i++) moles[i] = ((double) rand())/((double) RAND_MAX);
         else {
           for (i=0; i<NC; i++) {
             printf("Input moles of %15.15s (%15.15s): ", names[i], formulas[i]);
             scanf("%f", &ftemp); moles[i] = (double) ftemp; getchar();
           }
         }
         for (i=0; i<NC; i++) deltaM[i] = sqrt(TAU)*(1.0+ABS(moles[i]));

         if (!(*solids[n].test)(SIXTH, t, p, 0, 0, NULL, NULL, NULL, moles)) printf(
           "BAD The moles vector apparently violates bound constraints.\n"); 

         /********************************************************************
          Transform mole vector into independent compositional variables
          and test back conversion algorithm
          ********************************************************************/

         /* Convert moles of endmembers to independent compositional variables
            and mole fractions of endmembers. Get derivatives of the indepen-
            dent compositional variables with respect to moles of endmembers  */

         (*solids[n].convert)(SECOND, THIRD | FOURTH | FIFTH | SIXTH | EIGHTH,
           t, p, (double *) NULL, moles, x, mtemp, drdm, d2rdm2,
           (double **) NULL, d3rdm3);
         for (i=0; i<NX; i++) deltaX[i] = sqrt(TAU)*(1.0+ABS(x[i]));

         if (!(*solids[n].test)(FIFTH, t, p, 0, 0, NULL, NULL, x, NULL)) printf(
           "BAD The r vector apparently violates bound constraints.\n"); 

         /* Output moles and independent compositional variables */
         for (i=0; i<NC; i++) {
           printf("    moles[%-15.15s] = %13.6g", solids[n+i+1].label, 
             moles[i]);
           if (i < NX) printf("    r[%3d] = %13.6g\n", i, x[i]);
           else        printf("\n");
         }
         printf("\n");

         /* Output formula of the solid phase */
         (*solids[n].display)(FIRST, t, p, x, &dispForm);
         printf("    formula %s\n", dispForm); free(dispForm);
         printf("\n");

         /* Calculate total moles */
         for (i=0, mtotal=0.0; i<NC; i++) mtotal += moles[i];

         /* Check calculated mole fractions for internal consistency */
         for (i=0; i<NC; i++) {
            temp = mtemp[i];
            TEST(moles[i]/mtotal);
            printf("%s X[%s] = %g (%g, %s)\n", flag, solids[n+i+1].label,
               moles[i]/mtotal, temp, "from convert SECOND->FOURTH");
         }
         printf("\n");

         /* print and test drdm[] */
         for (i=0; i<NC; i++) {
           for (j=0; j<NC; j++) mtemp[j] = moles[j];
           mtemp[i] += deltaM[i];
           (*solids[n].convert)(SECOND, THIRD, t, p, (double *) NULL, mtemp, 
             xtemp, (double *) NULL, (double **) NULL, (double ***) NULL,
             (double **) NULL, (double ****) NULL);
           for (j=0; j<NX; j++) {
             temp = (xtemp[j]-x[j])/deltaM[i];
             TEST(drdm[j][i]);
             printf("%s drdm[%d][%d] = %g (%g, %s)\n", flag, j, i, drdm[j][i],
               temp, "from r");
           }
         }
         printf("\n");

         /* print and test d2rdm2[][][] */
         for (i=0; i<NC; i++) {
           for (j=0; j<NC; j++) {
             for (k=0; k<NC; k++) mtemp[k] = moles[k];
             mtemp[j] += deltaM[j];
             (*solids[n].convert)(SECOND, FIFTH, t, p, (double *) NULL, mtemp,
               (double *) NULL, (double *) NULL, dtemp, (double ***) NULL,
               (double **) NULL, (double ****) NULL);
             for (k=0; k<NX; k++) {
               temp = (dtemp[k][i]-drdm[k][i])/deltaM[j];
               TEST(d2rdm2[k][i][j]);
               printf("%s d2rdm2[%d][%d][%d] = %g (%g, %s)\n", flag, k, i, j,
                 d2rdm2[k][i][j], temp, "from drdm[][]");
             }
           }
         }
         printf("\n");

         /* print and test d3rdm3[][][] */
         for (i=0; i<NC; i++) {
           for (j=0; j<NC; j++) {
             for (k=0; k<NC; k++) {
               for (l=0; l<NC; l++)  mtemp[l] = moles[l];
               mtemp[k] += deltaM[k];
               (*solids[n].convert)(SECOND, SIXTH, t, p, (double *) NULL, mtemp,
                 (double *) NULL, (double *) NULL, (double **) NULL, d2temp,
                 (double **) NULL, (double ****) NULL);
               for (l=0; l<NX; l++) {
                 temp = (d2temp[l][i][j]-d2rdm2[l][i][j])/deltaM[k];
                 TEST(d3rdm3[l][i][j][k]);
                 printf("%s d3rdm3[%d][%d][%d][%d] = %g (%g, %s)\n", flag, l, i, j,
                   k, d3rdm3[l][i][j][k], temp, "from d2rdm2[][]");
               }
             }
           }
         }
         printf("\n");

         /* Convert independent compositional variables into mole fractions 
            and obtain derivatives of the mole fractions with respect to r    */
         (*solids[n].convert)(THIRD, FOURTH | SEVENTH, t, p, (double *) NULL,
           (double *) NULL, x, mtemp, (double **) NULL, (double ***) NULL,
           dxdr, (double ****) NULL);

         /* Check calculated mole fractions for internal consistency */
         for (i=0; i<NC; i++) {
            temp = mtemp[i];
            TEST(moles[i]/mtotal);
            printf("%s X[%s] = %g (%g, %s)\n", flag, solids[n+i+1].label, 
               moles[i]/mtotal, temp, "from convert THIRD->FOURTH");
         }
         printf("\n");

         /* print and test dxdr[] */
         for (i=0; i<NX; i++) {
           for (j=0; j<NX; j++) xtemp[j] = x[j];
           xtemp[i] += deltaX[i];
           (*solids[n].convert)(THIRD, FOURTH, t, p, (double *) NULL, 
             (double *) NULL, xtemp, mtemp, (double **) NULL, 
             (double ***) NULL, (double **) NULL, (double ****) NULL);
           for (j=0; j<NC; j++) {
             temp = (mtemp[j]-moles[j]/mtotal)/deltaX[i];
             TEST(dxdr[j][i]);
             printf("%s dxdr[%d][%d] = %g (%g, %s)\n", flag, j, i, dxdr[j][i],
               temp, "from X");
           }
         }
         printf("\n");

         /********************************************************************
          Evaluate Gibbs energy of mixing and its derivatives
          ********************************************************************/

         (*solids[n].gmix)(FIRST | SECOND | THIRD | FOURTH, t, p, x,
             &g, dgdx, d2gdx2, d3gdx3);
         printf("    g = %g\n", g); 

         /* print and test dgdx[] */
         for (i=0; i<NX; i++) {
            for (j=0; j<NX; j++) xtemp[j] = x[j];
            xtemp[i] += deltaX[i];
            (*solids[n].gmix)(FIRST, t, p, xtemp, &temp, (double *) NULL, 
               (double **) NULL, (double ***) NULL);
            temp = (temp-g)/deltaX[i];
            TEST(dgdx[i]);
            printf("%s dgdx[%d] = %g (%g, %s)\n", flag, i, dgdx[i], temp,
               "from g");
         } 

         /* print and test d2gdx2[][] */
         for (i=0; i<NX; i++) {
            for (j=0; j<NX; j++) {
               for (k=0; k<NX; k++) xtemp[k] = x[k];
               xtemp[j] += deltaX[j];
               (*solids[n].gmix)(SECOND, t, p, xtemp, (double *) NULL, vtemp,
                  (double **) NULL, (double ***) NULL);
               temp = (vtemp[i]-dgdx[i])/deltaX[j];
               TEST(d2gdx2[i][j]);
               printf("%s d2gdx2[%d][%d] = %g (%g, %s)\n", flag, i, j, 
                  d2gdx2[i][j], temp, "from dgdx[]");
            }
         }
         printf("\n");

         /* print and test d3gdx3[][][] */
         for (i=0; i<NX; i++) {
            for (j=0; j<NX; j++) {
               for (k=0; k<NX; k++) {
                 for (l=0; l<NX; l++)  xtemp[l] = x[l];
                 xtemp[k] += deltaX[k];
                 (*solids[n].gmix)(THIRD, t, p, xtemp, (double *) NULL,
                    (double *) NULL, v2temp, (double ***) NULL);
                 temp = (v2temp[i][j]-d2gdx2[i][j])/deltaX[k];
                 TEST(d3gdx3[i][j][k]);
                 printf("%s d3gdx3[%d][%d][%d] = %g (%g, %s)\n", flag, i, j,
                  k, d3gdx3[i][j][k], temp, "from d2gdx2[]");
               }
            }
         }
         printf("\n");

         /********************************************************************
          Evaluate activity routines
          ********************************************************************/

         (*solids[n].activity)(FIRST | SECOND | THIRD, t, p, x, a, mu, dadx);

         for (i=0; i<NC; i++) {
            for (j=0; j<NC; j++) mtemp[j] = moles[j];
            mtemp[i] += deltaM[i];
            for (j=0, mtotal=0.0; j<NC; j++) mtotal += mtemp[j];
            (*solids[n].convert)(SECOND, THIRD, t, p, (double *) NULL, mtemp, 
              xtemp, (double *) NULL, (double **) NULL, (double ***) NULL,
              (double **) NULL, (double ****) NULL);
            (*solids[n].gmix)(FIRST, t, p, xtemp, &temp, (double *) NULL, 
               (double **) NULL, (double ***) NULL);
            temp = mtotal*((temp-g)/deltaM[i]) + (g+temp)/2.0;
            temp = exp(temp/(8.3143*t));
            TEST(a[i]);
            printf("%s a[%s] = %g (%g, %s)\n", flag, solids[n+i+1].label, a[i],
               temp, "from g");
         }

         /* print and test chemical potentials */
         for (i=0; i<NC; i++) {
            temp = 8.3143*t*log(a[i]);
            TEST(mu[i]);
            printf("%s (mu-mu0)[%s] = %g (%g, %s)\n", flag, 
               solids[n+i+1].label, mu[i], temp, "from a[]");
         }

         /* print and test dadx[][] */
         for (i=0; i<NC; i++) {
            for (j=0; j<NX; j++) {
               for (k=0; k<NX; k++) xtemp[k] = x[k];
               xtemp[j] += deltaX[j];
               (*solids[n].activity)(FIRST, t, p, xtemp, vtemp, 
                  (double *) NULL, (double **) NULL);
               temp = (vtemp[i]-a[i])/deltaX[j];
               TEST(dadx[i][j]);
               printf("%s dadx[%s][%d] = %g (%g, %s)\n", flag, 
                  solids[n+i+1].label, j, dadx[i][j], temp, "from a[]");
            }
         }
         printf("\n");

         /********************************************************************
          Evaluate entropy of mixing and its derivatives
          ********************************************************************/

         (*solids[n].smix)(FIRST | SECOND | THIRD, t, p, x, &s, dsdx, d2sdx2);

         /* print and test s */
         (*solids[n].gmix)(FIRST, t+deltaT, p, x, &temp, (double *) NULL, 
            (double **) NULL, (double ***) NULL);
         temp = -(temp-g)/deltaT;
         TEST(s);
         printf("%s s = %g (%g, %s)\n", flag, s, temp, "from g"); 

         /* print and test dsdx[] */
         for (i=0; i<NX; i++) {
            for (j=0; j<NX; j++) xtemp[j] = x[j];
            xtemp[i] += deltaX[i];
            (*solids[n].smix)(FIRST, t, p, xtemp, &temp, (double *) NULL, 
               (double **) NULL);
            temp = (temp-s)/deltaX[i];
            TEST(dsdx[i]);
            printf("%s dsdx[%d] = %g (%g, %s)\n",flag, i, dsdx[i], temp,
               "from s");
         }
 
         /* print and test d2ddx2[][] */
         for (i=0; i<NX; i++) {
            for (j=0; j<NX; j++) {
               for (k=0; k<NX; k++) xtemp[k] = x[k];
               xtemp[j] += deltaX[j];
               (*solids[n].smix)(SECOND, t, p, xtemp, (double *) NULL, vtemp,
                  (double **) NULL);
               temp = (vtemp[i]-dsdx[i])/deltaX[j];
               TEST(d2sdx2[i][j]);
               printf("%s d2sdx2[%d][%d] = %g (%g, %s)\n", flag, i, j, 
                  d2sdx2[i][j], temp, "from dsdx[]");
            }
         }
         printf("\n");

         /********************************************************************
          Evaluate heat capacity of mixing and its derivatives
          ********************************************************************/

         (*solids[n].cpmix)(FIRST | SECOND | THIRD, t, p, x, &cp, &dcpdt,
           dcpdx);

         /* print and test cp */
         (*solids[n].smix)(FIRST, t+deltaT, p, x, &temp, (double *) NULL, 
            (double **) NULL);
         temp = t*(temp-s)/deltaT;
         TEST(cp);
         printf("%s cp = %g (%g, %s)\n", flag, cp, temp, "from s");

         /* print and test dcpdt */
         (*solids[n].cpmix)(FIRST, t+deltaT, p, x, &temp, (double *) NULL,
           (double *) NULL);
         temp = (temp-cp)/deltaT;
         TEST(dcpdt);
         printf("%s dcpdt = %g (%g, %s)\n", flag, dcpdt, temp, "from cp");

         /* print and test dcpdx[] */
         for (i=0; i<NX; i++) {
            for (j=0; j<NX; j++) xtemp[j] = x[j];
            xtemp[i] += deltaX[i];
            (*solids[n].cpmix)(FIRST, t, p, xtemp, &temp, (double *) NULL, 
               (double *) NULL);
            temp = (temp-cp)/deltaX[i];
            TEST(dcpdx[i]);
            printf("%s dcpdx[%d] = %g (%g, %s)\n",flag, i, dcpdx[i], temp,
               "from cp");
         }
         printf("\n");

         /********************************************************************
          Evaluate volume of mixing and its derivatives
          ********************************************************************/

         (*solids[n].vmix)(
            FIRST | SECOND | THIRD | FOURTH | FIFTH | SIXTH | SEVENTH |EIGHTH
            | NINTH | TENTH, t, p, x, &v, dvdx, d2vdx2, &dvdt, &dvdp, &d2vdt2,
            &d2vdtdp, &d2vdp2, d2vdxdt, d2vdxdp);

         /* print and test v */
         (*solids[n].gmix)(FIRST, t, p+deltaP, x, &temp, (double *) NULL, 
            (double **) NULL, (double ***) NULL);
         temp = (temp-g)/deltaP;
         flag = ( ABS(temp - v) <= sqrt(TAU)*ABS(g) ) ? "OK " : "BAD";
         printf("%s v = %g (%g, %s)\n", flag, v, temp, "from g"); 

         /* print and test dvdx[] */
         for (i=0; i<NX; i++) { 
            for (j=0; j<NX; j++) xtemp[j] = x[j];
            xtemp[i] += deltaX[i];
            (*solids[n].vmix)(FIRST, t, p, xtemp, &temp, (double *) NULL, 
               (double **) NULL, (double *) NULL, (double *) NULL, 
               (double *) NULL, (double *) NULL, (double *) NULL,
               (double *) NULL, (double *) NULL);
            temp = (temp-v)/deltaX[i];
            TEST(dvdx[i]);
            printf("%s dvdx[%d] = %g (%g, %s)\n", flag, i, dvdx[i], temp,
               "from v");
         }
 
         /* print and test d2vdx2[][] */
         for (i=0; i<NX; i++) {
            for (j=0; j<NX; j++) { 
               for (k=0; k<NX; k++) xtemp[k] = x[k];
               xtemp[j] += deltaX[j];
               (*solids[n].vmix)(SECOND, t, p, xtemp, (double *) NULL, vtemp,
                  (double **) NULL, (double *) NULL, (double *) NULL, 
                  (double *) NULL, (double *) NULL, (double *) NULL,
                  (double *) NULL, (double *) NULL);
               temp = (vtemp[i]-dvdx[i])/deltaX[j];
               TEST(d2vdx2[i][j]);
               printf("%s d2vdx2[%d][%d] = %g (%g, %s)\n", flag, i, j, 
                  d2vdx2[i][j], temp, "from dvdx[]");
            }
         }

         /* print and test dvdt */
         (*solids[n].vmix)(FIRST, t+deltaT, p, x, &temp, (double *) NULL, 
            (double **) NULL, (double *) NULL, (double *) NULL, 
            (double *) NULL, (double *) NULL, (double *) NULL,
            (double *) NULL, (double *) NULL);
         temp = (temp-v)/deltaT;
         TEST(dvdt);
         printf("%s dvdt = %g (%g, %s)\n", flag, dvdt, temp, "from v");
 
         /* print and test dvdp */
         (*solids[n].vmix)(FIRST, t, p+deltaP, x, &temp, (double *) NULL, 
            (double **) NULL, (double *) NULL, (double *) NULL, 
            (double *) NULL, (double *) NULL, (double *) NULL,
            (double *) NULL, (double *) NULL);
         temp = (temp-v)/deltaP;
         TEST(dvdp);
         printf("%s dvdp = %g (%g, %s)\n", flag, dvdp, temp, "from v"); 

         /* print and test d2vdt2 */
         (*solids[n].vmix)(FOURTH, t+deltaT, p, x, (double *) NULL, 
            (double *) NULL, (double **) NULL, &temp, (double *) NULL, 
            (double *) NULL, (double *) NULL, (double *) NULL,
            (double *) NULL, (double *) NULL);
         temp = (temp-dvdt)/deltaT;
         TEST(d2vdt2);
         printf("%s d2vdt2 = %g (%g, %s)\n", flag, d2vdt2, temp, "from dvdt"); 

         /* print and test d2vdtdp */
         (*solids[n].vmix)(FOURTH, t, p+deltaP, x, (double *) NULL, 
            (double *) NULL, (double **) NULL, &temp, (double *) NULL,
            (double *) NULL, (double *) NULL, (double *) NULL,
            (double *) NULL, (double *) NULL);
         temp = (temp-dvdt)/deltaP;
         TEST(d2vdtdp);
         printf("%s d2vdtdp = %g (%g, %s)\n", flag, d2vdtdp, temp, 
            "from dvdt"); 

         /* print and test d2vdtdp */
         (*solids[n].vmix)(FIFTH, t+deltaT, p, x, (double *) NULL, 
            (double *) NULL, (double **) NULL, (double *) NULL, &temp, 
            (double *) NULL, (double *) NULL, (double *) NULL,
            (double *) NULL, (double *) NULL);
         temp = (temp-dvdp)/deltaT;
         TEST(d2vdtdp);
         printf("%s d2vdtdp = %g (%g, %s)\n", flag, d2vdtdp, temp, 
            "from dvdp"); 

         /* print and test d2vdp2 */
         (*solids[n].vmix)(FIFTH, t, p+deltaP, x, (double *) NULL, 
            (double *) NULL, (double **) NULL, (double *) NULL, &temp, 
            (double *) NULL, (double *) NULL, (double *) NULL,
            (double *) NULL, (double *) NULL);
         temp = (temp-dvdp)/deltaP;
         TEST(d2vdp2);
         printf("%s d2vdp2 = %g (%g, %s)\n", flag, d2vdp2, temp, "from dvdp"); 

         /* print and test d2vdxdt[] */
         for (i=0; i<NX; i++) { 
            for (j=0; j<NX; j++) xtemp[j] = x[j];
            xtemp[i] += deltaX[i];
            (*solids[n].vmix)(FOURTH, t, p, xtemp, (double *) NULL, 
               (double *) NULL, (double **) NULL, &temp, (double *) NULL, 
               (double *) NULL, (double *) NULL, (double *) NULL, 
               (double *) NULL, (double *) NULL);
            temp = (temp-dvdt)/deltaX[i];
            TEST(d2vdxdt[i]);
            printf("%s d2vdxdt[%d] = %g (%g, %s)\n", flag, i, d2vdxdt[i], temp,
               "from dvdt");
         }

         /* print and test d2vdxdp[] */
         for (i=0; i<NX; i++) { 
            for (j=0; j<NX; j++) xtemp[j] = x[j];
            xtemp[i] += deltaX[i];
            (*solids[n].vmix)(FIFTH, t, p, xtemp, (double *) NULL, 
               (double *) NULL, (double **) NULL, (double *) NULL, &temp, 
               (double *) NULL, (double *) NULL, (double *) NULL, 
               (double *) NULL, (double *) NULL);
            temp = (temp-dvdp)/deltaX[i];
            TEST(d2vdxdp[i]);
            printf("%s d2vdxdp[%d] = %g (%g, %s)\n", flag, i, d2vdxdp[i], temp,
               "from dvdp");
         }
         printf("\n");

         /********************************************************************
          Evaluate enthalpy of mixing
          ********************************************************************/

         (*solids[n].hmix)(FIRST, t, p, x, &h);

         /* print and test h */
         temp = g + t*s;
         TEST(h);
         printf("%s h = %g (%g, %s)\n", flag, h, temp, "from g and s"); 
         printf("\n");

         /******************************************************************** 
          Destroy space allocated for vectors and matrices                 
          ********************************************************************/

         free_vector(  moles, 0, NC-1);
         free_vector(  mtemp, 0, NC-1);
         free_vector(      x, 0, NX-1);
         free_vector(  xtemp, 0, NX-1);
         free_vector(  vtemp, 0, NC-1);
         free_vector( deltaM, 0, NC-1);
         free_vector( deltaX, 0, NX-1);
         free_vector(      a, 0, NC-1);
         free_vector(     mu, 0, NC-1);
         free_vector(   dgdx, 0, NX-1);
         free_vector(   dsdx, 0, NX-1);
         free_vector(   dvdx, 0, NX-1);
         free_vector(  dcpdx, 0, NX-1);
         free_vector(d2vdxdt, 0, NX-1);
         free_vector(d2vdxdp, 0, NX-1);

         free_matrix(  drdm, 0, NX-1, 0, NC-1);
         free_matrix(  dxdr, 0, NC-1, 0, NX-1);
         free_matrix( dtemp, 0, NX-1, 0, NC-1);
         free_matrix(  dadx, 0, NC-1, 0, NX-1);
         free_matrix(d2gdx2, 0, NX-1, 0, NX-1);
         free_matrix(d2sdx2, 0, NX-1, 0, NX-1);
         free_matrix(d2vdx2, 0, NX-1, 0, NX-1);
         free_matrix(v2temp, 0, NX-1, 0, NX-1);

         for (i=0; i<NX; i++) free_matrix(d2rdm2[i], 0, NC-1, 0, NC-1);
         free(d2rdm2);
         for (i=0; i<NX; i++) free_matrix(d2temp[i], 0, NC-1, 0, NC-1);
         free(d2temp);
         for (i=0; i<NX; i++) free_matrix(d3gdx3[i], 0, NX-1, 0, NX-1);
         free(d3gdx3);
         for (i=0; i<NX; i++) {
            for (j=0; j<NC; j++) free_matrix(d3rdm3[i][j],0,NC-1,0,NC-1);
            free(d3rdm3[i]);
         }
         free(d3rdm3);

         for (i=0; i<NC; i++) {free(names[i]); free(formulas[i]);}
         free(names);
         free(formulas);
      }
   }
   return 0;
}

/* End file: TEST_A-X_RELATIONS.C */
