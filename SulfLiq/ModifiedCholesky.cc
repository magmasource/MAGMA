/* funciton ModifiedCholesky
 * Implements Gill et al. (1981) algorithm for modified Colesky decomposition.
 * Page 111.
 *
 * Do not bother with permutation
 * Optimized for speed.  Decomposition done in place. c,L and G all point
 * to same array.  This is for clarity only.  d[j] is stored in c[j][j].
 * This is the only aspect that will not be transparent to careful reader
 * of Gill et al. (1981)
 *
 * IMPORTANT: In order to conserved space and computing time, elements of
 * D are on diagonal (diagonal elements would be 1 otherwise).
 * One could easily have made a traditional "square root" decomposition,
 * which would have simplified matters somewhat.
 * I avoided this because square roots are computationally costly, and I
 * need this routine to run fast.
 *
 * Input matrix G must be symmetric real n x n matrix.
 * Returns decomposition with minimum diagonal modifications to make PD
 *
 * Victor Kress
 * University of Washington
 * 7/28/98
 * Debugged 7/30/98
 */


#define MAX(a,b) (((a)>(b))?a:b)
#define SQR(x) ((x)*(x))
#define DELTA 1.e-2

#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "ModifiedCholesky.h"

int ModifiedCholesky(double **G,int n) {

  double gamma,xi,betasqr,theta,temp,**c,**L,dj,nu;
  int i,j,s,mod=0;

  c=L=G;    /*remain separate only for clarity*/

  /*MC1: calculate bound elements*/
  
  temp = sqrt(n*n-1);
  nu = MAX(temp,1.);
  
  for (i=1,gamma=fabs(G[0][0]);i<n;i++) {  /*calculate gammaa*/
    temp=fabs(G[i][i]);
    if (temp>gamma) gamma=temp;
  }
  
  for (i=0,xi=0.;i<n;i++) {          /*calculate xi*/
    for (j=0;j<i;j++) {
      temp=fabs(G[i][j]);
      if (temp>xi) xi=temp;
    }
  }
  
  betasqr=1000.*DBL_EPSILON;                 /*calculate betasqr*/
  if (gamma>betasqr) betasqr=gamma;
  temp=xi/nu;
  if (temp>betasqr) betasqr=temp;
  
  for (j=0;j<n;j++) {    /*main loop*/
    
    for (s=0;s<j;s++) {                              /*MC4: jth row of l*/
      L[j][s]=c[j][s]/c[s][s];
    }
    for (i=j+1;i<n;i++) {
      c[i][j]=G[i][j];
      for (s=0;s<j;s++) {
	c[i][j] -= L[j][s]*c[i][s];
      }
    }
    for (i=j+1,theta=0.;i<n;i++) {
      temp=fabs(c[i][j]);
      if (temp>theta) theta=temp;
    }
    
    dj=fabs(c[j][j]);                              /*MC5: compute diagonal*/
    if (DELTA>dj) dj=DELTA;
    temp=SQR(theta)/betasqr;
    if (temp>dj) dj=temp;
    
    if (dj>c[j][j]) {
      mod++;
      c[j][j]=dj;
    }
    
    for (i=j+1;i<n;i++) {                            /*MC6: update diagonals*/
      c[i][i] -= SQR(c[i][j])/c[j][j];
    }
  }                                /*end for j*/
  
  /*zero upper corner*/
  for (i=0;i<n-1;i++) {
    for (j=i+1;j<n;j++) {
      G[i][j]=0.0;
    }
  }
  
  return(mod);
}                                  /*end ModifiecCholesky*/






