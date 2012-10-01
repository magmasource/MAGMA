#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*ran1.c from Numerical Recipes - This outputs random numbers to gasdev.c*/
#define IA 16807
#define IM 2147483647
#define AM (1.0/IM)
#define IQ 127773
#define IR 2836
#define NTAB 32
#define NDIV (1+(IM-1)/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)
 
float ran1(long *idum) {
    int j;
    long k;
    static long iy=0;
    static long iv[NTAB];
    float temp;
 
    if (*idum <= 0 || !iy) {
        if (-(*idum) < 1) *idum=1;
        else *idum = -(*idum);
        for (j=NTAB+7;j>=0;j--) {
            k=(*idum)/IQ;
            *idum=IA*(*idum-k*IQ)-IR*k;
            if (*idum < 0) *idum += IM;
            if (j < NTAB) iv[j] = *idum;
        }
        iy=iv[0];
    }
    k=(*idum)/IQ;
    *idum=IA*(*idum-k*IQ)-IR*k;
    if (*idum < 0) *idum += IM;
    j=iy/NDIV;
    iy=iv[j];
    iv[j] = *idum;
    if ((temp=AM*iy) > RNMX) return RNMX;
    else return temp;
}
 
#undef IA
#undef IM
#undef AM
#undef IQ
#undef IR
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX
 
/*gasdev.c - This returns pseudorandom numebers along a normal distribution.*/
float gasdev(long *idum) {
    float ran1(long *idum);
    static int iset=0;
    static float gset;
    float fac,rsq,v1,v2;
     
    if  (iset == 0) {
        do {
            v1=2.0*ran1(idum)-1.0;
            v2=2.0*ran1(idum)-1.0;
            rsq=v1*v1+v2*v2;
        }
        while (rsq >= 1.0 || rsq == 0.0);
        fac=sqrt(-2.0*log(rsq)/rsq);
        gset=v1*fac;
        iset=1;
        return v2*fac;
    } else {
        iset=0;
        return gset;
    }
}
                         
