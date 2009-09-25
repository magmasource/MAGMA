      SUBROUTINE SHI(XN,T,P,V,GSHI,GI)
CC
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C        CALCULATION OF ENTHALPY, ENTROPY, HEAT CAPACITY,              C
C                         GIBBS FREE ENERGY, (MU0/RT),                 C
C                            ACTIVITY AND FUGACITY                     C
C                  FOR A FLUID MIXTURE WITH COMPOSITION X              C
C                           AT P (bar) AND T (K)                       C
C ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ C
C                                                                      C
C                Pingfang SHI, and  Surendra K. Saxena                 C
C                ------------       ------------------                 C
C                       Planetary Geochemistry                         C
C                       Uppsala University                             C
C                       Uppsala                                        C
C                       SWEDEN                                         C
C                                                                      C
C                Yingwei FEI                                           C
C                ------------                                          C
C                       Geophysics Laboratory                          C
C                       Carnegie Institution                           C
C                       Washington D.C.                                C
C                       USA                                            C
C                                                                      C
C ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ C
C                                                                      C
C    Fluid System:  C-H-O-S-N-Ar Fluids.                               C
C    P,T-Range:      P = 1 bar --> 5000 bars                           C
C                    T = Critical Points --> 2273.15 K (0.001-1 kbar)  C
C                                        --> 3273.15 K (1 - 5 kbar)    C
C   ----------------------------------------------------------------   C
C                                                                      C
CC  Fluid Models:                                                      C
C    1. Pure Fluid Species:                                            C
C           H2O --- Saul-Wagner (1987, 1989)                           C
C           CO2 --- Jacobs-Kerrick (1981)                              C
C           CH4 --- Jacobs-Kerrick (1981)                              C
C                   Friend et al. (1989);  Grevel (1990)               C
C           CO, O2, H2, S2, SO2, COS, H2S --- Saxena-Fei (1987, 1988)  C
C                                             Shi-Saxena (1992)        C
C           N2, NH3, Ar --- Belonoshko-Saxena (1992)                   C
C                                                                      C
C   2. Fluid Mixtures:                                                 C
C        C-H-O-S-N-Ar --- Binary joins: Interaction-Potential Theory.  C
C                                Saxena-Fei (1988)                     C
C                                Shi-Saxena (1992)                     C
C                                Belonoshko-Shi-Saxena (1992)          C
C                       Ternary or higher-order: Kohler Formulation.   C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
CC
      PARAMETER (NGAS = 13)
      PARAMETER(LA=15,LB=20,LC=20,LF=7)
      DIMENSION XN(NGAS),GI(NGAS)
      COMMON /SALLA/ A(LA,LB), B0(LB), GV(LA), PI(2*LB), VGAS(LA), L
      COMMON /SALLI/ Y(LA), MF(LC+1), ML(LC+1), MP, MV
      COMMON /SALLR/ AKTFLN(LA), PX, RT, VX, X(LA), YTOT(LC)
      COMMON /SHECP/ C(LA,LF,8), HF(LA), S(LA)
      COMMON /SHEOM/ HOM(LA,LF-1), TOM(LA,LF-1), NOM(LA)
      COMMON /SSGGV/ GBAR, GE(LA,8), VT(LA,5), V0(LA), IGT(8), KVAL, MGT
      COMMON /STEXT/ IDENT(LA)
      CHARACTER IDENT*11
      DIMENSION GPVT(LA)
C      DIMENSION G(LA),GVT(LA),GVP(LA),GPVT(LA)
C
      IDENT(1) = ' H2O     '
      IDENT(2) = ' CO2     '
      IDENT(3) = ' CH4     '
      IDENT(4) = ' CO      '
      IDENT(5) = ' O2      '
      IDENT(6) = ' H2      '
      IDENT(7) = ' S2      '
      IDENT(8) = ' SO2     '
      IDENT(9) = ' COS     '
      IDENT(10)= ' H2S     '
      IDENT(11)= ' N2      '
      IDENT(12)= ' NH3     '
      IDENT(13)= ' Ar      '
C
      RT = 8.31451*T
C

      DO 1 IGAS = 1, NGAS
             X(IGAS) = XN(IGAS)
1     CONTINUE

      M = 1
      MF(M) = 1
      ML(M) = NGAS

C******    Calculation of Pure Fluid Species:
      CALL GAS(T, P, VVVVV, GV)

C******    Calculation of Fluid Mixtures:
      IF ( T .LT. 1873.0)  CALL FACTOR(M, XN, T, P, V)
        GSHI = 0.0
        EPS0 = 1.0E-50
        V = 0.0

C
      DO 10 I = 1, NGAS
         GPVT(I) = GV(I)*RT
         IF (XN(I) .GT. EPS0) THEN
            IF ( T .LT. 1873.0) GPVT(I) = GPVT(I) + AKTFLN(I)*RT
         END IF  
         V = V + VGAS(I)*XN(I)
         GI(I) = GPVT(I)
 10      GSHI = GSHI + GPVT(I)*XN(I)
c      END DO
C
      RETURN
      END

CCC
      SUBROUTINE GAS(T, P, VVVVV, G)
CC
CCC*****************************************************************
C                                                                  *
C        CALCULATION OF GIBBS FREE ENERGIES FOR REAL GASES         *
C                    at P (bar) and T (K)                          *
C                                                                  *
C    MAXIMUM NO. OF GAS PHASES IS 13                               *
C        GAS PHASES HAVE TO BE ARRANGED IN ORDER:                  *
C     H2O, CO2, CH4, CO, O2, H2, S2, SO2, COS, H2S, N2, N3 and Ar  *
C     (1    2    3    4   5   6   7   8    9   10   11  12     13) *
C                                                                  *
CCC*****************************************************************
CC
C      IMPLICIT DOUBLE PRECISION(A-H,O-Z)
      PARAMETER(LA=15,LB=20,LC=20,LF=7)
      COMMON /SALLA/ A(LA,LB), B0(LB), GV(LA), PI(2*LB), VGAS(LA), L
      COMMON /SALLI/ Y(LA), MF(LC+1), ML(LC+1), MP, MV
      COMMON /SALLR/ AKTFLN(LA), PX, RT, VX, X(LA), YTOT(LC)
      COMMON /SHECP/ C(LA,LF,8), HF(LA), S(LA)
      COMMON /SHEOM/ HOM(LA,LF-1), TOM(LA,LF-1), NOM(LA)
      COMMON /SSGGV/ GBAR, GE(LA,8), VT(LA,5), V0(LA), IGT(8), KVAL, MGT
      COMMON /STEXT/ IDENT(LA)
      CHARACTER IDENT*11
      DIMENSION Z(LA),TCR(10),PCR(10),TR(LA),PR(LA),HA(LA),HB(LA),HC(LA)
      DIMENSION GVP(LA),GVPK(LA),HD(LA),AA1(10),BB1(10),CC1(10)
      DIMENSION DD1(10),EE1(10),FF1(10),GG1(10),HH1(10)
      DIMENSION G(LA)
C      DIMENSION G(LA),GVT(LA),TPOT(8)

      PARAMETER (EM1=1.D-1,EM4=1.D-4,EP3=1.D3,EP6=1.D6,R=8.31451D0,
     *RN0=0.D0,RN1=1.D0,RN2=2.D0,RN3=3.D0,RN4=4.D0,RN5=5.D0,RN6=6.D0,
     *RN12=12.D0,RN20=20.D0,
     *RNA=298.15D0,RNB=5.D-9,
     *FHOA1=-7.025D-1,FHOA2=1.16D-3,FHOA3=9.96799D1)
      PARAMETER (
     *FHOB1=2.143D-1,FHOB2=-3.1423D-14,
     *FHOC1=-2.249D-06,FHOC2=-1.459D-1,FHOC3=2.169D-15,
     *HHOA1=4.0446D0,HHOA2=-7.8042D5,HHOA3=2.1698D+8,HHOA4=-3.9410D-1,
     *HHOB1=1.2428D-1,HHOB2=4.5709D+1,HHOB3=-1.1006D+4,
     *HHOC1=-1.1961D-8,HHOC2=-5.2680D-4,HHOC3=1.2440D-1)
      PARAMETER (
     *HHOC4=1.0726D-11,HHOC5=-6.9428D-11,
     *HHOD1=-4.6070D-13,HHOD2=1.5981D-9,HHOD3=-3.7239D-7,
     *HHOD4=-2.1564D-36,
     *COB1=9.827D-2,COB2=-2.709D-1,COC1=1.472D-2,COC2=-1.03D-3,
     *FCOA1=1.D0,FCOA2=-5.917D-1,
     *FCOB1=9.122D-2)
      PARAMETER (
     *FCOC1=-1.4164D-04,FCOC2=-2.8349D-06,
     *HCOA1=2.0614D0,HCOA2=-2.2351D0,HCOA3=-3.9411D-1,
     *HCOB1=5.5125D-2,HCOB2=3.9344D-2,
     *HCOC1=-1.8935D-6,HCOC2=-1.1092D-5,HCOC3=-2.1892D-5,
     *HCOD1=5.0527D-11,HCOD2=-6.3032D-21,
     *HA1=2.2615D0,HA2=-68.712D0,HA3=-1.0537D4,HA4=-1.6936D-1,
     *HB1=-0.26707D-3,HB2=0.20173D0,HB3=4.57586D0,HB4=0.314515D-4,
     *HC1=-2.33755D-09,HC2=0.34091D-6,HC3=-14.188D-04,HC4=3.0117D-10,
     *HD1=-3.2606D-15,HD2=2.4402D-12,HD3=-2.4027D-09)

      DATA GVP/LA*RN0/

      DATA TCR/6.4725D2,3.0415D2,1.9105D2,1.3315D2,1.5475D2,3.325D1,
     * 2.0815D2,4.3095D2,3.7795D2,3.7355D2/
      DATA PCR/2.211925D2,7.38659D1,4.64069D1,3.49571D1,5.07638D1,
     * 1.29696D1, 7.2954D1,7.87295D1,6.58612D1,9.00779D1/
      DATA AA1/-222.943D0,-38.315D0,-15.029D0,-4.650D0,-8.082D0,0.604D0,
     * 0.27243D1, 0.91198D2, 0.57637D1, -0.12649D4/
      DATA BB1/2.9865D-2,5.4832D-2,5.5411D-2,5.6794D-2,5.6237D-2,5.7324D
     *-2, 0.57308D-1, 0.63955D-1, 0.57544D-1, -0.34877D-1/
      DATA CC1/0.0D0, 0.0D0, 0.0D0, 0.0D0, 0.0D0, 0.0D0,
     * -0.33599D3, -0.11443D5, -0.29339D3, 0.95952D5/
      DATA DD1/0.0D0, 0.0D0, 0.0D0, 0.0D0, 0.0D0, 0.0D0,
     *  0.32792D-7, -0.84474D-6, -0.14216D-7, 0.71146D-6/
      DATA EE1/0.0D0, 0.0D0, 0.0D0, 0.0D0, 0.0D0, 0.0D0,
     * -0.14595D6, 0.26843D6, -0.17878D7, 0.45675D5/
      DATA FF1/0.0D0, 0.0D0, 0.0D0, 0.0D0, 0.0D0, 0.0D0,
     * -0.30694D-11, 0.55427D-10, 0.90888D-12, 0.10878D-8/
      DATA GG1/0.0D0, 0.0D0, 0.0D0, 0.0D0, 0.0D0, 0.0D0,
     * 0.29688D3, 0.43630D8, 0.27291D9, -0.43608D10/
      DATA HH1/35.9794,6.2055,2.8948,1.1645,1.6723,0.20685,
     * -0.21840D-1, -0.12085D2, -0.16838D0, 0.18265D3/

C
      RT = R*T

CC
CC    *****  H2O  *****
C
      I = 1

CCCCCCCCC
CC CHOOSING THE P(V,T) FORMULATION FROM Saul-Wagner MODEL
CC          Saul & Wagner (1987, 1989)
CC                           when T < 1273.15 K and P < 5 kbar.

      IF (T .GT. 1273.15) GO TO 502
      CALL H2O(T,P,V,GG)
      VGAS(I) = V
      GVP(I) = GG/RT
      Z(I) = P*VGAS(I)/(10.0*RT)
      GV(I) = G1BAR(I,T) + GVP(I)
      GO TO  9001

CCCCCCCCC
CC CHOOSING THE V(P,T) FORMULATION IN SEVERAL PRESSURE SEGMENTS
CC       of Saxena-Fei (1987, 1988) and Shi-Saxena (1992)
CC                           when T > 1273.15 K and P < 5 kbar.

