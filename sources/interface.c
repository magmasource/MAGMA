const char *interface_ver(void) { return "$Id: interface.c,v 1.13 2009/05/14 04:23:59 ghiorso Exp $"; }
/*
 MELTS Source Code: RCS $Log: interface.c,v $
 MELTS Source Code: RCS Revision 1.9  2008/03/06 17:51:23  ghiorso
 MELTS Source Code: RCS New fluid fractionation mode and other enhancements.
 MELTS Source Code: RCS
 MELTS Source Code: RCS Revision 1.8  2007/12/22 22:43:30  ghiorso
 MELTS Source Code: RCS Fixed error in BM integration in Gibbs.c
 MELTS Source Code: RCS Updated param_struct_data.h file for AGU 2007 xMELTS parameters
 MELTS Source Code: RCS Added support for status file production in MELTS-batch (XML)
 MELTS Source Code: RCS
 MELTS Source Code: RCS Revision 1.7  2007/10/29 19:58:02  ghiorso
 MELTS Source Code: RCS Updated ss volume terms for new regression.
 MELTS Source Code: RCS Miscellaneous fixes.
 MELTS Source Code: RCS
 MELTS Source Code: RCS Revision 1.6  2007/08/23 16:09:36  ghiorso
 MELTS Source Code: RCS Database updates.
 MELTS Source Code: RCS
 MELTS Source Code: RCS Revision 1.5  2007/06/14 16:41:58  ghiorso
 MELTS Source Code: RCS Corrected error in Batch MELTS (xml, Tinc)
 MELTS Source Code: RCS
 MELTS Source Code: RCS Revision 1.4  2007/06/08 17:25:42  ghiorso
 MELTS Source Code: RCS Added code to allow regression of Ghiorso EOS parameters
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
 MELTS Source Code: RCS Revision 1.3  2005/01/24 03:38:04  cvsaccount
 MELTS Source Code: RCS
 MELTS Source Code: RCS Added new files and modifications to perform builds for MgO-SiO2 system
 MELTS Source Code: RCS
 MELTS Source Code: RCS Revision 1.2  2004/12/04 19:10:36  cvsaccount
 MELTS Source Code: RCS *** empty log message ***
 MELTS Source Code: RCS
 MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
 MELTS Source Code: RCS CTserver University of Chicago
 MELTS Source Code: RCS
 MELTS Source Code: RCS Revision 1.3  2003/05/01 17:33:54  ghiorso
 MELTS Source Code: RCS *** empty log message ***
 MELTS Source Code: RCS
 MELTS Source Code: RCS Revision 1.2  2003/04/28 20:44:46  ghiorso
 MELTS Source Code: RCS *** empty log message ***
 MELTS Source Code: RCS
 MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
 MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
 MELTS Source Code: RCS
 MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
 MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
 MELTS Source Code: RCS
 * Revision 3.6  1997/06/21  22:49:51  ghiorso
 * June 1997 MELTS 3.0.x release
 * (prior to new entropy and regression model being introduced)
 *
 * Revision 3.5  1997/05/03  20:23:30  ghiorso
 * *** empty log message ***
 *
 * Revision 3.4  1997/03/27  17:03:33  ghiorso
 * *** empty log message ***
 *
 * Revision 3.3  1996/09/24  20:33:38  ghiorso
 * Version modified for OSF/1 4.0
 *
 * Revision 3.2  1995/12/09  19:26:38  ghiorso
 * Interface revisions for status box and graphics display
 *
 * Revision 3.1  1995/08/18  17:41:13  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 * Revision 3.1  1995/08/18  17:41:13  ghiorso
 * MELTS Version 3 - Initial Entry
 *
 */

/*
 **++
 **  FACILITY:  Silicate Melts Regression/Crystallization Package
 **
 **  MODULE DESCRIPTION:
 **
 **      User Interface main program (file: INTERFACE.C)
 **
 **  MODIFICATION HISTORY:
 **
 **      V1.0-1  Mark S. Ghiorso  August 20, 1990   Original Version
 **              Canabalized from TEST.C (graph widget test facility)
 **              Testing of basic Widget structures
 **      V1.0-2  Mark S. Ghiorso  August 23, 1990
 **              First modularization
 **      V1.0-3  Mark S. Ghiorso  August 24, 1990
 **              Second modularization
 **      V1.0-4  Mark S. Ghiorso  September 8, 1990
 **              Stabilitized logic for initial conditions and looping
 **      V1.0-5  Mark S. Ghiorso  August 30, 1991
 **              Added global definitions of extern widgets
 **      V1.0-6  Mark S. Ghiorso  October 18, 1991
 **              Added management of silmin_padb widget
 **      V2.0-1  Mark S. Ghiorso  November 14, 1991
 **              Conversion to OSF Motif V1.1.1/X11 Release 4
 **      V2.0-2  Mark S. Ghiorso  November 23, 1991
 **              Removed silmin_padb widget
 **      V2.0-3  Mark S. Ghiorso  November 29, 1991
 **              (1) Added icon pixmap, icon name and toLevel shell
 **                  title. The latter defines the application release
 **      V2.0-4  Mark S. Ghiorso  February 18, 1992
 **              (1) Minor changes for ANSI compliance
 **      V2.0-5  Mark S. Ghiorso  March 17, 1992
 **              Version 1.0 - alpha release
 **      V2.0-6  Mark S. Ghiorso  June 14, 1993
 **              Version 1.1.1 - beta release
 **      V2.0-7  Mark S. Ghiorso  September 21, 1993
 **              Corrected fifth argument to XtVaAppInitialize
 **              Version 1.1.2 - beta release
 **      V2.0-8  Mark S. Ghiorso  October 5, 1993
 **              Version 1.1.3 - beta release
 **      V2.0-9  Mark S. Ghiorso  March 16, 1993
 **              Added cast to (Cardinal *) for R4 OpenVMS alpha
 **              platform
 **      V3.0-1  Mark S. Ghiorso  May 11, 1994
 **              (1) Added banner for Version 2.0.1 alpha release
 **      V3.0-2  Mark S. Ghiorso  February, 18, 1995
 **              (1) Added banner for Version 2.0.1 beta release
 **              (2) Added demo banner
 **--
 */

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#ifdef MINGW
#include <windows.h>
#else
#ifndef SYSV
#include <sys/wait.h>
#else
#define SIGCHLD SIGCLD
#endif
#endif

#ifndef BATCH_VERSION
#include <X11/Intrinsic.h>
#include <Xm/Form.h>
#include <Xm/MainW.h>
#include "interface.h"
#else
#include <libxml/encoding.h>
#include <libxml/xmlschemas.h>
#include <libxml/xmlschemastypes.h>
#include <libxml/xmlwriter.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#ifdef MINGW
#define DIR_DELIM "\\"
#else
#define DIR_DELIM "/"
#endif
#endif

/*
 *=============================================================================
 * Initialize global SILMIN structures
 */

#include "silmin.h"

#ifdef BATCH_VERSION
#include "status.h"
MeltsStatus meltsStatus;
#endif

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
#endif

int calculationMode = MODE_DEFAULT;
int quad_tol_modifier = 1;

void (*additionalOutput) (char *filename) = NULL;
char *addOutputFileName = NULL;

#ifdef BATCH_VERSION
static SilminState *previousSilminState;
#endif

#ifdef RHYOLITE_ADJUSTMENTS
#define RELEASE "rhyolite-MELTS (1.0.2, 1.1.0, 1.2.0) pMELTS (5.6.1) - (" __DATE__ " - " __TIME__ ")"
#else
#define RELEASE "()(p)(x)Melts (MELTS V5.6.0) - (" __DATE__ " - " __TIME__ ")"
#endif

#ifndef BATCH_VERSION

#define MAIN_WINDOW_WIDTH  1230
#define MAIN_WINDOW_HEIGHT 980
#include "melts.icon"

Widget main_window, silmin_adb, topLevel;
MeltsEnviron meltsEnviron;

static void
getCommandLineAndEnvironment (int argc, char *argv[])
{
    char *environVar;

    /***************************************************************************
     Load Default Values of Environment, Version and Command Option Variables
     **************************************************************************/
    meltsEnviron.AUTHOR_LIST = (char *) malloc ((unsigned) (strlen (MELTS_AUTHOR_LIST) + 1) * sizeof (char));
    strcpy (meltsEnviron.AUTHOR_LIST, MELTS_AUTHOR_LIST);
    meltsEnviron.DATA_DIR    = (char *) malloc ((unsigned) (strlen (MELTS_DATA_DIR) + 1) * sizeof (char));
    strcpy (meltsEnviron.DATA_DIR, MELTS_DATA_DIR);
    meltsEnviron.DATA_SUFFIX = (char *) malloc ((unsigned) (strlen (MELTS_DATA_SUFFIX) + 1) * sizeof (char));
    strcpy (meltsEnviron.DATA_SUFFIX, MELTS_DATA_SUFFIX);
    meltsEnviron.HARDWARE_VERSION = (char *) malloc ((unsigned) (strlen (MELTS_HARDWARE_VERSION) + 1) * sizeof (char));
    strcpy (meltsEnviron.HARDWARE_VERSION, MELTS_HARDWARE_VERSION);
    meltsEnviron.INPUT_DIR = (char *) malloc ((unsigned) (strlen (MELTS_INPUT_DIR) + 1) * sizeof (char));
    strcpy (meltsEnviron.INPUT_DIR, MELTS_INPUT_DIR);
    meltsEnviron.INPUT_SUFFIX = (char *) malloc ((unsigned) (strlen (MELTS_INPUT_SUFFIX) + 1) * sizeof (char));
    strcpy (meltsEnviron.INPUT_SUFFIX, MELTS_INPUT_SUFFIX);
    meltsEnviron.MOTIF_VERSION = (char *) malloc ((unsigned) (strlen (MELTS_MOTIF_VERSION) + 1) * sizeof (char));
    strcpy (meltsEnviron.MOTIF_VERSION, MELTS_MOTIF_VERSION);
    meltsEnviron.OS_VERSION = (char *) malloc ((unsigned) (strlen (MELTS_OS_VERSION) + 1) * sizeof (char));
    strcpy (meltsEnviron.OS_VERSION, MELTS_OS_VERSION);
    meltsEnviron.OUTPUT_FILE = (char *) malloc ((unsigned) (strlen (MELTS_OUTPUT_FILE) + 1) * sizeof (char));
    strcpy (meltsEnviron.OUTPUT_FILE, MELTS_OUTPUT_FILE);
    meltsEnviron.WWW_BROWSER = (char *) malloc ((unsigned) (strlen (MELTS_WWW_BROWSER) + 1) * sizeof (char));
    strcpy (meltsEnviron.WWW_BROWSER, MELTS_WWW_BROWSER);
    meltsEnviron.WWW_CALCULATOR = (char *) malloc ((unsigned) (strlen (MELTS_WWW_CALCULATOR) + 1) * sizeof (char));
    strcpy (meltsEnviron.WWW_CALCULATOR, MELTS_WWW_CALCULATOR);
    meltsEnviron.WWW_MANUAL = (char *) malloc ((unsigned) (strlen (MELTS_WWW_MANUAL) + 1) * sizeof (char));
    strcpy (meltsEnviron.WWW_MANUAL, MELTS_WWW_MANUAL);
    meltsEnviron.X_VERSION = (char *) malloc ((unsigned) (strlen (MELTS_X_VERSION) + 1) * sizeof (char));
    strcpy (meltsEnviron.X_VERSION, MELTS_X_VERSION);
    meltsEnviron.RELEASE_DATE = (char *) malloc ((unsigned) (strlen (MELTS_RELEASE_DATE) + 1) * sizeof (char));
    strcpy (meltsEnviron.RELEASE_DATE, MELTS_RELEASE_DATE);
    meltsEnviron.RELEASE_VERSION = (char *) malloc ((unsigned) (strlen (MELTS_RELEASE_VERSION) + 1) * sizeof (char));
    strcpy (meltsEnviron.RELEASE_VERSION, MELTS_RELEASE_VERSION);
    meltsEnviron.DEBUG = FALSE;

    /****************************************************************************
     Read and process command line options
     ***************************************************************************/
    while (--argc > 0)
    {
        char *option = *++argv;
        if (strcmp (option, "-usage") == 0)
        {
            printf ("*************************************************************\n");
            printf ("The following environment variables may be set:\n");
            printf ("  MELTS_DATA_DIR       (def:%s)\n", meltsEnviron.DATA_DIR);
            printf ("  MELTS_DATA_SUFFIX    (def:%s)\n", meltsEnviron.DATA_SUFFIX);
            printf ("  MELTS_INPUT_DIR      (def:%s)\n", meltsEnviron.INPUT_DIR);
            printf ("  MELTS_INPUT_SUFFIX   (def:%s)\n", meltsEnviron.INPUT_SUFFIX);
            printf ("  MELTS_OUTPUT_FILE    (def:%s)\n", meltsEnviron.OUTPUT_FILE);
            printf ("  MELTS_WWW_BROWSER    (def:%s)\n", meltsEnviron.WWW_BROWSER);
            printf ("  MELTS_WWW_CALCULATOR (def:%s)\n", meltsEnviron.WWW_CALCULATOR);
            printf ("  MELTS_WWW_MANUAL     (def:%s)\n", meltsEnviron.WWW_MANUAL);
            printf ("*************************************************************\n");
            printf ("The following command line options may be set:\n");
            printf ("  -usage   Generates this output.\n");
            printf ("  -debug   Turns on debug mode.\n");
            printf ("*************************************************************\n");
        }
        else if (strcmp (option, "-debug") == 0)
        {
            meltsEnviron.DEBUG = TRUE;
            printf ("Debug mode is activated.\n");
        }
        else
        {
            printf ("%s is an unknown command line option.\n", option);
            printf ("   ->Try retyping command as: melts -usage\n");
        }
    }

    /****************************************************************************
     Read and process environment variables
     ***************************************************************************/
    if ((environVar = getenv ("MELTS_DATA_DIR")) != NULL)
    {
        meltsEnviron.DATA_DIR = (char *) realloc (meltsEnviron.DATA_DIR, (unsigned) (strlen (environVar) + 1) * sizeof (char));
        strcpy (meltsEnviron.DATA_DIR, environVar);
        printf ("Overwritten default value for MELTS_DATA_DIR: %s\n", meltsEnviron.DATA_DIR);
    }
    if ((environVar = getenv ("MELTS_DATA_SUFFIX")) != NULL)
    {
        meltsEnviron.DATA_SUFFIX = (char *) realloc (meltsEnviron.DATA_SUFFIX, (unsigned) (strlen (environVar) + 1) * sizeof (char));
        strcpy (meltsEnviron.DATA_SUFFIX, environVar);
        printf ("Overwritten default value for MELTS_DATA_SUFFIX: %s\n", meltsEnviron.DATA_SUFFIX);
    }
    if ((environVar = getenv ("MELTS_INPUT_DIR")) != NULL)
    {
        meltsEnviron.INPUT_DIR = (char *) realloc (meltsEnviron.INPUT_DIR, (unsigned) (strlen (environVar) + 1) * sizeof (char));
        strcpy (meltsEnviron.INPUT_DIR, environVar);
        printf ("Overwritten default value for MELTS_INPUT_DIR: %s\n", meltsEnviron.INPUT_DIR);
    }
    if ((environVar = getenv ("MELTS_INPUT_SUFFIX")) != NULL)
    {
        meltsEnviron.INPUT_SUFFIX = (char *) realloc (meltsEnviron.INPUT_SUFFIX, (unsigned) (strlen (environVar) + 1) * sizeof (char));
        strcpy (meltsEnviron.INPUT_SUFFIX, environVar);
        printf ("Overwritten default value for MELTS_INPUT_SUFFIX: %s\n", meltsEnviron.INPUT_SUFFIX);
    }
    if ((environVar = getenv ("MELTS_OUTPUT_FILE")) != NULL)
    {
        meltsEnviron.OUTPUT_FILE = (char *) realloc (meltsEnviron.OUTPUT_FILE, (unsigned) (strlen (environVar) + 1) * sizeof (char));
        strcpy (meltsEnviron.OUTPUT_FILE, environVar);
        printf ("Overwritten default value for MELTS_OUTPUT_FILE: %s\n", meltsEnviron.OUTPUT_FILE);
    }
    if ((environVar = getenv ("MELTS_WWW_BROWSER")) != NULL)
    {
        meltsEnviron.WWW_BROWSER = (char *) realloc (meltsEnviron.WWW_BROWSER, (unsigned) (strlen (environVar) + 1) * sizeof (char));
        strcpy (meltsEnviron.WWW_BROWSER, environVar);
        printf ("Overwritten default value for MELTS_WWW_BROWSER: %s\n", meltsEnviron.WWW_BROWSER);
    }
    if ((environVar = getenv ("MELTS_WWW_CALCULATOR")) != NULL)
    {
        meltsEnviron.WWW_CALCULATOR = (char *) realloc (meltsEnviron.WWW_CALCULATOR, (unsigned) (strlen (environVar) + 1) * sizeof (char));
        strcpy (meltsEnviron.WWW_CALCULATOR, environVar);
        printf ("Overwritten default value for MELTS_WWW_CALCULATOR: %s\n", meltsEnviron.WWW_CALCULATOR);
    }
    if ((environVar = getenv ("MELTS_WWW_MANUAL")) != NULL)
    {
        meltsEnviron.WWW_MANUAL = (char *) realloc (meltsEnviron.WWW_MANUAL, (unsigned) (strlen (environVar) + 1) * sizeof (char));
        strcpy (meltsEnviron.WWW_MANUAL, environVar);
        printf ("Overwritten default value for MELTS_WWW_MANUAL: %s\n", meltsEnviron.WWW_MANUAL);
    }

    return;
}
#else /* BATCH_VERSION */

#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))
#define REC 134

/* returns TRUE if successful */
/*         FALSE if not       */

