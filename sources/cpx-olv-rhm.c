#include "silmin.h"
#include "recipes.h"

#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"

int calculationMode = MODE_DEFAULT;

void *main_window, *silmin_adb, *topLevel, *meltsEnviron;
SilminState *silminState;

int main() {
  double t, p, *oOlv, *oCpx, *oIlm, rOlv[10], rCpx[10], rIlm[10], mOlv[10], mCpx[10], mIlm[10], logfO2;
  double eOlv[106], eCpx[106], eIlm[106]; 
  double muFa, muDi, muEn, muHd, muGk, muHm, muIl, muFs;
  int i, j, nOlv, nCpx, nIlm, converged, nFa, nDi, nEn, nHd, nGk, nHm, nIl, first, iters;
  float ftemp;

  calculationMode = MODE__MELTS;
  liquid = meltsLiquid;
  solids = meltsSolids;
  nlc = meltsNlc;
  nls = meltsNls;
  npc = meltsNpc;
  
  oOlv = (double *) malloc ((size_t) nc*sizeof(double));
  oCpx = (double *) malloc ((size_t) nc*sizeof(double));
  oIlm = (double *) malloc ((size_t) nc*sizeof(double));

  printf("Calling function: InitComputeDataStruct().\n");
  InitComputeDataStruct();

  t = 1000.0;
  for (i=0; i<npc; i++) {
    if (!strcmp("olivine",       solids[i].label)) nOlv = i;
    if (!strcmp("clinopyroxene", solids[i].label)) nCpx = i; 
    if (!strcmp("rhm-oxide",     solids[i].label)) nIlm = i; 
  }
  
  p = 1000.0;
  printf("Input a pressure in (bars):"); scanf("%f", &ftemp); p = (double) ftemp;
  getchar();
  
olivine:  
  for (j=0; j<106; j++) eOlv[j] = 0.0;
  for (i=0; i<nc; i++) {
    printf("Input a wt%% %s in olivine:", bulkSystem[i].label);       
    scanf("%f", &ftemp); oOlv[i] = ((double) ftemp)/bulkSystem[i].mw;
    getchar();
    for (j=0; j<106; j++) eOlv[j] += oOlv[i]*(bulkSystem[i].oxToElm)[j];
  }
  (*solids[nOlv].convert)(FIRST, SECOND, t, p, eOlv, mOlv, NULL, NULL, NULL, NULL, NULL, NULL);
  if (!(*solids[nOlv].test)(SIXTH, t, p, 0, 0, NULL, NULL, NULL, mOlv)) {
    printf("The olivine composition entered is infeasible for the solution model.  Please try again.\n"); 
    goto olivine;
  }
  (*solids[nOlv].convert)(SECOND, THIRD, t, p, NULL, mOlv, rOlv, NULL, NULL, NULL, NULL, NULL);

clinopyroxene:  
  for (j=0; j<106; j++) eCpx[j] = 0.0;
  for (i=0; i<nc; i++) {
    printf("Input a wt%% %s in clinopyroxene:", bulkSystem[i].label); 
    scanf("%f", &ftemp); oCpx[i] = ((double) ftemp)/bulkSystem[i].mw;
    getchar();
    for (j=0; j<106; j++) eCpx[j] += oCpx[i]*(bulkSystem[i].oxToElm)[j];
  }
  (*solids[nCpx].convert)(FIRST, SECOND, t, p, eCpx, mCpx, NULL, NULL, NULL, NULL, NULL, NULL);
  if (!(*solids[nCpx].test)(SIXTH, t, p, 0, 0, NULL, NULL, NULL, mCpx)) {
    printf("The clinopyroxene composition entered is infeasible for the solution model.  Please try again.\n"); 
    goto clinopyroxene;
  }
  (*solids[nCpx].convert)(SECOND, THIRD, t, p, NULL, mCpx, rCpx, NULL, NULL, NULL, NULL, NULL);
  
ilmenite:  
  for (j=0; j<106; j++) eIlm[j] = 0.0;
  for (i=0; i<nc; i++) {
    printf("Input a wt%% %s in ilmenite:", bulkSystem[i].label);      
    scanf("%f", &ftemp); oIlm[i] = ((double) ftemp)/bulkSystem[i].mw;
    getchar();
    for (j=0; j<106; j++) eIlm[j] += oIlm[i]*(bulkSystem[i].oxToElm)[j];
  }
  (*solids[nIlm].convert)(FIRST, SECOND, t, p, eIlm, mIlm, NULL, NULL, NULL, NULL, NULL, NULL);
  if (!(*solids[nIlm].test)(SIXTH, t, p, 0, 0, NULL, NULL, NULL, mIlm)) {
    printf("The ilmenite composition entered is infeasible for the solution model.  Please try again.\n"); 
    goto ilmenite;
  } 
  (*solids[nIlm].convert)(SECOND, THIRD, t, p, NULL, mIlm, rIlm, NULL, NULL, NULL, NULL, NULL);
  
  nFa = nOlv + 2;
  nDi = nCpx + 1;
  nEn = nCpx + 2;
  nHd = nCpx + 3;
  nGk = nIlm + 1;
  nHm = nIlm + 2;
  nIl = nIlm + 3;
  
  converged = 0;
  first = 1;
  iters = 0;
  while (!converged && (iters < 100)) {
    static double fold, told;
    double mu[10], f, df;
    
    gibbs(t, p, (char *) solids[nFa].label, &(solids[nFa].ref), NULL, NULL, &(solids[nFa].cur));
    gibbs(t, p, (char *) solids[nDi].label, &(solids[nDi].ref), NULL, NULL, &(solids[nDi].cur));
    gibbs(t, p, (char *) solids[nEn].label, &(solids[nEn].ref), NULL, NULL, &(solids[nEn].cur));
    gibbs(t, p, (char *) solids[nHd].label, &(solids[nHd].ref), NULL, NULL, &(solids[nHd].cur));
    gibbs(t, p, (char *) solids[nGk].label, &(solids[nGk].ref), NULL, NULL, &(solids[nGk].cur));
    gibbs(t, p, (char *) solids[nHm].label, &(solids[nHm].ref), NULL, NULL, &(solids[nHm].cur));
    gibbs(t, p, (char *) solids[nIl].label, &(solids[nIl].ref), NULL, NULL, &(solids[nIl].cur));
    
    (*solids[nOlv].activity)(SECOND, t, p, rOlv, NULL, mu, NULL);
    muFa = (solids[nFa].cur).g + mu[1];
    
    (*solids[nCpx].activity)(SECOND, t, p, rCpx, NULL, mu, NULL);
    muDi = (solids[nDi].cur).g + mu[0];
    muEn = (solids[nEn].cur).g + mu[1];
    muHd = (solids[nHd].cur).g + mu[2];
    muFs = 2.0*muHd - 2.0*muDi + muEn;
    
    (*solids[nIlm].activity)(SECOND, t, p, rIlm, NULL, mu, NULL);
    muGk = (solids[nGk].cur).g + mu[0];
    muHm = (solids[nHm].cur).g + mu[1];
    muIl = (solids[nIl].cur).g + mu[2];
    
    f = muHd + muGk - muDi - muIl;
    
    if (first) {
      fold = f;
      told = t;
      t += 20.0;
      first = 0;
    } else {
      df = (f - fold)/(t - told);
      fold = f;
      told = t;
      t += (df != 0.0) ? -f/df : 0.0;
      if (t <  500.0) t = 500.0;
      if (t > 2500.0) t = 2500.0;
    }
    
    if (fabs(t-told) < 0.01) converged = 1;
    printf("...Iteration %3.3d for t = %lf, f (optimally zero) = %lf\n", iters, t-273.15, f);
    iters++;
  }
  printf("Final converged T (C) = %lf\n", t - 273.15);
  
  gibbs(t, p, "o2", &(oxygen.ref), NULL, NULL, &(oxygen.cur));
  logfO2 = 2.0*(muFs + muHm - 2.0*muFa) - (oxygen.cur).g;
  logfO2 /= 8.3143*t*log(10.0);
  printf("Oxygen fugacity (log 10) = %lf, relative to NNO = %lf\n", logfO2, logfO2 - (-24930.0/t +  9.360));

  return 0;
}

