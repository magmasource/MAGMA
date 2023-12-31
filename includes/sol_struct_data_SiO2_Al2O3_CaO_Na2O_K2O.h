#ifndef _Sol_Struct_Data_h
#define _Sol_Struct_Data_h

#ifdef FOWLER
#undef FOWLER
#endif

/*
MELTS Source Code: RCS $Log: sol_struct_data.h,v $
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Include file for initializing solids data structure
**        (file: SOL_STRUCT_DATA.H)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  September 18, 1990   Original Version
**              Data taken from PARAMS.DAT file (SILREG V3.0)
**      V1.1-1  Mark S. Ghiorso  April 29, 1991
**              Finalized data structures and preliminary contents
**      V1.1-2  Mark S. Ghiorso  September 6, 1991
**              Removed initialization of defunct solids[] elements
**      V1.1-3  Mark S. Ghiorso  September 26, 1991
**              Added thermodynamic properties for pyrophanite
**      V1.1-4  Mark S. Ghiorso  October 24, 1991
**              Added to and reorganized thermodynamic properties of
**              clinopyroxenes
**      V1.1-5  Mark S. Ghiorso  November 2, 1991
**              Tested new formulaToMwStoich code, and changed name of
**              "clinopyroxenes" to "pyroxenes"
**      V1.1-6  Mark S. Ghiorso  November 7, 1991
**              Corrected errors in enthalpies of formation of 
**              clinoenstatite and hedenbergite
**      V1.1-7  Mark S. Ghiorso  April 7, 1992
**              (1) Added biotite and garnet solid solutions
**              (2) Allowed precipitation of pure muscovite
**              (3) Allowed precipitation of pure Nepheline
**              (4) Removed entry for apatite
**              Mark S. Ghiorso  April 8, 1992
**              (1) Added melilite solid solution
**              Mark S. Ghiorso  April 16, 1992
**              (1) Added cummingtonite solid solution routines and
**                  endmember thermodynamic data
**      V1.1-8  Mark S. Ghiorso  May 13, 1992
**              (1) Added initial estimates for the thermodynamic properties
**                  of Ca(Ti,Mg)(Al,Si)2O6 and Ca(Ti,Mg)(Fe,Si)2O6
**                  pyroxene endmembers
**      V1.1-9  Mark S. Ghiorso  May 26, 1992 
**              (1) Corrected non-quadrilateral pyroxene components for 
**                  consistency with CaTs (Berman)
**      V2.0-1  Mark S. Ghiorso  July 11, 1992
**              (1) Added solid solution function declarations
**              (2) Added (*display) entries for solid structures
**              (3) Changed pyroxene formula names to Buffoonite
**      V2.0-2  Mark S. Ghiorso  August 1 and 2, 1992
**              (1) Added I1 -> C1 phase transition to anorthite
**              (2) Modified whitlockite heat capacity expressions
**      V2.0-3  Mark S. Ghiorso  January 22, 1992
**              (1) Updated properties of Diopside, Clinoenstatite, and
**                  Hedenbergite
**      V2.0-4  Mark S. Ghiorso  February 18, 1993
**              (1) Removed binary opx and updated solid properties
**      V2.0-5  Mark S. Ghiorso  March 6, 1993
**              (1) Updated thermodynamic properties of non-quad pyroxenes
**      V2.0-6  Mark S. Ghiorso  April 7, 1993
**              (1) Added thermodynamic properties of aenigmatite
**      V2.0-7  Mark S. Ghiorso  May 18, 1993
**              (1) Revoked 2.0-4
**      V2.0-8  Mark S. Ghiorso  June 22, 1993
**              (1) Added leucite ss
**              (2) Added nepheline ss
**      V2.0-9  Mark S. Ghiorso  June 28, 1993
**              (1) New quadrilateral solution
**      V2.0-10 Mark S. Ghiorso  July 19, 1993
**              (1) Updated ss properties with the final quadrilateral solution
**      V3.0-1  Mark S. Ghiorso  August 13, 1993
**              (1) Final version of Cpx and Opx solution parameters
**              (2) Disabled Leucite ss and Nepheline ss
**      V3.0-2  Mark S. Ghiorso  September 24, 1994
**              (1) Corrected erroneous function declarations for cpmix and
**                  vmix
**      V3.0-3  Mark S. Ghiorso  February 28, 1995
**              (1) Updated endmember properties of cummingtonite and
**                  grunerite
**      V3.0-4  Mark S. Ghiorso  June 19, 1995
**              (1) Fixed names of buffonites
**    V4.0-1  Paul D. Asimow  May 6, 1995
**            (1) Include Hirschmann's 6-component olivine model
**    V4.1-1  Paul D. Asimow  July 31, 1995
**            (1) Change function prototypes for new (*convert)
**            and (*gmix) options
**--
*/

/* 
 *==============================================================================
 */

