/* tolja.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static doublereal c_b10 = .333333333;

/* Subroutine */ int tolja_(doublereal *x, doublereal *t, doublereal *p, doublereal *v, doublereal *gdivp)
{
    /* Initialized data */

    static doublereal v0meg[13] = { 6.65,10.94,10.46,9.46,7.97,3.92,7.19,
	    10.92,14.22,11.,9.,8.16,7.77 };
    static doublereal v0fif[13] = { 12.4,20.8,20.17,18.39,15.5,8.8,14.4,
	    20.8,27.2,20.8,18.,15.3,15.4 };

    static integer i__;
    static doublereal p5, v0, v5;
    extern /* Subroutine */ int nr_(U_fp, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal eps;
    extern /* Subroutine */ int vdp_(U_fp, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    extern /* Subroutine */ int tvpm_();
    static doublereal vdpint;

/* C */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*        CALCULATION OF ENTHALPY, ENTROPY, HEAT CAPACITY,              C */
/*                         GIBBS FREE ENERGY, (MU0/RT),                 C */
/*                            ACTIVITY AND FUGACITY                     C */
/*                  FOR A FLUID MIXTURE WITH COMPOSITION X              C */
/*                           AT P (bar) AND T (K)                       C */
/*                                                                      C */
/*        ****        when pressure is higher than 5 kbar.              C */
/*                                                                      C */
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ C */
/*                                                                      C */
/*             Anatoly B. Benoloshko,  and  Surendra K. Saxena          C */
/*             ---------------------        ------------------          C */
/*                     Planetary Geochemistry                           C */
/*                     Uppsala University                               C */
/*                     Uppsala                                          C */
/*                     SWEDEN                                           C */
/*                                                                      C */
/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ C */
/*                                                                      C */
/* C  Fluid Model:                                                       C */
/*      C-H-O-S-N-Ar One-Fluid Model:                                   C */
/*                        Belonoshko-Saxena (1991a)                     C */
/*                        Belonoshko-Saxena (1992b)                     C */
/*                        Belonoshko (1992)                             C */
/*                        Belonoshko-Saxena (1992)                      C */
/*                        Belonoshko-Shi-Saxena (1992)                  C */
/*                                                                      C */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* C */
    /* Parameter adjustments */
    --x;

    /* Function Body */

    eps = 1e-5;
    v0 = 20.;
    p5 = 5e3;
    nr_((U_fp)tvpm_, &eps, &x[1], t, &p5, &v0, &v5);
    if (*p <= 5e4) {
	v0 = 0.;
	for (i__ = 1; i__ <= 13; ++i__) {
/* L1: */
	    v0 += x[i__] * v0fif[i__ - 1];
	}
    }
    if (*p > 5e4) {
	v0 = 0.;
	for (i__ = 1; i__ <= 13; ++i__) {
/* L2: */
	    v0 += x[i__] * v0meg[i__ - 1];
	}
    }
    nr_((U_fp)tvpm_, &eps, &x[1], t, p, &v0, v);
    vdp_((U_fp)tvpm_, &eps, &x[1], t, &v5, v, &vdpint);
    *gdivp = vdpint;

    return 0;
} /* tolja_ */

/* CC */
/* Subroutine */ int nr_(S_fp funct, doublereal *eps, doublereal *x, doublereal *t, doublereal *p, 
	doublereal *v0, doublereal *v)
{
    /* System generated locals */
    doublereal r__1;

    /* Local variables */
    static doublereal pj, vj, rt, vj1, vid, pjs, ptrue;
    extern /* Subroutine */ int functs_(S_fp, doublereal *, doublereal *, doublereal *, doublereal *);


    /* Parameter adjustments */
    --x;

    /* Function Body */
    rt = *t * 8.31451;
    vid = rt / *p * 10.;
    vj = *v0;
    ptrue = *p;
L1:
    (*funct)(&x[1], t, &vj, &pj);
    functs_((S_fp)funct, &x[1], t, &vj, &pjs);
    vj1 = (ptrue - pj) / pjs + vj;
    if ((r__1 = vj1 - vj, dabs(r__1)) > 50.) {
	*v = vid;
	return 0;
    }
    if ((r__1 = (vj - vj1) / vj1, dabs(r__1)) < *eps) {
	*v = vj1;
	return 0;
    } else {
	vj = vj1;
	goto L1;
    }

    return 0;
} /* nr_ */

/* CC */
/* Subroutine */ int functs_(S_fp funct, doublereal *x, doublereal *t, doublereal *v, doublereal *ps)
{
    static doublereal dv, pm, pp, vm, vp;


    /* Parameter adjustments */
    --x;

    /* Function Body */
    dv = *v * .001;
    vm = *v - dv;
    vp = *v + dv;
    (*funct)(&x[1], t, &vm, &pm);
    (*funct)(&x[1], t, &vp, &pp);
    *ps = (pp - pm) / 2. / dv;

    return 0;
} /* functs_ */

/* CC */
/* Subroutine */ int ase_(doublereal *x, doublereal *alx, doublereal *sgmx, doublereal *epskx)
{
    /* Initialized data */

    static doublereal alij[169]	/* was [13][13] */ = { 12.75,13.31,13.38,
	    13.59,13.57,13.04,12.72,12.99,13.07,13.11,13.,13.1,
	    12.87,13.31,13.9,13.97,14.19,14.17,13.62,13.28,13.57,
	    13.65,13.68,13.58,13.67,13.44,13.38,13.97,14.05,14.26,
	    14.25,13.69,13.35,13.64,13.72,13.76,13.65,13.75,13.51,
	    13.59,14.19,14.26,14.48,14.46,13.9,13.56,13.85,13.93,
	    13.97,13.86,13.96,13.72,13.57,14.17,14.25,14.46,14.45,
	    13.88,13.54,13.83,13.92,13.95,13.84,13.94,13.71,13.04,
	    13.62,13.69,13.9,13.88,13.34,13.01,13.29,13.37,13.4,
	    13.3,13.39,13.17,12.72,13.28,13.35,13.56,13.54,13.01,
	    12.69,12.96,13.04,13.07,12.97,13.06,12.84,12.99,13.57,
	    13.64,13.85,13.83,13.29,12.96,13.24,13.32,13.36,13.25,
	    13.35,13.12,13.07,13.65,13.72,13.93,13.92,13.37,13.04,
	    13.32,13.4,13.43,13.33,13.42,13.2,13.11,13.68,13.76,
	    13.97,13.95,13.4,13.07,13.36,13.43,13.47,13.36,13.46,
	    13.23,13.,13.58,13.65,13.86,13.84,13.3,12.97,13.25,
	    13.33,13.36,13.26,13.35,13.13,13.1,13.67,13.75,13.96,
	    13.94,13.39,13.06,13.35,13.42,13.46,13.35,13.45,13.22,
	    12.87,13.44,13.51,13.72,13.71,13.17,12.84,13.12,13.2,
	    13.23,13.13,13.22,13. };
    static doublereal epskij[169]	/* was [13][13] */ = { 446.7,297.9,250.9,
	    201.4,210.8,106.,220.7,343.1,333.4,348.9,218.8,362.2,
	    233.4,297.9,198.6,167.3,134.3,140.6,70.7,147.1,228.8,
	    222.4,232.6,145.9,241.5,155.7,250.9,167.3,140.9,113.1,
	    118.4,59.5,123.9,192.7,187.3,196.,122.9,203.4,131.1,
	    201.4,134.3,113.1,90.8,95.1,47.8,99.5,154.7,150.3,157.3,
	    98.7,163.3,105.3,210.8,140.6,118.4,95.1,99.5,50.,104.1,
	    161.9,157.4,164.7,103.3,170.9,110.2,106.,70.7,59.5,47.8,
	    50.,25.1,52.4,81.4,79.1,82.8,51.9,85.9,55.4,220.7,
	    147.1,123.9,99.5,104.1,52.4,109.,169.5,164.7,172.3,
	    108.1,178.9,115.3,343.1,228.8,192.7,154.7,161.9,81.4,
	    169.5,263.5,256.1,268.,168.1,278.1,179.3,333.4,222.4,
	    187.3,150.3,157.4,79.1,164.7,256.1,248.9,260.4,163.3,
	    270.3,174.3,348.9,232.6,196.,157.3,164.7,82.8,172.3,
	    268.,260.4,272.5,170.9,282.8,182.3,218.8,145.9,122.9,
	    98.7,103.3,51.9,108.1,168.1,163.3,170.9,107.2,177.4,
	    114.4,362.2,241.5,203.4,163.3,170.9,85.9,178.9,278.1,
	    270.3,282.8,177.4,293.6,189.3,233.4,155.7,131.1,105.3,
	    110.2,55.4,115.3,179.3,174.3,182.3,114.4,189.3,122. };
    static doublereal sgmij[169]	/* was [13][13] */ = { 2.844,3.27,3.28,
	    3.249,3.106,2.911,3.103,3.279,3.5,3.267,3.265,3.039,
	    3.138,3.27,3.696,3.706,3.675,3.533,3.337,3.53,3.705,
	    3.926,3.693,3.691,3.465,3.564,3.28,3.706,3.717,3.685,
	    3.543,3.347,3.54,3.715,3.936,3.703,3.701,3.475,3.574,
	    3.249,3.675,3.685,3.653,3.511,3.316,3.508,3.683,3.904,
	    3.671,3.669,3.444,3.542,3.106,3.533,3.543,3.511,3.369,
	    3.173,3.366,3.541,3.762,3.529,3.527,3.301,3.4,2.911,
	    3.337,3.347,3.316,3.173,2.978,3.17,3.346,3.567,3.334,
	    3.332,3.106,3.204,3.103,3.53,3.54,3.508,3.366,3.17,
	    3.363,3.538,3.759,3.526,3.524,3.299,3.397,3.279,3.705,
	    3.715,3.683,3.541,3.346,3.538,3.713,3.934,3.702,3.699,
	    3.474,3.572,3.5,3.926,3.936,3.904,3.762,3.567,3.759,
	    3.934,4.155,3.922,3.92,3.695,3.793,3.267,3.693,3.703,
	    3.671,3.529,3.334,3.526,3.702,3.922,3.69,3.688,3.462,
	    3.56,3.265,3.691,3.701,3.669,3.527,3.332,3.524,3.699,
	    3.92,3.688,3.685,3.46,3.558,3.039,3.465,3.475,3.444,
	    3.301,3.106,3.299,3.474,3.695,3.462,3.46,3.234,3.333,
	    3.138,3.564,3.574,3.542,3.4,3.204,3.397,3.572,3.793,
	    3.56,3.558,3.333,3.431 };

    /* System generated locals */
    doublereal r__1;
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__, j;
    static doublereal ax, bx, cx, xex, xxs3;



    /* Parameter adjustments */
    --x;

    /* Function Body */
/* C */

    ax = 0.;
    bx = 0.;
    cx = 0.;
    xex = 1e-8;
    for (i__ = 1; i__ <= 13; ++i__) {
	if ((r__1 = x[i__], dabs(r__1)) <= xex) {
	    goto L3;
	}
	for (j = 1; j <= 13; ++j) {
	    if ((r__1 = x[j], dabs(r__1)) <= xex) {
		goto L4;
	    }
/* Computing 3rd power */
	    r__1 = sgmij[i__ + j * 13 - 14];
	    xxs3 = x[i__] * x[j] * (r__1 * (r__1 * r__1));
	    ax += xxs3 * epskij[i__ + j * 13 - 14];
	    bx += xxs3;
	    cx += xxs3 * alij[i__ + j * 13 - 14] * epskij[i__ + j * 13 - 14];
L4:
	    ;
	}
L3:
	;
    }

    d__1 = (doublereal) bx;
    *sgmx = pow_dd(&d__1, &c_b10);
    *epskx = ax / bx;
    *alx = cx / ax;

    return 0;
} /* ase_ */

/* CC */
/* Subroutine */ int tvpm_(doublereal *x, doublereal *t, doublereal *v, doublereal *p)
{
    /* Initialized data */

    static doublereal xc[29] = { .49379340772561688,1.77136719000011591,
	    -1.24397358740699658,-8.22738223585147906,1.26639755360917096,
	    1.71431494383712232,18.857674009587136,-.64967289865577738,
	    1.10631892859961082,3.43201986557894275,-11.61223156310191462,
	    -24.0910798733673468,7.15468164992105906,4.35243253136828275,
	    7.40801022796371711,-.43490428159049076,-5.05471913647956932,
	    -8.41696486054619399,2.81828771146679119,-5.20493168328355048,
	    2.65003464989916641,-1.17589498191260817,1.0091147682615068,
	    1.18264255424103514,.1021732463251438182,-.63676820398636927,
	    .60142122204215066,3.95204218076118927,-15.6392006408415389 };

    /* System generated locals */
    doublereal r__1, r__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal a, b, c__, d__, e, f, g, pc, ti, vi, ti2, ti3, ali, alk;
    extern /* Subroutine */ int ase_(doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal alx, ti100, ti1000, sgmx, sgmx3, edeps, epskx, pcoeff, tcoeff,
	     vcoeff;

    /* Parameter adjustments */
    --x;

    /* Function Body */

    ase_(&x[1], &alx, &sgmx, &epskx);
    edeps = 1. / epskx;
/* Computing 3rd power */
    r__1 = sgmx;
    sgmx3 = r__1 * (r__1 * r__1);
    pcoeff = sgmx3 * .007242759946166401 * edeps;
    tcoeff = edeps;
    vcoeff = 1.6605778811026237 / sgmx3;

    ti = *t * tcoeff;
    ti2 = ti * ti;
    ti3 = ti2 * ti;
    vi = *v * vcoeff;
    ali = alx;
    ti100 = ti2 / 100.;
    ti1000 = ti3 / 1e4;

    a = xc[0] + xc[1] * ti + xc[2] * ti100 + xc[14] * ti1000;
    b = xc[3] + xc[4] * ti + xc[5] * ti100 + xc[15] * ti1000;
    c__ = xc[6] + xc[7] * ti + xc[8] * ti100 + xc[16] / 1e5 * ti3;
    f = xc[17] + xc[18] * ti + xc[19] * ti100 + xc[20] * ti1000;
    g = xc[27] / 10. + xc[28] / 100. * ti;
    d__ = xc[9] / 10 + xc[10] / 1000 * ti + xc[21] / ti + xc[23] / 10 * vi + 
	    xc[24] / vi / 10;
    e = xc[11] / 100 + xc[12] / 1000 * ti + xc[22] / ti + xc[25] / 10 * vi + 
	    xc[26] / vi / 10;

/* Computing 2nd power */
    r__1 = vi;
/* Computing 3rd power */
    r__2 = vi;
    d__1 = (doublereal) vi;
    d__2 = (doublereal) xc[13];
    pc = a / (vi - g) + b / (r__1 * r__1) + f / (r__2 * (r__2 * r__2)) + c__ /
	     pow_dd(&d__1, &d__2);
/* Computing 2nd power */
    r__1 = ali - 12.75;
    alk = d__ * (ali - 12.75) + 1. + e * (r__1 * r__1);
    pc *= alk;
    *p = pc / pcoeff;

    return 0;
} /* tvpm_ */

/* CC */
/* Subroutine */ int vdp_(S_fp funct, doublereal *eps, doublereal *x, doublereal *t, doublereal *vst, 
	doublereal *vfin, doublereal *vdpint)
{
    static doublereal s1, pst, pfin;
    extern /* Subroutine */ int flint_(doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal pvintf, pvints;


    /* Parameter adjustments */
    --x;

    /* Function Body */
    (*funct)(&x[1], t, vfin, &pfin);
    (*funct)(&x[1], t, vst, &pst);
/*                VDPINT = (PFIN*VFIN -PST*VST + S1)/10.0 */
    flint_(&x[1], t, vfin, &pvintf);
    flint_(&x[1], t, vst, &pvints);
    s1 = pvints - pvintf;
    *vdpint = (pfin * *vfin - pst * *vst + s1) / 10.;

    return 0;
} /* vdp_ */

/* CC */
/* Subroutine */ int flint_(doublereal *x, doublereal *t, doublereal *v, doublereal *pvint)
{
    /* Initialized data */

    static doublereal xc[29] = { .93505310752561688,1.73699892000011591,
	    -1.30975098740699658,-9.14208223585147906,1.12375121360917096,
	    1.94532994383712232,18.052706684587136,-.60332346345947818,
	    .97658909559961082,3.57911846557894275,-9.81360148740191462,
	    -22.7287168733673468,6.22413763992105906,4.38140919236828275,
	    4.85395992796371711,-.57662210159049076,-4.11150218637956932,
	    -6.64748141694619399,2.71569335746679119,-4.78315896838355048,
	    2.18540232889916641,-1.03805953902260817,.9153738884315068,
	    .90857123024103514,-.0922267363251438182,-.60401350198636927,
	    .64619486687215066,2.89574909131718927,-11.3443869684011389 };

    /* System generated locals */
    doublereal r__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    double log(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal a, b, c__, f, g, a1, a2, a3, b1, b2, b3, f1, f2, f3, c1, c2, 
	    c3, am, dt, et, ti, x24, vi, x25, x26, x27, ai1, ai2, ai3, al1, 
	    ti2, ti3, al12, ali;
    extern /* Subroutine */ int ase_(doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal avi, alx, vig, avig, edvi, sgmx, edvi2, edvi3, edvi4, aicom, 
	    secnd, third, first, epskx, pcoeff, tcoeff, vcoeff;

    /* Parameter adjustments */
    --x;

    /* Function Body */

    ase_(&x[1], &alx, &sgmx, &epskx);
/* Computing 3rd power */
    r__1 = sgmx;
    pcoeff = r__1 * (r__1 * r__1) * .007242759946166401 / epskx;
    tcoeff = 1. / epskx;
/* Computing 3rd power */
    r__1 = sgmx;
    vcoeff = 1.6605778811026237 / (r__1 * (r__1 * r__1));

    ti = *t * tcoeff;
    ti2 = ti * ti;
    ti3 = ti2 * ti;
    vi = *v * vcoeff;
    ali = alx;

    x24 = xc[23] / 10.;
    x25 = xc[24] / 10.;
    x26 = xc[25] / 10.;
    x27 = xc[26] / 10.;
    al1 = ali - 12.75;

    a = xc[0] + xc[1] * ti + xc[2] / 100. * ti2 + xc[14] / 1e4 * ti3;
    b = xc[3] + xc[4] * ti + xc[5] / 100. * ti2 + xc[15] / 1e4 * ti3;
    c__ = xc[6] + xc[7] * ti + xc[8] / 100. * ti2 + xc[16] / 1e5 * ti3;
    f = xc[17] + xc[18] * ti + xc[19] / 100. * ti2 + xc[20] / 1e4 * ti3;
    g = xc[27] / 10. + xc[28] / 100. * ti;
    dt = xc[9] / 10 + xc[10] / 1000 * ti + xc[21] / ti;
    et = xc[11] / 100 + xc[12] / 1000 * ti + xc[22] / ti;

/* Computing 2nd power */
    r__1 = al1;
    al12 = r__1 * r__1;
    first = dt * al1 + 1. + et * al12;
    secnd = x24 * al1 + x26 * al12;
    third = x25 * al1 + x27 * al12;
    vig = vi - g;
    avi = log(vi);
    avig = log(vig);
    edvi = 1. / vi;
/* Computing 2nd power */
    r__1 = edvi;
    edvi2 = r__1 * r__1;
    edvi3 = edvi2 * edvi;
    edvi4 = edvi3 * edvi;

    a1 = a * avig;
    a2 = a * (vi + g * avig);
    a3 = a / g * (avig - avi);

    b1 = -b * edvi;
    b2 = b * avi;
    b3 = b * -.5 * edvi2;

    f1 = f * -.5 * edvi2;
    f2 = -f * edvi;
    f3 = -f / 3. * edvi3;

    am = xc[13];
    d__1 = (doublereal) vi;
    d__2 = (doublereal) (1. - am);
    c1 = c__ / (1. - am) * pow_dd(&d__1, &d__2);
    d__1 = (doublereal) vi;
    d__2 = (doublereal) (2. - am);
    c2 = c__ / (2. - am) * pow_dd(&d__1, &d__2);
    d__1 = (doublereal) vi;
    d__2 = (doublereal) (-am);
    c3 = -c__ / am * pow_dd(&d__1, &d__2);

    ai1 = (a1 + b1 + f1 + c1) * first;
    ai2 = (a2 + b2 + f2 + c2) * secnd;
    ai3 = (a3 + b3 + f3 + c3) * third;

    aicom = ai1 + ai2 + ai3;

    *pvint = aicom / (pcoeff * vcoeff);

    return 0;
} /* flint_ */

