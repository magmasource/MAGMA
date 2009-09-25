#include <mpi.h>

#define	DIETAG		1
#define WORKTAG		2
#define REPLYTAG	3

#define NRMAX 10
#define NAMAX (NRMAX+1)

typedef struct {
  int    phaseIndex;
  double t;
  double p;
  double r[NRMAX];
} InputFromMaster, OutputToSlave;

typedef struct {
  double mu[NAMAX];
} OutputToMaster, InputFromSlave;

