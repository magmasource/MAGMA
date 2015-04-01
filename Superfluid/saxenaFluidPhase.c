#include "silmin.h"
#include "recipes.h"
#include <signal.h>

#define FILE_TIME_STAMP_BUFFER_SIZE 30

static char fileTimeStamp[FILE_TIME_STAMP_BUFFER_SIZE];

const char *saxenaFluidPhase_ver(void) {
    strncpy(fileTimeStamp, __BASE_FILE__, FILE_TIME_STAMP_BUFFER_SIZE);
    strncat(fileTimeStamp, __TIMESTAMP__, FILE_TIME_STAMP_BUFFER_SIZE - strlen(fileTimeStamp) - 1);
    return fileTimeStamp;
}

#define SQUARE(x) ((x)*(x))
#define CUBE(x)   ((x)*(x)*(x))
#define QUARTIC(x) ((x)*(x)*(x)*(x))

/*
 * Model of C-H-O-S-N-Ar Supercritical Fluid System
 * Belonoshko, Shi, Fei, Saxena
 * Based on the FORTRAN program SUPERFLUID
 */

// Basis species [NA] = (0) H2O (1) CO2 (2) N2 (3) O2 (4) S2 (5) Ar
// Dependent species [NS] =
// (0) CH4 = 2H2O + CO2 - 2 O2
// (1) CO = CO2 - 1/2 O2
// (2) H2 = H2O - 1/2 O2
// (3) SO2 = 1/2 S2 + O2
// (4) COS = CO2 + 1/2 S2 - 1/2 O2
// (5) H2S = H2O + 1/2 S2 - 1/2 O2
// (6) NH3 = 1/2 N2 + 3/2 H2O - 3/4 O2

#define NA          6
#define NS          7
#define NY          0

#define NT         (NS+NY)
#define NR         (NA-1)
#define NE         (NA+NT)
#define FR0(i)     (i == 1) ? 1.0 - r[0] : - r[0]
#define DFR0DR0(i) - 1.0

#define R          8.3143

#define MAX_ITER 200  /* Maximum number of iterations allowed in order */

static char *listOfSpecies[13] = {
    "H2O", "CO2", "N2", "O2", "S2", "Ar", "CH4", "CO", "H2", "SO2", "COS", "H2S", "NH3"
};

static int *saxenaOrdering[13] = {
  0, 1, 10, 4, 6, 12, 2, 3, 5, 7, 8, 9, 11
};

static double xSpecies[NE];               /* Mole fractions of endmember species                                     */
static double dxSpeciesdr[NE][NR];        /* d(xSpecies)/dr                                                          */
static double dxSpeciesds[NE][NS];        /* d(xSpecies)/ds                                                          */
static double d2xSpeciesdrds[NE][NR][NS]; /* d2(xSpecies)/drds                                                       */
static double nSpecies;                   /* Total moles of all solution species relative to 1 mole of basis species */
static double dnSpeciesds[NS];            /* d(nSpecies)/ds                                                          */
static double d2nSpeciesds2[NS][NS];      /* d2(nSpecies)/ds2                                                        */
static double d3nSpeciesds3[NS][NS][NS];  /* d3(nSpecies)/ds3                                                        */

static int rANDsTOx (double r[NR], double s[NT]) {
    static double tolerance;
    double rSum, coeff, dcoeffds[NS], denom, dDenomds[NS];
    int i, j, k, okay = TRUE;
    
    for (i=0, rSum=0.0; i<NR; i++) rSum += r[i];
    
    coeff = 1.0 - s[1]/2.0 - s[2]/2.0 + s[3]/2.0 + s[6]/4.0;
    dcoeffds[0] =  0.0;
    dcoeffds[1] = -1.0/2.0;
    dcoeffds[2] = -1.0/2.0;
    dcoeffds[3] =  1.0/2.0;
    dcoeffds[4] =  0.0;
    dcoeffds[5] =  0.0;
    dcoeffds[6] =  1.0/4.0;
    
    /* xSpecies */
    xSpecies[ 0] = 1.0 - rSum*coeff;                   /* H2O   */
    for (i=0; i<NR; i++) xSpecies[ i+1] = r[i]*coeff;  /* basis */
    for (i=0; i<NS; i++) xSpecies[NA+i] = s[i];        /* depen */
    
    xSpecies[0] += - 2.0*s[0] - s[1]/2.0 - 3.0*s[2]/2.0 + s[3]/2.0 - s[5] - 5.0*s[6]/4.0;       // special case H2O
    xSpecies[1] += - s[0] - s[1] - s[4];                                                        // special case CO2
    xSpecies[2] += - s[6]/2.0;                                                                  // special case N2
    xSpecies[3] += 2.0*s[0] +  s[1]/2.0 + s[2]/2.0 - s[3] + s[4]/2.0 + s[5]/2.0 + 3.0*s[6]/4.0; // special case O2
    xSpecies[4] += - s[3]/2.0 - s[4]/2.0 - s[5]/2.0;                                            // special case S2
    
    /* Catch bad input data */
    for (i=0;  i<NE; i++) okay &= (xSpecies[i] >= 0.0);
    if (!okay) return okay;
    
    for (i=NS; i<NT; i++) okay &= ((s[i] > (10.0*DBL_EPSILON)) && (s[i] < (1.0-10.0*DBL_EPSILON)));
    if (okay && (NT > NS)) {
        double yIV = 1.0;
        for (i=NS; i<NT; i++) yIV -= s[i];
        okay &= ((yIV > (10.0*DBL_EPSILON)) && (yIV < (1.0-10.0*DBL_EPSILON)));
    }
    if (!okay) return okay;
    
    /* Correct roundoff problems - removed check on 4/10/02 when MgO species was included */
    if (tolerance == 0.0) tolerance = pow(DBL_EPSILON, (double) (2.0/3.0));
    /*  for (i=0; i<(NA+NS); i++) if (fabs(xSpecies[i]) < tolerance) xSpecies[i] = 0.0; */
    
    /* d xSpecies / dr */
    for (i=0; i<NR; i++) {
        dxSpeciesdr[  0][i] = - coeff;  /* SiO2  */
        dxSpeciesdr[i+1][i] =   coeff;  /* other */
    }
    
    /* d xSpecies / ds */
    for (i=0; i<NS; i++) {
        dxSpeciesds[   0][i] = - rSum*dcoeffds[i]; /* SiO2  */
        for (j=0; j<NR; j++) dxSpeciesds[ j+1][i] =   r[j]*dcoeffds[i]; /* basis */
        dxSpeciesds[NA+i][i] = 1.0;                /* depen */
    }
    
    dxSpeciesds[0][0] +=  2.0;     dxSpeciesds[0][1] += -1.0/2.0; dxSpeciesds[0][2] += -3.0/2.0; dxSpeciesds[0][3] +=  1.0/2.0;
    dxSpeciesds[0][4] +=  0.0;     dxSpeciesds[0][5] += -1.0;     dxSpeciesds[0][6] += -5.0/4.0;                                // special case H2O
    dxSpeciesds[1][0] +=  1.0;     dxSpeciesds[1][1] += -1.0;     dxSpeciesds[1][4] += -1.0;                                    // special case CO2
    dxSpeciesds[2][6] += -1.0/2.0;                                                                                              // special case N2
    dxSpeciesds[3][0] +=  2.0;     dxSpeciesds[3][1] +=  1.0/2.0; dxSpeciesds[3][2] +=  1.0/2.0; dxSpeciesds[3][3] += -1.0;
    dxSpeciesds[3][4] +=  1.0/2.0; dxSpeciesds[3][5] +=  1.0/2.0; dxSpeciesds[3][6] +=  3.0/4.0;                                // special case O2
    dxSpeciesds[4][3] += -1.0/2.0; dxSpeciesds[4][4] += -1.0/2.0; dxSpeciesds[4][5] += -1.0/2.0;                                // special case S2
    
    /* d2 xSpecies / dr ds */
    for (i=0; i<NR; i++) {
        for (j=0; j<NS; j++) {
            d2xSpeciesdrds[  0][i][j] = -dcoeffds[j];  /* SiO2  */
            d2xSpeciesdrds[i+1][i][j] =  dcoeffds[j];  /* other */
        }
    }
    
    /* Total moles of species relative to 1 mole of basis components */
    denom = 4.0 - 2.0*s[1] - 2.0*s[2] + 2.0*s[3] + s[6]; /* Special case */
    dDenomds[0] =  0.0;
    dDenomds[1] = -2.0;
    dDenomds[2] = -2.0;
    dDenomds[3] =  2.0;
    dDenomds[4] =  0.0;
    dDenomds[5] =  0.0;
    dDenomds[6] =  1.0;
    
    nSpecies = 4.0/denom;
    for (i=0; i<NS; i++) {
        dnSpeciesds[i] = -4.0*dDenomds[i]/(denom*denom);
        for (j=0; j<NS; j++) {
            d2nSpeciesds2[i][j] = 8.0*dDenomds[i]*dDenomds[j]/(denom*denom*denom);
            for (k=0; k<NS; k++) d3nSpeciesds3[i][j][k] = -24.0*dDenomds[i]*dDenomds[j]*dDenomds[k]/(denom*denom*denom*denom);
        }
    }
    
    return okay;
}

/*
 * =========================================================
 * Superfluid converted FORTRAN
 */

#define LA 15
#define LF 7

static double cpint(double t0, double t1, double ca, double cb, double cc, double cd, double ce, double cf,
             double cg, double ch, double ci, double cj, double ck) {
    const double rn2 = 2.0, rn3 = 3.0, rn5 = 5.0;
    
    double t2, t3, t4, t5, t6, ta, tb, tc, td, te, tf, tg, th, ti, tj, tk;
    t2 = t0 + t1;
    t3 = t0*t1;
    t4 = t3*t3;
    t5 = t0*t0;
    t6 = t5 + t1*t1;
    ta = t1 - t0;
    tb = ta*t2/rn2;
    tc = ta/t3;
    td = ta*(t2*t2 - t3)/rn3;
    te = tb/t4;
    tf = rn2*(sqrt(t1) - sqrt(t0));
    tg = log(t1/t0);
    th = td/(t3*t4);
    ti = tf/sqrt(t3);
    tj = tb*t6/rn2;
    tk = ta*(t1*t2*t6 + t5*t5)/rn5;
    return  ca*ta + cb*tb + cc*tc + cd*td + ce*te + cf*tf + cg*tg + ch*th + ci*ti + cj*tj + ck*tk;
}

static double shecp_c[LA][LF][8], shecp_hf[LA], shecp_s[LA];
static double sheom_hom[LA][LF-1], sheom_tom[LA][LF-1];
static int sheom_nom[LA];

static double h0(int i, double t) {
    double rn0 = 0.0, rna = 298.150, h0 = 0.0;
    int j;
    if (sheom_nom[i] == 0) {
        //
    } else if (sheom_tom[i][0] <= t) {
        h0 = shecp_hf[i] + cpint(rna, sheom_tom[i][0], shecp_c[i][0][0], shecp_c[i][0][1], shecp_c[i][0][2], shecp_c[i][0][3],
                           shecp_c[i][0][4], shecp_c[i][0][5], shecp_c[i][0][6], rn0, rn0, rn0, rn0) + sheom_hom[i][0];
        j = 1;
    line96:
        if (j < sheom_nom[i]) {
            if (sheom_tom[i][j] <= t) goto line21;
        }
        h0 = h0 + cpint(sheom_tom[i][j-1], t, shecp_c[i][j][0], shecp_c[i][j][1], shecp_c[i][j][2], shecp_c[i][j][3],
                        shecp_c[i][j][4], shecp_c[i][j][5], shecp_c[i][j][6], rn0, rn0, rn0, rn0);
        return h0;
    line21:
        h0 = h0 + cpint(sheom_tom[i][j-1], sheom_tom[i][j], shecp_c[i][j][0], shecp_c[i][j][1], shecp_c[i][j][2],
                        shecp_c[i][j][3], shecp_c[i][j][4], shecp_c[i][j][5], shecp_c[i][j][6], rn0, rn0, rn0, rn0) + sheom_hom[i][j];
        j++;
        goto line96;
    }
    h0 = shecp_hf[i] + cpint(rna, t, shecp_c[i][0][0], shecp_c[i][0][1], shecp_c[i][0][2], shecp_c[i][0][3], shecp_c[i][0][4],
                       shecp_c[i][0][5], shecp_c[i][0][6], rn0, rn0, rn0, rn0);
    return h0;
}

static double s0(int i, double t) {
    double rn0 = 0.0, rna = 298.150, s0 = 0.0;
    int j;

    if (sheom_nom[i] == 0) {
        //
    } else if (sheom_tom[i][0] <= t) {
        s0 = shecp_s[i] + cpint(rna, sheom_tom[i][0], shecp_c[i][0][1], shecp_c[i][0][3], shecp_c[i][0][6], rn0, shecp_c[i][0][2],
                                rn0, shecp_c[i][0][0], shecp_c[i][0][4], shecp_c[i][0][5], rn0, rn0) + sheom_hom[i][0]/sheom_tom[i][0];
        j = 1;
    line180:
        if (j < sheom_nom[i]) {
            if (sheom_tom[i][j] <= t) goto line177;
        }
        s0 = s0 + cpint(sheom_tom[i][j-1], t, shecp_c[i][j][1], shecp_c[i][j][3], shecp_c[i][j][6], rn0, shecp_c[i][j][2],
                        rn0, shecp_c[i][j][0], shecp_c[i][j][4], shecp_c[i][j][5], rn0, rn0);
        return s0;
    line177:
        s0 = s0 + cpint(sheom_tom[i][j-1], sheom_tom[i][j], shecp_c[i][j][1], shecp_c[i][j][3], shecp_c[i][j][6], rn0,
                        shecp_c[i][j][2], rn0, shecp_c[i][j][0], shecp_c[i][j][4], shecp_c[i][j][5], rn0, rn0)
           + sheom_hom[i][j]/sheom_tom[i][j];
        j++;
        goto line180;
    }
        s0 = shecp_s[i] + cpint(rna, t, shecp_c[i][0][1], shecp_c[i][0][3], shecp_c[i][0][6], rn0, shecp_c[i][0][2],
                                rn0, shecp_c[i][0][0], shecp_c[i][0][4], shecp_c[i][0][5], rn0, rn0);
    return s0;
}

#define LB 20
#define LC 20

static double salla_a[LA][LB], salla_b0[LB], salla_gv[LA], salla_pi[2*LB], salla_vgas[LA];
static int salla_l;
static double salli_y[LA];
static int salli_mf[LC+1], salli_ml[LC+1], salli_mp, salli_mv;
static double sallr_aktfln[LA], sallr_px, sallr_rt, sallr_vx, sallr_x[LA], sallr_ytot[LC];
static double ssgfc_xscan, ssgfc_yf[LA], ssgfc_yftot[LC];
static double swij_w[15][15][LC], swij_wm[15][15];
static int swij_ich, swij_jch, swij_mch;

static void interw(int m, double t, double p, double *v) {
    double dgas[13] = {
        2.650e0,3.760e0,3.565e0,3.760e0,3.109e0,2.960e0,4*3.0e0, 3.526e0, 3.000e0, 3.317e0
    };
    double egas[13] = {
        380.0e0,424.16e0,227.13e0,100.2e0,194.3e0,36.7e0,4*200.0e0, 139.2e0, 200.0e0, 146.52e0
    };
    double ugas[13] = {
        1.85e0,5*0.0e0,0.0e0, 1.61e0, 0.0e0, 0.0e0, 0.0e0, 0.0e0, 0.0e0
    };
    double sgas[13] = {
        1.59e0,2.65e0,2.60e0,1.95e0,1.60e0,0.79e0, 2.0e0, 3.72e0, 2.0e0, 2.0e0, 2.0e0, 2.0e0, 2.0e0
    };
    double agas[13] = {
        0., 0.615, 0.283, 0., 0.308, 0., 0.3, 0.3, 0.3, 0.3, 0.25, 0.3, 0.121
    };
    double xgas[13], rgas[13], wii[13], aij[13][13], bij[13][13], dij[13][13], eij[13][13], uij[13][13], rij[13][13], wmix[13][13];
    
    for (int i=salli_mf[m]; i<=salli_ml[m]; i++) {
        agas[i] = agas[i]*dgas[i]/(1.0 + agas[i]);
        xgas[i] = pow(ugas[i], 2.0)*pow(dgas[i], 3.0)*egas[i];
        rgas[i] = 2.0e8*pow(21.0*salla_vgas[i]/(88.0*6.023e23),(1.0/3.0));
        wii[i] = 8.3143*t*(4.0*egas[i]*(pow((dgas[i] - agas[i])/(rgas[i] - agas[i]), 12.0)
                                        - pow((dgas[i] - agas[i])/(rgas[i] - agas[i]),  6.0))
                           - xgas[i]/pow(rgas[i], 3.0));
    }
    
    for (int i=salli_mf[m]; i<=salli_ml[m]; i++) {
        for (int j=salli_mf[m]; j<salli_ml[m]; j++) {
            if ((i != j) && (i < j)) {
                aij[i][j] = (agas[i] + agas[j])/2.0;
                bij[i][j] = 1.0 + (sgas[j]/pow(dgas[j],3.0))*ugas[i]*pow(egas[i]/egas[j],0.5)/4.0;
                dij[i][j] = pow(bij[i][j], (-1./6.))*(dgas[i] + dgas[j])/2.0;
                eij[i][j] = sqrt(egas[i]*egas[j]);
                uij[i][j] = sqrt(ugas[i]*ugas[j]);
                rij[i][j] = (rgas[i] + rgas[j])/2.0;
                wmix[i][j] = 8.3143*t*(4.0*eij[i][j]*(pow((dij[i][j] - aij[i][j])/(rij[i][j] - aij[i][j]), 12.0)
                                                      - pow((dij[i][j] - aij[i][j])/(rij[i][j] - aij[i][j]),  6.0))
                                       - pow(uij[i][j], 2.0)*eij[i][j]*pow(dij[i][j],3.0)/pow(rij[i][j], 3.0));
                swij_wm[i][j] = (2.0*wmix[i][j] - wii[i] - wii[j])/(2.0*t);
            }
        }
    }
}

static void gamma2(int m, double *xn, double t, double p) {
    for (int i=salli_mf[m]; i<=salli_ml[m]; i++) {
        sallr_aktfln[i] = 0.0;
        for(int j=salli_mf[m]; j<=salli_ml[m]; j++) {
            if ((j != i) && (sallr_x[j] > 0.0)) {
                if (sallr_x[i] > 0.0) {
                    double temp = sallr_x[i] + sallr_x[j];
                    double x1 = sallr_x[i]/temp;
                    double x2 = 1.0 - x1;
                    double term = salla_vgas[i] + salla_vgas[j];
                    double q1 = 5.0*salla_vgas[i]/term;
                    double q2 = 5.0 - q1;
                    int ia = i - salli_mf[m];
                    int ja = j - salli_mf[m];
                    double temp1 = 2.0*swij_w[ia][ja][m]*x1*x2*q1*q2/(x1*q1 + x2*q2);
                    double temp2 = 2.0*swij_w[ia][ja][m]*q1/pow(1.0 + q1*x1/(q2*x2), 2.0);
                    sallr_aktfln[i] += temp*(temp1*(1.0 - temp) + temp2);
                }
                if (j < salli_ml[m]) {
                    for (int k=j+1;  k<=salli_ml[m]; k++) {
                        if ((k != i) && (sallr_x[k] > 0.0)) {
                            double temp = sallr_x[j] + sallr_x[k];
                            double x1 = sallr_x[j]/temp;
                            double x2 = 1.0 - x1;
                            double term = salla_vgas[j] + salla_vgas[k];
                            double q1 = 5.*salla_vgas[j]/term;
                            double q2 = 5.0 - q1;
                            int ja = j - salli_mf[m];
                            int ka = k - salli_mf[m];
                            double temp1 = 2.0*swij_w[ja][ka][m]*x1*x2*q1*q2/(x1*q1 + x2*q2);
                            sallr_aktfln[i] -= temp*temp*temp1;
                        }
                    }
                }
            }
        }
    }
    return;
}

