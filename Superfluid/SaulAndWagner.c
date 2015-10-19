//
//  SaulAndWagner.c
//  MELTS
//
//  Created by Mark Ghiorso on 3/10/15.
//  Copyright (c) 2015 Mark Ghiorso. All rights reserved.
//

#include <stdio.h>
#include <math.h>

static double db(double t, double p);
static double gb(double t, double p);

void h2o (double t, double p,double *v, double *g) {
    double pmpa, t8, dens, p1, dens1, gibbs1, gibbs2;
    t8 = t;

    pmpa = p/10.0;
    dens = db (t8, pmpa);
    p1 = 0.10;
    dens1 = db (t8, p1);
    gibbs1 = gb (t8, dens);
    gibbs2 = gb (t8, dens1) ;
    *v = 1.0/dens*1000000.0*(18.03/1000.0);
    *g = (gibbs1 - gibbs2)*18.03;
    return;
}

static double eps      = 1.e-8;
static double factor   = 1.e0;
static double ex[7]    = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 }; // originally indexed 0:6
static double exd[7]   = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; // originally indexed 0:6
static double exdd[7]  = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }; // originally indexed 0:6
static int    imaxf[8] = { 0,12,12,33,38,38,38,38 }; // originally indexed -1:6
static int    iex = 3;
static int    nt = 38;

static int idpot[58] = {
       1,    1,    2,    2,
       2,    2,    3,    5,
       5,    6,    7,    8,
       1,    1,    1,    2,
       3,    3,    3,    4,
       5,    5,    6,    7,
       7,    8,    8,    9,
      11,    11,   11,  11,
      11,
       2,   2,    3,     3,
       5
};

static int itpot[58] = {
    0,     2,     0,     1,
    2,     3,     5,     0,
    1,     3,     2,     5,
    5,     7,     9,     5,
    4,     6,    13,     5,
    2,     3,     2,     0,
    11,    1,     4,     0,
    0,     3,     5,     6,
    7,
    13,    14,   15,    24,
    15
};

static double g[58] = { //originally indexed 1:58
  0.2330009013e+00,-0.1402091128e+01, 0.1172248041e+00,
 -0.1850749499e+00, 0.1770110422e+00, 0.5525151794e-01,
 -0.3413257380e-03, 0.8557274367e-03, 0.3716900685e-03,
 -0.1308871233e-03, 0.3216895199e-04, 0.2785881034e-06,
 -0.3521511130e+00, 0.7881914536e-01,-0.1519666610e-01,
 -0.1068458586e+00,-0.2055046288e+00, 0.9146198012e+00,
  0.3213343569e-03,-0.1133591391e+01,-0.3107520749e+00,
  0.1217901527e+01,-0.4481710831e+00, 0.5494218772e-01,
 -0.8665222096e-04, 0.3844084088e-01, 0.9853044884e-02,
 -0.1767598472e-01, 0.1488549222e-02,-0.3070719069e-02,
  0.3880803280e-02,-0.2627505215e-02, 0.5258371388e-03,
 -0.1716396901e+00, 0.7188823624e-01, 0.5881268357e-01,
 -0.1455938880e-01,-0.1216139400e-01
};

static double tnorm = 647.14e0;
static double dnorm = 322.e0;

static double tceq = 647.14e0;
static double dceq = 322.e0;
static double pceq = 22.064e0;

static double d0 = 999.787398238e0;
static double t0 = 273.16e0;
static double b[7] = {  // original indexing 1:7
    -8.317709547068e0,6.681504888442e0,0.12436e0,0.97315e0,1.27950e0,0.969560e0,0.24873e0
};
static double tpid[7] = { // original indexing 1:7
    0.e0,1.e0,1.287202151e0,3.537101709e0,7.740210774e0,9.243749421e0,27.50564020e0
};
static double b2 = 3.00632e0;
static double f0 = 0.e0;
static double h0 = 0.e0;
static double u0 = 0.e0;
static double s0 = 0.e0;
static double g0 = 0.e0;
static int npol = 2;
static int n = 7;

static double tf[58], tsav, dsav;
static double df[15]; // original indexing -1:13

//****************************************************************************;
//           set of subroutines and functions to calculate      19.10.90;
//           various derivatives of an equation for the;
//           normalized real and ideal part of the;
//           helmholtz function f.;
//****************************************************************************;
//    usual input;
//    t    temperature (not normalized);
//    d    density (not normalized);
//********************************************************************;
//    the following program with functions and subroutines should be;
//    used like a library. you can call various thermodynami
//    properties listed in the table below :;
//                                          f = function;
//                                          s = subroutine;

// f <db>     this function calculates the density for given p,t;
// f <pb>     this function calculates the pressure;
// f <dpdtb>  1.derivative of pressure versus temperature;
// f <dpddb>  1.derivation of pressure versus density;
// f <cvb>    isochoric heat capacity;
// f <cpb>    isobaric heat capacity;
// f <wb>     velocity of sound;
// f <fb>     helmholtz function;
// f <hb>     enthalpy;
// f <sb>     entropy;
// f <ub>     internal energy;
// f <gb>     gibbs energy;
// f <betasb> isentropic temperature-pressure coefficient betas=(dt/dp)s;
// f <bb>     2. virialcoefficient b for given t;
// f <cb>     3. virialcoefficient c for given t;
// f <rjtb>   joule thomson coefficient;
// f <dtb>    isothermal throttling coefficient;
//            saturation lines;
// s <satt>   calculating dv,dl,p for given t;
// s <satp>   calculating t,dv,dl for given p;
// f <tseq>   calculating ts for a given p from sat-equation;
// s <vpeql>  linear extrapolation of the vapor-pressure for given t;
// s <sleq>   calculation of saturated liquid entropy for given t;
// s <sveq>   calculation of saturated vapor entropy for given t;
// s <hleq>   calculation of saturated liquid enthalpy for given t;
// s <hveq>   calculation of saturated vapor enthalpy for given t;
// s <vpeq>   vapour pressure for given t;
// s <dleq>   saturated liquid density for given t;
// s <dveq>   saturated vapour density for given t;
// s <dpdteq> 1. derivation of vaporpressure p versus temperature t for;
//            given t;
// f <pmelt>  melting pressure for given temperature;
// s <tmelt>  melting temperature for given pressure;
// f <psubl>  sublimation-pressure for given t;

//     further information about handling the subroutines and functions you;
//     will find in the programs, which are usually well documented.;


//******************************************************************************;
static void tfunc(t) {
//******************************************************************************;
    double tn=tnorm/t;
    for (int i=0; i<nt; i++) tf[i] = g[i]*pow(tn, itpot[i]/factor);
    tsav=t;
    return;
}

//******************************************************************************;
static void dfunc(d) {
//******************************************************************************;
    double dn=d/dnorm;
    df[0]= 1.e0/dn;
    for (int i=1; i<15; i++) df[i-1] = df[i]*dn;
    dsav=d;
    return;
}

//******************************************************************************;
static void efun() {
//******************************************************************************;
    for (int j=1; j<=3; j++ ) {
        ex[j]   = exp(-df[j+1]);
        exd[j]  = - j*df[j]*ex[j];
        exdd[j] = (j - 1.0 - j*df[j+1])*df[0]*exd[j];
    }
    if( iex != 6 ) return;
    // e**(-0.4*dn**j) - e**(-2*dn**6);

    if(df[2] < 0.2) {
        ex[6]   = (1.6e0 -   1.92e0*df[7])*df[7];
        exd[6]  = (9.6e0 -  23.04e0*df[7])*df[6];
        exdd[6] = (48.e0 - 253.44e0*df[7])*df[5];
    } else {
//*************-comment-**************************************;
//*                                                          *;
//* in some cases the following two statements will yield    *;
//* values very close to zero. be shure, that your system    *;
//* is able to calculate these values.;
//*                                                          *;
//************************************************************;
        double e1 =exp(-0.4e0*df[7]);
        double e2 =exp(-2.e0*df[7]);
        ex[6]   = e1 - e2;
        exd[6]  = (12.e0*e2 - 2.4e0*e1)*df[6];
        exdd[6] = (5.76e0*e1-144.e0*e2)*df[11] + 5.e0*exd[6]*df[0];
    }

    return;
}

