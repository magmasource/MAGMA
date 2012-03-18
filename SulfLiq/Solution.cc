/*
 * Solution class
 * $Id: Solution.cc,v 1.56 2008/05/30 01:15:14 kress Exp $
 */

#include <math.h>
#include <iostream>
#include <string>
#include <stdio.h> 
#include "Solution.h"
#include "NumUtil.h"
#include "ModifiedCholesky.h"
#include "eigensystem.h"

using namespace std;

Solution::Solution() {
  // init must be called by implementing child after ncomp set
  nspec=0;  // overridden in either subclasses or init
  return;
}
Solution::~Solution() {
  // delete constructs allocated in init()
  delete []comps;
  delete []ss;
  free_dmatrix(ncomp,ncomp,hessian);
  delete []indx;
  free_dmatrix(ncomp+1,ncomp+1,A);
  free_dmatrix(ncomp+1,ncomp+1,v);
  delete []w;
  if (eleStoich.nele) delete []eleStoich.ele;
  if (oxStoich.nele) {
    delete []oxStoich.ele;
    delete []formula;
  }
  return;
}
void Solution::init() {
  // Solution::init() must not call Phase::init().
  // This is an exception to general rule of calling parents.
  if (!nspec) nspec=ncomp;
  if (ncomp<=0) {
    PhaseError *e =
      new PhaseError(INVALID,FATAL,name,"Solution has invalid ncomp");
    throw e;
  }
  comps = new double[ncomp];
  hessian = dmatrix(ncomp,ncomp);
  ss = new Phase*[nspec];
  indx = new int[nspec];
  A =dmatrix(ncomp+1,ncomp+1);
  v =dmatrix(ncomp+1,ncomp+1);
  w = new double[ncomp+1];
  // cannot initialize stoichiometric arrays until ss array filled.
  eleStoich.nele=0; // signal that initElOxArrays() has not yet been run
  // initElOxArrays should be called by all implementations after ss set.
  formula = new char[9];
  strncpy(formula,"solution",8);
  return;
}
int Solution::initElOxArrays() {
  int i,j;
  for (i=0;i<Chem::nele;i++) elarray[i]=0.;
  for (i=0;i<ncomp;i++) {
    ss[i]->getAddElements(elarray,1.);
  }
  for (i=0,eleStoich.nele=0;i<Chem::nele;i++) {
    if (elarray[i]>0.) eleStoich.nele++;
  }
  //allocate
  eleStoich.ele = new int[eleStoich.nele];
  eleStoich.stoich = NULL;  // not relevant in solutions
  // fill
  for (i=0,j=0;i<Chem::nele;i++) {
    if (elarray[i]>0.) {
      eleStoich.ele[j++]=i;
    }
  }

  //oxStoich
  //first see if necessary
  j=ss[0]->isOxide();
  for (i=1;i<ncomp;i++) {
    j &= ss[i]->isOxide();
  }
  if (!j) {
    oxStoich.nele=0;
  }
  else {
    double *oxarray = new double[Chem::nox]; 
    Chem::elToOx(elarray,oxarray);
    for (i=0,oxStoich.nele=0;i<Chem::nox;i++) {
      if (oxarray[i]>0.) oxStoich.nele++;
    }
    //allocate
    oxStoich.ele = new int[oxStoich.nele];
    eleStoich.stoich = NULL;  // not relevant in solutions
    // fill
    for (i=0,j=0;i<Chem::nox;i++) {
      if (oxarray[i]>0.) {
	oxStoich.ele[j++]=i;
      }
    }
    delete []oxarray;
  }  // end of oxStoich fill
  return 0;
}

// persistent phase properties ////////////////
int Solution::getNcomp() {
  return ncomp;
}
double Solution::getMW(int i) {
  return ss[i]->getMW();
}
double Solution::getMW() {
  double gfw,n;
  n = getMoles();
  gfw = getMass()/n;
  return gfw;
}
const char *Solution::getCompName(int i) {
  if (i<0||i>ncomp) {
    return NULL;
  }
  else {
    return ss[i]->name;
  }
}
const char *Solution::getCompFormula(int i) {
  if (i<0||i>ncomp) {
    return NULL;
  }
  else {
    return ss[i]->formula;
  }
}
int Solution::getCompNo(char *lab) {
  int i;
  for (i=0;i<ncomp;i++) {
    if (strcmp(getCompName(i),lab)==0) {
      return i;
    }
  }
  return -1;
}

