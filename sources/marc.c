#include "silmin.h"
#include "recipes.h"

#include "liq_struct_data.h"
#include "sol_struct_data.h"
#include "param_struct_data.h"

SilminState *silminState;
int calculationMode = MODE__MELTS;

double h11    =  -8.7  * 1000.0 * 4.184;
double s11    =   0.0  * 1000.0 * 4.184;
double w11    =   4.5  * 1000.0 * 4.184;
double w14    =  20.8  * 1000.0 * 4.184;    
double w1p4   =  12.4  * 1000.0 * 4.184;
double w15    =  10.0  * 1000.0 * 4.184;
double w1p5   =  14.4  * 1000.0 * 4.184;
double w15p   =  11.7  * 1000.0 * 4.184;
double w1p5p  =   7.0  * 1000.0 * 4.184;    
double w22    =   3.6  * 1000.0 * 4.184;
double h24    =   6.55 * 1000.0 * 4.184;
double s24    =   0.0  * 1000.0 * 4.184;
double w24u   =  12.6  * 1000.0 * 4.184;   
double w2p4u  =  10.9  * 1000.0 * 4.184;
double h25    =   8.05 * 1000.0 * 4.184;
double s25    =   0.0  * 1000.0 * 4.184; 
double w25pu  =  15.3  * 1000.0 * 4.184;
double w2p5u  =  14.4  * 1000.0 * 4.184;
double w45    =   6.0  * 1000.0 * 4.184;
double w45p   =   2.0  * 1000.0 * 4.184;
double w4u5pu =   1.8  * 1000.0 * 4.184;
double h55    =   6.25 * 1000.0 * 4.184;
double s55    =   0.0  * 1000.0 * 4.184; 
double w55    =   0.0  * 1000.0 * 4.184;
double hex    =  -3.6  * 1000.0 * 4.184;  
double sex    =   0.0  * 1000.0 * 4.184; 
double hx     =   2.4  * 1000.0 * 4.184; 
double sx     =   0.0  * 1000.0 * 4.184; 
double woct   =   2.0  * 1000.0 * 4.184;    
double wtet   =   2.0  * 1000.0 * 4.184;
double h33    = -20.0  * 1000.0 * 4.184;
double s33    =   0.0  * 1000.0 * 4.184;
double h23    =   0.0  * 1000.0 * 4.184;
double s23    =   0.0  * 1000.0 * 4.184;
double w33    =   7.0  * 1000.0 * 4.184;
double w13    =  10.0  * 1000.0 * 4.184;
double w1p3   =  15.2  * 1000.0 * 4.184;
double w13p   =  11.3  * 1000.0 * 4.184;
double w1p3p  =   5.9  * 1000.0 * 4.184;
double w2p3u  =  10.0  * 1000.0 * 4.184;
double w23pu  =   9.7  * 1000.0 * 4.184;
double w34    =  12.5  * 1000.0 * 4.184;
double w3p4   =  10.0  * 1000.0 * 4.184;
double w3pu4u =  10.4  * 1000.0 * 4.184;
double w35    =   0.0  * 1000.0 * 4.184;
double w3p5   =  10.0  * 1000.0 * 4.184;
double w35p   =   8.0  * 1000.0 * 4.184;
double w3p5p  =   0.0  * 1000.0 * 4.184;

