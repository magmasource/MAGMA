/*
 *SpecSolution class generic implementation
 *Victor Kress
 *$Id: SpecSolution.cc,v 1.51 2007/11/30 09:25:52 kress Exp $
 *@version $Revision: 1.51 $
 */

#include <iostream>
#include <float.h>
#include <math.h>
#include "SpecSolution.h"
#include "NumUtil.h"
#include "svdSolve.h"
#include "svdInv.h"

using namespace std;

SpecSolution::SpecSolution() {
  // init must be called by implementing child after ncomp and nspec set
  verbose=0;  //default
  specCharge=NULL; // default reset in implementing class if charged species
  return;
}
SpecSolution::~SpecSolution() {
  // delete constructs allocated in init()
  delete []specs;
  free_dmatrix(nspec,ncomp,spstoich);
  free_dmatrix(nspec,nspec-ncomp,nu);
  delete []rdx;
  delete []rhs;
  delete []psi;
  delete []b;
  delete []bm;
  delete []delta;
  delete []mu;
  free_dmatrix(nspec,nspec,dmuds);
  free_dmatrix(nspec,nspec,K);
  free_dmatrix(nspec,nspec,m1);
  free_dmatrix(nspec,nspec,m2);
  free_dmatrix(nspec,nspec,m3);
  free_dmatrix3d(nspec,nspec,nspec,mmm);
  delete []v1;
  delete []v2;
  delete []supressSpec;
  return;
}
void SpecSolution::init() {
  int i;
  updated=0;
  spectol=1.e-15;
  Solution::init();
  if (nspec<=0) {
    PhaseError *e =
      new PhaseError(INVALID,FATAL,name,"SpecSolution has invalid nspec");
    throw e;
  }
  specs = new double[nspec];
  spstoich = dmatrix(nspec,ncomp);
  nu = dmatrix(nspec,nspec-ncomp);
  rdx = new int[nspec-ncomp];
  rhs = new double[ncomp+1];
  psi = new double[ncomp+1];
  b = new double[ncomp];
  bm = new double[ncomp];
  delta = new double[nspec];
  mu = new double[nspec];
  dmuds = dmatrix(nspec,nspec);
  K = dmatrix(nspec,nspec);
  m1 = dmatrix(nspec,nspec);
  m2 = dmatrix(nspec,nspec);
  m3 = dmatrix(nspec,nspec);
  mmm = dmatrix3d(nspec,nspec,nspec);
  v1 = new double[nspec];
  v2 = new double[nspec];
  supressSpec = new int[nspec];
  for (i=0;i<nspec;i++) supressSpec[i]=0;
  return;
}

// persistent phase properties ////////////////
int SpecSolution::getNspec() {
  return nspec;
}
const char *SpecSolution::getSpecName(int i) {
  return ss[i]->name;
}
const char *SpecSolution::getSpecFormula(int i) {
  return ss[i]->formula;
}

// setting methods ////////////////////////////
void SpecSolution::setTk(double ltk) {
  int i,resetSpecs;
  checkT(ltk);
  tk=ltk;
  resetSpecs=0; // This is a flag to indicate that species suppression has changed and specs needs to be refilled.
  for (i=0;i<nspec;i++) {
    if (!(SUPRESS && supressSpec[i])) { // don't bother if global supress
      try {
	ss[i]->setTk(tk);
	if (TSUPRESS && supressSpec[i]) { // Used to be tsupressed, but not now
	  resetSpecs++;                   // will need to clean up speciation
	  supressSpec[i] &= !TSUPRESS;    // unset tsupress bit
	}
      } catch(PhaseError *e) {
	if (e->type==BOUNDS) { // this species out of bounds. Supress.
	  if (i<ncomp) { // can't supress component species
	    cout << "Error: attempt to set T out of bounds for component";
	    throw e;
	  }
	  supressSpec[i] |= TSUPRESS;
	  resetSpecs++;
	}
	else {
	  throw e;
	}
      }
    }
  }
  if (resetSpecs) {
    fillSpecs();  // update species in light of new state of spec suppression
    index();
  }
  updated=0;
  return;
}
void SpecSolution::setPa(double lpa) {
  int i,resetSpecs;
  checkP(lpa);
  pa=lpa;
  resetSpecs=0; // This is a flag to indicate that species suppression has changed and specs needs to be refilled.
  for (i=0;i<nspec;i++) {
    if (!(SUPRESS && supressSpec[i])) { // don't bother if global supress
      try {
	ss[i]->setPa(pa);
 	if (PSUPRESS && supressSpec[i]) { // Used to be tsupressed, but not now
	  resetSpecs++;                   // will need to clean up speciation
	  supressSpec[i] &= !PSUPRESS;    // unset tsupress bit
	}
     } catch(PhaseError *e) {
	if (e->type==BOUNDS) { // this species out of bounds. Supress.
	  if (i<ncomp) { // can't supress component species
	    cout << "Error: attempt to set P out of bounds for component";
	    throw e;
	  }
	  supressSpec[i] |= PSUPRESS;
	  resetSpecs++;
	}
	else {
	  throw e;
	}
      }
    }
  }
  if (resetSpecs) {
    fillSpecs();  // update species in light of new state of spec suppression
    index();
  }
  updated=0;
  return;
}
void SpecSolution::setMoles(double m) throw(PhaseError *) {
  int i;
  double oldNmoles;
  oldNmoles=getMoles();
  Solution::setMoles(m);
  for (i=0;i<nspec;i++) {
    specs[i] *= m/oldNmoles;
  }
  for (i=0,specSum=0.;i<nspec;i++) specSum += specs[i];
  updated=0;
  return;
}
void SpecSolution::setComps(double *lcomps) {
  int i;
  for (i=0,nmoles=0.;i<ncomp;i++) {
    comps[i]=lcomps[i];
    nmoles += comps[i];
  }
  fillSpecs();
  index();
  getMoles();  // to set nmoles
  updated=0;
  return;
}
void SpecSolution::setSpecs(double *modelspecs) {
  int i;
  for (i=0;i<nspec;i++) {
    specs[i]=modelspecs[i];
  }
  for (i=0,specSum=0.;i<nspec;i++) specSum += specs[i];
  fillComps();
  index();
  updated=0;
  return;
}
void SpecSolution::setSpecsFull(double *modelspecs) {
  int i;
  for (i=0;i<nspec;i++) {
    specs[i]=modelspecs[i];
  }
  fillComps();
  fillSpecs();
  index();
  updated=0;
  return;
}

