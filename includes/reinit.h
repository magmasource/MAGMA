#ifndef _Reinit_h
#define _Reinit_h

/*
** In-process re-initialization / failure-recovery hooks.
**
** These let the library recover after a calculation failure (including a
** crash caught by the USESJLJ/USESEH signal handler) without unloading the
** shared library - which the MATLAB C/C++ interface and Python ctypes cannot
** do. Same calculation mode only; switching mode in-process is not supported.
*/

/* --------------------------------------------------------------------------
** Per-phase ordering-cache flush.
** Each pushes the -9999.0 sentinel through the phase's (static) tOld/pOld
** setters so order() recomputes on its next call, discarding any stale or
** partially-computed ordering state left by an aborted solve. Defined in the
** corresponding phase .c file. (biotite-taj.c is excluded: never the active
** biotite model, and its cache is order()-local with no accessors.)
** -------------------------------------------------------------------------- */
void resetOlvOrder(void);
void resetAphOrder(void);
void resetCphOrder(void);
void resetOphOrder(void);
void resetCumOrder(void);
void resetNphOrder(void);
void resetLiqOrder(void);
void resetLiq_CO2Order(void);
void resetLiq_CO2_H2OOrder(void);
void resetMsgOrder(void);
void resetAlbiteOrder(void);
void resetSpnOrder(void);        /* also flushes the pureOrder cache */
void resetCpxOrder(void); /* also flushes the pureOrder cache */
void resetOpxOrder(void); /* also flushes the pureOrder cache */
void resetMelOrder(void);      /* also flushes the pureOrder cache */
void resetRhmOrder(void);  /* also flushes the pureOrder cache */
void resetOoxOrder(void);    /* also flushes the pureOrder cache */

/* Flush every phase's ordering cache at once (defined in library.c). */
void resetAllOrdering(void);

/* Rewind the silmin() solver state machine (defined in silmin.c). Needed
** after an aborted/crashed solve leaves curStep/curStage mid-sequence. It is
** a request flag consumed at the next silmin() entry, so it does not disturb
** normal isenthalpic/isentropic path stepping. */
void resetSilminStateSolver(void);

/* --------------------------------------------------------------------------
** Public entry point (defined in library.c).
**   mode <= 0  or  mode == current calculationMode : failure reset (same mode)
**   mode  > 0  and != current calculationMode      : refused, returns FALSE
**                                                    (mode switching in-process
**                                                     is not supported)
** Returns TRUE on a successful reset, FALSE otherwise.
** -------------------------------------------------------------------------- */
int reinitializeLibrary(int mode);

#endif /* _Reinit_h */
