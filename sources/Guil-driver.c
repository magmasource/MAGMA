#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {

  char *data_guil[55][13] = { 
/* these are Lydia's data: SiO2, TiO2, Al2O3, FeO, MnO, MgO, CaO, Na2O, K2O, P2O5, H2O, delta QFM */
    { "OhiB_H2O_10_QFM_0", "69.27", "0.80", "14.85", "3.71", "0.00", "0.96", "3.02", "4.07", "3.32", "0.00", "10", "0" }, 
    { "OhiB_H2O_10_QFM_0.5", "69.27", "0.80", "14.85", "3.71", "0.00", "0.96", "3.02", "4.07", "3.32", "0.00", "10", "0.5" }, 
    { "OhiB_H2O_10_QFM_1", "69.27", "0.80", "14.85", "3.71", "0.00", "0.96", "3.02", "4.07", "3.32", "0.00", "10", "1" }, 
    { "OhiB_H2O_10_QFM_1.5", "69.27", "0.80", "14.85", "3.71", "0.00", "0.96", "3.02", "4.07", "3.32", "0.00", "10", "1.5" }, 
    { "OhiB_H2O_10_QFM_2", "69.27", "0.80", "14.85", "3.71", "0.00", "0.96", "3.02", "4.07", "3.32", "0.00", "10", "2" }, 
    { "X225BD_H2O_10_QFM_0", "69.53", "0.79", "14.75", "3.61", "0.00", "0.93", "2.96", "4.02", "3.40", "0.00", "10", "0" }, 
    { "X225BD_H2O_10_QFM_0.5", "69.53", "0.79", "14.75", "3.61", "0.00", "0.93", "2.96", "4.02", "3.40", "0.00", "10", "0.5" }, 
    { "X225BD_H2O_10_QFM_1", "69.53", "0.79", "14.75", "3.61", "0.00", "0.93", "2.96", "4.02", "3.40", "0.00", "10", "1" }, 
    { "X225BD_H2O_10_QFM_1.5", "69.53", "0.79", "14.75", "3.61", "0.00", "0.93", "2.96", "4.02", "3.40", "0.00", "10", "1.5" }, 
    { "X225BD_H2O_10_QFM_2", "69.53", "0.79", "14.75", "3.61", "0.00", "0.93", "2.96", "4.02", "3.40", "0.00", "10", "2" }, 
    { "X225CE_H2O_10_QFM_0", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "10", "0" }, 
    { "X225CE_H2O_10_QFM_0.5", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "10", "0.5" }, 
    { "X225CE_H2O_10_QFM_1", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "10", "1" }, 
    { "X225CE_H2O_10_QFM_1.5", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "10", "1.5" }, 
    { "X225CE_H2O_10_QFM_2", "70.16", "0.72", "14.58", "3.45", "0.00", "0.81", "2.70", "4.12", "3.45", "0.00", "10", "2" }, 
    { "X225DE_H2O_10_QFM_0", "69.86", "0.75", "14.74", "3.42", "0.00", "0.87", "2.84", "4.08", "3.44", "0.00", "10", "0" }, 
    { "X225DE_H2O_10_QFM_0.5", "69.86", "0.75", "14.74", "3.42", "0.00", "0.87", "2.84", "4.08", "3.44", "0.00", "10", "0.5" }, 
    { "X225DE_H2O_10_QFM_1", "69.86", "0.75", "14.74", "3.42", "0.00", "0.87", "2.84", "4.08", "3.44", "0.00", "10", "1" }, 
    { "X225DE_H2O_10_QFM_1.5", "69.86", "0.75", "14.74", "3.42", "0.00", "0.87", "2.84", "4.08", "3.44", "0.00", "10", "1.5" }, 
    { "X225DE_H2O_10_QFM_2", "69.86", "0.75", "14.74", "3.42", "0.00", "0.87", "2.84", "4.08", "3.44", "0.00", "10", "2" }, 
    { "X129AC_H2O_10_QFM_0", "71.84", "0.61", "14.10", "2.90", "0.00", "0.61", "2.27", "3.73", "3.94", "0.00", "10", "0" }, 
    { "X129AC_H2O_10_QFM_0.5", "71.84", "0.61", "14.10", "2.90", "0.00", "0.61", "2.27", "3.73", "3.94", "0.00", "10", "0.5" }, 
    { "X129AC_H2O_10_QFM_1", "71.84", "0.61", "14.10", "2.90", "0.00", "0.61", "2.27", "3.73", "3.94", "0.00", "10", "1" }, 
    { "X129AC_H2O_10_QFM_1.5", "71.84", "0.61", "14.10", "2.90", "0.00", "0.61", "2.27", "3.73", "3.94", "0.00", "10", "1.5" }, 
    { "X129AC_H2O_10_QFM_2", "71.84", "0.61", "14.10", "2.90", "0.00", "0.61", "2.27", "3.73", "3.94", "0.00", "10", "2" }, 
    { "X109AC-1_H2O_10_QFM_0", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "10", "0" }, 
    { "X109AC-1_H2O_10_QFM_0.5", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "10", "0.5" }, 
    { "X109AC-1_H2O_10_QFM_1", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "10", "1" }, 
    { "X109AC-1_H2O_10_QFM_1.5", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "10", "1.5" }, 
    { "X109AC-1_H2O_10_QFM_2", "70.31", "0.76", "14.27", "3.78", "0.00", "0.84", "2.83", "3.58", "3.64", "0.00", "10", "2" }, 
    { "X109AC-2_H2O_10_QFM_0", "63.94", "1.11", "14.97", "7.49", "0.00", "1.68", "4.80", "3.43", "2.59", "0.00", "10", "0" }, 
    { "X109AC-2_H2O_10_QFM_0.5", "63.94", "1.11", "14.97", "7.49", "0.00", "1.68", "4.80", "3.43", "2.59", "0.00", "10", "0.5" }, 
    { "X109AC-2_H2O_10_QFM_1", "63.94", "1.11", "14.97", "7.49", "0.00", "1.68", "4.80", "3.43", "2.59", "0.00", "10", "1" }, 
    { "X109AC-2_H2O_10_QFM_1.5", "63.94", "1.11", "14.97", "7.49", "0.00", "1.68", "4.80", "3.43", "2.59", "0.00", "10", "1.5" }, 
    { "X109AC-2_H2O_10_QFM_2", "63.94", "1.11", "14.97", "7.49", "0.00", "1.68", "4.80", "3.43", "2.59", "0.00", "10", "2" }, 
    { "X108BC_H2O_10_QFM_0", "64.85", "1.15", "14.65", "6.75", "0.00", "1.71", "4.48", "3.64", "2.78", "0.00", "10", "0" }, 
    { "X108BC_H2O_10_QFM_0.5", "64.85", "1.15", "14.65", "6.75", "0.00", "1.71", "4.48", "3.64", "2.78", "0.00", "10", "0.5" }, 
    { "X108BC_H2O_10_QFM_1", "64.85", "1.15", "14.65", "6.75", "0.00", "1.71", "4.48", "3.64", "2.78", "0.00", "10", "1" }, 
    { "X108BC_H2O_10_QFM_1.5", "64.85", "1.15", "14.65", "6.75", "0.00", "1.71", "4.48", "3.64", "2.78", "0.00", "10", "1.5" }, 
    { "X108BC_H2O_10_QFM_2", "64.85", "1.15", "14.65", "6.75", "0.00", "1.71", "4.48", "3.64", "2.78", "0.00", "10", "2" }, 
    { "X108AD_H2O_10_QFM_0", "64.76", "1.01", "15.19", "6.15", "0.00", "1.88", "4.59", "3.71", "2.71", "0.00", "10", "0" }, 
    { "X108AD_H2O_10_QFM_0.5", "64.76", "1.01", "15.19", "6.15", "0.00", "1.88", "4.59", "3.71", "2.71", "0.00", "10", "0.5" }, 
    { "X108AD_H2O_10_QFM_1", "64.76", "1.01", "15.19", "6.15", "0.00", "1.88", "4.59", "3.71", "2.71", "0.00", "10", "1" }, 
    { "X108AD_H2O_10_QFM_1.5", "64.76", "1.01", "15.19", "6.15", "0.00", "1.88", "4.59", "3.71", "2.71", "0.00", "10", "1.5" }, 
    { "X108AD_H2O_10_QFM_2", "64.76", "1.01", "15.19", "6.15", "0.00", "1.88", "4.59", "3.71", "2.71", "0.00", "10", "2" }, 
    { "X161AC_H2O_10_QFM_0", "63.20", "1.10", "15.53", "7.11", "0.00", "1.84", "5.26", "3.39", "2.58", "0.00", "10", "0" }, 
    { "X161AC_H2O_10_QFM_0.5", "63.20", "1.10", "15.53", "7.11", "0.00", "1.84", "5.26", "3.39", "2.58", "0.00", "10", "0.5" }, 
    { "X161AC_H2O_10_QFM_1", "63.20", "1.10", "15.53", "7.11", "0.00", "1.84", "5.26", "3.39", "2.58", "0.00", "10", "1" }, 
    { "X161AC_H2O_10_QFM_1.5", "63.20", "1.10", "15.53", "7.11", "0.00", "1.84", "5.26", "3.39", "2.58", "0.00", "10", "1.5" }, 
    { "X161AC_H2O_10_QFM_2", "63.20", "1.10", "15.53", "7.11", "0.00", "1.84", "5.26", "3.39", "2.58", "0.00", "10", "2" }, 
    { "X262AD_H2O_10_QFM_0", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "10", "0" }, 
    { "X262AD_H2O_10_QFM_0.5", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "10", "0.5" }, 
    { "X262AD_H2O_10_QFM_1", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "10", "1" }, 
    { "X262AD_H2O_10_QFM_1.5", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "10", "1.5" }, 
    { "X262AD_H2O_10_QFM_2", "70.78", "0.74", "14.30", "3.33", "0.00", "0.73", "2.54", "3.96", "3.62", "0.00", "10", "2" }
  };
  
  char *string = (char *) malloc(500*sizeof(char));
  int i;
  
  system("rm -rf GUIL-RUNS");
  system("mkdir GUIL-RUNS");
  
  for (i=0; i<55; i++) {
  
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 5000.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 4750.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 4500.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 4250.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 4000.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 3750.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 3500.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 3250.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 3000.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 2750.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 2500.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 2250.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 2000.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 1750.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 1500.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 1250.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 1000.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 750.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 500.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
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
  strcat(string, data_guil[i][11]); /* H2O   */
  strcat(string, " 250.0");
  strcat(string, " ");
  strcat(string, data_guil[i][12]);  /* delta QFM  */
  system(string);
  
  }

}