/* superfl.f -- translated by f2c (version 20030320).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;
static integer c__9 = 9;
static integer c__4 = 4;
static integer c__3 = 3;
static integer c__5 = 5;

/* Main program */ int MAIN__(void)
{
    /* Initialized data */

    static char name__[3*13] = "H2O" "CO2" "CH4" " CO" " O2" " H2" " S2" 
	    "SO2" "COS" "H2S" " N2" "NH3" " Ar";

    /* Format strings */
    static char fmt_12[] = "(\002         1   2   3   4   5   6   7   8   9 "
	    " 10  11  12  13 \002)";
    static char fmt_35[] = "(\002               T = \002,f14.2,\002   (K)"
	    " \002)";
    static char fmt_36[] = "(\002               P = \002,f14.2,\002   (bar)"
	    " \002)";
    static char fmt_37[] = "(\002               V = \002,f16.4,\002 (cm^3/mo"
	    "l) \002)";
    static char fmt_38[] = "(\002               G = \002,f14.2,\002   (J/mol"
	    ") \002)";
    static char fmt_303[] = "(\002 -----------------------------------------"
	    "-------------------------\002)";
    static char fmt_302[] = "(\002  N  Name    Xi     Gamma     FugCoeff    "
	    "   Gi\002,8x,\002 Fugacity\002)";
    static char fmt_301[] = "(1x,i2,2x,a3,f8.4,f10.6,e13.5,f12.2,e15.6)";

    /* System generated locals */
    doublereal d__1;
    olist o__1;

    /* Builtin functions */
    integer f_open(olist *), s_wsle(cilist *), e_wsle(void), s_wsfe(cilist *),
	     do_fio(integer *, char *, ftnlen), e_wsfe(void), do_lio(integer *
	    , integer *, char *, ftnlen), s_rsle(cilist *), e_rsle(void);
    double log(doublereal), exp(doublereal);
    integer s_rsfe(cilist *), e_rsfe(void);

    /* Local variables */
    static doublereal g;
    static integer i__;
    static doublereal p, t, v;
    static doublereal x[13], gg;
    static doublereal gi[13];
    static doublereal pp;
    static doublereal rt;
    static char yn[1];
    static doublereal tt, vv, xt, xx[13], ggi[13];
    static integer iii;
    static doublereal fug[13], gama[13];
    static doublereal gbar;
    extern /* Subroutine */ int fder_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *);
    static integer igas;
    static doublereal vbar, gsum, g1bar, p1bar, v1bar;
    extern /* Subroutine */ int fluid_(doublereal *, doublereal *, doublereal *, doublereal *, doublereal *)
	    ;
    static doublereal xpure[13];

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 6, 0, 0, 0 };
    static cilist io___3 = { 0, 6, 0, 0, 0 };
    static cilist io___4 = { 0, 6, 0, "(13x,a)", 0 };
    static cilist io___5 = { 0, 6, 0, "(13x,a)", 0 };
    static cilist io___6 = { 0, 6, 0, "(13x,a)", 0 };
    static cilist io___7 = { 0, 6, 0, "(13x,a)", 0 };
    static cilist io___8 = { 0, 6, 0, "(13x,a)", 0 };
    static cilist io___9 = { 0, 6, 0, "(13x,a)", 0 };
    static cilist io___10 = { 0, 6, 0, "(13x,a)", 0 };
    static cilist io___11 = { 0, 6, 0, "(13x,a)", 0 };
    static cilist io___12 = { 0, 6, 0, "(13x,a)", 0 };
    static cilist io___13 = { 0, 6, 0, 0, 0 };
    static cilist io___14 = { 0, 6, 0, 0, 0 };
    static cilist io___15 = { 0, 6, 0, 0, 0 };
    static cilist io___16 = { 0, 6, 0, 0, 0 };
    static cilist io___17 = { 0, 6, 0, 0, 0 };
    static cilist io___18 = { 0, 6, 0, 0, 0 };
    static cilist io___19 = { 0, 6, 0, 0, 0 };
    static cilist io___20 = { 0, 6, 0, 0, 0 };
    static cilist io___21 = { 0, 6, 0, 0, 0 };
    static cilist io___22 = { 0, 6, 0, 0, 0 };
    static cilist io___23 = { 0, 6, 0, 0, 0 };
    static cilist io___24 = { 0, 6, 0, 0, 0 };
    static cilist io___25 = { 0, 6, 0, 0, 0 };
    static cilist io___26 = { 0, 6, 0, 0, 0 };
    static cilist io___27 = { 0, 6, 0, 0, 0 };
    static cilist io___28 = { 0, 6, 0, 0, 0 };
    static cilist io___29 = { 0, 6, 0, 0, 0 };
    static cilist io___30 = { 0, 6, 0, 0, 0 };
    static cilist io___31 = { 0, 6, 0, 0, 0 };
    static cilist io___32 = { 0, 6, 0, 0, 0 };
    static cilist io___33 = { 0, 6, 0, 0, 0 };
    static cilist io___34 = { 0, 10, 0, 0, 0 };
    static cilist io___35 = { 0, 10, 0, 0, 0 };
    static cilist io___36 = { 0, 10, 0, 0, 0 };
    static cilist io___37 = { 0, 10, 0, 0, 0 };
    static cilist io___38 = { 0, 10, 0, 0, 0 };
    static cilist io___39 = { 0, 10, 0, 0, 0 };
    static cilist io___40 = { 0, 10, 0, 0, 0 };
    static cilist io___41 = { 0, 6, 0, 0, 0 };
    static cilist io___42 = { 0, 10, 0, 0, 0 };
    static cilist io___44 = { 0, 6, 0, 0, 0 };
    static cilist io___45 = { 0, 6, 0, 0, 0 };
    static cilist io___46 = { 0, 6, 0, 0, 0 };
    static cilist io___47 = { 0, 6, 0, "(a18,$)", 0 };
    static cilist io___48 = { 0, 5, 0, 0, 0 };
    static cilist io___60 = { 0, 6, 0, 0, 0 };
    static cilist io___61 = { 0, 6, 0, 0, 0 };
    static cilist io___62 = { 0, 6, 0, 0, 0 };
    static cilist io___63 = { 0, 6, 0, 0, 0 };
    static cilist io___64 = { 0, 6, 0, 0, 0 };
    static cilist io___65 = { 0, 6, 0, fmt_12, 0 };
    static cilist io___66 = { 0, 6, 0, "(6X,13(A4))", 0 };
    static cilist io___67 = { 0, 6, 0, 0, 0 };
    static cilist io___68 = { 0, 6, 0, "(A22,$)", 0 };
    static cilist io___69 = { 0, 5, 0, 0, 0 };
    static cilist io___71 = { 0, 6, 0, 0, 0 };
    static cilist io___72 = { 0, 6, 0, "(A31,A3,A4,$)", 0 };
    static cilist io___73 = { 0, 5, 0, 0, 0 };
    static cilist io___74 = { 0, 6, 0, 0, 0 };
    static cilist io___75 = { 0, 6, 0, 0, 0 };
    static cilist io___76 = { 0, 6, 0, 0, 0 };
    static cilist io___77 = { 0, 6, 0, 0, 0 };
    static cilist io___78 = { 0, 6, 0, 0, 0 };
    static cilist io___79 = { 0, 6, 0, 0, 0 };
    static cilist io___80 = { 0, 6, 0, 0, 0 };
    static cilist io___81 = { 0, 6, 0, 0, 0 };
    static cilist io___95 = { 0, 6, 0, fmt_35, 0 };
    static cilist io___96 = { 0, 6, 0, fmt_36, 0 };
    static cilist io___97 = { 0, 6, 0, fmt_37, 0 };
    static cilist io___98 = { 0, 6, 0, fmt_38, 0 };
    static cilist io___99 = { 0, 10, 0, fmt_35, 0 };
    static cilist io___100 = { 0, 10, 0, fmt_36, 0 };
    static cilist io___101 = { 0, 10, 0, fmt_37, 0 };
    static cilist io___102 = { 0, 10, 0, fmt_38, 0 };
    static cilist io___103 = { 0, 6, 0, fmt_303, 0 };
    static cilist io___104 = { 0, 10, 0, fmt_303, 0 };
    static cilist io___105 = { 0, 6, 0, fmt_302, 0 };
    static cilist io___106 = { 0, 10, 0, fmt_302, 0 };
    static cilist io___107 = { 0, 6, 0, fmt_303, 0 };
    static cilist io___108 = { 0, 10, 0, fmt_303, 0 };
    static cilist io___109 = { 0, 6, 0, fmt_301, 0 };
    static cilist io___110 = { 0, 10, 0, fmt_301, 0 };
    static cilist io___111 = { 0, 6, 0, 0, 0 };
    static cilist io___112 = { 0, 10, 0, 0, 0 };
    static cilist io___113 = { 0, 6, 0, 0, 0 };
    static cilist io___114 = { 0, 6, 0, 0, 0 };
    static cilist io___115 = { 0, 6, 0, 0, 0 };
    static cilist io___116 = { 0, 6, 0, 0, 0 };
    static cilist io___117 = { 0, 5, 0, "(A)", 0 };
    static cilist io___119 = { 0, 6, 0, 0, 0 };
    static cilist io___120 = { 0, 6, 0, 0, 0 };
    static cilist io___121 = { 0, 6, 0, 0, 0 };
    static cilist io___122 = { 0, 6, 0, 0, 0 };
    static cilist io___123 = { 0, 6, 0, 0, 0 };
    static cilist io___124 = { 0, 6, 0, 0, 0 };
    static cilist io___125 = { 0, 5, 0, 0, 0 };
    static cilist io___126 = { 0, 6, 0, 0, 0 };
    static cilist io___127 = { 0, 10, 0, 0, 0 };
    static cilist io___128 = { 0, 6, 0, 0, 0 };
    static cilist io___129 = { 0, 6, 0, 0, 0 };
    static cilist io___130 = { 0, 6, 0, "(10X,A12,F10.2,F14.2)", 0 };
    static cilist io___131 = { 0, 6, 0, 0, 0 };
    static cilist io___132 = { 0, 10, 0, 0, 0 };
    static cilist io___133 = { 0, 6, 0, 0, 0 };
    static cilist io___134 = { 0, 6, 0, 0, 0 };
    static cilist io___135 = { 0, 6, 0, "(15X,I2,4X,A3,2X,F10.4)", 0 };
    static cilist io___136 = { 0, 6, 0, 0, 0 };
    static cilist io___137 = { 0, 10, 0, 0, 0 };
    static cilist io___138 = { 0, 6, 0, 0, 0 };
    static cilist io___139 = { 0, 6, 0, 0, 0 };
    static cilist io___140 = { 0, 6, 0, 0, 0 };
    static cilist io___141 = { 0, 6, 0, 0, 0 };
    static cilist io___142 = { 0, 6, 0, 0, 0 };
    static cilist io___143 = { 0, 6, 0, 0, 0 };
    static cilist io___144 = { 0, 6, 0, 0, 0 };


