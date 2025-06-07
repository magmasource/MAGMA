const char *analyze_fusion_ver(void) { return "$Id: analyze-fusion.c,v 1.4 2009/04/16 16:35:22 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: analyze-fusion.c,v $
MELTS Source Code: RCS Revision 1.3  2007/06/08 17:25:42  ghiorso
MELTS Source Code: RCS Added code to allow regression of Ghiorso EOS parameters
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2006/08/17 16:47:18  ghiorso
MELTS Source Code: RCS Made modifications to protect strings.  These modifications allow removal
MELTS Source Code: RCS of the flag -fwritable-strings during gcc compilation.  This brings the
MELTS Source Code: RCS code up to gcc 4.x standards.
MELTS Source Code: RCS
MELTS Source Code: RCS Other minor rearrangements and cleanup.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:35  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2005/01/24 03:38:04  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added new files and modifications to perform builds for MgO-SiO2 system
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2003/04/28 20:44:46  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2002/07/22 19:52:05  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2002/04/11 21:39:07  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Test routine to evaluate the function gibbs (file: ANALYZE-FUSION.C)
**
**--
*/

#include "silmin.h"
#include "recipes.h"

#ifdef BUILD_MGO_SIO2_VERSION
#include "liq_struct_data_MgO_SiO2.h"
#include "sol_struct_data_MgO_SiO2.h"
#include "param_struct_data_MgO_SiO2.h"
#else
#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"
#endif /* BUILD_MGO_SIO2_VERSION */ 

int calculationMode = MODE_DEFAULT;

void *main_window, *silmin_adb, *topLevel, *meltsEnviron;
SilminState *silminState;

#include <unistd.h>
#include <grace_np.h>

static void grace_error_function(const char *msg)
{
  fprintf(stderr, "library message : \"%s\"\n", msg);
}

int main()
{
  struct _fusion {
    const char *name;
    const char *formula;
    double     t;
  } fusion[] = {
/*    {"akermanite",	     "Ca2MgSi2O7",     1727.0 }, */
      {"monalbite",	     "NaAlSi3O8",      1393.0 },
      {"anorthite",	     "CaAl2Si2O8",     1830.0 },
      {"orthoenstatite",     "Mg2Si2O6",       1834.0 },
/*    {"co-olivine",	     "Co2SiO4",        1688.0 }, */
/*    {"cordierite",	     "Mg2Al4Si5O18",   1740.0 }, */
/*    {"corundum",	     "Al2O3",	       2323.0 }, */
/*    {"cristobalite",       "SiO2",	       1999.0 }, */
      {"diopside",	     "CaMgSi2O6",      1670.0 },
      {"fayalite",	     "Fe2SiO4",        1490.0 },
/*    {"fluorphlogopite",    "KMg3AlSi3O10F2", 1670.0 }, */
      {"forsterite",	     "Mg2SiO4",        2174.0 },
/*    {"gehlenite",	     "Ca2Al2SiO7",     1863.0 }, */
/*    {"hematite",	     "Fe2O3",	       1895.0 }, */
/*    {"ilmenite",	     "FeTiO3",         1640.0 }, */
      {"jadeite",	     "NaAlSi2O6",      1100.0 },
/*    {"kalsilite",	     "KAlSiO4",        2023.0 }, */
/*    {"kdisilicate",	     "K2Si2O5",        1309.0 }, */
/*    {"kdisilicate",	     "K2Si2O5",        1318.0 }, */
/*    {"kmsilicate",	     "K2SiO3",         1249.0 }, */
/*    {"larnite",	     "Ca2SiO4",        2403.0 }, */
/*    {"magnetite",	     "Fe3O4",	       1870.0 }, */
/*    {"mgchromite",	     "MgCr2O4",        2673.0 }, */
/*    {"nadisilicate",       "Na2Si2O5",       1147.0 }, */
/*    {"namsilicate",	     "Na2SiO3",        1361.0 }, */
/*    {"namsilicate",	     "Na2SiO3",        1362.0 }, */
/*    {"nepheline",	     "NaAlSiO4",       1750.0 }, */
/*    {"nepheline",	     "NaAlSiO4",       1720.0 }, */
/*    {"ni-olivine",	     "Ni2SiO4",        1923.0 }, */
/*    {"pseudowollastonite", "CaSiO3",         1817.0 }, */
/*    {"pyrope",	     "Mg3Al2Si3O12",   1500.0 }, */
      {"pyrope",	     "Mg3Al2Si3O12",   1570.0 },
      {"betaquartz",	     "SiO2",	       1700.0 },
      {"grossular",          "Ca3Al2Si3O12",   1500.0 },
      {"almandine",          "Fe3Al2Si3O12",   1500.0 },
/*    {"rutile",	     "TiO2",	       1870.0 }, */
      {"sanidine",	     "KAlSi3O8",       1473.0 }
/*    {"sanidine",	     "KAlSi3O8",       1500.0 }, */
/*    {"sphene",	     "CaTiSiO5",       1670.0 }, */
/*    {"spinel",	     "MgAl2O4",        2408.0 }, */
/*    {"tephroite",	     "Mn2SiO4",        1620.0 }, */
/*    {"whitlockite",	     "Ca3(PO4)2",      1943.0 }, */
/*    {"wollastonite",       "CaSiO3",         1770.0 }, */
/*    {"wustite",	     "Fe0.947O",       1652.0 }  */
  };
  int nFus = (sizeof fusion / sizeof(struct _fusion));
  
#define MODEL   0  
#define SINK    1
#define FLOAT   2
#define NEUTRAL 3

#define KOMATIITE  0
#define PERIDOTITE 1
  
  struct _ageeWalker {
    const char *name;
    int material;
    int type;
    double p, t;
    double rho;
    double sio2, al2o3, feo, mgo, cao, total;
  } ageeWalker[] = {
    { "95K/5F*",     KOMATIITE,   SINK,  60000.0, 1805.0, 3.229, 46.48, 6.70, 13.77, 25.40, 6.42, 98.77 },
    { "90K/10F",     KOMATIITE,  FLOAT,  60000.0, 1800.0, 3.220, 46.54, 7.00, 14.11, 23.90, 6.51, 98.06 },
    { "90K/10F*",    KOMATIITE,  FLOAT,  60000.0, 1795.0, 3.239, 43.98, 6.15, 17.84, 24.94, 5.73, 98.65 },
    { "90K/10F",     KOMATIITE,   SINK,  48000.0, 1760.0, 3.167, 44.91, 8.03, 13.98, 24.15, 5.19, 96.26 },
    { "77.5K/22.5F", KOMATIITE,   SINK,  38000.0, 1700.0, 3.200, 42.97, 5.80, 23.19, 21.13, 5.10, 98.19 },
    { "75K/25F",     KOMATIITE,  FLOAT,  38000.0, 1680.0, 3.206, 42.71, 5.32, 21.61, 23.45, 4.96, 98.05 },
    { "72.5K/27.5F", KOMATIITE,  FLOAT,  40000.0, 1690.0, 3.213, 43.68, 5.62, 25.66, 19.87, 5.12, 99.95 },
    { "68K/32F",     KOMATIITE,   SINK,  38000.0, 1660.0, 3.296, 41.95, 5.39, 26.83, 19.17, 4.62, 97.98 },
    { "68K/32F*",    KOMATIITE,   SINK,  34000.0, 1660.0, 3.272, 41.58, 5.28, 28.07, 19.31, 4.45, 98.69 },
    { "65K/35F",     KOMATIITE,  FLOAT,  17000.0, 1550.0, 3.145, 40.96, 5.25, 29.53, 17.79, 4.50, 98.04 },
    { "65K/35F",     KOMATIITE,   SINK,  17000.0, 1545.0, 3.130, 41.88, 5.27, 28.24, 18.46, 4.39, 98.24 },
    { "65K/35F",     KOMATIITE,  FLOAT,  14000.0, 1525.0, 3.135, 40.69, 5.28, 29.68, 17.78, 4.51, 97.94 },
    { "65K/35F",     KOMATIITE,   SINK,  10000.0, 1500.0, 3.092, 41.64, 5.72, 29.71, 16.28, 5.01, 98.36 },
    { "61K/39F",     KOMATIITE,  FLOAT,  26000.0, 1585.0, 3.239, 40.07, 4.76, 30.94, 18.70, 3.75, 98.22 },
    { "61K/39F",     KOMATIITE,   SINK,  22000.0, 1560.0, 3.237, 40.53, 4.85, 30.85, 18.08, 3.83, 98.14 },
    { "50K/50F",     KOMATIITE,  FLOAT,  14000.0, 1460.0, 3.252, 37.92, 4.27, 37.48, 14.12, 3.34, 97.13 },
    { "50K/50F",     KOMATIITE,  FLOAT,  12000.0, 1450.0, 3.227, 38.34, 4.43, 37.78, 13.63, 3.56, 97.74 },
    { "50K/50F",     KOMATIITE,   SINK,  10000.0, 1425.0, 3.235, 38.34, 4.33, 37.48, 13.48, 3.48, 97.11 },
    { "50K/50F",     KOMATIITE,   SINK,  10000.0, 1400.0, 3.242, 38.64, 4.51, 39.23, 12.65, 3.68, 97.71 },
    { "100P*",       PERIDOTITE,  SINK,  60000.0, 1970.0, 3.230, 42.66, 5.19, 12.72, 32.14, 4.30, 97.01 },
    { "100P*",       PERIDOTITE,  SINK,  60000.0, 1970.0, 3.260, 42.66, 5.19, 12.72, 32.14, 4.30, 97.01 },
    { "60P/40F*",    PERIDOTITE, FLOAT,  50000.0, 1810.0, 3.327, 37.93, 3.32, 31.18, 23.21, 2.19, 97.83 },
    { "60P/40F*",    PERIDOTITE, FLOAT,  50000.0, 1810.0, 3.405, 37.93, 3.32, 31.18, 23.21, 2.19, 97.83 },
    { "60P/40F*",    PERIDOTITE, FLOAT,  40000.0, 1770.0, 3.316, 37.54, 2.99, 31.69, 23.91, 2.01, 98.14 },
    { "60P/40F*",    PERIDOTITE, FLOAT,  40000.0, 1770.0, 3.389, 37.54, 2.99, 31.69, 23.91, 2.01, 98.14 },
    { "60P/40F",     PERIDOTITE, FLOAT,  35000.0, 1730.0, 3.315, 37.48, 2.86, 34.07, 23.49, 1.83, 99.73 },
    { "AW93/1/1",    KOMATIITE,  FLOAT,  93000.0, 1900.0, 3.39,  46.47, 5.46,  9.47, 30.39, 5.77, 97.56 },
    { "AW93/1/2",    KOMATIITE,   SINK,  84000.0, 1900.0, 3.34,  45.65, 5.74, 11.18, 28.83, 5.79, 97.19 },
    { "AW93/1/3",    PERIDOTITE, FLOAT, 101000.0, 2000.0, 3.26,  45.66, 3.06,  5.21, 38.38, 2.82, 95.12 },    
    { "AW93/1/4",    PERIDOTITE,  SINK,  97000.0, 2000.0, 3.36,  44.90, 3.85,  5.19, 40.84, 3.11, 97.89 },
    { "AW93/1/5",    PERIDOTITE,  SINK,  95000.0, 2000.0, 3.36,  45.06, 3.96,  5.04, 39.49, 3.34, 96.89 },
    { "AW93/1/6",    PERIDOTITE, FLOAT,  90000.0, 2000.0, 3.23,  44.56, 3.13,  6.86, 39.12, 2.77, 96.44 },
    { "AW93/1/7",    PERIDOTITE, FLOAT,  85000.0, 2000.0, 3.22,  44.64, 3.39,  7.84, 39.10, 2.80, 97.77 },
    { "AW93/1/8",    PERIDOTITE,  SINK,  78000.0, 2000.0, 3.20,  43.28, 3.28,  6.48, 41.27, 2.69, 97.00 },
    { "AW93/1/9",    PERIDOTITE,  SINK,  72000.0, 2000.0, 3.19,  44.56, 4.15,  7.78, 38.36, 3.34, 98.19 }
  };
  int nAW = (sizeof ageeWalker / sizeof(struct _ageeWalker));

  struct _circoneAgee {
    const char *name;
    int type;
    double p, t;
    double rho;
    double sio2, tio2, al2o3, cr2o3, feo, mgo, cao, moo3, total;
  } circoneAgee[] = {
    { "67PC",    FLOAT,  10000.0, 1415.0, 3.22, 34.65, 15.03, 4.71, 0.67, 22.79, 14.00, 6.67, 1.88, 100.41 },
    { "64PC",    FLOAT,  15000.0, 1435.0, 3.23, 34.26, 15.63, 4.74, 0.92, 22.86, 14.38, 6.41, 1.55, 100.75 },
    { "63PC",    FLOAT,  20000.0, 1465.0, 3.25, 33.69, 15.36, 4.73, 0.92, 23.19, 13.88, 6.49, 2.18, 100.43 },
    { "62PC",    FLOAT,  25000.0, 1485.0, 3.26, 34.22, 15.74, 4.77, 1.00, 22.01, 14.84, 6.35, 2.35, 101.27 },
    { "88PC",  NEUTRAL,  15000.0, 1434.0, 3.30, 34.20, 15.23, 4.74, 0.75, 22.73, 14.19, 6.56, 1.84, 100.33 },
    { "84PC",    FLOAT,  20000.0, 1465.0, 3.31, 34.32, 15.40, 4.74, 0.81, 22.64, 14.25, 6.60, 2.00, 100.75 },
    { "301A8",    SINK,  40000.0, 1710.0, 3.62, 34.64, 15.10, 3.81, 0.69, 23.03, 14.29, 6.75, 3.17, 101.47 },
    { "308A8",    SINK,  50000.0, 1775.0, 3.64, 34.44, 14.72, 4.43, 0.83, 22.44, 14.32, 6.64, 3.60, 101.42 },
    { "321A8", NEUTRAL,  55000.0, 1800.0, 3.65, 33.47, 15.09, 4.91, 0.88, 22.30, 13.99, 6.53, 3.84, 101.00 },
    { "310A8",   FLOAT,  60000.0, 1804.0, 3.66, 34.53, 14.61, 3.89, 0.79, 22.04, 14.31, 6.79, 4.30, 101.27 },
    { "401A8", NEUTRAL,  60000.0, 1835.0, 3.66, 34.85, 14.45, 5.13, 0.87, 22.12, 14.43, 6.70, 2.75, 101.30 },
    { "402A8",    SINK,  82000.0, 1965.0, 3.79, 32.72, 15.95, 3.78, 0.76, 23.65, 13.11, 6.54, 3.81, 100.31 },
    { "405A8",    SINK,  85000.0, 1985.0, 3.80, 33.39, 15.38, 4.49, 0.83, 22.69, 13.44, 6.56, 3.74, 100.52 },
    { "410A8",    SINK,  90000.0, 2010.0, 3.81, 34.09, 14.97, 4.85, 0.91, 21.67, 13.90, 6.75, 3.77, 100.91 },
    { "426A8", NEUTRAL, 100000.0, 2055.0, 3.83, 34.27, 14.15, 5.95, 0.93, 21.54, 14.05, 6.49, 3.50, 100.88 },
    { "455A8", NEUTRAL, 115000.0, 2080.0, 3.86, 35.50, 17.20, 4.55, 0.87, 17.71, 14.32, 7.05, 3.40, 100.60 },
    { "397A8",    SINK,  88000.0, 1995.0, 3.85, 33.93, 14.92, 5.08, 0.85, 21.96, 13.80, 6.60, 3.61, 100.74 },
    { "399A8",    SINK,  92000.0, 2010.0, 3.86, 34.05, 14.84, 5.65, 0.84, 20.87, 14.06, 6.44, 3.85, 100.60 },
    { "412A8",    SINK, 100000.0, 2060.0, 3.88, 33.57, 15.08, 4.96, 0.91, 22.00, 13.78, 6.58, 3.88, 100.74 },
    { "390A8",    SINK,  94000.0, 2020.0, 3.95, 33.83, 15.59, 5.20, 0.87, 20.72, 13.78, 6.51, 4.13, 100.63 },
    { "411A8",    SINK, 100000.0, 2075.0, 3.95, 35.06, 15.56, 6.30, 0.93, 17.85, 14.28, 6.86, 3.53, 100.37 }
  };
  int nCA = (sizeof circoneAgee / sizeof(struct _circoneAgee));

  struct _fayalite {
    int type;
    double p, t;
    double rho;
    double sio2, al2o3, feo, mno, total;
  } fayalite[] = {
    { NEUTRAL, 13500.0, 1500.0, 3.856, 29.4, 1.0, 67.5, 0.0,  97.9 },
    { NEUTRAL, 50000.0, 1500.0, 4.150, 28.9, 0.5, 69.4, 0.12, 99.9 },
    { NEUTRAL, 11000.0, 1300.0, 3.875, 29.4, 1.0, 67.5, 0.0,  97.9 },
    { NEUTRAL, 11500.0, 1300.0, 3.876, 29.4, 1.0, 67.5, 0.0,  97.9 },
    { NEUTRAL, 12000.0, 1300.0, 3.877, 29.4, 1.0, 67.5, 0.0,  97.9 },
    { NEUTRAL, 12500.0, 1400.0, 3.867, 29.4, 1.0, 67.5, 0.0,  97.9 },
    { NEUTRAL, 13000.0, 1500.0, 3.857, 29.4, 1.0, 67.5, 0.0,  97.9 },
    { NEUTRAL, 13800.0, 1500.0, 3.859, 29.4, 1.0, 67.5, 0.0,  97.9 },
    { NEUTRAL, 14000.0, 1600.0, 3.848, 29.4, 1.0, 67.5, 0.0,  97.9 },
    { NEUTRAL, 14500.0, 1600.0, 3.849, 29.4, 1.0, 67.5, 0.0,  97.9 },
    { NEUTRAL, 15000.0, 1600.0, 3.850, 29.4, 1.0, 67.5, 0.0,  97.9 },
    { NEUTRAL, 15500.0, 1600.0, 3.851, 29.4, 1.0, 67.5, 0.0,  97.9 }
  };
  int nFayalite = (sizeof fayalite / sizeof(struct _fayalite));
  
  struct _suzuki {
    int type;
    double p, t;
    double rho;
    double sio2, al2o3, feo, mgo, cao;
  } suzuki[] = {
    { NEUTRAL, 205000.0, 2360.0, 3.59, 45.1, 2.8, 10.4, 38.4, 3.4 }, /* PHN1611 */
    { NEUTRAL, 163000.0, 2270.0, 3.56, 41.2, 3.7, 15.1, 33.0, 7.0 }, /* IT8720  */
    { NEUTRAL, 160000.0, 2330.0, 3.55, 42.1, 6.5, 16.0, 30.2, 5.3 }  /* MA      */
  };
  int nSuzuki = (sizeof suzuki / sizeof(struct _suzuki));
  
  struct _miller {
    double t, p;
    double rho;
    double sio2, tio2, al2o3, cr2o3, feo, mgo, cao, na2o, k2o;
  } miller[] = {
    { 1750.0,  50000.0, 3.13, 46.00, 0.40, 8.10, 0.35, 8.50, 27.20, 7.70, 1.00, 0.25 },
    { 1700.0,  58000.0, 3.19, 46.00, 0.40, 8.10, 0.35, 8.50, 27.20, 7.70, 1.00, 0.25 },
    { 1800.0,  71000.0, 3.25, 46.00, 0.40, 8.10, 0.35, 8.50, 27.20, 7.70, 1.00, 0.25 },
    { 1875.0,  88000.0, 3.34, 46.00, 0.40, 8.10, 0.35, 8.50, 27.20, 7.70, 1.00, 0.25 },
    { 1800.0,  97000.0, 3.39, 46.00, 0.40, 8.10, 0.35, 8.50, 27.20, 7.70, 1.00, 0.25 },
    { 2000.0, 128000.0, 3.52, 46.00, 0.40, 8.10, 0.35, 8.50, 27.20, 7.70, 1.00, 0.25 },
    { 2100.0, 142000.0, 3.57, 46.00, 0.40, 8.10, 0.35, 8.50, 27.20, 7.70, 1.00, 0.25 },
    { 2450.0, 155000.0, 3.60, 46.00, 0.40, 8.10, 0.35, 8.50, 27.20, 7.70, 1.00, 0.25 },
    { 2150.0, 177000.0, 3.71, 46.00, 0.40, 8.10, 0.35, 8.50, 27.20, 7.70, 1.00, 0.25 },
    { 2900.0, 240000.0, 3.88, 46.00, 0.40, 8.10, 0.35, 8.50, 27.20, 7.70, 1.00, 0.25 },
    { 3750.0, 277000.0, 3.94, 46.00, 0.40, 8.10, 0.35, 8.50, 27.20, 7.70, 1.00, 0.25 },
    { 4350.0, 357000.0, 4.15, 46.00, 0.40, 8.10, 0.35, 8.50, 27.20, 7.70, 1.00, 0.25 }
  };
  int nMiller = (sizeof miller / sizeof(struct _miller));  
  
  struct _rowan {
    double t, p;
    double rho;
    double sio2, tio2, al2o3, feo, mgo, cao, na2o, k2o;
  } rowan[] = {
    { 1480.0,  27700.0, 3.04, 49.24, 1.25, 15.27, 10.46, 7.73, 12.73, 2.69, 0.09 },
    { 1500.0,  33800.0, 3.19, 49.24, 1.25, 15.27, 10.46, 7.73, 12.73, 2.69, 0.09 },
    { 1530.0,  41000.0, 3.29, 49.24, 1.25, 15.27, 10.46, 7.73, 12.73, 2.69, 0.09 },
    { 1535.0,  41600.0, 3.35, 49.24, 1.25, 15.27, 10.46, 7.73, 12.73, 2.69, 0.09 },
    { 1590.0,  51600.0, 3.23, 49.24, 1.25, 15.27, 10.46, 7.73, 12.73, 2.69, 0.09 },
    { 1650.0,  60800.0, 3.29, 49.24, 1.25, 15.27, 10.46, 7.73, 12.73, 2.69, 0.09 },
    { 1690.0,  65900.0, 3.44, 49.24, 1.25, 15.27, 10.46, 7.73, 12.73, 2.69, 0.09 },
    { 2100.0, 104300.0, 3.70, 49.24, 1.25, 15.27, 10.46, 7.73, 12.73, 2.69, 0.09 },
    { 2820.0, 152900.0, 3.74, 49.24, 1.25, 15.27, 10.46, 7.73, 12.73, 2.69, 0.09 },
    { 3070.0, 167600.0, 3.94, 49.24, 1.25, 15.27, 10.46, 7.73, 12.73, 2.69, 0.09 },
    { 3200.0, 175500.0, 3.93, 49.24, 1.25, 15.27, 10.46, 7.73, 12.73, 2.69, 0.09 },
    { 3730.0, 201400.0, 3.94, 49.24, 1.25, 15.27, 10.46, 7.73, 12.73, 2.69, 0.09 }
  };
  int nRowan = (sizeof rowan / sizeof(struct _rowan));  
  
  struct _anorthite {
    double p, t;
    double rho;
    double sio2, al2o3, cao;
  } anorthite[] = {
    {  92000.0, 2028.0, 3.31, 43.193, 36.649, 20.157 },
    {  96000.0, 2037.0, 3.37, 43.193, 36.649, 20.157 },
    { 124000.0, 2044.0, 3.42, 43.193, 36.649, 20.157 }, 
    { 155000.0, 2064.0, 3.56, 43.193, 36.649, 20.157 }, 
    { 268000.0, 2128.0, 3.99, 43.193, 36.649, 20.157 }, 
    { 349000.0, 2181.0, 4.33, 43.193, 36.649, 20.157 } 
  };
  int nAnorthite = (sizeof anorthite / sizeof(struct _anorthite));
  
  struct _diopside {
    double p, t;
    double rho;
    double sio2, mgo, cao;
  } diopside[] = {
    {  85000.0, 1882.0, 3.13, 55.491, 18.611, 25.896 },
    { 133000.0, 1937.0, 3.38, 55.491, 18.611, 25.896 },
    { 197000.0, 1985.0, 3.59, 55.491, 18.611, 25.896 }, 
    { 318000.0, 2043.0, 3.84, 55.491, 18.611, 25.896 }, 
    { 380000.0, 2076.0, 3.98, 55.491, 18.611, 25.896 } 
  };
  int nDiopside = (sizeof diopside / sizeof(struct _diopside));
  
  int i, j, k, set=0, color=1;
  double t, p, *mLiq, *rLiq, wt[24];
  int Graph_0_Active = 0;
  int Graph_1_Active = 0;
  int Graph_2_Active = 0;
  int Graph_3_Active = 0;

  printf("---> Default calculation mode is xMELTS.  Change this? (y or n): ");
  if (tolower(getchar()) == 'y') {
    getchar();
    printf("     Set calculation mode is MELTS (public release v 3.0.x)? (y or n): ");
    if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE__MELTS; }
    else {
      getchar();
      printf("     Set calculation mode is pMELTS (public release v 4.0.x)? (y or n): ");
      if (tolower(getchar()) == 'y') { getchar(); calculationMode = MODE_pMELTS; }
    }
  } else getchar();
  
  if (calculationMode == MODE_xMELTS) {
    printf("---> Calculation mode is xMELTS (experimental v 5.0.x).\n");
  } else if (calculationMode == MODE__MELTS) {
    printf("---> Calculation mode is MELTS (public release v 3.0.x).\n");
    liquid = meltsLiquid;
    solids = meltsSolids;
    nlc = meltsNlc;
    nls = meltsNls;
    npc = meltsNpc;
  } else if (calculationMode == MODE_pMELTS) {
    printf("---> Calculation mode is pMELTS (public release v 4.0.x).\n");
    liquid = pMeltsLiquid;
    solids = pMeltsSolids;
    nlc = pMeltsNlc;
    nls = pMeltsNls;
    npc = pMeltsNpc;
  }

  printf("Calling function: InitComputeDataStruct().\n");
  InitComputeDataStruct();
  
  mLiq = (double *) malloc((size_t)  nlc*sizeof(double));
  rLiq = (double *) malloc((size_t)  nlc*sizeof(double));

  setModeToMixingLiq(FALSE);

  GraceRegisterErrorFunction (grace_error_function);
  if(GraceOpen (2048) < 0) { printf("Cannot open pipe to Grace.\n"); exit(0); }
  
  /*****************************************************
   * Type out calculated standard state eos parameters *
   *****************************************************/
   
  printf("%20.20s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s\n", "species", "v", "alpha", "c", "dcdt", "d2vdp2", "d3vdp3", "d4vdp4");
  for (i=0; i<nls; i++) {
    if (liquid[i].liq.eos_type == EOS_GHIORSO) {
      printf("%20.20s ", liquid[i].label);
      printf("%13.6e %13.6e %13.6e %13.6e %13.6e %13.6e %13.6e\n", liquid[i].liq.v, liquid[i].liq.eos.Ghiorso.alpha, liquid[i].liq.eos.Ghiorso.c,
        liquid[i].liq.eos.Ghiorso.dcdt, liquid[i].liq.eos.Ghiorso.d2vdp2, liquid[i].liq.eos.Ghiorso.d3vdp3, liquid[i].liq.eos.Ghiorso.d4vdp4);
    }
  }

  /*******************************************
   * Agee and Walker 1988; 1993; Miller 1991 *
   *******************************************/

  Graph_0_Active = 1;
  GracePrintf("WITH G0\n");
   GracePrintf("VIEW  %lf, %lf, %lf, %lf\n",  0.1, 0.1, 0.8, 0.9);
   GracePrintf("WORLD %lf, %lf, %lf, %lf\n",  3.0, 3.0, 4.4, 4.4);

   GracePrintf("XAXIS TICK MAJOR 0.10\n");
   GracePrintf("XAXIS TICK MINOR 0.02\n");
   GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

   GracePrintf("XAXIS LABEL \"calc\"\n");
   GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
   GracePrintf("XAXIS LABEL COLOR 2\n");

   GracePrintf("YAXIS TICK MAJOR 0.10\n");
   GracePrintf("YAXIS TICK MINOR 0.02\n");
   GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

   GracePrintf("YAXIS LABEL \"data\"\n");
   GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
   GracePrintf("YAXIS LABEL COLOR 2\n");
   
   GracePrintf("LEGEND ON\n");
   GracePrintf("FRAME ON\n");
    
  GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   MODEL,   "Model");
  GracePrintf("g0.s%1.1d LINESTYLE 1\n",     MODEL);
  GracePrintf("g0.s%1.1d COLOR 1\n",         MODEL); 
  GracePrintf("g0.s%1.1d SYMBOL 2\n",        MODEL);
  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",   MODEL);
  GracePrintf("g0.s%1.1d SYMBOL SIZE 0.5\n", MODEL);
  GracePrintf("g0.s%1.1d SYMBOL COLOR 1\n",  MODEL); 
  
  GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   SINK,    "AW Sink");
  GracePrintf("g0.s%1.1d LINESTYLE 0\n",     SINK);
  GracePrintf("g0.s%1.1d SYMBOL 2\n",        SINK);
  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",   SINK);
  GracePrintf("g0.s%1.1d SYMBOL SIZE 1.0\n", SINK);
  GracePrintf("g0.s%1.1d SYMBOL COLOR 2\n",  SINK); 
	 
  GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   FLOAT,   "AW Float");
  GracePrintf("g0.s%1.1d LINESTYLE 0\n",     FLOAT);
  GracePrintf("g0.s%1.1d SYMBOL 2\n",        FLOAT);
  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",   FLOAT);
  GracePrintf("g0.s%1.1d SYMBOL SIZE 1.0\n", FLOAT);
  GracePrintf("g0.s%1.1d SYMBOL COLOR 3\n",  FLOAT); 
	 
  GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   NEUTRAL, "Miller");
  GracePrintf("g0.s%1.1d LINESTYLE 0\n",     NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL 2\n",        NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",   NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL SIZE 1.0\n", NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL COLOR 4\n",  NEUTRAL); 
	 
  GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   1+NEUTRAL, "Fayalite N");
  GracePrintf("g0.s%1.1d LINESTYLE 0\n",     1+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL 2\n",        1+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",   1+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL SIZE 1.0\n", 1+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL COLOR 5\n",  1+NEUTRAL); 
	 
  GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   4+SINK,    "Circone S");
  GracePrintf("g0.s%1.1d LINESTYLE 0\n",     4+SINK);
  GracePrintf("g0.s%1.1d SYMBOL 2\n",        4+SINK);
  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",   4+SINK);
  GracePrintf("g0.s%1.1d SYMBOL SIZE 1.0\n", 4+SINK);
  GracePrintf("g0.s%1.1d SYMBOL COLOR 6\n",  4+SINK); 
	 
  GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   4+FLOAT,   "Circone F");
  GracePrintf("g0.s%1.1d LINESTYLE 0\n",     4+FLOAT);
  GracePrintf("g0.s%1.1d SYMBOL 2\n",        4+FLOAT);
  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",   4+FLOAT);
  GracePrintf("g0.s%1.1d SYMBOL SIZE 1.0\n", 4+FLOAT);
  GracePrintf("g0.s%1.1d SYMBOL COLOR 7\n",  4+FLOAT); 
	 
  GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   4+NEUTRAL, "Circone N");
  GracePrintf("g0.s%1.1d LINESTYLE 0\n",     4+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL 2\n",        4+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",   4+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL SIZE 1.0\n", 4+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL COLOR 8\n",  4+NEUTRAL); 
	 
  GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   5+NEUTRAL, "Suzuki N");
  GracePrintf("g0.s%1.1d LINESTYLE 0\n",     5+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL 2\n",        5+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",   5+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL SIZE 1.0\n", 5+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL COLOR 9\n",  5+NEUTRAL); 
	 
  GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   6+NEUTRAL, "Rowan N");
  GracePrintf("g0.s%1.1d LINESTYLE 0\n",     6+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL 2\n",        6+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL FILL 1\n",   6+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL SIZE 1.0\n", 6+NEUTRAL);
  GracePrintf("g0.s%1.1d SYMBOL COLOR 10\n", 6+NEUTRAL); 
	 
  GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   7+NEUTRAL, "Anorthite");
  GracePrintf("g0.s%2.2d LINESTYLE 0\n",     7+NEUTRAL);
  GracePrintf("g0.s%2.2d SYMBOL 2\n",        7+NEUTRAL);
  GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",   7+NEUTRAL);
  GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n", 7+NEUTRAL);
  GracePrintf("g0.s%2.2d SYMBOL COLOR 11\n", 7+NEUTRAL); 
	 
  GracePrintf("g0.s%1.1d LEGEND \"%s\"\n",   8+NEUTRAL, "Diopside");
  GracePrintf("g0.s%2.2d LINESTYLE 0\n",     8+NEUTRAL);
  GracePrintf("g0.s%2.2d SYMBOL 2\n",        8+NEUTRAL);
  GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",   8+NEUTRAL);
  GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n", 8+NEUTRAL);
  GracePrintf("g0.s%2.2d SYMBOL COLOR 12\n", 8+NEUTRAL); 
	 
  GracePrintf("g0.s0 POINT %lf, %lf\n", 3.0, 3.0);
  GracePrintf("g0.s0 POINT %lf, %lf\n", 4.4, 4.4);
  GracePrintf("REDRAW\n");

  /* Agee & Walker 1988l 1993 */
  printf("Agee and Walker 1988, 1993\n");
  for (i=0; i<24; i++) wt[i] = 0.0;
  for (k=0; k<nAW; k++) {
    double logfo2, sum, v, xSpecies[nls];
  
    wt[ 0] = ageeWalker[k].sio2;
    wt[ 2] = ageeWalker[k].al2o3;
    wt[ 5] = ageeWalker[k].feo;
    wt[ 7] = ageeWalker[k].mgo;
    wt[10] = ageeWalker[k].cao;
    
    t = ageeWalker[k].t + 273.15;
    p = ageeWalker[k].p;
    
    logfo2 = (-22324.0 + 189.0*p/1000.0 - 1.41*p*p/1000000.0)/t +  4.62; /* COH */
  
    for (i=0; i<nc; i++) wt[i] /= bulkSystem[i].mw;
    conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL,  NULL, NULL, &logfo2);
    
    for (i=0, sum=0.0; i<nlc; i++) { for (j=0, mLiq[i]=0.0; j<nc; j++) mLiq[i] += wt[j]*(bulkSystem[j].oxToLiq)[i]; sum += mLiq[i]; }
    conLiq(SECOND, THIRD, t, p, NULL, mLiq, rLiq, NULL, NULL, NULL, NULL);
    
    vmixLiq (FIRST, t, p, rLiq, &v, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    v *= sum;
    if (calculationMode != MODE_xMELTS) {
      for (i=0; i<nlc; i++) {
        gibbs(t, p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
	v += mLiq[i]*(liquid[i].cur).v;
      }
    }
    
    GracePrintf("g%1.1d.s%1.1d POINT %lf, %lf\n", 0, ageeWalker[k].type, ageeWalker[k].total/(10.0*v), ageeWalker[k].rho);
    GracePrintf("REDRAW\n");
    
    conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);
    printf("t = %g, p = %g", t-273.15, p/1000.0);
    for (i=0; i<nls; i++) if (xSpecies[i] > 0.005) printf(" %s %4.2f", liquid[i].label, xSpecies[i]); 
    printf("\n");
  }
  
  /* Circone and Agee 1996 */
  printf("Circone and Agee 1996\n");
  for (i=0; i<24; i++) wt[i] = 0.0;
  for (k=0; k<nCA; k++) {
    double logfo2, sum, v, sumwt, xSpecies[nls];
  
    wt[ 0] = circoneAgee[k].sio2;
    wt[ 1] = circoneAgee[k].tio2;
    wt[ 2] = circoneAgee[k].al2o3;
    wt[ 4] = circoneAgee[k].cr2o3;
    wt[ 5] = circoneAgee[k].feo;
    wt[ 7] = circoneAgee[k].mgo;
    wt[10] = circoneAgee[k].cao;
    
    t = circoneAgee[k].t + 273.15;
    p = circoneAgee[k].p;
    
    logfo2 = (-22324.0 + 189.0*p/1000.0 - 1.41*p*p/1000000.0)/t +  4.62; /* COH */
  
    for (i=0, sumwt=0.0; i<nc; i++) { sumwt += wt[i]; wt[i] /= bulkSystem[i].mw; }
    conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL,  NULL, NULL, &logfo2);
    
    for (i=0, sum=0.0; i<nlc; i++) { for (j=0, mLiq[i]=0.0; j<nc; j++) mLiq[i] += wt[j]*(bulkSystem[j].oxToLiq)[i]; sum += mLiq[i]; }
    conLiq(SECOND, THIRD, t, p, NULL, mLiq, rLiq, NULL, NULL, NULL, NULL);
    
    vmixLiq (FIRST, t, p, rLiq, &v, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    v *= sum;
    if (calculationMode != MODE_xMELTS) {
      for (i=0; i<nlc; i++) {
        gibbs(t, p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
	v += mLiq[i]*(liquid[i].cur).v;
      }
    }
    
    GracePrintf("g%1.1d.s%1.1d POINT %lf, %lf\n", 0, 4+circoneAgee[k].type, sumwt/(10.0*v), circoneAgee[k].rho);
    GracePrintf("REDRAW\n");
    
    conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);
    printf("t = %g, p = %g", t-273.15, p/1000.0);
    for (i=0; i<nls; i++) if (xSpecies[i] > 0.005) printf(" %s %4.2f", liquid[i].label, xSpecies[i]); 
    printf("\n");
  }  

  /* Suzuki 1995 */
  printf("Suzuki et al. 1995\n");
  for (i=0; i<24; i++) wt[i] = 0.0;
  for (k=0; k<nSuzuki; k++) {
    double logfo2, sum, v, sumwt, xSpecies[nls];
  
    wt[ 0] = suzuki[k].sio2;
    wt[ 2] = suzuki[k].al2o3;
    wt[ 5] = suzuki[k].feo;
    wt[ 7] = suzuki[k].mgo;
    wt[10] = suzuki[k].cao;
    
    t = suzuki[k].t + 273.15;
    p = suzuki[k].p;
    
    logfo2 = (-22324.0 + 189.0*p/1000.0 - 1.41*p*p/1000000.0)/t +  4.62; /* COH */
  
    for (i=0, sumwt=0.0; i<nc; i++) { sumwt += wt[i]; wt[i] /= bulkSystem[i].mw; }
    conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL,  NULL, NULL, &logfo2);
    
    for (i=0, sum=0.0; i<nlc; i++) { for (j=0, mLiq[i]=0.0; j<nc; j++) mLiq[i] += wt[j]*(bulkSystem[j].oxToLiq)[i]; sum += mLiq[i]; }
    conLiq(SECOND, THIRD, t, p, NULL, mLiq, rLiq, NULL, NULL, NULL, NULL);
    
    vmixLiq (FIRST, t, p, rLiq, &v, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    v *= sum;
    if (calculationMode != MODE_xMELTS) {
      for (i=0; i<nlc; i++) {
        gibbs(t, p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
	v += mLiq[i]*(liquid[i].cur).v;
      }
    }
    
    GracePrintf("g%1.1d.s%1.1d POINT %lf, %lf\n", 0, 5+suzuki[k].type, sumwt/(10.0*v), suzuki[k].rho);
    GracePrintf("REDRAW\n");
    
    conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);
    printf("t = %g, p = %g", t-273.15, p/1000.0);
    for (i=0; i<nls; i++) if (xSpecies[i] > 0.005) printf(" %s %4.2f", liquid[i].label, xSpecies[i]); 
    printf("\n");
  }  

  /* Agee 1992a,b */
  printf("Agee 1992a,b\n");
  for (i=0; i<24; i++) wt[i] = 0.0;
  for (k=0; k<nFayalite; k++) {
    double logfo2, sum, v, sumwt, xSpecies[nls];
  
    wt[ 0] = fayalite[k].sio2;
    wt[ 2] = fayalite[k].al2o3;
    wt[ 5] = fayalite[k].feo;
    wt[ 6] = fayalite[k].mno;
    
    t = fayalite[k].t + 273.15;
    p = fayalite[k].p;
    
    logfo2 = (-22324.0 + 189.0*p/1000.0 - 1.41*p*p/1000000.0)/t +  4.62; /* COH */
  
    for (i=0, sumwt=0.0; i<nc; i++) { sumwt += wt[i]; wt[i] /= bulkSystem[i].mw; }
    conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL,  NULL, NULL, &logfo2);
    
    for (i=0, sum=0.0; i<nlc; i++) { for (j=0, mLiq[i]=0.0; j<nc; j++) mLiq[i] += wt[j]*(bulkSystem[j].oxToLiq)[i]; sum += mLiq[i]; }
    conLiq(SECOND, THIRD, t, p, NULL, mLiq, rLiq, NULL, NULL, NULL, NULL);
    
    vmixLiq (FIRST, t, p, rLiq, &v, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    v *= sum;
    if (calculationMode != MODE_xMELTS) {
      for (i=0; i<nlc; i++) {
        gibbs(t, p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
	v += mLiq[i]*(liquid[i].cur).v;
      }
    }
    
    GracePrintf("g%1.1d.s%1.1d POINT %lf, %lf\n", 0, 1+fayalite[k].type, sumwt/(10.0*v), fayalite[k].rho);
    GracePrintf("REDRAW\n");
    
    conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);
    printf("t = %g, p = %g", t-273.15, p/1000.0);
    for (i=0; i<nls; i++) if (xSpecies[i] > 0.005) printf(" %s %4.2f", liquid[i].label, xSpecies[i]); 
    printf("\n");
  }  

  /* Miller et al. 1991 */
  printf("Miller et al. 1991\n");
  for (i=0; i<24; i++) wt[i] = 0.0;
  for (k=0; k<nMiller; k++) {
    double logfo2, sum, v, sumwt, xSpecies[nls];
  
    wt[ 0] = miller[k].sio2;
    wt[ 1] = miller[k].tio2;
    wt[ 2] = miller[k].al2o3;
    wt[ 4] = miller[k].cr2o3;
    wt[ 5] = miller[k].feo;
    wt[ 7] = miller[k].mgo;
    wt[10] = miller[k].cao;
    wt[11] = miller[k].na2o;
    wt[12] = miller[k].k2o;
    
    t = miller[k].t + 273.15;
    p = miller[k].p;
    
    logfo2 = (-22324.0 + 189.0*p/1000.0 - 1.41*p*p/1000000.0)/t +  4.62; /* COH */
  
    for (i=0, sumwt=0.0; i<nc; i++) { sumwt += wt[i]; wt[i] /= bulkSystem[i].mw; }
    conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL,  NULL, NULL, &logfo2);
    
    for (i=0, sum=0.0; i<nlc; i++) { for (j=0, mLiq[i]=0.0; j<nc; j++) mLiq[i] += wt[j]*(bulkSystem[j].oxToLiq)[i]; sum += mLiq[i]; }
    conLiq(SECOND, THIRD, t, p, NULL, mLiq, rLiq, NULL, NULL, NULL, NULL);
    
    vmixLiq (FIRST, t, p, rLiq, &v, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    v *= sum;
    if (calculationMode != MODE_xMELTS) {
      for (i=0; i<nlc; i++) {
        gibbs(t, p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
	v += mLiq[i]*(liquid[i].cur).v;
      }
    }
    
    GracePrintf("g%1.1d.s%1.1d POINT %lf, %lf\n", 0, NEUTRAL, sumwt/(10.0*v), miller[k].rho);
    GracePrintf("REDRAW\n");
    
    conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);
    printf("t = %g, p = %g", t-273.15, p/1000.0);
    for (i=0; i<nls; i++) if (xSpecies[i] > 0.005) printf(" %s %4.2f", liquid[i].label, xSpecies[i]); 
    printf("\n");
  }  

  /* Rowan. 1993 */
  printf("Rowan 1993\n");
  for (i=0; i<24; i++) wt[i] = 0.0;
  for (k=0; k<nRowan; k++) {
    double logfo2, sum, v, sumwt, xSpecies[nls];
  
    wt[ 0] = rowan[k].sio2;
    wt[ 1] = rowan[k].tio2;
    wt[ 2] = rowan[k].al2o3;
    wt[ 5] = rowan[k].feo;
    wt[ 7] = rowan[k].mgo;
    wt[10] = rowan[k].cao;
    wt[11] = rowan[k].na2o;
    wt[12] = rowan[k].k2o;
    
    t = rowan[k].t + 273.15;
    p = rowan[k].p;
    
    logfo2 = (-22324.0 + 189.0*p/1000.0 - 1.41*p*p/1000000.0)/t +  4.62; /* COH */
  
    for (i=0, sumwt=0.0; i<nc; i++) { sumwt += wt[i]; wt[i] /= bulkSystem[i].mw; }
    conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL,  NULL, NULL, &logfo2);
    
    for (i=0, sum=0.0; i<nlc; i++) { for (j=0, mLiq[i]=0.0; j<nc; j++) mLiq[i] += wt[j]*(bulkSystem[j].oxToLiq)[i]; sum += mLiq[i]; }
    conLiq(SECOND, THIRD, t, p, NULL, mLiq, rLiq, NULL, NULL, NULL, NULL);
    
    vmixLiq (FIRST, t, p, rLiq, &v, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    v *= sum;
    if (calculationMode != MODE_xMELTS) {
      for (i=0; i<nlc; i++) {
        gibbs(t, p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
	v += mLiq[i]*(liquid[i].cur).v;
      }
    }
    
    GracePrintf("g%1.1d.s%1.1d POINT %lf, %lf\n", 0, 6+NEUTRAL, sumwt/(10.0*v), rowan[k].rho);
    GracePrintf("REDRAW\n");
    
    conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);
    printf("t = %g, p = %g", t-273.15, p/1000.0);
    for (i=0; i<nls; i++) if (xSpecies[i] > 0.005) printf(" %s %4.2f", liquid[i].label, xSpecies[i]); 
    printf("\n");
  }  

  /* Anorthite */
  printf("Anorthite - Rigden et al. (1989)\n");
  for (i=0; i<24; i++) wt[i] = 0.0;
  for (k=0; k<nAnorthite; k++) {
    double sum, v, sumwt, xSpecies[nls];
  
    wt[ 0] = anorthite[k].sio2;
    wt[ 2] = anorthite[k].al2o3;
    wt[10] = anorthite[k].cao;
    
    t = anorthite[k].t;
    p = anorthite[k].p;
    
    for (i=0, sumwt=0.0; i<nc; i++) { sumwt += wt[i]; wt[i] /= bulkSystem[i].mw; }
    for (i=0, sum=0.0; i<nlc; i++) { for (j=0, mLiq[i]=0.0; j<nc; j++) mLiq[i] += wt[j]*(bulkSystem[j].oxToLiq)[i]; sum += mLiq[i]; }
    conLiq(SECOND, THIRD, t, p, NULL, mLiq, rLiq, NULL, NULL, NULL, NULL);
    
    vmixLiq (FIRST, t, p, rLiq, &v, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    v *= sum;
    if (calculationMode != MODE_xMELTS) {
      for (i=0; i<nlc; i++) {
        gibbs(t, p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
	v += mLiq[i]*(liquid[i].cur).v;
      }
    }
    
    GracePrintf("g%1.1d.s%2.2d POINT %lf, %lf\n", 0, 7+NEUTRAL, sumwt/(10.0*v), anorthite[k].rho);
    GracePrintf("REDRAW\n");
    
    conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);
    printf("t = %g, p = %g", t-273.15, p/1000.0);
    for (i=0; i<nls; i++) if (xSpecies[i] > 0.005) printf(" %s %4.2f", liquid[i].label, xSpecies[i]); 
    printf("\n");
  }  

  /* Diopside */
  printf("Diopside - Rigden et al. (1989)\n");
  for (i=0; i<24; i++) wt[i] = 0.0;
  for (k=0; k<nDiopside; k++) {
    double sum, v, sumwt, xSpecies[nls];
  
    wt[ 0] = diopside[k].sio2;
    wt[ 7] = diopside[k].mgo;
    wt[10] = diopside[k].cao;
    
    t = diopside[k].t;
    p = diopside[k].p;
    
    for (i=0, sumwt=0.0; i<nc; i++) { sumwt += wt[i]; wt[i] /= bulkSystem[i].mw; }
    for (i=0, sum=0.0; i<nlc; i++) { for (j=0, mLiq[i]=0.0; j<nc; j++) mLiq[i] += wt[j]*(bulkSystem[j].oxToLiq)[i]; sum += mLiq[i]; }
    conLiq(SECOND, THIRD, t, p, NULL, mLiq, rLiq, NULL, NULL, NULL, NULL);
    
    vmixLiq (FIRST, t, p, rLiq, &v, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    v *= sum;
    if (calculationMode != MODE_xMELTS) {
      for (i=0; i<nlc; i++) {
        gibbs(t, p, (char *) liquid[i].label, &(liquid[i].ref), &(liquid[i].liq), &(liquid[i].fus), &(liquid[i].cur));
	v += mLiq[i]*(liquid[i].cur).v;
      }
    }
    
    GracePrintf("g%1.1d.s%2.2d POINT %lf, %lf\n", 0, 8+NEUTRAL, sumwt/(10.0*v), diopside[k].rho);
    GracePrintf("REDRAW\n");
    
    conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);
    printf("t = %g, p = %g", t-273.15, p/1000.0);
    for (i=0; i<nls; i++) if (xSpecies[i] > 0.005) printf(" %s %4.2f", liquid[i].label, xSpecies[i]); 
    printf("\n");
  }  

  /***************************************************************************
   Speciation Analysis for Miller Shock Wave data
   ***************************************************************************/
    
  printf("Compute speciation properties Miller shock wave experiments? ");
  if (tolower(getchar()) == 'y') {
    getchar(); 
    
    if (Graph_3_Active) { GracePrintf("KILL G3\n"); Graph_3_Active = 0; }
    if (Graph_2_Active) { GracePrintf("KILL G2\n"); Graph_2_Active = 0; }
    if (Graph_1_Active) { GracePrintf("KILL G1\n"); Graph_1_Active = 0; }
    if (Graph_0_Active) { GracePrintf("KILL G0\n"); Graph_0_Active = 0; }

    Graph_0_Active = 1;
    GracePrintf("G0 TYPE CHART\n");
    GracePrintf("G0 STACKED TRUE\n");

    GracePrintf("WITH G0\n");
 
     GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1,  0.1,              0.8, 0.7);
     GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 1.0,  0.0, (double) nMiller, 1.0);

     GracePrintf("XAXIS TICK MAJOR 2.0\n");
     GracePrintf("XAXIS TICK MINOR 1.0\n");
     GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

     GracePrintf("XAXIS LABEL \"Index\"\n");
     GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
     GracePrintf("XAXIS LABEL COLOR 2\n");

     GracePrintf("YAXIS TICK MAJOR 0.1\n");
     GracePrintf("YAXIS TICK MINOR 0.02\n");
     GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

     GracePrintf("YAXIS LABEL \"X\"\n");
     GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
     GracePrintf("YAXIS LABEL COLOR 2\n");
 
     GracePrintf("LEGEND ON\n");
     GracePrintf("LEGEND 0.8, 0.9\n");
     GracePrintf("LEGEND CHAR SIZE 0.8\n");
 
     for (j=0; j<nls; j++) {
      int color = (int) fmod((double) j, (double) 15);
      GracePrintf("g0.s%2.2d TYPE BAR\n",	         j);
      GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",           j, liquid[j].label);
      GracePrintf("g0.s%2.2d SYMBOL 0\n",	         j);
      GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",      j, color+1);
      GracePrintf("g0.s%2.2d SYMBOL PATTERN 1\n",	 j);
      GracePrintf("g0.s%2.2d SYMBOL FILL COLOR %2.2d\n", j, color+1);
      GracePrintf("g0.s%2.2d SYMBOL FILL PATTERN 1\n",   j);
      GracePrintf("g0.s%2.2d LINE TYPE 1\n",             j);
      GracePrintf("g0.s%2.2d LINE LINESTYLE 0\n",        j);
      GracePrintf("g0.s%2.2d LINE LINEWIDTH 1.0\n",      j);
      GracePrintf("g0.s%2.2d LINE COLOR %2.2d\n",        j, color+1);
      GracePrintf("g0.s%2.2d FILL TYPE 1\n", 	         j);
      GracePrintf("g0.s%2.2d FILL COLOR %2.2d\n",        j, color+1);
      GracePrintf("g0.s%2.2d FILL PATTERN 0\n",          j);
     }   

    Graph_1_Active = 1;
    GracePrintf("WITH G1\n");
 
     GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1,    0.75,              0.8,     0.85);
     GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 1.0, 1000.0,  (double) nMiller,  5000.0);

     GracePrintf("XAXIS TICK MAJOR 2.0\n");
     GracePrintf("XAXIS TICK MINOR 1.0\n");
     GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

     GracePrintf("XAXIS LABEL \"Index\"\n");
     GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
     GracePrintf("XAXIS LABEL COLOR 2\n");

     GracePrintf("YAXIS TICK MAJOR 1000.0\n");
     GracePrintf("YAXIS TICK MINOR  500.0\n");
     GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

     GracePrintf("YAXIS LABEL \"T (C)\"\n");
     GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
     GracePrintf("YAXIS LABEL COLOR 2\n");

    Graph_2_Active = 1;
    GracePrintf("WITH G2\n");
 
     GracePrintf("VIEW  %lf, %lf, %lf, %lf\n", 0.1, 0.85,              0.8,   0.95);
     GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 1.0, 0.0,  (double) nMiller,  40.0);

     GracePrintf("XAXIS TICK MAJOR 2.0\n");
     GracePrintf("XAXIS TICK MINOR 1.0\n");
     GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

     GracePrintf("XAXIS LABEL \"Index\"\n");
     GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
     GracePrintf("XAXIS LABEL COLOR 2\n");

     GracePrintf("YAXIS TICK MAJOR 10.0\n");
     GracePrintf("YAXIS TICK MINOR  5.0\n");
     GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

     GracePrintf("YAXIS LABEL \"P (GPa)\"\n");
     GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
     GracePrintf("YAXIS LABEL COLOR 2\n");
 
    /* Miller et al. 1991 */
    for (i=0; i<24; i++) wt[i] = 0.0;
    for (k=0; k<nMiller; k++) {
      double logfo2, xSpecies[nls];
 
      wt[ 0] = miller[k].sio2;
      wt[ 1] = miller[k].tio2;
      wt[ 2] = miller[k].al2o3;
      wt[ 4] = miller[k].cr2o3;
      wt[ 5] = miller[k].feo;
      wt[ 7] = miller[k].mgo;
      wt[10] = miller[k].cao;
      wt[11] = miller[k].na2o;
      wt[12] = miller[k].k2o;
 
      t = miller[k].t + 273.15;
      p = miller[k].p;
 
      logfo2 = (-22324.0 + 189.0*p/1000.0 - 1.41*p*p/1000000.0)/t +  4.62; /* COH */
 
      for (i=0; i<nc; i++) wt[i] /= bulkSystem[i].mw;
      conLiq(FIRST | SEVENTH, FIRST, t, p, wt, NULL, NULL, NULL,  NULL, NULL, &logfo2);
 
      for (i=0; i<nlc; i++) for (j=0, mLiq[i]=0.0; j<nc; j++) mLiq[i] += wt[j]*(bulkSystem[j].oxToLiq)[i];
      conLiq(SECOND, THIRD, t, p, NULL, mLiq, rLiq, NULL, NULL, NULL, NULL);
      conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);

      for (i=0; i<nls; i++) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", i, (double) k, xSpecies[i]);
      GracePrintf("g1.s%2.2d POINT %lf, %lf\n", 0, (double) k, t-273.15);
      GracePrintf("g2.s%2.2d POINT %lf, %lf\n", 0, (double) k, p/10000.0);
      GracePrintf("REDRAW\n");
    }
  } else getchar();
 
        
  /***************************************************************************
   Speciation Analysis for fusion curve minerals
   ***************************************************************************/
    
  for (i=0; i<nFus; i++) {
    double xSpecies[nls];
    printf("Compute speciation properties for %s?", fusion[i].name);
    if (tolower(getchar()) == 'y') {
      getchar(); 

      if (Graph_3_Active) { GracePrintf("KILL G3\n"); Graph_3_Active = 0; }
      if (Graph_2_Active) { GracePrintf("KILL G2\n"); Graph_2_Active = 0; }
      if (Graph_1_Active) { GracePrintf("KILL G1\n"); Graph_1_Active = 0; }
      if (Graph_0_Active) { GracePrintf("KILL G0\n"); Graph_0_Active = 0; }

      Graph_0_Active = 1;
      GracePrintf("G0 TYPE CHART\n");
      GracePrintf("G0 STACKED TRUE\n");

      GracePrintf("WITH G0\n");
       
       GracePrintf("VIEW  %lf, %lf, %lf, %lf\n",   0.1,  0.1,	0.4,  0.45);
       GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 500.0,  0.0, 3000.0, 1.0);

       GracePrintf("XAXIS TICK MAJOR 500.0\n");
       GracePrintf("XAXIS TICK MINOR 100.0\n");
       GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

       GracePrintf("XAXIS LABEL \"T (C)\"\n");
       GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
       GracePrintf("XAXIS LABEL COLOR 2\n");

       GracePrintf("YAXIS TICK MAJOR 0.1\n");
       GracePrintf("YAXIS TICK MINOR 0.02\n");
       GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

       GracePrintf("YAXIS LABEL \"X\"\n");
       GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
       GracePrintf("YAXIS LABEL COLOR 2\n");
 
       GracePrintf("LEGEND ON\n");
       GracePrintf("LEGEND 0.8, 0.9\n");
       GracePrintf("LEGEND CHAR SIZE 0.8\n");
       
       for (j=0; j<nls; j++) {
        int color = (int) fmod((double) j, (double) 15);
        GracePrintf("g0.s%2.2d TYPE BAR\n",		   j);
        GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",	   j, liquid[j].label);
        GracePrintf("g0.s%2.2d SYMBOL 0\n",		   j);
        GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	   j, color+1);
        GracePrintf("g0.s%2.2d SYMBOL PATTERN 1\n",	   j);
        GracePrintf("g0.s%2.2d SYMBOL FILL COLOR %2.2d\n", j, color+1);
        GracePrintf("g0.s%2.2d SYMBOL FILL PATTERN 1\n",   j);
        GracePrintf("g0.s%2.2d LINE TYPE 1\n",  	   j);
        GracePrintf("g0.s%2.2d LINE LINESTYLE 0\n",	   j);
        GracePrintf("g0.s%2.2d LINE LINEWIDTH 1.0\n",	   j);
        GracePrintf("g0.s%2.2d LINE COLOR %2.2d\n",	   j, color+1);
        GracePrintf("g0.s%2.2d FILL TYPE 1\n",  	   j);
        GracePrintf("g0.s%2.2d FILL COLOR %2.2d\n",	   j, color+1);
        GracePrintf("g0.s%2.2d FILL PATTERN 0\n",	   j);
       }

      Graph_1_Active = 1;
      GracePrintf("G1 TYPE CHART\n");
      GracePrintf("G1 STACKED TRUE\n");

      GracePrintf("WITH G1\n");
       
       GracePrintf("VIEW  %lf, %lf, %lf, %lf\n",   0.5,  0.1,	0.8,  0.45);
       GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 500.0,  0.0, 3000.0, 1.0);

       GracePrintf("XAXIS TICK MAJOR 500.0\n");
       GracePrintf("XAXIS TICK MINOR 100.0\n");
       GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

       GracePrintf("XAXIS LABEL \"T (C)\"\n");
       GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
       GracePrintf("XAXIS LABEL COLOR 2\n");

       GracePrintf("YAXIS TICK MAJOR 0.1\n");
       GracePrintf("YAXIS TICK MINOR 0.02\n");
       GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

       GracePrintf("YAXIS LABEL \"X\"\n");
       GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
       GracePrintf("YAXIS LABEL COLOR 2\n");
 
       for (j=0; j<nls; j++) {
        int color = (int) fmod((double) j, (double) 15);
        GracePrintf("g1.s%2.2d TYPE BAR\n",		   j);
        GracePrintf("g1.s%2.2d SYMBOL 0\n",		   j);
        GracePrintf("g1.s%2.2d SYMBOL COLOR %2.2d\n",	   j, color+1);
        GracePrintf("g1.s%2.2d SYMBOL PATTERN 1\n",	   j);
        GracePrintf("g1.s%2.2d SYMBOL FILL COLOR %2.2d\n", j, color+1);
        GracePrintf("g1.s%2.2d SYMBOL FILL PATTERN 1\n",   j);
        GracePrintf("g1.s%2.2d LINE TYPE 1\n",  	   j);
        GracePrintf("g1.s%2.2d LINE LINESTYLE 0\n",	   j);
        GracePrintf("g1.s%2.2d LINE LINEWIDTH 1.0\n",	   j);
        GracePrintf("g1.s%2.2d LINE COLOR %2.2d\n",	   j, color+1);
        GracePrintf("g1.s%2.2d FILL TYPE 1\n",  	   j);
        GracePrintf("g1.s%2.2d FILL COLOR %2.2d\n",	   j, color+1);
        GracePrintf("g1.s%2.2d FILL PATTERN 0\n",	   j);
       }

      Graph_2_Active = 1;
      GracePrintf("G2 TYPE CHART\n");
      GracePrintf("G2 STACKED TRUE\n");

      GracePrintf("WITH G2\n");
       
       GracePrintf("VIEW  %lf, %lf, %lf, %lf\n",   0.1,  0.55,	0.4,  0.95);
       GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 500.0,  0.0, 3000.0, 1.0);

       GracePrintf("XAXIS TICK MAJOR 500.0\n");
       GracePrintf("XAXIS TICK MINOR 100.0\n");
       GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

       GracePrintf("XAXIS LABEL \"T (C)\"\n");
       GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
       GracePrintf("XAXIS LABEL COLOR 2\n");

       GracePrintf("YAXIS TICK MAJOR 0.1\n");
       GracePrintf("YAXIS TICK MINOR 0.02\n");
       GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

       GracePrintf("YAXIS LABEL \"X\"\n");
       GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
       GracePrintf("YAXIS LABEL COLOR 2\n");
 
       for (j=0; j<nls; j++) {
        int color = (int) fmod((double) j, (double) 15);
        GracePrintf("g2.s%2.2d TYPE BAR\n",		   j);
        GracePrintf("g2.s%2.2d SYMBOL 0\n",		   j);
        GracePrintf("g2.s%2.2d SYMBOL COLOR %2.2d\n",	   j, color+1);
        GracePrintf("g2.s%2.2d SYMBOL PATTERN 1\n",	   j);
        GracePrintf("g2.s%2.2d SYMBOL FILL COLOR %2.2d\n", j, color+1);
        GracePrintf("g2.s%2.2d SYMBOL FILL PATTERN 1\n",   j);
        GracePrintf("g2.s%2.2d LINE TYPE 1\n",  	   j);
        GracePrintf("g2.s%2.2d LINE LINESTYLE 0\n",	   j);
        GracePrintf("g2.s%2.2d LINE LINEWIDTH 1.0\n",	   j);
        GracePrintf("g2.s%2.2d LINE COLOR %2.2d\n",	   j, color+1);
        GracePrintf("g2.s%2.2d FILL TYPE 1\n",  	   j);
        GracePrintf("g2.s%2.2d FILL COLOR %2.2d\n",	   j, color+1);
        GracePrintf("g2.s%2.2d FILL PATTERN 0\n",	   j);
       }

      Graph_3_Active = 1;
      GracePrintf("G3 TYPE CHART\n");
      GracePrintf("G3 STACKED TRUE\n");

      GracePrintf("WITH G3\n");
       
       GracePrintf("VIEW  %lf, %lf, %lf, %lf\n",   0.5,  0.55,	0.8,  0.95);
       GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 500.0,  0.0, 3000.0, 1.0);

       GracePrintf("XAXIS TICK MAJOR 500.0\n");
       GracePrintf("XAXIS TICK MINOR 100.0\n");
       GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

       GracePrintf("XAXIS LABEL \"T (C)\"\n");
       GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
       GracePrintf("XAXIS LABEL COLOR 2\n");

       GracePrintf("YAXIS TICK MAJOR 0.1\n");
       GracePrintf("YAXIS TICK MINOR 0.02\n");
       GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

       GracePrintf("YAXIS LABEL \"X\"\n");
       GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
       GracePrintf("YAXIS LABEL COLOR 2\n");
 
       for (j=0; j<nls; j++) {
        int color = (int) fmod((double) j, (double) 15);
        GracePrintf("g3.s%2.2d TYPE BAR\n",		   j);
        GracePrintf("g3.s%2.2d SYMBOL 0\n",		   j);
        GracePrintf("g3.s%2.2d SYMBOL COLOR %2.2d\n",	   j, color+1);
        GracePrintf("g3.s%2.2d SYMBOL PATTERN 1\n",	   j);
        GracePrintf("g3.s%2.2d SYMBOL FILL COLOR %2.2d\n", j, color+1);
        GracePrintf("g3.s%2.2d SYMBOL FILL PATTERN 1\n",   j);
        GracePrintf("g3.s%2.2d LINE TYPE 1\n",  	   j);
        GracePrintf("g3.s%2.2d LINE LINESTYLE 0\n",	   j);
        GracePrintf("g3.s%2.2d LINE LINEWIDTH 1.0\n",	   j);
        GracePrintf("g3.s%2.2d LINE COLOR %2.2d\n",	   j, color+1);
        GracePrintf("g3.s%2.2d FILL TYPE 1\n",  	   j);
        GracePrintf("g3.s%2.2d FILL COLOR %2.2d\n",	   j, color+1);
        GracePrintf("g3.s%2.2d FILL PATTERN 0\n",	   j);
       }

      p = 1.0;
      
      for (j=0; j<npc; j++) {
  	if ((solids[j].ref).h != 0.0 &&
  	    strcmp(fusion[i].name,    solids[j].label)   == 0 &&
  	    strcmp(fusion[i].formula, solids[j].formula) == 0) {
  	  double sum;

  	  conLiq(SECOND, THIRD, t, p, NULL, solids[j].solToLiq, rLiq, NULL, NULL, NULL, NULL);
  	  for (k=0, sum=0.0; k<nlc; k++) sum += (solids[j].solToLiq)[k];
 
  	  if (testLiq(FIFTH, t, p, 0, 0, NULL, NULL, rLiq, NULL)) {
	  
	    for (t=1000.0; t<3000.0; t+=100) {	    
  	      conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);

  	      for (k=0; k<nls; k++) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", k, t-273.15, xSpecies[k]);
  	      GracePrintf("REDRAW\n");
  	    }
  	  } else printf("--> Generates negative mole fractions.\n");
  	  break;
  	}
      }
            
      p = 50000.0;
      
      for (j=0; j<npc; j++) {
  	if ((solids[j].ref).h != 0.0 &&
  	    strcmp(fusion[i].name,    solids[j].label)   == 0 &&
  	    strcmp(fusion[i].formula, solids[j].formula) == 0) {
  	  double sum;

  	  conLiq(SECOND, THIRD, t, p, NULL, solids[j].solToLiq, rLiq, NULL, NULL, NULL, NULL);
  	  for (k=0, sum=0.0; k<nlc; k++) sum += (solids[j].solToLiq)[k];
 
  	  if (testLiq(FIFTH, t, p, 0, 0, NULL, NULL, rLiq, NULL)) {
	  
	    for (t=1000.0; t<3000.0; t+=100) {	    
  	      conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);

  	      for (k=0; k<nls; k++) GracePrintf("g1.s%2.2d POINT %lf, %lf\n", k, t-273.15, xSpecies[k]);
  	      GracePrintf("REDRAW\n");
  	    }
  	  } else printf("--> Generates negative mole fractions.\n");
  	  break;
  	}
      }
      
      p = 100000.0;
      
      for (j=0; j<npc; j++) {
  	if ((solids[j].ref).h != 0.0 &&
  	    strcmp(fusion[i].name,    solids[j].label)   == 0 &&
  	    strcmp(fusion[i].formula, solids[j].formula) == 0) {
  	  double sum;

  	  conLiq(SECOND, THIRD, t, p, NULL, solids[j].solToLiq, rLiq, NULL, NULL, NULL, NULL);
  	  for (k=0, sum=0.0; k<nlc; k++) sum += (solids[j].solToLiq)[k];
 
  	  if (testLiq(FIFTH, t, p, 0, 0, NULL, NULL, rLiq, NULL)) {
	  
	    for (t=1000.0; t<3000.0; t+=100) {	    
  	      conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);

  	      for (k=0; k<nls; k++) GracePrintf("g2.s%2.2d POINT %lf, %lf\n", k, t-273.15, xSpecies[k]);
  	      GracePrintf("REDRAW\n");
  	    }
  	  } else printf("--> Generates negative mole fractions.\n");
  	  break;
  	}
      }
      
      p = 150000.0;
      
      for (j=0; j<npc; j++) {
  	if ((solids[j].ref).h != 0.0 &&
  	    strcmp(fusion[i].name,    solids[j].label)   == 0 &&
  	    strcmp(fusion[i].formula, solids[j].formula) == 0) {
  	  double sum;

  	  conLiq(SECOND, THIRD, t, p, NULL, solids[j].solToLiq, rLiq, NULL, NULL, NULL, NULL);
  	  for (k=0, sum=0.0; k<nlc; k++) sum += (solids[j].solToLiq)[k];
 
  	  if (testLiq(FIFTH, t, p, 0, 0, NULL, NULL, rLiq, NULL)) {
	  
	    for (t=1000.0; t<3000.0; t+=100) {	    
  	      conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);

  	      for (k=0; k<nls; k++) GracePrintf("g3.s%2.2d POINT %lf, %lf\n", k, t-273.15, xSpecies[k]);
  	      GracePrintf("REDRAW\n");
  	    }
  	  } else printf("--> Generates negative mole fractions.\n");
  	  break;
  	}
      }
      
    } else getchar();
  }  
  
  for (i=0, color=1; i<nFus; i++) {
    printf("Compute fusion properties for %s?", fusion[i].name);
    if (tolower(getchar()) == 'y') {
      getchar(); 

      if (Graph_3_Active) { GracePrintf("KILL G3\n"); Graph_3_Active = 0; }
      if (Graph_2_Active) { GracePrintf("KILL G2\n"); Graph_2_Active = 0; }
      if (Graph_1_Active) { GracePrintf("KILL G1\n"); Graph_1_Active = 0; }
      if (Graph_0_Active) { GracePrintf("KILL G0\n"); Graph_0_Active = 0; }

      Graph_0_Active = 1;
      GracePrintf("WITH G0\n");
       GracePrintf("VIEW  %lf, %lf, %lf, %lf\n",   0.1,  0.1,	0.8, 0.9);
       GracePrintf("WORLD %lf, %lf, %lf, %lf\n", 1500.0, 0.0, 2500.0,  100.0);

       GracePrintf("XAXIS TICK MAJOR 100.0\n");
       GracePrintf("XAXIS TICK MINOR 20.0\n");
       GracePrintf("XAXIS TICKLABEL CHAR SIZE 0.8\n");

       GracePrintf("XAXIS LABEL \"T (C)\"\n");
       GracePrintf("XAXIS LABEL CHAR SIZE 0.8\n");
       GracePrintf("XAXIS LABEL COLOR 2\n");

       GracePrintf("YAXIS TICK MAJOR 10.0\n");
       GracePrintf("YAXIS TICK MINOR 2.0\n");
       GracePrintf("YAXIS TICKLABEL CHAR SIZE 0.8\n");

       GracePrintf("YAXIS LABEL \"P (kbars)\"\n");
       GracePrintf("YAXIS LABEL CHAR SIZE 0.8\n");
       GracePrintf("YAXIS LABEL COLOR 2\n");
 
       GracePrintf("LEGEND ON\n");
 
      set   = 0;
      color = 0; /* white */

      if (strcmp(fusion[i].name, "monalbite")   == 0) {
      
	/* Morse */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Morse");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	for (t=1391.0, p=0.0; p<30.0; t += 25.0) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p = 14.5*(pow(t/1391.0, 5.1)-1.0));
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
 
    	/* Richet 1985 */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Richet");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	for (t=1373.0, p=0.0; p<30.0; t += 25.0) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p = 60.95*(pow(t/1373.0, 2.38)-1.0));
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
    	color++;
 
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "solid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 8\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1185.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1191.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1190.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1200.0,  12.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1210.0,  16.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1230.0,  16.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1225.0,  16.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1230.0,  16.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1250.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1265.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1260.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1310.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1315.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1340.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1350.0,  30.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "liquid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 6\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1200.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1210.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1220.0,  12.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1250.0,  13.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1238.0,  16.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1240.0,  16.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1250.0,  16.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1280.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1300.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1320.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1330.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1340.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1360.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1380.0,  30.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "both");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 2\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1150.0,   3.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1200.0,  12.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1210.0,  12.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1240.0,  16.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
    	color++;
	
      } else if (strcmp(fusion[i].name, "orthoenstatite")   == 0) {
      
    	/* Morse */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Morse");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	for (t=1833.0, p=0.0; p<30.0; t += 25.0) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p = 28.5*(pow(t/1833.0, 5.01)-1.0));
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
 
    	/* Richet 1985 */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Richet");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	for (t=1830.0, p=0.0; p<46.7; t += 25.0) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p = 28.65*(pow(t/1830.0, 5.01)-1.0));
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;
 
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "liquid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 8\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1600.0,   5.4);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1550.0,   6.1);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1625.0,   7.2);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1550.0,   7.4);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1550.0,   8.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1640.0,   8.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1640.0,   9.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1650.0,  10.8);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1675.0,  11.1);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1685.0,  12.6);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1700.0,  14.7);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1725.0,  17.9);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1850.0,  32.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1875.0,  39.5);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "solid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 6\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1625.0,   5.4);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1665.0,   8.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1700.0,  11.1);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1710.0,  12.6);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1725.0,  14.4);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1725.0,  14.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1750.0,  17.9);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1825.0,  25.1);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1875.0,  32.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1900.0,  39.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1950.0,  45.6);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "both");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 2\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1800.0,  25.1);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1950.0,  46.7);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2170.0, 100.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2210.0, 116.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2260.0, 121.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2290.0, 133.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2370.0, 160.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2370.0, 165.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
    	color++;

      } else if (strcmp(fusion[i].name, "diopside")   == 0) {
      
    	/* Morse */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Morse");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	for (t=1665.0, p=0.0; p<30.0; t += 25.0) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p = 23.3*(pow(t/1665.0, 4.64)-1.0));
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
 
    	/* Richet 1985 */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Richet");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	for (t=1670.0, p=0.0; p<50.0; t += 25.0) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p = 34.71*(pow(t/1670.0, 3.40)-1.0));
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;
 
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "liquid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 8\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1450.0,   5.4);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1525.0,  10.8);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1600.0,  17.9);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1650.0,  25.1);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1725.0,  32.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1725.0,  32.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1825.0,  46.7);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1392.0,   0.0001);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1465.0,   5.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1531.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1594.0,  15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1650.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1704.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1754.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1804.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1853.0,  40.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1901.0,  45.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1947.0,  50.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1490.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1500.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1510.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1560.0,  16.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1570.0,  16.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1615.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1625.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1660.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1670.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1710.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1730.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1970.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1970.0, 130.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;
 
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "solid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 6\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1475.0,   5.2);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1550.0,  10.8);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1625.0,  17.9);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1675.0,  25.1);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1700.0,  25.1);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1700.0,  25.1);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1750.0,  32.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1750.0,  32.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1800.0,  39.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1850.0,  46.7);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1392.0,   0.00001);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1465.0,   5.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1527.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1585.0,  15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1637.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1687.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1735.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1779.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1822.0,  40.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1864.0,  45.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1904.0,  50.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1515.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1520.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1580.0,  16.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1585.0,  16.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1635.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1640.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1680.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1693.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1730.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2010.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2010.0,  90.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2010.0, 130.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;
 
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "both");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 2\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1675.0,  25.1);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1775.0,  39.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1940.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1990.0,  80.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2030.0,  90.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2070.0, 100.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2090.0, 110.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2120.0, 120.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2150.0, 130.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2150.0, 140.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2150.0, 150.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
    	color++;

      } else if (strcmp(fusion[i].name, "fayalite")   == 0) {
      
    	/* Morse */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Morse");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	for (t=1478.0, p=0.0; p<60.0; t += 25.0) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p = 34.0*(pow(t/1478.0, 5.4)-1.0));
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "liquid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 8\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1250.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1320.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1380.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1420.0,  40.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1225.0,  17.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1275.0,  17.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1340.0,  28.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1390.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1345.0,  31.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1415.0,  45.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1480.0,  55.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1400.0,  56.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1380.0,  57.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1355.0,  58.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1480.0,  60.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1400.0,  61.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1525.0,  64.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1370.0,  40.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1370.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1345.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1305.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1300.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1300.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1250.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1270.0,  15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1250.0,  15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1250.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1270.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1260.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1230.0,  25.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;
 
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "solid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 6\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1280.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1320.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1400.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1450.0,  40.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1440.0,  44.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1400.0,  28.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1515.0,  55.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1555.0,  58.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1530.0,  60.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1555.0,  60.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1535.0,  62.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1620.0,  64.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1675.0,  64.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1775.0,  64.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1640.0,  48.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1425.0,  40.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1405.0,  40.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1500.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1470.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1400.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1380.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1500.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1450.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1405.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1375.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1400.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1345.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1430.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1400.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1375.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1350.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1330.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1315.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1345.0,  15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1295.0,  15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1430.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1300.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1280.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1320.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1300.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1290.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1395.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1375.0,  30.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;
 
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "both");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 2\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1315.0, 17.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1415.0, 30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1455.0, 45.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1475.0, 45.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1505.0, 58.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1570.0, 69.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1520.0, 71.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1555.0, 73.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1390.0, 40.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1350.0, 30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1330.0, 30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1330.0, 25.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
    	color++;

      } else if (strcmp(fusion[i].name, "forsterite")   == 0) {
      
    	/* Morse */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Morse");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, 2174.0-273.15,  0.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, 2317.1-273.15, 30.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
 
    	/* Richet 1985 */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Richet");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	for (t=2163.0, p=0.0; p<150.0; t += 25.0) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p = 108.33*(pow(t/2163.0, 3.7)-1.0));
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "liquid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 8\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1950.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2030.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2075.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2145.0,  74.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2185.0,  77.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2130.0,  84.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2230.0,  84.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1965.0,  98.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2010.0, 100.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2140.0,  98.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2245.0, 100.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2200.0, 127.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2360.0, 127.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2360.0, 153.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1900.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1950.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2050.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2100.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2125.0,  70.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;
 
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "solid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 6\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2100.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2140.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2155.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2200.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2185.0,  62.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2510.0,  74.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2360.0,  77.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2485.0,  84.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2340.0, 100.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2355.0,  99.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2440.0,  98.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2400.0, 127.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2600.0, 150.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2700.0, 150.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2680.0, 153.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2680.0, 153.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2000.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2125.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2150.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2200.0,  70.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;
 
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "both");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 2\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2250.0,  97.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
    	color++;

      } else if (strcmp(fusion[i].name, "jadeite")   == 0) {
      
    	/* Richet 1988 */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Richet 88");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	for (t=1700.0, p=0.0; p<60.0; t += 25.0) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p = 7.45*(pow(t/970.0, 3.036)-1.0));
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;

    	/* Richet 1985 */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Richet 85");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	for (t=1609.0, p=0.0; p<43.0; t += 25.0) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p = 7.97*(pow(t/1609.0, 8.35)-1.0)+29.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "liquid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 8\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1375.0,  34.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1400.0,  36.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1425.0,  36.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1425.0,  39.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1475.0,  36.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1500.0,  39.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1525.0,  43.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "solid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 6\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1350.0,  28.7);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1450.0,  34.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1550.0,  43.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "both");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 2\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1400.0,  34.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1425.0,  34.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1450.0,  36.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1525.0,  39.5);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
    	color++;

      } else if (strcmp(fusion[i].name, "pyrope")   == 0) {
      
    	/* Richet 1988 */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Richet 88");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	for (t=2025.0, p=0.0; p<100.0; t += 25.0) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p = 14.96*(pow(t/1570.0, 4.757)-1.0));
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;

    	/* Richet 1985 */
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, "Richet 85");
    	GracePrintf("g0.s%2.2d SYMBOL 0\n",	 set);
    	GracePrintf("g0.s%2.2d LINESTYLE 3\n",   set);
    	GracePrintf("g0.s%2.2d LINEWIDTH 2\n",   set);
    	GracePrintf("g0.s%2.2d COLOR %2.2d\n",   set, color);
    	for (t=2073.0, p=0.0; p<100.0; t += 25.0) GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p = 19.79*(pow(t/2073.0, 9.25)-1.0)+40.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "liquid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 8\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1725.0,  35.9);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1750.0,  35.9);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1775.0,  39.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1800.0,  43.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1825.0,  46.7);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1640.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1730.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1795.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1920.0,  62.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1960.0,  62.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2060.0,  77.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1840.0,  78.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2000.0,  78.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2070.0,  78.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2105.0, 100.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1700.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1730.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1800.0,  50.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1850.0,  55.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1900.0,  62.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1950.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1950.0,  75.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1950.0,  80.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1960.0,  85.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2000.0,  90.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2010.0,  95.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	
    	/* Morse */
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 8\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1800.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1830.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1900.0,  15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1980.0,  15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2110.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2210.0,  25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1600.0,   5.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1650.0,   5.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1680.0,   5.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1650.0,   6.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "solid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 6\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1800.0,  35.9);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1800.0,  39.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1825.0,  43.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1850.0,  46.7);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1840.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1885.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1990.0,  47.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2080.0,  59.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2220.0,  72.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2150.0,  76.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2170.0,  78.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2200.0, 100.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1800.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1875.0,  50.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1900.0,  50.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1930.0,  55.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1975.0,  62.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2100.0,  62.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2050.0,  65.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1975.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2000.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2100.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2250.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2350.0,  70.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2000.0,  75.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2100.0,  75.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2200.0,  75.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2050.0,  80.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2150.0,  80.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2250.0,  80.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2350.0,  80.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2050.0,  90.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2200.0,  90.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2075.0,  95.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2250.0,  95.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2075.0, 100.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2150.0, 100.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 6\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1700.0,   5.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1730.0,   5.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1750.0,   5.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1750.0,   7.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1850.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1860.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1870.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1900.0,  10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2000.0,  15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2050.0,  15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2120.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2250.0,  25.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",        set, "both");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 2\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1775.0,  35.9);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1980.0,  62.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2000.0, 100.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1750.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1850.0,  50.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1900.0,  55.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1900.0,  62.5);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2000.0,  80.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2000.0,  85.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2030.0,  90.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2040.0,  95.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
    	color++;

      } else if (strcmp(fusion[i].name, "betaquartz")   == 0) {
        color++;
      
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",	set, "liquid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 8\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1530.0,   7.3);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",	set, "solid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 6\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1575.0,   7.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1575.0,   6.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1600.0,   7.3);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1580.0,   8.7);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",	set, "both");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 2\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1650.0,  6.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1680.0,  6.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1710.0,  7.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1730.0,  7.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1800.0, 10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1820.0, 10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1840.0, 10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1850.0, 10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1880.0, 10.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1980.0, 15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2000.0, 15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2025.0, 15.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2230.0, 25.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1680.0,  3.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2290.0, 30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2350.0, 30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2360.0, 37.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2410.0, 37.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 2440.0, 45.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
    	color++;

      } else if (strcmp(fusion[i].name, "anorthite")   == 0) {
        color++;
	color++;
	color++;
      
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",	set, "both");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 2\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1570.0,  7.3);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
    	color++;

      } else if (strcmp(fusion[i].name, "sanidine")   == 0) {
        color++;
      
    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",	set, "liquid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 8\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1415.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1440.0,  20.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1515.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1530.0,  40.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
	color++;

    	GracePrintf("g0.s%2.2d LEGEND \"%s\"\n",	set, "solid");
    	GracePrintf("g0.s%2.2d LINESTYLE 0\n",  	set);
    	GracePrintf("g0.s%2.2d SYMBOL 6\n",		set);
    	GracePrintf("g0.s%2.2d SYMBOL FILL 1\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL SIZE 1.0\n",	set);
    	GracePrintf("g0.s%2.2d SYMBOL COLOR %2.2d\n",	set, color);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1460.0,  19.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1530.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1570.0,  30.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1575.0,  35.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1550.0,  40.0);
    	GracePrintf("g0.s%2.2d POINT %lf, %lf\n",	set, 1600.0,  40.0);
    	GracePrintf("AUTOSCALE\n");
    	GracePrintf("REDRAW\n");
    	set++;
    	color++;
	color++;
	
      } else { color++; color++; color++; color++; }

      t = fusion[i].t;
      p = 2.0;
      for (j=0; j<npc; j++) {
  	if ((solids[j].ref).h != 0.0 &&
  	    strcmp(fusion[i].name,    solids[j].label)   == 0 &&
  	    strcmp(fusion[i].formula, solids[j].formula) == 0) {
  	  double sum;

  	  conLiq(SECOND, THIRD, t, p, NULL, solids[j].solToLiq, rLiq, NULL, NULL, NULL, NULL);
  	  for (k=0, sum=0.0; k<nlc; k++) sum += (solids[j].solToLiq)[k];
 
  	  if (testLiq(FIFTH, t, p, 0, 0, NULL, NULL, rLiq, NULL)) {
  	    GracePrintf("g0.s%2.2d LEGEND \"%s\"\n", set, fusion[i].name);
  	    GracePrintf("g0.s%2.2d SYMBOL 0\n", set);
  	    GracePrintf("g0.s%2.2d LINESTYLE 1\n", set);
  	    GracePrintf("g0.s%2.2d LINEWIDTH 2\n", set);
  	    GracePrintf("g0.s%2.2d COLOR %2.2d\n", set, color++);
	    
  	    while (p <= 150000.0) {
  	      double deltaG = DBL_MAX, deltaS, kPrime;
  	      int count = 0;
 
  	      while (fabs(deltaG) > sqrt(DBL_EPSILON) && count < 25) {
  		gmixLiq (FIRST, t,   p, rLiq, &deltaG, NULL, NULL);
  		smixLiq (FIRST, t,   p, rLiq, &deltaS, NULL, NULL, NULL);
  		deltaG *= sum;
  		deltaS *= sum;
				
  		if (calculationMode != MODE_xMELTS) {
  		  for (k=0; k<nlc; k++) {
  		    gibbs(t, p, (char *) liquid[k].label, &(liquid[k].ref), &(liquid[k].liq), &(liquid[k].fus), &(liquid[k].cur));
  		    deltaG += (solids[j].solToLiq)[k]*(liquid[k].cur).g;
  		    deltaS += (solids[j].solToLiq)[k]*(liquid[k].cur).s;
  		  }
  		}
 
  		gibbs(t, p, (char *) solids[j].label, &(solids[j].ref), NULL, NULL, &(solids[j].cur));
  		deltaG -= (solids[j].cur).g;
  		deltaS -= (solids[j].cur).s;
 
  		t += deltaG/deltaS;
  		if (t > 3773.0) t = 3773.0;
  		if (t <  773.0) t =  773.0;
  		count++;
  	      }
 
  	      if (count < 25) {
  		double v, dvdp, dvdt, d2vdp2, xSpecies[nls], cp;
  		GracePrintf("g0.s%2.2d POINT %lf, %lf\n", set, t-273.15, p/1000.0);
  		GracePrintf("AUTOSCALE\n");
  		GracePrintf("REDRAW\n");
  		vmixLiq  (FIRST | FOURTH | FIFTH | EIGHTH, t, p, rLiq, &v, NULL, NULL, &dvdt, &dvdp, NULL, NULL, &d2vdp2, NULL, NULL, NULL);
  		cpmixLiq (FIRST, t, p, rLiq, &cp, NULL, NULL);
  		v      *= sum;
  		dvdt   *= sum;
  		dvdp   *= sum;
  		d2vdp2 *= sum;
  		cp     *= sum;
  		if (calculationMode != MODE_xMELTS) {
  		  for (k=0; k<nlc; k++) {
  		    v	   += (solids[j].solToLiq)[k]*(liquid[k].cur).v;
  		    dvdt   += (solids[j].solToLiq)[k]*(liquid[k].cur).dvdt;
  		    dvdp   += (solids[j].solToLiq)[k]*(liquid[k].cur).dvdp;
  		    d2vdp2 += (solids[j].solToLiq)[k]*(liquid[k].cur).d2vdp2;
  		    cp     += (solids[j].solToLiq)[k]*(liquid[k].cur).cp;
  		  }
  		}
  		kPrime = -1.0 + v*d2vdp2/pow(dvdp, (double) 2.0);
  		conLiq(THIRD,  FOURTH | EIGHTH, t, p, NULL, NULL, rLiq, xSpecies, NULL, NULL, NULL);

  		printf("P = %5.1f T = %5.0f K = %6.2f K' = %6.2f delV = %6.2f delS = %6.2f dvdt = %10.3e deldVdT = %10.3e delCp/T = %10.3e\n",
  		  p/10000.0, t-273.15, -v/(dvdp*10000.0), kPrime, 10.0*(v-(solids[j].cur).v), deltaS, 10.0*dvdt, 10.0*(dvdt-(solids[j].cur).dvdt),
  		  (cp-(solids[j].cur).cp)/t);
 
                for (k=0; k<nls; k++) if (xSpecies[k] > 0.005) printf(" %s %4.2f", liquid[k].label, xSpecies[k]); 
                printf("\n");
    
  	      } else {
  		printf("Iteration count exceeded at P = %g kbars, deltaG = %g J, t = %g C.\n", p/1000.0, deltaG, t-273.15);
  		p = 150000.0;
  	      }
 
  	      if (p == 1.0) p = 5000.0; else p += 5000.0;
  	    }

  	  } else printf("--> Generates negative mole fractions.\n");
  	  break;
  	}
      }
      set++;
    } else getchar();
  }

  return 0;
}

/* End file: ANALYZE-FUSION.C */

