/*
 easyMelts (c) 2020-2024 Einari Suikkanen
 easyMelts (c) 2025 Paula Antoshechkina
*/

#ifndef MELTS_INTERFACE_HPP
#define MELTS_INTERFACE_HPP

#ifndef BATCH_VERSION
#define BATCH_VERSION
#endif

#ifndef EASYMELTS_UPDATE_SYSTEM
#define EASYMELTS_UPDATE_SYSTEM
#endif

#include <array>
#include <vector>
#include <limits>
#include <map>
#include <memory>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif
#include "silmin.h"
#ifdef __cplusplus
}
#endif

#ifndef NaN
#define NaN std::numeric_limits<double>::quiet_NaN()
#endif


class SilminData {
private:
public:

    struct Prop {
        std::string label = "";
        std::string formula = "";
        int melts_phase_index = -1;
        std::vector<std::pair<std::string, double>> end_members; //label + amount;
        double mass = NaN; /*mass at step*/
        /*calculated*/
        double density = NaN; /*g/cm3*/
        double viscosity = NaN; /*log 10 poise*/
        double gibbs_energy = NaN; /*joules*/
        double enthalpy = NaN; /*J*/
        double entropy = NaN; /*J/K*/
        double volume = NaN; /*cm3*/
        double spec_heat_cap = NaN; /*specific heat capacity Cp = J/K*/
        double moles;
    };

    SilminData(SilminState* data, int index) {
        FillStructure(data, index);

    }