static void factor(int m, double *xn, double t, double p, double *v) {
    int ich = 0;
    int jch = 0;
    int mch = 0;
    double rt = 8.3143*t;

    interw(m, t, p, v);
    
    if ((ich != 0) || (jch != 1) || (mch != 0)) swij_w[0][1][0] = swij_wm[0][1]/rt;
    if ((ich != 0) || (jch != 2) || (mch != 0)) swij_w[0][2][0] = swij_wm[0][2]/rt;
    if ((ich != 0) || (jch != 3) || (mch != 0)) swij_w[0][3][0] = swij_wm[0][3]/rt;
    if ((ich != 0) || (jch != 4) || (mch != 0)) swij_w[0][4][0] = swij_wm[0][4]/rt;
    if ((ich != 0) || (jch != 5) || (mch != 0)) swij_w[0][5][0] = swij_wm[0][5]/rt;
    if ((ich != 0) || (jch != 6) || (mch != 0)) swij_w[0][6][0] = swij_wm[0][6]/rt;
    if ((ich != 0) || (jch != 7) || (mch != 0)) swij_w[0][7][0] = swij_wm[0][7]/rt;
    if ((ich != 0) || (jch != 8) || (mch != 0)) swij_w[0][8][0] = swij_wm[0][8]/rt;
    if ((ich != 0) || (jch != 9) || (mch != 0)) swij_w[0][9][0] = swij_wm[0][9]/rt;
    if ((ich != 0) || (jch != 10) || (mch != 0)) swij_w[0][10][0] = swij_wm[0][10]/rt;
    if ((ich != 0) || (jch != 11) || (mch != 0)) swij_w[0][11][0] = swij_wm[0][11]/rt;
    if ((ich != 0) || (jch != 12) || (mch != 0)) swij_w[0][12][0] = swij_wm[0][12]/rt;
    
    if ((ich != 1) || (jch != 0) || (mch != 0)) swij_w[1][0][0] = swij_w[0][1][0];
    if ((ich != 1) || (jch != 2) || (mch != 0)) swij_w[1][2][0] = swij_wm[1][2]/rt;
    if ((ich != 1) || (jch != 3) || (mch != 0)) swij_w[1][3][0] = swij_wm[1][3]/rt;
    if ((ich != 1) || (jch != 4) || (mch != 0)) swij_w[1][4][0] = swij_wm[1][4]/rt;
    if ((ich != 1) || (jch != 5) || (mch != 0)) swij_w[1][5][0] = swij_wm[1][5]/rt;
    if ((ich != 1) || (jch != 6) || (mch != 0)) swij_w[1][6][0] = swij_wm[1][6]/rt;
    if ((ich != 1) || (jch != 7) || (mch != 0)) swij_w[1][7][0] = swij_wm[1][7]/rt;
    if ((ich != 1) || (jch != 8) || (mch != 0)) swij_w[1][8][0] = swij_wm[1][8]/rt;
    if ((ich != 1) || (jch != 9) || (mch != 0)) swij_w[1][9][0] = swij_wm[1][9]/rt;
    if ((ich != 1) || (jch != 10) || (mch != 0)) swij_w[1][10][0] = swij_wm[1][10]/rt;
    if ((ich != 1) || (jch != 11) || (mch != 0)) swij_w[1][11][0] = swij_wm[1][11]/rt;
    if ((ich != 1) || (jch != 12) || (mch != 0)) swij_w[1][12][0] = swij_wm[1][12]/rt;
    
    if ((ich != 2) || (jch != 0) || (mch != 0)) swij_w[2][0][0] = swij_w[0][2][0];
    if ((ich != 2) || (jch != 1) || (mch != 0)) swij_w[2][1][0] = swij_w[1][2][0];
    if ((ich != 2) || (jch != 3) || (mch != 0)) swij_w[2][3][0] = swij_wm[2][3]/rt;
    if ((ich != 2) || (jch != 4) || (mch != 0)) swij_w[2][4][0] = swij_wm[2][4]/rt;
    if ((ich != 2) || (jch != 5) || (mch != 0)) swij_w[2][5][0] = swij_wm[2][5]/rt;
    if ((ich != 2) || (jch != 6) || (mch != 0)) swij_w[2][6][0] = swij_wm[2][6]/rt;
    if ((ich != 2) || (jch != 7) || (mch != 0)) swij_w[2][7][0] = swij_wm[2][7]/rt;
    if ((ich != 2) || (jch != 8) || (mch != 0)) swij_w[2][8][0] = swij_wm[2][8]/rt;
    if ((ich != 2) || (jch != 9) || (mch != 0)) swij_w[2][9][0] = swij_wm[2][9]/rt;
    if ((ich != 2) || (jch != 10) || (mch != 0)) swij_w[2][10][0] = swij_wm[2][10]/rt;
    if ((ich != 2) || (jch != 11) || (mch != 0)) swij_w[2][11][0] = swij_wm[2][11]/rt;
    if ((ich != 2) || (jch != 12) || (mch != 0)) swij_w[2][12][0] = swij_wm[2][12]/rt;
    
    if ((ich != 3) || (jch != 0) || (mch != 0)) swij_w[3][0][0] = swij_w[0][3][0];
    if ((ich != 3) || (jch != 1) || (mch != 0)) swij_w[3][1][0] = swij_w[1][3][0];
    if ((ich != 3) || (jch != 2) || (mch != 0)) swij_w[3][2][0] = swij_w[2][3][0];
    if ((ich != 3) || (jch != 4) || (mch != 0)) swij_w[3][4][0] = swij_wm[3][4]/rt;
    if ((ich != 3) || (jch != 5) || (mch != 0)) swij_w[3][5][0] = swij_wm[3][5]/rt;
    if ((ich != 3) || (jch != 6) || (mch != 0)) swij_w[3][6][0] = swij_wm[3][6]/rt;
    if ((ich != 3) || (jch != 7) || (mch != 0)) swij_w[3][7][0] = swij_wm[3][7]/rt;
    if ((ich != 3) || (jch != 8) || (mch != 0)) swij_w[3][8][0] = swij_wm[3][8]/rt;
    if ((ich != 3) || (jch != 9) || (mch != 0)) swij_w[3][9][0] = swij_wm[3][9]/rt;
    if ((ich != 3) || (jch != 10) || (mch != 0)) swij_w[3][10][0] = swij_wm[3][10]/rt;
    if ((ich != 3) || (jch != 11) || (mch != 0)) swij_w[3][11][0] = swij_wm[3][11]/rt;
    if ((ich != 3) || (jch != 12) || (mch != 0)) swij_w[3][12][0] = swij_wm[3][12]/rt;
    
    if ((ich != 4) || (jch != 0) || (mch != 0)) swij_w[4][0][0] = swij_w[0][4][0];
    if ((ich != 4) || (jch != 1) || (mch != 0)) swij_w[4][1][0] = swij_w[1][4][0];
    if ((ich != 4) || (jch != 2) || (mch != 0)) swij_w[4][2][0] = swij_w[2][4][0];
    if ((ich != 4) || (jch != 3) || (mch != 0)) swij_w[4][3][0] = swij_w[3][4][0];
    if ((ich != 4) || (jch != 5) || (mch != 0)) swij_w[4][5][0] = swij_wm[4][5]/rt;
    if ((ich != 4) || (jch != 6) || (mch != 0)) swij_w[4][6][0] = swij_wm[4][6]/rt;
    if ((ich != 4) || (jch != 7) || (mch != 0)) swij_w[4][7][0] = swij_wm[4][7]/rt;
    if ((ich != 4) || (jch != 8) || (mch != 0)) swij_w[4][8][0] = swij_wm[4][8]/rt;
    if ((ich != 4) || (jch != 9) || (mch != 0)) swij_w[4][9][0] = swij_wm[4][9]/rt;
    if ((ich != 4) || (jch != 10) || (mch != 0)) swij_w[4][10][0] = swij_wm[4][10]/rt;
    if ((ich != 4) || (jch != 11) || (mch != 0)) swij_w[4][11][0] = swij_wm[4][11]/rt;
    if ((ich != 4) || (jch != 12) || (mch != 0)) swij_w[4][12][0] = swij_wm[4][12]/rt;
    
    if ((ich != 5) || (jch != 0) || (mch != 0)) swij_w[5][0][0] = swij_w[0][5][0];
    if ((ich != 5) || (jch != 1) || (mch != 0)) swij_w[5][1][0] = swij_w[1][5][0];
    if ((ich != 5) || (jch != 2) || (mch != 0)) swij_w[5][2][0] = swij_w[2][5][0];
    if ((ich != 5) || (jch != 3) || (mch != 0)) swij_w[5][3][0] = swij_w[3][5][0];
    if ((ich != 5) || (jch != 4) || (mch != 0)) swij_w[5][4][0] = swij_w[4][5][0];
    if ((ich != 5) || (jch != 6) || (mch != 0)) swij_w[5][6][0] = swij_wm[5][6]/rt;
    if ((ich != 5) || (jch != 7) || (mch != 0)) swij_w[5][7][0] = swij_wm[5][7]/rt;
    if ((ich != 5) || (jch != 8) || (mch != 0)) swij_w[5][8][0] = swij_wm[5][8]/rt;
    if ((ich != 5) || (jch != 9) || (mch != 0)) swij_w[5][9][0] = swij_wm[5][9]/rt;
    if ((ich != 5) || (jch != 10) || (mch != 0)) swij_w[5][10][0] = swij_wm[5][10]/rt;
    if ((ich != 5) || (jch != 11) || (mch != 0)) swij_w[5][11][0] = swij_wm[5][11]/rt;
    if ((ich != 5) || (jch != 12) || (mch != 0)) swij_w[5][12][0] = swij_wm[5][12]/rt;
    
    if ((ich != 6) || (jch != 0) || (mch != 0)) swij_w[6][0][0] = swij_w[0][6][0];
    if ((ich != 6) || (jch != 1) || (mch != 0)) swij_w[6][1][0] = swij_w[1][6][0];
    if ((ich != 6) || (jch != 2) || (mch != 0)) swij_w[6][2][0] = swij_w[2][6][0];
    if ((ich != 6) || (jch != 3) || (mch != 0)) swij_w[6][3][0] = swij_w[3][6][0];
    if ((ich != 6) || (jch != 4) || (mch != 0)) swij_w[6][4][0] = swij_w[4][6][0];
    if ((ich != 6) || (jch != 5) || (mch != 0)) swij_w[6][5][0] = swij_w[5][6][0];
    if ((ich != 6) || (jch != 7) || (mch != 0)) swij_w[6][7][0] = swij_wm[6][7]/rt;
    if ((ich != 6) || (jch != 8) || (mch != 0)) swij_w[6][8][0] = swij_wm[6][8]/rt;
    if ((ich != 6) || (jch != 9) || (mch != 0)) swij_w[6][9][0] = swij_wm[6][9]/rt;
    if ((ich != 6) || (jch != 10) || (mch != 0)) swij_w[6][10][0] = swij_wm[6][10]/rt;
    if ((ich != 6) || (jch != 11) || (mch != 0)) swij_w[6][11][0] = swij_wm[6][11]/rt;
    if ((ich != 6) || (jch != 12) || (mch != 0)) swij_w[6][12][0] = swij_wm[6][12]/rt;
    
    if ((ich != 7) || (jch != 0) || (mch != 0)) swij_w[7][0][0] = swij_w[0][7][0];
    if ((ich != 7) || (jch != 1) || (mch != 0)) swij_w[7][1][0] = swij_w[1][7][0];
    if ((ich != 7) || (jch != 2) || (mch != 0)) swij_w[7][2][0] = swij_w[2][7][0];
    if ((ich != 7) || (jch != 3) || (mch != 0)) swij_w[7][3][0] = swij_w[3][7][0];
    if ((ich != 7) || (jch != 4) || (mch != 0)) swij_w[7][4][0] = swij_w[4][7][0];
    if ((ich != 7) || (jch != 5) || (mch != 0)) swij_w[7][5][0] = swij_w[5][7][0];
    if ((ich != 7) || (jch != 6) || (mch != 0)) swij_w[7][6][0] = swij_w[6][7][0];
    if ((ich != 7) || (jch != 8) || (mch != 0)) swij_w[7][8][0] = swij_wm[7][8]/rt;
    if ((ich != 7) || (jch != 9) || (mch != 0)) swij_w[7][9][0] = swij_wm[7][9]/rt;
    if ((ich != 7) || (jch != 10) || (mch != 0)) swij_w[7][10][0] = swij_wm[7][10]/rt;
    if ((ich != 7) || (jch != 11) || (mch != 0)) swij_w[7][11][0] = swij_wm[7][11]/rt;
    if ((ich != 7) || (jch != 12) || (mch != 0)) swij_w[7][12][0] = swij_wm[7][12]/rt;
    
    if ((ich != 8) || (jch != 0) || (mch != 0)) swij_w[8][0][0] = swij_w[0][8][0];
    if ((ich != 8) || (jch != 1) || (mch != 0)) swij_w[8][1][0] = swij_w[1][8][0];
    if ((ich != 8) || (jch != 2) || (mch != 0)) swij_w[8][2][0] = swij_w[2][8][0];
    if ((ich != 8) || (jch != 3) || (mch != 0)) swij_w[8][3][0] = swij_w[3][8][0];
    if ((ich != 8) || (jch != 4) || (mch != 0)) swij_w[8][4][0] = swij_w[4][8][0];
    if ((ich != 8) || (jch != 5) || (mch != 0)) swij_w[8][5][0] = swij_w[5][8][0];
    if ((ich != 8) || (jch != 6) || (mch != 0)) swij_w[8][6][0] = swij_w[6][8][0];
    if ((ich != 8) || (jch != 7) || (mch != 0)) swij_w[8][7][0] = swij_w[7][8][0];
    if ((ich != 8) || (jch != 9) || (mch != 0)) swij_w[8][9][0] = swij_wm[8][9]/rt;
    if ((ich != 8) || (jch != 10) || (mch != 0)) swij_w[8][10][0] = swij_wm[8][10]/rt;
    if ((ich != 8) || (jch != 11) || (mch != 0)) swij_w[8][11][0] = swij_wm[8][11]/rt;
    if ((ich != 8) || (jch != 12) || (mch != 0)) swij_w[8][12][0] = swij_wm[8][12]/rt;
    
    if ((ich != 9) || (jch != 0) || (mch != 0)) swij_w[9][0][0] = swij_w[0][9][0];
    if ((ich != 9) || (jch != 1) || (mch != 0)) swij_w[9][1][0] = swij_w[1][9][0];
    if ((ich != 9) || (jch != 2) || (mch != 0)) swij_w[9][2][0] = swij_w[2][9][0];
    if ((ich != 9) || (jch != 3) || (mch != 0)) swij_w[9][3][0] = swij_w[3][9][0];
    if ((ich != 9) || (jch != 4) || (mch != 0)) swij_w[9][4][0] = swij_w[4][9][0];
    if ((ich != 9) || (jch != 5) || (mch != 0)) swij_w[9][5][0] = swij_w[5][9][0];
    if ((ich != 9) || (jch != 6) || (mch != 0)) swij_w[9][6][0] = swij_w[6][9][0];
    if ((ich != 9) || (jch != 7) || (mch != 0)) swij_w[9][7][0] = swij_w[7][9][0];
    if ((ich != 9) || (jch != 8) || (mch != 0)) swij_w[9][8][0] = swij_w[8][9][0];
    if ((ich != 9) || (jch != 10) || (mch != 0)) swij_w[9][10][0] = swij_wm[9][10]/rt;
    if ((ich != 9) || (jch != 11) || (mch != 0)) swij_w[9][11][0] = swij_wm[9][11]/rt;
    if ((ich != 9) || (jch != 12) || (mch != 0)) swij_w[9][12][0] = swij_wm[9][12]/rt;
    
    if ((ich != 10) || (jch != 0) || (mch != 0)) swij_w[10][0][0] = swij_w[0][10][0];
    if ((ich != 10) || (jch != 1) || (mch != 0)) swij_w[10][1][0] = swij_w[1][10][0];
    if ((ich != 10) || (jch != 2) || (mch != 0)) swij_w[10][2][0] = swij_w[2][10][0];
    if ((ich != 10) || (jch != 3) || (mch != 0)) swij_w[10][3][0] = swij_w[3][10][0];
    if ((ich != 10) || (jch != 4) || (mch != 0)) swij_w[10][4][0] = swij_w[4][10][0];
    if ((ich != 10) || (jch != 5) || (mch != 0)) swij_w[10][5][0] = swij_w[5][10][0];
    if ((ich != 10) || (jch != 6) || (mch != 0)) swij_w[10][6][0] = swij_w[6][10][0];
    if ((ich != 10) || (jch != 7) || (mch != 0)) swij_w[10][7][0] = swij_w[7][10][0];
    if ((ich != 10) || (jch != 8) || (mch != 0)) swij_w[10][8][0] = swij_w[8][10][0];
    if ((ich != 10) || (jch != 9) || (mch != 0)) swij_w[10][9][0] = swij_w[9][10][0];
    if ((ich != 10) || (jch != 11) || (mch != 0)) swij_w[10][11][0] = swij_wm[10][11]/rt;
    if ((ich != 10) || (jch != 12) || (mch != 0)) swij_w[10][12][0] = swij_wm[10][12]/rt;
    
    if ((ich != 11) || (jch != 0) || (mch != 0)) swij_w[11][0][0] = swij_w[0][11][0];
    if ((ich != 11) || (jch != 1) || (mch != 0)) swij_w[11][1][0] = swij_w[1][11][0];
    if ((ich != 11) || (jch != 2) || (mch != 0)) swij_w[11][2][0] = swij_w[2][11][0];
    if ((ich != 11) || (jch != 3) || (mch != 0)) swij_w[11][3][0] = swij_w[3][11][0];
    if ((ich != 11) || (jch != 4) || (mch != 0)) swij_w[11][4][0] = swij_w[4][11][0];
    if ((ich != 11) || (jch != 5) || (mch != 0)) swij_w[11][5][0] = swij_w[5][11][0];
    if ((ich != 11) || (jch != 6) || (mch != 0)) swij_w[11][6][0] = swij_w[6][11][0];
    if ((ich != 11) || (jch != 7) || (mch != 0)) swij_w[11][7][0] = swij_w[7][11][0];
    if ((ich != 11) || (jch != 8) || (mch != 0)) swij_w[11][8][0] = swij_w[8][11][0];
    if ((ich != 11) || (jch != 9) || (mch != 0)) swij_w[11][9][0] = swij_w[9][11][0];
    if ((ich != 11) || (jch != 10) || (mch != 0)) swij_w[11][10][0] = swij_w[10][11][0];
    if ((ich != 11) || (jch != 12) || (mch != 0)) swij_w[11][12][0] = swij_wm[11][12]/rt;
    
    if ((ich != 12) || (jch != 0) || (mch != 0)) swij_w[12][0][0] = swij_w[0][12][0];
    if ((ich != 12) || (jch != 1) || (mch != 0)) swij_w[12][1][0] = swij_w[1][12][0];
    if ((ich != 12) || (jch != 2) || (mch != 0)) swij_w[12][2][0] = swij_w[2][12][0];
    if ((ich != 12) || (jch != 3) || (mch != 0)) swij_w[12][3][0] = swij_w[3][12][0];
    if ((ich != 12) || (jch != 4) || (mch != 0)) swij_w[12][4][0] = swij_w[4][12][0];
    if ((ich != 12) || (jch != 5) || (mch != 0)) swij_w[12][5][0] = swij_w[5][12][0];
    if ((ich != 12) || (jch != 6) || (mch != 0)) swij_w[12][6][0] = swij_w[6][12][0];
    if ((ich != 12) || (jch != 7) || (mch != 0)) swij_w[12][7][0] = swij_w[7][12][0];
    if ((ich != 12) || (jch != 8) || (mch != 0)) swij_w[12][8][0] = swij_w[8][12][0];
    if ((ich != 12) || (jch != 9) || (mch != 0)) swij_w[12][9][0] = swij_w[9][12][0];
    if ((ich != 12) || (jch != 10) || (mch != 0)) swij_w[12][10][0] = swij_w[10][12][0];
    if ((ich != 12) || (jch != 11) || (mch != 0)) swij_w[12][11][0] = swij_w[11][12][0];

    gamma2(m, xn, t, p);
}

static double g1bar(int i, double t) {
    double hfss[13] = {
        -241818.46, -393509.38, -74809.92, -110524.54, 0.00, 0.00, 128365.12, -296829.70, -142088.64, -20627.12,
        0.00, -45720.00, 0.00
    };
    double sss[13] = {
        188.715, 213.635, 186.155, 197.564, 205.029, 130.574, 228.070, 248.111, 231.459, 205.685,
        191.61, 192.78, 154.84
    };
    double c1[7] = {
        4.6461000e+01, 5.966000e-03, 6.320000e+06, 0.000000e+00, -7.957000e+08,  0.000000e+00, -1.663000e+04
    };
    double c2[7] = {
        7.0728000e+01,-8.822000e-04, 3.464000e+06, 0.000000e+00, -2.492000e+08,  0.000000e+00, -1.876000e+04
    };
    double c3[7] = {
        1.2901000e+02,-4.849000e-04, 2.221000e+07, 0.000000e+00, -2.291000e+09,  0.000000e+00, -7.656000e+04
    };
    double c4[7] = {
        3.8578000e+01, 6.513000e-04, 1.781000e+06, 0.000000e+00, -9.971000e+07,  0.000000e+00, -7.725000e+03
    };
    double c5[7] = {
        3.9450000e+01, 5.609000e-04, 9.067000e+05, 0.000000e+00, 6.039000e+05,  0.000000e+00, -6.101000e+03
    };
    double c6[7] = {
        2.3948000e+01, 4.962000e-03, 5.279000e+05, 0.000000e+00, -1.525000e+08,  0.000000e+00,  9.536000e+02
    };
    double c7[7] = {
        0.3840800e+02,-0.463000e-04,-0.463500e+06, 0.000000e+00, 0.693000e+08,  0.000000e+00, -0.993600e+03
    };
    double c8[7] = {
        0.7182800e+02,-0.267200e-02, 0.235400e+07, 0.000000e+00, -0.208300e+09,  0.000000e+00, -0.164200e+05
    };
    double c9[7] = {
        0.4244100e+02,-0.275730e-01, 0.707320e+06, 0.460640e-05, -0.521660e+10,  0.407210e+00, -0.174320e+05
    };
    double c10[7] = {
        0.6545900e+02, 0.916800e-03, 0.932600e+07, 0.000000e+00, 0.105400e+10,  0.000000e+00, -0.288400e+05
    };
    double c11[7] = {
        2.3941e+01, 1.10680e-02, 1.9064e+05, -2.5518e-06, 0.0000e+00, 0.0000e+00, 0.0000e+00
    };
    double c12[7] = {
        2.9735e+01,  3.9119e-02, 2.9243e+05, -8.2274e-06, 0.0000e+00, -1.4378e+02, 0.0000e+00
    };
    double c13[7] = {
        2.080e+01, 0.0000e+00, 0.0000e+00, 0.0000e+00,  0.0000e+00, 0.0000e+00, 0.0000e+00
    };

    for(int k=0; k<13; k++) {
        shecp_hf[k] = hfss[k];
        shecp_s[k] = sss[k];
        sheom_hom[k][0] = 0.000;
        sheom_tom[k][0] = 6000.00;
        sheom_nom[k] = 1;
    }

    for (int j=0; j<7; j++) {
        shecp_c[ 0][0][j] = c1[j];
        shecp_c[ 1][0][j] = c2[j];
        shecp_c[ 2][0][j] = c3[j];
        shecp_c[ 3][0][j] = c4[j];
        shecp_c[ 4][0][j] = c5[j];
        shecp_c[ 5][0][j] = c6[j];
        shecp_c[ 6][0][j] = c7[j];
        shecp_c[ 7][0][j] = c8[j];
        shecp_c[ 8][0][j] = c9[j];
        shecp_c[ 9][0][j] = c10[j];
        shecp_c[10][0][j] = c11[j];
        shecp_c[11][0][j] = c12[j];
        shecp_c[12][0][j] = c13[j];
    }

    return (h0(i,t) - t*s0(i,t))/8.31451/t;
}

static void functs (void (*funct)(double *, double, double, double *),
                    double *x, double t, double v, double *ps) {
    double dv = 0.001*v;
    double vm = v -dv;
    double vp = v + dv;
    double pm, pp;
    funct (x, t, vm, &pm);
    funct (x, t, vp, &pp);
    *ps = (pp-pm)/2.0/dv;
    return;
}

