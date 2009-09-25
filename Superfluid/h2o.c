/* h2o.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct ceps_1_ {
    doublereal eps;
};
struct ceps_2_ {
    doublereal epse;
};

#define ceps_1 (*(struct ceps_1_ *) &ceps_)
#define ceps_2 (*(struct ceps_2_ *) &ceps_)

struct cfunc_1_ {
    doublereal tf[58], tsav, df[15], dsav, ex[7], exd[7], exdd[7];
};

#define cfunc_1 (*(struct cfunc_1_ *) &cfunc_)

struct equ_1_ {
    doublereal g[58];
    integer idpot[58], itpot[58], imaxf[8], iex, nt;
};

#define equ_1 (*(struct equ_1_ *) &equ_)

struct cnorm_1_ {
    doublereal tnorm, dnorm;
};

#define cnorm_1 (*(struct cnorm_1_ *) &cnorm_)

struct cfac_1_ {
    doublereal factor;
};

#define cfac_1 (*(struct cfac_1_ *) &cfac_)

struct ccpeq_1_ {
    doublereal tceq, pceq, dceq;
};

#define ccpeq_1 (*(struct ccpeq_1_ *) &ccpeq_)

struct cfni_1_ {
    doublereal b2, b[7], tpid[7];
    integer npol, n;
};

#define cfni_1 (*(struct cfni_1_ *) &cfni_)

struct cnullp_1_ {
    doublereal t0, d0, f0, h0, u0, s0, g0;
};

#define cnullp_1 (*(struct cnullp_1_ *) &cnullp_)

struct csub1_1_ {
    char hsub[8];
};

#define csub1_1 (*(struct csub1_1_ *) &csub1_)

struct csub2_1_ {
    doublereal rg, xmol, tc, pc, dc;
};
struct csub2_2_ {
    doublereal r__, xmol, tc, pc, dc;
};

#define csub2_1 (*(struct csub2_1_ *) &csub2_)
#define csub2_2 (*(struct csub2_2_ *) &csub2_)

struct csub3_1_ {
    doublereal ttr, ptr, dltr, dvtr, tb, pb, dlb, dvb;
};
struct csub3_2_ {
    doublereal ttr, ptr, dltr, dvtr, tb, pboil, dlb, dvb;
};
struct csub3_3_ {
    doublereal ttr, ptr, dltr, dvtr, tbb, pbb, dlbb, dvbb;
};

#define csub3_1 (*(struct csub3_1_ *) &csub3_)
#define csub3_2 (*(struct csub3_2_ *) &csub3_)
#define csub3_3 (*(struct csub3_3_ *) &csub3_)

struct csub4_1_ {
    doublereal fw, fc;
};

#define csub4_1 (*(struct csub4_1_ *) &csub4_)

struct {
    integer nin, nout;
} cout_;

#define cout_1 cout_

struct cvpeq_1_ {
    doublereal g[6], tpot[6], tc, pc;
    integer n;
};

#define cvpeq_1 (*(struct cvpeq_1_ *) &cvpeq_)

struct calpeq_1_ {
    doublereal g[5], tpot[5], tc, a0, da0, dphi0;
    integer n;
};

#define calpeq_1 (*(struct calpeq_1_ *) &calpeq_)

struct cmelteq_1_ {
    doublereal g[7], tp[7], tt[7], pt[7];
    integer ig[7];
};

#define cmelteq_1 (*(struct cmelteq_1_ *) &cmelteq_)

/* Initialized data */

struct {
    doublereal e_1[15];
    integer e_2[2];
    } cfni_ = { { 3.00632, -8.317709547068, 6.681504888442, .12436, .97315, 
	    1.2795, .96956, .24873, 0., 1., 1.287202151, 3.537101709, 
	    7.740210774, 9.243749421, 27.5056402}, {2, 7} };

struct {
    doublereal e_1[7];
    } cnullp_ = { { 273.16, 999.787398238, 0., 0., 0., 0., 0.} };

struct {
    char e_1[8];
    } csub1_ = { "WATER   " };

struct {
    doublereal e_1[5];
    } csub2_ = { { 4.6151805e-4, 18.0152, 647.14, 22.064, 322.} };

struct {
    doublereal e_1[8];
    } csub3_ = { { 273.16, 6.11646e-4, 999.789, .00485195, 373.15, .101325, 
	    958.364, .597209 } };

struct {
    doublereal e_1[2];
    } csub4_ = { { 1e6, 1e3 } };

struct {
    doublereal e_1;
    } ceps_ = { 1e-8 };

struct {
    doublereal fill_1[75];
    doublereal e_2;
    doublereal fill_3[6];
    doublereal e_4;
    doublereal fill_5[6];
    doublereal e_6;
    doublereal fill_7[6];
    } cfunc_ = { {0}, 1., {0}, 0., {0}, 0. };

struct {
    doublereal e_1[38];
    doublereal fill_2[20];
    integer e_3[38];
    doublereal fill_4[10];
    integer e_5[38];
    doublereal fill_6[10];
    integer e_7[10];
    } equ_ = { { .2330009013, -1.402091128, .1172248041, -.1850749499, 
	    .1770110422, .05525151794, -3.41325738e-4, 8.557274367e-4, 
	    3.716900685e-4, -1.308871233e-4, 3.216895199e-5, 2.785881034e-7, 
	    -.352151113, .07881914536, -.0151966661, -.1068458586, 
	    -.2055046288, .9146198012, 3.213343569e-4, -1.133591391, 
	    -.3107520749, 1.217901527, -.4481710831, .05494218772, 
	    -8.665222096e-5, .03844084088, .009853044884, -.01767598472, 
	    .001488549222, -.003070719069, .00388080328, -.002627505215, 
	    5.258371388e-4, -.1716396901, .07188823624, .05881268357, 
	    -.0145593888, -.012161394 }, {0}, {1, 1, 2, 2, 2, 2, 3, 5, 5, 6, 7, 
	    8, 1, 1, 1, 2, 3, 3, 3, 4, 5, 5, 6, 7, 7, 8, 8, 9, 11, 11, 11, 11,
	     11, 2, 2, 3, 3, 5}, {0}, {0, 2, 0, 1, 2, 3, 5, 0, 1, 3, 2, 5, 5, 7,
	     9, 5, 4, 6, 13, 5, 2, 3, 2, 0, 11, 1, 4, 0, 0, 3, 5, 6, 7, 13, 
	    14, 15, 24, 15}, {0}, {0, 12, 12, 33, 38, 38, 38, 38, 3, 38} };

struct {
    doublereal e_1[2];
    } cnorm_ = { {647.14, 322.} };

struct {
    doublereal e_1;
    } cfac_ = { 1. };

struct {
    doublereal e_1[14];
    integer e_2;
    } cvpeq_ = { {-7.85823, 1.83991, -11.7811, 22.6705, -15.9393, 1.77516, 1., 
	    1.5, 3., 3.5, 4., 7.5, 647.14, 22.064}, 6 };

struct {
    doublereal e_1[14];
    integer e_2;
    } calpeq_ = { {-5.71756e-8, 2689.81, 129.889, -137.181, .968874, -19., 1., 
	    4.5, 5., 54.5, 647.14, 1., -1135.481615639, 2318.9142}, 5 };

struct {
    doublereal e_1[28];
    integer e_2[7];
    } cmelteq_ = { {6.04e5, 0., -.295123, 0., -1.18685, -1.07476, -.814894, 
	    10., 0., 60., 0., 8., 4.6, 1.92, 273.16, 0., 251.16, 0., 256.16, 
	    273.31, 355., 6.11659e-4, 0., 209.9, 0., 350.1, 632.4, 2216.}, {1, 
	    0, 1, 0, 1, 1, 2} };

struct {
    doublereal e_1[3];
    } ccpeq_ = { {647.14, 22.064, 322.} };


/* Table of constant values */

static integer c__1 = 1;
static integer c__2 = 2;
static integer c__9 = 9;
static integer c__5 = 5;
static doublereal c_b138 = 2.4e4;
static doublereal c_b143 = .5;
static doublereal c_b144 = .33333333333333331;

/*         program aaa */
/*      write (6,*) ' t p ' */
/*     read (5,*) t,p */
/*     call h2o (t,p, v,g) */
/*     write (6,*) ' t p v g  ',t,p,v,g */
/*     go to 1 */
/*     end */

/* Subroutine */ int h2o_(doublereal *t, doublereal *p, doublereal *v, doublereal *g)
{
    static doublereal p1, t8;
    extern doublereal db_(doublereal *, doublereal *), gb_(doublereal *, 
	    doublereal *);
    static doublereal dens, pmpa, dens1;
    static doublereal gibbs1, gibbs2;

    t8 = *t;
    pmpa = *p / 10.;
/*     write (6,*) ' t8= ',t8,' pmpa= ',pmpa */
    dens = db_(&t8, &pmpa);
/*      write (6,*) ' dens ',dens */
    p1 = .1;
    dens1 = db_(&t8, &p1);
/*     write (6,*) ' dens1= ', dens1 */
    gibbs1 = gb_(&t8, &dens);
    gibbs2 = gb_(&t8, &dens1);
    *v = 1. / dens * 1e6 * .018030000000000001;
    *g = (gibbs1 - gibbs2) * 18.03;
    return 0;
} /* h2o_ */

/* **************************************************************************** */
/* Subroutine */ int real38_(void)
{
    return 0;
} /* real38_ */

/* ***************************************************************************** */


/*   THIS SUBROUTINE SETS COEFFICIENTS FOR THE */
/*   SAUL AND WAGNER -EQUATION OF STATE */




/*        D     T      D     T      D     T      D     T */








/* **************************************************************************** */

/*           SET OF SUBROUTINES AND FUNCTIONS TO CALCULATE      19.10.90 */
/*           VARIOUS DERIVATIVES OF AN EQUATION FOR THE */
/*           NORMALIZED REAL AND IDEAL PART OF THE */
/*           HELMHOLTZ FUNCTION F. */

/* **************************************************************************** */
/*    USUAL INPUT */

/*    T    TEMPERATURE (NOT NORMALIZED) */
/*    D    DENSITY (NOT NORMALIZED) */


/* ******************************************************************** */

/*    The following program with functions and subroutines should be */
/*    used like a library. You can call various Thermodynamic */
/*    Properties listed in the table below : */

/*                                          F = FUNCTION */
/*                                          S = SUBROUTINE */


/* F <DB>     THIS FUNCTION CALCULATES THE DENSITY FOR GIVEN P,T */

/* F <PB>     THIS FUNCTION CALCULATES THE PRESSURE */

/* F <DPDTB>  1.DERIVATIVE OF PRESSURE VERSUS TEMPERATURE */

/* F <DPDDB>  1.DERIVATION OF PRESSURE VERSUS DENSITY */

/* F <CVB>    ISOCHORIC HEAT CAPACITY */

/* F <CPB>    ISOBARIC HEAT CAPACITY */

/* F <WB>     VELOCITY OF SOUND */

/* F <FB>     HELMHOLTZ FUNCTION */

/* F <HB>     ENTHALPY */

/* F <SB>     ENTROPY */

/* F <UB>     INTERNAL ENERGY */

/* F <GB>     GIBBS ENERGY */

/* F <BETASB> ISENTROPIC TEMPERATURE-PRESSURE COEFFICIENT BETAS=(DT/DP)s */

/* F <BB>     2. VIRIALCOEFFICIENT B FOR GIVEN T */

/* F <CB>     3. VIRIALCOEFFICIENT C FOR GIVEN T */

/* F <RJTB>   Joule Thomson Coefficient */

/* F <DTB>    Isothermal throttling coefficient */


/*            Saturation lines */


/* S <SATT>   CALCULATING DV,DL,P FOR GIVEN T */

/* S <SATP>   CALCULATING T,DV,DL FOR GIVEN P */

/* F <TSEQ>   CALCULATING TS FOR A GIVEN P FROM SAT-EQUATION */

/* S <VPEQL>  LINEAR EXTRAPOLATION OF THE VAPOR-PRESSURE FOR GIVEN T */

/* S <SLEQ>   CALCULATION OF SATURATED LIQUID ENTROPY FOR GIVEN T */

/* S <SVEQ>   CALCULATION OF SATURATED VAPOR ENTROPY FOR GIVEN T */

/* S <HLEQ>   CALCULATION OF SATURATED LIQUID ENTHALPY FOR GIVEN T */