    void FillStructure(SilminState* state, int index) {
        static int idx = 0;
        static double f_liq_mass = 0.0;
        static double f_sol_mass = 0.0;


        if ((idx = index) == 0) {
            f_liq_mass = 0.0, f_sol_mass = 0.0;


        }



        if (state->isenthalpic) this->isenthalpic = true;
        if (state->isentropic) this->isentropic = true;
        if (state->isochoric) this->isochoric = true;

        T = state->T - 273.15;
        P = state->P;
        fO2 = state->fo2;

        for (int i = 0; i < 20; ++i) {
            bulk_comp_n[i] = state->bulkComp[i];
        }

        double moles = 0.0, viscosity, gLiq = 0.0, hLiq = 0.0, sLiq = 0.0, vLiq = 0.0, cpLiq = 0.0, dvdtLiq = 0.0, dvdpLiq = 0.0, mLiq = 0.0,
                mass = 0.0, totalMass = 0.0,
                gibbsEnergy = 0.0, totalGibbsEnergy = 0.0,
                enthalpy = 0.0, totalEnthalpy = 0.0,
                entropy = 0.0, totalEntropy = 0.0,
                volume = 0.0, totalVolume = 0.0,
                heatCapacity = 0.0, totalHeatCapacity = 0.0,
                dVolumeDt = 0.0, totaldVolumeDt = 0.0,
                dVolumeDp = 0.0, totaldVolumeDp = 0.0;

        double* r = (double *) malloc((unsigned) nlc * sizeof (double));
        double* m = (double *) malloc((unsigned) nlc * sizeof (double));

        if (state->liquidMass > 0.0) {


            //double* m = (double *) malloc((unsigned) nlc * sizeof (double)); //activity

            for (int nl = 0; nl < state->nLiquidCoexist; nl++) {
                conLiq(SECOND, THIRD, state->T, state->P, NULL, state->liquidComp[nl], r, NULL, NULL, NULL, NULL);

                gmixLiq(FIRST, state->T, state->P, r, &gibbsEnergy, NULL, NULL);
                hmixLiq(FIRST, state->T, state->P, r, &enthalpy, NULL);
                smixLiq(FIRST, state->T, state->P, r, &entropy, NULL, NULL, NULL);
                vmixLiq(FIRST | FOURTH | FIFTH,
                        state->T, state->P, r, &volume, NULL, NULL, &dVolumeDt, &dVolumeDp, NULL, NULL, NULL, NULL, NULL, NULL);
                cpmixLiq(FIRST, state->T, state->P, r, &heatCapacity, NULL, NULL);
                visLiq(FIRST, state->T, state->P, r, &viscosity);

                moles = 0.0;
                for (int i = 0; i < nlc; i++) moles += (state->liquidComp)[nl][i];
                gibbsEnergy *= moles;
                enthalpy *= moles;
                entropy *= moles;
                volume *= moles;
                heatCapacity *= moles;
                dVolumeDt *= moles;
                dVolumeDp *= moles;

                for (int i = 0; i < nlc; i++) {
                    gibbsEnergy += (state->liquidComp)[nl][i]*(liquid[i].cur).g;
                    enthalpy += (state->liquidComp)[nl][i]*(liquid[i].cur).h;
                    entropy += (state->liquidComp)[nl][i]*(liquid[i].cur).s;
                    volume += (state->liquidComp)[nl][i]*(liquid[i].cur).v;
                    heatCapacity += (state->liquidComp)[nl][i]*(liquid[i].cur).cp;
                    dVolumeDt += (state->liquidComp)[nl][i]*(liquid[i].cur).dvdt;
                    dVolumeDp += (state->liquidComp)[nl][i]*(liquid[i].cur).dvdp;
                }

                std::vector<double> oxVal(nc, 0.0);
                double oxSum = 0.0;
                for (int i = 0; i < nc; i++) {
                    for (int j = 0; j < nlc; j++) oxVal[i] += (liquid[j].liqToOx)[i]*(state->liquidComp)[nl][j]; //moles
                    oxVal[i] *= bulkSystem[i].mw; //grams
                    oxSum += oxVal[i];

                }
                if (oxSum != 0.0)
                    for (int i = 0; i < nc; i++) {
                        oxVal[i] /= oxSum;
                        oxVal[i] *= 100.;
                    }


                //oxSum = mass (g), oxSum/10*volume = density in g/cm3 (volume = J/bar )
                //oxVal = mass frac... oxVal*100 = wt.%

                Prop p;
                p.gibbs_energy = gibbsEnergy;
                p.enthalpy = enthalpy;
                p.entropy = entropy;
                p.volume = volume * 10.; // cc
                p.mass = oxSum; // g
                p.viscosity = viscosity; // log 10 poise
                p.density = oxSum / 10. * volume; // g/cc
                p.spec_heat_cap = heatCapacity;
                p.label = std::string("Liquid ") + std::to_string(nl);
                p.melts_phase_index = npc; //
                liq_properties.insert(std::make_pair(nl, p));
                liquid_composition.insert(std::make_pair(nl, oxVal));


                gLiq += gibbsEnergy;
                hLiq += enthalpy;
                sLiq += entropy;
                vLiq += volume;
                cpLiq += heatCapacity;
                mLiq += oxSum;
                dvdtLiq += dVolumeDt;
                dvdpLiq += dVolumeDp;


            }

        }

        for (int j = 0; j < npc; j++)
            for (int ns = 0; ns < (state->nSolidCoexist)[j]; ns++) {
                if (solids[j].na == 1) {
                    mass = (state->solidComp)[j][ns] * solids[j].mw;
                    gibbsEnergy = (state->solidComp)[j][ns]*(solids[j].cur).g;
                    enthalpy = (state->solidComp)[j][ns]*(solids[j].cur).h;
                    entropy = (state->solidComp)[j][ns]*(solids[j].cur).s;
                    volume = (state->solidComp)[j][ns]*(solids[j].cur).v;
                    heatCapacity = (state->solidComp)[j][ns]*(solids[j].cur).cp;
                    dVolumeDt = (state->solidComp)[j][ns]*(solids[j].cur).dvdt;
                    dVolumeDp = (state->solidComp)[j][ns]*(solids[j].cur).dvdp;
                    totalMass += (state->solidComp)[j][ns] * solids[j].mw;
                    totalGibbsEnergy += (state->solidComp)[j][ns]*(solids[j].cur).g;
                    totalEnthalpy += (state->solidComp)[j][ns]*(solids[j].cur).h;
                    totalEntropy += (state->solidComp)[j][ns]*(solids[j].cur).s;
                    totalVolume += (state->solidComp)[j][ns]*(solids[j].cur).v;
                    totalHeatCapacity += (state->solidComp)[j][ns]*(solids[j].cur).cp;
                    totaldVolumeDt += (state->solidComp)[j][ns]*(solids[j].cur).dvdt;
                    totaldVolumeDp += (state->solidComp)[j][ns]*(solids[j].cur).dvdp;

                    Prop p;
                    p.label = std::string(solids[j].label);
                    p.formula = std::string(solids[j].formula);
                    p.density = (volume == 0.0) ? 0.0 : mass / (10. * volume);
                    p.enthalpy = enthalpy;
                    p.entropy = entropy;
                    p.gibbs_energy = gibbsEnergy;
                    p.mass = mass;
                    p.spec_heat_cap = heatCapacity;
                    p.volume = volume * 10.;
                    p.melts_phase_index = j;

                    sol_properties.push_back(p);


                } else {
                    char *formula;
                    mass = 0.0;
                    for (int i = 0; i < solids[j].na; i++) {
                        m[i] = (state->solidComp)[j + 1 + i][ns];
                        mass += (state->solidComp)[j + 1 + i][ns] * solids[j + 1 + i].mw;
                    }
                    (*solids[j].convert)(SECOND, THIRD, state->T, state->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
                    (*solids[j].display)(FIRST, state->T, state->P, r, &formula);
                    (*solids[j].gmix) (FIRST, state->T, state->P, r, &gibbsEnergy, NULL, NULL, NULL);
                    (*solids[j].hmix) (FIRST, state->T, state->P, r, &enthalpy);
                    (*solids[j].smix) (FIRST, state->T, state->P, r, &entropy, NULL, NULL);
                    (*solids[j].vmix) (FIRST | FOURTH | FIFTH,
                            state->T, state->P, r, &volume, NULL, NULL, &dVolumeDt, &dVolumeDp, NULL, NULL, NULL, NULL, NULL);
                    (*solids[j].cpmix)(FIRST, state->T, state->P, r, &heatCapacity, NULL, NULL);
                    gibbsEnergy *= (state->solidComp)[j][ns];
                    enthalpy *= (state->solidComp)[j][ns];
                    entropy *= (state->solidComp)[j][ns];
                    volume *= (state->solidComp)[j][ns];
                    heatCapacity *= (state->solidComp)[j][ns];
                    dVolumeDt *= (state->solidComp)[j][ns];
                    dVolumeDp *= (state->solidComp)[j][ns];
                    for (int i = 0; i < solids[j].na; i++) {
                        gibbsEnergy += m[i]*(solids[j + 1 + i].cur).g;
                        enthalpy += m[i]*(solids[j + 1 + i].cur).h;
                        entropy += m[i]*(solids[j + 1 + i].cur).s;
                        volume += m[i]*(solids[j + 1 + i].cur).v;
                        heatCapacity += m[i]*(solids[j + 1 + i].cur).cp;
                        dVolumeDt += m[i]*(solids[j + 1 + i].cur).dvdt;
                        dVolumeDp += m[i]*(solids[j + 1 + i].cur).dvdp;
                    }
                    totalMass += mass;
                    totalGibbsEnergy += gibbsEnergy;
                    totalEnthalpy += enthalpy;
                    totalEntropy += entropy;
                    totalVolume += volume;
                    totalHeatCapacity += heatCapacity;
                    totaldVolumeDt += dVolumeDt;
                    totaldVolumeDp += dVolumeDp;

                    Prop p;
                    p.label = std::string(solids[j].label);
                    p.formula = std::string(formula);
                    free(formula);
                    p.density = (volume == 0.0) ? 0.0 : mass / (10. * volume);
                    p.enthalpy = enthalpy;
                    p.entropy = entropy;
                    p.gibbs_energy = gibbsEnergy;
                    p.mass = mass;
                    p.spec_heat_cap = heatCapacity;
                    p.volume = volume * 10.;
                    p.end_members.reserve(solids[j].na);
                    p.melts_phase_index = j;


                    for (int i = 0; i < solids[j].na; i++) {
                        p.end_members.push_back(std::make_pair(std::string(solids[j + 1 + i].label), 100.0 * m[i] / (state->solidComp)[j][ns]));
                    }
                    sol_properties.push_back(p);
                }
            }

        sol_tot_properties.density = (totalVolume == 0) ? 0.0 : totalMass / (10. * totalVolume);
        sol_tot_properties.enthalpy = totalEnthalpy;
        sol_tot_properties.entropy = totalEntropy;
        sol_tot_properties.gibbs_energy = totalGibbsEnergy;
        sol_tot_properties.label = "Total solids";
        sol_tot_properties.mass = totalMass;
        sol_tot_properties.spec_heat_cap = totalHeatCapacity;
        sol_tot_properties.volume = totalVolume * 10.;


        sys_prop_nofrac.viscosity = (vLiq < totalVolume) ? NaN : viscosity - 2.0 * log10(1.0 - 2.0 * totalVolume / (totalVolume + vLiq));
        sys_prop_nofrac.mass = mLiq + totalMass;
        sys_prop_nofrac.density = (totalVolume + vLiq == 0.0) ? 0.0 : (mLiq + totalMass) / (10.0 * (vLiq + totalVolume));
        sys_prop_nofrac.gibbs_energy = gLiq + totalGibbsEnergy;
        sys_prop_nofrac.enthalpy = hLiq + totalEnthalpy;
        sys_prop_nofrac.entropy = sLiq + totalEntropy;
        sys_prop_nofrac.volume = (vLiq + totalVolume)*10.;
        sys_prop_nofrac.spec_heat_cap = cpLiq + totalHeatCapacity;


        //set references at first constrained step...
        if (state->isenthalpic && (state->refEnthalpy == 0.0)) state->refEnthalpy = hLiq + totalEnthalpy;
        if (state->isentropic && (state->refEntropy == 0.0)) state->refEntropy = sLiq + totalEntropy;
        if (state->isochoric && (state->refVolume == 0.0)) state->refVolume = vLiq + totalVolume;

        if (!state->isenthalpic) state->refEnthalpy = 0;
        if (!state->isentropic) state->refEntropy = 0;
        if (!state->isochoric) state->refVolume = 0;

        //        state->refEnthalpy = hLiq + totalEnthalpy;
        //        state->refEntropy = sLiq + totalEntropy;
        //        state->refVolume = vLiq + totalVolume;
        //        arg->dspHstop = arg->refEnthalpy;
        //        arg->dspSstop = arg->refEntropy;
        //        arg->dspVstop = arg->refVolume;

        //if (state->fractionateSol || state->fractionateFlu || state->fractionateLiq) {
        frac_mass = state->fracMass;
        //}

        if (state->fractionateSol || state->fractionateFlu) fractionate_solids = true;

        if (f_sol_mass > 0.0 || state->fractionateSol || state->fractionateFlu) {
            for (int j = 0; j < npc; j++) {
                if (state->fractionateSol && !state->fractionateFlu && (strcmp((char *) solids[j].label, "water") == 0 || strcmp((char *) solids[j].label, "fluid") == 0)) continue;
                if (!state->fractionateSol && state->fractionateFlu && (strcmp((char *) solids[j].label, "water") != 0))
                    if (strcmp((char *) solids[j].label, "fluid") != 0) continue;
                //solids[j].cur thermodynamic properties change over simulation so these values keep changing a tiny bit even though they are "fractionated". Not great.
                for (int ns = 0; ns < (state->nFracCoexist)[j]; ns++) {
                    if (solids[j].na == 1) {
                        mass = (state->fracSComp)[j][ns] * solids[j].mw;
                        gibbsEnergy = (state->fracSComp)[j][ns]*(solids[j].cur).g;
                        enthalpy = (state->fracSComp)[j][ns]*(solids[j].cur).h;
                        entropy = (state->fracSComp)[j][ns]*(solids[j].cur).s;
                        volume = (state->fracSComp)[j][ns]*(solids[j].cur).v;
                        heatCapacity = (state->fracSComp)[j][ns]*(solids[j].cur).cp;
                        dVolumeDt = (state->fracSComp)[j][ns]*(solids[j].cur).dvdt;
                        dVolumeDp = (state->fracSComp)[j][ns]*(solids[j].cur).dvdp;
                        totalMass += (state->fracSComp)[j][ns] * solids[j].mw;
                        totalGibbsEnergy += (state->fracSComp)[j][ns]*(solids[j].cur).g;
                        totalEnthalpy += (state->fracSComp)[j][ns]*(solids[j].cur).h;
                        totalEntropy += (state->fracSComp)[j][ns]*(solids[j].cur).s;
                        totalVolume += (state->fracSComp)[j][ns]*(solids[j].cur).v;
                        totalHeatCapacity += (state->fracSComp)[j][ns]*(solids[j].cur).cp;
                        totaldVolumeDt += (state->fracSComp)[j][ns]*(solids[j].cur).dvdt;
                        totaldVolumeDp += (state->fracSComp)[j][ns]*(solids[j].cur).dvdp;

                        Prop p;
                        p.label = std::string(solids[j].label);
                        p.formula = std::string(solids[j].formula);
                        p.density = (volume == 0.0) ? 0.0 : mass / (10. * volume);
                        p.enthalpy = enthalpy;
                        p.entropy = entropy;
                        p.gibbs_energy = gibbsEnergy;
                        p.mass = mass;
                        p.spec_heat_cap = heatCapacity;
                        p.volume = volume * 10.;
                        p.melts_phase_index = j;


                        frac_properties.push_back(p);

                        f_sol_mass += mass;


                    } else {
                        char *formula;
                        mass = 0.0;
                        for (int i = 0; i < solids[j].na; i++) {
                            m[i] = (state->fracSComp)[j + 1 + i][ns];
                            mass += (state->fracSComp)[j + 1 + i][ns] * solids[j + 1 + i].mw;
                        }
                        (*solids[j].convert)(SECOND, THIRD, state->T, state->P, NULL, m, r, NULL, NULL, NULL, NULL, NULL);
                        (*solids[j].display)(FIRST, state->T, state->P, r, &formula);
                        (*solids[j].gmix) (FIRST, state->T, state->P, r, &gibbsEnergy, NULL, NULL, NULL);
                        (*solids[j].hmix) (FIRST, state->T, state->P, r, &enthalpy);
                        (*solids[j].smix) (FIRST, state->T, state->P, r, &entropy, NULL, NULL);
                        (*solids[j].vmix) (FIRST | FOURTH | FIFTH,
                                state->T, state->P, r, &volume, NULL, NULL, &dVolumeDt, &dVolumeDp, NULL, NULL, NULL, NULL, NULL);
                        (*solids[j].cpmix)(FIRST, state->T, state->P, r, &heatCapacity, NULL, NULL);
                        gibbsEnergy *= (state->fracSComp)[j][ns];
                        enthalpy *= (state->fracSComp)[j][ns];
                        entropy *= (state->fracSComp)[j][ns];
                        volume *= (state->fracSComp)[j][ns];
                        heatCapacity *= (state->fracSComp)[j][ns];
                        dVolumeDt *= (state->fracSComp)[j][ns];
                        dVolumeDp *= (state->fracSComp)[j][ns];
                        for (int i = 0; i < solids[j].na; i++) {
                            gibbsEnergy += m[i]*(solids[j + 1 + i].cur).g;
                            enthalpy += m[i]*(solids[j + 1 + i].cur).h;
                            entropy += m[i]*(solids[j + 1 + i].cur).s;
                            volume += m[i]*(solids[j + 1 + i].cur).v;
                            heatCapacity += m[i]*(solids[j + 1 + i].cur).cp;
                            dVolumeDt += m[i]*(solids[j + 1 + i].cur).dvdt;
                            dVolumeDp += m[i]*(solids[j + 1 + i].cur).dvdp;
                        }

                        totalMass += mass;
                        totalGibbsEnergy += gibbsEnergy;
                        totalEnthalpy += enthalpy;
                        totalEntropy += entropy;
                        totalVolume += volume;
                        totalHeatCapacity += heatCapacity;
                        totaldVolumeDt += dVolumeDt;
                        totaldVolumeDp += dVolumeDp;

                        Prop p;
                        p.label = std::string(solids[j].label);
                        p.formula = std::string(formula);
                        free(formula);
                        p.density = (volume == 0.0) ? 0.0 : mass / (10. * volume);
                        p.enthalpy = enthalpy;
                        p.entropy = entropy;
                        p.gibbs_energy = gibbsEnergy;
                        p.mass = mass;
                        p.spec_heat_cap = heatCapacity;
                        p.volume = volume * 10.;
                        p.end_members.reserve(solids[j].na);
                        p.melts_phase_index = j;


                        for (int i = 0; i < solids[j].na; i++) {
                            p.end_members.push_back(std::make_pair(std::string(solids[j + 1 + i].label), 100.0 * (state->fracSComp)[j + 1 + i][ns] / (state->fracSComp)[j][ns]));
                        }
                        frac_properties.push_back(p);

                        f_sol_mass += mass;

                    }
                }
            }
        }

        if (f_liq_mass > 0.0 || state->fractionateLiq) {
            if (state->fractionateLiq) fractionate_liquid = true;
            char *formula;
            mass = 0.0;
            moles = 0.0;
            for (int i = 0; i < nlc; i++) {
                double mw = 0.0;
                for (int j = 0; j < nc; j++) mw += (liquid[i].liqToOx)[j] * bulkSystem[j].mw;
                m[i] = (state->fracLComp)[i];
                moles += m[i];
                mass += (state->fracLComp)[i] * mw;
            }
            if (mass > 0.0) {
                conLiq(SECOND, THIRD, state->T, state->P, NULL, m, r, NULL, NULL, NULL, NULL);
                dispLiq(FIRST, state->T, state->P, r, &formula);
                gmixLiq(FIRST, state->T, state->P, r, &gibbsEnergy, NULL, NULL);
                hmixLiq(FIRST, state->T, state->P, r, &enthalpy, NULL);
                smixLiq(FIRST, state->T, state->P, r, &entropy, NULL, NULL, NULL);
                vmixLiq(FIRST | FOURTH | FIFTH,
                        state->T, state->P, r, &volume, NULL, NULL, &dVolumeDt, &dVolumeDp, NULL, NULL, NULL, NULL, NULL, NULL);
                cpmixLiq(FIRST, state->T, state->P, r, &heatCapacity, NULL, NULL);
                gibbsEnergy *= moles;
                enthalpy *= moles;
                entropy *= moles;
                volume *= moles;
                heatCapacity *= moles;
                dVolumeDt *= moles;
                dVolumeDp *= moles;
                for (int i = 0; i < nlc; i++) {
                    gibbsEnergy += m[i]*(liquid[i].cur).g;
                    enthalpy += m[i]*(liquid[i].cur).h;
                    entropy += m[i]*(liquid[i].cur).s;
                    volume += m[i]*(liquid[i].cur).v;
                    heatCapacity += m[i]*(liquid[i].cur).cp;
                    dVolumeDt += m[i]*(liquid[i].cur).dvdt;
                    dVolumeDp += m[i]*(liquid[i].cur).dvdp;
                }
                totalMass += mass;
                totalGibbsEnergy += gibbsEnergy;
                totalEnthalpy += enthalpy;
                totalEntropy += entropy;
                totalVolume += volume;
                totalHeatCapacity += heatCapacity;
                totaldVolumeDt += dVolumeDt;
                totaldVolumeDp += dVolumeDp;


                frac_liq_properties.gibbs_energy = gibbsEnergy;
                frac_liq_properties.enthalpy = enthalpy;
                frac_liq_properties.entropy = entropy;
                frac_liq_properties.volume = volume * 10.; // cc
                frac_liq_properties.mass = mass; // g
                frac_liq_properties.formula = std::string(formula);
                free(formula);
                frac_liq_properties.density = (volume == 0.0) ? 0.0 : mass / 10. * volume; // g/cc
                frac_liq_properties.spec_heat_cap = heatCapacity;
                frac_liq_properties.label = std::string("Fractionated liquid");
                frac_liq_properties.melts_phase_index = npc;

                f_liq_mass += mass;
            }
        }

        sys_properties.viscosity = (vLiq < totalVolume) ? NaN : viscosity - 2.0 * log10(1.0 - 2.0 * totalVolume / (totalVolume + vLiq));
        sys_properties.mass = mLiq + totalMass;
        sys_properties.density = (totalVolume + vLiq == 0.0) ? 0.0 : (mLiq + totalMass) / (10.0 * (vLiq + totalVolume));

        sys_properties.gibbs_energy = gLiq + totalGibbsEnergy;
        sys_properties.enthalpy = hLiq + totalEnthalpy;
        sys_properties.entropy = sLiq + totalEntropy;
        sys_properties.volume = (vLiq + totalVolume)*10.;
        sys_properties.spec_heat_cap = cpLiq + totalHeatCapacity;

        if (state->fo2Path != FO2_NONE) {
            double mO2 = -state->oxygen;
            for (int nl = 0; nl < state->nLiquidCoexist; nl++) for (int i = 0; i < nlc; i++) mO2 += (oxygen.liqToOx)[i]*(state->liquidComp)[nl][i];
            for (int i = 0; i < npc; i++) for (int ns = 0; ns < (state->nSolidCoexist)[i]; ns++) {
                    if (solids[i].na == 1) mO2 += (oxygen.solToOx)[i]*(state->solidComp)[i][ns];
                    else {
                        for (int j = 0; j < solids[i].na; j++) mO2 += (oxygen.solToOx)[i + 1 + j]*(state->solidComp)[i + 1 + j][ns];
                    }
                }

            oxygen_properties.moles = mO2;
            oxygen_properties.mass = mO2 * 31.9988; //delta grams
            oxygen_properties.gibbs_energy = mO2 * (oxygen.cur).g;
            oxygen_properties.enthalpy = mO2 * (oxygen.cur).h;
            oxygen_properties.entropy = mO2 * (oxygen.cur).s;
            oxygen_properties.volume = mO2 * 10.0 * (oxygen.cur).v;
            oxygen_properties.spec_heat_cap = mO2 * (oxygen.cur).cp;
        }

        //assim_mass = (std::isnan(state->assimMass)) ? 0.0 : state->assimMass;
        assim_mass = (isnan(state->assimMass)) ? 0.0 : state->assimMass;
        if (state->assimilate) {
            assim_mass = state->assimMass;
            assim_t = state->dspAssimT;
            for (int j = 0; j < npc; j++) if (solids[j].type == PHASE) {
                    for (int ns = 0; ns < (state->nAssimComp)[j]; ns++) {
                        if (solids[j].na == 1) {
                            mass = (state->assimComp)[j][ns] * solids[j].mw;
                            Prop p;
                            p.mass = mass;
                            p.label = std::string(solids[j].label);
                            p.melts_phase_index = j;
                            assim_properties.push_back(p);
                        } else {
                            mass = 0.0;
                            for (int i = 0; i < solids[j].na; i++) mass += (state->assimComp)[j + 1 + i][ns] * solids[j + 1 + i].mw;
                            Prop p;
                            p.mass = mass;
                            p.label = std::string(solids[j].label);
                            p.end_members.reserve(solids[j].na);
                            p.melts_phase_index = j;

                            for (int i = 0; i < solids[j].na; i++) {
                                p.end_members.push_back(std::make_pair(std::string(solids[j + 1 + i].label), 100.0 * (state->assimComp)[j + 1 + i][ns] / (state->assimComp)[j][ns]));
                            }
                            assim_properties.push_back(p);
                        }
                    }
                }
            for (int ns = 0; ns < (state->nAssimComp)[npc + 1]; ns++) {
                assim_liq_comp = std::vector<double>(nc, 0.0);
                double oxSum = 0.0;
                for (int i = 0; i < nc; i++) {
                    for (int j = 0; j < nlc; j++) assim_liq_comp[i] += (liquid[j].liqToOx)[i]*(state->assimComp)[npc + j][ns]; //moles
                    assim_liq_comp[i] *= bulkSystem[i].mw; //grams
                    oxSum += assim_liq_comp[i];
                }
                if (oxSum != 0.0)
                    for (int i = 0; i < nc; i++) {
                        assim_liq_comp[i] /= oxSum;
                        assim_liq_comp[i] *= 100.;
                    }

                assim_liq_mass = oxSum;
            }
        }

        /*
         !!!!!!!!!!!!!!!
         */
        free(r); //hello C hello Explicit Memory Management my old friend
        free(m);
    }
    /*
     SYSTEM
     */
    /*
     NEEDS TOTAL FRAC SOLIDS & MELTS
     */
    std::array<double, 20> bulk_comp_n; /*bulk composition moles of oxides*/

    bool fractionate_solids = false;
    bool fractionate_liquid = false;
    bool isenthalpic = false;
    bool isentropic = false;
    bool isochoric = false;

    double T; /*temperature C*/
    double P; /*pressure*/
    double fO2; /*oxygen fugacity of system*/

    Prop sol_tot_properties;

    Prop sys_properties;
    Prop sys_prop_nofrac;
    Prop oxygen_properties;
    /*
     END SYSTEM
     */

    /*LIQUID*/
    std::map<int, std::vector<double>> liquid_composition; /*composition of n liquids in moles*/
    std::map<int, Prop> liq_properties; /*liquid properties at step*/

    /*SOLID*/
    std::vector<Prop> sol_properties;

    std::vector<Prop> frac_properties; //frac solids if present
    Prop frac_liq_properties; //frac liquid if present
    double frac_mass = NaN;

    std::vector<Prop> assim_properties; //assimilated minerals
    std::vector<double> assim_liq_comp; //assimilated liquid
    double assim_liq_mass = NaN;
    double assim_mass = NaN;
    double assim_t = NaN;


};

enum class SProcess {
    RUNNING = 0, STOPPED = 1
};

class MeltsInterface {
public:
    MeltsInterface();
    virtual ~MeltsInterface();