static int batchInputDataFromFile(char *fileName)
{
    static char *label;
    static FILE *input = NULL;
    static char line[REC];
    static double *oxideWt;

    size_t len;
    int i, j, np, ns;
    float temporary;
    double sum;

    /* -> Check validity of file name */

    if ((input = fopen (fileName, "r")) == NULL) {
        printf("Error in SILMIN file input procedure. Cannot open file: %s\n", fileName);
        return FALSE;
    }

    /* -> Initial global and static storage */

    if (silminInputData.name != NULL) free(silminInputData.name);
    silminInputData.name = (char *) malloc((size_t) (strlen(fileName)+1)*sizeof(char));
    (void) strcpy(silminInputData.name, fileName);

    if (label == NULL) {
        for (i=0, len=0; i<nc; i++) len = MAX(len, (int) strlen(bulkSystem[i].label));
        label = (char *) malloc((unsigned) (len+1)*sizeof(char));
    }
    if (oxideWt == NULL) oxideWt = (double *) malloc((unsigned) nc*sizeof(double));

    /* -> Set default values */

    sum = 0.0;
    for (i=0; i<nc; i++) oxideWt[i] = 0.0;

    for (i=0, np=0; i<npc; i++) if (solids[i].type == PHASE) { (silminState->incSolids)[np] = TRUE; np++; }
    (silminState->incSolids)[npc] = TRUE;

    silminState->nLiquidCoexist  = 1;
    silminState->fo2Path  = FO2_NONE;

    /* -> Read input data file */

    for (;;) {
        /* -> title record */
        if (fgets(line, REC, input) == NULL) break;
        len = strlen(line); for (i=0; i<len; i++) line[i] = tolower(line[i]);

        if        (!strncmp(line, "title: ",                 MIN(len, 7))) {

            /* -> initial composition record */
        } else if (!strncmp(line, "initial composition: ",   MIN(len,21))) {
            for (i=0; i<nc; i++) {
                for (j=0; j < ((int)strlen(bulkSystem[i].label)); j++) label[j] = tolower((bulkSystem[i].label)[j]);
                label[j] = '\0';
                if (!strncmp(&line[21], label, MIN((len-21), (int) strlen(label)))) {
                    if (sscanf(&line[21 + (int) strlen(label)], "%f", &temporary) == EOF) { return FALSE; }
                    oxideWt[i]  = (double) temporary;
                    sum        += (double) temporary;
                    break;
                }
            }
            if (i == nc) { return FALSE; }

            /* -> initial temperature record */
        } else if (!strncmp(line, "initial temperature: ",   MIN(len,21))) {
            if (sscanf(&line[21], "%f", &temporary) == EOF) { return FALSE; }
            silminState->T         = (double) temporary + 273.15;
            silminState->dspTstart = (double) temporary + 273.15;

            /* -> final temperature record */
        } else if (!strncmp(line, "final temperature: ",     MIN(len,19))) {
            if (sscanf(&line[19], "%f", &temporary) == EOF) { return FALSE; }
            silminState->dspTstop = (double) temporary + 273.15;

            /* -> increment temperature record */
        } else if (!strncmp(line, "increment temperature: ", MIN(len,23))) {
            if (sscanf(&line[23], "%f", &temporary) == EOF) { return FALSE; }
            silminState->dspTinc = (double) temporary;

            /* -> initial pressure record */
        } else if (!strncmp(line, "initial pressure: ",      MIN(len,18))) {
            if (sscanf(&line[18], "%f", &temporary) == EOF) { return FALSE; }
            silminState->P         = (double) temporary;
            silminState->dspPstart = (double) temporary;

            /* -> final pressure record */
        } else if (!strncmp(line, "final pressure: ",        MIN(len,16))) {
            if (sscanf(&line[16], "%f", &temporary) == EOF) { return FALSE; }
            silminState->dspPstop = (double) temporary;

            /* -> increment pressure record */
        } else if (!strncmp(line, "increment pressure: ",    MIN(len,20))) {
            if (sscanf(&line[20], "%f", &temporary) == EOF) { return FALSE; }
            silminState->dspPinc = (double) temporary;

            /* -> dp/dt record */
        } else if (!strncmp(line, "dp/dt: ",                 MIN(len, 7))) {
            if (sscanf(&line[7], "%f", &temporary) == EOF) { return FALSE; }
            silminState->dspDPDt = (double) temporary;

            /* -> increment enthalpy record */
        } else if (!strncmp(line, "increment enthalpy: ", MIN(len,20))) {
            if (sscanf(&line[20], "%f", &temporary) == EOF) { return FALSE; }
            silminState->dspHinc = (double) temporary;

            /* -> increment entropy record */
        } else if (!strncmp(line, "increment entropy: ", MIN(len,19))) {
            if (sscanf(&line[19], "%f", &temporary) == EOF) { return FALSE; }
            silminState->dspSinc = (double) temporary;

            /* -> increment volume record */
        } else if (!strncmp(line, "increment volume: ", MIN(len,18))) {
            if (sscanf(&line[18], "%f", &temporary) == EOF) { return FALSE; }
            silminState->dspVinc = (double) temporary;

            /* -> dp/dH record */
        } else if (!strncmp(line, "dp/dh: ",                 MIN(len, 7))) {
            if (sscanf(&line[7], "%f", &temporary) == EOF) { return FALSE; }
            silminState->dspDPDH = (double) temporary;

            /* -> dp/dS record */
        } else if (!strncmp(line, "dp/ds: ",                 MIN(len, 7))) {
            if (sscanf(&line[7], "%f", &temporary) == EOF) { return FALSE; }
            silminState->dspDPDS = (double) temporary;

            /* -> dt/dV record */
        } else if (!strncmp(line, "dt/dv: ",                 MIN(len, 7))) {
            if (sscanf(&line[7], "%f", &temporary) == EOF) { return FALSE; }
            silminState->dspDVDt = (temporary != 0.0) ? (double) 1.0/temporary : 0.0;

            /* -> log fo2 path record */
        } else if (!strncmp(line, "log fo2 path: ",          MIN(len,14))) {
            if      (!strncmp(&line[14], "none",  MIN((len-14), 4))) silminState->fo2Path  = FO2_NONE;
            else if (!strncmp(&line[14], "fmq",   MIN((len-14), 3))) silminState->fo2Path  = FO2_QFM;
            else if (!strncmp(&line[14], "coh",   MIN((len-14), 3))) silminState->fo2Path  = FO2_COH;
            else if (!strncmp(&line[14], "nno",   MIN((len-14), 3))) silminState->fo2Path  = FO2_NNO;
            else if (!strncmp(&line[14], "iw",    MIN((len-14), 2))) silminState->fo2Path  = FO2_IW;
            else if (!strncmp(&line[14], "hm",    MIN((len-14), 2))) silminState->fo2Path  = FO2_HM;
            else if (!strncmp(&line[14], "+3fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_P3;
            else if (!strncmp(&line[14], "+2fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_P2;
            else if (!strncmp(&line[14], "+1fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_P1;
            else if (!strncmp(&line[14], "-1fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M1;
            else if (!strncmp(&line[14], "-2fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M2;
            else if (!strncmp(&line[14], "-3fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M3;
            else if (!strncmp(&line[14], "-4fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M4;
            else if (!strncmp(&line[14], "-5fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M5;
            else if (!strncmp(&line[14], "-6fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M6;
            else if (!strncmp(&line[14], "-7fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M7;
            else if (!strncmp(&line[14], "-8fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M8;
            else if (!strncmp(&line[14], "-9fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_M9;
            else if (!strncmp(&line[14], "+0.5fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_P0_5;
            else if (!strncmp(&line[14], "+1.5fmq", MIN((len-14), 5))) silminState->fo2Path  = FO2_QFM_P1_5;
            else { return FALSE; }

            /* -> log fo2 delta record */
        } else if (!strncmp(line, "log fo2 offset:", MIN(len, 15))) {
            if (sscanf(&line[15], "%f", &temporary) == EOF) { return FALSE; }
            silminState->fo2Delta = (double) temporary;

            /* -> suppress a solid phase record */
        } else if (!strncmp(line, "suppress: ",              MIN(len,10))) {
            for (i=0, j=0; i<npc; i++) {
                if (solids[i].type == PHASE) {
                    int phaseStrLen = (int) strlen(solids[i].label);
                    if (((len-10-phaseStrLen)  == 0) && !strncmp(&line[10], solids[i].label, phaseStrLen)) {
                        if ( solids[i].nr == 0 || (solids[i].nr > 0 && solids[i].convert != NULL)) {
                            (silminState->incSolids)[j] = FALSE;
                        }
                        break;
                    }
                    j++;
                }
            }
            if (i == npc) { return FALSE; }

            /* -> mode record */
        } else if (!strncmp(line, "mode: ",                   MIN(len, 6))) {
            if      (!strncmp(&line[6],  "fractionate solids",  MIN((len-6), 18))) silminState->fractionateSol = TRUE;
            else if (!strncmp(&line[6],  "fractionate liquids", MIN((len-6), 19))) silminState->fractionateLiq = TRUE;
            else if (!strncmp(&line[6],  "fractionate fluids",  MIN((len-6), 18))) silminState->fractionateFlu = TRUE;
            else if (!strncmp(&line[6],  "multiple liquids",    MIN((len-6), 16))) silminState->multipleLiqs   = TRUE;
            else if (!strncmp(&line[6],  "isenthalpic",	  MIN((len-6), 11))) silminState->isenthalpic	 = TRUE;
            else if (!strncmp(&line[6],  "isentropic",	  MIN((len-6), 10))) silminState->isentropic	 = TRUE;
            else if (!strncmp(&line[6],  "isochoric", 	  MIN((len-6),  9))) silminState->isochoric	 = TRUE;
            else { return FALSE; }

            /* -> assimilate a solid phase record */
        } else if (!strncmp(line, "assimilant: ",            MIN(len,12))) {

            silminState->assimilate = TRUE;
            if (silminState->nDspAssimComp == NULL) silminState->nDspAssimComp = (int *)     calloc((unsigned) (npc+nc), sizeof(int));
            if (silminState->dspAssimComp  == NULL) silminState->dspAssimComp  = (double **) calloc((unsigned) (npc+nc), sizeof(double *));

            if        (!strncmp(&line[12],  "units ",       MIN((len-12),  6))) {
                if      (!strncmp(&line[18],  "vol %", MIN((len-18), 5))) silminState->dspAssimUnits = ASSIM_PADB_UNITS_VOLUME;
                else if (!strncmp(&line[18],  "wt %",  MIN((len-18), 4))) silminState->dspAssimUnits = ASSIM_PADB_UNITS_WEIGHT;
                else { return FALSE; }
            } else if (!strncmp(&line[12],  "temperature ", MIN((len-12), 12))) {
                if (sscanf(&line[24], "%f", &temporary) == EOF) { return FALSE; }
                silminState->dspAssimT = (double) temporary;
            } else if (!strncmp(&line[12],  "mass ",        MIN((len-12),  5))) {
                if (sscanf(&line[17], "%f", &temporary) == EOF) { return FALSE; }
                silminState->dspAssimMass = (double) temporary;
            } else if (!strncmp(&line[12],  "increments ",  MIN((len-12), 11))) {
                if (sscanf(&line[23], "%f", &temporary) == EOF) { return FALSE; }
                silminState->dspAssimInc = (double) temporary;
            } else if (!strncmp(&line[12],  "liquid mass ",  MIN((len-12), 12))) {
                if (sscanf(&line[24], "%f", &temporary) == EOF) { return FALSE; }
                silminState->dspAssimLiqM = (double) temporary;
            } else {
                for (i=0; i<npc; i++) {
                    if (!strncmp(&line[12], solids[i].label, MIN((len-12), (int) strlen(solids[i].label)))) {
                        if (sscanf(&line[12 + (int) strlen(solids[i].label)], "%f", &temporary) == EOF) { return FALSE; }
                        if ((ns = (silminState->nDspAssimComp)[i]) == 0) (silminState->dspAssimComp)[i] = (double *) malloc((unsigned) sizeof(double));
                        else  (silminState->dspAssimComp)[i] = (double *) REALLOC((silminState->dspAssimComp)[i], (unsigned) (ns+1)*sizeof(double));
                        (silminState->nDspAssimComp)[i]++;
                        (silminState->dspAssimComp)[i][ns] = (double) temporary;
                        break;
                    }
                }
                if (i == npc) {
                    for (i=0; i<nc; i++) {
                        for (j=0; j < ((int)strlen(bulkSystem[i].label)); j++) label[j] = tolower((bulkSystem[i].label)[j]);
                        label[j] = '\0';
                        if (!strncmp(&line[12], label, MIN((len-12), (int) strlen(label)))) {
                            if (sscanf(&line[12 + (int) strlen(label)], "%f", &temporary) == EOF) { return FALSE; }
                            if ((ns = (silminState->nDspAssimComp)[npc+i]) == 0) (silminState->dspAssimComp)[npc+i] = (double *) malloc((unsigned) sizeof(double));
                            else  (silminState->dspAssimComp)[npc+i] = (double *) REALLOC((silminState->dspAssimComp)[npc+i], (unsigned)(ns+1)*sizeof(double));
                            (silminState->nDspAssimComp)[npc+i]++;
                            (silminState->dspAssimComp)[npc+i][ns] = (double) temporary;
                            break;
                        }
                    }
                    if (i == nc) { return FALSE; }
                }
            }

            /* -> illegal record */
        } else {
            return FALSE;
        }
    }

    /* -> Close and discard file and return */

    fclose(input);

    for (i=0, silminState->liquidMass=0.0; i<nc; i++) {
        silminState->liquidMass    += oxideWt[i];
        (silminState->bulkComp)[i]  = oxideWt[i]/bulkSystem[i].mw;
    }

    for (i=0; i<nlc; i++)
        for ((silminState->liquidComp)[0][i]=0.0, silminState->oxygen=0.0, j=0; j<nc; j++) {
            (silminState->liquidComp)[0][i] += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i];
            silminState->oxygen += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
        }

    printf("Input file read. Waiting for command or user input.\n");
    return TRUE;
}

static void SelectComputeDataStruct(void) {

   if (calculationMode == MODE_xMELTS) {
        printf("---> Calculation mode is xMELTS (experimental v 2.0.0).\n");
    } else if ((calculationMode == MODE__MELTS) ||
               (calculationMode == MODE__MELTSandCO2) ||
               (calculationMode == MODE__MELTSandCO2_H2O) ){
#ifdef RHYOLITE_ADJUSTMENTS
                                                           printf("---> ************************************************************\n");
        if      (calculationMode == MODE__MELTS)           printf("---> Calculation mode is rhyolite-MELTS (public release v 1.0.2).\n");
        else if (calculationMode == MODE__MELTSandCO2)     printf("---> Calculation mode is rhyolite-MELTS (public release v 1.1.0).\n");
        else if (calculationMode == MODE__MELTSandCO2_H2O) printf("---> Calculation mode is rhyolite-MELTS (public release v 1.2.0).\n");
                                                           printf("---> ************************************************************\n");
#else
        printf("---> ***************************************************\n");
        printf("---> Calculation mode is MELTS (public release v 5.6.1).\n");
        printf("---> ***************************************************\n");
#endif
        if (calculationMode == MODE__MELTS) {
            liquid = meltsLiquid;
            solids = meltsSolids;
            nlc = meltsNlc;
            nls = meltsNls;
            npc = meltsNpc;
        } else if ((calculationMode == MODE__MELTSandCO2) || (calculationMode == MODE__MELTSandCO2_H2O)) {
            liquid = meltsFluidLiquid;
            solids = meltsFluidSolids;
            nlc = meltsFluidNlc;
            nls = meltsFluidNls;
            npc = meltsFluidNpc;
        }

    } else if (calculationMode == MODE_pMELTS) {
        printf("---> ****************************************************\n");
        printf("---> Calculation mode is pMELTS (public release v 5.6.1).\n");
        printf("---> ****************************************************\n");
        liquid = pMeltsLiquid;
        solids = pMeltsSolids;
        nlc = pMeltsNlc;
        nls = pMeltsNls;
        npc = pMeltsNpc;
    }

}

/* returns RUN_LIQUIDUS_CALC    or           */
/*         RUN_EQUILIBRATE_CALC if succesful */
/*         FALSE                if not       */

#define RUN_WETLIQUIDUS_CALC    1
#define RUN_LIQUIDUS_CALC       2
#define RUN_EQUILIBRATE_CALC    3
#define RETURN_WITHOUT_CALC     4
#define RETURN_DO_FRACTIONATION 5

#define RETURN_FINALIZED        6

static int batchInputDataFromXmlFile(char *fileName) {
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt = NULL;
    xmlSchemaValidCtxtPtr ctxt2 = NULL;
    int ret = TRUE;
    static int SiO2 = -1, TiO2, Al2O3, Fe2O3, Cr2O3, FeO, MnO, MgO, NiO, CoO, CaO, Na2O, K2O, P2O5, H2O, CO2;

    if (silminInputData.name != NULL) free(silminInputData.name);
    silminInputData.name = (char *) malloc((size_t) (strlen(fileName)+1)*sizeof(char));
    (void) strcpy(silminInputData.name, fileName);

    ctxt = xmlSchemaNewParserCtxt("MELTSinput.xsd");
    xmlSchemaSetParserErrors(ctxt,(xmlSchemaValidityErrorFunc) fprintf, (xmlSchemaValidityWarningFunc) fprintf, stderr);

    schema = xmlSchemaParse(ctxt);
    xmlSchemaFreeParserCtxt(ctxt);

    if (schema != NULL) {
        xmlDocPtr doc = NULL;

        ctxt2 = xmlSchemaNewValidCtxt(schema);
        xmlSchemaSetValidErrors(ctxt2,(xmlSchemaValidityErrorFunc) fprintf,(xmlSchemaValidityWarningFunc) fprintf, stderr);

        doc = xmlReadFile(fileName, NULL, 0);
        if (doc) {
            if (xmlSchemaValidateDoc(ctxt2, doc)) {
                printf("File %s is invalid against schema MELTSinput.xsd.\n", fileName);
                ret = FALSE;
            } else {
                xmlNode *root_element = xmlDocGetRootElement(doc);
                xmlNode *level1 = root_element->children;
                printf("File %s has been validated against schema MELTSinput.xsd.\n", fileName);

                while (level1 != NULL) {
                    if (level1->type == XML_ELEMENT_NODE) {
                        xmlChar *content1 = xmlNodeGetContent(level1);

                        if        (!strcmp((char *) level1->name, "initialize")) {
                            xmlNode *level2 = level1->children;
                            int i, j, np;
                            printf("Found initialize: %s\n", content1);

                            if (silminState != NULL)
                                destroySilminStateStructure(silminState); /*destroy the old state*/
                                /*if (silminState == NULL) silminState = allocSilminStatePointer();
                                    was testing to avoid memory leak when destroy was nyi */

                            while (level2 != NULL) {
                                if (level2->type == XML_ELEMENT_NODE) {
                                    xmlChar *content2 = xmlNodeGetContent(level2);
                                    char *pEnd = NULL;
                                    errno = 0;

                                    if (!strcmp((char *) level2->name, "modelSelection")) { /* first time through */
                                        printf("Found modelSelection: %s\n", content2);

                                        if (SiO2 == -1) {

                                            /* 'default' does not change the calculationMode */
                                                 if (!strcmp((char *) content2, "MELTS_v1.0.x")) calculationMode = MODE__MELTS;
                                            else if (!strcmp((char *) content2, "MELTS_v1.1.x")) calculationMode = MODE__MELTSandCO2;
                                            else if (!strcmp((char *) content2, "MELTS_v1.2.x")) calculationMode = MODE__MELTSandCO2_H2O;
                                            else if (!strcmp((char *) content2, "pMELTS_v5.6.1")) calculationMode = MODE_pMELTS;

                                            printf("---> Initializing data structures using selected calculation mode...\n");
                                            SelectComputeDataStruct();
                                            InitComputeDataStruct();
                                            int i;
                                            for (i=0; i<nc; i++) {
                                                if      (!strcmp(bulkSystem[i].label, "SiO2" )) SiO2  = i;
                                                else if (!strcmp(bulkSystem[i].label, "TiO2" )) TiO2  = i;
                                                else if (!strcmp(bulkSystem[i].label, "Al2O3")) Al2O3 = i;
                                                else if (!strcmp(bulkSystem[i].label, "Fe2O3")) Fe2O3 = i;
                                                else if (!strcmp(bulkSystem[i].label, "Cr2O3")) Cr2O3 = i;
                                                else if (!strcmp(bulkSystem[i].label, "FeO"  )) FeO   = i;
                                                else if (!strcmp(bulkSystem[i].label, "MnO"  )) MnO   = i;
                                                else if (!strcmp(bulkSystem[i].label, "MgO"  )) MgO   = i;
                                                else if (!strcmp(bulkSystem[i].label, "NiO"  )) NiO   = i;
                                                else if (!strcmp(bulkSystem[i].label, "CoO"  )) CoO   = i;
                                                else if (!strcmp(bulkSystem[i].label, "CaO"  )) CaO   = i;
                                                else if (!strcmp(bulkSystem[i].label, "Na2O" )) Na2O  = i;
                                                else if (!strcmp(bulkSystem[i].label, "K2O"  )) K2O   = i;
                                                else if (!strcmp(bulkSystem[i].label, "P2O5" )) P2O5  = i;
                                                else if (!strcmp(bulkSystem[i].label, "H2O"  )) H2O   = i;
                                                else if (!strcmp(bulkSystem[i].label, "CO2"  )) CO2   = i;
                                            }
                                        }
                                        else if ((!strcmp((char *) content2, "MELTS_v1.0.x") && calculationMode != MODE__MELTS) ||
                                                (!strcmp((char *) content2, "MELTS_v1.1.x")  && calculationMode != MODE__MELTSandCO2) ||
                                                (!strcmp((char *) content2, "MELTS_v1.2.x")  && calculationMode != MODE__MELTSandCO2_H2O) ||
                                                (!strcmp((char *) content2, "pMELTS_v5.6.1") && calculationMode != MODE_pMELTS)) {
                                            printf("Error: cannot change modelSelection after it has been initialized.\n");
                                            ret = FALSE;
                                        }

                                        silminState = allocSilminStatePointer();
                                        for (i=0, np=0; i<npc; i++) if (solids[i].type == PHASE) { (silminState->incSolids)[np] = TRUE; np++; }
                                        (silminState->incSolids)[npc] = TRUE;
                                        silminState->nLiquidCoexist  = 1;
                                        silminState->fo2Path  = FO2_NONE;
                                        silminState->T = 0.0;
                                        silminState->P = 0.0;
                                        silminState->assimilate = FALSE;

                                        for (i=0, silminState->liquidMass=0.0; i<nc; i++) (silminState->bulkComp)[i] = 0.0;
                                    }

                                    if (strcmp((char *) level2->name, "modelSelection")) { /* subsequent passes through */
                                             if (!strcmp((char *) level2->name, "SiO2" )) (silminState->bulkComp)[SiO2 ] = strtod((char *) content2, &pEnd)/bulkSystem[SiO2 ].mw;
                                        else if (!strcmp((char *) level2->name, "TiO2" )) (silminState->bulkComp)[TiO2 ] = strtod((char *) content2, &pEnd)/bulkSystem[TiO2 ].mw;
                                        else if (!strcmp((char *) level2->name, "Al2O3")) (silminState->bulkComp)[Al2O3] = strtod((char *) content2, &pEnd)/bulkSystem[Al2O3].mw;
                                        else if (!strcmp((char *) level2->name, "Fe2O3")) (silminState->bulkComp)[Fe2O3] = strtod((char *) content2, &pEnd)/bulkSystem[Fe2O3].mw;
                                        else if (!strcmp((char *) level2->name, "Cr2O3")) (silminState->bulkComp)[Cr2O3] = strtod((char *) content2, &pEnd)/bulkSystem[Cr2O3].mw;
                                        else if (!strcmp((char *) level2->name, "FeO"  )) (silminState->bulkComp)[FeO  ] = strtod((char *) content2, &pEnd)/bulkSystem[FeO  ].mw;
                                        else if (!strcmp((char *) level2->name, "MnO"  )) (silminState->bulkComp)[MnO  ] = strtod((char *) content2, &pEnd)/bulkSystem[MnO  ].mw;
                                        else if (!strcmp((char *) level2->name, "MgO"  )) (silminState->bulkComp)[MgO  ] = strtod((char *) content2, &pEnd)/bulkSystem[MgO  ].mw;
                                        else if (!strcmp((char *) level2->name, "NiO"  )) (silminState->bulkComp)[NiO  ] = strtod((char *) content2, &pEnd)/bulkSystem[NiO  ].mw;
                                        else if (!strcmp((char *) level2->name, "CoO"  )) (silminState->bulkComp)[CoO  ] = strtod((char *) content2, &pEnd)/bulkSystem[CoO  ].mw;
                                        else if (!strcmp((char *) level2->name, "CaO"  )) (silminState->bulkComp)[CaO  ] = strtod((char *) content2, &pEnd)/bulkSystem[CaO  ].mw;
                                        else if (!strcmp((char *) level2->name, "Na2O" )) (silminState->bulkComp)[Na2O ] = strtod((char *) content2, &pEnd)/bulkSystem[Na2O ].mw;
                                        else if (!strcmp((char *) level2->name, "K2O"  )) (silminState->bulkComp)[K2O  ] = strtod((char *) content2, &pEnd)/bulkSystem[K2O  ].mw;
                                        else if (!strcmp((char *) level2->name, "P2O5" )) (silminState->bulkComp)[P2O5 ] = strtod((char *) content2, &pEnd)/bulkSystem[P2O5 ].mw;
                                        else if (!strcmp((char *) level2->name, "H2O"  )) (silminState->bulkComp)[H2O  ] = strtod((char *) content2, &pEnd)/bulkSystem[H2O  ].mw;
                                        else if (!strcmp((char *) level2->name, "CO2"  )) (silminState->bulkComp)[CO2  ] = strtod((char *) content2, &pEnd)/bulkSystem[CO2  ].mw;
                                        if (pEnd == (char *) content2) {
                                            printf("Invalid number format: %s.\n", (char *) content2);
                                            ret = FALSE;
                                        }
                                        else if (errno == ERANGE) {
                                            double val = strtod((char *) content2, &pEnd);
                                            printf("Invalid number(?): %s.\n", (char *) content2);
                                            if (val > 1.0) ret = FALSE; /* overflow */
                                            else errno = 0; /* underflow */
                                        }
                                        else {
                                            silminState->liquidMass += strtod((char *) content2, &pEnd);
                                        }
                                    }
                                    if (content2 != NULL) xmlFree(content2);
                                }
                                level2 = level2->next;
                            }
                            for (i=0; i<nlc; i++) {
                                for ((silminState->liquidComp)[0][i]=0.0, silminState->oxygen=0.0, j=0; j<nc; j++) {
                                    (silminState->liquidComp)[0][i] += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i];
                                    silminState->oxygen += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
                                }
                            }

                        } else if (!strcmp((char *) level1->name, "calculationMode")) {
                            printf("Found calculationMode: %s\n", content1);
                            if   (!strcmp((char *) content1, "findWetLiquidus")) ret = RUN_WETLIQUIDUS_CALC;
                            else if (!strcmp((char *) content1, "findLiquidus")) ret = RUN_LIQUIDUS_CALC;
                            else if (!strcmp((char *) content1, "equilibrate" )) ret = RUN_EQUILIBRATE_CALC;

                        } else if (!strcmp((char *) level1->name, "title")) {
                            printf("Found title: %s\n", content1);
                            if (silminInputData.title != NULL) free(silminInputData.title);
                            silminInputData.title = (char *) malloc((size_t) (strlen((char *) content1)+1)*sizeof(char));
                            (void) strcpy(silminInputData.title, (char *) content1);

                        } else if (!strcmp((char *) level1->name, "fractionateOnly")) {
                            printf("Found fractionateOnly: %s\n", content1);
                            if      (!strcmp((char *) content1, "fractionateSolids"  )) {                                      silminState->fractionateSol =  TRUE;                                      }
                            else if (!strcmp((char *) content1, "fractionateFluids"  )) { silminState->fractionateFlu =  TRUE;                                                                           }
                            else if (!strcmp((char *) content1, "fractionateLiquids" )) { silminState->fractionateFlu = FALSE; silminState->fractionateSol = FALSE; silminState->fractionateLiq =  TRUE; }

                            if ((silminState->fractionateSol || silminState->fractionateFlu) && silminState->fracSComp == (double **) NULL) {
                                silminState->fracSComp    = (double **) calloc((unsigned) npc, sizeof(double *));
                                silminState->nFracCoexist = (int *) calloc((unsigned) npc, sizeof(int));
                            }
                            if (silminState->fractionateLiq && silminState->fracLComp == (double *) NULL) {
                                silminState->fracLComp = (double *) calloc((unsigned) nlc, sizeof(double));
                            }
                            ret = RETURN_DO_FRACTIONATION;

                        } else if (!strcmp((char *) level1->name, "changeBulk")) {
                            xmlNode *level2 = level1->children;
                            int i, j;
                            static double *changeBC = NULL;

                            printf("Found changeBulk\n");
                            if (changeBC == NULL) changeBC = (double *) calloc((size_t) nc, sizeof(double));
                            else for (i=0; i<nc; i++) changeBC[i] = 0.0;

                            while (level2 != NULL) {
                                if (level2->type == XML_ELEMENT_NODE) {
                                    xmlChar *content2 = xmlNodeGetContent(level2);
                                    char *pEnd = NULL;
                                    errno = 0;
                                    if      (!strcmp((char *) level2->name, "SiO2" )) changeBC[SiO2 ] = strtod((char *) content2, &pEnd)/bulkSystem[SiO2 ].mw;
                                    else if (!strcmp((char *) level2->name, "TiO2" )) changeBC[TiO2 ] = strtod((char *) content2, &pEnd)/bulkSystem[TiO2 ].mw;
                                    else if (!strcmp((char *) level2->name, "Al2O3")) changeBC[Al2O3] = strtod((char *) content2, &pEnd)/bulkSystem[Al2O3].mw;
                                    else if (!strcmp((char *) level2->name, "Fe2O3")) changeBC[Fe2O3] = strtod((char *) content2, &pEnd)/bulkSystem[Fe2O3].mw;
                                    else if (!strcmp((char *) level2->name, "Cr2O3")) changeBC[Cr2O3] = strtod((char *) content2, &pEnd)/bulkSystem[Cr2O3].mw;
                                    else if (!strcmp((char *) level2->name, "FeO"  )) changeBC[FeO  ] = strtod((char *) content2, &pEnd)/bulkSystem[FeO  ].mw;
                                    else if (!strcmp((char *) level2->name, "MnO"  )) changeBC[MnO  ] = strtod((char *) content2, &pEnd)/bulkSystem[MnO  ].mw;
                                    else if (!strcmp((char *) level2->name, "MgO"  )) changeBC[MgO  ] = strtod((char *) content2, &pEnd)/bulkSystem[MgO  ].mw;
                                    else if (!strcmp((char *) level2->name, "NiO"  )) changeBC[NiO  ] = strtod((char *) content2, &pEnd)/bulkSystem[NiO  ].mw;
                                    else if (!strcmp((char *) level2->name, "CoO"  )) changeBC[CoO  ] = strtod((char *) content2, &pEnd)/bulkSystem[CoO  ].mw;
                                    else if (!strcmp((char *) level2->name, "CaO"  )) changeBC[CaO  ] = strtod((char *) content2, &pEnd)/bulkSystem[CaO  ].mw;
                                    else if (!strcmp((char *) level2->name, "Na2O" )) changeBC[Na2O ] = strtod((char *) content2, &pEnd)/bulkSystem[Na2O ].mw;
                                    else if (!strcmp((char *) level2->name, "K2O"  )) changeBC[K2O  ] = strtod((char *) content2, &pEnd)/bulkSystem[K2O  ].mw;
                                    else if (!strcmp((char *) level2->name, "P2O5" )) changeBC[P2O5 ] = strtod((char *) content2, &pEnd)/bulkSystem[P2O5 ].mw;
                                    else if (!strcmp((char *) level2->name, "H2O"  )) changeBC[H2O  ] = strtod((char *) content2, &pEnd)/bulkSystem[H2O  ].mw;
                                    else if (!strcmp((char *) level2->name, "CO2"  )) changeBC[CO2  ] = strtod((char *) content2, &pEnd)/bulkSystem[CO2  ].mw;
                                    if (pEnd == (char *) content2) {
                                        printf("Invalid number format: %s.\n", (char *) content2);
                                        ret = FALSE;
                                    }
                                    else if (errno == ERANGE) {
                                        double val = strtod((char *) content2, &pEnd);
                                        printf("Invalid number(?): %s.\n", (char *) content2);
                                        if (val > 1.0) ret = FALSE; /* overflow */
                                        else errno = 0; /* underflow */
                                    }
                                    else {
                                        silminState->liquidMass += strtod((char *) content2, &pEnd);
                                    }
                                    if (content2 != NULL) xmlFree(content2);
                                }
                                level2 = level2->next;
                            }

                            for (i=0; i<nc; i++) (silminState->bulkComp)[i] += changeBC[i];
                            for (i=0; i<nlc; i++)
                                for (j=0; j<nc; j++) {
                                    (silminState->liquidComp)[0][i] += changeBC[j]*(bulkSystem[j].oxToLiq)[i];
                                    silminState->oxygen += changeBC[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
                                }

                        } else if (!strcmp((char *) level1->name, "changeLiquid")) {
                            xmlNode *level2 = level1->children;
                            int i, j;
                            static double *changeBC = NULL;

                            printf("Found changeLiquid\n");
                            if (changeBC == NULL) changeBC = (double *) calloc((size_t) nc, sizeof(double));
                            else for (i=0; i<nc; i++) changeBC[i] = 0.0;

                            while (level2 != NULL) {
                                if (level2->type == XML_ELEMENT_NODE) {
                                    xmlChar *content2 = xmlNodeGetContent(level2);
                                    char *pEnd = NULL;
                                    errno = 0;
                                    if      (!strcmp((char *) level2->name, "SiO2" )) changeBC[SiO2 ] = strtod((char *) content2, &pEnd)/bulkSystem[SiO2 ].mw;
                                    else if (!strcmp((char *) level2->name, "TiO2" )) changeBC[TiO2 ] = strtod((char *) content2, &pEnd)/bulkSystem[TiO2 ].mw;
                                    else if (!strcmp((char *) level2->name, "Al2O3")) changeBC[Al2O3] = strtod((char *) content2, &pEnd)/bulkSystem[Al2O3].mw;
                                    else if (!strcmp((char *) level2->name, "Fe2O3")) changeBC[Fe2O3] = strtod((char *) content2, &pEnd)/bulkSystem[Fe2O3].mw;
                                    else if (!strcmp((char *) level2->name, "Cr2O3")) changeBC[Cr2O3] = strtod((char *) content2, &pEnd)/bulkSystem[Cr2O3].mw;
                                    else if (!strcmp((char *) level2->name, "FeO"  )) changeBC[FeO  ] = strtod((char *) content2, &pEnd)/bulkSystem[FeO  ].mw;
                                    else if (!strcmp((char *) level2->name, "MnO"  )) changeBC[MnO  ] = strtod((char *) content2, &pEnd)/bulkSystem[MnO  ].mw;
                                    else if (!strcmp((char *) level2->name, "MgO"  )) changeBC[MgO  ] = strtod((char *) content2, &pEnd)/bulkSystem[MgO  ].mw;
                                    else if (!strcmp((char *) level2->name, "NiO"  )) changeBC[NiO  ] = strtod((char *) content2, &pEnd)/bulkSystem[NiO  ].mw;
                                    else if (!strcmp((char *) level2->name, "CoO"  )) changeBC[CoO  ] = strtod((char *) content2, &pEnd)/bulkSystem[CoO  ].mw;
                                    else if (!strcmp((char *) level2->name, "CaO"  )) changeBC[CaO  ] = strtod((char *) content2, &pEnd)/bulkSystem[CaO  ].mw;
                                    else if (!strcmp((char *) level2->name, "Na2O" )) changeBC[Na2O ] = strtod((char *) content2, &pEnd)/bulkSystem[Na2O ].mw;
                                    else if (!strcmp((char *) level2->name, "K2O"  )) changeBC[K2O  ] = strtod((char *) content2, &pEnd)/bulkSystem[K2O  ].mw;
                                    else if (!strcmp((char *) level2->name, "P2O5" )) changeBC[P2O5 ] = strtod((char *) content2, &pEnd)/bulkSystem[P2O5 ].mw;
                                    else if (!strcmp((char *) level2->name, "H2O"  )) changeBC[H2O  ] = strtod((char *) content2, &pEnd)/bulkSystem[H2O  ].mw;
                                    else if (!strcmp((char *) level2->name, "CO2"  )) changeBC[CO2  ] = strtod((char *) content2, &pEnd)/bulkSystem[CO2  ].mw;
                                    if (pEnd == (char *) content2) {
                                        printf("Invalid number format: %s.\n", (char *) content2);
                                        ret = FALSE;
                                    }
                                    else if (errno == ERANGE) {
                                        double val = strtod((char *) content2, &pEnd);
                                        printf("Invalid number(?): %s.\n", (char *) content2);
                                        if (val > 1.0) ret = FALSE; /* overflow */
                                        else errno = 0; /* underflow */
                                    }
                                    else {
                                        silminState->liquidMass += strtod((char *) content2, &pEnd);
                                    }
                                    if (content2 != NULL) xmlFree(content2);
                                }
                                level2 = level2->next;
                            }

                            for (i=0; i<nc; i++) (silminState->bulkComp)[i] += changeBC[i];
                            for (i=0; i<nlc; i++)
                                for (j=0; j<nc; j++) {
                                    (silminState->liquidComp)[0][i] += changeBC[j]*(bulkSystem[j].oxToLiq)[i];
                                    silminState->oxygen += changeBC[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
                                }
                            ret = RETURN_WITHOUT_CALC;

                        } else if (!strcmp((char *) level1->name, "changeFluid")) {
                            xmlNode *level2 = level1->children;
                            int i, j;
                            int haveWater = ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS));
                            static double *changeBC = NULL;

                            printf("Found changeFluid\n");
                            if (changeBC == NULL) changeBC = (double *) calloc((size_t) nc, sizeof(double));
                            else for (i=0; i<nc; i++) changeBC[i] = 0.0;

                            while (level2 != NULL) {
                                if (level2->type == XML_ELEMENT_NODE) {
                                    xmlChar *content2 = xmlNodeGetContent(level2);
                                    char *pEnd = NULL;
                                    errno = 0;
                                         if (!strcmp((char *) level2->name, "H2O"  )) changeBC[H2O  ] = strtod((char *) content2, &pEnd)/bulkSystem[H2O  ].mw;
                                    else if (!strcmp((char *) level2->name, "CO2"  )) changeBC[CO2  ] = strtod((char *) content2, &pEnd)/bulkSystem[CO2  ].mw;
                                    if (pEnd == (char *) content2) {
                                        printf("Invalid number format: %s.\n", (char *) content2);
                                        ret = FALSE;
                                    }
                                    else if (errno == ERANGE) {
                                        double val = strtod((char *) content2, &pEnd);
                                        printf("Invalid number(?): %s.\n", (char *) content2);
                                        if (val > 1.0) ret = FALSE; /* overflow */
                                        else errno = 0; /* underflow */
                                    }
                                    else {
                                        silminState->solidMass += strtod((char *) content2, &pEnd);
                                    }
                                    if (content2 != NULL) xmlFree(content2);
                                }
                                level2 = level2->next;
                            }

                            for (i=0; i<nc; i++) (silminState->bulkComp)[i] += changeBC[i];
                            for (i=0; i<npc; i++) {
                                if (!strcmp((char *) solids[i].label, "fluid")) {
                                    silminState->solidComp[i][0] += changeBC[H2O] + changeBC[CO2];
                                    for (j=0; j<solids[i].na; j++) {
                                             if (!strcmp((char *) solids[i+j+1].formula, "H2O"  )) silminState->solidComp[i+j+1][0] += changeBC[H2O];
                                        else if (!strcmp((char *) solids[i+j+1].formula, "CO2"  )) silminState->solidComp[i+j+1][0] += changeBC[CO2];
                                    }
                                }
                                else if (haveWater && !strcmp((char *) solids[i].label, "water")) silminState->solidComp[i][0] += changeBC[H2O];
                            }
                            for (i=0; i<nlc; i++)
                                for (j=0; j<nc; j++) {
                                    silminState->oxygen += changeBC[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
                                }
                            ret = RETURN_WITHOUT_CALC;

                        } else if (!strcmp((char *) level1->name, "constraints")) {
                            xmlNode *level2 = level1->children;
                            printf("Found constraints\n");
                            while (level2 != NULL) {
                                if (level2->type == XML_ELEMENT_NODE) {
                                    if (!strcmp((char *) level2->name, "setTP")) {
                                        double oldInitialT = silminState->T;
                                        xmlNode *level3 = level2->children;
                                        printf("Found setTP\n");
                                        silminState->isenthalpic = FALSE; silminState->refEnthalpy = 0.0;
                                        silminState->isentropic  = FALSE; silminState->refEntropy  = 0.0;
                                        silminState->isochoric   = FALSE; silminState->refVolume   = 0.0;
                                        while (level3 != NULL) {
                                            if (level3->type == XML_ELEMENT_NODE) {
                                                xmlChar *content3 = xmlNodeGetContent(level3);
                                                char *pEnd = NULL;
                                                errno = 0;
                                                if      (!strcmp((char *) level3->name, "initialT" )) {
                                                    silminState->T         = strtod((char *) content3, &pEnd) + 273.15;
                                                    silminState->dspTstart = strtod((char *) content3, &pEnd) + 273.15;
                                                }
                                                else if (!strcmp((char *) level3->name, "finalT"   )) silminState->dspTstop = strtod((char *) content3, &pEnd) + 273.15;
                                                else if (!strcmp((char *) level3->name, "incT"     )) silminState->dspTinc  = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "initialP" )) {
                                                    silminState->P         = strtod((char *) content3, &pEnd);
                                                    silminState->dspPstart = strtod((char *) content3, &pEnd);
                                                }
                                                else if (!strcmp((char *) level3->name, "finalP"   )) silminState->dspPstop = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "incP"     )) silminState->dspPinc  = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "dpdt"     )) silminState->dspDPDt  = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "fo2Path"  )) {
                                                    if      (!strcmp((char *) content3, "none")) silminState->fo2Path  = FO2_NONE;
                                                    else if (!strcmp((char *) content3, "fmq" )) silminState->fo2Path  = FO2_QFM;
                                                    else if (!strcmp((char *) content3, "coh" )) silminState->fo2Path  = FO2_COH;
                                                    else if (!strcmp((char *) content3, "nno" )) silminState->fo2Path  = FO2_NNO;
                                                    else if (!strcmp((char *) content3, "iw"  )) silminState->fo2Path  = FO2_IW;
                                                    else if (!strcmp((char *) content3, "hm"  )) silminState->fo2Path  = FO2_HM;
                                                }
                                                else if (!strcmp((char *) level3->name, "fo2Offset")) silminState->fo2Delta = strtod((char *) content3, &pEnd);
                                                if (pEnd == (char *) content3) {
                                                    printf("Invalid number format: %s.\n", (char *) content3);
                                                    ret = FALSE;
                                                }
                                                else if (errno == ERANGE) {
                                                    double val = strtod((char *) content3, &pEnd);
                                                    printf("Invalid number(?): %s.\n", (char *) content3);
                                                    if (val > 1.0) ret = FALSE; /* overflow */
                                                    else errno = 0; /* underflow */
                                                }
                                                if (content3 != NULL) xmlFree(content3);
                                            }
                                            level3 = level3->next;
                                        }
                                        if ((fabs(silminState->T - oldInitialT) < 1.0e-6) && (fabs(silminState->T - silminState->dspTstop) > 1.0e-6)) {
                                            printf("Found condition where initial T is a pickup T from previous run and final T is not equal to initial T - adjusting ...\n");
                                            if (fabs(silminState->T - silminState->dspTstop) > fabs(silminState->dspTinc)) {
                                                if (silminState->T > silminState->dspTstop) {
                                                    silminState->T         -= fabs(silminState->dspTinc);
                                                    silminState->dspTstart -= fabs(silminState->dspTinc);
                                                } else {
                                                    silminState->T         += fabs(silminState->dspTinc);
                                                    silminState->dspTstart += fabs(silminState->dspTinc);
                                                }
                                                printf("... reset initial T to input value minus T increment.\n");
                                            } else {
                                                if (silminState->T > silminState->dspTstop) {
                                                    silminState->T         -= 1.0e-6;
                                                    silminState->dspTstart -= 1.0e-6;
                                                } else {
                                                    silminState->T         += 1.0e-6;
                                                    silminState->dspTstart += 1.0e-6;
                                                }
                                                printf("... reset initial T to input value minus T increment.\n");
                                            }
                                        }

                                    } else if (!strcmp((char *) level2->name, "setTV")) {
                                        xmlNode *level3 = level2->children;
                                        printf("Found setTV\n");
                                        silminState->isenthalpic = FALSE; silminState->refEnthalpy = 0.0;
                                        silminState->isentropic  = FALSE; silminState->refEntropy  = 0.0;
                                        silminState->isochoric   = TRUE;  silminState->refVolume   = 0.0;
                                        while (level3 != NULL) {
                                            if (level3->type == XML_ELEMENT_NODE) {
                                                xmlChar *content3 = xmlNodeGetContent(level3);
                                                char *pEnd = NULL;
                                                errno = 0;
                                                if      (!strcmp((char *) level3->name, "initialT" )) {
                                                    silminState->T         = strtod((char *) content3, &pEnd) + 273.15;
                                                    silminState->dspTstart = strtod((char *) content3, &pEnd) + 273.15;
                                                }
                                                else if (!strcmp((char *) level3->name, "finalT"   )) silminState->dspTstop  = strtod((char *) content3, &pEnd) + 273.15;
                                                else if (!strcmp((char *) level3->name, "incT"     )) silminState->dspTinc   = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "initialV" )) silminState->refVolume = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "finalV"   )) silminState->dspVstop  = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "incV"     )) silminState->dspVinc  = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "dvdt"     )) silminState->dspDVDt  = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "fo2Path"  )) {
                                                    if      (!strcmp((char *) content3, "none")) silminState->fo2Path  = FO2_NONE;
                                                    else if (!strcmp((char *) content3, "fmq" )) silminState->fo2Path  = FO2_QFM;
                                                    else if (!strcmp((char *) content3, "coh" )) silminState->fo2Path  = FO2_COH;
                                                    else if (!strcmp((char *) content3, "nno" )) silminState->fo2Path  = FO2_NNO;
                                                    else if (!strcmp((char *) content3, "iw"  )) silminState->fo2Path  = FO2_IW;
                                                    else if (!strcmp((char *) content3, "hm"  )) silminState->fo2Path  = FO2_HM;
                                                }
                                                else if (!strcmp((char *) level3->name, "fo2Offset")) silminState->fo2Delta = strtod((char *) content3, &pEnd);
                                                if (pEnd == (char *) content3) {
                                                    printf("Invalid number format: %s.\n", (char *) content3);
                                                    ret = FALSE;
                                                }
                                                else if (errno == ERANGE) {
                                                    double val = strtod((char *) content3, &pEnd);
                                                    printf("Invalid number(?): %s.\n", (char *) content3);
                                                    if (val > 1.0) ret = FALSE; /* overflow */
                                                    else errno = 0; /* underflow */
                                                }
                                                if (content3 != NULL) xmlFree(content3);
                                            }
                                            level3 = level3->next;
                                        }

                                    } else if (!strcmp((char *) level2->name, "setHP")) {
                                        xmlNode *level3 = level2->children;
                                        printf("Found setHP\n");
                                        silminState->isenthalpic = TRUE;
                                        silminState->isentropic  = FALSE;
                                        silminState->isochoric   = FALSE;
                                        while (level3 != NULL) {
                                            if (level3->type == XML_ELEMENT_NODE) {
                                                xmlChar *content3 = xmlNodeGetContent(level3);
                                                char *pEnd = NULL;
                                                errno = 0;
                                                if      (!strcmp((char *) level3->name, "initialH" )) silminState->refEnthalpy = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "finalH"   )) silminState->dspHstop    = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "incH"     )) silminState->dspHinc     = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "initialP" )) {
                                                    silminState->P         = strtod((char *) content3, &pEnd);
                                                    silminState->dspPstart = strtod((char *) content3, &pEnd);
                                                }
                                                else if (!strcmp((char *) level3->name, "finalP"   )) silminState->dspPstop = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "incP"     )) silminState->dspPinc  = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "dpdh"     )) silminState->dspDPDH  = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "fo2Path"  )) {
                                                    if      (!strcmp((char *) content3, "none")) silminState->fo2Path  = FO2_NONE;
                                                    else if (!strcmp((char *) content3, "fmq" )) silminState->fo2Path  = FO2_QFM;
                                                    else if (!strcmp((char *) content3, "coh" )) silminState->fo2Path  = FO2_COH;
                                                    else if (!strcmp((char *) content3, "nno" )) silminState->fo2Path  = FO2_NNO;
                                                    else if (!strcmp((char *) content3, "iw"  )) silminState->fo2Path  = FO2_IW;
                                                    else if (!strcmp((char *) content3, "hm"  )) silminState->fo2Path  = FO2_HM;
                                                }
                                                else if (!strcmp((char *) level3->name, "fo2Offset")) silminState->fo2Delta = strtod((char *) content3, &pEnd);
                                                if (pEnd == (char *) content3) {
                                                    printf("Invalid number format: %s.\n", (char *) content3);
                                                    ret = FALSE;
                                                }
                                                else if (errno == ERANGE) {
                                                    double val = strtod((char *) content3, &pEnd);
                                                    printf("Invalid number(?): %s.\n", (char *) content3);
                                                    if (val > 1.0) ret = FALSE; /* overflow */
                                                    else errno = 0; /* underflow */
                                                }
                                                if (content3 != NULL) xmlFree(content3);
                                            }
                                            level3 = level3->next;
                                        }

                                    } else if (!strcmp((char *) level2->name, "setSP")) {
                                        xmlNode *level3 = level2->children;
                                        printf("Found setSP\n");
                                        silminState->isenthalpic = FALSE; silminState->refEnthalpy = 0.0;
                                        silminState->isentropic  = TRUE;  silminState->refEntropy  = 0.0;
                                        silminState->isochoric   = FALSE; silminState->refVolume   = 0.0;
                                        while (level3 != NULL) {
                                            if (level3->type == XML_ELEMENT_NODE) {
                                                xmlChar *content3 = xmlNodeGetContent(level3);
                                                char *pEnd = NULL;
                                                errno  = 0;
                                                if      (!strcmp((char *) level3->name, "initialS" )) silminState->refEntropy = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "finalS"   )) silminState->dspSstop   = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "incS"     )) silminState->dspSinc    = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "initialP" )) {
                                                    silminState->P         = strtod((char *) content3, &pEnd);
                                                    silminState->dspPstart = strtod((char *) content3, &pEnd);
                                                }
                                                else if (!strcmp((char *) level3->name, "finalP"   )) silminState->dspPstop = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "incP"     )) silminState->dspPinc  = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "dpds"     )) silminState->dspDPDS  = strtod((char *) content3, &pEnd);
                                                else if (!strcmp((char *) level3->name, "fo2Path"  )) {
                                                    if      (!strcmp((char *) content3, "none")) silminState->fo2Path  = FO2_NONE;
                                                    else if (!strcmp((char *) content3, "fmq" )) silminState->fo2Path  = FO2_QFM;
                                                    else if (!strcmp((char *) content3, "coh" )) silminState->fo2Path  = FO2_COH;
                                                    else if (!strcmp((char *) content3, "nno" )) silminState->fo2Path  = FO2_NNO;
                                                    else if (!strcmp((char *) content3, "iw"  )) silminState->fo2Path  = FO2_IW;
                                                    else if (!strcmp((char *) content3, "hm"  )) silminState->fo2Path  = FO2_HM;
                                                }
                                                else if (!strcmp((char *) level3->name, "fo2Offset")) silminState->fo2Delta = strtod((char *) content3, &pEnd);
                                                if (pEnd == (char *) content3) {
                                                    printf("Invalid number format: %s.\n", (char *) content3);
                                                    ret = FALSE;
                                                }
                                                else if (errno == ERANGE) {
                                                    double val = strtod((char *) content3, &pEnd);
                                                    printf("Invalid number(?): %s.\n", (char *) content3);
                                                    if (val > 1.0) ret = FALSE; /* overflow */
                                                    else errno = 0; /* underflow */
                                                }
                                                if (content3 != NULL) xmlFree(content3);
                                            }
                                            level3 = level3->next;
                                        }
                                    }

                                }
                                level2 = level2->next;
                            }

                        } else if (!strcmp((char *) level1->name, "suppressPhase")) {
                            int i, j;
                            printf("Found suppressPhase: %s\n", content1);
                            for (i=0, j=0; i<npc; i++) if (solids[i].type == PHASE) {
                                if (!strcmp((char *) content1, solids[i].label)) {
                                    if (solids[i].nr == 0 || (solids[i].nr > 0 && solids[i].convert != NULL)) (silminState->incSolids)[j] = FALSE;
                                    break;
                                }
                                j++;
                            }

                        } else if (!strcmp((char *) level1->name, "fractionationMode")) {
                            printf("Found fractionationMode: %s\n", content1);
                            if      (!strcmp((char *) content1, "fractionateSolids"  )) {                                      silminState->fractionateSol =  TRUE;                                      }
                            else if (!strcmp((char *) content1, "fractionateFluids"  )) { silminState->fractionateFlu =  TRUE;                                                                           }
                            else if (!strcmp((char *) content1, "fractionateLiquids" )) { silminState->fractionateFlu = FALSE; silminState->fractionateSol = FALSE; silminState->fractionateLiq =  TRUE; }
                            else if (!strcmp((char *) content1, "fractionateNone"    )) { silminState->fractionateFlu = FALSE; silminState->fractionateSol = FALSE; silminState->fractionateLiq = FALSE; }

                            if ((silminState->fractionateSol || silminState->fractionateFlu) && silminState->fracSComp == (double **) NULL) {
                                silminState->fracSComp    = (double **) calloc((unsigned) npc, sizeof(double *));
                                silminState->nFracCoexist = (int *) calloc((unsigned) npc, sizeof(int));
                            }
                            if (silminState->fractionateLiq && silminState->fracLComp == (double *) NULL) {
                                silminState->fracLComp = (double *) calloc((unsigned) nlc, sizeof(double));
                            }

                        } else if (!strcmp((char *) level1->name, "multLiquids")) {
                            printf("Found multLiquids: %s\n", content1);
                            if (!strcmp((char *) content1, "true")) silminState->multipleLiqs = TRUE;

                        } else if (!strcmp((char *) level1->name, "assimilant")) {
                            xmlNode *level2 = level1->children;
                            printf("Found assimilant\n");
                            silminState->assimilate = TRUE;
                            silminState->dspAssimUnits = ASSIM_PADB_UNITS_WEIGHT;
                            if (silminState->nDspAssimComp == NULL) silminState->nDspAssimComp = (int *)     calloc((unsigned) (npc+nc), sizeof(int));
                            if (silminState->dspAssimComp  == NULL) silminState->dspAssimComp  = (double **) calloc((unsigned) (npc+nc), sizeof(double *));

                            while (level2 != NULL) {
                                if (level2->type == XML_ELEMENT_NODE) {
                                    xmlChar *content2 = xmlNodeGetContent(level2);
                                    char *pEnd = NULL;
                                    errno = 0;
                                    if (!strcmp((char *) level2->name, "temperature" )) {
                                        printf("Found temperature = %s\n", content2); silminState->dspAssimT = strtod((char *) content2, &pEnd);
                                    } else if (!strcmp((char *) level2->name, "increments"  )) {
                                        printf("Found increments  = %s\n", content2); silminState->dspAssimInc = atoi((char *) content2);
                                    } else if (!strcmp((char *) level2->name, "mass"        )) {
                                        printf("Found mass        = %s\n", content2); silminState->dspAssimMass = strtod((char *) content2, &pEnd);
                                    } else if (!strcmp((char *) level2->name, "units"       )) {
                                        printf("Found units       = %s\n", content2);
                                    } else if (!strcmp((char *) level2->name, "phase"       )) {
                                        xmlNode *level3 = level2->children;
                                        printf("Found phase\n");
                                        while (level3 != NULL) {
                                            if (level3->type == XML_ELEMENT_NODE) {
                                                if        (!strcmp((char *) level3->name, "amorphous" )) {
                                                    xmlNode *level4 = level3->children;
                                                    printf("Found amorphous\n");
                                                    while (level4 != NULL) {
                                                        if (level4->type == XML_ELEMENT_NODE) {
                                                            xmlChar *content4 = xmlNodeGetContent(level4);
                                                            if (!strcmp((char *) level4->name, "massFraction" )) printf("Found massFraction  = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "SiO2" )) printf("Found SiO2  = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "TiO2" )) printf("Found TiO2  = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "Al2O3")) printf("Found Al2O3 = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "Fe2O3")) printf("Found Fe2O3 = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "Cr2O3")) printf("Found Cr2O3 = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "FeO"  )) printf("Found FeO   = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "MnO"  )) printf("Found MnO   = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "MgO"  )) printf("Found MgO   = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "NiO"  )) printf("Found NiO   = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "CoO"  )) printf("Found CoO   = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "CaO"  )) printf("Found CaO   = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "Na2O" )) printf("Found Na2O  = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "K2O"  )) printf("Found K2O   = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "P2O5" )) printf("Found P2O5  = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "H2O"  )) printf("Found H2O   = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "CO2"  )) printf("Found CO2   = %s\n", content4);
                                                            if (content4 != NULL) xmlFree(content4);
                                                        }
                                                        level4 = level4->next;
                                                    }

                                                } else if (!strcmp((char *) level3->name, "solid"     )) {
                                                    xmlNode *level4 = level3->children;
                                                    printf("Found solid\n");
                                                    while (level4 != NULL) {
                                                        if (level4->type == XML_ELEMENT_NODE) {
                                                            xmlChar *content4 = xmlNodeGetContent(level4);
                                                            if      (!strcmp((char *) level4->name, "label"        )) printf("Found label         = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "massFraction" )) printf("Found massFraction  = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "component"    )) {
                                                                xmlNode *level5 = level4->children;
                                                                printf("Found component\n");
                                                                while (level5 != NULL) {
                                                                    if (level5->type == XML_ELEMENT_NODE) {
                                                                        xmlChar *content5 = xmlNodeGetContent(level5);
                                                                        if      (!strcmp((char *) level5->name, "label"   )) printf("Found label   = %s\n", content5);
                                                                        else if (!strcmp((char *) level5->name, "molFrac" )) printf("Found molFrac = %s\n", content5);
                                                                        if (content5 != NULL) xmlFree(content5);
                                                                    }
                                                                    level5 = level5->next;
                                                                }
                                                            }
                                                            if (content4 != NULL) xmlFree(content4);
                                                        }
                                                        level4 = level4->next;
                                                    }


                                                } else if (!strcmp((char *) level3->name, "liquid"    )) {
                                                    xmlNode *level4 = level3->children;
                                                    printf("Found liquid\n");
                                                    while (level4 != NULL) {
                                                        if (level4->type == XML_ELEMENT_NODE) {
                                                            int iOx = -1;
                                                            xmlChar *content4 = xmlNodeGetContent(level4);
                                                            if (!strcmp((char *) level4->name, "massFraction" )) printf("Found massFraction  = %s\n", content4);
                                                            else if (!strcmp((char *) level4->name, "SiO2" )) { printf("Found SiO2  = %s\n", content4); iOx = SiO2;  }
                                                            else if (!strcmp((char *) level4->name, "TiO2" )) { printf("Found TiO2  = %s\n", content4); iOx = TiO2;  }
                                                            else if (!strcmp((char *) level4->name, "Al2O3")) { printf("Found Al2O3 = %s\n", content4); iOx = Al2O3; }
                                                            else if (!strcmp((char *) level4->name, "Fe2O3")) { printf("Found Fe2O3 = %s\n", content4); iOx = Fe2O3; }
                                                            else if (!strcmp((char *) level4->name, "Cr2O3")) { printf("Found Cr2O3 = %s\n", content4); iOx = Cr2O3; }
                                                            else if (!strcmp((char *) level4->name, "FeO"  )) { printf("Found FeO   = %s\n", content4); iOx = FeO;   }
                                                            else if (!strcmp((char *) level4->name, "MnO"  )) { printf("Found MnO   = %s\n", content4); iOx = MnO;   }
                                                            else if (!strcmp((char *) level4->name, "MgO"  )) { printf("Found MgO   = %s\n", content4); iOx = MgO;   }
                                                            else if (!strcmp((char *) level4->name, "NiO"  )) { printf("Found NiO   = %s\n", content4); iOx = NiO;   }
                                                            else if (!strcmp((char *) level4->name, "CoO"  )) { printf("Found CoO   = %s\n", content4); iOx = CoO;   }
                                                            else if (!strcmp((char *) level4->name, "CaO"  )) { printf("Found CaO   = %s\n", content4); iOx = CaO;   }
                                                            else if (!strcmp((char *) level4->name, "Na2O" )) { printf("Found Na2O  = %s\n", content4); iOx = Na2O;  }
                                                            else if (!strcmp((char *) level4->name, "K2O"  )) { printf("Found K2O   = %s\n", content4); iOx = K2O;   }
                                                            else if (!strcmp((char *) level4->name, "P2O5" )) { printf("Found P2O5  = %s\n", content4); iOx = P2O5;  }
                                                            else if (!strcmp((char *) level4->name, "H2O"  )) { printf("Found H2O   = %s\n", content4); iOx = H2O;   }
                                                            else if (!strcmp((char *) level4->name, "CO2"  )) { printf("Found CO2   = %s\n", content4); iOx = CO2;   }
                                                            if (content4 != NULL) xmlFree(content4);
                                                        }
                                                        level4 = level4->next;
                                                    }
                                                }
                                            }
                                            level3 = level3->next;
                                        }
                                    }
                                    if (pEnd == (char *) content2) {
                                        printf("Invalid number format: %s.\n", (char *) content2);
                                        ret = FALSE;
                                    }
                                    else if (errno == ERANGE) {
                                        double val = strtod((char *) content2, &pEnd);
                                        printf("Invalid number(?): %s.\n", (char *) content2);
                                        if (val > 1.0) ret = FALSE; /* overflow */
                                        else errno = 0; /* underflow */
                                    }
                                    if (content2 != NULL) xmlFree(content2);
                                }
                                level2 = level2->next;
                            }
                        } else if (!strcmp((char *) level1->name, "finalize")) {
                            /* Currently this element has no content */
                            /*
                            xmlNode *level2 = level1->children;
                            int i, j, np;
                            printf("Found finalize: %s\n", content1);
                            */
                            printf("Found finalize\n");
                            ret = RETURN_FINALIZED;
                        }
                        if (content1 != NULL) xmlFree(content1);
                    }
                    level1 = level1->next;
                }

            }
            xmlFreeDoc(doc);
        } else {
            printf("File %s cannot be opened.\n", fileName);
            ret = FALSE;
        }

        if (ctxt2 != NULL) xmlSchemaFreeValidCtxt(ctxt2);
    } else {
        printf("No schema file found! (MELTSinput.xsd does not exist).\n");
        ret = FALSE;
    }

    if (schema != NULL) xmlSchemaFree(schema);
    //xmlSchemaCleanupTypes(); deprecated - now private and called by xmlCleanupParser
    //xmlCleanupParser();

    return ret;
}