// setting methods ///////////////////////////
void Solution::setTk(double ltk) {
  int i;
  tk=ltk;

  for (i=0;i<ncomp;i++) {
    ss[i]->setTk(tk);
  }
  updated=0;
  return;
}
void Solution::setPa(double lpa) {
  int i;
  pa=lpa;
  for (i=0;i<ncomp;i++) {
    ss[i]->setPa(pa);
  }
  updated=0;
  return;
}
void Solution::setMoles(double m) throw(PhaseError *) {
  int i;
  double sum;
  nmoles = m;
  for (i=0,sum=0.0;i<ncomp;i++) {
    sum += comps[i];
  }
  for (i=0;i<ncomp;i++) {
    comps[i] *= nmoles/sum;
  }
  updated=0;
  return;
}
void Solution::setMass(double w) {
  double n,gm,r;
  n=getMoles();
  gm = getMass();
  r=w/gm;
  setMoles(n*r);
  return;
}
void Solution::setComps(double *lcomps) {
  int i;
  for (i=0,nmoles=0.;i<ncomp;i++) {
    comps[i]=lcomps[i];
    nmoles += comps[i];
  }
  index();
  getMoles(); // to set nmoles
  updated=0;
  return;
}
void Solution::setCompWeights(double *wt) {
  int i;
  double *mol;
  mol = new double[ncomp];
  for (i=0;i<ncomp;i++) {
    mol[i]=wt[i]/getMW(i);
  }
  setComps(mol);
  delete []mol;
  return;
}
void Solution::setCompWtPct(double *wt) {
  setCompWeights(wt);
  setMoles(1.0);
  return;
}
void Solution::setElements(double *ele) throw(PhaseError *) {
  int i;
  for (i=0;i<ncomp;i++) {    // set all component objects
    ss[i]->setElements(ele); // remember that this resets comp nmoles.
                             // Each component will take max from ele. 
  }
  for (i=0;i<ncomp;i++) {
    w[i] = ss[i]->getMoles();// using w array as working space (dangerous)
    ss[i]->setMoles(1.0);// very important. Solution calls expect molar q.
  }
  for (i=0;i<eleStoich.nele;i++) {
    if (ele[i]<0.) {
      PhaseError *e = 
	new PhaseError(BOUNDS,WARNING,name,"Negative element in setElements");
      throw e;
    }
  }
  setComps(w); //remember w is holding comps here (see above).
  return;
}
void Solution::resetTPbounds(double lowTbound,double hiTbound,
			     double lowPbound,double hiPbound) {
  int i;
  Phase::resetTPbounds(lowTbound,hiTbound,lowPbound,hiPbound);
  for (i=0;i<nspec;i++) {
    ss[i]->resetTPbounds(lowTbound,hiTbound,lowPbound,hiPbound);
  }
  return;
}




// getting methods ////////////////////////
double Solution::getMoles() {
  int i;
  double m;
  update();
  for (i=0,m=0.;i<ncomp;i++) {
    m += comps[i];
  }
  nmoles = m;
  return m;
}
double Solution::getMass() {
  int i;
  double gm;
  update();
  for (i=0,gm=0.;i<ncomp;i++) {
    gm += comps[i]*ss[i]->getMW();
  }
  return gm;
}
void Solution::getComps(double *lcomps) {
  int i;
  update();
  for (i=0;i<ncomp;i++) {
    lcomps[i]=comps[i];
  }
  return;
}
void Solution::getCompWeights(double *wt) {
  int i;
  update();
  for (i=0;i<ncomp;i++) wt[i] = comps[i]*getMW(i);  
  return;
}
void Solution::getCompWtPct(double *wt) {
  double sum;
  int i;
  update();
  for (i=0;i<ncomp;i++) wt[i] = comps[i]*getMW(i);
  for (i=0,sum=0.;i<ncomp;i++) sum += wt[i];
  sum /= 100.;
  for (i=0;i<ncomp;i++) wt[i]/=sum;
  return;
}
void Solution::getElements(double *lele) {
  int i;
  update();
  for (i=0;i<Chem::nele;i++) lele[i]=0.;
  for (i=0;i<ncomp;i++) {
    ss[i]->getAddElements(lele,comps[i]);
  }
  return;
}
void Solution::getAddElements(double *lele,double mol) {
  int i;
  update();
  for (i=0;i<ncomp;i++) {
    ss[i]->getAddElements(lele,comps[i]*mol);
  }
  return;
}