502   PR(I) = P/PCR(I)
      TR(I) = T/TCR(I)

      IF (P .GT. 10.00 .OR. P .EQ. 10.00) GO TO 6771
      VGAS(I) = (0.89959E+0 + 0.40267E-3*T +0.71835E+3/T
     *     -0.36840E+6/T**2.0 +0.54379E+8/T**3.0 -0.23965E+0*LOG(T))
      VGAS(I) = VGAS(I) +(0.17952E-1 -0.25984E-4*T -0.73371e+2/T
     *     +0.37138E+5/T**2.0 -0.66324E+7/T**3.0 +0.68494E-2*LOG(T))*P
      VGAS(I) = VGAS(I) +(0.18520E+2 -0.14375E-3*T -0.25510E+4/T
     *     +0.92763E+6/T**2.0 -0.14046E+9/T**3.0 -0.98457*LOG(T))/P
      VGAS(I) = RT*VGAS(I)
      Z(I) = 1 + (-2.20960*T**0.5 + 3.35460E-8*T**3.0)/VGAS(I)
     *     + (3.4569E-5*T**2.5 + 64.9764*LOG(T))/VGAS(I)**2.0
      GVPK(I) = 0.00
      GVP(I) = (0.89959E+0 + 0.40267E-3*T +0.71835E+3/T -0.36840E+6
     *     /T**2.0 +0.54379E+8/T**3.0 -0.23965E+0*LOG(T))
     *       *(P-1.0)/10.0
      GVP(I) = GVP(I) +(0.17952E-1 -0.25984E-4*T -0.73371E+2/T
     *    +0.37138E+5/T**2.0 -0.66324E+7/T**3.0 +0.68494E-2*LOG(T))
     *        *0.5*(P**2.0-1.0)/10.0
      GVP(I) = GVP(I) +(0.18520E+2 -0.14375E-3*T -0.25510E+4/T
     *     +0.92763E+6/T**2.0 -0.14046E+9/T**3.0 -0.98457*LOG(T))
     *        *LOG(P/1.0)/10.0
      GO TO 2020

 6771  IF (P .GT. 100.01 .OR. P .EQ. 100.01) GO TO 6772
      VGAS(I) = (0.87400E+0 + 0.40270E-3*T +0.80337E+3/T
     *     -0.44457E+6/T**2.0 +0.74301E+8/T**3.0 -0.24792E+0*LOG(T))
      VGAS(I) = VGAS(I) +(0.38781E-2 -0.11371E-5*T -0.25486E+1/T
     *    +0.85059E+3/T**2.0 -0.10269E+6/T**3.0 -0.13657E-3*LOG(T))*P
      VGAS(I) = VGAS(I) +(0.18394E+2 +0.40758E-3*T -0.24554E+4/T
     *    +0.12987E+7/T**2.0 -0.28598E+9/T**3.0 -0.10670E+1*LOG(T))/P
      VGAS(I) = RT*VGAS(I)
      Z(I) = 1 + (-2.20960*T**0.5 + 3.35460E-8*T**3.0)/VGAS(I)
     *     + (3.4569E-5*T**2.5 + 64.9764*LOG(T))/VGAS(I)**2.0
      GVPK(I) = (0.89959E+0 + 0.40267E-3*T +0.71835E+3/T -0.36840E+6
     *     /T**2.0 +0.54379E+8/T**3.0 -0.23965E+0*LOG(T))
     *       *(10.0-1.0)/10.0
      GVPK(I) = GVPK(I) +(0.17952E-1 -0.25984E-4*T -0.73371E+2/T
     *    +0.37138E+5/T**2.0 -0.66324E+7/T**3.0 +0.68494E-2*LOG(T))
     *       *0.5*(10.0**2.0-1.0)/10.0
      GVPK(I) = GVPK(I) +(0.18520E+2 -0.14375E-3*T -0.25510E+4/T
     *     +0.92763E+6/T**2.0 -0.14046E+9/T**3.0 -0.98457*LOG(T))
     *       *LOG(10.0/1.0)/10.0
      GVP(I) = (0.87400E+0 + 0.40270E-3*T +0.80337E+3/T -0.44457E+6
     *     /T**2.0 +0.74301E+8/T**3.0 -0.24792E+0*LOG(T))
     *      *(P-10.0)/10.0
      GVP(I) = GVP(I) +(0.38781E-2 -0.11371E-5*T -0.25486E+1/T
     *     +0.85059E+3/T**2.0 -0.10269E+6/T**3.0 -0.13657E-3*LOG(T))
     *        *0.5*(P**2.0-100.0)/10.0
      GVP(I) = GVP(I) +(0.18394E+2 +0.40758E-3*T -0.24554E+4/T
     *     +0.12987E+7/T**2.0 -0.28598E+9/T**3.0 -0.10670E+1*LOG(T))
     *        *LOG(P/10.0)/10.0
      GO TO 2020

 6772  IF (P .GT. 500.00 .OR. P .EQ. 500.00) GO TO 6773
      VGAS(I) = (-0.10168E+1 + 0.61393E-4*T +0.45627E+3/T
     *     -0.15728E+6/T**2.0 +0.27222E+7/T**3.0 +0.94293E-1*LOG(T))
      VGAS(I) = VGAS(I) +(0.47802E-3 -0.38548E-6*T -0.14431E+1/T
     *     +0.78898E+3/T**2.0 -0.14526E+6/T**3.0 +0.10234E-3*LOG(T))*P
      VGAS(I) = VGAS(I) +(0.40511E+2 -0.59424E-2*T -0.35194E+5/T
     *     +0.18536E+8/T**2.0 -0.29916E+10/T**3.0 -0.72234E+0*LOG(T))/P
      VGAS(I) = RT*VGAS(I)
      Z(I) = 1 + (-2.20960*T**0.5 + 3.35460E-8*T**3.0)/VGAS(I)
     *     + (3.4569E-5*T**2.5 + 64.9764*LOG(T))/VGAS(I)**2.0
      GVPK(I) = (0.89959E+0 + 0.40267E-3*T +0.71835E+3/T -0.36840E+6
     *     /T**2.0 +0.54379E+8/T**3.0 -0.23965E+0*LOG(T))
     *       *(10.0-1.0)/10.0
      GVPK(I) = GVPK(I) +(0.17952E-1 -0.25984E-4*T -0.73371E+2/T
     *    +0.37138E+5/T**2.0 -0.66324E+7/T**3.0 +0.68494E-2*LOG(T))
     *       *0.5*(10.0**2.0-1.0)/10.0
      GVPK(I) = GVPK(I) +(0.18520E+2 -0.14375E-3*T -0.25510E+4/T
     *     +0.92763E+6/T**2.0 -0.14046E+9/T**3.0 -0.98457*LOG(T))
     *       *LOG(10.0/1.0)/10.0
      GVPK(I) =GVPK(I)+(0.87400E+0+0.40270E-3*T+0.80337E+3/T-0.44457E+6
     *     /T**2.0 +0.74301E+8/T**3.0 -0.24792E+0*LOG(T))
     *       *(100.0-10.0)/10.0
      GVPK(I) = GVPK(I) +(0.38781E-2 -0.11371E-5*T -0.25486E+1/T
     *     +0.85059E+3/T**2.0 -0.10269E+6/T**3.0 -0.13657E-3*LOG(T))
     *       *0.5*(100.0**2.0-100.0)/10.0
      GVPK(I) = GVPK(I) +(0.18394E+2 +0.40758E-3*T -0.24554E+4/T
     *     +0.12987E+7/T**2.0 -0.28598E+9/T**3.0 -0.10670E+1*LOG(T))
     *       *LOG(100.0/10.0)/10.0
      GVP(I) = (-0.10168E+1 + 0.61393E-4*T +0.45627E+3/T
     *     -0.15728E+6/T**2.0 +0.27222E+7/T**3.0 +0.94293E-1*LOG(T))
     *           *(P-100.0)/10.0
      GVP(I) = GVP(I) +(0.47802E-3 -0.38548E-6*T -0.14431E+1/T
     *     +0.78898E+3/T**2.0 -0.14526E+6/T**3.0 +0.10234E-3*LOG(T))
     *        *0.5*(P**2.0-10000.0)/10.0
      GVP(I) = GVP(I) +(0.40511E+2 -0.59424E-2*T -0.35194E+5/T
     *     +0.18536E+8/T**2.0 -0.29916E+10/T**3.0 -0.72234E+0*LOG(T))
     *        *LOG(P/100.0)/10.0
      GO TO 2020

 6773  IF (P .GT. 1000.00 .OR. P .EQ. 1000.00) GO TO 2011
      VGAS(I) = (0.10202E+1 + 0.23660E-3*T +0.95162E+3/T
     *     -0.73172E+6/T**2.0 +0.17906E+9/T**3.0 -0.24074E+0*LOG(T))
      VGAS(I) = VGAS(I) +(0.32345E-2 -0.22552E-6*T -0.21426E+1/T
     *     +0.12039E+4/T**2.0 -0.25889E+6/T**3.0 -0.26166E-3*LOG(T))*P
      VGAS(I) = VGAS(I) +(0.42568E+2 -0.19179E-2*T -0.22746E+5/T
     *     +0.47462E+6/T**2.0 +0.45740E+9/T**3.0 -0.10585E+1*LOG(T))/P
      VGAS(I) = RT*VGAS(I)
      Z(I) = 1 + (-2.20960*T**0.5 + 3.35460E-8*T**3.0)/VGAS(I)
     *     + (3.4569E-5*T**2.5 + 64.9764*LOG(T))/VGAS(I)**2.0
      GVPK(I) = (0.89959E+0 + 0.40267E-3*T +0.71835E+3/T -0.36840E+6
     *     /T**2.0 +0.54379E+8/T**3.0 -0.23965E+0*LOG(T))
     *       *(10.0-1.0)/10.0
      GVPK(I) = GVPK(I) +(0.17952E-1 -0.25984E-4*T -0.73371E+2/T
     *    +0.37138E+5/T**2.0 -0.66324E+7/T**3.0 +0.68494E-2*LOG(T))
     *       *0.5*(10.0**2.0-1.0)/10.0
      GVPK(I) = GVPK(I) +(0.18520E+2 -0.14375E-3*T -0.25510E+4/T
     *     +0.92763E+6/T**2.0 -0.14046E+9/T**3.0 -0.98457*LOG(T))
     *       *LOG(10.0/1.0)/10.0
      GVPK(I) =GVPK(I)+(0.87400E+0+0.40270E-3*T+0.80337E+3/T-0.44457E+6
     *     /T**2.0 +0.74301E+8/T**3.0 -0.24792E+0*LOG(T))
     *        *(100.0-10.0)/10.0
      GVPK(I) = GVPK(I) +(0.38781E-2 -0.11371E-5*T -0.25486E+1/T
     *     +0.85059E+3/T**2.0 -0.10269E+6/T**3.0 -0.13657E-3*LOG(T))
     *       *0.5*(100.0**2.0-100.0)/10.0
      GVPK(I) = GVPK(I) +(0.18394E+2 +0.40758E-3*T -0.24554E+4/T
     *     +0.12987E+7/T**2.0 -0.28598E+9/T**3.0 -0.10670E+1*LOG(T))
     *       *LOG(100.0/10.0)/10.0
      GVPK(I) = GVPK(I) + (-0.10168E+1 + 0.61393E-4*T +0.45627E+3/T
     *     -0.15728E+6/T**2.0 +0.27222E+7/T**3.0 +0.94293E-1*LOG(T))
     *           *(500.0-100.0)/10.0
      GVPK(I) = GVPK(I) +(0.47802E-3 -0.38548E-6*T -0.14431E+1/T
     *     +0.78898E+3/T**2.0 -0.14526E+6/T**3.0 +0.10234E-3*LOG(T))
     *        *0.5*(500.0**2.0-10000.0)/10.0
      GVPK(I) = GVPK(I) +(0.40511E+2 -0.59424E-2*T -0.35194E+5/T
     *     +0.18536E+8/T**2.0 -0.29916E+10/T**3.0 -0.72234E+0*LOG(T))
     *        *LOG(500.0/100.0)/10.0
      GVP(I) = (0.10202E+1 + 0.23660E-3*T +0.95162E+3/T
     *     -0.73172E+6/T**2.0 +0.17906E+9/T**3.0 -0.24074E+0*LOG(T))
     *            *(P-500.0)/10.0
      GVP(I) = GVP(I) +(0.32345E-2 -0.22552E-6*T -0.21426E+1/T
     *     +0.12039E+4/T**2.0 -0.25889E+6/T**3.0 -0.26166E-3*LOG(T))
     *       *0.5*(P**2.0-250000.0)/10.0
      GVP(I) = GVP(I) +(0.42568E+2 -0.19179E-2*T -0.22746E+5/T
     *     +0.47462E+6/T**2.0 +0.45740E+9/T**3.0 -0.10585E+1*LOG(T))
     *       *LOG(P/500.0)/10.0
      GO TO 2020

 2011 IF (P .GT. 5000.00 .OR. P .EQ. 5000.00) GO TO 2010
      GVPK(I) = 1000.*(AA1(I) + BB1(I)*T + CC1(I)/T + DD1(I)*T**2.0
     *    + EE1(I)/T**2.0 + FF1(I)*T**3.0 + GG1(I)/T**3.0
     *    + HH1(I)*LOG(T))/RT
      Z(I) = FHOA1 + FHOA2*T + FHOA3/T
      Z(I) = Z(I) + (FHOB1/T + FHOB2*T**3.)*P
      Z(I) = Z(I) + (FHOC1/T + FHOC2/T**3. + FHOC3*T**2.)*P**2.
      VGAS(I) = 10.*RT*Z(I)/P
      GVP(I) = (FHOA1 + FHOA2*T + FHOA3/T)*LOG(P/1000.)
      GVP(I) = GVP(I) + (FHOB1/T + FHOB2*T**3.)*(P - 1000.)
      GVP(I) = GVP(I)+(FHOC1/T+FHOC2/T**3.+FHOC3*T**2.)*(P**2.-1.D6)/2.
      GO TO 2020

 2010 GVPK(I) = 1000.*(-130.517+ 6.4967D-2*T + 19.4831*LOG(T))/RT
      Z(I) = HHOA1 + HHOA2/T**2. + HHOA3/T**3. + HHOA4*LOG(T)
      Z(I) = Z(I) + (HHOB1/T + HHOB2/T**2. + HHOB3/T**3.)*P
      Z(I) = Z(I) + (HHOC5 + HHOC1/T + HHOC2/T**2. + HHOC3/T**3.
     *+ HHOC4*LOG(T))*P**2.
      Z(I) = Z(I) + (HHOD1/T + HHOD2/T**2. + HHOD3/T**3.
     *+ HHOD4*T**3.)*P**3.
      VGAS(I) = 10.*RT*Z(I)/P
      GVP(I) = (HHOA1 + HHOA2/T**2. + HHOA3/T**3.
     *+ HHOA4*LOG(T))*LOG(P/5000.)
      GVP(I) = GVP(I) + (HHOB1/T + HHOB2/T**2.
     *+ HHOB3/T**3.)*(P - 5000.)
      GVP(I) = GVP(I) + (HHOC5 + HHOC1/T + HHOC2/T**2. + HHOC3/T**3.
     *+ HHOC4*LOG(T))*(P**2. - 5000.**2.)/2.
      GVP(I) = GVP(I) + (HHOD1/T + HHOD2/T**2. + HHOD3/T**3.
     *+ HHOD4*T**3.)*(P**3. - 5000.**3.)/3.

 2020 GVP(I) = GVP(I) + GVPK(I)
      GV(I) = G1BAR(I,T) + GVP(I)

