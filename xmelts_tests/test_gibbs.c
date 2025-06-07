const char *test_gibbs_ver(void) { return "$Id: test_gibbs.c,v 1.5 2008/09/18 16:17:17 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: test_gibbs.c,v $
MELTS Source Code: RCS Revision 1.4  2007/11/29 05:32:14  ghiorso
MELTS Source Code: RCS Majorite testMaj corrections.  Fixed "O2" in sol_struct_data.h to "o2".
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2007/05/30 15:39:03  ghiorso
MELTS Source Code: RCS Corrected problem with links to dynamic libraries in Melts-batch
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
MELTS Source Code: RCS Revision 1.3  2005/01/24 03:38:05  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added new files and modifications to perform builds for MgO-SiO2 system
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2004/10/02 19:41:47  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2003/06/24 16:42:42  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 3.6  1997/06/21  22:49:21  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.5  1997/05/03  20:23:01  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:06  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:33:17  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.1  1995/08/18  19:17:36  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  19:17:36  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Test routine to evaluate the function gibbs (file: TEST_GIBBS.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  May 6, 1991 Original Version
**      V2.0-1  Mark S. Ghiorso  May 4, 1992
**              Revised to output oxygen properties and a complete set
**              of thermodynamic properties for fusion reactions
**      V3.0-1  Mark S. Ghiorso  July 29, 1992
**              (1) Added calculation of entropies of fusion for selected
**                  compounds
**      V3.1-1  Mark S. Ghiorso  January 16, 1993
**              (1) Modified entropy of fusion code to extract entropies of
**                  mixing from smixLiq()
**      V3.1-2  Mark S. Ghiorso  July 11, 1994
**              (1) Moved call to InitComputeDataStruct() to top of program
**                  because of changes in O2 computations
**      V3.2-1  Mark S. Ghiorso  February 3, 1995
**              (1) Added a test for consistency of the temperature derivative
**                  of the entropy and the heat capacity
**--
*/

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

void *main_window, *silmin_adb, *topLevel, *meltsEnviron;
SilminState *silminState;

#define TEST(x) \
   flag = ( ABS(temp - (x)) <= sqrt(sqrt(TAU))*ABS(x) ) \
   ? "OK " : "BAD"

int main()
{
  int i, j, indFeO = -1, indFe2O3 = -1;
  double t = 1173.15;
  double p = 5000.00;
  double Dg, Dh, Ds, DCp, DdCpdT, Dv, DdVdT, DdVdP, Dd2VdT2, Dd2VdP2,
         Dd2VdTdP, deltaT, deltaP, temp, cpRef, gRef, sRef, vRef, hRef,
         dvdtRef, d2vdt2Ref, dcpdtRef, dvdpRef, d2vdp2Ref, d2vdtdpRef;
  float ftemp; 
  FILE *output;
  char *flag;

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
   
  deltaT = sqrt(TAU)*(1.0+ABS(t));
  deltaP = sqrt(TAU)*(1.0+ABS(p));

  printf("Opening output file TEST_GIBBS.OUT.\n");
  output = fopen ("test_gibbs.out", "w");

  printf("Calling function: InitComputeDataStruct().\n");
  InitComputeDataStruct();
  
  printf("Printing computed liquid properties to output file.\n");
  fprintf(output, "Summary of liquid properties:\n");
  fprintf(output, " %10.10s %9.9s %8.8s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s\n", 
    "Name", "H (kJ)", "S (J/K)", "k0/a", "k1/b", "k2/c", "k3/d", "Tt/e", "delH/g", "l1/h", "l2");
  for (i=0; i<nls; i++) {
    fprintf(output, " %10.10s", liquid[i].label);
    fprintf(output, " %9.3f", liquid[i].ref.h/1000.0);
    fprintf(output, " %8.3f", liquid[i].ref.s);
    if      (liquid[i].ref.cp_type == CP_BERMAN) {
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Berman.k0);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Berman.k1);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Berman.k2);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Berman.k3);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Berman.Tt);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Berman.deltah);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Berman.l1);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Berman.l1);
    } else if (liquid[i].ref.cp_type == CP_SAXENA) {
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Saxena.a);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Saxena.b);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Saxena.c);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Saxena.d);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Saxena.e);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Saxena.g);
      fprintf(output, " %9.2g",  liquid[i].ref.cp.Saxena.h);
    }
    fprintf(output, "\n");
  }
  fprintf(output, "\n");

  fprintf(output, "Summary of liquid properties (con't):\n");
  fprintf(output, " %10.10s %7.7s %8.8s %8.8s %8.8s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s %9.9s\n", 
    "Name", "Tf (K)", "Sf (J/K)", "Cp (J/K)", "V (J/b)", "a/dt", "c/dp", "dcdt/dtp", "cp/dp2/K'", "mw", "v2", "v3", 
    "v4", "K (GPa)", "K'");
  for (i=0; i<nls; i++) {
    fprintf(output, " %10.10s", liquid[i].label);
    fprintf(output, " %7.2f", liquid[i].liq.tfus);
    fprintf(output, " %8.3f", liquid[i].liq.sfus);
    fprintf(output, " %8.3f", liquid[i].liq.cp);
    fprintf(output, " %8.4f", liquid[i].liq.v);
    if        (liquid[i].liq.eos_type == EOS_GHIORSO) {
      double v1 = -(liquid[i].liq.v)*(liquid[i].liq.v)
                  *(1000.0/((liquid[i].liq.eos.Ghiorso.mw)*(liquid[i].liq.eos.Ghiorso.c)*(liquid[i].liq.eos.Ghiorso.c))
		    + 1673.15*(liquid[i].liq.eos.Ghiorso.alpha)*(liquid[i].liq.eos.Ghiorso.alpha)/(liquid[i].liq.eos.Ghiorso.cp));
      double K  = -liquid[i].liq.v/v1;
      double Kp = (liquid[i].liq.eos.Ghiorso.d2vdp2)*K*K/liquid[i].liq.v - 1.0;
      fprintf(output, " %9.3g",  liquid[i].liq.eos.Ghiorso.alpha);
      fprintf(output, " %9.2f",  liquid[i].liq.eos.Ghiorso.c);
      fprintf(output, " %9.4f",  liquid[i].liq.eos.Ghiorso.dcdt);
      fprintf(output, " %9.2f",  liquid[i].liq.eos.Ghiorso.cp);
      fprintf(output, " %9.3f",  liquid[i].liq.eos.Ghiorso.mw);
      fprintf(output, " %9.3g",  liquid[i].liq.eos.Ghiorso.d2vdp2);
      fprintf(output, " %9.3g",  liquid[i].liq.eos.Ghiorso.d3vdp3);
      fprintf(output, " %9.3g",  liquid[i].liq.eos.Ghiorso.d4vdp4);
      fprintf(output, " %9.3g",  K/10000.0);
      fprintf(output, " %9.3g",  Kp);
    } else if (liquid[i].liq.eos_type == EOS_KRESS  ) {
      fprintf(output, " %9.2g",  liquid[i].liq.eos.Kress.dvdt);
      fprintf(output, " %9.2g",  liquid[i].liq.eos.Kress.dvdp);
      fprintf(output, " %9.2g",  liquid[i].liq.eos.Kress.d2vdtp);
      fprintf(output, " %9.2g",  liquid[i].liq.eos.Kress.d2vdp2);
    }
    fprintf(output, "\n");
  }
  fprintf(output, "\n");

  fprintf(output, "T = %8.2f (K), P = %9.2f (bars)\n", t, p);
  fprintf(output, 
  "%14.14s %10.10s %10.10s %8.8s %8.8s %10.10s %8.8s %10.10s %10.10s %10.10s %10.10s %10.10s\n", 
  "name", "G (J)", "H (J)", "S (J/K)", "Cp (J/K)", "dCpdT", 
  "V (J/bar)","dVdT", "dVdP", "d2VdT2", "d2VdP2", "d2VdTdP");

  printf("Computing and writing solid thermodynamic data.\n");
  for (i=0; i<npc; i++) {
    gibbs(t, p, (char *) solids[i].label, &(solids[i].ref), NULL, NULL, &(solids[i].cur));
    fprintf(output, "%14.14s ",  solids[i].label);
    fprintf(output, "%10.0f " , (solids[i].cur).g); 
    fprintf(output, "%10.0f " , (solids[i].cur).h); 
    fprintf(output,  "%8.2f " , (solids[i].cur).s); 
    fprintf(output,  "%8.2f " , (solids[i].cur).cp); 
    fprintf(output, "%10.3g " , (solids[i].cur).dcpdt); 
    fprintf(output,  "%8.2f " , (solids[i].cur).v); 
    fprintf(output, "%10.3g " , (solids[i].cur).dvdt); 
    fprintf(output, "%10.3g " , (solids[i].cur).dvdp); 
    fprintf(output, "%10.3g " , (solids[i].cur).d2vdt2); 
    fprintf(output, "%10.3g " , (solids[i].cur).d2vdp2); 
    fprintf(output, "%10.3g\n", (solids[i].cur).d2vdtdp); 

    gRef       = (solids[i].cur).g;
    hRef       = (solids[i].cur).h;
    sRef       = (solids[i].cur).s;
    cpRef      = (solids[i].cur).cp;
    dcpdtRef   = (solids[i].cur).dcpdt;
    vRef       = (solids[i].cur).v;
    dvdtRef    = (solids[i].cur).dvdt;
    dvdpRef    = (solids[i].cur).dvdp;
    d2vdt2Ref  = (solids[i].cur).d2vdt2;
    d2vdp2Ref  = (solids[i].cur).d2vdp2;
    d2vdtdpRef = (solids[i].cur).d2vdtdp;

    gibbs(t+deltaT, p, (char *) solids[i].label, &(solids[i].ref), NULL, NULL, &(solids[i].cur));

    temp = -((solids[i].cur).g-gRef)/deltaT;
    TEST(sRef);
    printf("%s %s s  = %g (%g, %s)\n", flag, solids[i].label, sRef, temp, 
      "from g");

    temp = t*((solids[i].cur).s-sRef)/deltaT;
    TEST(cpRef);
    printf("%s %s cp = %g (%g, %s)\n", flag, solids[i].label, cpRef, temp, 
      "from s");

    temp = ((solids[i].cur).h-hRef)/deltaT;
    TEST(cpRef);
    printf("%s %s cp = %g (%g, %s)\n", flag, solids[i].label, cpRef, temp, 
      "from h");

    temp = ((solids[i].cur).cp-cpRef)/deltaT;
    TEST(dcpdtRef);
    printf("%s %s dcpdt = %g (%g, %s)\n", flag, solids[i].label, dcpdtRef, 
      temp, "from cp");

    temp = ((solids[i].cur).v-vRef)/deltaT;
    TEST(dvdtRef);
    printf("%s %s dvdt = %g (%g, %s)\n", flag, solids[i].label, dvdtRef, temp, 
      "from v");

    temp = ((solids[i].cur).dvdt-dvdtRef)/deltaT;
    TEST(d2vdt2Ref);
    printf("%s %s d2vdt2 = %g (%g, %s)\n", flag, solids[i].label, d2vdt2Ref, 
      temp, "from dvdt");

    temp = ((solids[i].cur).dvdp-dvdpRef)/deltaT;
    TEST(d2vdtdpRef);
    printf("%s %s d2vdtdp = %g (%g, %s)\n", flag, solids[i].label, d2vdtdpRef, 
      temp, "from dvdp");

    gibbs(t, p+deltaP, (char *) solids[i].label, &(solids[i].ref), NULL, NULL, &(solids[i].cur));

    temp = ((solids[i].cur).g-gRef)/deltaP;
    TEST(vRef);
    printf("%s %s v  = %g (%g, %s)\n", flag, solids[i].label, vRef, temp, 
      "from g");

    temp = ((solids[i].cur).v-vRef)/deltaP;
    TEST(dvdpRef);
    printf("%s %s dvdp = %g (%g, %s)\n", flag, solids[i].label, dvdpRef, temp, 
      "from v");

    temp = ((solids[i].cur).dvdp-dvdpRef)/deltaP;
    TEST(d2vdp2Ref);
    printf("%s %s d2vdp2 = %g (%g, %s)\n", flag, solids[i].label, d2vdp2Ref, 
      temp, "from dvdp");

    temp = ((solids[i].cur).dvdt-dvdtRef)/deltaP;
    TEST(d2vdtdpRef);
    printf("%s %s d2vdtdp = %g (%g, %s)\n", flag, solids[i].label, d2vdtdpRef, 
      temp, "from dvdt");

  }
  gibbs(t, p, "o2", &(oxygen.ref), NULL, NULL, &(oxygen.cur));
  fprintf(output, "%14.14s ",  "O2");
  fprintf(output, "%10.0f " , (oxygen.cur).g); 
  fprintf(output, "%10.0f " , (oxygen.cur).h); 
  fprintf(output,  "%8.2f " , (oxygen.cur).s); 
  fprintf(output,  "%8.2f " , (oxygen.cur).cp); 
  fprintf(output, "%10.3g " , (oxygen.cur).dcpdt); 
  fprintf(output,  "%8.2f " , (oxygen.cur).v); 
  fprintf(output, "%10.3g " , (oxygen.cur).dvdt); 
  fprintf(output, "%10.3g " , (oxygen.cur).dvdp); 
  fprintf(output, "%10.3g " , (oxygen.cur).d2vdt2); 
  fprintf(output, "%10.3g " , (oxygen.cur).d2vdp2); 
  fprintf(output, "%10.3g\n", (oxygen.cur).d2vdtdp); 

  gRef       = (oxygen.cur).g;
  hRef       = (oxygen.cur).h;
  sRef       = (oxygen.cur).s;
  cpRef      = (oxygen.cur).cp;
  dcpdtRef   = (oxygen.cur).dcpdt;
  vRef       = (oxygen.cur).v;
  dvdtRef    = (oxygen.cur).dvdt;
  dvdpRef    = (oxygen.cur).dvdp;
  d2vdt2Ref  = (oxygen.cur).d2vdt2;
  d2vdp2Ref  = (oxygen.cur).d2vdp2;
  d2vdtdpRef = (oxygen.cur).d2vdtdp;

  gibbs(t+deltaT, p, "o2", &(oxygen.ref), NULL, NULL, &(oxygen.cur));

  temp = -((oxygen.cur).g-gRef)/deltaT;
  TEST(sRef);
  printf("%s %s s  = %g (%g, %s)\n", flag, "O2", sRef, temp, "from g");

  temp = t*((oxygen.cur).s-sRef)/deltaT;
  TEST(cpRef);
  printf("%s %s cp = %g (%g, %s)\n", flag, "O2", cpRef, temp, "from s");

  temp = ((oxygen.cur).h-hRef)/deltaT;
  TEST(cpRef);
  printf("%s %s cp = %g (%g, %s)\n", flag, "O2", cpRef, temp, "from h");

  temp = ((oxygen.cur).cp-cpRef)/deltaT;
  TEST(dcpdtRef);
  printf("%s %s dcpdt = %g (%g, %s)\n", flag, "O2", dcpdtRef, temp, "from h");

  temp = ((oxygen.cur).v-vRef)/deltaT;
  TEST(dvdtRef);
  printf("%s %s dvdt = %g (%g, %s)\n", flag, "O2", dvdtRef, temp, "from v");

  temp = ((oxygen.cur).dvdt-dvdtRef)/deltaT;
  TEST(d2vdt2Ref);
  printf("%s %s d2vdt2 = %g (%g, %s)\n", flag, "O2", d2vdt2Ref, temp, 
    "from dvdt");

  temp = ((oxygen.cur).dvdp-dvdpRef)/deltaT;
  TEST(d2vdtdpRef);
  printf("%s %s d2vdtdp = %g (%g, %s)\n", flag, "O2", d2vdtdpRef, temp, 
    "from dvdp");

  gibbs(t, p+deltaP, "o2", &(oxygen.ref), NULL, NULL, &(oxygen.cur));

  temp = ((oxygen.cur).g-gRef)/deltaP;
  TEST(vRef);
  printf("%s %s v  = %g (%g, %s)\n", flag, "O2", vRef, temp, "from g");

  temp = ((oxygen.cur).v-vRef)/deltaP;
  TEST(dvdpRef);
  printf("%s %s dvdp = %g (%g, %s)\n", flag, "O2", dvdpRef, temp, "from v");

  temp = ((oxygen.cur).dvdp-dvdpRef)/deltaP;
  TEST(d2vdp2Ref);
  printf("%s %s d2vdp2 = %g (%g, %s)\n", flag, "O2", d2vdp2Ref, temp, 
    "from dvdp");

  temp = ((oxygen.cur).dvdt-dvdtRef)/deltaP;
  TEST(d2vdtdpRef);
  printf("%s %s d2vdtdp = %g (%g, %s)\n", flag, "O2", d2vdtdpRef, temp, 
    "from dvdt");

  fprintf(output, "\fT = %.2f C, P = %.3f kb\n", t-273.15, p/1000.0);
  fprintf(output, 
  "%14.14s %10.10s %10.10s %8.8s %8.8s %10.10s %8.8s %10.10s %10.10s %10.10s %10.10s %10.10s\n", 
  "name", "G (J)", "H (J)", "S (J/K)", "Cp (J/K)", "dCpdT", 
  "V (J/bar)","dVdT", "dVdP", "d2VdT2", "d2VdP2", "d2VdTdP");
  printf("Computing and writing liquid thermodynamic data.\n");
  for (i=0; i<nls; i++) {
    gibbs(t, p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
    fprintf(output, "%14.14s ",  liquid[i].label);
    fprintf(output, "%10.0f " , (liquid[i].cur).g); 
    fprintf(output, "%10.0f " , (liquid[i].cur).h); 
    fprintf(output,  "%8.2f " , (liquid[i].cur).s); 
    fprintf(output,  "%8.2f " , (liquid[i].cur).cp); 
    fprintf(output, "%10.3g " , (liquid[i].cur).dcpdt); 
    fprintf(output,  "%8.2f " , (liquid[i].cur).v); 
    fprintf(output, "%10.3g " , (liquid[i].cur).dvdt); 
    fprintf(output, "%10.3g " , (liquid[i].cur).dvdp); 
    fprintf(output, "%10.3g " , (liquid[i].cur).d2vdt2); 
    fprintf(output, "%10.3g " , (liquid[i].cur).d2vdp2); 
    fprintf(output, "%10.3g\n", (liquid[i].cur).d2vdtdp); 

    gRef       = (liquid[i].cur).g;
    hRef       = (liquid[i].cur).h;
    sRef       = (liquid[i].cur).s;
    cpRef      = (liquid[i].cur).cp;
    dcpdtRef   = (liquid[i].cur).dcpdt;
    vRef       = (liquid[i].cur).v;
    dvdtRef    = (liquid[i].cur).dvdt;
    dvdpRef    = (liquid[i].cur).dvdp;
    d2vdt2Ref  = (liquid[i].cur).d2vdt2;
    d2vdp2Ref  = (liquid[i].cur).d2vdp2;
    d2vdtdpRef = (liquid[i].cur).d2vdtdp;

    gibbs(t+deltaT, p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));

    temp = -((liquid[i].cur).g-gRef)/deltaT;
    TEST(sRef);
    printf("%s %s s  = %g (%g, %s)\n", flag, liquid[i].label, sRef, temp, 
      "from g");

    temp = t*((liquid[i].cur).s-sRef)/deltaT;
    TEST(cpRef);
    printf("%s %s cp = %g (%g, %s)\n", flag, liquid[i].label, cpRef, temp, 
      "from s");

    temp = ((liquid[i].cur).h-hRef)/deltaT;
    TEST(cpRef);
    printf("%s %s cp = %g (%g, %s)\n", flag, liquid[i].label, cpRef, temp, 
      "from h");

    temp = ((liquid[i].cur).cp-cpRef)/deltaT;
    TEST(dcpdtRef);
    printf("%s %s dcpdt = %g (%g, %s)\n", flag, liquid[i].label, dcpdtRef, 
      temp, "from h");

    temp = ((liquid[i].cur).v-vRef)/deltaT;
    TEST(dvdtRef);
    printf("%s %s dvdt = %g (%g, %s)\n", flag, liquid[i].label, dvdtRef, temp, 
      "from v");

    temp = ((liquid[i].cur).dvdt-dvdtRef)/deltaT;
    TEST(d2vdt2Ref);
    printf("%s %s d2vdt2 = %g (%g, %s)\n", flag, liquid[i].label, d2vdt2Ref, 
      temp, "from dvdt");

    temp = ((liquid[i].cur).dvdp-dvdpRef)/deltaT;
    TEST(d2vdtdpRef);
    printf("%s %s d2vdtdp = %g (%g, %s)\n", flag, liquid[i].label, d2vdtdpRef, 
      temp, "from dvdp");

    gibbs(t, p+deltaP, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));

    temp = ((liquid[i].cur).g-gRef)/deltaP;
    TEST(vRef);
    printf("%s %s v  = %g (%g, %s)\n", flag, liquid[i].label, vRef, temp, 
      "from g");

    temp = ((liquid[i].cur).v-vRef)/deltaP;
    TEST(dvdpRef);
    printf("%s %s dvdp = %g (%g, %s)\n", flag, liquid[i].label, dvdpRef, temp, 
      "from v");

    temp = ((liquid[i].cur).dvdp-dvdpRef)/deltaP;
    TEST(d2vdp2Ref);
    printf("%s %s d2vdp2 = %g (%g, %s)\n", flag, liquid[i].label, d2vdp2Ref, 
      temp, "from dvdp");

    temp = ((liquid[i].cur).dvdt-dvdtRef)/deltaP;
    TEST(d2vdtdpRef);
    printf("%s %s d2vdtdp = %g (%g, %s)\n", flag, liquid[i].label, d2vdtdpRef, 
      temp, "from dvdt");
  }

  printf("Computing Gibbs energies of fusion for all solids.\n");
  fprintf(output,"\fsolid -> liquid Reaction Stoichiometry:\n");
  for (i=0; i<npc; i++) {
    if((solids[i].ref).h != 0.0) {
      fprintf(output, "%14.14s =", solids[i].label);
      for (j=0; j<nlc; j++) if( (solids[i].solToLiq)[j] != 0.0)
        fprintf(output, " %+5.2f %-10.10s", (solids[i].solToLiq)[j], 
          liquid[j].label);
      fprintf(output, "\n");
    }
  }

  for (i=0; i<nc; i++) {
    if (bulkSystem[i].type == FEO)   indFeO   = i;
    if (bulkSystem[i].type == FE2O3) indFe2O3 = i;
  }

  if (indFeO != -1 && indFe2O3 != -1) {
    fprintf(output, "%14.14s =", "O2");
    for (j=0; j<nlc; j++) {
      double coeff = 2.0*(bulkSystem[indFe2O3].oxToLiq)[j] 
                   - 4.0*(bulkSystem[indFeO].oxToLiq)[j];
      if( coeff != 0.0) fprintf(output, " %+5.2f %-10.10s", coeff, 
        liquid[j].label);
    }
    fprintf(output, "\n");
  }

  fprintf(output, 
  "\f%14.14s %10.10s %10.10s %8.8s %8.8s %10.10s %8.8s %10.10s %10.10s %10.10s %10.10s %10.10s\n", 
  "name", "G (J)", "H (J)", "S (J/K)", "Cp (J/K)", "dCpdT", 
  "V (J/bar)","dVdT", "dVdP", "d2VdT2", "d2VdP2", "d2VdTdP");
  for (i=0; i<npc; i++) {
    if((solids[i].ref).h != 0.0) {
      Dg       = -(solids[i].cur).g;
      Dh       = -(solids[i].cur).h; 
      Ds       = -(solids[i].cur).s; 
      DCp      = -(solids[i].cur).cp; 
      DdCpdT   = -(solids[i].cur).dcpdt; 
      Dv       = -(solids[i].cur).v; 
      DdVdT    = -(solids[i].cur).dvdt; 
      DdVdP    = -(solids[i].cur).dvdp; 
      Dd2VdT2  = -(solids[i].cur).d2vdt2; 
      Dd2VdP2  = -(solids[i].cur).d2vdp2; 
      Dd2VdTdP = -(solids[i].cur).d2vdtdp; 
      for (j=0; j<nlc; j++) {
        if( (solids[i].solToLiq)[j] != 0.0) {
          Dg       += (solids[i].solToLiq)[j]*(liquid[j].cur).g;
          Dh       += (solids[i].solToLiq)[j]*(liquid[j].cur).h;
          Ds       += (solids[i].solToLiq)[j]*(liquid[j].cur).s;
          DCp      += (solids[i].solToLiq)[j]*(liquid[j].cur).cp;
          DdCpdT   += (solids[i].solToLiq)[j]*(liquid[j].cur).dcpdt;
          Dv       += (solids[i].solToLiq)[j]*(liquid[j].cur).v;
          DdVdT    += (solids[i].solToLiq)[j]*(liquid[j].cur).dvdt;
          DdVdP    += (solids[i].solToLiq)[j]*(liquid[j].cur).dvdp;
          Dd2VdT2  += (solids[i].solToLiq)[j]*(liquid[j].cur).d2vdt2;
          Dd2VdP2  += (solids[i].solToLiq)[j]*(liquid[j].cur).d2vdp2;
          Dd2VdTdP += (solids[i].solToLiq)[j]*(liquid[j].cur).d2vdtdp;
        }
      }
      fprintf(output, "%14.14s ",  solids[i].label);
      fprintf(output, "%10.0f " , Dg); 
      fprintf(output, "%10.0f " , Dh); 
      fprintf(output,  "%8.2f " , Ds); 
      fprintf(output,  "%8.2f " , DCp); 
      fprintf(output, "%10.3g " , DdCpdT); 
      fprintf(output,  "%8.2f " , Dv); 
      fprintf(output, "%10.3g " , DdVdT); 
      fprintf(output, "%10.3g " , DdVdP); 
      fprintf(output, "%10.3g " , Dd2VdT2); 
      fprintf(output, "%10.3g " , Dd2VdP2); 
      fprintf(output, "%10.3g\n", Dd2VdTdP); 
    }
  }

  if (indFeO != -1 && indFe2O3 != -1) {
    Dg       = -(oxygen.cur).g;
    Dh       = -(oxygen.cur).h; 
    Ds       = -(oxygen.cur).s; 
    DCp      = -(oxygen.cur).cp; 
    DdCpdT   = -(oxygen.cur).dcpdt; 
    Dv       = -(oxygen.cur).v; 
    DdVdT    = -(oxygen.cur).dvdt; 
    DdVdP    = -(oxygen.cur).dvdp; 
    Dd2VdT2  = -(oxygen.cur).d2vdt2; 
    Dd2VdP2  = -(oxygen.cur).d2vdp2; 
    Dd2VdTdP = -(oxygen.cur).d2vdtdp; 
    for (j=0; j<nlc; j++) {
      double coeff = 2.0*(bulkSystem[indFe2O3].oxToLiq)[j] 
                   - 4.0*(bulkSystem[indFeO].oxToLiq)[j];
      if( coeff != 0.0) {
        Dg       += coeff*(liquid[j].cur).g;
        Dh       += coeff*(liquid[j].cur).h;
        Ds       += coeff*(liquid[j].cur).s;
        DCp      += coeff*(liquid[j].cur).cp;
        DdCpdT   += coeff*(liquid[j].cur).dcpdt;
        Dv       += coeff*(liquid[j].cur).v;
        DdVdT    += coeff*(liquid[j].cur).dvdt;
        DdVdP    += coeff*(liquid[j].cur).dvdp;
        Dd2VdT2  += coeff*(liquid[j].cur).d2vdt2;
        Dd2VdP2  += coeff*(liquid[j].cur).d2vdp2;
        Dd2VdTdP += coeff*(liquid[j].cur).d2vdtdp;
      }
    }
    fprintf(output, "%14.14s ", "O2");
    fprintf(output, "%10.0f " , Dg); 
    fprintf(output, "%10.0f " , Dh); 
    fprintf(output,  "%8.2f " , Ds); 
    fprintf(output,  "%8.2f " , DCp); 
    fprintf(output, "%10.3g " , DdCpdT); 
    fprintf(output,  "%8.2f " , Dv); 
    fprintf(output, "%10.3g " , DdVdT); 
    fprintf(output, "%10.3g " , DdVdP); 
    fprintf(output, "%10.3g " , Dd2VdT2); 
    fprintf(output, "%10.3g " , Dd2VdP2); 
    fprintf(output, "%10.3g\n", Dd2VdTdP); 
  }

  fclose(output);
  return 0;
}

/* End file: TEST_GIBBS.C */

