#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <unistd.h>
#include <grace_np.h>

static void grace_error_function(const char *msg)
{
  fprintf(stderr, "library message : \"%s\"\n", msg);
}

#define filterBasalts \
    if ((atof(LSiO2) < 45.0)  || (atof(LSiO2) > 55.0)) filter = 0; \
    if ((atof(LALKind) < 1.0) || (atof(LALKind) > 6.0)) filter = 0; 
    
#define filterAndesites \
    if ((atof(LSiO2) < 55.0)  || (atof(LSiO2) > 65.0)) filter = 0; \
    if ((atof(LALKind) < 1.0) || (atof(LALKind) > 7.0)) filter = 0; 
    
#define filterDacitesAndRhyolites \
    if ((atof(LSiO2) < 65.0)  || (atof(LSiO2) > 85.0)) filter = 0; \
    if ((atof(LALKind) < 1.0) || (atof(LALKind) > 10.0)) filter = 0; 
    
#define filterZeroAlkali \
    if (((atof(LALKind) < 0.0) || (atof(LALKind) > 1.0)) && !negateFilterChoice) filter = 0; \
    if (((atof(LALKind) < 0.0) || (atof(LALKind) < 1.0)) &&  negateFilterChoice) filter = 0;
    
#define filterAlbite \
    x = atof(LSiO2); \
    y = (11.82 - 8.27)*(x-48.12)/(68.74 - 48.12) + 8.27; \
    y -= atof(LALKind); \
    if ((fabs(y)  > 0.5) && !negateFilterChoice)  filter = 0; \
    if ((fabs(y) <= 0.5) &&  negateFilterChoice && (atof(LMgO) == 0.0) && (atof(LCaO) == 0.0))  filter = 0; \
    if ((fabs(y) <= 0.5) && ((atof(LMgO) > 0.0) || (atof(LCaO) > 0.0)) && !negateFilterChoice) filter = 0; 
    
#define filterKspar \
    x = atof(LSiO2); \
    y = (16.92 - 16.92*0.70)*(x-64.76*0.70)/(64.76 - 64.76*0.70) + 16.92*0.70; \
    y -= atof(LALKind); \
    if ((fabs(y)  > 0.5) && !negateFilterChoice)  filter = 0; \
    if ((fabs(y) <= 0.5) &&  negateFilterChoice && (atof(LMgO) == 0.0) && (atof(LCaO) == 0.0))  filter = 0; \
    if ((fabs(y) <= 0.5) && ((atof(LMgO) > 0.0) || (atof(LCaO) > 0.0)) && !negateFilterChoice) filter = 0; 
    
#define filterJadeite \
    x = atof(LSiO2); \
    y = (15.33 - 15.33*0.7)*(x-59.45*0.70)/(59.45 - 59.45*0.70) + 15.33*0.7; \
    y -= atof(LALKind); \
    if (fabs(y) > 0.2) filter = 0; \
    
#define filterPressure \
    if (atof(P) > 0.5) filter = 0;
    
#define filterHighAlaklies \
    if (atof(LALKind) < (atof(LSiO2)-30.0)/4.0) filter = 0;
    
