/* The following values are used to test for too small
   and too large values of v for an integer fraction to
   represent.

   These values are currently set for the amdal 5890.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 4.0e+10
#define MIN 3.0e-10

double
frac(v, n, d, error)
double v, error;
int *n, *d;
{
	/*
	  given a number, v, this function outputs two integers,
	  d and n, such that

		v = n / d

	  to accuracy
		epsilon = | (v - n/d) / v | <= error

	  input:  v = decimal number you want replaced by fraction.
		  error = accuracy to which the fraction should
			  represent the number v.

	  output:  n = numerator of representing fraction.
		   d = denominator of representing fraction.

	  return value:  -1.0 if (v < MIN || v > MAX || error < 0.0)
			 | (v - n/d) / v | otherwise.

	  Note:  This program only works for positive numbers, v.

	  reference:  Jerome Spanier and Keith B. Oldham, "An Atlas
		of Functions," Springer-Verlag, 1987, pp. 665-7.
	*/

	int D, N, t;
	double epsilon, r, m, fabs();


	if (v < MIN || v > MAX || error < 0.0)
		return(-1.0);
	*d = D = 1;
	*n = (int)v;
	N = (*n) + 1;
	goto three;

one:	if (r > 1.0)
		goto two;
	r = 1.0/r;
two:	N += (*n)*(int)r;
	D += (*d)*(int)r;
	(*n) += N;
	(*d) += D;
three:	r = 0.0;
	if (v*(*d) == (double)(*n))
		goto four;
	r = (N - v*D)/(v*(*d) - (*n));
	if (r > 1.0)
		goto four;
	t = N;
	N = (*n);
	*n = t;
	t = D;
	D = (*d);
	*d = t;
four:	epsilon = fabs(1.0 - (*n)/(v*(*d)));
	if (epsilon <= error)
		goto six;
	m = 1.0;
	do {
		m *= 10.0;
	} while (m*epsilon < 1.0);
	epsilon = 1.0/m * ((int)(0.5 + m*epsilon));
six:	if (epsilon <= error)
		return(epsilon);
	if (r != 0.0)
		goto one;
	return(-1.0);
}