//******************************************************************************;
double fnr(double t, double d) {
//******************************************************************************;
    static double tsave, dsave, fnrs;
    double result;
    if((fabs(t-tsave) < eps) && (fabs((d-dsave)/d) < eps)) {
        return fnrs;
    }

    result = 0.0;

    if( fabs( tsav - t )     > eps ) tfunc(t);
    if( fabs( dsav - d )/d   > eps ) dfunc(d);

    for (int j=0; j<=iex; j++) {
        if(imaxf[j] == imaxf[j+1]) goto line30;
        double h = 0.0;
        for (int i=imaxf[j]; i<imaxf[j+1]; i++) {
            h = h + tf[i]*df[idpot[i]+1];
        }
        result += h*ex[j];
    line30:
        continue;
    }

    fnrs = result;
    tsave = t;
    dsave = d;

    return result;
}

//ex[7]    // originally indexed  0:6
//exd[7]   // originally indexed  0:6
//exdd[7]  // originally indexed  0:6
//imaxf[8] // originally indexed -1:6
//df[15];  // originally indexed -1:13
//rest:    // originally indexed  1:x

//******************************************************************************;
double fnrd(double t, double d) {
//******************************************************************************;
    static double tsave,dsave,fnrds;
    double result;

    if((fabs(t-tsave) < eps) && (fabs((d-dsave)/d) < eps)) {
        return fnrds;
    }

    result = 0.0;

    if( fabs( tsav - t )    > eps ) tfunc(t);
    if( fabs( dsav - d )/d  > eps ) dfunc(d);

    for (int i=0; i<imaxf[0]; i++) result += tf[i]*idpot[i]*df[idpot[i]];

do 30 j=1,iex;
    for (int j=0; j<=iex)
if(imaxf(j-1).eq.imaxf(j)) goto 30;
exdn=ex(j)*df(-1);
do 20 i=imaxf(j-1)+1,imaxf(j);
fnrd= fnrd + tf(i)*(exd(j)+exdn*idpot(i))*df(idpot(i));
20    continue;
30  continue;

fnrds=fnrd;
tsave=t;
dsave=d;

    return result;
}

//******************************************************************************;
doubleprecision function fnrt(t,d);
//******************************************************************************;

//    this function calculates the 1st tn;
//    derivative of the f's normalized real part.;

implicit real*8(a-h,o-z);
//ommon/equ/g(58),idpot(58),itpot(58),imaxf(-1:6),iex,nt;
//ommon/cfunc/tf(58),tsav,df(-1:13),dsav;
*             ,ex(0:6),exd(0:6),exdd(0:6);
//ommon /ceps/ eps;
//ommon/cnorm/tnorm,dnorm;
//ommon/cfac/factor;
save tsave,dsave,fnrts;

if( dabs(t-tsave) .lt. eps;
   *    .and. dabs((d-dsave)/d) .lt. eps ) then;
fnrt=fnrts;
return;
end if;

fnrt=0.d0;

if( dabs( tsav - t )     .gt. eps ) call tfunc(t);
if( dabs( dsav - d )/d  .gt. eps ) call dfunc(d);

do 30 j=0,iex;
if(imaxf(j-1).eq.imaxf(j)) goto 30;
h=0.d0;
do 20 i=imaxf(j-1)+1,imaxf(j);
h = h + (itpot(i)/factor) *tf(i)*df(idpot(i));
20    continue;
fnrt = fnrt + h*ex(j);
30  continue;

fnrt=fnrt*(t/tnorm);

fnrts=fnrt;
tsave=t;
dsave=d;

return;
end;
//******************************************************************************;
doubleprecision function fnrdd(t,d);
//******************************************************************************;

//    this function calculates the 2nd dn;
//    derivative of the f's normalized real part.;

implicit real*8(a-h,o-z);
//ommon/equ/g(58),idpot(58),itpot(58),imaxf(-1:6),iex,nt;
//ommon/cfunc/tf(58),tsav,df(-1:13),dsav;
*             ,ex(0:6),exd(0:6),exdd(0:6);
//ommon /ceps/ eps;
save tsave,dsave,fnrdds;


if( dabs(t-tsave) .lt. eps;
   *    .and. dabs((d-dsave)/d) .lt. eps ) then;
fnrdd=fnrdds;
return;
end if;

fnrdd=0.d0;

if( dabs( tsav - t )     .gt. eps ) call tfunc(t);
if( dabs( dsav - d )/d  .gt. eps ) call dfunc(d);

do 10 i=1,imaxf(0);
fnrdd= fnrdd + tf(i)*idpot(i)*(idpot(i)-1)*df(idpot(i)-2);
10    continue;

do 30 j=1,iex;
if(imaxf(j-1).eq.imaxf(j)) goto 30;
exddn=2.d0*exd(j)/df(1);
exdn=ex(j)/df(2);
do 20 i=imaxf(j-1)+1,imaxf(j);
fnrdd= fnrdd + tf(i)*df(idpot(i));
*       *(exdd(j) + exddn*idpot(i) + exdn*idpot(i)*(idpot(i)-1));
20    continue;
30  continue;

fnrdds=fnrdd;
tsave=t;
dsave=d;

return;
end;
//******************************************************************************;
doubleprecision function fnrdt(t,d);
//******************************************************************************;

//    this function calculates the 2nd dn,tn-;
//    derivative of the f's normalized real part.;

implicit real*8(a-h,o-z);
//ommon/equ/g(58),idpot(58),itpot(58),imaxf(-1:6),iex,nt;
//ommon/cfunc/tf(58),tsav,df(-1:13),dsav;
*             ,ex(0:6),exd(0:6),exdd(0:6);
//ommon /ceps/ eps;
//ommon/cnorm/tnorm,dnorm;
//ommon/cfac/factor;
save tsave,dsave,fnrdts;

if( dabs(t-tsave) .lt. eps;
   *    .and. dabs((d-dsave)/d) .lt. eps ) then;
fnrdt=fnrdts;
return;
end if;

fnrdt=0.d0;

if( dabs( tsav - t )     .gt. eps ) call tfunc(t);
if( dabs( dsav - d )/d  .gt. eps ) call dfunc(d);

do 10 i=1,imaxf(0);
fnrdt= fnrdt + (itpot(i)/factor)*tf(i)*idpot(i)*df(idpot(i)-1);
10    continue;

do 30 j=1,iex;
if(imaxf(j-1).eq.imaxf(j)) goto 30;
exdn=ex(j)*df(-1);
do 20 i=imaxf(j-1)+1,imaxf(j);
fnrdt=fnrdt+(itpot(i)/factor)*tf(i)*(exd(j);
                                     1        +exdn*idpot(i))*df(idpot(i));
20    continue;
30  continue;

fnrdt=fnrdt*(t/tnorm);

fnrdts=fnrdt;
tsave=t;
dsave=d;

return;
end;
//****************************************************************************;
doubleprecision function fnrtt(t,d);
//*****************************************************************************;

//    this function calculates the 2nd tn-;
//    derivative of the f's normalized real part.;

implicit real*8(a-h,o-z);
//ommon/equ/g(58),idpot(58),itpot(58),imaxf(-1:6),iex,nt;
//ommon/cfunc/tf(58),tsav,df(-1:13),dsav;
*             ,ex(0:6),exd(0:6),exdd(0:6);
//ommon /ceps/ eps;
//ommon/cnorm/tnorm,dnorm;
//ommon/cfac/factor;
save tsave,dsave,fnrtts;

if( dabs(t-tsave) .lt. eps;
   *    .and. dabs((d-dsave)/d) .lt. eps ) then;
fnrtt=fnrtts;
return;
end if;

fnrtt=0.d0;

if( dabs( tsav - t )     .gt. eps ) call tfunc(t);
if( dabs( dsav - d )/d  .gt. eps ) call dfunc(d);

