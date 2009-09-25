/* simann.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    real u[97], c__, cd, cm;
    integer i97, j97;
} raset1_;

#define raset1_1 raset1_

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int sa_(integer *n, doublereal *x, logical *max__, 
	doublereal *rt, doublereal *eps, integer *ns, integer *nt, integer *
	neps, integer *maxevl, doublereal *lb, doublereal *ub, doublereal *
	c__, integer *iprint, integer *iseed1, integer *iseed2, doublereal *t,
	 doublereal *vm, doublereal *xopt, doublereal *fopt, integer *nacc, 
	integer *nfcnev, integer *nobds, integer *ier, doublereal *fstar, 
	doublereal *xp, integer *nacp)
{
    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);

    /* Local variables */
    static doublereal f;
    static integer h__, i__, j, m;
    static doublereal p, fp, pp;
    extern /* Subroutine */ int fcn_(integer *, doublereal *, doublereal *);
    static integer nup;
    extern /* Subroutine */ int prt1_(void), prt2_(logical *, integer *, 
	    doublereal *, doublereal *), prt3_(logical *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), prt4_(
	    logical *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), prt5_(void), prt6_(logical *), prt7_(logical *), 
	    prt8_(integer *, doublereal *, doublereal *, doublereal *), prt9_(
	    logical *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, integer 
	    *);
    static integer nrej;
    extern /* Subroutine */ int prt10_(void);
    static integer nnew;
    static logical quit;
    static doublereal ratio;
    static integer ndown;
    extern doublereal ranmar_(void);
    static integer lnobds;
    extern /* Subroutine */ int rmarin_(integer *, integer *);
    extern doublereal exprep_(doublereal *);

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 6, 0, "(/,'  THE INITIAL TEMPERATURE IS NOT "
	    "POSITIVE. '                 /,'  RESET THE VARIABLE T. '/)", 0 };
    static cilist io___13 = { 0, 6, 0, "('  POINT ACCEPTED')", 0 };
    static cilist io___14 = { 0, 6, 0, "('  NEW OPTIMUM')", 0 };


/*  Version: 3.2 */
/*  Date: 1/22/94. */
/*  Differences compared to Version 2.0: */
/*     1. If a trial is out of bounds, a point is randomly selected */
/*        from LB(i) to UB(i). Unlike in version 2.0, this trial is */
/*        evaluated and is counted in acceptances and rejections. */
/*        All corresponding documentation was changed as well. */
/*  Differences compared to Version 3.0: */
/*     1. If VM(i) > (UB(i) - LB(i)), VM is set to UB(i) - LB(i). */
/*        The idea is that if T is high relative to LB & UB, most */
/*        points will be accepted, causing VM to rise. But, in this */
/*        situation, VM has little meaning; particularly if VM is */
/*        larger than the acceptable region. Setting VM to this size */
/*        still allows all parts of the allowable region to be selected. */
/*  Differences compared to Version 3.1: */
/*     1. Test made to see if the initial temperature is positive. */
/*     2. WRITE statements prettied up. */
/*     3. References to paper updated. */

/*  Synopsis: */
/*  This routine implements the continuous simulated annealing global */
/*  optimization algorithm described in Corana et al.'s article */
/*  "Minimizing Multimodal Functions of Continuous Variables with the */
/*  "Simulated Annealing" Algorithm" in the September 1987 (vol. 13, */
/*  no. 3, pp. 262-280) issue of the ACM Transactions on Mathematical */
/*  Software. */

/*  A very quick (perhaps too quick) overview of SA: */
/*     SA tries to find the global optimum of an N dimensional function. */
/*  It moves both up and downhill and as the optimization process */
/*  proceeds, it focuses on the most promising area. */
/*     To start, it randomly chooses a trial point within the step length */
/*  VM (a vector of length N) of the user selected starting point. The */
/*  function is evaluated at this trial point and its value is compared */
/*  to its value at the initial point. */
/*     In a maximization problem, all uphill moves are accepted and the */
/*  algorithm continues from that trial point. Downhill moves may be */
/*  accepted; the decision is made by the Metropolis criteria. It uses T */
/*  (temperature) and the size of the downhill move in a probabilistic */
/*  manner. The smaller T and the size of the downhill move are, the more */
/*  likely that move will be accepted. If the trial is accepted, the */
/*  algorithm moves on from that point. If it is rejected, another point */
/*  is chosen instead for a trial evaluation. */
/*     Each element of VM periodically adjusted so that half of all */
/*  function evaluations in that direction are accepted. */
/*     A fall in T is imposed upon the system with the RT variable by */
/*  T(i+1) = RT*T(i) where i is the ith iteration. Thus, as T declines, */
/*  downhill moves are less likely to be accepted and the percentage of */
/*  rejections rise. Given the scheme for the selection for VM, VM falls. */
/*  Thus, as T declines, VM falls and SA focuses upon the most promising */
/*  area for optimization. */

