const char *hornblende_ver(void) { return "$Id: hornblende.c,v 1.3 2006/10/20 00:59:22 ghiorso Exp $"; }

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Routines to compute hornblende solution properties 
**      (file: HORNBLENDE.C)
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  Mark S. Ghiorso  March 26, 1997 Original Version
**      V2.0-1  Mark S. Ghiorso  May 18, 2011
**
*/

#include "silmin.h"  /* Structure definitions foor SILMIN package */

#define SQUARE(x)  ((x)*(x))
#define CUBE(x)    ((x)*(x)*(x))
#define QUARTIC(x) ((x)*(x)*(x)*(x))

#define NR         7
#define NS         0
#define NA         8
#define FR0(i)     (i == 1) ? 1.0 - r[0] : - r[0]
#define FR1(i)     (i == 2) ? 1.0 - r[1] : - r[1]
#define FR2(i)     (i == 3) ? 1.0 - r[2] : - r[2]
#define FR3(i)     (i == 4) ? 1.0 - r[3] : - r[3]
#define FR4(i)     (i == 5) ? 1.0 - r[4] : - r[4]
#define FR5(i)     (i == 6) ? 1.0 - r[5] : - r[5]
#define FR6(i)     (i == 7) ? 1.0 - r[6] : - r[6]
#define DFR0DR0(i) - 1.0
#define DFR1DR1(i) - 1.0
#define DFR2DR2(i) - 1.0
#define DFR3DR3(i) - 1.0
#define DFR4DR4(i) - 1.0
#define DFR5DR5(i) - 1.0
#define DFR6DR6(i) - 1.0

static double logA(double x) { return (x > 0.0) ? log(x) : 0.0; }

/*
 * Binary interaction parameters
 */
 
 
static const double W[NA][NA] = {
  { 	 1.0,	  -32240.3783,  -3332.9821,  -72506.9344,   6292.4765,  -14800.2191,	 516.3959,   -9832.7281 },
  { -32240.3783,       1.0,    -49011.1705, -130959.4243, -34830.2486,  -69026.7582,  -38016.8696,  -93491.8086 },
  {  -3332.9821,  -49011.1705,      1.0,     -87929.4620,  -1117.6543,  -18048.6214,   -9203.7662,  -24017.6362 },
  { -72506.9344, -130959.4243, -87929.4620,	  1.0,    -76930.5773, -129717.5504, -105428.5267,  -58996.9266 },
  {   6292.4765,  -34830.2486,  -1117.6543,  -76930.5773,      1.0,	-28639.6755,	2672.3390,  -15602.2875 },
  { -14800.2191,  -69026.7582, -18048.6214, -129717.5504, -28639.6755,       1.0,      -4531.1979,  -35869.6364 },
  {    516.3959,  -38016.8696,  -9203.7662, -105428.5267,   2672.3390,   -4531.1979,	   1.0,     -24068.2987 },
  {  -9832.7281,  -93491.8086, -24017.6362,  -58996.9266, -15602.2875,  -35869.6364,  -24068.2987,	 1.0    }
};

/*
 * Global (to this file): derivative definitions
 */
#define R  8.3143
#define S  -R*(  XNaA*logA(XNaA) + XKA*logA(XKA) + XVcA*logA(XVcA) \
               + XNaM4*logA(XNaM4) + XCaM4*logA(XCaM4) \
	       + 3.0*XMgM13*logA(XMgM13) + 3.0*XFe2M13*logA(XFe2M13) \
	       + 2.0*XMgM2*logA(XMgM2) + 2.0*XFe2M2*logA(XFe2M2) + 2.0*XAlM2*logA(XAlM2) + 2.0*XFe3M2*logA(XFe3M2) + 2.0*XTiM2*logA(XTiM2) \
	       + 4.0*XAlT1*logA(XAlT1) + 4.0*XSiT1*logA(XSiT1) )
#define H    (W[0][1]*r[0] + W[0][2]*r[1] + W[0][3]*r[2] + W[0][4]*r[3] + W[0][5]*r[4] + W[0][6]*r[5] + W[0][7]*r[6])*(1.0-r[0]-r[1]-r[2]-r[3]-r[4]-r[5]-r[6]) \
           + (W[1][2]*r[1] + W[1][3]*r[2] + W[1][4]*r[3] + W[1][5]*r[4] + W[1][6]*r[5] + W[1][7]*r[6])*r[0] \
	   + (W[2][3]*r[2] + W[2][4]*r[3] + W[2][5]*r[4] + W[2][6]*r[5] + W[2][7]*r[6])*r[1] \
	   + (W[3][4]*r[3] + W[3][5]*r[4] + W[3][6]*r[5] + W[3][7]*r[6])*r[2] \
	   + (W[4][5]*r[4] + W[4][6]*r[5] + W[4][7]*r[6])*r[3] \
	   + (W[5][6]*r[5] + W[5][7]*r[6])*r[4] \
	   + (W[6][7]*r[6])*r[5]
#define V  0.0
#define G  (H) - t*(S) + (p-1.0)*(V)

#define dkdr2  ( 4.0/(4.0+r[5]-r[6]))
#define dkdr5  (-4.0*r[2]/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))
#define dkdr6  ( 4.0*r[2]/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))

#define dMgM13dr2  (-(dkdr2))
#define dMgM13dr5  (-(dkdr5))
#define dMgM13dr6  (-(dkdr6))

#define dFe2M13dr2 (dkdr2)
#define dFe2M13dr5 (dkdr5)
#define dFe2M13dr6 (dkdr6)

#define dMgM2dr2   ((	      -(1.0+r[5]-r[6])*dkdr2)/2.0)
#define dMgM2dr5   (( (1.0-(k))-(1.0+r[5]-r[6])*dkdr5)/2.0)
#define dMgM2dr6   ((-(1.0-(k))-(1.0+r[5]-r[6])*dkdr6)/2.0)

#define dFe2M2dr2  ((	 (1.0+r[5]-r[6])*dkdr2)/2.0)
#define dFe2M2dr5  (( (k)+(1.0+r[5]-r[6])*dkdr5)/2.0)
#define dFe2M2dr6  ((-(k)+(1.0+r[5]-r[6])*dkdr6)/2.0)

#define DGDR0      R*t*( - logA(XNaA) + logA(XKA) ) \
                  - (W[0][1]*r[0] + W[0][2]*r[1] + W[0][3]*r[2] + W[0][4]*r[3] + W[0][5]*r[4] + W[0][6]*r[5] + W[0][7]*r[6]) \
                  +  W[0][1]*(1.0-r[0]-r[1]-r[2]-r[3]-r[4]-r[5]-r[6]) \
                  +  W[1][2]*r[1] + W[1][3]*r[2] + W[1][4]*r[3] + W[1][5]*r[4] + W[1][6]*r[5] + W[1][7]*r[6]		  
#define DGDR1      R*t*( logA(XAlM2) - logA(XFe3M2) ) \
                  - (W[0][1]*r[0] + W[0][2]*r[1] + W[0][3]*r[2] + W[0][4]*r[3] + W[0][5]*r[4] + W[0][6]*r[5] + W[0][7]*r[6]) \
                  +  W[0][2]*(1.0-r[0]-r[1]-r[2]-r[3]-r[4]-r[5]-r[6]) \
                  +  W[1][2]*r[0] +  W[2][3]*r[2] + W[2][4]*r[3] + W[2][5]*r[4] + W[2][6]*r[5] + W[2][7]*r[6]		  
#define DGDR2      R*t*(  3.0*dMgM13dr2*logA(XMgM13) + 3.0*dFe2M13dr2*logA(XFe2M13) \
		        + 2.0*dMgM2dr2*logA(XMgM2) + 2.0*dFe2M2dr2*logA(XFe2M2) \
			+ logA(XAlM2) - logA(XFe3M2) ) \
                  - (W[0][1]*r[0] + W[0][2]*r[1] + W[0][3]*r[2] + W[0][4]*r[3] + W[0][5]*r[4] + W[0][6]*r[5] + W[0][7]*r[6]) \
                  +  W[0][3]*(1.0-r[0]-r[1]-r[2]-r[3]-r[4]-r[5]-r[6]) \
                  +  W[1][3]*r[0] +  W[2][3]*r[1] +  W[3][4]*r[3] + W[3][5]*r[4] + W[3][6]*r[5] + W[3][7]*r[6]		
#define DGDR3      R*t*(- logA(XNaA) + logA(XVcA) \
                        + logA(XAlM2) - logA(XFe3M2) \
			- logA(XAlT1) + logA(XSiT1) ) \
                  - (W[0][1]*r[0] + W[0][2]*r[1] + W[0][3]*r[2] + W[0][4]*r[3] + W[0][5]*r[4] + W[0][6]*r[5] + W[0][7]*r[6]) \
                  +  W[0][4]*(1.0-r[0]-r[1]-r[2]-r[3]-r[4]-r[5]-r[6]) \
                  +  W[1][4]*r[0] +  W[2][4]*r[1] +  W[3][4]*r[2] + (W[4][5]*r[4] + W[4][6]*r[5] + W[4][7]*r[6])		  
#define DGDR4      R*t*(-  logA(XFe3M2) + logA(XTiM2) ) \
                  - (W[0][1]*r[0] + W[0][2]*r[1] + W[0][3]*r[2] + W[0][4]*r[3] + W[0][5]*r[4] + W[0][6]*r[5] + W[0][7]*r[6]) \
                  +  W[0][5]*(1.0-r[0]-r[1]-r[2]-r[3]-r[4]-r[5]-r[6]) \
                  +  W[1][5]*r[0] +  W[2][5]*r[1] +  W[3][5]*r[2] +  W[4][5]*r[3] +  W[5][6]*r[5] + W[5][7]*r[6]
#define DGDR5      R*t*(  3.0*dMgM13dr5*logA(XMgM13) + 3.0*dFe2M13dr5*logA(XFe2M13) \
		        + 2.0*dMgM2dr5*logA(XMgM2) + 2.0*dFe2M2dr5*logA(XFe2M2) - logA(XFe3M2) \
			- logA(XAlT1) + logA(XSiT1) ) \
                  - (W[0][1]*r[0] + W[0][2]*r[1] + W[0][3]*r[2] + W[0][4]*r[3] + W[0][5]*r[4] + W[0][6]*r[5] + W[0][7]*r[6]) \
                  +  W[0][6]*(1.0-r[0]-r[1]-r[2]-r[3]-r[4]-r[5]-r[6]) \
		  +  W[1][6]*r[0] +  W[2][6]*r[1] +  W[3][6]*r[2] +  W[4][6]*r[3] +  W[5][6]*r[4] +  W[6][7]*r[6]		  
#define DGDR6      R*t*(- logA(XNaA) + logA(XVcA) \
                  + logA(XNaM4) - logA(XCaM4) \
		  + 3.0*dMgM13dr6*logA(XMgM13) + 3.0*dFe2M13dr6*logA(XFe2M13) \
		  + 2.0*dMgM2dr6*logA(XMgM2) + 2.0*dFe2M2dr6*logA(XFe2M2) + 2.0*logA(XAlM2) - logA(XFe3M2) \
		  - logA(XAlT1) + logA(XSiT1) ) \
                  - (W[0][1]*r[0] + W[0][2]*r[1] + W[0][3]*r[2] + W[0][4]*r[3] + W[0][5]*r[4] + W[0][6]*r[5] + W[0][7]*r[6]) \
                  +  W[0][7]*(1.0-r[0]-r[1]-r[2]-r[3]-r[4]-r[5]-r[6]) \
                  +  W[1][7]*r[0] +  W[2][7]*r[1] +  W[3][7]*r[2] +  W[4][7]*r[3] +  W[5][7]*r[4] +  W[6][7]*r[5]     
#define DGDT       -(S)
#define DGDP       (V)

#define D2GDR0R0   R*t*( 1.0/XNaA + 1.0/XKA ) - 2.0*W[0][1]
#define D2GDR0R1   - W[0][2] - W[0][1] + W[1][2]
#define D2GDR0R2   - W[0][3] - W[0][1] + W[1][3]
#define D2GDR0R3   R*t*( 1.0/XNaA ) - W[0][4] - W[0][1] + W[1][4]
#define D2GDR0R4   - W[0][5] - W[0][1] + W[1][5]
#define D2GDR0R5   - W[0][6] - W[0][1] + W[1][6]
#define D2GDR0R6   R*t*( 1.0/XNaA ) - W[0][7] - W[0][1] + W[1][7]
#define D2GDR0DT   R*( - logA(XNaA) + logA(XKA) )
#define D2GDR0DP   0.0

#define D2GDR1R1   R*t*( 1.0/XAlM2/2.0 + 1.0/XFe3M2/2.0 ) - 2.0*W[0][2] 
#define D2GDR1R2   R*t*( 1.0/XAlM2/2.0 + 1.0/XFe3M2/2.0 ) - W[0][3] - W[0][2] + W[2][3]
#define D2GDR1R3   R*t*( 1.0/XAlM2/2.0 + 1.0/XFe3M2/2.0 ) - W[0][4] - W[0][2] + W[2][4]
#define D2GDR1R4   R*t*( 1.0/XFe3M2/2.0 ) - W[0][5] - W[0][2] + W[2][5]
#define D2GDR1R5   R*t*( 1.0/XFe3M2/2.0 ) - W[0][6] - W[0][2] + W[2][6]
#define D2GDR1R6   R*t*( 1.0/XAlM2 + 1.0/XFe3M2/2.0 ) - W[0][7] -  W[0][2] + W[2][7]
#define D2GDR1DT   R*( logA(XAlM2) - logA(XFe3M2) )
#define D2GDR1DP   0.0

#define d2kdr2dr2  ( 0.0)
#define d2kdr2dr5  (-4.0/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))
#define d2kdr2dr6  ( 4.0/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))
#define d2kdr5dr5  ( 8.0*r[2]/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))
#define d2kdr5dr6  (-8.0*r[2]/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))
#define d2kdr6dr6  ( 8.0*r[2]/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))

#define d2MgM13dr2dr2  (-(d2kdr2dr2))
#define d2MgM13dr2dr5  (-(d2kdr2dr5))
#define d2MgM13dr2dr6  (-(d2kdr2dr6))
#define d2MgM13dr5dr5  (-(d2kdr5dr5))
#define d2MgM13dr5dr6  (-(d2kdr5dr6))
#define d2MgM13dr6dr6  (-(d2kdr6dr6))

#define d2Fe2M13dr2dr2 (d2kdr2dr2)
#define d2Fe2M13dr2dr5 (d2kdr2dr5)
#define d2Fe2M13dr2dr6 (d2kdr2dr6)
#define d2Fe2M13dr5dr5 (d2kdr5dr5)
#define d2Fe2M13dr5dr6 (d2kdr5dr6)
#define d2Fe2M13dr6dr6 (d2kdr6dr6)

#define d2MgM2dr2dr2   ((	        - (1.0+r[5]-r[6])*d2kdr2dr2)/2.0)
#define d2MgM2dr2dr5   ((	- dkdr2 - (1.0+r[5]-r[6])*d2kdr2dr5)/2.0)
#define d2MgM2dr2dr6   ((	  dkdr2 - (1.0+r[5]-r[6])*d2kdr2dr6)/2.0)
#define d2MgM2dr5dr5   ((- dkdr5 - dkdr5 - (1.0+r[5]-r[6])*d2kdr5dr5)/2.0)
#define d2MgM2dr5dr6   ((- dkdr6 + dkdr5 - (1.0+r[5]-r[6])*d2kdr5dr6)/2.0)
#define d2MgM2dr6dr6   ((  dkdr6 + dkdr6 - (1.0+r[5]-r[6])*d2kdr6dr6)/2.0)

#define d2Fe2M2dr2dr2  ((	          (1.0+r[5]-r[6])*d2kdr2dr2)/2.0)
#define d2Fe2M2dr2dr5  ((	  dkdr2 + (1.0+r[5]-r[6])*d2kdr2dr5)/2.0)
#define d2Fe2M2dr2dr6  ((	- dkdr2 + (1.0+r[5]-r[6])*d2kdr2dr6)/2.0)
#define d2Fe2M2dr5dr5  ((  dkdr5 + dkdr5 + (1.0+r[5]-r[6])*d2kdr5dr5)/2.0)
#define d2Fe2M2dr5dr6  ((  dkdr6 - dkdr5 + (1.0+r[5]-r[6])*d2kdr5dr6)/2.0)
#define d2Fe2M2dr6dr6  ((- dkdr6 - dkdr6 + (1.0+r[5]-r[6])*d2kdr6dr6)/2.0)

#define D2GDR2R2   R*t*(  3.0*d2MgM13dr2dr2*logA(XMgM13) + 3.0*dMgM13dr2*dMgM13dr2/XMgM13 \
                        + 3.0*d2Fe2M13dr2dr2*logA(XFe2M13) + 3.0*dFe2M13dr2*dFe2M13dr2/XFe2M13 \
		        + 2.0*d2MgM2dr2dr2*logA(XMgM2) + 2.0*dMgM2dr2*dMgM2dr2/XMgM2 \
			+ 2.0*d2Fe2M2dr2dr2*logA(XFe2M2) + 2.0*dFe2M2dr2*dFe2M2dr2/XFe2M2 \
			+ 1.0/XAlM2/2.0 + 1.0/XFe3M2/2.0 ) - 2.0*W[0][3]			
#define D2GDR2R3   R*t*(  1.0/XAlM2/2.0 + 1.0/XFe3M2/2.0 ) - W[0][4] -  W[0][3] + W[3][4]
#define D2GDR2R4   R*t*(  1.0/XFe3M2/2.0 ) - W[0][5] - W[0][3] + W[3][5]
#define D2GDR2R5   R*t*(  3.0*d2MgM13dr2dr5*logA(XMgM13) + 3.0*dMgM13dr2*dMgM13dr5/XMgM13 \
                        + 3.0*d2Fe2M13dr2dr5*logA(XFe2M13) + 3.0*dFe2M13dr2*dFe2M13dr5/XFe2M13 \
		        + 2.0*d2MgM2dr2dr5*logA(XMgM2) + 2.0*dMgM2dr2*dMgM2dr5/XMgM2 \
			+ 2.0*d2Fe2M2dr2dr5*logA(XFe2M2) + 2.0*dFe2M2dr2*dFe2M2dr5/XFe2M2 \
			+ 1.0/XFe3M2/2.0 ) - W[0][6] - W[0][3] + W[3][6]				