do 30 j=0,iex;
if(imaxf(j-1).eq.imaxf(j)) goto 30;
h=0.d0;
do 20 i=imaxf(j-1)+1,imaxf(j);
h=h+(itpot(i)/factor)*((itpot(i)/factor)-1)*tf(i)*df(idpot(i));
20    continue;
fnrtt = fnrtt + h*ex(j);
30  continue;

fnrtt=fnrtt*(t/tnorm)**2;

fnrtts=fnrtt;
tsave=t;
dsave=d;

return;
end;
//****************************************************************************;
blockdata sbstce;
//*****************************************************************************;


//   this static void sets substance parameters for h2o;

implicit real*8(a-h,o-z);
//haracter*8 hsub;

//ommon/csub1/hsub;
//ommon/csub2/rg,xmol,tc,pc,d
//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;
//ommon/csub4/fw,f

data hsub /'water   '/;
data rg /0.46151805d-03/, xmol /18.0152d0/;
*     tc /647.14d0/, dc /322.d0/, pc /22.064d0/;
data ttr /273.16d0/, ptr /.611646d-3/, dltr /999.789d0/,;
*     dvtr /0.00485195d0/, tb /373.15d0/, pb/.101325d0/,;
*     dlb /958.364d0/, dvb /0.597209d0/;
data fw /1.d6/, fc /1.d3/;

end;

//**********************************************************************************;
doubleprecision function db(t,p);
//**********************************************************************************;

//  this function calculates the density for given p,t;

implicit real*8 (a-h,o-z);
//ommon/ceps/epse;
//ommon/csub2/r,xmol,tc,pc,d
//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;
//ommon/cout/nin,nout;

db=0.d0;
if( t .le. 230.d0 .or. p .le. 0.d0 ) then;
write(nout,1001) t,p;
1001  format('<db> t=',f8.3,'or p=',d10.4,'out of range of validity');
return;
end if;

if(pmelt(t,2) .lt. p) then;
write(nout,1002)t,p;
return;
end if;

if( t .lt. ttr) then;
pmelt1=pmelt(t,1);
pmelt2=pmelt(t,2);
if(pmelt1 .le. p .and. p .le. pmelt2) then;
dest= dltr;
goto 100;
else;
write(nout,1002) t,p;
1002   format('<db> t= ',f8.3,' and p= ',d10.4,' in solid phase');
return;
end if;
end if;

if( t .lt. tc) then;
//all vpeq(t,ps);

if(dabs(p - ps)/ps .lt. 2.5d-4 ) then;
//all satt(t,dv,dest,ps);
if( p .lt. ps ) dest=dv;
else;

if ( p .lt. ps )  dest = bdens(t,p,2);
if ( p .gt. ps )  dest = bdens(t,p,1);
end if;

else;
dest= bdens(t,p,2);
end if;

//  exact calculation of density;

100  eps = 1.d2*epse;
if ( t .gt. 374.d0 ) eps = 1.d4*epse;

db= dens(p,t,dest,eps);

return;
end;
//***********************************************************************;
doubleprecision function pb(t,d);
//***********************************************************************;

//     pressure;

implicit real * 8 (a-h,o-z);

//ommon/csub2/r,xmol,tc,pc,d
//ommon/cnorm/tnorm,dnorm;

pb=0.d0;
if( t .lt. 1.d0 ) return;
if( d .lt. 1.d-10) return;

dn=d/dnorm;

pb=d*r*t*(1.d0+dn*fnrd(t,d));

return;
end;
//***********************************************************************;
doubleprecision function dpdtb(t,d);
//***********************************************************************;

//      dp/dt;

implicit real * 8 (a-h,o-z);

//ommon/csub2/r,xmol,tc,pc,d
//ommon/cnorm/tnorm,dnorm;

dpdtb=0.d0;
if( t .lt. 1.d0 ) return;
if( d .lt. 1.d-10) return;

tn=tnorm/t;
dn=d/dnorm;

dpdtb=d*r*(1.d0+dn*fnrd(t,d)-dn*tn*fnrdt(t,d));

return;
end;
//***********************************************************************;
doubleprecision function dpddb(t,d);
//***********************************************************************;

//     dp/dd;

implicit real * 8 (a-h,o-z);

//ommon/csub2/r,xmol,tc,pc,d
//ommon/cnorm/tnorm,dnorm;

dpddb=0.d0;
if( t .lt. 1.d0 ) return;
if( d .lt. 1.d-10) return;

dn=d/dnorm;

dpddb=r*t*(1.d0+2.d0*dn*fnrd(t,d)+dn**2*fnrdd(t,d));

return;
end;
//***********************************************************************;
doubleprecision function cvb(t,d);
//***********************************************************************;

//     isochoric heat capacity;

implicit real * 8 (a-h,o-z);
//ommon/csub2/r,xmol,tc,pc,d
//ommon/csub4/fw,f
//ommon/cnorm/tnorm,dnorm;


//vb=0.d0;

if( t .lt. 1.d0 ) return;

if( d .lt. 1.d-10) return;



tn=tnorm/t;



//vb=-fc*r*tn**2*(fnitt(t,d)+fnrtt(t,d));



return;

end;

//***********************************************************************;

doubleprecision function cpb(t,d);

//***********************************************************************;



//     isobaric heat capacity;



implicit real * 8 (a-h,o-z);



//ommon/csub2/r,xmol,tc,pc,d

//ommon/csub4/fw,f

//ommon/cnorm/tnorm,dnorm;



//pb=0.d0;

if( t .lt. 1.d0 ) return;

if( d .lt. 1.d-10) return;



tn=tnorm/t;

dn=d/dnorm;



//pb=cvb(t,d)+fc*r*(1.d0+dn*fnrd(t,d)-dn*tn*fnrdt(t,d))**2/;

1    (1.d0+2.d0*dn*fnrd(t,d)+dn**2*fnrdd(t,d));



return;

end;

//***********************************************************************;

doubleprecision function wb(t,d);

//***********************************************************************;



//     velocity of sound;



implicit real * 8 (a-h,o-z);



//ommon/csub2/r,xmol,tc,pc,d

//ommon/csub4/fw,f

//ommon/cnorm/tnorm,dnorm;



wb=0.d0;

if( t .lt. 1.d0 ) return;

if( d .lt. 1.d-10) return;



tn=tnorm/t;

dn=d/dnorm;



wb2=cpb(t,d)/cvb(t,d)*(1.d0+2.d0*dn*fnrd(t,d)+dn**2*fnrdd(t,d));



if(wb2 .gt. 0.d0) then;

wb=sqrt(wb2*r*fw*t);

else;

wb=0.d0;

end if;



return;

end;

//***********************************************************************;

doubleprecision function fb(t,d);

//***********************************************************************;



//     helmholtz function;



implicit real * 8 (a-h,o-z);



//ommon/csub2/r,xmol,tc,pc,d

//ommon/cnorm/tnorm,dnorm;

//ommon/csub4/fw,f

//ommon /cnullp/t0,d0,f0,h0,u0,s0,g0;



fb=0.d0;

if( t .lt. 1.d0 ) return;

if( d .lt. 1.d-10) return;



fb=r*fc*t * (fnr(t,d) + fni(t,d));



return;

end;

//***********************************************************************;

doubleprecision function hb(t,d);

//***********************************************************************;



//     enthalpy;



implicit real * 8 (a-h,o-z);



//ommon/csub2/r,xmol,tc,pc,d

//ommon/cnorm/tnorm,dnorm;

//ommon/csub4/fw,f

//ommon /cnullp/t0,d0,f0,h0,u0,s0,g0;



hb=0.d0;

if( t .lt. 1.d0 ) return;

if( d .lt. 1.d-10) return;



tn=tnorm/t;

dn=d/dnorm;



hb=r*fc*t* (1.d0 + dn*fnrd(t,d) + tn*( fnit(t,d) + fnrt(t,d)));



return;

end;

//***********************************************************************;

doubleprecision function sb(t,d);

//***********************************************************************;



//     entropy;



