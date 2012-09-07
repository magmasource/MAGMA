/* 
   ShomateIdealGas code
   Victor Kress
   $Id: ShomateIdealGas.cc,v 1.2 2004/10/21 03:23:21 kress Exp $
*/

#include <math.h>
#include "ShomateIdealGas.h"

ShomateIdealGas::ShomateIdealGas(){
  highP = 4.e7; // optimistic limit for ideal gas.
  return;
}
ShomateIdealGas::ShomateIdealGas(ShomateData *sd) {
  setData(sd);
  return;
}
ShomateIdealGas::~ShomateIdealGas(){return;}

double ShomateIdealGas::getEntropy() {
  double s;
  s = ShomatePhase::getEntropy();
  s += nmoles*R*log(pa/pr);
  return s;
}

void ShomateIdealGas::getdSdm(double *dsdm) {
  dsdm[0]=getEntropy()/nmoles;
  return;
}
void ShomateIdealGas::getd2Sdm2(double **d2sdm2) {
  d2sdm2[0][0]=0.;
  return;
}

double ShomateIdealGas::getVolume() {
  double v;
  v = nmoles*R*tk/pa;
  return v;
}
void ShomateIdealGas::getdVdm(double *dvdm) {
  dvdm[0] = R*tk/pa;
  return;
}
void ShomateIdealGas::getd2Vdm2(double **d2vdm2) {
  d2vdm2[0][0] = 0.;
  return;
}
double ShomateIdealGas::getdVdT() {
  return nmoles*R/pa;
}
double ShomateIdealGas::getdVdP() {
  return -nmoles*R*tk/(pa*pa);
}
double ShomateIdealGas::getd2VdT2() {
  return 0.;
}
double ShomateIdealGas::getd2VdTdP() {
  return -nmoles*R/(pa*pa);
}
double ShomateIdealGas::getd2VdP2() {
  return 2.*nmoles*R*tk/(pa*pa*pa);
}
void ShomateIdealGas::getd2VdmdT(double *d2vdmdt) {
  d2vdmdt[0] = R/pa;
  return;
}
void ShomateIdealGas::getd2VdmdP(double *d2vdmdp) {
  d2vdmdp[0] = -R*tk/(pa*pa);
  return;
}
