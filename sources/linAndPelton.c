#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>
#include <grace_np.h>

static double A =  -31.38;
static double B =   23.01;
static double C = -135.98;

static double R = 8.3143/1000.0;

static double X;
static double T = 2200.0;

#define ITMAX 100
#define CGOLD 0.3819660
#define ZEPS 1.0e-10
#define SIGN(a,b) ((b) > 0.0 ? fabs(a) : -fabs(a))
#define SHFT(a,b,c,d) (a)=(b);(b)=(c);(c)=(d);

double brent(double ax, double bx, double cx, double (*f)(double), double tol, double *xmin)
{
  int iter;
  double a,b,d,etemp,fu,fv,fw,fx,p,q,r,tol1,tol2,u,v,w,x,xm;
  double e=0.0;

  a=((ax < cx) ? ax : cx);
  b=((ax > cx) ? ax : cx);
  x=w=v=bx;
  fw=fv=fx=(*f)(x);
  for (iter=1; iter<=ITMAX; iter++) {
    xm=0.5*(a+b);
    tol2=2.0*(tol1=tol*fabs(x)+ZEPS);
    if (fabs(x-xm) <= (tol2-0.5*(b-a))) {
  	    *xmin=x;
  	    return fx;
    }
    if (fabs(e) > tol1) {
  	    r=(x-w)*(fx-fv);
  	    q=(x-v)*(fx-fw);
  	    p=(x-v)*q-(x-w)*r;
  	    q=2.0*(q-r);
  	    if (q > 0.0) p = -p;
  	    q=fabs(q);
  	    etemp=e;
  	    e=d;
  	    if (fabs(p) >= fabs(0.5*q*etemp) || p <= q*(a-x) || p >= q*(b-x))
  		    d=CGOLD*(e=(x >= xm ? a-x : b-x));
  	    else {
  		    d=p/q;
  		    u=x+d;
  		    if (u-a < tol2 || b-u < tol2)
  			    d=SIGN(tol1,xm-x);
  	    }
    } else {
  	    d=CGOLD*(e=(x >= xm ? a-x : b-x));
    }
    u=(fabs(d) >= tol1 ? x+d : x+SIGN(tol1,d));
    fu=(*f)(u);
    if (fu <= fx) {
  	    if (u >= x) a=x; else b=x;
  	    SHFT(v,w,x,u)
  	    SHFT(fv,fw,fx,fu)
    } else {
  	    if (u < x) a=u; else b=u;
  	    if (fu <= fw || w == x) {
  		    v=w;
  		    w=u;
  		    fv=fw;
  		    fw=fu;
  	    } else if (fu <= fv || v == x || v == w) {
  		    v=u;
  		    fv=fu;
  	    }
    }
  }
  printf("Too many iterations in BRENT.\n");
  *xmin=x;
  return fx;
}

#undef ITMAX
#undef CGOLD
#undef ZEPS
#undef SIGN

static double H, S;

double G(double s) {
  double nO0   = 2.0*X - s/2.0;
  double nO2   = 1.0 - X - s/2.0;
  double nSiSi = (2.0*X)*(X/(X+nO2));
  
  S = -R*(X*log(X/(X+nO2)) + nO2*log(nO2/(X+nO2)) + nO0*log(nO0/nSiSi) + (nSiSi-nO0)*log((nSiSi-nO0)/nSiSi));
  H = (s/2.0)*(A*(1.0-X) + B*X + C*X*(1.0-X));
  return H - T*S;
}

static void grace_error_function(const char *msg)
{
  fprintf(stderr, "library message : \"%s\"\n", msg);
}