static void nr (void (*funct)(double *, double, double, double *),
                double eps, double *x, double t,double p, double v0, double *v) {
    double rt = 8.31451*t;
    double vid = rt/p*10.0;
    double vj  = v0;
    double ptrue = p;
    double pj, pjs, vj1;
    
line1:
    funct (x, t, vj, &pj);
    functs(funct, x, t, vj, &pjs);
    vj1 = (ptrue - pj)/pjs + vj;
    
    if (fabs(vj1-vj) > 50.0) {
        *v = vid;
        return;
    }
    
    if (fabs((vj-vj1)/vj1) < eps) {
        *v = vj1;
        return;
    } else {
        vj = vj1;
        goto line1;
    }
    
    return;
}

static void kjco2 (double *x, double t, double v, double *p) {
    double ct =  (28.31 + 0.10721*t -8.81*1.e-6*pow(t,2.0))*1.e6;
    double dt =  (9380.0 - 8.53*t + 1.189*1.e-3*pow(t,2.0))*1.e6;
    double et =  (-368654.0 + 715.9*t + 0.1534*pow(t,2.0))*1.e6;

    double av = ct + dt/v + et/pow(v,2.0);
    double b  = 58.0;
    double r  = 83.14;
    double y  = b/4.0/v;

    *p = r*t*(1+y+pow(y,2.0)-pow(y,3.0))/v/pow(1.0-y,3.0) - av/v/(v+b)/sqrt(t);
    return;
}

static void kjco2g (double t, double p, double v, double *g) {
    double ct =  (28.31 + 0.10721*t -8.81*1.e-6*pow(t,2.0))*1.e6;
    double dt =  (9380.0 - 8.53*t + 1.189*1.e-3*pow(t,2.0))*1.e6;
    double et =  (-368654.0 + 715.9*t + 0.1534*pow(t,2.0))*1.e6;

    double av = ct + dt/v + et/pow(v,2.0);
    double b  = 58.0;
    double r  = 83.1451;
    double y  = b/4.0/v;

    double pp = r*t*(1+y+pow(y,2.0)-pow(y,3.0))/v/pow(1.0-y,3.0) - av/v/(v+b)/sqrt(t);
    double zz = pp*v/r/t;

    double rt32 = r*pow(t,1.5);
    double vb   = v+b;
    *g = y*(8.0-9.0*y+3.0*y*y)/pow(1.0-y,3.0) - log(zz) - ct/rt32/vb -dt/rt32/v/vb-et/rt32/v/v/vb + ct/rt32/b*log(v/vb)
     -dt/rt32/b/v + dt/rt32/b/b*log(vb/v) - et/rt32/2.0/b/v/v +et/rt32/b/b/v -et/rt32/b/b/b*log(vb/v);
    *g = ((*g)*r*t +r*t*log(p))/10.0;
    return;
}

static void co2 (double t, double p, double *v, double *g) {
    double v0, eps, x[13];
    if (p <= 10.0) {
        *v = 83.1451*t/p;
        *g = 8.31451*t*log(p);
        return;
    }
    if (p <= 10.0)                  v0 = 10000.0;
    if ((p >= 10.0) && (p <= 60.0)) v0 =   200.0;
    if (p > 60.0)                   v0 =    20.0;
    eps = 0.001;
    nr (kjco2, 0.002, x, t, p, v0, v);
    kjco2g (t, p, *v, g);
    return;
}

static void kjch4 (double *x, double t, double v, double *p) {
    double ct = 13.403 *1.e6  + 9.28 *1.e4*t + 2.7*pow(t,2.0);
    double dt =  5.216 *1.e9  - 6.80 *1.e6*t + 3.28 *1.e3*pow(t,2.0);
    double et = -2.3322*1.e11 + 6.738*1.e8*t + 3.179*1.e5*pow(t,2.0);

    double av = ct + dt/v + et/pow(v,2.0);
    double b  = 60.0;
    double r  = 83.1451;
    double y  = b/4.0/v;

    *p = r*t*(1+y+pow(y,2.0)-pow(y,3.0))/v/pow(1.0-y,3.0) - av/v/(v+b)/sqrt(t);
    return;
}

static void kjch4g (double t, double p, double v, double *g) {
    double ct = 13.403 *1.e6  + 9.28 *1.e4*t + 2.7       *pow(t,2.0);
    double dt =  5.216 *1.e9  - 6.80 *1.e6*t + 3.28 *1.e3*pow(t,2.0);
    double et = -2.3322*1.e11 + 6.738*1.e8*t + 3.179*1.e5*pow(t,2.0);

    double av = ct + dt/v + et/pow(v,2.0);
    double b  = 60.0;
    double r  = 83.1451;
    double y  = b/4.0/v;

    double pp = r*t*(1+y+pow(y,2.0)-pow(y,3.0))/v/pow(1.0-y,3.0) - av/v/(v+b)/sqrt(t);
    double zz = pp*v/r/t;

    double rt32 = r*pow(t,1.5);
    double vb   = v+b;
    *g = y*(8.0-9.0*y+3.0*y*y)/pow(1.0-y,3.0) - log(zz) - ct/rt32/v -dt/rt32/v/vb-et/rt32/v/v/vb + ct/rt32/b*log(v/vb)
     -dt/rt32/b/v + dt/rt32/b/b*log(vb/v) - et/rt32/2.0/b/v/v +et/rt32/b/b/v -et/rt32/b/b/b*log(vb/v);
    *g = ((*g)*r*t +r*t*log(p))/10.0;
    return;
}

static void ch4 (double t, double p, double *v, double *g) {
    double x[13], v0, eps;
    if (p <= 6.0) {
        *v = 83.1451*t/p;
        *g = 8.31451*t*log(p);
        return;
    }
    if (p <= 10.0)                v0 = 1000.0;
    if ((p > 10.0) && (p <= 600)) v0 =  200.0;
    if (p > 60.0)                 v0 =   20.0;
    eps = 0.002;
    nr (kjch4, eps, x, t, p, v0, v);
    kjch4g (t, p, *v, g);
    return;
}

static double ssggv_gbar, ssggv_ge[LA][8], ssggv_vt[LA][5], ssggv_v0[LA];
static int ssggv_igt[8], ssggv_kval, ssggv_mgt;
static char *stext_ident[LA];

