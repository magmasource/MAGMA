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
  { "W(TiO2      ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 000 Basis species	 */
  { "W(Al2O3     ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 001 Basis species	 */
  { "W(Fe2SiO5   ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 002 Basis species	 */
  { "W(Cr2O3     ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 003 Basis species	 */
  { "W(Fe2SiO4   ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 004 Basis species	 */
  { "W(Mn2SiO4   ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 005 Basis species	 */
  { "W(Mg2SiO4   ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 006 Basis species	 */
  { "W(Ni2SiO4   ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 007 Basis species	 */
  { "W(Co2SiO4   ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 008 Basis species	 */
  { "W(Ca2SiO4   ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 009 Basis species	 */
  { "W(Na2SiO3   ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 010 Basis species	 */
  { "W(K2SiO3	 ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 011 Basis species	 */
  { "W(P2O5      ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 012 Basis species	 */
  { "W(CO2       ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 013 Basis species	 */
  { "W(SO3       ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 014 Basis species	 */
  { "W(Cl2O-1    ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 015 Basis species	 */
  { "W(F2O-1     ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 016 Basis species	 */
  { "W(H2O       ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 017 Basis species	 */

  { "W(Fe2SiO4.6 ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 018 Dependent species */
  { "W(Si0.25OH  ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgSiO3    ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.5 ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Al2O3     ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 037 Basis species	 */
  { "W(Fe2SiO5   ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 038 Basis species	 */
  { "W(Cr2O3     ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 039 Basis species	 */
  { "W(Fe2SiO4   ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 040 Basis species	 */
  { "W(Mn2SiO4   ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 041 Basis species	 */
  { "W(Mg2SiO4   ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 042 Basis species	 */
  { "W(Ni2SiO4   ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 043 Basis species	 */
  { "W(Co2SiO4   ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 044 Basis species	 */
  { "W(Ca2SiO4   ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 045 Basis species	 */
  { "W(Na2SiO3   ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 046 Basis species	 */
  { "W(K2SiO3	 ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 047 Basis species	 */
  { "W(P2O5      ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 048 Basis species	 */
  { "W(CO2       ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 049 Basis species	 */
  { "W(SO3       ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 050 Basis species	 */
  { "W(Cl2O-1    ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 051 Basis species	 */
  { "W(F2O-1     ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 052 Basis species	 */
  { "W(H2O       ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 053 Basis species	 */

  { "W(Fe2SiO4.6 ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 054 Dependent species */
  { "W(Si0.25OH  ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 055 Dependent species */
  { "W(MgSiO3    ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 055 Dependent species */
  { "W(Fe2AlO4.5 ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,TiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Fe2SiO5   ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 073 Basis species	 */
  { "W(Cr2O3     ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 074 Basis species	 */
  { "W(Fe2SiO4   ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 075 Basis species	 */
  { "W(Mn2SiO4   ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 076 Basis species	 */
  { "W(Mg2SiO4   ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 077 Basis species	 */
  { "W(Ni2SiO4   ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 078 Basis species	 */
  { "W(Co2SiO4   ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 079 Basis species	 */
  { "W(Ca2SiO4   ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 080 Basis species	 */
  { "W(Na2SiO3   ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 081 Basis species	 */
  { "W(K2SiO3	 ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 082 Basis species	 */
  { "W(P2O5      ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 083 Basis species	 */
  { "W(CO2       ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 084 Basis species	 */
  { "W(SO3       ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 085 Basis species	 */
  { "W(Cl2O-1    ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 086 Basis species	 */
  { "W(F2O-1     ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 087 Basis species	 */
  { "W(H2O       ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 088 Basis species	 */
  
  { "W(Fe2SiO4.6 ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 089 Dependent species */
  { "W(Si0.25OH  ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 090 Dependent species */
  { "W(MgSiO3    ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 090 Dependent species */
  { "W(Fe2AlO4.5 ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Al2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Cr2O3     ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 108 Basis species	 */
  { "W(Fe2SiO4   ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 109 Basis species	 */
  { "W(Mn2SiO4   ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 110 Basis species	 */
  { "W(Mg2SiO4   ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 111 Basis species	 */
  { "W(Ni2SiO4   ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 112 Basis species	 */
  { "W(Co2SiO4   ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 113 Basis species	 */
  { "W(Ca2SiO4   ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 114 Basis species	 */
  { "W(Na2SiO3   ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 115 Basis species	 */
  { "W(K2SiO3	 ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 116 Basis species	 */
  { "W(P2O5      ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 117 Basis species	 */
  { "W(CO2       ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 118 Basis species	 */
  { "W(SO3       ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 119 Basis species	 */
  { "W(Cl2O-1    ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 120 Basis species	 */
  { "W(F2O-1     ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 121 Basis species	 */
  { "W(H2O       ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 122 Basis species	 */

  { "W(Fe2SiO4.6 ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 123 Dependent species */
  { "W(Si0.25OH  ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 124 Dependent species */
  { "W(MgSiO3    ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 124 Dependent species */
  { "W(Fe2AlO4.5 ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Fe2SiO5   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
			             	  	                					   
  { "W(Fe2SiO4   ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 142 Basis species	 */
  { "W(Mn2SiO4   ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 143 Basis species	 */
  { "W(Mg2SiO4   ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 144 Basis species	 */
  { "W(Ni2SiO4   ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 145 Basis species	 */
  { "W(Co2SiO4   ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 146 Basis species	 */
  { "W(Ca2SiO4   ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 147 Basis species	 */
  { "W(Na2SiO3   ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 148 Basis species	 */
  { "W(K2SiO3	 ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 149 Basis species	 */
  { "W(P2O5      ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 150 Basis species	 */
  { "W(CO2       ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 151 Basis species	 */
  { "W(SO3       ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 152 Basis species	 */
  { "W(Cl2O-1    ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 153 Basis species	 */
  { "W(F2O-1     ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 154 Basis species	 */
  { "W(H2O       ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 155 Basis species	 */

  { "W(Fe2SiO4.6 ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 156 Dependent species */
  { "W(Si0.25OH  ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 157 Dependent species */
  { "W(MgSiO3    ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 157 Dependent species */
  { "W(Fe2AlO4.5 ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Cr2O3     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Mn2SiO4   ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 175 Basis species	 */
  { "W(Mg2SiO4   ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 176 Basis species	 */
  { "W(Ni2SiO4   ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 177 Basis species	 */
  { "W(Co2SiO4   ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 178 Basis species	 */
  { "W(Ca2SiO4   ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 179 Basis species	 */
  { "W(Na2SiO3   ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 180 Basis species	 */
  { "W(K2SiO3	 ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 181 Basis species	 */
  { "W(P2O5      ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 182 Basis species	 */
  { "W(CO2       ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 183 Basis species	 */
  { "W(SO3       ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 184 Basis species	 */
  { "W(Cl2O-1    ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 185 Basis species	 */
  { "W(F2O-1     ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 186 Basis species	 */
  { "W(H2O       ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 187 Basis species	 */

  { "W(Fe2SiO4.6 ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 188 Dependent species */
  { "W(Si0.25OH  ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 189 Dependent species */
  { "W(MgSiO3    ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 189 Dependent species */
  { "W(Fe2AlO4.5 ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Fe2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Mg2SiO4   ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 207 Basis species	 */
  { "W(Ni2SiO4   ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 208 Basis species	 */
  { "W(Co2SiO4   ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 209 Basis species	 */
  { "W(Ca2SiO4   ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 210 Basis species	 */
  { "W(Na2SiO3   ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 211 Basis species	 */
  { "W(K2SiO3	 ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 212 Basis species	 */
  { "W(P2O5      ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 213 Basis species	 */
  { "W(CO2       ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 214 Basis species	 */
  { "W(SO3       ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 215 Basis species	 */
  { "W(Cl2O-1    ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 216 Basis species	 */
  { "W(F2O-1     ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 217 Basis species	 */
  { "W(H2O       ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 218 Basis species	 */

  { "W(Fe2SiO4.6 ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 219 Dependent species */
  { "W(Si0.25OH  ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 220 Dependent species */
  { "W(MgSiO3    ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 220 Dependent species */
  { "W(Fe2AlO4.5 ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Mn2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Ni2SiO4   ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 238 Basis species	 */
  { "W(Co2SiO4   ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 239 Basis species	 */
  { "W(Ca2SiO4   ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 240 Basis species	 */
  { "W(Na2SiO3   ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 241 Basis species	 */
  { "W(K2SiO3	 ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 242 Basis species	 */
  { "W(P2O5      ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 243 Basis species	 */
  { "W(CO2       ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 244 Basis species	 */
  { "W(SO3       ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 245 Basis species	 */
  { "W(Cl2O-1    ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 246 Basis species	 */
  { "W(F2O-1     ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 247 Basis species	 */
  { "W(H2O       ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 248 Basis species	 */

  { "W(Fe2SiO4.6 ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 249 Dependent species */
  { "W(Si0.25OH  ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 250 Dependent species */
  { "W(MgSiO3    ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 250 Dependent species */
  { "W(Fe2AlO4.5 ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Mg2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Co2SiO4   ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 268 Basis species	 */
  { "W(Ca2SiO4   ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 269 Basis species	 */
  { "W(Na2SiO3   ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 270 Basis species	 */
  { "W(K2SiO3	 ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 271 Basis species	 */
  { "W(P2O5      ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 272 Basis species	 */
  { "W(CO2       ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 272 Basis species	 */
  { "W(SO3       ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 273 Basis species	 */
  { "W(Cl2O-1    ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 274 Basis species	 */
  { "W(F2O-1     ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 275 Basis species	 */
  { "W(H2O       ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 276 Basis species	 */

  { "W(Fe2SiO4.6 ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 277 Dependent species */
  { "W(Si0.25OH  ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 278 Dependent species */
  { "W(MgSiO3    ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 278 Dependent species */
  { "W(Fe2AlO4.5 ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Ni2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Ca2SiO4   ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 296 Basis species	 */
  { "W(Na2SiO3   ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 297 Basis species	 */
  { "W(K2SiO3	 ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 298 Basis species	 */	
  { "W(P2O5      ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 299 Basis species	 */    
  { "W(CO2       ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 300 Basis species	 */
  { "W(SO3       ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 301 Basis species	 */
  { "W(Cl2O-1    ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 302 Basis species	 */
  { "W(F2O-1     ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 303 Basis species	 */
  { "W(H2O       ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 304 Basis species	 */
			             	  	                					   
  { "W(Fe2SiO4.6 ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 305 Dependent species */
  { "W(Si0.25OH  ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 306 Dependent species */
  { "W(MgSiO3    ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 306 Dependent species */
  { "W(Fe2AlO4.5 ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Co2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
			             	  	                					   
  { "W(Na2SiO3   ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 324 Basis species	 */
  { "W(K2SiO3	 ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 325 Basis species	 */
  { "W(P2O5      ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 326 Basis species	 */
  { "W(CO2       ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 327 Basis species	 */
  { "W(SO3       ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 328 Basis species	 */
  { "W(Cl2O-1    ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 329 Basis species	 */
  { "W(F2O-1     ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 330 Basis species	 */
  { "W(H2O       ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 331 Basis species	 */

  { "W(Fe2SiO4.6 ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 332 Dependent species */
  { "W(Si0.25OH  ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 333 Dependent species */
  { "W(MgSiO3    ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 333 Dependent species */
  { "W(Fe2AlO4.5 ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Ca2SiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(K2SiO3	 ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 351 Basis species	 */
  { "W(P2O5      ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 352 Basis species	 */
  { "W(CO2       ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 353 Basis species	 */
  { "W(SO3       ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 354 Basis species	 */
  { "W(Cl2O-1    ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 355 Basis species	 */
  { "W(F2O-1     ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 356 Basis species	 */
  { "W(H2O       ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 357 Basis species	 */

  { "W(Fe2SiO4.6 ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 358 Dependent species */
  { "W(Si0.25OH  ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 359 Dependent species */
  { "W(MgSiO3    ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 359 Dependent species */
  { "W(Fe2AlO4.5 ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Na2SiO3   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(P2O5      ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 377 Basis species	 */
  { "W(CO2       ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 378 Basis species	 */
  { "W(SO3       ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 379 Basis species	 */
  { "W(Cl2O-1    ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 380 Basis species	 */
  { "W(F2O-1     ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 381 Basis species	 */
  { "W(H2O       ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 382 Basis species	 */

  { "W(Fe2SiO4.6 ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 383 Dependent species */
  { "W(Si0.25OH  ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 384 Dependent species */
  { "W(MgSiO3    ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 384 Dependent species */
  { "W(Fe2AlO4.5 ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,K2SiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(CO2       ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 402 Basis species	 */
  { "W(SO3       ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 403 Basis species	 */
  { "W(Cl2O-1    ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 404 Basis species	 */
  { "W(F2O-1     ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 405 Basis species	 */
  { "W(H2O       ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 406 Basis species	 */

  { "W(Fe2SiO4.6 ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 407 Dependent species */
  { "W(Si0.25OH  ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 408 Dependent species */
  { "W(MgSiO3    ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 408 Dependent species */
  { "W(Fe2AlO4.5 ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,SiO2      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,P2O5      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(SO3       ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 426 Basis species	 */
  { "W(Cl2O-1    ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 427 Basis species	 */
  { "W(F2O-1     ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 428 Basis species	 */
  { "W(H2O       ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 429 Basis species	 */

  { "W(Fe2SiO4.6 ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 430 Dependent species */
  { "W(Si0.25OH  ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 431 Dependent species */
  { "W(MgSiO3    ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 431 Dependent species */
  { "W(Fe2AlO4.5 ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,CO2       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Cl2O-1    ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 449 Basis species	 */
  { "W(F2O-1     ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 450 Basis species	 */
  { "W(H2O       ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 451 Basis species	 */

  { "W(Fe2SiO4.6 ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 452 Dependent species */
  { "W(Si0.25OH  ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 453 Dependent species */
  { "W(MgSiO3    ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 453 Dependent species */
  { "W(Fe2AlO4.5 ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,SO3       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(F2O-1     ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 471 Basis species	 */
  { "W(H2O       ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 472 Basis species	 */

  { "W(Fe2SiO4.6 ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 473 Dependent species */
  { "W(Si0.25OH  ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 474 Dependent species */
  { "W(MgSiO3    ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 474 Dependent species */
  { "W(Fe2AlO4.5 ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Cl2O-1    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(H2O       ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 492 Basis species	 */

  { "W(Fe2SiO4.6 ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 493 Dependent species */
  { "W(Si0.25OH  ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 494 Dependent species */
  { "W(MgSiO3    ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 494 Dependent species */
  { "W(Fe2AlO4.5 ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,F2O-1     )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Fe2SiO4.6 ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 512 Dependent species */
  { "W(Si0.25OH  ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 513 Dependent species */
  { "W(MgSiO3    ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 513 Dependent species */
  { "W(Fe2AlO4.5 ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,H2O       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Si0.25OH  ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 531 Dependent species */
  { "W(MgSiO3    ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 531 Dependent species */
  { "W(Fe2AlO4.5 ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Fe2SiO4.6 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(MgSiO3    ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 531 Dependent species */
  { "W(Fe2AlO4.5 ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Si0.25OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Fe2AlO4.5 ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO3.5 ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,MgSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Fe2AlO3.5 ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg2AlO3.5 ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Fe2AlO4.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Mg2AlO3.5 ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca2AlO3.5 ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Fe2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Ca2AlO3.5 ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Na2AlO2.5 ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Mg2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Na2AlO2.5 ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(K2AlO2.5  ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Ca2AlO3.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(K2AlO2.5  ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe2AlO4.1 ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Na2AlO2.5 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Fe2AlO4.1 ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Al0.33OH  ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,K2AlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Al0.33OH  ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(MgAlO2.5  ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Fe2AlO4.1 )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(MgAlO2.5  ,Al0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeSiO3    ,Al0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,Al0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,Al0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,Al0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Al0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Al0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Al0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Al0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Al0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Al0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Al0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(FeSiO3    ,MgAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(FeAlO2.5  ,MgAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,MgAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,MgAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,MgAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,MgAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,MgAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,MgAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,MgAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,MgAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,MgAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(FeAlO2.5  ,FeSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.33OH  ,FeSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,FeSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,FeSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,FeSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,FeSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,FeSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,FeSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,FeSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,FeSiO3    )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Fe0.33OH  ,FeAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Fe0.5OH   ,FeAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,FeAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,FeAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,FeAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,FeAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,FeAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,FeAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,FeAlO2.5  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Fe0.5OH   ,Fe0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Mg0.5OH   ,Fe0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Fe0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Fe0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Fe0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Fe0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Fe0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Fe0.33OH  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Mg0.5OH   ,Fe0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(Ca0.5OH   ,Fe0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Fe0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Fe0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Fe0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Fe0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Fe0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(Ca0.5OH   ,Mg0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaOH      ,Mg0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Mg0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Mg0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Mg0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Mg0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(NaOH      ,Ca0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KOH       ,Ca0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,Ca0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,Ca0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,Ca0.5OH   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(KOH       ,NaOH      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(NaAlSiO4  ,NaOH      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,NaOH      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,NaOH      )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(NaAlSiO4  ,KOH       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(KAlSiO4   ,KOH       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,KOH       )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(KAlSiO4   ,NaAlSiO4  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "W(CaAlSiO4  ,NaAlSiO4  )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "W(CaAlSiO4  ,KAlSiO4   )",  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  { "SiO2                    ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 702     Basis species */
  { "TiO2                    ",   13031.9,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 703     Basis species */
  { "Al2O3                   ",  -21190.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 704     Basis species */
  { "Fe2SiO5                 ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 705     Basis species */
  { "Cr2O3                   ",  303262.8,     214.7,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 706     Basis species */
  { "Fe2SiO4		     ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 707     Basis species */
  { "Mn2SiO4		     ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 708     Basis species */
  { "Mg2SiO4		     ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 709     Basis species */
  { "Ni2SiO4		     ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 710     Basis species */
  { "Co2SiO4		     ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 711     Basis species */
  { "Ca2SiO4		     ", -115240.8,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 712     Basis species */
  { "Na2SiO3		     ",  -64812.9,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 713     Basis species */
  { "K2SiO3		     ",  121171.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 714     Basis species */
  { "P2O5       	     ",  198624.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 715     Basis species */
  { "CO2                     ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 716     Basis species */
  { "SO3                     ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 717     Basis species */
  { "Cl2O-1                  ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 718     Basis species */
  { "F2O-1                   ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 719     Basis species */
  { "H2O                     ",  -12706.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 720     Basis species */

  { "Fe2SiO4.6               ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 721 Dependent species */
  { "Si0.25OH                ",  127310.6,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 722 Dependent species */
  { "MgSiO3                  ",    7758.1,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 722 Dependent species */
  { "Fe2AlO4.5  	     ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Fe2AlO3.5  	     ",   12864.6,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Mg2AlO3.5  	     ",  -14946.7,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Ca2AlO3.5  	     ", -103710.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Na2AlO2.5  	     ",   11047.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "K2AlO2.5   	     ",  -16199.7,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Fe2AlO4.1  	     ",       0.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Al0.33OH   	     ",  137679.3,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "MgAlO2.5   	     ",   37524.8,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "FeSiO3                  ",   63243.0,       0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "FeAlO2.5                ",   17396.9,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Fe0.33OH   	     ",  113289.5,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Fe0.5OH    	     ",   82199.5,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Mg0.5OH    	     ",   91139.1,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "Ca0.5OH    	     ",  158065.9,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "NaOH       	     ",  125126.0,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "KOH        	     ",  134578.9,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "NaAlSiO4                ",  -65245.4,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "KAlSiO4                 ", -146649.1,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */
  { "CaAlSiO4                ",  -28960.5,	 0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* 019 Dependent species */

  {"aenigmatite"              ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"apatite"                  ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"cordierite"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"corundum"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"cristobalite"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"density"                  ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"diamond"                  ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"enthalpy"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"entropy"                  ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"graphite"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"liquid"                   ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"merwinite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"muscovite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"O2"                       ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"perovskite"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"periclase"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"pseudowollastonite"       ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"quartz"                   ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"rutile"                   ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"S2"                       ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"sphene"                   ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"tridymite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"water"                    ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"whitlockite"              ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"wollastonite"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"wustite"                  ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"caperovskite-sx"          ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"coesite-sx"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"stishovite-sx"            ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"alloy-liquid"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"Fe-liquid"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"Ni-liquid"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"alloy-solid"              ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"Fe-metal"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"Ni-metal"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"amphibole"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"cummingtonite"            ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"grunerite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"tremolite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"biotite"                  ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"annite"                   ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"phlogopite"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"clinopyroxene"            ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"diopside"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"clinoenstatite"           ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"hedenbergite"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"alumino-buffonite"        ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"buffonite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"essenite"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"jadeite"                  ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"feldspar"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"albite"                   ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"anorthite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"sanidine"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"hornblende"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"pargasite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ferropargasite"           ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"magnesiohastingsite"      ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"kalsilite ss"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"na-nepheline"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"k-nepheline"              ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"vc-nepheline"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ca-nepheline"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"leucite ss"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"leucite"                  ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"analcime"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"na-leucite"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"majorite ss"              ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"grossular"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"pyrope"                   ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"almandine"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"majorite"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"melilite"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"akermanite"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"gehlenite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"iron-akermanite"          ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"soda-melilite"            ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"nepheline ss"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"na-nepheline"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"k-nepheline"              ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"vc-nepheline"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ca-nepheline"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"olivine"                  ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"tephroite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"fayalite"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"co-olivine"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ni-olivine"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"monticellite"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"forsterite"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ortho oxide"              ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"pseudobrookite"           ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ferropseudobrookite"      ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"karrooite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"orthopyroxene"            ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"diopside"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"clinoenstatite"           ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"hedenbergite"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"alumino-buffonite"        ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"buffonite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"essenite"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"jadeite"                  ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"perovskite ss"            ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"magnesioperovskite"       ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ferroperovskite"          ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"msg oxide"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"geikielite"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"hematite"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ilmenite"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"pyrophanite"              ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"corundum"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ringwoodite ss"           ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"magnesioringwoodite"      ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ferroringwoodite"         ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"spinel"                   ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"chromite"                 ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"hercynite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"magnetite"                ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"spinel"                   ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ulvospinel"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"wadsleyite ss"            ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"magnesiowadsleyite"       ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ferrowadsleyite"          ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"wustite ss"               ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid phase adjustment     */
  {"magnesiowustite"          ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }, /* Solid component adjustment */
  {"ferrowustite"             ,  0.0,  0.0,  0.0, FALSE, FALSE, FALSE, FALSE }  /* Solid component adjustment */
};

ModelParameters *modelParameters = originalModelParameters;

EosModelParameters eosModelParameters[] = {  /* sets nc entries */
                             /*  Kp   Kpp   Kppp */
  { "SiO2		     ", 0.188587,  1.91476e-05,  6.26232e-10, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "TiO2		     ",  -0.8548,  2.37406e-05, -1.69681e-09, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "Al2O3		     ", 0.720748, -1.22963e-05,   1.7757e-10, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "Fe2O3		     ",-0.516207, -2.77847e-05,  9.13701e-10, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 }, /* -0.516207, -2.77847e-05,  9.13701e-10 */ /*  1.0 */
  { "Cr2O3		     ",   2.8153,  1.05776e-05,  3.40393e-10, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "FeO		     ",  10.8578,  0.000326056, -9.59294e-09, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "MnO		     ",  10.5879,  0.000306443, -1.03951e-08, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "MgO		     ", -2.43032,  0.000271175, -3.12788e-08, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "NiO		     ",  28.8151,   0.00300134,  4.01919e-07, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "CoO		     ",  11.2075,  0.000310096, -1.22111e-08, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "CaO		     ",  18.0476,  0.000891667,  -2.0328e-08, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "Na2O		     ",   22.208,   0.00711102,  3.17635e-06, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "K2O		     ",  4.25535,  0.000752301,  8.46257e-08, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "P2O5		     ",   2.6445,  4.97721e-05,  2.73194e-10, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "H2O		     ",-0.653589, -7.46073e-06,  -8.1586e-12, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "CO2		     ", 0.930718,  4.37796e-06, -4.98837e-10, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "SO3		     ",  2.44963,  4.33544e-05,  9.62372e-11, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "Cl2O-1		     ",  19.2377,   0.00129928,    1.225e-07, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "F2O-1		     ",  3.10454,  6.60495e-05,  7.88912e-10, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 },   
  { "FeO1.3                  ",  1.47474, -7.28951e-05, -2.50008e-09, FALSE, FALSE, FALSE, 0.0, 0.0, 0.0 }  /* 1.47474, -7.28951e-05, -2.50008e-09 */ /* 12.0 */
}; 

int    nCN   = 0;                  /* Total number of coordination states beyond reference            */
#ifdef NEVER_DEFINED
int    nCN   = 2;                  /* Total number of coordination states beyond reference            */
double fCN[] = { 0.8346, 0.7811 }; /* configurational collapse term for IV->V, IV->IV oxygen CN shift */

SsCnModelParameters ssCnModelParameters[] = {           /* sets nc entries, repeated nCN-1 times   */
  { "SiO2		     ",  250000.0,       0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-001 */
  { "TiO2		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-002 */
  { "Al2O3		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-003 */
  { "Fe2O3		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-004 */
  { "Cr2O3		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-005 */
  { "FeO		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-006 */
  { "MnO		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-007 */
  { "MgO		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-008 */
  { "NiO		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-009 */
  { "CoO		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-010 */
  { "CaO		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-011 */
  { "Na2O		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-012 */
  { "K2O		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-013 */
  { "P2O5		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-014 */
  { "H2O		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-015 */
  { "CO2		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-016 */
  { "SO3		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-017 */
  { "Cl2O-1		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-018 */
  { "F2O-1		     ",  250000.0,	 0.0 }, /* oxygen  V-IV delta quantity ( V-IV)-019 */
  { "SiO2		     ",  300000.0,       0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-001 */
  { "TiO2		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-002 */
  { "Al2O3		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-003 */
  { "Fe2O3		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-004 */
  { "Cr2O3		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-005 */
  { "FeO		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-006 */
  { "MnO		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-007 */
  { "MgO		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-008 */
  { "NiO		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-009 */
  { "CoO		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-010 */
  { "CaO		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-011 */
  { "Na2O		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-012 */
  { "K2O		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-013 */
  { "P2O5		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-014 */
  { "H2O		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-015 */
  { "CO2		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-016 */
  { "SO3		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-017 */
  { "Cl2O-1		     ",  300000.0,	 0.0 }, /* oxygen VI-IV delta quantity (VI-IV)-018 */
  { "F2O-1		     ",  300000.0,	 0.0 }  /* oxygen VI-IV delta quantity (VI-IV)-019 */
};

WCnModelParameters wCnModelParameters[] = {             /* sets of nc*(nc-1)/2 entries, repeated nCN times */
 /* Label                        [r][*]-[r] [*][r]-[r] [*][*]-[r]         r = refernce CN, * = current CN  */
  { "W(TiO2      ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-001 */
  { "W(Al2O3     ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-002 */
  { "W(Fe2SiO5   ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-003 */
  { "W(Cr2O3     ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-004 */
  { "W(FeO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-005 */
  { "W(MnO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-006 */
  { "W(MgO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-007 */
  { "W(NiO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-008 */
  { "W(CoO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-009 */
  { "W(CaO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-010 */
  { "W(Na2O      ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-011 */
  { "W(K2O       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-012 */
  { "W(P2O5      ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-013 */
  { "W(H2O       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-014 */
  { "W(CO2       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-015 */
  { "W(SO3       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-016 */
  { "W(Cl2O-1    ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-017 */
  { "W(F2O-1     ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-018 */

  { "W(Al2O3     ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-019 */
  { "W(Fe2SiO5   ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-020 */
  { "W(Cr2O3     ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-021 */
  { "W(FeO       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-022 */
  { "W(MnO       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-023 */
  { "W(MgO       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-024 */
  { "W(NiO       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-025 */
  { "W(CoO       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-026 */
  { "W(CaO       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-027 */
  { "W(Na2O      ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-028 */
  { "W(K2O       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-029 */
  { "W(P2O5      ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-030 */
  { "W(H2O       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-031 */
  { "W(CO2       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-032 */
  { "W(SO3       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-033 */
  { "W(Cl2O-1    ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-034 */
  { "W(F2O-1     ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-035 */

  { "W(Fe2SiO5   ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-036 */
  { "W(Cr2O3     ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-037 */
  { "W(FeO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-038 */
  { "W(MnO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-039 */
  { "W(MgO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-040 */
  { "W(NiO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-041 */
  { "W(CoO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-042 */
  { "W(CaO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-043 */
  { "W(Na2O      ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-044 */
  { "W(K2O       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-045 */
  { "W(P2O5      ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-046 */
  { "W(H2O       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-047 */
  { "W(CO2       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-048 */
  { "W(SO3       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-049 */
  { "W(Cl2O-1    ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-050 */
  { "W(F2O-1     ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-051 */
  
  { "W(Cr2O3     ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-052 */
  { "W(FeO       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-053 */
  { "W(MnO       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-054 */
  { "W(MgO       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-055 */
  { "W(NiO       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-056 */
  { "W(CoO       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-057 */
  { "W(CaO       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-058 */
  { "W(Na2O      ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-059 */
  { "W(K2O       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-060 */
  { "W(P2O5      ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-061 */
  { "W(H2O       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-062 */
  { "W(CO2       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-063 */
  { "W(SO3       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-064 */
  { "W(Cl2O-1    ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-065 */
  { "W(F2O-1     ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-066 */

  { "W(FeO       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-067 */
  { "W(MnO       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-068 */
  { "W(MgO       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-069 */
  { "W(NiO       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-070 */
  { "W(CoO       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-071 */
  { "W(CaO       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-072 */
  { "W(Na2O      ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-073 */
  { "W(K2O       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-074 */
  { "W(P2O5      ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-075 */
  { "W(H2O       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-076 */
  { "W(CO2       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-077 */
  { "W(SO3       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-078 */
  { "W(Cl2O-1    ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-079 */
  { "W(F2O-1     ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-080 */

  { "W(MnO       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-081 */
  { "W(MgO       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-082 */
  { "W(NiO       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-083 */
  { "W(CoO       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-084 */
  { "W(CaO       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-085 */
  { "W(Na2O      ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-086 */
  { "W(K2O       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-087 */
  { "W(P2O5      ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-088 */
  { "W(H2O       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-089 */
  { "W(CO2       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-090 */
  { "W(SO3       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-091 */
  { "W(Cl2O-1    ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-092 */
  { "W(F2O-1     ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-093 */

  { "W(MgO       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-094 */
  { "W(NiO       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-095 */
  { "W(CoO       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-096 */
  { "W(CaO       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-097 */
  { "W(Na2O      ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-098 */
  { "W(K2O       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-099 */
  { "W(P2O5      ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-100 */
  { "W(H2O       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-101 */
  { "W(CO2       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-102 */
  { "W(SO3       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-103 */
  { "W(Cl2O-1    ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-104 */
  { "W(F2O-1     ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-105 */

  { "W(NiO       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-106 */
  { "W(CoO       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-107 */
  { "W(CaO       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-108 */
  { "W(Na2O      ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-109 */
  { "W(K2O       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-110 */
  { "W(P2O5      ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-111 */
  { "W(H2O       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-112 */
  { "W(CO2       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-113 */
  { "W(SO3       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-114 */
  { "W(Cl2O-1    ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-115 */
  { "W(F2O-1     ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-116 */

  { "W(CoO       ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-117 */
  { "W(CaO       ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-118 */
  { "W(Na2O      ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-119 */
  { "W(K2O       ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-120 */
  { "W(P2O5      ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-121 */
  { "W(H2O       ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-122 */
  { "W(CO2       ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-123 */
  { "W(SO3       ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-124 */
  { "W(Cl2O-1    ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-125 */
  { "W(F2O-1     ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-126 */

  { "W(CaO       ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-127 */
  { "W(Na2O      ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-128 */
  { "W(K2O       ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-129 */
  { "W(P2O5      ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-130 */
  { "W(H2O       ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-131 */
  { "W(CO2       ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-132 */
  { "W(SO3       ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-133 */
  { "W(Cl2O-1    ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-134 */
  { "W(F2O-1     ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-135 */

  { "W(Na2O      ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-136 */
  { "W(K2O       ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-137 */
  { "W(P2O5      ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-138 */
  { "W(H2O       ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-139 */
  { "W(CO2       ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-140 */
  { "W(SO3       ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-141 */
  { "W(Cl2O-1    ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-142 */
  { "W(F2O-1     ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-143 */

  { "W(K2O       ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-144 */
  { "W(P2O5      ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-145 */
  { "W(H2O       ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-146 */
  { "W(CO2       ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-147 */
  { "W(SO3       ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-148 */
  { "W(Cl2O-1    ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-149 */
  { "W(F2O-1     ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-150 */

  { "W(P2O5      ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-151 */
  { "W(H2O       ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-152 */
  { "W(CO2       ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-153 */
  { "W(SO3       ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-154 */
  { "W(Cl2O-1    ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-155 */
  { "W(F2O-1     ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-156 */

  { "W(H2O       ,P2O5      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-157 */
  { "W(CO2       ,P2O5      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-158 */
  { "W(SO3       ,P2O5      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-159 */
  { "W(Cl2O-1    ,P2O5      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-160 */
  { "W(F2O-1     ,P2O5      )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-161 */

  { "W(CO2       ,H2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-162 */
  { "W(SO3       ,H2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-163 */
  { "W(Cl2O-1    ,H2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-164 */
  { "W(F2O-1     ,H2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-165 */

  { "W(SO3       ,CO2       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-166 */
  { "W(Cl2O-1    ,CO2       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-167 */
  { "W(F2O-1     ,CO2       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-168 */

  { "W(Cl2O-1    ,SO3       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-169 */
  { "W(F2O-1     ,SO3       )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-170 */

  { "W(F2O-1     ,Cl2O-1    )", {	0.0,	   0.0,       0.0 } }, /* oxygen  V-IV delta quantity ( V-IV)-171 */

  { "W(TiO2      ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-001 */
  { "W(Al2O3     ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-002 */
  { "W(Fe2SiO5   ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-003 */
  { "W(Cr2O3     ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-004 */
  { "W(FeO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-005 */
  { "W(MnO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-006 */
  { "W(MgO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-007 */
  { "W(NiO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-008 */
  { "W(CoO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-009 */
  { "W(CaO       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-010 */
  { "W(Na2O      ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-011 */
  { "W(K2O       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-012 */
  { "W(P2O5      ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-013 */
  { "W(H2O       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-014 */
  { "W(CO2       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-015 */
  { "W(SO3       ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-016 */
  { "W(Cl2O-1    ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-017 */
  { "W(F2O-1     ,SiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-018 */

  { "W(Al2O3     ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-019 */
  { "W(Fe2SiO5   ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-020 */
  { "W(Cr2O3     ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-021 */
  { "W(FeO       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-022 */
  { "W(MnO       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-023 */
  { "W(MgO       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-024 */
  { "W(NiO       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-025 */
  { "W(CoO       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-026 */
  { "W(CaO       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-027 */
  { "W(Na2O      ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-028 */
  { "W(K2O       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-029 */
  { "W(P2O5      ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-030 */
  { "W(H2O       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-031 */
  { "W(CO2       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-032 */
  { "W(SO3       ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-033 */
  { "W(Cl2O-1    ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-034 */
  { "W(F2O-1     ,TiO2      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-035 */

  { "W(Fe2SiO5   ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-036 */
  { "W(Cr2O3     ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-037 */
  { "W(FeO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-038 */
  { "W(MnO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-039 */
  { "W(MgO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-040 */
  { "W(NiO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-041 */
  { "W(CoO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-042 */
  { "W(CaO       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-043 */
  { "W(Na2O      ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-044 */
  { "W(K2O       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-045 */
  { "W(P2O5      ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-046 */
  { "W(H2O       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-047 */
  { "W(CO2       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-048 */
  { "W(SO3       ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-049 */
  { "W(Cl2O-1    ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-050 */
  { "W(F2O-1     ,Al2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-051 */
  
  { "W(Cr2O3     ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-052 */
  { "W(FeO       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-053 */
  { "W(MnO       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-054 */
  { "W(MgO       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-055 */
  { "W(NiO       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-056 */
  { "W(CoO       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-057 */
  { "W(CaO       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-058 */
  { "W(Na2O      ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-059 */
  { "W(K2O       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-060 */
  { "W(P2O5      ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-061 */
  { "W(H2O       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-062 */
  { "W(CO2       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-063 */
  { "W(SO3       ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-064 */
  { "W(Cl2O-1    ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-065 */
  { "W(F2O-1     ,Fe2SiO5   )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-066 */

  { "W(FeO       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-067 */
  { "W(MnO       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-068 */
  { "W(MgO       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-069 */
  { "W(NiO       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-070 */
  { "W(CoO       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-071 */
  { "W(CaO       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-072 */
  { "W(Na2O      ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-073 */
  { "W(K2O       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-074 */
  { "W(P2O5      ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-075 */
  { "W(H2O       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-076 */
  { "W(CO2       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-077 */
  { "W(SO3       ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-078 */
  { "W(Cl2O-1    ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-079 */
  { "W(F2O-1     ,Cr2O3     )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-080 */

  { "W(MnO       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-081 */
  { "W(MgO       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-082 */
  { "W(NiO       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-083 */
  { "W(CoO       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-084 */
  { "W(CaO       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-085 */
  { "W(Na2O      ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-086 */
  { "W(K2O       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-087 */
  { "W(P2O5      ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-088 */
  { "W(H2O       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-089 */
  { "W(CO2       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-090 */
  { "W(SO3       ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-091 */
  { "W(Cl2O-1    ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-092 */
  { "W(F2O-1     ,FeO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-093 */

  { "W(MgO       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-094 */
  { "W(NiO       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-095 */
  { "W(CoO       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-096 */
  { "W(CaO       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-097 */
  { "W(Na2O      ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-098 */
  { "W(K2O       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-099 */
  { "W(P2O5      ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-100 */
  { "W(H2O       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-101 */
  { "W(CO2       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-102 */
  { "W(SO3       ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-103 */
  { "W(Cl2O-1    ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-104 */
  { "W(F2O-1     ,MnO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-105 */

  { "W(NiO       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-106 */
  { "W(CoO       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-107 */
  { "W(CaO       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-108 */
  { "W(Na2O      ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-109 */
  { "W(K2O       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-110 */
  { "W(P2O5      ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-111 */
  { "W(H2O       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-112 */
  { "W(CO2       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-113 */
  { "W(SO3       ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-114 */
  { "W(Cl2O-1    ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-115 */
  { "W(F2O-1     ,MgO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-116 */

  { "W(CoO       ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-117 */
  { "W(CaO       ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-118 */
  { "W(Na2O      ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-119 */
  { "W(K2O       ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-120 */
  { "W(P2O5      ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-121 */
  { "W(H2O       ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-122 */
  { "W(CO2       ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-123 */
  { "W(SO3       ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-124 */
  { "W(Cl2O-1    ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-125 */
  { "W(F2O-1     ,NiO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-126 */

  { "W(CaO       ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-127 */
  { "W(Na2O      ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-128 */
  { "W(K2O       ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-129 */
  { "W(P2O5      ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-130 */
  { "W(H2O       ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-131 */
  { "W(CO2       ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-132 */
  { "W(SO3       ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-133 */
  { "W(Cl2O-1    ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-134 */
  { "W(F2O-1     ,CoO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-135 */

  { "W(Na2O      ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-136 */
  { "W(K2O       ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-137 */
  { "W(P2O5      ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-138 */
  { "W(H2O       ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-139 */
  { "W(CO2       ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-140 */
  { "W(SO3       ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-141 */
  { "W(Cl2O-1    ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-142 */
  { "W(F2O-1     ,CaO       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-143 */

  { "W(K2O       ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-144 */
  { "W(P2O5      ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-145 */
  { "W(H2O       ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-146 */
  { "W(CO2       ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-147 */
  { "W(SO3       ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-148 */
  { "W(Cl2O-1    ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-149 */
  { "W(F2O-1     ,Na2O      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-150 */

  { "W(P2O5      ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-151 */
  { "W(H2O       ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-152 */
  { "W(CO2       ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-153 */
  { "W(SO3       ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-154 */
  { "W(Cl2O-1    ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-155 */
  { "W(F2O-1     ,K2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-156 */

  { "W(H2O       ,P2O5      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-157 */
  { "W(CO2       ,P2O5      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-158 */
  { "W(SO3       ,P2O5      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-159 */
  { "W(Cl2O-1    ,P2O5      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-160 */
  { "W(F2O-1     ,P2O5      )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-161 */

  { "W(CO2       ,H2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-162 */
  { "W(SO3       ,H2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-163 */
  { "W(Cl2O-1    ,H2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-164 */
  { "W(F2O-1     ,H2O       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-165 */

  { "W(SO3       ,CO2       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-166 */
  { "W(Cl2O-1    ,CO2       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-167 */
  { "W(F2O-1     ,CO2       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-168 */

  { "W(Cl2O-1    ,SO3       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-169 */
  { "W(F2O-1     ,SO3       )", {	0.0,	   0.0,       0.0 } }, /* oxygen VI-IV delta quantity (VI-IV)-170 */

  { "W(F2O-1     ,Cl2O-1    )", {	0.0,	   0.0,       0.0 } }  /* oxygen VI-IV delta quantity (VI-IV)-171 */
};
#endif /* NEVER_DEFINED */

#endif /* _Param_Struct_Data_h */