implicit real * 8 (a-h,o-z);



//ommon/csub2/r,xmol,tc,pc,d

//ommon/cnorm/tnorm,dnorm;

//ommon/csub4/fw,f

//ommon /cnullp/t0,d0,f0,h0,u0,s0,g0;



sb=0.d0;

if( t .lt. 1.d0 ) return;

if( d .lt. 1.d-10) return;



tn=tnorm/t;



sb=r*fc * ( tn*(fnit(t,d)+fnrt(t,d)) - (fni(t,d)+fnr(t,d)) );



return;

end;

//***********************************************************************;

doubleprecision function ub(t,d);

//***********************************************************************;



//     internal energy;



implicit real * 8 (a-h,o-z);



//ommon/csub2/r,xmol,tc,pc,d

//ommon/cnorm/tnorm,dnorm;

//ommon/csub4/fw,f

//ommon /cnullp/t0,d0,f0,h0,u0,s0,g0;



ub=0.d0;

if( t .lt. 1.d0 ) return;

if( d .lt. 1.d-10) return;



tn=tnorm/t;



ub=r*fc*t * tn*(fnit(t,d)+fnrt(t,d));



return;

end;

//***********************************************************************;

doubleprecision function gb(t,d);

//***********************************************************************;



//     gibbs energy;



implicit real * 8 (a-h,o-z);



//ommon/csub2/r,xmol,tc,pc,d

//ommon/cnorm/tnorm,dnorm;

//ommon/csub4/fw,f

//ommon /cnullp/t0,d0,f0,h0,u0,s0,g0;



gb=0.d0;

if( t .lt. 1.d0 ) return;

if( d .lt. 1.d-10) return;



tn=tnorm/t;

dn=d/dnorm;



gb=r*fc*t * (1.d0+dn*fnrd(t,d)+fni(t,d)+fnr(t,d));



return;

end;

//***********************************************************************;

doubleprecision function alphab(t1,dl1,dv1,t2,dl2,dv2);

//***********************************************************************;



//     alpha between t1 and t2;

//     (cf. osborne et al., 1930);



implicit real * 8 (a-h,o-z);

//ommon/csub4/fw,f

//ommon/csub2/rg,xmol,tc,pc,d

//ommon/cout/nin,nout;



alphab=0.d0;

if( t1 .lt. 1.d0 ) return;

if( dl1 .lt. 1.d-10) return;

if( dv1 .lt. 1.d-10) return;

if( t2 .lt. 1.d0 ) return;

if( dl2 .lt. 1.d-10) return;

if( dv2 .lt. 1.d-10) return;



if( t1 .gt. tc .or. t1 .gt. tc )then;

write(nout,*)'<alphab> t1 or t2 greater than tc . alpha not cal';

*,'culated !';

return;

end if;



beta1=fc*t1/dl1*dpsdtb(t1,dl1,dv1);

beta2=fc*t2/dl2*dpsdtb(t2,dl2,dv2);



alphab=(hb(t2,dl2)-beta2)-(hb(t1,dl1)-beta1);



return;

end;

//***********************************************************************;

doubleprecision function dpsdtb(t,dl,dv);

//***********************************************************************;



//     vapor pressure curve dps/dt;



implicit real * 8 (a-h,o-z);



//ommon/csub2/r,xmol,tc,pc,d

//ommon/csub4/fw,f

//ommon/cnorm/tnorm,dnorm;



dpsdtb=0.d0;

if( t .lt. 1.d0 ) return;

if( dl .lt. 1.d-10) return;

if( dv .lt. 1.d-10) return;



tn=tnorm/t;



dpsdtb=dl*dv/(dv-dl)*r*(log(dv/dl)+fnr(t,dv)-fnr(t,dl);
                        ;
                        *       -tn*(fnrt(t,dv)-fnrt(t,dl)));



return;

end;

//***********************************************************************;

doubleprecision function betasb(t,d);

//***********************************************************************;



//     isentropic temperature-pressure;

//     coefficient betas=(dt/dp)s;



implicit real * 8 (a-h,o-z);



//ommon/csub2/r,xmol,tc,pc,d



betasb=0.d0;

if( t .lt. 1.d0 ) return;

if( d .lt. 1.d-10) return;



betasb=t/d**2*dpdtb(t,d)/(cpb(t,d)*dpddb(t,d));



return;

end;

//***********************************************************************;

doubleprecision function bb(t);

//***********************************************************************;



//     2. virialcoefficient b;



implicit real * 8 (a-h,o-z);

//ommon/cnorm/tnorm,dnorm;

data d /1.d-200/;



bb=fnrd(t,d)/dnorm;



return;

end;

//***********************************************************************;

doubleprecision function cb(t);

//***********************************************************************;



//     3. virialcoefficient 



implicit real * 8 (a-h,o-z);

//ommon/cnorm/tnorm,dnorm;

data d /1.d-200/;



//b=fnrdd(t,d)/dnorm**2;



return;

end;

//***********************************************************************;

doubleprecision function rjtb(t,d);

//***********************************************************************;



//     joule thomson coefficient;



implicit real * 8 (a-h,o-z);



//ommon/csub2/r,xmol,tc,pc,d

//ommon/csub4/fw,f

//ommon/cnorm/tnorm,dnorm;



rjtb=0.d0;

if( t .lt. 1.d0 ) return;

if( d .lt. 1.d-10) return;



tn=tnorm/t;

dn=d/dnorm;



//vbn=-tn**2*(fnitt(t,d)+fnrtt(t,d));

dpddn=1.d0+2.d0*dn*fnrd(t,d)+dn**2*fnrdd(t,d);



rjtb=-((d*r)**(-1))*(dn*fnrd(t,d)+dn**2*fnrdd(t,d);
                     ;
                     *        +dn*tn*fnrdt(t,d))/;

*     ((1.d0+dn*fnrd(t,d)-dn*tn*fnrdt(t,d))**2+cvbn*dpddn);



return;

end;

//***********************************************************************;

doubleprecision function dtb(t,d);

//***********************************************************************;



//     isothermal throttling coefficient;



implicit real * 8 (a-h,o-z);



//ommon/csub2/r,xmol,tc,pc,d

//ommon/cnorm/tnorm,dnorm;



dtb=0.d0;

if( t .lt. 1.d0 ) return;

if( d .lt. 1.d-10) return;



tn=tnorm/t;

dn=d/dnorm;



dpddn=1.d0+2.d0*dn*fnrd(t,d)+dn**2*fnrdd(t,d);

dpdtn=1.d0+dn*fnrd(t,d)-dn*tn*fnrdt(t,d);



dtb=d**(-1)*(1.d0-dpdtn/dpddn);



return;

end;

//************************************************************************;

doubleprecision function dens(p,t,dest,epsh);

//************************************************************************;



// calculating density for given t,p,dest;



implicit real*8(a-h,o-z);

real*8 nullf;

//ommon/csub2/rg,xmol,tc,pc,d

external nullf;



eps=epsh;

if ((dest.gt.(2.d0*dc)).and.(t.lt.(tc-100.d0))) then;

dd=.003d0*dest;

else if(dest.gt.2.d0*dc) then;

dd=.01d0*dest;

else;

dd=0.05d0*dest;

end if;



d1=dest;



if(dest .gt. dc) then;

d2=d1+dd;

else;

d2=d1-dd;

end if;



if(eps. lt. 1.d-8) eps=1.d-8;



//all wnull3(d1,d2,nullf,p,t,eps,x,ix);



if( ix .le. 0 ) then;

dens=x;

else;

dens=0.d0;

end if;

999  return;

end;

//***********************************************************************;

doubleprecision function nullf(d,t,p);

//***********************************************************************;



implicit real*8 (a-h,o-z);



nullf=pb(t,d)-p;

999 return;

end;

//******************************************************************;

static void satt(t,dv,dl,p);

//******************************************************************;



//     calculating dv,dl,p for a given t;



implicit real*8(a-h,o-z);

//ommon /ceps/ epse;

//ommon/csub2/r,xmol,tc,pc,d

