/**********************************************************************************/
/* <><><><><> Sections indicated below require configuration for specific cluster */
/**********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "mpi_common.h"

#define ITERS 50

#ifdef USE_LAM_XLED
#include <ledreq.h>
#endif

static int          ntasks;		/* # compute tasks */
static MPI_Comm     *icomm_slaves;	/* inter comm. to each slave */
static MPI_Request  *req_slaves;	/* receive reqs from slaves */
static MPI_Datatype dtype_region;	/* place region into grid */

typedef struct _work {
  OutputToSlave outputToSlave;
  int           index;
  struct _work  *wrk_next;
} Work;

static Work **work_slaves; /* slave's current work   */
static int nwork_out;	   /* # work items out there */
static Work *work_bottom;  /* bottom of work list    */
static Work *work_top;	   /* top of work list       */

static char *bufferOut, **bufferIn;
static int  maxSizeIn, maxSizeOut;

/* insert work into list */
static void insert(Work *pwrk) {
  if (work_top    == 0) { work_top = pwrk;              }
  if (work_bottom != 0) { work_bottom->wrk_next = pwrk; }
  work_bottom = pwrk;
  pwrk->wrk_next = 0;
}

/* gets results */
static int harvest(void) {
  int err, idone;

  nwork_out--;
  err = MPI_Waitany(ntasks, req_slaves, &idone, MPI_STATUS_IGNORE);

  if (err != MPI_SUCCESS) {
    if (idone >= 0) {
      req_slaves[idone] = MPI_REQUEST_NULL;
      MPI_Comm_free(&icomm_slaves[idone]);
      insert(work_slaves[idone]);
    }
    return (-1);
  }

  return (idone);
}

