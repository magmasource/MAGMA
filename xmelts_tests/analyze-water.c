const char *analyze_water_ver(void) { return "$Id: analyze-water.c,v 1.3 2009/04/16 16:35:22 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: analyze-water.c,v $
MELTS Source Code: RCS Revision 1.2  2006/08/17 16:47:18  ghiorso
MELTS Source Code: RCS Made modifications to protect strings.  These modifications allow removal
MELTS Source Code: RCS of the flag -fwritable-strings during gcc compilation.  This brings the
MELTS Source Code: RCS code up to gcc 4.x standards.
MELTS Source Code: RCS
MELTS Source Code: RCS Other minor rearrangements and cleanup.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:35  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2005/01/24 03:38:04  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added new files and modifications to perform builds for MgO-SiO2 system
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Routine to read anhydrous solid-liquid database and perform various 
**      tests to evaluate quality of data (file: ANALYZE-WATER.C).
**--
*/

#include "silmin.h"

#ifdef BUILD_MGO_SIO2_VERSION
#include "liq_struct_data_MgO_SiO2.h"
#include "sol_struct_data_MgO_SiO2.h"
#include "param_struct_data_MgO_SiO2.h"
#else
#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"
#endif /* BUILD_MGO_SIO2_VERSION */ 

int calculationMode = MODE_DEFAULT;

void *main_window, *silmin_adb, *topLevel, *meltsEnviron;
SilminState *silminState;

#include <unistd.h>
#include <grace_np.h>

typedef struct {
  double t;      /* C    */
  double p;      /* bars */
  double wtSiO2, wtAl2O3, wtFeO, wtCaO, wtNa2O, wtK2O;
  double wtH2Ot;      /* total water in wt % */
  double wtH2O, wtOH; /* experimental proportions of H2O and OH */
} IZSdatabase;

static IZSdatabase iZSdatabase[] = {
    /* T(C), P(bars), SiO2  Al2O3  FeO  CaO  Na2O  K2O, H2O t, H2O m,    OH */
    { 600.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.781, 0.157, 0.624 }, /* Mono Craters */
    { 600.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.876, 0.187, 0.690 }, /* Mono Craters */
    { 600.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.073, 0.265, 0.809 }, /* Mono Craters */
    { 600.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.071, 0.264, 0.808 }, /* Mono Craters */
    { 600.0,  1002.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.325, 0.365, 0.961 }, /* Mono Craters */
    { 600.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.447, 0.418, 1.029 }, /* Mono Craters */
    { 600.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.474, 0.436, 1.038 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.444, 0.070, 0.374 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.437, 0.069, 0.368 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.809, 0.191, 0.618 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.767, 0.175, 0.592 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.796, 0.185, 0.611 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.763, 0.172, 0.591 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.807, 0.187, 0.620 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.832, 0.196, 0.636 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.856, 0.201, 0.655 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.318, 0.410, 0.908 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.309, 0.405, 0.904 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.345, 0.421, 0.924 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.321, 0.410, 0.912 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.329, 0.413, 0.916 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.459, 0.486, 0.973 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.470, 0.487, 0.983 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.463, 0.488, 0.975 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 2.363, 0.977, 1.386 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 2.327, 0.968, 1.359 }, /* Mono Craters */
    { 550.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 2.326, 0.962, 1.364 }, /* Mono Craters */
    { 540.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.828, 0.198, 0.630 }, /* Mono Craters */
    { 540.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.828, 0.199, 0.628 }, /* Mono Craters */
    { 540.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.851, 0.206, 0.644 }, /* Mono Craters */
    { 540.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.826, 0.198, 0.629 }, /* Mono Craters */
    { 530.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.838, 0.208, 0.630 }, /* Mono Craters */
    { 530.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.841, 0.209, 0.632 }, /* Mono Craters */
    { 530.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.836, 0.212, 0.624 }, /* Mono Craters */
    { 530.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.149, 0.348, 0.802 }, /* Mono Craters */
    { 530.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.154, 0.349, 0.805 }, /* Mono Craters */
    { 530.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.133, 0.344, 0.789 }, /* Mono Craters */
    { 530.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.155, 0.356, 0.799 }, /* Mono Craters */
    { 530.0,   744.0, 76.6,  12.7, 2.2, 0.3,  4.1, 4.6, 3.777, 2.024, 1.753 }, /* LPR1         */
    { 530.0,   744.0, 76.6,  12.7, 2.2, 0.3,  4.1, 4.6, 4.435, 2.589, 1.846 }, /* LPR2         */
    { 530.0,   744.0, 76.6,  12.7, 2.2, 0.3,  4.1, 4.6, 4.068, 2.272, 1.796 }, /* LPR3         */
    { 530.0,   744.0, 76.6,  12.7, 2.2, 0.3,  4.1, 4.6, 4.064, 2.267, 1.797 }, /* LPR3         */
    { 500.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.926, 0.268, 0.659 }, /* Mono Craters */
    { 500.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.001, 0.303, 0.698 }, /* Mono Craters */
    { 500.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.055, 0.331, 0.724 }, /* Mono Craters */
    { 500.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.351, 0.474, 0.877 }, /* Mono Craters */
    { 500.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.328, 0.462, 0.866 }, /* Mono Craters */
    { 500.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.327, 0.461, 0.866 }, /* Mono Craters */
    { 500.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.341, 0.470, 0.871 }, /* Mono Craters */
    { 500.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.307, 0.451, 0.856 }, /* Mono Craters */
    { 500.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.336, 0.468, 0.868 }, /* Mono Craters */
    { 500.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.323, 0.459, 0.864 }, /* Mono Craters */
    { 500.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.307, 0.454, 0.853 }, /* Mono Craters */
    { 500.0,   944.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.358, 0.478, 0.881 }, /* Mono Craters */
    { 500.0,   944.0, 77.6,  12.9, 0.4, 0.5,  4.2, 4.2, 2.674, 1.253, 1.421 }, /* GB           */
    { 500.0,   944.0, 76.6,  12.7, 2.2, 0.3,  4.1, 4.6, 3.661, 1.997, 1.664 }, /* LPR1         */
    { 500.0,   944.0, 76.6,  12.7, 2.2, 0.3,  4.1, 4.6, 4.490, 2.720, 1.769 }, /* LPR2         */
    { 500.0,   944.0, 76.6,  12.7, 2.2, 0.3,  4.1, 4.6, 3.959, 2.222, 1.737 }, /* LPR3         */
    { 490.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.813, 0.223, 0.590 }, /* Mono Craters */
    { 490.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.079, 0.349, 0.730 }, /* Mono Craters */
    { 490.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.096, 0.361, 0.735 }, /* Mono Craters */
    { 490.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.320, 0.478, 0.843 }, /* Mono Craters */
    { 490.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.317, 0.482, 0.835 }, /* Mono Craters */
    { 490.0,   250.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 3.036, 1.598, 1.439 }, /* Mono Craters */
    { 490.0,   250.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 2.984, 1.545, 1.438 }, /* Mono Craters */
    { 490.0,   250.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 3.049, 1.613, 1.436 }, /* Mono Craters */
    { 490.0,   250.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 2.288, 1.051, 1.236 }, /* Mono Craters */
    { 490.0,   250.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.847, 0.786, 1.061 }, /* Mono Craters */
    { 475.0,  1009.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.362, 0.518, 0.844 }, /* Mono Craters */
    { 475.0,  1009.0, 77.6,  12.9, 0.4, 0.5,  4.2, 4.2, 2.613, 1.288, 1.325 }, /* GB           */
    { 450.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.748, 0.229, 0.519 }, /* Mono Craters */
    { 450.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.801, 0.259, 0.542 }, /* Mono Craters */
    { 450.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 0.833, 0.275, 0.558 }, /* Mono Craters */
    { 450.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.111, 0.416, 0.695 }, /* Mono Craters */
    { 450.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.205, 0.469, 0.736 }, /* Mono Craters */
    { 450.0,   551.0, 76.6,  12.7, 2.2, 0.3,  4.1, 4.6, 4.684, 3.110, 1.574 }, /* LPR2         */
    { 403.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.336, 0.597, 0.739 }, /* Mono Craters */
    { 403.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.333, 0.598, 0.735 }, /* Mono Craters */
    { 403.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 1.737, 0.858, 0.879 }, /* Mono Craters */
    { 403.0,     1.0, 76.4,  12.3, 1.0, 0.5,  3.8, 4.8, 2.231, 1.207, 1.024 }  /* Mono Craters */
};

static int nIZS = (sizeof iZSdatabase / sizeof(IZSdatabase));

void *main_window, *silmin_adb, *topLevel, *meltsEnviron;

#define REC 134
#define PAGE 66
#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))

#define GETNEWLINE \
  if (fgets(line, REC, input) == NULL) { \
    n++; \
    printf("Error during read at line %d, offending record:\n", n); \
    printf("%s", line); \
    exit(0); \
  } else { \
    n++; \
    if (n % 100 == 0) printf("Processing line %d ...\n", n); \
  }

#define PARSELINE1 \
  if ((len = strlen(line)) < 81) {for (i=len-1; i<81; i++) line[i] = ' ';} \
  for (i=0; i<8; i++) { \
    strncpy(entry, &line[i*10], 10); \
    wt[i] = atof(entry); \
  }

#define PARSELINE2 \
  if ((len = strlen(line)) < 81) {for (i=len-1; i<81; i++) line[i] = ' ';} \
  for (i=0; i<8; i++) { \
    strncpy(entry, &line[i*10], 10); \
    wt[i+8] = atof(entry); \
  }

static void grace_error_function(const char *msg)
{
  fprintf(stderr, "library message : \"%s\"\n", msg);
}

int main(int argc, char **argv)
{   
   const char *database = "database-water.dat";
   FILE *input;

   char entry[] = { "          \0" };
   char line[REC];
   double t, p, logfo2, wt[24], molesLiqCmp[24], sum, *xSpecies, *rLiq;
   int i, j, k, n, len, nl = 0, nH2OB = -1, nH2O = -1, nSiOH = -1;

   printf("Initializing solids[] structure and allocating memory.\n");

   InitComputeDataStruct();
   xSpecies = (double *) malloc((size_t)     nls*sizeof(double));
   rLiq     = (double *) malloc((size_t) (nlc-1)*sizeof(double));

   if (argc > 1) {
     printf("Attempting to open input file %s for analysis.\n", argv[1]);
     if ((input = fopen (argv[1], "r")) == NULL) {
        printf("...Failure to open file. Exit.\n");
        exit(0);
     }
   } else {
     printf("Attempting to open input file %s for analysis.\n", database);
     if ((input = fopen (database, "r")) == NULL) {
        printf("...Failure to open file. Exit.\n");
        exit(0);
     }
   }
   
   for (i=0;   i<nc;  i++) if (strcmp(bulkSystem[i].label, "H2O") == 0) { nH2OB = i; break; }
   for (i=0;   i<nlc; i++) if (strcmp(liquid[i].label, "H2O")     == 0) { nH2O  = i; break; }
   for (i=nlc; i<nls; i++) if (strcmp(liquid[i].label, "Si0.25OH") == 0) { nSiOH = i; break; }
   if ( (nH2OB == -1) || (nH2O == -1) || (nSiOH == -1) ) {
     printf("...failure to find index for H2O and Si(OH)4.\n");
     exit(0);
   }

  GraceRegisterErrorFunction (grace_error_function);
  if(GraceOpen (2048) < 0) { printf("Cannot open pipe to Grace.\n"); exit(0); }

   GracePrintf("WITH G0\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n",   0.1,  0.1,   0.45, 0.45);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 400.0, -2.0, 600.0,  2.0);

    GracePrintf("XAXIS TICK MAJOR 50.0\n");
    GracePrintf("XAXIS TICK MINOR 10.0\n");
    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"T (C)\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS TICK MAJOR 1.0\n");
    GracePrintf("YAXIS TICK MINOR 0.2\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("YAXIS LABEL \"Wt% H2O\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
   
   GracePrintf("WITH G1\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n",   0.55,  0.1,   0.90, 0.45);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 400.0,  -2.0, 600.0,  2.0);

    GracePrintf("XAXIS TICK MAJOR 50.0\n");
    GracePrintf("XAXIS TICK MINOR 10.0\n");
    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"T (C)\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS TICK MAJOR 1.0\n");
    GracePrintf("YAXIS TICK MINOR 0.2\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("YAXIS LABEL \"Wt% OH\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
   
   GracePrintf("WITH G2\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.55, 0.45, 0.95);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0,  5.0,  4.0);

    GracePrintf("XAXIS TICK MAJOR 1.0\n");
    GracePrintf("XAXIS TICK MINOR 0.2\n");
    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"Wt H2O Bulk\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS TICK MAJOR 1.0\n");
    GracePrintf("YAXIS TICK MINOR 0.2\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("YAXIS LABEL \"Wt% H2O\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
   
   GracePrintf("WITH G3\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.55, 0.55, 0.90, 0.95);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0,  0.0,  5.0,  2.5);

    GracePrintf("XAXIS TICK MAJOR 1.0\n");
    GracePrintf("XAXIS TICK MINOR 0.2\n");
    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"Wt H2O Bulk\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS TICK MAJOR 0.5\n");
    GracePrintf("YAXIS TICK MINOR 0.1\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("YAXIS LABEL \"Wt% OH\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
   
   
   /* Compute test curves for a rhyolite at 1000 bars and 850 C */ 
   for (i=0; i<24; i++) wt[i] = 0.0;
   p      = 1000.0;
   for (k=0; k<nIZS; k++) {
     double sum;
     int color;
     t = iZSdatabase[k].t + 273.15;
     logfo2 = -24441.9/t +  8.290;
     wt[ 0] = iZSdatabase[k].wtSiO2;
     wt[ 2] = iZSdatabase[k].wtAl2O3;
     wt[ 5] = iZSdatabase[k].wtFeO;
     wt[10] = iZSdatabase[k].wtCaO;
     wt[11] = iZSdatabase[k].wtNa2O;
     wt[12] = iZSdatabase[k].wtK2O;
     wt[14] = iZSdatabase[k].wtH2Ot;
     sum = wt[0] + wt[2] + wt[5] + wt[10] + wt[11] + wt[12];
     wt[ 0] *= (100.0 - wt[14])/sum;
     wt[ 2] *= (100.0 - wt[14])/sum;
     wt[ 5] *= (100.0 - wt[14])/sum;
     wt[10] *= (100.0 - wt[14])/sum;
     wt[11] *= (100.0 - wt[14])/sum;
     wt[12] *= (100.0 - wt[14])/sum;
     
     if      (iZSdatabase[k].t == 600.0) color =  2;
     else if (iZSdatabase[k].t == 550.0) color =  3;
     else if (iZSdatabase[k].t == 540.0) color =  4;
     else if (iZSdatabase[k].t == 530.0) color =  5;
     else if (iZSdatabase[k].t == 500.0) color =  6;
     else if (iZSdatabase[k].t == 490.0) color =  7;
     else if (iZSdatabase[k].t == 475.0) color =  8;
     else if (iZSdatabase[k].t == 450.0) color =  9;
     else if (iZSdatabase[k].t == 403.0) color = 10;
     else color = 1;
 
     for (i=0; i<nc; i++) wt[i] /= bulkSystem[i].mw;
     conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL,  NULL, NULL, &logfo2);
     for (i=0, sum=0.0; i<nlc; i++) {
       for (j=0, molesLiqCmp[i]=0.0; j<nc; j++) molesLiqCmp[i] += wt[j]*(bulkSystem[j].oxToLiq)[i];
       sum += molesLiqCmp[i];
     }
     for (i=0; i<nc; i++) wt[i] *= bulkSystem[i].mw;
     if (sum != 0.0) for (i=0; i<nlc; i++) molesLiqCmp[i] /= sum;

     if (!testLiq(SIXTH, t, p, 0, 0, NULL, NULL, NULL, molesLiqCmp)) printf("-->Liquid %d has negative mole numbers.\n", nl);
     conLiq(SECOND, THIRD,	     t, p, NULL, molesLiqCmp, rLiq, NULL,     NULL, NULL, NULL);
     conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL,        rLiq, xSpecies, NULL, NULL, NULL);
     if (testLiq(SEVENTH,0, 0, 0, 0, NULL, NULL, NULL, NULL)) {
       double wtH2O = (iZSdatabase[k].wtH2Ot != 0.0) ? iZSdatabase[k].wtH2Ot*xSpecies[nH2O] /(xSpecies[nH2O]+xSpecies[nSiOH]) : 0.0;
       double wtOH  = (iZSdatabase[k].wtH2Ot != 0.0) ? iZSdatabase[k].wtH2Ot*xSpecies[nSiOH]/(xSpecies[nH2O]+xSpecies[nSiOH]) : 0.0;
       
       GracePrintf("g2.s0 LINESTYLE 0\n");
       GracePrintf("g2.s0 SYMBOL 2\n");
       GracePrintf("g2.s0 SYMBOL FILL 1\n");
       GracePrintf("g2.s0 SYMBOL SIZE 0.5\n");
       GracePrintf("g2.s0 SYMBOL COLOR 1\n"); 
       GracePrintf("g2.s0 POINT %lf, %lf\n", iZSdatabase[k].wtH2Ot, wtH2O);

       GracePrintf("g3.s0 LINESTYLE 0\n");
       GracePrintf("g3.s0 SYMBOL 2\n");
       GracePrintf("g3.s0 SYMBOL FILL 1\n");
       GracePrintf("g3.s0 SYMBOL SIZE 0.5\n");
       GracePrintf("g3.s0 SYMBOL COLOR 1\n"); 
       GracePrintf("g3.s0 POINT %lf, %lf\n", iZSdatabase[k].wtH2Ot, wtOH);

       GracePrintf("g0.s%2.2d LINESTYLE 0\n", color);
       GracePrintf("g0.s%2.2d SYMBOL 2\n", color);
       GracePrintf("g0.s%2.2d SYMBOL FILL 1\n", color);
       GracePrintf("g0.s%2.2d SYMBOL SIZE 0.5\n", color);
       GracePrintf("g0.s%2.2d SYMBOL COLOR %d\n", color, color); 
       GracePrintf("g0.s%2.2d POINT %lf, %lf\n", color, iZSdatabase[k].t, wtH2O-iZSdatabase[k].wtH2O);

       GracePrintf("g1.s%2.2d LINESTYLE 0\n", color);
       GracePrintf("g1.s%2.2d SYMBOL 2\n", color);
       GracePrintf("g1.s%2.2d SYMBOL FILL 1\n", color);
       GracePrintf("g1.s%2.2d SYMBOL SIZE 0.5\n", color);
       GracePrintf("g1.s%2.2d SYMBOL COLOR %d\n", color, color); 
       GracePrintf("g1.s%2.2d POINT %lf, %lf\n", color, iZSdatabase[k].t, wtOH-iZSdatabase[k].wtOH);

       GracePrintf("g2.s%2.2d LINESTYLE 0\n", color);
       GracePrintf("g2.s%2.2d SYMBOL 2\n", color);
       GracePrintf("g2.s%2.2d SYMBOL FILL 1\n", color);
       GracePrintf("g2.s%2.2d SYMBOL SIZE 0.5\n", color);
       GracePrintf("g2.s%2.2d SYMBOL COLOR %d\n", color, color); 
       GracePrintf("g2.s%2.2d POINT %lf, %lf\n", color, iZSdatabase[k].wtH2Ot, iZSdatabase[k].wtH2O);

       GracePrintf("g3.s%2.2d LINESTYLE 0\n", color);
       GracePrintf("g3.s%2.2d SYMBOL 2\n", color);
       GracePrintf("g3.s%2.2d SYMBOL FILL 1\n", color);
       GracePrintf("g3.s%2.2d SYMBOL SIZE 0.5\n", color);
       GracePrintf("g3.s%2.2d SYMBOL COLOR %d\n", color, color); 
       GracePrintf("g3.s%2.2d POINT %lf, %lf\n", color, iZSdatabase[k].wtH2Ot, iZSdatabase[k].wtOH);

       GracePrintf("REDRAW\n");
     }
   }
     
   /***************************************************************************
    Question to proceed
    ***************************************************************************/
   printf("Perform speciation analysis of database (y or n)? ");
   if (tolower(getchar()) == 'y') getchar(); else { getchar(); exit(0); }
   
   GracePrintf("FLUSH\n");

   GracePrintf("WITH G0\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.1, 0.90, 0.95);
    GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 0.0, 0.0, 16.0, 10.0);

    GracePrintf("XAXIS TICK MAJOR 2.0\n");
    GracePrintf("XAXIS TICK MINOR 1.0\n");
    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("XAXIS LABEL \"Wt H2O Bulk\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 2\n");

    GracePrintf("YAXIS TICK MAJOR 2.0\n");
    GracePrintf("YAXIS TICK MINOR 1.0\n");
    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    GracePrintf("YAXIS LABEL \"Wt% H2O, OH\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 2\n");
   
   for (n=1; fgets(line, REC, input) != NULL; n++) {
     len = strlen(line); for (i=0; i<len; i++) line[i] = tolower(line[i]);
     if (n % 100 == 0) printf("Processing line %d ...\n", n);

     /* Liquid entry: Title / t, p log fo2 / 8 wt % / 8 wt %                  */
     if (line[0] != '$') {
       double wtH2OB;
 
       nl++; 

       for (i=(len-1); i<70; i++) line[i] = ' '; line[70] = '\0';

       GETNEWLINE
       if (sscanf(line, "%lf %lf %lf", &t, &p, &logfo2) == EOF) {
         printf("Illegal numeric value at line %d, offending record:\n", n);
         printf("%s", line);
         exit(0);
       }

       GETNEWLINE
       PARSELINE1

       GETNEWLINE
       PARSELINE2

       for (i=16; i<24; i++) wt[i] = 0.0;
       wtH2OB = wt[nH2OB];
      
       for (i=0; i<nc; i++) wt[i] /= bulkSystem[i].mw;
       conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL,  NULL, NULL, &logfo2);
       for (i=0, sum=0.0; i<nlc; i++) {
         for (j=0, molesLiqCmp[i]=0.0; j<nc; j++) molesLiqCmp[i] += wt[j]*(bulkSystem[j].oxToLiq)[i];
         sum += molesLiqCmp[i];
       }
       for (i=0; i<nc; i++) wt[i] *= bulkSystem[i].mw;
       if (sum != 0.0) for (i=0; i<nlc; i++) molesLiqCmp[i] /= sum;

       if (!testLiq(SIXTH, t, p, 0, 0, NULL, NULL, NULL, molesLiqCmp)) printf("-->Liquid %d has negative mole numbers.\n", nl);
       conLiq(SECOND, THIRD,           t, p, NULL, molesLiqCmp, rLiq, NULL,     NULL, NULL, NULL);
       conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL,        rLiq, xSpecies, NULL, NULL, NULL);
       if (testLiq(SEVENTH,0, 0, 0, 0, NULL, NULL, NULL, NULL)) {
         double wtH2O = (wtH2OB != 0.0) ? wtH2OB*xSpecies[nH2O] /(xSpecies[nH2O]+xSpecies[nSiOH]) : 0.0;
         double wtOH  = (wtH2OB != 0.0) ? wtH2OB*xSpecies[nSiOH]/(xSpecies[nH2O]+xSpecies[nSiOH]) : 0.0;
	 
	 GracePrintf("g0.s0 LINESTYLE 0\n");
	 GracePrintf("g0.s0 SYMBOL 2\n");
	 GracePrintf("g0.s0 SYMBOL FILL 1\n");
	 GracePrintf("g0.s0 SYMBOL SIZE 0.5\n");
	 GracePrintf("g0.s0 SYMBOL COLOR 1\n"); 
         GracePrintf("g0.s0 POINT %lf, %lf\n", wtH2OB, wtH2O);
	 
	 GracePrintf("g0.s1 LINESTYLE 0\n");
	 GracePrintf("g0.s1 SYMBOL 2\n");
	 GracePrintf("g0.s1 SYMBOL FILL 1\n");
	 GracePrintf("g0.s1 SYMBOL SIZE 0.5\n");
	 GracePrintf("g0.s1 SYMBOL COLOR 2\n"); 
         GracePrintf("g0.s1 POINT %lf, %lf\n", wtH2OB, wtOH);
	 
         GracePrintf("REDRAW\n");
       } else printf("-->Liquid %d did not converge in ordering routine.\n", nl);

     /* Solid entry: $NAME extra information / 8 wt % / 8 wt %                */
     } else {

       line[len-1] = ' ';
       for (i=(len-1); line[i] == ' ' && i > 0; i--) line[i] = '\0';

       GETNEWLINE
       PARSELINE1

       GETNEWLINE
       PARSELINE2
     }
   }

   printf("END-OF-FILE detected on file %s at line %d\n", database, n);
   (void) fclose(input);
   free(xSpecies);
   free(rLiq);
   exit(0);   
}

/* End file: TEST_DATABASE.C */

