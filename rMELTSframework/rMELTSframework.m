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
//#include "param_struct_data.h"

int calculationMode = MODE_DEFAULT;
int quad_tol_modifier = 1;

void (*additionalOutput) (char *filename) = NULL;
char *addOutputFileName = NULL;

extern SilminState *bestState;

#define REALLOC(x, y) (((x) == NULL) ? malloc(y) : realloc((x), (y)))
#define REC 134

#import "rMELTSframework.h"

@implementation rMELTSframework

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

#pragma mark -
#pragma mark Class methods

+(NSUInteger)          MELTScalculationModeConstant { return MODE__MELTS;           }
+(NSUInteger)         pMELTScalculationModeConstant { return MODE_pMELTS;           }
+(NSUInteger)         xMELTScalculationModeConstant { return MODE_xMELTS;           }
+(NSUInteger)    MELTSandCO2calculationModeConstant { return MODE__MELTSandCO2;     }
+(NSUInteger)MELTSandCO2_H2OcalculationModeConstant { return MODE__MELTSandCO2_H2O; }

static int kSiO2, kTiO2, kAl2O3, kFe2O3, kCr2O3, kFeO, kMnO, kMgO, kNiO, kCoO, kCaO, kNa2O, kK2O, kP2O5, kH2O, kCO2;

+(void)initialize {
    for (int i=0; i<nc; i++) {
        if      (!strcmp(bulkSystem[i].label, "SiO2" )) kSiO2  = i;
        else if (!strcmp(bulkSystem[i].label, "TiO2" )) kTiO2  = i;
        else if (!strcmp(bulkSystem[i].label, "Al2O3")) kAl2O3 = i;
        else if (!strcmp(bulkSystem[i].label, "Fe2O3")) kFe2O3 = i;
        else if (!strcmp(bulkSystem[i].label, "Cr2O3")) kCr2O3 = i;
        else if (!strcmp(bulkSystem[i].label, "FeO"  )) kFeO   = i;
        else if (!strcmp(bulkSystem[i].label, "MnO"  )) kMnO   = i;
        else if (!strcmp(bulkSystem[i].label, "MgO"  )) kMgO   = i;
        else if (!strcmp(bulkSystem[i].label, "NiO"  )) kNiO   = i;
        else if (!strcmp(bulkSystem[i].label, "CoO"  )) kCoO   = i;
        else if (!strcmp(bulkSystem[i].label, "CaO"  )) kCaO   = i;
        else if (!strcmp(bulkSystem[i].label, "Na2O" )) kNa2O  = i;
        else if (!strcmp(bulkSystem[i].label, "K2O"  )) kK2O   = i;
        else if (!strcmp(bulkSystem[i].label, "P2O5" )) kP2O5  = i;
        else if (!strcmp(bulkSystem[i].label, "H2O"  )) kH2O   = i;
        else if (!strcmp(bulkSystem[i].label, "CO2"  )) kCO2   = i;
    }    
}

+(NSXMLDocument *)oxideListAsXMLDocument {
    NSXMLDocument *outputXMLDocument = [[NSXMLDocument alloc] init];
    NSXMLElement *root = [[NSXMLElement alloc] initWithName:@"MELTSWSoxides"];
    
    for (int i=0; i<nc; i++)
        [root addChild:[[NSXMLElement alloc] initWithName:@"Oxide" stringValue:[NSString stringWithFormat:@"%s", bulkSystem[i].label]]];
    
    [outputXMLDocument setRootElement:root];
    return outputXMLDocument;
}

+(NSXMLDocument *)phaseListAsXMLDocument:(NSString *)modelSelection {
    NSXMLDocument *outputXMLDocument = [[NSXMLDocument alloc] init];
    NSXMLElement *root = [[NSXMLElement alloc] initWithName:@"MELTSWSphases"];
    
    solids = meltsSolids;
    if      ([modelSelection isEqualToString:@"MELTS_v1.1.x"])  solids = meltsFluidSolids;
    else if ([modelSelection isEqualToString:@"MELTS_v1.2.x"])  solids = meltsFluidSolids;
    else if ([modelSelection isEqualToString:@"pMELTS_v5.6.1"]) solids = pMeltsSolids;
    for (int i=0; i<npc; i++) if (solids[i].type == PHASE)
        [root addChild:[[NSXMLElement alloc] initWithName:@"Phase" stringValue:[NSString stringWithFormat:@"%s", solids[i].label]]];
    
    [outputXMLDocument setRootElement:root];
    return outputXMLDocument;
}

#pragma mark -
#pragma mark Instance methods

typedef struct _nodeList {
    int node;
    SilminState *silminState;
    SilminState *previousSilminState;
} NodeList;

static NodeList *nodeList;
static int numberNodes;

static int compareNodes(const void *aPt, const void *bPt) {
    NodeList *a = (NodeList *) aPt;
    NodeList *b = (NodeList *) bPt;
    return (a->node - b->node);
}

static NodeList *getNodeListPointer(int node) {
    NodeList key;
    key.node = node;
    return (NodeList *) bsearch(&key, nodeList, (size_t) numberNodes, sizeof(struct _nodeList), compareNodes);
}

-(id)init:(NSString *)modelSelection {
    self = [super init];
    
    if (numberNodes != 0) {
        _nodeIndex = numberNodes;
        numberNodes++;
        nodeList = (NodeList *) realloc(nodeList, (size_t) numberNodes*sizeof(struct _nodeList));
        (nodeList[numberNodes-1]).silminState = NULL;
        (nodeList[numberNodes-1]).previousSilminState = NULL;
        (nodeList[numberNodes-1]).node = _nodeIndex;
        qsort(nodeList, (size_t) numberNodes, sizeof(struct _nodeList), compareNodes);
    }  else {
        _nodeIndex = 0;
        numberNodes = 1;
        nodeList = (NodeList *) realloc(nodeList, sizeof(struct _nodeList));
        (nodeList[0]).silminState = NULL;
        (nodeList[0]).previousSilminState = NULL;
        (nodeList[0]).node = _nodeIndex;
    }
    bestState = NULL;
    
    if ([modelSelection isEqualToString:@"MELTS_v1.0.x"]) {
        calculationMode = MODE__MELTS;
        liquid = meltsLiquid;
        solids = meltsSolids;
        nlc = meltsNlc;
        nls = meltsNls;
        npc = meltsNpc;
    } else if ([modelSelection isEqualToString:@"MELTS_v1.1.x"]) {
        calculationMode = MODE__MELTSandCO2;
        liquid = meltsFluidLiquid;
        solids = meltsFluidSolids;
        nlc = meltsFluidNlc;
        nls = meltsFluidNls;
        npc = meltsFluidNpc;
    } else if ([modelSelection isEqualToString:@"MELTS_v1.2.x"]) {
        calculationMode = MODE__MELTSandCO2_H2O;
        liquid = meltsFluidLiquid;
        solids = meltsFluidSolids;
        nlc = meltsFluidNlc;
        nls = meltsFluidNls;
        npc = meltsFluidNpc;
    } else if ([modelSelection isEqualToString:@"pMELTS_v5.6.1"]) {
        calculationMode = MODE_pMELTS;
        liquid = pMeltsLiquid;
        solids = pMeltsSolids;
        nlc = pMeltsNlc;
        nls = pMeltsNls;
        npc = pMeltsNpc;
    }
    
    // Should this always be executed?
    // Set a class static that tests if structures have been initialized and do the call ONLY if they have not.
    NSLog(@"Call to InitComputeDataStruct() for modelSelection = %@", modelSelection);
    InitComputeDataStruct();

    return self;
}

