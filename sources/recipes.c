const char *recipes_ver(void) { return "$Id: recipes.c,v 1.5 2008/11/10 18:24:06 ghiorso Exp $"; }
/*
MELTS Source Code: RCS $Log: recipes.c,v $
MELTS Source Code: RCS Revision 1.4  2006/10/20 00:59:22  ghiorso
MELTS Source Code: RCS (1) Made initial modifications for thread safe code.
MELTS Source Code: RCS (2) Added support for XML I/O in batch mode
MELTS Source Code: RCS (3) Added support for Melts-batch listener for eventual integration into VIGMCS
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2006/08/17 20:47:54  ghiorso
MELTS Source Code: RCS Clarified variable initialization issues in routines.  Problems discovered
MELTS Source Code: RCS when compiler optimization is turned on.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2006/08/17 16:47:19  ghiorso
MELTS Source Code: RCS Made modifications to protect strings.  These modifications allow removal
MELTS Source Code: RCS of the flag -fwritable-strings during gcc compilation.  This brings the
MELTS Source Code: RCS code up to gcc 4.x standards.
MELTS Source Code: RCS
MELTS Source Code: RCS Other minor rearrangements and cleanup.
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2006/08/15 16:57:36  ghiorso
MELTS Source Code: RCS xMELTS gcc 3.x sources
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.3  2004/10/19 02:27:59  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.2  2004/09/24 21:01:24  cvsaccount
MELTS Source Code: RCS *** empty log message ***
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2004/01/02 19:21:49  cvsaccount
MELTS Source Code: RCS CTserver University of Chicago
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 1.1.1.1  2001/12/20 03:25:03  ghiorso
MELTS Source Code: RCS Sources for MELTS 5.x (xMELTS)
MELTS Source Code: RCS
MELTS Source Code: RCS Revision 5.1  2000/02/15 17:58:12  ghiorso
MELTS Source Code: RCS MELTS 5.0 - xMELTS (associated solutions, multiple liquids)
MELTS Source Code: RCS
*/

/*
**++
**  FACILITY:  Silicate Melts Regression/Crystallization Package
**
**  MODULE DESCRIPTION:
**
**      Numerical Recipes Library described in:
**
**      Press, W.H., Flannery, B.P., Teukolsky, S.A. and Vetterling, W.T.
**      (1988) Numerical Recipes in C
**      Cambridge University Press, New York, 735 pages
**
**      File: RECIPES.C
**
**  MODIFICATION HISTORY:
**
**      V1.0-1  January 27, 2000
**              Version 2.0 of Numerical Recipes library
**              Changed all float -> double
**--
*/


#include <float.h>
#include <limits.h>
#include <math.h> 
#include <signal.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "recipes.h"

/* ------
   Definitions extracted from nrutil.h 
   ------*/

/* The code down to .... */

static double sqrarg;
#define SQR(a) ((sqrarg=(a)) == 0.0 ? 0.0 : sqrarg*sqrarg)

static double maxarg1,maxarg2;
#define FMAX(a,b) (maxarg1=(a),maxarg2=(b),(maxarg1) > (maxarg2) ?\
        (maxarg1) : (maxarg2))

static int iminarg1,iminarg2;
#define IMIN(a,b) (iminarg1=(a),iminarg2=(b),(iminarg1) < (iminarg2) ?\
        (iminarg1) : (iminarg2))

/* ... here is NOT thread safe.  However, this code is only used in svd, 
       which is in turn only called from preclb in MELTS                  */

#define SIGN(a,b) ((b) >= 0.0 ? fabs(a) : -fabs(a))

#ifndef _FCOMPLEX_DECLARE_T_
typedef struct FCOMPLEX {double r,i;} fcomplex;
#define _FCOMPLEX_DECLARE_T_
#endif /* _FCOMPLEX_DECLARE_T_ */

#ifndef _ARITHCODE_DECLARE_T_
typedef struct {
	unsigned long *ilob,*iupb,*ncumfq,jdif,nc,minint,nch,ncum,nrad;
} arithcode;
#define _ARITHCODE_DECLARE_T_
#endif /* _ARITHCODE_DECLARE_T_ */

#ifndef _HUFFCODE_DECLARE_T_
typedef struct {
	unsigned long *icod,*ncod,*left,*right,nch,nodemax;
} huffcode;
#define _HUFFCODE_DECLARE_T_
#endif /* _HUFFCODE_DECLARE_T_ */

/* ------
   From COVSRT.C 
   ------*/


#define SWAP(a,b) {swap=(a);(a)=(b);(b)=swap;}

void covsrt(double **covar, int ma, int ia[], int mfit)
{
  int i,j,k;
  double swap;

  for (i=mfit+1;i<=ma;i++)
    for (j=1;j<=i;j++) covar[i][j]=covar[j][i]=0.0;
  k=mfit;
  for (j=ma;j>=1;j--) {
    if (ia[j]) {
      for (i=1;i<=ma;i++) SWAP(covar[i][k],covar[i][j])
      for (i=1;i<=ma;i++) SWAP(covar[k][i],covar[j][i])
      k--;
    }
  }
}
#undef SWAP

