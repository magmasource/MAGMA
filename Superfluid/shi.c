/* shi.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    doublereal a[300]	/* was [15][20] */, b0[20], gv[15], pi[40], vgas[15];
    integer l;
} salla_;

#define salla_1 salla_

struct {
    doublereal y[15];
    integer mf[21], ml[21], mp, mv;
} salli_;

#define salli_1 salli_

struct {
    doublereal aktfln[15], px, rt, vx, x[15], ytot[20];
} sallr_;

#define sallr_1 sallr_

struct {
    doublereal c__[840]	/* was [15][7][8] */, hf[15], s[15];
} shecp_;

#define shecp_1 shecp_

struct {
    doublereal hom[90]	/* was [15][6] */, tom[90]	/* was [15][6] */;
    integer nom[15];
} sheom_;

#define sheom_1 sheom_

struct {
    doublereal gbar, ge[120]	/* was [15][8] */, vt[75]	/* was [15][5] */, v0[
	    15];
    integer igt[8], kval, mgt;
} ssggv_;

#define ssggv_1 ssggv_

struct {
    char ident[165];
} stext_;

#define stext_1 stext_

struct {
    doublereal xscan, yf[15], yftot[20];
} ssgfc_;

#define ssgfc_1 ssgfc_

struct {
    doublereal w[4500]	/* was [15][15][20] */, wm[225]	/* was [15][15] */;
    integer ich, jch, mch;
} swij_;

#define swij_1 swij_

/* Table of constant values */

static doublereal c_b21 = 2.;
static doublereal c_b22 = 3.;
static doublereal c_b27 = .5;
static doublereal c_b29 = 2.5;
static doublereal c_b54 = 10.;
static doublereal c_b88 = 100.;
static doublereal c_b130 = 500.;
static doublereal c_b172 = 5e3;
static doublereal c_b184 = 4.;
static doublereal c_b185 = 1.5;
static doublereal c_b388 = 298.15;
static doublereal c_b389 = 0.;
static doublereal c_b440 = .33333333333333331;
static doublereal c_b441 = 12.;
static doublereal c_b442 = 6.;
static doublereal c_b447 = -.16666666666666666;

