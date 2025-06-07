
/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Test routine to evaluate entropies of fusion (file: TEST_ENTROPY.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  September 27, 1994 Original Version
**              Canabalized test_gibbs.c
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
SilminState *silminState;
void *main_window, *silmin_adb, *topLevel, *meltsEnviron;

int main()
{
  int i, j, k, l;
  double t, p, *rLiq, *xLiq;
  FILE *output;
  struct _fusion {
    const char *name;
    const char *formula;
    double     t;
    double     p;
    double     s;
    double     error;
  } fusion[] = {
    {"akermanite",	   "Ca2MgSi2O7",     1727.0,  1.0,  71.7,  1.9},
    {"albite",  	   "NaAlSi3O8",      1373.0,  1.0,  45.7,  1.5},
    {"albite",  	   "NaAlSi3O8",      1373.0,  1.0,  46.2,  2.2},
    {"albite",  	   "NaAlSi3O8",      1393.0,  1.0,  46.3,  2.2},
    {"anorthite",	   "CaAl2Si2O8",     1830.0,  1.0,  74.1,  4.8},
    {"anorthite",	   "CaAl2Si2O8",     1830.0,  1.0,  72.7,  2.2},
    {"clinoenstatite",     "Mg2Si2O6",       1834.0,  1.0,  79.8,  6.6},
    {"co-olivine",	   "Co2SiO4",	     1688.0,  1.0,  58.0,  5.0},
    {"cordierite",	   "Mg2Al4Si5O18",   1740.0,  1.0, 199.0,  6.0},
    {"corundum",	   "Al2O3",	     2323.0,  1.0,  46.3,  2.3},
    {"cristobalite",	   "SiO2",	     1999.0,  1.0,   4.46, 0.5},
    {"diopside",	   "CaMgSi2O6",      1670.0,  1.0,  82.5,  1.2},
    {"fayalite",	   "Fe2SiO4",	     1490.0,  1.0,  59.9,  0.7},
    {"fluorphlogopite",    "KMg3AlSi3O10F2", 1670.0,  1.0, 185.0,  1.0},
    {"forsterite",	   "Mg2SiO4",	     2174.0,  1.0,  65.3,  6.0},
    {"gehlenite",	   "Ca2Al2SiO7",     1863.0,  1.0,  92.4,  3.2},
    {"hematite",	   "Fe2O3",	     1895.0,  1.0,  60.4,  0.0},
    {"ilmenite",	   "FeTiO3",	     1640.0,  1.0,  13.2,  0.1},
    {"jadeite", 	   "NaAlSi2O6",      1100.0,  1.0,  53.9,  2.7},
    {"kalsilite",	   "KAlSiO4",	     2023.0,  1.0,  24.5,  0.0},
    {"kdisilicate",	   "K2Si2O5",	     1309.0,  1.0,  24.3,  3.6},
    {"kdisilicate",	   "K2Si2O5",	     1318.0,  1.0,  24.3,  3.0},
    {"kmsilicate",	   "K2SiO3",	     1249.0,  1.0,  15.7,  3.2},
    {"larnite", 	   "Ca2SiO4",	     2403.0,  1.0,  75.74, 0.0},
    {"magnetite",	   "Fe3O4",	     1870.0,  1.0,  73.84, 0.0},
    {"mgchromite",	   "MgCr2O4",	     2673.15, 1.0,  73.22, 0.0},
    {"nadisilicate",	   "Na2Si2O5",       1147.0,  1.0,  38.7,  3.6},
    {"nadisilicate",	   "Na2Si2O5",       1147.0,  1.0,  32.9,  3.8},
    {"namsilicate",	   "Na2SiO3",	     1361.0,  1.0,  38.34, 0.5},
    {"namsilicate",	   "Na2SiO3",	     1362.0,  1.0,  38.2,  0.7},
    {"nepheline",	   "NaAlSiO4",       1750.0,  1.0,  28.0,  1.2},
    {"nepheline",	   "NaAlSiO4",       1720.0,  1.0,  26.9,  1.2},
    {"ni-olivine",	   "Ni2SiO4",	     1923.0,  1.0,  58.0,  5.0},
    {"pseudowollastonite", "CaSiO3",	     1817.0,  1.0,  31.50, 1.6},
    {"pyrope",  	   "Mg3Al2Si3O12",   1500.0,  1.0, 162.0,  5.0},
    {"pyrope",  	   "Mg3Al2Si3O12",   1570.0,  1.0, 154.1,  7.6},
    {"quartz",  	   "SiO2",	     1700.0,  1.0,   5.53, 0.56},
    {"rutile",  	   "TiO2",	     1870.0,  1.0,  35.8,  0.0},
    {"sanidine",	   "KAlSi3O8",       1473.0,  1.0,  39.2,  2.8},
    {"sanidine",	   "KAlSi3O8",       1500.0,  1.0,  36.0,  2.7},
    {"sphene",  	   "CaTiSiO5",       1670.0,  1.0,  74.1,  0.2},
    {"spinel",  	   "MgAl2O4",	     2408.0,  1.0,  44.0,  4.0},
    {"tephroite",	   "Mn2SiO4",	     1620.0,  1.0,  55.2,  0.3},
    {"whitlockite",	   "Ca3(PO4)2",      1943.0,  1.0,  35.7,  0.0},
    {"wollastonite",	   "CaSiO3",	     1770.0,  1.0,  34.9,  2.3},
    {"wustite", 	   "Fe0.947O",       1652.0,  1.0,  19.0,  0.1} 
  };
  int nFus = (sizeof fusion / sizeof(struct _fusion));
  double *s0Cfg, *s0Fus, *h0Fus, *CPliq, *xSum, *xOSum, *xNSum;

  printf("Opening output file TEST_ENTROPY.OUT.\n");
  output = fopen ("test_entropy.out", "w");

  printf("Calling function: InitComputeDataStruct().\n");
  InitComputeDataStruct();

  printf("Computing fusion properties for selected solids.\n");
  rLiq   = (double *) malloc((size_t)  nlc*sizeof(double));
  xLiq   = (double *) malloc((size_t)  nls*sizeof(double));
  xSum   = (double *) calloc((size_t) nFus, sizeof(double));
  xOSum  = (double *) calloc((size_t) nFus, sizeof(double));
  xNSum  = (double *) calloc((size_t) nFus, sizeof(double));
  s0Fus  = (double *) calloc((size_t) nFus, sizeof(double));
  s0Cfg  = (double *) calloc((size_t) nFus, sizeof(double));
  h0Fus  = (double *) calloc((size_t) nFus, sizeof(double));
  CPliq  = (double *) calloc((size_t) nFus, sizeof(double));

  for (i=0; i<nFus; i++) {
    printf("Looking up solid properties for %s", fusion[i].name);
    for (j=0; j<npc; j++) {
      if ((solids[j].ref).h != 0.0 &&
          strcmp(fusion[i].name,    solids[j].label)   == 0 &&
          strcmp(fusion[i].formula, solids[j].formula) == 0) {
        fprintf(output, "%14.14s =", solids[j].label);
        for (k=0; k<nlc; k++) if( (solids[j].solToLiq)[k] != 0.0)
          fprintf(output, " %+5.2f %-10.10s", (solids[j].solToLiq)[k], 
            liquid[k].label);
        fprintf(output, "\n");
        j = -1;
	printf(" --- Found it!\n");
        break;
      }
    }
    if (j != -1) printf(" --- Properties not in solids[]!\n");
  }
  fprintf(output, "\n");

  for (i=0; i<nFus; i++) {
    printf("Computing fusion properties for %s.\n", fusion[i].name);
    t = fusion[i].t;
    p = fusion[i].p;
    for (j=0; j<npc; j++) {
      if ((solids[j].ref).h != 0.0 &&
          strcmp(fusion[i].name,    solids[j].label)   == 0 &&
          strcmp(fusion[i].formula, solids[j].formula) == 0) {
        double sum, sumOx, sumNew;
	int count;

        conLiq(SECOND, THIRD, t, p, NULL, solids[j].solToLiq, rLiq, NULL, NULL, NULL, NULL);
	if (testLiq(FIFTH, t, p, 0, 0, NULL, NULL, rLiq, NULL)) {
          hmixLiq (FIRST, t, p, rLiq, &h0Fus[i], NULL);
          smixLiq (FIRST, t, p, rLiq, &s0Fus[i], NULL, NULL, NULL);
          cpmixLiq(FIRST, t, p, rLiq, &CPliq[i], NULL, NULL);

          conLiq(THIRD, FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xLiq, NULL, NULL, NULL);
          for (k=0, sum=0.0;    k<nlc; k++) sum    += (solids[j].solToLiq)[k];
          for (k=0, sumOx=0.0;  k<nc;  k++) sumOx  += (solids[j].solToOx)[k];
          for (l=0, sumNew=0.0; l<nls; l++) for (k=0; k<nc;  k++) sumNew += xLiq[l]*(liquid[l].liqToOx)[k];

          h0Fus[i] *= sum; 
          s0Fus[i] *= sum; 
          CPliq[i] *= sum;
	  s0Cfg[i]  = s0Fus[i];
	  xSum[i]   = sum;
	  xOSum[i]  = sumOx;
	  xNSum[i]  = sumNew;
	  
	  for (k=0; k<nlc; k++) if ((solids[j].solToLiq)[k] != 0.0) {
	    gibbs(t, p, (char *) liquid[k].label, &(liquid[k].ref), &(liquid[k].liq), &(liquid[k].fus), &(liquid[k].cur));
	    h0Fus[i] += (solids[j].solToLiq)[k]*(liquid[k].cur).h;
	    s0Fus[i] += (solids[j].solToLiq)[k]*(liquid[k].cur).s;
	    CPliq[i] += (solids[j].solToLiq)[k]*(liquid[k].cur).cp;
          }

          gibbs(t, p, (char *) solids[j].label, &(solids[j].ref), NULL, NULL, &(solids[j].cur));
          h0Fus[i] -= (solids[j].cur).h;
          s0Fus[i] -= (solids[j].cur).s;

          fprintf(output, "%14.14s =", solids[j].label);        
          for (k=0, count=0; k<nls; k++) if (fabs(xLiq[k]) > 10.0*DBL_EPSILON) {
            if (count == 4) {
              fprintf(output, "\n");
              fprintf(output, "%14.14s  ", " ");
              count = 0;
            }
            fprintf(output, " %+13.6g %-10.10s", xLiq[k]*sumOx/sumNew, liquid[k].label); count++;
          }

          fprintf(output, "\n");
	} else printf("--> Generates negative mole fractions.\n");
        break;
      }
    }
  }
  fprintf(output, "\n");

  fprintf(output, "%14.14s ", "Name  ");
  fprintf(output, "%14.14s ", "Formula  ");
  fprintf(output, "%8.8s ",   "T (K) ");
  fprintf(output, "%6.6s ",   "sm liq");
  fprintf(output, "%6.6s ",   "sm oxd");
  fprintf(output, "%6.6s ",   "sm spc");
  fprintf(output, "%6.6s ",   "S conf");
  fprintf(output, "%6.6s ",   "S clac");
  fprintf(output, "%6.6s ",   "S meas");
  fprintf(output, "%6.6s ",   "S diff");
  fprintf(output, "%6.6s ",   "S +/- ");
  fprintf(output, "%6.6s ",   "H clac");
  fprintf(output, "%6.6s ",   "H meas");
  fprintf(output, "%6.6s ",   "H diff");
  fprintf(output, "%6.6s ",   "H +/- ");
  fprintf(output, "%6.6s ",   "Cp liq");
  fprintf(output, "\n");
  for (i=0; i<nFus; i++) if (s0Fus[i] != 0.0) {
    fprintf(output, "%14.14s %14.14s", fusion[i].name, fusion[i].formula);
    fprintf(output, "%8.2f ", fusion[i].t);
    fprintf(output, "%6.4f ", xSum[i]);
    fprintf(output, "%6.4f ", xOSum[i]);
    fprintf(output, "%6.4f ", xNSum[i]);
    fprintf(output, "%6.2f ", s0Cfg[i]);
    fprintf(output, "%6.2f ", s0Fus[i]);
    fprintf(output, "%6.2f ", fusion[i].s);
    fprintf(output, "%6.2f ", s0Fus[i]-fusion[i].s);
    if (fusion[i].error == 0.0) fprintf(output, "%6.6s ", " ");
    else                        fprintf(output, "%6.2f ", fusion[i].error);
    fprintf(output, "%6.2f ", h0Fus[i]/1000.0);
    fprintf(output, "%6.2f ", (fusion[i].t)*(fusion[i].s)/1000.0);
    fprintf(output, "%6.2f ", (h0Fus[i]-(fusion[i].t)*(fusion[i].s))/1000.0);
    if (fusion[i].error == 0.0) fprintf(output, "%6.6s ", " ");
    else                        fprintf(output, "%6.2f ", (fusion[i].t)*(fusion[i].error)/1000.0);
    fprintf(output, "%6.2f ", CPliq[i]);
    fprintf(output, "\n");
  }

  free(rLiq);
  free(xLiq);
  free(xSum);
  free(xOSum);
  free(xNSum);
  free(s0Fus);
  free(s0Cfg);
  free(h0Fus);
  free(CPliq); 
  fclose(output);
  
  exit(0);
}

/* End file: TEST_ENTROPY.C */