/* ------
   From GAUSSJ.C 
   ------*/


#define SWAP(a,b) {temp=(a);(a)=(b);(b)=temp;}

void gaussj(double **a, int n, double **b, int m)
{
  int *indxc,*indxr,*ipiv;
  int i,icol = -1,irow = -1,j,k,l,ll;
  double big,dum,pivinv,temp;

  indxc=ivector(1,n);
  indxr=ivector(1,n);
  ipiv=ivector(1,n);
  for (j=1;j<=n;j++) ipiv[j]=0;
  for (i=1;i<=n;i++) {
    big=0.0;
    for (j=1;j<=n;j++)
      if (ipiv[j] != 1)
        for (k=1;k<=n;k++) {
          if (ipiv[k] == 0) {
            if (fabs(a[j][k]) >= big) {
              big=fabs(a[j][k]);
              irow=j;
              icol=k;
            }
          } else if (ipiv[k] > 1) nrerror("gaussj: Singular Matrix-1");
        }
    ++(ipiv[icol]);
    if (irow != icol) {
      for (l=1;l<=n;l++) SWAP(a[irow][l],a[icol][l])
      for (l=1;l<=m;l++) SWAP(b[irow][l],b[icol][l])
    }
    indxr[i]=irow;
    indxc[i]=icol;
    if (a[icol][icol] == 0.0) {
      /* original: nrerror("gaussj: Singular Matrix-2");            */
      /* Returns the identity matrix as inverse instead of aborting */
      for (i=1; i<=n; i++) {
        for (j=1; j<=n; j++) a[i][j] = 0.0;
        a[i][i] = 1.0; 
      }
      free_ivector(ipiv,1,n);
      free_ivector(indxr,1,n);
      free_ivector(indxc,1,n);
      return;
    }
    pivinv=1.0/a[icol][icol];
    a[icol][icol]=1.0;
    for (l=1;l<=n;l++) a[icol][l] *= pivinv;
    for (l=1;l<=m;l++) b[icol][l] *= pivinv;
    for (ll=1;ll<=n;ll++)
      if (ll != icol) {
        dum=a[ll][icol];
        a[ll][icol]=0.0;
        for (l=1;l<=n;l++) a[ll][l] -= a[icol][l]*dum;
        for (l=1;l<=m;l++) b[ll][l] -= b[icol][l]*dum;
      }
  }
  for (l=n;l>=1;l--) {
    if (indxr[l] != indxc[l])
      for (k=1;k<=n;k++)
        SWAP(a[k][indxr[l]],a[k][indxc[l]]);
  }
  free_ivector(ipiv,1,n);
  free_ivector(indxr,1,n);
  free_ivector(indxc,1,n);
}

#undef SWAP

/* ------
   From INDEXX.C
   ------*/

#define SWAP(a,b) itemp=(a);(a)=(b);(b)=itemp;
#define M 7
#define NSTACK 50

void indexx(unsigned long n, double arr[], unsigned long indx[])
{
  unsigned long i,indxt,ir=n,itemp,j,k,l=1;
  int jstack=0,*istack;
  double a;

  istack=ivector(1,NSTACK);
  for (j=1;j<=n;j++) indx[j]=j;
  for (;;) {
    if (ir-l < M) {
      for (j=l+1;j<=ir;j++) {
        indxt=indx[j];
        a=arr[indxt];
        for (i=j-1;i>=1;i--) {
          if (arr[indx[i]] <= a) break;
          indx[i+1]=indx[i];
        }
        indx[i+1]=indxt;
      }
      if (jstack == 0) break;
      ir=istack[jstack--];
      l=istack[jstack--];
    } else {
      k=(l+ir) >> 1;
      SWAP(indx[k],indx[l+1]);
      if (arr[indx[l+1]] > arr[indx[ir]]) {
        SWAP(indx[l+1],indx[ir])
      }
      if (arr[indx[l]] > arr[indx[ir]]) {
        SWAP(indx[l],indx[ir])
      }
      if (arr[indx[l+1]] > arr[indx[l]]) {
        SWAP(indx[l+1],indx[l])
      }
      i=l+1;
      j=ir;
      indxt=indx[l];
      a=arr[indxt];
      for (;;) {
        do i++; while (arr[indx[i]] < a);
        do j--; while (arr[indx[j]] > a);
        if (j < i) break;
        SWAP(indx[i],indx[j])
      }
      indx[l]=indx[j];
      indx[j]=indxt;
      jstack += 2;
      if (jstack > NSTACK) nrerror("NSTACK too small in indexx.");
      if (ir-i+1 >= j-l) {
        istack[jstack] = (int) ir;
        istack[jstack-1] = (int) i;
        ir=j-1;
      } else {
        istack[jstack] = (int) (j-1);
        istack[jstack-1] = (int) l;
        l=i;
      }
    }
  }
  free_ivector(istack,1,NSTACK);
}
#undef M
#undef NSTACK
#undef SWAP