C
C************************************************
C*       -----  CO2, CH4, CO, O2  -----         *
C************************************************
9001  CONTINUE

      DO 226 I = 2, 5

C 1.  FOR CO2
CCCCCCCCC
CC IF CHOOSING THE P(V,T) FORMULATION FROM MRK-EOS MODEL
CC          by Kerrick and Jacobs (1981)
CC

      IF (I .EQ. 2) THEN

      IF (T .GT. 1273.15) GO TO 503
      CALL CO2(T,P,V,GG)
      VGAS(I) = V
      GVP(I)  = GG/RT
      Z(I) = P*VGAS(I)/(10.0*RT)
      GV(I) = G1BAR(I,T) + GVP(I)
      GO TO 226

C 2.  FOR CH4
CCCCCCCCC
CC IF CHOOSING THE P(V,T) FORMULATION
CC        FROM Schemit-Wagner MODEL by Friend et al. (1989)
CC     or FROM MRK-EOS MODEL by Grevel (1990)
CC

      ELSE IF (I .EQ. 3) THEN

      IF (T .GT. 1273.15) GO TO 503
      CALL CH4(T,P,V,GG)
      VGAS (I) = V
      GVP  (I) = GG/RT
      Z(I) = P*VGAS(I)/(10.0*RT)
      GV(I) = G1BAR(I,T) + GVP(I)
      GO TO 226

C 3.  FOR CO AND O2
CCCCCCCCC
CC IF CHOOSING THE V(P,T) FORMULATION IN CORRESPONDING-STATE EOS
CC              of Saxena-Fei (1987, 1988)
CC
CC        For CO, O2:           P < 5 kbar;
CC        For CO2, CH4:   T > 1273.15 K,  P < 5 kbar.
CCCCC

      ELSE IF (I .EQ. 4 .OR. I .EQ. 5) THEN

 503  PR(I) = P/PCR(I)
      TR(I) = T/TCR(I)

      IF (P .GT. 1000. .OR. P .EQ. 1000.) GO TO 2031
      Z(I)= 1 + (0.09827/Tr(I) - 0.2709/Tr(I)**3.0)*Pr(I)
     * + (0.01427/Tr(I)**4.0 - 0.00103/Tr(I)**1.5)*Pr(I)*Pr(I)
      GVPK(I)=0.0
      GVP(I) = LOG(P) + (0.09827/Tr(I) - 0.2709/
     * Tr(I)**3.0)/PCR(I)*(P-1.0) + (0.01427/Tr(I)**4.0 - 0.00103
     * /Tr(I)**1.5)/PCR(I)**2.0/2.0*(P**2.0-1.0)
      VGAS(I) = 10.*RT*Z(I)/P
      GO TO 2060

 2031 IF (P .GT. 5000. .OR. P .EQ. 5000.) GO TO 2050
      GVPK(I) = 1000.*(AA1(I) + BB1(I)*T + CC1(I)/T + DD1(I)*T**2.0
     *    + EE1(I)/T**2.0 + FF1(I)*T**3.0 + GG1(I)/T**3.0
     *    + HH1(I)*LOG(T))/RT
      Z(I) = FCOA1 + FCOA2/TR(I)**2.
      Z(I) = Z(I) + (FCOB1/TR(I))*PR(I)
      Z(I) = Z(I) + (FCOC1/TR(I)**2. + FCOC2*LOG(TR(I)))*PR(I)**2.
      VGAS(I) = 10.*RT*Z(I)/P
      GVP(I) = (FCOA1 + FCOA2/TR(I)**2.)*LOG(P/1000.)
      GVP(I) = GVP(I) + (FCOB1/TR(I))*(PR(I) - 1000./PCR(I))
      GVP(I) = GVP(I) + (FCOC1/TR(I)**2. + FCOC2*LOG(TR(I)))
     **(PR(I)**2 - (1000./PCR(I))**2.)/2.
      GO TO 2060

 2050 GVPK(I) = 1000.*(AA1(I) + BB1(I)*T + CC1(I)/T + DD1(I)*T**2.0
     *    + EE1(I)/T**2.0 + FF1(I)*T**3.0 + GG1(I)/T**3.0
     *    + HH1(I)*LOG(T))/RT
      GVPK(I) = GVPK(I) + (FCOA1 + FCOA2/TR(I)**2.)*LOG(5000./1000.)
      GVPK(I) = GVPK(I) + (FCOB1/TR(I))*(5000./PCR(I) - 1000./PCR(I))
      GVPK(I) = GVPK(I) + (FCOC1/TR(I)**2. + FCOC2*LOG(TR(I)))
     **((5000./PCR(I))**2. - (1000./PCR(I))**2.)/2.
      Z(I) = HCOA1 + HCOA2/TR(I)**2. + HCOA3*LOG(TR(I))
      Z(I) = Z(I) + (HCOB1/TR(I) + HCOB2/TR(I)**2.)*PR(I)
      Z(I) = Z(I) + (HCOC1/TR(I) + HCOC2/TR(I)**2. + HCOC3/TR(I)**3.)
     **PR(I)**2.
      Z(I) = Z(I) + (HCOD1/TR(I) + HCOD2*TR(I)**3.)*PR(I)**3.
      VGAS(I) = 10.*RT*Z(I)/P
      GVP(I) = (HCOA1 + HCOA2/TR(I)**2. + HCOA3*LOG(TR(I)))*LOG(P/5000.)
      GVP(I) = GVP(I) + (HCOB1/TR(I) + HCOB2/TR(I)**2.)
     **(PR(I) - 5000./PCR(I))
      GVP(I) = GVP(I) + (HCOC1/TR(I) + HCOC2/TR(I)**2. + HCOC3
     */TR(I)**3.)*(PR(I)**2. - (5000./PCR(I))**2.)/2.
      GVP(I) = GVP(I) + (HCOD1/TR(I) + HCOD2*TR(I)**3.)
     **(PR(I)**3. - (5000./PCR(I))**3.)/3.

 2060 GVP(I) = GVP(I) + GVPK(I)
      GV(I) = G1BAR(I,T) + GVP(I)

      END IF

226   CONTINUE

C
CC    *****  H2  *****
C
CCCCCCCCC
CC  CHOOSING THE V(P,T) FORMULATION IN CORRESPONDING-STATE EOS
CC              of Saxena-Fei (1987, 1988)
CC
      I = 6

      PR(I) = P/PCR(I)
      TR(I) = T/TCR(I)

      IF (P .GT. 1000. .OR. P .EQ. 1000.) GO TO 2041
      Z(I)= 1 + (0.09827/Tr(I) - 0.2709/Tr(I)**3.0)*Pr(I)
     * + (0.01427/Tr(I)**4.0 - 0.00103/Tr(I)**1.5)*Pr(I)*Pr(I)
      GVPK(I)=0.0
      GVP(I) = LOG(P) + (0.09827/Tr(I) - 0.2709/
     * Tr(I)**3.0)/PCR(I)*(P-1.0) + (0.01427/Tr(I)**4.0 - 0.00103
     * /Tr(I)**1.5)/PCR(I)**2.0/2.0*(P**2.0-1.0)
      VGAS(I) = 10.*RT*Z(I)/P
      GO TO 2070

 2041 HA(I)=HA1+HA2/T+HA3/(T*T)+LOG(T)*HA4
      HB(I)=HB1+HB2/T+HB3/(T*T)+LOG(T)*HB4
      HC(I)=HC1+HC2/T+HC3/(T*T)+LOG(T)*HC4
      HD(I)=HD1+HD2/T+HD3/(T*T)
      Z(I)=HA(I)+HB(I)*P+HC(I)*P*P+HD(I)*P**3
      VGAS(I) = 10.*RT*Z(I)/P
      GVPK(I) = 1000.*(AA1(I) + BB1(I)*T + CC1(I)/T + DD1(I)*T**2.0
     *    + EE1(I)/T**2.0 + FF1(I)*T**3.0 + GG1(I)/T**3.0
     *    + HH1(I)*LOG(T))/RT
      GVP(I) = HA(I)*LOG(P/1000.) + HB(I)*(P-1000.)
      GVP(I) = GVP(I) + HC(I)*(P**2-1.D6)/2.
      GVP(I) = GVP(I) + HD(I)*(P**3-1.D9)/3.

 2070 GVP(I) = GVP(I) + GVPK(I)
      GV(I) = G1BAR(I,T) + GVP(I)

C
CC    *****  S2  *****
C
CCCCCCCCC
CC  CHOOSING THE V(P,T) FORMULATION IN CORRESPONDING-STATE EOS
CC       of Saxena & Fei (1987, 1988), Shi & Saxena (1992)
CC
      I = 7

      PR(I) = P/PCR(I)
      TR(I) = T/TCR(I)

      IF (P .GT. 1000. .OR. P .EQ. 1000.) GO TO 7331
      Z(I)= 1 + (0.09827/Tr(I) - 0.2709/Tr(I)**3.0)*Pr(I)
     * + (0.01427/Tr(I)**4.0 - 0.00103/Tr(I)**1.5)*Pr(I)*Pr(I)
      GVPK(I)=0.0
      GVP(I) = LOG(P) + (0.09827/Tr(I) - 0.2709/
     * Tr(I)**3.0)/PCR(I)*(P-1.0) + (0.01427/Tr(I)**4.0 - 0.00103
     * /Tr(I)**1.5)/PCR(I)**2.0/2.0*(P**2.0-1.0)
      VGAS(I) = 10.*RT*Z(I)/P
      GO TO 7361

 7331 IF (P .GT. 5000. .OR. P .EQ. 5000.) GO TO 7351
      GVPK(I) = 1000.*(AA1(I) + BB1(I)*T + CC1(I)/T + DD1(I)*T**2.0
     *    + EE1(I)/T**2.0 + FF1(I)*T**3.0 + GG1(I)/T**3.0
     *    + HH1(I)*LOG(T))/RT
      Z(I) = FCOA1 + FCOA2/TR(I)**2.
      Z(I) = Z(I) + (FCOB1/TR(I))*PR(I)
      Z(I) = Z(I) + (FCOC1/TR(I)**2. + FCOC2*LOG(TR(I)))*PR(I)**2.
      VGAS(I) = 10.*RT*Z(I)/P
      GVP(I) = (FCOA1 + FCOA2/TR(I)**2.)*LOG(P/1000.)
      GVP(I) = GVP(I) + (FCOB1/TR(I))*(PR(I) - 1000./PCR(I))
      GVP(I) = GVP(I) + (FCOC1/TR(I)**2. + FCOC2*LOG(TR(I)))
     **(PR(I)**2 - (1000./PCR(I))**2.)/2.
      GO TO 7361

 7351 GVPK(I) = 1000.*(AA1(I) + BB1(I)*T + CC1(I)/T + DD1(I)*T**2.0
     *    + EE1(I)/T**2.0 + FF1(I)*T**3.0 + GG1(I)/T**3.0
     *    + HH1(I)*LOG(T))/RT
      GVPK(I) = GVPK(I) + (FCOA1 + FCOA2/TR(I)**2.)*LOG(5000./1000.)
      GVPK(I) = GVPK(I) + (FCOB1/TR(I))*(5000./PCR(I) - 1000./PCR(I))
      GVPK(I) = GVPK(I) + (FCOC1/TR(I)**2. + FCOC2*LOG(TR(I)))
     **((5000./PCR(I))**2. - (1000./PCR(I))**2.)/2.
      Z(I) = HCOA1 + HCOA2/TR(I)**2. + HCOA3*LOG(TR(I))
      Z(I) = Z(I) + (HCOB1/TR(I) + HCOB2/TR(I)**2.)*PR(I)
      Z(I) = Z(I) + (HCOC1/TR(I) + HCOC2/TR(I)**2. + HCOC3/TR(I)**3.)
     **PR(I)**2.
      Z(I) = Z(I) + (HCOD1/TR(I) + HCOD2*TR(I)**3.)*PR(I)**3.
      VGAS(I) = 10.*RT*Z(I)/P
      GVP(I) = (HCOA1 + HCOA2/TR(I)**2. + HCOA3*LOG(TR(I)))*LOG(P/5000.)
      GVP(I) = GVP(I) + (HCOB1/TR(I) + HCOB2/TR(I)**2.)
     **(PR(I) - 5000./PCR(I))
      GVP(I) = GVP(I) + (HCOC1/TR(I) + HCOC2/TR(I)**2. + HCOC3
     */TR(I)**3.)*(PR(I)**2. - (5000./PCR(I))**2.)/2.
      GVP(I) = GVP(I) + (HCOD1/TR(I) + HCOD2*TR(I)**3.)
     **(PR(I)**3. - (5000./PCR(I))**3.)/3.

 7361 GVP(I) = GVP(I) + GVPK(I)
      GV(I) = G1BAR(I,T) + GVP(I)

