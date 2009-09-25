/* fluid.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Subroutine */ int fluid_(doublereal *x, doublereal *t, doublereal *p, doublereal *v, doublereal *g)
{
    static doublereal gi[13];
    extern /* Subroutine */ int shi_(doublereal *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal gdiv, pdiv, tdiv, vdiv;
    extern /* Subroutine */ int tolja_(doublereal *, doublereal *, doublereal *, doublereal *, doublereal *)
	    ;
    static doublereal gdivp;


/* C */
/* C********************************************************************** */
/*       X (NGAS) - MOLE FRACTIONS OF GASES */
/*       T        - TEMPERATURE         (K) */
/*       P        - PRESSURE            (BAR) */
/*       V        - VOLUME OF MIXTURE   (CM3/MOLE) */
/*       G        - GIBBS ENERGY        (J/MOLE) */
/*       GDIVP    - FUGACITY OF MIXTURE COUNTING FROM 5000 BAR (J/MOLE) */
/* C -------------------------------------------------------------------- */
/*         1 - H2O, 2 - CO2,  3 - CH4,  4 - CO,    5 - O2, */
/*         6 - H2,  7 - S2,   8 - SO2,  9 - COS,  10 - H2S, */
/*        11 - N2, 12 - NH3, 13 - Ar */
/* C********************************************************************** */
/* C */
    /* Parameter adjustments */
    --x;

    /* Function Body */
    pdiv = 4999.;
    tdiv = 400.;
    if (x[1] > 1e-7) {
	tdiv = 700.;
    }

    if (*t < tdiv || *p < pdiv) {
	shi_(&x[1], t, p, v, g, gi);
	return 0;
    } else {
	shi_(&x[1], t, &pdiv, &vdiv, &gdiv, gi);
	tolja_(&x[1], t, p, v, &gdivp);
	*g = gdiv + gdivp;
    }

    return 0;
} /* fluid_ */