/* ------
   From MRQCOF.C 
   ------*/

void mrqcof(double x[], double y[], double sig[], int ndata, double a[], int ia[],
  int ma, double **alpha, double beta[], double *chisq,
  void (*funcs)(double, double [], double *, double [], int))
{
  int i,j,k,l,m,mfit=0;
  double ymod,wt,sig2i,dy,*dyda;

  dyda=vector(1,ma);
  for (j=1;j<=ma;j++)
    if (ia[j]) mfit++;
  for (j=1;j<=mfit;j++) {
    for (k=1;k<=j;k++) alpha[j][k]=0.0;
    beta[j]=0.0;
  }
  *chisq=0.0;
  for (i=1;i<=ndata;i++) {
    (*funcs)(x[i],a,&ymod,dyda,ma);
    sig2i=1.0/(sig[i]*sig[i]);
    dy=y[i]-ymod;
    for (j=0,l=1;l<=ma;l++) {
      if (ia[l]) {
        wt=dyda[l]*sig2i;
        for (j++,k=0,m=1;m<=l;m++)
          if (ia[m]) alpha[j][++k] += wt*dyda[m];
        beta[j] += dy*wt;
      }
    }
    *chisq += dy*dy*sig2i;
  }
  for (j=2;j<=mfit;j++)
    for (k=1;k<j;k++) alpha[k][j]=alpha[j][k];
  free_vector(dyda,1,ma);
}

/* ------
   From MRQMIN.C 
   ------*/

void mrqmin(double x[], double y[], double sig[], int ndata, double a[], int ia[],
  int ma, double **covar, double **alpha, double *chisq,
  void (*funcs)(double, double [], double *, double [], int), double *alamda)
{
  void covsrt(double **covar, int ma, int ia[], int mfit);
  void gaussj(double **a, int n, double **b, int m);
  void mrqcof(double x[], double y[], double sig[], int ndata, double a[],
    int ia[], int ma, double **alpha, double beta[], double *chisq,
    void (*funcs)(double, double [], double *, double [], int));
  int j,k,l,m;
  static int mfit;                               /* This code is not thread safe           */
  static double ochisq,*atry,*beta,*da,**oneda;  /* It is called only from preclb in MELTS */

  if (*alamda < 0.0) {
    atry=vector(1,ma);
    beta=vector(1,ma);
    da=vector(1,ma);
    for (mfit=0,j=1;j<=ma;j++)
      if (ia[j]) mfit++;
    oneda=matrix(1,mfit,1,1);
    *alamda=0.001;
    mrqcof(x,y,sig,ndata,a,ia,ma,alpha,beta,chisq,funcs);
    ochisq=(*chisq);
    for (j=1;j<=ma;j++) atry[j]=a[j];
  }
  for (j=0,l=1;l<=ma;l++) {
    if (ia[l]) {
      for (j++,k=0,m=1;m<=ma;m++) {
        if (ia[m]) {
          k++;
          covar[j][k]=alpha[j][k];
        }
      }
      covar[j][j]=alpha[j][j]*(1.0+(*alamda));
      oneda[j][1]=beta[j];
    }
  }
  gaussj(covar,mfit,oneda,1);
  for (j=1;j<=mfit;j++) da[j]=oneda[j][1];
  if (*alamda == 0.0) {
    covsrt(covar,ma,ia,mfit);
    free_matrix(oneda,1,mfit,1,1);
    free_vector(da,1,ma);
    free_vector(beta,1,ma);
    free_vector(atry,1,ma);
    return;
  }
  for (j=0,l=1;l<=ma;l++)
    if (ia[l]) atry[l]=a[l]+da[++j];
  mrqcof(x,y,sig,ndata,atry,ia,ma,covar,da,chisq,funcs);
  if (*chisq < ochisq) {
    *alamda *= 0.1;
    ochisq=(*chisq);
    for (j=0,l=1;l<=ma;l++) {
      if (ia[l]) {
        for (j++,k=0,m=1;m<=ma;m++) {
          if (ia[m]) {
            k++;
            alpha[j][k]=covar[j][k];
          }
        }
        beta[j]=da[j];
        a[l]=atry[l];
      }
    }
  } else {
    *alamda *= 10.0;
    *chisq=ochisq;
  }
}

/* ------
   From PYTHAG.C 
   ------*/

double pythag(double a, double b)
{
  double absa,absb;
  absa=fabs(a);
  absb=fabs(b);
  if (absa > absb) return absa*sqrt(1.0+SQR(absb/absa));
  else return (absb == 0.0 ? 0.0 : absb*sqrt(1.0+SQR(absa/absb)));
}

/* ------
   From SIMP1.C
        made static
   ------*/

static void simp1(double **a, int mm, int ll[], int nll, int iabf, int *kp, double *bmax)
{
  int k;
  double test;

  *kp=ll[1];
  *bmax=a[mm+1][*kp+1];
  for (k=2;k<=nll;k++) {
    if (iabf == 0)
      test=a[mm+1][ll[k]+1]-(*bmax);
    else
      test=fabs(a[mm+1][ll[k]+1])-fabs(*bmax);
    if (test > 0.0) {
      *bmax=a[mm+1][ll[k]+1];
      *kp=ll[k];
    }
  }
}

