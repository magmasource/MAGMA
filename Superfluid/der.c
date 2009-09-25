/* der.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Subroutine */ int fder_(doublereal *xx, doublereal *tt, doublereal *pp, 
	doublereal *vv, doublereal *gg, doublereal *ggi)
{
    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    static doublereal g;
    static integer i__;
    static doublereal p, t, v, x[13], gi[13];
    static integer ii;
    extern /* Subroutine */ int flder_(doublereal *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *);
    static doublereal gnder[13], xstep;

    /* Parameter adjustments */
    --ggi;
    --xx;

    /* Function Body */
    t = *tt;
    p = *pp;
    xstep = 1e-8;
    for (i__ = 1; i__ <= 13; ++i__) {
	if (xx[i__] > 0. && xx[i__] <= xstep) {
	    x[i__ - 1] = xstep;
	} else {
	    x[i__ - 1] = (doublereal) xx[i__];
	}
/* L3: */
    }
    flder_(x, &t, &p, &v, &g, gnder);
    for (ii = 1; ii <= 13; ++ii) {
	if (xx[ii] > 0.) {
	    g += xx[ii] * log(xx[ii]) * 8.31451 * t;
	}
/* L77: */
    }
    *gg = 0.;
    for (i__ = 1; i__ <= 13; ++i__) {
	gi[i__ - 1] = gnder[i__ - 1];
/* L2: */
    }
    *vv = v;
    *gg = g;
    for (i__ = 1; i__ <= 13; ++i__) {
	if (xx[i__] > 0.) {
	    ggi[i__] = gi[i__ - 1] + log(xx[i__]) * 8.31451 * t;
	} else {
	    ggi[i__] = gi[i__ - 1];
	}
/* L4: */
    }
    return 0;
} /* fder_ */


/* Subroutine */ int flder_(doublereal *x, doublereal *t, doublereal *p, doublereal *v, doublereal *g, doublereal 
	*gnder)
{
    static integer i__;
    static doublereal vd, dni, prod, xdxi[13], xeps;
    extern /* Subroutine */ int fluid_(doublereal *, doublereal *, doublereal *, doublereal *, doublereal *)
	    ;
    static doublereal gplus, xexist;
    extern /* Subroutine */ int xtoxdx_(integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

/*           common /xeps/ xeps */

/* Calculation of Gibbs enery partial derivatives on composition */
/* Result: GXDER (1:NGAS, 1:NGAS) */

    /* Parameter adjustments */
    --gnder;
    --x;

    /* Function Body */
    xeps = 2e-8;
    xexist = 1e-45;

    fluid_(&x[1], t, p, v, g);
    prod = 1e3;
    dni = .001;
    for (i__ = 1; i__ <= 13; ++i__) {
	gnder[i__] = 0.;
	if (x[i__] > xexist) {
	    xtoxdx_(&i__, &x[1], xdxi, &dni, &prod);
	    fluid_(xdxi, t, p, &vd, &gplus);
	    gnder[i__] = (gplus * (dni + 1) - *g) / dni;
	}
/* L1: */
    }

    return 0;
} /* flder_ */

/* Subroutine */ int xtoxdx_(integer *j, doublereal *x, doublereal *xdxj, doublereal *dnj, doublereal 
	*prod)
{
    static integer i__;
    static doublereal s, bulk[13];

    /* Parameter adjustments */
    --xdxj;
    --x;

    /* Function Body */
    s = 0.;
    for (i__ = 1; i__ <= 13; ++i__) {
	bulk[i__ - 1] = x[i__] * *prod;
	s += bulk[i__ - 1];
/* L1: */
    }
    bulk[*j - 1] += *dnj * *prod;
    s += *dnj * *prod;
    for (i__ = 1; i__ <= 13; ++i__) {
	xdxj[i__] = bulk[i__ - 1] / s;
/* L2: */
    }
    return 0;
} /* xtoxdx_ */