/* S <HVEQ>   CALCULATION OF SATURATED VAPOR ENTHALPY FOR GIVEN T */

/* S <VPEQ>   VAPOUR PRESSURE FOR GIVEN T */

/* S <DLEQ>   SATURATED LIQUID DENSITY FOR GIVEN T */

/* S <DVEQ>   SATURATED VAPOUR DENSITY FOR GIVEN T */

/* S <DPDTEQ> 1. DERIVATION OF VAPORPRESSURE P VERSUS TEMPERATURE T FOR */
/*            GIVEN T */

/* F <PMELT>  MELTING PRESSURE FOR GIVEN TEMPERATURE */

/* S <TMELT>  MELTING TEMPERATURE FOR GIVEN PRESSURE */

/* F <PSUBL>  SUBLIMATION-PRESSURE FOR GIVEN T */


/*     Further information about handling the subroutines and functions You */
/*     will find in the programs, which are usually well documented. */


/* ****************************************************************************** */
/* ****************************************************************************** */
/* Subroutine */ int tfunc_(doublereal *t)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__;
    static doublereal tn;

/* ****************************************************************************** */

/*    T-FUNCTION */


    tn = cnorm_1.tnorm / *t;
    i__1 = equ_1.nt;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L10: */
	d__1 = equ_1.itpot[i__ - 1] / cfac_1.factor;
	cfunc_1.tf[i__ - 1] = equ_1.g[i__ - 1] * pow_dd(&tn, &d__1);
    }

    cfunc_1.tsav = *t;
    return 0;
} /* tfunc_ */


/* ****************************************************************************** */
/* Subroutine */ int dfunc_(doublereal *d__)
{
    static integer i__;
    static doublereal dn;
    extern /* Subroutine */ int efunc_(void);

/* ****************************************************************************** */

/*    D-FUNCTION */


    dn = *d__ / cnorm_1.dnorm;
    cfunc_1.df[0] = 1. / dn;
    for (i__ = 0; i__ <= 13; ++i__) {
/* L10: */
	cfunc_1.df[i__ + 1] = cfunc_1.df[i__] * dn;
    }

    cfunc_1.dsav = *d__;
    efunc_();
    return 0;
} /* dfunc_ */


/* ****************************************************************************** */
/* Subroutine */ int efunc_(void)
{
    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static integer j;
    static doublereal e1, e2;

/* ****************************************************************************** */

/*    THIS FUNCTION CALCULATES THE DN-DERIVATIVES OF THE */
/*    E-FUNCTION */


/*       E**(-DN**J) */

    for (j = 1; j <= 3; ++j) {
	cfunc_1.ex[j] = exp(-cfunc_1.df[j + 1]);
	cfunc_1.exd[j] = -j * cfunc_1.df[j] * cfunc_1.ex[j];
/* L10: */
	cfunc_1.exdd[j] = (j - 1 - j * cfunc_1.df[j + 1]) * cfunc_1.df[0] * 
		cfunc_1.exd[j];
    }

    if (equ_1.iex != 6) {
	return 0;
    }

/*        E**(-0.4*DN**J) - E**(-2*DN**6) */

    if (cfunc_1.df[2] < .2) {
	cfunc_1.ex[6] = (1.6 - cfunc_1.df[7] * 1.92) * cfunc_1.df[7];
	cfunc_1.exd[6] = (9.6 - cfunc_1.df[7] * 23.04) * cfunc_1.df[6];
	cfunc_1.exdd[6] = (48. - cfunc_1.df[7] * 253.44) * cfunc_1.df[5];
    } else {
/* *************-Comment-************************************** */
/* *                                                          * */
/* * In some cases the following two statements will yield    * */
/* * values very close to zero. Be shure, that Your system    * */
/* * is able to calculate these values. */
/* *                                                          * */
/* ************************************************************ */
	e1 = exp(cfunc_1.df[7] * -.4);
	e2 = exp(cfunc_1.df[7] * -2.);
	cfunc_1.ex[6] = e1 - e2;
	cfunc_1.exd[6] = (e2 * 12. - e1 * 2.4) * cfunc_1.df[6];
	cfunc_1.exdd[6] = (e1 * 5.76 - e2 * 144.) * cfunc_1.df[11] + 
		cfunc_1.exd[6] * 5. * cfunc_1.df[0];
    }

    return 0;
} /* efunc_ */


/* ****************************************************************************** */
doublereal fnr_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal ret_val, d__1, d__2;

    /* Local variables */
    static doublereal h__;
    static integer i__, j;
    static doublereal fnrs;
    extern /* Subroutine */ int dfunc_(doublereal *);
    static doublereal dsave;
    extern /* Subroutine */ int tfunc_(doublereal *);
    static doublereal tsave;

/* ****************************************************************************** */

/*    THIS FUNCTION CALCULATES F'S NORMALIZED REAL PART. */


    if ((d__1 = *t - tsave, abs(d__1)) < ceps_1.eps && (d__2 = (*d__ - dsave) 
	    / *d__, abs(d__2)) < ceps_1.eps) {
	ret_val = fnrs;
	return ret_val;
    }

    ret_val = 0.;

    if ((d__1 = cfunc_1.tsav - *t, abs(d__1)) > ceps_1.eps) {
	tfunc_(t);
    }
    if ((d__1 = cfunc_1.dsav - *d__, abs(d__1)) / *d__ > ceps_1.eps) {
	dfunc_(d__);
    }

    i__1 = equ_1.iex;
    for (j = 0; j <= i__1; ++j) {
	if (equ_1.imaxf[j] == equ_1.imaxf[j + 1]) {
	    goto L30;
	}
	h__ = 0.;
	i__2 = equ_1.imaxf[j + 1];
	for (i__ = equ_1.imaxf[j] + 1; i__ <= i__2; ++i__) {
	    h__ += cfunc_1.tf[i__ - 1] * cfunc_1.df[equ_1.idpot[i__ - 1] + 1];
/* L20: */
	}
	ret_val += h__ * cfunc_1.ex[j];
L30:
	;
    }

    fnrs = ret_val;
    tsave = *t;
    dsave = *d__;

    return ret_val;
} /* fnr_ */

/* ****************************************************************************** */
doublereal fnrd_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal ret_val, d__1, d__2;

    /* Local variables */
    static integer i__, j;
    static doublereal exdn;
    extern /* Subroutine */ int dfunc_(doublereal *);
    static doublereal dsave, fnrds;
    extern /* Subroutine */ int tfunc_(doublereal *);
    static doublereal tsave;

/* ****************************************************************************** */

/*    THIS FUNCTION CALCULATES THE 1ST DN */
/*    DERIVATIVE OF THE F'S NORMALIZED REAL PART. */


    if ((d__1 = *t - tsave, abs(d__1)) < ceps_1.eps && (d__2 = (*d__ - dsave) 
	    / *d__, abs(d__2)) < ceps_1.eps) {
	ret_val = fnrds;
	return ret_val;
    }

    ret_val = 0.;

    if ((d__1 = cfunc_1.tsav - *t, abs(d__1)) > ceps_1.eps) {
	tfunc_(t);
    }
    if ((d__1 = cfunc_1.dsav - *d__, abs(d__1)) / *d__ > ceps_1.eps) {
	dfunc_(d__);
    }

    i__1 = equ_1.imaxf[1];
    for (i__ = 1; i__ <= i__1; ++i__) {
	ret_val += cfunc_1.tf[i__ - 1] * equ_1.idpot[i__ - 1] * cfunc_1.df[
		equ_1.idpot[i__ - 1]];
/* L10: */
    }

    i__1 = equ_1.iex;
    for (j = 1; j <= i__1; ++j) {
	if (equ_1.imaxf[j] == equ_1.imaxf[j + 1]) {
	    goto L30;
	}
	exdn = cfunc_1.ex[j] * cfunc_1.df[0];
	i__2 = equ_1.imaxf[j + 1];
	for (i__ = equ_1.imaxf[j] + 1; i__ <= i__2; ++i__) {
	    ret_val += cfunc_1.tf[i__ - 1] * (cfunc_1.exd[j] + exdn * 
		    equ_1.idpot[i__ - 1]) * cfunc_1.df[equ_1.idpot[i__ - 1] + 
		    1];
/* L20: */
	}
L30:
	;
    }

    fnrds = ret_val;
    tsave = *t;
    dsave = *d__;

    return ret_val;
} /* fnrd_ */

/* ****************************************************************************** */
doublereal fnrt_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal ret_val, d__1, d__2;

    /* Local variables */
    static doublereal h__;
    static integer i__, j;
    extern /* Subroutine */ int dfunc_(doublereal *);
    static doublereal dsave;
    extern /* Subroutine */ int tfunc_(doublereal *);
    static doublereal tsave, fnrts;

/* ****************************************************************************** */

/*    THIS FUNCTION CALCULATES THE 1ST TN */
/*    DERIVATIVE OF THE F'S NORMALIZED REAL PART. */


    if ((d__1 = *t - tsave, abs(d__1)) < ceps_1.eps && (d__2 = (*d__ - dsave) 
	    / *d__, abs(d__2)) < ceps_1.eps) {
	ret_val = fnrts;
	return ret_val;
    }

    ret_val = 0.;

    if ((d__1 = cfunc_1.tsav - *t, abs(d__1)) > ceps_1.eps) {
	tfunc_(t);
    }
    if ((d__1 = cfunc_1.dsav - *d__, abs(d__1)) / *d__ > ceps_1.eps) {
	dfunc_(d__);
    }

    i__1 = equ_1.iex;
    for (j = 0; j <= i__1; ++j) {
	if (equ_1.imaxf[j] == equ_1.imaxf[j + 1]) {
	    goto L30;
	}
	h__ = 0.;
	i__2 = equ_1.imaxf[j + 1];
	for (i__ = equ_1.imaxf[j] + 1; i__ <= i__2; ++i__) {
	    h__ += equ_1.itpot[i__ - 1] / cfac_1.factor * cfunc_1.tf[i__ - 1] 
		    * cfunc_1.df[equ_1.idpot[i__ - 1] + 1];
/* L20: */
	}
	ret_val += h__ * cfunc_1.ex[j];
L30:
	;
    }

    ret_val *= *t / cnorm_1.tnorm;

    fnrts = ret_val;
    tsave = *t;
    dsave = *d__;

    return ret_val;
} /* fnrt_ */

/* ****************************************************************************** */
doublereal fnrdd_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal ret_val, d__1, d__2;

    /* Local variables */
    static integer i__, j;
    static doublereal exdn;
    extern /* Subroutine */ int dfunc_(doublereal *);
    static doublereal dsave, exddn;
    extern /* Subroutine */ int tfunc_(doublereal *);
    static doublereal tsave, fnrdds;

/* ****************************************************************************** */

/*    THIS FUNCTION CALCULATES THE 2ND DN */
/*    DERIVATIVE OF THE F'S NORMALIZED REAL PART. */



    if ((d__1 = *t - tsave, abs(d__1)) < ceps_1.eps && (d__2 = (*d__ - dsave) 
	    / *d__, abs(d__2)) < ceps_1.eps) {
	ret_val = fnrdds;
	return ret_val;
    }

    ret_val = 0.;

    if ((d__1 = cfunc_1.tsav - *t, abs(d__1)) > ceps_1.eps) {
	tfunc_(t);
    }
    if ((d__1 = cfunc_1.dsav - *d__, abs(d__1)) / *d__ > ceps_1.eps) {
	dfunc_(d__);
    }

    i__1 = equ_1.imaxf[1];
    for (i__ = 1; i__ <= i__1; ++i__) {
	ret_val += cfunc_1.tf[i__ - 1] * equ_1.idpot[i__ - 1] * (equ_1.idpot[
		i__ - 1] - 1) * cfunc_1.df[equ_1.idpot[i__ - 1] - 1];
/* L10: */
    }

    i__1 = equ_1.iex;
    for (j = 1; j <= i__1; ++j) {
	if (equ_1.imaxf[j] == equ_1.imaxf[j + 1]) {
	    goto L30;
	}
	exddn = cfunc_1.exd[j] * 2. / cfunc_1.df[2];
	exdn = cfunc_1.ex[j] / cfunc_1.df[3];
	i__2 = equ_1.imaxf[j + 1];
	for (i__ = equ_1.imaxf[j] + 1; i__ <= i__2; ++i__) {
	    ret_val += cfunc_1.tf[i__ - 1] * cfunc_1.df[equ_1.idpot[i__ - 1] 
		    + 1] * (cfunc_1.exdd[j] + exddn * equ_1.idpot[i__ - 1] + 
		    exdn * equ_1.idpot[i__ - 1] * (equ_1.idpot[i__ - 1] - 1));
/* L20: */
	}
L30:
	;
    }

    fnrdds = ret_val;
    tsave = *t;
    dsave = *d__;

    return ret_val;
} /* fnrdd_ */

