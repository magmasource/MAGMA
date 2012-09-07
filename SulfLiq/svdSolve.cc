/*
 From Numerical Recipes in C
 Converted to zero offset vectors and matrices and vector
 declarations converted to Kress standard
 converted to c++ 9/7/00
 */

#include <iostream>
#include <math.h>
#include "svdSolve.h"
#include "svDcmp.h"

using namespace std;

/**
   Singular Value Decomposition solution to ax=b
   From Numerical Recipes in C
   Converted to zero offset vectors and matrices and vector
   declarations converted to Kress standard
   converted to c++ 9/7/00
 */
void svdSolve(double **a,double *x,double *b,
              int m, int n,double *w,double **v,double tol) {
  int i,j,zcount,mm;
  double wmin,wmax;

  j=0;  //avoids compiler error

  if (m<n) {			/* degenerate case */
    mm=n;
    for (i=m;i<n;i++) {		/* augment problem with zeros */
      b[i]=0.;
      for (j=0;j<n;j++) {
	a[i][j] = 0.;
      }
    }
  }
  else mm=m;
  svDcmp(a,mm,n,w,v);		/* a now contains U */
  for (i=0,wmax=0.0;i<n;i++) {	/* find maximum w */
    if (w[i]>wmax) wmax=w[i];
  }
  wmin=tol*wmax;		/* minimum w */
  for (i=0,zcount=0;i<n;i++) {		/* zero small w's */
    if (w[i]<wmin) {
      w[i]=0.0;
      zcount++;
    }
  }
  while (zcount<(n-m)) {	/* make sure we have zeroed n-m w's */
    for (i=0,wmin=wmax;i<n;i++) {
      if (w[i]!=0.) {
	if (w[i]<wmin) {
	  wmin=w[i];
	  j=i;
	}
      }
    }
    w[j]=0.0;
    zcount++;
  }
  svBksb(a,w,v,mm,n,b,x);
  return;
}


void svBksb(double **u,double *w,double **v,int m,int n,double *b,double *x) {
  int jj,j,i;
  double s;
  double *tmp;

  tmp=new double[n];
  for (j=0;j<n;j++) {
    s=0.0;
    if (w[j]) {
      for (i=0;i<m;i++) s += u[i][j]*b[i];
      s /= w[j];
    }
    tmp[j]=s;
  }
  for (j=0;j<n;j++) {
    s=0.0;
    for (jj=0;jj<n;jj++) s += v[j][jj]*tmp[jj];
    x[j]=s;
  }
  delete []tmp;
}















