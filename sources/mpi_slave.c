#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "mpi_common.h"

#ifdef USE_LAM_XLED
#include <ledreq.h>
#endif

double wasteMyTime(int n) {
  return (double) n;
}

int main(int argc, char *argv[]) {
  int size, position, msgsize, membersize, maxSizeIn, maxSizeOut;
  MPI_Comm   comm;
  MPI_Status status;
  char *bufferIn, *bufferOut;
  InputFromMaster   inputFromMaster;
  int info[2], maxloop;

  MPI_Init(&argc, &argv);

  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_get_parent(&comm);
  if (comm == MPI_COMM_NULL) {
    printf("No parent!");
    MPI_Abort(MPI_COMM_WORLD, (1 << 16) + 1);
  }
  
  MPI_Pack_size(1,       MPI_INT,    comm, &membersize); maxSizeIn  = membersize;
  MPI_Pack_size(2+NRMAX, MPI_DOUBLE, comm, &membersize); maxSizeIn += membersize;
  bufferIn  = (char *) malloc((size_t) maxSizeIn);

  MPI_Pack_size(NAMAX,   MPI_DOUBLE, comm, &membersize); maxSizeOut = membersize;
  bufferOut = (char *) malloc((size_t) maxSizeOut);

  MPI_Recv(info, 2, MPI_INT, 0, MPI_ANY_TAG, comm, &status);
  printf("Slave %d received info packet from master.\n", info[0]);

#ifdef USE_LAM_XLED
   (void) lam_ledinit(info[0], info[1]);
   (void) lam_ledclr();
   (void) lam_ledon(3);
#endif

  /* Loop on work requests. */
  for (;;) {
    int i;
    OutputToMaster outputToMaster;
    
    MPI_Recv(bufferIn, maxSizeIn, MPI_PACKED, 0, MPI_ANY_TAG, comm, &status);
    if (status.MPI_TAG == DIETAG) break;
    printf("Slave %d received a data packet from master.\n", info[0]);

    position = 0;
    MPI_Get_count(&status, MPI_PACKED, &msgsize);
    MPI_Unpack(bufferIn, msgsize, &position, &(inputFromMaster.phaseIndex), 1,     MPI_INT,    comm);
    MPI_Unpack(bufferIn, msgsize, &position, &(inputFromMaster.t),          1,     MPI_DOUBLE, comm);
    MPI_Unpack(bufferIn, msgsize, &position, &(inputFromMaster.p),          1,     MPI_DOUBLE, comm);
    MPI_Unpack(bufferIn, msgsize, &position,   inputFromMaster.r,           NRMAX, MPI_DOUBLE, comm);

#ifdef USE_LAM_XLED
   (void) lam_ledon(4);
#endif

    /*************************************************/
    maxloop = rand()/(info[0]+info[1]);
    for (i=0; i<maxloop; i++) (void) wasteMyTime(i);
    for (i=0; i<NAMAX; i++) (outputToMaster.mu)[i] = (double) maxloop;
    /*************************************************/

#ifdef USE_LAM_XLED
   (void) lam_ledoff(4);
#endif

    position = 0;
    MPI_Pack(outputToMaster.mu, NAMAX, MPI_DOUBLE, bufferOut, maxSizeOut, &position, comm);
    MPI_Send(bufferOut, position, MPI_PACKED, 0, REPLYTAG, comm);

  }

#ifdef USE_LAM_XLED
   (void) lam_ledon(5);
#endif

  MPI_Finalize();
  return (0);
}
