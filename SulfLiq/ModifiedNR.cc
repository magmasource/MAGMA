/* Routine designed for optimal solution to Newson-Raphson interation.
 * Uses modified Cholesky decomposition algorithm of Gill et al. (1981)
 * to fix indefinite Hessians.
 * Equations then solved as an LU problem.
 * On return, H contains it's modified Cholesky decomposition, a contains
 * solution and grad is unmodified.
 * IMPORTANT:  Routines assume Cholesky decomposition (L) is storred in Kress
 * form, i.e. D along diagonal.
 *
 * Victor Kress
 * University of Washington
 * Seattle, Washington
 * 7/30/98
 * Debugged 8/2/98
 */

#include "ModifiedNR.h"
#include "ModifiedCholesky.h"
#include "CholeskySolve.h"

int ModifiedNR(double *a,double *b,double **H,int n) {

  int mod;

  /*Hessian decomposed in place*/
  mod=ModifiedCholesky(H,n);

  /*solve for a*/
  CholeskySolve(H,a,b,n);

  return mod;
}
