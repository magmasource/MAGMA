/*
 easyMelts (c) 2020 Einari Suikkanen
*/
#include "melts_interface.hpp"
#include "e_utility.hpp"

#include <fstream>
#include <iostream>

#include <cmath>
#include <map>
#include <utility>

//C includes for MELTS
#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

//assert
#include <cassert>

//
#include <limits>

#ifdef __cplusplus
extern "C" {
#endif
#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "status.h"
#ifdef __cplusplus
}
#endif

#define NO_STATUS 9999;

MeltsStatus meltsStatus;

void (*additionalOutput)(char *filename) = NULL;
char *addOutputFileName = NULL;

int calculationMode = MODE__MELTS;
int quad_tol_modifier = 1;

//MELTS INTERFACE CLASS FUNCTIONS

MeltsInterface::MeltsInterface() {
    for (size_t i = 0; i < m_Composition.size(); ++i)
        m_Composition.at(i) = 0.0;
}

MeltsInterface::~MeltsInterface() {
    DestroySilminState();
}

void MeltsInterface::DestroySilminState() {
    if (p_SS) {
        if (p_SS->fracSComp != NULL) {
            for (int i = 0; i < npc; ++i) {
                free(p_SS->fracSComp[i]);
                p_SS->fracSComp[i] = NULL;
            }
            free(p_SS->fracSComp);
            free(p_SS->nFracCoexist);
            p_SS->fracSComp = NULL;
            p_SS->nFracCoexist = NULL;
        }
        if (p_SS->fracLComp != NULL)
            free(p_SS->fracLComp);
        p_SS->fracLComp = NULL;

        ClearAllAssimilants();

        if (p_SS->yLiq != NULL) free(p_SS->yLiq);
        p_SS->yLiq = NULL;
        if (p_SS->ySol != NULL) free(p_SS->ySol);
        p_SS->ySol = NULL;

        destroySilminStateStructure(p_SS);
    }

    p_SS = nullptr;
}

void MeltsInterface::Normalize() {
    double sum = 0.0;
    for (double d : m_Composition) {
        sum += d;
    }
    for (size_t i = 0; i < m_Composition.size(); i++) {
        m_Composition.at(i) = m_Composition.at(i) / sum * 100.0;
    }
}

void MeltsInterface::InitializeMelts(int melts_version) {
    m_MeltsVersion = melts_version;
    calculationMode = melts_version;
    if (m_MeltsVersion > 4 || m_MeltsVersion < 1) {
        m_MeltsVersion = MODE__MELTS;
        std::cout << "Invalid melts version: Reverting to Melts 1.0.x" << std::endl;
    }
    if (p_SS) {
        DestroySilminState();
    }

    if (m_MeltsVersion == MODE__MELTS) {
        liquid = meltsLiquid;
        solids = meltsSolids;
        nlc = meltsNlc;
        nls = meltsNls;
        npc = meltsNpc;
    } else if (m_MeltsVersion == MODE__MELTSandCO2 || m_MeltsVersion == MODE__MELTSandCO2_H2O) {
        liquid = meltsFluidLiquid;
        solids = meltsFluidSolids;
        nlc = meltsFluidNlc;
        nls = meltsFluidNls;
        npc = meltsFluidNpc;
    } else if (m_MeltsVersion == MODE_pMELTS) {
        liquid = pMeltsLiquid;
        solids = pMeltsSolids;
        nlc = pMeltsNlc;
        nls = pMeltsNls;
        npc = pMeltsNpc;
    }

    InitComputeDataStruct();

    m_MeltsIsInitialized = true;

    this->CreateSilminState();

    if (!m_Phases.empty()) m_Phases.clear();
    GetPhaseNames(&m_Phases);
    std::cout << "Amount of phases: " << m_Phases.size() << std::endl;

    meltsStatus.status = NO_STATUS;
}

bool MeltsInterface::ReadyToEquilibrate() {
    return (m_MeltsIsInitialized && m_SilminStateCreated && m_CompositionSet && m_ParametersSet);
}

//Creates silminstate with calculation parameters. Required.

void MeltsInterface::CreateSilminState() {
    if (p_SS) {
        DestroySilminState();
    }

    m_InitTP = std::pair<double, double>(0, 0);
    m_CurrentStep = 0;
    m_LastIndex = 0;
    m_Failure = false;

    p_SS = allocSilminStatePointer();

    SetFractionate();

    p_SS->fo2Path = m_Fo2Path;
    p_SS->nLiquidCoexist = 1;
    p_SS->multipleLiqs = 0; //Allow multiple liquids?

    p_SS->T = 0;
    p_SS->dspTstart = 0;
    p_SS->dspTstop = 0;
    p_SS->dspTinc = 0;
    p_SS->P = 0;
    p_SS->dspPstart = 0;
    p_SS->dspPstop = 0;
    p_SS->dspPinc = 0;

    p_SS->fracSComp = NULL;
    p_SS->fracLComp = NULL;
    p_SS->dspAssimComp = NULL;
    p_SS->nDspAssimComp = NULL;
    p_SS->assimComp = NULL;
    p_SS->nAssimComp = NULL;

    p_SS->dspAssimT = 1000.;
    p_SS->assimT = 1000.;
    p_SS->dspAssimInc = 1;

    p_SS->assimInc = 0;
    p_SS->assimMass = 0.0;
    p_SS->dspAssimMass = 0.0;
    p_SS->dspAssimLiqM = 0.0;
    p_SS->assimilate = 0;

    p_SS->yLiq = NULL;
    p_SS->ySol = NULL;

    p_SS->isenthalpic = 0;
    p_SS->isentropic = 0;
    p_SS->isochoric = 0;
    p_SS->refEnthalpy = 0.0;
    p_SS->refEntropy = 0.0;
    p_SS->refVolume = 0.0;

    m_Composition = std::array<double, 20>();

    int i, j;
    for (i = 0, j = 0; i < npc; i++)
        if (solids[i].type == PHASE) {
            p_SS->incSolids[j] = TRUE; /*All solids*/
            j++;
        }

    p_SS->incSolids[npc] = TRUE; /*Allows liquid*/

    m_LiquidusT = NaN;
    m_CompositionSet = false;
    m_ParametersSet = false;

    if (!m_Steps.empty()) m_Steps.clear();
    if (!m_SuppressedPhases.empty()) m_SuppressedPhases.clear();

    meltsStatus.status = NO_STATUS;

    m_SilminStateCreated = true;
}

