#include "silmin.h"
#include "recipes.h"
#include <signal.h>

#include "f2c.h"
extern int fder_(doublereal *xx, doublereal *tt, doublereal *pp, doublereal *vv, doublereal *gg, doublereal *ggi);

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

static int convergedInOrder;
static double *dgds;
static double **d2gdrds, *d2gdsdt, *d2gdsdp;
static double ***d3gdr2ds, ***d3gdrds2,**d3gdrdsdt, **d3gdrdsdp,
***d3gds3, **d3gds2dt, **d3gds2dp, *d3gdsdt2, *d3gdsdtdp, *d3gdsdp2;


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

//static double mu0C;
//static double t, p;
//
//static void func(int n, double *v, double *f) {
//    double x[13], g, vol, gi[13];
//    x[ 0] = 0.0; x[ 1] = 0.0; x[ 2] = 0.0; x[ 3] = 0.0; x[ 4] = 0.0; x[ 5] = 0.0; x[ 6] = 0.0;
//    x[ 7] = 0.0; x[ 8] = 0.0; x[ 9] = 0.0; x[10] = 0.0; x[11] = 0.0; x[12] = 0.0;
//    
//    x[4] = exp(log(10.0)*v[1]);
//    x[3] = exp(log(10.0)*v[2]);
//    x[1] = 1.0-x[3]-x[4];
//    (void) fder_(x, &t, &p, &vol, &g, gi);
//    
//    f[1] = gi[1] - gi[4]	   - mu0C;
//    f[2] = gi[3] - gi[4]/2.0 - mu0C;
//    /*
//     printf("v[1] = %20.13g v[2] = %20.13g f[1] = %20.13g f[2] = %20.13g\n", v[1], v[2], f[1], f[2]);
//     */
//}
//
//#define USE_GRAPHITE
//
//int main()
//{
//    double xO2[13], vO2_1bar, gO2_1bar, vO2, gO2;
//    double x[13], vol, g, gi[13];
//    double gamO2, fugO2, f1, f2;
//    double p1bar = 1.0;
//    double v[3];
//    int i, indexD = -1, indexG = -1, check;
//    
//    printf("Calling function: InitComputeDataStruct().\n");
//    InitComputeDataStruct();
//    
//    for (i=0; i<npc; i++) {
//        if (!strcmp(solids[i].label, "diamond") ) indexD = i;
//        if (!strcmp(solids[i].label, "graphite")) indexG = i;
//    }
//    if (indexD == -1) { printf("Phase \"diamond\" not found in sol_struct_data.h\n"); return 1; }
//    if (indexG == -1) { printf("Phase \"graphite\" not found in sol_struct_data.h\n"); return 1; }
//    
//    x[ 0] = 0.0; xO2[ 0] = 0.0; /* H2O */
//    x[ 1] = 0.0; xO2[ 1] = 0.0; /* CO2 */
//    x[ 2] = 0.0; xO2[ 2] = 0.0; /* CH4 */
//    x[ 3] = 0.0; xO2[ 3] = 0.0; /*  CO */
//    x[ 4] = 0.0; xO2[ 4] = 1.0; /*  O2 */
//    x[ 5] = 0.0; xO2[ 5] = 0.0; /*  H2 */
//    x[ 6] = 0.0; xO2[ 6] = 0.0; /*  S2 */
//    x[ 7] = 0.0; xO2[ 7] = 0.0; /* SO2 */
//    x[ 8] = 0.0; xO2[ 8] = 0.0; /* COS */
//    x[ 9] = 0.0; xO2[ 9] = 0.0; /* H2S */
//    x[10] = 0.0; xO2[10] = 0.0; /*  N2 */
//    x[11] = 0.0; xO2[11] = 0.0; /* NH3 */
//    x[12] = 0.0; xO2[12] = 0.0; /*  Ar */
//    
//    printf("%5.5s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s\n",
//           "check", "T (K)", "P (bars)", "f1", "f2", "X", "Y", "X CO2", "X CO", "X O2", "log f O2", "buffer");
//    
//    t = 1360.0 + 273.15;   /* K    */
//    v[1] = -10.0;
//    v[2] =  -5.0;
//    
//    for (p=1000.0; p<=300000.0; p+=1000.0) {
//        
//#ifdef USE_GRAPHITE
//        gibbs(t, p, (char *) solids[indexG].label, &(solids[indexG].ref), NULL, NULL, &(solids[indexG].cur));
//        mu0C = (solids[indexG].cur).g;
//#else
//        gibbs(t, p, (char *) solids[indexD].label, &(solids[indexD].ref), NULL, NULL, &(solids[indexD].cur));
//        mu0C = (solids[indexD].cur).g;
//#endif
//        
//        (void) fluid_(xO2, &t, &p1bar, &vO2_1bar, &gO2_1bar);
//        (void) fluid_(xO2, &t, &p,     &vO2,      &gO2);
//        
//        newt (v, 2, &check, func);
//        
//        x[4] = exp(log(10.0)*v[1]);
//        x[3] = exp(log(10.0)*v[2]);
//        x[1] = 1.0-x[3]-x[4];
//        (void) fder_(x, &t, &p, &vol, &g, gi);
//        f1 = gi[1] - gi[4]	 - mu0C;
//        f2 = gi[3] - gi[4]/2.0 - mu0C;
//        gamO2 = gi[4] - gO2_1bar - R*t*log(p);
//        fugO2 = gO2	- gO2_1bar - R*t*log(p);
//        gamO2 = exp(gamO2/(R*t));
//        gamO2 = gamO2/x[4];
//        fugO2 = exp(fugO2/(R*t));
//        gamO2 = gamO2/fugO2;
//        
//        printf("%5.5d %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g\n",
//               check, t, p, f1, f2, v[1], v[2], x[1], x[3], x[4], log(fugO2*gamO2*x[4]*p)/log(10.0),
//               (-22324.0 + 189.0*p/1000.0 - 1.41*p*p/1000000.0)/t+4.62);
//    }
//    
//    return 0;
//}

