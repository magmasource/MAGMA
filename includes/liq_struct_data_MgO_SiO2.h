#ifndef _Liq_Struct_Data_h
#define _Liq_Struct_Data_h

/*
MELTS Source Code: RCS $Log: liq_struct_data_MgO_SiO2.h,v $
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:36  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2005/01/25 03:25:03  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1  2005/01/24 03:38:04  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added new files and modifications to perform builds for MgO-SiO2 system
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.7  2005/01/21 18:18:22  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added data structures and code to implement coordination number transformations
MELTS Source Code: RCS in the liquid phase EOS model.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.6  2004/12/30 00:22:52  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2004/12/11 22:19:43  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2004/10/03 22:40:08  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2004/10/02 19:41:47  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2004/10/02 01:33:03  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1  2004/09/29 21:24:22  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
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
#define LNCpMgO    94.2

/* Molecular Weights of Oxides */
#define MWSiO2   60.0848
#define MWMgO    40.3114


/*=================================================================*/
/*EOS parameters (in J/bar-*) or (m/sec-*)                         */
/*=================================================================*/
 
#define GKVSiO2        (2.81000)
#define GKVMgO         (0.928665)
 
#define GKdVdTSiO2     ( 3.27317e-5)
#define GKdVdTMgO      ( 3.43154e-4)
 
#define GKcSiO2        (5226.79)
#define GKcMgO	       ( 444.910)

#define GKdcdTSiO2     ( 4.15722e-2)
#define GKdcdTMgO      ( 6.33408e-1)
 
#define GKd2VdP2SiO2   ( 2.21992e-11)
#define GKd2VdP2MgO    ( 4.59754e-10)
 
#define GKd3VdP3SiO2   (-5.02108e-17)
#define GKd3VdP3MgO    (-1.82612e-14)
 
#define GKd4VdP4SiO2   (-2.26749e-21)
#define GKd4VdP4MgO    ( 9.12317e-19)

#define KPRIMEH2O      (5.0)

BulkSystem bulkSystem[] = { /* 3rd coefficient converts FeO(T) -> FeO, Fe2O3 */
  { "SiO2"  , OTHER,  0.0,   0.0, NULL, NULL, GKVSiO2    , GKdVdTSiO2    , GKcSiO2 , 0.0  , GKdcdTSiO2 , LNCpSiO2    , GKd2VdP2SiO2    , GKd3VdP3SiO2    , GKd4VdP4SiO2     },
  { "MgO"   , OTHER,  0.0,   0.0, NULL, NULL, GKVMgO     , GKdVdTMgO     , GKcMgO  , 0.0  , GKdcdTMgO  , LNCpMgO     , GKd2VdP2MgO     , GKd3VdP3MgO     , GKd4VdP4MgO      }
};
int nc = (sizeof bulkSystem / sizeof(struct _bulkSystem));

Liquid xMeltsLiquid[] = {
  /* Solid:  beta-cristobalite, Berman 1988                                         */
  /* Liquid: Fusion entropy, Richet et al., 1982                              */
  {"SiO2", NULL, 
    {            
      -906377.0, 46.029, 0.0,       
      CP_BERMAN,  {{83.51, -3.747E2, -24.554E5, 28.007E7, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{     
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1999.0, 4.46, 0.0, 0.0 	
    }
  },
  {"MgO = 1.0 MgSiO3 -1.0 SiO2", NULL,
    {
      0.0, 0.0, 0.0,	
      CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{                      
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1673.15, 0.0, 0.0, 0.0 		 
    }
  },
  /* Solid:  orthoenstatite, Berman 1988                                      */
  /* Liquid: Fusion entropy, Bottinga and Richet, 1984                        */  
  {"MgSiO3", NULL,
    {             
      -1545552.0, 66.17, 0.0,        
      CP_BERMAN,  {{166.58, -12.006E2, -22.706E5, 27.915E7, 0.0, 0.0, 0.0, 0.0}},
      EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}}
    },{    
      0.0,
      EOS_GHIORSO, {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
      1832.0, 76.7/2.0,	0.0, 0.0 	
    }
  }
};

int    nlc     = (sizeof xMeltsLiquid / sizeof(struct _liquid)) - 1;
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
  }
};
 
int const meltsNlc = (sizeof meltsLiquid / sizeof(struct _liquid));
int const meltsNls = (sizeof meltsLiquid / sizeof(struct _liquid));

#define corrH01  69752.597
#define corrH08   7911.937

#define corrS01     45.580
#define corrS08     12.777

#define corrV01      0.000
#define corrV08      0.000

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
  }
};

int const pMeltsNlc = (sizeof pMeltsLiquid / sizeof(struct _liquid));
int const pMeltsNls = (sizeof pMeltsLiquid / sizeof(struct _liquid));

#undef corrH01
#undef corrH08

#undef corrS01
#undef corrS08

#undef corrV01
#undef corrV08

Oxygen oxygen;

#endif /* _Liq_Struct_Data_h */