C
CC    *****  SO2  ******
C
CCCCCCCCC
CC  CHOOSING THE V(P,T) FORMULATION IN CORRESPONDING-STATE EOS
CC               of Shi & Saxena (1992)
CC
      I = 8

      PR(I) = P/PCR(I)
      TR(I) = T/TCR(I)

      IF (T .LE. 300.0 .AND. P .LE. 100.0) THEN
         VGAS(I) = 10.0*RT/P  
         GVP(I) = RT*LOG(P) 
         GVP(I) = GVP(I)/RT 
         GV(I) = G1BAR(I,T) + GVP(I) 
      ELSE

      GVPK(I) = 0.00
      Z(I) = 0.93000E+0 + 0.45410E-1*TR(I) -0.24482E+0/TR(I)
     *  +0.24222E+0/TR(I)**2.0 -0.53701E+0/TR(I)**3.0
     *  -0.21583E-1*LOG(TR(I))
      Z(I) = Z(I) + (0.67077E-3 -0.18400E-2*TR(I) +0.67399E-1/TR(I)
     *  -0.29688E-1/TR(I)**2.0 +0.29577E-1/TR(I)**3.0
     *  +0.52307E-2*LOG(TR(I)))*PR(I)
      Z(I) = Z(I) + (-0.36646E-3 +0.20067E-4*TR(I) +0.95671E-3/TR(I)
     *  -0.80239E-3/TR(I)**2.0 +0.20236E-3/TR(I)**3.0
     *  +0.72484E-4*LOG(TR(I)))*PR(I)**2.0
      VGAS(I) = 10.*RT*Z(I)/P
      GVP(I) = (0.93000E+0 + 0.45410E-1*TR(I) -0.24482E+0/TR(I)
     *  +0.24222E+0/TR(I)**2.0 -0.53701E+0/TR(I)**3.0
     *  -0.21583E-1*LOG(TR(I)))*LOG(P)
      GVP(I) = GVP(I) + (0.67077E-3 -0.18400E-2*TR(I) +0.67399E-1/TR(I)
     *  -0.29688E-1/TR(I)**2.0 +0.29577E-1/TR(I)**3.0
     *  +0.52307E-2*LOG(TR(I)))*(PR(I) - 1.0/PCR(I))
      GVP(I) = GVP(I) +(-0.36646E-3 +0.20067E-4*TR(I) +0.95671E-3/TR(I)
     *  -0.80239E-3/TR(I)**2.0 +0.20236E-3/TR(I)**3.0
     *  +0.72484E-4*LOG(TR(I)))*(PR(I)**2 - (1.00/PCR(I))**2.)/2.
      GVP(I) = GVP(I) + GVPK(I)
      GV(I) = G1BAR(I,T) + GVP(I)

      END IF

C
CC    *****  COS  *****
C
CCCCCCCCC
CC  CHOOSING THE V(P,T) FORMULATION IN CORRESPONDING-STATE EOS
CC       of Saxena & Fei (1987, 1988), Shi & Saxena (1992)
CC
      I = 9

      PR(I) = P/PCR(I)
      TR(I) = T/TCR(I)

      IF (P .GT. 1000. .OR. P .EQ. 1000.) GO TO 7471
      Z(I)= 1 + (0.09827/Tr(I) - 0.2709/Tr(I)**3.0)*Pr(I)
     * + (0.01427/Tr(I)**4.0 - 0.00103/Tr(I)**1.5)*Pr(I)*Pr(I)
      GVPK(I)=0.0
      GVP(I) = LOG(P) + (0.09827/Tr(I) - 0.2709/
     * Tr(I)**3.0)/PCR(I)*(P-1.0) + (0.01427/Tr(I)**4.0 - 0.00103
     * /Tr(I)**1.5)/PCR(I)**2.0/2.0*(P**2.0-1.0)
      VGAS(I) = 10.*RT*Z(I)/P
      GO TO 7421

 7471 IF (P .GT. 5000. .OR. P .EQ. 5000.) GO TO 7472
      GVPK(I) = 1000.*(AA1(I) + BB1(I)*T + CC1(I)/T + DD1(I)*T**2.0
     *    + EE1(I)/T**2.0 + FF1(I)*T**3.0 + GG1(I)/T**3.0
     *    + HH1(I)*LOG(T))/RT
      Z(I) = FCOA1 + FCOA2/TR(I)**2.
      Z(I) = Z(I) + (FCOB1/TR(I))*PR(I)
      Z(I) = Z(I) + (FCOC1/TR(I)**2. + FCOC2*LOG(TR(I)))*PR(I)**2.
      VGAS(I) = 10.*RT*Z(I)/P
      GVP(I) = (FCOA1 + FCOA2/TR(I)**2.)*LOG(P/1000.)
      GVP(I) = GVP(I) + (FCOB1/TR(I))*(PR(I) - 1000./PCR(I))
      GVP(I) = GVP(I) + (FCOC1/TR(I)**2. + FCOC2*LOG(TR(I)))
     **(PR(I)**2 - (1000./PCR(I))**2.)/2.
      GO TO 7421

 7472 GVPK(I) = 1000.*(AA1(I) + BB1(I)*T + CC1(I)/T + DD1(I)*T**2.0
     *    + EE1(I)/T**2.0 + FF1(I)*T**3.0 + GG1(I)/T**3.0
     *    + HH1(I)*LOG(T))/RT
      GVPK(I) = GVPK(I) + (FCOA1 + FCOA2/TR(I)**2.)*LOG(5000./1000.)
      GVPK(I) = GVPK(I) + (FCOB1/TR(I))*(5000./PCR(I) - 1000./PCR(I))
      GVPK(I) = GVPK(I) + (FCOC1/TR(I)**2. + FCOC2*LOG(TR(I)))
     **((5000./PCR(I))**2. - (1000./PCR(I))**2.)/2.
      Z(I) = HCOA1 + HCOA2/TR(I)**2. + HCOA3*LOG(TR(I))
      Z(I) = Z(I) + (HCOB1/TR(I) + HCOB2/TR(I)**2.)*PR(I)
      Z(I) = Z(I) + (HCOC1/TR(I) + HCOC2/TR(I)**2. + HCOC3/TR(I)**3.)
     **PR(I)**2.
      Z(I) = Z(I) + (HCOD1/TR(I) + HCOD2*TR(I)**3.)*PR(I)**3.
      VGAS(I) = 10.*RT*Z(I)/P
      GVP(I) = (HCOA1 + HCOA2/TR(I)**2. + HCOA3*LOG(TR(I)))*LOG(P/5000.)
      GVP(I) = GVP(I) + (HCOB1/TR(I) + HCOB2/TR(I)**2.)
     **(PR(I) - 5000./PCR(I))
      GVP(I) = GVP(I) + (HCOC1/TR(I) + HCOC2/TR(I)**2. + HCOC3
     */TR(I)**3.)*(PR(I)**2. - (5000./PCR(I))**2.)/2.
      GVP(I) = GVP(I) + (HCOD1/TR(I) + HCOD2*TR(I)**3.)
     **(PR(I)**3. - (5000./PCR(I))**3.)/3.

 7421 GVP(I) = GVP(I) + GVPK(I)
      GV(I) = G1BAR(I,T) + GVP(I)

C
CC    *****  H2S  *****
C
CCCCCCCCC
CC  CHOOSING THE V(P,T) FORMULATION IN CORRESPONDING-STATE EOS
CC               of Shi & Saxena (1992)
CC
      I = 10

      PR(I) = P/PCR(I)
      TR(I) = T/TCR(I)

      IF (T .LE. 300.0 .AND. P .LE. 50.0) THEN
         VGAS(I) = 10.0*RT/P  
         GVP(I) = RT*LOG(P) 
         GVP(I) = GVP(I)/RT 
         GV(I) = G1BAR(I,T) + GVP(I) 
      ELSE

      IF (P .GT. 500.01 .OR. P .EQ. 500.01) GO TO 1171
      GVPK(I) = 0.00
      Z(I) = 0.14721E+1 + 0.11177E+1*TR(I) +0.39657E+1/TR(I)
     *  -0.10028E+2/TR(I)**2.0 +0.45484E+1/TR(I)**3.0
     *  -0.38200E+1*LOG(TR(I))
      Z(I) = Z(I) + (0.16066E+0 +0.10887E+0*TR(I) +0.29014E+0/TR(I)
     *  -0.99593E+0/TR(I)**2.0 -0.18627E+0/TR(I)**3.0
     *  -0.45515E+0*LOG(TR(I)))*PR(I)
      Z(I) = Z(I) + (-0.28933E+0 -0.70522E-1*TR(I) +0.39828E+0/TR(I)
     *  -0.50533E-1/TR(I)**2.0 +0.11760E+0/TR(I)**3.0
     *  +0.33972E+0*LOG(TR(I)))*PR(I)**2.0
      VGAS(I) = 10.*RT*Z(I)/P
      GVP(I) = (0.14721E+1 + 0.11177E+1*TR(I) +0.39657E+1/TR(I)
     *  -0.10028E+2/TR(I)**2.0 +0.45484E+1/TR(I)**3.0
     *  -0.38200E+1*LOG(TR(I)))*LOG(P)
      GVP(I) = GVP(I) + (0.16066E+0 +0.10887E+0*TR(I) +0.29014E+0/TR(I)
     *  -0.99593E+0/TR(I)**2.0 -0.18627E+0/TR(I)**3.0
     *  -0.45515E+0*LOG(TR(I)))*(PR(I) - 1.0/PCR(I))
      GVP(I) = GVP(I) + (-0.28933E+0 -0.70522E-1*TR(I) +0.39828E+0/TR(I)
     *  -0.50533E-1/TR(I)**2.0 +0.11760E+0/TR(I)**3.0
     *  +0.33972E+0*LOG(TR(I)))*(PR(I)**2.0 - (1.00/PCR(I))**2.)/2.
      GO TO 1172

 1171 GVPK(I) = (0.14721E+1 + 0.11177E+1*TR(I) +0.39657E+1/TR(I)
     *  -0.10028E+2/TR(I)**2.0 +0.45484E+1/TR(I)**3.0
     *  -0.38200E+1*LOG(TR(I)))*LOG(500.0)
      GVPK(I)=GVPK(I) + (0.16066E+0 +0.10887E+0*TR(I) +0.29014E+0/TR(I)
     *  -0.99593E+0/TR(I)**2.0 -0.18627E+0/TR(I)**3.0
     *  -0.45515E+0*LOG(TR(I)))*(500./PCR(I) - 1.0/PCR(I))
      GVPK(I)=GVPK(I) + (-0.28933E+0 -0.70522E-1*TR(I) +0.39828E+0/TR(I)
     *  -0.50533E-1/TR(I)**2.0 +0.11760E+0/TR(I)**3.0
     *  +0.33972E+0*LOG(TR(I)))*((500./PCR(I))**2.0-(1.0/PCR(I))**2.)/2.
      Z(I) = 0.60031E+0 + 0.18359E-3*TR(I) +0.46502E-1/TR(I)
     *  +0.36113E+0/TR(I)**2.0 -0.79708E+0/TR(I)**3.0
     *  +0.25548E+0*LOG(TR(I))
      Z(I) = Z(I) + (0.22329E-1 +0.17675E-2*TR(I) +0.48904E-1/TR(I)
     *  -0.20378E-1/TR(I)**2.0 +0.33047E-1/TR(I)**3.0
     *  -0.11308E-1*LOG(TR(I)))*PR(I)
      Z(I) = Z(I) + (0.56686E-3 -0.42218E-5*TR(I) -0.11837E-2/TR(I)
     *  +0.14942E-2/TR(I)**2.0 -0.79541E-3/TR(I)**3.0
     *  -0.26759E-3*LOG(TR(I)))*PR(I)**2.0
      VGAS(I) = 10.*RT*Z(I)/P
      GVP(I) = (0.60031E+0 + 0.18359E-3*TR(I) +0.46502E-1/TR(I)
     *  +0.36113E+0/TR(I)**2.0 -0.79708E+0/TR(I)**3.0
     *  +0.25548E+0*LOG(TR(I)))*LOG(P/500.)
      GVP(I) = GVP(I) + (0.22329E-1 +0.17675E-2*TR(I) +0.48904E-1/TR(I)
     *  -0.20378E-1/TR(I)**2.0 +0.33047E-1/TR(I)**3.0
     *  -0.11308E-1*LOG(TR(I)))*(PR(I) - 500.0/PCR(I))
      GVP(I) = GVP(I) + (0.56686E-3 -0.42218E-5*TR(I) -0.11837E-2/TR(I)
     *  +0.14942E-2/TR(I)**2.0 -0.79541E-3/TR(I)**3.0
     *  -0.26759E-3*LOG(TR(I)))*(PR(I)**2 - (500.00/PCR(I))**2.)/2.

