#include <iostream>
#include <stdio.h>
#include <math.h>
#include "SulfLiq.h"

/*
 * Global (to this file): activity definitions and component transforms
 *    The function conBio defines the conversion from m[i], to r[j]
 */
#define NR         4
#define NS         0
#define NA         5

#define TRUE  1
#define FALSE 0

#define SQUARE(x) ((x)*(x))
#define CUBE(x)   ((x)*(x)*(x))
#define QUARTIC(x) ((x)*(x)*(x)*(x))

#define R 8.3143

/*
 *==============================================================================
 * Argument BITMASKs for public solid solution functions:
 */
#define FIRST       00000001 /* octal for binary 00000000000000000001 */
#define SECOND      00000002 /* octal for binary 00000000000000000010 */
#define THIRD       00000004 /* octal for binary 00000000000000000100 */
#define FOURTH      00000010 /* octal for binary 00000000000000001000 */
#define FIFTH       00000020 /* octal for binary 00000000000000010000 */
#define SIXTH       00000040 /* octal for binary 00000000000000100000 */
#define SEVENTH     00000100 /* octal for binary 00000000000001000000 */
#define EIGHTH      00000200 /* octal for binary 00000000000010000000 */
#define NINTH       00000400 /* octal for binary 00000000000100000000 */
#define TENTH       00001000 /* octal for binary 00000000001000000000 */
#define ELEVENTH    00002000 /* octal for binary 00000000010000000000 */
#define TWELFTH     00004000 /* octal for binary 00000000100000000000 */
#define THIRTEENTH  00010000 /* octal for binary 00000001000000000000 */
#define FOURTEENTH  00020000 /* octal for binary 00000010000000000000 */
#define FIFTEENTH   00040000 /* octal for binary 00000100000000000000 */
#define SIXTEENTH   00100000 /* octal for binary 00001000000000000000 */
#define SEVENTEENTH 00200000 /* octal for binary 00010000000000000000 */
#define EIGHTEENTH  00400000 /* octal for binary 00100000000000000000 */
#define NINETEENTH  01000000 /* octal for binary 01000000000000000000 */
#define TWENTIETH   02000000 /* octal for binary 10000000000000000000 */

/*
 * Global (to this file): derivative definitions
 */
/*
 *=============================================================================
 * Public functions:
 *    mask  -  bitwise mask for selecting output
 *    t     -  Temperature (K)
 *    p     -  Pressure (bars)
 *    *x    -  (pointer to x[]) Array of independent compositional variables
 */