/*  The importance of the parameter T: */
/*     The parameter T is crucial in using SA successfully. It influences */
/*  VM, the step length over which the algorithm searches for optima. For */
/*  a small intial T, the step length may be too small; thus not enough */
/*  of the function might be evaluated to find the global optima. The user */
/*  should carefully examine VM in the intermediate output (set IPRINT = */
/*  1) to make sure that VM is appropriate. The relationship between the */
/*  initial temperature and the resulting step length is function */
/*  dependent. */
/*     To determine the starting temperature that is consistent with */
/*  optimizing a function, it is worthwhile to run a trial run first. Set */
/*  RT = 1.5 and T = 1.0. With RT > 1.0, the temperature increases and VM */
/*  rises as well. Then select the T that produces a large enough VM. */

/*  For modifications to the algorithm and many details on its use, */
/*  (particularly for econometric applications) see Goffe, Ferrier */
/*  and Rogers, "Global Optimization of Statistical Functions with */
/*  Simulated Annealing," Journal of Econometrics, vol. 60, no. 1/2, */
/*  Jan./Feb. 1994, pp. 65-100. */
/*  For more information, contact */
/*              Bill Goffe */
/*              Department of Economics and International Business */
/*              University of Southern Mississippi */
/*              Hattiesburg, MS  39506-5072 */
/*              (601) 266-4484 (office) */
/*              (601) 266-4920 (fax) */
/*              bgoffe@whale.st.usm.edu (Internet) */

/*  As far as possible, the parameters here have the same name as in */
/*  the description of the algorithm on pp. 266-8 of Corana et al. */

/*  In this description, SP is single precision, DP is double precision, */
/*  INT is integer, L is logical and (N) denotes an array of length n. */
/*  Thus, DP(N) denotes a double precision array of length n. */

/*  Input Parameters: */
/*    Note: The suggested values generally come from Corana et al. To */
/*          drastically reduce runtime, see Goffe et al., pp. 90-1 for */
/*          suggestions on choosing the appropriate RT and NT. */
/*    N - Number of variables in the function to be optimized. (INT) */
/*    X - The starting values for the variables of the function to be */
/*        optimized. (DP(N)) */
/*    MAX - Denotes whether the function should be maximized or */
/*          minimized. A true value denotes maximization while a false */
/*          value denotes minimization. Intermediate output (see IPRINT) */
/*          takes this into account. (L) */
/*    RT - The temperature reduction factor. The value suggested by */
/*         Corana et al. is .85. See Goffe et al. for more advice. (DP) */
/*    EPS - Error tolerance for termination. If the final function */
/*          values from the last neps temperatures differ from the */
/*          corresponding value at the current temperature by less than */
/*          EPS and the final function value at the current temperature */
/*          differs from the current optimal function value by less than */
/*          EPS, execution terminates and IER = 0 is returned. (EP) */
/*    NS - Number of cycles. After NS*N function evaluations, each */
/*         element of VM is adjusted so that approximately half of */
/*         all function evaluations are accepted. The suggested value */
/*         is 20. (INT) */
/*    NT - Number of iterations before temperature reduction. After */
/*         NT*NS*N function evaluations, temperature (T) is changed */
/*         by the factor RT. Value suggested by Corana et al. is */
/*         MAX(100, 5*N). See Goffe et al. for further advice. (INT) */
/*    NEPS - Number of final function values used to decide upon termi- */
/*           nation. See EPS. Suggested value is 4. (INT) */
/*    MAXEVL - The maximum number of function evaluations. If it is */
/*             exceeded, IER = 1. (INT) */
/*    LB - The lower bound for the allowable solution variables. (DP(N)) */
/*    UB - The upper bound for the allowable solution variables. (DP(N)) */
/*         If the algorithm chooses X(I) .LT. LB(I) or X(I) .GT. UB(I), */
/*         I = 1, N, a point is from inside is randomly selected. This */
/*         This focuses the algorithm on the region inside UB and LB. */
/*         Unless the user wishes to concentrate the search to a par- */
/*         ticular region, UB and LB should be set to very large positive */
/*         and negative values, respectively. Note that the starting */
/*         vector X should be inside this region. Also note that LB and */
/*         UB are fixed in position, while VM is centered on the last */
/*         accepted trial set of variables that optimizes the function. */
/*    C - Vector that controls the step length adjustment. The suggested */
/*        value for all elements is 2.0. (DP(N)) */
/*    IPRINT - controls printing inside SA. (INT) */
/*             Values: 0 - Nothing printed. */
/*                     1 - Function value for the starting value and */
/*                         summary results before each temperature */
/*                         reduction. This includes the optimal */
/*                         function value found so far, the total */
/*                         number of moves (broken up into uphill, */
/*                         downhill, accepted and rejected), the */
/*                         number of out of bounds trials, the */
/*                         number of new optima found at this */
/*                         temperature, the current optimal X and */
/*                         the step length VM. Note that there are */
/*                         N*NS*NT function evalutations before each */
/*                         temperature reduction. Finally, notice is */
/*                         is also given upon achieveing the termination */
/*                         criteria. */
/*                     2 - Each new step length (VM), the current optimal */
/*                         X (XOPT) and the current trial X (X). This */
/*                         gives the user some idea about how far X */
/*                         strays from XOPT as well as how VM is adapting */
/*                         to the function. */
/*                     3 - Each function evaluation, its acceptance or */
/*                         rejection and new optima. For many problems, */
/*                         this option will likely require a small tree */
/*                         if hard copy is used. This option is best */
/*                         used to learn about the algorithm. A small */
/*                         value for MAXEVL is thus recommended when */
/*                         using IPRINT = 3. */
/*             Suggested value: 1 */
/*             Note: For a given value of IPRINT, the lower valued */
/*                   options (other than 0) are utilized. */
/*    ISEED1 - The first seed for the random number generator RANMAR. */
/*             0 .LE. ISEED1 .LE. 31328. (INT) */
/*    ISEED2 - The second seed for the random number generator RANMAR. */
/*             0 .LE. ISEED2 .LE. 30081. Different values for ISEED1 */
/*             and ISEED2 will lead to an entirely different sequence */
/*             of trial points and decisions on downhill moves (when */
/*             maximizing). See Goffe et al. on how this can be used */
/*             to test the results of SA. (INT) */