/* ****************************************************************************** */
doublereal fnrdt_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal ret_val, d__1, d__2;

    /* Local variables */
    static integer i__, j;
    static doublereal exdn;
    extern /* Subroutine */ int dfunc_(doublereal *);
    static doublereal dsave;
    extern /* Subroutine */ int tfunc_(doublereal *);
    static doublereal tsave, fnrdts;

/* ****************************************************************************** */

/*    THIS FUNCTION CALCULATES THE 2ND DN,TN- */
/*    DERIVATIVE OF THE F'S NORMALIZED REAL PART. */


    if ((d__1 = *t - tsave, abs(d__1)) < ceps_1.eps && (d__2 = (*d__ - dsave) 
	    / *d__, abs(d__2)) < ceps_1.eps) {
	ret_val = fnrdts;
	return ret_val;
    }

    ret_val = 0.;

    if ((d__1 = cfunc_1.tsav - *t, abs(d__1)) > ceps_1.eps) {
	tfunc_(t);
    }
    if ((d__1 = cfunc_1.dsav - *d__, abs(d__1)) / *d__ > ceps_1.eps) {
	dfunc_(d__);
    }

    i__1 = equ_1.imaxf[1];
    for (i__ = 1; i__ <= i__1; ++i__) {
	ret_val += equ_1.itpot[i__ - 1] / cfac_1.factor * cfunc_1.tf[i__ - 1] 
		* equ_1.idpot[i__ - 1] * cfunc_1.df[equ_1.idpot[i__ - 1]];
/* L10: */
    }

    i__1 = equ_1.iex;
    for (j = 1; j <= i__1; ++j) {
	if (equ_1.imaxf[j] == equ_1.imaxf[j + 1]) {
	    goto L30;
	}
	exdn = cfunc_1.ex[j] * cfunc_1.df[0];
	i__2 = equ_1.imaxf[j + 1];
	for (i__ = equ_1.imaxf[j] + 1; i__ <= i__2; ++i__) {
	    ret_val += equ_1.itpot[i__ - 1] / cfac_1.factor * cfunc_1.tf[i__ 
		    - 1] * (cfunc_1.exd[j] + exdn * equ_1.idpot[i__ - 1]) * 
		    cfunc_1.df[equ_1.idpot[i__ - 1] + 1];
/* L20: */
	}
L30:
	;
    }

    ret_val *= *t / cnorm_1.tnorm;

    fnrdts = ret_val;
    tsave = *t;
    dsave = *d__;

    return ret_val;
} /* fnrdt_ */

/* **************************************************************************** */
doublereal fnrtt_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal ret_val, d__1, d__2;

    /* Local variables */
    static doublereal h__;
    static integer i__, j;
    extern /* Subroutine */ int dfunc_(doublereal *);
    static doublereal dsave;
    extern /* Subroutine */ int tfunc_(doublereal *);
    static doublereal tsave, fnrtts;

/* ***************************************************************************** */

/*    THIS FUNCTION CALCULATES THE 2ND TN- */
/*    DERIVATIVE OF THE F'S NORMALIZED REAL PART. */


    if ((d__1 = *t - tsave, abs(d__1)) < ceps_1.eps && (d__2 = (*d__ - dsave) 
	    / *d__, abs(d__2)) < ceps_1.eps) {
	ret_val = fnrtts;
	return ret_val;
    }

    ret_val = 0.;

    if ((d__1 = cfunc_1.tsav - *t, abs(d__1)) > ceps_1.eps) {
	tfunc_(t);
    }
    if ((d__1 = cfunc_1.dsav - *d__, abs(d__1)) / *d__ > ceps_1.eps) {
	dfunc_(d__);
    }

    i__1 = equ_1.iex;
    for (j = 0; j <= i__1; ++j) {
	if (equ_1.imaxf[j] == equ_1.imaxf[j + 1]) {
	    goto L30;
	}
	h__ = 0.;
	i__2 = equ_1.imaxf[j + 1];
	for (i__ = equ_1.imaxf[j] + 1; i__ <= i__2; ++i__) {
	    h__ += equ_1.itpot[i__ - 1] / cfac_1.factor * (equ_1.itpot[i__ - 
		    1] / cfac_1.factor - 1) * cfunc_1.tf[i__ - 1] * 
		    cfunc_1.df[equ_1.idpot[i__ - 1] + 1];
/* L20: */
	}
	ret_val += h__ * cfunc_1.ex[j];
L30:
	;
    }

/* Computing 2nd power */
    d__1 = *t / cnorm_1.tnorm;
    ret_val *= d__1 * d__1;

    fnrtts = ret_val;
    tsave = *t;
    dsave = *d__;

    return ret_val;
} /* fnrtt_ */

/* **************************************************************************** */
/* Subroutine */ int sbstce_(void)
{
    return 0;
} /* sbstce_ */

/* ***************************************************************************** */


/*   THIS SUBROUTINE SETS SUBSTANCE PARAMETERS FOR H2O */






/* ********************************************************************************** */
doublereal db_(doublereal *t, doublereal *p)
{
    /* Format strings */
    static char fmt_1001[] = "(\002<DB> T=\002,f8.3,\002or P=\002,d10.4,\002"
	    "out of range of validity\002)";
    static char fmt_1002[] = "(\002<DB> T= \002,f8.3,\002 and P= \002,d10.4"
	    ",\002 in solid phase\002)";

    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal dv, ps, eps;
    extern doublereal dens_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal dest;
    extern /* Subroutine */ int vpeq_(doublereal *, doublereal *), satt_(
	    doublereal *, doublereal *, doublereal *, doublereal *);
    extern doublereal bdens_(doublereal *, doublereal *, integer *), pmelt_(
	    doublereal *, integer *);
    static doublereal pmelt1, pmelt2;

    /* Fortran I/O blocks */
    static cilist io___52 = { 0, 0, 0, fmt_1001, 0 };
    static cilist io___53 = { 0, 0, 0, fmt_1002, 0 };
    static cilist io___57 = { 0, 0, 0, fmt_1002, 0 };


/* ********************************************************************************** */

/*  THIS FUNCTION CALCULATES THE DENSITY FOR GIVEN P,T */


    ret_val = 0.;
    if (*t <= 230. || *p <= 0.) {
	io___52.ciunit = cout_1.nout;
	s_wsfe(&io___52);
	do_fio(&c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*p), (ftnlen)sizeof(doublereal));
	e_wsfe();
	return ret_val;
    }

    if (pmelt_(t, &c__2) < *p) {
	io___53.ciunit = cout_1.nout;
	s_wsfe(&io___53);
	do_fio(&c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*p), (ftnlen)sizeof(doublereal));
	e_wsfe();
	return ret_val;
    }

    if (*t < csub3_1.ttr) {
	pmelt1 = pmelt_(t, &c__1);
	pmelt2 = pmelt_(t, &c__2);
	if (pmelt1 <= *p && *p <= pmelt2) {
	    dest = csub3_1.dltr;
	    goto L100;
	} else {
	    io___57.ciunit = cout_1.nout;
	    s_wsfe(&io___57);
	    do_fio(&c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*p), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    return ret_val;
	}
    }

    if (*t < csub2_2.tc) {
	vpeq_(t, &ps);

	if ((d__1 = *p - ps, abs(d__1)) / ps < 2.5e-4) {
	    satt_(t, &dv, &dest, &ps);
	    if (*p < ps) {
		dest = dv;
	    }
	} else {

	    if (*p < ps) {
		dest = bdens_(t, p, &c__2);
	    }
	    if (*p > ps) {
		dest = bdens_(t, p, &c__1);
	    }
	}

    } else {
	dest = bdens_(t, p, &c__2);
    }

/*  EXACT CALCULATION OF DENSITY */

L100:
    eps = ceps_2.epse * 100.;
    if (*t > 374.) {
	eps = ceps_2.epse * 1e4;
    }

    ret_val = dens_(p, t, &dest, &eps);

    return ret_val;
} /* db_ */

/* *********************************************************************** */
doublereal pb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static doublereal dn;
    extern doublereal fnrd_(doublereal *, doublereal *);

/* *********************************************************************** */

/*     PRESSURE */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    dn = *d__ / cnorm_1.dnorm;

    ret_val = *d__ * csub2_2.r__ * *t * (dn * fnrd_(t, d__) + 1.);

    return ret_val;
} /* pb_ */

/* *********************************************************************** */
doublereal dpdtb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static doublereal dn, tn;
    extern doublereal fnrd_(doublereal *, doublereal *), fnrdt_(doublereal *, 
	    doublereal *);

/* *********************************************************************** */

/*      DP/DT */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    tn = cnorm_1.tnorm / *t;
    dn = *d__ / cnorm_1.dnorm;

    ret_val = *d__ * csub2_2.r__ * (dn * fnrd_(t, d__) + 1. - dn * tn * 
	    fnrdt_(t, d__));

    return ret_val;
} /* dpdtb_ */

/* *********************************************************************** */
doublereal dpddb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Local variables */
    static doublereal dn;
    extern doublereal fnrd_(doublereal *, doublereal *), fnrdd_(doublereal *, 
	    doublereal *);

/* *********************************************************************** */

/*     DP/DD */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    dn = *d__ / cnorm_1.dnorm;

/* Computing 2nd power */
    d__1 = dn;
    ret_val = csub2_2.r__ * *t * (dn * 2. * fnrd_(t, d__) + 1. + d__1 * d__1 *
	     fnrdd_(t, d__));

    return ret_val;
} /* dpddb_ */

/* *********************************************************************** */
doublereal cvb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Local variables */
    static doublereal tn;
    extern doublereal fnitt_(doublereal *, doublereal *), fnrtt_(doublereal *,
	     doublereal *);

/* *********************************************************************** */

/*     ISOCHORIC HEAT CAPACITY */


    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    tn = cnorm_1.tnorm / *t;

/* Computing 2nd power */
    d__1 = tn;
    ret_val = -csub4_1.fc * csub2_2.r__ * (d__1 * d__1) * (fnitt_(t, d__) + 
	    fnrtt_(t, d__));

    return ret_val;
} /* cvb_ */

/* *********************************************************************** */
doublereal cpb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val, d__1, d__2;

    /* Local variables */
    static doublereal dn, tn;
    extern doublereal cvb_(doublereal *, doublereal *), fnrd_(doublereal *, 
	    doublereal *), fnrdd_(doublereal *, doublereal *), fnrdt_(
	    doublereal *, doublereal *);

/* *********************************************************************** */

/*     ISOBARIC HEAT CAPACITY */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    tn = cnorm_1.tnorm / *t;
    dn = *d__ / cnorm_1.dnorm;

/* Computing 2nd power */
    d__1 = dn * fnrd_(t, d__) + 1. - dn * tn * fnrdt_(t, d__);
/* Computing 2nd power */
    d__2 = dn;
    ret_val = cvb_(t, d__) + csub4_1.fc * csub2_2.r__ * (d__1 * d__1) / (dn * 
	    2. * fnrd_(t, d__) + 1. + d__2 * d__2 * fnrdd_(t, d__));

    return ret_val;
} /* cpb_ */

/* *********************************************************************** */
doublereal wb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static doublereal dn, tn, wb2;
    extern doublereal cpb_(doublereal *, doublereal *), cvb_(doublereal *, 
	    doublereal *), fnrd_(doublereal *, doublereal *), fnrdd_(
	    doublereal *, doublereal *);

/* *********************************************************************** */

/*     VELOCITY OF SOUND */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    tn = cnorm_1.tnorm / *t;
    dn = *d__ / cnorm_1.dnorm;

/* Computing 2nd power */
    d__1 = dn;
    wb2 = cpb_(t, d__) / cvb_(t, d__) * (dn * 2. * fnrd_(t, d__) + 1. + d__1 *
	     d__1 * fnrdd_(t, d__));

    if (wb2 > 0.) {
	ret_val = sqrt(wb2 * csub2_2.r__ * csub4_1.fw * *t);
    } else {
	ret_val = 0.;
    }

    return ret_val;
} /* wb_ */