//ommon/cout/nin,nout;

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pboil,dlb,dvb;

save tsav,dlsav,dvsav,psav;



if( t .gt. tc ) goto 500;

if( t .lt. ttr ) goto 500;



eps = 1.d2*epse;

if ( t .gt. 374.d0 ) eps = 1.d4*epse;

epsd=.33d0*eps;



if( dabs(tc - t) .lt. epse ) then;

dl=d

dv=d

p=p

return;

end if;



if( dabs(tsav-t) .lt. epse ) then;

dl=dlsav;

dv=dvsav;

p=psav;

return;

end if;



//     initial values;



//all dveq(t,dv);

if(dv .lt. 1.d-20 ) goto 500;

//all dleq(t,dl);

//all vpeq(t,p);



//  *** maxwell-loop ***;



do 31 i=1,10;



dl=dens(p,t,dl,epsd);

if(dl.lt.1.d-20) goto 500;

fnrl=fnr(t,dl);



dv=dens(p,t,dv,epsd);

if(dv.lt.1.d-20) goto 500;

fnrv=fnr(t,dv);



if( dabs((dl-dv)/dv) .le. epsd) goto 500;



if( t .gt. 647.139d0) goto 999;

p0=p;

p=(fnrl-fnrv+log(dl/dv))*r*t/(1.d0/dv-1.d0/dl);



if(dabs((p-p0)/p) .lt. eps) goto 999;



31 continue;



write(nout,*)'<satt> did not converge at t=',t,'k';



500  continue;

dl=0.d0;

dv=0.d0;

p=0.d0;

if( t .lt. ttr );

*   write(nout,*)'<satt> t=',t,'k is below the triple-point';

if(t .gt. tc)write(nout,*)'<satt> t=',t,'k is supercritical';

999 continue;



tsav=t;

dlsav=dl;

dvsav=dv;

psav=p;



return;

end;

//******************************************************************;

static void satp(t,dv,dl,p);

//******************************************************************;



//     calculating t,dv,dl for a given p;



implicit real*8(a-h,o-z);

//ommon /ceps/ epse;

//ommon/csub2/r,xmol,tc,pc,d

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pboil,dlb,dvb;

//ommon/cout/nin,nout;

save tsav,dlsav,dvsav,psav;



if( p .gt. pc ) goto 500;

if( p .lt. ptr ) goto 500;



eps = 1.d2*epse;

if ( p .gt. 374.d0 ) eps = 1.d4*epse;

epsd=.33d0*eps;



if( dabs(pc - p)/p .lt. epse ) then;

dl=d

dv=d

t=t

return;

end if;



if( dabs(psav-p) .lt. epse ) then;

dl=dlsav;

dv=dvsav;

t=tsav;

return;

end if;



//     initial values;



t = tseq(p);

if(t .lt. 1.d-20 .or. t .gt. tc) goto 500;

//all dveq(t,dv);

//all dleq(t,dl);

//all dpdteq(t,dpdt);



//  *** maxwell-loop ***;



do 31 i=1,10;



dl=dens(p,t,dl,epsd);

if(dl.lt.1.d-20) goto 500;

fnrl=fnr(t,dl);



dv=dens(p,t,dv,epsd);

if(dv.lt.1.d-20) goto 500;

fnrv=fnr(t,dv);



if( dabs((dl-dv)/dv) .le. epsd) goto 500;



if( t .gt. 647.135d0) goto 999;

t0=t;

dp=p - (fnrl-fnrv+dlog(dl/dv))*r*t/(1.d0/dv-1.d0/dl);

t=t0 + dp/dpdt;



if(dabs(t-t0) .lt. eps) goto 999;



31 continue;



write(nout,*)'<satp> did not converge at p=',p,'mpa';



500  continue;

dl=0.d0;

dv=0.d0;

t=0.d0;

if( p .lt. ptr );

*   write(nout,*)'<satp> p=',p,'mpa is below the triple-point';

if(p .gt. pc)write(nout,*)'<satp> p=',p,'mpa is supercritical';

999 continue;



tsav=t;

dlsav=dl;

dvsav=dv;

psav=p;



return;

end;

//*******************************************************************;

static void wnull3(xa,xb,f,p,t,eps,x,ix);

//*******************************************************************;



//               f(x,t,p)=0;



//*************************************************************************;



implicit real*8(a-h,o-z);



x1=xa;

f1=f(x1,t,p);

x3=xb;

f3=f(x3,t,p);

ix=0;



do 100 i=1,40;



//   regula falsi;



if( f1 .ne. f3 ) then;

x=x1+(x3-x1)*f1/(f1-f3);

else;

goto 10;

end if;



if(x .lt. 0.d0) x=(x1+x3)/2.d0;



if(abs(x) .lt. 1.d-8) then;

if(abs(x-x1).lt.eps) return;

else;

if(abs((x-x1)/x).lt.eps) return;

end if;



f2=f(x,t,p);



x2=x1-(x1-x3)/2.d0;



if(f2*f1 .le.f2*f3) then;

x3=x1;

f3=f1;

end if;

x1=x;

f1=f2;



if((x2-x3)*(x2-x1) .ge. 0.d0) goto 100;

x=(x1+x3)/2.d0;

f2=f(x,t,p);



if(f2*f1 .le. f2*f3) then;

x3=x1;

f3=f1;

end if;



x1=x;

f1=f2;



100  continue;



10  ix=1;

999  return;

end;

//***********************************************************************;

doubleprecision function bdens(t,p,ireg);

//***********************************************************************;



//     estimating density for given t and p;



//             ireg- parameter for the region;

//                   1: liquid;

//                   2: gaseous;

//                   0: not known;



implicit real*8(a-h,o-z);

//ommon/csub2/rg,xmol,tc,pc,d

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pboil,dlb,dvb;



iregh=ireg;

if(ireg .eq. 0 .or. t .gt. tc) then;



iregh=1;

if(t .lt. tc .and. t .ge. ttr ) then;

//all vpeq(t,pt);

ps=pt;

else;

pt=1.d10;

end if;

if(t .lt. ttr) pt=ptr;

if(p .lt. pt) iregh=2;

end if;



if(iregh .eq. 1) then;

if(t .lt. ttr) then;

bdens=dltr;

return;

end if;



if(t .lt. .7*tc ) then;

//all dleq(t,dl);

bdens=dl+0.243d0*(p-ps);

else;

bdens=dsoave(t,p,iregh)+200.d0;

if(t .lt. tc) then;

//all dleq(t,dl);

if(dl .gt. bdens) bdens=dl;

end if;

end if;

else;

bdens=dsoave(t,p,iregh);

if(bdens .gt. 222.0431d0) bdens=bdens+200.d0;

if(t .lt. tc) then;

//all dveq(t,dv);

if(dv .lt. bdens) bdens=dv;

end if;

end if;



if( p .gt. 1000.d0 .or. bdens .lt. 0.d0 ) then;

dmax= 1400.d0 + (1000.d0/dlog10(24000.d0))*(dlog10(p) - 3.d0 );

if( dmax .lt. bdens .or. bdens .lt. 0.d0) bdens = dmax;

end if;



return;

end;

//***********************************************************************;

doubleprecision function dsoave(t,p,ireg);

//***********************************************************************;



//     estimating density with the soave equation;



implicit real*8 (a-h,o-z);

dimension y(3);

//ommon/csub2/ rg,xmol,tc,pc,d



dsoave=0.d0;





if(p.lt.0.d0.or.t.lt.0.d0) then;

write(1,1000);

1000 format('<bdens> error on p,t ');

goto 999;

endif;



pi= dacos(0.d0)*2.d0;

atc= .42748025d0*(rg*tc)**2/p

b= .08664035d0*rg*tc/p



tsoave= .7d0*t

//all vpeq(tsoave,psoave);

prsoav= psoave/p



omega= -log10(prsoav) -1.d0;



em= .47979d0 +1.576d0*omega -.1925d0*omega**2 +.025d0*omega**3;

alpha=(1.d0+ em*(1.d0-(t/tc)**.5d0))**2;