/*  Input/Output Parameters: */
/*    T - On input, the initial temperature. See Goffe et al. for advice. */
/*        On output, the final temperature. (DP) */
/*    VM - The step length vector. On input it should encompass the */
/*         region of interest given the starting value X. For point */
/*         X(I), the next trial point is selected is from X(I) - VM(I) */
/*         to  X(I) + VM(I). Since VM is adjusted so that about half */
/*         of all points are accepted, the input value is not very */
/*         important (i.e. is the value is off, SA adjusts VM to the */
/*         correct value). (DP(N)) */

/*  Output Parameters: */
/*    XOPT - The variables that optimize the function. (DP(N)) */
/*    FOPT - The optimal value of the function. (DP) */
/*    NACC - The number of accepted function evaluations. (INT) */
/*    NFCNEV - The total number of function evaluations. In a minor */
/*             point, note that the first evaluation is not used in the */
/*             core of the algorithm; it simply initializes the */
/*             algorithm. (INT). */
/*    NOBDS - The total number of trial function evaluations that */
/*            would have been out of bounds of LB and UB. Note that */
/*            a trial point is randomly selected between LB and UB. */
/*            (INT) */
/*    IER - The error return number. (INT) */
/*          Values: 0 - Normal return; termination criteria achieved. */
/*                  1 - Number of function evaluations (NFCNEV) is */
/*                      greater than the maximum number (MAXEVL). */
/*                  2 - The starting value (X) is not inside the */
/*                      bounds (LB and UB). */
/*                  3 - The initial temperature is not positive. */
/*                  99 - Should not be seen; only used internally. */

/*  Work arrays that must be dimensioned in the calling routine: */
/*       RWK1 (DP(NEPS))  (FSTAR in SA) */
/*       RWK2 (DP(N))     (XP    "  " ) */
/*       IWK  (INT(N))    (NACP  "  " ) */

/*  Required Functions (included): */
/*    EXPREP - Replaces the function EXP to avoid under- and overflows. */
/*             It may have to be modified for non IBM-type main- */
/*             frames. (DP) */
/*    RMARIN - Initializes the random number generator RANMAR. */
/*    RANMAR - The actual random number generator. Note that */
/*             RMARIN must run first (SA does this). It produces uniform */
/*             random numbers on [0,1]. These routines are from */
/*             Usenet's comp.lang.fortran. For a reference, see */
/*             "Toward a Universal Random Number Generator" */
/*             by George Marsaglia and Arif Zaman, Florida State */
/*             University Report: FSU-SCRI-87-50 (1987). */
/*             It was later modified by F. James and published in */
/*             "A Review of Pseudo-random Number Generators." For */
/*             further information, contact stuart@ads.com. These */
/*             routines are designed to be portable on any machine */
/*             with a 24-bit or more mantissa. I have found it produces */
/*             identical results on a IBM 3081 and a Cray Y-MP. */

/*  Required Subroutines (included): */
/*    PRTVEC - Prints vectors. */
/*    PRT1 ... PRT10 - Prints intermediate output. */
/*    FCN - Function to be optimized. The form is */
/*            SUBROUTINE FCN(N,X,F) */
/*            INTEGER N */
/*            DOUBLE PRECISION  X(N), F */
/*            ... */
/*            function code with F = F(X) */
/*            ... */
/*            RETURN */
/*            END */
/*          Note: This is the same form used in the multivariable */
/*          minimization algorithms in the IMSL edition 10 library. */

/*  Machine Specific Features: */
/*    1. EXPREP may have to be modified if used on non-IBM type main- */
/*       frames. Watch for under- and overflows in EXPREP. */
/*    2. Some FORMAT statements use G25.18; this may be excessive for */
/*       some machines. */
/*    3. RMARIN and RANMAR are designed to be protable; they should not */
/*       cause any problems. */
/*  Type all external variables. */
/*  Type all internal variables. */
/*  Type all functions. */
/*  Initialize the random number generator RANMAR. */
    /* Parameter adjustments */
    --nacp;
    --xp;
    --fstar;
    --xopt;
    --vm;
    --c__;
    --ub;
    --lb;
    --x;

    /* Function Body */
    rmarin_(iseed1, iseed2);
/*  Set initial values. */
    *nacc = 0;
    *nobds = 0;
    *nfcnev = 0;
    *ier = 99;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	xopt[i__] = x[i__];
	nacp[i__] = 0;
