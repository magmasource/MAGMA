#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {

  char *data_guil[85][11] = { 
/* these are Lydia's data: SiO2, TiO2, Al2O3, FeO, MnO, MgO, CaO, Na2O, K2O, P2O5 */
    { "PEV26G_2_2_1", "63.84", "0.36", "17.45", "3.9", "0", "2.29", "1.3", "4.28", "5.83", "0" }, 
    { "PEV26G_2_2_10", "64.48", "0", "20.95", "0.7", "0", "0.12", "4.63", "4.93", "4.19", "0" }, 
    { "PEV26G_2_2_11", "62.56", "0.35", "17.65", "3.86", "0", "3.93", "1.25", "3.35", "6.71", "0" }, 
    { "PEV26G_2_2_12", "64.64", "0.61", "17.78", "2.43", "0", "2.09", "0.77", "3.33", "8.14", "0" }, 
    { "PEV26G_2_2_13", "65.94", "0.49", "17.51", "2.63", "0", "1.51", "3.17", "4.01", "4.46", "0" }, 
    { "PEV26G_2_2_14", "61.98", "0.67", "16.34", "6.19", "0", "4.3", "1.32", "2.98", "6.21", "0" }, 
    { "PEV26G_2_2_3", "65.39", "0.6", "17.6", "2.38", "0", "1.08", "0.84", "3.85", "8.25", "0" }, 
    { "PEV26G_2_2_4", "62.5", "0.77", "18.04", "3.79", "0", "3.54", "1.54", "4.76", "4.38", "0" }, 
    { "PEV26G_2_2_6", "61.87", "0", "23.27", "4.22", "0", "6.58", "2.99", "0.88", "0.2", "0" }, 
    { "PEV26G_2_2_7", "78.64", "0.47", "11.16", "0.85", "0", "0.07", "0.32", "2.54", "5.94", "0" }, 
    { "PEV26G_2_2_8", "78.91", "0.45", "11.09", "0.86", "0.14", "0.15", "0.84", "2.69", "4.87", "0" }, 
    { "PEV26G_2_3_1", "65.17", "0.96", "16.51", "3.49", "0", "2.84", "1.11", "3.16", "6.76", "0" }, 
    { "PEV26G_2_3_12", "78.46", "0.39", "11.24", "0.64", "0", "0.07", "0.36", "2.2", "6.24", "0" }, 
    { "PEV26G_2_3_13", "73.71", "0.47", "13.34", "1.8", "0", "0.85", "0.7", "2.83", "6.31", "0" }, 
    { "PEV26G_2_3_14", "65.1", "0.45", "16.27", "3.93", "0", "3.42", "1.23", "2.92", "6.68", "0" }, 
    { "PEV26G_2_3_15", "64.96", "0.4", "15.99", "3.86", "0", "3.59", "1.3", "3.12", "6.35", "0" }, 
    { "PEV26G_2_3_16", "63.45", "0.73", "16.23", "4.65", "0", "3.43", "1.65", "2.95", "6.91", "0" }, 
    { "PEV26G_2_3_17", "63.3", "0.61", "17.25", "3.9", "0", "3.48", "1.21", "3.26", "6.98", "0" }, 
    { "PEV26G_2_3_18", "78.5", "0.5", "10.82", "0.86", "0", "0.15", "0.87", "2.28", "5.64", "0" }, 
    { "PEV26G_2_3_2", "64.09", "0.74", "16.78", "4.33", "0", "2.63", "1.16", "3.21", "7.07", "0" }, 
    { "PEV26G_2_3_20", "61.52", "0.42", "17.03", "4.88", "0", "4.62", "1.47", "3.09", "6.75", "0" }, 
    { "PEV26G_2_3_22", "78.71", "0.41", "11.42", "0.67", "0", "0.09", "0.64", "2.54", "5.52", "0" }, 
    { "PEV26G_2_3_23", "70", "0.67", "14.6", "2.49", "0", "1.4", "0.74", "2.83", "6.85", "0" }, 
    { "PEV26G_2_3_24", "65", "0.67", "17.46", "2.86", "0", "1.34", "0.82", "3.45", "8.4", "0" }, 
    { "PEV26G_2_3_3", "64.44", "0.39", "15.81", "5.13", "0", "4.39", "1.31", "3.35", "4.71", "0" }, 
    { "PEV26G_2_3_4", "63.94", "0.45", "17", "3.65", "0", "2.49", "1.16", "3.21", "7.7", "0" }, 
    { "PEV26G_2_3_5", "63.48", "0.6", "16.96", "3.57", "0", "2.4", "1.21", "3.05", "8.39", "0" }, 
    { "PEV26G_2_3_6", "63.91", "0.34", "18.7", "2.44", "0", "3.34", "1.21", "4.02", "6.06", "0" }, 
    { "PEV26G_2_3_7", "64.88", "0.64", "17.37", "3.14", "0", "2.4", "0.86", "3.36", "7.36", "0" }, 
    { "PEV26G_2_3_8", "64.48", "0.79", "18.01", "2.6", "0", "1.19", "0.84", "3.74", "8.35", "0" }, 
    { "PEV26G_2_3_9", "62.69", "0.64", "17.1", "4.91", "0", "3.28", "0.99", "3.04", "7.36", "0" }, 
    { "PEV26G_2_4_1", "62.52", "0.73", "17.14", "4.92", "0", "2.5", "1.28", "3.3", "7.05", "0" }, 
    { "PEV26G_2_4_10", "64.21", "0.66", "17.59", "3.28", "0", "2.04", "0.99", "3.07", "8.15", "0" }, 
    { "PEV26G_2_4_11", "63.26", "0.28", "17.62", "3.9", "0", "2.9", "0.91", "3.44", "7.16", "0" }, 
    { "PEV26G_2_4_12", "64.1", "0.22", "18.13", "3", "0", "2.95", "0.85", "3.99", "6.32", "0" }, 
    { "PEV26G_2_4_13", "64.74", "0.86", "15.95", "4.4", "0", "2.81", "0.94", "2.89", "7.42", "0" }, 
    { "PEV26G_2_4_14", "65.68", "0.6", "16.56", "3.35", "0", "2.84", "0.79", "3.19", "6.99", "0" }, 
    { "PEV26G_2_4_15", "64.36", "0.67", "17.15", "3.47", "0", "2.31", "0.95", "3.42", "7.67", "0" }, 
    { "PEV26G_2_4_16", "64.28", "0.78", "17.37", "2.81", "0", "1.29", "1", "3.4", "8.76", "0" }, 
    { "PEV26G_2_4_17", "63.63", "0.69", "16.53", "4.52", "0", "3.43", "1.07", "3.21", "6.94", "0" }, 
    { "PEV26G_2_4_18", "65.08", "0.6", "16.98", "3.28", "0", "0.94", "0.77", "3.55", "8.03", "0" }, 
    { "PEV26G_2_4_19", "61.57", "0.48", "16.7", "4.92", "0", "4.12", "1.49", "3.17", "6.99", "0" }, 
    { "PEV26G_2_4_2", "63.28", "0.69", "16.63", "4.79", "0", "3.46", "1.02", "3.15", "6.99", "0" }, 
    { "PEV26G_2_4_20", "68.05", "0.39", "15.71", "3.02", "0", "1.33", "0.84", "3.24", "6.99", "0" }, 
    { "PEV26G_2_4_22", "61.55", "0.7", "17.17", "5.45", "0", "3.9", "1.18", "3.4", "6.64", "0" }, 
    { "PEV26G_2_4_3", "62.8", "0.73", "17.29", "4.26", "0", "3.04", "1.03", "3.3", "7.54", "0" }, 
    { "PEV26G_2_4_4", "62.77", "0.53", "17.4", "4.57", "0", "3.12", "0.93", "3.07", "7.62", "0" }, 
    { "PEV26G_2_4_5", "65.02", "0.48", "17.53", "2.38", "0", "1.56", "0.82", "3.25", "8.34", "0" }, 
    { "PEV26G_2_4_6", "64.91", "0.51", "17.88", "2.36", "0", "1.15", "0.65", "3.62", "8.92", "0" }, 
    { "PEV26G_2_4_7", "64.26", "0.52", "16.06", "4.5", "0", "3.39", "0.91", "2.96", "7.39", "0" }, 
    { "PEV26G_2_4_8", "62.18", "0.37", "16.74", "5.07", "0", "4.3", "1.1", "3.07", "7.16", "0" }, 
    { "PEV26G_2_4_9", "63", "0.39", "17.75", "4.21", "0", "3.27", "0.97", "3.53", "6.89", "0" }, 
    { "PEV26G_2_5_1", "63.35", "0.53", "17.29", "3.79", "0", "3.02", "0.82", "3.2", "8.01", "0" }, 
    { "PEV26G_2_5_10", "62.18", "0.36", "15.87", "5.67", "0", "5.74", "1.24", "2.94", "6", "0" }, 
    { "PEV26G_2_5_12", "62.31", "0.62", "16.23", "5.73", "0", "4.23", "1.02", "3.03", "6.83", "0" }, 
    { "PEV26G_2_5_13", "61.71", "0.44", "16.67", "4.3", "0", "3.87", "1.68", "3.19", "6.91", "0" }, 
    { "PEV26G_2_5_14", "63.35", "0.21", "16.35", "5.16", "0", "3.82", "1.15", "2.84", "6.6", "0" }, 
    { "PEV26G_2_5_15", "63.7", "0.35", "17.36", "3.66", "0", "2.97", "0.9", "3.36", "7.71", "0" }, 
    { "PEV26G_2_5_16", "65.33", "0.64", "17.22", "2.7", "0", "1.81", "0.77", "3.53", "8", "0" }, 
    { "PEV26G_2_5_17", "63.35", "0.53", "16.29", "4.44", "0.18", "3.37", "0.99", "2.99", "7.52", "0" }, 
    { "PEV26G_2_5_18", "62.49", "0.81", "15.93", "5.37", "0", "4.16", "0.98", "2.92", "7.34", "0" }, 
    { "PEV26G_2_5_19", "63.67", "0.48", "16.28", "4.82", "0", "3.95", "1.12", "3.06", "6.38", "0" }, 
    { "PEV26G_2_5_2", "66.46", "0.43", "17.23", "2", "0", "1.15", "0.69", "3.13", "8.92", "0" }, 
    { "PEV26G_2_5_20", "61.98", "0.25", "16.11", "6.01", "0", "4.84", "1.03", "3", "6.78", "0" }, 
    { "PEV26G_2_5_21", "63.34", "0.54", "17.25", "3.72", "0", "2.96", "0.84", "3.3", "8.05", "0" }, 
    { "PEV26G_2_5_22", "62.73", "0.49", "16.35", "4.91", "0", "3.7", "1.08", "2.81", "7.94", "0" }, 
    { "PEV26G_2_5_23", "62.66", "0.58", "17.14", "4.48", "0", "3.53", "1.04", "3.2", "7.37", "0" }, 
    { "PEV26G_2_5_24", "62.44", "0.51", "17.07", "4.62", "0", "4.27", "0.89", "3.35", "6.84", "0" }, 
    { "PEV26G_2_5_25", "61.03", "0.62", "16.71", "5.71", "0", "5.02", "0.99", "3", "6.91", "0" }, 
    { "PEV26G_2_5_26", "61.38", "0.55", "16.6", "5.36", "0", "5.56", "1.49", "3.54", "5.53", "0" }, 
    { "PEV26G_2_5_27", "67.79", "0.46", "15.53", "2.92", "0", "2.28", "0.92", "3.09", "6.44", "0" }, 
    { "PEV26G_2_5_28", "62.5", "0.51", "16.55", "4.88", "0", "5.22", "1.04", "3.15", "6.15", "0" }, 
    { "PEV26G_2_5_3", "64.05", "0.28", "16.44", "4.66", "0", "3.45", "0.97", "2.99", "6.73", "0" }, 
    { "PEV26G_2_5_34", "62.45", "0.53", "17.11", "4.95", "0", "3.11", "1.59", "4", "6.26", "0" }, 
    { "PEV26G_2_5_4", "60.93", "0.65", "16.73", "5.63", "0", "5.22", "1.1", "3.17", "6.56", "0" }, 
    { "PEV26G_2_5_5", "63.58", "1.04", "17.64", "2.66", "0", "0.47", "1", "3.79", "8.93", "0" }, 
    { "PEV26G_2_5_6", "62.98", "0.83", "17.44", "4.07", "0", "2.68", "0.87", "3.25", "7.88", "0" }, 
    { "PEV26G_2_5_7", "62.49", "0.67", "17.09", "4.52", "0", "3.33", "1", "3.29", "7.61", "0" }, 
    { "PEV26G_2_5_8", "63.65", "0.43", "15.83", "4.94", "0", "5.33", "0.99", "3.21", "5.62", "0" }, 
    { "PEV26G_2_5_9", "63.19", "0.65", "17.53", "3.79", "0", "3.21", "0.94", "3.33", "7.36", "0" }, 
    { "PEV26G_2_1_10", "72.54", "0.34", "13.39", "2.45", "0", "0.86", "3.77", "3.29", "3.35", "0" }, 
    { "PEV26G_2_1_11", "78.65", "0.4", "11.18", "0.94", "0", "0.06", "0.32", "2.67", "5.77", "0" }, 
    { "PEV26G_2_1_12", "63.98", "0.33", "17.66", "2.87", "0", "1.48", "0.79", "3.25", "8.84", "0" }, 
    { "PEV26G_2_1_13", "63.96", "0.51", "17.33", "3.99", "0", "2.31", "1.09", "3.59", "6.72", "0" }, 
    { "PEV26G_2_1_14", "61.51", "0.44", "16.66", "5.26", "0", "3.68", "1.69", "3.19", "7.07", "0" }
  };
  
  char *string = (char *) malloc(500*sizeof(char));
  int i;
  
  system("rm -rf GUIL-RUNS");
  system("mkdir GUIL-RUNS");
  
  for (i=0; i<85; i++) {
  
  strcpy(string, "cd GUIL-RUNS; mkdir ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 500; cd 500; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 5000.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 475; cd 475; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 4750.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 450; cd 450; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 4500.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 425; cd 425; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 4250.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 400; cd 400; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 4000.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 375; cd 375; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 3750.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 350; cd 350; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 3500.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 325; cd 325; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 3250.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 300; cd 300; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 3000.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 275; cd 275; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 2750.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 250; cd 250; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 2500.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 225; cd 225; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 2250.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 200; cd 200; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 2000.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 175; cd 175; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 1750.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 150; cd 150; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 1500.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 125; cd 125; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 1250.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 100; cd 100; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 1000.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 75; cd 75; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 750.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 50; cd 50; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 500.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  strcpy(string, "cd GUIL-RUNS; cd ");
  strcat(string, data_guil[i][0]);
  strcat(string, "; mkdir 25; cd 25; ulimit -t 15; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, data_guil[i][1]);  /* SiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][2]);  /* TiO2  */
  strcat(string, " ");
  strcat(string, data_guil[i][3]);  /* Al2O3 */
  strcat(string, " ");
  strcat(string, data_guil[i][4]);  /* FeO   */
  strcat(string, " ");
  strcat(string, data_guil[i][5]);  /* MnO   */
  strcat(string, " ");
  strcat(string, data_guil[i][6]);  /* MgO   */
  strcat(string, " ");
  strcat(string, data_guil[i][7]);  /* CaO   */
  strcat(string, " ");
  strcat(string, data_guil[i][8]);  /* Na2O  */
  strcat(string, " ");
  strcat(string, data_guil[i][9]);  /* K2O   */
  strcat(string, " ");
  strcat(string, data_guil[i][10]); /* P2O5  */
  strcat(string, " ");
  strcat(string, "10.0"); /* H2O   */
  strcat(string, " 250.0");
  strcat(string, " ");
  strcat(string, "1.0");  /* delta QFM  */
  system(string);
  
  }

}