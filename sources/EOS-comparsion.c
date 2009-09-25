#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static double tr;

/* VINET Eqn and constants */

static double v0;  
static double alpha0;
static double K0;    
static double Kp0;

void vinet(double t, double p, double *v, double *alpha, double *K, double *Kp, double *A, double *Cv, double *Cp) {
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
  *Cp     = *Cv + 1000.0*(t+273.15)*(*alpha)*(*alpha)*(*v)*(*K);
        
  *A      = (9.0*v0*K0/(eta*eta))*(1.0-eta*(1.0-x))*exp(eta*(1.0-x)) + v0*(t-tr)*K0*alpha0*(x*x*x-1.0) - 9.0*v0*K0/(eta*eta);
  *A     *= -1000.0;
}

/* GHIORSO Eqn and constants */

static double v_trpr;  
static double dvdp_trpr;
static double dvdt_trpr;
static double alpha_trpr;    
static double d2vdt2_trpr;
static double cp_trpr;
static double msg_a;   
static double msg_b;
static double msg_c;
static double msg_d;

void msg_gen(double t, double pInGPa, double *v, double *alpha, double *K, double *Kp, double *A, double *Cv, double *Cp) {
  const double pr = 1.0;
  double dvdt, dvdp, d2vdp2, g;
  double a = msg_a;
  double b = msg_b;
  double c = msg_c;
  double d = msg_d;
  double p = 10000.0*pInGPa + 1.0;
  
  *v      = v_trpr + (dvdp_trpr*(p-pr) + c*(p-pr)*(p-pr))/(1.0 + a*(p-pr) + b*(p-pr)*(p-pr))
          + (dvdt_trpr*(t-tr) + d2vdt2_trpr*(t-tr)*(t-tr)/2.0)/(1.0 + d*(p-pr));
  dvdt    = (dvdt_trpr + d2vdt2_trpr*(t-tr))/(1.0 + d*(p-pr));
  *alpha  = dvdt/(*v);
  dvdp    = (dvdp_trpr + 2.0*c*(p-pr))/(1.0 + a*(p-pr) + b*(p-pr)*(p-pr))
          - (dvdp_trpr*(p-pr) + c*(p-pr)*(p-pr))*(a + 2.0*b*(p-pr))/pow(1.0 + a*(p-pr) + b*(p-pr)*(p-pr), (double) 2.0)
          - d*(dvdt_trpr*(t-tr) + d2vdt2_trpr*(t-tr)*(t-tr)/2.0)/pow(1.0 + d*(p-pr), (double) 2.0);
  *K      = -(*v)/dvdp;
  *K     /= 10000.0; /* bars -> GPa */
  d2vdp2  = 2.0*c/(1.0 + a*(p-pr) + b*(p-pr)*(p-pr))
          - 2.0*(dvdp_trpr + 2.0*c*(p-pr))*(a + 2.0*b*(p-pr))/pow(1.0 + a*(p-pr) + b*(p-pr)*(p-pr), (double) 2.0)
	  + 2.0*(dvdp_trpr*(p-pr) + c*(p-pr)*(p-pr))*pow(a + 2.0*b*(p-pr), (double) 2.0)/pow(1.0 + a*(p-pr) + b*(p-pr)*(p-pr), (double) 3.0)
	  - 2.0*b*(dvdp_trpr*(p-pr) + c*(p-pr)*(p-pr))/pow(1.0 + a*(p-pr) + b*(p-pr)*(p-pr), (double) 2.0)	  
          + 2.0*d*d*(dvdt_trpr*(t-tr) + d2vdt2_trpr*(t-tr)*(t-tr)/2.0)/pow(1.0 + d*(p-pr), (double) 3.0);	  
  *Kp     = (*v)*d2vdp2/(dvdp*dvdp) - 1.0;
  
  *Cp     = cp_trpr - (t+273.15)*d2vdt2_trpr*log(1.0+d*(p-pr))/(10.0*d);
  *Cv     = *Cp + (t+273.15)*dvdt*dvdt/(10.0*dvdp);
  
  if        (a*a-4.0*b  > 0.0) {
    double x = (a+2.0*b*(p-pr))/sqrt(a*a-4.0*b);
    double y = a/sqrt(a*a-4.0*b);
    g = (v_trpr+c/b)*(p-pr) + (1.0/(2.0*b))*(dvdp_trpr-a*c/b)*log(1.0+a*(p-pr)+b*(p-pr)*(p-pr))
      + (dvdt_trpr*(t-tr)+d2vdt2_trpr*(t-tr)*(t-tr)/2.0)*log(1.0+d*(p-pr))/d
      + ((a*dvdp_trpr+c*(2.0-a*a/b))/(b*sqrt(a*a-4.0*b)))*log((1.0+x)*(1.0-y)/((1.0-x)*(1.0+y)))/2.0;
  } else if (a*a-4.0*b == 0.0) {
    g = (v_trpr+4.0*c/(a*a))*(p-pr) + (4.0/(a*a))*(dvdp_trpr-4.0*c/a)*log(1.0+a*(p-pr)/2.0)
      + (dvdt_trpr*(t-tr)+d2vdt2_trpr*(t-tr)*(t-tr)/2.0)*log(1.0+d*(p-pr))/d
      + (8.0*c*(p-pr)-4.0*a*(p-pr)*dvdp_trpr)/(a*a*(2.0+a*(p-pr)));
  } else if (a*a-4.0*b  < 0.0) {
    double x = (a+2.0*b*(p-pr))/sqrt(4.0*b-a*a);
    double y = a/sqrt(4.0*b-a*a);
    g = (v_trpr+c/b)*(p-pr) + (1.0/(2.0*b))*(dvdp_trpr-a*c/b)*log(1.0+a*(p-pr)+b*(p-pr)*(p-pr))
      + (dvdt_trpr*(t-tr)+d2vdt2_trpr*(t-tr)*(t-tr)/2.0)*log(1.0+d*(p-pr))/d
      + ((a*dvdp_trpr+c*(2.0-a*a/b))/(b*sqrt(4.0*b-a*a)))*log((1.0+x)*(1.0-y)/((1.0-x)*(1.0+y)))/2.0;
  }
  
  *A      = (g - p*(*v))/10.0;  /* cc-bars -> J */
}