    MeltsInterface(MeltsInterface const &) = delete; // delete the copy constructor
    void operator=(MeltsInterface const &) = delete; // delete the copy-assignment operator

    void InitializeMelts(int melts_version);

    void CreateSilminState();
    void DestroySilminState();

    SilminState* GetSilminState() {
        return p_SS;
    }
     //STATUS
    int GetMeltsStatus();

    std::vector<double> LoadFromFile(const char* file); //load settings from file?
    bool SaveMeltsInputData(const std::vector<double> &assimilation_values);

    bool Liquidus();
    bool WetLiquidus();
    bool Equilibrate();
    int StopEquilibration();

    bool RedistributeFeOx(int fo2_buffer);
    void Normalize();

    bool SetNormalizeOnSave(bool set = true) {
        return m_NormalizeOnSave = set;
    }

    void SetTitle(std::string title) {
        m_RunTitle = title;
    }

    bool SetComposition(std::array<double, 20> composition); //

    bool ToggleCompositionSet(bool set = true) {
        return m_CompositionSet = set;
    }

    /*ASSIMILATION*/
    bool SetAssimilate(bool assimilate = true);
    bool AddAssimilant(int phase_index, double wtp_in_assm, std::vector<double> end_members);
    bool InitAssimilantTData();
    bool ClearAllAssimilants();
    void AssimilateSetComposition();

