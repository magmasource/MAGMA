const char *test_database_ver(void) { return "$Id: test_database.c,v 1.18 2009/04/16 16:35:24 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: test_database.c,v $
MELTS Source Code: RCS Revision 1.11  2007/10/18 00:01:42  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.10  2007/10/03 21:33:49  ghiorso
MELTS Source Code: RCS Updated liquid eos thermodynamics.
MELTS Source Code: RCS Added regression of ferric/ferrous parameters from data file.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.9  2007/08/30 18:26:10  ghiorso
MELTS Source Code: RCS Revised high-pressure log fO2 calculations (buffers and liquid)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.8  2007/06/08 17:25:43  ghiorso
MELTS Source Code: RCS Added code to allow regression of Ghiorso EOS parameters
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.7  2007/05/30 15:39:03  ghiorso
MELTS Source Code: RCS Corrected problem with links to dynamic libraries in Melts-batch
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.6  2007/05/07 18:23:21  ghiorso
MELTS Source Code: RCS Modifications to LEPR and calibration algorithms following visit by
MELTS Source Code: RCS Marc and Tim.  Mostly work on cpx and opx inclusion and reclassification.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2007/03/13 17:14:24  ghiorso
MELTS Source Code: RCS Adjustments for high-P fO2 estimates.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2007/03/07 21:21:58  ghiorso
MELTS Source Code: RCS Revised majorite model and the way garnets are treated during calibration.
MELTS Source Code: RCS Revised calibration XML file to include LEPER + older MELTS/pMELTS data.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2007/02/28 01:49:18  ghiorso
MELTS Source Code: RCS Modified EOS parameters for K2O and changed Ca3(PO4)2 component to P2O5.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2006/08/17 16:47:19  ghiorso
MELTS Source Code: RCS Made modifications to protect strings.  These modifications allow removal
MELTS Source Code: RCS of the flag -fwritable-strings during gcc compilation.  This brings the
MELTS Source Code: RCS code up to gcc 4.x standards.
MELTS Source Code: RCS
MELTS Source Code: RCS Other minor rearrangements and cleanup.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:36  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2005/01/24 03:38:05  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added new files and modifications to perform builds for MgO-SiO2 system
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2003/09/27 15:35:22  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
 * Revision 3.7  1997/06/21  22:49:22  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.6  1997/05/03  20:23:02  ghiorso
 * *** empty log message ***
 *
 * Revision 3.5  1997/03/27  17:03:06  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1996/09/24  20:33:17  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.3  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.2  1995/11/01  22:40:27  ghiorso
 * Implementation of subsolidus options after Asimow.
 * Additional implementation of nepheline solid solutions.
 *
 * Revision 3.2  1995/11/01  22:40:27  ghiorso
 * Implementation of subsolidus options after Asimow.
 * Additional implementation of nepheline solid solutions.
 *
 * Revision 3.1  1995/08/18  19:17:13  ghiorso
 * MELTS Version 3 - Initial Entry
 *
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Routine to read anhydrous solid-liquid database and perform various 
**      tests to evaluate quality of data (file: TEST_DATABASE.C).
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  June 14, 1991 Original Version
**      V1.0-2  Mark S. Ghiorso  September 13, 1991
**              Altered parameters in call to conLiq
**                               September 14, 1991
**              Altered call to (*solids[].convert) and associated local
**              structure to reflect change in parameter list
**      V1.0-3  Mark S. Ghiorso  September 24, 1991
**              Altered parameter list to (*solids[].convert) and made
**              appropriate modifications to the associated local structure
**      V1.0-4  Mark S. Ghiorso  November 12, 1991
**              Corrected error in counting number of active phases (np)
**      V1.0-5  Mark S. Ghiorso  February 1, 1992
**              Corrected error in definition of phases->ptFile
**      V1.0-6  Mark S. Ghiorso  July 24, 1992
**              Corrected memory leak in initializing output variable
**      V1.0-7  Mark S. Ghiorso  September 29, 1993
**              Modified call to realloc to catch zero pointer (SPARC port)
**--
*/

static void intenToExtenGradient(double pMix, double *dpMix, int nr,  double *dp, 
  int na, double mTotal, double **drdm)
{
  int i, j;
  
  for (j=0; j<na; j++) {
    for (i=0, dp[j] = 0.0; i<nr; i++) dp[j] += dpMix[i]*drdm[i][j];
    dp[j] = mTotal*dp[j] + pMix;
  }
}

typedef struct _eosRefParameters {
  double v, dvdt, cRef, dcdt, cp, d2vdp2, d3vdp3, d4vdp4, mw;
  double alpha, v0, v1, v2, v3, v4, a, b;
  double K, Kp, Kpp, Kppp;    
} EosRefParameters;

EosRefParameters *getEosRefParameters(double *r);

#include "silmin.h"

#ifdef BUILD_MGO_SIO2_VERSION
#include "liq_struct_data_MgO_SiO2.h"
#include "sol_struct_data_MgO_SiO2.h"
#include "param_struct_data_MgO_SiO2.h"

#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
#include "liq_struct_data_SiO2_Al2O3_CaO_Na2O_K2O.h"
#include "sol_struct_data_SiO2_Al2O3_CaO_Na2O_K2O.h"
#include "param_struct_data_SiO2_Al2O3_CaO_Na2O_K2O.h"

#else
#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"
#endif


SilminState *silminState;
int calculationMode = MODE_DEFAULT;
void *main_window, *silmin_adb, *topLevel, *meltsEnviron;
int isPigeonite(double t, double p, double *r);
int isOrthopyroxene(double t, double p, double *r);

#define REC 134
#define PAGE 1000000
#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))

#include <libxml/encoding.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>
#include <libxml/xmlwriter.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#ifndef __MSDOS__
#define DIR_DELIM "/"
#else
#define DIR_DELIM "\"
#endif

int main(int argc, char **argv)
{
  typedef struct _phases {
    char *name;    /* phase name					*/
    int  len;	   /* length of above string				*/
    int  n;	   /* number of this phase in database  		*/
    int  na;	   /* number of endmember components for this phase	*/
    int  index;    /* index of this phase in solids array		*/
    FILE *ptFile;  /* pointer to output file for data on this phase	*/
    double *moles; /* moles[na], array of moles of endmember components */
    double *r;     /* r[nr], array of independent comp variables	*/
    void (*convert) (int inpMask, int outMask, double t, double p, 
  		     double *e, double *m, double *r, double *x,
  		     double **dm, double ***d2m, double **dr,
  		     double ****paul);
    void (*display) (int inpMask, double t, double p, double *r,
  		     char **formula);
    int (*test) (int mask, double t, double p, int na, int nr, char **names,
  		 char **formulas, double *r, double *m);
    void (*vmix) (int mask, double t, double p, double *x,
  		  double *vmix, double *dx, double **dx2, double *dt,	
  		  double *dp, double *dt2, double *dtdp, double *dp2,  
  		  double *dxdt, double *dxdp);
  } Phases;
  Phases **phases;
  
  const char *database     = "SiO2-Al2O3-K2O+.xml";
  const char *liquidsOne   = "liquid-titles.out";    FILE *titleLiquids;
  const char *liquidsTwo   = "liquid-data.out";      FILE *dataLiquids;
  const char *liquidsThree = "liquid-comp.out";      FILE *compLiquids;
  const char *liquidsFour  = "liquid-species.out";   FILE *speciesLiquids;
  const char *liquidsFive  = "liquid-solid-rho.out"; FILE *rhoLiqSolids;
  const char *liquidsSix   = "liquid-eos.out";       FILE *eosLiquids;

  char *output = NULL;
  double t, p, logfo2, wt[24], mOx[24], molesLiqCmp[24], elements[107], sum, *xSpecies, *rLiq, **drdmLiq, *dvdx, *dvdm, mOxTot;
  int i, j, id;
  char **oxNamesLC = NULL;

  int nl = 0;
  int np = 0;

  xmlSchemaPtr schema = NULL;
  xmlSchemaParserCtxtPtr ctxt = NULL;
  xmlSchemaValidCtxtPtr ctxt2 = NULL;
  xmlDocPtr doc = NULL;
  xmlNode *root_element = NULL;
  xmlNode *level1;

  printf("Initializing solids[] structure and allocating memory.\n");

  InitComputeDataStruct();

  xSpecies = (double *)  malloc((size_t)     nls*sizeof(double));
  rLiq     = (double *)  malloc((size_t) (nlc-1)*sizeof(double));
  dvdx     = (double *)  malloc((size_t) (nlc-1)*sizeof(double));
  dvdm     = (double *)  malloc((size_t)     nlc*sizeof(double));
  drdmLiq  = (double **) malloc((size_t) (nlc-1)*sizeof(double *));
  for (i=0; i<(nlc-1); i++) drdmLiq[i] = (double *) malloc((size_t) nlc*sizeof(double));

  phases = (Phases **) malloc((size_t) sizeof(Phases *));
  for (i=0; i<npc; i++) {
    if (solids[i].type == PHASE) {
      phases = (Phases **) REALLOC(phases, (size_t) (np+1)*sizeof(Phases *));
      phases[np] = (Phases *) malloc((size_t) sizeof(Phases));
      (phases[np])->len = strlen(solids[i].label);
      (phases[np])->name = (char *) malloc((size_t) ((phases[np])->len+1)*sizeof(char)); 
      strcpy((phases[np])->name, solids[i].label);

      (phases[np])->n = 0;
      (phases[np])->na = solids[i].na;
      (phases[np])->index = i;
      (phases[np])->ptFile = NULL;
      (phases[np])->convert = solids[i].convert;
      (phases[np])->display = solids[i].display;
      (phases[np])->test    = solids[i].test;
      (phases[np])->vmix    = solids[i].vmix;
      (phases[np])->moles = (double *) malloc((size_t) ((phases[np])->na)*sizeof(double));
      (phases[np])->r = (double *) malloc((size_t) (solids[i].nr)*sizeof(double));
      np++; 
    }
  }
  if (oxNamesLC == NULL) oxNamesLC = (char **) malloc((size_t) nc*sizeof(char *));
  for (i=0; i<nc; i++) {
    int len = strlen(bulkSystem[i].label);
    oxNamesLC[i] = (char *) malloc((size_t) (len+1)*sizeof(char));
    for (j=0; j<len; j++) oxNamesLC[i][j] = tolower((bulkSystem[i].label)[j]);
    oxNamesLC[i][len] = '\0';
  }

  ctxt = xmlSchemaNewParserCtxt("LEPRdatabase.xsd");
  xmlSchemaSetParserErrors(ctxt,(xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr); 
  schema = xmlSchemaParse(ctxt);

  if (schema != NULL) {
    xmlSchemaFreeParserCtxt(ctxt);
    ctxt2 = xmlSchemaNewValidCtxt(schema);
    xmlSchemaSetValidErrors(ctxt2,(xmlSchemaValidityErrorFunc) fprintf,(xmlSchemaValidityWarningFunc) fprintf, stderr);
    if (argc > 1) {
      printf("Attempting to open input file %s for analysis.\n", argv[1]);
      doc = xmlReadFile(argv[1], NULL, 0);
    } else {
      printf("Attempting to open input file %s for analysis.\n", database);
      doc = xmlReadFile(database, NULL, 0);
    }
    if (doc) {
      if (xmlSchemaValidateDoc(ctxt2, doc)) {
  	printf("XML database file is invalid against schema LEPRdatabase.xsd.\n");
  	xmlFreeDoc(doc); doc = NULL; exit(0);
      } else {
  	root_element = xmlDocGetRootElement(doc);
  	level1 = root_element->children;
  	printf("XML database file has been validated against schema LEPRdatabase.xsd.");
      }
      
    } else { printf("XML database file cannot be opened.\n"); exit(0); }
  
  } else { printf("No schema file found! (LEPRdatabase.xsd does not exist).\n"); exit(0); }

  printf("Attempting to open output file %s for analysis.\n", liquidsOne);
  if ((titleLiquids = fopen (liquidsOne, "w")) == NULL) {
     printf("...Failure to open file. Exit.\n");
     exit(0);
  }

  printf("Attempting to open output file %s for analysis.\n", liquidsTwo);
  if ((dataLiquids = fopen (liquidsTwo, "w")) == NULL) {
     printf("...Failure to open file. Exit.\n");
     exit(0);
  }

  printf("Attempting to open output file %s for analysis.\n", liquidsThree);
  if ((compLiquids = fopen (liquidsThree, "w")) == NULL) {
     printf("...Failure to open file. Exit.\n");
     exit(0);
  }

  printf("Attempting to open output file %s for analysis.\n", liquidsFour);
  if ((speciesLiquids = fopen (liquidsFour, "w")) == NULL) {
     printf("...Failure to open file. Exit.\n");
     exit(0);
  }

  printf("Attempting to open output file %s for analysis.\n", liquidsFive);
  if ((rhoLiqSolids = fopen (liquidsFive, "w")) == NULL) {
     printf("...Failure to open file. Exit.\n");
     exit(0);
  }

  printf("Attempting to open output file %s for analysis.\n", liquidsSix);
  if ((eosLiquids = fopen (liquidsSix, "w")) == NULL) {
     printf("...Failure to open file. Exit.\n");
     exit(0);
  }

  fprintf(titleLiquids,   "%s\t%s\t%s\t%s\t%s\t%s\t%s", "No", "LEPRnum", "name", "author", "device", "container", "method");
  fprintf(dataLiquids,    "%s\t%s\t%s\t%s\t%s\t%s\t%s", "No", "LEPRnum", "name", "author", "device", "container", "method");
  fprintf(compLiquids,    "%s\t%s\t%s\t%s\t%s\t%s\t%s", "No", "LEPRnum", "name", "author", "device", "container", "method");
  fprintf(speciesLiquids, "%s\t%s\t%s\t%s\t%s\t%s\t%s", "No", "LEPRnum", "name", "author", "device", "container", "method");
  fprintf(rhoLiqSolids,   "%s\t%s\t%s\t%s\t%s\t%s\t%s", "No", "LEPRnum", "name", "author", "device", "container", "method");
  fprintf(eosLiquids,     "%s\t%s\t%s\t%s\t%s\t%s\t%s", "No", "LEPRnum", "name", "author", "device", "container", "method");

  fprintf(titleLiquids,   "\t%s\t%s\t%s", "T (C)", "P (GPa)", "log10 fO2");
  fprintf(dataLiquids,    "\t%s\t%s\t%s", "T (C)", "P (GPa)", "log10 fO2");
  fprintf(compLiquids,    "\t%s\t%s\t%s", "T (C)", "P (GPa)", "log10 fO2");
  fprintf(speciesLiquids, "\t%s\t%s\t%s", "T (C)", "P (GPa)", "log10 fO2");
  fprintf(rhoLiqSolids,   "\t%s\t%s\t%s", "T (C)", "P (GPa)", "log10 fO2");
  fprintf(eosLiquids,     "\t%s\t%s\t%s", "T (C)", "P (GPa)", "log10 fO2");

  for (i=0; i<nc; i++) fprintf(dataLiquids, "\t%s", bulkSystem[i].label);
  fprintf(dataLiquids, "\t%s", "sum");
  for (i=0; i<nlc; i++) fprintf(compLiquids, "\t%s", liquid[i].label);
  fprintf(eosLiquids, "\t%s\t%s\t%s", "V", "K (GPa)", "K'");
  fprintf(eosLiquids, "\t%s", "ref v (cc)");	    
  fprintf(eosLiquids, "\t%s", "ref dvdt (cc/K)");   
  fprintf(eosLiquids, "\t%s", "ref cRef (m/sec)");    
  fprintf(eosLiquids, "\t%s", "ref dcdt (m/sec-K)");  
  fprintf(eosLiquids, "\t%s", "ref cp (J/K)");      
  fprintf(eosLiquids, "\t%s", "ref d2vdp2 (cc/GPa^2)"); 
  fprintf(eosLiquids, "\t%s", "ref d3vdp3 (cc/GPa^3)"); 
  fprintf(eosLiquids, "\t%s", "ref d4vdp4 (cc/GPa^4)"); 
  fprintf(eosLiquids, "\t%s", "ref mw (gm)");	    
  fprintf(eosLiquids, "\t%s", "ref alpha (1/K)");      
  fprintf(eosLiquids, "\t%s", "ref v0 (cc)");	    
  fprintf(eosLiquids, "\t%s", "ref v1 (cc/GPa)");   
  fprintf(eosLiquids, "\t%s", "ref v2 (cc/GPa^2)"); 
  fprintf(eosLiquids, "\t%s", "ref v3 (cc/GPa^3)"); 
  fprintf(eosLiquids, "\t%s", "ref v4 (cc/GPa^4)"); 
  fprintf(eosLiquids, "\t%s", "ref a (1/GPa)");    
  fprintf(eosLiquids, "\t%s", "ref b (1/GPa^2)");  
  fprintf(eosLiquids, "\t%s", "ref K (GPa)");      
  fprintf(eosLiquids, "\t%s", "ref K'");		    
  fprintf(eosLiquids, "\t%s", "ref K'' (1/GPa)");    
  fprintf(eosLiquids, "\t%s", "ref K''' (1/GPa^2)");  
  for (i=0; i<nlc; i++) fprintf(eosLiquids, "\t%s", liquid[i].label);

  fprintf(titleLiquids,   "\tstatus\tpCritA (GPa)\tpCritB (GPa)");
  fprintf(dataLiquids,    "\tstatus\tpCritA (GPa)\tpCritB (GPa)");
  fprintf(compLiquids,    "\tstatus\tpCritA (GPa)\tpCritB (GPa)");
  fprintf(speciesLiquids, "\tstatus\tpCritA (GPa)\tpCritB (GPa)");
  fprintf(rhoLiqSolids,   "\trho liq\tpCritA (GPa)\tpCritB (GPa)");

  for (i=0; i<nls; i++) fprintf(speciesLiquids, "\t%s", liquid[i].label);
  for (i=0; i<nc; i++)  fprintf(speciesLiquids, "\twt %s", bulkSystem[i].label);

  fprintf(dataLiquids,    "\n");
  fprintf(compLiquids,    "\n");
  fprintf(speciesLiquids, "\n");

  fprintf(titleLiquids,   "\t%s", "phase");
  fprintf(rhoLiqSolids,   "\t%s\t%s", "phase", "rho sol");

  fprintf(titleLiquids,   "\n");
  fprintf(rhoLiqSolids,   "\n");
  fprintf(eosLiquids,     "\n");
  
  while (level1 != NULL) {
    if (level1->type == XML_ELEMENT_NODE) {
      xmlChar *content1 = xmlNodeGetContent(level1);
      
      if (!strcmp((char *) level1->name, "experiment")) {
	xmlNode *level2 = level1->children;
	int flagPC   = FALSE; /* flags for device type */
	int flagMA   = FALSE;
	int flagCSPV = FALSE;
	int flagIHPV = FALSE;
	int flagC    = FALSE; /* flags for container type */
	int flagPtC  = FALSE;
	int flagFe   = FALSE;
	int flagFePt = FALSE;
	int flagRe   = FALSE;
	int LEPRnum  = 0;
	char name[21], author[21], device[11], container[11], method[11];
        double hORsCon=0.0;
	
	t = -9999.0; p = -9999.0; logfo2 = -9999.0;
	for (i=0; i<21;i++) { name[i] = ' '; author[i] = ' '; }
	name[20] = '\0'; author[20] = '\0';
	for (i=0; i<11;i++) { device[i] = ' '; container[i] = ' '; method[i] = ' '; }
	device[10] = '\0'; container[10] = '\0'; method[10] = '\0';

	while (level2 != NULL) {
	  if (level2->type == XML_ELEMENT_NODE) {
	    xmlChar *content2 = xmlNodeGetContent(level2);
	    
	    if      (!strcmp((char *) level2->name, "number" )) LEPRnum = atoi((char *) content2);
	    
	    else if (!strcmp((char *) level2->name, "name"   )) { 
	      (void) strncpy(name, (char *) content2, 20); 
	    }
	    
	    else if (!strcmp((char *) level2->name, "author"    )) (void) strncpy(author, (char *) content2, 20);
	    
	    else if (!strcmp((char *) level2->name, "device"    )) {
	      (void) strncpy(device,    (char *) content2, 10);
	      if      (!strcmp((char *) content2, "PC"  )) flagPC = TRUE;
	      else if (!strcmp((char *) content2, "MA"  )) flagMA = TRUE;
	      else if (!strcmp((char *) content2, "CSPV")) flagCSPV = TRUE;
	      else if (!strcmp((char *) content2, "IHPV")) flagIHPV = TRUE;
	    }
	      
	    else if (!strcmp((char *) level2->name, "container" )) {
	      (void) strncpy(container, (char *) content2, 10);
	      if      (!strcmp((char *) content2, "C"   )) flagC   = TRUE;
	      else if (!strcmp((char *) content2, "PtC" )) flagPtC = TRUE;
	      else if (!strcmp((char *) content2, "Fe"  )) flagFe  = TRUE;
	      else if (!strcmp((char *) content2, "FePt")) flagFePt = TRUE;
	      else if (!strcmp((char *) content2, "Re"  )) flagRe  = TRUE;
	    }
	    
	    else if (!strcmp((char *) level2->name, "method"    )) (void) strncpy(method,(char *) content2, 10);
	    
	    else if (!strcmp((char *) level2->name, "t"      )) t = atof((char *) content2) + 273.15; /* K    */
	    else if (!strcmp((char *) level2->name, "p"      )) p = atof((char *) content2)*10000.0;  /* bars */
	    else if (!strcmp((char *) level2->name, "fo2val" )) logfo2 = atof((char *) content2);	    
	    
	    else if (!strcmp((char *) level2->name, "liquid" )) { /* at this point t and p are defined */
	      double sumGrams, sumMoles;
	      xmlNode *level3 = level2->children;
	      for (i=0; i<nc; i++) wt[i] = 0.0;
	      while (level3 != NULL) {
	        if (level3->type == XML_ELEMENT_NODE) {
	          xmlChar *content3 = xmlNodeGetContent(level3);
		  for (i=0; i<nc; i++) if (!strcmp((char *) level3->name, oxNamesLC[i])) {
		    wt[i] = atof((char *) content3);
		    break;
		  }
		  if (content3 != NULL) xmlFree(content3);
		}
		level3 = level3->next;
	      }

#ifndef BUILD_MGO_SIO2_VERSION
#ifndef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
              if (p > 50000.0) logfo2 = -9999.0; /* kill previous estimate of log fo2 from LEPR for high P experiments */
	      if ((LEPRnum >= 150001) && (LEPRnum <= 150312)) logfo2 = -9999.0; /* recalculate the log fO2s for all "density" constraints */
	      
              if (logfo2 == -9999.0 && (flagPC || flagMA) && (flagC || flagPtC)) {
	        /*
		 * The maximum log fO2 is acheived at a pressure of 6.7021 GPa.
		 *   Above that p use Andy Cambell's correction for IW buffer
		 */
	        logfo2 = getlog10fo2(t, (p < 67201.0) ? p : 67201.0, FO2_COH);
		if (p > 67201.0) logfo2 += 608.966*(p/10000.0)/t - 608.966*(67201.0/10000.0)/t;
		
	      } else if (logfo2 == -9999.0 && (flagFe || flagFePt)) {
	        logfo2 = getlog10fo2(t, 1.0, FO2_IW) - 2.0 + 608.966*(p/10000.0)/t; /* Andy Campbell's pressure correction */
		
	      } else if (logfo2 == -9999.0 && flagRe) { 
	        /* logfo2  = (-451020.0 + 297.595*t - 14.6585*t*log(t))/(8.3143*t*log(10.0)); */ /* good 850-1250 K */
		/* logfo2  = getlog10fo2(t, 1.0, FO2_IW) + 1.5; */ /* Tim Grove's suggestion */
	        logfo2 = getlog10fo2(t, (p < 67201.0) ? p : 67201.0, FO2_COH); /* Assume that there are carbon heaters */
		if (p > 67201.0) logfo2 += 608.966*(p/10000.0)/t - 608.966*(67201.0/10000.0)/t; /* Andy Campbell's pressure correction for IW */
		
	      } else if (logfo2 == -9999.0 && (flagPC || flagMA)) {
	        logfo2 = getlog10fo2(t, (p < 67201.0) ? p : 67201.0, FO2_COH); /* Pure guess */
		if (p > 67201.0) logfo2 += 608.966*(p/10000.0)/t - 608.966*(67201.0/10000.0)/t; /* Andy Campbell's pressure correction for IW */
		
	      } else if (logfo2 == -9999.0 && (flagCSPV || flagIHPV)) {
	        logfo2 = getlog10fo2(t, 1.0, FO2_NNO) + 2.5 + 0.046*(p-1.0)/t;  /* Frost pressure correction */
		
	      } else if (logfo2 == -9999.0 && wt[3] == 0.0 && wt[5] == 0.0) { /* No iron in liquid */
	        logfo2 = getlog10fo2(t, 1.0, FO2_QFM);
	      }
	      {
	        double fo2air = -0.68 + ((p > 0.0) ? log(p)/log(10.0) : 0.0);
	        if (logfo2 > fo2air) logfo2 = fo2air; /* Constrain the log fO2 to be at or below air at P */
	      }
#endif
#endif
              /********************************************************************/	      
	      /* Process liquid data in order to determine if this entry is valid */
	      /********************************************************************/
              nl++; 

              fprintf(titleLiquids,   "%d\t%d\t%s\t%s\t%s\t%s\t%s", nl, LEPRnum, name, author, device, container, method);
              fprintf(dataLiquids,    "%d\t%d\t%s\t%s\t%s\t%s\t%s", nl, LEPRnum, name, author, device, container, method);
              fprintf(compLiquids,    "%d\t%d\t%s\t%s\t%s\t%s\t%s", nl, LEPRnum, name, author, device, container, method);
              fprintf(speciesLiquids, "%d\t%d\t%s\t%s\t%s\t%s\t%s", nl, LEPRnum, name, author, device, container, method);
              fprintf(rhoLiqSolids,   "%d\t%d\t%s\t%s\t%s\t%s\t%s", nl, LEPRnum, name, author, device, container, method);
              fprintf(eosLiquids,     "%d\t%d\t%s\t%s\t%s\t%s\t%s", nl, LEPRnum, name, author, device, container, method);
  
              fprintf(titleLiquids,   "\t%g\t%g\t%g", t-273.15, p/10000.0, logfo2);
              fprintf(dataLiquids,    "\t%g\t%g\t%g", t-273.15, p/10000.0, logfo2);
              fprintf(compLiquids,    "\t%g\t%g\t%g", t-273.15, p/10000.0, logfo2);
              fprintf(speciesLiquids, "\t%g\t%g\t%g", t-273.15, p/10000.0, logfo2);
              fprintf(rhoLiqSolids,   "\t%g\t%g\t%g", t-273.15, p/10000.0, logfo2);
              fprintf(eosLiquids,     "\t%g\t%g\t%g", t-273.15, p/10000.0, logfo2);

#ifdef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
              if (wt[0] == 0.0) { /* No silica in the system, experiments in Na2O-Al2O3 */
	        double corrSiO2 = 3.0;                              /* wt % */
		double pseudo = (wt[1] != 0.0) ? wt[3]/wt[1] : 0.0; /* Na2O/Al2O3: There should NEVER be zero Al2O3 */
		double corrAl2O3 = (100.0 - corrSiO2)/(1.0+pseudo);
		double corrNa2O = pseudo*corrAl2O3;
		wt[0] = corrSiO2;
		wt[1] = corrAl2O3;
		wt[3] = corrNa2O;
	      }
#endif
	      
              for (i=0; i<nc; i++) wt[i] /= bulkSystem[i].mw;
#ifndef BUILD_MGO_SIO2_VERSION
#ifndef BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
              if ((logfo2 != -9999.0) && (LEPRnum < 90000))
	        conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL, NULL, NULL, &logfo2); /* FeO(T) -> Fe2O3, FeO */
#endif
#endif
              for (i=0, sumGrams=0.0; i<nc; i++) sumGrams += wt[i]*bulkSystem[i].mw; 
              
              for (i=0, sum=0.0; i<nlc; i++) {
        	for (j=0, molesLiqCmp[i]=0.0; j<nc; j++) molesLiqCmp[i] += wt[j]*(bulkSystem[j].oxToLiq)[i];
        	sum += molesLiqCmp[i];
              }
              for (i=0, mOxTot=0.0; i<nc; i++) { mOx[i] = wt[i]; mOxTot += mOx[i]; wt[i] *= bulkSystem[i].mw; }
	      
              if (sum != 0.0) for (i=0; i<nlc; i++) molesLiqCmp[i] /= sum;
              sumMoles = sum;

              for (sum = 0.0, i=0; i<nc; i++) { sum += wt[i]; fprintf(dataLiquids, "\t%g", wt[i]); }
              fprintf(dataLiquids, "\t%g", sum);

              for (i=0; i<nlc; i++) fprintf(compLiquids, "\t%g", molesLiqCmp[i]);

              if (!testLiq(SIXTH, t, p, 0, 0, NULL, NULL, NULL, molesLiqCmp)) {
        	for (i=0; i<nls; i++) xSpecies[i] = 0.0;
        	fprintf(titleLiquids,	"\tLiquid has negative mole numbers.\t\t");
        	fprintf(dataLiquids,	"\tLiquid has negative mole numbers.\t\t");
        	fprintf(compLiquids,	"\tLiquid has negative mole numbers.\t\t");
        	fprintf(speciesLiquids, "\tLiquid has negative mole numbers.\t\t");
        	fprintf(rhoLiqSolids, "\t\t\t");
              } else {
        	double g;
        	conLiq(SECOND, THIRD | FIFTH,   t, p, NULL, molesLiqCmp, rLiq, NULL,	 drdmLiq, NULL, NULL);
        	conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL,	 rLiq, xSpecies, NULL,    NULL, NULL);
        	if (!testLiq(SEVENTH,0, 0, 0, 0, NULL, NULL, NULL, NULL)) {
        	  fprintf(titleLiquids,   "\tFails liquid speciation test.\t\t");
        	  fprintf(dataLiquids,	  "\tFails liquid speciation test.\t\t");
        	  fprintf(compLiquids,	  "\tFails liquid speciation test.\t\t");
        	  fprintf(speciesLiquids, "\tFails liquid speciation test.\t\t");
        	  fprintf(rhoLiqSolids, "\t\t\t");
		} else {
		  double v, dvdt, c, cRef, dcdt, mw, cp, d2vdp2, d3vdp3, d4vdp4, v0, v1, v1Ref, v2, alpha, a, b,
		         root, pCritA, pCritB;
	          double tr = 1673.15;
                  for (i=0, v=0.0, dvdt=0.0, cRef=0.0, dcdt=0.0, mw=0.0, cp=0.0, d2vdp2=0.0, d3vdp3=0.0, d4vdp4=0.0; i<nc; i++) {
                    v       += mOx[i]*bulkSystem[i].gk_v;
                    dvdt    += mOx[i]*bulkSystem[i].gk_dvdt;
#ifndef BUILD_MGO_SIO2_VERSION
                    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot;
#elif BUILD_SIO2_AL2O3_CAO_NA2O_K2O_VERSION
                    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + mOx[i]*mOx[1]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);
#else
                    cRef    += mOx[i]*bulkSystem[i].gk_c/mOxTot + mOx[i]*mOx[2]*bulkSystem[i].gk_cXal2o3/(mOxTot*mOxTot);
#endif
                    dcdt    += mOx[i]*bulkSystem[i].gk_dcdt/mOxTot;
     		    cp      += mOx[i]*bulkSystem[i].gk_cp;
     		    d2vdp2  += mOx[i]*bulkSystem[i].gk_d2vdp2;
     		    d3vdp3  += mOx[i]*bulkSystem[i].gk_d3vdp3;
     		    d4vdp4  += mOx[i]*bulkSystem[i].gk_d4vdp4;
     		    mw      += mOx[i]*bulkSystem[i].mw;
   		  }
 
   		  alpha   = dvdt/v;
   		  v0	  = v*exp(alpha*(t-tr));
   		  v1Ref   = -v*v*(1000.0/(mw*cRef*cRef) + tr*alpha*alpha/(cp));
   		  c	  = cRef + (t-tr)*dcdt;
   		  v1	  = -v0*v0*(1000.0/(mw*c*c) + t*alpha*alpha/(cp));
   		  v2	  = d2vdp2;
   		  a	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d3vdp3 - v1Ref*d4vdp4/2.0)	 /(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
   		  b	  = (2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2 != 0.0) ? (d2vdp2*d4vdp4/4.0 - d3vdp3*d3vdp3/3.0)/(2.0*v1Ref*d3vdp3-3.0*d2vdp2*d2vdp2) : 0.0;
		  
		  root = a*a - 4.0*b;
		  if (root >= 0.0) {
		    pCritA = (2.0*b - a + sqrt(root))/(2.0*b);
		    pCritB = (2.0*b - a - sqrt(root))/(2.0*b);
		  } else { 
		    pCritA = 0.0;
		    pCritB = 0.0;
		  }
		
		  gmixLiq(FIRST, t, p, rLiq, &g, NULL, NULL);
        	  if (!testLiq(EIGHTH, 0, 0, 0, 0, NULL, NULL, NULL, NULL)) {
        	    fprintf(titleLiquids,   "\tFails liquid EOS test.");
        	    fprintf(dataLiquids,    "\tFails liquid EOS test.");
        	    fprintf(compLiquids,    "\tFails liquid EOS test.");
        	    fprintf(speciesLiquids, "\tFails liquid EOS test.");
        	    fprintf(rhoLiqSolids, "\t");
        	  } else {
        	    double v;
		    double K  = (v1 != 0.0) ? -v0/v1          : 0.0;
		    double Kp = (v0 != 0.0) ? v2*K*K/v0 - 1.0 : 0.0;
		    EosRefParameters *eos = getEosRefParameters(rLiq);
        	    setModeToMixingLiq(FALSE);
        	    vmixLiq(FIRST | SECOND, t, p, rLiq, &v, dvdx, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
        	    setModeToMixingLiq(TRUE);
		    intenToExtenGradient(v, dvdx, nlc-1,  dvdm, nlc, sumMoles, drdmLiq);
        	    fprintf(titleLiquids,   "\t");
        	    fprintf(dataLiquids,    "\t");
        	    fprintf(compLiquids,    "\t");
        	    fprintf(speciesLiquids, "\t");
        	    fprintf(rhoLiqSolids,   "\t%g", ((v*sumMoles) != 0.0) ? sumGrams/(10.0*v*sumMoles) : 0.0);
		    fprintf(eosLiquids,     "\t%g", v*sumMoles*10.0);
		    fprintf(eosLiquids,     "\t%g", K/10000.0);
		    fprintf(eosLiquids,     "\t%g", Kp);
    		    fprintf(eosLiquids,     "\t%g", eos->v     *10.0*sumMoles);
    		    fprintf(eosLiquids,     "\t%g", eos->dvdt  *10.0*sumMoles);
    		    fprintf(eosLiquids,     "\t%g", eos->cRef  );
    		    fprintf(eosLiquids,     "\t%g", eos->dcdt  );
    		    fprintf(eosLiquids,     "\t%g", eos->cp    *sumMoles);
    		    fprintf(eosLiquids,     "\t%g", eos->d2vdp2*10.0*10000.0*10000.0*sumMoles);
    		    fprintf(eosLiquids,     "\t%g", eos->d3vdp3*10.0*10000.0*10000.0*10000.0*sumMoles);
    		    fprintf(eosLiquids,     "\t%g", eos->d4vdp4*10.0*10000.0*10000.0*10000.0*10000.0*sumMoles);
    		    fprintf(eosLiquids,     "\t%g", eos->mw    *sumMoles);
    		    fprintf(eosLiquids,     "\t%g", eos->alpha );
    		    fprintf(eosLiquids,     "\t%g", eos->v0    *10.0*sumMoles);
    		    fprintf(eosLiquids,     "\t%g", eos->v1    *10.0*10000.0*sumMoles);
    		    fprintf(eosLiquids,     "\t%g", eos->v2    *10.0*10000.0*10000.0*sumMoles);
    		    fprintf(eosLiquids,     "\t%g", eos->v3    *10.0*10000.0*10000.0*10000.0*sumMoles);
    		    fprintf(eosLiquids,     "\t%g", eos->v4    *10.0*10000.0*10000.0*10000.0*10000.0*sumMoles);
    		    fprintf(eosLiquids,     "\t%g", eos->a     *10000.0);
    		    fprintf(eosLiquids,     "\t%g", eos->b     *10000.0*10000.0);
    		    fprintf(eosLiquids,     "\t%g", eos->K     /10000.0);
    		    fprintf(eosLiquids,     "\t%g", eos->Kp    );
    		    fprintf(eosLiquids,     "\t%g", eos->Kpp   *10000.0);
    		    fprintf(eosLiquids,     "\t%g", eos->Kppp  *10000.0*10000.0);    
		    for (i=0; i<nlc; i++) fprintf(eosLiquids, "\t%g", dvdm[i]*sumMoles*10.0);
        	  }
		  
		  if (pCritA > 0.0) {
        	    fprintf(titleLiquids,   "\t%g", pCritA/10000.0);
        	    fprintf(dataLiquids,    "\t%g", pCritA/10000.0);
        	    fprintf(compLiquids,    "\t%g", pCritA/10000.0);
        	    fprintf(speciesLiquids, "\t%g", pCritA/10000.0);
        	    fprintf(rhoLiqSolids,   "\t%g", pCritA/10000.0);
		  } else {
        	    fprintf(titleLiquids,   "\t");
        	    fprintf(dataLiquids,    "\t");
        	    fprintf(compLiquids,    "\t");
        	    fprintf(speciesLiquids, "\t");
        	    fprintf(rhoLiqSolids,   "\t");
		  }
		  
		  if (pCritB > 0.0) {
        	    fprintf(titleLiquids,   "\t%g", pCritB/10000.0);
        	    fprintf(dataLiquids,    "\t%g", pCritB/10000.0);
        	    fprintf(compLiquids,    "\t%g", pCritB/10000.0);
        	    fprintf(speciesLiquids, "\t%g", pCritB/10000.0);
        	    fprintf(rhoLiqSolids,   "\t%g", pCritB/10000.0);
		  } else {
        	    fprintf(titleLiquids,   "\t");
        	    fprintf(dataLiquids,    "\t");
        	    fprintf(compLiquids,    "\t");
        	    fprintf(speciesLiquids, "\t");
        	    fprintf(rhoLiqSolids,   "\t");
		  }
		  
		}
              }
	      
              for (i=0; i<nls; i++) fprintf(speciesLiquids, "\t%g", xSpecies[i]);
              for (i=0; i<nc; i++)  fprintf(speciesLiquids, "\t%g", (sum != 0.0) ? 100.0*wt[i]/sum: 0.0);

              fprintf(dataLiquids,    "\n");
              fprintf(compLiquids,    "\n");
              fprintf(speciesLiquids, "\n");
              fprintf(eosLiquids,     "\n");

	      /* This is the end of all liquid processing */
	    } else if (!strcmp((char *) level2->name, "phase" )) {
	      char *phaseNameXML = (char *) xmlGetProp(level2, (unsigned char *) "type");
	      char *phaseName;
	      int deRef = FALSE;
	      int bypass = FALSE;
	      xmlNode *level3 = level2->children;
	      
	      if      (!strcmp(phaseNameXML, "sulfide"        )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "oxide"          )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "cas"            )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "nakalsi"        )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "hollandite"     )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "carbonate"      )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "carbonateliquid")) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "sodalite"       )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "sillimanite"    )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "kyanite"        )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "staurolite"     )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "zoisite"        )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "cordierite"     )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "chevkinite"     )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "clay"           )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "chevkinite"     )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "epidote"        )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "montdorite"     )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "phlogopite"     )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "tisicomp"       )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "amphibole"      )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "melilite"       )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "biotite"        )) bypass = TRUE;
	      else if (!strcmp(phaseNameXML, "armacolite"     )) bypass = TRUE;
	      
	      if (!bypass) {
          	double totalGrams;
	        if	(!strcmp(phaseNameXML, "cpx"))            phaseName = "clinopyroxene";
	        else if (!strcmp(phaseNameXML, "opx"))            phaseName = "orthopyroxene"; 
	        else if (!strcmp(phaseNameXML, "plagioclase"))    phaseName = "feldspar"; 
	        else if (!strcmp(phaseNameXML, "kspar"))          phaseName = "feldspar"; 
	        else if (!strcmp(phaseNameXML, "ilmenite"))       phaseName = "msg oxide"; 
	        else if (!strcmp(phaseNameXML, "fluid"))          phaseName = "water"; 
	        else if (!strcmp(phaseNameXML, "leucite"))        phaseName = "leucite ss"; 
	        else if (!strcmp(phaseNameXML, "nepheline"))      phaseName = "nepheline ss"; 
	        else if (!strcmp(phaseNameXML, "titanite"))       phaseName = "sphene"; 
  	        else if (!strcmp(phaseNameXML, "caperovskite"))   phaseName = "caperovskite-sx";
  	        else if (!strcmp(phaseNameXML, "stishovite"))     phaseName = "stishovite-sx";
  	        else if (!strcmp(phaseNameXML, "coesite"))        phaseName = "coesite-sx";
  	        else if (!strcmp(phaseNameXML, "perovskite"))     phaseName = "perovskite ss";
		else if (!strcmp(phaseNameXML, "ferropericlase")) phaseName = "wustite ss";
		else if (!strcmp(phaseNameXML, "garnet"))         phaseName = "majorite ss";
	        else { 
	          phaseName = (char *) malloc((size_t) (strlen(phaseNameXML)+1)*sizeof(char)); 
	          phaseName = strcpy(phaseName, phaseNameXML);
	          deRef = TRUE;
	        }
	        xmlFree(phaseNameXML);

	        /* process a phase with name phaseName */
                /* phaseName can be Solid, ENTROPY (S J/gfw), ENTHALPY (H kJ/gfw), LIQUID (composition) */
                for (i=0, id=0; i<npc; i++) if (solids[i].type == PHASE) {
		  if(solids[i].inclInClb && !strcmp(solids[i].label, phaseName)) break;  
		  id += 1;
		} 
                if (id == np) { 
                  if (deRef) free(phaseName); break;
                } else if (deRef) free(phaseName);

                fprintf(titleLiquids,   "\t%s", (phases[id])->name);
                fprintf(rhoLiqSolids,   "\t%s", (phases[id])->name);

	        for (i=0; i<nc; i++) wt[i] = 0.0;
	        hORsCon = 0.0;
	        while (level3 != NULL) {
	          if (level3->type == XML_ELEMENT_NODE) {
	            xmlChar *content3 = xmlNodeGetContent(level3);
	            for (i=0; i<nc; i++) if (!strcmp((char *) level3->name, oxNamesLC[i])) {
	              wt[i] = atof((char *) content3);
	              break;
	            }
	            if ((!strcmp((char *) level3->name, "enthalpy")) || (!strcmp((char *) level3->name, "entropy"))) 
	              hORsCon = atof((char *) content3);
	            if (content3 != NULL) xmlFree(content3);
	          }
	          level3 = level3->next;
	        }

          	if ((phases[id])->ptFile == NULL) {
          	  if (output == NULL) output = (char *) malloc (	(size_t) ((phases[id])->len+5)*sizeof(char));
	  	  else  	      output = (char *) realloc(output, (size_t) ((phases[id])->len+5)*sizeof(char));
	  	  for (i=0; i<((phases[id])->len+5); i++) output[i] = '\0';
          	  
          	  output = strncpy(output, (phases[id])->name, (phases[id])->len);
          	  for (i=0; i<(phases[id])->len; i++) {
          	    if(output[i] == ' ') output[i] = '-';
          	  }
          	  output = strncat(output, ".out", 4);
          	  printf("Attempting to open output file %s for analysis.\n", output);
          	  if (((phases[id])->ptFile = fopen (output, "w")) == NULL) {
          	    printf("...Failure to open file. Exit.\n");
          	    exit(0);
          	  }
   		  fprintf((phases[id])->ptFile, "%s\t%s\t%s\t%s\t%s\t%s\t%s", "liq No", "LEPR num", "name", "author", "device", "container", "method");
   		  fprintf((phases[id])->ptFile, "\t%s\t%s\t%s", "T (C)", "P (GPa)", "log10 fO2");
		  for (i=0; i<nc; i++) fprintf((phases[id])->ptFile, "\t%s", bulkSystem[i].label);
		  fprintf((phases[id])->ptFile, "\t%s", "sum");
		  if ((phases[id])->convert != NULL) {
		    for (i=0; i<(phases[id])->na; i++) fprintf((phases[id])->ptFile, "\tX");
		    fprintf((phases[id])->ptFile, "\tstatus");
		  }
		  fprintf((phases[id])->ptFile, "\n");
          	} 

          	((phases[id])->n)++;

                fprintf((phases[id])->ptFile, "%d\t%d\t%s\t%s\t%s\t%s\t%s", nl, LEPRnum, name, author, device, container, method);
                fprintf((phases[id])->ptFile, "\t%g\t%g\t%g", t-273.15, p/10000.0, logfo2);
	      
          	for (sum = 0.0, i=0; i<nc; i++) {
          	  sum += wt[i]; fprintf((phases[id])->ptFile, "\t%g", wt[i]); 
	  	}
          	fprintf((phases[id])->ptFile, "\t%g", sum);
	  	
	  	totalGrams = sum;

          	if ((phases[id])->convert != NULL) {
	  	  /* Multicomponent solid phase */
          	  /* Convert wt % oxides to moles of oxides */
          	  for (i=0; i<nc; i++) wt[i] /= bulkSystem[i].mw;

          	  /* Convert moles of oxides to moles of elements */
          	  for (i=0; i<107; i++) {
          	    elements[i] = 0.0;
          	    for (j=0; j<nc; j++) {
          	      if ((bulkSystem[j].oxToElm)[i] != 0) 
          		elements[i] += ((double) (bulkSystem[j].oxToElm)[i])*wt[j];
          	    }
          	  }

          	  /* Convert moles of elements to moles of endmember components */
          	  (*((phases[id])->convert)) (FIRST, SECOND, t, p, elements, (phases[id])->moles, NULL, NULL, NULL, NULL, NULL, NULL);

          	  /* Output mole fractions of endmember components */
          	  for (i=0, sum=0.0; i<(phases[id])->na; i++) sum += ((phases[id])->moles)[i];
          	  for (i=0; i<(phases[id])->na; i++) {
          	    if (sum != 0.0) fprintf((phases[id])->ptFile, "\t%g", ((phases[id])->moles)[i]/sum);
          	  }

          	  if (!(*((phases[id])->test)) (SIXTH, t, p, 0, 0, NULL, NULL, NULL, (phases[id])->moles)) {
          	    printf("-->Phase %s in liquid %d fails validation test.\n", (phases[id])->name, nl);
          	    fprintf((phases[id])->ptFile, "\t-->Phase fails validation test.");
	  	    fprintf(rhoLiqSolids, "\t");
	  	  } else {
	  	    double v;
          	    (*((phases[id])->convert)) (SECOND, THIRD, t, p, NULL, (phases[id])->moles, (phases[id])->r, NULL, NULL, NULL, NULL, NULL);
	  	    (*((phases[id])->vmix)) (FIRST, t, p, (phases[id])->r, &v, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
	  	    v *= sum;
	  	    for (i=0; i<(phases[id])->na; i++) {
	  	      int solIndex = (phases[id])->index + 1 + i;
	  	      gibbs(t, p, (char *) solids[solIndex].label, &(solids[solIndex].ref), NULL, NULL, &(solids[solIndex].cur));
	  	      v += (solids[solIndex].cur.v)*((phases[id])->moles)[i];
	  	    }
	  	    fprintf(rhoLiqSolids, "\t%g", (v != 0.0) ? totalGrams/(10.0*v) : 0.0);
		    
		    if (!strcmp("orthopyroxene", phaseName) && isPigeonite(t, p, (phases[id])->r)) {
		      printf("Opx in experiment %d is really a pigeonite!\n", LEPRnum);
		      fprintf((phases[id])->ptFile, "\t-->Pigeonite.");
		    }
		    
		    if (!strcmp("clinopyroxene", phaseName) && isOrthopyroxene(t, p, (phases[id])->r)) {
		      printf("Cpx in experiment %d is really an opx!\n", LEPRnum);
		      fprintf((phases[id])->ptFile, "\t-->Opx.");
		    }
	  	  }
	  	
          	} else {
	  	  /* Single component solid phase */
	  	  int solIndex = (phases[id])->index;
	  	  gibbs(t, p, (char *) solids[solIndex].label, &(solids[solIndex].ref), NULL, NULL, &(solids[solIndex].cur));
	  	  fprintf(rhoLiqSolids, "\t%g", (solids[solIndex].mw)/(10.0*solids[solIndex].cur.v));
	  	}

          	fprintf((phases[id])->ptFile, "\n");
		
	      } else xmlFree(phaseNameXML); /* end if block on bypass phase */
	    }
	    
	    if (content2 != NULL) xmlFree(content2);
	  }  
	  level2 = level2->next;
	} /* This is the end of the while loop on level2 - no more entries for this experiment */
	 
	fprintf(titleLiquids,   "\n");
        fprintf(rhoLiqSolids,   "\n");
      } /* This is the end of the if block testing if a level1 node is an experiment */
      if (content1 != NULL) xmlFree(content1);
      
    } /* This is the end of the if block testing if level1 is a node */
    level1 = level1->next;
    
  } /* This is the end of the while loop level1 is NULL */
  
  if (doc    != NULL) xmlFreeDoc(doc);
  if (ctxt2  != NULL) xmlSchemaFreeValidCtxt(ctxt2);
  if (schema != NULL) xmlSchemaFree(schema);
  xmlSchemaCleanupTypes();
  xmlCleanupParser();	  

  (void) fclose(titleLiquids);
  (void) fclose(dataLiquids);
  (void) fclose(compLiquids);
  (void) fclose(speciesLiquids);
  (void) fclose(rhoLiqSolids);
  free(xSpecies);
  free(rLiq);
  free(dvdx);
  free(dvdm);
  for (i=0; i<(nlc-1); i++) free(drdmLiq[i]);
  free(drdmLiq);

  exit(0);   
}

/* End file: TEST_DATABASE.C */

