#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>

/*
 * H2O-CO2 model of Duan, Z, Zhang, Z (2006)
 * Equation of state of the H2O, CO2, and H2O-CO2 systems up to 10 GPa and 2573.15 K:
 * Molecular dynamics simulations with ab initio potential surface
 * Geochimica et Cosmochimica Acta, 70, 2311-2324
*/

/* pure EOSterms for 0 to 0.2 GPa */
static const double H2OLa1  =  4.38269941E-02; 
static const double H2OLa2  = -1.68244362E-01; 
static const double H2OLa3  = -2.36923373E-01; 
static const double H2OLa4  =  1.13027462E-02; 
static const double H2OLa5  = -7.67764181E-02; 
static const double H2OLa6  =  9.71820593E-02; 
static const double H2OLa7  =  6.62674916E-05; 
static const double H2OLa8  =  1.06637349E-03; 
static const double H2OLa9  = -1.23265258E-03; 
static const double H2OLa10 = -8.93953948E-06; 
static const double H2OLa11 = -3.88124606E-05; 
static const double H2OLa12 =  5.61510206E-05; 
static const double H2OLa   =  7.51274488E-03; 
static const double H2OLb   =  2.51598931E+00; 
static const double H2OLc   =  3.94000000E-02; 

static const double CO2La1  =  1.14400435E-01; 
static const double CO2La2  = -9.38526684E-01;
static const double CO2La3  =  7.21857006E-01;
static const double CO2La4  =  8.81072902E-03;
static const double CO2La5  =  6.36473911E-02;
static const double CO2La6  = -7.70822213E-02;
static const double CO2La7  =  9.01506064E-04;
static const double CO2La8  = -6.81834166E-03;
static const double CO2La9  =  7.32364258E-03;
static const double CO2La10 = -1.10288237E-04;
static const double CO2La11 =  1.26524193E-03;
static const double CO2La12 = -1.49730823E-03;
static const double CO2La   =  7.81940730E-03;
static const double CO2Lb   = -4.22918013E+00;
static const double CO2Lc   =  1.58500000E-01;

/* pure EOS terms for 0.2 to 10 GPa */
static const double H2OHa1  =  4.68071541E-02;  
static const double H2OHa2  = -2.81275941E-01;  
static const double H2OHa3  = -2.43926365E-01;  
static const double H2OHa4  =  1.10016958E-02;  
static const double H2OHa5  = -3.86603525E-02;  
static const double H2OHa6  =  9.30095461E-02;  
static const double H2OHa7  = -1.15747171E-05;  
static const double H2OHa8  =  4.19873848E-04;  
static const double H2OHa9  = -5.82739501E-04;  
static const double H2OHa10 =  1.00936000E-06;  
static const double H2OHa11 = -1.01713593E-05;  
static const double H2OHa12 =  1.63934213E-05;  
static const double H2OHa   = -4.49505919E-02;  
static const double H2OHb   = -3.15028174E-01;  
static const double H2OHc   =  1.25000000E-02; 

static const double CO2Ha1  =  5.72573440E-03;
static const double CO2Ha2  =  7.94836769E+00;
static const double CO2Ha3  = -3.84236281E+01;
static const double CO2Ha4  =  3.71600369E-02;
static const double CO2Ha5  = -1.92888994E+00;
static const double CO2Ha6  =  6.64254770E+00;
static const double CO2Ha7  = -7.02203950E-06;
static const double CO2Ha8  =  1.77093234E-02;
static const double CO2Ha9  = -4.81892026E-02;
static const double CO2Ha10 =  3.88344869E-06;
static const double CO2Ha11 = -5.54833167E-04;
static const double CO2Ha12 =  1.70489748E-03;
static const double CO2Ha   = -4.13039220E-01;
static const double CO2Hb   = -8.47988634E+00;
static const double CO2Hc   =  2.80000000E-02;

/* H2O, critical constants, K, bars, J/bar */

static const double H2OTc = 647.25;
static const double H2OPc = 221.19;
#define H2OVc (8.314467*H2OTc/H2OPc)

/* CO2 */

static const double CO2Tc = 304.1282;
static const double CO2Pc = 73.773;
#define CO2Vc (8.314467*CO2Tc/CO2Pc)

#define H2O 0
#define CO2 1

static const double idealCoeff[13][2] = {
  {  3.10409601236035e+01, -0.18188731e+01 },
  { -3.91422080460869e+01,  0.12903022e+02 },
  {  3.79695277233575e+01, -0.96634864e+01 },
  { -2.18374910952284e+01,  0.42251879e+01 },
  {  7.42251494566339e+00, -0.10421640e+01 },
  { -1.38178929609470e+00,  0.12683515e+00 },
  {  1.08807067571454e-01, -0.49939675e-02 },
  { -1.20771176848589e+01,  0.24950242e+01 },
  {  3.39105078851732e+00, -0.82723750e+00 },
  { -5.84520979955060e-01,  0.15372481e+00 },
  {  5.89930846488082e-02, -0.15861243e-01 },
  { -3.12970001415882e-03,  0.86017150e-03 },
  {  6.57460740981757e-05, -0.19222165e-04 }
};

static double powSum(double a, double fa, double b, double fb) {
  double sum = 0.0;
  sum += (a >= 0.0) ? fa*pow(a, 1.0/3.0) : -fa*pow(-a, 1.0/3.0);
  sum += (b >= 0.0) ? fb*pow(b, 1.0/3.0) : -fb*pow(-b, 1.0/3.0);
  return (sum >= 0.0) ? pow(sum/(fa+fb), 3.0) : -pow(-sum/(fa+fb), 3.0);
}