/* L10: */
    }
    i__1 = *neps;
    for (i__ = 1; i__ <= i__1; ++i__) {
	fstar[i__] = 1e20;
/* L20: */
    }
/*  If the initial temperature is not positive, notify the user and */
/*  return to the calling routine. */
    if (*t <= 0.f) {
	s_wsfe(&io___2);
	e_wsfe();
	*ier = 3;
	return 0;
    }
/*  If the initial value is out of bounds, notify the user and return */
/*  to the calling routine. */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (x[i__] > ub[i__] || x[i__] < lb[i__]) {
	    prt1_();
	    *ier = 2;
	    return 0;
	}
/* L30: */
    }
/*  Evaluate the function with input X and return value as F. */
    fcn_(n, &x[1], &f);
/*  If the function is to be minimized, switch the sign of the function. */
/*  Note that all intermediate and final output switches the sign back */
/*  to eliminate any possible confusion for the user. */
    if (! (*max__)) {
	f = -f;
    }
    ++(*nfcnev);
    *fopt = f;
    fstar[1] = f;
    if (*iprint >= 1) {
	prt2_(max__, n, &x[1], &f);
    }
/*  Start the main loop. Note that it terminates if (i) the algorithm */
/*  succesfully optimizes the function or (ii) there are too many */
/*  function evaluations (more than MAXEVL). */
L100:
    nup = 0;
    nrej = 0;
    nnew = 0;
    ndown = 0;
    lnobds = 0;
    i__1 = *nt;
    for (m = 1; m <= i__1; ++m) {
	i__2 = *ns;
	for (j = 1; j <= i__2; ++j) {
	    i__3 = *n;
	    for (h__ = 1; h__ <= i__3; ++h__) {
/*  Generate XP, the trial value of X. Note use of VM to choose XP. */
		i__4 = *n;
		for (i__ = 1; i__ <= i__4; ++i__) {
		    if (i__ == h__) {
			xp[i__] = x[i__] + (ranmar_() * 2.f - 1.f) * vm[i__];
		    } else {
			xp[i__] = x[i__];
		    }
/*  If XP is out of bounds, select a point in bounds for the trial. */
		    if (xp[i__] < lb[i__] || xp[i__] > ub[i__]) {
			xp[i__] = lb[i__] + (ub[i__] - lb[i__]) * ranmar_();
			++lnobds;
			++(*nobds);
			if (*iprint >= 3) {
			    prt3_(max__, n, &xp[1], &x[1], &fp, &f);
			}
		    }
/* L110: */
		}
/*  Evaluate the function with the trial point XP and return as FP. */
		fcn_(n, &xp[1], &fp);
		if (! (*max__)) {
		    fp = -fp;
		}
		++(*nfcnev);
		if (*iprint >= 3) {
		    prt4_(max__, n, &xp[1], &x[1], &fp, &f);
		}
/*  If too many function evaluations occur, terminate the algorithm. */
		if (*nfcnev >= *maxevl) {
		    prt5_();
		    if (! (*max__)) {
			*fopt = -(*fopt);
		    }
		    *ier = 1;
		    return 0;
		}
/*  Accept the new point if the function value increases. */
		if (fp >= f) {
		    if (*iprint >= 3) {
			s_wsfe(&io___13);
			e_wsfe();
		    }
		    i__4 = *n;
		    for (i__ = 1; i__ <= i__4; ++i__) {
			x[i__] = xp[i__];
/* L120: */
		    }
		    f = fp;
		    ++(*nacc);
		    ++nacp[h__];
		    ++nup;
/*  If greater than any other point, record as new optimum. */
		    if (fp > *fopt) {
			if (*iprint >= 3) {
			    s_wsfe(&io___14);
			    e_wsfe();
			}
			i__4 = *n;
			for (i__ = 1; i__ <= i__4; ++i__) {
			    xopt[i__] = xp[i__];
/* L130: */
			}
			*fopt = fp;
			++nnew;
		    }
/*  If the point is lower, use the Metropolis criteria to decide on */
/*  acceptance or rejection. */
		} else {
		    d__1 = (fp - f) / *t;
		    p = exprep_(&d__1);
		    pp = ranmar_();
		    if (pp < p) {
			if (*iprint >= 3) {
			    prt6_(max__);
			}
			i__4 = *n;
			for (i__ = 1; i__ <= i__4; ++i__) {
			    x[i__] = xp[i__];
/* L140: */
			}
			f = fp;
			++(*nacc);
			++nacp[h__];
			++ndown;
		    } else {
			++nrej;
			if (*iprint >= 3) {
			    prt7_(max__);
			}
		    }
		}
/* L200: */
	    }
/* L300: */
	}
/*  Adjust VM so that approximately half of all evaluations are accepted. */
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ratio = (doublereal) nacp[i__] / (doublereal) (*ns);
	    if (ratio > .6f) {
		vm[i__] *= c__[i__] * (ratio - .6f) / .4f + 1.f;
	    } else if (ratio < .4f) {
		vm[i__] /= c__[i__] * ((.4f - ratio) / .4f) + 1.f;
	    }
	    if (vm[i__] > ub[i__] - lb[i__]) {
		vm[i__] = ub[i__] - lb[i__];
	    }
/* L310: */
	}
	if (*iprint >= 2) {
	    prt8_(n, &vm[1], &xopt[1], &x[1]);
	}
	i__2 = *n;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    nacp[i__] = 0;