#define D2GDR2R6   R*t*(  3.0*d2MgM13dr2dr6*logA(XMgM13) + 3.0*dMgM13dr2*dMgM13dr6/XMgM13 \
                        + 3.0*d2Fe2M13dr2dr6*logA(XFe2M13) + 3.0*dFe2M13dr2*dFe2M13dr6/XFe2M13 \
		        + 2.0*d2MgM2dr2dr6*logA(XMgM2) + 2.0*dMgM2dr2*dMgM2dr6/XMgM2 \
			+ 2.0*d2Fe2M2dr2dr6*logA(XFe2M2) + 2.0*dFe2M2dr2*dFe2M2dr6/XFe2M2 \
			+ 1.0/XAlM2 + 1.0/XFe3M2/2.0 ) - W[0][7] - W[0][3] + W[3][7]
#define D2GDR2DT   R*(  3.0*dMgM13dr2*logA(XMgM13) + 3.0*dFe2M13dr2*logA(XFe2M13) \
		      + 2.0*dMgM2dr2*logA(XMgM2) + 2.0*dFe2M2dr2*logA(XFe2M2) \
		      + logA(XAlM2) - logA(XFe3M2) )
#define D2GDR2DP   0.0


#define D2GDR3R3   R*t*( 1.0/XNaA + 1.0/XVcA + 1.0/XAlM2/2.0 + 1.0/XFe3M2/2.0 + 0.25/XAlT1 + 0.25/XSiT1 ) - 2.0*W[0][4]
#define D2GDR3R4   R*t*( 1.0/XFe3M2/2.0 ) - W[0][5] - W[0][4] + W[4][5]
#define D2GDR3R5   R*t*( 1.0/XFe3M2/2.0 + 0.25/XAlT1 + 0.25/XSiT1 ) - W[0][6] - W[0][4] + W[4][6]
#define D2GDR3R6   R*t*( 1.0/XNaA + 1.0/XVcA + 1.0/XAlM2 + 1.0/XFe3M2/2.0 + 0.25/XAlT1 + 0.25/XSiT1 ) - W[0][7] - W[0][4] + W[4][7]
#define D2GDR3DT   R*(- logA(XNaA) + logA(XVcA) + logA(XAlM2) - logA(XFe3M2) - logA(XAlT1) + logA(XSiT1) )
#define D2GDR3DP   0.0

		
#define D2GDR4R4   R*t*( 1.0/XFe3M2/2.0 + 1.0/XTiM2/2.0 ) - 2.0*W[0][5]
#define D2GDR4R5   R*t*( 1.0/XFe3M2/2.0 ) - W[0][6] - W[0][5] + W[5][6]
#define D2GDR4R6   R*t*( 1.0/XFe3M2/2.0 ) - W[0][7] - W[0][5] + W[5][7]
#define D2GDR4DT   R*(-  logA(XFe3M2) + logA(XTiM2) )
#define D2GDR4DP   0.0

#define D2GDR5R5   R*t*(  3.0*d2MgM13dr5dr5*logA(XMgM13) + 3.0*dMgM13dr5*dMgM13dr5/XMgM13 \
                        + 3.0*d2Fe2M13dr5dr5*logA(XFe2M13) + 3.0*dFe2M13dr5*dFe2M13dr5/XFe2M13 \
		        + 2.0*d2MgM2dr5dr5*logA(XMgM2) + 2.0*dMgM2dr5*dMgM2dr5/XMgM2 \
			+ 2.0*d2Fe2M2dr5dr5*logA(XFe2M2) + 2.0*dFe2M2dr5*dFe2M2dr5/XFe2M2 \
			+ 1.0/XFe3M2/2.0 + 0.25/XAlT1 + 0.25/XSiT1 ) - 2.0*W[0][6]
#define D2GDR5R6   R*t*(  3.0*d2MgM13dr5dr6*logA(XMgM13) + 3.0*dMgM13dr5*dMgM13dr6/XMgM13 \
                        + 3.0*d2Fe2M13dr5dr6*logA(XFe2M13) + 3.0*dFe2M13dr5*dFe2M13dr6/XFe2M13 \
		        + 2.0*d2MgM2dr5dr6*logA(XMgM2) + 2.0*dMgM2dr5*dMgM2dr6/XMgM2 \
			+ 2.0*d2Fe2M2dr5dr6*logA(XFe2M2) + 2.0*dFe2M2dr5*dFe2M2dr6/XFe2M2 \
			+ 1.0/XFe3M2/2.0 + 0.25/XAlT1 + 0.25/XSiT1 ) - W[0][7] - W[0][6] + W[6][7]
#define D2GDR5DT   R*(  3.0*dMgM13dr5*logA(XMgM13) + 3.0*dFe2M13dr5*logA(XFe2M13) \
		      + 2.0*dMgM2dr5*logA(XMgM2) + 2.0*dFe2M2dr5*logA(XFe2M2) - logA(XFe3M2) \
		      - logA(XAlT1) + logA(XSiT1) )
#define D2GDR5DP   0.0

#define D2GDR6R6   R*t*(  1.0/XNaA + 1.0/XVcA + 1.0/XNaM4 + 1.0/XCaM4 \
		        + 3.0*d2MgM13dr6dr6*logA(XMgM13) + 3.0*dMgM13dr6*dMgM13dr6/XMgM13 \
		        + 3.0*d2Fe2M13dr6dr6*logA(XFe2M13) + 3.0*dFe2M13dr6*dFe2M13dr6/XFe2M13 \
		        + 2.0*d2MgM2dr6dr6*logA(XMgM2) + 2.0*dMgM2dr6*dMgM2dr6/XMgM2 \
		        + 2.0*d2Fe2M2dr6dr6*logA(XFe2M2) + 2.0*dFe2M2dr6*dFe2M2dr6/XFe2M2 \
		        + 2.0/XAlM2 + 1.0/XFe3M2/2.0 + 0.25/XAlT1 + 0.25/XSiT1 ) - 2.0*W[0][7]
#define D2GDR6DT   R*(- logA(XNaA) + logA(XVcA) \
                      + logA(XNaM4) - logA(XCaM4) \
		      + 3.0*dMgM13dr6*logA(XMgM13) + 3.0*dFe2M13dr6*logA(XFe2M13) \
		      + 2.0*dMgM2dr6*logA(XMgM2) + 2.0*dFe2M2dr6*logA(XFe2M2) + 2.0*logA(XAlM2) - logA(XFe3M2) \
		      - logA(XAlT1) + logA(XSiT1) )
#define D2GDR6DP   0.0


#define D2GDT2     0.0
#define D2GDTDP    0.0
#define D2GDP2     0.0

#define D3GDR0R0R0 R*t*( 1.0/XNaA/XNaA - 1.0/XKA/XKA )
#define D3GDR0R0R1 0.0
#define D3GDR0R0R2 0.0
#define D3GDR0R0R3 R*t*( 1.0/XNaA/XNaA )
#define D3GDR0R0R4 0.0
#define D3GDR0R0R5 0.0
#define D3GDR0R0R6 R*t*( 1.0/XNaA/XNaA )
#define D3GDR0R0DT R*( 1.0/XNaA + 1.0/XKA )
#define D3GDR0R0DP 0.0

#define D3GDR0R1R1 0.0
#define D3GDR0R1R2 0.0
#define D3GDR0R1R3 0.0
#define D3GDR0R1R4 0.0
#define D3GDR0R1R5 0.0
#define D3GDR0R1R6 0.0
#define D3GDR0R1DT 0.0
#define D3GDR0R1DP 0.0

#define D3GDR0R2R2 0.0
#define D3GDR0R2R3 0.0
#define D3GDR0R2R4 0.0
#define D3GDR0R2R5 0.0
#define D3GDR0R2R6 0.0
#define D3GDR0R2DT 0.0
#define D3GDR0R2DP 0.0

#define D3GDR0R3R3 R*t*( 1.0/XNaA/XNaA )
#define D3GDR0R3R4 0.0
#define D3GDR0R3R5 0.0
#define D3GDR0R3R6 R*t*( 1.0/XNaA/XNaA )
#define D3GDR0R3DT R*( 1.0/XNaA )
#define D3GDR0R3DP 0.0

#define D3GDR0R4R4 0.0
#define D3GDR0R4R5 0.0
#define D3GDR0R4R6 0.0
#define D3GDR0R4DT 0.0
#define D3GDR0R4DP 0.0

#define D3GDR0R5R5 0.0
#define D3GDR0R5R6 0.0
#define D3GDR0R5DT 0.0
#define D3GDR0R5DP 0.0

#define D3GDR0R6R6 R*t*( 1.0/XNaA/XNaA )
#define D3GDR0R6DT R*( 1.0/XNaA )
#define D3GDR0R6DP 0.0

#define D3GDR1R1R1 R*t*(- 1.0/XAlM2/XAlM2/4.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R1R2 R*t*(- 1.0/XAlM2/XAlM2/4.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R1R3 R*t*(- 1.0/XAlM2/XAlM2/4.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R1R4 R*t*(  1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R1R5 R*t*(  1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R1R6 R*t*(- 1.0/XAlM2/XAlM2/2.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R1DT R*( 1.0/XAlM2/2.0 + 1.0/XFe3M2/2.0 )
#define D3GDR1R1DP 0.0

#define D3GDR1R2R2 R*t*(- 1.0/XAlM2/XAlM2/4.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R2R3 R*t*(- 1.0/XAlM2/XAlM2/4.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R2R4 R*t*(  1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R2R5 R*t*(  1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R2R6 R*t*(- 1.0/XAlM2/XAlM2/2.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R2DT R*( 1.0/XAlM2/2.0 + 1.0/XFe3M2/2.0 )
#define D3GDR1R2DP 0.0

#define D3GDR1R3R3 R*t*(- 1.0/XAlM2/XAlM2/4.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R3R4 R*t*(  1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R3R5 R*t*(  1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R3R6 R*t*(- 1.0/XAlM2/XAlM2/2.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R3DT R*( 1.0/XAlM2/2.0 + 1.0/XFe3M2/2.0 )
#define D3GDR1R3DP 0.0

#define D3GDR1R4R4 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R4R5 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R4R6 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R4DT R*( 1.0/XFe3M2/2.0 )
#define D3GDR1R4DP 0.0

#define D3GDR1R5R5 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R5R6 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R5DT R*( 1.0/XFe3M2/2.0 )
#define D3GDR1R5DP 0.0

#define D3GDR1R6R6 R*t*(- 1.0/XAlM2/XAlM2 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR1R6DT R*( 1.0/XAlM2 + 1.0/XFe3M2/2.0 )
#define D3GDR1R6DP 0.0

#define d3kdr2dr2dr2  ( 0.0)
#define d3kdr2dr2dr5  ( 0.0)
#define d3kdr2dr2dr6  ( 0.0)
#define d3kdr2dr5dr5  ( 8.0/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))
#define d3kdr2dr5dr6  (-8.0/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))
#define d3kdr2dr6dr6  ( 8.0/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))
#define d3kdr5dr5dr5  (-24.0*r[2]/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))
#define d3kdr5dr5dr6  ( 24.0*r[2]/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))
#define d3kdr5dr6dr6  (-24.0*r[2]/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))
#define d3kdr6dr6dr6  ( 24.0*r[2]/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6])/(4.0+r[5]-r[6]))

#define d3MgM13dr2dr2dr2  (-(d3kdr2dr2dr2))
#define d3MgM13dr2dr2dr5  (-(d3kdr2dr2dr5))
#define d3MgM13dr2dr2dr6  (-(d3kdr2dr2dr6))
#define d3MgM13dr2dr5dr5  (-(d3kdr2dr5dr5))
#define d3MgM13dr2dr5dr6  (-(d3kdr2dr5dr6))
#define d3MgM13dr2dr6dr6  (-(d3kdr2dr6dr6))
#define d3MgM13dr5dr5dr5  (-(d3kdr5dr5dr5))
#define d3MgM13dr5dr5dr6  (-(d3kdr5dr5dr6))
#define d3MgM13dr5dr6dr6  (-(d3kdr5dr6dr6))
#define d3MgM13dr6dr6dr6  (-(d3kdr6dr6dr6))

#define d3Fe2M13dr2dr2dr2 (d3kdr2dr2dr2)
#define d3Fe2M13dr2dr2dr5 (d3kdr2dr2dr5)
#define d3Fe2M13dr2dr2dr6 (d3kdr2dr2dr6)
#define d3Fe2M13dr2dr5dr5 (d3kdr2dr5dr5)
#define d3Fe2M13dr2dr5dr6 (d3kdr2dr5dr6)
#define d3Fe2M13dr2dr6dr6 (d3kdr2dr6dr6)
#define d3Fe2M13dr5dr5dr5 (d3kdr5dr5dr5)
#define d3Fe2M13dr5dr5dr6 (d3kdr5dr5dr6)
#define d3Fe2M13dr5dr6dr6 (d3kdr5dr6dr6)
#define d3Fe2M13dr6dr6dr6 (d3kdr6dr6dr6)

#define d3MgM2dr2dr2dr2   ((	 		   - (1.0+r[5]-r[6])*d3kdr2dr2dr2)/2.0)
#define d3MgM2dr2dr2dr5   ((	 		   - (1.0+r[5]-r[6])*d3kdr2dr2dr5 - d2kdr2dr2)/2.0)
#define d3MgM2dr2dr2dr6   ((	 		   - (1.0+r[5]-r[6])*d3kdr2dr2dr6 + d2kdr2dr2)/2.0)
#define d3MgM2dr2dr5dr5   ((	       - d2kdr2dr5 - (1.0+r[5]-r[6])*d3kdr2dr5dr5 - d2kdr2dr5)/2.0)
#define d3MgM2dr2dr5dr6   ((	       - d2kdr2dr6 - (1.0+r[5]-r[6])*d3kdr2dr5dr6 + d2kdr2dr5)/2.0)
#define d3MgM2dr2dr6dr6   ((	 	 d2kdr2dr6 - (1.0+r[5]-r[6])*d3kdr2dr6dr6 + d2kdr2dr6)/2.0)
#define d3MgM2dr5dr5dr5   ((- d2kdr5dr5 - d2kdr5dr5 - (1.0+r[5]-r[6])*d3kdr5dr5dr5 - d2kdr5dr5)/2.0)
#define d3MgM2dr5dr5dr6   ((- d2kdr5dr6 - d2kdr5dr6 - (1.0+r[5]-r[6])*d3kdr5dr5dr6 + d2kdr5dr5)/2.0)
#define d3MgM2dr5dr6dr6   ((- d2kdr6dr6 + d2kdr5dr6 - (1.0+r[5]-r[6])*d3kdr5dr6dr6 + d2kdr5dr6)/2.0)
#define d3MgM2dr6dr6dr6   ((  d2kdr6dr6 + d2kdr6dr6 - (1.0+r[5]-r[6])*d3kdr6dr6dr6 + d2kdr6dr6)/2.0)

#define d3Fe2M2dr2dr2dr2  ((	           	     (1.0+r[5]-r[6])*d3kdr2dr2dr2)/2.0)
#define d3Fe2M2dr2dr2dr5  ((	           	     (1.0+r[5]-r[6])*d3kdr2dr2dr5 + d2kdr2dr2)/2.0)
#define d3Fe2M2dr2dr2dr6  ((	           	     (1.0+r[5]-r[6])*d3kdr2dr2dr6 - d2kdr2dr2)/2.0)
#define d3Fe2M2dr2dr5dr5  ((	   	 d2kdr2dr5 + (1.0+r[5]-r[6])*d3kdr2dr5dr5 + d2kdr2dr5)/2.0)
#define d3Fe2M2dr2dr5dr6  ((	   	 d2kdr2dr6 + (1.0+r[5]-r[6])*d3kdr2dr5dr6 - d2kdr2dr5)/2.0)
#define d3Fe2M2dr2dr6dr6  ((	       - d2kdr2dr6 + (1.0+r[5]-r[6])*d3kdr2dr6dr6 - d2kdr2dr6)/2.0)
#define d3Fe2M2dr5dr5dr5  ((  d2kdr5dr5 + d2kdr5dr5 + (1.0+r[5]-r[6])*d3kdr5dr5dr5 + d2kdr5dr5)/2.0)
#define d3Fe2M2dr5dr5dr6  ((  d2kdr5dr6 + d2kdr5dr6 + (1.0+r[5]-r[6])*d3kdr5dr5dr6 - d2kdr5dr5)/2.0)
#define d3Fe2M2dr5dr6dr6  ((  d2kdr6dr6 - d2kdr5dr6 + (1.0+r[5]-r[6])*d3kdr5dr6dr6 - d2kdr5dr6)/2.0)
#define d3Fe2M2dr6dr6dr6  ((- d2kdr6dr6 - d2kdr6dr6 + (1.0+r[5]-r[6])*d3kdr6dr6dr6 - d2kdr6dr6)/2.0)

