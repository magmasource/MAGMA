/* 
 * O2Gas class header file
 * Data from JANAF (Chase et al. 1985)
 * Victor Kress
 * $Id: O2Gas.h,v 1.4 2004/10/19 03:25:05 kress Exp $
 */
#ifndef O2GAS_H
#define O2GAS_H

#include "ShomateIdealGas.h"

/**
   O2 gas class
   Data from JANAF (Chase et al. 1985)
   $Id: O2Gas.h,v 1.4 2004/10/19 03:25:05 kress Exp $
   @author Victor Kress
   @version $Revision: 1.4 $
*/
class O2Gas: public ShomateIdealGas {
 public:
  /// blank constructor
  O2Gas();
  /// destructor
  virtual ~O2Gas();
};

#endif