/* *********************************************************************** */
doublereal fb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal fni_(doublereal *, doublereal *), fnr_(doublereal *, 
	    doublereal *);

/* *********************************************************************** */

/*     HELMHOLTZ FUNCTION */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    ret_val = csub2_2.r__ * csub4_1.fc * *t * (fnr_(t, d__) + fni_(t, d__));

    return ret_val;
} /* fb_ */

/* *********************************************************************** */
doublereal hb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static doublereal dn, tn;
    extern doublereal fnrd_(doublereal *, doublereal *), fnit_(doublereal *, 
	    doublereal *), fnrt_(doublereal *, doublereal *);

/* *********************************************************************** */

/*     ENTHALPY */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    tn = cnorm_1.tnorm / *t;
    dn = *d__ / cnorm_1.dnorm;

    ret_val = csub2_2.r__ * csub4_1.fc * *t * (dn * fnrd_(t, d__) + 1. + tn * 
	    (fnit_(t, d__) + fnrt_(t, d__)));

    return ret_val;
} /* hb_ */

/* *********************************************************************** */
doublereal sb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static doublereal tn;
    extern doublereal fni_(doublereal *, doublereal *), fnr_(doublereal *, 
	    doublereal *), fnit_(doublereal *, doublereal *), fnrt_(
	    doublereal *, doublereal *);

/* *********************************************************************** */

/*     ENTROPY */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    tn = cnorm_1.tnorm / *t;

    ret_val = csub2_2.r__ * csub4_1.fc * (tn * (fnit_(t, d__) + fnrt_(t, d__))
	     - (fni_(t, d__) + fnr_(t, d__)));

    return ret_val;
} /* sb_ */

/* *********************************************************************** */
doublereal ub_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static doublereal tn;
    extern doublereal fnit_(doublereal *, doublereal *), fnrt_(doublereal *, 
	    doublereal *);

/* *********************************************************************** */

/*     INTERNAL ENERGY */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    tn = cnorm_1.tnorm / *t;

    ret_val = csub2_2.r__ * csub4_1.fc * *t * tn * (fnit_(t, d__) + fnrt_(t, 
	    d__));

    return ret_val;
} /* ub_ */

/* *********************************************************************** */
doublereal gb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static doublereal dn, tn;
    extern doublereal fni_(doublereal *, doublereal *), fnr_(doublereal *, 
	    doublereal *), fnrd_(doublereal *, doublereal *);

/* *********************************************************************** */

/*     GIBBS ENERGY */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    tn = cnorm_1.tnorm / *t;
    dn = *d__ / cnorm_1.dnorm;

    ret_val = csub2_2.r__ * csub4_1.fc * *t * (dn * fnrd_(t, d__) + 1. + fni_(
	    t, d__) + fnr_(t, d__));

    return ret_val;
} /* gb_ */

/* *********************************************************************** */
doublereal alphab_(doublereal *t1, doublereal *dl1, doublereal *dv1, 
	doublereal *t2, doublereal *dl2, doublereal *dv2)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern doublereal hb_(doublereal *, doublereal *);
    static doublereal beta1, beta2;
    extern doublereal dpsdtb_(doublereal *, doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___77 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*     ALPHA BETWEEN T1 AND T2 */
/*     (CF. OSBORNE ET AL., 1930) */


    ret_val = 0.;
    if (*t1 < 1.) {
	return ret_val;
    }
    if (*dl1 < 1e-10) {
	return ret_val;
    }
    if (*dv1 < 1e-10) {
	return ret_val;
    }
    if (*t2 < 1.) {
	return ret_val;
    }
    if (*dl2 < 1e-10) {
	return ret_val;
    }
    if (*dv2 < 1e-10) {
	return ret_val;
    }

    if (*t1 > csub2_1.tc || *t1 > csub2_1.tc) {
	io___77.ciunit = cout_1.nout;
	s_wsle(&io___77);
	do_lio(&c__9, &c__1, "<ALPHAB> T1 or T2 greater than TC . Alpha not "
		"cal", (ftnlen)49);
	do_lio(&c__9, &c__1, "culated !", (ftnlen)9);
	e_wsle();
	return ret_val;
    }

    beta1 = csub4_1.fc * *t1 / *dl1 * dpsdtb_(t1, dl1, dv1);
    beta2 = csub4_1.fc * *t2 / *dl2 * dpsdtb_(t2, dl2, dv2);

    ret_val = hb_(t2, dl2) - beta2 - (hb_(t1, dl1) - beta1);

    return ret_val;
} /* alphab_ */

/* *********************************************************************** */
doublereal dpsdtb_(doublereal *t, doublereal *dl, doublereal *dv)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    static doublereal tn;
    extern doublereal fnr_(doublereal *, doublereal *), fnrt_(doublereal *, 
	    doublereal *);

/* *********************************************************************** */

/*     VAPOR PRESSURE CURVE DPS/DT */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*dl < 1e-10) {
	return ret_val;
    }
    if (*dv < 1e-10) {
	return ret_val;
    }

    tn = cnorm_1.tnorm / *t;

    ret_val = *dl * *dv / (*dv - *dl) * csub2_2.r__ * (log(*dv / *dl) + fnr_(
	    t, dv) - fnr_(t, dl) - tn * (fnrt_(t, dv) - fnrt_(t, dl)));

    return ret_val;
} /* dpsdtb_ */

/* *********************************************************************** */
doublereal betasb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Local variables */
    extern doublereal cpb_(doublereal *, doublereal *), dpddb_(doublereal *, 
	    doublereal *), dpdtb_(doublereal *, doublereal *);

/* *********************************************************************** */

/*     ISENTROPIC TEMPERATURE-PRESSURE */
/*     COEFFICIENT BETAS=(DT/DP)s */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

/* Computing 2nd power */
    d__1 = *d__;
    ret_val = *t / (d__1 * d__1) * dpdtb_(t, d__) / (cpb_(t, d__) * dpddb_(t, 
	    d__));

    return ret_val;
} /* betasb_ */

/* *********************************************************************** */
doublereal bb_(doublereal *t)
{
    /* Initialized data */

    static doublereal d__ = 1e-200;

    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal fnrd_(doublereal *, doublereal *);

/* *********************************************************************** */

/*     2. VIRIALCOEFFICIENT B */


    ret_val = fnrd_(t, &d__) / cnorm_1.dnorm;

    return ret_val;
} /* bb_ */

/* *********************************************************************** */
doublereal cb_(doublereal *t)
{
    /* Initialized data */

    static doublereal d__ = 1e-200;

    /* System generated locals */
    doublereal ret_val, d__1;

    /* Local variables */
    extern doublereal fnrdd_(doublereal *, doublereal *);

/* *********************************************************************** */

/*     3. VIRIALCOEFFICIENT C */


/* Computing 2nd power */
    d__1 = cnorm_1.dnorm;
    ret_val = fnrdd_(t, &d__) / (d__1 * d__1);

    return ret_val;
} /* cb_ */

/* *********************************************************************** */
doublereal rjtb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val, d__1, d__2;

    /* Local variables */
    static doublereal dn, tn, cvbn;
    extern doublereal fnrd_(doublereal *, doublereal *);
    static doublereal dpddn;
    extern doublereal fnrdd_(doublereal *, doublereal *), fnrdt_(doublereal *,
	     doublereal *), fnitt_(doublereal *, doublereal *), fnrtt_(
	    doublereal *, doublereal *);

/* *********************************************************************** */

/*     Joule Thomson Coefficient */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    tn = cnorm_1.tnorm / *t;
    dn = *d__ / cnorm_1.dnorm;

/* Computing 2nd power */
    d__1 = tn;
    cvbn = -(d__1 * d__1) * (fnitt_(t, d__) + fnrtt_(t, d__));
/* Computing 2nd power */
    d__1 = dn;
    dpddn = dn * 2. * fnrd_(t, d__) + 1. + d__1 * d__1 * fnrdd_(t, d__);

/* Computing 2nd power */
    d__1 = dn;
/* Computing 2nd power */
    d__2 = dn * fnrd_(t, d__) + 1. - dn * tn * fnrdt_(t, d__);
    ret_val = -(1 / (*d__ * csub2_2.r__)) * (dn * fnrd_(t, d__) + d__1 * d__1 
	    * fnrdd_(t, d__) + dn * tn * fnrdt_(t, d__)) / (d__2 * d__2 + 
	    cvbn * dpddn);

    return ret_val;
} /* rjtb_ */

/* *********************************************************************** */
doublereal dtb_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Local variables */
    static doublereal dn, tn;
    extern doublereal fnrd_(doublereal *, doublereal *);
    static doublereal dpddn;
    extern doublereal fnrdd_(doublereal *, doublereal *);
    static doublereal dpdtn;
    extern doublereal fnrdt_(doublereal *, doublereal *);

/* *********************************************************************** */

/*     Isothermal throttling coefficient */



    ret_val = 0.;
    if (*t < 1.) {
	return ret_val;
    }
    if (*d__ < 1e-10) {
	return ret_val;
    }

    tn = cnorm_1.tnorm / *t;
    dn = *d__ / cnorm_1.dnorm;

/* Computing 2nd power */
    d__1 = dn;
    dpddn = dn * 2. * fnrd_(t, d__) + 1. + d__1 * d__1 * fnrdd_(t, d__);
    dpdtn = dn * fnrd_(t, d__) + 1. - dn * tn * fnrdt_(t, d__);

    ret_val = 1 / *d__ * (1. - dpdtn / dpddn);

    return ret_val;
} /* dtb_ */

/* ************************************************************************ */
doublereal dens_(doublereal *p, doublereal *t, doublereal *dest, doublereal *
	epsh)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static doublereal x, d1, d2, dd;
    static integer ix;
    static doublereal eps;
    extern doublereal nullf_();
    extern /* Subroutine */ int wnull3_(doublereal *, doublereal *, D_fp, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *)
	    ;

/* ************************************************************************ */

/* CALCULATING DENSITY FOR GIVEN T,P,DEST */


    eps = *epsh;
    if (*dest > csub2_1.dc * 2. && *t < csub2_1.tc - 100.) {
	dd = *dest * .003;
    } else if (*dest > csub2_1.dc * 2.) {
	dd = *dest * .01;
    } else {
	dd = *dest * .05;
    }

    d1 = *dest;

    if (*dest > csub2_1.dc) {
	d2 = d1 + dd;
    } else {
	d2 = d1 - dd;
    }

    if (eps < 1e-8) {
	eps = 1e-8;
    }

    wnull3_(&d1, &d2, (D_fp)nullf_, p, t, &eps, &x, &ix);

    if (ix <= 0) {
	ret_val = x;
    } else {
	ret_val = 0.;
    }
/* L999: */
    return ret_val;
} /* dens_ */

/* *********************************************************************** */
doublereal nullf_(doublereal *d__, doublereal *t, doublereal *p)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    extern doublereal pb_(doublereal *, doublereal *);

/* *********************************************************************** */


    ret_val = pb_(t, d__) - *p;
/* L999: */
    return ret_val;
} /* nullf_ */

