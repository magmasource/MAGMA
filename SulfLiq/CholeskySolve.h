
#ifndef CHOLESKYSOLVE_H
#define CHOLESKYSOLVE_H

/** \file CholeskySolve.h
   $Id: CholeskySolve.h,v 1.3 2003/04/09 03:05:51 kress Exp $
   @author Victor Kress
   $Revision: 1.3 $
*/

/**
   Uses LU decomposition algorithm to solve Lx=b.  During calcs
   b is placed in x temporarily.
   @param L kress variant of Cholesky decomposition.  D along diagonal where 1's would otherwise be
   @param x n-vector solution on return.
   @param b n-vector.
   @see ModifiedCholesky
 */
void CholeskySolve(double **L,double *x,double *b,int n);

#endif
