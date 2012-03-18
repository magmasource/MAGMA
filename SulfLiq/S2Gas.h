/* 
 * S2Gas class header file
 * Data from JANAF (Chase et al. 1985)
 * Victor Kress
 */
#ifndef S2GAS_H
#define S2GAS_H

#include "ShomateIdealGas.h"

/**
   S2 gas class
   Data from JANAF (Chase et al. 1985)
   $Id: S2Gas.h,v 1.3 2004/10/19 03:25:05 kress Exp $
   @author Victor Kress
   @version $Revision: 1.3 $
 */
class S2Gas: public ShomateIdealGas {
 public:
  /// blank constructor
  S2Gas();
};

#endif
