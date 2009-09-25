#include "../silmin.h"
#include "../recipes.h"

#include "../liq_struct_data.h"
#include "../sol_struct_data.h"
#include "../param_struct_data.h"

int calculationMode = MODE_DEFAULT;

void *main_window, *silmin_adb, *topLevel, *meltsEnviron;
SilminState *silminState;

int fder_(double *x, double *t, double *p, double *v, double *g, double *gi);
int fluid_(double *x, double *t, double *p, double *v, double *g);

void lubksb(double **a, int n, int *indx, double b[])
{
	int i,ii=0,ip,j;
	double sum;

	for (i=1;i<=n;i++) {
		ip=indx[i];
		sum=b[ip];
		b[ip]=b[i];
		if (ii)
			for (j=ii;j<=i-1;j++) sum -= a[i][j]*b[j];
		else if (sum) ii=i;
		b[i]=sum;
	}
	for (i=n;i>=1;i--) {
		sum=b[i];
		for (j=i+1;j<=n;j++) sum -= a[i][j]*b[j];
		b[i]=sum/a[i][i];
	}
}

#define NRANSI
#define TINY 1.0e-20;

void ludcmp(double **a, int n, int *indx, double *d)
{
	int i,imax=-1,j,k;
	double big,dum,sum,temp;
	double *vv;

	vv=vector(1,n);
	*d=1.0;
	for (i=1;i<=n;i++) {
		big=0.0;
		for (j=1;j<=n;j++)
			if ((temp=fabs(a[i][j])) > big) big=temp;
		if (big == 0.0) nrerror("Singular matrix in routine ludcmp");
		vv[i]=1.0/big;
	}
	for (j=1;j<=n;j++) {
		for (i=1;i<j;i++) {
			sum=a[i][j];
			for (k=1;k<i;k++) sum -= a[i][k]*a[k][j];
			a[i][j]=sum;
		}
		big=0.0;
		for (i=j;i<=n;i++) {
			sum=a[i][j];
			for (k=1;k<j;k++)
				sum -= a[i][k]*a[k][j];
			a[i][j]=sum;
			if ( (dum=vv[i]*fabs(sum)) >= big) {
				big=dum;
				imax=i;
			}
		}
		if (j != imax) {
			for (k=1;k<=n;k++) {
				dum=a[imax][k];
				a[imax][k]=a[j][k];
				a[j][k]=dum;
			}
			*d = -(*d);
			vv[imax]=vv[j];
		}
		indx[j]=imax;
		if (a[j][j] == 0.0) a[j][j]=TINY;
		if (j != n) {
			dum=1.0/(a[j][j]);
			for (i=j+1;i<=n;i++) a[i][j] *= dum;
		}
	}
	free_vector(vv,1,n);
}
#undef TINY
#undef NRANSI

#define NRANSI
#define ALF 1.0e-4
#define TOLX 1.0e-7

static double maxarg1,maxarg2;
#define FMAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ?\
        (maxarg1) : (maxarg2))

void lnsrch(int n, double xold[], double fold, double g[], double p[], double x[],
	double *f, double stpmax, int *check, double (*func)(double []))
{
	int i;
	double a,alam,alam2=0.0,alamin,b,disc,f2=0.0,fold2=0.0,rhs1,rhs2,slope,sum,temp,
		test,tmplam=0.0;

	*check=0;
	for (sum=0.0,i=1;i<=n;i++) sum += p[i]*p[i];
	sum=sqrt(sum);
	if (sum > stpmax)
		for (i=1;i<=n;i++) p[i] *= stpmax/sum;
	for (slope=0.0,i=1;i<=n;i++)
		slope += g[i]*p[i];
	test=0.0;
	for (i=1;i<=n;i++) {
		temp=fabs(p[i])/FMAX(fabs(xold[i]),1.0);
		if (temp > test) test=temp;
	}
	alamin=TOLX/test;
	alam=1.0;
	for (;;) {
		for (i=1;i<=n;i++) x[i]=xold[i]+alam*p[i];
		*f=(*func)(x);
		if (alam < alamin) {
			for (i=1;i<=n;i++) x[i]=xold[i];
			*check=1;
			return;
		} else if (*f <= fold+ALF*alam*slope) return;
		else {
			if (alam == 1.0)
				tmplam = -slope/(2.0*(*f-fold-slope));
			else {
				rhs1 = *f-fold-alam*slope;
				rhs2=f2-fold2-alam2*slope;
				a=(rhs1/(alam*alam)-rhs2/(alam2*alam2))/(alam-alam2);
				b=(-alam2*rhs1/(alam*alam)+alam*rhs2/(alam2*alam2))/(alam-alam2);
				if (a == 0.0) tmplam = -slope/(2.0*b);
				else {
					disc=b*b-3.0*a*slope;
					if (disc<0.0) nrerror("Roundoff problem in lnsrch.");
					else tmplam=(-b+sqrt(disc))/(3.0*a);
				}
				if (tmplam>0.5*alam)
					tmplam=0.5*alam;
			}
		}
		alam2=alam;
		f2 = *f;
		fold2=fold;
		alam=FMAX(tmplam,0.1*alam);
	}
}
#undef ALF
#undef TOLX
#undef NRANSI