static void gas(double t, double p, double *vvvvv, double *g) {
    double z[LA], tr[LA], pr[LA], ha[LA], hb[LA], hc[LA];
    double gvpk[LA], hd[LA];

    const double rn0=0.e0,fhoa1=-7.025e-1,fhoa2=1.16e-3,fhoa3=9.96799e1;
    const double fhob1=2.143e-1,fhob2=-3.1423e-14,fhoc1=-2.249e-06,fhoc2=-1.459e-1,fhoc3=2.169e-15,
        hhoa1=4.0446e0,hhoa2=-7.8042e5,hhoa3=2.1698e+8,hhoa4=-3.9410e-1,hhob1=1.2428e-1,hhob2=4.5709e+1,hhob3=-1.1006e+4,
        hhoc1=-1.1961e-8,hhoc2=-5.2680e-4,hhoc3=1.2440e-1;
    const double hhoc4=1.0726e-11,hhoc5=-6.9428e-11,hhod1=-4.6070e-13,hhod2=1.5981e-9,hhod3=-3.7239e-7,
        hhod4=-2.1564e-36,fcoa1=1.e0,fcoa2=-5.917e-1,fcob1=9.122e-2;
    const double fcoc1=-1.4164e-04,fcoc2=-2.8349e-06,hcoa1=2.0614e0,hcoa2=-2.2351e0,hcoa3=-3.9411e-1,
        hcob1=5.5125e-2,hcob2=3.9344e-2,hcoc1=-1.8935e-6,hcoc2=-1.1092e-5,hcoc3=-2.1892e-5,
        hcod1=5.0527e-11,hcod2=-6.3032e-21,ha1=2.2615e0,ha2=-68.712e0,ha3=-1.0537e4,ha4=-1.6936e-1,
        hb1=-0.26707e-3,hb2=0.20173e0,hb3=4.57586e0,hb4=0.314515e-4,hc1=-2.33755e-09,hc2=0.34091e-6,hc3=-14.188e-04,hc4=3.0117e-10,
        hd1=-3.2606e-15,hd2=2.4402e-12,hd3=-2.4027e-09;

    double gvp[LA] = {
      rn0, rn0, rn0, rn0, rn0, rn0, rn0, rn0, rn0, rn0, rn0, rn0, rn0, rn0, rn0
    };
    double tcr[10] = {
        6.4725e2,3.0415e2,1.9105e2,1.3315e2,1.5475e2,3.325e1,2.0815e2,4.3095e2,3.7795e2,3.7355e2
    };
    double pcr[10] = {
        2.211925e2,7.38659e1,4.64069e1,3.49571e1,5.07638e1,1.29696e1, 7.2954e1,7.87295e1,6.58612e1,9.00779e1
    };
    double aa1[10] = {
        -222.943e0,-38.315e0,-15.029e0,-4.650e0,-8.082e0,0.604e0,0.27243e1, 0.91198e2, 0.57637e1, -0.12649e4
    };
    double bb1[10] = {
        2.9865e-2,5.4832e-2,5.5411e-2,5.6794e-2,5.6237e-2,5.7324e-2, 0.57308e-1, 0.63955e-1, 0.57544e-1, -0.34877e-1
    };
    double cc1[10] = {
        0.0e0, 0.0e0, 0.0e0, 0.0e0, 0.0e0, 0.0e0,-0.33599e3, -0.11443e5, -0.29339e3, 0.95952e5
    };
    double dd1[10] = {
        0.0e0, 0.0e0, 0.0e0, 0.0e0, 0.0e0, 0.0e0,0.32792e-7, -0.84474e-6, -0.14216e-7, 0.71146e-6
    };
    double ee1[10] = {
        0.0e0, 0.0e0, 0.0e0, 0.0e0, 0.0e0, 0.0e0,-0.14595e6, 0.26843e6, -0.17878e7, 0.45675e5
    };
    double ff1[10] = {
        0.0e0, 0.0e0, 0.0e0, 0.0e0, 0.0e0, 0.0e0,-0.30694e-11, 0.55427e-10, 0.90888e-12, 0.10878e-8
    };
    double gg1[10] = {
        0.0e0, 0.0e0, 0.0e0, 0.0e0, 0.0e0, 0.0e0,0.29688e3, 0.43630e8, 0.27291e9, -0.43608e10
    };
    double hh1[10] = {
        35.9794,6.2055,2.8948,1.1645,1.6723,0.20685,-0.21840e-1, -0.12085e2, -0.16838e0, 0.18265e3
    };

    double rt = 8.3143*t;

//
//    *****  h2o  *****
//
    int i = 0;
    double v, gg;

//
// choosing the p(v,t) formulation from saul-wagner model
//          saul & wagner (1987, 1989)
//                           when t < 1273.15 k and p < 5 kbar.

    if (t > 1273.15) goto line502;
    h2o(t, p, &v, &gg);
    salla_vgas[i] = v;
    gvp[i] = gg/rt;
    z[i] = p*salla_vgas[i]/(10.0*rt);
    salla_gv[i] = g1bar(i, t) + gvp[i];
    goto  line9001;

//
// choosing the v(p,t) formulation in several pressure segments
//       of saxena-fei (1987, 1988) and shi-saxena (1992)
//                           when t > 1273.15 k and p < 5 kbar.

line502:
    pr[i] = p/pcr[i];
    tr[i] = t/tcr[i];

    if ((p > 10.00) || (p == 10.00)) goto line6771;
    salla_vgas[i] = (0.89959e+0 + 0.40267e-3*t +0.71835e+3/t -0.36840e+6/pow(t,2.0) +0.54379e+8/pow(t,3.0) -0.23965e+0*log(t));
    salla_vgas[i] = salla_vgas[i] +(0.17952e-1 -0.25984e-4*t -0.73371e+2/t +0.37138e+5/pow(t,2.0) -0.66324e+7/pow(t,3.0) +0.68494e-2*log(t))*p;
    salla_vgas[i] = salla_vgas[i] +(0.18520e+2 -0.14375e-3*t -0.25510e+4/t +0.92763e+6/pow(t,2.0) -0.14046e+9/pow(t,3.0) -0.98457*log(t))/p;
    salla_vgas[i] = rt*salla_vgas[i];
    z[i] = 1.0 + (-2.20960*sqrt(t) + 3.35460e-8*pow(t,3.0))/salla_vgas[i] + (3.4569e-5*pow(t,2.5) + 64.9764*log(t))/pow(salla_vgas[i],2.0);
    gvpk[i] = 0.00;
    gvp[i] = (0.89959e+0 + 0.40267e-3*t +0.71835e+3/t -0.36840e+6/pow(t,2.0) +0.54379e+8/pow(t,3.0) -0.23965e+0*log(t))*(p-1.0)/10.0;
    gvp[i] = gvp[i] +(0.17952e-1 -0.25984e-4*t -0.73371e+2/t+0.37138e+5/pow(t,2.0) -0.66324e+7/pow(t,3.0) +0.68494e-2*log(t))*0.5*(pow(p,2.0)-1.0)/10.0;
    gvp[i] = gvp[i] +(0.18520e+2 -0.14375e-3*t -0.25510e+4/t +0.92763e+6/pow(t,2.0) -0.14046e+9/pow(t,3.0) -0.98457*log(t))*log(p/1.0)/10.0;
    goto line2020;

line6771:
    if ((p > 100.01) || (p == 100.01)) goto line6772;
    salla_vgas[i] = (0.87400e+0 + 0.40270e-3*t +0.80337e+3/t -0.44457e+6/pow(t,2.0) +0.74301e+8/pow(t,3.0) -0.24792e+0*log(t));
    salla_vgas[i] = salla_vgas[i] +(0.38781e-2 -0.11371e-5*t -0.25486e+1/t +0.85059e+3/pow(t,2.0) -0.10269e+6/pow(t,3.0) -0.13657e-3*log(t))*p;
    salla_vgas[i] = salla_vgas[i] +(0.18394e+2 +0.40758e-3*t -0.24554e+4/t +0.12987e+7/pow(t,2.0) -0.28598e+9/pow(t,3.0) -0.10670e+1*log(t))/p;
    salla_vgas[i] = rt*salla_vgas[i];
    z[i] = 1 + (-2.20960*sqrt(t) + 3.35460e-8*pow(t,3.0))/salla_vgas[i] + (3.4569e-5*pow(t,2.5) + 64.9764*log(t))/pow(salla_vgas[i],2.0);
    gvpk[i] = (0.89959e+0 + 0.40267e-3*t +0.71835e+3/t -0.36840e+6/pow(t,2.0) +0.54379e+8/pow(t,3.0) -0.23965e+0*log(t))*(10.0-1.0)/10.0;
    gvpk[i] = gvpk[i] +(0.17952e-1 -0.25984e-4*t -0.73371e+2/t +0.37138e+5/pow(t,2.0) -0.66324e+7/pow(t,3.0) +0.68494e-2*log(t))*0.5*(100.0-1.0)/10.0;
    gvpk[i] = gvpk[i] +(0.18520e+2 -0.14375e-3*t -0.25510e+4/t +0.92763e+6/pow(t,2.0) -0.14046e+9/pow(t,3.0) -0.98457*log(t))*log(10.0/1.0)/10.0;
    gvp[i] = (0.87400e+0 + 0.40270e-3*t +0.80337e+3/t -0.44457e+6/pow(t,2.0) +0.74301e+8/pow(t,3.0) -0.24792e+0*log(t))*(p-10.0)/10.0;
    gvp[i] = gvp[i] +(0.38781e-2 -0.11371e-5*t -0.25486e+1/t +0.85059e+3/pow(t,2.0) -0.10269e+6/pow(t,3.0) -0.13657e-3*log(t))*0.5*(pow(p,2.0)-100.0)/10.0;
    gvp[i] = gvp[i] +(0.18394e+2 +0.40758e-3*t -0.24554e+4/t +0.12987e+7/pow(t,2.0) -0.28598e+9/pow(t,3.0) -0.10670e+1*log(t))*log(p/10.0)/10.0;
    goto line2020;

line6772:
    if ((p > 500.00) || (p == 500.00)) goto line6773;
    salla_vgas[i] = (-0.10168e+1 + 0.61393e-4*t +0.45627e+3/t -0.15728e+6/pow(t,2.0) +0.27222e+7/pow(t,3.0) +0.94293e-1*log(t));
    salla_vgas[i] = salla_vgas[i] +(0.47802e-3 -0.38548e-6*t -0.14431e+1/t +0.78898e+3/pow(t,2.0) -0.14526e+6/pow(t,3.0) +0.10234e-3*log(t))*p;
    salla_vgas[i] = salla_vgas[i] +(0.40511e+2 -0.59424e-2*t -0.35194e+5/t +0.18536e+8/pow(t,2.0) -0.29916e+10/pow(t,3.0) -0.72234e+0*log(t))/p;
    salla_vgas[i] = rt*salla_vgas[i];
    z[i] = 1 + (-2.20960*sqrt(t) + 3.35460e-8*pow(t,3.0))/salla_vgas[i] + (3.4569e-5*pow(t,2.5) + 64.9764*log(t))/pow(salla_vgas[i],2.0);
    gvpk[i] = (0.89959e+0 + 0.40267e-3*t +0.71835e+3/t -0.36840e+6/pow(t,2.0) +0.54379e+8/pow(t,3.0) -0.23965e+0*log(t))*(10.0-1.0)/10.0;
    gvpk[i] = gvpk[i] +(0.17952e-1 -0.25984e-4*t -0.73371e+2/t +0.37138e+5/pow(t,2.0) -0.66324e+7/pow(t,3.0) +0.68494e-2*log(t))*0.5*(100.0-1.0)/10.0;
    gvpk[i] = gvpk[i] +(0.18520e+2 -0.14375e-3*t -0.25510e+4/t +0.92763e+6/pow(t,2.0) -0.14046e+9/pow(t,3.0) -0.98457*log(t))*log(10.0/1.0)/10.0;
    gvpk[i] = gvpk[i]+(0.87400e+0+0.40270e-3*t+0.80337e+3/t-0.44457e+6/pow(t,2.0) +0.74301e+8/pow(t,3.0) -0.24792e+0*log(t))*(100.0-10.0)/10.0;
    gvpk[i] = gvpk[i] +(0.38781e-2 -0.11371e-5*t -0.25486e+1/t +0.85059e+3/pow(t,2.0) -0.10269e+6/pow(t,3.0) -0.13657e-3*log(t))*0.5*(10000.0-100.0)/10.0;
    gvpk[i] = gvpk[i] +(0.18394e+2 +0.40758e-3*t -0.24554e+4/t +0.12987e+7/pow(t,2.0) -0.28598e+9/pow(t,3.0) -0.10670e+1*log(t))*log(100.0/10.0)/10.0;
    gvp[i] = (-0.10168e+1 + 0.61393e-4*t +0.45627e+3/t -0.15728e+6/pow(t,2.0) +0.27222e+7/pow(t,3.0) +0.94293e-1*log(t))*(p-100.0)/10.0;
    gvp[i] = gvp[i] +(0.47802e-3 -0.38548e-6*t -0.14431e+1/t +0.78898e+3/pow(t,2.0) -0.14526e+6/pow(t,3.0) +0.10234e-3*log(t))*0.5*(pow(p,2.0)-10000.0)/10.0;
    gvp[i] = gvp[i] +(0.40511e+2 -0.59424e-2*t -0.35194e+5/t +0.18536e+8/pow(t,2.0) -0.29916e+10/pow(t,3.0) -0.72234e+0*log(t))*log(p/100.0)/10.0;
    goto line2020;

line6773:
    if ((p > 1000.00) || (p == 1000.00)) goto line2011;
    salla_vgas[i] = (0.10202e+1 + 0.23660e-3*t +0.95162e+3/t -0.73172e+6/pow(t,2.0) +0.17906e+9/pow(t,3.0) -0.24074e+0*log(t));
    salla_vgas[i] = salla_vgas[i] +(0.32345e-2 -0.22552e-6*t -0.21426e+1/t +0.12039e+4/pow(t,2.0) -0.25889e+6/pow(t,3.0) -0.26166e-3*log(t))*p;
    salla_vgas[i] = salla_vgas[i] +(0.42568e+2 -0.19179e-2*t -0.22746e+5/t +0.47462e+6/pow(t,2.0) +0.45740e+9/pow(t,3.0) -0.10585e+1*log(t))/p;
    salla_vgas[i] = rt*salla_vgas[i];
    z[i] = 1 + (-2.20960*sqrt(t) + 3.35460e-8*pow(t,3.0))/salla_vgas[i] + (3.4569e-5*pow(t,2.5) + 64.9764*log(t))/pow(salla_vgas[i],2.0);
    gvpk[i] = (0.89959e+0 + 0.40267e-3*t +0.71835e+3/t -0.36840e+6/pow(t,2.0) +0.54379e+8/pow(t,3.0) -0.23965e+0*log(t))*(10.0-1.0)/10.0;
    gvpk[i] = gvpk[i] +(0.17952e-1 -0.25984e-4*t -0.73371e+2/t +0.37138e+5/pow(t,2.0) -0.66324e+7/pow(t,3.0) +0.68494e-2*log(t))*0.5*(100.0-1.0)/10.0;
    gvpk[i] = gvpk[i] +(0.18520e+2 -0.14375e-3*t -0.25510e+4/t +0.92763e+6/pow(t,2.0) -0.14046e+9/pow(t,3.0) -0.98457*log(t))*log(10.0/1.0)/10.0;
    gvpk[i] =gvpk[i]+(0.87400e+0+0.40270e-3*t+0.80337e+3/t-0.44457e+6/pow(t,2.0) +0.74301e+8/pow(t,3.0) -0.24792e+0*log(t))*(100.0-10.0)/10.0;
    gvpk[i] = gvpk[i] +(0.38781e-2 -0.11371e-5*t -0.25486e+1/t +0.85059e+3/pow(t,2.0) -0.10269e+6/pow(t,3.0) -0.13657e-3*log(t))*0.5*(10000.0-100.0)/10.0;
    gvpk[i] = gvpk[i] +(0.18394e+2 +0.40758e-3*t -0.24554e+4/t +0.12987e+7/pow(t,2.0) -0.28598e+9/pow(t,3.0) -0.10670e+1*log(t))*log(100.0/10.0)/10.0;
    gvpk[i] = gvpk[i] + (-0.10168e+1 + 0.61393e-4*t +0.45627e+3/t -0.15728e+6/pow(t,2.0) +0.27222e+7/pow(t,3.0) +0.94293e-1*log(t))*(500.0-100.0)/10.0;
    gvpk[i] = gvpk[i] +(0.47802e-3 -0.38548e-6*t -0.14431e+1/t +0.78898e+3/pow(t,2.0) -0.14526e+6/pow(t,3.0) +0.10234e-3*log(t))*0.5*(25000.0-10000.0)/10.0;
    gvpk[i] = gvpk[i] +(0.40511e+2 -0.59424e-2*t -0.35194e+5/t +0.18536e+8/pow(t,2.0) -0.29916e+10/pow(t,3.0) -0.72234e+0*log(t))*log(500.0/100.0)/10.0;
    gvp[i] = (0.10202e+1 + 0.23660e-3*t +0.95162e+3/t -0.73172e+6/pow(t,2.0) +0.17906e+9/pow(t,3.0) -0.24074e+0*log(t))*(p-500.0)/10.0;
    gvp[i] = gvp[i] +(0.32345e-2 -0.22552e-6*t -0.21426e+1/t +0.12039e+4/pow(t,2.0) -0.25889e+6/pow(t,3.0) -0.26166e-3*log(t))*0.5*(pow(p,2.0)-250000.0)/10.0;
    gvp[i] = gvp[i] +(0.42568e+2 -0.19179e-2*t -0.22746e+5/t +0.47462e+6/pow(t,2.0) +0.45740e+9/pow(t,3.0) -0.10585e+1*log(t))*log(p/500.0)/10.0;
    goto line2020;

line2011:
    if ((p > 5000.00) || (p == 5000.00)) goto line2010;
    gvpk[i] = 1000.*(aa1[i] + bb1[i]*t + cc1[i]/t + dd1[i]*pow(t,2.0) + ee1[i]/pow(t,2.0) + ff1[i]*pow(t,3.0) + gg1[i]/pow(t,3.0) + hh1[i]*log(t))/rt;
    z[i] = fhoa1 + fhoa2*t + fhoa3/t;
    z[i] = z[i] + (fhob1/t + fhob2*pow(t,3.0))*p;
    z[i] = z[i] + (fhoc1/t + fhoc2/pow(t,3.0) + fhoc3*pow(t,2.0))*pow(p,2.0);
    salla_vgas[i] = 10.*rt*z[i]/p;
    gvp[i] = (fhoa1 + fhoa2*t + fhoa3/t)*log(p/1000.);
    gvp[i] = gvp[i] + (fhob1/t + fhob2*pow(t,3.0))*(p - 1000.);
    gvp[i] = gvp[i]+(fhoc1/t+fhoc2/pow(t,3.0)+fhoc3*pow(t,2.0))*(pow(p,2.0)-1.e6)/2.0;
    goto line2020;

line2010:
    gvpk[i] = 1000.*(-130.517+ 6.4967e-2*t + 19.4831*log(t))/rt;
    z[i] = hhoa1 + hhoa2/pow(t,2.0) + hhoa3/pow(t,3.0) + hhoa4*log(t);
    z[i] = z[i] + (hhob1/t + hhob2/pow(t,2.0) + hhob3/pow(t,3.0))*p;
    z[i] = z[i] + (hhoc5 + hhoc1/t + hhoc2/pow(t,2.0) + hhoc3/pow(t,3.0) + hhoc4*log(t))*pow(p,2.0);
    z[i] = z[i] + (hhod1/t + hhod2/pow(t,2.0) + hhod3/pow(t,3.0) + hhod4*pow(t,3.0))*pow(p,3.0);
    salla_vgas[i] = 10.*rt*z[i]/p;
    gvp[i] = (hhoa1 + hhoa2/pow(t,2.0) + hhoa3/pow(t,3.0) + hhoa4*log(t))*log(p/5000.);
    gvp[i] = gvp[i] + (hhob1/t + hhob2/pow(t,2.0) + hhob3/pow(t,3.0))*(p - 5000.);
    gvp[i] = gvp[i] + (hhoc5 + hhoc1/t + hhoc2/pow(t,2.0) + hhoc3/pow(t,3.0) + hhoc4*log(t))*(pow(p,2.0) - pow(5000.0,2.0))/2.0;
    gvp[i] = gvp[i] + (hhod1/t + hhod2/pow(t,2.0) + hhod3/pow(t,3.0) + hhod4*pow(t,3.0))*(pow(p,3.0) - pow(5000.0,3.0))/3.0;

line2020:
    gvp[i] = gvp[i] + gvpk[i];
    salla_gv[i] = g1bar(i,t) + gvp[i];

//
//************************************************
//*       -----  co2, ch4, co, o2  -----         *
//************************************************

line9001:

    for (i=1; i<5; i++) {
        // 1.  for co2
        //ccccccc
        // if choosing the p(v,t) formulation from mrk-eos model
        //          by kerrick and jacobs (1981)
        //
        
        if (i == 1) {
            if (t > 1273.15) goto line503;
            co2(t, p, &v, &gg);
            salla_vgas[i] = v;
            gvp[i]  = gg/rt;
            z[i] = p*salla_vgas[i]/(10.0*rt);
            salla_gv[i] = g1bar(i,t) + gvp[i];
            goto line226;
            
            // 2.  for ch4
            //ccccccc
            // if choosing the p(v,t) formulation
            //        from schemit-wagner model by friend et al. (1989)
            //     or from mrk-eos model by grevel (1990)
            //
            
        } else if (i == 2) {
            if (t > 1273.15) goto line503;
            ch4(t, p, &v, &gg);
            salla_vgas [i] = v;
            gvp[i] = gg/rt;
            z[i] = p*salla_vgas[i]/(10.0*rt);
            salla_gv[i] = g1bar(i,t) + gvp[i];
            goto line226;
            
            // 3.  for co and o2
            //ccccccc
            // if choosing the v(p,t) formulation in corresponding-state eos
            //              of saxena-fei (1987, 1988)
            //
            //        for co, o2:           p < 5 kbar;
            //        for co2, ch4:   t > 1273.15 k,  p < 5 kbar.
            //ccc
            
        } else if ((i == 3) || (i == 4)) {
        line503:
            pr[i] = p/pcr[i];
            tr[i] = t/tcr[i];
            
            if ((p > 1000.0) || (p == 1000.0)) goto line2031;
            z[i]= 1 + (0.09827/tr[i] - 0.2709/pow(tr[i],3.0))*pr[i] + (0.01427/pow(tr[i],4.0) - 0.00103/pow(tr[i],1.5))*pr[i]*pr[i];
            gvpk[i]=0.0;
            gvp[i] = log(p) + (0.09827/tr[i] - 0.2709/pow(tr[i],3.0))/pcr[i]*(p-1.0) + (0.01427/pow(tr[i],4.0) - 0.00103/pow(tr[i],1.5))/pow(pcr[i],2.0)/2.0*(pow(p,2.0)-1.0);
            salla_vgas[i] = 10.*rt*z[i]/p;
            goto line2060;
        line2031:
            if ((p > 5000.0) || (p == 5000.0)) goto line2050;
            gvpk[i] = 1000.*(aa1[i] + bb1[i]*t + cc1[i]/t + dd1[i]*pow(t,2.0) + ee1[i]/pow(t,2.0) + ff1[i]*pow(t,3.0) + gg1[i]/pow(t,3.0) + hh1[i]*log(t))/rt;
            z[i] = fcoa1 + fcoa2/pow(tr[i],2.0);
            z[i] = z[i] + (fcob1/tr[i])*pr[i];
            z[i] = z[i] + (fcoc1/pow(tr[i],2.0) + fcoc2*log(tr[i]))*pow(pr[i],2.0);
            salla_vgas[i] = 10.*rt*z[i]/p;
            gvp[i] = (fcoa1 + fcoa2/pow(tr[i],2.0))*log(p/1000.);
            gvp[i] = gvp[i] + (fcob1/tr[i])*(pr[i] - 1000./pcr[i]);
            gvp[i] = gvp[i] + (fcoc1/pow(tr[i],2.0) + fcoc2*log(tr[i]))*(pow(pr[i],2.0) - pow(1000.0/pcr[i],2.0))/2.0;
            goto line2060;
            
        line2050:
            gvpk[i] = 1000.*(aa1[i] + bb1[i]*t + cc1[i]/t + dd1[i]*pow(t,2.0) + ee1[i]/pow(t,2.0) + ff1[i]*pow(t,3.0) + gg1[i]/pow(t,3.0) + hh1[i]*log(t))/rt;
            gvpk[i] = gvpk[i] + (fcoa1 + fcoa2/pow(tr[i],2.0))*log(5000./1000.);
            gvpk[i] = gvpk[i] + (fcob1/tr[i])*(5000./pcr[i] - 1000./pcr[i]);
            gvpk[i] = gvpk[i] + (fcoc1/pow(tr[i],2.0) + fcoc2*log(tr[i]))*(pow(5000.0/pcr[i],2.0) - pow(1000./pcr[i],2.0))/2.0;
            z[i] = hcoa1 + hcoa2/pow(tr[i],2.0) + hcoa3*log(tr[i]);
            z[i] = z[i] + (hcob1/tr[i] + hcob2/pow(tr[i],2.0))*pr[i];
            z[i] = z[i] + (hcoc1/tr[i] + hcoc2/pow(tr[i],2.0) + hcoc3/pow(tr[i],3.0))*pow(pr[i],2.0);
            z[i] = z[i] + (hcod1/tr[i] + hcod2*pow(tr[i],3.0))*pow(pr[i],3.0);
            salla_vgas[i] = 10.*rt*z[i]/p;
            gvp[i] = (hcoa1 + hcoa2/pow(tr[i],2.0) + hcoa3*log(tr[i]))*log(p/5000.);
            gvp[i] = gvp[i] + (hcob1/tr[i] + hcob2/pow(tr[i],2.0))*(pr[i] - 5000./pcr[i]);
            gvp[i] = gvp[i] + (hcoc1/tr[i] + hcoc2/pow(tr[i],2.0) + hcoc3/pow(tr[i],3.0))*(pow(pr[i],2.0) - pow(5000./pcr[i],2.0))/2.0;
            gvp[i] = gvp[i] + (hcod1/tr[i] + hcod2*pow(tr[i],3.0))*(pow(pr[i],3.0) - pow(5000./pcr[i],3.0))/3.0;
            
        line2060:
            gvp[i] = gvp[i] + gvpk[i];
            salla_gv[i] = g1bar(i,t) + gvp[i];
            
        }
        
    line226:
        continue;
    }

//cc    *****  h2  *****
//
//ccccccc
//  choosing the v(p,t) formulation in corresponding-state eos
//              of saxena-fei (1987, 1988)

    i = 5;

    pr[i] = p/pcr[i];
    tr[i] = t/tcr[i];

    if ((p > 1000.0) || (p == 1000.0)) goto line2041;
    z[i]= 1 + (0.09827/tr[i] - 0.2709/pow(tr[i],3.0))*pr[i] + (0.01427/pow(tr[i],4.0) - 0.00103/pow(tr[i],1.5))*pr[i]*pr[i];
    gvpk[i]=0.0;
    gvp[i] = log(p) + (0.09827/tr[i] - 0.2709/pow(tr[i],3.0))/pcr[i]*(p-1.0) + (0.01427/pow(tr[i],4.0) - 0.00103/pow(tr[i],1.5))/pow(pcr[i],2.0)/2.0*(pow(p,2.0)-1.0);
    salla_vgas[i] = 10.*rt*z[i]/p;
    goto line2070;

line2041:
    ha[i]=ha1+ha2/t+ha3/(t*t)+log(t)*ha4;
    hb[i]=hb1+hb2/t+hb3/(t*t)+log(t)*hb4;
    hc[i]=hc1+hc2/t+hc3/(t*t)+log(t)*hc4;
    hd[i]=hd1+hd2/t+hd3/(t*t);
    z[i]=ha[i]+hb[i]*p+hc[i]*p*p+hd[i]*pow(p,3.0);
    salla_vgas[i] = 10.*rt*z[i]/p;
    gvpk[i] = 1000.*(aa1[i] + bb1[i]*t + cc1[i]/t + dd1[i]*pow(t,2.0) + ee1[i]/pow(t,2.0) + ff1[i]*pow(t,3.0) + gg1[i]/pow(t,3.0) + hh1[i]*log(t))/rt;
    gvp[i] = ha[i]*log(p/1000.) + hb[i]*(p-1000.);
    gvp[i] = gvp[i] + hc[i]*(pow(p,2.0)-1.e6)/2.;
    gvp[i] = gvp[i] + hd[i]*(pow(p,3.0)-1.e9)/3.;

line2070:
    gvp[i] = gvp[i] + gvpk[i];
    salla_gv[i] = g1bar(i,t) + gvp[i];

//
//    *****  s2  *****
//
//ccccccc
//  choosing the v(p,t) formulation in corresponding-state eos
//       of saxena & fei (1987, 1988), shi & saxena (1992)
//
    i = 6;

    pr[i] = p/pcr[i];
    tr[i] = t/tcr[i];

    if ((p > 1000.0) || (p == 1000.0)) goto line7331;
    z[i]= 1 + (0.09827/tr[i] - 0.2709/pow(tr[i],3.0))*pr[i] + (0.01427/pow(tr[i],4.0) - 0.00103/pow(tr[i],1.5))*pr[i]*pr[i];
    gvpk[i]=0.0;
    gvp[i] = log(p) + (0.09827/tr[i] - 0.2709/pow(tr[i],3.0))/pcr[i]*(p-1.0) + (0.01427/pow(tr[i],4.0) - 0.00103/pow(tr[i],1.5))/pow(pcr[i],2.0)/2.0*(pow(p,2.0)-1.0);
    salla_vgas[i] = 10.*rt*z[i]/p;
    goto line7361;

line7331:
    if ((p > 5000.0) || (p == 5000.0)) goto line7351;
    gvpk[i] = 1000.*(aa1[i] + bb1[i]*t + cc1[i]/t + dd1[i]*pow(t,2.0) + ee1[i]/pow(t,2.0) + ff1[i]*pow(t,3.0) + gg1[i]/pow(t,3.0) + hh1[i]*log(t))/rt;
    z[i] = fcoa1 + fcoa2/pow(tr[i],2.0);
    z[i] = z[i] + (fcob1/tr[i])*pr[i];
    z[i] = z[i] + (fcoc1/pow(tr[i],2.0) + fcoc2*log(tr[i]))*pow(pr[i],2.0);
    salla_vgas[i] = 10.*rt*z[i]/p;
    gvp[i] = (fcoa1 + fcoa2/pow(tr[i],2.0))*log(p/1000.);
    gvp[i] = gvp[i] + (fcob1/tr[i])*(pr[i] - 1000./pcr[i]);
    gvp[i] = gvp[i] + (fcoc1/pow(tr[i],2.0) + fcoc2*log(tr[i]))*(pow(pr[i],2.0) - pow(1000./pcr[i],2.0))/2.;
    goto line7361;

line7351:
    gvpk[i] = 1000.*(aa1[i] + bb1[i]*t + cc1[i]/t + dd1[i]*pow(t,2.0) + ee1[i]/pow(t,2.0) + ff1[i]*pow(t,3.0) + gg1[i]/pow(t,3.0) + hh1[i]*log(t))/rt;
    gvpk[i] = gvpk[i] + (fcoa1 + fcoa2/pow(tr[i],2.0))*log(5000./1000.);
    gvpk[i] = gvpk[i] + (fcob1/tr[i])*(5000./pcr[i] - 1000./pcr[i]);
    gvpk[i] = gvpk[i] + (fcoc1/pow(tr[i],2.0) + fcoc2*log(tr[i]))*(pow(5000./pcr[i],2.0) - pow(1000./pcr[i],2.0))/2.0;
    z[i] = hcoa1 + hcoa2/pow(tr[i],2.0) + hcoa3*log(tr[i]);
    z[i] = z[i] + (hcob1/tr[i] + hcob2/pow(tr[i],2.0))*pr[i];
    z[i] = z[i] + (hcoc1/tr[i] + hcoc2/pow(tr[i],2.0) + hcoc3/pow(tr[i],3.0))*pow(pr[i],2.0);
    z[i] = z[i] + (hcod1/tr[i] + hcod2*pow(tr[i],3.0))*pow(pr[i],3.0);
    salla_vgas[i] = 10.*rt*z[i]/p;
    gvp[i] = (hcoa1 + hcoa2/pow(tr[i],2.0) + hcoa3*log(tr[i]))*log(p/5000.);
    gvp[i] = gvp[i] + (hcob1/tr[i] + hcob2/pow(tr[i],2.0))*(pr[i] - 5000./pcr[i]);
    gvp[i] = gvp[i] + (hcoc1/tr[i] + hcoc2/pow(tr[i],2.0) + hcoc3/pow(tr[i],3.0))*(pow(pr[i],2.0) - pow(5000./pcr[i],2.0))/2.;
    gvp[i] = gvp[i] + (hcod1/tr[i] + hcod2*pow(tr[i],3.0))*(pow(pr[i],3.0) - pow(5000./pcr[i],3.0))/3.;

line7361:
    gvp[i] = gvp[i] + gvpk[i];
    salla_gv[i] = g1bar(i,t) + gvp[i];

//
//    *****  so2  ******
//
//ccccccc
//  choosing the v(p,t) formulation in corresponding-state eos
//               of shi & saxena (1992)
//
    i = 7;

    pr[i] = p/pcr[i];
    tr[i] = t/tcr[i];

    if ((t <= 300.0) && (p <= 100.0)) {
        salla_vgas[i] = 10.0*rt/p;
        gvp[i] = rt*log(p);
        gvp[i] = gvp[i]/rt;
        salla_gv[i] = g1bar(i,t) + gvp[i];
    } else {

        gvpk[i] = 0.00;
        z[i] = 0.93000e+0 + 0.45410e-1*tr[i] -0.24482e+0/tr[i] +0.24222e+0/pow(tr[i],2.0) -0.53701e+0/pow(tr[i],3.0) -0.21583e-1*log(tr[i]);
        z[i] = z[i] + (0.67077e-3 -0.18400e-2*tr[i] +0.67399e-1/tr[i] -0.29688e-1/pow(tr[i],2.0) +0.29577e-1/pow(tr[i],3.0) +0.52307e-2*log(tr[i]))*pr[i];
        z[i] = z[i] + (-0.36646e-3 +0.20067e-4*tr[i] +0.95671e-3/tr[i] -0.80239e-3/pow(tr[i],2.0) +0.20236e-3/pow(tr[i],3.0) +0.72484e-4*log(tr[i]))*pow(pr[i],2.0);
        salla_vgas[i] = 10.*rt*z[i]/p;
        gvp[i] = (0.93000e+0 + 0.45410e-1*tr[i] -0.24482e+0/tr[i] +0.24222e+0/pow(tr[i],2.0) -0.53701e+0/pow(tr[i],3.0) -0.21583e-1*log(tr[i]))*log(p);
        gvp[i] = gvp[i] + (0.67077e-3 -0.18400e-2*tr[i] +0.67399e-1/tr[i] -0.29688e-1/pow(tr[i],2.0) +0.29577e-1/pow(tr[i],3.0) +0.52307e-2*log(tr[i]))*(pr[i] - 1.0/pcr[i]);
        gvp[i] = gvp[i] +(-0.36646e-3 +0.20067e-4*tr[i] +0.95671e-3/tr[i] -0.80239e-3/pow(tr[i],2.0) +0.20236e-3/pow(tr[i],3.0) +0.72484e-4*log(tr[i]))*(pow(pr[i],2.0) - pow(1.00/pcr[i],2.0))/2.;
        gvp[i] = gvp[i] + gvpk[i];
        salla_gv[i] = g1bar(i,t) + gvp[i];

    }

//
//    *****  cos  *****
//
//ccccccc
//  choosing the v(p,t) formulation in corresponding-state eos
//       of saxena & fei (1987, 1988), shi & saxena (1992)

    i = 8;

    pr[i] = p/pcr[i];
    tr[i] = t/tcr[i];

    if ((p > 1000.0) || (p == 1000.0)) goto line7471;
    z[i]= 1 + (0.09827/tr[i] - 0.2709/pow(tr[i],3.0))*pr[i] + (0.01427/pow(tr[i],4.0) - 0.00103/pow(tr[i],1.5))*pr[i]*pr[i];
    gvpk[i]=0.0;
    gvp[i] = log(p) + (0.09827/tr[i] - 0.2709/pow(tr[i],3.0))/pcr[i]*(p-1.0) + (0.01427/pow(tr[i],4.0) - 0.00103/pow(tr[i],1.5))/pow(pcr[i],2.0)/2.0*(pow(p,2.0)-1.0);
    salla_vgas[i] = 10.*rt*z[i]/p;
    goto line7421;

line7471:
    if ((p > 5000.0) || (p == 5000.0)) goto line7472;
    gvpk[i] = 1000.*(aa1[i] + bb1[i]*t + cc1[i]/t + dd1[i]*pow(t,2.0) + ee1[i]/pow(t,2.0) + ff1[i]*pow(t,3.0) + gg1[i]/pow(t,3.0) + hh1[i]*log(t))/rt;
    z[i] = fcoa1 + fcoa2/pow(tr[i],2.0);
    z[i] = z[i] + (fcob1/tr[i])*pr[i];
    z[i] = z[i] + (fcoc1/pow(tr[i],2.0) + fcoc2*log(tr[i]))*pow(pr[i],2.0);
    salla_vgas[i] = 10.*rt*z[i]/p;
    gvp[i] = (fcoa1 + fcoa2/pow(tr[i],2.0))*log(p/1000.);
    gvp[i] = gvp[i] + (fcob1/tr[i])*(pr[i] - 1000./pcr[i]);
    gvp[i] = gvp[i] + (fcoc1/pow(tr[i],2.0) + fcoc2*log(tr[i]))*(pow(pr[i],2.0) - pow(1000./pcr[i],2.0))/2.;
    goto line7421;

line7472:
    gvpk[i] = 1000.*(aa1[i] + bb1[i]*t + cc1[i]/t + dd1[i]*pow(t,2.0) + ee1[i]/pow(t,2.0) + ff1[i]*pow(t,3.0) + gg1[i]/pow(t,3.0) + hh1[i]*log(t))/rt;
    gvpk[i] = gvpk[i] + (fcoa1 + fcoa2/pow(tr[i],2.0))*log(5000./1000.);
    gvpk[i] = gvpk[i] + (fcob1/tr[i])*(5000./pcr[i] - 1000./pcr[i]);
    gvpk[i] = gvpk[i] + (fcoc1/pow(tr[i],2.0) + fcoc2*log(tr[i]))*(pow(5000./pcr[i],2.0) - pow(1000./pcr[i],2.0))/2.;
    z[i] = hcoa1 + hcoa2/pow(tr[i],2.0) + hcoa3*log(tr[i]);
    z[i] = z[i] + (hcob1/tr[i] + hcob2/pow(tr[i],2.0))*pr[i];
    z[i] = z[i] + (hcoc1/tr[i] + hcoc2/pow(tr[i],2.0) + hcoc3/pow(tr[i],3.0))*pow(pr[i],2.0);
    z[i] = z[i] + (hcod1/tr[i] + hcod2*pow(tr[i],3.0))*pow(pr[i],3.0);
    salla_vgas[i] = 10.*rt*z[i]/p;
    gvp[i] = (hcoa1 + hcoa2/pow(tr[i],2.0) + hcoa3*log(tr[i]))*log(p/5000.);
    gvp[i] = gvp[i] + (hcob1/tr[i] + hcob2/pow(tr[i],2.0))*(pr[i] - 5000./pcr[i]);
    gvp[i] = gvp[i] + (hcoc1/tr[i] + hcoc2/pow(tr[i],2.0) + hcoc3/pow(tr[i],3.0))*(pow(pr[i],2.0) - pow(5000./pcr[i],2.0))/2.;
    gvp[i] = gvp[i] + (hcod1/tr[i] + hcod2*pow(tr[i],3.0))*(pow(pr[i],3.0) - pow(5000./pcr[i],3.0))/3.;

line7421:
    gvp[i] = gvp[i] + gvpk[i];
    salla_gv[i] = g1bar(i,t) + gvp[i];

//
//    *****  h2s  *****
//
//ccccccc
//  choosing the v(p,t) formulation in corresponding-state eos
//               of shi & saxena (1992)
//
    i = 9;

    pr[i] = p/pcr[i];
    tr[i] = t/tcr[i];

    if ((t <= 300.0) && (p <= 50.0)) {
        salla_vgas[i] = 10.0*rt/p;
        gvp[i] = rt*log(p);
        gvp[i] = gvp[i]/rt;
        salla_gv[i] = g1bar(i,t) + gvp[i];
    } else {

        if ((p > 500.01) || (p == 500.01)) goto line1171;
        gvpk[i] = 0.00;
        z[i] = 0.14721e+1 + 0.11177e+1*tr[i] +0.39657e+1/tr[i] -0.10028e+2/pow(tr[i],2.0) +0.45484e+1/pow(tr[i],3.0) -0.38200e+1*log(tr[i]);
        z[i] = z[i] + (0.16066e+0 +0.10887e+0*tr[i] +0.29014e+0/tr[i] -0.99593e+0/pow(tr[i],2.0) -0.18627e+0/pow(tr[i],3.0) -0.45515e+0*log(tr[i]))*pr[i];
        z[i] = z[i] + (-0.28933e+0 -0.70522e-1*tr[i] +0.39828e+0/tr[i] -0.50533e-1/pow(tr[i],2.0) +0.11760e+0/pow(tr[i],3.0) +0.33972e+0*log(tr[i]))*pow(pr[i],2.0);
        salla_vgas[i] = 10.*rt*z[i]/p;
        gvp[i] = (0.14721e+1 + 0.11177e+1*tr[i] +0.39657e+1/tr[i] -0.10028e+2/pow(tr[i],2.0) +0.45484e+1/pow(tr[i],3.0) -0.38200e+1*log(tr[i]))*log(p);
        gvp[i] = gvp[i] + (0.16066e+0 +0.10887e+0*tr[i] +0.29014e+0/tr[i] -0.99593e+0/pow(tr[i],2.0) -0.18627e+0/pow(tr[i],3.0) -0.45515e+0*log(tr[i]))*(pr[i] - 1.0/pcr[i]);
        gvp[i] = gvp[i] + (-0.28933e+0 -0.70522e-1*tr[i] +0.39828e+0/tr[i] -0.50533e-1/pow(tr[i],2.0) +0.11760e+0/pow(tr[i],3.0) +0.33972e+0*log(tr[i]))*(pow(pr[i],2.0) - pow(1.00/pcr[i],2.0))/2.;
        goto line1172;

    line1171:
        gvpk[i] = (0.14721e+1 + 0.11177e+1*tr[i] +0.39657e+1/tr[i] -0.10028e+2/pow(tr[i],2.0) +0.45484e+1/pow(tr[i],3.0) -0.38200e+1*log(tr[i]))*log(500.0);
        gvpk[i]=gvpk[i] + (0.16066e+0 +0.10887e+0*tr[i] +0.29014e+0/tr[i] -0.99593e+0/pow(tr[i],2.0) -0.18627e+0/pow(tr[i],3.0) -0.45515e+0*log(tr[i]))*(500./pcr[i] - 1.0/pcr[i]);
        gvpk[i]=gvpk[i] + (-0.28933e+0 -0.70522e-1*tr[i] +0.39828e+0/tr[i] -0.50533e-1/pow(tr[i],2.0) +0.11760e+0/pow(tr[i],3.0) +0.33972e+0*log(tr[i]))*(pow(500./pcr[i],2.0)-pow(1.0/pcr[i],2.0))/2.;
        z[i] = 0.60031e+0 + 0.18359e-3*tr[i] +0.46502e-1/tr[i] +0.36113e+0/pow(tr[i],2.0) -0.79708e+0/pow(tr[i],3.0) +0.25548e+0*log(tr[i]);
        z[i] = z[i] + (0.22329e-1 +0.17675e-2*tr[i] +0.48904e-1/tr[i] -0.20378e-1/pow(tr[i],2.0) +0.33047e-1/pow(tr[i],3.0) -0.11308e-1*log(tr[i]))*pr[i];
        z[i] = z[i] + (0.56686e-3 -0.42218e-5*tr[i] -0.11837e-2/tr[i] +0.14942e-2/pow(tr[i],2.0) -0.79541e-3/pow(tr[i],3.0) -0.26759e-3*log(tr[i]))*pow(pr[i],2.0);
        salla_vgas[i] = 10.*rt*z[i]/p;
        gvp[i] = (0.60031e+0 + 0.18359e-3*tr[i] +0.46502e-1/tr[i] +0.36113e+0/pow(tr[i],2.0) -0.79708e+0/pow(tr[i],3.0) +0.25548e+0*log(tr[i]))*log(p/500.);
        gvp[i] = gvp[i] + (0.22329e-1 +0.17675e-2*tr[i] +0.48904e-1/tr[i] -0.20378e-1/pow(tr[i],2.0) +0.33047e-1/pow(tr[i],3.0) -0.11308e-1*log(tr[i]))*(pr[i] - 500.0/pcr[i]);
        gvp[i] = gvp[i] + (0.56686e-3 -0.42218e-5*tr[i] -0.11837e-2/tr[i] +0.14942e-2/pow(tr[i],2.0) -0.79541e-3/pow(tr[i],3.0) -0.26759e-3*log(tr[i]))*(pow(pr[i],2.0) - pow(500.00/pcr[i],2.0))/2.;

    line1172:
        gvp[i] = gvp[i] + gvpk[i];
        salla_gv[i] = g1bar(i,t) + gvp[i];

    }

//
//    *****  n2, nh3, ar  *****
//
//ccccccc
//  choosing the v(p,t) formulation of molecular dynamics eos
//               of belonoshko and saxena (1992)
//
//
    i = 10;

    if (p < 5000.00) {
        salla_vgas[i] = 10.0*rt/p;
        gvp[i] = rt*log(p);
        gvp[i] = gvp[i]/rt;
        salla_gv[i] = g1bar(i,t) + gvp[i];
    } else {
        gvp[i] = 1000.0*(-80.094 + 63.916*t/1000.0 + 13.616*log(t));
        gvp[i] = gvp[i]/rt;
        salla_gv[i] = g1bar(i,t) + gvp[i];
    }

//
    i = 11;

    if (p < 5000.00) {
        salla_vgas[i] = 10.0*rt/p;
        gvp[i] = rt*log(p);
        gvp[i] = gvp[i]/rt;
        salla_gv[i] = g1bar(i,t) + gvp[i];
    } else {
        gvp[i] = 1000.0*(-3.873 + 70.171*t/1000.0 + 2.302*log(t));
        gvp[i] = gvp[i]/rt;
        salla_gv[i] = g1bar(i,t) + gvp[i];
    }

//
    i = 12;

    if (p < 5000.00) {
        salla_vgas[i] = 10.0*rt/p;
        gvp[i] = rt*log(p);
        gvp[i] = gvp[i]/rt;
        salla_gv[i] = g1bar(i,t) + gvp[i];
    } else {
        gvp[i] = 1000.0*(-5.238 + 69.179*t/1000.0 + 3.102*log(t));
        gvp[i] = gvp[i]/rt;
        salla_gv[i] = g1bar(i,t) + gvp[i];
    }
}

