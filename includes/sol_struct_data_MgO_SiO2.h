#ifndef _Sol_Struct_Data_h
#define _Sol_Struct_Data_h

/*
MELTS Source Code: RCS $Log: sol_struct_data_MgO_SiO2.h,v $
MELTS Source Code: RCS Revision 1.2  2007/08/26 21:38:31  ghiorso
MELTS Source Code: RCS Normalized residuals (for xMELTS calibration) to the number of atoms in the
MELTS Source Code: RCS endmember mineral formula.  Revised residual-statistics.out file accordingly.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:36  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2005/02/04 14:48:54  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2005/01/27 15:26:12  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1  2005/01/24 03:38:05  cvsaccount
MELTS Source Code: RCS
MELTS Source Code: RCS Added new files and modifications to perform builds for MgO-SiO2 system
MELTS Source Code: RCS
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Include file for initializing solids data structure
**        (file: SOL_STRUCT_DATA.H)
**
**  MODIFICATION HISTORY:
**--
*/

/* 
 *==============================================================================
 */

#define        INCLUDE_IN_CALIBRATION TRUE
#define DO_NOT_INCLUDE_IN_CALIBRATION FALSE

#define        INCLUDE_IN_STD_SET TRUE
#define DO_NOT_INCLUDE_IN_STD_SET FALSE

#define USE_BERMAN_DATABASE
#undef  USE_SAXENA_DATABASE
#undef  USE_OLD_SAXENA_DATABASE