#define NRANSI
#define EPS sqrt(DBL_EPSILON) /* 1.0e-4 */

void fdjac(int n, double x[], double fvec[], double **df,
	void (*vecfunc)(int, double [], double []))
{
	int i,j;
	double h,temp,*f;

	f=vector(1,n);
	for (j=1;j<=n;j++) {
		temp=x[j];
		h=EPS*fabs(temp);
		if (h == 0.0) h=EPS;
		x[j]=temp+h;
		h=x[j]-temp;
		(*vecfunc)(n,x,f);
		x[j]=temp;
		for (i=1;i<=n;i++) df[i][j]=(f[i]-fvec[i])/h;
	}
	free_vector(f,1,n);
}
#undef EPS
#undef NRANSI

#define NRANSI

extern int nn;
extern double *fvec;
extern void (*nrfuncv)(int n, double v[], double f[]);

static double sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)

double fminima(double x[])
{
	int i;
	double sum;

	(*nrfuncv)(nn,x,fvec);
	for (sum=0.0,i=1;i<=nn;i++) sum += SQR(fvec[i]);
	return 0.5*sum;
}
#undef NRANSI

#define NRANSI
#define MAXITS 200
#define TOLF 1.0e-4
#define TOLMIN 1.0e-6
#define TOLX 1.0e-7 
#define STPMX 100.0

int nn;
double *fvec;
void (*nrfuncv)(int n, double v[], double f[]);
#define FREERETURN {free_vector(fvec,1,n);free_vector(xold,1,n);\
	free_vector(p,1,n);free_vector(g,1,n);free_matrix(fjac,1,n,1,n);\
	free_ivector(indx,1,n);return;}

void newt(double x[], int n, int *check,
	void (*vecfunc)(int, double [], double []))
{
	void fdjac(int n, double x[], double fvec[], double **df,
		void (*vecfunc)(int, double [], double []));
	double fminima(double x[]);
	void lnsrch(int n, double xold[], double fold, double g[], double p[], double x[],
		 double *f, double stpmax, int *check, double (*func)(double []));
	void lubksb(double **a, int n, int *indx, double b[]);
	void ludcmp(double **a, int n, int *indx, double *d);
	int i,its,j,*indx;
	double d,den,f,fold,stpmax,sum,temp,test,**fjac,*g,*p,*xold;

	indx=ivector(1,n);
	fjac=matrix(1,n,1,n);
	g=vector(1,n);
	p=vector(1,n);
	xold=vector(1,n);
	fvec=vector(1,n);
	nn=n;
	nrfuncv=vecfunc;
	f=fminima(x);
	test=0.0;
	for (i=1;i<=n;i++)
		if (fabs(fvec[i]) > test) test=fabs(fvec[i]);
	if (test<0.01*TOLF) FREERETURN
	for (sum=0.0,i=1;i<=n;i++) sum += SQR(x[i]);
	stpmax=STPMX*FMAX(sqrt(sum),(double)n);
	for (its=1;its<=MAXITS;its++) {
		fdjac(n,x,fvec,fjac,vecfunc);
		for (i=1;i<=n;i++) {
			for (sum=0.0,j=1;j<=n;j++) sum += fjac[j][i]*fvec[j];
			g[i]=sum;
		}
		for (i=1;i<=n;i++) xold[i]=x[i];
		fold=f;
		for (i=1;i<=n;i++) p[i] = -fvec[i];
		ludcmp(fjac,n,indx,&d);
		lubksb(fjac,n,indx,p);
		lnsrch(n,xold,fold,g,p,x,&f,stpmax,check,fminima);
		test=0.0;
		for (i=1;i<=n;i++)
			if (fabs(fvec[i]) > test) test=fabs(fvec[i]);
		if (test < TOLF) {
			*check=0;
			FREERETURN
		}
		if (*check) {
			test=0.0;
			den=FMAX(f,0.5*n);
			for (i=1;i<=n;i++) {
				temp=fabs(g[i])*FMAX(fabs(x[i]),1.0)/den;
				if (temp > test) test=temp;
			}
			*check=(test < TOLMIN ? 1 : 0);
			FREERETURN
		}
		test=0.0;
		for (i=1;i<=n;i++) {
			temp=(fabs(x[i]-xold[i]))/FMAX(fabs(x[i]),1.0);
			if (temp > test) test=temp;
		}
		if (test < TOLX) FREERETURN
	}
	nrerror("MAXITS exceeded in newt");
}
#undef MAXITS
#undef TOLF
#undef TOLMIN
#undef TOLX
#undef STPMX
#undef FREERETURN
#undef NRANSI