int main() {
  double aX, bX, cX, tol = sqrt(DBL_EPSILON), s, fmin, fmin2;
  int i;

  GraceRegisterErrorFunction (grace_error_function);
  if(GraceOpen (2048) < 0) { printf("Cannot open pipe to Grace.\n"); exit(0); }
  
  GracePrintf("WITH G0\n");
    GracePrintf("TITLE \"Lin and Pelton - s vrs X\"\n");
    GracePrintf("TITLE SIZE 0.8\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.1, 0.45, 0.4);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, 1.5);

    GracePrintf("XAXIS TICK MAJOR 0.2\n");
    GracePrintf("XAXIS TICK MINOR 0.1\n");
    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"X\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS TICK MAJOR 0.2\n");
    GracePrintf("YAXIS TICK MINOR 0.1\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("YAXIS LABEL \"s\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
    
  GracePrintf("WITH G1\n");
    GracePrintf("TITLE \"Lin and Pelton - S vrs X\"\n");
    GracePrintf("TITLE SIZE 0.8\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.6, 0.45,  0.9);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 1.0, 10.0);

    GracePrintf("XAXIS TICK MAJOR 0.2\n");
    GracePrintf("XAXIS TICK MINOR 0.1\n");
    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"X\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS TICK MAJOR 1.0\n");
    GracePrintf("YAXIS TICK MINOR 0.5\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("YAXIS LABEL \"S (J/K)\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
  
  GracePrintf("WITH G2\n");
    GracePrintf("TITLE \"Lin and Pelton - H vrs X\"\n");
    GracePrintf("TITLE SIZE 0.8\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.6,   0.6, 0.95,  0.9);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, -25.0, 1.0, 25.0);

    GracePrintf("XAXIS TICK MAJOR 0.2\n");
    GracePrintf("XAXIS TICK MINOR 0.1\n");
    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"X\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS TICK MAJOR 5.0\n");
    GracePrintf("YAXIS TICK MINOR 2.5\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("YAXIS LABEL \"H (kJ/K)\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
  
  GracePrintf("WITH G3\n");
    GracePrintf("TITLE \"Lin and Pelton - G vrs X\"\n");
    GracePrintf("TITLE SIZE 0.8\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.6,   0.1, 0.95, 0.4);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, -50.0, 1.0, 0.0);

    GracePrintf("XAXIS TICK MAJOR 0.2\n");
    GracePrintf("XAXIS TICK MINOR 0.1\n");
    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"X\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS TICK MAJOR 5.0\n");
    GracePrintf("YAXIS TICK MINOR 2.5\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("YAXIS LABEL \"G (kJ/K)\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
  
  GracePrintf("REDRAW\n");
  
  for (i=1; i<200; i++) {
    double nO0, nO2, nSiSi, sExt, hExt;
  
    X = ((double) i)*0.005;
    
    aX = 2.0*X +1.0 - sqrt(12.0*X*X - 4.0*X + 1.0);
    GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 1, X, aX);
    nO0   = 2.0*X - aX/2.0;
    nO2   = 1.0 - X - aX/2.0;
    nSiSi = (2.0*X)*(X/(X+nO2));
    sExt  = -R*X*log(X/(X+nO2));
    sExt += (nO2       > 0.0) ? -R*nO2*log(nO2/(X+nO2))               : 0.0; 
    sExt += (nO0       > 0.0) ? -R*nO0*log(nO0/nSiSi)                 : 0.0; 
    sExt += (nSiSi-nO0 > 0.0) ? -R*(nSiSi-nO0)*log((nSiSi-nO0)/nSiSi) : 0.0;
    GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 1, X, sExt*1000.0);
    hExt = (aX/2.0)*(A*(1.0-X) + B*X + C*X*(1.0-X));
    GracePrintf("g2.s%1.1d POINT %lf, %lf\n", 1, X, hExt);
    GracePrintf("g3.s%1.1d POINT %lf, %lf\n", 1, X, hExt - T*sExt);

    cX = (X <= 1.0/3.0) ? 4.0*X : 4.0/3.0 - (X-1.0/3.0)*2.0;
    GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 2, X, cX);
    nO0   = 2.0*X - cX/2.0;
    nO2   = 1.0 - X - cX/2.0;
    nSiSi = (2.0*X)*(X/(X+nO2));
    sExt  = -R*X*log(X/(X+nO2));
    sExt += (nO2       > 0.0) ? -R*nO2*log(nO2/(X+nO2))               : 0.0; 
    sExt += (nO0       > 0.0) ? -R*nO0*log(nO0/nSiSi)                 : 0.0; 
    sExt += (nSiSi-nO0 > 0.0) ? -R*(nSiSi-nO0)*log((nSiSi-nO0)/nSiSi) : 0.0;
    GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 2, X, sExt*1000.0);
    hExt = (cX/2.0)*(A*(1.0-X) + B*X + C*X*(1.0-X));
    GracePrintf("g2.s%1.1d POINT %lf, %lf\n", 2, X, hExt);
    GracePrintf("g3.s%1.1d POINT %lf, %lf\n", 2, X, hExt - T*sExt);
    
    bX = (aX + cX)/2.0; 
  
    printf("for X = %f, a,b,c = %f %f %f  ", X, aX, bX, cX);
    fmin = brent(aX, bX, cX, G, tol, &s);
    X = X + sqrt(DBL_EPSILON);
    fmin2 = brent(aX, bX, cX, G, tol, &s);
    printf("Value of mu SiO2 = %f\n", fmin + (1.0-X)*(fmin2-fmin)/sqrt(DBL_EPSILON));
    X = X - sqrt(DBL_EPSILON);

    GracePrintf("g0.s%1.1d POINT %lf, %lf\n", 0, X, s);
    GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 0, X, S*1000.0);
    GracePrintf("g2.s%1.1d POINT %lf, %lf\n", 0, X, H);
    GracePrintf("g3.s%1.1d POINT %lf, %lf\n", 0, X, fmin);
    
    GracePrintf("g1.s%1.1d POINT %lf, %lf\n", 3, X, -R*((1.0-X)*log(1.0-X)+X*log(X))*1000.0); /* ideal entropy */

  }
  GracePrintf("REDRAW\n");
  
  return 0; 
}
