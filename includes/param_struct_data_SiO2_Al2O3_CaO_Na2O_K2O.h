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
 * This is the 12/12/08 solution for Na2O-Al2O3-SiO2
 */

static ModelParameters originalModelParameters[] = {
  { "W(Al2O3     ,SiO2      )",   36950.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 001 Basis species     */
  { "W(Ca2SiO4   ,SiO2      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 009 Basis species     */
  { "W(Na2O      ,SiO2      )",       9.5,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Basis species     */
  { "W(K2SiO3	 ,SiO2      )",     -85.1,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 011 Basis species     */
  { "W(H2O       ,SiO2      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 011 Basis species     */

  { "W(CaAl2O4   ,SiO2      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 018 Dependent species */
  { "W(NaAlSiO4  ,SiO2      )",  -16647.5,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,SiO2      )",   49431.3,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAl2Si2O8,SiO2      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSi4O10 ,SiO2      )",  -20527.3,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Si0.25OH	 ,SiO2      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH	 ,SiO2      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH 	 ,SiO2      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,SiO2      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,SiO2      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,SiO2      )",    9617.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,SiO2      )",     364.5,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,SiO2      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,SiO2      )",   17588.2,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,SiO2      )",    6688.5,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,SiO2      )",   17313.6,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,SiO2      )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,SiO2      )",   31325.4,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,SiO2      )",     626.1,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Si4O9  ,SiO2      )",   16353.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na4Al2SiO7,SiO2      )",   -1950.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,SiO2      )",    7156.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,SiO2      )",   28919.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,SiO2      )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,SiO2      )",   12353.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,SiO2      )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,SiO2      )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,SiO2      )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,SiO2      )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Ca2SiO4   ,Al2O3     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 009 Basis species     */
  { "W(Na2O      ,Al2O3     )",   -9340.3,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Basis species     */
  { "W(K2SiO3	 ,Al2O3     )",  -56572.1,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 011 Basis species     */
  { "W(H2O       ,Al2O3     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 011 Basis species     */

  { "W(CaAl2O4   ,Al2O3     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 018 Dependent species */
  { "W(NaAlSiO4  ,Al2O3     )",   43004.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Al2O3     )",   13696.3,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAl2Si2O8,Al2O3     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSi4O10 ,Al2O3     )",   10927.6,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Si0.25OH	 ,Al2O3     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH	 ,Al2O3     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH 	 ,Al2O3     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Al2O3     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Al2O3     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,Al2O3     )",  -30708.3,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,Al2O3     )",  -26150.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,Al2O3     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,Al2O3     )",   -7980.3,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,Al2O3     )",   49637.1,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,Al2O3     )",  116983.1,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,Al2O3     )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,Al2O3     )",   30607.5,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,Al2O3     )",   -6280.6,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Si4O9  ,Al2O3     )",   17662.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na4Al2SiO7,Al2O3     )",   -1942.9,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,Al2O3     )",    2562.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,Al2O3     )",   23439.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Al2O3     )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Al2O3     )",  101592.6,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Al2O3     )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Al2O3     )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Al2O3     )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Al2O3     )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Na2O      ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Basis species     */
  { "W(K2SiO3	 ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 011 Basis species     */
  { "W(H2O       ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 011 Basis species     */

  { "W(CaAl2O4   ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 018 Dependent species */
  { "W(NaAlSiO4  ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAl2Si2O8,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSi4O10 ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Si0.25OH	 ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH	 ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH 	 ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Si4O9  ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na4Al2SiO7,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Ca2SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(K2SiO3	 ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 011 Basis species    */
  { "W(H2O       ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 011 Basis species     */

  { "W(CaAl2O4   ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 018 Dependent species */
  { "W(NaAlSiO4  ,Na2O      )",   43784.6,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAl2Si2O8,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSi4O10 ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Si0.25OH	 ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH	 ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH 	 ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,Na2O      )",     586.2,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,Na2O      )",  -27685.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,Na2O      )",     653.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,Na2O      )",   -2372.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,Na2O      )",      52.4,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,Na2O      )",    8706.4,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,Na2O      )",    -452.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,Na2O      )",     -25.1,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Na2O      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(H2O       ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 011 Basis species     */

  { "W(CaAl2O4   ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 018 Dependent species */
  { "W(NaAlSiO4  ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,K2SiO3    )", -167233.9,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAl2Si2O8,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSi4O10 ,K2SiO3    )",  -27256.3,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Si0.25OH	 ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH	 ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH 	 ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,K2SiO3    )",   -5005.2,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,K2SiO3    )",    5134.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,K2SiO3    )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,K2SiO3    )",   -3735.8,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,K2SiO3    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,K2SiO3    )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,K2SiO3    )",  -83707.7,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,K2SiO3    )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,K2SiO3    )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,K2SiO3    )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,K2SiO3    )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(CaAl2O4   ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 018 Dependent species */
  { "W(NaAlSiO4  ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAl2Si2O8,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSi4O10 ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Si0.25OH	 ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH	 ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH 	 ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,H2O       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
 
  { "W(NaAlSiO4  ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAl2Si2O8,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSi4O10 ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Si0.25OH	 ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH	 ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH 	 ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,CaAl2O4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
 
  { "W(KAlSiO4   ,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAl2Si2O8,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSi4O10 ,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Si0.25OH	 ,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH	 ,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH 	 ,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,NaAlSiO4  )",   17130.2,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,NaAlSiO4  )",   38108.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,NaAlSiO4  )",  -17381.8,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,NaAlSiO4  )",   37488.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,NaAlSiO4  )",   24858.3,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,NaAlSiO4  )",  -36177.4,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,NaAlSiO4  )",  -59136.9,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,NaAlSiO4  )",   -3465.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,NaAlSiO4  )",  -10409.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,NaAlSiO4  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(CaAl2Si2O8,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSi4O10 ,KAlSiO4   )", -134679.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Si0.25OH	 ,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH	 ,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH 	 ,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,KAlSiO4   )",  -58534.8,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,KAlSiO4   )",   47388.6,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,KAlSiO4   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,KAlSiO4   )",    7736.8,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,KAlSiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,KAlSIO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,KAlSiO4   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,KAlSiO4   )",   47738.7,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,KAlSiO4   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,KAlSiO4   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,KAlSiO4   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,KAlSiO4   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(KAlSi4O10 ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Si0.25OH	 ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH	 ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH 	 ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,CaAl2Si2O8)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Si0.25OH	 ,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH	 ,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH 	 ,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,KAlSi4O10 )",   99859.8,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,KAlSi4O10 )",   20189.4,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,KAlSi4O10 )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,KAlSi4O10 )",  -18729.6,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,KAlSi4O10 )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,KAlSi4O10 )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,KAlSi4O10 )",  -90675.2,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,KAlSi4O10 )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,KAlSi4O10 )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,KAlSi4O10 )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,KAlSi4O10 )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Al0.33OH	 ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH 	 ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Si0.25OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Ca0.5OH 	 ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Al0.33OH  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(NaOH      ,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Ca0.5OH   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(KOH       ,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2SiO3   ,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,NaOH      )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Na2SiO3   ,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlO2    ,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,KOH       )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(NaAlO2    ,Na2SiO3   )",  -33709.1,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlO2     ,Na2SiO3   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,Na2SiO3   )",  -12093.8,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,Na2SiO3   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,Na2SiO3   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,Na2SiO3   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,Na2SiO3   )",  -13383.4,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,Na2SiO3   )",    2657.3,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,Na2SiO3   )",  -14668.5,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,Na2SiO3   )",   -4180.9,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,Na2SiO3   )",   -8158.9,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,Na2SiO3   )",   26961.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Na2SiO3   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Na2SiO3   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Na2SiO3   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Na2SiO3   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Na2SiO3   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Na2SiO3   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(KAlO2     ,NaAlO2    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si2O5  ,NaAlO2    )",   -9416.3,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,NaAlO2    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,NaAlO2    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,NaAlO2    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,NaAlO2    )",    -160.9,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,NaAlO2    )",   -9521.1,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,NaAlO2    )",   17928.9,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,NaAlO2    )",    -818.5,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,NaAlO2    )",   -2172.9,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,NaAlO2    )",      95.2,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,NaAlO2    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,NaAlO2    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,NaAlO2    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,NaAlO2    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,NaAlO2    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,NaAlO2    )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Na2Si2O5  ,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si2O5   ,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,KAlO2     )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(K2Si2O5   ,Na2Si2O5  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Si4O9   ,Na2Si2O5  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,Na2Si2O5  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,Na2Si2O5  )",   -1062.9,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,Na2Si2O5  )",    2029.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,Na2Si2O5  )",   -4450.4,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,Na2Si2O5  )",   46612.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,Na2Si2O5  )",   -2469.5,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,Na2Si2O5  )",    6883.8,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Na2Si2O5  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Na2Si2O5  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Na2Si2O5  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Na2Si2O5  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Na2Si2O5  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Na2Si2O5  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(K2Si4O9   ,K2Si2O5   )",  -15706.5,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si4O1,K2Si2O5   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,K2Si2O5   )",   57163.8,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,K2Si2O5   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,K2Si2O5   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,K2Si2O5   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,K2Si2O5   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,K2Si2O5   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,K2Si2O5   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,K2Si2O5   )",    7161.4,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,K2Si2O5   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,K2Si2O5   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,K2Si2O5   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,K2Si2O5   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(K4Al2Si4O1,K2Si4O9   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al6Si2O13 ,K2Si4O9   )",   57419.7,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,K2Si4O9   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,K2Si4O9   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,K2Si4O9   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,K2Si4O9   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,K2Si4O9   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,K2Si4O9   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,K2Si4O9   )",   18906.3,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,K2Si4O9   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,K2Si4O9   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,K2Si4O9   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,K2Si4O9   )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Al6Si2O13 ,K4Al2Si4O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4SiO4   ,K4Al2Si4O1)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,K4Al2Si4O1)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,K4Al2Si4O1)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,K4Al2Si4O1)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,K4Al2Si4O1)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,K4Al2Si4O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,K4Al2Si4O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,K4Al2Si4O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,K4Al2Si4O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,K4Al2Si4O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,K4Al2Si4O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Na4SiO4   ,Al6Si2O13 )",   -2627.8,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2Si4O9  ,Al6Si2O13 )",    2906.3,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,Al6Si2O13 )",     -30.7,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,Al6Si2O13 )",    -621.9,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,Al6Si2O13 )",   39449.5,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Al6Si2O13 )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Al6Si2O13 )",   23905.5,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Al6Si2O13 )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Al6Si2O13 )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Al6Si2O13 )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Al6Si2O13 )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Na2Si4O9  ,Na4SiO4   )",   -2604.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na4Al2SiO7,Na4SiO4   )",    3456.3,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,Na4SiO4   )",     891.2,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,Na4SiO4   )",    -385.3,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Na4SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Na4SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Na4SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Na4SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Na4SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Na4SiO4   )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Na4Al2SiO7,Na2Si4O9  )",    4671.1,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(Na2Al4SiO9,Na2Si4O9  )",   -2306.8,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,Na2Si4O9  )",   10895.4,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Na2Si4O9  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Na2Si4O9  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Na2Si4O9  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Na2Si4O9  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Na2Si4O9  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Na2Si4O9  )",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Na2Al4SiO9,Na4Al2SiO7)",   -7756.3,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(NaAlSi4O10,Na4Al2SiO7)",  -14678.5,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Na4Al2SiO7)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Na4Al2SiO7)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Na4Al2SiO7)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Na4Al2SiO7)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Na4Al2SiO7)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Na4Al2SiO7)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(NaAlSi4O10,Na2Al4SiO9)",   24203.5,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(K2Al4Si2O1,Na2Al4SiO9)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,Na2Al4SiO9)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,Na4Al4SiO9)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,Na4Al4SiO9)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,Na4Al4SiO9)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,Na4Al4SiO9)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(K2Al4Si2O1,NaAlSi4O10)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Dependent species */
  { "W(KAlSi2O6  ,NaAlSi4O10)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,NaAlSi4O10)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,NaAlSi4O10)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,NaAlSi4O10)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,NaAlSi4O10)",       0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  
  { "W(KAlSi2O6  ,K2Al4Si2O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si8O2,K2Al4Si2O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,K2Al4Si2O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,K2Al4Si2O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,K2Al4Si2O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  
  { "W(K4Al2Si8O2,KAlSi2O6  )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K4Al2Si16O,KAlSi2O6  )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,KAlSi2O6  )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,KAlSi2O6  )",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  
  { "W(K4Al2Si16O,K4Al2Si8O2)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si4O1,K4Al2Si8O2)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,K4Al2Si8O2)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  
  { "W(K2Al4Si4O1,K4Al2Si16O)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2Al4Si8O2,K4Al2Si16O)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  
  { "W(K2Al4Si8O2,K2Al4Si4O1)",       0.0,  0.0,  0.0,  TRUE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  
#define SCORR (-40.0)
#define HCORR (60000.0)

  { "SiO2                    ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 001 Basis species     */
  { "Al2O3                   ",  -12846.3,	-6.1,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 009 Basis species     */
  { "Ca2SiO4                 ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Basis species     */
  { "Na2O                    ",    1650.7,     -38.7,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 011 Basis species     */
  { "K2SiO3                  ",    4291.1,     -13.5,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 011 Basis species     */
  { "H2O                     ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 011 Basis species     */
			
  { "CaAl2O4                 ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 018 Dependent species */
  { "NaAlSiO4                ",   51882.0,	89.9,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "KAlSiO4                 ",   32923.9,	68.9,  0.0,  TRUE,  TRUE, FALSE, FALSE }, /* 019 Dependent species */
  { "CaAl2Si2O8              ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "KAlSi4O10               ",   41847.1,	27.8,  0.0,  TRUE,  TRUE, FALSE, FALSE }, /* 019 Dependent species */
  { "Si0.25OH                ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Al0.33OH                ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Ca0.5OH                 ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "NaOH                    ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "KOH                     ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Na2SiO3                 ",  -35722.7,     -25.5,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "NaAlO2                  ",   16725.0,     -23.6,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "KAlO2                   ",    1639.0,     -13.2,  0.0,  TRUE,  TRUE, FALSE, FALSE }, /* 019 Dependent species */
  { "Na2Si2O5                ",  -29154.7,     -18.3,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "K2Si2O5                 ",  -19558.5,     -20.8,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "K2Si4O9                 ",   -2825.1,	-7.2,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "K4Al2Si4O1              ",    8475.0,	-9.3,  0.0,  TRUE,  TRUE, FALSE, FALSE }, /* 019 Dependent species */
  { "Al6Si2O13               ", -137771.2,    -110.5,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Na4SiO4                 ",  -22896.0,     -40.2,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Na2Si4O9                ",  -12894.5,     -10.5,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Na4Al2SiO7              ",  -13097.3,	44.7,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Na2Al4SiO9              ",  -53043.0,	11.1,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "NaAlSi4O10              ",   -4245.9,	35.5,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "K2Al4Si2O11             ",   10615.0,	-8.1,  0.0,  TRUE,  TRUE, FALSE, FALSE }, /* 019 Dependent species */
  { "KAlSi2O6                ",  -32394.9,	30.4,  0.0,  TRUE,  TRUE, FALSE, FALSE }, /* 019 Dependent species */
  { "K4Al2Si8O21             ",  -11804.0,	-6.7,  0.0,  TRUE,  TRUE, FALSE, FALSE }, /* 019 Dependent species */
  { "K4Al2Si16O37            ",   -7512.0,	-4.2,  0.0,  TRUE,  TRUE, FALSE, FALSE }, /* 019 Dependent species */
  { "K2Al4Si4O115            ",   13492.0,	-6.5,  0.0,  TRUE,  TRUE, FALSE, FALSE }, /* 019 Dependent species */
  { "K2Al4Si8O23             ",   16780.0,	-4.6,  0.0,  TRUE,  TRUE, FALSE, FALSE }, /* 019 Dependent species */

#undef SCORR

  {"albite"                   ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"carnegieite"              ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"corundum"                 ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"cristobalite"             ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"enthalpy"                 ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"entropy"                  ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"kalsilitehex"             ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment	    */
  {"kalsiliteortho"           ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment	    */
  {"kdisilicate"              ,   17711.6,  12.6,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment	    */
  {"kmetasilicate"            ,   18614.7, -20.1,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment	    */
  {"ktetrasilicate"           ,  -28417.4,  29.5,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment	    */
  {"leucite"                  ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"liquid"                   ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"mullite"                  ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"muscovite"                ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"nadisilicate"             ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"nametasilicate"           ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"naorthosilicate"          ,    6946.5,  -9.9,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"naalo2"                   ,  -29902.5,   1.4,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"naal9o14"                 ,    2604.7,   5.9,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"nepheline"                ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"pseudowollastonite"       ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"quartz"                   ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"sanidine"                 ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"tridymite"                ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"water"                    ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"wollastonite"             ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"coesite-sx"               ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"stishovite-sx"            ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"feldspar"                 ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"albite"                   ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"anorthite"                ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"sanidine"                 ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"kalsilite ss"             ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"na-nepheline"             ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"k-nepheline"              ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"vc-nepheline"             ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ca-nepheline"             ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"leucite ss"               ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"leucite"                  ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"analcime"                 ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"na-leucite"               ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"nepheline ss"             ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"na-nepheline"             ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"k-nepheline"              ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"vc-nepheline"             ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ca-nepheline"             ,       0.0,   0.0,  0.0, FALSE, FALSE, FALSE, FALSE }  /* Solid component adjustment */
};

ModelParameters *modelParameters = originalModelParameters;

EosModelParameters eosModelParameters[] = {  /* sets nc entries */
                             /*  Kp   Kpp   Kppp */
  { "SiO2		     ", 0.188587,  1.91476e-05,  6.26232e-10, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "Al2O3		     ", 0.720748, -1.22963e-05,   1.7757e-10, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "CaO		     ",  18.0476,  0.000891667,  -2.0328e-08, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "Na2O		     ",   22.208,   0.00711102,  3.17635e-06, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "K2O		     ",  4.25535,  0.000752301,  8.46257e-08, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "H2O		     ",-0.653589, -7.46073e-06,  -8.1586e-12, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 }    
}; 

int    nCN   = 0;                  /* Total number of coordination states beyond reference            */
#ifdef NEVER_DEFINED
int    nCN   = 2;                  /* Total number of coordination states beyond reference            */
double fCN[] = { 0.8346, 0.7811 }; /* configurational collapse term for IV->V, IV->IV oxygen CN shift */

SsCnModelParameters ssCnModelParameters[] = {           /* sets nc entries, repeated nCN-1 times   */
  { "SiO2		     ",  250000.0,       0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-001 */
  { "Al2O3		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-003 */
  { "CaO		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-011 */
  { "Na2O		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-012 */
  { "K2O		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-013 */
  { "H2O		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-015 */
  { "SiO2		     ",  300000.0,       0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-001 */
  { "Al2O3		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-003 */
  { "CaO		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-011 */
  { "Na2O		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-012 */
  { "K2O		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-013 */
  { "H2O		     ",  300000.0,	 0.0 }  /* oxygen VI-IV delta quantity (VI-IV)-015 */
};

WCnModelParameters wCnModelParameters[] = {             /* sets of nc*(nc-1)/2 entries, repeated nCN times */
 /* Label                        [r][*]-[r] [*][r]-[r] [*][*]-[r]         r = refernce CN, * = current CN  */
  { "W(Al2O3     ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-002 */
  { "W(CaO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-010 */
  { "W(Na2O      ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-011 */
  { "W(K2O       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-012 */
  { "W(H2O       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-014 */

  { "W(CaO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-043 */
  { "W(Na2O      ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-044 */
  { "W(K2O       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-045 */
  { "W(H2O       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-047 */

  { "W(Na2O      ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-136 */
  { "W(K2O       ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-137 */
  { "W(H2O       ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-139 */

  { "W(K2O       ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-144 */
  { "W(H2O       ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-146 */

  { "W(H2O       ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-152 */

  { "W(Al2O3     ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-002 */
  { "W(CaO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-010 */
  { "W(Na2O      ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-011 */
  { "W(K2O       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-012 */
  { "W(H2O       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-014 */

  { "W(CaO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-043 */
  { "W(Na2O      ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-044 */
  { "W(K2O       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-045 */
  { "W(H2O       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-047 */

  { "W(Na2O      ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-136 */
  { "W(K2O       ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-137 */
  { "W(H2O       ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-139 */

  { "W(K2O       ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-144 */
  { "W(H2O       ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-146 */

  { "W(H2O       ,K2O       )", {	0.0,	   0.0,       0.0 } }  /* oxygen VI-IV delta quantity (VI-IV)-152 */
};
#endif /* NEVER_DEFINED */

#endif /* _Param_Struct_Data_h */
