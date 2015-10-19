/* 
   SpecSolNID class generic implementation
   Victor Kress
   $Id: SpecSolNID.cc,v 1.29 2007/11/30 09:25:52 kress Exp $
 */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include "SpecSolNID.h"
#include "NumUtil.h"
#include "svdInv.h"

using namespace std;

// workaround for Darwin
// extern "C" int isnan(double);

int ModifiedNR(double *a,double *grad,double **H,int);

SpecSolNID::SpecSolNID() {
  // init must be called by implementing child after ncomp and nspec set
  return;
}

SpecSolNID::~SpecSolNID() {
  int r;
  r = nspec - ncomp;
  free_dmatrix(nspec,nspec,Wh);
  free_dmatrix(r,r,H);
  delete []grad;
  delete []delxi;
  delete []delta;
  delete []b;
  delete []d;
  delete []test;
  delete []smalldelta;
  return;
}
void SpecSolNID::init() {
  int i,j,r;
  SpecSolution::init();
  if (nspec<=0) {
    PhaseError *e =
      new PhaseError(INVALID,FATAL,name,"SpecSolNID has invalid nspec");
    throw e;
  }
  Wh = dmatrix(nspec,nspec);
  for (i=0;i<nspec;i++) {
    for (j=0;j<nspec;j++) {
      Wh[i][j]=0.;
    }
  }
  Ws = NULL;
  r = nspec - ncomp;
  H = dmatrix(r,r);
  grad = new double[r];
  b = new double[r];
  d = new double[r];
  delxi = new double[r];
  delta = new double[nspec];
  smalldelta = new double[nspec];
  test = new double[nspec];
  return;
}

// getting methods //////////////////////////////////////////
/* getGibbs**************************************************/
double SpecSolNID::getGibbs() {
  double g;
  update();
  g = getEnthalpy() - tk*getEntropy();
  return g;
}
/* getEnthalpy **********************************************/
double SpecSolNID::getEnthalpy() {
  int i,j;
  double h,hx;
  update();
  h=SpecSolution::getEnthalpy();  //ideal contribution
  for (i=0,hx=0.;i<nspec;i++) {
    for (j=0;j<nspec;j++) {
      if (i!=j) {
	hx += Wh[i][j]*specs[i]*specs[j]*specs[j];
      }
    }
  }
  h += hx/(specSum*specSum);
  return h;
}
/* getEntropy **********************************************/
double SpecSolNID::getEntropy() {
  int i,j;
  double s,sx;
  update();
  s=SpecSolution::getEntropy(); //ideal contribution
  if (Ws!=NULL) {
    for (i=0,sx=0.;i<nspec;i++) {
      for (j=0;j<nspec;j++) {
	if (i!=j) {
	  sx += Ws[i][j]*specs[i]*specs[j]*specs[j];
	}
      }
    }
    s += sx/(specSum*specSum);
  }
  return s;
}
/* getSpecMu ************************************************/
double SpecSolNID::getSpecMu(int ispec) {
  update();
  return mufunc(ispec,specs);
}