// getting methods ////////////////////////////////////
void SpecSolution::getSpecs(double *modelspecs) {
  int i;
  update();
  for (i=0;i<nspec;i++) {
    modelspecs[i]=specs[i];
  }
}
// Gibbs and derivatives
double SpecSolution::getGibbs() {
  /* This could almost have been inhereted from Solution, as only component
     potentials are relevant. Main difference is call to update.*/
  int i;
  double g;
  update();
  g=0.;
  for (i=0;i<ncomp;i++) {
    if (comps[i]>0.) {
      g += comps[i]*getSpecMu(i);
    }
  }
  return g;
}
double SpecSolution::getMu0(int i) {
  if (i>=0&&i<nspec) {
    return ss[i]->getGibbs();
  }
  else {
    cout << "\nspec index out of range error in SpecSolution::getMu0";
    return 0.;
  }
}
double SpecSolution::getMu(int i) {
  // update called in getSpecMu
  if (i>=0&&i<nspec) {
    return getSpecMu(i);
  }
  else {
    cout << "\nspec index out of range error in SpecSolution::getMu";
    return 0.;
  }
}
double SpecSolution::getCompMu(int icomp) {
  update();
  if (icomp<0||icomp>ncomp) {
    cout << "\nSpecSolution::getCompMu recieved out of range component number";
    return 0.;
  }
  else {
    return getSpecMu(icomp);
  }
}  
double SpecSolution::getSpecMu(int ispec) {
  // Assuming ideal solution for now
  double mu;
  update();
  if (ispec<0||ispec>nspec) {
    cout << "\nSpecSolution::getSpecMu recieved out of range species number";
    return 0.;
  }
  else {
    mu = (specs[ispec]>0.)? getMu0(ispec)+R*tk*log(specs[ispec]/specSum) : 0.;
    return mu;
  } 
}
double SpecSolution::getdMudX(int i,int j) {
  (void) getHessian(); // calls its own update()
  return hessian[i][j];
}
void SpecSolution::getd2Gdm2(double **h) {
  int i,j,k,l,r;

  r=nuRank;
  update();
  updateTransformKernel();  //brings K and dmuds up to date

  for (i=0;i<ncomp;i++) {
    for (j=0;j<ncomp;j++) {
      h[i][j]=0.;
    }
  }
  for (i=0;i<lcomp;i++) {
    for (j=0;j<lcomp;j++) {
      h[indx[i]][indx[j]]=dmuds[i][j];
    }
  }

  if (r>0) {
    for (i=0;i<lcomp;i++) {
      for (j=0;j<lcomp;j++) {
	for (k=0;k<lspec;k++) {
	  for (l=0;l<lspec;l++) {
	    h[indx[i]][indx[j]] -= dmuds[i][k]*K[k][l]*dmuds[l][j];
	  }
	}
      }
    }
  }
  return;
}
void SpecSolution::getd3Gdm3(double ***d3gdm3) {
  int m,i,j,k,l,p,r;
  // see 10/17/03 calculations
  update();
  updateTransformKernel();  //brings K and dmuds up to date

  r=nuRank;

  getd3Gds3(mmm);
  // first term
  for (m=0;m<ncomp;m++) {
    for (i=0;i<ncomp;i++) {
      for (j=0;j<ncomp;j++) {
	d3gdm3[m][i][j]=0.;
      }
    }
  }
  for (m=0;m<lcomp;m++) {
    for (i=0;i<lcomp;i++) {
      for (j=0;j<lcomp;j++) {
	d3gdm3[indx[m]][indx[i]][indx[j]]=mmm[m][i][j];
      }
    }
  }
  // second term
  for (m=0;m<lcomp;m++) {
    for (i=0;i<lcomp;i++) {
      for (j=0;j<lcomp;j++) {
	for (k=0;k<lspec;k++) {
	  for (p=0;p<lspec;p++) {
	    d3gdm3[indx[m]][indx[i]][indx[j]] -=
	      2.*mmm[m][i][p]*K[p][k]*dmuds[k][j];
	  }
	}
      }
    }
  }
  // third term
  /* (nuTdmudsnu)-1 */
  for (i=0;i<r;i++) {
    for (j=0;j<r;j++) {
      m1[i][j] = 0.;
      for (k=0;k<lspec;k++) {
	for (l=0;l<lspec;l++) {
	  m1[i][j] += nu[k][i]*dmuds[k][l]*nu[l][j];
	}
      }
    }
  }

  svdInv(m1,r,r,m2,v2,m3,1.e-7);  // m1 now holds Z-1 in 9/11/03 calculations

  for (m=0;m<lcomp;m++) {
    for (i=0;i<r;i++) {
      for (j=0;j<r;j++) {
	m2[i][j] = 0.;
	for (k=0;k<lspec;k++) {
	  for (l=0;l<lspec;l++) {
	    m2[i][j] += nu[k][i]*mmm[m][k][l]*nu[l][j];
	  }
	}
      }
    }                               // m2 now holds dZ/ds
    for (i=0;i<r;i++) {
      for (j=0;j<r;j++) {
	m3[i][j]=0.;
	for (k=0;k<r;k++) {
	  for (p=0;p<r;p++) {
	    m3[i][j] -= m1[i][k]*m2[k][p]*m1[p][j];
	  }
	}
      }
    }
    for (i=0;i<lspec;i++) {
      for (j=0;j<lspec;j++) {
	m1[i][j]=0.;
	for (k=0;k<r;k++) {
	  for (p=0;p<r;p++) {
	    m1[i][j] += nu[i][k]*m3[k][p]*nu[p][j];
	  }
	}
      }
    }
    for (i=0;i<lcomp;i++) {
      for (j=0;j<lcomp;j++) {
	for (k=0;k<lspec;k++) {
	  for (p=0;p<lspec;p++) {
	    d3gdm3[indx[m]][indx[i]][indx[j]] -= 
	      dmuds[i][k]*m1[k][p]*dmuds[p][j];
	  }
	}
      }
    }
  }
    
  return;
}