int main (int argc, char *argv[]) {
  /* these are the EMP data: Label1, SiO2, Al2O3, FeO, MgO, CaO, Na2O, K2O */
  double data[7] = { 77.28, 12.68, 0.7, 0.02, 0.45, 3.87, 4.99 };
  char *string = (char *) malloc(500*sizeof(char));
  char dirName[100];
  char dataString[100];
  int i;
  long idum = -1;
  
  system("rm -rf ERROR-RUNS");
  system("mkdir ERROR-RUNS");
  
  for (i=0; i<1000; i++) {
  
  double err[7];
  
  err[0] = gasdev(&idum)*0.7;
  err[1] = gasdev(&idum)*0.4;
  err[2] = gasdev(&idum)*0.03;
  err[3] = gasdev(&idum)*0.01;
  err[4] = gasdev(&idum)*0.01;
  err[5] = gasdev(&idum)*0.49;
  err[6] = gasdev(&idum)*0.24;
  
  printf("SiO2  = %6.2f +/- %6.2f\n", data[0], err[0]);
  printf("Al2O3 = %6.2f +/- %6.2f\n", data[1], err[1]);
  printf("FeO   = %6.2f +/- %6.2f\n", data[2], err[2]);
  printf("MgO   = %6.2f +/- %6.2f\n", data[3], err[3]);
  printf("CaO   = %6.2f +/- %6.2f\n", data[4], err[4]);
  printf("Na2O  = %6.2f +/- %6.2f\n", data[5], err[5]);
  printf("K2O   = %6.2f +/- %6.2f\n", data[6], err[6]);
  
  strcpy(string, "cd ERROR-RUNS; mkdir ");  
  sprintf(dirName, "16-Lu-2-case%d", i);
  strcat(string, dirName);
  strcat(string, "; cd ");
  strcat(string, dirName);
  strcat(string, "; mkdir 90; cd 90; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");  
  sprintf(dataString, "%f", data[0]+err[0]);
  strcat(string, dataString);  /* SiO2  */
  strcat(string, " 0.0 ");  /* TiO2  */
  sprintf(dataString, "%f", data[1]+err[1]);
  strcat(string, dataString);  /* Al2O3 */
  strcat(string, " ");
  sprintf(dataString, "%f", data[2]+err[2]);
  strcat(string, dataString);  /* FeO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[3]+err[3]);
  strcat(string, dataString);  /* MgO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[4]+err[4]);
  strcat(string, dataString);  /* CaO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[5]+err[5]);
  strcat(string, dataString);  /* Na2O  */
  strcat(string, " ");
  sprintf(dataString, "%f", data[6]+err[6]);
  strcat(string, dataString);  /* K2O   */
  strcat(string, " 900.0");
  system(string);
  
  strcpy(string, "cd ERROR-RUNS; cd ");
  strcat(string, dirName);
  strcat(string, "; mkdir 80; cd 80; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  sprintf(dataString, "%f", data[0]+err[0]);
  strcat(string, dataString);  /* SiO2  */
  strcat(string, " 0.0 ");  /* TiO2  */
  sprintf(dataString, "%f", data[1]+err[1]);
  strcat(string, dataString);  /* Al2O3 */
  strcat(string, " ");
  sprintf(dataString, "%f", data[2]+err[2]);
  strcat(string, dataString);  /* FeO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[3]+err[3]);
  strcat(string, dataString);  /* MgO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[4]+err[4]);
  strcat(string, dataString);  /* CaO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[5]+err[5]);
  strcat(string, dataString);  /* Na2O  */
  strcat(string, " ");
  sprintf(dataString, "%f", data[6]+err[6]);
  strcat(string, dataString);  /* K2O   */
  strcat(string, " 800.0");
  system(string);
  
  strcpy(string, "cd ERROR-RUNS; cd ");
  strcat(string, dirName);
  strcat(string, "; mkdir 70; cd 70; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  sprintf(dataString, "%f", data[0]+err[0]);
  strcat(string, dataString);  /* SiO2  */
  strcat(string, " 0.0 ");  /* TiO2  */
  sprintf(dataString, "%f", data[1]+err[1]);
  strcat(string, dataString);  /* Al2O3 */
  strcat(string, " ");
  sprintf(dataString, "%f", data[2]+err[2]);
  strcat(string, dataString);  /* FeO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[3]+err[3]);
  strcat(string, dataString);  /* MgO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[4]+err[4]);
  strcat(string, dataString);  /* CaO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[5]+err[5]);
  strcat(string, dataString);  /* Na2O  */
  strcat(string, " ");
  sprintf(dataString, "%f", data[6]+err[6]);
  strcat(string, dataString);  /* K2O   */
  strcat(string, " 700.0");
  system(string);

  strcpy(string, "cd ERROR-RUNS; cd ");
  strcat(string, dirName);
  strcat(string, "; mkdir 60; cd 60; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  sprintf(dataString, "%f", data[0]+err[0]);
  strcat(string, dataString);  /* SiO2  */
  strcat(string, " 0.0 ");  /* TiO2  */
  sprintf(dataString, "%f", data[1]+err[1]);
  strcat(string, dataString);  /* Al2O3 */
  strcat(string, " ");
  sprintf(dataString, "%f", data[2]+err[2]);
  strcat(string, dataString);  /* FeO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[3]+err[3]);
  strcat(string, dataString);  /* MgO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[4]+err[4]);
  strcat(string, dataString);  /* CaO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[5]+err[5]);
  strcat(string, dataString);  /* Na2O  */
  strcat(string, " ");
  sprintf(dataString, "%f", data[6]+err[6]);
  strcat(string, dataString);  /* K2O   */
  strcat(string, " 600.0");
  system(string);

  strcpy(string, "cd ERROR-RUNS; cd ");
  strcat(string, dirName);
  strcat(string, "; mkdir 50; cd 50; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  sprintf(dataString, "%f", data[0]+err[0]);
  strcat(string, dataString);  /* SiO2  */
  strcat(string, " 0.0 ");  /* TiO2  */
  sprintf(dataString, "%f", data[1]+err[1]);
  strcat(string, dataString);  /* Al2O3 */
  strcat(string, " ");
  sprintf(dataString, "%f", data[2]+err[2]);
  strcat(string, dataString);  /* FeO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[3]+err[3]);
  strcat(string, dataString);  /* MgO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[4]+err[4]);
  strcat(string, dataString);  /* CaO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[5]+err[5]);
  strcat(string, dataString);  /* Na2O  */
  strcat(string, " ");
  sprintf(dataString, "%f", data[6]+err[6]);
  strcat(string, dataString);  /* K2O   */
  strcat(string, " 500.0");
  system(string);

  strcpy(string, "cd ERROR-RUNS; cd ");
  strcat(string, dirName);
  strcat(string, "; mkdir 40; cd 40; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  sprintf(dataString, "%f", data[0]+err[0]);
  strcat(string, dataString);  /* SiO2  */
  strcat(string, " 0.0 ");  /* TiO2  */
  sprintf(dataString, "%f", data[1]+err[1]);
  strcat(string, dataString);  /* Al2O3 */
  strcat(string, " ");
  sprintf(dataString, "%f", data[2]+err[2]);
  strcat(string, dataString);  /* FeO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[3]+err[3]);
  strcat(string, dataString);  /* MgO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[4]+err[4]);
  strcat(string, dataString);  /* CaO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[5]+err[5]);
  strcat(string, dataString);  /* Na2O  */
  strcat(string, " ");
  sprintf(dataString, "%f", data[6]+err[6]);
  strcat(string, dataString);  /* K2O   */
  strcat(string, " 400.0");
  system(string);

  strcpy(string, "cd ERROR-RUNS; cd ");
  strcat(string, dirName);
  strcat(string, "; mkdir 30; cd 30; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  sprintf(dataString, "%f", data[0]+err[0]);
  strcat(string, dataString);  /* SiO2  */
  strcat(string, " 0.0 ");  /* TiO2  */
  sprintf(dataString, "%f", data[1]+err[1]);
  strcat(string, dataString);  /* Al2O3 */
  strcat(string, " ");
  sprintf(dataString, "%f", data[2]+err[2]);
  strcat(string, dataString);  /* FeO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[3]+err[3]);
  strcat(string, dataString);  /* MgO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[4]+err[4]);
  strcat(string, dataString);  /* CaO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[5]+err[5]);
  strcat(string, dataString);  /* Na2O  */
  strcat(string, " ");
  sprintf(dataString, "%f", data[6]+err[6]);
  strcat(string, dataString);  /* K2O   */
  strcat(string, " 300.0");
  system(string);

  strcpy(string, "cd ERROR-RUNS; cd ");
  strcat(string, dirName);
  strcat(string, "; mkdir 20; cd 20; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  sprintf(dataString, "%f", data[0]+err[0]);
  strcat(string, dataString);  /* SiO2  */
  strcat(string, " 0.0 ");  /* TiO2  */
  sprintf(dataString, "%f", data[1]+err[1]);
  strcat(string, dataString);  /* Al2O3 */
  strcat(string, " ");
  sprintf(dataString, "%f", data[2]+err[2]);
  strcat(string, dataString);  /* FeO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[3]+err[3]);
  strcat(string, dataString);  /* MgO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[4]+err[4]);
  strcat(string, dataString);  /* CaO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[5]+err[5]);
  strcat(string, dataString);  /* Na2O  */
  strcat(string, " ");
  sprintf(dataString, "%f", data[6]+err[6]);
  strcat(string, dataString);  /* K2O   */
  strcat(string, " 200.0");
  system(string);

  strcpy(string, "cd ERROR-RUNS; cd ");
  strcat(string, dirName);
  strcat(string, "; mkdir 10; cd 10; ulimit -t 10; /Users/ghiorso/Documents/ARCHIVE_CODE/xMelts/Test_commandLib ");
  sprintf(dataString, "%f", data[0]+err[0]);
  strcat(string, dataString);  /* SiO2  */
  strcat(string, " 0.0 ");  /* TiO2  */
  sprintf(dataString, "%f", data[1]+err[1]);
  strcat(string, dataString);  /* Al2O3 */
  strcat(string, " ");
  sprintf(dataString, "%f", data[2]+err[2]);
  strcat(string, dataString);  /* FeO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[3]+err[3]);
  strcat(string, dataString);  /* MgO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[4]+err[4]);
  strcat(string, dataString);  /* CaO   */
  strcat(string, " ");
  sprintf(dataString, "%f", data[5]+err[5]);
  strcat(string, dataString);  /* Na2O  */
  strcat(string, " ");
  sprintf(dataString, "%f", data[6]+err[6]);
  strcat(string, dataString);  /* K2O   */
  strcat(string, " 100.0");
  system(string);
  
  }

}