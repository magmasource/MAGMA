/* ShomateVinetPhase.cc
 * implements Phase using ShomatePhase for T and VinetEOS for pressure integrals.
 * $Id: ShomateVinetPhase.cc,v 1.7 2007/11/16 18:30:12 kress Exp $
 * Victor Kress, San Francisco, 10/26/07
 */

#include "ShomateVinetPhase.h"
#include <math.h>

ShomateVinetPhase::ShomateVinetPhase() {
  Vinet.tr=tr;
  Vinet.pr=pr;
  return;
}
ShomateVinetPhase::~ShomateVinetPhase(void){
  return;
}

void ShomateVinetPhase::init(void) {
  updated=0;
  ShomatePhase::init();
  return;
}

double ShomateVinetPhase::getGibbs() {
  double g;
  update();
  g=ShomatePhase::getGibbs();
  if (pa>pr) {
    g+=Vinet.getMolarGibbsPTerm()*nmoles;
  }
  return g;
}
double ShomateVinetPhase::getEnthalpy() {
  double h;
  update();
  h=ShomatePhase::getEnthalpy();
  if (pa>pr) {
    h+=Vinet.getMolarEnthalpyPTerm()*nmoles;
  }
  return h;
}
double ShomateVinetPhase::getEntropy() {
  double s;
  update();
  s=ShomatePhase::getEntropy();
  if (pa>pr) {
    s+=Vinet.getMolarEntropyPTerm()*nmoles;
  }
  return s;
}
double ShomateVinetPhase::getCp() {
  double cp;
  update();
  cp=ShomatePhase::getCp();
  if (pa>pr) {
    cp+=Vinet.getMolarCpPTerm()*nmoles;
  }
  return cp;
}
double ShomateVinetPhase::getdCpdT() {
  double dd;
  update();
  dd=ShomatePhase::getdCpdT();
  if (pa>pr) {
    dd+=Vinet.getMolardCpdTPTerm()*nmoles;
  }
  return dd;
}
double ShomateVinetPhase::getVolume() {
  double v;
  update();
  v=Vinet.getMolarVolume()*nmoles;
  return v;
}
double ShomateVinetPhase::getdVdT() {
  update();
  return Vinet.getMolardVdT()*nmoles;
}
double ShomateVinetPhase::getdVdP(){
  double dvdp;
  update();
  dvdp=Vinet.getMolardVdP()*nmoles;
  return dvdp;
}  
double ShomateVinetPhase::getd2VdT2(){
  double dd;
  update();
  dd = Vinet.getMolard2VdT2()*nmoles;
  return dd;
}
double ShomateVinetPhase::getd2VdTdP(){
  update();
  return Vinet.getMolard2VdTdP()*nmoles;
}
double ShomateVinetPhase::getd2VdP2() {
  update();
  return Vinet.getMolard2VdP2()*nmoles;
}
void ShomateVinetPhase::update() {
  if (!updated) {
    ShomatePhase::update();
    Vinet.tk=tk;
    Vinet.pa=pa;
    Vinet.update();
    updated=1;
  }
  return;
}