double SpecSolution::getGmix() {
  int i;
  double gmx;
  update();
  gmx=getGibbs();
  for (i=0;i<ncomp;i++) {
    if (comps[i]>0.) {
      gmx -= comps[i]*(ss[i]->getGibbs());
    }
  }
  return gmx;
}

// enthalpy and derivatives
double SpecSolution::getEnthalpy() {
  /* unlike Solution, bulk properties are calculated without call to
     mixing properties.  This is because mixing properties are
     referenced to COMPONENT mixing, while here we are interested in
     properties of a large collection of species.  Mixing properties in
     SpecSolution and subclasses are calculated from bulk properties minus
     contribution from component standard states.*/
  int i;
  double h;
  update();
  for(i=0,h=0.;i<nspec;i++) {
    if (specs[i]>0.) {
      h+=specs[i]*(ss[i]->getEnthalpy());
    }
  }
  return h;
}
double SpecSolution::getHmix() {
  int i;
  double hmx;
  update();
  hmx=getEnthalpy();
  for (i=0;i<ncomp;i++) {
    if (comps[i]>0.) {
      hmx -= comps[i]*(ss[i]->getEnthalpy());
    }
  }
  return hmx;
}

// entropy and derivatives
double SpecSolution::getEntropy() {
  /* unlike Solution, bulk properties are calculated without call to
     mixing properties.  This is because mixing properties are
     referenced to COMPONENT mixing, while here we are interested in
     properties of a large collection of species.  Mixing properties in
     SpecSolution and subclasses are calculated from bulk properties minus
     contribution from component standard states.
  */
  int i;
  double s;
  //double sum;
  update();
  /* This is tricky.  See Kress (2003)*/
  for(i=0,s=0.;i<nspec;i++) {
    if (specs[i]>0.) {
      s+=specs[i]*(ss[i]->getEntropy()-R*log(specs[i]/specSum));
    }
  }
  // ideal mixing of species assumed here so next should be equivalent.
  //s = (getEnthalpy() - getGibbs())/tk;
  return s;
}
void SpecSolution::getdSdm(double *dsdm) {
  int i,k,l,r;

  r=nuRank;
  update();
  updateTransformKernel();  //brings K and dmuds up to date
  getdSds(v1);

  for (i=0;i<ncomp;i++) dsdm[i]=0.;

  for (i=0;i<lcomp;i++) {
    dsdm[indx[i]]=v1[i];
  }

  if (r>0) {
    for (i=0;i<lcomp;i++) {
      for (k=0;k<lspec;k++) {
	for (l=0;l<lspec;l++) {
	  dsdm[indx[i]] -= 
	    v1[k]*K[k][l]*dmuds[l][i];
	}
      }
    }
  }
  return;
}
void SpecSolution::getd2Sdm2(double **d2sdm2) {
  int i,j,k,l,p,r,m;
  // see 10/22/03 calculations
  update();
  updateTransformKernel();
  getd3Gds3(mmm);
  r=nuRank;
  for (i=0;i<ncomp;i++) {
    for (j=0;j<ncomp;j++) {
      d2sdm2[i][j]=0.;
    }
  }

  // first term
  getd3Gds2dT(m1);
  for (i=0;i<lcomp;i++) {
    for (j=0;j<lcomp;j++) {
      d2sdm2[indx[i]][indx[j]] = m1[i][j];
    }
  }

  // second term
  for (i=0;i<lcomp;i++) {
    for (j=0;j<lcomp;j++) {
      for (k=0;k<lspec;k++) {
	for (l=0;l<lspec;l++) {
	  d2sdm2[indx[i]][indx[j]] -= m1[i][k]*K[k][l]*dmuds[l][j];
	}
      }
    }
  }

  // third term
  getdSds(v1);  
  /* (nuTdmudsnu)-1 */
  for (i=0;i<r;i++) {
    for (j=0;j<r;j++) {
      m1[i][j] = 0.;
      for (k=0;k<lspec;k++) {
	for (l=0;l<lspec;l++) {
	  m1[i][j] += nu[k][i]*dmuds[k][l]*nu[l][j];
	}
      }
    }
  }

  svdInv(m1,r,r,m2,v2,m3,1.e-7);  // m1 now holds Z-1 in 9/11/03 calculations

  for (m=0;m<lcomp;m++) {
    for (i=0;i<r;i++) {
      for (j=0;j<r;j++) {
	m2[i][j] = 0.;
	for (k=0;k<lspec;k++) {
	  for (l=0;l<lspec;l++) {
	    m2[i][j] += nu[k][i]*mmm[m][k][l]*nu[l][j];
	  }
	}
      }
    }                               // m2 now holds dZ/ds
    for (i=0;i<r;i++) {
      for (j=0;j<r;j++) {
	m3[i][j]=0.;
	for (k=0;k<r;k++) {
	  for (p=0;p<r;p++) {
	    m3[i][j] -= m1[i][k]*m2[k][p]*m1[p][j];
	  }
	}
      }
    }
    for (i=0;i<lspec;i++) {
      for (j=0;j<lspec;j++) {
	m1[i][j]=0.;
	for (k=0;k<r;k++) {
	  for (p=0;p<r;p++) {
	    m1[i][j] += nu[i][k]*m3[k][p]*nu[p][j];
	  }
	}
      }
    }
    for (i=0;i<lcomp;i++) {
      for (k=0;k<lspec;k++) {
	for (p=0;p<lspec;p++) {
	  d2sdm2[indx[m]][indx[i]] -= v1[k]*m1[k][p]*dmuds[p][i];
	}
      }
    }
  }


  // fourth term
  getd3Gds3(mmm);
  for (i=0;i<lcomp;i++) {
    for (j=0;j<lcomp;j++) {
      for (k=0;k<lspec;k++) {
	for (l=0;l<lspec;l++) {
	  d2sdm2[indx[i]][indx[j]] -= v1[k]*K[k][l]*mmm[l][i][j];//????
	}
      }
    }
  }

  return;
}
double SpecSolution::getSmix() {
  int i;
  double smx;
  update();
  smx=getEntropy();
  for (i=0;i<ncomp;i++) {
    if (comps[i]>0.) {
      smx -= comps[i]*(ss[i]->getEntropy());
    }
  }
  return smx;
}

