/*
 * CuLiq implementation
 * Victor Kress
 * dvdp from compressionProps.py run 1/8/08
 * $Id: CuLiq.cc,v 1.12 2008/01/08 22:53:49 kress Exp $
 */

#include "CuLiq.h"

static ShomateData cu = {"Cu liquid","Cu",63.546, 
			 32.84450,-0.000084,0.000032,-0.000004,-0.000028,
			 -1.804901,73.92310,11.8573};

CuLiq::CuLiq():tmp(1356.) {
  setData(&cu);
  lowT = 1300.;
  highT = 2843.;
  lowP=0.;
  highP=6.e9;
  Vinet.tr=tmp;
  Vinet.pr=1.e5;
  Vinet.V0=getVolume(tmp)/nmoles;
  Vinet.alphaT=getdVdT(tmp)/getVolume(tmp);
  Vinet.K=-getVolume(tmp)/(-1.811e-16);  //Kress et al. 2007
  Vinet.Kprime=5.5;
  updated=0;
  ShomateVinetPhase::init();
  return;
}
CuLiq::~CuLiq() {
  return;
}
double CuLiq::getVolume(double ttk) {
  // g/cc from Nasch and Steinemann (1995)
  double v,tmp=1356.,rhomp=8.02,b=-6.09e-4,c=0.;
  double dt,rho;
  dt=ttk-tmp;
  rho=rhomp+b*dt+c*dt*dt;
  v=nmoles*mw/rho;
  return v*1.e-6;
}
double CuLiq::getdVdT(double ttk) {
  double dvdt,rho,dt,rhomp=8.02,b=-6.09e-4,c=0.;
  dt=ttk-tmp;
  rho=rhomp+b*dt+c*dt*dt;
  dvdt = -mw*(b+2.*c*dt);
  dvdt /= rho*rho;       //cc/K
  dvdt *= 1.e-6;         //M^3/K
  return nmoles*dvdt;
}
double CuLiq::getd2VdT2(double ttk) {
  double temp,dd,rho,dt,rhomp=8.02,b=-6.09e-4,c=0.;
  dt=ttk-tmp;
  rho=rhomp+b*dt+c*dt*dt;
  temp = (b+2.*c*dt);
  dd = 2.*mw*temp*temp/(rho*rho*rho);
  dd -= 2.*mw*c/(rho*rho); // cc/(K*K)
  dd *= 1.e-6;             //M^3/(K*K)
  return nmoles*dd;
}