#define RATIO 0.5

static double mu0C;
static double t, p;

static void func(int n, double *v, double *f) {
  double x[13], g, vol, gi[13];
  x[ 0] = 0.0; x[ 1] = 0.0; x[ 2] = 0.0; x[ 3] = 0.0; x[ 4] = 0.0; x[ 5] = 0.0; x[ 6] = 0.0;
  x[ 7] = 0.0; x[ 8] = 0.0; x[ 9] = 0.0; x[10] = 0.0; x[11] = 0.0; x[12] = 0.0;
  
  /* RATIO = (X CO2 + X CO + X CH4)/(X H2O + X H2 + 2 X CH4) */
  
  x[4] = exp(log(10.0)*v[1]);                     		       /* O2  */
  x[3] = exp(log(10.0)*v[2]);                     		       /* CO  */
  x[5] = exp(log(10.0)*v[3]);                     		       /* H2  */
  x[2] = exp(log(10.0)*v[4]);                     		       /* CH4 */
  x[0] = (1.0 - (1.0+RATIO)*x[5] - 2.0*RATIO*x[2] - x[4])/(1.0+RATIO); /* H2O */
  x[1] = 1.0-x[0]-x[2]-x[3]-x[4]-x[5];                                 /* CO2 */
  (void) fder_(x, &t, &p, &vol, &g, gi);  
    
  f[1] = gi[1] - gi[4]	   - mu0C;  /* C(s) +     O2 = CO2 */
  f[2] = gi[3] - gi[4]/2.0 - mu0C;  /* C(s) + 1/2 O2 = CO  */
  f[3] = gi[2] - gi[5]*2.0 - mu0C;  /* C(s) +   2 H2 = CH4 */
  f[4] = gi[0] - gi[4]/2.0 - gi[5]; /* 1/2 O2   + H2 = H2O */
}

#define USE_GRAPHITE