double SpecSolution::getCp() {
  int i,j;
  double cp;
  // Cp = T(dSdT)
  update();
  updateTransformKernel();  //brings K and dmuds up to date
  getdSds(v1);

  // T(dS/dT)_xi
  for (i=0,cp=0.;i<lspec;i++) {
    cp += ss[indx[i]]->getCp()*specs[indx[i]];
  }

  for (i=0;i<lspec;i++) {
    for (j=0;j<lspec;j++) {
      cp += tk*v1[i]*K[i][j]*v1[j];
    }
  }
  return cp;
}
double SpecSolution::getdCpdT() {
  // see 10/23/03 calculations
  double dcpdt;
  int i,j,k,l,p,r;
  update();
  updateTransformKernel();   //brings K and dmuds up to date

  r=nuRank;
  getdSds(v1);
  dcpdt=0.;

  // first term
  for (i=0;i<lspec;i++) {
    dcpdt = ss[indx[i]]->getdCpdT()*specs[indx[i]];
  }
  // second term
  for (i=0;i<lspec;i++) {
    for (j=0;j<lspec;j++) {
      dcpdt += v1[i]*K[i][j]*v1[j];
    }
  }
  // third and fourth term
  for (i=0;i<lspec;i++) {
    for (j=0;j<lspec;j++) {
      dcpdt += (ss[indx[i]]->getCp())*K[i][j]*v1[j];
      dcpdt += v1[i]*K[i][j]*(ss[indx[j]]->getCp());
    }
  }

  // fifth term
  /* (nuTdmudsnu)-1 */
  for (i=0;i<r;i++) {
    for (j=0;j<r;j++) {
      m1[i][j] = 0.;
      for (k=0;k<lspec;k++) {
	for (l=0;l<lspec;l++) {
	  m1[i][j] += nu[k][i]*dmuds[k][l]*nu[l][j];
	}
      }
    }
  }                               // m1 holds Z

  svdInv(m1,r,r,m2,v2,m3,1.e-7);  // m1 now holds Z-1 in 9/11/03 calculations

  getd3Gds2dT(m3);           
  for (i=0;i<r;i++) {
    for (j=0;j<r;j++) {
      m2[i][j] = 0.;
      for (k=0;k<lspec;k++) {
	for (l=0;l<lspec;l++) {
	  m2[i][j] += nu[k][i]*m3[k][l]*nu[l][j];
	}
      }
    }
  }                               // m2 now holds dZ/dT
  for (i=0;i<r;i++) {
    for (j=0;j<r;j++) {
      m3[i][j]=0.;
      for (k=0;k<r;k++) {
	for (p=0;p<r;p++) {
	  m3[i][j] -= m1[i][k]*m2[k][p]*m1[p][j];
	}
      }
    }
  }
  for (i=0;i<lspec;i++) {
    for (j=0;j<lspec;j++) {
      m1[i][j]=0.;
      for (k=0;k<r;k++) {
	for (p=0;p<r;p++) {
	  m1[i][j] += nu[i][k]*m3[k][p]*nu[p][j];
	}
      }
    }
  }
  for (i=0;i<lspec;i++) {
    for (j=0;j<lspec;j++) {
      dcpdt += tk*v1[i]*m1[i][j]*v1[j];
    }
  }
    
  return dcpdt;
}
double SpecSolution::getCpmix() {
  int i;
  double cpmx;
  update();
  cpmx=getCp();
  for (i=0;i<ncomp;i++) {
    if (comps[i]>0.) {
      cpmx -= comps[i]*(ss[i]->getCp());
    }
  }
  return cpmx;
}
double SpecSolution::getdCpdTmix() {
  int i;
  double dcpdtmx;
  update();
  dcpdtmx=getdCpdT();
  for (i=0;i<ncomp;i++) {
    if (comps[i]>0.) {
      dcpdtmx -= comps[i]*(ss[i]->getdCpdT());
    }
  }
  return dcpdtmx;
}
// volume and derivatives
double SpecSolution::getVolume() {
  /* unlike solution, bulk properties are calculated without call to
     mixing properties.  This is because mixing properties are
     referenced to COMPONENT mixing, while here we are interested in
     properties of a large collection of species.  Mixing properties in
     SpecSolution and subclasses are calculated from bulk properties minus
     contribution from component standard states.By default, linear mixing
     in components is assumed.  May be subclassed to eliminate this constraint.
  */
  int i;
  double v;
  //update();
  //for(i=0,v=0.;i<nspec;i++) {
  //  if (specs[i]>0.) {
  //    v+=specs[i]*(ss[i]->getVolume());
  //  }
  //}
  // linear mixing of components assumed here.
  for (i=0,v=0.;i<ncomp;i++) {
    v += comps[i]*(ss[i]->getVolume());
  }
  return v;
}
double SpecSolution::getdVdT() {
  /* unlike solution, bulk properties are calculated without call to
     mixing properties.  This is because mixing properties are
     referenced to COMPONENT mixing, while here we are interested in
     properties of a large collection of species.  Mixing properties in
     SpecSolution and subclasses are calculated from bulk properties minus
     contribution from component standard states.  By default, linear mixing
     in components is assumed.  May be subclassed to eliminate this constraint..*/
  int i;
  double dv;
  //update();
  //for(i=0,dv=0.;i<nspec;i++) {
  //  if (specs[i]>0.) {
  //    dv+=specs[i]*(ss[i]->getdVdT());
  //  }
  //}
  // linear mixing of components assumed here.
  for (i=0,dv=0.;i<ncomp;i++) {
    dv += comps[i]*(ss[i]->getdVdT());
  }
  return dv;
}
double SpecSolution::getVmix() {
  int i;
  double vmx;
  update();
  vmx=getVolume();
  for (i=0;i<ncomp;i++) {
    if (comps[i]>0.) {
      vmx -= comps[i]*(ss[i]->getVolume());
    }
  }
  return vmx;
}
double SpecSolution::getdVdTmix() {
  int i;
  double dvdtmx;
  update();
  dvdtmx=getdVdT();
  for (i=0;i<ncomp;i++) {
    if (comps[i]>0.) {
      dvdtmx -= comps[i]*(ss[i]->getdVdT());
    }
  }
  return dvdtmx;
}

