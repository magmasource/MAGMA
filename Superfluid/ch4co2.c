/* ch4co2.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static doublereal c_b3 = 1.5;
static doublereal c_b5 = .002;

/*      PROGRAM AAA */
/* 1     WRITE (*,*) ' T P ' */
/*      READ  (*,*) T,P */
/*      CALL CO2 (T,P,V,G) */
/*      WRITE (*,*) ' T P V G',T,P,V,G,G/4184.0 */
/*      CALL CH4 (T,P,V,G) */
/*      WRITE (*,*) ' T P V G',T,P,V,G,G/4184.0 */
/*      GO TO 1 */
/*      END */
/* Subroutine */ int kjco2_(doublereal *x, doublereal *t, doublereal *v, doublereal *p)
{
    /* System generated locals */
    doublereal r__1, r__2, r__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal b, r__, y, ct, dt, et, av;

    /* Parameter adjustments */
    --x;

    /* Function Body */
/* Computing 2nd power */
    r__1 = *t;
    ct = (*t * .10721 + 28.31 - r__1 * r__1 * 8.8100000000000004e-6) * 
	    1e6;
/* Computing 2nd power */
    r__1 = *t;
    dt = (9380. - *t * 8.53 + r__1 * r__1 * .0011890000000000002) * 1e6;
/* Computing 2nd power */
    r__1 = *t;
    et = (*t * 715.9 - 368654. + r__1 * r__1 * .1534) * 1e6;

/* Computing 2nd power */
    r__1 = *v;
    av = ct + dt / *v + et / (r__1 * r__1);
    b = 58.;
    r__ = 83.14;
    y = b / 4. / *v;

/* Computing 2nd power */
    r__1 = y;
/* Computing 3rd power */
    r__2 = y;
/* Computing 3rd power */
    r__3 = 1. - y;
    *p = r__ * *t * (y + 1 + r__1 * r__1 - r__2 * (r__2 * r__2)) / *v / (r__3 
	    * (r__3 * r__3)) - av / *v / (*v + b) / sqrt(*t);
    return 0;
} /* kjco2_ */


/* Subroutine */ int kjco2g_(doublereal *t, doublereal *p, doublereal *v, doublereal *g)
{
    /* System generated locals */
    doublereal r__1, r__2, r__3;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal), pow_dd(doublereal *, doublereal *), log(
	    doublereal);

    /* Local variables */
    static doublereal b, r__, y, ct, dt, et, av, vb, pp, zz, rt32;

/* Computing 2nd power */
    r__1 = *t;
    ct = (*t * .10721 + 28.31 - r__1 * r__1 * 8.8100000000000004e-6) * 
	    1e6;
/* Computing 2nd power */
    r__1 = *t;
    dt = (9380. - *t * 8.53 + r__1 * r__1 * .0011890000000000002) * 1e6;
/* Computing 2nd power */
    r__1 = *t;
    et = (*t * 715.9 - 368654. + r__1 * r__1 * .1534) * 1e6;

/* Computing 2nd power */
    r__1 = *v;
    av = ct + dt / *v + et / (r__1 * r__1);
    b = 58.;
    r__ = 83.1451;
    y = b / 4. / *v;

/* Computing 2nd power */
    r__1 = y;
/* Computing 3rd power */
    r__2 = y;
/* Computing 3rd power */
    r__3 = 1. - y;
    pp = r__ * *t * (y + 1 + r__1 * r__1 - r__2 * (r__2 * r__2)) / *v / (r__3 
	    * (r__3 * r__3)) - av / *v / (*v + b) / sqrt(*t);
    zz = pp * *v / r__ / *t;
/*       WRITE (*,*) ' ZZ= ',ZZ */
    d__1 = (doublereal) (*t);
    rt32 = r__ * pow_dd(&d__1, &c_b3);
    vb = *v + b;
