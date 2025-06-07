const char *test_speciation_ver(void) { return "$Id: test_speciation.c,v 1.4 2008/09/18 16:17:17 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: test_speciation.c,v $
MELTS Source Code: RCS Revision 1.3  2007/06/08 17:25:43  ghiorso
MELTS Source Code: RCS Added code to allow regression of Ghiorso EOS parameters
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
MELTS Source Code: RCS Revision 1.8  2005/02/04 14:48:54  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.7  2005/01/25 03:25:03  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.6  2005/01/24 03:38:05  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added new files and modifications to perform builds for MgO-SiO2 system
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2004/11/21 21:50:11  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2004/11/21 21:42:30  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2004/11/21 21:34:28  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2004/11/21 16:25:32  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1  2004/11/17 03:44:19  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      (file: TEST_SPECIATION.C)
**
**  MODIFICATION HISTORY:
**
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

SilminState *silminState;
int calculationMode = MODE_DEFAULT;

#define NO_INPUT_COMPOSITION

static double computeTFus(int index, double t, double p, double *x) {
  static double *mu;
  double deltaT;
  int first = 1, iter=0;
  if (mu == NULL) mu = vector(0, nlc-1);
  
  do {
    double f, dG, tOld, fOld;
    int i;
    gibbs(t, p, (char *) solids[index].label, &(solids[index].ref), NULL, NULL, &(solids[index].cur));
    dG = -(solids[index].cur).g;  
    actLiq(SECOND, t, p, x, NULL, mu, NULL, NULL);
    for (i=0; i<nlc; i++) if ((solids[index].solToLiq)[i] != 0.0) dG += (solids[index].solToLiq)[i]*mu[i];
    f = dG*dG;
    
    if (first) {
      first = 0;
      tOld  = t;
      fOld  = f;
      t    += 20.0;
    } else {
      double dfdt = (f - fOld)/(t-tOld);
      tOld = t;
      fOld = f;
      t -= f/dfdt;
      if (t < 1500) t = 1500.0;
      if (t > 3300) t = 3300.0;
    }
    deltaT = t - tOld;
    iter++;
    
    /* printf("iter = %d t = %g deltaT = %g f = %g dG = %g\n", iter, t, deltaT, f, dG); */
  } while ((iter < 100) && (fabs(deltaT) > 0.005));
       
  return t;
}

int main()
{
   int i, first = 1;
   int nr = nlc - 1;
   double t = 2273.15;
   double p = 1.0;
   double *moles, *moles1, *moles2, *x, *mu, g, h, s, cp, dcpdt, v, dvdt, dvdp, d2vdt2, d2vdtdp, d2vdp2, *xSpecies, *xCN;
   double **d2gdr2, tFusPer, tFusFo, tFusCr, tFusPen;
   float ftemp;
   FILE *output, *outPer, *outCr, *outFo, *outPen;
   int iPericlase = -1, iForsterite = -1, iCristobalite = -1, iProtoenstatite = -1;
  
   moles    = vector(0, nlc-1);
   moles1   = vector(0, nlc-1);
   moles2   = vector(0, nlc-1);
   x        = vector(0, nr-1);
   mu       = vector(0, nlc-1);
   xSpecies = vector(0, nls-1);
   xCN      = vector(0, nCN-1);
   
   d2gdr2   = matrix(0, nr-1, 0, nr-1);

   printf("***************************************************\n");
   printf("%s\n", test_speciation_ver());
   printf("***************************************************\n\n");
   printf("***************************************************\n");
   printf("Calling function: InitComputeDataStruct().         \n");
   printf("***************************************************\n\n");
   InitComputeDataStruct();
   setModeToMixingLiq(FALSE);

  printf("Opening output files...\n");
  output = fopen ("system.dat",  "w");
  outPer = fopen ("tFusPer.dat", "w");
  outCr  = fopen ("tFusCr.dat",  "w");
  outFo  = fopen ("tFusFo.dat",  "w");
  outPen = fopen ("tFusPen.dat", "w");
        
   printf("Do calculations at %7.2f C (y or n)? ", t-273.15);
   if (tolower(getchar()) != 'y') {
     getchar(); printf("Input a temperature in (C):"); scanf("%f", &ftemp); t = ((double) ftemp)+273.15; getchar();
   } else getchar();
   
   printf("Do calculations at %7.2f bars (y or n)? ", p);
   if (tolower(getchar()) != 'y') {
     getchar(); printf("Input a pressure in (bars):"); scanf("%f", &ftemp); p = (double) ftemp; getchar();
   } else getchar();

   printf("*******************************************************\n");
   printf("* Calculations at %7.2f (C) and %8.2f (bars) *\n", t-273.15, p);
   printf("*******************************************************\n\n");

#ifdef INPUT_COMPOSITION

   for (i=0; i<nlc; i++) {
      printf("Input moles of %15.15s (liquid 1): ", liquid[i].label);
      scanf("%f", &ftemp); moles1[i] = (double) ftemp; getchar();
   }
   for (i=0; i<nlc; i++) {
      printf("Input moles of %15.15s (liquid 2): ", liquid[i].label);
      scanf("%f", &ftemp); moles2[i] = (double) ftemp; getchar();
   }

#else

#ifdef BUILD_MGO_SIO2_VERSION
   moles1[ 0] =  0.0;  moles2[ 0] =  1.0; /* SiO2    */ 
   moles1[ 1] =  1.0;  moles2[ 1] =  0.0; /* MgO     */ 
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
   moles1[ 0] =  0.0;  moles2[ 0] =  1.0; /* SiO2    */ 
   moles1[ 1] =  0.0;  moles2[ 1] =  0.0; /* Al2O3   */ 
   moles1[ 2] =  1.0;  moles2[ 2] =  0.0; /* CaO     */ 
   moles1[ 3] =  0.0;  moles2[ 3] =  0.0; /* Na2O    */ 
   moles1[ 4] =  0.0;  moles2[ 4] =  0.0; /* K2O     */ 
#else
   moles1[ 0] =  0.0;  moles2[ 0] =  1.0; /* SiO2    */ 
   moles1[ 1] =  0.0;  moles2[ 1] =  0.0; /* TiO2    */ 
   moles1[ 2] =  0.0;  moles2[ 2] =  0.0; /* Al2O3   */ 
   moles1[ 3] =  0.0;  moles2[ 3] =  0.0; /* Fe2O3   */ 
   moles1[ 4] =  0.0;  moles2[ 4] =  0.0; /* Cr2O3   */ 
   moles1[ 5] =  0.0;  moles2[ 5] =  0.0; /* FeO     */ 
   moles1[ 6] =  0.0;  moles2[ 6] =  0.0; /* MnO     */ 
   moles1[ 7] =  1.0;  moles2[ 7] =  0.0; /* MgO     */ 
   moles1[ 8] =  0.0;  moles2[ 8] =  0.0; /* NiO     */ 
   moles1[ 9] =  0.0;  moles2[ 9] =  0.0; /* CoO     */ 
   moles1[10] =  0.0;  moles2[10] =  0.0; /* CaO     */ 
   moles1[11] =  0.0;  moles2[11] =  0.0; /* Na2O    */ 
   moles1[12] =  0.0;  moles2[12] =  0.0; /* K2O     */ 
   moles1[13] =  0.0;  moles2[13] =  0.0; /* P2O5    */ 
   moles1[14] =  0.0;  moles2[14] =  0.0; /* CO2     */ 
   moles1[15] =  0.0;  moles2[15] =  0.0; /* SO3     */ 
   moles1[16] =  0.0;  moles2[16] =  0.0; /* Cl2O-1  */ 
   moles1[17] =  0.0;  moles2[17] =  0.0; /* F2O-1   */ 
   moles1[18] =  0.0;  moles2[18] =  0.0; /* H2O     */ 
#endif

#endif /* INPUT_COMPOSITION */

   for (i=0; i<npc; i++) {
     if      ( (solids[i].type == PHASE) && !strcmp(solids[i].label,"periclase")      ) iPericlase      = i; 
     else if ( (solids[i].type == PHASE) && !strcmp(solids[i].label,"forsterite")     ) iForsterite     = i; 
     else if ( (solids[i].type == PHASE) && !strcmp(solids[i].label,"cristobalite")   ) iCristobalite   = i; 
     else if ( (solids[i].type == PHASE) && !strcmp(solids[i].label,"protoenstatite") ) iProtoenstatite = i;
   }
   if (iPericlase      == -1) { printf("ERROR: Cannot find periclase in solids list.\n");      abort(); }
   if (iForsterite     == -1) { printf("ERROR: Cannot find forsterite in solids list.\n");     abort(); }
   if (iCristobalite   == -1) { printf("ERROR: Cannot find cristobalite in solids list.\n");   abort(); }
   if (iProtoenstatite == -1) { printf("ERROR: Cannot find protoenstatite in solids list.\n"); abort(); }
   
   gibbs(t, p, (char *) solids[iPericlase].label,      &(solids[iPericlase].ref),      NULL, NULL, &(solids[iPericlase].cur));
   gibbs(t, p, (char *) solids[iForsterite].label,     &(solids[iForsterite].ref),     NULL, NULL, &(solids[iForsterite].cur));
   gibbs(t, p, (char *) solids[iCristobalite].label,   &(solids[iCristobalite].ref),   NULL, NULL, &(solids[iCristobalite].cur));
   gibbs(t, p, (char *) solids[iProtoenstatite].label, &(solids[iProtoenstatite].ref), NULL, NULL, &(solids[iProtoenstatite].cur));

   for (i=1, tFusPer=t, tFusFo=t, tFusCr=t, tFusPen=t; i<100; i++) {
     double gFusPer, gFusFo, gFusCr, gFusPen;
     int j;
     for (j=0; j<nlc; j++) moles[j] = moles1[j]*(100.0 - (double) i)/100.0 + moles2[j]*((double) i)/100.0;
     
     conLiq(SECOND, THIRD, t, p, NULL, moles, x, NULL, NULL, NULL, NULL);
     conLiq(THIRD, FOURTH | EIGHTH, t, p, NULL, NULL, x, xSpecies, NULL, NULL, NULL);
     conLiq(THIRD, FOURTH | NINTH,  t, p, NULL, NULL, x, xCN,      NULL, NULL, NULL);

     gmixLiq(FIRST | THIRD, t, p, x, &g, NULL, d2gdr2);
     hmixLiq(FIRST, t, p, x, &h, NULL);
     smixLiq(FIRST, t, p, x, &s, NULL, NULL, NULL);
     cpmixLiq(FIRST | SECOND, t, p, x, &cp, &dcpdt, NULL);
     vmixLiq(FIRST | FOURTH | FIFTH | SIXTH | SEVENTH |EIGHTH, t, p, x, &v, NULL, NULL, 
           &dvdt, &dvdp, &d2vdt2, &d2vdtdp, &d2vdp2, NULL, NULL, NULL);
     actLiq(SECOND, t, p, x, NULL, mu, NULL, NULL);
     
     gFusPer = -(solids[iPericlase].cur).g;
     gFusFo  = -(solids[iForsterite].cur).g;
     gFusCr  = -(solids[iCristobalite].cur).g;
     gFusPen = -(solids[iProtoenstatite].cur).g;
     for (j=0; j<nlc; j++) {
       if ((solids[iPericlase].solToLiq)[j]      != 0.0) gFusPer += (solids[iPericlase].solToLiq)[j]     *mu[j];
       if ((solids[iForsterite].solToLiq)[j]     != 0.0) gFusFo  += (solids[iForsterite].solToLiq)[j]    *mu[j];
       if ((solids[iCristobalite].solToLiq)[j]   != 0.0) gFusCr  += (solids[iCristobalite].solToLiq)[j]  *mu[j];
       if ((solids[iProtoenstatite].solToLiq)[j] != 0.0) gFusPen += (solids[iProtoenstatite].solToLiq)[j]*mu[j];
     }

     if(first) {
       first = 0;
       printf(" %4.4s",   "x");
       printf(" %13.13s", "g");
       printf(" %13.13s", "h");
       printf(" %13.13s", "s");
       printf(" %13.13s", "cp");
       printf(" %13.13s", "dcpdt");
       printf(" %13.13s", "v");
       printf(" %13.13s", "dvdt");
       printf(" %13.13s", "dvdp");
       printf(" %13.13s", "d2vdt2");
       printf(" %13.13s", "d2vdtdp");
       printf(" %13.13s", "d2vdp2");
       
#ifdef BUILD_MGO_SIO2_VERSION
       printf(" %13.13s", "d2gdr2[0,0]");
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
       printf(" %13.13s", "d2gdr2[0,0]");
#else
       printf(" %13.13s", "d2gdr2[6,6]");
#endif
       
       for (j=0; j<nlc; j++) if (moles[j]    != 0.0) printf(" mu-%-10.10s", liquid[j].label);
       for (j=0; j<nls; j++) if (xSpecies[j] != 0.0) printf(" x-%-11.11s",  liquid[j].label);
       for (j=0; j<nCN; j++)                         printf(" CN-*");
       
       printf("\n");
     }
     
     tFusPer = computeTFus(iPericlase, t, p, x);
     printf("x = %g t fus Periclase = %g\n", ((double) i)/100.0, tFusPer);
     fprintf(outPer,"%13.6g %13.6g\n", ((double) i)/100.0, tFusPer);

     tFusCr = computeTFus(iCristobalite, t, p, x);
     printf("x = %g t fus Cristobalite = %g\n", ((double) i)/100.0, tFusCr);
     fprintf(outCr,"%13.6g %13.6g\n", ((double) i)/100.0, tFusCr);

     tFusFo = computeTFus(iForsterite, t, p, x);
     printf("x = %g t fus Forsterite = %g\n", ((double) i)/100.0, tFusFo);
     fprintf(outFo,"%13.6g %13.6g\n", ((double) i)/100.0, tFusFo);

     tFusPen = computeTFus(iProtoenstatite, t, p, x);
     printf("x = %g t fus Protoenstatite = %g\n", ((double) i)/100.0, tFusPen);
     fprintf(outPen,"%13.6g %13.6g\n", ((double) i)/100.0, tFusPen);
       
     printf(" %4.2f", ((double) i)/100.0);
     printf(" %13.6g", g/1000.0);
     printf(" %13.6g", h/1000.0);
     printf(" %13.6g", s);
     printf(" %13.6g", cp);
     printf(" %13.6g", dcpdt);
     printf(" %13.6g", v);
     printf(" %13.6g", dvdt);
     printf(" %13.6g", dvdp);
     printf(" %13.6g", d2vdt2);
     printf(" %13.6g", d2vdtdp);
     printf(" %13.6g", d2vdp2);

#ifdef BUILD_MGO_SIO2_VERSION
     printf(" %13.6g", d2gdr2[0][0]);
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
     printf(" %13.6g", d2gdr2[0][0]);
#else
     printf(" %13.6g", d2gdr2[6][6]);
#endif
     
     for (j=0; j<nlc; j++) if (moles[j]    != 0.0) printf(" %13.6g", mu[j]/1000.0);
     for (j=0; j<nls; j++) if (xSpecies[j] != 0.0) printf(" %13.6g", xSpecies[j]);
     for (j=0; j<nCN; j++)                         printf(" %13.6g", xCN[j]);

     printf(" %13.6g", gFusPer/1000.0);
     printf(" %13.6g", gFusFo/1000.0); 
     printf(" %13.6g", gFusCr/1000.0);
     printf(" %13.6g", gFusPen/1000.0);
     
     printf("\n");
     
     fprintf(output," %4.2f", ((double) i)/100.0);
     fprintf(output," %13.6g", g/1000.0);
     fprintf(output," %13.6g", h/1000.0);
     fprintf(output," %13.6g", s);
     fprintf(output," %13.6g", cp);
     fprintf(output," %13.6g", dcpdt);
     fprintf(output," %13.6g", v);
     fprintf(output," %13.6g", dvdt);
     fprintf(output," %13.6g", dvdp);
     fprintf(output," %13.6g", d2vdt2);
     fprintf(output," %13.6g", d2vdtdp);
     fprintf(output," %13.6g", d2vdp2);

#ifdef BUILD_MGO_SIO2_VERSION
     fprintf(output," %13.6g", d2gdr2[0][0]);
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
     fprintf(output," %13.6g", d2gdr2[0][0]);
#else
     fprintf(output," %13.6g", d2gdr2[6][6]);
#endif
     
     for (j=0; j<nlc; j++) if (moles[j]    != 0.0) fprintf(output," %13.6g", mu[j]/1000.0);
     for (j=0; j<nls; j++) if (xSpecies[j] != 0.0) fprintf(output," %13.6g", xSpecies[j]);
     for (j=0; j<nCN; j++)                         fprintf(output," %13.6g", xCN[j]);
     
     fprintf(output, " %13.6g", gFusPer/1000.0);
     fprintf(output, " %13.6g", gFusFo/1000.0); 
     fprintf(output, " %13.6g", gFusCr/1000.0);
     fprintf(output, " %13.6g", gFusPen/1000.0);
     
     fprintf(output, "\n");
   }

   free_vector(    moles, 0, nlc-1);
   free_vector(   moles1, 0, nlc-1);
   free_vector(   moles2, 0, nlc-1);
   free_vector(        x, 0, nr-1);
   free_vector(       mu, 0, nlc-1);
   free_vector( xSpecies, 0, nls-1);
   free_vector(      xCN, 0, nCN-1);
   
   free_matrix(   d2gdr2, 0, nr-1, 0, nr-1);

   fclose(output);
   return 0;
}

/* End file: TEST_SPECIATION.C */