/* ****************************************************************** */
/* Subroutine */ int satt_(doublereal *t, doublereal *dv, doublereal *dl, 
	doublereal *p)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double log(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__;
    static doublereal p0;
    extern doublereal fnr_(doublereal *, doublereal *);
    static doublereal eps;
    extern /* Subroutine */ int dleq_(doublereal *, doublereal *);
    extern doublereal dens_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal epsd;
    extern /* Subroutine */ int dveq_(doublereal *, doublereal *);
    static doublereal fnrl, psav;
    extern /* Subroutine */ int vpeq_(doublereal *, doublereal *);
    static doublereal tsav, fnrv, dlsav, dvsav;

    /* Fortran I/O blocks */
    static cilist io___107 = { 0, 0, 0, 0, 0 };
    static cilist io___108 = { 0, 0, 0, 0, 0 };
    static cilist io___109 = { 0, 0, 0, 0, 0 };


/* ****************************************************************** */

/*     CALCULATING DV,DL,P FOR A GIVEN T */


    if (*t > csub2_2.tc) {
	goto L500;
    }
    if (*t < csub3_2.ttr) {
	goto L500;
    }

    eps = ceps_2.epse * 100.;
    if (*t > 374.) {
	eps = ceps_2.epse * 1e4;
    }
    epsd = eps * .33;

    if ((d__1 = csub2_2.tc - *t, abs(d__1)) < ceps_2.epse) {
	*dl = csub2_2.dc;
	*dv = csub2_2.dc;
	*p = csub2_2.pc;
	return 0;
    }

    if ((d__1 = tsav - *t, abs(d__1)) < ceps_2.epse) {
	*dl = dlsav;
	*dv = dvsav;
	*p = psav;
	return 0;
    }

/*     INITIAL VALUES */

    dveq_(t, dv);
    if (*dv < 1e-20) {
	goto L500;
    }
    dleq_(t, dl);
    vpeq_(t, p);

/*  *** MAXWELL-LOOP *** */

    for (i__ = 1; i__ <= 10; ++i__) {

	*dl = dens_(p, t, dl, &epsd);
	if (*dl < 1e-20) {
	    goto L500;
	}
	fnrl = fnr_(t, dl);

	*dv = dens_(p, t, dv, &epsd);
	if (*dv < 1e-20) {
	    goto L500;
	}
	fnrv = fnr_(t, dv);

	if ((d__1 = (*dl - *dv) / *dv, abs(d__1)) <= epsd) {
	    goto L500;
	}

	if (*t > 647.139) {
	    goto L999;
	}
	p0 = *p;
	*p = (fnrl - fnrv + log(*dl / *dv)) * csub2_2.r__ * *t / (1. / *dv - 
		1. / *dl);

	if ((d__1 = (*p - p0) / *p, abs(d__1)) < eps) {
	    goto L999;
	}

/* L31: */
    }

    io___107.ciunit = cout_1.nout;
    s_wsle(&io___107);
    do_lio(&c__9, &c__1, "<SATT> Did not converge at T=", (ftnlen)29);
    do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
    do_lio(&c__9, &c__1, "K", (ftnlen)1);
    e_wsle();

L500:
    *dl = 0.;
    *dv = 0.;
    *p = 0.;
    if (*t < csub3_2.ttr) {
	io___108.ciunit = cout_1.nout;
	s_wsle(&io___108);
	do_lio(&c__9, &c__1, "<SATT> T=", (ftnlen)9);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, "K is below the triple-point", (ftnlen)27);
	e_wsle();
    }
    if (*t > csub2_2.tc) {
	io___109.ciunit = cout_1.nout;
	s_wsle(&io___109);
	do_lio(&c__9, &c__1, "<SATT> T=", (ftnlen)9);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, "K is supercritical", (ftnlen)18);
	e_wsle();
    }
L999:

    tsav = *t;
    dlsav = *dl;
    dvsav = *dv;
    psav = *p;

    return 0;
} /* satt_ */

/* ****************************************************************** */
/* Subroutine */ int satp_(doublereal *t, doublereal *dv, doublereal *dl, 
	doublereal *p)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double log(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__;
    static doublereal t0, dp;
    extern doublereal fnr_(doublereal *, doublereal *);
    static doublereal eps;
    extern /* Subroutine */ int dleq_(doublereal *, doublereal *);
    extern doublereal dens_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal epsd, dpdt;
    extern /* Subroutine */ int dveq_(doublereal *, doublereal *);
    static doublereal fnrl, psav, fnrv;
    extern doublereal tseq_(doublereal *);
    static doublereal tsav, dlsav, dvsav;
    extern /* Subroutine */ int dpdteq_(doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___122 = { 0, 0, 0, 0, 0 };
    static cilist io___123 = { 0, 0, 0, 0, 0 };
    static cilist io___124 = { 0, 0, 0, 0, 0 };


/* ****************************************************************** */

/*     CALCULATING T,DV,DL FOR A GIVEN P */


    if (*p > csub2_2.pc) {
	goto L500;
    }
    if (*p < csub3_2.ptr) {
	goto L500;
    }

    eps = ceps_2.epse * 100.;
    if (*p > 374.) {
	eps = ceps_2.epse * 1e4;
    }
    epsd = eps * .33;

    if ((d__1 = csub2_2.pc - *p, abs(d__1)) / *p < ceps_2.epse) {
	*dl = csub2_2.dc;
	*dv = csub2_2.dc;
	*t = csub2_2.tc;
	return 0;
    }

    if ((d__1 = psav - *p, abs(d__1)) < ceps_2.epse) {
	*dl = dlsav;
	*dv = dvsav;
	*t = tsav;
	return 0;
    }

/*     INITIAL VALUES */

    *t = tseq_(p);
    if (*t < 1e-20 || *t > csub2_2.tc) {
	goto L500;
    }
    dveq_(t, dv);
    dleq_(t, dl);
    dpdteq_(t, &dpdt);

/*  *** MAXWELL-LOOP *** */

    for (i__ = 1; i__ <= 10; ++i__) {

	*dl = dens_(p, t, dl, &epsd);
	if (*dl < 1e-20) {
	    goto L500;
	}
	fnrl = fnr_(t, dl);

	*dv = dens_(p, t, dv, &epsd);
	if (*dv < 1e-20) {
	    goto L500;
	}
	fnrv = fnr_(t, dv);

	if ((d__1 = (*dl - *dv) / *dv, abs(d__1)) <= epsd) {
	    goto L500;
	}

	if (*t > 647.135) {
	    goto L999;
	}
	t0 = *t;
	dp = *p - (fnrl - fnrv + log(*dl / *dv)) * csub2_2.r__ * *t / (1. / *
		dv - 1. / *dl);
	*t = t0 + dp / dpdt;

	if ((d__1 = *t - t0, abs(d__1)) < eps) {
	    goto L999;
	}

/* L31: */
    }

    io___122.ciunit = cout_1.nout;
    s_wsle(&io___122);
    do_lio(&c__9, &c__1, "<SATP> Did not converge at p=", (ftnlen)29);
    do_lio(&c__5, &c__1, (char *)&(*p), (ftnlen)sizeof(doublereal));
    do_lio(&c__9, &c__1, "MPa", (ftnlen)3);
    e_wsle();

L500:
    *dl = 0.;
    *dv = 0.;
    *t = 0.;
    if (*p < csub3_2.ptr) {
	io___123.ciunit = cout_1.nout;
	s_wsle(&io___123);
	do_lio(&c__9, &c__1, "<SATP> p=", (ftnlen)9);
	do_lio(&c__5, &c__1, (char *)&(*p), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, "MPa is below the triple-point", (ftnlen)29);
	e_wsle();
    }
    if (*p > csub2_2.pc) {
	io___124.ciunit = cout_1.nout;
	s_wsle(&io___124);
	do_lio(&c__9, &c__1, "<SATP> p=", (ftnlen)9);
	do_lio(&c__5, &c__1, (char *)&(*p), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, "MPa is supercritical", (ftnlen)20);
	e_wsle();
    }
L999:

    tsav = *t;
    dlsav = *dl;
    dvsav = *dv;
    psav = *p;

    return 0;
} /* satp_ */

/* ******************************************************************* */
/* Subroutine */ int wnull3_(doublereal *xa, doublereal *xb, D_fp f, 
	doublereal *p, doublereal *t, doublereal *eps, doublereal *x, integer 
	*ix)
{
    /* System generated locals */
    doublereal d__1;

    /* Local variables */
    static integer i__;
    static doublereal f1, f2, f3, x1, x2, x3;

/* ******************************************************************* */

/*               F(X,T,P)=0 */

/* ************************************************************************* */


    x1 = *xa;
    f1 = (*f)(&x1, t, p);
    x3 = *xb;
    f3 = (*f)(&x3, t, p);
    *ix = 0;

    for (i__ = 1; i__ <= 40; ++i__) {

/*   REGULA FALSI */

	if (f1 != f3) {
	    *x = x1 + (x3 - x1) * f1 / (f1 - f3);
	} else {
	    goto L10;
	}

	if (*x < 0.) {
	    *x = (x1 + x3) / 2.;
	}

	if (abs(*x) < 1e-8) {
	    if ((d__1 = *x - x1, abs(d__1)) < *eps) {
		return 0;
	    }
	} else {
	    if ((d__1 = (*x - x1) / *x, abs(d__1)) < *eps) {
		return 0;
	    }
	}

	f2 = (*f)(x, t, p);

	x2 = x1 - (x1 - x3) / 2.;

	if (f2 * f1 <= f2 * f3) {
	    x3 = x1;
	    f3 = f1;
	}
	x1 = *x;
	f1 = f2;

	if ((x2 - x3) * (x2 - x1) >= 0.) {
	    goto L100;
	}
	*x = (x1 + x3) / 2.;
	f2 = (*f)(x, t, p);

	if (f2 * f1 <= f2 * f3) {
	    x3 = x1;
	    f3 = f1;
	}

	x1 = *x;
	f1 = f2;

L100:
	;
    }

L10:
    *ix = 1;
/* L999: */
    return 0;
} /* wnull3_ */

/* *********************************************************************** */
doublereal bdens_(doublereal *t, doublereal *p, integer *ireg)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double d_lg10(doublereal *);

    /* Local variables */
    static doublereal dl, dv, ps, pt;
    extern /* Subroutine */ int dleq_(doublereal *, doublereal *);
    static doublereal dmax__;
    extern /* Subroutine */ int dveq_(doublereal *, doublereal *), vpeq_(
	    doublereal *, doublereal *);
    static integer iregh;
    extern doublereal dsoave_(doublereal *, doublereal *, integer *);

/* *********************************************************************** */

/*     ESTIMATING DENSITY FOR GIVEN T AND P */

/*             IREG- PARAMETER FOR THE REGION */
/*                   1: LIQUID */
/*                   2: GASEOUS */
/*                   0: NOT KNOWN */


    iregh = *ireg;
    if (*ireg == 0 || *t > csub2_1.tc) {

	iregh = 1;
	if (*t < csub2_1.tc && *t >= csub3_2.ttr) {
	    vpeq_(t, &pt);
	    ps = pt;
	} else {
	    pt = 1e10;
	}
	if (*t < csub3_2.ttr) {
	    pt = csub3_2.ptr;
	}
	if (*p < pt) {
	    iregh = 2;
	}
    }

    if (iregh == 1) {
	if (*t < csub3_2.ttr) {
	    ret_val = csub3_2.dltr;
	    return ret_val;
	}

	if (*t < csub2_1.tc * .7f) {
	    dleq_(t, &dl);
	    ret_val = dl + (*p - ps) * .243;
	} else {
	    ret_val = dsoave_(t, p, &iregh) + 200.;
	    if (*t < csub2_1.tc) {
		dleq_(t, &dl);
		if (dl > ret_val) {
		    ret_val = dl;
		}
	    }
	}
    } else {
	ret_val = dsoave_(t, p, &iregh);
	if (ret_val > 222.0431) {
	    ret_val += 200.;
	}
	if (*t < csub2_1.tc) {
	    dveq_(t, &dv);
	    if (dv < ret_val) {
		ret_val = dv;
	    }
	}
    }

    if (*p > 1e3 || ret_val < 0.) {
	dmax__ = 1e3 / d_lg10(&c_b138) * (d_lg10(p) - 3.) + 1400.;
	if (dmax__ < ret_val || ret_val < 0.) {
	    ret_val = dmax__;
	}
    }

    return ret_val;
} /* bdens_ */

