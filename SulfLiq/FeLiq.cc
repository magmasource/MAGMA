/*
 * FeLiq implementation
 * Victor Kress
 * dvdp from compressionProps.py run 1/8/08
 * $Id: FeLiq.cc,v 1.11 2008/01/08 22:53:49 kress Exp $
 */

#include "FeLiq.h"

static ShomateData fe = {"Fe liquid","Fe",55.847,
			 46.02400,-1.884667e-8,6.094750e-9,-6.640301e-10,
			 -8.246121e-9,-10.80543,72.54094,12.39502};

FeLiq::FeLiq():tmp(1809.) {
  lowT=1300.;
  highT=4001.0; /* 3133.345; */
  lowP=0.;
  highP=6.e9;
  setData(&fe);
  Vinet.tr=tmp;
  Vinet.pr=1.e5;
  Vinet.V0=getVolume(tmp)/nmoles;
  Vinet.alphaT=getdVdT(tmp)/getVolume(tmp);
  Vinet.K=-getVolume(tmp)/(-8.34e-17);  //Kress et al. 2007
  Vinet.Kprime=5.5;
  updated=0;
  ShomateVinetPhase::init();
  return;
}
FeLiq::~FeLiq() {
  return;
}
double FeLiq::getVolume(double ttk) {
  // g/cc from Nasch and Steinemann (1995)
  double v,rhomp=6.98,b=-5.72e-4,c=0.;
  double dt,rho;
  dt=ttk-tmp;
  rho=rhomp+b*dt+c*dt*dt;
  v=mw/rho;         //cc
  return nmoles*v*1.e-6;
}
double FeLiq::getdVdT(double ttk) {
  double dvdt,rho,dt,rhomp=6.98,b=-5.72e-4,c=0.;
  dt=ttk-tmp;
  rho=rhomp+b*dt+c*dt*dt;
  dvdt = -mw*(b+2.*c*dt);
  dvdt /= rho*rho;       //cc/K
  dvdt *= 1.e-6;         //M^3/K
  return nmoles*dvdt;
}
double FeLiq::getd2VdT2(double ttk) {
  double temp,dd,rho,dt,rhomp=6.98,b=-5.72e-4,c=0.;
  dt=ttk-tmp;
  rho=rhomp+b*dt+c*dt*dt;
  temp = (b+2.*c*dt);
  dd = 2.*mw*temp*temp/(rho*rho*rho);
  dd -= 2.*mw*c/(rho*rho); // cc/(K*K)
  dd *= 1.e-6;             //M^3/(K*K)
  return nmoles*dd;
}