int main()
{
  double xO2[13], vO2_1bar, gO2_1bar, vO2, gO2;
  double x[13], vol, g, gi[13];
  double gamO2, fugO2, f1, f2, f3, f4;
  double p1bar = 1.0;
  double v[5];
  int i, indexD = -1, indexG = -1, check;
  
  printf("Calling function: InitComputeDataStruct().\n");
  InitComputeDataStruct();
  
  for (i=0; i<npc; i++) {
    if (!strcmp(solids[i].label, "diamond") ) indexD = i;
    if (!strcmp(solids[i].label, "graphite")) indexG = i;
  }
  if (indexD == -1) { printf("Phase \"diamond\" not found in sol_struct_data.h\n"); return 1; }
  if (indexG == -1) { printf("Phase \"graphite\" not found in sol_struct_data.h\n"); return 1; }
  
  x[ 0] = 0.0; xO2[ 0] = 0.0; /* H2O */
  x[ 1] = 0.0; xO2[ 1] = 0.0; /* CO2 */
  x[ 2] = 0.0; xO2[ 2] = 0.0; /* CH4 */
  x[ 3] = 0.0; xO2[ 3] = 0.0; /*  CO */
  x[ 4] = 0.0; xO2[ 4] = 1.0; /*  O2 */
  x[ 5] = 0.0; xO2[ 5] = 0.0; /*  H2 */
  x[ 6] = 0.0; xO2[ 6] = 0.0; /*  S2 */
  x[ 7] = 0.0; xO2[ 7] = 0.0; /* SO2 */
  x[ 8] = 0.0; xO2[ 8] = 0.0; /* COS */
  x[ 9] = 0.0; xO2[ 9] = 0.0; /* H2S */
  x[10] = 0.0; xO2[10] = 0.0; /*  N2 */
  x[11] = 0.0; xO2[11] = 0.0; /* NH3 */
  x[12] = 0.0; xO2[12] = 0.0; /*  Ar */

  printf("%5.5s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s %13.13s\n", 
    "check", "T (K)", "P (bars)", "f1", "f2", "f3", "f4", "X H2O", "X CO2", "X CH4", "X CO", "X O2", "X H2", "log f O2", "buffer");
        
  t = 1360.0+273.15;   /* K   */
  v[1] = -10.0; /* O2  */
  v[2] =  -5.0; /* CO  */
  v[3] =  -5.0; /* H2  */
  v[4] =  -5.0; /* CH4 */
  
  for (p=1000.0; p<=300000.0; p+=1000.0) {

#ifdef USE_GRAPHITE
  gibbs(t, p, (char *) solids[indexG].label, &(solids[indexG].ref), NULL, NULL, &(solids[indexG].cur));
  mu0C = (solids[indexG].cur).g;
#else
  gibbs(t, p, (char *) solids[indexD].label, &(solids[indexD].ref), NULL, NULL, &(solids[indexD].cur));
  mu0C = (solids[indexD].cur).g;
#endif   
  
  (void) fluid_(xO2, &t, &p1bar, &vO2_1bar, &gO2_1bar);
  (void) fluid_(xO2, &t, &p,     &vO2,      &gO2);
  
  newt (v, 4, &check, func);

  x[4] = exp(log(10.0)*v[1]);                     		       /* O2  */
  x[3] = exp(log(10.0)*v[2]);                     		       /* CO  */
  x[5] = exp(log(10.0)*v[3]);                     		       /* H2  */
  x[2] = exp(log(10.0)*v[4]);                     		       /* CH4 */
  x[0] = (1.0 - (1.0+RATIO)*x[5] - 2.0*RATIO*x[2] - x[4])/(1.0+RATIO); /* H2O */
  x[1] = 1.0-x[0]-x[2]-x[3]-x[4]-x[5];                                 /* CO2 */
  (void) fder_(x, &t, &p, &vol, &g, gi);  
  f1 = gi[1] - gi[4]	   - mu0C;  /* C(s) +     O2 = CO2 */
  f2 = gi[3] - gi[4]/2.0 - mu0C;  /* C(s) + 1/2 O2 = CO  */
  f3 = gi[2] - gi[5]*2.0 - mu0C;  /* C(s) +   2 H2 = CH4 */
  f4 = gi[0] - gi[4]/2.0 - gi[5]; /* 1/2 O2   + H2 = H2O */
  gamO2 = gi[4] - gO2_1bar - R*t*log(p);
  fugO2 = gO2	- gO2_1bar - R*t*log(p);
  gamO2 = exp(gamO2/(R*t));
  gamO2 = gamO2/x[4];
  fugO2 = exp(fugO2/(R*t));
  gamO2 = gamO2/fugO2;
  
  printf("%5.5d %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g %13.6g\n", 
    check, t, p, f1, f2, f3, f4, x[0], x[1], x[2], x[3], x[4], x[5], log(fugO2*gamO2*x[4]*p)/log(10.0),
    (-22324.0 + 189.0*p/1000.0 - 1.41*p*p/1000000.0)/t+4.62);
  }

  return 0;
}