/* ------
   From SIMP2.C
        made static
   ------*/
   
#define EPS 1.0e-6

static void simp2(double **a, int n, int l2[], int nl2, int *ip, int kp, double *q1)
{
  int k,ii,i;
  double qp = 0.0, q0 = 0.0, q;

  *ip=0;
  for (i=1;i<=nl2;i++) {
    if (a[l2[i]+1][kp+1] < -EPS) {
      *q1 = -a[l2[i]+1][1]/a[l2[i]+1][kp+1];
      *ip=l2[i];
      for (i=i+1;i<=nl2;i++) {
        ii=l2[i];
        if (a[ii+1][kp+1] < -EPS) {
          q = -a[ii+1][1]/a[ii+1][kp+1];
          if (q < *q1) {
            *ip=ii;
            *q1=q;
          } else if (q == *q1) {
            for (k=1;k<=n;k++) {
              qp = -a[*ip+1][k+1]/a[*ip+1][kp+1];
              q0 = -a[ii+1][k+1]/a[ii+1][kp+1];
              if (q0 != qp) break;
            }
            if (q0 < qp) *ip=ii;
          }
        }
      }
    }
  }
}
#undef EPS

/* ------
   From SIMP3.C
        made static
   ------*/
   
static void simp3(double **a, int i1, int k1, int ip, int kp)
{
  int kk,ii;
  double piv;

  piv=1.0/a[ip+1][kp+1];
  for (ii=1;ii<=i1+1;ii++)
    if (ii-1 != ip) {
      a[ii][kp+1] *= piv;
      for (kk=1;kk<=k1+1;kk++)
        if (kk-1 != kp)
          a[ii][kk] -= a[ip+1][kk]*a[ii][kp+1];
    }
  for (kk=1;kk<=k1+1;kk++)
    if (kk-1 != kp) a[ip+1][kk] *= -piv;
  a[ip+1][kp+1]=piv;
}

/* ------
   From SIMPLX.C
        removed internal declarations of simp1, simp2, simp3
   ------*/
   
#define EPS 1.0e-6
#define FREEALL free_ivector(l3,1,m); free_ivector(l2,1,m); free_ivector(l1,1,n+1);

void simplx(double **a, int m, int n, int m1, int m2, int m3, int *icase, int izrov[], int iposv[])
{
  int i,ip,ir,is,k,kh,kp,m12,nl1,nl2;
  int *l1,*l2,*l3;
  double q1,bmax;

  if (m != (m1+m2+m3)) nrerror("Bad input constraint counts in simplx");
  l1=ivector(1,n+1);
  l2=ivector(1,m);
  l3=ivector(1,m);
  nl1=n;
  for (k=1;k<=n;k++) l1[k]=izrov[k]=k;
  nl2=m;
  for (i=1;i<=m;i++) {
    if (a[i+1][1] < 0.0) nrerror("Bad input tableau in simplx");
    l2[i]=i;
    iposv[i]=n+i;
  }
  for (i=1;i<=m2;i++) l3[i]=1;
  ir=0;
  if (m2+m3) {
    ir=1;
    for (k=1;k<=(n+1);k++) {
      q1=0.0;
      for (i=m1+1;i<=m;i++) q1 += a[i+1][k];
      a[m+2][k] = -q1;
    }
    do {
      simp1(a,m+1,l1,nl1,0,&kp,&bmax);
      if (bmax <= EPS && a[m+2][1] < -EPS) {
        *icase = -1;
        FREEALL return;
      } else if (bmax <= EPS && a[m+2][1] <= EPS) {
        m12=m1+m2+1;
        if (m12 <= m) {
          for (ip=m12;ip<=m;ip++) {
            if (iposv[ip] == (ip+n)) {
              simp1(a,ip,l1,
                nl1,1,&kp,&bmax);
              if (bmax > 0.0)
                goto one;
            }
          }
        }
        ir=0;
        --m12;
        if (m1+1 <= m12)
          for (i=m1+1;i<=m12;i++)
            if (l3[i-m1] == 1)
              for (k=1;k<=n+1;k++)
                a[i+1][k] = -a[i+1][k];
        break;
      }
      simp2(a,n,l2,nl2,&ip,kp,&q1);
      if (ip == 0) {
        *icase = -1;
        FREEALL return;
      }
  one:  simp3(a,m+1,n,ip,kp);
      if (iposv[ip] >= (n+m1+m2+1)) {
        for (k=1;k<=nl1;k++)
          if (l1[k] == kp) break;
        --nl1;
        for (is=k;is<=nl1;is++) l1[is]=l1[is+1];
        ++a[m+2][kp+1];
        for (i=1;i<=m+2;i++) a[i][kp+1] = -a[i][kp+1];
      } else {
        if (iposv[ip] >= (n+m1+1)) {
          kh=iposv[ip]-m1-n;
          if (l3[kh]) {
            l3[kh]=0;
            ++a[m+2][kp+1];
            for (i=1;i<=m+2;i++)
              a[i][kp+1] = -a[i][kp+1];
          }
        }
      }
      is=izrov[kp];
      izrov[kp]=iposv[ip];
      iposv[ip]=is;
    } while (ir);
  }
  for (;;) {
    simp1(a,0,l1,nl1,0,&kp,&bmax);
    if (bmax <= 0.0) {
      *icase=0;
      FREEALL return;
    }
    simp2(a,n,l2,nl2,&ip,kp,&q1);
    if (ip == 0) {
      *icase=1;
      FREEALL return;
    }
    simp3(a,m,n,ip,kp);
    is=izrov[kp];
    izrov[kp]=iposv[ip];
    iposv[ip]=is;
  }
}
#undef EPS
#undef FREEALL
#undef NRANSI