static double fillG (double r[NR], double s[NT], double t, double p) {
    double vol, result, gi[13];
    rANDsTOx(r, s);
    (void) fder_(xSpecies, &t, &p, &vol, &result, gi);
    return result;
}

static double fillS (double r[NR], double s[NT], double t, double p) {
    double result=0.0;
    return result;
}

static double fillV (double r[NR], double s[NT], double t, double p) {
    double result = 0.0;
    return result;
}

static void fillDGDR (double r[NR], double s[NT], double t, double p, double *result) {
    for (int i=0; i<NR; i++) {
        result[i] = 0.0;
    }
}

static void fillDGDS (double r[NR], double s[NT], double t, double p, double *result) {
    double vol, g, gi[13], sTemp[NT];
    rANDsTOx(r, s);
    (void) fder_(xSpecies, &t, &p, &vol, &g, gi);
    for (int i=0; i<NS; i++) sTemp[i] = s[i];
    
    for (int i=0; i<NS; i++) {
        if (s[i] == 0.0) result[i] = 0.0;
        else {
            double gTemp;
            sTemp[i] = (1.0+sqrt(DBL_EPSILON))*s[i];
            rANDsTOx(r, sTemp);
            (void) fder_(xSpecies, &t, &p, &vol, &gTemp, gi);
            result[i] = (gTemp-g)/(sTemp[i]-s[i]);
            sTemp[i] = s[i];
        }
    }
    
    rANDsTOx(r, s);
}

static void fillD2GDR2 (double r[NR], double s[NT], double t, double p, double **result) {
    for (int i=0; i<NR; i++) {
        result[i][i] = 0.0;
        for (int j=i+1; j<NR; j++) {
            result[i][j] = 0.0;
            result[j][i] = 0.0;
        }
    }
}

static void fillD2GDRDS (double r[NR], double s[NT], double t, double p, double **result) {
    for (int i=0; i<NR; i++) for (int j=0; j<NS; j++) result[i][j] = 0.0;
}

static void fillD2GDRDT (double r[NR], double s[NT], double t, double p, double *result) {
    for (int i=0; i<NR; i++) {
        result[i] = 0.0;
    }
}

