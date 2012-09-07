/*
 * O2Gas implementation
 * Victor Kress
 * $Id: O2Gas.cc,v 1.5 2004/10/18 21:06:12 kress Exp $
 */

#include "O2Gas.h"

static ShomateData o2 = {"O2 gas","O2",31.9988,
			 29.65900,6.137261,-1.186521,0.095780,-0.219663,
			 -9.861391,237.9480,0.};
// note: static in this case makes it local to this file

O2Gas::O2Gas() {
  setData(&o2);
  highT = 6000.;
  ShomatePhase::init();
  return;
}
O2Gas::~O2Gas() {
  return;
}

