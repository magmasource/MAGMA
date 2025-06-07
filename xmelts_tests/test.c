#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

static double mylog(double x) {
  double result = log(x);
  return result;
}

static long double mylogl(long double x) {
  long double result = logl(x);
  return result; 
}

int main () {
  int lenLD = sizeof(long double);
  int lenD  = sizeof(double);
  printf("Length of LD = %d, length of D = %d\n", lenLD, lenD);
  printf("FLT_EPSILON  = %20.13g\n", FLT_EPSILON); 
  printf("DBL_EPSILON  = %20.13g\n", DBL_EPSILON); 
  printf("LDBL_EPSILON = %20.13g\n", LDBL_EPSILON); 
  printf("FLT_MIN      = %20.13g\n", FLT_MIN); 
  printf("DBL_MIN      = %20.13g\n", DBL_MIN); 
  printf("LDBL_MIN     = %20.13g\n", LDBL_MIN); 
  printf("FLT_MAX      = %20.13g\n", FLT_MAX); 
  printf("DBL_MAX      = %20.13g\n", DBL_MAX); 
  printf("LDBL_MAX     = %20.13g\n", LDBL_MAX); 
  printf("log(2.0) LD  = %40.33g\n", mylogl(2.0));
  printf("log(2.0)  D  = %40.33g\n", mylog(2.0));
  printf("log(2.0)  F  = %40.33g\n", logf(2.0));
}