/* ------
   From SVBKSB.C 
        modified call to include e[]
   ------*/

void svbksb(double **u, double w[], double **v, int m, int n, double b[], char e[], double x[])
{
  int jj,j,i;
  double s,*tmp;

  tmp=vector(1,n);
  for (j=1;j<=n;j++) {
    s=0.0;
    if (w[j]) {
      for (i=1;i<=m;i++) s += (e[i]) ? u[i][j]*b[i] : 0.0;
      s /= w[j];
    }
    tmp[j]=s;
  }
  for (j=1;j<=n;j++) {
    s=0.0;
    for (jj=1;jj<=n;jj++) s += v[j][jj]*tmp[jj];
    x[j]=s;
  }
  free_vector(tmp,1,n);
}

/* ------
   From SVDCMP.C 
   ------*/

void svdcmp(double **a, int m, int n, double w[], double **v)
{
  double pythag(double a, double b);
  int flag,i,its,j,jj,k,l,nm;
  double anorm,c,f,g,h,s,scale,x,y,z,*rv1;

  rv1=vector(1,n);
  g=scale=anorm=0.0;
  for (i=1;i<=n;i++) {
    l=i+1;
    rv1[i]=scale*g;
    g=s=scale=0.0;
    if (i <= m) {
      for (k=i;k<=m;k++) scale += fabs(a[k][i]);
      if (scale) {
        for (k=i;k<=m;k++) {
          a[k][i] /= scale;
          s += a[k][i]*a[k][i];
        }
        f=a[i][i];
        g = -SIGN(sqrt(s),f);
        h=f*g-s;
        a[i][i]=f-g;
        for (j=l;j<=n;j++) {
          for (s=0.0,k=i;k<=m;k++) s += a[k][i]*a[k][j];
          f=s/h;
          for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
        }
        for (k=i;k<=m;k++) a[k][i] *= scale;
      }
    }
    w[i]=scale *g;
    g=s=scale=0.0;
    if (i <= m && i != n) {
      for (k=l;k<=n;k++) scale += fabs(a[i][k]);
      if (scale) {
        for (k=l;k<=n;k++) {
          a[i][k] /= scale;
          s += a[i][k]*a[i][k];
        }
        f=a[i][l];
        g = -SIGN(sqrt(s),f);
        h=f*g-s;
        a[i][l]=f-g;
        for (k=l;k<=n;k++) rv1[k]=a[i][k]/h;
        for (j=l;j<=m;j++) {
          for (s=0.0,k=l;k<=n;k++) s += a[j][k]*a[i][k];
          for (k=l;k<=n;k++) a[j][k] += s*rv1[k];
        }
        for (k=l;k<=n;k++) a[i][k] *= scale;
      }
    }
    anorm=FMAX(anorm,(fabs(w[i])+fabs(rv1[i])));
  }
  for (i=n;i>=1;i--) {
    if (i < n) {
      if (g) {
        for (j=l;j<=n;j++)
          v[j][i]=(a[i][j]/a[i][l])/g;
        for (j=l;j<=n;j++) {
          for (s=0.0,k=l;k<=n;k++) s += a[i][k]*v[k][j];
          for (k=l;k<=n;k++) v[k][j] += s*v[k][i];
        }
      }
      for (j=l;j<=n;j++) v[i][j]=v[j][i]=0.0;
    }
    v[i][i]=1.0;
    g=rv1[i];
    l=i;
  }
  for (i=IMIN(m,n);i>=1;i--) {
    l=i+1;
    g=w[i];
    for (j=l;j<=n;j++) a[i][j]=0.0;
    if (g) {
      g=1.0/g;
      for (j=l;j<=n;j++) {
        for (s=0.0,k=l;k<=m;k++) s += a[k][i]*a[k][j];
        f=(s/a[i][i])*g;
        for (k=i;k<=m;k++) a[k][j] += f*a[k][i];
      }
      for (j=i;j<=m;j++) a[j][i] *= g;
    } else for (j=i;j<=m;j++) a[j][i]=0.0;
    ++a[i][i];
  }
  for (k=n;k>=1;k--) {
    for (its=1;its<=30;its++) {
      flag=1;
      for (l=k;l>=1;l--) {
        nm=l-1;
        if ((double)(fabs(rv1[l])+anorm) == anorm) {
/* Revised
        if (fabs(rv1[l]) <= anorm*DBL_EPSILON) {
*/
          flag=0;
          break;
        }
        if ((double)(fabs(w[nm])+anorm) == anorm) break;
/* Revised 
        if (fabs(w[nm]) <= anorm*DBL_EPSILON) break;
*/
      }
      if (flag) {
        c=0.0;
        s=1.0;
        for (i=l;i<=k;i++) {
          f=s*rv1[i];
          rv1[i]=c*rv1[i];
          if ((double)(fabs(f)+anorm) == anorm) break;
/* Revised
          if (fabs(f) <= anorm*DBL_EPSILON) break;
*/
          g=w[i];
          h=pythag(f,g);
          w[i]=h;
          h=1.0/h;
          c=g*h;
          s = -f*h;
          for (j=1;j<=m;j++) {
            y=a[j][nm];
            z=a[j][i];
            a[j][nm]=y*c+z*s;
            a[j][i]=z*c-y*s;
          }
        }
      }
      z=w[k];
      if (l == k) {
        if (z < 0.0) {
          w[k] = -z;
          for (j=1;j<=n;j++) v[j][k] = -v[j][k];
        }
        break;
      }
      if (its == 30) printf("Warning (SVA): No convergence in 30 svdcmp iterations.\n");
/*    if (its == 30) nrerror("no convergence in 30 svdcmp iterations"); */
      x=w[l];
      nm=k-1;
      y=w[nm];
      g=rv1[nm];
      h=rv1[k];
      f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);
      g=pythag(f,1.0);
      f=((x-z)*(x+z)+h*((y/(f+SIGN(g,f)))-h))/x;
      c=s=1.0;
      for (j=l;j<=nm;j++) {
        i=j+1;
        g=rv1[i];
        y=w[i];
        h=s*g;
        g=c*g;
        z=pythag(f,h);
        rv1[j]=z;
        c=f/z;
        s=h/z;
        f=x*c+g*s;
        g = g*c-x*s;
        h=y*s;
        y *= c;
        for (jj=1;jj<=n;jj++) {
          x=v[jj][j];
          z=v[jj][i];
          v[jj][j]=x*c+z*s;
          v[jj][i]=z*c-x*s;
        }
        z=pythag(f,h);
        w[j]=z;
        if (z) {
          z=1.0/z;
          c=f*z;
          s=h*z;
        }
        f=c*g+s*y;
        x=c*y-s*g;
        for (jj=1;jj<=m;jj++) {
          y=a[jj][j];
          z=a[jj][i];
          a[jj][j]=y*c+z*s;
          a[jj][i]=z*c-y*s;
        }
      }
      rv1[l]=0.0;
      rv1[k]=f;
      w[k]=x;
    }
  }
  free_vector(rv1,1,n);
}

