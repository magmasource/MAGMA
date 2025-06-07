#include "silmin.h"
#include "recipes.h"

#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"

SilminState *silminState;
int calculationMode = MODE_DEFAULT;

void getPhaseResults(double t, double *alloy, double *results);

double intVinet(double p, double v0, double K, double Kp) {
    double eta = 3.0*(Kp-1.0)/2.0;
    double x   = 1.0;
    double x0  = 1.0;
    double pr  = 1.0;
    double fn, dfn, a;
    int iter;
    
    iter = 0;
    do {
      fn = x*x*(p/10000.0) - 3.0*K*(1.0-x)*exp(eta*(1.0-x));
      dfn = 2.0*x*(p/10000.0) + 3.0*K*(1.0+eta*(1.0-x))*exp(eta*(1.0-x));
      x = x - fn/dfn;
      iter++;
    } while ((iter < 500) && (fn*fn > DBL_EPSILON));
    
    iter = 0;
    do {
      fn = x0*x0*(pr/10000.0) - 3.0*K*(1.0-x0)*exp(eta*(1.0-x0));
      dfn = 2.0*x0*(pr/10000.0) + 3.0*K*(1.0+eta*(1.0-x0))*exp(eta*(1.0-x0));
      x0 = x0 - fn/dfn;
      iter++;
    } while ((iter < 500) && (fn*fn > DBL_EPSILON));

    a  = (9.0*v0*K/(eta*eta))*(1.0 - eta*(1.0-x ))*exp(eta*(1.0-x))   - 9.0*v0*K/(eta*eta);   
    a -= (9.0*v0*K/(eta*eta))*(1.0 - eta*(1.0-x0))*exp(eta*(1.0-x0)) - 9.0*v0*K/(eta*eta);
    
    return (-a*1000.0 + p*v0*x*x*x/10.0 - pr*v0*x0*x0*x0/10.0);
}

