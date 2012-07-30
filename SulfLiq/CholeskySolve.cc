/* function CholeskySolve
 * Uses LU decomposition algorithm to solve Lx=b
 * L is kress varient of Cholesky decomposition.  D along diagonal where
 * 1's would otherwise be
 * b is placed in x temporarily
 * on return x is solution
 * nothing else is modified
 */

#include "CholeskySolve.h"

void CholeskySolve(double **L,double *x,double *b,int n) {
  int i,j;

  for (i=0;i<n;i++) {
    x[i]=b[i];
    for (j=0;j<i;j++) {
      x[i] -= L[i][j]*x[j];
    }
  }
  
  for (i=n-1;i>=0;i--) {
    x[i] /= L[i][i];
    for (j=i+1;j<n;j++) {
      x[i] -= L[j][i]*x[j];
    }
  }
  return;
}