a= alpha*at



//  y**3 + beta*y**2 + gamma*y + delta = 0;



beta= -(rg*t)/p;

gamma= -(b**2)-(b*rg*t)/p+a/p;

delta= -(a*b)/p;



q= (beta**3)/27.d0-(beta*gamma)/6.d0+delta/2.d0;

pe= (gamma-(beta**2)/3.d0)/3.d0;

disk= (q**2)+(pe**3);



if(dabs(pe).lt.1.d-20) then;

y(1)= ((dabs(2.d0*q))**(1.d0/3.d0));

if(q.gt.0.d0) y(1)=-y(1);

y(2)= 0.d0;

y(3)= 0.d0;

kk=1;

goto 500;

endif;



if(disk.lt.0.d0) then;

r= ((abs(pe))**.5d0);

if(q.lt.0.d0) r=-r;

phi= dacos(q/(r**3));

y(1)= -(2.d0*r)*dcos(phi/3.d0);

y(2)=  (2.d0*r)*dcos((pi/3.d0)-(phi/3.d0));

y(3)=  (2.d0*r)*dcos((pi/3.d0)+(phi/3.d0));

kk= 3;

else;



diskn=(disk**.5d0);

sum1= -q+diskn;

if(sum1.lt.0.d0) then;

u=-((abs(sum1))**(1.d0/3.d0));

else;

u= (sum1**(1.d0/3.d0));

endif;

sum2= -q-diskn;

if(sum2.lt.0.d0)then;

v=-((abs(sum2))**(1.d0/3.d0));

else;

v= (sum2**(1.d0/3.d0));

endif;

y(1)= u+v;

y(2)= 0.d0;

y(3)= 0.d0;

kk=1;

endif;

500 continue;



dmax=0.d0;

dmin=1.d100;



do 50 i=1,kk;

d=1.d0/(y(i)-beta/3.d0);

if(d.gt.dmax) dmax=d;

if(d.lt.dmin) dmin=d;

50 continue;



dsoave=dmin;

iregh=ireg;



if(t .lt. tc) then;

if(ireg .eq. 0) then;

//all vpeq(t,ps);

iregh=2;

if(p .gt. ps) iregh=1;

end if;



if(iregh .eq. 1) then;

dsoave=dmax;

else;

dsoave=dmin;

end if;



end if;



999 continue;

return;

end;

//**********************************************************************************;

doubleprecision function tseq(p);

//**********************************************************************************;



//     calculating ts for a given p from sat-equation;



implicit real*8(a-h,o-z);

//ommon /ceps/ eps;

//ommon/csub2/rg,xmol,tc,pc,d

//ommon/csub3/ttr,ptr,dltr,dvtr,tbb,pbb,dlbb,dvbb;

//ommon/cout/nin,nout;

external rnufu;



tseq=0.d0;



if( abs(p-pc) .lt. 1.d-6 ) then;

tseq=t

return;

end if;



if(p.gt.pc) then;

write(nout,*)'<tseq> p is greater than pc';

return;

endif;



if(p.lt.ptr) then;

write(nout,*)'<tseq> p is less than ptr';

return;

endif;



xkonst= dlog(pc/ptr)/(1.d0/ttr-1.d0/tc);

t1=(1.d0/tc-1.d0/xkonst*dlog(p/pc))**(-1);

t2= t1-2.d0;



//all wnull3(t1,t2,rnufu,p,dummy,eps,ts,ix);



if( ix .le. 0 ) then;

tseq=ts;

else;

write(nout,*)'<tseq> did not converge at p =',p;

end if;



end;

//***********************************************************************;

doubleprecision function rnufu(t,dummy,p);

//***********************************************************************;

implicit real*8 (a-h,o-z);

//all vpeql(t,ps);

rnufu= ps-p;

return;

end;

//***********************************************************************;

static void vpeql(t,p);

//***********************************************************************;



implicit real*8 (a-h,o-z);

//ommon/csub2/r,xmol,tc,pc,d

save dpdt;

data dpdt/0.d0/;



if(t.gt.tc) then;

if( dpdt .lt. 1.d-10 ) call dpdteq(tc,dpdt);

p=pc+dpdt*(t-tc);

else;

//all vpeq(t,p);

end if;



return;

end;

//***********************************************************************;

static void sleq(t,sl);

//***********************************************************************;

implicit real*8(a-h,o-z);

//ommon/csub4/fw,f

//ommon/csub2/rg,xmol,tc,pc,d

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;

//ommon/cout/nin,nout;



//  calculation of saturated liquid entropy with help of phi;



if( t .gt. tc )then;

write(nout,*);

* '<sleq> t > tc. s.l.entropy will not be calculated !';

return;

end if;



if( t .lt. ttr)then;

write(nout,*);

* '<sleq> t <ttr. s.l.entropy will not be calculated !';

return;

end if;



//all dleq(t,dl);



if( dl .gt. 0.d0  ) then;

//all dpdteq(t,dpdt);

//all phieq(t,phi);

sl= phi + fc/dl*dpdt;

else;

sl= 0.d0;

end if;



end;

//***********************************************************************;

static void sveq(t,sv);

//***********************************************************************;

implicit real*8 (a-h,o-z);

//ommon/csub4/fw,f

//ommon/csub2/rg,xmol,tc,pc,d

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;

//ommon/cout/nin,nout;



//  calculation of saturated vapor entropy with help of phi;



if( t .gt. tc )then;

write(nout,*)'<sveq> t > tc. s.v.entropy',;

+              ' will not be calculated !';

return;

end if;



if( t .lt. ttr)then;

write(nout,*)'<sveq> t <ttr. s.v.entropy',;

+              ' will not be calculated !';

return;

end if;



//all dveq(t,dv);



if( dv .gt. 0.d0) then;

//all phieq(t,phi);

//all dpdteq(t,dpdt);

sv= phi + fc/dv*dpdt;

else;

sv=0.d0;

end if;



end;

//***********************************************************************;

static void hleq(t,hl);

//***********************************************************************;

implicit real*8(a-h,o-z);

//ommon/csub4/fw,f

//ommon/csub2/rg,xmol,tc,pc,d

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;

//ommon/cout/nin,nout;



//  calculation of saturated liquid enthalpy with help of alp;



if( t .gt. tc )then;

write(nout,*)'<hleq> t > tc. s.l.enthalpy',;

+              ' will not be calculated !';

return;

end if;



if( t .lt. ttr)then;

write(nout,*)'<hleq> t <ttr. s.l.enthalpy',;

+              ' will not be calculated !';

return;

end if;



//all dleq(t,dl);



if( dl .gt. 0.d0) then;

//all alpeq(t,alp);

//all dpdteq(t,dpdt);

hl= alp+ fc* t/dl*dpdt;

else;

hl=0.d0;

end if;



end;

//***********************************************************************;

static void hveq(t,hv);

//***********************************************************************;

implicit real*8 (a-h,o-z);

//ommon/csub4/fw,f

//ommon/csub2/rg,xmol,tc,pc,d

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;

//ommon/cout/nin,nout;



//  calculation of saturated vapor enthalpy with help of alpha;



if( t .gt. tc )then;

write(nout,*)'<hveq> t > tc. s.v.enthalpy',;

+              ' will not be calculated !';

return;

end if;



if( t .lt. ttr)then;

write(nout,*)'<hveq> t <ttr. s.v.enthalpy',;

+              ' will not be calculated !';

return;

end if;



//all dveq(t,dv);



if( dv .gt. 0.d0) then;

//all alpeq(t,alp);

//all dpdteq(t,dpdt);

hv= alp + fc*t/dv*dpdt;

else;

hv=0.d0;

end if;



end;

//***********************************************************************;

static void vpeq(t,p);

//***********************************************************************;

implicit real*8(a-h,o-z);



//     vapour pressure;



//ommon /cvpeq/g(6),tpot(6),tc,pc,n;

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;

//ommon/cout/nin,nout;



tau=1.d0-t/t

p=0.d0;



if(t .lt. ttr)then;

