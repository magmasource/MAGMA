/*
 * NumUtil file
 * includes various numerical utilities
 * Victor Kress
 */
#ifndef NUMUTIL_H
#define NUMUTIL_H

/** \file NumUtil.h
    header file for numerical utilities for matrix allocation and deallocation etc.
    $Id: NumUtil.h,v 1.7 2004/01/20 01:05:03 kress Exp $
    @author Victor Kress
    $Revision: 1.7 $
*/

/// implements dirac delta function
#define DIRAC(i,j) ((i==j)?1.0:0.0)
/// squares argument
#define SQR(x) ((x)*(x))
/// cubes argument
#define CUB(x) ((x)*(x)*(x))

/// allocates ** double matrix
double **dmatrix(int m,int n); 
/// deletes dmatrix          
void free_dmatrix(int m,int n,double **a);
/// allocates 3d matrix
double ***dmatrix3d(int m,int n,int o);
/// deletes 3d matrix
void free_dmatrix3d(int m,int n,int o,double ***a);
/// allocates 4d matrix
double ****dmatrix4d(int m,int n,int o,int p);
/// deletes 4d matrix
void free_dmatrix4d(int m,int n,int o,int p,double ****a);
/// allocates ** int matrix
int **imatrix(int m,int n); 
/// deletes imatrix
void free_imatrix(int m,int n,int **a);
/// convert c++ double matrix to **
double **conv_dmatrix(int m,int n,double **x);
/// returns double identity matrix
double **doubleIdentityMatrix(int m);
/// for backward compatibility
/// allocates vector of double
/// @param i dimension of vector
double *dvector(int i);    
/// for backward compatibility
/// deallocates vector created with dvector
void free_dvector(double *v,int i);    
/// for backward compatibility
/// allocates vector of int
/// @param i dimension of vector
int *ivector(int i);    
/// for backward compatibility
/// deallocates vector created with ivector
void free_ivector(int *v,int i);    

#endif




