#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static double v0;  
static double alpha0;
static double K0;    
static double Kp0;
static double Cv;   
static double tr;

void vinet(double t, double p, double *v, double *alpha, double *K, double *Kp, double *A) {
  double eta = 3.0*(Kp0-1.0)/2.0;
  double fn = DBL_MAX, dfn, dxdt, dxdp, d2xdp2;
  double x = 1.0;
  int iter = 0, iterMax = 500;
  
  while ((fabs(fn) > sqrt(DBL_EPSILON)) && (iter < iterMax)) {
    fn  = x*x*p - 3.0*K0*(1.0-x)*exp(eta*(1.0-x)) - x*x*alpha0*K0*(t-tr);
    dfn = 2.0*x*p+ 3.0*K0*exp(eta*(1.0-x)) + 3.0*K0*eta*(1.0-x)*exp(eta*(1.0-x)) - 2.0*x*alpha0*K0*(t-tr);
    x = x - fn/dfn;
    iter++;
  }
  if (iter == iterMax) printf("Iterations exceeded. x,fn = %g %g\n", x, fn);
  
  dxdt   = -(1.0/3.0)*x*x*x*alpha0*K0/(K0*exp(eta*(1.0-x))*(-2.0+x-eta*x+eta*x*x));
  dxdp   = -(1.0/3.0)*x*x*x/(K0*exp(eta*(1.0-x))*(2.0-x+eta*x-eta*x*x));
  d2xdp2 = - dxdp*dxdp*((-6.0+2.0*x-4.0*eta*x+2.0*eta*x*x-eta*eta*x*x+eta*eta*x*x*x)*exp(eta*(1.0-x)))/
             (x*exp(eta*(1.0-x))*(2.0-x+eta*x-eta*x*x));
  
  *v      = v0*x*x*x;
  *alpha  = 3.0*dxdt/x;
  *K      = -x/(3.0*dxdp);
  *Kp     = -1.0/3.0 - (*K)*d2xdp2/dxdp;
  
  *A      = (9.0*v0*K0/(eta*eta))*(1.0-eta*(1.0-x))*exp(eta*(1.0-x)) + v0*(t-tr)*K0*alpha0*(x*x*x-1.0) - 9.0*v0*K0/(eta*eta);
  *A     *= -1000.0;
}

#undef OUTPUT_ISOTHERM

int main (int argc, char** argv) {
  double p, t, v, alpha, K, Kp, A, xCrit, tCrit, pCrit, eta;
  float ftemp;
  FILE *output;
  
  output = fopen ("vinet.dat", "w");
  printf("Input a Kp at Tr:"); scanf("%f", &ftemp); Kp0 = ((double) ftemp); getchar();

  v0     = 49.80;
  alpha0 = 5.24e-3/49.80;
  K0	 = 49.80/(10000.0*1.35e-4);
  tr	 = 1400.0;
  Cv     = 271.0 - 1000.0*(tr+273.15)*alpha0*alpha0*v0*K0;

  eta   = 3.0*(Kp0-1.0)/2.0;
  xCrit = (eta-1.0 + sqrt(1.0+6.0*eta+eta*eta))/(2.0*eta);
  tCrit = tr - 3.0*K0*(1.0-xCrit)*exp(eta*(1.0-xCrit))/(xCrit*xCrit*alpha0*K0);
  pCrit = 3.0*K0*(1.0-xCrit)*exp(eta*(1.0-xCrit))/(xCrit*xCrit);
  
#ifdef OUTPUT_ISOTHERM
  printf("Input a new reference T (C) [tCrit at P=0 = %g}:", tCrit); scanf("%f", &ftemp); t = ((double) ftemp); getchar();
#else
  printf("Input a new reference P (GPa) [pCrit at T=1400 = %g}:", pCrit); scanf("%f", &ftemp); p = ((double) ftemp); getchar();
#endif
  
#ifdef OUTPUT_ISOTHERM
  for (p=0.0; p<101.0; p += ((p < 10.0) ? 1.0 : 5.0) ) {
    if (t < (tCrit = tr + p/(alpha0*K0) - 3.0*K0*(1.0-xCrit)*exp(eta*(1.0-xCrit))/(xCrit*xCrit*alpha0*K0)) ) {
#else
  for (t=1000.0; t<3001.0; t += 50.0 ) {
    if (p > (pCrit =  alpha0*K0*(t-tr) + 3.0*K0*(1.0-xCrit)*exp(eta*(1.0-xCrit))/(xCrit*xCrit))) {
#endif
      double Cp, gamma, G, S, H;
      vinet(t, p, &v, &alpha, &K, &Kp, &A);
      Cp = Cv + 1000.0*(t+273.15)*alpha*alpha*v*K;
      gamma = 1000.0*alpha*K*v/Cv;
      G = A + 1000.0*p*v;
      S = 1000.0*alpha*K*(v-v0);
      H = G + (t+273.15)*S;
#ifdef OUTPUT_ISOTHERM
      printf("p = %4.0f tCrit = %7.0f v =%6.2f alpha = %13.6e K = %7.2f Kp = %7.4f Cp = %6.1f gamma = %6.3f dA = %6.3f dG = %6.3f\n", p, tCrit, v, alpha, K, Kp, 
        Cp, gamma, A/1000.0, G/1000.0);
#else
      printf("t = %5.0f pCrit = %7.3f v =%6.2f alpha = %13.6e K = %7.2f Kp = %7.4f Cp = %6.1f gamma = %6.3f dA = %6.3f dG = %6.3f\n", t, pCrit, v, alpha, K, Kp, 
        Cp, gamma, A/1000.0, G/1000.0);
#endif
      fprintf(output, "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g\n", t, p, tCrit, pCrit, v, 100000.0*alpha, K, Kp, Cp, Cv, gamma, A/1000.0, G/1000.0, S, H/1000.0);
    }
  }
  
  fclose(output);
  exit(0);
}