static void fillD2GDRDP (double r[NR], double s[NT], double t, double p, double *result) {
    for (int i=0; i<NR; i++) {
        result[i] = 0.0;
    }
}

static void fillD2GDS2 (double r[NR], double s[NT], double t, double p, double **result) {
    double vol, g, gi[13], sTemp[NT], dgForward[NS], dgBackward[NS];
    rANDsTOx(r, s);
    (void) fder_(xSpecies, &t, &p, &vol, &g, gi);
    for (int i=0; i<NS; i++) sTemp[i] = s[i];
    
    for (int i=0; i<NS; i++) {
        if (s[i] == 0.0) { dgForward[i] = 0.0; dgBackward[i] = 0.0; }
        else {
            double gTemp;
            sTemp[i] = (1.0+sqrt(DBL_EPSILON))*s[i];
            rANDsTOx(r, sTemp);
            (void) fder_(xSpecies, &t, &p, &vol, &gTemp, gi);
            dgForward[i] = (gTemp-g)/(sTemp[i]-s[i]);
            
            sTemp[i] = (1.0-sqrt(DBL_EPSILON))*s[i];
            rANDsTOx(r, sTemp);
            (void) fder_(xSpecies, &t, &p, &vol, &gTemp, gi);
            dgBackward[i] = (g-gTemp)/(s[i]-sTemp[i]);
            sTemp[i] = s[i];
        }
    }
    
    // Fix this
    for (int i=0; i<NS; i++) {
        double dsi = s[i]*sqrt(DBL_EPSILON);
        for (int j=i; j<NS; j++) {
            double dsj = s[j]*sqrt(DBL_EPSILON);
            result[i][j] = 0.0;
            result[j][i] = 0.0;
        }
    }
}

static void fillD2GDSDT (double r[NR], double s[NT], double t, double p, double *result) {
    for (int i=0; i<NS; i++) {
        result[i] = 0.0;
    }
}

static void fillD2GDSDP (double r[NR], double s[NT], double t, double p, double *result) {
    for (int i=0; i<NS; i++) {
        result[i] = 0.0;
    }
}

static double fillD2GDT2 (double r[NR], double s[NT], double t, double p) {
    double result = 0.0;
    return result;
}

static double fillD2GDTDP (double r[NR], double s[NT], double t, double p) {
    double result = 0.0;
    return result;
}

static double fillD2GDP2 (double r[NR], double s[NT], double t, double p) {
    double result = 0.0;
    return result;
}

static void fillD3GDR3 (double r[NR], double s[NT], double t, double p, double ***result) {
    for (int j=0; j<NR; j++) {
        for (int k=j; k<NR; k++) {
            for (int l=k; l<NR; l++) {
                result[j][k][l]  = 0.0;
                result[k][j][l]  = result[j][k][l];
                result[l][j][k]  = result[j][k][l];
                result[l][k][j]  = result[j][k][l];
                result[j][l][k]  = result[j][k][l];
                result[k][l][j]  = result[j][k][l];
            }
        }
    }
}

static void fillD3GDR2DS (double r[NR], double s[NT], double t, double p, double ***result) {
    for (int j=0; j<NR; j++) {
        for (int k=j; k<NR; k++) {
            for (int l=0; l<NS; l++) {
                result[j][k][l]  = 0.0;
                result[k][j][l]  = result[j][k][l];
            }
        }
    }
}

static void fillD3GDR2DT (double r[NR], double s[NT], double t, double p, double **result) {
    for (int i=0; i<NR; i++) for (int j=i; j<NR; j++) {
        result[i][j] = 0.0;
        result[j][i] = result[i][j];
    }
}

static void fillD3GDR2DP (double r[NR], double s[NT], double t, double p, double **result) {
    for (int i=0; i<NR; i++) for (int j=i; j<NR; j++) {
        result[i][j] = 0.0;
        result[j][i] = result[i][j];
    }
    
}

static void fillD3GDRDS2 (double r[NR], double s[NT], double t, double p, double ***result) {
    for (int j=0; j<NR; j++) {
        for (int k=0; k<NS; k++) {
            for (int l=k; l<NS; l++) {
                result[j][k][l] += 0.0;
                result[j][l][k]  = result[j][k][l];
            }
        }
    }
}