/* L320: */
	}
/* L400: */
    }
    if (*iprint >= 1) {
	prt9_(max__, n, t, &xopt[1], &vm[1], fopt, &nup, &ndown, &nrej, &
		lnobds, &nnew);
    }
/*  Check termination criteria. */
    quit = FALSE_;
    fstar[1] = f;
    if (*fopt - fstar[1] <= *eps) {
	quit = TRUE_;
    }
    i__1 = *neps;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if ((d__1 = f - fstar[i__], abs(d__1)) > *eps) {
	    quit = FALSE_;
	}
/* L410: */
    }
/*  Terminate SA if appropriate. */
    if (quit) {
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    x[i__] = xopt[i__];
/* L420: */
	}
	*ier = 0;
	if (! (*max__)) {
	    *fopt = -(*fopt);
	}
	if (*iprint >= 1) {
	    prt10_();
	}
	return 0;
    }
/*  If termination criteria is not met, prepare for another loop. */
    *t = *rt * *t;
    for (i__ = *neps; i__ >= 2; --i__) {
	fstar[i__] = fstar[i__ - 1];
/* L430: */
    }
    f = *fopt;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	x[i__] = xopt[i__];
/* L440: */
    }
/*  Loop again. */
    goto L100;
} /* sa_ */

doublereal exprep_(doublereal *rdum)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal);

/*  This function replaces exp to avoid under- and overflows and is */
/*  designed for IBM 370 type machines. It may be necessary to modify */
/*  it for other machines. Note that the maximum and minimum values of */
/*  EXPREP are such that they has no effect on the algorithm. */
    if (*rdum > 174.f) {
	ret_val = 3.69e75;
    } else if (*rdum < -180.f) {
	ret_val = 0.f;
    } else {
	ret_val = exp(*rdum);
    }
    return ret_val;
} /* exprep_ */

/* Subroutine */ int rmarin_(integer *ij, integer *kl)
{
    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, k, l, m;
    static real s, t;
    static integer ii, jj;

    /* Fortran I/O blocks */
    static cilist io___19 = { 0, 6, 0, "(A)", 0 };
    static cilist io___20 = { 0, 6, 0, "(A)", 0 };


/*  This subroutine and the next function generate random numbers. See */
/*  the comments for SA for more information. The only changes from the */
/*  orginal code is that (1) the test to make sure that RMARIN runs first */
/*  was taken out since SA assures that this is done (this test didn't */
/*  compile under IBM's VS Fortran) and (2) typing ivec as integer was */
/*  taken out since ivec isn't used. With these exceptions, all following */
/*  lines are original. */
/* This is the initialization routine for the random number generator */
/*     RANMAR() */
/* NOTE: The seed variables can have values between:    0 <= IJ <= 31328 */
/*                                                      0 <= KL <= 30081 */
    if (*ij < 0 || *ij > 31328 || *kl < 0 || *kl > 30081) {
	s_wsfe(&io___19);
	do_fio(&c__1, " The first random number seed must have a value betwe"
		"en 0 and 31328", (ftnlen)67);
	e_wsfe();
	s_wsfe(&io___20);
	do_fio(&c__1, " The second seed must have a value between 0 and 30081"
		, (ftnlen)54);
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
    i__ = *ij / 177 % 177 + 2;
    j = *ij % 177 + 2;
    k = *kl / 169 % 178 + 1;
    l = *kl % 169;
    for (ii = 1; ii <= 97; ++ii) {
	s = 0.f;
	t = .5f;
	for (jj = 1; jj <= 24; ++jj) {
	    m = i__ * j % 179 * k % 179;
	    i__ = j;
	    j = k;
	    k = m;
	    l = (l * 53 + 1) % 169;
	    if (l * m % 64 >= 32) {
		s += t;
	    }
	    t *= .5f;
/* L3: */
	}
	raset1_1.u[ii - 1] = s;
/* L2: */
    }
    raset1_1.c__ = .021602869033813477f;
    raset1_1.cd = .45623308420181274f;
    raset1_1.cm = .99999982118606567f;
    raset1_1.i97 = 97;
    raset1_1.j97 = 33;
    return 0;
} /* rmarin_ */

doublereal ranmar_(void)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    static real uni;

    uni = raset1_1.u[raset1_1.i97 - 1] - raset1_1.u[raset1_1.j97 - 1];
    if (uni < 0.f) {
	uni += 1.f;
    }
    raset1_1.u[raset1_1.i97 - 1] = uni;
    --raset1_1.i97;
    if (raset1_1.i97 == 0) {
	raset1_1.i97 = 97;
    }
    --raset1_1.j97;
    if (raset1_1.j97 == 0) {
	raset1_1.j97 = 97;
    }
    raset1_1.c__ -= raset1_1.cd;
    if (raset1_1.c__ < 0.f) {
	raset1_1.c__ += raset1_1.cm;
    }
    uni -= raset1_1.c__;
    if (uni < 0.f) {
	uni += 1.f;
    }
    ret_val = uni;
    return ret_val;
} /* ranmar_ */