/* *********************************************************************** */
doublereal dsoave_(doublereal *t, doublereal *p, integer *ireg)
{
    /* Format strings */
    static char fmt_1000[] = "(\002<BDENS> ERROR ON P,T \002)";

    /* System generated locals */
    integer i__1;
    doublereal ret_val, d__1, d__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    double acos(doublereal), d_lg10(doublereal *), pow_dd(doublereal *, 
	    doublereal *), cos(doublereal);

    /* Local variables */
    static doublereal a, b, d__;
    static integer i__;
    static doublereal q, r__, u, v, y[3], em, pe;
    static integer kk;
    static doublereal pi, ps, atc, phi, sum1, sum2, beta, dmin__, dmax__, 
	    disk;
    extern /* Subroutine */ int vpeq_(doublereal *, doublereal *);
    static doublereal gamma, alpha, omega, delta;
    static integer iregh;
    static doublereal diskn, psoave, tsoave, prsoav;

    /* Fortran I/O blocks */
    static cilist io___138 = { 0, 1, 0, fmt_1000, 0 };


/* *********************************************************************** */

/*     ESTIMATING DENSITY WITH THE SOAVE EQUATION */


    ret_val = 0.;


    if (*p < 0. || *t < 0.) {
	s_wsfe(&io___138);
	e_wsfe();
	goto L999;
    }

    pi = acos(0.) * 2.;
/* Computing 2nd power */
    d__1 = csub2_1.rg * csub2_1.tc;
    atc = d__1 * d__1 * .42748025 / csub2_1.pc;
    b = csub2_1.rg * .08664035 * csub2_1.tc / csub2_1.pc;

    tsoave = csub2_1.tc * .7;
    vpeq_(&tsoave, &psoave);
    prsoav = psoave / csub2_1.pc;

    omega = -d_lg10(&prsoav) - 1.;

/* Computing 2nd power */
    d__1 = omega;
/* Computing 3rd power */
    d__2 = omega;
    em = omega * 1.576 + .47979 - d__1 * d__1 * .1925 + d__2 * (d__2 * d__2) *
	     .025;
    d__2 = *t / csub2_1.tc;
/* Computing 2nd power */
    d__1 = em * (1. - pow_dd(&d__2, &c_b143)) + 1.;
    alpha = d__1 * d__1;

    a = alpha * atc;

/*  Y**3 + BETA*Y**2 + GAMMA*Y + DELTA = 0 */

    beta = -(csub2_1.rg * *t) / *p;
/* Computing 2nd power */
    d__1 = b;
    gamma = -(d__1 * d__1) - b * csub2_1.rg * *t / *p + a / *p;
    delta = -(a * b) / *p;

/* Computing 3rd power */
    d__1 = beta;
    q = d__1 * (d__1 * d__1) / 27. - beta * gamma / 6. + delta / 2.;
/* Computing 2nd power */
    d__1 = beta;
    pe = (gamma - d__1 * d__1 / 3.) / 3.;
/* Computing 2nd power */
    d__1 = q;
/* Computing 3rd power */
    d__2 = pe;
    disk = d__1 * d__1 + d__2 * (d__2 * d__2);

    if (abs(pe) < 1e-20) {
	d__2 = (d__1 = q * 2., abs(d__1));
	y[0] = pow_dd(&d__2, &c_b144);
	if (q > 0.) {
	    y[0] = -y[0];
	}
	y[1] = 0.;
	y[2] = 0.;
	kk = 1;
	goto L500;
    }

    if (disk < 0.) {
	d__1 = abs(pe);
	r__ = pow_dd(&d__1, &c_b143);
	if (q < 0.) {
	    r__ = -r__;
	}
/* Computing 3rd power */
	d__1 = r__;
	phi = acos(q / (d__1 * (d__1 * d__1)));
	y[0] = -(r__ * 2.) * cos(phi / 3.);
	y[1] = r__ * 2. * cos(pi / 3. - phi / 3.);
	y[2] = r__ * 2. * cos(pi / 3. + phi / 3.);
	kk = 3;
    } else {

	diskn = pow_dd(&disk, &c_b143);
	sum1 = -q + diskn;
	if (sum1 < 0.) {
	    d__1 = abs(sum1);
	    u = -pow_dd(&d__1, &c_b144);
	} else {
	    u = pow_dd(&sum1, &c_b144);
	}
	sum2 = -q - diskn;
	if (sum2 < 0.) {
	    d__1 = abs(sum2);
	    v = -pow_dd(&d__1, &c_b144);
	} else {
	    v = pow_dd(&sum2, &c_b144);
	}
	y[0] = u + v;
	y[1] = 0.;
	y[2] = 0.;
	kk = 1;
    }
L500:

    dmax__ = 0.;
    dmin__ = 1e100;

    i__1 = kk;
    for (i__ = 1; i__ <= i__1; ++i__) {
	d__ = 1. / (y[i__ - 1] - beta / 3.);
	if (d__ > dmax__) {
	    dmax__ = d__;
	}
	if (d__ < dmin__) {
	    dmin__ = d__;
	}
/* L50: */
    }

    ret_val = dmin__;
    iregh = *ireg;

    if (*t < csub2_1.tc) {
	if (*ireg == 0) {
	    vpeq_(t, &ps);
	    iregh = 2;
	    if (*p > ps) {
		iregh = 1;
	    }
	}

	if (iregh == 1) {
	    ret_val = dmax__;
	} else {
	    ret_val = dmin__;
	}

    }

L999:
    return ret_val;
} /* dsoave_ */

/* ********************************************************************************** */
doublereal tseq_(doublereal *p)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double log(doublereal);

    /* Local variables */
    static doublereal t1, t2;
    static integer ix;
    static doublereal ts, dummy;
    extern /* Subroutine */ doublereal rnufu_(doublereal *t, doublereal *dummy, doublereal *p);
    extern /* Subroutine */ int wnull3_(doublereal *, doublereal *, D_fp, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *)
	    ;
    static doublereal xkonst;

    /* Fortran I/O blocks */
    static cilist io___170 = { 0, 0, 0, 0, 0 };
    static cilist io___171 = { 0, 0, 0, 0, 0 };
    static cilist io___178 = { 0, 0, 0, 0, 0 };


/* ********************************************************************************** */

/*     CALCULATING TS FOR A GIVEN P FROM SAT-EQUATION */


    ret_val = 0.;

    if ((d__1 = *p - csub2_1.pc, abs(d__1)) < 1e-6) {
	ret_val = csub2_1.tc;
	return ret_val;
    }

    if (*p > csub2_1.pc) {
	io___170.ciunit = cout_1.nout;
	s_wsle(&io___170);
	do_lio(&c__9, &c__1, "<TSEQ> P IS GREATER THAN PC", (ftnlen)27);
	e_wsle();
	return ret_val;
    }

    if (*p < csub3_3.ptr) {
	io___171.ciunit = cout_1.nout;
	s_wsle(&io___171);
	do_lio(&c__9, &c__1, "<TSEQ> P IS LESS THAN PTR", (ftnlen)25);
	e_wsle();
	return ret_val;
    }

    xkonst = log(csub2_1.pc / csub3_3.ptr) / (1. / csub3_3.ttr - 1. / 
	    csub2_1.tc);
    t1 = 1 / (1. / csub2_1.tc - 1. / xkonst * log(*p / csub2_1.pc));
    t2 = t1 - 2.;

    wnull3_(&t1, &t2, (D_fp)rnufu_, p, &dummy, &ceps_1.eps, &ts, &ix);

    if (ix <= 0) {
	ret_val = ts;
    } else {
	io___178.ciunit = cout_1.nout;
	s_wsle(&io___178);
	do_lio(&c__9, &c__1, "<TSEQ> did not converge at P =", (ftnlen)30);
	do_lio(&c__5, &c__1, (char *)&(*p), (ftnlen)sizeof(doublereal));
	e_wsle();
    }

    return ret_val;
} /* tseq_ */

/* *********************************************************************** */
doublereal rnufu_(doublereal *t, doublereal *dummy, doublereal *p)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static doublereal ps;
    extern /* Subroutine */ int vpeql_(doublereal *, doublereal *);

/* *********************************************************************** */
    vpeql_(t, &ps);
    ret_val = ps - *p;
    return ret_val;
} /* rnufu_ */

/* *********************************************************************** */
/* Subroutine */ int vpeql_(doublereal *t, doublereal *p)
{
    /* Initialized data */

    static doublereal dpdt = 0.;

    extern /* Subroutine */ int vpeq_(doublereal *, doublereal *), dpdteq_(
	    doublereal *, doublereal *);

/* *********************************************************************** */


    if (*t > csub2_2.tc) {
	if (dpdt < 1e-10) {
	    dpdteq_(&csub2_2.tc, &dpdt);
	}
	*p = csub2_2.pc + dpdt * (*t - csub2_2.tc);
    } else {
	vpeq_(t, p);
    }

    return 0;
} /* vpeql_ */

/* *********************************************************************** */
/* Subroutine */ int sleq_(doublereal *t, doublereal *sl)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static doublereal dl, phi;
    extern /* Subroutine */ int dleq_(doublereal *, doublereal *);
    static doublereal dpdt;
    extern /* Subroutine */ int phieq_(doublereal *, doublereal *), dpdteq_(
	    doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___181 = { 0, 0, 0, 0, 0 };
    static cilist io___182 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*  CALCULATION OF SATURATED LIQUID ENTROPY WITH HELP OF PHI */

    if (*t > csub2_1.tc) {
	io___181.ciunit = cout_1.nout;
	s_wsle(&io___181);
	do_lio(&c__9, &c__1, "<SLEQ> T > TC. S.L.Entropy will not be calcula"
		"ted !", (ftnlen)51);
	e_wsle();
	return 0;
    }

    if (*t < csub3_1.ttr) {
	io___182.ciunit = cout_1.nout;
	s_wsle(&io___182);
	do_lio(&c__9, &c__1, "<SLEQ> T <TTR. S.L.Entropy will not be calcula"
		"ted !", (ftnlen)51);
	e_wsle();
	return 0;
    }

    dleq_(t, &dl);

    if (dl > 0.) {
	dpdteq_(t, &dpdt);
	phieq_(t, &phi);
	*sl = phi + csub4_1.fc / dl * dpdt;
    } else {
	*sl = 0.;
    }

    return 0;
} /* sleq_ */

/* *********************************************************************** */
/* Subroutine */ int sveq_(doublereal *t, doublereal *sv)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static doublereal dv, phi, dpdt;
    extern /* Subroutine */ int dveq_(doublereal *, doublereal *), phieq_(
	    doublereal *, doublereal *), dpdteq_(doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___186 = { 0, 0, 0, 0, 0 };
    static cilist io___187 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*  CALCULATION OF SATURATED VAPOR ENTROPY WITH HELP OF PHI */

    if (*t > csub2_1.tc) {
	io___186.ciunit = cout_1.nout;
	s_wsle(&io___186);
	do_lio(&c__9, &c__1, "<SVEQ> T > TC. S.V.Entropy", (ftnlen)26);
	do_lio(&c__9, &c__1, " will not be calculated !", (ftnlen)25);
	e_wsle();
	return 0;
    }

    if (*t < csub3_1.ttr) {
	io___187.ciunit = cout_1.nout;
	s_wsle(&io___187);
	do_lio(&c__9, &c__1, "<SVEQ> T <TTR. S.V.Entropy", (ftnlen)26);
	do_lio(&c__9, &c__1, " will not be calculated !", (ftnlen)25);
	e_wsle();
	return 0;
    }

    dveq_(t, &dv);

    if (dv > 0.) {
	phieq_(t, &phi);
	dpdteq_(t, &dpdt);
	*sv = phi + csub4_1.fc / dv * dpdt;
    } else {
	*sv = 0.;
    }

    return 0;
} /* sveq_ */

/* *********************************************************************** */
/* Subroutine */ int hleq_(doublereal *t, doublereal *hl)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static doublereal dl, alp;
    extern /* Subroutine */ int dleq_(doublereal *, doublereal *);
    static doublereal dpdt;
    extern /* Subroutine */ int alpeq_(doublereal *, doublereal *), dpdteq_(
	    doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___191 = { 0, 0, 0, 0, 0 };
    static cilist io___192 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*  CALCULATION OF SATURATED LIQUID ENTHALPY WITH HELP OF ALP */

    if (*t > csub2_1.tc) {
	io___191.ciunit = cout_1.nout;
	s_wsle(&io___191);
	do_lio(&c__9, &c__1, "<HLEQ> T > TC. S.L.Enthalpy", (ftnlen)27);
	do_lio(&c__9, &c__1, " will not be calculated !", (ftnlen)25);
	e_wsle();
	return 0;
    }

    if (*t < csub3_1.ttr) {
	io___192.ciunit = cout_1.nout;
	s_wsle(&io___192);
	do_lio(&c__9, &c__1, "<HLEQ> T <TTR. S.L.Enthalpy", (ftnlen)27);
	do_lio(&c__9, &c__1, " will not be calculated !", (ftnlen)25);
	e_wsle();
	return 0;
    }

    dleq_(t, &dl);

    if (dl > 0.) {
	alpeq_(t, &alp);
	dpdteq_(t, &dpdt);
	*hl = alp + csub4_1.fc * *t / dl * dpdt;
    } else {
	*hl = 0.;
    }

    return 0;
} /* hleq_ */