static void fillD3GDRDSDT (double r[NR], double s[NT], double t, double p, double **result) {
    for (int i=0; i<NR; i++) for (int j=0; j<NS; j++) result[i][j] = 0.0;
}

static void fillD3GDRDSDP (double r[NR], double s[NT], double t, double p, double **result) {
    for (int i=0; i<NR; i++) for (int j=0; j<NS; j++) result[i][j] = 0.0;
}

static void fillD3GDS3 (double r[NR], double s[NT], double t, double p, double ***result) {
    for (int j=0; j<NS; j++) {
        for (int k=j; k<NS; k++) {
            for (int l=k; l<NS; l++) {
                result[j][k][l]  = 0.0;
                result[k][j][l]  = result[j][k][l];
                result[l][j][k]  = result[j][k][l];
                result[l][k][j]  = result[j][k][l];
                result[j][l][k]  = result[j][k][l];
                result[k][l][j]  = result[j][k][l];
            }
        }
    }
}

static void fillD3GDS2DT (double r[NR], double s[NT], double t, double p, double **result) {
    for (int i=0; i<NS; i++) for (int j=i; j<NS; j++) {
        result[i][j] = 0.0;
        result[j][i] = result[i][j];
    }
}

static void fillD3GDS2DP (double r[NR], double s[NT], double t, double p, double **result) {
    for (int i=0; i<NS; i++) for (int j=i; j<NS; j++) {
        result[i][j] = 0.0;
        result[j][i] = result[i][j];
    }
}

static void fillD3GDSDT2 (double r[NR], double s[NT], double t, double p, double *result) {
    for (int i=0; i<NS; i++) result[i] = 0.0;
}

static void fillD3GDSDTDP (double r[NR], double s[NT], double t, double p, double *result) {
    for (int i=0; i<NS; i++) result[i] = 0.0;
}

static void fillD3GDSDP2 (double r[NR], double s[NT], double t, double p, double *result) {
    for (int i=0; i<NS; i++) result[i] = 0.0;
}

static void fillD3GDRDT2 (double r[NR], double s[NT], double t, double p, double *result) {
    for (int i=0; i<NR; i++) result[i] = 0.0;
}

static void fillD3GDRDTDP (double r[NR], double s[NT], double t, double p, double *result) {
    for (int i=0; i<NR; i++) result[i] = 0.0;
}

static void fillD3GDRDP2 (double r[NR], double s[NT], double t, double p, double *result) {
    for (int i=0; i<NR; i++) result[i] = 0.0;
}

static double fillD3GDT3 (double r[NR], double s[NT], double t, double p) {
    double result = 0.0;
    return result;
}

static double fillD3GDT2DP (double r[NR], double s[NT], double t, double p) {
    double result = 0.0;
    return result;
}

static double fillD3GDTDP2 (double r[NR], double s[NT], double t, double p) {
    double result = 0.0;
    return result;
}

static double fillD3GDP3 (double r[NR], double s[NT], double t, double p) {
    double result = 0.0;
    return result;
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
                for (i=0;  i<NS; i++) fprintf(stderr, "   %20.20s %13.6g %13.13s %13.6g %13.6g %13.6g\n", liquid[i+NA].label, xSpecies[i+NA], "", sOld[i], dgds[i], sNew[i]-sOld[i]);
                for (i=NS; i<NT; i++) fprintf(stderr, "   %20.20s %13.13s %13.13s %13.6g %13.6g %13.6g\n", "order CN[*]", "", "", sOld[i], dgds[i], sNew[i]-sOld[i]);
                fprintf(stderr, " sNorm             = %20.13g\n", sNorm);
                fprintf(stderr, " dgdsNorm          = %20.13g\n", dgdsNORM);
                fprintf(stderr, " 10*DBL_EPSILON    = %20.13g\n", 10.0*DBL_EPSILON);
                fprintf(stderr, " DBL_EPSILON^(2/3) = %20.13g\n", pow(DBL_EPSILON, 2.0/3.0));
                fprintf(stderr, " DBL_EPSILON^(1/2) = %20.13g\n", sqrt(DBL_EPSILON));
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