static void BVcAndDerivative(int useLowPcoeff, double t, double x[2], double *bv, double bvPrime[2]) {
  double bEnd[2];
  double H2OTr = t/H2OTc;
  double CO2Tr = t/CO2Tc;
  double k1 = 0.0;

  if (useLowPcoeff) {
    bEnd[H2O] = H2OLa1 + H2OLa2/H2OTr/H2OTr + H2OLa3/H2OTr/H2OTr/H2OTr;
    bEnd[CO2] = CO2La1 + CO2La2/CO2Tr/CO2Tr + CO2La3/CO2Tr/CO2Tr/CO2Tr;
    k1 = 3.131 - 5.0624e-3*t + 1.8641e-6*t*t - 31.409/t;
  } else {
    bEnd[H2O] = H2OHa1 + H2OHa2/H2OTr/H2OTr + H2OHa3/H2OTr/H2OTr/H2OTr;
    bEnd[CO2] = CO2Ha1 + CO2Ha2/CO2Tr/CO2Tr + CO2Ha3/CO2Tr/CO2Tr/CO2Tr;
    k1 = 9.034 - 7.9212e-3*t + 2.3285e-6*t*t - 2.4221e3/t;
  }
  
  if ((x[H2O] == 0.0) && (x[CO2] == 0.0)) {
    *bv = 0.0;
    bvPrime[H2O] = 0.0;
    bvPrime[CO2] = 0.0;
    
  } else if ((x[H2O] == 1.0) && (x[CO2] == 0.0)) {
    *bv = bEnd[H2O]*H2OVc;
    bvPrime[H2O] = 2.0*bEnd[H2O]*H2OVc;
    bvPrime[CO2] = 2.0*powSum(bEnd[H2O], 1.0, bEnd[CO2], 1.0)*k1*powSum(H2OVc, 1.0, CO2Vc, 1.0);
    
  } else if ((x[H2O] == 0.0) && (x[CO2] == 1.0)) {
    *bv = bEnd[CO2]*CO2Vc;
    bvPrime[H2O] = 2.0*powSum(bEnd[H2O], 1.0, bEnd[CO2], 1.0)*k1*powSum(H2OVc, 1.0, CO2Vc, 1.0);
    bvPrime[CO2] = 2.0*bEnd[CO2]*CO2Vc;
    
  } else {
    *bv  = 0.0;
    *bv += bEnd[H2O]*H2OVc*x[H2O]*x[H2O];
    *bv += 2.0*powSum(bEnd[H2O], 1.0, bEnd[CO2], 1.0)*k1*powSum(H2OVc, 1.0, CO2Vc, 1.0)*x[H2O]*x[CO2];
    *bv += bEnd[CO2]*CO2Vc*x[CO2]*x[CO2];
  
    bvPrime[H2O]  = 0.0;
    bvPrime[H2O] += 2.0*bEnd[H2O]*H2OVc*x[H2O];
    bvPrime[H2O] += 2.0*powSum(bEnd[H2O], 1.0, bEnd[CO2], 1.0)*k1*powSum(H2OVc, 1.0, CO2Vc, 1.0)*x[CO2];

    bvPrime[CO2]  = 0.0;
    bvPrime[CO2] += 2.0*powSum(bEnd[H2O], 1.0, bEnd[CO2], 1.0)*k1*powSum(H2OVc, 1.0, CO2Vc, 1.0)*x[H2O];
    bvPrime[CO2] += 2.0*bEnd[CO2]*CO2Vc*x[CO2];
  }
  
  return;
}

static void CVcAndDerivative(int useLowPcoeff, double t, double x[2], double *cv, double cvPrime[2]) {
  double cEnd[2];
  double H2OTr = t/H2OTc;
  double CO2Tr = t/CO2Tc;
  double k2 = 0.0;

  if (useLowPcoeff) {
    cEnd[H2O] = H2OLa4 + H2OLa5/H2OTr/H2OTr + H2OLa6/H2OTr/H2OTr/H2OTr;
    cEnd[CO2] = CO2La4 + CO2La5/CO2Tr/CO2Tr + CO2La6/CO2Tr/CO2Tr/CO2Tr;
    k2 = -46.646 + 4.2877e-2*t - 1.0892e-5*t*t + 1.5782e4/t;
  } else {
    cEnd[H2O] = H2OHa4 + H2OHa5/H2OTr/H2OTr + H2OHa6/H2OTr/H2OTr/H2OTr;
    cEnd[CO2] = CO2Ha4 + CO2Ha5/CO2Tr/CO2Tr + CO2Ha6/CO2Tr/CO2Tr/CO2Tr;
    k2 = -1.068 + 1.8756e-3*t - 4.9371e-7*t*t + 6.6180e2/t;
  }
  
  if ((x[H2O] == 0.0) && (x[CO2] == 0.0)) {
    *cv = 0.0;
    cvPrime[H2O] = 0.0;
    cvPrime[CO2] = 0.0;
    
  } else if ((x[H2O] == 1.0) && (x[CO2] == 0.0)) {
    *cv = cEnd[H2O]*H2OVc*H2OVc;
    cvPrime[H2O] = 3.0*cEnd[H2O]*H2OVc*H2OVc;
    cvPrime[CO2] = 3.0*powSum(cEnd[H2O], 2.0, cEnd[CO2], 1.0)*k2*pow(powSum(H2OVc, 2.0, CO2Vc, 1.0), 2.0);
    
  } else if ((x[H2O] == 0.0) && (x[CO2] == 1.0)) {
    *cv = cEnd[CO2]*CO2Vc*CO2Vc;
    cvPrime[H2O] = 3.0*powSum(cEnd[H2O], 1.0, cEnd[CO2], 2.0)*k2*pow(powSum(H2OVc, 1.0, CO2Vc, 2.0), 2.0);
    cvPrime[CO2] = 3.0*cEnd[CO2]*CO2Vc*CO2Vc;
    
  } else {    
    *cv  = 0.0;
    *cv += cEnd[H2O]*H2OVc*H2OVc*x[H2O]*x[H2O]*x[H2O];
    *cv += 3.0*powSum(cEnd[H2O], 2.0, cEnd[CO2], 1.0)*k2*pow( powSum(H2OVc, 2.0, CO2Vc, 1.0), 2.0)*x[H2O]*x[H2O]*x[CO2];
    *cv += 3.0*powSum(cEnd[H2O], 1.0, cEnd[CO2], 2.0)*k2*pow( powSum(H2OVc, 1.0, CO2Vc, 2.0), 2.0)*x[H2O]*x[CO2]*x[CO2];      
    *cv += cEnd[CO2]*CO2Vc*CO2Vc*x[CO2]*x[CO2]*x[CO2];
  
    cvPrime[H2O]  = 0.0;
    cvPrime[H2O] += 3.0*cEnd[H2O]*H2OVc*H2OVc*x[H2O]*x[H2O];
    cvPrime[H2O] += 6.0*powSum(cEnd[H2O], 2.0, cEnd[CO2], 1.0)*k2*pow(powSum(H2OVc, 2.0, CO2Vc, 1.0), 2.0)*x[H2O]*x[CO2];
    cvPrime[H2O] += 3.0*powSum(cEnd[H2O], 1.0, cEnd[CO2], 2.0)*k2*pow(powSum(H2OVc, 1.0, CO2Vc, 2.0), 2.0)*x[CO2]*x[CO2];

    cvPrime[CO2]  = 0.0;
    cvPrime[CO2] += 3.0*powSum(cEnd[H2O], 2.0, cEnd[CO2], 1.0)*k2*pow(powSum(H2OVc, 2.0, CO2Vc, 1.0), 2.0)*x[H2O]*x[H2O];
    cvPrime[CO2] += 6.0*powSum(cEnd[H2O], 1.0, cEnd[CO2], 2.0)*k2*pow(powSum(H2OVc, 1.0, CO2Vc, 2.0), 2.0)*x[H2O]*x[CO2];
    cvPrime[CO2] += 3.0*cEnd[CO2]*CO2Vc*CO2Vc*x[CO2]*x[CO2];
  }
  
  return;
}