static void putOutputDataToXmlFile(char *outputFile) {
    xmlTextWriterPtr writer;
    size_t len;
    int rc;
    time_t tp;
    char * cOut, *temporary = (char *) malloc((size_t) 40*sizeof(char));
    double gLiq = 0.0, hLiq = 0.0, sLiq = 0.0, vLiq = 0.0, cpLiq = 0.0, mLiq = 0.0, viscosity = 0.0, fracMass = 0.0;
    double totalMass=0.0, totalGibbsEnergy=0.0, totalEnthalpy=0.0, totalEntropy=0.0, totalVolume=0.0, totalHeatCapacity=0.0;
    static double *m, *r, *oxVal;
    int i, j;
    double fo2Delta;

    if (m == NULL)         m = (double *) malloc((size_t)      nc*sizeof(double));
    if (r == NULL)         r = (double *) malloc((size_t) (nlc-1)*sizeof(double));
    if (oxVal == NULL) oxVal = (double *) malloc((size_t)      nc*sizeof(double));

    /* Zero previous entries - should only be necessary if have never fractionated */
    if (previousSilminState == NULL) previousSilminState = allocSilminStatePointer();
    if (silminState->fractionateSol || silminState->fractionateFlu) {
        if (previousSilminState->nFracCoexist == NULL) {
            previousSilminState->fracSComp    = (double **) calloc((unsigned) npc, sizeof(double *));
            previousSilminState->nFracCoexist = (int *)     calloc((unsigned) npc, sizeof(int));
        }
    }
    if ((silminState->fractionateLiq) && (previousSilminState->fracLComp == NULL))
        previousSilminState->fracLComp = (double *) calloc((unsigned) nlc, sizeof(double));

    printf("Output file name is %s\n", outputFile);

    (void) time(&tp);
    cOut = ctime(&tp);
    len = strlen(cOut);
    cOut[len-1] = '\0';

    writer = xmlNewTextWriterFilename(outputFile, 0);
    rc = xmlTextWriterStartDocument(writer, NULL, "UTF-8", NULL);

    rc = xmlTextWriterStartElement(writer, BAD_CAST "MELTSoutput");

    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "inputFile", "%s", silminInputData.name);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "outputFile","%s", outputFile);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "title",     "%s", silminInputData.title);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "time",      "%s", cOut);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "release",   "%s", RELEASE);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "buildDate", "%s", __DATE__);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "buildTime", "%s", __TIME__);

    rc = sprintf(temporary, "%23.16e", silminState->T-273.15); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "temperature", "%s", temporary);
    rc = sprintf(temporary, "%23.16e", silminState->P);        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "pressure",    "%s", temporary);
    rc = sprintf(temporary, "%23.16e", silminState->fo2);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "log_fO2",     "%s", temporary);

    fo2Delta = silminState->fo2Delta; silminState->fo2Delta = 0;
    rc = sprintf(temporary, "%23.16e", silminState->fo2 - getlog10fo2(silminState->T, silminState->P, FO2_HM));  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "deltaHM",     "%s", temporary);
    rc = sprintf(temporary, "%23.16e", silminState->fo2 - getlog10fo2(silminState->T, silminState->P, FO2_NNO)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "deltaNNO",    "%s", temporary);
    rc = sprintf(temporary, "%23.16e", silminState->fo2 - getlog10fo2(silminState->T, silminState->P, FO2_QFM)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "deltaFMQ",    "%s", temporary);
    rc = sprintf(temporary, "%23.16e", silminState->fo2 - getlog10fo2(silminState->T, silminState->P, FO2_COH)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "deltaCOH",    "%s", temporary);
    rc = sprintf(temporary, "%23.16e", silminState->fo2 - getlog10fo2(silminState->T, silminState->P, FO2_IW));  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "deltaIW",     "%s", temporary);
    silminState->fo2Delta = fo2Delta;

    if (silminState->liquidMass != 0.0) {
        int nl;

        for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
            double moles, oxSum;
            double gibbsEnergy, enthalpy, entropy, volume, heatCapacity;

            rc = xmlTextWriterStartElement(writer, BAD_CAST "liquid");

            conLiq(SECOND, THIRD, silminState->T, silminState->P, NULL, silminState->liquidComp[nl], r, NULL, NULL, NULL, NULL);

            gmixLiq (FIRST, silminState->T, silminState->P, r, &gibbsEnergy,  NULL, NULL);
            hmixLiq (FIRST, silminState->T, silminState->P, r, &enthalpy,	  NULL);
            smixLiq (FIRST, silminState->T, silminState->P, r, &entropy,	  NULL, NULL, NULL);
            vmixLiq (FIRST, silminState->T, silminState->P, r, &volume,	  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            cpmixLiq(FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
            visLiq  (FIRST, silminState->T, silminState->P, r, &viscosity);

            for (i=0, moles=0.0; i<nlc; i++) moles +=  (silminState->liquidComp)[nl][i];
            gibbsEnergy  *= moles;
            enthalpy     *= moles;
            entropy      *= moles;
            volume	     *= moles;
            heatCapacity *= moles;

            for (i=0; i<nlc; i++) {
                gibbsEnergy  += (silminState->liquidComp)[nl][i]*(liquid[i].cur).g;
                enthalpy     += (silminState->liquidComp)[nl][i]*(liquid[i].cur).h;
                entropy      += (silminState->liquidComp)[nl][i]*(liquid[i].cur).s;
                volume       += (silminState->liquidComp)[nl][i]*(liquid[i].cur).v;
                heatCapacity += (silminState->liquidComp)[nl][i]*(liquid[i].cur).cp;
            }

            for (i=0, oxSum=0.0; i<nc; i++) {
                for (j=0, oxVal[i]=0.0; j<nlc; j++) oxVal[i] += (liquid[j].liqToOx)[i]*(silminState->liquidComp)[nl][j];
                oxVal[i] *= bulkSystem[i].mw;
                oxSum	   += oxVal[i];
            }
            if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;

            gLiq += gibbsEnergy; hLiq += enthalpy; sLiq += entropy; vLiq += volume; cpLiq += heatCapacity; mLiq += oxSum;

            rc = sprintf(temporary, "%23.16e", oxSum);        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",            "%s", temporary);
            rc = sprintf(temporary, "%23.16e", (volume == 0.0) ? 0.0 : oxSum/(10.0*volume)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density", "%s", temporary);
            rc = sprintf(temporary, "%23.16e", viscosity);    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "viscosity",       "%s", temporary);
            rc = sprintf(temporary, "%23.16e", gibbsEnergy);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%s", temporary);
            rc = sprintf(temporary, "%23.16e", enthalpy);     rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",        "%s", temporary);
            rc = sprintf(temporary, "%23.16e", entropy);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",         "%s", temporary);
            rc = sprintf(temporary, "%23.16e", volume*10.0);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",          "%s", temporary);
            rc = sprintf(temporary, "%23.16e", heatCapacity); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%s", temporary);

            for (i=0; i<nc; i++) if (oxVal[i] != 0.0) {
                 rc = sprintf(temporary, "%23.16e", oxVal[i]*100.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%s", temporary);
            }
            rc = xmlTextWriterEndElement(writer);
        }
    }

    for (j=0, totalMass=0.0, totalGibbsEnergy=0.0, totalEnthalpy=0.0,
         totalEntropy=0.0, totalVolume=0.0, totalHeatCapacity=0.0; j<npc; j++) {
        int ns;
        for (ns=0; ns<(silminState->nSolidCoexist)[j]; ns++) {
            double oxSum, mass, gibbsEnergy, enthalpy, entropy, volume, heatCapacity;

            rc = xmlTextWriterStartElement(writer, BAD_CAST "solid");

            if (solids[j].na == 1) {
                mass  	     = (silminState->solidComp)[j][ns]*solids[j].mw;
                gibbsEnergy	     = (silminState->solidComp)[j][ns]*(solids[j].cur).g;
                enthalpy	     = (silminState->solidComp)[j][ns]*(solids[j].cur).h;
                entropy	     = (silminState->solidComp)[j][ns]*(solids[j].cur).s;
                volume	     = (silminState->solidComp)[j][ns]*(solids[j].cur).v;
                heatCapacity       = (silminState->solidComp)[j][ns]*(solids[j].cur).cp;
                totalMass	    += (silminState->solidComp)[j][ns]*solids[j].mw;
                totalGibbsEnergy  += (silminState->solidComp)[j][ns]*(solids[j].cur).g;
                totalEnthalpy     += (silminState->solidComp)[j][ns]*(solids[j].cur).h;
                totalEntropy      += (silminState->solidComp)[j][ns]*(solids[j].cur).s;
                totalVolume	    += (silminState->solidComp)[j][ns]*(solids[j].cur).v;
                totalHeatCapacity += (silminState->solidComp)[j][ns]*(solids[j].cur).cp;

                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",            "%s",   solids[j].label);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",         "%s",   solids[j].formula);
                rc = sprintf(temporary, "%23.16e", mass);         rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", 	   "%s", temporary);
                rc = sprintf(temporary, "%23.16e", (volume == 0.0) ? 0.0 : mass/(10.0*volume)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density", "%s", temporary);
                rc = sprintf(temporary, "%23.16e", gibbsEnergy);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%s", temporary);
                rc = sprintf(temporary, "%23.16e", enthalpy);     rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	     "%s", temporary);
                rc = sprintf(temporary, "%23.16e", entropy);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	     "%s", temporary);
                rc = sprintf(temporary, "%23.16e", volume*10.0);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",	         "%s", temporary);
                rc = sprintf(temporary, "%23.16e", heatCapacity); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%s", temporary);

                for (i=0, oxSum=0.0; i<nc; i++) {
                    oxVal[i]  = (solids[j].solToOx)[i]*bulkSystem[i].mw;
                    oxSum    += oxVal[i];
                }
                if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                for (i=0; i<nc; i++) if (oxVal[i] != 0.0) {
                    rc = sprintf(temporary, "%23.16e", oxVal[i]*100.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%s", temporary);
                }
                rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",         "%s",   solids[j].label);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",      "%s",   solids[j].formula);
                rc = sprintf(temporary, "%23.16e", 1.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%s", temporary);
                rc = xmlTextWriterEndElement(writer);

            } else {
                char *formula;
                for (i=0, mass=0.0; i<solids[j].na; i++) {
                    m[i] = (silminState->solidComp)[j+1+i][ns];
                    mass += (silminState->solidComp)[j+1+i][ns]*solids[j+1+i].mw;
                }
                (*solids[j].convert)(SECOND, THIRD, silminState->T, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
                (*solids[j].display)(FIRST, silminState->T, silminState->P, r, &formula);
                (*solids[j].gmix) (FIRST, silminState->T, silminState->P, r, &gibbsEnergy,  NULL, NULL, NULL);
                (*solids[j].hmix) (FIRST, silminState->T, silminState->P, r, &enthalpy);
                (*solids[j].smix) (FIRST, silminState->T, silminState->P, r, &entropy,      NULL, NULL);
                (*solids[j].vmix) (FIRST, silminState->T, silminState->P, r, &volume,       NULL, NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL);
                (*solids[j].cpmix)(FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
                gibbsEnergy  *= (silminState->solidComp)[j][ns];
                enthalpy     *= (silminState->solidComp)[j][ns];
                entropy      *= (silminState->solidComp)[j][ns];
                volume       *= (silminState->solidComp)[j][ns];
                heatCapacity *= (silminState->solidComp)[j][ns];
                for (i=0; i<solids[j].na; i++) {
                    gibbsEnergy  += m[i]*(solids[j+1+i].cur).g;
                    enthalpy	 += m[i]*(solids[j+1+i].cur).h;
                    entropy	 += m[i]*(solids[j+1+i].cur).s;
                    volume	 += m[i]*(solids[j+1+i].cur).v;
                    heatCapacity += m[i]*(solids[j+1+i].cur).cp;
                }
                totalMass	    += mass;
                totalGibbsEnergy  += gibbsEnergy;
                totalEnthalpy     += enthalpy;
                totalEntropy      += entropy;
                totalVolume	    += volume;
                totalHeatCapacity += heatCapacity;

                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",            "%s",   solids[j].label);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",         "%s",   formula); free(formula);
                rc = sprintf(temporary, "%23.16e", mass);         rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", 	   "%s", temporary);
                rc = sprintf(temporary, "%23.16e", (volume == 0.0) ? 0.0 : mass/(10.0*volume)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density", "%s", temporary);
                rc = sprintf(temporary, "%23.16e", gibbsEnergy);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%s", temporary);
                rc = sprintf(temporary, "%23.16e", enthalpy);     rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	     "%s", temporary);
                rc = sprintf(temporary, "%23.16e", entropy);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy", 	     "%s", temporary);
                rc = sprintf(temporary, "%23.16e", volume*10.0);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",	         "%s", temporary);
                rc = sprintf(temporary, "%23.16e", heatCapacity); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%s", temporary);

                for (i=0, oxSum=0.0; i<nc; i++) {
                    int k;
                    for (k=0, oxVal[i]=0.0; k<solids[j].na; k++) oxVal[i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw;
                    oxSum += oxVal[i];
                }
                if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                for (i=0; i<nc; i++) if (oxVal[i] != 0.0) {
                    rc = sprintf(temporary, "%23.16e", oxVal[i]*100.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%s", temporary);
                }

                for (i=0; i<solids[j].na; i++) {
                    rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",         "%s",   solids[j+1+i].label);
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",      "%s",   solids[j+1+i].formula);
                    rc = sprintf(temporary, "%23.16e", m[i]/(silminState->solidComp)[j][ns]); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%s", temporary);
                    rc = xmlTextWriterEndElement(writer);
                }
            }

            rc = xmlTextWriterEndElement(writer);
        }
    }

    if (totalMass != 0.0) {
        rc = xmlTextWriterStartElement(writer, BAD_CAST "totalSolids");
        rc = sprintf(temporary, "%23.16e", totalMass);         rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",		      "%s", temporary);
        rc = sprintf(temporary, "%23.16e", (totalVolume == 0.0) ? 0.0 : totalMass/(10.0*totalVolume)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density", "%s", temporary);
        rc = sprintf(temporary, "%23.16e", totalGibbsEnergy);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%s", temporary);
        rc = sprintf(temporary, "%23.16e", totalEnthalpy);     rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",        "%s", temporary);
        rc = sprintf(temporary, "%23.16e", totalEntropy);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",         "%s", temporary);
        rc = sprintf(temporary, "%23.16e", totalVolume*10.0);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",          "%s", temporary);
        rc = sprintf(temporary, "%23.16e", totalHeatCapacity); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",	  "%s", temporary);
        rc = xmlTextWriterEndElement(writer);
    }

    if (silminState->isenthalpic && (silminState->refEnthalpy == 0.0)) silminState->refEnthalpy = hLiq+totalEnthalpy;
    if (silminState->isentropic  && (silminState->refEntropy  == 0.0)) silminState->refEntropy  = sLiq+totalEntropy;
    if (silminState->isochoric   && (silminState->refVolume   == 0.0)) silminState->refVolume   = vLiq+totalVolume;

    fracMass = (silminState->fractionateSol || silminState->fractionateFlu || silminState->fractionateLiq) ?
        (silminState->fracMass-previousSilminState->fracMass) : 0.0;

    if ((silminState->fractionateSol || silminState->fractionateFlu || silminState->fractionateLiq) && (fracMass > 0.0)) {
        rc = xmlTextWriterStartElement(writer, BAD_CAST "fractionate");
        rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "type", BAD_CAST "current");
        rc = sprintf(temporary, "%23.16e", silminState->fracMass-previousSilminState->fracMass); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", "%s", temporary);

        if (silminState->fractionateSol || silminState->fractionateFlu) {
            int haveWater = ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS));
            for (j=0; j<npc; j++) {
                int ns;

                if ( haveWater &&  silminState->fractionateSol && !silminState->fractionateFlu && !strcmp((char *) solids[j].label, "water")) continue;
                if ( haveWater && !silminState->fractionateSol &&  silminState->fractionateFlu &&  strcmp((char *) solids[j].label, "water")) continue;
                if (!haveWater &&  silminState->fractionateSol && !silminState->fractionateFlu && !strcmp((char *) solids[j].label, "fluid")) continue;
                if (!haveWater && !silminState->fractionateSol &&  silminState->fractionateFlu &&  strcmp((char *) solids[j].label, "fluid")) continue;

                for (ns=0; ns<(silminState->nFracCoexist)[j]; ns++) {
                    double oxSum, mass, gibbsEnergy, enthalpy, entropy, volume, heatCapacity;
                    double tmpMoles = ((previousSilminState->nFracCoexist)[j] <= ns) ? (silminState->fracSComp)[j][ns]
                    : (silminState->fracSComp)[j][ns] - (previousSilminState->fracSComp)[j][ns];
                    if (fabs(tmpMoles) < 10.0*DBL_EPSILON) continue;

                    rc = xmlTextWriterStartElement(writer, BAD_CAST "solid");

                    if (solids[j].na == 1) {
                        mass		   = tmpMoles*solids[j].mw;
                        gibbsEnergy	   = tmpMoles*(solids[j].cur).g;
                        enthalpy	   = tmpMoles*(solids[j].cur).h;
                        entropy 	   = tmpMoles*(solids[j].cur).s;
                        volume  	   = tmpMoles*(solids[j].cur).v;
                        heatCapacity	   = tmpMoles*(solids[j].cur).cp;
                        totalMass	  += tmpMoles*solids[j].mw;
                        totalGibbsEnergy  += tmpMoles*(solids[j].cur).g;
                        totalEnthalpy	  += tmpMoles*(solids[j].cur).h;
                        totalEntropy	  += tmpMoles*(solids[j].cur).s;
                        totalVolume	  += tmpMoles*(solids[j].cur).v;
                        totalHeatCapacity += tmpMoles*(solids[j].cur).cp;

                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",		 "%s",   solids[j].label);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",	 "%s",   solids[j].formula);
                        rc = sprintf(temporary, "%23.16e", mass);         rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",	         "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", (volume == 0.0) ? 0.0 : mass/(10.0*volume)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density", "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", gibbsEnergy);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", enthalpy);     rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	     "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", entropy);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	     "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", volume*10.0);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",          "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", heatCapacity); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",	 "%s", temporary);

                        for (i=0, oxSum=0.0; i<nc; i++) {
                            oxVal[i]  = (solids[j].solToOx)[i]*bulkSystem[i].mw;
                            oxSum    += oxVal[i];
                        }
                        if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                        for (i=0; i<nc; i++) if (oxVal[i] != 0.0) {
                            rc = sprintf(temporary, "%23.16e", oxVal[i]*100.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%s", temporary);
                        }
                        rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",         "%s",   solids[j].label);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",      "%s",   solids[j].formula);
                        rc = sprintf(temporary, "%23.16e", 1.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%s", temporary);
                        rc = xmlTextWriterEndElement(writer);

                    } else {
                        char *formula;
                        for (i=0, mass=0.0; i<solids[j].na; i++) {
                            double tmpCmpMoles = ((previousSilminState->nFracCoexist)[j] <= ns) ? (silminState->fracSComp)[j+1+i][ns]
                            : (silminState->fracSComp)[j+1+i][ns] - (previousSilminState->fracSComp)[j+1+i][ns];
                            m[i]  = tmpCmpMoles;
                            mass += tmpCmpMoles*solids[j+1+i].mw;
                        }
                        (*solids[j].convert)(SECOND, THIRD, silminState->T, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
                        (*solids[j].display)(FIRST, silminState->T, silminState->P, r, &formula);
                        (*solids[j].gmix)   (FIRST, silminState->T, silminState->P, r, &gibbsEnergy,  NULL, NULL, NULL);
                        (*solids[j].hmix)   (FIRST, silminState->T, silminState->P, r, &enthalpy);
                        (*solids[j].smix)   (FIRST, silminState->T, silminState->P, r, &entropy,      NULL, NULL);
                        (*solids[j].vmix)   (FIRST, silminState->T, silminState->P, r, &volume,	      NULL, NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL);
                        (*solids[j].cpmix)  (FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
                        gibbsEnergy  *= tmpMoles;
                        enthalpy     *= tmpMoles;
                        entropy      *= tmpMoles;
                        volume       *= tmpMoles;
                        heatCapacity *= tmpMoles;
                        for (i=0; i<solids[j].na; i++) {
                            gibbsEnergy  += m[i]*(solids[j+1+i].cur).g;
                            enthalpy     += m[i]*(solids[j+1+i].cur).h;
                            entropy      += m[i]*(solids[j+1+i].cur).s;
                            volume       += m[i]*(solids[j+1+i].cur).v;
                            heatCapacity += m[i]*(solids[j+1+i].cur).cp;
                        }
                        totalMass	  += mass;
                        totalGibbsEnergy  += gibbsEnergy;
                        totalEnthalpy	  += enthalpy;
                        totalEntropy	  += entropy;
                        totalVolume	  += volume;
                        totalHeatCapacity += heatCapacity;

                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",		 "%s",   solids[j].label);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",	 "%s",   formula); free(formula);
                        rc = sprintf(temporary, "%23.16e", mass);         rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",		     "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", (volume == 0.0) ? 0.0 : mass/(10.0*volume)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density", "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", gibbsEnergy);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", enthalpy);     rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",        "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", entropy);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",         "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", volume*10.0);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",          "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", heatCapacity); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",	 "%s", temporary);

                        for (i=0, oxSum=0.0; i<nc; i++) {
                            int k;
                            for (k=0, oxVal[i]=0.0; k<solids[j].na; k++) oxVal[i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw;
                            oxSum += oxVal[i];
                        }
                        if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                        for (i=0; i<nc; i++) if (oxVal[i] != 0.0) {
                            rc = sprintf(temporary, "%23.16e", oxVal[i]*100.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%s", temporary);
                        }
                        for (i=0; i<solids[j].na; i++) {
                            rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name", 	  "%s",   solids[j+1+i].label);
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",  "%s",   solids[j+1+i].formula);
                            rc = sprintf(temporary, "%23.16e", m[i]/tmpMoles);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%s", temporary);
                            rc = xmlTextWriterEndElement(writer);
                        }
                    }

                    rc = xmlTextWriterEndElement(writer);
                }
            }
        }

        if (silminState->fractionateLiq) {
            double oxSum, mass, moles, gibbsEnergy, enthalpy, entropy, volume, heatCapacity;
            char *formula;

            for (i=0, mass=0.0, moles=0.0; i<nlc; i++) {
                double mw;
                double tmpMoles = (previousSilminState->fractionateLiq) ?
		              (silminState->fracLComp)[i] - (previousSilminState->fracLComp)[i] : (silminState->fracLComp)[i];
                for (j=0, mw = 0.0; j<nc; j++) mw += (liquid[i].liqToOx)[j]*bulkSystem[j].mw;
                m[i]   = tmpMoles;
                moles += m[i];
                mass  += tmpMoles*mw;
            }

            if (mass > 0.0) {
                rc = xmlTextWriterStartElement(writer, BAD_CAST "liquid");

                conLiq  (SECOND, THIRD, silminState->T, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL);
                dispLiq (FIRST, silminState->T, silminState->P, r, &formula);
                gmixLiq (FIRST, silminState->T, silminState->P, r, &gibbsEnergy,  NULL, NULL);
                hmixLiq (FIRST, silminState->T, silminState->P, r, &enthalpy,     NULL);
                smixLiq (FIRST, silminState->T, silminState->P, r, &entropy,      NULL, NULL, NULL);
                vmixLiq (FIRST, silminState->T, silminState->P, r, &volume,       NULL, NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL, NULL);
                cpmixLiq(FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
                gibbsEnergy  *= moles;
                enthalpy	 *= moles;
                entropy	 *= moles;
                volume	 *= moles;
                heatCapacity *= moles;
                for (i=0; i<nlc; i++) {
                    gibbsEnergy  += m[i]*(liquid[i].cur).g;
                    enthalpy     += m[i]*(liquid[i].cur).h;
                    entropy	   += m[i]*(liquid[i].cur).s;
                    volume	   += m[i]*(liquid[i].cur).v;
                    heatCapacity += m[i]*(liquid[i].cur).cp;
                }
                totalMass	      += mass;
                totalGibbsEnergy  += gibbsEnergy;
                totalEnthalpy     += enthalpy;
                totalEntropy      += entropy;
                totalVolume       += volume;
                totalHeatCapacity += heatCapacity;

                for (i=0, oxSum=0.0; i<nc; i++) {
                    for (j=0, oxVal[i]=0.0; j<nlc; j++) oxVal[i] += (liquid[j].liqToOx)[i]*m[j];
                    oxVal[i] *= bulkSystem[i].mw;
                    oxSum    += oxVal[i];
                }
                if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;

                rc = sprintf(temporary, "%23.16e", mass);         rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",	         "%s", temporary);
                rc = sprintf(temporary, "%23.16e", (volume == 0.0) ? 0.0 : mass/(10.0*volume)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density", "%s", temporary);
                rc = sprintf(temporary, "%23.16e", gibbsEnergy);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%s", temporary);
                rc = sprintf(temporary, "%23.16e", enthalpy);     rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	     "%s", temporary);
                rc = sprintf(temporary, "%23.16e", entropy);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	     "%s", temporary);
                rc = sprintf(temporary, "%23.16e", volume*10.0);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",	         "%s", temporary);
                rc = sprintf(temporary, "%23.16e", heatCapacity); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%s", temporary);

                for (i=0; i<nc; i++) if (oxVal[i] != 0.0) {
                    rc = sprintf(temporary, "%23.16e", oxVal[i]*100.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%s", temporary);
                }
                rc = xmlTextWriterEndElement(writer);
            }
        }

        rc = xmlTextWriterEndElement(writer);
    }

    if ( (previousSilminState->fractionateSol || previousSilminState->fractionateFlu || previousSilminState->fractionateLiq)
        && (previousSilminState->fracMass > 0.0) ) {
        rc = xmlTextWriterStartElement(writer, BAD_CAST "fractionate");
        rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "type", BAD_CAST "previous");
        rc = sprintf(temporary, "%23.16e", previousSilminState->fracMass); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", "%s", temporary);

        if (previousSilminState->fractionateSol || previousSilminState->fractionateFlu) {
            int haveWater = ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS));
            for (j=0; j<npc; j++) {
                int ns;

                if ( haveWater &&  previousSilminState->fractionateSol && !previousSilminState->fractionateFlu && !strcmp((char *) solids[j].label, "water")) continue;
                if ( haveWater && !previousSilminState->fractionateSol &&  previousSilminState->fractionateFlu &&  strcmp((char *) solids[j].label, "water")) continue;
                if (!haveWater &&  previousSilminState->fractionateSol && !previousSilminState->fractionateFlu && !strcmp((char *) solids[j].label, "fluid")) continue;
                if (!haveWater && !previousSilminState->fractionateSol &&  previousSilminState->fractionateFlu &&  strcmp((char *) solids[j].label, "fluid")) continue;

                for (ns=0; ns<(previousSilminState->nFracCoexist)[j]; ns++) {
                    double oxSum, mass, gibbsEnergy, enthalpy, entropy, volume, heatCapacity;

                    rc = xmlTextWriterStartElement(writer, BAD_CAST "solid");

                    if (solids[j].na == 1) {
                        mass		   = (previousSilminState->fracSComp)[j][ns]*solids[j].mw;
                        gibbsEnergy	   = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).g;
                        enthalpy	   = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).h;
                        entropy 	   = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).s;
                        volume  	   = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).v;
                        heatCapacity	   = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).cp;
                        totalMass	  += (previousSilminState->fracSComp)[j][ns]*solids[j].mw;
                        totalGibbsEnergy  += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).g;
                        totalEnthalpy	  += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).h;
                        totalEntropy	  += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).s;
                        totalVolume	  += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).v;
                        totalHeatCapacity += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).cp;

                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",		 "%s",   solids[j].label);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",	 "%s",   solids[j].formula);
                        rc = sprintf(temporary, "%23.16e", mass);         rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",	         "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", (volume == 0.0) ? 0.0 : mass/(10.0*volume)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density", "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", gibbsEnergy);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", enthalpy);     rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",        "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", entropy);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",         "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", volume*10.0);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",          "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", heatCapacity); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",	 "%s", temporary);

                        for (i=0, oxSum=0.0; i<nc; i++) {
                            oxVal[i]  = (solids[j].solToOx)[i]*bulkSystem[i].mw;
                            oxSum    += oxVal[i];
                        }
                        if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                        for (i=0; i<nc; i++) if (oxVal[i] != 0.0) {
                            rc = sprintf(temporary, "%23.16e", oxVal[i]*100.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%s", temporary);
                        }
                        rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",         "%s",   solids[j].label);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",      "%s",   solids[j].formula);
                        rc = sprintf(temporary, "%23.16e", 1.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%s", temporary);
                        rc = xmlTextWriterEndElement(writer);

                    } else {
                        char *formula;
                        for (i=0, mass=0.0; i<solids[j].na; i++) {
                            m[i] = (previousSilminState->fracSComp)[j+1+i][ns];
                            mass += (previousSilminState->fracSComp)[j+1+i][ns]*solids[j+1+i].mw;
                        }
                        (*solids[j].convert)(SECOND, THIRD, silminState->T, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
                        (*solids[j].display)(FIRST, silminState->T, silminState->P, r, &formula);
                        (*solids[j].gmix)   (FIRST, silminState->T, silminState->P, r, &gibbsEnergy,  NULL, NULL, NULL);
                        (*solids[j].hmix)   (FIRST, silminState->T, silminState->P, r, &enthalpy);
                        (*solids[j].smix)   (FIRST, silminState->T, silminState->P, r, &entropy,      NULL, NULL);
                        (*solids[j].vmix)   (FIRST, silminState->T, silminState->P, r, &volume,	      NULL, NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL);
                        (*solids[j].cpmix)  (FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
                        gibbsEnergy  *= (previousSilminState->fracSComp)[j][ns];
                        enthalpy     *= (previousSilminState->fracSComp)[j][ns];
                        entropy      *= (previousSilminState->fracSComp)[j][ns];
                        volume       *= (previousSilminState->fracSComp)[j][ns];
                        heatCapacity *= (previousSilminState->fracSComp)[j][ns];
                        for (i=0; i<solids[j].na; i++) {
                            gibbsEnergy  += m[i]*(solids[j+1+i].cur).g;
                            enthalpy     += m[i]*(solids[j+1+i].cur).h;
                            entropy      += m[i]*(solids[j+1+i].cur).s;
                            volume       += m[i]*(solids[j+1+i].cur).v;
                            heatCapacity += m[i]*(solids[j+1+i].cur).cp;
                        }
                        totalMass	  += mass;
                        totalGibbsEnergy  += gibbsEnergy;
                        totalEnthalpy	  += enthalpy;
                        totalEntropy	  += entropy;
                        totalVolume	  += volume;
                        totalHeatCapacity += heatCapacity;

                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",		 "%s",   solids[j].label);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",	 "%s",   formula); free(formula);
                        rc = sprintf(temporary, "%23.16e", mass);         rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",	         "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", (volume == 0.0) ? 0.0 : mass/(10.0*volume)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density", "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", gibbsEnergy);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", enthalpy);     rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",        "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", entropy);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",         "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", volume*10.0);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",          "%s", temporary);
                        rc = sprintf(temporary, "%23.16e", heatCapacity); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",	 "%s", temporary);

                        for (i=0, oxSum=0.0; i<nc; i++) {
                            int k;
                            for (k=0, oxVal[i]=0.0; k<solids[j].na; k++) oxVal[i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw;
                            oxSum += oxVal[i];
                        }
                        if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                        for (i=0; i<nc; i++) if (oxVal[i] != 0.0) {
                            rc =  sprintf(temporary, "%23.16e", oxVal[i]*100.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%s", temporary);
                        }
                        for (i=0; i<solids[j].na; i++) {
                            rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name", 	  "%s",   solids[j+1+i].label);
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",	  "%s",   solids[j+1+i].formula);
                            rc = sprintf(temporary, "%23.16e", m[i]/(previousSilminState->fracSComp)[j][ns]); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%s", temporary);
                            rc = xmlTextWriterEndElement(writer);
                        }
                    }

                    rc = xmlTextWriterEndElement(writer);
                }
            }
        }

        if (previousSilminState->fractionateLiq) {
            double oxSum, mass, moles, gibbsEnergy, enthalpy, entropy, volume, heatCapacity;
            char *formula;

            for (i=0, mass=0.0, moles=0.0; i<nlc; i++) {
                double mw;
                for (j=0, mw = 0.0; j<nc; j++) mw += (liquid[i].liqToOx)[j]*bulkSystem[j].mw;
                m[i]   = (previousSilminState->fracLComp)[i];
                moles += m[i];
                mass  += (previousSilminState->fracLComp)[i]*mw;
            }

            if (mass > 0.0) {
                rc = xmlTextWriterStartElement(writer, BAD_CAST "liquid");

                conLiq  (SECOND, THIRD, silminState->T, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL);
                dispLiq (FIRST, silminState->T, silminState->P, r, &formula);
                gmixLiq (FIRST, silminState->T, silminState->P, r, &gibbsEnergy,  NULL, NULL);
                hmixLiq (FIRST, silminState->T, silminState->P, r, &enthalpy,     NULL);
                smixLiq (FIRST, silminState->T, silminState->P, r, &entropy,      NULL, NULL, NULL);
                vmixLiq (FIRST, silminState->T, silminState->P, r, &volume,       NULL, NULL, NULL, NULL, NULL, NULL,  NULL, NULL, NULL, NULL);
                cpmixLiq(FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
                gibbsEnergy  *= moles;
                enthalpy	 *= moles;
                entropy	 *= moles;
                volume	 *= moles;
                heatCapacity *= moles;
                for (i=0; i<nlc; i++) {
                    gibbsEnergy  += m[i]*(liquid[i].cur).g;
                    enthalpy     += m[i]*(liquid[i].cur).h;
                    entropy	   += m[i]*(liquid[i].cur).s;
                    volume	   += m[i]*(liquid[i].cur).v;
                    heatCapacity += m[i]*(liquid[i].cur).cp;
                }
                totalMass	      += mass;
                totalGibbsEnergy  += gibbsEnergy;
                totalEnthalpy     += enthalpy;
                totalEntropy      += entropy;
                totalVolume       += volume;
                totalHeatCapacity += heatCapacity;

                for (i=0, oxSum=0.0; i<nc; i++) {
                    for (j=0, oxVal[i]=0.0; j<nlc; j++) oxVal[i] += (liquid[j].liqToOx)[i]*(previousSilminState->fracLComp)[j];
                    oxVal[i] *= bulkSystem[i].mw;
                    oxSum    += oxVal[i];
                }
                if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;

                rc = sprintf(temporary, "%23.16e", mass);         rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",           "%s", temporary);
                rc = sprintf(temporary, "%23.16e", (volume == 0.0) ? 0.0 : mass/(10.0*volume)); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density", "%s", temporary);
                rc = sprintf(temporary, "%23.16e", gibbsEnergy);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%s", temporary);
                rc = sprintf(temporary, "%23.16e", enthalpy);     rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	     "%s", temporary);
                rc = sprintf(temporary, "%23.16e", entropy);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	     "%s", temporary);
                rc = sprintf(temporary, "%23.16e", volume*10.0);  rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",	         "%s", temporary);
                rc = sprintf(temporary, "%23.16e", heatCapacity); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%s", temporary);

                for (i=0; i<nc; i++) if (oxVal[i] != 0.0) {
                    rc = sprintf(temporary, "%23.16e", oxVal[i]*100.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%s", temporary);
                }
                rc = xmlTextWriterEndElement(writer);
            }
        }

        rc = xmlTextWriterEndElement(writer);
    }

    rc = xmlTextWriterStartElement(writer, BAD_CAST "system");
    rc = sprintf(temporary, "%23.16e", mLiq+totalMass); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", "%s", temporary);
    rc = sprintf(temporary, "%23.16e", (vLiq+totalVolume == 0.0) ? 0.0 : (mLiq+totalMass)/(10.0*(vLiq+totalVolume)));
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density", "%s", temporary);

    if (vLiq > totalVolume) {
        rc = sprintf(temporary, "%23.16e", viscosity - 2.0*log10(1.0-2.0*totalVolume/(totalVolume+vLiq)));
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "viscosity", "%s", temporary);
    }
    rc = sprintf(temporary, "%23.16e", gLiq+totalGibbsEnergy);   rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%s", temporary);
    rc = sprintf(temporary, "%23.16e", hLiq+totalEnthalpy);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",        "%s", temporary);
    rc = sprintf(temporary, "%23.16e", sLiq+totalEntropy);       rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",         "%s", temporary);
    rc = sprintf(temporary, "%23.16e", (vLiq+totalVolume)*10.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",	        "%s", temporary);
    rc = sprintf(temporary, "%23.16e", cpLiq+totalHeatCapacity); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%s", temporary);
    rc = xmlTextWriterEndElement(writer);

    if (silminState->fo2Path != FO2_NONE) {
        double mO2 = -silminState->oxygen;
        int nl, ns;
        for (nl=0; nl<silminState->nLiquidCoexist; nl++) for (i=0; i<nlc; i++) mO2 += (oxygen.liqToOx)[i]*(silminState->liquidComp)[nl][i];
        for (i=0; i<npc; i++) for (ns=0; ns<(silminState->nSolidCoexist)[i]; ns++) {
            if (solids[i].na == 1) mO2 += (oxygen.solToOx)[i]*(silminState->solidComp)[i][ns];
            else {
                for (j=0; j<solids[i].na; j++) mO2 += (oxygen.solToOx)[i+1+j]*(silminState->solidComp)[i+1+j][ns];
            }
        }
        rc = xmlTextWriterStartElement(writer, BAD_CAST "oxygen");
        rc = sprintf(temporary, "%23.16e", mO2);                     rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moles",	        "%s", temporary);
        rc = sprintf(temporary, "%23.16e", mO2*31.9988);             rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",	        "%s", temporary);
        rc = sprintf(temporary, "%23.16e", mO2*(oxygen.cur).g);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%s", temporary);
        rc = sprintf(temporary, "%23.16e", mO2*(oxygen.cur).h);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",        "%s", temporary);
        rc = sprintf(temporary, "%23.16e", mO2*(oxygen.cur).s);      rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",         "%s", temporary);
        rc = sprintf(temporary, "%23.16e", mO2*10.0*(oxygen.cur).v); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",	        "%s", temporary);
        rc = sprintf(temporary, "%23.16e", mO2*(oxygen.cur).cp);     rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%s", temporary);
        rc = xmlTextWriterEndElement(writer);
    }

    if (silminState->assimilate) {
        int ns;
        rc = xmlTextWriterStartElement(writer, BAD_CAST "assimilant");
        rc = sprintf(temporary, "%23.16e", silminState->assimMass); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",	    "%s", temporary);
        rc = sprintf(temporary, "%23.16e", silminState->assimT); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "temperature", "%s", temporary);

        for (j=0; j<npc; j++) if (solids[j].type == PHASE)
            for (ns=0; ns<(silminState->nAssimComp)[j]; ns++) {
                rc = xmlTextWriterStartElement(writer, BAD_CAST "solid");
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name", "%s", solids[j].label);
                if (solids[j].na == 1) {
                    double mass = (silminState->assimComp)[j][ns]*solids[j].mw*silminState->assimMass/silminState->dspAssimMass;
                    rc = sprintf(temporary, "%23.16e", mass); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", "%s", temporary);
                    rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",         "%s",   solids[j].label);
                    rc = sprintf(temporary, "%23.16e", 1.0); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%s", temporary);
                    rc = xmlTextWriterEndElement(writer);

                } else {
                    double mass = 0.0;
                    for (i=0; i<solids[j].na; i++) mass += (silminState->assimComp)[j+1+i][ns]*solids[j+1+i].mw;
                    mass *= silminState->assimMass/silminState->dspAssimMass;
                    rc = sprintf(temporary, "%23.16e", mass); rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", "%s", temporary);

                    for (i=0; i<solids[j].na; i++) {
                        rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",    "%s", solids[j+1+i].label);
                        rc = sprintf(temporary, "%23.16e", (silminState->assimComp)[j+1+i][ns]/(silminState->assimComp)[j][ns]);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "molFrac", "%s", temporary);
                        rc = xmlTextWriterEndElement(writer);
                    }

                }
                rc = xmlTextWriterEndElement(writer);
            }
        rc = xmlTextWriterEndElement(writer);
    }

    rc = xmlTextWriterEndDocument(writer);
    xmlFreeTextWriter(writer);
    free (temporary);
}

