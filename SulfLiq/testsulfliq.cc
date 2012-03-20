
/**
   program induces upchuck from SulfLiq class.
   $Id: testsulfliq.cc,v 1.3 2001/05/09 01:50:28 kress Exp $
   Victor Kress
   Started 4/26/01
*/

#include <stdio.h>
#include <iostream.h>
#include "SulfLiq.h"
#include "NumUtil.h"

int main() {
  int i,n;
  double *comp,sum,temp;
  static const double spectol=1.e-16;

  SulfLiq *sol = new SulfLiq();
  n = sol->getNcomp();
  comp = new double[n];

  cout << "TC = ";
  cin >> temp;
  sol->setTk(temp+273.15);

  for (i=0,sum=0.;i<n;i++) {
    cout << sol->getCompName(i) << ": ";
    cin >> comp[i];
    sum+=comp[i];
  }
  for (i=0;i<n;i++) {
    comp[i]/=sum;
  }

  sol->setComps(comp);
  sol->setSpeciateTolerance(spectol);
  sol->printAll();

  cout << "\nTK     = " << sol->getTk();
  cout << "\nlogfo2 = " << sol->getlogfo2();
  cout << "\nlogfs2 = " << sol->getlogfs2();
  cout << "\nisStable = " << sol->isStable();
  sol->printAll();

return 0;
}

/*
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
*/