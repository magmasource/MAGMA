#ifndef _Res_Struct_Data_h
#define _Res_Struct_Data_h

/*
MELTS Source Code: RCS $Log: res_struct_data.h,v $
MELTS Source Code: RCS Revision 1.9  2007/11/22 04:08:14  ghiorso
MELTS Source Code: RCS Corrected infinite loop error in order() in albite.c
MELTS Source Code: RCS Removed arbitrary volume corrections in sol_struct_data.h
MELTS Source Code: RCS Turned on non-quadrilateral cpx endmembers for regression.
MELTS Source Code: RCS Added MgSiO3 species to liquid model.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.8  2007/11/12 20:19:58  ghiorso
MELTS Source Code: RCS Some updates regarding cpx regression and max number of regression equation per sample.s
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.7  2007/11/10 20:08:39  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.6  2007/10/31 20:12:05  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.5  2007/06/13 15:18:21  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.4  2007/06/09 20:30:04  ghiorso
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2007/03/12 20:06:36  ghiorso
MELTS Source Code: RCS Changed fO2 inclusion criteria and adjusted some mineral endmember inclusion
MELTS Source Code: RCS tolerances.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2007/03/07 21:21:58  ghiorso
MELTS Source Code: RCS Revised majorite model and the way garnets are treated during calibration.
MELTS Source Code: RCS Revised calibration XML file to include LEPER + older MELTS/pMELTS data.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:36  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:48:56  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Include file for initializing solids data structure
**        (file: RES_STRUCT_DATA.H)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  August 31, 1998   Original Version
**              Canabalized from sol_struct_data.h
**--
*/

/* 
 *==============================================================================
 */

/*********************WARNING*********************/
/* naMax for solid solutions is assumed to be 10 */
/*********************WARNING*********************/

ExtraSolids extraSolids[] = {
  /* "tephroite",    "Mn2SiO4"   */
  /* "fayalite",     "Fe2SiO4"   */
  /* "co-olivine",   "Co2SiO4"   */
  /* "ni-olivine",   "Ni2SiO4"   */
  /* "monticellite", "CaMgSiO4"  */
  /* "forsterite",   "Mg2SiO4"   */

  {"olivine", "kirstenite", "CaFeSiO4", 0.05, { 0.00, 0.05, 0.00, 0.00, 0.05, 0.00} },
                  
  /* "diopside",          COMPONENT, "CaMgSi2O6",          */
  /* "clinoenstatite",    COMPONENT, "Mg2Si2O6",           */
  /* "hedenbergite",      COMPONENT, "CaFeSi2O6",          */
  /* "alumino-buffonite", COMPONENT, "CaTi0.5Mg0.5AlSiO6", */
  /* "buffonite",         COMPONENT, "CaTi0.5Mg0.5FeSiO6", */
  /* "essenite",          COMPONENT, "CaFeAlSiO6",         */
  /* "jadeite",           COMPONENT, "NaAlSi2O6",          */  

  {"orthopyroxene", "ferrosilite",   "Fe2Si2O6",  0.00, { 0.00, 0.05, 0.10, 0.00, 0.00, 0.00, 0.00} },

  {"orthopyroxene", "mg-tschermaks", "MgAl2SiO6", 0.00, { 0.00, 0.05, 0.00, 0.05, 0.00, 0.05, 0.00} },
  {"orthopyroxene", "fe-tschermaks", "FeAl2SiO6", 0.00, { 0.00, 0.05, 0.05, 0.05, 0.00, 0.05, 0.00} },
  
  /* "diopside",          COMPONENT, "CaMgSi2O6",          */
  /* "clinoenstatite",    COMPONENT, "Mg2Si2O6",           */
  /* "hedenbergite",      COMPONENT, "CaFeSi2O6",          */
  /* "alumino-buffonite", COMPONENT, "CaTi0.5Mg0.5AlSiO6", */
  /* "buffonite",         COMPONENT, "CaTi0.5Mg0.5FeSiO6", */
  /* "essenite",          COMPONENT, "CaFeAlSiO6",         */
  /* "jadeite",           COMPONENT, "NaAlSi2O6",          */  

  {"clinopyroxene", "ferrosilite",   "Fe2Si2O6",  0.00, { 0.00, 0.05, 0.10, 0.00, 0.00, 0.00, 0.00} },

  {"clinopyroxene", "ca-tschermaks", "CaAl2SiO6", 0.00, { 0.00, 0.00, 0.00, 0.05, 0.00, 0.05, 0.00} }, 
  {"clinopyroxene", "mg-tschermaks", "MgAl2SiO6", 0.00, { 0.00, 0.05, 0.00, 0.05, 0.00, 0.05, 0.00} },
  {"clinopyroxene", "fe-tschermaks", "FeAl2SiO6", 0.00, { 0.00, 0.05, 0.05, 0.05, 0.00, 0.05, 0.00} },

  /* "cummingtonite", "Mg7Si8O22(OH)2",    */
  /* "grunerite",     "Fe7Si8O22(OH)2",    */
  /* "tremolite",     "Ca2Mg5Si8O22(OH)2", */
  
  {"amphibole", "actinolite", "Ca2Fe5Si8O22(OH)2", 0.05, { 0.00, 0.05, 0.05} }, 
  
  /* "pargasite",           "NaCa2Mg4AlAl2Si6O22(OH)2", */
  /* "ferropargasite",      "NaCa2Fe4AlAl2Si6O22(OH)2", */
  /* "magnesiohastingsite", "NaCa2Mg4FeAl2Si6O22(OH)2", */

  {"hornblende", "ferrohastingsite", "NaCa2Fe4FeAl2Si6O22(OH)2", 0.05, { 0.00, 0.05, 0.05} }, 
  
  /* "leucite",    "KAlSi2O6",       */
  /* "analcime",   "NaAlSi2O5(OH)2", */
  /* "na-leucite", "NaAlSi2O6",      */

  {"leucite ss", "K-analcime",   "KAlSi2O5(OH)2", 0.05, { 0.05, 0.05, 0.00} },

  /* "chromite",   "FeCr2O4", */
  /* "hercynite",  "FeAl2O4", */
  /* "magnetite",  "Fe3O4",   */
  /* "spinel",     "MgAl2O4", */
  /* "ulvospinel", "Fe2TiO4", */
  
  {"spinel", "magnesiochromite", "MgCr2O4", 0.00, { 0.05, 0.00, 0.00, 0.05, 0.00} }, 
  {"spinel", "magnesioferrite",  "MgFe2O4", 0.00, { 0.00, 0.00, 0.05, 0.05, 0.00} }, 
  {"spinel", "qandilite",        "Mg2TiO4", 0.00, { 0.00, 0.00, 0.00, 0.10, 0.05} } 
  
  /* "geikielite",  "MgTiO3" */
  /* "hematite",    "Fe2O3"  */
  /* "ilmenite",    "FeTiO3" */
  /* "pyrophanite", "MnTiO3" */
  
};
int nes = (sizeof extraSolids  / sizeof(struct _extraSolids));

#endif /* _Res_Struct_Data_h */