    bool SetFO2Path(int fo2_path);
    bool SetFO2Offset(double fo2_offset);
    bool SetFractionate(bool solids = false, bool fluid = false, bool liquid = false);
    bool SetMode(int mode); //isothermal, isenthalpic, isentropic, isochoric
    bool SetInitialTP(double initial_t, double initial_p);

    //next calc round steps
    bool SetCalcSteps(int steps);
    bool SetIncrement(int mode, double value);

    void SetIncrements();

    bool SetMultiLiq(bool arg);

    bool ToggleParametersSet(bool set = true) {
        return m_ParametersSet = set;
    }

    //GET MELTS INFORMATION
    void GetPhaseNames(std::map<int, std::string> *index_name);
    bool GetPhaseComponents(int phase_index, std::map<int, std::string> *index_name);

    int * GetStep() {
        return &m_CurrentStep;
    }

    const SilminData & GetData(int step) {
        return m_Steps.at(step);
    };

    const std::string GetTitle() const {
        return m_RunTitle;
    }

    const std::array<double, 20> & GetComposition() const {
        return m_Composition;
    }

    const std::vector<std::string> & GetFO2Paths() const {
        return m_FO2Paths;
    }

    const std::vector<std::string> & GetMeltsVersions() const {
        return m_MeltsVersions;
    }

