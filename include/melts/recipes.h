#ifndef _Recipes_h
#define _Recipes_h

/*
MELTS Source Code: RCS $Log: recipes.h,v $
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:36  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:48:56  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 3.6  1997/06/21  22:49:29  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.5  1997/05/03  20:23:08  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:12  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:33:22  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.1  1995/08/18  19:12:14  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  19:12:14  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Include module for all function and structure declarations 
**      for implementation of the math library described in:
**
**      Press, W.H., Flannery, B.P., Teukolsky, S.A. and Vetterling, W.T.
**      (1988) Numerical Recipes in C
**      Cambridge University Press, New York, 735 pages 
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  May 1, 1991
**              Taken from NR.H supplied with the above volume,
**              and reformatted for ANSI declarations
**      V1.0-2  Mark S. Ghiorso  July 31, 1991
**              Eliminated unnecessary definitions and modified argument
**              list for svbksb
**--
*/

void          nrerror(char error_text[]);
double        *vector(long nl, long nh);
int           *ivector(long nl, long nh);
unsigned char *cvector(long nl, long nh);
unsigned long *lvector(long nl, long nh);
double        *dvector(long nl, long nh);
double        **matrix(long nrl, long nrh, long ncl, long nch);
double        **dmatrix(long nrl, long nrh, long ncl, long nch);
int           **imatrix(long nrl, long nrh, long ncl, long nch);
double        **submatrix(double **a, long oldrl, long oldrh, long oldcl, long oldch, long newrl, long newcl);
double        **convert_matrix(double *a, long nrl, long nrh, long ncl, long nch);
double        ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh);
void free_vector(double *v, long nl, long nh);
void free_ivector(int *v, long nl, long nh);
void free_cvector(unsigned char *v, long nl, long nh);
void free_lvector(unsigned long *v, long nl, long nh);
void free_dvector(double *v, long nl, long nh);
void free_matrix(double **m, long nrl, long nrh, long ncl, long nch);
void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch);
void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch);
void free_submatrix(double **b, long nrl, long nrh, long ncl, long nch);
void free_convert_matrix(double **b, long nrl, long nrh, long ncl, long nch);
void free_f3tensor(double ***t, long nrl, long nrh, long ncl, long nch, long ndl, long ndh);

void covsrt(double **covar, int ma, int ia[], int mfit);
void gaussj(double **a, int n, double **b, int m);
void indexx(unsigned long n, double arr[], unsigned long indx[]);
void mrqcof(double x[], double y[], double sig[], int ndata, double a[],
	int ia[], int ma, double **alpha, double beta[], double *chisq,
	void (*funcs)(double, double [], double *, double [], int));
void mrqmin(double x[], double y[], double sig[], int ndata, double a[],
	int ia[], int ma, double **covar, double **alpha, double *chisq,
	void (*funcs)(double, double [], double *, double [], int), double *alamda);
double pythag(double a, double b);
void simplx(double **a, int m, int n, int m1, int m2, int m3, int *icase, int izrov[], int iposv[]);
void svbksb(double **u, double w[], double **v, int m, int n, double b[],
	char e[], double x[]);
void svdcmp(double **a, int m, int n, double w[], double **v);
void svdfit(double x[], double y[], double sig[], int ndata, double a[],
	int ma, double **u, double **v, double w[], double *chisq,
	void (*funcs)(double, double [], int));
void svdvar(double **v, int ma, double w[], double **cvm);

#endif /* _Recipes_h */