int main(int argc, char*argv[]) {
   int i, j;
   int nr = nlc - 1;
   float ftemp;
   double t, p0 = 1.0, p, *grams, gramsAlloy[5], *moles, *temp, *x, *mu, results[3], logfO2, intV0;
   double K  = 206.0;
   double Kp = 4.0;

   InitComputeDataStruct();
   setModeToMixingLiq(FALSE);

   if (argc == 1) {
     printf("Input a temperature in (C):"); scanf("%f", &ftemp); t = ((double) ftemp)+273.15; getchar();
     printf("Input a pressure in (bars):"); scanf("%f", &ftemp); p = (double) ftemp;          getchar();
   } else {
     t = atof(argv[1]) + 273.15;
     p = atof(argv[2]);
   }

   moles = (double *) malloc((size_t) nlc*sizeof(double));
   grams = (double *) malloc((size_t)  nc*sizeof(double));
   temp  = (double *) malloc((size_t)  nc*sizeof(double));
   x     = (double *) malloc((size_t)  nr*sizeof(double));
   mu    = (double *) malloc((size_t) nlc*sizeof(double));

   for (i=0; i<nc; i++) {
     if (argc == 1) {
       printf("Input wt%% of %5.5s in silicate liquid: ", bulkSystem[i].label);
       scanf("%f", &ftemp); grams[i] = (double) ftemp; getchar();
     } else {
       grams[i] = atof(argv[3+i]);
     }
     temp[i] = grams[i]/bulkSystem[i].mw;
   }
   for (i=0; i<nlc; i++) for (j=0,moles[i]=0.0; j<nc; j++) moles[i] += temp[j]*(bulkSystem[j].oxToLiq)[i];
   
   if (argc == 1) {
     printf("Input wt%% of  O in alloy: "); scanf("%f", &ftemp); gramsAlloy[0] = (double) ftemp; getchar();
     printf("Input wt%% of  S in alloy: "); scanf("%f", &ftemp); gramsAlloy[1] = (double) ftemp; getchar();
     printf("Input wt%% of Fe in alloy: "); scanf("%f", &ftemp); gramsAlloy[2] = (double) ftemp; getchar();
     printf("Input wt%% of Ni in alloy: "); scanf("%f", &ftemp); gramsAlloy[3] = (double) ftemp; getchar();
     printf("Input wt%% of Cu in alloy: "); scanf("%f", &ftemp); gramsAlloy[4] = (double) ftemp; getchar();
   } else {
     gramsAlloy[0] = atof(argv[3+nc+0]);
     gramsAlloy[1] = atof(argv[3+nc+1]);
     gramsAlloy[2] = atof(argv[3+nc+2]);
     gramsAlloy[3] = atof(argv[3+nc+3]);
     gramsAlloy[4] = atof(argv[3+nc+4]);
   }
      
   conLiq(SECOND, THIRD, t, p, NULL, moles, x, NULL, NULL, NULL, NULL);
   
   actLiq(SECOND, t, p0, x, NULL, mu, NULL, NULL); 
   if (argc == 1) printf("mu SiO2 (xMELTS, p0):    %20.13g\n", mu[0]);
   if (argc == 1) printf("mu Fe2SiO4 (xMELTS, p0): %20.13g\n", mu[5]);
   
   logfO2 = -(mu[0] - mu[5]);

   actLiq(SECOND, t, p, x, NULL, mu, NULL, NULL); 
   if (argc == 1) printf("mu SiO2 (xMELTS, p):     %20.13g\n", mu[0]);
   if (argc == 1) printf("mu Fe2SiO4 (xMELTS, p):  %20.13g\n", mu[5]);
   
   logfO2 += mu[0] - mu[5];

   calculationMode = MODE__MELTS;
   liquid = meltsLiquid;
   solids = meltsSolids;
   nlc = meltsNlc;
   nls = meltsNls;
   npc = meltsNpc;
   InitComputeDataStruct();
   setModeToMixingLiq(FALSE);
   
   for (i=0; i<nlc; i++) for (j=0,moles[i]=0.0; j<nc; j++) moles[i] += temp[j]*(bulkSystem[j].oxToLiq)[i];
   conLiq(SECOND, THIRD, t, p, NULL, moles, x, NULL, NULL, NULL, NULL);  
    
   actLiq(SECOND, t, p0, x, NULL, mu, NULL, NULL); 
   gibbs(t, p0, (char *) liquid[0].label, &(liquid[0].ref), &(liquid[0].liq), &(liquid[0].fus), &(liquid[0].cur));
   gibbs(t, p0, (char *) liquid[5].label, &(liquid[5].ref), &(liquid[5].liq), &(liquid[5].fus), &(liquid[5].cur));
   if (argc == 1) printf("mix SiO2 (MELTS, p0):    %20.13g\n", mu[0]);
   if (argc == 1) printf("mix Fe2SiO4 (MELTS, p0): %20.13g\n", mu[5]);
   if (argc == 1) printf("mu SiO2 (MELTS, p0):     %20.13g\n", mu[0]+(liquid[0].cur).g);
   if (argc == 1) printf("mu Fe2SiO4 (MELTS, p0):  %20.13g\n", mu[5]+(liquid[5].cur).g);
   
   logfO2 += mu[0]+(liquid[0].cur).g - (mu[5]+(liquid[5].cur).g);
      
   getPhaseResults(t, gramsAlloy, results);
   intV0 = intVinet(p, results[2], K, Kp);
   
   if (argc == 1) printf("mu Fe in sulfide liquid: %20.13g\n", results[0]);
   if (argc == 1) printf("mu O2 gas:               %20.13g\n", results[1]);
   if (argc == 1) printf("v0 Fe in sulfide liquid: %20.13g\n", results[2]);
   if (argc == 1) printf("int v0 Fe (1 to p):      %20.13g\n", intV0);
   
   logfO2 += results[1] + 2.0*(results[0] + intV0);
   logfO2 /= -8.3143*t*log(10.0);
   
   if (argc == 1) printf("log10 fO2:               %20.13g\n", logfO2);
   else           printf("\n%20.13g\n", logfO2);
   
   free(moles);
   free(grams);
   free(temp);
   free(x);
   free(mu);
    
   exit(0);
}
