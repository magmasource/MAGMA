//
//  main.c
//  TestSulfideLiquid
//
//  Created by Mark Ghiorso on 3/23/12.
//  Copyright (c) 2012 OFM Research Inc. All rights reserved.
//

#include "silmin.h"
#include "recipes.h"

int testSLq(int mask, double t, double p,
            int na,          /* Expected number of endmember components                 */
            int nr,          /* Expected number of independent compositional variables  */
            char **names,    /* array of strings of names of endmember components       */
            char **formulas, /* array of strings of formulas of endmember components    */
            double *r,       /* array of indepependent compos variables, check bounds   */
            double *m        /* array of moles of endmember components, check bounds    */
            );

void conSLq(int inpMask, int outMask, double t, double p,
            double *e,      /* comp of biotite in moles of elements                     */
            double *m,      /* comp of biotite in moles of endmember components         */
            double *r,      /* comp of biotite in terms of the independent comp var     */
            double *x,      /* comp of biotite in mole fractions of endmember comp      */
            double **dm,    /* Jacobian matrix: dm[i][j] = dr[i]/dm[j]                  */
            double ***d2m,  /* vector of matrices: d2m[i][j][k] = d2r[i]/dm[j]dm[k]     */
            double **dr,    /* Jacobian matrix: dr[i][j] = dx[i]/dr[j]                  */
            double ****d3m  /* 3rd deriv matrix: d3m[i][j][k][l]=d3r[i]/dm[j]dm[k]dm[l] */
            );

void dispSLq(int mask, double t, double p, double *x,
             char **formula            /* Mineral formula for interface display MASK: 1 */
             );

void actSLq(int mask, double t, double p, double *r, 
            double *a,  /* (pointer to a[]) activities              BINARY MASK: 0001 */
            double *mu, /* (pointer to mu[]) chemical potentials    BINARY MASK: 0010 */
            double **dx /* (pointer to dx[][]) d(a[])/d(x[])        BINARY MASK: 0100 */
            );          /* exclusion criteria applied to results if BINARY MASK: 1000 */  

void gmixSLq(int mask, double t, double p, double *r, 
             double *gmix, /* Gibbs energy of mixing             BINARY MASK: 0001 */
             double *dx,   /* (pointer to dx[]) d(g)/d(x[])      BINARY MASK: 0010 */
             double **dx2, /* (pointer to dx2[][]) d2(g)/d(x[])2 BINARY MASK: 0100 */
             double ***dx3 /* (pointer to dx3[][][]) d3(g)/d(x[])3 NARY MASK: 1000 */
             );

void hmixSLq(int mask, double t, double p, double *r, 
             double *hmix /* Enthalpy of mixing BINARY MASK: 1 */
             );

void smixSLq(int mask, double t, double p, double *r, 
             double *smix, /* Entropy of mixing                  BINARY MASK: 001 */
             double *dx,   /* (pointer to dx[]) d(s)/d(x[])      BINARY MASK: 010 */
             double **dx2  /* (pointer to dx2[][]) d2(s)/d(x[])2 BINARY MASK: 100 */
             );

void cpmixSLq(int mask, double t, double p, double *r, 
              double *cpmix, /* Heat capacity of mixing               BINARY MASK: 001 */
              double *dt,    /* d(cp)/d(t)                            BINARY MASK: 010 */
              double *dx     /* d(cp)/d(x[])d(t)                      BINARY MASK: 100 */
              );

void vmixSLq(int mask, double t, double p, double *r, 
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
             );    

BulkSystem bulkSystem[] = { 
    { "O"  , OTHER,  0.0,   15.994  , NULL, NULL, 0.0, 0.0, 0.0,  0.0, 0.0,  0.0, 0.0, 0.0, 0.0 },
    { "S"  , OTHER,  0.0,   32.065  , NULL, NULL, 0.0, 0.0, 0.0,  0.0, 0.0,  0.0, 0.0, 0.0, 0.0 },
    { "Fe" , OTHER,  0.0,   55.845  , NULL, NULL, 0.0, 0.0, 0.0,  0.0, 0.0,  0.0, 0.0, 0.0, 0.0 },
    { "Ni" , OTHER,  0.0,   58.6934 , NULL, NULL, 0.0, 0.0, 0.0,  0.0, 0.0,  0.0, 0.0, 0.0, 0.0 },
    { "Cu" , OTHER,  0.0,   63.546  , NULL, NULL, 0.0, 0.0, 0.0,  0.0, 0.0,  0.0, 0.0, 0.0, 0.0 }
};
int nc = (sizeof bulkSystem / sizeof(struct _bulkSystem));