static void shi(double *x, double t, double p, double *v, double *gshi, double *gi) {
    double gpvt[LA], rt, vvvvv, gv[13], eps0;
    int m;

    stext_ident[ 0] = "h2o";
    stext_ident[ 1] = "co2";
    stext_ident[ 2] = "ch4";
    stext_ident[ 3] = "co";
    stext_ident[ 4] = "o2";
    stext_ident[ 5] = "h2";
    stext_ident[ 6] = "s2";
    stext_ident[ 7] = "so2";
    stext_ident[ 8] = "cos";
    stext_ident[ 9] = "h2s";
    stext_ident[10] = "n2";
    stext_ident[11] = "nh3";
    stext_ident[12] = "ar";
    //
    rt = 8.31451*t;
    //
    
    m = 0;
    salli_mf[m] = 0;
    salli_ml[m] = 12;
    
    //    calculation of pure fluid species:
    gas(t, p, &vvvvv, gv);
    
    //    calculation of fluid mixtures:
    if ( t < 1873.0)  factor(m, x, t, p, v);
    *gshi = 0.0;
    eps0 = 1.0e-50;
    *v = 0.0;
    
    for (int i=0; i<13; i++) {
        gpvt[i] = salla_gv[i]*rt;
        if (x[i] > eps0) {
            if ( t > 1873.0) gpvt[i] = gpvt[i] + sallr_aktfln[i]*rt;
        }
        *v += salla_vgas[i]*x[i];
        gi[i] = gpvt[i];
        *gshi += + gpvt[i]*x[i];
    }

    return;
}

static void ase (double *x, double *alx, double *sgmx, double *epskx) {
    double alij[13][13] = {
        12.75,13.31,13.38,13.59,13.57,13.04,12.72,12.99,13.07,13.11,
        13.00,13.10,12.87,13.31,13.90,13.97,14.19,14.17,13.62,13.28,
        13.57,13.65,13.68,13.58,13.67,13.44,13.38,13.97,14.05,14.26,
        14.25,13.69,13.35,13.64,13.72,13.76,13.65,13.75,13.51,13.59,
        14.19,14.26,14.48,14.46,13.90,13.56,13.85,13.93,13.97,13.86,
        13.96,13.72,13.57,14.17,14.25,14.46,14.45,13.88,13.54,13.83,
        13.92,13.95,13.84,13.94,13.71,13.04,13.62,13.69,13.90,13.88,
        13.34,13.01,13.29,13.37,13.40,13.30,13.39,13.17,12.72,13.28,
        13.35,13.56,13.54,13.01,12.69,12.96,13.04,13.07,12.97,13.06,
        12.84,12.99,13.57,13.64,13.85,13.83,13.29,12.96,13.24,13.32,
        13.36,13.25,13.35,13.12,13.07,13.65,13.72,13.93,13.92,13.37,
        13.04,13.32,13.40,13.43,13.33,13.42,13.20,13.11,13.68,13.76,
        13.97,13.95,13.40,13.07,13.36,13.43,13.47,13.36,13.46,13.23,
        13.00,13.58,13.65,13.86,13.84,13.30,12.97,13.25,13.33,13.36,
        13.26,13.35,13.13,13.10,13.67,13.75,13.96,13.94,13.39,13.06,
        13.35,13.42,13.46,13.35,13.45,13.22,12.87,13.44,13.51,13.72,
        13.71,13.17,12.84,13.12,13.20,13.23,13.13,13.22,13.00
    };
    double epskij[13][13] = {
        446.7,297.9,250.9,201.4,210.8,106.0,220.7,343.1,333.4,348.9,
        218.8,362.2,233.4,297.9,198.6,167.3,134.3,140.6, 70.7,147.1,
        228.8,222.4,232.6,145.9,241.5,155.7,250.9,167.3,140.9,113.1,
        118.4, 59.5,123.9,192.7,187.3,196.0,122.9,203.4,131.1,201.4,
        134.3,113.1, 90.8, 95.1, 47.8, 99.5,154.7,150.3,157.3, 98.7,
        163.3,105.3,210.8,140.6,118.4, 95.1, 99.5, 50.0,104.1,161.9,
        157.4,164.7,103.3,170.9,110.2,106.0, 70.7, 59.5, 47.8, 50.0,
        25.1, 52.4, 81.4, 79.1, 82.8, 51.9, 85.9, 55.4,220.7,147.1,
        123.9, 99.5,104.1, 52.4,109.0,169.5,164.7,172.3,108.1,178.9,
        115.3,343.1,228.8,192.7,154.7,161.9, 81.4,169.5,263.5,256.1,
        268.0,168.1,278.1,179.3,333.4,222.4,187.3,150.3,157.4, 79.1,
        164.7,256.1,248.9,260.4,163.3,270.3,174.3,348.9,232.6,196.0,
        157.3,164.7, 82.8,172.3,268.0,260.4,272.5,170.9,282.8,182.3,
        218.8,145.9,122.9, 98.7,103.3, 51.9,108.1,168.1,163.3,170.9,
        107.2,177.4,114.4,362.2,241.5,203.4,163.3,170.9, 85.9,178.9,
        278.1,270.3,282.8,177.4,293.6,189.3,233.4,155.7,131.1,105.3,
        110.2, 55.4,115.3,179.3,174.3,182.3,114.4,189.3,122.0
    };
    double sgmij[13][13] = {
        2.844,3.270,3.280,3.249,3.106,2.911,3.103,3.279,3.500,3.267,
        3.265,3.039,3.138,3.270,3.696,3.706,3.675,3.533,3.337,3.530,
        3.705,3.926,3.693,3.691,3.465,3.564,3.280,3.706,3.717,3.685,
        3.543,3.347,3.540,3.715,3.936,3.703,3.701,3.475,3.574,3.249,
        3.675,3.685,3.653,3.511,3.316,3.508,3.683,3.904,3.671,3.669,
        3.444,3.542,3.106,3.533,3.543,3.511,3.369,3.173,3.366,3.541,
        3.762,3.529,3.527,3.301,3.400,2.911,3.337,3.347,3.316,3.173,
        2.978,3.170,3.346,3.567,3.334,3.332,3.106,3.204,3.103,3.530,
        3.540,3.508,3.366,3.170,3.363,3.538,3.759,3.526,3.524,3.299,
        3.397,3.279,3.705,3.715,3.683,3.541,3.346,3.538,3.713,3.934,
        3.702,3.699,3.474,3.572,3.500,3.926,3.936,3.904,3.762,3.567,
        3.759,3.934,4.155,3.922,3.920,3.695,3.793,3.267,3.693,3.703,
        3.671,3.529,3.334,3.526,3.702,3.922,3.690,3.688,3.462,3.560,
        3.265,3.691,3.701,3.669,3.527,3.332,3.524,3.699,3.920,3.688,
        3.685,3.460,3.558,3.039,3.465,3.475,3.444,3.301,3.106,3.299,
        3.474,3.695,3.462,3.460,3.234,3.333,3.138,3.564,3.574,3.542,
        3.400,3.204,3.397,3.572,3.793,3.560,3.558,3.333,3.431
    };
    double ax = 0.0;
    double bx = 0.0;
    double cx = 0.0;
    double xex = 1.e-8;
    for (int i=0; i<13; i++) {
        if ( abs(x[i]) <= xex ) continue;
        for (int j=0; j<13; j++) {
            double xxs3 = 0.0;
            if ( abs( x[j]) <= xex) continue;
            xxs3 = x[i]*x[j]*pow(sgmij[i][j],3.0);
            ax = ax + xxs3*epskij[i][j];
            bx = bx + xxs3;
            cx = cx + xxs3*alij[i][j]*epskij[i][j];
        }
    }

    *sgmx  = pow(bx,0.333333333);
    *epskx = ax/bx;
    *alx   = cx/ax;

    return;
}

static void flint(double *x, double t, double *v, double *pvint) {
    double xc[29] = {
        0.93505310752561688, 1.73699892000011591,-1.30975098740699658,
        -9.14208223585147906, 1.12375121360917096, 1.94532994383712232,
        18.05270668458713600,-0.60332346345947818, 0.97658909559961082,
        3.57911846557894275,-9.81360148740191462,-22.7287168733673468,
        6.22413763992105906, 4.38140919236828275, 4.85395992796371711,
        -0.57662210159049076,-4.11150218637956932,-6.64748141694619399,
        2.71569335746679119,-4.78315896838355048, 2.18540232889916641,
        -1.03805953902260817, 0.91537388843150680, 0.90857123024103514,
        -0.0922267363251438182,-0.60401350198636927, 0.64619486687215066,
        2.89574909131718927,     -11.34438696840113890
    };
    double alx, sgmx, epskx, pcoeff, tcoeff, vcoeff, ti, ti2, ti3, vi, ali, al1;
    double x24, x25, x26, x27, a, b, c, f, g, dt, et, al12,first, secnd, third, vig, avi, avig, edvi, edvi2, edvi3, edvi4;
    double a1, a2, a3, b1, b2, b3, f1, f2, f3, am, c1, c2, c3, ai1, ai2, ai3, aicom;

    ase (x, &alx, &sgmx, &epskx);
    pcoeff = 0.06022/8.31451*pow(sgmx,3.0)/epskx;
    tcoeff = 1.0/epskx;
    vcoeff = 10.0/6.022/pow(sgmx,3.0);

    ti = t * tcoeff;
    ti2 = ti*ti;
    ti3 = ti2*ti;
    vi = (*v) * vcoeff;
    ali = alx;

    x24 = xc[23]/10.0;
    x25 = xc[24]/10.0;
    x26 = xc[25]/10.0;
    x27 = xc[26]/10.0;
    al1 = ali - 12.75;

    a  = xc[ 0] + xc[ 1]*ti + xc[ 2]/100.0*ti2+xc[14]/10000.0*ti3;
    b  = xc[ 3] + xc[ 4]*ti + xc[ 5]/100.0*ti2+xc[15]/10000.0*ti3;
    c  = xc[ 6] + xc[ 7]*ti + xc[ 8]/100.0*ti2+xc[16]/100000.0*ti3;
    f  = xc[17] + xc[18]*ti + xc[19]/100.0*ti2+xc[20]/10000.0*ti3;
    g  = xc[27]/10.0 + xc[28]/100.0*ti;
    dt = xc[ 9]/10   + xc[10]/1000*ti+xc[21]/ti;
    et = xc[11]/100  + xc[12]/1000*ti+xc[22]/ti;

    al12 = pow(al1,2.0);
    first = 1.0 + dt*al1 + et*al12;
    secnd = x24*al1 + x26*al12;
    third = x25*al1 + x27*al12;
    vig = vi - g;
    avi = log(vi);
    avig = log(vig);
    edvi = 1.0/vi;
    edvi2 = pow(edvi,2.0);
    edvi3 = edvi2*edvi;
    edvi4 = edvi3*edvi;

    a1 = a*avig;
    a2 = a*( vi + g*avig);
    a3 = a/g*(avig-avi );

    b1 = -b*edvi;
    b2 = b*avi;
    b3 = -0.5*b*edvi2;

    f1 = -0.5*f*edvi2;
    f2 = -f*edvi;
    f3 = -f/3.0*edvi3;

    am = xc[13];
    c1 = c/(1.0-am)*pow(vi,1.0-am);
    c2 = c/(2.0-am)*pow(vi,2.0-am);
    c3 = -c/am*pow(vi,-am);

    ai1 = (a1+b1+f1+c1)*first;
    ai2 = (a2+b2+f2+c2)*secnd;
    ai3 = (a3+b3+f3+c3)*third;

    aicom = ai1 + ai2 + ai3;

    *pvint = aicom /(pcoeff*vcoeff);

    return;
}

static void tvpm (double *x, double t, double v, double *p) {
    double xc[29] = {
        0.49379340772561688, 1.77136719000011591,-1.24397358740699658,
        -8.22738223585147906, 1.26639755360917096, 1.71431494383712232,
        18.85767400958713600,-0.64967289865577738, 1.10631892859961082,
        3.43201986557894275,-11.61223156310191462,-24.0910798733673468,
        7.15468164992105906, 4.35243253136828275, 7.40801022796371711,
        -0.43490428159049076,-5.05471913647956932,-8.41696486054619399,
        2.81828771146679119,-5.20493168328355048, 2.65003464989916641,
        -1.17589498191260817, 1.00911476826150680, 1.18264255424103514,
        0.1021732463251438182,-0.63676820398636927, 0.60142122204215066,
        3.95204218076118927,  -15.63920064084153890
    };
    double alx, sgmx, epskx;
    double edeps, sgmx3, pcoeff, tcoeff, vcoeff, ti, ti2, ti3, vi, ali, ti100, ti1000;
    double a, b, c, f, g, d, e, pc, alk;

    ase (x, &alx, &sgmx, &epskx);
    edeps = 1.0/epskx;
    sgmx3 = pow(sgmx, 3.0);
    pcoeff = 0.06022/8.31451*sgmx3*edeps;
    tcoeff = edeps;
    vcoeff = 10.0/6.022/sgmx3;

    ti  = t * tcoeff;
    ti2 = ti*ti;
    ti3 = ti2*ti;
    vi  = v * vcoeff;
    ali = alx;
    ti100  = ti2/100.0;
    ti1000 = ti3/10000.0;

    a = xc[ 0] + xc[ 1]*ti + xc[ 2]*ti100+xc[14]*ti1000;
    b = xc[ 3] + xc[ 4]*ti + xc[ 5]*ti100+xc[15]*ti1000;
    c = xc[ 6] + xc[ 7]*ti + xc[ 8]*ti100+xc[16]/100000.0*ti3;
    f = xc[17] + xc[18]*ti + xc[19]*ti100+xc[20]*ti1000;
    g = xc[27]/10.0 + xc[28]/100.0*ti;
    d = xc[ 9]/10+xc[10]/1000*ti+xc[21]/ti+xc[23]/10*vi+xc[24]/vi/10;
    e = xc[11]/100+xc[12]/1000*ti+xc[22]/ti+xc[25]/10*vi+xc[26]/vi/10;

    pc = a/(vi-g) + b/pow(vi,2.0) +f/pow(vi,3.0) + c/pow(vi,xc[13]);
    alk = 1.0 + d*(ali-12.75)+e*pow(ali-12.75,2.0);
    pc = pc*alk;
    *p = pc/pcoeff;

    return;
}