// utility functions ///////////////////////////
void SpecSolution::supressSpecies(int i) {
  if (i<nspec&&i>=ncomp) {
    supressSpec[i]&=SUPRESS;
  }
  return;
}
void SpecSolution::setSpeciateTolerance(double tol) {
  spectol = tol;
  return;
}
int SpecSolution::speciate() {
  int niter,i;
  double tol;
  tol = spectol;
  do {
    niter = speciate_function(tol);
    if (niter==-2) {
      if (verbose) cout << ((tol<1000.)?"/":"!");
      tol*=5.0;
    }
    else if ((niter>0)&&(niter<2)&&(tol>spectol)) {
      if (verbose) cout << "\\";
      tol/=2.0;
    }
    else break;
  } while (tol<1000000.);

  /*wrap up*/
  if (verbose) cout << "|";
  for (i=0,specSum=0.;i<lspec;i++) specSum += specs[indx[i]];
  return niter;
}
void SpecSolution::update() {
  if (!updated) {
    int i,niter;
    for (i=0;i<lspec;i++) {
      ss[indx[i]]->update();
    }
    niter=speciate();
    updated = (niter>=0)? 1:0;
  }
  return;
}
double SpecSolution::getSpecCalcErr() {
  double gerr,temp;
  int i,j;
  gerr=0.;
  update();
  for (i=lcomp;i<lspec;i++) {
    temp = getSpecMu(indx[i]);
    for (j=0;j<lcomp;j++) {
      temp -= spstoich[indx[i]][indx[j]]*getSpecMu(indx[j]); 
    }
    gerr += fabs(temp);
  }
  return gerr;
}
int SpecSolution::isUpdated() {
  return updated;
}
void SpecSolution::printAll() {
  int i,j,lr;
  
  Solution::printAll();

  printf("\n\nSpecies\n%10s %10s %15s %15s",
	 "name","moles","mu0","mu");
  for (i=0;i<nspec;i++) {
    if (specs[i]>0.) {
      printf("\n%10s %10.4f %15.4g %15.4g",
	     getSpecName(i),specs[i],getMu0(i),getMu(i));
    }
  }

  printf("\n\nnu matrix");
  lr=lspec-lcomp;
  for (i=0;i<lspec;i++) {
    printf("\n");
    for (j=0;j<lr;j++) {
      printf("%10.4g ",nu[i][j]);
    }
  }
  printf("\n");
      
  return;
}