/* Subroutine */ int prt1_(void)
{
    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);

    /* Fortran I/O blocks */
    static cilist io___31 = { 0, 6, 0, "(/,'  THE STARTING VALUE (X) IS OUTS"
	    "IDE THE BOUNDS '             /,'  (LB AND UB). EXECUTION TERMINA"
	    "TED WITHOUT ANY'             /,'  OPTIMIZATION. RESPECIFY X, UB "
	    "OR LB SO THAT  '             /,'  LB(I) .LT. X(I) .LT. UB(I), I "
	    "= 1, N. '/)", 0 };


/*  This subroutine prints intermediate output, as does PRT2 through */
/*  PRT10. Note that if SA is minimizing the function, the sign of the */
/*  function value and the directions (up/down) are reversed in all */
/*  output to correspond with the actual function optimization. This */
/*  correction is because SA was written to maximize functions and */
/*  it minimizes by maximizing the negative a function. */
    s_wsfe(&io___31);
    e_wsfe();
    return 0;
} /* prt1_ */

/* Subroutine */ int prt2_(logical *max__, integer *n, doublereal *x, 
	doublereal *f)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int prtvec_(doublereal *, integer *, char *, 
	    ftnlen);

    /* Fortran I/O blocks */
    static cilist io___32 = { 0, 6, 0, "('  ')", 0 };
    static cilist io___33 = { 0, 6, 0, "('  INITIAL F: ',/, G25.18)", 0 };
    static cilist io___34 = { 0, 6, 0, "('  INITIAL F: ',/, G25.18)", 0 };


    /* Parameter adjustments */
    --x;

    /* Function Body */
    s_wsfe(&io___32);
    e_wsfe();
    prtvec_(&x[1], n, "INITIAL X", (ftnlen)9);
    if (*max__) {
	s_wsfe(&io___33);
	do_fio(&c__1, (char *)&(*f), (ftnlen)sizeof(doublereal));
	e_wsfe();
    } else {
	s_wsfe(&io___34);
	d__1 = -(*f);
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    return 0;
} /* prt2_ */

/* Subroutine */ int prt3_(logical *max__, integer *n, doublereal *xp, 
	doublereal *x, doublereal *fp, doublereal *f)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int prtvec_(doublereal *, integer *, char *, 
	    ftnlen);

    /* Fortran I/O blocks */
    static cilist io___35 = { 0, 6, 0, "('  ')", 0 };
    static cilist io___36 = { 0, 6, 0, "('  CURRENT F: ',G25.18)", 0 };
    static cilist io___37 = { 0, 6, 0, "('  CURRENT F: ',G25.18)", 0 };
    static cilist io___38 = { 0, 6, 0, "('  POINT REJECTED SINCE OUT OF BOUN"
	    "DS')", 0 };


    /* Parameter adjustments */
    --x;
    --xp;

    /* Function Body */
    s_wsfe(&io___35);
    e_wsfe();
    prtvec_(&x[1], n, "CURRENT X", (ftnlen)9);
    if (*max__) {
	s_wsfe(&io___36);
	do_fio(&c__1, (char *)&(*f), (ftnlen)sizeof(doublereal));
	e_wsfe();
    } else {
	s_wsfe(&io___37);
	d__1 = -(*f);
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    prtvec_(&xp[1], n, "TRIAL X", (ftnlen)7);
    s_wsfe(&io___38);
    e_wsfe();
    return 0;
} /* prt3_ */

/* Subroutine */ int prt4_(logical *max__, integer *n, doublereal *xp, 
	doublereal *x, doublereal *fp, doublereal *f)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int prtvec_(doublereal *, integer *, char *, 
	    ftnlen);

    /* Fortran I/O blocks */
    static cilist io___39 = { 0, 6, 0, "('  ')", 0 };
    static cilist io___40 = { 0, 6, 0, "('  CURRENT F: ',G25.18)", 0 };
    static cilist io___41 = { 0, 6, 0, "('  RESULTING F: ',G25.18)", 0 };
    static cilist io___42 = { 0, 6, 0, "('  CURRENT F: ',G25.18)", 0 };
    static cilist io___43 = { 0, 6, 0, "('  RESULTING F: ',G25.18)", 0 };


    /* Parameter adjustments */
    --x;
    --xp;

    /* Function Body */
    s_wsfe(&io___39);
    e_wsfe();
    prtvec_(&x[1], n, "CURRENT X", (ftnlen)9);
    if (*max__) {
	s_wsfe(&io___40);
	do_fio(&c__1, (char *)&(*f), (ftnlen)sizeof(doublereal));
	e_wsfe();
	prtvec_(&xp[1], n, "TRIAL X", (ftnlen)7);
	s_wsfe(&io___41);
	do_fio(&c__1, (char *)&(*fp), (ftnlen)sizeof(doublereal));
	e_wsfe();
    } else {
	s_wsfe(&io___42);
	d__1 = -(*f);
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsfe();
	prtvec_(&xp[1], n, "TRIAL X", (ftnlen)7);
	s_wsfe(&io___43);
	d__1 = -(*fp);
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    return 0;
} /* prt4_ */

