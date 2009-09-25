#ifndef _Param_Struct_Data_h
#define _Param_Struct_Data_h

/*
**++
**  FACILITY:  Silicate Melts Regression Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Include file for initializing values of liquid interaction
**         parameters (file: PARAM_STRUCT_DATA.H)
**
**  This file produced on: Tue Nov 16 15:48:01 2004
**--
*/

/*
 *=============================================================================
 * Initialize global values of interaction parameters
 */

static ModelParameters originalModelParameters[] = {
  { "W(MgO       ,SiO2      )",   30112.9,       0.0,  0.000000,  TRUE, FALSE, FALSE, FALSE }, /* 006 Basis species     */
  { "W(MgSiO3    ,SiO2      )",   44358.5,       0.0,  0.000000,  TRUE, FALSE, FALSE, FALSE }, /* 025 Dependent species */
  { "W(MgSiO3    ,MgO       )",    5316.3,       0.0,  0.000000,  TRUE, FALSE, FALSE, FALSE }, /* 256 Dependent species */

  { "SiO2                    ",  -3665.06, -2.641425,  0.000000, FALSE, FALSE, FALSE, FALSE }, /* 702     Basis species */
  { "MgO                     ",  -11167.4,     -33.5,  0.000000,  TRUE,  TRUE, FALSE, FALSE }, /* 709     Basis species */
  { "MgSiO3                  ",   -7526.4,      -5.7,  0.000000,  TRUE,  TRUE, FALSE, FALSE }  /* 728 Dependent species */
};

ModelParameters *modelParameters = originalModelParameters;

EosModelParameters eosModelParameters[] = {  /* sets nc entries */
  { "SiO2		     ",  0.0, 0.0, 0.0, FALSE, FALSE, FALSE }, 
  { "MgO		     ",  0.0, 0.0, 0.0, FALSE, FALSE, FALSE } 
};

int    nCN   = 2;                  /* Total number of coordination states beyond reference            */
double fCN[] = { 0.8346, 0.7811 }; /* configurational collapse term for IV->V, IV->IV oxygen CN shift */

SsCnModelParameters ssCnModelParameters[] = {           /* sets nc entries, repeated nCN-1 times   */
  { "SiO2		     ",   38580.4,  -1.09516 }, /* oxygen  V-IV delta quantity ( V-IV)-001 */
  { "MgO		     ",  211071.0,   1.09516 }, /* oxygen  V-IV delta quantity ( V-IV)-008 */

  { "SiO2		     ",   44645.4,  -12.0006 }, /* oxygen VI-IV delta quantity (VI-IV)-001 */
  { "MgO		     ",  441812.0,   12.0006 }  /* oxygen VI-IV delta quantity (VI-IV)-008 */
};

WCnModelParameters wCnModelParameters[] = {             /* sets of nc*(nc-1)/2 entries, repeated nCN times */
 /* Label                        [r][*]-[r] [*][r]-[r] [*][*]-[r]         r = refernce CN, * = current CN  */
  { "W(MgO       ,SiO2      )", {       0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-007 */
  { "W(MgO       ,SiO2      )", {       0.0,	   0.0,       0.0 } }  /* oxygen VI-IV delta quantity (VI-IV)-007 */
};

#endif /* _Param_Struct_Data_h */