// protected utility functions /////////////////////////////////////
int SpecSolution::speciate_function(double tol) {
  /*Implements RAND speciation algorithm as presented in:
   *
   *Smith and Missen (1982) Chemical Reaction Equilibrium Analysis:
   *Theory and Algorithms. Krieger.
   *
   *Gf is vector of standard state chemical potentials at T
   *spstoich[0:nspec-1][0:ncomp-1]
   *
   *IDEAL SOLUTION in species assumed
   */
  
  int i,j,k,niter,converged;
  double sum,omega,dGdw[2],mdel;
  const int max=5000;
  const double SMALL=1000.*DBL_EPSILON;

  sum=0.;

  /*********fill b*************************/
  for (k=0;k<lcomp;k++) {
    b[k] = comps[indx[k]];
  }

  /*****************main iteration loop*************************/
  tol=fabs(tol);
  mdel=10.*tol;
  for (niter=0;niter<=max&&mdel>tol;niter++) {
    for(k=0;k<lcomp;k++){
      for(j=0,bm[k]=0.0;j<lspec;j++){
	bm[k]+=spstoich[indx[j]][indx[k]]*specs[indx[j]];
      }
    }
    /*********calculate potentials****************/
    for(i=0,sum=0.;i<lspec;i++)sum+=specs[indx[i]];
    for(i=0;i<lspec;i++) mu[i]=ss[indx[i]]->getGibbs()
			   +R*tk*log(specs[indx[i]]/sum);

    /***********fill A and rhs***(1 offset for N.R.)*****************/
    /*Equation 6.3-26*/
    /*lhs*/
    for (j=0;j<lcomp;j++){
      for (i=0;i<lcomp;i++){
	for (k=0,A[j][i]=0.0;k<lspec;k++){
	  A[j][i] += spstoich[indx[k]][indx[i]]*spstoich[indx[k]][indx[j]]
	    *specs[indx[k]];
        }
      }
      A[j][lcomp]=bm[j]; /*this is the 'u' variable in Smith and Missen*/
    }
    /*rhs*/
    for (j=0;j<lcomp;j++){
      for (k=0,rhs[j]=0.0;k<lspec;k++) {
	rhs[j]+=spstoich[indx[k]][indx[j]]*specs[indx[k]]*mu[k]/(R*tk);
      }
      rhs[j] += b[j]-bm[j];
    }

    /*Equation 6.3-27*/
    for (i=0;i<lcomp;i++) A[lcomp][i]=bm[i];
    A[lcomp][lcomp]= -0.;/*inert species (nz) modifying 'u'*/
    for (k=0,rhs[lcomp]=0.0;k<lspec;k++){
      rhs[lcomp] += specs[indx[k]]*mu[k]/(R*tk);
    }

    /*************solve for Psi*******************************/
    svdSolve(A,psi,rhs,lcomp+1,lcomp+1,w,v,1.e-7);

    /*************calculate increment*(Eq. 6.3-24)*****************/
    for (j=0;j<lspec;j++){
      for (k=0,delta[j]=0.0;k<lcomp;k++) {
	delta[j]+=spstoich[indx[j]][indx[k]]*psi[k];
      }
      delta[j] += psi[lcomp]-mu[j]/(R*tk);
      delta[j] *= specs[indx[j]];
    }

    /*calculate factor necessary to prevent negative fractions*/
    for (j=0,omega=1.0;j<lspec;j++){
      if (delta[j]<0.&&specs[indx[j]]+delta[j]<SMALL) {
	double temp;
	temp=specs[indx[j]]*(1.e-7 - 1.)/delta[j];
	if(temp<0.){
	  printf("negative value for temp at line #%d\n",__LINE__);
	}
	if (temp<omega)omega=temp;
      }
    }
    if (omega<1.0){
      for(j=0;j<lspec;j++){
	delta[j]*=omega; /*to prevent iteration to negative fractions*/
      }
    }

    /*************calculate omega**********************************/
    /*see Smith and Missen p. 115*/
    for (i=0,sum=0.;i<lspec;i++) {
      sum += specs[indx[i]]+delta[i];
    }
    for (i=0,dGdw[0]=dGdw[1]=0.0;i<lspec;i++){
      dGdw[0]+=mu[i]*delta[i];
      dGdw[1]+=(ss[indx[i]]->getGibbs()
		+R*tk*log((specs[indx[i]]+delta[i])/sum))*delta[i];
    }
    if (dGdw[0]<0.0) {
      if (dGdw[1]<=0.0) omega=1.0;
      else omega=dGdw[0]/(dGdw[0]-dGdw[1]);
    }
    else {
      /*printf("\nWarning: speciation function not incrementing 'downhill'");*/
      omega=0.5;
    }

    /*************increment species********************************/
    for (i=0,mdel=0.0;i<lspec;i++) {
      double temp;
      if (specs[indx[i]]>10.*SMALL){  /*no tiny species in convergence test*/
	temp=fabs(delta[i])/specs[indx[i]];
	if (mdel<temp) mdel=temp;
      }
      specs[indx[i]] += omega*delta[i];
      if (specs[indx[i]]<=0.0){
	printf("\nAttempt to drive species %d negative at iteration %d",
	       i,niter);
	printf("\nSpec[%d]=%10.1e  delta=%10.1e",i,specs[indx[i]],delta[i]);
	specs[indx[i]]=SMALL;
      }
    }

  } /*end of main loop*/
  
  /*****************wrap up******************************/
  converged = (niter<=max);
  if (verbose) {
    printf("\n%s in %d iterations",(converged)? "Converged":"Not converged",niter);
    printf("\nFinal iteration max change %10.1g percent.",mdel*100.);
  }
  {  // mass balance correction loop
    double cf;
    for(k=0;k<lcomp;k++){
      for(j=0,bm[k]=0.0;j<lspec;j++){
	bm[k]+=spstoich[indx[j]][indx[k]]*specs[indx[j]];
      }
    }
    for (i=0,cf=0.;i<lcomp;i++) {
      double del;
      del = (bm[i]/b[i]);
      cf += del;
    }
    cf /= (double)lcomp;
    if (cf!=1.) {
      for (i=0;i<lspec;i++) {
	specs[indx[i]] /= cf;
      }
    }
  }
  return niter;
} /*End of SPECIATE function*/