#define D3GDR2R2R2 R*t*(  3.0*d3MgM13dr2dr2dr2*logA(XMgM13)     + 3.0*d2MgM13dr2dr2*dMgM13dr2/XMgM13 \
                        + 6.0*dMgM13dr2*d2MgM13dr2dr2/XMgM13    - 3.0*dMgM13dr2*dMgM13dr2*dMgM13dr2/XMgM13/XMgM13 \
                        + 3.0*d3Fe2M13dr2dr2dr2*logA(XFe2M13)   + 3.0*d2Fe2M13dr2dr2*dFe2M13dr2/XFe2M13 \
			+ 6.0*dFe2M13dr2*d2Fe2M13dr2dr2/XFe2M13 - 3.0*dFe2M13dr2*dFe2M13dr2*dFe2M13dr2/XFe2M13/XFe2M13 \
		        + 2.0*d3MgM2dr2dr2dr2*logA(XMgM2)       + 2.0*d2MgM2dr2dr2*dMgM2dr2/XMgM2 \
			+ 4.0*dMgM2dr2*d2MgM2dr2dr2/XMgM2       - 2.0*dMgM2dr2*dMgM2dr2*dMgM2dr2/XMgM2/XMgM2 \
			+ 2.0*d3Fe2M2dr2dr2dr2*logA(XFe2M2)     + 2.0*d2Fe2M2dr2dr2*dFe2M2dr2/XFe2M2 \
			+ 4.0*dFe2M2dr2*d2Fe2M2dr2dr2/XFe2M2    - 2.0*dFe2M2dr2*dFe2M2dr2*dFe2M2dr2/XFe2M2/XFe2M2 \
			- 1.0/XAlM2/XAlM2/4.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR2R2R3 R*t*(- 1.0/XAlM2/XAlM2/4.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR2R2R4 R*t*(  1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR2R2R5 R*t*(  3.0*d3MgM13dr2dr2dr5*logA(XMgM13)     + 3.0*d2MgM13dr2dr2*dMgM13dr5/XMgM13 \
                        + 6.0*dMgM13dr2*d2MgM13dr2dr5/XMgM13    - 3.0*dMgM13dr2*dMgM13dr2*dMgM13dr5/XMgM13/XMgM13 \
                        + 3.0*d3Fe2M13dr2dr2dr5*logA(XFe2M13)   + 3.0*d2Fe2M13dr2dr2*dFe2M13dr5/XFe2M13 \
			+ 6.0*dFe2M13dr2*d2Fe2M13dr2dr5/XFe2M13 - 3.0*dFe2M13dr2*dFe2M13dr2*dFe2M13dr5/XFe2M13/XFe2M13 \
		        + 2.0*d3MgM2dr2dr2dr5*logA(XMgM2)       + 2.0*d2MgM2dr2dr2*dMgM2dr5/XMgM2 \
			+ 4.0*dMgM2dr2*d2MgM2dr2dr5/XMgM2       - 2.0*dMgM2dr2*dMgM2dr2*dMgM2dr5/XMgM2/XMgM2 \
			+ 2.0*d3Fe2M2dr2dr2dr5*logA(XFe2M2)     + 2.0*d2Fe2M2dr2dr2*dFe2M2dr5/XFe2M2 \
			+ 4.0*dFe2M2dr2*d2Fe2M2dr2dr5/XFe2M2    - 2.0*dFe2M2dr2*dFe2M2dr2*dFe2M2dr5/XFe2M2/XFe2M2 \
			+ 1.0/XFe3M2/XFe3M2/4.0 )			
#define D3GDR2R2R6 R*t*(  3.0*d3MgM13dr2dr2dr6*logA(XMgM13)     + 3.0*d2MgM13dr2dr2*dMgM13dr6/XMgM13 \
                        + 6.0*dMgM13dr2*d2MgM13dr2dr6/XMgM13    - 3.0*dMgM13dr2*dMgM13dr2*dMgM13dr6/XMgM13/XMgM13 \
                        + 3.0*d3Fe2M13dr2dr2dr6*logA(XFe2M13)   + 3.0*d2Fe2M13dr2dr2*dFe2M13dr6/XFe2M13 \
			+ 6.0*dFe2M13dr2*d2Fe2M13dr2dr6/XFe2M13 - 3.0*dFe2M13dr2*dFe2M13dr2*dFe2M13dr6/XFe2M13/XFe2M13 \
		        + 2.0*d3MgM2dr2dr2dr6*logA(XMgM2)       + 2.0*d2MgM2dr2dr2*dMgM2dr6/XMgM2 \
			+ 4.0*dMgM2dr2*d2MgM2dr2dr6/XMgM2       - 2.0*dMgM2dr2*dMgM2dr2*dMgM2dr6/XMgM2/XMgM2 \
			+ 2.0*d3Fe2M2dr2dr2dr6*logA(XFe2M2)     + 2.0*d2Fe2M2dr2dr2*dFe2M2dr6/XFe2M2 \
			+ 4.0*dFe2M2dr2*d2Fe2M2dr2dr6/XFe2M2    - 2.0*dFe2M2dr2*dFe2M2dr2*dFe2M2dr6/XFe2M2/XFe2M2 \
			- 1.0/XAlM2/XAlM2/2.0 + 1.0/XFe3M2/XFe3M2/4.0 )			
#define D3GDR2R2DT R*(  3.0*d2MgM13dr2dr2*logA(XMgM13) + 3.0*dMgM13dr2*dMgM13dr2/XMgM13 \
                      + 3.0*d2Fe2M13dr2dr2*logA(XFe2M13) + 3.0*dFe2M13dr2*dFe2M13dr2/XFe2M13 \
		      + 2.0*d2MgM2dr2dr2*logA(XMgM2) + 2.0*dMgM2dr2*dMgM2dr2/XMgM2 \
	              + 2.0*d2Fe2M2dr2dr2*logA(XFe2M2) + 2.0*dFe2M2dr2*dFe2M2dr2/XFe2M2 \
		      + 1.0/XAlM2/2.0 + 1.0/XFe3M2/2.0 )
#define D3GDR2R2DP 0.0

#define D3GDR2R3R3 R*t*(- 1.0/XAlM2/XAlM2/4.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR2R3R4 R*t*(  1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR2R3R5 R*t*(  1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR2R3R6 R*t*(- 1.0/XAlM2/XAlM2/2.0 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR2R3DT R*(  1.0/XAlM2/2.0 + 1.0/XFe3M2/2.0 )
#define D3GDR2R3DP 0.0

#define D3GDR2R4R4 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR2R4R5 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR2R4R6 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR2R4DT R*( 1.0/XFe3M2/2.0 )
#define D3GDR2R4DP 0.0

#define D3GDR2R5R5 R*t*(  3.0*d3MgM13dr2dr5dr5*logA(XMgM13)     + 3.0*d2MgM13dr2dr5*dMgM13dr5/XMgM13 \
                        + 3.0*d2MgM13dr2dr5*dMgM13dr5/XMgM13    + 3.0*dMgM13dr2*d2MgM13dr5dr5/XMgM13    - 3.0*dMgM13dr2*dMgM13dr5*dMgM13dr5/XMgM13/XMgM13 \
                        + 3.0*d3Fe2M13dr2dr5dr5*logA(XFe2M13)   + 3.0*d2Fe2M13dr2dr5*dFe2M13dr5/XFe2M13 \
			+ 3.0*d2Fe2M13dr2dr5*dFe2M13dr5/XFe2M13 + 3.0*dFe2M13dr2*d2Fe2M13dr5dr5/XFe2M13 - 3.0*dFe2M13dr2*dFe2M13dr5*dFe2M13dr5/XFe2M13/XFe2M13 \
		        + 2.0*d3MgM2dr2dr5dr5*logA(XMgM2)       + 2.0*d2MgM2dr2dr5*dMgM2dr5/XMgM2 \
			+ 2.0*d2MgM2dr2dr5*dMgM2dr5/XMgM2       + 2.0*dMgM2dr2*d2MgM2dr5dr5/XMgM2       - 2.0*dMgM2dr2*dMgM2dr5*dMgM2dr5/XMgM2/XMgM2 \
			+ 2.0*d3Fe2M2dr2dr5dr5*logA(XFe2M2)     + 2.0*d2Fe2M2dr2dr5*dFe2M2dr5/XFe2M2 \
			+ 2.0*d2Fe2M2dr2dr5*dFe2M2dr5/XFe2M2    + 2.0*dFe2M2dr2*d2Fe2M2dr5dr5/XFe2M2    - 2.0*dFe2M2dr2*dFe2M2dr5*dFe2M2dr5/XFe2M2/XFe2M2 \
			+ 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR2R5R6 R*t*(  3.0*d3MgM13dr2dr5dr6*logA(XMgM13)     + 3.0*d2MgM13dr2dr5*dMgM13dr6/XMgM13 \
                        + 3.0*d2MgM13dr2dr6*dMgM13dr5/XMgM13    + 3.0*dMgM13dr2*d2MgM13dr5dr6/XMgM13    - 3.0*dMgM13dr2*dMgM13dr5*dMgM13dr6/XMgM13/XMgM13 \
                        + 3.0*d3Fe2M13dr2dr5dr6*logA(XFe2M13)   + 3.0*d2Fe2M13dr2dr5*dFe2M13dr6/XFe2M13 \
			+ 3.0*d2Fe2M13dr2dr6*dFe2M13dr5/XFe2M13 + 3.0*dFe2M13dr2*d2Fe2M13dr5dr6/XFe2M13 - 3.0*dFe2M13dr2*dFe2M13dr5*dFe2M13dr6/XFe2M13/XFe2M13 \
		        + 2.0*d3MgM2dr2dr5dr6*logA(XMgM2)       + 2.0*d2MgM2dr2dr5*dMgM2dr6/XMgM2 \
			+ 2.0*d2MgM2dr2dr6*dMgM2dr5/XMgM2       + 2.0*dMgM2dr2*d2MgM2dr5dr6/XMgM2       - 2.0*dMgM2dr2*dMgM2dr5*dMgM2dr6/XMgM2/XMgM2 \
			+ 2.0*d3Fe2M2dr2dr5dr6*logA(XFe2M2)     + 2.0*d2Fe2M2dr2dr5*dFe2M2dr6/XFe2M2 \
			+ 2.0*d2Fe2M2dr2dr6*dFe2M2dr5/XFe2M2    + 2.0*dFe2M2dr2*d2Fe2M2dr5dr6/XFe2M2    - 2.0*dFe2M2dr2*dFe2M2dr5*dFe2M2dr6/XFe2M2/XFe2M2 \
			+ 1.0/XFe3M2/XFe3M2/4.0 )

#define D3GDR2R5DT R*(  3.0*d2MgM13dr2dr5*logA(XMgM13) + 3.0*dMgM13dr2*dMgM13dr5/XMgM13 \
                      + 3.0*d2Fe2M13dr2dr5*logA(XFe2M13) + 3.0*dFe2M13dr2*dFe2M13dr5/XFe2M13 \
		      + 2.0*d2MgM2dr2dr5*logA(XMgM2) + 2.0*dMgM2dr2*dMgM2dr5/XMgM2 \
		      + 2.0*d2Fe2M2dr2dr5*logA(XFe2M2) + 2.0*dFe2M2dr2*dFe2M2dr5/XFe2M2 \
		      + 1.0/XFe3M2/2.0 )
#define D3GDR2R5DP 0.0

#define D3GDR2R6R6 R*t*(  3.0*d3MgM13dr2dr6dr6*logA(XMgM13) + 3.0*d2MgM13dr2dr6*dMgM13dr6/XMgM13 \
                        + 3.0*d2MgM13dr2dr6*dMgM13dr6/XMgM13 +  3.0*dMgM13dr2*d2MgM13dr6dr6/XMgM13 - 3.0*dMgM13dr2*dMgM13dr6*dMgM13dr6/XMgM13/XMgM13 \
                        + 3.0*d3Fe2M13dr2dr6dr6*logA(XFe2M13) + 3.0*d2Fe2M13dr2dr6*dFe2M13dr6/XFe2M13 \
			+ 3.0*d2Fe2M13dr2dr6*dFe2M13dr6/XFe2M13 + 3.0*dFe2M13dr2*d2Fe2M13dr6dr6/XFe2M13 - 3.0*dFe2M13dr2*dFe2M13dr6*dFe2M13dr6/XFe2M13/XFe2M13 \
		        + 2.0*d3MgM2dr2dr6dr6*logA(XMgM2) + 2.0*d2MgM2dr2dr6*dMgM2dr6/XMgM2 \
			+ 2.0*d2MgM2dr2dr6*dMgM2dr6/XMgM2 + 2.0*dMgM2dr2*d2MgM2dr6dr6/XMgM2 - 2.0*dMgM2dr2*dMgM2dr6*dMgM2dr6/XMgM2/XMgM2 \
			+ 2.0*d3Fe2M2dr2dr6dr6*logA(XFe2M2) + 2.0*d2Fe2M2dr2dr6*dFe2M2dr6/XFe2M2 \
			+ 2.0*d2Fe2M2dr2dr6*dFe2M2dr6/XFe2M2 + 2.0*dFe2M2dr2*d2Fe2M2dr6dr6/XFe2M2 - 2.0*dFe2M2dr2*dFe2M2dr6*dFe2M2dr6/XFe2M2/XFe2M2 \
			- 1.0/XAlM2/XAlM2 + 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR2R6DT R*(  3.0*d2MgM13dr2dr6*logA(XMgM13) + 3.0*dMgM13dr2*dMgM13dr6/XMgM13 \
                      + 3.0*d2Fe2M13dr2dr6*logA(XFe2M13) + 3.0*dFe2M13dr2*dFe2M13dr6/XFe2M13 \
		      + 2.0*d2MgM2dr2dr6*logA(XMgM2) + 2.0*dMgM2dr2*dMgM2dr6/XMgM2 \
		      + 2.0*d2Fe2M2dr2dr6*logA(XFe2M2) + 2.0*dFe2M2dr2*dFe2M2dr6/XFe2M2 \
		      + 1.0/XAlM2 + 1.0/XFe3M2/2.0 )
#define D3GDR2R6DP 0.0

#define D3GDR3R3R3 R*t*( 1.0/XNaA/XNaA - 1.0/XVcA/XVcA - 1.0/XAlM2/XAlM2/4.0 + 1.0/XFe3M2/XFe3M2/4.0 + 0.25*0.25/XAlT1/XAlT1 - 0.25*0.25/XSiT1/XSiT1 )
#define D3GDR3R3R4 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR3R3R5 R*t*( 1.0/XFe3M2/XFe3M2/4.0 + 0.25*0.25/XAlT1/XAlT1 - 0.25*0.25/XSiT1/XSiT1 )
#define D3GDR3R3R6 R*t*( 1.0/XNaA/XNaA - 1.0/XVcA/XVcA - 1.0/XAlM2/XAlM2/2.0 + 1.0/XFe3M2/XFe3M2/4.0 + 0.25*0.25/XAlT1/XAlT1 - 0.25*0.25/XSiT1/XSiT1 )
#define D3GDR3R3DT R*( 1.0/XNaA + 1.0/XVcA + 1.0/XAlM2/2.0 + 1.0/XFe3M2/2.0 + 0.25/XAlT1 + 0.25/XSiT1 )
#define D3GDR3R3DP 0.0

#define D3GDR3R4R4 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR3R4R5 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR3R4R6 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR3R4DT R*( 1.0/XFe3M2/2.0 )
#define D3GDR3R4DP 0.0

#define D3GDR3R5R5 R*t*( 1.0/XFe3M2/XFe3M2/4.0 + 0.25*0.25/XAlT1/XAlT1 - 0.25*0.25/XSiT1/XSiT1 )
#define D3GDR3R5R6 R*t*( 1.0/XFe3M2/XFe3M2/4.0 + 0.25*0.25/XAlT1/XAlT1 - 0.25*0.25/XSiT1/XSiT1 )
#define D3GDR3R5DT R*( 1.0/XFe3M2/2.0 + 0.25/XAlT1 + 0.25/XSiT1 )
#define D3GDR3R5DP 0.0

#define D3GDR3R6R6 R*t*( 1.0/XNaA/XNaA - 1.0/XVcA/XVcA - 1.0/XAlM2/XAlM2 + 1.0/XFe3M2/XFe3M2/4.0 + 0.25*0.25/XAlT1/XAlT1 - 0.25*0.25/XSiT1/XSiT1 )
#define D3GDR3R6DT R*( 1.0/XNaA + 1.0/XVcA + 1.0/XAlM2 + 1.0/XFe3M2/2.0 + 0.25/XAlT1 + 0.25/XSiT1 )
#define D3GDR3R6DP 0.0

#define D3GDR4R4R4 R*t*( 1.0/XFe3M2/XFe3M2/4.0 - 1.0/XTiM2/XTiM2/4.0 )
#define D3GDR4R4R5 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR4R4R6 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR4R4DT R*( 1.0/XFe3M2/2.0 + 1.0/XTiM2/2.0 )
#define D3GDR4R4DP 0.0

#define D3GDR4R5R5 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR4R5R6 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR4R5DT R*( 1.0/XFe3M2/2.0 )
#define D3GDR4R5DP 0.0

#define D3GDR4R6R6 R*t*( 1.0/XFe3M2/XFe3M2/4.0 )
#define D3GDR4R6DT R*( 1.0/XFe3M2/2.0 )
#define D3GDR4R6DP 0.0

#define D3GDR5R5R5 R*t*(  3.0*d3MgM13dr5dr5dr5*logA(XMgM13) + 3.0*d2MgM13dr5dr5*dMgM13dr5/XMgM13 \
                        + 3.0*d2MgM13dr5dr5*dMgM13dr5/XMgM13 + 3.0*dMgM13dr5*d2MgM13dr5dr5/XMgM13 - 3.0*dMgM13dr5*dMgM13dr5*dMgM13dr5/XMgM13/XMgM13 \
                        + 3.0*d3Fe2M13dr5dr5dr5*logA(XFe2M13) + 3.0*d2Fe2M13dr5dr5*dFe2M13dr5/XFe2M13 \
			+ 3.0*d2Fe2M13dr5dr5*dFe2M13dr5/XFe2M13 + 3.0*dFe2M13dr5*d2Fe2M13dr5dr5/XFe2M13 - 3.0*dFe2M13dr5*dFe2M13dr5*dFe2M13dr5/XFe2M13/XFe2M13 \
		        + 2.0*d3MgM2dr5dr5dr5*logA(XMgM2) + 2.0*d2MgM2dr5dr5*dMgM2dr5/XMgM2 \
			+ 2.0*d2MgM2dr5dr5*dMgM2dr5/XMgM2 + 2.0*dMgM2dr5*d2MgM2dr5dr5/XMgM2 - 2.0*dMgM2dr5*dMgM2dr5*dMgM2dr5/XMgM2/XMgM2 \
			+ 2.0*d3Fe2M2dr5dr5dr5*logA(XFe2M2) + 2.0*d2Fe2M2dr5dr5*dFe2M2dr5/XFe2M2 \
			+ 2.0*d2Fe2M2dr5dr5*dFe2M2dr5/XFe2M2 + 2.0*dFe2M2dr5*d2Fe2M2dr5dr5/XFe2M2 - 2.0*dFe2M2dr5*dFe2M2dr5*dFe2M2dr5/XFe2M2/XFe2M2 \
			+ 1.0/XFe3M2/XFe3M2/4.0 + 0.25*0.25/XAlT1/XAlT1 - 0.25*0.25/XSiT1/XSiT1 )
#define D3GDR5R5R6 R*t*(  3.0*d3MgM13dr5dr5dr6*logA(XMgM13) + 3.0*d2MgM13dr5dr5*dMgM13dr6/XMgM13 \
                        + 3.0*d2MgM13dr5dr6*dMgM13dr5/XMgM13 + 3.0*dMgM13dr5*d2MgM13dr5dr6/XMgM13 - 3.0*dMgM13dr5*dMgM13dr5*dMgM13dr6/XMgM13/XMgM13 \
                        + 3.0*d3Fe2M13dr5dr5dr6*logA(XFe2M13) + 3.0*d2Fe2M13dr5dr5*dFe2M13dr6/XFe2M13 \
			+ 3.0*d2Fe2M13dr5dr6*dFe2M13dr5/XFe2M13 + 3.0*dFe2M13dr5*d2Fe2M13dr5dr6/XFe2M13 - 3.0*dFe2M13dr5*dFe2M13dr5*dFe2M13dr6/XFe2M13/XFe2M13 \
		        + 2.0*d3MgM2dr5dr5dr6*logA(XMgM2) + 2.0*d2MgM2dr5dr5*dMgM2dr6/XMgM2 \
			+ 2.0*d2MgM2dr5dr6*dMgM2dr5/XMgM2 + 2.0*dMgM2dr5*d2MgM2dr5dr6/XMgM2 - 2.0*dMgM2dr5*dMgM2dr5*dMgM2dr6/XMgM2/XMgM2 \
			+ 2.0*d3Fe2M2dr5dr5dr6*logA(XFe2M2) + 2.0*d2Fe2M2dr5dr5*dFe2M2dr6/XFe2M2 \
			+ 2.0*d2Fe2M2dr5dr6*dFe2M2dr5/XFe2M2 + 2.0*dFe2M2dr5*d2Fe2M2dr5dr6/XFe2M2 - 2.0*dFe2M2dr5*dFe2M2dr5*dFe2M2dr6/XFe2M2/XFe2M2 \
			+ 1.0/XFe3M2/XFe3M2/4.0 + 0.25*0.25/XAlT1/XAlT1 - 0.25*0.25/XSiT1/XSiT1 )
