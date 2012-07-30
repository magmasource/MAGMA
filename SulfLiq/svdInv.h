#ifndef SVDINV_H
#define SVDINV_H

/** \file svdInv.h
    header file for svdInv global function
    $Id: svdInv.h,v 1.3 2003/04/09 03:05:52 kress Exp $
    @author Press et al. (1988), Victor Kress 10/19/00
    $Revision: 1.3 $
*/

/**
   Routine for SVD matrix inversion.
   Uses Numerical Recipes in C
   modified from Press et al (1988) routine
   floats changed to doubles
   vector declarations modified to simpler kress routine
   vectors and arrays changed to zero offset
   ANSI function prototypes
   @param a - m by n matrix where m>=n.  On exit contains inverse
   @param m - rows of a
   @param n - columns of a
   @param u - m by n matrix containing svd U on exit
   @param w - n dimensional vector.  Contains svd W on exit.
   @param v - n by n matrix.  Contains svd V on exit.
   @param tol - tolerance for editing W values
 */

void svdInv(double **a,int m, int n,double **u,
              double *w,double **v,double tol);

#endif
