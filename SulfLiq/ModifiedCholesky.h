
#ifndef MODIFIEDCHOLESKY_H
#define MODIFIEDCHOLESKY_H

/** \file ModifiedCholesky
    header file for global ModifiedCholesky function
   $Id: ModifiedCholesky.h,v 1.3 2003/04/09 03:05:51 kress Exp $
   @author Victor Kress
   $Revision: 1.3 $
*/


/**
   Implements Gill et al (1981) algorithm for modified Colesky decomposition.
   Page 111.
   Do not bother with permutation
   Optimized for speed.  Decomposition done in place. c,L and G all point
   to same array.  This is for clarity only.  d[j] is stored in c[j][j].
   This is the only aspect that will not be transparent to careful reader
   of Gill et al. (1981).
   IMPORTANT: In order to conserved space and computing time, elements of
   D are on diagonal (diagonal elements would be 1 otherwise).
   One could easily have made a traditional "square root" decomposition,
   which would have simplified matters somewhat.
   I avoided this because square roots are computationally costly, and I
   need this routine to run fast.
   @param G Symmetric real n x n matrix. Returns decomposition with minimum diagonal modifications to make PD.
   @param n dimension of square matrix
   @return Number of modifications required to make positive definite.
 */
int ModifiedCholesky(double **G,int n);

#endif