/* Subroutine */ int shi_(doublereal *xn, doublereal *t, doublereal *p, doublereal *v, doublereal *gshi, 
	doublereal *gi)
{
    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);

    /* Local variables */
    static integer i__, m;
    extern /* Subroutine */ int gas_(doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal eps0;
    static integer igas;
    static doublereal gpvt[15], vvvvv;
    extern /* Subroutine */ int factor_(integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

/* C */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*        CALCULATION OF ENTHALPY, ENTROPY, HEAT CAPACITY,              C */
/*                         GIBBS FREE ENERGY, (MU0/RT),                 C */
/*                            ACTIVITY AND FUGACITY                     C */
/*                  FOR A FLUID MIXTURE WITH COMPOSITION X              C */
/*                           AT P (bar) AND T (K)                       C */
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ C */
/*                                                                      C */
/*                Pingfang SHI, and  Surendra K. Saxena                 C */
/*                ------------       ------------------                 C */
/*                       Planetary Geochemistry                         C */
/*                       Uppsala University                             C */
/*                       Uppsala                                        C */
/*                       SWEDEN                                         C */
/*                                                                      C */
/*                Yingwei FEI                                           C */
/*                ------------                                          C */
/*                       Geophysics Laboratory                          C */
/*                       Carnegie Institution                           C */
/*                       Washington D.C.                                C */
/*                       USA                                            C */
/*                                                                      C */
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ C */
/*                                                                      C */
/*    Fluid System:  C-H-O-S-N-Ar Fluids.                               C */
/*    P,T-Range:      P = 1 bar --> 5000 bars                           C */
/*                    T = Critical Points --> 2273.15 K (0.001-1 kbar)  C */
/*                                        --> 3273.15 K (1 - 5 kbar)    C */
/*   ----------------------------------------------------------------   C */
/*                                                                      C */
/* C  Fluid Models:                                                      C */
/*    1. Pure Fluid Species:                                            C */
/*           H2O --- Saul-Wagner (1987, 1989)                           C */
/*           CO2 --- Jacobs-Kerrick (1981)                              C */
/*           CH4 --- Jacobs-Kerrick (1981)                              C */
/*                   Friend et al. (1989);  Grevel (1990)               C */
/*           CO, O2, H2, S2, SO2, COS, H2S --- Saxena-Fei (1987, 1988)  C */
/*                                             Shi-Saxena (1992)        C */
/*           N2, NH3, Ar --- Belonoshko-Saxena (1992)                   C */
/*                                                                      C */
/*   2. Fluid Mixtures:                                                 C */
/*        C-H-O-S-N-Ar --- Binary joins: Interaction-Potential Theory.  C */
/*                                Saxena-Fei (1988)                     C */
/*                                Shi-Saxena (1992)                     C */
/*                                Belonoshko-Shi-Saxena (1992)          C */
/*                       Ternary or higher-order: Kohler Formulation.   C */
/*                                                                      C */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* C */
/*      DIMENSION G(LA),GVT(LA),GVP(LA),GPVT(LA) */

    /* Parameter adjustments */
    --gi;
    --xn;

    /* Function Body */
    s_copy(stext_1.ident, " H2O     ", (ftnlen)11, (ftnlen)9);
    s_copy(stext_1.ident + 11, " CO2     ", (ftnlen)11, (ftnlen)9);
    s_copy(stext_1.ident + 22, " CH4     ", (ftnlen)11, (ftnlen)9);
    s_copy(stext_1.ident + 33, " CO      ", (ftnlen)11, (ftnlen)9);
    s_copy(stext_1.ident + 44, " O2      ", (ftnlen)11, (ftnlen)9);
    s_copy(stext_1.ident + 55, " H2      ", (ftnlen)11, (ftnlen)9);
    s_copy(stext_1.ident + 66, " S2      ", (ftnlen)11, (ftnlen)9);
    s_copy(stext_1.ident + 77, " SO2     ", (ftnlen)11, (ftnlen)9);
    s_copy(stext_1.ident + 88, " COS     ", (ftnlen)11, (ftnlen)9);
    s_copy(stext_1.ident + 99, " H2S     ", (ftnlen)11, (ftnlen)9);
    s_copy(stext_1.ident + 110, " N2      ", (ftnlen)11, (ftnlen)9);
    s_copy(stext_1.ident + 121, " NH3     ", (ftnlen)11, (ftnlen)9);
    s_copy(stext_1.ident + 132, " Ar      ", (ftnlen)11, (ftnlen)9);

    sallr_1.rt = *t * 8.31451;

    for (igas = 1; igas <= 13; ++igas) {
	sallr_1.x[igas - 1] = xn[igas];
/* L1: */
    }
    m = 1;
    salli_1.mf[m - 1] = 1;
    salli_1.ml[m - 1] = 13;
/* ******    Calculation of Pure Fluid Species: */
    gas_(t, p, &vvvvv, salla_1.gv);
/* ******    Calculation of Fluid Mixtures: */
    if (*t < 1873.) {
	factor_(&m, &xn[1], t, p, v);
    }
    *gshi = 0.;
    eps0 = 1e-50;
    *v = 0.;

    for (i__ = 1; i__ <= 13; ++i__) {
	gpvt[i__ - 1] = salla_1.gv[i__ - 1] * sallr_1.rt;
	if (xn[i__] > eps0) {
	    if (*t < 1873.) {
		gpvt[i__ - 1] += sallr_1.aktfln[i__ - 1] * sallr_1.rt;
	    }
	}
	*v += salla_1.vgas[i__ - 1] * xn[i__];
	gi[i__] = gpvt[i__ - 1];
/* L10: */
	*gshi += gpvt[i__ - 1] * xn[i__];
    }
/*      END DO */

    return 0;
} /* shi_ */

/* CC */
/* Subroutine */ int gas_(doublereal *t, doublereal *p, doublereal *vvvvv, doublereal *g)
{
    /* Initialized data */

    static doublereal aa1[10] = { -222.943,-38.315,-15.029,-4.65,-8.082,.604,
	    2.7243,91.198,5.7637,-1264.9 };
    static doublereal bb1[10] = { .029865,.054832,.055411,.056794,.056237,
	    .057324,.057308,.063955,.057544,-.034877 };
    static doublereal cc1[10] = { 0.,0.,0.,0.,0.,0.,-335.99,-11443.,
	    -293.39,95952. };
    static doublereal dd1[10] = { 0.,0.,0.,0.,0.,0.,3.2792e-8,-8.4474e-7,
	    -1.4216e-8,7.1146e-7 };
    static doublereal ee1[10] = { 0.,0.,0.,0.,0.,0.,-145950.,268430.,
	    -1787800.,45675. };
    static doublereal ff1[10] = { 0.,0.,0.,0.,0.,0.,-3.0694e-12,5.5427e-11,
	    9.0888e-13,1.0878e-9 };
    static doublereal gg1[10] = { 0.,0.,0.,0.,0.,0.,296.88,4.363e7,
	    2.7291e8,-4.3608e9 };
    static doublereal hh1[10] = { 35.9794,6.2055,2.8948,1.1645,1.6723,.20685,
	    -.02184,-12.085,-.16838,182.65 };
    static doublereal gvp[15] = { 0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0. };
    static doublereal tcr[10] = { 647.25,304.15,191.05,133.15,154.75,33.25,
	    208.15,430.95,377.95,373.55 };
    static doublereal pcr[10] = { 221.1925,73.8659,46.4069,34.9571,50.7638,
	    12.9696,72.954,78.7295,65.8612,90.0779 };

    /* System generated locals */
    doublereal r__1;
    doublereal d__1, d__2, d__3, d__4, d__5;

    /* Builtin functions */
    double log(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__;
    static doublereal v, z__[15], ha[15], hb[15], hc[15], hd[15], gg, pr[15], tr[15]
	    ;
    extern /* Subroutine */ int h2o_(doublereal *, doublereal *, doublereal *, doublereal *), co2_(
	    doublereal *, doublereal *, doublereal *, doublereal *), ch4_(doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal gvpk[15];
    extern doublereal g1bar_(integer *, doublereal *);

/* C */
/* CC***************************************************************** */
/*                                                                  * */
/*        CALCULATION OF GIBBS FREE ENERGIES FOR REAL GASES         * */
/*                    at P (bar) and T (K)                          * */
/*                                                                  * */
/*    MAXIMUM NO. OF GAS PHASES IS 13                               * */
/*        GAS PHASES HAVE TO BE ARRANGED IN ORDER:                  * */
/*     H2O, CO2, CH4, CO, O2, H2, S2, SO2, COS, H2S, N2, N3 and Ar  * */
/*     (1    2    3    4   5   6   7   8    9   10   11  12     13) * */
/*                                                                  * */
/* CC***************************************************************** */
/* C */
/*      IMPLICIT DOUBLE PRECISION(A-H,O-Z) */
/*      DIMENSION G(LA),GVT(LA),TPOT(8) */
    /* Parameter adjustments */
    --g;

    /* Function Body */

    sallr_1.rt = 8.31451 * *t;
/* C */
/* C    *****  H2O  ***** */

    i__ = 1;
/* CCCCCCCC */
/* C CHOOSING THE P(V,T) FORMULATION FROM Saul-Wagner MODEL */
/* C          Saul & Wagner (1987, 1989) */
/* C                           when T < 1273.15 K and P < 5 kbar. */
    if (*t > 1273.15) {
	goto L502;
    }
    h2o_(t, p, &v, &gg);
    salla_1.vgas[i__ - 1] = v;
    gvp[i__ - 1] = gg / sallr_1.rt;
    z__[i__ - 1] = *p * salla_1.vgas[i__ - 1] / (sallr_1.rt * 10.f);
    salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
    goto L9001;
/* CCCCCCCC */
/* C CHOOSING THE V(P,T) FORMULATION IN SEVERAL PRESSURE SEGMENTS */
/* C       of Saxena-Fei (1987, 1988) and Shi-Saxena (1992) */
/* C                           when T > 1273.15 K and P < 5 kbar. */
L502:
    pr[i__ - 1] = *p / pcr[i__ - 1];
    tr[i__ - 1] = *t / tcr[i__ - 1];
    if (*p > 10. || *p == 10.) {
	goto L6771;
    }
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    salla_1.vgas[i__ - 1] = *t * 4.0267e-4 + .89959 + 718.35 / *t - 
	    368400. / pow_dd(&d__1, &c_b21) + 5.4379e7 / pow_dd(&d__2, &
	    c_b22) - log(*t) * .23965;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    salla_1.vgas[i__ - 1] += (.017952 - *t * 2.5984e-5 - 73.371 / *t + 
	    37138. / pow_dd(&d__1, &c_b21) - 6632400. / pow_dd(&d__2, &
	    c_b22) + log(*t) * .0068494) * *p;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    salla_1.vgas[i__ - 1] += (18.52 - *t * 1.4375e-4 - 2551. / *t + 
	    927630. / pow_dd(&d__1, &c_b21) - 1.4046e8 / pow_dd(&d__2, &
	    c_b22) - log(*t) * .98457) / *p;
    salla_1.vgas[i__ - 1] = sallr_1.rt * salla_1.vgas[i__ - 1];
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*t);
    d__4 = (doublereal) salla_1.vgas[i__ - 1];
    z__[i__ - 1] = (pow_dd(&d__1, &c_b27) * -2.2096 + pow_dd(&d__2, &c_b22) *
	     3.3546e-8) / salla_1.vgas[i__ - 1] + 1 + (pow_dd(&d__3, &c_b29) 
	    * 3.4569e-5 + log(*t) * 64.9764) / pow_dd(&d__4, &c_b21);
    gvpk[i__ - 1] = 0.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvp[i__ - 1] = (*t * 4.0267e-4 + .89959 + 718.35 / *t - 368400. / 
	    pow_dd(&d__1, &c_b21) + 5.4379e7 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .23965) * (*p - 1.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*p);
    gvp[i__ - 1] += (.017952 - *t * 2.5984e-5 - 73.371 / *t + 37138. / 
	    pow_dd(&d__1, &c_b21) - 6632400. / pow_dd(&d__2, &c_b22) + log(*
	    t) * .0068494) * .5 * (pow_dd(&d__3, &c_b21) - 1.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvp[i__ - 1] += (18.52 - *t * 1.4375e-4 - 2551. / *t + 927630. / 
	    pow_dd(&d__1, &c_b21) - 1.4046e8 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .98457) * log(*p / 1.) / 10.;
    goto L2020;
L6771:
    if (*p > 100.01 || *p == 100.01) {
	goto L6772;
    }
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    salla_1.vgas[i__ - 1] = *t * 4.027e-4 + .874 + 803.37 / *t - 444570. /
	     pow_dd(&d__1, &c_b21) + 7.4301e7 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .24792;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    salla_1.vgas[i__ - 1] += (.0038781 - *t * 1.1371e-6 - 2.5486 / *t + 
	    850.59 / pow_dd(&d__1, &c_b21) - 102690. / pow_dd(&d__2, &c_b22)
	     - log(*t) * 1.3657e-4) * *p;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    salla_1.vgas[i__ - 1] += (*t * 4.0758e-4 + 18.394 - 2455.4 / *t + 
	    1298700. / pow_dd(&d__1, &c_b21) - 2.8598e8 / pow_dd(&d__2, &
	    c_b22) - log(*t) * 1.067) / *p;
    salla_1.vgas[i__ - 1] = sallr_1.rt * salla_1.vgas[i__ - 1];
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*t);
    d__4 = (doublereal) salla_1.vgas[i__ - 1];
    z__[i__ - 1] = (pow_dd(&d__1, &c_b27) * -2.2096 + pow_dd(&d__2, &c_b22) *
	     3.3546e-8) / salla_1.vgas[i__ - 1] + 1 + (pow_dd(&d__3, &c_b29) 
	    * 3.4569e-5 + log(*t) * 64.9764) / pow_dd(&d__4, &c_b21);
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] = (*t * 4.0267e-4 + .89959 + 718.35 / *t - 368400. / 
	    pow_dd(&d__1, &c_b21) + 5.4379e7 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .23965) * 9. / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (.017952 - *t * 2.5984e-5 - 73.371 / *t + 37138. / 
	    pow_dd(&d__1, &c_b21) - 6632400. / pow_dd(&d__2, &c_b22) + log(*
	    t) * .0068494) * .5 * (pow_dd(&c_b54, &c_b21) - 1.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (18.52 - *t * 1.4375e-4 - 2551. / *t + 927630. / 
	    pow_dd(&d__1, &c_b21) - 1.4046e8 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .98457) * log(10.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvp[i__ - 1] = (*t * 4.027e-4 + .874 + 803.37 / *t - 444570. / pow_dd(
	    &d__1, &c_b21) + 7.4301e7 / pow_dd(&d__2, &c_b22) - log(*t) * 
	    .24792) * (*p - 10.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*p);
    gvp[i__ - 1] += (.0038781 - *t * 1.1371e-6 - 2.5486 / *t + 850.59 / 
	    pow_dd(&d__1, &c_b21) - 102690. / pow_dd(&d__2, &c_b22) - log(*t)
	     * 1.3657e-4) * .5 * (pow_dd(&d__3, &c_b21) - 100.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvp[i__ - 1] += (*t * 4.0758e-4 + 18.394 - 2455.4 / *t + 1298700. / 
	    pow_dd(&d__1, &c_b21) - 2.8598e8 / pow_dd(&d__2, &c_b22) - log(*
	    t) * 1.067) * log(*p / 10.) / 10.;
    goto L2020;
L6772:
    if (*p > 500. || *p == 500.) {
	goto L6773;
    }
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    salla_1.vgas[i__ - 1] = *t * 6.1393e-5 - 1.0168 + 456.27 / *t - 
	    157280. / pow_dd(&d__1, &c_b21) + 2722200. / pow_dd(&d__2, &
	    c_b22) + log(*t) * .094293;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    salla_1.vgas[i__ - 1] += (4.7802e-4 - *t * 3.8548e-7 - 1.4431 / *t + 
	    788.98 / pow_dd(&d__1, &c_b21) - 145260. / pow_dd(&d__2, &c_b22)
	     + log(*t) * 1.0234e-4) * *p;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    salla_1.vgas[i__ - 1] += (40.511 - *t * .0059424 - 35194. / *t + 
	    1.8536e7 / pow_dd(&d__1, &c_b21) - 2.9916e9 / pow_dd(&d__2, &
	    c_b22) - log(*t) * .72234) / *p;
    salla_1.vgas[i__ - 1] = sallr_1.rt * salla_1.vgas[i__ - 1];
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*t);
    d__4 = (doublereal) salla_1.vgas[i__ - 1];
    z__[i__ - 1] = (pow_dd(&d__1, &c_b27) * -2.2096 + pow_dd(&d__2, &c_b22) *
	     3.3546e-8) / salla_1.vgas[i__ - 1] + 1 + (pow_dd(&d__3, &c_b29) 
	    * 3.4569e-5 + log(*t) * 64.9764) / pow_dd(&d__4, &c_b21);
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] = (*t * 4.0267e-4 + .89959 + 718.35 / *t - 368400. / 
	    pow_dd(&d__1, &c_b21) + 5.4379e7 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .23965) * 9. / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (.017952 - *t * 2.5984e-5 - 73.371 / *t + 37138. / 
	    pow_dd(&d__1, &c_b21) - 6632400. / pow_dd(&d__2, &c_b22) + log(*
	    t) * .0068494) * .5 * (pow_dd(&c_b54, &c_b21) - 1.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (18.52 - *t * 1.4375e-4 - 2551. / *t + 927630. / 
	    pow_dd(&d__1, &c_b21) - 1.4046e8 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .98457) * log(10.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (*t * 4.027e-4 + .874 + 803.37 / *t - 444570. / 
	    pow_dd(&d__1, &c_b21) + 7.4301e7 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .24792) * 90. / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (.0038781 - *t * 1.1371e-6 - 2.5486 / *t + 850.59 / 
	    pow_dd(&d__1, &c_b21) - 102690. / pow_dd(&d__2, &c_b22) - log(*t)
	     * 1.3657e-4) * .5 * (pow_dd(&c_b88, &c_b21) - 100.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (*t * 4.0758e-4 + 18.394 - 2455.4 / *t + 1298700. / 
	    pow_dd(&d__1, &c_b21) - 2.8598e8 / pow_dd(&d__2, &c_b22) - log(*
	    t) * 1.067) * log(10.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvp[i__ - 1] = (*t * 6.1393e-5 - 1.0168 + 456.27 / *t - 157280. / 
	    pow_dd(&d__1, &c_b21) + 2722200. / pow_dd(&d__2, &c_b22) + log(*
	    t) * .094293) * (*p - 100.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*p);
    gvp[i__ - 1] += (4.7802e-4 - *t * 3.8548e-7 - 1.4431 / *t + 788.98 / 
	    pow_dd(&d__1, &c_b21) - 145260. / pow_dd(&d__2, &c_b22) + log(*t)
	     * 1.0234e-4) * .5 * (pow_dd(&d__3, &c_b21) - 1e4) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvp[i__ - 1] += (40.511 - *t * .0059424 - 35194. / *t + 1.8536e7 / 
	    pow_dd(&d__1, &c_b21) - 2.9916e9 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .72234) * log(*p / 100.) / 10.;
    goto L2020;
L6773:
    if (*p > 1e3 || *p == 1e3) {
	goto L2011;
    }
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    salla_1.vgas[i__ - 1] = *t * 2.366e-4 + 1.0202 + 951.62 / *t - 
	    731720. / pow_dd(&d__1, &c_b21) + 1.7906e8 / pow_dd(&d__2, &
	    c_b22) - log(*t) * .24074;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    salla_1.vgas[i__ - 1] += (.0032345 - *t * 2.2552e-7 - 2.1426 / *t + 
	    1203.9 / pow_dd(&d__1, &c_b21) - 258890. / pow_dd(&d__2, &c_b22)
	     - log(*t) * 2.6166e-4) * *p;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    salla_1.vgas[i__ - 1] += (42.568 - *t * .0019179 - 22746. / *t + 
	    474620. / pow_dd(&d__1, &c_b21) + 4.574e8 / pow_dd(&d__2, &
	    c_b22) - log(*t) * 1.0585) / *p;
    salla_1.vgas[i__ - 1] = sallr_1.rt * salla_1.vgas[i__ - 1];
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*t);
    d__4 = (doublereal) salla_1.vgas[i__ - 1];
    z__[i__ - 1] = (pow_dd(&d__1, &c_b27) * -2.2096 + pow_dd(&d__2, &c_b22) *
	     3.3546e-8) / salla_1.vgas[i__ - 1] + 1 + (pow_dd(&d__3, &c_b29) 
	    * 3.4569e-5 + log(*t) * 64.9764) / pow_dd(&d__4, &c_b21);
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] = (*t * 4.0267e-4 + .89959 + 718.35 / *t - 368400. / 
	    pow_dd(&d__1, &c_b21) + 5.4379e7 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .23965) * 9. / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (.017952 - *t * 2.5984e-5 - 73.371 / *t + 37138. / 
	    pow_dd(&d__1, &c_b21) - 6632400. / pow_dd(&d__2, &c_b22) + log(*
	    t) * .0068494) * .5 * (pow_dd(&c_b54, &c_b21) - 1.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (18.52 - *t * 1.4375e-4 - 2551. / *t + 927630. / 
	    pow_dd(&d__1, &c_b21) - 1.4046e8 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .98457) * log(10.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (*t * 4.027e-4 + .874 + 803.37 / *t - 444570. / 
	    pow_dd(&d__1, &c_b21) + 7.4301e7 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .24792) * 90. / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (.0038781 - *t * 1.1371e-6 - 2.5486 / *t + 850.59 / 
	    pow_dd(&d__1, &c_b21) - 102690. / pow_dd(&d__2, &c_b22) - log(*t)
	     * 1.3657e-4) * .5 * (pow_dd(&c_b88, &c_b21) - 100.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (*t * 4.0758e-4 + 18.394 - 2455.4 / *t + 1298700. / 
	    pow_dd(&d__1, &c_b21) - 2.8598e8 / pow_dd(&d__2, &c_b22) - log(*
	    t) * 1.067) * log(10.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (*t * 6.1393e-5 - 1.0168 + 456.27 / *t - 157280. / 
	    pow_dd(&d__1, &c_b21) + 2722200. / pow_dd(&d__2, &c_b22) + log(*
	    t) * .094293) * 400. / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (4.7802e-4 - *t * 3.8548e-7 - 1.4431 / *t + 788.98 / 
	    pow_dd(&d__1, &c_b21) - 145260. / pow_dd(&d__2, &c_b22) + log(*t)
	     * 1.0234e-4) * .5 * (pow_dd(&c_b130, &c_b21) - 1e4) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvpk[i__ - 1] += (40.511 - *t * .0059424 - 35194. / *t + 1.8536e7 / 
	    pow_dd(&d__1, &c_b21) - 2.9916e9 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .72234) * log(5.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvp[i__ - 1] = (*t * 2.366e-4 + 1.0202 + 951.62 / *t - 731720. / 
	    pow_dd(&d__1, &c_b21) + 1.7906e8 / pow_dd(&d__2, &c_b22) - log(*
	    t) * .24074) * (*p - 500.) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*p);
    gvp[i__ - 1] += (.0032345 - *t * 2.2552e-7 - 2.1426 / *t + 1203.9 / 
	    pow_dd(&d__1, &c_b21) - 258890. / pow_dd(&d__2, &c_b22) - log(*t)
	     * 2.6166e-4) * .5 * (pow_dd(&d__3, &c_b21) - 2.5e5) / 10.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvp[i__ - 1] += (42.568 - *t * .0019179 - 22746. / *t + 474620. / 
	    pow_dd(&d__1, &c_b21) + 4.574e8 / pow_dd(&d__2, &c_b22) - log(*t)
	     * 1.0585) * log(*p / 500.) / 10.;
    goto L2020;
L2011:
    if (*p > 5e3 || *p == 5e3) {
	goto L2010;
    }
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*t);
    d__4 = (doublereal) (*t);
    gvpk[i__ - 1] = (aa1[i__ - 1] + bb1[i__ - 1] * *t + cc1[i__ - 1] / *t + 
	    dd1[i__ - 1] * pow_dd(&d__1, &c_b21) + ee1[i__ - 1] / pow_dd(&
	    d__2, &c_b21) + ff1[i__ - 1] * pow_dd(&d__3, &c_b22) + gg1[i__ - 
	    1] / pow_dd(&d__4, &c_b22) + hh1[i__ - 1] * log(*t)) * 1e3 / 
	    sallr_1.rt;
    z__[i__ - 1] = *t * .00116 - .7025 + 99.6799 / *t;
    d__1 = (doublereal) (*t);
    z__[i__ - 1] += (.2143 / *t + pow_dd(&d__1, &c_b22) * -3.1423e-14) * *p;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*p);
    z__[i__ - 1] += (-2.249e-6 / *t + -.1459 / pow_dd(&d__1, &c_b22) + 
	    pow_dd(&d__2, &c_b21) * 2.169e-15) * pow_dd(&d__3, &c_b21);
    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
    gvp[i__ - 1] = (*t * .00116 - .7025 + 99.6799 / *t) * log(*p / 1e3);
    d__1 = (doublereal) (*t);
    gvp[i__ - 1] += (.2143 / *t + pow_dd(&d__1, &c_b22) * -3.1423e-14) * (*
	    p - 1e3);
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*p);
    gvp[i__ - 1] += (-2.249e-6 / *t + -.1459 / pow_dd(&d__1, &c_b22) + 
	    pow_dd(&d__2, &c_b21) * 2.169e-15) * (pow_dd(&d__3, &c_b21) - 
	    1e6) / 2.;
    goto L2020;
L2010:
    gvpk[i__ - 1] = (*t * .064967 - 130.517 + log(*t) * 19.4831) * 1e3 / 
	    sallr_1.rt;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    z__[i__ - 1] = -780420. / pow_dd(&d__1, &c_b21) + 4.0446 + 2.1698e8 / 
	    pow_dd(&d__2, &c_b22) + log(*t) * -.3941;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    z__[i__ - 1] += (.12428 / *t + 45.709 / pow_dd(&d__1, &c_b21) + 
	    -11006. / pow_dd(&d__2, &c_b22)) * *p;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*p);
    z__[i__ - 1] += (-1.1961e-8 / *t - 6.9428e-11 + -5.268e-4 / pow_dd(&
	    d__1, &c_b21) + .1244 / pow_dd(&d__2, &c_b22) + log(*t) * 
	    1.0726e-11) * pow_dd(&d__3, &c_b21);
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*t);
    d__4 = (doublereal) (*p);
    z__[i__ - 1] += (-4.607e-13 / *t + 1.5981e-9 / pow_dd(&d__1, &c_b21) + 
	    -3.7239e-7 / pow_dd(&d__2, &c_b22) + pow_dd(&d__3, &c_b22) * 
	    -2.1564e-36) * pow_dd(&d__4, &c_b22);
    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvp[i__ - 1] = (-780420. / pow_dd(&d__1, &c_b21) + 4.0446 + 2.1698e8 / 
	    pow_dd(&d__2, &c_b22) + log(*t) * -.3941) * log(*p / 5e3);
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    gvp[i__ - 1] += (.12428 / *t + 45.709 / pow_dd(&d__1, &c_b21) + 
	    -11006. / pow_dd(&d__2, &c_b22)) * (*p - 5e3);
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*p);
    gvp[i__ - 1] += (-1.1961e-8 / *t - 6.9428e-11 + -5.268e-4 / pow_dd(&
	    d__1, &c_b21) + .1244 / pow_dd(&d__2, &c_b22) + log(*t) * 
	    1.0726e-11) * (pow_dd(&d__3, &c_b21) - pow_dd(&c_b172, &c_b21)) /
	     2.;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*t);
    d__4 = (doublereal) (*p);
    gvp[i__ - 1] += (-4.607e-13 / *t + 1.5981e-9 / pow_dd(&d__1, &c_b21) + 
	    -3.7239e-7 / pow_dd(&d__2, &c_b22) + pow_dd(&d__3, &c_b22) * 
	    -2.1564e-36) * (pow_dd(&d__4, &c_b22) - pow_dd(&c_b172, &c_b22)) 
	    / 3.;
L2020:
    gvp[i__ - 1] += gvpk[i__ - 1];
    salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];

/* ************************************************ */
/* *       -----  CO2, CH4, CO, O2  -----         * */
/* ************************************************ */
L9001:
    for (i__ = 2; i__ <= 5; ++i__) {
/* 1.  FOR CO2 */
/* CCCCCCCC */
/* C IF CHOOSING THE P(V,T) FORMULATION FROM MRK-EOS MODEL */
/* C          by Kerrick and Jacobs (1981) */
/* C */
	if (i__ == 2) {
	    if (*t > 1273.15) {
		goto L503;
	    }
	    co2_(t, p, &v, &gg);
	    salla_1.vgas[i__ - 1] = v;
	    gvp[i__ - 1] = gg / sallr_1.rt;
	    z__[i__ - 1] = *p * salla_1.vgas[i__ - 1] / (sallr_1.rt * 10.);
	    salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
	    goto L226;
/* 2.  FOR CH4 */
/* CCCCCCCC */
/* C IF CHOOSING THE P(V,T) FORMULATION */
/* C        FROM Schemit-Wagner MODEL by Friend et al. (1989) */
/* C     or FROM MRK-EOS MODEL by Grevel (1990) */
/* C */
	} else if (i__ == 3) {
	    if (*t > 1273.15) {
		goto L503;
	    }
	    ch4_(t, p, &v, &gg);
	    salla_1.vgas[i__ - 1] = v;
	    gvp[i__ - 1] = gg / sallr_1.rt;
	    z__[i__ - 1] = *p * salla_1.vgas[i__ - 1] / (sallr_1.rt * 10.);
	    salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
	    goto L226;
/* 3.  FOR CO AND O2 */
/* CCCCCCCC */
/* C IF CHOOSING THE V(P,T) FORMULATION IN CORRESPONDING-STATE EOS */
/* C              of Saxena-Fei (1987, 1988) */
/* C */
/* C        For CO, O2:           P < 5 kbar; */
/* C        For CO2, CH4:   T > 1273.15 K,  P < 5 kbar. */
/* CCCC */
	} else if (i__ == 4 || i__ == 5) {
L503:
	    pr[i__ - 1] = *p / pcr[i__ - 1];
	    tr[i__ - 1] = *t / tcr[i__ - 1];
	    if (*p > 1e3 || *p == 1e3) {
		goto L2031;
	    }
	    d__1 = (doublereal) tr[i__ - 1];
	    d__2 = (doublereal) tr[i__ - 1];
	    d__3 = (doublereal) tr[i__ - 1];
	    z__[i__ - 1] = (.09827 / tr[i__ - 1] - .2709 / pow_dd(&d__1, &
		    c_b22)) * pr[i__ - 1] + 1 + (.01427 / pow_dd(&d__2, &
		    c_b184) - .00103 / pow_dd(&d__3, &c_b185)) * pr[i__ - 1] 
		    * pr[i__ - 1];
	    gvpk[i__ - 1] = 0.;
	    d__1 = (doublereal) tr[i__ - 1];
	    d__2 = (doublereal) tr[i__ - 1];
	    d__3 = (doublereal) tr[i__ - 1];
	    d__4 = (doublereal) pcr[i__ - 1];
	    d__5 = (doublereal) (*p);
	    gvp[i__ - 1] = log(*p) + (.09827 / tr[i__ - 1] - .2709 / pow_dd(
		    &d__1, &c_b22)) / pcr[i__ - 1] * (*p - 1.) + (.01427 / 
		    pow_dd(&d__2, &c_b184) - .00103 / pow_dd(&d__3, &c_b185))
		     / pow_dd(&d__4, &c_b21) / 2. * (pow_dd(&d__5, &c_b21) - 
		    1.);
	    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
	    goto L2060;
L2031:
	    if (*p > 5e3 || *p == 5e3) {
		goto L2050;
	    }
	    d__1 = (doublereal) (*t);
	    d__2 = (doublereal) (*t);
	    d__3 = (doublereal) (*t);
	    d__4 = (doublereal) (*t);
	    gvpk[i__ - 1] = (aa1[i__ - 1] + bb1[i__ - 1] * *t + cc1[i__ - 1] /
		     *t + dd1[i__ - 1] * pow_dd(&d__1, &c_b21) + ee1[i__ - 1] 
		    / pow_dd(&d__2, &c_b21) + ff1[i__ - 1] * pow_dd(&d__3, &
		    c_b22) + gg1[i__ - 1] / pow_dd(&d__4, &c_b22) + hh1[i__ - 
		    1] * log(*t)) * 1e3 / sallr_1.rt;
	    d__1 = (doublereal) tr[i__ - 1];
	    z__[i__ - 1] = -.5917 / pow_dd(&d__1, &c_b21) + 1.;
	    z__[i__ - 1] += .09122 / tr[i__ - 1] * pr[i__ - 1];
	    d__1 = (doublereal) tr[i__ - 1];
	    d__2 = (doublereal) pr[i__ - 1];
	    z__[i__ - 1] += (-1.4164e-4 / pow_dd(&d__1, &c_b21) + log(tr[i__ 
		    - 1]) * -2.8349e-6) * pow_dd(&d__2, &c_b21);
	    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
	    d__1 = (doublereal) tr[i__ - 1];
	    gvp[i__ - 1] = (-.5917 / pow_dd(&d__1, &c_b21) + 1.) * log(*p / 
		    1e3);
	    gvp[i__ - 1] += .09122 / tr[i__ - 1] * (pr[i__ - 1] - 1e3 / pcr[
		    i__ - 1]);
	    d__1 = (doublereal) tr[i__ - 1];
/* Computing 2nd power */
	    r__1 = pr[i__ - 1];
	    d__2 = (doublereal) (1e3 / pcr[i__ - 1]);
	    gvp[i__ - 1] += (-1.4164e-4 / pow_dd(&d__1, &c_b21) + log(tr[i__ 
		    - 1]) * -2.8349e-6) * (r__1 * r__1 - pow_dd(&d__2, &
		    c_b21)) / 2.;
	    goto L2060;
L2050:
	    d__1 = (doublereal) (*t);
	    d__2 = (doublereal) (*t);
	    d__3 = (doublereal) (*t);
	    d__4 = (doublereal) (*t);
	    gvpk[i__ - 1] = (aa1[i__ - 1] + bb1[i__ - 1] * *t + cc1[i__ - 1] /
		     *t + dd1[i__ - 1] * pow_dd(&d__1, &c_b21) + ee1[i__ - 1] 
		    / pow_dd(&d__2, &c_b21) + ff1[i__ - 1] * pow_dd(&d__3, &
		    c_b22) + gg1[i__ - 1] / pow_dd(&d__4, &c_b22) + hh1[i__ - 
		    1] * log(*t)) * 1e3 / sallr_1.rt;
	    d__1 = (doublereal) tr[i__ - 1];
	    gvpk[i__ - 1] += (-.5917 / pow_dd(&d__1, &c_b21) + 1.) * log(
		    5.);
	    gvpk[i__ - 1] += .09122 / tr[i__ - 1] * (5e3 / pcr[i__ - 1] - 
		    1e3 / pcr[i__ - 1]);
	    d__1 = (doublereal) tr[i__ - 1];
	    d__2 = (doublereal) (5e3 / pcr[i__ - 1]);
	    d__3 = (doublereal) (1e3 / pcr[i__ - 1]);
	    gvpk[i__ - 1] += (-1.4164e-4 / pow_dd(&d__1, &c_b21) + log(tr[
		    i__ - 1]) * -2.8349e-6) * (pow_dd(&d__2, &c_b21) - 
		    pow_dd(&d__3, &c_b21)) / 2.;
	    d__1 = (doublereal) tr[i__ - 1];
	    z__[i__ - 1] = -2.2351 / pow_dd(&d__1, &c_b21) + 2.0614 + log(
		    tr[i__ - 1]) * -.39411;
	    d__1 = (doublereal) tr[i__ - 1];
	    z__[i__ - 1] += (.055125 / tr[i__ - 1] + .039344 / pow_dd(&d__1,
		     &c_b21)) * pr[i__ - 1];
	    d__1 = (doublereal) tr[i__ - 1];
	    d__2 = (doublereal) tr[i__ - 1];
	    d__3 = (doublereal) pr[i__ - 1];
	    z__[i__ - 1] += (-1.8935e-6 / tr[i__ - 1] + -1.1092e-5 / pow_dd(
		    &d__1, &c_b21) + -2.1892e-5 / pow_dd(&d__2, &c_b22)) * 
		    pow_dd(&d__3, &c_b21);
	    d__1 = (doublereal) tr[i__ - 1];
	    d__2 = (doublereal) pr[i__ - 1];
	    z__[i__ - 1] += (5.0527e-11 / tr[i__ - 1] + pow_dd(&d__1, &c_b22)
		     * -6.3032e-21) * pow_dd(&d__2, &c_b22);
	    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
	    d__1 = (doublereal) tr[i__ - 1];
	    gvp[i__ - 1] = (-2.2351 / pow_dd(&d__1, &c_b21) + 2.0614 + log(
		    tr[i__ - 1]) * -.39411) * log(*p / 5e3);
	    d__1 = (doublereal) tr[i__ - 1];
	    gvp[i__ - 1] += (.055125 / tr[i__ - 1] + .039344 / pow_dd(&d__1,
		     &c_b21)) * (pr[i__ - 1] - 5e3 / pcr[i__ - 1]);
	    d__1 = (doublereal) tr[i__ - 1];
	    d__2 = (doublereal) tr[i__ - 1];
	    d__3 = (doublereal) pr[i__ - 1];
	    d__4 = (doublereal) (5e3 / pcr[i__ - 1]);
	    gvp[i__ - 1] += (-1.8935e-6 / tr[i__ - 1] + -1.1092e-5 / pow_dd(
		    &d__1, &c_b21) + -2.1892e-5 / pow_dd(&d__2, &c_b22)) * (
		    pow_dd(&d__3, &c_b21) - pow_dd(&d__4, &c_b21)) / 2.;
	    d__1 = (doublereal) tr[i__ - 1];
	    d__2 = (doublereal) pr[i__ - 1];
	    d__3 = (doublereal) (5e3 / pcr[i__ - 1]);
	    gvp[i__ - 1] += (5.0527e-11 / tr[i__ - 1] + pow_dd(&d__1, &c_b22)
		     * -6.3032e-21) * (pow_dd(&d__2, &c_b22) - pow_dd(&d__3, 
		    &c_b22)) / 3.;
L2060:
	    gvp[i__ - 1] += gvpk[i__ - 1];
	    salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
	}
L226:
	;
    }

/* C    *****  H2  ***** */

/* CCCCCCCC */
/* C  CHOOSING THE V(P,T) FORMULATION IN CORRESPONDING-STATE EOS */
/* C              of Saxena-Fei (1987, 1988) */
/* C */
    i__ = 6;
    pr[i__ - 1] = *p / pcr[i__ - 1];
    tr[i__ - 1] = *t / tcr[i__ - 1];
    if (*p > 1e3 || *p == 1e3) {
	goto L2041;
    }
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) tr[i__ - 1];
    d__3 = (doublereal) tr[i__ - 1];
    z__[i__ - 1] = (.09827 / tr[i__ - 1] - .2709 / pow_dd(&d__1, &c_b22)) * 
	    pr[i__ - 1] + 1 + (.01427 / pow_dd(&d__2, &c_b184) - .00103 / 
	    pow_dd(&d__3, &c_b185)) * pr[i__ - 1] * pr[i__ - 1];
    gvpk[i__ - 1] = 0.;
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) tr[i__ - 1];
    d__3 = (doublereal) tr[i__ - 1];
    d__4 = (doublereal) pcr[i__ - 1];
    d__5 = (doublereal) (*p);
    gvp[i__ - 1] = log(*p) + (.09827 / tr[i__ - 1] - .2709 / pow_dd(&d__1, &
	    c_b22)) / pcr[i__ - 1] * (*p - 1.) + (.01427 / pow_dd(&d__2, &
	    c_b184) - .00103 / pow_dd(&d__3, &c_b185)) / pow_dd(&d__4, &
	    c_b21) / 2. * (pow_dd(&d__5, &c_b21) - 1.);
    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
    goto L2070;