1172  GVP(I) = GVP(I) + GVPK(I)
      GV(I) = G1BAR(I,T) + GVP(I)

      END IF

C
CC    *****  N2, NH3, Ar  *****
C
CCCCCCCCC
CC  CHOOSING THE V(P,T) FORMULATION OF Molecular Dynamics EOS
CC               of Belonoshko and Saxena (1992)
CC
C
      I = 11

      IF (P .LT. 5000.00) THEN
         VGAS(I) = 10.0*RT/P  
         GVP(I) = RT*LOG(P) 
         GVP(I) = GVP(I)/RT 
         GV(I) = G1BAR(I,T) + GVP(I) 
      ELSE
         GVP(I) = 1000.0*(-80.094 + 63.916*T/1000.0 + 13.616*LOG(T))
         GVP(I) = GVP(I)/RT
         GV(I) = G1BAR(I,T) + GVP(I)
      END IF

C
      I = 12

      IF (P .LT. 5000.00) THEN
         VGAS(I) = 10.0*RT/P  
         GVP(I) = RT*LOG(P) 
         GVP(I) = GVP(I)/RT 
         GV(I) = G1BAR(I,T) + GVP(I) 
      ELSE
         GVP(I) = 1000.0*(-3.873 + 70.171*T/1000.0 + 2.302*LOG(T))
         GVP(I) = GVP(I)/RT
         GV(I) = G1BAR(I,T) + GVP(I)
      END IF

C
      I = 13

      IF (P .LT. 5000.00) THEN
         VGAS(I) = 10.0*RT/P  
         GVP(I) = RT*LOG(P) 
         GVP(I) = GVP(I)/RT 
         GV(I) = G1BAR(I,T) + GVP(I) 
      ELSE
         GVP(I) = 1000.0*(-5.238 + 69.179*T/1000.0 + 3.102*LOG(T))
         GVP(I) = GVP(I)/RT
         GV(I) = G1BAR(I,T) + GVP(I)
      END IF
C
      RETURN
      END

CCC
      FUNCTION G1BAR(I,T)
CC
C ***********************************************************************
C *                                                                     *
C *  FUNCTION G1BAR(I,T) -----                                          *
C *                                                                     *
C *      CALCULATION OF THE FREE ENERGY AT 1 bar AND T FOR PHASE I      *
C *                                                                     *
C *     G1BAR(I,T) = G(1, T)                                            *
C *          = Hf(1, 298) - T*S(1, 298)                                 *
C *                                                                     *
C *                   .T                 .T                             *
C *               +  .   Cp(T) dT  - T* .  [Cp(T)/T] dT                 *
C *                 . 298              .298                             *
C *                                                                     *
C *  where  Cp(T) = a + bT + cT^-2 + dT^2 + eT^-3 + fT^-0.5 + g/T       *
C *                                                                     *
C ***********************************************************************
CC
C     IMPLICIT DOUBLE PRECISION(A-H,O-Z)
      PARAMETER(LA=15,LF=7)
      COMMON /SHECP/ C(LA,LF,8), HF(LA), S(LA)
      COMMON /SHEOM/ HOM(LA,LF-1), TOM(LA,LF-1), NOM(LA)
      DIMENSION HFSS(13), SSS(13)
      DIMENSION C1(7), C2(7), C3(7), C4(7), C5(7), C6(7), C7(7)
      DIMENSION C8(7), C9(7), C10(7), C11(7), C12(7), C13(7)
      PARAMETER(RN0=0.D0,RNA=298.15D0)
C
      DATA HFSS/-241818.46, -393509.38, -74809.92, -110524.54, 0.00,
     * 0.00, 128365.12, -296829.70, -142088.64, -20627.12,
     * 0.00, -45720.00, 0.00/
      DATA SSS/188.715, 213.635, 186.155, 197.564, 205.029,
     * 130.574, 228.070, 248.111, 231.459, 205.685,
     * 191.61, 192.78, 154.84/
CC
      DATA C1/4.6461000E+01, 5.966000E-03, 6.320000E+06, 0.000000E+00,
     * -7.957000E+08,  0.000000E+00, -1.663000E+04/
      DATA C2/7.0728000E+01,-8.822000E-04, 3.464000E+06, 0.000000E+00,
     * -2.492000E+08,  0.000000E+00, -1.876000E+04/
      DATA C3/1.2901000E+02,-4.849000E-04, 2.221000E+07, 0.000000E+00,
     * -2.291000E+09,  0.000000E+00, -7.656000E+04/
      DATA C4/3.8578000E+01, 6.513000E-04, 1.781000E+06, 0.000000E+00,
     * -9.971000E+07,  0.000000E+00, -7.725000E+03/
      DATA C5/3.9450000E+01, 5.609000E-04, 9.067000E+05, 0.000000E+00,
     *  6.039000E+05,  0.000000E+00, -6.101000E+03/
      DATA C6/2.3948000E+01, 4.962000E-03, 5.279000E+05, 0.000000E+00,
     * -1.525000E+08,  0.000000E+00,  9.536000E+02/
      DATA C7/0.3840800E+02,-0.463000E-04,-0.463500E+06, 0.000000E+00,
     *  0.693000E+08,  0.000000E+00, -0.993600E+03/
      DATA C8/0.7182800E+02,-0.267200E-02, 0.235400E+07, 0.000000E+00,
     * -0.208300E+09,  0.000000E+00, -0.164200E+05/
      DATA C9/0.4244100E+02,-0.275730E-01, 0.707320E+06, 0.460640E-05,
     * -0.521660E+10,  0.407210E+00, -0.174320E+05/
      DATA C10/0.6545900E+02, 0.916800E-03, 0.932600E+07, 0.000000E+00,
     *  0.105400E+10,  0.000000E+00, -0.288400E+05/
      DATA C11/2.3941E+01, 1.10680E-02, 1.9064E+05, -2.5518E-06,
     * 0.0000E+00, 0.0000E+00, 0.0000E+00/
      DATA C12/2.9735E+01,  3.9119E-02, 2.9243E+05, -8.2274E-06,
     * 0.0000E+00, -1.4378E+02, 0.0000E+00/
      DATA C13/2.080E+01, 0.0000E+00, 0.0000E+00, 0.0000E+00,
     *  0.0000E+00, 0.0000E+00, 0.0000E+00/

C
      DO 30 K = 1, 13
           HF(K) = HFSS(K)
           S(K) = SSS(K)
           HOM(K,1) = 0.000
           TOM(K,1) = 6000.00
           NOM(K) = 1
30    CONTINUE

C
      DO 20 J = 1, 7
           C(1,1,J) = C1(J)
           C(2,1,J) = C2(J)
           C(3,1,J) = C3(J)
           C(4,1,J) = C4(J)
           C(5,1,J) = C5(J)
           C(6,1,J) = C6(J)
           C(7,1,J) = C7(J)
           C(8,1,J) = C8(J)
           C(9,1,J) = C9(J)
           C(10,1,J) = C10(J)
           C(11,1,J) = C11(J)
           C(12,1,J) = C12(J)
           C(13,1,J) = C13(J)
 20   CONTINUE

C
CC     ********  G(1,T) FOR GASE SPECIES I
C
      G1BAR = (H0(I,T) - T*S0(I,T))/8.31451/T
C
      RETURN
      END


      FUNCTION H0(I,T)
CC
C *********************************************************************
C *                                                                   *
C *      CALCULATION OF THE ENTHALPY AT T K FOR SPECIES I             *
C *                                                                   *
C *********************************************************************
CC
C     IMPLICIT DOUBLE PRECISION(A-H,O-Z)
      PARAMETER(LA=15,LF=7)
      COMMON /SHECP/ C(LA,LF,8), HF(LA), S(LA)
      COMMON /SHEOM/ HOM(LA,LF-1), TOM(LA,LF-1), NOM(LA)
C
      PARAMETER(RN0=0.0,RNA=298.150)

      IF (NOM(I) .EQ. 1) THEN
      ELSE IF (TOM(I,1) .LE. T) THEN
      H0 = HF(I) + CPINT(RNA,TOM(I,1),C(I,1,1),C(I,1,2),C(I,1,3),C(I,1,4
     *),C(I,1,5),C(I,1,6),C(I,1,7),RN0,RN0,RN0,RN0) + HOM(I,1)
      J = 2
   96 IF (J .LT. NOM(I)) THEN
      IF (TOM(I,J) .LE. T) GO TO 21
      END IF
      H0 = H0 + CPINT(TOM(I,J-1),T,C(I,J,1),C(I,J,2),C(I,J,3),C(I,J,4),C
     *(I,J,5),C(I,J,6),C(I,J,7),RN0,RN0,RN0,RN0)
C
      RETURN
C
   21 H0 = H0 + CPINT(TOM(I,J-1),TOM(I,J),C(I,J,1),C(I,J,2),C(I,J,3),C(I
     *,J,4),C(I,J,5),C(I,J,6),C(I,J,7),RN0,RN0,RN0,RN0) + HOM(I,J)
      J = J + 1
      GO TO 96
      END IF
      H0 = HF(I) + CPINT(RNA,T,C(I,1,1),C(I,1,2),C(I,1,3),C(I,1,4),C(I,1
     *,5),C(I,1,6),C(I,1,7),RN0,RN0,RN0,RN0)
C
      RETURN
      END

CC
      FUNCTION S0(I,T)
CC
C **********************************************************************
C *                                                                    *
C *      CALCULATION OF THE ENTROPY AT T K FOR SPECIES I               *
C *                                                                    *
C **********************************************************************
CC
C      IMPLICIT DOUBLE PRECISION(A-H,O-Z)
      PARAMETER(LA=15,LF=7)
      COMMON /SHECP/ C(LA,LF,8), HF(LA), S(LA)
      COMMON /SHEOM/ HOM(LA,LF-1), TOM(LA,LF-1), NOM(LA)
C
      PARAMETER(RN0=0.D0,RNA=298.15D0)

      IF (NOM(I) .EQ. 1) THEN
      ELSE IF (TOM(I,1) .LE. T) THEN
      S0 = S(I) + CPINT(RNA,TOM(I,1),C(I,1,2),C(I,1,4),C(I,1,7),RN0,C(I,
     *1,3),RN0,C(I,1,1),C(I,1,5),C(I,1,6),RN0,RN0) + HOM(I,1)/TOM(I,1)
      J = 2
  180 IF (J .LT. NOM(I)) THEN
      IF (TOM(I,J) .LE. T) GO TO 177
      END IF
      S0 = S0 + CPINT(TOM(I,J-1),T,C(I,J,2),C(I,J,4),C(I,J,7),RN0,C(I,J,
     *3),RN0,C(I,J,1),C(I,J,5),C(I,J,6),RN0,RN0)
C
      RETURN
C
  177 S0=S0+CPINT(TOM(I,J-1),TOM(I,J),C(I,J,2),C(I,J,4),C(I,J,7),RN0,C(I
     *,J,3),RN0,C(I,J,1),C(I,J,5),C(I,J,6),RN0,RN0)+HOM(I,J)/TOM(I,J)
      J = J + 1
      GO TO 180
      END IF
      S0 = S(I) + CPINT(RNA,T,C(I,1,2),C(I,1,4),C(I,1,7),RN0,C(I,1,3),RN
     *0,C(I,1,1),C(I,1,5),C(I,1,6),RN0,RN0)
C
      RETURN
      END

CC
      FUNCTION CPINT(T0,T1,CA,CB,CC,CD,CE,CF,CG,CH,CI,CJ,CK)