/* ------
   From SVDFIT.C 
        modified call to svbksb to reflect redefinition above
   ------*/

#define TOL 1.0e-5

void svdfit(double x[], double y[], double sig[], int ndata, double a[], int ma,
  double **u, double **v, double w[], double *chisq,
  void (*funcs)(double, double [], int))
{
  void svbksb(double **u, double w[], double **v, int m, int n, double b[],
    char e[], double x[]);
  void svdcmp(double **a, int m, int n, double w[], double **v);
  int j,i;
  double wmax,tmp,thresh,sum,*b,*afunc;
  char *e;

  b=vector(1,ndata);
  e=(char *) malloc ((size_t) (ndata+1)*sizeof(char));
  for (i=0; i<=ndata; i++) e[i] = 1;
  afunc=vector(1,ma);
  for (i=1;i<=ndata;i++) {
    (*funcs)(x[i],afunc,ma);
    tmp=1.0/sig[i];
    for (j=1;j<=ma;j++) u[i][j]=afunc[j]*tmp;
    b[i]=y[i]*tmp;
  }
  svdcmp(u,ndata,ma,w,v);
  wmax=0.0;
  for (j=1;j<=ma;j++)
    if (w[j] > wmax) wmax=w[j];
  thresh=TOL*wmax;
  for (j=1;j<=ma;j++)
    if (w[j] < thresh) w[j]=0.0;
  svbksb(u,w,v,ndata,ma,b,&e[1],a);
  *chisq=0.0;
  for (i=1;i<=ndata;i++) {
    (*funcs)(x[i],afunc,ma);
    for (sum=0.0,j=1;j<=ma;j++) sum += a[j]*afunc[j];
    *chisq += (tmp=(y[i]-sum)/sig[i],tmp*tmp);
  }
  free_vector(afunc,1,ma);
  free_vector(b,1,ndata);
  free(e);
}
#undef TOL

/* ------
   From SVDVAR.C 
   ------*/