static void DVcAndDerivative(int useLowPcoeff, double t, double x[2], double *dv, double dvPrime[2]) {
  double dEnd[2];
  double H2OTr = t/H2OTc;
  double CO2Tr = t/CO2Tc;

  if (useLowPcoeff) {
    dEnd[H2O] = H2OLa7 + H2OLa8/H2OTr/H2OTr + H2OLa9/H2OTr/H2OTr/H2OTr;
    dEnd[CO2] = CO2La7 + CO2La8/CO2Tr/CO2Tr + CO2La9/CO2Tr/CO2Tr/CO2Tr;
  } else {
    dEnd[H2O] = H2OHa7 + H2OHa8/H2OTr/H2OTr + H2OHa9/H2OTr/H2OTr/H2OTr;
    dEnd[CO2] = CO2Ha7 + CO2Ha8/CO2Tr/CO2Tr + CO2Ha9/CO2Tr/CO2Tr/CO2Tr;
  }
  
  if ((x[H2O] == 0.0) && (x[CO2] == 0.0)) {
    *dv = 0.0;
    dvPrime[H2O] = 0.0;
    dvPrime[CO2] = 0.0;
    
  } else if ((x[H2O] == 1.0) && (x[CO2] == 0.0)) {
    *dv = dEnd[H2O]*H2OVc*H2OVc*H2OVc*H2OVc;
    dvPrime[H2O] = 5.0*dEnd[H2O]*H2OVc*H2OVc*H2OVc*H2OVc;
    dvPrime[CO2] = 5.0*powSum(dEnd[H2O], 1.0, dEnd[CO2], 4.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 4.0), 4.0);
    
  } else if ((x[H2O] == 0.0) && (x[CO2] == 1.0)) {
    *dv = dEnd[CO2]*CO2Vc*CO2Vc*CO2Vc*CO2Vc;
    dvPrime[H2O] = 5.0*powSum(dEnd[H2O], 4.0, dEnd[CO2], 1.0)*pow(powSum(H2OVc, 4.0, CO2Vc, 1.0), 4.0);
    dvPrime[CO2] = 5.0*dEnd[CO2]*CO2Vc*CO2Vc*CO2Vc*CO2Vc;
    
  } else {    
    *dv  = 0.0;
    *dv += dEnd[H2O]*H2OVc*H2OVc*H2OVc*H2OVc*x[H2O]*x[H2O]*x[H2O]*x[H2O]*x[H2O];
    *dv +=  5.0*powSum(dEnd[H2O], 4.0, dEnd[CO2], 1.0)*pow(powSum(H2OVc, 4.0, CO2Vc, 1.0), 4.0)*x[H2O]*x[H2O]*x[H2O]*x[H2O]*x[CO2];
    *dv += 10.0*powSum(dEnd[H2O], 3.0, dEnd[CO2], 2.0)*pow(powSum(H2OVc, 3.0, CO2Vc, 2.0), 4.0)*x[H2O]*x[H2O]*x[H2O]*x[CO2]*x[CO2];
    *dv += 10.0*powSum(dEnd[H2O], 2.0, dEnd[CO2], 3.0)*pow(powSum(H2OVc, 2.0, CO2Vc, 3.0), 4.0)*x[H2O]*x[H2O]*x[CO2]*x[CO2]*x[CO2];
    *dv +=  5.0*powSum(dEnd[H2O], 1.0, dEnd[CO2], 4.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 4.0), 4.0)*x[H2O]*x[CO2]*x[CO2]*x[CO2]*x[CO2];
    *dv += dEnd[CO2]*CO2Vc*CO2Vc*CO2Vc*CO2Vc*x[CO2]*x[CO2]*x[CO2]*x[CO2]*x[CO2];
  
    dvPrime[H2O]  =  0.0;
    dvPrime[H2O] +=  5.0*dEnd[H2O]*H2OVc*H2OVc*H2OVc*H2OVc*x[H2O]*x[H2O]*x[H2O]*x[H2O];
    dvPrime[H2O] += 20.0*powSum(dEnd[H2O], 4.0, dEnd[CO2], 1.0)*pow(powSum(H2OVc, 4.0, CO2Vc, 1.0), 4.0)*x[H2O]*x[H2O]*x[H2O]*x[CO2];
    dvPrime[H2O] += 30.0*powSum(dEnd[H2O], 3.0, dEnd[CO2], 2.0)*pow(powSum(H2OVc, 3.0, CO2Vc, 2.0), 4.0)*x[H2O]*x[H2O]*x[CO2]*x[CO2];
    dvPrime[H2O] += 20.0*powSum(dEnd[H2O], 2.0, dEnd[CO2], 3.0)*pow(powSum(H2OVc, 2.0, CO2Vc, 3.0), 4.0)*x[H2O]*x[CO2]*x[CO2]*x[CO2];
    dvPrime[H2O] +=  5.0*powSum(dEnd[H2O], 1.0, dEnd[CO2], 4.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 4.0), 4.0)*x[CO2]*x[CO2]*x[CO2]*x[CO2];

    dvPrime[CO2]  =  0.0;
    dvPrime[CO2] +=  5.0*powSum(dEnd[H2O], 4.0, dEnd[CO2], 1.0)*pow(powSum(H2OVc, 4.0, CO2Vc, 1.0), 4.0)*x[H2O]*x[H2O]*x[H2O]*x[H2O];
    dvPrime[CO2] += 20.0*powSum(dEnd[H2O], 3.0, dEnd[CO2], 2.0)*pow(powSum(H2OVc, 3.0, CO2Vc, 2.0), 4.0)*x[H2O]*x[H2O]*x[H2O]*x[CO2];
    dvPrime[CO2] += 30.0*powSum(dEnd[H2O], 2.0, dEnd[CO2], 3.0)*pow(powSum(H2OVc, 2.0, CO2Vc, 3.0), 4.0)*x[H2O]*x[H2O]*x[CO2]*x[CO2];
    dvPrime[CO2] += 20.0*powSum(dEnd[H2O], 1.0, dEnd[CO2], 4.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 4.0), 4.0)*x[H2O]*x[CO2]*x[CO2]*x[CO2];
    dvPrime[CO2] += 5.0*dEnd[CO2]*CO2Vc*CO2Vc*CO2Vc*CO2Vc*x[CO2]*x[CO2]*x[CO2]*x[CO2];
  }
  
  return;
}

