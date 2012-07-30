#ifndef EIGENSYSTEM_H
#define EIGENSYSTEM_H

/** \file eigensystem.h
 header file for eigensystem global function
 $Id: eigensystem.h,v 1.3 2003/04/09 03:05:51 kress Exp $
 @author Victor Kress
 $Revision: 1.3 $
*/

/**
 Uses SVD to estimate eigensystem for symmetric real matrix A.
 See Nash (1990) Algorithm 13.
 @param A - Matrix for analysys.  Not altered on exit.
 @param n - Dimension of A, U, w and V.
 @param U - Collumns contain eigenvectors on output.
 @param w - Contains eigenvalues on output.
 @param V - Null space for solution
*/
void eigensystem(double **A,int n,double **U,double *w,double **V);

#endif
