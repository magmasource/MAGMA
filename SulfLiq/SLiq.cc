/*
 * S liquid implementation
 * Victor Kress
 * dvdp data from compressionProps.py run 1/8/08
 * $Id: SLiq.cc,v 1.13 2008/01/08 22:53:49 kress Exp $
 */

#include "SLiq.h"

static ShomateData yellow = {"S liquid","S",32.066,
			     -4540.970,26065.60,-55520.70,42012.20,54.58860,
			     787.8070,-10826.30,1853.781};
static ShomateData red = {"S liquid","S",32.066,
			  -37.93350,133.2420,-95.32450,24.00940,7.654530,
			  29.78810,-13.15340,1853.781};

SLiq::SLiq() {
  lowT = 200.;
  highT = 2500.;
  lowP=0.;
  highP=3.e9;
  double ltr=1300.;
  setData(&yellow);
  Vinet.tr=ltr;
  Vinet.pr=1.e5;
  Vinet.V0=getVolume(ltr)/nmoles;
  Vinet.alphaT=getdVdT(ltr)/getVolume(ltr);
  Vinet.K=-getVolume(ltr)/(-1.502e-15);  //Kress et al. 2007
  Vinet.Kprime=5.5;
  updated=0;
  ShomateVinetPhase::init();
  ShomatePhase::setTk(298.15);
  return;
}
void SLiq::setTk(double ltk) {
  ShomatePhase::setTk(ltk);
  setData((tk>432.020)? &red : &yellow);
  return;
}
double SLiq::getVolume(double ttk) {
  // from Cubicciotti (1964)
  double v800=14.0;
  double v;
  v = v800*nmoles + (ttk-(800.+273.15))*getdVdT(ttk);
  v *= 1.e-6;  //convert to M^3
  return v;
}
double SLiq::getdVdT(double ttk) {
  // from Cubicciotti (1964)
  double dvdt;
  double v300=13.0; // cc/mol
  double v800=14.0;
  dvdt=(v800-v300)/(800.-300.);
  dvdt *= 1.e-6;  //convert to M^3 
  dvdt *= nmoles;
  return dvdt;
}
double SLiq::getd2VdT2(double ttk) {
  return 0.;
}