    const std::vector<std::string> & GetCalculationModes() const {
        return m_CalculationModes;
    }

    const std::map<int, std::string> & GetPhases() const {
        return m_Phases;
    }

    const std::vector<std::string> & GetPhasesVec() const {
        return m_PhasesVec;
    }

    const std::map<int, std::string> & GetSuppressedPhases() const {
        return m_SuppressedPhases;
    }

    const std::vector<std::string> & GetOxideNames() const {
        return m_OxideNames;
    }

    const std::vector<SilminData> & GetData() const {
        return m_Steps;
    }

    bool SetSuppressedPhases(std::map<int, std::string> suppressed_phases);
    bool ClearSuppressedPhases();



    double GetLiquidusT() const {
        return m_LiquidusT;
    }

    //ASSERT VALUES SET
    bool ReadyToEquilibrate();

    bool CompositionSet() const {
        return m_CompositionSet;
    }

    bool TPSet() const {
        return m_ParametersSet;
    }

    bool MeltsInitialized() const {
        return m_MeltsIsInitialized;
    }

    bool SilminStateExists() const {
        return m_SilminStateCreated;
    }

    struct Inc {
        double T = 0.0;
        double P = 0.0;
        double H = 0.0;
        double S = 0.0;
        double V = 0.0;
    } step_inc;