// Gibbs and derivatives
double Solution::getGibbs() {
  int i;
  double g;
  update();
  g=0.;
  for (i=0;i<ncomp;i++) {
    g += comps[i]*getMu(i);
  }
  return g;
}
double Solution::getMu0(int i) {
  update();
  if (i>=0&&i<ncomp) {
    return ss[i]->getGibbs();
  }
  else {
    cout << "\ncomp index out of range error in Solution::getmu0";
    return 0.;
  }
}
void Solution::getMu0(double *m0) {
  int i;
  update();
  for (i=0;i<ncomp;i++) {
    m0[i]=getMu0(i);
  }
  return;
}
double Solution::getMu(int icomp) {
  // Assuming ideal solution for now
  double mu;
  update();
  if (icomp<0||icomp>ncomp) {
    cout << "\nSolution getMu recieved out of range component number";
    return 0.;
  }
  else {
    mu = (comps[icomp]>0.)? getMu0(icomp) + R*tk*log(comps[icomp]/nmoles) : 0.;
    return mu;
  } 
}
void Solution::getMu(double *mu) {
  int i;
  update();
  for (i=0;i<ncomp;i++) {
    mu[i]=getMu(i);
  }
  return;
}
double Solution::getActivity(int icomp) {
  double lnact;
  update();
  if (icomp<0||icomp>ncomp) {
    return 0.;
  }
  else if (comps[icomp]<=0.) {
    return 0.;
  }
  else {
    lnact = getMu(icomp) - getMu0(icomp);
    lnact /= R*tk;
    return exp(lnact);
  }
}
void Solution::getActivity(double *a) {
  int i;
  update();
  for (i=0;i<ncomp;i++) {
    a[i]=getActivity(i);
  }
  return;
}
double Solution::getdMudX(int i,int j) {
  //ideal solution assumed for base class
  double xs;
  update();
  xs = (i==j)? nmoles/comps[i] : nmoles/(nmoles-comps[j]);
  xs *= -R*tk;
  return xs;
}
double Solution::getdMudP(int i) {
  update();
  return ss[i]->getVolume();
}
void Solution::getdGdm(double *dgdm) {
  int i;
  update();
  for (i=0;i<ncomp;i++) {
    dgdm[i]=getMu(i);
  }
  return;
}
void Solution::getd2Gdm2(double **d2gdm2) {
  // from 3/20/99 calculations
  int i,j;
  update();
  for (i=0;i<ncomp;i++) {
    for (j=i;j<ncomp;j++) {
      double temp;
      temp = (i==j)? 1.-comps[i]/nmoles : -comps[i]/nmoles;
      d2gdm2[i][j] = R*tk*temp/comps[i];
      if (i!=j) {
	d2gdm2[j][i]=d2gdm2[i][j];
      }
    }
  }
  return;
}
void Solution::getd3Gdm3(double ***d3gdm3) {
  // from 9/4/03 calculations
  int m,i,j;
  double temp;
  update();
  for (m=0;m<ncomp;m++) {
    for (i=0;i<ncomp;i++) {
      for (j=0;j<ncomp;j++) {
	temp = -DIRAC(j,m)*(DIRAC(i,m)-comps[m]/nmoles)/comps[m];
	temp -= (DIRAC(m,j)-comps[m]/nmoles)/nmoles;
	d3gdm3[m][i][j] = temp*R*tk/comps[m];
      }
    }
  }
  return;
}
double Solution::getGmix() {
  double gmx;
  update();
  gmx = getHmix() - tk*getSmix();
  return gmx;
}
void Solution::getHessian(double **h) {
  double **H;
  int i,j;
  update();
  H=getHessian();
  for (i=0;i<ncomp;i++) {
    for (j=0;j<ncomp;j++) {
      h[i][j]=H[i][j];
    }
  }
  return;
}
double **Solution::getHessian() {
  //  int i,j;
  update();
  getd2Gdm2(hessian);
  return hessian;
}

