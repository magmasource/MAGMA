#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {

  char *data_guil[74][11] = { 
/* these are new Toba data: SiO2, TiO2, Al2O3, FeO, MnO, MgO, CaO, Na2O, K2O, P2O5 */
{ "YTT_Gatti_1", "77.74", "0.05", "12.65", "0.91", "0.07", "0.06", "0.72", "2.75", "5.04", "0" },
{ "YTT_Gatti_2", "77.74", "0.06", "12.65", "0.91", "0.07", "0.06", "0.72", "2.74", "5.05", "0" },
{ "YTT_Gatti_3", "79.27", "0.05", "12.56", "0.92", "0.08", "0.05", "0.74", "1.69", "4.62", "0" },
{ "YTT_Gatti_4", "76.94", "0.12", "12.53", "0.88", "0.12", "0", "0.83", "3.4", "5.04", "0" },
{ "YTT_Gatti_5", "77.2", "0", "12.85", "0.85", "0", "0.07", "0.72", "3.2", "5.11", "0" },
{ "YTT_Gatti_6", "78.6", "0.06", "12.59", "1.03", "0.06", "0.06", "0.76", "1.8", "5.03", "0" },
{ "YTT_Gatti_7", "77.01", "0", "12.8", "0.9", "0", "0.11", "0.75", "3.21", "5.23", "0" },
{ "YTT_Gatti_8", "76.89", "0", "12.81", "0.83", "0", "0.1", "0.79", "3.26", "5.32", "0" },
{ "YTT_Gatti_9", "77", "0", "12.81", "0.87", "0", "0.07", "0.77", "3.13", "5.36", "0" },
{ "YTT_Gatti_10", "76.99", "0", "12.86", "0.88", "0", "0.12", "0.82", "2.96", "5.36", "0" },
{ "YTT_Gatti_11", "76.9", "0", "12.79", "0.88", "0", "0.1", "0.81", "3.17", "5.35", "0" },
{ "YTT_Gatti_12", "76.89", "0", "12.98", "0.85", "0", "0.07", "0.82", "3.05", "5.35", "0" },
{ "YTT_Gatti_13", "76.94", "0", "12.94", "0.84", "0", "0.11", "0.78", "3.23", "5.17", "0" },
{ "YTT_Gatti_14", "76.91", "0", "12.89", "0.87", "0", "0.1", "0.78", "3.23", "5.22", "0" },
{ "YTT_Gatti_15", "77.06", "0", "12.86", "0.85", "0", "0.09", "0.77", "3.13", "5.23", "0" },
{ "YTT_Gatti_16", "76.53", "0.07", "12.83", "0.96", "0.08", "0.04", "0.82", "3.27", "5.25", "0" },
{ "YTT_Gatti_17", "76.73", "0.08", "12.79", "0.88", "0.06", "0.04", "0.76", "3.34", "5.14", "0" },
{ "YTT_Gatti_18", "76.9", "0.09", "12.74", "0.93", "0.07", "0.05", "0.79", "3.41", "5.09", "0" },
{ "YTT_Gatti_19", "76.94", "0.06", "12.82", "0.89", "0.06", "0.05", "0.78", "3.42", "5", "0" },
{ "YTT_Gatti_20", "76.95", "0.07", "12.69", "0.91", "0.05", "0.05", "0.76", "3.44", "5.09", "0" },
{ "YTT_Gatti_21", "76.94", "0.06", "12.74", "0.95", "0.08", "0.04", "0.78", "3.46", "4.98", "0" },
{ "YTT_Gatti_22", "76.81", "0.05", "12.76", "0.92", "0.05", "0.05", "0.8", "3.48", "5.07", "0" },
{ "YTT_Gatti_23", "76.89", "0.07", "12.75", "0.91", "0.05", "0.06", "0.79", "3.46", "5.04", "0" },
{ "YTT_Gatti_24", "77.43", "0.05", "12.21", "0.88", "0.06", "0.06", "0.81", "3.28", "5.21", "0" },
{ "YTT_Gatti_25", "77", "0.05", "12.6", "0.89", "0.07", "0.06", "0.76", "3.35", "5.04", "0" },
{ "YTT_Gatti_26", "77.62", "0.07", "12.2", "0.9", "0.07", "0.05", "0.79", "3.17", "5", "0" },
{ "YTT_Gatti_27", "77.57", "0.05", "12.16", "0.92", "0.07", "0.05", "0.83", "3.17", "5.06", "0" },
{ "YTT_Gatti_28", "77.36", "0.05", "12.46", "0.87", "0.07", "0.06", "0.75", "3.25", "4.96", "0" },
{ "YTT_Gatti_29", "77.43", "0.05", "12.28", "0.88", "0.08", "0.05", "0.72", "3.37", "5.12", "0" },
{ "YTT_Gatti_30", "77.48", "0.06", "12.26", "0.87", "0.08", "0.053", "0.76", "3.44", "4.96", "0" },
{ "YTT_Gatti_31", "77.68", "0.05", "12.12", "0.88", "0.05", "0.06", "0.83", "3.22", "4.96", "0" },
{ "YTT_Gatti_32", "77.26", "0.05", "12.34", "0.89", "0.05", "0.07", "0.79", "3.31", "5.24", "0" },
{ "YTT_Gatti_33", "77.15", "0.06", "12.67", "0.86", "0.08", "0.06", "0.78", "3.26", "5.08", "0" },
{ "YTT_Gatti_34", "77.78", "0.05", "12.26", "0.86", "0.05", "0.04", "0.8", "3.08", "4.94", "0" },
{ "YTT_Gatti_35", "77.81", "0.05", "12.02", "0.86", "0.03", "0.05", "0.75", "3.24", "5.03", "0" },
{ "YTT_Gatti_36", "77.63", "0.05", "12.21", "0.87", "0.06", "0.06", "0.8", "3.13", "5.05", "0" },
{ "YTT_Gatti_37", "77.69", "0.09", "12.09", "0.88", "0.05", "0.06", "0.82", "3.14", "5.04", "0" },
{ "YTT_Gatti_38", "76.92", "0.06", "12.57", "0.87", "0.07", "0.05", "0.78", "3.36", "5.16", "0" },
{ "YTT_Gatti_39", "77.64", "0.05", "12.14", "0.87", "0.05", "0.04", "0.77", "3.22", "5.09", "0" },
{ "YTT_Gatti_40", "77.5", "0.07", "12.58", "0.89", "0.07", "0.06", "0.79", "3.29", "5.03", "0" },
{ "YTT_Gatti_41", "77.58", "0.07", "12.12", "0.9", "0.06", "0.06", "0.78", "3.1", "5.18", "0" },
{ "YTT_Gatti_42", "76.99", "0.06", "12.63", "0.9", "0.07", "0.06", "0.77", "3.22", "5.15", "0" },
{ "YTT_Gatti_43", "77.71", "0.08", "12.04", "0.85", "0.07", "0.05", "0.74", "3.14", "5.17", "0" },
{ "YTT_Gatti_44", "77.26", "0.05", "12.59", "0.92", "0.06", "0.05", "0.74", "3.22", "4.95", "0" },
{ "YTT_Gatti_45", "77.12", "0.05", "12.63", "0.94", "0.06", "0.05", "0.8", "3.14", "5.06", "0" },
{ "YTT_Gatti_46", "77.22", "0.05", "12.53", "0.94", "0.06", "0.05", "0.73", "3.18", "5.06", "0" },
{ "YTT_Gatti_47", "77.76", "0.06", "12.06", "0.88", "0.06", "0.05", "0.76", "3.21", "5.02", "0" },
{ "YTT_Gatti_48", "77.76", "0.03", "12.1", "0.87", "0.06", "0.05", "0.8", "3.08", "5.12", "0" },
{ "YTT_Gatti_49", "77.67", "0.07", "12.14", "0.89", "0.06", "0.05", "0.75", "3.24", "4.98", "0" },
{ "YTT_Gatti_50", "77.24", "0.05", "12.41", "0.84", "0.07", "0.05", "0.77", "2.95", "5.61", "0" },
{ "YTT_Gatti_51", "77.22", "0.04", "12.32", "0.84", "0.07", "0.05", "0.78", "3.2", "5.47", "0" },
{ "YTT_Gatti_52", "77.39", "0.04", "12.27", "0.9", "0.08", "0.07", "0.75", "3.27", "5.22", "0" },
{ "YTT_Gatti_53", "77.24", "0.06", "12.59", "0.87", "0.07", "0.06", "0.77", "3.09", "5.13", "0" },
{ "YTT_Gatti_54", "76.09", "0.17", "14.25", "0.76", "0.05", "0.1", "1.05", "2.62", "4.82", "0" },
{ "YTT_Gatti_55", "77.21", "0.05", "12.54", "0.89", "0.08", "0.06", "0.72", "3.4", "4.88", "0" },
{ "YTT_Gatti_56", "77.71", "0.06", "12.16", "0.89", "0.07", "0.05", "0.74", "3.24", "4.93", "0" },
{ "YTT_Gatti_57", "77.54", "0.08", "12.53", "0.83", "0", "0.05", "0.8", "3.02", "5.15", "0" },
{ "YTT_Gatti_58", "77.68", "0.08", "12.27", "0.84", "0.08", "0.05", "0.79", "3.16", "4.88", "0" },
{ "YTT_Gatti_59", "74.17", "0.14", "13.53", "0.95", "0.07", "0.25", "1.65", "3.82", "5.27", "0" },
{ "YTT_Gatti_60", "78.04", "0.05", "12.45", "0.85", "0.07", "0.06", "0.76", "2.86", "4.86", "0" },
{ "YTT_Gatti_61", "78.05", "0.05", "12.52", "0.84", "0.07", "0.06", "0.77", "2.78", "4.86", "0" },
{ "YTT_Gatti_62", "76.78", "0.23", "13.09", "0.97", "0.25", "0.87", "0.8", "2.75", "4.26", "0" },
{ "YTT_Gatti_63", "79.38", "0.07", "12.78", "0.89", "0.06", "0.04", "0.72", "1.47", "4.56", "0" },
{ "YTT_Gatti_64", "77.93", "0.05", "12.82", "0.87", "0.1", "0.02", "0.76", "2.66", "4.79", "0" },
{ "YTT_Gatti_65", "76.88", "0.09", "12.56", "0.91", "0.09", "0.07", "0.95", "3.21", "5.23", "0" },
{ "YTT_Gatti_66", "76.76", "0.13", "12.69", "1.06", "0.09", "0.1", "1.08", "3.14", "4.94", "0" },
{ "YTT_Gatti_67", "77.01", "0.09", "12.52", "0.92", "0.12", "0.07", "0.87", "3.17", "5.23", "0" },
{ "YTT_Gatti_68", "77.1", "0.08", "12.43", "0.93", "0.1", "0.06", "0.8", "3.39", "5.08", "0" },
{ "YTT_Gatti_69", "77.31", "0.07", "12.37", "0.92", "0.13", "0.05", "0.71", "3.41", "5.01", "0" },
{ "YTT_Gatti_70", "77.24", "0.06", "12.54", "0.85", "0.07", "0.05", "0.78", "3.1", "5.2", "0" },
{ "YTT_Gatti_71a", "77.37", "0.07", "12.55", "0.85", "0.08", "0.05", "0.69", "3.18", "5.04", "0" },
{ "YTT_Gatti_71b", "77.33", "0.07", "12.61", "0.87", "0.06", "0.05", "0.74", "3.12", "5.03", "0" },
{ "YTT_Gatti_71c", "77.13", "0.05", "12.64", "0.89", "0.07", "0.06", "0.79", "3.12", "5.13", "0" },
{ "YTT_Gatti_71d", "77.02", "0.06", "12.71", "0.92", "0.06", "0.08", "0.87", "3.11", "5.08", "0" }
  };
  
  char *string = (char *) malloc(500*sizeof(char));
  int i;
  
  system("rm -rf GUIL-RUNS");
  system("mkdir GUIL-RUNS");
  
  for (i=0; i<74; i++) {
  
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 5000.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 4750.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 4500.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 4250.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 4000.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 3750.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 3500.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 3250.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 3000.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 2750.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 2500.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 2250.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 2000.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 1750.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 1500.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 1250.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 1000.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 750.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 500.0");
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
  strcat(string, "8.0");            /* H2O   */
  strcat(string, " 250.0");
  system(string);
  
  }

}