/* VinetEOS header file
 * Implementation of Vinet pressure EOS for Phase class group.
 * Based on code from gibbs.c in Ghiorso's latest xMelts implementation 10/24/07
 * $Id: VinetEOS.cc,v 1.7 2007/11/17 01:52:22 kress Exp $
 * Victor Kress
 */

#include "VinetEOS.h"
#include <math.h>
#include <float.h>
#include <stdio.h>
/*
using namespace std;
*/
VinetEOS::VinetEOS() {
  alphaT=0.;//should be given value in child or error will be thrown
  x=x0=1.;
  return;
}
VinetEOS::~VinetEOS() {
  return;
}
double VinetEOS::getMolarVolume() {
  return V0*x*x*x;
}
double VinetEOS::getMolarGibbsPTerm(void){
  double gdp,a;
  double eta   = 3.0*(Kprime-1.0)/2.0;
  a  = (9.0*V0*K/(eta*eta))*(1.0 - eta*(1.0-x))*exp(eta*(1.0-x));
  a += V0*(tk-tr)*K*alphaT*(x*x*x - 1.0) - 9.0*V0*K/(eta*eta);  
  a -= (9.0*V0*K/(eta*eta))*(1.0 - eta*(1.0-x0))*exp(eta*(1.0-x0));
  a -= V0*(tk-tr)*K*alphaT*(x0*x0*x0 - 1.0) - 9.0*V0*K/(eta*eta);
  gdp = -a+pa*V0*x*x*x-pr*V0*x0*x0*x0;
  return gdp;
}
double VinetEOS::getMolarEnthalpyPTerm(void) {
  double hdp;
  hdp=getMolarGibbsPTerm()+tk*getMolarEntropyPTerm();
  return hdp;
}
double VinetEOS::getMolarEntropyPTerm(void) {
  double sdp;
  sdp = alphaT*K*V0*(x*x*x-x0*x0*x0);
  return sdp;
}
double VinetEOS::getMolarCpPTerm(void) {
  return tk*alphaT*K*V0*3.0*(x*x*dxdt - x0*x0*dx0dt);
}
double VinetEOS::getMolardCpdTPTerm(void) {
  double cpterm;
  cpterm = alphaT*K*V0*3.0*(x*x*dxdt - x0*x0*dx0dt) 
    + tk*alphaT*K*V0*3.0*(2.0*x*dxdt*dxdt + x*x*d2xdt2 - 2.0*x0*dx0dt*dx0dt 
			  - x0*x0*d2x0dt2);
  return cpterm;
}
double VinetEOS::getMolardVdT(void) {
  return 3.0*V0*x*x*dxdt;
}
double VinetEOS::getMolardVdP(void) {
  return 3.0*V0*x*x*dxdp;
}
double VinetEOS::getMolard2VdT2(void) {
  return 3.0*V0*(2.0*x*dxdt*dxdt + x*x*d2xdt2);
}
double VinetEOS::getMolard2VdTdP(void) {
  return 3.0*V0*(2.0*x*dxdt*dxdp + x*x*d2xdtdp);
}
double VinetEOS::getMolard2VdP2(void) {
  return 3.0*V0*(2.0*x*dxdp*dxdp + x*x*d2xdp2);
}
void VinetEOS::update(void) throw(PhaseError *){
  x=x0=1.;
  if (alphaT==0.) {
    PhaseError *e = 
      new PhaseError(STATE,FATAL,"VinetEOS",
		     "alphaT uninitialized in VinetEOS::update()");
    throw e;
  }
  double fn,dfn;
  int iter=0;
  double eta   = 3.0*(Kprime-1.0)/2.0;
  do {
    fn = x*x*pa - 3.0*K*(1.0-x)*exp(eta*(1.0-x)) -
      x*x*alphaT*K*(tk-tr);
    dfn = 2.0*x*pa + 3.0*K*(1.0+eta*(1.0-x))*exp(eta*(1.0-x)) -
      2.0*alphaT*K*(tk-tr);
    x = x - fn/dfn;
    iter++;
  } while ((iter < 500) && (fn*fn > 1.0e9*DBL_EPSILON));
  dxdt = -(1.0/3.0)*x*x*x*alphaT*K/(K*exp(eta*(1.0-x))*(-2.0+x-eta*x+eta*x*x));
  d2xdt2 = -dxdt*(2.0*pa*dxdt-6.0*K*eta*dxdt*exp(eta*(1.0-x))
		  -3.0*K*eta*eta*dxdt*exp(eta*(1.0-x))
		  +3.0*K*eta*eta*x*dxdt*exp(eta*(1.0-x))
		  -4.0*alphaT*K*x
		  -2.0*alphaT*K*dxdt*(tk-tr))/(2.0*pa*x
					       +3.0*K*exp(eta*(1.0-x))
					       +3.0*K*eta*exp(eta*(1.0-x))
					       -3.0*K*eta*x*exp(eta*(1.0-x))
					       -2.0*alphaT*K*x*(tk-tr));
  dxdp    = -(1.0/3.0)*x*x*x/(K*exp(eta*(1.0-x))*(2.0-x+eta*x-eta*x*x));
  d2xdtdp = -(2.0*x*dxdt+2.0*pa*dxdp*dxdt
	      -2.0*alphaT*K*dxdp*dxdt*(tk-tr)
	      -3.0*K*eta*eta*dxdt*dxdp*exp(eta*(1.0-x))
	      -6.0*K*dxdt*eta*dxdp*exp(eta*(1.0-x))
	      -2.0*alphaT*K*x*dxdp
	      +3.0*K*eta*eta*dxdt*dxdp
	      *exp(eta*(1.0-x))*x)/(2.0*pa*x+3.0*K*exp(eta*(1.0-x))
				    +3.0*K*eta*exp(eta*(1.0-x))
				    -3.0*K*eta*exp(eta*(1.0-x))*x
				    -2.0*alphaT*K*x*(tk-tr));
  d2xdp2  = - dxdp*dxdp*((-6.0+2.0*x
			  -4.0*eta*x+2.0*eta*x*x-eta*eta*x*x+eta*eta*x*x*x)
			 *exp(eta*(1.0-x)))/(x*exp(eta*(1.0-x))
					     *(2.0-x+eta*x-eta*x*x));
    
  iter = 0;
  do {
    fn = x0*x0*pr - 3.0*K*(1.0-x0)*exp(eta*(1.0-x0)) - x0*x0*alphaT*K*(tk-tr);
    dfn = 2.0*x0*pr + 3.0*K*(1.0+eta*(1.0-x0))*exp(eta*(1.0-x0)) 
      - 2.0*alphaT*K*(tk-tr);
    x0 = x0 - fn/dfn;
    iter++;
  } while ((iter < 500) && (fn*fn > 1.0e9*DBL_EPSILON));
  dx0dt    = -(1.0/3.0)*x0*x0*x0*alphaT*K/(K*exp(eta*(1.0-x0))
					  *(-2.0+x0-eta*x0+eta*x0*x0));
  d2x0dt2  = -dx0dt*(2.0*pr*dx0dt-6.0*K*eta*dx0dt*exp(eta*(1.0-x0))
		     -3.0*K*eta*eta*dx0dt*exp(eta*(1.0-x0))
		     +3.0*K*eta*eta*x0*dx0dt*exp(eta*(1.0-x0))
		     -4.0*alphaT*K*x0
		     -2.0*alphaT*K*dx0dt*(tk-tr))/(2.0*pr*x0
						 +3.0*K*exp(eta*(1.0-x0))
						 +3.0*K*eta*exp(eta*(1.0-x0))
						 -3.0*K*eta*x0*exp(eta*(1.0-x0))
						 -2.0*alphaT*K*x0*(tk-tr));
  return;
}