bool MeltsInterface::SetSuppressedPhases(std::map<int, std::string> suppressed_phases) {
    if (!p_SS) return false;

    m_SuppressedPhases = suppressed_phases;

    int i, j;
    for (i = 0, j = 0; i < npc; i++)
        if (solids[i].type == PHASE) {
            if (suppressed_phases.find(i) != suppressed_phases.end()) {
                p_SS->incSolids[j] = FALSE;
                j++;
            } else {
                p_SS->incSolids[j] = TRUE;
                j++;
            }
        }

    return true;
}

bool MeltsInterface::ClearSuppressedPhases() {
    if (!p_SS) return false;

    if (!m_SuppressedPhases.empty()) m_SuppressedPhases.clear();

    int i, j;
    for (i = 0, j = 0; i < npc; i++)
        if (solids[i].type == PHASE) {
            p_SS->incSolids[j] = TRUE; /*All solids*/
            j++;
        }

    return true;
}

bool MeltsInterface::SetFractionate(bool solids, bool fluid, bool liquid) {
    if (!p_SS) return false;

    p_SS->fractionateFlu = fluid ? 1 : 0;
    p_SS->fractionateSol = solids ? 1 : 0;
    p_SS->fractionateLiq = liquid ? 1 : 0;

    if ((p_SS->fractionateSol || p_SS->fractionateFlu) && p_SS->fracSComp == NULL) {
        p_SS->fracSComp = (double **)calloc((unsigned)npc, sizeof(double *));
        p_SS->nFracCoexist = (int *)calloc((unsigned)npc, sizeof(int));
    }
    if (p_SS->fractionateLiq && p_SS->fracLComp == NULL) {
        p_SS->fracLComp = (double *)calloc((unsigned)nlc, sizeof(double));
    }

    return true;
}

bool MeltsInterface::SetMode(int mode) {
    if (!p_SS) return false;

    if (mode == 0) {
        p_SS->isenthalpic = 0;
        p_SS->isentropic = 0;
        p_SS->isochoric = 0;
    } else if (mode == 1) {
        p_SS->isenthalpic = 1;
        p_SS->isentropic = 0;
        p_SS->isochoric = 0;
    } else if (mode == 2) {
        p_SS->isenthalpic = 0;
        p_SS->isentropic = 1;
        p_SS->isochoric = 0;
    } else if (mode == 3) {
        p_SS->isenthalpic = 0;
        p_SS->isentropic = 0;
        p_SS->isochoric = 1;
    } else
        SetMode(0);

    return true;
}

bool MeltsInterface::SetCalcSteps(int steps) {
    m_CalcSteps = steps + 1; //INITIAL EQUILIBRATION STEP, NOT SAVED WITH DATA, IS ADDED TO STEPS

    return true;
}

bool MeltsInterface::SetInitialTP(double initial_t, double initial_p) {
    if (!p_SS) return false;

    p_SS->T = initial_t + 273.15;
    p_SS->dspTstart = initial_t;
    p_SS->dspTstop = initial_t;
    p_SS->dspTinc = 0.0;
    p_SS->P = initial_p;
    p_SS->dspPstart = initial_p;
    p_SS->dspPstop = initial_p;
    p_SS->dspPinc = 0.0;

    p_SS->dspHinc = 0.0;
    p_SS->dspVinc = 0.0;
    p_SS->dspSinc = 0.0;

    m_ParametersSet = true;

    return true;
}

bool MeltsInterface::SetFO2Path(int fo2_path) {
    if (fo2_path < 0 || fo2_path > 19)
        return false;

    m_Fo2Path = fo2_path;

    if (!p_SS)
        return false;

    p_SS->fo2Path = fo2_path;

    return true;
}

bool MeltsInterface::SetComposition(std::array<double, 20> composition) {
    if (!p_SS) return false;

    m_Composition = composition;

    int i, j;
    double total = 0.0;

    /*
     Normalizes automatically
     */
    for (const double &d : m_Composition)
        total += d;

    if (total != 0.0)
        for (double &d : m_Composition)
            d = d / total * 100.0;

    /*
    Calculates bulk composition in moles and total mass of liquid (nc = component oxide)
     */
    for (i = 0, p_SS->liquidMass = 0.0; i < nc; i++) {
        (p_SS->bulkComp)[i] = m_Composition[i] / bulkSystem[i].mw;
        p_SS->liquidMass += m_Composition[i];
    }
    /*
    Calculates moles of cations & oxygen in liquid, nlc = components in liquid
     */
    for (int i = 0; i < nlc; i++)
        for ((p_SS->liquidComp)[0][i] = 0.0, p_SS->oxygen = 0.0, j = 0; j < nc; j++) {
            (p_SS->liquidComp)[0][i] += (p_SS->bulkComp)[j] * (bulkSystem[j].oxToLiq)[i];
            p_SS->oxygen += (p_SS->bulkComp)[j] * (bulkSystem[j].oxToLiq)[i] * (oxygen.liqToOx)[i];
        }

    m_CompositionSet = true;

    return true;
}

bool MeltsInterface::SetMultiLiq(bool arg) {
    if (!p_SS) return false;
    p_SS->multipleLiqs = arg ? 1 : 0;
    return true;
}