static void putStatusDataToXmlFile(char *statusFile) {
    xmlTextWriterPtr writer;
    int rc;
    const static char *m[] = {
        "Success: Find liquidus",                                  /* LIQUIDUS_SUCCESS	 */
        "Error: Maximum temperature in Find Liquidus",             /* LIQUIDUS_MAX_T	 */
        "Error: Minimum temperature in Find Liquidus",             /* LIQUIDUS_MIN_T	 */
        "Error: Maximum time limit exceeded in Find Liquidus",     /* LIQUIDUS_TIME 	 */
        "Error: Cannot specify multiple liquids in Find Liquidus", /* LIQUIDUS_MULTIPLE      */
        "Success: Equilibrate",                                    /* SILMIN_SUCCESS	 */
        "Error: Quadratic Iterations exceeded",                    /* SILMIN_QUAD_MAX	 */
        "Error: Zero steplength computed in linear search",        /* SILMIN_LIN_ZERO	 */
        "Error: Maximum iterations exceeded in linear search",     /* SILMIN_LIN_MAX	 */
        "Error: Cannot add a solid phase to liquid(+solids)",      /* SILMIN_ADD_LIQUID_1	 */
        "Error: Cannot add a solid phase to solid(s)",             /* SILMIN_ADD_LIQUID_2	 */
        "Error: Cannot add a liquid phase to solid(s)",            /* SILMIN_ADD_LIQUID_3	 */
        "Error: Phase rule violation (rank deficiency)",           /* SILMIN_RANK		 */
        "Error: Maximum time limit exceeded in Silmin",            /* SILMIN_TIME		 */
        "Error: Internal",                                         /* GENERIC_INTERNAL_ERROR */
        "Error: Failure in equilibration in Find Wet Liquidus",   /* LIQUIDUS_SILMIN_ERROR */
    };

    printf("Output file name is %s\n", statusFile);

    writer = xmlNewTextWriterFilename(statusFile, 0);
    rc = xmlTextWriterStartDocument(writer, NULL, "UTF-8", NULL);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "MELTSstatus", "%s", m[meltsStatus.status]);
    rc = xmlTextWriterEndDocument(writer);
    xmlFreeTextWriter(writer);
}