L2041:
    ha[i__ - 1] = -68.712 / *t + 2.2615 + -10537. / (*t * *t) + log(*t) * 
	    -.16936;
    hb[i__ - 1] = .20173 / *t - 2.6707e-4 + 4.57586 / (*t * *t) + log(*t) *
	     3.14515e-5;
    hc[i__ - 1] = 3.4091e-7 / *t - 2.33755e-9 + -.0014188 / (*t * *t) + 
	    log(*t) * 3.0117e-10;
    hd[i__ - 1] = 2.4402e-12 / *t - 3.2606e-15 + -2.4027e-9 / (*t * *t);
/* Computing 3rd power */
    r__1 = *p;
    z__[i__ - 1] = ha[i__ - 1] + hb[i__ - 1] * *p + hc[i__ - 1] * *p * *p + 
	    hd[i__ - 1] * (r__1 * (r__1 * r__1));
    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*t);
    d__4 = (doublereal) (*t);
    gvpk[i__ - 1] = (aa1[i__ - 1] + bb1[i__ - 1] * *t + cc1[i__ - 1] / *t + 
	    dd1[i__ - 1] * pow_dd(&d__1, &c_b21) + ee1[i__ - 1] / pow_dd(&
	    d__2, &c_b21) + ff1[i__ - 1] * pow_dd(&d__3, &c_b22) + gg1[i__ - 
	    1] / pow_dd(&d__4, &c_b22) + hh1[i__ - 1] * log(*t)) * 1e3 / 
	    sallr_1.rt;
    gvp[i__ - 1] = ha[i__ - 1] * log(*p / 1e3) + hb[i__ - 1] * (*p - 1e3);
/* Computing 2nd power */
    r__1 = *p;
    gvp[i__ - 1] += hc[i__ - 1] * (r__1 * r__1 - 1e6) / 2.;
/* Computing 3rd power */
    r__1 = *p;
    gvp[i__ - 1] += hd[i__ - 1] * (r__1 * (r__1 * r__1) - 1e9) / 3.;
L2070:
    gvp[i__ - 1] += gvpk[i__ - 1];
    salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];

/* C    *****  S2  ***** */

/* CCCCCCCC */
/* C  CHOOSING THE V(P,T) FORMULATION IN CORRESPONDING-STATE EOS */
/* C       of Saxena & Fei (1987, 1988), Shi & Saxena (1992) */
/* C */
    i__ = 7;
    pr[i__ - 1] = *p / pcr[i__ - 1];
    tr[i__ - 1] = *t / tcr[i__ - 1];
    if (*p > 1e3 || *p == 1e3) {
	goto L7331;
    }
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) tr[i__ - 1];
    d__3 = (doublereal) tr[i__ - 1];
    z__[i__ - 1] = (.09827 / tr[i__ - 1] - .2709 / pow_dd(&d__1, &c_b22)) * 
	    pr[i__ - 1] + 1 + (.01427 / pow_dd(&d__2, &c_b184) - .00103 / 
	    pow_dd(&d__3, &c_b185)) * pr[i__ - 1] * pr[i__ - 1];
    gvpk[i__ - 1] = 0.;
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) tr[i__ - 1];
    d__3 = (doublereal) tr[i__ - 1];
    d__4 = (doublereal) pcr[i__ - 1];
    d__5 = (doublereal) (*p);
    gvp[i__ - 1] = log(*p) + (.09827 / tr[i__ - 1] - .2709 / pow_dd(&d__1, &
	    c_b22)) / pcr[i__ - 1] * (*p - 1.) + (.01427 / pow_dd(&d__2, &
	    c_b184) - .00103 / pow_dd(&d__3, &c_b185)) / pow_dd(&d__4, &
	    c_b21) / 2. * (pow_dd(&d__5, &c_b21) - 1.);
    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
    goto L7361;
L7331:
    if (*p > 5e3 || *p == 5e3) {
	goto L7351;
    }
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*t);
    d__4 = (doublereal) (*t);
    gvpk[i__ - 1] = (aa1[i__ - 1] + bb1[i__ - 1] * *t + cc1[i__ - 1] / *t + 
	    dd1[i__ - 1] * pow_dd(&d__1, &c_b21) + ee1[i__ - 1] / pow_dd(&
	    d__2, &c_b21) + ff1[i__ - 1] * pow_dd(&d__3, &c_b22) + gg1[i__ - 
	    1] / pow_dd(&d__4, &c_b22) + hh1[i__ - 1] * log(*t)) * 1e3 / 
	    sallr_1.rt;
    d__1 = (doublereal) tr[i__ - 1];
    z__[i__ - 1] = -.5917 / pow_dd(&d__1, &c_b21) + 1.;
    z__[i__ - 1] += .09122 / tr[i__ - 1] * pr[i__ - 1];
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) pr[i__ - 1];
    z__[i__ - 1] += (-1.4164e-4 / pow_dd(&d__1, &c_b21) + log(tr[i__ - 1]) * 
	    -2.8349e-6) * pow_dd(&d__2, &c_b21);
    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
    d__1 = (doublereal) tr[i__ - 1];
    gvp[i__ - 1] = (-.5917 / pow_dd(&d__1, &c_b21) + 1.) * log(*p / 1e3);
    gvp[i__ - 1] += .09122 / tr[i__ - 1] * (pr[i__ - 1] - 1e3 / pcr[i__ - 1]
	    );
    d__1 = (doublereal) tr[i__ - 1];
/* Computing 2nd power */
    r__1 = pr[i__ - 1];
    d__2 = (doublereal) (1e3 / pcr[i__ - 1]);
    gvp[i__ - 1] += (-1.4164e-4 / pow_dd(&d__1, &c_b21) + log(tr[i__ - 1]) * 
	    -2.8349e-6) * (r__1 * r__1 - pow_dd(&d__2, &c_b21)) / 2.;
    goto L7361;