bool MeltsInterface::ClearAllAssimilants() {
    if (!p_SS) return false;

    if (p_SS->dspAssimComp != NULL) {
        for (int i = 0; i < npc + nc; ++i) {
            free(p_SS->dspAssimComp[i]);
            p_SS->dspAssimComp[i] = NULL;
        }
        free(p_SS->dspAssimComp);
        p_SS->dspAssimComp = NULL;
        free(p_SS->nDspAssimComp);
        p_SS->nDspAssimComp = NULL;
    }

    if (p_SS->assimComp != NULL) {
        for (int i = 0; i < npc + nlc; ++i) {
            free(p_SS->assimComp[i]);
            p_SS->assimComp[i] = NULL;
        }
        free(p_SS->assimComp);
        p_SS->assimComp = NULL;
        free(p_SS->nAssimComp);
        p_SS->nAssimComp = NULL;
    }

    p_SS->dspAssimMass = 0.0;
    p_SS->dspAssimLiqM = 0.0;
    p_SS->dspAssimT = 1000.;
    p_SS->assimT = 1000.;
    p_SS->dspAssimInc = 1; //how many steps
    /*frees all memory*/
    return true;
}

/*phase_index = npc+nc-1, oxides also*/
bool MeltsInterface::AddAssimilant(int phase_index, double mass, std::vector<double> end_members) {
    if (!p_SS) return false;

    //if (std::isnan(p_SS->dspAssimMass))
    if (isnan(p_SS->dspAssimMass))
        p_SS->dspAssimMass = mass;
    else
        p_SS->dspAssimMass += mass;

    if (phase_index == npc) {
        p_SS->dspAssimMass -= p_SS->dspAssimLiqM;
        p_SS->dspAssimLiqM = mass;
    }

    p_SS->dspAssimUnits = ASSIM_PADB_UNITS_WEIGHT; //

    /*ALLOCATE MEMORY FOR COMPOSITIONS IF NOT YET*/
    //to assimilate
    if (p_SS->nDspAssimComp == NULL) p_SS->nDspAssimComp = (int *)calloc((unsigned)(npc + nc), sizeof(int));
    if (p_SS->dspAssimComp == NULL) p_SS->dspAssimComp = (double **)calloc((unsigned)(npc + nc), sizeof(double *));
    //assimilated
    if (p_SS->assimComp == NULL) {
        p_SS->assimComp = (double **)calloc((unsigned)(npc + nlc), sizeof(double *));
        for (int i = 0; i < npc + nlc; ++i) {
            p_SS->assimComp[i] = (double *)calloc((unsigned)1, sizeof(double));
        }
    }
    if (p_SS->nAssimComp == NULL) p_SS->nAssimComp = (int *)calloc((unsigned)(npc + nlc), sizeof(int));

    if (phase_index == npc) p_SS->nAssimComp[phase_index + 1] = 1;
    if (phase_index < npc) p_SS->nAssimComp[phase_index] = 1;

    double *mm = (double *)malloc((unsigned)nc * sizeof(double));
    if (phase_index < npc) {
        if (solids[phase_index].na == 1) {
            (p_SS->assimComp)[phase_index][0] += mass / (solids[phase_index].mw);
        } else {
            double mw = 0.0;
            for (int j = 0; j < solids[phase_index].na; j++)
                mw += end_members[j + 1] * solids[phase_index + 1 + j].mw / 100.0;
            double moles_to_add = (mw == 0.0) ? 0.0 : mass / mw;
            for (int j = 0; j < solids[phase_index].na; j++)
                (p_SS->assimComp)[phase_index + 1 + j][0] += end_members[j + 1] * moles_to_add / 100.0;
            (p_SS->assimComp)[phase_index][0] += moles_to_add;
        }
    }
    if (phase_index == npc) {
        for (int i = 0; i < nc; i++)
            mm[i] = end_members[i] == 0.0 ? 0.0 : end_members[i] * mass / (100.0 * bulkSystem[i].mw);
        for (int i = 0; i < nlc; i++) {
            (p_SS->assimComp)[i + npc][0] = 0.0;
            for (int j = 0; j < nc; j++)
                (p_SS->assimComp)[i + npc][0] += mm[j] * (bulkSystem[j].oxToLiq)[i];
        }
    }

    free(mm);

    return true;
}