CC
C ********************************************************************
C *                                                                  *
C *        CALCULATION OF THE CP AND CP/T INTERGRAL                  *
C *                                                                  *
C ********************************************************************
CC
C      IMPLICIT DOUBLE PRECISION(A-H,O-Z)
      PARAMETER(RN0=0.0,RN2=2.0,RN3=3.0,RN5=5.0)

      Ot0 = 0.0
      OT1 = 0.0

      IF (T0 .NE. OT0 .OR. T1 .NE. OT1) THEN
      OT0 = T0
      OT1 = T1
      T2 = T0 + T1
      T3 = T0*T1
      T4 = T3*T3
      T5 = T0*T0
      T6 = T5 + T1*T1
      TA = T1 - T0
      TB = TA*T2/RN2
      TC = TA/T3
      TD = TA*(T2*T2 - T3)/RN3
      TE = TB/T4
      TF = RN2*(SQRT(T1) - SQRT(T0))
      TG = LOG(T1/T0)
      TH = TD/(T3*T4)
      TI = TF/SQRT(T3)
      TJ = TB*T6/RN2
      TK = TA*(T1*T2*T6 + T5*T5)/RN5
      END IF
      CPINT = CA*TA + CB*TB + CC*TC + CD*TD + CE*TE + CF*TF +
     *CG*TG + CH*TH + CI*TI + CJ*TJ + CK*TK
C
      RETURN
      END

CC
      SUBROUTINE FACTOR(M, XN, T, P, V)
CC
CC**************************************************************************
C        FACTOR IS A SUBROUTINE FOR THE CALCULATION OF FLUID MIXTURES      *
C              Giving Logarithmized ACTIVITY COEFFICIENTS    (AKTFLN)      *
C                                   EXCESS VOLUME            (EXVMIX)      *
C                                   EXCESS EHTHALPY          (EXHMIX)      *
C                                   EXCESS ENTROPY           (EXSMIX)      *
C                                   EXCESS Gibbs FREE ENERGY (EXGMIX)      *
C                  as functions of TEMPERATURE    (T, K)                   *
C                                  PRESSURE       (P, bar)                 *
C                             and  MOLE FRACTION  (X).                     *
C                                                                          *
C                                                                          *
C   NOTE: THIS PART IS REWRITTEN BASED ON 'SFAC.FOR', IN ORDER TO          *
C           CONSIDER FLUID MIXTURES IN THE SYSTEM C-H-O-S-N-Ar             *
C                              .1991.                                      *
C                                                                          *
C     **  THE ORDER OF  13  FLUID SPECIES IS:                              *
C           H2O, CO2, CH4, CO, O2, H2, S2, SO2, COS, H2S, N2, NH3 AND Ar   *
C                                                                          *
CC**************************************************************************
CC
C      IMPLICIT DOUBLE PRECISION(A-H,O-Z)
      PARAMETER(LA=15,LB=20,LC=20)
      COMMON /SALLA/ A(LA,LB), B0(LB), GV(LA), PI(2*LB), VGAS(LA), L
      COMMON /SALLI/ Y(LA), MF(LC+1), ML(LC+1), MP, MV
      COMMON /SALLR/ AKTFLN(LA), PX, RT, VX, X(LA), YTOT(LC)
      COMMON /SSGFC/ XSCAN, YF(LA), YFTOT(LC)
      COMMON /SWIJ/ W(15,15,LC), WM(15,15), ICH, JCH, MCH

C-------------------------------------------------------------------------*
C        AKTFLN(I) = LOGARITHMIZED ACTIVITY COEFFICIENT FOR SPECIES I
C        B0(J) = TOTAL AMOUNT OR LN OF THE EQUIL ACTIVITY OF COMPONENT J
C        GV(I) = (MU0/RT) FOR SPECIES I WITH VOLUME TERM INCLUDED
C        MF(M) = LOWEST SPECIES NUMBER IN MIXTURE M
C        ML(M) = HIGHEST SPECIES NUMBER IN MIXTURE M
C        MV = TOTAL NUMBER OF MIXTURES (INVARIANTS = MIXTURE (MP+1))
C        PI(J) = LAGRANGIAN MULTIPLIER FOR COMPONENT J
C        PX = CALCULATED TOTAL PRESSURE/BAR
C        RT = R*T (R = GAS CONSTANT/J.K-1MOL-1)
C        VX = CALCULATED TOTAL VOLUME/DM3
C        X(I) = MOLE FRACTION FOR SPECIES I
C        Y(I) = AMOUNT OF SUBSTANCE FOR SPECIES I
C        YTOT(M) = TOTAL AMOUNT OF MIXTURE M
C  CONSULT THE INPUT GUIDE FOR AN EXPLANATION OF THE FOLLOWING VARIABLES:
C                 A(I,J), L, MP, P, T, AND V.
C-------------------------------------------------------------------------*

CC*************************************************************************
C*    ***************************************************************     *
C* **** H2O-CO2-CH4-CO-O2-H2-S2-SO2-COS-H2S-N2-NH3-Ar FLUID MIXTURE ****  *
C*    ****  IWM = 1   ------- NON-IDEAL FLUID-MIXTURE MODEL      ****     *
C*    ****              ==>  SUBROUTINE GAMME2                   ****     *
C*    ****  IWM = 2   ------- IDEAL-MIXING MODEL (pure fluids)   ****     *
C*    ****              ==>  SUBROUTINE GAMME1                   ****     *
C*    ***************************************************************     *
CC*************************************************************************

      IWM = 1

      IF (IWM .EQ. 2) GO TO 555

C--------------------------------------
CC  NON-IDEAL MIXING
C--------------------------------------
C
      CALL INTERW(M, T, P, V)

CCCCCCCCCCCCCCCCCCCCCCC
C  !!! IF ONE WOULD LIKE TO CHANGE W(I,J,M)'s in SOLGAS or CHEMSAGE,
C         THE PROGRAMS WILL ASK HIM TO GIVE OPTION "W",
C       and INPUT ICH and JCH (comp. nos. in mix.) AND MCH (mix. no.),
C           AND FINALLY THE NEW VALUES FOR W(ICH,JCH,MCH)'s

CCCCCCCCCCCCCCCCCCCCCCC
C SURPOSING ONE WILL NOT CHANGE THE INTERACTION ENERGIES W(I,J,M)'s,
C        ----> ICH = JCH = MCH = 0
      ICH = 0
      JCH = 0
      MCH = 0

C
      IF (ICH.NE.1.OR.JCH.NE.2.OR.MCH.NE.1) W(1,2,1) = WM(1,2)/RT
      IF (ICH.NE.1.OR.JCH.NE.3.OR.MCH.NE.1) W(1,3,1) = WM(1,3)/RT
      IF (ICH.NE.1.OR.JCH.NE.4.OR.MCH.NE.1) W(1,4,1) = WM(1,4)/RT
      IF (ICH.NE.1.OR.JCH.NE.5.OR.MCH.NE.1) W(1,5,1) = WM(1,5)/RT
      IF (ICH.NE.1.OR.JCH.NE.6.OR.MCH.NE.1) W(1,6,1) = WM(1,6)/RT
      IF (ICH.NE.1.OR.JCH.NE.7.OR.MCH.NE.1) W(1,7,1) = WM(1,7)/RT
      IF (ICH.NE.1.OR.JCH.NE.8.OR.MCH.NE.1) W(1,8,1) = WM(1,8)/RT
      IF (ICH.NE.1.OR.JCH.NE.9.OR.MCH.NE.1) W(1,9,1) = WM(1,9)/RT
      IF (ICH.NE.1.OR.JCH.NE.10.OR.MCH.NE.1) W(1,10,1) = WM(1,10)/RT
      IF (ICH.NE.1.OR.JCH.NE.11.OR.MCH.NE.1) W(1,11,1) = WM(1,11)/RT
      IF (ICH.NE.1.OR.JCH.NE.12.OR.MCH.NE.1) W(1,12,1) = WM(1,12)/RT
      IF (ICH.NE.1.OR.JCH.NE.13.OR.MCH.NE.1) W(1,13,1) = WM(1,13)/RT
C
      IF (ICH.NE.2.OR.JCH.NE.1.OR.MCH.NE.1) W(2,1,1) = W(1,2,1)
      IF (ICH.NE.2.OR.JCH.NE.3.OR.MCH.NE.1) W(2,3,1) = WM(2,3)/RT
      IF (ICH.NE.2.OR.JCH.NE.4.OR.MCH.NE.1) W(2,4,1) = WM(2,4)/RT
      IF (ICH.NE.2.OR.JCH.NE.5.OR.MCH.NE.1) W(2,5,1) = WM(2,5)/RT
      IF (ICH.NE.2.OR.JCH.NE.6.OR.MCH.NE.1) W(2,6,1) = WM(2,6)/RT
      IF (ICH.NE.2.OR.JCH.NE.7.OR.MCH.NE.1) W(2,7,1) = WM(2,7)/RT
      IF (ICH.NE.2.OR.JCH.NE.8.OR.MCH.NE.1) W(2,8,1) = WM(2,8)/RT
      IF (ICH.NE.2.OR.JCH.NE.9.OR.MCH.NE.1) W(2,9,1) = WM(2,9)/RT
      IF (ICH.NE.2.OR.JCH.NE.10.OR.MCH.NE.1) W(2,10,1) = WM(2,10)/RT
      IF (ICH.NE.2.OR.JCH.NE.11.OR.MCH.NE.1) W(2,11,1) = WM(2,11)/RT
      IF (ICH.NE.2.OR.JCH.NE.12.OR.MCH.NE.1) W(2,12,1) = WM(2,12)/RT
      IF (ICH.NE.2.OR.JCH.NE.13.OR.MCH.NE.1) W(2,13,1) = WM(2,13)/RT
C
      IF (ICH.NE.3.OR.JCH.NE.1.OR.MCH.NE.1) W(3,1,1) = W(1,3,1)
      IF (ICH.NE.3.OR.JCH.NE.2.OR.MCH.NE.1) W(3,2,1) = W(2,3,1)
      IF (ICH.NE.3.OR.JCH.NE.4.OR.MCH.NE.1) W(3,4,1) = WM(3,4)/RT
      IF (ICH.NE.3.OR.JCH.NE.5.OR.MCH.NE.1) W(3,5,1) = WM(3,5)/RT
      IF (ICH.NE.3.OR.JCH.NE.6.OR.MCH.NE.1) W(3,6,1) = WM(3,6)/RT
      IF (ICH.NE.3.OR.JCH.NE.7.OR.MCH.NE.1) W(3,7,1) = WM(3,7)/RT
      IF (ICH.NE.3.OR.JCH.NE.8.OR.MCH.NE.1) W(3,8,1) = WM(3,8)/RT
      IF (ICH.NE.3.OR.JCH.NE.9.OR.MCH.NE.1) W(3,9,1) = WM(3,9)/RT
      IF (ICH.NE.3.OR.JCH.NE.10.OR.MCH.NE.1) W(3,10,1) = WM(3,10)/RT
      IF (ICH.NE.3.OR.JCH.NE.11.OR.MCH.NE.1) W(3,11,1) = WM(3,11)/RT
      IF (ICH.NE.3.OR.JCH.NE.12.OR.MCH.NE.1) W(3,12,1) = WM(3,12)/RT
      IF (ICH.NE.3.OR.JCH.NE.13.OR.MCH.NE.1) W(3,13,1) = WM(3,13)/RT
C
      IF (ICH.NE.4.OR.JCH.NE.1.OR.MCH.NE.1) W(4,1,1) = W(1,4,1)
      IF (ICH.NE.4.OR.JCH.NE.2.OR.MCH.NE.1) W(4,2,1) = W(2,4,1)
      IF (ICH.NE.4.OR.JCH.NE.3.OR.MCH.NE.1) W(4,3,1) = W(3,4,1)
      IF (ICH.NE.4.OR.JCH.NE.5.OR.MCH.NE.1) W(4,5,1) = WM(4,5)/RT
      IF (ICH.NE.4.OR.JCH.NE.6.OR.MCH.NE.1) W(4,6,1) = WM(4,6)/RT
      IF (ICH.NE.4.OR.JCH.NE.7.OR.MCH.NE.1) W(4,7,1) = WM(4,7)/RT
      IF (ICH.NE.4.OR.JCH.NE.8.OR.MCH.NE.1) W(4,8,1) = WM(4,8)/RT
      IF (ICH.NE.4.OR.JCH.NE.9.OR.MCH.NE.1) W(4,9,1) = WM(4,9)/RT
      IF (ICH.NE.4.OR.JCH.NE.10.OR.MCH.NE.1) W(4,10,1) = WM(4,10)/RT
      IF (ICH.NE.4.OR.JCH.NE.11.OR.MCH.NE.1) W(4,11,1) = WM(4,11)/RT
      IF (ICH.NE.4.OR.JCH.NE.12.OR.MCH.NE.1) W(4,12,1) = WM(4,12)/RT
      IF (ICH.NE.4.OR.JCH.NE.13.OR.MCH.NE.1) W(4,13,1) = WM(4,13)/RT