L7351:
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*t);
    d__4 = (doublereal) (*t);
    gvpk[i__ - 1] = (aa1[i__ - 1] + bb1[i__ - 1] * *t + cc1[i__ - 1] / *t + 
	    dd1[i__ - 1] * pow_dd(&d__1, &c_b21) + ee1[i__ - 1] / pow_dd(&
	    d__2, &c_b21) + ff1[i__ - 1] * pow_dd(&d__3, &c_b22) + gg1[i__ - 
	    1] / pow_dd(&d__4, &c_b22) + hh1[i__ - 1] * log(*t)) * 1e3 / 
	    sallr_1.rt;
    d__1 = (doublereal) tr[i__ - 1];
    gvpk[i__ - 1] += (-.5917 / pow_dd(&d__1, &c_b21) + 1.) * log(5.);
    gvpk[i__ - 1] += .09122 / tr[i__ - 1] * (5e3 / pcr[i__ - 1] - 1e3 / 
	    pcr[i__ - 1]);
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) (5e3 / pcr[i__ - 1]);
    d__3 = (doublereal) (1e3 / pcr[i__ - 1]);
    gvpk[i__ - 1] += (-1.4164e-4 / pow_dd(&d__1, &c_b21) + log(tr[i__ - 1]) *
	     -2.8349e-6) * (pow_dd(&d__2, &c_b21) - pow_dd(&d__3, &c_b21)) / 
	    2.;
    d__1 = (doublereal) tr[i__ - 1];
    z__[i__ - 1] = -2.2351 / pow_dd(&d__1, &c_b21) + 2.0614 + log(tr[i__ - 
	    1]) * -.39411;
    d__1 = (doublereal) tr[i__ - 1];
    z__[i__ - 1] += (.055125 / tr[i__ - 1] + .039344 / pow_dd(&d__1, &c_b21)
	    ) * pr[i__ - 1];
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) tr[i__ - 1];
    d__3 = (doublereal) pr[i__ - 1];
    z__[i__ - 1] += (-1.8935e-6 / tr[i__ - 1] + -1.1092e-5 / pow_dd(&d__1, &
	    c_b21) + -2.1892e-5 / pow_dd(&d__2, &c_b22)) * pow_dd(&d__3, &
	    c_b21);
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) pr[i__ - 1];
    z__[i__ - 1] += (5.0527e-11 / tr[i__ - 1] + pow_dd(&d__1, &c_b22) * 
	    -6.3032e-21) * pow_dd(&d__2, &c_b22);
    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
    d__1 = (doublereal) tr[i__ - 1];
    gvp[i__ - 1] = (-2.2351 / pow_dd(&d__1, &c_b21) + 2.0614 + log(tr[i__ - 
	    1]) * -.39411) * log(*p / 5e3);
    d__1 = (doublereal) tr[i__ - 1];
    gvp[i__ - 1] += (.055125 / tr[i__ - 1] + .039344 / pow_dd(&d__1, &c_b21)
	    ) * (pr[i__ - 1] - 5e3 / pcr[i__ - 1]);
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) tr[i__ - 1];
    d__3 = (doublereal) pr[i__ - 1];
    d__4 = (doublereal) (5e3 / pcr[i__ - 1]);
    gvp[i__ - 1] += (-1.8935e-6 / tr[i__ - 1] + -1.1092e-5 / pow_dd(&d__1, &
	    c_b21) + -2.1892e-5 / pow_dd(&d__2, &c_b22)) * (pow_dd(&d__3, &
	    c_b21) - pow_dd(&d__4, &c_b21)) / 2.;
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) pr[i__ - 1];
    d__3 = (doublereal) (5e3 / pcr[i__ - 1]);
    gvp[i__ - 1] += (5.0527e-11 / tr[i__ - 1] + pow_dd(&d__1, &c_b22) * 
	    -6.3032e-21) * (pow_dd(&d__2, &c_b22) - pow_dd(&d__3, &c_b22)) / 
	    3.;
L7361:
    gvp[i__ - 1] += gvpk[i__ - 1];
    salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];

/* C    *****  SO2  ****** */

/* CCCCCCCC */
/* C  CHOOSING THE V(P,T) FORMULATION IN CORRESPONDING-STATE EOS */
/* C               of Shi & Saxena (1992) */
/* C */
    i__ = 8;
    pr[i__ - 1] = *p / pcr[i__ - 1];
    tr[i__ - 1] = *t / tcr[i__ - 1];
    if (*t <= 300. && *p <= 100.) {
	salla_1.vgas[i__ - 1] = sallr_1.rt * 10. / *p;
	gvp[i__ - 1] = sallr_1.rt * log(*p);
	gvp[i__ - 1] /= sallr_1.rt;
	salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
    } else {
	gvpk[i__ - 1] = 0.;
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	z__[i__ - 1] = tr[i__ - 1] * .04541 + .93 - .24482 / tr[i__ - 1] + 
		.24222 / pow_dd(&d__1, &c_b21) - .53701 / pow_dd(&d__2, &
		c_b22) - log(tr[i__ - 1]) * .021583;
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	z__[i__ - 1] += (6.7077e-4 - tr[i__ - 1] * .00184 + .067399 / tr[
		i__ - 1] - .029688 / pow_dd(&d__1, &c_b21) + .029577 / 
		pow_dd(&d__2, &c_b22) + log(tr[i__ - 1]) * .0052307) * pr[
		i__ - 1];
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	d__3 = (doublereal) pr[i__ - 1];
	z__[i__ - 1] += (tr[i__ - 1] * 2.0067e-5 - 3.6646e-4 + 9.5671e-4 / 
		tr[i__ - 1] - 8.0239e-4 / pow_dd(&d__1, &c_b21) + 2.0236e-4 
		/ pow_dd(&d__2, &c_b22) + log(tr[i__ - 1]) * 7.2484e-5) * 
		pow_dd(&d__3, &c_b21);
	salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	gvp[i__ - 1] = (tr[i__ - 1] * .04541 + .93 - .24482 / tr[i__ - 1] 
		+ .24222 / pow_dd(&d__1, &c_b21) - .53701 / pow_dd(&d__2, &
		c_b22) - log(tr[i__ - 1]) * .021583) * log(*p);
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	gvp[i__ - 1] += (6.7077e-4 - tr[i__ - 1] * .00184 + .067399 / tr[
		i__ - 1] - .029688 / pow_dd(&d__1, &c_b21) + .029577 / 
		pow_dd(&d__2, &c_b22) + log(tr[i__ - 1]) * .0052307) * (pr[
		i__ - 1] - 1. / pcr[i__ - 1]);
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
/* Computing 2nd power */
	r__1 = pr[i__ - 1];
	d__3 = (doublereal) (1. / pcr[i__ - 1]);
	gvp[i__ - 1] += (tr[i__ - 1] * 2.0067e-5 - 3.6646e-4 + 9.5671e-4 / 
		tr[i__ - 1] - 8.0239e-4 / pow_dd(&d__1, &c_b21) + 2.0236e-4 
		/ pow_dd(&d__2, &c_b22) + log(tr[i__ - 1]) * 7.2484e-5) * (
		r__1 * r__1 - pow_dd(&d__3, &c_b21)) / 2.;
	gvp[i__ - 1] += gvpk[i__ - 1];
	salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
    }

/* C    *****  COS  ***** */

/* CCCCCCCC */
/* C  CHOOSING THE V(P,T) FORMULATION IN CORRESPONDING-STATE EOS */
/* C       of Saxena & Fei (1987, 1988), Shi & Saxena (1992) */
/* C */
    i__ = 9;
    pr[i__ - 1] = *p / pcr[i__ - 1];
    tr[i__ - 1] = *t / tcr[i__ - 1];
    if (*p > 1e3 || *p == 1e3) {
	goto L7471;
    }
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) tr[i__ - 1];
    d__3 = (doublereal) tr[i__ - 1];
    z__[i__ - 1] = (.09827 / tr[i__ - 1] - .2709 / pow_dd(&d__1, &c_b22)) * 
	    pr[i__ - 1] + 1 + (.01427 / pow_dd(&d__2, &c_b184) - .00103 / 
	    pow_dd(&d__3, &c_b185)) * pr[i__ - 1] * pr[i__ - 1];
    gvpk[i__ - 1] = 0.;
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) tr[i__ - 1];
    d__3 = (doublereal) tr[i__ - 1];
    d__4 = (doublereal) pcr[i__ - 1];
    d__5 = (doublereal) (*p);
    gvp[i__ - 1] = log(*p) + (.09827 / tr[i__ - 1] - .2709 / pow_dd(&d__1, &
	    c_b22)) / pcr[i__ - 1] * (*p - 1.) + (.01427 / pow_dd(&d__2, &
	    c_b184) - .00103 / pow_dd(&d__3, &c_b185)) / pow_dd(&d__4, &
	    c_b21) / 2. * (pow_dd(&d__5, &c_b21) - 1.);
    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
    goto L7421;
L7471:
    if (*p > 5e3 || *p == 5e3) {
	goto L7472;
    }
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*t);
    d__4 = (doublereal) (*t);
    gvpk[i__ - 1] = (aa1[i__ - 1] + bb1[i__ - 1] * *t + cc1[i__ - 1] / *t + 
	    dd1[i__ - 1] * pow_dd(&d__1, &c_b21) + ee1[i__ - 1] / pow_dd(&
	    d__2, &c_b21) + ff1[i__ - 1] * pow_dd(&d__3, &c_b22) + gg1[i__ - 
	    1] / pow_dd(&d__4, &c_b22) + hh1[i__ - 1] * log(*t)) * 1e3 / 
	    sallr_1.rt;
    d__1 = (doublereal) tr[i__ - 1];
    z__[i__ - 1] = -.5917 / pow_dd(&d__1, &c_b21) + 1.;
    z__[i__ - 1] += .09122 / tr[i__ - 1] * pr[i__ - 1];
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) pr[i__ - 1];
    z__[i__ - 1] += (-1.4164e-4 / pow_dd(&d__1, &c_b21) + log(tr[i__ - 1]) * 
	    -2.8349e-6) * pow_dd(&d__2, &c_b21);
    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
    d__1 = (doublereal) tr[i__ - 1];
    gvp[i__ - 1] = (-.5917 / pow_dd(&d__1, &c_b21) + 1.) * log(*p / 1e3);
    gvp[i__ - 1] += .09122 / tr[i__ - 1] * (pr[i__ - 1] - 1e3 / pcr[i__ - 1]
	    );
    d__1 = (doublereal) tr[i__ - 1];
/* Computing 2nd power */
    r__1 = pr[i__ - 1];
    d__2 = (doublereal) (1e3 / pcr[i__ - 1]);
    gvp[i__ - 1] += (-1.4164e-4 / pow_dd(&d__1, &c_b21) + log(tr[i__ - 1]) * 
	    -2.8349e-6) * (r__1 * r__1 - pow_dd(&d__2, &c_b21)) / 2.;
    goto L7421;
L7472:
    d__1 = (doublereal) (*t);
    d__2 = (doublereal) (*t);
    d__3 = (doublereal) (*t);
    d__4 = (doublereal) (*t);
    gvpk[i__ - 1] = (aa1[i__ - 1] + bb1[i__ - 1] * *t + cc1[i__ - 1] / *t + 
	    dd1[i__ - 1] * pow_dd(&d__1, &c_b21) + ee1[i__ - 1] / pow_dd(&
	    d__2, &c_b21) + ff1[i__ - 1] * pow_dd(&d__3, &c_b22) + gg1[i__ - 
	    1] / pow_dd(&d__4, &c_b22) + hh1[i__ - 1] * log(*t)) * 1e3 / 
	    sallr_1.rt;
    d__1 = (doublereal) tr[i__ - 1];
    gvpk[i__ - 1] += (-.5917 / pow_dd(&d__1, &c_b21) + 1.) * log(5.);
    gvpk[i__ - 1] += .09122 / tr[i__ - 1] * (5e3 / pcr[i__ - 1] - 1e3 / 
	    pcr[i__ - 1]);
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) (5e3 / pcr[i__ - 1]);
    d__3 = (doublereal) (1e3 / pcr[i__ - 1]);
    gvpk[i__ - 1] += (-1.4164e-4 / pow_dd(&d__1, &c_b21) + log(tr[i__ - 1]) *
	     -2.8349e-6) * (pow_dd(&d__2, &c_b21) - pow_dd(&d__3, &c_b21)) / 
	    2.;
    d__1 = (doublereal) tr[i__ - 1];
    z__[i__ - 1] = -2.2351 / pow_dd(&d__1, &c_b21) + 2.0614 + log(tr[i__ - 
	    1]) * -.39411;
    d__1 = (doublereal) tr[i__ - 1];
    z__[i__ - 1] += (.055125 / tr[i__ - 1] + .039344 / pow_dd(&d__1, &c_b21)
	    ) * pr[i__ - 1];
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) tr[i__ - 1];
    d__3 = (doublereal) pr[i__ - 1];
    z__[i__ - 1] += (-1.8935e-6 / tr[i__ - 1] + -1.1092e-5 / pow_dd(&d__1, &
	    c_b21) + -2.1892e-5 / pow_dd(&d__2, &c_b22)) * pow_dd(&d__3, &
	    c_b21);
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) pr[i__ - 1];
    z__[i__ - 1] += (5.0527e-11 / tr[i__ - 1] + pow_dd(&d__1, &c_b22) * 
	    -6.3032e-21) * pow_dd(&d__2, &c_b22);
    salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
    d__1 = (doublereal) tr[i__ - 1];
    gvp[i__ - 1] = (-2.2351 / pow_dd(&d__1, &c_b21) + 2.0614 + log(tr[i__ - 
	    1]) * -.39411) * log(*p / 5e3);
    d__1 = (doublereal) tr[i__ - 1];
    gvp[i__ - 1] += (.055125 / tr[i__ - 1] + .039344 / pow_dd(&d__1, &c_b21)
	    ) * (pr[i__ - 1] - 5e3 / pcr[i__ - 1]);
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) tr[i__ - 1];
    d__3 = (doublereal) pr[i__ - 1];
    d__4 = (doublereal) (5e3 / pcr[i__ - 1]);
    gvp[i__ - 1] += (-1.8935e-6 / tr[i__ - 1] + -1.1092e-5 / pow_dd(&d__1, &
	    c_b21) + -2.1892e-5 / pow_dd(&d__2, &c_b22)) * (pow_dd(&d__3, &
	    c_b21) - pow_dd(&d__4, &c_b21)) / 2.;
    d__1 = (doublereal) tr[i__ - 1];
    d__2 = (doublereal) pr[i__ - 1];
    d__3 = (doublereal) (5e3 / pcr[i__ - 1]);
    gvp[i__ - 1] += (5.0527e-11 / tr[i__ - 1] + pow_dd(&d__1, &c_b22) * 
	    -6.3032e-21) * (pow_dd(&d__2, &c_b22) - pow_dd(&d__3, &c_b22)) / 
	    3.;
L7421:
    gvp[i__ - 1] += gvpk[i__ - 1];
    salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];

/* C    *****  H2S  ***** */