/* distributes work */
static void seed(int islave) {
  int err, position, index = work_top->index;

  position = 0;
  MPI_Pack(&(work_top->outputToSlave).phaseIndex, 1,     MPI_INT,    bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  MPI_Pack(&(work_top->outputToSlave).t,          1,     MPI_DOUBLE, bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  MPI_Pack(&(work_top->outputToSlave).p,          1,     MPI_DOUBLE, bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  MPI_Pack( (work_top->outputToSlave).r,          NRMAX, MPI_DOUBLE, bufferOut, maxSizeOut, &position, icomm_slaves[islave]);
  printf("master: sending request to process %d\n", islave);
  err = MPI_Send(bufferOut, position, MPI_PACKED, 0, WORKTAG, icomm_slaves[islave]);
  if (err != MPI_SUCCESS) { MPI_Comm_free(&icomm_slaves[islave]); return; }

  ++nwork_out;
  work_slaves[islave] = work_top;
  work_top = work_top->wrk_next;
  
  err = MPI_Irecv(bufferIn[index], maxSizeIn, MPI_PACKED, 0, REPLYTAG, icomm_slaves[islave], &req_slaves[islave]);
  if (err != MPI_SUCCESS) {
    req_slaves[islave] = MPI_REQUEST_NULL;
    MPI_Comm_free(&icomm_slaves[islave]);
    insert(work_slaves[islave]);
    --nwork_out;
  }
}

int main(int argc, char *argv[]) {

  void **attrp;
  MPI_Info appInfo;
  char filename[128];
  FILE *fp;
  int flag, membersize, err, i;
  int islave;			/* harvested slave index */
  int return_status = 0;	/* Return status for master */
  Work *p;

  /* Initialize MPI. */

  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

  /* Check that we are the only master */

  if (ntasks != 1) {
    printf("Too many masters. Please launch only 1 copy of\n");
    printf("the master program. It will use MPI_Comm_spawn()\n");
    printf("to create the slaves.\n");
    MPI_Abort(MPI_COMM_WORLD, (1 << 16) + 1);
  }
  
  /* Get universe size */

  MPI_Attr_get(MPI_COMM_WORLD, MPI_UNIVERSE_SIZE, &attrp, &flag);
  if (flag == 1) {
    ntasks  = (int) *attrp; /* LAM determines the number of cpus automatically */
#ifndef USE_LAM_MPI
    ntasks = 4; /* Two processors per xserve node, one from each G4 Powerbook. <><><><><> */
#endif
    printf("This MPI says the Universe Size is %d\n", ntasks);
    ntasks -= (ntasks > 1) ? 1 : 0;  /* There should be one CPU that just runs the master */
  } else {
    printf("This MPI does not support Universe Size, which is needed\n");
    printf("for this example. \n");
    MPI_Abort(MPI_COMM_WORLD, (1 << 16) + 1);
  }

#ifdef USE_LAM_XLED
   (void) lam_ledinit(0, ntasks+1);
   (void) lam_ledclr();
   (void) lam_ledon(0);
#endif

  /* Allocate slave communicator arrays. */

  icomm_slaves = (MPI_Comm *) malloc((size_t) (ntasks * sizeof(MPI_Comm)));
  if (icomm_slaves == NULL) MPI_Abort(MPI_COMM_WORLD, (errno << 16) + 1);

  /* Spawn off the slaves */

#ifdef USE_LAM_MPI
  (void) snprintf(filename, 128, "./lam_fault_appschema.%d", (int) getpid());
  MPI_Info_create(&appInfo);
  MPI_Info_set(appInfo, "file", filename);
  for (i=0; i<ntasks; ++i) {

    /* Create a temporary app schema file */

    fp = fopen(filename, "w");
    if (fp == NULL) {
      printf("Could not open file %s\n", filename);
      MPI_Finalize();
      return 1;
    }
    fprintf(fp, "c%d ./slave\n", i+1);
    fclose(fp);

    /* Spawn */

    MPI_Comm_spawn(NULL, MPI_ARGV_NULL, 0, appInfo, 0, MPI_COMM_SELF, &(icomm_slaves[i]), &err);
    if (err != MPI_SUCCESS) {
      printf("Spawn Error %d\n", err);
      MPI_Abort(MPI_COMM_WORLD, (err << 16) + 1);
    } 
  }
  MPI_Info_free(&appInfo);
  unlink(filename);
#else
  for (i=0; i<ntasks; ++i) {
    printf("Calling MPI_Info_create() for slave %d/%d\n", i, ntasks-1);
    MPI_Info_create(&appInfo);
    printf("...return.\n");
    if      (i == 0) MPI_Info_set(appInfo, "host", "192.168.0.1"); /* <><><><><> */
    else if (i == 1) MPI_Info_set(appInfo, "host", "192.168.0.2"); /* <><><><><> */
    else if (i == 2) MPI_Info_set(appInfo, "host", "192.168.0.2"); /* <><><><><> */
    else if (i == 3) MPI_Info_set(appInfo, "host", "192.168.0.3"); /* <><><><><> */
    else if (i == 4) MPI_Info_set(appInfo, "host", "192.168.0.4"); /* <><><><><> */
    
    printf("Calling MPI_Comm_spawn() for this slave\n");
    MPI_Comm_spawn("slave", MPI_ARGV_NULL, 1, appInfo, 0, MPI_COMM_SELF, &(icomm_slaves[i]), &err);
    printf("...return.\n");
    if (err != MPI_SUCCESS) {
      printf("Spawn Error %d\n", err);
      MPI_Abort(MPI_COMM_WORLD, (err << 16) + 1);
    } 
    
    MPI_Info_free(&appInfo);
  }
#endif  
  /* Tell each slave who they are and how many processes there are */
  for (i=0; i<ntasks; i++) {
    int info[2];
    info[0] = i+1;
    info[1] = ntasks+1;
    MPI_Send(info, 2, MPI_INT, 0, WORKTAG, icomm_slaves[i]);
  }

  /* Allocate slave receive request array. */

  req_slaves = (MPI_Request *) malloc((size_t) (ntasks * sizeof(MPI_Request)));
  if (req_slaves == NULL) MPI_Abort(MPI_COMM_WORLD, (errno << 16) + 1);
  for (i=0; i<ntasks; ++i) req_slaves[i] = MPI_REQUEST_NULL;

  /* Allocate slave work ptr array. */

  work_slaves = (Work **) malloc((size_t) (ntasks * sizeof(struct _work *)));
  if (work_slaves == NULL) MPI_Abort(MPI_COMM_WORLD, (errno << 16) + 1);

  MPI_Pack_size(1,       MPI_INT,    MPI_COMM_WORLD, &membersize); maxSizeOut  = membersize;
  MPI_Pack_size(2+NRMAX, MPI_DOUBLE, MPI_COMM_WORLD, &membersize); maxSizeOut += membersize;
  bufferOut = (char *) malloc((size_t) maxSizeOut);

  MPI_Pack_size(NAMAX,   MPI_DOUBLE, MPI_COMM_WORLD, &membersize); maxSizeIn   = membersize;

  /* set communicators error handlers */

  for (i=0; i<ntasks; ++i) MPI_Errhandler_set(icomm_slaves[i], MPI_ERRORS_RETURN);
  MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

  /* Create the work list. */

  bufferIn = (char **) malloc((size_t) ITERS*sizeof(char *));
  for (i=0; i<ITERS; i++) {
      p = (Work *) malloc((size_t) sizeof(struct _work));
      if (p == 0) MPI_Abort(MPI_COMM_WORLD, errno);

      (p->outputToSlave).phaseIndex = 100;
      (p->outputToSlave).t          = 1500;
      (p->outputToSlave).p          = 10000;
      ((p->outputToSlave).r)[0]     = 0.1;
      ((p->outputToSlave).r)[1]     = 0.2;
      ((p->outputToSlave).r)[2]     = 0.3;
      ((p->outputToSlave).r)[3]     = 0.4;
      ((p->outputToSlave).r)[4]     = 0.5;
      ((p->outputToSlave).r)[5]     = 0.6;
      ((p->outputToSlave).r)[6]     = 0.7;
      ((p->outputToSlave).r)[7]     = 0.8;
      ((p->outputToSlave).r)[8]     = 0.9;
      p->index                      = i;
      p->wrk_next                   = NULL;

      bufferIn[i] = (char *) malloc((size_t) maxSizeIn);

      insert(p);
  }

  nwork_out = 0;

  /* Distribute work to slaves until all the answers have been
   * received or their are no more living slaves. */

#ifdef USE_LAM_XLED
  (void) lam_ledon(1);
#endif

  while (work_top) {
  
    /* Distribute a work order to all living slaves. */

    for (i=0; work_top && (i<ntasks); ++i) {
      if (icomm_slaves[i] == MPI_COMM_NULL) continue;
      seed(i);
    }

    if (nwork_out == 0) {
      printf("master: all slaves are dead\n");
      MPI_Abort(MPI_COMM_WORLD, 1);
    }

    /* Collect results and issue new work orders until there are
     * no outstanding work orders. */

    do {
      islave = harvest();

      if (islave < 0) ++return_status;  /* a node has died */

      if ((islave >= 0) && work_top) seed(islave);
    } while (nwork_out > 0);

    /* After letting living slaves idle due to lack of work, new
     * work orders may appear from slaves that die later.  So
     * start this whole process over with the remaining work
     * orders and living slaves. */
  }
  
  /* Upcak the answers returned by the slaves */
  
#ifdef USE_LAM_XLED
  (void) lam_ledon(2);
#endif

  for (i=0; i<ITERS; i++) {
    InputFromSlave inputFromSlave;
    int position = 0;
    
    MPI_Unpack(bufferIn[i], maxSizeIn, &position, inputFromSlave.mu, NAMAX, MPI_DOUBLE, MPI_COMM_WORLD);
    printf("%4.4d %g %g\n", i, (inputFromSlave.mu)[0], (inputFromSlave.mu)[9]);
  }

  /* We have all the answers now, so kill the living workers. */

  for (i=0; i<ntasks; ++i) {
    if (icomm_slaves[i] == MPI_COMM_NULL) continue;

    err = MPI_Send((void *) 0, 0, MPI_INT, 0, DIETAG, icomm_slaves[i]);
    if (err != MPI_SUCCESS) MPI_Comm_free(&icomm_slaves[i]);
  }

  /* If any one of the slaves died, abort on just myself
   * (MPI_COMM_SELF).  If we abort on MPI_COMM_WORLD, LAM will
   * try to kill all processes (one or more of which is now
   * already dead and possibly unresponsive, so LAM would hang.
   * Hence, just abort on MPI_COMM_SELF).  See the MPI_Abort(3)
   * man page for an explanation of the error code. */

  if (return_status != 0) MPI_Abort(MPI_COMM_SELF, (return_status << 16) + 1);

  /* MPI_Finalize(); This is done to avoid a bug in Open MPI when adding the laptop */ 
  return (0);
}