// protected utility methods ////////////////////////////////
/* mufunc ***************************************************/
double SpecSolNID::mufunc(int p,double *x) {
  /* in form for speciateNID function. x is moles */
  int i;
  double mu,sum;
  for (i=0,sum=0.;i<lspec;i++) sum += x[indx[i]];
  if (x[p]<=0.) {		// this should never happen.
    return 0.;			// should be -infinity, but will never be used
  }
  mu = getMu0(p);	                // standard state
  if (x[p]/sum<1.0) {		// normally true. otherwise, use standard state
    mu += R*tk*log(x[p]/sum);
    mu += muxs(p,x);
  }
  return mu;
}
double SpecSolNID::dmufunc(int m,int k,double *x) {
  /* in form for speciateNID function 
   * note that this applies only when N=1. otherwise, divide
   * all entries by N. This is done by the calling function */
  int i,p;
  double dmu,sum;
  for (i=0,sum=0.;i<lspec;i++) sum += x[indx[i]];
  dmu=0.0;
  for (p=0;p<lspec;p++) {
    double dmmdxp;
    dmmdxp = (m==indx[p])? R*tk*sum/x[m]:0.0;  /* dRTlnXm/dXp */
    dmmdxp += dmuxs(m,indx[p],x);
    dmmdxp *= DIRAC(k,indx[p])-x[indx[p]]/sum; /* times dXp/dNk */
    dmu += dmmdxp;
  }
  return dmu;
}
/* muxs ******************************************/
double SpecSolNID::muxs(int m,double *x) {
  /* asymmetric regular solution by default */
  int i,j;
  double temp,Q,sum;
  for (i=0,sum=0.;i<lspec;i++) sum += x[indx[i]];
  for (i=0,temp=0.0;i<lspec;i++) {
    for (j=0;j<lspec;j++) {
      if (i!=j) {
	Q = DIRAC(indx[i],m)+2.0*DIRAC(indx[j],m);
	temp+=Wh[indx[i]][indx[j]]*x[indx[i]]*x[indx[j]]*x[indx[j]]*(Q*sum/x[m]-2.0);
      }
    }
  }
  return temp/(sum*sum*sum);
}
/* dmuxs ****************************************/
double SpecSolNID::dmuxs(int m,int p,double *x) {
  /* asymmetric regular solution by default */
  int i,j;
  double dd=0.,sum;
  for (i=0,sum=0.;i<lspec;i++) sum += x[indx[i]];
  for (i=0;i<lspec;i++) {             /* + dRTln(gamma[m])/dX[p] */
    for (j=0;j<lspec;j++ ) {
      if (i!=j) {
	double temp=0.;
	if (indx[i]==p) {
	  temp += 2.*(DIRAC(indx[j],m)*x[indx[j]]/sum-SQR(x[indx[j]]/sum));
	}
	if (indx[j]==p) {
	  temp+=2.*(DIRAC(indx[i],m)*x[indx[j]]/sum+DIRAC(indx[j],m)*x[indx[i]]/sum
		    -2.*x[indx[i]]*x[indx[j]]/(sum*sum));
	}
	temp *= Wh[indx[i]][indx[j]];
	dd += temp;
      }
    }
  }
  return dd;
}
/* speciate_function ***************************/
int SpecSolNID::speciate_function(double tol) throw(PhaseError *) {
  const int MAXITER=2000;
  const double SMALL_COMP=1.e-8;
  const double VSMALL_COMP=1.e-10;
  const double DBL_MINI=1.e-100;
  const double NU=1.e-12;

  int i,j,k,l,niter,r,mod,converged,smallest,nanerr,itest;
  double sum,omega,minw,maxw,dGdw[2],temp,G[2],maxdel,bigchange;

  /* eliminate zero species and components */
  nanerr=0;              /* reset*/

  r=lspec-lcomp;
  if (r==0) return 0;		/* nothing to fit */

  /* pivot small species */
 for(i=0,sum=0.;i<lspec;i++) sum+=specs[indx[i]];
 if (sum!=specSum) {
   printf("\nspecSum inconsistent going into speciate_function()\n");
 }
 for (i=0;i<lcomp;i++) {
    double curr,max;
    int piv,ii;
    if (specs[indx[i]]<SMALL_COMP) { /* pivot component */
      for (j=0,max=0.,piv=-1;j<r;j++) {
	if (nu[i][j]!=0.) {    /* pivot reaction candidate */
	  ii=lcomp+j;
	  curr = fabs(nu[i][j]*nu[ii][j]*specs[indx[ii]]/sum);
	  if (curr>max) {
	    max=curr;
	    piv=j;
	  }
	}
      }
      if (piv>=0) { /* execute pivot */
	for (j=0;j<r;j++) {
	  if ((j!=piv)&&(nu[i][j]!=0.)) {
	    curr = nu[i][j]/nu[i][piv];
	    for (k=0;k<lspec;k++) {
	      nu[k][j] -= nu[k][piv]*curr;
	    }
	  }
	}
      } /* end of column pivot */
    }
  }   /* end of pivot section */


  /*****************main iteration loop*************************/
  minw=DBL_MINI;
  maxw=1.0;
  niter=0;
  G[1]=300000.;            // random large start value
  converged=0;
  do {
    niter++;
    /*Inside main loop, specs[] holds mole numbers and test[] is used
     *where mole fractions are needed.  Both are globally indexed
     *to communicate with outside world.
     */
    /*********calculate potentials****************/
    for(i=0,sum=0.;i<lspec;i++) sum+=specs[indx[i]];
    for (i=0;i<lspec;i++) test[indx[i]]=specs[indx[i]]/sum;

    for(i=0;i<lspec;i++) {
      mu[i] = mufunc(indx[i],test);
    }
    for(i=0;i<lspec;i++) {	/* calculate Hessian wrt n */
      for(j=0;j<lspec;j++) {
	dmuds[i][j]=dmufunc(indx[i],indx[j],test)/sum;
      }
    }
    for (i=0,G[0]=0.;i<lspec;i++) {
      G[0] += mu[i]*test[indx[i]];
    }
    G[0] *= sum; /*because sumSpec is dependent on speciation*/

    /***********fill H and grad********************/
    /*Equation 7.3-6*/
    for (j=0;j<r;j++) {
      /*lhs (Hessian wrt xi)*/
      for (l=j;l<r;l++){	/* Hessian must be symmetric */
	H[j][l]=0.0;
	for (i=0;i<lspec;i++){
	  for (k=0;k<lspec;k++){
	    H[j][l] += nu[i][j]*nu[k][l]*dmuds[i][k];
	  } /* for k */
	} /* for i */
	if (j!=l) H[l][j]=H[j][l];
      }	/* for l */
      /*grad*/
      for (i=0,grad[j]=0.0;i<lspec;i++){
	grad[j] += nu[i][j]*mu[i]; /* dG/dxi[j] */
      }	/* for i */
    } /* for j */

    /* check magnitude of grad */
    for (j=0,sum=0.;j<r;j++) {
      sum += SQR(grad[j]);
    }
    if (sum<10.*DBL_MIN) { /* rare, but happens */
      break;               /* from do loop */
    }

    /******** variable scaling *********/
    for (i=0;i<r;i++) {
      d[i] = 1.+fabs(G[0]); /* derivative scaling*/
      if (grad[i]!=0.) d[i] /= (2.*fabs(grad[i]));
      /*d[i]=sqrt((1.+fabs(G[0]))/(2.*fabs(H[i][i]))); * Hessian scaling*/
    }
    for (i=0;i<r;i++) {
      b[i]=-d[i]*grad[i];
    }
    for (i=0;i<r;i++) {
      for (j=0;j<r;j++) {
	H[i][j] *= d[i]*d[j];
      }
    }

    /***** calculate delxi *************/
    mod=ModifiedNR(delxi,b,H,r);  /* mod is number of mods to make H PD */

    /****** de-scale delxi ************/
    itest=0;
    for (i=0;i<r;i++) {
      delxi[i] *= d[i];
    }

    /********** calculate n increment*(Eq. 6.4-1) **************/
    for (i=0;i<r;i++) {
      itest|=isnan(delxi[i]);
    }
    if (!itest) {
      for (i=0;i<lspec;i++){
	delta[i]=0.0;
	for (j=0;j<r;j++) {
	  delta[i]+=nu[i][j]*delxi[j];
	}
      }

    /***** make sure we are going down hill **********/
      for (i=0,dGdw[0]=0.0;i<lspec;i++){   /* dGdw at this point */
	dGdw[0]+=mu[i]*delta[i];
      }
    }
    if (itest||dGdw[0]>0.) {     /* uphill or NAN (bad, bad)! */
      for (i=0;i<lspec;i++) {         /* use simple downhill method */
	delta[i]=0.0;
	for (j=0;j<r;j++) {
	  delta[i]-=nu[i][j]*grad[j];
	}
	if (isnan(delta[i])) {
	  delta[i]=0.;
	}
      }
    }

    /***** handle very small species (S&M 9.5.1) *****/
    /* first find smallest species */
    smallest=-1;
    for (i=0,sum=1.;i<lcomp;i++) {
      if (specs[indx[i]]<=VSMALL_COMP) {
	if (specs[indx[i]]<sum) {
	  smallest=i;
	  sum = specs[indx[i]];
	}
      }
    }
    for (i=0;i<lspec;i++) {
      smalldelta[i]=0.;
    }
    if (smallest>=0) {          /* small species exists */
      double Ghat;
      int nav;

      /* project out original small delta to other species */
      for (k=0;k<lspec;k++) {
	if (k!=smallest) {
	  for (j=0;j<r;j++) {
	    if (nu[smallest][j]!=0.) {
	      delta[k] -= delta[smallest]*nu[k][j]/nu[smallest][j];
	    }
	  }
	}
      }
      delta[smallest] = 0.;

      for (j=nav=0,Ghat=0.;j<r;j++) {   /* go through reactions */
	if (nu[smallest][j]!=0.) {      /* involved in reaction */
	  Ghat += grad[j]/nu[smallest][j];
	  nav++;
	}
      }
      Ghat /= (double) nav;
      temp = -Ghat/(R*tk);
      if (temp<-100.) {                /* trap potential range error */
	temp = -0.9;
      }
      else if (temp<100.) {
	temp = exp(temp)-1.;           /* normal usage */ 
	if (fabs(temp)<100.*DBL_MIN) { /* trap potential precision problem */
	  temp = -0.9;
	}
      }
      else {
	temp = 1.0;                    /* trap potential range error */
      }
      smalldelta[smallest] = specs[indx[smallest]]*temp; 

      /* adjust other deltas */
      for (j=0,sum=0.;j<r;j++) sum += SQR(nu[smallest][j]);
      for (j=0;j<r;j++) {   /* go through reactions */
	if (nu[smallest][j]!=0.) { /* involved in reaction */
	  /* contribution from this reaction */
	  for (k=0;k<lspec;k++) {
	    if (k!=smallest) {
	      smalldelta[k] += smalldelta[smallest]*
		nu[k][j]*nu[smallest][j]/sum;
	    }
	  } 
	}
      }

      /* check to see if this drives anything negative */
      omega=1.;
      for (i=0;i<lspec;i++) {
	if (smalldelta[i]<0.) { /* decreasing */
	  temp=specs[indx[i]]*(1000.*DBL_EPSILON-1.)/smalldelta[i];
	  if (temp<omega) {
	    omega=temp;       /* avoid negative n's */
	  }
	}
      }
      
      /*calculate values for this point corrected for small species*/
      for (i=0,sum=0.;i<lspec;i++) {
	test[indx[i]] = specs[indx[i]]+omega*smalldelta[i];
	sum += test[indx[i]];
      }
      for (i=0;i<lspec;i++) {
	test[indx[i]] /= sum;		/* normalize */
      }
      for (i=0;i<lspec;i++) {
	mu[i] = mufunc(indx[i],test);
      }
      for (i=0,dGdw[1]=0.0;i<lspec;i++){  /* dGdw at next point */
	dGdw[1]+=mu[i]*delta[i];
      }
      for (G[1]=0.0,i=0;i<lspec;i++) {    /* Gibbs energy at next point */
	G[1] += mu[i]*test[indx[i]];
      }
      G[1] *= sum; /*because sumSpec is dependent on speciation*/
      /* test to see if we are still going down hill */
      if ((dGdw[0]==dGdw[1])&&(G[0]==G[1])) { /* step too small to register */
	omega = 0.;
      }
      else if (dGdw[1]<0.) { /* new search direction still downhill */
	dGdw[0]=dGdw[1]; /* take new point as starting point */
	G[0]=G[1];
      }
      else {
	omega = 0.;                     /* zero out adjustment */
      }
      for (i=0;i<lspec;i++) {           /* commit to change */
	smalldelta[i]*=omega;
      }
    } /* end of small species section */

    /****calculate bounding omega to prevent negative fractions***/
    omega=(mod>0)? 5.0:1.0;  /*Hessian not PD, we may underestimate*/
    maxw=1.e16;
    for (i=0;i<lspec;i++) {     /* check rest of components */
      if (delta[i]<0.0) {	/* positive deltas are unbounded */
	if (specs[indx[i]]>0.0){ /*present and decreasing*/
	  double tmax;
	  tmax=(specs[indx[i]]+smalldelta[i])*(1000.*DBL_EPSILON-1.)/delta[i];
	  if (tmax<maxw) maxw=tmax;/*avoid negative n's*/
	}
      }
    }

    for (j=0,bigchange=0.;j<lspec;j++) { /* find largest deltax */
      temp=fabs(delta[j])/specs[indx[j]];
      if (temp>bigchange) bigchange=temp;
    }
    minw=DBL_EPSILON/bigchange;  /* any smaller is meaningless */
    if (omega>=maxw) {
      omega=(maxw+minw)/2.;
    }

    /*************calculate optimal omega************************/
    do {
      double pstep;
      /*calculate values for next point*/
      for (i=0,sum=0.;i<lspec;i++) {
	test[indx[i]] = specs[indx[i]]+smalldelta[i];
	test[indx[i]] += omega*delta[i]; /* fill test */
	if (test[indx[i]]<=0.) {
	  printf("\nspecies abundance driven negative!");
	  printf("\ntest[%d] = %g at iteration %d",
		 indx[i],test[indx[i]],niter);
	  printf("\n%s = %f + %f + %f * %f",
		 getCompFormula(indx[i]),specs[indx[i]],smalldelta[i],
						    omega,delta[i]);
	}
	sum += test[indx[i]];
      }
      for (i=0;i<lspec;i++) {
	test[indx[i]] /= sum;		/* normalize */
      }
      for (i=0;i<lspec;i++) {
	mu[i] = mufunc(indx[i],test);
      }
      for (i=0,dGdw[1]=0.0;i<lspec;i++){   /* gradient at next point */
	dGdw[1]+=mu[i]*delta[i];           /* dG/dw at next point */
      }
      for (G[1]=0.0,i=0;i<lspec;i++) {     /* Gibbs energy at next point */
        G[1] += mu[i]*test[indx[i]];
      }
      G[1] *= sum; /*because sumSpec is dependent on speciation*/
      for (i=0,pstep=0.;i<r;i++) { /*modification of Goldstein-Arujo*/
	pstep -= grad[i]*delxi[i]; 
      }
      pstep *= omega;

      /*tests*/
      if ((fabs(dGdw[1])<-NU*dGdw[0])||((maxw-minw)<1.e-8*omega)) {
	break;
      }
      else if ((dGdw[1]<0.0)&&(omega==maxw)) {
	break;
      }
      else if ((dGdw[1]>0.)||(G[1]>=G[0])) {/* next point uphill */
	if (bigchange*maxw<2.*DBL_EPSILON) {/*potential change too small*/
	  maxw=minw=omega=0.;
	}
	else if (dGdw[1]>-100.*DBL_EPSILON*dGdw[0]) {
	  maxw=omega;		           /* decrease omega */
	  temp=dGdw[0]/(dGdw[0]-dGdw[1]);    /* interpolation */
	  if (temp>.98) temp=.9;             /* for some difficult cases */
	  omega*=temp;
	  if (omega<minw) omega=minw;        /* can't hurt to check */
	}
	else {
	  maxw=omega;
	  omega=(maxw+minw)/2.;
	}
      }
      else {                               /* next point downhill */
	if (bigchange*omega<=10.*DBL_EPSILON) {/*unrepresentably tiny change */
	  minw=omega;
	  omega=(maxw+minw)/2.0;
	}
	else {	                           /* dGdw[1]<0.0 && omega<maxw */
	  minw=omega;		           /* not going to decrease it */
	  omega=(maxw+omega)/2.0;	   /* increase omega */
	}
      }      
    } while ((fabs(dGdw[1])>=-NU*dGdw[0])&&((maxw-minw)>1.e-8*omega));
    /* end of omega section */

    /*************increment species********************************/
    maxdel=0.;
    for (i=0,sum=0.;i<lspec;i++) {
      /* increment species */
      specs[indx[i]] += smalldelta[i];
      specs[indx[i]] += omega*delta[i];
      temp= fabs(smalldelta[i]+omega*delta[i])/specs[indx[i]];
      if (temp>maxdel) maxdel=temp;

      /* Final trap for negative species.  Should never get here. */
      if (specs[indx[i]]<1.e4*DBL_MIN){	/* usually happens when very small */
	if (specs[indx[i]]==0.) {
	  char *buf = new char[100];
	  sprintf(buf,"Spec[%d] driven to zero at final check.",indx[i]);
	  PhaseError *e = new PhaseError(CALCULATION,SERIOUS,name,buf);
	  delete []buf;
	  throw e;
	}
	else if (specs[indx[i]]>-1.e-70){
	  /*printf ("Correcting.\n");*/
	  specs[indx[i]]=-specs[indx[i]];
	}
	else {
	  char *buf = new char[100];
	  sprintf(buf,"Specs[%d]=%g driven negative at final check.",
		 indx[i],specs[indx[i]]);
	  PhaseError *e = new PhaseError(CALCULATION,SERIOUS,name,buf);
	  delete []buf;
	  throw e;
	}
      }
    }
    converged = converged||maxdel<tol; /* preferred exit */
  } while ((niter<=MAXITER)&&(!converged)); /*end of main loop*/
  
  /*****************wrap up******************************/
  for (j=0;j<lspec;j++) nanerr|=isnan(specs[indx[j]]);

  if (niter>=MAXITER) niter=-2;
  if (errno==EDOM) {
    PhaseError *e = 
      new PhaseError(CALCULATION,SERIOUS,name,
		     "speciation function generated domain error");
    errno=0;
    throw e;
  }
  if (errno==ERANGE) {
    PhaseError *e = 
      new PhaseError(CALCULATION,SERIOUS,name,
		     "speciation function generated range error");
    errno=0;
    throw e;
  } 
  if (nanerr) {
    PhaseError *e = 
      new PhaseError(CALCULATION,FATAL,name,
		     "NAN generated in speciation function");
    throw e;
  }
  for (i=0,specSum=0.;i<lspec;i++) specSum += specs[indx[i]];
  return(niter);
}
void SpecSolNID::getd2Gds2(double **d2gds2) {
  int i,j;
  update();
  for (i=0;i<lspec;i++) {
    for (j=0;j<=i;j++) {
      d2gds2[i][j] = dmufunc(indx[i],indx[j],specs);
      if (i!=j) {
	d2gds2[j][i]=d2gds2[i][j];
      }
    }
  }
  return;
}
void SpecSolNID::getd3Gds2dT(double **d3gds2dt) {
  cout << "getd3Gds2dT not implemented/n";
  return;
}
void SpecSolNID::getd3Gds3(double ***d3gds3) {
  cout << "getd3Gds3 not implemented/n";
  return;
}




