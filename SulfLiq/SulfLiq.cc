/* class SulfSpec
 * program to speciate OSFN data
 * by Victor Kress
 * $Id: SulfLiq.cc,v 1.71 2008/01/08 22:53:49 kress Exp $
 * @version $Revision: 1.71 $
 * best osfn fit as of 11/28/06 (osfn082406.fit)
 * cu species from osfnc101206.fit
 * dvdp numbers from compressionProps.py run 1/08/08
 * volumes from 10/12/07 fit
 */

#include "SulfLiq.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include "O2Gas.h"
#include "S2Gas.h"
#include "SLiq.h"
#include "FeLiq.h"
#include "NiLiq.h"
#include "CuLiq.h"
#include "NumUtil.h"
#include "svdSolve.h"

using namespace std;

static SLSSData odat = {"O liquid","O",
			15.9994,44049.14,65.94,31.460654,
			-147721.4115,
                        13.69e-6,-88.73e-9,-4.177e-15,7.463e-18};
static SLSSData specdat[10]={{"wu liquid","FeO",
			      71.8464,-179389.39,135.34,77.484654,
			      -212216.8076,
			      3.243063e-05,-8.812579e-08,-9.377e-15,1.756e-17},
			     {"hm liquid","FeO1.5",
			      79.8461,-232520.76,148.94,93.214982,
			      -286077.5134,
			      2.821563e-05,-1.324908e-07,-1.048e-14,2.297e-17},
			     {"bu liquid","NiO",
			      74.6894,-72035.49,191.97,70.371684,
			      -214087.2917,
			      2.092094e-05,-8.808343e-08,-5.307e-15,1.132e-17},
			     {"tt liquid","FeS",
			      87.913,-93139.49,130.58,77.484654,
			      -164460.1212,
			      2.220203e-05,2.604213e-09,-1.517e-15,-3.552e-19},
			     {"mi liquid","NiS",
			      90.756,-51451.87,186.76,70.371684,
			      -166330.6054,
			      1.806264e-05,2.646568e-09,-8.995e-16,-2.937e-19},
			     {"dj liquid","CuS0.5",
			      79.579,-383.91,66.90,48.574747,
			      -116954.5073,
			      1.511674e-05,1.596583e-09,-6.501e-16,-1.483e-19},
			     {"op liquid","FeOS",
			      103.908,-153851.88,390.91,108.945309,
			      -312181.5328,
			      4.750433e-05,-8.612579e-08,-1.573e-14,2.514e-17},
			     {"ns liquid","Ni.25S.25O",
			      38.6884,-59398.23,397.65,49.053576,
			      -189304.06285,
			      1.911116e-05,-8.806836e-08,-4.741e-15,1.034e-17},
			     {"cv liquid","CuS",
			      95.606,-82791.42,73.15,64.305074,
			      -166936.8699,
			      1.777159e-05,2.596583e-09,-8.710e-16,-2.835e-19},
			     {"te liquid","CuO",//destabilized manually
			      79.5454,-61481.10,46.86,64.305074,
			      -214693.5562,
			      2.157989e-05,-8.813342e-08,-5.520e-15,1.169e-17}};

double SulfLiq::allstoich[15][5]={{1.,0.,0.,0.,0.},   /*o-*/
				  {0.,1.,0.,0.,0.},   /*s-*/
				  {0.,0.,1.,0.,0.},   /*f-*/
				  {0.,0.,0.,1.,0.},   /*n-*/
				  {0.,0.,0.,0.,1.},   /*c-*/
				  {1.,0.,1.,0.,0.},   /*wu*/
				  {1.5,0.,1.,0.,0.},  /*hm*/
				  {1.,0.,0.,1.,0.},   /*bu*/
				  {0.,1.,1.,0.,0.},   /*tt*/
				  {0.,1.,0.,1.,0.},   /*mi*/
				  {0.,.5,0.,0.,1.},   /*dj*/
				  {1.,1.,1.,0.,0.},   /*op*/
				  {1.,.25,0.,.25,0.}, /*ns*/
				  {0.,1.,0.,0.,1.},   /*cv*/
				  {1.,0.,0.,0.,1.}};  /*te*/