/* CCCCCCCC */
/* C  CHOOSING THE V(P,T) FORMULATION IN CORRESPONDING-STATE EOS */
/* C               of Shi & Saxena (1992) */
/* C */
    i__ = 10;
    pr[i__ - 1] = *p / pcr[i__ - 1];
    tr[i__ - 1] = *t / tcr[i__ - 1];
    if (*t <= 300. && *p <= 50.) {
	salla_1.vgas[i__ - 1] = sallr_1.rt * 10. / *p;
	gvp[i__ - 1] = sallr_1.rt * log(*p);
	gvp[i__ - 1] /= sallr_1.rt;
	salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
    } else {
	if (*p > 500.01 || *p == 500.01) {
	    goto L1171;
	}
	gvpk[i__ - 1] = 0.;
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	z__[i__ - 1] = tr[i__ - 1] * 1.1177 + 1.4721 + 3.9657 / tr[i__ - 1]
		 - 10.028 / pow_dd(&d__1, &c_b21) + 4.5484 / pow_dd(&d__2, &
		c_b22) - log(tr[i__ - 1]) * 3.82;
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	z__[i__ - 1] += (tr[i__ - 1] * .10887 + .16066 + .29014 / tr[i__ - 
		1] - .99593 / pow_dd(&d__1, &c_b21) - .18627 / pow_dd(&d__2,
		 &c_b22) - log(tr[i__ - 1]) * .45515) * pr[i__ - 1];
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	d__3 = (doublereal) pr[i__ - 1];
	z__[i__ - 1] += (-.28933 - tr[i__ - 1] * .070522 + .39828 / tr[i__ 
		- 1] - .050533 / pow_dd(&d__1, &c_b21) + .1176 / pow_dd(&
		d__2, &c_b22) + log(tr[i__ - 1]) * .33972) * pow_dd(&d__3, &
		c_b21);
	salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	gvp[i__ - 1] = (tr[i__ - 1] * 1.1177 + 1.4721 + 3.9657 / tr[i__ - 
		1] - 10.028 / pow_dd(&d__1, &c_b21) + 4.5484 / pow_dd(&d__2,
		 &c_b22) - log(tr[i__ - 1]) * 3.82) * log(*p);
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	gvp[i__ - 1] += (tr[i__ - 1] * .10887 + .16066 + .29014 / tr[i__ - 
		1] - .99593 / pow_dd(&d__1, &c_b21) - .18627 / pow_dd(&d__2,
		 &c_b22) - log(tr[i__ - 1]) * .45515) * (pr[i__ - 1] - 1. / 
		pcr[i__ - 1]);
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	d__3 = (doublereal) pr[i__ - 1];
	d__4 = (doublereal) (1. / pcr[i__ - 1]);
	gvp[i__ - 1] += (-.28933 - tr[i__ - 1] * .070522 + .39828 / tr[i__ 
		- 1] - .050533 / pow_dd(&d__1, &c_b21) + .1176 / pow_dd(&
		d__2, &c_b22) + log(tr[i__ - 1]) * .33972) * (pow_dd(&d__3, &
		c_b21) - pow_dd(&d__4, &c_b21)) / 2.;
	goto L1172;
L1171:
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	gvpk[i__ - 1] = (tr[i__ - 1] * 1.1177 + 1.4721 + 3.9657 / tr[i__ - 
		1] - 10.028 / pow_dd(&d__1, &c_b21) + 4.5484 / pow_dd(&d__2,
		 &c_b22) - log(tr[i__ - 1]) * 3.82) * log(500.);
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	gvpk[i__ - 1] += (tr[i__ - 1] * .10887 + .16066 + .29014 / tr[i__ 
		- 1] - .99593 / pow_dd(&d__1, &c_b21) - .18627 / pow_dd(&
		d__2, &c_b22) - log(tr[i__ - 1]) * .45515) * (500. / pcr[
		i__ - 1] - 1. / pcr[i__ - 1]);
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	d__3 = (doublereal) (500. / pcr[i__ - 1]);
	d__4 = (doublereal) (1. / pcr[i__ - 1]);
	gvpk[i__ - 1] += (-.28933 - tr[i__ - 1] * .070522 + .39828 / tr[
		i__ - 1] - .050533 / pow_dd(&d__1, &c_b21) + .1176 / pow_dd(
		&d__2, &c_b22) + log(tr[i__ - 1]) * .33972) * (pow_dd(&d__3, 
		&c_b21) - pow_dd(&d__4, &c_b21)) / 2.;
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	z__[i__ - 1] = tr[i__ - 1] * 1.8359e-4 + .60031 + .046502 / tr[i__ 
		- 1] + .36113 / pow_dd(&d__1, &c_b21) - .79708 / pow_dd(&
		d__2, &c_b22) + log(tr[i__ - 1]) * .25548;
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	z__[i__ - 1] += (tr[i__ - 1] * .0017675 + .022329 + .048904 / tr[
		i__ - 1] - .020378 / pow_dd(&d__1, &c_b21) + .033047 / 
		pow_dd(&d__2, &c_b22) - log(tr[i__ - 1]) * .011308) * pr[i__ 
		- 1];
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	d__3 = (doublereal) pr[i__ - 1];
	z__[i__ - 1] += (5.6686e-4 - tr[i__ - 1] * 4.2218e-6 - .0011837 / 
		tr[i__ - 1] + .0014942 / pow_dd(&d__1, &c_b21) - 7.9541e-4 /
		 pow_dd(&d__2, &c_b22) - log(tr[i__ - 1]) * 2.6759e-4) * 
		pow_dd(&d__3, &c_b21);
	salla_1.vgas[i__ - 1] = sallr_1.rt * 10. * z__[i__ - 1] / *p;
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	gvp[i__ - 1] = (tr[i__ - 1] * 1.8359e-4 + .60031 + .046502 / tr[
		i__ - 1] + .36113 / pow_dd(&d__1, &c_b21) - .79708 / pow_dd(
		&d__2, &c_b22) + log(tr[i__ - 1]) * .25548) * log(*p / 500.)
		;
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
	gvp[i__ - 1] += (tr[i__ - 1] * .0017675 + .022329 + .048904 / tr[
		i__ - 1] - .020378 / pow_dd(&d__1, &c_b21) + .033047 / 
		pow_dd(&d__2, &c_b22) - log(tr[i__ - 1]) * .011308) * (pr[
		i__ - 1] - 500. / pcr[i__ - 1]);
	d__1 = (doublereal) tr[i__ - 1];
	d__2 = (doublereal) tr[i__ - 1];
/* Computing 2nd power */
	r__1 = pr[i__ - 1];
	d__3 = (doublereal) (500. / pcr[i__ - 1]);
	gvp[i__ - 1] += (5.6686e-4 - tr[i__ - 1] * 4.2218e-6 - .0011837 / 
		tr[i__ - 1] + .0014942 / pow_dd(&d__1, &c_b21) - 7.9541e-4 /
		 pow_dd(&d__2, &c_b22) - log(tr[i__ - 1]) * 2.6759e-4) * (
		r__1 * r__1 - pow_dd(&d__3, &c_b21)) / 2.;
L1172:
	gvp[i__ - 1] += gvpk[i__ - 1];
	salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
    }

/* C    *****  N2, NH3, Ar  ***** */

/* CCCCCCCC */
/* C  CHOOSING THE V(P,T) FORMULATION OF Molecular Dynamics EOS */
/* C               of Belonoshko and Saxena (1992) */
/* C */

    i__ = 11;
    if (*p < 5e3) {
	salla_1.vgas[i__ - 1] = sallr_1.rt * 10. / *p;
	gvp[i__ - 1] = sallr_1.rt * log(*p);
	gvp[i__ - 1] /= sallr_1.rt;
	salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
    } else {
	gvp[i__ - 1] = (*t * 63.916 / 1e3 - 80.094 + log(*t) * 13.616) * 
		1e3;
	gvp[i__ - 1] /= sallr_1.rt;
	salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
    }

    i__ = 12;
    if (*p < 5e3) {
	salla_1.vgas[i__ - 1] = sallr_1.rt * 10. / *p;
	gvp[i__ - 1] = sallr_1.rt * log(*p);
	gvp[i__ - 1] /= sallr_1.rt;
	salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
    } else {
	gvp[i__ - 1] = (*t * 70.171 / 1e3 - 3.873 + log(*t) * 2.302) * 
		1e3;
	gvp[i__ - 1] /= sallr_1.rt;
	salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
    }

    i__ = 13;
    if (*p < 5e3) {
	salla_1.vgas[i__ - 1] = sallr_1.rt * 10. / *p;
	gvp[i__ - 1] = sallr_1.rt * log(*p);
	gvp[i__ - 1] /= sallr_1.rt;
	salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
    } else {
	gvp[i__ - 1] = (*t * 69.179 / 1e3 - 5.238 + log(*t) * 3.102) * 
		1e3;
	gvp[i__ - 1] /= sallr_1.rt;
	salla_1.gv[i__ - 1] = g1bar_(&i__, t) + gvp[i__ - 1];
    }

    return 0;
} /* gas_ */

/* CC */
doublereal g1bar_(integer *i__, doublereal *t)
{
    /* Initialized data */

    static doublereal hfss[13] = { -241818.46,-393509.38,-74809.92,-110524.54,
	    0.,0.,128365.12,-296829.7,-142088.64,-20627.12,0.,-45720.,
	    0. };
    static doublereal sss[13] = { 188.715,213.635,186.155,197.564,205.029,
	    130.574,228.07,248.111,231.459,205.685,191.61,192.78,
	    154.84 };
    static doublereal c1[7] = { 46.461,.005966,6.32e6,0.,-7.957e8,0.,-16630. 
	    };
    static doublereal c2[7] = { 70.728,-8.822e-4,3.464e6,0.,-2.492e8,0.,
	    -18760. };
    static doublereal c3[7] = { 129.01,-4.849e-4,2.221e7,0.,-2.291e9,0.,
	    -76560. };
    static doublereal c4[7] = { 38.578,6.513e-4,1.781e6,0.,-9.971e7,0.,
	    -7725. };
    static doublereal c5[7] = { 39.45,5.609e-4,906700.,0.,603900.,0.,-6101. }
	    ;
    static doublereal c6[7] = { 23.948,.004962,527900.,0.,-1.525e8,0.,953.6 }
	    ;
    static doublereal c7[7] = { 38.408,-4.63e-5,-463500.,0.,6.93e7,0.,-993.6 
	    };
    static doublereal c8[7] = { 71.828,-.002672,2.354e6,0.,-2.083e8,0.,
	    -16420. };
    static doublereal c9[7] = { 42.441,-.027573,707320.,4.6064e-6,-5.2166e9,
	    .40721,-17432. };
    static doublereal c10[7] = { 65.459,9.168e-4,9.326e6,0.,1.054e9,0.,
	    -28840. };
    static doublereal c11[7] = { 23.941,.011068,190640.,-2.5518e-6,0.,0.,0. }
	    ;
    static doublereal c12[7] = { 29.735,.039119,292430.,-8.2274e-6,0.,-143.78,
	    0. };
    static doublereal c13[7] = { 20.8,0.,0.,0.,0.,0.,0. };

    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static integer j, k;
    extern doublereal h0_(integer *, doublereal *), s0_(integer *, doublereal *);

/* C */
/* *********************************************************************** */
/* *                                                                     * */
/* *  FUNCTION G1BAR(I,T) -----                                          * */
/* *                                                                     * */
/* *      CALCULATION OF THE FREE ENERGY AT 1 bar AND T FOR PHASE I      * */
/* *                                                                     * */
/* *     G1BAR(I,T) = G(1, T)                                            * */
/* *          = Hf(1, 298) - T*S(1, 298)                                 * */
/* *                                                                     * */
/* *                   .T                 .T                             * */
/* *               +  .   Cp(T) dT  - T* .  [Cp(T)/T] dT                 * */
/* *                 . 298              .298                             * */
/* *                                                                     * */
/* *  where  Cp(T) = a + bT + cT^-2 + dT^2 + eT^-3 + fT^-0.5 + g/T       * */
/* *                                                                     * */
/* *********************************************************************** */
/* C */
/*     IMPLICIT DOUBLE PRECISION(A-H,O-Z) */

/* C */

    for (k = 1; k <= 13; ++k) {
	shecp_1.hf[k - 1] = hfss[k - 1];
	shecp_1.s[k - 1] = sss[k - 1];
	sheom_1.hom[k - 1] = 0.;
	sheom_1.tom[k - 1] = 6e3;
	sheom_1.nom[k - 1] = 1;
/* L30: */
    }

    for (j = 1; j <= 7; ++j) {
	shecp_1.c__[(j * 7 + 1) * 15 - 120] = c1[j - 1];
	shecp_1.c__[(j * 7 + 1) * 15 - 119] = c2[j - 1];
	shecp_1.c__[(j * 7 + 1) * 15 - 118] = c3[j - 1];
	shecp_1.c__[(j * 7 + 1) * 15 - 117] = c4[j - 1];
	shecp_1.c__[(j * 7 + 1) * 15 - 116] = c5[j - 1];
	shecp_1.c__[(j * 7 + 1) * 15 - 115] = c6[j - 1];
	shecp_1.c__[(j * 7 + 1) * 15 - 114] = c7[j - 1];
	shecp_1.c__[(j * 7 + 1) * 15 - 113] = c8[j - 1];
	shecp_1.c__[(j * 7 + 1) * 15 - 112] = c9[j - 1];
	shecp_1.c__[(j * 7 + 1) * 15 - 111] = c10[j - 1];
	shecp_1.c__[(j * 7 + 1) * 15 - 110] = c11[j - 1];
	shecp_1.c__[(j * 7 + 1) * 15 - 109] = c12[j - 1];
	shecp_1.c__[(j * 7 + 1) * 15 - 108] = c13[j - 1];
/* L20: */
    }

/* C     ********  G(1,T) FOR GASE SPECIES I */

    ret_val = (h0_(i__, t) - *t * s0_(i__, t)) / 8.31451 / *t;

    return ret_val;
} /* g1bar_ */

doublereal h0_(integer *i__, doublereal *t)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static integer j;
    extern doublereal cpint_(doublereal *, doublereal *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, doublereal *, doublereal *, doublereal *);

/* C */
/* ********************************************************************* */
/* *                                                                   * */
/* *      CALCULATION OF THE ENTHALPY AT T K FOR SPECIES I             * */
/* *                                                                   * */
/* ********************************************************************* */
/* C */
/*     IMPLICIT DOUBLE PRECISION(A-H,O-Z) */

    if (sheom_1.nom[*i__ - 1] == 1) {
    } else if (sheom_1.tom[*i__ - 1] <= *t) {
	ret_val = shecp_1.hf[*i__ - 1] + cpint_(&c_b388, &sheom_1.tom[*i__ - 
		1], &shecp_1.c__[*i__ - 1], &shecp_1.c__[*i__ + 104], &
		shecp_1.c__[*i__ + 209], &shecp_1.c__[*i__ + 314], &
		shecp_1.c__[*i__ + 419], &shecp_1.c__[*i__ + 524], &
		shecp_1.c__[*i__ + 629], &c_b389, &c_b389, &c_b389, &c_b389) 
		+ sheom_1.hom[*i__ - 1];
	j = 2;
L96:
	if (j < sheom_1.nom[*i__ - 1]) {
	    if (sheom_1.tom[*i__ + j * 15 - 16] <= *t) {
		goto L21;
	    }
	}
	ret_val += cpint_(&sheom_1.tom[*i__ + (j - 1) * 15 - 16], t, &
		shecp_1.c__[*i__ + (j + 7) * 15 - 121], &shecp_1.c__[*i__ + (
		j + 14) * 15 - 121], &shecp_1.c__[*i__ + (j + 21) * 15 - 121],
		 &shecp_1.c__[*i__ + (j + 28) * 15 - 121], &shecp_1.c__[*i__ 
		+ (j + 35) * 15 - 121], &shecp_1.c__[*i__ + (j + 42) * 15 - 
		121], &shecp_1.c__[*i__ + (j + 49) * 15 - 121], &c_b389, &
		c_b389, &c_b389, &c_b389);

	return ret_val;

L21:
	ret_val = ret_val + cpint_(&sheom_1.tom[*i__ + (j - 1) * 15 - 16], &
		sheom_1.tom[*i__ + j * 15 - 16], &shecp_1.c__[*i__ + (j + 7) *
		 15 - 121], &shecp_1.c__[*i__ + (j + 14) * 15 - 121], &
		shecp_1.c__[*i__ + (j + 21) * 15 - 121], &shecp_1.c__[*i__ + (
		j + 28) * 15 - 121], &shecp_1.c__[*i__ + (j + 35) * 15 - 121],
		 &shecp_1.c__[*i__ + (j + 42) * 15 - 121], &shecp_1.c__[*i__ 
		+ (j + 49) * 15 - 121], &c_b389, &c_b389, &c_b389, &c_b389) + 
		sheom_1.hom[*i__ + j * 15 - 16];
	++j;
	goto L96;
    }
    ret_val = shecp_1.hf[*i__ - 1] + cpint_(&c_b388, t, &shecp_1.c__[*i__ - 1]
	    , &shecp_1.c__[*i__ + 104], &shecp_1.c__[*i__ + 209], &
	    shecp_1.c__[*i__ + 314], &shecp_1.c__[*i__ + 419], &shecp_1.c__[*
	    i__ + 524], &shecp_1.c__[*i__ + 629], &c_b389, &c_b389, &c_b389, &
	    c_b389);

    return ret_val;
} /* h0_ */

/* C */
doublereal s0_(integer *i__, doublereal *t)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static integer j;
    extern doublereal cpint_(doublereal *, doublereal *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, doublereal *, doublereal *, doublereal *);

