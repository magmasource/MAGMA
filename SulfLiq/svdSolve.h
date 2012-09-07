
#ifndef SVDSOLVE_H
#define SVDSOLVE_H

/** \file svdSolve.h
    header file for svdSolve global function
    $Id: svdSolve.h,v 1.3 2003/04/09 03:05:52 kress Exp $
    @author Victor Kress
    $Revision: 1.3 $
*/

/**
   From Numerical Recipes in C
   Converted to zero offset vectors and matrices and vector
   declarations converted to Kress standard
   University of Washington
   11/9/98
   Solves ax=b for x.  Also returns SVD
   m rows and n columns.
   <p> Note: if m<n (degenerate) matrices must be big enough to hold nxn 
   problem. 
   @param a - m by n design matrix on input.  Contains svd U on output
   @param x - m dimensional vector
   @param b - n dimensional vector
   @param m - rows of a
   @param n - columns of a
   @param w - n dimensional vector
   @param v - n by n svd V matrix
   @param tol - tolerance for editing singular values
*/
void svdSolve(double **a,double *x,double *b,
              int m, int n,double *w,double **v,double tol);

/**
   modified from Press et al (1988) routine
   by Victor Kress 3/14/98.
   floats changed to doubles
   vector declarations modified to simpler kress routine
   vectors and arrays changed to zero offset
   ANSI function prototypes
*/
void svBksb(double **u,double *w,double **v,int m,int n,double *b,double *x);

#endif

