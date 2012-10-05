#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#undef USE_ORIGINAL_DATASET

int main (int argc, char *argv[]) {

#ifdef USE_ORIGINAL_DATASET

  /* these are the EMP data: Label1, SiO2, Al2O3, FeO, MgO, CaO, Na2O, K2O */
  char *data_emp[115][8] = {
    { "5B-B1-1", "78.72", "12.08", "0.67", "0.02", "0.42", "3.16", "4.93" },
    { "5B-B1-3", "76.84", "13.02", "0.64", "0.03", "0.42", "4.45", "4.6" },
    { "5C-Q1", "77.56", "12.32", "0.02", "0.44", "0.59", "3.47", "4.5" },
    { "5C-Q2", "77.67", "12.39", "0.02", "0.42", "0.67", "3.95", "4.86" },
    { "5D-Lu1-1", "77.575", "12.305", "0.65", "0.02", "0.405", "4.485", "4.695" },
    { "5D-Lu1-2", "77.44", "12.76", "0.71", "0.02", "0.42", "3.82", "4.89" },
    { "5D-Lu2-1", "77.05", "12.57", "0.62", "0.04", "0.4", "4.38", "5.06" },
    { "5D-Lu2-2", "77.735", "12.475", "0.61", "0.02", "0.43", "4.035", "4.79" },
    { "6A-B7-1", "77.57", "12.63", "0.67", "0.02", "0.44", "4.15", "4.67" },
    { "6A-B7-2", "78.14", "12.39", "0.66", "0.02", "0.42", "3.6", "4.87" },
    { "6A-F2-1", "77.89", "12.35", "0.65", "0.02", "0.46", "3.77", "4.87" },
    { "6A-F2-2", "77.89", "12.23", "0.65", "0.02", "0.43", "3.29", "4.81" },
    { "6A-Q1", "77.96", "12.86", "0.02", "0.42", "0.62", "3.31", "4.81" },
    { "6A-Q2", "77.86", "12.94", "0.02", "0.48", "0.67", "3.22", "4.8" },
    { "6B-1", "77.95", "12.32", "0.63", "0.03", "0.44", "4.26", "4.37" },
    { "6B-2-1", "78.02", "12.66", "0.65", "0.03", "0.45", "3.64", "4.56" },
    { "6B-2-2", "77.75", "12.64", "0.89", "0.04", "0.48", "3.57", "5.14" },
    { "6B-4", "76.66", "12.58", "0.61", "0.02", "0.44", "4.76", "4.92" },
    { "6B-D2-1", "76.965", "12.475", "0.655", "0.025", "0.385", "4.44", "4.565" },
    { "6B-D2-2", "77.969", "12.359", "0.62", "0.025", "1.027", "4.011", "4.843" },
    { "6B-D2-3", "77.36", "12.67", "0.69", "0.03", "0.39", "4.45", "4.55" },
    { "6B-D3-1", "77.23", "12.16", "0.625", "0.02", "0.39", "4.335", "4.555" },
    { "6B-D3-2", "77.43", "12.54", "0.68", "0.02", "0.62", "3.94", "4.76" },
    { "6B-D3-3", "76.93", "12.86", "0.62", "0.02", "0.93", "3.73", "4.9" },
    { "6B-G5", "78.39", "12.37", "0.56", "0.02", "0.39", "4.07", "4.21" },
    { "6B2-2", "77.75", "12.64", "0.89", "0.04", "0.48", "3.57", "5.14" },
    { "7B-F2-1", "77.31", "12.29", "0.64", "0.02", "0.46", "4.42", "4.86" },
    { "7B-F2-2", "77.61", "12.47", "0.65", "0.02", "0.4", "3.86", "4.75" },
    { "7B-F3", "77.45", "12.25", "0.67", "0.04", "0.45", "3.48", "4.93" },
    { "7B-Lu1-1", "77.19", "12.69", "0.69", "0.02", "0.45", "4.42", "4.56" },
    { "7B-Q1", "77.35", "12.33", "0.03", "0.44", "0.65", "4.19", "4.86" },
    { "7B-Q2", "77.75", "12.14", "0.03", "0.43", "0.67", "3.7", "4.56" },
    { "8A-L1-2", "77.71", "12.26", "0.66", "0.03", "0.43", "4.48", "4.43" },
    { "8A-Q1", "78.67", "12.07", "0.03", "0.44", "0.67", "3.31", "4.81" },
    { "8B-F1-1", "77.54", "12.44", "0.64", "0.02", "0.45", "4.2", "4.7" },
    { "8B-F1-2", "77.65", "12.33", "0.63", "0.03", "0.41", "3.86", "4.63" },
    { "8B-G11-1", "78.6", "12.29", "0.65", "0.03", "0.43", "3.36", "4.74" },
    { "8B-G11-2", "77.16", "12.44", "0.61", "0.03", "0.44", "3.96", "4.65" },
    { "8B-G12-1", "77.47", "12.42", "0.64", "0.01", "0.44", "4.19", "4.94" },
    { "8B-G12-2", "77.79", "12.395", "0.655", "0.02", "0.425", "3.985", "4.865" },
    { "8B-H4", "77.42", "12.72", "0.66", "0.03", "0.43", "4.17", "4.8" },
    { "9-Lu", "77.19", "12.76", "0.69", "0.03", "0.45", "4.26", "4.6" },
    { "10–1", "78.06", "11.86", "0.65", "0.03", "0.43", "4.67", "4.29" },
    { "10–2", "78.35", "12.47", "0.61", "0.04", "0.4", "3.56", "4.57" },
    { "10-B1", "77.31", "12.38", "0.64", "0.03", "0.42", "4.51", "4.74" },
    { "10-Lu-1", "77.7", "12.34", "0.7", "0.07", "0.44", "3.96", "4.79" },
    { "10-Lu-2", "78.12", "12.34", "0.7", "0.03", "0.47", "3.69", "4.65" },
    { "10LuB", "77.7", "12.525", "0.65", "0.02", "0.425", "3.9", "4.895" },
    { "11A-B1-1", "76.49", "13.33", "0.64", "0.03", "0.43", "4.01", "5.07" },
    { "11A-B1-2", "77.08", "12.89", "0.65", "0.03", "0.43", "4", "4.92" },
    { "11A-F1", "78.72", "12.28", "0.65", "0.03", "0.42", "3.25", "4.65" },
    { "11A-Lu-1", "77.46", "12.42", "0.63", "0.02", "0.42", "4.21", "4.94" },
    { "11A-Lu-2", "77.83", "12.61", "0.67", "0.01", "0.43", "3.83", "4.77" },
    { "11A-Q1", "77.19", "12.19", "0.01", "0.42", "0.68", "4.38", "4.81" },
    { "11A-Q2", "77.91", "11.99", "0.02", "0.47", "0.68", "3.96", "4.98" },
    { "11B-B1", "77.721", "12.43", "0.65", "0.02", "0.43", "3.49", "4.93" },
    { "11B-F1", "77.72", "12.55", "0.6", "0.03", "0.43", "3.61", "4.77" },
    { "11B-Q1", "77.33", "12.4", "0.61", "0.02", "0.42", "3.6", "4.77" },
    { "11B-Lu-1", "77.59", "12.59", "0.655", "0.025", "0.2475", "3.78", "5.235" },
    { "11B-Lu-2", "77.83", "12.61", "0.67", "0.01", "0.43", "3.83", "4.77" },
    { "12-Q1", "77.78", "12.41", "0.02", "0.43", "0.65", "3.98", "4.73" },
    { "12-Q2", "77.39", "12.6", "0.02", "0.41", "0.64", "4.1", "4.84" },
    { "13-1", "78.1", "12.32", "0.6", "0.02", "0.43", "3.71", "4.81" },
    { "13-B1", "76.86", "12.49", "0.57", "0.03", "0.43", "4.63", "4.99" },
    { "13-LU-1", "77.02", "12.86", "0.71", "0.03", "0.44", "3.85", "5.09" },
    { "13-LU-2", "77.62", "12.9", "0.64", "0.02", "0.4", "4.06", "4.45" },
    { "13-LU-3", "77.12", "12.53", "0.62", "0.03", "0.41", "4.62", "4.36" },
    { "14-B1-1", "77.22", "12.6", "0.59", "0.04", "0.42", "4.76", "4.37" },
    { "14-B1-2", "78.22", "11.975", "0.645", "0.03", "0.4", "4.175", "4.56" },
    { "14-B2", "77.56", "12.52", "0.64", "0.03", "0.38", "4.05", "4.83" },
    { "15-F1-1", "77.35", "12.66", "0.63", "0.02", "0.44", "3.74", "4.65" },
    { "15-F1-2", "77.45", "12.52", "0.56", "0.02", "0.49", "3.58", "4.8" },
    { "15-Q1-1", "77.61", "12.98", "0.02", "0.45", "0.72", "3.27", "4.95" },
    { "15-Q1-2", "77.39", "12.62", "0.01", "0.45", "0.66", "3.72", "4.62" },
    { "16-H6-1", "77.64", "12.05", "0.61", "0.02", "0.47", "4.2", "5" },
    { "16-H6-2", "78.06", "11.68", "0.66", "0.02", "0.39", "4.18", "4.67" },
    { "16-Lu-1", "77.04", "12.98", "0.64", "0.03", "0.42", "4.19", "4.69" },
    { "16-Lu-2", "77.28", "12.68", "0.7", "0.02", "0.45", "3.87", "4.99" },
    { "21A-3-1", "77.89", "11.71", "0.65", "0.02", "0.45", "4.62", "4.65" },
    { "21A-3-2", "78.19", "12.16", "0.58", "0.02", "0.41", "4.09", "4.55" },
    { "21A-B1", "77.67", "12.71", "0.42", "0.02", "0.57", "3.94", "4.67" },
    { "21A-C8-1", "77.77", "12.45", "0.65", "0.03", "0.44", "3.96", "4.79" },
    { "21A-C11", "77.53", "12.44", "0.66", "0.01", "0.43", "4.24", "4.83" },
    { "21A-Lu2", "76.97", "12.75", "0.63", "0.02", "0.43", "4.37", "4.84" },
    { "24B-B1", "77.64", "12.11", "0.71", "0.02", "0.43", "3.98", "4.89" },
    { "24C-3-1", "76.64", "13.39", "0.63", "0.03", "0.5", "4.16", "4.565" },
    { "24C-B1", "77.27", "12.78", "0.61", "0.01", "0.39", "3.58", "5.4" },
    { "133A-1", "78.52", "12.69", "0.64", "0.02", "0.47", "3.15", "4.51" },
    { "133A-7-1", "77.55", "12.66", "0.65", "0.02", "0.48", "4.08", "4.61" },
    { "133A-B1", "76.94", "12.51", "0.66", "0.02", "0.4", "4.9", "4.56" },
    { "17A-2-1", "77.69", "12.69", "0.73", "0.04", "0.47", "3.48", "4.9" },
    { "17A-3-1", "77.097", "12.394", "0.7125", "0.0565", "0.4665", "4.191", "5.2265" },
    { "17A-3-2", "78.03", "11.6", "0.67", "0.05", "0.46", "4.05", "5.28" },
    { "17A-5-1", "76.67", "12.87", "0.67", "0.03", "0.46", "4.01", "5.29" },
    { "17A-6-1", "77.6", "12.16", "0.69", "0.03", "0.47", "3.54", "5.5" },
    { "17A-6-2", "77.46", "12.41", "0.69", "0.04", "0.44", "3.84", "5.11" },
    { "17A-7-1", "77.08", "11.9", "0.58", "0.03", "0.44", "4.38", "5.59" },
    { "32W-1", "78.32", "11.56", "0.06", "0.03", "0.42", "4.08", "5.15" },
    { "32W-4-1", "78.23", "11.7", "0.53", "0.03", "0.36", "4.19", "5.09" },
    { "32W-4-2", "76.83", "12.29", "0.62", "0.04", "0.42", "4.88", "5.12" },
    { "32W-5", "78.61", "11.33", "0.61", "0.03", "0.4", "4.32", "4.86" },
    { "41-2", "78.34", "11.6", "0.59", "0.03", "0.39", "3.94", "5.2" },
    { "41-3", "78.35", "11.53", "0.65", "0.03", "0.39", "4", "5.2" },
    { "42-3", "78.43", "11.39", "0.64", "0.04", "0.44", "4.34", "4.88" },
    { "42-5", "78.91", "11.23", "0.68", "0.04", "0.42", "3.91", "4.93" },
    { "42-6", "77.51", "11.95", "0.73", "0.05", "0.44", "4.51", "4.81" },
    { "45-3", "77.53", "11.81", "0.69", "0.04", "0.44", "4.49", "5.01" },
    { "45-4", "77.86", "11.86", "0.58", "0.03", "0.44", "4.09", "4.32" },
    { "3-1-2-2", "77.74", "12.09", "0.712000826", "0.051594263", "0.495304922", "3.363945929", "5.45" },
    { "3-1-2-3", "78.64", "11.8", "0.625978091", "0.041731873", "0.427751695", "3.015127804", "5.33" },
    { "3-1-8-1", "77.76", "11.83", "0.734137389", "0.062926062", "0.492920818", "3.61", "5.411641321" },
    { "3-3-10-1", "77.57", "12.13", "0.66003143", "0.031430068", "0.429544264", "3.740178104", "5.364064955" },
    { "3-3-14-2", "77.91", "12.17", "0.625065111", "0.031253256", "0.427127826", "3.333680592", "5.41" },
    { "3-5-17-1", "78.04", "12.06", "0.6775774", "0.020848535", "0.437819243", "3.85", "4.81" },
    { "3-5-19-1", "77.97", "11.78", "0.689371334", "0.041156498", "0.463010598", "3.78", "5.17" }
  };
  char *data_imp[99][9] = { 
    /* these are the IMP data: Label1, SiO2, TiO2, Al2O3, FeO, MgO, CaO, Na2O, K2O */
    { "3A-5-1", "77.0", "0.080155091", "12.7", "0.517", "0.028964073", "0.438", "4.00", "4.98" },
    { "3A-5-2", "77.0", "0.077677506", "12.9", "0.529", "0.027695467", "0.414", "3.90", "4.98" },
    { "3A-5-3", "77.0", "0.082575452", "13.0", "0.477", "0.026776653", "0.399", "3.85", "4.99" },
    { "3A-5-4", "77.0", "0.078750226", "13.0", "0.548", "0.027432076", "0.408", "3.92", "4.77" },
    { "5B-L1-1", "77.0", "0.075728354", "13.3", "0.480", "0.026394189", "0.388", "3.69", "4.81" },
    { "5B-L1-2", "77.0", "0.081813102", "13.1", "0.483", "0.027032544", "0.395", "3.86", "4.84" },
    { "5B-L1-3", "77.0", "0.077795437", "13.0", "0.482", "0.026752327", "0.403", "3.86", "4.93" },
    { "5B-L1-4", "77.0", "0.074592506", "12.8", "0.467", "0.026987754", "0.400", "4.01", "4.96" },
    { "5B-L2-1", "77.0", "0.087419855", "12.7", "0.558", "0.032305333", "0.439", "4.07", "4.95" },
    { "5B-L3-1", "77.0", "0.076371804", "12.9", "0.483", "0.028145713", "0.421", "4.06", "4.83" },
    { "5B-L3-2", "77.0", "0.078900126", "12.8", "0.535", "0.028272701", "0.422", "4.11", "4.85" },
    { "5B-L3-3", "77.0", "0.085569449", "12.6", "0.522", "0.031399793", "0.424", "4.10", "4.98" },
    { "5B-L4-1", "77.0", "0.085065136", "12.7", "0.549", "0.031658844", "0.452", "4.16", "4.78" },
    { "5B-L4-2", "77.0", "0.08409005", "12.6", "0.524", "0.033574478", "0.452", "4.10", "5.01" },
    { "5C-L1-1", "77.0", "0.10199312", "12.9", "0.549", "0.035411507", "0.463", "3.91", "4.82" },
    { "5C-L1-2", "77.0", "0.07914375", "12.8", "0.479", "0.02801934", "0.437", "3.93", "4.96" },
    { "5D-L1-1", "77.0", "0.075304972", "12.7", "0.569", "0.028612596", "0.435", "4.07", "4.88" },
    { "5D-Lu1-1", "77.6", "0.074975637", "12.4", "0.521", "0.026903979", "0.426", "3.89", "4.94" },
    { "5D-Lu1-2", "77.5", "0.074235601", "12.1", "0.515", "0.02883943", "0.448", "4.04", "5.11" },
    { "5D-Lu2-1", "77.1", "0.074861298", "12.6", "0.478", "0.029315469", "0.436", "4.10", "5.02" },
    { "5D-Lu2-2", "77.8", "0.07504531", "12.3", "0.429", "0.028140978", "0.413", "3.97", "4.82" },
    { "6A-B7-1", "77.6", "0.078485769", "12.2", "0.448", "0.030258093", "0.458", "3.98", "5.06" },
    { "6A-B7-2", "78.1", "0.081455033", "11.8", "0.472", "0.030015798", "0.444", "3.90", "4.92" },
    { "6B-D2-1", "77.0", "0.079744382", "12.5", "0.502", "0.031806037", "0.414", "4.06", "5.23" },
    { "6B-D2-3", "77.4", "0.075439774", "12.3", "0.495", "0.031918682", "0.391", "4.04", "5.10" },
    { "6B-G8-1", "77.0", "0.077111749", "13.1", "0.502", "0.027298509", "0.430", "3.87", "4.79" },
    { "6B-G8-2", "77.0", "0.083824172", "13.0", "0.468", "0.026415058", "0.418", "3.95", "4.86" },
    { "6B-G8-3", "77.0", "0.08312654", "13.1", "0.485", "0.026875774", "0.425", "3.90", "4.77" },
    { "7A-L1-1", "77.0", "0.08733316", "12.8", "0.531", "0.030818633", "0.466", "3.94", "4.90" },
    { "7A-L1-2", "77.0", "0.076164463", "12.7", "0.540", "0.028577484", "0.454", "3.98", "5.00" },
    { "7B-F1-1", "77.1", "0.073389718", "12.8", "0.562", "0.028635701", "0.432", "4.07", "4.84" },
    { "7B-F2-1", "77.8", "0.07525631", "12.4", "0.475", "0.030609719", "0.433", "3.85", "4.78" },
    { "7B-L1-1", "77.0", "0.09045621", "12.7", "0.561", "0.033051971", "0.465", "3.92", "5.03" },
    { "7B-Lu1-1", "77.0", "0.08708228", "12.9", "0.545", "0.03172457", "0.440", "3.92", "4.91" },
    { "7B-Lu1-2", "77.0", "0.091038529", "12.7", "0.566", "0.032022659", "0.450", "3.96", "4.97" },
    { "7B-Lu1-3", "77.0", "0.090849551", "12.9", "0.525", "0.029750144", "0.433", "3.90", "4.94" },
    { "7B-Lu2-1", "77.0", "0.066746461", "13.7", "0.511", "0.028032364", "0.380", "3.63", "4.47" },
    { "7B-Lu2-2", "77.0", "0.075291401", "13.6", "0.477", "0.029152422", "0.401", "3.52", "4.63" },
    { "8A-I2", "77.0", "0.075515886", "12.8", "0.486", "0.026917953", "0.426", "3.94", "4.98" },
    { "8A-L1-1", "77.0", "0.097122833", "12.8", "0.547", "0.03361242", "0.462", "3.75", "5.15" },
    { "8A-L1-2", "77.0", "0.077506974", "12.8", "0.514", "0.027936839", "0.431", "3.96", "4.99" },
    { "8B-F1-1", "77.4", "0.079279714", "12.4", "0.451", "0.030537247", "0.436", "4.14", "4.85" },
    { "8B-G12-1", "77.5", "0.076578042", "12.3", "0.431", "0.028398206", "0.441", "4.06", "5.00" },
    { "8B-G12-2", "77.9", "0.069078784", "12.0", "0.462", "0.026819321", "0.396", "4.02", "4.86" },
    { "8B-H4", "77.4", "0.070494292", "12.9", "0.452", "0.024902823", "0.380", "3.64", "4.90" },
    { "8B-L1-1", "77.0", "0.076675786", "12.9", "0.477", "0.026571825", "0.406", "3.96", "4.95" },
    { "8B-L2-1", "77.0", "0.078747116", "12.7", "0.553", "0.028313389", "0.431", "4.09", "4.94" },
    { "8B-L4-1", "77.0", "0.068885172", "12.8", "0.533", "0.026871687", "0.394", "4.06", "4.86" },
    { "8B-L4-2", "77.0", "0.081875935", "12.7", "0.522", "0.029477303", "0.442", "4.06", "4.99" },
    { "8B-L5-1", "77.0", "0.077328504", "12.7", "0.543", "0.02789564", "0.442", "3.97", "5.04" },
    { "10LuB", "77.7", "0.070798254", "12.2", "0.444", "0.027502064", "0.411", "4.08", "4.86" },
    { "11A-F1", "77.2", "0.074174958", "13.2", "0.446", "0.02675723", "0.375", "3.70", "4.74" },
    { "11A-L1-1", "77.0", "0.084007638", "12.8", "0.519", "0.031020651", "0.455", "3.94", "4.99" },
    { "11A-Lu-1", "77.4", "0.07813169", "12.7", "0.410", "0.024880903", "0.376", "3.85", "4.97" },
    { "11A-Lu-2", "77.8", "0.06570748", "12.7", "0.378", "0.024617808", "0.345", "3.77", "4.74" },
    { "11B-F1", "76.9", "0.072713564", "13.4", "0.465", "0.026452717", "0.381", "3.69", "4.91" },
    { "11B-L1-1", "77.0", "0.083343271", "12.9", "0.509", "0.026937331", "0.404", "3.84", "5.00" },
    { "11B-L1-2", "77.0", "0.083934463", "12.5", "0.545", "0.028490205", "0.449", "4.11", "5.06" },
    { "11B-Lu-1", "77.6", "0.08475267", "12.5", "0.446", "0.029030331", "0.439", "3.64", "5.04" },
    { "11B-Lu-2", "77.6", "0.083214849", "12.0", "0.526", "0.030183937", "0.446", "3.76", "5.41" },
    { "12-L1-1", "77.0", "0.081150485", "12.7", "0.510", "0.030923835", "0.452", "4.09", "4.97" },
    { "13-LU-1", "77.0", "0.078632462", "12.6", "0.553", "0.030064721", "0.455", "4.10", "4.99" },
    { "13-LU-2", "77.0", "0.079978678", "12.7", "0.477", "0.030795337", "0.453", "4.04", "4.97" },
    { "14-L1-1", "77.0", "0.087781187", "12.5", "0.611", "0.036130718", "0.499", "3.98", "5.15" },
    { "15-F1-1", "77.5", "0.069864915", "13.2", "0.394", "0.025152861", "0.370", "3.68", "4.59" },
    { "15-F1-2", "77.5", "0.070590212", "13.2", "0.411", "0.026139396", "0.388", "3.69", "4.55" },
    { "16-H5-1", "77.0", "0.085200135", "12.4", "0.525", "0.031825187", "0.460", "3.87", "5.34" },
    { "16-H5-2", "77.0", "0.08470175", "12.8", "0.512", "0.033253205", "0.509", "3.79", "4.99" },
    { "16-L1-1", "77.0", "0.086533276", "12.5", "0.551", "0.034230573", "0.452", "4.09", "5.08" },
    { "21A-2-1?", "77.0", "0.090509637", "12.9", "0.538", "0.032042738", "0.456", "3.92", "4.88" },
    { "21A-C8-1", "77.8", "0.072595766", "12.0", "0.490", "0.028385477", "0.456", "3.91", "5.05" },
    { "21A-C11", "77.5", "0.073590945", "12.4", "0.482", "0.026289342", "0.438", "3.93", "4.93" },
    { "21A-Lu2", "77.0", "0.075014394", "13.2", "0.492", "0.027475182", "0.420", "3.72", "4.83" },
    { "24C-3-1", "77.0", "0.069157302", "13.1", "0.415", "0.029271224", "0.467", "3.90", "4.77" },
    { "133A-7-1", "77.0", "0.082383556", "12.8", "0.454", "0.029443818", "0.468", "4.11", "4.87" },
    { "17A-2-1", "77.0", "0.097846322", "12.7", "0.579", "0.040750984", "0.453", "3.46", "5.55" },
    { "17A-3-2", "78.0", "0.146009841", "11.6", "0.531", "0.051404146", "0.447", "3.77", "5.25" },
    { "17A-5-1", "77.0", "0.086766312", "12.8", "0.486", "0.036227358", "0.413", "3.52", "5.48" },
    { "17A-6-1", "77.0", "0.094205862", "12.3", "0.570", "0.040474703", "0.436", "3.63", "5.77" },
    { "17A-6-2", "77.0", "0.086469065", "12.8", "0.463", "0.038608256", "0.411", "3.52", "5.52" },
    { "17A-7-1", "77.0", "0.089747983", "12.4", "0.503", "0.032832078", "0.407", "3.49", "5.88" },
    { "32W-1", "78.3", "0.084228019", "11.3", "0.449", "0.034605634", "0.421", "3.99", "5.21" },
    { "32W-4-1", "78.2", "0.041693309", "11.7", "0.321", "0.027731443", "0.393", "3.98", "5.15" },
    { "32W-4-2", "76.8", "0.081335652", "12.3", "0.461", "0.043073188", "0.433", "4.30", "5.41" },
    { "32W-5", "78.6", "0.074923187", "11.7", "0.325", "0.031085033", "0.343", "3.81", "4.89" },
    { "41-2", "78.4", "0.07290902", "11.3", "0.391", "0.029239904", "0.403", "4.04", "5.22" },
    { "41-3", "78.4", "0.064861811", "11.1", "0.483", "0.042972337", "0.435", "4.04", "5.27" },
    { "42-3", "78.4", "0.096269445", "11.3", "0.469", "0.040100459", "0.441", "4.03", "5.01" },
    { "42-5", "78.9", "0.085308826", "11.4", "0.395", "0.042047021", "0.382", "3.98", "4.56" },
    { "42-6", "77.5", "0.119742748", "11.5", "0.537", "0.051703863", "0.515", "4.27", "5.27" },
    { "45-3", "77.5", "0.145850249", "12.2", "0.427", "0.042557119", "0.380", "3.99", "5.10" },
    { "45-4", "77.9", "0.078583129", "11.8", "0.396", "0.029374885", "0.442", "3.93", "5.26" },
    { "3-1-2-2", "77.8", "0.092858216", "12.0", "0.638", "0.061116507", "0.484", "3.30", "5.44" },
    { "3-1-2-3", "78.8", "0.085275925", "11.6", "0.543", "0.045155106", "0.420", "3.16", "5.21" },
    { "3-1-8-1", "77.8", "0.12312812", "12.0", "0.676", "0.055959381", "0.459", "3.32", "5.39" },
    { "3-3-10-1", "77.6", "0.081652763", "12.1", "0.543", "0.037084917", "0.425", "3.34", "5.63" },
    { "3-3-14-2", "78.0", "0.083583678", "12.1", "0.536", "0.041540704", "0.434", "3.27", "5.41" },
    { "3-5-17-1", "78.1", "0.0782159", "12.0", "0.486", "0.030776896", "0.435", "3.48", "5.18" },
    { "3-5-19-1", "78.0", "0.106885456", "11.9", "0.622", "0.051977779", "0.462", "3.54", "5.08" }
  };
 
  char *string = (char *) malloc(500*sizeof(char));
  int i;
  
  system("rm -rf EMP-RUNS");
  system("mkdir EMP-RUNS");
  
  for (i=0; i<115; i++) {
  
  strcpy(string, "cd EMP-RUNS; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 300; cd 300; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][1]);  /* SiO2  */
  strcat(string, " 0.0 ");     /* TiO2  */
  strcat(string, data_emp[i][2]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][6]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* K2O   */
  strcat(string, " 3000.0");
  system(string);
  
  strcpy(string, "cd EMP-RUNS; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 275; cd 275; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][1]);  /* SiO2  */
  strcat(string, " 0.0 ");     /* TiO2  */
  strcat(string, data_emp[i][2]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][6]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* K2O   */
  strcat(string, " 2750.0");
  system(string);
  
    strcpy(string, "cd EMP-RUNS; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 250; cd 250; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][1]);  /* SiO2  */
  strcat(string, " 0.0 ");     /* TiO2  */
  strcat(string, data_emp[i][2]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][6]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* K2O   */
  strcat(string, " 2500.0");
  system(string);

  strcpy(string, "cd EMP-RUNS; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 225; cd 225; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][1]);  /* SiO2  */
  strcat(string, " 0.0 ");     /* TiO2  */
  strcat(string, data_emp[i][2]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][6]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* K2O   */
  strcat(string, " 2250.0");
  system(string);

  strcpy(string, "cd EMP-RUNS; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 200; cd 200; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][1]);  /* SiO2  */
  strcat(string, " 0.0 ");     /* TiO2  */
  strcat(string, data_emp[i][2]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][6]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* K2O   */
  strcat(string, " 2000.0");
  system(string);

  strcpy(string, "cd EMP-RUNS; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 175; cd 175; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][1]);  /* SiO2  */
  strcat(string, " 0.0 ");     /* TiO2  */
  strcat(string, data_emp[i][2]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][6]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* K2O   */
  strcat(string, " 1750.0");
  system(string);

  strcpy(string, "cd EMP-RUNS; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 150; cd 150; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][1]);  /* SiO2  */
  strcat(string, " 0.0 ");     /* TiO2  */
  strcat(string, data_emp[i][2]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][6]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* K2O   */
  strcat(string, " 1500.0");
  system(string);

  strcpy(string, "cd EMP-RUNS; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 125; cd 125; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][1]);  /* SiO2  */
  strcat(string, " 0.0 ");     /* TiO2  */
  strcat(string, data_emp[i][2]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][6]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* K2O   */
  strcat(string, " 1250.0");
  system(string);

  strcpy(string, "cd EMP-RUNS; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 100; cd 100; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][1]);  /* SiO2  */
  strcat(string, " 0.0 ");     /* TiO2  */
  strcat(string, data_emp[i][2]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][6]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* K2O   */
  strcat(string, " 1000.0");
  system(string);
  
  }

  system("rm -rf IMP-RUNS");
  system("mkdir IMP-RUNS");
  
  for (i=0; i<99; i++) {
  
  strcpy(string, "cd IMP-RUNS; mkdir ");
  strcat(string, data_imp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_imp[i][0]);
  strcat(string, "; mkdir 300; cd 300; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_imp[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_imp[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_imp[i][5]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_imp[i][6]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_imp[i][7]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_imp[i][8]);  /* K2O   */
  strcat(string, " 3000.0");
  system(string);
  
  strcpy(string, "cd IMP-RUNS; cd ");
  strcat(string, data_imp[i][0]);
  strcat(string, "; mkdir 275; cd 275; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_imp[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_imp[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_imp[i][5]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_imp[i][6]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_imp[i][7]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_imp[i][8]);  /* K2O   */
  strcat(string, " 2750.0");
  system(string);
  
  strcpy(string, "cd IMP-RUNS; cd ");
  strcat(string, data_imp[i][0]);
  strcat(string, "; mkdir 250; cd 250; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_imp[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_imp[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_imp[i][5]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_imp[i][6]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_imp[i][7]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_imp[i][8]);  /* K2O   */
  strcat(string, " 2500.0");
  system(string);

  strcpy(string, "cd IMP-RUNS; cd ");
  strcat(string, data_imp[i][0]);
  strcat(string, "; mkdir 225; cd 225; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_imp[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_imp[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_imp[i][5]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_imp[i][6]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_imp[i][7]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_imp[i][8]);  /* K2O   */
  strcat(string, " 2250.0");
  system(string);

  strcpy(string, "cd IMP-RUNS; cd ");
  strcat(string, data_imp[i][0]);
  strcat(string, "; mkdir 200; cd 200; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_imp[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_imp[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_imp[i][5]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_imp[i][6]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_imp[i][7]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_imp[i][8]);  /* K2O   */
  strcat(string, " 2000.0");
  system(string);

  strcpy(string, "cd IMP-RUNS; cd ");
  strcat(string, data_imp[i][0]);
  strcat(string, "; mkdir 175; cd 175; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_imp[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_imp[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_imp[i][5]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_imp[i][6]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_imp[i][7]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_imp[i][8]);  /* K2O   */
  strcat(string, " 1750.0");
  system(string);

  strcpy(string, "cd IMP-RUNS; cd ");
  strcat(string, data_imp[i][0]);
  strcat(string, "; mkdir 150; cd 150; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_imp[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_imp[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_imp[i][5]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_imp[i][6]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_imp[i][7]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_imp[i][8]);  /* K2O   */
  strcat(string, " 1500.0");
  system(string);

  strcpy(string, "cd IMP-RUNS; cd ");
  strcat(string, data_imp[i][0]);
  strcat(string, "; mkdir 125; cd 125; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_imp[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_imp[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_imp[i][5]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_imp[i][6]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_imp[i][7]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_imp[i][8]);  /* K2O   */
  strcat(string, " 1250.0");
  system(string);

  strcpy(string, "cd IMP-RUNS; cd ");
  strcat(string, data_imp[i][0]);
  strcat(string, "; mkdir 100; cd 100; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_imp[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_imp[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_imp[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_imp[i][5]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_imp[i][6]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_imp[i][7]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_imp[i][8]);  /* K2O   */
  strcat(string, " 1000.0");
  system(string);
  
  }
  
#else 

  char *string = (char *) malloc(500*sizeof(char));
  int i;
  

char *data_one[8][11] = {
// "Sample","P (MPa)","SiO2","TiO2","Al2O3","FeO","MnO","MgO","CaO","Na2O","K2O
// Oruanui Tuff, Glass Inclusions (Liu et al. 2006)
{ "P1573","141.2071429","79.11678906","0.120712202","12.12151695","1.015994367","0","0.130771552","1.015994367","3.339704255","3.138517252" },
{ "P1412","125.8785714","79.05922643","0.080580177","12.03666398","1.087832393","0","0.120870266","1.11804996","3.323932313","3.17284448" },
{ "P1577","128.0666667","78.93518519","0.161030596","12.19806763","1.177536232","0","0.120772947","1.066827697","3.250805153","3.089774557" },
{ "P1408","130.8","78.87492519","0.099740674","12.15838819","1.186914024","0","0.109714742","1.057251147","3.411131059","3.101934969" },
{ "P1508","129.95","78.24733989","0.180686609","12.51756675","1.084119655","0","0.110419594","0.99377635","3.603694037","3.262397109" },
{ "P1537","153.3777778","78.58217186","0.100270731","12.24305625","1.092950968","0","0.100270731","0.982653164","3.669908754","3.228717537" },
{ "P1541","150.0333333","77.81450321","0.110176282","12.97075321","1.181891026","0","0.110176282","1.061698718","3.545673077","3.205128205" },
{ "Avg","137.0447846","78.6609319","0.121863799","12.32114695","1.11827957","0","0.114695341","1.042293907","3.449462366","3.171326165" }
};

  system("rm -rf Oruanui_incl");
  system("mkdir Oruanui_incl");
  
  for (i=0; i<8; i++) { // 50 to 400 MPa in 25 MPa increments
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 400; cd 400; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 4000.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 375; cd 375; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3750.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 350; cd 350; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3500.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 325; cd 325; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3250.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 300; cd 300; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3000.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 275; cd 275; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2750.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 250; cd 250; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2500.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 225; cd 225; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2250.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 200; cd 200; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2000.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 175; cd 175; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1750.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 150; cd 150; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1500.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 125; cd 125; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1250.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 100; cd 100; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1000.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 75; cd 75; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 750.0");
  system(string);
  
  strcpy(string, "cd Oruanui_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 50; cd 50; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 500.0");
  system(string);
  
  }
  
char *data_two[4][11] = {
// "Sample","P (MPa)","SiO2","TiO2","Al2O3","FeO","MnO","MgO","CaO","Na2O","K2O
// Oruanui Tuff, Matrix glass (Allan et al. 2012)
{ "Bt-free","133.0636648","77.95073498","0.118329389","12.60791307","1.223292557","0.1349955","0","1.139962001","3.74320856","3.081563948" },
{ "Bt-bear.","153.9418715","77.70833333","0.108333333","12.59","1.045","0.043333333","0.106666667","0.818333333","3.796666667","3.783333333" }, 
{ "Rubbish","127.240682","77.79388969","0.0700035","12.57562878","0.840042002","0.040002","0.05500275","0.660033002","3.82019101","4.14520726" }, 
{ "Avg","134.212892","77.79318814","0.107099061","12.59056564","1.091696431","0.08210928","0.093711679","0.933189821","3.775598907","3.532841035" }
};

  system("rm -rf Oruanui_tuff");
  system("mkdir Oruanui_tuff");
  
  for (i=0; i<4; i++) { // 50 to 400 MPa in 25 MPa increments
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 400; cd 400; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 4000.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 375; cd 375; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3750.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 350; cd 350; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3500.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 325; cd 325; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3250.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 300; cd 300; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3000.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 275; cd 275; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2750.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 250; cd 250; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2500.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 225; cd 225; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2250.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 200; cd 200; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2000.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 175; cd 175; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1750.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 150; cd 150; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1500.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 125; cd 125; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1250.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 100; cd 100; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1000.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 75; cd 75; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 750.0");
  system(string);
  
  strcpy(string, "cd Oruanui_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 50; cd 50; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 500.0");
  system(string);
  
  }

char *data_three[6][11] = {
// "Sample","P (MPa)","SiO2","TiO2","Al2O3","FeO","MnO","MgO","CaO","Na2O","K2O
// Fish Canyon Tuff, Matrix Glass (Bachmann et al. 2002)
{ "PPD","224","77.61208967","0.150120096","12.75020016","0.550440352","0.060048038","0.060048038","0.720576461","2.702161729","5.394315452" },
{ "FCT (O)","224","77.51272582","0.129753468","12.60604851","0.658748378","0.039924144","0.059886216","0.718634594","2.784709053","5.489569817" },
{ "FCT (I)","224","76.87299679","0.240384615","12.55008013","0.600961538","0.040064103","0.070112179","0.721153846","2.794471154","6.109775641" },
{ "Xtal-rich PPD","224","77.32866433","0.130065033","12.96648324","0.690345173","0.070035018","0.070035018","0.740370185","2.821410705","5.182591296" },
{ "Xtal-rich FCT(I)","224","77.30319096","0.130039012","13.23397019","0.660198059","0.030009003","0.070021006","0.56016805","3.601080324","4.411323397" },
{ "Avg","224","77.32610479","0.156040571","12.82133355","0.632164363","0.048012483","0.066017164","0.692179967","2.940764599","5.317382519" }
};

  system("rm -rf Fish_Canyon_tuff");
  system("mkdir Fish_Canyon_tuff");
  
  for (i=0; i<6; i++) { // 50 to 400 MPa in 25 MPa increments
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 400; cd 400; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 4000.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 375; cd 375; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3750.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 350; cd 350; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3500.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 325; cd 325; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3250.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 300; cd 300; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3000.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 275; cd 275; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2750.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 250; cd 250; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2500.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 225; cd 225; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2250.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 200; cd 200; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2000.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 175; cd 175; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1750.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 150; cd 150; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1500.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 125; cd 125; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1250.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 100; cd 100; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1000.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 75; cd 75; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 750.0");
  system(string);
  
  strcpy(string, "cd Fish_Canyon_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 50; cd 50; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 500.0");
  system(string);
  
  }

char *data_four[7][11] = {
// "Sample","P (MPa)","SiO2","TiO2","Al2O3","FeO","MnO","MgO","CaO","Na2O","K2O
// Bishop Tuff - Early, Glass Inclusions (Anderson et al. 2000)
{ "Lu1-1","170.1","77.47603834","0","12.28035144","0.648961661","0","0.019968051","0.409345048","4.482827476","4.682507987" },
{ "H4","185.9","77.25321888","0","12.67591576","0.658748378","0","0.029943108","0.429184549","4.162092025","4.790897295" },
{ "Lu-1","213.4","77.32164209","0","12.55480271","0.657632523","0","0.029892387","0.448385811","3.766440813","5.221203667" },
{ "Lu-2","195.8","77.57672698","0","12.49625112","0.659802059","0","0.029991003","0.429871039","3.738878336","5.068479456" },
{ "B7-1","156.1","77.48377434","0","12.58112831","0.668996505","0","0.019970045","0.439340989","4.143784324","4.663005492" }, 
{ "B7-2","149.5","78.04536824","0","12.39132607","0.659538323","0","0.01998601","0.419706206","3.597481763","4.866593385" },
{ "Avg","178.4666667","77.52595847","0","12.49667199","0.658945687","0","0.024960064","0.429313099","3.981962194","4.882188498" }
};

  system("rm -rf Bishop_early_incl");
  system("mkdir Bishop_early_incl");
  
  for (i=0; i<7; i++) { // 50 to 400 MPa in 25 MPa increments
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 400; cd 400; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 4000.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 375; cd 375; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3750.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 350; cd 350; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3500.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 325; cd 325; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3250.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 300; cd 300; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3000.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 275; cd 275; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2750.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 250; cd 250; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2500.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 225; cd 225; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2250.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 200; cd 200; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2000.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 175; cd 175; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1750.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 150; cd 150; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1500.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 125; cd 125; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1250.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 100; cd 100; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1000.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 75; cd 75; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 750.0");
  system(string);
  
  strcpy(string, "cd Bishop_early_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 50; cd 50; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 500.0");
  system(string);
  
  }

char *data_five[7][11] = {
// "Sample","P (MPa)","SiO2","TiO2","Al2O3","FeO","MnO","MgO","CaO","Na2O","K2O
// Bishop Tuff - Late, Glass Inclusions (Anderson et al. 2000)
{ "6-1","184.4","77.57672698","0","12.1963411","0.689793062","0","0.029991003","0.469859042","3.538938319","5.498350495" },
{ "6-2","188.2","77.4845031","0","12.3975205","0.689862028","0","0.039992002","0.439912018","3.839232154","5.108978204" },
{ "7-1","124.7","77.08458308","0","11.89762048","0.579884023","0","0.029994001","0.439912018","4.379124175","5.588882224" },
{ "1","-","78.15151213","0","11.5780018","0.608843198","0","0.029943108","0.419203513","4.072262701","5.140233556" },
{ "1-2-2","205.3","77.80114148","0","12.11575048","0.710924201","0","0.050065085","0.500650846","3.364373686","5.457094222" },
{ "1-2-3","150.7","78.71807712","0","11.81772659","0.63094642","0","0.04006009","0.430645969","3.024536805","5.338007011" },
{ "Avg","170.66","77.80259342","0","12.00040001","0.65168839","0","0.036667889","0.450015001","3.703456782","5.355178506" }
};

  system("rm -rf Bishop_late_incl");
  system("mkdir Bishop_late_incl");
  
  for (i=0; i<7; i++) { // 50 to 400 MPa in 25 MPa increments
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 400; cd 400; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 4000.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 375; cd 375; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3750.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 350; cd 350; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3500.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 325; cd 325; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3250.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 300; cd 300; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3000.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 275; cd 275; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2750.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 250; cd 250; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2500.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 225; cd 225; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2250.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 200; cd 200; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2000.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 175; cd 175; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1750.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 150; cd 150; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1500.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 125; cd 125; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1250.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 100; cd 100; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1000.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 75; cd 75; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 750.0");
  system(string);
  
  strcpy(string, "cd Bishop_late_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 50; cd 50; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 500.0");
  system(string);
  
  }

char *data_six[8][11] = {
// "Sample","P (MPa)","SiO2","TiO2","Al2O3","FeO","MnO","MgO","CaO","Na2O","K2O
// Young Toba Tuff, Matrix Glass (Chesner & Luhr 2010)
{ "YTT 5B3 MG","282","77.32546509","0.070014003","12.37247449","0.920184037","0.130026005","0.050010002","0.710142028","3.410682136","5.0110022" },
{ "YTT 55A1 MG","282","77.12313694","0.080024007","12.43373012","0.930279084","0.100030009","0.060018005","0.800240072","3.391017305","5.081524457" },
{ "YTT 23A4 MG","282","77.01","0.09","12.52","0.92","0.12","0.07","0.87","3.17","5.23" },
{ "YTT 12A1 MG","282","76.88768877","0.090009001","12.56125613","0.910091009","0.090009001","0.070007001","0.95009501","3.210321032","5.230523052" },
{ "YTT 21A4 MG","282","76.76767677","0.130013001","12.69126913","1.060106011","0.090009001","0.100010001","1.080108011","3.140314031","4.940494049" },
{ "PYLD TT2 MG","282","77.4154831","0.080016003","12.26245249","0.890178036","0.160032006","0.050010002","0.710142028","3.400680136","5.031006201" },
{ "PYLD TT7 MG","282","76.66533307","0.100020004","12.71254251","1.040208042","0.100020004","0.070014003","0.980196039","3.150630126","5.181036207" },
{ "Avg","282","77.02781866","0.091442941","12.50767978","0.953006901","0.11287488","0.06715341","0.871565532","3.267656346","5.100801555" }
};

  system("rm -rf Young_Toba_tuff");
  system("mkdir Young_Toba_tuff");
  
  for (i=0; i<8; i++) { // 50 to 400 MPa in 25 MPa increments
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 400; cd 400; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 4000.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 375; cd 375; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3750.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 350; cd 350; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3500.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 325; cd 325; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3250.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 300; cd 300; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3000.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 275; cd 275; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2750.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 250; cd 250; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2500.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 225; cd 225; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2250.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 200; cd 200; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2000.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 175; cd 175; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1750.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 150; cd 150; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1500.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 125; cd 125; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1250.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 100; cd 100; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1000.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 75; cd 75; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 750.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 50; cd 50; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 500.0");
  system(string);
  
  }

char *data_seven[8][11] = {
// "Sample","P (MPa)","SiO2","TiO2","Al2O3","FeO","MnO","MgO","CaO","Na2O","K2O
// Young Toba Tuff, Glass Inclusions (Chesner & Luhr 2010)
{ "5B3-3 MI","286","76.37291187","0.070021006","12.77383215","0.970291087","0.100030009","0.070021006","0.78023407","3.651095329","5.211563469" },
{ "55A1-3-MI","286","75.81790895","0.110055028","13.04652326","1.030515258","0.060030015","0.070035018","0.850425213","3.691845923","5.322661331" }, 
{ "23A4-3-MI","286","76.13761376","0.060006001","12.76127613","1.130113011","0.060006001","0.050005001","0.610061006","3.670367037","5.520552055" },
{ "12A1- 3-MI","286","76.58765877","0.070007001","12.38123812","1.01010101","0.080008001","0.060006001","0.730073007","3.770377038","5.310531053" }, 
{ "21A4-3MI","286","76.53295989","0.090027008","12.2336701","0.970291087","0.210063019","0.050015005","0.810243073","4.321296389","4.78143443" },
{ "TT2-3- MI","286","76.98309493","0.090027008","12.32369711","0.970291087","0.070021006","0.060018005","0.730219066","3.78113434","4.991497449" }, 
{ "TT7-3- MI","286","76.33763376","0.060006001","12.55125513","1.02010201","0.060006001","0.080008001","0.890089009","3.700370037","5.300530053" }, 
{ "Avg","286","76.3956961","0.078590515","12.58162697","1.014532101","0.091450781","0.062872412","0.771615964","3.798065244","5.205549919" }
};

  system("rm -rf Young_Toba_incl");
  system("mkdir Young_Toba_incl");
  
  for (i=0; i<8; i++) { // 50 to 400 MPa in 25 MPa increments
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 400; cd 400; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 4000.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 375; cd 375; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3750.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 350; cd 350; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3500.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 325; cd 325; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3250.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 300; cd 300; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3000.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 275; cd 275; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2750.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 250; cd 250; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2500.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 225; cd 225; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2250.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 200; cd 200; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2000.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 175; cd 175; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1750.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 150; cd 150; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1500.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 125; cd 125; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1250.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 100; cd 100; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1000.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 75; cd 75; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 750.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 50; cd 50; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 500.0");
  system(string);
  
  }

char *data_eight[4][11] = {
// "Sample","P (MPa)","SiO2","TiO2","Al2O3","FeO","MnO","MgO","CaO","Na2O","K2O
// Old+Middle Toba Tuffs, Matrix Glass (Chesner 1998)
{ "15A-G","-","76.49970409","0.08007296","13.28210223","0.549383767","0.02001824","0.17015504","1.040948479","3.563246717","4.794368476" },
{ "7-G","300","75.35303179","0.060098125","14.00286301","1.288830481","0.030049062","0.140228957","0.751226556","3.515740284","4.857931732" },
{ "8-G","-","77.04804432","0.100140427","12.64773589","1.081286488","0.050070213","0.180252768","0.821151499","2.984184716","5.087133677" },
{ "Avg","300","76.30036562","0.080105371","13.31084244","0.973073164","0.033377238","0.163548465","0.871145907","3.354412399","4.913129405" }
};

  system("rm -rf Old_Toba_tuff");
  system("mkdir Old_Toba_tuff");
  
  for (i=0; i<4; i++) { // 50 to 400 MPa in 25 MPa increments
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 400; cd 400; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 4000.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 375; cd 375; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3750.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 350; cd 350; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3500.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 325; cd 325; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3250.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 300; cd 300; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3000.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 275; cd 275; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2750.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 250; cd 250; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2500.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 225; cd 225; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2250.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 200; cd 200; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2000.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 175; cd 175; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1750.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 150; cd 150; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1500.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 125; cd 125; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1250.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 100; cd 100; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1000.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 75; cd 75; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 750.0");
  system(string);
  
  strcpy(string, "cd Old_Toba_tuff; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 50; cd 50; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 500.0");
  system(string);
  
  }

char *data_nine[5][11] = {
// "Sample","P (MPa)","SiO2","TiO2","Al2O3","FeO","MnO","MgO","CaO","Na2O","K2O
// Young Toba Tuff, Matrix Glass (Chesner 1998)
{ "94A5-G","260","78.19207447","0.040036904","12.05110825","0.828587582","0.060055357","0.150138392","0.62057202","2.792574088","5.26485294" },
{ "51A5-G","300","78.28783529","0.060067393","11.91336624","0.918835562","0.070078625","0.170190946","0.690775017","2.683010212","5.20584071" },
{ "6A2-G","-","77.67313769","0.0800754","12.7920451","0.756551517","0.06005655","0.200188499","0.800753997","2.60245049","5.034740755" },
{ "63A1-G","290","76.92094467","0.080105123","12.94699056","1.090198974","0.070091983","0.180236527","0.941235199","2.943863282","4.82633368" },
{ "Avg","283.3333333","77.76855533","0.065069912","12.42585046","0.898524364","0.065069912","0.175188224","0.763320119","2.755460495","5.082961185" }
};

  system("rm -rf Young_Toba_glass");
  system("mkdir Young_Toba_glass");
  
  for (i=0; i<5; i++) { // 50 to 400 MPa in 25 MPa increments
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 400; cd 400; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 4000.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 375; cd 375; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3750.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 350; cd 350; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3500.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 325; cd 325; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3250.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 300; cd 300; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3000.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 275; cd 275; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2750.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 250; cd 250; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2500.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 225; cd 225; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2250.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 200; cd 200; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2000.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 175; cd 175; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1750.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 150; cd 150; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1500.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 125; cd 125; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1250.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 100; cd 100; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1000.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 75; cd 75; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 750.0");
  system(string);
  
  strcpy(string, "cd Young_Toba_glass; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 50; cd 50; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 500.0");
  system(string);
  
  }

char *data_ten[5][11] = {
// "Sample","P (MPa)","SiO2","TiO2","Al2O3","FeO","MnO","MgO","CaO","Na2O","K2O
// Toba Tuffs Glass Inclusions (Beddoe-Stephens et al. 1983)
{ "Q","287.5","76.8794028","0.052570708","13.05856377","0.883187888","0.073598991","0.042056566","0.725475765","3.290926296","4.994217222" },
{ "P","287.5","77.2911261","0.083030618","12.85936689","0.975609756","0.051894136","0.041515309","0.788790867","2.999481059","4.909185262" },
{ "K","287.5","77.56709149","0.051808103","12.7033468","0.93254585","0.072531344","0.051808103","0.683866957","2.942700238","4.994301109" },
{ "M","287.5","77.40555208","0.052181173","12.72176999","0.918388645","0.073053642","0.041744938","0.667919015","2.901273221","5.218117303" },
{ "Avg","287.5","77.28705803","0.059928607","12.83514422","0.927590609","0.067745382","0.044295057","0.71653769","3.032908622","5.028791787" }
};

  system("rm -rf Toba_glass_incl");
  system("mkdir Toba_glass_incl");
  
  for (i=0; i<5; i++) { // 50 to 400 MPa in 25 MPa increments
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 400; cd 400; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 4000.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 375; cd 375; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3750.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 350; cd 350; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3500.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 325; cd 325; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3250.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 300; cd 300; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 3000.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 275; cd 275; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2750.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 250; cd 250; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2500.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 225; cd 225; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2250.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 200; cd 200; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 2000.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 175; cd 175; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1750.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 150; cd 150; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1500.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 125; cd 125; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1250.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 100; cd 100; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 1000.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 75; cd 75; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 750.0");
  system(string);
  
  strcpy(string, "cd Toba_glass_incl; mkdir ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_emp[i][0]);
  strcat(string, "; mkdir 50; cd 50; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_emp[i][2]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][3]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_emp[i][4]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_emp[i][5]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_emp[i][7]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_emp[i][8]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_emp[i][9]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_emp[i][10]);  /* K2O   */
  strcat(string, " 500.0");
  system(string);
  
  }

#endif  
  
}