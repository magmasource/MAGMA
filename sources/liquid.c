static const char compileDate[] = __DATE__;
static const char compileTime[] = __TIME__;
const char *liquid_ver(void) { return "$Id: liquid.c,v 1.42 2009/05/14 04:24:00 ghiorso Exp $"; }

/*
MELTS Source Code: RCS $Log: liquid.c,v $
MELTS Source Code: RCS Revision 1.30  2008/05/24 21:32:43  ghiorso
MELTS Source Code: RCS Added NaAlSiO4, KAlSiO4, and Ca(1/2)AlSiO4 species.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.29  2008/05/23 17:07:31  ghiorso
MELTS Source Code: RCS Added more hydroxyl species.
MELTS Source Code: RCS Improved preclb interface for larger number of species.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.28  2008/05/20 17:32:21  ghiorso
MELTS Source Code: RCS Added FeSiO3 and FeAlO2.5 species to balance Mg-equivalents.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.27  2008/05/03 18:16:16  ghiorso
MELTS Source Code: RCS Revised Fe2O3 and FeO1.3 EOS coefficients.
MELTS Source Code: RCS Corrected Ferric/ferrous calculation in liquid.c
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.26  2008/05/02 19:03:52  ghiorso
MELTS Source Code: RCS Revised liquid speciation model.
MELTS Source Code: RCS Created new test routine for homogeneous equilibrium fO2 at P.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.25  2008/01/06 22:35:59  ghiorso
MELTS Source Code: RCS Updated param and liq data structures to modify EOS parameters for FeO1.3
MELTS Source Code: RCS and to compute f O2 and ferric/ferrous from KC '89 + EOS integral
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.24  2007/12/22 22:43:30  ghiorso
MELTS Source Code: RCS Fixed error in BM integration in Gibbs.c
MELTS Source Code: RCS Updated param_struct_data.h file for AGU 2007 xMELTS parameters
MELTS Source Code: RCS Added support for status file production in MELTS-batch (XML)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.23  2007/11/28 01:05:37  ghiorso
MELTS Source Code: RCS Reverted back to version:
MELTS Source Code: RCS 1.21 liquid.c
MELTS Source Code: RCS 1.13 liq_struct_data.h
MELTS Source Code: RCS 1.33 param_struct_data.h
MELTS Source Code: RCS i.e. MgSiO3 and CaSiO3 species only.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.21  2007/11/23 17:47:50  ghiorso
MELTS Source Code: RCS Added the species CaSiO3.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.20  2007/11/22 04:08:13  ghiorso
MELTS Source Code: RCS Corrected infinite loop error in order() in albite.c
MELTS Source Code: RCS Removed arbitrary volume corrections in sol_struct_data.h
MELTS Source Code: RCS Turned on non-quadrilateral cpx endmembers for regression.
MELTS Source Code: RCS Added MgSiO3 species to liquid model.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.19  2007/10/18 00:33:37  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.18  2007/10/18 00:01:42  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.17  2007/10/17 16:38:20  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.16  2007/10/15 17:43:40  ghiorso
MELTS Source Code: RCS Improved convergence criteria, roundoff errors and numerical stability of
MELTS Source Code: RCS the ordering routines in liquid.c
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.15  2007/10/09 01:08:59  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.14  2007/10/06 16:47:56  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.13  2007/10/04 17:39:21  ghiorso
MELTS Source Code: RCS Relaxed convergence criteria in liquid ordering routine.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.12  2007/10/04 00:46:05  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.11  2007/10/03 21:33:48  ghiorso
MELTS Source Code: RCS Updated liquid eos thermodynamics.
MELTS Source Code: RCS Added regression of ferric/ferrous parameters from data file.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.10  2007/08/30 18:26:10  ghiorso
MELTS Source Code: RCS Revised high-pressure log fO2 calculations (buffers and liquid)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.9  2007/07/09 21:33:41  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.8  2007/06/16 01:01:55  ghiorso
MELTS Source Code: RCS Revised EOS regression to have K', K'', and K''' as parameters.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.7  2007/06/13 15:12:47  ghiorso
MELTS Source Code: RCS Revised strategy for EOS parameter fitting.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.6  2007/06/09 20:30:04  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2007/06/08 17:25:42  ghiorso
MELTS Source Code: RCS Added code to allow regression of Ghiorso EOS parameters
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2007/02/13 21:48:29  ghiorso
MELTS Source Code: RCS Modifications to read XML database files for LEPER calibration.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2006/10/20 00:59:22  ghiorso
MELTS Source Code: RCS (1) Made initial modifications for thread safe code.
MELTS Source Code: RCS (2) Added support for XML I/O in batch mode
MELTS Source Code: RCS (3) Added support for Melts-batch listener for eventual integration into VIGMCS
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2006/08/17 16:47:18  ghiorso
MELTS Source Code: RCS Made modifications to protect strings.  These modifications allow removal
MELTS Source Code: RCS of the flag -fwritable-strings during gcc compilation.  This brings the
MELTS Source Code: RCS code up to gcc 4.x standards.
MELTS Source Code: RCS
MELTS Source Code: RCS Other minor rearrangements and cleanup.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:36  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.16  2005/02/12 18:42:34  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.15  2005/02/11 03:27:10  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.14  2005/01/25 03:25:03  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.13  2005/01/24 03:38:04  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added new files and modifications to perform builds for MgO-SiO2 system
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.12  2005/01/23 20:13:27  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.11  2005/01/21 18:18:22  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added data structures and code to implement coordination number transformations
MELTS Source Code: RCS in the liquid phase EOS model.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.10  2005/01/05 17:27:26  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.9  2004/12/11 22:19:43  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.8  2004/10/03 22:40:08  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.7  2004/09/27 18:24:41  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.6  2004/09/25 19:01:50  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2004/09/24 18:26:35  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2004/09/24 02:31:21  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2004/09/23 21:18:06  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2004/09/23 20:07:04  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.11  2003/09/30 17:36:38  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.10  2003/09/27 15:35:22  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.9  2002/08/03 00:21:40  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.8  2002/07/31 20:42:27  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.7  2002/07/29 20:44:03  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.6  2002/07/26 23:55:04  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2002/07/26 01:01:37  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2002/04/10 20:39:27  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2002/04/10 00:42:21  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2002/04/06 00:51:39  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Routines to compute liquid solution properties 
**      (file: LIQUID.C)
**
**--
*/

#ifdef DEBUG
#undef DEBUG
#endif

#define USE_GHIORSO_KRESS_MODEL
#define USE_KRESS_CARMICHAEL_FO2

#include "silmin.h"
#include "recipes.h"
#include "mthread.h"
#include <signal.h>

#define SQUARE(x) ((x)*(x))
#define CUBE(x)   ((x)*(x)*(x))

#define MAX_ITER 200  /* Maximum number of iterations allowed in order */

enum {
  ERR_NONE,
  ERR_DGDR_GMAP_1,
  ERR_DGDR_GMAP_2,
  ERR_DGDT_GMAP,
  ERR_D2GDRDT_GMAP_1,
  ERR_D2GDRDT_GMAP_2,
  ERR_D3GDRDT2_GMAP_1,
  ERR_D3GDRDT2_GMAP_2,
  ERR_D2GDT2_GMAP,
  ERR_D3GDT3_GMAP,
  ERR_D2GDR2_GMAP,
  ERR_D3GDR2DT_GMAP,
  ERR_D3GDR3_GMAP,
  ERR_AB_ZERO,
  ERR_A_ZERO,
  ERR_B_ZERO,
  ERR_SUM_ZERO,
  ERR_SUM_LT_ZERO,
  ERR_SUM_GT_ZERO
};

#define printERR(name, num, description, value) \
  { fprintf(stderr, "*-->Exception in %s (%d) (file liquid.c). Bad argument to log(%s = %13.6e)\n", name, num, description, value); liqERRstate = num; return 0.0;}

/* This global variable is only accessed from preclb.  The construction here
   is not thread safe.                                                       */

int liqERRstate = ERR_NONE;

/*
 *===========================================================================
 * Backward compatible liquid functions defined in liquid_v34.c
*/

void conLiq_v34  (int inpMask, int outMask, double t, double p, double *o, double *m, double *r, double *x, double **dm, double ***dm2, double *logfo2);
int  testLiq_v34 (int mask, double t, double p, int na, int nr, char **names, char **formulas, double *r, double *m);
void dispLiq_v34 (int mask, double t, double p, double *x, char **formula);
void actLiq_v34  (int mask, double t, double p, double *x, double *a,     double *mu,   double **dx);
void gmixLiq_v34 (int mask, double t, double p, double *x, double *gmix,  double *dx,   double **dx2);
void hmixLiq_v34 (int mask, double t, double p, double *x, double *hmix);
void smixLiq_v34 (int mask, double t, double p, double *x, double *smix,  double *dx,   double **dx2);
void cpmixLiq_v34(int mask, double t, double p, double *x, double *cpmix, double *dt,   double *dx);
void vmixLiq_v34 (int mask, double t, double p, double *x, double *vmix,  double *dx,   double **dx2, double *dt, double *dp,   double *dt2,  double *dtdp, 
                                                           double *dp2,   double *dxdt, double *dxdp);
void muO2Liq_v34 (int mask, double t, double p, double *m, double *muO2,  double *dm,   double *dt,   double *dp, double **d2m, double *d2mt, double *d2mp,
                                                           double *d2t2,  double *d2tp, double *d2p2);
void visLiq_v34  (int mask, double t, double p, double *x, double *viscosity);


/*
 *=============================================================================
 * Private functions and globals:
*/

#ifdef BUILD_MGO_SIO2_VERSION
#define NA  2                    /* Number of liquid components 		          */
#define NS  1                    /* Number of ordering parameters for liquid species      */
#define NY  2                    /* Number of ordering parameters for coordination states */
static const int iOxAl2O3      = -1; /* Index of Al2O3 in bulksystem[] structure array    */
static const int iOxFe2O3      = -1; /* Index of Fe2O3 in bulksystem[] structure array    */
static const int iOxFeO        = -1; /* Index of FeO in bulksystem[] structure array      */
static const int iOxCaO        = -1; /* Index of CaO in bulksystem[] structure array      */
static const int iOxNa2O       = -1; /* Index of Na2O in bulksystem[] structure array     */
static const int iOxK2O        = -1; /* Index of K2O in bulksystem[] structure array      */
static const int iOxFeO1_3     = -1; /* Index of FeO1.3 in bulksystem[] structure array   */
static const int iCmpAl2O3     = -1; /* Index of Al2O3 in r[] array                       */
static const int iCmpFe2SiO5   = -1; /* Index of Fe2SiO5 in r[] array                     */
static const int iCmpFe2SiO4   = -1; /* Index of Fe2SiO4 in r[] array                     */
static const int iCmpFe2SiO4_6 = -1; /* Index of Fe2SiO4.6 in s[] array                   */
static const int iCmpFe2AlO4_5 = -1; /* Index of Fe2AlO4.5 in s[] array                   */
static const int iCmpFe2AlO3_5 = -1; /* Index of Fe2AlO3.5 in s[] array                   */
static const int iCmpFe2AlO4_1 = -1; /* Index of Fe2AlO4.1 in s[] array                   */
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
#define NA  6                    /* Number of liquid components 		          */
#define NS 29                    /* Number of ordering parameters for liquid species      */
#define NY  0                    /* Number of ordering parameters for coordination states */
static const int iOxAl2O3      =  1; /* Index of Al2O3 in bulksystem[] structure array    */
static const int iOxFe2O3      = -1; /* Index of Fe2O3 in bulksystem[] structure array    */
static const int iOxFeO        = -1; /* Index of FeO in bulksystem[] structure array      */
static const int iOxCaO        =  2; /* Index of CaO in bulksystem[] structure array      */
static const int iOxNa2O       =  3; /* Index of Na2O in bulksystem[] structure array     */
static const int iOxK2O        =  4; /* Index of K2O in bulksystem[] structure array      */
static const int iOxFeO1_3     = -1; /* Index of FeO1.3 in bulksystem[] structure array   */
static const int iCmpAl2O3     =  0; /* Index of Al2O3 in r[] array                       */
static const int iCmpFe2SiO5   = -1; /* Index of Fe2SiO5 in r[] array                     */
static const int iCmpFe2SiO4   = -1; /* Index of Fe2SiO4 in r[] array                     */
static const int iCmpFe2SiO4_6 = -1; /* Index of Fe2SiO4.6 in s[] array                   */
static const int iCmpFe2AlO4_5 = -1; /* Index of Fe2AlO4.5 in s[] array                   */
static const int iCmpFe2AlO3_5 = -1; /* Index of Fe2AlO3.5 in s[] array                   */
static const int iCmpFe2AlO4_1 = -1; /* Index of Fe2AlO4.1 in s[] array                   */
#else
#define NA 19                    /* Number of liquid components 		          */
#define NS 23                    /* Number of ordering parameters for liquid species      */
#define NY  0                    /* Number of ordering parameters for coordination states */
static const int iOxAl2O3      =  2; /* Index of Al2O3 in bulksystem[] structure array    */
static const int iOxFe2O3      =  3; /* Index of Fe2O3 in bulksystem[] structure array    */
static const int iOxFeO        =  5; /* Index of FeO in bulksystem[] structure array      */
static const int iOxCaO        = 10; /* Index of CaO in bulksystem[] structure array      */
static const int iOxNa2O       = 11; /* Index of Na2O in bulksystem[] structure array     */
static const int iOxK2O        = 12; /* Index of K2O in bulksystem[] structure array      */
static const int iOxFeO1_3     = 19; /* Index of FeO1.3 in bulksystem[] structure array   */
static const int iCmpAl2O3     =  1; /* Index of Al2O3 in r[] array                       */
static const int iCmpFe2SiO5   =  2; /* Index of Fe2SiO5 in r[] array                     */
static const int iCmpFe2SiO4   =  4; /* Index of Fe2SiO4 in r[] array                     */
static const int iCmpFe2SiO4_6 =  0; /* Index of Fe2SiO4.6 in s[] array                   */
static const int iCmpFe2AlO4_5 =  3; /* Index of Fe2AlO4.5 in s[] array                   */
static const int iCmpFe2AlO3_5 =  4; /* Index of Fe2AlO3.5 in s[] array                   */
static const int iCmpFe2AlO4_1 =  9; /* Index of Fe2AlO4.1 in s[] array                   */
#endif

#define NT (NS+NY)               /* Number of ordering parameters                         */
#define NR (NA-1)                /* Number of independent mole fraction variables         */
#define NW ((NA+NS)*(NA+NS-1)/2) /* Number of regular solution interaction parameters     */
#define NV (NR+NS)               /* Number of independent variables in the model          */
#define NP (NA+NS+NW)            /* Number of model parameters  		          */

/* The statics from here to ... */

static int convergedInOrder;
static int eosIntegralBranch;
#define GMAPeosBRANCH 1
#define LMAPeosBRANCH 2
static double eosIntDGDS[NS];

static double *dgdr, *dgds, *dgdw;
static double **d2gdr2, **d2gdrds, *d2gdrdt, *d2gdrdp, **d2gdrdw, **d2gds2, *d2gdsdt, *d2gdsdp, **d2gdsdw, *d2gdtdw, *d2gdpdw; 
static double ***d3gdr3, ***d3gdr2ds, **d3gdr2dt, **d3gdr2dp, ***d3gdrds2,**d3gdrdsdt, **d3gdrdsdp, *d3gdrdt2, *d3gdrdtdp, *d3gdrdp2, 
              ***d3gds3, **d3gds2dt, **d3gds2dp, *d3gdsdt2, *d3gdsdtdp, *d3gdsdp2, ***d3gds2dw, **d3gdrdtdw, ***d3gdrdsdw, **d3gdsdtdw; 

static double *xSpecies;         /* Mole fractions of endmember species                                                  */
static double **dxSpeciesdr;     /* d(xSpecies)/dr                                                                       */
static double **dxSpeciesds;     /* d(xSpecies)/ds                                                                       */
static double ***d2xSpeciesdrds; /* d2(xSpecies)/drds                                                                    */
static double nSpecies;          /* Total moles of all solution species relative to 1 mole of basis species              */
static double *dnSpeciesds;      /* d(nSpecies)/ds                                                                       */
static double **d2nSpeciesds2;   /* d2(nSpecies)/ds2                                                                     */
static double ***d3nSpeciesds3;  /* d3(nSpecies)/ds3                                                                     */

static MTHREAD_MUTEX_T global_data_mutex = MTHREAD_MUTEX_INITIALIZER;

/* ... here are dealt with by creating a mutex lock on the code that requires access to these quantities */

/***********************************************/
/* Statics for class initialization structures */
/***********************************************/

static MTHREAD_ONCE_T initThreadBlock = MTHREAD_ONCE_INIT;

static void initializeLiquid(void);

static void threadInit(void) {
  initializeLiquid();
}

/* The statics from here ... */

static int NE;   /* Number of liquid endmembers (species) */
static int nH2O;

static double Gconst,       *gr,       *gs,       **grr,        **grs,       **gss;
static double Hconst,       *hr,       *hs,       **hrr,        **hrs,       **hss;
static double Sconst,       *sr,       *ss,       **srr,        **srs,       **sss;
static double Vconst,       *vr,       *vs,       **vrr,        **vrs,       **vss;
static double CPconst,      *cpr,      *cps;
static double DCPDTconst,   *dcpdtr,   *dcpdts;
static double DVDTconst,    *dvdtr,    *dvdts;
static double DVDPconst,    *dvdpr,    *dvdps;
static double D2VDT2const,  *d2vdt2r,  *d2vdt2s;
static double D2VDTDPconst, *d2vdtdpr, *d2vdtdps;
static double D2VDP2const,  *d2vdp2r,  *d2vdp2s;

static double **taylorCoeff;  /* Taylor Expansion coefficients: [endmember species | W(i,j)][g0, gr, gs, grr, grs, gss] */
static double **rsEndmembers; /* r and s coefficients for species endmembers                                            */

/* ... to here are set in initializeLiquid() */

static void initializeTaylor(double *array) {
  int i;
  for (i=0; i<NP; i++) array[i] = 0.0;
}

static void loadTaylor(double *array, double coeff, double *p) {
  int i, j, n;

  array[0] += coeff;
  for (i=0, n=1; i<NV; i++, n++) if (p[i] != 0.0) array[n] += coeff*p[i];
  for (i=0; i<NV; i++) for (j=i; j<NV; j++, n++) 
    if (p[i] != 0.0 && p[j] != 0.0) array[n] += coeff*p[i]*p[j];
}

static void initializeLiquid(void) {
  int i, j, k, n, contentsOK;
  double **mTaylor, **vTaylor, *wTaylor, *bTaylor, *temp, *coeff; 
  char *eTaylor;
  FILE *tcFILE;
#ifdef BUILD_MGO_SIO2_VERSION
  const char *tcFILEname = "liquid-model-ms.inp";
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
  const char *tcFILEname = "liquid-model-sacnk.inp";
#else
#ifdef BATCH_VERSION
  const char *tcFILEname = "liquid-model-batch.inp";
#else
  const char *tcFILEname = "liquid-model.inp";
#endif /* BATCH_VERSION */
#endif /* BUILD_MGO_SIO2_VERSION */

#ifdef DEBUG
  printf("Entering function initializeLiquid...\n");
#endif

  /* Initialize global constants */
  NE = nls; /* Number of liquid endmembers (species) */
  if ( (NE == 0) || (NA != nlc) || (NS != (nls-nlc)) ) {
    if (NE == 0)         printf("Error in initializeLiquid() [liquid.c].  Number of species is zero.\n");
    if (NA != nlc)       printf("Error in initializeLiquid() [liquid.c].  Constant NA is not equal to nlc (%d).\n", nlc);
    if (NS != (nls-nlc)) printf("Error in initializeLiquid() [liquid.c].  Constant NS is not equal to nls-nlc (%d).\n", nls-nlc);
    exit(0);
  }
    
  nH2O = -1;
  for (i=0; i<NE; i++) if ((strcmp(liquid[i].label, "H2O-OH") == 0) || (strcmp(liquid[i].label, "h2o-oh") == 0)) { nH2O = i; break; }
  
  /* Static global storage for endmember species mole fractions */
  xSpecies       = vector(0, NE-1);
  dxSpeciesdr    = matrix(0, NE-1, 0, NR-1);
  dxSpeciesds    = matrix(0, NE-1, 0, NS-1);
  d2xSpeciesdrds = (double ***) malloc((size_t) NE*sizeof(double **));
                   for (i=0; i<NE; i++) d2xSpeciesdrds[i] = matrix(0, NR-1, 0, NS-1);
  dnSpeciesds    = vector(0, NS-1);
  d2nSpeciesds2  = matrix(0, NS-1, 0, NS-1);
  d3nSpeciesds3  = (double ***) malloc((size_t) NS*sizeof(double **));
                   for (i=0; i<NS; i++) d3nSpeciesds3[i] = matrix(0, NS-1, 0, NS-1);
 
  /* Allocate static storage for the derivatives of g */
  dgdr      = vector(0, NR-1); 
  dgds      = vector(0, NT-1); 
  dgdw      = vector(0, 3*NP-1); 
  d2gdr2    = matrix(0, NR-1, 0, NR-1); 
  d2gdrds   = matrix(0, NR-1, 0, NT-1); 
  d2gdrdt   = vector(0, NR-1); 
  d2gdrdp   = vector(0, NR-1); 
  d2gdrdw   = matrix(0, NR-1, 0, 3*NP-1); 
  d2gds2    = matrix(0, NT-1, 0, NT-1);
  d2gdsdt   = vector(0, NT-1); 
  d2gdsdp   = vector(0, NT-1);
  d2gdsdw   = matrix(0, NT-1, 0, 3*NP-1); 
  d2gdtdw   = vector(0, 3*NP-1); 
  d2gdpdw   = vector(0, 3*NP-1); 
  d3gdr3    = (double ***) malloc ((size_t) NR*sizeof(double **));
              for (i=0; i<NR; i++) d3gdr3[i] = matrix(0, NR-1, 0, NR-1);
  d3gdr2ds  = (double ***) malloc ((size_t) NR*sizeof(double **));
              for (i=0; i<NR; i++) d3gdr2ds[i] = matrix(0, NR-1, 0, NT-1); 
  d3gdr2dt  = matrix(0, NR-1, 0, NR-1); 
  d3gdr2dp  = matrix(0, NR-1, 0, NR-1); 
  d3gdrdt2  = vector(0, NR-1); 
  d3gdrdtdp = vector(0, NR-1); 
  d3gdrdp2  = vector(0, NR-1);
  d3gdrds2  = (double ***) malloc ((size_t) NR*sizeof(double **));
              for (i=0; i<NR; i++) d3gdrds2[i] = matrix(0, NT-1, 0, NT-1);
  d3gdrdsdt = matrix(0, NR-1, 0, NT-1); 
  d3gdrdsdp = matrix(0, NR-1, 0, NT-1); 
  d3gds3    = (double ***) malloc ((size_t) NT*sizeof(double **));
              for (i=0; i<NT; i++) d3gds3[i] = matrix(0, NT-1, 0, NT-1); 
  d3gds2dt  = matrix(0, NT-1, 0, NT-1); 
  d3gds2dp  = matrix(0, NT-1, 0, NT-1); 
  d3gdsdt2  = vector(0, NT-1);
  d3gdsdtdp = vector(0, NT-1); 
  d3gdsdp2  = vector(0, NT-1);
  d3gdrdtdw = matrix(0, NR-1, 0, 3*NP-1); 
  d3gdsdtdw = matrix(0, NT-1, 0, 3*NP-1);
  d3gds2dw  = (double ***) malloc ((size_t) NT*sizeof(double **));
              for (i=0; i<NT; i++) d3gds2dw[i] = matrix(0, NT-1, 0, 3*NP-1);
  d3gdrdsdw = (double ***) malloc ((size_t) NR*sizeof(double **));
              for (i=0; i<NR; i++) d3gdrdsdw[i] = matrix(0, NT-1, 0, 3*NP-1);
  
	 gr = vector(0, NR-1);		 
         gs = vector(0, NS-1);
        grr = matrix(0, NR-1, 0, NR-1);	 
        grs = matrix(0, NR-1, 0, NS-1);	    
        gss = matrix(0, NS-1, 0, NS-1);
	 hr = vector(0, NR-1);		 
	 hs = vector(0, NS-1);    
        hrr = matrix(0, NR-1, 0, NR-1);	 
        hrs = matrix(0, NR-1, 0, NS-1);	    
        hss = matrix(0, NS-1, 0, NS-1);
	 sr = vector(0, NR-1);		 
	 ss = vector(0, NS-1);   
        srr = matrix(0, NR-1, 0, NR-1);	 
        srs = matrix(0, NR-1, 0, NS-1);	    
        sss = matrix(0, NS-1, 0, NS-1);
	 vr = vector(0, NR-1);		 
	 vs = vector(0, NS-1);       
        vrr = matrix(0, NR-1, 0, NR-1);	 
        vrs = matrix(0, NR-1, 0, NS-1);	    
        vss = matrix(0, NS-1, 0, NS-1);
	cpr = vector(0, NR-1);		
	cps = vector(0, NS-1);       
     dcpdtr = vector(0, NR-1);	     
     dcpdts = vector(0, NS-1);       
      dvdtr = vector(0, NR-1);	      
      dvdts = vector(0, NS-1); 
      dvdpr = vector(0, NR-1);	      
      dvdps = vector(0, NS-1); 
    d2vdt2r = vector(0, NR-1);	    
    d2vdt2s = vector(0, NS-1); 
   d2vdtdpr = vector(0, NR-1);	   
   d2vdtdps = vector(0, NS-1); 
    d2vdp2r = vector(0, NR-1);    
    d2vdp2s = vector(0, NS-1); 
  
#ifdef DEBUG
  printf("...Constructing r,s --> Endmember species matrix.\n");
#endif
  /* r and s coefficients for endmember species */
  rsEndmembers = matrix (0, NE-1, 0, NV-1);
  coeff        = vector (0, NE-1);
  for (i=0; i<NE; i++) for (j=0; j<NV; j++) rsEndmembers[i][j] = 0.0;
  for (i=0; i<NA; i++) coeff[i] = 1.0;
  /* --> basis species     */
  for (i=1; i<NA; i++) rsEndmembers[i][i-1] = 1.0;
  /* --> dependent species */
  for (i=NA; i<NE; i++) {
    for (k=0, coeff[i]=0.0; k<nc; k++) coeff[i] += (bulkSystem[k].oxToLiq)[0]*(liquid[i].liqToOx)[k];
    for (j=1; j<NA; j++) for (k=0, rsEndmembers[i][j-1]=0.0; k<nc; k++) 
      rsEndmembers[i][j-1] += (bulkSystem[k].oxToLiq)[j]*(liquid[i].liqToOx)[k];
    for (j=0; j<NR; j++) coeff[i] += rsEndmembers[i][j];
    if (coeff[i] != 0.0) for (j=0; j<NR; j++) rsEndmembers[i][j] /= coeff[i];
    rsEndmembers[i][i-NA+NR] = 1.0;  /* ordering parameter */
  }
#ifdef DEBUG
  printf("...rsEndmembers matrix:\n");
  for (i=0; i<NE; i++) {
    printf("coeff[%-15.15s] = %10.4f\n", liquid[i].label, coeff[i]);
    for (j=0; j<NV; j++) printf("%4.1f ", rsEndmembers[i][j]);
    printf("\n");
  }
#endif
  
#ifdef DEBUG
  printf("...Zeroing dxdr, dxds, and d2xdrds matrices.\n");
#endif
  for (i=0; i<NE; i++) {
    for (j=0; j<NR; j++) {
      dxSpeciesdr[i][j] = 0.0;
      for (k=0; k<NS; k++) d2xSpeciesdrds[i][j][k] = 0.0;
    }
    for (j=0; j<NS; j++) dxSpeciesds[i][j] = 0.0;
  }

  /********************************************
   * Create the liquid model Taylor expansion *
   ********************************************/
 
  if ((tcFILE = fopen(tcFILEname, "r")) != NULL) {
    char buffer[140];
    contentsOK = 1;
    if (contentsOK && (fgets(buffer, 140, tcFILE) == NULL))                     contentsOK = 0;
    if (contentsOK && (strncmp(buffer, compileDate, strlen(compileDate)) != 0)) contentsOK = 0;
    if (contentsOK && (fgets(buffer, 140, tcFILE) == NULL))                     contentsOK = 0;  
    if (contentsOK && (strncmp(buffer, compileTime, strlen(compileTime)) != 0)) contentsOK = 0;   
    if (contentsOK) {
      taylorCoeff = matrix (1, NP, 1, NP);
      for (i=1; i<=NP; i++) for (j=1; j<=NP; j++) {
        if (fgets(buffer, 140, tcFILE) == NULL) { printf("Fatal error in taylor coefficient file on reading.\n"); exit(0); }
	buffer[strlen(buffer)-1] = '\0';
        taylorCoeff[i][j] = atof(buffer);
      }
    }      
    fclose(tcFILE);
  } else contentsOK = 0;
  
  if (!contentsOK) {

#ifdef DEBUG
    printf("...Constructing Taylor expansion coefficients of liquid model.\n");
#endif
    n = 0;
    mTaylor = matrix (1, NP, 1, NP);

    /* First-order Taylor terms */
    for (i=0; i<NE; i++) {
      n++; initializeTaylor (&mTaylor[n][1]);
      loadTaylor (&mTaylor[n][1], coeff[i], &rsEndmembers[i][0]);
    }

    /* Second-order Taylor terms: binary interaction parameters
       join A-B ==>  4 ( G(A/2+B/2) - G(A)/2 - G(B)/2 ) 	   */
    temp = vector(0, NE-1);
    for (i=0; i<NE; i++) {
      for (j=i+1; j<NE; j++) {
  	for (k=0; k<NV; k++) temp[k] = (rsEndmembers[i][k] + rsEndmembers[j][k])/2.0;
  	n++; initializeTaylor (&mTaylor[n][1]);
  	loadTaylor (&mTaylor[n][1], (double)  4.0, temp);
  	loadTaylor (&mTaylor[n][1], (double) -2.0, &rsEndmembers[i][0]);
  	loadTaylor (&mTaylor[n][1], (double) -2.0, &rsEndmembers[j][0]);
      }
    }
    free_vector(temp,  0, NE-1);
    free_vector(coeff, 0, NE-1);

    /* Fill in uninitialized entries */
    for (i=n+1; i<=NP; i++) initializeTaylor (&mTaylor[i][1]);

    vTaylor	= matrix (1, NP, 1, NP);
    wTaylor	= vector (1, NP);
    bTaylor	= vector (1, NP);
    taylorCoeff = matrix (1, NP, 1, NP);
    eTaylor	= (char *) malloc ((unsigned) (NP+1)*sizeof(char));
    for (i=1; i<=NP; i++) eTaylor[i] = '1';

#ifdef DEBUG
    printf("...Performing singular value analysis of coefficient matrix...\n");
#endif
    svdcmp(mTaylor, NP, NP, wTaylor, vTaylor);
    for (i=1, j=0; i<=NP; i++) if (fabs(wTaylor[i]) < DBL_EPSILON) { wTaylor[i] = 0.0; j++; }
#ifdef DEBUG
    if (NP-j < n) printf("...Problem is rank deficient! rank = %d\n", NP-j);
    printf("...Performing back-substitution phase...\n");
#endif
    for (i=1; i<=NP; i++) {
      for (j=1; j<=NP; j++) bTaylor[j] = (i == j) ? 1.0 : 0.0;
      svbksb(mTaylor, wTaylor, vTaylor, NP, NP, bTaylor, eTaylor, taylorCoeff[i]);
    }
    
    tcFILE = fopen(tcFILEname, "w");
    fprintf(tcFILE, "%s\n", compileDate);
    fprintf(tcFILE, "%s\n", compileTime);

    for (i=1; i<=NP; i++) for (j=1; j<=NP; j++) {
      if (fabs(taylorCoeff[i][j]) < sqrt(DBL_EPSILON)) taylorCoeff[i][j] = 0.0;
      fprintf(tcFILE, "%20.13g\n", taylorCoeff[i][j]);
    }
    
    fclose(tcFILE);
 
    free_matrix(mTaylor,   1, NP, 1, NP);
    free_matrix(vTaylor,   1, NP, 1, NP);
    free_vector(wTaylor,   1, NP);
    free_vector(bTaylor,   1, NP);
    free(eTaylor);
  }
  
#ifdef DEBUG
  printf("...Exiting function initializeLiquid.\n");
#endif
}

#ifdef BUILD_MGO_SIO2_VERSION
static int rANDsTOx (double r[NR], double s[NT]) {
  static double tolerance;
  double rSum, coeff, dcoeffds[NS], denom, dDenomds[NS];
  int i, j, k, okay = TRUE;
  
  for (i=0, rSum=0.0; i<NR; i++) rSum += r[i];
  
  coeff       = 1.0;  
  dcoeffds[0] = 0.0; 

  /* xSpecies */
  xSpecies[ 0] = 1.0 - rSum*coeff;                   /* SiO2  */
  for (i=0; i<NR; i++) xSpecies[ i+1] = r[i]*coeff;  /* basis */
  for (i=0; i<NS; i++) xSpecies[NA+i] = s[i];        /* depen */
  
  xSpecies[0] += - s[0]/2.0; /* special case SiO2  */
  xSpecies[1] += - s[0]/2.0; /* special case MgO   */
  
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
  /* for (i=0; i<(NA+NS); i++) if (fabs(xSpecies[i]) < tolerance) xSpecies[i] = 0.0; */

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
  
  dxSpeciesds[0][0] += - 1.0/2.0; /* special case SiO2 */
  dxSpeciesds[1][0] += - 1.0/2.0; /* special case MgO  */
   
  /* d2 xSpecies / dr ds */
  for (i=0; i<NR; i++) {
    for (j=0; j<NS; j++) {
      d2xSpeciesdrds[  0][i][j] = -dcoeffds[j];  /* SiO2  */
      d2xSpeciesdrds[i+1][i][j] =  dcoeffds[j];  /* other */
    }
  }
  
  /* Total moles of species relative to 1 mole of basis components */
  denom = 4.0;        /* Special case */
  
  dDenomds[0] = 0.0; /* MgSiO3    */

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

#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
static int rANDsTOx (double r[NR], double s[NT]) {
  static int firstTime = TRUE;
  double rSum;
  int i, j, k, okay = TRUE;
  
  for (i=0, rSum=0.0; i<NR; i++) rSum += r[i];
  
  /* xSpecies */
  xSpecies[ 0] = 1.0 - rSum;                  /* SiO2  */
  for (i=0; i<NR; i++) xSpecies[ i+1] = r[i]; /* basis */
  for (i=0; i<NS; i++) xSpecies[NA+i] = s[i]; /* depen */
  
  xSpecies[0] +=   s[0]/6.0 - s[1]/3.0 - s[2]/6.0 -3.0*s[3]/10.0 
                 - 7.0*s[4]/12.0 - s[5]/5.0 + s[7]/6.0 + s[9]/4.0 - s[10]/3.0 + s[12]/4.0  
		 - s[13]/2.0 - s[14]/4.0 - s[15]/2.0 - s[16]/5.0 - s[17]/4.0 
		 - s[18]/5.0 - 2.0*s[19]/3.0 - s[20]/7.0 - s[21]/7.0 - 2.0*s[22]/3.0
		 - s[23]/8.0 - 3.0*s[24]/8.0 - 3.0*s[25]/7.0 - 7.0*s[26]/11.0
		 - 3.0*s[27]/10.0 - s[28]/2.0;                                           /* special case SiO2    x 2   */
  xSpecies[1] += - 2.0*s[0]/3.0 - s[1]/3.0 - s[2]/3.0 - 2.0*s[3]/5.0 - s[4]/6.0
                 - s[6]/4.0 - s[11]/2.0 - s[12]/2.0 - s[16]/5.0 - 3.0*s[17]/4.0
		 - 2.0*s[20]/7.0 - 4.0*s[21]/7.0 - s[22]/6.0 - s[23]/2.0 - s[24]/4.0
		 - s[25]/7.0 - s[26]/11.0 - 2.0*s[27]/5.0 - 2.0*s[28]/7.0;              /* special case Al2O3         */
  xSpecies[2] += - s[0]/2.0 - 3.0*s[3]/10.0 - s[7]/2.0;                                 /* special case Ca2SiO4 x 2/3 */
  xSpecies[3] += - s[1]/3.0 - s[8]/2.0 - 2.0*s[10]/3.0 - s[11]/2.0 - s[13]/2.0
                 - 4.0*s[18]/5.0 - s[19]/3.0 - 4.0*s[20]/7.0 - 2.0*s[21]/7.0 
		 - s[22]/6.0;                                                           /* special case Na2O          */
  xSpecies[4] += - s[2]/2.0 - s[4]/4.0 - 3.0*s[9]/4.0 - 3.0*s[12]/4.0
                 - 3.0*s[14]/4.0 - s[15]/2.0 - 3.0*s[16]/5.0 - 3.0*s[23]/8.0 
		 - 3.0*s[24]/8.0 - 3.0*s[25]/7.0 - 3.0*s[26]/11.0 - 3.0*s[27]/10.0
		 - 3.0*s[28]/14.0;                                                      /* special case K2SiO3  x 2/3 */
  xSpecies[5] += - 4.0*s[5]/5.0 - 3.0*s[6]/4.0 - 2.0*s[7]/3.0 - s[8]/2.0 -s[9]/2.0;     /* special case H2O           */
  
  /* d xSpecies / dr */
  for (i=0; i<NR; i++) { 
    dxSpeciesdr[  0][i] = - 1.0;  /* SiO2  */
    dxSpeciesdr[i+1][i] =   1.0;  /* other */
  }

  /* d xSpecies / ds */
  for (i=0; i<NS; i++) {
                         dxSpeciesds[   0][i] = 0.0; /* SiO2  */
    for (j=0; j<NR; j++) dxSpeciesds[ j+1][i] = 0.0; /* basis */
                         dxSpeciesds[NA+i][i] = 1.0; /* depen */
  }
  
  dxSpeciesds[0][ 0] +=    1.0/6.0;  dxSpeciesds[0][ 1] += -  1.0/3.0;  /* special case SiO2 x 2 */
  dxSpeciesds[0][ 2] += -  1.0/6.0;  dxSpeciesds[0][ 3] += -  3.0/10.0;
  dxSpeciesds[0][ 4] += -  7.0/12.0; dxSpeciesds[0][ 5] += -  1.0/5.0;  
  dxSpeciesds[0][ 7] +=    1.0/6.0;  dxSpeciesds[0][ 9] +=    1.0/4.0;  
  dxSpeciesds[0][10] += -  1.0/3.0;  dxSpeciesds[0][12] +=    1.0/4.0;  
  dxSpeciesds[0][13] += -  1.0/2.0;  dxSpeciesds[0][14] += -  1.0/4.0;  
  dxSpeciesds[0][15] += -  1.0/2.0;  dxSpeciesds[0][16] += -  1.0/5.0;
  dxSpeciesds[0][17] += -  1.0/4.0;  dxSpeciesds[0][18] += -  1.0/5.0;
  dxSpeciesds[0][19] += -  2.0/3.0;  dxSpeciesds[0][20] += -  1.0/7.0;  
  dxSpeciesds[0][21] += -  1.0/7.0;  dxSpeciesds[0][22] += -  2.0/3.0; 
  dxSpeciesds[0][23] += -  1.0/8.0;  dxSpeciesds[0][24] += -  3.0/8.0; 
  dxSpeciesds[0][25] += -  3.0/7.0;  dxSpeciesds[0][26] += -  7.0/11.0; 
  dxSpeciesds[0][27] += -  3.0/10.0; dxSpeciesds[0][28] += -  1.0/2.0; 
  
  dxSpeciesds[1][ 0] += -  2.0/3.0;  dxSpeciesds[1][ 1] += -  1.0/3.0;  /* special case Al2O3 */
  dxSpeciesds[1][ 2] += -  1.0/3.0;  dxSpeciesds[1][ 3] += -  2.0/5.0;
  dxSpeciesds[1][ 4] += -  1.0/6.0;  dxSpeciesds[1][ 6] += -  1.0/4.0;  
  dxSpeciesds[1][11] += -  1.0/2.0;  dxSpeciesds[1][12] += -  1.0/2.0;    
  dxSpeciesds[1][16] += -  1.0/5.0;  dxSpeciesds[1][17] += -  3.0/4.0; 
  dxSpeciesds[1][20] += -  2.0/7.0;  dxSpeciesds[1][21] += -  4.0/7.0;
  dxSpeciesds[1][22] += -  1.0/6.0;  dxSpeciesds[1][23] += -  1.0/2.0;
  dxSpeciesds[1][24] += -  1.0/4.0;  dxSpeciesds[1][25] += -  1.0/7.0;
  dxSpeciesds[1][26] += -  1.0/11.0; dxSpeciesds[1][27] += -  2.0/5.0;
  dxSpeciesds[1][28] += -  2.0/7.0;
  
  dxSpeciesds[2][ 0] += -  1.0/2.0;  dxSpeciesds[2][ 3] += -  3.0/10.0; /* special case Ca2SiO4 x 2/3 */
  dxSpeciesds[2][ 7] += -  1.0/2.0;
  
  dxSpeciesds[3][ 1] += -  1.0/3.0;  dxSpeciesds[3][ 8] += -  1.0/2.0;  /* special case Na2O */
  dxSpeciesds[3][10] += -  2.0/3.0;  dxSpeciesds[3][11] += -  1.0/2.0;  
  dxSpeciesds[3][13] += -  1.0/2.0;  dxSpeciesds[3][18] += -  4.0/5.0;
  dxSpeciesds[3][19] += -  1.0/3.0;  dxSpeciesds[3][20] += -  4.0/7.0;
  dxSpeciesds[3][21] += -  2.0/7.0;  dxSpeciesds[3][22] += -  1.0/6.0;
  
  dxSpeciesds[4][ 2] += -  1.0/2.0;  dxSpeciesds[4][ 4] += -  1.0/4.0;  /* special case K2SiO3 x 2/3 */
  dxSpeciesds[4][ 9] += -  3.0/4.0;  dxSpeciesds[4][12] += -  3.0/4.0;
  dxSpeciesds[4][14] += -  3.0/4.0;  dxSpeciesds[4][15] += -  1.0/2.0;
  dxSpeciesds[4][16] += -  3.0/5.0;  dxSpeciesds[4][23] += -  3.0/8.0;
  dxSpeciesds[4][24] += -  3.0/8.0;  dxSpeciesds[4][25] += -  3.0/7.0;
  dxSpeciesds[4][26] += -  3.0/11.0; dxSpeciesds[4][27] += -  3.0/10.0;
  dxSpeciesds[4][28] += -  3.0/14.0;
  
  dxSpeciesds[5][ 5] += -  4.0/5.0;  dxSpeciesds[5][ 6] += -  3.0/4.0; /* special case H2O     */
  dxSpeciesds[5][ 7] += -  2.0/3.0;  dxSpeciesds[5][ 8] += -  1.0/2.0;
  dxSpeciesds[5][ 9] += -  1.0/2.0;
  
  if (firstTime) {
    /* d2 xSpecies / dr ds */
    for (i=0; i<NR; i++) {
      for (j=0; j<NS; j++) {
        d2xSpeciesdrds[  0][i][j] = 0.0;  /* SiO2 x 2 */
        d2xSpeciesdrds[i+1][i][j] = 0.0;  /* other    */
      }
    }
    nSpecies = 1.0;
    for (i=0; i<NS; i++) dnSpeciesds[i] = 0.0;
    for (i=0; i<NS; i++) for (j=0; j<NS; j++) d2nSpeciesds2[i][j] = 0.0;
    for (i=0; i<NS; i++) for (j=0; j<NS; j++) for (k=0; k<NS; k++) d3nSpeciesds3[i][j][k] = 0.0;
    firstTime = FALSE;
  }

  /* Catch bad input data */
  for (i=0;  i<NE; i++) okay &= (xSpecies[i] >= 0.0);
  if (!okay) return okay;

  /*for (i=NS; i<NT; i++) okay &= ((s[i] > (10.0*DBL_EPSILON)) && (s[i] < (1.0-10.0*DBL_EPSILON))); */
  for (i=NS; i<NT; i++) okay &= ((s[i] > DBL_MIN) && (s[i] < (1.0-10.0*DBL_EPSILON)));
  if (okay && (NT > NS)) {
    double yIV = 1.0;
    for (i=NS; i<NT; i++) yIV -= s[i];
    okay &= ((yIV > (10.0*DBL_EPSILON)) && (yIV < (1.0-10.0*DBL_EPSILON)));
  }
  if (!okay) return okay;
  
  return okay;
}

#else /* ! BUILD_MGO_SIO2_VERSION */

static int rANDsTOx (double r[NR], double s[NT]) {
  static double tolerance;
  double rSum, coeff, dcoeffds[NS], denom, dDenomds[NS];
  int i, j, k, okay = TRUE;
  const double y = 0.3; /* Fe2SiO(4+2*0.3) or Fe2AlO(3.5+2*0.3) */
  
  for (i=0, rSum=0.0; i<NR; i++) rSum += r[i];
  
  coeff = 1.0 - s[ 1]/4.0 - s[ 3]/2.0 - s[ 4]/2.0 - s[ 5]/2.0 - s[ 6]/2.0 
              - s[ 7]/2.0 - s[ 8]/2.0 - s[ 9]/2.0 - s[10]/3.0 - s[11]/2.0
	      - s[13]/2.0 - s[14]/2.0 - s[15]/2.0 - s[16]/2.0 - s[17]/2.0
	      - s[18]/2.0 - s[19]/2.0 + s[20]/2.0 + s[21]/2.0 + s[22]/2.0;
  
  dcoeffds[ 0] =      0.0; 
  dcoeffds[ 1] = -1.0/4.0; 
  dcoeffds[ 2] =      0.0; 
  dcoeffds[ 3] = -1.0/2.0; 
  dcoeffds[ 4] = -1.0/2.0; 
  dcoeffds[ 5] = -1.0/2.0; 
  dcoeffds[ 6] = -1.0/2.0; 
  dcoeffds[ 7] = -1.0/2.0; 
  dcoeffds[ 8] = -1.0/2.0; 
  dcoeffds[ 9] = -1.0/2.0; 
  dcoeffds[10] = -1.0/3.0; 
  dcoeffds[11] = -1.0/2.0; 
  dcoeffds[12] =      0.0; 
  dcoeffds[13] = -1.0/2.0; 
  dcoeffds[14] = -1.0/2.0; 
  dcoeffds[15] = -1.0/2.0; 
  dcoeffds[16] = -1.0/2.0; 
  dcoeffds[17] = -1.0/2.0; 
  dcoeffds[18] = -1.0/2.0; 
  dcoeffds[19] = -1.0/2.0; 
  dcoeffds[20] =  1.0/2.0; 
  dcoeffds[21] =  1.0/2.0; 
  dcoeffds[22] =  1.0/2.0; 

  /* xSpecies */
  xSpecies[ 0] = 1.0 - rSum*coeff;                   /* SiO2  */
  for (i=0; i<NR; i++) xSpecies[ i+1] = r[i]*coeff;  /* basis */
  for (i=0; i<NS; i++) xSpecies[NA+i] = s[i];        /* depen */
  
  xSpecies[ 0] += - s[ 1]/2.0 - s[ 2]/2.0 + s[ 3]/2.0 + s[ 4]/2.0  /* special case SiO2    */ 
                  + s[ 5]/2.0 + s[ 6]/2.0 + s[ 7]/2.0 + s[ 8]/2.0 
		  + s[ 9]/2.0 - s[10]/3.0 - s[12]/2.0 - s[14]/3.0
		  - s[15]/4.0 - s[16]/4.0 - s[17]/4.0 - s[22]/4.0;           
  xSpecies[ 2] += - s[ 3]/2.0 - s[ 4]/2.0 - s[ 5]/2.0              /* special case Al2O3   */
                  - s[ 6]/2.0 - s[ 7]/2.0 - s[ 8]/2.0 
		  - s[ 9]/2.0 - s[10]/6.0 - s[11]/2.0 
		  - s[13]/2.0 - s[20]/2.0 - s[21]/2.0 - s[22]/2.0;  
  xSpecies[ 3] += - 2.0*y*s[0] - s[3] - 2.0*y*s[9] - s[14]/6.0;    /* special case Fe2O3   */  
  xSpecies[ 5] +=  (2.0*y-1.0)*s[0] -s[4] + (2.0*y-1.0)*s[9]       /* special case Fe2SiO4 */ 
                  - s[12]/2.0 - s[13]/2.0 - s[15]/4.0;
  xSpecies[ 7] += - s[2]/2.0 - s[5] -s[11]/2.0 - s[16]/4.0;        /* special case Mg2SiO4 */  
  xSpecies[10] += - s[6] - s[17]/4.0 - s[22]/4.0;             	   /* special case Ca2SiO4 */
  xSpecies[11] += - s[7] - s[18]/2.0 - s[20]/2.0;             	   /* special case Na2SiO3 */
  xSpecies[12] += - s[8] - s[19]/2.0 - s[21]/2.0;             	   /* special case K2SiO3  */  
  xSpecies[18] += - s[ 1]/2.0 - s[10]/2.0 - s[14]/2.0 - s[15]/2.0  /* special case H2O     */
                  - s[16]/2.0 - s[17]/2.0 - s[18]/2.0 - s[19]/2.0;
  
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
  
  dxSpeciesds[ 0][ 1] += - 1.0/2.0;     dxSpeciesds[ 0][ 2] += - 1.0/2.0; /* special case SiO2    */
  dxSpeciesds[ 0][ 3] +=   1.0/2.0;     dxSpeciesds[ 0][ 4] +=   1.0/2.0;     
  dxSpeciesds[ 0][ 5] +=   1.0/2.0;     dxSpeciesds[ 0][ 6] +=   1.0/2.0;     
  dxSpeciesds[ 0][ 7] +=   1.0/2.0;     dxSpeciesds[ 0][ 8] +=   1.0/2.0;     
  dxSpeciesds[ 0][ 9] +=   1.0/2.0;     dxSpeciesds[ 0][10] += - 1.0/3.0;
  dxSpeciesds[ 0][12] += - 1.0/2.0;     dxSpeciesds[ 0][14] += - 1.0/3.0;     
  dxSpeciesds[ 0][15] += - 1.0/4.0;     dxSpeciesds[ 0][16] += - 1.0/4.0;     
  dxSpeciesds[ 0][17] += - 1.0/4.0;     dxSpeciesds[ 0][22] += - 1.0/4.0; 
  dxSpeciesds[ 2][ 3] += - 1.0/2.0;     dxSpeciesds[ 2][ 4] += - 1.0/2.0; /* special case Al2O3   */
  dxSpeciesds[ 2][ 5] += - 1.0/2.0;     dxSpeciesds[ 2][ 6] += - 1.0/2.0;
  dxSpeciesds[ 2][ 7] += - 1.0/2.0;     dxSpeciesds[ 2][ 8] += - 1.0/2.0;
  dxSpeciesds[ 2][ 9] += - 1.0/2.0;     dxSpeciesds[ 2][10] += - 1.0/6.0;
  dxSpeciesds[ 2][11] += - 1.0/2.0;     dxSpeciesds[ 2][13] += - 1.0/2.0;
  dxSpeciesds[ 2][20] += - 1.0/2.0;     dxSpeciesds[ 2][21] += - 1.0/2.0;
  dxSpeciesds[ 2][22] += - 1.0/2.0;
  dxSpeciesds[ 3][ 0] += - 2.0*y;       dxSpeciesds[ 3][ 3] += - 1.0;     /* special case Fe2O3   */
  dxSpeciesds[ 3][ 9] += - 2.0*y;       dxSpeciesds[ 3][14] += - 1.0/6.0;
  dxSpeciesds[ 5][ 0] +=   2.0*y - 1.0; dxSpeciesds[ 5][ 4] += - 1.0;     /* special case Fe2SiO4 */
  dxSpeciesds[ 5][ 9] +=   2.0*y - 1.0; dxSpeciesds[ 5][12] += - 1.0/2.0;     
  dxSpeciesds[ 5][13] += - 1.0/2.0;     dxSpeciesds[ 5][15] += - 1.0/4.0;
  dxSpeciesds[ 7][ 2] += - 1.0/2.0;  	dxSpeciesds[ 7][ 5] += - 1.0;     /* special case Mg2SiO4 */
  dxSpeciesds[ 7][11] += - 1.0/2.0;  	dxSpeciesds[ 7][16] += - 1.0/4.0;
  dxSpeciesds[10][ 6] += - 1.0;  	dxSpeciesds[10][17] += - 1.0/4.0; /* special case Ca2SiO4 */
  dxSpeciesds[10][22] += - 1.0/4.0;
  dxSpeciesds[11][ 7] += - 1.0;  	dxSpeciesds[11][18] += - 1.0/2.0; /* special case Na2SiO3 */
  dxSpeciesds[11][20] += - 1.0/2.0;
  dxSpeciesds[12][ 8] += - 1.0;  	dxSpeciesds[12][19] += - 1.0/2.0; /* special case K2SiO3  */
  dxSpeciesds[12][21] += - 1.0/2.0;
  dxSpeciesds[18][ 1] += - 1.0/2.0;  	dxSpeciesds[18][10] += - 1.0/2.0; /* special case H2O	  */
  dxSpeciesds[18][14] += - 1.0/2.0;  	dxSpeciesds[18][15] += - 1.0/2.0;  	
  dxSpeciesds[18][16] += - 1.0/2.0;  	dxSpeciesds[18][17] += - 1.0/2.0;  	
  dxSpeciesds[18][18] += - 1.0/2.0;  	dxSpeciesds[18][19] += - 1.0/2.0;  	
   
  /* d2 xSpecies / dr ds */
  for (i=0; i<NR; i++) {
    for (j=0; j<NS; j++) {
      d2xSpeciesdrds[  0][i][j] = -dcoeffds[j];  /* SiO2  */
      d2xSpeciesdrds[i+1][i][j] =  dcoeffds[j];  /* other */
    }
  }
  
  /* Total moles of species relative to 1 mole of basis components */
  denom = 12.0      - 3.0*s[ 1] - 6.0*s[ 3] - 6.0*s[ 4] - 6.0*s[ 5] - 6.0*s[ 6] 
        - 6.0*s[ 7] - 6.0*s[ 8] - 6.0*s[ 9] - 4.0*s[10] - 6.0*s[11] - 6.0*s[13]
	- 6.0*s[14] - 6.0*s[15] - 6.0*s[16] - 6.0*s[17] - 6.0*s[18] - 6.0*s[19]
	+ 6.0*s[20] + 6.0*s[21] + 6.0*s[22];                                    /* Special case */
  
  dDenomds[ 0] =  0.0; /* Fe2SiO(4+2y)   */
  dDenomds[ 1] = -3.0; /* Si(1/4)OH      */
  dDenomds[ 2] =  0.0; /* MgSiO3         */
  dDenomds[ 3] = -6.0; /* Fe2AlO4.5      */
  dDenomds[ 4] = -6.0; /* Fe2AlO3.5      */
  dDenomds[ 5] = -6.0; /* Mg2AlO3.5      */
  dDenomds[ 6] = -6.0; /* Ca2AlO3.5      */
  dDenomds[ 7] = -6.0; /* Na2AlO2.5      */
  dDenomds[ 8] = -6.0; /* K2AlO2.5       */
  dDenomds[ 9] = -6.0; /* Fe2AlO(3.5+2y) */
  dDenomds[10] = -4.0; /* Al(1/3)OH      */
  dDenomds[11] = -6.0; /* MgAlO2.5       */
  dDenomds[12] =  0.0; /* FeSiO3         */
  dDenomds[13] = -6.0; /* FeAlO2.5       */
  dDenomds[14] = -6.0; /* Fe(1/3)OH      */
  dDenomds[15] = -6.0; /* Fe(1/2)OH      */
  dDenomds[16] = -6.0; /* Mg(1/2)OH      */
  dDenomds[17] = -6.0; /* Ca(1/2)OH      */
  dDenomds[18] = -6.0; /* NaOH           */
  dDenomds[19] = -6.0; /* KOH            */
  dDenomds[20] =  6.0; /* NaAlSiO4       */
  dDenomds[21] =  6.0; /* KAlSiO4        */
  dDenomds[22] =  6.0; /* Ca(1/2)AlSiO4  */

  nSpecies = 12.0/denom;
  for (i=0; i<NS; i++) {
    dnSpeciesds[i] = -12.0*dDenomds[i]/(denom*denom);
    for (j=0; j<NS; j++) {
      d2nSpeciesds2[i][j] = 24.0*dDenomds[i]*dDenomds[j]/(denom*denom*denom);
      for (k=0; k<NS; k++) d3nSpeciesds3[i][j][k] = -72.0*dDenomds[i]*dDenomds[j]*dDenomds[k]/(denom*denom*denom*denom);
    }
  }
  
  return okay;
}
#endif /* BUILD_MGO_SIO2_VERSION */

#ifdef USE_GHIORSO_KRESS_MODEL

#define WH(k) (modelParameters[k].enthalpy)
#define WS(k) (modelParameters[k].entropy)
#define WV(k) 0.0
#define W(k)  (modelParameters[k].enthalpy - t*modelParameters[k].entropy)

#define G(i)       ((liquid[i].cur).g + modelParameters[NW+i].enthalpy - t*modelParameters[NW+i].entropy)
#define H(i)       ((liquid[i].cur).h + modelParameters[NW+i].enthalpy)
#define S(i)       ((liquid[i].cur).s + modelParameters[NW+i].entropy)
#define V(i)       0.0
#define CP(i)      ((liquid[i].cur).cp)
#define DCPDT(i)   ((liquid[i].cur).dcpdt)
#define DVDT(i)    0.0
#define DVDP(i)    0.0
#define D2VDT2(i)  0.0
#define D2VDTDP(i) 0.0
#define D2VDP2(i)  0.0

#else

#define WH(k) (modelParameters[k].enthalpy)
#define WS(k) (modelParameters[k].entropy)
#define WV(k) (modelParameters[k].volume)
#define W(k)  (modelParameters[k].enthalpy - t*modelParameters[k].entropy  + (p-1.0)*modelParameters[k].volume)

#define G(i)       ((liquid[i].cur).g + modelParameters[NW+i].enthalpy - t*modelParameters[NW+i].entropy + (p-1.0)*modelParameters[NW+i].volume)
#define H(i)       ((liquid[i].cur).h + modelParameters[NW+i].enthalpy)
#define S(i)       ((liquid[i].cur).s + modelParameters[NW+i].entropy)
#define V(i)       ((liquid[i].cur).v + modelParameters[NW+i].volume)
#define CP(i)      ((liquid[i].cur).cp)
#define DCPDT(i)   ((liquid[i].cur).dcpdt)
#define DVDT(i)    ((liquid[i].cur).dvdt)
#define DVDP(i)    ((liquid[i].cur).dvdp)
#define D2VDT2(i)  ((liquid[i].cur).d2vdt2)
#define D2VDTDP(i) ((liquid[i].cur).d2vdtdp)
#define D2VDP2(i)  ((liquid[i].cur).d2vdp2)

#endif /* USE_GHIORSO_KRESS_MODEL */

static void loadTaylorCoefficients(double t, double p)
{
  int i, j, k, l, m, n;

#ifdef DEBUG
  printf("Call to loadTaylorCoefficients ...\n");
#endif
  
#ifdef USE_GHIORSO_KRESS_MODEL
  for (i=0; i<NE; i++)  gibbs(t, 1.0, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
#else
  for (i=0; i<NE; i++)  gibbs(t,   p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
#endif /* USE_GHIORSO_KRESS_MODEL */
  
  Gconst       = 0.0;  Hconst       = 0.0;  Sconst       = 0.0;  Vconst       = 0.0;            
  CPconst      = 0.0;  DCPDTconst   = 0.0;  DVDTconst    = 0.0;  DVDPconst    = 0.0;         
  D2VDT2const  = 0.0;  D2VDTDPconst = 0.0;  D2VDP2const  = 0.0;  
  for (j=0; j<NR; j++) { 
    gr[j]       = 0.0;  hr[j]       = 0.0;  sr[j]       = 0.0;  vr[j]       = 0.0; 
    cpr[j]      = 0.0;  dcpdtr[j]   = 0.0;  dvdtr[j]    = 0.0;  dvdpr[j]    = 0.0; 
    d2vdt2r[j]  = 0.0;  d2vdtdpr[j] = 0.0;  d2vdp2r[j]  = 0.0; 
    for (k=0; k<NR; k++) { grr[j][k] = 0.0;  hrr[j][k] = 0.0;  srr[j][k] = 0.0;  vrr[j][k] = 0.0; }
    for (k=0; k<NS; k++) { grs[j][k] = 0.0;  hrs[j][k] = 0.0;  srs[j][k] = 0.0;  vrs[j][k] = 0.0; }
  }
  for (j=0; j<NS; j++) {
    gs[j]       = 0.0;  hs[j]       = 0.0;  ss[j]       = 0.0;  vs[j]       = 0.0; 
    cps[j]      = 0.0;  dcpdts[j]   = 0.0;  dvdts[j]    = 0.0;  dvdps[j]    = 0.0; 
    d2vdt2s[j]  = 0.0;  d2vdtdps[j] = 0.0;  d2vdp2s[j]  = 0.0; 
    for (k=0; k<NS; k++) { gss[j][k] = 0.0;  hss[j][k] = 0.0;  sss[j][k] = 0.0;  vss[j][k] = 0.0; }
  }
       
  for (i=0; i<NE; i++) {
    Gconst       += taylorCoeff[i+1][0+1]*G(i);
    Hconst       += taylorCoeff[i+1][0+1]*H(i);
    Sconst       += taylorCoeff[i+1][0+1]*S(i);
    Vconst       += taylorCoeff[i+1][0+1]*V(i);
    CPconst      += taylorCoeff[i+1][0+1]*CP(i);
    DCPDTconst   += taylorCoeff[i+1][0+1]*DCPDT(i);
    DVDTconst    += taylorCoeff[i+1][0+1]*DVDT(i);
    DVDPconst    += taylorCoeff[i+1][0+1]*DVDP(i);
    D2VDT2const  += taylorCoeff[i+1][0+1]*D2VDT2(i);
    D2VDTDPconst += taylorCoeff[i+1][0+1]*D2VDTDP(i);
    D2VDP2const  += taylorCoeff[i+1][0+1]*D2VDP2(i);
    for (j=0; j<NR; j++) {
      gr[j]       += taylorCoeff[i+1][1+j+1]*G(i);
      hr[j]       += taylorCoeff[i+1][1+j+1]*H(i);
      sr[j]       += taylorCoeff[i+1][1+j+1]*S(i);
      vr[j]       += taylorCoeff[i+1][1+j+1]*V(i);
      cpr[j]      += taylorCoeff[i+1][1+j+1]*CP(i);
      dcpdtr[j]   += taylorCoeff[i+1][1+j+1]*DCPDT(i);
      dvdtr[j]    += taylorCoeff[i+1][1+j+1]*DVDT(i);
      dvdpr[j]    += taylorCoeff[i+1][1+j+1]*DVDP(i);
      d2vdt2r[j]  += taylorCoeff[i+1][1+j+1]*D2VDT2(i);
      d2vdtdpr[j] += taylorCoeff[i+1][1+j+1]*D2VDTDP(i);
      d2vdp2r[j]  += taylorCoeff[i+1][1+j+1]*D2VDP2(i);
    }
    for (j=0; j<NS; j++) {
      gs[j]       += taylorCoeff[i+1][1+NR+j+1]*G(i);
      hs[j]       += taylorCoeff[i+1][1+NR+j+1]*H(i);
      ss[j]       += taylorCoeff[i+1][1+NR+j+1]*S(i);
      vs[j]       += taylorCoeff[i+1][1+NR+j+1]*V(i);
      cps[j]      += taylorCoeff[i+1][1+NR+j+1]*CP(i);
      dcpdts[j]   += taylorCoeff[i+1][1+NR+j+1]*DCPDT(i);
      dvdts[j]    += taylorCoeff[i+1][1+NR+j+1]*DVDT(i);
      dvdps[j]    += taylorCoeff[i+1][1+NR+j+1]*DVDP(i);
      d2vdt2s[j]  += taylorCoeff[i+1][1+NR+j+1]*D2VDT2(i);
      d2vdtdps[j] += taylorCoeff[i+1][1+NR+j+1]*D2VDTDP(i);
      d2vdp2s[j]  += taylorCoeff[i+1][1+NR+j+1]*D2VDP2(i);
    }
  }
  /* Code below is optimized for speed of execution ... */
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    register double w  = W(n);
    if (w != 0.0) {
      Gconst += taylorCoeff[n+NE+1][0+1]*w;
      for (j=0, m=0; j<NR; j++) {
        gr[j] += taylorCoeff[n+NE+1][1+j+1]*w;
        for (k=j; k<NR; k++, m++) grr[j][k] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*w;
        for (k=0; k<NS; k++, m++) grs[j][k] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*w;
      }
      for (j=0; j<NS; j++) {
        gs[j] += taylorCoeff[n+NE+1][1+NR+j+1]*w;
        for (k=j; k<NS; k++, m++) if (taylorCoeff[n+NE+1][1+NR+NS+m+1] != 0.0) gss[j][k] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*w;
      }
    }
  }
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    register double wh = WH(n);
    if (wh != 0.0) {
      Hconst += taylorCoeff[n+NE+1][0+1]*wh;
      for (j=0, m=0; j<NR; j++) {
        hr[j] += taylorCoeff[n+NE+1][1+j+1]*wh;
        for (k=j; k<NR; k++, m++) hrr[j][k] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*wh;
        for (k=0; k<NS; k++, m++) hrs[j][k] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*wh;
      }
      for (j=0; j<NS; j++) {
        hs[j] += taylorCoeff[n+NE+1][1+NR+j+1]*wh;
        for (k=j; k<NS; k++, m++) if (taylorCoeff[n+NE+1][1+NR+NS+m+1] != 0.0) hss[j][k] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*wh;
      }
    }
  }
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    register double ws = WS(n);
    if (ws != 0.0) {
      Sconst += taylorCoeff[n+NE+1][0+1]*ws;
      for (j=0, m=0; j<NR; j++) {
        sr[j] += taylorCoeff[n+NE+1][1+j+1]*ws;
        for (k=j; k<NR; k++, m++) srr[j][k] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*ws;
        for (k=0; k<NS; k++, m++) srs[j][k] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*ws;
      }
      for (j=0; j<NS; j++) {
        ss[j] += taylorCoeff[n+NE+1][1+NR+j+1]*ws;
        for (k=j; k<NS; k++, m++) if (taylorCoeff[n+NE+1][1+NR+NS+m+1] != 0.0) sss[j][k] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*ws;
      }
    }
  }
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    register double wv = WV(n);
    if (wv != 0.0) {
      Vconst += taylorCoeff[n+NE+1][0+1]*wv;
      for (j=0, m=0; j<NR; j++) {
        vr[j] += taylorCoeff[n+NE+1][1+j+1]*wv;
        for (k=j; k<NR; k++, m++) vrr[j][k] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*wv;
        for (k=0; k<NS; k++, m++) vrs[j][k] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*wv;
      }
      for (j=0; j<NS; j++) {
        vs[j] += taylorCoeff[n+NE+1][1+NR+j+1]*wv;
        for (k=j; k<NS; k++, m++) if (taylorCoeff[n+NE+1][1+NR+NS+m+1] != 0.0) vss[j][k] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*wv;
      }
    }
  }
  /* ... end speed optimization. */
  
  for (j=0; j<NR; j++) for (k=j+1; k<NR; k++) {
     grr[k][j]       = grr[j][k];
     hrr[k][j]       = hrr[j][k];
     srr[k][j]       = srr[j][k];
     vrr[k][j]       = vrr[j][k];
  }

  for (j=0; j<NS; j++) for (k=j+1; k<NS; k++) {
     gss[k][j]       = gss[j][k];
     hss[k][j]       = hss[j][k];
     sss[k][j]       = sss[j][k];
     vss[k][j]       = vss[j][k];
  }

/* ============================================================================== */
/* Do this to insure that mixing properties are reference to a T,P standard State */
/* ============================================================================== */

#ifdef USE_GHIORSO_KRESS_MODEL
  for (i=0; i<NE; i++)  gibbs(t, p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
#endif /* USE_GHIORSO_KRESS_MODEL */

}

/* ================================================ */
/* The fill (some thermodynamic property) routines. */                                                                                        
/* ================================================ */

#ifdef USE_GHIORSO_KRESS_MODEL

/* -----> These routines are coded by Maple */

static 
double d2gdp2MAP(double p,double pr,double v0,double v1,double v2,double a,
double b)
{
  double t1;
  double t11;
  double t13;
  double t20;
  double t5;
  double t6;
  {
    t1 = v0*a;
    t5 = v2/2.0+v1*a+v0*b;
    t6 = p-pr;
    t11 = t6*t6;
    t13 = 1.0+a*t6+b*t11;
    t20 = t13*t13;
    return((v1+t1+2.0*t5*t6)/t13-(v0+(v1+t1)*t6+t5*t11)/t20*(a+2.0*b*t6));
  }
}

static 
double d2gdrdpMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr)
{
  double t12;
  double t17;
  double t29;
  double t4;
  {
    t4 = p-pr;
    t12 = t4*t4;
    t17 = 1.0+a*t4+b*t12;
    t29 = t17*t17;
    return((dv0dr+(dv1dr+dv0dr*a+v0*dadr)*t4+(dv2dr/2.0+dv1dr*a+v1*dadr+dv0dr*b
+v0*dbdr)*t12)/t17-(v0+(v1+v0*a)*t4+(v2/2.0+v1*a+v0*b)*t12)/t29*(dadr*t4+dbdr*
t12));
  }
}

static 
double d2gdtdpMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dt,double dv1dt)
{
  double t3;
  double t8;
  {
    t3 = p-pr;
    t8 = t3*t3;
    return((dv0dt+(dv1dt+dv0dt*a)*t3+(dv1dt*a+dv0dt*b)*t8)/(1.0+a*t3+b*t8));
  }
}

static 
double d3gdr2dpMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr,
double dv0ds,double dv1ds,double dv2ds,double dads,double dbds,double d2v0dr2,
double d2v1dr2,double d2v2dr2,double d2adr2,double d2bdr2)
{
  double t18;
  double t23;
  double t38;
  double t39;
  double t43;
  double t6;
  double t60;
  double t70;
  {
    t6 = p-pr;
    t18 = t6*t6;
    t23 = 1.0+a*t6+b*t18;
    t38 = t23*t23;
    t39 = 1/t38;
    t43 = dads*t6+dbds*t18;
    t60 = dadr*t6+dbdr*t18;
    t70 = v0+(v1+v0*a)*t6+(v2/2.0+v1*a+v0*b)*t18;
    return((d2v0dr2+(d2v1dr2+d2v0dr2*a+dv0dr*dads+dv0ds*dadr+v0*d2adr2)*t6+(
d2v2dr2/2.0+d2v1dr2*a+dv1dr*dads+dv1ds*dadr+v1*d2adr2+d2v0dr2*b+dv0dr*dbds+
dv0ds*dbdr+v0*d2bdr2)*t18)/t23-(dv0dr+(dv1dr+dv0dr*a+v0*dadr)*t6+(dv2dr/2.0+
dv1dr*a+v1*dadr+dv0dr*b+v0*dbdr)*t18)*t39*t43-(dv0ds+(dv1ds+dv0ds*a+v0*dads)*t6
+(dv2ds/2.0+dv1ds*a+v1*dads+dv0ds*b+v0*dbds)*t18)*t39*t60+2.0*t70/t38/t23*t60*
t43-t70*t39*(d2adr2*t6+d2bdr2*t18));
  }
}

static 
double d3gdrdtdpMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr,
double dv0dt,double dv1dt,double d2v0drdt,double d2v1drdt)
{
  double t11;
  double t16;
  double t27;
  double t4;
  {
    t4 = p-pr;
    t11 = t4*t4;
    t16 = 1.0+a*t4+b*t11;
    t27 = t16*t16;
    return((d2v0drdt+(d2v1drdt+d2v0drdt*a+dv0dt*dadr)*t4+(d2v1drdt*a+dv1dt*dadr
+d2v0drdt*b+dv0dt*dbdr)*t11)/t16-(dv0dt+(dv1dt+dv0dt*a)*t4+(dv1dt*a+dv0dt*b)*
t11)/t27*(dadr*t4+dbdr*t11));
  }
}

static 
double d3gdrdp2MAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr)
{
  double t1;
  double t14;
  double t16;
  double t2;
  double t23;
  double t24;
  double t28;
  double t30;
  double t34;
  double t41;
  double t46;
  double t8;
  double t9;
  {
    t1 = dv0dr*a;
    t2 = v0*dadr;
    t8 = dv2dr/2.0+dv1dr*a+v1*dadr+dv0dr*b+v0*dbdr;
    t9 = p-pr;
    t14 = t9*t9;
    t16 = 1.0+a*t9+b*t14;
    t23 = t16*t16;
    t24 = 1/t23;
    t28 = a+2.0*b*t9;
    t30 = v0*a;
    t34 = v2/2.0+v1*a+v0*b;
    t41 = dadr*t9+dbdr*t14;
    t46 = v0+(v1+t30)*t9+t34*t14;
    return((dv1dr+t1+t2+2.0*t8*t9)/t16-(dv0dr+(dv1dr+t1+t2)*t9+t8*t14)*t24*t28-
(v1+t30+2.0*t34*t9)*t24*t41+2.0*t46/t23/t16*t41*t28-t46*t24*(dadr+2.0*dbdr*t9)
);
  }
}

static 
double d3gdp3MAP(double p,double pr,double v0,double v1,double v2,double a,
double b)
{
  double t1;
  double t10;
  double t13;
  double t15;
  double t19;
  double t20;
  double t24;
  double t3;
  double t30;
  double t34;
  double t6;
  double t8;
  {
    t1 = v1*a;
    t3 = v0*b;
    t6 = p-pr;
    t8 = t6*t6;
    t10 = 1.0+a*t6+b*t8;
    t13 = v0*a;
    t15 = v2/2.0+t1+t3;
    t19 = t10*t10;
    t20 = 1/t19;
    t24 = a+2.0*b*t6;
    t30 = v0+(v1+t13)*t6+t15*t8;
    t34 = t24*t24;
    return((v2+2.0*t1+2.0*t3)/t10-2.0*(v1+t13+2.0*t15*t6)*t20*t24+2.0*t30/t19/
t10*t34-2.0*t30*t20*b);
  }
}

static 
double d3gdt2dpMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dt,double dv1dt,double d2v0dt2,double d2v1dt2)
{
  double t3;
  double t8;
  {
    t3 = p-pr;
    t8 = t3*t3;
    return((d2v0dt2+(d2v1dt2+d2v0dt2*a)*t3+(d2v1dt2*a+d2v0dt2*b)*t8)/(1.0+a*t3+
b*t8));
  }
}

static 
double d3gdtdp2MAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dt,double dv1dt)
{
  double t1;
  double t10;
  double t12;
  double t19;
  double t4;
  double t5;
  {
    t1 = dv0dt*a;
    t4 = dv1dt*a+dv0dt*b;
    t5 = p-pr;
    t10 = t5*t5;
    t12 = 1.0+a*t5+b*t10;
    t19 = t12*t12;
    return((dv1dt+t1+2.0*t4*t5)/t12-(dv0dt+(dv1dt+t1)*t5+t4*t10)/t19*(a+2.0*b*
t5));
  }
}

static 
double dgdrLMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr)
{
  double t1;
  double t100;
  double t11;
  double t119;
  double t125;
  double t129;
  double t13;
  double t131;
  double t132;
  double t14;
  double t152;
  double t154;
  double t16;
  double t162;
  double t175;
  double t177;
  double t18;
  double t2;
  double t22;
  double t25;
  double t26;
  double t27;
  double t28;
  double t32;
  double t4;
  double t42;
  double t5;
  double t54;
  double t55;
  double t6;
  double t61;
  double t64;
  double t67;
  double t68;
  double t7;
  double t72;
  double t74;
  double t8;
  double t82;
  double t83;
  double t9;
  double t94;
  double t95;
  {
    t1 = b*b;
    t2 = 1/t1;
    t4 = a*a;
    t5 = 4.0*b-t4;
    t6 = sqrt(t5);
    t7 = 1/t6;
    t8 = t2*t7;
    t9 = v2*dbdr;
    t11 = 1/b;
    t13 = 1/t6/t5;
    t14 = t11*t13;
    t16 = a*dadr;
    t18 = 4.0*dbdr-2.0*t16;
    t22 = t11*t7;
    t25 = 1/t1/b;
    t26 = t25*t7;
    t27 = t4*a;
    t28 = v1*t27;
    t32 = t2*t13;
    t42 = v2*t4;
    t54 = v1*a;
    t55 = t54*dbdr;
    t61 = dv1dr*a;
    t64 = v1*dadr;
    t67 = t8*t9+t14*v2*t18/2.0-t22*dv2dr-2.0*t26*t28*dbdr-t32*t28*t18/2.0+t8*
dv1dr*t27+3.0*t8*v1*t4*dadr-t26*t42*dbdr-t32*t42*t18/4.0+t8*dv2dr*t4/2.0+t8*v2*
a*dadr+3.0*t8*t55+3.0/2.0*t14*t54*t18-3.0*t22*t61-3.0*t22*t64;
    t68 = b*p;
    t72 = a+2.0*t68-2.0*b*pr;
    t74 = atan(t72*t7);
    t82 = -t22*v2+t8*t28+t8*t42/2.0-3.0*t22*t54;
    t83 = dbdr*p;
    t94 = t72*t72;
    t95 = 1/t5;
    t100 = t2*v1;
    t119 = t2*v2;
    t125 = p*p;
    t129 = pr*pr;
    t131 = 1.0+a*p-a*pr+b*t125-2.0*t68*pr+b*t129;
    t132 = log(t131);
    t152 = t2*p;
    t154 = t11*p;
    t162 = atan(a*t7);
    t175 = t2*pr;
    t177 = t11*pr;
    return(t67*t74+t82*((dadr+2.0*t83-2.0*dbdr*pr)*t7-t72*t13*t18/2.0)/(1.0+t94
*t95)+(-t100*dbdr/2.0+t11*dv1dr/2.0+t25*v1*t4*dbdr-t2*dv1dr*t4/2.0-t100*t16+t25
*v2*a*dbdr/2.0-t2*dv2dr*a/4.0-t119*dadr/4.0)*t132+(t11*v1/2.0-t100*t4/2.0-t119*
a/4.0)*(dadr*p-dadr*pr+dbdr*t125-2.0*t83*pr+dbdr*t129)/t131+dv0dr*p-t152*t55+
t154*t61+t154*t64-t152*t9/2.0+t154*dv2dr/2.0-t67*t162-t82*(dadr*t7-a*t13*t18/
2.0)/(1.0+t4*t95)-dv0dr*pr+t175*t55-t177*t61-t177*t64+t175*t9/2.0-t177*dv2dr/
2.0);
  }
}

static 
double dgdrGMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr)
{
  double t1;
  double t100;
  double t11;
  double t119;
  double t125;
  double t129;
  double t13;
  double t131;
  double t132;
  double t14;
  double t152;
  double t154;
  double t16;
  double t162;
  double t175;
  double t177;
  double t18;
  double t2;
  double t22;
  double t25;
  double t26;
  double t27;
  double t28;
  double t32;
  double t4;
  double t42;
  double t5;
  double t54;
  double t55;
  double t6;
  double t61;
  double t64;
  double t67;
  double t68;
  double t7;
  double t72;
  double t74;
  double t8;
  double t82;
  double t83;
  double t9;
  double t94;
  double t95;
  {
    t1 = b*b;
    t2 = 1/t1;
    t4 = a*a;
    t5 = -4.0*b+t4;
    t6 = sqrt(t5);
    t7 = 1/t6;
    t8 = t2*t7;
    t9 = v2*dbdr;
    t11 = 1/b;
    t13 = 1/t6/t5;
    t14 = t11*t13;
    t16 = a*dadr;
    t18 = -4.0*dbdr+2.0*t16;
    t22 = t11*t7;
    t25 = 1/t1/b;
    t26 = t25*t7;
    t27 = t4*a;
    t28 = v1*t27;
    t32 = t2*t13;
    t42 = v2*t4;
    t54 = v1*a;
    t55 = t54*dbdr;
    t61 = dv1dr*a;
    t64 = v1*dadr;
    t67 = -t8*t9-t14*v2*t18/2.0+t22*dv2dr+2.0*t26*t28*dbdr+t32*t28*t18/2.0-t8*
dv1dr*t27-3.0*t8*v1*t4*dadr+t26*t42*dbdr+t32*t42*t18/4.0-t8*dv2dr*t4/2.0-t8*v2*
a*dadr-3.0*t8*t55-3.0/2.0*t14*t54*t18+3.0*t22*t61+3.0*t22*t64;
    t68 = b*p;
    t72 = a+2.0*t68-2.0*b*pr;
    t74 = (1.0+t72*t7)/(1.0-t72*t7);
    t82 = t22*v2-t8*t28-t8*t42/2.0+3.0*t22*t54;
    t83 = dbdr*p;
    t94 = t72*t72;
    t95 = 1/t5;
    t100 = t2*v1;
    t119 = t2*v2;
    t125 = p*p;
    t129 = pr*pr;
    t131 = 1.0+a*p-a*pr+b*t125-2.0*t68*pr+b*t129;
    if (t131 <= 0.0) printERR("dgdrGMAP", ERR_DGDR_GMAP_1, "t131", t131) 
    t132 = log(t131);
    t152 = t2*p;
    t154 = t11*p;
    t162 = (1.0+a*t7)/(1.0-a*t7);
    t175 = t2*pr;
    t177 = t11*pr;
    if (t74/t162 <= 0.0) printERR("dgdrGMAP", ERR_DGDR_GMAP_2, "t74/t162", t74/t162)
    return(t82*((dadr+2.0*t83-2.0*dbdr*pr)*t7-t72*t13*t18/2.0)/(1.0-t94
*t95)+(-t100*dbdr/2.0+t11*dv1dr/2.0+t25*v1*t4*dbdr-t2*dv1dr*t4/2.0-t100*t16+t25
*v2*a*dbdr/2.0-t2*dv2dr*a/4.0-t119*dadr/4.0)*t132+(t11*v1/2.0-t100*t4/2.0-t119*
a/4.0)*(dadr*p-dadr*pr+dbdr*t125-2.0*t83*pr+dbdr*t129)/t131+p*dv0dr-t152*t55+
t154*t61+t154*t64-t152*t9/2.0+t154*dv2dr/2.0-t82*(dadr*t7-a*t13*t18/
2.0)/(1.0-t4*t95)-pr*dv0dr+t175*t55-t177*t61-t177*t64+t175*t9/2.0-t177*dv2dr/
2.0 + t67*log(t74/t162)/2.0 );
  }
}

#ifdef NEVER_DEFINED

static 
double dgdtLMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dt,double dv1dt)
{
  double t1;
  double t12;
  double t14;
  double t17;
  double t18;
  double t2;
  double t24;
  double t33;
  double t37;
  double t4;
  double t40;
  double t46;
  double t6;
  double t7;
  {
    t1 = b*b;
    t2 = 1/t1;
    t4 = a*a;
    t6 = sqrt(4.0*b-t4);
    t7 = 1/t6;
    t12 = 1/b;
    t14 = dv1dt*a;
    t17 = t2*t7*dv1dt*t4*a-3.0*t12*t7*t14;
    t18 = b*p;
    t24 = atan((a+2.0*t18-2.0*b*pr)*t7);
    t33 = p*p;
    t37 = pr*pr;
    t40 = log(1.0+a*p-a*pr+b*t33-2.0*t18*pr+b*t37);
    t46 = atan(a*t7);
    return(t17*t24+(t12*dv1dt/2.0-t2*dv1dt*t4/2.0)*t40+p*dv0dt+t12*p*t14-t17*
t46-pr*dv0dt-t12*pr*t14);
  }
}

static 
double dgdtGMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dt,double dv1dt)
{
  double t1;
  double t12;
  double t14;
  double t17;
  double t18;
  double t2;
  double t24;
  double t33;
  double t37;
  double t4;
  double t40;
  double t46;
  double t6;
  double t7;
  {
    t1 = b*b;
    t2 = 1/t1;
    t4 = a*a;
    t6 = sqrt(-4.0*b+t4);
    t7 = 1/t6;
    t12 = 1/b;
    t14 = dv1dt*a;
    t17 = -t2*t7*dv1dt*t4*a+3.0*t12*t7*t14;
    t18 = b*p;
    t24 = (1.0+(a+2.0*t18-2.0*b*pr)*t7)/(1.0-(a+2.0*t18-2.0*b*pr)*t7);
    t33 = p*p;
    t37 = pr*pr;
    t40 = log(1.0+a*p-a*pr+b*t33-2.0*t18*pr+b*t37);
    t46 = (1.0+a*t7)/(1.0-a*t7);
    if (t24/t46 <= 0.0) printERR("dgdtGMAP", ERR_DGDT_GMAP, "t24/t46", t24/t46)
    return(t17*log(t24/t46)/2.0+(t12*dv1dt/2.0-t2*dv1dt*t4/2.0)*t40+p*dv0dt+t12*p*t14-pr*dv0dt-t12*pr*t14);
  }
}

#endif /* NEVER_DEFINED */

static 
double d2gdrdtLMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr,
double dv0dt,double dv1dt,double d2v0drdt,double d2v1drdt)
{
  double t1;
  double t10;
  double t100;
  double t101;
  double t11;
  double t120;
  double t124;
  double t139;
  double t15;
  double t17;
  double t20;
  double t22;
  double t26;
  double t3;
  double t33;
  double t34;
  double t37;
  double t42;
  double t43;
  double t46;
  double t49;
  double t5;
  double t50;
  double t54;
  double t56;
  double t6;
  double t61;
  double t62;
  double t7;
  double t73;
  double t74;
  double t79;
  double t8;
  double t94;
  double t98;
  {
    t1 = b*b;
    t3 = 1/t1/b;
    t5 = a*a;
    t6 = 4.0*b-t5;
    t7 = sqrt(t6);
    t8 = 1/t7;
    t10 = t5*a;
    t11 = dv1dt*t10;
    t15 = 1/t1;
    t17 = 1/t7/t6;
    t20 = a*dadr;
    t22 = 4.0*dbdr-2.0*t20;
    t26 = t15*t8;
    t33 = dv1dt*a;
    t34 = t33*dbdr;
    t37 = 1/b;
    t42 = t37*t8;
    t43 = d2v1drdt*a;
    t46 = dv1dt*dadr;
    t49 = -2.0*t3*t8*t11*dbdr-t15*t17*t11*t22/2.0+t26*d2v1drdt*t10+3.0*t26*
dv1dt*t5*dadr+3.0*t26*t34+3.0/2.0*t37*t17*t33*t22-3.0*t42*t43-3.0*t42*t46;
    t50 = b*p;
    t54 = a+2.0*t50-2.0*b*pr;
    t56 = atan(t54*t8);
    t61 = t26*t11-3.0*t42*t33;
    t62 = dbdr*p;
    t73 = t54*t54;
    t74 = 1/t6;
    t79 = t15*dv1dt;
    t94 = p*p;
    t98 = pr*pr;
    t100 = 1.0+a*p-a*pr+b*t94-2.0*t50*pr+b*t98;
    t101 = log(t100);
    t120 = t37*p;
    t124 = atan(a*t8);
    t139 = t37*pr;
    return(t49*t56+t61*((dadr+2.0*t62-2.0*dbdr*pr)*t8-t54*t17*t22/2.0)/(1.0+t73
*t74)+(-t79*dbdr/2.0+t37*d2v1drdt/2.0+t3*dv1dt*t5*dbdr-t15*d2v1drdt*t5/2.0-t79*
t20)*t101+(t37*dv1dt/2.0-t79*t5/2.0)*(dadr*p-dadr*pr+dbdr*t94-2.0*t62*pr+dbdr*
t98)/t100+p*d2v0drdt-t15*p*t34+t120*t43+t120*t46-t49*t124-t61*(dadr*t8-a*t17*
t22/2.0)/(1.0+t5*t74)-pr*d2v0drdt+t15*pr*t34-t139*t43-t139*t46);
  }
}

static 
double d2gdrdtGMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr,
double dv0dt,double dv1dt,double d2v0drdt,double d2v1drdt)
{
  double t1;
  double t10;
  double t100;
  double t101;
  double t11;
  double t120;
  double t124;
  double t139;
  double t15;
  double t17;
  double t20;
  double t22;
  double t26;
  double t3;
  double t33;
  double t34;
  double t37;
  double t42;
  double t43;
  double t46;
  double t49;
  double t5;
  double t50;
  double t54;
  double t56;
  double t6;
  double t61;
  double t62;
  double t7;
  double t73;
  double t74;
  double t79;
  double t8;
  double t94;
  double t98;
  {
    t1 = b*b;
    t3 = 1/t1/b;
    t5 = a*a;
    t6 = -4.0*b+t5;
    t7 = sqrt(t6);
    t8 = 1/t7;
    t10 = t5*a;
    t11 = dv1dt*t10;
    t15 = 1/t1;
    t17 = 1/t7/t6;
    t20 = a*dadr;
    t22 = -4.0*dbdr+2.0*t20;
    t26 = t15*t8;
    t33 = dv1dt*a;
    t34 = t33*dbdr;
    t37 = 1/b;
    t42 = t37*t8;
    t43 = d2v1drdt*a;
    t46 = dv1dt*dadr;
    t49 = 2.0*t3*t8*t11*dbdr+t15*t17*t11*t22/2.0-t26*d2v1drdt*t10-3.0*t26*dv1dt
*t5*dadr-3.0*t26*t34-3.0/2.0*t37*t17*t33*t22+3.0*t42*t43+3.0*t42*t46;
    t50 = b*p;
    t54 = a+2.0*t50-2.0*b*pr;
    t56 = (1.0+t54*t8)/(1.0-t54*t8);
    t61 = -t26*t11+3.0*t42*t33;
    t62 = dbdr*p;
    t73 = t54*t54;
    t74 = 1/t6;
    t79 = t15*dv1dt;
    t94 = p*p;
    t98 = pr*pr;
    t100 = 1.0+a*p-a*pr+b*t94-2.0*t50*pr+b*t98;
    if (t100 <= 0.0) printERR("d2gdrdtGMAP", ERR_D2GDRDT_GMAP_1, "t100", t100)
    t101 = log(t100);
    t120 = t37*p;
    t124 = (1.0+a*t8)/(1.0-a*t8);
    t139 = t37*pr;
    if (t56/t124 <= 0.0) printERR("d2gdrdtGMAP", ERR_D2GDRDT_GMAP_2, "t56/t124", t56/t124)
    return(t49*log(t56/t124)/2.0+t61*((dadr+2.0*t62-2.0*dbdr*pr)*t8-t54*t17*t22/2.0)/(1.0-t73
*t74)+(-t79*dbdr/2.0+t37*d2v1drdt/2.0+t3*dv1dt*t5*dbdr-t15*d2v1drdt*t5/2.0-t79*
t20)*t101+(t37*dv1dt/2.0-t79*t5/2.0)*(dadr*p-dadr*pr+dbdr*t94-2.0*t62*pr+dbdr*
t98)/t100+p*d2v0drdt-t15*p*t34+t120*t43+t120*t46-t61*(dadr*t8-a*t17*
t22/2.0)/(1.0-t5*t74)-pr*d2v0drdt+t15*pr*t34-t139*t43-t139*t46);
  }
}

static 
double d3gdrdt2LMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr,
double dv0dt,double dv1dt,double d2v0drdt,double d2v1drdt,double d2v0dt2,
double d2v1dt2,double d3v0drdt2,double d3v1drdt2)
{
  double t1;
  double t10;
  double t100;
  double t101;
  double t11;
  double t120;
  double t124;
  double t139;
  double t15;
  double t17;
  double t20;
  double t22;
  double t26;
  double t3;
  double t33;
  double t34;
  double t37;
  double t42;
  double t43;
  double t46;
  double t49;
  double t5;
  double t50;
  double t54;
  double t56;
  double t6;
  double t61;
  double t62;
  double t7;
  double t73;
  double t74;
  double t79;
  double t8;
  double t94;
  double t98;
  {
    t1 = b*b;
    t3 = 1/t1/b;
    t5 = a*a;
    t6 = 4.0*b-t5;
    t7 = sqrt(t6);
    t8 = 1/t7;
    t10 = t5*a;
    t11 = d2v1dt2*t10;
    t15 = 1/t1;
    t17 = 1/t7/t6;
    t20 = a*dadr;
    t22 = 4.0*dbdr-2.0*t20;
    t26 = t15*t8;
    t33 = d2v1dt2*a;
    t34 = t33*dbdr;
    t37 = 1/b;
    t42 = t37*t8;
    t43 = d3v1drdt2*a;
    t46 = d2v1dt2*dadr;
    t49 = -2.0*t3*t8*t11*dbdr-t15*t17*t11*t22/2.0+t26*d3v1drdt2*t10+3.0*t26*
d2v1dt2*t5*dadr+3.0*t26*t34+3.0/2.0*t37*t17*t33*t22-3.0*t42*t43-3.0*t42*t46;
    t50 = b*p;
    t54 = a+2.0*t50-2.0*b*pr;
    t56 = atan(t54*t8);
    t61 = t26*t11-3.0*t42*t33;
    t62 = dbdr*p;
    t73 = t54*t54;
    t74 = 1/t6;
    t79 = t15*d2v1dt2;
    t94 = p*p;
    t98 = pr*pr;
    t100 = 1.0+a*p-a*pr+b*t94-2.0*t50*pr+b*t98;
    t101 = log(t100);
    t120 = t37*p;
    t124 = atan(a*t8);
    t139 = t37*pr;
    return(t49*t56+t61*((dadr+2.0*t62-2.0*dbdr*pr)*t8-t54*t17*t22/2.0)/(1.0+t73
*t74)+(-t79*dbdr/2.0+t37*d3v1drdt2/2.0+t3*d2v1dt2*t5*dbdr-t15*d3v1drdt2*t5/2.0-
t79*t20)*t101+(t37*d2v1dt2/2.0-t79*t5/2.0)*(dadr*p-dadr*pr+dbdr*t94-2.0*t62*pr+
dbdr*t98)/t100+p*d3v0drdt2-t15*p*t34+t120*t43+t120*t46-t49*t124-t61*(dadr*t8-a*
t17*t22/2.0)/(1.0+t5*t74)-pr*d3v0drdt2+t15*pr*t34-t139*t43-t139*t46);
  }
}

static 
double d3gdrdt2GMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr,
double dv0dt,double dv1dt,double d2v0drdt,double d2v1drdt,double d2v0dt2,
double d2v1dt2,double d3v0drdt2,double d3v1drdt2)
{
  double t1;
  double t10;
  double t100;
  double t101;
  double t11;
  double t120;
  double t124;
  double t139;
  double t15;
  double t17;
  double t20;
  double t22;
  double t26;
  double t3;
  double t33;
  double t34;
  double t37;
  double t42;
  double t43;
  double t46;
  double t49;
  double t5;
  double t50;
  double t54;
  double t56;
  double t6;
  double t61;
  double t62;
  double t7;
  double t73;
  double t74;
  double t79;
  double t8;
  double t94;
  double t98;
  {
    t1 = b*b;
    t3 = 1/t1/b;
    t5 = a*a;
    t6 = -4.0*b+t5;
    t7 = sqrt(t6);
    t8 = 1/t7;
    t10 = t5*a;
    t11 = d2v1dt2*t10;
    t15 = 1/t1;
    t17 = 1/t7/t6;
    t20 = a*dadr;
    t22 = -4.0*dbdr+2.0*t20;
    t26 = t15*t8;
    t33 = d2v1dt2*a;
    t34 = t33*dbdr;
    t37 = 1/b;
    t42 = t37*t8;
    t43 = d3v1drdt2*a;
    t46 = d2v1dt2*dadr;
    t49 = 2.0*t3*t8*t11*dbdr+t15*t17*t11*t22/2.0-t26*d3v1drdt2*t10-3.0*t26*
d2v1dt2*t5*dadr-3.0*t26*t34-3.0/2.0*t37*t17*t33*t22+3.0*t42*t43+3.0*t42*t46;
    t50 = b*p;
    t54 = a+2.0*t50-2.0*b*pr;
    t56 = (1.0+t54*t8)/(1.0-t54*t8);
    t61 = -t26*t11+3.0*t42*t33;
    t62 = dbdr*p;
    t73 = t54*t54;
    t74 = 1/t6;
    t79 = t15*d2v1dt2;
    t94 = p*p;
    t98 = pr*pr;
    t100 = 1.0+a*p-a*pr+b*t94-2.0*t50*pr+b*t98;
    if (t100 <= 0.0) printERR("d3gdrdt2GMAP", ERR_D3GDRDT2_GMAP_1, "t100", t100)
    t101 = log(t100);
    t120 = t37*p;
    t124 = (1.0+a*t8)/(1.0-a*t8);
    t139 = t37*pr;
    if (t56/t124 <= 0.0) printERR("d3gdrdt2GMAP", ERR_D3GDRDT2_GMAP_2, "t56/t124", t56/t124)
    return(t49*log(t56/t124)/2.0+t61*((dadr+2.0*t62-2.0*dbdr*pr)*t8-t54*t17*t22/2.0)/(1.0-t73
*t74)+(-t79*dbdr/2.0+t37*d3v1drdt2/2.0+t3*d2v1dt2*t5*dbdr-t15*d3v1drdt2*t5/2.0-
t79*t20)*t101+(t37*d2v1dt2/2.0-t79*t5/2.0)*(dadr*p-dadr*pr+dbdr*t94-2.0*t62*pr+
dbdr*t98)/t100+p*d3v0drdt2-t15*p*t34+t120*t43+t120*t46-t61*(dadr*t8-a*
t17*t22/2.0)/(1.0-t5*t74)-pr*d3v0drdt2+t15*pr*t34-t139*t43-t139*t46);
  }
}

static 
double d2gdt2LMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dt,double dv1dt,double d2v0dt2,double d2v1dt2)
{
  double t1;
  double t12;
  double t14;
  double t17;
  double t18;
  double t2;
  double t24;
  double t33;
  double t37;
  double t4;
  double t40;
  double t46;
  double t6;
  double t7;
  {
    t1 = b*b;
    t2 = 1/t1;
    t4 = a*a;
    t6 = sqrt(4.0*b-t4);
    t7 = 1/t6;
    t12 = 1/b;
    t14 = d2v1dt2*a;
    t17 = t2*t7*d2v1dt2*t4*a-3.0*t12*t7*t14;
    t18 = b*p;
    t24 = atan((a+2.0*t18-2.0*b*pr)*t7);
    t33 = p*p;
    t37 = pr*pr;
    t40 = log(1.0+a*p-a*pr+b*t33-2.0*t18*pr+b*t37);
    t46 = atan(a*t7);
    return(t17*t24+(t12*d2v1dt2/2.0-t2*d2v1dt2*t4/2.0)*t40+p*d2v0dt2+t12*p*t14-
t17*t46-pr*d2v0dt2-t12*pr*t14);
  }
}

static 
double d2gdt2GMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dt,double dv1dt,double d2v0dt2,double d2v1dt2)
{
  double t1;
  double t12;
  double t14;
  double t17;
  double t18;
  double t2;
  double t24;
  double t33;
  double t37;
  double t4;
  double t40;
  double t46;
  double t6;
  double t7;
  {
    t1 = b*b;
    t2 = 1/t1;
    t4 = a*a;
    t6 = sqrt(-4.0*b+t4);
    t7 = 1/t6;
    t12 = 1/b;
    t14 = d2v1dt2*a;
    t17 = -t2*t7*d2v1dt2*t4*a+3.0*t12*t7*t14;
    t18 = b*p;
    t24 = (1.0+(a+2.0*t18-2.0*b*pr)*t7)/(1.0-(a+2.0*t18-2.0*b*pr)*t7);
    t33 = p*p;
    t37 = pr*pr;
    t40 = log(1.0+a*p-a*pr+b*t33-2.0*t18*pr+b*t37);
    t46 = (1.0+a*t7)/(1.0-a*t7);
    if (t24/t46 <= 0.0) printERR("d2gdt2GMAP", ERR_D2GDT2_GMAP, "t24/t46", t24/t46)
    return(t17*log(t24/t46)/2.0+(t12*d2v1dt2/2.0-t2*d2v1dt2*t4/2.0)*t40+p*d2v0dt2+t12*p*t14-pr*d2v0dt2-t12*pr*t14);
  }
}

static 
double d3gdt3LMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dt,double dv1dt,double d2v0dt2,double d2v1dt2,
double d3v0dt3,double d3v1dt3)
{
  double t1;
  double t12;
  double t14;
  double t17;
  double t18;
  double t2;
  double t24;
  double t33;
  double t37;
  double t4;
  double t40;
  double t46;
  double t6;
  double t7;
  {
    t1 = b*b;
    t2 = 1/t1;
    t4 = a*a;
    t6 = sqrt(4.0*b-t4);
    t7 = 1/t6;
    t12 = 1/b;
    t14 = d3v1dt3*a;
    t17 = t2*t7*d3v1dt3*t4*a-3.0*t12*t7*t14;
    t18 = b*p;
    t24 = atan((a+2.0*t18-2.0*b*pr)*t7);
    t33 = p*p;
    t37 = pr*pr;
    t40 = log(1.0+a*p-a*pr+b*t33-2.0*t18*pr+b*t37);
    t46 = atan(a*t7);
    return(t17*t24+(t12*d3v1dt3/2.0-t2*d3v1dt3*t4/2.0)*t40+p*d3v0dt3+t12*p*t14-
t17*t46-pr*d3v0dt3-t12*pr*t14);
  }
}

static 
double d3gdt3GMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dt,double dv1dt,double d2v0dt2,double d2v1dt2,
double d3v0dt3,double d3v1dt3)
{
  double t1;
  double t12;
  double t14;
  double t17;
  double t18;
  double t2;
  double t24;
  double t33;
  double t37;
  double t4;
  double t40;
  double t46;
  double t6;
  double t7;
  {
    t1 = b*b;
    t2 = 1/t1;
    t4 = a*a;
    t6 = sqrt(-4.0*b+t4);
    t7 = 1/t6;
    t12 = 1/b;
    t14 = d3v1dt3*a;
    t17 = -t2*t7*d3v1dt3*t4*a+3.0*t12*t7*t14;
    t18 = b*p;
    t24 = (1.0+(a+2.0*t18-2.0*b*pr)*t7)/(1.0-(a+2.0*t18-2.0*b*pr)*t7);
    t33 = p*p;
    t37 = pr*pr;
    t40 = log(1.0+a*p-a*pr+b*t33-2.0*t18*pr+b*t37);
    t46 = (1.0+a*t7)/(1.0-a*t7);
    if (t24/t46 <= 0.0) printERR("d3gdt3GMAP", ERR_D3GDT3_GMAP, "t24/t46", t24/t46)
    return(t17*log(t24/t46)/2.0+(t12*d3v1dt3/2.0-t2*d3v1dt3*t4/2.0)*t40+p*d3v0dt3+t12*p*t14-pr*d3v0dt3-t12*pr*t14);
  }
}

static 
double d2gdr2LMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr,
double dv0ds,double dv1ds,double dv2ds,double dads,double dbds,double d2v0dr2,
double d2v1dr2,double d2v2dr2,double d2adr2,double d2bdr2)
{
  double t1;
  double t10;
  double t103;
  double t104;
  double t105;
  double t106;
  double t107;
  double t110;
  double t111;
  double t114;
  double t115;
  double t118;
  double t120;
  double t121;
  double t122;
  double t126;
  double t13;
  double t130;
  double t132;
  double t136;
  double t142;
  double t145;
  double t148;
  double t155;
  double t158;
  double t16;
  double t161;
  double t165;
  double t170;
  double t171;
  double t174;
  double t179;
  double t18;
  double t180;
  double t182;
  double t183;
  double t197;
  double t207;
  double t21;
  double t218;
  double t221;
  double t224;
  double t228;
  double t232;
  double t241;
  double t253;
  double t255;
  double t257;
  double t261;
  double t263;
  double t265;
  double t271;
  double t275;
  double t278;
  double t28;
  double t281;
  double t282;
  double t290;
  double t292;
  double t293;
  double t311;
  double t315;
  double t316;
  double t319;
  double t32;
  double t322;
  double t325;
  double t326;
  double t327;
  double t33;
  double t330;
  double t35;
  double t356;
  double t367;
  double t380;
  double t395;
  double t396;
  double t397;
  double t4;
  double t402;
  double t412;
  double t416;
  double t417;
  double t421;
  double t424;
  double t43;
  double t44;
  double t447;
  double t45;
  double t450;
  double t453;
  double t456;
  double t459;
  double t461;
  double t47;
  double t475;
  double t478;
  double t483;
  double t498;
  double t5;
  double t50;
  double t502;
  double t503;
  double t509;
  double t517;
  double t52;
  double t520;
  double t524;
  double t53;
  double t537;
  double t539;
  double t541;
  double t544;
  double t550;
  double t552;
  double t555;
  double t56;
  double t564;
  double t569;
  double t576;
  double t6;
  double t614;
  double t646;
  double t648;
  double t65;
  double t652;
  double t661;
  double t670;
  double t69;
  double t7;
  double t76;
  double t78;
  double t81;
  double t83;
  double t86;
  double t95;
  double t99;
  {
    t1 = 1/b;
    t4 = b*b;
    t5 = 1/t4;
    t6 = t5*v1;
    t7 = a*a;
    t10 = t5*v2;
    t13 = t1*v1/2.0-t6*t7/2.0-t10*a/4.0;
    t16 = p*p;
    t18 = d2bdr2*p;
    t21 = pr*pr;
    t28 = b*p;
    t32 = 1.0+a*p-a*pr+b*t16-2.0*t28*pr+b*t21;
    t33 = 1/t32;
    t35 = t1*p;
    t43 = 1/t4/b;
    t44 = t43*v1;
    t45 = t7*dbdr;
    t47 = t5*dv1dr;
    t50 = a*dadr;
    t52 = t43*v2;
    t53 = a*dbdr;
    t56 = t5*dv2dr;
    t65 = dbds*p;
    t69 = dads*p-dads*pr+dbds*t16-2.0*t65*pr+dbds*t21;
    t76 = t7*dbds;
    t78 = t5*dv1ds;
    t81 = a*dads;
    t83 = a*dbds;
    t86 = t5*dv2ds;
    t95 = dbdr*p;
    t99 = dadr*p-dadr*pr+dbdr*t16-2.0*t95*pr+dbdr*t21;
    t103 = 4.0*b-t7;
    t104 = sqrt(t103);
    t105 = 1/t104;
    t106 = t5*t105;
    t107 = v2*dbdr;
    t110 = 1/t104/t103;
    t111 = t1*t110;
    t114 = 4.0*dbdr-2.0*t50;
    t115 = v2*t114;
    t118 = t1*t105;
    t120 = t43*t105;
    t121 = a*t7;
    t122 = v1*t121;
    t126 = t5*t110;
    t130 = dv1dr*t121;
    t132 = v1*t7;
    t136 = v2*t7;
    t142 = dv2dr*t7;
    t145 = v2*a;
    t148 = v1*a;
    t155 = dv1dr*a;
    t158 = v1*dadr;
    t161 = t106*t107+t111*t115/2.0-t118*dv2dr-2.0*t120*t122*dbdr-t126*t122*t114
/2.0+t106*t130+3.0*t106*t132*dadr-t120*t136*dbdr-t126*t136*t114/4.0+t106*t142/
2.0+t106*t145*dadr+3.0*t106*t148*dbdr+3.0/2.0*t111*t148*t114-3.0*t118*t155-3.0*
t118*t158;
    t165 = dads+2.0*t65-2.0*dbds*pr;
    t170 = a+2.0*t28-2.0*b*pr;
    t171 = t170*t110;
    t174 = 4.0*dbds-2.0*t81;
    t179 = t170*t170;
    t180 = 1/t103;
    t182 = 1.0+t179*t180;
    t183 = 1/t182;
    t197 = dv1ds*t121;
    t207 = dv2ds*t7;
    t218 = dv1ds*a;
    t221 = v1*dads;
    t224 = t106*v2*dbds+t111*v2*t174/2.0-t118*dv2ds-2.0*t120*t122*dbds-t126*
t122*t174/2.0+t106*t197+3.0*t106*t132*dads-t120*t136*dbds-t126*t136*t174/4.0+
t106*t207/2.0+t106*t145*dads+3.0*t106*t148*dbds+3.0/2.0*t111*t148*t174-3.0*t118
*t218-3.0*t118*t221;
    t228 = dadr+2.0*t95-2.0*dbdr*pr;
    t232 = t228*t105-t171*t114/2.0;
    t241 = -t118*v2+t106*t122+t106*t136/2.0-3.0*t118*t148;
    t253 = t103*t103;
    t255 = 1/t104/t253;
    t257 = t114*t174;
    t261 = dads*dadr;
    t263 = a*d2adr2;
    t265 = 4.0*d2bdr2-2.0*t261-2.0*t263;
    t271 = t1*pr;
    t275 = a*t110;
    t278 = dadr*t105-t275*t114/2.0;
    t281 = 1.0+t7*t180;
    t282 = 1/t281;
    t290 = v1*d2adr2;
    t292 = t13*(d2adr2*p-d2adr2*pr+d2bdr2*t16-2.0*t18*pr+d2bdr2*t21)*t33+t35*
d2v2dr2/2.0+(-t6*dbdr/2.0+t1*dv1dr/2.0+t44*t45-t47*t7/2.0-t6*t50+t52*t53/2.0-
t56*a/4.0-t10*dadr/4.0)*t69*t33+(-t6*dbds/2.0+t1*dv1ds/2.0+t44*t76-t78*t7/2.0-
t6*t81+t52*t83/2.0-t86*a/4.0-t10*dads/4.0)*t99*t33+t161*(t165*t105-t171*t174/
2.0)*t183+t224*t232*t183+t241*((d2adr2+2.0*t18-2.0*d2bdr2*pr)*t105-t228*t110*
t174/2.0-t165*t110*t114/2.0+3.0/4.0*t170*t255*t257-t171*t265/2.0)*t183-t271*
d2v2dr2/2.0-t224*t278*t282-t161*(dads*t105-t275*t174/2.0)*t282+t35*t290;
    t293 = dv1dr*dads;
    t311 = t32*t32;
    t315 = t5*p;
    t316 = v2*d2bdr2;
    t319 = dv2ds*dbdr;
    t322 = d2v1dr2*a;
    t325 = t43*t110;
    t326 = t325*v1;
    t327 = t121*dbdr;
    t330 = t120*v1;
    t356 = dv2dr*dbds;
    t367 = -t118*d2v2dr2+t326*t327*t174-6.0*t330*t45*dads-t120*t207*dbdr-t126*
t136*t265/4.0+3.0*t106*t132*d2adr2-t120*t136*d2bdr2-t126*t207*t114/4.0+t106*
t319+3.0*t106*dv1ds*t7*dadr+t106*t316+t111*dv2ds*t114/2.0+t106*t356+t111*dv2dr*
t174/2.0+t106*d2v1dr2*t121+3.0*t106*dv1dr*t7*dads;
    t380 = dv1ds*dadr;
    t395 = t4*t4;
    t396 = 1/t395;
    t397 = t396*t105;
    t402 = t7*dadr;
    t412 = t1*t255;
    t416 = t126*v1;
    t417 = t7*t114;
    t421 = t107*dbds;
    t424 = -3.0*t118*t290+t106*d2v2dr2*t7/2.0-3.0*t118*t322-2.0*t120*t130*dbds
-3.0*t118*t293-3.0*t118*t380-t126*t130*t174/2.0+t111*v2*t265/2.0-t126*t122*t265
/2.0-2.0*t120*t122*d2bdr2+6.0*t397*v1*t327*dbds-6.0*t330*t402*dbds-t126*t197*
t114/2.0-2.0*t120*t197*dbdr-3.0/4.0*t412*t115*t174-3.0/2.0*t416*t417*dads-2.0*
t120*t421;
    t447 = t158*dbds;
    t450 = t155*dbds;
    t453 = t221*dbdr;
    t456 = t148*d2bdr2;
    t459 = t5*t255;
    t461 = t121*t114;
    t475 = t218*dbdr;
    t478 = -t126*t107*t174/2.0-t126*t115*dbds/2.0+3.0/2.0*t111*t158*t174+3.0/
2.0*t111*t155*t174+3.0/2.0*t111*t148*t265+3.0/2.0*t111*t218*t114+3.0/2.0*t111*
t221*t114+3.0*t106*t447+3.0*t106*t450+3.0*t106*t453+3.0*t106*t456+3.0/4.0*t459*
v1*t461*t174+t326*t461*dbds+t106*dv2ds*a*dadr+t106*v2*dads*dadr+t106*t145*
d2adr2+3.0*t106*t475;
    t483 = a*t114;
    t498 = t126*v2;
    t502 = t120*v2;
    t503 = t50*dbds;
    t509 = t53*dbds;
    t517 = t45*dbds;
    t520 = t325*v2;
    t524 = t53*dads;
    t537 = -t126*t142*t174/4.0-9.0/4.0*t412*v1*t483*t174-t120*t142*dbds+t106*
dv2dr*a*dads-3.0/2.0*t416*t53*t174-3.0/2.0*t416*t483*dbds-t498*t483*dads/2.0
-2.0*t502*t503-t498*t50*t174/2.0-6.0*t330*t509+6.0*t106*v1*t50*dads+3.0*t397*v2
*t517+t520*t45*t174/2.0-2.0*t502*t524+t520*t417*dbds/2.0+3.0/8.0*t459*v2*t417*
t174-3.0/2.0*t416*t402*t174;
    t539 = t367+t424+t478+t537;
    t541 = atan(t170*t105);
    t544 = atan(a*t105);
    t550 = t43*pr;
    t552 = t35*t293-t241*(d2adr2*t105-dadr*t110*t174/2.0-dads*t110*t114/2.0+3.0
/4.0*a*t255*t257-t275*t265/2.0)*t282-t13*t99/t311*t69-t315*t316/2.0-t315*t319/
2.0+t35*t322+t539*t541-t539*t544+t35*t380-t315*t356/2.0-t271*t293-t550*t421;
    t555 = t5*pr;
    t564 = t182*t182;
    t569 = 1/t253;
    t576 = t281*t281;
    t614 = -t56*dads/4.0-t86*dadr/4.0-t10*d2adr2/4.0-t78*dbdr/2.0-t6*d2bdr2/2.0
-t47*dbds/2.0-t5*d2v1dr2*t7/2.0-t5*d2v2dr2*a/4.0+t43*dv1ds*t45+t44*dbdr*dbds-
t47*t81-t78*t50+t44*t7*d2bdr2;
    t646 = t52*dadr*dbds/2.0+t43*dv2ds*t53/2.0+t52*dads*dbdr/2.0+t52*a*d2bdr2/
2.0+t43*dv2dr*t83/2.0-t6*t261-t6*t263+t43*dv1dr*t76-3.0*t396*v1*t517+2.0*t44*
t524+2.0*t44*t503-3.0/2.0*t396*v2*t509+t1*d2v1dr2/2.0;
    t648 = log(t32);
    t652 = -t271*t322+t555*t319/2.0+t555*t316/2.0+t555*t356/2.0-t271*t380-t241*
t232/t564*(2.0*t170*t180*t165-t179*t569*t174)+t241*t278/t576*(2.0*a*t180*dads-
t7*t569*t174)+t555*t447-t271*t290+(t614+t646)*t648+t555*t475+t555*t456;
    t661 = t43*p;
    t670 = t555*t453+p*d2v0dr2-2.0*t550*v1*t509+t555*t450-t315*t475-t315*t450+
t661*t421-t315*t447-t315*t456-t315*t453+2.0*t661*v1*t509-pr*d2v0dr2;
    return(t292+t552+t652+t670);
  }
}

static 
double d2gdr2GMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr,
double dv0ds,double dv1ds,double dv2ds,double dads,double dbds,double d2v0dr2,
double d2v1dr2,double d2v2dr2,double d2adr2,double d2bdr2)
{
  double t1;
  double t101;
  double t106;
  double t107;
  double t111;
  double t115;
  double t12;
  double t126;
  double t13;
  double t132;
  double t135;
  double t139;
  double t143;
  double t145;
  double t148;
  double t15;
  double t152;
  double t153;
  double t161;
  double t164;
  double t165;
  double t168;
  double t17;
  double t172;
  double t181;
  double t183;
  double t184;
  double t186;
  double t190;
  double t194;
  double t200;
  double t206;
  double t209;
  double t21;
  double t210;
  double t214;
  double t218;
  double t222;
  double t223;
  double t224;
  double t227;
  double t234;
  double t237;
  double t24;
  double t241;
  double t262;
  double t27;
  double t271;
  double t273;
  double t275;
  double t28;
  double t29;
  double t3;
  double t30;
  double t310;
  double t311;
  double t315;
  double t317;
  double t321;
  double t322;
  double t327;
  double t328;
  double t33;
  double t330;
  double t331;
  double t339;
  double t348;
  double t35;
  double t351;
  double t357;
  double t358;
  double t37;
  double t395;
  double t399;
  double t4;
  double t402;
  double t406;
  double t410;
  double t412;
  double t417;
  double t42;
  double t429;
  double t432;
  double t437;
  double t438;
  double t44;
  double t440;
  double t444;
  double t445;
  double t448;
  double t451;
  double t457;
  double t461;
  double t463;
  double t471;
  double t472;
  double t48;
  double t480;
  double t484;
  double t496;
  double t5;
  double t50;
  double t502;
  double t514;
  double t517;
  double t52;
  double t520;
  double t521;
  double t525;
  double t532;
  double t547;
  double t549;
  double t554;
  double t557;
  double t58;
  double t588;
  double t6;
  double t61;
  double t619;
  double t62;
  double t621;
  double t63;
  double t631;
  double t640;
  double t670;
  double t68;
  double t7;
  double t72;
  double t73;
  double t74;
  double t76;
  double t8;
  double t80;
  double t87;
  double t93;
  double t97;
  double t98;
  {
    t1 = 1/b;
    t3 = a*a;
    t4 = -4.0*b+t3;
    t5 = sqrt(t4);
    t6 = 1/t5;
    t7 = t1*t6;
    t8 = d2v1dr2*a;
    t12 = 1/t5/t4;
    t13 = t1*t12;
    t15 = a*dads;
    t17 = -4.0*dbds+2.0*t15;
    t21 = v1*d2adr2;
    t24 = dv1ds*dadr;
    t27 = b*b;
    t28 = 1/t27;
    t29 = t28*t6;
    t30 = dv2dr*dbds;
    t33 = dads*dadr;
    t35 = a*d2adr2;
    t37 = -4.0*d2bdr2+2.0*t33+2.0*t35;
    t42 = a*dadr;
    t44 = -4.0*dbdr+2.0*t42;
    t48 = v2*d2bdr2;
    t50 = dv2ds*dbdr;
    t52 = dv1dr*dads;
    t58 = t3*a;
    t61 = t28*t12;
    t62 = t61*v1;
    t63 = a*t44;
    t68 = dv2dr*t3;
    t72 = t27*t27;
    t73 = 1/t72;
    t74 = t73*t6;
    t76 = t58*dbdr;
    t80 = 3.0*t7*t8-t13*dv2dr*t17/2.0+3.0*t7*t21+3.0*t7*t24-t29*t30-t13*v2*t37/
2.0-t13*dv2ds*t44/2.0-t29*t48-t29*t50+3.0*t7*t52-t29*d2v2dr2*t3/2.0-t29*d2v1dr2
*t58+3.0/2.0*t62*t63*dbds+t7*d2v2dr2+t61*t68*t17/4.0-6.0*t74*v1*t76*dbds;
    t87 = v2*a;
    t93 = v1*t58;
    t97 = v1*a;
    t98 = t97*d2bdr2;
    t101 = dv1ds*t58;
    t106 = 1/t27/b;
    t107 = t106*t6;
    t111 = dv1dr*t58;
    t115 = dv1ds*a;
    t126 = t115*dbdr;
    t132 = v2*t3;
    t135 = v1*dads;
    t139 = dv1dr*a;
    t143 = -t29*dv2dr*a*dads-t29*dv2ds*a*dadr-t29*t87*d2adr2-t29*v2*dads*dadr+
t61*t93*t37/2.0-3.0*t29*t98+t61*t101*t44/2.0+2.0*t107*t101*dbdr+t61*t111*t17/
2.0-3.0/2.0*t13*t115*t44-3.0*t29*dv1dr*t3*dads+2.0*t107*t111*dbds-3.0*t29*t126
-3.0/2.0*t13*t97*t37+t107*t132*d2bdr2-3.0/2.0*t13*t135*t44-3.0/2.0*t13*t139*t17
;
    t145 = dv2ds*t3;
    t148 = v1*t3;
    t152 = t107*v1;
    t153 = t3*dbdr;
    t161 = t135*dbdr;
    t164 = t106*t12;
    t165 = t164*v1;
    t168 = t3*dadr;
    t172 = v2*t44;
    t181 = t4*t4;
    t183 = 1/t5/t181;
    t184 = t28*t183;
    t186 = t58*t44;
    t190 = v2*dbdr;
    t194 = t190*dbds;
    t200 = v1*dadr;
    t206 = t139*dbds;
    t209 = t107*t145*dbdr-3.0*t29*t148*d2adr2+6.0*t152*t153*dads-3.0*t29*dv1ds*
t3*dadr-3.0*t29*t161-t165*t76*t17+6.0*t152*t168*dbds+t61*t172*dbds/2.0+t107*t68
*dbds+t61*t145*t44/4.0-3.0/4.0*t184*v1*t186*t17+t61*t190*t17/2.0+2.0*t107*t194+
t61*t132*t37/4.0-3.0/2.0*t13*t200*t17-t165*t186*dbds-3.0*t29*t206;
    t210 = t200*dbds;
    t214 = t3*t44;
    t218 = t164*v2;
    t222 = t107*v2;
    t223 = a*dbdr;
    t224 = t223*dads;
    t227 = t223*dbds;
    t234 = t153*dbds;
    t237 = t61*v2;
    t241 = t1*t183;
    t262 = t42*dbds;
    t271 = -3.0*t29*t210-3.0/8.0*t184*v2*t214*t17-t218*t214*dbds/2.0+2.0*t222*
t224+6.0*t152*t227-t218*t153*t17/2.0-3.0*t74*v2*t234+t237*t42*t17/2.0+9.0/4.0*
t241*v1*t63*t17+3.0/2.0*t62*t214*dads+3.0/2.0*t62*t168*t17-6.0*t29*v1*t42*dads+
3.0/4.0*t241*t172*t17+2.0*t107*t93*d2bdr2+2.0*t222*t262+t237*t63*dads/2.0+3.0/
2.0*t62*t223*t17;
    t273 = t80+t143+t209+t271;
    t275 = (1.0+a*t6)/(1.0-a*t6);
    t310 = -t29*t190-t13*t172/2.0+t7*dv2dr+2.0*t107*t93*dbdr+t61*t93*t44/2.0-
t29*t111-3.0*t29*t148*dadr+t107*t132*dbdr+t61*t132*t44/4.0-t29*t68/2.0-t29*t87*
dadr-3.0*t29*t97*dbdr-3.0/2.0*t13*t97*t44+3.0*t7*t139+3.0*t7*t200;
    t311 = dbds*p;
    t315 = dads+2.0*t311-2.0*dbds*pr;
    t317 = b*p;
    t321 = a+2.0*t317-2.0*b*pr;
    t322 = t321*t12;
    t327 = t321*t321;
    t328 = 1/t4;
    t330 = 1.0-t327*t328;
    t331 = 1/t330;
    t339 = t7*v2-t29*t93-t29*t132/2.0+3.0*t7*t97;
    t348 = t44*t17;
    t351 = a*t12;
    t357 = 1.0-t3*t328;
    t358 = 1/t357;
    t395 = -t29*v2*dbds-t13*v2*t17/2.0+t7*dv2ds+2.0*t107*t93*dbds+t61*t93*t17/
2.0-t29*t101-3.0*t29*t148*dads+t107*t132*dbds+t61*t132*t17/4.0-t29*t145/2.0-t29
*t87*dads-3.0*t29*t97*dbds-3.0/2.0*t13*t97*t17+3.0*t7*t115+3.0*t7*t135;
    t399 = dadr*t6-t351*t44/2.0;
    t402 = dbdr*p;
    t406 = dadr+2.0*t402-2.0*dbdr*pr;
    t410 = t406*t6-t322*t44/2.0;
    t412 = t330*t330;
    t417 = 1/t181;
    t429 = t1*pr;
    t432 = t28*v1;
    t437 = t106*v1;
    t438 = t3*dbds;
    t440 = t28*dv1ds;
    t444 = t106*v2;
    t445 = a*dbds;
    t448 = t28*dv2ds;
    t451 = t28*v2;
    t457 = p*p;
    t461 = pr*pr;
    t463 = dadr*p-dadr*pr+dbdr*t457-2.0*t402*pr+dbdr*t461;
    t471 = 1.0+a*p-a*pr+b*t457-2.0*t317*pr+b*t461;
    t472 = 1/t471;
    t480 = t1*v1/2.0-t432*t3/2.0-t451*a/4.0;
    t484 = d2bdr2*p;
    t496 = t28*dv1dr;
    t502 = t28*dv2dr;
    t514 = dads*p-dads*pr+dbds*t457-2.0*t311*pr+dbds*t461;
    t517 = t1*p;
    t520 = t310*(t315*t6-t322*t17/2.0)*t331-t339*(d2adr2*t6-dadr*t12
*t17/2.0-dads*t12*t44/2.0+3.0/4.0*a*t183*t348-t351*t37/2.0)*t358-t395*t399*t358
-t339*t410/t412*(-2.0*t321*t328*t315+t327*t417*t17)-t310*(dads*t6-t351*t17/2.0)
*t358-t429*d2v2dr2/2.0+(-t432*dbds/2.0+t1*dv1ds/2.0+t437*t438-t440*t3/2.0-t432*
t15+t444*t445/2.0-t448*a/4.0-t451*dads/4.0)*t463*t472+t480*(d2adr2*p-d2adr2*pr+
d2bdr2*t457-2.0*t484*pr+d2bdr2*t461)*t472+(-t432*dbdr/2.0+t1*dv1dr/2.0+t437*
t153-t496*t3/2.0-t432*t42+t444*t223/2.0-t502*a/4.0-t451*dadr/4.0)*t514*t472+
t517*d2v2dr2/2.0;
    t521 = t28*pr;
    t525 = t28*p;
    t532 = t357*t357;
    t547 = t521*t50/2.0-t429*t24-t525*t50/2.0+t517*t52+t517*t21+t517*t24+t339*
t399/t532*(-2.0*a*t328*dads+t3*t417*t17)+t521*t210+t521*t206+t521*t98+t521*t161
+t521*t126;
    t549 = t106*pr;
    t554 = (1.0+t321*t6)/(1.0-t321*t6);
    t557 = t471*t471;
    t588 = t106*dv2dr*t445/2.0-t440*t42-t496*t15+t106*dv1dr*t438+t444*dadr*dbds
/2.0-t432*t35-t432*t33+t437*t3*d2bdr2+t106*dv1ds*t153+t444*a*d2bdr2/2.0+t444*
dads*dbdr/2.0+t106*dv2ds*t223/2.0+t437*dbdr*dbds;
    t619 = -t432*d2bdr2/2.0-t496*dbds/2.0-t502*dads/4.0-t451*d2adr2/4.0+t1*
d2v1dr2/2.0-t448*dadr/4.0+2.0*t437*t262-t440*dbdr/2.0-t28*d2v1dr2*t3/2.0-t28*
d2v2dr2*a/4.0+2.0*t437*t224-3.0/2.0*t73*v2*t227-3.0*t73*v1*t234;
    t621 = log(t471);
    if (t554/t275 <= 0.0) printERR("d2gdr2GMAP", ERR_D2GDR2_GMAP, "t554/t275", t554/t275)
    t631 = -2.0*t549*v1*t227+t273*log(t554/t275)/2.0+-t480*t463/t557*t514+(t588+t619)*t621+p*
d2v0dr2-t429*t8-t429*t52-t429*t21+t517*t8-t525*t206-t525*t98-t525*t161;
    t640 = t106*p;
    t670 = -t525*t126+t521*t48/2.0+t521*t30/2.0-t525*t30/2.0-t525*t210+t640*
t194+2.0*t640*v1*t227-t525*t48/2.0-t549*t194+t339*((d2adr2+2.0*t484-2.0*d2bdr2*
pr)*t6-t406*t12*t17/2.0-t315*t12*t44/2.0+3.0/4.0*t321*t183*t348-t322*t37/2.0)*
t331+t395*t410*t331-pr*d2v0dr2;
    return(t520+t547+t631+t670);
  }
}

static 
double d3gdr2dtLMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr,
double dv0ds,double dv1ds,double dv2ds,double dads,double dbds,double d2v0dr2,
double d2v1dr2,double d2v2dr2,double d2adr2,double d2bdr2,double dv0dt,
double dv1dt,double d2v0drdt,double d2v1drdt,double d2v0dsdt,double d2v1dsdt,
double d3v0dr2dt,double d3v1dr2dt)
{
  double t1;
  double t10;
  double t106;
  double t107;
  double t11;
  double t115;
  double t126;
  double t129;
  double t132;
  double t134;
  double t140;
  double t141;
  double t146;
  double t149;
  double t15;
  double t150;
  double t155;
  double t157;
  double t162;
  double t166;
  double t169;
  double t17;
  double t173;
  double t174;
  double t177;
  double t179;
  double t18;
  double t180;
  double t182;
  double t184;
  double t186;
  double t188;
  double t190;
  double t196;
  double t198;
  double t20;
  double t205;
  double t207;
  double t213;
  double t214;
  double t22;
  double t226;
  double t230;
  double t232;
  double t234;
  double t238;
  double t240;
  double t242;
  double t26;
  double t27;
  double t273;
  double t29;
  double t3;
  double t319;
  double t33;
  double t338;
  double t339;
  double t343;
  double t344;
  double t349;
  double t350;
  double t365;
  double t37;
  double t38;
  double t400;
  double t401;
  double t407;
  double t408;
  double t410;
  double t413;
  double t416;
  double t42;
  double t421;
  double t43;
  double t46;
  double t460;
  double t461;
  double t464;
  double t476;
  double t49;
  double t5;
  double t50;
  double t54;
  double t56;
  double t6;
  double t60;
  double t61;
  double t63;
  double t65;
  double t68;
  double t7;
  double t70;
  double t71;
  double t73;
  double t74;
  double t77;
  double t8;
  double t82;
  double t83;
  double t85;
  double t9;
  double t92;
  double t96;
  double t98;
  {
    t1 = b*b;
    t3 = 1/t1/b;
    t5 = a*a;
    t6 = 4.0*b-t5;
    t7 = sqrt(t6);
    t8 = 1/t7;
    t9 = t3*t8;
    t10 = t5*a;
    t11 = dv1dt*t10;
    t15 = 1/t1;
    t17 = 1/t7/t6;
    t18 = t15*t17;
    t20 = a*dads;
    t22 = 4.0*dbds-2.0*t20;
    t26 = t15*t8;
    t27 = d2v1dsdt*t10;
    t29 = dv1dt*t5;
    t33 = dv1dt*a;
    t37 = 1/b;
    t38 = t37*t17;
    t42 = t37*t8;
    t43 = d2v1dsdt*a;
    t46 = dv1dt*dads;
    t49 = -2.0*t9*t11*dbds-t18*t11*t22/2.0+t26*t27+3.0*t26*t29*dads+3.0*t26*t33
*dbds+3.0/2.0*t38*t33*t22-3.0*t42*t43-3.0*t42*t46;
    t50 = dbdr*p;
    t54 = dadr+2.0*t50-2.0*dbdr*pr;
    t56 = b*p;
    t60 = a+2.0*t56-2.0*b*pr;
    t61 = t60*t17;
    t63 = a*dadr;
    t65 = 4.0*dbdr-2.0*t63;
    t68 = t54*t8-t61*t65/2.0;
    t70 = t60*t60;
    t71 = 1/t6;
    t73 = 1.0+t70*t71;
    t74 = 1/t73;
    t77 = t15*dv1dt;
    t82 = t3*dv1dt;
    t83 = t5*dbds;
    t85 = t15*d2v1dsdt;
    t92 = p*p;
    t96 = pr*pr;
    t98 = dadr*p-dadr*pr+dbdr*t92-2.0*t50*pr+dbdr*t96;
    t106 = 1.0+a*p-a*pr+b*t92-2.0*t56*pr+b*t96;
    t107 = 1/t106;
    t115 = d2v1drdt*t10;
    t126 = d2v1drdt*a;
    t129 = dv1dt*dadr;
    t132 = -2.0*t9*t11*dbdr-t18*t11*t65/2.0+t26*t115+3.0*t26*t29*dadr+3.0*t26*
t33*dbdr+3.0/2.0*t38*t33*t65-3.0*t42*t126-3.0*t42*t129;
    t134 = a*t17;
    t140 = 1.0+t5*t71;
    t141 = 1/t140;
    t146 = dadr*t8-t134*t65/2.0;
    t149 = t15*p;
    t150 = t43*dbdr;
    t155 = t37*dv1dt/2.0-t77*t5/2.0;
    t157 = t106*t106;
    t162 = dbds*p;
    t166 = dads*p-dads*pr+dbds*t92-2.0*t162*pr+dbds*t96;
    t169 = t33*d2bdr2;
    t173 = a*dbdr;
    t174 = t173*dbds;
    t177 = t46*dbdr;
    t179 = t37*p;
    t180 = dv1dt*d2adr2;
    t182 = t129*dbds;
    t184 = d2v1dsdt*dadr;
    t186 = t126*dbds;
    t188 = d2v1drdt*dads;
    t190 = d3v1dr2dt*a;
    t196 = t5*dbdr;
    t198 = t15*d2v1drdt;
    t205 = t37*pr;
    t207 = t49*t68*t74+p*d3v0dr2dt+(-t77*dbds/2.0+t37*d2v1dsdt/2.0+t82*t83-t85*
t5/2.0-t77*t20)*t98*t107-t132*(dads*t8-t134*t22/2.0)*t141-t49*t146*t141-t149*
t150-t155*t98/t157*t166-t149*t169+2.0*t3*p*dv1dt*t174-t149*t177+t179*t180-t149*
t182+t179*t184-t149*t186+t179*t188+t179*t190+(-t77*dbdr/2.0+t37*d2v1drdt/2.0+
t82*t196-t198*t5/2.0-t77*t63)*t166*t107-t205*t188;
    t213 = t26*t11-3.0*t42*t33;
    t214 = d2bdr2*p;
    t226 = dads+2.0*t162-2.0*dbds*pr;
    t230 = t6*t6;
    t232 = 1/t7/t230;
    t234 = t65*t22;
    t238 = dads*dadr;
    t240 = a*d2adr2;
    t242 = 4.0*d2bdr2-2.0*t238-2.0*t240;
    t273 = t15*pr;
    t319 = a*t65;
    t338 = t26*d3v1dr2dt*t10-3.0*t42*t184-3.0*t42*t188-3.0*t42*t180-3.0*t42*
t190+3.0/2.0*t38*t129*t22+3.0/2.0*t38*t43*t65+3.0/2.0*t38*t33*t242+3.0*t26*t186
+3.0/2.0*t38*t46*t65+3.0/2.0*t38*t126*t22+3.0*t26*t182-9.0/4.0*t37*t232*dv1dt*
t319*t22+3.0*t26*t169-2.0*t9*t115*dbds-t18*t11*t242/2.0-t18*t115*t22/2.0+3.0*
t26*d2v1drdt*t5*dads;
    t339 = t18*dv1dt;
    t343 = t9*dv1dt;
    t344 = t5*dadr;
    t349 = t3*t17*dv1dt;
    t350 = t10*t65;
    t365 = t10*dbdr;
    t400 = t1*t1;
    t401 = 1/t400;
    t407 = -3.0/2.0*t339*t319*dbds-6.0*t343*t344*dbds+t349*t350*dbds+3.0/4.0*
t15*t232*dv1dt*t350*t22-3.0/2.0*t339*t5*t65*dads-t18*t27*t65/2.0+t349*t365*t22
-2.0*t9*t11*d2bdr2+3.0*t26*t177-3.0/2.0*t339*t173*t22-2.0*t9*t27*dbdr+3.0*t26*
t150-6.0*t343*t196*dads+3.0*t26*d2v1dsdt*t5*dadr+3.0*t26*t29*d2adr2-3.0/2.0*
t339*t344*t22+6.0*t26*dv1dt*t63*dads-6.0*t343*t174+6.0*t401*t8*dv1dt*t365*dbds;
    t408 = t338+t407;
    t410 = atan(a*t8);
    t413 = atan(t60*t8);
    t416 = t140*t140;
    t421 = 1/t230;
    t460 = t37*d3v1dr2dt/2.0-t198*t20+t3*d2v1drdt*t83+t82*t5*d2bdr2+t3*d2v1dsdt
*t196+t82*dbdr*dbds-t77*t240-t77*t238-t85*t63-t15*d3v1dr2dt*t5/2.0-t198*dbds/
2.0-t77*d2bdr2/2.0-t85*dbdr/2.0+2.0*t82*t63*dbds+2.0*t82*t173*dads-3.0*t401*
dv1dt*t196*dbds;
    t461 = log(t106);
    t464 = t73*t73;
    t476 = -t205*t190-t205*t180+t213*((d2adr2+2.0*t214-2.0*d2bdr2*pr)*t8-t54*
t17*t22/2.0-t226*t17*t65/2.0+3.0/4.0*t60*t232*t234-t61*t242/2.0)*t74+t132*(t226
*t8-t22*t61/2.0)*t74-t213*(d2adr2*t8-dadr*t17*t22/2.0-dads*t17*t65/2.0+3.0/4.0*
a*t232*t234-t134*t242/2.0)*t141-2.0*t3*pr*dv1dt*t174+t273*t186+t273*t182+t273*
t169+t273*t150+t273*t177+t155*(d2adr2*p-d2adr2*pr+d2bdr2*t92-2.0*t214*pr+d2bdr2
*t96)*t107-t408*t410+t408*t413+t213*t146/t416*(2.0*a*t71*dads-t5*t421*t22)+t460
*t461-t213*t68/t464*(2.0*t60*t71*t226-t70*t421*t22)-pr*d3v0dr2dt-t205*t184;
    return(t207+t476);
  }
}

static
double d3gdr2dtGMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr,
double dv0ds,double dv1ds,double dv2ds,double dads,double dbds,double d2v0dr2,
double d2v1dr2,double d2v2dr2,double d2adr2,double d2bdr2,double dv0dt,
double dv1dt,double d2v0drdt,double d2v1drdt,double d2v0dsdt,double d2v1dsdt,
double d3v0dr2dt,double d3v1dr2dt)
{
  double t1;
  double t10;
  double t100;
  double t104;
  double t108;
  double t11;
  double t114;
  double t115;
  double t127;
  double t129;
  double t131;
  double t135;
  double t137;
  double t139;
  double t147;
  double t148;
  double t15;
  double t151;
  double t152;
  double t154;
  double t155;
  double t157;
  double t159;
  double t164;
  double t167;
  double t17;
  double t170;
  double t171;
  double t173;
  double t175;
  double t177;
  double t179;
  double t18;
  double t198;
  double t199;
  double t20;
  double t211;
  double t216;
  double t22;
  double t227;
  double t238;
  double t242;
  double t243;
  double t247;
  double t248;
  double t251;
  double t26;
  double t27;
  double t276;
  double t29;
  double t3;
  double t302;
  double t303;
  double t305;
  double t307;
  double t315;
  double t33;
  double t339;
  double t342;
  double t345;
  double t349;
  double t351;
  double t359;
  double t360;
  double t368;
  double t37;
  double t376;
  double t377;
  double t379;
  double t38;
  double t385;
  double t392;
  double t409;
  double t414;
  double t42;
  double t421;
  double t43;
  double t431;
  double t46;
  double t470;
  double t471;
  double t474;
  double t476;
  double t49;
  double t5;
  double t50;
  double t54;
  double t56;
  double t6;
  double t60;
  double t61;
  double t63;
  double t65;
  double t7;
  double t70;
  double t71;
  double t73;
  double t74;
  double t8;
  double t82;
  double t9;
  double t93;
  double t96;
  double t99;
  {
    t1 = b*b;
    t3 = 1/t1/b;
    t5 = a*a;
    t6 = -4.0*b+t5;
    t7 = sqrt(t6);
    t8 = 1/t7;
    t9 = t3*t8;
    t10 = t5*a;
    t11 = dv1dt*t10;
    t15 = 1/t1;
    t17 = 1/t7/t6;
    t18 = t15*t17;
    t20 = a*dadr;
    t22 = -4.0*dbdr+2.0*t20;
    t26 = t15*t8;
    t27 = d2v1drdt*t10;
    t29 = dv1dt*t5;
    t33 = dv1dt*a;
    t37 = 1/b;
    t38 = t37*t17;
    t42 = t37*t8;
    t43 = d2v1drdt*a;
    t46 = dv1dt*dadr;
    t49 = 2.0*t9*t11*dbdr+t18*t11*t22/2.0-t26*t27-3.0*t26*t29*dadr-3.0*t26*t33*
dbdr-3.0/2.0*t38*t33*t22+3.0*t42*t43+3.0*t42*t46;
    t50 = dbds*p;
    t54 = dads+2.0*t50-2.0*dbds*pr;
    t56 = b*p;
    t60 = a+2.0*t56-2.0*b*pr;
    t61 = t60*t17;
    t63 = a*dads;
    t65 = -4.0*dbds+2.0*t63;
    t70 = t60*t60;
    t71 = 1/t6;
    t73 = 1.0-t70*t71;
    t74 = 1/t73;
    t82 = d2v1dsdt*t10;
    t93 = d2v1dsdt*a;
    t96 = dv1dt*dads;
    t99 = 2.0*t9*t11*dbds+t18*t11*t65/2.0-t26*t82-3.0*t26*t29*dads-3.0*t26*t33*
dbds-3.0/2.0*t38*t33*t65+3.0*t42*t93+3.0*t42*t96;
    t100 = dbdr*p;
    t104 = dadr+2.0*t100-2.0*dbdr*pr;
    t108 = t104*t8-t61*t22/2.0;
    t114 = -t26*t11+3.0*t42*t33;
    t115 = d2bdr2*p;
    t127 = t6*t6;
    t129 = 1/t7/t127;
    t131 = t22*t65;
    t135 = dads*dadr;
    t137 = a*d2adr2;
    t139 = -4.0*d2bdr2+2.0*t135+2.0*t137;
    t147 = a*dbdr;
    t148 = t147*dbds;
    t151 = t15*pr;
    t152 = t46*dbds;
    t154 = t37*pr;
    t155 = d3v1dr2dt*a;
    t157 = d2v1dsdt*dadr;
    t159 = dv1dt*d2adr2;
    t164 = a*t17;
    t167 = dadr*t8-t164*t22/2.0;
    t170 = 1.0-t5*t71;
    t171 = 1/t170;
    t173 = t93*dbdr;
    t175 = d2v1drdt*dads;
    t177 = t43*dbds;
    t179 = t33*d2bdr2;
    t198 = t18*dv1dt;
    t199 = a*t22;
    t211 = t96*dbdr;
    t216 = t10*t22;
    t227 = t3*t17*dv1dt;
    t238 = 3.0*t42*t175+3.0*t42*t155-t26*d3v1dr2dt*t10+3.0*t42*t157+2.0*t9*t27*
dbds-3.0/2.0*t38*t33*t139-3.0/2.0*t38*t96*t22+3.0/2.0*t198*t199*dbds+9.0/4.0*
t37*t129*dv1dt*t199*t65-3.0/2.0*t38*t93*t22-3.0*t26*t211-3.0/4.0*t15*t129*dv1dt
*t216*t65+3.0*t42*t159+3.0/2.0*t198*t5*t22*dads-t227*t216*dbds+2.0*t9*t11*
d2bdr2-3.0*t26*t179+t18*t82*t22/2.0;
    t242 = t9*dv1dt;
    t243 = t5*dbdr;
    t247 = t1*t1;
    t248 = 1/t247;
    t251 = t10*dbdr;
    t276 = t5*dadr;
    t302 = 2.0*t9*t82*dbdr+6.0*t242*t243*dads-6.0*t248*t8*dv1dt*t251*dbds-t227*
t251*t65-3.0/2.0*t38*t43*t65-3.0*t26*t152-3.0*t26*t177-3.0/2.0*t38*t46*t65+6.0*
t242*t148-3.0*t26*t29*d2adr2-6.0*t26*dv1dt*t20*dads+3.0/2.0*t198*t276*t65+3.0/
2.0*t198*t147*t65+6.0*t242*t276*dbds-3.0*t26*t173-3.0*t26*d2v1dsdt*t5*dadr+t18*
t11*t139/2.0-3.0*t26*d2v1drdt*t5*dads+t18*t27*t65/2.0;
    t303 = t238+t302;
    t305 = (1.0+t60*t8)/(1.0-t60*t8);
    t307 = t37*p;
    t315 = t49*(t54*t8-t61*t65/2.0)*t74+t99*t108*t74+t114*((d2adr2+2.0*t115-2.0
*d2bdr2*pr)*t8-t104*t17*t65/2.0-t54*t17*t22/2.0+3.0/4.0*t60*t129*t131-t61*t139/
2.0)*t74-2.0*t3*pr*dv1dt*t148+t151*t152-t154*t155-t154*t157-t154*t159+p*
d3v0dr2dt-pr*d3v0dr2dt-t99*t167*t171+t151*t173-t154*t175+t151*t177+t151*t179
+t307*t157-t49*(dads*t8-t164*t65/2.0)*t171;
    t339 = t15*dv1dt;
    t342 = t37*dv1dt/2.0-t339*t5/2.0;
    t345 = p*p;
    t349 = pr*pr;
    t351 = dadr*p-dadr*pr+dbdr*t345-2.0*t100*pr+dbdr*t349;
    t359 = 1.0+a*p-a*pr+b*t345-2.0*t56*pr+b*t349;
    t360 = t359*t359;
    t368 = dads*p-dads*pr+dbds*t345-2.0*t50*pr+dbds*t349;
    t376 = t3*dv1dt;
    t377 = t5*dbds;
    t379 = t15*d2v1dsdt;
    t385 = 1/t359;
    t392 = t15*d2v1drdt;
    t409 = t170*t170;
    t414 = 1/t127;
    t421 = t73*t73;
    t431 = t15*p;
    t470 = t3*d2v1dsdt*t243+2.0*t376*t20*dbds-3.0*t248*dv1dt*t243*dbds+2.0*t376
*t147*dads+t376*dbdr*dbds-t339*t137-t339*t135-t379*t20-t392*t63+t3*d2v1drdt*
t377+t376*t5*d2bdr2-t392*dbds/2.0-t339*d2bdr2/2.0-t379*dbdr/2.0-t15*d3v1dr2dt*
t5/2.0+t37*d3v1dr2dt/2.0;
    t471 = log(t359);
    t474 = (1.0+a*t8)/(1.0-a*t8);
    t476 = t151*t211+t307*t159+2.0*t3*p*dv1dt*t148-t114*(d2adr2*t8-dadr*t17*t65
/2.0-dads*t17*t22/2.0+3.0/4.0*a*t129*t131-t164*t139/2.0)*t171+t307*t155-t342*
t351/t360*t368+t307*t175+(-t339*dbds/2.0+t37*d2v1dsdt/2.0+t376*t377-t379*t5/2.0
-t339*t63)*t351*t385+(-t339*dbdr/2.0+t37*d2v1drdt/2.0+t376*t243-t392*t5/2.0-
t339*t20)*t368*t385+t342*(d2adr2*p-d2adr2*pr+d2bdr2*t345-2.0*t115*pr+d2bdr2*
t349)*t385+t114*t167/t409*(-2.0*a*t71*dads+t5*t414*t65)-t114*t108/t421*(-2.0*
t60*t71*t54+t70*t414*t65)-t431*t173-t431*t177-t431*t211-t431*t179-t431*t152+
t470*t471;
    if (t305/t474 <= 0.0) printERR("d3gdr2dtGMAP", ERR_D3GDR2DT_GMAP, "t305/t474", t305/t474)
    return(t315+t476+t303*log(t305/t474)/2.0);
  }
}

static 
double d3gdr3LMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr,
double dv0ds,double dv1ds,double dv2ds,double dads,double dbds,double dv0dt,
double dv1dt,double dv2dt,double dadt,double dbdt,double d2v0drs,
double d2v1drs,double d2v2drs,double d2adrs,double d2bdrs,double d2v0drt,
double d2v1drt,double d2v2drt,double d2adrt,double d2bdrt,double d2v0dst,
double d2v1dst,double d2v2dst,double d2adst,double d2bdst,double d3v0dr3,
double d3v1dr3,double d3v2dr3,double d3adr3,double d3bdr3)
{
  double t1;
  double t10;
  double t100;
  double t1000;
  double t1002;
  double t1008;
  double t1009;
  double t101;
  double t1011;
  double t1013;
  double t102;
  double t1029;
  double t1036;
  double t1038;
  double t1043;
  double t1044;
  double t1049;
  double t105;
  double t1052;
  double t1058;
  double t106;
  double t1061;
  double t1064;
  double t1066;
  double t1086;
  double t109;
  double t11;
  double t110;
  double t111;
  double t1113;
  double t1132;
  double t1139;
  double t114;
  double t1140;
  double t1142;
  double t115;
  double t1152;
  double t1164;
  double t1165;
  double t1166;
  double t1173;
  double t1174;
  double t118;
  double t1182;
  double t1183;
  double t119;
  double t1190;
  double t1197;
  double t1201;
  double t1202;
  double t1203;
  double t122;
  double t1225;
  double t1228;
  double t123;
  double t1235;
  double t1246;
  double t126;
  double t1265;
  double t1272;
  double t128;
  double t1284;
  double t1285;
  double t1290;
  double t1294;
  double t13;
  double t1306;
  double t131;
  double t1314;
  double t1317;
  double t132;
  double t1321;
  double t1337;
  double t1342;
  double t1345;
  double t135;
  double t1358;
  double t1365;
  double t1369;
  double t1383;
  double t1387;
  double t1388;
  double t139;
  double t1394;
  double t1395;
  double t14;
  double t1407;
  double t141;
  double t1412;
  double t142;
  double t1420;
  double t1429;
  double t1449;
  double t1452;
  double t1469;
  double t147;
  double t1487;
  double t1496;
  double t151;
  double t1511;
  double t1512;
  double t1527;
  double t154;
  double t155;
  double t1553;
  double t1559;
  double t1565;
  double t158;
  double t1597;
  double t16;
  double t160;
  double t1621;
  double t163;
  double t1632;
  double t165;
  double t1651;
  double t167;
  double t1680;
  double t169;
  double t1699;
  double t17;
  double t170;
  double t1704;
  double t1708;
  double t1720;
  double t1721;
  double t1724;
  double t1728;
  double t173;
  double t1734;
  double t1746;
  double t1749;
  double t1750;
  double t1753;
  double t1757;
  double t1768;
  double t1772;
  double t1776;
  double t179;
  double t1808;
  double t1809;
  double t181;
  double t1813;
  double t1816;
  double t1817;
  double t1820;
  double t1826;
  double t1834;
  double t184;
  double t1840;
  double t1845;
  double t1850;
  double t1851;
  double t1854;
  double t1857;
  double t186;
  double t1860;
  double t1861;
  double t1873;
  double t188;
  double t1886;
  double t1894;
  double t19;
  double t190;
  double t191;
  double t1915;
  double t1923;
  double t1926;
  double t1937;
  double t194;
  double t1940;
  double t1945;
  double t196;
  double t198;
  double t1985;
  double t2;
  double t20;
  double t2005;
  double t2009;
  double t201;
  double t2017;
  double t2021;
  double t2027;
  double t2046;
  double t2064;
  double t2067;
  double t2068;
  double t207;
  double t2074;
  double t2080;
  double t2083;
  double t2084;
  double t2088;
  double t2095;
  double t2102;
  double t2103;
  double t2119;
  double t2128;
  double t2131;
  double t2135;
  double t2136;
  double t2147;
  double t2149;
  double t2164;
  double t2175;
  double t2178;
  double t22;
  double t2208;
  double t2213;
  double t2215;
  double t2237;
  double t2240;
  double t226;
  double t2264;
  double t2288;
  double t23;
  double t230;
  double t232;
  double t2330;
  double t236;
  double t2376;
  double t239;
  double t241;
  double t2416;
  double t2455;
  double t2457;
  double t2478;
  double t25;
  double t250;
  double t2505;
  double t2510;
  double t2512;
  double t2519;
  double t2523;
  double t2527;
  double t2534;
  double t254;
  double t257;
  double t2575;
  double t26;
  double t260;
  double t2611;
  double t263;
  double t265;
  double t2650;
  double t268;
  double t27;
  double t270;
  double t2702;
  double t2704;
  double t2713;
  double t273;
  double t2732;
  double t2736;
  double t2751;
  double t2754;
  double t2759;
  double t276;
  double t2764;
  double t2770;
  double t280;
  double t2811;
  double t283;
  double t2831;
  double t2846;
  double t2860;
  double t287;
  double t2870;
  double t2897;
  double t29;
  double t292;
  double t2927;
  double t295;
  double t2951;
  double t298;
  double t3;
  double t30;
  double t301;
  double t303;
  double t306;
  double t310;
  double t313;
  double t316;
  double t319;
  double t32;
  double t323;
  double t33;
  double t334;
  double t338;
  double t341;
  double t344;
  double t35;
  double t350;
  double t352;
  double t355;
  double t357;
  double t358;
  double t36;
  double t360;
  double t361;
  double t363;
  double t364;
  double t366;
  double t370;
  double t371;
  double t374;
  double t375;
  double t376;
  double t377;
  double t379;
  double t38;
  double t380;
  double t381;
  double t383;
  double t388;
  double t391;
  double t392;
  double t395;
  double t398;
  double t399;
  double t4;
  double t400;
  double t402;
  double t403;
  double t404;
  double t408;
  double t409;
  double t41;
  double t410;
  double t413;
  double t414;
  double t417;
  double t422;
  double t423;
  double t426;
  double t427;
  double t429;
  double t432;
  double t436;
  double t44;
  double t445;
  double t450;
  double t454;
  double t458;
  double t460;
  double t469;
  double t47;
  double t472;
  double t485;
  double t487;
  double t490;
  double t494;
  double t495;
  double t496;
  double t5;
  double t50;
  double t502;
  double t505;
  double t507;
  double t509;
  double t514;
  double t515;
  double t517;
  double t521;
  double t523;
  double t527;
  double t528;
  double t53;
  double t531;
  double t535;
  double t536;
  double t542;
  double t543;
  double t546;
  double t549;
  double t551;
  double t553;
  double t554;
  double t555;
  double t556;
  double t557;
  double t56;
  double t561;
  double t564;
  double t566;
  double t567;
  double t569;
  double t574;
  double t577;
  double t578;
  double t580;
  double t586;
  double t59;
  double t590;
  double t593;
  double t594;
  double t595;
  double t596;
  double t598;
  double t603;
  double t604;
  double t605;
  double t606;
  double t609;
  double t611;
  double t612;
  double t615;
  double t618;
  double t621;
  double t622;
  double t625;
  double t628;
  double t629;
  double t63;
  double t631;
  double t634;
  double t635;
  double t638;
  double t641;
  double t644;
  double t645;
  double t646;
  double t647;
  double t653;
  double t654;
  double t66;
  double t660;
  double t664;
  double t667;
  double t669;
  double t673;
  double t674;
  double t677;
  double t678;
  double t681;
  double t685;
  double t688;
  double t689;
  double t692;
  double t697;
  double t701;
  double t702;
  double t705;
  double t711;
  double t717;
  double t72;
  double t723;
  double t729;
  double t744;
  double t75;
  double t757;
  double t76;
  double t773;
  double t775;
  double t778;
  double t786;
  double t787;
  double t79;
  double t795;
  double t797;
  double t8;
  double t803;
  double t805;
  double t807;
  double t809;
  double t812;
  double t815;
  double t818;
  double t82;
  double t820;
  double t85;
  double t853;
  double t857;
  double t868;
  double t871;
  double t874;
  double t876;
  double t877;
  double t879;
  double t88;
  double t881;
  double t884;
  double t888;
  double t889;
  double t89;
  double t896;
  double t898;
  double t9;
  double t90;
  double t904;
  double t906;
  double t91;
  double t92;
  double t922;
  double t929;
  double t931;
  double t932;
  double t939;
  double t940;
  double t948;
  double t952;
  double t958;
  double t96;
  double t97;
  double t993;
  double t997;
  {
    t1 = b*b;
    t2 = 1/t1;
    t3 = t2*p;
    t4 = v1*d2adst;
    t5 = t4*dbdr;
    t8 = 1/t1/b;
    t9 = t8*p;
    t10 = v2*d2bdrt;
    t11 = t10*dbds;
    t13 = v1*dadt;
    t14 = t13*d2bdrs;
    t16 = dv1dr*a;
    t17 = t16*d2bdst;
    t19 = d2v1drs*a;
    t20 = t19*dbdt;
    t22 = v1*dads;
    t23 = t22*d2bdrt;
    t25 = t2*pr;
    t26 = v1*a;
    t27 = t26*d3bdr3;
    t29 = v2*dbdr;
    t30 = t29*d2bdst;
    t32 = dv1dt*a;
    t33 = t32*d2bdrs;
    t35 = v2*d2bdrs;
    t36 = t35*dbdt;
    t38 = t2*dv1dt;
    t41 = t2*dv2dr;
    t44 = t2*d2v1dst;
    t47 = t2*d2v1drs;
    t50 = t2*d2v2drt;
    t53 = t2*dv2ds;
    t56 = t2*dv1ds;
    t59 = t2*v1;
    t63 = a*a;
    t66 = t2*v2;
    t72 = t2*d2v1drt;
    t75 = -t38*d2bdrs/2.0-t41*d2adst/4.0-t44*dbdr/2.0-t47*dbdt/2.0-t50*dads/4.0
-t53*d2adrt/4.0-t56*d2bdrt/2.0-t59*d3bdr3/2.0-t2*d3v1dr3*t63/2.0-t66*d3adr3/4.0
-t2*d3v2dr3*a/4.0-t72*dbds/2.0;
    t76 = t2*dv2dt;
    t79 = t2*d2v2dst;
    t82 = t2*dv1dr;
    t85 = t2*d2v2drs;
    t88 = t1*t1;
    t89 = 1/t88;
    t90 = t89*v2;
    t91 = dads*dbdr;
    t92 = t91*dbdt;
    t96 = a*dbds;
    t97 = t96*dbdt;
    t100 = t89*v1;
    t101 = dbdr*dbds;
    t102 = t101*dbdt;
    t105 = a*d2bdrt;
    t106 = t105*dbds;
    t109 = t8*v1;
    t110 = a*dadr;
    t111 = t110*d2bdst;
    t114 = a*dbdr;
    t115 = t114*d2bdst;
    t118 = a*d2adrt;
    t119 = t118*dbds;
    t122 = t63*d2bdrt;
    t123 = t122*dbds;
    t126 = -t76*d2adrs/4.0-t79*dadr/4.0-t82*d2bdst/2.0-t85*dadt/4.0-3.0/2.0*t90
*t92-3.0/2.0*t89*dv2dr*t97-3.0*t100*t102-3.0/2.0*t90*t106+2.0*t109*t111-3.0/2.0
*t90*t115+2.0*t109*t119-3.0*t100*t123;
    t128 = t105*dads;
    t131 = a*d2adrs;
    t132 = t131*dbdt;
    t135 = t8*dv2dt;
    t139 = t63*dbdr;
    t141 = t8*dv2dr;
    t142 = dads*dbdt;
    t147 = t139*d2bdst;
    t151 = a*dbdt;
    t154 = a*d2bdrs;
    t155 = t154*dadt;
    t158 = t8*dv1ds;
    t160 = t114*d2adst;
    t163 = a*dadt;
    t165 = 2.0*t109*t128+2.0*t109*t132+t135*t91/2.0+t8*d2v1dst*t139+t141*t142/
2.0+t109*d2bdrt*dbds-3.0*t100*t147+t8*d2v2drs*t151/2.0+2.0*t109*t155+t158*t122+
2.0*t109*t160-t47*t163;
    t167 = t63*dbdt;
    t169 = t63*d2bdrs;
    t170 = t169*dbdt;
    t173 = t154*dbdt;
    t179 = t8*dv1dt;
    t181 = t8*dv2ds;
    t184 = dadt*d2adrs;
    t186 = a*dads;
    t188 = a*d2adst;
    t190 = t8*dv1dr;
    t191 = t63*d2bdst;
    t194 = t63*dbds;
    t196 = a*d3adr3;
    t198 = t8*d2v1drs*t167-3.0*t100*t170-3.0/2.0*t90*t173+t109*d2bdrs*dbdt-t38*
t131+t179*t169+t181*t105/2.0-t59*t184-t72*t186-t82*t188+t190*t191+t8*d2v1drt*
t194-t59*t196;
    t201 = t8*v2;
    t207 = a*d2bdst;
    t226 = d2adst*dadr;
    t230 = dads*d2adrt;
    t232 = t201*a*d3bdr3/2.0+t109*t63*d3bdr3+t141*t207/2.0+t201*d2adrs*dbdt/2.0
+t8*d2v2drt*t96/2.0+t8*d2v2dst*t114/2.0+t201*d2adrt*dbds/2.0+t201*dadt*d2bdrs/
2.0-t56*t118-t59*t226+t135*t154/2.0-t59*t230;
    t236 = dadt*dbds;
    t239 = dadt*dads;
    t241 = dbdr*dbdt;
    t250 = dbds*dbdt;
    t254 = dadr*dbdt;
    t257 = dadr*dbds;
    t260 = dadt*dbdr;
    t263 = t201*dadr*d2bdst/2.0+t141*t236/2.0-t82*t239+t158*t241+t201*dads*
d2bdrt/2.0+t201*d2adst*dbdr/2.0-t44*t110+t190*t250+t109*dbdr*d2bdst+t181*t254/
2.0+t135*t257/2.0+t181*t260/2.0;
    t265 = dadt*dadr;
    t268 = dads*dadr;
    t270 = t114*dadt;
    t273 = t186*dbdt;
    t276 = t100*a;
    t280 = t139*dbdt;
    t283 = t96*dadt;
    t287 = 1/t88/b;
    t292 = t101*dadt;
    t295 = t260*dads;
    t298 = 1/b;
    t301 = -t56*t265+t179*t101-t38*t268+2.0*t158*t270+2.0*t190*t273-6.0*t276*
t92-3.0*t89*dv1ds*t280+2.0*t190*t283+12.0*t287*v1*t63*t102-6.0*t276*t292+2.0*
t109*t295+t298*d3v1dr3/2.0;
    t303 = t194*dbdt;
    t306 = t268*dbdt;
    t310 = t114*dbdt;
    t313 = t265*dbds;
    t316 = t110*dbdt;
    t319 = t257*dbdt;
    t323 = t114*dbds;
    t334 = t114*dads;
    t338 = t139*dbds;
    t341 = t110*dbds;
    t344 = -3.0*t89*dv1dr*t303+2.0*t109*t306-3.0/2.0*t89*dv2ds*t310+2.0*t109*
t313+2.0*t158*t316-6.0*t276*t319-3.0/2.0*t89*dv2dt*t323+6.0*t287*v2*a*t102-3.0/
2.0*t90*t292-3.0/2.0*t90*t319+2.0*t179*t334-3.0*t89*dv1dt*t338+2.0*t179*t341;
    t350 = p*p;
    t352 = b*p;
    t355 = pr*pr;
    t357 = 1.0+a*p-a*pr+b*t350-2.0*t352*pr+b*t355;
    t358 = log(t357);
    t360 = dv1ds*a;
    t361 = t360*d2bdrt;
    t363 = d2v1dst*a;
    t364 = t363*dbdr;
    t366 = t8*pr;
    t370 = t298*pr;
    t371 = v1*d3adr3;
    t374 = 4.0*b-t63;
    t375 = sqrt(t374);
    t376 = 1/t375;
    t377 = t298*t376;
    t379 = t2*t376;
    t380 = t63*a;
    t381 = v1*t380;
    t383 = v2*t63;
    t388 = -t377*v2+t379*t381+t379*t383/2.0-3.0*t377*t26;
    t391 = 1/t375/t374;
    t392 = a*t391;
    t395 = 4.0*dbdr-2.0*t110;
    t398 = dadr*t376-t392*t395/2.0;
    t399 = t388*t398;
    t400 = 1/t374;
    t402 = 1.0+t63*t400;
    t403 = t402*t402;
    t404 = 1/t403;
    t408 = t374*t374;
    t409 = 1/t408;
    t410 = a*t409;
    t413 = 4.0*dbdt-2.0*t163;
    t414 = dads*t413;
    t417 = a*t400;
    t422 = 4.0*dbds-2.0*t186;
    t423 = t422*dadt;
    t426 = t408*t374;
    t427 = 1/t426;
    t429 = t422*t413;
    t432 = t63*t409;
    t436 = 4.0*d2bdst-2.0*t239-2.0*t188;
    t445 = t298*t391;
    t450 = t8*t376;
    t454 = t2*t391;
    t458 = dv1dt*t380;
    t460 = v1*t63;
    t469 = dv2dt*t63;
    t472 = v2*a;
    t485 = t379*v2*dbdt+t445*v2*t413/2.0-t377*dv2dt-2.0*t450*t381*dbdt-t454*
t381*t413/2.0+t379*t458+3.0*t379*t460*dadt-t450*t383*dbdt-t454*t383*t413/4.0+
t379*t469/2.0+t379*t472*dadt+3.0*t379*t26*dbdt+3.0/2.0*t445*t26*t413-3.0*t377*
t32-3.0*t377*t13;
    t487 = dadr*t391;
    t490 = dads*t391;
    t494 = 1/t375/t408;
    t495 = a*t494;
    t496 = t395*t422;
    t502 = 4.0*d2bdrs-2.0*t268-2.0*t131;
    t505 = d2adrs*t376-t487*t422/2.0-t490*t395/2.0+3.0/4.0*t495*t496-t392*t502/
2.0;
    t507 = 1/t402;
    t509 = -t3*t5+t9*t11-t3*t14-t3*t17-t3*t20-t3*t23+t25*t27+t9*t30-t3*t33+t9*
t36+(t75+t126+t165+t198+t232+t263+t301+t344)*t358-t3*t361-t3*t364-2.0*t366*
dv1dr*t97-t370*t371+t399*t404*(2.0*dadt*t400*dads-2.0*t410*t414+2.0*t417*d2adst
-2.0*t410*t423+2.0*t63*t427*t429-t432*t436)-t370*d3v2dr3/2.0-t485*t505*t507;
    t514 = 2.0*t417*dadt-t432*t413;
    t515 = t404*t514;
    t517 = d2bdrs*p;
    t521 = d2adrs+2.0*t517-2.0*d2bdrs*pr;
    t523 = dbdr*p;
    t527 = dadr+2.0*t523-2.0*dbdr*pr;
    t528 = t527*t391;
    t531 = dbds*p;
    t535 = dads+2.0*t531-2.0*dbds*pr;
    t536 = t535*t391;
    t542 = a+2.0*t352-2.0*b*pr;
    t543 = t542*t494;
    t546 = t542*t391;
    t549 = t521*t376-t528*t422/2.0-t536*t395/2.0+3.0/4.0*t543*t496-t546*t502/
2.0;
    t551 = t542*t542;
    t553 = 1.0+t551*t400;
    t554 = t553*t553;
    t555 = 1/t554;
    t556 = t542*t400;
    t557 = dbdt*p;
    t561 = dadt+2.0*t557-2.0*dbdt*pr;
    t564 = t551*t409;
    t566 = 2.0*t556*t561-t564*t413;
    t567 = t555*t566;
    t569 = t9*v1;
    t574 = v2*d3bdr3;
    t577 = dv1dr*dads;
    t578 = t577*dbdt;
    t580 = v2*dads;
    t586 = dv2dr*t63;
    t590 = dv2ds*a;
    t593 = t8*t391;
    t594 = t593*v1;
    t595 = t380*t395;
    t596 = t595*dbds;
    t598 = dv2dr*a;
    t603 = t298*t494;
    t604 = t603*v1;
    t605 = a*t395;
    t606 = t605*t422;
    t609 = dv2dr*dbds;
    t611 = t454*v1;
    t612 = t605*dbds;
    t615 = t114*t422;
    t618 = t450*v1;
    t621 = t454*v2;
    t622 = t110*t422;
    t625 = t450*v2;
    t628 = t380*dbdr;
    t629 = t628*t422;
    t631 = t139*dads;
    t634 = t379*t580*dadr+3.0*t379*t360*dbdr-t454*t586*t422/4.0+t379*t590*dadr+
t594*t596+t379*t598*dads-t450*t586*dbds-9.0/4.0*t604*t606+t379*t609-3.0/2.0*
t611*t612-3.0/2.0*t611*t615-6.0*t618*t323-t621*t622/2.0-2.0*t625*t341+t594*t629
-6.0*t618*t631;
    t635 = t605*dads;
    t638 = dv2dr*t422;
    t641 = dv2ds*t63;
    t644 = t2*t494;
    t645 = t644*v2;
    t646 = t63*t395;
    t647 = t646*t422;
    t653 = t593*v2;
    t654 = t646*dbds;
    t660 = dv1ds*t63;
    t664 = t139*t422;
    t667 = dv2ds*dbdr;
    t669 = dv1dr*t63;
    t673 = t89*t376;
    t674 = t673*v2;
    t677 = t379*v1;
    t678 = t110*dads;
    t681 = dv1dr*t380;
    t685 = dv2ds*t395;
    t688 = t63*dadr;
    t689 = t688*t422;
    t692 = -t621*t635/2.0+t445*t638/2.0-t450*t641*dbdr+3.0/8.0*t645*t647-t454*
t641*t395/4.0+t653*t654/2.0-2.0*t625*t334-t377*d2v2drs+3.0*t379*t660*dadr+t653*
t664/2.0+t379*t667+3.0*t379*t669*dads+3.0*t674*t338+6.0*t677*t678-t454*t681*
t422/2.0+t445*t685/2.0-3.0/2.0*t611*t689;
    t697 = dv1ds*t380;
    t701 = t673*v1;
    t702 = t628*dbds;
    t705 = dv1ds*dadr;
    t711 = t688*dbds;
    t717 = t646*dads;
    t723 = v2*t502;
    t729 = v2*t395;
    t744 = -2.0*t450*t681*dbds-t454*t697*t395/2.0+6.0*t701*t702-3.0*t377*t705
-2.0*t450*t697*dbdr-6.0*t618*t711-t454*t383*t502/4.0-3.0/2.0*t611*t717+3.0/2.0*
t445*t26*t502+t445*t723/2.0+3.0*t379*t26*d2bdrs-3.0/4.0*t603*t729*t422+t379*
t472*d2adrs-t450*t383*d2bdrs-2.0*t450*t381*d2bdrs+t379*t35-t454*t729*dbds/2.0;
    t757 = v1*dadr;
    t773 = d2v1drs*t380;
    t775 = v1*d2adrs;
    t778 = d2v2drs*t63;
    t786 = t644*v1;
    t787 = t595*t422;
    t795 = 3.0*t379*t460*d2adrs-t454*t29*t422/2.0-2.0*t450*t29*dbds+3.0/2.0*
t445*t16*t422+3.0/2.0*t445*t757*t422-t454*t381*t502/2.0+3.0*t379*t757*dbds+3.0*
t379*t16*dbds+3.0/2.0*t445*t22*t395+t379*t773-3.0*t377*t775+t379*t778/2.0+3.0/
2.0*t445*t360*t395-3.0*t377*t19+3.0/4.0*t786*t787+3.0*t379*t22*dbdr-3.0*t377*
t577;
    t797 = t634+t692+t744+t795;
    t803 = 1/t553;
    t805 = dv1dt*d2adrs;
    t807 = d3v1dr3*a;
    t809 = dv2dr*d2bdst;
    t812 = d2v2drs*dbdt;
    t815 = d2v2dst*dbdr;
    t818 = v2*dbds;
    t820 = v2*t422;
    t853 = t379*t818+t445*t820/2.0-t377*dv2ds-2.0*t450*t381*dbds-t454*t381*t422
/2.0+t379*t697+3.0*t379*t460*dads-t450*t383*dbds-t454*t383*t422/4.0+t379*t641/
2.0+t379*t472*dads+3.0*t379*t26*dbds+3.0/2.0*t445*t26*t422-3.0*t377*t360-3.0*
t377*t22;
    t857 = t527*t376-t546*t395/2.0;
    t868 = dv2dt*d2bdrs;
    t871 = d2v2drt*dbds;
    t874 = t388*t505*t515-t388*t549*t567+2.0*t569*t319+2.0*t569*t92+t25*t574/
2.0-t3*t578+t797*(t561*t376-t546*t413/2.0)*t803-t370*t805-t370*t807-t3*t809/2.0
-t3*t812/2.0-t3*t815/2.0-t853*t857*t567+t853*t398*t515+t25*t809/2.0+t25*t812/
2.0+t25*t815/2.0+t25*t868/2.0+t25*t871/2.0;
    t876 = dv1ds*dadt;
    t877 = t876*dbdr;
    t879 = t298*p;
    t881 = dv2ds*d2bdrt;
    t884 = t705*dbdt;
    t888 = dv1dr*dadt;
    t889 = t888*dbds;
    t896 = t89*p;
    t898 = t114*t250;
    t904 = d2v1dst*dadr;
    t906 = dv1ds*d2adrt;
    t922 = -t59*dbdr/2.0+t298*dv1dr/2.0+t109*t139-t82*t63/2.0-t59*t110+t201*
t114/2.0-t41*a/4.0-t66*dadr/4.0;
    t929 = dads*p-dads*pr+dbds*t350-2.0*t531*pr+dbds*t355;
    t931 = t357*t357;
    t932 = 1/t931;
    t939 = dadt*p-dadt*pr+dbdt*t350-2.0*t557*pr+dbdt*t355;
    t940 = t932*t939;
    t948 = t298*v1/2.0-t59*t63/2.0-t66*a/4.0;
    t952 = d3bdr3*p;
    t958 = 1/t357;
    t993 = t379*t29+t445*t729/2.0-t377*dv2dr-2.0*t450*t381*dbdr-t454*t381*t395/
2.0+t379*t681+3.0*t379*t460*dadr-t450*t383*dbdr-t454*t383*t395/4.0+t379*t586/
2.0+t379*t472*dadr+3.0*t379*t26*dbdr+3.0/2.0*t445*t26*t395-3.0*t377*t16-3.0*
t377*t757;
    t997 = dads*t376-t392*t422/2.0;
    t1000 = dv1dr*d2adst;
    t1002 = t667*dbdt;
    t1008 = 2.0*t417*dads-t432*t422;
    t1009 = t404*t1008;
    t1011 = -t3*t877+t879*t805-t3*t881/2.0-t3*t884-t3*t868/2.0-t3*t889-t3*t871/
2.0-d3v0dr3*pr+2.0*t569*t292-6.0*t896*v1*t898+2.0*t9*dv1ds*t310-t370*t904+t879*
t906-t922*t929*t940+t948*(d3adr3*p-d3adr3*pr+d3bdr3*t350-2.0*t952*pr+d3bdr3*
t355)*t958+t993*t997*t515-t370*t1000-t366*t1002+t485*t398*t1009;
    t1013 = t609*dbdt;
    t1029 = -t59*dbdt/2.0+t298*dv1dt/2.0+t109*t167-t38*t63/2.0-t59*t163+t201*
t151/2.0-t76*a/4.0-t66*dadt/4.0;
    t1036 = dadr*p-dadr*pr+dbdr*t350-2.0*t523*pr+dbdr*t355;
    t1038 = t932*t929;
    t1043 = dv2dt*dbdr;
    t1044 = t1043*dbds;
    t1049 = dadt*t391;
    t1052 = t395*t413;
    t1058 = 4.0*d2bdrt-2.0*t265-2.0*t118;
    t1061 = d2adrt*t376-t487*t413/2.0-t1049*t395/2.0+3.0/4.0*t495*t1052-t392*
t1058/2.0;
    t1064 = d2v1drs*dadt;
    t1066 = d2v1drt*dads;
    t1086 = -t38*t110+t201*t260/2.0+t141*t151/2.0+t109*t122+t135*t114/2.0+t201*
t105/2.0-t59*t118+t179*t139+t109*t241-t82*t163+t201*t254/2.0-t59*t265+t190*t167
;
    t1113 = -t38*dbdr/2.0-t59*d2bdrt/2.0-t66*d2adrt/4.0-t76*dadr/4.0-t82*dbdt/
2.0-t41*dadt/4.0-t50*a/4.0-t72*t63/2.0+t298*d2v1drt/2.0-3.0/2.0*t90*t310+2.0*
t109*t316-3.0*t100*t280+2.0*t109*t270;
    t1132 = -t59*dbds/2.0+t298*dv1ds/2.0+t109*t194-t56*t63/2.0-t59*t186+t201*
t96/2.0-t53*a/4.0-t66*dads/4.0;
    t1139 = 2.0*t556*t535-t564*t422;
    t1140 = t555*t1139;
    t1142 = t89*pr;
    t1152 = t366*v1;
    t1164 = t89*t391;
    t1165 = t1164*v2;
    t1166 = t422*dbdt;
    t1173 = 1/t375/t426;
    t1174 = t2*t1173;
    t1182 = t8*t494;
    t1183 = t1182*v2;
    t1190 = dbds*t413;
    t1197 = t63*d2adrs;
    t1201 = t454*dv1dr;
    t1202 = t63*t422;
    t1203 = t1202*dadt;
    t1225 = t593*dv2dt;
    t1228 = -6.0*t618*t292-6.0*t618*t1197*dbdt-3.0/2.0*t1201*t1203+3.0*t673*
dv2dt*t338-2.0*t625*t128-3.0/2.0*t1165*t646*t250+t653*t139*t436/2.0+t653*t169*
t413/2.0+t653*t122*t422/2.0+t653*t605*t236+t1225*t654/2.0;
    t1235 = d2v2dst*t63;
    t1246 = dv1dt*t63;
    t1265 = t63*t502;
    t1272 = t380*d2bdrt;
    t1284 = t454*dv1ds;
    t1285 = t114*t413;
    t1290 = dadr*t422;
    t1294 = -3.0/2.0*t611*t91*t413+6.0*t677*t131*dadt+3.0/8.0*t645*t1265*t413+
18.0*t701*t139*t236+t594*t1272*t422+t445*dv2dt*t502/2.0+3.0/2.0*t445*t876*t395-
t454*t469*t502/4.0-3.0/2.0*t1284*t1285+t379*t598*d2adst-9.0/4.0*t604*t1290*t413
;
    t1306 = t1164*v1;
    t1314 = t450*dv1ds;
    t1317 = a*t502;
    t1321 = t287*t376;
    t1337 = t605*t413;
    t1342 = d2v2drt*t63;
    t1345 = t605*dbdt;
    t1358 = -t621*t605*d2adst/2.0-t454*t641*t1058/4.0-9.0/4.0*t603*dv1ds*t1337
-6.0*t618*t319-t450*t1342*dbds-3.0/2.0*t1284*t1345-3.0*t377*t371-t450*t586*
d2bdst+3.0*t674*t170+3.0*t379*t578-2.0*t625*t119;
    t1365 = a*t1058;
    t1369 = dadt*t395;
    t1383 = t454*dv2dt;
    t1387 = a*t422;
    t1388 = t1387*t413;
    t1394 = -3.0/2.0*t611*t257*t413-2.0*t625*t160-t621*t1365*dads/2.0-9.0/4.0*
t604*t1369*t422+t653*t114*t423-t454*t1342*t422/4.0+3.0*t594*t688*t1190+t379*
d3v1dr3*t380-t1383*t622/2.0-9.0/4.0*t603*dv1dr*t1388-t454*t458*t502/2.0;
    t1395 = t380*d2bdrs;
    t1407 = t298*t1173;
    t1412 = t1387*dbdt;
    t1420 = d2v1dst*t380;
    t1429 = t594*t1395*t413-3.0/4.0*t1183*t139*t429-t621*t265*t422/2.0-2.0*t450
*t458*d2bdrs+45.0/8.0*t1407*v1*t605*t429-3.0/2.0*t1201*t1412-6.0*t618*t169*dadt
+3.0*t379*t889-t454*t1420*t395/2.0+t653*t110*t1166+3.0/2.0*t445*t888*t422;
    t1449 = t96*t413;
    t1452 = d2v1drt*t380;
    t1469 = t450*dv1dr;
    t1487 = t380*t1058;
    t1496 = 3.0/4.0*t645*t110*t429-t454*t773*t413/2.0-6.0*t1469*t97-3.0/4.0*
t603*t729*t436+9.0/4.0*t786*t605*t1166+t379*dv2ds*dadt*dadr-t454*t1452*t422/2.0
-9.0/4.0*t604*t1317*t413+t594*t1487*dbds-t454*t681*t436/2.0+3.0/2.0*t445*t705*
t413;
    t1511 = t454*dv2dr;
    t1512 = t186*t413;
    t1527 = -t377*d3v2dr3-3.0/2.0*t611*t1365*dbds-2.0*t450*t681*d2bdst+t379*
dv2dr*dadt*dads+3.0/2.0*t445*t22*t1058-t1511*t1512/2.0+3.0*t379*t884+t594*t595*
d2bdst+3.0/4.0*t786*t1487*t422-2.0*t625*t306+3.0/2.0*t445*t4*t395;
    t1553 = v2*dadt;
    t1559 = -2.0*t450*t1002+t379*t590*d2adrt-t454*t667*t413/2.0+t379*d2v2dst*a*
dadr+3.0/2.0*t445*t13*t502-t621*t268*t413/2.0+3.0/2.0*t445*t32*t502+3.0*t379*
t660*d2adrt-12.0*t618*t114*t239+t379*t1553*d2adrs-3.0/2.0*t611*t605*d2bdst;
    t1565 = t450*dv2ds;
    t1597 = dv2dt*a;
    t1621 = 3.0*t379*d2v1drt*t63*dads+18.0*t701*t139*t142+t379*t1597*d2adrs-3.0
*t611*t605*t239-2.0*t450*t1044-t621*t118*t422/2.0+3.0/2.0*t445*t757*t436+6.0*
t701*t1395*dbdt-2.0*t450*t1013+6.0*t674*t102-t621*t110*t436/2.0;
    t1632 = t63*d2adrt;
    t1651 = 3.0*t379*t669*d2adst+3.0*t674*t123+t379*t809-12.0*t618*t110*t236
-6.0*t618*t1632*dbds+t653*t101*t413+t379*t812-6.0*t618*t122*dads-t454*t685*dbdt
/2.0+3.0*t379*d2v1dst*t63*dadr+3.0*t379*t361;
    t1680 = 3.0*t594*t688*t1166-3.0/2.0*t611*t154*t413-3.0/2.0*t611*t688*t436+
3.0*t379*t23+3.0*t594*t139*t423+3.0*t379*t364-6.0*t618*t688*d2bdst-3.0/2.0*t611
*t1632*t422+3.0*t379*t5+t379*t871-3.0/2.0*t611*t646*d2adst;
    t1699 = t63*t1058;
    t1704 = t186*dadt;
    t1708 = t496*t413;
    t1720 = v1*d2adrt;
    t1721 = t1720*dbds;
    t1724 = t380*t502;
    t1728 = d2v1drt*a;
    t1734 = t757*d2bdst;
    t1746 = t450*dv2dr;
    t1749 = t63*dads;
    t1750 = t1749*dbdt;
    t1753 = t445*d2v2drt*t422/2.0+3.0*t379*t1721+3.0/4.0*t786*t1724*t413+3.0/
2.0*t445*t1728*t422-t450*t778*dbdt+3.0*t379*t1734-3.0*t1306*t628*t1166-t454*
t729*d2bdst/2.0+t445*d2v2drs*t413/2.0-2.0*t1746*t273-6.0*t1469*t1750;
    t1757 = dv2dt*t395;
    t1768 = t1182*v1;
    t1772 = t1749*t413;
    t1776 = t628*dbdt;
    t1808 = t593*dv2ds;
    t1809 = t139*t413;
    t1813 = t1202*t413;
    t1816 = t593*dv2dr;
    t1817 = t1202*dbdt;
    t1820 = -3.0*t611*t110*t414-15.0/8.0*t1174*v1*t595*t429-2.0*t450*t36+t653*
t1699*dbds/2.0+t653*t114*t414-3.0/2.0*t1768*t628*t429-2.0*t625*t295+6.0*t674*
t114*t142+t1808*t1809/2.0+3.0/8.0*t644*dv2dr*t1813+t1816*t1817/2.0;
    t1826 = t395*dbds;
    t1834 = t450*dv2dt;
    t1840 = v2*t1058;
    t1845 = t646*t413;
    t1850 = t593*dv1ds;
    t1851 = t628*t413;
    t1854 = t139*dadt;
    t1857 = t775*dbdt;
    t1860 = t454*dv2ds;
    t1861 = t605*dadt;
    t1873 = t194*t413;
    t1886 = -6.0*t1314*t1854+3.0*t379*t1857-t1860*t1861/2.0+t653*t646*d2bdst/
2.0+3.0*t673*dv2dr*t303-t454*t1757*dbds/2.0+t1816*t1873/2.0+3.0/4.0*t645*t1826*
t413-t454*t29*t436/2.0-t450*t383*d3bdr3-t1383*t635/2.0;
    t1894 = t646*dbdt;
    t1915 = 9.0/4.0*t786*t646*t423-t454*t35*t413/2.0+t1808*t1894/2.0+t379*t472*
d3adr3-2.0*t450*t381*d3bdr3+3.0/4.0*t645*t605*t414-2.0*t1834*t341+t379*t815+3.0
/2.0*t445*t775*t413+t379*t574+9.0/4.0*t786*t688*t429;
    t1923 = t1387*dadt;
    t1926 = t1728*dbds;
    t1937 = dbdr*t422;
    t1940 = t110*t413;
    t1945 = 3.0/8.0*t645*t646*t436+3.0*t379*t27+t653*t110*t1190-t1511*t1923/2.0
+3.0*t379*t1926-t621*t1369*dads/2.0+3.0*t379*t33+3.0/2.0*t445*t16*t436+t653*
t1937*dbdt-t1860*t1940/2.0+3.0*t379*t14;
    t1985 = t110*dadt;
    t2005 = 4.0*d3bdr3-2.0*t226-2.0*t230-2.0*t184-2.0*t196;
    t2009 = -3.0/2.0*t611*t1317*dbdt+t445*dv2dr*t436/2.0-3.0*t377*t805-3.0/2.0*
t611*t105*t422+6.0*t379*dv1ds*t1985+t379*t868+t445*d2v2dst*t395/2.0-6.0*t618*
t139*d2adst-3.0*t377*t904+3.0/2.0*t445*t360*t1058+t445*v2*t2005/2.0;
    t2017 = dads*t395;
    t2021 = t194*dadt;
    t2027 = t688*dbdt;
    t2046 = -3.0/4.0*t603*t1840*t422+3.0/2.0*t445*t363*t395-3.0/2.0*t611*t2017*
dbdt-6.0*t1469*t2021-9.0/4.0*t604*t605*t436-6.0*t1314*t2027+3.0/8.0*t645*t1699*
t422-9.0/4.0*t604*t1365*t422+3.0/4.0*t645*t1937*t413+3.0*t379*d2v1drs*t63*dadt
-3.0/2.0*t611*t1369*dbds;
    t2064 = t595*dbdt;
    t2067 = t380*t422;
    t2068 = t2067*t413;
    t2074 = t688*t413;
    t2080 = 3.0/2.0*t445*t26*t2005-3.0*t377*t1064+9.0/4.0*t786*t605*t1190-t454*
t383*t2005/4.0-t454*t381*t2005/2.0-9.0/4.0*t604*t2017*t413+t1850*t2064+3.0/4.0*
t644*dv1dr*t2068-3.0/2.0*t611*t260*t422-3.0/2.0*t1284*t2074+3.0*t594*t605*t250;
    t2083 = t593*dv1dr;
    t2084 = t2067*dbdt;
    t2088 = t646*dadt;
    t2095 = t595*t413;
    t2102 = t380*dbds;
    t2103 = t2102*dbdt;
    t2119 = t2102*t413;
    t2128 = t454*dv1dt;
    t2131 = dv1dt*dads;
    t2135 = dv1dt*dadr;
    t2136 = t2135*dbds;
    t2147 = 6.0*t674*t114*t236+t2083*t2119+3.0*t594*t646*t142-6.0*t618*t92+3.0*
t379*t877-3.0/2.0*t2128*t612+3.0/2.0*t445*t2131*t395+3.0*t379*t2136+3.0/2.0*
t445*t2135*t422-3.0/2.0*t2128*t717-3.0/4.0*t603*t723*t413;
    t2149 = t450*dv1dt;
    t2164 = t593*dv1dt;
    t2175 = t2131*dbdr;
    t2178 = -6.0*t2149*t711-9.0/4.0*t603*dv1dt*t606-6.0*t2149*t631-12.0*t1321*
v2*t139*t250-t454*t586*t436/4.0+t2164*t629+3.0/4.0*t644*dv1dt*t787+t2164*t596+
6.0*t379*dv1dt*t678-6.0*t2149*t323+3.0*t379*t2175;
    t2208 = -3.0/2.0*t2128*t615+6.0*t673*dv1dt*t702-3.0/2.0*t2128*t689-2.0*t450
*t11+t445*dv2ds*t1058/2.0-3.0/2.0*t1165*t139*t1190-t454*t723*dbdt/2.0+3.0*t379*
t20+t379*d3v2dr3*t63/2.0+3.0*t594*t114*t1190-3.0/2.0*t1768*t595*t1190;
    t2213 = t1886-3.0/2.0*t1201*t1772-6.0*t618*t106-3.0/2.0*t1284*t2088+t1850*
t1851-2.0*t1565*t270-2.0*t625*t111+t379*t881-3.0*t377*t807-3.0*t377*t1000-2.0*
t450*t30-6.0*t1314*t310-2.0*t1746*t283-2.0*t1834*t334+t2080-15.0/16.0*t1174*v2*
t646*t429+t379*d2v2drs*a*dadt+t379*dv2dt*dads*dadr+t379*v2*d2adst*dadr-24.0*
t1321*v1*t628*t250+t379*d2v2drt*a*dads+t1228+t1496+3.0*t674*t147+t1915+t2083*
t2084+18.0*t701*t898-2.0*t625*t313-6.0*t618*t173+t1621+t1429+t1559+t2009-3.0*
t377*t906-t450*t641*d2bdrt-t454*t1043*t422/2.0+t379*t580*d2adrt-t450*t469*
d2bdrs+3.0/4.0*t645*t605*t423+6.0*t677*t118*dads+6.0*t701*t1272*dbds-2.0*t450*
t697*d2bdrt-3.0/4.0*t603*t638*t413-3.0/2.0*t611*t114*t436+t594*t1724*dbdt+3.0/
2.0*t445*t1720*t422-3.0/2.0*t1768*t595*t1166+6.0*t673*dv1ds*t1776-3.0/2.0*t611*
t1265*dadt-t454*t10*t422/2.0-2.0*t450*t773*dbdt+t653*t1826*dbdt-3.0*t1306*t628*
t1190+18.0*t701*t688*t250+3.0*t594*t139*t414-3.0/4.0*t603*t685*t413-3.0/2.0*
t611*t1699*dads+6.0*t379*dv1dr*t1704+15.0/8.0*t1407*v2*t1708+3.0*t379*t1246*
d2adrs-3.0/4.0*t1183*t646*t1190+6.0*t677*t110*d2adst+t653*t1265*dbdt/2.0+3.0/
8.0*t644*dv2dt*t647-3.0/2.0*t611*t1197*t413+3.0/4.0*t786*t595*t436-2.0*t450*
t1452*dbds-t450*t1235*dbdr+t594*t628*t436-t454*t609*t413/2.0-t621*t1317*dadt/
2.0-2.0*t450*t1420*dbdr+t653*t605*t142-3.0/4.0*t603*t1757*t422-3.0/2.0*t611*
t1290*dbdt+3.0*t673*dv2ds*t280-3.0/2.0*t1165*t139*t1166-3.0/4.0*t1183*t646*
t1166-t454*t638*dbdt/2.0+3.0/2.0*t445*t19*t413-t454*t1235*t395/4.0-t621*t131*
t413/2.0+9.0/4.0*t786*t646*t414+6.0*t701*t628*d2bdst+9.0/4.0*t786*t114*t429+3.0
/4.0*t644*dv1ds*t2095+3.0*t594*t114*t1166+6.0*t673*dv1dr*t2103-t454*t697*t1058/
2.0-3.0*t1306*t595*t250+3.0/2.0*t445*t577*t413+3.0*t594*t646*t236-3.0*t611*t110
*t423+6.0*t674*t110*t250+3.0*t379*t460*d3adr3-t454*t1840*dbds/2.0+3.0/8.0*t644*
dv2ds*t1845+6.0*t677*t265*dads+3.0/4.0*t645*t496*dbdt-12.0*t618*t110*t142-t454*
t778*t413/4.0+t1527+t2208+t1294+t1945+t1651-2.0*t1565*t316+t1753-3.0*t377*t1066
+t2046-3.0/2.0*t1201*t1449-2.0*t625*t132-2.0*t625*t155+3.0*t379*t17+t1225*t664/
2.0+t1358+t1680+t2147+t1394+t2178-6.0*t618*t115+t1820;
    t2215 = atan(t542*t376);
    t2237 = d2adrs*p-d2adrs*pr+d2bdrs*t350-2.0*t517*pr+d2bdrs*t355;
    t2240 = t9*t1002+t9*t1013-t1029*t1036*t1038-3.0*t896*v2*t102+t9*t1044+t388*
t1061*t1009-t370*t1064-t370*t1066+(t1086+t1113)*t929*t958-t366*t1013-t1132*
t1036*t940-t485*t857*t1140+3.0*t1142*v2*t102-t797*(dadt*t376-t392*t413/2.0)*
t507-2.0*t1152*t106+t2213*t2215+2.0*t569*t115-t993*(d2adst*t376-t490*t413/2.0-
t1049*t422/2.0+3.0/4.0*t495*t429-t392*t436/2.0)*t507+t1029*t2237*t958;
    t2264 = -t59*d2bdst/2.0-t66*d2adst/4.0-t79*a/4.0-t56*dbdt/2.0-t76*dads/4.0-
t44*t63/2.0-t38*t186+t158*t167+t179*t194+t201*t236/2.0+t109*t250-t56*t163+t201*
t142/2.0;
    t2288 = t135*t96/2.0+t201*t207/2.0-t59*t188+t181*t151/2.0-t59*t239+t109*
t191-3.0/2.0*t90*t97+2.0*t109*t273+t298*d2v1dst/2.0+2.0*t109*t283-t53*dadt/4.0-
t38*dbds/2.0-3.0*t100*t303;
    t2330 = t379*t1452-3.0*t377*t2135-3.0*t377*t888+t445*t1840/2.0+t379*t1043+
t379*dv2dr*dbdt-3.0*t377*t1720+t379*t1342/2.0+t379*t10-3.0*t377*t1728+t445*
dv2dr*t413/2.0+t445*t1757/2.0+3.0*t379*t32*dbdr+3.0/2.0*t445*t32*t395+3.0*t379*
t1246*dadr-2.0*t450*t458*dbdr;
    t2376 = -t454*t458*t395/2.0-t377*d2v2drt-t454*t729*dbdt/2.0-2.0*t450*t29*
dbdt-3.0/4.0*t603*t729*t413-3.0/2.0*t611*t2088-t454*t29*t413/2.0+3.0/4.0*t786*
t2095+3.0/2.0*t445*t26*t1058+3.0/2.0*t445*t757*t413-t454*t383*t1058/4.0-t454*
t381*t1058/2.0+3.0*t379*t13*dbdr+3.0/2.0*t445*t13*t395-9.0/4.0*t604*t1337-3.0/
2.0*t611*t1285+3.0*t379*t757*dbdt;
    t2416 = -t450*t383*d2bdrt+t379*t472*d2adrt-2.0*t450*t381*d2bdrt+3.0/2.0*
t445*t16*t413+3.0*t379*t16*dbdt-3.0/2.0*t611*t1345+3.0*t379*t460*d2adrt+3.0*
t379*t26*d2bdrt+6.0*t701*t1776+t594*t2064-6.0*t618*t1854+t594*t1851+t379*t598*
dadt-t621*t1940/2.0+t379*t1553*dadr-6.0*t618*t310-t454*t469*t395/4.0;
    t2455 = -t450*t586*dbdt-t621*t1861/2.0-2.0*t625*t316+3.0*t674*t280-2.0*t625
*t270-t450*t469*dbdr-t454*t586*t413/4.0+3.0/8.0*t645*t1845+t379*t1597*dadr-2.0*
t450*t681*dbdt-6.0*t618*t2027+6.0*t677*t1985+t653*t1809/2.0+t653*t1894/2.0+3.0*
t379*t669*dadt-t454*t681*t413/2.0-3.0/2.0*t611*t2074;
    t2457 = t2330+t2376+t2416+t2455;
    t2478 = t109*t101+t190*t194-t82*t186-t56*t110+t158*t139+t181*t114/2.0+t201*
t91/2.0+t141*t96/2.0-t59*t268+t201*t257/2.0-t59*t131+t201*t154/2.0+t109*t169;
    t2505 = -t66*d2adrs/4.0-t41*dads/4.0-t53*dadr/4.0-t56*dbdr/2.0-t82*dbds/2.0
-t85*a/4.0-t47*t63/2.0-t59*d2bdrs/2.0-3.0*t100*t338+2.0*t109*t334+2.0*t109*t341
-3.0/2.0*t90*t323+t298*d2v1drs/2.0;
    t2510 = atan(a*t376);
    t2512 = t948*t1036;
    t2519 = d2bdrt*p;
    t2523 = d2adrt+2.0*t2519-2.0*d2bdrt*pr;
    t2527 = t561*t391;
    t2534 = t2523*t376-t528*t413/2.0-t2527*t395/2.0+3.0/4.0*t543*t1052-t546*
t1058/2.0;
    t2575 = t445*dv2dt*t422/2.0+t379*dv2dt*dbds+t445*dv2ds*t413/2.0+t379*dv2ds*
dbdt+t379*t1235/2.0+t379*t1420-3.0*t377*t4-3.0*t377*t363+t379*v2*d2bdst+t445*v2
*t436/2.0-3.0*t377*t2131-t377*d2v2dst+3.0*t379*t26*d2bdst-2.0*t450*t381*d2bdst+
3.0*t379*t460*d2adst+t379*t472*d2adst;
    t2611 = -t450*t383*d2bdst-6.0*t618*t1750-3.0/2.0*t611*t1772-3.0/2.0*t611*
t1203+3.0/4.0*t786*t2068-t454*t697*t413/2.0-2.0*t450*t697*dbdt+t594*t2084-6.0*
t618*t2021+6.0*t701*t2103+t594*t2119+3.0*t379*t13*dbds-3.0/2.0*t611*t1449-3.0*
t377*t876-3.0/2.0*t611*t1412-6.0*t618*t97+t653*t1873/2.0;
    t2650 = t379*t1553*dads-2.0*t625*t273-9.0/4.0*t604*t1388+t379*t1597*dads+
t653*t1817/2.0-t621*t1512/2.0+t379*t590*dadt-t621*t1923/2.0-t450*t641*dbdt-2.0*
t625*t283-t450*t469*dbds+3.0*t379*t660*dadt+3.0*t674*t303-t454*t469*t422/4.0+
6.0*t677*t1704+3.0/8.0*t645*t1813-t454*t820*dbdt/2.0;
    t2702 = -t454*t381*t436/2.0-t454*t383*t436/4.0-t454*t641*t413/4.0+3.0/2.0*
t445*t26*t436+3.0*t379*t360*dbdt+3.0/2.0*t445*t13*t422+3.0/2.0*t445*t360*t413+
3.0*t379*t22*dbdt+3.0/2.0*t445*t22*t413-t454*t818*t413/2.0-3.0/4.0*t603*t820*
t413-t454*t458*t422/2.0-2.0*t450*t458*dbds+3.0*t379*t1246*dads+3.0*t379*t32*
dbds-2.0*t450*t818*dbdt+3.0/2.0*t445*t32*t422;
    t2704 = t2575+t2611+t2650+t2702;
    t2713 = d2adrt*p-d2adrt*pr+d2bdrt*t350-2.0*t2519*pr+d2bdrt*t355;
    t2732 = d2bdst*p;
    t2736 = d2adst+2.0*t2732-2.0*d2bdst*pr;
    t2751 = t1058*t422;
    t2754 = t395*t436;
    t2759 = t502*t413;
    t2764 = (d3adr3+2.0*t952-2.0*d3bdr3*pr)*t376-t521*t391*t413/2.0-t2523*t391*
t422/2.0+3.0/4.0*t527*t494*t429-t528*t436/2.0-t2736*t391*t395/2.0+3.0/4.0*t535*
t494*t1052-t536*t1058/2.0+3.0/4.0*t561*t494*t496-15.0/8.0*t542*t1173*t1708+3.0/
4.0*t543*t2751+3.0/4.0*t543*t2754-t2527*t502/2.0+3.0/4.0*t543*t2759-t546*t2005/
2.0;
    t2770 = t535*t376-t546*t422/2.0;
    t2811 = d3adr3*t376-d2adrs*t391*t413/2.0-d2adrt*t391*t422/2.0+3.0/4.0*dadr*
t494*t429-t487*t436/2.0-d2adst*t391*t395/2.0+3.0/4.0*dads*t494*t1052-t490*t1058
/2.0+3.0/4.0*dadt*t494*t496-15.0/8.0*a*t1173*t1708+3.0/4.0*t495*t2751+3.0/4.0*
t495*t2754-t1049*t502/2.0+3.0/4.0*t495*t2759-t392*t2005/2.0;
    t2831 = (t2264+t2288)*t1036*t958-t853*t1061*t507+t485*t549*t803-t2457*t997*
t507+(t2478+t2505)*t939*t958-t2213*t2510+2.0*t2512/t931/t357*t929*t939+t853*
t2534*t803-2.0*t1152*t115+t2704*t857*t803+t1132*t2713*t958+t388*t2764*t803+
t2457*t2770*t803+2.0*t569*t173-t388*t2811*t507+t25*t2136+t25*t2175-2.0*t366*
dv1dt*t323+t993*(t2736*t376-t536*t413/2.0-t2527*t422/2.0+3.0/4.0*t543*t429-t546
*t436/2.0)*t803;
    t2846 = d2adst*p-d2adst*pr+d2bdst*t350-2.0*t2732*pr+d2bdst*t355;
    t2860 = t388*t857;
    t2870 = t542*t409;
    t2897 = -t2704*t398*t507-t3*t574/2.0+t879*t807-t993*t2770*t567+t879*t371+
t922*t2846*t958+t879*t1000+t879*t1066-2.0*t399/t403/t402*t1008*t514-t948*t2237*
t940+t879*t904+2.0*t2860/t554/t553*t1139*t566-t2860*t555*(2.0*t561*t400*t535
-2.0*t2870*t535*t413+2.0*t556*t2736-2.0*t2870*t422*t561+2.0*t551*t427*t429-t564
*t436)-t366*t1044+t25*t877+6.0*t1142*v1*t898-2.0*t366*dv1ds*t310-2.0*t1152*t292
-t370*t906;
    t2927 = -t2512*t932*t2846+t879*t1064+t25*t578+t25*t884+t25*t889-2.0*t1152*
t92-2.0*t1152*t319-t948*t2713*t1038+t25*t881/2.0-t3*t2136+2.0*t9*dv1dt*t323-t3*
t2175-t3*t1721+2.0*t9*dv1dr*t97-t3*t1734-t3*t1926-t366*t30+t25*t364-t3*t1857;
    t2951 = t25*t5+2.0*t569*t106+d3v0dr3*p+t879*d3v2dr3/2.0-t3*t27-t366*t36-2.0
*t1152*t173+t25*t361+t25*t20+t25*t17+t25*t14-t366*t11+t25*t33+t25*t1857+t25*t23
+t25*t1721+t25*t1734+t25*t1926-t388*t2534*t1140;
    return(t509+t874+t1011+t2240+t2831+t2897+t2927+t2951);
  }
}

static 
double d3gdr3GMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr,
double dv0ds,double dv1ds,double dv2ds,double dads,double dbds,double dv0dt,
double dv1dt,double dv2dt,double dadt,double dbdt,double d2v0drs,
double d2v1drs,double d2v2drs,double d2adrs,double d2bdrs,double d2v0drt,
double d2v1drt,double d2v2drt,double d2adrt,double d2bdrt,double d2v0dst,
double d2v1dst,double d2v2dst,double d2adst,double d2bdst,double d3v0dr3,
double d3v1dr3,double d3v2dr3,double d3adr3,double d3bdr3)
{
  double t1;
  double t1004;
  double t1009;
  double t102;
  double t1021;
  double t1028;
  double t103;
  double t1030;
  double t104;
  double t106;
  double t1066;
  double t1070;
  double t108;
  double t1090;
  double t1099;
  double t11;
  double t110;
  double t1102;
  double t111;
  double t1110;
  double t1115;
  double t1124;
  double t113;
  double t1142;
  double t1146;
  double t116;
  double t1169;
  double t1172;
  double t1179;
  double t1182;
  double t1185;
  double t1188;
  double t119;
  double t1191;
  double t1196;
  double t1203;
  double t1206;
  double t121;
  double t1218;
  double t1219;
  double t1222;
  double t1223;
  double t124;
  double t1242;
  double t1245;
  double t1252;
  double t1257;
  double t126;
  double t1262;
  double t1277;
  double t1278;
  double t1281;
  double t1286;
  double t1289;
  double t129;
  double t1297;
  double t13;
  double t1300;
  double t1304;
  double t1312;
  double t1316;
  double t132;
  double t1341;
  double t136;
  double t1363;
  double t138;
  double t1389;
  double t1394;
  double t1397;
  double t14;
  double t140;
  double t1405;
  double t1408;
  double t141;
  double t1428;
  double t1431;
  double t1436;
  double t1437;
  double t144;
  double t1440;
  double t1443;
  double t1446;
  double t1455;
  double t1461;
  double t1467;
  double t147;
  double t1479;
  double t1482;
  double t1485;
  double t1487;
  double t149;
  double t1492;
  double t1497;
  double t1506;
  double t1517;
  double t1523;
  double t1534;
  double t1549;
  double t1557;
  double t1568;
  double t1570;
  double t1573;
  double t1577;
  double t1580;
  double t1582;
  double t1599;
  double t16;
  double t160;
  double t1607;
  double t1610;
  double t1613;
  double t1618;
  double t1624;
  double t1647;
  double t1650;
  double t1660;
  double t1684;
  double t1723;
  double t1728;
  double t1729;
  double t1734;
  double t1738;
  double t1740;
  double t1745;
  double t1748;
  double t1751;
  double t1757;
  double t1768;
  double t1779;
  double t1785;
  double t18;
  double t1808;
  double t181;
  double t1813;
  double t1827;
  double t1831;
  double t1834;
  double t1843;
  double t185;
  double t1854;
  double t1856;
  double t1859;
  double t1869;
  double t1880;
  double t19;
  double t1919;
  double t192;
  double t1926;
  double t193;
  double t1937;
  double t194;
  double t1940;
  double t1948;
  double t1967;
  double t197;
  double t1974;
  double t1978;
  double t1991;
  double t1992;
  double t1993;
  double t2;
  double t2008;
  double t2012;
  double t2016;
  double t2024;
  double t2046;
  double t2051;
  double t2052;
  double t2056;
  double t206;
  double t2071;
  double t2077;
  double t2083;
  double t209;
  double t2098;
  double t210;
  double t2116;
  double t2121;
  double t213;
  double t2133;
  double t214;
  double t2143;
  double t2154;
  double t2168;
  double t217;
  double t2175;
  double t2185;
  double t2187;
  double t219;
  double t22;
  double t220;
  double t2200;
  double t2211;
  double t2219;
  double t2223;
  double t223;
  double t2237;
  double t224;
  double t2243;
  double t2251;
  double t2261;
  double t2264;
  double t2267;
  double t230;
  double t231;
  double t2313;
  double t232;
  double t2320;
  double t2327;
  double t233;
  double t2333;
  double t234;
  double t235;
  double t2350;
  double t2356;
  double t2374;
  double t2377;
  double t238;
  double t2394;
  double t241;
  double t2422;
  double t244;
  double t2441;
  double t2469;
  double t2475;
  double t25;
  double t2504;
  double t2522;
  double t2527;
  double t253;
  double t254;
  double t2541;
  double t255;
  double t2560;
  double t2565;
  double t2570;
  double t2588;
  double t2594;
  double t26;
  double t260;
  double t2603;
  double t261;
  double t2613;
  double t2627;
  double t2633;
  double t264;
  double t2656;
  double t2675;
  double t2688;
  double t27;
  double t2714;
  double t2722;
  double t274;
  double t2754;
  double t2759;
  double t2761;
  double t2772;
  double t2778;
  double t278;
  double t2782;
  double t279;
  double t2791;
  double t28;
  double t2806;
  double t281;
  double t2811;
  double t2817;
  double t2823;
  double t2835;
  double t2837;
  double t285;
  double t2853;
  double t2871;
  double t2879;
  double t2895;
  double t2916;
  double t293;
  double t294;
  double t295;
  double t2951;
  double t296;
  double t299;
  double t303;
  double t307;
  double t308;
  double t311;
  double t312;
  double t315;
  double t318;
  double t319;
  double t32;
  double t322;
  double t323;
  double t326;
  double t327;
  double t330;
  double t331;
  double t334;
  double t337;
  double t338;
  double t341;
  double t344;
  double t347;
  double t349;
  double t351;
  double t357;
  double t358;
  double t36;
  double t363;
  double t365;
  double t366;
  double t367;
  double t370;
  double t372;
  double t373;
  double t38;
  double t381;
  double t382;
  double t388;
  double t392;
  double t396;
  double t4;
  double t400;
  double t405;
  double t408;
  double t410;
  double t412;
  double t414;
  double t417;
  double t42;
  double t421;
  double t425;
  double t429;
  double t431;
  double t434;
  double t436;
  double t438;
  double t440;
  double t444;
  double t447;
  double t449;
  double t451;
  double t454;
  double t455;
  double t458;
  double t461;
  double t464;
  double t468;
  double t470;
  double t472;
  double t474;
  double t476;
  double t479;
  double t48;
  double t481;
  double t483;
  double t486;
  double t489;
  double t492;
  double t495;
  double t498;
  double t5;
  double t501;
  double t504;
  double t507;
  double t508;
  double t51;
  double t511;
  double t512;
  double t514;
  double t515;
  double t518;
  double t521;
  double t522;
  double t523;
  double t526;
  double t527;
  double t530;
  double t535;
  double t536;
  double t539;
  double t54;
  double t543;
  double t545;
  double t550;
  double t552;
  double t555;
  double t559;
  double t563;
  double t565;
  double t573;
  double t574;
  double t578;
  double t583;
  double t586;
  double t589;
  double t596;
  double t598;
  double t6;
  double t601;
  double t603;
  double t606;
  double t608;
  double t61;
  double t612;
  double t615;
  double t618;
  double t620;
  double t623;
  double t628;
  double t631;
  double t634;
  double t638;
  double t64;
  double t646;
  double t649;
  double t650;
  double t658;
  double t665;
  double t667;
  double t668;
  double t67;
  double t675;
  double t676;
  double t678;
  double t679;
  double t68;
  double t682;
  double t685;
  double t688;
  double t690;
  double t693;
  double t7;
  double t700;
  double t703;
  double t705;
  double t72;
  double t721;
  double t724;
  double t726;
  double t727;
  double t729;
  double t732;
  double t733;
  double t736;
  double t74;
  double t756;
  double t766;
  double t777;
  double t78;
  double t780;
  double t783;
  double t788;
  double t789;
  double t79;
  double t791;
  double t8;
  double t801;
  double t803;
  double t81;
  double t814;
  double t817;
  double t820;
  double t827;
  double t83;
  double t834;
  double t839;
  double t842;
  double t846;
  double t849;
  double t86;
  double t863;
  double t873;
  double t874;
  double t876;
  double t877;
  double t88;
  double t880;
  double t881;
  double t884;
  double t89;
  double t899;
  double t9;
  double t91;
  double t92;
  double t920;
  double t926;
  double t928;
  double t929;
  double t93;
  double t935;
  double t94;
  double t946;
  double t947;
  double t95;
  double t952;
  double t965;
  double t977;
  double t978;
  double t981;
  double t982;
  double t985;
  double t988;
  double t99;
  double t996;
  double t999;
  {
    t1 = b*b;
    t2 = 1/t1;
    t4 = a*a;
    t5 = -4.0*b+t4;
    t6 = sqrt(t5);
    t7 = 1/t6;
    t8 = t2*t7;
    t9 = v2*dbds;
    t11 = 1/b;
    t13 = 1/t6/t5;
    t14 = t11*t13;
    t16 = a*dads;
    t18 = -4.0*dbds+2.0*t16;
    t19 = v2*t18;
    t22 = t11*t7;
    t25 = 1/t1/b;
    t26 = t25*t7;
    t27 = t4*a;
    t28 = v1*t27;
    t32 = t2*t13;
    t36 = dv1ds*t27;
    t38 = v1*t4;
    t42 = v2*t4;
    t48 = dv2ds*t4;
    t51 = v2*a;
    t54 = v1*a;
    t61 = dv1ds*a;
    t64 = v1*dads;
    t67 = -t8*t9-t14*t19/2.0+t22*dv2ds+2.0*t26*t28*dbds+t32*t28*t18/2.0-t8*t36
-3.0*t8*t38*dads+t26*t42*dbds+t32*t42*t18/4.0-t8*t48/2.0-t8*t51*dads-3.0*t8*t54
*dbds-3.0/2.0*t14*t54*t18+3.0*t22*t61+3.0*t22*t64;
    t68 = dbdr*p;
    t72 = dadr+2.0*t68-2.0*dbdr*pr;
    t74 = b*p;
    t78 = a+2.0*t74-2.0*b*pr;
    t79 = t78*t13;
    t81 = a*dadr;
    t83 = -4.0*dbdr+2.0*t81;
    t86 = t72*t7-t79*t83/2.0;
    t88 = t78*t78;
    t89 = 1/t5;
    t91 = 1.0-t88*t89;
    t92 = t91*t91;
    t93 = 1/t92;
    t94 = t78*t89;
    t95 = dbdt*p;
    t99 = dadt+2.0*t95-2.0*dbdt*pr;
    t102 = t5*t5;
    t103 = 1/t102;
    t104 = t88*t103;
    t106 = a*dadt;
    t108 = -4.0*dbdt+2.0*t106;
    t110 = -2.0*t94*t99+t104*t108;
    t111 = t93*t110;
    t113 = dv2dr*t18;
    t116 = dv1ds*dadr;
    t119 = dv2dr*dbds;
    t121 = dv2ds*t83;
    t124 = dv2ds*dbdr;
    t126 = dv1dr*dads;
    t129 = v1*d2adrs;
    t132 = d2v1drs*a;
    t136 = dads*dadr;
    t138 = a*d2adrs;
    t140 = -4.0*d2bdrs+2.0*t136+2.0*t138;
    t141 = v2*t140;
    t144 = d2v2drs*t4;
    t147 = d2v1drs*t27;
    t149 = v2*d2bdrs;
    t160 = -t14*t113/2.0+3.0*t22*t116-t8*t119-t14*t121/2.0-t8*t124+3.0*t22*t126
+3.0*t22*t129+3.0*t22*t132-t14*t141/2.0-t8*t144/2.0-t8*t147-t8*t149+t22*d2v2drs
-t8*t51*d2adrs-3.0/2.0*t14*t54*t140+t32*t42*t140/4.0;
    t181 = dv1dr*t27;
    t185 = dv1dr*t4;
    t192 = t26*v1;
    t193 = t4*dadr;
    t194 = t193*dbds;
    t197 = dv1ds*t4;
    t206 = dv2dr*t4;
    t209 = t32*v2;
    t210 = t81*t18;
    t213 = a*dbdr;
    t214 = t213*dbds;
    t217 = t32*t28*t140/2.0-3.0*t8*t54*d2bdrs+2.0*t26*t28*d2bdrs+t26*t42*d2bdrs
-3.0*t8*t38*d2adrs+2.0*t26*t36*dbdr+t32*t36*t83/2.0+2.0*t26*t181*dbds-3.0*t8*
t185*dads+t32*t181*t18/2.0+6.0*t192*t194-3.0*t8*t197*dadr+t26*t48*dbdr+t32*t48*
t83/4.0+t26*t206*dbds+t209*t210/2.0+6.0*t192*t214;
    t219 = t32*v1;
    t220 = t213*t18;
    t223 = a*t83;
    t224 = t223*dbds;
    t230 = t1*t1;
    t231 = 1/t230;
    t232 = t231*t7;
    t233 = t232*v1;
    t234 = t27*dbdr;
    t235 = t234*dbds;
    t238 = dv2dr*a;
    t241 = v2*dads;
    t244 = dv2ds*a;
    t253 = t25*t13;
    t254 = t253*v1;
    t255 = t234*t18;
    t260 = t4*dbdr;
    t261 = t260*dads;
    t264 = dv1dr*a;
    t274 = v1*dadr;
    t278 = t27*t83;
    t279 = t278*dbds;
    t281 = 3.0/2.0*t219*t220+3.0/2.0*t219*t224+t32*t206*t18/4.0-6.0*t233*t235-
t8*t238*dads-t8*t241*dadr-t8*t244*dadr-3.0*t8*t61*dbdr-3.0/2.0*t14*t61*t83-t254
*t255-3.0*t8*t64*dbdr+6.0*t192*t261-3.0/2.0*t14*t264*t18-3.0/2.0*t14*t64*t83
-3.0*t8*t264*dbds-3.0*t8*t274*dbds-t254*t279;
    t285 = v2*dbdr;
    t293 = 1/t6/t102;
    t294 = t2*t293;
    t295 = t294*v1;
    t296 = t278*t18;
    t299 = v2*t83;
    t303 = t11*t293;
    t307 = t4*t83;
    t308 = t307*dads;
    t311 = t303*v1;
    t312 = t223*t18;
    t315 = t193*t18;
    t318 = t8*v1;
    t319 = t81*dads;
    t322 = t232*v2;
    t323 = t260*dbds;
    t326 = t253*v2;
    t327 = t260*t18;
    t330 = t26*v2;
    t331 = t213*dads;
    t334 = t307*dbds;
    t337 = t294*v2;
    t338 = t307*t18;
    t341 = t223*dads;
    t344 = t81*dbds;
    t347 = -3.0/2.0*t14*t274*t18+2.0*t26*t285*dbds+t32*t285*t18/2.0-3.0/4.0*
t295*t296+t32*t299*dbds/2.0+3.0/4.0*t303*t299*t18+3.0/2.0*t219*t308+9.0/4.0*
t311*t312+3.0/2.0*t219*t315-6.0*t318*t319-3.0*t322*t323-t326*t327/2.0+2.0*t330*
t331-t326*t334/2.0-3.0/8.0*t337*t338+t209*t341/2.0+2.0*t330*t344;
    t349 = t160+t217+t281+t347;
    t351 = a*t13;
    t357 = 1.0-t4*t89;
    t358 = 1/t357;
    t363 = dadr*t7-t351*t83/2.0;
    t365 = t357*t357;
    t366 = 1/t365;
    t367 = a*t89;
    t370 = t4*t103;
    t372 = -2.0*t367*dadt+t370*t108;
    t373 = t366*t372;
    t381 = t22*v2-t8*t28-t8*t42/2.0+3.0*t22*t54;
    t382 = d3bdr3*p;
    t388 = d2bdrs*p;
    t392 = d2adrs+2.0*t388-2.0*d2bdrs*pr;
    t396 = d2bdrt*p;
    t400 = d2adrt+2.0*t396-2.0*d2bdrt*pr;
    t405 = t18*t108;
    t408 = t72*t13;
    t410 = dadt*dads;
    t412 = a*d2adst;
    t414 = -4.0*d2bdst+2.0*t410+2.0*t412;
    t417 = d2bdst*p;
    t421 = d2adst+2.0*t417-2.0*d2bdst*pr;
    t425 = dbds*p;
    t429 = dads+2.0*t425-2.0*dbds*pr;
    t431 = t83*t108;
    t434 = t429*t13;
    t436 = dadt*dadr;
    t438 = a*d2adrt;
    t440 = -4.0*d2bdrt+2.0*t436+2.0*t438;
    t444 = t83*t18;
    t447 = t102*t5;
    t449 = 1/t6/t447;
    t451 = t444*t108;
    t454 = t78*t293;
    t455 = t440*t18;
    t458 = t83*t414;
    t461 = t99*t13;
    t464 = t140*t108;
    t468 = d2adst*dadr;
    t470 = dads*d2adrt;
    t472 = dadt*d2adrs;
    t474 = a*d3adr3;
    t476 = -4.0*d3bdr3+2.0*t468+2.0*t470+2.0*t472+2.0*t474;
    t479 = (d3adr3+2.0*t382-2.0*d3bdr3*pr)*t7-t392*t13*t108/2.0-t400*t13*t18/
2.0+3.0/4.0*t72*t293*t405-t408*t414/2.0-t421*t13*t83/2.0+3.0/4.0*t429*t293*t431
-t434*t440/2.0+3.0/4.0*t99*t293*t444-15.0/8.0*t78*t449*t451+3.0/4.0*t454*t455+
3.0/4.0*t454*t458-t461*t140/2.0+3.0/4.0*t454*t464-t79*t476/2.0;
    t481 = 1/t91;
    t483 = t2*dv2dt;
    t486 = t2*dv1dr;
    t489 = t2*dv1dt;
    t492 = t2*v1;
    t495 = t2*v2;
    t498 = t2*d2v2drt;
    t501 = t2*d2v1drt;
    t504 = t2*dv2dr;
    t507 = t25*dv1dr;
    t508 = t4*dbdt;
    t511 = t25*v1;
    t512 = dbdr*dbdt;
    t514 = t25*dv2dr;
    t515 = a*dbdt;
    t518 = t213*dadt;
    t521 = -t483*dadr/4.0-t486*dbdt/2.0-t489*dbdr/2.0-t492*d2bdrt/2.0-t495*
d2adrt/4.0-t498*a/4.0-t501*t4/2.0-t504*dadt/4.0+t507*t508-t486*t106+t511*t512+
t514*t515/2.0+2.0*t511*t518;
    t522 = t231*v2;
    t523 = t213*dbdt;
    t526 = t25*v2;
    t527 = dadt*dbdr;
    t530 = t81*dbdt;
    t535 = t231*v1;
    t536 = t260*dbdt;
    t539 = dadr*dbdt;
    t543 = t4*d2bdrt;
    t545 = t25*dv2dt;
    t550 = t25*dv1dt;
    t552 = a*d2bdrt;
    t555 = -3.0/2.0*t522*t523+t526*t527/2.0+2.0*t511*t530+t11*d2v1drt/2.0-3.0*
t535*t536+t526*t539/2.0-t492*t436+t511*t543+t545*t213/2.0-t492*t438-t489*t81+
t550*t260+t526*t552/2.0;
    t559 = p*p;
    t563 = pr*pr;
    t565 = dads*p-dads*pr+dbds*t559-2.0*t425*pr+dbds*t563;
    t573 = 1.0+a*p-a*pr+b*t559-2.0*t74*pr+b*t563;
    t574 = 1/t573;
    t578 = t2*d2v1dst;
    t583 = t2*d2v2dst;
    t586 = t2*dv1ds;
    t589 = t2*dv2ds;
    t596 = t4*dbds;
    t598 = t25*dv1ds;
    t601 = t4*d2bdst;
    t603 = a*dbds;
    t606 = -t495*d2adst/4.0-t578*t4/2.0-t492*d2bdst/2.0-t583*a/4.0-t586*dbdt/
2.0-t589*dadt/4.0-t483*dads/4.0-t489*dbds/2.0+t550*t596+t598*t508-t492*t412+
t511*t601+t545*t603/2.0;
    t608 = a*d2bdst;
    t612 = t25*dv2ds;
    t615 = dads*dbdt;
    t618 = dbds*dbdt;
    t620 = t603*dbdt;
    t623 = t596*dbdt;
    t628 = t603*dadt;
    t631 = t16*dbdt;
    t634 = dbds*dadt;
    t638 = -t586*t106+t526*t608/2.0-t492*t410+t612*t515/2.0+t526*t615/2.0+t511*
t618-3.0/2.0*t522*t620-3.0*t535*t623+t11*d2v1dst/2.0+2.0*t511*t628+2.0*t511*
t631+t526*t634/2.0-t489*t16;
    t646 = dadr*p-dadr*pr+dbdr*t559-2.0*t68*pr+dbdr*t563;
    t649 = t11*p;
    t650 = d2v1drs*dadt;
    t658 = t11*v1/2.0-t492*t4/2.0-t495*a/4.0;
    t665 = d2adrs*p-d2adrs*pr+d2bdrs*t559-2.0*t388*pr+d2bdrs*t563;
    t667 = t573*t573;
    t668 = 1/t667;
    t675 = dadt*p-dadt*pr+dbdt*t559-2.0*t95*pr+dbdt*t563;
    t676 = t668*t675;
    t678 = t2*p;
    t679 = dv2dt*d2bdrs;
    t682 = d2v2drt*dbds;
    t685 = dv2dr*d2bdst;
    t688 = d3v1dr3*a;
    t690 = d2v2dst*dbdr;
    t693 = t658*t646;
    t700 = d2adst*p-d2adst*pr+d2bdst*t559-2.0*t417*pr+d2bdst*t563;
    t703 = dv1dr*d2adst;
    t705 = dv1dt*d2adrs;
    t721 = -t492*dbdr/2.0+t11*dv1dr/2.0+t511*t260-t486*t4/2.0-t492*t81+t526*
t213/2.0-t504*a/4.0-t495*dadr/4.0;
    t724 = d2v1dst*dadr;
    t726 = -t67*t86*t111-t349*(dadt*t7-t351*t108/2.0)*t358+t67*t363*t373+t381*
t479*t481+(t521+t555)*t565*t574+(t606+t638)*t646*t574+t649*t650-t658*t665*t676-
t678*t679/2.0-t678*t682/2.0-t678*t685/2.0+t649*t688-t678*t690/2.0-t693*t668*
t700+t649*t703+t649*t705+t721*t700*t574+t649*t724;
    t727 = d2v1drt*dads;
    t729 = d2v2drs*dbdt;
    t732 = t2*pr;
    t733 = dv2ds*d2bdrt;
    t736 = t11*pr;
    t756 = dv1dt*t27;
    t766 = dv2dt*t4;
    t777 = dv1dt*a;
    t780 = v1*dadt;
    t783 = -t8*v2*dbdt-t14*v2*t108/2.0+t22*dv2dt+2.0*t26*t28*dbdt+t32*t28*t108/
2.0-t8*t756-3.0*t8*t38*dadt+t26*t42*dbdt+t32*t42*t108/4.0-t8*t766/2.0-t8*t51*
dadt-3.0*t8*t54*dbdt-3.0/2.0*t14*t54*t108+3.0*t22*t777+3.0*t22*t780;
    t788 = -2.0*t94*t429+t104*t18;
    t789 = t93*t788;
    t791 = v1*d3adr3;
    t801 = d2adrt*p-d2adrt*pr+d2bdrt*t559-2.0*t396*pr+d2bdrt*t563;
    t803 = t668*t565;
    t814 = t392*t7-t408*t18/2.0-t434*t83/2.0+3.0/4.0*t454*t444-t79*t140/2.0;
    t817 = dv1ds*d2adrt;
    t820 = v2*d3bdr3;
    t827 = t649*t727-t678*t729/2.0+t732*t733/2.0-t736*t703-t736*t650-t736*t727+
t732*t729/2.0-t736*t705-t736*t724-t783*t86*t789+t649*t791-t678*t733/2.0-t658*
t801*t803-t381*t814*t111-t736*t817-t736*t688+t732*t820/2.0+t732*t690/2.0+t732*
t682/2.0;
    t834 = dv1ds*dadt;
    t839 = v1*d2adst;
    t842 = d2v1dst*t27;
    t846 = d2v1dst*a;
    t849 = d2v2dst*t4;
    t863 = dv1dt*dads;
    t873 = t27*dbds;
    t874 = t873*t108;
    t876 = 3.0*t22*t834-t8*dv2dt*dbds+3.0*t22*t839-t8*t842-t8*v2*d2bdst+3.0*t22
*t846-t8*t849/2.0-t14*v2*t414/2.0-t14*dv2dt*t18/2.0-t8*dv2ds*dbdt-t14*dv2ds*
t108/2.0+3.0*t22*t863+t22*d2v2dst+3.0/4.0*t303*t19*t108-3.0*t8*t197*dadt-t254*
t874;
    t877 = t873*dbdt;
    t880 = t4*dads;
    t881 = t880*dbdt;
    t884 = t880*t108;
    t899 = t16*dadt;
    t920 = t596*t108;
    t926 = -6.0*t233*t877+6.0*t192*t881+3.0/2.0*t219*t884-3.0*t8*t54*d2bdst+2.0
*t26*t28*d2bdst-3.0*t322*t623+t26*t766*dbds+2.0*t330*t628-6.0*t318*t899+t32*t36
*t108/2.0-3.0*t8*t64*dbdt-3.0*t8*t61*dbdt+2.0*t26*t36*dbdt-3.0/2.0*t14*t64*t108
+t32*t19*dbdt/2.0-t326*t920/2.0+2.0*t26*t9*dbdt;
    t928 = t4*t18;
    t929 = t928*t108;
    t935 = t928*dbdt;
    t946 = a*t18;
    t947 = t946*dadt;
    t952 = t946*t108;
    t965 = t16*t108;
    t977 = -3.0/8.0*t337*t929-3.0/2.0*t14*t61*t108-t326*t935/2.0+t32*t9*t108/
2.0+t32*t766*t18/4.0+t26*t48*dbdt+t209*t947/2.0+2.0*t330*t631+9.0/4.0*t311*t952
+t32*t42*t414/4.0-t8*t51*d2adst+t26*t42*d2bdst+t32*t48*t108/4.0+t209*t965/2.0
-3.0*t8*t38*d2adst-3.0*t8*t777*dbds-3.0/2.0*t14*t54*t414;
    t978 = t928*dadt;
    t981 = t27*t18;
    t982 = t981*t108;
    t985 = t596*dadt;
    t988 = t981*dbdt;
    t996 = t946*dbdt;
    t999 = t603*t108;
    t1004 = dv2dt*a;
    t1009 = v2*dadt;
    t1021 = dv1dt*t4;
    t1028 = 3.0/2.0*t219*t978-3.0/4.0*t295*t982+6.0*t192*t985-t254*t988-3.0/2.0
*t14*t780*t18-3.0*t8*t780*dbds+3.0/2.0*t219*t996+3.0/2.0*t219*t999+6.0*t192*
t620-t8*t1004*dads-t8*t244*dadt-t8*t1009*dads-3.0/2.0*t14*t777*t18+t32*t756*t18
/2.0+t32*t28*t414/2.0-3.0*t8*t1021*dads+2.0*t26*t756*dbds;
    t1030 = t876+t926+t977+t1028;
    t1066 = -t8*t285-t14*t299/2.0+t22*dv2dr+2.0*t26*t28*dbdr+t32*t28*t83/2.0-t8
*t181-3.0*t8*t38*dadr+t26*t42*dbdr+t32*t42*t83/4.0-t8*t206/2.0-t8*t51*dadr-3.0*
t8*t54*dbdr-3.0/2.0*t14*t54*t83+3.0*t22*t264+3.0*t22*t274;
    t1070 = t429*t7-t79*t18/2.0;
    t1090 = a*d2bdrs;
    t1099 = dads*dbdr;
    t1102 = -t486*t410+t526*dadr*d2bdst/2.0+t526*dads*d2bdrt/2.0+t514*t608/2.0+
t526*dadt*d2bdrs/2.0+t25*d2v2dst*t213/2.0+t612*t552/2.0+t545*t1090/2.0+t511*t4*
d3bdr3-t492*t474+t526*a*d3bdr3/2.0+t545*t1099/2.0;
    t1110 = t2*d2v1drs;
    t1115 = t4*d2bdrs;
    t1124 = -t492*t472-t492*t468+t25*d2v1drs*t508-t489*t138+t25*d2v1dst*t260-
t1110*t106+t598*t543+t511*d2bdrs*dbdt+t550*t1115+t511*dbdr*d2bdst+t511*d2bdrt*
dbds+t25*d2v2drs*t515/2.0;
    t1142 = dadr*dbds;
    t1146 = t526*d2adst*dbdr/2.0+t507*t601+t25*d2v1drt*t596+t612*t527/2.0-t501*
t16+t514*t615/2.0+t612*t539/2.0-t586*t436+t598*t512+t507*t618+t545*t1142/2.0-
t578*t81;
    t1169 = t2*d2v2drs;
    t1172 = -t486*t412+t526*d2adrs*dbdt/2.0-t492*t470-t586*t438-t501*dbds/2.0-
t483*d2adrs/4.0-t578*dbdr/2.0-t1110*dbdt/2.0-t486*d2bdst/2.0-t489*d2bdrs/2.0-
t586*d2bdrt/2.0-t498*dads/4.0-t1169*dadt/4.0;
    t1179 = t81*d2bdst;
    t1182 = t552*dbds;
    t1185 = t138*dbdt;
    t1188 = t438*dbds;
    t1191 = t1090*dbdt;
    t1196 = t213*d2bdst;
    t1203 = t1142*dbdt;
    t1206 = -t589*d2adrt/4.0-t583*dadr/4.0+2.0*t511*t1179-3.0/2.0*t522*t1182+
2.0*t511*t1185+2.0*t511*t1188-3.0/2.0*t522*t1191-t495*d3adr3/4.0-3.0/2.0*t522*
t1196+2.0*t507*t628-t492*d3bdr3/2.0-3.0/2.0*t522*t1203;
    t1218 = dbdr*dbds;
    t1219 = t1218*dbdt;
    t1222 = t535*a;
    t1223 = t1099*dbdt;
    t1242 = -3.0/2.0*t231*dv2dr*t620-t2*d3v2dr3*a/4.0+2.0*t507*t631-3.0*t231*
dv1dr*t623-3.0*t535*t1219-6.0*t1222*t1223+2.0*t598*t518-t504*d2adst/4.0-3.0*
t231*dv1ds*t536+t526*d2adrt*dbds/2.0-t2*d3v1dr3*t4/2.0+t25*d2v2drt*t603/2.0;
    t1245 = 1/t230/b;
    t1252 = t1218*dadt;
    t1257 = t527*dads;
    t1262 = t136*dbdt;
    t1277 = 12.0*t1245*v1*t4*t1219+t514*t634/2.0-6.0*t1222*t1252+t11*d3v1dr3/
2.0+2.0*t511*t1257+2.0*t598*t530+2.0*t511*t1262-3.0/2.0*t522*t1223+6.0*t1245*v2
*a*t1219-3.0/2.0*t522*t1252-3.0/2.0*t231*dv2dt*t214+t550*t1218;
    t1278 = t1090*dadt;
    t1281 = t436*dbds;
    t1286 = t1115*dbdt;
    t1289 = t552*dads;
    t1297 = t543*dbds;
    t1300 = t260*d2bdst;
    t1304 = t213*d2adst;
    t1312 = 2.0*t511*t1278+2.0*t511*t1281-6.0*t1222*t1203-3.0*t535*t1286+2.0*
t511*t1289-3.0/2.0*t231*dv2ds*t523+2.0*t550*t331-3.0*t535*t1297-3.0*t535*t1300-
t489*t136+2.0*t511*t1304-3.0*t231*dv1dt*t323+2.0*t550*t344;
    t1316 = log(t573);
    t1341 = -t492*dbds/2.0+t11*dv1ds/2.0+t511*t596-t586*t4/2.0-t492*t16+t526*
t603/2.0-t589*a/4.0-t495*dads/4.0;
    t1363 = -t589*dadr/4.0+t526*t1142/2.0-t586*t81-t486*t16-t492*t138+t526*
t1090/2.0+t511*t1115+t511*t1218+t598*t260+t526*t1099/2.0+t612*t213/2.0-t492*
t136-t486*dbds/2.0;
    t1389 = -t492*d2bdrs/2.0-t1110*t4/2.0-t495*d2adrs/4.0-t1169*a/4.0-t504*dads
/4.0+t11*d2v1drs/2.0-3.0*t535*t323+2.0*t511*t331+t507*t596+2.0*t511*t344-t586*
dbdr/2.0+t514*t603/2.0-3.0/2.0*t522*t214;
    t1394 = dv2dt*dbdr;
    t1397 = v1*d2adrt;
    t1405 = t307*dadt;
    t1408 = t223*t108;
    t1428 = t193*dbdt;
    t1431 = t193*t108;
    t1436 = -t8*t1394+t22*d2v2drt+3.0*t22*t1397+2.0*t26*t181*dbdt+t26*t766*dbdr
+3.0/2.0*t219*t1405+9.0/4.0*t311*t1408-3.0*t8*t264*dbdt-3.0/2.0*t14*t780*t83+
t32*t181*t108/2.0-3.0/2.0*t14*t264*t108-3.0*t8*t274*dbdt-3.0*t322*t536+6.0*t192
*t1428+3.0/2.0*t219*t1431+2.0*t330*t530;
    t1437 = v2*t440;
    t1440 = t81*dadt;
    t1443 = t81*t108;
    t1446 = t260*t108;
    t1455 = t213*t108;
    t1461 = t223*dbdt;
    t1467 = dv1dr*dadt;
    t1479 = t234*dbdt;
    t1482 = dv2dt*t83;
    t1485 = -t14*t1437/2.0-6.0*t318*t1440+t209*t1443/2.0-t326*t1446/2.0-t8*
t1009*dadr-t8*t1004*dadr+6.0*t192*t523+3.0/2.0*t219*t1455-3.0*t8*t780*dbdr+3.0/
2.0*t219*t1461-t14*dv2dr*t108/2.0+3.0*t22*t1467-3.0/2.0*t14*t54*t440+t32*t42*
t440/4.0+t32*t28*t440/2.0-6.0*t233*t1479-t14*t1482/2.0;
    t1487 = t234*t108;
    t1492 = t278*dbdt;
    t1497 = t260*dadt;
    t1506 = t278*t108;
    t1517 = dv1dt*dadr;
    t1523 = t223*dadt;
    t1534 = -t254*t1487-3.0*t8*t777*dbdr-t254*t1492-3.0*t8*t1021*dadr+6.0*t192*
t1497-3.0/2.0*t14*t777*t83+2.0*t26*t756*dbdr-3.0/4.0*t295*t1506+t32*t766*t83/
4.0+t32*t756*t83/2.0+t26*t206*dbdt+3.0*t22*t1517-3.0*t8*t185*dadt+t209*t1523/
2.0+t32*t206*t108/4.0+t32*t285*t108/2.0-t8*t238*dadt;
    t1549 = t307*dbdt;
    t1557 = t307*t108;
    t1568 = v2*d2bdrt;
    t1570 = d2v2drt*t4;
    t1573 = d2v1drt*t27;
    t1577 = d2v1drt*a;
    t1580 = 3.0/4.0*t303*t299*t108+2.0*t330*t518+t32*t299*dbdt/2.0+2.0*t26*t285
*dbdt-3.0/2.0*t14*t274*t108-t326*t1549/2.0-3.0*t8*t38*d2adrt-t8*t51*d2adrt-3.0/
8.0*t337*t1557-3.0*t8*t54*d2bdrt+t26*t42*d2bdrt+2.0*t26*t28*d2bdrt-t8*t1568-t8*
t1570/2.0-t8*t1573-t8*dv2dr*dbdt+3.0*t22*t1577;
    t1582 = t1436+t1485+t1534+t1580;
    t1599 = -t492*dbdt/2.0+t11*dv1dt/2.0+t511*t508-t489*t4/2.0-t492*t106+t526*
t515/2.0-t483*a/4.0-t495*dadt/4.0;
    t1607 = dadr*t13;
    t1610 = dadt*t13;
    t1613 = a*t293;
    t1618 = d2adrt*t7-t1607*t108/2.0-t1610*t83/2.0+3.0/4.0*t1613*t431-t351*t440
/2.0;
    t1624 = dads*t13;
    t1647 = d2adrs*t7-t1607*t18/2.0-t1624*t83/2.0+3.0/4.0*t1613*t444-t351*t140/
2.0;
    t1650 = t732*t685/2.0+t732*t679/2.0-t736*t791-t1030*t363*t358-t1066*t1070*
t111+(t1102+t1124+t1146+t1172+t1206+t1242+t1277+t1312)*t1316+t658*(d3adr3*p-
d3adr3*pr+d3bdr3*t559-2.0*t382*pr+d3bdr3*t563)*t574-t1341*t646*t676+(t1363+
t1389)*t675*t574+t649*t817+t1582*t1070*t481-t1599*t646*t803+t1030*t86*t481-t736
*d3v2dr3/2.0-t67*t1618*t358+t783*t814*t481-t1066*(d2adst*t7-t1624*t108/2.0-
t1610*t18/2.0+3.0/4.0*t1613*t405-t351*t414/2.0)*t358+t1341*t801*t574-t783*t1647
*t358;
    t1660 = dads*t7-t351*t18/2.0;
    t1684 = t400*t7-t408*t108/2.0-t461*t83/2.0+3.0/4.0*t454*t431-t79*t440/2.0;
    t1723 = d3adr3*t7-d2adrs*t13*t108/2.0-d2adrt*t13*t18/2.0+3.0/4.0*dadr*t293*
t405-t1607*t414/2.0-d2adst*t13*t83/2.0+3.0/4.0*dads*t293*t431-t1624*t440/2.0+
3.0/4.0*dadt*t293*t444-15.0/8.0*a*t449*t451+3.0/4.0*t1613*t455+3.0/4.0*t1613*
t458-t1610*t140/2.0+3.0/4.0*t1613*t464-t351*t476/2.0;
    t1728 = t25*p;
    t1729 = t1728*v1;
    t1734 = t25*pr;
    t1738 = t116*dbdt;
    t1740 = t1568*dbds;
    t1745 = t1397*dbds;
    t1748 = t274*d2bdst;
    t1751 = t64*d2bdrt;
    t1757 = a*t440;
    t1768 = t4*d2adrt;
    t1779 = t863*dbdr;
    t1785 = t1467*dbds;
    t1808 = -3.0/2.0*t14*t846*t83-3.0*t8*t1779-3.0/2.0*t14*t863*t83-3.0*t8*
t1785+2.0*t330*t1185-6.0*t318*t138*dadt-6.0*t318*t438*dads-6.0*t318*t81*d2adst+
3.0/2.0*t219*t193*t414-6.0*t318*t436*dads+6.0*t192*t193*d2bdst;
    t1813 = t839*dbdr;
    t1827 = a*t140;
    t1831 = t32*dv1dt;
    t1834 = t32*dv1dr;
    t1843 = t124*dbdt;
    t1854 = t253*dv1dt;
    t1856 = t846*dbdr;
    t1859 = t26*dv1dt;
    t1869 = -t326*t1115*t108/2.0+2.0*t26*t1843-3.0/4.0*t294*dv1dt*t296+3.0/2.0*
t1831*t308+t32*t1570*t18/4.0-t1854*t279-3.0*t8*t1856+6.0*t1859*t261+3.0/4.0*
t303*t121*t108-t1854*t255-3.0/2.0*t14*t264*t414;
    t1880 = t61*d2bdrt;
    t1919 = -t8*t682-t8*t729-t8*t820-6.0*t8*dv1dr*t899-t8*d3v2dr3*t4/2.0-t14*
dv2ds*t440/2.0+t32*t766*t140/4.0-t8*t690+3.0/2.0*t1834*t884+3.0*t22*t703+3.0*
t22*t817;
    t1926 = t1517*dbds;
    t1937 = t213*t618;
    t1940 = t26*dv1dr;
    t1948 = -t8*d3v1dr3*t27+t32*t119*t108/2.0-3.0*t8*t1926-t14*d2v2drt*t18/2.0+
t209*t1827*dadt/2.0-t8*t733-t8*t679-18.0*t233*t1937+6.0*t1940*t881-t8*t238*
d2adst-t14*d2v2drs*t108/2.0;
    t1967 = t119*dbdt;
    t1974 = t4*t140;
    t1978 = -t14*d2v2dst*t83/2.0+3.0*t22*t705-3.0/2.0*t14*t1517*t18+3.0*t22*
t791-t14*dv2dr*t414/2.0-t14*v2*t476/2.0+3.0*t22*t650+2.0*t26*t1967+6.0*t1859*
t214+3.0/2.0*t1834*t978-3.0/8.0*t337*t1974*t108;
    t1991 = t231*t13;
    t1992 = t1991*v2;
    t1993 = dbds*t108;
    t2008 = t4*t440;
    t2012 = t26*dv2ds;
    t2016 = t1245*t7;
    t2024 = t18*dbdt;
    t2046 = 12.0*t2016*v2*t260*t618-3.0/2.0*t14*t61*t440+3.0/2.0*t1992*t260*
t2024-t326*t307*d2bdst/2.0+6.0*t192*t1252+6.0*t1859*t194-t8*dv2ds*dadt*dadr+t22
*d3v2dr3+3.0/2.0*t1831*t315+t209*t223*d2adst/2.0+2.0*t330*t1262;
    t2051 = t25*t293;
    t2052 = t2051*v2;
    t2056 = t32*dv2ds;
    t2071 = t253*dv2dt;
    t2077 = t149*dbdt;
    t2083 = -t8*dv2dt*dads*dadr+3.0/4.0*t2052*t260*t405+t2056*t1443/2.0-t326*
t1974*dbdt/2.0+t209*t136*t108/2.0-6.0*t322*t213*t634+3.0/2.0*t219*t552*t18-
t2071*t327/2.0+t209*t1757*dads/2.0+2.0*t26*t2077+t32*t849*t83/4.0;
    t2098 = t32*dv2dt;
    t2116 = t26*t144*dbdt+t32*t285*t414/2.0-3.0/4.0*t337*t81*t405+3.0/2.0*t219*
t213*t414-6.0*t322*t81*t618+t2098*t210/2.0-3.0/8.0*t337*t307*t414+2.0*t26*t147*
dbdt-t326*t81*t1993+24.0*t2016*v1*t234*t618-t8*d2v2drs*a*dadt;
    t2121 = t26*dv2dt;
    t2133 = t83*dbds;
    t2143 = t253*dv1ds;
    t2154 = t11*t449;
    t2168 = t2051*v1;
    t2175 = t1991*v1;
    t2185 = t32*t147*t108/2.0-18.0*t233*t260*t634-45.0/8.0*t2154*v1*t223*t405
-6.0*t232*dv1ds*t1479-3.0/2.0*t14*t129*t108-3.0/2.0*t14*t132*t108+3.0/2.0*t2168
*t234*t405-3.0*t254*t223*t618+3.0*t2175*t234*t2024+3.0/2.0*t219*t307*d2adst+3.0
/4.0*t303*t299*t414;
    t2187 = t27*t440;
    t2200 = t18*dadt;
    t2211 = t253*dv2ds;
    t2219 = -3.0/4.0*t295*t2187*t18+3.0/4.0*t303*t1482*t18+t32*t144*t108/4.0+
3.0/2.0*t219*t2008*dads-t326*t213*t2200-3.0*t254*t260*t2200-6.0*t322*t1219+3.0/
4.0*t303*t1437*t18-t2211*t1446/2.0+3.0*t2175*t234*t1993-t254*t234*t414;
    t2223 = t27*d2bdrt;
    t2237 = dbdr*t18;
    t2243 = t264*d2bdst;
    t2251 = t209*t81*t414/2.0-6.0*t233*t2223*dbds-t8*t244*d2adrt+2.0*t330*t1179
+t209*t438*t18/2.0-t8*v2*d2adst*dadr-t326*t2237*dbdt-6.0*t233*t234*d2bdst-3.0*
t8*t2243-t8*d2v2dst*a*dadr-t326*t1218*t108;
    t2261 = t1394*dbds;
    t2264 = t285*d2bdst;
    t2267 = t1577*dbds;
    t2313 = 2.0*t2012*t518+6.0*t192*t1196+2.0*t26*t842*dbdr-3.0/2.0*t14*t64*
t440+2.0*t26*t1740-3.0/2.0*t14*t777*t140-t8*t1004*d2adrs+9.0/4.0*t311*t1827*
t108-9.0/4.0*t295*t193*t405+6.0*t192*t543*dads+t32*t1437*dbds/2.0;
    t2320 = t253*dv1dr;
    t2327 = t32*dv2dr;
    t2333 = dads*t108;
    t2350 = dadr*t18;
    t2356 = t4*d2adrs;
    t2374 = t32*t1568*t18/2.0+3.0*t219*t81*t2200-t2320*t874+9.0/4.0*t311*t2350*
t108+2.0*t2121*t331+3.0/2.0*t219*t2356*t108+3.0/2.0*t219*t2350*dbdt+t32*t149*
t108/2.0+6.0*t1940*t985-3.0/4.0*t294*dv1dr*t982-18.0*t233*t193*t618;
    t2377 = t2*t449;
    t2394 = t129*dbdt;
    t2422 = dadt*t83;
    t2441 = -3.0/4.0*t294*dv1ds*t1506-t326*t543*t18/2.0+3.0/4.0*t303*t141*t108-
t326*t260*t414/2.0+3.0/2.0*t219*t2422*dbds+3.0*t2175*t278*t618-t326*t81*t2024+
3.0/2.0*t2168*t278*t1993-3.0*t8*d2v1drt*t4*dads-3.0*t322*t1300-t2143*t1492;
    t2469 = t54*d3bdr3;
    t2475 = -18.0*t233*t260*t615+2.0*t330*t1278+t32*t141*dbdt/2.0-3.0*t8*t185*
d2adst-3.0*t254*t307*t634-15.0/8.0*t2154*v2*t451+t32*t181*t414/2.0+t209*t436*
t18/2.0-3.0*t254*t260*t2333-3.0*t8*t2469+9.0/4.0*t311*t2422*t18;
    t2504 = -9.0/4.0*t295*t307*t2333-3.0/2.0*t14*t54*t476+6.0*t1940*t620+2.0*
t330*t1304+3.0/2.0*t1834*t999-3.0*t322*t1286-3.0*t8*t38*d3adr3+12.0*t192*t213*
t410+t209*t138*t108/2.0-t8*t51*d3adr3+2.0*t26*t28*d3bdr3;
    t2522 = t32*dv1ds;
    t2527 = t26*dv1ds;
    t2541 = t253*dv2dr;
    t2560 = t26*dv2dr;
    t2565 = t26*t849*dbdr-3.0*t8*t1738-t2541*t920/2.0+3.0/2.0*t219*t1974*dadt+
6.0*t2527*t523-3.0/2.0*t14*t1467*t18+t32*t756*t140/2.0+t2327*t965/2.0+t32*t1573
*t18/2.0+2.0*t2560*t631-t2541*t935/2.0;
    t2570 = t777*d2bdrs;
    t2588 = t27*t140;
    t2594 = 2.0*t26*t181*d2bdst-3.0*t8*t2570+t32*t842*t83/2.0+3.0/2.0*t2522*
t1455+2.0*t2560*t628-3.0*t322*t1297-t326*t223*t615+t2056*t1523/2.0+6.0*t192*
t1203-t254*t2588*dbdt-3.0*t254*t213*t2024;
    t2603 = t27*d2bdrs;
    t2613 = t834*dbdr;
    t2627 = 9.0/4.0*t303*dv1dr*t952+t26*t48*d2bdrt-3.0*t232*dv2dr*t623-6.0*t233
*t2603*dbdt+t32*t113*dbdt/2.0+6.0*t192*t260*d2adst-3.0*t8*t2613+t209*t2422*dads
/2.0+2.0*t26*t756*d2bdrs+t2098*t341/2.0-3.0/4.0*t337*t223*t2333;
    t2633 = t780*d2bdrs;
    t2656 = t132*dbdt;
    t2675 = dads*t83;
    t2688 = -3.0*t8*t2656+3.0/4.0*t2052*t307*t2024+3.0/2.0*t219*t223*d2bdst-
t326*t223*t634+2.0*t330*t1188+2.0*t26*t1573*dbds+t32*t121*dbdt/2.0+3.0/2.0*t219
*t2675*dbdt+2.0*t26*t36*d2bdrt+3.0/2.0*t219*t1768*t18+9.0/4.0*t311*t223*t414;
    t2714 = t126*dbdt;
    t2722 = 9.0/4.0*t303*dv1ds*t1408+15.0/16.0*t2377*v2*t307*t405-3.0/4.0*t337*
t223*t2200+3.0/2.0*t219*t1090*t108-t2211*t1549/2.0-3.0/8.0*t294*dv2ds*t1557-3.0
/8.0*t294*dv2dt*t338+12.0*t192*t81*t615-3.0*t8*t2714+3.0*t219*t81*t2333+3.0/2.0
*t2522*t1431;
    t2754 = 6.0*t192*t1223-9.0/4.0*t295*t223*t1993+3.0/2.0*t1992*t307*t618+3.0/
2.0*t219*t527*t18+9.0/4.0*t311*t2675*t108-9.0/4.0*t295*t213*t405-3.0/2.0*t14*
t116*t108-6.0*t8*dv1ds*t1440+6.0*t2527*t1428-3.0/2.0*t14*t126*t108-3.0/4.0*t337
*t2237*t108;
    t2759 = 2.0*t330*t1289+t1869-t8*d2v2drt*a*dads-3.0*t8*d2v1drs*t4*dadt-t8*
dv2dr*dadt*dads+15.0/8.0*t2377*v1*t278*t405-3.0*t8*d2v1dst*t4*dadr+t2504+t2688+
t2219+t2046+t2251+t2722-9.0/4.0*t295*t307*t2200+12.0*t192*t81*t634+t32*t1394*
t18/2.0+t32*t28*t476/2.0-3.0*t254*t193*t1993-3.0*t232*dv2ds*t536+t32*t299*
d2bdst/2.0-6.0*t322*t213*t615-t8*t241*d2adrt-t254*t278*d2bdst-t326*t2008*dbds/
2.0-3.0/4.0*t337*t2133*t108-9.0/4.0*t295*t223*t2024+t32*t1482*dbds/2.0+t26*t42*
d3bdr3+t26*t1570*dbds+t32*t48*t440/4.0+3.0/4.0*t303*t113*t108-6.0*t232*dv1dt*
t235-t14*dv2dt*t140/2.0+t32*t206*t414/4.0-3.0*t232*dv2dt*t323+3.0/2.0*t1992*
t260*t1993-3.0*t254*t213*t1993-6.0*t8*dv1dt*t319-3.0/4.0*t295*t2588*t108-3.0*t8
*t197*d2adrt-3.0*t8*t1021*d2adrs+9.0/4.0*t303*dv1dt*t312+t26*t206*d2bdst+3.0/
2.0*t219*t1827*dbdt+t26*t766*d2bdrs+t32*t124*t108/2.0-3.0/2.0*t14*t1397*t18+3.0
/2.0*t219*t1099*t108+6.0*t192*t1768*dbds+9.0/4.0*t311*t1757*t18-3.0/2.0*t14*
t839*t83-t254*t2603*t108+6.0*t192*t2356*dbdt-3.0/2.0*t14*t1577*t18-3.0/2.0*t14*
t274*t414+3.0/2.0*t219*t1757*dbds-3.0/8.0*t337*t2008*t18-t254*t2187*dbds+3.0/
4.0*t2052*t307*t1993+3.0/2.0*t219*t1142*t108-3.0/2.0*t14*t834*t83+3.0*t219*t223
*t410-t326*t2133*dbdt-3.0/4.0*t295*t278*t414-3.0/8.0*t294*dv2dr*t929+t32*t42*
t476/4.0-3.0*t254*t307*t615-3.0/2.0*t14*t780*t140-t8*t1009*d2adrs-3.0*t254*t193
*t2024+t32*t36*t440/2.0-t326*t213*t2333+6.0*t192*t1115*dadt-6.0*t232*dv1dr*t877
-3.0/4.0*t337*t444*dbdt+3.0/2.0*t2168*t278*t2024-t254*t2223*t18+t1808+t2627+
t2565+t2083+t2116+t2754+2.0*t2012*t530+t2185-t2143*t1487-3.0*t8*t1748+3.0/2.0*
t1831*t220+t2327*t947/2.0-3.0*t8*t2394+t1919+3.0*t22*t688-t2071*t334/2.0+t2374+
3.0/2.0*t2522*t1461+3.0*t22*t724+6.0*t192*t1182-3.0*t8*t1745+3.0/2.0*t1834*t996
+t2594-t8*t685-3.0*t8*t2633+3.0*t22*t727-t2320*t988+t1978-3.0*t8*t1813+t2313+
2.0*t26*t2261+6.0*t2527*t1497+3.0/2.0*t1831*t224+2.0*t330*t1257+2.0*t2121*t344+
2.0*t330*t1281+3.0/2.0*t2522*t1405+t2441+2.0*t26*t2264-3.0*t8*t1880-3.0*t8*
t2267+t2475-3.0*t8*t1751+6.0*t192*t1191+t1948;
    t2761 = (1.0+t78*t7)/(1.0-t78*t7);
    t2772 = t349*(t99*t7-t79*t108/2.0)*t481-t1582*t1660*t358+t1066*(t421*t7-
t434*t108/2.0-t461*t18/2.0+3.0/4.0*t454*t405-t79*t414/2.0)*t481+t67*t1684*t481-
t381*t1723*t358-t721*t565*t676+2.0*t1729*t1196+2.0*t1729*t1182-2.0*t1734*dv1dt*
t214+t732*t1738+t1728*t1740+t1728*t2264+t1728*t2077+t732*t1779+t732
*t1926+2.0*t1728*dv1dt*t214-t678*t1926-t678*t1779;
    t2778 = t381*t86;
    t2782 = t78*t103;
    t2791 = 1/t447;
    t2806 = (1.0+a*t7)/(1.0-a*t7);
    t2811 = t381*t363;
    t2817 = -2.0*t367*dads+t370*t18;
    t2823 = t1734*v1;
    t2835 = t366*t2817;
    t2837 = t732*t2714+t732*t1785+t732*t2613-t2778*t93*(-2.0*t99*t89*t429+2.0*
t2782*t429*t108-2.0*t94*t421+2.0*t2782*t18*t99-2.0*t88*t2791*t405+t104*t414)
-2.0*t1734*dv1ds*t523+t1728*t2261+t1066*t1660*t373+t732*t2469-t381*
t1684*t789-2.0*t2811/t365/t357*t2817*t372-t1734*t2264-2.0*t2823*t1182-2.0*t2823
*t1196-t1734*t1740-t1734*t2077+t1599*t665*t574-2.0*t2823*t1191+t381*t1618*t2835;
    t2853 = a*t103;
    t2871 = t231*pr;
    t2879 = t732*t2570+t732*t2656+t732*t1856+t732*t1880+t732*t1748+t732*t2243+
t381*t1647*t373+t732*t1751+t732*t1745+t732*t2267+t732*t1813+t2811*t366*(-2.0*
dadt*t89*dads+2.0*t2853*t2333-2.0*t367*d2adst+2.0*t2853*t2200-2.0*t4*t2791*t405
+t370*t414)-2.0*t2823*t1252+t732*t2633-t1734*t1967+3.0*t2871*v2*t1219-t678*
t1813-2.0*t2823*t1203-d3v0dr3*pr;
    t2895 = t231*p;
    t2916 = -t1734*t2261+2.0*t1729*t1252+t1728*t1843-t1734*t1843+2.0*t1728*
dv1ds*t523+2.0*t2778/t92/t91*t788*t110-3.0*t2895*v2*t1219+6.0*t2871*v1*t1937+
t1728*t1967-6.0*t2895*v1*t1937-2.0*t2823*t1223+t732*t2394-t678*t1856-t678*t1880
-t678*t2243-t678*t1785-t678*t1751-t678*t2394-t678*t1748;
    t2951 = -t678*t1738-t678*t1745-t678*t2714-t678*t2267-t678*t2613-2.0*t1734*
dv1dr*t620-t678*t2633+2.0*t1729*t1191-t678*t2570-t678*t2656+t783*t363*t2835-
t678*t820/2.0-t678*t2469+t649*d3v2dr3/2.0+d3v0dr3*p+2.0*t1728*dv1dr*t620+2.0*
t1729*t1223+2.0*t693/t667/t573*t565*t675+2.0*t1729*t1203;
    if (t2761/t2806 <= 0.0) printERR("d3gdr3GMAP", ERR_D3GDR3_GMAP, "t2761/t2806", t2761/t2806)
    return(t726+t827+t1650+t2772+t2837+t2879+t2916+t2951+t2759*log(t2761/t2806)/2.0);
  }
}

/* ***************************************************************************************
 * These functions return integral properties of V-liquid, as described by the Ghiorso EOS
 *****************************************************************************************/

static double integralV_GK(double r[NR], double s[NT], double t, double p) {
  const double pr	  = 1.0;
  const double tr	  = 1673.15;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, cRef, c, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double gInt;
  int i, j;

  if (fabs(p-pr) < 10.0*DBL_EPSILON) return (double) 0.0;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return 0.0;
 
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
  }
  if (v == 0.0) return 0.0;
 
  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  a	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)	 /(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
  b	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
  sum	  = a*a - 4.0*b;    
  gInt    = 0.0;

  if ((a == 0.0) && (b == 0.0)) {
    gInt      += v0*(p-pr) + v1*(p-pr)*(p-pr)/2.0 + v2*(p-pr)*(p-pr)*(p-pr)/6.0;
    
  } else if ((a != 0.0) && (b == 0.0)) {
    gInt      += (v0 - v2/(2.0*a*a))*(p-pr) + (v1 + v2/(2.0*a))*(p-pr)*(p-pr)/2.0 + v2*log(1.0+a*(p-pr))/(2.0*a*a*a);
    
  } else if ((a == 0.0) && (b != 0.0)) {
    gInt      += (v0 + v2/(2.0*b))*(p-pr) + v1*log(1.0 + b*(p-pr)*(p-pr))/(2.0*b);
    gInt      += (b > 0.0) ? -v2*atan(sqrt(b)*(p-pr))/(2.0*b*sqrt(b)) : -v2*log((1.0+sqrt(-b)*(p-pr))/(1.0-sqrt(-b)*(p-pr)))/(4.0*b*sqrt(-b));

  } else if (sum > 0.0) {
    double x = sqrt(sum);
    double y = (a + 2.0*b*(p-pr))/x;
    double z = a/x;
    double PcA = (2.0*b*pr - a + x)/(2.0*b);
    double PcB = (2.0*b*pr - a - x)/(2.0*b);
    double arg = (1.0 + y)*(1.0 - z)/((1.0 - y)*(1.0 + z));
    
    if (((pr < PcA) && (PcA < p)) || ((pr < PcB) && (PcB < p))) printf("v %g,alpha %g, v1Ref %g, v1 %g\nc %g, v2 %g, a %g, b %g\n", v, alpha, v1Ref, v1, c, v2, a, b);
    if (((pr < PcA) && (PcA < p)) || ((pr < PcB) && (PcB < p))) printERR("integralV_GK", ERR_SUM_GT_ZERO, "1.0+a*(p-pr)+b*(p-pr)*(p-pr)", 1.0+a*(p-pr)+b*(p-pr)*(p-pr))
    if (arg <= 0.0)						printERR("integralV_GK", ERR_SUM_GT_ZERO, "arg", arg)
    
    gInt      += (v0 + a*v1/b + v2/(2.0*b))*(p-pr);
    gInt      += (v1*(1.0-a*a/b) - v2*a/(2.0*b))*log(1.0+a*(p-pr)+b*(p-pr)*(p-pr))/(2.0*b);
    gInt      += (v1*a*(3.0-a*a/b) + v2*(1.0 - a*a/(2.0*b)))*log(arg)/(2.0*b*x);
    
  } else if (sum == 0.0) {
    gInt      += (v0 + 4.0*v1/a + 2.0*v2/(a*a))*(p-pr);
    gInt      += -8.0*(v2/a + v1)/(a*a*(2.0+a*(p-pr))) + 4.0*(v2/a + v1)/(a*a);
    gInt      += -4.0*(3.0*v1 + 2.0*v2/a)*log(1.0 + a*(p-pr)/2.0)/(a*a);
    
  } else if(sum < 0.0) {
    double x = sqrt(-sum);
    double y = (a + 2.0*b*(p-pr))/x;
    double z = a/x;
    
    gInt      += (v0 + a*v1/b + v2/(2.0*b))*(p-pr);
    gInt      += (v1*(1.0-a*a/b) - v2*a/(2.0*b))*log(1.0+a*(p-pr)+b*(p-pr)*(p-pr))/(2.0*b);
    gInt      += (v1*a*(3.0-a*a/b) + v2*(1.0 - a*a/(2.0*b)))*atan((z-y)/(1.0+z*y))/(b*x);
    
  }
  
  return gInt;
}

static double dIntegralV_GKdT(double r[NR], double s[NT], double t, double p) {
  const double pr	  = 1.0;
  const double tr	  = 1673.15;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double dv1dt, dgIntdt;
  int i, j;

  if (fabs(p-pr) < 10.0*DBL_EPSILON) return (double) 0.0;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return 0.0;
 
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
  }
  if (v == 0.0) return 0.0;
 
  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  a	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)	 /(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
  b	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
  sum	  = a*a - 4.0*b;
  dv1dt   = - 2.0*v0*v0*alpha*(1000.0/(mw*c*c) + t*alpha*alpha/(cp)) - v0*v0*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp));
  dgIntdt = 0.0;
  
  if ((a == 0.0) && (b == 0.0)) {
    dgIntdt   += alpha*v0*(p-pr) + dv1dt*(p-pr)*(p-pr)/2.0;
    
  } else if ((a != 0.0) && (b == 0.0)) {
    dgIntdt   += alpha*v0*(p-pr) + dv1dt*(p-pr)*(p-pr)/2.0;
    
  } else if ((a == 0.0) && (b != 0.0)) {
    dgIntdt   += alpha*v0*(p-pr) + dv1dt*log(1.0 + b*(p-pr)*(p-pr))/(2.0*b);

  } else if (sum > 0.0) {
    double x = sqrt(sum);
    double y = (a + 2.0*b*(p-pr))/x;
    double z = a/x;
    double PcA = (2.0*b*pr - a + x)/(2.0*b);
    double PcB = (2.0*b*pr - a - x)/(2.0*b);
    double arg = (1.0 + y)*(1.0 - z)/((1.0 - y)*(1.0 + z));
    
    if (((pr < PcA) && (PcA < p)) || ((pr < PcB) && (PcB < p))) printERR("dIntegralV_GKdT", ERR_SUM_GT_ZERO, "1.0+a*(p-pr)+b*(p-pr)*(p-pr)", 1.0+a*(p-pr)+b*(p-pr)*(p-pr))
    if (arg <= 0.0)						printERR("dIntegralV_GKdT", ERR_SUM_GT_ZERO, "arg", arg)
    
    dgIntdt   += (alpha*v0 + a*dv1dt/b)*(p-pr);
    dgIntdt   += dv1dt*(1.0-a*a/b)*log(1.0+a*(p-pr)+b*(p-pr)*(p-pr))/(2.0*b);
    dgIntdt   += dv1dt*a*(3.0-a*a/b)*log(arg)/(2.0*b*x);

  } else if (sum == 0.0) {
    dgIntdt   += (alpha*v0 + 4.0*dv1dt/a)*(p-pr);
    dgIntdt   += -8.0*dv1dt/(a*a*(2.0+a*(p-pr))) + 4.0*dv1dt/(a*a);
    dgIntdt   += -4.0*3.0*dv1dt*log(1.0 + a*(p-pr)/2.0)/(a*a);
    
  } else if(sum < 0.0) {
    double x = sqrt(-sum);
    double y = (a + 2.0*b*(p-pr))/x;
    double z = a/x;
    
    dgIntdt   += (alpha*v0 + a*dv1dt/b)*(p-pr);
    dgIntdt   += dv1dt*(1.0-a*a/b)*log(1.0+a*(p-pr)+b*(p-pr)*(p-pr))/(2.0*b);
    dgIntdt   += dv1dt*a*(3.0-a*a/b)*atan((z-y)/(1.0+z*y))/(b*x);
    
  }
       
  return dgIntdt;
}

static void dIntegralV_GKdr(double r[NR], double s[NT], double t, double p, double *dr) {
  const double pr	 = 1.0;
  const double tr	 = 1673.15;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double dvdr[NR], d2vdrdt[NR], dcRefdr[NR], d2cdrdt[NR], dmwdr[NR], dcpdr[NR], d3vdrdp2[NR], d4vdrdp3[NR], d5vdrdp4[NR], dmOxTotdr[NR], denom;
  int i, j;
  
  for (i=0; i<NR; i++) dr[i] = 0.0;
  if (fabs(p-pr) < 10.0*DBL_EPSILON) return;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return;
  
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }

  for (i=0; i<NR; i++) { 
    dvdr[i]    = 0.0; d2vdrdt[i]  = 0.0; dcRefdr[i]  = 0.0; d2cdrdt[i]  = 0.0; dmwdr[i] = 0.0; 
    dcpdr[i]   = 0.0; d3vdrdp2[i] = 0.0; d4vdrdp3[i] = 0.0; d5vdrdp4[i] = 0.0; 
    for (j=0, dmOxTotdr[i]=0.0; j<nc; j++) dmOxTotdr[i] += (liquid[i+1].liqToOx)[j] - (liquid[0].liqToOx)[j];
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
    for (j=0; j<NR; j++) {
      dvdr[j]	   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_v;
      d2vdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dvdt;
      dmwdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].mw;
      dcpdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cp;  
      dcRefdr[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c/mOxTot 
        	    - mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot);
      dcRefdr[j]   += (iOxAl2O3 != -1) ? ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
        	    - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
      d2cdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt/mOxTot 
        	    - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot);
      d3vdrdp2[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d4vdrdp3[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d5vdrdp4[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    }
    if (iCmpAl2O3 != -1) dcRefdr[iCmpAl2O3] += ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);
  }
  if (v == 0.0) return;

  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
  a	  = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
  b	  = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
  sum	  = a*a - 4.0*b;

  for (i=0; i<NR; i++) {
    double dalphadr   = d2vdrdt[i]/v - dvdt*dvdr[i]/(v*v);
    double dv0dr      = (dvdr[i] + v*dalphadr*(t-tr))*exp(alpha*(t-tr));      
    double dv1Refdr   = -2.0*v*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
  			-v*v*(-1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
        		      + 2.0*tr*alpha*dalphadr/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp));   
    double dcdr       = dcRefdr[i] + (t-tr)*d2cdrdt[i];
    double dv1dr      = -2.0*v0*dv0dr*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  			-v0*v0*(-1000.0*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*c*c*c) 
        			+ 2.0*t*alpha*dalphadr/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp));      
    double dv2dr      = d3vdrdp2[i];
    double ddenomdr   = 2.0*dv1Refdr*d3vdp3+2.0*v1Ref*d4vdrdp3[i]-6.0*d2vdp2*d3vdrdp2[i]; 
    double dadr       = (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdr*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)/denom
  		      - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdr;
    double dbdr       = (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/denom
  		      - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdr;		      
    double dgIntdr    = 0.0;

    if ((a == 0.0) && (b == 0.0)) {
      dgIntdr  = dv0dr*(p-pr) + dv1dr*(p-pr)*(p-pr)/2.0 + dv2dr*(p-pr)*(p-pr)*(p-pr)/6.0;
 
    } else if ((a != 0.0) && (b == 0.0)) {
      dgIntdr  = (dv0dr - dv2dr/(2.0*a*a) + v2*dadr/(a*a*a))*(p-pr) + (dv1dr + dv2dr/(2.0*a) - v2*dadr/(2.0*a*a))*(p-pr)*(p-pr)/2.0; 
      dgIntdr += (dv2dr*log(1.0+a*(p-pr)) + v2*dadr*(p-pr)/(1.0+a*(p-pr)))/(2.0*a*a*a) - 3.0*dadr*v2*log(1.0+a*(p-pr))/(2.0*a*a*a*a);
 
    } else if ((a == 0.0) && (b != 0.0)) {
      dgIntdr  = (dv0dr + dv2dr/(2.0*b) - v2*dbdr/(2.0*b*b))*(p-pr);
      dgIntdr += (dv1dr*log(1.0 + b*(p-pr)*(p-pr)) + v1*dbdr*(p-pr)*(p-pr)/(1.0 + b*(p-pr)*(p-pr)))/(2.0*b) - dbdr*v1*log(1.0 + b*(p-pr)*(p-pr))/(2.0*b*b);

      printf("*-->Exception in dIntegralV_GKdr (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
      dgIntdr  = 0.0;

    } else if (sum > 0.0) {   
      dgIntdr  = dgdrGMAP(p/10000.0, pr/10000.0, 
                          v0,       v1*10000.0,    v2*10000.0*10000.0,    a*10000.0,    b*10000.0*10000.0, 
			  dv0dr, dv1dr*10000.0, dv2dr*10000.0*10000.0, dadr*10000.0, dbdr*10000.0*10000.0)*10000.0;
       
    } else if (sum == 0.0) {
      printf("*-->Exception in dIntegralV_GKdr (liquid.c). a*a-4*b is equal to zero.\n"); liqERRstate = ERR_SUM_ZERO;
      dgIntdr  = 0.0;
 
    } else if(sum < 0.0) {
      dgIntdr  = dgdrLMAP(p/10000.0, pr/10000.0, 
                          v0,       v1*10000.0,    v2*10000.0*10000.0,    a*10000.0,    b*10000.0*10000.0, 
			  dv0dr, dv1dr*10000.0, dv2dr*10000.0*10000.0, dadr*10000.0, dbdr*10000.0*10000.0)*10000.0;
 
    }
  	  
    dr[i] = dgIntdr;
  }
}

static 
double dgdsLMAP(double p,double pr,double v0,double v1,double v2,double a,
double b,double dv0dr,double dv1dr,double dv2dr,double dadr,double dbdr) {
  double t1 = b*b;
  double t2 = 1.0/t1;
  double t4 = a*a;
  double t5 = 4.0*b-a*a;
  double t6 = sqrt(t5);
  double t7 = 1.0/t6;
  double t8 = t2*t7;
  double t11 = 1/b;
  double t13 = 1/t6/t5;
  double t18 = 4.0*dbdr-2.0*a*dadr;
  double t22 = t11*t7;
  double t25 = 1/t1/b;
  double t26 = t25*t7;
  double t67 = t8*(v2*dbdr + dv1dr*a*a*a + 3.0*v1*a*a*dadr + dv2dr*a*a/2.0 + v2*a*dadr + 3.0*v1*a*dbdr) 
             + t11*t13*t18*(v2/2.0 + 3.0*v1*a/2.0) - t2*t13*t18*(v1*a/2.0 + v2/4.0)*a*a
	     - t22*(dv2dr + 3.0*dv1dr*a + 3.0*v1*dadr)
	     - t26*dbdr*(2.0*v1*a + v2)*a*a;
  double t72 = a + 2.0*b*(p-pr);
  double t74 = atan(t72*t7);
  double t82 = - t22*(v2 + 3.0*v1*a) + t8*(v1*a + v2/2.0)*a*a;
  double t94 = t72*t72;
  double t95 = 1/t5;
  double t131 = 1.0 + a*(p-pr) + b*(p-pr)*(p-pr);
  double t132 = log(t131);
  double t162 = atan(a*t7);
  double result = t67*(t74-t162)
                + t82*((dadr+2.0*dbdr*(p-pr))*t7 - t72*t13*t18/2.0)/(1.0+t94*t95)
		+ (-t2*v1*dbdr/2.0 + t11*dv1dr/2.0 + t25*v1*t4*dbdr - t2*dv1dr*t4/2.0 - t2*v1*a*dadr + t25*v2*a*dbdr/2.0 - t2*dv2dr*a/4.0 - t2*v2*dadr/4.0)*t132
		+ (t11*v1/2.0 - t2*v1*t4/2.0 - t2*v2*a/4.0)*(dadr*(p-pr) + dbdr*(p-pr)*(p-pr))/t131
		- t82*(dadr*t7-a*t13*t18/2.0)/(1.0+t4*t95)
		+ dv0dr*(p-pr) + v1*a*dbdr*t2*(pr-p) - v2*dbdr*t2*(p-pr)/2.0 + (dv1dr*a + v1*dadr + dv2dr/2.0)*t11*(p-pr);
  return result;
}

static void dIntegralV_GKds(double r[NR], double s[NT], double t, double p, double *ds) {
  const double pr = 1.0;
  const double tr = 1673.15;
  const double y  = 0.3;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double dvds[NS], d2vdsdt[NS], dcRefds[NS], d2cdsdt[NS], dmwds[NS], dcpds[NS], d3vdsdp2[NS], d4vdsdp3[NS], d5vdsdp4[NS], denom;
  int i, j;
  
  for (i=0; i<NS; i++) ds[i] = 0.0;
  if (fabs(p-pr) < 10.0*DBL_EPSILON) return;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return;
  
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }

  for (i=0; i<NS; i++) { 
    dvds[i]    = 0.0; d2vdsdt[i]  = 0.0; dcRefds[i]  = 0.0; d2cdsdt[i]  = 0.0; dmwds[i] = 0.0; 
    dcpds[i]   = 0.0; d3vdsdp2[i] = 0.0; d4vdsdp3[i] = 0.0; d5vdsdp4[i] = 0.0;
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    double dmOxds[NS], dmOxTotds[NS];
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
    for (j=0; j<NS; j++) { dmOxds[j] = 0.0; dmOxTotds[j] = 0.0; }
    if (iCmpFe2SiO4_6 != -1) {
      for (j=0; j<NS; j++) {
        if      (iOxFe2O3  == i) dmOxds[j] += -2.0*y*s[iCmpFe2SiO4_6]*dnSpeciesds[j];		 
        else if (iOxFeO	   == i) dmOxds[j] += -2.0*(1.0-2.0*y)*s[iCmpFe2SiO4_6]*dnSpeciesds[j]; 	 
        else if (iOxFeO1_3 == i) dmOxds[j] += 2.0*s[iCmpFe2SiO4_6]*dnSpeciesds[j];
	dmOxTotds[j] += 2.0*y*s[iCmpFe2SiO4_6]*dnSpeciesds[j]; 
      }
      if      (iOxFe2O3  == i) dmOxds[iCmpFe2SiO4_6] += -2.0*y*nSpecies;	   
      else if (iOxFeO	 == i) dmOxds[iCmpFe2SiO4_6] += -2.0*(1.0-2.0*y)*nSpecies; 
      else if (iOxFeO1_3 == i) dmOxds[iCmpFe2SiO4_6] += 2.0*nSpecies;
      dmOxTotds[iCmpFe2SiO4_6] += 2.0*y*nSpecies;		   
    }
    if (iCmpFe2AlO4_1 != -1) {
      for (j=0; j<NS; j++) {
        if      (iOxFe2O3  == i) dmOxds[j] += -2.0*y*s[iCmpFe2AlO4_1]*dnSpeciesds[j];		 
        else if (iOxFeO	   == i) dmOxds[j] += -2.0*(1.0-2.0*y)*s[iCmpFe2AlO4_1]*dnSpeciesds[j]; 	 
        else if (iOxFeO1_3 == i) dmOxds[j] += 2.0*s[iCmpFe2AlO4_1]*dnSpeciesds[j];
	dmOxTotds[j] += 2.0*y*s[iCmpFe2AlO4_1]*dnSpeciesds[j]; 
      }
      if      (iOxFe2O3  == i) dmOxds[iCmpFe2AlO4_1] += -2.0*y*nSpecies;	   
      else if (iOxFeO	 == i) dmOxds[iCmpFe2AlO4_1] += -2.0*(1.0-2.0*y)*nSpecies; 
      else if (iOxFeO1_3 == i) dmOxds[iCmpFe2AlO4_1] += 2.0*nSpecies;
      dmOxTotds[iCmpFe2AlO4_1] += 2.0*y*nSpecies;		   
    }
    for (j=0; j<NS; j++) {
      dvds[j]	   += dmOxds[j]*bulkSystem[i].gk_v;
      d2vdsdt[j]   += dmOxds[j]*bulkSystem[i].gk_dvdt;
      dmwds[j]     += dmOxds[j]*bulkSystem[i].mw;
      dcpds[j]     += dmOxds[j]*bulkSystem[i].gk_cp;  
      dcRefds[j]   += dmOxds[j]*bulkSystem[i].gk_c/mOxTot - mOx[i]*bulkSystem[i].gk_c*dmOxTotds[j]/(mOxTot*mOxTot);
      dcRefds[j]   += (iOxAl2O3 != -1) ? dmOxds[j]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
        	    - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotds[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
      d2cdsdt[j]   += dmOxds[j]*bulkSystem[i].gk_dcdt/mOxTot - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotds[j]/(mOxTot*mOxTot);
      d3vdsdp2[j]  += dmOxds[j]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d4vdsdp3[j]  += dmOxds[j]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d5vdsdp4[j]  += dmOxds[j]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    }
  }
  if (v == 0.0) return;

  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
  a	  = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
  b	  = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
  sum	  = a*a - 4.0*b;

  for (i=0; i<NS; i++) {
    double dalphads   = d2vdsdt[i]/v - dvdt*dvds[i]/(v*v);
    double dv0ds      = (dvds[i] + v*dalphads*(t-tr))*exp(alpha*(t-tr));      
    double dv1Refds   = -2.0*v*dvds[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
  			-v*v*(-1000.0*(cRef*dmwds[i]+2.0*mw*dcRefds[i])/(mw*mw*cRef*cRef*cRef) 
        		      + 2.0*tr*alpha*dalphads/(cp) - tr*alpha*alpha*dcpds[i]/(cp*cp));   
    double dcds       = dcRefds[i] + (t-tr)*d2cdsdt[i];
    double dv1ds      = -2.0*v0*dv0ds*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  			-v0*v0*(-1000.0*(c*dmwds[i]+2.0*mw*dcds)/(mw*mw*c*c*c) 
        			+ 2.0*t*alpha*dalphads/(cp) - t*alpha*alpha*dcpds[i]/(cp*cp));      
    double dv2ds      = d3vdsdp2[i];
    double ddenomds   = 2.0*dv1Refds*d3vdp3+2.0*v1Ref*d4vdsdp3[i]-6.0*d2vdp2*d3vdsdp2[i]; 
    double dads       = (d3vdsdp2[i]*d3vdp3+d2vdp2*d4vdsdp3[i]-dv1Refds*d4vdp4/2.0-v1Ref*d5vdsdp4[i]/2.0)/denom
  		      - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomds;
    double dbds       = (d3vdsdp2[i]*d4vdp4/4.0+d2vdp2*d5vdsdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdsdp3[i])/denom
  		      - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomds;		      
    double dgIntds    = 0.0;

    if ((a == 0.0) && (b == 0.0)) {
      dgIntds  = dv0ds*(p-pr) + dv1ds*(p-pr)*(p-pr)/2.0 + dv2ds*(p-pr)*(p-pr)*(p-pr)/6.0;
 
    } else if ((a != 0.0) && (b == 0.0)) {
      dgIntds  = (dv0ds - dv2ds/(2.0*a*a) + v2*dads/(a*a*a))*(p-pr) + (dv1ds + dv2ds/(2.0*a) - v2*dads/(2.0*a*a))*(p-pr)*(p-pr)/2.0; 
      dgIntds += (dv2ds*log(1.0+a*(p-pr)) + v2*dads*(p-pr)/(1.0+a*(p-pr)))/(2.0*a*a*a) - 3.0*dads*v2*log(1.0+a*(p-pr))/(2.0*a*a*a*a);
 
    } else if ((a == 0.0) && (b != 0.0)) {
      dgIntds  = (dv0ds + dv2ds/(2.0*b) - v2*dbds/(2.0*b*b))*(p-pr);
      dgIntds += (dv1ds*log(1.0 + b*(p-pr)*(p-pr)) + v1*dbds*(p-pr)*(p-pr)/(1.0 + b*(p-pr)*(p-pr)))/(2.0*b) - dbds*v1*log(1.0 + b*(p-pr)*(p-pr))/(2.0*b*b);

      printf("*-->Exception in dIntegralV_GKds (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
      dgIntds  = 0.0;

    } else if (sum > 0.0) {
      eosIntegralBranch = GMAPeosBRANCH;   
      dgIntds  = dgdrGMAP(p/10000.0, pr/10000.0, 
                          v0,       v1*10000.0,    v2*10000.0*10000.0,    a*10000.0,    b*10000.0*10000.0, 
                          dv0ds, dv1ds*10000.0, dv2ds*10000.0*10000.0, dads*10000.0, dbds*10000.0*10000.0)*10000.0;
      eosIntDGDS[i] = dgIntds;
       
    } else if (sum == 0.0) {
      printf("*-->Exception in dIntegralV_GKds (liquid.c). a*a-4*b is equal to zero.\n"); liqERRstate = ERR_SUM_ZERO;
      dgIntds  = 0.0;
 
    } else if(sum < 0.0) {
      eosIntegralBranch = LMAPeosBRANCH;   
      dgIntds  = dgdsLMAP(p/10000.0, pr/10000.0, 
                          v0,       v1*10000.0,    v2*10000.0*10000.0,    a*10000.0,    b*10000.0*10000.0, 
			  dv0ds, dv1ds*10000.0, dv2ds*10000.0*10000.0, dads*10000.0, dbds*10000.0*10000.0)*10000.0;
      eosIntDGDS[i] = dgIntds;
 
    }
  	  
    ds[i] = dgIntds;
  }
}

static void d2IntegralV_GKdr2(double r[NR], double s[NT], double t, double p, double d2r[NR][NR]) {
  const double pr	  = 1.0; 
  const double tr	  = 1673.15;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double dvdr[NR], d2vdrdt[NR], dcRefdr[NR], d2cdrdt[NR], dmwdr[NR], dcpdr[NR], d3vdrdp2[NR], d4vdrdp3[NR], d5vdrdp4[NR], dmOxTotdr[NR], denom;
  double d2cRefdr2[NR][NR], d3cdr2dt[NR][NR];
  int i, j, k;
  
  for (i=0; i<NR; i++) for (j=0; j<NR; j++) d2r[i][j] = 0.0;
  if (fabs(p-pr) < 10.0*DBL_EPSILON) return;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return;
  
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }

  for (i=0; i<NR; i++) { 
    dvdr[i]    = 0.0; d2vdrdt[i]  = 0.0; dcRefdr[i]  = 0.0; d2cdrdt[i]  = 0.0; dmwdr[i] = 0.0; 
    dcpdr[i]   = 0.0; d3vdrdp2[i] = 0.0; d4vdrdp3[i] = 0.0; d5vdrdp4[i] = 0.0; 
    for (j=0, dmOxTotdr[i]=0.0; j<nc; j++) dmOxTotdr[i] += (liquid[i+1].liqToOx)[j] - (liquid[0].liqToOx)[j];
    for (j=i; j<NR; j++) { d2cRefdr2[i][j] = 0.0; d3cdr2dt[i][j] = 0.0; }
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
    
    for (j=0; j<NR; j++) {
      dvdr[j]	   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_v;
      d2vdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dvdt;
      dmwdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].mw;
      dcpdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cp;  
      dcRefdr[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c/mOxTot 
        	    - mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot);
      dcRefdr[j]   += (iOxAl2O3 != -1) ? ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
        	    - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
      d2cdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt/mOxTot 
        	    - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot);
      d3vdrdp2[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d4vdrdp3[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d5vdrdp4[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    }
    if (iCmpAl2O3 != -1) dcRefdr[iCmpAl2O3] += ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);
    
    for (j=0; j<NR; j++) {
      for (k=j; k<NR; k++) {
        d2cRefdr2[j][k] += -((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c*dmOxTotdr[k]/(mOxTot*mOxTot)		
        		 -  ((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot)
        		 + 2.0*mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot);
        d2cRefdr2[j][k] += (iOxAl2O3 != -1) ? 
	                 - 2.0*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot)
        		 - 2.0*((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot)
			 + 6.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot*mOxTot)
        		 : 0.0;
        d3cdr2dt[j][k]  += -((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt*dmOxTotdr[k]/(mOxTot*mOxTot) 
        		 -  ((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot)
        		 + 2.0*mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot);
      }
      if (iCmpAl2O3 != -1) d2cRefdr2[(j<iCmpAl2O3) ? j : iCmpAl2O3][(j>iCmpAl2O3) ? j : iCmpAl2O3] +=
        ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
        - 2.0*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot);
    }
    if (iCmpAl2O3 != -1) d2cRefdr2[iCmpAl2O3][iCmpAl2O3] +=
      ((liquid[iCmpAl2O3+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
      - 2.0*mOx[i]*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[iCmpAl2O3]/(mOxTot*mOxTot*mOxTot);
    
  }
  if (v == 0.0) return;

  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
  a	  = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
  b	  = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
  sum	  = a*a - 4.0*b;

  for (i=0; i<NR; i++) {
    double dalphadri   = d2vdrdt[i]/v - dvdt*dvdr[i]/(v*v);
    double dv0dri      = (dvdr[i] + v*dalphadri*(t-tr))*exp(alpha*(t-tr));	
    double dv1Refdri   = -2.0*v*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
  			 -v*v*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
        		       + 2.0*tr*alpha*dalphadri/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp));   
    double dcdri       = dcRefdr[i] + (t-tr)*d2cdrdt[i];
    double dv1dri      = -2.0*v0*dv0dri*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  			 -v0*v0*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c) 
        			 + 2.0*t*alpha*dalphadri/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp));      
    double ddenomdri   = 2.0*dv1Refdri*d3vdp3+2.0*v1Ref*d4vdrdp3[i]-6.0*d2vdp2*d3vdrdp2[i]; 
    double dadri       = (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdri*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)/denom
  		       - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdri;
    double dbdri       = (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/denom
  		       - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdri; 		      

    for (j=i; j<NR; j++) {
      double dalphadrj   = d2vdrdt[j]/v - dvdt*dvdr[j]/(v*v);
      double dv0drj	 = (dvdr[j] + v*dalphadrj*(t-tr))*exp(alpha*(t-tr));	  
      double dv1Refdrj   = -2.0*v*dvdr[j]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
  			   -v*v*(- 1000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])/(mw*mw*cRef*cRef*cRef) 
  				 + 2.0*tr*alpha*dalphadrj/(cp) - tr*alpha*alpha*dcpdr[j]/(cp*cp));   
      double dcdrj	 = dcRefdr[j] + (t-tr)*d2cdrdt[j];
      double dv1drj	 = -2.0*v0*dv0drj*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  			   -v0*v0*(- 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c) 
  				   + 2.0*t*alpha*dalphadrj/(cp) - t*alpha*alpha*dcpdr[j]/(cp*cp));	
      double ddenomdrj   = 2.0*dv1Refdrj*d3vdp3+2.0*v1Ref*d4vdrdp3[j]-6.0*d2vdp2*d3vdrdp2[j]; 
      double dadrj	 = (d3vdrdp2[j]*d3vdp3+d2vdp2*d4vdrdp3[j]-dv1Refdrj*d4vdp4/2.0-v1Ref*d5vdrdp4[j]/2.0)/denom
  			 - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdrj;
      double dbdrj	 = (d3vdrdp2[j]*d4vdp4/4.0+d2vdp2*d5vdrdp4[j]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[j])/denom
  		       - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdrj; 		      

      double d2alphadr2   = -d2vdrdt[i]*dvdr[j]/(v*v)-d2vdrdt[j]*dvdr[i]/(v*v)+2.0*dvdt*dvdr[i]*dvdr[j]/(v*v*v);
      double d2v0dr2	  = dvdr[i]*dalphadrj*(t-tr)*exp(alpha*(t-tr))
        		  + dvdr[j]*dalphadri*(t-tr)*exp(alpha*(t-tr))
        		  + v*d2alphadr2*(t-tr)*exp(alpha*(t-tr))
        		  + v*dalphadri*pow(t-tr,2.0)*dalphadrj*exp(alpha*(t-tr));
      double d2v1Refdr2   = -2.0*dvdr[j]*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
        		  - 2.0*v*dvdr[i]*(- 1000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])/(mw*mw*cRef*cRef*cRef) 
        				   + 2.0*tr*alpha*dalphadrj/(cp) - tr*alpha*alpha*dcpdr[j]/(cp*cp))
  			  - 2.0*v*dvdr[j]*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
  					   + 2.0*tr*alpha*dalphadri/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp))
        		   -v*v*(- 1000.0*(dcRefdr[j]*dmwdr[i]+2.0*dmwdr[j]*dcRefdr[i]+2.0*mw*d2cRefdr2[i][j])/(mw*mw*cRef*cRef*cRef)
        			 + 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])*(2.0*dmwdr[j]*cRef+3.0*mw*dcRefdr[j])/(mw*mw*mw*cRef*cRef*cRef*cRef) 
        			 + 2.0*tr*alpha*d2alphadr2/(cp)
        			 + 2.0*tr*dalphadrj*dalphadri/(cp) - 2.0*tr*alpha*dalphadri*dcpdr[j]/(cp*cp) 
        			 - 2.0*tr*alpha*dalphadrj*dcpdr[i]/(cp*cp) + 2.0*tr*alpha*alpha*dcpdr[i]*dcpdr[j]/(cp*cp*cp)); 
      double d2cdr2	 = d2cRefdr2[i][j] + (t-tr)*d3cdr2dt[i][j];
      double d2v1dr2	 = -2.0*dv0drj*dv0dri*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
        		  - 2.0*v0*d2v0dr2*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
        		  - 2.0*v0*dv0dri*(- 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c) 
        				   + 2.0*t*alpha*dalphadrj/(cp) - t*alpha*alpha*dcpdr[j]/(cp*cp))
  			  - 2.0*v0*dv0drj*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c) 
  					   + 2.0*t*alpha*dalphadri/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp))
        		   -v0*v0*(- 1000.0*(dcdrj*dmwdr[i]+2.0*dmwdr[j]*dcdri+2.0*mw*d2cdr2)/(mw*mw*c*c*c)
        			   + 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)*(2.0*dmwdr[j]*c+3.0*mw*dcdrj)/(mw*mw*mw*c*c*c*c) 
        			   + 2.0*t*alpha*d2alphadr2/(cp)
        			   + 2.0*t*dalphadrj*dalphadri/(cp) - 2.0*t*alpha*dalphadri*dcpdr[j]/(cp*cp) 
        			   - 2.0*t*alpha*dalphadrj*dcpdr[i]/(cp*cp) + 2.0*t*alpha*alpha*dcpdr[i]*dcpdr[j]/(cp*cp*cp));   
      double d2denomdr2   = 2.0*d2v1Refdr2*d3vdp3 + 2.0*dv1Refdri*d4vdrdp3[j] + 2.0*dv1Refdrj*d4vdrdp3[i] - 6.0*d3vdrdp2[j]*d3vdrdp2[i]; 
      double d2adr2	 = (d3vdrdp2[i]*d4vdrdp3[j]+d3vdrdp2[j]*d4vdrdp3[i]-d2v1Refdr2*d4vdp4/2.0-dv1Refdri*d5vdrdp4[j]/2.0-dv1Refdrj*d5vdrdp4[i]/2.0)/denom
        		 - (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdri*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)*ddenomdrj/(denom*denom)
  			 - (d3vdrdp2[j]*d3vdp3+d2vdp2*d4vdrdp3[j]-dv1Refdrj*d4vdp4/2.0-v1Ref*d5vdrdp4[j]/2.0)*ddenomdri/(denom*denom)
  			 + 2.0*(d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*ddenomdri*ddenomdrj/(denom*denom*denom)
  			 - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*d2denomdr2/(denom*denom);
      double d2bdr2	 = (d3vdrdp2[i]*d5vdrdp4[j]/4.0+d3vdrdp2[j]*d5vdrdp4[i]/4.0-2.0/3.0*d4vdrdp3[j]*d4vdrdp3[i])/denom
  			 - (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])*ddenomdrj/(denom*denom)
  			 - (d3vdrdp2[j]*d4vdp4/4.0+d2vdp2*d5vdrdp4[j]/4.0-2.0*d4vdrdp3[j]*d3vdp3/3.0)*ddenomdri/(denom*denom)
        		 + 2.0*(d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*ddenomdri*ddenomdrj/(denom*denom*denom)
        		 - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*d2denomdr2/(denom*denom);			
      double d2gIntdr2   = 0.0;

      if ((a == 0.0) && (b == 0.0)) {
  	d2gIntdr2  = d2v0dr2*(p-pr) + d2v1dr2*(p-pr)*(p-pr)/2.0;
 
      } else if ((a != 0.0) && (b == 0.0)) {
  	printf("*-->Exception in d2IntegralV_GKdr2 (liquid.c). a is not equal to zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
  	d2gIntdr2  = 0.0;
 
      } else if ((a == 0.0) && (b != 0.0)) {
  	printf("*-->Exception in d2IntegralV_GKdr2 (liquid.c). a is zero, b is not equal to zero.\n"); liqERRstate = ERR_A_ZERO;
  	d2gIntdr2  = 0.0;

      } else if (sum > 0.0) {
  	d2gIntdr2  = d2gdr2GMAP(p/10000.0, pr/10000.0, 
	                        v0,           v1*10000.0,      d2vdp2*10000.0*10000.0,      a*10000.0,      b*10000.0*10000.0, 
				dv0dri,   dv1dri*10000.0, d3vdrdp2[i]*10000.0*10000.0,  dadri*10000.0,  dbdri*10000.0*10000.0, 
  				dv0drj,   dv1drj*10000.0, d3vdrdp2[j]*10000.0*10000.0,  dadrj*10000.0,  dbdrj*10000.0*10000.0, 
        			d2v0dr2, d2v1dr2*10000.0,                         0.0, d2adr2*10000.0, d2bdr2*10000.0*10000.0)*10000.0;
 
      } else if (sum == 0.0) {
  	printf("*-->Exception in d2IntegralV_GKdr2 (liquid.c). a*a-4*b is equal to zero.\n"); liqERRstate = ERR_SUM_ZERO;
  	d2gIntdr2  = 0.0;
 
      } else if(sum < 0.0) {
  	d2gIntdr2  = d2gdr2LMAP(p/10000.0, pr/10000.0, 
	                        v0,           v1*10000.0,      d2vdp2*10000.0*10000.0,      a*10000.0,      b*10000.0*10000.0, 
				dv0dri,   dv1dri*10000.0, d3vdrdp2[i]*10000.0*10000.0,  dadri*10000.0,  dbdri*10000.0*10000.0, 
  				dv0drj,   dv1drj*10000.0, d3vdrdp2[j]*10000.0*10000.0,  dadrj*10000.0,  dbdrj*10000.0*10000.0, 
        			d2v0dr2, d2v1dr2*10000.0,                         0.0, d2adr2*10000.0, d2bdr2*10000.0*10000.0)*10000.0;
 
      }

      d2r[i][j] += d2gIntdr2;
      if (i != j) d2r[j][i] += d2gIntdr2;

    }
  }
  
}

static void d2IntegralV_GKdrds(double r[NR], double s[NT], double t, double p, double drds[NR][NS]) {
  const double pr = 1.0;
  const double tr = 1673.15;
  const double y  = 0.3;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double dvdr[NR], d2vdrdt[NR], dcRefdr[NR], d2cdrdt[NR], dmwdr[NR], dcpdr[NR], d3vdrdp2[NR], d4vdrdp3[NR], d5vdrdp4[NR], dmOxTotdr[NR], denom;
  double dvds[NS], d2vdsdt[NS], dcRefds[NS], d2cdsdt[NS], dmwds[NS], dcpds[NS], d3vdsdp2[NS], d4vdsdp3[NS], d5vdsdp4[NS], dmOxTotds[NS];
  double d2vdrds[NR][NS], d3vdrdsdt[NR][NS], d2cRefdrds[NR][NS], d3cdrdsdt[NR][NS], d2mwdrds[NR][NS], d2cpdrds[NR][NS], d4vdrdsdp2[NR][NS], 
         d5vdrdsdp3[NR][NS], d6vdrdsdp4[NR][NS], d2mOxTotdrds[NR][NS];
  int i, j, k;
  
  for (i=0; i<NR; i++) for (j=0; j<NS; j++) drds[i][j] = 0.0;
  if (fabs(p-pr) < 10.0*DBL_EPSILON) return;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return;
  
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }

  for (i=0; i<NR; i++) { 
    dvdr[i]    = 0.0; d2vdrdt[i]  = 0.0; dcRefdr[i]  = 0.0; d2cdrdt[i]  = 0.0; dmwdr[i] = 0.0; 
    dcpdr[i]   = 0.0; d3vdrdp2[i] = 0.0; d4vdrdp3[i] = 0.0; d5vdrdp4[i] = 0.0; 
    for (j=0, dmOxTotdr[i]=0.0; j<nc; j++) dmOxTotdr[i] += (liquid[i+1].liqToOx)[j] - (liquid[0].liqToOx)[j];
  }
  for (i=0; i<NS; i++) { 
    dvds[i]    = 0.0; d2vdsdt[i]  = 0.0; dcRefds[i]  = 0.0; d2cdsdt[i]  = 0.0; dmwds[i] = 0.0; 
    dcpds[i]   = 0.0; d3vdsdp2[i] = 0.0; d4vdsdp3[i] = 0.0; d5vdsdp4[i] = 0.0; dmOxTotds[i] = 0.0;
  }
  if (iCmpFe2SiO4_6 != -1) {
    for (i=0; i<NS; i++) dmOxTotds[i] += 2.0*y*s[iCmpFe2SiO4_6]*dnSpeciesds[i];
    dmOxTotds[iCmpFe2SiO4_6] += 2.0*y*nSpecies;
  }
  if (iCmpFe2AlO4_1 != -1) {
    for (i=0; i<NS; i++) dmOxTotds[i] += 2.0*y*s[iCmpFe2AlO4_1]*dnSpeciesds[i];
    dmOxTotds[iCmpFe2AlO4_1] += 2.0*y*nSpecies;
  }
  for (j=0; j<NR; j++) for (k=0; k<NS; k++) {
    d2mOxTotdrds[j][k] = 0.0; d2vdrds[j][k]      = 0.0; d3vdrdsdt[j][k]    = 0.0; d2cRefdrds[j][k]   = 0.0; d3cdrdsdt[j][k]    = 0.0;
    d2mwdrds[j][k]     = 0.0; d2cpdrds[j][k]     = 0.0; d4vdrdsdp2[j][k]   = 0.0; d5vdrdsdp3[j][k]   = 0.0; d6vdrdsdp4[j][k]   = 0.0;
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    double dmOxds[NS];
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;

    for (j=0; j<NS; j++) dmOxds[j] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      for (j=0; j<NS; j++) {
        if      (iOxFe2O3  == i) dmOxds[j] += -2.0*y*s[iCmpFe2SiO4_6]*dnSpeciesds[j];		 
        else if (iOxFeO	   == i) dmOxds[j] += -2.0*(1.0-2.0*y)*s[iCmpFe2SiO4_6]*dnSpeciesds[j]; 	 
        else if (iOxFeO1_3 == i) dmOxds[j] += 2.0*s[iCmpFe2SiO4_6]*dnSpeciesds[j];
      }
      if      (iOxFe2O3  == i) dmOxds[iCmpFe2SiO4_6] += -2.0*y*nSpecies;	   
      else if (iOxFeO	 == i) dmOxds[iCmpFe2SiO4_6] += -2.0*(1.0-2.0*y)*nSpecies; 
      else if (iOxFeO1_3 == i) dmOxds[iCmpFe2SiO4_6] += 2.0*nSpecies;		   
    }
    if (iCmpFe2AlO4_1 != -1) {
      for (j=0; j<NS; j++) {
        if      (iOxFe2O3  == i) dmOxds[j] += -2.0*y*s[iCmpFe2AlO4_1]*dnSpeciesds[j];		 
        else if (iOxFeO	   == i) dmOxds[j] += -2.0*(1.0-2.0*y)*s[iCmpFe2AlO4_1]*dnSpeciesds[j]; 	 
        else if (iOxFeO1_3 == i) dmOxds[j] += 2.0*s[iCmpFe2AlO4_1]*dnSpeciesds[j];
      }
      if      (iOxFe2O3  == i) dmOxds[iCmpFe2AlO4_1] += -2.0*y*nSpecies;	   
      else if (iOxFeO	 == i) dmOxds[iCmpFe2AlO4_1] += -2.0*(1.0-2.0*y)*nSpecies; 
      else if (iOxFeO1_3 == i) dmOxds[iCmpFe2AlO4_1] += 2.0*nSpecies;		   
    }
    for (j=0; j<NS; j++) {
      dvds[j]	   += dmOxds[j]*bulkSystem[i].gk_v;
      d2vdsdt[j]   += dmOxds[j]*bulkSystem[i].gk_dvdt;
      dmwds[j]     += dmOxds[j]*bulkSystem[i].mw;
      dcpds[j]     += dmOxds[j]*bulkSystem[i].gk_cp;  
      dcRefds[j]   += dmOxds[j]*bulkSystem[i].gk_c/mOxTot - mOx[i]*bulkSystem[i].gk_c*dmOxTotds[j]/(mOxTot*mOxTot);
      dcRefds[j]   += (iOxAl2O3 != -1) ? dmOxds[j]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
        	    - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotds[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
      d2cdsdt[j]   += dmOxds[j]*bulkSystem[i].gk_dcdt/mOxTot - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotds[j]/(mOxTot*mOxTot);
      d3vdsdp2[j]  += dmOxds[j]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d4vdsdp3[j]  += dmOxds[j]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d5vdsdp4[j]  += dmOxds[j]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    }
    
    for (j=0; j<NR; j++) {
      dvdr[j]	   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_v;
      d2vdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dvdt;
      dmwdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].mw;
      dcpdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cp;  
      dcRefdr[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c/mOxTot 
        	    - mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot);
      dcRefdr[j]   += (iOxAl2O3 != -1) ? ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
        	    - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
      d2cdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt/mOxTot 
        	    - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot);
      d3vdrdp2[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d4vdrdp3[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d5vdrdp4[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    }
    if (iCmpAl2O3 != -1) dcRefdr[iCmpAl2O3] += ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);
    for (j=0; j<NR; j++) for (k=0; k<NS; k++) {
      d2cRefdrds[j][k] += -((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c*dmOxTotds[k]/(mOxTot*mOxTot) 
        	        - (dmOxds[k]*bulkSystem[i].gk_c*dmOxTotdr[j] + mOx[i]*bulkSystem[i].gk_c*d2mOxTotdrds[j][k])/(mOxTot*mOxTot)
        	        + 2.0*mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]*dmOxTotds[k]/(mOxTot*mOxTot*mOxTot);			
      d2cRefdrds[j][k] += (iOxAl2O3 != -1) ? -2.0*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotds[k]/(mOxTot*mOxTot*mOxTot)
        	        - 2.0*(dmOxds[k]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j] + mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*d2mOxTotdrds[j][k])/(mOxTot*mOxTot*mOxTot)
			+ 6.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]*dmOxTotds[k]/(mOxTot*mOxTot*mOxTot*mOxTot) 
			: 0.0;
      d3cdrdsdt[j][k]  += -((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt*dmOxTotds[k]/(mOxTot*mOxTot)       
        	        - (dmOxds[k]*bulkSystem[i].gk_dcdt*dmOxTotdr[j] + mOx[i]*bulkSystem[i].gk_dcdt*d2mOxTotdrds[j][k])/(mOxTot*mOxTot) 
			+ 2.0*mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]*dmOxTotds[k]/(mOxTot*mOxTot*mOxTot);
    }
    if (iCmpAl2O3 != -1) for (k=0; k<NS; k++) {
      d2cRefdrds[iCmpAl2O3][k] += ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*dmOxds[k]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
                                - 2.0*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3*dmOxTotds[k]/(mOxTot*mOxTot*mOxTot);
    }
  }
  if (v == 0.0) return;

  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
  a	  = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
  b	  = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
  sum	  = a*a - 4.0*b;

  for (i=0; i<NR; i++) {
    double dalphadr   = d2vdrdt[i]/v - dvdt*dvdr[i]/(v*v);
    double dv0dr      = (dvdr[i] + v*dalphadr*(t-tr))*exp(alpha*(t-tr));      
    double dv1Refdr   = -2.0*v*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
  			-v*v*(-1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
        		      + 2.0*tr*alpha*dalphadr/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp));   
    double dcdr       = dcRefdr[i] + (t-tr)*d2cdrdt[i];
    double dv1dr      = -2.0*v0*dv0dr*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  			-v0*v0*(-1000.0*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*c*c*c) 
        			+ 2.0*t*alpha*dalphadr/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp));      
    double dv2dr      = d3vdrdp2[i];
    double ddenomdr   = 2.0*dv1Refdr*d3vdp3+2.0*v1Ref*d4vdrdp3[i]-6.0*d2vdp2*d3vdrdp2[i]; 
    double dadr       = (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdr*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)/denom
  		      - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdr;
    double dbdr       = (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/denom
  		      - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdr;
    for (j=0; j<NS; j++) {
      double dalphads	= d2vdsdt[j]/v - dvdt*dvds[j]/(v*v);
      double dv0ds	= (dvds[j] + v*dalphads*(t-tr))*exp(alpha*(t-tr));	
      double dv1Refds	= -2.0*v*dvds[j]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
     			  -v*v*(-1000.0*(cRef*dmwds[j]+2.0*mw*dcRefds[j])/(mw*mw*cRef*cRef*cRef) 
     				+ 2.0*tr*alpha*dalphads/(cp) - tr*alpha*alpha*dcpds[j]/(cp*cp));   
      double dcds	= dcRefds[j] + (t-tr)*d2cdsdt[j];
      double dv1ds	= -2.0*v0*dv0ds*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
     			  -v0*v0*(-1000.0*(c*dmwds[j]+2.0*mw*dcds)/(mw*mw*c*c*c) 
     				  + 2.0*t*alpha*dalphads/(cp) - t*alpha*alpha*dcpds[j]/(cp*cp));      
      double dv2ds	= d3vdsdp2[j];
      double ddenomds	= 2.0*dv1Refds*d3vdp3+2.0*v1Ref*d4vdsdp3[j]-6.0*d2vdp2*d3vdsdp2[j]; 
      double dads	= (d3vdsdp2[j]*d3vdp3+d2vdp2*d4vdsdp3[j]-dv1Refds*d4vdp4/2.0-v1Ref*d5vdsdp4[j]/2.0)/denom
     			- (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomds;
      double dbds	= (d3vdsdp2[j]*d4vdp4/4.0+d2vdp2*d5vdsdp4[j]/4.0-2.0/3.0*d3vdp3*d4vdsdp3[j])/denom
     			- (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomds; 		

      double d2alphadrds = d3vdrdsdt[i][j]/v - d2vdrdt[i]*dvds[j]/(v*v) - (d2vdsdt[j]*dvdr[i]+dvdt*d2vdrds[i][j])/(v*v) 
                         + 2.0*dvdt*dvdr[i]*dvds[j]/(v*v*v);
      double d2v0drds	 = (d2vdrds[i][j] + dvds[j]*dalphadr*(t-tr) + v*d2alphadrds*(t-tr))*exp(alpha*(t-tr)) 
                         + (dvdr[i] + v*dalphadr*(t-tr))*dalphads*(t-tr)*exp(alpha*(t-tr));
      double d2v1Refdrds = -2.0*(dvds[j]*dvdr[i]+v*d2vdrds[i][j])*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
                         - 2.0*v*dvdr[i]*(-1000.0*(cRef*dmwds[j]+2.0*mw*dcRefds[j])/(mw*mw*cRef*cRef*cRef) 
        			+ 2.0*tr*alpha*dalphads/(cp) - tr*alpha*alpha*dcpds[j]/(cp*cp))
    	  		 - 2.0*v*dvds[j]*(-1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
        			+ 2.0*tr*alpha*dalphadr/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp))
			 - v*v*(-1000.0*(dcRefds[j]*dmwdr[i]+cRef*d2mwdrds[i][j]+2.0*dmwds[j]*dcRefdr[i]+2.0*mw*d2cRefdrds[i][j])
			                /(mw*mw*cRef*cRef*cRef)
			        +1000.0*(2.0*dmwds[j]*cRef+3.0*mw*dcRefds[j])*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])
				        /(mw*mw*mw*cRef*cRef*cRef*cRef)
        			+ 2.0*tr*(dalphads*dalphadr+alpha*d2alphadrds)/(cp) 
				- 2.0*tr*alpha*dalphadr*dcpds[j]/(cp*cp) 
				- tr*(2.0*alpha*dalphads*dcpdr[i]+alpha*alpha*d2cpdrds[i][j])/(cp*cp)
				+ 2.0*tr*alpha*alpha*dcpdr[i]*dcpds[j]/(cp*cp*cp)
				);   
      double d2cdrds	= d2cRefdrds[i][j] + (t-tr)*d3cdrdsdt[i][j];
      double d2v1drds	= -2.0*(dv0ds*dv0dr+v0*d2v0drds)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                        - 2.0*v0*dv0dr*(-(dmwds[j]*c+2.0*mw*dcds)*1000.0/(mw*mw*c*c*c) + 2.0*t*alpha*dalphads/(cp) 
			                - t*alpha*alpha*dcpds[j]/(cp*cp))
    	  		- 2.0*v0*dv0ds*(-1000.0*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*c*c*c) 
        			        + 2.0*t*alpha*dalphadr/(cp) 
				        - t*alpha*alpha*dcpdr[i]/(cp*cp)
				        )
			- v0*v0*(-1000.0*(dcds*dmwdr[i]+c*d2mwdrds[i][j]+2.0*dmwds[j]*dcdr+2.0*mw*d2cdrds)/(mw*mw*c*c*c)
			         +1000.0*(2.0*dmwds[j]*c+3.0*mw*dcds)*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*mw*c*c*c*c)
        			  + 2.0*t*(dalphads*dalphadr+alpha*d2alphadrds)/(cp) 
				  - 2.0*t*alpha*dalphadr*dcpds[j]/(cp*cp)
				  - t*(2.0*alpha*dalphads*dcpdr[i]+alpha*alpha*d2cpdrds[i][j])/(cp*cp) 
				  + 2.0*t*alpha*alpha*dcpdr[i]*dcpds[j]/(cp*cp*cp)
				  
				  );  
      double d2v2drds	= d4vdrdsdp2[i][j];
      double d2denomdrds= 2.0*d2v1Refdrds*d3vdp3 + 2.0*dv1Refdr*d4vdsdp3[j]
                        + 2.0*dv1Refds*d4vdrdp3[i] + 2.0*v1Ref*d5vdrdsdp3[i][j]
			- 6.0*d3vdsdp2[j]*d3vdrdp2[i] - 6.0*d2vdp2*d4vdrdsdp2[i][j]; 
      double d2adrds	= (  d4vdrdsdp2[i][j]*d3vdp3 + d3vdrdp2[i]*d4vdsdp3[j] 
                           + d3vdsdp2[j]*d4vdrdp3[i] + d2vdp2*d5vdrdsdp3[i][j]
                           - d2v1Refdrds*d4vdp4/2.0 - dv1Refdr*d5vdsdp4[j]/2.0 
			   - dv1Refds*d5vdrdp4[i]/2.0 - v1Ref*d6vdrdsdp4[i][j]/2.0
			  )/denom
                        - (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdr*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)*ddenomds/(denom*denom)
    	  		- (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*d2denomdrds/(denom*denom)
			- (d3vdsdp2[j]*d3vdp3 + d2vdp2*d4vdsdp3[j] - dv1Refds*d4vdp4/2.0 - v1Ref*d5vdsdp4[j]/2.0)*ddenomdr/(denom*denom)
    	  		+ 2.0*(d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*ddenomdr*ddenomds/(denom*denom*denom);
			
			
      double d2bdrds	= (d4vdrdsdp2[i][j]*d4vdp4/4.0 + d3vdrdp2[i]*d5vdsdp4[j]/4.0
                           + d3vdsdp2[j]*d5vdrdp4[i]/4.0 + d2vdp2*d6vdrdsdp4[i][j]/4.0
			   - 2.0/3.0*d4vdsdp3[j]*d4vdrdp3[i] - 2.0/3.0*d3vdp3*d5vdrdsdp3[i][j]
                           )/denom
                        - (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])*ddenomds/(denom*denom)
  		        - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*d2denomdrds/(denom*denom)
			- (d3vdsdp2[j]*d4vdp4/4.0+d2vdp2*d5vdsdp4[j]/4.0-d4vdsdp3[j]*d3vdp3/3.0-d3vdp3*d4vdsdp3[j]/3.0)*ddenomdr/(denom*denom)
			+ 2.0*(d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*ddenomdr*ddenomds/(denom*denom*denom);

      double d2gIntdrds = 0.0;

      if ((a == 0.0) && (b == 0.0)) {
     	d2gIntdrds = d2v0drds*(p-pr) + d2v1drds*(p-pr)*(p-pr)/2.0 + d2v2drds*(p-pr)*(p-pr)*(p-pr)/6.0;
 
      } else if ((a != 0.0) && (b == 0.0)) {
     	d2gIntdrds = (d2v0drds - d2v2drds/(2.0*a*a) + dv2dr*dads/(a*a*a) + (dv2ds*dadr + v2*d2adrds)/(a*a*a) - 3.0*v2*dadr*dads/(a*a*a*a) 
		     )*(p-pr)
	           + (d2v1drds + d2v2drds/(2.0*a) - dv2dr*dads/(2.0*a*a) - (dv2ds*dadr + v2*d2adrds)/(2.0*a*a) + v2*dadr*dads/(a*a*a)
		     )*(p-pr)*(p-pr)/2.0; 
     	d2gIntdrds += (d2v2drds*log(1.0+a*(p-pr)) + dv2dr*dads*(p-pr)/(1.0+a*(p-pr))
	               + (dv2ds*dadr + v2*d2adrds)*(p-pr)/(1.0+a*(p-pr)) 
		       - v2*dadr*dads*(p-pr)*(p-pr)/((1.0+a*(p-pr))*(1.0+a*(p-pr)))
	              )/(2.0*a*a*a)
		    - 3.0*(dv2dr*log(1.0+a*(p-pr)) + v2*dadr*(p-pr)/(1.0+a*(p-pr)))*dads/(2.0*a*a*a*a) 
	            - 3.0*(d2adrds*v2*log(1.0+a*(p-pr)) + dadr*dv2ds*log(1.0+a*(p-pr)) + dadr*v2*dads*(p-pr)/(1.0+a*(p-pr)))/(2.0*a*a*a*a)
		    + 12.0*dadr*v2*log(1.0+a*(p-pr))*dads/(2.0*a*a*a*a*a);
 
      } else if ((a == 0.0) && (b != 0.0)) {
     	printf("*-->Exception in d2IntegralV_GKdrds (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
     	d2gIntdrds = 0.0;

      } else if (sum > 0.0) {	
     	d2gIntdrds = d2gdr2GMAP(p/10000.0, pr/10000.0, 
	                        v0,             v1*10000.0,       v2*10000.0*10000.0,       a*10000.0,       b*10000.0*10000.0, 
	                        dv0dr,       dv1dr*10000.0,    dv2dr*10000.0*10000.0,    dadr*10000.0,    dbdr*10000.0*10000.0,
                                dv0ds,       dv1ds*10000.0,    dv2ds*10000.0*10000.0,    dads*10000.0,    dbds*10000.0*10000.0, 
			        d2v0drds, d2v1drds*10000.0, d2v2drds*10000.0*10000.0, d2adrds*10000.0, d2bdrds*10000.0*10000.0)*10000.0;
     	 
      } else if (sum == 0.0) {
     	printf("*-->Exception in d2IntegralV_GKdrds (liquid.c). a*a-4*b is equal to zero.\n"); liqERRstate = ERR_SUM_ZERO;
     	d2gIntdrds = 0.0;
 
      } else if(sum < 0.0) {
     	d2gIntdrds = d2gdr2LMAP(p/10000.0, pr/10000.0, 
	                        v0,             v1*10000.0,       v2*10000.0*10000.0,       a*10000.0,       b*10000.0*10000.0, 
	                        dv0dr,       dv1dr*10000.0,    dv2dr*10000.0*10000.0,    dadr*10000.0,    dbdr*10000.0*10000.0,
                                dv0ds,       dv1ds*10000.0,    dv2ds*10000.0*10000.0,    dads*10000.0,    dbds*10000.0*10000.0, 
			        d2v0drds, d2v1drds*10000.0, d2v2drds*10000.0*10000.0, d2adrds*10000.0, d2bdrds*10000.0*10000.0)*10000.0;
 
      }
     	    
      drds[i][j] = d2gIntdrds;
    } /* end loop on j [NS] */
  } /* end loop on i [NR] */
}

static void d2IntegralV_GKdrdt(double r[NR], double s[NT], double t, double p, double *drdt) {
  const double pr	 = 1.0;
  const double tr	 = 1673.15;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double dvdr[NR], d2vdrdt[NR], dcRefdr[NR], d2cdrdt[NR], dmwdr[NR], dcpdr[NR], d3vdrdp2[NR], d4vdrdp3[NR], d5vdrdp4[NR], dmOxTotdr[NR], denom;
  int i, j;
  
  for (i=0; i<NR; i++) drdt[i] = 0.0;
  if (fabs(p-pr) < 10.0*DBL_EPSILON) return;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return;
  
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }

  for (i=0; i<NR; i++) { 
    dvdr[i]    = 0.0; d2vdrdt[i]  = 0.0; dcRefdr[i]  = 0.0; d2cdrdt[i]  = 0.0; dmwdr[i] = 0.0; 
    dcpdr[i]   = 0.0; d3vdrdp2[i] = 0.0; d4vdrdp3[i] = 0.0; d5vdrdp4[i] = 0.0; 
    for (j=0, dmOxTotdr[i]=0.0; j<nc; j++) dmOxTotdr[i] += (liquid[i+1].liqToOx)[j] - (liquid[0].liqToOx)[j];
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
    
    for (j=0; j<NR; j++) {
      dvdr[j]	   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_v;
      d2vdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dvdt;
      dmwdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].mw;
      dcpdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cp;  
      dcRefdr[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c/mOxTot 
        	    - mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot);
      dcRefdr[j]   += (iOxAl2O3 != -1) ? ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
        	    - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
      d2cdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt/mOxTot 
        	    - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot);
      d3vdrdp2[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d4vdrdp3[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d5vdrdp4[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    }
    if (iCmpAl2O3 != -1) dcRefdr[iCmpAl2O3] += ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);
  }
  if (v == 0.0) return;

  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
  a	  = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
  b	  = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
  sum	  = a*a - 4.0*b;

  for (i=0; i<NR; i++) {
    double dalphadr = d2vdrdt[i]/v - dvdt*dvdr[i]/(v*v);
    double dv0dr    = (dvdr[i] + v*dalphadr*(t-tr))*exp(alpha*(t-tr));      
    double dv1Refdr = -2.0*v*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
  		      -v*v*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
        		    + 2.0*tr*alpha*dalphadr/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp));   
    double dcdr     = dcRefdr[i] + (t-tr)*d2cdrdt[i];
    double dv1dr    = -2.0*v0*dv0dr*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  		      -v0*v0*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*c*c*c) 
        		      + 2.0*t*alpha*dalphadr/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp));	  
    double dv2dr    = d3vdrdp2[i];
    double ddenomdr = 2.0*dv1Refdr*d3vdp3+2.0*v1Ref*d4vdrdp3[i]-6.0*d2vdp2*d3vdrdp2[i]; 
    double dadr     = (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdr*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)/denom
  		    - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdr;
    double dbdr     = (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/denom
  		    - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdr;
    double dv0dt    = v*alpha*exp(alpha*(t-tr));
    double dv1dt    = - 2.0*v0*v0*alpha*(1000.0/(mw*c*c) + t*alpha*alpha/(cp)) - v0*v0*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp));

    double d2v0drdt = v*dalphadr*exp(alpha*(t-tr)) + (dvdr[i] + v*dalphadr*(t-tr))*alpha*exp(alpha*(t-tr));
    double d2v1drdt = -2.0*(dv0dt*dv0dr + v0*d2v0drdt)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  		    - 2.0*v0*dv0dr*(- 2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
  		    - 2.0*v0*dv0dt*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*c*c*c) 
        			    + 2.0*t*alpha*dalphadr/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp))
        	    - v0*v0*(- 1000.0*(dcdt*dmwdr[i]+2.0*mw*d2cdrdt[i])/(mw*mw*c*c*c) + 3000.0*(c*dmwdr[i]+2.0*mw*dcdr)*dcdt/(mw*mw*c*c*c*c)
        		     + 2.0*alpha*dalphadr/(cp) - alpha*alpha*dcpdr[i]/(cp*cp));
    double d2gIntdrdt = 0.0;

    if ((a == 0.0) && (b == 0.0)) {
      d2gIntdrdt       = d2v0drdt*(p-pr) + d2v1drdt*(p-pr)*(p-pr)/2.0;
 
    } else if ((a != 0.0) && (b == 0.0)) {
      printf("*-->Exception in d2IntegralV_GKdrdt (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
      d2gIntdrdt       = 0.0;
 
    } else if ((a == 0.0) && (b != 0.0)) {
      printf("*-->Exception in d2IntegralV_GKdrdt (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
      d2gIntdrdt       = 0.0;

    } else if (sum > 0.0) {   
      d2gIntdrdt       = d2gdrdtGMAP(p/10000.0, pr/10000.0, 
                                     v0,             v1*10000.0,    v2*10000.0*10000.0,    a*10000.0,    b*10000.0*10000.0, 
				     dv0dr,       dv1dr*10000.0, dv2dr*10000.0*10000.0, dadr*10000.0, dbdr*10000.0*10000.0, 
				     dv0dt,       dv1dt*10000.0, 
				     d2v0drdt, d2v1drdt*10000.0)*10000.0;
       
    } else if (sum == 0.0) {
      printf("*-->Exception in d2IntegralV_GKdrdt (liquid.c). a*a-4*b is equal to zero.\n"); liqERRstate = ERR_SUM_ZERO;
      d2gIntdrdt       = 0.0;
 
    } else if(sum < 0.0) {
      d2gIntdrdt       = d2gdrdtLMAP(p/10000.0, pr/10000.0, 
                                     v0,             v1*10000.0,    v2*10000.0*10000.0,    a*10000.0,    b*10000.0*10000.0, 
				     dv0dr,       dv1dr*10000.0, dv2dr*10000.0*10000.0, dadr*10000.0, dbdr*10000.0*10000.0, 
				     dv0dt,       dv1dt*10000.0, 
				     d2v0drdt, d2v1drdt*10000.0)*10000.0;
 
    }
    
    drdt[i] += d2gIntdrdt;
  }
}


static void d2IntegralV_GKdrdp(double r[NR], double s[NT], double t, double p, double *drdp) {
  const double pr	 = 1.0;
  const double tr	 = 1673.15;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double dvdr[NR], d2vdrdt[NR], dcRefdr[NR], d2cdrdt[NR], dmwdr[NR], dcpdr[NR], d3vdrdp2[NR], d4vdrdp3[NR], d5vdrdp4[NR], dmOxTotdr[NR], denom;
  int i, j;
  
  for (i=0; i<NR; i++) drdp[i] = 0.0;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return;
  
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }

  for (i=0; i<NR; i++) { 
    dvdr[i]    = 0.0; d2vdrdt[i]  = 0.0; dcRefdr[i]  = 0.0; d2cdrdt[i]  = 0.0; dmwdr[i] = 0.0; 
    dcpdr[i]   = 0.0; d3vdrdp2[i] = 0.0; d4vdrdp3[i] = 0.0; d5vdrdp4[i] = 0.0; 
    for (j=0, dmOxTotdr[i]=0.0; j<nc; j++) dmOxTotdr[i] += (liquid[i+1].liqToOx)[j] - (liquid[0].liqToOx)[j];
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
    
    for (j=0; j<NR; j++) {
      dvdr[j]	   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_v;
      d2vdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dvdt;
      dmwdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].mw;
      dcpdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cp;  
      dcRefdr[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c/mOxTot 
        	    - mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot);
      dcRefdr[j]   += (iOxAl2O3 != -1) ? ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
        	    - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
      d2cdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt/mOxTot 
        	    - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot);
      d3vdrdp2[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d4vdrdp3[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d5vdrdp4[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    }
    if (iCmpAl2O3 != -1) dcRefdr[iCmpAl2O3] += ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);
  }
  if (v == 0.0) return;

  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
  a	  = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
  b	  = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
  sum	  = a*a - 4.0*b;

  for (i=0; i<NR; i++) {
    double dalphadr   = d2vdrdt[i]/v - dvdt*dvdr[i]/(v*v);
    double dv0dr      = (dvdr[i] + v*dalphadr*(t-tr))*exp(alpha*(t-tr));      
    double dv1Refdr   = -2.0*v*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
  			-v*v*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
        		      + 2.0*tr*alpha*dalphadr/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp));   
    double dcdr       = dcRefdr[i] + (t-tr)*d2cdrdt[i];
    double dv1dr      = -2.0*v0*dv0dr*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  			-v0*v0*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*c*c*c) 
        			+ 2.0*t*alpha*dalphadr/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp));      
    double dv2dr      = d3vdrdp2[i];
    double ddenomdr   = 2.0*dv1Refdr*d3vdp3+2.0*v1Ref*d4vdrdp3[i]-6.0*d2vdp2*d3vdrdp2[i]; 
    double dadr       = (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdr*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)/denom
  		      - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdr;
    double dbdr       = (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/denom
  		      - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdr;		      
    double d2gdrdp;

    if ((a == 0.0) && (b == 0.0)) {
      d2gdrdp  = dv1dr + dv2dr*(p-pr);
 
    } else if ((a != 0.0) && (b == 0.0)) {
      printf("*-->Exception in d2IntegralV_GKdrdp (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
      d2gdrdp  = 0.0;
 
    } else if ((a == 0.0) && (b != 0.0)) {
      printf("*-->Exception in d2IntegralV_GKdrdp (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
      d2gdrdp  = 0.0;

    } else {  
      d2gdrdp  = d2gdrdpMAP(p, pr, v0, v1, v2, a, b, dv0dr, dv1dr, dv2dr, dadr, dbdr);
 
    }
    
    drdp[i] += d2gdrdp;
  }
}
 
static void d2IntegralV_GKds2(double r[NR], double s[NT], double t, double p, double d2s[NS][NS]) {
  const double pr = 1.0;
  const double tr = 1673.15;
  const double y  = 0.3;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double dvds[NS], d2vdsdt[NS], dcRefds[NS], d2cdsdt[NS], dmwds[NS], dcpds[NS], d3vdsdp2[NS], d4vdsdp3[NS], d5vdsdp4[NS], denom;
  double d2vds2[NS][NS], d3vds2dt[NS][NS], d2cRefds2[NS][NS], d3cds2dt[NS][NS], d2mwds2[NS][NS], d2cpds2[NS][NS], d4vds2dp2[NS][NS], 
         d5vds2dp3[NS][NS], d6vds2dp4[NS][NS];
  int i, j, k;
  
  for (i=0; i<NS; i++) for (j=0; j<NS; j++) d2s[i][j] = 0.0;
  if (fabs(p-pr) < 10.0*DBL_EPSILON) return;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return;
  
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }

  for (i=0; i<NS; i++) { 
    dvds[i]    = 0.0; d2vdsdt[i]  = 0.0; dcRefds[i]  = 0.0; d2cdsdt[i]  = 0.0; dmwds[i] = 0.0; 
    dcpds[i]   = 0.0; d3vdsdp2[i] = 0.0; d4vdsdp3[i] = 0.0; d5vdsdp4[i] = 0.0;
    for (j=0; j<NS; j++) {
      d2vds2[i][j]  = 0.0; d3vds2dt[i][j]  = 0.0; d2cRefds2[i][j] = 0.0; d3cds2dt[i][j]  = 0.0; d2mwds2[i][j] = 0.0;
      d2cpds2[i][j] = 0.0; d4vds2dp2[i][j] = 0.0; d5vds2dp3[i][j] = 0.0; d6vds2dp4[i][j] = 0.0;
    }
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    double dmOxds[NS], dmOxTotds[NS], d2mOxds2[NS][NS], d2mOxTotds2[NS][NS];
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
    
    for (j=0; j<NS; j++) { dmOxds[j] = 0.0; dmOxTotds[j] = 0.0; }
    for (j=0; j<NS; j++) for (k=0; k<NS; k++) { d2mOxds2[j][k] = 0.0; d2mOxTotds2[j][k] = 0.0; }
    if (iCmpFe2SiO4_6 != -1) {
    
      for (j=0; j<NS; j++) {
        if      (iOxFe2O3  == i) dmOxds[j] += -2.0*y*s[iCmpFe2SiO4_6]*dnSpeciesds[j];		 
        else if (iOxFeO	   == i) dmOxds[j] += -2.0*(1.0-2.0*y)*s[iCmpFe2SiO4_6]*dnSpeciesds[j]; 	 
        else if (iOxFeO1_3 == i) dmOxds[j] += 2.0*s[iCmpFe2SiO4_6]*dnSpeciesds[j];
	dmOxTotds[j] += 2.0*y*s[iCmpFe2SiO4_6]*dnSpeciesds[j]; 
	for (k=0; k<NS; k++) {
          if	  (iOxFe2O3  == i) d2mOxds2[j][k] += -2.0*y*s[iCmpFe2SiO4_6]*d2nSpeciesds2[j][k]; 	   
          else if (iOxFeO    == i) d2mOxds2[j][k] += -2.0*(1.0-2.0*y)*s[iCmpFe2SiO4_6]*d2nSpeciesds2[j][k];	   
          else if (iOxFeO1_3 == i) d2mOxds2[j][k] += 2.0*s[iCmpFe2SiO4_6]*d2nSpeciesds2[j][k];
	  d2mOxTotds2[j][k] += 2.0*y*s[iCmpFe2SiO4_6]*d2nSpeciesds2[j][k]; 
	}
      }
      
      if      (iOxFe2O3  == i) dmOxds[iCmpFe2SiO4_6] += -2.0*y*nSpecies;	   
      else if (iOxFeO	 == i) dmOxds[iCmpFe2SiO4_6] += -2.0*(1.0-2.0*y)*nSpecies; 
      else if (iOxFeO1_3 == i) dmOxds[iCmpFe2SiO4_6] += 2.0*nSpecies;
      dmOxTotds[iCmpFe2SiO4_6] += 2.0*y*nSpecies;
      for (j=0; j<NS; j++) {
        if (j != iCmpFe2SiO4_6) {
          if	  (iOxFe2O3  == i) { d2mOxds2[iCmpFe2SiO4_6][j] += -2.0*y*dnSpeciesds[j];	    d2mOxds2[j][iCmpFe2SiO4_6] += -2.0*y*dnSpeciesds[j];	   }
          else if (iOxFeO    == i) { d2mOxds2[iCmpFe2SiO4_6][j] += -2.0*(1.0-2.0*y)*dnSpeciesds[j]; d2mOxds2[j][iCmpFe2SiO4_6] += -2.0*(1.0-2.0*y)*dnSpeciesds[j]; }
          else if (iOxFeO1_3 == i) { d2mOxds2[iCmpFe2SiO4_6][j] += 2.0*dnSpeciesds[j];		    d2mOxds2[j][iCmpFe2SiO4_6] += 2.0*dnSpeciesds[j];              }
          d2mOxTotds2[iCmpFe2SiO4_6][j] += 2.0*y*dnSpeciesds[j];
          d2mOxTotds2[j][iCmpFe2SiO4_6] += 2.0*y*dnSpeciesds[j];
	}
      }
      if      (iOxFe2O3  == i) d2mOxds2[iCmpFe2SiO4_6][iCmpFe2SiO4_6] += -4.0*y*dnSpeciesds[iCmpFe2SiO4_6];	     
      else if (iOxFeO	 == i) d2mOxds2[iCmpFe2SiO4_6][iCmpFe2SiO4_6] += -4.0*(1.0-2.0*y)*dnSpeciesds[iCmpFe2SiO4_6];
      else if (iOxFeO1_3 == i) d2mOxds2[iCmpFe2SiO4_6][iCmpFe2SiO4_6] += 4.0*dnSpeciesds[iCmpFe2SiO4_6];	     
      d2mOxTotds2[iCmpFe2SiO4_6][iCmpFe2SiO4_6] += 4.0*y*dnSpeciesds[iCmpFe2SiO4_6];
      
    }
    if (iCmpFe2AlO4_1 != -1) {
    
      for (j=0; j<NS; j++) {
        if      (iOxFe2O3  == i) dmOxds[j] += -2.0*y*s[iCmpFe2AlO4_1]*dnSpeciesds[j];		 
        else if (iOxFeO	   == i) dmOxds[j] += -2.0*(1.0-2.0*y)*s[iCmpFe2AlO4_1]*dnSpeciesds[j]; 	 
        else if (iOxFeO1_3 == i) dmOxds[j] += 2.0*s[iCmpFe2AlO4_1]*dnSpeciesds[j];
	dmOxTotds[j] += 2.0*y*s[iCmpFe2AlO4_1]*dnSpeciesds[j]; 
	for (k=0; k<NS; k++) {
          if	  (iOxFe2O3  == i) d2mOxds2[j][k] += -2.0*y*s[iCmpFe2AlO4_1]*d2nSpeciesds2[j][k]; 	   
          else if (iOxFeO    == i) d2mOxds2[j][k] += -2.0*(1.0-2.0*y)*s[iCmpFe2AlO4_1]*d2nSpeciesds2[j][k];	   
          else if (iOxFeO1_3 == i) d2mOxds2[j][k] += 2.0*s[iCmpFe2AlO4_1]*d2nSpeciesds2[j][k];
	  d2mOxTotds2[j][k] += 2.0*y*s[iCmpFe2AlO4_1]*d2nSpeciesds2[j][k]; 
	}
      }
      
      if      (iOxFe2O3  == i) dmOxds[iCmpFe2AlO4_1] += -2.0*y*nSpecies;	   
      else if (iOxFeO	 == i) dmOxds[iCmpFe2AlO4_1] += -2.0*(1.0-2.0*y)*nSpecies; 
      else if (iOxFeO1_3 == i) dmOxds[iCmpFe2AlO4_1] += 2.0*nSpecies;
      dmOxTotds[iCmpFe2AlO4_1] += 2.0*y*nSpecies;
      for (j=0; j<NS; j++) {
        if (j != iCmpFe2AlO4_1) {
          if	  (iOxFe2O3  == i) { d2mOxds2[iCmpFe2AlO4_1][j] += -2.0*y*dnSpeciesds[j];	    d2mOxds2[j][iCmpFe2AlO4_1] += -2.0*y*dnSpeciesds[j];	   }
          else if (iOxFeO    == i) { d2mOxds2[iCmpFe2AlO4_1][j] += -2.0*(1.0-2.0*y)*dnSpeciesds[j]; d2mOxds2[j][iCmpFe2AlO4_1] += -2.0*(1.0-2.0*y)*dnSpeciesds[j]; }
          else if (iOxFeO1_3 == i) { d2mOxds2[iCmpFe2AlO4_1][j] += 2.0*dnSpeciesds[j];		    d2mOxds2[j][iCmpFe2AlO4_1] += 2.0*dnSpeciesds[j];              }
          d2mOxTotds2[iCmpFe2AlO4_1][j] += 2.0*y*dnSpeciesds[j];
          d2mOxTotds2[j][iCmpFe2AlO4_1] += 2.0*y*dnSpeciesds[j];
	}
      }
      if      (iOxFe2O3  == i) d2mOxds2[iCmpFe2AlO4_1][iCmpFe2AlO4_1] += -4.0*y*dnSpeciesds[iCmpFe2AlO4_1];	     
      else if (iOxFeO	 == i) d2mOxds2[iCmpFe2AlO4_1][iCmpFe2AlO4_1] += -4.0*(1.0-2.0*y)*dnSpeciesds[iCmpFe2AlO4_1];
      else if (iOxFeO1_3 == i) d2mOxds2[iCmpFe2AlO4_1][iCmpFe2AlO4_1] += 4.0*dnSpeciesds[iCmpFe2AlO4_1];	     
      d2mOxTotds2[iCmpFe2AlO4_1][iCmpFe2AlO4_1] += 4.0*y*dnSpeciesds[iCmpFe2AlO4_1];
      
    }
    for (j=0; j<NS; j++) {
      dvds[j]	   += dmOxds[j]*bulkSystem[i].gk_v;
      d2vdsdt[j]   += dmOxds[j]*bulkSystem[i].gk_dvdt;
      dmwds[j]     += dmOxds[j]*bulkSystem[i].mw;
      dcpds[j]     += dmOxds[j]*bulkSystem[i].gk_cp;  
      dcRefds[j]   += dmOxds[j]*bulkSystem[i].gk_c/mOxTot - mOx[i]*bulkSystem[i].gk_c*dmOxTotds[j]/(mOxTot*mOxTot);
      dcRefds[j]   += (iOxAl2O3 != -1) ? dmOxds[j]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
        	    - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotds[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
      d2cdsdt[j]   += dmOxds[j]*bulkSystem[i].gk_dcdt/mOxTot - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotds[j]/(mOxTot*mOxTot);
      d3vdsdp2[j]  += dmOxds[j]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d4vdsdp3[j]  += dmOxds[j]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d5vdsdp4[j]  += dmOxds[j]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      
      for (k=0; k<NS; k++) {
        d2vds2[j][k]     += d2mOxds2[j][k]*bulkSystem[i].gk_v;
        d3vds2dt[j][k]   += d2mOxds2[j][k]*bulkSystem[i].gk_dvdt;
        d2mwds2[j][k]    += d2mOxds2[j][k]*bulkSystem[i].mw;
        d2cpds2[j][k]    += d2mOxds2[j][k]*bulkSystem[i].gk_cp;  
        d2cRefds2[j][k]  += d2mOxds2[j][k]*bulkSystem[i].gk_c/mOxTot 
	                  - dmOxds[j]*bulkSystem[i].gk_c*dmOxTotds[k]/(mOxTot*mOxTot)
	                  - dmOxds[k]*bulkSystem[i].gk_c*dmOxTotds[j]/(mOxTot*mOxTot) 
			  - mOx[i]*bulkSystem[i].gk_c*d2mOxTotds2[j][k]/(mOxTot*mOxTot) 
			  + 2.0*mOx[i]*bulkSystem[i].gk_c*dmOxTotds[j]*dmOxTotds[k]/(mOxTot*mOxTot*mOxTot);
        d2cRefds2[j][k]  += (iOxAl2O3 != -1) ? 
	                    d2mOxds2[j][k]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) 
			  - 2.0*dmOxds[j]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotds[k]/(mOxTot*mOxTot*mOxTot)
        	          - 2.0*dmOxds[k]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotds[j]/(mOxTot*mOxTot*mOxTot)
			  - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*d2mOxTotds2[j][k]/(mOxTot*mOxTot*mOxTot)
			  + 6.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotds[j]*dmOxTotds[k]/(mOxTot*mOxTot*mOxTot*mOxTot) 
			  : 0.0;
        d3cds2dt[j][k]   += d2mOxds2[j][k]*bulkSystem[i].gk_dcdt/mOxTot 
	                  - dmOxds[j]*bulkSystem[i].gk_dcdt*dmOxTotds[k]/(mOxTot*mOxTot) 
	                  - dmOxds[k]*bulkSystem[i].gk_dcdt*dmOxTotds[j]/(mOxTot*mOxTot)
			  - mOx[i]*bulkSystem[i].gk_dcdt*d2mOxTotds2[j][k]/(mOxTot*mOxTot)
			  + 2.0*mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotds[j]*dmOxTotds[k]/(mOxTot*mOxTot*mOxTot);
        d4vds2dp2[j][k]  += d2mOxds2[j][k]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
        d5vds2dp3[j][k]  += d2mOxds2[j][k]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
        d6vds2dp4[j][k]  += d2mOxds2[j][k]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      }
      
    }
  }
  if (v == 0.0) return;

  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
  a	  = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
  b	  = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
  sum	  = a*a - 4.0*b;

  for (i=0; i<NS; i++) {
    double dalphadsi  = d2vdsdt[i]/v - dvdt*dvds[i]/(v*v);
    double dv0dsi     = (dvds[i] + v*dalphadsi*(t-tr))*exp(alpha*(t-tr));      
    double dv1Refdsi  = -2.0*v*dvds[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
  		       -v*v*(-1000.0*(cRef*dmwds[i]+2.0*mw*dcRefds[i])/(mw*mw*cRef*cRef*cRef) 
        	             + 2.0*tr*alpha*dalphadsi/(cp) - tr*alpha*alpha*dcpds[i]/(cp*cp));   
    double dcdsi      = dcRefds[i] + (t-tr)*d2cdsdt[i];
    double dv1dsi     = -2.0*v0*dv0dsi*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  		       -v0*v0*(-1000.0*(c*dmwds[i]+2.0*mw*dcdsi)/(mw*mw*c*c*c) 
        	               + 2.0*t*alpha*dalphadsi/(cp) - t*alpha*alpha*dcpds[i]/(cp*cp));      
    double ddenomdsi  = 2.0*dv1Refdsi*d3vdp3+2.0*v1Ref*d4vdsdp3[i]-6.0*d2vdp2*d3vdsdp2[i]; 
    double dadsi      = (d3vdsdp2[i]*d3vdp3+d2vdp2*d4vdsdp3[i]-dv1Refdsi*d4vdp4/2.0-v1Ref*d5vdsdp4[i]/2.0)/denom
  		      - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdsi;
    double dbdsi      = (d3vdsdp2[i]*d4vdp4/4.0+d2vdp2*d5vdsdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdsdp3[i])/denom
  		      - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdsi;	
		      	     
    for (j=i; j<NS; j++) {
      double dalphadsj   = d2vdsdt[j]/v - dvdt*dvds[j]/(v*v);
      double dv0dsj	 = (dvds[j] + v*dalphadsj*(t-tr))*exp(alpha*(t-tr));	  
      double dv1Refdsj   = -2.0*v*dvds[j]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
  			   -v*v*(- 1000.0*(cRef*dmwds[j]+2.0*mw*dcRefds[j])/(mw*mw*cRef*cRef*cRef) 
  				 + 2.0*tr*alpha*dalphadsj/(cp) - tr*alpha*alpha*dcpds[j]/(cp*cp));   
      double dcdsj	 = dcRefds[j] + (t-tr)*d2cdsdt[j];
      double dv1dsj	 = -2.0*v0*dv0dsj*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  			   -v0*v0*(- 1000.0*(c*dmwds[j]+2.0*mw*dcdsj)/(mw*mw*c*c*c) 
  				   + 2.0*t*alpha*dalphadsj/(cp) - t*alpha*alpha*dcpds[j]/(cp*cp));	
      double ddenomdsj   = 2.0*dv1Refdsj*d3vdp3+2.0*v1Ref*d4vdsdp3[j]-6.0*d2vdp2*d3vdsdp2[j]; 
      double dadsj	 = (d3vdsdp2[j]*d3vdp3+d2vdp2*d4vdsdp3[j]-dv1Refdsj*d4vdp4/2.0-v1Ref*d5vdsdp4[j]/2.0)/denom
  			 - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdsj;
      double dbdsj	 = (d3vdsdp2[j]*d4vdp4/4.0+d2vdp2*d5vdsdp4[j]/4.0-2.0/3.0*d3vdp3*d4vdsdp3[j])/denom
  		         - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdsj; 		      

      double d2alphads2   = d3vds2dt[i][j]/v - d2vdsdt[i]*dvds[j]/(v*v) - d2vdsdt[j]*dvds[i]/(v*v) - dvdt*d2vds2[i][j]/(v*v) + 2.0*dvdt*dvds[i]*dvds[j]/(v*v*v);
      double d2v0ds2	  = d2vds2[i][j]*exp(alpha*(t-tr))
                          + dvds[i]*dalphadsj*(t-tr)*exp(alpha*(t-tr))
        		  + dvds[j]*dalphadsi*(t-tr)*exp(alpha*(t-tr))
        		  + v*d2alphads2*(t-tr)*exp(alpha*(t-tr))
        		  + v*dalphadsi*pow(t-tr,2.0)*dalphadsj*exp(alpha*(t-tr));
      double d2v1Refds2   = -2.0*v*d2vds2[i][j]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
                          - 2.0*dvds[j]*dvds[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
        		  - 2.0*v*dvds[i]*(- 1000.0*(cRef*dmwds[j]+2.0*mw*dcRefds[j])/(mw*mw*cRef*cRef*cRef) 
        				   + 2.0*tr*alpha*dalphadsj/(cp) - tr*alpha*alpha*dcpds[j]/(cp*cp))
  			  - 2.0*v*dvds[j]*(- 1000.0*(cRef*dmwds[i]+2.0*mw*dcRefds[i])/(mw*mw*cRef*cRef*cRef) 
  					   + 2.0*tr*alpha*dalphadsi/(cp) - tr*alpha*alpha*dcpds[i]/(cp*cp))
        		   -v*v*(- 1000.0*(dcRefds[j]*dmwds[i]+cRef*d2mwds2[i][j]+2.0*dmwds[j]*dcRefds[i]+2.0*mw*d2cRefds2[i][j])/(mw*mw*cRef*cRef*cRef)			   
        			 + 1000.0*(cRef*dmwds[i]+2.0*mw*dcRefds[i])*(2.0*dmwds[j]*cRef+3.0*mw*dcRefds[j])/(mw*mw*mw*cRef*cRef*cRef*cRef) 
        			 + 2.0*tr*alpha*d2alphads2/(cp)
        			 + 2.0*tr*dalphadsj*dalphadsi/(cp) - 2.0*tr*alpha*dalphadsi*dcpds[j]/(cp*cp) 
        			 - 2.0*tr*alpha*dalphadsj*dcpds[i]/(cp*cp) + 2.0*tr*alpha*alpha*dcpds[i]*dcpds[j]/(cp*cp*cp)); 
      double d2cds2	 = d2cRefds2[i][j] + (t-tr)*d3cds2dt[i][j];
      double d2v1ds2	 = -2.0*dv0dsj*dv0dsi*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
        		  - 2.0*v0*d2v0ds2*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
        		  - 2.0*v0*dv0dsi*(- 1000.0*(c*dmwds[j]+2.0*mw*dcdsj)/(mw*mw*c*c*c) 
        				   + 2.0*t*alpha*dalphadsj/(cp) - t*alpha*alpha*dcpds[j]/(cp*cp))
  			  - 2.0*v0*dv0dsj*(- 1000.0*(c*dmwds[i]+2.0*mw*dcdsi)/(mw*mw*c*c*c) 
  					   + 2.0*t*alpha*dalphadsi/(cp) - t*alpha*alpha*dcpds[i]/(cp*cp))
        		   -v0*v0*(- 1000.0*(dcdsj*dmwds[i]+c*d2mwds2[i][j]+2.0*dmwds[j]*dcdsi+2.0*mw*d2cds2)/(mw*mw*c*c*c)
        			   + 1000.0*(c*dmwds[i]+2.0*mw*dcdsi)*(2.0*dmwds[j]*c+3.0*mw*dcdsj)/(mw*mw*mw*c*c*c*c) 
        			   + 2.0*t*alpha*d2alphads2/(cp)
        			   + 2.0*t*dalphadsj*dalphadsi/(cp) - 2.0*t*alpha*dalphadsi*dcpds[j]/(cp*cp) 
        			   - 2.0*t*alpha*dalphadsj*dcpds[i]/(cp*cp) + 2.0*t*alpha*alpha*dcpds[i]*dcpds[j]/(cp*cp*cp));   
      double d2denomds2   = 2.0*d2v1Refds2*d3vdp3+2.0*dv1Refdsi*d4vdsdp3[j]+2.0*dv1Refdsj*d4vdsdp3[i]+2.0*v1Ref*d5vds2dp3[i][j]-6.0*d3vdsdp2[j]*d3vdsdp2[i]-6.0*d2vdp2*d4vds2dp2[i][j]; 
      double d2ads2	 = (d4vds2dp2[i][j]*d3vdp3+d3vdsdp2[i]*d4vdsdp3[j]+d3vdsdp2[j]*d4vdsdp3[i]+d2vdp2*d5vds2dp3[i][j]
                         - d2v1Refds2*d4vdp4/2.0-dv1Refdsi*d5vdsdp4[j]/2.0-dv1Refdsj*d5vdsdp4[i]/2.0-v1Ref*d6vds2dp4[i][j]/2.0)/denom
        		 - (d3vdsdp2[i]*d3vdp3+d2vdp2*d4vdsdp3[i]-dv1Refdsi*d4vdp4/2.0-v1Ref*d5vdsdp4[i]/2.0)*ddenomdsj/(denom*denom)
  			 - (d3vdsdp2[j]*d3vdp3+d2vdp2*d4vdsdp3[j]-dv1Refdsj*d4vdp4/2.0-v1Ref*d5vdsdp4[j]/2.0)*ddenomdsi/(denom*denom)
  			 + 2.0*(d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*ddenomdsi*ddenomdsj/(denom*denom*denom)
  			 - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*d2denomds2/(denom*denom);
      double d2bds2	 = (d4vds2dp2[i][j]*d4vdp4/4.0+d3vdsdp2[i]*d5vdsdp4[j]/4.0+d3vdsdp2[j]*d5vdsdp4[i]/4.0+d2vdp2*d6vds2dp4[i][j]/4.0
                         - 2.0/3.0*d4vdsdp3[j]*d4vdsdp3[i]-2.0/3.0*d3vdp3*d5vds2dp3[i][j])/denom
  			 - (d3vdsdp2[i]*d4vdp4/4.0+d2vdp2*d5vdsdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdsdp3[i])*ddenomdsj/(denom*denom)
  			 - (d3vdsdp2[j]*d4vdp4/4.0+d2vdp2*d5vdsdp4[j]/4.0-2.0*d4vdsdp3[j]*d3vdp3/3.0)*ddenomdsi/(denom*denom)
        		 + 2.0*(d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*ddenomdsi*ddenomdsj/(denom*denom*denom)
        		 - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*d2denomds2/(denom*denom);			
      double d2gIntds2   = 0.0;

      if ((a == 0.0) && (b == 0.0)) {
  	d2gIntds2  = d2v0ds2*(p-pr) + d2v1ds2*(p-pr)*(p-pr)/2.0;
 
      } else if ((a != 0.0) && (b == 0.0)) {
  	printf("*-->Exception in d2IntegralV_GKds2 (liquid.c). a is not equal to zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
  	d2gIntds2  = 0.0;
 
      } else if ((a == 0.0) && (b != 0.0)) {
  	printf("*-->Exception in d2IntegralV_GKds2 (liquid.c). a is zero, b is not equal to zero.\n"); liqERRstate = ERR_A_ZERO;
  	d2gIntds2  = 0.0;

      } else if (sum > 0.0) {
  	d2gIntds2  = d2gdr2GMAP(p/10000.0, pr/10000.0, 
	                        v0,           v1*10000.0,          d2vdp2*10000.0*10000.0,      a*10000.0,      b*10000.0*10000.0, 
	                        dv0dsi,   dv1dsi*10000.0,     d3vdsdp2[i]*10000.0*10000.0,  dadsi*10000.0,  dbdsi*10000.0*10000.0, 
  				dv0dsj,   dv1dsj*10000.0,     d3vdsdp2[j]*10000.0*10000.0,  dadsj*10000.0,  dbdsj*10000.0*10000.0, 
        			d2v0ds2, d2v1ds2*10000.0, d4vds2dp2[i][j]*10000.0*10000.0, d2ads2*10000.0, d2bds2*10000.0*10000.0)*10000.0;
 
      } else if (sum == 0.0) {
  	printf("*-->Exception in d2IntegralV_GKds2 (liquid.c). a*a-4*b is equal to zero.\n"); liqERRstate = ERR_SUM_ZERO;
  	d2gIntds2  = 0.0;
 
      } else if(sum < 0.0) {
  	d2gIntds2  = d2gdr2LMAP(p/10000.0, pr/10000.0, 
	                        v0,           v1*10000.0,          d2vdp2*10000.0*10000.0,      a*10000.0,      b*10000.0*10000.0, 
	                        dv0dsi,   dv1dsi*10000.0,     d3vdsdp2[i]*10000.0*10000.0,  dadsi*10000.0,  dbdsi*10000.0*10000.0, 
  				dv0dsj,   dv1dsj*10000.0,     d3vdsdp2[j]*10000.0*10000.0,  dadsj*10000.0,  dbdsj*10000.0*10000.0, 
        			d2v0ds2, d2v1ds2*10000.0, d4vds2dp2[i][j]*10000.0*10000.0, d2ads2*10000.0, d2bds2*10000.0*10000.0)*10000.0;
 
      }

      d2s[i][j] += d2gIntds2;
      if (i != j) d2s[j][i] += d2gIntds2;

    }
  }
}

static void d2IntegralV_GKdsdt(double r[NR], double s[NT], double t, double p, double dsdt[NS]) {
  const double pr = 1.0;
  const double tr = 1673.15;
  const double y  = 0.3;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double dvds[NS], d2vdsdt[NS], dcRefds[NS], d2cdsdt[NS], dmwds[NS], dcpds[NS], d3vdsdp2[NS], d4vdsdp3[NS], d5vdsdp4[NS], denom;
  int i, j;
  
  for (i=0; i<NS; i++) dsdt[i] = 0.0;
  if (fabs(p-pr) < 10.0*DBL_EPSILON) return;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return;
  
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }

  for (i=0; i<NS; i++) { 
    dvds[i]    = 0.0; d2vdsdt[i]  = 0.0; dcRefds[i]  = 0.0; d2cdsdt[i]  = 0.0; dmwds[i] = 0.0; 
    dcpds[i]   = 0.0; d3vdsdp2[i] = 0.0; d4vdsdp3[i] = 0.0; d5vdsdp4[i] = 0.0;
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    double dmOxds[NS], dmOxTotds[NS];
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
    for (j=0; j<NS; j++) { dmOxds[j] = 0.0; dmOxTotds[j] = 0.0; }
    if (iCmpFe2SiO4_6 != -1) {
      for (j=0; j<NS; j++) {
        if      (iOxFe2O3  == i) dmOxds[j] += -2.0*y*s[iCmpFe2SiO4_6]*dnSpeciesds[j];		 
        else if (iOxFeO	   == i) dmOxds[j] += -2.0*(1.0-2.0*y)*s[iCmpFe2SiO4_6]*dnSpeciesds[j]; 	 
        else if (iOxFeO1_3 == i) dmOxds[j] += 2.0*s[iCmpFe2SiO4_6]*dnSpeciesds[j];
	dmOxTotds[j] += 2.0*y*s[iCmpFe2SiO4_6]*dnSpeciesds[j]; 
      }
      if      (iOxFe2O3  == i) dmOxds[iCmpFe2SiO4_6] += -2.0*y*nSpecies;	   
      else if (iOxFeO	 == i) dmOxds[iCmpFe2SiO4_6] += -2.0*(1.0-2.0*y)*nSpecies; 
      else if (iOxFeO1_3 == i) dmOxds[iCmpFe2SiO4_6] += 2.0*nSpecies;
      dmOxTotds[iCmpFe2SiO4_6] += 2.0*y*nSpecies;		   
    }
    if (iCmpFe2AlO4_1 != -1) {
      for (j=0; j<NS; j++) {
        if      (iOxFe2O3  == i) dmOxds[j] += -2.0*y*s[iCmpFe2AlO4_1]*dnSpeciesds[j];		 
        else if (iOxFeO	   == i) dmOxds[j] += -2.0*(1.0-2.0*y)*s[iCmpFe2AlO4_1]*dnSpeciesds[j]; 	 
        else if (iOxFeO1_3 == i) dmOxds[j] += 2.0*s[iCmpFe2AlO4_1]*dnSpeciesds[j];
	dmOxTotds[j] += 2.0*y*s[iCmpFe2AlO4_1]*dnSpeciesds[j]; 
      }
      if      (iOxFe2O3  == i) dmOxds[iCmpFe2AlO4_1] += -2.0*y*nSpecies;	   
      else if (iOxFeO	 == i) dmOxds[iCmpFe2AlO4_1] += -2.0*(1.0-2.0*y)*nSpecies; 
      else if (iOxFeO1_3 == i) dmOxds[iCmpFe2AlO4_1] += 2.0*nSpecies;
      dmOxTotds[iCmpFe2AlO4_1] += 2.0*y*nSpecies;		   
    }
    for (j=0; j<NS; j++) {
      dvds[j]	   += dmOxds[j]*bulkSystem[i].gk_v;
      d2vdsdt[j]   += dmOxds[j]*bulkSystem[i].gk_dvdt;
      dmwds[j]     += dmOxds[j]*bulkSystem[i].mw;
      dcpds[j]     += dmOxds[j]*bulkSystem[i].gk_cp;  
      dcRefds[j]   += dmOxds[j]*bulkSystem[i].gk_c/mOxTot - mOx[i]*bulkSystem[i].gk_c*dmOxTotds[j]/(mOxTot*mOxTot);
      dcRefds[j]   += (iOxAl2O3 != -1) ? dmOxds[j]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
        	    - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotds[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
      d2cdsdt[j]   += dmOxds[j]*bulkSystem[i].gk_dcdt/mOxTot - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotds[j]/(mOxTot*mOxTot);
      d3vdsdp2[j]  += dmOxds[j]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d4vdsdp3[j]  += dmOxds[j]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d5vdsdp4[j]  += dmOxds[j]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    }
  }
  if (v == 0.0) return;

  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
  a	  = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
  b	  = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
  sum	  = a*a - 4.0*b;

  for (i=0; i<NS; i++) {
    double dalphads = d2vdsdt[i]/v - dvdt*dvds[i]/(v*v);
    double dv0ds    = (dvds[i] + v*dalphads*(t-tr))*exp(alpha*(t-tr));      
    double dv1Refds = -2.0*v*dvds[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
  		      -v*v*(-1000.0*(cRef*dmwds[i]+2.0*mw*dcRefds[i])/(mw*mw*cRef*cRef*cRef) 
        	            + 2.0*tr*alpha*dalphads/(cp) - tr*alpha*alpha*dcpds[i]/(cp*cp));   
    double dcds     = dcRefds[i] + (t-tr)*d2cdsdt[i];
    double dv1ds    = -2.0*v0*dv0ds*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  		      -v0*v0*(-1000.0*(c*dmwds[i]+2.0*mw*dcds)/(mw*mw*c*c*c) 
        	              + 2.0*t*alpha*dalphads/(cp) - t*alpha*alpha*dcpds[i]/(cp*cp));	  
    double dv2ds    = d3vdsdp2[i];
    double ddenomds = 2.0*dv1Refds*d3vdp3+2.0*v1Ref*d4vdsdp3[i]-6.0*d2vdp2*d3vdsdp2[i]; 
    double dads     = (d3vdsdp2[i]*d3vdp3+d2vdp2*d4vdsdp3[i]-dv1Refds*d4vdp4/2.0-v1Ref*d5vdsdp4[i]/2.0)/denom
  		    - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomds;
    double dbds     = (d3vdsdp2[i]*d4vdp4/4.0+d2vdp2*d5vdsdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdsdp3[i])/denom
  		    - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomds;		    
    double dv0dt    = v*alpha*exp(alpha*(t-tr));
    double dv1dt    = - 2.0*v0*v0*alpha*(1000.0/(mw*c*c) + t*alpha*alpha/(cp)) - v0*v0*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp));

    double d2v0dsdt = v*dalphads*exp(alpha*(t-tr)) + (dvds[i] + v*dalphads*(t-tr))*alpha*exp(alpha*(t-tr));
    double d2v1dsdt = -2.0*(dv0dt*dv0ds + v0*d2v0dsdt)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  		    - 2.0*v0*dv0ds*(- 2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
  		    - 2.0*v0*dv0dt*(- 1000.0*(c*dmwds[i]+2.0*mw*dcds)/(mw*mw*c*c*c) 
        			    + 2.0*t*alpha*dalphads/(cp) - t*alpha*alpha*dcpds[i]/(cp*cp))
        	    - v0*v0*(- 1000.0*(dcdt*dmwds[i]+2.0*mw*d2cdsdt[i])/(mw*mw*c*c*c) + 3000.0*(c*dmwds[i]+2.0*mw*dcds)*dcdt/(mw*mw*c*c*c*c)
        		     + 2.0*alpha*dalphads/(cp) - alpha*alpha*dcpds[i]/(cp*cp));
    double d2gIntdsdt = 0.0;

    if ((a == 0.0) && (b == 0.0)) {
      d2gIntdsdt       = d2v0dsdt*(p-pr) + d2v1dsdt*(p-pr)*(p-pr)/2.0;
 
    } else if ((a != 0.0) && (b == 0.0)) {
      printf("*-->Exception in d2IntegralV_GKdsdt (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
      d2gIntdsdt       = 0.0;
 
    } else if ((a == 0.0) && (b != 0.0)) {
      printf("*-->Exception in d2IntegralV_GKdsdt (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
      d2gIntdsdt       = 0.0;

    } else if (sum > 0.0) {   
      d2gIntdsdt       = d2gdrdtGMAP(p/10000.0, pr/10000.0, 
                                     v0,             v1*10000.0,    v2*10000.0*10000.0,    a*10000.0,    b*10000.0*10000.0, 
				     dv0ds,       dv1ds*10000.0, dv2ds*10000.0*10000.0, dads*10000.0, dbds*10000.0*10000.0, 
				     dv0dt,       dv1dt*10000.0, 
				     d2v0dsdt, d2v1dsdt*10000.0)*10000.0;
       
    } else if (sum == 0.0) {
      printf("*-->Exception in d2IntegralV_GKdsdt (liquid.c). a*a-4*b is equal to zero.\n"); liqERRstate = ERR_SUM_ZERO;
      d2gIntdsdt       = 0.0;
 
    } else if(sum < 0.0) {
      d2gIntdsdt       = d2gdrdtLMAP(p/10000.0, pr/10000.0, 
                                     v0,             v1*10000.0,    v2*10000.0*10000.0,    a*10000.0,    b*10000.0*10000.0, 
				     dv0ds,       dv1ds*10000.0, dv2ds*10000.0*10000.0, dads*10000.0, dbds*10000.0*10000.0, 
				     dv0dt,       dv1dt*10000.0, 
				     d2v0dsdt, d2v1dsdt*10000.0)*10000.0;
 
    }
    
    dsdt[i] += d2gIntdsdt;
    
  }
}

static double d2IntegralV_GKdT2(double r[NR], double s[NT], double t, double p)  {
  const double pr	  = 1.0;
  const double tr	  = 1673.15;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum, denom;
  double dv0dt, dv1dt, d2v0dt2, d2v1dt2, d2gIntdt2;
  int i, j;

  if (fabs(p-pr) < 10.0*DBL_EPSILON) return (double) 0.0;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return 0.0;
  
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
  }
  if (v == 0.0) return 0.0;
 
  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
  a	  = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
  b	  = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
  sum	  = a*a - 4.0*b;
  
  dv0dt   = alpha*v*exp(alpha*(t-tr));
  dv1dt   = - 2.0*v0*dv0dt*(1000.0/(mw*c*c) + t*alpha*alpha/(cp)) - v0*v0*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp));
  d2v0dt2 = alpha*alpha*v*exp(alpha*(t-tr));
  d2v1dt2 = - 2.0*(dv0dt*dv0dt+v0*d2v0dt2)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  	    - 4.0*v0*dv0dt*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
            - v0*v0*(6000.0*dcdt*dcdt/(mw*c*c*c*c));
  d2gIntdt2 = 0.0;
  
  if ((a == 0.0) && (b == 0.0)) {
    d2gIntdt2 += alpha*alpha*v0*(p-pr) + d2v1dt2*(p-pr)*(p-pr)/2.0;
    
  } else if ((a != 0.0) && (b == 0.0)) {
    printf("*-->Exception in d2IntegralV_GKdT2 (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
    d2gIntdt2	    = 0.0;
    
  } else if ((a == 0.0) && (b != 0.0)) {
    printf("*-->Exception in d2IntegralV_GKdT2 (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
    d2gIntdt2	    = 0.0;

  } else if (sum > 0.0) {   
    d2gIntdt2 = d2gdt2GMAP(p/10000.0, pr/10000.0, 
                           v0,           v1*10000.0, v2*10000.0*10000.0, a*10000.0, b*10000.0*10000.0, 
			   dv0dt,     dv1dt*10000.0, 
			   d2v0dt2, d2v1dt2*10000.0)*10000.0;
     
  } else if (sum == 0.0) {
    printf("*-->Exception in d2IntegralV_GKdT2 (liquid.c). a*a-4*b is equal to zero.\n"); liqERRstate = ERR_SUM_ZERO;
    d2gIntdt2	    = 0.0;
 
  } else if(sum < 0.0) {
    d2gIntdt2 = d2gdt2LMAP(p/10000.0, pr/10000.0, 
                           v0,           v1*10000.0, v2*10000.0*10000.0, a*10000.0, b*10000.0*10000.0, 
			   dv0dt,     dv1dt*10000.0, 
			   d2v0dt2, d2v1dt2*10000.0)*10000.0;
 
  }

  return d2gIntdt2;
}
  
static double d2IntegralV_GKdTdP(double r[NR], double s[NT], double t, double p) {
  const double pr	  = 1.0;
  const double tr	  = 1673.15;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double dv0dt, dv1dt, d2gIntdtdp;
  int i, j;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return 0.0;
  
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
  }
  if (v == 0.0) return 0.0;
 
  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  a	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)	 /(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
  b	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
  sum	  = a*a - 4.0*b;
  dv0dt   = alpha*v0;
  dv1dt   = - 2.0*v0*v0*alpha*(1000.0/(mw*c*c) + t*alpha*alpha/(cp)) - v0*v0*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp));
  
  if ((a == 0.0) && (b == 0.0)) {
    d2gIntdtdp = alpha*v0 + dv1dt*(p-pr);
    
  } else if ((a != 0.0) && (b == 0.0)) {
    printf("*-->Exception in d2IntegralV_GKdTdP (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
    d2gIntdtdp = 0.0;
    
  } else if ((a == 0.0) && (b != 0.0)) {
    printf("*-->Exception in d2IntegralV_GKdTdP (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
    d2gIntdtdp = 0.0;

  } else {   
    d2gIntdtdp = d2gdtdpMAP(p, pr, v0, v1, v2, a, b, dv0dt, dv1dt);
 
  }
  return d2gIntdtdp;
}  

static double d2IntegralV_GKdP2(double r[NR], double s[NT], double t, double p) {
  const double pr	  = 1.0;
  const double tr	  = 1673.15;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, cRef, c, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double d2gdp2;
  int i, j;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return 0.0;
  
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
  }
  if (v == 0.0) return 0.0;
 
  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  a	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)	 /(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
  b	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
  sum	  = a*a - 4.0*b;    
  
  if ((a == 0.0) && (b == 0.0)) {
    d2gdp2 = v1 + v2*(p-pr);
    
  } else if ((a != 0.0) && (b == 0.0)) {
    printf("*-->Exception in d2IntegralV_GKdP2 (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
    d2gdp2 = 0.0;
    
  } else if ((a == 0.0) && (b != 0.0)) {
    printf("*-->Exception in d2IntegralV_GKdP2 (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
    d2gdp2 = 0.0;

  } else {   
    d2gdp2 = d2gdp2MAP(p, pr, v0, v1, v2, a, b);
 
  }
       
  return d2gdp2;
}  

#endif /* USE_GHIORSO_KRESS_MODEL */

static double fillG (double r[NR], double s[NT], double t, double p) {
  double result, config;
  int i, j;

  /* Taylor expansion and standard state terms */
  result = Gconst;
  for (i=0; i<NR; i++) {
    result += gr[i]*r[i];
    for (j=i; j<NR; j++) result += grr[i][j]*r[i]*r[j];
    for (j=0; j<NS; j++) result += grs[i][j]*r[i]*s[j];
  }
  for (i=0; i<NS; i++) {
    result += gs[i]*s[i];
    for (j=i; j<NS; j++) result += gss[i][j]*s[i]*s[j];
  }

  /* Configurational entropy terms */
  for (i=0, config=0.0; i<NE; i++) if (xSpecies[i] > 0.0) config += xSpecies[i]*log(xSpecies[i]);
  if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0) config += xSpecies[nH2O]*log(xSpecies[nH2O]) + (1.0-xSpecies[nH2O])*log(1.0-xSpecies[nH2O]); 
  result += R*t*nSpecies*config;

#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double yIV    = 1.0;
    double gIntIV = integralV_GK(r, s, t, p); 
    double gInt;
    
    for (i=0; i<NY; i++) yIV -= (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
    gInt = gIntIV + R*t*yIV*log(yIV);
    
    for (i=0; i<NY; i++) {
      double f = fCN[i];
      double deltaG_GK, y;
      
      y         = (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
      deltaG_GK = ssCnModelParameters[i*nc+0].enthalpy - t*ssCnModelParameters[i*nc+0].entropy;
      for (j=0; j<NR; j++) deltaG_GK += (  (ssCnModelParameters[i*nc+j+1].enthalpy - t*ssCnModelParameters[i*nc+j+1].entropy)
	                                 - (ssCnModelParameters[i*nc  +0].enthalpy - t*ssCnModelParameters[i*nc  +0].entropy))*r[j];
      
      gInt += R*t*y*log(y) + y*deltaG_GK + (f-1.0)*y*gIntIV;
    }
    
    result += gInt;
  }
#endif /* USE_GHIORSO_KRESS_MODEL */

  return result;
}

static double fillS (double r[NR], double s[NT], double t, double p) {
  double result, config;
  int i, j;

  /* Taylor expansion and standard state terms */
  result = Sconst;
  for (i=0; i<NR; i++) {
    result += sr[i]*r[i];
    for (j=i; j<NR; j++) result += srr[i][j]*r[i]*r[j];
    for (j=0; j<NS; j++) result += srs[i][j]*r[i]*s[j];
  }
  for (i=0; i<NS; i++) {
    result += ss[i]*s[i];
    for (j=i; j<NS; j++) result += sss[i][j]*s[i]*s[j];
  }

  /* Configurational entropy terms */
  for (i=0, config=0.0; i<NE; i++) if (xSpecies[i] > 0.0) config += xSpecies[i]*log(xSpecies[i]);
  if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0) config += xSpecies[nH2O]*log(xSpecies[nH2O]) + (1.0-xSpecies[nH2O])*log(1.0-xSpecies[nH2O]); 
  result -= R*nSpecies*config;
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double yIV       = 1.0;
    double dgIntIVdt = dIntegralV_GKdT(r, s, t, p);
    double dgIntdt;
    
    for (i=0; i<NY; i++) yIV -= (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
    dgIntdt = dgIntIVdt + R*yIV*log(yIV);
    
    for (i=0; i<NY; i++) {
      double f = fCN[i];
      double dDeltaG_GKdT, y;
      
      y            = (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
      dDeltaG_GKdT = - ssCnModelParameters[i*nc+0].entropy;
      for (j=0; j<NR; j++) dDeltaG_GKdT += (-ssCnModelParameters[i*nc+j+1].entropy + ssCnModelParameters[i*nc+0].entropy)*r[j];
      
      dgIntdt += R*y*log(y) + y*dDeltaG_GKdT + (f-1.0)*y*dgIntIVdt;
    }

    result += -dgIntdt;
  }

/*  Maple-derived equivalent functions:
dgdtLMAP(p, pr, v0, v1, v2, a, b, dv0dt, dv1dt)
dgdtGMAP(p, pr, v0, v1, v2, a, b, dv0dt, dv1dt)
*/

#endif /* USE_GHIORSO_KRESS_MODEL */

  return result;
}

#ifdef USE_GHIORSO_KRESS_MODEL

static double fillV (double r[NR], double s[NT], double t, double p) {
  const double pr	  = 1.0;
  const double tr	  = 1673.15;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, coeffCN;
  int i, j;
  double result = 0.0;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return result;
  
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
  }
  if (v == 0.0) return result;
 
  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  a	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)	 /(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
  b	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;

  if (1.0 + a*(p-pr) + b*(p-pr)*(p-pr) == 0.0) return result;
  
  for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i];

  result = coeffCN*((v0 + (v1+v0*a)*(p-pr) + (v2/2.0+v1*a+v0*b)*(p-pr)*(p-pr))/(1.0 + a*(p-pr) + b*(p-pr)*(p-pr)));
  return result;
}

#else

static double fillV (double r[NR], double s[NT], double t, double p) {
  double result;
  int i, j;

  /* Taylor expansion and standard state terms */
  result = Vconst;
  for (i=0; i<NR; i++) {
    result += vr[i]*r[i];
    for (j=i; j<NR; j++) result += vrr[i][j]*r[i]*r[j];
    for (j=0; j<NS; j++) result += vrs[i][j]*r[i]*s[j];
  }
  for (i=0; i<NS; i++) {
    result += vs[i]*s[i];
    for (j=i; j<NS; j++) result += vss[i][j]*s[i]*s[j];
  }

  return result;
}

#endif /* USE_GHIORSO_KRESS_MODEL */


static void fillDGDR (double r[NR], double s[NT], double t, double p, double *result) { 
  int i, j;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) {
    result[i] = gr[i] + grr[i][i]*r[i];
    for (j=0; j<NR; j++) result[i] += grr[i][j]*r[j];
    for (j=0; j<NS; j++) result[i] += grs[i][j]*s[j];
  }

  /* Configurational entropy terms */
  for (j=0; j<NR; j++) {
    double config = 0.0;
    for (i=0; i<NE; i++) if (xSpecies[i] > 0.0 && dxSpeciesdr[i][j] != 0.0) config += dxSpeciesdr[i][j]*(1.0 + log(xSpecies[i]));
    if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0 && dxSpeciesdr[nH2O][j] != 0.0) 
      config += dxSpeciesdr[nH2O][j]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O])); 
    result[j] += R*t*nSpecies*config;
  }

#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double dgIntIVdr[NR];
  
    dIntegralV_GKdr(r, s, t, p, dgIntIVdr);
    
    for (i=0; i<NR; i++) {
      result[i] += dgIntIVdr[i];
      for (j=0; j<NY; j++) {
        double y = (s[NS+j] > 0.0) ? s[NS+j] : DBL_EPSILON;
        double f = fCN[j];
        
        result[i] += y*( (ssCnModelParameters[j*nc+i+1].enthalpy - t*ssCnModelParameters[j*nc+i+1].entropy)
        	        -(ssCnModelParameters[j*nc  +0].enthalpy - t*ssCnModelParameters[j*nc  +0].entropy)) 
        	   + (f-1.0)*y*dgIntIVdr[i];
      }
    }
    
  }
#endif /* USE_GHIORSO_KRESS_MODEL */
  
}

static void fillDGDS (double r[NR], double s[NT], double t, double p, double *result) {
  int i, j;

  for (j=0; j<NT; j++) result[j] = 0.0;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NS; i++) {
    result[i] = gs[i] + gss[i][i]*s[i];
    for (j=0; j<NS; j++) result[i] += gss[i][j]*s[j];
    for (j=0; j<NR; j++) result[i] += grs[j][i]*r[j];
  }

  /* Configurational entropy terms */
  for (j=0; j<NS; j++) {
    double config = 0.0;
    for (i=0; i<NE; i++) if (xSpecies[i] > 0.0) 
      config += dnSpeciesds[j]*xSpecies[i]*log(xSpecies[i]) + nSpecies*dxSpeciesds[i][j]*(1.0 + log(xSpecies[i]));
    if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0) 
      config += dnSpeciesds[j]*(xSpecies[nH2O]*log(xSpecies[nH2O]) + (1.0-xSpecies[nH2O])*log(1.0-xSpecies[nH2O]))
              + nSpecies*dxSpeciesds[nH2O][j]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O])); 
    result[j] += R*t*config;
  }
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double yIV    = 1.0;
    double gIntIV = integralV_GK(r, s, t, p);  
    double dgIntIVds[NS];
  
    dIntegralV_GKds(r, s, t, p, dgIntIVds);
    
    for (i=0; i<NS; i++) {
      result[i] += dgIntIVds[i];
      for (j=0; j<NY; j++) {
        double y = (s[NS+j] > 0.0) ? s[NS+j] : DBL_EPSILON;
        double f = fCN[j];
        result[i] += y*( (ssCnModelParameters[j*nc+i+1].enthalpy - t*ssCnModelParameters[j*nc+i+1].entropy)
        	        -(ssCnModelParameters[j*nc  +0].enthalpy - t*ssCnModelParameters[j*nc  +0].entropy)) 
        	   + (f-1.0)*y*dgIntIVds[i];
      }
    }
    
    for (i=0; i<NY; i++) {
      double f =fCN[i];
      double deltaG_GK, y;
      
      y         = (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
      deltaG_GK = ssCnModelParameters[i*nc+0].enthalpy - t*ssCnModelParameters[i*nc+0].entropy;
      
      for (j=0; j<NR; j++) deltaG_GK += ( (ssCnModelParameters[i*nc+j+1].enthalpy - t*ssCnModelParameters[i*nc+j+1].entropy)
	                                 -(ssCnModelParameters[i*nc  +0].enthalpy - t*ssCnModelParameters[i*nc  +0].entropy))*r[j];
      
      yIV  -= y;
      result[NS+i] += R*t*log(y) + deltaG_GK + (f-1.0)*gIntIV;
    }
    
    for (i=0; i<NY; i++) result[NS+i] -= R*t*log(yIV);
    
  }
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillDGDW (double r[NR], double s[NT], double t, double p, double *result) {
  int i, j, k, l, m, n;

  /*******************************
   * Parameters: NW WH(), NE H() *
   *             NW WS(), NE S() *
   *             NW WV(), NE V() *
   *******************************/
  for (i=0; i<(3*NP); i++) result[i] = 0.0;

  /**************************************
   * NW W parameters solution are first *
   **************************************/
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    result[     n] +=         taylorCoeff[n+NE+1][0+1];
    result[  NP+n] +=      -t*taylorCoeff[n+NE+1][0+1];
#ifndef USE_GHIORSO_KRESS_MODEL
    result[2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][0+1];
#endif /* USE_GHIORSO_KRESS_MODEL */
    m = 0;
    for (j=0, m=0; j<NR; j++) {
      result[	  n] += 	taylorCoeff[n+NE+1][1+j+1]*r[j];
      result[  NP+n] +=      -t*taylorCoeff[n+NE+1][1+j+1]*r[j];
#ifndef USE_GHIORSO_KRESS_MODEL
      result[2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+j+1]*r[j];
#endif /* USE_GHIORSO_KRESS_MODEL */
      for (k=j; k<NR; k++, m++) {
        result[     n] +=	  taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j]*r[k];
        result[  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j]*r[k];
#ifndef USE_GHIORSO_KRESS_MODEL
        result[2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j]*r[k];
#endif /* USE_GHIORSO_KRESS_MODEL */
      }
      for (k=0; k<NS; k++, m++) {
        result[     n] += 	  taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j]*s[k];
        result[  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j]*s[k];
#ifndef USE_GHIORSO_KRESS_MODEL
        result[2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j]*s[k];
#endif /* USE_GHIORSO_KRESS_MODEL */
      }
    }
    for (j=0; j<NS; j++) {
      result[	  n] += 	taylorCoeff[n+NE+1][1+NR+j+1]*s[j];
      result[  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+j+1]*s[j];
#ifndef USE_GHIORSO_KRESS_MODEL
      result[2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+j+1]*s[j];
#endif /* USE_GHIORSO_KRESS_MODEL */
      for (k=j; k<NS; k++, m++) {
        result[     n] += 	  taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[j]*s[k];
        result[  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[j]*s[k];
#ifndef USE_GHIORSO_KRESS_MODEL
        result[2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[j]*s[k];
#endif /* USE_GHIORSO_KRESS_MODEL */
      }
    }
  }

  /**************************************
   * NE standard state terms are second *
   **************************************/
  for (i=0; i<NE; i++, n++) {
    result[	n] +=         taylorCoeff[i+1][0+1];
    result[  NP+n] +=      -t*taylorCoeff[i+1][0+1];
#ifndef USE_GHIORSO_KRESS_MODEL
    result[2*NP+n] += (p-1.0)*taylorCoeff[i+1][0+1];
#endif /* USE_GHIORSO_KRESS_MODEL */
    for (j=0; j<NR; j++) {
      result[	  n] += 	taylorCoeff[i+1][1+j+1]*r[j];
      result[  NP+n] +=      -t*taylorCoeff[i+1][1+j+1]*r[j];
#ifndef USE_GHIORSO_KRESS_MODEL
      result[2*NP+n] += (p-1.0)*taylorCoeff[i+1][1+j+1]*r[j];
#endif /* USE_GHIORSO_KRESS_MODEL */
    }
    for (j=0; j<NS; j++) {
      result[	  n] += 	taylorCoeff[i+1][1+NR+j+1]*s[j];
      result[  NP+n] +=      -t*taylorCoeff[i+1][1+NR+j+1]*s[j];
#ifndef USE_GHIORSO_KRESS_MODEL
      result[2*NP+n] += (p-1.0)*taylorCoeff[i+1][1+NR+j+1]*s[j];
#endif /* USE_GHIORSO_KRESS_MODEL */
    }
  }
}

static void fillD2GDR2 (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j, k;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) {
    result[i][i] = 2.0*grr[i][i];
    for (j=i+1; j<NR; j++) {
      result[i][j] = grr[i][j];
      result[j][i] = grr[i][j];
    }
  }

  /* Configurational entropy terms */
  for (j=0; j<NR; j++) {
    for (k=j; k<NR; k++) {
      double config = 0.0;
      for (i=0; i<NE; i++) if (xSpecies[i] > 0.0 && dxSpeciesdr[i][j] != 0.0 && dxSpeciesdr[i][k] != 0.0) 
        config += dxSpeciesdr[i][j]*dxSpeciesdr[i][k]/xSpecies[i];
      if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0 && dxSpeciesdr[nH2O][j] != 0.0 && dxSpeciesdr[nH2O][k] != 0.0) 
        config += dxSpeciesdr[nH2O][j]*dxSpeciesdr[nH2O][k]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O])); 
      result[j][k] += R*t*nSpecies*config;
      result[k][j]  = result[j][k];
    }
  }
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double d2gIntIVdr2[NR][NR];
  
    d2IntegralV_GKdr2(r, s, t, p, d2gIntIVdr2);
    
    for (i=0; i<NR; i++) {
      for (j=i; j<NR; j++) {
        
        result[i][j] += d2gIntIVdr2[i][j];
	if (i != j) result[j][i] += d2gIntIVdr2[i][j];
	
	for (k=0; k<NY; k++) {
          double y = (s[NS+k] > 0.0) ? s[NS+k] : DBL_EPSILON;
          double f = fCN[k];
	  result[i][j] += (f-1.0)*y*d2gIntIVdr2[i][j];
	  if (i != j) result[j][i] += (f-1.0)*y*d2gIntIVdr2[i][j];
	}
	
      }
    }
  } 
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillD2GDRDS (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j, k;

  for (j=0; j<NR; j++) for (k=0; k<NT; k++) result[j][k] = 0.0;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) for (j=0; j<NS; j++) result[i][j] = grs[i][j];

  /* Configurational entopy terms */
  for (j=0; j<NR; j++) {
    for (k=0; k<NS; k++) {
      double config = 0.0;
      for (i=0; i<NE; i++) if (xSpecies[i] > 0.0) 
        config += nSpecies*(d2xSpeciesdrds[i][j][k]*log(xSpecies[i]) + dxSpeciesdr[i][j]*dxSpeciesds[i][k]/xSpecies[i])
	        + dnSpeciesds[k]*(dxSpeciesdr[i][j]*(1.0 + log(xSpecies[i])));
      if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0) 
        config += dnSpeciesds[k]*dxSpeciesdr[nH2O][j]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O]))	
                + nSpecies*(d2xSpeciesdrds[nH2O][j][k]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O])) 
		  + dxSpeciesds[nH2O][k]*dxSpeciesdr[nH2O][j]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O]))); 
      result[j][k] += R*t*config;
    }
  }
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double dgIntIVdr[NR];
    double d2gIntIVdrds[NR][NS];
  
    d2IntegralV_GKdrds(r, s, t, p, d2gIntIVdrds);
    
    for (i=0; i<NR; i++) {
      for (j=0; j<NS; j++) {
        
        result[i][j] += d2gIntIVdrds[i][j];
	
	for (k=0; k<NY; k++) {
          double y = (s[NS+k] > 0.0) ? s[NS+k] : DBL_EPSILON;
          double f = fCN[k];
	  result[i][j] += (f-1.0)*y*d2gIntIVdrds[i][j];
	}
	
      }
    }
  
    dIntegralV_GKdr(r, s, t, p, dgIntIVdr);
    
    for (i=0; i<NR; i++) {
      for (j=0; j<NY; j++) {
        double f = fCN[j];
        
        result[i][NS+j] += ( (ssCnModelParameters[j*nc+i+1].enthalpy - t*ssCnModelParameters[j*nc+i+1].entropy)
        	            -(ssCnModelParameters[j*nc  +0].enthalpy - t*ssCnModelParameters[j*nc  +0].entropy)) 
        	         + (f-1.0)*dgIntIVdr[i];
      }
    }
    
  }
#endif /* USE_GHIORSO_KRESS_MODEL */
}

static void fillD2GDRDT (double r[NR], double s[NT], double t, double p, double *result) {
  int i, j;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) {
    result[i] = -sr[i] + -srr[i][i]*r[i];
    for (j=0; j<NR; j++) result[i] += -srr[i][j]*r[j];
    for (j=0; j<NS; j++) result[i] += -srs[i][j]*s[j];
  }

  /* Configurational entropy terms */
  for (j=0; j<NR; j++) {
    double config = 0.0;
    for (i=0; i<NE; i++) if (xSpecies[i] > 0.0 && dxSpeciesdr[i][j] != 0.0) config += dxSpeciesdr[i][j]*(1.0 + log(xSpecies[i]));
    if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0 && dxSpeciesdr[nH2O][j] != 0.0) 
      config += dxSpeciesdr[nH2O][j]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O])); 
    result[j] += R*nSpecies*config;
  }
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double d2gIntIVdrdt[NR];
  
    d2IntegralV_GKdrdt(r, s, t, p, d2gIntIVdrdt);
  
    for (i=0; i<NR; i++) {
      result[i] += d2gIntIVdrdt[i];

      for (j=0; j<NY; j++) {
        double y = (s[NS+j] > 0.0) ? s[NS+j] : DBL_EPSILON;
        double f = fCN[j];
        
        result[i] += y*(-ssCnModelParameters[j*nc+i+1].entropy + ssCnModelParameters[j*nc  +0].entropy) + (f-1.0)*y*d2gIntIVdrdt[i];
      }
    
    }
  }
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillD2GDRDP (double r[NR], double s[NT], double t, double p, double *result) {
  int i, j;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) {
#ifdef USE_GHIORSO_KRESS_MODEL
    result[i] = 0.0;
#else
    result[i] = vr[i] + vrr[i][i]*r[i];
    for (j=0; j<NR; j++) result[i] += vrr[i][j]*r[j];
    for (j=0; j<NS; j++) result[i] += vrs[i][j]*s[j];
#endif /* USE_GHIORSO_KRESS_MODEL */
  }
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double coeffCN, d2gIntIVdrdp[NR];
    
    d2IntegralV_GKdrdp(r, s, t, p, d2gIntIVdrdp);
    for (j=0, coeffCN=1.0; j<NY; j++) coeffCN += (fCN[j]-1.0)*s[NS+j]; 
    
    for (i=0; i<NR; i++) result[i] += coeffCN*d2gIntIVdrdp[i];
  } 
#endif /* USE_GHIORSO_KRESS_MODEL */
}

static void fillD2GDRDW (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j, k, l, m, n, ii;

  /*******************************
   * Parameters: NW WH(), NE H() *
   *             NW WS(), NE S() *
   *             NW WV(), NE V() *
   *******************************/
  for (ii=0; ii<NR; ii++) for (i=0; i<(3*NP); i++) result[ii][i] = 0.0;

  /**************************************
   * NW W parameters solution are first *
   **************************************/
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    for (ii=0; ii<NR; ii++) {
      result[ii][     n] +=	    taylorCoeff[n+NE+1][1+ii+1];
      result[ii][  NP+n] +=	 -t*taylorCoeff[n+NE+1][1+ii+1];
#ifndef USE_GHIORSO_KRESS_MODEL
      result[ii][2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+ii+1];
#endif /* USE_GHIORSO_KRESS_MODEL */
      m = 0;
      for (j=0, m=0; j<NR; j++) {
    	for (k=j; k<NR; k++, m++) {
	  if (j == ii) {
    	    result[ii][     n] +=         taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[k];
    	    result[ii][  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[k];
#ifndef USE_GHIORSO_KRESS_MODEL
    	    result[ii][2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[k];
#endif /* USE_GHIORSO_KRESS_MODEL */
          }
	  if (k == ii) {
	    result[ii][     n] +=         taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j];
	    result[ii][  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j];
#ifndef USE_GHIORSO_KRESS_MODEL
	    result[ii][2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j];
#endif /* USE_GHIORSO_KRESS_MODEL */
	  }
    	}
    	for (k=0; k<NS; k++, m++) {
	  if (j == ii) {
    	    result[ii][     n] +=         taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[k];
    	    result[ii][  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[k];
#ifndef USE_GHIORSO_KRESS_MODEL
    	    result[ii][2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[k];
#endif /* USE_GHIORSO_KRESS_MODEL */
    	  }
	}
      }
    }
  }

  /**************************************
   * NE standard state terms are second *
   **************************************/
  for (i=0; i<NE; i++, n++) {
    for (ii=0; ii<NR; ii++) {
      result[ii][     n] += 	    taylorCoeff[i+1][1+ii+1];
      result[ii][  NP+n] +=      -t*taylorCoeff[i+1][1+ii+1];
#ifndef USE_GHIORSO_KRESS_MODEL
      result[ii][2*NP+n] += (p-1.0)*taylorCoeff[i+1][1+ii+1];
#endif /* USE_GHIORSO_KRESS_MODEL */
    }
  }
}

static void fillD2GDS2 (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j, k;
  
  for (j=0; j<NT; j++) for (k=0; k<NT; k++) result[j][k] = 0.0;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NS; i++) {
    result[i][i] = 2.0*gss[i][i];
    for (j=i+1; j<NS; j++) {
      result[i][j] = gss[i][j];
      result[j][i] = gss[i][j];
    }
  }

  /* Configurational entropy terms */
  for (j=0; j<NS; j++) {
    for (k=j; k<NS; k++) {
      double config = 0.0;
      for (i=0; i<NE; i++) if (xSpecies[i] > 0.0) 
        config += nSpecies*dxSpeciesds[i][j]*dxSpeciesds[i][k]/xSpecies[i]
 		+ dnSpeciesds[k]*dxSpeciesds[i][j]*(1.0 + log(xSpecies[i]))
 		+ dnSpeciesds[j]*dxSpeciesds[i][k]*(1.0 + log(xSpecies[i]))
 		+ d2nSpeciesds2[j][k]*xSpecies[i]*log(xSpecies[i]);
    if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0) 
      config += d2nSpeciesds2[j][k]*(xSpecies[nH2O]*log(xSpecies[nH2O]) + (1.0-xSpecies[nH2O])*log(1.0-xSpecies[nH2O]))
              + dnSpeciesds[j]*dxSpeciesds[nH2O][k]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O]))
              + dnSpeciesds[k]*dxSpeciesds[nH2O][j]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O]))
	      + nSpecies*dxSpeciesds[nH2O][j]*dxSpeciesds[nH2O][k]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O])); 
      result[j][k] += R*t*config;
      result[k][j]  = result[j][k];
    }
  }
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double yIV = 1.0;
    double d2gIntIVds2[NS][NS];
  
    d2IntegralV_GKds2(r, s, t, p, d2gIntIVds2);
    
    for (i=0; i<NS; i++) {
      for (j=i; j<NS; j++) {
        
        result[i][j] += d2gIntIVds2[i][j];
	if (i != j) result[j][i] += d2gIntIVds2[i][j];
	
	for (k=0; k<NY; k++) {
          double y = (s[NS+k] > 0.0) ? s[NS+k] : DBL_EPSILON;
          double f = fCN[k];
	  result[i][j] += (f-1.0)*y*d2gIntIVds2[i][j];
	  if (i != j) result[j][i] += (f-1.0)*y*d2gIntIVds2[i][j];
	}
	
      }
    }
    
    for (i=0; i<NY; i++) yIV -= (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
    
    for (i=0; i<NY; i++) {
      double y = (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
      result[NS+i][NS+i] = R*t*(1.0/y + 1.0/yIV);
      for (j=i+1; j<NY; j++) { result[NS+i][NS+j] = R*t/yIV; result[NS+j][NS+i] = result[NS+i][NS+j]; }
    }
    
  }
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillD2GDSDT (double r[NR], double s[NT], double t, double p, double *result) {
  int i, j;

  for (i=0; i<NT; i++) result[i] = 0.0;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NS; i++) {
    result[i] = -ss[i] - sss[i][i]*s[i];
    for (j=0; j<NS; j++) result[i] += -sss[i][j]*s[j];
    for (j=0; j<NR; j++) result[i] += -srs[j][i]*r[j];
  }

  /* Configurational entropy terms */
  for (j=0; j<NS; j++) {
    double config = 0.0;
    for (i=0; i<NE; i++) if (xSpecies[i] > 0.0) 
      config += dnSpeciesds[j]*xSpecies[i]*log(xSpecies[i]) + nSpecies*dxSpeciesds[i][j]*(1.0 + log(xSpecies[i]));
    if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0) 
      config += dnSpeciesds[j]*(xSpecies[nH2O]*log(xSpecies[nH2O]) + (1.0-xSpecies[nH2O])*log(1.0-xSpecies[nH2O]))
              + nSpecies*dxSpeciesds[nH2O][j]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O])); 
    result[j] += R*config;
  }
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double yIV       = 1.0;
    double dgIntIVdt = dIntegralV_GKdT(r, s, t, p);
    double d2gIntIVdsdt[NS];
  
    d2IntegralV_GKdsdt(r, s, t, p, d2gIntIVdsdt);
  
    for (i=0; i<NS; i++) {
      result[i] += d2gIntIVdsdt[i];

      for (j=0; j<NY; j++) {
        double y = (s[NS+j] > 0.0) ? s[NS+j] : DBL_EPSILON;
        double f = fCN[j];
        
        result[i] += y*(-ssCnModelParameters[j*nc+i+1].entropy + ssCnModelParameters[j*nc  +0].entropy) + (f-1.0)*y*d2gIntIVdsdt[i];
      }
    
    }
    
    for (i=0; i<NY; i++) yIV -= (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
    
    for (i=0; i<NY; i++) {
      double f = fCN[i];
      double dDeltaG_GKdT, y;
      
      y            = (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
      dDeltaG_GKdT = - ssCnModelParameters[i*nc+0].entropy;
      for (j=0; j<NR; j++) dDeltaG_GKdT += (-ssCnModelParameters[i*nc+j+1].entropy + ssCnModelParameters[i*nc+0].entropy)*r[j];
      
      result[NS+i] += R*(log(y)-log(yIV)) + dDeltaG_GKdT + (f-1.0)*dgIntIVdt;
    }
  }
#endif /* USE_GHIORSO_KRESS_MODEL */

}

#ifdef USE_GHIORSO_KRESS_MODEL

static void fillD2GDSDP (double r[NR], double s[NT], double t, double p, double *result) {
  const double pr	  = 1.0;
  const double tr	  = 1673.15;
  const double y  = 0.3;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b;
  double dvds[NS], d2vdsdt[NS], dcRefds[NS], d2cdsdt[NS], dmwds[NS], dcpds[NS], d3vdsdp2[NS], d4vdsdp3[NS], d5vdsdp4[NS], denom;
  int i, j;

  for (i=0; i<NT; i++) result[i] = 0.0;

  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return;
 
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }
 
  for (i=0; i<NS; i++) { 
    dvds[i]    = 0.0; d2vdsdt[i]  = 0.0; dcRefds[i]  = 0.0; d2cdsdt[i]  = 0.0; dmwds[i] = 0.0; 
    dcpds[i]   = 0.0; d3vdsdp2[i] = 0.0; d4vdsdp3[i] = 0.0; d5vdsdp4[i] = 0.0;
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    double dmOxds[NS], dmOxTotds[NS];
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
    for (j=0; j<NS; j++) { dmOxds[j] = 0.0; dmOxTotds[j] = 0.0; }
    if (iCmpFe2SiO4_6 != -1) {
      for (j=0; j<NS; j++) {
        if      (iOxFe2O3  == i) dmOxds[j] += -2.0*y*s[iCmpFe2SiO4_6]*dnSpeciesds[j];		 
        else if (iOxFeO	   == i) dmOxds[j] += -2.0*(1.0-2.0*y)*s[iCmpFe2SiO4_6]*dnSpeciesds[j]; 	 
        else if (iOxFeO1_3 == i) dmOxds[j] += 2.0*s[iCmpFe2SiO4_6]*dnSpeciesds[j];
	dmOxTotds[j] += 2.0*y*s[iCmpFe2SiO4_6]*dnSpeciesds[j]; 
      }
      if      (iOxFe2O3  == i) dmOxds[iCmpFe2SiO4_6] += -2.0*y*nSpecies;	   
      else if (iOxFeO	 == i) dmOxds[iCmpFe2SiO4_6] += -2.0*(1.0-2.0*y)*nSpecies; 
      else if (iOxFeO1_3 == i) dmOxds[iCmpFe2SiO4_6] += 2.0*nSpecies;
      dmOxTotds[iCmpFe2SiO4_6] += 2.0*y*nSpecies;		   
    }
    if (iCmpFe2AlO4_1 != -1) {
      for (j=0; j<NS; j++) {
        if      (iOxFe2O3  == i) dmOxds[j] += -2.0*y*s[iCmpFe2AlO4_1]*dnSpeciesds[j];		 
        else if (iOxFeO	   == i) dmOxds[j] += -2.0*(1.0-2.0*y)*s[iCmpFe2AlO4_1]*dnSpeciesds[j]; 	 
        else if (iOxFeO1_3 == i) dmOxds[j] += 2.0*s[iCmpFe2AlO4_1]*dnSpeciesds[j];
	dmOxTotds[j] += 2.0*y*s[iCmpFe2AlO4_1]*dnSpeciesds[j]; 
      }
      if      (iOxFe2O3  == i) dmOxds[iCmpFe2AlO4_1] += -2.0*y*nSpecies;	   
      else if (iOxFeO	 == i) dmOxds[iCmpFe2AlO4_1] += -2.0*(1.0-2.0*y)*nSpecies; 
      else if (iOxFeO1_3 == i) dmOxds[iCmpFe2AlO4_1] += 2.0*nSpecies;
      dmOxTotds[iCmpFe2AlO4_1] += 2.0*y*nSpecies;		   
    }
    for (j=0; j<NS; j++) {
      dvds[j]	   += dmOxds[j]*bulkSystem[i].gk_v;
      d2vdsdt[j]   += dmOxds[j]*bulkSystem[i].gk_dvdt;
      dmwds[j]     += dmOxds[j]*bulkSystem[i].mw;
      dcpds[j]     += dmOxds[j]*bulkSystem[i].gk_cp;  
      dcRefds[j]   += dmOxds[j]*bulkSystem[i].gk_c/mOxTot - mOx[i]*bulkSystem[i].gk_c*dmOxTotds[j]/(mOxTot*mOxTot);
      dcRefds[j]   += (iOxAl2O3 != -1) ? dmOxds[j]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
        	    - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotds[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
      d2cdsdt[j]   += dmOxds[j]*bulkSystem[i].gk_dcdt/mOxTot - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotds[j]/(mOxTot*mOxTot);
      d3vdsdp2[j]  += dmOxds[j]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d4vdsdp3[j]  += dmOxds[j]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d5vdsdp4[j]  += dmOxds[j]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    }
  }
  if (v == 0.0) return;
 
  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
  a	  = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
  b	  = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;

  if (1.0 + a*(p-pr) + b*(p-pr)*(p-pr) == 0.0) return;


  for (i=0; i<NS; i++) {
    double dalphads = d2vdsdt[i]/v - dvdt*dvds[i]/(v*v);
    double dv0ds    = (dvds[i] + v*dalphads*(t-tr))*exp(alpha*(t-tr));      
    double dv1Refds = -2.0*v*dvds[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
  		      -v*v*(-1000.0*(cRef*dmwds[i]+2.0*mw*dcRefds[i])/(mw*mw*cRef*cRef*cRef) 
        	            + 2.0*tr*alpha*dalphads/(cp) - tr*alpha*alpha*dcpds[i]/(cp*cp));   
    double dcds     = dcRefds[i] + (t-tr)*d2cdsdt[i];
    double dv1ds    = -2.0*v0*dv0ds*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
  		      -v0*v0*(-1000.0*(c*dmwds[i]+2.0*mw*dcds)/(mw*mw*c*c*c) 
        	              + 2.0*t*alpha*dalphads/(cp) - t*alpha*alpha*dcpds[i]/(cp*cp));	  
    double dv2ds    = d3vdsdp2[i];
    double ddenomds = 2.0*dv1Refds*d3vdp3+2.0*v1Ref*d4vdsdp3[i]-6.0*d2vdp2*d3vdsdp2[i]; 
    double dads     = (d3vdsdp2[i]*d3vdp3+d2vdp2*d4vdsdp3[i]-dv1Refds*d4vdp4/2.0-v1Ref*d5vdsdp4[i]/2.0)/denom
  		    - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomds;
    double dbds     = (d3vdsdp2[i]*d4vdp4/4.0+d2vdp2*d5vdsdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdsdp3[i])/denom
  		    - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomds;
		    
    result[i] += (dv0ds + (dv1ds+dv0ds*a+v0*dads)*(p-pr) + (dv2ds/2.0+dv1ds*a+v1*dads+dv0ds*b+v0*dbds)*(p-pr)*(p-pr))
                 /(1.0 + a*(p-pr) + b*(p-pr)*(p-pr))
               - (v0 + (v1+v0*a)*(p-pr) + (v2/2.0+v1*a+v0*b)*(p-pr)*(p-pr))*(dads*(p-pr) + dbds*(p-pr)*(p-pr))
	         /((1.0 + a*(p-pr) + b*(p-pr)*(p-pr))*(1.0 + a*(p-pr) + b*(p-pr)*(p-pr)));
  }		    
  
  for (i=0; i<NY; i++) result[NS+i] = (fCN[i]-1.0)*((v0 + (v1+v0*a)*(p-pr) + (v2/2.0+v1*a+v0*b)*(p-pr)*(p-pr))/(1.0 + a*(p-pr) + b*(p-pr)*(p-pr)));

}

#else

static void fillD2GDSDP (double r[NR], double s[NT], double t, double p, double *result) {
  int i, j;

  for (i=0; i<NT; i++) result[i] = 0.0;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NS; i++) {
    result[i] = vs[i] + vss[i][i]*s[i];
    for (j=0; j<NS; j++) result[i] += vss[i][j]*s[j];
    for (j=0; j<NR; j++) result[i] += vrs[j][i]*r[j];
  }
  
}

#endif /* USE_GHIORSO_KRESS_MODEL */

static void fillD2GDSDW (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j, k, l, m, n, ii;

  /*******************************
   * Parameters: NW WH(), NE H() *
   *             NW WS(), NE S() *
   *             NW WV(), NE V() *
   *******************************/
  for (ii=0; ii<NT; ii++) for (i=0; i<(3*NP); i++) result[ii][i] = 0.0;

  /**************************************
   * NW W parameters solution are first *
   **************************************/
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    for (ii=0; ii<NS; ii++) {
      for (j=0, m=0; j<NR; j++) {
    	m += NR - j;
    	m += ii;
    	result[ii][     n] +=	      taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j];
    	result[ii][  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j];
#ifndef USE_GHIORSO_KRESS_MODEL
    	result[ii][2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j];
#endif /* USE_GHIORSO_KRESS_MODEL */
	m += NS - ii; 
      }
      result[ii][     n] += 	    taylorCoeff[n+NE+1][1+NR+ii+1];
      result[ii][  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+ii+1];
#ifndef USE_GHIORSO_KRESS_MODEL
      result[ii][2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+ii+1];
#endif /* USE_GHIORSO_KRESS_MODEL */

      for (k=ii; k<NS; k++) {
	m = ii*NS+(k+1)-(ii+1)*(ii+2)/2+(ii+1)-1+NR*(NR-1)/2+NR+NR*NS;
    	result[ii][     n] +=         taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[k];
    	result[ii][  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[k];
#ifndef USE_GHIORSO_KRESS_MODEL
    	result[ii][2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[k];
#endif /* USE_GHIORSO_KRESS_MODEL */
      }
      
      for (j=0; j<=ii; j++) {
	m = j*NS+(ii+1)-(j+1)*(j+2)/2+(j+1)-1+NR*(NR-1)/2+NR+NR*NS;
    	result[ii][     n] +=         taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[j];
    	result[ii][  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[j];
#ifndef USE_GHIORSO_KRESS_MODEL
    	result[ii][2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[j];
#endif /* USE_GHIORSO_KRESS_MODEL */
      }
      
    }
  }

  /**************************************
   * NE standard state terms are second *
   **************************************/
  for (i=0; i<NE; i++, n++) {
    for (ii=0; ii<NS; ii++) {
      result[ii][     n] += 	    taylorCoeff[i+1][1+NR+ii+1];
      result[ii][  NP+n] +=      -t*taylorCoeff[i+1][1+NR+ii+1];
#ifndef USE_GHIORSO_KRESS_MODEL
      result[ii][2*NP+n] += (p-1.0)*taylorCoeff[i+1][1+NR+ii+1];
#endif /* USE_GHIORSO_KRESS_MODEL */
    }
  }
}

static double fillD2GDT2 (double r[NR], double s[NT], double t, double p) {
  double result;
  int i;

  /* Taylor expansion and standard state terms */
  result = CPconst;
  for (i=0; i<NR; i++) result += cpr[i]*r[i];
  for (i=0; i<NS; i++) result += cps[i]*s[i];
  result /= -t;
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double coeffCN;
    double d2gIntIVdt2 = d2IntegralV_GKdT2(r, s, t, p);
  
    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i]; 
    result += coeffCN*d2gIntIVdt2;
  }
#endif /* USE_GHIORSO_KRESS_MODEL */

  return result;
}

static double fillD2GDTDP (double r[NR], double s[NT], double t, double p) {
  double result;
  int i;

  /* Taylor expansion and standard state terms */
  result = DVDTconst;
  for (i=0; i<NR; i++) result += dvdtr[i]*r[i];
  for (i=0; i<NS; i++) result += dvdts[i]*s[i];

#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double coeffCN;
    double d2gIntIVdtdp = d2IntegralV_GKdTdP(r, s, t, p);
  
    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i]; 
    result += coeffCN*d2gIntIVdtdp;
  }  
#endif /* USE_GHIORSO_KRESS_MODEL */

  return result;
}

static void fillD2GDTDW (double r[NR], double s[NT], double t, double p, double *result) {
  int i, j, k, l, m, n;

  /*******************************
   * Parameters: NW WH(), NE H() *
   *             NW WS(), NE S() *
   *             NW WV(), NE V() *
   *******************************/
  for (i=0; i<(3*NP); i++) result[i] = 0.0;

  /**************************************
   * NW W parameters solution are first *
   **************************************/
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    result[NP+n] += -taylorCoeff[n+NE+1][0+1];
    m = 0;
    for (j=0, m=0; j<NR; j++) {
      result[NP+n] += -taylorCoeff[n+NE+1][1+j+1]*r[j];
      for (k=j; k<NR; k++, m++) result[NP+n] += -taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j]*r[k];
      for (k=0; k<NS; k++, m++) result[NP+n] += -taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j]*s[k];
    }
    for (j=0; j<NS; j++) {
      result[NP+n] += -taylorCoeff[n+NE+1][1+NR+j+1]*s[j];
      for (k=j; k<NS; k++, m++) result[NP+n] += -taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[j]*s[k];
    }
  }

  /**************************************
   * NE standard state terms are second *
   **************************************/
  for (i=0; i<NE; i++, n++) {
    result[NP+n] += -taylorCoeff[i+1][0+1];
    for (j=0; j<NR; j++) result[NP+n] += -taylorCoeff[i+1][1+j+1]*r[j];
    for (j=0; j<NS; j++) result[NP+n] += -taylorCoeff[i+1][1+NR+j+1]*s[j];
  }
}

static void fillD2GDPDW (double r[NR], double s[NT], double t, double p, double *result) {
  int i;

  /*******************************
   * Parameters: NW WH(), NE H() *
   *             NW WS(), NE S() *
   *             NW WV(), NE V() *
   *******************************/
  for (i=0; i<(3*NP); i++) result[i] = 0.0;

  /**************************************
   * NW W parameters solution are first *
   **************************************/
#ifndef USE_GHIORSO_KRESS_MODEL
{
  int j, k, l, m, n
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    result[2*NP+n] += taylorCoeff[n+NE+1][0+1];
    m = 0;
    for (j=0, m=0; j<NR; j++) {
      result[2*NP+n] += taylorCoeff[n+NE+1][1+j+1]*r[j];
      for (k=j; k<NR; k++, m++) result[2*NP+n] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j]*r[k];
      for (k=0; k<NS; k++, m++) result[2*NP+n] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j]*s[k];
    }
    for (j=0; j<NS; j++) {
      result[2*NP+n] += taylorCoeff[n+NE+1][1+NR+j+1]*s[j];
      for (k=j; k<NS; k++, m++) result[2*NP+n] += taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[j]*s[k];
    }
  }

  /**************************************
   * NE standard state terms are second *
   **************************************/
  for (i=0; i<NE; i++, n++) {
    result[2*NP+n] += taylorCoeff[i+1][0+1];
    for (j=0; j<NR; j++) result[2*NP+n] += taylorCoeff[i+1][1+j+1]*r[j];
    for (j=0; j<NS; j++) result[2*NP+n] += taylorCoeff[i+1][1+NR+j+1]*s[j];
  }
}
#endif /* USE_GHIORSO_KRESS_MODEL */
}

static double fillD2GDP2 (double r[NR], double s[NT], double t, double p) {
  double result;
  int i;

  /* Taylor expansion and standard state terms */
  result = DVDPconst;
  for (i=0; i<NR; i++) result += dvdpr[i]*r[i];
  for (i=0; i<NS; i++) result += dvdps[i]*s[i];

#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double coeffCN;
    double d2gIntIVdp2 = d2IntegralV_GKdP2(r, s, t, p);
  
    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i]; 
    result += coeffCN*d2gIntIVdp2;
  }
#endif /* USE_GHIORSO_KRESS_MODEL */

  return result;
}

static void fillD3GDR3 (double r[NR], double s[NT], double t, double p, double ***result) {
  int i, j, k, l;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) for (j=0; j<NR; j++) for (k=0; k<NR; k++) result[i][j][k] = 0.0;

  /* Configurational entropy terms */
  for (j=0; j<NR; j++) {
    for (k=j; k<NR; k++) {
      for (l=k; l<NR; l++) {
        double config = 0.0;
        for (i=0; i<NE; i++) if (xSpecies[i] > 0.0 && dxSpeciesdr[i][j] != 0.0 && dxSpeciesdr[i][k] != 0.0 && dxSpeciesdr[i][l] != 0.0) 
          config += -dxSpeciesdr[i][j]*dxSpeciesdr[i][k]*dxSpeciesdr[i][l]/(xSpecies[i]*xSpecies[i]);
        if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0 && dxSpeciesdr[nH2O][j] != 0.0 && dxSpeciesdr[nH2O][k] != 0.0 && dxSpeciesdr[i][l] != 0.0) 
          config += -dxSpeciesdr[nH2O][j]*dxSpeciesdr[nH2O][k]*dxSpeciesdr[nH2O][l]
	            *(1.0/(xSpecies[nH2O]*xSpecies[nH2O]) - 1.0/((1.0-xSpecies[nH2O])*(1.0-xSpecies[nH2O]))); 	  
        result[j][k][l] += R*t*nSpecies*config;
        result[k][j][l]  = result[j][k][l];
        result[l][j][k]  = result[j][k][l];
        result[l][k][j]  = result[j][k][l];
        result[j][l][k]  = result[j][k][l];
        result[k][l][j]  = result[j][k][l];
      }
    }
  }

#ifdef USE_GHIORSO_KRESS_MODEL
  {
    const double pr         = 1.0;
    const double tr         = 1673.15;
    double m[NA], mOx[NA], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum, coeffCN;
    double dvdr[NR], d2vdrdt[NR], dcRefdr[NR], d2cdrdt[NR], dmwdr[NR], dcpdr[NR], d3vdrdp2[NR], d4vdrdp3[NR], d5vdrdp4[NR], dmOxTotdr[NR], denom;
    double d2cRefdr2[NR][NR], d3cdr2dt[NR][NR], d3cRefdr3[NR][NR][NR], d4cdr3dt[NR][NR][NR];

    if (fabs(p-pr) < 10.0*DBL_EPSILON) return;

    /* Convert input composition (r) to liquid moles (m)  */
    for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
    
    /* Compute moles and total moles of oxides */
    for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
    if (mOxTot == 0.0) return;

    for (i=0; i<NR; i++) { 
      dvdr[i]    = 0.0; d2vdrdt[i]  = 0.0; dcRefdr[i]  = 0.0; d2cdrdt[i]  = 0.0; dmwdr[i] = 0.0; 
      dcpdr[i]   = 0.0; d3vdrdp2[i] = 0.0; d4vdrdp3[i] = 0.0; d5vdrdp4[i] = 0.0; 
      for (j=0, dmOxTotdr[i]=0.0; j<nc; j++) dmOxTotdr[i] += (liquid[i+1].liqToOx)[j] - (liquid[0].liqToOx)[j];
      for (j=i; j<NR; j++) { 
        d2cRefdr2[i][j] = 0.0; d3cdr2dt[i][j] = 0.0; 
	for (k=j; k<NR; k++) { d3cRefdr3[i][j][k] = 0.0; d4cdr3dt[i][j][k]  = 0.0; }
      }
    }
    
    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i];
	  
    for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<nc; i++) {
      v       += mOx[i]*bulkSystem[i].gk_v;
      dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
      cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
      dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
      cp      += mOx[i]*bulkSystem[i].gk_cp;
      d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      mw      += mOx[i]*bulkSystem[i].mw;
      
      for (j=0; j<NR; j++) {
        dvdr[j]      += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_v;
        d2vdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dvdt;
        dmwdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].mw;
        dcpdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cp;	
	dcRefdr[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c/mOxTot 
	              - mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot);
        dcRefdr[j]   += (iOxAl2O3 != -1) ? ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
		      - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
	d2cdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt/mOxTot 
	              - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot);
        d3vdrdp2[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
        d4vdrdp3[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
        d5vdrdp4[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      }
      if (iCmpAl2O3 != -1) dcRefdr[iCmpAl2O3] += ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);
      
      for (j=0; j<NR; j++) {
	for (k=j; k<NR; k++) {
	  d2cRefdr2[j][k] += -((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c*dmOxTotdr[k]/(mOxTot*mOxTot) 	  
	  		   - ((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot)
			   + 2.0*mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot);
	  d2cRefdr2[j][k] += (iOxAl2O3 != -1) ?
	  		   - 2.0*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot)
	  		   - 2.0*((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot)
			   + 6.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot*mOxTot) : 0.0;
			   
	  d3cdr2dt[j][k]  += -((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt*dmOxTotdr[k]/(mOxTot*mOxTot) 
	  		   - ((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot)
			   + 2.0*mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot);
	}
	if (iCmpAl2O3 != -1) d2cRefdr2[(j<iCmpAl2O3) ? j : iCmpAl2O3][(j>iCmpAl2O3) ? j : iCmpAl2O3] +=
	  ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
	  - 2.0*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot);
      }
      if (iCmpAl2O3 != -1) d2cRefdr2[iCmpAl2O3][iCmpAl2O3] +=
	((liquid[iCmpAl2O3+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
	- 2.0*mOx[i]*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[iCmpAl2O3]/(mOxTot*mOxTot*mOxTot);

      for (j=0; j<NR; j++) {
	for (k=j; k<NR; k++) {
	  for (l=k; l<NR; l++) {
	    d3cRefdr3[j][k][l] += 2.0*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c*dmOxTotdr[k]*dmOxTotdr[l]/(mOxTot*mOxTot*mOxTot) 
	  		    	+ 2.0*((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c*dmOxTotdr[j]*dmOxTotdr[l]/(mOxTot*mOxTot*mOxTot)
			    	+ 2.0*((liquid[l+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot)
			    	- 6.0*mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]*dmOxTotdr[k]*dmOxTotdr[l]/(mOxTot*mOxTot*mOxTot*mOxTot);
	    d3cRefdr3[j][k][l] += (iOxAl2O3 != -1) ?
	  		    	+ 6.0*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[k]*dmOxTotdr[l]/(mOxTot*mOxTot*mOxTot*mOxTot)
	  		    	+ 6.0*((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]*dmOxTotdr[l]/(mOxTot*mOxTot*mOxTot*mOxTot)
			    	+ 6.0*((liquid[l+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot*mOxTot)
			    	- 24.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]*dmOxTotdr[k]*dmOxTotdr[l]/(mOxTot*mOxTot*mOxTot*mOxTot*mOxTot) : 0.0;
	    		    	
	    d4cdr3dt[j][k][l] += 2.0*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt*dmOxTotdr[k]*dmOxTotdr[l]/(mOxTot*mOxTot*mOxTot) 
	  		       + 2.0*((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt*dmOxTotdr[j]*dmOxTotdr[l]/(mOxTot*mOxTot*mOxTot)
			       + 2.0*((liquid[l+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot)
			       - 6.0*mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]*dmOxTotdr[k]*dmOxTotdr[l]/(mOxTot*mOxTot*mOxTot*mOxTot);
	  }
	  /* case for j || k || l == iCmpAl2O3 */
	  if (iCmpAl2O3 != -1) d3cRefdr3[(j<iCmpAl2O3) ? j : iCmpAl2O3][(j>iCmpAl2O3) ? j : ((k<iCmpAl2O3) ? k : iCmpAl2O3)][(k>iCmpAl2O3) ? k : iCmpAl2O3] += 
	    - 2.0*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot)
	    - 2.0*((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot)
	    + 6.0*mOx[i]*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot*mOxTot);
	}
	/* case for j,k || j,l || k,l == iCmpAl2O3 */
	if (iCmpAl2O3 != -1) d3cRefdr3[(j<iCmpAl2O3) ? j : iCmpAl2O3][iCmpAl2O3][(j>iCmpAl2O3) ? j : iCmpAl2O3] += 
	  - 2.0*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[iCmpAl2O3]/(mOxTot*mOxTot*mOxTot)
	  - 2.0*((liquid[iCmpAl2O3+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot)
	  + 6.0*mOx[i]*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]*dmOxTotdr[iCmpAl2O3]/(mOxTot*mOxTot*mOxTot*mOxTot);
      }
      /* Case for j,k,l == iCmpAl2O3*/
      if (iCmpAl2O3 != -1) d3cRefdr3[iCmpAl2O3][iCmpAl2O3][iCmpAl2O3] += 
	- 2.0*((liquid[iCmpAl2O3+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[iCmpAl2O3]/(mOxTot*mOxTot*mOxTot)
	- 2.0*((liquid[iCmpAl2O3+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[iCmpAl2O3]/(mOxTot*mOxTot*mOxTot)
	+ 6.0*mOx[i]*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[iCmpAl2O3]*dmOxTotdr[iCmpAl2O3]/(mOxTot*mOxTot*mOxTot*mOxTot);
    }
    if (v == 0.0) return;

    alpha   = dvdt/v;
    v0      = v*exp(alpha*(t-tr));
    v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
    c       = cRef + (t-tr)*dcdt;
    v1      = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
    v2      = d2vdp2;
    denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
    a	    = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
    b	    = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
    sum     = a*a - 4.0*b;

    for (i=0; i<NR; i++) {
      double dalphadri   = d2vdrdt[i]/v - dvdt*dvdr[i]/(v*v);
      double dv0dri      = (dvdr[i] + v*dalphadri*(t-tr))*exp(alpha*(t-tr));      
      double dv1Refdri   = -2.0*v*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
                           -v*v*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
			         + 2.0*tr*alpha*dalphadri/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp));   
      double dcdri       = dcRefdr[i] + (t-tr)*d2cdrdt[i];
      double dv1dri      = -2.0*v0*dv0dri*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                           -v0*v0*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c) 
			           + 2.0*t*alpha*dalphadri/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp));      
      double ddenomdri   = 2.0*dv1Refdri*d3vdp3+2.0*v1Ref*d4vdrdp3[i]-6.0*d2vdp2*d3vdrdp2[i]; 
      double dadri       = (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdri*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)/denom
                         - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdri;
      double dbdri       = (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/denom
                         - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdri;			

      for (j=i; j<NR; j++) {
        double dalphadrj   = d2vdrdt[j]/v - dvdt*dvdr[j]/(v*v);
        double dv0drj	   = (dvdr[j] + v*dalphadrj*(t-tr))*exp(alpha*(t-tr));      
        double dv1Refdrj   = -2.0*v*dvdr[j]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
        		     -v*v*(- 1000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])/(mw*mw*cRef*cRef*cRef) 
        			   + 2.0*tr*alpha*dalphadrj/(cp) - tr*alpha*alpha*dcpdr[j]/(cp*cp));   
        double dcdrj	   = dcRefdr[j] + (t-tr)*d2cdrdt[j];
        double dv1drj	   = -2.0*v0*dv0drj*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
        		     -v0*v0*(- 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c) 
        			     + 2.0*t*alpha*dalphadrj/(cp) - t*alpha*alpha*dcpdr[j]/(cp*cp));      
        double ddenomdrj   = 2.0*dv1Refdrj*d3vdp3+2.0*v1Ref*d4vdrdp3[j]-6.0*d2vdp2*d3vdrdp2[j]; 
        double dadrj	   = (d3vdrdp2[j]*d3vdp3+d2vdp2*d4vdrdp3[j]-dv1Refdrj*d4vdp4/2.0-v1Ref*d5vdrdp4[j]/2.0)/denom
        		   - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdrj;
        double dbdrj	   = (d3vdrdp2[j]*d4vdp4/4.0+d2vdp2*d5vdrdp4[j]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[j])/denom
                         - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdrj;			

        double d2alphadridrj = -d2vdrdt[i]*dvdr[j]/(v*v)-d2vdrdt[j]*dvdr[i]/(v*v)+2.0*dvdt*dvdr[i]*dvdr[j]/(v*v*v);
        double d2v0dridrj    = dvdr[i]*dalphadrj*(t-tr)*exp(alpha*(t-tr))
			     + dvdr[j]*dalphadri*(t-tr)*exp(alpha*(t-tr))
			     + v*d2alphadridrj*(t-tr)*exp(alpha*(t-tr))
			     + v*dalphadri*pow(t-tr,2.0)*dalphadrj*exp(alpha*(t-tr));
        double d2v1Refdridrj = -2.0*dvdr[j]*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
	                     - 2.0*v*dvdr[i]*(- 1000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])/(mw*mw*cRef*cRef*cRef) 
			                      + 2.0*tr*alpha*dalphadrj/(cp) - tr*alpha*alpha*dcpdr[j]/(cp*cp))
        		     - 2.0*v*dvdr[j]*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
        			              + 2.0*tr*alpha*dalphadri/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp))
			     - v*v*(- 1000.0*(dcRefdr[j]*dmwdr[i]+2.0*dmwdr[j]*dcRefdr[i]+2.0*mw*d2cRefdr2[i][j])/(mw*mw*cRef*cRef*cRef)
			           + 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])*(2.0*dmwdr[j]*cRef+3.0*mw*dcRefdr[j])/(mw*mw*mw*cRef*cRef*cRef*cRef) 
			           + 2.0*tr*alpha*d2alphadridrj/(cp)
				   + 2.0*tr*dalphadrj*dalphadri/(cp) - 2.0*tr*alpha*dalphadri*dcpdr[j]/(cp*cp) 
				   - 2.0*tr*alpha*dalphadrj*dcpdr[i]/(cp*cp) + 2.0*tr*alpha*alpha*dcpdr[i]*dcpdr[j]/(cp*cp*cp)); 
        double d2cdridrj	   = d2cRefdr2[i][j] + (t-tr)*d3cdr2dt[i][j];
        double d2v1dridrj	   = -2.0*dv0drj*dv0dri*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
	                    - 2.0*v0*d2v0dridrj*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
	                    - 2.0*v0*dv0dri*(- 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c) 
			                     + 2.0*t*alpha*dalphadrj/(cp) - t*alpha*alpha*dcpdr[j]/(cp*cp))
        		    - 2.0*v0*dv0drj*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c) 
        			             + 2.0*t*alpha*dalphadri/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp))
			     -v0*v0*(- 1000.0*(dcdrj*dmwdr[i]+2.0*dmwdr[j]*dcdri+2.0*mw*d2cdridrj)/(mw*mw*c*c*c)
			             + 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)*(2.0*dmwdr[j]*c+3.0*mw*dcdrj)/(mw*mw*mw*c*c*c*c) 
				     + 2.0*t*alpha*d2alphadridrj/(cp)
			             + 2.0*t*dalphadrj*dalphadri/(cp) - 2.0*t*alpha*dalphadri*dcpdr[j]/(cp*cp) 
				     - 2.0*t*alpha*dalphadrj*dcpdr[i]/(cp*cp) + 2.0*t*alpha*alpha*dcpdr[i]*dcpdr[j]/(cp*cp*cp));   
        double d2denomdridrj   = 2.0*d2v1Refdridrj*d3vdp3 + 2.0*dv1Refdri*d4vdrdp3[j] + 2.0*dv1Refdrj*d4vdrdp3[i] - 6.0*d3vdrdp2[j]*d3vdrdp2[i]; 
        double d2adridrj	   = (d3vdrdp2[i]*d4vdrdp3[j]+d3vdrdp2[j]*d4vdrdp3[i]-d2v1Refdridrj*d4vdp4/2.0-dv1Refdri*d5vdrdp4[j]/2.0-dv1Refdrj*d5vdrdp4[i]/2.0)/denom
	                   - (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdri*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)*ddenomdrj/(denom*denom)
        		   - (d3vdrdp2[j]*d3vdp3+d2vdp2*d4vdrdp3[j]-dv1Refdrj*d4vdp4/2.0-v1Ref*d5vdrdp4[j]/2.0)*ddenomdri/(denom*denom)
                           + 2.0*(d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*ddenomdri*ddenomdrj/(denom*denom*denom)
                           - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*d2denomdridrj/(denom*denom);
        double d2bdridrj	   = (d3vdrdp2[i]*d5vdrdp4[j]/4.0+d3vdrdp2[j]*d5vdrdp4[i]/4.0-2.0/3.0*d4vdrdp3[j]*d4vdrdp3[i])/denom
                           - (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])*ddenomdrj/(denom*denom)
        		   - (d3vdrdp2[j]*d4vdp4/4.0+d2vdp2*d5vdrdp4[j]/4.0-2.0*d4vdrdp3[j]*d3vdp3/3.0)*ddenomdri/(denom*denom)
			   + 2.0*(d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*ddenomdri*ddenomdrj/(denom*denom*denom)
			   - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*d2denomdridrj/(denom*denom);			  

        for (k=j; k<NR; k++) {
          double dalphadrk   = d2vdrdt[k]/v - dvdt*dvdr[k]/(v*v);
          double dv0drk      = (dvdr[k] + v*dalphadrk*(t-tr))*exp(alpha*(t-tr));      
          double dv1Refdrk   = -2.0*v*dvdr[k]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
         		       -v*v*(- 1000.0*(cRef*dmwdr[k]+2.0*mw*dcRefdr[k])/(mw*mw*cRef*cRef*cRef) 
         			     + 2.0*tr*alpha*dalphadrk/(cp) - tr*alpha*alpha*dcpdr[k]/(cp*cp));   
          double dcdrk       = dcRefdr[k] + (t-tr)*d2cdrdt[k];
          double dv1drk      = -2.0*v0*dv0drk*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
         		       -v0*v0*(- 1000.0*(c*dmwdr[k]+2.0*mw*dcdrk)/(mw*mw*c*c*c) 
         			       + 2.0*t*alpha*dalphadrk/(cp) - t*alpha*alpha*dcpdr[k]/(cp*cp));      
          double ddenomdrk   = 2.0*dv1Refdrk*d3vdp3+2.0*v1Ref*d4vdrdp3[k]-6.0*d2vdp2*d3vdrdp2[k]; 
          double dadrk       = (d3vdrdp2[k]*d3vdp3+d2vdp2*d4vdrdp3[k]-dv1Refdrk*d4vdp4/2.0-v1Ref*d5vdrdp4[k]/2.0)/denom
         		     - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdrk;
          double dbdrk       = (d3vdrdp2[k]*d4vdp4/4.0+d2vdp2*d5vdrdp4[k]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[k])/denom
                             - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdrk;			

          double d2alphadridrk = -d2vdrdt[i]*dvdr[k]/(v*v)-d2vdrdt[k]*dvdr[i]/(v*v)+2.0*dvdt*dvdr[i]*dvdr[k]/(v*v*v);
          double d2v0dridrk    = dvdr[i]*dalphadrk*(t-tr)*exp(alpha*(t-tr))
	 		       + dvdr[k]*dalphadri*(t-tr)*exp(alpha*(t-tr))
	 		       + v*d2alphadridrk*(t-tr)*exp(alpha*(t-tr))
	 		       + v*dalphadri*pow(t-tr,2.0)*dalphadrk*exp(alpha*(t-tr));
          double d2v1Refdridrk = -2.0*dvdr[k]*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
	 		       - 2.0*v*dvdr[i]*(- 1000.0*(cRef*dmwdr[k]+2.0*mw*dcRefdr[k])/(mw*mw*cRef*cRef*cRef) 
	 					+ 2.0*tr*alpha*dalphadrk/(cp) - tr*alpha*alpha*dcpdr[k]/(cp*cp))
         		       - 2.0*v*dvdr[k]*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
         					+ 2.0*tr*alpha*dalphadri/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp))
	 		       - v*v*(- 1000.0*(dcRefdr[k]*dmwdr[i]+2.0*dmwdr[k]*dcRefdr[i]+2.0*mw*d2cRefdr2[i][k])/(mw*mw*cRef*cRef*cRef)
	 			      + 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])*(2.0*dmwdr[k]*cRef+3.0*mw*dcRefdr[k])/(mw*mw*mw*cRef*cRef*cRef*cRef) 
	 			      + 2.0*tr*alpha*d2alphadridrk/(cp)
	 			      + 2.0*tr*dalphadrk*dalphadri/(cp) - 2.0*tr*alpha*dalphadri*dcpdr[k]/(cp*cp) 
	 			      - 2.0*tr*alpha*dalphadrk*dcpdr[i]/(cp*cp) + 2.0*tr*alpha*alpha*dcpdr[i]*dcpdr[k]/(cp*cp*cp)); 
          double d2cdridrk	      = d2cRefdr2[i][k] + (t-tr)*d3cdr2dt[i][k];
          double d2v1dridrk	      = -2.0*dv0drk*dv0dri*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
	 		      - 2.0*v0*d2v0dridrk*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
	 		      - 2.0*v0*dv0dri*(- 1000.0*(c*dmwdr[k]+2.0*mw*dcdrk)/(mw*mw*c*c*c) 
	 				       + 2.0*t*alpha*dalphadrk/(cp) - t*alpha*alpha*dcpdr[k]/(cp*cp))
         		      - 2.0*v0*dv0drk*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c) 
         				       + 2.0*t*alpha*dalphadri/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp))
	 		       -v0*v0*(- 1000.0*(dcdrk*dmwdr[i]+2.0*dmwdr[k]*dcdri+2.0*mw*d2cdridrk)/(mw*mw*c*c*c)
	 			       + 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)*(2.0*dmwdr[k]*c+3.0*mw*dcdrk)/(mw*mw*mw*c*c*c*c) 
	 			       + 2.0*t*alpha*d2alphadridrk/(cp)
	 			       + 2.0*t*dalphadrk*dalphadri/(cp) - 2.0*t*alpha*dalphadri*dcpdr[k]/(cp*cp) 
	 			       - 2.0*t*alpha*dalphadrk*dcpdr[i]/(cp*cp) + 2.0*t*alpha*alpha*dcpdr[i]*dcpdr[k]/(cp*cp*cp));   
          double d2denomdridrk = 2.0*d2v1Refdridrk*d3vdp3 + 2.0*dv1Refdri*d4vdrdp3[k] + 2.0*dv1Refdrk*d4vdrdp3[i] - 6.0*d3vdrdp2[k]*d3vdrdp2[i]; 
          double d2adridrk     = (d3vdrdp2[i]*d4vdrdp3[k]+d3vdrdp2[k]*d4vdrdp3[i]-d2v1Refdridrk*d4vdp4/2.0-dv1Refdri*d5vdrdp4[k]/2.0-dv1Refdrk*d5vdrdp4[i]/2.0)/denom
	 		       - (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdri*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)*ddenomdrk/(denom*denom)
         		       - (d3vdrdp2[k]*d3vdp3+d2vdp2*d4vdrdp3[k]-dv1Refdrk*d4vdp4/2.0-v1Ref*d5vdrdp4[k]/2.0)*ddenomdri/(denom*denom)
         		       + 2.0*(d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*ddenomdri*ddenomdrk/(denom*denom*denom)
         		       - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*d2denomdridrk/(denom*denom);
          double d2bdridrk     = (d3vdrdp2[i]*d5vdrdp4[k]/4.0+d3vdrdp2[k]*d5vdrdp4[i]/4.0-2.0/3.0*d4vdrdp3[k]*d4vdrdp3[i])/denom
         		       - (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])*ddenomdrk/(denom*denom)
         		       - (d3vdrdp2[k]*d4vdp4/4.0+d2vdp2*d5vdrdp4[k]/4.0-2.0*d4vdrdp3[k]*d3vdp3/3.0)*ddenomdri/(denom*denom)
	 		       + 2.0*(d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*ddenomdri*ddenomdrk/(denom*denom*denom)
	 		       - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*d2denomdridrk/(denom*denom);		      
			      
          double d2alphadrjdrk = -d2vdrdt[j]*dvdr[k]/(v*v)-d2vdrdt[k]*dvdr[j]/(v*v)+2.0*dvdt*dvdr[j]*dvdr[k]/(v*v*v);
          double d2v0drjdrk    = dvdr[j]*dalphadrk*(t-tr)*exp(alpha*(t-tr))
	 		       + dvdr[k]*dalphadrj*(t-tr)*exp(alpha*(t-tr))
	 		       + v*d2alphadrjdrk*(t-tr)*exp(alpha*(t-tr))
	 		       + v*dalphadrj*pow(t-tr,2.0)*dalphadrk*exp(alpha*(t-tr));
          double d2v1Refdrjdrk = -2.0*dvdr[k]*dvdr[j]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
	 		       - 2.0*v*dvdr[j]*(- 1000.0*(cRef*dmwdr[k]+2.0*mw*dcRefdr[k])/(mw*mw*cRef*cRef*cRef) 
	 					+ 2.0*tr*alpha*dalphadrk/(cp) - tr*alpha*alpha*dcpdr[k]/(cp*cp))
         		       - 2.0*v*dvdr[k]*(- 1000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])/(mw*mw*cRef*cRef*cRef) 
         					+ 2.0*tr*alpha*dalphadrj/(cp) - tr*alpha*alpha*dcpdr[j]/(cp*cp))
	 		       - v*v*(- 1000.0*(dcRefdr[k]*dmwdr[j]+2.0*dmwdr[k]*dcRefdr[j]+2.0*mw*d2cRefdr2[j][k])/(mw*mw*cRef*cRef*cRef)
	 			      + 1000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])*(2.0*dmwdr[k]*cRef+3.0*mw*dcRefdr[k])/(mw*mw*mw*cRef*cRef*cRef*cRef) 
	 			      + 2.0*tr*alpha*d2alphadrjdrk/(cp)
	 			      + 2.0*tr*dalphadrk*dalphadrj/(cp) - 2.0*tr*alpha*dalphadrj*dcpdr[k]/(cp*cp) 
	 			      - 2.0*tr*alpha*dalphadrk*dcpdr[j]/(cp*cp) + 2.0*tr*alpha*alpha*dcpdr[j]*dcpdr[k]/(cp*cp*cp)); 
          double d2cdrjdrk     = d2cRefdr2[j][k] + (t-tr)*d3cdr2dt[j][k];
          double d2v1drjdrk    = -2.0*dv0drk*dv0drj*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
	 		       - 2.0*v0*d2v0drjdrk*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
	 		       - 2.0*v0*dv0drj*(- 1000.0*(c*dmwdr[k]+2.0*mw*dcdrk)/(mw*mw*c*c*c) 
	 			 	        + 2.0*t*alpha*dalphadrk/(cp) - t*alpha*alpha*dcpdr[k]/(cp*cp))
         		       - 2.0*v0*dv0drk*(- 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c) 
         				        + 2.0*t*alpha*dalphadrj/(cp) - t*alpha*alpha*dcpdr[j]/(cp*cp))
	 		       -v0*v0*(- 1000.0*(dcdrk*dmwdr[j]+2.0*dmwdr[k]*dcdrj+2.0*mw*d2cdrjdrk)/(mw*mw*c*c*c)
	 			       + 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)*(2.0*dmwdr[k]*c+3.0*mw*dcdrk)/(mw*mw*mw*c*c*c*c) 
	 			       + 2.0*t*alpha*d2alphadrjdrk/(cp)
	 			       + 2.0*t*dalphadrk*dalphadrj/(cp) - 2.0*t*alpha*dalphadrj*dcpdr[k]/(cp*cp) 
	 			       - 2.0*t*alpha*dalphadrk*dcpdr[j]/(cp*cp) + 2.0*t*alpha*alpha*dcpdr[j]*dcpdr[k]/(cp*cp*cp));   
          double d2denomdrjdrk = 2.0*d2v1Refdrjdrk*d3vdp3 + 2.0*dv1Refdrj*d4vdrdp3[k] + 2.0*dv1Refdrk*d4vdrdp3[j] - 6.0*d3vdrdp2[k]*d3vdrdp2[j]; 
          double d2adrjdrk     = (d3vdrdp2[j]*d4vdrdp3[k]+d3vdrdp2[k]*d4vdrdp3[j]-d2v1Refdrjdrk*d4vdp4/2.0-dv1Refdrj*d5vdrdp4[k]/2.0-dv1Refdrk*d5vdrdp4[j]/2.0)/denom
	 		       - (d3vdrdp2[j]*d3vdp3+d2vdp2*d4vdrdp3[j]-dv1Refdrj*d4vdp4/2.0-v1Ref*d5vdrdp4[j]/2.0)*ddenomdrk/(denom*denom)
         		       - (d3vdrdp2[k]*d3vdp3+d2vdp2*d4vdrdp3[k]-dv1Refdrk*d4vdp4/2.0-v1Ref*d5vdrdp4[k]/2.0)*ddenomdrj/(denom*denom)
         		       + 2.0*(d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*ddenomdrj*ddenomdrk/(denom*denom*denom)
         		       - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*d2denomdrjdrk/(denom*denom);
          double d2bdrjdrk     = (d3vdrdp2[j]*d5vdrdp4[k]/4.0+d3vdrdp2[k]*d5vdrdp4[j]/4.0-2.0/3.0*d4vdrdp3[k]*d4vdrdp3[j])/denom
         		       - (d3vdrdp2[j]*d4vdp4/4.0+d2vdp2*d5vdrdp4[j]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[j])*ddenomdrk/(denom*denom)
         		       - (d3vdrdp2[k]*d4vdp4/4.0+d2vdp2*d5vdrdp4[k]/4.0-2.0*d4vdrdp3[k]*d3vdp3/3.0)*ddenomdrj/(denom*denom)
	 		       + 2.0*(d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*ddenomdrj*ddenomdrk/(denom*denom*denom)
	 		       - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*d2denomdrjdrk/(denom*denom);		      
			      
			      
          double d3alphadr3 = 2.0*d2vdrdt[i]/(v*v*v)*dvdr[j]*dvdr[k]
        		    + 2.0*d2vdrdt[j]/(v*v*v)*dvdr[i]*dvdr[k]
        		    + 2.0*d2vdrdt[k]/(v*v*v)*dvdr[i]*dvdr[j]
        		    - 6.0*dvdt/(v*v*v*v)*dvdr[i]*dvdr[j]*dvdr[k];
          double d3v0dr3 = dvdr[i]*d2alphadrjdrk*(t-tr)*exp(alpha*(t-tr))
        		 + dvdr[i]*dalphadrj*pow(t-tr,2.0)*dalphadrk*exp(alpha*(t-tr))
        		 + dvdr[j]*d2alphadridrk*(t-tr)*exp(alpha*(t-tr))
        		 + dvdr[j]*dalphadri*pow(t-tr,2.0)*dalphadrk*exp(alpha*(t-tr))
        		 + dvdr[k]*d2alphadridrj*(t-tr)*exp(alpha*(t-tr))
        		 + v*d3alphadr3*(t-tr)*exp(alpha*(t-tr))
        		 + v*d2alphadridrj*pow(t-tr,2.0)*dalphadrk*exp(alpha*(t-tr))
        		 + dvdr[k]*dalphadri*pow(t-tr,2.0)*dalphadrj*exp(alpha*(t-tr))
        		 + v*d2alphadridrk*pow(t-tr,2.0)*dalphadrj*exp(alpha*(t-tr))
        		 + v*dalphadri*pow(t-tr,2.0)*d2alphadrjdrk*exp(alpha*(t-tr))
        		 + v*dalphadri*pow(t-tr,3.0)*dalphadrj*dalphadrk*exp(alpha*(t-tr));
	  double d3v1Refdr3 = -2.0*dvdr[j]*dvdr[i]*(-1000.0*dmwdr[k]/(mw*mw*cRef*cRef) - 2000.0*dcRefdr[k]/(mw*cRef*cRef*cRef) + 2.0*tr*alpha*dalphadrk/(cp))
	                     - 2.0*dvdr[k]*dvdr[i]*(- 1000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])/(mw*mw*cRef*cRef*cRef) 
			                            + 2.0*tr*alpha*dalphadrj/(cp) - tr*alpha*alpha*dcpdr[j]/(cp*cp))
			     - 2.0*v*dvdr[i]*(- 1000.0*(dcRefdr[k]*dmwdr[j]+2.0*dmwdr[k]*dcRefdr[j]+2.0*mw*d2cRefdr2[j][k])/(mw*mw*cRef*cRef*cRef)
			                      + 2000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])*dmwdr[k]/(mw*mw*mw*cRef*cRef*cRef) 
			                      + 3000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])*dcRefdr[k]/(mw*mw*cRef*cRef*cRef*cRef)
			                      + 2.0*tr*dalphadrk*dalphadrj/(cp) 
					      + 2.0*tr*alpha*d2alphadrjdrk/(cp) 
					      - 2.0*tr*alpha*dalphadrj*dcpdr[k]/(cp*cp)
					      - tr*2.0*alpha*dalphadrk*dcpdr[j]/(cp*cp) 
					      + 2.0*tr*alpha*alpha*dcpdr[j]*dcpdr[k]/(cp*cp*cp)
					     )
        		     - 2.0*dvdr[k]*dvdr[j]*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
			                            + 2.0*tr*alpha*dalphadri/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp))
			     - 2.0*v*dvdr[j]*(- 1000.0*(dcRefdr[k]*dmwdr[i]+2.0*dmwdr[k]*dcRefdr[i]+2.0*mw*d2cRefdr2[i][k])/(mw*mw*cRef*cRef*cRef)
			                      + 2000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])*dmwdr[k]/(mw*mw*mw*cRef*cRef*cRef)
			                      + 3000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])*dcRefdr[k]/(mw*mw*cRef*cRef*cRef*cRef)
			                      + 2.0*tr*dalphadrk*dalphadri/(cp) 
					      + 2.0*tr*alpha*d2alphadridrk/(cp) 
					      - 2.0*tr*alpha*dalphadri*dcpdr[k]/(cp*cp)
					      - tr*2.0*alpha*dalphadrk*dcpdr[i]/(cp*cp) 
					      + 2.0*tr*alpha*alpha*dcpdr[i]*dcpdr[k]/(cp*cp*cp)
					     )
			     - 2.0*v*dvdr[k]*(- 1000.0*(dcRefdr[j]*dmwdr[i]+2.0*dmwdr[j]*dcRefdr[i]+2.0*mw*d2cRefdr2[i][j])/(mw*mw*cRef*cRef*cRef)
			            	      + 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])*(2.0*dmwdr[j]*cRef+3.0*mw*dcRefdr[j])/(mw*mw*mw*cRef*cRef*cRef*cRef) 
			            	      + 2.0*tr*alpha*d2alphadridrj/(cp)
				    	      + 2.0*tr*dalphadrj*dalphadri/(cp) 
				    	      - 2.0*tr*alpha*dalphadri*dcpdr[j]/(cp*cp) 
				    	      - 2.0*tr*alpha*dalphadrj*dcpdr[i]/(cp*cp) 
				    	      + 2.0*tr*alpha*alpha*dcpdr[i]*dcpdr[j]/(cp*cp*cp)
				    	     )
			      - v*v*(- 1000.0*(d2cRefdr2[j][k]*dmwdr[i]+2.0*dmwdr[j]*d2cRefdr2[i][k]+2.0*dmwdr[k]*d2cRefdr2[i][j]+2.0*mw*d3cRefdr3[i][j][k])/(mw*mw*cRef*cRef*cRef)
			             + 2000.0*(dcRefdr[j]*dmwdr[i]+2.0*dmwdr[j]*dcRefdr[i]+2.0*mw*d2cRefdr2[i][j])*dmwdr[k]/(mw*mw*mw*cRef*cRef*cRef)
			             + 3000.0*(dcRefdr[j]*dmwdr[i]+2.0*dmwdr[j]*dcRefdr[i]+2.0*mw*d2cRefdr2[i][j])*dcRefdr[k]/(mw*mw*cRef*cRef*cRef*cRef)
			             + 1000.0*(dcRefdr[k]*dmwdr[i]+2.0*dmwdr[k]*dcRefdr[i]+2.0*mw*d2cRefdr2[i][k])*(2.0*dmwdr[j]*cRef+3.0*mw*dcRefdr[j])/(mw*mw*mw*cRef*cRef*cRef*cRef)
				     + 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])*(2.0*dmwdr[j]*dcRefdr[k]+3.0*dmwdr[k]*dcRefdr[j]+3.0*mw*d2cRefdr2[j][k])/(mw*mw*mw*cRef*cRef*cRef*cRef)
				     - 3000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])*(2.0*dmwdr[j]*cRef+3.0*mw*dcRefdr[j])*dmwdr[k]/(mw*mw*mw*mw*cRef*cRef*cRef*cRef)
				     - 4000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])*(2.0*dmwdr[j]*cRef+3.0*mw*dcRefdr[j])*dcRefdr[k]/(mw*mw*mw*cRef*cRef*cRef*cRef*cRef) 
			             + 2.0*tr*dalphadrk*d2alphadridrj/(cp) + 2.0*tr*alpha*d3alphadr3/(cp) - 2.0*tr*alpha*d2alphadridrj*dcpdr[k]/(cp*cp)
				     + 2.0*tr*d2alphadrjdrk*dalphadri/(cp) + 2.0*tr*dalphadrj*d2alphadridrk/(cp) - 2.0*tr*dalphadrj*dalphadri*dcpdr[k]/(cp*cp)
				     - 2.0*tr*dalphadrk*dalphadri*dcpdr[j]/(cp*cp) - 2.0*tr*alpha*d2alphadridrk*dcpdr[j]/(cp*cp) + 4.0*tr*alpha*dalphadri*dcpdr[j]*dcpdr[k]/(cp*cp*cp)
				     - 2.0*tr*dalphadrk*dalphadrj*dcpdr[i]/(cp*cp) - 2.0*tr*alpha*d2alphadrjdrk*dcpdr[i]/(cp*cp) + 4.0*tr*alpha*dalphadrj*dcpdr[i]*dcpdr[k]/(cp*cp*cp)
				     + 4.0*tr*alpha*dalphadrk*dcpdr[i]*dcpdr[j]/(cp*cp*cp) - 6.0*tr*alpha*alpha*dcpdr[i]*dcpdr[j]*dcpdr[k]/(cp*cp*cp*cp) 
				    );
	  double d3cdr3     = d3cRefdr3[i][j][k] + (t-tr)*d4cdr3dt[i][j][k];
          double d3v1dr3    = - 2.0*(d2v0drjdrk*dv0dri + dv0drj*d2v0dridrk)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
	                      - 2.0*dv0drj*dv0dri*(- 1000.0*dmwdr[k]/(mw*mw*c*c) - 2000.0*dcdrk/(mw*c*c*c) + t*2.0*alpha*dalphadrk/(cp) - t*alpha*alpha*dcpdr[k]/(cp*cp))
	                      - 2.0*(dv0drk*d2v0dridrj + v0*d3v0dr3)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
			      - 2.0*v0*d2v0dridrj*(- 1000.0*dmwdr[k]/(mw*mw*c*c) - 2000.0*dcdrk/(mw*c*c*c) + 2.0*t*alpha*dalphadrk/(cp) - t*alpha*alpha*dcpdr[k]/(cp*cp))
	                      - 2.0*(dv0drk*dv0dri + v0*d2v0dridrk)*(- 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c) 
			                                             + 2.0*t*alpha*dalphadrj/(cp) 
					                             - t*alpha*alpha*dcpdr[j]/(cp*cp)
					                            )
			      - 2.0*v0*dv0dri*(- 1000.0*(dcdrk*dmwdr[j]+2.0*dmwdr[k]*dcdrj+2.0*mw*d2cdrjdrk)/(mw*mw*c*c*c) 
			                       + 2000.0*(c*dmwdr[j]+2.0*mw*dcdrj)*dmwdr[k]/(mw*mw*mw*c*c*c) 
					       + 3000.0*(c*dmwdr[j]+2.0*mw*dcdrj)*dcdrk/(mw*mw*c*c*c*c)
			                       + 2.0*t*(dalphadrk*dalphadrj + alpha*d2alphadrjdrk)/(cp) - 2.0*t*alpha*dalphadrj*dcpdr[k]/(cp*cp)
					       - 2.0*t*alpha*dalphadrk*dcpdr[j]/(cp*cp) + 2.0*t*alpha*alpha*dcpdr[j]*dcpdr[k]/(cp*cp*cp)
					      )
        		      - 2.0*(dv0drk*dv0drj + v0*d2v0drjdrk)*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c) 
        			                                     + 2.0*t*alpha*dalphadri/(cp) 
					                             - t*alpha*alpha*dcpdr[i]/(cp*cp)
					                            )
			      - 2.0*v0*dv0drj*(- 1000.0*(dcdrk*dmwdr[i]+2.0*dmwdr[k]*dcdri+2.0*mw*d2cdridrk)/(mw*mw*c*c*c) 
			                       + 2000.0*(c*dmwdr[i]+2.0*mw*dcdri)*dmwdr[k]/(mw*mw*mw*c*c*c) 
					       + 3000.0*(c*dmwdr[i]+2.0*mw*dcdri)*dcdrk/(mw*mw*c*c*c*c)
        			               + 2.0*t*(dalphadrk*dalphadri + alpha*d2alphadridrk)/(cp) - 2.0*t*alpha*dalphadri*dcpdr[k]/(cp*cp)
					       - 2.0*t*alpha*dalphadrk*dcpdr[i]/(cp*cp) + 2.0*t*alpha*alpha*dcpdr[i]*dcpdr[k]/(cp*cp*cp)
					      )
			      - 2.0*v0*dv0drk*(- 1000.0*(dcdrj*dmwdr[i]+2.0*dmwdr[j]*dcdri+2.0*mw*d2cdridrj)/(mw*mw*c*c*c)
			        	       + 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)*(2.0*dmwdr[j]*c+3.0*mw*dcdrj)/(mw*mw*mw*c*c*c*c) 
			        	       + 2.0*t*alpha*d2alphadridrj/(cp)
			        	       + 2.0*t*dalphadrj*dalphadri/(cp) - 2.0*t*alpha*dalphadri*dcpdr[j]/(cp*cp) 
			        	       - 2.0*t*alpha*dalphadrj*dcpdr[i]/(cp*cp) + 2.0*t*alpha*alpha*dcpdr[i]*dcpdr[j]/(cp*cp*cp)
			                      )
			      - v0*v0*(- 1000.0*(d2cdrjdrk*dmwdr[i]+2.0*dmwdr[j]*d2cdridrk+2.0*dmwdr[k]*d2cdridrj+2.0*mw*d3cdr3)/(mw*mw*c*c*c)
			               + 2000.0*(dcdrj*dmwdr[i]+2.0*dmwdr[j]*dcdri+2.0*mw*d2cdridrj)*dmwdr[k]/(mw*mw*mw*c*c*c)
				       + 3000.0*(dcdrj*dmwdr[i]+2.0*dmwdr[j]*dcdri+2.0*mw*d2cdridrj)*dcdrk/(mw*mw*c*c*c*c)
			               + 1000.0*(dcdrk*dmwdr[i]+2.0*dmwdr[k]*dcdri+2.0*mw*d2cdridrk)*(2.0*dmwdr[j]*c+3.0*mw*dcdrj)/(mw*mw*mw*c*c*c*c)
				       + 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)*(2.0*dmwdr[j]*dcdrk+3.0*dmwdr[k]*dcdrj+3.0*mw*d2cdrjdrk)/(mw*mw*mw*c*c*c*c)
				       - 3000.0*(c*dmwdr[i]+2.0*mw*dcdri)*(2.0*dmwdr[j]*c+3.0*mw*dcdrj)*dmwdr[k]/(mw*mw*mw*mw*c*c*c*c)
				       - 4000.0*(c*dmwdr[i]+2.0*mw*dcdri)*(2.0*dmwdr[j]*c+3.0*mw*dcdrj)*dcdrk/(mw*mw*mw*c*c*c*c*c) 
			               + 2.0*t*(dalphadrk*d2alphadridrj + alpha*d3alphadr3)/(cp) - 2.0*t*alpha*d2alphadridrj*dcpdr[k]/(cp*cp)
			               + 2.0*t*(d2alphadrjdrk*dalphadri + dalphadrj*d2alphadridrk)/(cp) - 2.0*t*dalphadrj*dalphadri*dcpdr[k]/(cp*cp)
				       - 2.0*t*(dalphadrk*dalphadri + alpha*d2alphadridrk)*dcpdr[j]/(cp*cp) + 4.0*t*alpha*dalphadri*dcpdr[j]*dcpdr[k]/(cp*cp*cp)
			               - 2.0*t*(dalphadrk*dalphadrj + alpha*d2alphadrjdrk)*dcpdr[i]/(cp*cp) + 4.0*t*alpha*dalphadrj*dcpdr[i]*dcpdr[k]/(cp*cp*cp)
				       + 4.0*t*alpha*dalphadrk*dcpdr[i]*dcpdr[j]/(cp*cp*cp) - 6.0*t*alpha*alpha*dcpdr[i]*dcpdr[j]*dcpdr[k]/(cp*cp*cp*cp)
			              );
	  double d3denomdr3 = 2.0*d3v1Refdr3*d3vdp3 + 2.0*d2v1Refdridrj*d4vdrdp3[k] + 2.0*d2v1Refdridrk*d4vdrdp3[j] + 2.0*d2v1Refdrjdrk*d4vdrdp3[i];
	  double d3adr3 = (-d3v1Refdr3*d4vdp4/2.0-d2v1Refdridrj*d5vdrdp4[k]/2.0-d2v1Refdridrk*d5vdrdp4[j]/2.0-d2v1Refdrjdrk*d5vdrdp4[i]/2.0)/denom
			- (d3vdrdp2[i]*d4vdrdp3[j]+d3vdrdp2[j]*d4vdrdp3[i]-d2v1Refdridrj*d4vdp4/2.0-dv1Refdri*d5vdrdp4[j]/2.0-dv1Refdrj*d5vdrdp4[i]/2.0)*ddenomdrk/(denom*denom)
	                - (d3vdrdp2[i]*d4vdrdp3[k]+d3vdrdp2[k]*d4vdrdp3[i]-d2v1Refdridrk*d4vdp4/2.0-dv1Refdri*d5vdrdp4[k]/2.0-dv1Refdrk*d5vdrdp4[i]/2.0)*ddenomdrj/(denom*denom)
			- (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdri*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)*d2denomdrjdrk/(denom*denom)
			+ 2.0*(d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdri*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)*ddenomdrj*ddenomdrk/(denom*denom*denom)
        		- (d3vdrdp2[j]*d4vdrdp3[k]+d3vdrdp2[k]*d4vdrdp3[j]-d2v1Refdrjdrk*d4vdp4/2.0-dv1Refdrj*d5vdrdp4[k]/2.0-dv1Refdrk*d5vdrdp4[j]/2.0)*ddenomdri/(denom*denom)
			- (d3vdrdp2[j]*d3vdp3+d2vdp2*d4vdrdp3[j]-dv1Refdrj*d4vdp4/2.0-v1Ref*d5vdrdp4[j]/2.0)*d2denomdridrk/(denom*denom)
			+ 2.0*(d3vdrdp2[j]*d3vdp3+d2vdp2*d4vdrdp3[j]-dv1Refdrj*d4vdp4/2.0-v1Ref*d5vdrdp4[j]/2.0)*ddenomdri*ddenomdrk/(denom*denom*denom)
                        + 2.0*(d3vdrdp2[k]*d3vdp3+d2vdp2*d4vdrdp3[k]-dv1Refdrk*d4vdp4/2.0-v1Ref*d5vdrdp4[k]/2.0)*ddenomdri*ddenomdrj/(denom*denom*denom)
			+ 2.0*(d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*(d2denomdridrk*ddenomdrj+ddenomdri*d2denomdrjdrk)/(denom*denom*denom)
			- 6.0*(d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*ddenomdri*ddenomdrj*ddenomdrk/(denom*denom*denom*denom)
                        - (d3vdrdp2[k]*d3vdp3+d2vdp2*d4vdrdp3[k]-dv1Refdrk*d4vdp4/2.0-v1Ref*d5vdrdp4[k]/2.0)*d2denomdridrj/(denom*denom)
			- (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*d3denomdr3/(denom*denom)
			+ 2.0*(d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*d2denomdridrj*ddenomdrk/(denom*denom*denom);
          double d3bdr3 = -(d3vdrdp2[i]*d5vdrdp4[j]/4.0+d3vdrdp2[j]*d5vdrdp4[i]/4.0-2.0/3.0*d4vdrdp3[j]*d4vdrdp3[i])/(denom*denom)*ddenomdrk
        		  -(d3vdrdp2[i]*d5vdrdp4[k]/4.0+d3vdrdp2[k]*d5vdrdp4[i]/4.0-2.0/3.0*d4vdrdp3[k]*d4vdrdp3[i])/(denom*denom)*ddenomdrj
        		+ 2.0*(d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/(denom*denom*denom)*ddenomdrj*ddenomdrk
        		- (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/(denom*denom)*d2denomdrjdrk
        		- (d3vdrdp2[j]*d5vdrdp4[k]/4.0+d3vdrdp2[k]*d5vdrdp4[j]/4.0-2.0/3.0*d4vdrdp3[k]*d4vdrdp3[j])/(denom*denom)*ddenomdri
        		+ 2.0*(d3vdrdp2[j]*d4vdp4/4.0+d2vdp2*d5vdrdp4[j]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[j])/(denom*denom*denom)*ddenomdri*ddenomdrk
        		- (d3vdrdp2[j]*d4vdp4/4.0+d2vdp2*d5vdrdp4[j]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[j])/(denom*denom)*d2denomdridrk
        		+ 2.0*(d3vdrdp2[k]*d4vdp4/4.0+d2vdp2*d5vdrdp4[k]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[k])/(denom*denom*denom)*ddenomdri*ddenomdrj
        		- 6.0*(d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom*denom*denom)*ddenomdri*ddenomdrj*ddenomdrk
        		+ 2.0*(d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom*denom)*d2denomdridrk*ddenomdrj
        		+ 2.0*(d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom*denom)*ddenomdri*d2denomdrjdrk
        		- (d3vdrdp2[k]*d4vdp4/4.0+d2vdp2*d5vdrdp4[k]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[k])/(denom*denom)*d2denomdridrj
        		+ 2.0*(d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom*denom)*d2denomdridrj*ddenomdrk;
			      
          double d3gIntdr3 = 0.0;

          if ((a == 0.0) && (b == 0.0)) {
            d3gIntdr3  = d3v0dr3*(p-pr) + d3v1dr3*(p-pr)*(p-pr)/2.0;
 
          } else if ((a != 0.0) && (b == 0.0)) {
            printf("*-->Exception in fillD3GDR3 (liquid.c). a is not equal to zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
            d3gIntdr3  = 0.0;
 
          } else if ((a == 0.0) && (b != 0.0)) {
            printf("*-->Exception in fillD3GDR3 (liquid.c). a is zero, b is not equal to zero.\n"); liqERRstate = ERR_A_ZERO;
            d3gIntdr3  = 0.0;

          } else if (sum > 0.0) {
            d3gIntdr3  = d3gdr3GMAP(p/10000.0, pr/10000.0, 
	                            v0,                 v1*10000.0,      d2vdp2*10000.0*10000.0,         a*10000.0,         b*10000.0*10000.0, 
	                            dv0dri,         dv1dri*10000.0, d3vdrdp2[i]*10000.0*10000.0,     dadri*10000.0,     dbdri*10000.0*10000.0, 
	                            dv0drj,         dv1drj*10000.0, d3vdrdp2[j]*10000.0*10000.0,     dadrj*10000.0,     dbdrj*10000.0*10000.0, 
				    dv0drk,         dv1drk*10000.0, d3vdrdp2[k]*10000.0*10000.0,     dadrk*10000.0,     dbdrk*10000.0*10000.0, 
                                    d2v0dridrj, d2v1dridrj*10000.0,  			    0.0, d2adridrj*10000.0, d2bdridrj*10000.0*10000.0, 
				    d2v0dridrk, d2v1dridrk*10000.0,  			    0.0, d2adridrk*10000.0, d2bdridrk*10000.0*10000.0, 
				    d2v0drjdrk, d2v1drjdrk*10000.0,  			    0.0, d2adrjdrk*10000.0, d2bdrjdrk*10000.0*10000.0, 
                                    d3v0dr3,       d3v1dr3*10000.0,  			    0.0,    d3adr3*10000.0,    d3bdr3*10000.0*10000.0)*10000.0;
 
          } else if (sum == 0.0) {
            printf("*-->Exception in fillD3GDR3 (liquid.c). a*a-4*b is equal to zero.\n"); liqERRstate = ERR_SUM_ZERO;
            d3gIntdr3  = 0.0;
 
          } else if(sum < 0.0) {
            d3gIntdr3  = d3gdr3LMAP(p/10000.0, pr/10000.0, 
	                            v0,                 v1*10000.0,      d2vdp2*10000.0*10000.0,         a*10000.0,         b*10000.0*10000.0, 
	                            dv0dri,         dv1dri*10000.0, d3vdrdp2[i]*10000.0*10000.0,     dadri*10000.0,     dbdri*10000.0*10000.0, 
	                            dv0drj,         dv1drj*10000.0, d3vdrdp2[j]*10000.0*10000.0,     dadrj*10000.0,     dbdrj*10000.0*10000.0, 
				    dv0drk,         dv1drk*10000.0, d3vdrdp2[k]*10000.0*10000.0,     dadrk*10000.0,     dbdrk*10000.0*10000.0, 
                                    d2v0dridrj, d2v1dridrj*10000.0,  			    0.0, d2adridrj*10000.0, d2bdridrj*10000.0*10000.0, 
				    d2v0dridrk, d2v1dridrk*10000.0,  			    0.0, d2adridrk*10000.0, d2bdridrk*10000.0*10000.0, 
				    d2v0drjdrk, d2v1drjdrk*10000.0,  			    0.0, d2adrjdrk*10000.0, d2bdrjdrk*10000.0*10000.0, 
                                    d3v0dr3,       d3v1dr3*10000.0,  			    0.0,    d3adr3*10000.0,    d3bdr3*10000.0*10000.0)*10000.0;
 
          }
 
          result[i][j][k] += coeffCN*d3gIntdr3;
	  
          if      (i == j && j != k) { result[i][k][j] += coeffCN*d3gIntdr3; result[k][i][j] += coeffCN*d3gIntdr3; }
	  else if (i != j && j == k) { result[j][i][k] += coeffCN*d3gIntdr3; result[j][k][i] += coeffCN*d3gIntdr3; }
	  else if (i != j && j != k) {
	    result[i][k][j] += coeffCN*d3gIntdr3; 
	    result[j][i][k] += coeffCN*d3gIntdr3; 
	    result[j][k][i] += coeffCN*d3gIntdr3; 
	    result[k][i][j] += coeffCN*d3gIntdr3; 
	    result[k][j][i] += coeffCN*d3gIntdr3; 	    
	  }
	}
      }
    }
  }
    
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillD3GDR2DS (double r[NR], double s[NT], double t, double p, double ***result) {
  int i, j, k, l;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) for (j=0; j<NR; j++) for (k=0; k<NT; k++) result[i][j][k] = 0.0;

  /* Configurational entropy terms */
  for (j=0; j<NR; j++) {
    for (k=j; k<NR; k++) {
      for (l=0; l<NS; l++) {
        double config = 0.0;
        for (i=0; i<NE; i++) if (xSpecies[i] > 0.0) 
          config += nSpecies*(
	              (d2xSpeciesdrds[i][j][l]*dxSpeciesdr[i][k]+dxSpeciesdr[i][j]*d2xSpeciesdrds[i][k][l])/xSpecies[i]
	              - dxSpeciesdr[i][j]*dxSpeciesdr[i][k]*dxSpeciesds[i][l]/(xSpecies[i]*xSpecies[i]) )
	          + dnSpeciesds[l]*dxSpeciesdr[i][j]*dxSpeciesdr[i][k]/xSpecies[i];
        if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0) 
          config += nSpecies*( (d2xSpeciesdrds[nH2O][j][l]*dxSpeciesdr[nH2O][k] + dxSpeciesdr[nH2O][j]*d2xSpeciesdrds[nH2O][k][l])
	                         *(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O]))	  
	                      - dxSpeciesdr[nH2O][j]*dxSpeciesdr[nH2O][k]*dxSpeciesds[nH2O][l]
			         *(1.0/(xSpecies[nH2O]*xSpecies[nH2O]) - 1.0/((1.0-xSpecies[nH2O])*(1.0-xSpecies[nH2O]))) )
	          + dnSpeciesds[l]*dxSpeciesdr[nH2O][j]*dxSpeciesdr[nH2O][k]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O])); 

        result[j][k][l] += R*t*config;
        result[k][j][l]  = result[j][k][l];
      }
    }
  }

#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double d2gIntIVdr2[NR][NR];
  
    d2IntegralV_GKdr2(r, s, t, p, d2gIntIVdr2);
    for (i=0; i<NR; i++) {
      for (j=i; j<NR; j++) {
        for (k=0; k<NY; k++) {
	  result[i][j][NS+k] += (fCN[k]-1.0)*d2gIntIVdr2[i][j];
	  result[j][i][NS+k]  = result[i][j][NS+k];
	}
      }
    }
  }
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillD3GDR2DT (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j, k;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) for (j=i; j<NR; j++) {
    result[i][j] = (i == j) ? -2.0*srr[i][i] : -srr[i][j];
    result[j][i] = result[i][j];
  }

  /* Configurational entropy terms */
  for (j=0; j<NR; j++) {
    for (k=j; k<NR; k++) {
      double config = 0.0;
      for (i=0; i<NE; i++) if (xSpecies[i] > 0.0 && dxSpeciesdr[i][j] != 0.0 && dxSpeciesdr[i][k] != 0.0) 
        config += dxSpeciesdr[i][j]*dxSpeciesdr[i][k]/xSpecies[i];
      if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0 && dxSpeciesdr[nH2O][j] != 0.0 && dxSpeciesdr[nH2O][k] != 0.0) 
        config += dxSpeciesdr[nH2O][j]*dxSpeciesdr[nH2O][k]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O])); 
      result[j][k] += R*nSpecies*config;
      result[k][j]  = result[j][k];
    }
  }
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    const double pr         = 1.0;
    const double tr         = 1673.15;
    double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum, coeffCN;
    double dvdr[NR], d2vdrdt[NR], dcRefdr[NR], d2cdrdt[NR], dmwdr[NR], dcpdr[NR], d3vdrdp2[NR], d4vdrdp3[NR], d5vdrdp4[NR], dmOxTotdr[NR], denom;
    double d2cRefdr2[NR][NR], d3cdr2dt[NR][NR];
    double dv0dt, dv1dt;

    if (fabs(p-pr) < 10.0*DBL_EPSILON) return;

    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i];

    /* Convert input composition (r) to liquid moles (m)  */
    for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
    
    /* Compute moles and total moles of oxides */
    for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
    if (mOxTot == 0.0) return;

    /* Deal with the special case of FeO1.3 */
    mOx[NA] = 0.0;
    if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
      const double y = 0.3;
      mOx[iOxFeO1_3] = 0.0;
      if (iCmpFe2SiO4_6 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
      }
      if (iCmpFe2AlO4_1 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
      }
    }

    for (i=0; i<NR; i++) { 
      dvdr[i]    = 0.0; d2vdrdt[i]  = 0.0; dcRefdr[i]  = 0.0; d2cdrdt[i]  = 0.0; dmwdr[i] = 0.0; 
      dcpdr[i]   = 0.0; d3vdrdp2[i] = 0.0; d4vdrdp3[i] = 0.0; d5vdrdp4[i] = 0.0; 
      for (j=0, dmOxTotdr[i]=0.0; j<nc; j++) dmOxTotdr[i] += (liquid[i+1].liqToOx)[j] - (liquid[0].liqToOx)[j];
      for (j=i; j<NR; j++) { d2cRefdr2[i][j] = 0.0; d3cdr2dt[i][j] = 0.0; }
    }
 
    for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
      v       += mOx[i]*bulkSystem[i].gk_v;
      dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
      cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
      dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
      cp      += mOx[i]*bulkSystem[i].gk_cp;
      d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      mw      += mOx[i]*bulkSystem[i].mw;
      
      for (j=0; j<NR; j++) {
        dvdr[j]      += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_v;
        d2vdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dvdt;
        dmwdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].mw;
        dcpdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cp;	
	dcRefdr[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c/mOxTot 
	              - mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot);
	dcRefdr[j]   += (iOxAl2O3 != -1) ? ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
		      - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
	d2cdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt/mOxTot 
	              - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot);
        d3vdrdp2[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
        d4vdrdp3[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
        d5vdrdp4[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      }
      if (iCmpAl2O3 != -1) dcRefdr[iCmpAl2O3] += ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);

      for (j=0; j<NR; j++) {
	for (k=j; k<NR; k++) {
	  d2cRefdr2[j][k] += -((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c*dmOxTotdr[k]/(mOxTot*mOxTot) 	  
	  		   - ((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot)
			   + 2.0*mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot);
	  d2cRefdr2[j][k] += (iOxAl2O3 != -1) ?
	  		   - 2.0*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot)
	  		   - 2.0*((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot)
			   + 6.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot*mOxTot)
			   : 0.0;
			   
	  d3cdr2dt[j][k]  += -((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt*dmOxTotdr[k]/(mOxTot*mOxTot) 
	  		   - ((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot)
			   + 2.0*mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot);
	}
	if (iCmpAl2O3 != -1) d2cRefdr2[(j<iCmpAl2O3) ? j : iCmpAl2O3][(j>iCmpAl2O3) ? j : iCmpAl2O3] +=
	  ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
	  - 2.0*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot);
      }
      if (iCmpAl2O3 != -1) d2cRefdr2[iCmpAl2O3][iCmpAl2O3] +=
	((liquid[iCmpAl2O3+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
	- 2.0*mOx[i]*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[iCmpAl2O3]/(mOxTot*mOxTot*mOxTot);
      
    }
    if (v == 0.0) return;

    alpha   = dvdt/v;
    v0      = v*exp(alpha*(t-tr));
    v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
    c       = cRef + (t-tr)*dcdt;
    v1      = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
    v2      = d2vdp2;
    denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
    a	    = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
    b	    = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
    sum     = a*a - 4.0*b;
    dv0dt   = alpha*v0;
    dv1dt   = - 2.0*v0*v0*alpha*(1000.0/(mw*c*c) + t*alpha*alpha/(cp)) - v0*v0*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp));

    for (i=0; i<NR; i++) {
      double dalphadri   = d2vdrdt[i]/v - dvdt*dvdr[i]/(v*v);
      double dv0dri      = (dvdr[i] + v*dalphadri*(t-tr))*exp(alpha*(t-tr));      
      double dv1Refdri   = -2.0*v*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
                           -v*v*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
			         + 2.0*tr*alpha*dalphadri/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp));   
      double dcdri       = dcRefdr[i] + (t-tr)*d2cdrdt[i];
      double dv1dri      = -2.0*v0*dv0dri*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                           -v0*v0*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c) 
			           + 2.0*t*alpha*dalphadri/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp));      
      double ddenomdri   = 2.0*dv1Refdri*d3vdp3+2.0*v1Ref*d4vdrdp3[i]-6.0*d2vdp2*d3vdrdp2[i]; 
      double dadri       = (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdri*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)/denom
                         - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdri;
      double dbdri       = (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/denom
                         - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdri;		 			 			
      double d2v0dridt   = dvdr[i]*alpha*exp(alpha*(t-tr))+v*(d2vdrdt[i]/v-dvdt/(v*v)*dvdr[i])*exp(alpha*(t-tr))
                         + v*(d2vdrdt[i]/v-dvdt/(v*v)*dvdr[i])*(t-tr)*alpha*exp(alpha*(t-tr));			 
      double d2v1dridt   = -2.0*(dv0dt*dv0dri + v0*d2v0dridt)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                         - 2.0*v0*dv0dri*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
                         - 2.0*v0*dv0dt*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c) 
		        	         + 2.0*t*alpha*dalphadri/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp))
		         - v0*v0*(- 1000.0*(dcdt*dmwdr[i]+2.0*mw*d2cdrdt[i])/(mw*mw*c*c*c) + 3000.0*(c*dmwdr[i]+2.0*mw*dcdri)*dcdt/(mw*mw*c*c*c*c)
		                  + 2.0*alpha*dalphadri/(cp) - alpha*alpha*dcpdr[i]/(cp*cp));

      for (j=i; j<NR; j++) {
        double dalphadrj   = d2vdrdt[j]/v - dvdt*dvdr[j]/(v*v);
        double dv0drj	   = (dvdr[j] + v*dalphadrj*(t-tr))*exp(alpha*(t-tr));      
        double dv1Refdrj   = -2.0*v*dvdr[j]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
        		     -v*v*(- 1000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])/(mw*mw*cRef*cRef*cRef) 
        			   + 2.0*tr*alpha*dalphadrj/(cp) - tr*alpha*alpha*dcpdr[j]/(cp*cp));   
        double dcdrj	   = dcRefdr[j] + (t-tr)*d2cdrdt[j];
        double dv1drj	   = -2.0*v0*dv0drj*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
        		     -v0*v0*(- 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c) 
        			     + 2.0*t*alpha*dalphadrj/(cp) - t*alpha*alpha*dcpdr[j]/(cp*cp));      
        double ddenomdrj   = 2.0*dv1Refdrj*d3vdp3+2.0*v1Ref*d4vdrdp3[j]-6.0*d2vdp2*d3vdrdp2[j]; 
        double dadrj	   = (d3vdrdp2[j]*d3vdp3+d2vdp2*d4vdrdp3[j]-dv1Refdrj*d4vdp4/2.0-v1Ref*d5vdrdp4[j]/2.0)/denom
        		   - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdrj;
        double dbdrj	   = (d3vdrdp2[j]*d4vdp4/4.0+d2vdp2*d5vdrdp4[j]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[j])/denom
                         - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdrj;		 			
        double d2v0drjdt   = dvdr[j]*alpha*exp(alpha*(t-tr))+v*(d2vdrdt[j]/v-dvdt/(v*v)*dvdr[j])*exp(alpha*(t-tr))
        		   + v*(d2vdrdt[j]/v-dvdt/(v*v)*dvdr[j])*(t-tr)*alpha*exp(alpha*(t-tr));
        double d2v1drjdt   = -2.0*(dv0dt*dv0drj + v0*d2v0drjdt)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                           - 2.0*v0*dv0drj*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
                           - 2.0*v0*dv0dt*(- 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c) 
		        	           + 2.0*t*alpha*dalphadrj/(cp) - t*alpha*alpha*dcpdr[j]/(cp*cp))
		           - v0*v0*(- 1000.0*(dcdt*dmwdr[j]+2.0*mw*d2cdrdt[j])/(mw*mw*c*c*c) + 3000.0*(c*dmwdr[j]+2.0*mw*dcdrj)*dcdt/(mw*mw*c*c*c*c)
		                    + 2.0*alpha*dalphadrj/(cp) - alpha*alpha*dcpdr[j]/(cp*cp));

        double d2alphadr2  = -d2vdrdt[i]*dvdr[j]/(v*v)-d2vdrdt[j]*dvdr[i]/(v*v)+2.0*dvdt*dvdr[i]*dvdr[j]/(v*v*v);
        double d2v0dr2     = dvdr[i]*dalphadrj*(t-tr)*exp(alpha*(t-tr)) 					 
			   + dvdr[j]*dalphadri*(t-tr)*exp(alpha*(t-tr))
			   + v*d2alphadr2*(t-tr)*exp(alpha*(t-tr))
			   + v*dalphadri*pow(t-tr,2.0)*dalphadrj*exp(alpha*(t-tr));
        double d2v1Refdr2  = -2.0*dvdr[j]*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
	                    - 2.0*v*dvdr[i]*(- 1000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])/(mw*mw*cRef*cRef*cRef) 
			                     + 2.0*tr*alpha*dalphadrj/(cp) - tr*alpha*alpha*dcpdr[j]/(cp*cp))
        		    - 2.0*v*dvdr[j]*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
        			             + 2.0*tr*alpha*dalphadri/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp))
			     -v*v*(- 1000.0*(dcRefdr[j]*dmwdr[i]+2.0*dmwdr[j]*dcRefdr[i]+2.0*mw*d2cRefdr2[i][j])/(mw*mw*cRef*cRef*cRef)
			           + 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])*(2.0*dmwdr[j]*cRef+3.0*mw*dcRefdr[j])/(mw*mw*mw*cRef*cRef*cRef*cRef) 
			           + 2.0*tr*alpha*d2alphadr2/(cp)
				   + 2.0*tr*dalphadrj*dalphadri/(cp) - 2.0*tr*alpha*dalphadri*dcpdr[j]/(cp*cp) 
				   - 2.0*tr*alpha*dalphadrj*dcpdr[i]/(cp*cp) + 2.0*tr*alpha*alpha*dcpdr[i]*dcpdr[j]/(cp*cp*cp)); 
        double d2cdr2	   = d2cRefdr2[i][j] + (t-tr)*d3cdr2dt[i][j];	
        double d2v1dr2	   = -2.0*dv0drj*dv0dri*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
	                    - 2.0*v0*d2v0dr2*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
	                    - 2.0*v0*dv0dri*(- 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c) 
			                     + 2.0*t*alpha*dalphadrj/(cp) - t*alpha*alpha*dcpdr[j]/(cp*cp))
        		    - 2.0*v0*dv0drj*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c) 
        			             + 2.0*t*alpha*dalphadri/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp))
			     -v0*v0*(- 1000.0*(dcdrj*dmwdr[i]+2.0*dmwdr[j]*dcdri+2.0*mw*d2cdr2)/(mw*mw*c*c*c)
			             + 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)*(2.0*dmwdr[j]*c+3.0*mw*dcdrj)/(mw*mw*mw*c*c*c*c) 
				     + 2.0*t*alpha*d2alphadr2/(cp)
			             + 2.0*t*dalphadrj*dalphadri/(cp) - 2.0*t*alpha*dalphadri*dcpdr[j]/(cp*cp) 
				     - 2.0*t*alpha*dalphadrj*dcpdr[i]/(cp*cp) + 2.0*t*alpha*alpha*dcpdr[i]*dcpdr[j]/(cp*cp*cp));   
        double d2denomdr2  = 2.0*d2v1Refdr2*d3vdp3 + 2.0*dv1Refdri*d4vdrdp3[j] + 2.0*dv1Refdrj*d4vdrdp3[i] - 6.0*d3vdrdp2[j]*d3vdrdp2[i]; 
        double d2adr2	   = (d3vdrdp2[i]*d4vdrdp3[j]+d3vdrdp2[j]*d4vdrdp3[i]-d2v1Refdr2*d4vdp4/2.0-dv1Refdri*d5vdrdp4[j]/2.0-dv1Refdrj*d5vdrdp4[i]/2.0)/denom
	                   - (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdri*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)*ddenomdrj/(denom*denom)
        		   - (d3vdrdp2[j]*d3vdp3+d2vdp2*d4vdrdp3[j]-dv1Refdrj*d4vdp4/2.0-v1Ref*d5vdrdp4[j]/2.0)*ddenomdri/(denom*denom)
                           + 2.0*(d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*ddenomdri*ddenomdrj/(denom*denom*denom)
                           - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*d2denomdr2/(denom*denom);
        double d2bdr2	   = (d3vdrdp2[i]*d5vdrdp4[j]/4.0+d3vdrdp2[j]*d5vdrdp4[i]/4.0-2.0/3.0*d4vdrdp3[j]*d4vdrdp3[i])/denom
                           - (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])*ddenomdrj/(denom*denom)
        		   - (d3vdrdp2[j]*d4vdp4/4.0+d2vdp2*d5vdrdp4[j]/4.0-2.0*d4vdrdp3[j]*d3vdp3/3.0)*ddenomdri/(denom*denom)
			   + 2.0*(d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*ddenomdri*ddenomdrj/(denom*denom*denom)
			   - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*d2denomdr2/(denom*denom);			  
        double d3v0dr2dt   = dvdr[i]*dalphadrj*exp(alpha*(t-tr))+dvdr[i]*dalphadrj*(t-tr)*alpha*exp(alpha*(t-tr))
                           + dvdr[j]*(d2vdrdt[i]/v-dvdt/(v*v)*dvdr[i])*exp(alpha*(t-tr))
			   + dvdr[j]*(d2vdrdt[i]/v-dvdt/(v*v)*dvdr[i])*(t-tr)*alpha*exp(alpha*(t-tr))
	                   + v*d2alphadr2*exp(alpha*(t-tr))+v*d2alphadr2*(t-tr)*alpha*exp(alpha*(t-tr))
	                   + 2.0*v*(d2vdrdt[i]/v-dvdt/(v*v)*dvdr[i])*(t-tr)*dalphadrj*exp(alpha*(t-tr))
	                   + v*(d2vdrdt[i]/v-dvdt/(v*v)*dvdr[i])*pow(t-tr,2.0)*dalphadrj*alpha*exp(alpha*(t-tr));		   			   
        double d3v1dr2dt   = -2.0*(d2v0drjdt*dv0dri+dv0drj*d2v0dridt)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
	                   - 2.0*dv0drj*dv0dri*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
			   - 2.0*(dv0dt*d2v0dr2+v0*d3v0dr2dt)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
			   - 2.0*v0*d2v0dr2*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
	                   - 2.0*(dv0dt*dv0dri+v0*d2v0dridt)*(- 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c) 
			   		    + 2.0*t*alpha*dalphadrj/(cp) - t*alpha*alpha*dcpdr[j]/(cp*cp))
			   - 2.0*v0*dv0dri*(- 1000.0*(dcdt*dmwdr[j]+2.0*mw*d2cdrdt[j])/(mw*mw*c*c*c) + 3000.0*dcdt*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c*c)
			   		    + 2.0*alpha*dalphadrj/(cp) - alpha*alpha*dcpdr[j]/(cp*cp))
        		   - 2.0*(dv0dt*dv0drj+v0*d2v0drjdt)*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c) 
        		        	    + 2.0*t*alpha*dalphadri/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp))
			   - 2.0*v0*dv0drj*(- 1000.0*(dcdt*dmwdr[i]+2.0*mw*d2cdrdt[i])/(mw*mw*c*c*c) + 3000.0*dcdt*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c*c)
        		        	    + 2.0*alpha*dalphadri/(cp) - alpha*alpha*dcpdr[i]/(cp*cp))
			   - 2.0*v0*dv0dt*(- 1000.0*(dcdrj*dmwdr[i]+2.0*dmwdr[j]*dcdri+2.0*mw*d2cdr2)/(mw*mw*c*c*c)
			   	   	   + 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)*(2.0*dmwdr[j]*c+3.0*mw*dcdrj)/(mw*mw*mw*c*c*c*c) 
					   + 2.0*t*alpha*d2alphadr2/(cp)
			   	   	   + 2.0*t*dalphadrj*dalphadri/(cp) - 2.0*t*alpha*dalphadri*dcpdr[j]/(cp*cp) 
			           	   - 2.0*t*alpha*dalphadrj*dcpdr[i]/(cp*cp) + 2.0*t*alpha*alpha*dcpdr[i]*dcpdr[j]/(cp*cp*cp)
				          )
			   - v0*v0*(- 1000.0*(d2cdrdt[j]*dmwdr[i]+2.0*dmwdr[j]*d2cdrdt[i]+2.0*mw*d3cdr2dt[i][j])/(mw*mw*c*c*c)
			            + 3000.0*(dcdrj*dmwdr[i]+2.0*dmwdr[j]*dcdri+2.0*mw*d2cdr2)*dcdt/(mw*mw*c*c*c*c)
			   	    + 1000.0*(dcdt*dmwdr[i]+2.0*mw*d2cdrdt[i])*(2.0*dmwdr[j]*c+3.0*mw*dcdrj)/(mw*mw*mw*c*c*c*c)
				    + 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)*(2.0*dmwdr[j]*dcdt+3.0*mw*d2cdrdt[j])/(mw*mw*mw*c*c*c*c)
				    - 4000.0*(c*dmwdr[i]+2.0*mw*dcdri)*(2.0*dmwdr[j]*c+3.0*mw*dcdrj)*dcdt/(mw*mw*mw*c*c*c*c*c) 
				    + 2.0*alpha*d2alphadr2/(cp)
			   	    + 2.0*dalphadrj*dalphadri/(cp) - 2.0*alpha*dalphadri*dcpdr[j]/(cp*cp) 
				    - 2.0*alpha*dalphadrj*dcpdr[i]/(cp*cp) + 2.0*alpha*alpha*dcpdr[i]*dcpdr[j]/(cp*cp*cp)
				   );
        double d3gIntdr2dt = 0.0;

        if ((a == 0.0) && (b == 0.0)) {
          d3gIntdr2dt  = d3v0dr2dt*(p-pr) + d3v1dr2dt*(p-pr)*(p-pr)/2.0;
 
        } else if ((a != 0.0) && (b == 0.0)) {
          printf("*-->Exception in fillD3GDR2DT (liquid.c). a is not equal to zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
          d3gIntdr2dt  = 0.0;
 
        } else if ((a == 0.0) && (b != 0.0)) {
          printf("*-->Exception in fillD3GDR2DT (liquid.c). a is zero, b is not equal to zero.\n"); liqERRstate = ERR_A_ZERO;
          d3gIntdr2dt  = 0.0;

        } else if (sum > 0.0) {
          d3gIntdr2dt  = d3gdr2dtGMAP(p/10000.0, pr/10000.0, 
	                              v0,               v1*10000.0,      d2vdp2*10000.0*10000.0,      a*10000.0,      b*10000.0*10000.0, 
				      dv0dri,       dv1dri*10000.0, d3vdrdp2[i]*10000.0*10000.0,  dadri*10000.0,  dbdri*10000.0*10000.0, 
				      dv0drj,       dv1drj*10000.0, d3vdrdp2[j]*10000.0*10000.0,  dadrj*10000.0,  dbdrj*10000.0*10000.0, 
				      d2v0dr2,     d2v1dr2*10000.0,                         0.0, d2adr2*10000.0, d2bdr2*10000.0*10000.0, 
				      dv0dt,         dv1dt*10000.0, 
				      d2v0dridt, d2v1dridt*10000.0, 
				      d2v0drjdt, d2v1drjdt*10000.0, 
				      d3v0dr2dt, d3v1dr2dt*10000.0)*10000.0;
 
        } else if (sum == 0.0) {
          printf("*-->Exception in fillD3GDR2DT (liquid.c). a*a-4*b is equal to zero.\n"); liqERRstate = ERR_SUM_ZERO;
          d3gIntdr2dt  = 0.0;
 
        } else if(sum < 0.0) {
          d3gIntdr2dt  = d3gdr2dtLMAP(p/10000.0, pr/10000.0, 
	                              v0,               v1*10000.0,      d2vdp2*10000.0*10000.0,      a*10000.0,      b*10000.0*10000.0, 
				      dv0dri,       dv1dri*10000.0, d3vdrdp2[i]*10000.0*10000.0,  dadri*10000.0,  dbdri*10000.0*10000.0, 
				      dv0drj,       dv1drj*10000.0, d3vdrdp2[j]*10000.0*10000.0,  dadrj*10000.0,  dbdrj*10000.0*10000.0, 
				      d2v0dr2,     d2v1dr2*10000.0,                         0.0, d2adr2*10000.0, d2bdr2*10000.0*10000.0, 
				      dv0dt,         dv1dt*10000.0, 
				      d2v0dridt, d2v1dridt*10000.0, 
				      d2v0drjdt, d2v1drjdt*10000.0, 
				      d3v0dr2dt, d3v1dr2dt*10000.0)*10000.0;
 
        }
	 
        result[i][j] += coeffCN*d3gIntdr2dt;
	if (i != j) result[j][i] += coeffCN*d3gIntdr2dt;
      }
    }
  }
  
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillD3GDR2DP (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) for (j=i; j<NR; j++) {
    result[i][j] = (i == j) ? 2.0*vrr[i][i] : vrr[i][j];
    result[j][i] = result[i][j];
  }
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    const double pr         = 1.0;
    const double tr         = 1673.15;
    double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum, coeffCN;
    double dvdr[NR], d2vdrdt[NR], dcRefdr[NR], d2cdrdt[NR], dmwdr[NR], dcpdr[NR], d3vdrdp2[NR], d4vdrdp3[NR], d5vdrdp4[NR], dmOxTotdr[NR], denom;
    double d2cRefdr2[NR][NR], d3cdr2dt[NR][NR];
    int k;

    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i];

    /* Convert input composition (r) to liquid moles (m)  */
    for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
    
    /* Compute moles and total moles of oxides */
    for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
    if (mOxTot == 0.0) return;
 
    /* Deal with the special case of FeO1.3 */
    mOx[NA] = 0.0;
    if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
      const double y = 0.3;
      mOx[iOxFeO1_3] = 0.0;
      if (iCmpFe2SiO4_6 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
      }
      if (iCmpFe2AlO4_1 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
      }
    }

    for (i=0; i<NR; i++) { 
      dvdr[i]    = 0.0; d2vdrdt[i]  = 0.0; dcRefdr[i]  = 0.0; d2cdrdt[i]  = 0.0; dmwdr[i] = 0.0; 
      dcpdr[i]   = 0.0; d3vdrdp2[i] = 0.0; d4vdrdp3[i] = 0.0; d5vdrdp4[i] = 0.0; 
      for (j=0, dmOxTotdr[i]=0.0; j<nc; j++) dmOxTotdr[i] += (liquid[i+1].liqToOx)[j] - (liquid[0].liqToOx)[j];
      for (j=i; j<NR; j++) { d2cRefdr2[i][j] = 0.0; d3cdr2dt[i][j] = 0.0; }
    }
 
    for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
      v       += mOx[i]*bulkSystem[i].gk_v;
      dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
      cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
      dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
      cp      += mOx[i]*bulkSystem[i].gk_cp;
      d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      mw      += mOx[i]*bulkSystem[i].mw;
      
      for (j=0; j<NR; j++) {
        dvdr[j]      += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_v;
        d2vdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dvdt;
        dmwdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].mw;
        dcpdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cp;	
	dcRefdr[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c/mOxTot 
	              - mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot);
	dcRefdr[j]   += (iOxAl2O3 != -1) ? ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
		      - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
	d2cdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt/mOxTot 
	              - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot);
        d3vdrdp2[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
        d4vdrdp3[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
        d5vdrdp4[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      }
      if (iCmpAl2O3 != -1) dcRefdr[iCmpAl2O3] += ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);
      
      for (j=0; j<NR; j++) {
	for (k=j; k<NR; k++) {
	  d2cRefdr2[j][k] += -((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c*dmOxTotdr[k]/(mOxTot*mOxTot) 	  
	  		   -  ((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot)
			   + 2.0*mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot);
	  d2cRefdr2[j][k] += (iOxAl2O3 != -1) ?
	  		   - 2.0*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot)
	  		   - 2.0*((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot)
			   + 6.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot*mOxTot)
			   : 0.0;
			   
	  d3cdr2dt[j][k]  += -((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt*dmOxTotdr[k]/(mOxTot*mOxTot) 
	  		   - ((liquid[k+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot)
			   + 2.0*mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]*dmOxTotdr[k]/(mOxTot*mOxTot*mOxTot);
	}
	if (iCmpAl2O3 != -1) d2cRefdr2[(j<iCmpAl2O3) ? j : iCmpAl2O3][(j>iCmpAl2O3) ? j : iCmpAl2O3] +=
	  ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
	  - 2.0*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot);
      }
      if (iCmpAl2O3 != -1) d2cRefdr2[iCmpAl2O3][iCmpAl2O3] +=
	((liquid[iCmpAl2O3+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
	- 2.0*mOx[i]*((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*bulkSystem[i].gk_cXal2o3*dmOxTotdr[iCmpAl2O3]/(mOxTot*mOxTot*mOxTot);

    }
    if (v == 0.0) return;

    alpha   = dvdt/v;
    v0      = v*exp(alpha*(t-tr));
    v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
    c       = cRef + (t-tr)*dcdt;
    v1      = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
    v2      = d2vdp2;
    denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
    a	    = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
    b	    = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
    sum     = a*a - 4.0*b;

    for (i=0; i<NR; i++) {
      double dalphadri   = d2vdrdt[i]/v - dvdt*dvdr[i]/(v*v);
      double dv0dri      = (dvdr[i] + v*dalphadri*(t-tr))*exp(alpha*(t-tr));      
      double dv1Refdri   = -2.0*v*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
                           -v*v*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
			         + 2.0*tr*alpha*dalphadri/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp));   
      double dcdri       = dcRefdr[i] + (t-tr)*d2cdrdt[i];
      double dv1dri      = -2.0*v0*dv0dri*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                           -v0*v0*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c) 
			           + 2.0*t*alpha*dalphadri/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp));      
      double ddenomdri   = 2.0*dv1Refdri*d3vdp3+2.0*v1Ref*d4vdrdp3[i]-6.0*d2vdp2*d3vdrdp2[i]; 
      double dadri       = (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdri*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)/denom
                         - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdri;
      double dbdri       = (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/denom
                         - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdri;			

      for (j=i; j<NR; j++) {
        double dalphadrj   = d2vdrdt[j]/v - dvdt*dvdr[j]/(v*v);
        double dv0drj	   = (dvdr[j] + v*dalphadrj*(t-tr))*exp(alpha*(t-tr));      
        double dv1Refdrj   = -2.0*v*dvdr[j]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
        		     -v*v*(- 1000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])/(mw*mw*cRef*cRef*cRef) 
        			   + 2.0*tr*alpha*dalphadrj/(cp) - tr*alpha*alpha*dcpdr[j]/(cp*cp));   
        double dcdrj	   = dcRefdr[j] + (t-tr)*d2cdrdt[j];
        double dv1drj	   = -2.0*v0*dv0drj*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
        		     -v0*v0*(- 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c) 
        			     + 2.0*t*alpha*dalphadrj/(cp) - t*alpha*alpha*dcpdr[j]/(cp*cp));      
        double ddenomdrj   = 2.0*dv1Refdrj*d3vdp3+2.0*v1Ref*d4vdrdp3[j]-6.0*d2vdp2*d3vdrdp2[j]; 
        double dadrj	   = (d3vdrdp2[j]*d3vdp3+d2vdp2*d4vdrdp3[j]-dv1Refdrj*d4vdp4/2.0-v1Ref*d5vdrdp4[j]/2.0)/denom
        		   - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdrj;
        double dbdrj	   = (d3vdrdp2[j]*d4vdp4/4.0+d2vdp2*d5vdrdp4[j]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[j])/denom
                         - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdrj;			

        double d2alphadr2   = -d2vdrdt[i]*dvdr[j]/(v*v)-d2vdrdt[j]*dvdr[i]/(v*v)+2.0*dvdt*dvdr[i]*dvdr[j]/(v*v*v);
        double d2v0dr2      = dvdr[i]*dalphadrj*(t-tr)*exp(alpha*(t-tr))                                          
			    + dvdr[j]*dalphadri*(t-tr)*exp(alpha*(t-tr))
			    + v*d2alphadr2*(t-tr)*exp(alpha*(t-tr))
			    + v*dalphadri*pow(t-tr,2.0)*dalphadrj*exp(alpha*(t-tr));
        double d2v1Refdr2   = -2.0*dvdr[j]*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
	                    - 2.0*v*dvdr[i]*(- 1000.0*(cRef*dmwdr[j]+2.0*mw*dcRefdr[j])/(mw*mw*cRef*cRef*cRef) 
			                     + 2.0*tr*alpha*dalphadrj/(cp) - tr*alpha*alpha*dcpdr[j]/(cp*cp))
        		    - 2.0*v*dvdr[j]*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
        			             + 2.0*tr*alpha*dalphadri/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp))
			     -v*v*(- 1000.0*(dcRefdr[j]*dmwdr[i]+2.0*dmwdr[j]*dcRefdr[i]+2.0*mw*d2cRefdr2[i][j])/(mw*mw*cRef*cRef*cRef)
			           + 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])*(2.0*dmwdr[j]*cRef+3.0*mw*dcRefdr[j])/(mw*mw*mw*cRef*cRef*cRef*cRef) 
			           + 2.0*tr*alpha*d2alphadr2/(cp)
				   + 2.0*tr*dalphadrj*dalphadri/(cp) - 2.0*tr*alpha*dalphadri*dcpdr[j]/(cp*cp) 
				   - 2.0*tr*alpha*dalphadrj*dcpdr[i]/(cp*cp) + 2.0*tr*alpha*alpha*dcpdr[i]*dcpdr[j]/(cp*cp*cp)); 
        double d2cdr2	   = d2cRefdr2[i][j] + (t-tr)*d3cdr2dt[i][j];
        double d2v1dr2	   = -2.0*dv0drj*dv0dri*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
	                    - 2.0*v0*d2v0dr2*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
	                    - 2.0*v0*dv0dri*(- 1000.0*(c*dmwdr[j]+2.0*mw*dcdrj)/(mw*mw*c*c*c) 
			                     + 2.0*t*alpha*dalphadrj/(cp) - t*alpha*alpha*dcpdr[j]/(cp*cp))
        		    - 2.0*v0*dv0drj*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)/(mw*mw*c*c*c) 
        			             + 2.0*t*alpha*dalphadri/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp))
			     -v0*v0*(- 1000.0*(dcdrj*dmwdr[i]+2.0*dmwdr[j]*dcdri+2.0*mw*d2cdr2)/(mw*mw*c*c*c)
			             + 1000.0*(c*dmwdr[i]+2.0*mw*dcdri)*(2.0*dmwdr[j]*c+3.0*mw*dcdrj)/(mw*mw*mw*c*c*c*c) 
				     + 2.0*t*alpha*d2alphadr2/(cp)
			             + 2.0*t*dalphadrj*dalphadri/(cp) - 2.0*t*alpha*dalphadri*dcpdr[j]/(cp*cp) 
				     - 2.0*t*alpha*dalphadrj*dcpdr[i]/(cp*cp) + 2.0*t*alpha*alpha*dcpdr[i]*dcpdr[j]/(cp*cp*cp));   
        double d2denomdr2   = 2.0*d2v1Refdr2*d3vdp3 + 2.0*dv1Refdri*d4vdrdp3[j] + 2.0*dv1Refdrj*d4vdrdp3[i] - 6.0*d3vdrdp2[j]*d3vdrdp2[i]; 
        double d2adr2	   = (d3vdrdp2[i]*d4vdrdp3[j]+d3vdrdp2[j]*d4vdrdp3[i]-d2v1Refdr2*d4vdp4/2.0-dv1Refdri*d5vdrdp4[j]/2.0-dv1Refdrj*d5vdrdp4[i]/2.0)/denom
	                   - (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdri*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)*ddenomdrj/(denom*denom)
        		   - (d3vdrdp2[j]*d3vdp3+d2vdp2*d4vdrdp3[j]-dv1Refdrj*d4vdp4/2.0-v1Ref*d5vdrdp4[j]/2.0)*ddenomdri/(denom*denom)
                           + 2.0*(d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*ddenomdri*ddenomdrj/(denom*denom*denom)
                           - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)*d2denomdr2/(denom*denom);
        double d2bdr2	   = (d3vdrdp2[i]*d5vdrdp4[j]/4.0+d3vdrdp2[j]*d5vdrdp4[i]/4.0-2.0/3.0*d4vdrdp3[j]*d4vdrdp3[i])/denom
                           - (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])*ddenomdrj/(denom*denom)
        		   - (d3vdrdp2[j]*d4vdp4/4.0+d2vdp2*d5vdrdp4[j]/4.0-2.0*d4vdrdp3[j]*d3vdp3/3.0)*ddenomdri/(denom*denom)
			   + 2.0*(d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*ddenomdri*ddenomdrj/(denom*denom*denom)
			   - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)*d2denomdr2/(denom*denom);			  
        double d3gIntdr2dp;

        if ((a == 0.0) && (b == 0.0)) {
          d3gIntdr2dp  = d2v0dr2 + d2v1dr2*(p-pr);
 
        } else if ((a != 0.0) && (b == 0.0)) {
          printf("*-->Exception in fillD3GDR2DP (liquid.c). a is not equal to zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
          d3gIntdr2dp  = 0.0;
 
        } else if ((a == 0.0) && (b != 0.0)) {
          printf("*-->Exception in fillD3GDR2DP (liquid.c). a is zero, b is not equal to zero.\n"); liqERRstate = ERR_A_ZERO;
          d3gIntdr2dp  = 0.0;

        } else {
          d3gIntdr2dp  = d3gdr2dpMAP(p, pr, v0, v1, d2vdp2, a, b, dv0dri, dv1dri, d3vdrdp2[i], dadri, dbdri, dv0drj, dv1drj, d3vdrdp2[j], dadrj, dbdrj, 
	                             d2v0dr2, d2v1dr2, 0.0, d2adr2, d2bdr2);
 
        }
 
        result[i][j] += coeffCN*d3gIntdr2dp;
	if (i != j) result[j][i] += coeffCN*d3gIntdr2dp;
      }
    }
  }
  
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillD3GDRDS2 (double r[NR], double s[NT], double t, double p, double ***result) {
  int i, j, k, l;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) for (j=0; j<NT; j++) for (k=0; k<NT; k++) result[i][j][k] = 0.0;

  /* Configurational entropy terms */
  for (j=0; j<NR; j++) {
    for (k=0; k<NS; k++) {
      for (l=k; l<NS; l++) {
        double config = 0.0;
        for (i=0; i<NE; i++) if (xSpecies[i] > 0.0) 
          config += nSpecies*(
                     (d2xSpeciesdrds[i][j][k]*dxSpeciesds[i][l] + dxSpeciesds[i][k]*d2xSpeciesdrds[i][j][l])/xSpecies[i]
		     - dxSpeciesdr[i][j]*dxSpeciesds[i][k]*dxSpeciesds[i][l]/(xSpecies[i]*xSpecies[i]) )
		  + dnSpeciesds[l]*(d2xSpeciesdrds[i][j][k]*log(xSpecies[i]) + dxSpeciesdr[i][j]*dxSpeciesds[i][k]/xSpecies[i])
		  + dnSpeciesds[k]*(d2xSpeciesdrds[i][j][l]*log(xSpecies[i]) + dxSpeciesdr[i][j]*dxSpeciesds[i][l]/xSpecies[i])
		  + d2nSpeciesds2[k][l]*(dxSpeciesdr[i][j]*(1.0 + log(xSpecies[i])));
        if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0) 
          config += d2nSpeciesds2[k][l]*(dxSpeciesdr[nH2O][j]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O])))
	          + dnSpeciesds[k]*(d2xSpeciesdrds[nH2O][j][l]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O]))
	                            + dxSpeciesdr[nH2O][j]*dxSpeciesds[nH2O][l]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O])))
		  + dnSpeciesds[l]*(d2xSpeciesdrds[nH2O][j][k]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O])) 
		                    + dxSpeciesds[nH2O][k]*dxSpeciesdr[nH2O][j]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O])))
                  + nSpecies*(
 		      d2xSpeciesdrds[nH2O][j][k]*dxSpeciesds[nH2O][l]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O]))
		    + dxSpeciesds[nH2O][k]*d2xSpeciesdrds[nH2O][j][l]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O]))
		    - dxSpeciesds[nH2O][k]*dxSpeciesdr[nH2O][j]*dxSpeciesds[nH2O][l]
		      *(1.0/(xSpecies[nH2O]*xSpecies[nH2O]) - 1.0/((1.0-xSpecies[nH2O])*(1.0-xSpecies[nH2O]))) ); 	  
        result[j][k][l] += R*t*config;
        result[j][l][k]  = result[j][k][l];
      }
    }
  }
}

static void fillD3GDRDSDT (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j, k;

  for (i=0; i<NR; i++) for (j=0; j<NT; j++) result[i][j] = 0.0;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) for (j=0; j<NS; j++) result[i][j] = -srs[i][j];

  /* Configurational entropy terms */
  for (j=0; j<NR; j++) {
    for (k=0; k<NS; k++) {
      double config = 0.0;
      for (i=0; i<NE; i++) if (xSpecies[i] > 0.0) 
        config += nSpecies*(d2xSpeciesdrds[i][j][k]*log(xSpecies[i]) + dxSpeciesdr[i][j]*dxSpeciesds[i][k]/xSpecies[i])
	        + dnSpeciesds[k]*(dxSpeciesdr[i][j]*(1.0 + log(xSpecies[i])));
      if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0) 
        config += dnSpeciesds[k]*dxSpeciesdr[nH2O][j]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O]))	
                + nSpecies*(d2xSpeciesdrds[nH2O][j][k]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O])) 
		  + dxSpeciesds[nH2O][k]*dxSpeciesdr[nH2O][j]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O]))); 
      result[j][k] += R*config;
    }
  }

#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double d2gIntIVdrdt[NR];
  
    d2IntegralV_GKdrdt(r, s, t, p, d2gIntIVdrdt);
    for (i=0; i<NR; i++) for (j=0; j<NY; j++) result[i][NS+j] += (-ssCnModelParameters[j*nc+i+1].entropy + ssCnModelParameters[j*nc  +0].entropy) + (fCN[j]-1.0)*d2gIntIVdrdt[i];
  }
#endif /* USE_GHIORSO_KRESS_MODEL */
}

static void fillD3GDRDSDP (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j;

  for (i=0; i<NR; i++) for (j=0; j<NT; j++) result[i][j] = 0.0;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) for (j=0; j<NS; j++) result[i][j] = vrs[i][j];

#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double d2gIntIVdrdp[NR];
    
    d2IntegralV_GKdrdp(r, s, t, p, d2gIntIVdrdp);
    for (i=0; i<NR; i++) for (j=0; j<NY; j++) result[i][NS+j] += (fCN[j]-1.0)*d2gIntIVdrdp[i];
  } 
#endif /* USE_GHIORSO_KRESS_MODEL */
}

static void fillD3GDS3 (double r[NR], double s[NT], double t, double p, double ***result) {
  int i, j, k, l;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NT; i++) for (j=0; j<NT; j++) for (k=0; k<NT; k++) result[i][j][k] = 0.0;

  /* Configurational entropy terms */
  for (j=0; j<NS; j++) {
    for (k=j; k<NS; k++) {
      for (l=k; l<NS; l++) {
        double config = 0.0;
        for (i=0; i<NE; i++) if (xSpecies[i] > 0.0) 
          config += -nSpecies*dxSpeciesds[i][j]*dxSpeciesds[i][k]*dxSpeciesds[i][l]/(xSpecies[i]*xSpecies[i])
	          + dnSpeciesds[l]*dxSpeciesds[i][j]*dxSpeciesds[i][k]/xSpecies[i]
		  + dnSpeciesds[k]*dxSpeciesds[i][j]*dxSpeciesds[i][l]/xSpecies[i]
		  + d2nSpeciesds2[k][l]*dxSpeciesds[i][j]*(1.0 + log(xSpecies[i]))
		  + dnSpeciesds[j]*dxSpeciesds[i][k]*dxSpeciesds[i][l]/xSpecies[i]
		  + d2nSpeciesds2[j][l]*dxSpeciesds[i][k]*(1.0 + log(xSpecies[i]))
		  + d2nSpeciesds2[j][k]*dxSpeciesds[i][l]*(1.0 + log(xSpecies[i]))
		  + d3nSpeciesds3[j][k][l]*xSpecies[i]*log(xSpecies[i]);		  
        if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0) 
          config += d3nSpeciesds3[j][k][l]*(xSpecies[nH2O]*log(xSpecies[nH2O]) + (1.0-xSpecies[nH2O])*log(1.0-xSpecies[nH2O]))
	          + d2nSpeciesds2[j][k]*dxSpeciesds[nH2O][l]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O]))
                  + d2nSpeciesds2[j][l]*dxSpeciesds[nH2O][k]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O]))
		  + dnSpeciesds[j]*dxSpeciesds[nH2O][k]*dxSpeciesds[nH2O][l]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O]))
                  + d2nSpeciesds2[k][l]*dxSpeciesds[nH2O][j]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O]))
		  + dnSpeciesds[k]*dxSpeciesds[nH2O][j]*dxSpeciesds[nH2O][l]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O]))
	          + dnSpeciesds[l]*dxSpeciesds[nH2O][j]*dxSpeciesds[nH2O][k]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O]))
		  - nSpecies*dxSpeciesds[nH2O][j]*dxSpeciesds[nH2O][k]*dxSpeciesds[nH2O][l]
		    *(1.0/(xSpecies[nH2O]*xSpecies[nH2O]) - 1.0/((1.0-xSpecies[nH2O])*(1.0-xSpecies[nH2O])));
        result[j][k][l] += R*t*config;
        result[k][j][l]  = result[j][k][l];
        result[l][j][k]  = result[j][k][l];
        result[l][k][j]  = result[j][k][l];
        result[j][l][k]  = result[j][k][l];
        result[k][l][j]  = result[j][k][l];
      }
    }
  }
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double yIV = 1.0;
    
    for (i=0; i<NY; i++) yIV -= (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
    
    for (i=0; i<NY; i++) {
      double y = (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
      for (j=i; j<NY; j++) {
        for (k=j; k<NY; k++) {	
          if ((i == j) && (j == k)) result[NS+i][NS+i][NS+i] = R*t*(-1.0/(y*y) + 1.0/(yIV*yIV));
	  else                      result[NS+i][NS+j][NS+k] = R*t/(yIV*yIV); 
	  result[NS+j][NS+i][NS+k] = result[NS+i][NS+j][NS+k];
	  result[NS+k][NS+i][NS+j] = result[NS+i][NS+j][NS+k];
	  result[NS+k][NS+j][NS+i] = result[NS+i][NS+j][NS+k];
	  result[NS+i][NS+k][NS+j] = result[NS+i][NS+j][NS+k];
	  result[NS+j][NS+k][NS+i] = result[NS+i][NS+j][NS+k];
	  
	}
      }
    }
    
  }
#endif /* USE_GHIORSO_KRESS_MODEL */
}

static void fillD3GDS2DT (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j, k;

  for (i=0; i<NS; i++) for (j=0; j<NS; j++) result[i][j] = 0.0;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NS; i++) for (j=i; j<NS; j++) {
      result[i][j] = (i == j) ? -2.0*sss[i][i] : -sss[i][j];
      result[j][i] = result[i][j];
  }

  /* Configurational entropy terms */
  for (j=0; j<NS; j++) {
    for (k=j; k<NS; k++) {
      double config = 0.0;
      for (i=0; i<NE; i++) if (xSpecies[i] > 0.0) 
        config += nSpecies*dxSpeciesds[i][j]*dxSpeciesds[i][k]/xSpecies[i]
	        + dnSpeciesds[k]*dxSpeciesds[i][j]*(1.0 + log(xSpecies[i]))
	        + dnSpeciesds[j]*dxSpeciesds[i][k]*(1.0 + log(xSpecies[i]))
	        + d2nSpeciesds2[j][k]*xSpecies[i]*log(xSpecies[i]);
      if (nH2O != -1 && xSpecies[nH2O] > 0.0 && xSpecies[nH2O] < 1.0) 
        config += d2nSpeciesds2[j][k]*(xSpecies[nH2O]*log(xSpecies[nH2O]) + (1.0-xSpecies[nH2O])*log(1.0-xSpecies[nH2O]))
                + dnSpeciesds[j]*dxSpeciesds[nH2O][k]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O]))
                + dnSpeciesds[k]*dxSpeciesds[nH2O][j]*(log(xSpecies[nH2O]) - log(1.0-xSpecies[nH2O]))
	        + nSpecies*dxSpeciesds[nH2O][j]*dxSpeciesds[nH2O][k]*(1.0/xSpecies[nH2O] + 1.0/(1.0-xSpecies[nH2O])); 
      result[j][k] += R*config;
      result[k][j]  = result[j][k];
    }
  }
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double yIV = 1.0;
    
    for (i=0; i<NY; i++) yIV -= (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
    
    for (i=0; i<NY; i++) {
      double y = (s[NS+i] > 0.0) ? s[NS+i] : DBL_EPSILON;
      result[NS+i][NS+i] = R*(1.0/y + 1.0/yIV);
      for (j=i+1; j<NY; j++) { result[NS+i][NS+j] = R/yIV; result[NS+j][NS+i] = result[NS+i][NS+j]; }
    }
    
  }
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillD3GDS2DP (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j;

  for (i=0; i<NS; i++) for (j=0; j<NS; j++) result[i][j] = 0.0;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NS; i++) for (j=i; j<NS; j++) {
      result[i][j] = (i == j) ? 2.0*vss[i][i] : vss[i][j];
      result[j][i] = result[i][j];
  }
}

static void fillD3GDSDT2 (double r[NR], double s[NT], double t, double p, double *result) {
  int i;

  for (i=0; i<NT; i++) result[i] = 0.0;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NS; i++) result[i] = -cps[i]/t;
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double d2gIntIVdt2 = d2IntegralV_GKdT2(r, s, t, p);  
    for (i=0; i<NY; i++) result[NS+i] = (fCN[i]-1.0)*d2gIntIVdt2; 
  }
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillD3GDSDTDP (double r[NR], double s[NT], double t, double p, double *result) {
  int i;

  for (i=0; i<NT; i++) result[i] = 0.0;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NS; i++) result[i] = dvdts[i];
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double d2gIntIVdtdp = d2IntegralV_GKdTdP(r, s, t, p);  
    for (i=0; i<NY; i++) result[NS+i] = (fCN[i]-1.0)*d2gIntIVdtdp; 
  }
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillD3GDSDP2 (double r[NR], double s[NT], double t, double p, double *result) {
  int i;

  for (i=0; i<NT; i++) result[i] = 0.0;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NS; i++) result[i] = dvdps[i];
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    double d2gIntIVdp2 = d2IntegralV_GKdP2(r, s, t, p);  
    for (i=0; i<NY; i++) result[NS+i] = (fCN[i]-1.0)*d2gIntIVdp2; 
  }
#endif /* USE_GHIORSO_KRESS_MODEL */

}
 
static void fillD3GDRDT2 (double r[NR], double s[NT], double t, double p, double *result) {
  int i;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) result[i] = -cpr[i]/t;
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    const double pr        = 1.0;
    const double tr        = 1673.15;
    double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum, coeffCN;
    double dvdr[NR], d2vdrdt[NR], dcRefdr[NR], d2cdrdt[NR], dmwdr[NR], dcpdr[NR], d3vdrdp2[NR], d4vdrdp3[NR], d5vdrdp4[NR], dmOxTotdr[NR], denom;
    int j;

    if (fabs(p-pr) < 10.0*DBL_EPSILON) return;

    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i];

    /* Convert input composition (r) to liquid moles (m)  */
    for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
    
    /* Compute moles and total moles of oxides */
    for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
    if (mOxTot == 0.0) return;
 
    /* Deal with the special case of FeO1.3 */
    mOx[NA] = 0.0;
    if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
      const double y = 0.3;
      mOx[iOxFeO1_3] = 0.0;
      if (iCmpFe2SiO4_6 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
      }
      if (iCmpFe2AlO4_1 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
      }
    }

    for (i=0; i<NR; i++) { 
      dvdr[i]    = 0.0; d2vdrdt[i]  = 0.0; dcRefdr[i]  = 0.0; d2cdrdt[i]  = 0.0; dmwdr[i] = 0.0; 
      dcpdr[i]   = 0.0; d3vdrdp2[i] = 0.0; d4vdrdp3[i] = 0.0; d5vdrdp4[i] = 0.0; 
      for (j=0, dmOxTotdr[i]=0.0; j<nc; j++) dmOxTotdr[i] += (liquid[i+1].liqToOx)[j] - (liquid[0].liqToOx)[j];
    }
 
    for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
      v       += mOx[i]*bulkSystem[i].gk_v;
      dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
      cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
      dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
      cp      += mOx[i]*bulkSystem[i].gk_cp;
      d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      mw      += mOx[i]*bulkSystem[i].mw;
      for (j=0; j<NR; j++) {
        dvdr[j]      += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_v;
        d2vdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dvdt;
        dmwdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].mw;
        dcpdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cp;	
	dcRefdr[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c/mOxTot 
	              - mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot);
        dcRefdr[j]   += (iOxAl2O3 != -1) ? ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
		      - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
	d2cdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt/mOxTot 
	              - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot);
        d3vdrdp2[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
        d4vdrdp3[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
        d5vdrdp4[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      }
      if (iCmpAl2O3 != -1) dcRefdr[iCmpAl2O3] += ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);
    }
    if (v == 0.0) return;

    alpha   = dvdt/v;
    v0      = v*exp(alpha*(t-tr));
    v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
    c       = cRef + (t-tr)*dcdt;
    v1      = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
    v2      = d2vdp2;
    denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
    a	    = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
    b	    = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
    sum     = a*a - 4.0*b;

    for (i=0; i<NR; i++) {
      double dalphadr = d2vdrdt[i]/v - dvdt*dvdr[i]/(v*v);
      double dv0dr    = (dvdr[i] + v*dalphadr*(t-tr))*exp(alpha*(t-tr));      
      double dv1Refdr = -2.0*v*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
                        -v*v*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
		              + 2.0*tr*alpha*dalphadr/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp));   
      double dcdr     = dcRefdr[i] + (t-tr)*d2cdrdt[i];
      double dv1dr    = -2.0*v0*dv0dr*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                        -v0*v0*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*c*c*c) 
		        	+ 2.0*t*alpha*dalphadr/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp));      
      double dv2dr    = d3vdrdp2[i];
      double ddenomdr = 2.0*dv1Refdr*d3vdp3+2.0*v1Ref*d4vdrdp3[i]-6.0*d2vdp2*d3vdrdp2[i]; 
      double dadr     = (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdr*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)/denom
                      - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdr;
      double dbdr     = (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/denom
                      - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdr;
      double dv0dt    = v*alpha*exp(alpha*(t-tr));
      double dv1dt    = - 2.0*v0*v0*alpha*(1000.0/(mw*c*c) + t*alpha*alpha/(cp)) - v0*v0*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp));
      double d2v0drdt = v*dalphadr*exp(alpha*(t-tr)) + (dvdr[i] + v*dalphadr*(t-tr))*alpha*exp(alpha*(t-tr));
      
      double d2v1drdt = -2.0*(dv0dt*dv0dr + v0*d2v0drdt)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                      - 2.0*v0*dv0dr*(- 2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
                      - 2.0*v0*dv0dt*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*c*c*c) 
		        	      + 2.0*t*alpha*dalphadr/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp))
		      - v0*v0*(- 1000.0*(dcdt*dmwdr[i]+2.0*mw*d2cdrdt[i])/(mw*mw*c*c*c) + 3000.0*(c*dmwdr[i]+2.0*mw*dcdr)*dcdt/(mw*mw*c*c*c*c)
		               + 2.0*alpha*dalphadr/(cp) - alpha*alpha*dcpdr[i]/(cp*cp));
      double d2v0dt2  = v*alpha*alpha*exp(alpha*(t-tr));
      double d2v1dt2  = - 2.0*(dv0dt*dv0dt+v0*d2v0dt2)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                      - 4.0*v0*dv0dt*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
	              - v0*v0*(6000.0*dcdt*dcdt/(mw*c*c*c*c));
      double d3v0drdt2  = 2.0*v*dalphadr*alpha*exp(alpha*(t-tr)) + (dvdr[i] + v*dalphadr*(t-tr))*alpha*alpha*exp(alpha*(t-tr));
      
      double d3v1drdt2  = - 2.0*(d2v0dt2*dv0dr + dv0dt*d2v0drdt + dv0dt*d2v0drdt + v0*d3v0drdt2)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                          - 2.0*(dv0dt*dv0dr + v0*d2v0drdt)*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
                          - 2.0*(dv0dt*dv0dr + v0*d2v0drdt)*(- 2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp)) - 2.0*v0*dv0dr*6000.0*dcdt*dcdt/(mw*c*c*c*c)
                          - 2.0*(dv0dt*dv0dt + v0*d2v0dt2)*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*c*c*c) + 2.0*t*alpha*dalphadr/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp))
		          - 2.0*v0*dv0dt*(- 1000.0*(dcdt*dmwdr[i]+2.0*mw*d2cdrdt[i])/(mw*mw*c*c*c) + 3000.0*(c*dmwdr[i]+2.0*mw*dcdr)*dcdt/(mw*mw*c*c*c*c)
		                          + 2.0*alpha*dalphadr/(cp) - alpha*alpha*dcpdr[i]/(cp*cp))      
		          - 2.0*v0*dv0dt*(- 1000.0*(dcdt*dmwdr[i]+2.0*mw*d2cdrdt[i])/(mw*mw*c*c*c) + 3000.0*(c*dmwdr[i]+2.0*mw*dcdr)*dcdt/(mw*mw*c*c*c*c)
		                          + 2.0*alpha*dalphadr/(cp) - alpha*alpha*dcpdr[i]/(cp*cp))
			  - v0*v0*(6000.0*(dcdt*dmwdr[i]+2.0*mw*d2cdrdt[i])*dcdt/(mw*mw*c*c*c*c) - 12000.0*(c*dmwdr[i]+2.0*mw*dcdr)*dcdt*dcdt/(mw*mw*c*c*c*c*c));

      double d3gIntdrdt2 = 0.0;

      if ((a == 0.0) && (b == 0.0)) {
        d3gIntdrdt2 = d3v0drdt2*(p-pr) + d3v1drdt2*(p-pr)*(p-pr)/2.0;
 
      } else if ((a != 0.0) && (b == 0.0)) {
	printf("*-->Exception in fillD3GDRDT2 (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
        d3gIntdrdt2 = 0.0;
 
      } else if ((a == 0.0) && (b != 0.0)) {
	printf("*-->Exception in fillD3GDRDT2 (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
        d3gIntdrdt2 = 0.0;

      } else if (sum > 0.0) {	
        d3gIntdrdt2 = d3gdrdt2GMAP(p/10000.0, pr/10000.0, 
	                           v0,               v1*10000.0,    v2*10000.0*10000.0,    a*10000.0,    b*10000.0*10000.0, 
				   dv0dr,         dv1dr*10000.0, dv2dr*10000.0*10000.0, dadr*10000.0, dbdr*10000.0*10000.0, 
				   dv0dt,         dv1dt*10000.0, 
	                           d2v0drdt,   d2v1drdt*10000.0, 
				   d2v0dt2,     d2v1dt2*10000.0, 
				   d3v0drdt2, d3v1drdt2*10000.0)*10000.0;
	 
      } else if (sum == 0.0) {
	printf("*-->Exception in fillD3GDRDT2 (liquid.c). a*a-4*b is equal to zero.\n"); liqERRstate = ERR_SUM_ZERO;
        d3gIntdrdt2 = 0.0;
 
      } else if(sum < 0.0) {
        d3gIntdrdt2 = d3gdrdt2LMAP(p/10000.0, pr/10000.0, 
	                           v0,               v1*10000.0,    v2*10000.0*10000.0,    a*10000.0,    b*10000.0*10000.0, 
				   dv0dr,         dv1dr*10000.0, dv2dr*10000.0*10000.0, dadr*10000.0, dbdr*10000.0*10000.0, 
				   dv0dt,         dv1dt*10000.0, 
	                           d2v0drdt,   d2v1drdt*10000.0, 
				   d2v0dt2,     d2v1dt2*10000.0, 
				   d3v0drdt2, d3v1drdt2*10000.0)*10000.0;
 
      }
 
      result[i] += coeffCN*d3gIntdrdt2;
    }
  }
  
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillD3GDRDTDP (double r[NR], double s[NT], double t, double p, double *result) {
  int i;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) result[i] = dvdtr[i];
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    const double pr        = 1.0;
    const double tr        = 1673.15;
    double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum, coeffCN;
    double dvdr[NR], d2vdrdt[NR], dcRefdr[NR], d2cdrdt[NR], dmwdr[NR], dcpdr[NR], d3vdrdp2[NR], d4vdrdp3[NR], d5vdrdp4[NR], dmOxTotdr[NR], denom;
    int j;

    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i];

    /* Convert input composition (r) to liquid moles (m)  */
    for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
    
    /* Compute moles and total moles of oxides */
    for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
    if (mOxTot == 0.0) return;
 
    /* Deal with the special case of FeO1.3 */
    mOx[NA] = 0.0;
    if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
      const double y = 0.3;
      mOx[iOxFeO1_3] = 0.0;
      if (iCmpFe2SiO4_6 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
      }
      if (iCmpFe2AlO4_1 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
      }
    }

    for (i=0; i<NR; i++) { 
      dvdr[i]    = 0.0; d2vdrdt[i]  = 0.0; dcRefdr[i]  = 0.0; d2cdrdt[i]  = 0.0; dmwdr[i] = 0.0; 
      dcpdr[i]   = 0.0; d3vdrdp2[i] = 0.0; d4vdrdp3[i] = 0.0; d5vdrdp4[i] = 0.0; 
      for (j=0, dmOxTotdr[i]=0.0; j<nc; j++) dmOxTotdr[i] += (liquid[i+1].liqToOx)[j] - (liquid[0].liqToOx)[j];
    }
 
    for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
      v       += mOx[i]*bulkSystem[i].gk_v;
      dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
      cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
      dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
      cp      += mOx[i]*bulkSystem[i].gk_cp;
      d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      mw      += mOx[i]*bulkSystem[i].mw;
      for (j=0; j<NR; j++) {
        dvdr[j]      += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_v;
        d2vdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dvdt;
        dmwdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].mw;
        dcpdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cp;	
	dcRefdr[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c/mOxTot 
	              - mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot);
	dcRefdr[j]   += (iOxAl2O3 != -1) ? ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
		      - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
	d2cdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt/mOxTot 
	              - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot);
        d3vdrdp2[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
        d4vdrdp3[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
        d5vdrdp4[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      }
      if (iCmpAl2O3 != -1) dcRefdr[iCmpAl2O3] += ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);
    }
    if (v == 0.0) return;

    alpha   = dvdt/v;
    v0      = v*exp(alpha*(t-tr));
    v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
    c       = cRef + (t-tr)*dcdt;
    v1      = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
    v2      = d2vdp2;
    denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
    a	    = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
    b	    = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
    sum     = a*a - 4.0*b;

    for (i=0; i<NR; i++) {
      double dalphadr = d2vdrdt[i]/v - dvdt*dvdr[i]/(v*v);
      double dv0dr    = (dvdr[i] + v*dalphadr*(t-tr))*exp(alpha*(t-tr));      
      double dv1Refdr = -2.0*v*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
                        -v*v*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
		              + 2.0*tr*alpha*dalphadr/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp));   
      double dcdr     = dcRefdr[i] + (t-tr)*d2cdrdt[i];
      double dv1dr    = -2.0*v0*dv0dr*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                        -v0*v0*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*c*c*c) 
		        	+ 2.0*t*alpha*dalphadr/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp));      
      double dv2dr    = d3vdrdp2[i];
      double ddenomdr = 2.0*dv1Refdr*d3vdp3+2.0*v1Ref*d4vdrdp3[i]-6.0*d2vdp2*d3vdrdp2[i]; 
      double dadr     = (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdr*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)/denom
                      - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdr;
      double dbdr     = (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/denom
                      - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdr;
      double dv0dt    = v*alpha*exp(alpha*(t-tr));
      double dv1dt    = - 2.0*v0*v0*alpha*(1000.0/(mw*c*c) + t*alpha*alpha/(cp)) - v0*v0*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp));

      double d2v0drdt = v*dalphadr*exp(alpha*(t-tr)) + (dvdr[i] + v*dalphadr*(t-tr))*alpha*exp(alpha*(t-tr));
      double d2v1drdt = -2.0*(dv0dt*dv0dr + v0*d2v0drdt)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                      - 2.0*v0*dv0dr*(- 2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
                      - 2.0*v0*dv0dt*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*c*c*c) 
		        	      + 2.0*t*alpha*dalphadr/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp))
		      - v0*v0*(- 1000.0*(dcdt*dmwdr[i]+2.0*mw*d2cdrdt[i])/(mw*mw*c*c*c) + 3000.0*(c*dmwdr[i]+2.0*mw*dcdr)*dcdt/(mw*mw*c*c*c*c)
		               + 2.0*alpha*dalphadr/(cp) - alpha*alpha*dcpdr[i]/(cp*cp));
      double d3gdrdtdp;

      if ((a == 0.0) && (b == 0.0)) {
        d3gdrdtdp = d2v0drdt + d2v1drdt*(p-pr);
 
      } else if ((a != 0.0) && (b == 0.0)) {
	printf("*-->Exception in fillD2GDRDT (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
        d3gdrdtdp = 0.0;
 
      } else if ((a == 0.0) && (b != 0.0)) {
	printf("*-->Exception in fillD2GDRDT (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
        d3gdrdtdp = 0.0;

      } else {	
        d3gdrdtdp = d3gdrdtdpMAP(p, pr, v0, v1, v2, a, b, dv0dr, dv1dr, dv2dr, dadr, dbdr, dv0dt, dv1dt, d2v0drdt, d2v1drdt);
 
      }
 
      result[i] += coeffCN*d3gdrdtdp;
    }
  }
  
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static void fillD3GDRDP2 (double r[NR], double s[NT], double t, double p, double *result) {
  int i;

  /* Taylor expansion and standard state terms */
  for (i=0; i<NR; i++) result[i] = dvdpr[i];
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    const double pr        = 1.0;
    const double tr        = 1673.15;
    double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum, coeffCN;
    double dvdr[NR], d2vdrdt[NR], dcRefdr[NR], d2cdrdt[NR], dmwdr[NR], dcpdr[NR], d3vdrdp2[NR], d4vdrdp3[NR], d5vdrdp4[NR], dmOxTotdr[NR], denom;
    int j;

    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i];

    /* Convert input composition (r) to liquid moles (m)  */
    for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
    
    /* Compute moles and total moles of oxides */
    for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
    if (mOxTot == 0.0) return;
 
    /* Deal with the special case of FeO1.3 */
    mOx[NA] = 0.0;
    if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
      const double y = 0.3;
      mOx[iOxFeO1_3] = 0.0;
      if (iCmpFe2SiO4_6 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
      }
      if (iCmpFe2AlO4_1 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
      }
    }

    for (i=0; i<NR; i++) { 
      dvdr[i]    = 0.0; d2vdrdt[i]  = 0.0; dcRefdr[i]  = 0.0; d2cdrdt[i]  = 0.0; dmwdr[i] = 0.0; 
      dcpdr[i]   = 0.0; d3vdrdp2[i] = 0.0; d4vdrdp3[i] = 0.0; d5vdrdp4[i] = 0.0; 
      for (j=0, dmOxTotdr[i]=0.0; j<nc; j++) dmOxTotdr[i] += (liquid[i+1].liqToOx)[j] - (liquid[0].liqToOx)[j];
    }
 
    for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
      v       += mOx[i]*bulkSystem[i].gk_v;
      dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
      cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
      dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
      cp      += mOx[i]*bulkSystem[i].gk_cp;
      d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      mw      += mOx[i]*bulkSystem[i].mw;
      for (j=0; j<NR; j++) {
        dvdr[j]      += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_v;
        d2vdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dvdt;
        dmwdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].mw;
        dcpdr[j]     += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_cp;	
	dcRefdr[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_c/mOxTot 
	              - mOx[i]*bulkSystem[i].gk_c*dmOxTotdr[j]/(mOxTot*mOxTot);
	dcRefdr[j]   += (iOxAl2O3 != -1) ? ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot)
		      - 2.0*mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3*dmOxTotdr[j]/(mOxTot*mOxTot*mOxTot) : 0.0;
	d2cdrdt[j]   += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*bulkSystem[i].gk_dcdt/mOxTot 
	              - mOx[i]*bulkSystem[i].gk_dcdt*dmOxTotdr[j]/(mOxTot*mOxTot);
        d3vdrdp2[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
        d4vdrdp3[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
        d5vdrdp4[j]  += ((liquid[j+1].liqToOx)[i]-(liquid[0].liqToOx)[i])*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      }
      if (iCmpAl2O3 != -1) dcRefdr[iCmpAl2O3] += ((liquid[iCmpAl2O3+1].liqToOx)[iOxAl2O3]-(liquid[0].liqToOx)[iOxAl2O3])*mOx[i]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);
    }
    if (v == 0.0) return;

    alpha   = dvdt/v;
    v0      = v*exp(alpha*(t-tr));
    v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
    c       = cRef + (t-tr)*dcdt;
    v1      = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
    v2      = d2vdp2;
    denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
    a	    = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
    b	    = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
    sum     = a*a - 4.0*b;

    for (i=0; i<NR; i++) {
      double dalphadr   = d2vdrdt[i]/v - dvdt*dvdr[i]/(v*v);
      double dv0dr      = (dvdr[i] + v*dalphadr*(t-tr))*exp(alpha*(t-tr));      
      double dv1Refdr   = -2.0*v*dvdr[i]*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp))
                          -v*v*(- 1000.0*(cRef*dmwdr[i]+2.0*mw*dcRefdr[i])/(mw*mw*cRef*cRef*cRef) 
			        + 2.0*tr*alpha*dalphadr/(cp) - tr*alpha*alpha*dcpdr[i]/(cp*cp));   
      double dcdr       = dcRefdr[i] + (t-tr)*d2cdrdt[i];
      double dv1dr      = -2.0*v0*dv0dr*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                          -v0*v0*(- 1000.0*(c*dmwdr[i]+2.0*mw*dcdr)/(mw*mw*c*c*c) 
			          + 2.0*t*alpha*dalphadr/(cp) - t*alpha*alpha*dcpdr[i]/(cp*cp));      
      double dv2dr      = d3vdrdp2[i];
      double ddenomdr   = 2.0*dv1Refdr*d3vdp3+2.0*v1Ref*d4vdrdp3[i]-6.0*d2vdp2*d3vdrdp2[i]; 
      double dadr       = (d3vdrdp2[i]*d3vdp3+d2vdp2*d4vdrdp3[i]-dv1Refdr*d4vdp4/2.0-v1Ref*d5vdrdp4[i]/2.0)/denom
                        - (d2vdp2*d3vdp3-v1Ref*d4vdp4/2.0)/(denom*denom)*ddenomdr;
      double dbdr       = (d3vdrdp2[i]*d4vdp4/4.0+d2vdp2*d5vdrdp4[i]/4.0-2.0/3.0*d3vdp3*d4vdrdp3[i])/denom
                        - (d2vdp2*d4vdp4/4.0-d3vdp3*d3vdp3/3.0)/(denom*denom)*ddenomdr;			
      double d3gdrdp2;

      if ((a == 0.0) && (b == 0.0)) {
        d3gdrdp2 = dv2dr;
 
      } else if ((a != 0.0) && (b == 0.0)) {
	printf("*-->Exception in fillD3GDRDP2 (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
        d3gdrdp2 = 0.0;
 
      } else if ((a == 0.0) && (b != 0.0)) {
	printf("*-->Exception in fillD3GDRDP2 (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
        d3gdrdp2 = 0.0;

      } else {	
        d3gdrdp2 = d3gdrdp2MAP(p, pr, v0, v1, v2, a, b, dv0dr, dv1dr, dv2dr, dadr, dbdr);
 
      }
 
      result[i] += coeffCN*d3gdrdp2;
    }
  }
  
#endif /* USE_GHIORSO_KRESS_MODEL */

}

static double fillD3GDT3 (double r[NR], double s[NT], double t, double p) {
  double result;
  int i;

  /* Taylor expansion and standard state terms */
  result = CPconst/(t*t) - DCPDTconst/t;
  for (i=0; i<NR; i++) result += cpr[i]*r[i]/(t*t) - dcpdtr[i]*r[i]/t;
  for (i=0; i<NS; i++) result += cps[i]*s[i]/(t*t) - dcpdts[i]*s[i]/t;
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    int j;
    const double pr         = 1.0;
    const double tr         = 1673.15;
    double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum, denom, coeffCN;
    double dv0dt, dv1dt, d2v0dt2, d2v1dt2, d3v0dt3, d3v1dt3, d3gIntdt3 = 0.0;

    if (fabs(p-pr) < 10.0*DBL_EPSILON) return 0.0;

    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i];

    /* Convert input composition (r) to liquid moles (m)  */
    for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
    
    /* Compute moles and total moles of oxides */
    for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
    if (mOxTot == 0.0) return result;
 
    /* Deal with the special case of FeO1.3 */
    mOx[NA] = 0.0;
    if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
      const double y = 0.3;
      mOx[iOxFeO1_3] = 0.0;
      if (iCmpFe2SiO4_6 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
      }
      if (iCmpFe2AlO4_1 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
      }
    }
 
    for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
      v       += mOx[i]*bulkSystem[i].gk_v;
      dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
      cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
      dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
      cp      += mOx[i]*bulkSystem[i].gk_cp;
      d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      mw      += mOx[i]*bulkSystem[i].mw;
    }
    if (v == 0.0) return result;
 
    alpha   = dvdt/v;
    v0      = v*exp(alpha*(t-tr));
    v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
    c       = cRef + (t-tr)*dcdt;
    v1      = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
    v2      = d2vdp2;
    denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
    a	    = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
    b	    = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
    sum     = a*a - 4.0*b;
    
    dv0dt   = alpha*v*exp(alpha*(t-tr));
    dv1dt   = - 2.0*v0*dv0dt*(1000.0/(mw*c*c) + t*alpha*alpha/(cp)) - v0*v0*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp));
    d2v0dt2 = alpha*alpha*v*exp(alpha*(t-tr));
    d2v1dt2 = - 2.0*(dv0dt*dv0dt+v0*d2v0dt2)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
              - 4.0*v0*dv0dt*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
	      - v0*v0*(6000.0*dcdt*dcdt/(mw*c*c*c*c));
    d3v0dt3   = alpha*alpha*alpha*v*exp(alpha*(t-tr));
    d3v1dt3   = - 2.0*(3.0*dv0dt*d2v0dt2 + v0*d3v0dt3)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
                - 2.0*(dv0dt*dv0dt+v0*d2v0dt2)*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
                - 4.0*(dv0dt*dv0dt + v0*d2v0dt2)*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
	        - 4.0*v0*dv0dt*6000.0*dcdt*dcdt/(mw*c*c*c*c)
	        - 2.0*v0*dv0dt*(6000.0*dcdt*dcdt/(mw*c*c*c*c)) - v0*v0*(-24000.0*dcdt*dcdt*dcdt/(mw*c*c*c*c*c));
  
    if ((a == 0.0) && (b == 0.0)) {
      d3gIntdt3	= d3v0dt3*(p-pr) + d3v1dt3*(p-pr)*(p-pr)/2.0;
      
    } else if ((a != 0.0) && (b == 0.0)) {
      printf("*-->Exception in fillD3GDT3 (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
      d3gIntdt3       = 0.0;
      
    } else if ((a == 0.0) && (b != 0.0)) {
      printf("*-->Exception in fillD3GDT3 (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
      d3gIntdt3       = 0.0;

    } else if (sum > 0.0) {   
      d3gIntdt3 = d3gdt3GMAP(p/10000.0, pr/10000.0, 
                             v0,           v1*10000.0, v2*10000.0*10000.0, a*10000.0, b*10000.0*10000.0, 
			     dv0dt,     dv1dt*10000.0, 
			     d2v0dt2, d2v1dt2*10000.0, 
			     d3v0dt3, d3v1dt3*10000.0)*10000.0;
       
    } else if (sum == 0.0) {
      printf("*-->Exception in fillD3GDT3 (liquid.c). a*a-4*b is equal to zero.\n"); liqERRstate = ERR_SUM_ZERO;
      d3gIntdt3       = 0.0;
 
    } else if(sum < 0.0) {
      d3gIntdt3 = d3gdt3LMAP(p/10000.0, pr/10000.0, 
                             v0,           v1*10000.0, v2*10000.0*10000.0, a*10000.0, b*10000.0*10000.0, 
			     dv0dt,     dv1dt*10000.0, 
			     d2v0dt2, d2v1dt2*10000.0, 
			     d3v0dt3, d3v1dt3*10000.0)*10000.0;
 
    }
	 
    result += coeffCN*d3gIntdt3;
  }
  
#endif /* USE_GHIORSO_KRESS_MODEL */

  return result;
}

static double fillD3GDT2DP (double r[NR], double s[NT], double t, double p) {
  double result;
  int i;

  /* Taylor expansion and standard state terms */
  result = D2VDT2const;
  for (i=0; i<NR; i++) result += d2vdt2r[i]*r[i];
  for (i=0; i<NS; i++) result += d2vdt2s[i]*s[i];
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    int j;
    const double pr         = 1.0;
    const double tr         = 1673.15;
    double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum, denom, coeffCN;
    double dv0dt, dv1dt, d2v0dt2, d2v1dt2, d3gdt2dp;

    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i];

    /* Convert input composition (r) to liquid moles (m)  */
    for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
    
    /* Compute moles and total moles of oxides */
    for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
    if (mOxTot == 0.0) return 0.0;
 
    /* Deal with the special case of FeO1.3 */
    mOx[NA] = 0.0;
    if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
      const double y = 0.3;
      mOx[iOxFeO1_3] = 0.0;
      if (iCmpFe2SiO4_6 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
      }
      if (iCmpFe2AlO4_1 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
      }
    }
 
    for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
      v       += mOx[i]*bulkSystem[i].gk_v;
      dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
      cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
      dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
      cp      += mOx[i]*bulkSystem[i].gk_cp;
      d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      mw      += mOx[i]*bulkSystem[i].mw;
    }
    if (v == 0.0) return result;
 
    alpha   = dvdt/v;
    v0      = v*exp(alpha*(t-tr));
    v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
    c       = cRef + (t-tr)*dcdt;
    v1      = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
    v2      = d2vdp2;
    denom   = 2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2;
    a	    = (denom != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /denom : 0.0;
    b	    = (denom != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/denom : 0.0;
    sum     = a*a - 4.0*b;
    
    dv0dt   = alpha*v*exp(alpha*(t-tr));
    dv1dt   = - 2.0*v0*dv0dt*(1000.0/(mw*c*c) + t*alpha*alpha/(cp)) - v0*v0*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp));
    d2v0dt2 = alpha*alpha*v*exp(alpha*(t-tr));
    d2v1dt2 = - 2.0*(dv0dt*dv0dt+v0*d2v0dt2)*(1000.0/(mw*c*c) + t*alpha*alpha/(cp))
              - 4.0*v0*dv0dt*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp))
	      - v0*v0*(6000.0*dcdt*dcdt/(mw*c*c*c*c));
    d3gdt2dp = 0.0;
  
    if ((a == 0.0) && (b == 0.0)) {
      d3gdt2dp	+= d2v0dt2 + d2v1dt2*(p-pr);
      
    } else if ((a != 0.0) && (b == 0.0)) {
      printf("*-->Exception in fillD3GDT2DP (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
      d3gdt2dp       = 0.0;
      
    } else if ((a == 0.0) && (b != 0.0)) {
      printf("*-->Exception in fillD3GDT2DP (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
      d3gdt2dp       = 0.0;

    } else {   
      d3gdt2dp = d3gdt2dpMAP(p, pr, v0, v1, v2, a, b, dv0dt, dv1dt, d2v0dt2, d2v1dt2);
 
    }
	 
    result += coeffCN*d3gdt2dp;
  }
  
#endif /* USE_GHIORSO_KRESS_MODEL */

  return result;
}

static double fillD3GDTDP2 (double r[NR], double s[NT], double t, double p) {
  double result;
  int i;

  /* Taylor expansion and standard state terms */
  result = D2VDTDPconst;
  for (i=0; i<NR; i++) result += d2vdtdpr[i]*r[i];
  for (i=0; i<NS; i++) result += d2vdtdps[i]*s[i];
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    int j;
    const double pr         = 1.0;
    const double tr         = 1673.15;
    double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum, coeffCN;
    double dv0dt, dv1dt, d3gdtdp2;

    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i];

    /* Convert input composition (r) to liquid moles (m)  */
    for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
    
    /* Compute moles and total moles of oxides */
    for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
    if (mOxTot == 0.0) return result;
 
    /* Deal with the special case of FeO1.3 */
    mOx[NA] = 0.0;
    if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
      const double y = 0.3;
      mOx[iOxFeO1_3] = 0.0;
      if (iCmpFe2SiO4_6 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
      }
      if (iCmpFe2AlO4_1 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
      }
    }
 
    for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
      v       += mOx[i]*bulkSystem[i].gk_v;
      dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
      cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
      dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
      cp      += mOx[i]*bulkSystem[i].gk_cp;
      d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      mw      += mOx[i]*bulkSystem[i].mw;
    }
    if (v == 0.0) return result;
 
    alpha   = dvdt/v;
    v0      = v*exp(alpha*(t-tr));
    v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
    c       = cRef + (t-tr)*dcdt;
    v1      = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
    v2      = d2vdp2;
    a	    = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
    b	    = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
    sum     = a*a - 4.0*b;
    dv0dt   = alpha*v0;
    dv1dt   = - 2.0*v0*v0*alpha*(1000.0/(mw*c*c) + t*alpha*alpha/(cp)) - v0*v0*(-2000.0*dcdt/(mw*c*c*c) + alpha*alpha/(cp));
  
    if ((a == 0.0) && (b == 0.0)) {
      d3gdtdp2 = dv1dt;
      
    } else if ((a != 0.0) && (b == 0.0)) {
      printf("*-->Exception in fillD3GDTDP2 (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
      d3gdtdp2 = 0.0;
      
    } else if ((a == 0.0) && (b != 0.0)) {
      printf("*-->Exception in fillD3GDTDP2 (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
      d3gdtdp2 = 0.0;

    } else {   
      d3gdtdp2 = d3gdtdp2MAP(p, pr, v0, v1, v2, a, b, dv0dt, dv1dt);
 
    }
	 
    result += coeffCN*d3gdtdp2;
  }
  
#endif /* USE_GHIORSO_KRESS_MODEL */

  return result;
}

static double fillD3GDP3 (double r[NR], double s[NT], double t, double p) {
  double result;
  int i;

  /* Taylor expansion and standard state terms */
  result = D2VDP2const;
  for (i=0; i<NR; i++) result += d2vdp2r[i]*r[i];
  for (i=0; i<NS; i++) result += d2vdp2s[i]*s[i];
  
#ifdef USE_GHIORSO_KRESS_MODEL
  {
    int j;
    const double pr         = 1.0;
    const double tr         = 1673.15;
    double m[NA], mOx[NA+1], mOxTot, v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum, coeffCN;
    double d3gdp3;

    for (i=0, coeffCN=1.0; i<NY; i++) coeffCN += (fCN[i]-1.0)*s[NS+i];

    /* Convert input composition (r) to liquid moles (m)  */
    for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
    
    /* Compute moles and total moles of oxides */
    for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
    if (mOxTot == 0.0) return result;
 
    /* Deal with the special case of FeO1.3 */
    mOx[NA] = 0.0;
    if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
      const double y = 0.3;
      mOx[iOxFeO1_3] = 0.0;
      if (iCmpFe2SiO4_6 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
      }
      if (iCmpFe2AlO4_1 != -1) {
   	mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
   	mOxTot         += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
      }
    }
 
    for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
      v       += mOx[i]*bulkSystem[i].gk_v;
      dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
      cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
      dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
      cp      += mOx[i]*bulkSystem[i].gk_cp;
      d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
      d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
      d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
      mw      += mOx[i]*bulkSystem[i].mw;
    }
    if (v == 0.0) return result;
 
    alpha   = dvdt/v;
    v0      = v*exp(alpha*(t-tr));
    v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
    c       = cRef + (t-tr)*dcdt;
    v1      = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
    v2      = d2vdp2;
    a	    = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)     /(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
    b	    = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
    sum     = a*a - 4.0*b;
  
    if ((a == 0.0) && (b == 0.0)) {
      d3gdp3 = v2;
      
    } else if ((a != 0.0) && (b == 0.0)) {
      printf("*-->Exception in fillD3GDP3 (liquid.c). a is greater than zero, b is zero.\n"); liqERRstate = ERR_B_ZERO;
      d3gdp3 = 0.0;
      
    } else if ((a == 0.0) && (b != 0.0)) {
      printf("*-->Exception in fillD3GDP3 (liquid.c). a is zero, b is greater than zero.\n"); liqERRstate = ERR_A_ZERO;
      d3gdp3 = 0.0;

    } else {   
      d3gdp3 = d3gdp3MAP(p, pr, v0, v1, v2, a, b);
 
    }
	 
    result += coeffCN*d3gdp3;
  }
  
#endif /* USE_GHIORSO_KRESS_MODEL */

  return result;
}

static void fillD3GDS2DW (double r[NR], double s[NT], double t, double p, double ***result) {
  int i, j, k, l, m, n, ii, iii;

  /*******************************
   * Parameters: NW WH(), NE H() *
   *             NW WS(), NE S() *
   *             NW WV(), NE V() *
   *******************************/
  for (k=0; k<NT; k++) for (j=0; j<NT; j++) for (i=0; i<(3*NP); i++) result[k][j][i] = 0.0;

  /**************************************
   * NW W parameters solution are first *
   **************************************/
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    for (ii=0; ii<NS; ii++) {
      for (iii=ii; iii<NS; iii++) {
        m = 0;
        for (j=0, m=0; j<NR; j++) {
    	  for (k=j; k<NR; k++, m++) ;
    	  for (k=0; k<NS; k++, m++) ;
        }
        for (j=0; j<NS; j++) {
    	  for (k=j; k<NS; k++, m++) {
	    if ((j == ii) && (k == iii)) {
    	      result[ii][iii][     n] +=	 taylorCoeff[n+NE+1][1+NR+NS+m+1];
    	      result[ii][iii][  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+NS+m+1];
#ifndef USE_GHIORSO_KRESS_MODEL
    	      result[ii][iii][2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+NS+m+1];
#endif /* USE_GHIORSO_KRESS_MODEL */
    	      result[iii][ii][     n] +=	 taylorCoeff[n+NE+1][1+NR+NS+m+1];
    	      result[iii][ii][  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+NS+m+1];
#ifndef USE_GHIORSO_KRESS_MODEL
    	      result[iii][ii][2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+NS+m+1];
#endif /* USE_GHIORSO_KRESS_MODEL */
            }
	  }
    	}
      }
    }
  }

}

static void fillD3GDSDTDW (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j, k, l, m, n, ii;

  /*******************************
   * Parameters: NW WH(), NE H() *
   *             NW WS(), NE S() *
   *             NW WV(), NE V() *
   *******************************/
  for (ii=0; ii<NT; ii++) for (i=0; i<(3*NP); i++) result[ii][i] = 0.0;

  /**************************************
   * NW W parameters solution are first *
   **************************************/
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    for (ii=0; ii<NS; ii++) {
      m = 0;
      for (j=0, m=0; j<NR; j++) {
    	for (k=j; k<NR; k++, m++) ;
    	for (k=0; k<NS; k++, m++) {
	  if (k == ii) result[ii][  NP+n] += -taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j];
	}
      }
      result[ii][  NP+n] += -taylorCoeff[n+NE+1][1+NR+ii+1];
      for (j=0; j<NS; j++) {
    	for (k=j; k<NS; k++, m++) {
	  if (j == ii) result[ii][  NP+n] += -taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[k];
	  if (k == ii) result[ii][  NP+n] += -taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[j];
    	}
      }
    }
  }

  /**************************************
   * NE standard state terms are second *
   **************************************/
  for (i=0; i<NE; i++, n++) {
    for (ii=0; ii<NS; ii++) result[ii][  NP+n] += -taylorCoeff[i+1][1+NR+ii+1];
  }
}

static void fillD3GDRDTDW (double r[NR], double s[NT], double t, double p, double **result) {
  int i, j, k, l, m, n, ii;

  /*******************************
   * Parameters: NW WH(), NE H() *
   *             NW WS(), NE S() *
   *             NW WV(), NE V() *
   *******************************/
  for (ii=0; ii<NR; ii++) for (i=0; i<(3*NP); i++) result[ii][i] = 0.0;

  /**************************************
   * NW W parameters solution are first *
   **************************************/
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    for (ii=0; ii<NR; ii++) {
      result[ii][  NP+n] += -taylorCoeff[n+NE+1][1+ii+1];
      m = 0;
      for (j=0, m=0; j<NR; j++) {
    	for (k=j; k<NR; k++, m++) {
	  if (j == ii) result[ii][  NP+n] += -taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[k];
	  if (k == ii) result[ii][  NP+n] += -taylorCoeff[n+NE+1][1+NR+NS+m+1]*r[j];
    	}
    	for (k=0; k<NS; k++, m++) {
	  if (j == ii) result[ii][  NP+n] += -taylorCoeff[n+NE+1][1+NR+NS+m+1]*s[k];
	}
      }
    }
  }

  /**************************************
   * NE standard state terms are second *
   **************************************/
  for (i=0; i<NE; i++, n++) {
    for (ii=0; ii<NR; ii++) result[ii][  NP+n] += -taylorCoeff[i+1][1+ii+1];
  }
}

static void fillD3GDRDSDW (double r[NR], double s[NT], double t, double p, double ***result) {
  int i, j, k, l, m, n, ii, iii;

  /*******************************
   * Parameters: NW WH(), NE H() *
   *             NW WS(), NE S() *
   *             NW WV(), NE V() *
   *******************************/
  for (iii=0; iii<NR; iii++) for (ii=0; ii<NT; ii++) for (i=0; i<(3*NP); i++) result[iii][ii][i] = 0.0;

  /**************************************
   * NW W parameters solution are first *
   **************************************/
  for (i=0, n=0; i<NE; i++) for (l=i+1; l<NE; l++, n++) {
    for (ii=0; ii<NR; ii++) {
      for (iii=0; iii<NS; iii++) {
        m = 0;
        for (j=0, m=0; j<NR; j++) {
    	  for (k=j; k<NR; k++, m++) ;
    	  for (k=0; k<NS; k++, m++) {
	    if ((j == ii) && (k == iii)) {
    	      result[ii][iii][     n] +=         taylorCoeff[n+NE+1][1+NR+NS+m+1];
    	      result[ii][iii][  NP+n] +=      -t*taylorCoeff[n+NE+1][1+NR+NS+m+1];
#ifndef USE_GHIORSO_KRESS_MODEL
    	      result[ii][iii][2*NP+n] += (p-1.0)*taylorCoeff[n+NE+1][1+NR+NS+m+1];
#endif /* USE_GHIORSO_KRESS_MODEL */
    	    }
	  }
        }
      }
    }
  }

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
  
#ifdef DEBUG
  printf("Call to initialGuessOrdering in liquid.c\n");
#endif
  if (sCorr == NULL) sCorr = (double *) malloc((size_t) NS*sizeof(double));

  for (i=0; i<NS; i++)  s[i] = 0.0;
  for (i=NS; i<NT; i++) s[i] = 1.0/(((double) NY)+1.0);

#ifdef NEVER_DEFINED /* BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION */
  /*
   * This code block is executed for the special case of data along the Na2O-Al2O3 join
   * ... the test to enter this block is that the SiO2 concentration is negative because
   *     sodium is present as Na4SiO4 but there is no silica in the system.
   *     We also require Ca2SiO4, K2SiO3, and H2O concentrations to be zero.
   */
  if (((1.0-r[0]-r[1]-r[2]-r[3]-r[4]) < 0.0) && (r[1] == 0.0) && (r[3] == 0.0) && (r[4] == 0.0)) {
    static const int xSiO2_2        =  0;
    static const int xNa4SiO4_2_5   =  3;
    static const int nNaAlSiO4_2_3  =  1;
    static const int nNaAlSi3O8_2_5 =  4;
    static const int nNa2SiO3_2_3   = 11;
    static const int nNaAlO2        = 12;
    static const int nNa2Si2O5_1_2  = 14;
    static const int nNaAl2SiO7_2_7 = 17;
    static const int nAl6Si2O13_1_4 = 19;
    double inc = 0.1;
    double nSi = (1.0-r[0]-r[1]-r[2]-r[3]-r[4])*2.0 + r[1]*2.0/3.0 + r[2]*2.0/5.0 + r[3]*2.0/3.0;
    double nAl = 2.0*r[0];
    double nNa = 4.0*r[2]*2.0/5.0;
    while (!rANDsTOx (r, s) && (fabs(inc) > sqrt(DBL_EPSILON)) ) {
      if      ((xSpecies[     xSiO2_2] < 0.0) && (inc < 0.0)) inc /= -2.0;
      else if ((xSpecies[xNa4SiO4_2_5] < 0.0) && (inc > 0.0)) inc /= -2.0;
      s[nNaAlSiO4_2_3 ]  = 1e-4;
      s[nNaAlSi3O8_2_5]  = 1e-4;
      s[nNa2SiO3_2_3  ]  = 1e-4;
      s[nNaAlO2       ] += inc;
      s[nNa2Si2O5_1_2 ]  = 1e-4;
      s[nNaAl2SiO7_2_7] += inc;
      s[nAl6Si2O13_1_4]  = 1e-4;
#ifdef DEBUG
      printf("...Special case (Na2O-Al2O3 join): Attempt to generate an initial feasible solution with inc = %g\n", inc);
#endif
    }
#ifdef DEBUG
    printf("Results of call to initialGuessOrdering (Special case along the Na2O-Al2O3 join):\n");
    printf("   %20.20s %13.13s %13.13s %13.13s\n", "Species", "Mole frac", "r", "s");
    printf("   %20.20s %13.6g\n", liquid[0].label, xSpecies[0]);
    for (i=0;  i<NR; i++) printf("   %20.20s %13.6g %13.6g\n", liquid[i+1].label, xSpecies[i+1], r[i]);
    for (i=0;  i<NS; i++) printf("   %20.20s %13.6g %13.13s %13.6g\n", liquid[i+NA].label, xSpecies[i+NA], "", s[i]);
    for (i=NS; i<NT; i++) printf("   %20.20s %13.13s %13.13s %13.6g\n", "order CN[*]", "", "", s[i]);
#endif
    return;
  }
#endif

  if (!rANDsTOx (r, s)) {
#ifdef BUILD_MGO_SIO2_VERSION
    static const int indexCon[] = { 0, 1 };
                                  /* [ 0] SiO2 [ 1] MgO */
    static const int nCon = 2;
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
    static const int indexCon[] = { 0, 1, 2, 3, 4, 5 };
                                  /* [ 0] SiO2 [ 1] Al2O3 [ 2] CaO [ 3] Na2O [ 4] K2O [ 5] H2O */
    static const int nCon = 6;
#else
    static const int indexCon[] = { 0, 2, 3, 5, 7, 10, 11, 12, 14 };
                                  /* [ 0] SiO2 [ 2] Al2O3 [ 3] Fe2O3 [ 5] FeO [ 7] MgO [10] CaO [11] Na2O [12] K2O [14] H2O */
    static const int nCon = 9;
#endif
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
      double dp2[NT],          /* d2s[NT]/dp2            BINARY MASK: 001000000000 */
      double dw[NT][3*NP],     /* ds[NT]/dw[3*NP]        BINARY MASK: 010000000000 */
      double dtw[NT][3*NP]     /* ds[NT]/dtdw[3*NP]      BINARY MASK: 100000000000 */
     )
{
  static double tOld = -9999.0;
  static double pOld = -9999.0;
  static double *rOld, *sOld, **ptToD2gds2, **d2gds2, **ptToD2gds2Copy, **d2gds2Copy, dLU;
  static ModelParameters *shadowParameters;
  static EosModelParameters *eosShadowParameters;
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
    shadowParameters = (ModelParameters *) calloc((size_t) NP, sizeof(ModelParameters));
    eosShadowParameters = (EosModelParameters *) calloc((size_t) nc, sizeof(EosModelParameters));
    indexLU = ivector(1, NT);
  }
  
  /* default value for update is FALSE */ 
  for (i=0; i<NP; i++) {                             /* check if modelparameters are changing (independent of t, p) */
    if (modelParameters[i].activeH && (modelParameters[i].enthalpy != shadowParameters[i].enthalpy)) { update |= TRUE; 
      shadowParameters[i].enthalpy = modelParameters[i].enthalpy; }
    if (modelParameters[i].activeS && (modelParameters[i].entropy  != shadowParameters[i].entropy )) { update |= TRUE; 
      shadowParameters[i].entropy  = modelParameters[i].entropy;  }
    if (modelParameters[i].activeV && (modelParameters[i].volume   != shadowParameters[i].volume  )) { update |= TRUE; 
      shadowParameters[i].volume   = modelParameters[i].volume ;  }
  }

  for (i=0; i<nc; i++) {                             /* check if modelparameters are changing (independent of t, p) */
    if (eosModelParameters[i].activeKp   && (eosModelParameters[i].Kp   != eosShadowParameters[i].Kp  )) { update |= TRUE; eosShadowParameters[i].Kp   = eosModelParameters[i].Kp  ; }
    if (eosModelParameters[i].activeKpp  && (eosModelParameters[i].Kpp  != eosShadowParameters[i].Kpp )) { update |= TRUE; eosShadowParameters[i].Kpp  = eosModelParameters[i].Kpp ; }
    if (eosModelParameters[i].activeKppp && (eosModelParameters[i].Kppp != eosShadowParameters[i].Kppp)) { update |= TRUE; eosShadowParameters[i].Kppp = eosModelParameters[i].Kppp; }
  }

  update |= (t != tOld);
  update |= (p != pOld);
  if (update) loadTaylorCoefficients(t, p);         /* if T, P, or modelParameters change                    */
  for (i=0; i<NR; i++) update |= (r[i] != rOld[i]); 
  
  /* look-up or compute the current ordering state */
  if (update) {                                     /* if T, P, modelParameters or liquid composition change */
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
  if (mask & ELEVENTH ) {   /* compute ds/dw:  */
    double *s = sOld;
    double temp[NT];
    
    fillD2GDSDW (r, s, t, p, d2gdsdw);
    for (j=0; j<NP; j++) {
      for (i=0; i<NT; i++) temp[i] = d2gdsdw[i][     j];
      lubksb(ptToD2gds2, NT, indexLU, temp-1);
      for (i=0; i<NT; i++) dw[i][     j] = (s[i] > 0.0) ? -temp[i] : 0.0;
      for (i=0; i<NT; i++) temp[i] = d2gdsdw[i][  NP+j];
      lubksb(ptToD2gds2, NT, indexLU, temp-1);
      for (i=0; i<NT; i++) dw[i][  NP+j] = (s[i] > 0.0) ? -temp[i] : 0.0;
      for (i=0; i<NT; i++) temp[i] = d2gdsdw[i][2*NP+j];
      lubksb(ptToD2gds2, NT, indexLU, temp-1);
      for (i=0; i<NT; i++) dw[i][2*NP+j] = (s[i] > 0.0) ? -temp[i] : 0.0;
    }
    
  }
  if (mask & TWELFTH ) {   /* compute ds/dtdw:  */
    double *s = sOld;
    double temp[NT], dsdw[NT][3*NP], dsdt[NT];
    
    fillD2GDSDW (r, s, t, p, d2gdsdw);
    for (j=0; j<NP; j++) {
      for (i=0; i<NT; i++) temp[i] = d2gdsdw[i][     j];
      lubksb(ptToD2gds2, NT, indexLU, temp-1);
      for (i=0; i<NT; i++) dsdw[i][     j] = (s[i] > 0.0) ? -temp[i] : 0.0;
      for (i=0; i<NT; i++) temp[i] = d2gdsdw[i][  NP+j];
      lubksb(ptToD2gds2, NT, indexLU, temp-1);
      for (i=0; i<NT; i++) dsdw[i][  NP+j] = (s[i] > 0.0) ? -temp[i] : 0.0;
      for (i=0; i<NT; i++) temp[i] = d2gdsdw[i][2*NP+j];
      lubksb(ptToD2gds2, NT, indexLU, temp-1);
      for (i=0; i<NT; i++) dsdw[i][2*NP+j] = (s[i] > 0.0) ? -temp[i] : 0.0;
    }
    
    fillD2GDSDT (r, s, t, p, d2gdsdt);
    for (i=0; i<NT; i++) temp[i] = d2gdsdt[i];   
    lubksb(ptToD2gds2, NT, indexLU, temp-1);
    for (i=0; i<NT; i++) dsdt[i] = (s[i] > 0.0) ? -temp[i] : 0.0;
    
    fillD3GDSDTDW (r, s, t, p, d3gdsdtdw);
    fillD3GDS2DW  (r, s, t, p, d3gds2dw);
    fillD3GDS2DT  (r, s, t, p, d3gds2dt);
    fillD3GDS3    (r, s, t, p, d3gds3);
    for (j=0; j<NP; j++) {
      for (i=0; i<NT; i++) {
        int k, l;
        temp[i] = d3gdsdtdw[i][j];
	for (k=0; k<NT; k++) {
	  temp[i] += d3gds2dw[i][k][j]*dsdt[k] + d3gds2dt[i][k]*dsdw[k][j];
	  for (l=0; l<NT; l++) temp[i] += d3gds3[i][k][l]*dsdt[k]*dsdw[l][j];
	}
      }
      lubksb(ptToD2gds2, NT, indexLU, temp-1);
      for (i=0; i<NT; i++) dtw[i][j] = (s[i] > 0.0) ? -temp[i] : 0.0;
      for (i=0; i<NT; i++) {
        int k, l;
        temp[i] = d3gdsdtdw[i][j+NP];
	for (k=0; k<NT; k++) {
	  temp[i] += d3gds2dw[i][k][j+NP]*dsdt[k] + d3gds2dt[i][k]*dsdw[k][j+NP];
	  for (l=0; l<NT; l++) temp[i] += d3gds3[i][k][l]*dsdt[k]*dsdw[l][j+NP];
	}
      }
      lubksb(ptToD2gds2, NT, indexLU, temp-1);
      for (i=0; i<NT; i++) dtw[i][j+NP] = (s[i] > 0.0) ? -temp[i] : 0.0;
      for (i=0; i<NT; i++) {
        int k, l;
        temp[i] = d3gdsdtdw[i][j+2*NP];
	for (k=0; k<NT; k++) {
	  temp[i] += d3gds2dw[i][k][j+2*NP]*dsdt[k] + d3gds2dt[i][k]*dsdw[k][j+2*NP];
	  for (l=0; l<NT; l++) temp[i] += d3gds3[i][k][l]*dsdt[k]*dsdw[l][j+2*NP];
	}
      }
      lubksb(ptToD2gds2, NT, indexLU, temp-1);
      for (i=0; i<NT; i++) dtw[i][j+2*NP] = (s[i] > 0.0) ? -temp[i] : 0.0;
    }
    
  }

}

/*
 *=============================================================================
 * Public functions:
 *    t       -  Temperature (K)
 *    p       -  Pressure (bars)
 *    *r      -  (pointer to x[]) Array of independent compositional variables
 */

double /* returns 1 + a (p-pr) + b (p-pr)^2 */
retLiqEosParam (double r[NR], double t, double p,
  double *v1Ret, /* dv/dp   at reference temperature and 1 bar */
  double *v2Ret, /* d2v/dp2 at reference temperature and 1 bar */
  double *v3Ret, /* d3v/dp3 at reference temperature and 1 bar */
  double *v4Ret, /* d4v/dp4 at reference temperature and 1 bar */
  double *aRet,  /* a = f(v1,v2,v3,v4)                         */
  double *bRet)  /* b = f(v1,v2,v3,v4)                         */ 
{
  const double pr	  = 1.0;
  const double tr	  = 1673.15;
  double m[NA], mOx[NA+1], mOxTot, v, dvdt, cRef, mw, cp, d2vdp2, d3vdp3, d4vdp4, v1Ref, alpha, a, b;
  double s[NT];
  int i, j;
  double result = 0.0;

  liqERRstate = ERR_NONE;
  MTHREAD_ONCE(&initThreadBlock, threadInit);
  
  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot == 0.0) return result;
 
  order(FIRST, t, p, r, s, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  /* Deal with the special case of FeO1.3 */
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }
 
  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    v	    += mOx[i]*bulkSystem[i].gk_v;
    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    cp      += mOx[i]*bulkSystem[i].gk_cp;
    d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    mw      += mOx[i]*bulkSystem[i].mw;
  }
  if (v == 0.0) return result;
 
  alpha   = dvdt/v;
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  a	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)	 /(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
  b	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;

  *v1Ret = v1Ref;
  *v2Ret = d2vdp2;
  *v3Ret = d3vdp3;
  *v4Ret = d4vdp4;
  *aRet  = a;
  *bRet  = b;
  return (1.0 + a*(p-pr) + b*(p-pr)*(p-pr));
}

typedef struct _eosRefParameters {
  double v, dvdt, cRef, dcdt, cp, d2vdp2, d3vdp3, d4vdp4, mw;
  double alpha, v0, v1, v2, v3, v4, a, b;
  double K, Kp, Kpp, Kppp;    
} EosRefParameters;

EosRefParameters *getEosRefParameters(double *r) {
  static EosRefParameters eos;
  double s[NT];
  const double tr = 1673.15;
  const double pr = 1.0;
  double m[NA], mOx[NA+1], mOxTot, denom;
  int i, j;
  
  liqERRstate = ERR_NONE;
  MTHREAD_ONCE(&initThreadBlock, threadInit);
  
  eos.v      = 0.0; eos.dvdt   = 0.0; eos.cRef   = 0.0; eos.dcdt = 0.0; eos.cp = 0.0; 
  eos.d2vdp2 = 0.0; eos.d3vdp3 = 0.0; eos.d4vdp4 = 0.0; eos.mw   = 0.0;
  eos.alpha  = 0.0; eos.v0     = 0.0; eos.v1     = 0.0; eos.v2   = 0.0; eos.a  = 0.0; eos.b = 0.0;
  eos.K      = 0.0; eos.Kp     = 0.0; eos.Kpp    = 0.0; eos.Kppp = 0.0;    
  
  /* Convert input composition (r) to liquid moles (m)  */
  for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
  
  /* Compute moles and total moles of oxides */
  for (i=0, mOxTot=0.0; i<nc; i++) { for (j=0, mOx[i]=0.0; j<NA; j++) mOx[i] += m[j]*(liquid[j].liqToOx)[i]; mOxTot += mOx[i]; }
  if (mOxTot < 100.0*DBL_EPSILON) return &eos;
  
  order(FIRST, tr, pr, r, s, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
  /* Deal with the special case of FeO1.3 */
  mOx[NA] = 0.0;
  if ((iOxFe2O3 != -1) && (iOxFeO != -1) && (iOxFeO1_3 != -1)) {
    const double y = 0.3;
    mOx[iOxFeO1_3] = 0.0;
    if (iCmpFe2SiO4_6 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2SiO4_6]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2SiO4_6]*nSpecies;
    }
    if (iCmpFe2AlO4_1 != -1) {
      mOx[iOxFeO1_3] += 2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFe2O3]  -= y*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOx[iOxFeO]    -= (1.0-2.0*y)*2.0*s[iCmpFe2AlO4_1]*nSpecies;
      mOxTot	     += 2.0*y*s[iCmpFe2AlO4_1]*nSpecies;
    }
  }
 
  for (i=0; i<((iOxFeO1_3 != -1) ? nc+1 : nc); i++) {
    eos.v	+= mOx[i]*bulkSystem[i].gk_v;
    eos.dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
    eos.cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + ((iOxAl2O3 != -1) ? mOx[i]*mOx[iOxAl2O3]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot) : 0.0);
    eos.dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
    eos.cp      += mOx[i]*bulkSystem[i].gk_cp;
    eos.d2vdp2  += mOx[i]*(bulkSystem[i].gk_d2vdp2 + eosModelParameters[i].v2);
    eos.d3vdp3  += mOx[i]*(bulkSystem[i].gk_d3vdp3 + eosModelParameters[i].v3);
    eos.d4vdp4  += mOx[i]*(bulkSystem[i].gk_d4vdp4 + eosModelParameters[i].v4);
    eos.mw      += mOx[i]*bulkSystem[i].mw;
  }
  if (eos.v < 100.0*DBL_EPSILON) return &eos;
 
  eos.alpha = eos.dvdt/eos.v;
  eos.v0    = eos.v;
  eos.v1    = -eos.v*eos.v*(1000.0/(eos.mw*eos.cRef*eos.cRef) + tr*eos.alpha*eos.alpha/eos.cp);
  eos.v2    = eos.d2vdp2;
  eos.v3    = eos.d3vdp3;
  eos.v4    = eos.d4vdp4;
  denom     = 2.0*eos.v1*eos.d3vdp3-3.0*eos.d2vdp2*eos.d2vdp2;
  eos.a	    = (denom) ? (eos.d2vdp2*eos.d3vdp3 - eos.v1*eos.d4vdp4/2.0)        /denom : 0.0;
  eos.b	    = (denom) ? (eos.d2vdp2*eos.d4vdp4/4.0 - eos.d3vdp3*eos.d3vdp3/3.0)/denom : 0.0;
  
  eos.K    = -eos.v0/eos.v1;
  eos.Kp   = eos.v2*eos.K*eos.K/eos.v0 - 1.0;
  eos.Kpp  = (eos.v3*eos.K*eos.K*eos.K/eos.v0 + (2.0*eos.Kp+1.0)*(eos.Kp+1.0))/eos.K;
  eos.Kppp = (eos.v4*eos.K*eos.K*eos.K*eos.K/eos.v0 + eos.Kpp*eos.K*(4.0+6.0*eos.Kp) 
              - (3.0*eos.Kp+1.0)*(2.0*eos.Kp+1.0)*(eos.Kp+1.0))
	     /(eos.K*eos.K);
	     
  return &eos;
}

/* function utilized by conLiq and test_eos for high-P ferric/ferrous calculation */

double integralV_GKsp(int index, double t, double p) {
  const double pr = 1.0;
  const double tr = 1673.15;
  double v, dvdt, cRef, c, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b, sum;
  double gInt;

  if (fabs(p-pr) < 10.0*DBL_EPSILON) return (double) 0.0;
 
  v	  = bulkSystem[index].gk_v;
  dvdt    = bulkSystem[index].gk_dvdt;
  cRef    = bulkSystem[index].gk_c;
  dcdt    = bulkSystem[index].gk_dcdt;
  cp	  = bulkSystem[index].gk_cp;
  d2vdp2  = bulkSystem[index].gk_d2vdp2 + eosModelParameters[index].v2;
  d3vdp3  = bulkSystem[index].gk_d3vdp3 + eosModelParameters[index].v3;
  d4vdp4  = bulkSystem[index].gk_d4vdp4 + eosModelParameters[index].v4;
  mw	  = bulkSystem[index].mw;
    
  if (v == 0.0) return 0.0;
 
  alpha   = dvdt/v;
  v0	  = v*exp(alpha*(t-tr));
  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
  c	  = cRef + (t-tr)*dcdt;
  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
  v2	  = d2vdp2;
  a	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)	 /(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
  b	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
  sum	  = a*a - 4.0*b;    
  gInt    = 0.0;

  if ((a == 0.0) && (b == 0.0)) {
    gInt      += v0*(p-pr) + v1*(p-pr)*(p-pr)/2.0 + v2*(p-pr)*(p-pr)*(p-pr)/6.0;
    
  } else if ((a != 0.0) && (b == 0.0)) {
    gInt      += (v0 - v2/(2.0*a*a))*(p-pr) + (v1 + v2/(2.0*a))*(p-pr)*(p-pr)/2.0 + v2*log(1.0+a*(p-pr))/(2.0*a*a*a);
    
  } else if ((a == 0.0) && (b != 0.0)) {
    gInt      += (v0 + v2/(2.0*b))*(p-pr) + v1*log(1.0 + b*(p-pr)*(p-pr))/(2.0*b);
    gInt      += (b > 0.0) ? -v2*atan(sqrt(b)*(p-pr))/(2.0*b*sqrt(b)) : -v2*log((1.0+sqrt(-b)*(p-pr))/(1.0-sqrt(-b)*(p-pr)))/(4.0*b*sqrt(-b));

  } else if (sum > 0.0) {
    double x = sqrt(sum);
    double y = (a + 2.0*b*(p-pr))/x;
    double z = a/x;
    double PcA = (2.0*b*pr - a + x)/(2.0*b);
    double PcB = (2.0*b*pr - a - x)/(2.0*b);
    double arg = (1.0 + y)*(1.0 - z)/((1.0 - y)*(1.0 + z));
    
    if (((pr < PcA) && (PcA < p)) || ((pr < PcB) && (PcB < p))) fprintf(stderr, "index %d, v %g,alpha %g, v1Ref %g, v1 %g\nc %g, v2 %g, a %g, b %g\n", index, v, alpha, v1Ref, v1, c, v2, a, b);
    if (((pr < PcA) && (PcA < p)) || ((pr < PcB) && (PcB < p))) printERR("integralV_GKsp", ERR_SUM_GT_ZERO, "1.0+a*(p-pr)+b*(p-pr)*(p-pr)", 1.0+a*(p-pr)+b*(p-pr)*(p-pr))
    if (arg <= 0.0)						printERR("integralV_GKsp", ERR_SUM_GT_ZERO, "arg", arg)
    
    gInt      += (v0 + a*v1/b + v2/(2.0*b))*(p-pr);
    gInt      += (v1*(1.0-a*a/b) - v2*a/(2.0*b))*log(1.0+a*(p-pr)+b*(p-pr)*(p-pr))/(2.0*b);
    gInt      += (v1*a*(3.0-a*a/b) + v2*(1.0 - a*a/(2.0*b)))*log(arg)/(2.0*b*x);
    
  } else if (sum == 0.0) {
    gInt      += (v0 + 4.0*v1/a + 2.0*v2/(a*a))*(p-pr);
    gInt      += -8.0*(v2/a + v1)/(a*a*(2.0+a*(p-pr))) + 4.0*(v2/a + v1)/(a*a);
    gInt      += -4.0*(3.0*v1 + 2.0*v2/a)*log(1.0 + a*(p-pr)/2.0)/(a*a);
    
  } else if(sum < 0.0) {
    double x = sqrt(-sum);
    double y = (a + 2.0*b*(p-pr))/x;
    double z = a/x;
    
    gInt      += (v0 + a*v1/b + v2/(2.0*b))*(p-pr);
    gInt      += (v1*(1.0-a*a/b) - v2*a/(2.0*b))*log(1.0+a*(p-pr)+b*(p-pr)*(p-pr))/(2.0*b);
    gInt      += (v1*a*(3.0-a*a/b) + v2*(1.0 - a*a/(2.0*b)))*atan((z-y)/(1.0+z*y))/(b*x);
    
  }
  
  return gInt;
}

/*
 *=============================================================================
 * Public functions:
 *    inpMask -  bitwise mask for specifying input parameters
 *    outMask -  bitwise mask for selecting output
 *    mask    -  bitwise mask for selecting output
 *    t       -  Temperature (K)
 *    p       -  Pressure (bars)
 *    *r      -  (pointer to x[]) Array of independent compositional variables
 */

void
conLiq(int inpMask, int outMask, double t, double p, 
  double *o,      /* comp of liquid in moles of oxides                        */
  double *m,      /* comp of liquid in moles of endmember components          */
  double *r,      /* comp of liquid in terms of the independent comp var      */
  double *x,      /* comp of liquid in mole fractions of endmember components */
  double **dm,    /* Jacobian matrix: dm[i][j] = dr[i]/dm[j]                  */
  double ***d2m,  /* vector of matrices: d2m[i][j][k] = d2r[i]/dm[j]dm[k]     */
  double *logfo2) /* base 10 logarithm of the oxygen fugacity                 */
{
  /*--------------------------------------------------------------------------- 
  Not all combinations of inpMask and outMask are feasible. Valid 
    combinations are:

       inpMask          outMask
  (1)  FIRST | SEVENTH  FIRST
  (2)  FIRST            SEVENTH
  (3)  SECOND           THIRD | FOURTH | FIFTH | SIXTH
  (4)  THIRD            FOURTH
  (5)  THIRD            FOURTH | EIGHTH
  (6)  THIRD            FOURTH | NINTH

  (1) converts a vector of moles of oxides into a vector of moles of oxides
      with the correct redox state for the given t, p, and logfo2. Note that
      the original vector is used as output.
  (2) calculates from a vector of moles of oxides and the given t and p, the
      appropriate logfo2
  (3) calculates from a vector of moles of endmember components, one or
      all of: r[], x[], dr[]/dm[], or d2r[]/dm[]dm[]
  (4) calculates from a vector of independent compositional variables
      mole fractions of endmember components
  (5) calculates from a vector of independent compositional variables
      mole fractions of endmember species
  (6) calculates from a vector of independent compositional variables
      fraction of system in CN state (vector 0 ... NT-1)
  ----------------------------------------------------------------------------*/
      
  int i, j, k;
  
  liqERRstate = ERR_NONE;
  
  if ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS)) { conLiq_v34(inpMask, outMask, t, p, o, m, r, x, dm, d2m, logfo2); return; }
  
  MTHREAD_ONCE(&initThreadBlock, threadInit);

  if (inpMask & FIRST) {
#ifdef BUILD_MGO_SIO2_VERSION  
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
#else
    /*-------------------------------------------------------------------------
      Oxide+logfo2 -> oxide or oxide -> logfo2. The algorithm used is that 
      given by:
      Kress, VC and Carmichael, ISE (1991) The compressibility of silicate
        liquids containing Fe2O3 and the effect of composition, temperature,
        oxygen fugacity and pressure on their redox states.
        Contributions to Mineralogy and Petrology (in press)
      Coefficients for the oxides are initialized in LIQ_STRUCT_DATA.H        
    --------------------------------------------------------------------------*/
    static int indexFeO = 0, indexFe2O3 = 0;
#ifdef USE_KRESS_CARMICHAEL_FO2
    static const double t0 = 1673.15,                      /* K       */
                         a =    0.196,
                         b =    1.1492e4,                  /* K       */
                         c =   -6.675,
                         e =   -3.364,
                         f =   -7.01e-7  * 1.0e5,          /* K/bar   */
                         g =   -1.54e-10 * 1.0e5,          /* 1/bar   */
                         h =    3.85e-17 * 1.0e5 * 1.0e5;  /* K/bar^2 */
#endif /* USE_KRESS_CARMICHAEL_FO2 */
    double sum = 0.0, temp; 

    if (indexFeO == 0 || indexFe2O3 == 0) {
      for (i=0; i<nc; i++) { 
        if (bulkSystem[i].type == FEO)   indexFeO   = i;
        if (bulkSystem[i].type == FE2O3) indexFe2O3 = i;
      }
      if (indexFeO == 0 || indexFe2O3 == 0) {
         printf("Fatal error in conLiq (LIQUID.C)\n");
         printf("The oxides FeO and Fe2O3 cannot be identified.\n");
         return;
      }
    }
#endif /* BUILD_*_VERSION */

    if (inpMask == (FIRST | SEVENTH)  && outMask == FIRST) { 
      /*----------------------------------------------------------------------
        Converts a vector of moles of oxides (as defined in LIQ_STRUCT_DATA.H
        for the structure bulkSystem) into a vector of moles of oxides with
        the correct redox state (ferric/ferrous ratio) for the given bulk
        composition, t and p. 
      ------------------------------------------------------------------------*/

#ifdef BUILD_MGO_SIO2_VERSION  
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
#else
      o[indexFeO]   += 2.0*o[indexFe2O3];
      o[indexFe2O3]  = 0.0;
      if (o[indexFeO] == 0.0) return;

      for (i=0; i<nc; i++) sum += o[i];
      if (sum == 0.0) return;

#ifdef USE_KRESS_CARMICHAEL_FO2
      if (p < 50000.0) temp = a*log(10.0)*(*logfo2) + b/t + c + e*(1.0 - t0/t - log(t/t0))
                            + f*p/t + g*(t-t0)*p/t + h*SQUARE(p)/t;
      else             temp = a*log(10.0)*(*logfo2) + b/t + c + e*(1.0 - t0/t - log(t/t0))
                            + f*50000.0/t + g*(t-t0)*50000.0/t + h*SQUARE(50000.0)/t
			    - a*log(10.0)*(608.966*p/10000.0-608.966*5.0)/t;
	   
      for (i=0; i<nc; i++) temp += bulkSystem[i].coeff*o[i]/sum;
      temp = exp(temp);

      o[indexFe2O3]  = temp*o[indexFeO]/(1.0 + 2.0*temp);
      o[indexFeO]   -= 2.0*o[indexFe2O3];
#else
      {
        double y = 0.3;
        double intVFe2O3  = integralV_GKsp(iOxFe2O3,  t, p);
	double intVFeO    = integralV_GKsp(iOxFeO,    t, p);
	double intVFeO1_3 = integralV_GKsp(iOxFeO1_3, t, p);
	double deltaG = -106200.0 - t*(-55.1) + 31.86*(t - 1673.15 - t*log(t/1673.15)) + intVFe2O3/2.0 - intVFeO;
	double KD1 = exp(-deltaG/(R*t)
		         -(39860.0*o[iOxAl2O3] - 62520.0*o[iOxCaO] - 102000.0*o[iOxNa2O] - 119000.0*o[iOxK2O])/(R*t*sum));
	double K2 = 0.4*exp(-(intVFeO1_3 - (1.0-2.0*y)*intVFeO - y*intVFe2O3)/(R*t));
	double fo2 = exp((*logfo2)*log(10.0));
	
	temp =  (KD1*pow(fo2, (double) 0.25) + 2.0*y*K2*pow(KD1, 2.0*y)*pow(fo2, y/2.0))
	       /(1.0 + (1.0-2.0*y)*K2*pow(KD1, 2.0*y)*pow(fo2, y/2.0));

        o[indexFe2O3]  = o[indexFeO]*(1.0-1.0/(1.0+temp))/2.0;
        o[indexFeO]   -= 2.0*o[indexFe2O3];
      }
#endif /* USE_KRESS_CARMICHAEL_FO2 */
#endif /* BUILD_*_VERSION */

    } else if (inpMask == FIRST && outMask == SEVENTH) {
      /*----------------------------------------------------------------------
        Calculates from the given t and p and a vector of moles of oxides 
        (as defined in LIQ_STRUCT_DATA.H for the structure bulkSystem) the 
        appropriate log10fo2 for the given t and p. 
      ------------------------------------------------------------------------*/

#ifdef BUILD_MGO_SIO2_VERSION  
      *logfo2 = 0.0; 
      return;
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
      *logfo2 = 0.0; 
      return;
#else
      if (o[indexFeO] == 0.0 || o[indexFe2O3] == 0.0) { *logfo2 = 0.0; return; }
      for (i=0; i<nc; i++) sum += o[i]; 
      sum += o[indexFe2O3];
      if (sum == 0.0) { *logfo2 = 0.0; return; }
      
#ifdef USE_KRESS_CARMICHAEL_FO2      
      if (p< 50000.0) temp = b/t + c + e*(1.0 - t0/t - log(t/t0)) + f*p/t + g*(t-t0)*p/t + h*SQUARE(p)/t;
      else            temp = b/t + c + e*(1.0 - t0/t - log(t/t0)) + f*50000.0/t + g*(t-t0)*50000.0/t + h*SQUARE(50000.0)/t
                             - a*log(10.0)*(608.966*p/10000.0-608.966*5.0)/t;
      for (i=0; i<nc; i++) temp += bulkSystem[i].coeff*o[i]/sum;
      temp += 2.0*bulkSystem[indexFeO].coeff*o[indexFe2O3]/sum
                - bulkSystem[indexFe2O3].coeff*o[indexFe2O3]/sum;
      *logfo2 = (log(o[indexFe2O3]/o[indexFeO]) - temp)/(a*log(10.0));
#else
      {
        double y = 0.3;
        double intVFe2O3  = integralV_GKsp(iOxFe2O3,  t, p);
	double intVFeO    = integralV_GKsp(iOxFeO,    t, p);
	double intVFeO1_3 = integralV_GKsp(iOxFeO1_3, t, p);
	double deltaG = -106200.0 - t*(-55.1) + 31.86*(t - 1673.15 - t*log(t/1673.15)) + intVFe2O3/2.0 - intVFeO;
	double KD1 = exp(-deltaG/(R*t)
		         -(39860.0*o[iOxAl2O3] - 62520.0*o[iOxCaO] - 102000.0*o[iOxNa2O] - 119000.0*o[iOxK2O])/(R*t*sum));
	double K2 = 0.4*exp(-(intVFeO1_3 - (1.0-2.0*y)*intVFeO - y*intVFe2O3)/(R*t));
	int converged = FALSE;
	int iter = 0;
	
	*logfo2 = -10.0;
	
	while (!converged && (iter < 200)) {
	  double fo2    = exp((*logfo2)*log(10.0));
	  double dfo2   = exp((*logfo2)*log(10.0))*log(10.0);
	  double numer  = KD1*pow(fo2, (double) 0.25) + 2.0*y*K2*pow(KD1, 2.0*y)*pow(fo2, y/2.0);
	  double dnumer = 0.25*KD1*dfo2/pow(fo2, (double) 0.75) + 2.0*y*K2*pow(KD1, 2.0*y)*(y/2.0)*dfo2/pow(fo2, 1.0-y/2.0);	  
	  double denom  = 1.0 + (1.0-2.0*y)*K2*pow(KD1, 2.0*y)*pow(fo2, y/2.0);
	  double ddenom = (1.0-2.0*y)*K2*pow(KD1, 2.0*y)*(y/2.0)*dfo2/pow(fo2, 1.0-y/2.0);
	  
	  double f  =  numer/denom - 2.0*o[indexFe2O3]/o[indexFeO];
	  double df = dnumer/denom - numer*ddenom/(denom*denom);
	  double corr = -f/df;
	  
	  if (fabs(corr) > sqrt(DBL_EPSILON)) *logfo2 += corr; else converged = TRUE;
	  if (*logfo2 >  10.0) *logfo2 =  10.0;
	  if (*logfo2 < -50.0) *logfo2 = -50.0;
	  iter++;
	}
	
	if (!converged) printf("Convergence failure in conLiq(FIRST,SEVENTH)\n");   
      }
#endif /* USE_KRESS_CARMICHAEL_FO2 */
#endif /* BUILD_*_VERSION */

    } else 
      printf("Illegal call to conLiq with inpMask = %o and outMask = %o\n",
        inpMask, outMask);

  } else if (inpMask == SECOND) {
    double sum;

    if (outMask & ~(THIRD | FOURTH | FIFTH | SIXTH))
      printf("Illegal call to conLiq with inpMask = %o and outMask = %o\n",
        inpMask, outMask);

    for (i=0, sum=0.0; i<NA; i++) sum += m[i];

    if (outMask & THIRD) {
      /* Converts a vector of moles of end-member components (m) into a vector
         of independent compositional variables (r) required as input for the
         remaining public functions.                                            
         The dependent variable is taken to be SiO2 (1st component), as this 
         component will never have a mole fraction of zero.                   */

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
        for (i=0; i<NR; i++) for (j=0; j<NA; j++) dm[i][j] = 0.0;
      } else {
        for (i=0; i<NR; i++) {
          for (j=0; j<NA; j++) {
            dm[i][j] = (i+1 == j) ? (1.0-m[i+1]/sum)/sum : - m[i+1]/SQUARE(sum);
          }
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
          for (j=0; j<NA; j++) { 
            for (k=0; k<NA; k++) {
              d2m[i][j][k]  = 2.0*m[i+1]/CUBE(sum);
              d2m[i][j][k] -= (i+1 == j) ? 1.0/SQUARE(sum) : 0.0; 
              d2m[i][j][k] -= (i+1 == k) ? 1.0/SQUARE(sum) : 0.0; 
            }
          }
        }
      }

    }

  } else if (inpMask == THIRD && outMask == FOURTH) {
   /* Converts a vector of independent compositional variables (r) 
      into a vector of mole fractions of end-member components (x)            */

    for (i=0, x[0] = 1.0; i<NR; i++) { x[0] -= r[i]; x[i+1] = r[i]; }

  } else if (inpMask == THIRD && outMask == (FOURTH | EIGHTH)) {
   /* Converts a vector of independent compositional variables (r) 
      into a vector of mole fractions of endmember species (x)                */

    MTHREAD_MUTEX_LOCK(&global_data_mutex);
    order(0, t, p, r,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    for (i=0; i<NE; i++) x[i] = xSpecies[i];
    MTHREAD_MUTEX_UNLOCK(&global_data_mutex);

  } else if (inpMask == THIRD && outMask == (FOURTH | NINTH)) {
    double s[NT];
   /* Converts a vector of independent compositional variables (r) 
      into a vector of fractions of system in CN state * (x)                */

    MTHREAD_MUTEX_LOCK(&global_data_mutex);
    order(FIRST, t, p, r,
        s, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    for (i=0; i<NY; i++) x[i] = s[NS+i];
    MTHREAD_MUTEX_UNLOCK(&global_data_mutex);

  } else {
    printf("Illegal call to conLiq with inpMask = %o and outMask = %o\n",
      inpMask, outMask);
  }

}

int
testLiq(int mask, double t, double p,
  int na,          /* Expected number of endmember components                 */
  int nr,          /* Expected number of independent compositional variables  */
  char **names,    /* array of strings of names of endmember oxides           */
  char **formulas, /* array of strings of formulas of endmember components    */
  double *r,       /* array of indepependent compos variables, check bounds   */
  double *m)       /* array of moles of endmember components, check bounds    */
{
  const char *phase = "liquid.c";
  int result = TRUE, i;
  
  if ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS)) return testLiq_v34(mask, t, p, na, nr, names, formulas, r, m);

  MTHREAD_ONCE(&initThreadBlock, threadInit);

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
      result = result && (strcmp(names[i],bulkSystem[i].label) == 0);
      if (!result)
        printf("<<%s>> Oxide[%d] should be %s not %s.\n",
          phase, i, bulkSystem[i].label, names[i]);
    }
  }
  if (mask & FOURTH) {
    for (i=0; i<NA; i++) {
      result = result && (strcmp(formulas[i],liquid[i].label) == 0);
      if (!result)
        printf("<<%s>> Component[%d] should have formula %s not %s.\n",
          phase, i, liquid[i].label, formulas[i]);
    }
  }
  /* Check bounds on the independent compositional variables */
  if (mask & FIFTH) {
    double s[NT];    
    MTHREAD_MUTEX_LOCK(&global_data_mutex);
    initialGuessOrdering(r, s);    
    result = rANDsTOx (r, s);
    MTHREAD_MUTEX_UNLOCK(&global_data_mutex);
  }
  /* Check bounds on moles of endmember components */
  if (mask & SIXTH) {
    double rTemp[NR], s[NT], sum;
    for (i=0, sum=0.0; i<NA; i++) sum += m[i];
    for (i=0; i<NR; i++) rTemp[i] = (sum != 0.0) ? m[i+1]/sum : 0.0;
    MTHREAD_MUTEX_LOCK(&global_data_mutex);
    initialGuessOrdering(rTemp, s);    
    result = rANDsTOx (rTemp, s);
    MTHREAD_MUTEX_UNLOCK(&global_data_mutex);
  }
  /* Check if ordering state calculation has converged */
  if (mask & SEVENTH) { /* This call is NOT thread safe, but it should never be called from a threaded app */
    result = convergedInOrder;
  }
  /* Check if EOS calculation is valid */
  if (mask & EIGHTH) { /* This call is NOT thread safe, but it should never be called from a threaded app */
    result = ((liqERRstate == ERR_NONE) ? TRUE : FALSE);
  }
  /* Check if number of CN states is corrcet */
  if (mask & NINTH) {
    result = result && (NY == nCN);
    if (!result) printf("<<%s>> Wrong number of CN states!\n", phase);
  }
  
  return result;
}

void
dispLiq(int mask, double t, double p, double *x,
  char **formula            /* Mineral formula for interface display MASK: 1 */
  )
{
  double *r = x;

  if ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS)) { dispLiq_v34(mask, t, p, x, formula); return; }

  MTHREAD_ONCE(&initThreadBlock, threadInit);

  if (mask & FIRST) {    /* assume maximum string length is 5 */
    char *string = (char *) malloc((unsigned) (7+NA*12)*sizeof(char));;
    double m[NA], oxVal[NA], oxSum;
    int i, j, n;
 
    (void) sprintf(string, "wt%% ox:");

    for (i=0, m[0] = 1.0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }
    for (i=0, oxSum=0.0; i<NA; i++) {
      for (j=0, oxVal[i]=0.0; j<NA; j++) oxVal[i] += m[j]*(liquid[j].liqToOx)[i];
      oxVal[i] *= bulkSystem[i].mw;
      oxSum    += oxVal[i];
    }

    if (oxSum != 0.0) for (i=0, n=7; i<NA; i++)
      if (oxVal[i] != 0.0) {
        double w = 100.0*oxVal[i]/oxSum;
        (void) sprintf(&string[n], " %s %.2f", bulkSystem[i].label, w);
        if      (w < 1.0)  n += 5+strlen(bulkSystem[i].label);
        else if (w < 10.0) n += 6+strlen(bulkSystem[i].label);
        else               n += 7+strlen(bulkSystem[i].label);
      }

    *formula = string;
  }
}

static int returnMixingProperties = TRUE;
void setModeToMixingLiq(int flag) { returnMixingProperties = flag; }

void
actLiq(int mask, double t, double p, double *x,
  double *a,   /* (pointer to a[]) activities              BINARY MASK: 000001 */
  double *mu,  /* (pointer to mu[]) chemical potentials    BINARY MASK: 000010 */
  double **dx, /* (pointer to dx[][]) d(a[])/d(x[])        BINARY MASK: 000100 */
  double **dw  /* (pointer to dw[][]) d(mu[])/d(w[])       BINARY MASK: 001000 */
  )
{
  double *r = x;
  double s[NT], g;
  double fr[NA][NR];
  int i, j;

  liqERRstate = ERR_NONE;

  if ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS)) { actLiq_v34(mask, t, p, x, a, mu, dx); return; }

  MTHREAD_ONCE(&initThreadBlock, threadInit);

  MTHREAD_MUTEX_LOCK(&global_data_mutex);
  order(FIRST, t, p, r,
        s, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

  for(i=0; i<NA; i++) for (j=0; j<NR; j++) fr[i][j] = rsEndmembers[i][j] - r[j];

  g = fillG(r, s, t, p);  
  fillDGDR (r, s, t, p, dgdr);

  if (mask & FIRST) {
    for(i=0; i<NA; i++) {
       for (a[i]=g, j=0; j<NR; j++) a[i] += fr[i][j]*dgdr[j];
       if (returnMixingProperties) a[i] -= G(i);
       a[i] = exp(a[i]/(R*t));
    }
  }

  if (mask & SECOND) {
    for(i=0; i<NA; i++) {
      for (mu[i]=g, j=0; j<NR; j++) mu[i] += fr[i][j]*dgdr[j];
      if (returnMixingProperties) mu[i] -= G(i);
    }
    
  }

  if (mask & THIRD) {
    double dsdr[NT][NR], dfrdr[NA][NR], gs[NA][NT], aref[NA], sum;
    int k, l;

    fillD2GDR2  (r, s, t, p, d2gdr2);
    fillD2GDRDS (r, s, t, p, d2gdrds);
    fillD2GDS2  (r, s, t, p, d2gds2);

    /* fill Darken structures */
    for(i=0; i<NA; i++) {
      for (j=0;  j<NR; j++) dfrdr[i][j] = -1.0;
      for (j=0;  j<NS; j++) gs[i][j] = rsEndmembers[i][NR+j] - s[j];
      for (j=NS; j<NT; j++) gs[i][j] = 0.0;
    }

    order(SECOND, t, p, r,
          NULL, dsdr, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    /* get reference activities */
    if (!(mask & FIRST)) {
      for(i=0; i<NA; i++) {
        for (aref[i]=g, j=0; j<NR; j++) aref[i] += fr[i][j]*dgdr[j];
        if (returnMixingProperties) aref[i] -= G(i);
        aref[i] = exp(aref[i]/(R*t));
      }
    } else for (i=0; i<NA; i++) aref[i] = a[i];

    /* Compute derivatives of the chemical potentials */
    for (i=0; i<NA; i++) {
      for (k=0; k<NR; k++) {
        sum = (1.0+dfrdr[i][k])*dgdr[k];
        for (j=0; j<NR; j++) {
          sum += fr[i][j]*d2gdr2[j][k];
          for (l=0; l<NT; l++) sum += fr[i][j]*d2gdrds[j][l]*dsdr[l][k];
        }
        for (j=0; j<NT; j++) {
          sum += gs[i][j]*d2gdrds[k][j];
          for (l=0; l<NT; l++) sum += gs[i][j]*d2gds2[j][l]*dsdr[l][k];
        }
        dx[i][k] = sum; /* This is d mu/d r */
      }
    }
    
    /* convert result to d a/d r */
    for (i=0; i<NA; i++) for (j=0; j<NR; j++) dx[i][j] *= aref[i]/(R*t);
    
  }
  
  if (mask & FOURTH) {
    double dsdw[NT][3*NP], sum;
    int k, l;
    
    fillDGDW    (r, s, t, p, dgdw);
    fillD2GDRDS (r, s, t, p, d2gdrds);
    fillD2GDRDW (r, s, t, p, d2gdrdw);
  
    order(ELEVENTH, t, p, r,
          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, dsdw, NULL);
    
    for (i=0; i<NA; i++) {
      for (j=0; j<NP; j++) {      
        if (modelParameters[j].activeH) {
          for (k=0, dw[i][j]=dgdw[j]; k<NR; k++) {
	    for (l=0, sum=d2gdrdw[k][j]; l<NT; l++) sum += d2gdrds[k][l]*dsdw[l][j];
	    dw[i][j] += fr[i][k]*sum;
	  }
	} else dw[i][j] = 0.0;
	
        if (modelParameters[j].activeS) {
          for (k=0, dw[i][NP+j]=dgdw[NP+j]; k<NR; k++) {
	    for (l=0, sum=d2gdrdw[k][NP+j]; l<NT; l++) sum += d2gdrds[k][l]*dsdw[l][NP+j];
	    dw[i][NP+j] += fr[i][k]*sum;
	  }
	} else dw[i][NP+j] = 0.0;
	
        if (modelParameters[j].activeV) {
          for (k=0, dw[i][2*NP+j]=dgdw[2*NP+j]; k<NR; k++) {
	    for (l=0, sum=d2gdrdw[k][2*NP+j]; l<NT; l++) sum += d2gdrds[k][l]*dsdw[l][2*NP+j];
	    dw[i][2*NP+j] += fr[i][k]*sum;
	  }
	} else dw[i][2*NP+j] = 0.0;
      }
      
      if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
        if (modelParameters[NW+i].activeH) dw[i][     NW+i] -= 1.0;
        if (modelParameters[NW+i].activeS) dw[i][  NP+NW+i] -= -t;
#ifndef USE_GHIORSO_KRESS_MODEL
        if (modelParameters[NW+i].activeV) dw[i][2*NP+NW+i] -= (p-1.0);
#endif /* USE_GHIORSO_KRESS_MODEL */
      }
    }
  }

  /************************************************************************
   * This return is not-public and is used for testing of the derivatives *
   * of G with respect to w[] internal to test_liquid.                    *
   ************************************************************************/
  if (mask & FIFTH) {    
    fillDGDW (r, s, t, p, mu);
    
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      mu[     NW+0] -= 1.0;
      mu[  NP+NW+0] -= -t;
#ifndef USE_GHIORSO_KRESS_MODEL
      mu[2*NP+NW+0] -= (p-1.0);
#endif /* USE_GHIORSO_KRESS_MODEL */
      for (i=0; i<NR; i++) {
        mu[     NW  +0] +=         r[i];
        mu[  NP+NW  +0] +=      -t*r[i];
#ifndef USE_GHIORSO_KRESS_MODEL
        mu[2*NP+NW  +0] += (p-1.0)*r[i];
#endif /* USE_GHIORSO_KRESS_MODEL */
        mu[     NW+i+1] -=         r[i];
        mu[  NP+NW+i+1] -=      -t*r[i];
#ifndef USE_GHIORSO_KRESS_MODEL
        mu[2*NP+NW+i+1] -= (p-1.0)*r[i];
#endif /* USE_GHIORSO_KRESS_MODEL */
      }
    }
    
    for (i=0; i<(3*NP); i++) if (fabs(mu[i]) < 10.0*DBL_EPSILON) mu[i] = 0.0;
  }
  
  /*****************************************************************************
   * This return is used by the preclb_support.c functions to return the       *
   * configurational part of the activity.  It is now obsolete and is included *
   * for backwards compatibility.                                              *
   * ***************************************************************************/ 
  if (mask & SIXTH) {
    for (i=0; i<NA; i++) {
      a[i] = x[i];
      a[i] = (i != NA-1)   ? (1.0 - x[NA-1])*a[i] : x[NA-1]*a[NA-1];
    } 
  }

  /*****************************************************************************
   * This return is not-public and is used within preclb_slave for             *
   * computation of the parameter derivatives of dgdr which are returned in dw.*
   *****************************************************************************/
  if (mask & SEVENTH) {
    double dsdw[NT][3*NP];
    int k;
    
    fillD2GDRDS (r, s, t, p, d2gdrds);
    fillD2GDRDW (r, s, t, p, d2gdrdw);
  
    order(ELEVENTH, t, p, r,
          NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, dsdw, NULL);
    
    for (i=0; i<NR; i++) {
      for (j=0; j<NP; j++) {      
        if (modelParameters[j].activeH) {
	  for (k=0, dw[i][j]=d2gdrdw[i][j]; k<NT; k++) dw[i][j] += d2gdrds[i][k]*dsdw[k][j];
	} else dw[i][j] = 0.0;
	
        if (modelParameters[j].activeS) {
	  for (k=0, dw[i][NP+j]=d2gdrdw[i][NP+j]; k<NT; k++) dw[i][NP+j] += d2gdrds[i][k]*dsdw[k][NP+j];
	} else dw[i][NP+j] = 0.0;
	
        if (modelParameters[j].activeV) {
	  for (k=0, dw[i][2*NP+j]=d2gdrdw[i][2*NP+j]; k<NT; k++) dw[i][2*NP+j] += d2gdrds[i][k]*dsdw[k][2*NP+j];
	} else dw[i][2*NP+j] = 0.0;
      }
      
      if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties dr[i] += (G(0)-G(i+1)); */
        if (modelParameters[NW  +0].activeH) dw[i][     NW  +0] += 1.0;
        if (modelParameters[NW  +0].activeS) dw[i][  NP+NW  +0] += -t;
#ifndef USE_GHIORSO_KRESS_MODEL
        if (modelParameters[NW  +0].activeV) dw[i][2*NP+NW  +0] += (p-1.0);
#endif /* USE_GHIORSO_KRESS_MODEL */
        if (modelParameters[NW+i+1].activeH) dw[i][     NW+i+1] -= 1.0;
        if (modelParameters[NW+i+1].activeS) dw[i][  NP+NW+i+1] -= -t;
#ifndef USE_GHIORSO_KRESS_MODEL
        if (modelParameters[NW+i+1].activeV) dw[i][2*NP+NW+i+1] -= (p-1.0);
#endif /* USE_GHIORSO_KRESS_MODEL */
      }
    }
  }

  /*******************************************************************************
  * This return is non-public and is designed for xMELTS calibration purposes.   *
  * The negative of the partial molar entropy (i.e. d mu dT) is returned in mu[] * 
  ********************************************************************************/
  if (mask & EIGHTH) {
    double dsdt[NT], gs[NA][NT], sum, dgdt;
    int k;

    dgdt = -fillS(r, s, t, p);
    fillD2GDRDS (r, s, t, p, d2gdrds);
    fillD2GDRDT (r, s, t, p, d2gdrdt);
    fillD2GDS2  (r, s, t, p, d2gds2);
    fillD2GDSDT (r, s, t, p, d2gdsdt);

    /* fill Darken structures */
    for(i=0; i<NA; i++) {
      for (j=0;  j<NS; j++) gs[i][j] = rsEndmembers[i][NR+j] - s[j];
      for (j=NS; j<NT; j++) gs[i][j] = 0.0;
    }

    order(THIRD, t, p, r,
          NULL, NULL, dsdt, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    /* Compute derivatives of the chemical potentials */
    for (i=0; i<NA; i++) {
      sum = dgdt;
      for (j=0; j<NR; j++) {
        sum += fr[i][j]*d2gdrdt[j];
        for (k=0; k<NT; k++) sum += fr[i][j]*d2gdrds[j][k]*dsdt[k];
      }
      for (j=0; j<NT; j++) {
        sum += gs[i][j]*d2gdsdt[j];
        for (k=0; k<NT; k++) sum += gs[i][j]*d2gds2[j][k]*dsdt[k];
      }
      mu[i] = sum; /* This is d mu/d t */
      if (returnMixingProperties) mu[i] -= -S(i);
    }
    
  }

  /*******************************************************************************
  * This return is non-public and is designed for xMELTS calibration purposes.   *
  * The model parameter derivative of the negative of the partial molar entropy  *
  * (i.e. d mu / dT dW) is returned in dw[][]                                    * 
  ********************************************************************************/
  if (mask & NINTH) {
    double dsdt[NT], dsdw[NT][3*NP], d2sdtdw[NT][3*NP], gs[NA][NT];
    int k, l, m;
    
    fillD2GDSDW   (r, s, t, p, d2gdsdw);  
    fillD2GDTDW   (r, s, t, p, d2gdtdw);  
    fillD2GDRDS   (r, s, t, p, d2gdrds);  
    fillD2GDS2    (r, s, t, p, d2gds2);   
    fillD2GDSDT   (r, s, t, p, d2gdsdt);  
    fillD3GDRDS2  (r, s, t, p, d3gdrds2); 
    fillD3GDRDSDT (r, s, t, p, d3gdrdsdt);
    fillD3GDRDSDW (r, s, t, p, d3gdrdsdw);
    fillD3GDRDTDW (r, s, t, p, d3gdrdtdw);
    fillD3GDS3    (r, s, t, p, d3gds3);   
    fillD3GDS2DT  (r, s, t, p, d3gds2dt); 
    fillD3GDS2DW  (r, s, t, p, d3gds2dw); 
    fillD3GDSDTDW (r, s, t, p, d3gdsdtdw);
    
    /* fill Darken structures */
    for(i=0; i<NA; i++) {
      for (j=0;  j<NS; j++) gs[i][j] = rsEndmembers[i][NR+j] - s[j];
      for (j=NS; j<NT; j++) gs[i][j] = 0.0;
    }
  
    order(THIRD | ELEVENTH | TWELFTH, t, p, r,
          NULL, NULL, dsdt, NULL, NULL, NULL, NULL, NULL, NULL, NULL, dsdw, d2sdtdw);
    
    for (i=0; i<NA; i++) {
      for (j=0; j<NP; j++) {      
        if (modelParameters[j].activeH) {
	  dw[i][j] = d2gdtdw[j];
	  for (l=0; l<NT; l++) dw[i][j] += d2gdsdt[l]*dsdw[l][j];
          for (k=0; k<NR; k++) {
	    dw[i][j] += fr[i][k]*d3gdrdtdw[k][j];
	    for (l=0; l<NT; l++) dw[i][j] += fr[i][k]*d3gdrdsdt[k][l]*dsdw[l][j];
	    for (m=0; m<NT; m++) {
	      dw[i][j] += fr[i][k]*(d3gdrdsdw[k][m][j]*dsdt[m]+d2gdrds[k][m]*d2sdtdw[m][j]);
	      for (l=0; l<NT; l++) dw[i][j] += fr[i][k]*d3gdrds2[k][m][l]*dsdw[l][j]*dsdt[m];
	    }
	  }	  
          for (k=0; k<NT; k++) {
	    dw[i][j] += gs[i][k]*d3gdsdtdw[k][j];
	    for (l=0; l<NT; l++) dw[i][j] += gs[i][k]*d3gds2dt[k][l]*dsdw[l][j];
	    for (m=0; m<NT; m++) {
	      dw[i][j] += gs[i][k]*(d3gds2dw[k][m][j]*dsdt[m]+d2gds2[k][m]*d2sdtdw[m][j]);
	      for (l=0; l<NT; l++) dw[i][j] += gs[i][k]*d3gds3[k][m][l]*dsdw[l][j]*dsdt[m];
	    }
	  }	  
	} else dw[i][j] = 0.0;
	
        if (modelParameters[j].activeS) {
	  dw[i][NP+j] = d2gdtdw[NP+j];
	  for (l=0; l<NT; l++) dw[i][NP+j] += d2gdsdt[l]*dsdw[l][NP+j];
          for (k=0; k<NR; k++) {
	    dw[i][NP+j] += fr[i][k]*d3gdrdtdw[k][NP+j];
	    for (l=0; l<NT; l++) dw[i][NP+j] += fr[i][k]*d3gdrdsdt[k][l]*dsdw[l][NP+j];
	    for (m=0; m<NT; m++) {
	      dw[i][NP+j] += fr[i][k]*(d3gdrdsdw[k][m][NP+j]*dsdt[m]+d2gdrds[k][m]*d2sdtdw[m][NP+j]);
	      for (l=0; l<NT; l++) dw[i][NP+j] += fr[i][k]*d3gdrds2[k][m][l]*dsdw[l][NP+j]*dsdt[m];
	    }
	  }	  
          for (k=0; k<NT; k++) {
	    dw[i][NP+j] += gs[i][k]*d3gdsdtdw[k][NP+j];
	    for (l=0; l<NT; l++) dw[i][NP+j] += gs[i][k]*d3gds2dt[k][l]*dsdw[l][NP+j];
	    for (m=0; m<NT; m++) {
	      dw[i][NP+j] += gs[i][k]*(d3gds2dw[k][m][NP+j]*dsdt[m]+d2gds2[k][m]*d2sdtdw[m][NP+j]);
	      for (l=0; l<NT; l++) dw[i][NP+j] += gs[i][k]*d3gds3[k][m][l]*dsdw[l][NP+j]*dsdt[m];
	    }
	  }	  
	} else dw[i][NP+j] = 0.0;
	
        if (modelParameters[j].activeV) {
	  dw[i][2*NP+j] = d2gdtdw[2*NP+j];
	  for (l=0; l<NT; l++) dw[i][2*NP+j] += d2gdsdt[l]*dsdw[l][2*NP+j];
          for (k=0; k<NR; k++) {
	    dw[i][2*NP+j] += fr[i][k]*d3gdrdtdw[k][2*NP+j];
	    for (l=0; l<NT; l++) dw[i][2*NP+j] += fr[i][k]*d3gdrdsdt[k][l]*dsdw[l][2*NP+j];
	    for (m=0; m<NT; m++) {
	      dw[i][2*NP+j] += fr[i][k]*(d3gdrdsdw[k][m][2*NP+j]*dsdt[m]+d2gdrds[k][m]*d2sdtdw[m][2*NP+j]);
	      for (l=0; l<NT; l++) dw[i][2*NP+j] += fr[i][k]*d3gdrds2[k][m][l]*dsdw[l][2*NP+j]*dsdt[m];
	    }
	  }	  
          for (k=0; k<NT; k++) {
	    dw[i][2*NP+j] += gs[i][k]*d3gdsdtdw[k][2*NP+j];
	    for (l=0; l<NT; l++) dw[i][2*NP+j] += gs[i][k]*d3gds2dt[k][l]*dsdw[l][2*NP+j];
	    for (m=0; m<NT; m++) {
	      dw[i][2*NP+j] += gs[i][k]*(d3gds2dw[k][m][2*NP+j]*dsdt[m]+d2gds2[k][m]*d2sdtdw[m][2*NP+j]);
	      for (l=0; l<NT; l++) dw[i][2*NP+j] += gs[i][k]*d3gds3[k][m][l]*dsdw[l][2*NP+j]*dsdt[m];
	    }
	  }	  
	} else dw[i][2*NP+j] = 0.0;
      }
      
      if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
        if (modelParameters[NW+i].activeS) dw[i][  NP+NW+i] -= -1.0;
      }
      
    }
  }

  MTHREAD_MUTEX_UNLOCK(&global_data_mutex);
}

void
gmixLiq(int mask, double t, double p, double *x,
  double *gmix, /* Gibbs energy of mixing             BINARY MASK: 0001 */
  double *dx,   /* (pointer to dx[]) d(g)/d(x[])      BINARY MASK: 0010 */
  double **dx2  /* (pointer to dx2[][]) d2(g)/d(x[])2 BINARY MASK: 0100 */
  )
{
  double *r = x;
  double s[NT];
  int i;

  liqERRstate = ERR_NONE;

  if ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS)) { gmixLiq_v34(mask, t, p, x, gmix, dx, dx2); return; }

  MTHREAD_ONCE(&initThreadBlock, threadInit);

  MTHREAD_MUTEX_LOCK(&global_data_mutex);
  order(FIRST, t, p, r,
        s, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

  if (mask & FIRST) {
    *gmix  = fillG (r, s, t, p);   
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      *gmix -= G(0);
      for (i=0; i<NR; i++) *gmix += r[i]*(G(0)-G(i+1));
    }
  }

  if(mask & SECOND) {
    fillDGDR (r, s, t, p, dx);
    if (returnMixingProperties) for (i=0; i<NR; i++) dx[i] += (G(0)-G(i+1));
  }

  if(mask & THIRD) {
    double dsdr[NT][NR];
    int j, k, l;

    fillD2GDR2  (r, s, t, p, d2gdr2);
    fillD2GDRDS (r, s, t, p, d2gdrds);
    fillD2GDS2  (r, s, t, p, d2gds2);

    order(SECOND, t, p, r,
          NULL, dsdr, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    for (i=0; i<NR; i++) {
      for (j=0; j<NR; j++) {
        dx2[i][j] = d2gdr2[i][j];
        for (k=0; k<NT; k++) {
          dx2[i][j] += d2gdrds[i][k]*dsdr[k][j] + d2gdrds[j][k]*dsdr[k][i];
          for (l=0; l<NT; l++) dx2[i][j] += d2gds2[k][l]*dsdr[k][i]*dsdr[l][j];
        }
      }
    }
  }

  if(mask & FOURTH) {
    double dx3[NR][NR][NR]; /* This should be passed to the function */
    double dsdr[NT][NR], d2sdr2[NT][NR][NR];
    int i, j, k, l, m, n;

    fillD3GDR3   (r, s, t, p, d3gdr3);
    fillD3GDR2DS (r, s, t, p, d3gdr2ds);
    fillD3GDRDS2 (r, s, t, p, d3gdrds2);
    fillD3GDS3   (r, s, t, p, d3gds3);

    order(SECOND, t, p, r, 
          NULL, dsdr, NULL, NULL, d2sdr2, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    for (i=0; i<NR; i++) {
      for (j=0; j<NR; j++) {
        for (k=0; k<NR; k++) {
          dx3[i][j][k] = d3gdr3[i][j][k];
          for (l=0; l<NT; l++) {
            dx3[i][j][k] += d3gdr2ds[i][j][l]*dsdr[l][k] +
              d3gdr2ds[j][k][l]*dsdr[l][i] + d3gdr2ds[k][i][l]*dsdr[l][j];
            for (m=0; m<NT; m++) {
              dx3[i][j][k] += 
                d3gdrds2[i][l][m]*dsdr[l][j]*dsdr[m][k] +
                d3gdrds2[j][l][m]*dsdr[l][k]*dsdr[m][i] +
                d3gdrds2[k][l][m]*dsdr[l][i]*dsdr[m][j];
              for (n=0; n<NT; n++)
                dx3[i][j][k] +=
                  d3gds3[l][m][n]*dsdr[l][i]*dsdr[m][j]*dsdr[n][k];
            }
          }
        }
      }
    }
  }
  
  MTHREAD_MUTEX_UNLOCK(&global_data_mutex);
}

void
hmixLiq(int mask, double t, double p, double *x,
  double *hmix, /* Enthalpy of mixing BINARY MASK:                 01 */
  double *dw    /* (pointer to dw[]) d(H)/d(x[])      BINARY MASK: 10 */
  )
{
  double *r = x;
  double s[NT], dsdt[NT];
  int i;

  liqERRstate = ERR_NONE;

  if ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS)) { hmixLiq_v34 (mask, t, p, x, hmix); return; }

  MTHREAD_ONCE(&initThreadBlock, threadInit);

  MTHREAD_MUTEX_LOCK(&global_data_mutex);
  order(FIRST | THIRD, t, p, r,
        s, NULL, dsdt, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

  if (mask & FIRST) {
    *hmix = fillG (r, s, t, p) + t*fillS (r, s, t, p);                            /* was: *hmix = fillH (r, s, t, p);  */

    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      *hmix -= (G(0) + t*S(0));                                                   /* was: *hmix -= H(0);               */
      for (i=0; i<NR; i++) *hmix += r[i]*((G(0) + t*S(0))-(G(i+1) + t*S(i+1)));   /* was: *hmix += r[i]*(H(0)-H(i+1)); */
    }
  }

  if (mask & SECOND) {    
    double dsdw[NT][3*NP], dsdt[NT];
    int i, k, l;

    fillDGDW    (r, s, t, p, dgdw);    
    fillD2GDSDW (r, s, t, p, d2gdsdw);
    fillD2GDTDW (r, s, t, p, d2gdtdw);
    fillD2GDS2  (r, s, t, p, d2gds2);
    fillD2GDSDT (r, s, t, p, d2gdsdt);
 
    order(THIRD | ELEVENTH, t, p, r,
          NULL, NULL, dsdt, NULL, NULL, NULL, NULL, NULL, NULL, NULL, dsdw, NULL);

    for (i=0; i<NP; i++) {
      if (modelParameters[i].activeH) {
        dw[i] = d2gdtdw[i];
        for (k=0; k<NT; k++) {
          dw[i] += d2gdsdw[k][i]*dsdt[k] + d2gdsdt[k]*dsdw[k][i];
          for (l=0; l<NT; l++) dw[i] += d2gds2[k][l]*dsdt[k]*dsdw[l][i] ;
        }
        dw[i] = dgdw[i] - t*dw[i];
      } else dw[i] = 0.0;
      
      if (modelParameters[i].activeS) {
        dw[NP+i] = d2gdtdw[NP+i];
        for (k=0; k<NT; k++) {
          dw[NP+i] += d2gdsdw[k][NP+i]*dsdt[k] + d2gdsdt[k]*dsdw[k][NP+i];
          for (l=0; l<NT; l++) dw[NP+i] += d2gds2[k][l]*dsdt[k]*dsdw[l][NP+i] ;
        }
        dw[NP+i] = dgdw[NP+i] - t*dw[NP+i];
      } else dw[NP+i] = 0.0;

      if (modelParameters[i].activeV) {
        dw[2*NP+i] = d2gdtdw[2*NP+i];
        for (k=0; k<NT; k++) {
          dw[2*NP+i] += d2gdsdw[k][2*NP+i]*dsdt[k] + d2gdsdt[k]*dsdw[k][2*NP+i];
          for (l=0; l<NT; l++) dw[2*NP+i] += d2gds2[k][l]*dsdt[k]*dsdw[l][2*NP+i] ;
        }
        dw[2*NP+i] = dgdw[2*NP+i] - t*dw[2*NP+i];
      } else dw[2*NP+i] = 0.0;
    }
    
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      if (modelParameters[NW+0].activeH) dw[     NW+0] -= 1.0;
#ifndef USE_GHIORSO_KRESS_MODEL
      if (modelParameters[NW+0].activeV) dw[2*NP+NW+0] -= (p-1.0);
#endif /* USE_GHIORSO_KRESS_MODEL */
      for (i=0; i<NR; i++) { 
        if (modelParameters[NW  +0].activeH) dw[     NW  +0] +=         r[i]; 
#ifndef USE_GHIORSO_KRESS_MODEL
        if (modelParameters[NW  +0].activeV) dw[2*NP+NW  +0] += (p-1.0)*r[i]; 
#endif /* USE_GHIORSO_KRESS_MODEL */
        if (modelParameters[NW+i+1].activeH) dw[     NW+i+1] -=         r[i]; 
#ifndef USE_GHIORSO_KRESS_MODEL
        if (modelParameters[NW+i+1].activeV) dw[2*NP+NW+i+1] -= (p-1.0)*r[i]; 
#endif /* USE_GHIORSO_KRESS_MODEL */
      }
    }
    
    for (i=0; i<(3*NP); i++) if (fabs(dw[i]) < 10.0*DBL_EPSILON) dw[i] = 0.0;
  }
  
  MTHREAD_MUTEX_UNLOCK(&global_data_mutex);
}

void
smixLiq(int mask, double t, double p, double *x,
  double *smix, /* Entropy of mixing                  BINARY MASK: 0001 */
  double *dx,   /* (pointer to dx[]) d(s)/d(x[])      BINARY MASK: 0010 */
  double **dx2, /* (pointer to dx2[][]) d2(s)/d(x[])2 BINARY MASK: 0100 */
  double *dw    /* (pointer to dw[]) d(s)/d(x[])      BINARY MASK: 1000 */
  )
{
  double *r = x;
  double s[NT];

  liqERRstate = ERR_NONE;

  if ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS)) { smixLiq_v34(mask, t, p, x, smix, dx, dx2); return; }

  MTHREAD_ONCE(&initThreadBlock, threadInit);

  MTHREAD_MUTEX_LOCK(&global_data_mutex);
  order(FIRST, t, p, r,
        s, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        
  if (mask & FIRST) {
    int i;
  
    *smix = fillS (r, s, t, p);
    
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      *smix -= S(0);
      for (i=0; i<NR; i++) *smix += r[i]*(S(0)-S(i+1));
    }
  }

  if(mask & SECOND) {
   double dsdr[NT][NR], dsdt[NT];
    int i, k, l;

    fillD2GDRDS (r, s, t, p, d2gdrds);
    fillD2GDRDT (r, s, t, p, d2gdrdt);
    fillD2GDS2  (r, s, t, p, d2gds2);
    fillD2GDSDT (r, s, t, p, d2gdsdt);
 
    order(SECOND | THIRD, t, p, r,
          NULL, dsdr, dsdt, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    for (i=0; i<NR; i++) {
      dx[i] = d2gdrdt[i];
      for (k=0; k<NT; k++) {
        dx[i] += d2gdrds[i][k]*dsdt[k] + d2gdsdt[k]*dsdr[k][i];
        for (l=0; l<NT; l++) dx[i] += d2gds2[k][l]*dsdt[k]*dsdr[l][i] ;
      }
      dx[i] *= -1.0;
    }
    
    /* Convert Solution Properties -> Mixing Properties */
    if (returnMixingProperties) for (i=0; i<NR; i++) dx[i] += (S(0)-S(i+1));
  }

  if(mask & THIRD) {
    double dsdr[NT][NR], dsdt[NT], d2sdr2[NT][NR][NR], d2sdrdt[NT][NR];
    int i, j, k, l, m;

    fillD2GDRDS   (r, s, t, p, d2gdrds);
    fillD2GDS2    (r, s, t, p, d2gds2);
    fillD2GDSDT   (r, s, t, p, d2gdsdt);
    fillD3GDR2DS  (r, s, t, p, d3gdr2ds);
    fillD3GDR2DT  (r, s, t, p, d3gdr2dt);
    fillD3GDRDS2  (r, s, t, p, d3gdrds2);
    fillD3GDRDSDT (r, s, t, p, d3gdrdsdt);
    fillD3GDS3    (r, s, t, p, d3gds3);
    fillD3GDS2DT  (r, s, t, p, d3gds2dt);

    order(SECOND | THIRD | FIFTH | SIXTH, t, p, r,
          NULL, dsdr, dsdt, NULL, d2sdr2, d2sdrdt, NULL, NULL, NULL, NULL, NULL, NULL);

    for (i=0; i<NR; i++) {
      for (j=0; j<NR; j++) {
        dx2[i][j] = d3gdr2dt[i][j];
        for (k=0; k<NT; k++) {
          dx2[i][j] += d3gdr2ds[i][j][k]*dsdt[k]
                     + d3gdrdsdt[i][k]*dsdr[k][j]
                     + d3gdrdsdt[j][k]*dsdr[k][i]
                     + d2gdsdt[k]*d2sdr2[k][i][j]
                     + d2gdrds[i][k]*d2sdrdt[k][j]
                     + d2gdrds[j][k]*d2sdrdt[k][i];
          for (l=0; l<NT; l++) {
            dx2[i][j] += d3gdrds2[i][k][l]*dsdr[k][j]*dsdt[l]
                       + d3gdrds2[j][k][l]*dsdr[k][i]*dsdt[l]
                       + d2gds2[k][l]*d2sdr2[k][i][j]*dsdt[l]
                       + d3gds2dt[k][l]*dsdr[k][i]*dsdr[l][j]
                       + d2gds2[k][l]*dsdr[k][i]*d2sdrdt[l][j]
                       + d2gds2[k][l]*dsdr[k][j]*d2sdrdt[l][i];
            for (m=0; m<NT; m++)
              dx2[i][j] += d3gds3[k][l][m]*dsdr[k][i]*dsdr[l][j]*dsdt[m];
          }
        }
        dx2[i][j] *= -1.0;
      }
    }
  }
  
  if(mask & FOURTH) {
    double dsdw[NT][3*NP], dsdt[NT];
    int i, k, l;

    fillD2GDSDW (r, s, t, p, d2gdsdw);
    fillD2GDTDW (r, s, t, p, d2gdtdw);
    fillD2GDS2  (r, s, t, p, d2gds2);
    fillD2GDSDT (r, s, t, p, d2gdsdt);
 
    order(THIRD | ELEVENTH, t, p, r,
          NULL, NULL, dsdt, NULL, NULL, NULL, NULL, NULL, NULL, NULL, dsdw, NULL);

    for (i=0; i<NP; i++) {
      if (modelParameters[i].activeH) {
        dw[i] = d2gdtdw[i];
        for (k=0; k<NT; k++) {
          dw[i] += d2gdsdw[k][i]*dsdt[k] + d2gdsdt[k]*dsdw[k][i];
          for (l=0; l<NT; l++) dw[i] += d2gds2[k][l]*dsdt[k]*dsdw[l][i] ;
        }
        dw[i] *= -1.0;
      } else dw[i] = 0.0;
      
      if (modelParameters[i].activeS) {
        dw[NP+i] = d2gdtdw[NP+i];
        for (k=0; k<NT; k++) {
          dw[NP+i] += d2gdsdw[k][NP+i]*dsdt[k] + d2gdsdt[k]*dsdw[k][NP+i];
          for (l=0; l<NT; l++) dw[NP+i] += d2gds2[k][l]*dsdt[k]*dsdw[l][NP+i] ;
        }
        dw[NP+i] *= -1.0;
      } else dw[NP+i] = 0.0;

      if (modelParameters[i].activeV) {
        dw[2*NP+i] = d2gdtdw[2*NP+i];
        for (k=0; k<NT; k++) {
          dw[2*NP+i] += d2gdsdw[k][2*NP+i]*dsdt[k] + d2gdsdt[k]*dsdw[k][2*NP+i];
          for (l=0; l<NT; l++) dw[2*NP+i] += d2gds2[k][l]*dsdt[k]*dsdw[l][2*NP+i] ;
        }
        dw[2*NP+i] *= -1.0;
      } else dw[2*NP+i] = 0.0;
    }
    
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      if (modelParameters[NW+0].activeS) dw[NP+NW+0] -= 1.0;
      for (i=0; i<NR; i++) { 
        if (modelParameters[NW  +0].activeS) dw[NP+NW  +0] += r[i]; 
        if (modelParameters[NW+i+1].activeS) dw[NP+NW+i+1] -= r[i]; 
      }
    }
    
    for (i=0; i<(3*NP); i++) if (fabs(dw[i]) < 10.0*DBL_EPSILON) dw[i] = 0.0;
  }
  
  MTHREAD_MUTEX_UNLOCK(&global_data_mutex);
}

void
cpmixLiq(int mask, double t, double p, double *x,
  double *cpmix, /* Heat capacity of mixing               BINARY MASK: 001 */
  double *dt,    /* d(cp)/d(t)                            BINARY MASK: 010 */
  double *dx     /* d(cp)/d(x[])d(t)                      BINARY MASK: 100 */
  )
{
  double *r = x;
  double s[NT], dsdt[NT];
  double d2gdt2;
  int i, j;

  liqERRstate = ERR_NONE;

  if ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS)) { cpmixLiq_v34(mask, t, p, x, cpmix, dt, dx); return; }

  MTHREAD_ONCE(&initThreadBlock, threadInit);

  MTHREAD_MUTEX_LOCK(&global_data_mutex);
  order(FIRST | THIRD, t, p, r,
        s,    NULL, dsdt, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

  fillD2GDSDT (r, s, t, p, d2gdsdt);
  fillD2GDS2  (r, s, t, p, d2gds2);
  d2gdt2 = fillD2GDT2  (r, s, t, p);

  if (mask & FIRST) {
    *cpmix = d2gdt2;
    for (i=0; i<NT; i++) {
      *cpmix += 2.0*d2gdsdt[i]*dsdt[i];
      for (j=0; j<NT; j++) *cpmix += d2gds2[i][j]*dsdt[i]*dsdt[j];
    }
    *cpmix *= -t;
    
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      *cpmix -= CP(0);
      for (i=0; i<NR; i++) *cpmix += r[i]*(CP(0)-CP(i+1));
    }
  }

  if(mask & SECOND) {
    double d3gdt3 = fillD3GDT3   (r, s, t, p);
    double d2sdt2[NT], temp;
    int k;

    fillD3GDS3   (r, s, t, p, d3gds3);
    fillD3GDS2DT (r, s, t, p, d3gds2dt);
    fillD3GDSDT2 (r, s, t, p, d3gdsdt2);

    order(EIGHTH, t, p, r,
          NULL, NULL, NULL, NULL, NULL, NULL, NULL, d2sdt2, NULL, NULL, NULL, NULL);

    /* compute d2gdt2 */
    temp = d2gdt2;
    for (i=0; i<NT; i++) {
      temp += 2.0*d2gdsdt[i]*dsdt[i];
      for (j=0; j<NT; j++) temp += d2gds2[i][j]*dsdt[i]*dsdt[j];
    }

    *dt = d3gdt3;
    for (i=0; i<NT; i++) {
      *dt += 3.0*d3gdsdt2[i]*dsdt[i] + 3.0*d2gdsdt[i]*d2sdt2[i];
      for (j=0; j<NT; j++) {
        *dt += 3.0*d2gds2[i][j]*dsdt[i]*d2sdt2[j]
             + 3.0*d3gds2dt[i][j]*dsdt[i]*dsdt[j];
        for (k=0; k<NT; k++) *dt += d3gds3[i][j][k]*dsdt[i]*dsdt[j]*dsdt[k];
      }
    }
    *dt = -t*(*dt) - temp;
    
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      *dt -= DCPDT(0);
      for (i=0; i<NR; i++) *dt += r[i]*(DCPDT(0)-DCPDT(i+1));
    }
  }

  if(mask & THIRD) {
    double dsdr[NT][NR], d2sdrdt[NT][NR], d2sdt2[NT];
    int k, l;

    fillD3GDS3    (r, s, t, p, d3gds3);
    fillD3GDRDS2  (r, s, t, p, d3gdrds2);
    fillD3GDRDSDT (r, s, t, p, d3gdrdsdt);
    fillD3GDS2DT  (r, s, t, p, d3gds2dt);
    fillD2GDRDS   (r, s, t, p, d2gdrds);
    fillD3GDRDT2  (r, s, t, p, d3gdrdt2);
    fillD3GDSDT2  (r, s, t, p, d3gdsdt2);

    order(SECOND | SIXTH | EIGHTH, t, p, r,
          NULL, dsdr, NULL, NULL, NULL, d2sdrdt, NULL, d2sdt2, NULL, NULL, NULL, NULL);

    for (i=0; i<NR; i++) {
      for (j=0,dx[i]=d3gdrdt2[i]; j<NT; j++) {
        dx[i] += d3gdsdt2[j]*dsdr[j][i] + 2.0*d2gdsdt[j]*d2sdrdt[j][i] +
                 2.0*d3gdrdsdt[i][j]*dsdt[j] + d2gdrds[i][j]*d2sdt2[j];
        for (k=0; k<NT; k++) {
          dx[i] += d3gdrds2[i][j][k]*dsdt[j]*dsdt[k] +
                   2.0*d2gds2[j][k]*dsdt[j]*d2sdrdt[k][i] +
                   2.0*d3gds2dt[j][k]*dsdr[j][i]*dsdt[k] +
                   d2gds2[j][k]*dsdr[j][i]*d2sdt2[k];
          for (l=0; l<NT; l++)
            dx[i] += d3gds3[j][k][l]*dsdr[j][i]*dsdt[k]*dsdt[l];
        }
      }
      dx[i] *= -t;
    }
    
    if (returnMixingProperties) for (i=0; i<NR; i++) dx[i] += (CP(0)-CP(i+1));
  }

  MTHREAD_MUTEX_UNLOCK(&global_data_mutex);
}

void
vmixLiq(int mask, double t, double p, double *x,
  double *vmix, /* Volume of mixing                BINARY MASK: 00000000001 */
  double *dx,   /* (pointer to dx[]) d(v)/d(x[])   BINARY MASK: 00000000010 */
  double **dx2, /* (point to dx2[][]) d(v)/d(x[])2 BINARY MASK: 00000000100 */
  double *dt,   /* d(v)/d(t)                       BINARY MASK: 00000001000 */
  double *dp,   /* d(v)/d(p)                       BINARY MASK: 00000010000 */
  double *dt2,  /* d2(v)/d(t)2                     BINARY MASK: 00000100000 */
  double *dtdp, /* d2(v)/d(t)d(p)                  BINARY MASK: 00001000000 */
  double *dp2,  /* d2(v)/d(p)2                     BINARY MASK: 00010000000 */
  double *dxdt, /* d2(v)/d(x[])d(t)                BINARY MASK: 00100000000 */
  double *dxdp, /* d2(v)/d(x[])d(p)                BINARY MASK: 01000000000 */
  double *dw    /* (pointer to dw[]) d(v)/d(x[])   BINARY MASK: 10000000000 */
  )
{
  double *r = x;
  double s[NT];

  liqERRstate = ERR_NONE;

  if ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS)) { 
    vmixLiq_v34 (mask, t, p, x, vmix, dx, dx2, dt, dp, dt2, dtdp, dp2, dxdt, dxdp);
    return;
  }

  MTHREAD_ONCE(&initThreadBlock, threadInit);

  MTHREAD_MUTEX_LOCK(&global_data_mutex);
  order(FIRST, t, p, r,
        s, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

#ifdef USE_GHIORSO_KRESS_MODEL
#undef  V
#undef  DVDT
#undef  DVDP
#undef  D2VDT2
#undef  D2VDTDP
#undef  D2VDP2
#define V(i)       ((liquid[i].cur).v + modelParameters[NW+i].volume)
#define DVDT(i)    ((liquid[i].cur).dvdt)
#define DVDP(i)    ((liquid[i].cur).dvdp)
#define D2VDT2(i)  ((liquid[i].cur).d2vdt2)
#define D2VDTDP(i) ((liquid[i].cur).d2vdtdp)
#define D2VDP2(i)  ((liquid[i].cur).d2vdp2)
#endif /* USE_GHIORSO_KRESS_MODEL */

  if (mask & FIRST) {
    int i;
    *vmix = fillV (r, s, t, p);
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      *vmix -= V(0);
      for (i=0; i<NR; i++) *vmix += r[i]*(V(0)-V(i+1));
    }
  }

  if(mask & SECOND) {
    double dsdr[NT][NR], dsdp[NT];
    int i, j, k;

    fillD2GDRDS (r, s, t, p, d2gdrds);
    fillD2GDRDP (r, s, t, p, d2gdrdp);
    fillD2GDS2  (r, s, t, p, d2gds2);
    fillD2GDSDP (r, s, t, p, d2gdsdp);

    order(SECOND | FOURTH, t, p, r,
          NULL, dsdr, NULL, dsdp, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    for (i=0; i<NR; i++) {
      dx[i] = d2gdrdp[i];
      for (j=0; j<NT; j++) {
        dx[i] += d2gdrds[i][j]*dsdp[j] + d2gdsdp[j]*dsdr[j][i];
        for (k=0; k<NT; k++) dx[i] += d2gds2[j][k]*dsdp[j]*dsdr[k][i];
      }
    }
    
    if (returnMixingProperties) for (i=0; i<NR; i++) dx[i] += (V(0)-V(i+1));
  }

  if(mask & THIRD) {
    double dsdr[NT][NR], dsdp[NT], d2sdr2[NT][NR][NR], d2sdrdp[NT][NR];
    int i, j, k, l, m;

    fillD2GDRDS   (r, s, t, p, d2gdrds);
    fillD2GDS2    (r, s, t, p, d2gds2);
    fillD2GDSDP   (r, s, t, p, d2gdsdp);
    fillD3GDR2DS  (r, s, t, p, d3gdr2ds);
    fillD3GDR2DP  (r, s, t, p, d3gdr2dp);
    fillD3GDRDS2  (r, s, t, p, d3gdrds2);
    fillD3GDRDSDP (r, s, t, p, d3gdrdsdp);
    fillD3GDS3    (r, s, t, p, d3gds3);
    fillD3GDS2DP  (r, s, t, p, d3gds2dp);

    order(SECOND | FOURTH | FIFTH | SEVENTH, t, p, r,
          NULL, dsdr, NULL, dsdp, d2sdr2, NULL, d2sdrdp,  NULL, NULL, NULL, NULL, NULL);

    for (i=0; i<NR; i++) {
      for (j=0; j<NR; j++) {
        dx2[i][j] = d3gdr2dp[i][j];
        for (k=0; k<NT; k++) {
          dx2[i][j] += d3gdr2ds[i][j][k]*dsdp[k]
                     + d3gdrdsdp[i][k]*dsdr[k][j]
                     + d3gdrdsdp[j][k]*dsdr[k][i]
                     + d2gdsdp[k]*d2sdr2[k][i][j]
                     + d2gdrds[i][k]*d2sdrdp[k][j]
                     + d2gdrds[j][k]*d2sdrdp[k][i];
          for (l=0; l<NT; l++) {
            dx2[i][j] += d3gdrds2[i][k][l]*dsdr[k][j]*dsdp[l]
                       + d3gdrds2[j][k][l]*dsdr[k][i]*dsdp[l]
                       + d2gds2[k][l]*d2sdr2[k][i][j]*dsdp[l]
                       + d3gds2dp[k][l]*dsdr[k][i]*dsdr[l][j]
                       + d2gds2[k][l]*dsdr[k][i]*d2sdrdp[l][j]
                       + d2gds2[k][l]*dsdr[k][j]*d2sdrdp[l][i];
            for (m=0; m<NT; m++)
              dx2[i][j] += d3gds3[k][l][m]*dsdr[k][i]*dsdr[l][j]*dsdp[m];
          }
        }
      }
    }
    
  }

  if(mask & FOURTH) {
    double d2gdtdp = fillD2GDTDP (r, s, t, p);
    double dsdt[NT], dsdp[NT];
    int i, j;

    fillD2GDS2  (r, s, t, p, d2gds2);
    fillD2GDSDT (r, s, t, p, d2gdsdt);
    fillD2GDSDP (r, s, t, p, d2gdsdp);

    order(THIRD | FOURTH, t, p, r,
          NULL, NULL, dsdt, dsdp, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    *dt = d2gdtdp;
    for (i=0; i<NT; i++) {
      *dt += d2gdsdt[i]*dsdp[i] + d2gdsdp[i]*dsdt[i];
      for (j=0; j<NT; j++) *dt += d2gds2[i][j]*dsdt[i]*dsdp[j];
    }
    
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      *dt -= DVDT(0);
      for (i=0; i<NR; i++) *dt += r[i]*(DVDT(0)-DVDT(i+1));
    }
  }

  if(mask & FIFTH) {
    double   d2gdp2  = fillD2GDP2  (r, s, t, p);
    double dsdp[NT];
    int i,j;

    fillD2GDS2  (r, s, t, p, d2gds2);
    fillD2GDSDP (r, s, t, p, d2gdsdp);

    order(FOURTH, t, p, r,
          NULL, NULL, NULL, dsdp, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    *dp = d2gdp2;
    for (i=0; i<NT; i++) {
      *dp += 2.0*d2gdsdp[i]*dsdp[i];
      for (j=0; j<NT; j++) *dp += d2gds2[i][j]*dsdp[i]*dsdp[j];
    }
    
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      *dp -= DVDP(0);
      for (i=0; i<NR; i++) *dp += r[i]*(DVDP(0)-DVDP(i+1));
    }
  }

  if(mask & SIXTH) {
    double    d3gdt2dp  = fillD3GDT2DP  (r, s, t, p);
    double dsdt[NT], dsdp[NT], d2sdt2[NT], d2sdtdp[NT];
    int i, j, k;

    fillD2GDS2    (r, s, t, p, d2gds2);
    fillD2GDSDT   (r, s, t, p, d2gdsdt);
    fillD2GDSDP   (r, s, t, p, d2gdsdp);
    fillD3GDS3    (r, s, t, p, d3gds3);
    fillD3GDS2DP  (r, s, t, p, d3gds2dp);
    fillD3GDS2DT  (r, s, t, p, d3gds2dt);
    fillD3GDSDTDP (r, s, t, p, d3gdsdtdp);
    fillD3GDSDT2  (r, s, t, p, d3gdsdt2);

    order(THIRD | FOURTH | EIGHTH | NINTH, t, p, r,
          NULL, NULL, dsdt, dsdp, NULL, NULL, NULL, d2sdt2, d2sdtdp, NULL, NULL, NULL);

    *dt2 = d3gdt2dp;
    for (i=0; i<NT; i++) {
      *dt2 += d3gdsdt2[i]*dsdp[i] + 2.0*d2gdsdt[i]*d2sdtdp[i]
            + d2gdsdp[i]*d2sdt2[i] + 2.0*d3gdsdtdp[i]*dsdt[i];
      for (j=0; j<NT; j++) {
        *dt2 += 2.0*d3gds2dt[i][j]*dsdt[i]*dsdp[j]
              + d2gds2[i][j]*d2sdt2[i]*dsdp[j]
              + 2.0*d2gds2[i][j]*dsdt[i]*d2sdtdp[j]
              + d3gds2dp[i][j]*dsdt[i]*dsdt[j];
        for (k=0; k<NT; k++) *dt2 += d3gds3[i][j][k]*dsdt[i]*dsdt[j]*dsdp[k];
      }
    }
    
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      *dt2 -= D2VDT2(0);
      for (i=0; i<NR; i++) *dt2 += r[i]*(D2VDT2(0)-D2VDT2(i+1));
    }
  }

  if(mask & SEVENTH) {
    double    d3gdtdp2  = fillD3GDTDP2  (r, s, t, p);
    double dsdt[NT], dsdp[NT], d2sdtdp[NT], d2sdp2[NT];
    int i, j, k;

    fillD2GDS2    (r, s, t, p, d2gds2);
    fillD2GDSDT   (r, s, t, p, d2gdsdt);
    fillD2GDSDP   (r, s, t, p, d2gdsdp);
    fillD3GDS3    (r, s, t, p, d3gds3);
    fillD3GDS2DT  (r, s, t, p, d3gds2dt);
    fillD3GDS2DP  (r, s, t, p, d3gds2dp);
    fillD3GDSDTDP (r, s, t, p, d3gdsdtdp);
    fillD3GDSDP2  (r, s, t, p, d3gdsdp2);

    order(THIRD | FOURTH | NINTH | TENTH, t, p, r,
          NULL, NULL, dsdt, dsdp, NULL, NULL, NULL, NULL, d2sdtdp, d2sdp2, NULL, NULL);

    *dtdp = d3gdtdp2;
    for (i=0; i<NT; i++) {
      *dtdp += 2.0*d3gdsdtdp[i]*dsdp[i] + d2gdsdt[i]*d2sdp2[i]
             + 2.0*d2gdsdp[i]*d2sdtdp[i] + d3gdsdp2[i]*dsdt[i];
      for (j=0; j<NT; j++) {
        *dtdp += 2.0*d3gds2dp[i][j]*dsdt[i]*dsdp[j]
               + d2gds2[i][j]*dsdt[i]*d2sdp2[j]
               + 2.0*d2gds2[i][j]*d2sdtdp[i]*dsdp[j]
               + d3gds2dt[i][j]*dsdp[i]*dsdp[j];
        for (k=0; k<NT; k++) *dtdp += d3gds3[i][j][k]*dsdt[i]*dsdp[j]*dsdp[k];
      }
    }
    
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      *dtdp -= D2VDTDP(0);
      for (i=0; i<NR; i++) *dtdp += r[i]*(D2VDTDP(0)-D2VDTDP(i+1));
    }
  }

  if(mask & EIGHTH) {
    double    d3gdp3   = fillD3GDP3   (r, s, t, p);
    double dsdp[NT], d2sdp2[NT];
    int i, j, k;

    fillD2GDS2   (r, s, t, p, d2gds2);
    fillD2GDSDP  (r, s, t, p, d2gdsdp);
    fillD3GDS3   (r, s, t, p, d3gds3);
    fillD3GDS2DP (r, s, t, p, d3gds2dp);
    fillD3GDSDP2 (r, s, t, p, d3gdsdp2);

    order(FOURTH | TENTH, t, p, r,
          NULL, NULL, NULL, dsdp, NULL, NULL, NULL, NULL, NULL, d2sdp2, NULL, NULL);

    *dp2 = d3gdp3;
    for (i=0; i<NT; i++) {
      *dp2 += 3.0*d3gdsdp2[i]*dsdp[i] + 3.0*d2gdsdp[i]*d2sdp2[i];
      for (j=0; j<NT; j++) {
        *dp2 += 3.0*d2gds2[i][j]*dsdp[i]*d2sdp2[j]
              + 3.0*d3gds2dp[i][j]*dsdp[i]*dsdp[j];
        for (k=0; k<NT; k++) *dp2 += d3gds3[i][j][k]*dsdp[i]*dsdp[j]*dsdp[k];
      }
    }
    
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      *dp2 -= D2VDP2(0);
      for (i=0; i<NR; i++) *dp2 += r[i]*(D2VDP2(0)-D2VDP2(i+1));
    }
  }

  if(mask & NINTH) {
    double dsdt[NT], dsdp[NT], dsdr[NT][NR], d2sdrdt[NT][NR], d2sdrdp[NT][NR],
      d2sdtdp[NT];
    int i, j, k, l;

    fillD3GDS3    (r, s, t, p, d3gds3);
    fillD3GDRDS2  (r, s, t, p, d3gdrds2);
    fillD3GDRDSDT (r, s, t, p, d3gdrdsdt);
    fillD3GDS2DP  (r, s, t, p, d3gds2dp);
    fillD2GDRDS   (r, s, t, p, d2gdrds);
    fillD3GDRDTDP (r, s, t, p, d3gdrdtdp);
    fillD3GDSDTDP (r, s, t, p, d3gdsdtdp);
    fillD2GDS2    (r, s, t, p, d2gds2);
    fillD2GDSDT   (r, s, t, p, d2gdsdt);
    fillD3GDRDSDP (r, s, t, p, d3gdrdsdp);
    fillD2GDSDP   (r, s, t, p, d2gdsdp);
    fillD3GDS2DT  (r, s, t, p, d3gds2dt);

    order(SECOND | THIRD | FOURTH | SIXTH | SEVENTH | NINTH, t, p, r,
          NULL, dsdr, dsdt, dsdp, NULL, d2sdrdt, d2sdrdp, NULL, d2sdtdp, NULL, NULL, NULL);

    for (i=0; i<NR; i++) {
      for (j=0,dxdt[i]=d3gdrdtdp[i]; j<NT; j++) {
        dxdt[i] += d3gdsdtdp[j]*dsdr[j][i] + d2gdsdt[j]*d2sdrdp[j][i] +
                   d3gdrdsdt[i][j]*dsdp[j] + d2gdrds[i][j]*d2sdtdp[j] +
                   d3gdrdsdp[i][j]*dsdt[j] + d2gdsdp[j]*d2sdrdt[j][i];
        for (k=0; k<NT; k++) {
          dxdt[i] += d3gdrds2[i][j][k]*dsdt[j]*dsdp[k] +
                     d2gds2[j][k]*dsdt[j]*d2sdrdp[k][i] +
                     d2gds2[j][k]*dsdp[j]*d2sdrdt[k][i] +
                     d3gds2dt[j][k]*dsdr[j][i]*dsdp[k] +
                     d3gds2dp[j][k]*dsdr[j][i]*dsdt[k] +
                     d2gds2[j][k]*dsdr[j][i]*d2sdtdp[k];
          for (l=0; l<NT; l++)
            dxdt[i] += d3gds3[j][k][l]*dsdr[j][i]*dsdt[k]*dsdp[l];
        }
      }
    }
    
    if (returnMixingProperties) for (i=0; i<NR; i++) dxdt[i] += (DVDT(0)-DVDT(i+1));
  }

  if(mask & TENTH) {
    double dsdr[NT][NR], dsdp[NT], d2sdrdp[NT][NR], d2sdp2[NT];
    int i, j, k, l;

    fillD3GDS3    (r, s, t, p, d3gds3);
    fillD3GDRDS2  (r, s, t, p, d3gdrds2);
    fillD3GDS2DP  (r, s, t, p, d3gds2dp);
    fillD2GDRDS   (r, s, t, p, d2gdrds);
    fillD3GDRDSDP (r, s, t, p, d3gdrdsdp);
    fillD3GDRDP2  (r, s, t, p, d3gdrdp2);
    fillD3GDSDP2  (r, s, t, p, d3gdsdp2);
    fillD2GDSDP   (r, s, t, p, d2gdsdp);
    fillD2GDS2    (r, s, t, p, d2gds2);

    order(SECOND | FOURTH | SEVENTH | TENTH, t, p, r,
          NULL, dsdr, NULL, dsdp, NULL, NULL, d2sdrdp, NULL, NULL, d2sdp2, NULL, NULL);

    for (i=0; i<NR; i++) {
      for (j=0,dxdp[i]=d3gdrdp2[i]; j<NT; j++) {
        dxdp[i] += d3gdsdp2[j]*dsdr[j][i] + d2gdsdp[j]*d2sdrdp[j][i] +
                   2.0*d3gdrdsdp[i][j]*dsdp[j] + d2gdrds[i][j]*d2sdp2[j] +
                   d2gdsdp[j]*d2sdrdp[j][i];
        for (k=0; k<NT; k++) {
          dxdp[i] += d3gdrds2[i][j][k]*dsdp[j]*dsdp[k] +
                     2.0*d2gds2[j][k]*dsdp[j]*d2sdrdp[k][i] +
                     2.0*d3gds2dp[j][k]*dsdr[j][i]*dsdp[k] +
                     d2gds2[j][k]*dsdr[j][i]*d2sdp2[k];
          for (l=0; l<NT; l++)
            dxdp[i] += d3gds3[j][k][l]*dsdr[j][i]*dsdp[k]*dsdp[l];
        }
      }
    }
    
    if (returnMixingProperties) for (i=0; i<NR; i++) dxdp[i] += (DVDP(0)-DVDP(i+1));
  }

  if(mask & ELEVENTH) {
    double dsdw[NT][3*NP], dsdp[NT];
    int i, k, l;

    fillD2GDSDW (r, s, t, p, d2gdsdw);
    fillD2GDPDW (r, s, t, p, d2gdpdw);
    fillD2GDS2  (r, s, t, p, d2gds2);
    fillD2GDSDP (r, s, t, p, d2gdsdp);
 
    order(FOURTH | ELEVENTH, t, p, r,
          NULL, NULL, NULL, dsdp, NULL, NULL, NULL, NULL, NULL, NULL, dsdw, NULL);

    for (i=0; i<NP; i++) {
      if (modelParameters[i].activeH) {
        dw[i] = d2gdpdw[i];
        for (k=0; k<NT; k++) {
          dw[i] += d2gdsdw[k][i]*dsdp[k] + d2gdsdp[k]*dsdw[k][i];
          for (l=0; l<NT; l++) dw[i] += d2gds2[k][l]*dsdp[k]*dsdw[l][i] ;
        }
        dw[i] *= -1.0;
      } else dw[i] = 0.0;
      
      if (modelParameters[i].activeS) {
        dw[NP+i] = d2gdpdw[NP+i];
        for (k=0; k<NT; k++) {
          dw[NP+i] += d2gdsdw[k][NP+i]*dsdp[k] + d2gdsdp[k]*dsdw[k][NP+i];
          for (l=0; l<NT; l++) dw[NP+i] += d2gds2[k][l]*dsdp[k]*dsdw[l][NP+i] ;
        }
        dw[NP+i] *= -1.0;
      } else dw[NP+i] = 0.0;

      if (modelParameters[i].activeV) {
        dw[2*NP+i] = d2gdpdw[2*NP+i];
        for (k=0; k<NT; k++) {
          dw[2*NP+i] += d2gdsdw[k][2*NP+i]*dsdp[k] + d2gdsdp[k]*dsdw[k][2*NP+i];
          for (l=0; l<NT; l++) dw[2*NP+i] += d2gds2[k][l]*dsdp[k]*dsdw[l][2*NP+i] ;
        }
        dw[2*NP+i] *= -1.0;
      } else dw[2*NP+i] = 0.0;
    }
    
    if (returnMixingProperties) { /* Convert Solution Properties -> Mixing Properties */
      if (modelParameters[NW+0].activeS) dw[NP+NW+0] -= 1.0;
      for (i=0; i<NR; i++) { 
        if (modelParameters[NW  +0].activeS) dw[NP+NW  +0] += r[i]; 
        if (modelParameters[NW+i+1].activeS) dw[NP+NW+i+1] -= r[i]; 
      }
    }
    
    for (i=0; i<(3*NP); i++) if (fabs(dw[i]) < 10.0*DBL_EPSILON) dw[i] = 0.0;
  }

#ifdef USE_GHIORSO_KRESS_MODEL
#undef  V
#undef  DVDT
#undef  DVDP
#undef  D2VDT2
#undef  D2VDTDP
#undef  D2VDP2
#define V(i)       0.0
#define DVDT(i)    0.0
#define DVDP(i)    0.0
#define D2VDT2(i)  0.0
#define D2VDTDP(i) 0.0
#define D2VDP2(i)  0.0
#endif  /* USE_GHIORSO_KRESS_MODEL */

  MTHREAD_MUTEX_UNLOCK(&global_data_mutex);
}

/* ============================================================================
   In the following public routine:
   m = m[i] = moles of the ith component in the liquid, and
   mu*O2    = mu O2 - mu0 O2, defined from the vector o[] 
   This routine should be deprecated as it is inconsistent with conLiq
   ==========================================================================*/

void
muO2Liq(int mask, double t, double p, double *m,
  double *muO2, /* muO2      = mu*O2                 BINARY MASK: 0000000001 */
  double *dm,   /* dm[i]     = d mu*O2/dm[i]         BINARY MASK: 0000000010 */
  double *dt,   /* dt        = d mu*O2/d T           BINARY MASK: 0000000100 */
  double *dp,   /* dp        = d mu*O2/d P           BINARY MASK: 0000001000 */
  double **d2m, /* d2m[i][j] = d mu*O2/dm[i][j]      BINARY MASK: 0000010000 */
  double *d2mt, /* d2mt[i]   = d mu*O2/dm[i]dt       BINARY MASK: 0000100000 */
  double *d2mp, /* d2mp[i]   = d mu*O2/dm[i]dp       BINARY MASK: 0001000000 */
  double *d2t2, /* d2t2      = d mu*O2/dt2           BINARY MASK: 0010000000 */ 
  double *d2tp, /* d2tp      = d mu*O2/dtdp          BINARY MASK: 0100000000 */
  double *d2p2) /* d2p2      = d mu*O2/dp2           BINARY MASK: 1000000000 */
{
  /*-------------------------------------------------------------------------
    The algorithm used is that given by:
    Kress, VC and Carmichael, ISE (1991) The compressibility of silicate
      liquids containing Fe2O3 and the effect of composition, temperature,
      oxygen fugacity and pressure on their redox states.
      Contributions to Mineralogy and Petrology (in press)
    Coefficients for the oxides are initialized in LIQ_STRUCT_DATA.H        
  --------------------------------------------------------------------------*/
  static int indexFeO = -1, indexFe2O3 = -1;
  static const double t0 = 1673.15,                      /* K       */
                       a =    0.196,
                       b =    1.1492e4,                  /* K       */
                       c =   -6.675,
                       e =   -3.364,
                       f =   -7.01e-7  * 1.0e5,          /* K/bar   */
                       g =   -1.54e-10 * 1.0e5,          /* 1/bar   */
                       h =    3.85e-17 * 1.0e5 * 1.0e5;  /* K/bar^2 */
  double mOx[NA], vTemp[NA], mTemp[NA][NA];
  int i, j;
  double sum; 

  liqERRstate = ERR_NONE;

  if ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS)) { 
    muO2Liq_v34(mask, t, p, m, muO2, dm, dt, dp, d2m, d2mt, d2mp, d2t2, d2tp, d2p2);
    return;
  }

  MTHREAD_ONCE(&initThreadBlock, threadInit);

  MTHREAD_MUTEX_LOCK(&global_data_mutex);
  if ((indexFeO == -1) || (indexFe2O3 == -1)) {
    for (i=0; i<nc; i++) { 
      if (bulkSystem[i].type == FEO)   indexFeO   = i;
      if (bulkSystem[i].type == FE2O3) indexFe2O3 = i;
    }
    if (indexFeO == 0 || indexFe2O3 == 0) {
       printf("Fatal error in muO2Liq (LIQUID.C)\n");
       printf("The oxides FeO and Fe2O3 cannot be identified.\n");
       return;
    }
  }
  MTHREAD_MUTEX_UNLOCK(&global_data_mutex);

  for (i=0; i<nc; i++) 
    for (j=0, mOx[i]=0.0; j<nlc; j++) mOx[i] += (liquid[j].liqToOx)[i]*m[j];

  for (i=0, sum=0.0; i<nc; i++) { sum += mOx[i]; } sum += mOx[indexFe2O3];
  if (sum == 0.0 || mOx[indexFeO] == 0.0 || mOx[indexFe2O3] == 0.0) { 
    if (mask & FIRST)   *muO2 = 0.0; 
    if (mask & SECOND)  for (i=0; i<nlc; i++) dm[i] = 0.0;
    if (mask & THIRD)   *dt = 0.0;
    if (mask & FOURTH)  *dp = 0.0;
    if (mask & FIFTH)   {
      for (i=0; i<nlc; i++) for (j=0; j<nlc; j++) d2m[i][j] = 0.0;
    }
    if (mask & SIXTH)   for (i=0; i<nlc; i++) d2mt[i] = 0.0;
    if (mask & SEVENTH) for (i=0; i<nlc; i++) d2mp[i] = 0.0;
    if (mask & EIGHTH)  *d2t2 = 0.0;
    if (mask & NINTH)   *d2tp = 0.0;
    if (mask & TENTH)   *d2p2 = 0.0;
    return; 
  }

  /*-------------------------------------------------------------------------*/

  if (mask & FIRST) {
    double temp;
    if (p < 50000.0) temp = b/t + c + e*(1.0 - t0/t - log(t/t0)) + f*p/t + g*(t-t0)*p/t + h*SQUARE(p)/t;
    else             temp = b/t + c + e*(1.0 - t0/t - log(t/t0)) + f*50000.0/t + g*(t-t0)*50000.0/t + h*SQUARE(50000.0)/t
                          - a*log(10.0)*(608.966*p/10000.0-608.966*5.0)/t;
    for (i=0; i<nc; i++) temp += bulkSystem[i].coeff*mOx[i]/sum;
    temp += 2.0*bulkSystem[indexFeO].coeff*mOx[indexFe2O3]/sum - bulkSystem[indexFe2O3].coeff*mOx[indexFe2O3]/sum;
    *muO2 = R*t*(log(mOx[indexFe2O3]/mOx[indexFeO]) - temp)/a;
  }

  if (mask & SECOND) {
    for (j=0; j<nc; j++) {
      double factor = (j == indexFe2O3) ? 2.0 : 1.0;
      for (i=0, vTemp[j]=0.0; i<nc; i++) 
        vTemp[j] -= (i == j) ? 
          bulkSystem[i].coeff*(1.0-factor*mOx[i]/sum)/sum : 
          - bulkSystem[i].coeff*factor*mOx[i]/SQUARE(sum);  
      vTemp[j] += - (factor*mOx[indexFe2O3]/SQUARE(sum))
        *(bulkSystem[indexFe2O3].coeff-2.0*bulkSystem[indexFeO].coeff);
      if      (j == indexFeO) vTemp[j] += -1.0/mOx[indexFeO];
      else if (j == indexFe2O3) {
        vTemp[j] += 1.0/mOx[indexFe2O3];
        vTemp[j] += (1.0/sum)
          *(bulkSystem[indexFe2O3].coeff-2.0*bulkSystem[indexFeO].coeff);
      }
      vTemp[j] *= R*t/a;
    }
    for (i=0; i<nlc; i++)
      for (j=0, dm[i]=0.0; j<nc; j++) dm[i] += vTemp[j]*(liquid[i].liqToOx)[j];
  }

  if (mask & THIRD) {
    double temp;
    if (p < 50000.0) temp = b/t + c + e*(1.0 - t0/t - log(t/t0)) + f*p/t + g*(t-t0)*p/t + h*SQUARE(p)/t;
    else             temp = b/t + c + e*(1.0 - t0/t - log(t/t0)) + f*50000.0/t + g*(t-t0)*50000.0/t + h*SQUARE(50000.0)/t
                          - a*log(10.0)*(608.966*p/10000.0-608.966*5.0)/t;
    for (i=0; i<nc; i++) temp += bulkSystem[i].coeff*mOx[i]/sum;
    temp += 2.0*bulkSystem[indexFeO].coeff*mOx[indexFe2O3]/sum - bulkSystem[indexFe2O3].coeff*mOx[indexFe2O3]/sum;
    *dt = R*(log(mOx[indexFe2O3]/mOx[indexFeO]) - temp)/a + R*t*(b/SQUARE(t) - e*(t0/t-1.0)*(1.0/t))/a;
    if (p < 50000.0) *dt += R*t*(f*p/SQUARE(t) - g*(t0/t)*(p/t) + h*SQUARE(p/t))/a;
    else             *dt += R*t*(f*50000.0/SQUARE(t) - g*(t0/t)*(50000.0/t) + h*SQUARE(50000.0/t)
                                 - a*log(10.0)*(608.966*p/10000.0-608.966*5.0)/SQUARE(t))/a;
  }

  if (mask & FOURTH) {
    if (p < 50000.0) *dp = R*t*(-f/t - g*(t-t0)/t - 2.0*h*p/t)/a;
    else             *dp = R*t*(a*log(10.0)*608.966/10000.0/t)/a;
  }

  if (mask & FIFTH) {
    int k, l;
    for (k=0; k<nc; k++) {
      double factorK = (k == indexFe2O3) ? 2.0 : 1.0;
      for (j=0; j<nc; j++) {
        double factorJ = (j == indexFe2O3) ? 2.0 : 1.0;
        for (i=0, mTemp[k][j]=0.0; i<nc; i++) {
          mTemp[k][j] -= 
            2.0*factorJ*factorK*bulkSystem[i].coeff*mOx[i]/CUBE(sum);
          if (i == j) mTemp[k][j] -= - factorK*bulkSystem[i].coeff/SQUARE(sum);
          if (i == k) mTemp[k][j] -= - factorJ*bulkSystem[i].coeff/SQUARE(sum);
        } 
        mTemp[k][j] += 2.0*(factorJ*factorK*mOx[indexFe2O3]/CUBE(sum))
          *(bulkSystem[indexFe2O3].coeff-2.0*bulkSystem[indexFeO].coeff);
        if      (j == indexFeO && k == indexFeO) 
          mTemp[k][j] += 1.0/SQUARE(mOx[indexFeO]);
        else if (j == indexFe2O3 && k == indexFe2O3) {
          mTemp[k][j] += -1.0/SQUARE(mOx[indexFe2O3]);
          mTemp[k][j] += -((factorJ+factorK)/SQUARE(sum))
            *(bulkSystem[indexFe2O3].coeff-2.0*bulkSystem[indexFeO].coeff);
        }
        else if (j == indexFe2O3) mTemp[k][j] += -(factorK/SQUARE(sum))
            *(bulkSystem[indexFe2O3].coeff-2.0*bulkSystem[indexFeO].coeff);
        else if (k == indexFe2O3) mTemp[k][j] += -(factorJ/SQUARE(sum))
            *(bulkSystem[indexFe2O3].coeff-2.0*bulkSystem[indexFeO].coeff);
        mTemp[k][j] *= R*t/a;
      }
    }
    for (i=0; i<nlc; i++) for (j=0; j<nlc; j++) 
      for (k=0, d2m[i][j]=0.0; k<nc; k++) for (l=0; l<nc; l++)
        d2m[i][j] += mTemp[k][l]*(liquid[i].liqToOx)[k]*(liquid[j].liqToOx)[l];
  }

  if (mask & SIXTH) {
    for (j=0; j<nc; j++) {
      double factor = (j == indexFe2O3) ? 2.0 : 1.0;
      for (i=0, vTemp[j]=0.0; i<nc; i++) 
        vTemp[j] -= (i == j) ? 
          bulkSystem[i].coeff*(1.0-factor*mOx[i]/sum)/sum : 
          - bulkSystem[i].coeff*factor*mOx[i]/SQUARE(sum);  
      vTemp[j] += - (factor*mOx[indexFe2O3]/SQUARE(sum))
        *(bulkSystem[indexFe2O3].coeff-2.0*bulkSystem[indexFeO].coeff);
      if      (j == indexFeO) vTemp[j] += -1.0/mOx[indexFeO];
      else if (j == indexFe2O3) {
        vTemp[j] += 1.0/mOx[indexFe2O3];
        vTemp[j] += (1.0/sum)
          *(bulkSystem[indexFe2O3].coeff-2.0*bulkSystem[indexFeO].coeff);
      }
      vTemp[j] *= R/a;
    }
    for (i=0; i<nlc; i++) for (j=0, d2mt[i]=0.0; j<nc; j++) 
      d2mt[i] += vTemp[j]*(liquid[i].liqToOx)[j];
  }

  if (mask & SEVENTH) {
    for (i=0; i<nlc; i++) d2mp[i] = 0.0;
  }

  if (mask & EIGHTH) {

    *d2t2 = 2.0*R*(b/SQUARE(t) - e*(t0/t-1.0)*(1.0/t))/a
          + R*t*(-2.0*b/CUBE(t) - e*(1.0 - 2.0*t0/t)/SQUARE(t))/a;
  }

  if (mask & NINTH) {
    if (p < 50000.0) *d2tp = -R*(f/t + g*(t-t0)/t + 2.0*h*p/t)/a + R*t*(f/SQUARE(t) - g*(t0/t)/t + 2.0*h*p/SQUARE(t))/a;
    else             *d2tp = -R*(-a*log(10.0)*608.966/10000.0/t)/a + R*t*(-a*log(10.0)*608.966/10000.0/SQUARE(t))/a;
  }

  if (mask & TENTH) {
    if (p < 50000.0) *d2p2 = - (R*t*2.0*h/t)/a;
    else             *d2p2 = 0.0;
  }

}

void 
visLiq(int mask, double t, double p, double *r, 
  double *viscosity  /* log(10) viscosity            BINARY MASK: 00000001 */
  )
{
  double coeff[NA], factor[NA], m[NA], x[NA], sum;
  int nSiO2 = -1, i, j;

  liqERRstate = ERR_NONE;

  if ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS)) { visLiq_v34(mask, t, p, r, viscosity); return; }

  MTHREAD_ONCE(&initThreadBlock, threadInit);

  struct _shawModel {
    char   *oxide;
    double coeff;
    double factor;
  } shawModel[] = {
    { "TiO2",	4.5, 1.0 }, { "Al2O3",  6.7, 2.0 }, 
    { "Fe2O3",  3.4, 2.0 }, { "FeO",	3.4, 1.0 }, 
    { "MgO",	3.4, 1.0 }, { "CaO",	4.5, 1.0 },
    { "Na2O",	2.8, 1.0 }, { "K2O",	2.8, 1.0 }, 
    { "H2O",	2.0, 1.0 }
  };
  const int nShaw = (sizeof shawModel / sizeof(struct _shawModel));
    
  for (j=0; j<NA; j++) { coeff[j] = 0.0; factor[j] = 0.0; }
  for (i=0; i<nShaw; i++) {
    for (j=0; j<NA; j++) if (strcmp(shawModel[i].oxide, bulkSystem[j].label) == 0) {
      coeff[j]  = shawModel[i].coeff; 
      factor[j] = shawModel[i].factor;
      break; 
    }
  } 
  for (i=0; i<NA; i++) if (strcmp("SiO2", bulkSystem[i].label) == 0) { nSiO2 = i; break; } 

  if (nSiO2 == -1) { *viscosity = 0.0; return; }

  /* m[0] --> m[NA-1] is an array of mole fractions of liquid components      */
  for (m[0]=1.0, i=0; i<NR; i++) { m[0] -= r[i]; m[i+1] = r[i]; }

  /* convert m[] -> x[] : mole fractions of liquid comp -> moles of oxides    */
  for (i=0; i<NA; i++) 
    for (j=0, x[i]=0.0; j<NA; j++) x[i] += (liquid[j].liqToOx)[i]*m[j];

  /* Convert to the Shaw mole fractions                                       */
  for (i=0, sum=0.0; i<NA; i++) { 
    if (factor[i] > 0.0) x[i] *= factor[i];
    sum += x[i];
  }
  for (i=0; i<NA; i++) x[i] /= (sum != 0.0) ? sum : 1.0;

  if (mask & FIRST) {
    for (i=0, *viscosity=0.0; i<NA; i++) *viscosity += coeff[i]*x[nSiO2]*x[i];
    *viscosity /= (x[nSiO2] < 1.0) ? 1.0 - x[nSiO2] : 1.0; 
    *viscosity  = (*viscosity)*(10000.0/t - 1.50)  - 6.40; 
    *viscosity /= log(10.0);
  }
}

/* end of file LIQUID.C */