    int GetStepsToCalculate() const {
        return m_CalcSteps - 1;
    }

    int GetStepsRemaining() const {
        return m_CalcStepsRemaining;
    }

    bool SilminRunning() const {
        return m_SilminEnd == 0 ? true : false;
    }

    bool SilminFailed() const {
        return m_Failure;
    }

    const std::pair<double, double> & GetInitTP() const {
        return m_InitTP;
    }

    void SetInitTP(double t, double p) {
        m_InitTP = std::pair<double, double>(t, p);
    }

private:
    std::pair<double, double> m_InitTP;
    int m_CalcSteps = 1;
    int m_SilminEnd = 1;
    int m_CalcStepsRemaining = 0; //step of current calculation
    bool m_Failure = false;

    int m_LastIndex = 0;

    std::vector<SilminData> m_Steps; //holds all data

    int m_CurrentStep = 0;

    int m_MeltsVersion = MODE__MELTS;

    std::string m_RunTitle = "Default";

    SilminState* p_SS = nullptr; /*CURRENT SILMINSTATE*/

    bool m_SilminStateCreated = false;
    bool m_MeltsIsInitialized = false; /**/
    bool m_CompositionSet = false;
    bool m_ParametersSet = false;

    bool m_NormalizeOnSave = true;

    std::array<double, 20> m_Composition; /* Initial composition of the system set by user */