/****************************
 ***** public functions *****
 ****************************/

/******************** initialization ***********************/
/* constructors ********************************************/
SulfLiq::SulfLiq():NCOMP(5),NSPEC(15),ODEX(0),SDEX(1),FDEX(2),NDEX(3),
		   CDEX(4),WUDEX(5),HMDEX(6),BUDEX(7),TTDEX(8),
		   MIDEX(9),DJDEX(10),OPDEX(11),NSDEX(12),CVDEX(13),
		   TEDEX(14),STR(1300.) {             // plain constructor
  init();
  return;
}

SulfLiq::~SulfLiq() {
  int i;
  delete po2;
  delete ps2;
  for (i=0;i<NSPEC;i++) {
    delete ss[i];
  }
  delete []name;
  return;
}

/* init **********************************/
void SulfLiq::init() {
  int i,j;
  name = new char[15];
  strcpy(name,"Sulfide Liquid");

  ncomp = NCOMP;
  nspec = NSPEC;
  highT = 4000.;
  lowT = 700.;
  highP = 6.e9;

  SpecSolNID::init();  // starts cascade of space allocation in parents

  for (i=0;i<nspec;i++) {
    for (j=0;j<ncomp;j++) {
      spstoich[i][j]=allstoich[i][j];
    }
  }
  
  po2 = new O2Gas();
  ps2 = new S2Gas();
  
  Wh[SDEX][TTDEX]  = -21971.43;
  Wh[SDEX][MIDEX]  =  46930.37;
  Wh[SDEX][OPDEX]  =  44200.86;
  Wh[SDEX][NSDEX]  =  19443.81;
  
  Wh[FDEX][NDEX]   = -13720.23;
  Wh[FDEX][WUDEX]  =  69048.93;
  Wh[FDEX][HMDEX]  =  26016.05;
  Wh[FDEX][BUDEX]  =  46726.28;
  Wh[FDEX][TTDEX]  =  11097.89;
  Wh[FDEX][MIDEX]  = -34811.29;
  Wh[FDEX][OPDEX]  =  -3438.46;
  Wh[FDEX][DJDEX]  =  11649.50;
  Wh[FDEX][CVDEX]  =  64684.94;
  Wh[FDEX][TEDEX]  =  14045.46;
  
  Wh[NDEX][FDEX]   =  -6102.36;
  Wh[NDEX][WUDEX]  = 185737.30;
  Wh[NDEX][HMDEX]  = 104123.23;
  Wh[NDEX][BUDEX]  =  46860.72;
  Wh[NDEX][TTDEX]  = -11388.91;
  Wh[NDEX][MIDEX]  = -71588.29;
  Wh[NDEX][OPDEX]  = 159666.44;
  Wh[NDEX][NSDEX]  = -67300.07;
  Wh[NDEX][DJDEX]  =   8606.17;
  Wh[NDEX][CVDEX]  =   8751.31;
  Wh[NDEX][TEDEX]  =  24098.37;

  Wh[CDEX][WUDEX]  = 159999.60;
  Wh[CDEX][BUDEX]  =  20214.72;
  Wh[CDEX][TTDEX]  =  93009.54;
  Wh[CDEX][MIDEX]  = -15349.12;
  Wh[CDEX][DJDEX]  =  27999.77;
  Wh[CDEX][CVDEX]  =    273.10;
  Wh[CDEX][TEDEX]  =     85.83;
  
  Wh[WUDEX][FDEX]  =  87503.08;
  Wh[WUDEX][NDEX]  = Wh[NDEX][WUDEX];
  Wh[WUDEX][HMDEX] = -21711.53;
  Wh[WUDEX][BUDEX] = -60039.70;
  Wh[WUDEX][MIDEX] =      0.00;
  Wh[WUDEX][NSDEX] =      0.00;
  
  Wh[HMDEX][FDEX]  =  36220.54;
  Wh[HMDEX][NDEX]  = Wh[NDEX][HMDEX];
  Wh[HMDEX][WUDEX] = -10871.49;
  Wh[HMDEX][TTDEX] =      0.00;
  Wh[HMDEX][BUDEX] =      0.00;
  Wh[HMDEX][MIDEX] =      0.00;
  Wh[HMDEX][OPDEX] =      0.00;
  Wh[HMDEX][NSDEX] =      0.00;
  
  Wh[BUDEX][FDEX]  = Wh[FDEX][BUDEX];
  Wh[BUDEX][NDEX]  = Wh[NDEX][BUDEX];
  Wh[BUDEX][WUDEX] = Wh[WUDEX][BUDEX];
  Wh[BUDEX][HMDEX] = Wh[HMDEX][BUDEX];
  Wh[BUDEX][TTDEX] =      0.00;
  Wh[BUDEX][MIDEX] =   2930.50;
  Wh[BUDEX][NSDEX] =      0.00;

  Wh[TTDEX][SDEX]  =  40100.07;
  Wh[TTDEX][FDEX]  = Wh[FDEX][TTDEX];
  Wh[TTDEX][NDEX]  = Wh[NDEX][TTDEX];
  Wh[TTDEX][WUDEX] = Wh[WUDEX][TTDEX];
  Wh[TTDEX][HMDEX] = Wh[HMDEX][TTDEX];
  Wh[TTDEX][BUDEX] = Wh[BUDEX][TTDEX];
  Wh[TTDEX][MIDEX] = -14791.05;
  Wh[TTDEX][OPDEX] =  16076.86;
  
  Wh[MIDEX][SDEX]  = Wh[SDEX][MIDEX];
  Wh[MIDEX][FDEX]  = Wh[FDEX][MIDEX];
  Wh[MIDEX][NDEX]  =  -7104.74;
  Wh[MIDEX][WUDEX] = Wh[WUDEX][MIDEX];
  Wh[MIDEX][HMDEX] = Wh[HMDEX][MIDEX];
  Wh[MIDEX][BUDEX] = Wh[BUDEX][MIDEX];
  Wh[MIDEX][TTDEX] =  -9190.86;
  Wh[MIDEX][OPDEX] =      0.00;
  Wh[MIDEX][NSDEX] =  49008.57;

  Wh[DJDEX][CDEX]  = Wh[CDEX][DJDEX];
 
  Wh[OPDEX][SDEX]  = Wh[SDEX][OPDEX];
  Wh[OPDEX][FDEX]  = Wh[FDEX][OPDEX];
  Wh[OPDEX][NDEX]  = Wh[NDEX][OPDEX];
  Wh[OPDEX][WUDEX] = Wh[WUDEX][OPDEX];
  Wh[OPDEX][HMDEX] = Wh[HMDEX][OPDEX];
  Wh[OPDEX][TTDEX] = -71847.20;
  Wh[OPDEX][MIDEX] = Wh[MIDEX][OPDEX];
  Wh[OPDEX][NSDEX] =      0.00;
  
  Wh[NSDEX][SDEX]  = Wh[SDEX][NSDEX];
  Wh[NSDEX][NDEX]  = Wh[NDEX][NSDEX];
  Wh[NSDEX][WUDEX] = Wh[WUDEX][NSDEX];
  Wh[NSDEX][HMDEX] = Wh[HMDEX][NSDEX];
  Wh[NSDEX][BUDEX] = Wh[BUDEX][NSDEX];
  Wh[NSDEX][MIDEX] = Wh[MIDEX][NSDEX];
  Wh[NSDEX][OPDEX] = Wh[OPDEX][NSDEX];

  Wh[DJDEX][FDEX]  = Wh[FDEX][DJDEX];
  Wh[DJDEX][NDEX]  = Wh[NDEX][DJDEX];
  Wh[DJDEX][CDEX]  = Wh[CDEX][DJDEX];
  Wh[DJDEX][CVDEX] =          -10.31;
  Wh[DJDEX][TEDEX] =        -3843.52;

  Wh[CVDEX][FDEX]  = Wh[FDEX][CVDEX];
  Wh[CVDEX][NDEX]  = Wh[NDEX][CVDEX];
  Wh[CVDEX][CDEX]  = Wh[CDEX][CVDEX];
  Wh[CVDEX][DJDEX] = Wh[DJDEX][CVDEX];
  Wh[CVDEX][TEDEX] =            -0.29;

  Wh[TEDEX][FDEX]  = Wh[FDEX][TEDEX];
  Wh[TEDEX][NDEX]  = Wh[NDEX][TEDEX];
  Wh[TEDEX][CDEX]  = Wh[CDEX][TEDEX];
  Wh[TEDEX][DJDEX] = Wh[DJDEX][TEDEX];
  Wh[TEDEX][CVDEX] = Wh[CVDEX][TEDEX];
  
  /**set standard states**/
  ss[ODEX] = new SLSSPhase(&odat);
  ss[SDEX] = new SLiq();
  ss[FDEX] = new FeLiq();
  ss[NDEX] = new NiLiq();
  ss[CDEX] = new CuLiq();
  for (i=WUDEX;i<nspec;i++) {
    ss[i] = new SLSSPhase(&specdat[i-WUDEX]);
  }

  // reset T and P bounds to solution defaults
  for (i=0;i<nspec;i++) {
    ss[i]->resetTPbounds(lowT,highT,lowP,highP);
  }

  initElOxArrays();
  
  return;  // end of init
}