void svdvar(double **v, int ma, double w[], double **cvm)
{
  int k,j,i;
  double sum,*wti;

  wti=vector(1,ma);
  for (i=1;i<=ma;i++) {
    wti[i]=0.0;
    if (w[i]) wti[i]=1.0/(w[i]*w[i]);
  }
  for (i=1;i<=ma;i++) {
    for (j=1;j<=i;j++) {
      for (sum=0.0,k=1;k<=ma;k++) sum += v[i][k]*v[j][k]*wti[k];
      cvm[j][i]=cvm[i][j]=sum;
    }
  }
  free_vector(wti,1,ma);
}

/* ------
   From NRUTIL.C 
   ------*/

#define NR_END 1
#define FREE_ARG char*

void nrerror(char error_text[])
/* Numerical Recipes standard error handler */
{
  fprintf(stderr,"Numerical Recipes run-time error...\n");
  fprintf(stderr,"%s\n",error_text);
  fprintf(stderr,"...now exiting to system...\n");
  /* exit(1); */
  (void) raise(SIGABRT);
  return;
}

double *vector(long nl, long nh)
/* allocate a double vector with subscript range v[nl..nh] */
{
  double *v;

  v=(double *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(double)));
  if (!v) nrerror("allocation failure in vector()");
  return v-nl+NR_END;
}

int *ivector(long nl, long nh)
/* allocate an int vector with subscript range v[nl..nh] */
{
  int *v;

  v=(int *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(int)));
  if (!v) nrerror("allocation failure in ivector()");
  return v-nl+NR_END;
}

unsigned char *cvector(long nl, long nh)
/* allocate an unsigned char vector with subscript range v[nl..nh] */
{
  unsigned char *v;

  v=(unsigned char *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(unsigned char)));
  if (!v) nrerror("allocation failure in cvector()");
  return v-nl+NR_END;
}

unsigned long *lvector(long nl, long nh)
/* allocate an unsigned long vector with subscript range v[nl..nh] */
{
  unsigned long *v;

  v=(unsigned long *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(long)));
  if (!v) nrerror("allocation failure in lvector()");
  return v-nl+NR_END;
}

double *dvector(long nl, long nh)
/* allocate a double vector with subscript range v[nl..nh] */
{
  double *v;

  v=(double *)malloc((size_t) ((nh-nl+1+NR_END)*sizeof(double)));
  if (!v) nrerror("allocation failure in dvector()");
  return v-nl+NR_END;
}

double **matrix(long nrl, long nrh, long ncl, long nch)
/* allocate a double matrix with subscript range m[nrl..nrh][ncl..nch] */
{
  long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
  double **m;

  /* allocate pointers to rows */
  m=(double **) malloc((size_t)((nrow+NR_END)*sizeof(double*)));
  if (!m) nrerror("allocation failure 1 in matrix()");
  m += NR_END;
  m -= nrl;

  /* allocate rows and set pointers to them */
  m[nrl]=(double *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));
  if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
  m[nrl] += NR_END;
  m[nrl] -= ncl;

  for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

  /* return pointer to array of pointers to rows */
  return m;
}

double **dmatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a double matrix with subscript range m[nrl..nrh][ncl..nch] */
{
  long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
  double **m;

  /* allocate pointers to rows */
  m=(double **) malloc((size_t)((nrow+NR_END)*sizeof(double*)));
  if (!m) nrerror("allocation failure 1 in matrix()");
  m += NR_END;
  m -= nrl;

  /* allocate rows and set pointers to them */
  m[nrl]=(double *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(double)));
  if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
  m[nrl] += NR_END;
  m[nrl] -= ncl;

  for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

  /* return pointer to array of pointers to rows */
  return m;
}

int **imatrix(long nrl, long nrh, long ncl, long nch)
/* allocate a int matrix with subscript range m[nrl..nrh][ncl..nch] */
{
  long i, nrow=nrh-nrl+1,ncol=nch-ncl+1;
  int **m;

  /* allocate pointers to rows */
  m=(int **) malloc((size_t)((nrow+NR_END)*sizeof(int*)));
  if (!m) nrerror("allocation failure 1 in matrix()");
  m += NR_END;
  m -= nrl;


  /* allocate rows and set pointers to them */
  m[nrl]=(int *) malloc((size_t)((nrow*ncol+NR_END)*sizeof(int)));
  if (!m[nrl]) nrerror("allocation failure 2 in matrix()");
  m[nrl] += NR_END;
  m[nrl] -= ncl;

  for(i=nrl+1;i<=nrh;i++) m[i]=m[i-1]+ncol;

  /* return pointer to array of pointers to rows */
  return m;
}

double **submatrix(double **a, long oldrl, long oldrh, long oldcl, long oldch,
  long newrl, long newcl)
/* point a submatrix [newrl..][newcl..] to a[oldrl..oldrh][oldcl..oldch] */
{
  long i,j,nrow=oldrh-oldrl+1,ncol=oldcl-newcl;
  double **m;

  /* allocate array of pointers to rows */
  m=(double **) malloc((size_t) ((nrow+NR_END)*sizeof(double*)));
  if (!m) nrerror("allocation failure in submatrix()");
  m += NR_END;
  m -= newrl;

  /* set pointers to rows */
  for(i=oldrl,j=newrl;i<=oldrh;i++,j++) m[j]=a[i]+ncol;

  /* return pointer to array of pointers to rows */
  return m;
}