#define D3GDR5R5DT R*(  3.0*d2MgM13dr5dr5*logA(XMgM13) + 3.0*dMgM13dr5*dMgM13dr5/XMgM13 \
                      + 3.0*d2Fe2M13dr5dr5*logA(XFe2M13) + 3.0*dFe2M13dr5*dFe2M13dr5/XFe2M13 \
		      + 2.0*d2MgM2dr5dr5*logA(XMgM2) + 2.0*dMgM2dr5*dMgM2dr5/XMgM2 \
		      + 2.0*d2Fe2M2dr5dr5*logA(XFe2M2) + 2.0*dFe2M2dr5*dFe2M2dr5/XFe2M2 \
		      + 1.0/XFe3M2/2.0 + 0.25/XAlT1 + 0.25/XSiT1 )
#define D3GDR5R5DP 0.0

#define D3GDR5R6R6 R*t*(  3.0*d3MgM13dr5dr6dr6*logA(XMgM13) + 3.0*d2MgM13dr5dr6*dMgM13dr6/XMgM13 \
                        + 3.0*d2MgM13dr5dr6*dMgM13dr6/XMgM13 + 3.0*dMgM13dr5*d2MgM13dr6dr6/XMgM13 - 3.0*dMgM13dr5*dMgM13dr6*dMgM13dr6/XMgM13/XMgM13 \
                        + 3.0*d3Fe2M13dr5dr6dr6*logA(XFe2M13) + 3.0*d2Fe2M13dr5dr6*dFe2M13dr6/XFe2M13 \
			+ 3.0*d2Fe2M13dr5dr6*dFe2M13dr6/XFe2M13 + 3.0*dFe2M13dr5*d2Fe2M13dr6dr6/XFe2M13 - 3.0*dFe2M13dr5*dFe2M13dr6*dFe2M13dr6/XFe2M13/XFe2M13 \
		        + 2.0*d3MgM2dr5dr6dr6*logA(XMgM2) + 2.0*d2MgM2dr5dr6*dMgM2dr6/XMgM2 \
			+ 2.0*d2MgM2dr5dr6*dMgM2dr6/XMgM2 + 2.0*dMgM2dr5*d2MgM2dr6dr6/XMgM2 - 2.0*dMgM2dr5*dMgM2dr6*dMgM2dr6/XMgM2/XMgM2 \
			+ 2.0*d3Fe2M2dr5dr6dr6*logA(XFe2M2) + 2.0*d2Fe2M2dr5dr6*dFe2M2dr6/XFe2M2 \
			+ 2.0*d2Fe2M2dr5dr6*dFe2M2dr6/XFe2M2 + 2.0*dFe2M2dr5*d2Fe2M2dr6dr6/XFe2M2 - 2.0*dFe2M2dr5*dFe2M2dr6*dFe2M2dr6/XFe2M2/XFe2M2 \
			+ 1.0/XFe3M2/XFe3M2/4.0 + 0.25*0.25/XAlT1/XAlT1 - 0.25*0.25/XSiT1/XSiT1 )
#define D3GDR5R6DT R*(  3.0*d2MgM13dr5dr6*logA(XMgM13) + 3.0*dMgM13dr5*dMgM13dr6/XMgM13 \
                      + 3.0*d2Fe2M13dr5dr6*logA(XFe2M13) + 3.0*dFe2M13dr5*dFe2M13dr6/XFe2M13 \
		      + 2.0*d2MgM2dr5dr6*logA(XMgM2) + 2.0*dMgM2dr5*dMgM2dr6/XMgM2 \
		      + 2.0*d2Fe2M2dr5dr6*logA(XFe2M2) + 2.0*dFe2M2dr5*dFe2M2dr6/XFe2M2 \
		      + 1.0/XFe3M2/2.0 + 0.25/XAlT1 + 0.25/XSiT1 )
#define D3GDR5R6DP 0.0

#define D3GDR6R6R6 R*t*(  1.0/XNaA/XNaA - 1.0/XVcA/XVcA - 1.0/XNaM4/XNaM4 + 1.0/XCaM4/XCaM4 \
		        + 3.0*d3MgM13dr6dr6dr6*logA(XMgM13) + 3.0*d2MgM13dr6dr6*dMgM13dr6/XMgM13 \
			+ 3.0*d2MgM13dr6dr6*dMgM13dr6/XMgM13 + 3.0*dMgM13dr6*d2MgM13dr6dr6/XMgM13 - 3.0*dMgM13dr6*dMgM13dr6*dMgM13dr6/XMgM13/XMgM13 \
		        + 3.0*d3Fe2M13dr6dr6dr6*logA(XFe2M13) + 3.0*d2Fe2M13dr6dr6*dFe2M13dr6/XFe2M13 \
			+ 3.0*d2Fe2M13dr6dr6*dFe2M13dr6/XFe2M13 + 3.0*dFe2M13dr6*d2Fe2M13dr6dr6/XFe2M13 - 3.0*dFe2M13dr6*dFe2M13dr6*dFe2M13dr6/XFe2M13/XFe2M13 \
		        + 2.0*d3MgM2dr6dr6dr6*logA(XMgM2) + 2.0*d2MgM2dr6dr6*dMgM2dr6/XMgM2 \
			+ 2.0*d2MgM2dr6dr6*dMgM2dr6/XMgM2 + 2.0*dMgM2dr6*d2MgM2dr6dr6/XMgM2 - 2.0*dMgM2dr6*dMgM2dr6*dMgM2dr6/XMgM2/XMgM2 \
		        + 2.0*d3Fe2M2dr6dr6dr6*logA(XFe2M2) + 2.0*d2Fe2M2dr6dr6*dFe2M2dr6/XFe2M2 \
			+ 2.0*d2Fe2M2dr6dr6*dFe2M2dr6/XFe2M2 + 2.0*dFe2M2dr6*d2Fe2M2dr6dr6/XFe2M2 - 2.0*dFe2M2dr6*dFe2M2dr6*dFe2M2dr6/XFe2M2/XFe2M2 \
		        - 2.0/XAlM2/XAlM2 + 1.0/XFe3M2/XFe3M2/4.0 + 0.25*0.25/XAlT1/XAlT1 - 0.25*0.25/XSiT1/XSiT1 )
#define D3GDR6R6DT R*(  1.0/XNaA + 1.0/XVcA + 1.0/XNaM4 + 1.0/XCaM4 \
		      + 3.0*d2MgM13dr6dr6*logA(XMgM13) + 3.0*dMgM13dr6*dMgM13dr6/XMgM13 \
		      + 3.0*d2Fe2M13dr6dr6*logA(XFe2M13) + 3.0*dFe2M13dr6*dFe2M13dr6/XFe2M13 \
		      + 2.0*d2MgM2dr6dr6*logA(XMgM2) + 2.0*dMgM2dr6*dMgM2dr6/XMgM2 \
		      + 2.0*d2Fe2M2dr6dr6*logA(XFe2M2) + 2.0*dFe2M2dr6*dFe2M2dr6/XFe2M2 \
		      + 2.0/XAlM2 + 1.0/XFe3M2/2.0 + 0.25/XAlT1 + 0.25/XSiT1 )
#define D3GDR6R6DP 0.0

#define D3GDT3     0.0
#define D3GDT2DP   0.0
#define D3GDTDP2   0.0
#define D3GDP3     0.0

#define D3GDR0DT2  0.0
#define D3GDR1DT2  0.0
#define D3GDR2DT2  0.0
#define D3GDR3DT2  0.0
#define D3GDR4DT2  0.0
#define D3GDR5DT2  0.0
#define D3GDR6DT2  0.0

#define D3GDR0DTDP 0.0
#define D3GDR1DTDP 0.0
#define D3GDR2DTDP 0.0
#define D3GDR3DTDP 0.0
#define D3GDR4DTDP 0.0
#define D3GDR5DTDP 0.0
#define D3GDR6DTDP 0.0

#define D3GDR0DP2  0.0
#define D3GDR1DP2  0.0
#define D3GDR2DP2  0.0
#define D3GDR3DP2  0.0
#define D3GDR4DP2  0.0
#define D3GDR5DP2  0.0
#define D3GDR6DP2  0.0

/*
 *=============================================================================
 * Macros for automatic array initialization
 */
 
#define fillDGDR \
 dgdr[0] = DGDR0; dgdr[1] = DGDR1; dgdr[2] = DGDR2; dgdr[3] = DGDR3; \
 dgdr[4] = DGDR4; dgdr[5] = DGDR5; dgdr[6] = DGDR6;
 
#define fillD2GDR2 \
 d2gdr2[0][0] = D2GDR0R0;     d2gdr2[0][1] = D2GDR0R1; \
 d2gdr2[0][2] = D2GDR0R2;     d2gdr2[0][3] = D2GDR0R3; \
 d2gdr2[0][4] = D2GDR0R4;     d2gdr2[0][5] = D2GDR0R5; \
 d2gdr2[0][6] = D2GDR0R6; \
 d2gdr2[1][0] = d2gdr2[0][1]; d2gdr2[1][1] = D2GDR1R1; \
 d2gdr2[1][2] = D2GDR1R2;     d2gdr2[1][3] = D2GDR1R3; \
 d2gdr2[1][4] = D2GDR1R4;     d2gdr2[1][5] = D2GDR1R5; \
 d2gdr2[1][6] = D2GDR1R6; \
 d2gdr2[2][0] = d2gdr2[0][2]; d2gdr2[2][1] = d2gdr2[1][2]; \
 d2gdr2[2][2] = D2GDR2R2;     d2gdr2[2][3] = D2GDR2R3; \
 d2gdr2[2][4] = D2GDR2R4;     d2gdr2[2][5] = D2GDR2R5; \
 d2gdr2[2][6] = D2GDR2R6; \
 d2gdr2[3][0] = d2gdr2[0][3]; d2gdr2[3][1] = d2gdr2[1][3]; \
 d2gdr2[3][2] = d2gdr2[2][3]; d2gdr2[3][3] = D2GDR3R3; \
 d2gdr2[3][4] = D2GDR3R4;     d2gdr2[3][5] = D2GDR3R5; \
 d2gdr2[3][6] = D2GDR3R6; \
 d2gdr2[4][0] = d2gdr2[0][4]; d2gdr2[4][1] = d2gdr2[1][4]; \
 d2gdr2[4][2] = d2gdr2[2][4]; d2gdr2[4][3] = d2gdr2[3][4]; \
 d2gdr2[4][4] = D2GDR4R4;     d2gdr2[4][5] = D2GDR4R5; \
 d2gdr2[4][6] = D2GDR4R6; \
 d2gdr2[5][0] = d2gdr2[0][5]; d2gdr2[5][1] = d2gdr2[1][5]; \
 d2gdr2[5][2] = d2gdr2[2][5]; d2gdr2[5][3] = d2gdr2[3][5]; \
 d2gdr2[5][4] = d2gdr2[4][5]; d2gdr2[5][5] = D2GDR5R5; \
 d2gdr2[5][6] = D2GDR5R6; \
 d2gdr2[6][0] = d2gdr2[0][6]; d2gdr2[6][1] = d2gdr2[1][6]; \
 d2gdr2[6][2] = d2gdr2[2][6]; d2gdr2[6][3] = d2gdr2[3][6]; \
 d2gdr2[6][4] = d2gdr2[4][6]; d2gdr2[6][5] = d2gdr2[5][6]; \
 d2gdr2[6][6] = D2GDR6R6; 

#define fillD2GDRDT \
 d2gdrdt[0] = D2GDR0DT; d2gdrdt[1] = D2GDR1DT; d2gdrdt[2] = D2GDR2DT; \
 d2gdrdt[3] = D2GDR3DT; d2gdrdt[4] = D2GDR4DT; d2gdrdt[5] = D2GDR5DT; \
 d2gdrdt[6] = D2GDR6DT;

#define fillD2GDRDP \
 d2gdrdp[0] = D2GDR0DP; d2gdrdp[1] = D2GDR1DP; d2gdrdp[2] = D2GDR2DP; \
 d2gdrdp[3] = D2GDR3DP; d2gdrdp[4] = D2GDR4DP; d2gdrdp[5] = D2GDR5DP; \
 d2gdrdp[6] = D2GDR6DP;