void msg_alpha(double t, double pInGPa, double *v, double *alpha, double *K, double *Kp, double *A, double *Cv, double *Cp) {
  const double pr = 1.0;
  double dvdt, dvdp, d2vdp2, g;
  double a = msg_a;
  double b = msg_b;
  double c = msg_c;
  double d = msg_d;
  double p = 10000.0*pInGPa + 1.0;
  
  *v      = v_trpr + (dvdp_trpr*(p-pr) + c*(p-pr)*(p-pr))/(1.0 + a*(p-pr) + b*(p-pr)*(p-pr))
          + v_trpr*(exp(alpha_trpr*(t-tr))-1.0)/(1.0 + d*(p-pr));
  dvdt    = v_trpr*alpha_trpr*exp(alpha_trpr*(t-tr))/(1.0 + d*(p-pr));
  *alpha  = dvdt/(*v);
  dvdp    = (dvdp_trpr + 2.0*c*(p-pr))/(1.0 + a*(p-pr) + b*(p-pr)*(p-pr))
          - (dvdp_trpr*(p-pr) + c*(p-pr)*(p-pr))*(a + 2.0*b*(p-pr))/pow(1.0 + a*(p-pr) + b*(p-pr)*(p-pr), (double) 2.0)
          - d*v_trpr*(exp(alpha_trpr*(t-tr))-1.0)/pow(1.0 + d*(p-pr), (double) 2.0);
  *K      = -(*v)/dvdp;
  *K     /= 10000.0; /* bars -> GPa */
  d2vdp2  = 2.0*c/(1.0 + a*(p-pr) + b*(p-pr)*(p-pr))
          - 2.0*(dvdp_trpr + 2.0*c*(p-pr))*(a + 2.0*b*(p-pr))/pow(1.0 + a*(p-pr) + b*(p-pr)*(p-pr), (double) 2.0)
	  + 2.0*(dvdp_trpr*(p-pr) + c*(p-pr)*(p-pr))*pow(a + 2.0*b*(p-pr), (double) 2.0)/pow(1.0 + a*(p-pr) + b*(p-pr)*(p-pr), (double) 3.0)
	  - 2.0*b*(dvdp_trpr*(p-pr) + c*(p-pr)*(p-pr))/pow(1.0 + a*(p-pr) + b*(p-pr)*(p-pr), (double) 2.0)	  
          + 2.0*d*d*v_trpr*(exp(alpha_trpr*(t-tr))-1.0)/pow(1.0 + d*(p-pr), (double) 3.0);	  
  *Kp     = (*v)*d2vdp2/(dvdp*dvdp) - 1.0;

  *Cp     = cp_trpr - (t+273.15)*v_trpr*alpha_trpr*alpha_trpr*exp(alpha_trpr*(t-tr))*log(1.0+d*(p-pr))/(10.0*d);
  *Cv     = *Cp + (t+273.15)*dvdt*dvdt/(10.0*dvdp);
  
  if        (a*a-4.0*b  > 0.0) {
    double x = (a+2.0*b*(p-pr))/sqrt(a*a-4.0*b);
    double y = a/sqrt(a*a-4.0*b);
    g = (v_trpr+c/b)*(p-pr) + (1.0/(2.0*b))*(dvdp_trpr-a*c/b)*log(1.0+a*(p-pr)+b*(p-pr)*(p-pr))
      + v_trpr*(exp(alpha_trpr*(t-tr))-1.0)*log(1.0+d*(p-pr))/d
      + ((a*dvdp_trpr+c*(2.0-a*a/b))/(b*sqrt(a*a-4.0*b)))*log((1.0+x)*(1.0-y)/((1.0-x)*(1.0+y)))/2.0;
  } else if (a*a-4.0*b == 0.0) {
    g = (v_trpr+4.0*c/(a*a))*(p-pr) + (4.0/(a*a))*(dvdp_trpr-4.0*c/a)*log(1.0+a*(p-pr)/2.0)
      + v_trpr*(exp(alpha_trpr*(t-tr))-1.0)*log(1.0+d*(p-pr))/d
      + (8.0*c*(p-pr)-4.0*a*(p-pr)*dvdp_trpr)/(a*a*(2.0+a*(p-pr)));
  } else if (a*a-4.0*b  < 0.0) {
    double x = (a+2.0*b*(p-pr))/sqrt(4.0*b-a*a);
    double y = a/sqrt(4.0*b-a*a);
    g = (v_trpr+c/b)*(p-pr) + (1.0/(2.0*b))*(dvdp_trpr-a*c/b)*log(1.0+a*(p-pr)+b*(p-pr)*(p-pr))
      + v_trpr*(exp(alpha_trpr*(t-tr))-1.0)*log(1.0+d*(p-pr))/d
      + ((a*dvdp_trpr+c*(2.0-a*a/b))/(b*sqrt(4.0*b-a*a)))*log((1.0+x)*(1.0-y)/((1.0-x)*(1.0+y)))/2.0;
  }
  
  *A      = (g - p*(*v))/10.0;  /* cc-bars -> J */
}