extern "C" int testSLq(int mask, double t, double p,
  int na,          /* Expected number of endmember components                 */
  int nr,          /* Expected number of independent compositional variables  */
  char **names,    /* array of strings of names of endmember components       */
  char **formulas, /* array of strings of formulas of endmember components    */
  double *r,       /* array of indepependent compos variables, check bounds   */
  double *m)       /* array of moles of endmember components, check bounds    */
{
  const char *phase = "sulfideLiquid.cc";
  const char *NAMES[NA]    = { "O", "S", "Fe", "Ni", "Cu" };
  const char *FORMULAS[NA] = { "O", "S", "Fe", "Ni", "Cu" };
  int result = TRUE, i;
  double sum;

  if (mask & FIRST) {
    result = result && (na == NA);
    if (!result) printf("<<%s>> Wrong number of components!", phase);
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

extern "C" void conSLq(int inpMask, int outMask, double t, double p,
  double *e,      /* comp of biotite in moles of elements                     */
  double *m,      /* comp of biotite in moles of endmember components         */
  double *r,      /* comp of biotite in terms of the independent comp var     */
  double *x,      /* comp of biotite in mole fractions of endmember comp      */
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
      endmember biotite components.
  (2) calculates from a vector of moles of endmember components, one or
      all of: r[], x[], dr[]/dm[], d2r[]/dm[]dm[], or d3r[]/dm[]dm[]dm[]
  (3) calculates from a vector of independent compositional variables
      mole fractions of endmember components and/or the Jacobian matrix
      dx[]/dr[]

  In this routine it is assumed that the elements are in the order of atomic 
  numbers and that the order of biotite components has been verified as:
        m[0] = annite     (KFe3Si3AlO10(OH)2),
        m[1] = phlogopite (KMg3Si3AlO10(OH)2) . 

  ----------------------------------------------------------------------------*/

  int i, j, k;

  if (inpMask == FIRST && outMask == SECOND) {
    static const int O  =  8;
    static const int S  = 16;
    static const int Fe = 26;
    static const int Ni = 28;
    static const int Cu = 29;
    
    m[0] = e[ O]; 
    m[1] = e[ S];
    m[2] = e[Fe];
    m[3] = e[Ni];
    m[4] = e[Cu];

  } else if (inpMask == SECOND) {
    double sum;

    if (outMask & ~(THIRD | FOURTH | FIFTH | SIXTH | EIGHTH))
      printf("Illegal call to conSLq with inpMask = %o and outMask = %o\n",
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
      printf("Illegal call to conSLq with inpMask = %o and outMask = %o\n",
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
    printf("Illegal call to conSLq with inpMask = %o and outMask = %o\n",
      inpMask, outMask);
  }

}

extern "C" void dispSLq(int mask, double t, double p, double *x,
  char **formula            /* Mineral formula for interface display MASK: 1 */
  )
{
  double *r = x;
  static char masterString[] = {
/*             1111111111222222222233333333334444444444555555555566666666667
     01234567890123456789012345678901234567890123456789012345678901234567890 */
    "O_.__S_.__Fe_.__Ni_.__Cu_.__" };

  if (mask & FIRST) {
    char *string = strcpy((char *) malloc((size_t) (strlen(masterString)+1)*sizeof(char)), masterString);
    char n[5];
    int i;

    (void) snprintf(n, 5, "%4.2f", 1.0-r[0]-r[1]-r[2]-r[3]); for (i=0; i<4; i++) string[ 1+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", r[0]);                    for (i=0; i<4; i++) string[ 6+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", r[1]);                    for (i=0; i<4; i++) string[12+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", r[2]);                    for (i=0; i<4; i++) string[18+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", r[3]);                    for (i=0; i<4; i++) string[24+i] = n[i];

    *formula = string;
  }
}

static SulfLiq *update(double t, double p, double *r) {
  static SulfLiq *solution = NULL;
  static double rOld[NR] = { 0.0, 0.0, 0.0, 0.0 }, tOld = -9999.0, pOld = -9999.0; 

  if (!solution) {
    static const double spectol=1.e-16;
    solution = new SulfLiq(); 
    solution->setSpeciateTolerance(spectol);
  }
  
  if (t != tOld) { solution->setTk(t);       tOld = t; }
  if (p != pOld) { solution->setPa(p*1.0e5); pOld = p; }
  
  if ( (r[0] != rOld[0]) || (r[1] != rOld[1]) || (r[2] != rOld[2]) || (r[3] != rOld[3]) ) {
    double *comp = new double[NA];
    comp[0] = 1.0 - r[0] - r[1] - r[2] - r[3];
    comp[1] = r[0];  rOld[0] = r[0];
    comp[2] = r[1];  rOld[1] = r[1];
    comp[3] = r[2];  rOld[2] = r[2];
    comp[4] = r[3];  rOld[3] = r[3];
    solution->setComps(comp);
  }
  
  return solution;
}

extern "C" void actSLq(int mask, double t, double p, double *r, 
  double *a,  /* (pointer to a[]) activities              BINARY MASK: 0001 */
  double *mu, /* (pointer to mu[]) chemical potentials    BINARY MASK: 0010 */
  double **dx /* (pointer to dx[][]) d(a[])/d(x[])        BINARY MASK: 0100 */
  )           /* exclusion criteria applied to results if BINARY MASK: 1000 */
{
  double *comp = new double[NA];
  int i;
  
  SulfLiq *solution = update(t, p, r);

  if (mask & FIRST) {
    for(i=0; i<NA; i++) {
       a[i] = solution->getActivity(i);
    }
  }

  if (mask & SECOND) {
    for(i=0; i<NA; i++) {
       mu[i] = solution->getSpecMu(i) - solution->getMu0(i);
    }
  }

  if (mask & THIRD) {
    int j;
    for(i=0; i<NA; i++) for (j=0; j<NR; j++) dx[i][j] = 0.0;
  }

  if (mask & FOURTH) {
    /* implement exclusion criteria on quantities for preclb routines  */
    static const double exclusion[NA] = {
       0.0,  /* exclusion criteria on the mole fraction of O  */
       0.0,  /* exclusion criteria on the mole fraction of S  */
       0.0,  /* exclusion criteria on the mole fraction of Fe */
       0.0,  /* exclusion criteria on the mole fraction of Ni */
       0.0,  /* exclusion criteria on the mole fraction of Cu */
    };

    for (i=0; i<NA; i++) {
      int j;
      if (comp[i] < exclusion[i]) {
        if (mask & FIRST)  a[i]  = 0.0;
        if (mask & SECOND) mu[i] = 0.0;
        if (mask & THIRD)  for (j=0; j<NR; j++) dx[i][j] = 0.0;
      }
    }
  }

}

extern "C" void gmixSLq(int mask, double t, double p, double *r, 
  double *gmix, /* Gibbs energy of mixing             BINARY MASK: 0001 */
  double *dx,   /* (pointer to dx[]) d(g)/d(x[])      BINARY MASK: 0010 */
  double **dx2, /* (pointer to dx2[][]) d2(g)/d(x[])2 BINARY MASK: 0100 */
  double ***dx3 /* (pointer to dx3[][][]) d3(g)/d(x[])3 NARY MASK: 1000 */
  )
{
  SulfLiq *solution = update(t, p, r);
  
  if (mask & FIRST) {
    *gmix = solution->getGmix();  
  }
  
  if(mask & SECOND) {
    dx[0] = 0.0;
  }

  if(mask & THIRD) {
    int i, j;
    for (i=0; i<NR; i++) {
       for (j=0; j<NR; j++) dx2[i][j] = 0.0;
    }
  }

  if (mask & FOURTH) {
    int i, j, k;
    for (i=0; i<NR; i++) {
      for (j=0; j<NR; j++) {
	    for (k=0; k<NR; k++) dx3[i][j][k] = 0.0;
      }
    }
  }

}

extern "C" void hmixSLq(int mask, double t, double p, double *r, 
  double *hmix /* Enthalpy of mixing BINARY MASK: 1 */
  )
{
  SulfLiq *solution = update(t, p, r);
  *hmix = solution->getHmix();
}

extern "C" void smixSLq(int mask, double t, double p, double *r, 
  double *smix, /* Entropy of mixing                  BINARY MASK: 001 */
  double *dx,   /* (pointer to dx[]) d(s)/d(x[])      BINARY MASK: 010 */
  double **dx2  /* (pointer to dx2[][]) d2(s)/d(x[])2 BINARY MASK: 100 */
  )
{
  SulfLiq *solution = update(t, p, r);

  if (mask & FIRST) {
    *smix = solution->getSmix(); 
  }
  
  if(mask & SECOND) {
    int i;
    for (i=0; i<NR; i++) dx[i] = 0.0;
  }

  if(mask & THIRD) {
    int i, j;
    for (i=0; i<NR; i++) {
       for (j=0; j<NR; j++) dx2[i][j] = 0.0;
    }
  }

}

extern "C" void cpmixSLq(int mask, double t, double p, double *r, 
  double *cpmix, /* Heat capacity of mixing               BINARY MASK: 001 */
  double *dt,    /* d(cp)/d(t)                            BINARY MASK: 010 */
  double *dx     /* d(cp)/d(x[])d(t)                      BINARY MASK: 100 */
  )
{
  SulfLiq *solution = update(t, p, r);

  if (mask & FIRST) {
    *cpmix = solution->getCpmix();
  }

  if(mask & SECOND) {
    *dt = solution->getdCpdTmix();
  }

  if(mask & THIRD) {
    int i;
    for (i=0; i<NR; i++) dx[i] = 0.0;
  }

}

extern "C" void vmixSLq(int mask, double t, double p, double *r, 
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
  SulfLiq *solution = update(t, p, r);

  if (mask & FIRST) {
    *vmix = solution->getVmix()*1.0e5;
  }

  if(mask & SECOND) {
    int i;
    for (i=0; i<NR; i++) dx[i] = 0.0; 
  }

  if(mask & THIRD) {
    int i, j;
    for (i=0; i<NR; i++) {
       for (j=0; j<NR; j++) dx2[i][j] = 0.0;
    }
  }

  if(mask & FOURTH) {
    *dt = solution->getdVdTmix()*1.0e5;
  }

  if(mask & FIFTH) {
    *dp = 0.0; // solution->getdVdP()*1.0e5*1.0e5;
  }

  if(mask & SIXTH) {
    *dt2 = 0.0; // solution->getd2VdT2()*1.0e5;
  }

  if(mask & SEVENTH) {
    *dtdp = 0.0; // solution->getd2VdTdP()*1.0e5*1.0e5;
  }

  if(mask & EIGHTH) {
    *dp2 = 0.0; // solution->getd2VdP2()*1.0e5*1.0e5*1.0e5;
  }

  if(mask & NINTH) {
    int i;
    for (i=0; i<NR; i++) dxdt[i] = 0.0; 
  }

  if(mask & TENTH) {
    int i;
    for (i=0; i<NR; i++) dxdp[i] = 0.0; 
  }

}