static void vdp (void (*funct)(double *, double, double, double *),
                double eps, double *x, double t, double vst, double vfin, double *vdpint) {
    double pfin, pst, pvintf, pvints, s1;
    funct (x, t, vfin, &pfin);
    funct (x, t, vst, &pst);

    flint (x, t, &vfin, &pvintf);
    flint (x, t, &vst , &pvints);
    s1 = pvints - pvintf;
    *vdpint = (pfin*vfin - pst*vst + s1)/10.0;
    return;
}

static void tolja (double *x, double t, double p, double *v, double *gdivp) {
    double v0meg[13] = {
        6.65,10.94,10.46,9.46,7.97,3.92,7.19,10.92,14.22, 11.0, 9.0, 8.16, 7.77
    };
    double v0fif[13] = {
        12.4,20.8,20.17,18.39,15.5,8.8,14.4,20.8,27.2,20.8, 18.0,15.3,15.4
    };

    double eps = 0.00001;
    double v0  = 20.0;
    double p5 = 5000.0;
    double v5;
    nr (tvpm, eps, x, t, p5, v0, &v5);

    if ( p <= 50000.0) {
        v0 = 0.0;
        for (int i=0; i<13; i++) v0 += x[i]*v0fif[i];
    }
    if ( p > 50000.0) {
        v0 = 0.0;
        for (int i=0; i<13; i++) v0 += x[i]*v0meg[i];
    }

    nr (tvpm, eps, x, t, p, v0, v);
    vdp (tvpm, eps, x,t, v5, *v, gdivp);

    return;
}

static void fluid(double *x, double t, double p, double *v, double *g) {
    double gi[NE];
    double pdiv = 4999.0;
    double tdiv = 400.0;

    if (x[1] > 0.0000001) tdiv = 700.0;
    if ((t < tdiv) || (p < pdiv)) {
        shi(x, t, p, v, g, gi);
    } else {
        double gdiv, gdivp;
        shi(x, t, p, v, &gdiv, gi);
        tolja(x, t, p, v, &gdivp);
        *g = gdiv + gdivp;
    }
}

static void xtoxdx(int j, double *x, double *xdxj, double dnj, double prod) {
    double bulk[NE];
    double s = 0.0;
    for (int i=0; i<NE; i++) {
        bulk[i] = x[i]*prod;
        s += bulk[i];
    }
    bulk[j] = bulk[j] + dnj*prod;
    s += dnj*prod;
    for (int i=0; i<NE; i++) xdxj[i] = bulk[i]/s;
}

static void flder(double t, double p, double *x, double *v, double *g, double *mu) {
    double xdxi[NE];
    double xexist = 1.e-45;
    double prod, dni;

    fluid (x, t, p, v, g);
    prod = 1000.0;
    dni = 0.001;
    for (int i=0; i<NE; i++) {
        mu[i] = 0.0;
        if ( x[i] > xexist) {
            double vd, gplus;
            xtoxdx(i, x, xdxi, dni, prod);
            fluid(xdxi, t, p, &vd, &gplus);
            mu[i] = (gplus*(1.0 + dni) - *g)/dni;
        }
    }
}

static void fder(double t, double p, double*x, double *v, double *g, double *mu) {
    double xstep = 1.e-8;
    
    for (int i=0; i<NE; i++) if ((x[i] > 0.0) && (x[i] <= xstep)) x[i] = xstep;
    flder(t, p, x, v, g, mu);
    
    for (int i=0; i<NE; i++) if (x[i] > 0.0) *g += 8.3143*t*x[i]*log(x[i]);
    for (int i=0; i<NE; i++) if (x[i] > 0.0) mu[i] += 8.3143*t*log(x[i]);
}

static int superfluid(double t, double p, double *x, double *g, double *mu) {
    double v, gSum = 0.0;
    double xPure[13] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    int i;
    
    fder(t, p, x, &v, g, mu);

    for (i=0; i<NE; i++) {
        double gamma = 1.0, fugacity = 1.0;
        double v1bar, g1bar, vbar, gbar;

        gSum += mu[i]*x[i];
        xPure[i] = 1.0;

        fluid(xPure, t, 1.0, &v1bar, &g1bar);
        fluid(xPure, t, p,   &vbar,  &gbar);

        xPure[i] = 0.0;
        if (x[i] > 0.0) {
            gamma = mu[i] - g1bar - 8.3143*t*log(p);
            fugacity = gbar - g1bar - 8.3143*t*log(p);
            gamma = exp(gamma/(8.3143*t))/x[i];
            fugacity = exp(fugacity/(8.3143*t));
            gamma /= fugacity;
        } else {
            gamma = 1.0;
            fugacity = exp(fugacity/(8.3143*t));
        }
    }
    
    return TRUE;
}

/*
 * ==========================================================
 * End FORTRAN conversion code from Superfluid
 */

#ifdef DEBUG
static int choldc(double **a, int n) {
    int i,j,k;
    double sum, *p;
    
    p = vector(0,n-1);
    for (i=0;i<n;i++) {
        for (j=i;j<n;j++) {
            for (sum=a[i][j],k=i-1;k>=0;k--) sum-=a[i][k]*a[j][k];
            if (i==j) {
                if (sum <= 0.0) return FALSE;
                p[i] = sqrt(sum);
            } else a[j][i] = sum/p[i];
        }
    }
    free_vector(p,0,n-1);
    return TRUE;
}
#endif

#define TINY 1.0e-20;

static void ludcmp(double **a, int n, int *indx, double *d) {
    int i,imax=-1,j,k;
    double big,dum,sum,temp;
    double *vv,*vector();
    void nrerror(),free_vector();
    
    vv=vector(1,n);
    *d=1.0;
    for (i=1;i<=n;i++) {
        big=0.0;
        for (j=1;j<=n;j++)
            if ((temp=fabs(a[i][j])) > big) big=temp;
        if (big == 0.0) nrerror("Singular matrix in routine LUDCMP");
        vv[i]=1.0/big;
    }
    for (j=1;j<=n;j++) {
        for (i=1;i<j;i++) {
            sum=a[i][j];
            for (k=1;k<i;k++) sum -= a[i][k]*a[k][j];
            a[i][j]=sum;
        }
        big=0.0;
        for (i=j;i<=n;i++) {
            sum=a[i][j];
            for (k=1;k<j;k++)
                sum -= a[i][k]*a[k][j];
            a[i][j]=sum;
            if ( (dum=vv[i]*fabs(sum)) >= big) {
                big=dum;
                imax=i;
            }
        }
        if (j != imax) {
            for (k=1;k<=n;k++) {
                dum=a[imax][k];
                a[imax][k]=a[j][k];
                a[j][k]=dum;
            }
            *d = -(*d);
            vv[imax]=vv[j];
        }
        indx[j]=imax;
        if (a[j][j] == 0.0) a[j][j]=TINY;
        if (j != n) {
            dum=1.0/(a[j][j]);
            for (i=j+1;i<=n;i++) a[i][j] *= dum;
        }
    }
    free_vector(vv,1,n);
}

#undef TINY

static void lubksb(double **a, int n, int *indx, double b[]) {
    int i,ii=0,ip,j;
    double sum;
    
    for (i=1;i<=n;i++) {
        ip=indx[i];
        sum=b[ip];
        b[ip]=b[i];
        if (ii)
            for (j=ii;j<=i-1;j++) sum -= a[i][j]*b[j];
        else if (sum) ii=i;
        b[i]=sum;
    }
    for (i=n;i>=1;i--) {
        sum=b[i];
        for (j=i+1;j<=n;j++) sum -= a[i][j]*b[j];
        b[i]=sum/a[i][i];
    }
}

static void mprove(double **a, double **alud, int n,int *indx, double b[], double x[]) {
    int j,i;
    double sdp;
    double *r,*vector();
    void lubksb(),free_vector();
    
    r=vector(1,n);
    for (i=1;i<=n;i++) {
        sdp = -b[i];
        for (j=1;j<=n;j++) sdp += a[i][j]*x[j];
        r[i]=sdp;
    }
    lubksb(alud,n,indx,r);
    for (i=1;i<=n;i++) x[i] -= r[i];
    free_vector(r,1,n);
}

static void initialGuessOrdering(double r[NR], double s[NT]) {
    int i;
    static double *sCorr;
    double factor = 1.0;
    
    if (NT == 0) return;
    
#ifdef DEBUG
    printf("Call to initialGuessOrdering in liquid.c\n");
#endif
    if (sCorr == NULL) sCorr = (double *) malloc((size_t) NS*sizeof(double));
    
    for (i=0; i<NS; i++)  s[i] = 0.0;
    for (i=NS; i<NT; i++) s[i] = 1.0/(((double) NY)+1.0);
    
    if (!rANDsTOx (r, s)) {
        static const int indexCon[] = { 0, 10, 14 };
        /* [ 0] SiO2 [10] CaO [14] CO2 */
        static const int nCon = 3;
        static double **a, *sMin, *sMax, tolerance;
        static int *iposv, *izrov;
        int j, m1, m2, m3, m, n, icase;
        
        if (a == NULL) {
            a     = matrix(1, nCon+2, 1, NS+1);
            sMin  = vector(0, NS-1);
            sMax  = vector(0, NS-1);
            iposv = ivector(1, nCon);
            izrov = ivector(1, NS);
            tolerance = pow(DBL_EPSILON, (double) (2.0/3.0));
        }
        
#ifdef DEBUG
        printf("Setting up for a call to the Simplex method:\n");
        for (i=0; i<nCon; i++) {
            printf("%10.10s %6.3f ", liquid[indexCon[i]].label, xSpecies[indexCon[i]]);
            for (j=0; j<NS; j++) printf(" %6.3f", dxSpeciesds[indexCon[i]][j]);
            printf("\n");
        }
#endif
        
        /***********************************/
        /* Find minimum length Soln vector */
        /***********************************/
        
        /* objective fucntion row for finding minimum length solution vector that satisfies constraints */
        a[1][1] = 0.0; for (i=0; i<NS; i++) a[1][2+i] = -1.0;
        /* remainder of the tableau */
        for (i=0, m1=0; i<nCon; i++) if (-xSpecies[indexCon[i]]  < 0.0) {
            m1++; a[1+m1][1] = xSpecies[indexCon[i]];  for (j=0; j<NS; j++) a[1+m1][2+j] = dxSpeciesds[indexCon[i]][j];
        }
        for (i=0, m2=0; i<nCon; i++) if (-xSpecies[indexCon[i]]  > 0.0) {
            m2++; a[1+m1+m2][1] = -xSpecies[indexCon[i]]; for (j=0; j<NS; j++) a[1+m1+m2][2+j] = -dxSpeciesds[indexCon[i]][j];
        }
        for (i=0, m3=0; i<nCon; i++) if (-xSpecies[indexCon[i]] == 0.0) {
            m3++; a[1+m1+m2+m3][1] = 0.0; for (j=0; j<NS; j++) a[1+m1+m2+m3][2+j] = -dxSpeciesds[indexCon[i]][j];
        }
        
        m = nCon; n = NS;
        
#ifdef DEBUG
        for (i=1; i<=(m+1); i++) {
            for (j=1; j<=(n+1); j++) printf("%6.3f ", a[i][j]);
            printf("\n");
        }
        printf("Making call to the Simplex method: m1 = %d, m2 = %d, m3 = %d, m = %d, n = %d\n", m1, m2, m3, m, n);
#endif
        
        simplx(a, m, n, m1, m2, m3, &icase, izrov, iposv);
        
#ifdef DEBUG
        printf("Tableau output from the Simplex method:\n");
        for (i=1; i<=(m+1); i++) {
            for (j=1; j<=(n+1); j++) printf("%6.3f ", a[i][j]);
            printf("\n");
        }
        printf("icase = %d\n", icase);
        printf("izrov = "); for (j=1; j<=n; j++) printf("%d ", izrov[j]); printf("\n");
        printf("iposv = "); for (j=1; j<=m; j++) printf("%d ", iposv[j]); printf("\n");
        
        printf("Solution:\n");
        for (j=1; j<=m; j++) if ((i = iposv[j]) <= n) printf("s[%15.15s] = %g\n", liquid[nlc+i-1].label, a[j+1][1]);
        for (j=1; j<=n; j++) if ((i = izrov[j]) <= n) printf("s[%15.15s] = %g\n", liquid[nlc+i-1].label, 0.0);
#endif
        
        /* if (icase != 0) return; */
        
        for (j=1; j<=m; j++) if ((i = iposv[j]) <= n) sMin[i-1] = a[j+1][1];
        for (j=1; j<=n; j++) if ((i = izrov[j]) <= n) sMin[i-1] = 0.0;
        
        /***********************************/
        /* Find maximum length Soln vector */
        /***********************************/
        
        /* objective fucntion row for finding maximum length solution vector that satisfies constraints */
        a[1][1] = 0.0; for (i=0; i<NS; i++) a[1][2+i] = 1.0;
        /* remainder of the tableau */
        for (i=0, m1=0; i<nCon; i++) if (-xSpecies[indexCon[i]]  < 0.0) {
            m1++; a[1+m1][1] = xSpecies[indexCon[i]];  for (j=0; j<NS; j++) a[1+m1][2+j] = dxSpeciesds[indexCon[i]][j];
        }
        for (i=0, m2=0; i<nCon; i++) if (-xSpecies[indexCon[i]]  > 0.0) {
            m2++; a[1+m1+m2][1] = -xSpecies[indexCon[i]]; for (j=0; j<NS; j++) a[1+m1+m2][2+j] = -dxSpeciesds[indexCon[i]][j];
        }
        for (i=0, m3=0; i<nCon; i++) if (-xSpecies[indexCon[i]] == 0.0) {
            m3++; a[1+m1+m2+m3][1] = 0.0; for (j=0; j<NS; j++) a[1+m1+m2+m3][2+j] = -dxSpeciesds[indexCon[i]][j];
        }
        
        m = nCon; n = NS;
        
#ifdef DEBUG
        for (i=1; i<=(m+1); i++) {
            for (j=1; j<=(n+1); j++) printf("%6.3f ", a[i][j]);
            printf("\n");
        }
        printf("Making call to the Simplex method: m1 = %d, m2 = %d, m3 = %d, m = %d, n = %d\n", m1, m2, m3, m, n);
#endif
        
        simplx(a, m, n, m1, m2, m3, &icase, izrov, iposv);
        
#ifdef DEBUG
        printf("Tableau output from the Simplex method:\n");
        for (i=1; i<=(m+1); i++) {
            for (j=1; j<=(n+1); j++) printf("%6.3f ", a[i][j]);
            printf("\n");
        }
        printf("icase = %d\n", icase);
        printf("izrov = "); for (j=1; j<=n; j++) printf("%d ", izrov[j]); printf("\n");
        printf("iposv = "); for (j=1; j<=m; j++) printf("%d ", iposv[j]); printf("\n");
        
        printf("Solution:\n");
        for (j=1; j<=m; j++) if ((i = iposv[j]) <= n) printf("s[%15.15s] = %g\n", liquid[nlc+i-1].label, a[j+1][1]);
        for (j=1; j<=n; j++) if ((i = izrov[j]) <= n) printf("s[%15.15s] = %g\n", liquid[nlc+i-1].label, 0.0);
#endif
        
        /* if (icase != 0) return; */
        
        for (j=1; j<=m; j++) if ((i = iposv[j]) <= n) sMax[i-1] = a[j+1][1];
        for (j=1; j<=n; j++) if ((i = izrov[j]) <= n) sMax[i-1] = 0.0;
        
        /***************************************************************/
        /* Return average of two solutions - should always be feasible */
        /***************************************************************/
        
        for (i=0; i<NS; i++) {
            s[i] = (sMin[i] + sMax[i])/2.0;
            if (fabs(s[i]) < tolerance) s[i] = 0.0;
        }
        
        if(!rANDsTOx (r, s)) fprintf(stderr, "Simplex method suceeded but failed to find feasible solution in initialGuessOrdering.\n");
        
        for (i=NS; i<NT; i++) s[i] = 1.0/(((double) NY)+1.0);
        
#ifdef DEBUG
        printf("Results of call to initialGuessOrdering:\n");
        printf("   %20.20s %13.13s %13.13s %13.13s\n", "Species", "Mole frac", "r", "s");
        printf("   %20.20s %13.6g\n", liquid[0].label, xSpecies[0]);
        for (i=0;  i<NR; i++) printf("   %20.20s %13.6g %13.6g\n", liquid[i+1].label, xSpecies[i+1], r[i]);
        for (i=0;  i<NS; i++) printf("   %20.20s %13.6g %13.13s %13.6g\n", liquid[i+NA].label, xSpecies[i+NA], "", s[i]);
        for (i=NS; i<NT; i++) printf("   %20.20s %13.13s %13.13s %13.6g\n", "order CN[*]", "", "", s[i]);
#endif
        
        return;
    } /* end block on simplex method */
    
    for (i=0; i<NS; i++) {
        sCorr[i] = 0.0; s[i] = sqrt(DBL_EPSILON);
        if (!rANDsTOx (r, s)) s[i] = 0.0;
        else {
            sCorr[i] = 0.5; s[i] = 1.0;
            while (sCorr[i] > sqrt(DBL_EPSILON)) {
                if(!rANDsTOx (r, s)) s[i] -= sCorr[i]; else s[i] += sCorr[i];
                sCorr[i] /= 2.0;
            }
        }
        sCorr[i] = s[i]/2.0;
        s[i]     = 0.0;
    }
    
    for (i=0; i<NS; i++) s[i] = sCorr[i];
    while (factor > sqrt(DBL_EPSILON) && !rANDsTOx (r, s)) {
        factor /= 2.0;
        for (i=0; i<NS; i++) s[i] = sCorr[i]*factor;
    }
    
    for (i=NS; i<NT; i++) s[i] = 1.0/(((double) NY)+1.0);
    
#ifdef DEBUG
    printf("Results of call to initialGuessOrdering:\n");
    printf("   %20.20s %13.13s %13.13s %13.13s\n", "Species", "Mole frac", "r", "s");
    printf("   %20.20s %13.6g\n", liquid[0].label, xSpecies[0]);
    for (i=0;  i<NR; i++) printf("   %20.20s %13.6g %13.6g\n", liquid[i+1].label, xSpecies[i+1], r[i]);
    for (i=0;  i<NS; i++) printf("   %20.20s %13.6g %13.13s %13.6g\n", liquid[i+NA].label, xSpecies[i+NA], "", s[i]);
    for (i=NS; i<NT; i++) printf("   %20.20s %13.13s %13.13s %13.6g\n", "order CN[*]", "", "", s[i]);
#endif
}