/* Subroutine */ int prt5_(void)
{
    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);

    /* Fortran I/O blocks */
    static cilist io___44 = { 0, 6, 0, "(/,'  TOO MANY FUNCTION EVALUATIONS;"
	    " CONSIDER '                  /,'  INCREASING MAXEVL OR EPS, OR D"
	    "ECREASING '                  /,'  NT OR RT. THESE RESULTS ARE LI"
	    "KELY TO BE '                 /,'  POOR.',/)", 0 };


    s_wsfe(&io___44);
    e_wsfe();
    return 0;
} /* prt5_ */

/* Subroutine */ int prt6_(logical *max__)
{
    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);

    /* Fortran I/O blocks */
    static cilist io___45 = { 0, 6, 0, "('  THOUGH LOWER, POINT ACCEPTED')", 
	    0 };
    static cilist io___46 = { 0, 6, 0, "('  THOUGH HIGHER, POINT ACCEPTED')", 
	    0 };


    if (*max__) {
	s_wsfe(&io___45);
	e_wsfe();
    } else {
	s_wsfe(&io___46);
	e_wsfe();
    }
    return 0;
} /* prt6_ */

/* Subroutine */ int prt7_(logical *max__)
{
    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);

    /* Fortran I/O blocks */
    static cilist io___47 = { 0, 6, 0, "('  LOWER POINT REJECTED')", 0 };
    static cilist io___48 = { 0, 6, 0, "('  HIGHER POINT REJECTED')", 0 };


    if (*max__) {
	s_wsfe(&io___47);
	e_wsfe();
    } else {
	s_wsfe(&io___48);
	e_wsfe();
    }
    return 0;
} /* prt7_ */

/* Subroutine */ int prt8_(integer *n, doublereal *vm, doublereal *xopt, 
	doublereal *x)
{
    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);

    /* Local variables */
    extern /* Subroutine */ int prtvec_(doublereal *, integer *, char *, 
	    ftnlen);

    /* Fortran I/O blocks */
    static cilist io___49 = { 0, 6, 0, "(/,                                 "
	    "                       ' INTERMEDIATE RESULTS AFTER STEP LENGTH "
	    "ADJUSTMENT',/)", 0 };
    static cilist io___50 = { 0, 6, 0, "(' ')", 0 };


    /* Parameter adjustments */
    --x;
    --xopt;
    --vm;

    /* Function Body */
    s_wsfe(&io___49);
    e_wsfe();
    prtvec_(&vm[1], n, "NEW STEP LENGTH (VM)", (ftnlen)20);
    prtvec_(&xopt[1], n, "CURRENT OPTIMAL X", (ftnlen)17);
    prtvec_(&x[1], n, "CURRENT X", (ftnlen)9);
    s_wsfe(&io___50);
    e_wsfe();
    return 0;
} /* prt8_ */