#define fillD3GDR3 \
 d3gdr3[0][0][0] = D3GDR0R0R0;		d3gdr3[0][0][1] = D3GDR0R0R1; \
 d3gdr3[0][0][2] = D3GDR0R0R2;		d3gdr3[0][0][3] = D3GDR0R0R3; \
 d3gdr3[0][0][4] = D3GDR0R0R4;		d3gdr3[0][0][5] = D3GDR0R0R5; \
 d3gdr3[0][0][6] = D3GDR0R0R6; \
 d3gdr3[0][1][0] = d3gdr3[0][0][1];	d3gdr3[0][1][1] = D3GDR0R1R1; \
 d3gdr3[0][1][2] = D3GDR0R1R2;		d3gdr3[0][1][3] = D3GDR0R1R3; \
 d3gdr3[0][1][4] = D3GDR0R1R4;		d3gdr3[0][1][5] = D3GDR0R1R5; \
 d3gdr3[0][1][6] = D3GDR0R1R6; \
 d3gdr3[0][2][0] = d3gdr3[0][0][2];	d3gdr3[0][2][1] = d3gdr3[0][1][2]; \
 d3gdr3[0][2][2] = D3GDR0R2R2;		d3gdr3[0][2][3] = D3GDR0R2R3; \
 d3gdr3[0][2][4] = D3GDR0R2R4;		d3gdr3[0][2][5] = D3GDR0R2R5; \
 d3gdr3[0][2][6] = D3GDR0R2R6; \
 d3gdr3[0][3][0] = d3gdr3[0][0][3];	d3gdr3[0][3][1] = d3gdr3[0][1][3]; \
 d3gdr3[0][3][2] = d3gdr3[0][2][3];	d3gdr3[0][3][3] = D3GDR0R3R3; \
 d3gdr3[0][3][4] = D3GDR0R3R4;		d3gdr3[0][3][5] = D3GDR0R3R5; \
 d3gdr3[0][3][6] = D3GDR0R3R6; \
 d3gdr3[0][4][0] = d3gdr3[0][0][4];	d3gdr3[0][4][1] = d3gdr3[0][1][4]; \
 d3gdr3[0][4][2] = d3gdr3[0][2][4];	d3gdr3[0][4][3] = d3gdr3[0][3][4]; \
 d3gdr3[0][4][4] = D3GDR0R4R4;		d3gdr3[0][4][5] = D3GDR0R4R5; \
 d3gdr3[0][4][6] = D3GDR0R4R6; \
 d3gdr3[0][5][0] = d3gdr3[0][0][5];	d3gdr3[0][5][1] = d3gdr3[0][1][5]; \
 d3gdr3[0][5][2] = d3gdr3[0][2][5];	d3gdr3[0][5][3] = d3gdr3[0][3][5]; \
 d3gdr3[0][5][4] = d3gdr3[0][4][5];	d3gdr3[0][5][5] = D3GDR0R5R5; \
 d3gdr3[0][5][6] = D3GDR0R5R6; \
 d3gdr3[0][6][0] = d3gdr3[0][0][6];	d3gdr3[0][6][1] = d3gdr3[0][1][6]; \
 d3gdr3[0][6][2] = d3gdr3[0][2][6];	d3gdr3[0][6][3] = d3gdr3[0][3][6]; \
 d3gdr3[0][6][4] = d3gdr3[0][4][6];	d3gdr3[0][6][5] = d3gdr3[0][5][6]; \
 d3gdr3[0][6][6] = D3GDR0R6R6; \
 d3gdr3[1][0][0] = d3gdr3[0][0][1];	d3gdr3[1][0][1] = d3gdr3[0][1][1]; \
 d3gdr3[1][0][2] = d3gdr3[0][1][2];	d3gdr3[1][0][3] = d3gdr3[0][1][3]; \
 d3gdr3[1][0][4] = d3gdr3[0][1][4];	d3gdr3[1][0][5] = d3gdr3[0][1][5]; \
 d3gdr3[1][0][6] = d3gdr3[0][1][6]; \
 d3gdr3[1][1][0] = d3gdr3[0][1][1];	d3gdr3[1][1][1] = D3GDR1R1R1; \
 d3gdr3[1][1][2] = D3GDR1R1R2;		d3gdr3[1][1][3] = D3GDR1R1R3; \
 d3gdr3[1][1][4] = D3GDR1R1R4;		d3gdr3[1][1][5] = D3GDR1R1R5; \
 d3gdr3[1][1][6] = D3GDR1R1R6; \
 d3gdr3[1][2][0] = d3gdr3[0][1][2];	d3gdr3[1][2][1] = d3gdr3[1][1][2]; \
 d3gdr3[1][2][2] = D3GDR1R2R2;		d3gdr3[1][2][3] = D3GDR1R2R3; \
 d3gdr3[1][2][4] = D3GDR1R2R4;		d3gdr3[1][2][5] = D3GDR1R2R5; \
 d3gdr3[1][2][6] = D3GDR1R2R6; \
 d3gdr3[1][3][0] = d3gdr3[0][1][3];	d3gdr3[1][3][1] = d3gdr3[1][1][3]; \
 d3gdr3[1][3][2] = d3gdr3[1][2][3];	d3gdr3[1][3][3] = D3GDR1R3R3; \
 d3gdr3[1][3][4] = D3GDR1R3R4;		d3gdr3[1][3][5] = D3GDR1R3R5; \
 d3gdr3[1][3][6] = D3GDR1R3R6; \
 d3gdr3[1][4][0] = d3gdr3[0][1][4];	d3gdr3[1][4][1] = d3gdr3[1][1][4]; \
 d3gdr3[1][4][2] = d3gdr3[1][2][4];	d3gdr3[1][4][3] = d3gdr3[1][3][4]; \
 d3gdr3[1][4][4] = D3GDR1R4R4;		d3gdr3[1][4][5] = D3GDR1R4R5; \
 d3gdr3[1][4][6] = D3GDR1R4R6; \
 d3gdr3[1][5][0] = d3gdr3[0][1][5];	d3gdr3[1][5][1] = d3gdr3[1][1][5]; \
 d3gdr3[1][5][2] = d3gdr3[1][2][5];	d3gdr3[1][5][3] = d3gdr3[1][3][5]; \
 d3gdr3[1][5][4] = d3gdr3[1][4][5];	d3gdr3[1][5][5] = D3GDR1R5R5; \
 d3gdr3[1][5][6] = D3GDR1R5R6; \
 d3gdr3[1][6][0] = d3gdr3[0][1][6];	d3gdr3[1][6][1] = d3gdr3[1][1][6]; \
 d3gdr3[1][6][2] = d3gdr3[1][2][6];	d3gdr3[1][6][3] = d3gdr3[1][3][6]; \
 d3gdr3[1][6][4] = d3gdr3[1][4][6];	d3gdr3[1][6][5] = d3gdr3[1][5][6]; \
 d3gdr3[1][6][6] = D3GDR1R6R6; \
 d3gdr3[2][0][0] = d3gdr3[0][0][2];	d3gdr3[2][0][1] = d3gdr3[0][1][2]; \
 d3gdr3[2][0][2] = d3gdr3[0][2][2];	d3gdr3[2][0][3] = d3gdr3[0][2][3]; \
 d3gdr3[2][0][4] = d3gdr3[0][2][4];	d3gdr3[2][0][5] = d3gdr3[0][2][5]; \
 d3gdr3[2][0][6] = d3gdr3[0][2][6]; \
 d3gdr3[2][1][0] = d3gdr3[0][1][2];	d3gdr3[2][1][1] = d3gdr3[1][1][2]; \
 d3gdr3[2][1][2] = d3gdr3[1][2][2];	d3gdr3[2][1][3] = d3gdr3[1][2][3]; \
 d3gdr3[2][1][4] = d3gdr3[1][2][4];	d3gdr3[2][1][5] = d3gdr3[1][2][5]; \
 d3gdr3[2][1][6] = d3gdr3[1][2][6]; \
 d3gdr3[2][2][0] = d3gdr3[0][2][2];	d3gdr3[2][2][1] = d3gdr3[1][2][2]; \
 d3gdr3[2][2][2] = D3GDR2R2R2;		d3gdr3[2][2][3] = D3GDR2R2R3; \
 d3gdr3[2][2][4] = D3GDR2R2R4;		d3gdr3[2][2][5] = D3GDR2R2R5; \
 d3gdr3[2][2][6] = D3GDR2R2R6; \
 d3gdr3[2][3][0] = d3gdr3[0][2][3];	d3gdr3[2][3][1] = d3gdr3[1][2][3]; \
 d3gdr3[2][3][2] = d3gdr3[2][2][3];	d3gdr3[2][3][3] = D3GDR2R3R3; \
 d3gdr3[2][3][4] = D3GDR2R3R4;		d3gdr3[2][3][5] = D3GDR2R3R5; \
 d3gdr3[2][3][6] = D3GDR2R3R6; \
 d3gdr3[2][4][0] = d3gdr3[0][2][4];	d3gdr3[2][4][1] = d3gdr3[1][2][4]; \
 d3gdr3[2][4][2] = d3gdr3[2][2][4];	d3gdr3[2][4][3] = d3gdr3[2][3][4]; \
 d3gdr3[2][4][4] = D3GDR2R4R4;		d3gdr3[2][4][5] = D3GDR2R4R5; \
 d3gdr3[2][4][6] = D3GDR2R4R6; \
 d3gdr3[2][5][0] = d3gdr3[0][2][5];	d3gdr3[2][5][1] = d3gdr3[1][2][5]; \
 d3gdr3[2][5][2] = d3gdr3[2][2][5];	d3gdr3[2][5][3] = d3gdr3[2][3][5]; \
 d3gdr3[2][5][4] = d3gdr3[2][4][5];	d3gdr3[2][5][5] = D3GDR2R5R5; \
 d3gdr3[2][5][6] = D3GDR2R5R6; \
 d3gdr3[2][6][0] = d3gdr3[0][2][6];	d3gdr3[2][6][1] = d3gdr3[1][2][6]; \
 d3gdr3[2][6][2] = d3gdr3[2][2][6];	d3gdr3[2][6][3] = d3gdr3[2][3][6]; \
 d3gdr3[2][6][4] = d3gdr3[2][4][6];	d3gdr3[2][6][5] = d3gdr3[2][5][6]; \
 d3gdr3[2][6][6] = D3GDR2R6R6; \
 d3gdr3[3][0][0] = d3gdr3[0][0][3];	d3gdr3[3][0][1] = d3gdr3[0][1][3]; \
 d3gdr3[3][0][2] = d3gdr3[0][2][3];	d3gdr3[3][0][3] = d3gdr3[0][3][3]; \
 d3gdr3[3][0][4] = d3gdr3[0][3][4];	d3gdr3[3][0][5] = d3gdr3[0][3][5]; \
 d3gdr3[3][0][6] = d3gdr3[0][3][6]; \
 d3gdr3[3][1][0] = d3gdr3[0][1][3];	d3gdr3[3][1][1] = d3gdr3[1][1][3]; \
 d3gdr3[3][1][2] = d3gdr3[1][2][3];	d3gdr3[3][1][3] = d3gdr3[1][3][3]; \
 d3gdr3[3][1][4] = d3gdr3[1][3][4];	d3gdr3[3][1][5] = d3gdr3[1][3][5]; \
 d3gdr3[3][1][6] = d3gdr3[1][3][6]; \
 d3gdr3[3][2][0] = d3gdr3[0][2][3];	d3gdr3[3][2][1] = d3gdr3[1][2][3]; \
 d3gdr3[3][2][2] = d3gdr3[2][2][3];	d3gdr3[3][2][3] = d3gdr3[2][3][3]; \
 d3gdr3[3][2][4] = d3gdr3[2][3][4];	d3gdr3[3][2][5] = d3gdr3[2][3][5]; \
 d3gdr3[3][2][6] = d3gdr3[2][3][6]; \
 d3gdr3[3][3][0] = d3gdr3[0][3][3];	d3gdr3[3][3][1] = d3gdr3[1][3][3]; \
 d3gdr3[3][3][2] = d3gdr3[2][3][3];	d3gdr3[3][3][3] = D3GDR3R3R3; \
 d3gdr3[3][3][4] = D3GDR3R3R4;		d3gdr3[3][3][5] = D3GDR3R3R5; \
 d3gdr3[3][3][6] = D3GDR3R3R6; \
 d3gdr3[3][4][0] = d3gdr3[0][3][4];	d3gdr3[3][4][1] = d3gdr3[1][3][4]; \
 d3gdr3[3][4][2] = d3gdr3[2][3][4];	d3gdr3[3][4][3] = d3gdr3[3][3][4]; \
 d3gdr3[3][4][4] = D3GDR3R4R4;		d3gdr3[3][4][5] = D3GDR3R4R5; \
 d3gdr3[3][4][6] = D3GDR3R4R6; \
 d3gdr3[3][5][0] = d3gdr3[0][3][5];	d3gdr3[3][5][1] = d3gdr3[1][3][5]; \
 d3gdr3[3][5][2] = d3gdr3[2][3][5];	d3gdr3[3][5][3] = d3gdr3[3][3][5]; \
 d3gdr3[3][5][4] = d3gdr3[3][4][5];	d3gdr3[3][5][5] = D3GDR3R5R5; \
 d3gdr3[3][5][6] = D3GDR3R5R6; \
 d3gdr3[3][6][0] = d3gdr3[0][3][6];	d3gdr3[3][6][1] = d3gdr3[1][3][6]; \
 d3gdr3[3][6][2] = d3gdr3[2][3][6];	d3gdr3[3][6][3] = d3gdr3[3][3][6]; \
 d3gdr3[3][6][4] = d3gdr3[3][4][6];	d3gdr3[3][6][5] = d3gdr3[3][5][6]; \
 d3gdr3[3][6][6] = D3GDR3R6R6; \
 d3gdr3[4][0][0] = d3gdr3[0][0][4];	d3gdr3[4][0][1] = d3gdr3[0][1][4]; \
 d3gdr3[4][0][2] = d3gdr3[0][2][4];	d3gdr3[4][0][3] = d3gdr3[0][3][4]; \
 d3gdr3[4][0][4] = d3gdr3[0][4][4];	d3gdr3[4][0][5] = d3gdr3[0][4][5]; \
 d3gdr3[4][0][6] = d3gdr3[0][4][6]; \
 d3gdr3[4][1][0] = d3gdr3[0][1][4];	d3gdr3[4][1][1] = d3gdr3[1][1][4]; \
 d3gdr3[4][1][2] = d3gdr3[1][2][4];	d3gdr3[4][1][3] = d3gdr3[1][3][4]; \
 d3gdr3[4][1][4] = d3gdr3[1][4][4];	d3gdr3[4][1][5] = d3gdr3[1][4][5]; \
 d3gdr3[4][1][6] = d3gdr3[1][4][6]; \
 d3gdr3[4][2][0] = d3gdr3[0][2][4];	d3gdr3[4][2][1] = d3gdr3[1][2][4]; \
 d3gdr3[4][2][2] = d3gdr3[2][2][4];	d3gdr3[4][2][3] = d3gdr3[2][3][4]; \
 d3gdr3[4][2][4] = d3gdr3[2][4][4];	d3gdr3[4][2][5] = d3gdr3[2][4][5]; \
 d3gdr3[4][2][6] = d3gdr3[2][4][6]; \
 d3gdr3[4][3][0] = d3gdr3[0][3][4];	d3gdr3[4][3][1] = d3gdr3[1][3][4]; \
 d3gdr3[4][3][2] = d3gdr3[2][3][4];	d3gdr3[4][3][3] = d3gdr3[3][3][4]; \
 d3gdr3[4][3][4] = d3gdr3[3][4][4];	d3gdr3[4][3][5] = d3gdr3[3][4][5]; \
 d3gdr3[4][3][6] = d3gdr3[3][4][6]; \
 d3gdr3[4][4][0] = d3gdr3[0][4][4];	d3gdr3[4][4][1] = d3gdr3[1][4][4]; \
 d3gdr3[4][4][2] = d3gdr3[2][4][4];	d3gdr3[4][4][3] = d3gdr3[3][4][4]; \
 d3gdr3[4][4][4] = D3GDR4R4R4;		d3gdr3[4][4][5] = D3GDR4R4R5; \
 d3gdr3[4][4][6] = D3GDR4R4R6; \
 d3gdr3[4][5][0] = d3gdr3[0][4][5];	d3gdr3[4][5][1] = d3gdr3[1][4][5]; \
 d3gdr3[4][5][2] = d3gdr3[2][4][5];	d3gdr3[4][5][3] = d3gdr3[3][4][5]; \
 d3gdr3[4][5][4] = d3gdr3[4][4][5];	d3gdr3[4][5][5] = D3GDR4R5R5; \
 d3gdr3[4][5][6] = D3GDR4R5R6; \
 d3gdr3[4][6][0] = d3gdr3[0][4][6];	d3gdr3[4][6][1] = d3gdr3[1][4][6]; \
 d3gdr3[4][6][2] = d3gdr3[2][4][6];	d3gdr3[4][6][3] = d3gdr3[3][4][6]; \
 d3gdr3[4][6][4] = d3gdr3[4][4][6];	d3gdr3[4][6][5] = d3gdr3[4][5][6]; \
 d3gdr3[4][6][6] = D3GDR4R6R6; \
 d3gdr3[5][0][0] = d3gdr3[0][0][5];	d3gdr3[5][0][1] = d3gdr3[0][1][5]; \
 d3gdr3[5][0][2] = d3gdr3[0][2][5];	d3gdr3[5][0][3] = d3gdr3[0][3][5]; \
 d3gdr3[5][0][4] = d3gdr3[0][4][5];	d3gdr3[5][0][5] = d3gdr3[0][5][5]; \
 d3gdr3[5][0][6] = d3gdr3[0][5][6]; \
 d3gdr3[5][1][0] = d3gdr3[0][1][5];	d3gdr3[5][1][1] = d3gdr3[1][1][5]; \
 d3gdr3[5][1][2] = d3gdr3[1][2][5];	d3gdr3[5][1][3] = d3gdr3[1][3][5]; \
 d3gdr3[5][1][4] = d3gdr3[1][4][5];	d3gdr3[5][1][5] = d3gdr3[1][5][5]; \
 d3gdr3[5][1][6] = d3gdr3[1][5][6]; \
 d3gdr3[5][2][0] = d3gdr3[0][2][5];	d3gdr3[5][2][1] = d3gdr3[1][2][5]; \
 d3gdr3[5][2][2] = d3gdr3[2][2][5];	d3gdr3[5][2][3] = d3gdr3[2][3][5]; \
 d3gdr3[5][2][4] = d3gdr3[2][4][5];	d3gdr3[5][2][5] = d3gdr3[2][5][5]; \
 d3gdr3[5][2][6] = d3gdr3[2][5][6]; \
 d3gdr3[5][3][0] = d3gdr3[0][3][5];	d3gdr3[5][3][1] = d3gdr3[1][3][5]; \
 d3gdr3[5][3][2] = d3gdr3[2][3][5];	d3gdr3[5][3][3] = d3gdr3[3][3][5]; \
 d3gdr3[5][3][4] = d3gdr3[3][4][5];	d3gdr3[5][3][5] = d3gdr3[3][5][5]; \
 d3gdr3[5][3][6] = d3gdr3[3][5][6]; \
 d3gdr3[5][4][0] = d3gdr3[0][4][5];	d3gdr3[5][4][1] = d3gdr3[1][4][5]; \
 d3gdr3[5][4][2] = d3gdr3[2][4][5];	d3gdr3[5][4][3] = d3gdr3[3][4][5]; \
 d3gdr3[5][4][4] = d3gdr3[4][4][5];	d3gdr3[5][4][5] = d3gdr3[4][5][5]; \
 d3gdr3[5][4][6] = d3gdr3[4][5][6]; \
 d3gdr3[5][5][0] = d3gdr3[0][5][5];	d3gdr3[5][5][1] = d3gdr3[1][5][5]; \
 d3gdr3[5][5][2] = d3gdr3[2][5][5];	d3gdr3[5][5][3] = d3gdr3[3][5][5]; \
 d3gdr3[5][5][4] = d3gdr3[4][5][5];	d3gdr3[5][5][5] = D3GDR5R5R5; \
 d3gdr3[5][5][6] = D3GDR5R5R6; \
 d3gdr3[5][6][0] = d3gdr3[0][5][6];	d3gdr3[5][6][1] = d3gdr3[1][5][6]; \
 d3gdr3[5][6][2] = d3gdr3[2][5][6];	d3gdr3[5][6][3] = d3gdr3[3][5][6]; \
 d3gdr3[5][6][4] = d3gdr3[4][5][6];	d3gdr3[5][6][5] = d3gdr3[5][5][6]; \
 d3gdr3[5][6][6] = D3GDR5R6R6; \
 d3gdr3[6][0][0] = d3gdr3[0][0][6];	d3gdr3[6][0][1] = d3gdr3[0][1][6]; \
 d3gdr3[6][0][2] = d3gdr3[0][2][6];	d3gdr3[6][0][3] = d3gdr3[0][3][6]; \
 d3gdr3[6][0][4] = d3gdr3[0][4][6];	d3gdr3[6][0][5] = d3gdr3[0][5][6]; \
 d3gdr3[6][0][6] = d3gdr3[0][6][6]; \
 d3gdr3[6][1][0] = d3gdr3[0][1][6];	d3gdr3[6][1][1] = d3gdr3[1][1][6]; \
 d3gdr3[6][1][2] = d3gdr3[1][2][6];	d3gdr3[6][1][3] = d3gdr3[1][3][6]; \
 d3gdr3[6][1][4] = d3gdr3[1][4][6];	d3gdr3[6][1][5] = d3gdr3[1][5][6]; \
 d3gdr3[6][1][6] = d3gdr3[1][6][6]; \
 d3gdr3[6][2][0] = d3gdr3[0][2][6];	d3gdr3[6][2][1] = d3gdr3[1][2][6]; \
 d3gdr3[6][2][2] = d3gdr3[2][2][6];	d3gdr3[6][2][3] = d3gdr3[2][3][6]; \
 d3gdr3[6][2][4] = d3gdr3[2][4][6];	d3gdr3[6][2][5] = d3gdr3[2][5][6]; \
 d3gdr3[6][2][6] = d3gdr3[2][6][6]; \
 d3gdr3[6][3][0] = d3gdr3[0][3][6];	d3gdr3[6][3][1] = d3gdr3[1][3][6]; \
 d3gdr3[6][3][2] = d3gdr3[2][3][6];	d3gdr3[6][3][3] = d3gdr3[3][3][6]; \
 d3gdr3[6][3][4] = d3gdr3[3][4][6];	d3gdr3[6][3][5] = d3gdr3[3][5][6]; \
 d3gdr3[6][3][6] = d3gdr3[3][6][6]; \
 d3gdr3[6][4][0] = d3gdr3[0][4][6];	d3gdr3[6][4][1] = d3gdr3[1][4][6]; \
 d3gdr3[6][4][2] = d3gdr3[2][4][6];	d3gdr3[6][4][3] = d3gdr3[3][4][6]; \
 d3gdr3[6][4][4] = d3gdr3[4][4][6];	d3gdr3[6][4][5] = d3gdr3[4][5][6]; \
 d3gdr3[6][4][6] = d3gdr3[4][6][6]; \
 d3gdr3[6][5][0] = d3gdr3[0][5][6];	d3gdr3[6][5][1] = d3gdr3[1][5][6]; \
 d3gdr3[6][5][2] = d3gdr3[2][5][6];	d3gdr3[6][5][3] = d3gdr3[3][5][6]; \
 d3gdr3[6][5][4] = d3gdr3[4][5][6];	d3gdr3[6][5][5] = d3gdr3[5][5][6]; \
 d3gdr3[6][5][6] = d3gdr3[5][6][6]; \
 d3gdr3[6][6][0] = d3gdr3[0][6][6];	d3gdr3[6][6][1] = d3gdr3[1][6][6]; \
 d3gdr3[6][6][2] = d3gdr3[2][6][6];	d3gdr3[6][6][3] = d3gdr3[3][6][6]; \
 d3gdr3[6][6][4] = d3gdr3[4][6][6];	d3gdr3[6][6][5] = d3gdr3[5][6][6]; \
 d3gdr3[6][6][6] = D3GDR6R6R6;
 
