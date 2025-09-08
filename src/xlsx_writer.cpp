/*
 easyMelts (c) 2020-2024 Einari Suikkanen
 easyMelts (c) 2025 Paula Antoshechkina
*/

#include "xlsx_writer.hpp"
extern "C" {
#include "xlsxwriter.h"
}

#include <filesystem>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

const int INDEX = 0;
const int MODE = 1;
const int TEMPERATURE = 2;
const int PRESSURE = 3;
const int OX_FUGACITY = 4;
const int GIBBS = 5;
const int ENTHALPY = 6;
const int ENTROPY = 7;
const int HEAT_CAPACITY = 8;
const int VOLUME = 9;
const int DENSITY = 10;
const int VISCOSITY = 11;
const int MASS = 12;
const int MASS_MELT = 13;
const int MASS_SOLID = 14;
const int MASS_FRAC = 15;
const int MASS_ASSIM = 16;
const int START = 17;


XLSXWriter::XLSXWriter(const std::vector<SilminData> &data, std::string filename) {
    WriteToFile(data, filename);
}

bool XLSXWriter::WriteToFile(const std::vector<SilminData> &data, std::string filename) {
    std::string fn;
    std::string orig_fn;

    fn = filename;
    orig_fn = filename;

    std::filesystem::path p(fn + std::string(".XLSX"));
    int fileadd = 1;
    while (std::filesystem::exists(p)) {
        fn = orig_fn + " (" + std::to_string(fileadd++) + ")";
        p = std::filesystem::path(fn + std::string(".XLSX"));
    }
    fn = orig_fn + ((fileadd - 1) ? " (" + std::to_string(fileadd - 1) + ")" : "") + std::string(".XLSX");

    lxw_workbook *doc = workbook_new(&fn[0]);

    //doc.SetProperty(XLProperty::Creator, "easyMelts");

    lxw_worksheet *wks = workbook_add_worksheet(doc, "Data");

    int rows = data.size();

    std::vector<int> mpi;
    int indexx = 0;
    std::unordered_map<int, int> phase_indices; //first melts, second index in plot data
    for (int i = 0; i < npc; ++i)
        if (solids[i].type == PHASE) {
            phase_indices.emplace(i, indexx++);
            mpi.push_back(i);
        }

    std::vector<std::vector<double>> phase_masses(mpi.size(), std::vector(rows, 0.0));
    std::vector<std::vector<double>> frac_phase_masses(mpi.size(), std::vector(rows, 0.0));
    std::vector<std::vector<double>> assim_phase_masses(mpi.size(), std::vector(rows, 0.0));
    std::vector<int> n_phases_exist(mpi.size(), 0);
    std::vector<bool> frac_phase_exists(mpi.size(), false);
    std::vector<bool> assim_phase_exists(mpi.size(), false);

    bool liq_assimilated = false;

    int step = 0;
    for (const auto &s : data) {

        for (const auto &a : s.sol_properties) {
            phase_masses.at(phase_indices.at(a.melts_phase_index))[step] += (float)a.mass;
            n_phases_exist[phase_indices.at(a.melts_phase_index)]++;
        }
        for (const auto &f : s.frac_properties) {
            frac_phase_masses.at(phase_indices.at(f.melts_phase_index))[step] += (float)f.mass;
            frac_phase_exists.at(phase_indices.at(f.melts_phase_index)) = true;
        }
        for (const auto &as : s.assim_properties) {
            assim_phase_masses.at(phase_indices.at(as.melts_phase_index))[step] += (float)as.mass;
            assim_phase_exists.at(phase_indices.at(as.melts_phase_index)) = true;
        }
        if (!std::isnan(s.assim_liq_mass) && s.assim_liq_mass > 0.0) liq_assimilated = true;

        step++;
    }

    int n_phe = 0;
    int n_phe_f = 0;
    int n_phe_a = 0;

    for (size_t i = 0; i < n_phases_exist.size(); ++i) {
        if (n_phases_exist[i]) n_phe++;
        if (frac_phase_exists[i]) n_phe_f++;
        if (assim_phase_exists[i]) n_phe_a++;
    }

    long row = 1;

    worksheet_write_string(wks, row, INDEX, "Index", NULL);
    worksheet_write_string(wks, row, MODE, "Mode", NULL);
    worksheet_write_string(wks, row, TEMPERATURE, "T (C)", NULL);
    worksheet_write_string(wks, row, PRESSURE, "P (bar)", NULL);
    worksheet_write_string(wks, row, OX_FUGACITY, "log fO2", NULL);
    worksheet_write_string(wks, row, GIBBS, "G (J)", NULL);
    worksheet_write_string(wks, row, ENTHALPY, "H (J)", NULL);
    worksheet_write_string(wks, row, ENTROPY, "S (J/K)", NULL);
    worksheet_write_string(wks, row, HEAT_CAPACITY, "Cp (J)", NULL);
    worksheet_write_string(wks, row, VOLUME, "V (cm3)", NULL);
    worksheet_write_string(wks, row, DENSITY, "density (g/cm3)", NULL);
    worksheet_write_string(wks, row, VISCOSITY, "viscosity (log poise)", NULL);
    worksheet_write_string(wks, row, MASS, "m (total)", NULL);
    worksheet_write_string(wks, row, MASS_MELT, "m (melt)", NULL);
    worksheet_write_string(wks, row, MASS_SOLID, "m (solid)", NULL);
    worksheet_write_string(wks, row, MASS_FRAC, "m (frac)", NULL);
    worksheet_write_string(wks, row, MASS_ASSIM, "m (assim)", NULL);

    worksheet_write_string(wks, 0, 1, "System properties (no fractionated)", NULL);
    worksheet_write_string(wks, 0, MASS, "Masses", NULL);
    worksheet_write_string(wks, 0, START, "Liquid composition wt%", NULL);
    if (n_phe > 0)
        worksheet_write_string(wks, 0, START + nc, "Solids in eq with liquid", NULL);
    if (n_phe_f > 0)
        worksheet_write_string(wks, 0, START + nc + n_phe, "Fractionated solids", NULL);
    if (n_phe_a > 0 || liq_assimilated) worksheet_write_string(wks, 0, START + nc + n_phe + n_phe_f, "Assim T", NULL);
    if (n_phe_a > 0)
        worksheet_write_string(wks, 0, START + nc + n_phe + n_phe_f + 1, "Mass assim solids at step", NULL);
    if (liq_assimilated)
        worksheet_write_string(wks, 0, START + nc + n_phe + n_phe_f + n_phe_a + 1, "Assim liquid at step", NULL);

    for (int i = 0; i < nc; ++i) {
        worksheet_write_string(wks, row, i + START, bulkSystem[i].label, NULL);
    }

    int liq_phases = 0;
    for (size_t i = 0; i < mpi.size(); ++i) {
        if (n_phases_exist[i] > 0)
            worksheet_write_string(wks, row, nc + START + liq_phases++, solids[mpi[i]].label, NULL);
    }
    if (n_phe_f > 0) {
        for (size_t i = 0; i < mpi.size(); ++i) {
            if (frac_phase_exists.at(i))
                worksheet_write_string(wks, row, nc + START + liq_phases++, solids[mpi[i]].label, NULL);
        }
    }
    if (n_phe_a > 0 || liq_assimilated) {
        worksheet_write_string(wks, row, nc + START + liq_phases++, "assim T", NULL);
    }
    if (n_phe_a > 0) {
        for (size_t i = 0; i < mpi.size(); ++i) {
            if (assim_phase_exists[i])
                worksheet_write_string(wks, row, nc + START + liq_phases++, solids[mpi[i]].label, NULL);
        }
    }
    if (liq_assimilated) {
        for (int i = 0; i < nc; ++i) {
            if (i == 0) worksheet_write_string(wks, row, nc + START + liq_phases + i, "m liq ass", NULL);
            worksheet_write_string(wks, row, nc + START + liq_phases + i, bulkSystem[i].label, NULL);
        }
    }

    step = 0;
    row = 2;
    for (const auto &a : data) {

        double value;
        worksheet_write_number(wks, row, INDEX, step, NULL);
        const char *mode = "";
        if (a.isenthalpic)
            mode = "Isenthalpic";
        else if (a.isentropic)
            mode = "Isentropic";
        else if (a.isochoric)
            mode = "Isochoric";
        else
            mode = "Isothermal/Isobaric";
        worksheet_write_string(wks, row, MODE, mode, NULL);
        worksheet_write_number(wks, row, TEMPERATURE, a.T, NULL);
        worksheet_write_number(wks, row, PRESSURE, a.P, NULL);
        worksheet_write_number(wks, row, OX_FUGACITY, a.fO2, NULL);
        worksheet_write_number(wks, row, GIBBS, a.sys_prop_nofrac.gibbs_energy, NULL);
        worksheet_write_number(wks, row, ENTHALPY, a.sys_prop_nofrac.enthalpy, NULL);
        worksheet_write_number(wks, row, ENTROPY, a.sys_prop_nofrac.entropy, NULL);
        worksheet_write_number(wks, row, HEAT_CAPACITY, a.sys_prop_nofrac.spec_heat_cap, NULL);
        worksheet_write_number(wks, row, VOLUME, a.sys_prop_nofrac.volume, NULL);
        worksheet_write_number(wks, row, DENSITY, a.sys_prop_nofrac.density, NULL);
        if (std::isnan(a.sys_prop_nofrac.viscosity))
            worksheet_write_string(wks, row, VISCOSITY, "Vsol>Vliq", NULL);
        else
            worksheet_write_number(wks, row, VISCOSITY, a.sys_prop_nofrac.viscosity, NULL);
        worksheet_write_number(wks, row, MASS, a.sys_properties.mass, NULL);
        if (a.liq_properties.find(0) == a.liq_properties.end())
            worksheet_write_number(wks, row, MASS_MELT, 0.0, NULL);
        else
            worksheet_write_number(wks, row, MASS_MELT, a.liq_properties.at(0).mass, NULL);
        value = std::isnan(a.sol_tot_properties.mass) ? 0.0 : a.sol_tot_properties.mass;
        worksheet_write_number(wks, row, MASS_SOLID, value, NULL);
        value = (std::isnan(a.frac_mass) || a.frac_mass == 0.0) ? 0.0 : a.frac_mass;
        worksheet_write_number(wks, row, MASS_FRAC, value, NULL);
        value = (std::isnan(a.assim_mass)) ? 0.0 : a.assim_mass;
        worksheet_write_number(wks, row, MASS_ASSIM, value, NULL);

        if (a.liq_properties.find(0) != a.liq_properties.end()) {
            for (int i = 0; i < nc; ++i) {
                worksheet_write_number(wks, row, i + START, a.liquid_composition.at(0).at(i), NULL);
            }
        }
        int np = 0;
        for (size_t i = 0; i < mpi.size(); ++i) {
            if (n_phases_exist[i]) {
                worksheet_write_number(wks, row, nc + START + np++, phase_masses.at(i)[step], NULL);
            }
        }
        if (n_phe_f > 0) {
            np = 0;
            for (size_t i = 0; i < mpi.size(); ++i) {
                if (frac_phase_exists[i]) {
                    worksheet_write_number(wks, row, nc + START + np++ + n_phe, frac_phase_masses.at(i)[step], NULL);
                }
            }
        }
        if (!std::isnan(a.assim_t)) {
            worksheet_write_number(wks, row, nc + START + n_phe + n_phe_f, a.assim_t, NULL);
        }
        if (n_phe_a > 0) {
            np = 0;
            for (size_t i = 0; i < mpi.size(); ++i) {
                if (assim_phase_exists[i]) {
                    worksheet_write_number(wks, row, nc + START + np++ + n_phe + n_phe_f, assim_phase_masses.at(i)[step], NULL);
                }
            }
        }
        if (!std::isnan(a.assim_liq_mass)) {
            for (int i = 0; i < nc; ++i) {
                if (i == 0) worksheet_write_number(wks, row, START + nc + n_phe + n_phe_f + n_phe_a, a.assim_liq_mass, NULL);
                worksheet_write_number(wks, row, START + nc + n_phe + n_phe_f + n_phe_a + i + 1, a.assim_liq_comp.at(i), NULL);
            }
        }
        row++;
        step++;
    }

    lxw_worksheet *wks2 = workbook_add_worksheet(doc, "Phases");

    row = 2;
    step = 0;
    worksheet_write_string(wks2, 0, 0, "Solid and fluid phases in equilibrium with the melt (and to be fractionated before next equilibration step if fractionation is active)", NULL);
    worksheet_write_string(wks2, 1, 0, "Step", NULL);
    worksheet_write_string(wks2, 1, 1, "Label", NULL);
    worksheet_write_string(wks2, 1, 2, "Formula", NULL);
    worksheet_write_string(wks2, 1, 3, "Mass", NULL);
    for (const auto &a : data) {
        worksheet_write_number(wks2, row, 0, step++, NULL);
        int column = 1;
        for (const auto &s : a.sol_properties) {
            worksheet_write_string(wks2, row, column++, &(s.label)[0], NULL);
            worksheet_write_string(wks2, row, column++, &(s.formula)[0], NULL);
            worksheet_write_number(wks2, row, column++, s.mass, NULL);
        }
        row++;
    }

    return workbook_close(doc);
}
