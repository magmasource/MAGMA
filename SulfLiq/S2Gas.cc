/*
 * S2Gas implementation
 * $Id: S2Gas.cc,v 1.4 2004/10/29 03:12:44 kress Exp $
 */

#include "S2Gas.h"

static ShomateData s2 = {"S2 gas","S2",64.132,
			 33.51313,5.065360,-1.059670,0.089905,-0.211911,
			 117.6855,266.0919,128.6003};
// note: static in this case makes it local to this file
/* Constructors **********************/
S2Gas::S2Gas() {
  setData(&s2);
  highT = 6000.;
  ShomatePhase::init();
  return;
}