#define fillD3GDR2DT \
 d3gdr2dt[0][0] = D3GDR0R0DT;     d3gdr2dt[0][1] = D3GDR0R1DT; \
 d3gdr2dt[0][2] = D3GDR0R2DT;     d3gdr2dt[0][3] = D3GDR0R3DT; \
 d3gdr2dt[0][4] = D3GDR0R4DT;     d3gdr2dt[0][5] = D3GDR0R5DT; \
 d3gdr2dt[0][6] = D3GDR0R6DT; \
 d3gdr2dt[1][0] = d3gdr2dt[0][1]; d3gdr2dt[1][1] = D3GDR1R1DT; \
 d3gdr2dt[1][2] = D3GDR1R2DT;     d3gdr2dt[1][3] = D3GDR1R3DT; \
 d3gdr2dt[1][4] = D3GDR1R4DT;     d3gdr2dt[1][5] = D3GDR1R5DT; \
 d3gdr2dt[1][6] = D3GDR1R6DT; \
 d3gdr2dt[2][0] = d3gdr2dt[0][2]; d3gdr2dt[2][1] = d3gdr2dt[1][2]; \
 d3gdr2dt[2][2] = D3GDR2R2DT;     d3gdr2dt[2][3] = D3GDR2R3DT; \
 d3gdr2dt[2][4] = D3GDR2R4DT;     d3gdr2dt[2][5] = D3GDR2R5DT; \
 d3gdr2dt[2][6] = D3GDR2R6DT; \
 d3gdr2dt[3][0] = d3gdr2dt[0][3]; d3gdr2dt[3][1] = d3gdr2dt[1][3]; \
 d3gdr2dt[3][2] = d3gdr2dt[2][3]; d3gdr2dt[3][3] = D3GDR3R3DT; \
 d3gdr2dt[3][4] = D3GDR3R4DT;     d3gdr2dt[3][5] = D3GDR3R5DT; \
 d3gdr2dt[3][6] = D3GDR3R6DT; \
 d3gdr2dt[4][0] = d3gdr2dt[0][4]; d3gdr2dt[4][1] = d3gdr2dt[1][4]; \
 d3gdr2dt[4][2] = d3gdr2dt[2][4]; d3gdr2dt[4][3] = d3gdr2dt[3][4]; \
 d3gdr2dt[4][4] = D3GDR4R4DT;     d3gdr2dt[4][5] = D3GDR4R5DT; \
 d3gdr2dt[4][6] = D3GDR4R6DT; \
 d3gdr2dt[5][0] = d3gdr2dt[0][5]; d3gdr2dt[5][1] = d3gdr2dt[1][5]; \
 d3gdr2dt[5][2] = d3gdr2dt[2][5]; d3gdr2dt[5][3] = d3gdr2dt[3][5]; \
 d3gdr2dt[5][4] = d3gdr2dt[4][5]; d3gdr2dt[5][5] = D3GDR5R5DT; \
 d3gdr2dt[5][6] = D3GDR5R6DT; \
 d3gdr2dt[6][0] = d3gdr2dt[0][6]; d3gdr2dt[6][1] = d3gdr2dt[1][6]; \
 d3gdr2dt[6][2] = d3gdr2dt[2][6]; d3gdr2dt[6][3] = d3gdr2dt[3][6]; \
 d3gdr2dt[6][4] = d3gdr2dt[4][6]; d3gdr2dt[6][5] = d3gdr2dt[5][6]; \
 d3gdr2dt[6][6] = D3GDR6R6DT; \

#define fillD3GDR2DP \
 d3gdr2dp[0][0] = D3GDR0R0DP;     d3gdr2dp[0][1] = D3GDR0R1DP; \
 d3gdr2dp[0][2] = D3GDR0R2DP;     d3gdr2dp[0][3] = D3GDR0R3DP; \
 d3gdr2dp[0][4] = D3GDR0R4DP;     d3gdr2dp[0][5] = D3GDR0R5DP; \
 d3gdr2dp[0][6] = D3GDR0R6DP; \
 d3gdr2dp[1][0] = d3gdr2dp[0][1]; d3gdr2dp[1][1] = D3GDR1R1DP; \
 d3gdr2dp[1][2] = D3GDR1R2DP;     d3gdr2dp[1][3] = D3GDR1R3DP; \
 d3gdr2dp[1][4] = D3GDR1R4DP;     d3gdr2dp[1][5] = D3GDR1R5DP; \
 d3gdr2dp[1][6] = D3GDR1R6DP; \
 d3gdr2dp[2][0] = d3gdr2dp[0][2]; d3gdr2dp[2][1] = d3gdr2dp[1][2]; \
 d3gdr2dp[2][2] = D3GDR2R2DP;     d3gdr2dp[2][3] = D3GDR2R3DP; \
 d3gdr2dp[2][4] = D3GDR2R4DP;     d3gdr2dp[2][5] = D3GDR2R5DP; \
 d3gdr2dp[2][6] = D3GDR2R6DP; \
 d3gdr2dp[3][0] = d3gdr2dp[0][3]; d3gdr2dp[3][1] = d3gdr2dp[1][3]; \
 d3gdr2dp[3][2] = d3gdr2dp[2][3]; d3gdr2dp[3][3] = D3GDR3R3DP; \
 d3gdr2dp[3][4] = D3GDR3R4DP;     d3gdr2dp[3][5] = D3GDR3R5DP; \
 d3gdr2dp[3][6] = D3GDR3R6DP; \
 d3gdr2dp[4][0] = d3gdr2dp[0][4]; d3gdr2dp[4][1] = d3gdr2dp[1][4]; \
 d3gdr2dp[4][2] = d3gdr2dp[2][4]; d3gdr2dp[4][3] = d3gdr2dp[3][4]; \
 d3gdr2dp[4][4] = D3GDR4R4DP;     d3gdr2dp[4][5] = D3GDR4R5DP; \
 d3gdr2dp[4][6] = D3GDR4R6DP; \
 d3gdr2dp[5][0] = d3gdr2dp[0][5]; d3gdr2dp[5][1] = d3gdr2dp[1][5]; \
 d3gdr2dp[5][2] = d3gdr2dp[2][5]; d3gdr2dp[5][3] = d3gdr2dp[3][5]; \
 d3gdr2dp[5][4] = d3gdr2dp[4][5]; d3gdr2dp[5][5] = D3GDR5R5DP; \
 d3gdr2dp[5][6] = D3GDR5R6DP; \
 d3gdr2dp[6][0] = d3gdr2dp[0][6]; d3gdr2dp[6][1] = d3gdr2dp[1][6]; \
 d3gdr2dp[6][2] = d3gdr2dp[2][6]; d3gdr2dp[6][3] = d3gdr2dp[3][6]; \
 d3gdr2dp[6][4] = d3gdr2dp[4][6]; d3gdr2dp[6][5] = d3gdr2dp[5][6]; \
 d3gdr2dp[6][6] = D3GDR6R6DP;

#define fillD3GDRDT2 \
 d3gdrdt2[0] = D3GDR0DT2; d3gdrdt2[1] = D3GDR1DT2; \
 d3gdrdt2[2] = D3GDR2DT2; d3gdrdt2[3] = D3GDR3DT2; \
 d3gdrdt2[4] = D3GDR4DT2; d3gdrdt2[5] = D3GDR5DT2; \
 d3gdrdt2[6] = D3GDR6DT2;

#define fillD3GDRDTDP \
 d3gdrdtdp[0] = D3GDR0DTDP; d3gdrdtdp[1] = D3GDR1DTDP; \
 d3gdrdtdp[2] = D3GDR2DTDP; d3gdrdtdp[3] = D3GDR3DTDP; \
 d3gdrdtdp[4] = D3GDR4DTDP; d3gdrdtdp[5] = D3GDR5DTDP; \
 d3gdrdtdp[6] = D3GDR6DTDP;

#define fillD3GDRDP2 \
 d3gdrdp2[0] = D3GDR0DP2; d3gdrdp2[1] = D3GDR1DP2; \
 d3gdrdp2[2] = D3GDR2DP2; d3gdrdp2[3] = D3GDR3DP2; \
 d3gdrdp2[4] = D3GDR4DP2; d3gdrdp2[5] = D3GDR5DP2; \
 d3gdrdp2[6] = D3GDR6DP2; 


/*
 *=============================================================================
 * Public functions:
 *    mask  -  bitwise mask for selecting output
 *    t     -  Temperature (K)
 *    p     -  Pressure (bars)
 *    *x    -  (pointer to x[]) Array of independent compositional variables
 */
int
testHrn(int mask, double t, double p,
  int na,          /* Expected number of endmember components                 */
  int nr,          /* Expected number of independent compositional variables  */
  char **names,    /* array of strings of names of endmember components       */
  char **formulas, /* array of strings of formulas of endmember components    */
  double *r,       /* array of indepependent compos variables, check bounds   */
  double *m)       /* array of moles of endmember components, check bounds    */
{
  const char *phase = "leucite.c";
  const char *NAMES[NA]    = { "hastingsite", "k-hastingsite", "pargasite",  "ferro-pargasite",
                               "hornblende",  "kaersutite",    "edenite",    "barroisite"       };
  const char *FORMULAS[NA] = { "NaCa2Mg4FeAl2Si6O22(OH)2", "KCa2Mg4FeAl2Si6O22(OH)2",
			       "NaCa2Mg4AlAl2Si6O22(OH)2", "NaCa2Fe4AlAl2Si6O22(OH)2",
			       "Ca2Mg4AlAlSi7O22(OH)2",    "NaCa2Mg4TiAl2Si6O23(OH)",
			       "NaCa2Mg5AlSi7O22(OH)2",    "NaCaMg3Al2AlSi7O22(OH)2"  };
  int result = TRUE, i;

  if (mask & FIRST) {
    result = result && (na == NA);
    if (!result) printf("<<%s>> Wrong number of components!\n", phase);
  }
  if (mask & SECOND) {
    result = result && (nr == NR);
    if (!result) printf("<<%s>> Wrong number of indep variables!\n", phase);
  }
  if (mask & THIRD) {
    for (i=0; i<NA; i++) {
      result = result && (strcmp(names[i],NAMES[i]) == 0);
      if (!result)
        printf("<<%s>> Component[%d] should be %s not %s.\n",
          phase, i, NAMES[i], names[i]);
    }
  }
  if (mask & FOURTH) {
    for (i=0; i<NA; i++) {
      result = result && (strcmp(formulas[i],FORMULAS[i]) == 0);
      if (!result)
        printf("<<%s>> Component[%d] should have formula %s not %s.\n",
          phase, i, FORMULAS[i], formulas[i]);
    }
  }
  /* Check bounds on the independent compositional variables */
  if (mask & FIFTH) {
    double k = 4.0*r[2]/(4.0+r[5]-r[6]);
    
    result = result & (1.0-r[0]-r[3]-r[6]       	 >= 0.0); /* A Na     */
    result = result & (r[0]                     	 >= 0.0); /* A K      */  
    result = result & (r[3]+r[6]                	 >= 0.0); /* A Vc     */  
    result = result & (r[6]                     	 >= 0.0); /* M4 Na    */  
    result = result & (1.0-r[6]                 	 >= 0.0); /* M4 Ca    */  
    result = result & (1.0-k                    	 >= 0.0); /* M13 Mg   */  
    result = result & (k                        	 >= 0.0); /* M13 Fe2+ */  
    result = result & ((1.0+r[5]-r[6])*(1.0-k)  	 >= 0.0); /* M2 Mg    */  
    result = result & ((1.0+r[5]-r[6])*k        	 >= 0.0); /* M2 Fe2+  */  
    result = result & (1.0-r[1]-r[2]-r[3]-r[4]-r[5]-r[6] >= 0.0); /* M2 Fe3+  */  
    result = result & (r[1]+r[2]+r[3]+2.0*r[6]           >= 0.0); /* M2 Al    */  
    result = result & (r[4]                              >= 0.0); /* M2 Ti    */  
    result = result & (0.5-r[3]/4.0-r[5]/4.0-r[6]/4.0    >= 0.0); /* T1 Al    */  
    result = result & (0.5+r[3]/4.0+r[5]/4.0+r[6]/4.0    >= 0.0); /* T1 Si    */  
  }
  /* Check bounds on moles of endmember components */
  if (mask & SIXTH) {
    double sum = m[0]+m[1]+m[2]+m[3]+m[4]+m[5]+m[6]+m[7]; 
    double k = 4.0*m[3]/(4.0*sum+m[6]-m[7]);
    
    result = result & (sum-m[1]-m[4]-m[7]       	  >= 0.0); /* A Na     */
    result = result & (m[1]                     	  >= 0.0); /* A K      */
    result = result & (m[4]+m[7]                	  >= 0.0); /* A Vc     */
    result = result & (m[7]                     	  >= 0.0); /* M4 Na    */
    result = result & (sum-m[7]                 	  >= 0.0); /* M4 Ca    */
    result = result & (1.0-k                    	  >= 0.0); /* M13 Mg   */
    result = result & (k                        	  >= 0.0); /* M13 Fe2+ */
    result = result & ((sum+m[6]-m[7])*(1.0-k)  	  >= 0.0); /* M2 Mg    */
    result = result & ((sum+m[6]-m[7])*k        	  >= 0.0); /* M2 Fe2+  */
    result = result & (sum-m[2]-m[3]-m[4]-m[5]-m[6]-m[7]  >= 0.0); /* M2 Fe3+  */
    result = result & (m[2]+m[3]+m[4]+2.0*m[7]            >= 0.0); /* M2 Al    */
    result = result & (m[5]                               >= 0.0); /* M2 Ti    */
    result = result & (sum/2.0-m[4]/4.0-m[6]/4.0-m[7]/4.0 >= 0.0); /* T1 Al    */
    result = result & (sum/2.0+m[4]/4.0+m[6]/4.0+m[7]/4.0 >= 0.0); /* T1 Si    */
  }

  return result;
}