write(nout,*)'<vpeq> t= ',t,'<ttr .vapour pressure will not be',;

*' calculated !';

return;

end if;



if(tau .lt. 0.d0) then;

write(nout,*)'<vpeq> t= ',t,'>tc. vapour pressure will not be',;

*' calculated !';

return;

end if;





if(tau .lt. 1.d-8) then;

p=p

return;

endif;



do 10 i=1,n;

10   p=p+g(i)*tau**tpot(i);



p=pc*exp(p*tc/t);



return;

end;

//***********************************************************************;

blockdata blvpeq;

//***********************************************************************;

implicit real*8(a-h,o-z);



//     vapour pressure;



//ommon /cvpeq/g(6),tpot(6),tc,pc,n;



data tc/647.14d0/, pc/22.064d0/,n/6/;

*      tpot/1.d0,1.5d0,3.d0,3.5d0,4.d0,7.5d0/,;

*      g/-.785823d01, .183991d01,-.117811d02,;

*         .226705d02,-.159393d02, .177516d01/;

end;



//***********************************************************************;

static void dleq(t,dl);

//***********************************************************************;



//     saturated liquid density;



implicit real*8(a-h,o-z);

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;

//ommon/cout/nin,nout;

dimension g(6),tpot(6);



//     saturated liquid density;



data tc/647.14d0/,  dc/322.000d0/, n/6/;

*     tpot/ .33333333333333d00, .66666666666667d00,;

*           .16666666666667d01, .53333333333333d01,;

*           .14333333333333d02, .36666666666667d02/,;

*     g   / .199206d01, .110123d01,-.512506d00,;

*          -.175263d01,-.454485d02,-.675615d06/;



tau=1.d0-t/t

dl=0.d0;



if(t .lt. ttr)then;

write(nout,*)'<dleq> t= ',t,'<ttr. density will not be',;

*' calculated !';

return;

end if;



if (tau.lt.0.d0) then;

write(nout,*)'<dleq> t= ',t,'>tc. density will not be',;

*' calculated !';

return;

end if;



if (tau .lt. 1.d-8) then;

dl=d

return;

endif;



do 10 i=1,n;

10   dl=dl+g(i)*tau**tpot(i);



dl=(dl+1.d0)*d



return;

end;

//***********************************************************************;

static void dveq(t,dv);

//***********************************************************************;

implicit real*8(a-h,o-z);

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;

//ommon/cout/nin,nout;

dimension g(6),tpot(6);



//     saturated vapour density;



data tc/647.14d0/,  dc/322.000d0/, n/6/;

*    tpot/ .33333333333333d00, .66666666666667d00,;

*          .13333333333333d01, .30000000000000d01,;

*          .61666666666667d01, .11833333333333d02/;

*    g  / -.202957d01,-.268781d01,-.538107d01,;

*         -.173151d02,-.446384d02,-.643486d02/;



tau=1.d0-t/t

dv=0.d0;



if(t .lt. ttr)then;

write(nout,*)'<dveq> t= ',t,'<ttr. density will not be',;

*' calculated !';

return;

end if;



if (tau .lt. 0.d0) then;

write(nout,*)'<dveq> t= ',t,'>tc. density will not be',;

*' calculated !';

return;

end if;



if(tau .lt. 1.d-8) then;

dv=d

return;

endif;



do 10 i=1,n;

10  dv=dv+g(i)*tau**tpot(i);



dv=dc*dexp(dv);



return;

end;

//***********************************************************************;

static void dpdteq(t,dpdt);

//***********************************************************************;

implicit real*8 (a-h,o-z);

//ommon /cvpeq/g(6),tpot(6),tc,pc,n;

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;

//ommon/cout/nin,nout;



//  first derivative of vaporpressure p with resp. to temperature t;



tau= 1.d0- t/t

dpdt=0.d0;

p=0.d0;



if(t .lt. ttr)then;

write(nout,*)'<dpdteq> t= ',t,'<ttr. derivative will not be',;

*' calculated !';

return;

end if;



if (tau .lt. 0.d0) then;

write(nout,*)'<dpdteq> t= ',t,'>tc. derivative will not be',;

*' calculated !';

return;

end if;



if (tau .le. 1.d-8) then;

if(dabs(tpot(1)-1.d0).lt. 1.d-8) dpdt= -pc/tc*g(1);

return;

endif;



do 10 i=1,n;

dpdt= dpdt + g(i)*tpot(i)*tau**(tpot(i)-1.d0);

p=p + g(i)*tau**tpot(i);

10 continue;



p=pc*dexp(p*tc/t);

dpdt= (dpdt+dlog(p/pc))*(-p/t);



return;

end;

//***********************************************************************;

static void alpeq(t,alp);

//***********************************************************************;

implicit real*8 (a-h,o-z);

//ommon /calpeq/g(5),tpot(5),tc,a0,da0,dphi0,n;

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;

//ommon/cout/nin,nout;



//  alpha value used to calculate saturated liquid enthalpy and;

//  saturated vapor enthalpy;



teta= t/t

alp=0.d0;



if(t .lt. ttr)then;

write(nout,*)'<alpha> t= ',t,'<ttr. alpha will not be',;

*' calculated !';

return;

end if;



if( teta .gt. 1.d0) then;

write(nout,*)'<alpha> t= ',t,'>tc. alpha will not be',;

*' calculated !';

return;

end if;





alp= da0;



do 10 i=1,n;

alp= alp + g(i)*teta**tpot(i);

10 continue;



alp=alp*a0;



return;

end;

//***********************************************************************;

blockdata balpeq;

//***********************************************************************;

implicit real*8 (a-h,o-z);

//ommon /calpeq/g(5),tpot(5),tc,a0,da0,dphi0,n;



//  alpha value used to calculate saturated liquid enthalpy and;

//  saturated vapor enthalpy;





data  tc/647.14 d0/,a0/1.d0/,da0/ -1135.481615639 d0/,;

*      dphi0/2318.9142d0/,n/5/,;

*      tpot/ -19.d0,1.d0,4.5d0,5.d0,54.5d0/;

*         g/ - .571756d-7 , .268981d4, .129889d3,;

*            - .137181d3  , .968874d0/;



end;

//***********************************************************************;

static void phieq(t,phi);

//***********************************************************************;

implicit real*8 (a-h,o-z);

//ommon /calpeq/g(5),tpot(5),tc,a0,da0,dphi0,n;

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;

//ommon/cout/nin,nout;



//  phi value used to calculate saturated liquid entropy and;

//  saturated vapor entropy;



//  reference value:;



phi0=a0/t



teta= t/t

phi= 0.d0;



if(t .lt. ttr)then;

write(nout,*)'<phi> t= ',t,'<ttr. phi will not be',;

*' calculated !';

return;

end if;



if( teta .gt. 1.d0) then;

write(nout,*)'<phi> t= ',t,'>tc. phi will not be',;

*' calculated !';

return;

end if;



do 10 i=1,n;

tpt=tpot(i);

if(abs(tpt-1.d0) .lt. 1.d-8) then;

phi= phi + g(i)*log(teta);

else;

phi= phi + g(i)*tpt/(tpt-1.d0)*teta**(tpt-1.d0);

end if;

10 continue;



phi= (phi + dphi0)*phi0;



return;

end;

//***********************************************************************;

doubleprecision function pmelt(t,ist);

//***********************************************************************;



//     melting pressure for given temperature;



//     ist .eq. 1 => lower pressure  t<273.16;

//     ist .ne. 1 => higher pressure t<273.16;



implicit real*8(a-h,o-z);

//ommon /cmelteq/g(7),tp(7),tt(7),pt(7),ig(7);

//ommon/cout/nin,nout;



if( t .lt. tt(3) ) then;

pmelt=1.d-10;

write(nout,*)'<pmelt> t= ',t,' <',tt(3),'. no calculation',;

* ' possible !';

return;

end if;



if( ist .eq. 1 .and. t .le. tt(1)) then;

i=1;

goto 20;

end if;



do 10 j=3,7;

i=10-j;

