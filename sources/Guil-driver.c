#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[]) {
  char *string = (char *) malloc(500*sizeof(char));
  int i;
  
  system("rm -rf Bishop_runs");
  system("mkdir Bishop_runs");
  
  // 0 ppm CO2, 4.74 wt% H2O
  strcpy(string, "cd Bishop_runs; mkdir LBT-pum+1_000; cd LBT-pum+1_000;");
  strcat(string, "mkdir 400; cd 400; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 4000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_000;");
  strcat(string, "mkdir 375; cd 375; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 3750.0");
  system(string);

  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_000;");
  strcat(string, "mkdir 350; cd 350; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 3500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_000;");
  strcat(string, "mkdir 325; cd 325; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 3250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_000;");
  strcat(string, "mkdir 300; cd 300; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 3000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_000;");
  strcat(string, "mkdir 275; cd 275; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 2750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_000;");
  strcat(string, "mkdir 250; cd 250; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 2500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_000;");
  strcat(string, "mkdir 225; cd 225; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 2250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_000;");
  strcat(string, "mkdir 200; cd 200; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 2000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_000;");
  strcat(string, "mkdir 175; cd 175; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 1750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_000;");
  strcat(string, "mkdir 150; cd 150; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 1500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_000;");
  strcat(string, "mkdir 125; cd 125; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 1250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_000;");
  strcat(string, "mkdir 100; cd 100; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.000 1000.0");
  system(string);
  
  // 10 ppm CO2, 4.74 wt% H2O
  strcpy(string, "cd Bishop_runs; mkdir LBT-pum+1_001; cd LBT-pum+1_001;");
  strcat(string, "mkdir 400; cd 400; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 4000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_001;");
  strcat(string, "mkdir 375; cd 375; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 3750.0");
  system(string);

  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_001;");
  strcat(string, "mkdir 350; cd 350; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 3500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_001;");
  strcat(string, "mkdir 325; cd 325; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 3250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_001;");
  strcat(string, "mkdir 300; cd 300; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 3000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_001;");
  strcat(string, "mkdir 275; cd 275; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 2750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_001;");
  strcat(string, "mkdir 250; cd 250; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 2500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_001;");
  strcat(string, "mkdir 225; cd 225; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 2250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_001;");
  strcat(string, "mkdir 200; cd 200; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 2000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_001;");
  strcat(string, "mkdir 175; cd 175; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 1750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_001;");
  strcat(string, "mkdir 150; cd 150; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 1500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_001;");
  strcat(string, "mkdir 125; cd 125; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 1250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_001;");
  strcat(string, "mkdir 100; cd 100; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.001 1000.0");
  system(string);
  
  // 20 ppm CO2, 4.74 wt% H2O
  strcpy(string, "cd Bishop_runs; mkdir LBT-pum+1_002; cd LBT-pum+1_002;");
  strcat(string, "mkdir 400; cd 400; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 4000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_002;");
  strcat(string, "mkdir 375; cd 375; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 3750.0");
  system(string);

  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_002;");
  strcat(string, "mkdir 350; cd 350; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 3500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_002;");
  strcat(string, "mkdir 325; cd 325; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 3250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_002;");
  strcat(string, "mkdir 300; cd 300; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 3000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_002;");
  strcat(string, "mkdir 275; cd 275; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 2750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_002;");
  strcat(string, "mkdir 250; cd 250; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 2500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_002;");
  strcat(string, "mkdir 225; cd 225; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 2250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_002;");
  strcat(string, "mkdir 200; cd 200; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 2000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_002;");
  strcat(string, "mkdir 175; cd 175; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 1750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_002;");
  strcat(string, "mkdir 150; cd 150; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 1500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_002;");
  strcat(string, "mkdir 125; cd 125; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 1250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_002;");
  strcat(string, "mkdir 100; cd 100; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.002 1000.0");
  system(string);
  
  // 50 ppm CO2, 4.74 wt% H2O
  strcpy(string, "cd Bishop_runs; mkdir LBT-pum+1_005; cd LBT-pum+1_005;");
  strcat(string, "mkdir 400; cd 400; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 4000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_005;");
  strcat(string, "mkdir 375; cd 375; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 3750.0");
  system(string);

  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_005;");
  strcat(string, "mkdir 350; cd 350; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 3500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_005;");
  strcat(string, "mkdir 325; cd 325; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 3250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_005;");
  strcat(string, "mkdir 300; cd 300; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 3000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_005;");
  strcat(string, "mkdir 275; cd 275; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 2750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_005;");
  strcat(string, "mkdir 250; cd 250; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 2500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_005;");
  strcat(string, "mkdir 225; cd 225; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 2250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_005;");
  strcat(string, "mkdir 200; cd 200; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 2000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_005;");
  strcat(string, "mkdir 175; cd 175; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 1750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_005;");
  strcat(string, "mkdir 150; cd 150; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 1500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_005;");
  strcat(string, "mkdir 125; cd 125; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 1250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_005;");
  strcat(string, "mkdir 100; cd 100; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.005 1000.0");
  system(string);
  
  // 100 ppm CO2, 4.74 wt% H2O
  strcpy(string, "cd Bishop_runs; mkdir LBT-pum+1_010; cd LBT-pum+1_010;");
  strcat(string, "mkdir 400; cd 400; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 4000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_010;");
  strcat(string, "mkdir 375; cd 375; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 3750.0");
  system(string);

  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_010;");
  strcat(string, "mkdir 350; cd 350; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 3500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_010;");
  strcat(string, "mkdir 325; cd 325; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 3250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_010;");
  strcat(string, "mkdir 300; cd 300; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 3000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_010;");
  strcat(string, "mkdir 275; cd 275; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 2750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_010;");
  strcat(string, "mkdir 250; cd 250; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 2500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_010;");
  strcat(string, "mkdir 225; cd 225; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 2250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_010;");
  strcat(string, "mkdir 200; cd 200; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 2000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_010;");
  strcat(string, "mkdir 175; cd 175; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 1750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_010;");
  strcat(string, "mkdir 150; cd 150; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 1500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_010;");
  strcat(string, "mkdir 125; cd 125; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 1250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_010;");
  strcat(string, "mkdir 100; cd 100; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.010 1000.0");
  system(string);
  
  // 200 ppm CO2, 4.74 wt% H2O
  strcpy(string, "cd Bishop_runs; mkdir LBT-pum+1_020; cd LBT-pum+1_020;");
  strcat(string, "mkdir 400; cd 400; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 4000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_020;");
  strcat(string, "mkdir 375; cd 375; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 3750.0");
  system(string);

  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_020;");
  strcat(string, "mkdir 350; cd 350; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 3500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_020;");
  strcat(string, "mkdir 325; cd 325; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 3250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_020;");
  strcat(string, "mkdir 300; cd 300; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 3000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_020;");
  strcat(string, "mkdir 275; cd 275; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 2750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_020;");
  strcat(string, "mkdir 250; cd 250; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 2500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_020;");
  strcat(string, "mkdir 225; cd 225; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 2250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_020;");
  strcat(string, "mkdir 200; cd 200; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 2000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_020;");
  strcat(string, "mkdir 175; cd 175; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 1750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_020;");
  strcat(string, "mkdir 150; cd 150; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 1500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_020;");
  strcat(string, "mkdir 125; cd 125; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 1250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_020;");
  strcat(string, "mkdir 100; cd 100; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.020 1000.0");
  system(string);
  
  // 500 ppm CO2, 4.74 wt% H2O
  strcpy(string, "cd Bishop_runs; mkdir LBT-pum+1_050; cd LBT-pum+1_050;");
  strcat(string, "mkdir 400; cd 400; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 4000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_050;");
  strcat(string, "mkdir 375; cd 375; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 3750.0");
  system(string);

  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_050;");
  strcat(string, "mkdir 350; cd 350; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 3500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_050;");
  strcat(string, "mkdir 325; cd 325; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 3250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_050;");
  strcat(string, "mkdir 300; cd 300; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 3000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_050;");
  strcat(string, "mkdir 275; cd 275; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 2750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_050;");
  strcat(string, "mkdir 250; cd 250; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 2500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_050;");
  strcat(string, "mkdir 225; cd 225; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 2250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_050;");
  strcat(string, "mkdir 200; cd 200; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 2000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_050;");
  strcat(string, "mkdir 175; cd 175; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 1750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_050;");
  strcat(string, "mkdir 150; cd 150; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 1500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_050;");
  strcat(string, "mkdir 125; cd 125; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 1250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_050;");
  strcat(string, "mkdir 100; cd 100; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.050 1000.0");
  system(string);
  
  // 1000 ppm CO2, 4.74 wt% H2O
  strcpy(string, "cd Bishop_runs; mkdir LBT-pum+1_100; cd LBT-pum+1_100;");
  strcat(string, "mkdir 400; cd 400; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 4000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_100;");
  strcat(string, "mkdir 375; cd 375; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 3750.0");
  system(string);

  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_100;");
  strcat(string, "mkdir 350; cd 350; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 3500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_100;");
  strcat(string, "mkdir 325; cd 325; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 3250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_100;");
  strcat(string, "mkdir 300; cd 300; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 3000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_100;");
  strcat(string, "mkdir 275; cd 275; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 2750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_100;");
  strcat(string, "mkdir 250; cd 250; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 2500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_100;");
  strcat(string, "mkdir 225; cd 225; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 2250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_100;");
  strcat(string, "mkdir 200; cd 200; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 2000.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_100;");
  strcat(string, "mkdir 175; cd 175; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 1750.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_100;");
  strcat(string, "mkdir 150; cd 150; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 1500.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_100;");
  strcat(string, "mkdir 125; cd 125; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 1250.0");
  system(string);
  
  strcpy(string, "cd Bishop_runs; cd LBT-pum+1_100;");
  strcat(string, "mkdir 100; cd 100; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  strcat(string, "75.51 0.21 13.0 0.0000 1.1000 0.25 0.95 3.35 5.55 4.74 0.100 1000.0");
  system(string);
  
}