C
      IF (ICH.NE.5.OR.JCH.NE.1.OR.MCH.NE.1) W(5,1,1) = W(1,5,1)
      IF (ICH.NE.5.OR.JCH.NE.2.OR.MCH.NE.1) W(5,2,1) = W(2,5,1)
      IF (ICH.NE.5.OR.JCH.NE.3.OR.MCH.NE.1) W(5,3,1) = W(3,5,1)
      IF (ICH.NE.5.OR.JCH.NE.4.OR.MCH.NE.1) W(5,4,1) = W(4,5,1)
      IF (ICH.NE.5.OR.JCH.NE.6.OR.MCH.NE.1) W(5,6,1) = WM(5,6)/RT
      IF (ICH.NE.5.OR.JCH.NE.7.OR.MCH.NE.1) W(5,7,1) = WM(5,7)/RT
      IF (ICH.NE.5.OR.JCH.NE.8.OR.MCH.NE.1) W(5,8,1) = WM(5,8)/RT
      IF (ICH.NE.5.OR.JCH.NE.9.OR.MCH.NE.1) W(5,9,1) = WM(5,9)/RT
      IF (ICH.NE.5.OR.JCH.NE.10.OR.MCH.NE.1) W(5,10,1) = WM(5,10)/RT
      IF (ICH.NE.5.OR.JCH.NE.11.OR.MCH.NE.1) W(5,11,1) = WM(5,11)/RT
      IF (ICH.NE.5.OR.JCH.NE.12.OR.MCH.NE.1) W(5,12,1) = WM(5,12)/RT
      IF (ICH.NE.5.OR.JCH.NE.13.OR.MCH.NE.1) W(5,13,1) = WM(5,13)/RT
C
      IF (ICH.NE.6.OR.JCH.NE.1.OR.MCH.NE.1) W(6,1,1) = W(1,6,1)
      IF (ICH.NE.6.OR.JCH.NE.2.OR.MCH.NE.1) W(6,2,1) = W(2,6,1)
      IF (ICH.NE.6.OR.JCH.NE.3.OR.MCH.NE.1) W(6,3,1) = W(3,6,1)
      IF (ICH.NE.6.OR.JCH.NE.4.OR.MCH.NE.1) W(6,4,1) = W(4,6,1)
      IF (ICH.NE.6.OR.JCH.NE.5.OR.MCH.NE.1) W(6,5,1) = W(5,6,1)
      IF (ICH.NE.6.OR.JCH.NE.7.OR.MCH.NE.1) W(6,7,1) = WM(6,7)/RT
      IF (ICH.NE.6.OR.JCH.NE.8.OR.MCH.NE.1) W(6,8,1) = WM(6,8)/RT
      IF (ICH.NE.6.OR.JCH.NE.9.OR.MCH.NE.1) W(6,9,1) = WM(6,9)/RT
      IF (ICH.NE.6.OR.JCH.NE.10.OR.MCH.NE.1) W(6,10,1) = WM(6,10)/RT
      IF (ICH.NE.6.OR.JCH.NE.11.OR.MCH.NE.1) W(6,11,1) = WM(6,11)/RT
      IF (ICH.NE.6.OR.JCH.NE.12.OR.MCH.NE.1) W(6,12,1) = WM(6,12)/RT
      IF (ICH.NE.6.OR.JCH.NE.13.OR.MCH.NE.1) W(6,13,1) = WM(6,13)/RT
C
      IF (ICH.NE.7.OR.JCH.NE.1.OR.MCH.NE.1) W(7,1,1) = W(1,7,1)
      IF (ICH.NE.7.OR.JCH.NE.2.OR.MCH.NE.1) W(7,2,1) = W(2,7,1)
      IF (ICH.NE.7.OR.JCH.NE.3.OR.MCH.NE.1) W(7,3,1) = W(3,7,1)
      IF (ICH.NE.7.OR.JCH.NE.4.OR.MCH.NE.1) W(7,4,1) = W(4,7,1)
      IF (ICH.NE.7.OR.JCH.NE.5.OR.MCH.NE.1) W(7,5,1) = W(5,7,1)
      IF (ICH.NE.7.OR.JCH.NE.6.OR.MCH.NE.1) W(7,6,1) = W(6,7,1)
      IF (ICH.NE.7.OR.JCH.NE.8.OR.MCH.NE.1) W(7,8,1) = WM(7,8)/RT
      IF (ICH.NE.7.OR.JCH.NE.9.OR.MCH.NE.1) W(7,9,1) = WM(7,9)/RT
      IF (ICH.NE.7.OR.JCH.NE.10.OR.MCH.NE.1) W(7,10,1) = WM(7,10)/RT
      IF (ICH.NE.7.OR.JCH.NE.11.OR.MCH.NE.1) W(7,11,1) = WM(7,11)/RT
      IF (ICH.NE.7.OR.JCH.NE.12.OR.MCH.NE.1) W(7,12,1) = WM(7,12)/RT
      IF (ICH.NE.7.OR.JCH.NE.13.OR.MCH.NE.1) W(7,13,1) = WM(7,13)/RT
C
      IF (ICH.NE.8.OR.JCH.NE.1.OR.MCH.NE.1) W(8,1,1) = W(1,8,1)
      IF (ICH.NE.8.OR.JCH.NE.2.OR.MCH.NE.1) W(8,2,1) = W(2,8,1)
      IF (ICH.NE.8.OR.JCH.NE.3.OR.MCH.NE.1) W(8,3,1) = W(3,8,1)
      IF (ICH.NE.8.OR.JCH.NE.4.OR.MCH.NE.1) W(8,4,1) = W(4,8,1)
      IF (ICH.NE.8.OR.JCH.NE.5.OR.MCH.NE.1) W(8,5,1) = W(5,8,1)
      IF (ICH.NE.8.OR.JCH.NE.6.OR.MCH.NE.1) W(8,6,1) = W(6,8,1)
      IF (ICH.NE.8.OR.JCH.NE.7.OR.MCH.NE.1) W(8,7,1) = W(7,8,1)
      IF (ICH.NE.8.OR.JCH.NE.9.OR.MCH.NE.1) W(8,9,1) = WM(8,9)/RT
      IF (ICH.NE.8.OR.JCH.NE.10.OR.MCH.NE.1) W(8,10,1) = WM(8,10)/RT
      IF (ICH.NE.8.OR.JCH.NE.11.OR.MCH.NE.1) W(8,11,1) = WM(8,11)/RT
      IF (ICH.NE.8.OR.JCH.NE.12.OR.MCH.NE.1) W(8,12,1) = WM(8,12)/RT
      IF (ICH.NE.8.OR.JCH.NE.13.OR.MCH.NE.1) W(8,13,1) = WM(8,13)/RT
C
      IF (ICH.NE.9.OR.JCH.NE.1.OR.MCH.NE.1) W(9,1,1) = W(1,9,1)
      IF (ICH.NE.9.OR.JCH.NE.2.OR.MCH.NE.1) W(9,2,1) = W(2,9,1)
      IF (ICH.NE.9.OR.JCH.NE.3.OR.MCH.NE.1) W(9,3,1) = W(3,9,1)
      IF (ICH.NE.9.OR.JCH.NE.4.OR.MCH.NE.1) W(9,4,1) = W(4,9,1)
      IF (ICH.NE.9.OR.JCH.NE.5.OR.MCH.NE.1) W(9,5,1) = W(5,9,1)
      IF (ICH.NE.9.OR.JCH.NE.6.OR.MCH.NE.1) W(9,6,1) = W(6,9,1)
      IF (ICH.NE.9.OR.JCH.NE.7.OR.MCH.NE.1) W(9,7,1) = W(7,9,1)
      IF (ICH.NE.9.OR.JCH.NE.8.OR.MCH.NE.1) W(9,8,1) = W(8,9,1)
      IF (ICH.NE.9.OR.JCH.NE.10.OR.MCH.NE.1) W(9,10,1) = WM(9,10)/RT
      IF (ICH.NE.9.OR.JCH.NE.11.OR.MCH.NE.1) W(9,11,1) = WM(9,11)/RT
      IF (ICH.NE.9.OR.JCH.NE.12.OR.MCH.NE.1) W(9,12,1) = WM(9,12)/RT
      IF (ICH.NE.9.OR.JCH.NE.13.OR.MCH.NE.1) W(9,13,1) = WM(9,13)/RT
C
      IF (ICH.NE.10.OR.JCH.NE.1.OR.MCH.NE.1) W(10,1,1) = W(1,10,1)
      IF (ICH.NE.10.OR.JCH.NE.2.OR.MCH.NE.1) W(10,2,1) = W(2,10,1)
      IF (ICH.NE.10.OR.JCH.NE.3.OR.MCH.NE.1) W(10,3,1) = W(3,10,1)
      IF (ICH.NE.10.OR.JCH.NE.4.OR.MCH.NE.1) W(10,4,1) = W(4,10,1)
      IF (ICH.NE.10.OR.JCH.NE.5.OR.MCH.NE.1) W(10,5,1) = W(5,10,1)
      IF (ICH.NE.10.OR.JCH.NE.6.OR.MCH.NE.1) W(10,6,1) = W(6,10,1)
      IF (ICH.NE.10.OR.JCH.NE.7.OR.MCH.NE.1) W(10,7,1) = W(7,10,1)
      IF (ICH.NE.10.OR.JCH.NE.8.OR.MCH.NE.1) W(10,8,1) = W(8,10,1)
      IF (ICH.NE.10.OR.JCH.NE.9.OR.MCH.NE.1) W(10,9,1) = W(9,10,1)
      IF (ICH.NE.10.OR.JCH.NE.11.OR.MCH.NE.1) W(10,11,1) = WM(10,11)/RT
      IF (ICH.NE.10.OR.JCH.NE.12.OR.MCH.NE.1) W(10,12,1) = WM(10,12)/RT
      IF (ICH.NE.10.OR.JCH.NE.13.OR.MCH.NE.1) W(10,13,1) = WM(10,13)/RT
C
      IF (ICH.NE.11.OR.JCH.NE.1.OR.MCH.NE.1) W(11,1,1) = W(1,11,1)
      IF (ICH.NE.11.OR.JCH.NE.2.OR.MCH.NE.1) W(11,2,1) = W(2,11,1)
      IF (ICH.NE.11.OR.JCH.NE.3.OR.MCH.NE.1) W(11,3,1) = W(3,11,1)
      IF (ICH.NE.11.OR.JCH.NE.4.OR.MCH.NE.1) W(11,4,1) = W(4,11,1)
      IF (ICH.NE.11.OR.JCH.NE.5.OR.MCH.NE.1) W(11,5,1) = W(5,11,1)
      IF (ICH.NE.11.OR.JCH.NE.6.OR.MCH.NE.1) W(11,6,1) = W(6,11,1)
      IF (ICH.NE.11.OR.JCH.NE.7.OR.MCH.NE.1) W(11,7,1) = W(7,11,1)
      IF (ICH.NE.11.OR.JCH.NE.8.OR.MCH.NE.1) W(11,8,1) = W(8,11,1)
      IF (ICH.NE.11.OR.JCH.NE.9.OR.MCH.NE.1) W(11,9,1) = W(9,11,1)
      IF (ICH.NE.11.OR.JCH.NE.10.OR.MCH.NE.1) W(11,10,1) = W(10,11,1)
      IF (ICH.NE.11.OR.JCH.NE.12.OR.MCH.NE.1) W(11,12,1) = WM(11,12)/RT
      IF (ICH.NE.11.OR.JCH.NE.13.OR.MCH.NE.1) W(11,13,1) = WM(11,13)/RT
C
      IF (ICH.NE.12.OR.JCH.NE.1.OR.MCH.NE.1) W(12,1,1) = W(1,12,1)
      IF (ICH.NE.12.OR.JCH.NE.2.OR.MCH.NE.1) W(12,2,1) = W(2,12,1)
      IF (ICH.NE.12.OR.JCH.NE.3.OR.MCH.NE.1) W(12,3,1) = W(3,12,1)
      IF (ICH.NE.12.OR.JCH.NE.4.OR.MCH.NE.1) W(12,4,1) = W(4,12,1)
      IF (ICH.NE.12.OR.JCH.NE.5.OR.MCH.NE.1) W(12,5,1) = W(5,12,1)
      IF (ICH.NE.12.OR.JCH.NE.6.OR.MCH.NE.1) W(12,6,1) = W(6,12,1)
      IF (ICH.NE.12.OR.JCH.NE.7.OR.MCH.NE.1) W(12,7,1) = W(7,12,1)
      IF (ICH.NE.12.OR.JCH.NE.8.OR.MCH.NE.1) W(12,8,1) = W(8,12,1)
      IF (ICH.NE.12.OR.JCH.NE.9.OR.MCH.NE.1) W(12,9,1) = W(9,12,1)
      IF (ICH.NE.12.OR.JCH.NE.10.OR.MCH.NE.1) W(12,10,1) = W(10,12,1)
      IF (ICH.NE.12.OR.JCH.NE.11.OR.MCH.NE.1) W(12,11,1) = W(11,12,1)
      IF (ICH.NE.12.OR.JCH.NE.13.OR.MCH.NE.1) W(12,13,1) = WM(12,13)/RT
