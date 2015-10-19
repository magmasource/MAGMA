
#include "svdInv.h"
#include "svDcmp.h"

void svdInv(double **a,int m, int n,double **u,
              double *w,double **v,double tol) {
  int i,j,k;
  double wmin,wmax;
  for (i=0;i<m;i++) {
    for (j=0;j<n;j++) {
      u[i][j]=a[i][j];
    }
  }
  svDcmp(u,m,n,w,v);		/* a now contains U */
  for (i=0,wmax=0.0;i<n;i++) {	/* find maximum w */
    if (w[i]>wmax) wmax=w[i];
  }
  wmin=tol*wmax;		/* minimum w */
  for (i=0;i<n;i++) {		/* zero small w's */
    if (w[i]<wmin) w[i]=0.0;
  }
  for (i=0;i<n;i++) {
    for (j=0;j<m;j++) {
      a[i][j]=0.;
      for (k=0;k<n;k++) {
	if (w[k]!=0.) {
	  a[i][j]+=v[i][k]*u[j][k]/w[k];
	}
      }
    }
  }
  return;
}