int main(int argc, char *argv[])  {
  char *liqListFileName       = "liqList.res";
  char *pureWaterFileName     = "h2oduan.res";
  char *pureCarbonDioxideName = "co2duan.res";
  char *fluidName             = "fluid.res";
  
  FILE *liqList           = fopen(liqListFileName, "r");
  FILE *pureWater         = fopen(pureWaterFileName, "r");
  FILE *pureCarbonDioxide = fopen(pureCarbonDioxideName, "r");
  FILE *fluid             = fopen(fluidName, "r");
  FILE *output;
  
  char buffer[2000];
  int   listOfLEPRn[2000];
  char *listOfAuthors[2000];
  char lastAuthor[2000];
  int liqIndex = 0;
  
  int usePureWater          = 1;
  int usePureCarbonDioxide  = 0;
  int useFluidWater         = 0;
  int useFluidCarbonDioxide = 0;
  
  int onlyBasalts             = 0;
  int onlyAndesites           = 0;
  int onlyDacitesAndRhyolites = 0;
  int onlyZeroAlkalies        = 0;
  int onlyAlbite              = 0;
  int onlyJadeite             = 0;
  int onlyLowPressure         = 0;
  int onlyHighAlkalies        = 0;
  int onlyKspar               = 0;
  
  int useTonXaxis      = 0;
  int usePonXaxis      = 0;
  int useXH2OflOnXaxis = 0;
  int useMuOnYaxis     = 0;
  
  int useMuOnYaxisSiO2onXaxis    = 0;
  int useMuOnYaxisTiO2onXaxis    = 0;
  int useMuOnYaxisAl2O3onXaxis   = 0;
  int useMuOnYaxisFe2O3onXaxis   = 0;
  int useMuOnYaxisFe2SiO4onXaxis = 0;
  int useMuOnYaxisMg2SiO4onXaxis = 0;
  int useMuOnYaxisCaSiO3onXaxis  = 0;
  int useMuOnYaxisNa2SiO3onXaxis = 0;
  int useMuOnYaxisKAlSiO4onXaxis = 0;
  int useMuOnYaxisAlIndexonXaxis = 0;
  
  int useGenericMu = 0;
  
  int negateFilterChoice = 0;
  int colorByT           = 0;
  int outputFile         = 0;
  
  if (argc > 1) {
    if      (!strcmp(argv[1], "H2Opure"))  { usePureWater = 1; usePureCarbonDioxide = 0; useFluidWater = 0; useFluidCarbonDioxide = 0; }
    else if (!strcmp(argv[1], "CO2pure"))  { usePureWater = 0; usePureCarbonDioxide = 1; useFluidWater = 0; useFluidCarbonDioxide = 0; }
    else if (!strcmp(argv[1], "H2Ofluid")) { usePureWater = 0; usePureCarbonDioxide = 0; useFluidWater = 1; useFluidCarbonDioxide = 0; }
    else if (!strcmp(argv[1], "CO2fluid")) { usePureWater = 0; usePureCarbonDioxide = 0; useFluidWater = 0; useFluidCarbonDioxide = 1; }
    else if (!strcmp(argv[1], "H2O"))      { usePureWater = 1; usePureCarbonDioxide = 0; useFluidWater = 1; useFluidCarbonDioxide = 0; }
    else if (!strcmp(argv[1], "CO2"))      { usePureWater = 0; usePureCarbonDioxide = 1; useFluidWater = 0; useFluidCarbonDioxide = 1; }
    else if (!strcmp(argv[1], "All"))      { usePureWater = 1; usePureCarbonDioxide = 1; useFluidWater = 1; useFluidCarbonDioxide = 1; }
    else {
      printf("Unrecognizable command: %s\n", argv[1]);
      exit(0);
    }
    if (argc > 2) {
      if      (!strcmp(argv[2], "basalts"))             { onlyBasalts             = 1; }
      else if (!strcmp(argv[2], "andesites"))           { onlyAndesites           = 1; }
      else if (!strcmp(argv[2], "dacitesAndRhyolites")) { onlyDacitesAndRhyolites = 1; }
      else if (!strcmp(argv[2], "zeroAlkalies"))        { onlyZeroAlkalies        = 1; }
      else if (!strcmp(argv[2], "albite"))              { onlyAlbite              = 1; }
      else if (!strcmp(argv[2], "kspar"))               { onlyKspar               = 1; }
      else if (!strcmp(argv[2], "jadeite"))             { onlyJadeite             = 1; }
      else if (!strcmp(argv[2], "lowP"))                { onlyLowPressure         = 1; }
      else if (!strcmp(argv[2], "highAlkalies"))        { onlyHighAlkalies        = 1; }
      else if (!strcmp(argv[2], "noSimpleLiquids"))     { onlyAlbite              = 1; onlyKspar =1; onlyZeroAlkalies = 1; negateFilterChoice = 1; }
      else {
        printf("Unrecognizable filter: %s.  Command ignored.\n", argv[2]);
      }
      if (argc > 3) {
        if      (!strcmp(argv[3], "plotT"))         useTonXaxis      = 1;
        else if (!strcmp(argv[3], "plotP"))         usePonXaxis      = 1;
        else if (!strcmp(argv[3], "plotXH2Ofl"))    useXH2OflOnXaxis = 1;
        else if (!strcmp(argv[3], "plotMu"))        useMuOnYaxis     = 1;
        else if (!strcmp(argv[3], "plotMuSiO2"))    useMuOnYaxisSiO2onXaxis    = 1;
        else if (!strcmp(argv[3], "plotMuTiO2"))    useMuOnYaxisTiO2onXaxis    = 1;
        else if (!strcmp(argv[3], "plotMuAl2O3"))   useMuOnYaxisAl2O3onXaxis   = 1;
        else if (!strcmp(argv[3], "plotMuFe2O3"))   useMuOnYaxisFe2O3onXaxis   = 1;
        else if (!strcmp(argv[3], "plotMuFe2SiO4")) useMuOnYaxisFe2SiO4onXaxis = 1;
        else if (!strcmp(argv[3], "plotMuMg2SiO4")) useMuOnYaxisMg2SiO4onXaxis = 1;
        else if (!strcmp(argv[3], "plotMuCaSiO3"))  useMuOnYaxisCaSiO3onXaxis  = 1;
        else if (!strcmp(argv[3], "plotMuNa2SiO3")) useMuOnYaxisNa2SiO3onXaxis = 1;
        else if (!strcmp(argv[3], "plotMuKAlSiO4")) useMuOnYaxisKAlSiO4onXaxis = 1;
        else if (!strcmp(argv[3], "plotMuAlIndex")) useMuOnYaxisAlIndexonXaxis = 1;
        if (argc > 4) {
          if      (!strcmp(argv[4], "negate"))     negateFilterChoice = 1;
          else if (!strcmp(argv[4], "colorByT"))   colorByT = 1;
          else if (!strcmp(argv[4], "outputFile")) outputFile = 1;
        }
      }
    } else printf("No filters will be applied.\n");
    
  } else {
    printf("Usage [H2Opure]   [basalts]             [plotT]         [negate]\n");
    printf("      [CO2pure]   [andesites]           [plotP]         [colorByT]\n");
    printf("      [H2Ofluid]  [dacitesAndRhyolites] [plotMu]        [outputFile]\n");
    printf("      [CO2fluid]  [zeroAlkalies]        [plotMuSiO2]\n");
    printf("      [H2O]       [albite]              [plotMuTiO2]\n");
    printf("      [CO2]       [jadeite]             [plotMuAl2O3]\n");
    printf("      [All]       [lowP]                [plotMuFe2O3]\n");
    printf("                  [highAlkalies]        [plotMuFe2SiO4]\n");
    printf("                  [noSimpleLiquids]     [plotMuMg2SiO4]\n");
    printf("                  [kspar]               [plotMuCaSiO3]\n");
    printf("                  [dummy]               [plotMuNa2SiO3]\n");
    printf("                                        [plotMuKAlSiO4]\n");
    printf("                                        [plotMuAlIndex]\n");
    printf("                                        [plotXH2Ofl]\n");
    printf("                                        [dummy]\n");
    exit(0);
  }
  
  useGenericMu = useMuOnYaxis || useMuOnYaxisSiO2onXaxis    || useMuOnYaxisTiO2onXaxis    || useMuOnYaxisAl2O3onXaxis ||
                                 useMuOnYaxisFe2O3onXaxis   || useMuOnYaxisFe2SiO4onXaxis || useMuOnYaxisMg2SiO4onXaxis ||
                                 useMuOnYaxisCaSiO3onXaxis  || useMuOnYaxisNa2SiO3onXaxis || useMuOnYaxisKAlSiO4onXaxis ||
                                 useMuOnYaxisAlIndexonXaxis || useXH2OflOnXaxis;
  
  if (outputFile) output = fopen("output.dat", "w");
  
  int nSet=-1, nColor=-1, nSym = 1;

  while (fgets(buffer, 2000, liqList)) {
    char *LEPRn      = strtok(buffer, "\t");
    if ((atoi(LEPRn) == 0) || (atoi(LEPRn) == 999999)) continue;
    char *LIQn       = strtok(NULL,   "\t");
    char *name       = strtok(NULL,   "\t");
    char *author     = strtok(NULL,   "\t");
    char *device     = strtok(NULL,   "\t");
    char *container  = strtok(NULL,   "\t");
    char *method     = strtok(NULL,   "\t");
    char *T          = strtok(NULL,   "\t");
    char *P          = strtok(NULL,   "\t");
    char *logfO2     = strtok(NULL,   "\t");
    
    //printf("%8.8d %s\n", atoi(LEPRn), author);
    listOfLEPRn[liqIndex] = atoi(LEPRn);
    listOfAuthors[liqIndex] = (char *) malloc((strlen(author)+1)*sizeof(char));
    strcpy(listOfAuthors[liqIndex], author);
    liqIndex++;
  }
 
  GraceRegisterErrorFunction (grace_error_function);

  if(GraceOpen (2048) < 0) { printf("Cannot open pipe to Grace.\n"); exit(0); }
  
  GracePrintf("PAGE SIZE 1824, 960\n");

  GracePrintf("WITH G0\n");
    GracePrintf("VIEW  %lf, %lf, %lf, %lf\n",  0.1,   0.1,  1.5,  0.9);
    if      (useTonXaxis)  {
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n",  500.0, -30.0, 2000.0, 20.0);
      GracePrintf("XAXIS TICK MAJOR 200.00\n");
      GracePrintf("XAXIS TICK MINOR 100.00\n");
      GracePrintf("YAXIS TICK MAJOR 2.00\n");
      GracePrintf("YAXIS TICK MINOR 1.00\n");
    } else if (usePonXaxis)  {
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n",    0.0, -30.0, 1000.0, 20.0);
      GracePrintf("XAXIS TICK MAJOR 100.00\n");
      GracePrintf("XAXIS TICK MINOR  50.00\n");
      GracePrintf("YAXIS TICK MAJOR 2.00\n");
      GracePrintf("YAXIS TICK MINOR 1.00\n");
    } else if (useXH2OflOnXaxis)  {
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n",    0.0, -5.0, 1.0, 5.0);
      GracePrintf("XAXIS TICK MAJOR 0.10\n");
      GracePrintf("XAXIS TICK MINOR 0.05\n");
      GracePrintf("YAXIS TICK MAJOR 2.00\n");
      GracePrintf("YAXIS TICK MINOR 1.00\n");
    } else if (useGenericMu) {
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n",    0.0,  -5.0,    1.0,  5.0);
      GracePrintf("XAXIS TICK MAJOR 0.10\n");
      GracePrintf("XAXIS TICK MINOR 0.05\n");
      GracePrintf("YAXIS TICK MAJOR 2.00\n");
      GracePrintf("YAXIS TICK MINOR 1.00\n");
    } else {
      GracePrintf("WORLD %lf, %lf, %lf, %lf\n",    0.0, -30.0,   30.0, 20.0);
      GracePrintf("XAXIS TICK MAJOR 2.00\n");
      GracePrintf("XAXIS TICK MINOR 1.00\n");
      GracePrintf("YAXIS TICK MAJOR 2.00\n");
      GracePrintf("YAXIS TICK MINOR 1.00\n");
    }

    GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

    if      (useTonXaxis)                                                     GracePrintf("XAXIS LABEL \"T °C\"\n");
    else if (usePonXaxis)                                                     GracePrintf("XAXIS LABEL \"P MPa\"\n");
    else if (useXH2OflOnXaxis)                                                GracePrintf("XAXIS LABEL \"X H2O fluid phase\"\n");
    else if (useMuOnYaxis && (usePureWater || useFluidWater))                 GracePrintf("XAXIS LABEL \"X H2O\"\n");
    else if (useMuOnYaxis && (usePureCarbonDioxide || useFluidCarbonDioxide)) GracePrintf("XAXIS LABEL \"X CO2\"\n");
    else if (useMuOnYaxisSiO2onXaxis)                                         GracePrintf("XAXIS LABEL \"X SiO2\"\n");
    else if (useMuOnYaxisTiO2onXaxis)                                         GracePrintf("XAXIS LABEL \"X TiO2\"\n");
    else if (useMuOnYaxisAl2O3onXaxis)                                        GracePrintf("XAXIS LABEL \"X Al2O3\"\n");
    else if (useMuOnYaxisFe2O3onXaxis)                                        GracePrintf("XAXIS LABEL \"X Fe2O3\"\n");
    else if (useMuOnYaxisFe2SiO4onXaxis)                                      GracePrintf("XAXIS LABEL \"X Fe2SiO4\"\n");
    else if (useMuOnYaxisMg2SiO4onXaxis)                                      GracePrintf("XAXIS LABEL \"X Mg2SiO4\"\n");
    else if (useMuOnYaxisCaSiO3onXaxis)                                       GracePrintf("XAXIS LABEL \"X CaSiO3\"\n");
    else if (useMuOnYaxisNa2SiO3onXaxis)                                      GracePrintf("XAXIS LABEL \"X Na2SiO3\"\n");
    else if (useMuOnYaxisKAlSiO4onXaxis)                                      GracePrintf("XAXIS LABEL \"X KAlSiO4\"\n");
    else if (useMuOnYaxisAlIndexonXaxis)                                      GracePrintf("XAXIS LABEL \"X Al2O3 - X Na2SiO3\"\n");
    else if (usePureWater || useFluidWater)                                   GracePrintf("XAXIS LABEL \"wt H2O\"\n");
    else if (usePureCarbonDioxide || useFluidCarbonDioxide)                   GracePrintf("XAXIS LABEL \"wt CO2\"\n");
    GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("XAXIS LABEL COLOR 1\n");

    GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

    if      (useGenericMu && (usePureWater || useFluidWater))                 GracePrintf("YAXIS LABEL \"residual muH2O\"\n");
    else if (useGenericMu && (usePureCarbonDioxide || useFluidCarbonDioxide)) GracePrintf("YAXIS LABEL \"residual muCO2\"\n");
    else if (usePureWater || useFluidWater)                                   GracePrintf("YAXIS LABEL \"delta H2O\"\n");
    else if (usePureCarbonDioxide || useFluidCarbonDioxide)                   GracePrintf("YAXIS LABEL \"delta CO2\"\n");
    GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
    GracePrintf("YAXIS LABEL COLOR 1\n");
   
    GracePrintf("LEGEND ON\n");
    GracePrintf("LEGEND 1.51, 0.95\n");
    GracePrintf("LEGEND FONT 4\n");
    GracePrintf("LEGEND CHAR SIZE 0.450000\n");
    GracePrintf("LEGEND VGAP 0\n");
    GracePrintf("FRAME ON\n");
 
  lastAuthor[0] = '\0'; 
  
  
  while (usePureWater && fgets(buffer, 2000, pureWater)) {
    double x, y;
    static int nPoint = 0;
  
    char *LEPRn = strtok(buffer, ",");
    if ((atoi(LEPRn) == 0) || (atoi(LEPRn) == 999999)) continue;
    char *T          = strtok(NULL, ",");
    char *P          = strtok(NULL, ",");
    char *logfO2     = strtok(NULL, ",");
    char *Palk       = strtok(NULL, ",");
    char *Mal        = strtok(NULL, ",");
    char *Pal        = strtok(NULL, ",");
    char *LSiO2      = strtok(NULL, ",");
    char *LMgNum     = strtok(NULL, ",");
    char *LALKind    = strtok(NULL, ",");
    char *LMgO       = strtok(NULL, ",");
    char *LCaO       = strtok(NULL, ",");
    char *LH2O       = strtok(NULL, ",");
    char *LCO2       = strtok(NULL, ",");
    char *SFe2SiO5   = strtok(NULL, ",");
    char *SFe2SiO4   = strtok(NULL, ",");
    char *SFe2SiO6   = strtok(NULL, ",");
    char *SH2O       = strtok(NULL, ",");
    char *SSiOH      = strtok(NULL, ",");
    char *SAlOH      = strtok(NULL, ",");
    char *Deph2oduan = strtok(NULL, ",");
    char *Resh2oduan = strtok(NULL, ",");
    char *Afnh2oduan = strtok(NULL, ",");
    char *SiO2       = strtok(NULL, ",");
    char *TiO2       = strtok(NULL, ",");
    char *Al2O3      = strtok(NULL, ",");
    char *Fe2O3      = strtok(NULL, ",");
    char *MgCr2O4    = strtok(NULL, ",");
    char *Fe2SiO4    = strtok(NULL, ",");
    char *Mn2SiO4    = strtok(NULL, ",");
    char *Mg2SiO4    = strtok(NULL, ",");
    char *Ni2SiO4    = strtok(NULL, ",");
    char *Co2SiO4    = strtok(NULL, ",");
    char *CaSiO3     = strtok(NULL, ",");
    char *Na2SiO3    = strtok(NULL, ",");
    char *KAlSiO4    = strtok(NULL, ",");
    char *Ca3P2O8    = strtok(NULL, ",");
    char *CO2        = strtok(NULL, ",");
    char *SO3        = strtok(NULL, ",");
    char *Cl2O       = strtok(NULL, ",");
    char *F2O        = strtok(NULL, ",");
    char *H2O        = strtok(NULL, ",");
    char *iters      = strtok(NULL, ",");
    char *H2Opred    = strtok(NULL, ",");
    
    int filter = 1;
    if (onlyBasalts)             { filterBasalts             }
    if (onlyAndesites)           { filterAndesites           }
    if (onlyDacitesAndRhyolites) { filterDacitesAndRhyolites }
    if (onlyZeroAlkalies)        { filterZeroAlkali          }
    if (onlyAlbite)              { filterAlbite              }
    if (onlyKspar)               { filterKspar               }
    if (onlyJadeite)             { filterJadeite             }
    if (onlyLowPressure)         { filterPressure            }
    if (onlyHighAlkalies)        { filterHighAlaklies        }    
    if(!filter) continue;
    
    int nLEPR = atoi(LEPRn);
    int nLiq = -1;
    for (nLiq=0; nLiq<liqIndex; nLiq++) if (listOfLEPRn[nLiq] == nLEPR) break;
    
    if (strcmp(lastAuthor, listOfAuthors[nLiq])) { 
      nSet++; 
      nColor++; 
      if (nColor > 14) { nColor = 0; nSym++; }
      strcpy(lastAuthor, listOfAuthors[nLiq]);
      nPoint = 0;
      
      GracePrintf("g0.s%1.1d LINESTYLE 0\n",     nSet);
      GracePrintf("g0.s%1.1d COLOR %1.1d\n",     nSet, nColor);
      GracePrintf("g0.s%1.1d SYMBOL %d\n",       nSet, nSym);
      GracePrintf("g0.s%1.1d SYMBOL SIZE 0.5\n", nSet);
      GracePrintf("g0.s%1.1d SYMBOL FILL PATTERN 1\n", nSet);
      GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   nSet, lastAuthor);
      if (colorByT) GracePrintf("g0.s%1.1d TYPE XYCOLOR\n", nSet);
    }
    
    x = atof(LH2O);
    y = atof(H2Opred) - x;
    if (useTonXaxis) x = atof(T);
    if (usePonXaxis) x = atof(P)*1000;
    if (useXH2OflOnXaxis) x = 1.0;
    if      (useMuOnYaxis)               x = atof(H2O);
    else if (useMuOnYaxisSiO2onXaxis)    x = atof(SiO2);
    else if (useMuOnYaxisTiO2onXaxis)    x = atof(TiO2);
    else if (useMuOnYaxisAl2O3onXaxis)   x = atof(Al2O3);
    else if (useMuOnYaxisFe2O3onXaxis)   x = atof(Fe2O3);
    else if (useMuOnYaxisFe2SiO4onXaxis) x = atof(Fe2SiO4);
    else if (useMuOnYaxisMg2SiO4onXaxis) x = atof(Mg2SiO4);
    else if (useMuOnYaxisCaSiO3onXaxis)  x = atof(CaSiO3);
    else if (useMuOnYaxisNa2SiO3onXaxis) x = atof(Na2SiO3);
    else if (useMuOnYaxisKAlSiO4onXaxis) x = atof(KAlSiO4);
    else if (useMuOnYaxisAlIndexonXaxis) x = (2.0*atof(H2O) - atof(SiO2))*atof(SiO2);
    if (useGenericMu) y = atof(Resh2oduan);
    
    GracePrintf("g0.s%2.2d POINT %lf, %lf\n", nSet, x, y);
    if (colorByT) {
      double t = atof(T);
      if      (t < 700.0)  GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 2);
      else if (t < 900.0)  GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 3);
      else if (t < 1100.0) GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 4);
      else if (t < 1300.0) GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 5);
      else                 GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 6); 
    }
    nPoint++;
    if (outputFile) fprintf(output, "%s\t%s\t%s\t%s\t%s\t%s\n", lastAuthor, T, P, LH2O, Deph2oduan, Resh2oduan);

    //printf(" Found H2O residual for %8.8d %s\n", nLEPR, listOfAuthors[nLiq]);
  }
 
   while (usePureCarbonDioxide && fgets(buffer, 2000, pureCarbonDioxide)) {
    double x, y;
    static int nPoint = 0;
  
    char *LEPRn = strtok(buffer, ",");
    if ((atoi(LEPRn) == 0) || (atoi(LEPRn) == 999999)) continue;
    char *T          = strtok(NULL, ",");
    char *P          = strtok(NULL, ",");
    char *logfO2     = strtok(NULL, ",");
    char *Palk       = strtok(NULL, ",");
    char *Mal        = strtok(NULL, ",");
    char *Pal        = strtok(NULL, ",");
    char *LSiO2      = strtok(NULL, ",");
    char *LMgNum     = strtok(NULL, ",");
    char *LALKind    = strtok(NULL, ",");
    char *LMgO       = strtok(NULL, ",");
    char *LCaO       = strtok(NULL, ",");
    char *LH2O       = strtok(NULL, ",");
    char *LCO2       = strtok(NULL, ",");
    char *SFe2SiO5   = strtok(NULL, ",");
    char *SFe2SiO4   = strtok(NULL, ",");
    char *SFe2SiO6   = strtok(NULL, ",");
    char *SH2O       = strtok(NULL, ",");
    char *SSiOH      = strtok(NULL, ",");
    char *SAlOH      = strtok(NULL, ",");
    char *Depco2duan = strtok(NULL, ",");
    char *Resco2duan = strtok(NULL, ",");
    char *Afnco2duan = strtok(NULL, ",");
    char *SiO2       = strtok(NULL, ",");
    char *TiO2       = strtok(NULL, ",");
    char *Al2O3      = strtok(NULL, ",");
    char *Fe2O3      = strtok(NULL, ",");
    char *MgCr2O4    = strtok(NULL, ",");
    char *Fe2SiO4    = strtok(NULL, ",");
    char *Mn2SiO4    = strtok(NULL, ",");
    char *Mg2SiO4    = strtok(NULL, ",");
    char *Ni2SiO4    = strtok(NULL, ",");
    char *Co2SiO4    = strtok(NULL, ",");
    char *CaSiO3     = strtok(NULL, ",");
    char *Na2SiO3    = strtok(NULL, ",");
    char *KAlSiO4    = strtok(NULL, ",");
    char *Ca3P2O8    = strtok(NULL, ",");
    char *CO2        = strtok(NULL, ",");
    char *SO3        = strtok(NULL, ",");
    char *Cl2O       = strtok(NULL, ",");
    char *F2O        = strtok(NULL, ",");
    char *H2O        = strtok(NULL, ",");
    char *iters      = strtok(NULL, ",");
    char *CO2pred    = strtok(NULL, ",");
    
    int filter = 1;
    if (onlyBasalts)             { filterBasalts             }
    if (onlyAndesites)           { filterAndesites           }
    if (onlyDacitesAndRhyolites) { filterDacitesAndRhyolites }
    if (onlyZeroAlkalies)        { filterZeroAlkali          }
    if (onlyAlbite)              { filterAlbite              }
    if (onlyKspar)               { filterKspar               }
    if (onlyJadeite)             { filterJadeite             }
    if (onlyLowPressure)         { filterPressure            }
    if (onlyHighAlkalies)        { filterHighAlaklies        }    
    if(!filter) continue;
    
    int nLEPR = atoi(LEPRn);
    int nLiq = -1;
    for (nLiq=0; nLiq<liqIndex; nLiq++) if (listOfLEPRn[nLiq] == nLEPR) break;
    
    if (strcmp(lastAuthor, listOfAuthors[nLiq])) { 
      nSet++; 
      nColor++; 
      if (nColor > 14) { nColor = 0; nSym++; }
      strcpy(lastAuthor, listOfAuthors[nLiq]);
      nPoint = 0;
      
      GracePrintf("g0.s%1.1d LINESTYLE 0\n",     nSet);
      GracePrintf("g0.s%1.1d COLOR %1.1d\n",     nSet, nColor);
      GracePrintf("g0.s%1.1d SYMBOL %d\n",       nSet, nSym);
      GracePrintf("g0.s%1.1d SYMBOL SIZE 0.5\n", nSet);
      GracePrintf("g0.s%1.1d SYMBOL FILL PATTERN 1\n", nSet);
      GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   nSet, lastAuthor);
      if (colorByT) GracePrintf("g0.s%1.1d TYPE XYCOLOR\n", nSet);
    }
    
    x = atof(LCO2);
    y = atof(CO2pred) - x;
    if(useTonXaxis) x = atof(T);
    if (usePonXaxis) x = atof(P)*1000;
    if (useXH2OflOnXaxis) x = 0.0;
    if (useMuOnYaxis)                    x = atof(CO2);
    else if (useMuOnYaxisSiO2onXaxis)    x = atof(SiO2);
    else if (useMuOnYaxisTiO2onXaxis)    x = atof(TiO2);
    else if (useMuOnYaxisAl2O3onXaxis)   x = atof(Al2O3);
    else if (useMuOnYaxisFe2O3onXaxis)   x = atof(Fe2O3);
    else if (useMuOnYaxisFe2SiO4onXaxis) x = atof(Fe2SiO4);
    else if (useMuOnYaxisMg2SiO4onXaxis) x = atof(Mg2SiO4);
    else if (useMuOnYaxisCaSiO3onXaxis)  x = atof(CaSiO3);
    else if (useMuOnYaxisNa2SiO3onXaxis) x = atof(Na2SiO3);
    else if (useMuOnYaxisKAlSiO4onXaxis) x = atof(KAlSiO4);
    else if (useMuOnYaxisAlIndexonXaxis) x = (2.0*atof(H2O) - atof(SiO2))*atof(SiO2);
    if (useGenericMu) y = atof(Resco2duan);
    
    GracePrintf("g0.s%2.2d POINT %lf, %lf\n", nSet, x, y);
    if (colorByT) {
      double t = atof(T);
      if      (t < 700.0)  GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 2);
      else if (t < 900.0)  GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 3);
      else if (t < 1100.0) GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 4);
      else if (t < 1300.0) GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 5);
      else                 GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 6); 
    }
    nPoint++;
    if (outputFile) fprintf(output, "%s\t%s\t%s\t%s\t%s\t%s\n", lastAuthor, T, P, LCO2, Depco2duan, Resco2duan);

    //printf(" Found H2O residual for %8.8d %s\n", nLEPR, listOfAuthors[nLiq]);
  }

  while ((useFluidWater || useFluidCarbonDioxide) && fgets(buffer, 2000, fluid)) {
    double x, y;
    static int nPoint = 0;
    
    char *LEPRn = strtok(buffer, ",");
    if ((atoi(LEPRn) == 0) || (atoi(LEPRn) == 999999)) continue;
    char *T          = strtok(NULL, ",");
    char *P          = strtok(NULL, ",");
    char *logfO2     = strtok(NULL, ",");
    char *Palk       = strtok(NULL, ",");
    char *Mal        = strtok(NULL, ",");
    char *Pal        = strtok(NULL, ",");
    char *LSiO2      = strtok(NULL, ",");
    char *LMgNum     = strtok(NULL, ",");
    char *LALKind    = strtok(NULL, ",");
    char *LMgO       = strtok(NULL, ",");
    char *LCaO       = strtok(NULL, ",");
    char *LH2O       = strtok(NULL, ",");
    char *LCO2       = strtok(NULL, ",");
    char *SFe2SiO5   = strtok(NULL, ",");
    char *SFe2SiO4   = strtok(NULL, ",");
    char *SFe2SiO6   = strtok(NULL, ",");
    char *SH2O       = strtok(NULL, ",");
    char *SSiOH      = strtok(NULL, ",");
    char *SAlOH      = strtok(NULL, ",");
    char *Xh2oduan   = strtok(NULL, ",");
    char *Deph2oduan = strtok(NULL, ",");
    char *Resh2oduan = strtok(NULL, ",");
    char *Xco2duan   = strtok(NULL, ",");
    char *Depco2duan = strtok(NULL, ",");
    char *Resco2duan = strtok(NULL, ",");
    char *SiO2       = strtok(NULL, ",");
    char *TiO2       = strtok(NULL, ",");
    char *Al2O3      = strtok(NULL, ",");
    char *Fe2O3      = strtok(NULL, ",");
    char *MgCr2O4    = strtok(NULL, ",");
    char *Fe2SiO4    = strtok(NULL, ",");
    char *Mn2SiO4    = strtok(NULL, ",");
    char *Mg2SiO4    = strtok(NULL, ",");
    char *Ni2SiO4    = strtok(NULL, ",");
    char *Co2SiO4    = strtok(NULL, ",");
    char *CaSiO3     = strtok(NULL, ",");
    char *Na2SiO3    = strtok(NULL, ",");
    char *KAlSiO4    = strtok(NULL, ",");
    char *Ca3P2O8    = strtok(NULL, ",");
    char *CO2        = strtok(NULL, ",");
    char *SO3        = strtok(NULL, ",");
    char *Cl2O       = strtok(NULL, ",");
    char *F2O        = strtok(NULL, ",");
    char *H2O        = strtok(NULL, ",");
    char *iters      = strtok(NULL, ",");
    char *H2Opred    = strtok(NULL, ",");
    char *CO2pred    = strtok(NULL, ",");
    
    int filter = 1;
    if (onlyBasalts)             { filterBasalts             }
    if (onlyAndesites)           { filterAndesites           }
    if (onlyDacitesAndRhyolites) { filterDacitesAndRhyolites }
    if (onlyZeroAlkalies)        { filterZeroAlkali          }
    if (onlyAlbite)              { filterAlbite              }
    if (onlyKspar)               { filterKspar               }
    if (onlyJadeite)             { filterJadeite             }
    if (onlyLowPressure)         { filterPressure            }
    if (onlyHighAlkalies)        { filterHighAlaklies        }    
    if(!filter) continue;
    
    int nLEPR = atoi(LEPRn);
    int nLiq = -1;
    for (nLiq=0; nLiq<liqIndex; nLiq++) if (listOfLEPRn[nLiq] == nLEPR) break;
    
    if (strcmp(lastAuthor, listOfAuthors[nLiq])) { 
      nSet++; 
      nColor++; 
      if (nColor > 14) { nColor = 0; nSym++; }
      strcpy(lastAuthor, listOfAuthors[nLiq]);
      nPoint = 0;
      
      GracePrintf("g0.s%1.1d LINESTYLE 0\n",     nSet);
      GracePrintf("g0.s%1.1d COLOR %1.1d\n",     nSet, nColor);
      GracePrintf("g0.s%1.1d SYMBOL %d\n",       nSet, nSym);
      GracePrintf("g0.s%1.1d SYMBOL SIZE 0.5\n", nSet);
      GracePrintf("g0.s%1.1d SYMBOL FILL PATTERN 1\n", nSet);
      GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   nSet, lastAuthor);
      if (colorByT) GracePrintf("g0.s%1.1d TYPE XYCOLOR\n", nSet);
    }
    
    if (useFluidWater) {
      x = atof(LH2O);
      y = atof(H2Opred) - x;
      if (useMuOnYaxis)                    x = atof(H2O);
      else if (useMuOnYaxisSiO2onXaxis)    x = atof(SiO2);
      else if (useMuOnYaxisTiO2onXaxis)    x = atof(TiO2);
      else if (useMuOnYaxisAl2O3onXaxis)   x = atof(Al2O3);
      else if (useMuOnYaxisFe2O3onXaxis)   x = atof(Fe2O3);
      else if (useMuOnYaxisFe2SiO4onXaxis) x = atof(Fe2SiO4);
      else if (useMuOnYaxisMg2SiO4onXaxis) x = atof(Mg2SiO4);
      else if (useMuOnYaxisCaSiO3onXaxis)  x = atof(CaSiO3);
      else if (useMuOnYaxisNa2SiO3onXaxis) x = atof(Na2SiO3);
      else if (useMuOnYaxisKAlSiO4onXaxis) x = atof(KAlSiO4);
      else if (useMuOnYaxisAlIndexonXaxis) x = (2.0*atof(H2O) - atof(SiO2))*atof(SiO2);
      if (useGenericMu) y = atof(Resh2oduan);
    } else if (useFluidCarbonDioxide) {
      x = atof(LCO2);
      y = atof(CO2pred) - x;
      if (useMuOnYaxis)                    x = atof(CO2);
      else if (useMuOnYaxisSiO2onXaxis)    x = atof(SiO2);
      else if (useMuOnYaxisTiO2onXaxis)    x = atof(TiO2);
      else if (useMuOnYaxisAl2O3onXaxis)   x = atof(Al2O3);
      else if (useMuOnYaxisFe2O3onXaxis)   x = atof(Fe2O3);
      else if (useMuOnYaxisFe2SiO4onXaxis) x = atof(Fe2SiO4);
      else if (useMuOnYaxisMg2SiO4onXaxis) x = atof(Mg2SiO4);
      else if (useMuOnYaxisCaSiO3onXaxis)  x = atof(CaSiO3);
      else if (useMuOnYaxisNa2SiO3onXaxis) x = atof(Na2SiO3);
      else if (useMuOnYaxisKAlSiO4onXaxis) x = atof(KAlSiO4);
      else if (useMuOnYaxisAlIndexonXaxis) x = (2.0*atof(H2O) - atof(SiO2))*atof(SiO2);
      if (useGenericMu) y = atof(Resco2duan);
    }
    if (useTonXaxis) x = atof(T);
    if (usePonXaxis) x = atof(P)*1000;
    if (useXH2OflOnXaxis) x = atof(Xh2oduan);
    
    GracePrintf("g0.s%2.2d POINT %lf, %lf\n", nSet, x, y);
    if (colorByT) {
      double t = atof(T);
      if      (t < 700.0)  GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 2);
      else if (t < 900.0)  GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 3);
      else if (t < 1100.0) GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 4);
      else if (t < 1300.0) GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 5);
      else                 GracePrintf("g0.s%2.2d.y1[%d] = %d\n", nSet, nPoint, 6); 
    }
    nPoint++;
    if (outputFile) {
      if (useFluidWater)         fprintf(output, "%s\t%s\t%s\t%s\t%s\t%s\n", lastAuthor, T, P, LH2O, Deph2oduan, Resh2oduan);
      if (useFluidCarbonDioxide) fprintf(output, "%s\t%s\t%s\t%s\t%s\t%s\n", lastAuthor, T, P, LCO2, Depco2duan, Resco2duan);
    }

    //printf(" Found H2O residual for %8.8d %s\n", nLEPR, listOfAuthors[nLiq]);
  }
  
  GracePrintf("g0.s%1.1d LINESTYLE 1\n", nSet+1);
  GracePrintf("g0.s%1.1d COLOR %1.1d\n", nSet+1, 1);
  GracePrintf("g0.s%1.1d SYMBOL %d\n",   nSet+1, 0);
  if (useTonXaxis) {
    GracePrintf("g0.s%2.2d POINT %lf, %lf\n", nSet+1,  500.0, 0.0);
    GracePrintf("g0.s%2.2d POINT %lf, %lf\n", nSet+1, 2000.0, 0.0); 
  } else if (usePonXaxis) {
    GracePrintf("g0.s%2.2d POINT %lf, %lf\n", nSet+1,    0.0, 0.0);
    GracePrintf("g0.s%2.2d POINT %lf, %lf\n", nSet+1, 1000.0, 0.0); 
  } else if (useGenericMu) {
    GracePrintf("g0.s%2.2d POINT %lf, %lf\n", nSet+1,  0.0, 0.0);
    GracePrintf("g0.s%2.2d POINT %lf, %lf\n", nSet+1,  1.0, 0.0); 
  } else {
    GracePrintf("g0.s%2.2d POINT %lf, %lf\n", nSet+1,  0.0, 0.0);
    GracePrintf("g0.s%2.2d POINT %lf, %lf\n", nSet+1, 30.0, 0.0); 
  }
  
  if(outputFile) fclose(output);

   return 0;
}