static void EVcAndDerivative(int useLowPcoeff, double t, double x[2], double *ev, double evPrime[2]) {
  double eEnd[2];
  double H2OTr = t/H2OTc;
  double CO2Tr = t/CO2Tc;

  if (useLowPcoeff) {
    eEnd[H2O] = H2OLa10 + H2OLa11/H2OTr/H2OTr + H2OLa12/H2OTr/H2OTr/H2OTr;
    eEnd[CO2] = CO2La10 + CO2La11/CO2Tr/CO2Tr + CO2La12/CO2Tr/CO2Tr/CO2Tr;
  } else {
    eEnd[H2O] = H2OHa10 + H2OHa11/H2OTr/H2OTr + H2OHa12/H2OTr/H2OTr/H2OTr;
    eEnd[CO2] = CO2Ha10 + CO2Ha11/CO2Tr/CO2Tr + CO2Ha12/CO2Tr/CO2Tr/CO2Tr;
  }
  
  if ((x[H2O] == 0.0) && (x[CO2] == 0.0)) {
    *ev = 0.0;
    evPrime[H2O] = 0.0;
    evPrime[CO2] = 0.0;
    
  } else if ((x[H2O] == 1.0) && (x[CO2] == 0.0)) {
    *ev = eEnd[H2O]*H2OVc*H2OVc*H2OVc*H2OVc*H2OVc;
    evPrime[H2O] = 6.0*eEnd[H2O]*H2OVc*H2OVc*H2OVc*H2OVc*H2OVc;
    evPrime[CO2] = 6.0*powSum(eEnd[H2O], 5.0, eEnd[CO2], 1.0)*pow(powSum(H2OVc, 5.0, CO2Vc, 1.0), 5.0);
    
  } else if ((x[H2O] == 0.0) && (x[CO2] == 1.0)) {
    *ev = eEnd[CO2]*CO2Vc*CO2Vc*CO2Vc*CO2Vc*CO2Vc;
    evPrime[H2O] = 6.0*powSum(eEnd[H2O], 1.0, eEnd[CO2], 5.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 5.0), 5.0);
    evPrime[CO2] = 6.0*eEnd[CO2]*CO2Vc*CO2Vc*CO2Vc*CO2Vc*CO2Vc;
    
  } else {    
    *ev  = 0.0;
    *ev += eEnd[H2O]*H2OVc*H2OVc*H2OVc*H2OVc*H2OVc*x[H2O]*x[H2O]*x[H2O]*x[H2O]*x[H2O]*x[H2O];
    *ev +=  6.0*powSum(eEnd[H2O], 5.0, eEnd[CO2], 1.0)*pow(powSum(H2OVc, 5.0, CO2Vc, 1.0), 5.0)*x[H2O]*x[H2O]*x[H2O]*x[H2O]*x[H2O]*x[CO2];
    *ev += 15.0*powSum(eEnd[H2O], 4.0, eEnd[CO2], 2.0)*pow(powSum(H2OVc, 4.0, CO2Vc, 2.0), 5.0)*x[H2O]*x[H2O]*x[H2O]*x[H2O]*x[CO2]*x[CO2];
    *ev += 20.0*powSum(eEnd[H2O], 3.0, eEnd[CO2], 3.0)*pow(powSum(H2OVc, 3.0, CO2Vc, 3.0), 5.0)*x[H2O]*x[H2O]*x[H2O]*x[CO2]*x[CO2]*x[CO2];
    *ev += 15.0*powSum(eEnd[H2O], 2.0, eEnd[CO2], 4.0)*pow(powSum(H2OVc, 2.0, CO2Vc, 4.0), 5.0)*x[H2O]*x[H2O]*x[CO2]*x[CO2]*x[CO2]*x[CO2];
    *ev +=  6.0*powSum(eEnd[H2O], 1.0, eEnd[CO2], 5.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 5.0), 5.0)*x[H2O]*x[CO2]*x[CO2]*x[CO2]*x[CO2]*x[CO2];
    *ev += eEnd[CO2]*CO2Vc*CO2Vc*CO2Vc*CO2Vc*CO2Vc*x[CO2]*x[CO2]*x[CO2]*x[CO2]*x[CO2]*x[CO2];
  
    evPrime[H2O]  =  0.0;
    evPrime[H2O] +=  6.0*eEnd[H2O]*H2OVc*H2OVc*H2OVc*H2OVc*H2OVc*x[H2O]*x[H2O]*x[H2O]*x[H2O]*x[H2O];
    evPrime[H2O] += 30.0*powSum(eEnd[H2O], 5.0, eEnd[CO2], 1.0)*pow(powSum(H2OVc, 5.0, CO2Vc, 1.0), 5.0)*x[H2O]*x[H2O]*x[H2O]*x[H2O]*x[CO2];
    evPrime[H2O] += 60.0*powSum(eEnd[H2O], 4.0, eEnd[CO2], 2.0)*pow(powSum(H2OVc, 4.0, CO2Vc, 2.0), 5.0)*x[H2O]*x[H2O]*x[H2O]*x[CO2]*x[CO2];
    evPrime[H2O] += 60.0*powSum(eEnd[H2O], 3.0, eEnd[CO2], 3.0)*pow(powSum(H2OVc, 3.0, CO2Vc, 3.0), 5.0)*x[H2O]*x[H2O]*x[CO2]*x[CO2]*x[CO2];
    evPrime[H2O] += 30.0*powSum(eEnd[H2O], 2.0, eEnd[CO2], 4.0)*pow(powSum(H2OVc, 2.0, CO2Vc, 4.0), 5.0)*x[H2O]*x[CO2]*x[CO2]*x[CO2]*x[CO2];
    evPrime[H2O] +=  6.0*powSum(eEnd[H2O], 1.0, eEnd[CO2], 5.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 5.0), 5.0)*x[CO2]*x[CO2]*x[CO2]*x[CO2]*x[CO2];;

    evPrime[CO2]  =  0.0;
    evPrime[CO2] +=  6.0*powSum(eEnd[H2O], 5.0, eEnd[CO2], 1.0)*pow(powSum(H2OVc, 5.0, CO2Vc, 1.0), 5.0)*x[H2O]*x[H2O]*x[H2O]*x[H2O]*x[H2O];
    evPrime[CO2] += 30.0*powSum(eEnd[H2O], 4.0, eEnd[CO2], 2.0)*pow(powSum(H2OVc, 4.0, CO2Vc, 2.0), 5.0)*x[H2O]*x[H2O]*x[H2O]*x[H2O]*x[CO2];
    evPrime[CO2] += 60.0*powSum(eEnd[H2O], 3.0, eEnd[CO2], 3.0)*pow(powSum(H2OVc, 3.0, CO2Vc, 3.0), 5.0)*x[H2O]*x[H2O]*x[H2O]*x[CO2]*x[CO2];
    evPrime[CO2] += 60.0*powSum(eEnd[H2O], 2.0, eEnd[CO2], 4.0)*pow(powSum(H2OVc, 2.0, CO2Vc, 4.0), 5.0)*x[H2O]*x[H2O]*x[CO2]*x[CO2]*x[CO2];
    evPrime[CO2] += 30.0*powSum(eEnd[H2O], 1.0, eEnd[CO2], 5.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 5.0), 5.0)*x[H2O]*x[CO2]*x[CO2]*x[CO2]*x[CO2];
    evPrime[CO2] +=  6.0*eEnd[CO2]*CO2Vc*CO2Vc*CO2Vc*CO2Vc*CO2Vc*x[CO2]*x[CO2]*x[CO2]*x[CO2]*x[CO2];
  }
  
  return;
}