/* Computing 3rd power */
    r__1 = 1. - y;
    *g = y * (8. - y * 9. + y * 3. * y) / (r__1 * (r__1 * r__1)) - log(zz) 
	    - ct / rt32 / vb - dt / rt32 / *v / vb - et / rt32 / *v / *v / vb 
	    + ct / rt32 / b * log(*v / vb) - dt / rt32 / b / *v + dt / rt32 / 
	    b / b * log(vb / *v) - et / rt32 / 2. / b / *v / *v + et / rt32 /
	     b / b / *v - et / rt32 / b / b / b * log(vb / *v);
    *g = (*g * r__ * *t + r__ * *t * log(*p)) / 10.;
    return 0;
} /* kjco2g_ */


/* Subroutine */ int co2_(doublereal *t, doublereal *p, doublereal *v, doublereal *g)
{
    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    static doublereal x[13], v0;
    extern /* Subroutine */ int nr_(S_fp, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal eps;
    extern /* Subroutine */ int kjco2_(doublereal *, doublereal *, doublereal *, doublereal *), 
	    kjco2g_(doublereal *, doublereal *, doublereal *, doublereal *);

    if (*p <= 10.) {
	*v = *t * 83.1451 / *p;
	*g = *t * 8.31451 * log(*p);
	return 0;
    }
    if (*p <= 10.) {
	v0 = 1e4;
    }
    if (*p >= 10. && *p <= 60.) {
	v0 = 200.;
    }
    if (*p > 60.) {
	v0 = 20.;
    }
    eps = .001;
    nr_((S_fp)kjco2_, &c_b5, x, t, p, &v0, v);
    kjco2g_(t, p, v, g);
    return 0;
} /* co2_ */


/*     SUBROUTINE NR (FUNCT, EPS, X,T,P,V0,V) */
/*     PARAMETER (NGAS = 13) */
/*     DIMENSION X(NGAS) */
/*     EXTERNAL FUNCT */
/*       VJ  = V0 */
/*       PTRUE = P */
/* 1       CALL FUNCT (X, T,VJ, PJ) */
/*       CALL FUNCTS(FUNCT, X, T,VJ, PJS) */
/*       VJ1 = (PTRUE - PJ)/PJS + VJ */
/*        WRITE (*,*) ' VJ1= ',VJ1 */
/*       IF ( ABS((VJ-VJ1)/VJ1) .LT. EPS) THEN */
/*              V = VJ1 */
/*              RETURN */
/*       ELSE */
/*              VJ = VJ1 */
/*              GOTO 1 */
/*       END IF */
/*       RETURN */
/*       END */

/*       SUBROUTINE FUNCTS ( FUNCT,X, T, V, PS) */
/*        PARAMETER (NGAS = 13) */
/*        DIMENSION X(NGAS) */
/*        EXTERNAL FUNCT */
/*       DV = 0.002 */
/*       VM = V -DV */
/*       VP = V +DV */
/*       CALL FUNCT (X, T, VM, PM) */
/*       CALL FUNCT (X, T, VP, PP) */
/*       PS = (PP-PM)/2.0/DV */
/*       RETURN */
/*       END */

/* Subroutine */ int kjch4_(doublereal *x, doublereal *t, doublereal *v, doublereal *p)
{
    /* System generated locals */
    doublereal r__1, r__2, r__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal b, r__, y, ct, dt, et, av;

    /* Parameter adjustments */
    --x;

    /* Function Body */
/* Computing 2nd power */
    r__1 = *t;
    ct = *t * 92800. + 1.3403e7 + r__1 * r__1 * 2.7;
/* Computing 2nd power */
    r__1 = *t;
    dt = 5.216e9 - *t * 6.8e6 + r__1 * r__1 * 3280.;
/* Computing 2nd power */
    r__1 = *t;
    et = *t * 6.738e8 - 233219999999.99997 + r__1 * r__1 * 317900.;

/* Computing 2nd power */
    r__1 = *v;
    av = ct + dt / *v + et / (r__1 * r__1);
    b = 60.;
    r__ = 83.1451;
    y = b / 4. / *v;

/* Computing 2nd power */
    r__1 = y;
/* Computing 3rd power */
    r__2 = y;
/* Computing 3rd power */
    r__3 = 1. - y;
    *p = r__ * *t * (y + 1 + r__1 * r__1 - r__2 * (r__2 * r__2)) / *v / (r__3 
	    * (r__3 * r__3)) - av / *v / (*v + b) / sqrt(*t);
    return 0;
} /* kjch4_ */


/* Subroutine */ int kjch4g_(doublereal *t, doublereal *p, doublereal *v, doublereal *g)
{
    /* System generated locals */
    doublereal r__1, r__2, r__3;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal), pow_dd(doublereal *, doublereal *), log(
	    doublereal);

    /* Local variables */
    static doublereal b, r__, y, ct, dt, et, av, vb, pp, zz, rt32;

/* Computing 2nd power */
    r__1 = *t;
    ct = *t * 92800. + 1.3403e7 + r__1 * r__1 * 2.7;
/* Computing 2nd power */
    r__1 = *t;
    dt = 5.216e9 - *t * 6.8e6 + r__1 * r__1 * 3280.;
/* Computing 2nd power */
    r__1 = *t;
    et = *t * 6.738e8 - 233219999999.99997 + r__1 * r__1 * 317900.;

/* Computing 2nd power */
    r__1 = *v;
    av = ct + dt / *v + et / (r__1 * r__1);
    b = 60.;
    r__ = 83.1451;
    y = b / 4. / *v;

/* Computing 2nd power */
    r__1 = y;
/* Computing 3rd power */
    r__2 = y;
/* Computing 3rd power */
    r__3 = 1. - y;
    pp = r__ * *t * (y + 1 + r__1 * r__1 - r__2 * (r__2 * r__2)) / *v / (r__3 
	    * (r__3 * r__3)) - av / *v / (*v + b) / sqrt(*t);
    zz = pp * *v / r__ / *t;
/*       WRITE (*,*) ' ZZ= ',ZZ */
    d__1 = (doublereal) (*t);
    rt32 = r__ * pow_dd(&d__1, &c_b3);
    vb = *v + b;
/* Computing 3rd power */
    r__1 = 1. - y;
    *g = y * (8. - y * 9. + y * 3. * y) / (r__1 * (r__1 * r__1)) - log(zz) 
	    - ct / rt32 / vb - dt / rt32 / *v / vb - et / rt32 / *v / *v / vb 
	    + ct / rt32 / b * log(*v / vb) - dt / rt32 / b / *v + dt / rt32 / 
	    b / b * log(vb / *v) - et / rt32 / 2. / b / *v / *v + et / rt32 /
	     b / b / *v - et / rt32 / b / b / b * log(vb / *v);
    *g = (*g * r__ * *t + r__ * *t * log(*p)) / 10.;
    return 0;
} /* kjch4g_ */


/* Subroutine */ int ch4_(doublereal *t, doublereal *p, doublereal *v, doublereal *g)
{
    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    static doublereal x[13], v0;
    extern /* Subroutine */ int nr_(S_fp, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal eps;
    extern /* Subroutine */ int kjch4_(doublereal *, doublereal *, doublereal *, doublereal *), 
	    kjch4g_(doublereal *, doublereal *, doublereal *, doublereal *);

    if (*p <= 6.) {
	*v = *t * 83.1451 / *p;
	*g = *t * 8.31451 * log(*p);
	return 0;
    }
    if (*p <= 10.) {
	v0 = 1e3;
    }
    if (*p > 10. && *p <= 60.) {
	v0 = 200.;
    }
    if (*p > 60.) {
	v0 = 20.;
    }
    eps = .002;
    nr_((S_fp)kjch4_, &eps, x, t, p, &v0, v);
    kjch4g_(t, p, v, g);
    return 0;
} /* ch4_ */