/* C */
/* ********************************************************************** */
/* *                                                                    * */
/* *      CALCULATION OF THE ENTROPY AT T K FOR SPECIES I               * */
/* *                                                                    * */
/* ********************************************************************** */
/* C */
/*      IMPLICIT DOUBLE PRECISION(A-H,O-Z) */

    if (sheom_1.nom[*i__ - 1] == 1) {
    } else if (sheom_1.tom[*i__ - 1] <= *t) {
	ret_val = shecp_1.s[*i__ - 1] + cpint_(&c_b388, &sheom_1.tom[*i__ - 1]
		, &shecp_1.c__[*i__ + 104], &shecp_1.c__[*i__ + 314], &
		shecp_1.c__[*i__ + 629], &c_b389, &shecp_1.c__[*i__ + 209], &
		c_b389, &shecp_1.c__[*i__ - 1], &shecp_1.c__[*i__ + 419], &
		shecp_1.c__[*i__ + 524], &c_b389, &c_b389) + sheom_1.hom[*i__ 
		- 1] / sheom_1.tom[*i__ - 1];
	j = 2;
L180:
	if (j < sheom_1.nom[*i__ - 1]) {
	    if (sheom_1.tom[*i__ + j * 15 - 16] <= *t) {
		goto L177;
	    }
	}
	ret_val += cpint_(&sheom_1.tom[*i__ + (j - 1) * 15 - 16], t, &
		shecp_1.c__[*i__ + (j + 14) * 15 - 121], &shecp_1.c__[*i__ + (
		j + 28) * 15 - 121], &shecp_1.c__[*i__ + (j + 49) * 15 - 121],
		 &c_b389, &shecp_1.c__[*i__ + (j + 21) * 15 - 121], &c_b389, &
		shecp_1.c__[*i__ + (j + 7) * 15 - 121], &shecp_1.c__[*i__ + (
		j + 35) * 15 - 121], &shecp_1.c__[*i__ + (j + 42) * 15 - 121],
		 &c_b389, &c_b389);

	return ret_val;

L177:
	ret_val = ret_val + cpint_(&sheom_1.tom[*i__ + (j - 1) * 15 - 16], &
		sheom_1.tom[*i__ + j * 15 - 16], &shecp_1.c__[*i__ + (j + 14) 
		* 15 - 121], &shecp_1.c__[*i__ + (j + 28) * 15 - 121], &
		shecp_1.c__[*i__ + (j + 49) * 15 - 121], &c_b389, &
		shecp_1.c__[*i__ + (j + 21) * 15 - 121], &c_b389, &
		shecp_1.c__[*i__ + (j + 7) * 15 - 121], &shecp_1.c__[*i__ + (
		j + 35) * 15 - 121], &shecp_1.c__[*i__ + (j + 42) * 15 - 121],
		 &c_b389, &c_b389) + sheom_1.hom[*i__ + j * 15 - 16] / 
		sheom_1.tom[*i__ + j * 15 - 16];
	++j;
	goto L180;
    }
    ret_val = shecp_1.s[*i__ - 1] + cpint_(&c_b388, t, &shecp_1.c__[*i__ + 
	    104], &shecp_1.c__[*i__ + 314], &shecp_1.c__[*i__ + 629], &c_b389,
	     &shecp_1.c__[*i__ + 209], &c_b389, &shecp_1.c__[*i__ - 1], &
	    shecp_1.c__[*i__ + 419], &shecp_1.c__[*i__ + 524], &c_b389, &
	    c_b389);

    return ret_val;
} /* s0_ */

/* C */
doublereal cpint_(doublereal *t0, doublereal *t1, doublereal *ca, doublereal *cb, doublereal *cc, doublereal *cd, 
	doublereal *ce, doublereal *cf, doublereal *cg, doublereal *ch, doublereal *ci, doublereal *cj, doublereal *ck)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double sqrt(doublereal), log(doublereal);

    /* Local variables */
    static doublereal t2, t3, t4, t5, t6, ta, tb, tc, td, te, tf, tg, th, ti, tj, 
	    tk, ot0, ot1;

/* C */
/* ******************************************************************** */
/* *                                                                  * */
/* *        CALCULATION OF THE CP AND CP/T INTERGRAL                  * */
/* *                                                                  * */
/* ******************************************************************** */
/* C */
/*      IMPLICIT DOUBLE PRECISION(A-H,O-Z) */
    ot0 = 0.;
    ot1 = 0.;
    if (*t0 != ot0 || *t1 != ot1) {
	ot0 = *t0;
	ot1 = *t1;
	t2 = *t0 + *t1;
	t3 = *t0 * *t1;
	t4 = t3 * t3;
	t5 = *t0 * *t0;
	t6 = t5 + *t1 * *t1;
	ta = *t1 - *t0;
	tb = ta * t2 / 2.;
	tc = ta / t3;
	td = ta * (t2 * t2 - t3) / 3.;
	te = tb / t4;
	tf = (sqrt(*t1) - sqrt(*t0)) * 2.;
	tg = log(*t1 / *t0);
	th = td / (t3 * t4);
	ti = tf / sqrt(t3);
	tj = tb * t6 / 2.;
	tk = ta * (*t1 * t2 * t6 + t5 * t5) / 5.;
    }
    ret_val = *ca * ta + *cb * tb + *cc * tc + *cd * td + *ce * te + *cf * tf 
	    + *cg * tg + *ch * th + *ci * ti + *cj * tj + *ck * tk;

    return ret_val;
} /* cpint_ */

/* C */
/* Subroutine */ int factor_(integer *m, doublereal *xn, doublereal *t, doublereal *p, doublereal *v)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double log(doublereal);

    /* Local variables */
    static integer i__, j, iwm;
    extern /* Subroutine */ int gamma1_(integer *, doublereal *, doublereal *, doublereal *), 
	    gamma2_(integer *, doublereal *, doublereal *, doublereal *), interw_(integer *, 
	    doublereal *, doublereal *, doublereal *);

/* C */
/* C************************************************************************** */
/*        FACTOR IS A SUBROUTINE FOR THE CALCULATION OF FLUID MIXTURES      * */
/*              Giving Logarithmized ACTIVITY COEFFICIENTS    (AKTFLN)      * */
/*                                   EXCESS VOLUME            (EXVMIX)      * */
/*                                   EXCESS EHTHALPY          (EXHMIX)      * */
/*                                   EXCESS ENTROPY           (EXSMIX)      * */
/*                                   EXCESS Gibbs FREE ENERGY (EXGMIX)      * */
/*                  as functions of TEMPERATURE    (T, K)                   * */
/*                                  PRESSURE       (P, bar)                 * */
/*                             and  MOLE FRACTION  (X).                     * */
/*                                                                          * */
/*                                                                          * */
/*   NOTE: THIS PART IS REWRITTEN BASED ON 'SFAC.FOR', IN ORDER TO          * */
/*           CONSIDER FLUID MIXTURES IN THE SYSTEM C-H-O-S-N-Ar             * */
/*                              .1991.                                      * */
/*                                                                          * */
/*     **  THE ORDER OF  13  FLUID SPECIES IS:                              * */
/*           H2O, CO2, CH4, CO, O2, H2, S2, SO2, COS, H2S, N2, NH3 AND Ar   * */
/*                                                                          * */
/* C************************************************************************** */
/* C */
/*      IMPLICIT DOUBLE PRECISION(A-H,O-Z) */
/* -------------------------------------------------------------------------* */
/*        AKTFLN(I) = LOGARITHMIZED ACTIVITY COEFFICIENT FOR SPECIES I */
/*        B0(J) = TOTAL AMOUNT OR LN OF THE EQUIL ACTIVITY OF COMPONENT J */
/*        GV(I) = (MU0/RT) FOR SPECIES I WITH VOLUME TERM INCLUDED */
/*        MF(M) = LOWEST SPECIES NUMBER IN MIXTURE M */
/*        ML(M) = HIGHEST SPECIES NUMBER IN MIXTURE M */
/*        MV = TOTAL NUMBER OF MIXTURES (INVARIANTS = MIXTURE (MP+1)) */
/*        PI(J) = LAGRANGIAN MULTIPLIER FOR COMPONENT J */
/*        PX = CALCULATED TOTAL PRESSURE/BAR */
/*        RT = R*T (R = GAS CONSTANT/J.K-1MOL-1) */
/*        VX = CALCULATED TOTAL VOLUME/DM3 */
/*        X(I) = MOLE FRACTION FOR SPECIES I */
/*        Y(I) = AMOUNT OF SUBSTANCE FOR SPECIES I */
/*        YTOT(M) = TOTAL AMOUNT OF MIXTURE M */
/*  CONSULT THE INPUT GUIDE FOR AN EXPLANATION OF THE FOLLOWING VARIABLES: */
/*                 A(I,J), L, MP, P, T, AND V. */
/* -------------------------------------------------------------------------* */
/* C************************************************************************* */
/* *    ***************************************************************     * */
/* * **** H2O-CO2-CH4-CO-O2-H2-S2-SO2-COS-H2S-N2-NH3-Ar FLUID MIXTURE ****  * */
/* *    ****  IWM = 1   ------- NON-IDEAL FLUID-MIXTURE MODEL      ****     * */
/* *    ****              ==>  SUBROUTINE GAMME2                   ****     * */
/* *    ****  IWM = 2   ------- IDEAL-MIXING MODEL (pure fluids)   ****     * */
/* *    ****              ==>  SUBROUTINE GAMME1                   ****     * */
/* *    ***************************************************************     * */
/* C************************************************************************* */
    iwm = 1;
    if (iwm == 2) {
	goto L555;
    }
/* -------------------------------------- */
/* C  NON-IDEAL MIXING */
/* -------------------------------------- */

    interw_(m, t, p, v);