C
      IF (ICH.NE.13.OR.JCH.NE.1.OR.MCH.NE.1) W(13,1,1) = W(1,13,1)
      IF (ICH.NE.13.OR.JCH.NE.2.OR.MCH.NE.1) W(13,2,1) = W(2,13,1)
      IF (ICH.NE.13.OR.JCH.NE.3.OR.MCH.NE.1) W(13,3,1) = W(3,13,1)
      IF (ICH.NE.13.OR.JCH.NE.4.OR.MCH.NE.1) W(13,4,1) = W(4,13,1)
      IF (ICH.NE.13.OR.JCH.NE.5.OR.MCH.NE.1) W(13,5,1) = W(5,13,1)
      IF (ICH.NE.13.OR.JCH.NE.6.OR.MCH.NE.1) W(13,6,1) = W(6,13,1)
      IF (ICH.NE.13.OR.JCH.NE.7.OR.MCH.NE.1) W(13,7,1) = W(7,13,1)
      IF (ICH.NE.13.OR.JCH.NE.8.OR.MCH.NE.1) W(13,8,1) = W(8,13,1)
      IF (ICH.NE.13.OR.JCH.NE.9.OR.MCH.NE.1) W(13,9,1) = W(9,13,1)
      IF (ICH.NE.13.OR.JCH.NE.10.OR.MCH.NE.1) W(13,10,1) = W(10,13,1)
      IF (ICH.NE.13.OR.JCH.NE.11.OR.MCH.NE.1) W(13,11,1) = W(11,13,1)
      IF (ICH.NE.13.OR.JCH.NE.12.OR.MCH.NE.1) W(13,12,1) = W(12,13,1)

C
      CALL GAMMA2(M, XN, T, P)
      GO TO 666

C--------------------------------------
CC  IDEAL MIXING
C--------------------------------------
 555  DO 444 I = 1, ML(1)
      DO 333 J = 1, ML(1)
               W(I,J,1) = 0.0
 333  CONTINUE
 444  CONTINUE
      CALL GAMMA1(M, XN, T, P)
      DO 17 I = MF(M), ML(M)
            AKTFLN(I) = AKTFLN(I) - LOG(P)
   17 CONTINUE

 666  CONTINUE
C
      RETURN
      END

CC
      SUBROUTINE INTERW(M, T, P, V)
CC
C*******************************************************************
C*           INTERW IS A SUBROUTINE FOR THE CALCULATION            *
C*                 OF INTERACTION ENERGIES (WIJ)                   *
C*    BY USING THE KIHARA AND THE STOCKMAYER POTENTIEL FUNCTIONS.  *
C*                                                                 *
C*               REFERENCES: Tren & Lienhard (1971)                *
C*                           Prausnitz et al. (1986)               *
C*                           Reid (1987)                           *
C*                           Saxena & Fei (1988)                   *
C*                           Shi & Saxena (1992)                   *
C*******************************************************************
CC    
C      IMPLICIT DOUBLE PRECISION(A-H,O-Z)
      PARAMETER(LA=15,LB=20,LC=20)
      COMMON /SALLA/ A(LA,LB), B0(LB), GV(LA), PI(2*LB), VGAS(LA), L
      COMMON /SALLI/ Y(LA), MF(LC+1), ML(LC+1), MP, MV
      COMMON /SALLR/ AKTFLN(LA), PX, RT, VX, X(LA), YTOT(LC)
      COMMON /SSGFC/ XSCAN, YF(LA), YFTOT(LC)
      COMMON /SWIJ/ W(15,15,LC), WM(15,15), ICH, JCH, MCH
      DIMENSION AGAS(13), DGAS(13), EGAS(13), UGAS(13), SGAS(13)
      DIMENSION XGAS(13), RGAS(13), WII(13), AIJ(13,13), BIJ(13,13)
      DIMENSION DIJ(13,13), EIJ(13,13), UIJ(13,13)
      DIMENSION RIJ(13,13), WMIX(13,13)
C      DATA AGAS/0.0D0,0.615D0,0.283D0,0.0D0,0.308D0,0.0D0,
C     *          4*0.3D0, 0.250D0, 0.300D0, 0.121D0/
      DATA DGAS/2.650D0,3.760D0,3.565D0,3.760D0,3.109D0,2.960D0,
     *          4*3.0D0, 3.526D0, 3.000D0, 3.317D0/
      DATA EGAS/380.0D0,424.16D0,227.13D0,100.2D0,194.3D0,36.7D0,
     *          4*200.0D0, 139.2D0, 200.0D0, 146.52D0/
      DATA UGAS/1.85D0,5*0.0D0,
     *          0.0D0, 1.61D0, 0.0D0, 0.0D0, 0.0D0, 0.0D0, 0.0D0/
      DATA SGAS/1.59D0,2.65D0,2.60D0,1.95D0,1.60D0,0.79D0,
     *          2.0D0, 3.72D0, 2.0D0, 2.0D0, 2.0D0, 2.0D0, 2.0D0/
CC
      AGAS(1)=0.
      AGAS(2)=0.615
      AGAS(3)=0.283
      AGAS(4)=0.
      AGAS(5)=0.308
      AGAS(6)=0.
      AGAS(7)=0.3
      AGAS(8)=0.3
      AGAS(9)=0.3
      AGAS(10)=0.3
      AGAS(11)=0.25
      AGAS(12)=0.3
      AGAS(13)=0.121
C
      DO 5 I = MF(M), ML(M)
      AGAS(I) = AGAS(I)*DGAS(I)/(1. + AGAS(I))
      XGAS(I) = (UGAS(I)**2.)*(DGAS(I)**3.)*EGAS(I)
      RGAS(I) = 2.D8*(21.*VGAS(I)/(88.*6.023D23))**(1./3.)
      WII(I) = RT*(4.*EGAS(I)*(((DGAS(I) - AGAS(I))/(RGAS(I) -
     *AGAS(I)))**12. - ((DGAS(I) - AGAS(I))/(RGAS(I) - AGAS(I)))
     ***6.) - XGAS(I)/RGAS(I)**3.)
    5 CONTINUE
C
      DO 3 I = MF(M), ML(M)
      DO 3 J = MF(M), ML(M)
      IF (I .NE. J .AND. I .LT. J ) THEN
      AIJ(I,J) = (AGAS(I) + AGAS(J))/2.
      BIJ(I,J) = 1. + (SGAS(J)/(DGAS(J)**3.))*UGAS(I)
     **(EGAS(I)/EGAS(J))**0.5/4.
      DIJ(I,J) = (BIJ(I,J)**(-1./6.))*(DGAS(I) + DGAS(J))/2.
      EIJ(I,J) = (EGAS(I)*EGAS(J))**0.5
      UIJ(I,J) = (UGAS(I)*UGAS(J))**0.5
      RIJ(I,J) = (RGAS(I) + RGAS(J))/2.
      WMIX(I,J) = RT*(4.*EIJ(I,J)*(((DIJ(I,J) - AIJ(I,J))/
     *(RIJ(I,J) - AIJ(I,J)))**12. - ((DIJ(I,J) - AIJ(I,J))/
     *(RIJ(I,J) - AIJ(I,J)))**6.) - UIJ(I,J)**2.*EIJ(I,J)*
     *DIJ(I,J)**3./RIJ(I,J)**3.)
      WM(I,J) = (2.*WMIX(I,J) - WII(I) - WII(J))/(2.*T)
      END IF
    3 CONTINUE
    7 FORMAT('       I = ',I2,'  J = ',I2,'   W(I,J) = ',E12.2)
C
      RETURN
      END

CC
      SUBROUTINE GAMMA2(M, XN, T, P)
CC
C*******************************************************************
C*           GAMME2 IS A SUBROUTINE FOR THE CALCULATION            *
C*           OF ACTIVITIES FOR NON-IDEAL MIXING SPECIES            *
C*                  IN 13-COMPONENT SYSTEM:                        *
C*          H2O-CO2-CH4-CO-O2-H2-S2-SO2-COS-H2S-N2-NH3-Ar.         *
C*                                                                 *
C*    1. THE BINARY SOLUTION MODEL IS VAN LA FORMULATION.          *
C*    2. THE KOHLER MODEL HAS BEEN USED TO COMPUTE ACTIVITIES      *
C*             IN A MULTICOMPONENT SYSTEM.                         *
C*******************************************************************
CC
C      IMPLICIT DOUBLE PRECISION(A-H,O-Z)
      PARAMETER(LA=15,LB=20,LC=20)
      COMMON /SALLA/ A(LA,LB), B0(LB), GV(LA), PI(2*LB), VGAS(LA), L
      COMMON /SALLI/ Y(LA), MF(LC+1), ML(LC+1), MP, MV
      COMMON /SALLR/ AKTFLN(LA), PX, RT, VX, X(LA), YTOT(LC)
      COMMON /SWIJ/ W(15,15,LC), WM(15,15), ICH, JCH, MCH
C
      DO 8 I = MF(M), ML(M)
      AKTFLN(I) = 0.
      DO 8 J = MF(M), ML(M)
      IF (J .NE. I .AND. X(J) .GT. 0.) THEN
      IF (X(I) .GT. 0.) THEN
      TEMP = X(I) + X(J)
      X1 = X(I)/TEMP
      X2 = 1. - X1
      TERM = VGAS(I) + VGAS(J)
      Q1 = 5.*VGAS(I)/TERM
      Q2 = 5. - Q1
      IA = I - MF(M) + 1
      JA = J - MF(M) + 1
      TEMP1 = 2.*W(IA,JA,M)*X1*X2*Q1*Q2/(X1*Q1 + X2*Q2)
      TEMP2 = 2.*W(IA,JA,M)*Q1/(1. + Q1*X1/(Q2*X2))**2.
      AKTFLN(I) = AKTFLN(I) + TEMP*(TEMP1*(1. - TEMP) + TEMP2)
      END IF
      IF (J .LT. ML(M)) THEN
      DO 9 K = J+1, ML(M)
      IF (K .NE. I .AND. X(K) .GT. 0.) THEN
      TEMP = X(J) + X(K)
      X1 = X(J)/TEMP
      X2 = 1. - X1
      TERM = VGAS(J) + VGAS(K)
      Q1 = 5.*VGAS(J)/TERM
      Q2 = 5. - Q1
      KA = K - MF(M) + 1
      TEMP1 = 2.*W(JA,KA,M)*X1*X2*Q1*Q2/(X1*Q1 + X2*Q2)
      AKTFLN(I) = AKTFLN(I) - TEMP*TEMP*TEMP1
      END IF
    9 CONTINUE
      END IF
      END IF
    8 CONTINUE
C
      RETURN
      END

CC
      SUBROUTINE GAMMA1(M, XN, T, P)
CC
C*******************************************************************
C*           GAMME1 IS A SUBROUTINE FOR THE CALCULATION            *
C*             OF ACTIVITIES FOR IDEAL MIXING SPECIES              *
C*                  IN 13-COMPONENT SYSTEM:                        *
C*          H2O-CO2-CH4-CO-O2-H2-S2-SO2-COS-H2S-N2-NH3-Ar.         *
C*                                                                 *
C*******************************************************************
CC
C      IMPLICIT DOUBLE PRECISION(A-H,O-Z)
      PARAMETER(LA=15,LC=20)
      COMMON /SALLI/ Y(LA), MF(LC+1), ML(LC+1), MP, MV
      COMMON /SALLR/ AKTFLN(LA), PX, RT, VX, X(LA), YTOT(LC)
      COMMON /SWIJ/ W(15,15,LC), WM(15,15), ICH, JCH, MCH
C
      DO 1 I = MF(M), ML(M)
      AKTFLN(I) = 0.
      DO 1 J = MF(M), ML(M)
      IF (J .NE. I .AND. X(J) .GT. 0.) THEN
      IF (X(I) .GT. 0.) THEN
      TEMP = X(I) + X(J)
      X1 = X(I)/TEMP
      X2 = 1. - X1
      IA = I - MF(M) + 1
      JA = J - MF(M) + 1
      TEMP1 = W(IA,JA,M)*X2 + W(JA,IA,M)*X1
      TEMP2 = W(IA,JA,M)+ 2.*X1*(W(JA,IA,M) - W(IA,JA,M))
      AKTFLN(I) = AKTFLN(I) + TEMP*X2*(TEMP1*X1*(1. - TEMP) + TEMP2*X2)
      END IF
      IF (J .LT. ML(M)) THEN
      DO 2 K = J+1, ML(M)
      IF (K .NE. I .AND. X(K) .GT. 0.) THEN
      TEMP = X(J) + X(K)
      X1 = X(J)/TEMP
      X2 = 1. - X1
      KA = K - MF(M) + 1
      TEMP1 = W(JA,KA,M)*X2 + W(KA,JA,M)*X1
      AKTFLN(I) = AKTFLN(I) - TEMP*TEMP*TEMP1*X1*X2
      END IF
    2 CONTINUE
      END IF
      END IF
    1 CONTINUE
C
      RETURN
      END
