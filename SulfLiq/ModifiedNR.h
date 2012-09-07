#ifndef MODIFIEDNR_H
#define MODIFIEDNR_H
/** \file ModifiedNR.h
    header file for ModifiedNR global function
   $Id: ModifiedNR.h,v 1.3 2003/04/09 03:05:51 kress Exp $
   @author Victor Kress
   $Revision: 1.3 $
*/

/**
   Routine designed for optimal solution to Newson-Raphson interation.
   Uses modified Cholesky decomposition algorithm of Gill et al. (1981)
   to fix indefinite Hessians.
   Equations then solved as an LU problem.
   On return, H contains it's modified Cholesky decomposition, a contains
   solution and grad is unmodified.
   IMPORTANT:  Routines assume Cholesky decomposition (L) is storred in Kress
   form, i.e. D along diagonal.
   @see CholeskySolve
   @see ModifiedCholesky
   @param a n-vector.  Contains solution of aH = b on exit.
   @param b n-vector.
   @param H n by n matrix.
   @return number of modified diagonals to make positive-definite.
 */
int ModifiedNR(double *a,double *b,double **H,int n);

#endif