/* CCCCCCCCCCCCCCCCCCCCCC */
/*  !!! IF ONE WOULD LIKE TO CHANGE W(I,J,M)'s in SOLGAS or CHEMSAGE, */
/*         THE PROGRAMS WILL ASK HIM TO GIVE OPTION "W", */
/*       and INPUT ICH and JCH (comp. nos. in mix.) AND MCH (mix. no.), */
/*           AND FINALLY THE NEW VALUES FOR W(ICH,JCH,MCH)'s */
/* CCCCCCCCCCCCCCCCCCCCCC */
/* SURPOSING ONE WILL NOT CHANGE THE INTERACTION ENERGIES W(I,J,M)'s, */
/*        ----> ICH = JCH = MCH = 0 */
    swij_1.ich = 0;
    swij_1.jch = 0;
    swij_1.mch = 0;

    if (swij_1.ich != 1 || swij_1.jch != 2 || swij_1.mch != 1) {
	swij_1.w[15] = swij_1.wm[15] / sallr_1.rt;
    }
    if (swij_1.ich != 1 || swij_1.jch != 3 || swij_1.mch != 1) {
	swij_1.w[30] = swij_1.wm[30] / sallr_1.rt;
    }
    if (swij_1.ich != 1 || swij_1.jch != 4 || swij_1.mch != 1) {
	swij_1.w[45] = swij_1.wm[45] / sallr_1.rt;
    }
    if (swij_1.ich != 1 || swij_1.jch != 5 || swij_1.mch != 1) {
	swij_1.w[60] = swij_1.wm[60] / sallr_1.rt;
    }
    if (swij_1.ich != 1 || swij_1.jch != 6 || swij_1.mch != 1) {
	swij_1.w[75] = swij_1.wm[75] / sallr_1.rt;
    }
    if (swij_1.ich != 1 || swij_1.jch != 7 || swij_1.mch != 1) {
	swij_1.w[90] = swij_1.wm[90] / sallr_1.rt;
    }
    if (swij_1.ich != 1 || swij_1.jch != 8 || swij_1.mch != 1) {
	swij_1.w[105] = swij_1.wm[105] / sallr_1.rt;
    }
    if (swij_1.ich != 1 || swij_1.jch != 9 || swij_1.mch != 1) {
	swij_1.w[120] = swij_1.wm[120] / sallr_1.rt;
    }
    if (swij_1.ich != 1 || swij_1.jch != 10 || swij_1.mch != 1) {
	swij_1.w[135] = swij_1.wm[135] / sallr_1.rt;
    }
    if (swij_1.ich != 1 || swij_1.jch != 11 || swij_1.mch != 1) {
	swij_1.w[150] = swij_1.wm[150] / sallr_1.rt;
    }
    if (swij_1.ich != 1 || swij_1.jch != 12 || swij_1.mch != 1) {
	swij_1.w[165] = swij_1.wm[165] / sallr_1.rt;
    }
    if (swij_1.ich != 1 || swij_1.jch != 13 || swij_1.mch != 1) {
	swij_1.w[180] = swij_1.wm[180] / sallr_1.rt;
    }

    if (swij_1.ich != 2 || swij_1.jch != 1 || swij_1.mch != 1) {
	swij_1.w[1] = swij_1.w[15];
    }
    if (swij_1.ich != 2 || swij_1.jch != 3 || swij_1.mch != 1) {
	swij_1.w[31] = swij_1.wm[31] / sallr_1.rt;
    }
    if (swij_1.ich != 2 || swij_1.jch != 4 || swij_1.mch != 1) {
	swij_1.w[46] = swij_1.wm[46] / sallr_1.rt;
    }
    if (swij_1.ich != 2 || swij_1.jch != 5 || swij_1.mch != 1) {
	swij_1.w[61] = swij_1.wm[61] / sallr_1.rt;
    }
    if (swij_1.ich != 2 || swij_1.jch != 6 || swij_1.mch != 1) {
	swij_1.w[76] = swij_1.wm[76] / sallr_1.rt;
    }
    if (swij_1.ich != 2 || swij_1.jch != 7 || swij_1.mch != 1) {
	swij_1.w[91] = swij_1.wm[91] / sallr_1.rt;
    }
    if (swij_1.ich != 2 || swij_1.jch != 8 || swij_1.mch != 1) {
	swij_1.w[106] = swij_1.wm[106] / sallr_1.rt;
    }
    if (swij_1.ich != 2 || swij_1.jch != 9 || swij_1.mch != 1) {
	swij_1.w[121] = swij_1.wm[121] / sallr_1.rt;
    }
    if (swij_1.ich != 2 || swij_1.jch != 10 || swij_1.mch != 1) {
	swij_1.w[136] = swij_1.wm[136] / sallr_1.rt;
    }
    if (swij_1.ich != 2 || swij_1.jch != 11 || swij_1.mch != 1) {
	swij_1.w[151] = swij_1.wm[151] / sallr_1.rt;
    }
    if (swij_1.ich != 2 || swij_1.jch != 12 || swij_1.mch != 1) {
	swij_1.w[166] = swij_1.wm[166] / sallr_1.rt;
    }
    if (swij_1.ich != 2 || swij_1.jch != 13 || swij_1.mch != 1) {
	swij_1.w[181] = swij_1.wm[181] / sallr_1.rt;
    }

    if (swij_1.ich != 3 || swij_1.jch != 1 || swij_1.mch != 1) {
	swij_1.w[2] = swij_1.w[30];
    }
    if (swij_1.ich != 3 || swij_1.jch != 2 || swij_1.mch != 1) {
	swij_1.w[17] = swij_1.w[31];
    }
    if (swij_1.ich != 3 || swij_1.jch != 4 || swij_1.mch != 1) {
	swij_1.w[47] = swij_1.wm[47] / sallr_1.rt;
    }
    if (swij_1.ich != 3 || swij_1.jch != 5 || swij_1.mch != 1) {
	swij_1.w[62] = swij_1.wm[62] / sallr_1.rt;
    }
    if (swij_1.ich != 3 || swij_1.jch != 6 || swij_1.mch != 1) {
	swij_1.w[77] = swij_1.wm[77] / sallr_1.rt;
    }
    if (swij_1.ich != 3 || swij_1.jch != 7 || swij_1.mch != 1) {
	swij_1.w[92] = swij_1.wm[92] / sallr_1.rt;
    }
    if (swij_1.ich != 3 || swij_1.jch != 8 || swij_1.mch != 1) {
	swij_1.w[107] = swij_1.wm[107] / sallr_1.rt;
    }
    if (swij_1.ich != 3 || swij_1.jch != 9 || swij_1.mch != 1) {
	swij_1.w[122] = swij_1.wm[122] / sallr_1.rt;
    }
    if (swij_1.ich != 3 || swij_1.jch != 10 || swij_1.mch != 1) {
	swij_1.w[137] = swij_1.wm[137] / sallr_1.rt;
    }
    if (swij_1.ich != 3 || swij_1.jch != 11 || swij_1.mch != 1) {
	swij_1.w[152] = swij_1.wm[152] / sallr_1.rt;
    }
    if (swij_1.ich != 3 || swij_1.jch != 12 || swij_1.mch != 1) {
	swij_1.w[167] = swij_1.wm[167] / sallr_1.rt;
    }
    if (swij_1.ich != 3 || swij_1.jch != 13 || swij_1.mch != 1) {
	swij_1.w[182] = swij_1.wm[182] / sallr_1.rt;
    }

    if (swij_1.ich != 4 || swij_1.jch != 1 || swij_1.mch != 1) {
	swij_1.w[3] = swij_1.w[45];
    }
    if (swij_1.ich != 4 || swij_1.jch != 2 || swij_1.mch != 1) {
	swij_1.w[18] = swij_1.w[46];
    }
    if (swij_1.ich != 4 || swij_1.jch != 3 || swij_1.mch != 1) {
	swij_1.w[33] = swij_1.w[47];
    }
    if (swij_1.ich != 4 || swij_1.jch != 5 || swij_1.mch != 1) {
	swij_1.w[63] = swij_1.wm[63] / sallr_1.rt;
    }
    if (swij_1.ich != 4 || swij_1.jch != 6 || swij_1.mch != 1) {
	swij_1.w[78] = swij_1.wm[78] / sallr_1.rt;
    }
    if (swij_1.ich != 4 || swij_1.jch != 7 || swij_1.mch != 1) {
	swij_1.w[93] = swij_1.wm[93] / sallr_1.rt;
    }
    if (swij_1.ich != 4 || swij_1.jch != 8 || swij_1.mch != 1) {
	swij_1.w[108] = swij_1.wm[108] / sallr_1.rt;
    }
    if (swij_1.ich != 4 || swij_1.jch != 9 || swij_1.mch != 1) {
	swij_1.w[123] = swij_1.wm[123] / sallr_1.rt;
    }
    if (swij_1.ich != 4 || swij_1.jch != 10 || swij_1.mch != 1) {
	swij_1.w[138] = swij_1.wm[138] / sallr_1.rt;
    }
    if (swij_1.ich != 4 || swij_1.jch != 11 || swij_1.mch != 1) {
	swij_1.w[153] = swij_1.wm[153] / sallr_1.rt;
    }
    if (swij_1.ich != 4 || swij_1.jch != 12 || swij_1.mch != 1) {
	swij_1.w[168] = swij_1.wm[168] / sallr_1.rt;
    }
    if (swij_1.ich != 4 || swij_1.jch != 13 || swij_1.mch != 1) {
	swij_1.w[183] = swij_1.wm[183] / sallr_1.rt;
    }

    if (swij_1.ich != 5 || swij_1.jch != 1 || swij_1.mch != 1) {
	swij_1.w[4] = swij_1.w[60];
    }
    if (swij_1.ich != 5 || swij_1.jch != 2 || swij_1.mch != 1) {
	swij_1.w[19] = swij_1.w[61];
    }
    if (swij_1.ich != 5 || swij_1.jch != 3 || swij_1.mch != 1) {
	swij_1.w[34] = swij_1.w[62];
    }
    if (swij_1.ich != 5 || swij_1.jch != 4 || swij_1.mch != 1) {
	swij_1.w[49] = swij_1.w[63];
    }
    if (swij_1.ich != 5 || swij_1.jch != 6 || swij_1.mch != 1) {
	swij_1.w[79] = swij_1.wm[79] / sallr_1.rt;
    }
    if (swij_1.ich != 5 || swij_1.jch != 7 || swij_1.mch != 1) {
	swij_1.w[94] = swij_1.wm[94] / sallr_1.rt;
    }
    if (swij_1.ich != 5 || swij_1.jch != 8 || swij_1.mch != 1) {
	swij_1.w[109] = swij_1.wm[109] / sallr_1.rt;
    }
    if (swij_1.ich != 5 || swij_1.jch != 9 || swij_1.mch != 1) {
	swij_1.w[124] = swij_1.wm[124] / sallr_1.rt;
    }
    if (swij_1.ich != 5 || swij_1.jch != 10 || swij_1.mch != 1) {
	swij_1.w[139] = swij_1.wm[139] / sallr_1.rt;
    }
    if (swij_1.ich != 5 || swij_1.jch != 11 || swij_1.mch != 1) {
	swij_1.w[154] = swij_1.wm[154] / sallr_1.rt;
    }
    if (swij_1.ich != 5 || swij_1.jch != 12 || swij_1.mch != 1) {
	swij_1.w[169] = swij_1.wm[169] / sallr_1.rt;
    }
    if (swij_1.ich != 5 || swij_1.jch != 13 || swij_1.mch != 1) {
	swij_1.w[184] = swij_1.wm[184] / sallr_1.rt;
    }

    if (swij_1.ich != 6 || swij_1.jch != 1 || swij_1.mch != 1) {
	swij_1.w[5] = swij_1.w[75];
    }
    if (swij_1.ich != 6 || swij_1.jch != 2 || swij_1.mch != 1) {
	swij_1.w[20] = swij_1.w[76];
    }
    if (swij_1.ich != 6 || swij_1.jch != 3 || swij_1.mch != 1) {
	swij_1.w[35] = swij_1.w[77];
    }
    if (swij_1.ich != 6 || swij_1.jch != 4 || swij_1.mch != 1) {
	swij_1.w[50] = swij_1.w[78];
    }
    if (swij_1.ich != 6 || swij_1.jch != 5 || swij_1.mch != 1) {
	swij_1.w[65] = swij_1.w[79];
    }
    if (swij_1.ich != 6 || swij_1.jch != 7 || swij_1.mch != 1) {
	swij_1.w[95] = swij_1.wm[95] / sallr_1.rt;
    }
    if (swij_1.ich != 6 || swij_1.jch != 8 || swij_1.mch != 1) {
	swij_1.w[110] = swij_1.wm[110] / sallr_1.rt;
    }
    if (swij_1.ich != 6 || swij_1.jch != 9 || swij_1.mch != 1) {
	swij_1.w[125] = swij_1.wm[125] / sallr_1.rt;
    }
    if (swij_1.ich != 6 || swij_1.jch != 10 || swij_1.mch != 1) {
	swij_1.w[140] = swij_1.wm[140] / sallr_1.rt;
    }
    if (swij_1.ich != 6 || swij_1.jch != 11 || swij_1.mch != 1) {
	swij_1.w[155] = swij_1.wm[155] / sallr_1.rt;
    }
    if (swij_1.ich != 6 || swij_1.jch != 12 || swij_1.mch != 1) {
	swij_1.w[170] = swij_1.wm[170] / sallr_1.rt;
    }
    if (swij_1.ich != 6 || swij_1.jch != 13 || swij_1.mch != 1) {
	swij_1.w[185] = swij_1.wm[185] / sallr_1.rt;
    }

    if (swij_1.ich != 7 || swij_1.jch != 1 || swij_1.mch != 1) {
	swij_1.w[6] = swij_1.w[90];
    }
    if (swij_1.ich != 7 || swij_1.jch != 2 || swij_1.mch != 1) {
	swij_1.w[21] = swij_1.w[91];
    }
    if (swij_1.ich != 7 || swij_1.jch != 3 || swij_1.mch != 1) {
	swij_1.w[36] = swij_1.w[92];
    }
    if (swij_1.ich != 7 || swij_1.jch != 4 || swij_1.mch != 1) {
	swij_1.w[51] = swij_1.w[93];
    }
    if (swij_1.ich != 7 || swij_1.jch != 5 || swij_1.mch != 1) {
	swij_1.w[66] = swij_1.w[94];
    }
    if (swij_1.ich != 7 || swij_1.jch != 6 || swij_1.mch != 1) {
	swij_1.w[81] = swij_1.w[95];
    }
    if (swij_1.ich != 7 || swij_1.jch != 8 || swij_1.mch != 1) {
	swij_1.w[111] = swij_1.wm[111] / sallr_1.rt;
    }
    if (swij_1.ich != 7 || swij_1.jch != 9 || swij_1.mch != 1) {
	swij_1.w[126] = swij_1.wm[126] / sallr_1.rt;
    }
    if (swij_1.ich != 7 || swij_1.jch != 10 || swij_1.mch != 1) {
	swij_1.w[141] = swij_1.wm[141] / sallr_1.rt;
    }
    if (swij_1.ich != 7 || swij_1.jch != 11 || swij_1.mch != 1) {
	swij_1.w[156] = swij_1.wm[156] / sallr_1.rt;
    }
    if (swij_1.ich != 7 || swij_1.jch != 12 || swij_1.mch != 1) {
	swij_1.w[171] = swij_1.wm[171] / sallr_1.rt;
    }
    if (swij_1.ich != 7 || swij_1.jch != 13 || swij_1.mch != 1) {
	swij_1.w[186] = swij_1.wm[186] / sallr_1.rt;
    }

    if (swij_1.ich != 8 || swij_1.jch != 1 || swij_1.mch != 1) {
	swij_1.w[7] = swij_1.w[105];
    }
    if (swij_1.ich != 8 || swij_1.jch != 2 || swij_1.mch != 1) {
	swij_1.w[22] = swij_1.w[106];
    }
    if (swij_1.ich != 8 || swij_1.jch != 3 || swij_1.mch != 1) {
	swij_1.w[37] = swij_1.w[107];
    }
    if (swij_1.ich != 8 || swij_1.jch != 4 || swij_1.mch != 1) {
	swij_1.w[52] = swij_1.w[108];
    }
    if (swij_1.ich != 8 || swij_1.jch != 5 || swij_1.mch != 1) {
	swij_1.w[67] = swij_1.w[109];
    }
    if (swij_1.ich != 8 || swij_1.jch != 6 || swij_1.mch != 1) {
	swij_1.w[82] = swij_1.w[110];
    }
    if (swij_1.ich != 8 || swij_1.jch != 7 || swij_1.mch != 1) {
	swij_1.w[97] = swij_1.w[111];
    }
    if (swij_1.ich != 8 || swij_1.jch != 9 || swij_1.mch != 1) {
	swij_1.w[127] = swij_1.wm[127] / sallr_1.rt;
    }
    if (swij_1.ich != 8 || swij_1.jch != 10 || swij_1.mch != 1) {
	swij_1.w[142] = swij_1.wm[142] / sallr_1.rt;
    }
    if (swij_1.ich != 8 || swij_1.jch != 11 || swij_1.mch != 1) {
	swij_1.w[157] = swij_1.wm[157] / sallr_1.rt;
    }
    if (swij_1.ich != 8 || swij_1.jch != 12 || swij_1.mch != 1) {
	swij_1.w[172] = swij_1.wm[172] / sallr_1.rt;
    }
    if (swij_1.ich != 8 || swij_1.jch != 13 || swij_1.mch != 1) {
	swij_1.w[187] = swij_1.wm[187] / sallr_1.rt;
    }

    if (swij_1.ich != 9 || swij_1.jch != 1 || swij_1.mch != 1) {
	swij_1.w[8] = swij_1.w[120];
    }
    if (swij_1.ich != 9 || swij_1.jch != 2 || swij_1.mch != 1) {
	swij_1.w[23] = swij_1.w[121];
    }
    if (swij_1.ich != 9 || swij_1.jch != 3 || swij_1.mch != 1) {
	swij_1.w[38] = swij_1.w[122];
    }
    if (swij_1.ich != 9 || swij_1.jch != 4 || swij_1.mch != 1) {
	swij_1.w[53] = swij_1.w[123];
    }
    if (swij_1.ich != 9 || swij_1.jch != 5 || swij_1.mch != 1) {
	swij_1.w[68] = swij_1.w[124];
    }
    if (swij_1.ich != 9 || swij_1.jch != 6 || swij_1.mch != 1) {
	swij_1.w[83] = swij_1.w[125];
    }
    if (swij_1.ich != 9 || swij_1.jch != 7 || swij_1.mch != 1) {
	swij_1.w[98] = swij_1.w[126];
    }
    if (swij_1.ich != 9 || swij_1.jch != 8 || swij_1.mch != 1) {
	swij_1.w[113] = swij_1.w[127];
    }
    if (swij_1.ich != 9 || swij_1.jch != 10 || swij_1.mch != 1) {
	swij_1.w[143] = swij_1.wm[143] / sallr_1.rt;
    }
    if (swij_1.ich != 9 || swij_1.jch != 11 || swij_1.mch != 1) {
	swij_1.w[158] = swij_1.wm[158] / sallr_1.rt;
    }
    if (swij_1.ich != 9 || swij_1.jch != 12 || swij_1.mch != 1) {
	swij_1.w[173] = swij_1.wm[173] / sallr_1.rt;
    }
    if (swij_1.ich != 9 || swij_1.jch != 13 || swij_1.mch != 1) {
	swij_1.w[188] = swij_1.wm[188] / sallr_1.rt;
    }

    if (swij_1.ich != 10 || swij_1.jch != 1 || swij_1.mch != 1) {
	swij_1.w[9] = swij_1.w[135];
    }
    if (swij_1.ich != 10 || swij_1.jch != 2 || swij_1.mch != 1) {
	swij_1.w[24] = swij_1.w[136];
    }
    if (swij_1.ich != 10 || swij_1.jch != 3 || swij_1.mch != 1) {
	swij_1.w[39] = swij_1.w[137];
    }
    if (swij_1.ich != 10 || swij_1.jch != 4 || swij_1.mch != 1) {
	swij_1.w[54] = swij_1.w[138];
    }
    if (swij_1.ich != 10 || swij_1.jch != 5 || swij_1.mch != 1) {
	swij_1.w[69] = swij_1.w[139];
    }
    if (swij_1.ich != 10 || swij_1.jch != 6 || swij_1.mch != 1) {
	swij_1.w[84] = swij_1.w[140];
    }
    if (swij_1.ich != 10 || swij_1.jch != 7 || swij_1.mch != 1) {
	swij_1.w[99] = swij_1.w[141];
    }
    if (swij_1.ich != 10 || swij_1.jch != 8 || swij_1.mch != 1) {
	swij_1.w[114] = swij_1.w[142];
    }
    if (swij_1.ich != 10 || swij_1.jch != 9 || swij_1.mch != 1) {
	swij_1.w[129] = swij_1.w[143];
    }
    if (swij_1.ich != 10 || swij_1.jch != 11 || swij_1.mch != 1) {
	swij_1.w[159] = swij_1.wm[159] / sallr_1.rt;
    }
    if (swij_1.ich != 10 || swij_1.jch != 12 || swij_1.mch != 1) {
	swij_1.w[174] = swij_1.wm[174] / sallr_1.rt;
    }
    if (swij_1.ich != 10 || swij_1.jch != 13 || swij_1.mch != 1) {
	swij_1.w[189] = swij_1.wm[189] / sallr_1.rt;
    }

    if (swij_1.ich != 11 || swij_1.jch != 1 || swij_1.mch != 1) {
	swij_1.w[10] = swij_1.w[150];
    }
    if (swij_1.ich != 11 || swij_1.jch != 2 || swij_1.mch != 1) {
	swij_1.w[25] = swij_1.w[151];
    }
    if (swij_1.ich != 11 || swij_1.jch != 3 || swij_1.mch != 1) {
	swij_1.w[40] = swij_1.w[152];
    }
    if (swij_1.ich != 11 || swij_1.jch != 4 || swij_1.mch != 1) {
	swij_1.w[55] = swij_1.w[153];
    }
    if (swij_1.ich != 11 || swij_1.jch != 5 || swij_1.mch != 1) {
	swij_1.w[70] = swij_1.w[154];
    }
    if (swij_1.ich != 11 || swij_1.jch != 6 || swij_1.mch != 1) {
	swij_1.w[85] = swij_1.w[155];
    }
    if (swij_1.ich != 11 || swij_1.jch != 7 || swij_1.mch != 1) {
	swij_1.w[100] = swij_1.w[156];
    }
    if (swij_1.ich != 11 || swij_1.jch != 8 || swij_1.mch != 1) {
	swij_1.w[115] = swij_1.w[157];
    }
    if (swij_1.ich != 11 || swij_1.jch != 9 || swij_1.mch != 1) {
	swij_1.w[130] = swij_1.w[158];
    }
    if (swij_1.ich != 11 || swij_1.jch != 10 || swij_1.mch != 1) {
	swij_1.w[145] = swij_1.w[159];
    }
    if (swij_1.ich != 11 || swij_1.jch != 12 || swij_1.mch != 1) {
	swij_1.w[175] = swij_1.wm[175] / sallr_1.rt;
    }
    if (swij_1.ich != 11 || swij_1.jch != 13 || swij_1.mch != 1) {
	swij_1.w[190] = swij_1.wm[190] / sallr_1.rt;
    }

    if (swij_1.ich != 12 || swij_1.jch != 1 || swij_1.mch != 1) {
	swij_1.w[11] = swij_1.w[165];
    }
    if (swij_1.ich != 12 || swij_1.jch != 2 || swij_1.mch != 1) {
	swij_1.w[26] = swij_1.w[166];
    }
    if (swij_1.ich != 12 || swij_1.jch != 3 || swij_1.mch != 1) {
	swij_1.w[41] = swij_1.w[167];
    }
    if (swij_1.ich != 12 || swij_1.jch != 4 || swij_1.mch != 1) {
	swij_1.w[56] = swij_1.w[168];
    }
    if (swij_1.ich != 12 || swij_1.jch != 5 || swij_1.mch != 1) {
	swij_1.w[71] = swij_1.w[169];
    }
    if (swij_1.ich != 12 || swij_1.jch != 6 || swij_1.mch != 1) {
	swij_1.w[86] = swij_1.w[170];
    }
    if (swij_1.ich != 12 || swij_1.jch != 7 || swij_1.mch != 1) {
	swij_1.w[101] = swij_1.w[171];
    }
    if (swij_1.ich != 12 || swij_1.jch != 8 || swij_1.mch != 1) {
	swij_1.w[116] = swij_1.w[172];
    }
    if (swij_1.ich != 12 || swij_1.jch != 9 || swij_1.mch != 1) {
	swij_1.w[131] = swij_1.w[173];
    }
    if (swij_1.ich != 12 || swij_1.jch != 10 || swij_1.mch != 1) {
	swij_1.w[146] = swij_1.w[174];
    }
    if (swij_1.ich != 12 || swij_1.jch != 11 || swij_1.mch != 1) {
	swij_1.w[161] = swij_1.w[175];
    }
    if (swij_1.ich != 12 || swij_1.jch != 13 || swij_1.mch != 1) {
	swij_1.w[191] = swij_1.wm[191] / sallr_1.rt;
    }

    if (swij_1.ich != 13 || swij_1.jch != 1 || swij_1.mch != 1) {
	swij_1.w[12] = swij_1.w[180];
    }
    if (swij_1.ich != 13 || swij_1.jch != 2 || swij_1.mch != 1) {
	swij_1.w[27] = swij_1.w[181];
    }
    if (swij_1.ich != 13 || swij_1.jch != 3 || swij_1.mch != 1) {
	swij_1.w[42] = swij_1.w[182];
    }
    if (swij_1.ich != 13 || swij_1.jch != 4 || swij_1.mch != 1) {
	swij_1.w[57] = swij_1.w[183];
    }
    if (swij_1.ich != 13 || swij_1.jch != 5 || swij_1.mch != 1) {
	swij_1.w[72] = swij_1.w[184];
    }
    if (swij_1.ich != 13 || swij_1.jch != 6 || swij_1.mch != 1) {
	swij_1.w[87] = swij_1.w[185];
    }
    if (swij_1.ich != 13 || swij_1.jch != 7 || swij_1.mch != 1) {
	swij_1.w[102] = swij_1.w[186];
    }
    if (swij_1.ich != 13 || swij_1.jch != 8 || swij_1.mch != 1) {
	swij_1.w[117] = swij_1.w[187];
    }
    if (swij_1.ich != 13 || swij_1.jch != 9 || swij_1.mch != 1) {
	swij_1.w[132] = swij_1.w[188];
    }
    if (swij_1.ich != 13 || swij_1.jch != 10 || swij_1.mch != 1) {
	swij_1.w[147] = swij_1.w[189];
    }
    if (swij_1.ich != 13 || swij_1.jch != 11 || swij_1.mch != 1) {
	swij_1.w[162] = swij_1.w[190];
    }
    if (swij_1.ich != 13 || swij_1.jch != 12 || swij_1.mch != 1) {
	swij_1.w[177] = swij_1.w[191];
    }

    gamma2_(m, xn, t, p);
    goto L666;