// setting methods ///////////////////////////////
/* setTk *************************************/
void SulfLiq::setTk(double ltk) {
  SpecSolution::setTk(ltk);
  po2->setTk(ltk);
  ps2->setTk(ltk);
  return;
}
/* setPa *************************************/
void SulfLiq::setPa(double lpa) {
  SpecSolution::setPa(lpa);
  return;
}
/* setFugacity *******************************/
int SulfLiq::setFugacity(double logfo2,double logfs2,int verbose) {
  int i,j,niter,done,stable;
  double lastobj,thisobj,omega,muo,mus,lambda,xstep,maxomega,minomega;
  double *test,*msulf,**H,**Hprime,*w,**v,*dmu,*newdmu,*dx,*F,*dFdx,fo,fs;
  static const double tol=5.;
  static const double defomega=300.;
  static const double deflambda=100.;
  static const double minstep=1.e-8;
  static const int maxiter=250;
  static const double minlambda=1.e-20;
  static const double maxlambda=1.e30;

  msulf = new double[ncomp];
  test = new double[ncomp];
  dx = new double[2];
  dmu = new double[2];
  newdmu = new double[2];
  H=dmatrix(2,2);
  Hprime=dmatrix(2,2);
  w = new double[2];
  v = dmatrix(2,2);
  F = new double[2];
  dFdx = new double[2];

  muo = po2->getGibbs();
  muo += R*tk*logfo2*2.3026;
  muo /= 2.;
  mus = ps2->getGibbs();
  mus += R*tk*logfs2*2.3026;
  mus /= 2.;
  
  getComps(msulf);
  getComps(test);

  omega=defomega;
  lambda=deflambda;
  done=0;
  lastobj=DBL_MAX;
  xstep=1.;
  setComps(test);
  i=speciate();
  //cout << "\nSpeciated " << i;
  stable=isStable();
  if (!stable) {
    cout << "\nEntered setFugacity with unstable composition";
    return 0;
  }

  for (niter=done=0;niter<maxiter&&!done;niter++) {

    //calculate new objective function      
    newdmu[0] = muo - getMu(ODEX);
    newdmu[1] = mus - getMu(SDEX);
    thisobj = fabs(newdmu[0])+fabs(newdmu[1]);
    if (verbose) {
      printf("\n%10.1f %10.1f %10.1f ",newdmu[0],newdmu[1],thisobj);
      if (!stable) {
	cout << "unstable";
      }
    }

    //cout <<endl<<stable<<" "<<lastobj<<" "<<thisobj<<" "<<xstep;
    if (xstep<=minstep) {  //reset
      lastobj = thisobj;
      if (lambda==deflambda) { //unusual case
	lambda /=10.;
	omega = 100.*minstep/xstep;
	if (verbose) cout << " ~" << lambda << " " << omega;
      }
      else {  // normal reset
	lambda=deflambda;
	if (verbose) cout << " !" << lambda << " " << omega;
	for (i=0;i<2;i++) {
	  for (j=0,H[i][j]=0.;j<2;j++) {
	    H[i][j] = getdMudX(i,0)*getdMudX(j,0)+getdMudX(i,1)*getdMudX(j,1);
	  }
	}
	for (i=0;i<2;i++) {
	  for (j=0,dmu[i]=0.;j<2;j++) {
	    dmu[i] += getdMudX(i,j)*newdmu[j];
	  }
	}
      }
    }
    else if (!stable||(thisobj>lastobj)){//failed try
      thisobj=lastobj;
      if (lambda<maxlambda) lambda *= 10.;
      if (verbose) cout << " /" << lambda << " " << omega;
    }
    else {                              //successful try
      if (lambda>minlambda) lambda /=2.;
      if (verbose) cout << " \\" << lambda << " " << omega;
      for (i=0;i<ncomp;i++) msulf[i]=test[i]; //transfer current guess
      lastobj = thisobj;
      if (fabs(thisobj) < tol) {         // converged
	done = 1;
	continue;		// exit loop
      }
      for (i=0;i<2;i++) {
	for (j=0,H[i][j]=0.;j<2;j++) {
	  H[i][j] = getdMudX(i,0)*getdMudX(j,0)+getdMudX(i,1)*getdMudX(j,1);
	}
      }
      for (i=0;i<2;i++) {
	for (j=0,dmu[i]=0.;j<2;j++) {
	  dmu[i] += getdMudX(i,j)*newdmu[j];
	}
      }
    }

    if (!done) {//test unecessary.'continue' above would skip this code anyway.
      for (i=0;i<2;i++) {
	for (j=0;j<2;j++) {
	  Hprime[i][j] = H[i][j];
	}
	Hprime[i][i] += lambda;
      }

      svdSolve(Hprime,dx,dmu,2,2,w,v,1.e-10);

      // make sure omega isn't too small
      xstep = (dx[0]*dx[0]+dx[1]*dx[1]);
      xstep = sqrt(xstep);
      minomega=minstep/xstep;
      // make sure omega isn't too large
      maxomega=defomega;
      for (i=0;i<2;i++) {
	double temp;
	if (dx[i]!=0.) {
	  temp=msulf[i]*0.2/fabs(dx[i]); /*is change too large?*/
	  if (temp<maxomega) maxomega=temp;
	}
	if (dx[i]<0.) {   /*is omega driving component neg?*/
	  temp = (msulf[i]/dx[i])*(1.e-6 - 1.); 
	  if (temp<maxomega) maxomega=temp;
	}
      }
      // find optimum omega
      setComps(msulf);
      speciate();
      fo=muo - getMu(ODEX);
      fs=mus - getMu(SDEX);
      F[0] =  fo*fo+fs*fs;
      dFdx[0] = -2.*fo*dx[0]-2.*fs*dx[1];
      if (dFdx[0]>0.) { // uphill from the start
	//worth a try (we're pretty desperate here)
	omega=(maxomega+minomega)/2.;
	if (-2.*fo*dx[0]>0.) dx[0]=0.;
	if (-2.*fs*dx[1]>0.) dx[1]=0.;
	for (i=0;i<2;i++) test[i] = msulf[i]+omega*dx[i];
	setComps(test);
	speciate();
      }
      else {
	int wniter=0;
	do {
	  double lastomega;
	  wniter++;
	  lastomega=omega;
	  omega=(maxomega+minomega)/2.;
	  for (i=0;i<2;i++) test[i] = msulf[i]+omega*dx[i];
	  setComps(test);
	  speciate();
	  stable = isStable();
	  fo=muo - getMu(ODEX);
	  fs=mus - getMu(SDEX);
	  F[1] =  fo*fo+fs*fs;
	  dFdx[1] = -2.*fo*dx[0]-2.*fs*dx[1];
	  if (!stable) {
	    if (lastomega==maxomega)  maxomega=omega;
	    else minomega=omega;
	  }
	  if (F[1]>F[0]) {
	    if (dFdx[1]>0) maxomega=omega;
	    else minomega=omega;
	  }
	  else if (dFdx[1]<0.) {
	    minomega = omega;
	    F[0]=F[1];
	  }
	  else if (dFdx[1]>0.) {
	    maxomega = omega;
	    F[0]=F[1];
	  }
	  else {
	    maxomega=minomega=omega;
	  }
	} while ((F[1]>F[0])&&(maxomega-minomega>.1)&&(wniter<150));
      }
      // increment sulfide
      xstep = (dx[0]*dx[0]+dx[1]*dx[1])*omega*omega;
      xstep = sqrt(xstep);
    }
  } // end of main iteration loop

  delete []msulf;
  delete []test;
  delete []dx;
  delete []dmu;
  delete []newdmu;
  delete []w;
  delete []F;
  delete []dFdx;
  free_dmatrix(2,2,H);
  free_dmatrix(2,2,Hprime);
  free_dmatrix(2,2,v);
  return niter;
}
int SulfLiq::setFugacity(double logfo2,double logfs2) {
   int niter;
   niter = setFugacity(logfo2,logfs2,0);
   return niter;
}
int SulfLiq::setlogfo2(double logfo2) {
  static const int maxiter=200;
  int niter=0;
  double ftol=.00001;
  double minx,maxx,xo,lf,resid;
  minx=10.*DBL_EPSILON;
  maxx=.2;
  do {
    xo=(maxx+minx)/2.;
    comps[ODEX]=xo*getMoles();
    fillSpecs();
    getMoles();
    updated=0;
    update();
    if (getdMudX(ODEX,ODEX)>0.) {
      lf=getlogfo2();
      resid=lf-logfo2;
      if (fabs(resid)<ftol) {
	break;
      }
      else if (resid<0.) {
	minx=xo;
      }
      else {
	maxx=xo;
      }
    }
    else { //current xo not stable
      maxx=xo;
      resid=100.;
    }
    printf("%10.4f  %10.4f  %10.4f  %10.4f\n",minx,xo,maxx,resid);
    niter++;
  } while ((niter<maxiter)&&(fabs(resid)>ftol)&&(maxx-minx>0.));
  return niter;
}
int SulfLiq::setlogfs2(double logfs2) {
  static const int maxiter=200;
  int niter=0;
  double ftol=.00001;
  double minx,maxx,xs,lf,resid;
  minx=10.*DBL_EPSILON;
  maxx=.2;
  do {
    xs=(maxx+minx)/2.;
    comps[SDEX]=xs*getMoles();
    fillSpecs();
    getMoles();
    updated=0;
    update();
    if (getdMudX(SDEX,SDEX)>0.) {
      lf=getlogfs2();
      resid=lf-logfs2;
      if (fabs(resid)<ftol) {
	break;
      }
      else if (resid<0.) {
	minx=xs;
      }
      else {
	maxx=xs;
      }
    }
    else { //current xs not stable
      maxx=xs;
      resid=100.;
    }
    printf("%10.4f  %10.4f  %10.4f  %10.4f\n",minx,xs,maxx,resid);
    niter++;
  } while ((niter<maxiter)&&(fabs(resid)>ftol)&&(maxx-minx>0.));
  return niter;
}