Solids xMeltsSolids[] = {
  {"enthalpy", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,            /* Dummy formula to fool parser                         */
   {                /* ThermoRef structure                                   */
   -1000.0,         /* H ref (J)                                             */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"entropy", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,             /* Dummy formula to fool parser                         */
   {                /* ThermoRef structure                                   */
   -1000.0,         /* H ref (J)                                             */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"liquid", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,            /* Dummy formula to fool parser                         */
   {                /* ThermoRef structure                                   */
   -1000.0,         /* H ref (J)                                             */
   0.0,             /* S ref (J/K)                                           */
   0.0,             /* V ref (J/bar)                                         */
   CP_BERMAN,  {{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{0.0, 0.0, 0.0, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
#ifdef USE_BERMAN_DATABASE
  /***************************************************************************
  
   -----> Berman (1988) phases + Saxena high P cen
   
   ***************************************************************************/
  {"cen-hp-sx", PHASE, "MgSiO3", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1544826.4,       /* H ref (J)                       Saxena et al. (1993) */
   65.200,           /* S ref (J/K)                     Saxena et al. (1993) */
   3.0918,           /* V ref (J/bar)                   Saxena et al. (1993) */
   CP_SAXENA,  {{ 1.4440140e02, 1.8812e-3, -1.3609e06, 0.0000e00, 4.5980e08, 0.0000e00, -1.9350e04}},                               
   EOS_SAXENA, {{ 3.87702e-5, 4.50016e-9, 3.43917e-4, -1.72362e00, 8.89581e-7, 1.35473e-10, 3.17162e-14, 1.15236e-17, 4.2, 4.2e-4}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"coesite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907604.1,        /* H ref (J) Berman (1988)                              */
   39.424,           /* S ref (J/K) Berman (1988)                            */
   2.064,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{94.90714, -767.338, -527867.000, 26270730.0, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-1.0368217E-6, 3.0E-12, 7.3963178E-6, 43.605E-10}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"cristobalite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907753.0,        /* H ref (J) Berman (1988)                              */
   43.394,           /* S ref (J/K) Berman (1988)                            */
   2.587,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{83.51, -3.747E2, -24.554E5, 28.007E7, 535.0, 0.0, -14.216E-2, 44.142E-5}},
   EOS_BERMAN, {{-2.515E-6, 0.0, 20.824E-6, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"forsterite", PHASE, "Mg2SiO4", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2174420.0,       /* H ref (J)                              Berman (1988) */
   94.010,           /* S ref (J/K)                            Berman (1988) */
   4.366,            /* V ref (J/bar)                          Berman (1988) */
   CP_BERMAN, {{238.64, -20.013E2, 0.0, -11.624E7, 0.0, 0.0, 0.0, 0.0}},                
   EOS_VINET, {{ 3.1393e-5, 125.099, 5.05799 }} /* EOS_BERMAN, {{-0.791E-6, 1.351E-12, 29.464E-6, 88.633E-10}} */
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"orthoenstatite", PHASE, "MgSiO3", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1545552.0,      /* H ref (J)                               Berman (1988) */
   66.17,           /* S ref (J/K)                             Berman (1988) */
   3.133,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN, {{166.58, -12.006E2, -22.706E5, 27.915E7, 0.0, 0.0, 0.0, 0.0}},
   EOS_VINET, {{ 3.1219e-5, 108.508861, 7.75676841 }}  /* EOS_BERMAN, {{-0.749E-6, 0.447E-12, 24.656E-6, 74.670E-10}} */
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"periclase", PHASE, "MgO", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -601500.0,       /* H ref (J)                               Berman (1990) */
   26.951,          /* S ref (J/K)                             Berman (1990) */
   1.125,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN,  {{61.10965, -2.96199e2, -6.21154e5, 0.5844612e7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-0.6223329e-6, 1.5114e-12, 37.4774182e-6, 3.556e-10}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"protoenstatite", PHASE, "MgSiO3", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1543959.0,      /* H ref (J)                               Berman (1988) */
   67.438,          /* S ref (J/K)                             Berman (1988) */
   3.242,           /* V ref (J/bar)                           Berman (1988) */
   CP_BERMAN, {{166.58, -12.006E2, -22.706E5, 27.915E7, 0.0, 0.0, 0.0, 0.0}},
   EOS_BERMAN, {{-0.7496E-6, 0.448E-12, 16.832E-6, 116.65E-10}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"quartz", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -910700.0,        /* H ref (J) Berman (1988)                              */
   41.460,           /* S ref (J/K) Berman (1988)                            */
   2.269,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN, {{80.01, -2.403E2, -35.467E5, 49.157E7, 848.0, 0.0, -9.187E-2, 24.607E-5}},
   EOS_VINET, {{0.0, 80.7754443, 5.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"tridymite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907750.0,        /* H ref (J) Berman (1988)                              */
   43.770,           /* S ref (J/K) Berman (1988)                            */
   2.675,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{75.37, 0.0, -59.581E5, 95.825E7, 383.0, 130.0, 42.670E-2, -144.575E-5}},                  
   EOS_BERMAN, {{-2.508E-6, 0.0, 19.339E-6, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  }
#endif /* USE_BERMAN_DATABASE */
#ifdef USE_SAXENA_DATABASE
  /***************************************************************************
  
   -----> Saxena High Pressure database - pure solids
   
  a0, a1, a2, a3, b0, b1, b2, b3, dKdP, d2KdTdP; EOS Saxena;
  
    alpha      = a0 + a1*t + a2/t + a3/(t*t);
    beta       = b0 + b1*t + b2*t*t + b3*t*t*t;
    K	       = 1.0/beta;
    Kp         = dKdP + d2KdTdP*(t-300.0)*log(t/300.0);

  a, b, c, d, e, g, h; Cp Saxena;

    cps    = a + b*t + c/(t*t) + d*t*t + e/(t*t*t) + gCp/sqrt(t) + hCp/t;
   
   ***************************************************************************/
  {"clinoenstatite-sx", PHASE, "MgSiO3", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1544823.0,       /* H ref (J)                                            */
   65.300,           /* S ref (J/K)                                          */
   3.09177,          /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 110.148, 0.015219, -8.3416e06, 0.0, 9.17225e8, 0.0, 9.3904e3}},                               
   EOS_SAXENA, {{ 3.87701887e-5, 4.50015778e-9, 3.43917089e-4, -1.72362114e00, 8.89581038e-7, 1.35473202e-10, 3.17162053e-14, 1.15235914e-17, 3.6, 1.5e-4}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"coesite-sx", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -906400.0,        /* H ref (J)                                            */
   40.600,           /* S ref (J/K)                                          */
   2.0640,           /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 78.9, 0.0, -5.065e6, 0.0, 0.825e9, -1.635e2, 0.0}},                               
   EOS_SAXENA, {{ 5.43e-6, 7.6e-9, 0.0000e00, 0.0000e00, 1.05e-6, 1.5e-10, 0.0, 0.0,8.4, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"cristobalite-sx", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,            /* alpha above 523 K                                     */
   {                /* ThermoRef structure                                   */
   -906034.0,        /* H ref (J)                                            */
   46.060,           /* S ref (J/K)                                          */
   2.5740,           /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 74.9325, -1.6202e-3, -4.405322e6, 9.94385e-7, 0.0, 0.0, 0.0}},                               
   EOS_SAXENA, {{ 5.0e-6, 0.0, 0.0, 0.0, 5.13e-6, 0.0, 0.0, 0.0, 6.0, 0.0e00}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"forsterite-sx", PHASE, "Mg2SiO4", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2174140.0,       /* H ref (J)                                            */
   95.60,            /* S ref (J/K)                                          */
   4.367,            /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 165.8, 1.855e-2, -3971000.0, 0.0, 2.861e8, 0.0, -5610.0}},                               
   EOS_SAXENA, {{ 2.01e-5, 1.39e-8, 1.627e-3, -0.338, 7.427e-7, 1.24e-10, 6.9e-14, 1.702e-17, 5.2, 2.0e-4}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"ilmenite-sx", PHASE, "MgSiO3", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1494100.0,       /* H ref (J)                                            */
   58.300,           /* S ref (J/K)                                          */
   2.635,            /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 125.5, 5.303e-3, -6.282e6,  0.0, 7.665e8, 0.0,  -3.04e3}},                               
   EOS_SAXENA, {{ 2.2704e-5, 6.8209e-9, -0.001809, 0.3851, 4.504e-7, 8.2987e-11, -3.8777e-15,1.2095e-17, 4.0, 3.0e-4}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"majorite-sx", PHASE, "MgSiO3", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1513000.0,       /* H ref (J)                                            */
   60.300,           /* S ref (J/K)                                          */
   2.85,             /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 176.80, 0.0, -6.44e5,  0.0, 6.59e7,  -1.603e3, 0.0}},                               
   EOS_SAXENA, {{ 1.1019e-5, 7.5075e-9, 0.0060403, -1.0267, 5.8168e-7, 2.521e-10, -1.1e-13, 5.58636e-17, 4.0, 1.0e-3}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"orthoenstatite-sx", PHASE, "MgSiO3", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1546290.0,       /* H ref (J)                                            */
   66.270,           /* S ref (J/K)                                          */
   3.1346,            /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 1.4445e02, 1.8821e-3, -1.3500e06,  0.0000e00, 4.6120e08,  0.0000e00, -1.9380e04}},                               
   EOS_SAXENA, {{ 2.66e-5, 7.2e-9, 0.0, 0.0, 9.3e-7, 1.3584e-10, 3.1613e-14, 1.1413e-17, 10.2, 1.5e-4}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"periclase-sx", PHASE, "MgO", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -601490.0,        /* H ref (J)                                            */
   26.940,           /* S ref (J/K)                                          */
   1.125,            /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 45.49, 4.773e-3, -2.16e6, 0.0, 1.744e8, 0.0, 2.411e3}},                               
   EOS_SAXENA, {{ 3.64e-5, 8.35e-9, 8.5e-4, -9.5e-1, 5.875e-7, 1.101e-10, 1.37e-14, 4.8e-18, 4.17, 4.0e-5}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
   {"perovskite-sx", PHASE, "MgSiO3", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1449500.0,       /* H ref (J)                                            */
   63.600,           /* S ref (J/K)                                          */
   2.4447,           /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 137.9, 1.564e-3, -3.191e6,  0.0, 7.192e8, 0.0,  -1.459e4}},                               
   EOS_SAXENA, {{ 4.903e-5, -2.307e-9, -0.01812, 2.543, 3.7184e-7, 2.3496e-11, 2.2508e-14, 0.0, 4.1, 1.0e-4}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"protoenstatite-sx", PHASE, "MgSiO3", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1545790.000,     /* H ref (J)                                            */
   66.960,           /* S ref (J/K)                                          */
   3.2458,           /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 145.79, 1.8986e-3, -1.374258e06, 0.0000e00, 4.58429e08, 0.0000e00, -2.01626e04}},                               
   EOS_SAXENA, {{ 6.40239e-5, 1.4439e-8, -0.0632425, 7.86955, 9.11066e-7, 7.612e-12, -7.3162e-13, 5.311578e-16, 6.6, 1.5e-4}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"alpha-quartz-sx", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,            /* alpha quartz above 848 K                              */
   {                /* ThermoRef structure                                   */
   -910700.0,        /* H ref (J)                                            */
   41.460,           /* S ref (J/K)                                          */
   2.2688,           /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 78.812, 0.001205, -1.731e5, 0.0, 1.202e8, 0.0, -12130.0}},                               
   EOS_SAXENA, {{ 2.7513e-5, 2.9868e-8, 5.5722e-6, 9.1181e-2, 2.556e-6, 1.1557e-11, 1.013e-16, 8.89e-19,6.4, 0.0e00}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"beta-quartz-sx", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,            /* beta quartz  above 848 K                              */
   {                /* ThermoRef structure                                   */
   -910495.0,        /* H ref (J)                                            */
   41.700,           /* S ref (J/K)                                          */
   2.28755,          /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 78.812, 0.001205, -1.731e5, 0.0, 1.202e8, 0.0, -12130.0}},                               
   EOS_SAXENA, {{ 2.0604e-5, 3.4694e-8, 1.3075e-4, -1.6376, 1.39699e-6, 2.41181e-9, -2.1518e-12, 6.4543e-16, 5.346, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"ringwoodite-sx", PHASE, "Mg2SiO4", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2132100.0,       /* H ref (J)                                            */
   90.60,            /* S ref (J/K)                                          */
   3.965,            /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 158.26, 1.22e-2, -1.2297e7, 0.0, 1.4841e9, 0.0, 7.9719e3}},                               
   EOS_SAXENA, {{ 1.225e-5, 1.104e-8, 2.496e-3, -0.511, 5.07778e-7, 1.3371e-10, -2.9854e-14, 2.7822e-17, 4.3, 6.0e-4}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
 {"stishovite-sx", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -874000.0,        /* H ref (J)                                            */
   24.642,           /* S ref (J/K)                                          */
   1.4010,           /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 85.78, 0.0, -3.605e6, 0.0, 4.511e8, -345.5, 0.0}},                               
   EOS_SAXENA, {{ 2.3e-6, 1.2e-8, 0.0062, -1.13, 2.954e-7, 8.9610e-11, -3.29e-14, 2.3310e-17, 6.0, 1.0e-3}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"tridymite-sx", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,            /* alpha above 673                                       */
   {                /* ThermoRef structure                                   */
   -906913.0,        /* H ref (J)                                            */
   45.116,           /* S ref (J/K)                                          */
   2.653,            /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 66.6993, 5.2779e-3, -2132338.0, -3.54783e-7, 0.0, 0.0, 0.0}},                               
   EOS_SAXENA, {{ 2.1797e-5, -1.53e-8, 0.0, 0.0, 4.0e-6, 0.0, 0.0, 0.0, 6.0, 0.0}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"wadsleyite-sx", PHASE, "Mg2SiO4", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -2140500.0,       /* H ref (J)                                            */
   95.00,            /* S ref (J/K)                                          */
   4.054,            /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 172.9, 1.129e-2, -1077100.0, 0.0, -2.187e8, 0.0, -13477.0}},                               
   EOS_SAXENA, {{ 2.319e-5, 9.04e-9, -3.966e-3, 0.7496, 5.5128e-7, 9.2017e-11, 8.849e-15, 1.1529e-17, 4.3, 3.0e-4}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  }
#endif /* USE_SAXENA_DATABASE */
#ifdef USE_OLD_SAXENA_DATABASE
  {"cen-lt-sx", PHASE, "MgSiO3", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1548715.113,     /* H ref (J)                                            */
   63.230,           /* S ref (J/K)                                          */
   3.1282,           /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 1.3807968e02, 8.7088e-3, 4.0591e05, -1.3523e-6, 0.0000e00,  0.0000e00, -1.8888e04}},                               
   EOS_SAXENA, {{ 3.67653e-5, 2.36466e-8, -2.00989e-2, 4.88850e00, 9.37603e-7, -3.72785e-15, 1.65566e-13, -4.28415e-17, 4.52467, 5.53033e-4}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  },
  {"cen-ht-sx", PHASE, "MgSiO3", INCLUDE_IN_CALIBRATION, DO_NOT_INCLUDE_IN_STD_SET, NULL, NULL,
   0.0, 0.0,
   {                /* ThermoRef structure                                   */
   -1543295.2,       /* H ref (J)                                            */
   68.332,           /* S ref (J/K)                                          */
   3.1282,           /* V ref (J/bar)                                        */
   CP_SAXENA,  {{ 1.4433281e02, 1.8794e-3, -1.3529e06, 0.0000e00, 4.6254e08, 0.0000e00, -1.9514e04}},                               
   EOS_SAXENA, {{ 5.42920e-5, 3.10143e-9, -2.25441e-2, 6.87659e00, 5.00000e-7, 1.35840e-10, 3.16130e-14, 1.14130e-17, 4.0, 1.5e-4}} 
   },
   {                /* ThermoData structure                                  */
   0.0, 0.0, 0.0, 0.0, 0.0,         /* Dummy entries to ThermoData structure */
   0.0, 0.0, 0.0,
   0.0, 0.0, 0.0
   }
  }
#endif /* USE_OLD_SAXENA_DATABASE */
};

int    npc     = (sizeof xMeltsSolids / sizeof(struct _solids));
Solids *solids = xMeltsSolids;

Solids meltsSolids[] = {
  {"quartz", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -910700.0,        /* H ref (J) Berman (1988)                              */
   41.460,           /* S ref (J/K) Berman (1988)                            */
   2.269,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{80.01, -2.403E2, -35.467E5, 49.157E7, 848.0, 0.0, -9.187E-2, 24.607E-5}},
   EOS_BERMAN, {{-2.434E-6, 10.137E-12, 23.895E-6, 0.0}}
   }
  },
  {"tridymite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907750.0,        /* H ref (J) Berman (1988)                              */
   43.770,           /* S ref (J/K) Berman (1988)                            */
   2.675,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{75.37, 0.0, -59.581E5, 95.825E7, 383.0, 130.0, 42.670E-2, -144.575E-5}},
   EOS_BERMAN, {{-2.508E-6, 0.0, 19.339E-6, 0.0}}
   }
  },
  {"cristobalite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907753.0,        /* H ref (J) Berman (1988)                              */
   43.394,           /* S ref (J/K) Berman (1988)                            */
   2.587,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{83.51, -3.747E2, -24.554E5, 28.007E7, 535.0, 0.0, -14.216E-2, 44.142E-5}},
   EOS_BERMAN, {{-2.515E-6, 0.0, 20.824E-6, 0.0}}
   }
  }
};
int const meltsNpc = (sizeof meltsSolids  / sizeof(struct _solids));