-(NSUInteger)parseAndLoadDataStructuresFromXMLDocument:(NSXMLDocument *) inputXMLDocument {
    NSXMLElement *rootElement = [inputXMLDocument rootElement];
    NSArray *levelOneChildren = [rootElement children];
    NSUInteger returnParam = GENERIC_CALC;
    
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    
    for (NSXMLElement *levelOneChild in levelOneChildren) {
        if ([[levelOneChild name] isEqualToString:@"initialize"]) {
            NSUInteger i, j, np;
            if (silminState != NULL) continue; // destroy the old state - nyi
            silminState = allocSilminStatePointer();
            nodePointer->silminState = silminState;
            for (i=0, np=0; i<npc; i++) if (solids[i].type == PHASE) { (silminState->incSolids)[np] = TRUE; np++; }
            (silminState->incSolids)[npc] = TRUE;
            silminState->nLiquidCoexist  = 1;
            silminState->fo2Path  = FO2_NONE;
            silminState->T = 0.0;
            silminState->P = 0.0;
            for (i=0, silminState->liquidMass=0.0; i<nc; i++) (silminState->bulkComp)[i] = 0.0;
            
            NSArray *levelTwoChildren = [levelOneChild children];
            for (NSXMLElement *levelTwoChild in levelTwoChildren) {
                NSString *name = [levelTwoChild name];
                if      ([name isEqualToString:@"SiO2" ]) (silminState->bulkComp)[kSiO2 ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kSiO2 ].mw;
                else if ([name isEqualToString:@"TiO2" ]) (silminState->bulkComp)[kTiO2 ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kTiO2 ].mw;
                else if ([name isEqualToString:@"Al2O3"]) (silminState->bulkComp)[kAl2O3] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kAl2O3].mw;
                else if ([name isEqualToString:@"Fe2O3"]) (silminState->bulkComp)[kFe2O3] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kFe2O3].mw;
                else if ([name isEqualToString:@"Cr2O3"]) (silminState->bulkComp)[kCr2O3] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kCr2O3].mw;
                else if ([name isEqualToString:@"FeO"  ]) (silminState->bulkComp)[kFeO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kFeO  ].mw;
                else if ([name isEqualToString:@"MnO"  ]) (silminState->bulkComp)[kMnO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kMnO  ].mw;
                else if ([name isEqualToString:@"MgO"  ]) (silminState->bulkComp)[kMgO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kMgO  ].mw;
                else if ([name isEqualToString:@"NiO"  ]) (silminState->bulkComp)[kNiO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kNiO  ].mw;
                else if ([name isEqualToString:@"CoO"  ]) (silminState->bulkComp)[kCoO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kCoO  ].mw;
                else if ([name isEqualToString:@"CaO"  ]) (silminState->bulkComp)[kCaO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kCaO  ].mw;
                else if ([name isEqualToString:@"Na2O" ]) (silminState->bulkComp)[kNa2O ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kNa2O ].mw;
                else if ([name isEqualToString:@"K2O"  ]) (silminState->bulkComp)[kK2O  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kK2O  ].mw;
                else if ([name isEqualToString:@"P2O5" ]) (silminState->bulkComp)[kP2O5 ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kP2O5 ].mw;
                else if ([name isEqualToString:@"H2O"  ]) (silminState->bulkComp)[kH2O  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kH2O  ].mw;
                else if ([name isEqualToString:@"CO2"  ]) (silminState->bulkComp)[kCO2  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kCO2  ].mw;
                silminState->liquidMass += [[levelTwoChild stringValue] doubleValue];
            }
            
            for (i=0; i<nlc; i++)
                for ((silminState->liquidComp)[0][i]=0.0, silminState->oxygen=0.0, j=0; j<nc; j++) {
                    (silminState->liquidComp)[0][i] += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i];
                    silminState->oxygen += (silminState->bulkComp)[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
                }
            
        } else if ([[levelOneChild name] isEqualToString:@"title"]) {
            const char *content = [[levelOneChild stringValue] cStringUsingEncoding:[NSString defaultCStringEncoding]];
            if (silminInputData.title != NULL) free(silminInputData.title);
            silminInputData.title = (char *) malloc((size_t) (strlen((char *) content)+1)*sizeof(char));
            (void) strcpy(silminInputData.title, (char *) content);
            
        } else if ([[levelOneChild name] isEqualToString:@"calculationMode"]) {
            NSString *value = [levelOneChild stringValue];
            if      ([value isEqualToString:@"findLiquidus"])    returnParam = RUN_LIQUIDUS_CALC;
            else if ([value isEqualToString:@"equilibrate"])     returnParam = RUN_EQUILIBRATE_CALC;
            else if ([value isEqualToString:@"findWetLiquidus"]) returnParam = RUN_WET_LIQUIDUS_CALC;
        
        } else if ([[levelOneChild name] isEqualToString:@"fractionateOnly"]) {
            NSString *content = [levelOneChild stringValue];
            if      ([content isEqualToString:@"fractionateSolids" ]) {                                      silminState->fractionateSol =  TRUE;                                      }
            else if ([content isEqualToString:@"fractionateFluids" ]) { silminState->fractionateFlu =  TRUE;                                                                           }
            else if ([content isEqualToString:@"fractionateLiquids"]) { silminState->fractionateFlu = FALSE; silminState->fractionateSol = FALSE; silminState->fractionateLiq =  TRUE; }
            
            if ((silminState->fractionateSol || silminState->fractionateFlu) && silminState->fracSComp == (double **) NULL) {
                silminState->fracSComp    = (double **) calloc((unsigned) npc, sizeof(double *));
                silminState->nFracCoexist = (int *) calloc((unsigned) npc, sizeof(int));
            }
            if (silminState->fractionateLiq && silminState->fracLComp == (double *) NULL) {
                silminState->fracLComp = (double *) calloc((unsigned) nlc, sizeof(double));
            }
            returnParam = RETURN_DO_FRACTIONATION;

        } else if ([[levelOneChild name] isEqualToString:@"changeBulk"]) {
            NSUInteger i, j;
            double *changeBC = (double *) calloc((size_t) nc, sizeof(double));
            NSArray *levelTwoChildren = [levelOneChild children];
            for (NSXMLElement *levelTwoChild in levelTwoChildren) {
                NSString *name = [levelTwoChild name];
                if      ([name isEqualToString:@"SiO2" ]) changeBC[kSiO2 ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kSiO2 ].mw;
                else if ([name isEqualToString:@"TiO2" ]) changeBC[kTiO2 ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kTiO2 ].mw;
                else if ([name isEqualToString:@"Al2O3"]) changeBC[kAl2O3] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kAl2O3].mw;
                else if ([name isEqualToString:@"Fe2O3"]) changeBC[kFe2O3] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kFe2O3].mw;
                else if ([name isEqualToString:@"Cr2O3"]) changeBC[kCr2O3] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kCr2O3].mw;
                else if ([name isEqualToString:@"FeO"  ]) changeBC[kFeO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kFeO  ].mw;
                else if ([name isEqualToString:@"MnO"  ]) changeBC[kMnO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kMnO  ].mw;
                else if ([name isEqualToString:@"MgO"  ]) changeBC[kMgO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kMgO  ].mw;
                else if ([name isEqualToString:@"NiO"  ]) changeBC[kNiO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kNiO  ].mw;
                else if ([name isEqualToString:@"CoO"  ]) changeBC[kCoO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kCoO  ].mw;
                else if ([name isEqualToString:@"CaO"  ]) changeBC[kCaO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kCaO  ].mw;
                else if ([name isEqualToString:@"Na2O" ]) changeBC[kNa2O ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kNa2O ].mw;
                else if ([name isEqualToString:@"K2O"  ]) changeBC[kK2O  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kK2O  ].mw;
                else if ([name isEqualToString:@"P2O5" ]) changeBC[kP2O5 ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kP2O5 ].mw;
                else if ([name isEqualToString:@"H2O"  ]) changeBC[kH2O  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kH2O  ].mw;
                else if ([name isEqualToString:@"CO2"  ]) changeBC[kCO2  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kCO2  ].mw;
                silminState->liquidMass += [[levelTwoChild stringValue] doubleValue];
            }
            
            for (i=0; i<nc; i++) (silminState->bulkComp)[i] += changeBC[i];
            for (i=0; i<nlc; i++)
                for (j=0; j<nc; j++) {
                    (silminState->liquidComp)[0][i] += changeBC[j]*(bulkSystem[j].oxToLiq)[i];
                    silminState->oxygen += changeBC[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
                }
            
            free(changeBC);
            
        } else if ([[levelOneChild name] isEqualToString:@"changeLiquid"]) {
            NSUInteger i, j;
            double *changeBC = (double *) calloc((size_t) nc, sizeof(double));
            NSArray *levelTwoChildren = [levelOneChild children];
            for (NSXMLElement *levelTwoChild in levelTwoChildren) {
                NSString *name = [levelTwoChild name];
                if      ([name isEqualToString:@"SiO2" ]) changeBC[kSiO2 ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kSiO2 ].mw;
                else if ([name isEqualToString:@"TiO2" ]) changeBC[kTiO2 ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kTiO2 ].mw;
                else if ([name isEqualToString:@"Al2O3"]) changeBC[kAl2O3] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kAl2O3].mw;
                else if ([name isEqualToString:@"Fe2O3"]) changeBC[kFe2O3] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kFe2O3].mw;
                else if ([name isEqualToString:@"Cr2O3"]) changeBC[kCr2O3] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kCr2O3].mw;
                else if ([name isEqualToString:@"FeO"  ]) changeBC[kFeO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kFeO  ].mw;
                else if ([name isEqualToString:@"MnO"  ]) changeBC[kMnO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kMnO  ].mw;
                else if ([name isEqualToString:@"MgO"  ]) changeBC[kMgO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kMgO  ].mw;
                else if ([name isEqualToString:@"NiO"  ]) changeBC[kNiO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kNiO  ].mw;
                else if ([name isEqualToString:@"CoO"  ]) changeBC[kCoO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kCoO  ].mw;
                else if ([name isEqualToString:@"CaO"  ]) changeBC[kCaO  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kCaO  ].mw;
                else if ([name isEqualToString:@"Na2O" ]) changeBC[kNa2O ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kNa2O ].mw;
                else if ([name isEqualToString:@"K2O"  ]) changeBC[kK2O  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kK2O  ].mw;
                else if ([name isEqualToString:@"P2O5" ]) changeBC[kP2O5 ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kP2O5 ].mw;
                else if ([name isEqualToString:@"H2O"  ]) changeBC[kH2O  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kH2O  ].mw;
                else if ([name isEqualToString:@"CO2"  ]) changeBC[kCO2  ] = [[levelTwoChild stringValue] doubleValue]/bulkSystem[kCO2  ].mw;
                silminState->liquidMass += [[levelTwoChild stringValue] doubleValue];
            }
            
            for (i=0; i<nc; i++) (silminState->bulkComp)[i] += changeBC[i];
            for (i=0; i<nlc; i++)
                for (j=0; j<nc; j++) {
                    (silminState->liquidComp)[0][i] += changeBC[j]*(bulkSystem[j].oxToLiq)[i];
                    silminState->oxygen += changeBC[j]*(bulkSystem[j].oxToLiq)[i]*(oxygen.liqToOx)[i];
                }
            
            free(changeBC);
            returnParam = RETURN_WITHOUT_CALC;
            
        } else if ([[levelOneChild name] isEqualToString:@"constraints"]) {
            NSXMLNode *levelTwoChild = [[levelOneChild children] objectAtIndex:0]; // There can be only one
            
            if ([[levelTwoChild name]isEqualToString:@"setTP"]) {
                double oldInitialT = silminState->T;
                silminState->isenthalpic = FALSE; silminState->refEnthalpy = 0.0;
                silminState->isentropic  = FALSE; silminState->refEntropy  = 0.0;
                silminState->isochoric   = FALSE; silminState->refVolume   = 0.0;
                
                NSArray *levelThreeChildren = [levelTwoChild children];
                for (NSXMLElement *levelThreeChild in levelThreeChildren) {
                    NSString *name = [levelThreeChild name];
                    if ([name isEqualToString:@"initialT"]) {
                        silminState->T         = [[levelThreeChild stringValue] doubleValue] + 273.15;
                        silminState->dspTstart = [[levelThreeChild stringValue] doubleValue] + 273.15;
                        silminState->dspTstop  = [[levelThreeChild stringValue] doubleValue] + 273.15;
                        silminState->dspTinc   = 0.0;
                    }
                    else if ([name isEqualToString:@"finalT"  ]) silminState->dspTstop = [[levelThreeChild stringValue] doubleValue] + 273.15;
                    else if ([name isEqualToString:@"incT"    ]) silminState->dspTinc  = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"initialP"]) {
                        silminState->P         = [[levelThreeChild stringValue] doubleValue];
                        silminState->dspPstart = [[levelThreeChild stringValue] doubleValue];
                        silminState->dspPstop  = [[levelThreeChild stringValue] doubleValue];
                        silminState->dspPinc   = 0.0;
                        silminState->dspDPDt   = 0.0;
                    }
                    else if ([name isEqualToString:@"finalP"  ]) silminState->dspPstop = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"incP"    ]) silminState->dspPinc  = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"dpdt"    ]) silminState->dspDPDt  = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"fo2path" ]) {
                        NSString *value = [levelThreeChild stringValue];
                        if      ([value isEqualToString:@"none"]) silminState->fo2Path  = FO2_NONE;
                        else if ([value isEqualToString:@"fmq" ]) silminState->fo2Path  = FO2_QFM;
                        else if ([value isEqualToString:@"coh" ]) silminState->fo2Path  = FO2_COH;
                        else if ([value isEqualToString:@"nno" ]) silminState->fo2Path  = FO2_NNO;
                        else if ([value isEqualToString:@"iw"  ]) silminState->fo2Path  = FO2_IW;
                        else if ([value isEqualToString:@"hm"  ]) silminState->fo2Path  = FO2_HM;
                    }
                    else if ([name isEqualToString:@"fo2Offset" ]) silminState->fo2Delta = [[levelThreeChild stringValue] doubleValue];
                }
                
                if ((fabs(silminState->T - oldInitialT) < 1.0e-6) && (fabs(silminState->T - silminState->dspTstop) > 1.0e-6)) {
                    if (fabs(silminState->T - silminState->dspTstop) > fabs(silminState->dspTinc)) {
                        if (silminState->T > silminState->dspTstop) {
                            silminState->T         -= fabs(silminState->dspTinc);
                            silminState->dspTstart -= fabs(silminState->dspTinc);
                        } else {
                            silminState->T         += fabs(silminState->dspTinc);
                            silminState->dspTstart += fabs(silminState->dspTinc);
                        }
                    } else {
                        if (silminState->T > silminState->dspTstop) {
                            silminState->T         -= 1.0e-6;
                            silminState->dspTstart -= 1.0e-6;
                        } else {
                            silminState->T         += 1.0e-6;
                            silminState->dspTstart += 1.0e-6;
                        }
                    }
                }
                
            } else if ([[levelTwoChild name]isEqualToString:@"setTV"]) {
                silminState->isenthalpic = FALSE; silminState->refEnthalpy = 0.0;
                silminState->isentropic  = FALSE; silminState->refEntropy  = 0.0;
                silminState->isochoric   = TRUE;  silminState->refVolume   = 0.0;
                
                NSArray *levelThreeChildren = [levelTwoChild children];
                for (NSXMLElement *levelThreeChild in levelThreeChildren) {
                    NSString *name = [levelThreeChild name];
                    if ([name isEqualToString:@"initialT"]) {
                        silminState->T         = [[levelThreeChild stringValue] doubleValue] + 273.15;
                        silminState->dspTstart = [[levelThreeChild stringValue] doubleValue] + 273.15;
                        silminState->dspTstop  = [[levelThreeChild stringValue] doubleValue] + 273.15;
                        silminState->dspTinc   = 0.0;
                    }
                    else if ([name isEqualToString:@"finalT"  ]) silminState->dspTstop  = [[levelThreeChild stringValue] doubleValue] + 273.15;
                    else if ([name isEqualToString:@"incT"    ]) silminState->dspTinc   = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"initialV"]) silminState->refVolume = [[levelThreeChild stringValue] doubleValue]/10.0;
                    else if ([name isEqualToString:@"finalV"  ]) silminState->dspVstop  = [[levelThreeChild stringValue] doubleValue]/10.0;
                    else if ([name isEqualToString:@"incV"    ]) silminState->dspVinc   = [[levelThreeChild stringValue] doubleValue]/10.0;
                    else if ([name isEqualToString:@"dvdt"    ]) silminState->dspDVDt   = [[levelThreeChild stringValue] doubleValue]/10.0;
                    else if ([name isEqualToString:@"fo2path" ]) {
                        NSString *value = [levelThreeChild stringValue];
                        if      ([value isEqualToString:@"none"]) silminState->fo2Path  = FO2_NONE;
                        else if ([value isEqualToString:@"fmq" ]) silminState->fo2Path  = FO2_QFM;
                        else if ([value isEqualToString:@"coh" ]) silminState->fo2Path  = FO2_COH;
                        else if ([value isEqualToString:@"nno" ]) silminState->fo2Path  = FO2_NNO;
                        else if ([value isEqualToString:@"iw"  ]) silminState->fo2Path  = FO2_IW;
                        else if ([value isEqualToString:@"hm"  ]) silminState->fo2Path  = FO2_HM;
                    }
                    else if ([name isEqualToString:@"fo2Offset" ]) silminState->fo2Delta = [[levelThreeChild stringValue] doubleValue];
                }
                
            } else if ([[levelTwoChild name]isEqualToString:@"setHP"]) {
                silminState->isenthalpic = TRUE;
                silminState->isentropic  = FALSE;
                silminState->isochoric   = FALSE;
                
                NSArray *levelThreeChildren = [levelTwoChild children];
                for (NSXMLElement *levelThreeChild in levelThreeChildren) {
                    NSString *name = [levelThreeChild name];
                    if      ([name isEqualToString:@"initialH"]) silminState->refEnthalpy = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"finalH"  ]) silminState->dspHstop    = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"incH"    ]) silminState->dspHinc     = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"initialP"]) {
                        silminState->P         = [[levelThreeChild stringValue] doubleValue];
                        silminState->dspPstart = [[levelThreeChild stringValue] doubleValue];
                        silminState->dspPstop  = [[levelThreeChild stringValue] doubleValue];
                        silminState->dspPinc   = 0.0;
                    }
                    else if ([name isEqualToString:@"finalP"  ]) silminState->dspPstop    = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"incP"    ]) silminState->dspPinc     = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"dpdh"    ]) silminState->dspDPDH     = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"fo2path" ]) {
                        NSString *value = [levelThreeChild stringValue];
                        if      ([value isEqualToString:@"none"]) silminState->fo2Path  = FO2_NONE;
                        else if ([value isEqualToString:@"fmq" ]) silminState->fo2Path  = FO2_QFM;
                        else if ([value isEqualToString:@"coh" ]) silminState->fo2Path  = FO2_COH;
                        else if ([value isEqualToString:@"nno" ]) silminState->fo2Path  = FO2_NNO;
                        else if ([value isEqualToString:@"iw"  ]) silminState->fo2Path  = FO2_IW;
                        else if ([value isEqualToString:@"hm"  ]) silminState->fo2Path  = FO2_HM;
                    }
                    else if ([name isEqualToString:@"fo2Offset" ]) silminState->fo2Delta = [[levelThreeChild stringValue] doubleValue];
                }
                
                
            } else if ([[levelTwoChild name]isEqualToString:@"setSP"]) {
                silminState->isenthalpic = FALSE; silminState->refEnthalpy = 0.0;
                silminState->isentropic  = TRUE;  silminState->refEntropy  = 0.0;
                silminState->isochoric   = FALSE; silminState->refVolume   = 0.0;
                
                NSArray *levelThreeChildren = [levelTwoChild children];
                for (NSXMLElement *levelThreeChild in levelThreeChildren) {
                    NSString *name = [levelThreeChild name];
                    if      ([name isEqualToString:@"initialS"]) silminState->refEntropy = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"finalS"  ]) silminState->dspSstop   = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"incS"    ]) silminState->dspSinc    = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"initialP"]) {
                        silminState->P         = [[levelThreeChild stringValue] doubleValue];
                        silminState->dspPstart = [[levelThreeChild stringValue] doubleValue];
                        silminState->dspPstop  = [[levelThreeChild stringValue] doubleValue];
                        silminState->dspPinc   = 0.0;
                    }
                    else if ([name isEqualToString:@"finalP"  ]) silminState->dspPstop   = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"incP"    ]) silminState->dspPinc    = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"dsdh"    ]) silminState->dspDPDS    = [[levelThreeChild stringValue] doubleValue];
                    else if ([name isEqualToString:@"fo2path" ]) {
                        NSString *value = [levelThreeChild stringValue];
                        if      ([value isEqualToString:@"none"]) silminState->fo2Path  = FO2_NONE;
                        else if ([value isEqualToString:@"fmq" ]) silminState->fo2Path  = FO2_QFM;
                        else if ([value isEqualToString:@"coh" ]) silminState->fo2Path  = FO2_COH;
                        else if ([value isEqualToString:@"nno" ]) silminState->fo2Path  = FO2_NNO;
                        else if ([value isEqualToString:@"iw"  ]) silminState->fo2Path  = FO2_IW;
                        else if ([value isEqualToString:@"hm"  ]) silminState->fo2Path  = FO2_HM;
                    }
                    else if ([name isEqualToString:@"fo2Offset" ]) silminState->fo2Delta = [[levelThreeChild stringValue] doubleValue];
                }
            }
            
        } else if ([[levelOneChild name] isEqualToString:@"suppressPhase"]) {
            const char *value = [[levelOneChild stringValue] cStringUsingEncoding:[NSString defaultCStringEncoding]];
            NSUInteger i, j;
            for (i=0, j=0; i<npc; i++) if (solids[i].type == PHASE) {
                if (!strcmp(value, solids[i].label)) {
                    if (solids[i].nr == 0 || (solids[i].nr > 0 && solids[i].convert != NULL)) (silminState->incSolids)[j] = FALSE;
                    break;
                }
                j++;
            }
            
        } else if ([[levelOneChild name] isEqualToString:@"fractionationMode"]) {
            NSString *content = [levelOneChild stringValue];
            if      ([content isEqualToString:@"fractionateSolids" ]) {                                      silminState->fractionateSol =  TRUE;                                      }
            else if ([content isEqualToString:@"fractionateFluids" ]) { silminState->fractionateFlu =  TRUE;                                                                           }
            else if ([content isEqualToString:@"fractionateLiquids"]) { silminState->fractionateFlu = FALSE; silminState->fractionateSol = FALSE; silminState->fractionateLiq =  TRUE; }
            else if ([content isEqualToString:@"fractionateNone"   ]) { silminState->fractionateFlu = FALSE; silminState->fractionateSol = FALSE; silminState->fractionateLiq = FALSE; }
            
            if ((silminState->fractionateSol || silminState->fractionateFlu) && silminState->fracSComp == (double **) NULL) {
                silminState->fracSComp    = (double **) calloc((unsigned) npc, sizeof(double *));
                silminState->nFracCoexist = (int *) calloc((unsigned) npc, sizeof(int));
            }
            if (silminState->fractionateLiq && silminState->fracLComp == (double *) NULL) {
                silminState->fracLComp = (double *) calloc((unsigned) nlc, sizeof(double));
            }
        
        } else if ([[levelOneChild name] isEqualToString:@"multLiquids"]) {
            if ([[levelOneChild stringValue] isEqualToString:@"true"]) silminState->multipleLiqs = TRUE;
            
        } else if ([[levelOneChild name] isEqualToString:@"assimilant"]) {
            silminState->assimilate = TRUE;
            silminState->dspAssimUnits = ASSIM_PADB_UNITS_WEIGHT;
            if (silminState->nDspAssimComp == NULL) silminState->nDspAssimComp = (int *)     calloc((unsigned) (npc+nc), sizeof(int));
            if (silminState->dspAssimComp  == NULL) silminState->dspAssimComp  = (double **) calloc((unsigned) (npc+nc), sizeof(double *));
            
            NSArray *levelTwoChildren = [levelOneChild children];
            for (NSXMLElement *levelTwoChild in levelTwoChildren) {
                if      ([[levelTwoChild name] isEqualToString:@"temperature"]) silminState->dspAssimT    = [[levelTwoChild stringValue] doubleValue];
                else if ([[levelTwoChild name] isEqualToString:@"increments" ]) silminState->dspAssimInc  = [[levelTwoChild stringValue] intValue];
                else if ([[levelTwoChild name] isEqualToString:@"mass"       ]) silminState->dspAssimMass = [[levelTwoChild stringValue] doubleValue];
                else if ([[levelTwoChild name] isEqualToString:@"units"      ]) NSLog(@"Not Yet Implemented, units");
                else if ([[levelTwoChild name] isEqualToString:@"phase"      ]) {
                    NSXMLNode *levelThreeChild = [[levelTwoChild children] objectAtIndex:0]; // there may be only one
                    if ([[levelThreeChild name] isEqualToString:@"amorphous"] || [[levelThreeChild name] isEqualToString:@"liquid"]) {
                        NSArray *levelFourChildren = [levelThreeChild children];
                        for (NSXMLElement *levelFourChild in levelFourChildren) {
                            NSString *name = [levelFourChild name];
                            double value = [[levelFourChild stringValue] doubleValue];
                            if      ([name isEqualToString:@"massFraction"]) NSLog(@"Not Yet Implemented, massFraction value = %lf", value);
                            else if ([name isEqualToString:@"SiO2"        ]) NSLog(@"Not Yet Implemented, SiO2         value = %lf", value);
                            else if ([name isEqualToString:@"TiO2"        ]) NSLog(@"Not Yet Implemented, TiO2         value = %lf", value);
                            else if ([name isEqualToString:@"Al2O3"       ]) NSLog(@"Not Yet Implemented, Al2O3        value = %lf", value);
                            else if ([name isEqualToString:@"Fe2O3"       ]) NSLog(@"Not Yet Implemented, Fe2O3        value = %lf", value);
                            else if ([name isEqualToString:@"Cr2O3"       ]) NSLog(@"Not Yet Implemented, Cr2O3        value = %lf", value);
                            else if ([name isEqualToString:@"FeO"         ]) NSLog(@"Not Yet Implemented, FeO          value = %lf", value);
                            else if ([name isEqualToString:@"MnO"         ]) NSLog(@"Not Yet Implemented, MnO          value = %lf", value);
                            else if ([name isEqualToString:@"MgO"         ]) NSLog(@"Not Yet Implemented, MgO          value = %lf", value);
                            else if ([name isEqualToString:@"NiO"         ]) NSLog(@"Not Yet Implemented, NiO          value = %lf", value);
                            else if ([name isEqualToString:@"CoO"         ]) NSLog(@"Not Yet Implemented, CoO          value = %lf", value);
                            else if ([name isEqualToString:@"CaO"         ]) NSLog(@"Not Yet Implemented, CaO          value = %lf", value);
                            else if ([name isEqualToString:@"Na2O"        ]) NSLog(@"Not Yet Implemented, Na2O         value = %lf", value);
                            else if ([name isEqualToString:@"K2O"         ]) NSLog(@"Not Yet Implemented, K2O          value = %lf", value);
                            else if ([name isEqualToString:@"P2O5"        ]) NSLog(@"Not Yet Implemented, P2O5         value = %lf", value);
                            else if ([name isEqualToString:@"H2O"         ]) NSLog(@"Not Yet Implemented, H2O          value = %lf", value);
                            else if ([name isEqualToString:@"CO2"         ]) NSLog(@"Not Yet Implemented, CO2          value = %lf", value);
                        }
                    } else if ([[levelThreeChild name] isEqualToString:@"solid"]) {
                        NSArray *levelFourChildren = [levelThreeChild children];
                        for (NSXMLElement *levelFourChild in levelFourChildren) {
                            NSString *name = [levelFourChild name];
                            if      ([name isEqualToString:@"label"       ]) NSLog(@"Not Yet Implemented, label = %@", [levelFourChild stringValue]);
                            else if ([name isEqualToString:@"massFraction"]) NSLog(@"Not Yet Implemented, massFraction value = %lf", [[levelFourChild stringValue] doubleValue]);
                            else if ([name isEqualToString:@"component"   ]) {
                                NSArray *levelFiveChildren = [levelFourChild children];
                                for (NSXMLElement *levelFiveChild in levelFiveChildren) {
                                    if      ([[levelFiveChild name] isEqualToString:@"label"  ]) NSLog(@"Not Yet Implemented, label   = %@", [levelFiveChild stringValue]);
                                    else if ([[levelFiveChild name] isEqualToString:@"molFrac"]) NSLog(@"Not Yet Implemented, molFrac = %@", [levelFiveChild stringValue]);
                                }
                            }
                        }
                    }
                }
                
            }
        }

    }
    
    return returnParam;
}