// getting methods ////////////////////////////
/* getVolume *********************************/
double SulfLiq::getVolume() {
  int i;
  double v;
  update();
  v=0.;
  for (i=0;i<nspec;i++) {
    v+=specs[i]*ss[i]->getVolume();
  }
  return v;
}
/* getdVdT *********************************/
double SulfLiq::getdVdT() {
  int i;
  double dv;
  update();
  dv=0.;
  for (i=0;i<nspec;i++) {
    dv+=specs[i]*ss[i]->getdVdT();
  }
  return dv;
}
/* getlnfo2 **********************************/
double SulfLiq::getlogfo2() {
  double lnfo2;
  update();
  if (specs[ODEX]<=0.) {
    PhaseError *e = new PhaseError(INVALID,WARNING,name,
				   "getlogfo2() called with O<=0");
    throw e;
  }
  else {
    lnfo2 = 2.*getMu(ODEX);
    lnfo2 -= po2->getGibbs();
    lnfo2 /= 2.302585*R*tk;
    return lnfo2;
  }
}
/* getlnfs2 **********************************/
double SulfLiq::getlogfs2() {
  double lnfs2;
  update();
  if (specs[SDEX]<=0.) {
    PhaseError *e = new PhaseError(INVALID,WARNING,name,
				   "getlogfs2() called with S<=0");
    throw e;
  }
  else {
    lnfs2 = 2.*getMu(SDEX);
    lnfs2 -= ps2->getGibbs();
    lnfs2 /= 2.302585*R*tk;
    return lnfs2;
  }
}


