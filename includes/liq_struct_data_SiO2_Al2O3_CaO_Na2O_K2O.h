#ifndef _Liq_Struct_Data_h
#define _Liq_Struct_Data_h

/*
MELTS Source Code: RCS $Log:$
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Include file for initializing liquid data structure
**        (file LIQ_STRUCT_DATA.H)
**--
*/

/* 
 *==============================================================================
 */

/* Lange and Carmichael linear mixing coefficients */

/* J/K */
#define LNCpSiO2   82.6
#define LNCpAl2O3 170.3
#define LNCpCaO    89.8
#define LNCpNa2O   97.6
#define LNCpK2O    98.5

/* Molecular Weights of Oxides */
#define MWSiO2   60.0848
#define MWAl2O3 101.9612
#define MWCaO    56.0794
#define MWNa2O   61.9790
#define MWK2O    94.2034
#define MWH2O    18.01534

/*=================================================================*/
/*EOS parameters (in J/bar-*) or (m/sec-*)                         */
/*=================================================================*/
 
#define GKVSiO2        (2.6710)
#define GKVAl2O3       (3.7616)
#define GKVCaO         (1.6671)
#define GKVNa2O        (2.9117)
#define GKVK2O         (4.6401)
 
#define GKdVdTSiO2     ( 1.007e-4)
#define GKdVdTAl2O3    (-0.649e-4)
#define GKdVdTCaO      ( 3.143e-4)
#define GKdVdTNa2O     ( 6.077e-4)
#define GKdVdTK2O      (10.432e-4)
 
#define GKcSiO2        (2321.75)
#define GKcAl2O3       (2738.35)
#define GKcCaO	       (3967.42)
#define GKcNa2O        (3080.69)
#define GKcK2O	       (1682.35)

#define GKcXX          (5800.72) /* Na2O - Al2O3 cross term */
 
#define GKdcdTSiO2     ( 0.39934)
#define GKdcdTAl2O3    ( 0.50394)
#define GKdcdTCaO      (-0.20526)
#define GKdcdTNa2O     (-2.16757)
#define GKdcdTK2O      (-2.34406)
 
/*
  Entries for d2Vdp2, d3vdp3, and d4vdp4 listed immediately below are from Part IV
  These quantities are overwritten in melts_support.c in favor of entries from the 
  EosModelParameters structure that are initialized in params_struct_data.h.  
  EOS parameters are expressed in that file in terms of K', K'', and K'''.
  NOTE that the endmember liquid component EOS parameters (liquids structure)are NOT 
  modified in melts_support.c; only the oxide coefficients (bulkSystem structure) are 
  changed.
*/ 
 
#define GKd2VdP2SiO2   ( 0.219950e-9)
#define GKd2VdP2Al2O3  ( 0.157380e-9)
#define GKd2VdP2CaO    ( 0.284390e-9)
#define GKd2VdP2Na2O   ( 3.429800e-9)
#define GKd2VdP2K2O    (11.154000e-9) /*  Fusion curve, Part IV value is (21.300000e-9) */
 
#define GKd3VdP3SiO2   (  0.010220e-13)
#define GKd3VdP3Al2O3  ( -0.030193e-13)
#define GKd3VdP3CaO    ( -0.182580e-13)
#define GKd3VdP3Na2O   ( -0.588340e-13)
#define GKd3VdP3K2O    ( -6.721000e-13) /* Fusion curve, Part IV value is (-31.307000e-13) */
 
#define GKd4VdP4SiO2   ( -0.00025985e-17)
#define GKd4VdP4Al2O3  (  0.00919470e-17)
#define GKd4VdP4CaO    (  0.04328500e-17)
#define GKd4VdP4Na2O   ( -2.35100000e-17)
#define GKd4VdP4K2O    (-16.09000000e-17) /* Fusion curve, Part IV value is (32.00400000e-17) */

#define KPRIMEH2O      (5.0)

BulkSystem bulkSystem[] = { /* 3rd coefficient converts FeO(T) -> FeO, Fe2O3 */
  { "SiO2"  , OTHER,  0.0,   MWSiO2  , NULL, NULL, GKVSiO2    , GKdVdTSiO2    , GKcSiO2 ,  0.0  , GKdcdTSiO2 ,  LNCpSiO2    , GKd2VdP2SiO2    , GKd3VdP3SiO2	, GKd4VdP4SiO2     },
  { "Al2O3" , OTHER, -2.243, MWAl2O3 , NULL, NULL, GKVAl2O3   , GKdVdTAl2O3   , GKcAl2O3,  0.0  , GKdcdTAl2O3,  LNCpAl2O3   , GKd2VdP2Al2O3   , GKd3VdP3Al2O3	, GKd4VdP4Al2O3    },
  { "CaO"   , OTHER,  3.201, MWCaO   , NULL, NULL, GKVCaO     , GKdVdTCaO     , GKcCaO  ,  0.0  , GKdcdTCaO  ,  LNCpCaO     , GKd2VdP2CaO     , GKd3VdP3CaO	, GKd4VdP4CaO	   },
  { "Na2O"  , OTHER,  5.854, MWNa2O  , NULL, NULL, GKVNa2O    , GKdVdTNa2O    , GKcNa2O ,  GKcXX, GKdcdTNa2O ,  LNCpNa2O    , GKd2VdP2Na2O    , GKd3VdP3Na2O	, GKd4VdP4Na2O     },
  { "K2O"   , OTHER,  6.215, MWK2O   , NULL, NULL, GKVK2O     , GKdVdTK2O     , GKcK2O  ,  0.0  , GKdcdTK2O  ,  LNCpK2O     , GKd2VdP2K2O     , GKd3VdP3K2O	, GKd4VdP4K2O	   },
  { "H2O"   , OTHER,  0.0,   MWH2O   , NULL, NULL, 0.0        , 0.0           , 0.0     ,  0.0  , 0.0        ,  0.0         , 0.0             , 0.0             , 0.0              },
  { "dummy" , OTHER,  0.0,   0.0     , NULL, NULL, 0.0        , 0.0           , 0.0     ,  0.0  , 0.0        ,  0.0         , 0.0             , 0.0             , 0.0              }
};
int nc = ((sizeof bulkSystem / sizeof(struct _bulkSystem))-1);

