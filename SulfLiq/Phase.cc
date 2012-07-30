/* 
 * Phase class dummy function implementation
 * $Id: Phase.cc,v 1.47 2007/11/21 23:06:02 kress Exp $
 */

#include "Phase.h"
#include <stdio.h>
#include <math.h>
#include <string>

using namespace std;

/* Constructors **********************/
Phase::Phase():R(8.31468),tr(298.15),pr(1.e5) {
  ncomp=1;  //default value if not changed by daughter
  // more defaults. Should be overridden.
  lowT = tr;
  highT = 2100.;
  lowP = 0.;
  highP = 5.e7;
  setMoles(1.0);
  setTk(tr);
  setPa(pr);

  //element array
  elarray = new double[Chem::nele];
  updated=0;
  return;
}
Phase::~Phase() {
  delete []elarray;
  if (ncomp==1) { // otherwise, let Solution destructor deal with this.
    delete []eleStoich.ele;
    delete []eleStoich.stoich;
    if (oxStoich.nele) {
      delete []oxStoich.ele;
      delete []oxStoich.stoich;
    }
  }
  return;
}

/* getting persistent properties *****************/
int Phase::getNcomp() {
  return ncomp;
}
double Phase::getMW() {
  return mw;
}
const char *Phase::getCompName(int i) {
  if (i==0) {
    return name;
  }
  else {
    return NULL;
  }
}
const char *Phase::getCompFormula(int i) {
  if (i==0) {
    return formula;
  }
  else {
    return NULL;
  }
}
int Phase::getCompNo(char *lab) {
  if (strcmp(name,lab)==0) {
      return 0;
  }
  else {
    return -1;
  }
}
int Phase::getGenericNcomp() {
  if (oxStoich.nele) { 
    return oxStoich.nele;
  }
  else {
    return eleStoich.nele;
  }
}
char *Phase::getGenericCompFormula(int icomp) {
  if (oxStoich.nele) { 
    return Chem::ox[oxStoich.ele[icomp]].formula;
  }
  else {
    return Chem::ele[eleStoich.ele[icomp]].symbol;
  }
}
int Phase::isOxide() {
  return (oxStoich.nele>0);
}

/* Setting protected variables *******************/
void Phase::setTk(double ltk) {
  checkT(ltk);
  tk = ltk;
  updated = 0;
  return;
}
void Phase::setPa(double lpa) {
  checkP(lpa);
  pa = lpa;
  updated = 0;
  return;
}
void Phase::setMoles(double lm) throw(PhaseError *) {
  if (lm<=0.) {
    PhaseError *e =
      new PhaseError(INVALID,WARNING,name,"Attempt to set negative moles");
    throw e;
  }
  nmoles = lm;
  updated = 0;
  return;
}
void Phase::setMass(double w) {
  setMoles(w/mw);
  updated = 0;
  return;
}
void Phase::setComps(double *rawcomps) {
  setMoles(rawcomps[0]);
  return;
}
void Phase::setCompWeights(double *wt) {
  setMass(wt[0]);
  return;
}
void Phase::setCompWtPct(double *wt) {
  // not meaningful for single component phases
  setMoles(1.0);
  return;
}
void Phase::setGenericCompWts(double *wt) throw(PhaseError *) {
  int i;
  double sum;
  if (oxStoich.nele) {   // set as oxide
    double *oxarray = new double[Chem::nox];
    for (i=0;i<Chem::nox;i++) oxarray[i]=0.;
    for (i=0;i<oxStoich.nele;i++) {
      if (wt[i]<0.) {
	PhaseError *e = 
	  new PhaseError(INVALID,WARNING,name,
			 "Negative oxide in Phase::setGenericCompWts()"
			 );
	throw e;
      }
      oxarray[oxStoich.ele[i]] = wt[i];
    }
    Chem::oxWtToMol(oxarray);
    Chem::oxToEl(oxarray,elarray);
    for (i=0,sum=0.;i<Chem::nele;i++) sum += elarray[i]; 
    setElements(elarray);
    delete []oxarray;
  }
  else {                 //set as elements
    for (i=0,sum=0.;i<eleStoich.nele;i++) {
      int j;
      if (wt[i]<0.) {
	PhaseError *e = 
	  new PhaseError(INVALID,WARNING,name,
			 "Negative element in Phase::setGenericCompWts()"
			 );
	throw e;
      }
      j = eleStoich.ele[i];
      elarray[j]=wt[i]/Chem::ele[j].aw;
      sum += elarray[j];
    }
    setElements(elarray);
  }    
  for (i=0;i<Chem::nele;i++) {
    if (elarray[i]>sum*.01) {
      PhaseError *e = 
	new PhaseError(INVALID,WARNING,name,
		       "Inconsistent input array in Phase::setGenericCompWts()"
		       );
      throw e;
    }
  }
  updated = 0;
  return;
}
void Phase::setElements(double *lele) throw(PhaseError *) {
  int i;
  double moles,temp;
  for (i=0;i<eleStoich.nele;i++) {
    if (lele[i]<0.) {
      PhaseError *e = 
	new PhaseError(INVALID,WARNING,name,"Negative element in setElements");
      throw e;
    }
  }
  moles=lele[eleStoich.ele[0]]/eleStoich.stoich[0];
  for (i=1;i<eleStoich.nele;i++) {
    temp=lele[eleStoich.ele[i]]/eleStoich.stoich[i]; 
    if (temp<moles) moles=temp;
  }
  for (i=0;i<eleStoich.nele;i++) {
    lele[eleStoich.ele[i]] -= moles*eleStoich.stoich[i];
  }
  checkX(&moles);
  nmoles = moles;
  updated = 0;
  return;
}
void Phase::resetTPbounds(double lowTbound,double hiTbound,
			  double lowPbound,double hiPbound) {
  lowT=lowTbound;
  highT=hiTbound;
  lowP=lowPbound;
  highP=hiPbound;
  return;
}