Solids pMeltsSolids[] = {
  {"quartz", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -910700.0,        /* H ref (J) Berman (1988)                              */
   41.460,           /* S ref (J/K) Berman (1988)                            */
   2.269,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{80.01, -2.403E2, -35.467E5, 49.157E7, 848.0, 0.0, -9.187E-2, 24.607E-5}},
   EOS_BERMAN, {{-2.434E-6, 10.137E-12, 23.895E-6, 0.0}}
   }
  },
  {"tridymite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907750.0,        /* H ref (J) Berman (1988)                              */
   43.770,           /* S ref (J/K) Berman (1988)                            */
   2.675,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{75.37, 0.0, -59.581E5, 95.825E7, 383.0, 130.0, 42.670E-2, -144.575E-5}},
   EOS_BERMAN, {{-2.508E-6, 0.0, 19.339E-6, 0.0}}
   }
  },
  {"cristobalite", PHASE, "SiO2", INCLUDE_IN_CALIBRATION, INCLUDE_IN_STD_SET, NULL, NULL, 
   0.0, 0.0,                              /* alpha phase, transformed in GIBBS.C */
   {                /* ThermoRef structure                                   */
   -907753.0,        /* H ref (J) Berman (1988)                              */
   43.394,           /* S ref (J/K) Berman (1988)                            */
   2.587,            /* V ref (J/bar) Berman (1988)                          */
   CP_BERMAN,  {{83.51, -3.747E2, -24.554E5, 28.007E7, 535.0, 0.0, -14.216E-2, 44.142E-5}},
   EOS_BERMAN, {{-2.515E-6, 0.0, 20.824E-6, 0.0}}
   }
  }
};

const int pMeltsNpc = (sizeof pMeltsSolids  / sizeof(struct _solids));

#endif /* _Sol_Struct_Data_h */
