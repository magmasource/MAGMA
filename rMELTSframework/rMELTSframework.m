//
//  rMELTSframework.m
//  rMELTSframework
//
//  Created by Mark Ghiorso on 1/7/13.
//  Copyright (c) 2013 Mark Ghiorso. All rights reserved.
//

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#include "silmin.h"
#include "status.h"
MeltsStatus meltsStatus;

#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"

int calculationMode = MODE_DEFAULT;
int quad_tol_modifier = 1;

void (*additionalOutput) (char *filename) = NULL;
char *addOutputFileName = NULL;

static SilminState *previousSilminState;

#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))
#define REC 134


/* returns RUN_LIQUIDUS_CALC    or           */
/*         RUN_EQUILIBRATE_CALC if succesful */
/*         FALSE                if not       */

#define RUN_LIQUIDUS_CALC       2
#define RUN_EQUILIBRATE_CALC    3
#define RETURN_WITHOUT_CALC     4
#define RETURN_DO_FRACTIONATION 5

/*
static int batchInputDataFromXmlFile(char *fileName) {
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt = NULL;
    xmlSchemaValidCtxtPtr ctxt2 = NULL;
    int ret = TRUE;
    static int SiO2 = -1, TiO2, Al2O3, Fe2O3, Cr2O3, FeO, MnO, MgO, NiO, CoO, CaO, Na2O, K2O, P2O5, H2O;
    
    if (SiO2 == -1) {
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
        }
    }
    
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
                            
                            if (silminState != NULL) ; // destroy the old state - nyi
                            silminState = allocSilminStatePointer();
                            for (i=0, np=0; i<npc; i++) if (solids[i].type == PHASE) { (silminState->incSolids)[np] = TRUE; np++; }
                            (silminState->incSolids)[npc] = TRUE;
                            silminState->nLiquidCoexist  = 1;
                            silminState->fo2Path  = FO2_NONE;
                            silminState->T = 0.0;
                            silminState->P = 0.0;
                            
                            for (i=0, silminState->liquidMass=0.0; i<nc; i++) (silminState->bulkComp)[i] = 0.0;
                            while (level2 != NULL) {
                                if (level2->type == XML_ELEMENT_NODE) {
                                    xmlChar *content2 = xmlNodeGetContent(level2);
                                    if      (!strcmp((char *) level2->name, "SiO2" )) (silminState->bulkComp)[SiO2 ] = atof((char *) content2)/bulkSystem[SiO2 ].mw;
                                    else if (!strcmp((char *) level2->name, "TiO2" )) (silminState->bulkComp)[TiO2 ] = atof((char *) content2)/bulkSystem[TiO2 ].mw;
                                    else if (!strcmp((char *) level2->name, "Al2O3")) (silminState->bulkComp)[Al2O3] = atof((char *) content2)/bulkSystem[Al2O3].mw;
                                    else if (!strcmp((char *) level2->name, "Fe2O3")) (silminState->bulkComp)[Fe2O3] = atof((char *) content2)/bulkSystem[Fe2O3].mw;
                                    else if (!strcmp((char *) level2->name, "Cr2O3")) (silminState->bulkComp)[Cr2O3] = atof((char *) content2)/bulkSystem[Cr2O3].mw;
                                    else if (!strcmp((char *) level2->name, "FeO"  )) (silminState->bulkComp)[FeO  ] = atof((char *) content2)/bulkSystem[FeO  ].mw;
                                    else if (!strcmp((char *) level2->name, "MnO"  )) (silminState->bulkComp)[MnO  ] = atof((char *) content2)/bulkSystem[MnO  ].mw;
                                    else if (!strcmp((char *) level2->name, "MgO"  )) (silminState->bulkComp)[MgO  ] = atof((char *) content2)/bulkSystem[MgO  ].mw;
                                    else if (!strcmp((char *) level2->name, "NiO"  )) (silminState->bulkComp)[NiO  ] = atof((char *) content2)/bulkSystem[NiO  ].mw;
                                    else if (!strcmp((char *) level2->name, "CoO"  )) (silminState->bulkComp)[CoO  ] = atof((char *) content2)/bulkSystem[CoO  ].mw;
                                    else if (!strcmp((char *) level2->name, "CaO"  )) (silminState->bulkComp)[CaO  ] = atof((char *) content2)/bulkSystem[CaO  ].mw;
                                    else if (!strcmp((char *) level2->name, "Na2O" )) (silminState->bulkComp)[Na2O ] = atof((char *) content2)/bulkSystem[Na2O ].mw;
                                    else if (!strcmp((char *) level2->name, "K2O"  )) (silminState->bulkComp)[K2O  ] = atof((char *) content2)/bulkSystem[K2O  ].mw;
                                    else if (!strcmp((char *) level2->name, "P2O5" )) (silminState->bulkComp)[P2O5 ] = atof((char *) content2)/bulkSystem[P2O5 ].mw;
                                    else if (!strcmp((char *) level2->name, "H2O"  )) (silminState->bulkComp)[H2O  ] = atof((char *) content2)/bulkSystem[H2O  ].mw;
                                    silminState->liquidMass += atof((char *) content2);
                                    if (content2 != NULL) xmlFree(content2);
                                }
                                level2 = level2->next;
                            }
                            for (i=0; i<nlc; i++)
                                for ((silminState->liquidComp)[0][i]=0.0, silminState->oxygen=0.0, j=0; j<nc; j++) {
                                    (silminState->liquidComp)[0][i] += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i];
                                    silminState->oxygen += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
                                }
                            
                            
                            
                        } else if (!strcmp((char *) level1->name, "calculationMode")) {
                            printf("Found calculationMode: %s\n", content1);
                            if      (!strcmp((char *) content1, "findLiquidus")) ret = RUN_LIQUIDUS_CALC;
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
                                    if      (!strcmp((char *) level2->name, "SiO2" )) changeBC[SiO2 ] = atof((char *) content2)/bulkSystem[SiO2 ].mw;
                                    else if (!strcmp((char *) level2->name, "TiO2" )) changeBC[TiO2 ] = atof((char *) content2)/bulkSystem[TiO2 ].mw;
                                    else if (!strcmp((char *) level2->name, "Al2O3")) changeBC[Al2O3] = atof((char *) content2)/bulkSystem[Al2O3].mw;
                                    else if (!strcmp((char *) level2->name, "Fe2O3")) changeBC[Fe2O3] = atof((char *) content2)/bulkSystem[Fe2O3].mw;
                                    else if (!strcmp((char *) level2->name, "Cr2O3")) changeBC[Cr2O3] = atof((char *) content2)/bulkSystem[Cr2O3].mw;
                                    else if (!strcmp((char *) level2->name, "FeO"  )) changeBC[FeO  ] = atof((char *) content2)/bulkSystem[FeO  ].mw;
                                    else if (!strcmp((char *) level2->name, "MnO"  )) changeBC[MnO  ] = atof((char *) content2)/bulkSystem[MnO  ].mw;
                                    else if (!strcmp((char *) level2->name, "MgO"  )) changeBC[MgO  ] = atof((char *) content2)/bulkSystem[MgO  ].mw;
                                    else if (!strcmp((char *) level2->name, "NiO"  )) changeBC[NiO  ] = atof((char *) content2)/bulkSystem[NiO  ].mw;
                                    else if (!strcmp((char *) level2->name, "CoO"  )) changeBC[CoO  ] = atof((char *) content2)/bulkSystem[CoO  ].mw;
                                    else if (!strcmp((char *) level2->name, "CaO"  )) changeBC[CaO  ] = atof((char *) content2)/bulkSystem[CaO  ].mw;
                                    else if (!strcmp((char *) level2->name, "Na2O" )) changeBC[Na2O ] = atof((char *) content2)/bulkSystem[Na2O ].mw;
                                    else if (!strcmp((char *) level2->name, "K2O"  )) changeBC[K2O  ] = atof((char *) content2)/bulkSystem[K2O  ].mw;
                                    else if (!strcmp((char *) level2->name, "P2O5" )) changeBC[P2O5 ] = atof((char *) content2)/bulkSystem[P2O5 ].mw;
                                    else if (!strcmp((char *) level2->name, "H2O"  )) changeBC[H2O  ] = atof((char *) content2)/bulkSystem[H2O  ].mw;
                                    silminState->liquidMass += atof((char *) content2);
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
                                    if      (!strcmp((char *) level2->name, "SiO2" )) changeBC[SiO2 ] = atof((char *) content2)/bulkSystem[SiO2 ].mw;
                                    else if (!strcmp((char *) level2->name, "TiO2" )) changeBC[TiO2 ] = atof((char *) content2)/bulkSystem[TiO2 ].mw;
                                    else if (!strcmp((char *) level2->name, "Al2O3")) changeBC[Al2O3] = atof((char *) content2)/bulkSystem[Al2O3].mw;
                                    else if (!strcmp((char *) level2->name, "Fe2O3")) changeBC[Fe2O3] = atof((char *) content2)/bulkSystem[Fe2O3].mw;
                                    else if (!strcmp((char *) level2->name, "Cr2O3")) changeBC[Cr2O3] = atof((char *) content2)/bulkSystem[Cr2O3].mw;
                                    else if (!strcmp((char *) level2->name, "FeO"  )) changeBC[FeO  ] = atof((char *) content2)/bulkSystem[FeO  ].mw;
                                    else if (!strcmp((char *) level2->name, "MnO"  )) changeBC[MnO  ] = atof((char *) content2)/bulkSystem[MnO  ].mw;
                                    else if (!strcmp((char *) level2->name, "MgO"  )) changeBC[MgO  ] = atof((char *) content2)/bulkSystem[MgO  ].mw;
                                    else if (!strcmp((char *) level2->name, "NiO"  )) changeBC[NiO  ] = atof((char *) content2)/bulkSystem[NiO  ].mw;
                                    else if (!strcmp((char *) level2->name, "CoO"  )) changeBC[CoO  ] = atof((char *) content2)/bulkSystem[CoO  ].mw;
                                    else if (!strcmp((char *) level2->name, "CaO"  )) changeBC[CaO  ] = atof((char *) content2)/bulkSystem[CaO  ].mw;
                                    else if (!strcmp((char *) level2->name, "Na2O" )) changeBC[Na2O ] = atof((char *) content2)/bulkSystem[Na2O ].mw;
                                    else if (!strcmp((char *) level2->name, "K2O"  )) changeBC[K2O  ] = atof((char *) content2)/bulkSystem[K2O  ].mw;
                                    else if (!strcmp((char *) level2->name, "P2O5" )) changeBC[P2O5 ] = atof((char *) content2)/bulkSystem[P2O5 ].mw;
                                    else if (!strcmp((char *) level2->name, "H2O"  )) changeBC[H2O  ] = atof((char *) content2)/bulkSystem[H2O  ].mw;
                                    silminState->liquidMass += atof((char *) content2);
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
                                                if      (!strcmp((char *) level3->name, "initialT" )) {
                                                    silminState->T         = atof((char *) content3) + 273.15;
                                                    silminState->dspTstart = atof((char *) content3) + 273.15;
                                                }
                                                else if (!strcmp((char *) level3->name, "finalT"   )) silminState->dspTstop = atof((char *) content3) + 273.15;
                                                else if (!strcmp((char *) level3->name, "incT"     )) silminState->dspTinc  = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "initialP" )) {
                                                    silminState->P         = atof((char *) content3);
                                                    silminState->dspPstart = atof((char *) content3);
                                                }
                                                else if (!strcmp((char *) level3->name, "finalP"   )) silminState->dspPstop = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "incP"     )) silminState->dspPinc  = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "dpdt"     )) silminState->dspDPDt  = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "fo2Path"  )) {
                                                    if      (!strcmp((char *) content3, "none")) silminState->fo2Path  = FO2_NONE;
                                                    else if (!strcmp((char *) content3, "fmq" )) silminState->fo2Path  = FO2_QFM;
                                                    else if (!strcmp((char *) content3, "coh" )) silminState->fo2Path  = FO2_COH;
                                                    else if (!strcmp((char *) content3, "nno" )) silminState->fo2Path  = FO2_NNO;
                                                    else if (!strcmp((char *) content3, "iw"  )) silminState->fo2Path  = FO2_IW;
                                                    else if (!strcmp((char *) content3, "hm"  )) silminState->fo2Path  = FO2_HM;
                                                }
                                                else if (!strcmp((char *) level3->name, "fo2Offset")) silminState->fo2Delta = atof((char *) content3);
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
                                                if      (!strcmp((char *) level3->name, "initialT" )) {
                                                    silminState->T         = atof((char *) content3) + 273.15;
                                                    silminState->dspTstart = atof((char *) content3) + 273.15;
                                                }
                                                else if (!strcmp((char *) level3->name, "finalT"   )) silminState->dspTstop  = atof((char *) content3) + 273.15;
                                                else if (!strcmp((char *) level3->name, "incT"     )) silminState->dspTinc   = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "initialV" )) silminState->refVolume = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "finalV"   )) silminState->dspVstop  = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "incV"     )) silminState->dspVinc  = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "dvdt"     )) silminState->dspDVDt  = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "fo2Path"  )) {
                                                    if      (!strcmp((char *) content3, "none")) silminState->fo2Path  = FO2_NONE;
                                                    else if (!strcmp((char *) content3, "fmq" )) silminState->fo2Path  = FO2_QFM;
                                                    else if (!strcmp((char *) content3, "coh" )) silminState->fo2Path  = FO2_COH;
                                                    else if (!strcmp((char *) content3, "nno" )) silminState->fo2Path  = FO2_NNO;
                                                    else if (!strcmp((char *) content3, "iw"  )) silminState->fo2Path  = FO2_IW;
                                                    else if (!strcmp((char *) content3, "hm"  )) silminState->fo2Path  = FO2_HM;
                                                }
                                                else if (!strcmp((char *) level3->name, "fo2Offset")) silminState->fo2Delta = atof((char *) content3);
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
                                                if      (!strcmp((char *) level3->name, "initialH" )) silminState->refEnthalpy = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "finalH"   )) silminState->dspHstop    = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "incH"     )) silminState->dspHinc     = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "initialP" )) {
                                                    silminState->P         = atof((char *) content3);
                                                    silminState->dspPstart = atof((char *) content3);
                                                }
                                                else if (!strcmp((char *) level3->name, "finalP"   )) silminState->dspPstop = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "incP"     )) silminState->dspPinc  = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "dpdh"     )) silminState->dspDPDH  = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "fo2Path"  )) {
                                                    if      (!strcmp((char *) content3, "none")) silminState->fo2Path  = FO2_NONE;
                                                    else if (!strcmp((char *) content3, "fmq" )) silminState->fo2Path  = FO2_QFM;
                                                    else if (!strcmp((char *) content3, "coh" )) silminState->fo2Path  = FO2_COH;
                                                    else if (!strcmp((char *) content3, "nno" )) silminState->fo2Path  = FO2_NNO;
                                                    else if (!strcmp((char *) content3, "iw"  )) silminState->fo2Path  = FO2_IW;
                                                    else if (!strcmp((char *) content3, "hm"  )) silminState->fo2Path  = FO2_HM;
                                                }
                                                else if (!strcmp((char *) level3->name, "fo2Offset")) silminState->fo2Delta = atof((char *) content3);
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
                                                if      (!strcmp((char *) level3->name, "initialS" )) silminState->refEntropy = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "finalS"   )) silminState->dspSstop   = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "incS"     )) silminState->dspSinc    = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "initialP" )) {
                                                    silminState->P         = atof((char *) content3);
                                                    silminState->dspPstart = atof((char *) content3);
                                                }
                                                else if (!strcmp((char *) level3->name, "finalP"   )) silminState->dspPstop = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "incP"     )) silminState->dspPinc  = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "dpds"     )) silminState->dspDPDS  = atof((char *) content3);
                                                else if (!strcmp((char *) level3->name, "fo2Path"  )) {
                                                    if      (!strcmp((char *) content3, "none")) silminState->fo2Path  = FO2_NONE;
                                                    else if (!strcmp((char *) content3, "fmq" )) silminState->fo2Path  = FO2_QFM;
                                                    else if (!strcmp((char *) content3, "coh" )) silminState->fo2Path  = FO2_COH;
                                                    else if (!strcmp((char *) content3, "nno" )) silminState->fo2Path  = FO2_NNO;
                                                    else if (!strcmp((char *) content3, "iw"  )) silminState->fo2Path  = FO2_IW;
                                                    else if (!strcmp((char *) content3, "hm"  )) silminState->fo2Path  = FO2_HM;
                                                }
                                                else if (!strcmp((char *) level3->name, "fo2Offset")) silminState->fo2Delta = atof((char *) content3);
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
                                    if (!strcmp((char *) level2->name, "temperature" )) {
                                        printf("Found temperature = %s\n", content2); silminState->dspAssimT = atof((char *) content2);
                                    } else if (!strcmp((char *) level2->name, "increments"  )) {
                                        printf("Found increments  = %s\n", content2); silminState->dspAssimInc = atoi((char *) content2);
                                    } else if (!strcmp((char *) level2->name, "mass"        )) {
                                        printf("Found mass        = %s\n", content2); silminState->dspAssimMass = atof((char *) content2);
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
                                                            if (content4 != NULL) xmlFree(content4);
                                                        }
                                                        level4 = level4->next;
                                                    }
                                                }
                                            }
                                            level3 = level3->next;
                                        }
                                    }
                                    if (content2 != NULL) xmlFree(content2);
                                }
                                level2 = level2->next;
                            }
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
    xmlSchemaCleanupTypes();
    xmlCleanupParser();
    
    return ret;
}

static void putOutputDataToXmlFile(char *outputFile) {
    xmlTextWriterPtr writer;
    size_t len;
    int rc;
    time_t tp;
    char * cOut;
    double gLiq = 0.0, hLiq = 0.0, sLiq = 0.0, vLiq = 0.0, cpLiq = 0.0, mLiq = 0.0, viscosity = 0.0;
    double totalMass=0.0, totalGibbsEnergy=0.0, totalEnthalpy=0.0, totalEntropy=0.0, totalVolume=0.0, totalHeatCapacity=0.0;
    static double *m, *r, *oxVal;
    int i, j;
    
    if (m == NULL)         m = (double *) malloc((size_t)      nc*sizeof(double));
    if (r == NULL)         r = (double *) malloc((size_t) (nlc-1)*sizeof(double));
    if (oxVal == NULL) oxVal = (double *) malloc((size_t)      nc*sizeof(double));
    
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
    
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "temperature", "%.20g", silminState->T-273.15);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "pressure",    "%.20g", silminState->P);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "log_fO2",     "%.20g", silminState->fo2);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "deltaHM",     "%.20g", silminState->fo2 - getlog10fo2(silminState->T, silminState->P, FO2_HM));
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "deltaNNO",    "%.20g", silminState->fo2 - getlog10fo2(silminState->T, silminState->P, FO2_NNO));
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "deltaFMQ",    "%.20g", silminState->fo2 - getlog10fo2(silminState->T, silminState->P, FO2_QFM));
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "deltaCOH",    "%.20g", silminState->fo2 - getlog10fo2(silminState->T, silminState->P, FO2_COH));
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "deltaIW",     "%.20g", silminState->fo2 - getlog10fo2(silminState->T, silminState->P, FO2_IW));
    
    
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
            
            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",            "%.20g", oxSum);
            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density",         "%.20g", (volume == 0.0) ? 0.0 : oxSum/(10.0*volume));
            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "viscosity",       "%.20g", viscosity);
            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%.20g", gibbsEnergy);
            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",        "%.20g", enthalpy);
            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",         "%.20g", entropy);
            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",          "%.20g", volume*10.0);
            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%.20g", heatCapacity);
            
            for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%.20g", oxVal[i]*100.0);
            
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
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", 	   "%.20g", mass);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density",	   "%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume));
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%.20g", gibbsEnergy);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	   "%.20g", enthalpy);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	   "%.20g", entropy);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",	   "%.20g", volume*10.0);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%.20g", heatCapacity);
                
                for (i=0, oxSum=0.0; i<nc; i++) {
                    oxVal[i]  = (solids[j].solToOx)[i]*bulkSystem[i].mw;
                    oxSum    += oxVal[i];
                }
                if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%.20g", oxVal[i]*100.0);
                
                rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",         "%s",   solids[j].label);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",      "%s",   solids[j].formula);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%.20g", 1.0);
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
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", 	   "%.20g", mass);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density",	   "%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume));
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%.20g", gibbsEnergy);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	   "%.20g", enthalpy);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	   "%.20g", entropy);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",	   "%.20g", volume*10.0);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%.20g", heatCapacity);
                
                for (i=0, oxSum=0.0; i<nc; i++) {
                    int k;
                    for (k=0, oxVal[i]=0.0; k<solids[j].na; k++) oxVal[i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw;
                    oxSum += oxVal[i];
                }
                if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%.20g", oxVal[i]*100.0);
                
                for (i=0; i<solids[j].na; i++) {
                    rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",         "%s",   solids[j+1+i].label);
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",      "%s",   solids[j+1+i].formula);
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%.20g", m[i]/(silminState->solidComp)[j][ns]);
                    rc = xmlTextWriterEndElement(writer);
                }
            }
            
            rc = xmlTextWriterEndElement(writer);
        }
    }
    
    if (totalMass != 0.0) {
        rc = xmlTextWriterStartElement(writer, BAD_CAST "totalSolids");
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",		 "%.20g", totalMass);
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density",	 "%.20g", (totalVolume == 0.0) ? 0.0 : totalMass/(10.0*totalVolume));
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%.20g", totalGibbsEnergy);
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	 "%.20g", totalEnthalpy);
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	 "%.20g", totalEntropy);
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume", 	 "%.20g", totalVolume*10.0);
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",	 "%.20g", totalHeatCapacity);
        rc = xmlTextWriterEndElement(writer);
    }
    
    if (silminState->isenthalpic && (silminState->refEnthalpy == 0.0)) silminState->refEnthalpy = hLiq+totalEnthalpy;
    if (silminState->isentropic  && (silminState->refEntropy  == 0.0)) silminState->refEntropy  = sLiq+totalEntropy;
    if (silminState->isochoric   && (silminState->refVolume   == 0.0)) silminState->refVolume   = vLiq+totalVolume;
    
    if (silminState->fractionateSol || silminState->fractionateFlu || silminState->fractionateLiq) {
        rc = xmlTextWriterStartElement(writer, BAD_CAST "fractionate");
        rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "type", BAD_CAST "current");
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", "%.20g", silminState->fracMass-previousSilminState->fracMass);
        
        if (silminState->fractionateSol || silminState->fractionateFlu) {
            for (j=0; j<npc; j++) {
                int ns;
                
                if ( silminState->fractionateSol && !silminState->fractionateFlu && !strcmp((char *) solids[j].label, "water")) continue;
                if (!silminState->fractionateSol &&  silminState->fractionateFlu &&  strcmp((char *) solids[j].label, "water")) continue;
                
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
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",		 "%.20g", mass);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density",	 "%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume));
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%.20g", gibbsEnergy);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	 "%.20g", enthalpy);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	 "%.20g", entropy);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume", 	 "%.20g", volume*10.0);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",	 "%.20g", heatCapacity);
                        
                        for (i=0, oxSum=0.0; i<nc; i++) {
                            oxVal[i]  = (solids[j].solToOx)[i]*bulkSystem[i].mw;
                            oxSum    += oxVal[i];
                        }
                        if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                        for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%.20g", oxVal[i]*100.0);
                        
                        rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",         "%s",   solids[j].label);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",      "%s",   solids[j].formula);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%.20g", 1.0);
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
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",		 "%.20g", mass);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density",	 "%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume));
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%.20g", gibbsEnergy);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	 "%.20g", enthalpy);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	 "%.20g", entropy);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume", 	 "%.20g", volume*10.0);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",	 "%.20g", heatCapacity);
                        
                        for (i=0, oxSum=0.0; i<nc; i++) {
                            int k;
                            for (k=0, oxVal[i]=0.0; k<solids[j].na; k++) oxVal[i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw;
                            oxSum += oxVal[i];
                        }
                        if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                        for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%.20g", oxVal[i]*100.0);
                        
                        for (i=0; i<solids[j].na; i++) {
                            rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name", 	  "%s",   solids[j+1+i].label);
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",	  "%s",   solids[j+1+i].formula);
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%.20g", m[i]/tmpMoles);
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
                
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",	     "%.20g", mass);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density",	     "%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume));
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%.20g", gibbsEnergy);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	     "%.20g", enthalpy);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	     "%.20g", entropy);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",	     "%.20g", volume*10.0);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%.20g", heatCapacity);
                
                for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%.20g", oxVal[i]*100.0);
                
                rc = xmlTextWriterEndElement(writer);
            }
        }
        
        rc = xmlTextWriterEndElement(writer);
    }
    
    if ( (previousSilminState->fractionateSol || previousSilminState->fractionateFlu || previousSilminState->fractionateLiq)
        && (previousSilminState->fracMass > 0) ) {
        rc = xmlTextWriterStartElement(writer, BAD_CAST "fractionate");
        rc = xmlTextWriterWriteAttribute(writer, BAD_CAST "type", BAD_CAST "previous");
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", "%.20g", previousSilminState->fracMass);
        
        if (previousSilminState->fractionateSol || previousSilminState->fractionateFlu) {
            for (j=0; j<npc; j++) {
                int ns;
                
                if ( previousSilminState->fractionateSol && !previousSilminState->fractionateFlu && !strcmp((char *) solids[j].label, "water")) continue;
                if (!previousSilminState->fractionateSol &&  previousSilminState->fractionateFlu &&  strcmp((char *) solids[j].label, "water")) continue;
                
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
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",		 "%.20g", mass);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density",	 "%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume));
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%.20g", gibbsEnergy);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	 "%.20g", enthalpy);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	 "%.20g", entropy);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume", 	 "%.20g", volume*10.0);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",	 "%.20g", heatCapacity);
                        
                        for (i=0, oxSum=0.0; i<nc; i++) {
                            oxVal[i]  = (solids[j].solToOx)[i]*bulkSystem[i].mw;
                            oxSum    += oxVal[i];
                        }
                        if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                        for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%.20g", oxVal[i]*100.0);
                        
                        rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",         "%s",   solids[j].label);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",      "%s",   solids[j].formula);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%.20g", 1.0);
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
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",		 "%.20g", mass);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density",	 "%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume));
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%.20g", gibbsEnergy);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	 "%.20g", enthalpy);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	 "%.20g", entropy);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume", 	 "%.20g", volume*10.0);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",	 "%.20g", heatCapacity);
                        
                        for (i=0, oxSum=0.0; i<nc; i++) {
                            int k;
                            for (k=0, oxVal[i]=0.0; k<solids[j].na; k++) oxVal[i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw;
                            oxSum += oxVal[i];
                        }
                        if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                        for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%.20g", oxVal[i]*100.0);
                        
                        for (i=0; i<solids[j].na; i++) {
                            rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name", 	  "%s",   solids[j+1+i].label);
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "formula",	  "%s",   solids[j+1+i].formula);
                            rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%.20g", m[i]/(previousSilminState->fracSComp)[j][ns]);
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
                
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",	     "%.20g", mass);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density",	     "%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume));
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%.20g", gibbsEnergy);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",	     "%.20g", enthalpy);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",	     "%.20g", entropy);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",	     "%.20g", volume*10.0);
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%.20g", heatCapacity);
                
                for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST bulkSystem[i].label, "%.20g", oxVal[i]*100.0);
                
                rc = xmlTextWriterEndElement(writer);
            }
        }
        
        rc = xmlTextWriterEndElement(writer);
    }
    
    rc = xmlTextWriterStartElement(writer, BAD_CAST "system");
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",	       "%.20g", mLiq+totalMass);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "density",         "%.20g", (vLiq+totalVolume == 0.0) ? 0.0
                                         :  (mLiq+totalMass)/(10.0*(vLiq+totalVolume)));
    if (vLiq > totalVolume)
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "viscosity",       "%.20g",
                                             viscosity - 2.0*log10(1.0-2.0*totalVolume/(totalVolume+vLiq)));
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%.20g", gLiq+totalGibbsEnergy);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",        "%.20g", hLiq+totalEnthalpy);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",         "%.20g", sLiq+totalEntropy);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",	       "%.20g", (vLiq+totalVolume)*10.0);
    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%.20g", cpLiq+totalHeatCapacity);
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
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moles",	         "%.20g", mO2);
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",	         "%.20g", mO2*31.9988);
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "gibbsFreeEnergy", "%.20g", mO2*(oxygen.cur).g);
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "enthalpy",        "%.20g", mO2*(oxygen.cur).h);
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "entropy",         "%.20g", mO2*(oxygen.cur).s);
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "volume",	         "%.20g", mO2*10.0*(oxygen.cur).v);
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "heatCapacity",    "%.20g", mO2*(oxygen.cur).cp);
        rc = xmlTextWriterEndElement(writer);
    }
    
    if (silminState->assimilate) {
        int ns;
        rc = xmlTextWriterStartElement(writer, BAD_CAST "assimilant");
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass",	         "%.20g", silminState->assimMass);
        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "temperature",	 "%.20g", silminState->assimT);
        
        for (j=0; j<npc; j++) if (solids[j].type == PHASE)
            for (ns=0; ns<(silminState->nAssimComp)[j]; ns++) {
                rc = xmlTextWriterStartElement(writer, BAD_CAST "solid");
                rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name", "%s", solids[j].label);
                if (solids[j].na == 1) {
                    double mass = (silminState->assimComp)[j][ns]*solids[j].mw*silminState->assimMass/silminState->dspAssimMass;
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", "%.20g", mass);
                    rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",         "%s",   solids[j].label);
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "moleFraction", "%.20g", 1.0);
                    rc = xmlTextWriterEndElement(writer);
                    
                } else {
                    double mass = 0.0;
                    for (i=0; i<solids[j].na; i++) mass += (silminState->assimComp)[j+1+i][ns]*solids[j+1+i].mw;
                    mass *= silminState->assimMass/silminState->dspAssimMass;
                    rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "mass", "%.20g", mass);
                    
                    for (i=0; i<solids[j].na; i++) {
                        rc = xmlTextWriterStartElement(writer, BAD_CAST "component");
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "name",    "%s", solids[j+1+i].label);
                        rc = xmlTextWriterWriteFormatElement(writer, BAD_CAST "molFrac", "%.20g",
                                                             (silminState->assimComp)[j+1+i][ns]/(silminState->assimComp)[j][ns]);
                        rc = xmlTextWriterEndElement(writer);
                    }
                    
                }
                rc = xmlTextWriterEndElement(writer);
            }
        rc = xmlTextWriterEndElement(writer);
    }
    
    rc = xmlTextWriterEndDocument(writer);
    xmlFreeTextWriter(writer);
}

static void putStatusDataToXmlFile(char *statusFile) {
    xmlTextWriterPtr writer;
    int rc;
    const static char *m[] = {
        "Success: Find liquidus",                                  // LIQUIDUS_SUCCESS
        "Error: Maximum temperature in Find Liquidus",             // LIQUIDUS_MAX_T
        "Error: Minimum temperature in Find Liquidus",             // LIQUIDUS_MIN_T
        "Error: Maximum time limit exceeded in Find Liquidus",     // LIQUIDUS_TIME
        "Error: Cannot specify multiple liquids in Find Liquidus", // LIQUIDUS_MULTIPLE
        "Success: Equilibrate",                                    // SILMIN_SUCCESS
        "Error: Quadratic Iterations exceeded",                    // SILMIN_QUAD_MAX
        "Error: Zero steplength computed in linear search",        // SILMIN_LIN_ZERO
        "Error: Maximum iterations exceeded in linear search",     // SILMIN_LIN_MAX
        "Error: Cannot add a solid phase to liquid(+solids)",      // SILMIN_ADD_LIQUID_1
        "Error: Cannot add a solid phase to solid(s)",             // SILMIN_ADD_LIQUID_2
        "Error: Cannot add a liquid phase to solid(s)",            // SILMIN_ADD_LIQUID_3
        "Error: Phase rule violation (rank deficiency)",           // SILMIN_RANK
        "Error: Maximum time limit exceeded in Silmin",            // SILMIN_TIME
        "Error: Internal",                                         // GENERIC_INTERNAL_ERROR
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
    
    // Solid Phase Fractionation
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
        for (i=0; i<npc; i++) {
            if ( silminState->fractionateSol && !silminState->fractionateFlu && !strcmp((char *) solids[i].label, "water")) continue;
            if (!silminState->fractionateSol &&  silminState->fractionateFlu &&  strcmp((char *) solids[i].label, "water")) continue;
            for (ns=0; ns<(silminState->nSolidCoexist)[i]; ns++) {
                if (solids[i].na == 1) {
                    (silminState->fracSComp)[i][ns] += (silminState->solidComp)[i][ns]-MASSIN;
                    if (silminState->fo2Path != FO2_NONE) silminState->oxygen -= (oxygen.solToOx)[i]*((silminState->solidComp)[i][ns]-MASSIN);
                    silminState->fracMass += ((silminState->solidComp)[i][ns]-MASSIN)*solids[i].mw;
                    for (j=0; j<nc; j++) (silminState->bulkComp)[j] -= (solids[i].solToOx)[j]*((silminState->solidComp)[i][ns]-MASSIN);
                    
                    // Subtract off H, S or V if appropriate
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
                        
                        // Subtract off H, S or V if appropriate
                        if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0)) silminState->refEnthalpy -= m[j]*(solids[i+1+j].cur).h;
                        if (silminState->isentropic && (silminState->refEntropy != 0.0))   silminState->refEntropy  -= m[j]*(solids[i+1+j].cur).s;
                        if (silminState->isochoric && (silminState->refVolume != 0.0))     silminState->refVolume   -= m[j]*(solids[i+1+j].cur).v;
                    }
                    (silminState->solidComp)[i][ns] = MASSIN;
                    
                    // Subtract off H, S or V if appropriate
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
    
    // Liquid Phase Fractionation
    if (silminState->fractionateLiq && !hasLiquid) fprintf(stderr, "...Cannot do liquid fractionation without a liquid phase.\n");
	
    if (silminState->fractionateLiq && hasLiquid) {
        double *m = (double *) malloc((size_t) nlc*sizeof(double));
        double *r = (double *) malloc((size_t) nlc*sizeof(double));
        for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
            double refMoles, totalMoles;
            for (i=0, refMoles=0.0; i<nlc; i++) refMoles += (silminState->liquidComp)[nl][i];
            
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
                    
                    // Subtract off H, S or V if appropriate
                    if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0)) silminState->refEnthalpy -= m[i]*(liquid[i].cur).h;
                    if (silminState->isentropic  && (silminState->refEntropy  != 0.0)) silminState->refEntropy  -= m[i]*(liquid[i].cur).s;
                    if (silminState->isochoric   && (silminState->refVolume   != 0.0)) silminState->refVolume	-= m[i]*(liquid[i].cur).v;
                } else m[i] = 0.0;
            }
            
            // Subtract off H, S or V if appropriate
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

int main (int argc, char *argv[])
{
    calculationMode = MODE__MELTS;
    
    if (calculationMode == MODE__MELTS) {
        liquid = meltsLiquid;
        solids = meltsSolids;
        nlc = meltsNlc;
        nls = meltsNls;
        npc = meltsNpc;
    } else if (calculationMode == MODE_pMELTS) {
        liquid = pMeltsLiquid;
        solids = pMeltsSolids;
        nlc = pMeltsNlc;
        nls = pMeltsNls;
        npc = pMeltsNpc;
    }
    
    InitComputeDataStruct();
    
            size_t len;
            int ret;
            char *outputFile;
            
            if (silminState == NULL) {
                int i, np;
                silminState = allocSilminStatePointer();
                for (i=0, np=0; i<npc; i++) if (solids[i].type == PHASE) { (silminState->incSolids)[np] = TRUE; np++; }
                (silminState->incSolids)[npc] = TRUE;
                silminState->nLiquidCoexist  = 1;
                silminState->fo2Path  = FO2_NONE;
            }
            silminState->assimilate = FALSE;
            ret = batchInputDataFromXmlFile(argv[1]);
            
            len = strlen(silminInputData.name) - 4;
            outputFile = (char *) malloc((size_t) (len+9)*sizeof(char));
            (void) strncpy(outputFile, silminInputData.name, len);
            (void) strcpy(&outputFile[len], "-out.xml");
            
            if (ret != FALSE) previousSilminState = copySilminStateStructure(silminState, previousSilminState);
            
            if        (ret == FALSE) {
                
                } else if (ret == RUN_LIQUIDUS_CALC) {
                    fileOpenAttempts = 0;
                    meltsStatus.status = GENERIC_INTERNAL_ERROR;
                    while(!liquidus());
                    putOutputDataToXmlFile(oFileName);
                    putStatusDataToXmlFile(sFileName);
                } else if (ret == RUN_EQUILIBRATE_CALC) {
                    fileOpenAttempts = 0;
                    meltsStatus.status = GENERIC_INTERNAL_ERROR;
                    while(!silmin());
                    putOutputDataToXmlFile(oFileName);
                    putStatusDataToXmlFile(sFileName);
                } else if (ret == RETURN_WITHOUT_CALC) {
                    fileOpenAttempts = 0;
                    meltsStatus.status = SILMIN_SUCCESS;
                    putOutputDataToXmlFile(oFileName);
                    putStatusDataToXmlFile(sFileName);
                } else if (ret == RETURN_DO_FRACTIONATION) {
                    doBatchFractionation();
                    fileOpenAttempts = 0;
                    meltsStatus.status = SILMIN_SUCCESS;
                    putOutputDataToXmlFile(oFileName);
                    putStatusDataToXmlFile(sFileName);
                }
            
            free(outputFile);
}
*/

#import "rMELTSframework.h"

@implementation rMELTSframework

@end