static void ord_spn(t, x2, x3, x4, x5, s1, s2, s3, s4,
  xmg2tet, xfe2tet, xal3tet, xfe3tet, xcr3tet, xmg2oct, 
  xfe2oct, xal3oct, xfe3oct, xti4oct, xcr3oct, lstop)
  double t, x2, x3, x4, x5, *s1, *s2, *s3, *s4, *xmg2tet, *xfe2tet, 
  	  *xal3tet, *xfe3tet, *xcr3tet, *xmg2oct, *xfe2oct, *xal3oct, 
  	  *xfe3oct, *xti4oct, *xcr3oct;
  int *lstop;
{
  double g11, g33, g55, gx, gex, g23, g24, g25;
  double h5pu5u, s5pu5u, w5u5pu, w4u5u, g5pu5u, h22, s22, g22,
  	  gs1, gs2, gs3, gs4, gx2x2, gx3x3, gx4x4, gx5x5, gs1s1, gs2s2,
  	  gs3s3, gs4s4, gs1s2, gs1s3, gs1s4, gs2s3, gs2s4, gs3s4, gx2x3,
  	  gx2x4, gx2x5, gx3x4, gx3x5, gx4x5, gx2s1, gx2s2, gx2s3, gx2s4,
  	  gx3s1, gx3s2, gx3s3, gx3s4, gx4s1, gx4s2, gx4s3, gx4s4, gx5s1,
  	  gx5s2, gx5s3, gx5s4;
  double r1, relerr, small, s1old, s2old, s4old, a, a1, b1, c1, q;
  int converged, j;

  *lstop = FALSE;
 
  g11 = h11 - t*s11;
  g33 = h33 - t*s33;
  g55 = h55 - t*s55;
  gx  = hx  - t*sx;
  gex = hex - t*sex;
  g23 = h23 - t*s23;
  g24 = h24 - t*s24;
  g25 = h25 - t*s25;
 
  h5pu5u = h55 + 2.0*h24 - h25 + (w24u-w14) + (w4u5pu-w45p)
  	  - (w25pu-w15p);
  s5pu5u = s55 + 2.0*s24 - s25;
  w5u5pu = w55 + (w2p5u+w25pu+w11) - (w1p5+w15p+w22);
  w4u5u = w45 + h25 + (w24u+w2p5u+w11) - (w14+w1p5+w22);
  g5pu5u = h5pu5u - t*s5pu5u;
  w4u5u = w4u5u - t*s25;
  h22 = 2.0*h24+h11+(w24u+w2p4u+w11)-(w14+w1p4+w22);
  s22 = 2.0*s24+s11;
  g22 = h22 - t*s22;
 
  gs1 = 0.5*(-woct + w24u - w14 + 0.5*gx + 0.5*gex + g24);
  gs2 = w11 + g11;
  gs3 = w13p - w13 + g33;
  gs4 = w15p - w15 + g55;
  gx2x2 = -0.25*(wtet + woct + gx);
  gx3x3 = - w13;
  gx4x4 = -w14;
  gx5x5 = -w15;
  gs1s1 = 0.25*(-wtet - woct + gx);
  gs2s2 = -w11;
  gs3s3 = -w33;
  gs4s4 = -w55;
  gs1s2= 0.5*(wtet - w22 + w11 + woct -gx);
  gs1s3 = 0.5*(wtet + woct - w2p3u - w23pu + w22 + w1p3 + w13p 
  	  - w11 - gx);
  gs1s4 = 0.5*(wtet + woct + w22 - w11 - w2p5u - w25pu + w1p5 + w15p 
  	  - gx);
  gs2s3 = w1p3p - w1p3 - w13p + w13;
  gs2s4 = w1p5p - w1p5 - w15p + w15;
  gs3s4 = w3p5p - w3p5 - w35p + w35;
  gx2x3 = 0.5*(w2p3u - w22 -w1p3 + w11 + 2.0*g23);
  gx2x4 = 0.5*(wtet - w24u + w14 + 0.5*gx - 0.5*gex + g24);
  gx2x5 = 0.5*(-w22 + w11 + w2p5u - w1p5 + 2.0*g25);
  gx3x4 = w34 - w14 - w13;
  gx3x5 = w35 - w15 -w13;
  gx4x5 = w45 - w15 - w14;
  gx2s1 = 0.5*(woct - wtet);
  gx2s2 = 0.5*(wtet - w22 + w11 - woct + 2.0*w2p4u - 2.0*w1p4 - gex 
  	  + 2.0*g24);
  gx2s3 = 0.5*(wtet - woct + 2.0*w3pu4u - 2.0*w3p4 - w2p3u - w23pu
  	  + w22 + w1p3 + w13p - w11 - gex + 2.0*g24 - 2.0*g23);
  gx2s4 = 0.5*(wtet - woct - w11 + w22 + 2.0*w4u5pu - 2.0*w45p 
  	  - w2p5u - w25pu + w1p5 + w15p - gex - 2.0*g25 + 2.0*g24);
  gx3s1 = 0.5*(w2p3u - w22 - w1p3 + w11);
  gx3s2 = w1p3 - w13 - w11;
  gx3s3 = w33 - w13p + w13;
  gx3s4 = w35p - w35 - w15p + w15;
  gx4s1 = 0.5*(wtet - w24u + w14 - 0.5*gx + 0.5*gex - g24);
  gx4s2 = -w11 + w1p4 - w14;
  gx4s3 = w3p4 - w34 - w13p + w13;
  gx4s4 = w45p - w45 - w15p + w15;
  gx5s1 = 0.5*(-w22 + w11 + w2p5u - w1p5);
  gx5s2 = -w11 + w1p5 - w15;
  gx5s3 = w3p5 - w35 - w13p + w13;
  gx5s4 = w55 - w15p + w15;
  if((x2 == 1.0) && (x3 == 0.0 ) && (x4 == 0.0 ) && (x5 == 0.0 )) {
    *s2 = 1.0;
    *s1 = 2.0*(*s2) - 1.0;
    *s3 = 0.0;
    *s4 = 0.0;
  } else if((x2 == 1.0) && (x3 == 1.0) && (x4 == 0.0) && (x5 == 0.0)) {
    *s2 = 0.0;
    *s3 = 1.0;
    *s4 = 0.0;
    *s1 = 2.0*(*s3) - 1.0;
  } else if((x2 == 1.0) && (x3 == 0.0) && (x4 == 0.0) && (x5 == 1.0)) {
    *s2 = 0.0;
    *s3 = 0.0;
    *s4 = 0.0;
    *s1 = 2.0*(*s4) - 1.0;
  } else {
    *s1 = 0.5*x2;
    *s2 = x2;
    *s3 = x3;
    *s4 = 0.0;
  }
  r1 = 8.3143;
  j = 0;
  converged = FALSE;
  relerr = 1.0e-6;
  small = 1.0e-12;
  while(!converged && (j <= 1000)) {
    s1old = *s1;
    s2old = *s2;
    s4old = *s4;
 
    if((x2 == 1.0) && (x3 == 0.0) && (x4 == 0.0) && (x5 == 0.0)) {
      *s1 = 2.0*(*s2) - 1.0;
    } else if((x2 == 1.0) && (x3 == 1.0) && (x4 == 0.0) && (x5 == 0.0)) {
      *s1 = 2.0*(*s3) - 1.0;
    } else if((x2 == 1.0) && (x3 == 0.0) && (x4 == 0.0) && (x5 == 1.0)) {
      *s1 = 2.0*(*s4) - 1.0;
    } else {
      a = 2.0*gs1 + 4.0*gs1s1*(*s1) + 2.0*gx2s1*x2 + 2.0*gx4s1*x4 
  	+ 2.0*gx5s1*(x5) + 2.0*gs1s2*(*s2) + 2.0*gs1s4*(*s4)
  	+ 2.0*gx3s1*x3 + 2.0*gs1s3*(*s3);
      a = exp(a/(r1*t));
      c1 = (2.0*x2*x4 + 2.0*x2*(*s2) + 2.0*x2*(*s3) + 2.0*x2*(*s4) - x2*x2) 
  	 - a*(2.0*x2 - x2*x2 - 2.0*x2*(*s2) - 2.0*x2*(*s3) - 2.0*x2*(*s4));
      b1 = (-2.0*x4 - 2.0*(*s2) - 2.0*(*s3) - 2.0*(*s4)) 
  	 - a*(2.0 - 2.0*(*s2) - 2.0*(*s3) - 2.0*(*s4));
      a1 = 1.0 - a;
      q = sqrt(b1*b1 -4.0*a1*c1);
      if(a1 != 0.0) {
  	*s1 = (-b1 -q) / (2.0*a1);
      } else {
  	*s1 = -c1/b1;
      }
    }
 
    if((x2 == 1.0) && (x3 == 0.0) && (x4 == 0.0) && (x5 == 0.0)) {
      a = g22 + w22*(1.0-2.0*(*s2));
      a = exp(a/(r1*t));
      a1 = (1.0 - a);
       b1 = -2.0 - a;
      c1 = 1.0;
      q = sqrt(b1*b1-4.0*a1*c1);
      if(a1 != 0.0) {
  	*s2 = (-b1-q)/(2.0*a1);
      } else {
  	*s2 = -c1/b1;
      }
      *s1 = 2.0*(*s2) - 1.0;
    } else {
      a = gs2 + 2.0*gs2s2*(*s2) + gx2s2*x2 + gx3s2*x3 + gx4s2*x4 
  	+ gx5s2*(x5) + gs1s2*(*s1) +gs2s3*(*s3) + gs2s4*(*s4);
      a = exp(a/(r1*t));
      c1 = (1.0 - 0.5*x2 + 0.5*(*s1) - *s3 - *s4 -x3 + 0.5*x2*x3 
  	 - 0.5*(*s1)*x3 + *s3*x3 );
      c1 = c1 + (*s4*x3 - x4 + 0.5*x2*x4 - 0.5*(*s1)*x4 + *s3*x4 
  	 + *s4*x4 - x5 + 0.5*x2*x5);
      c1 = c1 + (-0.5*(*s1)*x5 + *s3*x5 + *s4*x5);
      c1 = c1 - a*(x4 - 0.5*x2 - 0.5*(*s1) + *s3 + *s4);
      c1 = c1 - a*(-x4*x3 + 0.5*x2*x3 + 0.5*(*s1)*x3 - *s3*x3 - *s4*x3);
      c1 = c1 - a*(-x4*x4 + 0.5*x2*x4 + 0.5*(*s1)*x4 - *s3*x4 - *s4*x4);
      c1 = c1 - a*(-x4*x5 + 0.5*x2*x5 + 0.5*(*s1)*x5 - *s3*x5 - *s4*x5);
      b1 = (-1.0 + x3 + x4 + x5 -1.0 + 0.5*x2 - 0.5*(*s1) + *s3 + *s4);
      b1 = b1 - a*(1.0 - x3 - x4 - x5 + x4 - 0.5*x2 - 0.5*(*s1) 
  	 + *s3 + *s4);
      a1 = 1.0 - a;
      q = sqrt(b1*b1-4.0*a1*c1);
      if(a1 != 0.0) {
  	 *s2 = (-b1-q) / (2.0*a1);
      } else {
  	*s2 = -c1/b1;
      }
    }
 
    if((x2 == 1.0) && (x3 == 0.0) && (x4 == 0.0) && (x5 == 1.0)) {
      a = g5pu5u + w5u5pu*(1.0-2.0*(*s4));
      a = exp(a/(r1*t));
      a1 = (1.0 - a);
      b1 = -2.0 - a;
      c1 = 1.0;
      q = sqrt(b1*b1-4.0*a1*c1);
      if(a1 != 0.0) {
  	*s4 = (-b1-q)/(2.0*a1);
      } else {
  	*s4 = -c1/b1;
      }
      *s1 = 2.0*(*s4) - 1.0;
    } else { 
      a = gs4 + 2.0*gs4s4*(*s4) + gx2s4*x2 + gx3s4*x3 + gx4s4*x4 
  	+ gx5s4*(x5) + gs1s4*(*s1) + gs2s4*(*s2) + gs3s4*(*s3);
      a = exp(a/(r1*t));
      c1 = (x5 - 0.5*x2*x5 + 0.5*(*s1)*x5 - *s2*x5 - *s3*x5) -a*(x4*x5 
  	 - 0.5*x2*x5 - 0.5*(*s1)*x5 + *s2*x5 + *s3*x5);
      b1 = (-x5 -1.0 + 0.5*x2 - 0.5*(*s1) + *s2 + *s3) 
  	 - a*(x5 + x4 - 0.5*x2 - 0.5*(*s1) + *s2 + *s3);
      a1 = 1.0- a;
      q = sqrt(b1*b1 -4.0*a1*c1);
      if(a1 != 0.0) {
  	*s4 = (-b1 -q) / (2.0*a1);
      } else {
  	*s4 = -c1/b1;
      }
    }
 
    j = j + 1;
    if(j > 1000) {
      printf("Iteration limit (1000) exceeded in ord_spn!\n");
      *lstop = TRUE;
    }
    converged = (fabs(*s1-s1old) <= relerr*fabs(*s1)) | (fabs(*s1-s1old) <= small);
    converged = converged  & ((fabs(*s2-s2old) <= relerr*fabs(*s2)) | (fabs(*s2-s2old) <= small) );
    converged = converged  & ((fabs(*s4-s4old) <= relerr*fabs(*s4)) | (fabs(*s4-s4old) <= small) );
 
  }
 
  *xmg2tet = 0.5*(x2 + *s1);
  *xfe2tet = (x4 - 0.5*x2 - 0.5*(*s1) + *s2 + *s3 + *s4);
  *xal3tet = (1.0 - x3 - x4 - x5 - *s2);
  *xfe3tet = x5 - *s4;
  *xcr3tet = x3 - *s3;
  *xmg2oct = 0.25*(x2 - *s1);
  *xfe2oct = 0.25*(2.0 - x2 + *s1 - 2.0*(*s2) - 2.0*(*s3) - 2.0*(*s4));
  *xal3oct = 0.5*(1.0 - x3 - x4 - x5 + *s2);
  *xfe3oct = 0.5*(x5 + *s4);
  *xcr3oct = 0.5*(x3 + *s3);
  *xti4oct = 0.5*x4;
 
}