int  testAlL (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conAlL  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actAlL  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixAlL (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixAlL (int mask, double t, double P, double *x, double *hmix);
void smixAlL (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixAlL(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixAlL (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispAlL (int mask, double t, double P, double *x, char **formula);

int  testAlS (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conAlS  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actAlS  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixAlS (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixAlS (int mask, double t, double P, double *x, double *hmix);
void smixAlS (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixAlS(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixAlS (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispAlS (int mask, double t, double P, double *x, char **formula);

int  testAph (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conAph  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actAph  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixAph (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixAph (int mask, double t, double P, double *x, double *hmix);
void smixAph (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixAph(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixAph (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispAph (int mask, double t, double P, double *x, char **formula);

int  testBio (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conBio  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actBio  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixBio (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixBio (int mask, double t, double P, double *x, double *hmix);
void smixBio (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixBio(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixBio (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispBio (int mask, double t, double P, double *x, char **formula);

int  testCpx (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conCpx  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actCpx  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixCpx (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixCpx (int mask, double t, double P, double *x, double *hmix);
void smixCpx (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixCpx(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixCpx (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispCpx (int mask, double t, double P, double *x, char **formula);

int  testCum (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conCum  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actCum  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixCum (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixCum (int mask, double t, double P, double *x, double *hmix);
void smixCum (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixCum(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixCum (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispCum (int mask, double t, double P, double *x, char **formula);

int  testFld (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conFld  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actFld  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixFld (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixFld (int mask, double t, double P, double *x, double *hmix);
void smixFld (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixFld(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixFld (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispFld (int mask, double t, double P, double *x, char **formula);

int  testGrn (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conGrn  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actGrn  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixGrn (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixGrn (int mask, double t, double P, double *x, double *hmix);
void smixGrn (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixGrn(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixGrn (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispGrn (int mask, double t, double P, double *x, char **formula);

int  testHrn (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conHrn  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actHrn  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixHrn (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixHrn (int mask, double t, double P, double *x, double *hmix);
void smixHrn (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixHrn(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixHrn (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispHrn (int mask, double t, double P, double *x, char **formula);

int  testIlm (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conIlm  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actIlm  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixIlm (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixIlm (int mask, double t, double P, double *x, double *hmix);
void smixIlm (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixIlm(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixIlm (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispIlm (int mask, double t, double P, double *x, char **formula);

int  testLeu (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conLeu  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actLeu  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixLeu (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixLeu (int mask, double t, double P, double *x, double *hmix);
void smixLeu (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixLeu(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixLeu (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispLeu (int mask, double t, double P, double *x, char **formula);

int  testMaj (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conMaj  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actMaj  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixMaj (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixMaj (int mask, double t, double P, double *x, double *hmix);
void smixMaj (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixMaj(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixMaj (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispMaj (int mask, double t, double P, double *x, char **formula);

int  testMel (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conMel  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actMel  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixMel (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixMel (int mask, double t, double P, double *x, double *hmix);
void smixMel (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixMel(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixMel (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispMel (int mask, double t, double P, double *x, char **formula);

int  testNph (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conNph  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actNph  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixNph (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixNph (int mask, double t, double P, double *x, double *hmix);
void smixNph (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixNph(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixNph (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispNph (int mask, double t, double P, double *x, char **formula);

int  testKal (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conKal  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actKal  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixKal (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixKal (int mask, double t, double P, double *x, double *hmix);
void smixKal (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixKal(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixKal (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispKal (int mask, double t, double P, double *x, char **formula);

int  testOlv (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conOlv  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actOlv  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixOlv (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixOlv (int mask, double t, double P, double *x, double *hmix);
void smixOlv (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixOlv(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixOlv (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispOlv (int mask, double t, double P, double *x, char **formula);

int  testOsx (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conOsx  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actOsx  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixOsx (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixOsx (int mask, double t, double P, double *x, double *hmix);
void smixOsx (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixOsx(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixOsx (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispOsx (int mask, double t, double P, double *x, char **formula);

int  testOox (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conOox  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actOox  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixOox (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixOox (int mask, double t, double P, double *x, double *hmix);
void smixOox (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixOox(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixOox (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispOox (int mask, double t, double P, double *x, char **formula);

int  testOpx (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conOpx  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actOpx  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixOpx (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixOpx (int mask, double t, double P, double *x, double *hmix);
void smixOpx (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixOpx(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixOpx (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispOpx (int mask, double t, double P, double *x, char **formula);

int  testPvk (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conPvk  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actPvk  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixPvk (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixPvk (int mask, double t, double P, double *x, double *hmix);
void smixPvk (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixPvk(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixPvk (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispPvk (int mask, double t, double P, double *x, char **formula);

int  testRhm (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conRhm  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actRhm  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixRhm (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixRhm (int mask, double t, double P, double *x, double *hmix);
void smixRhm (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixRhm(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixRhm (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispRhm (int mask, double t, double P, double *x, char **formula);

int  testMsg (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conMsg  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actMsg  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixMsg (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixMsg (int mask, double t, double P, double *x, double *hmix);
void smixMsg (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixMsg(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixMsg (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispMsg (int mask, double t, double P, double *x, char **formula);

int  testRgw (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conRgw  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actRgw  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixRgw (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixRgw (int mask, double t, double P, double *x, double *hmix);
void smixRgw (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixRgw(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixRgw (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispRgw (int mask, double t, double P, double *x, char **formula);

int  testSpn (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conSpn  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actSpn  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixSpn (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixSpn (int mask, double t, double P, double *x, double *hmix);
void smixSpn (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixSpn(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixSpn (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispSpn (int mask, double t, double P, double *x, char **formula);

int  testWds (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conWds  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actWds  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixWds (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixWds (int mask, double t, double P, double *x, double *hmix);
void smixWds (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixWds(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixWds (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispWds (int mask, double t, double P, double *x, char **formula);

int  testWus (int mask, double t, double p, int na, int nr, char **names,
              char **formulas, double *r, double *m);
void conWus  (int inpMask, int outMask, double t, double p, double *e,
              double *m, double *r, double *x, double **dm, double ***d2m,
              double **dr, double ****d3m);
void actWus  (int mask, double t, double p, double *x, double *a,
              double *mu, double **dx);
void gmixWus (int mask, double t, double P, double *x, double *gmix,
              double *dx, double **dx2, double ***dx3);
void hmixWus (int mask, double t, double P, double *x, double *hmix);
void smixWus (int mask, double t, double P, double *x, double *smix,
              double *dx, double **dx2);
void cpmixWus(int mask, double t, double P, double *x, double *cpmix,
              double *dt, double *dx);
void vmixWus (int mask, double t, double P, double *x, double *vmix,
              double *dx, double **dx2, double *dt, double *dp,
              double *dt2, double *dtdp, double *dp2, double *dxdt,
              double *dxdp);
void dispWus (int mask, double t, double P, double *x, char **formula);

#define        INCLUDE_IN_CALIBRATION TRUE
#define DO_NOT_INCLUDE_IN_CALIBRATION FALSE

#define        INCLUDE_IN_STD_SET TRUE
#define DO_NOT_INCLUDE_IN_STD_SET FALSE

Solids xMeltsSolids[] = {
  /***************************************************************************
  
   -----> Pure Phases
   
   ***************************************************************************/
  {"monalbite", PHASE, "NaAlSi3O8", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3921618.0,      /* H ref (J)                   monalbite - Berman (1988) */
   224.412,         /* S ref (J/K)                             Berman (1988) */
   10.083,          /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN, {{393.64, -24.155E2, -78.928E5, 107.064E7, 0.0, 0.0, 0.0, 0.0}},          
   EOS_VINET, {{2.6307e-5, 51.414, 5.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"carnegieite", PHASE, "NaAlSiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2104300.0+15726.0,     /* H ref (J) Robie (1995) + corr carn = nephe at 1250 C */
   118.7,                  /* S ref (J/K)                       Robie (1995) */
   5.603,                  /* V ref (J/bar)                     Robie (1995) */
   CP_BERMAN,  {{232.69, -15.158E2, -57.552E5, 99.999E7, 970.0, 8741.0, -11.472E-2, 34.895E-5}}, 
   EOS_VINET,  {{31.802e-6, 48.7805, 1.4747}} 
   },
   {                                /* ThermoData structure                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"corundum", PHASE, "Al2O3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1675700.0,      /* H ref (J)                               Berman (1988) */
   50.820,          /* S ref (J/K)                             Berman (1988) */
   2.558,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{155.02, -8.284E2, -38.614E5, 40.908E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_VINET,  {{21.342E-6, 259.74, 4.06}} /* refit Berman (1988)            */ 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"cristobalite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907753.0,        /* H ref (J) Berman (1988)                              */
   43.394,           /* S ref (J/K) Berman (1988)                            */
   2.587,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{83.51, -3.747E2, -24.554E5, 28.007E7, 535.0, 0.0, -14.216E-2, 44.142E-5}},
   EOS_VINET,  {{20.824E-6, 39.761, 4.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"enthalpy", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,            /* Dummy formula to fool parser                         */
   {                /* ThermoRef structure                                   */
   -1000.0,         /* H ref (J)                                             */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"entropy", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,             /* Dummy formula to fool parser                         */
   {                /* ThermoRef structure                                   */
   -1000.0,         /* H ref (J)                                             */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"kalsilitehex", PHASE, "KAlSiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0, /* H adjusted to zero delta G of Ks + Orthoclase = 2 Lc at 495  */
   {                /* ThermoRef structure                                   */
   -2124700.0-8407.0,  /* H ref (J)   Robie et al.(1995)                     */
   133.3,              /* S ref (J/K) Kelley et al. (1953)                   */
   5.989,              /* V ref (J/bar) Robie et al.(1995)                   */
   CP_BERMAN,  {{186.0, 0.0, -131.067E5, 213.893E7, 810.0, 1154.0, -7.096454E-2, 21.682E-5}},
   EOS_VINET,  {{31.802e-6, 48.7805, 1.4747}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"kalsiliteortho", PHASE, "KAlSiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0, /* H adjusted to zero delta G of Ks + Orthoclase = 2 Lc at 495  */
   {                /* ThermoRef structure                                   */
   -2124700.0-8407.0,  /* H ref (J)   Robie et al.(1995)                     */
   133.3,              /* S ref (J/K) Kelley et al. (1953)                   */
   5.989,              /* V ref (J/bar) Robie et al.(1995)                   */
   CP_BERMAN,  {{186.0, 0.0, -131.067E5, 213.893E7, 810.0, 1154.0, -7.096454E-2, 21.682E-5}},
   EOS_VINET,  {{31.802e-6, 48.7805, 1.4747}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"kdisilicate", PHASE, "K2Si2O5", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,        /* Cp from Berman and Brown (1985)                       */
   {                /* ThermoRef structure                                   */
   -2571739.1,      /* H ref (J)                             Forsberg (2002) */
   176.82,          /* S ref (J/K)     estimated from Helgeson et al. (1978) */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{240.72, 0.0, -147.934E5, 228.921E7, 0.0, 0.0, 0.0, 0.0}},             
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                                /* ThermoData structure                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"kmetasilicate", PHASE, "K2SiO3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,        /* Cp from Berman and Brown (1985)                       */
   {                /* ThermoRef structure                                   */
   -1609952.1,      /* H ref (J)                             Forsberg (2002) */
   135.9,           /* S ref (J/K)     estimated from Helgeson et al. (1978) */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{225.99, -19.866E2, 0.0, 14.896E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                                /* ThermoData structure                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"ktetrasilicate", PHASE, "K2Si4O9", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,        /* Cp from Berman and Brown (1985) estimation algorithm  */
   {                /* ThermoRef structure                                   */
   -4335281.0,      /* H ref (J)                             Forsberg (2002) */
   259.5,           /* S ref (J/K)     estimated from Helgeson et al. (1978) */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{456.264, -25.8771E2, -101.1424E5, 145.4828E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                                /* ThermoData structure                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"leucite", PHASE, "KAlSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0, /* H corrected to zero deltaG of San + Fo = Lc + En at 967 C    */
   {                /* ThermoRef structure                                   */
   -3037800.0-10076.0,                /* H ref (J)      Robie et al.(1995)   */
   179.3,                             /* S ref (J/K)    Paukov et al. (2002) */
   8.827,                             /* V ref (J/bar)  Robie et al.(1995)   */
   CP_BERMAN,  {{271.14, -9.441E2, -78.572E5, 95.920E7, 955.0, 256.0, -9.731e-2, 33.730e-5}},
   EOS_VINET,  {{12.5167877e-6, 64.2333, 0.0512}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"liquid", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,            /* Dummy formula to fool parser                         */
   {                /* ThermoRef structure                                   */
   -1000.0,         /* H ref (J)                                             */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"mullite", PHASE, "Al6Si2O13", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1629830.0*4.184,/* H ref (J)                                      Janaff */
   65.7*4.184,      /* S ref (J/K)                                    Janaff */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{634.81, -33.735e2, -172.099e5, 212.274e7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"muscovite", PHASE, "KAl2Si3AlO10(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -5976740.0,      /* H ref (J)                               Berman (1988) */
   293.157,         /* S ref (J/K)                             Berman (1988) */
   14.087,          /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{651.49, -38.732e2, -185.232e5, 274.247e7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_VINET,  {{3.54e-5, 61.4, 6.9}} /* Knittle (1995)                      */ 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"nadisilicate", PHASE, "Na2Si2O5", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -590360.0*4.184, /* H ref (J)                    Stull and Prophet (1971) */
   39.21*4.184,     /* S ref (J/K)                  Stull and Prophet (1971) */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{250.69, 0.0, -156.510E5, 221.700E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                                /* ThermoData structure                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"nametasilicate", PHASE, "Na2SiO3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -373190.0*4.184, /* H ref (J)                    Stull and Prophet (1971) */
   27.21*4.184,     /* S ref (J/K)                  Stull and Prophet (1971) */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{234.77, -22.189E2, 0.0, 13.530E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                                /* ThermoData structure                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"naorthosilicate", PHASE, "Na4SiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2200000.0,      /* H ref (J)                                       Guess */
   46.8*4.184,      /* S ref (J/K)                                    Kelley */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{43.79*4.184, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}}, /* Kelley */           
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                                /* ThermoData structure                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"naalo2", PHASE, "NaAlO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1120869.33,     /* H ref (J)                                             */
   63.5687,         /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{125.269, -4.26145e2, -48.97675e5, 73.6866e7, 0.0, 0.0, 0.0, 0.0}},             
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                                /* ThermoData structure                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"naal9o14", PHASE, "NaAl9O14", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -7869802.76,     /* H ref (J)                                             */
   271.67,          /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{746.829, -38.35305e2, -236.629e5, 329.720e7, 0.0, 0.0, 0.0, 0.0}},          
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                                /* ThermoData structure                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"nepheline", PHASE, "NaAlSiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2093004.0,      /* H ref (J)  Waterwiese et al. (1995)	             */
   124.641,         /* S ref (J/K)				             */
   5.4131,          /* V ref (J/bar)				             */
   CP_BERMAN,  {{205.24, -7.599E2, -108.383E5, 208.182E7, 467.0, 241.0, -50.249E-2, 165.95E-5}}, 
   EOS_VINET,  {{31.802e-6, 48.7805, 1.4747}} 
   },
   {                                /* ThermoData structure                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"pseudowollastonite", PHASE, "CaSiO3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1627427.0,              /* H ref (J) (Pseudowallostonite)  Berman (1988) */
   85.279,                  /* S ref (J/K)                     Berman (1988) */
   4.016,                   /* V ref (J/bar)                   Berman (1988) */
   CP_BERMAN,  {{141.16, -4.172e2, -58.576e5, 94.074e7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_VINET,  {{2.8180e-5, 80.321, 3.017}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"quartz", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -910700.0,        /* H ref (J) Berman (1988)                              */
   41.460,           /* S ref (J/K) Berman (1988)                            */
   2.269,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN, {{80.01, -2.403E2, -35.467E5, 49.157E7, 848.0, 0.0, -9.187E-2, 24.607E-5}},
   EOS_VINET, {{0.0, 37.1, 6.2}} /* Knittle (1995)                           */
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"highsanidine", PHASE, "KAlSi3O8", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3959704.0,       /* H ref (J)                              Berman (1988) */
   229.157,          /* S ref (J/K)                            Berman (1988) */
   10.896,           /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN, {{381.37, -19.410E2, -120.373E5, 183.643E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_VINET, {{1.5145e-5, 55.402, 5.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"tridymite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907750.0,        /* H ref (J) Berman (1988)                              */
   43.770,           /* S ref (J/K) Berman (1988)                            */
   2.675,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{75.37, 0.0, -59.581E5, 95.825E7, 383.0, 130.0, 42.670E-2, -144.575E-5}},                  
   EOS_VINET,  {{19.339E-6, 39.872, 4.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"water", PHASE, "H2O", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* Calculated in GIBBS.C Berman (1988) */
   {                /* ThermoRef structure                                   */
   -54955.2356,     /* H ref (J) non-zero to allow phase inclusion in preclb */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},                               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"wollastonite", PHASE, "CaSiO3", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1631500.0,              /* H ref (J) (Pseudowallostonite)  Berman (1988) */
   81.810,                  /* S ref (J/K)                     Berman (1988) */
   3.983,                   /* V ref (J/bar)                   Berman (1988) */
   CP_BERMAN,  {{149.07, -6.903e2, -36.593e5, 48.435e7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_VINET,  {{2.8180e-5, 80.321, 3.017}} /* refit of Berman (1988)        */
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  /***************************************************************************
  
   -----> Saxena High Pressure database - pure solids
   
   ***************************************************************************/
  {"coesite-sx", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -907604.0,        /* H ref (J)                              Berman (1988) */
   39.424,           /* S ref (J/K)                            Berman (1988) */
   2.064,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{ 94.907, -7.673e2, -5.279e5, 2.627e7, 0.0, 0.0, 0.0, 0.0}},                          
   EOS_VINET,  {{0.69e-5, 96.0, 8.4}} /* alpha Fei (1995), Knittle (1995)    */
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"stishovite-sx", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -864000.0,        /* H ref (J)                       Saxena et al. (1993) */
   29.500,           /* S ref (J/K)                     Saxena et al. (1993) */
   1.4010,           /* V ref (J/bar)                   Saxena et al. (1993) */
   CP_BERMAN,  {{85.4245, -3.7388e2, -38.3420e5, 65.5985e7, 0.0, 0.0, 0.0, 0.0}}, /* refit from Robie */                             
   EOS_VINET,  {{1.64e-5, 306.0, 2.8}} /* alpha Fei (1995), Knittle (1995)   */
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  /***************************************************************************
  
   -----> SOLID SOLUTIONS
   
   ***************************************************************************/
  {"feldspar", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testFld,         /* Pointer to testFld  : test expected number and order  */
   conFld,          /* Pointer to conFld   : moles to indep comp variables   */
   actFld,          /* Pointer to actFld   : activities, chemical potentials */
   gmixFld,         /* Pointer to gmixFld  : Gibbs free energy of mixing     */
   hmixFld,         /* Pointer to hmixFld  : Enthaly of mixing               */
   smixFld,         /* Pointer to smixFld  : Entropy of mixing               */
   cpmixFld,        /* Pointer to cpmixFld : Heat capacity of mixing         */
   vmixFld,         /* Pointer to vmixFld  : Volume of mixing                */
   dispFld          /* Pointer to dispFld  : Formula for interface display   */
  },
  {"albite", COMPONENT, "NaAlSi3O8", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                                      /* Salje correction in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3921618.0,      /* H ref (J)                   monalbite - Berman (1988) */
   224.412,         /* S ref (J/K)                             Berman (1988) */
   10.083,          /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN, {{393.64, -24.155E2, -78.928E5, 107.064E7, 0.0, 0.0, 0.0, 0.0}},          
   EOS_VINET, {{2.6307e-5, 51.414, 5.0}} 
   }
  },
  {"anorthite", COMPONENT, "CaAl2Si2O8", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -4228730.0,     /* H ref (J)   Berman (1988)  Carpenter I1->C1 +3.7*4184.0*/
   200.186, /* S ref (J/K) Berman (1988)  Carpenter I1->C1 +3.7*4184.0/2200.0*/
   10.075,           /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN, {{439.37, -37.341E2, 0.0, -31.702E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_VINET, {{1.4102e-5, 78.570, 5.27718644}} 
   }
  },
  {"sanidine", COMPONENT, "KAlSi3O8", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                             /* K-feldspar, ordering done in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3970791.0,       /* H ref (J)                              Berman (1988) */
   214.145,          /* S ref (J/K)                            Berman (1988) */
   10.869,           /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN, {{381.37, -19.410E2, -120.373E5, 183.643E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_VINET, {{1.5145e-5, 55.402, 5.0}} 
   }
  },
  {"kalsilite ss", PHASE, "", DO_NOT_INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testKal,         /* Pointer to testKal  : test expected number and order  */
   conKal,          /* Pointer to conKal   : moles to indep comp variables   */
   actKal,          /* Pointer to actKal   : activities, chemical potentials */
   gmixKal,         /* Pointer to gmixKal  : Gibbs free energy of mixing     */
   hmixKal,         /* Pointer to hmixKal  : Enthaly of mixing               */
   smixKal,         /* Pointer to smixKal  : Entropy of mixing               */
   cpmixKal,        /* Pointer to cpmixKal : Heat capacity of mixing         */
   vmixKal,         /* Pointer to vmixKal  : Volume of mixing                */
   dispKal          /* Pointer to dispKal  : Formula for interface display   */
  },
  {"na-nepheline", COMPONENT, "Na4Al4Si4O16", DO_NOT_INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2093004.0*4.0,         /* H ref (J)  Waterwiese et al. (1995)            */
   124.641*4.0,            /* S ref (J/K)                                    */
   5.4131*4.0,             /* V ref (J/bar)                                  */
   CP_BERMAN,  {{205.24*4.0, -7.599E2*4.0, -108.383E5*4.0, 208.182E7*4.0, 467.0, 241.0*4.0, -50.249E-2*2.0, 165.95E-5*2.0}}, 
   EOS_VINET,  {{31.802e-6, 48.7805, 1.4747}} 
   }
  },
#define DH2     -1.35      * 1000.0 * 4.184 /* K4Al4Si4O16 kals-neph  joules */ 
#define DS2      0.0       * 1000.0 * 4.184 /* joules/T */
#define DV2     -0.00001   * 1000.0 * 4.184 /* joules/bar */
  {"k-nepheline", COMPONENT, "K4Al4Si4O16", DO_NOT_INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2109563.55*4.0-(DH2),       /* H ref (J)     Berman (pers com) Kalsilite */
   133.9653*4.0-(DS2),          /* S ref (J/K)   Berman (pers com) Kalsilite */
   6.043478*4.0-(DV2),          /* V ref (J/bar)                   Kalsilite */
   CP_BERMAN,  {{186.0*4.0, 0.0, -131.067E5*4.0, 213.893E7*4.0, 800.15, 1154.0*4.0,-7.096454E-2*2.0, 21.682E-5*2.0}},
   EOS_VINET,  {{31.802e-6, 48.7805, 1.4747}} 
   }
  },
#undef DH2
#undef DS2
#undef DV2
  {"vc-nepheline", COMPONENT, "Na3Al3Si5O16", DO_NOT_INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,       /* monalbite */
   0.0, 0.0,                                      /* Salje correction in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3921618.0,      /* H ref (J)                   monalbite - Berman (1988) */
   224.412,         /* S ref (J/K)                             Berman (1988) */
   0.0,             /* V ref (J/bar) - Volume correction accounted in Gibbs  */
   CP_BERMAN,  {{393.64, -24.155E2, -78.928E5, 107.064E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_VINET,  {{31.802e-6, 48.7805, 1.4747}} 
   }
  },
  {"ca-nepheline", COMPONENT, "CaNa2Al4Si4O16", DO_NOT_INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,  /* C1-anorthite */
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -4228730.0,     /* H ref (J)   Berman (1988)  Carpenter I1->C1 +3.7*4184.0*/
   200.186, /* S ref (J/K) Berman (1988)  Carpenter I1->C1 +3.7*4184.0/2200.0*/
   0.0,              /* V ref (J/bar) - Volume correction accounted in Gibbs */
   CP_BERMAN,  {{439.37, -37.341E2, 0.0, -31.702E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_VINET,  {{31.802e-6, 48.7805, 1.4747}} 
   }
  },
  {"leucite ss", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testLeu,         /* Pointer to testLeu  : test expected number and order  */
   conLeu,          /* Pointer to conLeu   : moles to indep comp variables   */
   actLeu,          /* Pointer to actLeu   : activities, chemical potentials */
   gmixLeu,         /* Pointer to gmixLeu  : Gibbs free energy of mixing     */
   hmixLeu,         /* Pointer to hmixLeu  : Enthaly of mixing               */
   smixLeu,         /* Pointer to smixLeu  : Entropy of mixing               */
   cpmixLeu,        /* Pointer to cpmixLeu : Heat capacity of mixing         */
   vmixLeu,         /* Pointer to vmixLeu  : Volume of mixing                */
   dispLeu          /* Pointer to dispLeu  : Formula for interface display   */
  },
  {"leucite", COMPONENT, "KAlSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3032146.03+27000.0,                       /* H ref (J)   adjusted 21866.4*/
   184.096+21.75,                        /* S ref (J/K)  Kelley et al. 1953  */
   8.8390,                             /* V ref (J/bar)  Robie et al. (1978) */
   CP_BERMAN,  {{271.14, -9.441E2, -78.572E5, 95.920E7, 955.0, 256.0, -9.731e-2, 33.730e-5}},
   EOS_VINET,  {{12.5167877e-6, 64.2333, 0.0512}} 
   }
  },
  {"analcime", COMPONENT, "NaAlSi2O5(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                             /*               properties of analcime */
   {                /* ThermoRef structure                                   */
   -3308500.0-17400,                 /* Johnson et al.             H ref (J) */
   228.10,                           /* Johnson et al.           S ref (J/K) */
   9.71,                             /*        Helgeson (1978) V ref (J/bar) */
   CP_BERMAN,  {{571.83, -71.887E2, 0.0, 149.306E7, 0.0, 0.0, 0.0, 0.0}},
   EOS_VINET,  {{12.5167877e-6, 64.2333, 0.0512}} 
   }
  },
  {"na-leucite", COMPONENT, "NaAlSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                             /*    properties of dehydrated analcime */
   {                /* ThermoRef structure                                   */
   -2980100.0-21875.55,              /*   Johnson et al.           H ref (J) */
   173.68-7.94,                      /*   King and Weller (1961) S ref (J/K) */
   8.91,                             /*        Helgeson (1978) V ref (J/bar) */
   CP_BERMAN,  {{401.27, -42.480E2, 0.0, 21.630E7, 0.0, 0.0, 0.0, 0.0}},
   EOS_VINET,  {{12.5167877e-6, 64.2333, 0.0512}} 
   }
  },
  {"nepheline ss", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testNph,         /* Pointer to testNph  : test expected number and order  */
   conNph,          /* Pointer to conNph   : moles to indep comp variables   */
   actNph,          /* Pointer to actNph   : activities, chemical potentials */
   gmixNph,         /* Pointer to gmixNph  : Gibbs free energy of mixing     */
   hmixNph,         /* Pointer to hmixNph  : Enthaly of mixing               */
   smixNph,         /* Pointer to smixNph  : Entropy of mixing               */
   cpmixNph,        /* Pointer to cpmixNph : Heat capacity of mixing         */
   vmixNph,         /* Pointer to vmixNph  : Volume of mixing                */
   dispNph          /* Pointer to dispNph  : Formula for interface display   */
  },
  {"na-nepheline", COMPONENT, "Na4Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2093004.0*4.0,         /* H ref (J)  Waterwiese et al. (1995)            */
   124.641*4.0,            /* S ref (J/K)                                    */
   5.4131*4.0,             /* V ref (J/bar)                                  */
   CP_BERMAN,  {{205.24*4.0, -7.599E2*4.0, -108.383E5*4.0, 208.182E7*4.0, 467.0, 241.0*4.0, -50.249E-2*2.0, 165.95E-5*2.0}},
   EOS_VINET,  {{31.802e-6, 48.7805, 1.4747}} 
   }
  },
#define DH2     -1.35      * 1000.0 * 4.184 /* K4Al4Si4O16 kals-neph  joules */ 
#define DS2      0.0       * 1000.0 * 4.184 /* joules/T */
#define DV2     -0.00001   * 1000.0 * 4.184 /* joules/bar */
  {"k-nepheline", COMPONENT, "K4Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2109563.55*4.0-(DH2)-3572.76, /* H ref (J)   Berman (pers com) Kalsilite */
   133.9653*4.0-(DS2),          /* S ref (J/K)   Berman (pers com) Kalsilite */
   6.043478*4.0-(DV2),          /* V ref (J/bar)                   Kalsilite */
   CP_BERMAN,  {{186.0*4.0, 0.0, -131.067E5*4.0, 213.893E7*4.0, 800.15, 1154.0*4.0, -7.096454E-2*2.0, 21.682E-5*2.0}},
   EOS_VINET,  {{31.802e-6, 48.7805, 1.4747}} 
   }
  },
#undef DH2
#undef DS2
#undef DV2
  {"vc-nepheline", COMPONENT, "Na3Al3Si5O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,       /* monalbite */
   0.0, 0.0,                                      /* Salje correction in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3921618.0,      /* H ref (J)                   monalbite - Berman (1988) */
   224.412,         /* S ref (J/K)                             Berman (1988) */
   5.4131*4.0,             /* V ref (J/bar)                                  */
   CP_BERMAN,  {{393.64, -24.155E2, -78.928E5, 107.064E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_VINET,  {{31.802e-6, 48.7805, 1.4747}} 
   }
  },
  {"ca-nepheline", COMPONENT, "CaNa2Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,  /* C1-anorthite */
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -4228730.0,        /* H ref (J) Berman (1988) Carpenter I1->C1 +3.7*4184.0*/
   200.186, /* S ref (J/K) Berman (1988)  Carpenter I1->C1 +3.7*4184.0/2200.0*/
   5.4131*4.0,             /* V ref (J/bar)                                  */
   CP_BERMAN,  {{439.37, -37.341E2, 0.0, -31.702E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_VINET,  {{31.802e-6, 48.7805, 1.4747}} 
   }
  }
};

int    npc     = (sizeof xMeltsSolids / sizeof(struct _solids));
Solids *solids = xMeltsSolids;

Solids meltsSolids[] = {
  {"olivine", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testOlv,         /* Pointer to testOlv  : test expected number and order  */
   conOlv,          /* Pointer to conOlv   : moles to indep comp variables   */
   actOlv,          /* Pointer to actOlv   : activities, chemical potentials */
   gmixOlv,         /* Pointer to gmixOlv  : Gibbs free energy of mixing     */
   hmixOlv,         /* Pointer to hmixOlv  : Enthaly of mixing               */
   smixOlv,         /* Pointer to smixOlv  : Entropy of mixing               */
   cpmixOlv,        /* Pointer to cpmixOlv : Heat capacity of mixing         */
   vmixOlv,         /* Pointer to vmixOlv  : Volume of mixing                */
   dispOlv          /* Pointer to dispOlv  : Formula for interface display   */
  },
  {"tephroite", COMPONENT, "Mn2SiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1732000.0,       /* H ref (J)                              Berman (1988) */
   155.900,          /* S ref (J/K)                            Berman (1988) */
   4.889,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{219.89, -12.710E2, -20.496E5, 17.652E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.784E-6, 0.0, 25.14E-6, 64.7E-10}} 
   }
  },
  {"fayalite", COMPONENT, "Fe2SiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1479360.0,       /* H ref (J)                              Berman (1988) */
   150.930,          /* S ref (J/K)                            Berman (1988) */ 
   4.630,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{248.93, -19.239E2, 0.0, -13.910E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_BERMAN, {{-0.730E-6, 0.0, 26.546E-6, 79.482E-10}} 
   }
  },
  {"co-olivine", COMPONENT, "Co2SiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1414100.0,       /* H ref (J)                              Berman (1988) */
   142.600,          /* S ref (J/K)                            Berman (1988) */
   4.459,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{201.048, -0.369E2, -71.81E5, 90.05E7, 0.0, 0.0, 0.0, 0.0}},             
   EOS_BERMAN, {{-0.64E-6, 0.0E-12, 28.422E-6, 35.355E-10}} 
   }
  },
  {"ni-olivine", COMPONENT, "Ni2SiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1395300.0,       /* H ref (J)                              Berman (1988) */
   128.100,          /* S ref (J/K)                            Berman (1988) */
   4.259,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{214.997, -10.308E2, -49.445E5, 62.370E7, 0.0, 0.0, 0.0, 0.0}},          
   EOS_BERMAN, {{-0.671E-6, 0.0E-12, 28.422E-6, 35.355E-10}} 
   }
  },
  {"monticellite", COMPONENT, "CaMgSiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2250027.0,       /* H ref (J)                              Berman (1988) */
   108.300,          /* S ref (J/K)                            Berman (1988) */
   5.148,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{226.34, -15.427E2, -11.797E5, -2.329E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.904E-6, 2.00E-12, 27.863E-6, 76.339E-10}} 
   }
  },
  {"forsterite", COMPONENT, "Mg2SiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2174420.0,       /* H ref (J)                              Berman (1988) */
   94.010,           /* S ref (J/K)                            Berman (1988) */
   4.366,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{238.64, -20.013E2, 0.0, -11.624E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_BERMAN, {{-0.791E-6, 1.351E-12, 29.464E-6, 88.633E-10}} 
   }
  },
  {"fayalite", PHASE, "Fe2SiO4", DO_NOT_INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1479360.0,       /* H ref (J)                              Berman (1988) */
   150.930,          /* S ref (J/K)                            Berman (1988) */ 
   4.630,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN, {{248.93, -19.239E2, 0.0, -13.910E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_VINET, {{ 2.9447e-5, 127.955797, 5.016956 }}  /* EOS_BERMAN, {{-0.730E-6, 0.0, 26.546E-6, 79.482E-10}} */
   }
  },
  {"sphene", PHASE, "CaTiSiO5", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2596652.0,       /* H ref (J)                              Berman (1988) */
   129.290,          /* S ref (J/K)                            Berman (1988) */
   5.565,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{234.62, -10.403E2, -51.183E5, 59.146E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.590E-6, 0.0, 25.200E-6, 0.0}} 
   }
  },
  {"garnet", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testGrn,         /* Pointer to testGrn  : test expected number and order  */
   conGrn,          /* Pointer to conGrn   : moles to indep comp variables   */
   actGrn,          /* Pointer to actGrn   : activities, chemical potentials */
   gmixGrn,         /* Pointer to gmixGrn  : Gibbs free energy of mixing     */
   hmixGrn,         /* Pointer to hmixGrn  : Enthaly of mixing               */
   smixGrn,         /* Pointer to smixGrn  : Entropy of mixing               */
   cpmixGrn,        /* Pointer to cpmixGrn : Heat capacity of mixing         */
   vmixGrn,         /* Pointer to vmixGrn  : Volume of mixing                */
   dispGrn          /* Pointer to dispGrn  : Formula for interface display   */
  },
  {"almandine", COMPONENT, "Fe3Al2Si3O12", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -5267216.0,      /* H ref (J)                               Berman (1990) */
   340.007,         /* S ref (J/K)                             Berman (1990) */
   11.511,          /* V (J/bar)                               Berman (1988) */
   CP_BERMAN,  {{573.96, -14.831E2, -292.920E5, 502.208E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{-0.558E-6, 0.321E-12, 18.613E-6, 74.539E-10}} 
   }
  },
  {"grossular", COMPONENT, "Ca3Al2Si3O12", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -6632859.0,       /* H ref (J)                              Berman (1988) */
   255.150,          /* S ref (J/K)                            Berman (1988) */
   12.538,           /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{573.43, -20.394E2, -188.872E5, 231.931E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{-0.654E-6, 1.635E-12, 18.994E-6, 79.756E-10}} 
   }
  },
  {"pyrope", COMPONENT, "Mg3Al2Si3O12", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -6286548.0,       /* H ref (J)                              Berman (1988) */
   266.359,          /* S ref (J/K)                            Berman (1988) */
   11.316,           /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{640.72, -45.421E2, -47.019E5, 0.0E7, 0.0, 0.0, 0.0, 0.0}},              
   EOS_BERMAN, {{-0.576E-6, 0.442E-12, 22.519E-6, 37.044E-10}} 
   }
  },
  {"melilite", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testMel,         /* Pointer to testMel  : test expected number and order  */
   conMel,          /* Pointer to conMel   : moles to indep comp variables   */
   actMel,          /* Pointer to actMel   : activities, chemical potentials */
   gmixMel,         /* Pointer to gmixMel  : Gibbs free energy of mixing     */
   hmixMel,         /* Pointer to hmixMel  : Enthaly of mixing               */
   smixMel,         /* Pointer to smixMel  : Entropy of mixing               */
   cpmixMel,        /* Pointer to cpmixMel : Heat capacity of mixing         */
   vmixMel,         /* Pointer to vmixMel  : Volume of mixing                */
   dispMel          /* Pointer to dispMel  : Formula for interface display   */
  },
  {"akermanite", COMPONENT, "Ca2MgSi2O7", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3860441.0+4900.0,/* H ref (J)                              Berman (1988) */
   212.000,         /* S ref (J/K)                             Berman (1988) */
   9.252,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{387.06, -29.388E2, 0.0, -4.079E7, 358.0, 452.0, 0.0, 0.0}},     
   EOS_BERMAN, {{-0.785E-6, 0.0, 25.011E-6, 67.224E-10}} 
   }
  }, 
  {"gehlenite", COMPONENT, "Ca2Al2SiO7", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                                         /* Ordering done in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3988158.0+18900.0,/* H ref (J)                             Berman (1988) */
   198.600,          /* S ref (J/K)                            Berman (1988) */
   9.033,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{373.09, -22.768E2, -47.785E5, 47.791E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.996E-6, 2.488E-12, 24.926E-6, 5.664E-10}} 
   }
  },
  {"iron-akermanite", COMPONENT, "Ca2FeSi2O7", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,     /* akermanite */
   0.0, 0.0,                /* Ca2MgSi2O7 + 1/2 Fe2SiO4 - 1/2 Mg2SiO4 in Gibbs.c */
   {                /* ThermoRef structure                                   */
   -3860441.0+4000.0,/* H ref (J)                              Berman (1988) */
   212.000,         /* S ref (J/K)                             Berman (1988) */
   9.252,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{387.06, -29.388E2, 0.0, -4.079E7, 358.0, 452.0, 0.0, 0.0}},                 
   EOS_BERMAN, {{-0.785E-6, 0.0, 25.011E-6, 67.224E-10}} 
   }
  },  
  {"soda-melilite", COMPONENT, "Na2Si3O7", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,       /* gehlenite */
   0.0, 0.0,                 /* Ca2Al2SiO7 + 2NaAlSi3O8 - 2CaAl2Si2O8 in Gibbs.c */                    
   {                /* ThermoRef structure                                   */
   -3988158.0+6700.0,/* H ref (J)                              Berman (1988) */
   198.600,          /* S ref (J/K) + 2Rln(2)                  Berman (1988) */
   9.033,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{373.09, -22.768E2, -47.785E5, 47.791E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.996E-6, 2.488E-12, 24.926E-6, 5.664E-10}} 
   }
  },
  {"orthopyroxene", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testOpx,         /* Pointer to testOpx  : test expected number and order  */
   conOpx,          /* Pointer to conOpx   : moles to indep comp variables   */
   actOpx,          /* Pointer to actOpx   : activities, chemical potentials */
   gmixOpx,         /* Pointer to gmixOpx  : Gibbs free energy of mixing     */
   hmixOpx,         /* Pointer to hmixOpx  : Enthaly of mixing               */
   smixOpx,         /* Pointer to smixOpx  : Entropy of mixing               */
   cpmixOpx,        /* Pointer to cpmixOpx : Heat capacity of mixing         */
   vmixOpx,         /* Pointer to vmixOpx  : Volume of mixing                */
   dispOpx          /* Pointer to dispOpx  : Formula for interface display   */
  },
  {"diopside", COMPONENT, "CaMgSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3200583.0,      /* H ref (J)                               Berman (1988) */
   142.5,           /* S ref (J/K)                             Berman (1988) */
   6.620,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{305.41, -16.049E2, -71.660E5, 92.184E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.872E-6, 1.707E-12, 27.795E-6, 83.082E-10}} 
   }
  },
  {"clinoenstatite", COMPONENT, "Mg2Si2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                                                       /* C2/c phase */
   {                /* ThermoRef structure                                   */
   -3086083.0,      /* H ref (J)                     2.0*Berman (1988) + DH2 */
   135.164,         /* S ref (J/K)                   2.0*Berman (1988) + DS2 */
   6.3279,          /* V ref (J/bar)                 2.0*Berman (1988) + DV2 */
   CP_BERMAN,  {{333.16, -24.012E2, -45.412E5, 55.830E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.749E-6, 0.447E-12, 24.656E-6, 74.670E-10}} 
   }
  },
  {"hedenbergite", COMPONENT, "CaFeSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2842221.0,       /* H ref (J)                           Sack and Ghiorso */
   174.2,            /* S ref (J/K)                         Sack and Ghiorso */
   6.7894,           /* V ref (J/bar)                       Sack and Ghiorso */
   CP_BERMAN,  {{307.89, -15.973E2, -69.925E5, 93.522E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.9925E-6, 1.4835E-12, 31.371E-6, 83.672E-10}} 
   }
  },
#define H31  -8.56518 * 1000.0  /* Joules     */
#define S31   0.00000           /* Joules/K   */
#define V31   0.00000           /* Joules/bar */
#define H41   7.93205 * 1000.0  /* Joules     */
#define S41  18.756             /* Joules/K   */
#define V41   0.00000           /* Joules/bar */
#define H51  -7.26701 * 1000.0  /* Joules     */
#define S51  18.756             /* Joules/K   */
  {"alumino-buffonite", COMPONENT, "CaTi0.5Mg0.5AlSiO6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3275265.0+(H31),             /* H ref (J)                          Guess */
   143.745+(S31),                /* S ref (J/K)                        Guess */
   6.356+(V31),      /* V ref (J/bar)           Guessed as identical to CaTs */
   CP_BERMAN,  {{297.499, -13.5596e2, -67.0219e5, 75.9082e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-0.870e-6, 2.171e-12, 22.250e-6, 52.863e-10}} 
   }
  },
  {"buffonite", COMPONENT, "CaTi0.5Mg0.5FeSiO6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2836709.0+(H41),             /* H ref (J)                          Guess */
   161.985+(S41),                /* S ref (J/K)                        Guess */ 
   6.7217+(V41),     /* V ref (J/bar)       Guessed as identical to essenite */
   CP_BERMAN,  {{303.909, -14.1767e2, -43.5654e5, 35.2523e7, 0.0, 0.0, 0.0, 0.0}},       
   EOS_BERMAN, {{-0.870e-6, 2.171e-12, 22.250e-6, 52.863e-10}} 
   }
  },
  {"essenite", COMPONENT, "CaFeAlSiO6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2860211.0+(H51),             /* H ref (J)    H CaTs (Berman 1988)-H3+H4  */
   158.991+(S51),                /* S ref (J/K)  S CaTs (Berman 1988)-S3+S4  */
   6.7217,           /* V ref (J/bar)       Cosca and Peacor (AM 72:148-156) */
   CP_BERMAN,  {{317.11, -17.333e2, -51.0965e5, 54.222e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-0.870e-6, 2.171e-12, 22.250e-6, 52.863e-10}} 
   }
  },
#undef H31
#undef S31
#undef V31
#undef H41
#undef S41
#undef V41
#undef H51
#undef S51
  {"jadeite", COMPONENT, "NaAlSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3025118.0,      /* H ref (J)                               Berman (1988) */
   133.574,         /* S ref (J/K)                             Berman (1988) */
   6.034,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{311.29, -20.051e2, -53.503e5, 66.257e7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.860e-6, 2.149e-12, 23.118e-6, 25.785e-10}} 
   }
  },
  {"clinopyroxene", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testCpx,         /* Pointer to testCpx  : test expected number and order  */
   conCpx,          /* Pointer to conCpx   : moles to indep comp variables   */
   actCpx,          /* Pointer to actCpx   : activities, chemical potentials */
   gmixCpx,         /* Pointer to gmixCpx  : Gibbs free energy of mixing     */
   hmixCpx,         /* Pointer to hmixCpx  : Enthaly of mixing               */
   smixCpx,         /* Pointer to smixCpx  : Entropy of mixing               */
   cpmixCpx,        /* Pointer to cpmixCpx : Heat capacity of mixing         */
   vmixCpx,         /* Pointer to vmixCpx  : Volume of mixing                */
   dispCpx          /* Pointer to dispCpx  : Formula for interface display   */
  },
  {"diopside", COMPONENT, "CaMgSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3200583.0,      /* H ref (J)                               Berman (1988) */
   142.5,           /* S ref (J/K)                             Berman (1988) */
   6.620,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{305.41, -16.049E2, -71.660E5, 92.184E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.872E-6, 1.707E-12, 27.795E-6, 83.082E-10}} 
   }
  },
  {"clinoenstatite", COMPONENT, "Mg2Si2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                                                       /* C2/c phase */
   {                /* ThermoRef structure                                   */
   -3086083.0,      /* H ref (J)                     2.0*Berman (1988) + DH2 */
   135.164,         /* S ref (J/K)                   2.0*Berman (1988) + DS2 */
   6.3279,          /* V ref (J/bar)                 2.0*Berman (1988) + DV2 */
   CP_BERMAN,  {{333.16, -24.012E2, -45.412E5, 55.830E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.749E-6, 0.447E-12, 24.656E-6, 74.670E-10}} 
   }
  },
  {"hedenbergite", COMPONENT, "CaFeSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2842221.0,       /* H ref (J)                           Sack and Ghiorso */
   174.2,            /* S ref (J/K)                         Sack and Ghiorso */
   6.7894,           /* V ref (J/bar)                       Sack and Ghiorso */
   CP_BERMAN,  {{307.89, -15.973E2, -69.925E5, 93.522E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.9925E-6, 1.4835E-12, 31.371E-6, 83.672E-10}} 
   }
  },
#define H31  -8.56518 * 1000.0  /* Joules     */
#define S31   0.00000           /* Joules/K   */
#define V31   0.00000           /* Joules/bar */
#define H41   7.93205 * 1000.0  /* Joules     */
#define S41  18.756             /* Joules/K   */
#define V41   0.00000           /* Joules/bar */
#define H51  -7.26701 * 1000.0  /* Joules     */
#define S51  18.756             /* Joules/K   */
  {"alumino-buffonite", COMPONENT, "CaTi0.5Mg0.5AlSiO6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3275265.0+(H31),             /* H ref (J)                          Guess */
   143.745+(S31),                /* S ref (J/K)                        Guess */
   6.356+(V31),      /* V ref (J/bar)           Guessed as identical to CaTs */
   CP_BERMAN,  {{297.499, -13.5596e2, -67.0219e5, 75.9082e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-0.870e-6, 2.171e-12, 22.250e-6, 52.863e-10}} 
   }
  },
  {"buffonite", COMPONENT, "CaTi0.5Mg0.5FeSiO6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2836709.0+(H41),             /* H ref (J)                          Guess */
   161.985+(S41),                /* S ref (J/K)                        Guess */ 
   6.7217+(V41),     /* V ref (J/bar)       Guessed as identical to essenite */
   CP_BERMAN,  {{303.909, -14.1767e2, -43.5654e5, 35.2523e7, 0.0, 0.0, 0.0, 0.0}},       
   EOS_BERMAN, {{-0.870e-6, 2.171e-12, 22.250e-6, 52.863e-10}} 
   }
  },
  {"essenite", COMPONENT, "CaFeAlSiO6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2860211.0+(H51),             /* H ref (J)    H CaTs (Berman 1988)-H3+H4  */
   158.991+(S51),                /* S ref (J/K)  S CaTs (Berman 1988)-S3+S4  */
   6.7217,           /* V ref (J/bar)       Cosca and Peacor (AM 72:148-156) */
   CP_BERMAN,  {{317.11, -17.333e2, -51.0965e5, 54.222e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-0.870e-6, 2.171e-12, 22.250e-6, 52.863e-10}} 
   }
  },
#undef H31
#undef S31
#undef V31
#undef H41
#undef S41
#undef V41
#undef H51
#undef S51
  {"jadeite", COMPONENT, "NaAlSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3025118.0,      /* H ref (J)                               Berman (1988) */
   133.574,         /* S ref (J/K)                             Berman (1988) */
   6.034,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{311.29, -20.051e2, -53.503e5, 66.257e7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.860e-6, 2.149e-12, 23.118e-6, 25.785e-10}} 
   }
  },
  {"aegirine", PHASE, "NaFeSi2O6", DO_NOT_INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2576800.0,      /* H ref (J)		       Sack & Ghiorso (1994) */
   170.57,          /* S ref (J/K)		       Sack & Ghiorso (1994) */
   63.997,         /* V ref (J/bar)		       Sack & Ghiorso (1994) */
   CP_BERMAN, {{311.29+303.909-297.499, -20.051e2+(-14.1767e2)-(-13.5596e2), -53.503e5+(-43.5654e5)-(-67.0219e5), 66.257e7+(35.2523e7)-(75.9082e7), 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}                /* v1, v2, v3, v4 terms */
   }
  },
  {"aenigmatite", PHASE, "Na2Fe5TiSi6O20", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -8472805.0,       /* H ref (J)                                      Guess */
   740.23,           /* S ref (J/K)                  Sum-of-oxides+magnetics */
   22.8546,          /* V ref (J/bar)               Specific gravity of 3.77 */
   CP_BERMAN,  {{1092.073, -61.5981e2, -225.2679e5, 326.8659e7, 0.0, 0.0, 0.0, 0.0}},    
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"cummingtonite", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testCum,         /* Pointer to testCum  : test expected number and order  */
   conCum,          /* Pointer to conCum   : moles to indep comp variables   */
   actCum,          /* Pointer to actCum   : activities, chemical potentials */
   gmixCum,         /* Pointer to gmixCum  : Gibbs free energy of mixing     */
   hmixCum,         /* Pointer to hmixCum  : Enthaly of mixing               */
   smixCum,         /* Pointer to smixCum  : Entropy of mixing               */
   cpmixCum,        /* Pointer to cpmixCum : Heat capacity of mixing         */
   vmixCum,         /* Pointer to vmixCum  : Volume of mixing                */
   dispCum          /* Pointer to dispCum  : Formula for interface display   */
  },
  {"cummingtonite", COMPONENT, "Mg7Si8O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -12067517.0,     /* H ref (J)                Ghiorso et al. (1995)        */
   540.2587,        /* S ref (J/K)              Ghiorso et al. (1995)        */
   26.33,           /* V ref (J/bar)            Ghiorso et al. (1995)        */
   CP_BERMAN,  {{1233.79200, -71.33980e2, -221.63800e5, 233.393749e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.1393847e-6, 0.0, 28.1048234e-6, 62.894e-10}} 
   }
  },
  {"grunerite", COMPONENT, "Fe7Si8O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -9623300.0,      /* H ref (J)                Ghiorso et al. (1995)        */
   725.0,           /* S ref (J/K)              Ghiorso et al. (1995)        */
   27.840,          /* V ref (J/bar)            Ghiorso et al. (1995)        */
   CP_BERMAN,  {{1347.83, -93.5691e2, -202.2848e5, 303.919e7, 0.0, 0.0, 0.0, 0.0}},      
   EOS_BERMAN, {{-1.670299e-6, 8.68919e-12, 28.400e-6, 0.0}} 
   }
  },
  {"amphibole", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testAph,         /* Pointer to testAph  : test expected number and order  */
   conAph,          /* Pointer to conAph   : moles to indep comp variables   */
   actAph,          /* Pointer to actAph   : activities, chemical potentials */
   gmixAph,         /* Pointer to gmixAph  : Gibbs free energy of mixing     */
   hmixAph,         /* Pointer to hmixAph  : Enthaly of mixing               */
   smixAph,         /* Pointer to smixAph  : Entropy of mixing               */
   cpmixAph,        /* Pointer to cpmixAph : Heat capacity of mixing         */
   vmixAph,         /* Pointer to vmixAph  : Volume of mixing                */
   dispAph          /* Pointer to dispAph  : Formula for interface display   */
  },
  {"cummingtonite", COMPONENT, "Mg7Si8O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -12067920.38,    /* H ref (J)                Ghiorso et al. (2001)        */
   540.2587,        /* S ref (J/K)              Ghiorso et al. (1995)        */
   26.34,           /* V ref (J/bar)            Ghiorso et al. (2001)        */
   CP_BERMAN,  {{1233.79200, -71.33980e2, -221.63800e5, 233.393749e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.1393847e-6, 0.0, 28.1048234e-6, 62.894e-10}} 
   }
  },
  {"grunerite", COMPONENT, "Fe7Si8O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -9623550.0,      /* H ref (J)                Ghiorso et al. (2001)        */
   725.0,           /* S ref (J/K)              Ghiorso et al. (1995)        */
   27.840,          /* V ref (J/bar)            Ghiorso et al. (1995)        */
   CP_BERMAN,  {{1347.83, -93.5691e2, -202.2848e5, 303.919e7, 0.0, 0.0, 0.0, 0.0}},      
   EOS_BERMAN, {{-1.670299e-6, 8.68919e-12, 28.400e-6, 0.0}} 
   }
  },
  {"tremolite", COMPONENT, "Ca2Mg5Si8O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -12307863.0,     /* H ref (J)                Ghiorso et al. (2001)        */
   549.500,         /* S ref (J/K)              Bernard's Guess              */
   27.312,          /* V ref (J/bar)            Yang and Evans               */
   CP_BERMAN,  {{1229.36, -64.019e2, -320.899e5, 420.881e7, 0.0, 0.0, 0.0, 0.0}},        
   EOS_BERMAN, {{-1.4763e-6, 8.9462e-12, 24.374e-6, 98.338e-10}} 
   }
  },
  {"hornblende", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testHrn,         /* Pointer to testHrn  : test expected number and order  */
   conHrn,          /* Pointer to conHrn   : moles to indep comp variables   */
   actHrn,          /* Pointer to actHrn   : activities, chemical potentials */
   gmixHrn,         /* Pointer to gmixHrn  : Gibbs free energy of mixing     */
   hmixHrn,         /* Pointer to hmixHrn  : Enthaly of mixing               */
   smixHrn,         /* Pointer to smixHrn  : Entropy of mixing               */
   cpmixHrn,        /* Pointer to cpmixHrn : Heat capacity of mixing         */
   vmixHrn,         /* Pointer to vmixHrn  : Volume of mixing                */
   dispHrn          /* Pointer to dispHrn  : Formula for interface display   */
  },
  {"pargasite", COMPONENT, "NaCa2Mg4AlAl2Si6O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3016624.0*4.184,                 /* H ref (J)     Helgeson et al. (1978) */
   160.0*4.184,                      /* S ref (J/K)   Helgeson et al. (1978) */
   27.35,                            /* V ref (J/bar) Helgeson et al. (1978) */
   CP_BERMAN,  {{1267.25, -66.5434e2, -303.787e5, 391.353e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.392e-6, 3.481e-12, 24.374e-6, 98.338e-10}} 
   }
  },
#define DHGrnCum (-9623300.0-(-12067517.0))
  {"ferropargasite", COMPONENT, "NaCa2Fe4AlAl2Si6O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3016624.0*4.184+4.0*DHGrnCum/7.0,/* H ref (J)     Helgeson et al. (1978) */
   185.5*4.184,                      /* S ref (J/K)   Helgeson et al. (1978) */
   27.989,                           /* V ref (J/bar) Helgeson et al. (1978) */
   CP_BERMAN,  {{1342.61, -83.4862e2, -247.604e5, 348.507e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.392e-6, 3.481e-12, 24.374e-6, 98.338e-10}} 
   }
  },
#undef DHGrnCum
#define DHBfABf ((-2836709.0+7932.05)-(-3275265.0-8565.18))
  {"magnesiohastingsite", COMPONENT, "NaCa2Mg4FeAl2Si6O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3016624.0*4.184+DHBfABf,         /* H ref (J)     Helgeson et al. (1978) */
   163.8*4.184,                      /* S ref (J/K)   Helgeson et al. (1978) */
   27.38,                            /* V ref (J/bar) Helgeson et al. (1978) */
   CP_BERMAN,  {{1273.66, -67.1606e2, -280.331e5, 350.697e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.392e-6, 3.481e-12, 24.374e-6, 98.338e-10}} 
   }
  },
#undef DHBfABf
  {"biotite", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testBio,         /* Pointer to testBio  : test expected number and order  */
   conBio,          /* Pointer to conBio   : moles to indep comp variables   */
   actBio,          /* Pointer to actBio   : activities, chemical potentials */
   gmixBio,         /* Pointer to gmixBio  : Gibbs free energy of mixing     */
   hmixBio,         /* Pointer to hmixBio  : Enthaly of mixing               */
   smixBio,         /* Pointer to smixBio  : Entropy of mixing               */
   cpmixBio,        /* Pointer to cpmixBio : Heat capacity of mixing         */
   vmixBio,         /* Pointer to vmixBio  : Volume of mixing                */
   dispBio          /* Pointer to dispBio  : Formula for interface display   */
  },
  {"annite", COMPONENT, "KFe3Si3AlO10(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -5142800.0,      /* H ref (J)                               Berman (1990) */
   420.0,           /* S ref (J/K)                             Berman (1990) */
   15.408,          /* V ref (J/bar)                           Berman (1990) */
   CP_BERMAN,  {{727.208, -47.75040e2, -138.319e5, 211.906e7, 0.0, 0.0, 0.0, 0.0}},      
   EOS_BERMAN, {{-1.6969784e-6, 0.0, 34.4473262e-6, 0.0}} 
   }
  },
  {"phlogopite", COMPONENT, "KMg3Si3AlO10(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -6210391.0,      /* H ref (J)                               Berman (1990) */
   334.346,         /* S ref (J/K)                             Berman (1990) */
   14.977,          /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{610.37988, -20.83781e2, -215.33008e5, 284.1040896e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.6969784e-6, 0.0, 34.4473262e-6, 0.0}} 
   }
  },
  {"muscovite", PHASE, "KAl2Si3AlO10(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -5976740.0,      /* H ref (J)                               Berman (1988) */
   293.157,         /* S ref (J/K)                             Berman (1988) */
   14.087,          /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{651.49, -38.732e2, -185.232e5, 274.247e7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{-1.717e-6, 4.295e-12, 33.527e-6, 0.0}} 
   }
  },
  {"feldspar", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testFld,         /* Pointer to testFld  : test expected number and order  */
   conFld,          /* Pointer to conFld   : moles to indep comp variables   */
   actFld,          /* Pointer to actFld   : activities, chemical potentials */
   gmixFld,         /* Pointer to gmixFld  : Gibbs free energy of mixing     */
   hmixFld,         /* Pointer to hmixFld  : Enthaly of mixing               */
   smixFld,         /* Pointer to smixFld  : Entropy of mixing               */
   cpmixFld,        /* Pointer to cpmixFld : Heat capacity of mixing         */
   vmixFld,         /* Pointer to vmixFld  : Volume of mixing                */
   dispFld          /* Pointer to dispFld  : Formula for interface display   */
  },
  {"albite", COMPONENT, "NaAlSi3O8", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                                      /* Salje correction in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3921618.0,      /* H ref (J)                   monalbite - Berman (1988) */
   224.412,         /* S ref (J/K)                             Berman (1988) */
   10.083,          /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{393.64, -24.155E2, -78.928E5, 107.064E7, 0.0, 0.0, 0.0, 0.0}},          
   EOS_BERMAN, {{-1.945E-6, 4.861E-12, 26.307E-6, 32.407E-10}} 
   }
  },
  {"anorthite", COMPONENT, "CaAl2Si2O8", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -4228730.0+3.7*4184.0,     /* H ref (J)   Berman (1988)  Carpenter I1->C1 */
   200.186+3.7*4184.0/2200.0, /* S ref (J/K) Berman (1988)  Carpenter I1->C1 */
   10.075,           /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{439.37, -37.341E2, 0.0, -31.702E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_BERMAN, {{-1.272E-6, 3.176E-12, 10.918E-6, 41.985E-10}} 
   }
  },
  {"sanidine", COMPONENT, "KAlSi3O8", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                             /* K-feldspar, ordering done in GIBBS.C */
   {                /* ThermoRef structure                                   */
#ifdef FOWLER
   -3970791.0+2500.0,/* H ref (J)                              Berman (1988) */
#else
   -3970791.0,       /* H ref (J)                              Berman (1988) */
#endif
   214.145,          /* S ref (J/K)                            Berman (1988) */
   10.869,           /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{381.37, -19.410E2, -120.373E5, 183.643E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{-1.805E-6, 5.112E-12, 15.145E-6, 54.850E-10}} 
   }
  },
  {"quartz", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -910700.0,        /* H ref (J) Berman (1988)                              */
   41.460,           /* S ref (J/K) Berman (1988)                            */
   2.269,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{80.01, -2.403E2, -35.467E5, 49.157E7, 848.0, 0.0, -9.187E-2, 24.607E-5}},
   EOS_BERMAN, {{-2.434E-6, 10.137E-12, 23.895E-6, 0.0}}
   }
  },
  {"tridymite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907750.0,        /* H ref (J) Berman (1988)                              */
   43.770,           /* S ref (J/K) Berman (1988)                            */
   2.675,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{75.37, 0.0, -59.581E5, 95.825E7, 383.0, 130.0, 42.670E-2, -144.575E-5}},
   EOS_BERMAN, {{-2.508E-6, 0.0, 19.339E-6, 0.0}}
   }
  },
  {"cristobalite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907753.0,        /* H ref (J) Berman (1988)                              */
   43.394,           /* S ref (J/K) Berman (1988)                            */
   2.587,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{83.51, -3.747E2, -24.554E5, 28.007E7, 535.0, 0.0, -14.216E-2, 44.142E-5}},
   EOS_BERMAN, {{-2.515E-6, 0.0, 20.824E-6, 0.0}}
   }
  },
  {"nepheline", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testNph,         /* Pointer to testNph  : test expected number and order  */
   conNph,          /* Pointer to conNph   : moles to indep comp variables   */
   actNph,          /* Pointer to actNph   : activities, chemical potentials */
   gmixNph,         /* Pointer to gmixNph  : Gibbs free energy of mixing     */
   hmixNph,         /* Pointer to hmixNph  : Enthaly of mixing               */
   smixNph,         /* Pointer to smixNph  : Entropy of mixing               */
   cpmixNph,        /* Pointer to cpmixNph : Heat capacity of mixing         */
   vmixNph,         /* Pointer to vmixNph  : Volume of mixing                */
   dispNph          /* Pointer to dispNph  : Formula for interface display   */
  },
  {"na-nepheline", COMPONENT, "Na4Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2093004.0*4.0,         /* H ref (J)  Waterwiese et al. (1995)            */
   124.641*4.0,            /* S ref (J/K)                                    */
   5.4131*4.0,             /* V ref (J/bar)                                  */
   CP_BERMAN,  {{205.24*4.0, -7.599E2*4.0, -108.383E5*4.0, 208.182E7*4.0, 467.0, 241.0*4.0, -50.249E-2*2.0, 165.95E-5*2.0}},
   EOS_BERMAN, {{-2.0500e-6, 5.2000e-12, 31.802e-6, 213.0e-10}} 
   }
  },
#define DH2     -1.35      * 1000.0 * 4.184 /* K4Al4Si4O16 kals-neph  joules */ 
#define DS2      0.0       * 1000.0 * 4.184 /* joules/T */
#define DV2     -0.00001   * 1000.0 * 4.184 /* joules/bar */
  {"k-nepheline", COMPONENT, "K4Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2109563.55*4.0-(DH2)-3572.76, /* H ref (J)   Berman (pers com) Kalsilite */
   133.9653*4.0-(DS2),          /* S ref (J/K)   Berman (pers com) Kalsilite */
   6.043478*4.0-(DV2),          /* V ref (J/bar)                   Kalsilite */
   CP_BERMAN,  {{186.0*4.0, 0.0, -131.067E5*4.0, 213.893E7*4.0, 800.15, 1154.0*4.0, -7.096454E-2*2.0, 21.682E-5*2.0}},
   EOS_BERMAN, {{-2.0500e-6, 5.2000e-12, 31.802e-6, 213.0e-10}} 
   }
  },
  {"vc-nepheline", COMPONENT, "Na3Al3Si5O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,       /* monalbite */
   0.0, 0.0,                                      /* Salje correction in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3921618.0,      /* H ref (J)                   monalbite - Berman (1988) */
   224.412,         /* S ref (J/K)                             Berman (1988) */
   0.0,             /* V ref (J/bar) - Volume correction accounted in Gibbs  */
   CP_BERMAN,  {{393.64, -24.155E2, -78.928E5, 107.064E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"ca-nepheline", COMPONENT, "CaNa2Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,  /* C1-anorthite */
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -4228730.0+3.7*4184.0,        /* H ref (J) Berman (1988) Carpenter I1->C1 */
   200.186+3.7*4184.0/2200.0, /* S ref (J/K) Berman (1988)  Carpenter I1->C1 */
   0.0,              /* V ref (J/bar) - Volume correction accounted in Gibbs */
   CP_BERMAN,  {{439.37, -37.341E2, 0.0, -31.702E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"kalsilite", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testKal,         /* Pointer to testKal  : test expected number and order  */
   conKal,          /* Pointer to conKal   : moles to indep comp variables   */
   actKal,          /* Pointer to actKal   : activities, chemical potentials */
   gmixKal,         /* Pointer to gmixKal  : Gibbs free energy of mixing     */
   hmixKal,         /* Pointer to hmixKal  : Enthaly of mixing               */
   smixKal,         /* Pointer to smixKal  : Entropy of mixing               */
   cpmixKal,        /* Pointer to cpmixKal : Heat capacity of mixing         */
   vmixKal,         /* Pointer to vmixKal  : Volume of mixing                */
   dispKal          /* Pointer to dispKal  : Formula for interface display   */
  },
  {"na-nepheline", COMPONENT, "Na4Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2093004.0*4.0,         /* H ref (J)  Waterwiese et al. (1995)            */
   124.641*4.0,            /* S ref (J/K)                                    */
   5.4131*4.0,             /* V ref (J/bar)                                  */
   CP_BERMAN,  {{205.24*4.0, -7.599E2*4.0, -108.383E5*4.0, 208.182E7*4.0, 467.0, 241.0*4.0, -50.249E-2*2.0, 165.95E-5*2.0}},
   EOS_BERMAN, {{-2.0500e-6, 5.2000e-12, 31.802e-6, 213.0e-10}}
   }
  },
  {"k-nepheline", COMPONENT, "K4Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2109563.55*4.0-(DH2),       /* H ref (J)     Berman (pers com) Kalsilite */
   133.9653*4.0-(DS2),          /* S ref (J/K)   Berman (pers com) Kalsilite */
   6.043478*4.0-(DV2),          /* V ref (J/bar)                   Kalsilite */
   CP_BERMAN,  {{186.0*4.0, 0.0, -131.067E5*4.0, 213.893E7*4.0, 800.15, 1154.0*4.0, -7.096454E-2*2.0, 21.682E-5*2.0}},
   EOS_BERMAN, {{-2.0500e-6, 5.2000e-12, 31.802e-6, 213.0e-10}}
   }
  },
  {"vc-nepheline", COMPONENT, "Na3Al3Si5O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,       /* monalbite */
   0.0, 0.0,                                      /* Salje correction in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3921618.0,      /* H ref (J)                   monalbite - Berman (1988) */
   224.412,         /* S ref (J/K)                             Berman (1988) */
   0.0,             /* V ref (J/bar) - Volume correction accounted in Gibbs  */
   CP_BERMAN,  {{393.64, -24.155E2, -78.928E5, 107.064E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"ca-nepheline", COMPONENT, "CaNa2Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,  /* C1-anorthite */
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -4228730.0+3.7*4184.0,     /* H ref (J)   Berman (1988)  Carpenter I1->C1 */
   200.186+3.7*4184.0/2200.0, /* S ref (J/K) Berman (1988)  Carpenter I1->C1 */
   0.0,              /* V ref (J/bar) - Volume correction accounted in Gibbs */
   CP_BERMAN,  {{439.37, -37.341E2, 0.0, -31.702E7, 0.0, 0.0, 0.0, 0.0}},                 
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"leucite", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testLeu,         /* Pointer to testLeu  : test expected number and order  */
   conLeu,          /* Pointer to conLeu   : moles to indep comp variables   */
   actLeu,          /* Pointer to actLeu   : activities, chemical potentials */
   gmixLeu,         /* Pointer to gmixLeu  : Gibbs free energy of mixing     */
   hmixLeu,         /* Pointer to hmixLeu  : Enthaly of mixing               */
   smixLeu,         /* Pointer to smixLeu  : Entropy of mixing               */
   cpmixLeu,        /* Pointer to cpmixLeu : Heat capacity of mixing         */
   vmixLeu,         /* Pointer to vmixLeu  : Volume of mixing                */
   dispLeu          /* Pointer to dispLeu  : Formula for interface display   */
  },
  {"leucite", COMPONENT, "KAlSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3032146.03+21866.4,                              /* H ref (J)   adjusted */
   184.096+21.75,                        /* S ref (J/K)  Kelley et al. 1953  */
   8.8390,                             /* V ref (J/bar)  Robie et al. (1978) */
   CP_BERMAN,  {{271.14, -9.441E2, -78.572E5, 95.920E7, 955.0, 256.0, -9.731e-2, 33.730e-5}},
   EOS_BERMAN, {{-1.5568254e-6, 1.2739e-12, 12.5167877e-6, 0.0}}
   }
  },
  {"analcime", COMPONENT, "NaAlSi2O5(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                             /*               properties of analcime */
   {                /* ThermoRef structure                                   */
   -3308500.0-17400,                 /* Johnson et al.             H ref (J) */
   228.10,                           /* Johnson et al.           S ref (J/K) */
   9.71,                             /*        Helgeson (1978) V ref (J/bar) */
   CP_BERMAN,  {{571.83, -71.887E2, 0.0, 149.306E7, 0.0, 0.0, 0.0, 0.0}}, 
   EOS_BERMAN, {{-1.5568254e-6, 1.2739e-12, 12.5167877e-6, 0.0}}
   }
  },
  {"na-leucite", COMPONENT, "NaAlSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                             /*    properties of dehydrated analcime */
   {                /* ThermoRef structure                                   */
   -2980100.0-21875.55,              /*   Johnson et al.           H ref (J) */
   173.68-7.94,                      /*   King and Weller (1961) S ref (J/K) */
   8.91,                             /*        Helgeson (1978) V ref (J/bar) */
   CP_BERMAN,  {{401.27, -42.480E2, 0.0, 21.630E7, 0.0, 0.0, 0.0, 0.0}}, 
   EOS_BERMAN, {{-1.5568254e-6, 1.2739e-12, 12.5167877e-6, 0.0}}
   }
  },
#undef DH2
#undef DS2
#undef DV2
  {"corundum", PHASE, "Al2O3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1675700.0,      /* H ref (J)                               Berman (1988) */
   50.820,          /* S ref (J/K)                             Berman (1988) */
   2.558,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{155.02, -8.284E2, -38.614E5, 40.908E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{-0.385E-6, 0.375E-12, 21.342E-6, 47.180E-10}}
   }
  },
  {"rutile", PHASE, "TiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -944750.0,       /* H ref (J)                               Berman (1988) */
   50.460,          /* S ref (J/K)                             Berman (1988) */ 
   1.882,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{77.84, 0.0, -33.678E5, 40.294E7, 0.0, 0.0, 0.0, 0.0}},                  
   EOS_BERMAN, {{-0.454E-6, 0.584E-12, 25.716E-6, 15.409E-10}}
   }
  },
  {"perovskite", PHASE, "CaTiO3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1660630.0,      /* H ref (J)                         Robie et al. (1978) */
   93.64,           /* S ref (J/K)                       Robie et al. (1978) */
   3.3626,          /* V ref (J/bar)                     Robie et al. (1978) */
   CP_BERMAN,  {{150.49, -6.213E2, 0.0, -43.010E7, 1530.0, 550.0*4.184, 0.0, 0.0}},                 
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"spinel", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testSpn,         /* Pointer to testSpn  : test expected number and order  */
   conSpn,          /* Pointer to conSpn   : moles to indep comp variables   */
   actSpn,          /* Pointer to actSpn   : activities, chemical potentials */
   gmixSpn,         /* Pointer to gmixSpn  : Gibbs free energy of mixing     */
   hmixSpn,         /* Pointer to hmixSpn  : Enthaly of mixing               */
   smixSpn,         /* Pointer to smixSpn  : Entropy of mixing               */
   cpmixSpn,        /* Pointer to cpmixSpn : Heat capacity of mixing         */
   vmixSpn,         /* Pointer to vmixSpn  : Volume of mixing                */
   dispSpn          /* Pointer to dispSpn  : Formula for interface display   */
  },
  {"chromite", COMPONENT, "FeCr2O4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1445490.0,      /* H ref (J)                    Sack and Ghiorso (1991b) */
   142.676,         /* S ref (J/K)                  Sack and Ghiorso (1991b) */
   4.4010,          /* V ref (J/bar)                     Robie et al. (1978) */
   CP_BERMAN,  {{236.874, -16.796E2, 0.0, -16.765E7, 0.0, 0.0, 0.0, 0.0}},               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"hercynite", COMPONENT, "FeAl2O4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1947681.0,      /* H ref (J)                    Sack and Ghiorso (1991b) */
   115.362,         /* S ref (J/K)                  Sack and Ghiorso (1991b) */
   0.973948*4.184,  /* V ref (J/bar)                                         */
   CP_BERMAN,  {{235.190, -14.370E2, -46.913E5, 64.564E7, 0.0, 0.0, 0.0, 0.0}},          
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"magnetite", COMPONENT, "Fe3O4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1117403.0,      /* H ref (J)                               Berman (1988) */
   146.114,         /* S ref (J/K)                             Berman (1988) */
   4.452,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{207.93, 0.0, -72.433E5, 66.436E7, 848.0, 1565.0, -19.502E-2, 61.037E-5}},
   EOS_BERMAN, {{-0.582E-6, 1.751E-12, 30.291E-6, 138.470E-10}}
   }
  },
  {"spinel", COMPONENT, "MgAl2O4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2300313.0,      /* H ref (J)                               Berman (1988) */
   84.535,          /* S ref (J/K)                             Berman (1988) */
   3.977,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{235.90, -17.666E2, -17.104E5, 4.062E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{-0.489E-6, 0.0, 21.691E-6, 50.528E-10}}
   }
  },
  {"ulvospinel", COMPONENT, "Fe2TiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1488500.0,      /* H ref (J)                    Sack and Ghiorso (1991b) */
   185.447,         /* S ref (J/K)                  Sack and Ghiorso (1991b) */
   4.682,           /* V ref (J/bar)                     Robie et al. (1978) */
   CP_BERMAN,  {{249.63, -18.174E2, 0.0, -5.453E7, 0.0, 0.0, 0.0, 0.0}},                 
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"rhm-oxide", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testRhm,         /* Pointer to testRhm  : test expected number and order  */
   conRhm,          /* Pointer to conRhm   : moles to indep comp variables   */
   actRhm,          /* Pointer to actRhm   : activities, chemical potentials */
   gmixRhm,         /* Pointer to gmixRhm  : Gibbs free energy of mixing     */
   hmixRhm,         /* Pointer to hmixRhm  : Enthaly of mixing               */
   smixRhm,         /* Pointer to smixRhm  : Entropy of mixing               */
   cpmixRhm,        /* Pointer to cpmixRhm : Heat capacity of mixing         */
   vmixRhm,         /* Pointer to vmixRhm  : Volume of mixing                */
   dispRhm          /* Pointer to dispRhm  : Formula for interface display   */
  },
  {"geikielite", COMPONENT, "MgTiO3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1572560.0,      /* H ref (J)                              Ghiorso (1990) */
   74.56,           /* S ref (J/K)                            Ghiorso (1990) */
   3.086,           /* V ref (J/bar)                     Robie et al. (1978) */
   CP_BERMAN,  {{146.20, -4.160E2, -39.998E5, 40.233E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{-0.5839748e-6, 1.2303e-12, 27.2476341e-6, 29.968e-10}} 
   }
  },
  {"hematite", COMPONENT, "Fe2O3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -822000.0,       /* H ref (J)                              Ghiorso (1990) */
   87.40,           /* S ref (J/K)                            Ghiorso (1990) */
   3.027,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{146.86, 0.0, -55.768E5, 52.563E7, 955.0, 1287.0, -7.403E-2, 27.921E-5}},
   EOS_BERMAN, {{-0.479E-6, 0.304E-12, 38.310E-6, 1.650E-10}} 
   }
  },
  {"ilmenite", COMPONENT, "FeTiO3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1231947.0,      /* H ref (J)                               Berman (1988) */
   108.628,         /* S ref (J/K)                             Berman (1988) */
   3.170,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{150.00, -4.416E2, -33.237E5, 34.815E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{-0.584E-6, 1.230E-12, 27.248E-6, 29.968E-10}} 
   }
  },
  {"pyrophanite", COMPONENT, "MnTiO3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1350707.0,      /* H ref (J)                      Ghiorso (1991 - guess) */
   104.935,         /* S ref (J/K)               Stephenson and Smith (1968) */
   3.170,           /* V ref (J/bar)    (assumed ilmenite >>>) Berman (1988) */
   CP_BERMAN,  {{150.00, -4.416E2, -33.237E5, 34.815E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{-0.584E-6, 1.230E-12, 27.248E-6, 29.968E-10}} 
   }
  },
  {"ortho-oxide", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testOox,         /* Pointer to testOox  : test expected number and order  */
   conOox,          /* Pointer to conOox   : moles to indep comp variables   */
   actOox,          /* Pointer to actOox   : activities, chemical potentials */
   gmixOox,         /* Pointer to gmixOox  : Gibbs free energy of mixing     */
   hmixOox,         /* Pointer to hmixOox  : Enthaly of mixing               */
   smixOox,         /* Pointer to smixOox  : Entropy of mixing               */
   cpmixOox,        /* Pointer to cpmixOox : Heat capacity of mixing         */
   vmixOox,         /* Pointer to vmixOox  : Volume of mixing                */
   dispOox          /* Pointer to dispOox  : Formula for interface display   */
  },
  {"pseudobrookite", COMPONENT, "Fe2TiO5", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                            /* Cp terms from Berman and Brown (1985) */
   {                /* ThermoRef structure                                   */
   -1754429.0,      /* H ref (J)   Analysis of Haggerty & Lindsley Data      */
   156.4816,        /* S ref (J/K) Kelley & King (1961)                      */
   5.491,           /* V ref (J/bar) From page 45 (oxide short course)       */
   CP_BERMAN,  {{261.35, -15.307e2, 0.0, -23.466e7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"ferropseudobrookite", COMPONENT, "FeTi2O5", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2175332.0,      /* H ref (J)   Analysis of Haggerty & Lindsley Data      */
   127.1936-26.94+59.80, /* King & Kelley (1961) for MgTi2O5 - MgO (periclase
                     Robie et al. (1978) + FeO (stoich) (op cit) S ref (J/K) */
   5.578,           /* V ref (J/bar) From page 45 (oxide short course)
                       Armacolite (50:50) - karrooite                        */
   CP_BERMAN,  {{232.58-58.196+77.036, -7.555e2-(-1.6114e2)-5.8471e2, -56.608e5-(-14.0458e5), 
     58.214e7-11.2673e7+0.5558e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"karrooite", COMPONENT, "MgTi2O5", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                            /* Cp terms from Berman and Brown (1985) */
   {                /* ThermoRef structure                                   */
   -2507053.0,      /* H ref (J)   Kelley, Todd & King (1954)                */
   127.1936,        /* S ref (J/K) Kelley & King (1961)                      */
   5.482,           /* V ref (J/bar) From page 45 (oxide short course)       */
   CP_BERMAN,  {{232.58, -7.555e2, -56.608e5, 58.214e7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"whitlockite", PHASE, "Ca3(PO4)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -4097169.0,              /* H ref (J)       Zhu and Sverjensky (in press) */
   235.978,                 /* S ref (J/K)        Southard and Milner (1935) */
   9.7620,                  /* V ref (J/bar)             Robie et al. (1978) */
   CP_BERMAN,  {{402.997, -28.0835E2, 0.0, -32.6230E7, 1373.0, 14059.0, 2.5427E-2, 19.255E-5}},
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"apatite", PHASE, "Ca5(PO4)3OH", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -6694689.0,              /* H ref (J)       Zhu and Sverjensky (in press) */
   398.74,                  /* S ref (J/K)     Zhu and Sverjensky (in press) */
   16.4025,                 /* V ref (J/bar)   Zhu and Sverjensky (in press) */
   CP_BERMAN,  {{758.81, -64.806E2, 0.0, 44.794E7, 0.0, 0.0, 0.0, 0.0}},                 
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"water", PHASE, "H2O", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* Calculated in GIBBS.C Berman (1988) */
   {                /* ThermoRef structure                                   */
   -54955.2356,     /* H ref (J) non-zero to allow phase inclusion in preclb */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},                               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"alloy-solid", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testAlS,         /* Pointer to testAlS  : test expected number and order  */
   conAlS,          /* Pointer to conAlS   : moles to indep comp variables   */
   actAlS,          /* Pointer to actAlS   : activities, chemical potentials */
   gmixAlS,         /* Pointer to gmixAlS  : Gibbs free energy of mixing     */
   hmixAlS,         /* Pointer to hmixAlS  : Enthaly of mixing               */
   smixAlS,         /* Pointer to smixAlS  : Entropy of mixing               */
   cpmixAlS,        /* Pointer to cpmixAlS : Heat capacity of mixing         */
   vmixAlS,         /* Pointer to vmixAlS  : Volume of mixing                */
   dispAlS          /* Pointer to dispAlS  : Formula for interface display   */
  },
  {"Fe-metal", COMPONENT, "Fe", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /*               Calculated in GIBBS.C */
   {                /* ThermoRef structure                                   */
   9999.0,          /* H ref (J) non-zero to allow phase inclusion in preclb */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},                               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"Ni-metal", COMPONENT, "Ni", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /*               Calculated in GIBBS.C */
   {                /* ThermoRef structure                                   */
   9999.0,          /* H ref (J) non-zero to allow phase inclusion in preclb */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},                               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"alloy-liquid", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testAlL,         /* Pointer to testAlL  : test expected number and order  */
   conAlL,          /* Pointer to conAlL   : moles to indep comp variables   */
   actAlL,          /* Pointer to actAlL   : activities, chemical potentials */
   gmixAlL,         /* Pointer to gmixAlL  : Gibbs free energy of mixing     */
   hmixAlL,         /* Pointer to hmixAlL  : Enthaly of mixing               */
   smixAlL,         /* Pointer to smixAlL  : Entropy of mixing               */
   cpmixAlL,        /* Pointer to cpmixAlL : Heat capacity of mixing         */
   vmixAlL,         /* Pointer to vmixAlL  : Volume of mixing                */
   dispAlL          /* Pointer to dispAlL  : Formula for interface display   */
  },
  {"Fe-liquid", COMPONENT, "Fe", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /*               Calculated in GIBBS.C */
   {                /* ThermoRef structure                                   */
   9999.0,          /* H ref (J) non-zero to allow phase inclusion in preclb */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},                               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  },
  {"Ni-liquid", COMPONENT, "Ni", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /*               Calculated in GIBBS.C */
   {                /* ThermoRef structure                                   */
   9999.0,          /* H ref (J) non-zero to allow phase inclusion in preclb */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},                               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   }
  }
#ifdef FOWLER
  ,
  {"lime", PHASE, "CaO", DO_NOT_INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -635090.0,       /* H ref (J)         				     */
   37.750,          /* S ref (J/K)       				     */
   1.676,           /* V ref (J/bar)     				     */
   CP_BERMAN,  {{58.79117,-1.33904e2,-11.47146e5,10.2978784e7, 0.0, 0.0, 0.0, 0.0}},                 
   EOS_BERMAN, {{-1.0217132e-6, 2.5650e-12, 34.6103555e-6, 6.7406e-9}} 
   }
  },
  {"periclase", PHASE, "MgO", DO_NOT_INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -601500.0,       /* H ref (J)                               Berman (1990) */
   26.951,          /* S ref (J/K)                             Berman (1990) */
   1.125,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{61.10965, -2.96199e2, -6.21154e5, 0.5844612e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-0.6223329e-6, 1.5114e-12, 37.4774182e-6, 3.556e-10}} 
   }
  }
#endif
};
int const meltsNpc = (sizeof meltsSolids  / sizeof(struct _solids));

Solids pMeltsSolids[] = {
  {"olivine", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testOlv,         /* Pointer to testOlv  : test expected number and order  */
   conOlv,          /* Pointer to conOlv   : moles to indep comp variables   */
   actOlv,          /* Pointer to actOlv   : activities, chemical potentials */
   gmixOlv,         /* Pointer to gmixOlv  : Gibbs free energy of mixing     */
   hmixOlv,         /* Pointer to hmixOlv  : Enthaly of mixing               */
   smixOlv,         /* Pointer to smixOlv  : Entropy of mixing               */
   cpmixOlv,        /* Pointer to cpmixOlv : Heat capacity of mixing         */
   vmixOlv,         /* Pointer to vmixOlv  : Volume of mixing                */
   dispOlv          /* Pointer to dispOlv  : Formula for interface display   */
  },
  {"tephroite", COMPONENT, "Mn2SiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1732000.0,       /* H ref (J)                              Berman (1988) */
   155.900,          /* S ref (J/K)                            Berman (1988) */
   4.889,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{219.89, -12.710E2, -20.496E5, 17.652E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.784E-6, 0.0, 25.14E-6, 64.7E-10}}
   }
  },
  {"fayalite", COMPONENT, "Fe2SiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1479360.0,       /* H ref (J)                              Berman (1988) */
   150.930,          /* S ref (J/K)                            Berman (1988) */ 
   4.630,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{248.93, -19.239E2, 0.0, -13.910E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_BERMAN, {{-0.730E-6, 0.0, 26.546E-6, 79.482E-10}}
   }
  },
  {"co-olivine", COMPONENT, "Co2SiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1414100.0,       /* H ref (J)                              Berman (1988) */
   142.600,          /* S ref (J/K)                            Berman (1988) */
   4.459,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{201.048, -0.369E2, -71.81E5, 90.05E7, 0.0, 0.0, 0.0, 0.0}},             
   EOS_BERMAN, {{-0.64E-6, 0.0E-12, 28.422E-6, 35.355E-10}}
   }
  },
  {"ni-olivine", COMPONENT, "Ni2SiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1395300.0,       /* H ref (J)                              Berman (1988) */
   128.100,          /* S ref (J/K)                            Berman (1988) */
   4.259,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{214.997, -10.308E2, -49.445E5, 62.370E7, 0.0, 0.0, 0.0, 0.0}},          
   EOS_BERMAN, {{-0.671E-6, 0.0E-12, 28.422E-6, 35.355E-10}}
   }
  },
  {"monticellite", COMPONENT, "CaMgSiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2250027.0,       /* H ref (J)                              Berman (1988) */
   108.300,          /* S ref (J/K)                            Berman (1988) */
   5.148,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{226.34, -15.427E2, -11.797E5, -2.329E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.904E-6, 2.00E-12, 27.863E-6, 76.339E-10}}
   }
  },
  {"forsterite", COMPONENT, "Mg2SiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2174420.0,       /* H ref (J)                              Berman (1988) */
   94.010,           /* S ref (J/K)                            Berman (1988) */
   4.366,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{238.64, -20.013E2, 0.0, -11.624E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_BERMAN, {{-0.791E-6, 1.351E-12, 29.464E-6, 88.633E-10}}
   }
  },
  {"sphene", PHASE, "CaTiSiO5", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2596652.0,       /* H ref (J)                              Berman (1988) */
   129.290,          /* S ref (J/K)                            Berman (1988) */
   5.565,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{234.62, -10.403E2, -51.183E5, 59.146E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.590E-6, 0.0, 25.200E-6, 0.0}}
   }
  },
  {"garnet", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testGrn,         /* Pointer to testGrn  : test expected number and order  */
   conGrn,          /* Pointer to conGrn   : moles to indep comp variables   */
   actGrn,          /* Pointer to actGrn   : activities, chemical potentials */
   gmixGrn,         /* Pointer to gmixGrn  : Gibbs free energy of mixing     */
   hmixGrn,         /* Pointer to hmixGrn  : Enthaly of mixing               */
   smixGrn,         /* Pointer to smixGrn  : Entropy of mixing               */
   cpmixGrn,        /* Pointer to cpmixGrn : Heat capacity of mixing         */
   vmixGrn,         /* Pointer to vmixGrn  : Volume of mixing                */
   dispGrn          /* Pointer to dispGrn  : Formula for interface display   */
  },
  {"almandine", COMPONENT, "Fe3Al2Si3O12", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -5267216.0,      /* H ref (J)                               Berman (1990) */
   340.007,         /* S ref (J/K)                             Berman (1990) */
   11.511,          /* V (J/bar)                               Berman (1988) */
   CP_BERMAN,  {{573.96, -14.831E2, -292.920E5, 502.208E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{-0.558E-6, 0.321E-12, 18.613E-6, 74.539E-10}}
   }
  },
  {"grossular", COMPONENT, "Ca3Al2Si3O12", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -6632859.0,       /* H ref (J)                              Berman (1988) */
   255.150,          /* S ref (J/K)                            Berman (1988) */
   12.538,           /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{573.43, -20.394E2, -188.872E5, 231.931E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{-0.654E-6, 1.635E-12, 18.994E-6, 79.756E-10}}
   }
  },
  {"pyrope", COMPONENT, "Mg3Al2Si3O12", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -6286548.0,       /* H ref (J)                              Berman (1988) */
   266.359,          /* S ref (J/K)                            Berman (1988) */
   11.316,           /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{640.72, -45.421E2, -47.019E5, 0.0E7, 0.0, 0.0, 0.0, 0.0}},              
   EOS_BERMAN, {{-0.576E-6, 0.442E-12, 22.519E-6, 37.044E-10}}
   }
  },
  {"melilite", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testMel,         /* Pointer to testMel  : test expected number and order  */
   conMel,          /* Pointer to conMel   : moles to indep comp variables   */
   actMel,          /* Pointer to actMel   : activities, chemical potentials */
   gmixMel,         /* Pointer to gmixMel  : Gibbs free energy of mixing     */
   hmixMel,         /* Pointer to hmixMel  : Enthaly of mixing               */
   smixMel,         /* Pointer to smixMel  : Entropy of mixing               */
   cpmixMel,        /* Pointer to cpmixMel : Heat capacity of mixing         */
   vmixMel,         /* Pointer to vmixMel  : Volume of mixing                */
   dispMel          /* Pointer to dispMel  : Formula for interface display   */
  },
  {"akermanite", COMPONENT, "Ca2MgSi2O7", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3860441.0+4900.0,/* H ref (J)                              Berman (1988) */
   212.000,         /* S ref (J/K)                             Berman (1988) */
   9.252,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{387.06, -29.388E2, 0.0, -4.079E7, 358.0, 452.0, 0.0, 0.0}},                 
   EOS_BERMAN, {{-0.785E-6, 0.0, 25.011E-6, 67.224E-10}}
   }
  }, 
  {"gehlenite", COMPONENT, "Ca2Al2SiO7", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                                         /* Ordering done in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3988158.0+18900.0,/* H ref (J)                             Berman (1988) */
   198.600,          /* S ref (J/K)                            Berman (1988) */
   9.033,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{373.09, -22.768E2, -47.785E5, 47.791E7, 0.0, 0.0, 0.0, 0.0}},          
   EOS_BERMAN, {{-0.996E-6, 2.488E-12, 24.926E-6, 5.664E-10}}
   }
  },
  {"iron-akermanite", COMPONENT, "Ca2FeSi2O7", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,     /* akermanite */
   0.0, 0.0,                /* Ca2MgSi2O7 + 1/2 Fe2SiO4 - 1/2 Mg2SiO4 in Gibbs.c */
   {                /* ThermoRef structure                                   */
   -3860441.0+4000.0,/* H ref (J)                              Berman (1988) */
   212.000,         /* S ref (J/K)                             Berman (1988) */
   9.252,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{387.06, -29.388E2, 0.0, -4.079E7, 358.0, 452.0, 0.0, 0.0}},                 
   EOS_BERMAN, {{-0.785E-6, 0.0, 25.011E-6, 67.224E-10}}
   }
  },  
  {"soda-melilite", COMPONENT, "Na2Si3O7", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,       /* gehlenite */
   0.0, 0.0,                 /* Ca2Al2SiO7 + 2NaAlSi3O8 - 2CaAl2Si2O8 in Gibbs.c */                    
   {                /* ThermoRef structure                                   */
   -3988158.0+6700.0,/* H ref (J)                              Berman (1988) */
   198.600,          /* S ref (J/K) + 2Rln(2)                  Berman (1988) */
   9.033,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{373.09, -22.768E2, -47.785E5, 47.791E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.996E-6, 2.488E-12, 24.926E-6, 5.664E-10}}
   }
  },
  {"orthopyroxene", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testOpx,         /* Pointer to testOpx  : test expected number and order  */
   conOpx,          /* Pointer to conOpx   : moles to indep comp variables   */
   actOpx,          /* Pointer to actOpx   : activities, chemical potentials */
   gmixOpx,         /* Pointer to gmixOpx  : Gibbs free energy of mixing     */
   hmixOpx,         /* Pointer to hmixOpx  : Enthaly of mixing               */
   smixOpx,         /* Pointer to smixOpx  : Entropy of mixing               */
   cpmixOpx,        /* Pointer to cpmixOpx : Heat capacity of mixing         */
   vmixOpx,         /* Pointer to vmixOpx  : Volume of mixing                */
   dispOpx          /* Pointer to dispOpx  : Formula for interface display   */
  },
  {"diopside", COMPONENT, "CaMgSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3200583.0,      /* H ref (J)                               Berman (1988) */
   142.5,           /* S ref (J/K)                             Berman (1988) */
   6.620,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{305.41, -16.049E2, -71.660E5, 92.184E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.872E-6, 1.707E-12, 27.795E-6, 83.082E-10}}
   }
  },
  {"clinoenstatite", COMPONENT, "Mg2Si2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                                                       /* C2/c phase */
   {                /* ThermoRef structure                                   */
   -3086083.0,      /* H ref (J)                     2.0*Berman (1988) + DH2 */
   135.164,         /* S ref (J/K)                   2.0*Berman (1988) + DS2 */
   6.3279,          /* V ref (J/bar)                 2.0*Berman (1988) + DV2 */
   CP_BERMAN,  {{333.16, -24.012E2, -45.412E5, 55.830E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.749E-6, 0.447E-12, 24.656E-6, 74.670E-10}}
   }
  },
  {"hedenbergite", COMPONENT, "CaFeSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2842221.0,       /* H ref (J)                           Sack and Ghiorso */
   174.2,            /* S ref (J/K)                         Sack and Ghiorso */
   6.7894,           /* V ref (J/bar)                       Sack and Ghiorso */
   CP_BERMAN,  {{307.89, -15.973E2, -69.925E5, 93.522E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.9925E-6, 1.4835E-12, 31.371E-6, 83.672E-10}}
   }
  },
#define H31  -8.56518 * 1000.0  /* Joules     */
#define S31   0.00000           /* Joules/K   */
#define V31   0.00000           /* Joules/bar */
#define H41   7.93205 * 1000.0  /* Joules     */
#define S41  18.756             /* Joules/K   */
#define V41   0.00000           /* Joules/bar */
#define H51  -7.26701 * 1000.0  /* Joules     */
#define S51  18.756             /* Joules/K   */
  {"alumino-buffonite", COMPONENT, "CaTi0.5Mg0.5AlSiO6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3275265.0+(H31),             /* H ref (J)                          Guess */
   143.745+(S31),                /* S ref (J/K)                        Guess */
   6.356+(V31),      /* V ref (J/bar)           Guessed as identical to CaTs */
   CP_BERMAN,  {{297.499, -13.5596e2, -67.0219e5, 75.9082e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-0.870e-6, 2.171e-12, 22.250e-6, 52.863e-10}}
   }
  },
  {"buffonite", COMPONENT, "CaTi0.5Mg0.5FeSiO6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2836709.0+(H41),             /* H ref (J)                          Guess */
   161.985+(S41),                /* S ref (J/K)                        Guess */ 
   6.7217+(V41),     /* V ref (J/bar)       Guessed as identical to essenite */
   CP_BERMAN,  {{303.909, -14.1767e2, -43.5654e5, 35.2523e7, 0.0, 0.0, 0.0, 0.0}},       
   EOS_BERMAN, {{-0.870e-6, 2.171e-12, 22.250e-6, 52.863e-10}}
   }
  },
  {"essenite", COMPONENT, "CaFeAlSiO6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2860211.0+(H51),             /* H ref (J)    H CaTs (Berman 1988)-H3+H4  */
   158.991+(S51),                /* S ref (J/K)  S CaTs (Berman 1988)-S3+S4  */
   6.7217,           /* V ref (J/bar)       Cosca and Peacor (AM 72:148-156) */
   CP_BERMAN,  {{317.11, -17.333e2, -51.0965e5, 54.222e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-0.870e-6, 2.171e-12, 22.250e-6, 52.863e-10}}
   }
  },
#undef H31
#undef S31
#undef V31
#undef H41
#undef S41
#undef V41
#undef H51
#undef S51
  {"jadeite", COMPONENT, "NaAlSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3025118.0,      /* H ref (J)                               Berman (1988) */
   133.574,         /* S ref (J/K)                             Berman (1988) */
   6.034,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{311.29, -20.051e2, -53.503e5, 66.257e7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.860e-6, 2.149e-12, 23.118e-6, 25.785e-10}}
   }
  },
  {"clinopyroxene", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testCpx,         /* Pointer to testCpx  : test expected number and order  */
   conCpx,          /* Pointer to conCpx   : moles to indep comp variables   */
   actCpx,          /* Pointer to actCpx   : activities, chemical potentials */
   gmixCpx,         /* Pointer to gmixCpx  : Gibbs free energy of mixing     */
   hmixCpx,         /* Pointer to hmixCpx  : Enthaly of mixing               */
   smixCpx,         /* Pointer to smixCpx  : Entropy of mixing               */
   cpmixCpx,        /* Pointer to cpmixCpx : Heat capacity of mixing         */
   vmixCpx,         /* Pointer to vmixCpx  : Volume of mixing                */
   dispCpx          /* Pointer to dispCpx  : Formula for interface display   */
  },
  {"diopside", COMPONENT, "CaMgSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3200583.0,      /* H ref (J)                               Berman (1988) */
   142.5,           /* S ref (J/K)                             Berman (1988) */
   6.620,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{305.41, -16.049E2, -71.660E5, 92.184E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.872E-6, 1.707E-12, 27.795E-6, 83.082E-10}}
   }
  },
  {"clinoenstatite", COMPONENT, "Mg2Si2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                                                       /* C2/c phase */
   {                /* ThermoRef structure                                   */
   -3086083.0,      /* H ref (J)                     2.0*Berman (1988) + DH2 */
   135.164,         /* S ref (J/K)                   2.0*Berman (1988) + DS2 */
   6.3279,          /* V ref (J/bar)                 2.0*Berman (1988) + DV2 */
   CP_BERMAN,  {{333.16, -24.012E2, -45.412E5, 55.830E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.749E-6, 0.447E-12, 24.656E-6, 74.670E-10}}
   }
  },
  {"hedenbergite", COMPONENT, "CaFeSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2842221.0,       /* H ref (J)                           Sack and Ghiorso */
   174.2,            /* S ref (J/K)                         Sack and Ghiorso */
   6.7894,           /* V ref (J/bar)                       Sack and Ghiorso */
   CP_BERMAN,  {{307.89, -15.973E2, -69.925E5, 93.522E7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.9925E-6, 1.4835E-12, 31.371E-6, 83.672E-10}}
   }
  },
#define H31  -8.56518 * 1000.0  /* Joules     */
#define S31   0.00000           /* Joules/K   */
#define V31   0.00000           /* Joules/bar */
#define H41   7.93205 * 1000.0  /* Joules     */
#define S41  18.756             /* Joules/K   */
#define V41   0.00000           /* Joules/bar */
#define H51  -7.26701 * 1000.0  /* Joules     */
#define S51  18.756             /* Joules/K   */
  {"alumino-buffonite", COMPONENT, "CaTi0.5Mg0.5AlSiO6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3275265.0+(H31),             /* H ref (J)                          Guess */
   143.745+(S31),                /* S ref (J/K)                        Guess */
   6.356+(V31),      /* V ref (J/bar)           Guessed as identical to CaTs */
   CP_BERMAN,  {{297.499, -13.5596e2, -67.0219e5, 75.9082e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-0.870e-6, 2.171e-12, 22.250e-6, 52.863e-10}}
   }
  },
  {"buffonite", COMPONENT, "CaTi0.5Mg0.5FeSiO6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2836709.0+(H41),             /* H ref (J)                          Guess */
   161.985+(S41),                /* S ref (J/K)                        Guess */ 
   6.7217+(V41),     /* V ref (J/bar)       Guessed as identical to essenite */
   CP_BERMAN,  {{303.909, -14.1767e2, -43.5654e5, 35.2523e7, 0.0, 0.0, 0.0, 0.0}},       
   EOS_BERMAN, {{-0.870e-6, 2.171e-12, 22.250e-6, 52.863e-10}}
   }
  },
  {"essenite", COMPONENT, "CaFeAlSiO6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2860211.0+(H51),             /* H ref (J)    H CaTs (Berman 1988)-H3+H4  */
   158.991+(S51),                /* S ref (J/K)  S CaTs (Berman 1988)-S3+S4  */
   6.7217,           /* V ref (J/bar)       Cosca and Peacor (AM 72:148-156) */
   CP_BERMAN,  {{317.11, -17.333e2, -51.0965e5, 54.222e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-0.870e-6, 2.171e-12, 22.250e-6, 52.863e-10}}
   }
  },
#undef H31
#undef S31
#undef V31
#undef H41
#undef S41
#undef V41
#undef H51
#undef S51
  {"jadeite", COMPONENT, "NaAlSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3025118.0,      /* H ref (J)                               Berman (1988) */
   133.574,         /* S ref (J/K)                             Berman (1988) */
   6.034,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{311.29, -20.051e2, -53.503e5, 66.257e7, 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{-0.860e-6, 2.149e-12, 23.118e-6, 25.785e-10}}
   }
  },
  {"aegirine", PHASE, "NaFeSi2O6", DO_NOT_INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2576800.0,      /* H ref (J)		       Sack & Ghiorso (1994) */
   170.57,          /* S ref (J/K)		       Sack & Ghiorso (1994) */
   63.997,         /* V ref (J/bar)		       Sack & Ghiorso (1994) */
   CP_BERMAN, {{311.29+303.909-297.499, -20.051e2+(-14.1767e2)-(-13.5596e2), -53.503e5+(-43.5654e5)-(-67.0219e5), 66.257e7+(35.2523e7)-(75.9082e7), 0.0, 0.0, 0.0, 0.0}},           
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}                /* v1, v2, v3, v4 terms */
   }
  },
  {"aenigmatite", PHASE, "Na2Fe5TiSi6O20", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -8472805.0,       /* H ref (J)                                      Guess */
   740.23,           /* S ref (J/K)                  Sum-of-oxides+magnetics */
   22.8546,          /* V ref (J/bar)               Specific gravity of 3.77 */
   CP_BERMAN,  {{1092.073, -61.5981e2, -225.2679e5, 326.8659e7,  0.0, 0.0, 0.0, 0.0}},   
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"cummingtonite", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testCum,         /* Pointer to testCum  : test expected number and order  */
   conCum,          /* Pointer to conCum   : moles to indep comp variables   */
   actCum,          /* Pointer to actCum   : activities, chemical potentials */
   gmixCum,         /* Pointer to gmixCum  : Gibbs free energy of mixing     */
   hmixCum,         /* Pointer to hmixCum  : Enthaly of mixing               */
   smixCum,         /* Pointer to smixCum  : Entropy of mixing               */
   cpmixCum,        /* Pointer to cpmixCum : Heat capacity of mixing         */
   vmixCum,         /* Pointer to vmixCum  : Volume of mixing                */
   dispCum          /* Pointer to dispCum  : Formula for interface display   */
  },
  {"cummingtonite", COMPONENT, "Mg7Si8O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -12067517.0,     /* H ref (J)                Ghiorso et al. (1995)        */
   540.2587,        /* S ref (J/K)              Ghiorso et al. (1995)        */
   26.33,           /* V ref (J/bar)            Ghiorso et al. (1995)        */
   CP_BERMAN,  {{1233.79200, -71.33980e2, -221.63800e5, 233.393749e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.1393847e-6, 0.0, 28.1048234e-6, 62.894e-10}}
   }
  },
  {"grunerite", COMPONENT, "Fe7Si8O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -9623300.0,      /* H ref (J)                Ghiorso et al. (1995)        */
   725.0,           /* S ref (J/K)              Ghiorso et al. (1995)        */
   27.840,          /* V ref (J/bar)            Ghiorso et al. (1995)        */
   CP_BERMAN,  {{1347.83, -93.5691e2, -202.2848e5, 303.919e7, 0.0, 0.0, 0.0, 0.0}},      
   EOS_BERMAN, {{-1.670299e-6, 8.68919e-12, 28.400e-6, 0.0}}
   }
  },
  {"amphibole", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testAph,         /* Pointer to testAph  : test expected number and order  */
   conAph,          /* Pointer to conAph   : moles to indep comp variables   */
   actAph,          /* Pointer to actAph   : activities, chemical potentials */
   gmixAph,         /* Pointer to gmixAph  : Gibbs free energy of mixing     */
   hmixAph,         /* Pointer to hmixAph  : Enthaly of mixing               */
   smixAph,         /* Pointer to smixAph  : Entropy of mixing               */
   cpmixAph,        /* Pointer to cpmixAph : Heat capacity of mixing         */
   vmixAph,         /* Pointer to vmixAph  : Volume of mixing                */
   dispAph          /* Pointer to dispAph  : Formula for interface display   */
  },
  {"cummingtonite", COMPONENT, "Mg7Si8O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -12067920.38,    /* H ref (J)                Ghiorso et al. (2001)        */
   540.2587,        /* S ref (J/K)              Ghiorso et al. (1995)        */
   26.34,           /* V ref (J/bar)            Ghiorso et al. (2001)        */
   CP_BERMAN,  {{1233.79200, -71.33980e2, -221.63800e5, 233.393749e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.1393847e-6, 0.0, 28.1048234e-6, 62.894e-10}} 
   }
  },
  {"grunerite", COMPONENT, "Fe7Si8O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -9623550.0,      /* H ref (J)                Ghiorso et al. (2001)        */
   725.0,           /* S ref (J/K)              Ghiorso et al. (1995)        */
   27.840,          /* V ref (J/bar)            Ghiorso et al. (1995)        */
   CP_BERMAN,  {{1347.83, -93.5691e2, -202.2848e5, 303.919e7, 0.0, 0.0, 0.0, 0.0}},      
   EOS_BERMAN, {{-1.670299e-6, 8.68919e-12, 28.400e-6, 0.0}} 
   }
  },
  {"tremolite", COMPONENT, "Ca2Mg5Si8O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -12307863.0,     /* H ref (J)                Ghiorso et al. (2001)        */
   549.500,         /* S ref (J/K)              Bernard's Guess              */
   27.312,          /* V ref (J/bar)            Yang and Evans               */
   CP_BERMAN,  {{1229.36, -64.019e2, -320.899e5, 420.881e7, 0.0, 0.0, 0.0, 0.0}},        
   EOS_BERMAN, {{-1.4763e-6, 8.9462e-12, 24.374e-6, 98.338e-10}} 
   }
  },
  {"hornblende", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testHrn,         /* Pointer to testHrn  : test expected number and order  */
   conHrn,          /* Pointer to conHrn   : moles to indep comp variables   */
   actHrn,          /* Pointer to actHrn   : activities, chemical potentials */
   gmixHrn,         /* Pointer to gmixHrn  : Gibbs free energy of mixing     */
   hmixHrn,         /* Pointer to hmixHrn  : Enthaly of mixing               */
   smixHrn,         /* Pointer to smixHrn  : Entropy of mixing               */
   cpmixHrn,        /* Pointer to cpmixHrn : Heat capacity of mixing         */
   vmixHrn,         /* Pointer to vmixHrn  : Volume of mixing                */
   dispHrn          /* Pointer to dispHrn  : Formula for interface display   */
  },
  {"pargasite", COMPONENT, "NaCa2Mg4AlAl2Si6O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3016624.0*4.184,                 /* H ref (J)     Helgeson et al. (1978) */
   160.0*4.184,                      /* S ref (J/K)   Helgeson et al. (1978) */
   27.35,                            /* V ref (J/bar) Helgeson et al. (1978) */
   CP_BERMAN,  {{1267.25, -66.5434e2, -303.787e5, 391.353e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.392e-6, 3.481e-12, 24.374e-6, 98.338e-10}} 
   }
  },
#define DHGrnCum (-9623300.0-(-12067517.0))
  {"ferropargasite", COMPONENT, "NaCa2Fe4AlAl2Si6O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3016624.0*4.184+4.0*DHGrnCum/7.0,/* H ref (J)     Helgeson et al. (1978) */
   185.5*4.184,                      /* S ref (J/K)   Helgeson et al. (1978) */
   27.989,                           /* V ref (J/bar) Helgeson et al. (1978) */
   CP_BERMAN,  {{1342.61, -83.4862e2, -247.604e5, 348.507e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.392e-6, 3.481e-12, 24.374e-6, 98.338e-10}} 
   }
  },
#undef DHGrnCum
#define DHBfABf ((-2836709.0+7932.05)-(-3275265.0-8565.18))
  {"magnesiohastingsite", COMPONENT, "NaCa2Mg4FeAl2Si6O22(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3016624.0*4.184+DHBfABf,         /* H ref (J)     Helgeson et al. (1978) */
   163.8*4.184,                      /* S ref (J/K)   Helgeson et al. (1978) */
   27.38,                            /* V ref (J/bar) Helgeson et al. (1978) */
   CP_BERMAN,  {{1273.66, -67.1606e2, -280.331e5, 350.697e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.392e-6, 3.481e-12, 24.374e-6, 98.338e-10}} 
   }
  },
#undef DHBfABf
  {"biotite", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testBio,         /* Pointer to testBio  : test expected number and order  */
   conBio,          /* Pointer to conBio   : moles to indep comp variables   */
   actBio,          /* Pointer to actBio   : activities, chemical potentials */
   gmixBio,         /* Pointer to gmixBio  : Gibbs free energy of mixing     */
   hmixBio,         /* Pointer to hmixBio  : Enthaly of mixing               */
   smixBio,         /* Pointer to smixBio  : Entropy of mixing               */
   cpmixBio,        /* Pointer to cpmixBio : Heat capacity of mixing         */
   vmixBio,         /* Pointer to vmixBio  : Volume of mixing                */
   dispBio          /* Pointer to dispBio  : Formula for interface display   */
  },
  {"annite", COMPONENT, "KFe3Si3AlO10(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -5142800.0,      /* H ref (J)                               Berman (1990) */
   420.0,           /* S ref (J/K)                             Berman (1990) */
   15.408,          /* V ref (J/bar)                           Berman (1990) */
   CP_BERMAN,  {{727.208, -47.75040e2, -138.319e5, 211.906e7, 0.0, 0.0, 0.0, 0.0}},      
   EOS_BERMAN, {{-1.6969784e-6, 0.0, 34.4473262e-6, 0.0}} 
   }
  },
  {"phlogopite", COMPONENT, "KMg3Si3AlO10(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -6210391.0,      /* H ref (J)                               Berman (1990) */
   334.346,         /* S ref (J/K)                             Berman (1990) */
   14.977,          /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{610.37988, -20.83781e2, -215.33008e5, 284.1040896e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.6969784e-6, 0.0, 34.4473262e-6, 0.0}} 
   }
  },
  {"muscovite", PHASE, "KAl2Si3AlO10(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -5976740.0,      /* H ref (J)                               Berman (1988) */
   293.157,         /* S ref (J/K)                             Berman (1988) */
   14.087,          /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{651.49, -38.732e2, -185.232e5, 274.247e7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{-1.717e-6, 4.295e-12, 33.527e-6, 0.0}} 
   }
  },
  {"feldspar", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testFld,         /* Pointer to testFld  : test expected number and order  */
   conFld,          /* Pointer to conFld   : moles to indep comp variables   */
   actFld,          /* Pointer to actFld   : activities, chemical potentials */
   gmixFld,         /* Pointer to gmixFld  : Gibbs free energy of mixing     */
   hmixFld,         /* Pointer to hmixFld  : Enthaly of mixing               */
   smixFld,         /* Pointer to smixFld  : Entropy of mixing               */
   cpmixFld,        /* Pointer to cpmixFld : Heat capacity of mixing         */
   vmixFld,         /* Pointer to vmixFld  : Volume of mixing                */
   dispFld          /* Pointer to dispFld  : Formula for interface display   */
  },
  {"albite", COMPONENT, "NaAlSi3O8", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                                      /* Salje correction in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3921618.0,      /* H ref (J)                   monalbite - Berman (1988) */
   224.412,         /* S ref (J/K)                             Berman (1988) */
   10.083,          /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{393.64, -24.155E2, -78.928E5, 107.064E7, 0.0, 0.0, 0.0, 0.0}},          
   EOS_BERMAN, {{-1.945E-6, 4.861E-12, 26.307E-6, 32.407E-10}} 
   }
  },
  {"anorthite", COMPONENT, "CaAl2Si2O8", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -4228730.0,     /* H ref (J)   Berman (1988)  Carpenter I1->C1 +3.7*4184.0*/
   200.186, /* S ref (J/K) Berman (1988)  Carpenter I1->C1 +3.7*4184.0/2200.0*/
   10.075,           /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{439.37, -37.341E2, 0.0, -31.702E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_BERMAN, {{-1.272E-6, 3.176E-12, 10.918E-6, 41.985E-10}} 
   }
  },
  {"sanidine", COMPONENT, "KAlSi3O8", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                             /* K-feldspar, ordering done in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3970791.0,       /* H ref (J)                              Berman (1988) */
   214.145,          /* S ref (J/K)                            Berman (1988) */
   10.869,           /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN,  {{381.37, -19.410E2, -120.373E5, 183.643E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{-1.805E-6, 5.112E-12, 15.145E-6, 54.850E-10}} 
   }
  },
  {"quartz", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -910700.0,        /* H ref (J) Berman (1988)                              */
   41.460,           /* S ref (J/K) Berman (1988)                            */
   2.269,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{80.01, -2.403E2, -35.467E5, 49.157E7, 848.0, 0.0, -9.187E-2, 24.607E-5}},
   EOS_BERMAN, {{-2.434E-6, 10.137E-12, 23.895E-6, 0.0}}
   }
  },
  {"tridymite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907750.0,        /* H ref (J) Berman (1988)                              */
   43.770,           /* S ref (J/K) Berman (1988)                            */
   2.675,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{75.37, 0.0, -59.581E5, 95.825E7, 383.0, 130.0, 42.670E-2, -144.575E-5}},
   EOS_BERMAN, {{-2.508E-6, 0.0, 19.339E-6, 0.0}}
   }
  },
  {"cristobalite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907753.0,        /* H ref (J) Berman (1988)                              */
   43.394,           /* S ref (J/K) Berman (1988)                            */
   2.587,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{83.51, -3.747E2, -24.554E5, 28.007E7, 535.0, 0.0, -14.216E-2, 44.142E-5}},
   EOS_BERMAN, {{-2.515E-6, 0.0, 20.824E-6, 0.0}}
   }
  },
  {"nepheline ss", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testNph,         /* Pointer to testNph  : test expected number and order  */
   conNph,          /* Pointer to conNph   : moles to indep comp variables   */
   actNph,          /* Pointer to actNph   : activities, chemical potentials */
   gmixNph,         /* Pointer to gmixNph  : Gibbs free energy of mixing     */
   hmixNph,         /* Pointer to hmixNph  : Enthaly of mixing               */
   smixNph,         /* Pointer to smixNph  : Entropy of mixing               */
   cpmixNph,        /* Pointer to cpmixNph : Heat capacity of mixing         */
   vmixNph,         /* Pointer to vmixNph  : Volume of mixing                */
   dispNph          /* Pointer to dispNph  : Formula for interface display   */
  },
  {"na-nepheline", COMPONENT, "Na4Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2093004.0*4.0,         /* H ref (J)  Waterwiese et al. (1995)            */
   124.641*4.0,            /* S ref (J/K)                                    */
   5.4131*4.0,             /* V ref (J/bar)                                  */
   CP_BERMAN,  {{205.24*4.0, -7.599E2*4.0, -108.383E5*4.0, 208.182E7*4.0, 467.0, 241.0*4.0, -50.249E-2*2.0, 165.95E-5*2.0}},
   EOS_BERMAN, {{-2.0500e-6, 5.2000e-12, 31.802e-6, 213.0e-10}}
   }
  },
#define DH2     -1.35      * 1000.0 * 4.184 /* K4Al4Si4O16 kals-neph  joules */ 
#define DS2      0.0       * 1000.0 * 4.184 /* joules/T */
#define DV2     -0.00001   * 1000.0 * 4.184 /* joules/bar */
  {"k-nepheline", COMPONENT, "K4Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2109563.55*4.0-(DH2)-3572.76, /* H ref (J)   Berman (pers com) Kalsilite */
   133.9653*4.0-(DS2),          /* S ref (J/K)   Berman (pers com) Kalsilite */
   6.043478*4.0-(DV2),          /* V ref (J/bar)                   Kalsilite */
   CP_BERMAN,  {{186.0*4.0, 0.0, -131.067E5*4.0, 213.893E7*4.0, 800.15, 1154.0*4.0, -7.096454E-2*2.0, 21.682E-5*2.0}},
   EOS_BERMAN, {{-2.0500e-6, 5.2000e-12, 31.802e-6, 213.0e-10}}
   }
  },
  {"vc-nepheline", COMPONENT, "Na3Al3Si5O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,       /* monalbite */
   0.0, 0.0,                                      /* Salje correction in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3921618.0,      /* H ref (J)                   monalbite - Berman (1988) */
   224.412,         /* S ref (J/K)                             Berman (1988) */
   0.0,             /* V ref (J/bar) - Volume correction accounted in Gibbs  */
   CP_BERMAN,  {{393.64, -24.155E2, -78.928E5, 107.064E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"ca-nepheline", COMPONENT, "CaNa2Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,  /* C1-anorthite */
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -4228730.0,        /* H ref (J) Berman (1988) Carpenter I1->C1 +3.7*4184.0*/
   200.186, /* S ref (J/K) Berman (1988)  Carpenter I1->C1 +3.7*4184.0/2200.0*/
   0.0,              /* V ref (J/bar) - Volume correction accounted in Gibbs */
   CP_BERMAN,  {{439.37, -37.341E2, 0.0, -31.702E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"kalsilite ss", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testKal,         /* Pointer to testKal  : test expected number and order  */
   conKal,          /* Pointer to conKal   : moles to indep comp variables   */
   actKal,          /* Pointer to actKal   : activities, chemical potentials */
   gmixKal,         /* Pointer to gmixKal  : Gibbs free energy of mixing     */
   hmixKal,         /* Pointer to hmixKal  : Enthaly of mixing               */
   smixKal,         /* Pointer to smixKal  : Entropy of mixing               */
   cpmixKal,        /* Pointer to cpmixKal : Heat capacity of mixing         */
   vmixKal,         /* Pointer to vmixKal  : Volume of mixing                */
   dispKal          /* Pointer to dispKal  : Formula for interface display   */
  },
  {"na-nepheline", COMPONENT, "Na4Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2093004.0*4.0,         /* H ref (J)  Waterwiese et al. (1995)            */
   124.641*4.0,            /* S ref (J/K)                                    */
   5.4131*4.0,             /* V ref (J/bar)                                  */
   CP_BERMAN,  {{205.24*4.0, -7.599E2*4.0, -108.383E5*4.0, 208.182E7*4.0, 467.0, 241.0*4.0, -50.249E-2*2.0, 165.95E-5*2.0}},
   EOS_BERMAN, {{-2.0500e-6, 5.2000e-12, 31.802e-6, 213.0e-10}}
   }
  },
  {"k-nepheline", COMPONENT, "K4Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2109563.55*4.0-(DH2),       /* H ref (J)     Berman (pers com) Kalsilite */
   133.9653*4.0-(DS2),          /* S ref (J/K)   Berman (pers com) Kalsilite */
   6.043478*4.0-(DV2),          /* V ref (J/bar)                   Kalsilite */
   CP_BERMAN,  {{186.0*4.0, 0.0, -131.067E5*4.0, 213.893E7*4.0, 800.15, 1154.0*4.0, -7.096454E-2*2.0, 21.682E-5*2.0}},
   EOS_BERMAN, {{-2.0500e-6, 5.2000e-12, 31.802e-6, 213.0e-10}}
   }
  },
  {"vc-nepheline", COMPONENT, "Na3Al3Si5O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,       /* monalbite */
   0.0, 0.0,                                      /* Salje correction in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -3921618.0,      /* H ref (J)                   monalbite - Berman (1988) */
   224.412,         /* S ref (J/K)                             Berman (1988) */
   0.0,             /* V ref (J/bar) - Volume correction accounted in Gibbs  */
   CP_BERMAN,  {{393.64, -24.155E2, -78.928E5, 107.064E7, 0.0, 0.0, 0.0, 0.0}},         
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"ca-nepheline", COMPONENT, "CaNa2Al4Si4O16", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL,  /* C1-anorthite */
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -4228730.0,     /* H ref (J)   Berman (1988)  Carpenter I1->C1 +3.7*4184.0*/
   200.186, /* S ref (J/K) Berman (1988)  Carpenter I1->C1 +3.7*4184.0/2200.0*/
   0.0,              /* V ref (J/bar) - Volume correction accounted in Gibbs */
   CP_BERMAN,  {{439.37, -37.341E2, 0.0, -31.702E7, 0.0, 0.0, 0.0, 0.0}},               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"leucite ss", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testLeu,         /* Pointer to testLeu  : test expected number and order  */
   conLeu,          /* Pointer to conLeu   : moles to indep comp variables   */
   actLeu,          /* Pointer to actLeu   : activities, chemical potentials */
   gmixLeu,         /* Pointer to gmixLeu  : Gibbs free energy of mixing     */
   hmixLeu,         /* Pointer to hmixLeu  : Enthaly of mixing               */
   smixLeu,         /* Pointer to smixLeu  : Entropy of mixing               */
   cpmixLeu,        /* Pointer to cpmixLeu : Heat capacity of mixing         */
   vmixLeu,         /* Pointer to vmixLeu  : Volume of mixing                */
   dispLeu          /* Pointer to dispLeu  : Formula for interface display   */
  },
  {"leucite", COMPONENT, "KAlSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -3032146.03+27000.0,                       /* H ref (J)   adjusted 21866.4*/
   184.096+21.75,                        /* S ref (J/K)  Kelley et al. 1953  */
   8.8390,                             /* V ref (J/bar)  Robie et al. (1978) */
   CP_BERMAN,  {{271.14, -9.441E2, -78.572E5, 95.920E7, 955.0, 256.0, -9.731e-2, 33.730e-5}},
   EOS_BERMAN, {{-1.5568254e-6, 1.2739e-12, 12.5167877e-6, 0.0}}
   }
  },
  {"analcime", COMPONENT, "NaAlSi2O5(OH)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                             /*               properties of analcime */
   {                /* ThermoRef structure                                   */
   -3308500.0-17400,                 /* Johnson et al.             H ref (J) */
   228.10,                           /* Johnson et al.           S ref (J/K) */
   9.71,                             /*        Helgeson (1978) V ref (J/bar) */
   CP_BERMAN,  {{571.83, -71.887E2, 0.0, 149.306E7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.5568254e-6, 1.2739e-12, 12.5167877e-6, 0.0}}
   }
  },
  {"na-leucite", COMPONENT, "NaAlSi2O6", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                             /*    properties of dehydrated analcime */
   {                /* ThermoRef structure                                   */
   -2980100.0-21875.55,              /*   Johnson et al.           H ref (J) */
   173.68-7.94,                      /*   King and Weller (1961) S ref (J/K) */
   8.91,                             /*        Helgeson (1978) V ref (J/bar) */
   CP_BERMAN,  {{401.27, -42.480E2, 0.0, 21.630E7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.5568254e-6, 1.2739e-12, 12.5167877e-6, 0.0}}
   }
  },
#undef DH2
#undef DS2
#undef DV2
  {"corundum", PHASE, "Al2O3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1675700.0,      /* H ref (J)                               Berman (1988) */
   50.820,          /* S ref (J/K)                             Berman (1988) */
   2.558,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{155.02, -8.284E2, -38.614E5, 40.908E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{-0.385E-6, 0.375E-12, 21.342E-6, 47.180E-10}}
   }
  },
  {"rutile", PHASE, "TiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -944750.0,       /* H ref (J)                               Berman (1988) */
   50.460,          /* S ref (J/K)                             Berman (1988) */ 
   1.882,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{77.84, 0.0, -33.678E5, 40.294E7, 0.0, 0.0, 0.0, 0.0}},                  
   EOS_BERMAN, {{-0.454E-6, 0.584E-12, 25.716E-6, 15.409E-10}}
   }
  },
  {"perovskite", PHASE, "CaTiO3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1660630.0,      /* H ref (J)                         Robie et al. (1978) */
   93.64,           /* S ref (J/K)                       Robie et al. (1978) */
   3.3626,          /* V ref (J/bar)                     Robie et al. (1978) */
   CP_BERMAN,  {{150.49, -6.213E2, 0.0, -43.010E7, 1530.0, 550.0*4.184, 0.0, 0.0}},                 
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"spinel", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testSpn,         /* Pointer to testSpn  : test expected number and order  */
   conSpn,          /* Pointer to conSpn   : moles to indep comp variables   */
   actSpn,          /* Pointer to actSpn   : activities, chemical potentials */
   gmixSpn,         /* Pointer to gmixSpn  : Gibbs free energy of mixing     */
   hmixSpn,         /* Pointer to hmixSpn  : Enthaly of mixing               */
   smixSpn,         /* Pointer to smixSpn  : Entropy of mixing               */
   cpmixSpn,        /* Pointer to cpmixSpn : Heat capacity of mixing         */
   vmixSpn,         /* Pointer to vmixSpn  : Volume of mixing                */
   dispSpn          /* Pointer to dispSpn  : Formula for interface display   */
  },
  {"chromite", COMPONENT, "FeCr2O4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1445490.0,      /* H ref (J)                    Sack and Ghiorso (1991b) */
   142.676,         /* S ref (J/K)                  Sack and Ghiorso (1991b) */
   4.4010,          /* V ref (J/bar)                     Robie et al. (1978) */
   CP_BERMAN,  {{236.874, -16.796E2, 0.0, -16.765E7, 0.0, 0.0, 0.0, 0.0}},               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"hercynite", COMPONENT, "FeAl2O4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1947681.0,      /* H ref (J)                    Sack and Ghiorso (1991b) */
   115.362,         /* S ref (J/K)                  Sack and Ghiorso (1991b) */
   0.973948*4.184,  /* V ref (J/bar)                                         */
   CP_BERMAN,  {{235.190, -14.370E2, -46.913E5, 64.564E7, 0.0, 0.0, 0.0, 0.0}},          
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"magnetite", COMPONENT, "Fe3O4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1117403.0,      /* H ref (J)                               Berman (1988) */
   146.114,         /* S ref (J/K)                             Berman (1988) */
   4.452,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{207.93, 0.0, -72.433E5, 66.436E7, 848.0, 1565.0, -19.502E-2, 61.037E-5}},
   EOS_BERMAN, {{-0.582E-6, 1.751E-12, 30.291E-6, 138.470E-10}}
   }
  },
  {"spinel", COMPONENT, "MgAl2O4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2300313.0,      /* H ref (J)                               Berman (1988) */
   84.535,          /* S ref (J/K)                             Berman (1988) */
   3.977,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{235.90, -17.666E2, -17.104E5, 4.062E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{-0.489E-6, 0.0, 21.691E-6, 50.528E-10}}
   }
  },
  {"ulvospinel", COMPONENT, "Fe2TiO4", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1488500.0,      /* H ref (J)                    Sack and Ghiorso (1991b) */
   185.447,         /* S ref (J/K)                  Sack and Ghiorso (1991b) */
   4.682,           /* V ref (J/bar)                     Robie et al. (1978) */
   CP_BERMAN,  {{249.63, -18.174E2, 0.0, -5.453E7, 0.0, 0.0, 0.0, 0.0}},                 
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"rhm oxide", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testRhm,         /* Pointer to testRhm  : test expected number and order  */
   conRhm,          /* Pointer to conRhm   : moles to indep comp variables   */
   actRhm,          /* Pointer to actRhm   : activities, chemical potentials */
   gmixRhm,         /* Pointer to gmixRhm  : Gibbs free energy of mixing     */
   hmixRhm,         /* Pointer to hmixRhm  : Enthaly of mixing               */
   smixRhm,         /* Pointer to smixRhm  : Entropy of mixing               */
   cpmixRhm,        /* Pointer to cpmixRhm : Heat capacity of mixing         */
   vmixRhm,         /* Pointer to vmixRhm  : Volume of mixing                */
   dispRhm          /* Pointer to dispRhm  : Formula for interface display   */
  },
  {"geikielite", COMPONENT, "MgTiO3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1572560.0,      /* H ref (J)                              Ghiorso (1990) */
   74.56,           /* S ref (J/K)                            Ghiorso (1990) */
   3.086,           /* V ref (J/bar)                     Robie et al. (1978) */
   CP_BERMAN,  {{146.20, -4.160E2, -39.998E5, 40.233E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{-0.5839748e-6, 1.2303e-12, 27.2476341e-6, 29.968e-10}}
   }
  },
  {"hematite", COMPONENT, "Fe2O3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -822000.0,       /* H ref (J)                              Ghiorso (1990) */
   87.40,           /* S ref (J/K)                            Ghiorso (1990) */
   3.027,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{146.86, 0.0, -55.768E5, 52.563E7, 955.0, 1287.0, -7.403E-2, 27.921E-5}},
   EOS_BERMAN, {{-0.479E-6, 0.304E-12, 38.310E-6, 1.650E-10}}
   }
  },
  {"ilmenite", COMPONENT, "FeTiO3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1231947.0,      /* H ref (J)                               Berman (1988) */
   108.628,         /* S ref (J/K)                             Berman (1988) */
   3.170,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{150.00, -4.416E2, -33.237E5, 34.815E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{-0.584E-6, 1.230E-12, 27.248E-6, 29.968E-10}}
   }
  },
  {"pyrophanite", COMPONENT, "MnTiO3", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1350707.0,      /* H ref (J)                      Ghiorso (1991 - guess) */
   104.935,         /* S ref (J/K)               Stephenson and Smith (1968) */
   3.170,           /* V ref (J/bar)    (assumed ilmenite >>>) Berman (1988) */
   CP_BERMAN,  {{150.00, -4.416E2, -33.237E5, 34.815E7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{-0.584E-6, 1.230E-12, 27.248E-6, 29.968E-10}}
   }
  },
  {"ortho oxide", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testOox,         /* Pointer to testOox  : test expected number and order  */
   conOox,          /* Pointer to conOox   : moles to indep comp variables   */
   actOox,          /* Pointer to actOox   : activities, chemical potentials */
   gmixOox,         /* Pointer to gmixOox  : Gibbs free energy of mixing     */
   hmixOox,         /* Pointer to hmixOox  : Enthaly of mixing               */
   smixOox,         /* Pointer to smixOox  : Entropy of mixing               */
   cpmixOox,        /* Pointer to cpmixOox : Heat capacity of mixing         */
   vmixOox,         /* Pointer to vmixOox  : Volume of mixing                */
   dispOox          /* Pointer to dispOox  : Formula for interface display   */
  },
  {"pseudobrookite", COMPONENT, "Fe2TiO5", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                            /* Cp terms from Berman and Brown (1985) */
   {                /* ThermoRef structure                                   */
   -1754429.0,      /* H ref (J)   Analysis of Haggerty & Lindsley Data      */
   156.4816,        /* S ref (J/K) Kelley & King (1961)                      */
   5.491,           /* V ref (J/bar) From page 45 (oxide short course)       */
   CP_BERMAN,  {{261.35, -15.307e2, 0.0, -23.466e7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"ferropseudobrookite", COMPONENT, "FeTi2O5", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2175332.0,      /* H ref (J)   Analysis of Haggerty & Lindsley Data      */
   127.1936-26.94+59.80, /* King & Kelley (1961) for MgTi2O5 - MgO (periclase
                     Robie et al. (1978) + FeO (stoich) (op cit) S ref (J/K) */
   5.578,           /* V ref (J/bar) From page 45 (oxide short course)
                       Armacolite (50:50) - karrooite                        */
   CP_BERMAN,  {{232.58-58.196+77.036, -7.555e2-(-1.6114e2)-5.8471e2, -56.608e5-(-14.0458e5), 
     58.214e7-11.2673e7+0.5558e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"karrooite", COMPONENT, "MgTi2O5", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                            /* Cp terms from Berman and Brown (1985) */
   {                /* ThermoRef structure                                   */
   -2507053.0,      /* H ref (J)   Kelley, Todd & King (1954)                */
   127.1936,        /* S ref (J/K) Kelley & King (1961)                      */
   5.482,           /* V ref (J/bar) From page 45 (oxide short course)       */
   CP_BERMAN,  {{232.58, -7.555e2, -56.608e5, 58.214e7, 0.0, 0.0, 0.0, 0.0}},            
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"whitlockite", PHASE, "Ca3(PO4)2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -4097169.0,              /* H ref (J)       Zhu and Sverjensky (in press) */
   235.978,                 /* S ref (J/K)        Southard and Milner (1935) */
   9.7620,                  /* V ref (J/bar)             Robie et al. (1978) */
   CP_BERMAN,  {{402.997, -28.0835E2, 0.0, -32.6230E7, 1373.0, 14059.0, 2.5427E-2, 19.255E-5}},
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"apatite", PHASE, "Ca5(PO4)3OH", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -6694689.0,              /* H ref (J)       Zhu and Sverjensky (in press) */
   398.74,                  /* S ref (J/K)     Zhu and Sverjensky (in press) */
   16.4025,                 /* V ref (J/bar)   Zhu and Sverjensky (in press) */
   CP_BERMAN,  {{758.81, -64.806E2, 0.0, 44.794E7, 0.0, 0.0, 0.0, 0.0}},                 
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"water", PHASE, "H2O", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* Calculated in GIBBS.C Berman (1988) */
   {                /* ThermoRef structure                                   */
   -54955.2356,     /* H ref (J) non-zero to allow phase inclusion in preclb */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},                               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"alloy-solid", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testAlS,         /* Pointer to testAlS  : test expected number and order  */
   conAlS,          /* Pointer to conAlS   : moles to indep comp variables   */
   actAlS,          /* Pointer to actAlS   : activities, chemical potentials */
   gmixAlS,         /* Pointer to gmixAlS  : Gibbs free energy of mixing     */
   hmixAlS,         /* Pointer to hmixAlS  : Enthaly of mixing               */
   smixAlS,         /* Pointer to smixAlS  : Entropy of mixing               */
   cpmixAlS,        /* Pointer to cpmixAlS : Heat capacity of mixing         */
   vmixAlS,         /* Pointer to vmixAlS  : Volume of mixing                */
   dispAlS          /* Pointer to dispAlS  : Formula for interface display   */
  },
  {"Fe-metal", COMPONENT, "Fe", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /*               Calculated in GIBBS.C */
   {                /* ThermoRef structure                                   */
   9999.0,          /* H ref (J) non-zero to allow phase inclusion in preclb */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},                               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"Ni-metal", COMPONENT, "Ni", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /*               Calculated in GIBBS.C */
   {                /* ThermoRef structure                                   */
   9999.0,          /* H ref (J) non-zero to allow phase inclusion in preclb */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},                               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"alloy-liquid", PHASE, "", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
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
   testAlL,         /* Pointer to testAlL  : test expected number and order  */
   conAlL,          /* Pointer to conAlL   : moles to indep comp variables   */
   actAlL,          /* Pointer to actAlL   : activities, chemical potentials */
   gmixAlL,         /* Pointer to gmixAlL  : Gibbs free energy of mixing     */
   hmixAlL,         /* Pointer to hmixAlL  : Enthaly of mixing               */
   smixAlL,         /* Pointer to smixAlL  : Entropy of mixing               */
   cpmixAlL,        /* Pointer to cpmixAlL : Heat capacity of mixing         */
   vmixAlL,         /* Pointer to vmixAlL  : Volume of mixing                */
   dispAlL          /* Pointer to dispAlL  : Formula for interface display   */
  },
  {"Fe-liquid", COMPONENT, "Fe", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /*               Calculated in GIBBS.C */
   {                /* ThermoRef structure                                   */
   9999.0,          /* H ref (J) non-zero to allow phase inclusion in preclb */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},                               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  },
  {"Ni-liquid", COMPONENT, "Ni", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /*               Calculated in GIBBS.C */
   {                /* ThermoRef structure                                   */
   9999.0,          /* H ref (J) non-zero to allow phase inclusion in preclb */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},                               
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
   }
  }
};

const int pMeltsNpc = (sizeof pMeltsSolids  / sizeof(struct _solids));

#endif /* _Sol_Struct_Data_h */