static void doBatchFractionation(void) {
    int i, j, k, ns, nl;
    int hasLiquid = ((silminState != NULL) && (silminState->liquidMass != 0.0));

    /* Solid Phase Fractionation */
    if ((silminState->fractionateSol || silminState->fractionateFlu) && !hasLiquid) fprintf(stderr, "...Cannot do solid/fluid fractionation without a liquid phase.\n");

    if ((silminState->fractionateSol || silminState->fractionateFlu) && hasLiquid) {
        double *m = (double *) malloc((size_t) nlc*sizeof(double));
        double *r = (double *) malloc((size_t) nlc*sizeof(double));
        for (i=0; i<npc; i++) if (solids[i].type == PHASE) {
            if ((silminState->nSolidCoexist)[i] > (silminState->nFracCoexist)[i]) {
                int ns = (silminState->nSolidCoexist)[i];
                int nf = (silminState->nFracCoexist)[i];
                (silminState->nFracCoexist)[i] = ns;
                if (nf == 0) {
                    (silminState->fracSComp)[i] = (double *) calloc((size_t) ns, sizeof(double));
                    if (solids[i].na > 1) for (j=0; j<solids[i].na; j++) (silminState->fracSComp)[i+1+j] = (double *) calloc((size_t) ns, sizeof(double));
                } else {
                    (silminState->fracSComp)[i] = (double *) REALLOC((silminState->fracSComp)[i], (size_t) ns*sizeof(double));
                    for (j=nf; j<ns; j++) (silminState->fracSComp)[i][j] = 0.0;
                    if (solids[i].na > 1) for (j=0; j<solids[i].na; j++) {
                        (silminState->fracSComp)[i+1+j] = (double *) REALLOC((silminState->fracSComp)[i+1+j], (size_t) ns*sizeof(double));
                        for (k=nf; k<ns; k++) (silminState->fracSComp)[i+1+j][k] = 0.0;
                    }
                }
            }
        }
	int haveWater = ((calculationMode == MODE__MELTS) || (calculationMode == MODE_pMELTS));
        for (i=0; i<npc; i++) {
	    if ( haveWater &&  silminState->fractionateSol && !silminState->fractionateFlu && !strcmp((char *) solids[i].label, "water")) continue;
	    if ( haveWater && !silminState->fractionateSol &&  silminState->fractionateFlu &&  strcmp((char *) solids[i].label, "water")) continue;
	    if (!haveWater &&  silminState->fractionateSol && !silminState->fractionateFlu && !strcmp((char *) solids[i].label, "fluid")) continue;
	    if (!haveWater && !silminState->fractionateSol &&  silminState->fractionateFlu &&  strcmp((char *) solids[i].label, "fluid")) continue;
            for (ns=0; ns<(silminState->nSolidCoexist)[i]; ns++) {
                if ((silminState->solidComp)[i][ns] < MASSIN) continue;
                if (solids[i].na == 1) {
                    (silminState->fracSComp)[i][ns] += (silminState->solidComp)[i][ns]-MASSIN;
                    if (silminState->fo2Path != FO2_NONE) silminState->oxygen -= (oxygen.solToOx)[i]*((silminState->solidComp)[i][ns]-MASSIN);
                    silminState->fracMass += ((silminState->solidComp)[i][ns]-MASSIN)*solids[i].mw;
                    for (j=0; j<nc; j++) (silminState->bulkComp)[j] -= (solids[i].solToOx)[j]*((silminState->solidComp)[i][ns]-MASSIN);

                    /* Subtract off H, S or V if appropriate                          */
                    if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0))
                        silminState->refEnthalpy -= ((silminState->solidComp)[i][ns]-MASSIN)*(solids[i].cur).h;
                    if (silminState->isentropic && (silminState->refEntropy != 0.0))
                        silminState->refEntropy -= ((silminState->solidComp)[i][ns]-MASSIN)*(solids[i].cur).s;
                    if (silminState->isochoric && (silminState->refVolume != 0.0))
                        silminState->refVolume -= ((silminState->solidComp)[i][ns]-MASSIN)*(solids[i].cur).v;

                    (silminState->solidComp)[i][ns] = MASSIN;
                } else {
                    double moleF, totalMoles=0.0;
                    (silminState->fracSComp)[i][ns] += (silminState->solidComp)[i][ns] - MASSIN;
                    for (j=0; j<solids[i].na; j++) {
                        moleF = (silminState->solidComp)[i+1+j][ns]/(silminState->solidComp)[i][ns];
                        m[j] = (silminState->solidComp)[i+1+j][ns] - MASSIN*moleF;
                        totalMoles += m[j];
                        (silminState->fracSComp)[i+1+j][ns] += m[j];
                        if (silminState->fo2Path != FO2_NONE) silminState->oxygen -= (oxygen.solToOx)[i+1+j]*m[j];
                        silminState->fracMass += m[j]*solids[i+1+j].mw;
                        for (k=0; k<nc; k++) (silminState->bulkComp)[k] -= (solids[i+1+j].solToOx)[k]*m[j];
                        (silminState->solidComp)[i+1+j][ns] = MASSIN*moleF;

                        /* Subtract off H, S or V if appropriate                        */
                        if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0)) silminState->refEnthalpy -= m[j]*(solids[i+1+j].cur).h;
                        if (silminState->isentropic && (silminState->refEntropy != 0.0))   silminState->refEntropy  -= m[j]*(solids[i+1+j].cur).s;
                        if (silminState->isochoric && (silminState->refVolume != 0.0))     silminState->refVolume   -= m[j]*(solids[i+1+j].cur).v;
                    }
                    (silminState->solidComp)[i][ns] = MASSIN;

                    /* Subtract off H, S or V if appropriate                          */
                    if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0)) {
                        double enthalpy;
                        (*solids[i].convert)(SECOND, THIRD, silminState->T,silminState->P, NULL, m, r, NULL,  NULL, NULL, NULL, NULL);
                        (*solids[i].hmix)(FIRST, silminState->T, silminState->P, r, &enthalpy);
                        silminState->refEnthalpy -= totalMoles*enthalpy;
                    }
                    if (silminState->isentropic && (silminState->refEntropy != 0.0)) {
                        double entropy;
                        (*solids[i].convert)(SECOND, THIRD,silminState->T,silminState->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
                        (*solids[i].smix)(FIRST, silminState->T, silminState->P, r, &entropy, (double *) NULL, (double **) NULL);
                        silminState->refEntropy  -= totalMoles*entropy;
                    }
                    if (silminState->isochoric && (silminState->refVolume != 0.0)) {
                        double volume;
                        (*solids[i].convert)(SECOND, THIRD, silminState->T,silminState->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
                        (*solids[i].vmix)(FIRST, silminState->T, silminState->P, r, &volume, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
                        silminState->refVolume   -= totalMoles*volume;
                    }

                }
            }
        }

        for (i=0; i<nc; i++) {
            if ((silminState->bulkComp)[i] != 0.0 && (silminState->bulkComp)[i] <  MASSOUT && bulkSystem[i].type != FE2O3) {
                fprintf(stderr, "  Moles of %5.5s in system (%g) < %g\n.", bulkSystem[i].label, (silminState->bulkComp)[i], MASSOUT);
                (silminState->bulkComp)[i] = 0.0;
                for (j=0; j<nlc; j++) if ((liquid[j].liqToOx)[i] != 0.0) {
                    for (nl=0; nl<silminState->nLiquidCoexist; nl++) (silminState->liquidComp)[nl][j] = 0.0;
                    fprintf(stderr, "    Moles of %s in liquid(s) set to zero.\n", liquid[j].label);
                }
                for (j=0; j<npc; j++) {
                    for (ns=0; ns<(silminState->nSolidCoexist)[j]; ns++) {
                        if (solids[j].na == 1) {
                            if ((solids[j].solToOx)[i] != 0.0) {
                                (silminState->solidComp)[j][ns] = 0.0;
                                fprintf(stderr, "    Moles of %s in solid set to zero.\n", solids[j].label);
                            }
                        } else {
                            for (k=0; k<solids[j].na; k++) {
                                if ((solids[j+1+k].solToOx)[i] != 0.0) {
                                    (silminState->solidComp)[j][ns] -= (silminState->solidComp)[j+1+k][ns];
                                    (silminState->solidComp)[j+1+k][ns] = 0.0;
                                    fprintf(stderr, "    Moles of %s in %s solid set to zero.\n", solids[j+1+k].label, solids[j].label);
                                }
                            }
                        }
                    }
                }
            }
        }
        free(m);
        free(r);
    }

    /* Liquid Phase Fractionation */
    if (silminState->fractionateLiq && !hasLiquid) fprintf(stderr, "...Cannot do liquid fractionation without a liquid phase.\n");

    if (silminState->fractionateLiq && hasLiquid) {
        double *m = (double *) malloc((size_t) nlc*sizeof(double));
        double *r = (double *) malloc((size_t) nlc*sizeof(double));
        for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
            double refMoles, totalMoles;
            for (i=0, refMoles=0.0; i<nlc; i++) refMoles += (silminState->liquidComp)[nl][i];
            if (refMoles < MASSIN) continue;

            for (i=0, totalMoles=0.0; i<nlc; i++) {
                if (((silminState->liquidComp)[nl][i] != 0.0) && (refMoles != 0.0)) {
                    double mw;
                    double moleF = (silminState->liquidComp)[nl][i]/refMoles;

                    for (j=0, mw = 0.0; j<nc; j++) mw += (liquid[i].liqToOx)[j]*bulkSystem[j].mw;
                    m[i] = (silminState->liquidComp)[nl][i] - MASSIN*moleF;
                    totalMoles += m[i];
                    (silminState->fracLComp)[i] += m[i];
                    if (silminState->fo2Path != FO2_NONE) silminState->oxygen -= (oxygen.liqToOx)[i]*m[i];
                    silminState->fracMass += m[i]*mw;
                    for (j=0; j<nc; j++) (silminState->bulkComp)[j] -= (liquid[i].liqToOx)[j]*m[i];
                    (silminState->liquidComp)[nl][i] = MASSIN*moleF;

                    /* Subtract off H, S or V if appropriate			    */
                    if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0)) silminState->refEnthalpy -= m[i]*(liquid[i].cur).h;
                    if (silminState->isentropic  && (silminState->refEntropy  != 0.0)) silminState->refEntropy  -= m[i]*(liquid[i].cur).s;
                    if (silminState->isochoric   && (silminState->refVolume   != 0.0)) silminState->refVolume	-= m[i]*(liquid[i].cur).v;
                } else m[i] = 0.0;
            }

            /* Subtract off H, S or V if appropriate			  */
            if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0)) {
                double enthalpy;
                conLiq (SECOND, THIRD, silminState->T,silminState->P, NULL, m, r, NULL,  NULL, NULL, NULL);
                hmixLiq(FIRST, silminState->T, silminState->P, r, &enthalpy, NULL);
                silminState->refEnthalpy -= totalMoles*enthalpy;
            }
            if (silminState->isentropic && (silminState->refEntropy != 0.0)) {
                double entropy;
                conLiq (SECOND, THIRD,silminState->T,silminState->P, NULL, m, r, NULL, NULL, NULL, NULL);
                smixLiq(FIRST, silminState->T, silminState->P, r, &entropy, NULL, NULL, NULL);
                silminState->refEntropy  -= totalMoles*entropy;
            }
            if (silminState->isochoric && (silminState->refVolume != 0.0)) {
                double volume;
                conLiq (SECOND, THIRD, silminState->T,silminState->P, NULL, m, r, NULL, NULL, NULL, NULL);
                vmixLiq(FIRST, silminState->T, silminState->P, r, &volume, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
                silminState->refVolume   -= totalMoles*volume;
            }

        }

        for (i=0; i<nc; i++) {
            if ((silminState->bulkComp)[i] != 0.0 && (silminState->bulkComp)[i] <  MASSOUT && bulkSystem[i].type != FE2O3) {
                fprintf(stderr, "  Moles of %5.5s in system (%g) < %g\n.", bulkSystem[i].label, (silminState->bulkComp)[i], MASSOUT);
                (silminState->bulkComp)[i] = 0.0;
                for (j=0; j<nlc; j++) if ((liquid[j].liqToOx)[i] != 0.0) {
                    for (nl=0; nl<silminState->nLiquidCoexist; nl++) (silminState->liquidComp)[nl][j] = 0.0;
                    fprintf(stderr, "    Moles of %s in liquid(s) set to zero.\n", liquid[j].label);
                }
                for (j=0; j<npc; j++) {
                    for (ns=0; ns<(silminState->nSolidCoexist)[j]; ns++) {
                        if (solids[j].na == 1) {
                            if ((solids[j].solToOx)[i] != 0.0) {
                                (silminState->solidComp)[j][ns] = 0.0;
                                fprintf(stderr, "    Moles of %s in solid set to zero.\n", solids[j].label);
                            }
                        } else {
                            for (k=0; k<solids[j].na; k++) {
                                if ((solids[j+1+k].solToOx)[i] != 0.0) {
                                    (silminState->solidComp)[j][ns] -= (silminState->solidComp)[j+1+k][ns];
                                    (silminState->solidComp)[j+1+k][ns] = 0.0;
                                    fprintf(stderr, "    Moles of %s in %s solid set to zero.\n", solids[j+1+k].label, solids[j].label);
                                }
                            }
                        }
                    }
                }
            }
        }
        free(m);
        free(r);
    }
}

