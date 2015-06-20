#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {

  char *data_guil[11][11] = { 
/* these are Lydia's data: SiO2, TiO2, Al2O3, FeO, MnO, MgO, CaO, Na2O, K2O, P2O5, H2O, delta NNO */
    { "D157", "68.40182648", "0.507356672", "16.2658549", "3.396480224", "0.131912735", "0.720446474", "2.749873161", "5.083713851", "2.262810756", "0.101471334" }, 
    { "Oh4_1", "67.67374716", "0.546504434", "16.01361105", "3.609193782", "0.144359662", "1.020829037", "3.15528975", "5.269127655", "2.010723861", "0.154671066" }, 
    { "Oh4_4", "66.02557545", "0.624040921", "16.76726343", "3.902939951", "0.163682864", "0.971867008", "3.549872123", "5.15601023", "2.230179028", "0.173913043" }, 
    { "Oh4_7", "65.56776557", "0.610500611", "16.92104192", "4.147399139", "0.152625153", "1.027676028", "3.540903541", "5.413105413", "1.984126984", "0.172975173" }, 
    { "D153b", "70.07898246", "0.471843266", "15.47851062", "3.036537204", "0.112832085", "0.676992512", "2.656682737", "4.338906555", "2.697712586", "0.112832085" }, 
    { "D153c", "67.02105909", "0.562257207", "17.0926191", "3.467819391", "0.1226743", "0.776937232", "3.404211818", "4.947863423", "2.17746882", "0.040891433" }, 
    { "D192", "68.14030718", "0.487754255", "16.51100042", "3.268240685", "0.145288501", "0.799086758", "2.750103778", "4.555832296", "2.926525529", "0.051888751" }, 
    { "D27", "69.40728545", "0.483638609", "15.93949372", "2.536976516", "0.082321465", "0.637991356", "2.623996707", "5.227413048", "2.675447623", "0.102901832" }, 
    { "D3", "68.02051282", "0.564102564", "16.53333333", "3.709917195", "0.133333333", "0.8", "2.892307692", "4.656410256", "2.256410256", "0.020512821" }, 
    { "D59", "69.16521203", "0.503131738", "16.01807167", "3.307588245", "0.123215936", "0.667419653", "2.608070644", "4.353629736", "2.803162542", "0.082143957" }, 
    { "D87", "69.80228292", "0.4790053", "15.34855279", "3.191276862", "0.122299225", "0.693028944", "2.751732572", "4.830819405", "2.303302079", "0.122299225" }
  };
  
  char *string = (char *) malloc(500*sizeof(char));
  int i;
  
  system("rm -rf GUIL-RUNS");
  system("mkdir GUIL-RUNS");
  
  for (i=0; i<11; i++) {
  
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