/* -------------------------------------- */
/* C  IDEAL MIXING */
/* -------------------------------------- */
L555:
    i__1 = salli_1.ml[0];
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = salli_1.ml[0];
	for (j = 1; j <= i__2; ++j) {
	    swij_1.w[i__ + (j + 15) * 15 - 241] = 0.;
/* L333: */
	}
/* L444: */
    }
    gamma1_(m, xn, t, p);
    i__1 = salli_1.ml[*m - 1];
    for (i__ = salli_1.mf[*m - 1]; i__ <= i__1; ++i__) {
	sallr_1.aktfln[i__ - 1] -= log(*p);
/* L17: */
    }
L666:

    return 0;
} /* factor_ */

/* C */
/* Subroutine */ int interw_(integer *m, doublereal *t, doublereal *p, doublereal *v)
{
    /* Initialized data */

    static doublereal dgas[13] = { 2.65,3.76,3.565,3.76,3.109,2.96,3.,3.,
	    3.,3.,3.526,3.,3.317 };
    static doublereal egas[13] = { 380.,424.16,227.13,100.2,194.3,36.7,200.,
	    200.,200.,200.,139.2,200.,146.52 };
    static doublereal ugas[13] = { 1.85,0.,0.,0.,0.,0.,0.,1.61,0.,0.,0.,
	    0.,0. };
    static doublereal sgas[13] = { 1.59,2.65,2.6,1.95,1.6,.79,2.,3.72,2.,
	    2.,2.,2.,2. };

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2, d__3, d__4, d__5;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__, j;
    static doublereal aij[169]	/* was [13][13] */, bij[169]	/* was [13][
	    13] */, dij[169]	/* was [13][13] */, eij[169]	/* was [13][
	    13] */, rij[169]	/* was [13][13] */, uij[169]	/* was [13][
	    13] */, wii[13], agas[13], rgas[13], xgas[13], wmix[169]	/* 
	    was [13][13] */;

/* C */
/* ******************************************************************* */
/* *           INTERW IS A SUBROUTINE FOR THE CALCULATION            * */
/* *                 OF INTERACTION ENERGIES (WIJ)                   * */
/* *    BY USING THE KIHARA AND THE STOCKMAYER POTENTIEL FUNCTIONS.  * */
/* *                                                                 * */
/* *               REFERENCES: Tren & Lienhard (1971)                * */
/* *                           Prausnitz et al. (1986)               * */
/* *                           Reid (1987)                           * */
/* *                           Saxena & Fei (1988)                   * */
/* *                           Shi & Saxena (1992)                   * */
/* ******************************************************************* */
/* C */
/*      IMPLICIT DOUBLE PRECISION(A-H,O-Z) */
/*      DATA AGAS/0.0D0,0.615D0,0.283D0,0.0D0,0.308D0,0.0D0, */
/*     *          4*0.3D0, 0.250D0, 0.300D0, 0.121D0/ */
/* C */
    agas[0] = 0.;
    agas[1] = .615;
    agas[2] = .283;
    agas[3] = 0.;
    agas[4] = .308;
    agas[5] = 0.;
    agas[6] = .3;
    agas[7] = .3;
    agas[8] = .3;
    agas[9] = .3;
    agas[10] = .25;
    agas[11] = .3;
    agas[12] = .121;

    i__1 = salli_1.ml[*m - 1];
    for (i__ = salli_1.mf[*m - 1]; i__ <= i__1; ++i__) {
	agas[i__ - 1] = agas[i__ - 1] * dgas[i__ - 1] / (agas[i__ - 1] + 1.);
	d__1 = (doublereal) ugas[i__ - 1];
	d__2 = (doublereal) dgas[i__ - 1];
	xgas[i__ - 1] = pow_dd(&d__1, &c_b21) * pow_dd(&d__2, &c_b22) * egas[
		i__ - 1];
	d__1 = salla_1.vgas[i__ - 1] * 21. / 5.3002400000000002e25;
	rgas[i__ - 1] = pow_dd(&d__1, &c_b440) * 2e8;
	d__1 = (doublereal) ((dgas[i__ - 1] - agas[i__ - 1]) / (rgas[i__ - 1] 
		- agas[i__ - 1]));
	d__2 = (doublereal) ((dgas[i__ - 1] - agas[i__ - 1]) / (rgas[i__ - 1] 
		- agas[i__ - 1]));
	d__3 = (doublereal) rgas[i__ - 1];
	wii[i__ - 1] = sallr_1.rt * (egas[i__ - 1] * 4. * (pow_dd(&d__1, &
		c_b441) - pow_dd(&d__2, &c_b442)) - xgas[i__ - 1] / pow_dd(&
		d__3, &c_b22));
/* L5: */
    }

    i__1 = salli_1.ml[*m - 1];
    for (i__ = salli_1.mf[*m - 1]; i__ <= i__1; ++i__) {
	i__2 = salli_1.ml[*m - 1];
	for (j = salli_1.mf[*m - 1]; j <= i__2; ++j) {
	    if (i__ != j && i__ < j) {
		aij[i__ + j * 13 - 14] = (agas[i__ - 1] + agas[j - 1]) / 2.;
		d__1 = (doublereal) dgas[j - 1];
		d__2 = (doublereal) (egas[i__ - 1] / egas[j - 1]);
		bij[i__ + j * 13 - 14] = sgas[j - 1] / pow_dd(&d__1, &c_b22) *
			 ugas[i__ - 1] * pow_dd(&d__2, &c_b27) / 4. + 1.;
		d__1 = (doublereal) bij[i__ + j * 13 - 14];
		dij[i__ + j * 13 - 14] = pow_dd(&d__1, &c_b447) * (dgas[i__ - 
			1] + dgas[j - 1]) / 2.;
		d__1 = (doublereal) (egas[i__ - 1] * egas[j - 1]);
		eij[i__ + j * 13 - 14] = pow_dd(&d__1, &c_b27);
		d__1 = (doublereal) (ugas[i__ - 1] * ugas[j - 1]);
		uij[i__ + j * 13 - 14] = pow_dd(&d__1, &c_b27);
		rij[i__ + j * 13 - 14] = (rgas[i__ - 1] + rgas[j - 1]) / 2.;
		d__1 = (doublereal) ((dij[i__ + j * 13 - 14] - aij[i__ + j * 
			13 - 14]) / (rij[i__ + j * 13 - 14] - aij[i__ + j * 
			13 - 14]));
		d__2 = (doublereal) ((dij[i__ + j * 13 - 14] - aij[i__ + j * 
			13 - 14]) / (rij[i__ + j * 13 - 14] - aij[i__ + j * 
			13 - 14]));
		d__3 = (doublereal) uij[i__ + j * 13 - 14];
		d__4 = (doublereal) dij[i__ + j * 13 - 14];
		d__5 = (doublereal) rij[i__ + j * 13 - 14];
		wmix[i__ + j * 13 - 14] = sallr_1.rt * (eij[i__ + j * 13 - 14]
			 * 4. * (pow_dd(&d__1, &c_b441) - pow_dd(&d__2, &
			c_b442)) - pow_dd(&d__3, &c_b21) * eij[i__ + j * 13 - 
			14] * pow_dd(&d__4, &c_b22) / pow_dd(&d__5, &c_b22));
		swij_1.wm[i__ + j * 15 - 16] = (wmix[i__ + j * 13 - 14] * 2. 
			- wii[i__ - 1] - wii[j - 1]) / (*t * 2.);
	    }
/* L3: */
	}
    }
/* L7: */

    return 0;
} /* interw_ */

/* C */
/* Subroutine */ int gamma2_(integer *m, doublereal *xn, doublereal *t, doublereal *p)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__, j, k;
    static doublereal q1, q2, x1, x2;
    static integer ia, ja, ka;
    static doublereal temp, term, temp1, temp2;

/* C */
/* ******************************************************************* */
/* *           GAMME2 IS A SUBROUTINE FOR THE CALCULATION            * */
/* *           OF ACTIVITIES FOR NON-IDEAL MIXING SPECIES            * */
/* *                  IN 13-COMPONENT SYSTEM:                        * */
/* *          H2O-CO2-CH4-CO-O2-H2-S2-SO2-COS-H2S-N2-NH3-Ar.         * */
/* *                                                                 * */
/* *    1. THE BINARY SOLUTION MODEL IS VAN LA FORMULATION.          * */
/* *    2. THE KOHLER MODEL HAS BEEN USED TO COMPUTE ACTIVITIES      * */
/* *             IN A MULTICOMPONENT SYSTEM.                         * */
/* ******************************************************************* */
/* C */
/*      IMPLICIT DOUBLE PRECISION(A-H,O-Z) */

    i__1 = salli_1.ml[*m - 1];
    for (i__ = salli_1.mf[*m - 1]; i__ <= i__1; ++i__) {
	sallr_1.aktfln[i__ - 1] = 0.;
	i__2 = salli_1.ml[*m - 1];
	for (j = salli_1.mf[*m - 1]; j <= i__2; ++j) {
	    if (j != i__ && sallr_1.x[j - 1] > 0.) {
		if (sallr_1.x[i__ - 1] > 0.) {
		    temp = sallr_1.x[i__ - 1] + sallr_1.x[j - 1];
		    x1 = sallr_1.x[i__ - 1] / temp;
		    x2 = 1. - x1;
		    term = salla_1.vgas[i__ - 1] + salla_1.vgas[j - 1];
		    q1 = salla_1.vgas[i__ - 1] * 5. / term;
		    q2 = 5. - q1;
		    ia = i__ - salli_1.mf[*m - 1] + 1;
		    ja = j - salli_1.mf[*m - 1] + 1;
		    temp1 = swij_1.w[ia + (ja + *m * 15) * 15 - 241] * 2. * 
			    x1 * x2 * q1 * q2 / (x1 * q1 + x2 * q2);
		    d__1 = (doublereal) (q1 * x1 / (q2 * x2) + 1.);
		    temp2 = swij_1.w[ia + (ja + *m * 15) * 15 - 241] * 2. * 
			    q1 / pow_dd(&d__1, &c_b21);
		    sallr_1.aktfln[i__ - 1] += temp * (temp1 * (1. - temp) + 
			    temp2);
		}
		if (j < salli_1.ml[*m - 1]) {
		    i__3 = salli_1.ml[*m - 1];
		    for (k = j + 1; k <= i__3; ++k) {
			if (k != i__ && sallr_1.x[k - 1] > 0.) {
			    temp = sallr_1.x[j - 1] + sallr_1.x[k - 1];
			    x1 = sallr_1.x[j - 1] / temp;
			    x2 = 1. - x1;
			    term = salla_1.vgas[j - 1] + salla_1.vgas[k - 1];
			    q1 = salla_1.vgas[j - 1] * 5. / term;
			    q2 = 5. - q1;
			    ka = k - salli_1.mf[*m - 1] + 1;
			    temp1 = swij_1.w[ja + (ka + *m * 15) * 15 - 241] *
				     2. * x1 * x2 * q1 * q2 / (x1 * q1 + x2 *
				     q2);
			    sallr_1.aktfln[i__ - 1] -= temp * temp * temp1;
			}
/* L9: */
		    }
		}
	    }
/* L8: */
	}
    }

    return 0;
} /* gamma2_ */

/* C */
/* Subroutine */ int gamma1_(integer *m, doublereal *xn, doublereal *t, doublereal *p)
{
    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Local variables */
    static integer i__, j, k;
    static doublereal x1, x2;
    static integer ia, ja, ka;
    static doublereal temp, temp1, temp2;

/* C */
/* ******************************************************************* */
/* *           GAMME1 IS A SUBROUTINE FOR THE CALCULATION            * */
/* *             OF ACTIVITIES FOR IDEAL MIXING SPECIES              * */
/* *                  IN 13-COMPONENT SYSTEM:                        * */
/* *          H2O-CO2-CH4-CO-O2-H2-S2-SO2-COS-H2S-N2-NH3-Ar.         * */
/* *                                                                 * */
/* ******************************************************************* */
/* C */
/*      IMPLICIT DOUBLE PRECISION(A-H,O-Z) */

    i__1 = salli_1.ml[*m - 1];
    for (i__ = salli_1.mf[*m - 1]; i__ <= i__1; ++i__) {
	sallr_1.aktfln[i__ - 1] = 0.;
	i__2 = salli_1.ml[*m - 1];
	for (j = salli_1.mf[*m - 1]; j <= i__2; ++j) {
	    if (j != i__ && sallr_1.x[j - 1] > 0.) {
		if (sallr_1.x[i__ - 1] > 0.) {
		    temp = sallr_1.x[i__ - 1] + sallr_1.x[j - 1];
		    x1 = sallr_1.x[i__ - 1] / temp;
		    x2 = 1. - x1;
		    ia = i__ - salli_1.mf[*m - 1] + 1;
		    ja = j - salli_1.mf[*m - 1] + 1;
		    temp1 = swij_1.w[ia + (ja + *m * 15) * 15 - 241] * x2 + 
			    swij_1.w[ja + (ia + *m * 15) * 15 - 241] * x1;
		    temp2 = swij_1.w[ia + (ja + *m * 15) * 15 - 241] + x1 * 
			    2. * (swij_1.w[ja + (ia + *m * 15) * 15 - 241] - 
			    swij_1.w[ia + (ja + *m * 15) * 15 - 241]);
		    sallr_1.aktfln[i__ - 1] += temp * x2 * (temp1 * x1 * (1. 
			    - temp) + temp2 * x2);
		}
		if (j < salli_1.ml[*m - 1]) {
		    i__3 = salli_1.ml[*m - 1];
		    for (k = j + 1; k <= i__3; ++k) {
			if (k != i__ && sallr_1.x[k - 1] > 0.) {
			    temp = sallr_1.x[j - 1] + sallr_1.x[k - 1];
			    x1 = sallr_1.x[j - 1] / temp;
			    x2 = 1. - x1;
			    ka = k - salli_1.mf[*m - 1] + 1;
			    temp1 = swij_1.w[ja + (ka + *m * 15) * 15 - 241] *
				     x2 + swij_1.w[ka + (ja + *m * 15) * 15 - 
				    241] * x1;
			    sallr_1.aktfln[i__ - 1] -= temp * temp * temp1 * 
				    x1 * x2;
			}
/* L2: */
		    }
		}
	    }
/* L1: */
	}
    }

    return 0;
} /* gamma1_ */