Liquid xMeltsLiquid[] = {
    {"O", NULL,
        {                /* ThermoRef structure block */
            0.0,  	         /* H ref (J)			      */
            0.0,		     /* S ref (J/K)			      */
            0.0,		     /* V ref (J/bar)			  */
            CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
            EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
        },{              /* ThermoLiq structure block */
            0.0,		     /* V liq (J) 	              */
            EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
            1673.0,		     /* T fusion (K)		      */
            0.0,		     /* S fusion (J/K)  	      */
            0.0,		     /* Cp liquid (J/K)           */
            0.0 		     /* T glass transition (K)    */
        }
    },
    {"S", NULL,
        {                /* ThermoRef structure block */
            0.0,  	         /* H ref (J)			      */
            0.0,		     /* S ref (J/K)			      */
            0.0,		     /* V ref (J/bar)			  */
            CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
            EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
        },{              /* ThermoLiq structure block */
            0.0,		     /* V liq (J) 	              */
            EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
            1673.0,		     /* T fusion (K)		      */
            0.0,		     /* S fusion (J/K)  	      */
            0.0,		     /* Cp liquid (J/K)           */
            0.0 		     /* T glass transition (K)    */
        }
    },
    {"Fe", NULL,
        {                /* ThermoRef structure block */
            0.0,  	         /* H ref (J)			      */
            0.0,		     /* S ref (J/K)			      */
            0.0,		     /* V ref (J/bar)			  */
            CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
            EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
        },{              /* ThermoLiq structure block */
            0.0,		     /* V liq (J) 	              */
            EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
            1673.0,		     /* T fusion (K)		      */
            0.0,		     /* S fusion (J/K)  	      */
            0.0,		     /* Cp liquid (J/K)           */
            0.0 		     /* T glass transition (K)    */
        }
    },
    {"Ni", NULL,
        {                /* ThermoRef structure block */
            0.0,  	         /* H ref (J)			      */
            0.0,		     /* S ref (J/K)			      */
            0.0,		     /* V ref (J/bar)			  */
            CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
            EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
        },{              /* ThermoLiq structure block */
            0.0,		     /* V liq (J) 	              */
            EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
            1673.0,		     /* T fusion (K)		      */
            0.0,		     /* S fusion (J/K)  	      */
            0.0,		     /* Cp liquid (J/K)           */
            0.0 		     /* T glass transition (K)    */
        }
    },
    {"Cu", NULL,
        {                /* ThermoRef structure block */
            0.0,  	         /* H ref (J)			      */
            0.0,		     /* S ref (J/K)			      */
            0.0,		     /* V ref (J/bar)			  */
            CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
            EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
        },{              /* ThermoLiq structure block */
            0.0,		     /* V liq (J) 	              */
            EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
            1673.0,		     /* T fusion (K)		      */
            0.0,		     /* S fusion (J/K)  	      */
            0.0,		     /* Cp liquid (J/K)           */
            0.0 		     /* T glass transition (K)    */
        }
    },
};

int    nlc     = (sizeof xMeltsLiquid / sizeof(struct _liquid));
int    nls     = (sizeof xMeltsLiquid / sizeof(struct _liquid));
Liquid *liquid = xMeltsLiquid;

Oxygen oxygen;

#define        INCLUDE_IN_CALIBRATION TRUE
#define DO_NOT_INCLUDE_IN_CALIBRATION FALSE

#define        INCLUDE_IN_STD_SET TRUE
#define DO_NOT_INCLUDE_IN_STD_SET FALSE


Solids xMeltsSolids[] = {
    {"sulfideLiquid", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
        0.0, 0.0,
        {                /* ThermoRef structure                                   */
            0.0, 0.0, 0.0,                    /* Dummy entries to ThermoRef structure */ 
            CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}}, 
            EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
        },
        {                /* ThermoData structure                                  */
            0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
            0.0, 0.0, 0.0,
            0.0, 0.0, 0.0
        },
        0, 0,
        testSLq,         /* Pointer to testOlv  : test expected number and order  */
        conSLq,          /* Pointer to conOlv   : moles to indep comp variables   */
        actSLq,          /* Pointer to actOlv   : activities, chemical potentials */
        gmixSLq,         /* Pointer to gmixOlv  : Gibbs free energy of mixing     */
        hmixSLq,         /* Pointer to hmixOlv  : Enthaly of mixing               */
        smixSLq,         /* Pointer to smixOlv  : Entropy of mixing               */
        cpmixSLq,        /* Pointer to cpmixOlv : Heat capacity of mixing         */
        vmixSLq,         /* Pointer to vmixOlv  : Volume of mixing                */
        dispSLq          /* Pointer to dispOlv  : Formula for interface display   */
    },
    {"O", COMPONENT, "O", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
        0.0, 0.0,
        {                 /* ThermoRef structure                                  */
            0.0,              /* H ref (J)                                            */
            0.0,              /* S ref (J/K)                                          */
            0.0,              /* V ref (J/bar)                                        */
            CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},           
            EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
        }
    },
    {"S", COMPONENT, "S", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
        0.0, 0.0,
        {                 /* ThermoRef structure                                  */
            0.0,              /* H ref (J)                                            */
            0.0,              /* S ref (J/K)                                          */
            0.0,              /* V ref (J/bar)                                        */
            CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},           
            EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
        }
    },
    {"Fe", COMPONENT, "Fe", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
        0.0, 0.0,
        {                 /* ThermoRef structure                                  */
            0.0,              /* H ref (J)                                            */
            0.0,              /* S ref (J/K)                                          */
            0.0,              /* V ref (J/bar)                                        */
            CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},           
            EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
        }
    },
    {"Ni", COMPONENT, "Ni", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
        0.0, 0.0,
        {                 /* ThermoRef structure                                  */
            0.0,              /* H ref (J)                                            */
            0.0,              /* S ref (J/K)                                          */
            0.0,              /* V ref (J/bar)                                        */
            CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},           
            EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
        }
    },
    {"Cu", COMPONENT, "Cu", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
        0.0, 0.0,
        {                 /* ThermoRef structure                                  */
            0.0,              /* H ref (J)                                            */
            0.0,              /* S ref (J/K)                                          */
            0.0,              /* V ref (J/bar)                                        */
            CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},           
            EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
        }
    }
};

