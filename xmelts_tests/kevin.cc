#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <float.h>
#include <unistd.h>

#include "adolc.h"

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

extern "C" { int data (const char *phase, const char *component, double *param); }
extern "C" { void getPhaseResults(double t, double *alloy, double *results); }

static adouble plg (adouble t) {

/*-----------------------------------------------------------------------*/
/* 29th order series expansion of polylog terms in sixtrude's EoS about  */
/* t = 0, good to 0.0001 accuracy to t = 5.                              */
/* f := int((ln(1-exp(-t))*t^2),t=0..TD);                                */
/* gg := convert(series(f,TD=0,29),polynom);                             */
/*-----------------------------------------------------------------------*/

  adouble c2, result;
  c2 = 0.1111111111111111111;

  result  = t*t*t*(
            log(t)/3.0
	  - c2 
          - t/8.0 
	  + t*t/120.0	  
          - pow(t,  4.0)/20160.0 
	  + pow(t,  6.0)/1632960.0 
	  - pow(t,  8.0)/106444800.0
          + pow(t, 10.0)/6227020800.0 
	  - 0.2935661189e-11*pow(t, 12.0) 
          + 0.562291451e-13 *pow(t, 14.0) 
	  - 0.1115026413e-14*pow(t, 16.0)
          + 0.2271444989e-16*pow(t, 18.0) 
	  - 0.4727975432e-18*pow(t, 20.0)
          + 0.1001636878e-19*pow(t, 22.0) 
	  - 0.2153466772e-21*pow(t, 24.0)
	  );
  return result;
}

adouble helmholtz (adouble t, adouble v, double *params) {
  int itic; 
  adouble tr, r, a0, n, v0, k00, k0p, theta0, gamma0, q, refS;
  adouble f, a, c1, c2, c3, c5, c7, f1, tht, tht0, d0;

  tr    = 300.00;
  r     = 8.314472;

/*
    Test data - forsterite joules and bars
           1      2       3         4    5      6     7    8      9
          f0     -n     -v0        k0  k0'     td  gam0   q0  etaS0
    -2055000.   -7.   -4.36  1.28E+06  4.2  809.0  0.99  2.1    2.4
*/
  
  a0	 = params[0]; /*  1 J/m     */
  n	 = params[1]; /*  2         */
  v0	 = params[2]; /*  3 J/bar-m */
  k00	 = params[3]; /*  4 bar     */
  k0p	 = params[4]; /*  5         */
  theta0 = params[5]; /*  6 K       */
  gamma0 = params[6]; /*  7         */
  q	 = params[7]; /*  8         */
  refS   = params[8]; /* 10         */

  c1   = 9.0*k00*v0;
  c2   = k0p/2.0 - 2.0;
  c3   = 3.0*c1*c2;
  c5   = 3.0*gamma0;
  c7   = c5*(-2.0 + 6.0*gamma0 - 3.0*q);
  
  f1   = 1.0e9;
  itic = 0; 

  f    = 0.5*pow(v0/v, 2.0/3.0) - 0.5;
  d0   = sqrt(1.0 + c7*f*f + 2.0*c5*f);
  tht  = theta0/t*d0;
  tht0 = tht*t/tr;

  a = a0 + c1*f*f*(0.5 + c2*f) + 9.0*n*r*(t/(tht*tht*tht)*plg(tht) - tr/(tht0*tht0*tht0)*plg(tht0)) - t*refS;

  return a;
} 

double computeStix(double t, double targetP, double *params) {
  static double **H;
  double result, x[2], g[2], p, s, v;
  adouble at, av, aresult;
  int i, flag, iter;

  if (H == NULL) {
    H = (double **) malloc((size_t) 2*sizeof(double *));
    for (i=0; i<2; i++) H[i] = (double *) malloc((size_t) (i+1)*sizeof(double));
  }
  
  v       = params[2]*0.90;  
  x[0] = t;
  x[1] = v;

  trace_on(1);
    at <<= x[0];
    av <<= x[1];
    aresult = helmholtz (at, av, params);
    aresult >>= result;
  trace_off();
  
  flag = gradient(1, 2, x, g);
  p = -g[1];

  iter = 0; 
  while ((fabs(p-targetP) > 0.1) && (iter < 100)) {
    double f, df;
    flag = gradient(1, 2, x, g); if (flag < 0) printf("ADOL incorrect approximation.\n"); 
    flag = hessian(1, 2, x, H);
    p = -g[1];
    f  = p - targetP;
    df = -H[1][1];
    v -= f/df;
    x[1] = v;
    iter++;
  }
  
  flag = function(1, 1, 2, x, &result);

  flag = gradient(1, 2, x, g);
  s = -g[0];
  p = -g[1];

  return result + p*v;
}