bool MeltsInterface::InitAssimilantTData() {
    if (!p_SS) return false;
    //if (std::isnan(p_SS->dspAssimMass) || p_SS->dspAssimMass == 0.0) return false;
    if (isnan(p_SS->dspAssimMass) || p_SS->dspAssimMass == 0.0) return false;
    {
        double *m = (double *)malloc((unsigned)nlc * sizeof(double));
        double *r = (double *)malloc((unsigned)(nlc - 1) * sizeof(double));
        double enthalpy, entropy, volume, totalEnthalpy, totalEntropy,
            totalVolume;

        totalEnthalpy = 0.0;
        totalEntropy = 0.0;
        totalVolume = 0.0;

        for (int j = 0; j < npc; j++)
            if (solids[j].type == PHASE)
                for (int ns = 0; ns < (p_SS->nAssimComp)[j]; ns++) {
                    if (solids[j].na == 1) {
                        gibbs(p_SS->assimT + 273.15, p_SS->P, (char *)solids[j].label, &(solids[j].ref), NULL, NULL, &(p_SS->assimTD));
                        enthalpy = (p_SS->assimComp)[j][ns] * (p_SS->assimTD).h;
                        entropy = (p_SS->assimComp)[j][ns] * (p_SS->assimTD).s;
                        volume = (p_SS->assimComp)[j][ns] * (p_SS->assimTD).v;
                    } else {
                        for (int i = 0; i < solids[j].na; i++)
                            m[i] = (p_SS->assimComp)[j + 1 + i][ns];
                        (*solids[j].convert)(SECOND, THIRD, p_SS->assimT + 273.15, p_SS->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
                        (*solids[j].hmix)(FIRST, p_SS->assimT + 273.15, p_SS->P, r, &enthalpy);
                        (*solids[j].smix)(FIRST, p_SS->assimT + 273.15, p_SS->P, r, &entropy, NULL, NULL);
                        (*solids[j].vmix)(FIRST, p_SS->assimT + 273.15, p_SS->P, r, &volume, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
                        enthalpy *= (p_SS->assimComp)[j][ns];
                        entropy *= (p_SS->assimComp)[j][ns];
                        volume *= (p_SS->assimComp)[j][ns];
                        for (int i = 0; i < solids[j].na; i++) {
                            gibbs(p_SS->assimT + 273.15, p_SS->P, (char *)solids[j + 1 + i].label, &(solids[j + 1 + i].ref), NULL, NULL, &(p_SS->assimTD));
                            enthalpy += m[i] * (p_SS->assimTD).h;
                            entropy += m[i] * (p_SS->assimTD).s;
                            volume += m[i] * (p_SS->assimTD).v;
                        }
                    }
                    totalEnthalpy += enthalpy;
                    totalEntropy += entropy;
                    totalVolume += volume;
                }

        for (int ns = 0; ns < (p_SS->nAssimComp)[npc + 1]; ns++) {
            double totalMoles;
            for (int i = 0, totalMoles = 0.0; i < nlc; i++) {
                m[i] = (p_SS->assimComp)[npc + i][ns];
                totalMoles += m[i];
            }
            conLiq(SECOND, THIRD, p_SS->assimT + 273.15, p_SS->P, NULL, m, r, NULL, NULL, NULL, NULL);
            hmixLiq(FIRST, p_SS->assimT + 273.15, p_SS->P, r, &enthalpy, NULL);
            smixLiq(FIRST, p_SS->assimT + 273.15, p_SS->P, r, &entropy, NULL, NULL, NULL);
            vmixLiq(FIRST, p_SS->assimT + 273.15, p_SS->P, r, &volume, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
            enthalpy *= totalMoles;
            entropy *= totalMoles;
            volume *= totalMoles;
            for (int i = 0; i < nlc; i++) {
                gibbs(p_SS->assimT + 273.15, p_SS->P, (char *)liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(p_SS->assimTD));
                enthalpy += m[i] * (p_SS->assimTD).h;
                entropy += m[i] * (p_SS->assimTD).s;
                volume += m[i] * (p_SS->assimTD).v;
            }
            totalEnthalpy += enthalpy;
            totalEntropy += entropy;
            totalVolume += volume;
        }

        (p_SS->assimTD).g = 0.0;
        (p_SS->assimTD).h = totalEnthalpy;
        (p_SS->assimTD).s = totalEntropy;
        (p_SS->assimTD).v = totalVolume;
        (p_SS->assimTD).cp = 0.0;
        (p_SS->assimTD).dcpdt = 0.0;
        (p_SS->assimTD).dvdt = 0.0;
        (p_SS->assimTD).dvdp = 0.0;
        (p_SS->assimTD).d2vdt2 = 0.0;
        (p_SS->assimTD).d2vdp2 = 0.0;
        (p_SS->assimTD).d2vdtdp = 0.0;

        free(m);
        free(r);
    }
    return true;
}

//REDISTRIBUTES SET COMPOSITION ACCORDING TO AN FO2 BUFFER AND RENORMALIZES (check button callbacks))
//P, T must be set prior, also composition, also fo2_buffer

bool MeltsInterface::RedistributeFeOx(int fo2_buffer) {
    if (!p_SS) return false;
    if (!m_CompositionSet) return false;
    if (p_SS->fo2Path < 1 || p_SS->fo2Path > 19) return false;
    if (!p_SS->P || !p_SS->T) return false;

    double log10fo2 = getlog10fo2(p_SS->T, p_SS->P, p_SS->fo2Path);
    double *moles = (double *)malloc((unsigned)nc * sizeof(double));

    for (int j = 0; j < nc; j++)
        moles[j] = m_Composition[j] / bulkSystem[j].mw;

    conLiq(FIRST | SEVENTH, FIRST, p_SS->T, p_SS->P, moles, (double *)NULL, (double *)NULL,
           (double *)NULL, (double **)NULL, (double ***)NULL, &log10fo2);

    for (int j = 0; j < nc; j++)
        m_Composition[j] = moles[j] * bulkSystem[j].mw;

    free(moles);

    SetComposition(m_Composition);

    return true;
}

std::string GetErrorString() {
    std::string s = "";
    switch (meltsStatus.status) {
    case SILMIN_SUCCESS:
        return s = "SILMIN_SUCCESS";
        break;
    case SILMIN_QUAD_MAX:
        s = "SILMIN_QUAD_MAX";
        break;
    case SILMIN_LIN_ZERO:
        s = "SILMIN_LIN_ZERO";
        break;
    case SILMIN_LIN_MAX:
        s = "SILMIN_LIN_MAX";
        break;
    case SILMIN_ADD_LIQUID_1:
        s = "SILMIN_ADD_LIQUID_1";
        break;
    case SILMIN_ADD_LIQUID_2:
        s = "SILMIN_ADD_LIQUID_2";
        break;
    case SILMIN_ADD_LIQUID_3:
        s = "SILMIN_ADD_LIQUID_3";
        break;
    case SILMIN_RANK:
        s = "SILMIN_RANK";
        break;
    case SILMIN_TIME:
        s = "SILMIN_TIME";
        break;
    case GENERIC_INTERNAL_ERROR:
        s = "GENERIC_INTERNAL_ERROR";
        break;
    case LIQUIDUS_SUCCESS:
        return s = "LIQUIDUS_SUCCESS";
        break;
    case LIQUIDUS_MAX_T:
        return s = "LIQUIDUS_MAX_T";
        break;
    case LIQUIDUS_MIN_T:
        return s = "LIQUIDUS_MIN_T";
        break;
    case LIQUIDUS_TIME:
        return s = "LIQUIDUS_TIME";
        break;
    case LIQUIDUS_MULTIPLE:
        return s = "LIQUIDUS_MULTIPLE";
        break;
    default:
        s = "NO_STATUS";
        break;
    }
    return s + " ";
}

void MeltsInterface::SetIncrements() {
    p_SS->T = p_SS->T + step_inc.T;
    p_SS->dspTstop = p_SS->T - 273.15;
    p_SS->P = p_SS->P + step_inc.P;
    p_SS->dspPstart = p_SS->P;
    p_SS->dspPstop = p_SS->P;
    p_SS->refEnthalpy = p_SS->refEnthalpy + step_inc.H;
    p_SS->dspHstop = p_SS->refEnthalpy;
    if (std::abs(step_inc.H) > 0.0) {
        correctTforChangeInEnthalpy();
    }
    p_SS->refEntropy = p_SS->refEntropy + step_inc.S;
    p_SS->dspSstop = p_SS->refEntropy;
    if (std::abs(step_inc.S) > 0.0) {
        correctTforChangeInEntropy();
    }
    p_SS->refVolume = p_SS->refVolume + step_inc.V / 10.; /*cc to J/bar*/
    p_SS->dspVstop = p_SS->refVolume;
    if (std::abs(step_inc.V) > 0.0) {
        correctPforChangeInVolume();
    }
}

/*Moved from silmin() to here*/
void MeltsInterface::AssimilateSetComposition() {
    if (silminState->assimilate && silminState->dspAssimMass > 0.0) {

        silminState->assimMass += silminState->dspAssimMass;
        if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0)) silminState->refEnthalpy += (silminState->assimTD).h;
        if (silminState->isentropic && (silminState->refEntropy != 0.0)) silminState->refEntropy += (silminState->assimTD).s;
        if (silminState->isochoric && (silminState->refVolume != 0.0)) silminState->refVolume += (silminState->assimTD).v;
        silminState->assimInc++;

        for (int i = 0; i < npc; i++)
            for (int ns = 0; ns < (silminState->nAssimComp)[i]; ns++) {
                if (solids[i].type == PHASE && solids[i].na == 1) {
                    for (int k = 0; k < nc; k++)
                        (silminState->bulkComp)[k] += (silminState->assimComp)[i][ns] * (solids[i].solToOx)[k];
                    if (silminState->liquidMass > 0.0)
                        for (int k = 0; k < nlc; k++)
                            (silminState->liquidComp)[0][k] += (silminState->assimComp)[i][ns] * (solids[i].solToLiq)[k];
                    if (silminState->liquidMass <= 0.0) { /* if liquid is absent, assimilate as solid */
                        if (!(silminState->nSolidCoexist)[i]) (silminState->nSolidCoexist)[i] = 1;
                        (silminState->solidComp)[i][0] += (silminState->assimComp)[i][ns];
                    }
                    if (silminState->fo2Path != FO2_NONE) silminState->oxygen += (oxygen.solToOx)[i] * (silminState->assimComp)[i][ns];
                } else if (solids[i].type == PHASE && solids[i].na > 1) {
                    for (int j = 0; j < solids[i].na; j++) {
                        for (int k = 0; k < nc; k++)
                            (silminState->bulkComp)[k] += (silminState->assimComp)[i + 1 + j][ns] * (solids[i + 1 + j].solToOx)[k];
                        if (silminState->liquidMass > 0.0)
                            for (int k = 0; k < nlc; k++)
                                (silminState->liquidComp)[0][k] += (silminState->assimComp)[i + 1 + j][ns] * (solids[i + 1 + j].solToLiq)[k];
                        if (silminState->liquidMass <= 0.0) { /* if liquid is absent, assimilate as solid -- risky ? */
                            if (!(silminState->nSolidCoexist)[i]) (silminState->nSolidCoexist)[i] = 1;
                            (silminState->solidComp)[i + 1 + j][0] += (silminState->assimComp)[i + 1 + j][ns];
                        }
                        if (silminState->fo2Path != FO2_NONE) silminState->oxygen += (oxygen.solToOx)[i + 1 + j] * (silminState->assimComp)[i + 1 + j][ns];
                    }
                }
            }
        for (int ns = 0; ns < (silminState->nAssimComp)[npc + 1]; ns++) { /*number of liquids*/
            for (int i = 0; i < nlc; i++) {
                (silminState->liquidComp)[0][i] += (silminState->assimComp)[npc + i][ns];
                for (int j = 0; j < nc; j++)
                    (silminState->bulkComp)[j] += (silminState->assimComp)[npc + i][ns] * (liquid[i].liqToOx)[j];
                if (silminState->fo2Path != FO2_NONE) silminState->oxygen += (oxygen.liqToOx)[i] * (silminState->assimComp)[npc + i][ns];
            }
            silminState->liquidMass = 0.0;
            for (int i = 0; i < nc; i++) {
                for (int j = 0; j < nlc; j++)
                    silminState->liquidMass += silminState->liquidComp[0][j] * (liquid[j].liqToOx)[i] * bulkSystem[i].mw;
            }
        }
        if (silminState->isenthalpic && (silminState->refEnthalpy != 0.0)) {
            correctTforChangeInEnthalpy();
        }
        if (silminState->isentropic && (silminState->refEntropy != 0.0)) {
            correctTforChangeInEntropy();
        }
        if (silminState->isochoric && (silminState->refVolume != 0.0)) {
            correctPforChangeInVolume();
        }
    }
}

int MeltsInterface::GetMeltsStatus() {
    return meltsStatus.status;
}

int MeltsInterface::StopEquilibration() {
    m_SilminEnd = 1;
    m_CalcStepsRemaining = 0;
    Elog::Log().AddLog("Equilibration stopped at T=" + MyUtil::DoubleAsString(silminState->T - 273.15, 2) + " status " + GetErrorString(), Severity::CAUTION);
    return meltsStatus.status;
}

bool MeltsInterface::Equilibrate() {
    if (!p_SS) return false;

    //Assimilation without an assimilant tends to crash Melts
    //if (p_SS->assimilate && (p_SS->dspAssimMass == 0.0 || std::isnan(p_SS->dspAssimMass))) p_SS->assimilate = 0;
    if (p_SS->assimilate && (p_SS->dspAssimMass == 0.0 || isnan(p_SS->dspAssimMass))) p_SS->assimilate = 0;

    meltsStatus.status = NO_STATUS;
    //calc_index is sent to silmin() to fix crash that is caused by stopping equilibration
    //in the middle of silmin, recreating silminstate and starting again
    static int calc_index = 0;
    calc_index = m_LastIndex;

    silminState = p_SS;

    for (m_CalcStepsRemaining = m_CalcSteps; m_CalcStepsRemaining > 0; --m_CalcStepsRemaining) {
        m_SilminEnd = 0;
        while (!m_SilminEnd) {
            m_SilminEnd = silmin(calc_index);
            calc_index++;
            if (calc_index == INT_MAX) calc_index = 1;
            if (p_SS->ready_to_output) {                                       //Saves data at the same time as Melts normally does it (before fractionation, assimilation or parameter change)
                if (m_LastIndex == 0 || m_CalcStepsRemaining != m_CalcSteps) { //We dont want initial step to be saved with the data (except first time) since system state does not change visibly
                    m_Steps.push_back(SilminData(p_SS, m_LastIndex));
                    m_LastIndex++;
                }
            }
            if (m_CalcStepsRemaining == 0) {
                m_SilminEnd = 1;
                break;
            } //this situation calcsteps have been changed by stopequilibration function
        }
        //silmin() ended with failure.
        if (meltsStatus.status != SILMIN_SUCCESS) {
            Elog::Log().AddLog("Equilibration failed/stopped at T=" + MyUtil::DoubleAsString(p_SS->T - 273.15, 2) + " with value " + GetErrorString(), Severity::WARNING);
            std::cout << "Equilibration failed with error code: " << GetErrorString() << meltsStatus.status << std::endl;
            m_Failure = true;
            silminState = nullptr;
            return false;
        }
        if (m_CalcStepsRemaining > 1) { //CHANGE STATE and Assimilate
            this->SetIncrements();      //change T, P, H, S, V
            if (silminState->assimilate) this->AssimilateSetComposition();
        }
    }
    silminState = nullptr;

    return true;
}

bool MeltsInterface::Liquidus() {

    silminState = p_SS;

    while (!liquidus())
        ;

    if (meltsStatus.status == LIQUIDUS_SUCCESS) {
        m_LiquidusT = silminState->T - 273.15;
        std::cout << "Liquidus found at: " << m_LiquidusT << " C" << std::endl;
    } else {
        std::cout << "Liquidus calculation failed! " << GetErrorString() << std::endl;
    }

    silminState = nullptr;

    /*Update state*/

    p_SS->dspTstart = p_SS->T - 273.15;
    p_SS->dspTstop = p_SS->dspTstart;

    for (int i = 0; i < nc; ++i) {
        m_Composition[i] = bulkSystem[i].mw * p_SS->bulkComp[i];
    }
    SetComposition(m_Composition);

    meltsStatus.status = NO_STATUS;

    return true;
}

//Populates unordered map with Phases in Melts
void MeltsInterface::GetPhaseNames(std::map<int, std::string> *index_name) {
    for (int i = 0; i < npc; i++) {
        if (solids[i].type == PHASE) {
            index_name->insert(std::make_pair(i, std::string(solids[i].label)));
            m_PhasesVec.push_back(std::string(solids[i].label));
        }
    }
}

//Populates unorderd map with all components for each phase
bool MeltsInterface::GetPhaseComponents(int phase_index, std::map<int, std::string> *index_name) {
    if (solids[phase_index].na == 1) return false;
    for (int i = 0; i < solids[phase_index].na; i++) {
        index_name->insert(std::make_pair(phase_index + 1 + i, std::string(solids[phase_index + 1 + i].label)));
    }
    return true;
}

#include "file_utility.hpp"

bool MeltsInterface::SaveMeltsInputData(const std::vector<double> &assimilation_values) {
    if (!p_SS)
        return false;

    auto &&DAS = MyUtil::DoubleAsString;

    std::fstream output;
    std::ios::openmode flags;
    flags = std::ios::out | std::ios::trunc;

    std::string orig_title = m_RunTitle.empty() ? "Untitled" : m_RunTitle;
    std::string title = m_RunTitle.empty() ? "Untitled" : m_RunTitle;

    FileUtility futil;
    int titleid = 1;
    while (futil.FileExists(title + std::string(".melts"))) {
        title = orig_title + " (" + std::to_string(titleid) + ")";
        titleid++;
    }

    output.open(title + std::string(".melts"), flags);

    output << "Title: " << title << "\n";

    for (int i = 0; i < nc; i++)
        if ((p_SS->bulkComp)[i] != 0.0)
            output << "Initial Composition: " << bulkSystem[i].label << " " << MyUtil::DoubleAsString((p_SS->bulkComp[i] * bulkSystem[i].mw), 4) << "\n";

    output << "Initial Temperature: " << DAS(std::max(p_SS->T - 273.15, 0.0), 2) << "\n"
           << "Initial Pressure: " << DAS(p_SS->P, 2) << "\n";

    if (p_SS->isenthalpic) {
        output << "Increment Pressure: " << DAS(step_inc.P, 2) << "\n";
        output << "Increment Enthalpy: " << DAS(step_inc.H, 2) << "\n";
    } else if (p_SS->isentropic) {
        output << "Increment Pressure: " << DAS(step_inc.P, 2) << "\n";
        output << "Increment Entropy: " << DAS(step_inc.S, 2) << "\n";
    } else if (p_SS->isochoric) {
        output << "Increment Temperature: " << DAS(step_inc.T, 2) << "\n";
        output << "Increment Volume: " << DAS(step_inc.V, 2) << "\n";
    } else {
        output << "Increment Temperature: " << DAS(step_inc.T, 2) << "\n";
        output << "Increment Pressure: " << DAS(step_inc.P, 2) << "\n";
    }

    //fo2 path
    int path = p_SS->fo2Path;
    std::string p_s;

    if (path == 0) p_s = "None";
    if (path == 1) p_s = "HM";
    if (path == 2) p_s = "NNO";
    if (path == 3) p_s = "FMQ";
    if (path == 4) p_s = "COH";
    if (path == 5) p_s = "IW";
    if (path == 6) p_s = "+3FMQ";
    if (path == 7) p_s = "+2FMQ";
    if (path == 8) p_s = "+1FMQ";
    if (path == 9) p_s = "-1FMQ";
    if (path == 10) p_s = "-2FMQ";
    if (path == 11) p_s = "-3FMQ";
    if (path == 12) p_s = "-4FMQ";
    if (path == 13) p_s = "-5FMQ";
    if (path == 14) p_s = "-6FMQ";
    if (path == 15) p_s = "-7FMQ";
    if (path == 16) p_s = "-8FMQ";
    if (path == 17) p_s = "-9FMQ";
    if (path == 18) p_s = "+0.5FMQ";
    if (path == 19) p_s = "+1.5FMQ";
    if (path > 19 || path < 0) p_s = "None";

    output << "log fo2 Path: " << p_s << "\n";

    int j;
    for (int i = 0, j = 0; i < npc; i++) {
        if (solids[i].type == PHASE) {
            if (p_SS->incSolids[j] == FALSE) {
                output << "Suppress: " << solids[i].label << "\n";
            }
            j++;
        }
    }

    if (p_SS->fractionateSol)
        output << "Mode: Fractionate Solids\n";
    if (p_SS->fractionateLiq)
        output << "Mode: Fractionate Liquids\n";
    if (p_SS->fractionateFlu)
        output << "Mode: Fractionate Fluids\n";
    if (p_SS->multipleLiqs)
        output << "Mode: Multiple Liquids\n";
    if (p_SS->isenthalpic)
        output << "Mode: Isenthalpic\n";
    if (p_SS->isentropic)
        output << "Mode: Isentropic\n";
    if (p_SS->isochoric)
        output << "Mode: Isochoric\n";

    //assimilation
    //if (!std::isnan(p_SS->dspAssimMass) && p_SS->dspAssimMass > 0.0) {
    if (!isnan(p_SS->dspAssimMass) && p_SS->dspAssimMass > 0.0) {
        double ass_mass = p_SS->dspAssimMass;

        output << "Assimilant: Temperature " << DAS(p_SS->assimT, 2) << "\n"
               << "Assimilant: Mass " << DAS(p_SS->dspAssimMass, 2) << "\n"
               << "Assimilant: Increments " << DAS(1.0, 2) << "\n"
               << "Assimilant: Liquid Mass " << DAS(p_SS->dspAssimLiqM, 2) << "\n"
               << "Assimilant: Units Wt %\n";

        for (int i = 0; i < npc; i++) {
            if (solids[i].type == PHASE) {
                double d = assimilation_values[i] / ass_mass * 100.0;
                output << "Assimilant: " << solids[i].label << " " << DAS(d, 2) << "\n";
            } else {
                output << "Assimilant: " << solids[i].label << " " << DAS(assimilation_values[i], 2) << "\n";
            }
        }
        for (int i = npc; i < npc + nc; ++i)
            output << "Assimilant: " << bulkSystem[i - npc].label << " " << DAS(assimilation_values[i], 2) << "\n";
    }

    output.close();

    return true;
}

std::vector<std::string> GetWords(std::string line) {
    std::vector<std::string> ws;

    std::string word = "";
    for (auto x : line) {
        if (x == ' ') {
            ws.push_back(word);
            word = "";
        } else {
            word = word + x;
        }
    }
    return ws;
}

std::vector<double> MeltsInterface::LoadFromFile(const char *file) {
    std::ifstream input(file);

    std::vector<double> assimilation_values(npc + nc + 1, 0.0);
    std::vector<int> assimilant_idx_found;
    bool assimilant_liquid_found = false;
    std::array<double, 20> composition = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.00, 0.0, 0.0, 0.0, 0.00, 0.00, 0.0, 0.0, 0.0, 0.00, 0.00, 0.00, 0.00, 0.00};
    double init_temp = 0.0;
    double init_pres = 0.0;
    bool fractionate_sol = false;
    bool fractionate_liq = false;
    bool fractionate_flu = false;

    if (input) {
        CreateSilminState();
    } else {
        CreateSilminState();
        return assimilation_values;
    }

    auto s_end = std::string::npos;

    std::string line;
    while (std::getline(input, line)) {
        if (line.find("Title:") != s_end) {
            m_RunTitle = line.substr(7);
            continue;
        }
        if (line.find("Initial Composition:") != s_end) {
            m_CompositionSet = true;
            std::string compstr("Initial Composition: ");
            for (int i = 0; i < nc; i++) {
                std::string label(bulkSystem[i].label);
                if (line.find(label) != s_end) {
                    double weight_perc = std::stod(line.substr(std::string(compstr + label).length()));
                    //p_SS->bulkComp[i] = weight_perc / bulkSystem[i].mw;
                    composition[i] = weight_perc;
                    break;
                }
            }
            continue;
        }
        if (line.find("Initial Temperature:") != s_end) {
            std::string init_t_string = line.substr(21);
            init_temp = std::stod(init_t_string);

            continue;
        }
        if (line.find("Initial Pressure:") != s_end) {
            std::string init_p_string = line.substr(18);
            init_pres = std::stod(init_p_string);
            continue;
        }
        if (line.find("Increment Pressure:") != s_end) {
            step_inc.P = std::stod(line.substr(20));
            continue;
        }
        if (line.find("Increment Temperature:") != s_end) {
            step_inc.T = std::stod(line.substr(23));
            continue;
        }
        if (line.find("Increment Enthalpy:") != s_end) {
            step_inc.H = std::stod(line.substr(20));
            continue;
        }
        if (line.find("Increment Entropy:") != s_end) {
            step_inc.S = std::stod(line.substr(19));
            continue;
        }
        if (line.find("Increment Volume:") != s_end) {
            step_inc.V = std::stod(line.substr(18));
            continue;
        }
        if (line.find("log fo2 Path:") != s_end) {
            std::string path = line.substr(14);
            if (path == "None")
                p_SS->fo2Path = 0;
            else if (path == "HM")
                p_SS->fo2Path = 1;
            else if (path == "NNO")
                p_SS->fo2Path = 2;
            else if (path == "FMQ")
                p_SS->fo2Path = 3;
            else if (path == "COH")
                p_SS->fo2Path = 4;
            else if (path == "IW")
                p_SS->fo2Path = 5;
            else if (path == "+3FMQ")
                p_SS->fo2Path = 6;
            else if (path == "+2FMQ")
                p_SS->fo2Path = 7;
            else if (path == "+1FMQ")
                p_SS->fo2Path = 8;
            else if (path == "-1FMQ")
                p_SS->fo2Path = 9;
            else if (path == "-2FMQ")
                p_SS->fo2Path = 10;
            else if (path == "-3FMQ")
                p_SS->fo2Path = 11;
            else if (path == "-4FMQ")
                p_SS->fo2Path = 12;
            else if (path == "-5FMQ")
                p_SS->fo2Path = 13;
            else if (path == "-6FMQ")
                p_SS->fo2Path = 14;
            else if (path == "-7FMQ")
                p_SS->fo2Path = 15;
            else if (path == "-8FMQ")
                p_SS->fo2Path = 16;
            else if (path == "-9FMQ")
                p_SS->fo2Path = 17;
            else if (path == "+0.5FMQ")
                p_SS->fo2Path = 18;
            else if (path == "+1.5FMQ")
                p_SS->fo2Path = 19;
            else
                p_SS->fo2Path = 0;

            m_Fo2Path = p_SS->fo2Path;

            continue;
        }
        if (line.find("Suppress:") != s_end) {
            std::string label = line.substr(10);
            for (int i = 0, j = 0; i < npc; i++) {
                if (solids[i].type == PHASE) {
                    if (label == std::string(solids[i].label)) {
                        p_SS->incSolids[j] = FALSE;
                        break;
                    }
                    j++;
                }
            }
            continue;
        }
        if (line.find("Mode: Fractionate Solids") != s_end) {
            fractionate_sol = true;
            continue;
        }
        if (line.find("Mode: Fractionate Liquids") != s_end) {
            fractionate_liq = true;
            continue;
        }
        if (line.find("Mode: Fractionate Fluids") != s_end) {
            fractionate_flu = true;
            continue;
        }
        if (line.find("Mode: Multiple Liquids") != s_end) {
            p_SS->multipleLiqs = TRUE;
            continue;
        }
        if (line.find("Mode: Isenthalpic") != s_end) {
            p_SS->isenthalpic = TRUE;
            continue;
        }
        if (line.find("Mode: Isentropic") != s_end) {
            p_SS->isentropic = TRUE;
            continue;
        }
        if (line.find("Mode: Isochoric") != s_end) {
            p_SS->isochoric = TRUE;
            continue;
        }

        //assim increments are always 1

        bool found_idx = false;
        if (line.find("Assimilant: ") != s_end) {
            if (line.find("Assimilant: Temperature") != s_end) {
                double at = std::stod(line.substr(24));
                p_SS->assimT = at;
                p_SS->dspAssimT = at;
                continue;
            }
            if (line.find("Assimilant: Mass") != s_end) {
                p_SS->dspAssimMass = std::stod(line.substr(17));
                continue;
            }
            if (line.find("Assimilant: Liquid Mass") != s_end) {
                p_SS->dspAssimLiqM = std::stod(line.substr(24));
                assimilation_values[npc + nc] = p_SS->dspAssimLiqM;
                continue;
            }
            if (line.find("Units") != s_end) {
                continue;
            }
            if (line.find("Increments") != s_end) {
                continue;
            }
            std::vector<std::string> words = GetWords(line);
            size_t words_size = words.size();
            for (int i = 0; i < npc; i++) {
                std::string label(solids[i].label);
                if (words_size > 1 && label == words[1]) {
                    double as_amount = std::stod(line.substr(label.length() + 13));
                    if (solids[i].type == PHASE) {
                        assimilant_idx_found.push_back(i);
                        assimilation_values[i] = as_amount * p_SS->dspAssimMass / 100.;
                    } else {
                        assimilation_values[i] = as_amount;
                    }
                    found_idx = true;
                    break;
                }
            }

            if (found_idx) continue;

            for (int i = npc; i < npc + nc; ++i) {
                std::string label(bulkSystem[i - npc].label);
                if (line.find(label) != s_end) {
                    double as_amount = std::stod(line.substr(label.length() + 13));
                    assimilation_values[i] = as_amount;
                    assimilant_liquid_found = true;
                    break;
                }
            }
        }
    }

    SetComposition(composition);
    SetInitialTP(init_temp, init_pres);
    SetInitTP(init_temp, init_pres);
    SetFractionate(fractionate_sol, fractionate_flu, fractionate_liq);

    for (int idx : assimilant_idx_found) {
        if (assimilation_values[idx] > 0.0) {
            std::vector<double> values;
            for (int j = 0; j < solids[idx].na + 1; ++j) {
                values.push_back(assimilation_values[idx + j]);
            }
            AddAssimilant(idx, assimilation_values[idx], values);
        }
    }

    if (assimilant_liquid_found) {
        std::vector<double> values;
        for (int x = 0; x < nc; ++x) {
            values.push_back(assimilation_values[npc + x]);
        }
        if (assimilation_values[npc+nc] > 0.0)
            AddAssimilant(npc, assimilation_values[npc + nc], values);
    }
    if (assimilant_liquid_found || !assimilant_idx_found.empty())
        InitAssimilantTData();

    return assimilation_values;
}