/* Getting methods ****************/
double Phase::getTk() {
  return tk;
}
double Phase::getPa() {
  return pa;
}
double Phase::getMoles() {
  return nmoles;
}
double Phase::getMass() {
  return nmoles*mw;
}
double Phase::getDensity() {
  double v,g;
  v=getVolume();    //m^3
  if (v==0.) return 0.;
  g=getMass();      //grams
  return 1.e-6*g/v; // convert to gm/cc
}
void Phase::getComps(double *rawcomps) {
  rawcomps[0]=nmoles;
  return;
}
void Phase::getCompWeights(double *wt) {
  wt[0]=nmoles*mw;
  return;
}
void Phase::getCompWtPct(double *wt) {
  wt[0]=100.;
  return;
}
void Phase::getGenericCompWts(double *wt) {
  int i;
  getElements(elarray);
  if (oxStoich.nele) { // oxide components
    double *oxarray = new double[Chem::nox];
    Chem::elToOx(elarray,oxarray);
    Chem::oxMolToWt(oxarray);
    for (i=0;i<oxStoich.nele;i++) {
      wt[i]=oxarray[oxStoich.ele[i]];
    }
    delete []oxarray;
  }
  else {               // element components
    for (i=0;i<eleStoich.nele;i++) {
      wt[i] = elarray[eleStoich.ele[i]]*Chem::ele[eleStoich.ele[i]].aw;
    }
  }
  return;
}
void Phase::getElements(double *lele) {
  int i;
  for (i=0;i<Chem::nele;i++) lele[i]=0.;
  for (i=0;i<eleStoich.nele;i++) {
    lele[eleStoich.ele[i]]=nmoles*eleStoich.stoich[i];
  }
  return;
}
void Phase::getAddElements(double *lele,double mol) {
  int i;
  for (i=0;i<eleStoich.nele;i++) {
    lele[eleStoich.ele[i]]+=mol*eleStoich.stoich[i];
  }
  return;
}