static void FVcAndDerivative(int useLowPcoeff, double t, double x[2], double *fv, double fvPrime[2]) {
  double fEnd[2];
  double H2OTr = t/H2OTc;
  double CO2Tr = t/CO2Tc;

  if (useLowPcoeff) {
    fEnd[H2O] = H2OLa/H2OTr/H2OTr/H2OTr;
    fEnd[CO2] = CO2La/CO2Tr/CO2Tr/CO2Tr;
  } else {
    fEnd[H2O] = H2OHa/H2OTr/H2OTr/H2OTr;
    fEnd[CO2] = CO2Ha/CO2Tr/CO2Tr/CO2Tr;
  }
  
  if ((x[H2O] == 0.0) && (x[CO2] == 0.0)) {
    *fv = 0.0;
    fvPrime[H2O] = 0.0;
    fvPrime[CO2] = 0.0;
    
  } else if ((x[H2O] == 1.0) && (x[CO2] == 0.0)) {
    *fv = fEnd[H2O]*H2OVc*H2OVc;
    fvPrime[H2O] = 2.0*fEnd[H2O]*H2OVc*H2OVc;
    fvPrime[CO2] = 2.0*powSum(fEnd[H2O], 1.0, fEnd[CO2], 1.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 1.0), 2.0);
    
  } else if ((x[H2O] == 0.0) && (x[CO2] == 1.0)) {
    *fv = fEnd[CO2]*CO2Vc*CO2Vc;
    fvPrime[H2O] = 2.0*powSum(fEnd[H2O], 1.0, fEnd[CO2], 1.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 1.0), 2.0);
    fvPrime[CO2] = 2.0*fEnd[CO2]*CO2Vc*CO2Vc;
    
  } else {
    *fv  = 0.0;
    *fv += fEnd[H2O]*H2OVc*H2OVc*x[H2O]*x[H2O];
    *fv += 2.0*powSum(fEnd[H2O], 1.0, fEnd[CO2], 1.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 1.0), 2.0)*x[H2O]*x[CO2];
    *fv += fEnd[CO2]*CO2Vc*CO2Vc*x[CO2]*x[CO2];
  
    fvPrime[H2O]  = 0.0;
    fvPrime[H2O] += 2.0*fEnd[H2O]*H2OVc*H2OVc*x[H2O];
    fvPrime[H2O] += 2.0*powSum(fEnd[H2O], 1.0, fEnd[CO2], 1.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 1.0), 2.0)*x[CO2];

    fvPrime[CO2]  = 0.0;
    fvPrime[CO2] += 2.0*powSum(fEnd[H2O], 1.0, fEnd[CO2], 1.0)*pow(powSum(H2OVc, 1.0, CO2Vc, 1.0), 2.0)*x[H2O];
    fvPrime[CO2] += 2.0*fEnd[CO2]*CO2Vc*CO2Vc*x[CO2];
  }
  
  return;
}

static void BetaAndDerivative(int useLowPcoeff, double t, double x[2], double *beta, double betaPrime[2]) {
  double betaEnd[2];

  if (useLowPcoeff) {
    betaEnd[H2O] = H2OLb;
    betaEnd[CO2] = CO2Lb;
  } else {
    betaEnd[H2O] = H2OHb;
    betaEnd[CO2] = CO2Hb;
  }
  
  *beta  = betaEnd[H2O]*x[H2O] + betaEnd[CO2]*x[CO2];
  
  betaPrime[H2O]  = betaEnd[H2O];
  betaPrime[CO2]  = betaEnd[CO2];
  
  return;
}

static void GammaVcAndDerivative(int useLowPcoeff, double t, double x[2], double *gammav, double gammavPrime[2]) {
  double gammaEnd[2];
  double k3 = 0.0;

  if (useLowPcoeff) {
    gammaEnd[H2O] = H2OLc;
    gammaEnd[CO2] = CO2Lc;
    k3 = 0.9;
  } else {
    gammaEnd[H2O] = H2OHc;
    gammaEnd[CO2] = CO2Hc;
    k3 = 1.0;
  }
  
  if ((x[H2O] == 0.0) && (x[CO2] == 0.0)) {
    *gammav = 0.0;
    gammavPrime[H2O] = 0.0;
    gammavPrime[CO2] = 0.0;
    
  } else if ((x[H2O] == 1.0) && (x[CO2] == 0.0)) {
    *gammav = gammaEnd[H2O]*H2OVc*H2OVc;
    gammavPrime[H2O] = 3.0*gammaEnd[H2O]*H2OVc*H2OVc;
    gammavPrime[CO2] = 3.0*powSum(gammaEnd[H2O], 2.0, gammaEnd[CO2], 1.0)*k3*pow(powSum(H2OVc, 2.0, CO2Vc, 1.0), 2.0);
    
  } else if ((x[H2O] == 0.0) && (x[CO2] == 1.0)) {
    *gammav = gammaEnd[CO2]*CO2Vc*CO2Vc;
    gammavPrime[H2O] = 3.0*powSum(gammaEnd[H2O], 1.0, gammaEnd[CO2], 2.0)*k3*pow(powSum(H2OVc, 1.0, CO2Vc, 2.0), 2.0);
    gammavPrime[CO2] = 3.0*gammaEnd[CO2]*CO2Vc*CO2Vc;
    
  } else {
    *gammav  = 0.0;
    *gammav += gammaEnd[H2O]*H2OVc*H2OVc*x[H2O]*x[H2O]*x[H2O];
    *gammav += 3.0*powSum(gammaEnd[H2O], 2.0, gammaEnd[CO2], 1.0)*k3*pow(powSum(H2OVc, 2.0, CO2Vc, 1.0), 2.0)*x[H2O]*x[H2O]*x[CO2];
    *gammav += 3.0*powSum(gammaEnd[H2O], 1.0, gammaEnd[CO2], 2.0)*k3*pow(powSum(H2OVc, 1.0, CO2Vc, 2.0), 2.0)*x[H2O]*x[CO2]*x[CO2];      
    *gammav += gammaEnd[CO2]*CO2Vc*CO2Vc*x[CO2]*x[CO2]*x[CO2];
  
    gammavPrime[H2O]  = 0.0;
    gammavPrime[H2O] += 3.0*gammaEnd[H2O]*H2OVc*H2OVc*x[H2O]*x[H2O];
    gammavPrime[H2O] += 6.0*powSum(gammaEnd[H2O], 2.0, gammaEnd[CO2], 1.0)*k3*pow(powSum(H2OVc, 2.0, CO2Vc, 1.0), 2.0)*x[H2O]*x[CO2];
    gammavPrime[H2O] += 3.0*powSum(gammaEnd[H2O], 1.0, gammaEnd[CO2], 2.0)*k3*pow(powSum(H2OVc, 1.0, CO2Vc, 2.0), 2.0)*x[CO2]*x[CO2];

    gammavPrime[CO2]  = 0.0;
    gammavPrime[CO2] += 3.0*powSum(gammaEnd[H2O], 2.0, gammaEnd[CO2], 1.0)*k3*pow(powSum(H2OVc, 2.0, CO2Vc, 1.0), 2.0)*x[H2O]*x[H2O];
    gammavPrime[CO2] += 6.0*powSum(gammaEnd[H2O], 1.0, gammaEnd[CO2], 2.0)*k3*pow(powSum(H2OVc, 1.0, CO2Vc, 2.0), 2.0)*x[H2O]*x[CO2];
    gammavPrime[CO2] += 3.0*gammaEnd[CO2]*CO2Vc*CO2Vc*x[CO2]*x[CO2];
  }
  
  return;
}

static void idealGas(double t, double cp[2], double s0[2], double h0[2]) {
  int i, j;
  
  for (j=0; j<2; j++) {
    for (i=0, cp[j]=0.0; i<7; i++) cp[j] += idealCoeff[i][j]*pow(t/1000.0, (double) i);
    for (i=7; i<13; i++)           cp[j] += idealCoeff[i][j]/pow(t/1000.0, (double) (i-6));
    
    for (i=0, h0[j]=0.0; i<7; i++) h0[j] += idealCoeff[i][j]*pow(t/1000.0, (double) (i+1))/((double) (i+1));
                                   h0[j] += idealCoeff[7][j]*log(t/1000.0);
    for (i=8; i<13; i++)           h0[j] += idealCoeff[i][j]/pow(t/1000.0, (double) (i-7))/((double) (7-i));
    
                                   s0[j]  = idealCoeff[0][j]*log(t/1000.0);
    for (i=1; i<7; i++)            s0[j] += idealCoeff[i][j]*pow(t/1000.0, (double) i)/((double) i);
    for (i=7; i<13; i++)           s0[j] += idealCoeff[i][j]/pow(t/1000.0, (double) (i-6))/((double) (6-i));

    cp[j] *= 8.31451;
    h0[j] *= 8.31451*1000.0;
    s0[j] *= 8.31451;
  }
}  