/* *********************************************************************** */
/* Subroutine */ int hveq_(doublereal *t, doublereal *hv)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static doublereal dv, alp, dpdt;
    extern /* Subroutine */ int dveq_(doublereal *, doublereal *), alpeq_(
	    doublereal *, doublereal *), dpdteq_(doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___196 = { 0, 0, 0, 0, 0 };
    static cilist io___197 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*  CALCULATION OF SATURATED VAPOR ENTHALPY WITH HELP OF ALPHA */

    if (*t > csub2_1.tc) {
	io___196.ciunit = cout_1.nout;
	s_wsle(&io___196);
	do_lio(&c__9, &c__1, "<HVEQ> T > TC. S.V.Enthalpy", (ftnlen)27);
	do_lio(&c__9, &c__1, " will not be calculated !", (ftnlen)25);
	e_wsle();
	return 0;
    }

    if (*t < csub3_1.ttr) {
	io___197.ciunit = cout_1.nout;
	s_wsle(&io___197);
	do_lio(&c__9, &c__1, "<HVEQ> T <TTR. S.V.Enthalpy", (ftnlen)27);
	do_lio(&c__9, &c__1, " will not be calculated !", (ftnlen)25);
	e_wsle();
	return 0;
    }

    dveq_(t, &dv);

    if (dv > 0.) {
	alpeq_(t, &alp);
	dpdteq_(t, &dpdt);
	*hv = alp + csub4_1.fc * *t / dv * dpdt;
    } else {
	*hv = 0.;
    }

    return 0;
} /* hveq_ */

/* *********************************************************************** */
/* Subroutine */ int vpeq_(doublereal *t, doublereal *p)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double pow_dd(doublereal *, doublereal *), exp(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal tau;

    /* Fortran I/O blocks */
    static cilist io___202 = { 0, 0, 0, 0, 0 };
    static cilist io___203 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*     VAPOUR PRESSURE */


    tau = 1. - *t / cvpeq_1.tc;
    *p = 0.;

    if (*t < csub3_1.ttr) {
	io___202.ciunit = cout_1.nout;
	s_wsle(&io___202);
	do_lio(&c__9, &c__1, "<VPEQ> T= ", (ftnlen)10);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, "<TTR .Vapour pressure will not be", (ftnlen)33);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }

    if (tau < 0.) {
	io___203.ciunit = cout_1.nout;
	s_wsle(&io___203);
	do_lio(&c__9, &c__1, "<VPEQ> T= ", (ftnlen)10);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, ">TC. Vapour pressure will not be", (ftnlen)32);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }

    if (tau < 1e-8) {
	*p = cvpeq_1.pc;
	return 0;
    }

    i__1 = cvpeq_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L10: */
	*p += cvpeq_1.g[i__ - 1] * pow_dd(&tau, &cvpeq_1.tpot[i__ - 1]);
    }

    *p = cvpeq_1.pc * exp(*p * cvpeq_1.tc / *t);

    return 0;
} /* vpeq_ */

/* *********************************************************************** */
/* Subroutine */ int blvpeq_(void)
{
    return 0;
} /* blvpeq_ */

/* *********************************************************************** */

/*     VAPOUR PRESSURE */




/* *********************************************************************** */
/* Subroutine */ int dleq_(doublereal *t, doublereal *dl)
{
    /* Initialized data */

    static doublereal tc = 647.14;
    static doublereal dc = 322.;
    static integer n = 6;
    static doublereal tpot[6] = { .33333333333333,.66666666666667,
	    1.6666666666667,5.3333333333333,14.333333333333,36.666666666667 };
    static doublereal g[6] = { 1.99206,1.10123,-.512506,-1.75263,-45.4485,
	    -675615. };

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__;
    static doublereal tau;

    /* Fortran I/O blocks */
    static cilist io___211 = { 0, 0, 0, 0, 0 };
    static cilist io___212 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*     SATURATED LIQUID DENSITY */


/*     SATURATED LIQUID DENSITY */


    tau = 1. - *t / tc;
    *dl = 0.;

    if (*t < csub3_1.ttr) {
	io___211.ciunit = cout_1.nout;
	s_wsle(&io___211);
	do_lio(&c__9, &c__1, "<DLEQ> T= ", (ftnlen)10);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, "<TTR. Density will not be", (ftnlen)25);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }

    if (tau < 0.) {
	io___212.ciunit = cout_1.nout;
	s_wsle(&io___212);
	do_lio(&c__9, &c__1, "<DLEQ> T= ", (ftnlen)10);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, ">TC. Density will not be", (ftnlen)24);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }

    if (tau < 1e-8) {
	*dl = dc;
	return 0;
    }

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L10: */
	*dl += g[i__ - 1] * pow_dd(&tau, &tpot[i__ - 1]);
    }

    *dl = (*dl + 1.) * dc;

    return 0;
} /* dleq_ */

/* *********************************************************************** */
/* Subroutine */ int dveq_(doublereal *t, doublereal *dv)
{
    /* Initialized data */

    static doublereal tc = 647.14;
    static doublereal dc = 322.;
    static integer n = 6;
    static doublereal tpot[6] = { .33333333333333,.66666666666667,
	    1.3333333333333,3.,6.1666666666667,11.833333333333 };
    static doublereal g[6] = { -2.02957,-2.68781,-5.38107,-17.3151,-44.6384,
	    -64.3486 };

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double pow_dd(doublereal *, doublereal *), exp(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal tau;

    /* Fortran I/O blocks */
    static cilist io___220 = { 0, 0, 0, 0, 0 };
    static cilist io___221 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*     SATURATED VAPOUR DENSITY */


    tau = 1. - *t / tc;
    *dv = 0.;

    if (*t < csub3_1.ttr) {
	io___220.ciunit = cout_1.nout;
	s_wsle(&io___220);
	do_lio(&c__9, &c__1, "<DVEQ> T= ", (ftnlen)10);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, "<TTR. Density will not be", (ftnlen)25);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }

    if (tau < 0.) {
	io___221.ciunit = cout_1.nout;
	s_wsle(&io___221);
	do_lio(&c__9, &c__1, "<DVEQ> T= ", (ftnlen)10);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, ">TC. Density will not be", (ftnlen)24);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }

    if (tau < 1e-8) {
	*dv = dc;
	return 0;
    }

    i__1 = n;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* L10: */
	*dv += g[i__ - 1] * pow_dd(&tau, &tpot[i__ - 1]);
    }

    *dv = dc * exp(*dv);

    return 0;
} /* dveq_ */

/* *********************************************************************** */
/* Subroutine */ int dpdteq_(doublereal *t, doublereal *dpdt)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double pow_dd(doublereal *, doublereal *), exp(doublereal), log(
	    doublereal);

    /* Local variables */
    static integer i__;
    static doublereal p, tau;

    /* Fortran I/O blocks */
    static cilist io___225 = { 0, 0, 0, 0, 0 };
    static cilist io___226 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*  FIRST DERIVATIVE OF VAPORPRESSURE P WITH RESP. TO TEMPERATURE T */

    tau = 1. - *t / cvpeq_1.tc;
    *dpdt = 0.;
    p = 0.;

    if (*t < csub3_1.ttr) {
	io___225.ciunit = cout_1.nout;
	s_wsle(&io___225);
	do_lio(&c__9, &c__1, "<DPDTEQ> T= ", (ftnlen)12);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, "<TTR. Derivative will not be", (ftnlen)28);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }

    if (tau < 0.) {
	io___226.ciunit = cout_1.nout;
	s_wsle(&io___226);
	do_lio(&c__9, &c__1, "<DPDTEQ> T= ", (ftnlen)12);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, ">TC. Derivative will not be", (ftnlen)27);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }

    if (tau <= 1e-8) {
	if ((d__1 = cvpeq_1.tpot[0] - 1., abs(d__1)) < 1e-8) {
	    *dpdt = -cvpeq_1.pc / cvpeq_1.tc * cvpeq_1.g[0];
	}
	return 0;
    }

    i__1 = cvpeq_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	d__1 = cvpeq_1.tpot[i__ - 1] - 1.;
	*dpdt += cvpeq_1.g[i__ - 1] * cvpeq_1.tpot[i__ - 1] * pow_dd(&tau, &
		d__1);
	p += cvpeq_1.g[i__ - 1] * pow_dd(&tau, &cvpeq_1.tpot[i__ - 1]);
/* L10: */
    }

    p = cvpeq_1.pc * exp(p * cvpeq_1.tc / *t);
    *dpdt = (*dpdt + log(p / cvpeq_1.pc)) * (-p / *t);

    return 0;
} /* dpdteq_ */

/* *********************************************************************** */
/* Subroutine */ int alpeq_(doublereal *t, doublereal *alp)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__;
    static doublereal teta;

    /* Fortran I/O blocks */
    static cilist io___229 = { 0, 0, 0, 0, 0 };
    static cilist io___230 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*  ALPHA VALUE USED TO CALCULATE SATURATED LIQUID ENTHALPY AND */
/*  SATURATED VAPOR ENTHALPY */

    teta = *t / calpeq_1.tc;
    *alp = 0.;

    if (*t < csub3_1.ttr) {
	io___229.ciunit = cout_1.nout;
	s_wsle(&io___229);
	do_lio(&c__9, &c__1, "<ALPHA> T= ", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, "<TTR. Alpha will not be", (ftnlen)23);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }

    if (teta > 1.) {
	io___230.ciunit = cout_1.nout;
	s_wsle(&io___230);
	do_lio(&c__9, &c__1, "<ALPHA> T= ", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, ">TC. Alpha will not be", (ftnlen)22);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }


    *alp = calpeq_1.da0;

    i__1 = calpeq_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	*alp += calpeq_1.g[i__ - 1] * pow_dd(&teta, &calpeq_1.tpot[i__ - 1]);
/* L10: */
    }

    *alp *= calpeq_1.a0;

    return 0;
} /* alpeq_ */

/* *********************************************************************** */
/* Subroutine */ int balpeq_(void)
{
    return 0;
} /* balpeq_ */

/* *********************************************************************** */

/*  ALPHA VALUE USED TO CALCULATE SATURATED LIQUID ENTHALPY AND */
/*  SATURATED VAPOR ENTHALPY */




/* *********************************************************************** */
/* Subroutine */ int phieq_(doublereal *t, doublereal *phi)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double log(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__;
    static doublereal tpt, phi0, teta;

    /* Fortran I/O blocks */
    static cilist io___234 = { 0, 0, 0, 0, 0 };
    static cilist io___235 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*  PHI VALUE USED TO CALCULATE SATURATED LIQUID ENTROPY AND */
/*  SATURATED VAPOR ENTROPY */

/*  REFERENCE VALUE: */

    phi0 = calpeq_1.a0 / calpeq_1.tc;

    teta = *t / calpeq_1.tc;
    *phi = 0.;

    if (*t < csub3_1.ttr) {
	io___234.ciunit = cout_1.nout;
	s_wsle(&io___234);
	do_lio(&c__9, &c__1, "<PHI> T= ", (ftnlen)9);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, "<TTR. Phi will not be", (ftnlen)21);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }

    if (teta > 1.) {
	io___235.ciunit = cout_1.nout;
	s_wsle(&io___235);
	do_lio(&c__9, &c__1, "<PHI> T= ", (ftnlen)9);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, ">TC. Phi will not be", (ftnlen)20);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }

    i__1 = calpeq_1.n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	tpt = calpeq_1.tpot[i__ - 1];
	if ((d__1 = tpt - 1., abs(d__1)) < 1e-8) {
	    *phi += calpeq_1.g[i__ - 1] * log(teta);
	} else {
	    d__1 = tpt - 1.;
	    *phi += calpeq_1.g[i__ - 1] * tpt / (tpt - 1.) * pow_dd(&teta, &
		    d__1);
	}
/* L10: */
    }

    *phi = (*phi + calpeq_1.dphi0) * phi0;

    return 0;
} /* phieq_ */