static void
order(int mask, double t, double p, double r[NR],
      double s[NT],            /* s[NT]                  BINARY MASK: 000000000001 */
      double dr[NT][NR] ,      /* ds[NT]/dr[NR]          BINARY MASK: 000000000010 */
      double dt[NT],           /* ds[NT]/dt              BINARY MASK: 000000000100 */
      double dp[NT],           /* ds[NT]/dp              BINARY MASK: 000000001000 */
      double dr2[NT][NR][NR],  /* d2s[NT]/dr[NR]dr[NR]   BINARY MASK: 000000010000 */
      double drt[NT][NR],      /* d2s[NT]/dr[NR]dt       BINARY MASK: 000000100000 */
      double drp[NT][NR],      /* d2s[NT]/dr[NR]dp       BINARY MASK: 000001000000 */
      double dt2[NT],          /* d2s[NT]/dt2            BINARY MASK: 000010000000 */
      double dtp[NT],          /* d2s[NT]/dtp            BINARY MASK: 000100000000 */
      double dp2[NT]           /* d2s[NT]/dp2            BINARY MASK: 001000000000 */
)
{
    static double tOld = -9999.0;
    static double pOld = -9999.0;
    static double *rOld, *sOld, **ptToD2gds2, **d2gds2, **ptToD2gds2Copy, **d2gds2Copy, dLU;
    static int *indexLU;
    int i, j, iter=0, doAbort=FALSE, update=FALSE, loop;
    
    if (ptToD2gds2 == NULL) {
        d2gds2      = matrix(0, NT-1, 0, NT-1); /* must be local */
        d2gds2Copy  = matrix(0, NT-1, 0, NT-1);
        ptToD2gds2  = (double **) malloc((size_t) NT*sizeof(double *));
        ptToD2gds2 -= 1; /* index ptToD2gds2[1:NT][] */
        for (i=0; i<NT; i++) ptToD2gds2[i+1] = d2gds2[i] - 1; /* index ptToD2gds2[][1:NT] */
        ptToD2gds2Copy  = (double **) malloc((size_t) NT*sizeof(double *));
        ptToD2gds2Copy -= 1; /* index ptToD2gds2Copy[1:NT][] */
        for (i=0; i<NT; i++) ptToD2gds2Copy[i+1] = d2gds2Copy[i] - 1; /* index ptToD2gds2Copy[][1:NT] */
        rOld = vector(0, NR-1);
        sOld = vector(0, NT-1);
        for (i=0; i<NR; i++) rOld[i] = -9999.0;
        for (i=0; i<NT; i++) sOld[i] = 0.0;
        indexLU = ivector(1, NT);
    }
    
    update |= (t != tOld);
    update |= (p != pOld);
    for (i=0; i<NR; i++) update |= (r[i] != rOld[i]);
    
    /* look-up or compute the current ordering state */
    if (update) {                                     /* if T, P, meltsAndCO2_H2OModelParameters or liquid composition change */
        double sNew[NT], dgdsNORM=0.0;
        for (i=0; i<NT; i++) { sNew[i] = sOld[i]; sOld[i] = 2.0; }
        convergedInOrder = TRUE;
        
        initialGuessOrdering(r, sNew);
        if (!rANDsTOx (r, sNew)) {
            printf("Initial guess to ordering state iteration is infeasible\n");
            doAbort = TRUE;
        }
        if (doAbort) {
            printf("Results of call to ordering with bad initial guess:\n");
            printf("   %20.20s %13.13s %13.13s %13.13s\n", "Species", "Mole frac", "r", "s");
            printf("   %20.20s %13.6g\n", liquid[0].label, xSpecies[0]);
            for (i=0;  i<NR; i++) printf("   %20.20s %13.6g %13.6g\n",         liquid[i+1].label,  xSpecies[i+1],  r[i]);
            for (i=0;  i<NS; i++) printf("   %20.20s %13.6g %13.13s %13.6g\n", liquid[i+NA].label, xSpecies[i+NA], "", sNew[i]);
            for (i=NS; i<NT; i++) printf("   %20.20s %13.13s %13.13s %13.6g\n", "order CN[*]", "", "", sNew[i]);
            (void) raise(SIGABRT);
        }
        
        loop = TRUE;
        while (loop) {
            double s[NT], deltaS[NT], lambda=1.0, ptToDgds[NT], ptToDgdsCopy[NT];
            int cycle = TRUE /*, errGaussj */;
            
            for (i=0; i<NT; i++) s[i] = sNew[i];
            
            fillDGDS   (r, s, t, p, dgds);
            fillD2GDS2 (r, s, t, p, d2gds2);
            
            for (i=0, dgdsNORM=0.0; i<NT; i++) {
                sOld[i] = s[i];
                for (j=0; j<NT; j++) if (s[i] == 0.0 || s[j] == 0.0) d2gds2[i][j] = 0.0;
                if (s[i] == 0.0) {
                    d2gds2[i][i] = 1.0;
                    dgds[i]      = 0.0;
                }
                dgdsNORM += pow(dgds[i]/MAX(1.0, fabs(eosIntDGDS[i])), (double) 2.0);
            }
            dgdsNORM = sqrt(dgdsNORM);
            
            for (i=0; i<NT; i++) for (j=0; j<NT; j++) d2gds2Copy[i][j] = d2gds2[i][j];
            
#ifdef DEBUG
            if (!choldc(d2gds2Copy, NT)) printf("--->d2gds2 is NOT positive definite.\n");
            else                         printf("--->d2gds2 is positive definite.\n");
            for (i=0; i<NT; i++) for (j=0; j<NT; j++) d2gds2Copy[i][j] = d2gds2[i][j];
#endif
            
            for (i=0; i<NT; i++) { ptToDgds[i] = -dgds[i]; ptToDgdsCopy[i] = -dgds[i]; }
            
            ludcmp(ptToD2gds2, NT, indexLU, &dLU);
            lubksb(ptToD2gds2, NT, indexLU, ptToDgds-1);
#ifdef DEBUG
            printf("--->dels from lubksb:   ");
            for (i=0; i<NT; i++) printf("%20.13g", ptToDgds[i]);
            printf("\n");
#endif
            mprove(ptToD2gds2Copy, ptToD2gds2, NT, indexLU, ptToDgdsCopy-1, ptToDgds-1);
#ifdef DEBUG
            printf("--->dels after mprove:  ");
            for (i=0; i<NT; i++) printf("%20.13g", ptToDgds[i]);
            printf("\n");
#endif
            
            for (i=0; i<NT; i++) {
                s[i] += ptToDgds[i];
                deltaS[i] = s[i] - sOld[i];
            }
            
#ifdef DEBUG
            printf("--->dgds:   ");
            for (i=0; i<NT; i++) if (fabs(s[i]) > 10.0*DBL_EPSILON) printf("%20.13g", dgds[i]);
            printf("\n");
            for (j=0; j<NT; j++) if (fabs(s[j]) > 10.0*DBL_EPSILON) {
                printf("--->d2gds2[%d][]: ", j);
                for (i=0; i<NT; i++) if (fabs(s[i]) > 10.0*DBL_EPSILON) printf("%20.13g", d2gds2Copy[j][i]);
                printf("\n");
            }
            printf("--->s:      ");
            for (i=0; i<NT; i++) if (fabs(s[i]) > 10.0*DBL_EPSILON) printf("%20.13g", s[i]);
            printf("\n");
            printf("--->dels:   ");
            for (i=0; i<NT; i++) if (fabs(s[i]) > 10.0*DBL_EPSILON) printf("%20.13g", deltaS[i]);
            printf("\n");
#endif
            
            while (cycle && !rANDsTOx (r, s)) {
                lambda /= 2.0;
                for (j=0; j<NT; j++) s[j] = sOld[j] + lambda*deltaS[j];
                /*      if (lambda < DBL_EPSILON) { */
                if (lambda < DBL_MIN) {
                    cycle = FALSE;
                    s[0] = (double) iter;
                    iter = MAX_ITER - 1;
                    fprintf(stderr, "\n*****lambda -> zero in ORDER. Terminating search loop.\n");
                }
            }
#ifdef DEBUG
            printf("steplength correction:  = %20.13g\n", lambda);
            printf("--->s(adj): ");
            for (i=0; i<NT; i++) if (fabs(s[i]) > 10.0*DBL_EPSILON) printf("%20.13g", s[i]);
            printf("\n----- end -----\n");
#endif
            
            for (i=0; i<NT; i++) sNew[i] = s[i];
            iter++;
            loop = FALSE;
            if (iter < MAX_ITER) for (i=0; i<NT; i++) loop |= (fabs(sNew[i]-sOld[i]) > 10.0*DBL_EPSILON);
        }
        tOld = t;
        pOld = p;
        for (i=0; i<NR; i++) rOld[i] = r[i];
        
        (void) rANDsTOx (rOld, sOld);
        
        if (iter == MAX_ITER) {
            double sNorm;
            for (i=0, sNorm=0.0; i<NT; i++) sNorm += pow(sNew[i]-sOld[i], (double) 2.0);
            sNorm = sqrt(sNorm);
            if (sNorm > sqrt(DBL_EPSILON)) {
                /* convergedInOrder = FALSE; */
                fprintf(stderr, "ERROR in LIQUID.C (function ORDER). Failed to converge!\n");
                if (iter >= MAX_ITER) fprintf(stderr, " Iteration limit (%4d) exceeded.\n", iter);
                fprintf(stderr, "   T (C) = %8.2f, P (GPa) = %10.4f\n", t-273.15, p/10000.0);
                fprintf(stderr, "   %20.20s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s\n", "Species", "Mole frac", "r", "s", "dgds", "deltaS", "eosIntDGDS");
                fprintf(stderr, "   %20.20s %13.6g\n", liquid[0].label, xSpecies[0]);
                for (i=0;  i<NR; i++) fprintf(stderr, "   %20.20s %13.6g %13.6g\n",		 liquid[i+1].label,  xSpecies[i+1],  r[i]);
                for (i=0;  i<NS; i++) fprintf(stderr, "   %20.20s %13.6g %13.13s %13.6g %13.6g %13.6g %13.6g\n", liquid[i+NA].label, xSpecies[i+NA], "", sOld[i], dgds[i], sNew[i]-sOld[i], eosIntDGDS[i]);
                for (i=NS; i<NT; i++) fprintf(stderr, "   %20.20s %13.13s %13.13s %13.6g %13.6g %13.6g\n", "order CN[*]", "", "", sOld[i], dgds[i], sNew[i]-sOld[i]);
                fprintf(stderr, " sNorm             = %20.13g\n", sNorm);
                fprintf(stderr, " dgdsNorm          = %20.13g\n", dgdsNORM);
                fprintf(stderr, " 10*DBL_EPSILON    = %20.13g\n", 10.0*DBL_EPSILON);
                fprintf(stderr, " DBL_EPSILON^(2/3) = %20.13g\n", pow(DBL_EPSILON, 2.0/3.0));
                fprintf(stderr, " DBL_EPSILON^(1/2) = %20.13g\n", sqrt(DBL_EPSILON));
                fprintf(stderr, " eosIntegralBranch = %s\n", (eosIntegralBranch == GMAPeosBRANCH) ? "GMAP" : "LMAP");
            } else if (sNorm > pow(DBL_EPSILON, 2.0/3.0)) {
                fprintf(stderr, "WARNING in LIQUID.C (function ORDER). sNorm = %g, dgdsNorm = %g [eps = %g, sqrt(eps) = %g]\n", sNorm, dgdsNORM, DBL_EPSILON, sqrt(DBL_EPSILON));
            }
        }
        
#ifdef DEBUG
        printf("Results of ordering state calculation:\n");
        printf("   T (C) = %8.2f, P (GPa) = %10.4f\n", t-273.15, p/10000.0);
        printf("   %20.20s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s\n", "Species", "Mole frac", "r", "s", "dgds", "deltaS", "eosIntDGDS");
        printf("   %20.20s %13.6g\n", liquid[0].label, xSpecies[0]);
        for (i=0;  i<NR; i++) printf("   %20.20s %13.6g %13.6g\n", liquid[i+1].label, xSpecies[i+1], r[i]);
        for (i=0;  i<NS; i++) printf("   %20.20s %13.6g %13.13s %13.6g %13.6g %13.6g %13.6g\n", liquid[i+NA].label, xSpecies[i+NA], "", sOld[i], dgds[i], sNew[i]-sOld[i], eosIntDGDS[i]);
        for (i=NS; i<NT; i++) printf("   %20.20s %13.13s %13.13s %13.6g %13.6g %13.6g\n", "order CN[*]", "", "", sOld[i], dgds[i], sNew[i]-sOld[i]);
        printf(" 10*DBL_EPSILON    = %20.13g\n", 10.0*DBL_EPSILON);
        printf(" DBL_EPSILON^(2/3) = %20.13g\n", pow(DBL_EPSILON, 2.0/3.0));
        printf(" DBL_EPSILON^(1/2) = %20.13g\n", sqrt(DBL_EPSILON));
        printf(" eosIntegralBranch = %s\n", (eosIntegralBranch == GMAPeosBRANCH) ? "GMAP" : "LMAP");
        for (i=0; i<NS; i++) {
            double s[NT];
            for (j=0; j<NT; j++) s[j] = sOld[j];
            s[i] += 30.0*DBL_EPSILON;
            fillDGDS(r, s, t, p, dgds);
            printf(" s[%d]+30eps gives dgds = %20.13g\n", i, dgds[i]);
            s[i] -= 10.0*DBL_EPSILON;
            fillDGDS(r, s, t, p, dgds);
            printf(" s[%d]+20eps gives dgds = %20.13g\n", i, dgds[i]);
            s[i] -= 10.0*DBL_EPSILON;
            fillDGDS(r, s, t, p, dgds);
            printf(" s[%d]+10eps gives dgds = %20.13g\n", i, dgds[i]);
            printf(" ----------------------\n");
            s[i] = sOld[i];
            fillDGDS(r, s, t, p, dgds);
            printf(" s[%d]       gives dgds = %20.13g\n", i, dgds[i]);
            printf(" ----------------------\n");
            s[i] -= 10.0*DBL_EPSILON;
            fillDGDS(r, s, t, p, dgds);
            printf(" s[%d]-10eps gives dgds = %20.13g\n", i, dgds[i]);
            s[i] -= 10.0*DBL_EPSILON;
            fillDGDS(r, s, t, p, dgds);
            printf(" s[%d]-20eps gives dgds = %20.13g\n", i, dgds[i]);
            s[i] -= 10.0*DBL_EPSILON;
            fillDGDS(r, s, t, p, dgds);
            printf(" s[%d]-30eps gives dgds = %20.13g\n", i, dgds[i]);
            printf(" ++++++++++++++++++++++\n");
        }
#endif
    }
    
    if (mask & FIRST  ) {   /* return s        */
        for (i=0; i<NT; i++) s[i] = sOld[i];
    }
    if (mask & SECOND ) {   /* compute ds/dr:  */
        double *s = sOld;
        
        fillD2GDRDS (r, s, t, p, d2gdrds);
        for (j=0; j<NR; j++) {
            double temp[NT];
            for (i=0; i<NT; i++) temp[i] = d2gdrds[j][i];
            lubksb(ptToD2gds2, NT, indexLU, temp-1);
            for (i=0; i<NT; i++) dr[i][j] = (s[i] > 0.0) ? -temp[i] : 0.0;
        }
    }
    if (mask & THIRD  ) {   /* compute ds/dt:  */
        double *s = sOld;
        double temp[NT];
        
        fillD2GDSDT (r, s, t, p, d2gdsdt);
        for (i=0; i<NT; i++) temp[i] = d2gdsdt[i];
        lubksb(ptToD2gds2, NT, indexLU, temp-1);
        for (i=0; i<NT; i++) dt[i] = (s[i] > 0.0) ? -temp[i] : 0.0;
        
    }
    if (mask & FOURTH ) {   /* compute ds/dp:  */
        double *s = sOld;
        double temp[NT];
        
        fillD2GDSDP (r, s, t, p, d2gdsdp);
        for (i=0; i<NT; i++) temp[i] = d2gdsdp[i];
        lubksb(ptToD2gds2, NT, indexLU, temp-1);
        for (i=0; i<NT; i++) dp[i] = (s[i] > 0.0) ? -temp[i] : 0.0;
    }
    if (mask & FIFTH  ) {   /* compute d2s/dr2 */
        double *s = sOld;
        double dsdr[NT][NR], temp[NT];
        int k, l, m, n;
        
        fillD2GDRDS  (r, s, t, p, d2gdrds);
        fillD3GDR2DS (r, s, t, p, d3gdr2ds);
        fillD3GDRDS2 (r, s, t, p, d3gdrds2);
        fillD3GDS3   (r, s, t, p, d3gds3);
        
        /* compute dsdr matrix */
        for (j=0; j<NR; j++) {
            double temp[NT];
            for (i=0; i<NT; i++) temp[i] = d2gdrds[j][i];
            lubksb(ptToD2gds2, NT, indexLU, temp-1);
            for (i=0; i<NT; i++) dsdr[i][j] = (s[i] > 0.0) ? -temp[i] : 0.0;
        }
        
        /* compute dsdr2 cube */
        for (j=0; j<NR; j++) {
            for (k=0; k<NR; k++) {
                for (l=0; l<NT; l++) {
                    temp[l] = d3gdr2ds[j][k][l];
                    for (m=0; m<NT; m++) {
                        temp[l] += d3gdrds2[j][l][m]*dsdr[m][k]
                        + d3gdrds2[k][l][m]*dsdr[m][j];
                        for (n=0; n<NT; n++)
                            temp[l] += d3gds3[l][m][n]*dsdr[m][j]*dsdr[n][k];
                    }
                }
                lubksb(ptToD2gds2, NT, indexLU, temp-1);
                for (i=0; i<NT; i++) dr2[i][j][k] = (s[i] > 0.0) ? -temp[i] : 0.0;
            }
        }
    }
    if (mask & SIXTH  ) {   /* compute d2s/drt */
        double *s = sOld;
        double dsdr[NT][NR], dsdt[NT], temp[NT];
        int k, l, m;
        
        fillD2GDRDS   (r, s, t, p, d2gdrds);
        fillD2GDSDT   (r, s, t, p, d2gdsdt);
        fillD3GDRDS2  (r, s, t, p, d3gdrds2);
        fillD3GDRDSDT (r, s, t, p, d3gdrdsdt);
        fillD3GDS3    (r, s, t, p, d3gds3);
        fillD3GDS2DT  (r, s, t, p, d3gds2dt);
        
        /* compute dsdr matrix */
        for (j=0; j<NR; j++) {
            for (i=0; i<NT; i++) temp[i] = d2gdrds[j][i];
            lubksb(ptToD2gds2, NT, indexLU, temp-1);
            for (i=0; i<NT; i++) dsdr[i][j] = (s[i] > 0.0) ? -temp[i] : 0.0;
        }
        
        /* compute dsdt vector */
        for (i=0; i<NT; i++) temp[i] = d2gdsdt[i];
        lubksb(ptToD2gds2, NT, indexLU, temp-1);
        for (i=0; i<NT; i++) dsdt[i] = (s[i] > 0.0) ? -temp[i] : 0.0;
        
        /* compute dsdrdt matrix */
        for (j=0; j<NR; j++) {
            for (k=0; k<NT; k++) {
                temp[k] = d3gdrdsdt[j][k];
                for (l=0; l<NT; l++) {
                    temp[k] += d3gdrds2[j][k][l]*dsdt[l] + d3gds2dt[k][l]*dsdr[l][j];
                    for (m=0; m<NT; m++) temp[k] += d3gds3[k][l][m]*dsdr[l][j]*dsdt[m];
                }
            }
            lubksb(ptToD2gds2, NT, indexLU, temp-1);
            for (i=0; i<NT; i++) drt[i][j] = (s[i] > 0.0) ? -temp[i] : 0.0;
        }
        
    }
    if (mask & SEVENTH) {   /* compute d2s/drp */
        double *s = sOld;
        double dsdr[NT][NR], dsdp[NT], temp[NT];
        int k, l, m;
        
        fillD2GDRDS   (r, s, t, p, d2gdrds);
        fillD2GDSDP   (r, s, t, p, d2gdsdp);
        fillD3GDRDS2  (r, s, t, p, d3gdrds2);
        fillD3GDRDSDP (r, s, t, p, d3gdrdsdp);
        fillD3GDS3    (r, s, t, p, d3gds3);
        fillD3GDS2DP  (r, s, t, p, d3gds2dp);
        
        /* compute dsdr matrix */
        for (j=0; j<NR; j++) {
            for (i=0; i<NT; i++) temp[i] = d2gdrds[j][i];
            lubksb(ptToD2gds2, NT, indexLU, temp-1);
            for (i=0; i<NT; i++) dsdr[i][j] = (s[i] > 0.0) ? -temp[i] : 0.0;
        }
        
        /* compute dsdp vector */
        for (i=0; i<NT; i++) temp[i] = d2gdsdp[i];
        lubksb(ptToD2gds2, NT, indexLU, temp-1);
        for (i=0; i<NT; i++) dsdp[i] = (s[i] > 0.0) ? -temp[i] : 0.0;
        
        /* compute dsdrdp matrix */
        for (j=0; j<NR; j++) {
            for (k=0; k<NT; k++) {
                temp[k] = d3gdrdsdp[j][k];
                for (l=0; l<NT; l++) {
                    temp[k] += d3gdrds2[j][k][l]*dsdp[l] + d3gds2dp[k][l]*dsdr[l][j];
                    for (m=0; m<NT; m++) temp[k] += d3gds3[k][l][m]*dsdr[l][j]*dsdp[m];
                }
            }
            lubksb(ptToD2gds2, NT, indexLU, temp-1);
            for (i=0; i<NT; i++) drp[i][j] = (s[i] > 0.0) ? -temp[i] : 0.0;
        }
    }
    if (mask & EIGHTH ) {   /* compute d2s/dt2 */
        double *s = sOld;
        double dsdt[NT], temp[NT];
        int k, l;
        
        fillD2GDSDT  (r, s, t, p, d2gdsdt);
        fillD3GDS3   (r, s, t, p, d3gds3);
        fillD3GDS2DT (r, s, t, p, d3gds2dt);
        fillD3GDSDT2 (r, s, t, p, d3gdsdt2);
        
        /* compute dsdt vector */
        for (i=0; i<NT; i++) temp[i] = d2gdsdt[i];
        lubksb(ptToD2gds2, NT, indexLU, temp-1);
        for (i=0; i<NT; i++) dsdt[i] = (s[i] > 0.0) ? -temp[i] : 0.0;
        
        /* compute dsdt2 vector */
        for (j=0; j<NT; j++) {
            temp[j] = d3gdsdt2[j];
            for (k=0; k<NT; k++) {
                temp[j] +=  2.0*d3gds2dt[j][k]*dsdt[k];
                for (l=0; l<NT; l++) temp[j] += d3gds3[j][k][l]*dsdt[k]*dsdt[l];
            }
        }
        lubksb(ptToD2gds2, NT, indexLU, temp-1);
        for (i=0; i<NT; i++) dt2[i] = (s[i] > 0.0) ? -temp[i] : 0.0;
    }
    if (mask & NINTH  ) {   /* compute d2s/dtp */
        double *s = sOld;
        double dsdt[NT], dsdp[NT], temp[NT];
        int k, l;
        
        fillD2GDSDT   (r, s, t, p, d2gdsdt);
        fillD2GDSDP   (r, s, t, p, d2gdsdp);
        fillD3GDS3    (r, s, t, p, d3gds3);
        fillD3GDS2DT  (r, s, t, p, d3gds2dt);
        fillD3GDS2DP  (r, s, t, p, d3gds2dp);
        fillD3GDSDTDP (r, s, t, p, d3gdsdtdp);
        
        /* compute dsdt vector */
        for (i=0; i<NT; i++) temp[i] = d2gdsdt[i];
        lubksb(ptToD2gds2, NT, indexLU, temp-1);
        for (i=0; i<NT; i++) dsdt[i] = (s[i] > 0.0) ? -temp[i] : 0.0;
        
        /* compute dsdp vector */
        for (i=0; i<NT; i++) temp[i] = d2gdsdp[i];
        lubksb(ptToD2gds2, NT, indexLU, temp-1);
        for (i=0; i<NT; i++) dsdp[i] = (s[i] > 0.0) ? -temp[i] : 0.0;
        
        /* compute dsdtp vector */
        for (j=0; j<NT; j++) {
            temp[j] = d3gdsdtdp[j];
            for (k=0; k<NT; k++) {
                temp[j] += d3gds2dt[j][k]*dsdp[k] + d3gds2dp[j][k]*dsdt[k];
                for (l=0; l<NT; l++) temp[j] += d3gds3[j][k][l]*dsdt[k]*dsdp[l];
            }
        }
        lubksb(ptToD2gds2, NT, indexLU, temp-1);
        for (i=0; i<NT; i++) dtp[i] = (s[i] > 0.0) ? -temp[i] : 0.0;
    }
    if (mask & TENTH  ) {   /* compute d2s/dp2 */
        double *s = sOld;
        double dsdp[NT], temp[NT];
        int k, l;
        
        fillD2GDSDP  (r, s, t, p, d2gdsdp);
        fillD3GDS3   (r, s, t, p, d3gds3);
        fillD3GDS2DP (r, s, t, p, d3gds2dp);
        fillD3GDSDP2 (r, s, t, p, d3gdsdp2);
        
        /* compute dsdp vector */
        for (i=0; i<NT; i++) temp[i] = d2gdsdp[i];
        lubksb(ptToD2gds2, NT, indexLU, temp-1);
        for (i=0; i<NT; i++) dsdp[i] = (s[i] > 0.0) ? -temp[i] : 0.0;
        
        /* compute dsdp2 vector */
        for (j=0; j<NT; j++) {
            temp[j] = d3gdsdp2[j];
            for (k=0; k<NT; k++) {
                temp[j] +=  2.0*d3gds2dp[j][k]*dsdp[k];
                for (l=0; l<NT; l++) temp[j] += d3gds3[j][k][l]*dsdp[k]*dsdp[l];
            }
        }
        lubksb(ptToD2gds2, NT, indexLU, temp-1);
        for (i=0; i<NT; i++) dp2[i] = (s[i] > 0.0) ? -temp[i] : 0.0;
    }
}