static void duan(double t, double p, double x[2], double *vPt, double *zPt, double phi[2]) {
  double bv, cv, dv, ev, fv, beta, gammav, v, z;
  double bvPrime[2], cvPrime[2], dvPrime[2], evPrime[2], fvPrime[2], betaPrime[2], gammavPrime[2];
  double zRef, vRef, phiRef[2], lnPhiH2O, lnPhiCO2;
  int useLowPcoeff, iter;
  
  zRef = 1.0;	  
  vRef = DBL_MAX; 
  phiRef[0] = 1.0;
  phiRef[1] = 1.0;
  
  useLowPcoeff = (p <= 2000.0) ? 1 : 0;
  
  if (!useLowPcoeff) {
    BVcAndDerivative	(1, t, x, &bv,     bvPrime);
    CVcAndDerivative	(1, t, x, &cv,     cvPrime);
    DVcAndDerivative	(1, t, x, &dv,     dvPrime);
    EVcAndDerivative	(1, t, x, &ev,     evPrime);
    FVcAndDerivative	(1, t, x, &fv,     fvPrime);
    BetaAndDerivative	(1, t, x, &beta,   betaPrime);
    GammaVcAndDerivative(1, t, x, &gammav, gammavPrime);
    
    iter = 0;
    v = 8.314467*t/2000.0;
    while (iter < 100) {
      double delv;
      z = 1 + bv/v + cv/v/v + dv/v/v/v/v + ev/v/v/v/v/v + (fv/v/v) * (beta + gammav/v/v) * exp(-gammav/v/v);
      delv = z*8.314467*t/2000.0 - v;
      if (fabs(delv) < v*100.0*DBL_EPSILON) break;
      v = (z*8.314467*t/2000.0 + v)/2.0;
      iter++;
    }
    if (iter >= 100) printf("zRef = %g, vRef = %g, iter = %d\n", z, v, iter);
    
    lnPhiH2O  = log(phiRef[H2O]);
    lnPhiH2O += -log(z) + log(zRef);
    lnPhiH2O += bvPrime[H2O]/v;
    lnPhiH2O += cvPrime[H2O]/2.0/v/v;
    lnPhiH2O += dvPrime[H2O]/4.0/v/v/v/v;
    lnPhiH2O += evPrime[H2O]/5.0/v/v/v/v/v;
    lnPhiH2O += ((fvPrime[H2O]*beta + betaPrime[H2O]*fv)/2.0/gammav)*(1.0-exp(-gammav/v/v));
    lnPhiH2O += ((fvPrime[H2O]*gammav+gammavPrime[H2O]*fv-fv*beta*(gammavPrime[H2O]-gammav))/2.0/gammav/gammav)
    	       *(1.0 - (gammav/v/v + 1.0)*exp(-gammav/v/v));
    lnPhiH2O += ((gammavPrime[H2O]-gammav)*fv/2.0/gammav/gammav)*(-2.0 + (gammav*gammav/v/v/v/v + 2.0*gammav/v/v + 2.0)*exp(-gammav/v/v));
    
    lnPhiCO2  = log(phiRef[CO2]);
    lnPhiCO2 += -log(z) + log(zRef);
    lnPhiCO2 += bvPrime[CO2]/v;
    lnPhiCO2 += cvPrime[CO2]/2.0/v/v;
    lnPhiCO2 += dvPrime[CO2]/4.0/v/v/v/v;
    lnPhiCO2 += evPrime[CO2]/5.0/v/v/v/v/v;
    lnPhiCO2 += ((fvPrime[CO2]*beta + betaPrime[CO2]*fv)/2.0/gammav)*(1.0-exp(-gammav/v/v));
    lnPhiCO2 += ((fvPrime[CO2]*gammav+gammavPrime[CO2]*fv-fv*beta*(gammavPrime[CO2]-gammav))/2.0/gammav/gammav)
    	       *(1.0 - (gammav/v/v + 1.0)*exp(-gammav/v/v));
    lnPhiCO2 += ((gammavPrime[CO2]-gammav)*fv/2.0/gammav/gammav)*(-2.0 + (gammav*gammav/v/v/v/v + 2.0*gammav/v/v + 2.0)*exp(-gammav/v/v));

    phiRef[H2O] = exp(lnPhiH2O);
    phiRef[CO2] = exp(lnPhiCO2);
    /*
    printf("phi H2O ref = %g, phi CO2 ref = %g\n", phiRef[H2O], phiRef[CO2]);
    */
  }
  
  BVcAndDerivative    (useLowPcoeff, t, x, &bv,     bvPrime);
  CVcAndDerivative    (useLowPcoeff, t, x, &cv,     cvPrime);
  DVcAndDerivative    (useLowPcoeff, t, x, &dv,     dvPrime);
  EVcAndDerivative    (useLowPcoeff, t, x, &ev,     evPrime);
  FVcAndDerivative    (useLowPcoeff, t, x, &fv,     fvPrime);
  BetaAndDerivative   (useLowPcoeff, t, x, &beta,   betaPrime);
  GammaVcAndDerivative(useLowPcoeff, t, x, &gammav, gammavPrime);
  
  if (!useLowPcoeff) {
    iter = 0;
    v = 8.314467*t/2000.0;
    while (iter < 100) {
      double delv;
      z = 1 + bv/v + cv/v/v + dv/v/v/v/v + ev/v/v/v/v/v + (fv/v/v) * (beta + gammav/v/v) * exp(-gammav/v/v);
      delv = z*8.314467*t/2000.0 - v;
      if (fabs(delv) < v*100.0*DBL_EPSILON) break;
      v = (z*8.314467*t/2000.0 + v)/2.0;
      iter++;
    }
    if (iter >= 100) printf("zRef = %g, vRef = %g, iter = %d\n", z, v, iter);
    zRef = z;
    vRef = v;
  }

  iter = 0;
  v = 8.314467*t/p;
  while (iter < 100) {
    double delv;
    z = 1 + bv/v + cv/v/v + dv/v/v/v/v + ev/v/v/v/v/v + (fv/v/v) * (beta + gammav/v/v) * exp(-gammav/v/v);
    delv = z*8.314467*t/p - v;
    if (fabs(delv) < v*100.0*DBL_EPSILON) break;
    v = (z*8.314467*t/p + v)/2.0;
    iter++;
  }
  if (iter >= 100) printf("z = %g, v = %g, iter = %d\n", z, v, iter);

  lnPhiH2O  = log(phiRef[H2O]);
  lnPhiH2O += -log(z) + log(zRef);
  lnPhiH2O += bvPrime[H2O]/v             - (!useLowPcoeff ? bvPrime[H2O]/vRef                         : 0.0);
  lnPhiH2O += cvPrime[H2O]/2.0/v/v       - (!useLowPcoeff ? cvPrime[H2O]/2.0/vRef/vRef                : 0.0);
  lnPhiH2O += dvPrime[H2O]/4.0/v/v/v/v   - (!useLowPcoeff ? dvPrime[H2O]/4.0/vRef/vRef/vRef/vRef      : 0.0);
  lnPhiH2O += evPrime[H2O]/5.0/v/v/v/v/v - (!useLowPcoeff ? evPrime[H2O]/5.0/vRef/vRef/vRef/vRef/vRef : 0.0);
  lnPhiH2O += ((fvPrime[H2O]*beta + betaPrime[H2O]*fv)/2.0/gammav)*(1.0-exp(-gammav/v/v));
  lnPhiH2O += ((fvPrime[H2O]*gammav+gammavPrime[H2O]*fv-fv*beta*(gammavPrime[H2O]-gammav))/2.0/gammav/gammav)
             *(1.0 - (gammav/v/v + 1.0)*exp(-gammav/v/v));
  lnPhiH2O += ((gammavPrime[H2O]-gammav)*fv/2.0/gammav/gammav)*(-2.0 + (gammav*gammav/v/v/v/v + 2.0*gammav/v/v + 2.0)*exp(-gammav/v/v));
  if (!useLowPcoeff) {
    lnPhiH2O -= ((fvPrime[H2O]*beta + betaPrime[H2O]*fv)/2.0/gammav)*(1.0-exp(-gammav/vRef/vRef));
    lnPhiH2O -= ((fvPrime[H2O]*gammav+gammavPrime[H2O]*fv-fv*beta*(gammavPrime[H2O]-gammav))/2.0/gammav/gammav)
               *(1.0 - (gammav/vRef/vRef + 1.0)*exp(-gammav/vRef/vRef));
    lnPhiH2O -= ((gammavPrime[H2O]-gammav)*fv/2.0/gammav/gammav)
               *(-2.0 + (gammav*gammav/vRef/vRef/vRef/vRef + 2.0*gammav/vRef/vRef + 2.0)*exp(-gammav/vRef/vRef));
  }

  lnPhiCO2  = log(phiRef[CO2]);
  lnPhiCO2 += -log(z) + log(zRef);
  lnPhiCO2 += bvPrime[CO2]/v             - (!useLowPcoeff ? bvPrime[CO2]/vRef                         : 0.0);
  lnPhiCO2 += cvPrime[CO2]/2.0/v/v       - (!useLowPcoeff ? cvPrime[CO2]/2.0/vRef/vRef                : 0.0);
  lnPhiCO2 += dvPrime[CO2]/4.0/v/v/v/v   - (!useLowPcoeff ? dvPrime[CO2]/4.0/vRef/vRef/vRef/vRef      : 0.0);
  lnPhiCO2 += evPrime[CO2]/5.0/v/v/v/v/v - (!useLowPcoeff ? evPrime[CO2]/5.0/vRef/vRef/vRef/vRef/vRef : 0.0);
  lnPhiCO2 += ((fvPrime[CO2]*beta + betaPrime[CO2]*fv)/2.0/gammav)*(1.0-exp(-gammav/v/v));
  lnPhiCO2 += ((fvPrime[CO2]*gammav+gammavPrime[CO2]*fv-fv*beta*(gammavPrime[CO2]-gammav))/2.0/gammav/gammav)
             *(1.0 - (gammav/v/v + 1.0)*exp(-gammav/v/v));
  lnPhiCO2 += ((gammavPrime[CO2]-gammav)*fv/2.0/gammav/gammav)*(-2.0 + (gammav*gammav/v/v/v/v + 2.0*gammav/v/v + 2.0)*exp(-gammav/v/v));
  if (!useLowPcoeff) {
    lnPhiCO2 -= ((fvPrime[CO2]*beta + betaPrime[CO2]*fv)/2.0/gammav)*(1.0-exp(-gammav/vRef/vRef));
    lnPhiCO2 -= ((fvPrime[CO2]*gammav+gammavPrime[CO2]*fv-fv*beta*(gammavPrime[CO2]-gammav))/2.0/gammav/gammav)
               *(1.0 - (gammav/vRef/vRef + 1.0)*exp(-gammav/vRef/vRef));
    lnPhiCO2 -= ((gammavPrime[CO2]-gammav)*fv/2.0/gammav/gammav)
               *(-2.0 + (gammav*gammav/vRef/vRef/vRef/vRef + 2.0*gammav/vRef/vRef + 2.0)*exp(-gammav/vRef/vRef));
  }
  
  *vPt = v;
  *zPt = z;
  phi[H2O] = exp(lnPhiH2O);
  phi[CO2] = exp(lnPhiCO2);
}