/* Subroutine */ int prt9_(logical *max__, integer *n, doublereal *t, 
	doublereal *xopt, doublereal *vm, doublereal *fopt, integer *nup, 
	integer *ndown, integer *nrej, integer *lnobds, integer *nnew)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int prtvec_(doublereal *, integer *, char *, 
	    ftnlen);
    static integer totmov;

    /* Fortran I/O blocks */
    static cilist io___52 = { 0, 6, 0, "(/,                                 "
	    "                       ' INTERMEDIATE RESULTS BEFORE NEXT TEMPER"
	    "ATURE REDUCTION',/)", 0 };
    static cilist io___53 = { 0, 6, 0, "('  CURRENT TEMPERATURE:            "
	    "',G12.5)", 0 };
    static cilist io___54 = { 0, 6, 0, "('  MAX FUNCTION VALUE SO FAR:  ',G2"
	    "5.18)", 0 };
    static cilist io___55 = { 0, 6, 0, "('  TOTAL MOVES:                ',I8)"
	    , 0 };
    static cilist io___56 = { 0, 6, 0, "('     UPHILL:                  ',I8)"
	    , 0 };
    static cilist io___57 = { 0, 6, 0, "('     ACCEPTED DOWNHILL:       ',I8)"
	    , 0 };
    static cilist io___58 = { 0, 6, 0, "('     REJECTED DOWNHILL:       ',I8)"
	    , 0 };
    static cilist io___59 = { 0, 6, 0, "('  OUT OF BOUNDS TRIALS:       ',I8)"
	    , 0 };
    static cilist io___60 = { 0, 6, 0, "('  NEW MAXIMA THIS TEMPERATURE:',I8)"
	    , 0 };
    static cilist io___61 = { 0, 6, 0, "('  MIN FUNCTION VALUE SO FAR:  ',G2"
	    "5.18)", 0 };
    static cilist io___62 = { 0, 6, 0, "('  TOTAL MOVES:                ',I8)"
	    , 0 };
    static cilist io___63 = { 0, 6, 0, "('     DOWNHILL:                ',I8)"
	    , 0 };
    static cilist io___64 = { 0, 6, 0, "('     ACCEPTED UPHILL:         ',I8)"
	    , 0 };
    static cilist io___65 = { 0, 6, 0, "('     REJECTED UPHILL:         ',I8)"
	    , 0 };
    static cilist io___66 = { 0, 6, 0, "('  TRIALS OUT OF BOUNDS:       ',I8)"
	    , 0 };
    static cilist io___67 = { 0, 6, 0, "('  NEW MINIMA THIS TEMPERATURE:',I8)"
	    , 0 };
    static cilist io___68 = { 0, 6, 0, "(' ')", 0 };


    /* Parameter adjustments */
    --vm;
    --xopt;

    /* Function Body */
    totmov = *nup + *ndown + *nrej;
    s_wsfe(&io___52);
    e_wsfe();
    s_wsfe(&io___53);
    do_fio(&c__1, (char *)&(*t), (ftnlen)sizeof(doublereal));
    e_wsfe();
    if (*max__) {
	s_wsfe(&io___54);
	do_fio(&c__1, (char *)&(*fopt), (ftnlen)sizeof(doublereal));
	e_wsfe();
	s_wsfe(&io___55);
	do_fio(&c__1, (char *)&totmov, (ftnlen)sizeof(integer));
	e_wsfe();
	s_wsfe(&io___56);
	do_fio(&c__1, (char *)&(*nup), (ftnlen)sizeof(integer));
	e_wsfe();
	s_wsfe(&io___57);
	do_fio(&c__1, (char *)&(*ndown), (ftnlen)sizeof(integer));
	e_wsfe();
	s_wsfe(&io___58);
	do_fio(&c__1, (char *)&(*nrej), (ftnlen)sizeof(integer));
	e_wsfe();
	s_wsfe(&io___59);
	do_fio(&c__1, (char *)&(*lnobds), (ftnlen)sizeof(integer));
	e_wsfe();
	s_wsfe(&io___60);
	do_fio(&c__1, (char *)&(*nnew), (ftnlen)sizeof(integer));
	e_wsfe();
    } else {
	s_wsfe(&io___61);
	d__1 = -(*fopt);
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsfe();
	s_wsfe(&io___62);
	do_fio(&c__1, (char *)&totmov, (ftnlen)sizeof(integer));
	e_wsfe();
	s_wsfe(&io___63);
	do_fio(&c__1, (char *)&(*nup), (ftnlen)sizeof(integer));
	e_wsfe();
	s_wsfe(&io___64);
	do_fio(&c__1, (char *)&(*ndown), (ftnlen)sizeof(integer));
	e_wsfe();
	s_wsfe(&io___65);
	do_fio(&c__1, (char *)&(*nrej), (ftnlen)sizeof(integer));
	e_wsfe();
	s_wsfe(&io___66);
	do_fio(&c__1, (char *)&(*lnobds), (ftnlen)sizeof(integer));
	e_wsfe();
	s_wsfe(&io___67);
	do_fio(&c__1, (char *)&(*nnew), (ftnlen)sizeof(integer));
	e_wsfe();
    }
    prtvec_(&xopt[1], n, "CURRENT OPTIMAL X", (ftnlen)17);
    prtvec_(&vm[1], n, "STEP LENGTH (VM)", (ftnlen)16);
    s_wsfe(&io___68);
    e_wsfe();
    return 0;
} /* prt9_ */

/* Subroutine */ int prt10_(void)
{
    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);

    /* Fortran I/O blocks */
    static cilist io___69 = { 0, 6, 0, "(/,'  SA ACHIEVED TERMINATION CRITER"
	    "IA. IER = 0. ',/)", 0 };


    s_wsfe(&io___69);
    e_wsfe();
    return 0;
} /* prt10_ */

/* Subroutine */ int prtvec_(doublereal *vector, integer *ncols, char *name__,
	 ftnlen name_len)
{
    /* Format strings */
    static char fmt_1001[] = "(/,25x,a)";
    static char fmt_1000[] = "(10(g12.5,1x))";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, j, ll, lines;

    /* Fortran I/O blocks */
    static cilist io___70 = { 0, 6, 0, fmt_1001, 0 };
    static cilist io___74 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___76 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___77 = { 0, 6, 0, fmt_1000, 0 };


/*  This subroutine prints the double precision vector named VECTOR. */
/*  Elements 1 thru NCOLS will be printed. NAME is a character variable */
/*  that describes VECTOR. Note that if NAME is given in the call to */
/*  PRTVEC, it must be enclosed in quotes. If there are more than 10 */
/*  elements in VECTOR, 10 elements will be printed on each line. */
    /* Parameter adjustments */
    --vector;

    /* Function Body */
    s_wsfe(&io___70);
    do_fio(&c__1, name__, name_len);
    e_wsfe();
    if (*ncols > 10) {
	lines = (integer) (*ncols / 10.f);
	i__1 = lines;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    ll = (i__ - 1) * 10;
	    s_wsfe(&io___74);
	    i__2 = ll + 10;
	    for (j = ll + 1; j <= i__2; ++j) {
		do_fio(&c__1, (char *)&vector[j], (ftnlen)sizeof(doublereal));
	    }
	    e_wsfe();
/* L100: */
	}
	s_wsfe(&io___76);
	i__1 = *ncols;
	for (j = ll + 11; j <= i__1; ++j) {
	    do_fio(&c__1, (char *)&vector[j], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
    } else {
	s_wsfe(&io___77);
	i__1 = *ncols;
	for (j = 1; j <= i__1; ++j) {
	    do_fio(&c__1, (char *)&vector[j], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
    }
    return 0;
} /* prtvec_ */