double olvDat[19] = {
 38.899, 0.062, 0.002, 0.0,  0.205, 16.767, 0.466, 43.493, 0.0, 0.0, 0.006, 0.007, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double spn1Dat[19] = {
  0.073, 1.950, 7.106, 0.0, 57.078, 27.676, 1.072,  3.674, 0.0, 0.0, 0.027, 0.018, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double opxDat[19] = {
 55.6236, 0.1518, 0.1984, 0.0,  0.171, 10.3729, 0.4958, 31.1087, 0.0, 0.0, 0.7989, 0.0067, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
double spn2Dat[19] = {
  0.024, 1.907, 7.049, 0.0, 56.629, 27.837, 1.036,  3.694, 0.0, 0.0, 0.032, 0.003, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

int main(int argc, char*argv[]) {
   int i, j, itemp;
   int nr = nlc - 1;
   float ftemp;
   double t, p, *grams, *moles, *elements, *rOlv, *rSpn, *rOpx, *muOlv, *muSpn, *muOpx, logfO2, tOld, deltaG, deltaGold;
   int indexOlv = -1, indexSpn = -1, indexOpx = -1, indexFa = -1, indexFo = -1, indexSp = -1, indexHc = -1, indexMg = -1, 
       indexDi = -1, indexEn = -1, indexHd = -1, iter; 
   int doOlvSpn = 1;
   int doOpxSpn = 0;

   InitComputeDataStruct();
   
   if (indexOlv == -1) { 
     for (i=0; i<npc; i++) if (solids[i].type == PHASE && !strcmp(solids[i].label, "olivine")) indexOlv = i; 
     for (i=0; i<solids[indexOlv].na; i++) {
       if (!strcmp(solids[indexOlv+1+i].label, "forsterite")) indexFo = i;
       if (!strcmp(solids[indexOlv+1+i].label, "fayalite"  )) indexFa = i;
     }
   }
   if (indexOlv == -1) { printf("Error: Internal - index\n"); exit(0); }

   if (indexSpn == -1) { 
     for (i=0; i<npc; i++) if (solids[i].type == PHASE && !strcmp(solids[i].label, "spinel")) indexSpn = i; 
     for (i=0; i<solids[indexSpn].na; i++) {
       if (!strcmp(solids[indexSpn+1+i].label, "spinel")) indexSp = i;
       if (!strcmp(solids[indexSpn+1+i].label, "hercynite"  )) indexHc = i;
       if (!strcmp(solids[indexSpn+1+i].label, "magnetite"  )) indexMg = i;
     }
   }
   if (indexSpn == -1) { printf("Error: Internal - index\n"); exit(0); }

   if (indexOpx == -1) { 
     for (i=0; i<npc; i++) if (solids[i].type == PHASE && !strcmp(solids[i].label, "orthopyroxene")) indexOpx = i; 
     for (i=0; i<solids[indexOpx].na; i++) {
       if (!strcmp(solids[indexOpx+1+i].label, "diopside")) indexDi = i;
       if (!strcmp(solids[indexOpx+1+i].label, "clinoenstatite"  )) indexEn = i;
       if (!strcmp(solids[indexOpx+1+i].label, "hedenbergite"  )) indexHd = i;
     }
   }
   if (indexOpx == -1) { printf("Error: Internal - index\n"); exit(0); }
   
   //doOlvSpn = 0;
   //doOpxSpn = 1;

   if (argc == 1) {
     printf("Input a temperature in (C):"); scanf("%f", &ftemp); t = (double) ftemp; getchar();
   } else {
     t = atof(argv[1]);
   }
   if (t == 0.0) t = 1200.0;
   else { t += 273.15; doOlvSpn = 0; doOpxSpn = 0;}
   
   if (argc == 1) {
     printf("Input a pressure in (bars):"); scanf("%f", &ftemp); p = (double) ftemp; getchar();
   } else {
     p = atof(argv[2]);
   }
   
   moles    = (double *) malloc((size_t)  nc*sizeof(double));
   elements = (double *) malloc((size_t) 107*sizeof(double));
   grams    = (double *) malloc((size_t)  nc*sizeof(double));
   rOlv     = (double *) malloc((size_t)  nr*sizeof(double));
   rSpn     = (double *) malloc((size_t)  nr*sizeof(double));
   rOpx     = (double *) malloc((size_t)  nr*sizeof(double));
   muOlv    = (double *) malloc((size_t)  nc*sizeof(double));
   muSpn    = (double *) malloc((size_t)  nc*sizeof(double));
   muOpx    = (double *) malloc((size_t)  nc*sizeof(double));

   for (i=0; i<nc; i++) {
     if (argc == 1) {
       printf("Input wt%% of %5.5s in olivine: ", bulkSystem[i].label);
       scanf("%f", &ftemp); grams[i] = (double) ftemp; getchar();
       //grams[i] = olvDat[i];
     } else {
       grams[i] = atof(argv[3+i]);
     }
     moles[i] = grams[i]/bulkSystem[i].mw;
   }
   for (i=0; i<107; i++) {
     elements[i] = 0.0;
     for (j=0; j<nc; j++) if ((bulkSystem[j].oxToElm)[i] != 0) elements[i] += ((double) (bulkSystem[j].oxToElm)[i])*moles[j];
   }
   conOlv(FIRST,  SECOND, t, p, elements, moles, NULL, NULL, NULL, NULL, NULL, NULL);
   if(!testOlv(SIXTH, t, p, 0, 0, NULL, NULL, NULL, moles)) { printf("Error: Bad olivine\n"); exit(0); }
   conOlv(SECOND, THIRD, t, p, NULL, moles, rOlv, NULL, NULL, NULL, NULL, NULL);

   for (i=0; i<nc; i++) {
     if (argc == 1) {
       printf("Input wt%% of %5.5s in spinel: ", bulkSystem[i].label);
       scanf("%f", &ftemp); grams[i] = (double) ftemp; getchar();
       //grams[i] = spn2Dat[i];
     } else {
       grams[i] = atof(argv[nc+3+i]);
     }
     moles[i] = grams[i]/bulkSystem[i].mw;
   }
   for (i=0; i<107; i++) {
     elements[i] = 0.0;
     for (j=0; j<nc; j++) if ((bulkSystem[j].oxToElm)[i] != 0) elements[i] += ((double) (bulkSystem[j].oxToElm)[i])*moles[j];
   }
   conSpn(FIRST,  SECOND, t, p, elements, moles, NULL, NULL, NULL, NULL, NULL, NULL);
   if(!testSpn(SIXTH, t, p, 0, 0, NULL, NULL, NULL, moles)) { printf("Error: Bad spinel\n"); exit(0); }
   conSpn(SECOND, THIRD, t, p, NULL, moles, rSpn, NULL, NULL, NULL, NULL, NULL);

   for (i=0; i<nc; i++) {
     if (argc == 1) {
       printf("Input wt%% of %5.5s in orthopyroxene: ", bulkSystem[i].label);
       scanf("%f", &ftemp); grams[i] = (double) ftemp; getchar();
       //grams[i] = opxDat[i];
     } else {
       grams[i] = atof(argv[2*nc+3+i]);
     }
     moles[i] = grams[i]/bulkSystem[i].mw;
   }
   for (i=0; i<107; i++) {
     elements[i] = 0.0;
     for (j=0; j<nc; j++) if ((bulkSystem[j].oxToElm)[i] != 0) elements[i] += ((double) (bulkSystem[j].oxToElm)[i])*moles[j];
   }
   conOpx(FIRST,  SECOND, t, p, elements, moles, NULL, NULL, NULL, NULL, NULL, NULL);
   if(!testOpx(SIXTH, t, p, 0, 0, NULL, NULL, NULL, moles)) { printf("Error: Bad orthopyroxene\n"); exit(0); }
   conOpx(SECOND, THIRD, t, p, NULL, moles, rOpx, NULL, NULL, NULL, NULL, NULL);

   if (doOlvSpn || doOpxSpn) {
     /* First calculate olv-spn temperature */
     tOld = t;
     deltaG = 1000.0;
     deltaGold = 0.0;
     iter = 0;
     while ((fabs(deltaG) > 0.001) && (iter < 1000)) {  	  
       static double h21 = -88.4*4.184*1000.0;    
       static double s21 = -0.0098*4.184*1000.0;
       double x2 = rSpn[0];
       double x3 = rSpn[1];
       double x4 = rSpn[2];
       double x5 = rSpn[3];
       double s1, s2, s3, s4, xmg2tet, xfe2tet, xal3tet, xfe3tet, xcr3tet, xmg2oct, 
     	      xfe2oct, xal3oct, xfe3oct, xti4oct, xcr3oct, g11, g33, g55, gx, gex, g23, g24, g25, g21;
       int lstop;
   	   
   	   if (doOlvSpn) {   
         actOlv(SECOND,  t, p, rOlv, NULL, muOlv, NULL);
         gibbs(t, p, (char *) solids[indexOlv+1+indexFo].label, &(solids[indexOlv+1+indexFo].ref), NULL, NULL, &solids[indexOlv+1+indexFo].cur);
         muOlv[indexFo] += solids[indexOlv+1+indexFo].cur.g;
         gibbs(t, p, (char *) solids[indexOlv+1+indexFa].label, &(solids[indexOlv+1+indexFa].ref), NULL, NULL, &solids[indexOlv+1+indexFa].cur);
         muOlv[indexFa] += solids[indexOlv+1+indexFa].cur.g;
       } else {
         actOpx(SECOND,  t, p, rOpx, NULL, muOpx, NULL);
         gibbs(t, p, (char *) solids[indexOpx+1+indexDi].label, &(solids[indexOpx+1+indexDi].ref), NULL, NULL, &solids[indexOpx+1+indexDi].cur);
         muOpx[indexDi] += solids[indexOpx+1+indexDi].cur.g;
         gibbs(t, p, (char *) solids[indexOpx+1+indexHd].label, &(solids[indexOpx+1+indexHd].ref), NULL, NULL, &solids[indexOpx+1+indexHd].cur);
         muOpx[indexHd] += solids[indexOpx+1+indexHd].cur.g;
         muOlv[indexFo] = 2.0*muOpx[indexDi];
         muOlv[indexFa] = 2.0*muOpx[indexHd];
       }

       actSpn(SECOND,  t, p, rSpn, NULL, muSpn, NULL);
       gibbs(t, p, (char *) solids[indexSpn+1+indexSp].label, &(solids[indexSpn+1+indexSp].ref), NULL, NULL, &solids[indexSpn+1+indexSp].cur);
       muSpn[indexSp] += solids[indexSpn+1+indexSp].cur.g;
       gibbs(t, p, (char *) solids[indexSpn+1+indexHc].label, &(solids[indexSpn+1+indexHc].ref), NULL, NULL, &solids[indexSpn+1+indexHc].cur);
       muSpn[indexHc] += solids[indexSpn+1+indexHc].cur.g;

       ord_spn(t, x2, x3, x4, x5, &s1, &s2, &s3, &s4, &xmg2tet, &xfe2tet, &xal3tet, &xfe3tet, &xcr3tet, &xmg2oct, 
     	 &xfe2oct, &xal3oct, &xfe3oct, &xti4oct, &xcr3oct, &lstop);
   	  		  
       g11 = h11 - t*s11;
       g33 = h33 - t*s33;
       g55 = h55 - t*s55;
       gx  = hx  - t*sx;
       gex = hex - t*sex;
       g23 = h23 - t*s23;
       g24 = h24 - t*s24;
       g25 = h25 - t*s25;
       g21 = h21 - t*s21;
 
       deltaG = 0.5*(muOlv[indexFo] - muOlv[indexFa])  
     	  - ( 8.3143*t*log(xmg2tet/xfe2tet) + w2p5u*x5 - w22*x5 - w1p5*x5
     	      + w11*x5 + g25*x5 + wtet*x4 - w24u*x4 + w14*x4 + w2p3u*x3
     	      - w22*x3 - w1p3*x3 + w11*x3 + g23*x3 - wtet*x2 - gx*x2/2.0
     	      + s4*wtet + s3*wtet + s2*wtet - s1*wtet + s4*w4u5pu 
     	      - s4*w45p + s3*w3pu4u - s3*w3p4 - s4*w2p5u + s2*w2p4u
     	      - s3*w2p3u - s4*w25pu + w24u - s3*w23pu + s4*w22 + s3*w22
     	      - s2*w22 + s4*w1p5 - s2*w1p4 + s3*w1p3 + s4*w15p - w14 
     	      + s3*w13p - s4*w11 - s3*w11 + s2*w11 - gx*s4/2.0 
     	      - gex*s4/2.0 - g25*s4 + g24*s4 - gx*s3/2.0 - gex*s3/2.0
     	      + g24*s3 - g23*s3 - gx*s2/2.0 - gex*s2/2.0 + g24*s2 
     	      + gx*s1/2.0 + gx/2.0 + gex/2.0 + g24 + g21 
   	    );
   	  	  
       if (t == tOld) {
     	 t += 20.0;  
     	 deltaGold = deltaG;
       } else {
     	 double deltaGdT = (deltaG-deltaGold)/(t-tOld);
     	 tOld = t;  
     	 deltaGold = deltaG;  
     	 t += -deltaG/deltaGdT;
       }
       iter++;
       if (argc == 1) printf("iter = %d, deltaG = %g, t = %g\n", iter, deltaG, t);
     }
     if (iter == 1000) { printf("Iteration limit exceeded in Olv-Spn"); exit(0); }
   } else {
     actOlv(SECOND,  t, p, rOlv, NULL, muOlv, NULL);
     gibbs(t, p, (char *) solids[indexOlv+1+indexFo].label, &(solids[indexOlv+1+indexFo].ref), NULL, NULL, &solids[indexOlv+1+indexFo].cur);
     muOlv[indexFo] += solids[indexOlv+1+indexFo].cur.g;
     gibbs(t, p, (char *) solids[indexOlv+1+indexFa].label, &(solids[indexOlv+1+indexFa].ref), NULL, NULL, &solids[indexOlv+1+indexFa].cur);
     muOlv[indexFa] += solids[indexOlv+1+indexFa].cur.g;

     actSpn(SECOND,  t, p, rSpn, NULL, muSpn, NULL);
     gibbs(t, p, (char *) solids[indexSpn+1+indexSp].label, &(solids[indexSpn+1+indexSp].ref), NULL, NULL, &solids[indexSpn+1+indexSp].cur);
     muSpn[indexSp] += solids[indexSpn+1+indexSp].cur.g;
     gibbs(t, p, (char *) solids[indexSpn+1+indexHc].label, &(solids[indexSpn+1+indexHc].ref), NULL, NULL, &solids[indexSpn+1+indexHc].cur);
     muSpn[indexHc] += solids[indexSpn+1+indexHc].cur.g;
   }

   if (argc == 1) printf("T (C): %20.13g\n", t-273.15);
   else           printf("\n%20.13g,", t-273.15);

   actOpx(SECOND,  t, p, rOpx, NULL, muOpx, NULL);
   gibbs(t, p, (char *) solids[indexOpx+1+indexDi].label, &(solids[indexOpx+1+indexDi].ref), NULL, NULL, &solids[indexOpx+1+indexDi].cur);
   muOpx[indexDi] += solids[indexOpx+1+indexDi].cur.g;
   gibbs(t, p, (char *) solids[indexOpx+1+indexEn].label, &(solids[indexOpx+1+indexEn].ref), NULL, NULL, &solids[indexOpx+1+indexEn].cur);
   muOpx[indexEn] += solids[indexOpx+1+indexEn].cur.g;
   gibbs(t, p, (char *) solids[indexOpx+1+indexHd].label, &(solids[indexOpx+1+indexHd].ref), NULL, NULL, &solids[indexOpx+1+indexHd].cur);
   muOpx[indexHd] += solids[indexOpx+1+indexHd].cur.g;
   
   gibbs(t, p, (char *) solids[indexSpn+1+indexMg].label, &(solids[indexSpn+1+indexMg].ref), NULL, NULL, &solids[indexSpn+1+indexMg].cur);
   muSpn[indexMg] += solids[indexSpn+1+indexMg].cur.g;
   
   logfO2 = 3.0*(2.0*muOpx[indexHd]-2.0*muOpx[indexDi]+muOpx[indexEn]) + 2.0*muSpn[indexMg] - 6.0*muOlv[indexFa];
   gibbs(t, (double) 1.0, (char *) "o2", &(oxygen.ref), NULL, NULL, &(oxygen.cur));
   logfO2 -= oxygen.cur.g;
   logfO2 /= 8.3143*t*log(10.0);
   
   if (argc == 1) printf("log10 fO2: %20.13g\n", logfO2);
   else           printf("%20.13g\n", logfO2);
   
   free(moles);
   free(grams);
   free(elements);
   free(rOlv);
   free(rSpn);
   free(rOpx);
   free(muOlv);
   free(muSpn);
   free(muOpx);

   exit(0);
}
