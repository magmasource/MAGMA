/*
 * NiLiq implementation
 * Victor Kress
 * dvdp from compressionProps.py run 1/8/08
 * $Id: NiLiq.cc,v 1.14 2008/01/08 22:53:49 kress Exp $
 */

#include "NiLiq.h"

static ShomateData ni = {"Ni liquid","Ni",58.69,
			 38.91103,0.000000,0.000000,0.000000,0.000000,
			 -2.722630,74.47143,17.47904};

NiLiq::NiLiq():tmp(1726.) {
  lowT = 1300.;
  highT = 4001.0; /* 3156.; */
  lowP=0.;
  highP=6.e9;
  setData(&ni);
  Vinet.tr=tmp;
  Vinet.pr=1.e5;
  Vinet.V0=getVolume(tmp)/nmoles;
  Vinet.alphaT=getdVdT(tmp)/getVolume(tmp);
  Vinet.K=-getVolume(tmp)/(-7.98e-17);  //Kress et al. 2007
  Vinet.Kprime=5.5;
  updated=0;
  ShomateVinetPhase::init();
  return;
}
NiLiq::~NiLiq() {
  return;
}
double NiLiq::getVolume(double ttk) {
  // g/cc from Nasch and Steinemann (1995)
  double v,rhomp=7.81,b=-7.26e-4,c=0.;
  double dt,rho;
  dt=ttk-tmp;
  rho=rhomp+b*dt+c*dt*dt;
  v=mw/rho;
  return nmoles*v*1.e-6;
}
double NiLiq::getdVdT(double ttk) {
  double dvdt,rho,dt,rhomp=7.81,b=-7.26e-4,c=0.;
  dt=ttk-tmp;
  rho=rhomp+b*dt+c*dt*dt;
  dvdt = -mw*(b+2.*c*dt);
  dvdt /= rho*rho;       //cc/K
  dvdt *= 1.e-6;         //M^3/K
  return nmoles*dvdt;
}
double NiLiq::getd2VdT2(double ttk) {
  double temp,dd,rho,dt,rhomp=7.81,b=-7.26e-4,c=0.;
  dt=ttk-tmp;
  rho=rhomp+b*dt+c*dt*dt;
  temp = (b+2.*c*dt);
  dd = 2.*mw*temp*temp/(rho*rho*rho);
  dd -= 2.*mw*c/(rho*rho); // cc/(K*K)
  dd *= 1.e-6;             //M^3/(K*K)
  return nmoles*dd;
}