#endif /* BATCH_VERSION */

/*****************/
/* MAIN FUNCTION */
/****************/

static void chomp(char *s) {
    while(*s && *s != '\n' && *s != '\r') s++;
    *s = 0;
}

int main (int argc, char *argv[])
{
#ifndef BATCH_VERSION
    XtAppContext app;
    Pixmap icon_pixmap;
#endif

    printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");
    printf("%s\n", RELEASE);
    printf("<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>\n");

#ifndef BATCH_VERSION
    printf("---> Reading environment variables...\n");
    getCommandLineAndEnvironment (argc, argv);
#endif

    printf("<><> There are three releases of rhyolite-MELTS and a version of pMELTS included in this package:\n");
    printf("     (*) rhyolite-MELTS v. 1.0.2 (original version, with corrections) - old H2O model, no mixed fluids.\n");
    printf("     (*) rhyolite-MELTS v, 1.1.0 (mixed fluid version that perserves the ternary minimum) - old H2O model.\n");
    printf("     (*) rhyolite-MELTS v. 1.2.0 (mixed fluid version optimal for mafic and alkalic melts) - new H2O model.\n");
    printf("     (*) pMELTS v. 5.6.1 (original version, with corrections) - - old H2O model, no mixed fluids.\n");
    printf("<><> Visit the website melts.ofm-research.org for information on which version to use for your application.\n");
#ifdef PUBLIC_RELEASE_VERSION
    calculationMode = MODE__MELTS;
#ifdef RHYOLITE_ADJUSTMENTS
    printf("---> Default calculation mode is rhyolite-MELTS (v. 1.0.2).  Change this? (y or n): ");
#else
    printf("---> Default calculation mode is MELTS (original).  Change this? (y or n): ");
#endif
    if (tolower(getchar()) == 'y') {
        getchar();
        printf("     Set calculation mode to rhyolite-MELTS (public release v 1.1.0)? (y or n): ");
        if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE__MELTSandCO2; }
        else {
            getchar();
            printf("     Set calculation mode to rhyolite-MELTS (public release v 1.2.0)? (y or n): ");
            if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE__MELTSandCO2_H2O; }
            else {
                getchar();
                printf("     Set calculation mode to pMELTS (public release v 5.6.1)? (y or n): ");
                if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE_pMELTS; }
                else { getchar(); exit(0); }
            }
        }
    } else getchar();