// Enthalpy and derivatives
double Solution::getEnthalpy() {
  int i;
  double h;
  update();
  for (i=0,h=0.;i<ncomp;i++) {
    h += comps[i]*(ss[i]->getEnthalpy());  // assume ideal
  }
  h += getHmix();
  return h;
}

// Entropy and derivatives
double Solution::getEntropy() {
  int i;
  double s;
  update();
  for (i=0,s=0.;i<ncomp;i++) {
    s += comps[i]*(ss[i]->getEntropy());
  }
  s += getSmix();
  return s;
}
void Solution::getdSdm(double *dsdm) {
  int i;
  update();
  for (i=0;i<ncomp;i++) {
    dsdm[i]=(ss[i]->getEntropy())-R*log(comps[i]/nmoles);
  }
  return;
}
void Solution::getd2Sdm2(double **d2sdm2) {
  int i,j;
  update();
  for (i=0;i<ncomp;i++) {
    for (j=i;j<ncomp;j++) {
      double temp;
      temp = (i==j)? 1.-comps[i]/nmoles : -comps[i]/nmoles;
      d2sdm2[i][j] = -R*temp/comps[i];
      if (i!=j) {
	d2sdm2[j][i]=d2sdm2[i][j];
      }
    }
  }
  return;
}
double Solution::getSmix() {
  int i;
  double smx;
  update();
  for (i=0,smx=0.;i<ncomp;i++) {
    smx-=comps[i]*log(comps[i]/nmoles);
  }
  smx *= R;
  return smx;
}

// Cp and derivatives
double Solution::getCp() {
  int i;
  double cp;
  update();
  for (i=0,cp=0.;i<ncomp;i++) {
    cp += comps[i]*(ss[i]->getCp());
  }
  return cp;
}
double Solution::getdCpdT() {
  int i;
  double dcpdt;
  update();
  for (i=0,dcpdt=0.;i<ncomp;i++) {
    dcpdt += comps[i]*(ss[i]->getdCpdT());
  }
  return dcpdt;
}
void Solution::getdCpdm(double *dcpdm) {
  int i;
  update();
  for (i=0;i<ncomp;i++) {
    dcpdm[i]=(ss[i]->getCp());
  }
  return;
}

// Volume and derivatives
double Solution::getVolume() {
  int i;
  double v;
  update();
  for (i=0,v=0.;i<ncomp;i++) {
    v += comps[i]*(ss[i]->getVolume());
  }
  v += getVmix();
  return v;
}
void Solution::getdVdm(double *dvdm) {
  int i;
  update();
  for (i=0;i<ncomp;i++) {
    dvdm[i]=(ss[i]->getVolume());
  }
  return;
}
void Solution::getd2Vdm2(double **d2vdm2) {
  int i,j;
  update();
  for (i=0;i<ncomp;i++) {
    for (j=0;j<ncomp;j++) {
      d2vdm2[i][j]=0.;
    }
  }
  return;
}
double Solution::getdVdT() {
  int i;
  double dvdt;
  update();
  for (i=0,dvdt=0.;i<ncomp;i++) {
    dvdt += comps[i]*(ss[i]->getdVdT());
  }
  return dvdt;
}
double Solution::getdVdP() {
  int i;
  double dvdp;
  update();
  for (i=0,dvdp=0.;i<ncomp;i++) {
    dvdp += comps[i]*(ss[i]->getdVdP());
  }
  return dvdp;
}
double Solution::getd2VdT2() {
  int i;
  double d2vdt2;
  update();
  for (i=0,d2vdt2=0.;i<ncomp;i++) {
    d2vdt2 += comps[i]*(ss[i]->getd2VdT2());
  }
  return d2vdt2;
}
double Solution::getd2VdTdP() {
  int i;
  double d2vdtdp;
  update();
  for (i=0,d2vdtdp=0.;i<ncomp;i++) {
    d2vdtdp += comps[i]*(ss[i]->getd2VdTdP());
  }
  return d2vdtdp;
}
double Solution::getd2VdP2() {
  int i;
  double d2vdp2;
  update();
  for (i=0,d2vdp2=0.;i<ncomp;i++) {
    d2vdp2 += comps[i]*(ss[i]->getd2VdP2());
  }
  return d2vdp2;
}
void Solution::getd2VdmdT(double *d2vdmdt) {
  int i;
  update();
  for (i=0;i<ncomp;i++) {
    d2vdmdt[i] = (ss[i]->getdVdT());
  }
  return;
}
void Solution::getd2VdmdP(double *d2vdmdp) {
  int i;
  update();
  for (i=0;i<ncomp;i++) {
    d2vdmdp[i] = (ss[i]->getdVdP());
  }
  return;
}