void
conHrn(int inpMask, int outMask, double t, double p,
  double *e,      /* comp of hornblende in moles of elements                  */
  double *m,      /* comp of hornblende in moles of endmember components      */
  double *r,      /* comp of hornblende in terms of the independent comp var  */
  double *x,      /* comp of hornblende in mole fractions of endmember comp   */
  double **dm,    /* Jacobian matrix: dm[i][j] = dr[i]/dm[j]                  */
  double ***d2m,  /* vector of matrices: d2m[i][j][k] = d2r[i]/dm[j]dm[k]     */
  double **dr,    /* Jacobian matrix: dr[i][j] = dx[i]/dr[j]                  */
  double ****d3m) /* 3rd deriv matrix: d3m[i][j][k][l]=d3r[i]/dm[j]dm[k]dm[l] */
{
  /*---------------------------------------------------------------------------
  Not all combinations of inpMask and outMask are feasible. Valid
    combinations are:

       inpMask          outMask
  (1)  FIRST            SECOND
  (2)  SECOND           THIRD  | FOURTH  | FIFTH | SIXTH | EIGHTH
  (3)  THIRD            FOURTH | SEVENTH

  (1) converts a vector of moles of elements into a vector of moles of 
      endmember leucite components.
  (2) calculates from a vector of moles of endmember components, one or
      all of: r[], x[], dr[]/dm[], d2r[]/dm[]dm[], or d3r[]/dm[]dm[]dm[]
  (3) calculates from a vector of independent compositional variables
      mole fractions of endmember components and/or the Jacobian matrix
      dx[]/dr[]

  ----------------------------------------------------------------------------*/

  int i, j, k;

  if (inpMask == FIRST && outMask == SECOND) {
    static const int Na = 11;
    static const int Mg = 12;
    static const int Al = 13;
    static const int Si = 14;
    static const int K  = 19;
    static const int Ca = 20;
    static const int Ti = 22;
    static const int Fe = 26;
    
    int okay = FALSE, iter = 0;
    double silica = e[Si];
    double sum=0.0, k=0.0;
     
    printf("...conHrn: Entering conHrn with inpMask = FIRST, outMask = SECOND for elemental conversion to moles.\n");
    while (!okay) {
      m[0] = 20.0*e[Fe]/13.0 - 2.0*e[K] + 20.0*e[Mg]/13.0 - 2.0*e[Ca] - e[Na] - 6.0*silica/13.0 + 7.0*e[Al]/13.0 + 7.0*e[Ti]/13.0;
      m[1] = e[K];
      m[2] = - 3.0*silica/26.0 - 8.0*e[Mg]/13.0 + 3.0*e[Na]/4.0 + 3.0*e[K]/4.0 + 3.0*e[Ca]/2.0 - 45.0*e[Fe]/52.0  + 7.0*e[Al]/52.0 - 45.0*e[Ti]/52.0;
      m[3] = - 5.0*e[Mg]/13.0 + e[Ca]/2.0 + e[Na]/4.0 + e[K]/4.0 + 3.0*silica/26.0 - 7.0*e[Al]/52.0 - 7.0*e[Fe]/52.0 - 7.0*e[Ti]/52.0;
      m[4] = e[Al]/13.0 + e[Fe]/13.0 - e[Na] - e[K] + e[Ti]/13.0 + silica/13.0 + e[Mg]/13.0;
      m[5] = e[Ti];
      m[6] = 4.0*silica/13.0 + e[Na] + e[K] + e[Ca] - 9.0*e[Al]/13.0 - 9.0*e[Fe]/13.0 - 9.0*e[Ti]/13.0 - 9.0*e[Mg]/13.0;
      m[7] = -e[Ca] + 2.0*e[Al]/13.0 + 2.0*e[Fe]/13.0 + 2.0*e[Ti]/13.0 + 2.0*silica/13.0 + 2.0*e[Mg]/13.0;

      okay = TRUE;
      sum = m[0]+m[1]+m[2]+m[3]+m[4]+m[5]+m[6]+m[7]; 
      k = 4.0*m[3]/(4.0*sum+m[6]-m[7]);
	
      if      (m[1]  < 0.0) okay = TRUE; /* give up, as e[K]  is negative */
      else if (m[5]  < 0.0) okay = TRUE; /* give up, as e[Ti] is negative */
      else if (k     > 1.0) okay = TRUE; /* give up, no dependence on Si  */
      else {  /* all the rest depend on silica */
        double silicaMin = silica, silicaMax = silica;
	int badConstraints = 0;
      
        if (sum-m[1]-m[4]-m[7] < 0.0) {  /* A Na      */
	  double zeroSi = - e[Al] - e[Fe] + 13.0*e[Ca]/2.0 - e[Mg] - e[Ti] + 13.0*e[Na]/2.0;
	  if (zeroSi < silicaMax) silicaMax = zeroSi;
	  okay = FALSE;
	  badConstraints |= 01;
	} else if (sum-m[1]-m[4]-m[7] > sum) {
	  double oneSi = - e[Al] - e[Fe] + 13.0*e[Ca]/3.0 - e[Mg] - e[Ti] + 13.0*e[Na]/3.0;
	  if (oneSi > silicaMin) silicaMin = oneSi;
	  okay = FALSE;
	  badConstraints |= 010001;
	}
	
        if (m[4]+m[7] < 0.0) {  /* A Vc      */
	  double zeroSi = - e[Al] - e[Fe] + 13.0*e[Na]/3.0 + 13.0*e[K]/3.0 - e[Ti] - e[Mg] + 13.0*e[Ca]/3.0;
	  if (zeroSi > silicaMin) silicaMin = zeroSi;
	  okay = FALSE;
	  badConstraints |= 02;
	} else if (m[4]+m[7] > sum) {
	  double oneSi = - e[Al] - e[Fe] + 13.0*e[Na]/2.0 + 13.0*e[K]/2.0 - e[Ti] - e[Mg] + 13.0*e[Ca]/2.0;
	  if (oneSi < silicaMax) silicaMax = oneSi;
	  okay = FALSE;
	  badConstraints |= 010002;
	}
	
        if (m[7] < 0.0) {  /* M4 Na     */
	  double zeroSi = 13.0*e[Ca]/2.0 - e[Al] - e[Fe] - e[Ti] - e[Mg];
	  if (zeroSi > silicaMin) silicaMin = zeroSi;
	  okay = FALSE;
	  badConstraints |= 04;
	} else if (m[7] > sum) {
	  double oneSi = 13.0*e[Ca] - e[Al] - e[Fe] - e[Ti] - e[Mg];
	  if (oneSi < silicaMax) silicaMax = oneSi;
	  okay = FALSE;
	  badConstraints |= 010004;
	}
	
        if (sum-m[7] < 0.0) {  /* M4 Ca     */
	  double zeroSi = - e[Al] - e[Fe] + 13.0*e[Ca] - e[Mg] - e[Ti];
	  if (zeroSi < silicaMax) silicaMax = zeroSi;
	  okay = FALSE;
	  badConstraints |= 010;
	} else if (sum-m[7] > sum) {
	  double oneSi = - e[Al] - e[Fe] - 13.0*e[Ca]/2.0 - e[Mg] - e[Ti];
	  if (oneSi > silicaMin) silicaMin = oneSi;
	  okay = FALSE;
	  badConstraints |= 010010;
	}
	
        if (k				       < 0.0) {  /* M13 Fe2+  */
	  double zeroSi = 10.0*e[Mg]/3.0 - 13.0*e[Ca]/3.0 - 13.0*e[Na]/6.0 - 13.0*e[K]/6.0 + 7.0*e[Al]/6.0 + 7.0*e[Fe]/6.0 + 7.0*e[Ti]/6.0;
	  if (zeroSi > silicaMin) silicaMin = zeroSi;
	  okay = FALSE;
	  badConstraints |= 020;
	}
	
        if ((sum+m[6]-m[7]) < 0.0) {  /* M2 Mg+Fe2 */
	  double zeroSi = 10.0*e[Al]/3.0 + 10.0*e[Fe]/3.0 - 26.0*e[Ca]/3.0 + 10.0*e[Mg]/3.0 + 10.0*e[Ti]/3.0 - 13.0*e[Na]/3.0 - 13.0*e[K]/3.0;
	  if (zeroSi > silicaMin) silicaMin = zeroSi;
	  okay = FALSE;
	  badConstraints |= 040;
	} else if ((sum+m[6]-m[7]) > 2.0*sum) {
	  double oneSi = 12.0*e[Ti] + 12.0*e[Fe] + 12.0*e[Mg] + 12.0*e[Al] - 13.0*e[Na] - 13.0*e[K] - 26.0*e[Ca];
	  if (oneSi < silicaMax) silicaMax = oneSi;
	  okay = FALSE;
	  badConstraints |= 010040;
	}
	
        if (sum-m[2]-m[3]-m[4]-m[5]-m[6]-m[7]  < 0.0) {  /* M2 Fe3+   */
	  double zeroSi = - 13.0*e[Ca]/3.0 - 13.0*e[Na]/6.0 - 13.0*e[K]/6.0 + 10.0*e[Fe]/3.0 + 10.0*e[Mg]/3.0 + 7.0*e[Al]/6.0 + 7.0*e[Ti]/6.0;
	  if (zeroSi < silicaMax) silicaMax = zeroSi;
	  okay = FALSE;
	  badConstraints |= 0100;
	} else if (sum-m[2]-m[3]-m[4]-m[5]-m[6]-m[7]  > sum) {  /* M2 Fe3+   */
	  double oneSi = - 26.0*e[Ca]/7.0 - 13.0*e[Na]/7.0 - 13.0*e[K]/7.0 + 19.0*e[Fe]/7.0 + 19.0*e[Mg]/7.0 + 6.0*e[Al]/7.0 + 6.0*e[Ti]/7.0;
	  if (oneSi > silicaMin) silicaMin = oneSi;
	  okay = FALSE;
	  badConstraints |= 010100;
	}
	
        if (m[2]+m[3]+m[4]+2.0*m[7] < 0.0) {  /* M2 Al     */
	  double zeroSi = - e[Al] + 8.0*e[Fe]/5.0 + 8.0*e[Mg]/5.0 + 8.0*e[Ti]/5.0;
	  if (zeroSi > silicaMin) silicaMin = zeroSi;
	  okay = FALSE;	  
	  badConstraints |= 0200;
	} else if (m[2]+m[3]+m[4]+2.0*m[7] > 2.0*sum) {  /* M2 Al     */
	  double oneSi = - e[Al] + 10.0*e[Fe]/3.0 + 10.0*e[Mg]/3.0 + 10.0*e[Ti]/3.0;
	  if (oneSi < silicaMax) silicaMax = oneSi;
	  okay = FALSE;	  
	  badConstraints |= 010200;
	}
	
        if (sum/2.0-m[4]/4.0-m[6]/4.0-m[7]/4.0 < 0.0) {  /* T1 Al     */
	  double zeroSi = 8.0*e[Al]/5.0 + 8.0*e[Fe]/5.0 + 8.0*e[Mg]/5.0 + 8.0*e[Ti]/5.0;
	  if (zeroSi < silicaMax) silicaMax = zeroSi;
	  okay = FALSE;
	  badConstraints |= 0400;
	} else if (sum/2.0-m[4]/4.0-m[6]/4.0-m[7]/4.0 > sum/2.0) {  /* T1 Al     */
	  double oneSi = 6.0*e[Al]/7.0 + 6.0*e[Fe]/7.0 + 6.0*e[Mg]/7.0 + 6.0*e[Ti]/7.0;
	  if (oneSi > silicaMin) silicaMin = oneSi;
	  okay = FALSE;
	  badConstraints |= 010400;
	}
	
        if (sum/2.0+m[4]/4.0+m[6]/4.0+m[7]/4.0 < 0.0) {  /* T1 Si     */
	  double zeroSi = 4.0*e[Al]/9.0 + 4.0*e[Fe]/9.0 + 4.0*e[Mg]/9.0 + 4.0*e[Ti]/9.0;
	  if (zeroSi > silicaMin) silicaMin = zeroSi;
	  okay = FALSE;
	  badConstraints |= 01000;
	} else if (sum/2.0+m[4]/4.0+m[6]/4.0+m[7]/4.0 > 3.0*sum/4.0) {  /* T1 Si     */
	  double oneSi = 7.0*e[Al]/6.0 + 7.0*e[Fe]/6.0 + 7.0*e[Mg]/6.0 + 7.0*e[Ti]/6.0;
	  if (oneSi < silicaMax) silicaMax = oneSi;
	  okay = FALSE;
	  badConstraints |= 011000;
	}
	
	if (!okay) {
	  printf("...conHrn: Problem with casting compostion into endmember moles (%o).  Adjusting silica (iter = %d)\n", badConstraints, iter);
	  printf(".........: Silica input: %g, computed Silica Min: %g, Max: %g\n", e[Si], silicaMin, silicaMax);
	  if (silicaMax < 0.90*e[Si]) {
	    printf(".........: Giving up. Computed maximum silica content is %.2f%% of measured silica.\n",
	      100.0*silicaMax/e[Si]);
	    okay = TRUE;
	  }
	  if (silicaMin > 1.10*e[Si]) {
	    printf(".........: Giving up. Computed minimum silica content is %.2f%% of measured silica.\n",
	      100.0*silicaMin/e[Si]);
	    okay = TRUE;
	  }
	  if (iter > 1) {
	    printf(".........: Giving up. Too many iterations.\n");
	    okay = TRUE;
	  }
	  if        ((silica == silicaMin) && !okay) {
	    printf(".........: Silica reset from %g to %g (%.2f%%)\n", silica, silicaMax, 100.0*(silicaMax-silica)/silica);
	    silica = silicaMax - sqrt(DBL_EPSILON);
	  } else if ((silica == silicaMax) && !okay) {
	    printf(".........: Silica reset from %g to %g (%.2f%%)\n", silica, silicaMin, 100.0*(silicaMin-silica)/silica);
	    silica = silicaMin + sqrt(DBL_EPSILON);
	  } else if (!okay) {
	    printf(".........: Silica reset from %g to %g (%.2f%%)\n", silica, (silicaMin+silicaMax)/2.0,
	      ((silicaMin+silicaMax)/2.0 - silica)/silica);
	    silica = (silicaMin+silicaMax)/2.0;
	  }
	  
	}
	
	iter++;
      }
    }
    printf("	    A Na     = %g\n", 1.0-m[1]/sum-m[4]/sum-m[7]/sum);  			
    printf("	    A K      = %g\n", m[1]/sum);				
    printf("	    A Vc     = %g\n", m[4]/sum+m[7]/sum);			
    printf("	    M4 Na    = %g\n", m[7]/sum);				
    printf("	    M4 Ca    = %g\n", 1.0-m[7]/sum);			
    printf("	    M13 Mg   = %g\n", 1.0-k);				
    printf("	    M13 Fe2+ = %g\n", k);				
    printf("	    M2 Mg    = %g\n", (1.0+m[6]/sum-m[7]/sum)*(1.0-k)/2.0); 	
    printf("	    M2 Fe2+  = %g\n", (1.0+m[6]/sum-m[7]/sum)*k/2.0);		
    printf("	    M2 Fe3+  = %g\n", (1.0-m[2]/sum-m[3]/sum-m[4]/sum-m[5]/sum-m[6]/sum-m[7]/sum)/2.0); 
    printf("	    M2 Al    = %g\n", (m[2]/sum+m[3]/sum+m[4]/sum+2.0*m[7]/sum)/2.0); 	
    printf("	    M2 Ti    = %g\n", m[5]/sum/2.0);				
    printf("	    T1 Al    = %g\n", 1.0/2.0-m[4]/4.0/sum-m[6]/4.0/sum-m[7]/4.0/sum);
    printf("	    T1 Si    = %g\n", 1.0/2.0+m[4]/4.0/sum+m[6]/4.0/sum+m[7]/4.0/sum);
    printf("	    X[Hast]  = %g\n", m[0]/sum);
    printf("	    X[K-Ht]  = %g\n", m[1]/sum);
    printf("	    X[Parg]  = %g\n", m[2]/sum);
    printf("	    X[Fe-P]  = %g\n", m[3]/sum);
    printf("	    X[Hrnb]  = %g\n", m[4]/sum);
    printf("	    X[Kaer]  = %g\n", m[5]/sum);
    printf("	    X[Eden]  = %g\n", m[6]/sum);
    printf("	    X[Barr]  = %g\n", m[7]/sum);

  } else if (inpMask == SECOND) {
    double sum;

    if (outMask & ~(THIRD | FOURTH | FIFTH | SIXTH | EIGHTH))
      printf("Illegal call to conHrn with inpMask = %o and outMask = %o\n",
        inpMask, outMask);

    for (i=0, sum=0.0; i<NA; i++) sum += m[i];

    if (outMask & THIRD) {
      for (i=0; i<NR; i++) r[i] = (sum != 0.0) ? m[i+1]/sum : 0.0; 
    }  

    if (outMask & FOURTH) {
      /* Converts a vector of moles of end-member components (m) into a vector
         of mole fractions of endmember components                            */
      for (i=0; i<NA; i++) x[i] = (sum != 0.0) ? m[i]/sum : 0.0; 
    }

    if (outMask & FIFTH) {
      /* Calculates the matrix dr[i]/dm[j] using m[] as input                 */
      if (sum == 0.0) {
        for (i=0; i<NR; i++) { for (j=0; j<NA; j++) dm[i][j] = 0.0; }
      } else {
        for (i=0; i<NR; i++) {
          for (j=0; j<NA; j++)
            dm[i][j] = (i+1 == j) ? (1.0-m[i+1]/sum)/sum : - m[i+1]/SQUARE(sum);
        }
      }

    }

    if (outMask & SIXTH) {
      /* Calculates the matrix d2r[i]/dm[j]dm[k] using m[] as input           */

      if (sum == 0.0) {
        for (i=0; i<NR; i++) {
          for (j=0; j<NA; j++)  {
            for (k=0; k<NA; k++) d2m[i][j][k] = 0.0;
          }
        }
      } else {
        for (i=0; i<NR; i++) {
          for (j=0; j<NA; j++)  {
            for (k=0; k<NA; k++) {
              d2m[i][j][k]  = 2.0*m[i+1]/CUBE(sum);
              d2m[i][j][k] -= (i+1 == j) ? 1.0/SQUARE(sum) : 0.0;
              d2m[i][j][k] -= (i+1 == k) ? 1.0/SQUARE(sum) : 0.0;
            }
          }
        }
      }

    }

    if (outMask & EIGHTH) {
      /* calculates the matrix d3r[i]/dm[j]dm[k]dm[l] using m[] as input */
      int l;

      if (sum == 0.0) {
        for (i=0; i<NR; i++) {
          for (j=0; j<NA; j++)  {
            for (k=0; k<NA; k++)  {
              for (l=0; l<NA; l++) d3m[i][j][k][l] = 0.0;
            }
          }
        }
      } else {
        for (i=0; i<NR; i++) {
          for (j=0; j<NA; j++)  {
            for (k=0; k<NA; k++)  {
              for (l=0; l<NA; l++)  {
                d3m[i][j][k][l]  = -6.0*m[i+1]/QUARTIC(sum);
                d3m[i][j][k][l] += (i+1 == j) ? 2.0/CUBE(sum) : 0.0;
                d3m[i][j][k][l] += (i+1 == k) ? 2.0/CUBE(sum) : 0.0;
                d3m[i][j][k][l] += (i+1 == l) ? 2.0/CUBE(sum) : 0.0;
              }
            }
          }
        }
      }

    }

  } else if (inpMask == THIRD) {

    if (outMask & ~(FOURTH | SEVENTH))
      printf("Illegal call to conHrn with inpMask = %o and outMask = %o\n",
        inpMask, outMask);

    if (outMask & FOURTH) {
      /* Converts a vector of independent compositional variables (r) 
         into a vector of mole fractions of endmember components (x).         */

      for (i=0, x[0]=1.0; i<NR; i++) { x[i+1] = r[i]; x[0] -= r[i]; }
    }

    if (outMask & SEVENTH) {
      /* computes the Jacobian matrix dr[i][j] = dx[i]/dr[j] */
      for (i=0; i<NR; i++) for (j=0; j<NR; j++) dr[i+1][j] = (i == j) ? 1.0 : 0.0;
                           for (j=0; j<NR; j++) dr[0][j] = -1.0;
    }

  } else  {
    printf("Illegal call to conHrn with inpMask = %o and outMask = %o\n",
      inpMask, outMask);
  }

}

void
dispHrn(int mask, double t, double p, double *x,
  char **formula            /* Mineral formula for interface display MASK: 1 */
  )
{
  double *r = x;
  static char masterString[] = {
/*             11111111112222222222333333333344444444445555555555666666666677777777778
     012345678901234567890123456789012345678901234567890123456789012345678901234567890 */
    "[]_.__Na_.__K_.__Ca_.__Mg_.__Fe2+_.__Ti_.__Fe3+_.__Al_.__Si_.__O_.__(OH)_.__" };

  if (mask & FIRST) {
    char *string = strcpy((char *) malloc((size_t) (strlen(masterString)+1)*sizeof(char)), masterString);
    double totVc, totNa, totK, totCa, totMg, totFe2, totTi, totFe3, totAl, totSi, totO, totOH;
    char n[5];
    int i;

    totVc  = r[3] + r[6];
    totNa  = 1.0 - r[0] - r[3];
    totK   = r[0];
    totCa  = 2.0 - r[6];
    totMg  = 4.0 - 4.0*r[2] + r[5] - r[6];
    totFe2 = 4.0*r[2];
    totTi  = r[4];
    totFe3 = 1.0 - r[1] - r[2] - r[3] - r[4] - r[5] - r[6];
    totAl  = 2.0 + r[1] + r[2] - r[5] + r[6];
    totSi  = 6.0 + r[3] + r[5] + r[6]; 
    totO   = 22.0 + r[4];
    totOH  = 2.0 - r[4];

    (void) snprintf(n, 5, "%4.2f", totVc ); for (i=0; i<4; i++) string[ 2+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", totNa ); for (i=0; i<4; i++) string[ 8+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", totK  ); for (i=0; i<4; i++) string[13+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", totCa ); for (i=0; i<4; i++) string[19+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", totMg ); for (i=0; i<4; i++) string[25+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", totFe2); for (i=0; i<4; i++) string[33+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", totTi ); for (i=0; i<4; i++) string[39+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", totFe3); for (i=0; i<4; i++) string[47+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", totAl ); for (i=0; i<4; i++) string[53+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", totSi ); for (i=0; i<4; i++) string[59+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", totO  ); for (i=0; i<4; i++) string[64+i] = n[i];
    (void) snprintf(n, 5, "%4.2f", totOH ); for (i=0; i<4; i++) string[72+i] = n[i];

    *formula = string;
  }
}

