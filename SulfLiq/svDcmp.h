
#ifndef SVDCMP_H
#define SVDCMP_H

/** \file svDcmp.h
    header file for svDcmp global function
    $Id: svDcmp.h,v 1.3 2003/04/09 03:05:51 kress Exp $
    @author Press et al. (1988), Victor Kress
    $Revision: 1.3 $
*/

/**
   function performs in-place singular-value decomposition of mxn matrix
   From Numerical Recipes in C
   modified from Press et al (1988) routine
   floats changed to doubles
   vector declarations modified to simpler kress routine
   vectors and arrays changed to zero offset
   ANSI function prototypes
   @param a - m by n matrix where m>=n.  On exit contains svd U matrix
   @param m - rows of a
   @param n - columns of a
   @param w - n dimensional vector.  Contains svd W on exit.
   @param v - n by n matrix.  Contains svd V on exit.
*/
void svDcmp(double **a,int m,int n,double *w,double **v);

#endif