int main(int argc, char*argv[]) {
	int i, j;
	float ftemp;
	double t, p0 = 1.0, p, gramsAlloy[5], results[3], logfO2, intV0;
	double gFa, gWd, gRg, gPv, gFs, gWu, deltaG;
	double K  = 206.0;
	double Kp = 4.0;
	double Wolv =  5300.0;
    double Wwad =  6100.0;
    double Wrgw =  3500.0;
    double Wpv  = 12000.0;
    double Wwus = 13000.0;
	double Xfay = 0.1;
	double Xwad = 0.1;
	double Xrgw = 0.1;
	double Xpv = 0.1;
	double Xopx = 0.1;
	double Xwus = 0.2;
	double params[9];
  
    printf("t (K), p (GPa), fa-opx, wd-opx, rg-opx, wu\n");
    
    for (i=0; i<11; i++) {
    
    if      (i ==  0) { t = 1973.0;  p =      1.0; }
    else if (i ==  1) { t = 1994.0;  p =  20000.0; }
    else if (i ==  2) { t = 2025.5;  p =  50000.0; }
    else if (i ==  3) { t = 2078.0;  p = 100000.0; }
    else if (i ==  4) { t = 2183.0;  p = 200000.0; }
    else if (i ==  5) { t = 2235.5;  p = 250000.0; }
    else if (i ==  6) { t = 2288.0;  p = 300000.0; }
    else if (i ==  7) { t = 2340.5;  p = 350000.0; }
    else if (i ==  8) { t = 2393.0;  p = 400000.0; }
    else if (i ==  9) { t = 2445.5;  p = 450000.0; }
    else if (i == 10) { t = 2498.0;  p = 500000.0; }
    
    printf("%g, %g, ", t, p/10000.0);

    gramsAlloy[0] =  0.0; // O
    gramsAlloy[1] =  0.0; // S
    gramsAlloy[2] = 90.0; // Fe
    gramsAlloy[3] = 10.0; // Ni
    gramsAlloy[4] =  0.0; // Cu
                
	getPhaseResults(t, gramsAlloy, results);
	intV0 = intVinet(p, results[2], K, Kp);
	//printf("mu Fe in sulfide liquid: %20.13g\n", results[0]);
	//printf("mu O2 gas:               %20.13g\n", results[1]);
	//printf("v0 Fe in sulfide liquid: %20.13g\n", results[2]);
	//printf("int v0 Fe (1 to p):      %20.13g\n", intV0);
   
    // 2 Fe (alloy) + O2 (gas) + (1/2)Fe4Si4O12 (opx) = 2 Fe2SiO4 (olv,wads,ringw)
        
	(void) data("olivine", "fayalite", params); 	  /* Fe2SiO4 */
    gFa = computeStix(t, p, params);
    gFa += 8.3143*t*2.0*log(Xfay) + Wolv*pow(1.0-Xfay, 2.0);
    
    (void) data("wadsleyite", "fe-wadsleyite", params);   /* Fe2SiO4 */
    gWd =  computeStix(t, p, params);
    gWd += 8.3143*t*2.0*log(Xwad) + Wwad*pow(1.0-Xwad, 2.0);
    
    (void) data("ringwoodite", "fe-ringwoodite", params); /* Fe2SiO4 */
    gRg =  computeStix(t, p, params);
    gRg += 8.3143*t*2.0*log(Xrgw) + Wrgw*pow(1.0-Xrgw, 2.0);
    
    (void) data("perovskite", "fe-perovskite", params);   /* FeSiO3 */
    gPv = computeStix(t, p, params);
    gPv += 8.3143*t*log(Xpv) + Wpv*pow(1.0-Xpv, 2.0);

    (void) data("orthopyroxene", "ferrosilite", params);  /* Fe4S4O12 */
    gFs =  computeStix(t, p, params);
    gFs += 8.3143*t*4.0*log(Xopx);

    // 2 Fe (alloy) + O2 (gas) = 2 FeO (wuestite)
   
    (void) data("magnesiowustite", "wuestite", params);   /* FeO */
    gWu = computeStix(t, p, params);
    gWu += 8.3143*t*log(Xwus) + Wwus*pow(1.0-Xwus, 2.0);
    
    // deltaG
    
    deltaG = 2.0*gFa - 0.5*gFs - 2.0*(results[0] + intV0) - results[1];
	logfO2 = deltaG/(8.3143*t*log(10.0));
	printf("%20.13g, ", logfO2);
       
    deltaG = 2.0*gWd - 0.5*gFs - 2.0*(results[0] + intV0) - results[1];
	logfO2 = deltaG/(8.3143*t*log(10.0));
	printf("%20.13g, ", logfO2);
       
    deltaG = 2.0*gRg - 0.5*gFs - 2.0*(results[0] + intV0) - results[1];
	logfO2 = deltaG/(8.3143*t*log(10.0));
	printf("%20.13g, ", logfO2);
       
    deltaG = 2.0*gWu - 2.0*(results[0] + intV0) - results[1];
	logfO2 = deltaG/(8.3143*t*log(10.0));
	printf("%20.13g\n", logfO2);
	
	}
       
	exit(0);
}