    double m_LiquidusT = NaN; /*calculated by MELTS*/

    int m_Fo2Path = FO2_NONE;
    double m_Fo2Offset = 0.0;

    /*
    MODE__DEFAULT == xMELTS
    MODE_xMELTS == xMELTS (experimental 2.0.0)      0
    MODE__MELTS == rhyolite-MELTS 1.0.2             1
    MODE_pMELTS == pMELTS 5.6.1                     2
    MODE__MELTSandCO2 == rhyolite-MELTS 1.1.0       3
    MODE__MELTSandCO2_H2O = rhyolite-MELTS 1.2.0    4

     *
     */

    //const std::vector<std::string> m_FO2Paths{"None", "HM", "NNO", "QFM", "COH", "IW", "QFM_P3", "QFM_P2", "QFM_P1", "QFM_M1", "QFM_M2", "QFM_M3", "QFM_M4", "QFM_M5", "QFM_M6", "QFM_M7", "QFM_M8", "QFM_M9", "FO2_QFM_P0_5", "FO2_QFM_P1_5"};
    const std::vector<std::string> m_FO2Paths{"None", "HM", "NNO", "QFM", "COH", "IW"};
    const std::vector<std::string> m_MeltsVersions{/*"xMELTS",*/"MELTS_v1.0.x","pMELTS_v5.6.1","MELTS_v1.1.0", "MELTS_v1.2.0"};
    const std::vector<std::string> m_CalculationModes{"Isothermal/Isobaric", "Isenthalpic", "Isentropic", "Isochoric"};
    std::map<int, std::string> m_Phases;
    std::vector<std::string> m_PhasesVec;
    const std::vector<std::string> m_OxideNames{"SiO2", "TiO2", "Al2O3", "Fe2O3", "Cr2O3", "FeO", "MnO", "MgO", "NiO", "CoO", "CaO", "Na2O", "K2O", "P2O5", "H2O", "CO2", "SO3", "Cl2O-1", "F2O-1"};

    std::map<int, std::string> m_SuppressedPhases;
};

#endif /* MELTS_INTERFACE_HPP */

/*

 * temperature of mixed fluids
 *
 t = (m1 c1 t1 + m2 c2 t2 + ... + mn cn tn) / (m1 c1 + m2 c2 + ... + mn cn)

where

t = final temperature (oC, oF)

c1..n = specific heat of substances (kJ/kgoC, Btu/lboF)

t1..n = temperatures of substances (oC, oF)
 */