#elif ! defined(BATCH_VERSION)
    printf("---> Default calculation mode is xMELTS.  Change this? (y or n): ");
    if (tolower(getchar()) == 'y') {
        getchar();
        printf("     Set calculation mode to rhyolite-MELTS (public release v 1.0.2)? (y or n): ");
        if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE__MELTS; }
        else {
            getchar();
            printf("     Set calculation mode to rhyolite-MELTS (public release v 1.1.0)? (y or n): ");
            if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE__MELTSandCO2; }
            else {
                getchar();
                printf("     Set calculation mode to rhyolite-MELTS (public release v 1.2.0)? (y or n): ");
                if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE__MELTSandCO2_H2O; }
                else {
                    getchar();
                    printf("     Set calculation mode to pMELTS (public release v 5.6.1)? (y or n): ");
                    if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE_pMELTS; }
                    else { getchar(); exit(0); }
                }
            }
        }
    } else getchar();
#else
#ifdef V102
    calculationMode = MODE__MELTS;
    printf("---> Default calculation mode is rhyolite-MELTS (v. 1.0.2) for batch processing.\n");
#elif defined(V110)
    calculationMode = MODE__MELTSandCO2;
    printf("---> Default calculation mode is rhyolite-MELTS (v. 1.1.0) for batch processing.\n");
#elif defined(V120)
    calculationMode = MODE__MELTSandCO2_H2O;
    printf("---> Default calculation mode is rhyolite-MELTS (v. 1.2.0) for batch processing.\n");
#else
    calculationMode = MODE_pMELTS;
    printf("---> Default calculation mode is pMELTS (v 5.6.1) for batch processing.\n");
#endif
#endif

#ifndef BATCH_VERSION

    if (calculationMode == MODE_xMELTS) {
        printf("---> Calculation mode is xMELTS (experimental v 2.0.0).\n");
    } else if ((calculationMode == MODE__MELTS) ||
               (calculationMode == MODE__MELTSandCO2) ||
               (calculationMode == MODE__MELTSandCO2_H2O) ){
#ifdef RHYOLITE_ADJUSTMENTS
                                                           printf("---> ************************************************************\n");
        if      (calculationMode == MODE__MELTS)           printf("---> Calculation mode is rhyolite-MELTS (public release v 1.0.2).\n");
        else if (calculationMode == MODE__MELTSandCO2)     printf("---> Calculation mode is rhyolite-MELTS (public release v 1.1.0).\n");
        else if (calculationMode == MODE__MELTSandCO2_H2O) printf("---> Calculation mode is rhyolite-MELTS (public release v 1.2.0).\n");
                                                           printf("---> ************************************************************\n");
#else
        printf("---> ***************************************************\n");
        printf("---> Calculation mode is MELTS (public release v 5.6.1).\n");
        printf("---> ***************************************************\n");
#endif
        if (calculationMode == MODE__MELTS) {
            liquid = meltsLiquid;
            solids = meltsSolids;
            nlc = meltsNlc;
            nls = meltsNls;
            npc = meltsNpc;
        } else if ((calculationMode == MODE__MELTSandCO2) || (calculationMode == MODE__MELTSandCO2_H2O)) {
            liquid = meltsFluidLiquid;
            solids = meltsFluidSolids;
            nlc = meltsFluidNlc;
            nls = meltsFluidNls;
            npc = meltsFluidNpc;
        }

    } else if (calculationMode == MODE_pMELTS) {
        printf("---> ****************************************************\n");
        printf("---> Calculation mode is pMELTS (public release v 5.6.1).\n");
        printf("---> ****************************************************\n");
        liquid = pMeltsLiquid;
        solids = pMeltsSolids;
        nlc = pMeltsNlc;
        nls = pMeltsNls;
        npc = pMeltsNpc;
    }

    printf("---> Initializing data structures using selected calculation mode...\n");
    InitComputeDataStruct();
# else
    /* Move initialization later for BATCH_VERSION so models can be selected via XML */
    /* Select temporary values for nlc, nls, and npc so can allocate silminState safely */
    if (calculationMode == MODE__MELTS) {
        liquid = meltsLiquid;
        solids = meltsSolids;
        nlc = meltsNlc;
        nls = meltsNls;
        npc = meltsNpc;
    } else if ((calculationMode == MODE__MELTSandCO2) || (calculationMode == MODE__MELTSandCO2_H2O)) {
        liquid = meltsFluidLiquid;
        solids = meltsFluidSolids;
        nlc = meltsFluidNlc;
        nls = meltsFluidNls;
        npc = meltsFluidNpc;
    } else if (calculationMode == MODE_pMELTS) {
        liquid = pMeltsLiquid;
        solids = pMeltsSolids;
        nlc = pMeltsNlc;
        nls = pMeltsNls;
        npc = pMeltsNpc;
    }
#endif

#ifndef BATCH_VERSION
    printf("---> Building interface...\n");
    /*
     *=============================================================================
     * (1) Install signal error handler for child process control
     * (2) Set language locale
     */
    signal (SIGCHLD, signalDeathOfChild);
    if (atexit (killChildren)) printf ("Cannot register exit cleanup routine.\n");
#if XtSpecificationRelease >= 5
    XtSetLanguageProc (NULL, NULL, NULL);
#endif

    /*
     *=============================================================================
     * (1) Create the topLevel shell widget
     * (2) Get needed display information
     */
    topLevel = XtVaAppInitialize (&app, "Melts", (XrmOptionDescList) NULL, (Cardinal) 0,
#if XtSpecificationRelease == 4
                                  (Cardinal *) & argc,
#else
                                  &argc,
#endif
                                  argv, (String *) NULL, NULL);
    icon_pixmap = XCreateBitmapFromData (XtDisplay (topLevel), RootWindowOfScreen (XtScreen (topLevel)), icon_bits, icon_width, icon_height);
    if      (calculationMode == MODE__MELTS)
#ifdef RHYOLITE_ADJUSTMENTS
        XtVaSetValues (topLevel, XmNiconPixmap, icon_pixmap, XmNtitle, "rhyolite-MELTS (code release 1.0.2)",  XmNiconName, "Melts",  NULL);
#else
        XtVaSetValues (topLevel, XmNiconPixmap, icon_pixmap, XmNtitle, "MELTS (code release 5.6.1)",  XmNiconName, "Melts",  NULL);