// Gibbs and derivatives
double Phase::getGibbs() {
  return 0.;
}
double Phase::getMu0(int i) { 
  if (i==0) {
    return getGibbs()/nmoles;
  }
  else {
    return 0.;
  }
}
void Phase::getMu0(double *m0) {
  m0[0]=getMu0(0);
  return;
}
double Phase::getMu(int i) {
  return getMu0(i);
}
void Phase::getMu(double *mu) {
  mu[0]=getMu(0);
  return;
}
double Phase::getActivity(int icomp) {
  if (icomp==0) {
    return 1.;
  }
  else {
    return 0.;
  }
}
void Phase::getActivity(double *a) {
  a[0]=1.;
  return;
}
double Phase::getdMudX(int i,int j) {
  return 0.;
}
double Phase::getdMudP(int i) {
  return getVolume();
}
void Phase::getdGdm(double *dgdm) {
  dgdm[0]=getMu(0);
}
void Phase::getd2Gdm2(double **d2gdm2) {
  d2gdm2[0][0]=0.;
}
void Phase::getd3Gdm3(double ***d3gdm3) {
  d3gdm3[0][0][0]=0.;
}
double Phase::getGmix() {
  return 0.;
}
void Phase::getHessian(double **h) {
  h[0][0]=0.;
  return;
}

// Enthalpy and derivatives
double Phase::getEnthalpy() {
  return 0.;
}
double Phase::getHmix() {
  return 0.;
}

// Entropy and derivatives
double Phase::getEntropy() {
  return 0.;
}
void Phase::getdSdm(double *dsdm) {
  dsdm[0]=getEntropy()/nmoles;
  return;
}
void Phase::getd2Sdm2(double **d2sdm2) {
  d2sdm2[0][0]=0.;
  return;
}
double Phase::getSmix() {
  return 0.;
}

// Cp and derivatives
double Phase::getCp() {
  return 0.;
}
double Phase::getdCpdT() {
  return 0.;
}
void Phase::getdCpdm(double *dcpdm) {
  dcpdm[0]=getCp()/nmoles;
  return;
}

// Volume and derivatives
double Phase::getVolume() {
  return 0.;
}
void Phase::getdVdm(double *dvdm) {
  dvdm[0]=getVolume()/nmoles;
  return;
}
void Phase::getd2Vdm2(double **d2vdm2) {
  d2vdm2[0][0]=0.;
  return;
}
double Phase::getdVdT() {
  return 0.;
}
double Phase::getdVdP() {
  return 0.;
}
double Phase::getd2VdT2() {
  return 0.;
}
double Phase::getd2VdTdP() {
  return 0.;
}
double Phase::getd2VdP2() {
  return 0.;
}
void Phase::getd2VdmdT(double *d2vdmdt) {
  d2vdmdt[0]=getdVdT()/nmoles;
  return;
}
void Phase::getd2VdmdP(double *d2vdmdp) {
  d2vdmdp[0]=getdVdP()/nmoles;
  return;
}
double Phase::getVmix() {
  return 0.;
}