int    npc     = (sizeof xMeltsSolids / sizeof(struct _solids));
Solids *solids = xMeltsSolids;

int calculationMode = MODE_DEFAULT;
SilminState *silminState;

#define TEST(x) \
flag = ( ABS(temp - (x)) <= sqrt(sqrt(TAU))*ABS(x) ) \
? "OK " : "BAD"

int main()
{
    int n, i, j, k, l, NC, NX, doRandom=TRUE;
    char *flag;
    char **names, **formulas, *dispForm;
    double t = 1200.0 + 273.15;
    double p = 1000.0;
    double *moles, *x, *a, *mu, **dadx, g, *dgdx, **d2gdx2, h, s, *dsdx,
    **d2sdx2, cp, dcpdt, v, *dvdx, **d2vdx2, dvdt, dvdp, d2vdt2,
    d2vdtdp, d2vdp2, deltaT, deltaP, *deltaX, *deltaM, temp, *xtemp,
    *mtemp, mtotal, *vtemp, **drdm, **dtemp, ***d2rdm2, **dxdr,
    *dcpdx, *d2vdxdt, *d2vdxdp, ****d3rdm3, ***d3gdx3, ***d2temp,
    **v2temp;
    float ftemp;
    
    printf("Input test compositions (y or n)? ");
    if (tolower(getchar()) == 'y') doRandom = FALSE;
    getchar();
    
    printf("Do calculations at %7.2f C (y or n)? ", t-273.15);
    if (tolower(getchar()) != 'y') {
        getchar();
        printf("Input a temperature in (C):"); scanf("%f", &ftemp); t = ((double) ftemp) +273.15;
        getchar();
    } else getchar();
    
    printf("Do calculations at %7.2f bars (y or n)? ", p);
    if (tolower(getchar()) != 'y') {
        getchar();
        printf("Input a pressure in (bars):"); scanf("%f", &ftemp); p = (double) ftemp;
        getchar();
    } else getchar();
    
    printf("*******************************************************\n");
    printf("* Calculations at %7.2f (C) and %8.2f (bars) *\n", t-273.15, p);
    printf("*******************************************************\n\n");
    
    /**************************************************************************
     Compute constants for numerical differentiation                        
     **************************************************************************/
    
    deltaT = sqrt(TAU)*(1.0+ABS(t));
    deltaP = sqrt(TAU)*(1.0+ABS(p));
    
    /**************************************************************************
     Evaluate activity-composition relations for all solid phases          
     **************************************************************************/
    
    for (n=0; n<npc; n++) {
        if (solids[n].type == PHASE && solids[n].activity != NULL) {
            
            for (i=n+1; solids[i].type == COMPONENT && i<npc; i++); i--;
            
            NC =  i - n;   /* Number of end-member components in solid solution */
            NX = NC - 1;   /* Number of independent compositional variables     */
            
            /********************************************************************
             Allocate space for required vectors and matrices                 
             ********************************************************************/
            
            moles   = vector(0, NC-1);
            mtemp   = vector(0, NC-1);
            x       = vector(0, NX-1);
            xtemp   = vector(0, NX-1);
            vtemp   = vector(0, NC-1);
            deltaM  = vector(0, NC-1);
            deltaX  = vector(0, NX-1);
            a       = vector(0, NC-1);
            mu      = vector(0, NC-1);
            dgdx    = vector(0, NX-1);
            dsdx    = vector(0, NX-1);
            dvdx    = vector(0, NX-1);
            dcpdx   = vector(0, NX-1);
            d2vdxdt = vector(0, NX-1);
            d2vdxdp = vector(0, NX-1);
            
            drdm   = matrix(0, NX-1, 0, NC-1);
            dxdr   = matrix(0, NC-1, 0, NX-1);
            dtemp  = matrix(0, NX-1, 0, NC-1);
            dadx   = matrix(0, NC-1, 0, NX-1);
            d2gdx2 = matrix(0, NX-1, 0, NX-1);
            d2sdx2 = matrix(0, NX-1, 0, NX-1);
            d2vdx2 = matrix(0, NX-1, 0, NX-1);
            v2temp = matrix(0, NX-1, 0, NX-1);
            
            d2rdm2 = (double ***) malloc((unsigned) NX*sizeof(double **));
            for (i=0; i<NX; i++) d2rdm2[i] = matrix(0, NC-1, 0, NC-1);
            d2temp = (double ***) malloc((unsigned) NX*sizeof(double **));
            for (i=0; i<NX; i++) d2temp[i] = matrix(0, NC-1, 0, NC-1);
            
            d3rdm3 = (double ****) malloc((unsigned) NX*sizeof(double ***));
            for (i=0; i<NX; i++) {
                d3rdm3[i] = (double ***) malloc((unsigned) NC*sizeof(double **));
                for (j=0; j<NC; j++) d3rdm3[i][j] = matrix(0, NC-1, 0, NC-1);
            }
            
            d3gdx3 = (double ***) malloc((unsigned) NX*sizeof(double **));
            for (i=0; i<NX; i++) d3gdx3[i] = matrix(0, NX-1, 0, NX-1);
            
            names    = (char **) malloc((unsigned) NC*sizeof(char *));
            formulas = (char **) malloc((unsigned) NC*sizeof(char *));
            for (i=0; i<NC; i++) {
                names[i]    = (char *) malloc((unsigned) 
                                              (strlen(solids[n+1+i].label)+1)*sizeof(char));
                formulas[i] = (char *) malloc((unsigned) 
                                              (strlen(solids[n+1+i].formula)+1)*sizeof(char));
            }
            
            /********************************************************************
             Test internal consistency of SOL_STRUCT_DATA.H include file
             and conventions adopted in coding the routine. Do not check bounds
             constraints, since there is no a priori way of knowing what they 
             may be.
             ********************************************************************/
            
            for (i=0; i<NC; i++) {
                names[i]    = strcpy(names[i], solids[n+1+i].label);
                formulas[i] = strcpy(formulas[i], solids[n+1+i].formula);
            }
            if (!(*solids[n].test)(FIRST | SECOND | THIRD | FOURTH, t, p, 
                                   NC, NX, names, formulas, (double *) NULL, (double *) NULL)) exit(0);
            
            /******************************************************************** 
             Compute composition of the solid phase (moles) 
             ********************************************************************/
            
            if (doRandom) 
                for (i=0; i<NC; i++) moles[i] = ((double) rand())/((double) RAND_MAX);
            else {
                for (i=0; i<NC; i++) {
                    printf("Input moles of %15.15s (%15.15s): ", names[i], formulas[i]);
                    scanf("%f", &ftemp); moles[i] = (double) ftemp; getchar();
                }
            }
            for (i=0; i<NC; i++) deltaM[i] = sqrt(TAU)*(1.0+ABS(moles[i]));
            
            if (!(*solids[n].test)(SIXTH, t, p, 0, 0, NULL, NULL, NULL, moles)) printf(
                                                                                       "BAD The moles vector apparently violates bound constraints.\n"); 
            
            /********************************************************************
             Transform mole vector into independent compositional variables
             and test back conversion algorithm
             ********************************************************************/
            
            /* Convert moles of endmembers to independent compositional variables
             and mole fractions of endmembers. Get derivatives of the indepen-
             dent compositional variables with respect to moles of endmembers  */
            
            (*solids[n].convert)(SECOND, THIRD | FOURTH | FIFTH | SIXTH | EIGHTH,
                                 t, p, (double *) NULL, moles, x, mtemp, drdm, d2rdm2,
                                 (double **) NULL, d3rdm3);
            for (i=0; i<NX; i++) deltaX[i] = sqrt(TAU)*(1.0+ABS(x[i]));
            
            if (!(*solids[n].test)(FIFTH, t, p, 0, 0, NULL, NULL, x, NULL)) printf(
                                                                                   "BAD The r vector apparently violates bound constraints.\n"); 
            
            /* Output moles and independent compositional variables */
            for (i=0; i<NC; i++) {
                printf("    moles[%-15.15s] = %13.6g", solids[n+i+1].label, 
                       moles[i]);
                if (i < NX) printf("    r[%3d] = %13.6g\n", i, x[i]);
                else        printf("\n");
            }
            printf("\n");
            
            /* Output formula of the solid phase */
            (*solids[n].display)(FIRST, t, p, x, &dispForm);
            printf("    formula %s\n", dispForm); free(dispForm);
            printf("\n");
            
            /* Calculate total moles */
            for (i=0, mtotal=0.0; i<NC; i++) mtotal += moles[i];
            
            /* Check calculated mole fractions for internal consistency */
            for (i=0; i<NC; i++) {
                temp = mtemp[i];
                TEST(moles[i]/mtotal);
                printf("%s X[%s] = %g (%g, %s)\n", flag, solids[n+i+1].label,
                       moles[i]/mtotal, temp, "from convert SECOND->FOURTH");
            }
            printf("\n");
            
            /* print and test drdm[] */
            for (i=0; i<NC; i++) {
                for (j=0; j<NC; j++) mtemp[j] = moles[j];
                mtemp[i] += deltaM[i];
                (*solids[n].convert)(SECOND, THIRD, t, p, (double *) NULL, mtemp, 
                                     xtemp, (double *) NULL, (double **) NULL, (double ***) NULL,
                                     (double **) NULL, (double ****) NULL);
                for (j=0; j<NX; j++) {
                    temp = (xtemp[j]-x[j])/deltaM[i];
                    TEST(drdm[j][i]);
                    printf("%s drdm[%d][%d] = %g (%g, %s)\n", flag, j, i, drdm[j][i],
                           temp, "from r");
                }
            }
            printf("\n");
            
            /* print and test d2rdm2[][][] */
            for (i=0; i<NC; i++) {
                for (j=0; j<NC; j++) {
                    for (k=0; k<NC; k++) mtemp[k] = moles[k];
                    mtemp[j] += deltaM[j];
                    (*solids[n].convert)(SECOND, FIFTH, t, p, (double *) NULL, mtemp,
                                         (double *) NULL, (double *) NULL, dtemp, (double ***) NULL,
                                         (double **) NULL, (double ****) NULL);
                    for (k=0; k<NX; k++) {
                        temp = (dtemp[k][i]-drdm[k][i])/deltaM[j];
                        TEST(d2rdm2[k][i][j]);
                        printf("%s d2rdm2[%d][%d][%d] = %g (%g, %s)\n", flag, k, i, j,
                               d2rdm2[k][i][j], temp, "from drdm[][]");
                    }
                }
            }
            printf("\n");
            
            /* print and test d3rdm3[][][] */
            for (i=0; i<NC; i++) {
                for (j=0; j<NC; j++) {
                    for (k=0; k<NC; k++) {
                        for (l=0; l<NC; l++)  mtemp[l] = moles[l];
                        mtemp[k] += deltaM[k];
                        (*solids[n].convert)(SECOND, SIXTH, t, p, (double *) NULL, mtemp,
                                             (double *) NULL, (double *) NULL, (double **) NULL, d2temp,
                                             (double **) NULL, (double ****) NULL);
                        for (l=0; l<NX; l++) {
                            temp = (d2temp[l][i][j]-d2rdm2[l][i][j])/deltaM[k];
                            TEST(d3rdm3[l][i][j][k]);
                            printf("%s d3rdm3[%d][%d][%d][%d] = %g (%g, %s)\n", flag, l, i, j,
                                   k, d3rdm3[l][i][j][k], temp, "from d2rdm2[][]");
                        }
                    }
                }
            }
            printf("\n");
            
            /* Convert independent compositional variables into mole fractions 
             and obtain derivatives of the mole fractions with respect to r    */
            (*solids[n].convert)(THIRD, FOURTH | SEVENTH, t, p, (double *) NULL,
                                 (double *) NULL, x, mtemp, (double **) NULL, (double ***) NULL,
                                 dxdr, (double ****) NULL);
            
            /* Check calculated mole fractions for internal consistency */
            for (i=0; i<NC; i++) {
                temp = mtemp[i];
                TEST(moles[i]/mtotal);
                printf("%s X[%s] = %g (%g, %s)\n", flag, solids[n+i+1].label, 
                       moles[i]/mtotal, temp, "from convert THIRD->FOURTH");
            }
            printf("\n");
            
            /* print and test dxdr[] */
            for (i=0; i<NX; i++) {
                for (j=0; j<NX; j++) xtemp[j] = x[j];
                xtemp[i] += deltaX[i];
                (*solids[n].convert)(THIRD, FOURTH, t, p, (double *) NULL, 
                                     (double *) NULL, xtemp, mtemp, (double **) NULL, 
                                     (double ***) NULL, (double **) NULL, (double ****) NULL);
                for (j=0; j<NC; j++) {
                    temp = (mtemp[j]-moles[j]/mtotal)/deltaX[i];
                    TEST(dxdr[j][i]);
                    printf("%s dxdr[%d][%d] = %g (%g, %s)\n", flag, j, i, dxdr[j][i],
                           temp, "from X");
                }
            }
            printf("\n");
            
            /********************************************************************
             Evaluate Gibbs energy of mixing and its derivatives
             ********************************************************************/
            
            (*solids[n].gmix)(FIRST | SECOND | THIRD | FOURTH, t, p, x,
                              &g, dgdx, d2gdx2, d3gdx3);
            printf("    g = %g\n", g); 
            
            /* print and test dgdx[] */
            for (i=0; i<NX; i++) {
                for (j=0; j<NX; j++) xtemp[j] = x[j];
                xtemp[i] += deltaX[i];
                (*solids[n].gmix)(FIRST, t, p, xtemp, &temp, (double *) NULL, 
                                  (double **) NULL, (double ***) NULL);
                temp = (temp-g)/deltaX[i];
                TEST(dgdx[i]);
                printf("%s dgdx[%d] = %g (%g, %s)\n", flag, i, dgdx[i], temp,
                       "from g");
            } 
            
            /* print and test d2gdx2[][] */
            for (i=0; i<NX; i++) {
                for (j=0; j<NX; j++) {
                    for (k=0; k<NX; k++) xtemp[k] = x[k];
                    xtemp[j] += deltaX[j];
                    (*solids[n].gmix)(SECOND, t, p, xtemp, (double *) NULL, vtemp,
                                      (double **) NULL, (double ***) NULL);
                    temp = (vtemp[i]-dgdx[i])/deltaX[j];
                    TEST(d2gdx2[i][j]);
                    printf("%s d2gdx2[%d][%d] = %g (%g, %s)\n", flag, i, j, 
                           d2gdx2[i][j], temp, "from dgdx[]");
                }
            }
            printf("\n");
            
            /* print and test d3gdx3[][][] */
            for (i=0; i<NX; i++) {
                for (j=0; j<NX; j++) {
                    for (k=0; k<NX; k++) {
                        for (l=0; l<NX; l++)  xtemp[l] = x[l];
                        xtemp[k] += deltaX[k];
                        (*solids[n].gmix)(THIRD, t, p, xtemp, (double *) NULL,
                                          (double *) NULL, v2temp, (double ***) NULL);
                        temp = (v2temp[i][j]-d2gdx2[i][j])/deltaX[k];
                        TEST(d3gdx3[i][j][k]);
                        printf("%s d3gdx3[%d][%d][%d] = %g (%g, %s)\n", flag, i, j,
                               k, d3gdx3[i][j][k], temp, "from d2gdx2[]");
                    }
                }
            }
            printf("\n");
            
            /********************************************************************
             Evaluate activity routines
             ********************************************************************/
            
            (*solids[n].activity)(FIRST | SECOND | THIRD, t, p, x, a, mu, dadx);
            
            for (i=0; i<NC; i++) {
                for (j=0; j<NC; j++) mtemp[j] = moles[j];
                mtemp[i] += deltaM[i];
                for (j=0, mtotal=0.0; j<NC; j++) mtotal += mtemp[j];
                (*solids[n].convert)(SECOND, THIRD, t, p, (double *) NULL, mtemp, 
                                     xtemp, (double *) NULL, (double **) NULL, (double ***) NULL,
                                     (double **) NULL, (double ****) NULL);
                (*solids[n].gmix)(FIRST, t, p, xtemp, &temp, (double *) NULL, 
                                  (double **) NULL, (double ***) NULL);
                temp = mtotal*((temp-g)/deltaM[i]) + (g+temp)/2.0;
                temp = exp(temp/(8.3143*t));
                TEST(a[i]);
                printf("%s a[%s] = %g (%g, %s)\n", flag, solids[n+i+1].label, a[i],
                       temp, "from g");
            }
            
            /* print and test chemical potentials */
            for (i=0; i<NC; i++) {
                temp = 8.3143*t*log(a[i]);
                TEST(mu[i]);
                printf("%s (mu-mu0)[%s] = %g (%g, %s)\n", flag, 
                       solids[n+i+1].label, mu[i], temp, "from a[]");
            }
            
            /* print and test dadx[][] */
            for (i=0; i<NC; i++) {
                for (j=0; j<NX; j++) {
                    for (k=0; k<NX; k++) xtemp[k] = x[k];
                    xtemp[j] += deltaX[j];
                    (*solids[n].activity)(FIRST, t, p, xtemp, vtemp, 
                                          (double *) NULL, (double **) NULL);
                    temp = (vtemp[i]-a[i])/deltaX[j];
                    TEST(dadx[i][j]);
                    printf("%s dadx[%s][%d] = %g (%g, %s)\n", flag, 
                           solids[n+i+1].label, j, dadx[i][j], temp, "from a[]");
                }
            }
            printf("\n");
            
            /********************************************************************
             Evaluate entropy of mixing and its derivatives
             ********************************************************************/
            
            (*solids[n].smix)(FIRST | SECOND | THIRD, t, p, x, &s, dsdx, d2sdx2);
            
            /* print and test s */
            (*solids[n].gmix)(FIRST, t+deltaT, p, x, &temp, (double *) NULL, 
                              (double **) NULL, (double ***) NULL);
            temp = -(temp-g)/deltaT;
            TEST(s);
            printf("%s s = %g (%g, %s)\n", flag, s, temp, "from g"); 
            
            /* print and test dsdx[] */
            for (i=0; i<NX; i++) {
                for (j=0; j<NX; j++) xtemp[j] = x[j];
                xtemp[i] += deltaX[i];
                (*solids[n].smix)(FIRST, t, p, xtemp, &temp, (double *) NULL, 
                                  (double **) NULL);
                temp = (temp-s)/deltaX[i];
                TEST(dsdx[i]);
                printf("%s dsdx[%d] = %g (%g, %s)\n",flag, i, dsdx[i], temp,
                       "from s");
            }
            
            /* print and test d2ddx2[][] */
            for (i=0; i<NX; i++) {
                for (j=0; j<NX; j++) {
                    for (k=0; k<NX; k++) xtemp[k] = x[k];
                    xtemp[j] += deltaX[j];
                    (*solids[n].smix)(SECOND, t, p, xtemp, (double *) NULL, vtemp,
                                      (double **) NULL);
                    temp = (vtemp[i]-dsdx[i])/deltaX[j];
                    TEST(d2sdx2[i][j]);
                    printf("%s d2sdx2[%d][%d] = %g (%g, %s)\n", flag, i, j, 
                           d2sdx2[i][j], temp, "from dsdx[]");
                }
            }
            printf("\n");
            
            /********************************************************************
             Evaluate heat capacity of mixing and its derivatives
             ********************************************************************/
            
            (*solids[n].cpmix)(FIRST | SECOND | THIRD, t, p, x, &cp, &dcpdt,
                               dcpdx);
            
            /* print and test cp */
            (*solids[n].smix)(FIRST, t+deltaT, p, x, &temp, (double *) NULL, 
                              (double **) NULL);
            temp = t*(temp-s)/deltaT;
            TEST(cp);
            printf("%s cp = %g (%g, %s)\n", flag, cp, temp, "from s");
            
            /* print and test dcpdt */
            (*solids[n].cpmix)(FIRST, t+deltaT, p, x, &temp, (double *) NULL,
                               (double *) NULL);
            temp = (temp-cp)/deltaT;
            TEST(dcpdt);
            printf("%s dcpdt = %g (%g, %s)\n", flag, dcpdt, temp, "from cp");
            
            /* print and test dcpdx[] */
            for (i=0; i<NX; i++) {
                for (j=0; j<NX; j++) xtemp[j] = x[j];
                xtemp[i] += deltaX[i];
                (*solids[n].cpmix)(FIRST, t, p, xtemp, &temp, (double *) NULL, 
                                   (double *) NULL);
                temp = (temp-cp)/deltaX[i];
                TEST(dcpdx[i]);
                printf("%s dcpdx[%d] = %g (%g, %s)\n",flag, i, dcpdx[i], temp,
                       "from cp");
            }
            printf("\n");
            
            /********************************************************************
             Evaluate volume of mixing and its derivatives
             ********************************************************************/
            
            (*solids[n].vmix)(
                              FIRST | SECOND | THIRD | FOURTH | FIFTH | SIXTH | SEVENTH |EIGHTH
                              | NINTH | TENTH, t, p, x, &v, dvdx, d2vdx2, &dvdt, &dvdp, &d2vdt2,
                              &d2vdtdp, &d2vdp2, d2vdxdt, d2vdxdp);
            
            /* print and test v */
            (*solids[n].gmix)(FIRST, t, p+deltaP, x, &temp, (double *) NULL, 
                              (double **) NULL, (double ***) NULL);
            temp = (temp-g)/deltaP;
            flag = ( ABS(temp - v) <= sqrt(TAU)*ABS(g) ) ? "OK " : "BAD";
            printf("%s v = %g (%g, %s)\n", flag, v, temp, "from g"); 
            
            /* print and test dvdx[] */
            for (i=0; i<NX; i++) { 
                for (j=0; j<NX; j++) xtemp[j] = x[j];
                xtemp[i] += deltaX[i];
                (*solids[n].vmix)(FIRST, t, p, xtemp, &temp, (double *) NULL, 
                                  (double **) NULL, (double *) NULL, (double *) NULL, 
                                  (double *) NULL, (double *) NULL, (double *) NULL,
                                  (double *) NULL, (double *) NULL);
                temp = (temp-v)/deltaX[i];
                TEST(dvdx[i]);
                printf("%s dvdx[%d] = %g (%g, %s)\n", flag, i, dvdx[i], temp,
                       "from v");
            }
            
            /* print and test d2vdx2[][] */
            for (i=0; i<NX; i++) {
                for (j=0; j<NX; j++) { 
                    for (k=0; k<NX; k++) xtemp[k] = x[k];
                    xtemp[j] += deltaX[j];
                    (*solids[n].vmix)(SECOND, t, p, xtemp, (double *) NULL, vtemp,
                                      (double **) NULL, (double *) NULL, (double *) NULL, 
                                      (double *) NULL, (double *) NULL, (double *) NULL,
                                      (double *) NULL, (double *) NULL);
                    temp = (vtemp[i]-dvdx[i])/deltaX[j];
                    TEST(d2vdx2[i][j]);
                    printf("%s d2vdx2[%d][%d] = %g (%g, %s)\n", flag, i, j, 
                           d2vdx2[i][j], temp, "from dvdx[]");
                }
            }
            
            /* print and test dvdt */
            (*solids[n].vmix)(FIRST, t+deltaT, p, x, &temp, (double *) NULL, 
                              (double **) NULL, (double *) NULL, (double *) NULL, 
                              (double *) NULL, (double *) NULL, (double *) NULL,
                              (double *) NULL, (double *) NULL);
            temp = (temp-v)/deltaT;
            TEST(dvdt);
            printf("%s dvdt = %g (%g, %s)\n", flag, dvdt, temp, "from v");
            
            /* print and test dvdp */
            (*solids[n].vmix)(FIRST, t, p+deltaP, x, &temp, (double *) NULL, 
                              (double **) NULL, (double *) NULL, (double *) NULL, 
                              (double *) NULL, (double *) NULL, (double *) NULL,
                              (double *) NULL, (double *) NULL);
            temp = (temp-v)/deltaP;
            TEST(dvdp);
            printf("%s dvdp = %g (%g, %s)\n", flag, dvdp, temp, "from v"); 
            
            /* print and test d2vdt2 */
            (*solids[n].vmix)(FOURTH, t+deltaT, p, x, (double *) NULL, 
                              (double *) NULL, (double **) NULL, &temp, (double *) NULL, 
                              (double *) NULL, (double *) NULL, (double *) NULL,
                              (double *) NULL, (double *) NULL);
            temp = (temp-dvdt)/deltaT;
            TEST(d2vdt2);
            printf("%s d2vdt2 = %g (%g, %s)\n", flag, d2vdt2, temp, "from dvdt"); 
            
            /* print and test d2vdtdp */
            (*solids[n].vmix)(FOURTH, t, p+deltaP, x, (double *) NULL, 
                              (double *) NULL, (double **) NULL, &temp, (double *) NULL,
                              (double *) NULL, (double *) NULL, (double *) NULL,
                              (double *) NULL, (double *) NULL);
            temp = (temp-dvdt)/deltaP;
            TEST(d2vdtdp);
            printf("%s d2vdtdp = %g (%g, %s)\n", flag, d2vdtdp, temp, 
                   "from dvdt"); 
            
            /* print and test d2vdtdp */
            (*solids[n].vmix)(FIFTH, t+deltaT, p, x, (double *) NULL, 
                              (double *) NULL, (double **) NULL, (double *) NULL, &temp, 
                              (double *) NULL, (double *) NULL, (double *) NULL,
                              (double *) NULL, (double *) NULL);
            temp = (temp-dvdp)/deltaT;
            TEST(d2vdtdp);
            printf("%s d2vdtdp = %g (%g, %s)\n", flag, d2vdtdp, temp, 
                   "from dvdp"); 
            
            /* print and test d2vdp2 */
            (*solids[n].vmix)(FIFTH, t, p+deltaP, x, (double *) NULL, 
                              (double *) NULL, (double **) NULL, (double *) NULL, &temp, 
                              (double *) NULL, (double *) NULL, (double *) NULL,
                              (double *) NULL, (double *) NULL);
            temp = (temp-dvdp)/deltaP;
            TEST(d2vdp2);
            printf("%s d2vdp2 = %g (%g, %s)\n", flag, d2vdp2, temp, "from dvdp"); 
            
            /* print and test d2vdxdt[] */
            for (i=0; i<NX; i++) { 
                for (j=0; j<NX; j++) xtemp[j] = x[j];
                xtemp[i] += deltaX[i];
                (*solids[n].vmix)(FOURTH, t, p, xtemp, (double *) NULL, 
                                  (double *) NULL, (double **) NULL, &temp, (double *) NULL, 
                                  (double *) NULL, (double *) NULL, (double *) NULL, 
                                  (double *) NULL, (double *) NULL);
                temp = (temp-dvdt)/deltaX[i];
                TEST(d2vdxdt[i]);
                printf("%s d2vdxdt[%d] = %g (%g, %s)\n", flag, i, d2vdxdt[i], temp,
                       "from dvdt");
            }
            
            /* print and test d2vdxdp[] */
            for (i=0; i<NX; i++) { 
                for (j=0; j<NX; j++) xtemp[j] = x[j];
                xtemp[i] += deltaX[i];
                (*solids[n].vmix)(FIFTH, t, p, xtemp, (double *) NULL, 
                                  (double *) NULL, (double **) NULL, (double *) NULL, &temp, 
                                  (double *) NULL, (double *) NULL, (double *) NULL, 
                                  (double *) NULL, (double *) NULL);
                temp = (temp-dvdp)/deltaX[i];
                TEST(d2vdxdp[i]);
                printf("%s d2vdxdp[%d] = %g (%g, %s)\n", flag, i, d2vdxdp[i], temp,
                       "from dvdp");
            }
            printf("\n");
            
            /********************************************************************
             Evaluate enthalpy of mixing
             ********************************************************************/
            
            (*solids[n].hmix)(FIRST, t, p, x, &h);
            
            /* print and test h */
            temp = g + t*s;
            TEST(h);
            printf("%s h = %g (%g, %s)\n", flag, h, temp, "from g and s"); 
            printf("\n");
            
            /******************************************************************** 
             Destroy space allocated for vectors and matrices                 
             ********************************************************************/
            
            free_vector(  moles, 0, NC-1);
            free_vector(  mtemp, 0, NC-1);
            free_vector(      x, 0, NX-1);
            free_vector(  xtemp, 0, NX-1);
            free_vector(  vtemp, 0, NC-1);
            free_vector( deltaM, 0, NC-1);
            free_vector( deltaX, 0, NX-1);
            free_vector(      a, 0, NC-1);
            free_vector(     mu, 0, NC-1);
            free_vector(   dgdx, 0, NX-1);
            free_vector(   dsdx, 0, NX-1);
            free_vector(   dvdx, 0, NX-1);
            free_vector(  dcpdx, 0, NX-1);
            free_vector(d2vdxdt, 0, NX-1);
            free_vector(d2vdxdp, 0, NX-1);
            
            free_matrix(  drdm, 0, NX-1, 0, NC-1);
            free_matrix(  dxdr, 0, NC-1, 0, NX-1);
            free_matrix( dtemp, 0, NX-1, 0, NC-1);
            free_matrix(  dadx, 0, NC-1, 0, NX-1);
            free_matrix(d2gdx2, 0, NX-1, 0, NX-1);
            free_matrix(d2sdx2, 0, NX-1, 0, NX-1);
            free_matrix(d2vdx2, 0, NX-1, 0, NX-1);
            free_matrix(v2temp, 0, NX-1, 0, NX-1);
            
            for (i=0; i<NX; i++) free_matrix(d2rdm2[i], 0, NC-1, 0, NC-1);
            free(d2rdm2);
            for (i=0; i<NX; i++) free_matrix(d2temp[i], 0, NC-1, 0, NC-1);
            free(d2temp);
            for (i=0; i<NX; i++) free_matrix(d3gdx3[i], 0, NX-1, 0, NX-1);
            free(d3gdx3);
            for (i=0; i<NX; i++) {
                for (j=0; j<NC; j++) free_matrix(d3rdm3[i][j],0,NC-1,0,NC-1);
                free(d3rdm3[i]);
            }
            free(d3rdm3);
            
            for (i=0; i<NC; i++) {free(names[i]); free(formulas[i]);}
            free(names);
            free(formulas);
        }
    }
    return 0;
}