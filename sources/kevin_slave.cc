#include <iostream>
#include <stdio.h>
#include "SulfLiq.h"
#include "O2Gas.h"
#include "FeNiLiq.h"
#include "Chem.h"  

using namespace std;

extern "C" void getPhaseResults(double t, double *alloy, double *results) {
  double o2[] = { 1.0 };
  double fe[] = { 1.0, 0.0 };
  SulfLiq     *sulfLiq;
  O2Gas       *o2Gas;
  FeNiLiq     *feNiLiq;
  
  sulfLiq = new SulfLiq();
  sulfLiq->setTk(t);
  sulfLiq->setPa(100000.0);
  sulfLiq->setGenericCompWts(alloy);
  results[0] = sulfLiq->getMu(2); // mu Fe in sulfide liquid
  
  o2Gas = new O2Gas();
  o2Gas->setTk(t);
  o2Gas->setPa(100000.0);
  o2Gas->setComps(o2);
  results[1] = o2Gas->getGibbs(); // mu O2 gas
 
  feNiLiq = new FeNiLiq();
  feNiLiq->setTk(t);
  feNiLiq->setPa(100000.0);
  feNiLiq->setComps(fe);
  results[2] = feNiLiq->getVolume()*1000000.0; // v0 Fe in sulfide liquid

  delete sulfLiq;
  delete o2Gas;
  delete feNiLiq;
}