#endif
    else if (calculationMode == MODE__MELTSandCO2)
        XtVaSetValues (topLevel, XmNiconPixmap, icon_pixmap, XmNtitle, "rhyolite-MELTS+CO2+old-H2O (code release 1.1.0)",  XmNiconName, "Melts",  NULL);
    else if (calculationMode == MODE__MELTSandCO2_H2O)
        XtVaSetValues (topLevel, XmNiconPixmap, icon_pixmap, XmNtitle, "rhyolite-MELTS+CO2+new-H2O (code release 1.2.0)",  XmNiconName, "Melts",  NULL);
    else if (calculationMode == MODE_pMELTS)
        XtVaSetValues (topLevel, XmNiconPixmap, icon_pixmap, XmNtitle, "pMELTS (code release 5.6.1)", XmNiconName, "pMelts", NULL);
    else if (calculationMode == MODE_xMELTS)
        XtVaSetValues (topLevel, XmNiconPixmap, icon_pixmap, XmNtitle, "xMELTS (code release 2.0.0)", XmNiconName, "xMelts", NULL);

    printf("---> ...Call to initialize_colors ()...\n");
    initialize_colors ();
    printf("---> ...Call to initialize_strings ()...\n");
    initialize_strings ();

    /*
     *=============================================================================
     *  (1) Create a Main Window Widget to hold everything
     */
    printf("---> ...Create main window...\n");
    main_window = XtVaCreateWidget ("MainWin", xmMainWindowWidgetClass, topLevel,
                                    XmNwidth,  MAIN_WINDOW_WIDTH,
                                    XmNheight, MAIN_WINDOW_HEIGHT,
                                    NULL);

    /*
     *============================================================================
     * Create menu bar and all its sub-menus. This menu bar applies to all the
     *   defined work windows.
     */
    printf("---> ...Create menu bar...\n");
    create_menu_bar ();
    if (calculationMode != MODE_xMELTS) XtSetSensitive(mode_entry, FALSE);

    /*
     *=============================================================================
     * Create the work window portion of the main window
     *   The main window is filled on startup by an attached dialog box widget
     *   (silmin_adb) which has visible (managed) children created by the
     *   function create_managed and invisible (unmanaged) pop up children
     *   created by the functions create_popup_table
     * Alternative work windows are:
     *   preclb_adb -  an attached dialog box widget for the pre-calibration setup
     *   postclb_adb - an attached dialog box widget for the post-calibration
     *                 analysis
     */
    printf("---> ...Create work window...\n");
    silmin_adb = XmCreateForm (main_window, "silmin_adb", NULL, 0);
    XtVaSetValues (main_window, XmNworkWindow, silmin_adb, NULL);

    printf("---> ...Call to create_managed ()...\n");
    create_managed ();		/* of silmin_adb */
    printf("---> ...Call to create_unmanaged ()...\n");
    create_unmanaged ();		/* children of the main window widget        */
    /* These are the caution box, file selection */
    /*   message and help widgets.               */

    /*
     * Now manage the silmin_adb widget and its parent (main_window).
     */
    printf("---> ...Manage children...\n");
    XtManageChild (silmin_adb);
    printf("---> ...Manage parent...\n");
    XtManageChild (main_window);

    /*
     *=============================================================================
     * Realize the Shell widget (and hence all its children)
     */
    printf("---> ...Realize parent...\n");
    XtRealizeWidget (topLevel);

    /*
     *=============================================================================
     * Get events
     */

    printf("---> Ready for user input...\n");
#if defined(DEBUG)
    debugMainLoop (app);
#else
    XtAppMainLoop (app);
#endif

#elif !defined(EASYMELTS_UPDATE_SYSTEM) /* BATCH_VERSION */
    {
        if (argc == 1) {
            printf("Usage:\n");
            printf("  Melts-batch input.melts\n");
            printf("  Melts-batch input.xml\n");
#ifdef DEBUG
            printf("  Melts-batch input.txt\n");
#endif
            printf("  Melts-batch inputDir outputDir [inputProcessedDir]\n");
            printf("              Directories are stipulated relative to current directory\n");
            printf("              with no trailing delimiter.\n");
            exit(0);

        } else if (strstr(argv[1], ".melts") != NULL) {
            int i, j, k, l;

            printf("---> Initializing data structures using selected calculation mode...\n");
            SelectComputeDataStruct();
            InitComputeDataStruct();

            if (silminState == NULL) silminState = allocSilminStatePointer();

            if(!batchInputDataFromFile(argv[1])) {
                printf("Error(s) detected on reading input file %s. Exiting.\n", argv[1]);
                exit(0);
            }

            if (argc > 2) {
                printf("Press any key to continue.\n");
                getchar();
                getchar();
            }

            if ((argc == 2) || !strncmp(argv[2], "liquidus", 8)) { // default is find liquidus followed by equilibrate
                int fractionateSol = silminState->fractionateSol, fractionateFlu = silminState->fractionateFlu,
                    fractionateLiq = silminState->fractionateLiq;
                silminState->fractionateSol = FALSE;
                silminState->fractionateFlu = FALSE;
                silminState->fractionateLiq = FALSE;

                while(!liquidus());
                printf("Liquidus temperature is: %f\n", silminState->T-273.15); silminState->dspTstart = silminState->T;
                (void) putOutputDataToFile(NULL);

                silminState->fractionateSol = fractionateSol;
                silminState->fractionateFlu = fractionateFlu;
                silminState->fractionateLiq = fractionateLiq;
            }
            else if (!strncmp(argv[2], "wetliquidus", 11)) {
                int fractionateSol = silminState->fractionateSol, fractionateFlu = silminState->fractionateFlu,
                    fractionateLiq = silminState->fractionateLiq;
                silminState->fractionateSol = FALSE;
                silminState->fractionateFlu = FALSE;
                silminState->fractionateLiq = FALSE;

                (void) findWetLiquidus();
                printf("Liquidus temperature is: %f\n", silminState->T-273.15); silminState->dspTstart = silminState->T;
                (void) putOutputDataToFile(NULL);

                silminState->fractionateSol = fractionateSol;
                silminState->fractionateFlu = fractionateFlu;
                silminState->fractionateLiq = fractionateLiq;
            }
            if ((argc == 2) || !strncmp(argv[2], "equilibrate", 11)) {
                if ((silminState->fractionateSol || silminState->fractionateFlu) && silminState->fracSComp == (double **) NULL) {
                    silminState->fracSComp    = (double **) calloc((unsigned) npc, sizeof(double *));
                    silminState->nFracCoexist = (int *) calloc((unsigned) npc, sizeof(int));
                }
                if (silminState->fractionateLiq && silminState->fracLComp == (double *) NULL) {
                    silminState->fracLComp = (double *) calloc((unsigned) nlc, sizeof(double));
                }
                while(!silmin());
            }

            for (i=0; i<npc; i++) if (solids[i].type == PHASE) {
                if ((silminState->nSolidCoexist)[i] > 0) {
                    for (j=0; j<(silminState->nSolidCoexist)[i]; j++) {
                        double phaseMoles, phaseGrams;

                        if (solids[i].na == 1) {
                            phaseMoles   = (silminState->solidComp)[i][j];
                            for (l=0, phaseGrams=0.0; l<nc; l++) {
                                phaseGrams += phaseMoles*(solids[i].solToOx)[l]*bulkSystem[l].mw;
                            }

                            printf("Got phase %s with moles %f and grams %f\n", solids[i].label, phaseMoles, phaseGrams);

                        } else {
                            char *formula;
                            double *r      = (double *) malloc((size_t) solids[i].nr *sizeof(double));
                            double *phaseX = (double *) malloc((size_t) solids[i].na *sizeof(double));

                            for (k=0, phaseGrams=0.0, phaseMoles=0.0; k<solids[i].na; k++) {
                                phaseX[k]   = (silminState->solidComp)[i+1+k][j];
                                phaseMoles += (silminState->solidComp)[i+1+k][j];
                                for (l=0; l<nc; l++) phaseGrams += phaseX[k]*(solids[i+1+k].solToOx)[l]*bulkSystem[l].mw;
                            }

                            (*solids[i].convert)(SECOND, THIRD, silminState->T, silminState->P, NULL, phaseX, r, NULL, NULL, NULL, NULL, NULL);
                            (*solids[i].display)(FIRST, silminState->T, silminState->P, r, &formula);

                            printf("Got phase %s with moles %f and grams %f and formula %s\n", solids[i].label, phaseMoles, phaseGrams, formula);
                            free(r);
                            free(phaseX);
                            free(formula);
                        }
                    }
                }
            }

            {
                double phaseMoles, phaseGrams;
                int nl;

                for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
                    for (k=0, phaseMoles=0.0, phaseGrams=0.0; k<nlc; k++) {
                        phaseMoles += (silminState->liquidComp)[nl][k];
                        for (l=0; l<nc; l++) phaseGrams += (silminState->liquidComp)[nl][k]*(liquid[k].liqToOx)[l]*bulkSystem[l].mw;
                    }

                    printf("Got phase %s with moles %f and grams %f\n", "liquid", phaseMoles, phaseGrams);
                }
            }

        } else if (strstr(argv[1], ".xml")   != NULL) {
            size_t len;
            int ret;
            char *outputFile;

            if (silminState == NULL) silminState = allocSilminStatePointer();
            /* moved initialization of incSolids etc. into input routine */
            ret = batchInputDataFromXmlFile(argv[1]);

            len = strlen(silminInputData.name) - 4;
            outputFile = (char *) malloc((size_t) (len+9)*sizeof(char));
            (void) strncpy(outputFile, silminInputData.name, len);
            (void) strcpy(&outputFile[len], "-out.xml");

            if (ret != FALSE) previousSilminState = copySilminStateStructure(silminState, previousSilminState);

            if        (ret == FALSE) {
                printf("Error(s) detected on reading input file %s. Exiting.\n", argv[1]);
                exit(0);
            } else if (ret == RUN_WETLIQUIDUS_CALC) {
                (void) findWetLiquidus();
                printf("Liquidus temperature is: %f\n", silminState->T-273.15); silminState->dspTstart = silminState->T;
                putOutputDataToXmlFile(outputFile);
            } else if (ret == RUN_LIQUIDUS_CALC) {
                while(!liquidus());
                printf("Liquidus temperature is: %f\n", silminState->T-273.15); silminState->dspTstart = silminState->T;
                putOutputDataToXmlFile(outputFile);
            } else if (ret == RUN_EQUILIBRATE_CALC) {
                while(!silmin());
                putOutputDataToXmlFile(outputFile);
                putSequenceDataToXmlFile(FALSE); /* finalize and close file */
            } else if (ret == RETURN_WITHOUT_CALC) {
                /* can be used to test changeLiquid (calling with changeFluid with likely cause seg fault) */
                putOutputDataToXmlFile(outputFile);
            }

            xmlCleanupParser();
            free(outputFile);

        } else if (strstr(argv[1], ".txt")) { /* debugging option to process list of files */
            static FILE *input = NULL;

            if ((input = fopen (argv[1], "r")) == NULL) {
                printf("Error(s) detected on reading input file %s. Exiting.\n", argv[1]);
                exit(0);
            }

            for (;;) {
                size_t len;
                int ret;
                char *iFileName, *oFileName, *sFileName;

                if (silminState == NULL) silminState = allocSilminStatePointer();
                /* moved initialization of incSolids etc. into input routine */
                silminState->assimilate = FALSE; // turn off assimilation for MCS debugging

                iFileName = (char *) malloc((size_t) REC*sizeof(char));

                if (fgets(iFileName, REC, input) == NULL) break;
                chomp(iFileName);
                ret = batchInputDataFromXmlFile(iFileName);

                len = strlen(silminInputData.name) - 4;
                oFileName = (char *) malloc((size_t) (len+9)*sizeof(char));
                (void) strncpy(oFileName, silminInputData.name, len);
                (void) strcpy(&oFileName[len], "-out.xml");

                sFileName = (char *) malloc((size_t) (len+12)*sizeof(char));
                (void) strncpy(sFileName, silminInputData.name, len);
                (void) strcpy(&sFileName[len], "-status.xml");

                if ((ret != FALSE) && (previousSilminState == NULL))
                    previousSilminState = copySilminStateStructure(silminState, previousSilminState);

                if        (ret == FALSE) {
                    printf("Error(s) detected on reading input file %s. Exiting.\n", iFileName);
                    exit(0);
                } else if (ret == RUN_WETLIQUIDUS_CALC) {
                    meltsStatus.status = GENERIC_INTERNAL_ERROR;
                    (void) findWetLiquidus();
                    (void) strcpy(silminInputData.name, iFileName);
                    putOutputDataToXmlFile(oFileName);
                    putStatusDataToXmlFile(sFileName);
                } else if (ret == RUN_LIQUIDUS_CALC) {
                    meltsStatus.status = GENERIC_INTERNAL_ERROR;
                    while(!liquidus());
                    (void) strcpy(silminInputData.name, iFileName);
                    putOutputDataToXmlFile(oFileName);
                    putStatusDataToXmlFile(sFileName);
                } else if (ret == RUN_EQUILIBRATE_CALC) {
                    meltsStatus.status = GENERIC_INTERNAL_ERROR;
                    while(!silmin());
                    (void) strcpy(silminInputData.name, iFileName);
                    putOutputDataToXmlFile(oFileName);
                    putStatusDataToXmlFile(sFileName);
                } else if (ret == RETURN_WITHOUT_CALC) {
                    meltsStatus.status = SILMIN_SUCCESS;
                    (void) strcpy(silminInputData.name, iFileName);
                    putOutputDataToXmlFile(oFileName);
                    putStatusDataToXmlFile(sFileName);
                } else if (ret == RETURN_DO_FRACTIONATION) {
                    doBatchFractionation();
                    meltsStatus.status = SILMIN_SUCCESS;
                    (void) strcpy(silminInputData.name, iFileName);
                    putOutputDataToXmlFile(oFileName);
                    putStatusDataToXmlFile(sFileName);
                } else if (ret == RETURN_FINALIZED) {
                    meltsStatus.status = SILMIN_SUCCESS;
                    putSequenceDataToXmlFile(FALSE); /* finalize and close file */
                    xmlCleanupParser();
                }

                free (iFileName);
                free (oFileName);
                free (sFileName);

                if ((meltsStatus.status != SILMIN_SUCCESS) && (meltsStatus.status != LIQUIDUS_SUCCESS)) break;
                else if ((silminState->fractionateSol || silminState->fractionateFlu || silminState->fractionateLiq))
                    previousSilminState = copySilminStateStructure(silminState, previousSilminState);

            }

            /* -> Close and discard file and return */

            fclose(input);

        } else { /* fall into listener mode */
            DIR *inputDir, *outputDir, *processedDir;
            size_t lenIdir, lenOdir, lenPdir;
            int fileOpenAttempts = 0;

            if (argc < 3) {
                printf("Usage:\n");
                printf("  Melts-batch input.melts\n");
                printf("  Melts-batch input.xml\n");
                printf("  Melts-batch inputDir outputDir [inputProcessedDir]\n");
                printf("              Directories are stipulated relative to current directory\n");
                printf("              with no trailing delimiter.\n");
                exit(0);
            }
            printf("Batch melts is in listener mode with\n");
            printf("               input directory  %s\n", argv[1]);
            printf("               output directory %s\n", argv[2]);
            printf("  and input processed directory %s\n", (argc > 3) ? argv[3] : argv[2]);

            inputDir = opendir(argv[1]);
            if(inputDir == NULL) { printf("Cannot open directory %s.  Exiting ...\n", argv[1]); exit(0); }
            else (void) closedir(inputDir);

            outputDir = opendir(argv[2]);
            if(outputDir == NULL) { printf("Cannot open directory %s.  Exiting ...\n", argv[2]); exit(0); }
            else (void) closedir(outputDir);

            processedDir = opendir((argc > 3) ? argv[3] : argv[2]);
            if(processedDir == NULL) { printf("Cannot open directory %s.  Exiting ...\n", (argc > 3) ? argv[3] : argv[2]); exit(0); }
            else (void) closedir(processedDir);

            lenIdir = strlen(argv[1]);
            lenOdir = strlen(argv[2]);
            lenPdir = strlen((argc > 3) ? argv[3] : argv[2]);

            for (;;) {
                unsigned int delay = 1;
                struct dirent *dp;

                inputDir = opendir(argv[1]);

                while ((dp = readdir(inputDir)) != NULL) {
                    if (strstr(dp->d_name, ".xml")   != NULL) { /* found a file to process */
                        int ret, len;
                        char *iFileName, *oFileName, *pFileName, *sFileName;

                        if (silminState == NULL) silminState = allocSilminStatePointer();
                        /* moved initialization of incSolids etc. into input routine */
                        silminState->assimilate = FALSE; // assimilation is handled in MCS

                        len = strlen(dp->d_name);
                        iFileName = (char *) malloc((size_t) (lenIdir + 1 + len + 1)*sizeof(char));
                        oFileName = (char *) malloc((size_t) (lenOdir + 1 + len + 5)*sizeof(char));
                        pFileName = (char *) malloc((size_t) (lenPdir + 1 + len + 1)*sizeof(char));
                        sFileName = (char *) malloc((size_t) (lenPdir + 1 + len + 8)*sizeof(char));

                        (void) strcpy(iFileName, argv[1]);
                        (void) strcat(iFileName, DIR_DELIM);
                        (void) strcat(iFileName, dp->d_name);

                        (void) strcpy(oFileName, argv[2]);
                        (void) strcat(oFileName, DIR_DELIM);
                        (void) strncat(oFileName, dp->d_name, len-4);
                        (void) strcat(oFileName, "-out.xml");

                        (void) strcpy(pFileName, (argc > 3) ? argv[3] : argv[2]);
                        (void) strcat(pFileName, DIR_DELIM);
                        (void) strcat(pFileName, dp->d_name);

                        (void) strcpy(sFileName, argv[2]);
                        (void) strcat(sFileName, DIR_DELIM);
                        (void) strncat(sFileName, dp->d_name, len-4);
                        (void) strcat(sFileName, "-status.xml");

                        ret = batchInputDataFromXmlFile(iFileName);
                        if ((ret != FALSE) && (previousSilminState == NULL))
                            previousSilminState = copySilminStateStructure(silminState, previousSilminState);

                        /* Rename file so -sequence.xml file is written in same location as .tbl files */
                        (void) strcpy(silminInputData.name, dp->d_name);

                        if        (ret == FALSE) {
                            fileOpenAttempts++;
                            printf("Error(s) detected on reading input file %s. Exiting.\n", iFileName);
                        } else if (ret == RUN_WETLIQUIDUS_CALC) {
                            fileOpenAttempts = 0;
                            meltsStatus.status = GENERIC_INTERNAL_ERROR;
                            (void) findWetLiquidus();
                            (void) strcpy(silminInputData.name, iFileName);
                            putOutputDataToXmlFile(oFileName);
                            putStatusDataToXmlFile(sFileName);
                        } else if (ret == RUN_LIQUIDUS_CALC) {
                            fileOpenAttempts = 0;
                            meltsStatus.status = GENERIC_INTERNAL_ERROR;
                            while(!liquidus());
                            (void) strcpy(silminInputData.name, iFileName);
                            putOutputDataToXmlFile(oFileName);
                            putStatusDataToXmlFile(sFileName);
                        } else if (ret == RUN_EQUILIBRATE_CALC) {
                            fileOpenAttempts = 0;
                            meltsStatus.status = GENERIC_INTERNAL_ERROR;
                            while(!silmin());
                            (void) strcpy(silminInputData.name, iFileName);
                            putOutputDataToXmlFile(oFileName);
                            putStatusDataToXmlFile(sFileName);
                        } else if (ret == RETURN_WITHOUT_CALC) {
                            fileOpenAttempts = 0;
                            meltsStatus.status = SILMIN_SUCCESS;
                            (void) strcpy(silminInputData.name, iFileName);
                            putOutputDataToXmlFile(oFileName);
                            putStatusDataToXmlFile(sFileName);
                        } else if (ret == RETURN_DO_FRACTIONATION) {
                            doBatchFractionation();
                            fileOpenAttempts = 0;
                            meltsStatus.status = SILMIN_SUCCESS;
                            (void) strcpy(silminInputData.name, iFileName);
                            putOutputDataToXmlFile(oFileName);
                            putStatusDataToXmlFile(sFileName);
                        } else if (ret == RETURN_FINALIZED) {
                            meltsStatus.status = SILMIN_SUCCESS;
                            putSequenceDataToXmlFile(FALSE); /* finalize and close file */
                            xmlCleanupParser();
                        }

                        if (fileOpenAttempts > 2) { ret = TRUE; fileOpenAttempts = 0; }
                        else if ((silminState->fractionateSol || silminState->fractionateFlu || silminState->fractionateLiq))
                            previousSilminState = copySilminStateStructure(silminState, previousSilminState);

                        if (ret) {
                            if (rename(iFileName, pFileName))
                                printf("Error(s) detected on renaming file %s to %s\n", iFileName, pFileName);
                        }

                        free (iFileName);
                        free (oFileName);
                        free (pFileName);
                        free (sFileName);
                        break; /* exit the while loop */
                    }
                }

                (void) closedir(inputDir);

                /* no files in input directory - wait and look again */
#ifdef MINGW
                Sleep(delay);
#else
                sleep(delay);
#endif

            }

        }

    }
#endif /* BATCH_VERSION */

    exit(0);
}

// findWetLiquidus moved back to liquidus.c so it can be called from easyMelts

/* end of file INTERFACE.C */