void 
actHrn(int mask, double t, double p, double *x, 
  double *a,  /* (pointer to a[]) activities              BINARY MASK: 0001 */
  double *mu, /* (pointer to mu[]) chemical potentials    BINARY MASK: 0010 */
  double **dx /* (pointer to dx[][]) d(a[])/d(x[])        BINARY MASK: 0100 */
  )           /* exclusion criteria applied to results if BINARY MASK: 1000 */
{
  double *r      = x;
  double k       = 4.0*r[2]/(4.0+r[5]-r[6]);
  double XNaA    = (1.0-r[0]-r[3]-r[6] > 0.0)       	     ? 1.0-r[0]-r[3]-r[6]       	       : DBL_EPSILON;
  double XKA     = (r[0] > 0.0)                     	     ? r[0]		        	       : DBL_EPSILON;
  double XVcA    = (r[3]+r[6] > 0.0)                	     ? r[3]+r[6]	        	       : DBL_EPSILON;
  double XNaM4   = (r[6] > 0.0)                     	     ? r[6]		        	       : DBL_EPSILON;
  double XCaM4   = (1.0-r[6] > 0.0)                 	     ? 1.0-r[6] 	        	       : DBL_EPSILON;
  double XMgM13  = (1.0-k > 0.0)                    	     ? 1.0-k		        	       : DBL_EPSILON;
  double XFe2M13 = (k > 0.0)                        	     ? k		        	       : DBL_EPSILON;
  double XMgM2   = ((1.0+r[5]-r[6])*(1.0-k) > 0.0)  	     ? (1.0+r[5]-r[6])*(1.0-k)/2.0  	       : DBL_EPSILON;
  double XFe2M2  = ((1.0+r[5]-r[6])*k > 0.0)        	     ? (1.0+r[5]-r[6])*k/2.0        	       : DBL_EPSILON;
  double XAlM2   = (r[1]+r[2]+r[3]+2.0*r[6] > 0.0)  	     ? (r[1]+r[2]+r[3]+2.0*r[6])/2.0  	       : DBL_EPSILON;
  double XFe3M2  = (1.0-r[1]-r[2]-r[3]-r[4]-r[5]-r[6] > 0.0) ? (1.0-r[1]-r[2]-r[3]-r[4]-r[5]-r[6])/2.0 : DBL_EPSILON;
  double XTiM2   = (r[4] > 0.0)                              ? r[4]/2.0                                : DBL_EPSILON;
  double XAlT1   = (0.5-(r[3]+r[5]+r[6])/4.0 > 0.0)          ? 0.5-(r[3]+r[5]+r[6])/4.0                : DBL_EPSILON;
  double XSiT1   = (0.5+(r[3]+r[5]+r[6])/4.0 > 0.0)          ? 0.5+(r[3]+r[5]+r[6])/4.0                : DBL_EPSILON;

  double g, dgdr[NR], fr[NA][NR];
  int i, j;
  
  for(i=0; i<NA; i++) {
    fr[i][0] = FR0(i);
    fr[i][1] = FR1(i);
    fr[i][2] = FR2(i);
    fr[i][3] = FR3(i);
    fr[i][4] = FR4(i);
    fr[i][5] = FR5(i);
    fr[i][6] = FR6(i);
  }

  g       = G;
  fillDGDR

  if (mask & FIRST) {
    for(i=0; i<NA; i++) {
       for (a[i]=g, j=0; j<NR; j++) a[i] += fr[i][j]*dgdr[j];
       a[i] = exp(a[i]/(R*t));
    }
  }

  if (mask & SECOND) {
    for(i=0; i<NA; i++) {
       for (mu[i]=g, j=0; j<NR; j++) mu[i] += fr[i][j]*dgdr[j];
    }
  }

  if (mask & THIRD) {
    double d2gdr2[NR][NR], dfrdr[NA][NR], sum;
    int l;

    fillD2GDR2

    for(i=0; i<NA; i++) {
      dfrdr[i][0] = DFR0DR0(i);
      dfrdr[i][1] = DFR1DR1(i);
      dfrdr[i][2] = DFR2DR2(i);
      dfrdr[i][3] = DFR3DR3(i);
      dfrdr[i][4] = DFR4DR4(i);
      dfrdr[i][5] = DFR5DR5(i);
      dfrdr[i][6] = DFR6DR6(i);
    }

    for (i=0; i<NA; i++) {
       for (l=0; l<NR; l++) {
          for (dx[i][l]=g, j=0; j<NR; j++) dx[i][l] += fr[i][j]*dgdr[j];
          dx[i][l] = exp(dx[i][l]/(R*t));
          sum = (1.0+dfrdr[i][l])*dgdr[l];
          for (j=0; j<NR; j++) sum += fr[i][j]*d2gdr2[j][l];
          dx[i][l] *= sum/(R*t);
       }
    }  
  }

  if (mask & FOURTH) {
    /* implement exclusion criteria on quantities for preclb routines  */
    int exclusion[NA];
    
    exclusion[0] = (XNaA > 0.05)  		   && (XCaM4 > 0.05) && (XMgM13  > 0.05) && (XFe3M2 > 0.05) && (XAlT1 > 0.05) && (XSiT1 > 0.05);
    exclusion[1] = (XKA  > 0.05)  		   && (XCaM4 > 0.05) && (XMgM13  > 0.05) && (XFe3M2 > 0.05) && (XAlT1 > 0.05) && (XSiT1 > 0.05);
    exclusion[2] = (XNaA > 0.05)  		   && (XCaM4 > 0.05) && (XMgM13  > 0.05) && (XAlM2  > 0.05) && (XAlT1 > 0.05) && (XSiT1 > 0.05);
    exclusion[3] = (XNaA > 0.05)  		   && (XCaM4 > 0.05) && (XFe2M13 > 0.05) && (XAlM2  > 0.05) && (XAlT1 > 0.05) && (XSiT1 > 0.05);
    exclusion[4] = (XVcA > 0.05)  		   && (XCaM4 > 0.05) && (XMgM13  > 0.05) && (XAlM2  > 0.05) && (XAlT1 > 0.05) && (XSiT1 > 0.05);
    exclusion[5] = (XNaA > 0.05)  		   && (XCaM4 > 0.05) && (XMgM13  > 0.05) && (XTiM2  > 0.05) && (XAlT1 > 0.05) && (XSiT1 > 0.05);
    exclusion[6] = (XNaA > 0.05)  		   && (XCaM4 > 0.05) && (XMgM13  > 0.05)   		    && (XAlT1 > 0.05) && (XSiT1 > 0.05);
    exclusion[7] = (XVcA > 0.05) && (XNaM4 > 0.05) && (XCaM4 > 0.05) && (XMgM13  > 0.05) && (XAlM2  > 0.05) && (XAlT1 > 0.05) && (XSiT1 > 0.05);
    
    for (i=0; i<NA; i++) {
      if (!exclusion[i]) {
        if (mask & FIRST)  a[i]  = 0.0;
        if (mask & SECOND) mu[i] = 0.0;
        if (mask & THIRD)  for (j=0; j<NR; j++) dx[i][j] = 0.0;
      }
    }
  }

}

void 
gmixHrn(int mask, double t, double p, double *x, 
  double *gmix, /* Gibbs energy of mixing             BINARY MASK: 0001 */
  double *dx,   /* (pointer to dx[]) d(g)/d(x[])      BINARY MASK: 0010 */
  double **dx2, /* (pointer to dx2[][]) d2(g)/d(x[])2 BINARY MASK: 0100 */
  double ***dx3 /* (pointer to dx3[][][]) d3(g)/d(x[])3 NARY MASK: 1000 */
  )
{
  double *r    = x;
  double k       = 4.0*r[2]/(4.0+r[5]-r[6]);
  double XNaA    = (1.0-r[0]-r[3]-r[6] > 0.0)       	     ? 1.0-r[0]-r[3]-r[6]       	       : DBL_EPSILON;
  double XKA     = (r[0] > 0.0)                     	     ? r[0]		        	       : DBL_EPSILON;
  double XVcA    = (r[3]+r[6] > 0.0)                	     ? r[3]+r[6]	        	       : DBL_EPSILON;
  double XNaM4   = (r[6] > 0.0)                     	     ? r[6]		        	       : DBL_EPSILON;
  double XCaM4   = (1.0-r[6] > 0.0)                 	     ? 1.0-r[6] 	        	       : DBL_EPSILON;
  double XMgM13  = (1.0-k > 0.0)                    	     ? 1.0-k		        	       : DBL_EPSILON;
  double XFe2M13 = (k > 0.0)                        	     ? k		        	       : DBL_EPSILON;
  double XMgM2   = ((1.0+r[5]-r[6])*(1.0-k) > 0.0)  	     ? (1.0+r[5]-r[6])*(1.0-k)/2.0  	       : DBL_EPSILON;
  double XFe2M2  = ((1.0+r[5]-r[6])*k > 0.0)        	     ? (1.0+r[5]-r[6])*k/2.0        	       : DBL_EPSILON;
  double XAlM2   = (r[1]+r[2]+r[3]+2.0*r[6] > 0.0)  	     ? (r[1]+r[2]+r[3]+2.0*r[6])/2.0  	       : DBL_EPSILON;
  double XFe3M2  = (1.0-r[1]-r[2]-r[3]-r[4]-r[5]-r[6] > 0.0) ? (1.0-r[1]-r[2]-r[3]-r[4]-r[5]-r[6])/2.0 : DBL_EPSILON;
  double XTiM2   = (r[4] > 0.0)                              ? r[4]/2.0                                : DBL_EPSILON;
  double XAlT1   = (0.5-(r[3]+r[5]+r[6])/4.0 > 0.0)          ? 0.5-(r[3]+r[5]+r[6])/4.0                : DBL_EPSILON;
  double XSiT1   = (0.5+(r[3]+r[5]+r[6])/4.0 > 0.0)          ? 0.5+(r[3]+r[5]+r[6])/4.0                : DBL_EPSILON;
  
  if (mask & FIRST) {
    *gmix = G;
  }
  
  if(mask & SECOND) {
    dx[0] = DGDR0;
    dx[1] = DGDR1;
    dx[2] = DGDR2;
    dx[3] = DGDR3;
    dx[4] = DGDR4;
    dx[5] = DGDR5;
    dx[6] = DGDR6;
  }

  if(mask & THIRD) {
    double d2gdr2[NR][NR];
    int i, j;

    fillD2GDR2

    for (i=0; i<NR; i++) {
       for (j=0; j<NR; j++) dx2[i][j] = d2gdr2[i][j];
    }
  }
  if (mask & FOURTH) {
    double d3gdr3[NR][NR][NR];
    int i, j, l;

    fillD3GDR3

    for (i=0; i<NR; i++) {
      for (j=0; j<NR; j++) {
        for (l=0; l<NR; l++) dx3[i][j][l] = d3gdr3[i][j][l];
      }
    }
  }

}

void 
hmixHrn(int mask, double t, double p, double *x, 
  double *hmix /* Enthalpy of mixing BINARY MASK: 1 */
  )
{
  double *r    = x;
  double k       = 4.0*r[2]/(4.0+r[5]-r[6]);
  double XNaA    = (1.0-r[0]-r[3]-r[6] > 0.0)       	     ? 1.0-r[0]-r[3]-r[6]       	       : DBL_EPSILON;
  double XKA     = (r[0] > 0.0)                     	     ? r[0]		        	       : DBL_EPSILON;
  double XVcA    = (r[3]+r[6] > 0.0)                	     ? r[3]+r[6]	        	       : DBL_EPSILON;
  double XNaM4   = (r[6] > 0.0)                     	     ? r[6]		        	       : DBL_EPSILON;
  double XCaM4   = (1.0-r[6] > 0.0)                 	     ? 1.0-r[6] 	        	       : DBL_EPSILON;
  double XMgM13  = (1.0-k > 0.0)                    	     ? 1.0-k		        	       : DBL_EPSILON;
  double XFe2M13 = (k > 0.0)                        	     ? k		        	       : DBL_EPSILON;
  double XMgM2   = ((1.0+r[5]-r[6])*(1.0-k) > 0.0)  	     ? (1.0+r[5]-r[6])*(1.0-k)/2.0  	       : DBL_EPSILON;
  double XFe2M2  = ((1.0+r[5]-r[6])*k > 0.0)        	     ? (1.0+r[5]-r[6])*k/2.0        	       : DBL_EPSILON;
  double XAlM2   = (r[1]+r[2]+r[3]+2.0*r[6] > 0.0)  	     ? (r[1]+r[2]+r[3]+2.0*r[6])/2.0  	       : DBL_EPSILON;
  double XFe3M2  = (1.0-r[1]-r[2]-r[3]-r[4]-r[5]-r[6] > 0.0) ? (1.0-r[1]-r[2]-r[3]-r[4]-r[5]-r[6])/2.0 : DBL_EPSILON;
  double XTiM2   = (r[4] > 0.0)                              ? r[4]/2.0                                : DBL_EPSILON;
  double XAlT1   = (0.5-(r[3]+r[5]+r[6])/4.0 > 0.0)          ? 0.5-(r[3]+r[5]+r[6])/4.0                : DBL_EPSILON;
  double XSiT1   = (0.5+(r[3]+r[5]+r[6])/4.0 > 0.0)          ? 0.5+(r[3]+r[5]+r[6])/4.0                : DBL_EPSILON;
  
  *hmix = (G) + t*(S);
}

void 
smixHrn(int mask, double t, double p, double *x, 
  double *smix, /* Entropy of mixing                  BINARY MASK: 001 */
  double *dx,   /* (pointer to dx[]) d(s)/d(x[])      BINARY MASK: 010 */
  double **dx2  /* (pointer to dx2[][]) d2(s)/d(x[])2 BINARY MASK: 100 */
  )
{
  double *r    = x;
  double k       = 4.0*r[2]/(4.0+r[5]-r[6]);
  double XNaA    = (1.0-r[0]-r[3]-r[6] > 0.0)       	     ? 1.0-r[0]-r[3]-r[6]       	       : DBL_EPSILON;
  double XKA     = (r[0] > 0.0)                     	     ? r[0]		        	       : DBL_EPSILON;
  double XVcA    = (r[3]+r[6] > 0.0)                	     ? r[3]+r[6]	        	       : DBL_EPSILON;
  double XNaM4   = (r[6] > 0.0)                     	     ? r[6]		        	       : DBL_EPSILON;
  double XCaM4   = (1.0-r[6] > 0.0)                 	     ? 1.0-r[6] 	        	       : DBL_EPSILON;
  double XMgM13  = (1.0-k > 0.0)                    	     ? 1.0-k		        	       : DBL_EPSILON;
  double XFe2M13 = (k > 0.0)                        	     ? k		        	       : DBL_EPSILON;
  double XMgM2   = ((1.0+r[5]-r[6])*(1.0-k) > 0.0)  	     ? (1.0+r[5]-r[6])*(1.0-k)/2.0  	       : DBL_EPSILON;
  double XFe2M2  = ((1.0+r[5]-r[6])*k > 0.0)        	     ? (1.0+r[5]-r[6])*k/2.0        	       : DBL_EPSILON;
  double XAlM2   = (r[1]+r[2]+r[3]+2.0*r[6] > 0.0)  	     ? (r[1]+r[2]+r[3]+2.0*r[6])/2.0  	       : DBL_EPSILON;
  double XFe3M2  = (1.0-r[1]-r[2]-r[3]-r[4]-r[5]-r[6] > 0.0) ? (1.0-r[1]-r[2]-r[3]-r[4]-r[5]-r[6])/2.0 : DBL_EPSILON;
  double XTiM2   = (r[4] > 0.0)                              ? r[4]/2.0                                : DBL_EPSILON;
  double XAlT1   = (0.5-(r[3]+r[5]+r[6])/4.0 > 0.0)          ? 0.5-(r[3]+r[5]+r[6])/4.0                : DBL_EPSILON;
  double XSiT1   = (0.5+(r[3]+r[5]+r[6])/4.0 > 0.0)          ? 0.5+(r[3]+r[5]+r[6])/4.0                : DBL_EPSILON;

  if (mask & FIRST) {
    *smix = S; 
  }
  
  if(mask & SECOND) {
    double d2gdrdt[NR];
    int i;

    fillD2GDRDT

    for (i=0; i<NR; i++) dx[i] = - d2gdrdt[i];
  }

  if(mask & THIRD) {
    double d3gdr2dt[NR][NR];
    int i, j;

    fillD3GDR2DT 

    for (i=0; i<NR; i++) {
       for (j=0; j<NR; j++) dx2[i][j] = - d3gdr2dt[i][j];
    }
  }

}

void 
cpmixHrn(int mask, double t, double p, double *x, 
  double *cpmix, /* Heat capacity of mixing               BINARY MASK: 001 */
  double *dt,    /* d(cp)/d(t)                            BINARY MASK: 010 */
  double *dx     /* d(cp)/d(x[])d(t)                      BINARY MASK: 100 */
  )
{
  double d2gdt2 = D2GDT2;

  if (mask & FIRST) {
    *cpmix = - t*d2gdt2;
  }

  if(mask & SECOND) {
    double d3gdt3   = D3GDT3;

    *dt = -t*d3gdt3 - d2gdt2;
  }

  if(mask & THIRD) {
    double d3gdrdt2[NR];
    int i;

    fillD3GDRDT2

    for (i=0; i<NR; i++) dx[i] = -t*d3gdrdt2[i];
  }

}

void 
vmixHrn(int mask, double t, double p, double *x, 
  double *vmix, /* Volume of mixing                BINARY MASK: 0000000001 */
  double *dx,   /* (pointer to dx[]) d(v)/d(x[])   BINARY MASK: 0000000010 */
  double **dx2, /* (point to dx2[][]) d(v)/d(x[])2 BINARY MASK: 0000000100 */
  double *dt,   /* d(v)/d(t)                       BINARY MASK: 0000001000 */
  double *dp,   /* d(v)/d(p)                       BINARY MASK: 0000010000 */
  double *dt2,  /* d2(v)/d(t)2                     BINARY MASK: 0000100000 */
  double *dtdp, /* d2(v)/d(t)d(p)                  BINARY MASK: 0001000000 */
  double *dp2,  /* d2(v)/d(p)2                     BINARY MASK: 0010000000 */
  double *dxdt, /* d2(v)/d(x[])d(t)                BINARY MASK: 0100000000 */
  double *dxdp  /* d2(v)/d(x[])d(p)                BINARY MASK: 1000000000 */
  )
{
  if (mask & FIRST) {
    *vmix = DGDP;
  }

  if(mask & SECOND) {
    double d2gdrdp[NR];
    int i;
    
    fillD2GDRDP

    for (i=0; i<NR; i++) dx[i] = d2gdrdp[i]; 
  }

  if(mask & THIRD) {
    double d3gdr2dp[NR][NR];
    int i, j;

    fillD3GDR2DP

    for (i=0; i<NR; i++) {
       for (j=0; j<NR; j++) dx2[i][j] = d3gdr2dp[i][j];
    }
  }

  if(mask & FOURTH) {
    *dt = D2GDTDP;
  }

  if(mask & FIFTH) {
    *dp = D2GDP2;
  }

  if(mask & SIXTH) {
    *dt2 = D3GDT2DP;
  }

  if(mask & SEVENTH) {
    *dtdp = D3GDTDP2;
  }

  if(mask & EIGHTH) {
    *dp2 = D3GDP3;
  }

  if(mask & NINTH) {
    double d3gdrdtdp[NR];
    int i;

    fillD3GDRDTDP

    for (i=0; i<NR; i++) dxdt[i] = d3gdrdtdp[i];
  }

  if(mask & TENTH) {
    double d3gdrdp2[NR];
    int i;

    fillD3GDRDP2

    for (i=0; i<NR; i++) dxdp[i] = d3gdrdp2[i];
  }

}

/* end of file HORNBLENDE.C */
