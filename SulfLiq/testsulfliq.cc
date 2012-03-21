
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