double **convert_matrix(double *a, long nrl, long nrh, long ncl, long nch)
/* allocate a double matrix m[nrl..nrh][ncl..nch] that points to the matrix
declared in the standard C manner as a[nrow][ncol], where nrow=nrh-nrl+1
and ncol=nch-ncl+1. The routine should be called with the address
&a[0][0] as the first argument. */
{
  long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1;
  double **m;

  /* allocate pointers to rows */
  m=(double **) malloc((size_t) ((nrow+NR_END)*sizeof(double*)));
  if (!m) nrerror("allocation failure in convert_matrix()");
  m += NR_END;
  m -= nrl;

  /* set pointers to rows */
  m[nrl]=a-ncl;
  for(i=1,j=nrl+1;i<nrow;i++,j++) m[j]=m[j-1]+ncol;
  /* return pointer to array of pointers to rows */
  return m;
}

double ***f3tensor(long nrl, long nrh, long ncl, long nch, long ndl, long ndh)
/* allocate a double 3tensor with range t[nrl..nrh][ncl..nch][ndl..ndh] */
{
  long i,j,nrow=nrh-nrl+1,ncol=nch-ncl+1,ndep=ndh-ndl+1;
  double ***t;

  /* allocate pointers to pointers to rows */
  t=(double ***) malloc((size_t)((nrow+NR_END)*sizeof(double**)));
  if (!t) nrerror("allocation failure 1 in f3tensor()");
  t += NR_END;
  t -= nrl;

  /* allocate pointers to rows and set pointers to them */
  t[nrl]=(double **) malloc((size_t)((nrow*ncol+NR_END)*sizeof(double*)));
  if (!t[nrl]) nrerror("allocation failure 2 in f3tensor()");
  t[nrl] += NR_END;
  t[nrl] -= ncl;

  /* allocate rows and set pointers to them */
  t[nrl][ncl]=(double *) malloc((size_t)((nrow*ncol*ndep+NR_END)*sizeof(double)));
  if (!t[nrl][ncl]) nrerror("allocation failure 3 in f3tensor()");
  t[nrl][ncl] += NR_END;
  t[nrl][ncl] -= ndl;

  for(j=ncl+1;j<=nch;j++) t[nrl][j]=t[nrl][j-1]+ndep;
  for(i=nrl+1;i<=nrh;i++) {
    t[i]=t[i-1]+ncol;
    t[i][ncl]=t[i-1][ncl]+ncol*ndep;
    for(j=ncl+1;j<=nch;j++) t[i][j]=t[i][j-1]+ndep;
  }

  /* return pointer to array of pointers to rows */
  return t;
}

void free_vector(double *v, long nl, long nh)
/* free a double vector allocated with vector() */
{
  free((FREE_ARG) (v+nl-NR_END));
}

void free_ivector(int *v, long nl, long nh)
/* free an int vector allocated with ivector() */
{
  free((FREE_ARG) (v+nl-NR_END));
}

void free_cvector(unsigned char *v, long nl, long nh)
/* free an unsigned char vector allocated with cvector() */
{
  free((FREE_ARG) (v+nl-NR_END));
}

void free_lvector(unsigned long *v, long nl, long nh)
/* free an unsigned long vector allocated with lvector() */
{
  free((FREE_ARG) (v+nl-NR_END));
}

void free_dvector(double *v, long nl, long nh)
/* free a double vector allocated with dvector() */
{
  free((FREE_ARG) (v+nl-NR_END));
}

void free_matrix(double **m, long nrl, long nrh, long ncl, long nch)
/* free a double matrix allocated by matrix() */
{
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

void free_dmatrix(double **m, long nrl, long nrh, long ncl, long nch)
/* free a double matrix allocated by dmatrix() */
{
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

void free_imatrix(int **m, long nrl, long nrh, long ncl, long nch)
/* free an int matrix allocated by imatrix() */
{
  free((FREE_ARG) (m[nrl]+ncl-NR_END));
  free((FREE_ARG) (m+nrl-NR_END));
}

void free_submatrix(double **b, long nrl, long nrh, long ncl, long nch)
/* free a submatrix allocated by submatrix() */
{
  free((FREE_ARG) (b+nrl-NR_END));
}

void free_convert_matrix(double **b, long nrl, long nrh, long ncl, long nch)
/* free a matrix allocated by convert_matrix() */
{
  free((FREE_ARG) (b+nrl-NR_END));
}

void free_f3tensor(double ***t, long nrl, long nrh, long ncl, long nch,
  long ndl, long ndh)
/* free a double f3tensor allocated by f3tensor() */
{
  free((FREE_ARG) (t[nrl][ncl]+ndl-NR_END));
  free((FREE_ARG) (t[nrl]+ncl-NR_END));
  free((FREE_ARG) (t+nrl-NR_END));
}

#undef NR_END
#undef FREE_ARG

/* end-of-file RECIPES.C */