/* *********************************************************************** */
doublereal pmelt_(doublereal *t, integer *ist)
{
    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double pow_dd(doublereal *, doublereal *), exp(doublereal);

    /* Local variables */
    static integer i__, j;
    static doublereal pi;

    /* Fortran I/O blocks */
    static cilist io___238 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*     MELTING PRESSURE FOR GIVEN TEMPERATURE */

/*     IST .EQ. 1 => lower pressure  T<273.16 */
/*     IST .NE. 1 => higher pressure T<273.16 */


    if (*t < cmelteq_1.tt[2]) {
	ret_val = 1e-10;
	io___238.ciunit = cout_1.nout;
	s_wsle(&io___238);
	do_lio(&c__9, &c__1, "<PMELT> T= ", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, " <", (ftnlen)2);
	do_lio(&c__5, &c__1, (char *)&cmelteq_1.tt[2], (ftnlen)sizeof(
		doublereal));
	do_lio(&c__9, &c__1, ". No calculation", (ftnlen)16);
	do_lio(&c__9, &c__1, " possible !", (ftnlen)11);
	e_wsle();
	return ret_val;
    }

    if (*ist == 1 && *t <= cmelteq_1.tt[0]) {
	i__ = 1;
	goto L20;
    }

    for (j = 3; j <= 7; ++j) {
	i__ = 10 - j;
	if (cmelteq_1.ig[i__ - 1] == 0) {
	    goto L10;
	}
	if (*t >= cmelteq_1.tt[i__ - 1]) {
	    goto L20;
	}
L10:
	;
    }

L20:

    if (*t == cmelteq_1.tt[i__ - 1]) {
	ret_val = cmelteq_1.pt[i__ - 1];
	return ret_val;
    }

    d__1 = *t / cmelteq_1.tt[i__ - 1];
    pi = cmelteq_1.g[i__ - 1] * (1. - pow_dd(&d__1, &cmelteq_1.tp[i__ - 1]));

    if (cmelteq_1.ig[i__ - 1] == 1) {
	ret_val = cmelteq_1.pt[i__ - 1] * (pi + 1.);
    } else {
	ret_val = cmelteq_1.pt[i__ - 1] * exp(pi);
    }

    return ret_val;
} /* pmelt_ */

/* ********************************************************************************** */
/* Subroutine */ int tmelt_(doublereal *ts, doublereal *p)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double log(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__, j;
    static doublereal pi;

    /* Fortran I/O blocks */
    static cilist io___242 = { 0, 0, 0, 0, 0 };


/* ********************************************************************************** */

/*     MELTING TEMPERATURE FOR GIVEN PRESSURE */


    if (*p < csub3_1.ptr) {
	io___242.ciunit = cout_1.nout;
	s_wsle(&io___242);
	do_lio(&c__9, &c__1, "<TMELT> P= ", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&(*p), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, "<PTR. TS will not be", (ftnlen)20);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return 0;
    }

    for (j = 2; j <= 7; ++j) {
	if (cmelteq_1.ig[j - 1] == 0) {
	    goto L10;
	}
	if (*p < cmelteq_1.pt[j - 1]) {
	    i__ = j - 1;
	    if (cmelteq_1.ig[i__ - 1] == 0) {
		i__ = j - 2;
	    }
	    goto L20;
	}
	i__ = j;
L10:
	;
    }

L20:

    if (*p == cmelteq_1.pt[i__ - 1]) {
	*ts = cmelteq_1.tt[i__ - 1];
	return 0;
    }

    if (cmelteq_1.ig[i__ - 1] == 1) {
	pi = *p / cmelteq_1.pt[i__ - 1] - 1.;
    } else {
	pi = log(*p / cmelteq_1.pt[i__ - 1]);
    }

    d__1 = 1. - pi / cmelteq_1.g[i__ - 1];
    d__2 = 1. / cmelteq_1.tp[i__ - 1];
    *ts = cmelteq_1.tt[i__ - 1] * pow_dd(&d__1, &d__2);

/* L999: */
    return 0;
} /* tmelt_ */

/* *********************************************************************** */
/* Subroutine */ int blmelt_(void)
{
    return 0;
} /* blmelt_ */

/* *********************************************************************** */

/*     MELTING PRESSURE */

/*         ICE-I       ICE-III         ICE-V     ICE-VI       ICE-VII */


/* *********************************************************************** */
doublereal psubl_(doublereal *t)
{
    /* Initialized data */

    static doublereal tt = 273.16;
    static doublereal pt = 6.11659e-4;
    static doublereal g[3] = { 19.2933313,-3.82215108,1.6528316 };
    static doublereal tp[3] = { -1.,3.,5. };

    /* System generated locals */
    doublereal ret_val = 0.0, d__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double pow_dd(doublereal *, doublereal *), exp(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal pi;

    /* Fortran I/O blocks */
    static cilist io___250 = { 0, 0, 0, 0, 0 };
    static cilist io___251 = { 0, 0, 0, 0, 0 };


/* *********************************************************************** */

/*     SUBLIMATION-PRESSURE: */


    if (*t <= 0.) {
	io___250.ciunit = cout_1.nout;
	s_wsle(&io___250);
	do_lio(&c__9, &c__1, "<PSUBL> T < O . Psubl will not be calculated !",
		 (ftnlen)46);
	e_wsle();
	return ret_val;
    }

    if (*t > tt) {
	io___251.ciunit = cout_1.nout;
	s_wsle(&io___251);
	do_lio(&c__9, &c__1, "<PSUBL> T= ", (ftnlen)11);
	do_lio(&c__5, &c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
	do_lio(&c__9, &c__1, " > TTR . Psubl will not be", (ftnlen)26);
	do_lio(&c__9, &c__1, " calculated !", (ftnlen)13);
	e_wsle();
	return ret_val;
    }

    if (*t == tt) {
	ret_val = pt;
	return ret_val;
    }

    pi = 0.;

    for (i__ = 1; i__ <= 3; ++i__) {
/* L10: */
	d__1 = *t / tt;
	pi += g[i__ - 1] * (1. - pow_dd(&d__1, &tp[i__ - 1]));
    }

    ret_val = pt * exp(pi);

    return ret_val;
} /* psubl_ */

/* ********************************************************************* */
/* *************************************************************************** */
doublereal fni_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val, d__1;

    /* Builtin functions */
    double log(doublereal), exp(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal dn, tn, fnis, dsave, tsave;

/* *************************************************************************** */

/* THIS FUNCTION CALCULATES F'S NORMALIZED IDEAL PART */
/* FOR EINSTEIN-TYPE CP0'S. */


    if ((d__1 = *t - tsave, abs(d__1)) < ceps_1.eps) {
	ret_val = log(*d__ / dsave) + fnis;
	return ret_val;
    }

    dn = *d__ / cnorm_1.dnorm;
    tn = cnorm_1.tnorm / *t;

    ret_val = log(dn) + cfni_1.b2 * log(tn) + cfni_1.b[0] + cfni_1.b[1] * tn;

    i__1 = cfni_1.n;
    for (i__ = cfni_1.npol + 1; i__ <= i__1; ++i__) {
	ret_val += cfni_1.b[i__ - 1] * log(1. - exp(-cfni_1.tpid[i__ - 1] * 
		tn));
/* L20: */
    }

/* L999: */

    tsave = *t;
    dsave = *d__;
    fnis = ret_val;

    return ret_val;
} /* fni_ */

/* ****************************************************************************** */
doublereal fnit_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val, d__1;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal dn, tn, dsave, tsave, fnits;

/* ****************************************************************************** */

/*  THIS SUBROUTINE CALCULATES THE 1ST TN-DERIVATIVE OF F'S NORMALIZED */
/*  IDEAL PART */


    if ((d__1 = *t - tsave, abs(d__1)) < ceps_1.eps) {
	ret_val = fnits;
	return ret_val;
    }

    dn = *d__ / cnorm_1.dnorm;
    tn = cnorm_1.tnorm / *t;

    ret_val = cfni_1.b2 / tn + cfni_1.b[1];

    i__1 = cfni_1.n;
    for (i__ = cfni_1.npol + 1; i__ <= i__1; ++i__) {
	ret_val += cfni_1.tpid[i__ - 1] * cfni_1.b[i__ - 1] * (1 / (1. - exp(
		-cfni_1.tpid[i__ - 1] * tn)) - 1.);
/* L20: */
    }

    tsave = *t;
    dsave = *d__;
    fnits = ret_val;

    return ret_val;
} /* fnit_ */

/* *************************************************************************** */
doublereal fnitt_(doublereal *t, doublereal *d__)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val, d__1, d__2;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal dn, ex, tn, dsave, tsave, fnitts;

/* ******************************************************************************* */

/* THIS FUNCTION CALCULATES THE 2ND TN-DERIVATIVE OF */
/* F'S NORMALIZED IDEAL PART */


    if ((d__1 = *t - tsave, abs(d__1)) < ceps_1.eps) {
	ret_val = fnitts;
	return ret_val;
    }

    dn = *d__ / cnorm_1.dnorm;
    tn = cnorm_1.tnorm / *t;

/* Computing 2nd power */
    d__1 = tn;
    ret_val = -cfni_1.b2 / (d__1 * d__1);

    i__1 = cfni_1.n;
    for (i__ = cfni_1.npol + 1; i__ <= i__1; ++i__) {
	ex = exp(-cfni_1.tpid[i__ - 1] * tn);
/* Computing 2nd power */
	d__1 = cfni_1.tpid[i__ - 1];
/* Computing 2nd power */
	d__2 = 1 / (1. - ex);
	ret_val -= d__1 * d__1 * cfni_1.b[i__ - 1] * (d__2 * d__2) * ex;
/* L20: */
    }

    tsave = *t;
    dsave = *d__;
    fnitts = ret_val;

    return ret_val;
} /* fnitt_ */

/* ********************************************************************** */
/*     BLOCKDATA FNICOO */
/* ********************************************************************** */
/*      IMPLICIT REAL*8(A-H,O-Z) */


/* THIS ROUTINE SETS COEFFICIENTS FOR F'S NORMALIZED IDEAL PART OF WATER */
/* OF COOPER'S EQUATION */

/*   Cooper, J.R. (1982): */
/*             Representation of the Ideal-Gas Thermodynamic Properties */
/*             of Water. Int. J. Therm. 3, 35 (1982). */

/*     COMMON /CFNI/  B2, B(7), TPID(7), NPOL, N */
/*     COMMON /CNULLP/T0,D0,F0,H0,U0,S0,G0 */
/*     DATA F0/0.D0/,H0/0.D0/, U0/0.D0/,S0/0.D0/,G0/0.D0/,NPOL/2/,N/7/ */

/*     DATA B2/3.00632D0/ */

/*     THERE MAY BE MACHINEDEPENDANT PROBLEMS TO YIELD ZERO VALUES FOR */
/*     ENTROPY (S) AND INTERNAL ENERGY (U) AT THE TRIPLE POINT. */
/*     IN ORDER TO YIELD U=0 AND S=0 AT THE TRIPLEPOINT IN THE LIQUID, */
/*     ONE HAS TO ADJUST THE COEFFS. B(1) AND B(2) BY A CALL OF FNULLP. */

/*     DATA (B(I),I=3,7)/ .012436D0,.97315D0,1.27950D0, */
/*    *                   .969560D0,.24873D0/, */
/*    *  (TPID(I),I=1,7)/  0.D0,1.D0, */
/*    *           0.1287202151D+01,0.3537101709D+01,0.7740210774D+01, */
/*    *           0.9243749421D+01,0.2750564020D+02/ */
/*     END */
/* *********************************************************************** */
/* Subroutine */ int fnullp_(void)
{
    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    extern doublereal fni_(doublereal *, doublereal *), fnr_(doublereal *, 
	    doublereal *), fnit_(doublereal *, doublereal *), fnrt_(
	    doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___273 = { 0, 6, 0, 0, 0 };


/* *********************************************************************** */

/*     THIS ROUTINE WILL ADJUST THE COEFS. OF THE IDEAL GAS FUNCTION */
/*     IN ORDER TO YIELD S=U=0 AT THE TRIPLEPOINT */


    cfni_1.b[1] -= fnit_(&cnullp_1.t0, &cnullp_1.d0) + fnrt_(&cnullp_1.t0, &
	    cnullp_1.d0);
    cfni_1.b[0] -= fni_(&cnullp_1.t0, &cnullp_1.d0) + fnr_(&cnullp_1.t0, &
	    cnullp_1.d0);
    s_wsle(&io___273);
    do_lio(&c__9, &c__1, "         B(1)=", (ftnlen)14);
    do_lio(&c__5, &c__1, (char *)&cfni_1.b[0], (ftnlen)sizeof(doublereal));
    do_lio(&c__9, &c__1, "B(2)=", (ftnlen)5);
    do_lio(&c__5, &c__1, (char *)&cfni_1.b[1], (ftnlen)sizeof(doublereal));
    e_wsle();
    return 0;
} /* fnullp_ */