if( ig(i) .eq. 0 ) goto 10;

if( t .ge. tt(i) ) goto 20;

10 continue;



20 continue;



if( t .eq. tt(i)) then;

pmelt=pt(i);

return;

end if;



pi=g(i)*(1.d0 - (t/tt(i))**tp(i));



if( ig(i) .eq. 1 ) then;

pmelt=pt(i)*(pi+1.d0);

else;

pmelt=pt(i)*exp(pi);

end if;



return;

end;

//**********************************************************************************;

static void tmelt(ts,p);

//**********************************************************************************;



//     melting temperature for given pressure;



implicit real*8(a-h,o-z);

//ommon /cmelteq/g(7),tp(7),tt(7),pt(7),ig(7);

//ommon/csub3/ttr,ptr,dltr,dvtr,tb,pb,dlb,dvb;

//ommon/cout/nin,nout;



if(p .lt. ptr)then;

write(nout,*)'<tmelt> p= ',p,'<ptr. ts will not be',;

*' calculated !';

return;

end if;



do 10 j=2,7;

if( ig(j) .eq. 0 ) goto 10;

if( p .lt. pt(j) ) then;

i=j-1;

if( ig(i) .eq. 0 ) i=j-2;

goto 20;

end if;

i=j;

10 continue;



20 continue;



if( p .eq. pt(i)) then;

ts=tt(i);

return;

end if;



if( ig(i) .eq. 1 ) then;

pi=p/pt(i)-1.d0;

else;

pi=dlog(p/pt(i));

end if;



ts=tt(i)*(1.d0 - pi/g(i))**(1.d0/tp(i));



999 return;

end;

//***********************************************************************;

blockdata blmelt;

//***********************************************************************;



//     melting pressure;



implicit real*8(a-h,o-z);

//ommon /cmelteq/g(7),tp(7),tt(7),pt(7),ig(7);

data;

//         ice-i       ice-iii         ice-v     ice-vi       ice-vii;

* g/6.04d5,0.d0,-.295123d0,0.d0,-1.18685d0,-1.07476d0,-.814894d0/;

*tp/ 10.d0,0.d0,     60.d0,0.d0,      8.d0,     4.6d0,    1.92d0/;

*tt/273.16d0,0.,  251.16d0,0.d0,  256.16d0,  273.31d0,    355.d0/;

*pt/.611659d-3,0., 209.9d0,0.d0,   350.1d0,   632.4d0,   2216.d0/;

*ig/       1, 0,         1,   0,         1,         1,         2/;



end;

//***********************************************************************;

doubleprecision function psubl(t);

//***********************************************************************;



//     sublimation-pressure:;



implicit real*8(a-h,o-z);

//ommon/cout/nin,nout;

dimension g(3),tp(3);

data  tt/273.16d0/, pt/.611659d-3/;

* g/ 0.192933313d+02,-0.382215108d+01, 0.165283160d+01/;

*tp/-1.d0,3.d0,5.d0/;



if( t .le. 0.d0 )then;

write(nout,*)'<psubl> t < o . psubl will not be calculated !';

return;

end if;



if ( t .gt. tt ) then;

write(nout,*)'<psubl> t= ',t,' > ttr . psubl will not be';

*,' calculated !';

return;

end if;



if( t .eq. tt) then;

psubl=pt;

return;

end if;



pi=0.d0;



do 10 i=1,3;

10   pi=pi + g(i)*(1.d0 - (t/tt)**tp(i));



psubl=pt*dexp(pi);



return;

end;

**********************************************************************;

//***************************************************************************;

doubleprecision function fni(t,d);

//***************************************************************************;



// this function calculates f's normalized ideal part;

// for einstein-type cp0's.;



implicit real*8(a-h,o-z);

//ommon /cfni/b2,b(7),tpid(7),npol,n;

//ommon/cnorm/tnorm,dnorm;

//ommon /ceps/ eps;

save tsave,dsave,fnis;



if( dabs(t-tsave) .lt. eps ) then;

fni=dlog(d/dsave) + fnis;

return;

end if;



dn= d/dnorm;

tn= tnorm/t;



fni= dlog(dn) + b2*dlog(tn) + b(1) + b(2)*tn;



do 20 i= npol+1,n;

fni= fni + b(i) * dlog(1.d0 - dexp(-tpid(i)*tn));

20 continue;



999 continue;



tsave=t;

dsave=d;

fnis=fni;



return;

end;

//******************************************************************************;

doubleprecision function fnit(t,d);

//******************************************************************************;



//  this subroutine calculates the 1st tn-derivative of f's normalized;

//  ideal part;



implicit real*8(a-h,o-z);

//ommon /cfni/b2,b(7),tpid(7),npol,n;

//ommon/cnorm/tnorm,dnorm;

//ommon /ceps/ eps;



if( dabs(t-tsave) .lt. eps ) then;

fnit = fnits;

return;

end if;



dn= d/dnorm;

tn= tnorm/t;



fnit =  b2/tn + b(2);



do 20 i= npol+1,n;

fnit= fnit + tpid(i)*b(i);

*              *((1.d0-dexp(-tpid(i)*tn))**(-1) - 1.d0);

20 continue;



tsave=t;

dsave=d;

fnits=fnit;



return;

end;

//***************************************************************************;

doubleprecision function fnitt(t,d);

//*******************************************************************************;



// this function calculates the 2nd tn-derivative of;

// f's normalized ideal part;



implicit real*8(a-h,o-z);

//ommon /cfni/b2,b(7),tpid(7),npol,n;

//ommon/cnorm/tnorm,dnorm;

//ommon /ceps/ eps;



if( dabs(t-tsave) .lt. eps ) then;

fnitt = fnitts;

return;

end if;



dn= d/dnorm;

tn= tnorm/t;



fnitt =  -  b2/tn**2;



do 20 i= npol+1,n;

ex=dexp(-tpid(i)*tn);

fnitt= fnitt- tpid(i)**2*b(i) * (1.d0- ex)**(-2) *  ex;

20 continue;



tsave=t;

dsave=d;

fnitts=fnitt;



return;

end;

//**********************************************************************;
//     blockdata fnicoo;
//**********************************************************************;
//      implicit real*8(a-h,o-z);


// this routine sets coefficients for f's normalized ideal part of water;
// of cooper's equation;

//   cooper, j.r. (1982):;
//             representation of the ideal-gas thermodynamic properties;
//             of water. int. j. therm. 3, 35 (1982).;

//     common /cfni/  b2, b(7), tpid(7), npol, n;
//     common /cnullp/t0,d0,f0,h0,u0,s0,g0;
//     data f0/0.d0/,h0/0.d0/, u0/0.d0/,s0/0.d0/,g0/0.d0/,npol/2/,n/7/;

//     data b2/3.00632d0/;

//     there may be machinedependant problems to yield zero values for;
//     entropy (s) and internal energy (u) at the triple point.;
//     in order to yield u=0 and s=0 at the triplepoint in the liquid,;
//     one has to adjust the coeffs. b(1) and b(2) by a call of fnullp.;

//     data (b(i),i=3,7)/ .012436d0,.97315d0,1.27950d0,;
//    *                   .969560d0,.24873d0/,;
//    *  (tpid(i),i=1,7)/  0.d0,1.d0,;
//    *           0.1287202151d+01,0.3537101709d+01,0.7740210774d+01,;
//    *           0.9243749421d+01,0.2750564020d+02/;
//     end;
//***********************************************************************;

static void fnullp;

//***********************************************************************;



//     this routine will adjust the coefs. of the ideal gas function;

//     in order to yield s=u=0 at the triplepoint;



implicit real*8 (a-h,o-z);



//ommon /cfni/  b2, b(7), tpid(7), npol, n;

//ommon /cnullp/t0,d0,f0,h0,u0,s0,g0;

b(2)=b(2) - (fnit(t0,d0) + fnrt(t0,d0));

b(1)=b(1) - (fni (t0,d0) + fnr(t0,d0) );

write (*,*) '         b(1)=',b(1),'b(2)=',b(2);

return;

end;