/* fillSpecs *****************************************/
int SpecSolution::fillSpecs() {
  const double SMALL=1.e-7;
  int i,j,k,kmin;
  double min;
  for (i=0;i<ncomp;i++) {
    specs[i]=comps[i];
  }
  /* Put minimal value in relevant species. */
  for (j=ncomp;j<nspec;j++) {
    if (supressSpec[j]) {
      specs[j]=0.;
    }
    else {
      for (k=0,kmin=-1;k<ncomp;k++) {
	//loop checks to see if all comps present and find smallest
	if (spstoich[j][k]>0.) {	// component required for species
	  if (specs[k]>0.) {	// species present
	    if (kmin<0) {
	      kmin=k;
	    }
	    else {
	      if (specs[k]<specs[kmin]) {
		kmin=k;
	      }
	    }
	  }
	  else {			// required component not present
	    break;                // if so species will be set to zero
	  }
	}
      }
      if (k==ncomp) {		// got through whole list without break
	// this means we should put small amount in this species
	if (specs[kmin]>100.*SMALL) {
	  min = SMALL;
	}
	else {
	  min = specs[kmin]/1000.;
	}
	specs[j]=min/spstoich[j][kmin];
	// and subtract appropriate amount from components
	for (k=0;k<ncomp;k++) {
	  specs[k] -= min*spstoich[j][k]/spstoich[j][kmin];
	}
      }
      else {		        // zero species 
	specs[j]=0.;
      }
    }
  }
  for (i=0,specSum=0.;i<nspec;i++) specSum += specs[i];
  return 0;
} /*end fillSpecs*/
/* fillComps ***********************************************/
void SpecSolution::fillComps() {
  int i,j;
  /* specs*spstoich to transform to components */
  for (i=0,nmoles=0.;i<ncomp;i++) {
    comps[i]=0.;
    for (j=0;j<nspec;j++) {
      comps[i] += (specs[j]*spstoich[j][i]);
    }
    nmoles += comps[i];
  }
  return;
}
/* index **************************************************/
void SpecSolution::index() {
  int i,j,r;
  for (i=lcomp=lspec=r=0;i<nspec;i++) {
    if (specs[i]>0.0) {
      indx[lspec] = i;
      lspec++;
      if (i<ncomp) {
	lcomp++;
      }
      else {
	rdx[r]=i-ncomp;
	r++;
      }
    }
  }
  /* Fill nu matrix (Smith and Misson section 2.3.3)
   * This must be done every time in case one spec has zeroed component
   * IMPORTANT: nu is indexed on non-zero reactions and species.
   */
  for (j=0;j<r;j++) {	        /* all reactions */
    for (i=0;i<lcomp;i++) {	/* components */
      nu[i][j]=-spstoich[indx[lcomp+j]][indx[i]];
    }
  }
  
  for (i=0;i<r;i++) {		/* fill lower part with identity */
    for (j=0;j<r;j++) {
      nu[i+lcomp][j] = (i==j)? 1.0:0.0;
    }
  }
  nuRank=r;
  if (specCharge!=NULL) { //incorporate charge balance constraints
    int iflag,ipivot;
    for (i=0,iflag=0;i<lspec;i++) {
      if (specCharge[indx[i]]!=0.) {
	v1[i]=specCharge[indx[i]];
	iflag=1;
      }
      else v1[i]=0.;
    }
    if (iflag) {  //if non-zero charged species exist (otherwise, we are done)
      nuRank--;  // reduce rank for charge balance constraint
      // first take care of charged components
      for (i=0;i<lcomp;i++) {
	if (v1[i]!=0.) {
	  for (j=lcomp;j<lspec;j++) {
	    v1[j]-=v1[i]*spstoich[indx[j]][indx[i]];
	    v1[i]=0.;
	  }
	}
      }
      // now zero first charged column of nu
      for (ipivot=lcomp;ipivot<lspec;ipivot++) {
	if (v1[ipivot]!=0) {  //first charged will be pivot
	  for (i=ipivot;i<lspec;i++) {
	    v1[i] /= v1[ipivot];  // scale
	  }
	  break;
	}
      }
      for (i=0;i<lcomp;i++) {
	for (j=ipivot;j<lspec;j++) {
	  nu[i][j-lcomp] -= nu[i][ipivot-lcomp]*v1[j]/v1[ipivot];
	}
      }
      // finally, eliminate zeroed collumn
      for (i=0;i<lspec;i++) {
	for (j=ipivot-lcomp;j<r-1;j++) {
	  nu[i][j]=nu[i][j+1];
	}
      }
    }
  }  // end of charge balance section
  return;
}
void SpecSolution::getd2Gds2(double **d2gds2) {
  int i,j;
  update();
  // ideal solution
  for (i=0;i<lspec;i++) {
    for (j=0;j<=i;j++) {
      d2gds2[i][j] = R*tk*(DIRAC(i,j)-specs[indx[i]]/specSum)/specs[indx[i]];
      if (i!=j) {
	d2gds2[j][i]=d2gds2[i][j];
      }
    }
  }
  return;
}
void SpecSolution::getd3Gds2dT(double **d3gds2dt) {
  int i,j;
  update();
  // ideal solution
  for (i=0;i<lspec;i++) {
    for (j=0;j<=i;j++) {
      d3gds2dt[i][j] = R*(DIRAC(i,j)-specs[indx[i]]/specSum)/specs[indx[i]];
      if (i!=j) {
	d3gds2dt[j][i]=d3gds2dt[i][j];
      }
    }
  }
  return;
}
void SpecSolution::getd3Gds3(double ***d3gds3) {
  int i,j,m;
  update();
  for (m=0;m<lspec;m++) {
    for (i=0;i<=m;i++) {
      for (j=0;j<=i;j++) {
	d3gds3[m][i][j] = -DIRAC(j,m)*(DIRAC(i,m)/specs[indx[m]]-1./specSum);
	d3gds3[m][i][j] -= (DIRAC(m,j)-specs[indx[m]])/specSum;
	d3gds3[m][i][j] *= R*tk/specSum;
	if (m!=i) {
	  d3gds3[i][m][j]=d3gds3[m][i][j];
	}
	if (m!=j) {
	  d3gds3[j][i][m]=d3gds3[m][i][j];
	}
	if (i!=j) {
	  d3gds3[m][j][i]=d3gds3[m][i][j];
	}
      }
    }
  }
  return;
}
void SpecSolution::getdSds(double *dsds) {
  int i;
  update();
  for (i=0;i<lspec;i++) {
    dsds[i] = ss[indx[i]]->getEntropy() - R*log(specs[indx[i]]/specSum);
  }
  return;
}
void SpecSolution::getdVds(double *dvds) {
  int i;
  update();
  for (i=0;i<lspec;i++) {
    dvds[i] = ss[indx[i]]->getVolume();
  }
  return;
}
void SpecSolution::updateTransformKernel() {
  int i,j,k,l,r;

  r=nuRank;

  for (i=0;i<lspec;i++) {
    for (j=0;j<lspec;j++) {
      K[i][j]=0.;
    }
  }

  getd2Gds2(dmuds);

  if (r>0) {
    /* (nuTdmudsnu)-1 */
    for (i=0;i<r;i++) {
      for (j=0;j<r;j++) {
	m1[i][j] = 0.;
	for (k=0;k<lspec;k++) {
	  for (l=0;l<lspec;l++) {
	    m1[i][j] += nu[k][i]*dmuds[k][l]*nu[l][j];
	  }
	}
      }
    }

    svdInv(m1,r,r,m2,v1,m3,1.e-7); 

    for (i=0;i<lspec;i++) {
      for (j=0;j<lspec;j++) {
	for (k=0;k<r;k++) {
	  for (l=0;l<r;l++) {
	    K[i][j] += nu[i][k]*m1[k][l]*nu[j][l];
	  }
	}
      }
    }
  }

  return;
}

double SpecSolution::dmufunc(int m,int p,double *s) {
  //ideal solution
  double dmu,sum;
  int i;
  for (i=0,sum=0.;i<nspec;i++) sum += s[i];
  dmu = R*tk/s[m];
  dmu *= (DIRAC(m,p)-s[m]/sum);
  return dmu;
}