int main(int argc, char *argv[]) {
  double t = 1073.15; /* K     */
  double p = 14000.0; /* bars  */
  double x[2] = { 0.8, 0.2 }, xPureH2O[2] = { 1.0, 0.0}, xPureCO2[2] = { 0.0, 1.0 };
  
  double z, v, phi[2], zPureH2O, vPureH2O, phiPureH2O[2], zPureCO2, vPureCO2, phiPureCO2[2], cp[2], s0[2], h0[2];
  double zTempFp, vTempFp, phiTempFp[2], zTempBp, vTempBp, phiTempBp[2];
  double zTempFt, vTempFt, phiTempFt[2], zTempBt, vTempBt, phiTempBt[2];
  double zTempFpFt, vTempFpFt, phiTempFpFt[2], zTempFpBt, vTempFpBt, phiTempFpBt[2];
  double zTempBpFt, vTempBpFt, phiTempBpFt[2], zTempBpBt, vTempBpBt, phiTempBpBt[2];
  double dvdp, dzdp, dphidp[2], d2vdp2, d2zdp2, d2phidp2[2];
  double dvdt, dzdt, dphidt[2], d2vdt2, d2zdt2, d2phidt2[2];
  double d2vdtdp, d2zdtdp, d2phidtdp[2];
  double delp, delt;
  FILE *output;

  idealGas(t, cp, s0, h0);
  printf("H2O at t = %g K Cp = %g, s0 = %g, h0 = %g\n", t, cp[H2O], s0[H2O] + 359.6505, h0[H2O] - 355665.4136);
  printf("CO2 at t = %g K Cp = %g, s0 = %g, h0 = %g\n", t, cp[CO2], s0[CO2] + 210.0304, h0[CO2] - 385358.2260);
  
  printf("x[H2O] = %g, x[CO2] = %g\n", x[H2O], x[CO2]);  
  
  delp = p*sqrt(DBL_EPSILON);
  delt = t*sqrt(DBL_EPSILON);
  
  output = fopen("duan-table.dat", "w");
   
/*  for (p=10000.0; p<10100.0; p+=100.0) { */
    duan(t, p, x, &v, &z, phi);
    duan(t, p, xPureH2O, &vPureH2O, &zPureH2O, phiPureH2O);
    duan(t, p, xPureCO2, &vPureCO2, &zPureCO2, phiPureCO2);
    
    duan(t, p+delp, x, &vTempFp, &zTempFp, phiTempFp);
    duan(t, p-delp, x, &vTempBp, &zTempBp, phiTempBp);
    
    dvdp = (vTempFp-vTempBp)/(2.0*delp);
    dzdp = (zTempFp-zTempBp)/(2.0*delp);
    dphidp[H2O] = (phiTempFp[H2O]-phiTempBp[H2O])/(2.0*delp);
    dphidp[CO2] = (phiTempFp[CO2]-phiTempBp[CO2])/(2.0*delp);
    
    d2vdp2 = (vTempFp-2.0*v+vTempBp)/delp/delp;
    d2zdp2 = (zTempFp-2.0*z+zTempBp)/delp/delp;
    d2phidp2[H2O] = (phiTempFp[H2O]-2.0*phi[H2O]+phiTempBp[H2O])/delp/delp;
    d2phidp2[CO2] = (phiTempFp[CO2]-2.0*phi[CO2]+phiTempBp[CO2])/delp/delp;

    duan(t+delt, p, x, &vTempFt, &zTempFt, phiTempFt);
    duan(t-delt, p, x, &vTempBt, &zTempBt, phiTempBt);

    dvdt = (vTempFt-vTempBt)/(2.0*delt);
    dzdt = (zTempFt-zTempBt)/(2.0*delt);
    dphidt[H2O] = (phiTempFt[H2O]-phiTempBt[H2O])/(2.0*delt);
    dphidt[CO2] = (phiTempFt[CO2]-phiTempBt[CO2])/(2.0*delt);
    
    d2vdt2 = (vTempFt-2.0*v+vTempBt)/delt/delt;
    d2zdt2 = (zTempFt-2.0*z+zTempBt)/delt/delt;
    d2phidt2[H2O] = (phiTempFt[H2O]-2.0*phi[H2O]+phiTempBt[H2O])/delt/delt;
    d2phidt2[CO2] = (phiTempFt[CO2]-2.0*phi[CO2]+phiTempBt[CO2])/delt/delt;

    duan(t+delt, p+delp, x, &vTempFpFt, &zTempFpFt, phiTempFpFt);
    duan(t+delt, p-delp, x, &vTempBpFt, &zTempBpFt, phiTempBpFt);
    duan(t-delt, p+delp, x, &vTempFpBt, &zTempFpBt, phiTempFpBt);
    duan(t-delt, p-delp, x, &vTempBpBt, &zTempBpBt, phiTempBpBt);
    
    d2vdtdp = (vTempFpFt-vTempFpBt-vTempBpFt+vTempBpBt)/(4.0*delp*delt);
    d2zdtdp = (zTempFpFt-zTempFpBt-zTempBpFt+zTempBpBt)/(4.0*delp*delt);
    d2phidtdp[H2O] = (phiTempFpFt[H2O]-phiTempFpBt[H2O]-phiTempBpFt[H2O]+phiTempBpBt[H2O])/(4.0*delp*delt);
    d2phidtdp[CO2] = (phiTempFpFt[CO2]-phiTempFpBt[CO2]-phiTempBpFt[CO2]+phiTempBpBt[CO2])/(4.0*delp*delt);
  
    printf("t              %20.13e\n", t); 
    printf("p              %20.13e\n", p); 
    printf("v              %20.13e\n", v); 
    printf("z              %20.13e\n", z); 
    printf("phi[H2O]       %20.13e\n", phi[H2O]); 
    printf("phi[CO2]       %20.13e\n", phi[CO2]); 
    printf("f[H2O]         %20.13e\n", x[H2O]*phi[H2O]*p); 
    printf("f[CO2]         %20.13e\n", x[CO2]*phi[CO2]*p); 
    printf("a[H2O]         %20.13e\n", x[H2O]*phi[H2O]/phiPureH2O[H2O]); 
    printf("a[CO2]         %20.13e\n", x[CO2]*phi[CO2]/phiPureCO2[CO2]); 
    printf("dvdp           %20.13e\n", dvdp); 
    printf("dzdp           %20.13e\n", dzdp); 
    printf("dphidp[H2O]    %20.13e\n", dphidp[H2O]); 
    printf("dphidp[CO2]    %20.13e\n", dphidp[CO2]); 
    printf("d2vdp2         %20.13e\n", d2vdp2); 
    printf("d2zdp2         %20.13e\n", d2zdp2); 
    printf("d2phidp2[H2O]  %20.13e\n", d2phidp2[H2O]);
    printf("d2phidp2[CO2]  %20.13e\n", d2phidp2[CO2]);
    printf("dvdt           %20.13e\n", dvdt); 
    printf("dzdt           %20.13e\n", dzdt); 
    printf("dphidt[H2O]    %20.13e\n", dphidt[H2O]); 
    printf("dphidt[CO2]    %20.13e\n", dphidt[CO2]); 
    printf("d2vdt2         %20.13e\n", d2vdt2); 
    printf("d2zdt2         %20.13e\n", d2zdt2); 
    printf("d2phidt2[H2O]  %20.13e\n", d2phidt2[H2O]);
    printf("d2phidt2[CO2]  %20.13e\n", d2phidt2[CO2]);
    printf("d2vdtdp        %20.13e\n", d2vdtdp); 
    printf("d2zdtdp        %20.13e\n", d2zdtdp); 
    printf("d2phidtdp[H2O] %20.13e\n", d2phidtdp[H2O]);
    printf("d2phidtdp[CO2] %20.13e\n", d2phidtdp[CO2]);
    
    fprintf(output, " %20.13e", t); 
    fprintf(output, ",%20.13e", p); 
    fprintf(output, ",%20.13e", v); 
    fprintf(output, ",%20.13e", z); 
    fprintf(output, ",%20.13e", phi[H2O]); 
    fprintf(output, ",%20.13e", phi[CO2]); 
    fprintf(output, ",%20.13e", x[H2O]*phi[H2O]*p); 
    fprintf(output, ",%20.13e", x[CO2]*phi[CO2]*p); 
    fprintf(output, ",%20.13e", x[H2O]*phi[H2O]/phiPureH2O[H2O]); 
    fprintf(output, ",%20.13e", x[CO2]*phi[CO2]/phiPureCO2[CO2]); 
    fprintf(output, ",%20.13e", dvdp); 
    fprintf(output, ",%20.13e", dzdp); 
    fprintf(output, ",%20.13e", dphidp[H2O]); 
    fprintf(output, ",%20.13e", dphidp[CO2]); 
    fprintf(output, ",%20.13e", d2vdp2); 
    fprintf(output, ",%20.13e", d2zdp2); 
    fprintf(output, ",%20.13e", d2phidp2[H2O]);
    fprintf(output, ",%20.13e", d2phidp2[CO2]);
    fprintf(output, ",%20.13e", dvdt); 
    fprintf(output, ",%20.13e", dzdt); 
    fprintf(output, ",%20.13e", dphidt[H2O]); 
    fprintf(output, ",%20.13e", dphidt[CO2]); 
    fprintf(output, ",%20.13e", d2vdt2); 
    fprintf(output, ",%20.13e", d2zdt2); 
    fprintf(output, ",%20.13e", d2phidt2[H2O]);
    fprintf(output, ",%20.13e", d2phidt2[CO2]);
    fprintf(output, ",%20.13e", d2vdtdp); 
    fprintf(output, ",%20.13e", d2zdtdp); 
    fprintf(output, ",%20.13e", d2phidtdp[H2O]);
    fprintf(output, ",%20.13e", d2phidtdp[CO2]);
    fprintf(output, "\n");
/*  } */
  
  fclose(output);

  exit(0);
}










