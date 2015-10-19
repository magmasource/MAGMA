
/*
 Uses SVD to estimate eigensystem for symmetric real matrix A.
 See Nash (1990) Algorithm 13
 Victor Kress
 $Id: eigensystem.cc,v 1.3 2003/04/24 20:09:43 kress Exp $
*/

#include <math.h>
#include "eigensystem.h"
#include "svDcmp.h"

void eigensystem(double **A,int n,double **U,double *w,double **V) {
  int i,j;
  double shift,t;
  /*copy into U*/
  for (i=0;i<n;i++) {
    for (j=0;j<n;j++) {
      U[i][j]=A[i][j];
    }
  }

  /*find lower bound on eigenvalues*/
  shift=0.;
  for (i=0;i<n;i++) {
    t=A[i][i];
    for (j=0;j<n;j++) {
      if (i!=j) {
	t -= fabs(A[i][j]);
      }
      if (t<shift) shift = t;
    }
  }
  shift = (shift>0.)? 0.:-shift;
  for (i=0;i<n;i++) {
    U[i][i] += shift;
  }

  /*singular value decomposition*/
  svDcmp(U,n,n,w,V);

  /* Nash (1990 Eq. 10.20 */
  for (j=0;j<n;j++) {
    w[j] -= shift;
  }
  return;
}

