/*
 * NumUtil routine bodies
 * prototypes in NumUtil.h
 * Victor Kress
 */

#include "NumUtil.h"

double **dmatrix(int m,int n) {
  int i;
  double **a;
  a = new double*[m];
  for(i=0;i<m;i++) {
    a[i] = new double[n];
  }
  return a;
}
  
void free_dmatrix(int m,int n,double **a) {
  int i;
  for(i=0;i<m;i++) {
    delete[] a[i];
  }
  delete[] a;
  a=0;
  return;
  }

double ***dmatrix3d(int m,int n,int o) {
  int i;
  double ***a;
  a = new double**[m];
  for (i=0;i<m;i++) {
    a[i]=dmatrix(n,o);
  }
  return a;
}

void free_dmatrix3d(int m,int n,int o,double ***a) {
  int i;
  for (i=0;i<m;i++) {
    free_dmatrix(n,o,a[i]);
  }
  delete[] a;
  a=0;
  return;
}

double ****dmatrix4d(int m,int n,int o,int p) {
  int i;
  double ****a;
  a = new double***[m];
  for (i=0;i<m;i++) {
    a[i]=dmatrix3d(n,o,p);
  }
  return a;
}

void free_dmatrix4d(int m,int n,int o,int p,double ****a) {
  int i;
  for (i=0;i<m;i++) {
    free_dmatrix3d(n,o,p,a[i]);
  }
  delete[] a;
  a=0;
  return;
}

int **imatrix(int m,int n) {
  int i;
  int **a;
  a = new int*[m];
  for(i=0;i<m;i++) {
    a[i] = new int[n];
  }
  return a;
}
  
void free_imatrix(int m,int n,int **a) {
  int i;
  for(i=0;i<m;i++) {
    delete[] a[i];
  }
  delete[] a;
  a=0;
  return;
}

double **conv_dmatrix(int m,int n,double **x) {
  int i;
  double **a;
  a = new double*[m];
  for (i=0;i<m;i++) {
    a[i] = *x+i*n;
  }
  return a;
}

double **doubleIdentityMatrix(int m) {
  int i,j;
  double **I;
  I=dmatrix(m,m);
  for(i=0;i<m;i++) {
    for (j=0;j<m;j++) {
      I[i][j] = (i==j)? 1.0 : 0.0;;
    }
  }
  return I;
}

double *dvector(int n) {
  double *v;
  v = new double[n];
  return v;
}

void free_dvector(double *v,int n) {
  delete []v;
  return;
}

int *ivector(int n) {
  int *v;
  v = new int[n];
  return v;
}

void free_ivector(int *v,int n) {
  delete []v;
  return;
}