// utility methods //////////////////////////////
void Phase::init() {
  int i,j;
  double sum,temp;
  updated=0;

  if (formula==NULL) {
    PhaseError *e =
      new PhaseError(INVALID,FATAL,name,
		     "Phase::init() called without formula set");
    throw e;
  }
  else if (ncomp>1){ // don't parse solutions
    PhaseError *e = new PhaseError(INVALID,FATAL,name,
				   "Phase::init() called from Solution");
    throw e;
  }
  else {
    Chem::parseFormula(formula,elarray);
    // test parse and set mw
    if (mw > 0.) {
      temp = Chem::mwt(elarray);
      if (fabs(temp-mw)/mw>0.01) {
	char *buffer = new char[100];
	sprintf(buffer,"Inconsistent parse of '%s' in first test",formula);
	PhaseError *e = new PhaseError(INVALID,FATAL,name,buffer);
	delete []buffer;
	throw e;
      }
    }
    else {
      mw = Chem::mwt(elarray);
    }
    // set element stoichiometry
    for (i=0,eleStoich.nele=0;i<Chem::nele;i++) {
      if (elarray[i]>0.) eleStoich.nele++;
    }
    eleStoich.ele = new int[eleStoich.nele];
    eleStoich.stoich = new double[eleStoich.nele];
    for (i=0,j=0;i<Chem::nele;i++) {
      if (elarray[i]>0.) {
	eleStoich.ele[j]=i;
	eleStoich.stoich[j]=elarray[i];
	j++;
      }
    }
    // test eleStoich
    temp = Chem::mwt(&eleStoich);
    if (fabs(temp-mw)/mw>0.01) {
      char *buffer = new char[100];
      sprintf(buffer,"Inconsistent parse of '%s' in second test",formula);
      PhaseError *e = new PhaseError(INVALID,FATAL,name,buffer);
      delete []buffer;
      throw e;
    }
    
    // now set oxide Stoich structure
    double *oxarray = new double[Chem::nox];  // more space than we need
    for (i=0;i<Chem::nox;i++) oxarray[i]=0.;
    for (i=0,sum=0.;i<Chem::nele;i++) sum+=elarray[i];
    Chem::elToOx(elarray,oxarray);
    oxStoich.nele=0;
    for (i=0;i<Chem::nele;i++) { // check remainders
      if (elarray[i]>0.0001*sum) {
	oxStoich.nele=-1;
	break;
      }
    }
    if (oxStoich.nele==0) {   // remainders acceptable
      for (i=0;i<Chem::nox;i++) {  // count oxides
	if (oxarray[i]>0.) oxStoich.nele++;
      }
    }
    else {                    // set to indicate not oxide
      oxStoich.nele=0;
    }
    if (oxStoich.nele) {     // allocate and set Stoich structure
      oxStoich.ele = new int[oxStoich.nele];
      oxStoich.stoich = new double[oxStoich.nele];
      for (i=0,j=0;i<Chem::nox;i++) {
	if (oxarray[i]>0.) {
	  oxStoich.ele[j]=i;
	  oxStoich.stoich[j]=oxarray[i];
	  j++;
	}
      }
    }
    delete []oxarray;
  }
  return;
}
int Phase::isStable() {
  return 1;
}
void Phase::printAll() {
  printf("\n%s<-->%s, mol.wt. = %10.3f\n",name,formula,getMW());
  printf("T = %10.1fK, P = %15.4ePa\n",tk,pa);
  printf("G = %12.4fkJ, H = %12.4fkJ, S = %10.2fJ/K, Cp = %10.2fJ/K\n",
	 getGibbs()/1000.,getEnthalpy()/1000.,getEntropy(),getCp());
  printf("V = %10.4em^3, dVdT = %10.4em^3/K, dVdP = %10.4em^3/Pa\n",
	 getVolume(),getdVdT(),getdVdP());
  printf("total moles = %10.4f\n",nmoles);
  return;
}
void Phase::update() {
  updated=1;
  return;
}
void Phase::checkT(double t) throw(PhaseError *) {
  if (t<lowT) {
    char *buffer = new char[30];
    sprintf(buffer,"Input T < minimum (%4.0fK)",lowT);
    PhaseError *e =
      new PhaseError(BOUNDS,WARNING,name,buffer);
    delete []buffer;
    throw e;
  }
  else if (t>highT) {
    char *buffer = new char[30];
    sprintf(buffer,"Input T > maximum (%4.0fK)",highT);
    PhaseError *e =
      new PhaseError(BOUNDS,WARNING,name,buffer);
    delete []buffer;
    throw e;
  }
  return;
}
void Phase::checkP(double p) throw(PhaseError *) {
  if (p<lowP) {
    char *buffer = new char[30];
    sprintf(buffer,"Input P < minimum (%7.2gPa)",lowP);
    PhaseError *e =
      new PhaseError(BOUNDS,WARNING,name,buffer);
    delete []buffer;
    throw e;
  }
  else if (p>highP) {
    char *buffer = new char[30];
    sprintf(buffer,"Input P > maximum (%7.2gPa)",highP);
    PhaseError *e =
      new PhaseError(BOUNDS,WARNING,name,buffer);
    delete []buffer;
    throw e;
  }
  return;
}
void Phase::checkX(double *x) throw(PhaseError *) {
  int i;
  double sum;
  for (i=0,sum=0.;i<ncomp;i++) {
    if (x[i]<0.) {
      PhaseError *e =
	new PhaseError(INVALID,WARNING,name,"Input component <0 moles");
      throw e;
    }
    sum += x[i];
  }
  if (sum<0.) {
      PhaseError *e =
	new PhaseError(INVALID,WARNING,name,"Input component sum <0 moles");
      throw e;
  }
  return;
}