/************************************************
 * SLSSPhase methods ***************************
 ************************************************/
SLSSPhase::SLSSPhase(SLSSData *sd):STR(1300.) {
  dat = sd;
  name = dat->name;
  formula = dat->formula;
  mw = dat->mw;
  Vinet.tr = STR;
  Vinet.pr = pr;
  Vinet.V0 = dat->v1300;
  Vinet.alphaT = dat->dvdt/dat->v1300;
  Vinet.K = -dat->v1300/dat->dvdp; 
  Vinet.Kprime=5.5;
  Phase::init();
  return;
}
double SLSSPhase::getGibbs() {
  double g;
  g = getEnthalpy() - tk*getEntropy();
  return g;
}
 double SLSSPhase::getEnthalpy() {
  double g,h; 
  update();
  g = dat->g0+dat->ge1300;
  h = g + STR*dat->s; // at STR
  h += dat->cp*(tk-STR);
  if (pa>pr) {
    h += Vinet.getMolarEnthalpyPTerm(); //*nmoles;
  }
  return h*nmoles;
}
double SLSSPhase::getEntropy() {
  double s;
  update();
  s=dat->s+dat->cp*log(tk/STR);
  if (pa>pr) {
    s += Vinet.getMolarEntropyPTerm();
  }
  return s*nmoles;
}
double SLSSPhase::getCp() {
  double cp;
  update();
  cp = dat->cp;
  if (pa>pr) {
    cp += Vinet.getMolarCpPTerm();
  }
  return cp*nmoles;
}
double SLSSPhase::getdCpdT() {
  double dd;
  update();
  dd=0.;
  if (pa>pr) {
    dd += Vinet.getMolardCpdTPTerm();
  }
  return dd*nmoles;
}
double SLSSPhase::getVolume() {
  double v;
  update();
  v = Vinet.getMolarVolume();
  v *= nmoles;
  return v;
}
double SLSSPhase::getdVdT() {
  double dd;
  update();
  dd = Vinet.getMolardVdT();
  dd*=nmoles;
  return dd;
}
double SLSSPhase::getd2VdT2() {
  double dd;
  update();
  dd = Vinet.getMolard2VdT2();
  dd *= nmoles;
  return dd;
}
double SLSSPhase::getdVdP() {
  double dvdp;
  update();
  dvdp=Vinet.getMolardVdP();
  dvdp *= nmoles;
  return dvdp;
}
double SLSSPhase::getd2VdTdP() {
  double dd;
  update();
  dd = Vinet.getMolard2VdTdP();
  dd *= nmoles;
  return dd;
}
double SLSSPhase::getd2VdP2() {
  double dd;
  update();
  dd=Vinet.getMolard2VdP2();
  dd *= nmoles;
  return dd;
}
void SLSSPhase::update() {
  if (!updated) {
    Vinet.tk=tk;
    Vinet.pa=pa;
    Vinet.update();
    updated=1;
  }
  return;
}






















