#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "recipes.h"

#define NV  19  /* Number of indepedent variables in model */
#define NS   1  /* Number of ordering parameters in model  */
#define NP  (1+2*NV+NV*(NV-1)/2)

double frac(double v, int *n, int *d, double error);

static char *fracString(double fraction, int *p, int *n, int *d)
{
  int num, denom;
  static char string[9], sign;

  if (fraction < 0.0) { sign = '-'; fraction *= -1.0; *p = -1; }
  else                { sign = ' '; *p = 1; }

  if (frac(fraction, &num, &denom, sqrt(DBL_EPSILON)) < 0.0) {
    (void) snprintf(string, 9, "%c%7.4f", sign, fraction);
  } else {
    if (num == 1 && denom == 1) (void) snprintf(string, 9, "%c       ", sign);
    else (void) snprintf(string, 9, "%c%3d/%-3d", sign, num, denom);
  }
  *n = num; *d = denom;
  return string;
}

static void load(double *array, double coeff, ...)
{
  double p[NV];
  int i, j, n;
  va_list args;

  va_start(args, coeff);
  for (i=0; i<NV; i++) p[i] = va_arg(args, double);
  va_end(args);

  array[0] += coeff;
  for (i=0, n=1; i<NV; i++, n++) if (p[i] != 0.0) array[n] += coeff*p[i];
  for (i=0; i<NV; i++) for (j=i; j<NV; j++, n++) 
    if (p[i] != 0.0 && p[j] != 0.0) array[n] += coeff*p[i]*p[j];
}

static void initialize(double *array, char **string, char *label)
{
  int i;

  *string = (char *) malloc((unsigned) (strlen(label)+1)*sizeof(char));
  (void) strcpy(*string, label);

  for (i=0; i<NP; i++) array[i] = 0.0;
}