/*      IMPLICIT DOUBLE PRECISION (A-H, O-Z) */

/*     OPEN (UNIT=10, FILE='SUPER.OUT', ACCESS='APPEND') */
    o__1.oerr = 0;
    o__1.ounit = 10;
    o__1.ofnmlen = 9;
    o__1.ofnm = "SUPER.OUT";
    o__1.orl = 0;
    o__1.osta = 0;
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);

    s_wsle(&io___2);
    e_wsle();
    s_wsle(&io___3);
    e_wsle();
    s_wsfe(&io___4);
    do_fio(&c__1, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", (ftnlen)42);
    e_wsfe();
    s_wsfe(&io___5);
    do_fio(&c__1, "$$$    $$$  $$  $$     $$$      $$     $$$", (ftnlen)42);
    e_wsfe();
    s_wsfe(&io___6);
    do_fio(&c__1, "$$  $$  $$  $$  $$  $$  $$  $$$$$$  $$  $$", (ftnlen)42);
    e_wsfe();
    s_wsfe(&io___7);
    do_fio(&c__1, "$$  $$$$$$  $$  $$  $$  $$  $$$$$$  $$  $$", (ftnlen)42);
    e_wsfe();
    s_wsfe(&io___8);
    do_fio(&c__1, "$$$  $$$$$  $$  $$     $$$      $$     $$$", (ftnlen)42);
    e_wsfe();
    s_wsfe(&io___9);
    do_fio(&c__1, "$$$$  $$$$  $$  $$  $$$$$$  $$$$$$  $  $$$", (ftnlen)42);
    e_wsfe();
    s_wsfe(&io___10);
    do_fio(&c__1, "$$  $$  $$  $$  $$  $$$$$$  $$$$$$  $$  $$", (ftnlen)42);
    e_wsfe();
    s_wsfe(&io___11);
    do_fio(&c__1, "$$$    $$$$    $$$  $$$$$$      $$  $$$ $$", (ftnlen)42);
    e_wsfe();
    s_wsfe(&io___12);
    do_fio(&c__1, "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", (ftnlen)42);
    e_wsfe();
    s_wsle(&io___13);
    e_wsle();
    s_wsle(&io___14);
    do_lio(&c__9, &c__1, "               WELCOME TO USE THE SUPERFLUID PROGR"
	    "AM !   ", (ftnlen)57);
    e_wsle();
    s_wsle(&io___15);
    e_wsle();
    s_wsle(&io___16);
    do_lio(&c__9, &c__1, "                --- Calculation of P-V-T Relations "
	    , (ftnlen)51);
    e_wsle();
    s_wsle(&io___17);
    do_lio(&c__9, &c__1, "                        and a-f-G Properties ", (
	    ftnlen)45);
    e_wsle();
    s_wsle(&io___18);
    do_lio(&c__9, &c__1, "             in C-H-O-S-N-Ar Supercritical Fluid S"
	    "ystem ", (ftnlen)56);
    e_wsle();
    s_wsle(&io___19);
    do_lio(&c__9, &c__1, "             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	    "^^^^^  ", (ftnlen)57);
    e_wsle();
    s_wsle(&io___20);
    do_lio(&c__9, &c__1, "             Authors:  Benoloshko AB, Shi PF, Saxe"
	    "na SK ", (ftnlen)56);
    e_wsle();
    s_wsle(&io___21);
    do_lio(&c__9, &c__1, "                       1992, Uppsala University, S"
	    "weden  ", (ftnlen)57);
    e_wsle();
    s_wsle(&io___22);
    do_lio(&c__9, &c__1, "             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
	    "^^^^^  ", (ftnlen)57);
    e_wsle();
    s_wsle(&io___23);
    e_wsle();
    s_wsle(&io___24);
    do_lio(&c__9, &c__1, "           NOTES:   ", (ftnlen)20);
    e_wsle();
    s_wsle(&io___25);
    do_lio(&c__9, &c__1, "             Input pressure in BAR and temperature"
	    " in K ", (ftnlen)56);
    e_wsle();
    s_wsle(&io___26);
    do_lio(&c__9, &c__1, "             Number of gas:     from 1 to 13 ", (
	    ftnlen)45);
    e_wsle();
    s_wsle(&io___27);
    do_lio(&c__9, &c__1, "             Mole fraction of gas must be from 0 t"
	    "o 1 ", (ftnlen)54);
    e_wsle();
    s_wsle(&io___28);
    do_lio(&c__9, &c__1, "             Sum of X must be equal to 1.0 ", (
	    ftnlen)43);
    e_wsle();
    s_wsle(&io___29);
    do_lio(&c__9, &c__1, "             Mole fraction of fluid equals to 0 on"
	    " default ", (ftnlen)59);
    e_wsle();
    s_wsle(&io___30);
    do_lio(&c__9, &c__1, "             Type negative number to finish compos"
	    "ition input ", (ftnlen)62);
    e_wsle();
    s_wsle(&io___31);
    do_lio(&c__9, &c__1, "             All calculated data will be saved in "
	    "SUPER.OUT", (ftnlen)59);
    e_wsle();
    s_wsle(&io___32);
    do_lio(&c__9, &c__1, "             -------------------------------------"
	    "----------- ", (ftnlen)62);
    e_wsle();
    s_wsle(&io___33);
    e_wsle();

    s_wsle(&io___34);
    e_wsle();
    s_wsle(&io___35);
    e_wsle();
    s_wsle(&io___36);
    do_lio(&c__9, &c__1, "       THERMODYNAMIC CALCULATION OF ", (ftnlen)36);
    e_wsle();
    s_wsle(&io___37);
    do_lio(&c__9, &c__1, "    THE C-H-O-S-N-Ar SUPERCRITCAL FLUIDS ", (ftnlen)
	    41);
    e_wsle();
    s_wsle(&io___38);
    do_lio(&c__9, &c__1, "    - using SUPERFLUID (Uppsala, 1992) - ", (ftnlen)
	    41);
    e_wsle();
    s_wsle(&io___39);
    do_lio(&c__9, &c__1, " --------------------------------------- ", (ftnlen)
	    41);
    e_wsle();
    s_wsle(&io___40);
    e_wsle();
    s_wsle(&io___41);
    do_lio(&c__9, &c__1, " **************** ", (ftnlen)18);
    e_wsle();
    s_wsle(&io___42);
    do_lio(&c__9, &c__1, " *** ", (ftnlen)5);
    e_wsle();
    iii = 3;

L44:
    s_wsle(&io___44);
    e_wsle();
    s_wsle(&io___45);
    do_lio(&c__9, &c__1, " GIVING T(K) and P(bar) : ", (ftnlen)26);
    e_wsle();
    s_wsle(&io___46);
    do_lio(&c__9, &c__1, " ------------------------ ", (ftnlen)26);
    e_wsle();
    s_wsfe(&io___47);
    do_fio(&c__1, "         T, P =   ", (ftnlen)18);
    e_wsfe();
    s_rsle(&io___48);
    do_lio(&c__4, &c__1, (char *)&t, (ftnlen)sizeof(doublereal));
    do_lio(&c__4, &c__1, (char *)&p, (ftnlen)sizeof(doublereal));
    e_rsle();
    pp = p;
    tt = t;
    rt = t * 8.31451;
    p1bar = 1.;
    if (iii == 3) {
	goto L4;
    }
    if (iii == 2) {
	goto L3;
    }
L4:
    for (i__ = 1; i__ <= 13; ++i__) {
	xx[i__ - 1] = 0.;
	x[i__ - 1] = 0.;
/* L1: */
	xpure[i__ - 1] = 0.;
    }
    xt = 0.;
    s_wsle(&io___60);
    e_wsle();
    s_wsle(&io___61);
    do_lio(&c__9, &c__1, " GIVING COMPOSITION X(I): ", (ftnlen)26);
    e_wsle();
    s_wsle(&io___62);
    do_lio(&c__9, &c__1, " ------------------------ ", (ftnlen)26);
    e_wsle();
    s_wsle(&io___63);
    do_lio(&c__9, &c__1, "       List of The C-H-O-S-N-Ar Fluid Species: ", (
	    ftnlen)47);
    e_wsle();
    s_wsle(&io___64);
    do_lio(&c__9, &c__1, "       -------------------------------------------"
	    "--------", (ftnlen)58);
    e_wsle();
    s_wsfe(&io___65);
    e_wsfe();
    s_wsfe(&io___66);
    for (i__ = 1; i__ <= 13; ++i__) {
	do_fio(&c__1, name__ + (i__ - 1) * 3, (ftnlen)3);
    }
    e_wsfe();
L54:
    xt = 0.;
    for (i__ = 1; i__ <= 13; ++i__) {
	xx[i__ - 1] = 0.;
	x[i__ - 1] = 0.;
	xpure[i__ - 1] = 0.;
    }
    s_wsle(&io___67);
    do_lio(&c__9, &c__1, "       -------------------------------------------"
	    "--------", (ftnlen)58);
    e_wsle();
L6:
    s_wsfe(&io___68);
    do_fio(&c__1, "               IGAS = ", (ftnlen)22);
    e_wsfe();
    s_rsle(&io___69);
    do_lio(&c__3, &c__1, (char *)&igas, (ftnlen)sizeof(integer));
    e_rsle();
    if (igas >= 14 || igas == 0) {
	s_wsle(&io___71);
	do_lio(&c__9, &c__1, "                 !!!    The IGAS number is 0 o"
		"r larger than 13", (ftnlen)62);
	e_wsle();
	goto L6;
    } else {
	goto L66;
    }
L66:
    if (igas < 0) {
	goto L33;
    }
    s_wsfe(&io___72);
    do_fio(&c__1, "                            X(", (ftnlen)30);
    do_fio(&c__1, name__ + (igas - 1) * 3, (ftnlen)3);
    do_fio(&c__1, ") = ", (ftnlen)4);
    e_wsfe();
    s_rsle(&io___73);
    do_lio(&c__5, &c__1, (char *)&x[igas - 1], (ftnlen)sizeof(doublereal));
    e_rsle();
    xx[igas - 1] = x[igas - 1];
    xt += x[igas - 1];
    if (xt > 1.f) {
	s_wsle(&io___74);
	do_lio(&c__9, &c__1, "         SORRY!!!    Your X(total) is > 1.0 ", (
		ftnlen)44);
	e_wsle();
	s_wsle(&io___75);
	do_lio(&c__9, &c__1, "                     You have to give them aga"
		"in!", (ftnlen)49);
	e_wsle();
	goto L54;
    } else {
	goto L6;
    }
L33:
    if (xt < 1.) {
	s_wsle(&io___76);
	do_lio(&c__9, &c__1, "         SORRY!!!    Your X(total) is < 1.0 ", (
		ftnlen)44);
	e_wsle();
	s_wsle(&io___77);
	do_lio(&c__9, &c__1, "                     You have to give them aga"
		"in!", (ftnlen)49);
	e_wsle();
	goto L54;
    } else {
	goto L3;
    }
L3:
    s_wsle(&io___78);
    e_wsle();
    s_wsle(&io___79);
    e_wsle();
    s_wsle(&io___80);
    do_lio(&c__9, &c__1, " LISTING THE CALCULATED RESULT at GIVEN T-P-X: ", (
	    ftnlen)47);
    e_wsle();
    s_wsle(&io___81);
    do_lio(&c__9, &c__1, " --------------------------------------------- ", (
	    ftnlen)47);
    e_wsle();

/*  CALCULATING ...... */

    fder_(xx, &tt, &pp, &vv, &gg, ggi);
    v = (doublereal) vv;
    g = (doublereal) gg;
    for (i__ = 1; i__ <= 13; ++i__) {
	gi[i__ - 1] = (doublereal) ggi[i__ - 1];
    }
    gsum = 0.;
    for (i__ = 1; i__ <= 13; ++i__) {
	gsum += gi[i__ - 1] * x[i__ - 1];
	gama[i__ - 1] = 1.;
	xpure[i__ - 1] = 1.;
	fluid_(xpure, &t, &p1bar, &v1bar, &g1bar);
	fluid_(xpure, &t, &p, &vbar, &gbar);
	xpure[i__ - 1] = 0.;
	if (x[i__ - 1] > 0.) {
	    gama[i__ - 1] = gi[i__ - 1] - g1bar - rt * log(p);
	    fug[i__ - 1] = gbar - g1bar - rt * log(p);
	}
	if (x[i__ - 1] > 0. && x[i__ - 1] < 1.) {
	    gama[i__ - 1] = exp(gama[i__ - 1] / rt);
	    gama[i__ - 1] /= x[i__ - 1];
	    fug[i__ - 1] = exp(fug[i__ - 1] / rt);
	    gama[i__ - 1] /= fug[i__ - 1];
	} else {
	    gama[i__ - 1] = 1.;
	    fug[i__ - 1] = exp(fug[i__ - 1] / rt);
	}
	xpure[i__ - 1] = 0.;
/* L2: */
    }

/*  WRITE OUT THE RESULT on SCREEN and OUTPUT FILE 'SUPER.OUT' */

    s_wsfe(&io___95);
    do_fio(&c__1, (char *)&t, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___96);
    do_fio(&c__1, (char *)&p, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___97);
    do_fio(&c__1, (char *)&v, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___98);
    do_fio(&c__1, (char *)&g, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___99);
    do_fio(&c__1, (char *)&t, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___100);
    do_fio(&c__1, (char *)&p, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___101);
    do_fio(&c__1, (char *)&v, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___102);
    do_fio(&c__1, (char *)&g, (ftnlen)sizeof(doublereal));
    e_wsfe();
    s_wsfe(&io___103);
    e_wsfe();
    s_wsfe(&io___104);
    e_wsfe();
    s_wsfe(&io___105);
    e_wsfe();
    s_wsfe(&io___106);
    e_wsfe();
    s_wsfe(&io___107);
    e_wsfe();
    s_wsfe(&io___108);
    e_wsfe();
/* L301: */
    for (i__ = 1; i__ <= 13; ++i__) {
	if (x[i__ - 1] > 0.) {
	    s_wsfe(&io___109);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, name__ + (i__ - 1) * 3, (ftnlen)3);
	    do_fio(&c__1, (char *)&x[i__ - 1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&gama[i__ - 1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fug[i__ - 1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&gi[i__ - 1], (ftnlen)sizeof(doublereal));
	    d__1 = fug[i__ - 1] * gama[i__ - 1] * x[i__ - 1] * p;
	    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    s_wsfe(&io___110);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, name__ + (i__ - 1) * 3, (ftnlen)3);
	    do_fio(&c__1, (char *)&x[i__ - 1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&gama[i__ - 1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fug[i__ - 1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&gi[i__ - 1], (ftnlen)sizeof(doublereal));
	    d__1 = fug[i__ - 1] * gama[i__ - 1] * x[i__ - 1] * p;
	    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
/* L199: */
    }
    s_wsle(&io___111);
    do_lio(&c__9, &c__1, " ================================================="
	    "=================", (ftnlen)67);
    e_wsle();
    s_wsle(&io___112);
    do_lio(&c__9, &c__1, " ================================================="
	    "=================", (ftnlen)67);
    e_wsle();
    s_wsle(&io___113);
    e_wsle();
    s_wsle(&io___114);
    do_lio(&c__9, &c__1, "       DO YOU WANT TO HAVE OTHER CALCULATIONS ", (
	    ftnlen)46);
    e_wsle();
    s_wsle(&io___115);
    do_lio(&c__9, &c__1, "           at other T-P-X conditions (Y/N)? ", (
	    ftnlen)44);
    e_wsle();
    s_wsle(&io___116);
    do_lio(&c__9, &c__1, "       -------------------------------------- ", (
	    ftnlen)46);
    e_wsle();
L24:
    s_rsfe(&io___117);
    do_fio(&c__1, yn, (ftnlen)1);
    e_rsfe();
    if (*(unsigned char *)yn == 'y' || *(unsigned char *)yn == 'Y') {
	s_wsle(&io___119);
	e_wsle();
	s_wsle(&io___120);
	do_lio(&c__9, &c__1, "         THREE OPTIONS:  ", (ftnlen)25);
	e_wsle();
	s_wsle(&io___121);
	do_lio(&c__9, &c__1, "             1.   SAME  T-P, but DIFFERENT X(I"
		"); ", (ftnlen)49);
	e_wsle();
	s_wsle(&io___122);
	do_lio(&c__9, &c__1, "             2.   SAME X(I), but DIFFERENT  T-"
		"P; ", (ftnlen)49);
	e_wsle();
	s_wsle(&io___123);
	do_lio(&c__9, &c__1, "             3.   DIFFERENT  T-P-X(I). ", (
		ftnlen)39);
	e_wsle();
	s_wsle(&io___124);
	do_lio(&c__9, &c__1, "         WHICH ONE DO YOU WANT TO CHOOSE (1/2/"
		"3)?", (ftnlen)49);
	e_wsle();
L34:
	s_rsle(&io___125);
	do_lio(&c__3, &c__1, (char *)&iii, (ftnlen)sizeof(integer));
	e_rsle();
	if (iii == 1) {
	    s_wsle(&io___126);
	    do_lio(&c__9, &c__1, " **************** ", (ftnlen)18);
	    e_wsle();
	    s_wsle(&io___127);
	    do_lio(&c__9, &c__1, " *** ", (ftnlen)5);
	    e_wsle();
	    s_wsle(&io___128);
	    e_wsle();
	    s_wsle(&io___129);
	    do_lio(&c__9, &c__1, "          LISTING DEFINED T(K) and P(bar): "
		    , (ftnlen)43);
	    e_wsle();
	    s_wsfe(&io___130);
	    do_fio(&c__1, "     T, P = ", (ftnlen)12);
	    do_fio(&c__1, (char *)&t, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&p, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    goto L4;
	} else if (iii == 2) {
	    s_wsle(&io___131);
	    do_lio(&c__9, &c__1, " **************** ", (ftnlen)18);
	    e_wsle();
	    s_wsle(&io___132);
	    do_lio(&c__9, &c__1, " *** ", (ftnlen)5);
	    e_wsle();
	    s_wsle(&io___133);
	    e_wsle();
	    s_wsle(&io___134);
	    do_lio(&c__9, &c__1, "          LISTING DEFINED COMPOSITION X(I)"
		    ": ", (ftnlen)44);
	    e_wsle();
	    for (i__ = 1; i__ <= 13; ++i__) {
		if (x[i__ - 1] > 0.) {
		    s_wsfe(&io___135);
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, name__ + (i__ - 1) * 3, (ftnlen)3);
		    do_fio(&c__1, (char *)&x[i__ - 1], (ftnlen)sizeof(
			    doublereal));
		    e_wsfe();
		}
	    }
	    goto L44;
	} else if (iii == 3) {
	    s_wsle(&io___136);
	    do_lio(&c__9, &c__1, " **************** ", (ftnlen)18);
	    e_wsle();
	    s_wsle(&io___137);
	    do_lio(&c__9, &c__1, " *** ", (ftnlen)5);
	    e_wsle();
	    goto L44;
	} else {
	    s_wsle(&io___138);
	    do_lio(&c__9, &c__1, "           PLEASE CHOOSE THE CORRECT OPTIO"
		    "N !", (ftnlen)45);
	    e_wsle();
	    goto L34;
	}
    } else if (*(unsigned char *)yn == 'n' || *(unsigned char *)yn == 'N') {
	goto L14;
    } else {
	goto L24;
    }
L14:
    s_wsle(&io___139);
    e_wsle();
    s_wsle(&io___140);
    do_lio(&c__9, &c__1, "       The calculated results are stored in SUPER."
	    "OUT ", (ftnlen)54);
    e_wsle();
    s_wsle(&io___141);
    do_lio(&c__9, &c__1, "                                            ******"
	    "*** ", (ftnlen)54);
    e_wsle();
    s_wsle(&io___142);
    e_wsle();
    s_wsle(&io___143);
    do_lio(&c__9, &c__1, "       HAVE A NICE DAY! ", (ftnlen)24);
    e_wsle();
    s_wsle(&io___144);
    e_wsle();
    return 0;
} /* MAIN__ */

/* Main program alias */ int superfl_ () { MAIN__ (); return 0; }
