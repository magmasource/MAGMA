#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {

  char *data_guil[71][11] = { 
/* these are Lydia's data: SiO2, TiO2, Al2O3, FeO, MnO, MgO, CaO, Na2O, K2O, P2O5 */
    { "Ch98_YTT_Welded_54", "75.18", "0.19", "13.27", "1.75", "0.06", "0.39", "1.56", "2.91", "4.68", "0.02" }, 
    { "Ch98_YTT_Welded_11", "73.15", "0.33", "13.86", "2.25", "0.07", "0.70", "2.15", "3.36", "4.05", "0.08" }, 
    { "Ch98_YTT_Welded_70", "70.59", "0.46", "15.14", "3.00", "0.08", "0.74", "2.81", "3.46", "3.62", "0.09" }, 
    { "Ch98_YTT_Pumice_5B3", "76.76", "0.06", "13.29", "1.09", "0.08", "0.18", "0.67", "2.93", "4.92", "0.02" }, 
    { "Ch98_YTT_Pumice_17A1", "76.39", "0.14", "12.73", "1.54", "0.08", "0.36", "1.23", "2.66", "4.84", "0.02" }, 
    { "Ch98_YTT_Pumice_94A5", "75.97", "0.18", "12.83", "1.64", "0.07", "0.33", "1.20", "2.78", "4.98", "0.02" }, 
    { "Ch98_YTT_Pumice_51A5", "75.35", "0.24", "12.94", "1.91", "0.07", "0.40", "1.51", "2.87", "4.70", "0.01" }, 
    { "Ch98_YTT_Pumice_51A1", "74.40", "0.26", "13.48", "1.99", "0.07", "0.45", "1.70", "3.00", "4.62", "0.02" }, 
    { "Ch98_YTT_Pumice_51A2", "73.92", "0.33", "13.46", "2.38", "0.07", "0.53", "2.04", "2.99", "4.27", "0.02" }, 
    { "Ch98_YTT_Pumice_6A2", "72.32", "0.30", "14.61", "2.67", "0.08", "0.58", "2.18", "2.97", "4.26", "0.02" }, 
    { "Ch98_YTT_Pumice_40A1", "71.44", "0.50", "14.33", "3.50", "0.09", "0.82", "2.66", "2.92", "3.72", "0.02" }, 
    { "Ch98_YTT_Pumice_23A2", "71.11", "0.36", "14.84", "3.13", "0.08", "0.72", "2.95", "3.15", "3.63", "0.02" }, 
    { "Ch98_YTT_Pumice_57A2", "69.87", "0.56", "14.77", "3.56", "0.09", "0.96", "3.29", "3.32", "3.53", "0.04" }, 
    { "Ch98_YTT_Pumice_57A3", "69.18", "0.61", "14.88", "3.87", "0.09", "1.11", "3.51", "3.33", "3.37", "0.04" }, 
    { "Ch98_YTT_Pumice_40B1", "69.12", "0.42", "15.30", "3.70", "0.13", "0.85", "3.07", "3.23", "4.14", "0.02" }, 
    { "Ch98_YTT_Glass_94A5_G", "78.18", "0.04", "12.05", "0.83", "0.06", "0.15", "0.62", "2.79", "5.26", "0.01" }, 
    { "Ch98_YTT_Glass_51A5_G", "78.28", "0.06", "11.91", "0.92", "0.07", "0.17", "0.69", "2.68", "5.21", "0.01" }, 
    { "Ch98_YTT_Glass_6A2_G", "77.67", "0.08", "12.79", "0.76", "0.06", "0.20", "0.80", "2.60", "5.03", "0.01" }, 
    { "Ch98_YTT_Glass_63A1_G", "76.91", "0.08", "12.95", "1.09", "0.07", "0.18", "0.94", "2.94", "4.83", "0.01" }, 
    { "ChLu10_YTT_5B3WR", "76.76", "0.06", "13.29", "1.09", "0.08", "0.18", "0.67", "2.93", "4.92", "0.02" }, 
    { "ChLu10_YTT_5B3_3_MI", "76.36", "0.07", "12.77", "0.97", "0.10", "0.07", "0.78", "3.65", "5.21", "0.02" }, 
    { "ChLu10_YTT_5B3_MG", "77.31", "0.07", "12.37", "0.92", "0.13", "0.05", "0.71", "3.41", "5.01", "0.02" }, 
    { "ChLu10_YTT_55A1_WR", "75.97", "0.18", "12.98", "1.55", "0.07", "0.30", "1.20", "2.83", "4.91", "0.01" }, 
    { "ChLu10_YTT_55A1_3_MI", "75.78", "0.11", "13.04", "1.03", "0.06", "0.07", "0.85", "3.69", "5.32", "0.05" }, 
    { "ChLu10_YTT_55A1_MG", "77.11", "0.08", "12.43", "0.93", "0.10", "0.06", "0.80", "3.39", "5.08", "0.02" }, 
    { "ChLu10_YTT_23A4_WR", "74.99", "0.19", "13.30", "1.86", "0.07", "0.44", "1.62", "2.97", "4.54", "0.02" }, 
    { "ChLu10_YTT_23A4_3_MI", "76.13", "0.06", "12.76", "1.13", "0.06", "0.05", "0.61", "3.67", "5.52", "0.01" }, 
    { "ChLu10_YTT_23A4_MG", "77.00", "0.09", "12.52", "0.92", "0.12", "0.07", "0.87", "3.17", "5.23", "0.01" }, 
    { "ChLu10_YTT_12A1_WR", "71.99", "0.27", "15.92", "2.50", "0.08", "0.48", "2.08", "2.80", "3.85", "0.03" }, 
    { "ChLu10_YTT_12A1_3_MI", "76.58", "0.07", "12.38", "1.01", "0.08", "0.06", "0.73", "3.77", "5.31", "0.01" }, 
    { "ChLu10_YTT_12A1_MG", "76.88", "0.09", "12.56", "0.91", "0.09", "0.07", "0.95", "3.21", "5.23", "0.01" }, 
    { "ChLu10_YTT_21A4_WR", "70.19", "0.41", "15.67", "3.30", "0.08", "0.76", "2.86", "3.10", "3.57", "0.06" }, 
    { "ChLu10_YTT_21A4_3MI", "76.51", "0.09", "12.23", "0.97", "0.21", "0.05", "0.81", "4.32", "4.78", "0.03" }, 
    { "ChLu10_YTT_21A4_MG", "76.75", "0.13", "12.69", "1.06", "0.09", "0.10", "1.08", "3.14", "4.94", "0.02" }, 
    { "ChLu10_PYLD_TT2_WR", "75.87", "0.12", "13.13", "1.26", "0.07", "0.18", "1.14", "3.40", "4.82", "0.01" }, 
    { "ChLu10_PYLD_TT2_3_MI", "76.96", "0.09", "12.32", "0.97", "0.07", "0.06", "0.73", "3.78", "4.99", "0.03" }, 
    { "ChLu10_PYLD_TT2_MG", "77.41", "0.08", "12.26", "0.89", "0.16", "0.05", "0.71", "3.40", "5.03", "0.01" }, 
    { "ChLu10_PYLD_TT7_WR", "69.78", "0.40", "15.37", "3.23", "0.08", "1.01", "3.22", "3.46", "3.34", "0.11" }, 
    { "ChLu10_PYLD_TT7_3_MI", "76.34", "0.06", "12.55", "1.02", "0.06", "0.08", "0.89", "3.70", "5.30", "0.00" }, 
    { "ChLu10_PYLD_TT7_MG", "76.65", "0.10", "12.71", "1.04", "0.10", "0.07", "0.98", "3.15", "5.18", "0.02" }, 
    { "Ch98_MTT_Welded_7", "76.31", "0.13", "13.00", "1.42", "0.02", "0.21", "1.02", "3.57", "4.31", "0.01" }, 
    { "Ch98_MTT_Welded_8", "74.33", "0.21", "13.80", "1.88", "0.05", "0.39", "1.76", "3.23", "4.30", "0.05" }, 
    { "Ch98_MTT_Fiamme_41A", "75.58", "0.14", "13.38", "1.96", "0.05", "0.22", "0.93", "3.20", "4.51", "0.03" }, 
    { "Ch98_MTT_Fiamme_41B", "72.80", "0.33", "14.23", "3.45", "0.06", "0.41", "1.60", "2.95", "4.15", "0.02" }, 
    { "Ch98_MTT_Glass_7_G", "75.34", "0.06", "14.00", "1.29", "0.03", "0.14", "0.75", "3.52", "4.86", "0.02" }, 
    { "Ch98_MTT_Glass_8_G", "77.03", "0.10", "12.65", "1.08", "0.05", "0.18", "0.82", "2.98", "5.09", "0.02" }, 
    { "ChLu10_MTT_66_WR", "77.94", "0.12", "13.47", "0.68", "0.01", "0.18", "0.58", "2.56", "4.44", "0.02" }, 
    { "ChLu10_MTT_66_1_MI", "76.56", "0.04", "12.44", "1.14", "0.11", "0.00", "0.66", "3.90", "5.15", "0.00" }, 
    { "ChLu10_MTT_7A_WR", "76.12", "0.16", "13.15", "1.65", "0.05", "0.24", "1.24", "3.19", "4.18", "0.02" }, 
    { "ChLu10_MTT_7A_1_MI", "75.03", "0.05", "13.40", "1.25", "0.01", "0.01", "0.64", "3.67", "5.94", "0.00" }, 
    { "ChLu10_MTT_99_WR", "74.42", "0.26", "14.14", "1.70", "0.04", "0.41", "1.72", "2.87", "4.42", "0.02" }, 
    { "ChLu10_MTT_99_3AMI", "74.51", "0.03", "13.44", "1.30", "0.10", "0.02", "0.73", "4.47", "5.40", "0.00" }, 
    { "ChLu10_MTT_99_MG", "77.19", "0.06", "12.57", "0.75", "0.04", "0.01", "0.73", "3.12", "5.51", "0.02" }, 
    { "Ch98_OTT_Welded_27", "72.59", "0.22", "14.16", "2.27", "0.07", "0.58", "1.94", "3.11", "4.99", "0.06" }, 
    { "Ch98_OTT_Welded_15A", "73.65", "0.26", "14.01", "1.69", "0.04", "0.52", "1.93", "3.67", "4.18", "0.06" }, 
    { "Ch98_OTT_Welded_74", "70.19", "0.38", "14.85", "3.17", "0.07", "0.79", "2.82", "3.51", "4.09", "0.12" }, 
    { "Ch98_OTT_Fiamme_76A1", "74.50", "0.18", "13.57", "1.30", "0.02", "0.50", "1.43", "3.36", "5.10", "0.04" }, 
    { "Ch98_OTT_Fiamme_86A1", "70.64", "0.44", "14.54", "3.19", "0.08", "0.77", "2.87", "3.68", "3.67", "0.11" }, 
    { "Ch98_OTT_Fiamme_74A7", "65.65", "0.75", "15.98", "3.99", "0.08", "1.94", "4.50", "3.51", "3.40", "0.20" }, 
    { "Ch98_OTT_Fiamme_74A2", "61.80", "0.81", "18.29", "5.23", "0.10", "1.26", "4.70", "4.13", "3.47", "0.21" }, 
    { "Ch98_OTT_Glass_15A_G", "76.48", "0.08", "13.28", "0.55", "0.02", "0.17", "1.04", "3.56", "4.79", "0.03" }, 
    { "Ch98_OTT_Glass_74_G", "72.18", "0.23", "14.48", "2.33", "0.06", "0.56", "1.91", "3.45", "4.72", "0.08" }, 
    { "ChLu10_OTT_85_WR", "73.20", "0.22", "13.88", "2.23", "0.06", "0.47", "1.82", "3.48", "4.58", "0.06" }, 
    { "ChLu10_OTT_85_1_MI", "74.76", "0.09", "13.59", "1.23", "0.10", "0.00", "0.60", "3.72", "5.91", "0.00" }, 
    { "ChLu10_OTT_27_MG", "77.54", "0.06", "12.38", "0.66", "0.08", "0.01", "0.70", "2.51", "6.05", "0.01" }, 
    { "ChLu10_OTT_25A_WR", "71.30", "0.37", "14.34", "3.14", "0.06", "0.78", "2.68", "3.41", "3.82", "0.10" }, 
    { "ChLu10_OTT_25A1_MI", "76.75", "0.02", "12.64", "1.04", "0.08", "0.00", "0.72", "3.53", "5.21", "0.01" }, 
    { "ChLu10_OTT_77_WR", "69.19", "0.51", "14.76", "3.98", "0.08", "0.94", "3.44", "3.43", "3.51", "0.16" }, 
    { "ChLu10_OTT_77_2_MI", "76.97", "0.03", "12.37", "1.15", "0.07", "0.01", "0.63", "3.26", "5.49", "0.02" }, 
    { "Ch98_HDT_Welded_9", "64.25", "0.67", "16.39", "5.49", "0.11", "1.62", "5.47", "2.81", "3.02", "0.17" }, 
    { "Ch98_HDT_Fiamme_46A", "65.86", "0.73", "16.50", "4.55", "0.08", "1.23", "4.75", "2.69", "3.46", "0.14" }
  };
  
  char *string = (char *) malloc(500*sizeof(char));
  int i;
  
  system("rm -rf GUIL-RUNS");
  system("mkdir GUIL-RUNS");
  
  for (i=0; i<71; i++) {
  
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
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
  strcat(string, "0.0");  /* delta NNO  */
  system(string);
  
  }

}