Liquid xMeltsLiquid[] = {
  /* Solid:  beta-cristobalite, Berman 1988                                   */
  /* Liquid: Fusion entropy, Richet et al., 1982                              */
#define SCALE 2.0
  {"(SiO2)2", NULL, 
    {            
      -906377.0*SCALE, 46.029*SCALE, 0.0,       
      CP_BERMAN,  {{83.51*SCALE, -3.747E2*SCALE, -24.554E5*SCALE, 28.007E7*SCALE, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{     
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1999.0, 4.46*SCALE, 0.0, 0.0 	
    }
  },
#undef SCALE
  /* Solid:  corundum, Berman 1988                                            */
  /* Liquid: Fusion entropy, Richet and Bottinga, 1984                        */
  {"Al2O3", NULL,
    {          
      -1675700.0, 50.82, 0.0,	
      CP_BERMAN,  {{155.02, -8.284E2, -38.614E5, 40.908E7, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{    
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      2320.0, 46.3, 0.0, 0.0
    }
  },
  /* Solid:  alpha larnite, Robie et al. 1978                                 */
  /* Liquid: Fusion entropy, guess                                            */  
#define SCALE     0.666666666666
#define sqrtSCALE 0.8164965809
  {"(Ca2SiO4)0.666666666666", NULL,                          /* alpha larnite */
    {
      -2326361.0*SCALE, 94.51*SCALE, 0.0,
      CP_BERMAN,  {{209.68*SCALE, -7.019e2*SCALE, -79.894e5*SCALE, 129.748e7*SCALE, 1710.0, 11903.0*SCALE, -22.815e-2, 23.196e-5}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      2403.0, 75.74*SCALE, 0.0, 0.0 		 
    }
  },
#undef sqrtSCALE
#undef SCALE
  /* Solid:                                                                  */
  /* Liquid: H and S from Yazhenskikh et al. (2008)                          */
  {"Na2O", NULL, 
    {               
      -570284.0, 108.989, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                    */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      298.15, 0.0, 0.0, 0.0 	
    }
  },
  /* Solid:                                                                  */
  /* Liquid: H and S from Yazhenskikh et al. (2008)                          */
  {"(K2SiO3)0.666666666666", NULL,
    {
      -1012800.0, 119.31, 0.0,             
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      298.15, 0.0, 0.0, 0.0
    }
  },
  /* Volumetric properties from Ochs & Lange, 1997                           */
  {"H2O", NULL,
    {
      0.0, 0.0, 0.0,
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{     
      2.775,
      EOS_KRESS, {{10.86e-4, -6.00e-5, 0.0, KPRIMEH2O}},
      1673.15, 0.0, 0.0, 0.0 
    }
  },
  /* Liquid:  estiamte                                                        */
  {"(CaAl2O4)0.666666666666 = 0.5 (Ca2SiO4)0.666666666666 0.666666666666 Al2O3 -0.166666666666 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid:  estiamte is taken from SiO2, Al2O3 and Na2SiO3                  */
  {"(NaAlSiO4)0.666666666666 = 0.416666666666 (Na4SiO4)0.4 0.333333333333 Al2O3 0.25 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid:  estiamte is taken from SiO2, Al2O3 and K2SiO3                   */
  {"(KAlSiO4)0.666666666666 = 0.5 (K2SiO3)0.666666666666 0.333333333333 Al2O3 0.166666666666 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid:  estiamte is taken from SiO2, Al2O3 and Ca2SiO4                  */
  {"(CaAl2Si2O8)0.4 = 0.3 (Ca2SiO4)0.666666666666 0.4 Al2O3 0.3 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid:  estiamte                                                        */
  {"(KAlSi4O10)0.333333333333 = 0.25 (K2SiO3)0.666666666666 0.166666666667 Al2O3 0.583333333333 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid: guess: H and S from Fig 4 Ihlinger et al.                        */
  /* Volumetric properties from Ochs & Lange, 1997                            */
#define SCALE 1.6
  {"(Si0.25OH)1.6", NULL,
    {               
      9500.0*SCALE, 12.0*SCALE, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{ 
      (GKVSiO2/4.0+2.775/2.0)*SCALE,
      EOS_KRESS, {{10.86e-4, -6.00e-5, 0.0, KPRIMEH2O}},
      1673.15, 0.0, 0.0, 0.0
    }
  },
#undef SCALE
  /* Liquid: guess: H and S from Fig 4 Ihlinger et al.                        */
  /* Volumetric properties from Ochs & Lange, 1997                            */
#define SCALE 1.5
  {"(Al0.33OH)1.5", NULL,
    {               
      9500.0*SCALE, 12.0*SCALE, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{ 
      (GKVAl2O3/6.0+2.775/2.0)*SCALE,
      EOS_KRESS, {{10.86e-4, -6.00e-5, 0.0, KPRIMEH2O}},
      1673.15, 0.0, 0.0, 0.0
    }
  },
#undef SCALE
   /* Liquid: guess: H and S from Fig 4 Ihlinger et al.                       */
  /* Volumetric properties from Ochs & Lange, 1997                            */
#define SCALE 1.33333333333
  {"(Ca0.5OH)1.33333333333", NULL,
    {               
      9500.0*SCALE, 12.0*SCALE, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{ 
      (GKVCaO/2.0+2.775/2.0)*SCALE,
      EOS_KRESS, {{10.86e-4, -6.00e-5, 0.0, KPRIMEH2O}},
      1673.15, 0.0, 0.0, 0.0
    }
  },
#undef SCALE
   /* Liquid: guess: H and S from Fig 4 Ihlinger et al.                        */
  /* Volumetric properties from Ochs & Lange, 1997                            */
  {"(NaOH)1", NULL,
    {               
      9500.0, 12.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{ 
      GKVNa2O/2.0+2.775/2.0,
      EOS_KRESS, {{10.86e-4, -6.00e-5, 0.0, KPRIMEH2O}},
      1673.15, 0.0, 0.0, 0.0
    }
  },
   /* Liquid: guess: H and S from Fig 4 Ihlinger et al.                        */
  /* Volumetric properties from Ochs & Lange, 1997                            */
  {"(KOH)1", NULL,
    {               
      9500.0, 12.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{ 
      GKVK2O/2.0+2.775/2.0,
      EOS_KRESS, {{10.86e-4, -6.00e-5, 0.0, KPRIMEH2O}},
      1673.15, 0.0, 0.0, 0.0
    }
  },
  /* Solid:                                                                   */
  /* Liquid: Yazhenskikh et al. (2008)                                        */  
  {"(Na2SiO3)0.666666666666", NULL, 
    {               
      -1009578.2+14757.0, 93.25-10.20, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      298.15, 0.0, 0.0, 0.0 	
    }
  },
  /* Liquid: Yazhenskikh et al. (2008)                                        */  
  {"NaAlO2", NULL,
    {
      -1045111.6, 96.86, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      298.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid: Yazhenskikh et al. (2008)                                        */  
  {"KAlO2 = 0.75 (K2SiO3)0.666666666666 0.5 Al2O3 -0.25 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid: Yazhenskikh et al. (2008)                                        */  
  {"(Na2Si2O5)0.5", NULL,
    {
      -1222471.3+15382.0, 91.60-21.515, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      298.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid: Yazhenskikh et al. (2008)                                        */  
  {"(K2Si2O5)0.5", NULL,
    {
      -1248200.0, 95.09, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      298.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid: Yazhenskikh et al. (2008)                                        */  
  {"(K2Si4O9)0.333333333333", NULL,
    {
      -1431900.0, 89.72, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      298.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid:  estiamte                                                        */
  {"(K4Al2Si4O13)0.2 = 0.6 (K2SiO3)0.666666666666 0.2 Al2O3 0.2 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid: Yazhenskikh et al. (2008)                                        */  
  {"(Al6Si2O13)0.25", NULL,
    {
      -1600000.0, 99.430, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      298.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Solid:                                                                  */
  /* Liquid: H and S from Yazhenskikh et al. (2008)                          */
  {"(Na4SiO4)0.4", NULL, 
    {               
      -804302.5-20704.0, 104.91-11.49, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                    */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      298.15, 0.0, 0.0, 0.0 	
    }
  },
  /* Solid:                                                                  */
  /* Liquid: H and S from Yazhenskikh et al. (2008)                          */
  {"(Na2Si4O9)0.333333333333", NULL, 
    {               
      -804302.5-615055.0, 104.91-47.79, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                    */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      298.15, 0.0, 0.0, 0.0 	
    }
  }, 
  /* Liquid:  estiamte is taken from SiO2, Al2O3 and Na2SiO3                  */
  {"(Na4Al2SiO7)0.285714286 = 0.714285714 (Na4SiO4)0.4 0.285714286 Al2O3", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid:  estiamte is taken from SiO2, Al2O3 and Na2SiO3                  */
  {"(Na2Al4SiO9)0.285714286 = 0.357142857 (Na4SiO4)0.4 0.571428571 Al2O3 0.071428571 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid:  estiamte is taken from SiO2, Al2O3 and Na2SiO3                  */
  {"(NaAlSi4O10)0.333333333333 = 0.208333333 (Na4SiO4)0.4 0.166666667 Al2O3 0.625 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },  
  {"(K2Al4Si2O11)0.25 = 0.375 (K2SiO3)0.666666666666 0.5 Al2O3 0.125 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid:  estiamte is taken from SiO2, Al2O3 and K2SiO3                   */
  {"(KAlSi2O6)0.5 = 0.375 (K2SiO3)0.666666666666 0.25 Al2O3 0.375 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid:  estiamte is taken from SiO2, Al2O3 and K2SiO3                   */
  {"(K4Al2Si8O21)0.1428571429 = 0.4285714286 (K2SiO3)0.666666666666 0.1428571429 Al2O3 0.4285714286 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid:  estiamte is taken from SiO2, Al2O3 and K2SiO3                   */
  {"(K4Al2Si6O37)0.090909090909 = 0.272727272727 (K2SiO3)0.666666666666 0.090909090909 Al2O3 0.636363636363 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid:  estiamte is taken from SiO2, Al2O3 and K2SiO3                   */
  {"(K2Al4Si4O15)0.2 = 0.3 (K2SiO3)0.666666666666 0.4 Al2O3 0.3 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Liquid:  estiamte is taken from SiO2, Al2O3 and K2SiO3                   */
  {"(K2Al4Si8O23)0.1428571429 = 0.2142857143 (K2SiO3)0.666666666666 0.2857142857 Al2O3 0.5 (SiO2)2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  }
};

int    nlc     = (sizeof xMeltsLiquid / sizeof(struct _liquid)) - 29;
int    nls     = (sizeof xMeltsLiquid / sizeof(struct _liquid));
Liquid *liquid = xMeltsLiquid;

Liquid meltsLiquid[] = {
  {"SiO2"     , NULL,        /* Solid Properties are beta-cristobalite        */
    {                        /* ThermoRef structure block                     */
    -906377.0,  	     /* H ref (J)			Berman (1988) */
    46.029,		     /* S ref (J/K)			Berman (1988) */
    2.730,		     /* V ref (J/bar)			Berman (1988) */
    CP_BERMAN,  {{83.51, -3.747e2, -24.554e5, 28.007e7, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    2.690,		     /* V liq (J) 	Lange and Carmichael (1990)   */
    EOS_KRESS, {{0.0, -1.89e-5, 1.3e-8, 3.6e-10}},
    1999.0,		     /* T fusion (K)				      */
    4.46,		     /* S fusion (J/K)  	 Richet et al. (1982) */
    82.6,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"TiO2"     , NULL,
    {                        /* ThermoRef structure block                     */
    -944750.0,  	     /* H ref (J)			Berman (1988) */
    50.460,		     /* S ref (J)			Berman (1988) */
    1.882,		     /* V ref (J/bar)			Berman (1988) */
    CP_BERMAN,  {{77.84, 0.0, -33.678e5, 40.294e7, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    2.316,		     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{7.246e-4, -2.310e-5, 0.0, 5.0e-10}},
    1870.0,		     /* T fusion (K)  Oxide Handbook: Samsonov (1982) */
    35.824,		     /* S fusion (J/K)  	      Samsonov (1982) */
    109.2,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)         1246.67 Guess */
    }
  },
  {"Al2O3"    , NULL,
    {                        /* ThermoRef structure block                     */
    -1675700.0, 	     /* H ref (J)			Berman (1988) */
    50.82,		     /* S ref (J/K)			Berman (1988) */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{155.02, -8.284E2, -38.614E5, 40.908E7, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    3.711,		     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{2.62e-4, -2.26e-5, 2.7e-8, 4.0e-10}},
    2319.65,		     /* T fusion (K)  Oxide Handbook: Samsonov (1982) */
    48.61,		     /* S fusion (J/K)  	      Samsonov (1982) */
    170.3,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)         1551.33  Guess */
    }
  },
  {"Fe2O3"    , NULL,
    {                        /* ThermoRef structure block                     */
    -822000.0,  	     /* H ref (J)		       Ghiorso (1990) */
    87.40,		     /* S ref (J/K)		       Ghiorso (1990) */
    3.027,		     /* V ref (J/bar)			Berman (1988) */
    CP_BERMAN,  {{146.86, 0.0, -55.768E5, 52.563E7, 955.0, 1287.0, -7.403E-2, 27.921E-5}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    4.213,		     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{9.09E-4, -2.53E-5, 3.1E-8, 4.4e-10}},
    1895.0,		     /* T fusion (K)		  Robie et al. (1978) */
    60.41,		     /* S fusion (J/K) Robie et al. (1978) Fe3O4 - FeO*/
    240.9,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)         1263.33  Guess */
    }
  },
  {"MgCr2O4"  , NULL,
    {                        /* ThermoRef structure block                     */
    -1783640.0, 	     /* H ref (J)	      Sack and Ghiorso (1991) */
    106.02,		     /* S ref (J/K)	      Sack and Ghiorso (1991) */
    4.3560,		     /* V ref (J/bar)		  Robie et al. (1978) */
    CP_BERMAN,  {{201.981, -5.519E2, -57.844E5, 57.729E7, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    5.358,		     /* V liq (J) Lange and Carmichael (1990) MgFe2O4 */
    EOS_KRESS, {{11.71e-4, -2.26e-5, 1.8e-8, 4.67e-10}},
    2673.15,		     /* T fusion (K)	 Phase diagrams for ceramists */
    73.22,		     /* S fusion (J/K)  			Guess */
    335.1,		     /* Cp liquid (J/K) Lange & Navrot. (1992)MgFe2O3 */
    0.0 		     /* T glass transition (K)  	1782.10 Guess */
    }
  },
  {"Fe2SiO4"  , NULL,
    {                        /* ThermoRef structure block                     */
    -1479360.0, 	     /* H ref (J)			Berman (1988) */
    150.930,		     /* S ref (J/K)			Berman (1988) */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{248.93, -19.239E2, 0.0, -13.910E7, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    5.420,		     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{5.84e-4, -2.79e-5, -2.3e-8, 14.6e-10}},
    1490.0,		     /* T fusion (K)	       Stebbins et al. (1984) */
    59.9,		     /* S fusion (J/K)         Stebbins et al. (1984) */
    240.2,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)  	 933.33 Guess */
    }
  },
  {"MnSi0.5O2"  , NULL,
    {                        /* ThermoRef structure block                     */
    -1732000.0/2.0,	     /* H ref (J)				      */
    155.9/2.0,  	     /* S ref (J/K)		  Robie et al. (1982) */
    4.889/2.0,        /* V ref (J/bar)  		  HIRSCHMANN IN PREP  */
    CP_BERMAN,  {{219.89/2.0, -12.710E2/2.0,-20.496E5/2.0, 17.652E7/2.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    2.84,		     /* V liq (J)				      */
    EOS_KRESS, {{5.84e-4/2.0, -2.79e-5/2.0, -2.3e-8/2.0, 14.6e-10/2.0}},
    1620.0,		     /* T fusion (K)			   Mah (1960) */
    27.6,		     /* S fusion (J/K)  		   Mah (1960) */
    121.6,		     /* Cp liquid (J/K) 		   Mah (1960) */
    0.0 		     /* T glass transition (K)         1080.00  Guess */
    }
  },
  {"Mg2SiO4"  , NULL,
    {                        /* ThermoRef structure block                     */
    -2174420.0, 	     /* H ref (J)			Berman (1988) */
    94.010,		     /* S ref (J/K)			Berman (1988) */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{238.64, -20.013E2, 0.0, -11.624E7, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    4.980,		     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{5.24e-4, -1.35e-5, -1.3e-8, 4.14e-10}},
    2163.0,		     /* T fusion (K)	    Bowen and Anderson (1914) */
    57.2,		     /* S fusion (J/K)  corr: Navrotsky et al. (1989) */
    271.0,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)  	1442.00 Guess */
    }
  },
  {"NiSi0.5O2"  , NULL,
    {                        /* ThermoRef structure block                     */
    -1395300.0/2.0,	     /* H ref (J)		    Hirschmann (1993) */
    128.1/2.0,  	     /* S ref (J/K)		    Hirschmann (1993) */
    4.259/2.0,  	     /* V ref (J/bar)		    Hirschmann (1993) */
    CP_BERMAN,  {{214.997/2.0, -10.3075E2/2.0, -49.4453E5/2.0, 62.375E7/2.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    2.48,		     /* V liq (J)				      */
    EOS_KRESS, {{5.84e-4/2.0, -2.79e-5/2.0, -2.3e-8/2.0, 14.6e-10/2.0}},
    1923.0,		     /* T fusion (K)				      */
    29.0,		     /* S fusion (J/K)  			      */
    119.3,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"CoSi0.5O2"  , NULL,
    {                        /* ThermoRef structure block                     */
    -1414100.0/2.0,	     /* H ref (J)		 HIRSCHMANN, in press */
    142.6/2.0,  	     /* S ref (J/K)		 HIRSCHMANN, in press */
    4.459/2.0,  	     /* V ref (J/bar)		 HIRSCHMANN, in press */
    CP_BERMAN,  {{201.048/2.0, -0.369E2/2.0, -71.81E5/2.0, 90.05E7/2.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    2.30,		     /* V liq (J)				      */
    EOS_KRESS, {{5.84e-4/2.0, -2.79e-5/2.0, -2.3e-8/2.0, 14.6e-10/2.0}},
    1688.0,		     /* T fusion (K)				      */
    29.0,		     /* S fusion (J/K)  			      */
    125.3,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"CaSiO3"   , NULL,
    {                        /* ThermoRef structure block                     */
    -1627427.0, 	     /* H ref (J) (Pseudowallostonite)  Berman (1988) */
    85.279,		     /* S ref (J/K)			Berman (1988) */
    4.016,		     /* V ref (J/bar)			Berman (1988) */
    CP_BERMAN,  {{141.16, -4.172e2, -58.576e5, 94.074e7, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    4.347,		     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{2.92e-4, -1.55e-5, -1.6e-8, 3.89e-10}},
    1817.0,		     /* T fusion (K)		  Adamkovicova (1980) */
    31.5,		     /* S fusion (J/K)  	  Adamkovicova (1980) */
    172.4,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)  	1211.33 Guess */
    }
  },
  {"Na2SiO3"  , NULL,
    {                        /* ThermoRef structure block                     */
    -373190.0*4.184,	     /* H ref (J)	     Stull and Prophet (1971) */
    27.21*4.184,	     /* S ref (J/K)	     Stull and Prophet (1971) */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{234.77, -22.189E2, 0.0, 13.530E7, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    5.568,		     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{7.41e-4, -4.29e-5, -5.3e-8, 8.4e-10}},
    1361.0,		     /* T fusion (K)	       Stebbins et al. (1984) */
    38.34,		     /* S fusion (J/K)         Stebbins et al. (1984) */
    180.2,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)  	907.33  Guess */
    }
  },
  {"KAlSiO4"  , NULL,
    {                        /* ThermoRef structure block                     */
    -2111813.55,	     /* H ref (J)		    Berman (pers com) */
    133.9653,		     /* S ref (J/K)		    Berman (pers com) */
    5.989,		     /* V ref (J/bar)		    Berman (pers com) */
    CP_BERMAN,  {{186.0, 0.0, -131.067E5, 213.893E7, 800.15, 1154.0, -7.096454E-2, 21.682E-5}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    6.8375,		     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{7.265e-4, -6.395e-5, -4.6e-8, 12.1e-10}},
    2023.15,		     /* T fusion (K)   Morse (phase diagram page 257) */
    24.5,		     /* S fusion (J/K) Guess - Stebbins et al. (1984) */
    217.0,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)         1348.77  Guess */
    }
  },
  {"Ca3(PO4)2", NULL,
    {                        /* ThermoRef structure block                     */
    -4097169.0, 	     /* H ref (J)	Zhu and Sverjensky (in press) */
    235.978,		     /* S ref (J/K)	   Southard and Milner (1935) */
    9.7620,		     /* V ref (J/bar)		  Robie et al. (1978) */
    CP_BERMAN,  {{402.997, -28.0835E2, 0.0, -32.6230E7, 1373.0, 14059.0, 2.5427E-2, 19.255E-5}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    10.7382,		     /* V liq (J)	1.1 times the volume of solid */
    EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
    1943.15,		     /* T fusion (K)	 Handbook of Chem and Physics */
    35.690,		     /* S fusion (J/K) ave of Mg3(PO4)2 and Ba3(PO4)2 */
    574.67,		     /* Cp liquid (J/K)       from Ca2P2O7 and CaP2O6 */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"CO2"      , NULL,
    {                        /* ThermoRef structure block                     */
    0.0,		     /* H ref (J)				      */
    0.0,		     /* S ref (J/K)				      */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    0.0,		     /* V liq (J)				      */
    EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
    1000.0,		     /* T fusion (K) dummy			      */
    0.0,		     /* S fusion (J/K)  			      */
    0.0,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"SO3"	 , NULL,
    {                        /* ThermoRef structure block                     */
    0.0,		     /* H ref (J)				      */
    0.0,		     /* S ref (J/K)				      */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    0.0,		     /* V liq (J)				      */
    EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
    1000.0,		     /* T fusion (K) dummy			      */
    0.0,		     /* S fusion (J/K)  			      */
    0.0,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"Cl2O-1"	   , NULL,
    {                        /* ThermoRef structure block                     */
    0.0,		     /* H ref (J)				      */
    0.0,		     /* S ref (J/K)				      */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    0.0,		     /* V liq (J)				      */
    EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
    1000.0,		     /* T fusion (K) dummy			      */
    0.0,		     /* S fusion (J/K)  			      */
    0.0,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"F2O-1"	   , NULL,
    {                        /* ThermoRef structure block                     */
    0.0,		     /* H ref (J)				      */
    0.0,		     /* S ref (J/K)				      */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    0.0,		     /* V liq (J)				      */
    EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
    1000.0,		     /* T fusion (K) dummy			      */
    0.0,		     /* S fusion (J/K)  			      */
    0.0,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"H2O"      , NULL,
    {                        /* ThermoRef structure block                     */
    0.0,		     /* H ref (J)				      */
    0.0,		     /* S ref (J/K)				      */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    0.0,		     /* V liq (J)				      */
    EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
    1000.0,		     /* T fusion (K) dummy			      */
    0.0,		     /* S fusion (J/K)  			      */
    0.0,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  }
};
 
int const meltsNlc = (sizeof meltsLiquid / sizeof(struct _liquid));
int const meltsNls = (sizeof meltsLiquid / sizeof(struct _liquid));

#define corrH01  69752.597
#define corrH02 -16940.793
#define corrH03  43463.013
#define corrH04 163652.907
#define corrH05   7238.581
#define corrH06  13739.014
#define corrH07      0.000
#define corrH08   7911.937
#define corrH09      0.000
#define corrH10      0.000
#define corrH11 -21862.658
#define corrH12 -20028.750
#define corrH13 -16015.286
#define corrH14  13197.286
#define corrH15      0.000
#define corrH16      0.000
#define corrH17      0.000
#define corrH18      0.000
#define corrH19    663.955

#define corrS01     45.580
#define corrS02      0.000
#define corrS03    -25.166
#define corrS04     25.413
#define corrS05      0.000
#define corrS06      6.424
#define corrS07      0.000
#define corrS08     12.777
#define corrS09      0.000
#define corrS10      0.000
#define corrS11     -2.266
#define corrS12      0.000
#define corrS13     -7.311
#define corrS14      0.000
#define corrS15      0.000
#define corrS16      0.000
#define corrS17      0.000
#define corrS18      0.000
#define corrS19      9.219

#define corrV01      0.000
#define corrV02      0.000
#define corrV03      0.000
#define corrV04      0.000
#define corrV05      0.000
#define corrV06      0.000
#define corrV07      0.000
#define corrV08      0.000
#define corrV09      0.000
#define corrV10      0.000
#define corrV11      0.000
#define corrV12      0.000
#define corrV13      0.000
#define corrV14      0.000
#define corrV15      0.000
#define corrV16      0.000
#define corrV17      0.000
#define corrV18      0.000
#define corrV19      0.000

Liquid pMeltsLiquid[] = {
#define SIO2_MULT 4.0
  {"Si4O8", NULL,                   /* Solid Properties are beta-cristobalite */
    {                        /* ThermoRef structure block                     */
    -906377.0  *SIO2_MULT + corrH01,		   /* H ref (J) Berman (1988) */
    46.029*SIO2_MULT + corrS01, 		 /* S ref (J/K) Berman (1988) */
    2.730*SIO2_MULT,			       /* V ref (J/bar) Berman (1988) */
    CP_BERMAN,  {{83.51*SIO2_MULT, -3.747e2*SIO2_MULT, -24.554e5*SIO2_MULT,
      28.007e7*SIO2_MULT, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    2.690*SIO2_MULT + corrV01,       /* V liq (J) Lange and Carmichael (1990) */
    EOS_KRESS, {{0.0, -1.89e-5*SIO2_MULT, 1.3e-8*SIO2_MULT, 3.6e-10*SIO2_MULT}},
    1999.0,						      /* T fusion (K) */
    4.46*SIO2_MULT,		       /* S fusion (J/K) Richet et al. (1982) */
    82.6*SIO2_MULT,		/* Cp liquid (J/K) Lange and Navrotsky (1992) */
    0.0 					    /* T glass transition (K) */
    }
  },
#undef SIO2_MULT
  {"TiO2", NULL,
    {                        /* ThermoRef structure block                     */
    -944750.0 + corrH02,     /* H ref (J)			Berman (1988) */
    50.460 + corrS02,	     /* S ref (J)			Berman (1988) */
    1.882,		     /* V ref (J/bar)			Berman (1988) */
    CP_BERMAN,  {{77.84, 0.0, -33.678e5, 40.294e7, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    2.316 + corrV02,	     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{7.246e-4, -2.310e-5, 0.0, 5.0e-10}},
    1870.0,		     /* T fusion (K)  Oxide Handbook: Samsonov (1982) */
    35.824,		     /* S fusion (J/K)  	      Samsonov (1982) */
    109.2,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)          1246.67 Guess */
    }
  },
 #define AL2O3_MULT 2.0
  {"Al4O6", NULL,
    {                        /* ThermoRef structure block                     */
    -1675700.0*AL2O3_MULT + corrH03,		   /* H ref (J) Berman (1988) */
    50.82*AL2O3_MULT + corrS03, 		 /* S ref (J/K) Berman (1988) */
    0.0,						     /* V ref (J/bar) */
    CP_BERMAN,  {{155.02*AL2O3_MULT, -8.284E2*AL2O3_MULT, -38.614E5*AL2O3_MULT,
      40.908E7*AL2O3_MULT, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    3.711*AL2O3_MULT + corrV03,      /* V liq (J) Lange and Carmichael (1990) */
    EOS_KRESS, {{2.62e-4*AL2O3_MULT, -2.26e-5*AL2O3_MULT, 2.7e-8*AL2O3_MULT, 4.0e-10*AL2O3_MULT}}, 
    2319.65,		     /* T fusion (K)  Oxide Handbook: Samsonov (1982) */
    48.61*AL2O3_MULT,	     /* S fusion (J/K)  	      Samsonov (1982) */
    170.3*AL2O3_MULT,	     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)         1551.33  Guess */
    }
  },
#undef AL2O3_MULT
  {"Fe2O3", NULL,
    {                        /* ThermoRef structure block                     */
    -822000.0 + corrH04,     /* H ref (J)		       Ghiorso (1990) */
    87.40 + corrS04,	     /* S ref (J/K)		       Ghiorso (1990) */
    3.027,		     /* V ref (J/bar)			Berman (1988) */
    CP_BERMAN,  {{146.86, 0.0, -55.768E5, 52.563E7, 955.0, 1287.0, -7.403E-2, 27.921E-5}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    4.213 + corrV04,	     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{9.09E-4, -2.53E-5, 3.1E-8, 4.4e-10}},
    1895.0,		     /* T fusion (K)		  Robie et al. (1978) */
    60.41,		     /* S fusion (J/K) Robie et al. (1978) Fe3O4 - FeO*/
    240.9,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)         1263.33  Guess */
    }
  },
  {"MgCr2O4", NULL,
    {                        /* ThermoRef structure block                     */
    -1783640.0 + corrH05,    /* H ref (J)	      Sack and Ghiorso (1991) */
    106.02 + corrS05,	     /* S ref (J/K)	      Sack and Ghiorso (1991) */
    4.3560,		     /* V ref (J/bar)		  Robie et al. (1978) */
    CP_BERMAN,  {{201.981, -5.519E2, -57.844E5, 57.729E7, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    5.358 + corrV05,	     /* V liq (J) Lange and Carmichael (1990) MgFe2O4 */
    EOS_KRESS, {{11.71e-4, -2.26e-5, 1.8e-8, 4.67e-10}},
    2673.15,		     /* T fusion (K)	 Phase diagrams for ceramists */
    73.22,		     /* S fusion (J/K)  			Guess */
    335.1,		     /* Cp liquid (J/K) Lange & Navrot. (1992)MgFe2O3 */
    0.0 		     /* T glass transition (K)  	1782.10 Guess */
    }
  },
  {"Fe2SiO4", NULL,
    {                        /* ThermoRef structure block                     */
    -1479360.0 + corrH06,    /* H ref (J)			Berman (1988) */
    150.930 + corrS06,       /* S ref (J/K)			Berman (1988) */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{248.93, -19.239E2, 0.0, -13.910E7, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    5.420 + corrV06,	     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{5.84e-4, -2.79e-5, -2.3e-8, 14.6e-10}},
    1490.0,		     /* T fusion (K)	       Stebbins et al. (1984) */
    59.9,		     /* S fusion (J/K)         Stebbins et al. (1984) */
    240.2,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)  	 933.33 Guess */
    }
  },
  {"MnSi0.5O2", NULL,
    {                        /* ThermoRef structure block                     */
    -1732000.0/2.0 + corrH07,/* H ref (J)				      */
    155.9/2.0 + corrS07,     /* S ref (J/K)		  Robie et al. (1982) */
    4.889/2.0,  	     /* V ref (J/bar)		  HIRSCHMANN IN PREP  */
    CP_BERMAN,  {{219.89/2.0, -12.710E2/2.0,-20.496E5/2.0, 17.652E7/2.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    2.84 + corrV07,	     /* V liq (J)				      */
    EOS_KRESS, {{5.84e-4/2.0, -2.79e-5/2.0, -2.3e-8/2.0, 14.6e-10/2.0}},
    1620.0,		     /* T fusion (K)			   Mah (1960) */
    27.6,		     /* S fusion (J/K)  		   Mah (1960) */
    121.6,		     /* Cp liquid (J/K) 		   Mah (1960) */
    0.0 		     /* T glass transition (K)         1080.00  Guess */
    }
  },
  {"Mg2SiO4", NULL,
    {                        /* ThermoRef structure block                     */
    -2174420.0 + corrH08,    /* H ref (J)			Berman (1988) */
    94.010 + corrS08,	     /* S ref (J/K)			Berman (1988) */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{238.64, -20.013E2, 0.0, -11.624E7, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    4.980 + corrV08,	     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{5.24e-4, -1.35e-5, -1.3e-8, 4.14e-10}},
    2163.0,		     /* T fusion (K)	    Bowen and Anderson (1914) */
    57.2,		     /* S fusion (J/K)  corr: Navrotsky et al. (1989) */
    271.0,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)  	1442.00 Guess */
    }
  },
  {"NiSi0.5O2", NULL,
    {                        /* ThermoRef structure block                     */
    -1395300.0/2.0 + corrH09,/* H ref (J)		    Hirschmann (1993) */
    128.1/2.0 + corrS09,     /* S ref (J/K)		    Hirschmann (1993) */
    4.259/2.0,  	     /* V ref (J/bar)		    Hirschmann (1993) */
    CP_BERMAN,  {{214.997/2.0, -10.3075E2/2.0, -49.4453E5/2.0, 62.375E7/2.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    2.48 + corrV09,	     /* V liq (J)				      */
    EOS_KRESS, {{5.84e-4/2.0, -2.79e-5/2.0, -2.3e-8/2.0, 14.6e-10/2.0}},
    1923.0,		     /* T fusion (K)				      */
    29.0,		     /* S fusion (J/K)  			      */
    119.3,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"CoSi0.5O2", NULL,
    {                        /* ThermoRef structure block                     */
    -1414100.0/2.0 + corrH10,/* H ref (J)		 HIRSCHMANN, in press */
    142.6/2.0 + corrS10,     /* S ref (J/K)		 HIRSCHMANN, in press */
    4.459/2.0,  	     /* V ref (J/bar)		 HIRSCHMANN, in press */
    CP_BERMAN,  {{201.048/2.0, -0.369E2/2.0, -71.81E5/2.0, 90.05E7/2.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    2.30 + corrV10,	     /* V liq (J)				      */
    EOS_KRESS, {{5.84e-4/2.0, -2.79e-5/2.0, -2.3e-8/2.0, 14.6e-10/2.0}},
    1688.0,		     /* T fusion (K)				      */
    29.0,		     /* S fusion (J/K)  			      */
    125.3,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
#define CASIO3_MULT 2.0
  {"Ca2Si2O6", NULL,                                    /* Pseudowallostonite */
    {                        /* ThermoRef structure block                     */
    -1627427.0*CASIO3_MULT + corrH11,		   /* H ref (J) Berman (1988) */
    85.279*CASIO3_MULT + corrS11,		 /* S ref (J/K) Berman (1988) */
    4.016*CASIO3_MULT,  		       /* V ref (J/bar) Berman (1988) */
    CP_BERMAN,  {{141.16*CASIO3_MULT, -4.172e2*CASIO3_MULT, -58.576e5*CASIO3_MULT,
      94.074e7*CASIO3_MULT, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    4.347*CASIO3_MULT + corrV11,     /* V liq (J) Lange and Carmichael (1990) */
    EOS_KRESS, {{2.92e-4*CASIO3_MULT, -1.55e-5*CASIO3_MULT, -1.6e-8*CASIO3_MULT, 3.89e-10*CASIO3_MULT}},
    1817.0,		     /* T fusion (K)		  Adamkovicova (1980) */
    31.5*CASIO3_MULT,	     /* S fusion (J/K)  	  Adamkovicova (1980) */
    172.4*CASIO3_MULT,       /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)  	1211.33 Guess */
    }
  },
#undef CASIO3_MULT
#define NA2SIO3_MULT 0.5
  {"NaSi0.5O1.5", NULL,                           /* Stull and Prophet (1971) */
    {                        /* ThermoRef structure block                     */
    -373190.0*4.184*NA2SIO3_MULT + corrH12,			 /* H ref (J) */
    27.21*4.184*NA2SIO3_MULT + corrS12, 		       /* S ref (J/K) */
    0.0,						     /* V ref (J/bar) */
    CP_BERMAN,  {{234.77*NA2SIO3_MULT, -22.189E2*NA2SIO3_MULT, 0.0,
      13.530E7*NA2SIO3_MULT, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    5.568*NA2SIO3_MULT + corrV12,/* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{7.41e-4*NA2SIO3_MULT, -4.29e-5*NA2SIO3_MULT, -5.3e-8*NA2SIO3_MULT, 8.4e-10*NA2SIO3_MULT}}, 
    1361.0,		     /* T fusion (K)	       Stebbins et al. (1984) */
    38.34*NA2SIO3_MULT,      /* S fusion (J/K)         Stebbins et al. (1984) */
    180.2*NA2SIO3_MULT,      /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)  	907.33  Guess */
    }
  },
#define NA2SIO3_MULT 0.5
  {"KAlSiO4", NULL,
    {                        /* ThermoRef structure block                     */
    -2111813.55 + corrH13,   /* H ref (J)		    Berman (pers com) */
    133.9653 + corrS13,      /* S ref (J/K)		    Berman (pers com) */
    5.989,		     /* V ref (J/bar)		    Berman (pers com) */
    CP_BERMAN,  {{186.0, 0.0, -131.067E5, 213.893E7, 800.15, 1154.0, -7.096454E-2, 21.682E-5}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    6.8375 + corrV13,	     /* V liq (J)	  Lange and Carmichael (1990) */
    EOS_KRESS, {{7.265e-4, -6.395e-5, -4.6e-8, 12.1e-10}},
    2023.15,		     /* T fusion (K)   Morse (phase diagram page 257) */
    24.5,		     /* S fusion (J/K) Guess - Stebbins et al. (1984) */
    217.0,		     /* Cp liquid (J/K)    Lange and Navrotsky (1992) */
    0.0 		     /* T glass transition (K)         1348.77  Guess */
    }
  },
  {"Ca3(PO4)2", NULL,
    {                        /* ThermoRef structure block                     */
    -4097169.0 + corrH14,    /* H ref (J)	Zhu and Sverjensky (in press) */
    235.978 + corrS14,       /* S ref (J/K)	   Southard and Milner (1935) */
    9.7620,		     /* V ref (J/bar)		  Robie et al. (1978) */
    CP_BERMAN,  {{402.997, -28.0835E2, 0.0, -32.6230E7, 1373.0, 14059.0, 2.5427E-2, 19.255E-5}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    10.7382 + corrV14,       /* V liq (J)	1.1 times the volume of solid */
    EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
    1943.15,		     /* T fusion (K)	 Handbook of Chem and Physics */
    35.690,		     /* S fusion (J/K) ave of Mg3(PO4)2 and Ba3(PO4)2 */
    574.67,		     /* Cp liquid (J/K)       from Ca2P2O7 and CaP2O6 */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"CO2", NULL,
    {                        /* ThermoRef structure block                     */
    corrH15,		     /* H ref (J)				      */
    corrS15,		     /* S ref (J/K)				      */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    corrV15,		     /* V liq (J)				      */
    EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
    1000.0,		     /* T fusion (K) dummy			      */
    0.0,		     /* S fusion (J/K)  			      */
    0.0,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"SO3", NULL,
    {                        /* ThermoRef structure block                     */
    corrH16,		     /* H ref (J)				      */
    corrS16,		     /* S ref (J/K)				      */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    corrV16,		     /* V liq (J)				      */
    EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
    1000.0,		     /* T fusion (K) dummy			      */
    0.0,		     /* S fusion (J/K)  			      */
    0.0,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"Cl2O-1", NULL,
    {                        /* ThermoRef structure block                     */
    corrH17,		     /* H ref (J)				      */
    corrS17,		     /* S ref (J/K)				      */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    corrV17,		     /* V liq (J)				      */
    EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
    1000.0,		     /* T fusion (K) dummy			      */
    0.0,		     /* S fusion (J/K)  			      */
    0.0,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"F2O-1", NULL,
    {                        /* ThermoRef structure block                     */
    corrH18,		     /* H ref (J)				      */
    corrS18,		     /* S ref (J/K)				      */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    corrV18,		     /* V liq (J)				      */
    EOS_KRESS, {{0.0, 0.0, 0.0, 0.0}},
    1000.0,		     /* T fusion (K) dummy			      */
    0.0,		     /* S fusion (J/K)  			      */
    0.0,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  },
  {"H2O", NULL,
    {                        /* ThermoRef structure block                     */
    corrH19,		     /* H ref (J)				      */
    corrS19,		     /* S ref (J/K)				      */
    0.0,		     /* V ref (J/bar)				      */
    CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
    EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      /* ThermoLiq structure block                     */
    2.775+ corrV19,	     /* V liq (J)	   Ochs & Lange (1997)        */
    EOS_KRESS, {{10.86e-4, -6.00e-5, 0.0, 0.0}},
    1000.0,		     /* T fusion (K) dummy			      */
    0.0,		     /* S fusion (J/K)  			      */
    0.0,		     /* Cp liquid (J/K) 			      */
    0.0 		     /* T glass transition (K)  		      */
    }
  }
};

int const pMeltsNlc = (sizeof pMeltsLiquid / sizeof(struct _liquid));
int const pMeltsNls = (sizeof pMeltsLiquid / sizeof(struct _liquid));

#undef corrH01
#undef corrH02
#undef corrH03
#undef corrH04
#undef corrH05
#undef corrH06
#undef corrH07
#undef corrH08
#undef corrH09
#undef corrH10
#undef corrH11
#undef corrH12
#undef corrH13
#undef corrH14
#undef corrH15
#undef corrH16
#undef corrH17
#undef corrH18
#undef corrH19

#undef corrS01
#undef corrS02
#undef corrS03
#undef corrS04
#undef corrS05
#undef corrS06
#undef corrS07
#undef corrS08
#undef corrS09
#undef corrS10
#undef corrS11
#undef corrS12
#undef corrS13
#undef corrS14
#undef corrS15
#undef corrS16
#undef corrS17
#undef corrS18
#undef corrS19

#undef corrV01
#undef corrV02
#undef corrV03
#undef corrV04
#undef corrV05
#undef corrV06
#undef corrV07
#undef corrV08
#undef corrV09
#undef corrV10
#undef corrV11
#undef corrV12
#undef corrV13
#undef corrV14
#undef corrV15
#undef corrV16
#undef corrV17
#undef corrV18
#undef corrV19

Oxygen oxygen;

#endif /* _Liq_Struct_Data_h */