/*
 *=============================================================================
 * Public functions:
 *    mask  -  bitwise mask for selecting output
 *    t     -  Temperature (K)
 *    p     -  Pressure (bars)
 *    *x    -  (pointer to x[]) Array of independent compositional variables
 */
int
testSfl(int mask, double t, double p,
        int na,          /* Expected number of endmember components                 */
        int nr,          /* Expected number of independent compositional variables  */
        char **names,    /* array of strings of names of endmember components       */
        char **formulas, /* array of strings of formulas of endmember components    */
        double *r,       /* array of indepependent compos variables, check bounds   */
        double *m)       /* array of moles of endmember components, check bounds    */
{
    const char *phase = "saxenaFluidPhase.c";
    const char *NAMES[NA]    = { "H", "C", "N", "O", "S", "Ar" };
    const char *FORMULAS[NA] = { "H", "C", "N", "O", "S", "Ar" };
    int result = TRUE, i;
    double sum;
    
    if (mask & FIRST) {
        result = result && (na == NA);
        if (!result) printf("<<%s>> Wrong number of components!\n", phase);
    }
    if (mask & SECOND) {
        result = result && (nr == NR);
        if (!result) printf("<<%s>> Wrong number of indep variables!\n", phase);
    }
    if (mask & THIRD) {
        for (i=0; i<NA; i++) {
            result = result && (strcmp(names[i],NAMES[i]) == 0);
            if (!result)
                printf("<<%s>> Component[%d] should be %s not %s.\n",
                       phase, i, NAMES[i], names[i]);
        }
    }
    if (mask & FOURTH) {
        for (i=0; i<NA; i++) {
            result = result && (strcmp(formulas[i],FORMULAS[i]) == 0);
            if (!result)
                printf("<<%s>> Component[%d] should have formula %s not %s.\n",
                       phase, i, FORMULAS[i], formulas[i]);
        }
    }
    /* Check bounds on the independent compositional variables */
    if (mask & FIFTH) {
        for (i=0, sum=0.0; i<NR; i++) {
            result = result && (r[i] >= 0.0) && (r[i] <= 1.0);
            sum += r[i];
        }
        result = result && (sum <= 1.0);
    }
    /* Check bounds on moles of endmember components */
    if (mask & SIXTH) {
        for (i=0; i<NA; i++) result = result && (m[i] >= 0.0);
    }
    
    return result;
}

void
conSfl(int inpMask, int outMask, double t, double p,
       double *e,      /* comp of fluid phase in moles of elements                     */
       double *m,      /* comp of fluid phase in moles of endmember components         */
       double *r,      /* comp of fluid phase in terms of the independent comp var     */
       double *x,      /* comp of fluid phase in mole fractions of endmember comp      */
       double **dm,    /* Jacobian matrix: dm[i][j] = dr[i]/dm[j]                  */
       double ***d2m,  /* vector of matrices: d2m[i][j][k] = d2r[i]/dm[j]dm[k]     */
       double **dr,    /* Jacobian matrix: dr[i][j] = dx[i]/dr[j]                  */
       double ****d3m) /* 3rd deriv matrix: d3m[i][j][k][l]=d3r[i]/dm[j]dm[k]dm[l] */
{
    /*---------------------------------------------------------------------------
     Not all combinations of inpMask and outMask are feasible. Valid
     combinations are:
     
     inpMask          outMask
     (1)  FIRST            SECOND
     (2)  SECOND           THIRD  | FOURTH  | FIFTH | SIXTH | EIGHTH
     (3)  THIRD            FOURTH | SEVENTH
     
     (1) converts a vector of moles of elements into a vector of moles of
     endmember fluid phase components.
     (2) calculates from a vector of moles of endmember components, one or
     all of: r[], x[], dr[]/dm[], d2r[]/dm[]dm[], or d3r[]/dm[]dm[]dm[]
     (3) calculates from a vector of independent compositional variables
     mole fractions of endmember components and/or the Jacobian matrix
     dx[]/dr[]
     
     ----------------------------------------------------------------------------*/
    
    int i, j, k;
    
    if (inpMask == FIRST && outMask == SECOND) {
        static const int H  =  1;
        static const int C  =  6;
        static const int N  =  7;
        static const int O  =  8;
        static const int S  = 16;
        static const int Ar = 18;
        
        m[0] = e[H];  /* moles of H  */
        m[1] = e[C];  /* Moles of C  */
        m[1] = e[N];  /* Moles of N  */
        m[1] = e[O];  /* Moles of O  */
        m[1] = e[S];  /* Moles of S  */
        m[1] = e[Ar]; /* Moles of Ar */
        
    } else if (inpMask == SECOND) {
        double sum;
        
        if (outMask & ~(THIRD | FOURTH | FIFTH | SIXTH | EIGHTH))
            printf("Illegal call to conSfl with inpMask = %o and outMask = %o\n",
                   inpMask, outMask);
        
        for (i=0, sum=0.0; i<NA; i++) sum += m[i];
        
        if (outMask & THIRD) {
            for (i=0; i<NR; i++) r[i] = (sum != 0.0) ? m[i+1]/sum : 0.0;
        }
        
        if (outMask & FOURTH) {
            /* Converts a vector of moles of end-member components (m) into a vector
             of mole fractions of endmember components                            */
            for (i=0; i<NA; i++) x[i] = (sum != 0.0) ? m[i]/sum : 0.0;
        }
        
        if (outMask & FIFTH) {
            /* Calculates the matrix dr[i]/dm[j] using m[] as input                 */
            if (sum == 0.0) {
                for (i=0; i<NR; i++) { for (j=0; j<NA; j++) dm[i][j] = 0.0; }
            } else {
                for (i=0; i<NR; i++) {
                    for (j=0; j<NA; j++)
                        dm[i][j] = (i+1 == j) ? (1.0-m[i+1]/sum)/sum : - m[i+1]/SQUARE(sum);
                }
            }
            
        }
        
        if (outMask & SIXTH) {
            /* Calculates the matrix d2r[i]/dm[j]dm[k] using m[] as input           */
            
            if (sum == 0.0) {
                for (i=0; i<NR; i++) {
                    for (j=0; j<NA; j++)  {
                        for (k=0; k<NA; k++) d2m[i][j][k] = 0.0;
                    }
                }
            } else {
                for (i=0; i<NR; i++) {
                    for (j=0; j<NA; j++)  {
                        for (k=0; k<NA; k++) {
                            d2m[i][j][k]  = 2.0*m[i+1]/CUBE(sum);
                            d2m[i][j][k] -= (i+1 == j) ? 1.0/SQUARE(sum) : 0.0;
                            d2m[i][j][k] -= (i+1 == k) ? 1.0/SQUARE(sum) : 0.0;
                        }
                    }
                }
            }
        }
        
        if (outMask & EIGHTH) {
            /* calculates the matrix d3r[i]/dm[j]dm[k]dm[l] using m[] as input	*/
            int l;
            
            if (sum == 0.0) {
                for (i=0; i<NR; i++) {
                    for (j=0; j<NA; j++)  {
                        for (k=0; k<NA; k++)  {
                            for (l=0; l<NA; l++) d3m[i][j][k][l] = 0.0;
                        }
                    }
                }
            } else {
                for (i=0; i<NR; i++) {
                    for (j=0; j<NA; j++)  {
                        for (k=0; k<NA; k++)  {
                            for (l=0; l<NA; l++)  {
                                d3m[i][j][k][l]  = -6.0*m[i+1]/QUARTIC(sum);
                                d3m[i][j][k][l] += (i+1 == j) ? 2.0/CUBE(sum) : 0.0;
                                d3m[i][j][k][l] += (i+1 == k) ? 2.0/CUBE(sum) : 0.0;
                                d3m[i][j][k][l] += (i+1 == l) ? 2.0/CUBE(sum) : 0.0;
                            }
                        }
                    }
                }
            }
            
        }
        
    } else if (inpMask == THIRD) {
        
        if (outMask & ~(FOURTH | SEVENTH))
            printf("Illegal call to conSfl with inpMask = %o and outMask = %o\n",
                   inpMask, outMask);
        
        if (outMask & FOURTH) {
            /* Converts a vector of independent compositional variables (r)
             into a vector of mole fractions of endmember components (x).         */
            
            for (i=0, x[0]=1.0; i<NR; i++) { x[i+1] = r[i]; x[0] -= r[i]; }
        }
        
        if (outMask & SEVENTH) {
            /* computes the Jacobian matrix dr[i][j] = dx[i]/dr[j] */
            for (i=0; i<NR; i++) for (j=0; j<NR; j++) dr[i+1][j] = (i == j) ? 1.0 : 0.0;
            for (j=0; j<NR; j++) dr[0][j]   = -1.0;
        }
        
    } else  {
        printf("Illegal call to conSfl with inpMask = %o and outMask = %o\n",
               inpMask, outMask);
    }
    
}

void
dispSfl(int mask, double t, double p, double *x,
        char **formula            /* Mineral formula for interface display MASK: 1 */
)
{
    double *r = x;
    static char masterString[] = {
        /*             1111111111222222222233333333334444444444555555555566666666667
         01234567890123456789012345678901234567890123456789012345678901234567890 */
        "H_.__C_.__N_.__O_.__S_.__Ar_.__" };
    
    if (mask & FIRST) {
        char *string = strcpy((char *) malloc((size_t) (strlen(masterString)+1)*sizeof(char)), masterString);
        char n[5];
        int i;
        
        (void) snprintf(n, 5, "%4.2f", 1.0-r[0]-r[1]-r[2]-r[3]-r[4]); for (i=0; i<4; i++) string[ 1+i] = n[i];
        (void) snprintf(n, 5, "%4.2f",     r[0]); for (i=0; i<4; i++) string[ 6+i] = n[i];
        (void) snprintf(n, 5, "%4.2f",     r[1]); for (i=0; i<4; i++) string[ 6+i] = n[i];
        (void) snprintf(n, 5, "%4.2f",     r[2]); for (i=0; i<4; i++) string[ 6+i] = n[i];
        (void) snprintf(n, 5, "%4.2f",     r[3]); for (i=0; i<4; i++) string[ 6+i] = n[i];
        (void) snprintf(n, 5, "%4.2f",     r[4]); for (i=0; i<4; i++) string[ 6+i] = n[i];
        
        *formula = string;
    }
}

void
actSfl(int mask, double t, double p, double *r,
       double *a,  /* (pointer to a[]) activities              BINARY MASK: 0001 */
       double *mu, /* (pointer to mu[]) chemical potentials    BINARY MASK: 0010 */
       double **dx /* (pointer to dx[][]) d(a[])/d(x[])        BINARY MASK: 0100 */
)           /* exclusion criteria applied to results if BINARY MASK: 1000 */
{
    static const int H  = 0;
    static const int C  = 1;
    static const int N  = 2;
    static const int O  = 3;
    static const int S  = 4;
    static const int Ar = 5;
    
    double x[6];
    int i, j;
    
    x[H ] = 1.0 - r[0] - r[1] - r[2] - r[3] - r[4];
    x[C ] = r[0];
    x[N ] = r[1];
    x[O ] = r[2];
    x[S ] = r[3];
    x[Ar] = r[4];
    
    if (mask & FIRST) {
        a[H ] = x[H ];
        a[C ] = x[C ];
        a[N ] = x[N ];
        a[O ] = x[O ];
        a[S ] = x[S ];
        a[Ar] = x[Ar];
    }
    
    if (mask & SECOND) {
        mu[H ] = (x[H ] != 0.0) ? R*t*log(x[H ]) : 0.0;
        mu[C ] = (x[C ] != 0.0) ? R*t*log(x[C ]) : 0.0;
        mu[N ] = (x[N ] != 0.0) ? R*t*log(x[N ]) : 0.0;
        mu[O ] = (x[O ] != 0.0) ? R*t*log(x[O ]) : 0.0;
        mu[S ] = (x[S ] != 0.0) ? R*t*log(x[S ]) : 0.0;
        mu[C ] = (x[Ar] != 0.0) ? R*t*log(x[Ar]) : 0.0;
    }
    
    if (mask & THIRD) {
        double g, dgdr[NR], fr[NA][NR];
        double d2gdr2[NR][NR], dfrdr[NA][NR], sum;
        int k;
        
        for(i=0; i<NA; i++) fr[i][0] = FR0(i);
        
        g            = 0.0;
        for (i=0; i<NR; i++) dgdr[i] = 0.0;
        for (i=0; i<NR; i++) for (j=0; j<NR; j++) d2gdr2[i][j] = 0.0;
        
        for(i=0; i<NA; i++) dfrdr[i][0] = DFR0DR0(i);
        
        for (i=0; i<NA; i++) {
            for (k=0; k<NR; k++) {
                for (dx[i][k]=g, j=0; j<NR; j++) dx[i][k] += fr[i][j]*dgdr[j];
                dx[i][k] = exp(dx[i][k]/(R*t));
                sum = (1.0+dfrdr[i][k])*dgdr[k];
                for (j=0; j<NR; j++) sum += fr[i][j]*d2gdr2[j][k];
                dx[i][k] *= sum/(R*t);
            }
        }
    }
    
    if (mask & FOURTH) {
        //
    }
    
}

void
gmixSfl(int mask, double t, double p, double *r,
        double *gmix, /* Gibbs energy of mixing             BINARY MASK: 0001 */
        double *dx,   /* (pointer to dx[]) d(g)/d(x[])      BINARY MASK: 0010 */
        double **dx2, /* (pointer to dx2[][]) d2(g)/d(x[])2 BINARY MASK: 0100 */
        double ***dx3 /* (pointer to dx3[][][]) d3(g)/d(x[])3 NARY MASK: 1000 */
)
{
    static const int H  = 0;
    static const int C  = 1;
    static const int N  = 2;
    static const int O  = 3;
    static const int S  = 4;
    static const int Ar = 5;

    double x[6];
    
    x[H ] = 1.0 - r[0] - r[1] - r[2] - r[3] - r[4];
    x[C ] = r[0];
    x[N ] = r[1];
    x[O ] = r[2];
    x[S ] = r[3];
    x[Ar] = r[4];
    
    if (mask & FIRST) {
        *gmix = 0.0;
    }
    
    if(mask & SECOND) {
        dx[0] = 0.0;
        dx[1] = 0.0;
        dx[2] = 0.0;
        dx[3] = 0.0;
        dx[4] = 0.0;
        dx[5] = 0.0;
    }
    
    if(mask & THIRD) {
        double d2gdr2[NR][NR];
        int i, j;
        
        for (i=0; i<NR; i++) for (j=0; j<NR; j++) d2gdr2[i][j] = 0.0;
        
        for (i=0; i<NR; i++) {
            for (j=0; j<NR; j++) dx2[i][j] = d2gdr2[i][j];
        }
    }
    
    if (mask & FOURTH) {
        double d3gdr3[NR][NR][NR];
        int i, j, k;
        
        for (i=0; i<NR; i++) for (j=0; j<NR; j++) for (k=0; k<NR; k++) d3gdr3[i][j][k] = 0.0;
        
        for (i=0; i<NR; i++) {
            for (j=0; j<NR; j++) {
                for (k=0; k<NR; k++) dx3[i][j][k] = d3gdr3[i][j][k];
            }
        }
    }
    
}

void
hmixSfl(int mask, double t, double p, double *r,
        double *hmix /* Enthalpy of mixing BINARY MASK: 1 */
)
{
    static const int H  = 0;
    static const int C  = 1;
    static const int N  = 2;
    static const int O  = 3;
    static const int S  = 4;
    static const int Ar = 5;
    
    double x[6];
    
    x[H ] = 1.0 - r[0] - r[1] - r[2] - r[3] - r[4];
    x[C ] = r[0];
    x[N ] = r[1];
    x[O ] = r[2];
    x[S ] = r[3];
    x[Ar] = r[4];
    
    *hmix = 0.0;
}

void
smixSfl(int mask, double t, double p, double *r,
        double *smix, /* Entropy of mixing                  BINARY MASK: 001 */
        double *dx,   /* (pointer to dx[]) d(s)/d(x[])      BINARY MASK: 010 */
        double **dx2  /* (pointer to dx2[][]) d2(s)/d(x[])2 BINARY MASK: 100 */
)
{
    static const int H  = 0;
    static const int C  = 1;
    static const int N  = 2;
    static const int O  = 3;
    static const int S  = 4;
    static const int Ar = 5;
    
    double x[6];
    
    x[H ] = 1.0 - r[0] - r[1] - r[2] - r[3] - r[4];
    x[C ] = r[0];
    x[N ] = r[1];
    x[O ] = r[2];
    x[S ] = r[3];
    x[Ar] = r[4];
    
    if (mask & FIRST) {
        *smix = 0.0;
    }
    
    if(mask & SECOND) {
        int i;
        for (i=0; i<NR; i++) dx[i] = 0.0;
    }
    
    if(mask & THIRD) {
        double d3gdr2dt[NR][NR];
        int i, j;
        
        for (i=0; i<NR; i++) for (j=0; j<NR; j++) d3gdr2dt[i][j] = 0.0;
        
        for (i=0; i<NR; i++) {
            for (j=0; j<NR; j++) dx2[i][j] = - d3gdr2dt[i][j];
        }
    }
    
}

void
cpmixSfl(int mask, double t, double p, double *r,
         double *cpmix, /* Heat capacity of mixing               BINARY MASK: 001 */
         double *dt,    /* d(cp)/d(t)                            BINARY MASK: 010 */
         double *dx     /* d(cp)/d(x[])d(t)                      BINARY MASK: 100 */
)
{
    static const int H  = 0;
    static const int C  = 1;
    static const int N  = 2;
    static const int O  = 3;
    static const int S  = 4;
    static const int Ar = 5;
    
    double x[6];
    
    x[H ] = 1.0 - r[0] - r[1] - r[2] - r[3] - r[4];
    x[C ] = r[0];
    x[N ] = r[1];
    x[O ] = r[2];
    x[S ] = r[3];
    x[Ar] = r[4];
    
    if (mask & FIRST) {
        *cpmix = 0.0;
    }
    
    if(mask & SECOND) {
        *dt = 0.0;
    }
    
    if(mask & THIRD) {
        double d3gdrdt2[NR];
        int i;
        
        for (i=0; i<NR; i++) d3gdrdt2[i] = 0.0;
        for (i=0; i<NR; i++) dx[i] = -t*d3gdrdt2[i];
    }
    
}

void
vmixSfl(int mask, double t, double p, double *r,
        double *vmix, /* Volume of mixing                BINARY MASK: 0000000001 */
        double *dx,   /* (pointer to dx[]) d(v)/d(x[])   BINARY MASK: 0000000010 */
        double **dx2, /* (point to dx2[][]) d(v)/d(x[])2 BINARY MASK: 0000000100 */
        double *dt,   /* d(v)/d(t)                       BINARY MASK: 0000001000 */
        double *dp,   /* d(v)/d(p)                       BINARY MASK: 0000010000 */
        double *dt2,  /* d2(v)/d(t)2                     BINARY MASK: 0000100000 */
        double *dtdp, /* d2(v)/d(t)d(p)                  BINARY MASK: 0001000000 */
        double *dp2,  /* d2(v)/d(p)2                     BINARY MASK: 0010000000 */
        double *dxdt, /* d2(v)/d(x[])d(t)                BINARY MASK: 0100000000 */
        double *dxdp  /* d2(v)/d(x[])d(p)                BINARY MASK: 1000000000 */
)
{
    static const int H  = 0;
    static const int C  = 1;
    static const int N  = 2;
    static const int O  = 3;
    static const int S  = 4;
    static const int Ar = 5;
    
    double x[6];
    
    x[H ] = 1.0 - r[0] - r[1] - r[2] - r[3] - r[4];
    x[C ] = r[0];
    x[N ] = r[1];
    x[O ] = r[2];
    x[S ] = r[3];
    x[Ar] = r[4];
    
    if (mask & FIRST) {
        *vmix = 0.0;
    }
    
    if(mask & SECOND) {
        double d2gdrdp[NR];
        int i;
        
        for (i=0; i<NR; i++) d2gdrdp[i] = 0.0;
        
        for (i=0; i<NR; i++) dx[i] = d2gdrdp[i]; 
    }
    
    if(mask & THIRD) {
        double d3gdr2dp[NR][NR];
        int i, j;
        
        for (i=0; i<NR; i++) for (j=0; j<NR; i++) d3gdr2dp[i][j] = 0.0;
        
        for (i=0; i<NR; i++) {
            for (j=0; j<NR; j++) dx2[i][j] = d3gdr2dp[i][j];
        }
    }
    
    if(mask & FOURTH) {
        *dt = 0.0;
    }
    
    if(mask & FIFTH) {
        *dp = 0.0;
    }
    
    if(mask & SIXTH) {
        *dt2 = 0.0;
    }
    
    if(mask & SEVENTH) {
        *dtdp = 0.0;
    }
    
    if(mask & EIGHTH) {
        *dp2 = 0.0;
    }
    
    if(mask & NINTH) {
        double d3gdrdtdp[NR];
        int i;
        
        for (i=0; i<NR; i++) d3gdrdtdp[i] = 0.0;
        
        for (i=0; i<NR; i++) dxdt[i] = d3gdrdtdp[i]; 
    }
    
    if(mask & TENTH) {
        double d3gdrdp2[NR];
        int i;
        
        for (i=0; i<NR; i++) d3gdrdp2[i] = 0.0;
        
        for (i=0; i<NR; i++) dxdp[i] = d3gdrdp2[i]; 
    }
    
}

/* end of file fluidPhase.c */
