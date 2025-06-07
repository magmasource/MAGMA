const char *test_eos_ver(void) { return "$Id: test_SACNK.c,v 1.4 2009/05/14 04:24:00 ghiorso Exp $"; }

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Test routine to evaluate the functions defined for the computation
**      of EOS properties in the liquid 
**      (file: TEST_EOS.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  January 16, 2009 Original Version
**--
*/

#include <X11/Intrinsic.h>
#include <Xm/Xm.h>

#include "interface.h"
Widget main_window, silmin_adb, topLevel;
MeltsEnviron meltsEnviron;

#include "silmin.h"
#include "recipes.h"

#include "liq_struct_data_SiO2_Al2O3_CaO_Na2O_K2O.h"
#include "sol_struct_data_SiO2_Al2O3_CaO_Na2O_K2O.h"
#include "param_struct_data_SiO2_Al2O3_CaO_Na2O_K2O.h"

#include <unistd.h>
#include <grace_np.h>

SilminState *silminState;
int calculationMode = MODE_DEFAULT;

static void grace_error_function(const char *msg)
{
  fprintf(stderr, "library message : \"%s\"\n", msg);
}

int main()
{
  int i, j, k, type;
  int nr = nlc - 1;
  float ftemp;
  double t, pb;
  double p = 1.0;
  double *grams, *moles, *x, *mu, *xSpecies;
  int list[] = { 0, 1, 3, 7, 16, 17, 19, 23, 24, 25, 26, 27, 28 }; 
  int nCrst = -1, nTrid = -1, nQtz = -1, nNaDi = -1, nNaMt = -1, nNaOr = -1, nCor = -1, nMul = -1, 
      nAlb = -1, nCar = -1, nNeph = -1, nNA2 = -1, nNA9 = -1;
  
  printf("***************************************************\n");
  printf("Calling function: InitComputeDataStruct().	     \n");
  printf("***************************************************\n\n");
  InitComputeDataStruct();
  setModeToMixingLiq(FALSE);

  printf("1    = speciation\n");
  printf("2    = phase diagram\n");
  printf("3(1) = Gibbs energy (mix)\n");
  printf("4(1) = Entropy (mix)\n");
  printf("5(1) = Enthalpy (mix)\n");
  printf("6    = activities\n");
  printf("Input plot type: "); scanf("%d", &type);
  getchar();
  if (type != 2) {
    printf("Input a T (C): "); scanf("%f", &ftemp); t = (double) ftemp + 273.15;
    getchar();
  } else t = 1800.0;
  printf("9999 = SiO2-Na2O join\n8888 = SiO2-Al2O3 join\n7777 = Na2O-Al2O3 join\n6666 = SiO2-NaAlO2 join\n");
  printf("5555 = SiO2-Na2O_60_Al2O3_40 join\n4444 = SiO2-Na2O_70_Al2O3_30 join\n3333 = SiO2-Na2O_80_Al2O3_20 join\n");
  printf("2222 = SiO2-Na2O_90_Al2O3_10 join\n1111 = SiO2-Na2O_50_Al2O3_50 join\n1234 = SiO2-Na2O_30_Al2O3_70 join\n");
  printf("else input a wt ratio of SiO2/Al2O3: "); scanf("%f", &ftemp); pb = (double) ftemp;
  getchar();

  grams    = vector(0, nc-1);
  moles    = vector(0, nlc-1);
  x	   = vector(0, nr-1);
  mu	   = vector(0, nlc-1);
  xSpecies = vector(0, nls-1);

  GraceRegisterErrorFunction (grace_error_function);
  if(GraceOpen (2048) < 0) { printf("Cannot open pipe to Grace.\n"); exit(0); }

  GracePrintf("WITH G0\n");
   GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.15, 0.15, 1.15, 0.85);
   GracePrintf("WORLD %lf, %lf, %lf, %lf\n",  0.0, 0.0, 100.0, 1.0);

   GracePrintf("XAXIS TICK MAJOR 10.0\n");
   GracePrintf("XAXIS TICK MINOR  5.0\n");
   GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

   GracePrintf("XAXIS LABEL \"Wt% Na2O\"\n");
   GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
   GracePrintf("XAXIS LABEL COLOR 2\n");

   GracePrintf("YAXIS TICK MAJOR 4.00\n");
   GracePrintf("YAXIS TICK MINOR 2.00\n");
   GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

   GracePrintf("YAXIS LABEL \"various\"\n");
   GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
   GracePrintf("YAXIS LABEL COLOR 2\n");
   
   GracePrintf("LEGEND ON\n");
   GracePrintf("LEGEND 1, 0.95\n");
   GracePrintf("LEGEND FONT 6\n");
   GracePrintf("LEGEND CHAR SIZE 0.750000\n");
   
   GracePrintf("FRAME ON\n");
 
   if (type == 2) {
     if (pb != 7777.0) {
       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 0);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 0, 0+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    0);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 0, "eq", "cristobalite");

       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 1);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 1, 1+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    1);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 1, "eq", "tridymite");

       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 2);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 2, 2+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    2);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 2, "eq", "quartz");
     }

     if ((pb != 7777.0) && (pb != 8888.0)) {
       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 3);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 3, 3+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    3);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 3, "eq", "nadisilicate");

       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 4);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 4, 4+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    4);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 4, "eq", "nametasilicate");

       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 5);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 5, 5+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    5);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 5, "eq", "naorthosilicate");
     }
     
     if (pb != 9999.0) {
       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 6);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 6, 6+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    6);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 6, "eq", "corundum");

       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 7);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 7, 7+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    7);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 7, "eq", "mullite");
     }
     
     if ((pb != 7777.0) && (pb != 8888.0) && (pb != 9999.0)) {
       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 8);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 8, 8+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    8);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 8, "eq", "monalbite");

       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 9);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 9, 9+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    9);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 9, "eq", "carnegieite");

       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 10);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 10, 10+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    10);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 10, "eq", "nepheline");

       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 11);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 11, 11+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    11);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 11, "eq", "naalo2");

       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 12);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 12, 12+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    12);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 12, "eq", "naal9o14");
     }
     
   } else if ((type == 4) || (type == 41)) {  
     GracePrintf("g0.s%1.1d LINESTYLE 1\n", 5);
     GracePrintf("g0.s%1.1d COLOR %1.1d\n", 5, 5+1);
     GracePrintf("g0.s%1.1d SYMBOL 0\n",    5);
     GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 5, "Entropy", "J/K-100 gm");
     if ((type == 4) && (pb == 9999.0)) {
       GracePrintf("g0.s%1.1d LINESTYLE 0\n", 6);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 6, 6+1);
       GracePrintf("g0.s%1.1d SYMBOL 1\n",    6);
       GracePrintf("g0.s%1.1d SYMBOL COLOR %1.1d\n", 6, 0+1);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 6, "S (data)", "J/K-100 gm");
       GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 6, 50.78, 306.088/1.2289); /* Na2SiO3  1088.15 C */
       GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 6, 34.03, 262.50/1.09804); /* Na2Si2O5  873.85 C */
     }
   } else if ((type == 5) || (type == 51)) {  
     GracePrintf("g0.s%1.1d LINESTYLE 1\n", 7);
     GracePrintf("g0.s%1.1d COLOR %1.1d\n", 7, 7+1);
     GracePrintf("g0.s%1.1d SYMBOL 0\n",    7);
     GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 7, "Enhalpy", "kJ/100 gm");
     if ((type == 5) &&  (pb == 9999.0)) {
       GracePrintf("g0.s%1.1d LINESTYLE 0\n", 8);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 8, 8+1);
       GracePrintf("g0.s%1.1d SYMBOL 1\n",    8);
       GracePrintf("g0.s%1.1d SYMBOL COLOR %1.1d\n", 8, 0+2);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 8, "H (data)", "kJ/100 gm");
       GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 8, 50.78, -1102.756/1.2289);  /* Na2SiO3  1088.15 C */
       GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 8, 34.03, -1234.669/1.09804); /* Na2Si2O5  873.85 C */
     }
   } else if (type == 1) {  
     for (i=10; i<(10+13); i++) {
       GracePrintf("g0.s%2.2d LINESTYLE 1\n", i);
       GracePrintf("g0.s%2.2d COLOR %1.1d\n", i, i-9);
       GracePrintf("g0.s%2.2d SYMBOL 0\n",    i);
       GracePrintf("g0.s%2.2d LEGEND \"%s %s\"\n", i, "X", liquid[list[i-10]].label);
     }
   } else if ((type == 3) || (type == 31)) {
       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 0);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 0, 0+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    0);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 0, "Gibbs Energy", "kJ/mol");
   } else if (type == 6) {
       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 0);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 0, 0+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    0);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 0, "Si2O4", "kJ/mol");

       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 1);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 1, 1+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    1);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 1, "Al2O3", "kJ/mol");

       GracePrintf("g0.s%1.1d LINESTYLE 1\n", 2);
       GracePrintf("g0.s%1.1d COLOR %1.1d\n", 2, 2+1);
       GracePrintf("g0.s%1.1d SYMBOL 0\n",    2);
       GracePrintf("g0.s%1.1d LEGEND \"%s %s\"\n", 2, "Na2O", "kJ/mol");
   }

   /*************************************************************************** 
    Compute composition of the liquid phase (moles)
    ***************************************************************************/

   for (i=1; i<100; i++) {
     double wtSoda = (double) i;
     double smix, hmix, gmix;
     grams[3] = wtSoda;                       /* Na2O  */
     if (pb == 9999.0) { /* SiO2 - Na2O join */
       grams[1] = 0.0;
       grams[0] = 100.0 - wtSoda;

     } else if (pb == 8888.0) { /* SiO2 - Al2O3 join */
       grams[1] = wtSoda;
       grams[0] = 100.0 - wtSoda;
       grams[3] = 0.0;
     
     } else if (pb == 7777.0) { /* Na2O - Al2O3 join */
       grams[0] = 0.0;
       grams[1] = 100.0 - wtSoda;

     } else if (pb == 6666.0) { /* NaAlO2 - SiO2 join */
       double spb = 37.81/62.19;
       grams[0] = 100.0 - wtSoda;
       grams[1] =     (100.0-grams[0])/(1.0+spb); /* Al2O3 */
       grams[3] = spb*(100.0-grams[0])/(1.0+spb); /* Na2O  */
     
     } else if (pb == 5555.0) { /* Na2O 60% Al2O3 40% - SiO2 join */
       double spb = 60.0/40.0;
       grams[0] = 100.0 - wtSoda;
       grams[1] =     (100.0-grams[0])/(1.0+spb); /* Al2O3 */
       grams[3] = spb*(100.0-grams[0])/(1.0+spb); /* Na2O  */
     
     } else if (pb == 4444.0) { /* Na2O 70% Al2O3 30% - SiO2 join */
       double spb = 70.0/30.0;
       grams[0] = 100.0 - wtSoda;
       grams[1] =     (100.0-grams[0])/(1.0+spb); /* Al2O3 */
       grams[3] = spb*(100.0-grams[0])/(1.0+spb); /* Na2O  */
     
     } else if (pb == 3333.0) { /* Na2O 80% Al2O3 20% - SiO2 join */
       double spb = 80.0/20.0;
       grams[0] = 100.0 - wtSoda;
       grams[1] =     (100.0-grams[0])/(1.0+spb); /* Al2O3 */
       grams[3] = spb*(100.0-grams[0])/(1.0+spb); /* Na2O  */
     
     } else if (pb == 2222.0) { /* Na2O 90% Al2O3 10% - SiO2 join */
       double spb = 90.0/10.0;
       grams[0] = 100.0 - wtSoda;
       grams[1] =     (100.0-grams[0])/(1.0+spb); /* Al2O3 */
       grams[3] = spb*(100.0-grams[0])/(1.0+spb); /* Na2O  */
     
     } else if (pb == 1111.0) { /* Na2O 50% Al2O3 50% - SiO2 join */
       double spb = 1.0;
       grams[0] = 100.0 - wtSoda;
       grams[1] =     (100.0-grams[0])/(1.0+spb); /* Al2O3 */
       grams[3] = spb*(100.0-grams[0])/(1.0+spb); /* Na2O  */
     
     } else if (pb == 1234.0) { /* Na2O 30% Al2O3 70% - SiO2 join */
       double spb = 30.0/70.0;
       grams[0] = 100.0 - wtSoda;
       grams[1] =     (100.0-grams[0])/(1.0+spb); /* Al2O3 */
       grams[3] = spb*(100.0-grams[0])/(1.0+spb); /* Na2O  */
     
     } else {
       grams[1] =    (100.0-grams[3])/(1.0+pb); /* Al2O3 */
       grams[0] = pb*(100.0-grams[3])/(1.0+pb); /* SiO2  */
       printf("%g %g %g\n", grams[0], grams[1], grams[3]);
     }
     grams[2] = 0.0; grams[4] = 0.0; grams[5] = 0.0;

     for (j=0; j<nc; j++) grams[j] /= bulkSystem[j].mw;
     for (j=0; j<nlc; j++) for (k=0,moles[j]=0.0; k<nc; k++) moles[j] += grams[k]*(bulkSystem[k].oxToLiq)[j];

     if (testLiq(SIXTH, t, p, 0, 0, NULL, NULL, NULL, moles)) {
       conLiq(SECOND, THIRD, t, p, NULL, moles, x, NULL, NULL, NULL, NULL);
       conLiq(THIRD, FOURTH | EIGHTH, t, p, NULL, NULL, x, xSpecies, NULL, NULL, NULL);
   
       if (type == 2) {
         static double tCrst = 2000.0, tTrid = 2000.0, tQtz = 1700.0, tNaDi = 1900.0, tNaMt = 1800.0, tNaOr = 1700.0,
	               tCor = 2000.0, tMul = 2000.0, tAlb = 2000.0, tCar = 2000.0, tNeph = 2000.0, tNA2 = 2000.0, 
		       tNA9 = 2000.0;
	 double resid, tinc;
	 int count;
         if ((nCrst == -1) || (nTrid == -1) || (nQtz == -1) || (nNaDi == -1) || (nNaMt == -1) || (nNaOr == -1)
	  || (nCor  == -1) || (nMul  == -1) || (nAlb == -1) || (nCar  == -1) || (nNeph == -1) || (nNA2  == -1) 
	  || (nNA9  == -1) ) {
           for (k=0; k<npc; k++) {
	     if (!strcmp("cristobalite",    solids[k].label) && (solids[k].type == PHASE)) nCrst = k;
	     if (!strcmp("tridymite",       solids[k].label) && (solids[k].type == PHASE)) nTrid = k;
	     if (!strcmp("quartz",          solids[k].label) && (solids[k].type == PHASE)) nQtz  = k;
	     if (!strcmp("nadisilicate",    solids[k].label) && (solids[k].type == PHASE)) nNaDi = k;
	     if (!strcmp("nametasilicate",  solids[k].label) && (solids[k].type == PHASE)) nNaMt = k;
	     if (!strcmp("naorthosilicate", solids[k].label) && (solids[k].type == PHASE)) nNaOr = k;
	     if (!strcmp("corundum",        solids[k].label) && (solids[k].type == PHASE)) nCor  = k;
	     if (!strcmp("mullite",         solids[k].label) && (solids[k].type == PHASE)) nMul  = k;
	     if (!strcmp("monalbite",       solids[k].label) && (solids[k].type == PHASE)) nAlb  = k;
	     if (!strcmp("carnegieite",     solids[k].label) && (solids[k].type == PHASE)) nCar  = k;
	     if (!strcmp("nepheline",       solids[k].label) && (solids[k].type == PHASE)) nNeph = k;
	     if (!strcmp("naalo2",          solids[k].label) && (solids[k].type == PHASE)) nNA2  = k;
	     if (!strcmp("naal9o14",        solids[k].label) && (solids[k].type == PHASE)) nNA9  = k;
	   }
	   if ((nCrst == -1) || (nTrid == -1) || (nQtz == -1) || (nNaDi == -1) || (nNaMt == -1) || (nNaOr == -1)
	    || (nCor  == -1) || (nMul  == -1) || (nAlb == -1) || (nCar  == -1) || (nNeph == -1) || (nNA2  == -1) 
	    || (nNA9  == -1) ) {
	     printf("Cannot find index of one or more solid phases:\n");
	     printf("  nCrst(%d), nTrid(%d), nQtz(%d)  nNaDi(%d), nNaMt(%d), nNaOr(%d), nCor(%d), nMul(%d)\n", 
	       nCrst, nTrid, nQtz, nNaDi, nNaMt, nNaOr, nCor, nMul);
	     printf("  nAlb(%d), nCar(%d), nNeph(%d)  nNA2(%d)  nNA9(%d)\n", nAlb, nCar, nNeph, nNA2, nNA9);
	     return 0;
	   }
	 }
	 printf("Computing phase stablity at wt = %5.1f ", wtSoda);
	 
	 if (pb != 7777.0) {

         printf("C");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tCrst, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tCrst, p, (char *) solids[nCrst].label, &(solids[nCrst].ref), NULL, NULL, &(solids[nCrst].cur));
	   resid = (mu[0]/2.0-solids[nCrst].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tCrst += tinc;
	   count++;
	   if (tCrst < 800.0) { count = 100; tCrst = 2000.0; } 
	   /* printf("tCrst = %f, resid = %g, count = %d\n", tCrst, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 0, 100.0-wtSoda, tCrst-273.15);

         printf("T");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tTrid, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tTrid, p, (char *) solids[nTrid].label, &(solids[nTrid].ref), NULL, NULL, &(solids[nTrid].cur));
	   resid = (mu[0]/2.0-solids[nTrid].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tTrid += tinc;
	   count++;
	   if (tTrid < 800.0) { count = 100; tTrid = 2000.0; } 
	   /* printf("tTrid = %f, resid = %g, count = %d\n", tTrid, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, 100.0-wtSoda, tTrid-273.15);

         printf("Q");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tQtz, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tQtz, p, (char *) solids[nQtz].label, &(solids[nQtz].ref), NULL, NULL, &(solids[nQtz].cur));
	   resid = (mu[0]/2.0-solids[nQtz].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tQtz += tinc;
	   count++;
	   if (tQtz < 800.0) { count = 100; tQtz = 2000.0; } 
	   /* printf("tQtz = %f, resid = %g, count = %d\n", tQtz, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 2, 100.0-wtSoda, tQtz-273.15);
	 
	 }
	 if ((pb != 7777.0) && (pb != 8888.0)) {

         printf("D");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tNaDi, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tNaDi, p, (char *) solids[nNaDi].label, &(solids[nNaDi].ref), NULL, NULL, &(solids[nNaDi].cur));
	   resid = (mu[0]+mu[3]-solids[nNaDi].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tNaDi += tinc;
	   count++;
	   if (tNaDi < 800.0) { count = 100; tNaDi = 2000.0; } 
	   /* printf("tNaDi = %f, resid = %g, count = %d\n", tNaDi, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 3, 100.0-wtSoda, tNaDi-273.15);

         printf("M");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tNaMt, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tNaMt, p, (char *) solids[nNaMt].label, &(solids[nNaMt].ref), NULL, NULL, &(solids[nNaMt].cur));
	   resid = (mu[0]/2.0+mu[3]-solids[nNaMt].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tNaMt += tinc;
	   count++;
	   if (tNaMt < 800.0) { count = 100; tNaMt = 2000.0; } 
	   /* printf("tNaMt = %f, resid = %g, count = %d\n", tNaMt, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 4, 100.0-wtSoda, tNaMt-273.15);

         printf("T");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tNaOr, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tNaOr, p, (char *) solids[nNaOr].label, &(solids[nNaOr].ref), NULL, NULL, &(solids[nNaOr].cur));
	   resid = (mu[0]/2.0+2.0*mu[3]-solids[nNaOr].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tNaOr += tinc;
	   count++;
	   if (tNaOr < 800.0) { count = 100; tNaOr = 2000.0; } 
	   /* printf("tNaOr = %f, resid = %g, count = %d\n", tNaOr, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 5, 100.0-wtSoda, tNaOr-273.15);
	 
	 }
	 if (pb != 9999.0) {
	 
         printf("C");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tCor, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tCor, p, (char *) solids[nCor].label, &(solids[nCor].ref), NULL, NULL, &(solids[nCor].cur));
	   resid = (mu[1]-solids[nCor].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tCor += tinc;
	   count++;
	   if (tCor < 800.0) { count = 100; tCor = 2000.0; } 
	   /* printf("tCor = %f, resid = %g, count = %d\n", tCor, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 6, 100.0-wtSoda, tCor-273.15);
	 
         printf("M");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tMul, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tMul, p, (char *) solids[nMul].label, &(solids[nMul].ref), NULL, NULL, &(solids[nMul].cur));
	   resid = (mu[0]+3.0*mu[1]-solids[nMul].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tMul += tinc;
	   count++;
	   if (tMul < 800.0) { count = 100; tMul = 2000.0; } 
	   /* printf("tMul = %f, resid = %g, count = %d\n", tMul, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 7, 100.0-wtSoda, tMul-273.15);
	 
	 }
	 
	 if ((pb != 7777.0) && (pb != 8888.0) && (pb != 9999.0)) {

         printf("A");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tAlb, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tAlb, p, (char *) solids[nAlb].label, &(solids[nAlb].ref), NULL, NULL, &(solids[nAlb].cur));
	   resid = (3.0*mu[0]/2.0+mu[1]/2.0+mu[3]/2.0-solids[nAlb].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tAlb += tinc;
	   count++;
	   if (tAlb < 800.0) { count = 100; tAlb = 2000.0; } 
	   /* printf("tAlb = %f, resid = %g, count = %d\n", tAlb, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 8, 100.0-wtSoda, tAlb-273.15);

         printf("C");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tCar, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tCar, p, (char *) solids[nCar].label, &(solids[nCar].ref), NULL, NULL, &(solids[nCar].cur));
	   resid = (mu[0]/2.0+mu[1]/2.0+mu[3]/2.0-solids[nCar].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tCar += tinc;
	   count++;
	   if (tCar < 800.0) { count = 100; tCar = 2000.0; } 
	   /* printf("tCar = %f, resid = %g, count = %d\n", tCar, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 9, 100.0-wtSoda, tCar-273.15);

         printf("N");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tNeph, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tNeph, p, (char *) solids[nNeph].label, &(solids[nNeph].ref), NULL, NULL, &(solids[nNeph].cur));
	   resid = (mu[0]/2.0+mu[1]/2.0+mu[3]/2.0-solids[nNeph].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tNeph += tinc;
	   count++;
	   if (tNeph < 800.0) { count = 100; tNeph = 2000.0; } 
	   /* printf("tNeph = %f, resid = %g, count = %d\n", tNeph, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 10, 100.0-wtSoda, tNeph-273.15);

         printf("2");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tNA2, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tNA2, p, (char *) solids[nNA2].label, &(solids[nNA2].ref), NULL, NULL, &(solids[nNA2].cur));
	   resid = (mu[1]/2.0+mu[3]/2.0-solids[nNA2].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tNA2 += tinc;
	   count++;
	   if (tNA2 < 800.0) { count = 100; tNA2 = 2000.0; } 
	   /* printf("tNA2 = %f, resid = %g, count = %d\n", tNA2, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 11, 100.0-wtSoda, tNA2-273.15);

         printf("9");
	 tinc = -25.0;
	 count = 0;
	 do {
           actLiq(SECOND, tNA9, p, x, NULL, mu, NULL, NULL);	 
	   gibbs(tNA9, p, (char *) solids[nNA9].label, &(solids[nNA9].ref), NULL, NULL, &(solids[nNA9].cur));
	   resid = (9.0*mu[1]/2.0+mu[3]/2.0-solids[nNA9].cur.g)/1000.0;
	   /* liquid too stable, temperature too high */
	   if ((resid < 0.0) && (tinc > 0.0)) tinc *= -0.5; 
	   /* solid too stable,  temperature too low  */
	   else if ((resid > 0.0) && (tinc < 0.0)) tinc *= -0.5;
	   tNA9 += tinc;
	   count++;
	   if (tNA9 < 800.0) { count = 100; tNA9 = 2000.0; } 
	   /* printf("tNA9 = %f, resid = %g, count = %d\n", tNA9, resid, count); */
	 } while ((fabs(resid) > 0.00001) && (count < 100));
         if (count < 100) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 12, 100.0-wtSoda, tNA9-273.15);

	 }
         
	 printf("\n");
       }

       if ((type == 31) || (type == 41) || (type == 51) || (type == 6)) setModeToMixingLiq(TRUE);
       if ((type ==  4) || (type == 41)) smixLiq(FIRST, t, p, x, &smix, NULL, NULL, NULL);
       if ((type ==  5) || (type == 51)) hmixLiq(FIRST, t, p, x, &hmix, NULL);
       if ((type ==  3) || (type == 31)) gmixLiq(FIRST, t, p, x, &gmix, NULL, NULL);
       if (type == 6) actLiq(FIRST, t, p, x, mu, NULL, NULL, NULL);
       if ((type == 31) || (type == 41) || (type == 51) || (type == 6)) setModeToMixingLiq(FALSE);
       
       if ((type ==  4) || (type == 41)) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 5, wtSoda, smix);
       if ((type ==  5) || (type == 51)) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 7, wtSoda, hmix/1000.0);
       if ((type ==  3) || (type == 31)) GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, wtSoda, gmix/1000.0);
       if ( type ==  1) for (j=10; j<(10+13); j++) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", j, wtSoda, xSpecies[list[j-10]]);
       if (type == 6) {
         GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 0, wtSoda, mu[0]);
         GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, wtSoda, mu[1]);
         GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 2, wtSoda, mu[3]);
       }

       GracePrintf("REDRAW\n");
     }
   }
   
   free_vector(    grams, 0, nlc-1);
   free_vector(    moles, 0, nlc-1);
   free_vector(        x, 0, nr-1);
   free_vector(       mu, 0, nlc-1);
   free_vector( xSpecies, 0, nls-1);
    
   return 0;
}

/* End file: TEST_SACNK.C */