// utility functions /////////////////////
int Solution::isStable() {
  double **H;
  int i,j,stable;
  update();
  H = getHessian();
  for (i=0;i<lcomp;i++) {      // eliminate zero components
    for (j=0;j<lcomp;j++) {
      H[i][j]=H[indx[i]][indx[j]];
    }
  }
  eigensystem(H,lcomp,A,w,v);
  for (i=stable=1;i<lcomp&&stable==1;i++) {
    stable = (w[i]>0.);
  }
  return stable;
}
void Solution::testHessian(double step) {
  double *mu00,*comp00,**H;
  int i,j;
  update();
  mu00 = new double[ncomp];
  comp00 = new double[ncomp];
  getComps(comp00);
  update();
  H=getHessian();
  for (i=0;i<ncomp;i++) {
    mu00[i] = getMu(i);
  }
  printf("\n");
  for (i=0;i<ncomp;i++) {
    printf(" %10.8s",getCompName(i));
  }
  printf("\n");
  for (i=0;i<ncomp;i++) {
    printf(" %10.0f",mu00[i]);
  }
  printf("\nDelta predicted from Hessian followed by observed");
  for (j=0;j<ncomp;j++) {
    if (comp00[j]>0.) {
      double temp;
      printf("\ndelta %10.8s\n",getCompName(j));
      temp=comp00[j];
      comp00[j]+=step;
      setComps(comp00);
      comp00[j]=temp;
      update();
      for (i=0;i<ncomp;i++) {
      printf(" %10.0f",H[i][j]*step);
      }
      printf("\n");
      for (i=0;i<ncomp;i++) {
	printf(" %10.0f",getMu(i)-mu00[i]);
      }
    }
  }
  printf("\n");
  delete []comp00;
  delete []mu00;
  return;
}
void Solution::update() {
  int i;
  if (!updated) {
    for (i=0;i<ncomp;i++) {
      ss[i]->update();
    }
    updated=1;
  }
  return;
}
void Solution::printAll() {
  int i,j;
  double **H;
  update();
  Phase::printAll();
  printf("components\n");
  printf("%15s %15s %10s %10s %10s %10s %10s\n",
	 "name","formula","mols[i]","x[i]","a[i]","mu0[i](kJ)","mu[i](kJ)");
  for (i=0;i<ncomp;i++) {
    printf("%15s %15s %10.4f %10.4f %10.4f %10.4f %10.4f\n",
	   getCompName(i),getCompFormula(i),
	   comps[i],comps[i]/nmoles,
	   getActivity(i),getMu0(i)/1000.,getMu(i)/1000.);
  }
  H=getHessian();
  printf("\nComponent Hessian (kJ)\n");
  for (i=0;i<ncomp;i++) {
    for (j=0;j<ncomp;j++) {
      printf("%10.4f ",H[i][j]/1000.);
    }
    printf("\n");
  }
  i=isStable();
  if (!i) printf("un");
  printf("stable phase\n");
  return;
}
void Solution::index() {
  int i;
  if (!eleStoich.nele) { // this should have been run in constructor,
    initElOxArrays();    // but if not we can run it now.
  }
  for (i=lcomp=lspec=0;i<ncomp;i++) {
    if (comps[i]>0.0) {
      indx[lcomp] = i;
      lcomp++;
    }
  }
  lspec=lcomp;
  return;
}