#define TRUE      1
#define FALSE     0

#define VINET     0
#define MSG_GEN   1
#define MSG_ALPHA 2

static int OUTPUT_ISOTHERM;
static int OUTPUT_EOS;

int main (int argc, char** argv) {
  double p, t, v, alpha, K, Kp, A, xCrit, tCrit, pCrit, eta, Cv, Cp;
  float ftemp;
  FILE *output;
  
  printf("Output isotherms (y or n)? ");
  if (tolower(getchar()) == 'y') { getchar(); OUTPUT_ISOTHERM = TRUE;  }
  else                           { getchar(); OUTPUT_ISOTHERM = FALSE; }
  
  printf("Compute using Vinet equation (y or n)? ");
  if (tolower(getchar()) == 'y') { 
    getchar(); OUTPUT_EOS = VINET; 
  } else { 
    getchar(); 
    printf("Compute using Ghiorso general equation (y or n)? ");
    if (tolower(getchar()) == 'y') { 
      getchar(); OUTPUT_EOS = MSG_GEN; 
    } else { 
      getchar(); 
      printf("Compute using Ghiorso (alpha const) equation (y or n)? ");
      if (tolower(getchar()) == 'y') { 
	getchar(); OUTPUT_EOS = MSG_ALPHA; 
      } else { getchar(); exit(1); }
    }
  }
  
  output = fopen ("eos.dat", "w");
  
  if (OUTPUT_EOS == VINET) {
    printf("Input a Kp at Tr:"); scanf("%f", &ftemp); Kp0 = ((double) ftemp); getchar();
  } else Kp0 = 6.0;

  v0     = 49.80;
  alpha0 = 5.24e-3/49.80;
  K0	 = 49.80/(10000.0*1.35e-4);
  tr	 = 1400.0;
  Cp     = 271.0;
  Cv     = Cp - 1000.0*(tr+273.15)*alpha0*alpha0*v0*K0;
  
  v_trpr     = 49.80;
  dvdt_trpr  =  5.24e-3;
  alpha_trpr =  5.24e-3/49.80;
  dvdp_trpr  = -1.35e-4; 
  cp_trpr    = 271.0;
  msg_a      = ( 1.60832e-5)*13;    /* 13 */
  msg_b      = ( 2.09614e-11)*1;
  msg_c      = (-5.29886e-10)*1;
  msg_d      =  -(-1.3e-7)/dvdt_trpr;

  eta   = 3.0*(Kp0-1.0)/2.0;
  xCrit = (eta-1.0 + sqrt(1.0+6.0*eta+eta*eta))/(2.0*eta);
  tCrit = tr - 3.0*K0*(1.0-xCrit)*exp(eta*(1.0-xCrit))/(xCrit*xCrit*alpha0*K0);
  pCrit = 3.0*K0*(1.0-xCrit)*exp(eta*(1.0-xCrit))/(xCrit*xCrit);
  
  d2vdt2_trpr = dvdt_trpr*dvdt_trpr*(2.0-sqrt(2.0))/(v_trpr*pow(sqrt(2.0)-1.0, (double) 2.0));
  
  if        (OUTPUT_EOS == VINET &&  OUTPUT_ISOTHERM) {
    printf("Input a new reference T (C) [tCrit at P=0 = %g]:", tCrit); scanf("%f", &ftemp); t = ((double) ftemp); getchar();
  } else if (OUTPUT_ISOTHERM) {
    printf("Input a new reference T (C):"); scanf("%f", &ftemp); t = ((double) ftemp); getchar();
  } else if (OUTPUT_EOS == VINET && !OUTPUT_ISOTHERM) { 
    printf("Input a new reference P (GPa) [pCrit at T=1400 = %g]:", pCrit); scanf("%f", &ftemp); p = ((double) ftemp); getchar();
  } else if (!OUTPUT_ISOTHERM) {
    printf("Input a new reference P (GPa):"); scanf("%f", &ftemp); p = ((double) ftemp); getchar();
  }
  
  if (OUTPUT_ISOTHERM) {
    for (p=0.0; p<101.0; p += ((p < 10.0) ? 1.0 : 5.0) ) {
      if (OUTPUT_EOS != VINET || (t < (tCrit = tr + p/(alpha0*K0) - 3.0*K0*(1.0-xCrit)*exp(eta*(1.0-xCrit))/(xCrit*xCrit*alpha0*K0))) ) {
        double gamma, G, S, H;
        if (OUTPUT_EOS == VINET)         vinet(t, p, &v, &alpha, &K, &Kp, &A, &Cv, &Cp);
        if (OUTPUT_EOS == MSG_GEN)     msg_gen(t, p, &v, &alpha, &K, &Kp, &A, &Cv, &Cp);
        if (OUTPUT_EOS == MSG_ALPHA) msg_alpha(t, p, &v, &alpha, &K, &Kp, &A, &Cv, &Cp);
        gamma = 1000.0*alpha*K*v/Cv;
        G = A + 1000.0*p*v;
        S = 1000.0*alpha*K*(v-v0);
        H = G + (t+273.15)*S;
        printf("p = %4.0f tCrit = %7.0f v =%6.2f alpha = %13.6e K = %7.2f Kp = %7.4f Cp = %6.1f gamma = %6.3f dA = %6.3f dG = %6.3f\n", p, tCrit, v, alpha, K, Kp, 
          Cp, gamma, A/1000.0, G/1000.0);
        fprintf(output, "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g\n",
	/* [C]  [GPa] [C]    [GPa]  [cc] dvdt [cc/K] [10^5/K]        dvdp [cc/bar] beta [1/bar] [GPa] []  [J/K] [J/K] []    */
	   t,   p,    tCrit, pCrit, v,   alpha*v,    100000.0*alpha, -v*1.0e-4/K,  1.0e-4/K,    K,    Kp, Cp,   Cv,   gamma, 
	/* (dP/dT)V [GPa/K] [kJ]      [kJ]      [J/K]   [kJ]       */
	   alpha*K,         A/1000.0, G/1000.0, S,      H/1000.0);
      }
    }
  } else {
    for (t=1000.0; t<3001.0; t += 50.0 ) {
      if (OUTPUT_EOS != VINET || (p > (pCrit =  alpha0*K0*(t-tr) + 3.0*K0*(1.0-xCrit)*exp(eta*(1.0-xCrit))/(xCrit*xCrit))) ) {
        double gamma, G, S, H;
        if (OUTPUT_EOS == VINET)         vinet(t, p, &v, &alpha, &K, &Kp, &A, &Cv, &Cp);
        if (OUTPUT_EOS == MSG_GEN)     msg_gen(t, p, &v, &alpha, &K, &Kp, &A, &Cv, &Cp);
        if (OUTPUT_EOS == MSG_ALPHA) msg_alpha(t, p, &v, &alpha, &K, &Kp, &A, &Cv, &Cp);
        gamma = 1000.0*alpha*K*v/Cv;
        G = A + 1000.0*p*v;
        S = 1000.0*alpha*K*(v-v0);
        H = G + (t+273.15)*S;
        printf("t = %5.0f pCrit = %7.3f v =%6.2f alpha = %13.6e K = %7.2f Kp = %7.4f Cp = %6.1f gamma = %6.3f dA = %6.3f dG = %6.3f\n", t, pCrit, v, alpha, K, Kp, 
          Cp, gamma, A/1000.0, G/1000.0);
        fprintf(output, "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g\n",
	/* [C]  [GPa] [C]    [GPa]  [cc] dvdt [cc/K] [10^5/K]        dvdp [cc/bar] beta [1/bar] [GPa] []  [J/K] [J/K] []    */
	   t,   p,    tCrit, pCrit, v,   alpha*v,    100000.0*alpha, -v*1.0e-4/K,  1.0e-4/K,    K,    Kp, Cp,   Cv,   gamma, 
	/* (dP/dT)V [GPa/K] [kJ]      [kJ]      [J/K]   [kJ]       */
	   alpha*K,         A/1000.0, G/1000.0, S,      H/1000.0);
      }
    }
  }
  
  fclose(output);
  exit(0);
}
