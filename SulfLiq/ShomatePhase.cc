/* ShomatePhase functions
 * Implements seven-term Shomate form for S and Cp
 * Victor Kress
 * $Id: ShomatePhase.cc,v 1.10 2005/03/31 00:56:30 kress Exp $
 */ 

#include <math.h>
#include "ShomatePhase.h"

ShomatePhase::ShomatePhase() {return;}
ShomatePhase::ShomatePhase(ShomateData *sd) {
  setData(sd);
  return;
}
ShomatePhase::~ShomatePhase() {return;}

// setting methods /////////////////////////////////////
void ShomatePhase::setTk(double ltk) {
  checkT(ltk);
  tk=ltk;
  t=tk/1000.;
  updated=0;
}
void ShomatePhase::setData(ShomateData *sd) {
  dat=sd;
  name=dat->name;
  formula=dat->formula;
  mw=dat->mw;
  updated=0;
}

// getting methods ////////////////////////////////////
double ShomatePhase::getGibbs() {
  double g;
  g = getEnthalpy() - tk*getEntropy();
  return g;
}
double ShomatePhase::getEnthalpy() {
  double h;
  h=(dat->A)*t + (dat->B)*t*t/2. + (dat->C)*t*t*t/3. + (dat->D)*t*t*t*t/4. 
    - (dat->E)/t + dat->F;
  h*=1000.;  // This is an artifact of the Shomate form.  
  return nmoles*h; // Joules/mol
}
double ShomatePhase::getEntropy() {
  double s;
  s=(dat->A)*log(t) + (dat->B)*t + (dat->C)*t*t/2. + (dat->D)*t*t*t/3. 
    - (dat->E)/(2.*t*t) + dat->G;
  return nmoles*s; // Joules/(mol*K)
}
double ShomatePhase::getCp() {
  double cp;
  cp=(dat->A) + (dat->B)*t + (dat->C)*t*t + (dat->D)*t*t*t
    + (dat->E)/(t*t);
  return nmoles*cp; // Joules/(mole*K)
}
double ShomatePhase::getdCpdT() {
  // dCpdTk = dCpdt*dtdTk
  double dcpdt;
  dcpdt = (dat->B) + 2.*(dat->C)*t + 3.*(dat->D)*t*t - 2.*(dat->E)/(t*t*t);
  dcpdt *= nmoles/1000.; //dtdTk
  return dcpdt;
}
void ShomatePhase::init() {
  Phase::init();
  return;
}
 