int main (int argc, char *argv[])
{
  int c, d, dd, i, j, k, n = 0, first, prefix, num, denom;
  double **m, **v, *w, *b, **x;
  char   **names, *e;
  FILE   *includeFile;
  time_t dateTime;
  const char *param[NV] = { 
    "rTiO2",      "rAl2O3",   "rFe2O3",   "rMgCr2O4", "rFe2SiO4", "rMn2SiO4", 
    "rMg2SiO4",   "rNi2SiO4", "rCo2SiO4", "rCa2SiO4", "rNa2SiO3", "rK2SiO3", 
    "rCa3(PO4)2", "rCO2",     "rSO3",     "rCl2O-1",  "rF2O-1",   "rH2O",     
    "s" };
  struct {
    const char *name;
    double     r[NV];
    double     coeff;
  } species[NV+1] = {
    { "Si4O8",      {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0},
                     1.0 },
    { "TiO2",       {1.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   
                     0.0},
                     1.0 },
    { "Al4O6",      {0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   
                     0.0},
                     1.0 },
    { "Fe2O3",      {0.0,   0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   
                     0.0},
                     1.0 },
    { "MgCr2O4",    {0.0,   0.0,   0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   
                     0.0},
                     1.0 },
    { "Fe2SiO4",    {0.0,   0.0,   0.0,   0.0,   1.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   
                     0.0},
                     1.0 },
    { "MnSi0.5O2",  {0.0,   0.0,   0.0,   0.0,   0.0,   1.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   
                     0.0},
                     1.0 },
    { "Mg2SiO4",    {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   1.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   
                     0.0},
                     1.0 },
    { "NiSi0.5O2",  {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   1.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   
                     0.0},
                     1.0 },
    { "CoSi0.5O2",  {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   1.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   
                     0.0},
                     1.0 },
    { "Ca2Si2O6",   {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     1.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0, 
                     0.0},
                     1.0 },
    { "NaSi0.5O1.5",{0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   
                     0.0},
                     1.0 },
    { "KAlSiO4",    {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   
                     0.0},
                     1.0 },
    { "Ca3(PO4)2",  {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   1.0,   0.0,   0.0,   0.0,   0.0,   0.0, 
                     0.0},
                     1.0 },
    { "CO2",        {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   1.0,   0.0,   0.0,   0.0,   0.0,
                     0.0},
                     1.0 },
    { "SO3",        {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   1.0,   0.0,   0.0,   0.0,
                     0.0},
                     1.0 },
    { "Cl2O-1",     {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   1.0,   0.0,   0.0,
                     0.0},
                     1.0 },
    { "F2O-1",      {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   1.0,   0.0,
                     0.0},
                     1.0 },
    { "H2O",        {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   1.0,
                     0.0},
                     1.0 },
    { "Mg2Si2O6",   {0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.8,   0.0,   0.0,
                     0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,   0.0,
                     1.0},
                     1.25 }
  };
  struct {
    int i;
    int j;
  } index[NP+1];

  m     = matrix (1, NP, 1, NP);
  names = (char **) malloc ((unsigned) (NP+1)*sizeof(char *));

  printf("Initializing coefficient matrix...\n");

  /* First-order Taylor terms */

  for (i=0; i<(NV+1); i++) {
    n++; initialize (&m[n][1],&names[n], (char *) species[i].name);
    load (&m[n][1], species[i].coeff, 
       (species[i].r)[ 0], (species[i].r)[ 1], (species[i].r)[ 2], 
       (species[i].r)[ 3], (species[i].r)[ 4], (species[i].r)[ 5], 
       (species[i].r)[ 6], (species[i].r)[ 7], (species[i].r)[ 8], 
       (species[i].r)[ 9], (species[i].r)[10], (species[i].r)[11], 
       (species[i].r)[12], (species[i].r)[13], (species[i].r)[14], 
       (species[i].r)[15], (species[i].r)[16], (species[i].r)[17], 
       (species[i].r)[18]);
  }

  /* Second-order Taylor terms: binary interaction parameters
     join A-B ==>  4 ( G(A/2+B/2) - G(A)/2 - G(B)/2 )            */

#define W(AX2,  AX3,  AX4,  AX5,  AX6,  AX7,  AX8,  AX9,  AX10, AX11, AX12, \
          AX13, AX14, AX15, AX16, AX17, AX18, AX19, AS1,  ACOEFF, \
          BX2,  BX3,  BX4,  BX5,  BX6,  BX7,  BX8,  BX9,  BX10, BX11, BX12, \
          BX13, BX14, BX15, BX16, BX17, BX18, BX19, BS1,  BCOEFF) \
  load (&m[n][1],  4.0*((ACOEFF)+(BCOEFF))/2.0, \
                        (AX2 +BX2 )/2.0, (AX3 +BX3 )/2.0, (AX4 +BX4 )/2.0, \
                        (AX5 +BX5 )/2.0, (AX6 +BX6 )/2.0, (AX7 +BX7 )/2.0, \
                        (AX8 +BX8 )/2.0, (AX9 +BX9 )/2.0, (AX10+BX10)/2.0, \
                        (AX11+BX11)/2.0, (AX12+BX12)/2.0, (AX13+BX13)/2.0, \
                        (AX14+BX14)/2.0, (AX15+BX15)/2.0, (AX16+BX16)/2.0, \
                        (AX17+BX17)/2.0, (AX18+BX18)/2.0, (AX19+BX19)/2.0, \
                        (AS1 +BS1 )/2.0); \
  load (&m[n][1], -2.0*(ACOEFF), \
                        AX2,  AX3,  AX4,  AX5,  AX6,  AX7,  AX8,  AX9,  \
                        AX10, AX11, AX12, AX13, AX14, AX15, AX16, AX17, \
                        AX18, AX19, AS1); \
  load (&m[n][1], -2.0*(BCOEFF), \
                        BX2,  BX3,  BX4,  BX5,  BX6,  BX7,  BX8,  BX9,  \
                        BX10, BX11, BX12, BX13, BX14, BX15, BX16, BX17, \
                        BX18, BX19, BS1);

  for (i=0; i<(NV+1); i++) {
    for (j=i+1; j<(NV+1); j++) {
      char label[23];
      (void) snprintf(label, 23, "W%10.10s-%10.10s", species[i].name, species[j].name);
      n++; initialize (&m[n][1],&names[n], label);
      W(   (species[i].r)[ 0], (species[i].r)[ 1], (species[i].r)[ 2], 
           (species[i].r)[ 3], (species[i].r)[ 4], (species[i].r)[ 5], 
           (species[i].r)[ 6], (species[i].r)[ 7], (species[i].r)[ 8], 
           (species[i].r)[ 9], (species[i].r)[10], (species[i].r)[11], 
           (species[i].r)[12], (species[i].r)[13], (species[i].r)[14], 
           (species[i].r)[15], (species[i].r)[16], (species[i].r)[17], 
           (species[i].r)[18],
           1.0 /* species[i].coeff */,
           (species[j].r)[ 0], (species[j].r)[ 1], (species[j].r)[ 2],
           (species[j].r)[ 3], (species[j].r)[ 4], (species[j].r)[ 5],
           (species[j].r)[ 6], (species[j].r)[ 7], (species[j].r)[ 8],
           (species[j].r)[ 9], (species[j].r)[10], (species[j].r)[11],
           (species[j].r)[12], (species[j].r)[13], (species[j].r)[14],
           (species[j].r)[15], (species[j].r)[16], (species[j].r)[17],
           (species[j].r)[18],
           1.0 /* species[j].coeff */
       )
      index[n].i = i;
      index[n].j = j;
    }
  }

  /****************************************************************************
   End of Taylor expansion coefficient definitions 
   ****************************************************************************/

  for (i=n+1; i<=NP; i++) initialize (&m[i][1], &names[i], "");

  v = matrix (1, NP, 1, NP);
  w = vector (1, NP); 
  b = vector (1, NP); 
  x = matrix (1, NP, 1, NP); 
  e = (char *) malloc ((unsigned) (NP+1)*sizeof(char));
  for (i=1; i<=NP; i++) e[i] = '1';

  printf("Performing singular value analysis of coefficient matrix...\n");
  svdcmp(m, NP, NP, w, v);
  for (i=1, j=0; i<=NP; i++) if (fabs(w[i]) < DBL_EPSILON) { w[i] = 0.0; j++; }
  if (NP-j < n) printf("Problem is rank deficient! rank = %d\n", NP-j);
  printf("Performing back-substitution phase...\n");
  for (i=1; i<=NP; i++) {
    for (j=1; j<=NP; j++) b[j] = (i == j) ? 1.0 : 0.0;
    svbksb(m, w, v, NP, NP, b, e, x[i]);
  }

  includeFile = fopen("liquid-model.h", "w");
  (void) time(&dateTime);

  fprintf(includeFile, "/*\n");
  fprintf(includeFile, "  Gibbs Energy        %s", asctime(localtime(&dateTime)));
  fprintf(includeFile, "*/\n");
  n = 1;
  for (j=1, first=1; j<=NP; j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
    if (first) { 
      first = 0; printf("g[     0]       ");                                     c  = 16; 
      dd = fprintf(includeFile, "  Gconst = ");                                  d  = dd;
    }
    printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
    fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
    if (denom != 1) {
      dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
    } else if (num != 1) {
      dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
    }
    if (j == 1) {
      dd = fprintf(includeFile, "(G(0))");                                       d += dd;
    } else {
      dd = fprintf(includeFile, "(G(%1.d))", j-1);                               d += dd;
    }
    if (c > 100) { 
      printf("\n"); 
      printf("                ");                                                c  = 16; 
    }
    if (d >  70) { 
      fprintf(includeFile, "\n"); 
      dd = fprintf(includeFile, "           ");                                  d  = dd; 
    }
  }
  if (!first) printf("\n");
  fprintf(includeFile, ";\n");

  n = 2;
  for (i=0; i<NV; i++, n++) {
    for (j=1, first=1; j<=NP; j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
      if (first) { 
        first = 0; printf("g[%6.6s]       ", param[i]);                            c  = 16; 
        if ((n-2) == 0) {
          dd = fprintf(includeFile, "  gr[ 0] = ");                                d  = dd;
        } else if (((n-2) > 0) && ((n-2) < (NV-NS))) {
          dd = fprintf(includeFile, "  gr[%2.d] = ", n-2);                         d  = dd;
        } else if (((n-2) > 0) && ((n-2) == (NV-NS))) {
          dd = fprintf(includeFile, "  gs[ 0] = ");                                d  = dd;
        } else {
          dd = fprintf(includeFile, "  gs[%2.d] = ", n-2-(NV-NS));                 d  = dd;
        }
     } 
      printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (j == 1) {
        dd = fprintf(includeFile, "(G(0))");                                       d += dd;      
      } else if (j <= (NV+1)) {
        dd = fprintf(includeFile, "(G(%1.d))", j-1);                               d += dd;
      } else if (index[j].i == 0 && index[j].j == 0) {
        dd = fprintf(includeFile, "(W(0,0))");                                     d += dd;
      } else if (index[j].i == 0) {
        dd = fprintf(includeFile, "(W(0,%1.d))", index[j].j);                      d += dd;
      } else if (index[j].j == 0) {
        dd = fprintf(includeFile, "(W(%1.d,0))", index[j].i);                      d += dd;
      } else {
        dd = fprintf(includeFile, "(W(%1.d,%1.d))", index[j].i, index[j].j);       d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "           ");                                  d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  for (i=0; i<NV; i++) for (j=i; j<NV; j++, n++) {
    for (k=1, first=1; k<=NP; k++) if (fabs(x[k][n]) > sqrt(DBL_EPSILON)) { 
      if (first) { 
        first = 0; printf("g[%6.6s,%6.6s]", param[i], param[j]);                   c  = 16; 
        if (i == 0 && j == 0) {
          dd = fprintf(includeFile, "  grr[ 0][ 0] = ");                           d  = dd;
        } else if (i == 0) {
          if (j < (NV-NS)) {
            dd = fprintf(includeFile, "  grr[ 0][%2.d] = ", j);                    d  = dd;
          } else if (j == (NV-NS)) {
            dd = fprintf(includeFile, "  grs[ 0][ 0] = ");                         d  = dd;
          } else {
            dd = fprintf(includeFile, "  grs[ 0][%2.d] = ", j-(NV-NS));            d  = dd;
          }
        } else if (i < (NV-NS)) {
          if (j < (NV-NS)) {
            dd = fprintf(includeFile, "  grr[%2.d][%2.d] = ", i, j);               d  = dd;
          } else if (j == (NV-NS)) {
            dd = fprintf(includeFile, "  grs[%2.d][ 0] = ", i);                    d  = dd;
          } else {
            dd = fprintf(includeFile, "  grs[%2.d][%2.d] = ", i, j-(NV-NS));       d  = dd;
          }
        } else if (i == (NV-NS)) {
          if (j == (NV-NS)) {
            dd = fprintf(includeFile, "  gss[ 0][ 0] = ");                         d  = dd;
          } else {
            dd = fprintf(includeFile, "  gss[ 0][%2.d] = ", j-(NV-NS));            d  = dd;
          } 
        } else {
          dd = fprintf(includeFile, "  gss[%2.d][%2.d] = ", i-(NV-NS), j-(NV-NS)); d  = dd;
        }
      } 
      printf(" %s %s", fracString(x[k][n], &prefix, &num, &denom), names[k]); 
      c += 10 + strlen(names[k]);
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (k == 1) {
        fprintf(includeFile, "(G(0))");                                            d +=  2;
      } else if (k <= (NV+1)) {
        dd = fprintf(includeFile, "(G(%1.d))", k-1);                               d += dd;
      } else if (index[k].i == 0 && index[k].j == 0) {
        dd = fprintf(includeFile, "(W(0,0))");                                     d += dd; 
      } else if (index[k].i == 0) {
        dd = fprintf(includeFile, "(W(0,%1.d))", index[k].j);                      d += dd;
      } else if (index[k].j == 0) {
        dd = fprintf(includeFile, "(W(%1.d,0))", index[k].i);                      d += dd;
      } else { 
        dd = fprintf(includeFile, "(W(%1.d,%1.d))", index[k].i, index[k].j);       d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "                ");                             d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  fprintf(includeFile, "/*\n");
  fprintf(includeFile, "  Enthalpy            %s", asctime(localtime(&dateTime)));
  fprintf(includeFile, "*/\n");
  n = 1;
  for (j=1, first=1; j<=NP; j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
    if (first) { 
      first = 0; printf("h[     0]       ");                                     c  = 16; 
      dd = fprintf(includeFile, "  Hconst = ");                                  d  = dd;
    }
    printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
    fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
    if (denom != 1) {
      dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
    } else if (num != 1) {
      dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
    }
    if (j == 1) {
      dd = fprintf(includeFile, "(H(0))");                                       d += dd;
    } else {
      dd = fprintf(includeFile, "(H(%1.d))", j-1);                               d += dd;
    }
    if (c > 100) { 
      printf("\n"); 
      printf("                ");                                                c  = 16; 
    }
    if (d >  70) { 
      fprintf(includeFile, "\n"); 
      dd = fprintf(includeFile, "           ");                                  d  = dd; 
    }
  }
  if (!first) printf("\n");
  fprintf(includeFile, ";\n");

  n = 2;
  for (i=0; i<NV; i++, n++) {
    for (j=1, first=1; j<=NP; j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
      if (first) { 
        first = 0; printf("h[%6.6s]       ", param[i]);                            c  = 16; 
        if ((n-2) == 0) {
          dd = fprintf(includeFile, "  hr[ 0] = ");                                d  = dd;
        } else if (((n-2) > 0) && ((n-2) < (NV-NS))) {
          dd = fprintf(includeFile, "  hr[%2.d] = ", n-2);                         d  = dd;
        } else if (((n-2) > 0) && ((n-2) == (NV-NS))) {
          dd = fprintf(includeFile, "  hs[ 0] = ");                                d  = dd;
        } else {
          dd = fprintf(includeFile, "  hs[%2.d] = ", n-2-(NV-NS));                 d  = dd;
        }
     } 
      printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (j == 1) {
        dd = fprintf(includeFile, "(H(0))");                                       d += dd;      
      } else if (j <= (NV+1)) {
        dd = fprintf(includeFile, "(H(%1.d))", j-1);                               d += dd;
      } else if (index[j].i == 0 && index[j].j == 0) {
        dd = fprintf(includeFile, "(WH(0,0))");                                    d += dd;
      } else if (index[j].i == 0) {
        dd = fprintf(includeFile, "(WH(0,%1.d))", index[j].j);                     d += dd;
      } else if (index[j].j == 0) {
        dd = fprintf(includeFile, "(WH(%1.d,0))", index[j].i);                     d += dd;
      } else {
        dd = fprintf(includeFile, "(WH(%1.d,%1.d))", index[j].i, index[j].j);      d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "           ");                                  d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  for (i=0; i<NV; i++) for (j=i; j<NV; j++, n++) {
    for (k=1, first=1; k<=NP; k++) if (fabs(x[k][n]) > sqrt(DBL_EPSILON)) { 
      if (first) { 
        first = 0; printf("h[%6.6s,%6.6s]", param[i], param[j]);                   c  = 16; 
        if (i == 0 && j == 0) {
          dd = fprintf(includeFile, "  hrr[ 0][ 0] = ");                           d  = dd;
        } else if (i == 0) {
          if (j < (NV-NS)) {
            dd = fprintf(includeFile, "  hrr[ 0][%2.d] = ", j);                    d  = dd;
          } else if (j == (NV-NS)) {
            dd = fprintf(includeFile, "  hrs[ 0][ 0] = ");                         d  = dd;
          } else {
            dd = fprintf(includeFile, "  hrs[ 0][%2.d] = ", j-(NV-NS));            d  = dd;
          }
        } else if (i < (NV-NS)) {
          if (j < (NV-NS)) {
            dd = fprintf(includeFile, "  hrr[%2.d][%2.d] = ", i, j);               d  = dd;
          } else if (j == (NV-NS)) {
            dd = fprintf(includeFile, "  hrs[%2.d][ 0] = ", i);                    d  = dd;
          } else {
            dd = fprintf(includeFile, "  hrs[%2.d][%2.d] = ", i, j-(NV-NS));       d  = dd;
          }
        } else if (i == (NV-NS)) {
          if (j == (NV-NS)) {
            dd = fprintf(includeFile, "  hss[ 0][ 0] = ");                         d  = dd;
          } else {
            dd = fprintf(includeFile, "  hss[ 0][%2.d] = ", j-(NV-NS));            d  = dd;
          } 
        } else {
          dd = fprintf(includeFile, "  hss[%2.d][%2.d] = ", i-(NV-NS), j-(NV-NS)); d  = dd;
        }
      } 
      printf(" %s %s", fracString(x[k][n], &prefix, &num, &denom), names[k]); 
      c += 10 + strlen(names[k]);
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (k == 1) {
        fprintf(includeFile, "(H(0))");                                            d +=  2;
      } else if (k <= (NV+1)) {
        dd = fprintf(includeFile, "(H(%1.d))", k-1);                               d += dd;
      } else if (index[k].i == 0 && index[k].j == 0) {
        dd = fprintf(includeFile, "(WH(0,0))");                                    d += dd; 
      } else if (index[k].i == 0) {
        dd = fprintf(includeFile, "(WH(0,%1.d))", index[k].j);                     d += dd;
      } else if (index[k].j == 0) {
        dd = fprintf(includeFile, "(WH(%1.d,0))", index[k].i);                     d += dd;
      } else { 
        dd = fprintf(includeFile, "(WH(%1.d,%1.d))", index[k].i, index[k].j);      d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "                ");                             d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  fprintf(includeFile, "/*\n");
  fprintf(includeFile, "  Entropy             %s", asctime(localtime(&dateTime)));
  fprintf(includeFile, "*/\n");
  n = 1;
  for (j=1, first=1; j<=NP; j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
    if (first) { 
      first = 0; printf("s[     0]       ");                                     c  = 16; 
      dd = fprintf(includeFile, "  Sconst = ");                                  d  = dd;
    }
    printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
    fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
    if (denom != 1) {
      dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
    } else if (num != 1) {
      dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
    }
    if (j == 1) {
      dd = fprintf(includeFile, "(S(0))");                                       d += dd;
    } else {
      dd = fprintf(includeFile, "(S(%1.d))", j-1);                               d += dd;
    }
    if (c > 100) { 
      printf("\n"); 
      printf("                ");                                                c  = 16; 
    }
    if (d >  70) { 
      fprintf(includeFile, "\n"); 
      dd = fprintf(includeFile, "           ");                                  d  = dd; 
    }
  }
  if (!first) printf("\n");
  fprintf(includeFile, ";\n");

  n = 2;
  for (i=0; i<NV; i++, n++) {
    for (j=1, first=1; j<=NP; j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
      if (first) { 
        first = 0; printf("s[%6.6s]       ", param[i]);                            c  = 16; 
        if ((n-2) == 0) {
          dd = fprintf(includeFile, "  sr[ 0] = ");                                d  = dd;
        } else if (((n-2) > 0) && ((n-2) < (NV-NS))) {
          dd = fprintf(includeFile, "  sr[%2.d] = ", n-2);                         d  = dd;
        } else if (((n-2) > 0) && ((n-2) == (NV-NS))) {
          dd = fprintf(includeFile, "  ss[ 0] = ");                                d  = dd;
        } else {
          dd = fprintf(includeFile, "  ss[%2.d] = ", n-2-(NV-NS));                 d  = dd;
        }
     } 
      printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (j == 1) {
        dd = fprintf(includeFile, "(S(0))");                                       d += dd;      
      } else if (j <= (NV+1)) {
        dd = fprintf(includeFile, "(S(%1.d))", j-1);                               d += dd;
      } else if (index[j].i == 0 && index[j].j == 0) {
        dd = fprintf(includeFile, "(WS(0,0))");                                    d += dd;
      } else if (index[j].i == 0) {
        dd = fprintf(includeFile, "(WS(0,%1.d))", index[j].j);                     d += dd;
      } else if (index[j].j == 0) {
        dd = fprintf(includeFile, "(WS(%1.d,0))", index[j].i);                     d += dd;
      } else {
        dd = fprintf(includeFile, "(WS(%1.d,%1.d))", index[j].i, index[j].j);      d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "           ");                                  d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  for (i=0; i<NV; i++) for (j=i; j<NV; j++, n++) {
    for (k=1, first=1; k<=NP; k++) if (fabs(x[k][n]) > sqrt(DBL_EPSILON)) { 
      if (first) { 
        first = 0; printf("s[%6.6s,%6.6s]", param[i], param[j]);                   c  = 16; 
        if (i == 0 && j == 0) {
          dd = fprintf(includeFile, "  srr[ 0][ 0] = ");                           d  = dd;
        } else if (i == 0) {
          if (j < (NV-NS)) {
            dd = fprintf(includeFile, "  srr[ 0][%2.d] = ", j);                    d  = dd;
          } else if (j == (NV-NS)) {
            dd = fprintf(includeFile, "  srs[ 0][ 0] = ");                         d  = dd;
          } else {
            dd = fprintf(includeFile, "  srs[ 0][%2.d] = ", j-(NV-NS));            d  = dd;
          }
        } else if (i < (NV-NS)) {
          if (j < (NV-NS)) {
            dd = fprintf(includeFile, "  srr[%2.d][%2.d] = ", i, j);               d  = dd;
          } else if (j == (NV-NS)) {
            dd = fprintf(includeFile, "  srs[%2.d][ 0] = ", i);                    d  = dd;
          } else {
            dd = fprintf(includeFile, "  srs[%2.d][%2.d] = ", i, j-(NV-NS));       d  = dd;
          }
        } else if (i == (NV-NS)) {
          if (j == (NV-NS)) {
            dd = fprintf(includeFile, "  sss[ 0][ 0] = ");                         d  = dd;
          } else {
            dd = fprintf(includeFile, "  sss[ 0][%2.d] = ", j-(NV-NS));            d  = dd;
          } 
        } else {
          dd = fprintf(includeFile, "  sss[%2.d][%2.d] = ", i-(NV-NS), j-(NV-NS)); d  = dd;
        }
      } 
      printf(" %s %s", fracString(x[k][n], &prefix, &num, &denom), names[k]); 
      c += 10 + strlen(names[k]);
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (k == 1) {
        fprintf(includeFile, "(S(0))");                                            d +=  2;
      } else if (k <= (NV+1)) {
        dd = fprintf(includeFile, "(S(%1.d))", k-1);                               d += dd;
      } else if (index[k].i == 0 && index[k].j == 0) {
        dd = fprintf(includeFile, "(WS(0,0))");                                    d += dd; 
      } else if (index[k].i == 0) {
        dd = fprintf(includeFile, "(WS(0,%1.d))", index[k].j);                     d += dd;
      } else if (index[k].j == 0) {
        dd = fprintf(includeFile, "(WS(%1.d,0))", index[k].i);                     d += dd;
      } else { 
        dd = fprintf(includeFile, "(WS(%1.d,%1.d))", index[k].i, index[k].j);      d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "                ");                             d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  fprintf(includeFile, "/*\n");
  fprintf(includeFile, "  Volume              %s", asctime(localtime(&dateTime)));
  fprintf(includeFile, "*/\n");
  n = 1;
  for (j=1, first=1; j<=NP; j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
    if (first) { 
      first = 0; printf("v[     0]       ");                                     c  = 16; 
      dd = fprintf(includeFile, "  Vconst = ");                                  d  = dd;
    }
    printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
    fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
    if (denom != 1) {
      dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
    } else if (num != 1) {
      dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
    }
    if (j == 1) {
      dd = fprintf(includeFile, "(V(0))");                                       d += dd;
    } else {
      dd = fprintf(includeFile, "(V(%1.d))", j-1);                               d += dd;
    }
    if (c > 100) { 
      printf("\n"); 
      printf("                ");                                                c  = 16; 
    }
    if (d >  70) { 
      fprintf(includeFile, "\n"); 
      dd = fprintf(includeFile, "           ");                                  d  = dd; 
    }
  }
  if (!first) printf("\n");
  fprintf(includeFile, ";\n");

  n = 2;
  for (i=0; i<NV; i++, n++) {
    for (j=1, first=1; j<=NP; j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
      if (first) { 
        first = 0; printf("v[%6.6s]       ", param[i]);                            c  = 16; 
        if ((n-2) == 0) {
          dd = fprintf(includeFile, "  vr[ 0] = ");                                d  = dd;
        } else if (((n-2) > 0) && ((n-2) < (NV-NS))) {
          dd = fprintf(includeFile, "  vr[%2.d] = ", n-2);                         d  = dd;
        } else if (((n-2) > 0) && ((n-2) == (NV-NS))) {
          dd = fprintf(includeFile, "  vs[ 0] = ");                                d  = dd;
        } else {
          dd = fprintf(includeFile, "  vs[%2.d] = ", n-2-(NV-NS));                 d  = dd;
        }
     } 
      printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (j == 1) {
        dd = fprintf(includeFile, "(V(0))");                                       d += dd;      
      } else if (j <= (NV+1)) {
        dd = fprintf(includeFile, "(V(%1.d))", j-1);                               d += dd;
      } else if (index[j].i == 0 && index[j].j == 0) {
        dd = fprintf(includeFile, "(WV(0,0))");                                    d += dd;
      } else if (index[j].i == 0) {
        dd = fprintf(includeFile, "(WV(0,%1.d))", index[j].j);                     d += dd;
      } else if (index[j].j == 0) {
        dd = fprintf(includeFile, "(WV(%1.d,0))", index[j].i);                     d += dd;
      } else {
        dd = fprintf(includeFile, "(WV(%1.d,%1.d))", index[j].i, index[j].j);      d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "           ");                                  d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  for (i=0; i<NV; i++) for (j=i; j<NV; j++, n++) {
    for (k=1, first=1; k<=NP; k++) if (fabs(x[k][n]) > sqrt(DBL_EPSILON)) { 
      if (first) { 
        first = 0; printf("v[%6.6s,%6.6s]", param[i], param[j]);                   c  = 16; 
        if (i == 0 && j == 0) {
          dd = fprintf(includeFile, "  vrr[ 0][ 0] = ");                           d  = dd;
        } else if (i == 0) {
          if (j < (NV-NS)) {
            dd = fprintf(includeFile, "  vrr[ 0][%2.d] = ", j);                    d  = dd;
          } else if (j == (NV-NS)) {
            dd = fprintf(includeFile, "  vrs[ 0][ 0] = ");                         d  = dd;
          } else {
            dd = fprintf(includeFile, "  vrs[ 0][%2.d] = ", j-(NV-NS));            d  = dd;
          }
        } else if (i < (NV-NS)) {
          if (j < (NV-NS)) {
            dd = fprintf(includeFile, "  vrr[%2.d][%2.d] = ", i, j);               d  = dd;
          } else if (j == (NV-NS)) {
            dd = fprintf(includeFile, "  vrs[%2.d][ 0] = ", i);                    d  = dd;
          } else {
            dd = fprintf(includeFile, "  vrs[%2.d][%2.d] = ", i, j-(NV-NS));       d  = dd;
          }
        } else if (i == (NV-NS)) {
          if (j == (NV-NS)) {
            dd = fprintf(includeFile, "  vss[ 0][ 0] = ");                         d  = dd;
          } else {
            dd = fprintf(includeFile, "  vss[ 0][%2.d] = ", j-(NV-NS));            d  = dd;
          } 
        } else {
          dd = fprintf(includeFile, "  vss[%2.d][%2.d] = ", i-(NV-NS), j-(NV-NS)); d  = dd;
        }
      } 
      printf(" %s %s", fracString(x[k][n], &prefix, &num, &denom), names[k]); 
      c += 10 + strlen(names[k]);
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (k == 1) {
        fprintf(includeFile, "(V(0))");                                            d +=  2;
      } else if (k <= (NV+1)) {
        dd = fprintf(includeFile, "(V(%1.d))", k-1);                               d += dd;
      } else if (index[k].i == 0 && index[k].j == 0) {
        dd = fprintf(includeFile, "(WV(0,0))");                                    d += dd; 
      } else if (index[k].i == 0) {
        dd = fprintf(includeFile, "(WV(0,%1.d))", index[k].j);                     d += dd;
      } else if (index[k].j == 0) {
        dd = fprintf(includeFile, "(WV(%1.d,0))", index[k].i);                     d += dd;
      } else { 
        dd = fprintf(includeFile, "(WV(%1.d,%1.d))", index[k].i, index[k].j);      d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "                ");                             d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  fprintf(includeFile, "/*\n");
  fprintf(includeFile, "  Heat Capacity       %s", asctime(localtime(&dateTime)));
  fprintf(includeFile, "*/\n");
  n = 1;
  for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
    if (first) { 
      first = 0; printf("cp[     0]      ");                                     c  = 16; 
      dd = fprintf(includeFile, "  CPconst = ");                                 d  = dd;
    }
    printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
    fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
    if (denom != 1) {
      dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
    } else if (num != 1) {
      dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
    }
    if (j == 1) {
      dd = fprintf(includeFile, "(CP(0))");                                      d += dd;
    } else {
      dd = fprintf(includeFile, "(CP(%1.d))", j-1);                              d += dd;
    }
    if (c > 100) { 
      printf("\n"); 
      printf("                ");                                                c  = 16; 
    }
    if (d >  70) { 
      fprintf(includeFile, "\n"); 
      dd = fprintf(includeFile, "            ");                                 d  = dd; 
    }
  }
  if (!first) printf("\n");
  fprintf(includeFile, ";\n");

  n = 2;
  for (i=0; i<NV; i++, n++) {
    for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
      if (first) { 
        first = 0; printf("cp[%6.6s]      ", param[i]);                            c  = 16; 
        if ((n-2) == 0) {
          dd = fprintf(includeFile, "  cpr[ 0] = ");                               d  = dd;
        } else if (((n-2) > 0) && ((n-2) < (NV-NS))) {
          dd = fprintf(includeFile, "  cpr[%2.d] = ", n-2);                        d  = dd;
        } else if (((n-2) > 0) && ((n-2) == (NV-NS))) {
          dd = fprintf(includeFile, "  cps[ 0] = ");                               d  = dd;
        } else {
          dd = fprintf(includeFile, "  cps[%2.d] = ", n-2-(NV-NS));                d  = dd;
        }
     } 
      printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (j == 1) {
        dd = fprintf(includeFile, "(CP(0))");                                      d += dd;      
      } else {
        dd = fprintf(includeFile, "(CP(%1.d))", j-1);                              d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "            ");                                 d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  fprintf(includeFile, "/*\n");
  fprintf(includeFile, "  d(Heat Capacity)/dT %s", asctime(localtime(&dateTime)));
  fprintf(includeFile, "*/\n");
  n = 1;
  for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
    if (first) { 
      first = 0; printf("dcpdt[     0]   ");                                     c  = 16; 
      dd = fprintf(includeFile, "  DCPDTconst = ");                              d  = dd;
    }
    printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
    fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
    if (denom != 1) {
      dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
    } else if (num != 1) {
      dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
    }
    if (j == 1) {
      dd = fprintf(includeFile, "(DCPDT(0))");                                   d += dd;
    } else {
      dd = fprintf(includeFile, "(DCPDT(%1.d))", j-1);                           d += dd;
    }
    if (c > 100) { 
      printf("\n"); 
      printf("                ");                                                c  = 16; 
    }
    if (d >  70) { 
      fprintf(includeFile, "\n"); 
      dd = fprintf(includeFile, "               ");                              d  = dd; 
    }
  }
  if (!first) printf("\n");
  fprintf(includeFile, ";\n");

  n = 2;
  for (i=0; i<NV; i++, n++) {
    for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
      if (first) { 
        first = 0; printf("dcpdt[%6.6s]   ", param[i]);                            c  = 16; 
        if ((n-2) == 0) {
          dd = fprintf(includeFile, "  dcpdtr[ 0] = ");                            d  = dd;
        } else if (((n-2) > 0) && ((n-2) < (NV-NS))) {
          dd = fprintf(includeFile, "  dcpdtr[%2.d] = ", n-2);                     d  = dd;
        } else if (((n-2) > 0) && ((n-2) == (NV-NS))) {
          dd = fprintf(includeFile, "  dcpdts[ 0] = ");                            d  = dd;
        } else {
          dd = fprintf(includeFile, "  dcpdts[%2.d] = ", n-2-(NV-NS));             d  = dd;
        }
     } 
      printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (j == 1) {
        dd = fprintf(includeFile, "(DCPDT(0))");                                   d += dd;      
      } else {
        dd = fprintf(includeFile, "(DCPDT(%1.d))", j-1);                           d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "               ");                              d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  fprintf(includeFile, "/*\n");
  fprintf(includeFile, "  d(Volume)/dT        %s", asctime(localtime(&dateTime)));
  fprintf(includeFile, "*/\n");
  n = 1;
  for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
    if (first) { 
      first = 0; printf("dvdt[     0]    ");                                     c  = 16; 
      dd = fprintf(includeFile, "  DVDTconst = ");                               d  = dd;
    }
    printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
    fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
    if (denom != 1) {
      dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
    } else if (num != 1) {
      dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
    }
    if (j == 1) {
      dd = fprintf(includeFile, "(DVDT(0))");                                    d += dd;
    } else {
      dd = fprintf(includeFile, "(DVDT(%1.d))", j-1);                            d += dd;
    }
    if (c > 100) { 
      printf("\n"); 
      printf("                ");                                                c  = 16; 
    }
    if (d >  70) { 
      fprintf(includeFile, "\n"); 
      dd = fprintf(includeFile, "              ");                               d  = dd; 
    }
  }
  if (!first) printf("\n");
  fprintf(includeFile, ";\n");

  n = 2;
  for (i=0; i<NV; i++, n++) {
    for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
      if (first) { 
        first = 0; printf("dvdt[%6.6s]    ", param[i]);                            c  = 16; 
        if ((n-2) == 0) {
          dd = fprintf(includeFile, "  dvdtr[ 0] = ");                             d  = dd;
        } else if (((n-2) > 0) && ((n-2) < (NV-NS))) {
          dd = fprintf(includeFile, "  dvdtr[%2.d] = ", n-2);                      d  = dd;
        } else if (((n-2) > 0) && ((n-2) == (NV-NS))) {
          dd = fprintf(includeFile, "  dvdts[ 0] = ");                             d  = dd;
        } else {
          dd = fprintf(includeFile, "  dvdts[%2.d] = ", n-2-(NV-NS));              d  = dd;
        }
     } 
      printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (j == 1) {
        dd = fprintf(includeFile, "(DVDT(0))");                                    d += dd;      
      } else {
        dd = fprintf(includeFile, "(DVDT(%1.d))", j-1);                            d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "              ");                               d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  fprintf(includeFile, "/*\n");
  fprintf(includeFile, "  d(Volume)/dP        %s", asctime(localtime(&dateTime)));
  fprintf(includeFile, "*/\n");
  n = 1;
  for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
    if (first) { 
      first = 0; printf("dvdp[     0]    ");                                     c  = 16; 
      dd = fprintf(includeFile, "  DVDPconst = ");                               d  = dd;
    }
    printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
    fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
    if (denom != 1) {
      dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
    } else if (num != 1) {
      dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
    }
    if (j == 1) {
      dd = fprintf(includeFile, "(DVDP(0))");                                    d += dd;
    } else {
      dd = fprintf(includeFile, "(DVDP(%1.d))", j-1);                            d += dd;
    }
    if (c > 100) { 
      printf("\n"); 
      printf("                ");                                                c  = 16; 
    }
    if (d >  70) { 
      fprintf(includeFile, "\n"); 
      dd = fprintf(includeFile, "              ");                               d  = dd; 
    }
  }
  if (!first) printf("\n");
  fprintf(includeFile, ";\n");

  n = 2;
  for (i=0; i<NV; i++, n++) {
    for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
      if (first) { 
        first = 0; printf("dvdp[%6.6s]    ", param[i]);                            c  = 16; 
        if ((n-2) == 0) {
          dd = fprintf(includeFile, "  dvdpr[ 0] = ");                             d  = dd;
        } else if (((n-2) > 0) && ((n-2) < (NV-NS))) {
          dd = fprintf(includeFile, "  dvdpr[%2.d] = ", n-2);                      d  = dd;
        } else if (((n-2) > 0) && ((n-2) == (NV-NS))) {
          dd = fprintf(includeFile, "  dvdps[ 0] = ");                             d  = dd;
        } else {
          dd = fprintf(includeFile, "  dvdps[%2.d] = ", n-2-(NV-NS));              d  = dd;
        }
     } 
      printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (j == 1) {
        dd = fprintf(includeFile, "(DVDP(0))");                                    d += dd;      
      } else {
        dd = fprintf(includeFile, "(DVDP(%1.d))", j-1);                            d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "              ");                               d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  fprintf(includeFile, "/*\n");
  fprintf(includeFile, "  d2(Volume)/dT2      %s", asctime(localtime(&dateTime)));
  fprintf(includeFile, "*/\n");
  n = 1;
  for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
    if (first) { 
      first = 0; printf("d2vdt2[     0]  ");                                     c  = 16; 
      dd = fprintf(includeFile, "  D2VDT2const   = ");                           d  = dd;
    }
    printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
    fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
    if (denom != 1) {
      dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
    } else if (num != 1) {
      dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
    }
    if (j == 1) {
      dd = fprintf(includeFile, "(D2VDT2(0))");                                  d += dd;
    } else {
      dd = fprintf(includeFile, "(D2VDT2(%1.d))", j-1);                          d += dd;
    }
    if (c > 100) { 
      printf("\n"); 
      printf("                ");                                                c  = 16; 
    }
    if (d >  70) { 
      fprintf(includeFile, "\n"); 
      dd = fprintf(includeFile, "                ");                             d  = dd; 
    }
  }
  if (!first) printf("\n");
  fprintf(includeFile, ";\n");

  n = 2;
  for (i=0; i<NV; i++, n++) {
    for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
      if (first) { 
        first = 0; printf("d2vdt2[%6.6s]  ", param[i]);                            c  = 16; 
        if ((n-2) == 0) {
          dd = fprintf(includeFile, "  d2vdt2r[ 0] = ");                           d  = dd;
        } else if (((n-2) > 0) && ((n-2) < (NV-NS))) {
          dd = fprintf(includeFile, "  d2vdt2r[%2.d] = ", n-2);                    d  = dd;
        } else if (((n-2) > 0) && ((n-2) == (NV-NS))) {
          dd = fprintf(includeFile, "  d2vdt2s[ 0] = ");                           d  = dd;
        } else {
          dd = fprintf(includeFile, "  d2vdt2s[%2.d] = ", n-2-(NV-NS));            d  = dd;
        }
     } 
      printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (j == 1) {
        dd = fprintf(includeFile, "(D2VDT2(0))");                                  d += dd;      
      } else {
        dd = fprintf(includeFile, "(D2VDT2(%1.d))", j-1);                          d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "                ");                             d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  fprintf(includeFile, "/*\n");
  fprintf(includeFile, "  d2(Volume)/dP2      %s", asctime(localtime(&dateTime)));
  fprintf(includeFile, "*/\n");
  n = 1;
  for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
    if (first) { 
      first = 0; printf("d2vdp2[     0]  ");                                     c  = 16; 
      dd = fprintf(includeFile, "  D2VDP2const   = ");                           d  = dd;
    }
    printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
    fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
    if (denom != 1) {
      dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
    } else if (num != 1) {
      dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
    }
    if (j == 1) {
      dd = fprintf(includeFile, "(D2VDP2(0))");                                  d += dd;
    } else {
      dd = fprintf(includeFile, "(D2VDP2(%1.d))", j-1);                          d += dd;
    }
    if (c > 100) { 
      printf("\n"); 
      printf("                ");                                                c  = 16; 
    }
    if (d >  70) { 
      fprintf(includeFile, "\n"); 
      dd = fprintf(includeFile, "                ");                             d  = dd; 
    }
  }
  if (!first) printf("\n");
  fprintf(includeFile, ";\n");

  n = 2;
  for (i=0; i<NV; i++, n++) {
    for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
      if (first) { 
        first = 0; printf("d2vdp2[%6.6s]  ", param[i]);                            c  = 16; 
        if ((n-2) == 0) {
          dd = fprintf(includeFile, "  d2vdp2r[ 0] = ");                           d  = dd;
        } else if (((n-2) > 0) && ((n-2) < (NV-NS))) {
          dd = fprintf(includeFile, "  d2vdp2r[%2.d] = ", n-2);                    d  = dd;
        } else if (((n-2) > 0) && ((n-2) == (NV-NS))) {
          dd = fprintf(includeFile, "  d2vdp2s[ 0] = ");                           d  = dd;
        } else {
          dd = fprintf(includeFile, "  d2vdp2s[%2.d] = ", n-2-(NV-NS));            d  = dd;
        }
     } 
      printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (j == 1) {
        dd = fprintf(includeFile, "(D2VDP2(0))");                                  d += dd;      
      } else {
        dd = fprintf(includeFile, "(D2VDP2(%1.d))", j-1);                          d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "                ");                             d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  fprintf(includeFile, "/*\n");
  fprintf(includeFile, "  d2(Volume)/dTdP     %s", asctime(localtime(&dateTime)));
  fprintf(includeFile, "*/\n");
  n = 1;
  for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
    if (first) { 
      first = 0; printf("d2vdtdp[     0] ");                                     c  = 16; 
      dd = fprintf(includeFile, "  D2VDTDPconst   = ");                          d  = dd;
    }
    printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
    fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
    if (denom != 1) {
      dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
    } else if (num != 1) {
      dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
    }
    if (j == 1) {
      dd = fprintf(includeFile, "(D2VDTDP(0))");                                 d += dd;
    } else {
      dd = fprintf(includeFile, "(D2VDTDP(%1.d))", j-1);                         d += dd;
    }
    if (c > 100) { 
      printf("\n"); 
      printf("                ");                                                c  = 16; 
    }
    if (d >  70) { 
      fprintf(includeFile, "\n"); 
      dd = fprintf(includeFile, "                 ");                            d  = dd; 
    }
  }
  if (!first) printf("\n");
  fprintf(includeFile, ";\n");

  n = 2;
  for (i=0; i<NV; i++, n++) {
    for (j=1, first=1; j<=(NV+1); j++) if (fabs(x[j][n]) > sqrt(DBL_EPSILON)) {
      if (first) { 
        first = 0; printf("d2vdtdp[%6.6s] ", param[i]);                            c  = 16; 
        if ((n-2) == 0) {
          dd = fprintf(includeFile, "  d2vdtdpr[ 0] = ");                          d  = dd;
        } else if (((n-2) > 0) && ((n-2) < (NV-NS))) {
          dd = fprintf(includeFile, "  d2vdtdpr[%2.d] = ", n-2);                   d  = dd;
        } else if (((n-2) > 0) && ((n-2) == (NV-NS))) {
          dd = fprintf(includeFile, "  d2vdtdps[ 0] = ");                          d  = dd;
        } else {
          dd = fprintf(includeFile, "  d2vdtdps[%2.d] = ", n-2-(NV-NS));           d  = dd;
        }
     } 
      printf(" %s %22.22s", fracString(x[j][n], &prefix, &num, &denom), names[j]); c += 32;
      fprintf(includeFile, "%s", (prefix > 0) ? "+" : "-");                        d +=  1;
      if (denom != 1) {
        dd = fprintf(includeFile, "(%d.0/%d.0)*", num, denom);                     d += dd;
      } else if (num != 1) {
        dd = fprintf(includeFile, "%d.0*", num);                                   d += dd;
      }
      if (j == 1) {
        dd = fprintf(includeFile, "(D2VDTDP(0))");                                 d += dd;      
      } else {
        dd = fprintf(includeFile, "(D2VDTDP(%1.d))", j-1);                         d += dd;
      }
      if (c > 100) { 
        printf("\n"); 
        printf("                ");                                                c  = 16; 
      }
      if (d >  70) { 
        fprintf(includeFile, "\n"); 
        dd = fprintf(includeFile, "                 ");                            d  = dd; 
      }
    }
    if (!first) printf("\n");
    fprintf(includeFile, ";\n");
  }

  fprintf(includeFile, "\n");
  /* end */  

  fclose(includeFile);

  exit(0);
}
