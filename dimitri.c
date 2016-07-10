#include "silmin.h"
#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"

void propertiesOfPureH2O(double t, double p, 
     double *g, double *h, double *s, double *cp, double *dcpdt,
     double *v, double *dvdt, double *dvdp, double *d2vdt2, double *d2vdtdp, double *d2vdp2);
void propertiesOfPureCO2(double t, double p, 
     double *g, double *h, double *s, double *cp, double *dcpdt,
     double *v, double *dvdt, double *dvdp, double *d2vdt2, double *d2vdtdp, double *d2vdp2);
     
void actFlu(int mask, double t, double p, double *r, double *a,  double *mu, double **dx); 
void gmixFlu(int mask, double t, double p, double *r, double *gmix, double *dx, double **dx2, double ***dx3);
void hmixFlu(int mask, double t, double p, double *r, double *hmix);
void smixFlu(int mask, double t, double p, double *r, double *smix, double *dx, double **dx2);
void cpmixFlu(int mask, double t, double p, double *r, double *cpmix, double *dt, double *dx);
void vmixFlu(int mask, double t, double p, double *r, double *vmix, double *dx,   double **dx2, 
  double *dt, double *dp, double *dt2, double *dtdp, double *dp2, double *dxdt, double *dxdp);
  
int calculationMode = MODE_DEFAULT;

void *main_window, *silmin_adb, *topLevel, *meltsEnviron;
SilminState *silminState;

int main() {
  FILE *output;
  double t, p, r[1], a[2], mu[2];
  double gmix, hmix, smix, cpmix, dcpdtmix, vmix, dvdtmix, dvdpmix, d2vdt2mix, d2vdtdpmix, d2vdp2mix;
  double gH2O, hH2O, sH2O, cpH2O, dcpdtH2O, vH2O, dvdtH2O, dvdpH2O, d2vdt2H2O, d2vdtdpH2O, d2vdp2H2O;
  double gCO2, hCO2, sCO2, cpCO2, dcpdtCO2, vCO2, dvdtCO2, dvdpCO2, d2vdt2CO2, d2vdtdpCO2, d2vdp2CO2;
  
  double pRange[ 3] = { 10000.0, 25000.0, 50000.0 }; // bars
  double tRange[ 4] = { 873.15, 973.15, 1073.15, 1173.15 };           // K
  double xRange[17] = { 0.001, 0.002, 0.005, 0.01, 0.02, 0.03, 0.04, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };
  
  int i, j, k;
  
  InitComputeDataStruct();
  output = fopen ("dimitri.csv", "w");
  
  fprintf(output, "p, t, xCO2, gH2O, hH2O, sH2O, cpH2O, dcpdtH2O, vH2O, dvdtH2O, dvdpH2O, d2vdt2H2O, d2vdtdpH2O, d2vdp2H2O,");
  fprintf(output,             "gCO2, hCO2, sCO2, cpCO2, dcpdtCO2, vCO2, dvdtCO2, dvdpCO2, d2vdt2CO2, d2vdtdpCO2, d2vdp2CO2,");
  fprintf(output, "a[H2O], a[CO2], muMix[H2O], muMix[CO2],");
  fprintf(output,             "gmix, hmix, smix, cpmix, dcpdtmix, vmix, dvdtmix, dvdpmix, d2vdt2mix, d2vdtdpmix, d2vdp2mix\n");
  
  for (i=0; i<3; i++) {
    p = pRange[i];
    
    for (j=0; j<4; j++) {
      t = tRange[j];
      
      printf("<><><> p = %f, t = %f\n", p/1000.0, t-273.15);
      
      propertiesOfPureH2O(t, p, &gH2O, &hH2O, &sH2O, &cpH2O, &dcpdtH2O, &vH2O, &dvdtH2O, &dvdpH2O, &d2vdt2H2O, &d2vdtdpH2O, &d2vdp2H2O);
      propertiesOfPureCO2(t, p, &gCO2, &hCO2, &sCO2, &cpCO2, &dcpdtCO2, &vCO2, &dvdtCO2, &dvdpCO2, &d2vdt2CO2, &d2vdtdpCO2, &d2vdp2CO2);
      
      for (k=0; k<17; k++) {
        r[0] = xRange[k];
        
        printf("  <><> x = %f\n", r[0]);
        
        actFlu(  FIRST | SECOND,                                    t, p, r, a, mu, NULL); 
        gmixFlu( FIRST,                                             t, p, r, &gmix, NULL, NULL, NULL);
        hmixFlu( FIRST,                                             t, p, r, &hmix);
        smixFlu( FIRST,                                             t, p, r, &smix, NULL, NULL);
        cpmixFlu(FIRST | SECOND,                                    t, p, r, &cpmix, &dcpdtmix, NULL);
        vmixFlu( FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, t, p, r, &vmix, NULL, NULL, &dvdtmix, &dvdpmix, &d2vdt2mix, &d2vdtdpmix, &d2vdp2mix, NULL, NULL);
        
        fprintf(output, "%e, %e, %e, ", p/1000.0, t-273.15, r[0]);
        fprintf(output, "%e, %e, %e, %e, %e, %e, %e, %e, %e, %e, %e, ", gH2O, hH2O, sH2O, cpH2O, dcpdtH2O, vH2O, dvdtH2O, dvdpH2O, d2vdt2H2O, d2vdtdpH2O, d2vdp2H2O);
        fprintf(output, "%e, %e, %e, %e, %e, %e, %e, %e, %e, %e, %e, ", gCO2, hCO2, sCO2, cpCO2, dcpdtCO2, vCO2, dvdtCO2, dvdpCO2, d2vdt2CO2, d2vdtdpCO2, d2vdp2CO2);
        fprintf(output, "%e, %e, %e, %e, ", a[0], a[1], mu[0], mu[1]);
        fprintf(output, "%e, %e, %e, %e, %e, %e, %e, %e, %e, %e, %e\n", gmix, hmix, smix, cpmix, dcpdtmix, vmix, dvdtmix, dvdpmix, d2vdt2mix, d2vdtdpmix, d2vdp2mix);
        
      }
    }
  }
  
  fclose(output);
  return 0;
}