-(NSXMLDocument *)writeDataStructuresToXMLDocument:(NSString *)sessionID {
    NSArray *statusArray = [NSArray arrayWithObjects:
                            @"Success: Find liquidus",                                  // LIQUIDUS_SUCCESS
                            @"Error: Maximum temperature in Find Liquidus",             // LIQUIDUS_MAX_T
                            @"Error: Minimum temperature in Find Liquidus",             // LIQUIDUS_MIN_T
                            @"Error: Maximum time limit exceeded in Find Liquidus",     // LIQUIDUS_TIME
                            @"Error: Cannot specify multiple liquids in Find Liquidus", // LIQUIDUS_MULTIPLE
                            @"Success: Equilibrate",                                    // SILMIN_SUCCESS
                            @"Error: Quadratic Iterations exceeded",                    // SILMIN_QUAD_MAX
                            @"Error: Zero steplength computed in linear search",        // SILMIN_LIN_ZERO
                            @"Error: Maximum iterations exceeded in linear search",     // SILMIN_LIN_MAX
                            @"Error: Cannot add a solid phase to liquid(+solids)",      // SILMIN_ADD_LIQUID_1
                            @"Error: Cannot add a solid phase to solid(s)",             // SILMIN_ADD_LIQUID_2
                            @"Error: Cannot add a liquid phase to solid(s)",            // SILMIN_ADD_LIQUID_3
                            @"Error: Phase rule violation (rank deficiency)",           // SILMIN_RANK
                            @"Error: Maximum time limit exceeded in Silmin",            // SILMIN_TIME
                            @"Error: Internal",                                         // GENERIC_INTERNAL_ERROR,
                            nil];
    
    NSXMLDocument *outputXMLDocument = [[NSXMLDocument alloc] init];
    NSXMLElement *root = [[NSXMLElement alloc] initWithName:@"MELTSoutput"];
    
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    SilminState *previousSilminState = nodePointer->previousSilminState;
        
    [root addChild:[[NSXMLElement alloc] initWithName:@"status" stringValue:[statusArray objectAtIndex:meltsStatus.status]]];

     size_t len;
     time_t tp;
     char * cOut;
     double gLiq = 0.0, hLiq = 0.0, sLiq = 0.0, vLiq = 0.0, dvdtLiq=0.0, dvdpLiq=0.0, d2vdt2Liq=0.0, d2vdtdpLiq=0.0, d2vdp2Liq=0.0, cpLiq = 0.0, mLiq = 0.0, viscosity = 0.0;
     double totalMass=0.0, totalGibbsEnergy=0.0, totalEnthalpy=0.0, totalEntropy=0.0, totalVolume=0.0, totalHeatCapacity=0.0;
     double totalDvdt=0.0, totalDvdp=0.0, totalD2vdt2=0.0, totalD2vdtdp=0.0, totalD2vdp2=0.0;
     static double *m, *r, *oxVal;
     int i, j;
     
     if (m == NULL)         m = (double *) malloc((size_t)      nc*sizeof(double));
     if (r == NULL)         r = (double *) malloc((size_t) (nlc-1)*sizeof(double));
     if (oxVal == NULL) oxVal = (double *) malloc((size_t)      nc*sizeof(double));
          
     (void) time(&tp);
     cOut = ctime(&tp);
     len = strlen(cOut);
     cOut[len-1] = '\0';
    
    [root addChild:[[NSXMLElement alloc] initWithName:@"sessionID"  stringValue:[NSString stringWithFormat:@"%@", sessionID]]];
    [root addChild:[[NSXMLElement alloc] initWithName:@"title"      stringValue:[NSString stringWithFormat:@"%s", silminInputData.title]]];
    [root addChild:[[NSXMLElement alloc] initWithName:@"time"       stringValue:[NSString stringWithFormat:@"%s", cOut]]];
    NSString *releaseString = @"MELTS Web Services, MELTS v.1.0.x";
    if      (calculationMode == MODE__MELTSandCO2)     releaseString = @"MELTS Web Services, MELTS v.1.1.x";
    else if (calculationMode == MODE__MELTSandCO2_H2O) releaseString = @"MELTS Web Services, MELTS v.1.2.x";
    else if (calculationMode == MODE_pMELTS)           releaseString = @"MELTS Web Services, pMELTS v.5.6.1";
    [root addChild:[[NSXMLElement alloc] initWithName:@"release"    stringValue:releaseString]];
    [root addChild:[[NSXMLElement alloc] initWithName:@"buildDate"  stringValue:[NSString stringWithFormat:@"%s", __DATE__]]];
    [root addChild:[[NSXMLElement alloc] initWithName:@"buildTime"  stringValue:[NSString stringWithFormat:@"%s", __TIME__]]];
    
    [root addChild:[[NSXMLElement alloc] initWithName:@"temperature" stringValue:[NSString stringWithFormat:@"%.20g", silminState->T-273.15]]];
    [root addChild:[[NSXMLElement alloc] initWithName:@"pressure"    stringValue:[NSString stringWithFormat:@"%.20g", silminState->P]]];
    [root addChild:[[NSXMLElement alloc] initWithName:@"log_fO2"     stringValue:[NSString stringWithFormat:@"%.20g", silminState->fo2]]];
    [root addChild:[[NSXMLElement alloc] initWithName:@"deltaHM"     stringValue:[NSString stringWithFormat:@"%.20g", silminState->fo2 - (getlog10fo2(silminState->T, silminState->P, FO2_HM)  - silminState->fo2Delta)]]];
    [root addChild:[[NSXMLElement alloc] initWithName:@"deltaNNO"    stringValue:[NSString stringWithFormat:@"%.20g", silminState->fo2 - (getlog10fo2(silminState->T, silminState->P, FO2_NNO) - silminState->fo2Delta)]]];
    [root addChild:[[NSXMLElement alloc] initWithName:@"deltaFMQ"    stringValue:[NSString stringWithFormat:@"%.20g", silminState->fo2 - (getlog10fo2(silminState->T, silminState->P, FO2_QFM) - silminState->fo2Delta)]]];
    [root addChild:[[NSXMLElement alloc] initWithName:@"deltaCOH"    stringValue:[NSString stringWithFormat:@"%.20g", silminState->fo2 - (getlog10fo2(silminState->T, silminState->P, FO2_COH) - silminState->fo2Delta)]]];
    [root addChild:[[NSXMLElement alloc] initWithName:@"deltaIW"     stringValue:[NSString stringWithFormat:@"%.20g", silminState->fo2 - (getlog10fo2(silminState->T, silminState->P, FO2_IW)  - silminState->fo2Delta)]]];
    
    
    if (silminState->liquidMass != 0.0) {
        int nl;
        
        for (nl=0; nl<silminState->nLiquidCoexist; nl++) {
            double moles, oxSum;
            double gibbsEnergy, enthalpy, entropy, volume, dvdt, dvdp, d2vdt2, d2vdtdp, d2vdp2, heatCapacity;
            
            NSXMLElement *liquidElement = [[NSXMLElement alloc] initWithName:@"liquid"];
            
            conLiq(SECOND, THIRD, silminState->T, silminState->P, NULL, silminState->liquidComp[nl], r, NULL, NULL, NULL, NULL);
            
            gmixLiq (FIRST, silminState->T, silminState->P, r, &gibbsEnergy,  NULL, NULL);
            hmixLiq (FIRST, silminState->T, silminState->P, r, &enthalpy,	  NULL);
            smixLiq (FIRST, silminState->T, silminState->P, r, &entropy,	  NULL, NULL, NULL);
            vmixLiq (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, silminState->T, silminState->P, r, &volume,	NULL, NULL, &dvdt, &dvdp, &d2vdt2, &d2vdtdp, &d2vdp2, NULL, NULL, NULL);
            cpmixLiq(FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
            visLiq  (FIRST, silminState->T, silminState->P, r, &viscosity);
            
            for (i=0, moles=0.0; i<nlc; i++) moles +=  (silminState->liquidComp)[nl][i];
            gibbsEnergy  *= moles;
            enthalpy     *= moles;
            entropy      *= moles;
            volume	     *= moles;
            dvdt	     *= moles;
            dvdp	     *= moles;
            d2vdt2	     *= moles;
            d2vdtdp	     *= moles;
            d2vdp2	     *= moles;
            heatCapacity *= moles;
            
            for (i=0; i<nlc; i++) {
                gibbsEnergy  += (silminState->liquidComp)[nl][i]*(liquid[i].cur).g;
                enthalpy     += (silminState->liquidComp)[nl][i]*(liquid[i].cur).h;
                entropy      += (silminState->liquidComp)[nl][i]*(liquid[i].cur).s;
                volume       += (silminState->liquidComp)[nl][i]*(liquid[i].cur).v;
                dvdt         += (silminState->liquidComp)[nl][i]*(liquid[i].cur).dvdt;
                dvdp         += (silminState->liquidComp)[nl][i]*(liquid[i].cur).dvdp;
                d2vdt2       += (silminState->liquidComp)[nl][i]*(liquid[i].cur).d2vdt2;
                d2vdtdp      += (silminState->liquidComp)[nl][i]*(liquid[i].cur).d2vdtdp;
                d2vdp2       += (silminState->liquidComp)[nl][i]*(liquid[i].cur).d2vdp2;
                heatCapacity += (silminState->liquidComp)[nl][i]*(liquid[i].cur).cp;
            }
            
            for (i=0, oxSum=0.0; i<nc; i++) {
                for (j=0, oxVal[i]=0.0; j<nlc; j++) oxVal[i] += (liquid[j].liqToOx)[i]*(silminState->liquidComp)[nl][j];
                oxVal[i] *= bulkSystem[i].mw;
                oxSum	   += oxVal[i];
            }
            if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
            
            gLiq += gibbsEnergy; hLiq += enthalpy; sLiq += entropy; vLiq += volume; dvdtLiq += dvdt; dvdpLiq += dvdp; d2vdt2Liq += d2vdt2; d2vdtdpLiq += d2vdtdp; d2vdp2Liq += d2vdp2; cpLiq += heatCapacity; mLiq += oxSum;
            
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"mass"            stringValue:[NSString stringWithFormat:@"%.20g", oxSum]]];
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"density"         stringValue:[NSString stringWithFormat:@"%.20g", (volume == 0.0) ? 0.0 : oxSum/(10.0*volume)]]];
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"viscosity"       stringValue:[NSString stringWithFormat:@"%.20g", viscosity]]];
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", gibbsEnergy]]];
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"        stringValue:[NSString stringWithFormat:@"%.20g", enthalpy]]];
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"         stringValue:[NSString stringWithFormat:@"%.20g", entropy]]];
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"volume"          stringValue:[NSString stringWithFormat:@"%.20g", volume*10.0]]];
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt"            stringValue:[NSString stringWithFormat:@"%.20g", dvdt*10.0]]];
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"            stringValue:[NSString stringWithFormat:@"%.20g", dvdp*10.0]]];
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2"          stringValue:[NSString stringWithFormat:@"%.20g", d2vdt2*10.0]]];
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp"         stringValue:[NSString stringWithFormat:@"%.20g", d2vdtdp*10.0]]];
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2"          stringValue:[NSString stringWithFormat:@"%.20g", d2vdp2*10.0]]];
            [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"    stringValue:[NSString stringWithFormat:@"%.20g", heatCapacity]]];
            
            for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                [liquidElement addChild:[[NSXMLElement alloc] initWithName:[NSString stringWithFormat:@"%s", bulkSystem[i].label] stringValue:[NSString stringWithFormat:@"%.20g", oxVal[i]*100.0]]];
            
            [root addChild:liquidElement];
        }
    }
     
    for (j=0, totalMass=0.0, totalGibbsEnergy=0.0, totalEnthalpy=0.0, totalEntropy=0.0, totalVolume=0.0, totalDvdt=0.0, totalDvdp=0.0, totalD2vdt2=0.0, totalD2vdtdp=0.0, totalD2vdp2=0.0, totalHeatCapacity=0.0; j<npc; j++) {
        int ns;
        for (ns=0; ns<(silminState->nSolidCoexist)[j]; ns++) {
            double oxSum, mass, gibbsEnergy, enthalpy, entropy, volume, dvdt, dvdp, d2vdt2, d2vdtdp, d2vdp2, heatCapacity;
            
            NSXMLElement *solidElement = [[NSXMLElement alloc] initWithName:@"solid"];
            
            if (solids[j].na == 1) {
                mass  	           = (silminState->solidComp)[j][ns]*solids[j].mw;
                gibbsEnergy	       = (silminState->solidComp)[j][ns]*(solids[j].cur).g;
                enthalpy	       = (silminState->solidComp)[j][ns]*(solids[j].cur).h;
                entropy	           = (silminState->solidComp)[j][ns]*(solids[j].cur).s;
                volume	           = (silminState->solidComp)[j][ns]*(solids[j].cur).v;
                dvdt	           = (silminState->solidComp)[j][ns]*(solids[j].cur).dvdt;
                dvdp	           = (silminState->solidComp)[j][ns]*(solids[j].cur).dvdp;
                d2vdt2	           = (silminState->solidComp)[j][ns]*(solids[j].cur).d2vdt2;
                d2vdtdp	           = (silminState->solidComp)[j][ns]*(solids[j].cur).d2vdtdp;
                d2vdp2	           = (silminState->solidComp)[j][ns]*(solids[j].cur).d2vdp2;
                heatCapacity       = (silminState->solidComp)[j][ns]*(solids[j].cur).cp;
                totalMass	      += (silminState->solidComp)[j][ns]*solids[j].mw;
                totalGibbsEnergy  += (silminState->solidComp)[j][ns]*(solids[j].cur).g;
                totalEnthalpy     += (silminState->solidComp)[j][ns]*(solids[j].cur).h;
                totalEntropy      += (silminState->solidComp)[j][ns]*(solids[j].cur).s;
                totalVolume	      += (silminState->solidComp)[j][ns]*(solids[j].cur).v;
                totalDvdt	      += (silminState->solidComp)[j][ns]*(solids[j].cur).dvdt;
                totalDvdp	      += (silminState->solidComp)[j][ns]*(solids[j].cur).dvdp;
                totalD2vdt2	      += (silminState->solidComp)[j][ns]*(solids[j].cur).d2vdt2;
                totalD2vdtdp	  += (silminState->solidComp)[j][ns]*(solids[j].cur).d2vdtdp;
                totalD2vdp2	      += (silminState->solidComp)[j][ns]*(solids[j].cur).d2vdp2;
                totalHeatCapacity += (silminState->solidComp)[j][ns]*(solids[j].cur).cp;
                
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"name"            stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"formula"         stringValue:[NSString stringWithFormat:@"%s",   solids[j].formula]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"mass" 	         stringValue:[NSString stringWithFormat:@"%.20g", mass]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"density"	     stringValue:[NSString stringWithFormat:@"%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume)]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", gibbsEnergy]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"	     stringValue:[NSString stringWithFormat:@"%.20g", enthalpy]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"	     stringValue:[NSString stringWithFormat:@"%.20g", entropy]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"volume"	         stringValue:[NSString stringWithFormat:@"%.20g", volume*10.0]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt"	         stringValue:[NSString stringWithFormat:@"%.20g", dvdt*10.0]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"	         stringValue:[NSString stringWithFormat:@"%.20g", dvdp*10.0]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2"	         stringValue:[NSString stringWithFormat:@"%.20g", d2vdt2*10.0]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp"	     stringValue:[NSString stringWithFormat:@"%.20g", d2vdtdp*10.0]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2"	         stringValue:[NSString stringWithFormat:@"%.20g", d2vdp2*10.0]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"    stringValue:[NSString stringWithFormat:@"%.20g", heatCapacity]]];
                
                for (i=0, oxSum=0.0; i<nc; i++) {
                    oxVal[i]  = (solids[j].solToOx)[i]*bulkSystem[i].mw;
                    oxSum    += oxVal[i];
                }
                if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                    [solidElement addChild:[[NSXMLElement alloc] initWithName:[NSString stringWithFormat:@"%s", bulkSystem[i].label] stringValue:[NSString stringWithFormat:@"%.20g", oxVal[i]*100.0]]];
                
                NSXMLElement *componentElement = [[NSXMLElement alloc] initWithName:@"component"];
                [componentElement addChild:[[NSXMLElement alloc] initWithName:@"name"         stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
                [componentElement addChild:[[NSXMLElement alloc] initWithName:@"formula"      stringValue:[NSString stringWithFormat:@"%s",   solids[j].formula]]];
                [componentElement addChild:[[NSXMLElement alloc] initWithName:@"moleFraction" stringValue:[NSString stringWithFormat:@"%.20g", 1.0]]];
                [solidElement addChild:componentElement];
     
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
                (*solids[j].vmix) (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, silminState->T, silminState->P, r, &volume, NULL, NULL, &dvdt, &dvdp, &d2vdt2, &d2vdtdp, &d2vdp2, NULL, NULL);
                (*solids[j].cpmix)(FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
                gibbsEnergy  *= (silminState->solidComp)[j][ns];
                enthalpy     *= (silminState->solidComp)[j][ns];
                entropy      *= (silminState->solidComp)[j][ns];
                volume       *= (silminState->solidComp)[j][ns];
                dvdt         *= (silminState->solidComp)[j][ns];
                dvdp         *= (silminState->solidComp)[j][ns];
                d2vdt2       *= (silminState->solidComp)[j][ns];
                d2vdtdp      *= (silminState->solidComp)[j][ns];
                d2vdp2       *= (silminState->solidComp)[j][ns];
                heatCapacity *= (silminState->solidComp)[j][ns];
                for (i=0; i<solids[j].na; i++) {
                    gibbsEnergy  += m[i]*(solids[j+1+i].cur).g;
                    enthalpy	 += m[i]*(solids[j+1+i].cur).h;
                    entropy	 += m[i]*(solids[j+1+i].cur).s;
                    volume	 += m[i]*(solids[j+1+i].cur).v;
                    dvdt	 += m[i]*(solids[j+1+i].cur).dvdt;
                    dvdp	 += m[i]*(solids[j+1+i].cur).dvdp;
                    d2vdt2	 += m[i]*(solids[j+1+i].cur).d2vdt2;
                    d2vdtdp	 += m[i]*(solids[j+1+i].cur).d2vdtdp;
                    d2vdp2	 += m[i]*(solids[j+1+i].cur).d2vdp2;
                    heatCapacity += m[i]*(solids[j+1+i].cur).cp;
                }
                totalMass	    += mass;
                totalGibbsEnergy  += gibbsEnergy;
                totalEnthalpy     += enthalpy;
                totalEntropy      += entropy;
                totalVolume	      += volume;
                totalDvdt	      += dvdt;
                totalDvdp	      += dvdp;
                totalD2vdt2	      += d2vdt2;
                totalD2vdtdp	  += d2vdtdp;
                totalD2vdp2	      += d2vdp2;
                totalHeatCapacity += heatCapacity;
     
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"name"            stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"formula"         stringValue:[NSString stringWithFormat:@"%s",   formula]]]; free(formula);
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"mass" 	         stringValue:[NSString stringWithFormat:@"%.20g", mass]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"density"	     stringValue:[NSString stringWithFormat:@"%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume)]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", gibbsEnergy]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"	     stringValue:[NSString stringWithFormat:@"%.20g", enthalpy]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"	     stringValue:[NSString stringWithFormat:@"%.20g", entropy]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"volume"	         stringValue:[NSString stringWithFormat:@"%.20g", volume*10.0]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt"	         stringValue:[NSString stringWithFormat:@"%.20g", dvdt*10.0]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"	         stringValue:[NSString stringWithFormat:@"%.20g", dvdp*10.0]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2"	         stringValue:[NSString stringWithFormat:@"%.20g", d2vdt2*10.0]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp"	     stringValue:[NSString stringWithFormat:@"%.20g", d2vdtdp*10.0]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2"	         stringValue:[NSString stringWithFormat:@"%.20g", d2vdp2*10.0]]];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"    stringValue:[NSString stringWithFormat:@"%.20g", heatCapacity]]];
     
                for (i=0, oxSum=0.0; i<nc; i++) {
                    int k;
                    for (k=0, oxVal[i]=0.0; k<solids[j].na; k++) oxVal[i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw;
                    oxSum += oxVal[i];
                }
                if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                    [solidElement addChild:[[NSXMLElement alloc] initWithName:[NSString stringWithFormat:@"%s",bulkSystem[i].label] stringValue:[NSString stringWithFormat:@"%.20g", oxVal[i]*100.0]]];
     
                for (i=0; i<solids[j].na; i++) {
                    NSXMLElement *componentElement = [[NSXMLElement alloc] initWithName:@"component"];
                    [componentElement addChild:[[NSXMLElement alloc] initWithName:@"name"         stringValue:[NSString stringWithFormat:@"%s",   solids[j+1+i].label]]];
                    [componentElement addChild:[[NSXMLElement alloc] initWithName:@"formula"      stringValue:[NSString stringWithFormat:@"%s",   solids[j+1+i].formula]]];
                    [componentElement addChild:[[NSXMLElement alloc] initWithName:@"moleFraction" stringValue:[NSString stringWithFormat:@"%.20g", m[i]/(silminState->solidComp)[j][ns]]]];
                    [solidElement addChild:componentElement];
                }
            }
            
            [root addChild:solidElement];
        }
    }
     
    if (totalMass != 0.0) {
        NSXMLElement *totalSolidsElement = [[NSXMLElement alloc] initWithName:@"totalSolids"];
        [totalSolidsElement addChild:[[NSXMLElement alloc] initWithName:@"mass"		       stringValue:[NSString stringWithFormat:@"%.20g", totalMass]]];
        [totalSolidsElement addChild:[[NSXMLElement alloc] initWithName:@"density"	       stringValue:[NSString stringWithFormat:@"%.20g", (totalVolume == 0.0) ? 0.0 : totalMass/(10.0*totalVolume)]]];
        [totalSolidsElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", totalGibbsEnergy]]];
        [totalSolidsElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"	       stringValue:[NSString stringWithFormat:@"%.20g", totalEnthalpy]]];
        [totalSolidsElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"         stringValue:[NSString stringWithFormat:@"%.20g", totalEntropy]]];
        [totalSolidsElement addChild:[[NSXMLElement alloc] initWithName:@"volume" 	       stringValue:[NSString stringWithFormat:@"%.20g", totalVolume*10.0]]];
        [totalSolidsElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt" 	       stringValue:[NSString stringWithFormat:@"%.20g", totalDvdt*10.0]]];
        [totalSolidsElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp" 	       stringValue:[NSString stringWithFormat:@"%.20g", totalDvdp*10.0]]];
        [totalSolidsElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2" 	       stringValue:[NSString stringWithFormat:@"%.20g", totalD2vdt2*10.0]]];
        [totalSolidsElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp" 	       stringValue:[NSString stringWithFormat:@"%.20g", totalD2vdtdp*10.0]]];
        [totalSolidsElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2" 	       stringValue:[NSString stringWithFormat:@"%.20g", totalD2vdp2*10.0]]];
        [totalSolidsElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"	   stringValue:[NSString stringWithFormat:@"%.20g", totalHeatCapacity]]];
        [root addChild:totalSolidsElement];
    }
    
     if (silminState->isenthalpic && (silminState->refEnthalpy == 0.0)) silminState->refEnthalpy = hLiq+totalEnthalpy;
     if (silminState->isentropic  && (silminState->refEntropy  == 0.0)) silminState->refEntropy  = sLiq+totalEntropy;
     if (silminState->isochoric   && (silminState->refVolume   == 0.0)) silminState->refVolume   = vLiq+totalVolume;
     
     if (silminState->fractionateSol || silminState->fractionateFlu || silminState->fractionateLiq) {
         NSXMLElement *fractionateElement = [[NSXMLElement alloc] initWithName:@"fractionate"];
         [fractionateElement addAttribute:[[NSXMLElement alloc] initWithName:@"type" stringValue:@"current"]];
         
         [fractionateElement addChild:[[NSXMLElement alloc] initWithName:@"mass" stringValue:[NSString stringWithFormat:@"%.20g", silminState->fracMass-previousSilminState->fracMass]]];
     
         if (silminState->fractionateSol || silminState->fractionateFlu) {
             for (j=0; j<npc; j++) {
                 int ns;
                 
                 if ( silminState->fractionateSol && !silminState->fractionateFlu && !strcmp((char *) solids[j].label, "water")) continue;
                 if (!silminState->fractionateSol &&  silminState->fractionateFlu &&  strcmp((char *) solids[j].label, "water")) continue;
                 
                 for (ns=0; ns<(silminState->nFracCoexist)[j]; ns++) {
                     double oxSum, mass, gibbsEnergy, enthalpy, entropy, volume, dvdt, dvdp, d2vdt2, d2vdtdp, d2vdp2, heatCapacity;
                     double tmpMoles = ((previousSilminState->nFracCoexist)[j] <= ns) ? (silminState->fracSComp)[j][ns]
                     : (silminState->fracSComp)[j][ns] - (previousSilminState->fracSComp)[j][ns];
                     if (fabs(tmpMoles) < 10.0*DBL_EPSILON) continue;
     
                     NSXMLElement *solidElement = [[NSXMLElement alloc] initWithName:@"solid"];
     
                     if (solids[j].na == 1) {
                         mass		        = tmpMoles*solids[j].mw;
                         gibbsEnergy	    = tmpMoles*(solids[j].cur).g;
                         enthalpy	        = tmpMoles*(solids[j].cur).h;
                         entropy 	        = tmpMoles*(solids[j].cur).s;
                         volume  	        = tmpMoles*(solids[j].cur).v;
                         dvdt   	        = tmpMoles*(solids[j].cur).dvdt;
                         dvdp   	        = tmpMoles*(solids[j].cur).dvdp;
                         d2vdt2  	        = tmpMoles*(solids[j].cur).d2vdt2;
                         d2vdtdp  	        = tmpMoles*(solids[j].cur).d2vdtdp;
                         d2vdp2  	        = tmpMoles*(solids[j].cur).d2vdp2;
                         heatCapacity	    = tmpMoles*(solids[j].cur).cp;
                         totalMass	       += tmpMoles*solids[j].mw;
                         totalGibbsEnergy  += tmpMoles*(solids[j].cur).g;
                         totalEnthalpy	   += tmpMoles*(solids[j].cur).h;
                         totalEntropy	   += tmpMoles*(solids[j].cur).s;
                         totalVolume	   += tmpMoles*(solids[j].cur).v;
                         totalDvdt  	   += tmpMoles*(solids[j].cur).dvdt;
                         totalDvdp  	   += tmpMoles*(solids[j].cur).dvdp;
                         totalD2vdt2	   += tmpMoles*(solids[j].cur).d2vdt2;
                         totalD2vdtdp	   += tmpMoles*(solids[j].cur).d2vdtdp;
                         totalD2vdp2	   += tmpMoles*(solids[j].cur).d2vdp2;
                         totalHeatCapacity += tmpMoles*(solids[j].cur).cp;
     
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"name"		      stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"formula"	      stringValue:[NSString stringWithFormat:@"%s",   solids[j].formula]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"mass"		      stringValue:[NSString stringWithFormat:@"%.20g", mass]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"density"	      stringValue:[NSString stringWithFormat:@"%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume)]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", gibbsEnergy]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"	      stringValue:[NSString stringWithFormat:@"%.20g", enthalpy]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"	      stringValue:[NSString stringWithFormat:@"%.20g", entropy]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"volume" 	      stringValue:[NSString stringWithFormat:@"%.20g", volume*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt" 	          stringValue:[NSString stringWithFormat:@"%.20g", dvdt*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"  	      stringValue:[NSString stringWithFormat:@"%.20g", dvdp*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2" 	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdt2*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp" 	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdtdp*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2" 	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdp2*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"	  stringValue:[NSString stringWithFormat:@"%.20g", heatCapacity]]];
     
                         for (i=0, oxSum=0.0; i<nc; i++) {
                             oxVal[i]  = (solids[j].solToOx)[i]*bulkSystem[i].mw;
                             oxSum    += oxVal[i];
                         }
                         if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                         for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                             [solidElement addChild:[[NSXMLElement alloc] initWithName:[NSString stringWithFormat:@"%s", bulkSystem[i].label] stringValue:[NSString stringWithFormat:@"%.20g", oxVal[i]*100.0]]];
                         
                         NSXMLElement *compentElement = [[NSXMLElement alloc] initWithName:@"component"];
                         [compentElement addChild:[[NSXMLElement alloc] initWithName:@"name"         stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
                         [compentElement addChild:[[NSXMLElement alloc] initWithName:@"formula"      stringValue:[NSString stringWithFormat:@"%s",   solids[j].formula]]];
                         [compentElement addChild:[[NSXMLElement alloc] initWithName:@"moleFraction" stringValue:[NSString stringWithFormat:@"%.20g", 1.0]]];
                         [solidElement addChild:compentElement];
     
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
                         (*solids[j].vmix)   (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, silminState->T, silminState->P, r, &volume, NULL, NULL, &dvdt, &dvdp, &d2vdt2, &d2vdtdp, &d2vdp2, NULL, NULL);
                         (*solids[j].cpmix)  (FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
                         gibbsEnergy  *= tmpMoles;
                         enthalpy     *= tmpMoles;
                         entropy      *= tmpMoles;
                         volume       *= tmpMoles;
                         dvdt         *= tmpMoles;
                         dvdp         *= tmpMoles;
                         d2vdt2       *= tmpMoles;
                         d2vdtdp      *= tmpMoles;
                         d2vdp2       *= tmpMoles;
                         heatCapacity *= tmpMoles;
                         for (i=0; i<solids[j].na; i++) {
                             gibbsEnergy  += m[i]*(solids[j+1+i].cur).g;
                             enthalpy     += m[i]*(solids[j+1+i].cur).h;
                             entropy      += m[i]*(solids[j+1+i].cur).s;
                             volume       += m[i]*(solids[j+1+i].cur).v;
                             dvdt         += m[i]*(solids[j+1+i].cur).dvdt;
                             dvdp         += m[i]*(solids[j+1+i].cur).dvdp;
                             d2vdt2       += m[i]*(solids[j+1+i].cur).d2vdt2;
                             d2vdtdp      += m[i]*(solids[j+1+i].cur).d2vdtdp;
                             d2vdp2       += m[i]*(solids[j+1+i].cur).d2vdp2;
                             heatCapacity += m[i]*(solids[j+1+i].cur).cp;
                         }
                         totalMass	  += mass;
                         totalGibbsEnergy  += gibbsEnergy;
                         totalEnthalpy	   += enthalpy;
                         totalEntropy	   += entropy;
                         totalVolume	   += volume;
                         totalDvdt  	   += dvdt;
                         totalDvdp  	   += dvdp;
                         totalD2vdt2	   += d2vdt2;
                         totalD2vdtdp	   += d2vdtdp;
                         totalD2vdp2	   += d2vdp2;
                         totalHeatCapacity += heatCapacity;
     
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"name"		      stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"formula"	      stringValue:[NSString stringWithFormat:@"%s",   formula]]]; free(formula);
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"mass"		      stringValue:[NSString stringWithFormat:@"%.20g", mass]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"density"	      stringValue:[NSString stringWithFormat:@"%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume)]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", gibbsEnergy]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"	      stringValue:[NSString stringWithFormat:@"%.20g", enthalpy]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"	      stringValue:[NSString stringWithFormat:@"%.20g", entropy]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"volume" 	      stringValue:[NSString stringWithFormat:@"%.20g", volume*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt"  	      stringValue:[NSString stringWithFormat:@"%.20g", dvdt*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"  	      stringValue:[NSString stringWithFormat:@"%.20g", dvdp*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2" 	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdt2*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp" 	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdtdp*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2" 	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdp2*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"    stringValue:[NSString stringWithFormat:@"%.20g", heatCapacity]]];
                         
                         for (i=0, oxSum=0.0; i<nc; i++) {
                             int k;
                             for (k=0, oxVal[i]=0.0; k<solids[j].na; k++) oxVal[i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw;
                             oxSum += oxVal[i];
                         }
                         if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                         for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                             [solidElement addChild:[[NSXMLElement alloc] initWithName:[NSString stringWithFormat:@"%s",bulkSystem[i].label] stringValue:[NSString stringWithFormat:@"%.20g", oxVal[i]*100.0]]];
     
                         for (i=0; i<solids[j].na; i++) {
                             NSXMLElement *componentElement = [[NSXMLElement alloc] initWithName:@"component"];
                             [componentElement  addChild:[[NSXMLElement alloc] initWithName:@"name" 	    stringValue:[NSString stringWithFormat:@"%s",   solids[j+1+i].label]]];
                             [componentElement  addChild:[[NSXMLElement alloc] initWithName:@"formula"	    stringValue:[NSString stringWithFormat:@"%s",   solids[j+1+i].formula]]];
                             [componentElement  addChild:[[NSXMLElement alloc] initWithName:@"moleFraction" stringValue:[NSString stringWithFormat:@"%.20g", m[i]/tmpMoles]]];
                             [solidElement addChild:componentElement];
                         }
                     }
                     
                     [fractionateElement addChild:solidElement];
                 }
             }
         }
     
         if (silminState->fractionateLiq) {
             double oxSum, mass, moles, gibbsEnergy, enthalpy, entropy, volume, dvdt, dvdp, d2vdt2, d2vdtdp, d2vdp2, heatCapacity;
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
                 NSXMLElement *liquidElement = [[NSXMLElement alloc] initWithName:@"liquid"];
     
                 conLiq  (SECOND, THIRD, silminState->T, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL);
                 dispLiq (FIRST, silminState->T, silminState->P, r, &formula);
                 gmixLiq (FIRST, silminState->T, silminState->P, r, &gibbsEnergy,  NULL, NULL);
                 hmixLiq (FIRST, silminState->T, silminState->P, r, &enthalpy,     NULL);
                 smixLiq (FIRST, silminState->T, silminState->P, r, &entropy,      NULL, NULL, NULL);
                 vmixLiq (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, silminState->T, silminState->P, r, &volume, NULL, NULL, &dvdt, &dvdp, &d2vdt2, &d2vdtdp, &d2vdp2, NULL, NULL, NULL);
                 cpmixLiq(FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
                 gibbsEnergy  *= moles;
                 enthalpy	  *= moles;
                 entropy	  *= moles;
                 volume	      *= moles;
                 dvdt	      *= moles;
                 dvdp	      *= moles;
                 d2vdt2	      *= moles;
                 d2vdtdp	  *= moles;
                 d2vdp2	      *= moles;
                 heatCapacity *= moles;
                 for (i=0; i<nlc; i++) {
                     gibbsEnergy  += m[i]*(liquid[i].cur).g;
                     enthalpy     += m[i]*(liquid[i].cur).h;
                     entropy	  += m[i]*(liquid[i].cur).s;
                     volume	      += m[i]*(liquid[i].cur).v;
                     dvdt	      += m[i]*(liquid[i].cur).dvdt;
                     dvdp	      += m[i]*(liquid[i].cur).dvdp;
                     d2vdt2	      += m[i]*(liquid[i].cur).d2vdt2;
                     d2vdtdp	  += m[i]*(liquid[i].cur).d2vdtdp;
                     d2vdp2	      += m[i]*(liquid[i].cur).d2vdp2;
                     heatCapacity += m[i]*(liquid[i].cur).cp;
                 }
                 totalMass	       += mass;
                 totalGibbsEnergy  += gibbsEnergy;
                 totalEnthalpy     += enthalpy;
                 totalEntropy      += entropy;
                 totalVolume       += volume;
                 totalDvdt         += dvdt;
                 totalDvdp         += dvdp;
                 totalD2vdt2       += d2vdt2;
                 totalD2vdtdp      += d2vdtdp;
                 totalD2vdp2       += d2vdp2;
                 totalHeatCapacity += heatCapacity;
                 
                 for (i=0, oxSum=0.0; i<nc; i++) {
                     for (j=0, oxVal[i]=0.0; j<nlc; j++) oxVal[i] += (liquid[j].liqToOx)[i]*m[j];
                     oxVal[i] *= bulkSystem[i].mw;
                     oxSum    += oxVal[i];
                 }
                 if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                 
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"mass"	           stringValue:[NSString stringWithFormat:@"%.20g", mass]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"density"	       stringValue:[NSString stringWithFormat:@"%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume)]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", gibbsEnergy]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"	       stringValue:[NSString stringWithFormat:@"%.20g", enthalpy]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"	       stringValue:[NSString stringWithFormat:@"%.20g", entropy]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"volume"	       stringValue:[NSString stringWithFormat:@"%.20g", volume*10.0]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt" 	       stringValue:[NSString stringWithFormat:@"%.20g", dvdt*10.0]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"            stringValue:[NSString stringWithFormat:@"%.20g", dvdp*10.0]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2"	       stringValue:[NSString stringWithFormat:@"%.20g", d2vdt2*10.0]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp"	       stringValue:[NSString stringWithFormat:@"%.20g", d2vdtdp*10.0]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2"	       stringValue:[NSString stringWithFormat:@"%.20g", d2vdp2*10.0]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"    stringValue:[NSString stringWithFormat:@"%.20g", heatCapacity]]];
                 
                 for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                     [liquidElement addChild:[[NSXMLElement alloc] initWithName:[NSString stringWithFormat:@"%s", bulkSystem[i].label] stringValue:[NSString stringWithFormat:@"%.20g", oxVal[i]*100.0]]];
     
                 [fractionateElement addChild:liquidElement];
             }
         }
     
         [root addChild:fractionateElement];
     }
     
     if ( (previousSilminState->fractionateSol || previousSilminState->fractionateFlu || previousSilminState->fractionateLiq) && (previousSilminState->fracMass > 0) ) {
         NSXMLElement *fractionateElement = [[NSXMLElement alloc] initWithName:@"fractionate"];
         [fractionateElement addAttribute:[[NSXMLElement alloc] initWithName:@"type" stringValue:@"previous"]];
         
         [fractionateElement addChild:[[NSXMLElement alloc] initWithName:@"mass" stringValue:[NSString stringWithFormat:@"%.20g", previousSilminState->fracMass]]];
     
         if (previousSilminState->fractionateSol || previousSilminState->fractionateFlu) {
             for (j=0; j<npc; j++) {
                 int ns;
                 
                 if ( previousSilminState->fractionateSol && !previousSilminState->fractionateFlu && !strcmp((char *) solids[j].label, "water")) continue;
                 if (!previousSilminState->fractionateSol &&  previousSilminState->fractionateFlu &&  strcmp((char *) solids[j].label, "water")) continue;
                 
                 for (ns=0; ns<(previousSilminState->nFracCoexist)[j]; ns++) {
                     double oxSum, mass, gibbsEnergy, enthalpy, entropy, volume, dvdt, dvdp, d2vdt2, d2vdtdp, d2vdp2, heatCapacity;
                     
                     NSXMLElement *solidElement = [[NSXMLElement alloc] initWithName:@"solid"];
     
                     if (solids[j].na == 1) {
                         mass		        = (previousSilminState->fracSComp)[j][ns]*solids[j].mw;
                         gibbsEnergy	    = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).g;
                         enthalpy	        = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).h;
                         entropy 	        = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).s;
                         volume  	        = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).v;
                         dvdt   	        = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).dvdt;
                         dvdp   	        = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).dvdp;
                         d2vdt2  	        = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).d2vdt2;
                         d2vdtdp  	        = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).d2vdtdp;
                         d2vdp2  	        = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).d2vdp2;
                         heatCapacity	    = (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).cp;
                         totalMass	       += (previousSilminState->fracSComp)[j][ns]*solids[j].mw;
                         totalGibbsEnergy  += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).g;
                         totalEnthalpy	   += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).h;
                         totalEntropy	   += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).s;
                         totalVolume	   += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).v;
                         totalDvdt         += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).dvdt;
                         totalDvdp	       += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).dvdp;
                         totalD2vdt2	   += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).d2vdt2;
                         totalD2vdtdp	   += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).d2vdtdp;
                         totalD2vdp2	   += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).d2vdp2;
                         totalHeatCapacity += (previousSilminState->fracSComp)[j][ns]*(solids[j].cur).cp;
                         
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"name"		      stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"formula"	      stringValue:[NSString stringWithFormat:@"%s",   solids[j].formula]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"mass"		      stringValue:[NSString stringWithFormat:@"%.20g", mass]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"density"	      stringValue:[NSString stringWithFormat:@"%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume)]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", gibbsEnergy]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"	      stringValue:[NSString stringWithFormat:@"%.20g", enthalpy]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"	      stringValue:[NSString stringWithFormat:@"%.20g", entropy]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"volume" 	      stringValue:[NSString stringWithFormat:@"%.20g", volume*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt"  	      stringValue:[NSString stringWithFormat:@"%.20g", dvdt*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"  	      stringValue:[NSString stringWithFormat:@"%.20g", dvdp*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2" 	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdt2*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp" 	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdtdp*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2" 	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdp2*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"	  stringValue:[NSString stringWithFormat:@"%.20g", heatCapacity]]];
     
                         for (i=0, oxSum=0.0; i<nc; i++) {
                             oxVal[i]  = (solids[j].solToOx)[i]*bulkSystem[i].mw;
                             oxSum    += oxVal[i];
                         }
                         if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                         for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                             [solidElement addChild:[[NSXMLElement alloc] initWithName:[NSString stringWithFormat:@"%s", bulkSystem[i].label] stringValue:[NSString stringWithFormat:@"%.20g", oxVal[i]*100.0]]];
     
                         NSXMLElement *componentElement = [[NSXMLElement alloc] initWithName:@"component"];
                         [componentElement addChild:[[NSXMLElement alloc] initWithName:@"name"         stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
                         [componentElement addChild:[[NSXMLElement alloc] initWithName:@"formula"      stringValue:[NSString stringWithFormat:@"%s",   solids[j].formula]]];
                         [componentElement addChild:[[NSXMLElement alloc] initWithName:@"moleFraction" stringValue:[NSString stringWithFormat:@"%.20g", 1.0]]];
                         [solidElement addChild:componentElement];
     
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
                         (*solids[j].vmix)   (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, silminState->T, silminState->P, r, &volume, NULL, NULL, &dvdt, &dvdp, &d2vdt2, &d2vdtdp, &d2vdp2, NULL, NULL);
                         (*solids[j].cpmix)  (FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
                         gibbsEnergy  *= (previousSilminState->fracSComp)[j][ns];
                         enthalpy     *= (previousSilminState->fracSComp)[j][ns];
                         entropy      *= (previousSilminState->fracSComp)[j][ns];
                         volume       *= (previousSilminState->fracSComp)[j][ns];
                         dvdt         *= (previousSilminState->fracSComp)[j][ns];
                         dvdp         *= (previousSilminState->fracSComp)[j][ns];
                         d2vdt2       *= (previousSilminState->fracSComp)[j][ns];
                         d2vdtdp      *= (previousSilminState->fracSComp)[j][ns];
                         d2vdp2       *= (previousSilminState->fracSComp)[j][ns];
                         heatCapacity *= (previousSilminState->fracSComp)[j][ns];
                         for (i=0; i<solids[j].na; i++) {
                             gibbsEnergy  += m[i]*(solids[j+1+i].cur).g;
                             enthalpy     += m[i]*(solids[j+1+i].cur).h;
                             entropy      += m[i]*(solids[j+1+i].cur).s;
                             volume       += m[i]*(solids[j+1+i].cur).v;
                             dvdt         += m[i]*(solids[j+1+i].cur).dvdt;
                             dvdp         += m[i]*(solids[j+1+i].cur).dvdp;
                             d2vdt2       += m[i]*(solids[j+1+i].cur).d2vdt2;
                             d2vdtdp      += m[i]*(solids[j+1+i].cur).d2vdtdp;
                             d2vdp2       += m[i]*(solids[j+1+i].cur).d2vdp2;
                             heatCapacity += m[i]*(solids[j+1+i].cur).cp;
                         }
                         totalMass	       += mass;
                         totalGibbsEnergy  += gibbsEnergy;
                         totalEnthalpy	   += enthalpy;
                         totalEntropy	   += entropy;
                         totalVolume	   += volume;
                         totalDvdt	       += dvdt;
                         totalDvdp         += dvdp;
                         totalD2vdt2	   += d2vdt2;
                         totalD2vdtdp	   += d2vdtdp;
                         totalD2vdp2	   += d2vdp2;
                         totalHeatCapacity += heatCapacity;
                         
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"name"		      stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"formula"	      stringValue:[NSString stringWithFormat:@"%s",   formula]]]; free(formula);
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"mass"		      stringValue:[NSString stringWithFormat:@"%.20g", mass]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"density"	      stringValue:[NSString stringWithFormat:@"%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume)]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", gibbsEnergy]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"	      stringValue:[NSString stringWithFormat:@"%.20g", enthalpy]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"	      stringValue:[NSString stringWithFormat:@"%.20g", entropy]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"volume" 	      stringValue:[NSString stringWithFormat:@"%.20g", volume*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt"  	      stringValue:[NSString stringWithFormat:@"%.20g", dvdt*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"  	      stringValue:[NSString stringWithFormat:@"%.20g", dvdp*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2" 	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdt2*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp" 	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdtdp*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2" 	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdp2*10.0]]];
                         [solidElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"    stringValue:[NSString stringWithFormat:@"%.20g", heatCapacity]]];
     
                         for (i=0, oxSum=0.0; i<nc; i++) {
                             int k;
                             for (k=0, oxVal[i]=0.0; k<solids[j].na; k++) oxVal[i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw;
                             oxSum += oxVal[i];
                         }
                         if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
                         for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                             [solidElement addChild:[[NSXMLElement alloc] initWithName:[NSString stringWithFormat:@"%s", bulkSystem[i].label] stringValue:[NSString stringWithFormat:@"%.20g", oxVal[i]*100.0]]];
     
                         for (i=0; i<solids[j].na; i++) {
                             NSXMLElement *componentElement = [[NSXMLElement alloc] initWithName:@"component"];
                             [componentElement addChild:[[NSXMLElement alloc] initWithName:@"name" 	       stringValue:[NSString stringWithFormat:@"%s",   solids[j+1+i].label]]];
                             [componentElement addChild:[[NSXMLElement alloc] initWithName:@"formula"	   stringValue:[NSString stringWithFormat:@"%s",   solids[j+1+i].formula]]];
                             [componentElement addChild:[[NSXMLElement alloc] initWithName:@"moleFraction" stringValue:[NSString stringWithFormat:@"%.20g", m[i]/(previousSilminState->fracSComp)[j][ns]]]];
                             [solidElement addChild:componentElement];
                         }
                     }
     
                     [fractionateElement addChild:solidElement];
                 }
             }
         }
     
         if (previousSilminState->fractionateLiq) {
             double oxSum, mass, moles, gibbsEnergy, enthalpy, entropy, volume, dvdt, dvdp, d2vdt2, d2vdtdp, d2vdp2, heatCapacity;
             char *formula;
             
             for (i=0, mass=0.0, moles=0.0; i<nlc; i++) {
                 double mw;
                 for (j=0, mw = 0.0; j<nc; j++) mw += (liquid[i].liqToOx)[j]*bulkSystem[j].mw;
                 m[i]   = (previousSilminState->fracLComp)[i];
                 moles += m[i];
                 mass  += (previousSilminState->fracLComp)[i]*mw;
             }
             
             if (mass > 0.0) {
                 NSXMLElement *liquidElement = [[NSXMLElement alloc] initWithName:@"liquid"];
     
                 conLiq  (SECOND, THIRD, silminState->T, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL);
                 dispLiq (FIRST, silminState->T, silminState->P, r, &formula);
                 gmixLiq (FIRST, silminState->T, silminState->P, r, &gibbsEnergy,  NULL, NULL);
                 hmixLiq (FIRST, silminState->T, silminState->P, r, &enthalpy,     NULL);
                 smixLiq (FIRST, silminState->T, silminState->P, r, &entropy,      NULL, NULL, NULL);
                 vmixLiq (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, silminState->T, silminState->P, r, &volume, NULL, NULL, &dvdt, &dvdp, &d2vdt2, &d2vdtdp, &d2vdp2, NULL, NULL, NULL);
                 cpmixLiq(FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
                 gibbsEnergy  *= moles;
                 enthalpy	  *= moles;
                 entropy	  *= moles;
                 volume	      *= moles;
                 dvdt	      *= moles;
                 dvdp	      *= moles;
                 d2vdt2	      *= moles;
                 d2vdtdp	  *= moles;
                 d2vdp2    	  *= moles;
                 heatCapacity *= moles;
                 for (i=0; i<nlc; i++) {
                     gibbsEnergy  += m[i]*(liquid[i].cur).g;
                     enthalpy     += m[i]*(liquid[i].cur).h;
                     entropy	  += m[i]*(liquid[i].cur).s;
                     volume	      += m[i]*(liquid[i].cur).v;
                     dvdt	      += m[i]*(liquid[i].cur).dvdt;
                     dvdp	      += m[i]*(liquid[i].cur).dvdp;
                     d2vdt2	      += m[i]*(liquid[i].cur).d2vdt2;
                     d2vdtdp	  += m[i]*(liquid[i].cur).d2vdtdp;
                     d2vdp2	      += m[i]*(liquid[i].cur).d2vdp2;
                     heatCapacity += m[i]*(liquid[i].cur).cp;
                 }
                 totalMass	       += mass;
                 totalGibbsEnergy  += gibbsEnergy;
                 totalEnthalpy     += enthalpy;
                 totalEntropy      += entropy;
                 totalVolume       += volume;
                 totalDvdt         += dvdt;
                 totalDvdp         += dvdp;
                 totalD2vdt2       += d2vdt2;
                 totalD2vdtdp      += d2vdtdp;
                 totalD2vdp2       += d2vdp2;
                 totalHeatCapacity += heatCapacity;
                 
                 for (i=0, oxSum=0.0; i<nc; i++) {
                     for (j=0, oxVal[i]=0.0; j<nlc; j++) oxVal[i] += (liquid[j].liqToOx)[i]*(previousSilminState->fracLComp)[j];
                     oxVal[i] *= bulkSystem[i].mw;
                     oxSum    += oxVal[i];
                 }
                 if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
     
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"mass"	           stringValue:[NSString stringWithFormat:@"%.20g", mass]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"density"	       stringValue:[NSString stringWithFormat:@"%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume)]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", gibbsEnergy]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"	       stringValue:[NSString stringWithFormat:@"%.20g", enthalpy]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"	       stringValue:[NSString stringWithFormat:@"%.20g", entropy]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"volume"	       stringValue:[NSString stringWithFormat:@"%.20g", volume*10.0]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt"	           stringValue:[NSString stringWithFormat:@"%.20g", dvdt*10.0]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"	           stringValue:[NSString stringWithFormat:@"%.20g", dvdp*10.0]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2"	       stringValue:[NSString stringWithFormat:@"%.20g", d2vdt2*10.0]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp"	       stringValue:[NSString stringWithFormat:@"%.20g", d2vdtdp*10.0]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2"	       stringValue:[NSString stringWithFormat:@"%.20g", d2vdp2*10.0]]];
                 [liquidElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"    stringValue:[NSString stringWithFormat:@"%.20g", heatCapacity]]];
                 
                 for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                     [liquidElement addChild:[[NSXMLElement alloc] initWithName:[NSString stringWithFormat:@"%s",bulkSystem[i].label] stringValue:[NSString stringWithFormat:@"%.20g", oxVal[i]*100.0]]];
                                     
                 [fractionateElement addChild:liquidElement];
             }
         }
     
         [root addChild:fractionateElement];
     }
     
    NSXMLElement *systemElement = [[NSXMLElement alloc] initWithName:@"system"];
    [systemElement addChild:[[NSXMLElement alloc] initWithName:@"mass"	          stringValue:[NSString stringWithFormat:@"%.20g", mLiq+totalMass]]];
    [systemElement addChild:[[NSXMLElement alloc] initWithName:@"density"         stringValue:[NSString stringWithFormat:@"%.20g", (vLiq+totalVolume == 0.0) ? 0.0 :  (mLiq+totalMass)/(10.0*(vLiq+totalVolume))]]];
    if (vLiq > totalVolume)
        [systemElement addChild:[[NSXMLElement alloc] initWithName:@"viscosity"   stringValue:[NSString stringWithFormat:@"%.20g", viscosity - 2.0*log10(1.0-2.0*totalVolume/(totalVolume+vLiq))]]];
    [systemElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", gLiq+totalGibbsEnergy]]];
    [systemElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"        stringValue:[NSString stringWithFormat:@"%.20g", hLiq+totalEnthalpy]]];
    [systemElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"         stringValue:[NSString stringWithFormat:@"%.20g", sLiq+totalEntropy]]];
    [systemElement addChild:[[NSXMLElement alloc] initWithName:@"volume"	      stringValue:[NSString stringWithFormat:@"%.20g", (vLiq+totalVolume)*10.0]]];
    [systemElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt"  	      stringValue:[NSString stringWithFormat:@"%.20g", (dvdtLiq+totalDvdt)*10.0]]];
    [systemElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"  	      stringValue:[NSString stringWithFormat:@"%.20g", (dvdpLiq+totalDvdp)*10.0]]];
    [systemElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2"	      stringValue:[NSString stringWithFormat:@"%.20g", (d2vdt2Liq+totalD2vdt2)*10.0]]];
    [systemElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp"	      stringValue:[NSString stringWithFormat:@"%.20g", (d2vdtdpLiq+totalD2vdtdp)*10.0]]];
    [systemElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2"	      stringValue:[NSString stringWithFormat:@"%.20g", (d2vdp2Liq+totalD2vdp2)*10.0]]];
    [systemElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"    stringValue:[NSString stringWithFormat:@"%.20g", cpLiq+totalHeatCapacity]]];
    [root addChild:systemElement];
    
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
        NSXMLElement *oxygenElement = [[NSXMLElement alloc] initWithName:@"oxygen"];
        [oxygenElement addChild:[[NSXMLElement alloc] initWithName:@"moles"	          stringValue:[NSString stringWithFormat:@"%.20g", mO2]]];
        [oxygenElement addChild:[[NSXMLElement alloc] initWithName:@"mass"	          stringValue:[NSString stringWithFormat:@"%.20g", mO2*31.9988]]];
        [oxygenElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", mO2*(oxygen.cur).g]]];
        [oxygenElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"        stringValue:[NSString stringWithFormat:@"%.20g", mO2*(oxygen.cur).h]]];
        [oxygenElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"         stringValue:[NSString stringWithFormat:@"%.20g", mO2*(oxygen.cur).s]]];
        [oxygenElement addChild:[[NSXMLElement alloc] initWithName:@"volume"	      stringValue:[NSString stringWithFormat:@"%.20g", mO2*10.0*(oxygen.cur).v]]];
        [oxygenElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt"  	      stringValue:[NSString stringWithFormat:@"%.20g", mO2*10.0*(oxygen.cur).dvdt]]];
        [oxygenElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"  	      stringValue:[NSString stringWithFormat:@"%.20g", mO2*10.0*(oxygen.cur).dvdp]]];
        [oxygenElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2"	      stringValue:[NSString stringWithFormat:@"%.20g", mO2*10.0*(oxygen.cur).d2vdt2]]];
        [oxygenElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp"	      stringValue:[NSString stringWithFormat:@"%.20g", mO2*10.0*(oxygen.cur).d2vdtdp]]];
        [oxygenElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2"	      stringValue:[NSString stringWithFormat:@"%.20g", mO2*10.0*(oxygen.cur).d2vdp2]]];
        [oxygenElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"    stringValue:[NSString stringWithFormat:@"%.20g", mO2*(oxygen.cur).cp]]];
        [root addChild:oxygenElement];
    }
     
    if (silminState->assimilate) {
        int ns;
        NSXMLElement *assimilantElement = [[NSXMLElement alloc] initWithName:@"assimilant"];
        [assimilantElement  addChild:[[NSXMLElement alloc] initWithName:@"mass"	    stringValue:[NSString stringWithFormat:@"%.20g", silminState->assimMass]]];
        [assimilantElement  addChild:[[NSXMLElement alloc] initWithName:@"temperature"	stringValue:[NSString stringWithFormat:@"%.20g", silminState->assimT]]];
        
        for (j=0; j<npc; j++) if (solids[j].type == PHASE)
            for (ns=0; ns<(silminState->nAssimComp)[j]; ns++) {
                NSXMLElement *solidElement = [[NSXMLElement alloc] initWithName:@"solid"];
                [solidElement addChild:[[NSXMLElement alloc] initWithName:@"name" stringValue:[NSString stringWithFormat:@"%s", solids[j].label]]];
                if (solids[j].na == 1) {
                    double mass = (silminState->assimComp)[j][ns]*solids[j].mw*silminState->assimMass/silminState->dspAssimMass;
                    [solidElement addChild:[[NSXMLElement alloc] initWithName:@"mass" stringValue:[NSString stringWithFormat:@"%.20g", mass]]];
                    NSXMLElement *componentElement = [[NSXMLElement alloc] initWithName:@"component"];
                    [componentElement addChild:[[NSXMLElement alloc] initWithName:@"name"         stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
                    [componentElement addChild:[[NSXMLElement alloc] initWithName:@"moleFraction" stringValue:[NSString stringWithFormat:@"%.20g", 1.0]]];
                    [solidElement addChild:componentElement];
                    
                } else {
                    double mass = 0.0;
                    for (i=0; i<solids[j].na; i++) mass += (silminState->assimComp)[j+1+i][ns]*solids[j+1+i].mw;
                    mass *= silminState->assimMass/silminState->dspAssimMass;
                    [solidElement addChild:[[NSXMLElement alloc] initWithName:@"mass" stringValue:[NSString stringWithFormat:@"%.20g", mass]]];
     
                    for (i=0; i<solids[j].na; i++) {
                        NSXMLElement *componentElement = [[NSXMLElement alloc] initWithName:@"component"];
                        [componentElement addChild:[[NSXMLElement alloc] initWithName:@"name"    stringValue:[NSString stringWithFormat:@"%s", solids[j+1+i].label]]];
                        [componentElement addChild:[[NSXMLElement alloc] initWithName:@"molFrac" stringValue:[NSString stringWithFormat:@"%.20g", (silminState->assimComp)[j+1+i][ns]/(silminState->assimComp)[j][ns]]]];
                        [solidElement addChild:componentElement];
                    }
                    
                }
                [assimilantElement addChild:solidElement];
            }
        [root addChild:assimilantElement];
    }
    
    for (j=0; j<npc; j++) if ((solids[j].type == PHASE) && ((silminState->ySol)[j] != 0.0)) {
        double oxSum, affinity, mass, gibbsEnergy, enthalpy, entropy, volume, dvdt, dvdp, d2vdt2, d2vdtdp, d2vdp2, heatCapacity;
        
        NSXMLElement *potentialSolidElement = [[NSXMLElement alloc] initWithName:@"potentialSolid"];
        
        if (solids[j].na == 1) {
            affinity  	       = (silminState->ySol)[j];
            gibbsEnergy	       = (solids[j].cur).g;
            enthalpy	       = (solids[j].cur).h;
            entropy	           = (solids[j].cur).s;
            volume	           = (solids[j].cur).v;
            dvdt	           = (solids[j].cur).dvdt;
            dvdp	           = (solids[j].cur).dvdp;
            d2vdt2	           = (solids[j].cur).d2vdt2;
            d2vdtdp	           = (solids[j].cur).d2vdtdp;
            d2vdp2	           = (solids[j].cur).d2vdp2;
            heatCapacity       = (solids[j].cur).cp;
            
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"name"            stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"formula"         stringValue:[NSString stringWithFormat:@"%s",   solids[j].formula]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"affinity" 	      stringValue:[NSString stringWithFormat:@"%.20g", affinity]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"density"	      stringValue:[NSString stringWithFormat:@"%.20g", (volume == 0.0) ? 0.0 : solids[j].mw/(10.0*volume)]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", gibbsEnergy]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"	      stringValue:[NSString stringWithFormat:@"%.20g", enthalpy]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"	      stringValue:[NSString stringWithFormat:@"%.20g", entropy]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"volume"	      stringValue:[NSString stringWithFormat:@"%.20g", volume*10.0]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt"  	      stringValue:[NSString stringWithFormat:@"%.20g", dvdt*10.0]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"  	      stringValue:[NSString stringWithFormat:@"%.20g", dvdp*10.0]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2"	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdt2*10.0]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp"	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdtdp*10.0]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2"	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdp2*10.0]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"    stringValue:[NSString stringWithFormat:@"%.20g", heatCapacity]]];
            
            for (i=0, oxSum=0.0; i<nc; i++) {
                oxVal[i]  = (solids[j].solToOx)[i]*bulkSystem[i].mw;
                oxSum    += oxVal[i];
            }
            if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
            for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:[NSString stringWithFormat:@"%s", bulkSystem[i].label] stringValue:[NSString stringWithFormat:@"%.20g", oxVal[i]*100.0]]];
            
            NSXMLElement *componentElement = [[NSXMLElement alloc] initWithName:@"component"];
            [componentElement addChild:[[NSXMLElement alloc] initWithName:@"name"         stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
            [componentElement addChild:[[NSXMLElement alloc] initWithName:@"formula"      stringValue:[NSString stringWithFormat:@"%s",   solids[j].formula]]];
            [componentElement addChild:[[NSXMLElement alloc] initWithName:@"moleFraction" stringValue:[NSString stringWithFormat:@"%.20g", 1.0]]];
            [potentialSolidElement addChild:componentElement];
            
        } else {
            char *formula;
            affinity = (silminState->ySol)[j];
            for (i=0; i<solids[j].na; i++) m[i] = (silminState->ySol)[j+1+i];
            
            (*solids[j].convert)(SECOND, THIRD, silminState->T, silminState->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
            (*solids[j].display)(FIRST, silminState->T, silminState->P, r, &formula);
            (*solids[j].gmix) (FIRST, silminState->T, silminState->P, r, &gibbsEnergy,  NULL, NULL, NULL);
            (*solids[j].hmix) (FIRST, silminState->T, silminState->P, r, &enthalpy);
            (*solids[j].smix) (FIRST, silminState->T, silminState->P, r, &entropy,      NULL, NULL);
            (*solids[j].vmix) (FIRST | FOURTH | FIFTH | SIXTH | SEVENTH | EIGHTH, silminState->T, silminState->P, r, &volume, NULL, NULL, &dvdt, &dvdp, &d2vdt2, &d2vdtdp, &d2vdp2, NULL, NULL);
            (*solids[j].cpmix)(FIRST, silminState->T, silminState->P, r, &heatCapacity, NULL, NULL);
            
            for (i=0, mass=0.0; i<solids[j].na; i++) {
                gibbsEnergy  += m[i]*(solids[j+1+i].cur).g;
                enthalpy	 += m[i]*(solids[j+1+i].cur).h;
                entropy	     += m[i]*(solids[j+1+i].cur).s;
                volume	     += m[i]*(solids[j+1+i].cur).v;
                dvdt	     += m[i]*(solids[j+1+i].cur).dvdt;
                dvdp	     += m[i]*(solids[j+1+i].cur).dvdp;
                d2vdt2	     += m[i]*(solids[j+1+i].cur).d2vdt2;
                d2vdtdp	     += m[i]*(solids[j+1+i].cur).d2vdtdp;
                d2vdp2	     += m[i]*(solids[j+1+i].cur).d2vdp2;
                heatCapacity += m[i]*(solids[j+1+i].cur).cp;
                mass         += m[i]*(solids[j+1+i]).mw;
            }
            
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"name"            stringValue:[NSString stringWithFormat:@"%s",   solids[j].label]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"formula"         stringValue:[NSString stringWithFormat:@"%s",   formula]]]; free(formula);
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"affinity" 	      stringValue:[NSString stringWithFormat:@"%.20g", affinity]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"density"	      stringValue:[NSString stringWithFormat:@"%.20g", (volume == 0.0) ? 0.0 : mass/(10.0*volume)]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"gibbsFreeEnergy" stringValue:[NSString stringWithFormat:@"%.20g", gibbsEnergy]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"enthalpy"	      stringValue:[NSString stringWithFormat:@"%.20g", enthalpy]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"entropy"	      stringValue:[NSString stringWithFormat:@"%.20g", entropy]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"volume"	      stringValue:[NSString stringWithFormat:@"%.20g", volume*10.0]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdt"            stringValue:[NSString stringWithFormat:@"%.20g", dvdt*10.0]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"dvdp"	          stringValue:[NSString stringWithFormat:@"%.20g", dvdp*10.0]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdt2"	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdt2*10.0]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdtdp"	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdtdp*10.0]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"d2vdp2"	      stringValue:[NSString stringWithFormat:@"%.20g", d2vdp2*10.0]]];
            [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:@"heatCapacity"    stringValue:[NSString stringWithFormat:@"%.20g", heatCapacity]]];
            
            for (i=0, oxSum=0.0; i<nc; i++) {
                int k;
                for (k=0, oxVal[i]=0.0; k<solids[j].na; k++) oxVal[i] += (solids[j+1+k].solToOx)[i]*m[k]*bulkSystem[i].mw;
                oxSum += oxVal[i];
            }
            if (oxSum != 0.0) for (i=0; i<nc; i++) oxVal[i] /= oxSum;
            for (i=0; i<nc; i++) if (oxVal[i] != 0.0)
                [potentialSolidElement addChild:[[NSXMLElement alloc] initWithName:[NSString stringWithFormat:@"%s",bulkSystem[i].label] stringValue:[NSString stringWithFormat:@"%.20g", oxVal[i]*100.0]]];
            
            for (i=0; i<solids[j].na; i++) {
                NSXMLElement *componentElement = [[NSXMLElement alloc] initWithName:@"component"];
                [componentElement addChild:[[NSXMLElement alloc] initWithName:@"name"         stringValue:[NSString stringWithFormat:@"%s",   solids[j+1+i].label]]];
                [componentElement addChild:[[NSXMLElement alloc] initWithName:@"formula"      stringValue:[NSString stringWithFormat:@"%s",   solids[j+1+i].formula]]];
                [componentElement addChild:[[NSXMLElement alloc] initWithName:@"moleFraction" stringValue:[NSString stringWithFormat:@"%.20g", m[i]]]];
                [potentialSolidElement addChild:componentElement];
            }
        }
        
        [root addChild:potentialSolidElement];
    }
    
    [outputXMLDocument setRootElement:root];
    return outputXMLDocument;
}

#pragma mark -
#pragma mark Temperature sequence methods

-(double)initialTemperature {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->dspTstart;
}

-(void)setInitialTemperature:(double)tValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->T = tValue;
    silminState->dspTstart = tValue;
}

-(double)finalTemperature {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->dspTstop;
}

-(void)setFinalTemperature:(double)tValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->dspTstop = tValue;
}

-(double)incrementTemperature {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->dspTinc;
}

-(void)setIncrementTemperature:(double)tValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->dspTinc = tValue;
}

#pragma mark -
#pragma mark Pressure sequence methods

-(double)initialPressure {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->dspPstart;
}

-(void)setInitialPressure:(double)pValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->P = pValue;
    silminState->dspPstart = pValue;
}

-(double)finalPressure {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->dspPstop;
}

-(void)setFinalPressure:(double)pValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->dspPstop = pValue;
}

-(double)incrementPressure {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->dspPinc;
}

-(void)setIncrementPressure:(double)pValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->dspPinc = pValue;
}

#pragma mark -
#pragma mark Volume sequence methods

-(double)initialVolume {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->refVolume;
}

-(void)setInitialVolume:(double)vValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->refVolume = vValue;
}

-(double)finalVolume {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->dspVstop;
}

-(void)setFinalVolume:(double)vValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->dspVstop = vValue;
}

-(double)incrementVolume {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->dspVinc;
}

-(void)setIncrementVolume:(double)vValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->dspVinc = vValue;
}

#pragma mark -
#pragma mark Enthalpy sequence methods

-(double)initialEnthalpy {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->refEnthalpy;
}

-(void)setInitialEnthalpy:(double)hValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->refEnthalpy = hValue;
}

-(double)finalEnthalpy {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->dspHstop;
}

-(void)setFinalEnthalpy:(double)hValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->dspHstop = hValue;
}

-(double)incrementEnthalpy {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->dspHinc;
}

-(void)setIncrementEnthalpy:(double)hValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->dspHinc = hValue;
}

#pragma mark -
#pragma mark Entropy sequence methods

-(double)initialEntropy {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->refEntropy;
}

-(void)setInitialEntropy:(double)sValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->refEntropy = sValue;
}

-(double)finalEntropy {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->dspSstop;
}

-(void)setFinalEntropy:(double)sValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->dspSstop = sValue;
}

-(double)incrementEntropy {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return silminState->dspSinc;
}

-(void)setIncrementEntropy:(double)sValue {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    silminState->dspSinc = sValue;
}

#pragma mark -
#pragma mark Cal;culation mode inquiry methods

-(Boolean)isIsochoric {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return (silminState->isochoric) ? YES : NO;
}

-(Boolean)isIsenthalpic {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return (silminState->isenthalpic) ? YES : NO;
}

-(Boolean)isIsotropic {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    return (silminState->isentropic) ? YES : NO;
}

#pragma mark -
#pragma mark Calculation engine

-(Boolean)performMELTScalculation:(NSUInteger)type {
    NodeList *nodePointer = getNodeListPointer([self nodeIndex]);
    silminState = nodePointer->silminState;
    SilminState *previousSilminState = nodePointer->previousSilminState;
    previousSilminState = copySilminStateStructure(silminState, previousSilminState);
    nodePointer->previousSilminState = previousSilminState;
    
    switch (type) {
        case RUN_LIQUIDUS_CALC:
            meltsStatus.status = GENERIC_INTERNAL_ERROR;
            while(!liquidus());
            break;
        case RUN_EQUILIBRATE_CALC:
            meltsStatus.status = GENERIC_INTERNAL_ERROR;
            if (silminState->isenthalpic) {
                correctTforChangeInEnthalpy();
                NSLog(@"Before silimn() call, refH = %lf, corrected T = %lf", silminState->refEnthalpy, silminState->T);
            } else if (silminState->isentropic) {
                correctTforChangeInEntropy();
                NSLog(@"Before silimn() call, refS = %lf, corrected T = %lf", silminState->refEntropy, silminState->T);
            } else if (silminState->isochoric) {
                correctPforChangeInVolume();
                NSLog(@"Before silimn() call, refV = %lf, corrected P = %lf", silminState->refVolume, silminState->P);
            }
            while(!silmin());
            if      (meltsStatus.status == SILMIN_ADD_LIQUID_1) { NSLog(@"... !!! <><><><>  Failure in silmin(): ADD_LIQUID_1"); meltsStatus.status = GENERIC_INTERNAL_ERROR; }
            else if (meltsStatus.status == SILMIN_ADD_LIQUID_2) { NSLog(@"... !!! <><><><>  Failure in silmin(): ADD_LIQUID_2"); meltsStatus.status = GENERIC_INTERNAL_ERROR; }
            else if (meltsStatus.status == SILMIN_ADD_LIQUID_3) { NSLog(@"... !!! <><><><>  Failure in silmin(): ADD_LIQUID_3"); meltsStatus.status = GENERIC_INTERNAL_ERROR; }
            else if (meltsStatus.status == SILMIN_LIN_MAX     ) { NSLog(@"... !!! <><><><>  Failure in silmin(): LIN_MAX");  }
            else if (meltsStatus.status == SILMIN_LIN_ZERO    ) { NSLog(@"... !!! <><><><>  Failure in silmin(): LIN_ZERO"); }
            else if (meltsStatus.status == SILMIN_QUAD_MAX    ) { NSLog(@"... !!! <><><><>  Failure in silmin(): QUAD_MAX"); }
            else if (meltsStatus.status == SILMIN_RANK        ) { NSLog(@"... !!! <><><><>  Failure in silmin(): RANK");     }
            if (silminState->isenthalpic) NSLog(@"Aftersilimn() call,  refH = %lf, corrected T = %lf", silminState->refEnthalpy, silminState->T);
            else if (silminState->isentropic) NSLog(@"Aftersilimn() call,  refS = %lf, corrected T = %lf", silminState->refEntropy, silminState->T);
            else if (silminState->isochoric) NSLog(@"Aftersilimn() call,  refV = %lf, corrected P = %lf", silminState->refVolume, silminState->P);
            break;
        case RETURN_WITHOUT_CALC:
            meltsStatus.status = SILMIN_SUCCESS;
            break;
        case RETURN_DO_FRACTIONATION:
            doBatchFractionation();
            meltsStatus.status = SILMIN_SUCCESS;
            break;
        case RUN_WET_LIQUIDUS_CALC:
            meltsStatus.status = GENERIC_INTERNAL_ERROR;
            int *oldIncSolids = (int *) malloc((size_t) npc*sizeof(NSUInteger));
            double oldT = 0.0;
            NSUInteger iter = 0;
            
            do {
                oldT = silminState->T;
                for (NSUInteger i=0, j=0; i<npc; i++) if ((solids[i].type == PHASE) && (solids[i].nr == 0 || (solids[i].nr > 0 && solids[i].convert != NULL))) {
                    oldIncSolids[j] = (silminState->incSolids)[j];
                    (silminState->incSolids)[j] = FALSE;
                    if (!strcmp("water", solids[i].label)) (silminState->incSolids)[j] = TRUE;
                    j++;
                }
                while(!silmin());
                NSLog(@"<><><><> !!! <><><><> T after equilibrate: %lf", silminState->T);
                if (meltsStatus.status != SILMIN_SUCCESS) {
                    NSLog(@"<><><><> !!! <><><><>  Failure in silmin() stage of findWetLiquidus. Aborting ...");
                    break;
                }
                
                for (NSUInteger i=0, j=0; i<npc; i++) if ((solids[i].type == PHASE) && (solids[i].nr == 0 || (solids[i].nr > 0 && solids[i].convert != NULL))) {
                    (silminState->incSolids)[j] = oldIncSolids[j];
                    j++;
                }
                while(!liquidus());
                NSLog(@"<><><><> !!! <><><><> T after liquidus: %lf, iter: %ld", silminState->T, iter);
                if (meltsStatus.status != LIQUIDUS_SUCCESS) {
                    NSLog(@"<><><><> !!! <><><><>  Failure in liquidus() stage of findWetLiquidus. Aborting ...");
                    break;
                }
                
                silminState->dspTstart = silminState->T;
                silminState->dspTstop  = silminState->T;
                iter++;
            } while ((fabs(oldT - silminState->T) > 0.5) && (iter < 50));
            
            if (iter == 50) {
                meltsStatus.status = GENERIC_INTERNAL_ERROR;
                NSLog(@"<><><><> !!! <><><><> Unable to locate (Wet) liquidus.");
            } else NSLog(@"<><><><> !!! <><><><> Found (Wet) liquidus at %lf (C) and %lf MPa.", silminState->T-273.15, silminState->P/10.0);
            free(oldIncSolids);
            break;
        default:
            break;
    }
    if (meltsStatus.status != GENERIC_INTERNAL_ERROR) return YES; else return NO;
}

@end