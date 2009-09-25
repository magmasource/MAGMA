c         program aaa
c      write (6,*) ' t p '
c     read (5,*) t,p
c     call h2o (t,p, v,g)
c     write (6,*) ' t p v g  ',t,p,v,g
c     go to 1
c     end
c 
       subroutine h2o (T,P,V,g)

       real*8 PMPA, T8, dens, db, gb, p1,dens1
       t8 = t

       PMPA = P/10.0
c     write (6,*) ' t8= ',t8,' pmpa= ',pmpa
       dens = DB (T8, PMPA)
c      write (6,*) ' dens ',dens
       p1 = 0.10
       dens1 = db (t8, p1)
c     write (6,*) ' dens1= ', dens1
       gibbs1 = GB (T8, dens)
       gibbs2 = gb (t8, dens1) 
       v = 1.0/dens*1000000.0*(18.03/1000.0)
       g = (gibbs1 - gibbs2)*18.03
       return
       end

C****************************************************************************
         BLOCKDATA REAL38
C*****************************************************************************
C
C
C   THIS SUBROUTINE SETS COEFFICIENTS FOR THE
C   SAUL AND WAGNER -EQUATION OF STATE
C
      IMPLICIT REAL*8(A-H,O-Z)
C
      COMMON /CEPS/ EPS
      COMMON/CFUNC/TF(58),TSAV,DF(-1:13),DSAV
     *             ,EX(0:6),EXD(0:6),EXDD(0:6)
      COMMON/EQU/G(58),IDPOT(58),ITPOT(58),IMAXF(-1:6),IEX,NT
      COMMON/CNORM/TNORM,DNORM
      COMMON/CFAC/FACTOR
      COMMON/CCPEQ/TCEQ,PCEQ,DCEQ
      COMMON /CFNI/  B2, B(7), TPID(7), NPOL, N
      COMMON /CNULLP/T0,D0,F0,H0,U0,S0,G0
C
      DATA          EPS/1.D-8/, FACTOR/1.D0/
      DATA EX(0)/1.D0/, EXD(0)/0.D0/, EXDD(0)/0.D0/
      DATA IMAXF/0,12,12,33,38,38,38,38/, IEX/3/, NT/38/
C
      DATA (IDPOT(I),ITPOT(I), I=1,38)/
C        D     T      D     T      D     T      D     T
     *   1,    0,     1,    2,     2,    0,     2,    1,
     *   2,    2,     2,    3,     3,    5,     5,    0,
     *   5,    1,     6,    3,     7,    2,     8,    5,
C
     *   1,    5,     1,    7,     1,    9,     2,    5,
     *   3,    4,     3,    6,     3,   13,     4,    5,
     *   5,    2,     5,    3,     6,    2,     7,    0,
     *   7,   11,     8,    1,     8,    4,     9,    0,
     *  11,    0,    11,    3,    11,    5,    11,    6,
     *  11,    7,
C
     *   2,   13,     2,   14,     3,   15,     3,   24,
     *   5,   15/
C
      DATA (G(I), I=1,38)
     */ 0.2330009013D+00,-0.1402091128D+01, 0.1172248041D+00,
     * -0.1850749499D+00, 0.1770110422D+00, 0.5525151794D-01,
     * -0.3413257380D-03, 0.8557274367D-03, 0.3716900685D-03,
     * -0.1308871233D-03, 0.3216895199D-04, 0.2785881034D-06,
     * -0.3521511130D+00, 0.7881914536D-01,-0.1519666610D-01,
     * -0.1068458586D+00,-0.2055046288D+00, 0.9146198012D+00,
     *  0.3213343569D-03,-0.1133591391D+01,-0.3107520749D+00,
     *  0.1217901527D+01,-0.4481710831D+00, 0.5494218772D-01,
     * -0.8665222096D-04, 0.3844084088D-01, 0.9853044884D-02,
     * -0.1767598472D-01, 0.1488549222D-02,-0.3070719069D-02,
     *  0.3880803280D-02,-0.2627505215D-02, 0.5258371388D-03,
     * -0.1716396901D+00, 0.7188823624D-01, 0.5881268357D-01,
     * -0.1455938880D-01,-0.1216139400D-01/
C
      DATA TNORM /647.14D0/, DNORM /322.D0/
C
      DATA TCEQ /647.14D0/, DCEQ /322.D0/, PCEQ /22.064D0/
C
      DATA D0/ 999.787398238D0/, T0/273.16D0/
      DATA (B(I),I=1,7)/-8.317709547068D0,6.681504888442D0,
     > 0.12436d0,0.97315d0,1.27950d0,0.969560d0,0.24873d0/
       data
     > (tpid(i),i=1,7)/0.d0,1.d0,1.287202151d0,3.537101709d0,
     > 7.740210774d0,9.243749421d0,27.50564020d0/,b2/3.00632d0/,
     > f0/0.d0/,h0/0.d0/,u0/0.d0/,s0/0.d0/,g0/0.d0/,npol/2/,n/7/

C
      END

C****************************************************************************
C
C           SET OF SUBROUTINES AND FUNCTIONS TO CALCULATE      19.10.90
C           VARIOUS DERIVATIVES OF AN EQUATION FOR THE
C           NORMALIZED REAL AND IDEAL PART OF THE
C           HELMHOLTZ FUNCTION F.
C
C****************************************************************************
C    USUAL INPUT
C
C    T    TEMPERATURE (NOT NORMALIZED)
C    D    DENSITY (NOT NORMALIZED)
C
C
C********************************************************************
C
C    The following program with functions and subroutines should be
C    used like a library. You can call various Thermodynamic
C    Properties listed in the table below :
C
C                                          F = FUNCTION
C                                          S = SUBROUTINE
C
C
C F <DB>     THIS FUNCTION CALCULATES THE DENSITY FOR GIVEN P,T
C
C F <PB>     THIS FUNCTION CALCULATES THE PRESSURE
C
C F <DPDTB>  1.DERIVATIVE OF PRESSURE VERSUS TEMPERATURE
C
C F <DPDDB>  1.DERIVATION OF PRESSURE VERSUS DENSITY
C
C F <CVB>    ISOCHORIC HEAT CAPACITY
C
C F <CPB>    ISOBARIC HEAT CAPACITY
C
C F <WB>     VELOCITY OF SOUND
C
C F <FB>     HELMHOLTZ FUNCTION
C
C F <HB>     ENTHALPY
C
C F <SB>     ENTROPY
C
C F <UB>     INTERNAL ENERGY
C
C F <GB>     GIBBS ENERGY
C
C F <BETASB> ISENTROPIC TEMPERATURE-PRESSURE COEFFICIENT BETAS=(DT/DP)s
C
C F <BB>     2. VIRIALCOEFFICIENT B FOR GIVEN T
C
C F <CB>     3. VIRIALCOEFFICIENT C FOR GIVEN T
C
C F <RJTB>   Joule Thomson Coefficient
C
C F <DTB>    Isothermal throttling coefficient
C
C
C            Saturation lines
C
C
C S <SATT>   CALCULATING DV,DL,P FOR GIVEN T
C
C S <SATP>   CALCULATING T,DV,DL FOR GIVEN P
C
C F <TSEQ>   CALCULATING TS FOR A GIVEN P FROM SAT-EQUATION
C
C S <VPEQL>  LINEAR EXTRAPOLATION OF THE VAPOR-PRESSURE FOR GIVEN T
C
C S <SLEQ>   CALCULATION OF SATURATED LIQUID ENTROPY FOR GIVEN T
C
C S <SVEQ>   CALCULATION OF SATURATED VAPOR ENTROPY FOR GIVEN T
C
C S <HLEQ>   CALCULATION OF SATURATED LIQUID ENTHALPY FOR GIVEN T
C
C S <HVEQ>   CALCULATION OF SATURATED VAPOR ENTHALPY FOR GIVEN T
C
C S <VPEQ>   VAPOUR PRESSURE FOR GIVEN T
C
C S <DLEQ>   SATURATED LIQUID DENSITY FOR GIVEN T
C
C S <DVEQ>   SATURATED VAPOUR DENSITY FOR GIVEN T
C
C S <DPDTEQ> 1. DERIVATION OF VAPORPRESSURE P VERSUS TEMPERATURE T FOR
C            GIVEN T
C
C F <PMELT>  MELTING PRESSURE FOR GIVEN TEMPERATURE
C
C S <TMELT>  MELTING TEMPERATURE FOR GIVEN PRESSURE
C
C F <PSUBL>  SUBLIMATION-PRESSURE FOR GIVEN T
C
C
C     Further information about handling the subroutines and functions You
C     will find in the programs, which are usually well documented.
C
C
C******************************************************************************
C******************************************************************************
      SUBROUTINE TFUNC(T)
C******************************************************************************
C
C    T-FUNCTION
C
      IMPLICIT REAL*8(A-H,O-Z)
      COMMON/EQU/G(58),IDPOT(58),ITPOT(58),IMAXF(-1:6),IEX,NT
      COMMON/CFUNC/TF(58),TSAV,DF(-1:13),DSAV

     *             ,EX(0:6),EXD(0:6),EXDD(0:6)
      COMMON/CNORM/TNORM,DNORM
      COMMON/CFAC/FACTOR
C
      TN=TNORM/T
       DO 10 I=1,NT
  10    TF(I) = G(I)*TN**(ITPOT(I) / FACTOR)
C
      TSAV=T
      RETURN
      END
C
C******************************************************************************
      SUBROUTINE DFUNC(D)
C******************************************************************************
C
C    D-FUNCTION
C
      IMPLICIT REAL*8(A-H,O-Z)
      COMMON/CFUNC/TF(58),TSAV,DF(-1:13),DSAV
     *             ,EX(0:6),EXD(0:6),EXDD(0:6)
      COMMON/CNORM/TNORM,DNORM
C
       DN=D/DNORM
       DF(-1)=1.D0/DN
       DO 10 I=0,13
  10    DF(I) = DF(I-1)*DN
C
      DSAV=D
      CALL EFUNC
      RETURN
      END
C
C******************************************************************************
      SUBROUTINE EFUNC
C******************************************************************************
C
C    THIS FUNCTION CALCULATES THE DN-DERIVATIVES OF THE
C    E-FUNCTION
C
      IMPLICIT REAL*8(A-H,O-Z)
      COMMON/CFUNC/TF(58),TSAV,DF(-1:13),DSAV
     *             ,EX(0:6),EXD(0:6),EXDD(0:6)
      COMMON/EQU/G(58),IDPOT(58),ITPOT(58),IMAXF(-1:6),IEX,NT
C
C       E**(-DN**J)
C
      DO 10 J=1,3
        EX(J)=EXP(-DF(J))
        EXD(J)=-J*DF(J-1)*EX(J)
   10   EXDD(J)= ( J-1 - J*DF(J) )*DF(-1)*EXD(J)
C
      IF( IEX .NE. 6 ) RETURN
C
C        E**(-0.4*DN**J) - E**(-2*DN**6)
C
        IF( DF(1) .LT. .2D0 ) THEN
         EX(6)=  (1.6D0 -   1.92D0*DF(6))*DF(6)
         EXD(6)= (9.6D0 -  23.04D0*DF(6))*DF(5)
         EXDD(6)=(48.D0 - 253.44D0*DF(6))*DF(4)
        ELSE
C*************-Comment-**************************************
C*                                                          *
C* In some cases the following two statements will yield    *
C* values very close to zero. Be shure, that Your system    *
C* is able to calculate these values.
C*                                                          *
C************************************************************
         E1=dEXP(-0.4D0*DF(6))
         E2=dEXP(-2.D0*DF(6))
         EX(6)=E1-E2
         EXD(6)= (12.D0*E2 - 2.4D0*E1)*DF(5)
         EXDD(6)=(5.76D0*E1-144.D0*E2)*DF(10)+5.D0*EXD(6)*DF(-1)
        END IF
C
      RETURN
      END
C
C******************************************************************************
      DOUBLEPRECISION FUNCTION FNR(T,D)
C******************************************************************************
C
C    THIS FUNCTION CALCULATES F'S NORMALIZED REAL PART.
C
      IMPLICIT REAL*8(A-H,O-Z)
      COMMON/EQU/G(58),IDPOT(58),ITPOT(58),IMAXF(-1:6),IEX,NT
      COMMON/CFUNC/TF(58),TSAV,DF(-1:13),DSAV
     *             ,EX(0:6),EXD(0:6),EXDD(0:6)
      COMMON /CEPS/ EPS
      SAVE TSAVE,DSAVE,FNRS
C
      IF( dABS(T-TSAVE) .LT. EPS
     *    .AND. dABS((D-DSAVE)/D) .LT. EPS ) THEN
       FNR=FNRS
       RETURN
      END IF
C
      FNR=0.D0
C
      IF( dABS( TSAV - T )     .GT. EPS ) CALL TFUNC(T)
      IF( dABS( DSAV - D )/D   .GT. EPS ) CALL DFUNC(D)
C
      DO 30 J=0,IEX
       IF(IMAXF(J-1).EQ.IMAXF(J)) GOTO 30
        H=0.D0
        DO 20 I=IMAXF(J-1)+1,IMAXF(J)
         H=H + TF(I)*DF(IDPOT(I))
  20   CONTINUE
       FNR = FNR + H*EX(J)
  30  CONTINUE
C
      FNRS=FNR
      TSAVE=T
      DSAVE=D
C
      RETURN
      END
C******************************************************************************
      DOUBLEPRECISION FUNCTION FNRD(T,D)
C******************************************************************************
C
C    THIS FUNCTION CALCULATES THE 1ST DN
C    DERIVATIVE OF THE F'S NORMALIZED REAL PART.
C
      IMPLICIT REAL*8(A-H,O-Z)
      COMMON/EQU/G(58),IDPOT(58),ITPOT(58),IMAXF(-1:6),IEX,NT
      COMMON/CFUNC/TF(58),TSAV,DF(-1:13),DSAV
     *             ,EX(0:6),EXD(0:6),EXDD(0:6)
      COMMON /CEPS/ EPS
      SAVE TSAVE,DSAVE,FNRDS
C
      IF( dABS(T-TSAVE) .LT. EPS
     *    .AND. dABS((D-DSAVE)/D) .LT. EPS ) THEN
       FNRD=FNRDS
       RETURN
      END IF
C
      FNRD=0.D0
C
      IF( dABS( TSAV - T )     .GT. EPS ) CALL TFUNC(T)
      IF( dABS( DSAV - D )/D  .GT. EPS ) CALL DFUNC(D)
C
        DO 10 I=1,IMAXF(0)
         FNRD= FNRD + TF(I)*IDPOT(I)*DF(IDPOT(I)-1)
  10    CONTINUE
C
      DO 30 J=1,IEX
       IF(IMAXF(J-1).EQ.IMAXF(J)) GOTO 30
        EXDN=EX(J)*DF(-1)
        DO 20 I=IMAXF(J-1)+1,IMAXF(J)
         FNRD= FNRD + TF(I)*(EXD(J)+EXDN*IDPOT(I))*DF(IDPOT(I))
  20    CONTINUE
  30  CONTINUE
C
      FNRDS=FNRD
      TSAVE=T
      DSAVE=D
C
      RETURN
      END
C******************************************************************************
      DOUBLEPRECISION FUNCTION FNRT(T,D)
C******************************************************************************
C
C    THIS FUNCTION CALCULATES THE 1ST TN
C    DERIVATIVE OF THE F'S NORMALIZED REAL PART.
C
      IMPLICIT REAL*8(A-H,O-Z)
      COMMON/EQU/G(58),IDPOT(58),ITPOT(58),IMAXF(-1:6),IEX,NT
      COMMON/CFUNC/TF(58),TSAV,DF(-1:13),DSAV
     *             ,EX(0:6),EXD(0:6),EXDD(0:6)
      COMMON /CEPS/ EPS
      COMMON/CNORM/TNORM,DNORM
      COMMON/CFAC/FACTOR
      SAVE TSAVE,DSAVE,FNRTS
C
      IF( dABS(T-TSAVE) .LT. EPS
     *    .AND. dABS((D-DSAVE)/D) .LT. EPS ) THEN
       FNRT=FNRTS
       RETURN
      END IF
C
      FNRT=0.D0
C
      IF( dABS( TSAV - T )     .GT. EPS ) CALL TFUNC(T)
      IF( dABS( DSAV - D )/D  .GT. EPS ) CALL DFUNC(D)
C
      DO 30 J=0,IEX
       IF(IMAXF(J-1).EQ.IMAXF(J)) GOTO 30
        H=0.D0
        DO 20 I=IMAXF(J-1)+1,IMAXF(J)
         H = H + (ITPOT(I)/FACTOR) *TF(I)*DF(IDPOT(I))
  20    CONTINUE
        FNRT = FNRT + H*EX(J)
  30  CONTINUE
C
      FNRT=FNRT*(T/TNORM)
C
      FNRTS=FNRT
      TSAVE=T
      DSAVE=D
C
      RETURN
      END
C******************************************************************************
      DOUBLEPRECISION FUNCTION FNRDD(T,D)
C******************************************************************************
C
C    THIS FUNCTION CALCULATES THE 2ND DN
C    DERIVATIVE OF THE F'S NORMALIZED REAL PART.
C
      IMPLICIT REAL*8(A-H,O-Z)
      COMMON/EQU/G(58),IDPOT(58),ITPOT(58),IMAXF(-1:6),IEX,NT
      COMMON/CFUNC/TF(58),TSAV,DF(-1:13),DSAV
     *             ,EX(0:6),EXD(0:6),EXDD(0:6)
      COMMON /CEPS/ EPS
      SAVE TSAVE,DSAVE,FNRDDS
C
C
      IF( dABS(T-TSAVE) .LT. EPS
     *    .AND. dABS((D-DSAVE)/D) .LT. EPS ) THEN
       FNRDD=FNRDDS
       RETURN
      END IF
C
      FNRDD=0.D0
C
      IF( dABS( TSAV - T )     .GT. EPS ) CALL TFUNC(T)
      IF( dABS( DSAV - D )/D  .GT. EPS ) CALL DFUNC(D)
C
        DO 10 I=1,IMAXF(0)
         FNRDD= FNRDD + TF(I)*IDPOT(I)*(IDPOT(I)-1)*DF(IDPOT(I)-2)
  10    CONTINUE
C
      DO 30 J=1,IEX
       IF(IMAXF(J-1).EQ.IMAXF(J)) GOTO 30
        EXDDN=2.D0*EXD(J)/DF(1)
        EXDN=EX(J)/DF(2)
        DO 20 I=IMAXF(J-1)+1,IMAXF(J)
         FNRDD= FNRDD + TF(I)*DF(IDPOT(I))
     *       *(EXDD(J) + EXDDN*IDPOT(I) + EXDN*IDPOT(I)*(IDPOT(I)-1))
  20    CONTINUE
  30  CONTINUE
C
      FNRDDS=FNRDD
      TSAVE=T
      DSAVE=D
C
      RETURN
      END
C******************************************************************************
      DOUBLEPRECISION FUNCTION FNRDT(T,D)
C******************************************************************************
C
C    THIS FUNCTION CALCULATES THE 2ND DN,TN-
C    DERIVATIVE OF THE F'S NORMALIZED REAL PART.
C
      IMPLICIT REAL*8(A-H,O-Z)
      COMMON/EQU/G(58),IDPOT(58),ITPOT(58),IMAXF(-1:6),IEX,NT
      COMMON/CFUNC/TF(58),TSAV,DF(-1:13),DSAV
     *             ,EX(0:6),EXD(0:6),EXDD(0:6)
      COMMON /CEPS/ EPS
      COMMON/CNORM/TNORM,DNORM
      COMMON/CFAC/FACTOR
      SAVE TSAVE,DSAVE,FNRDTS
C
      IF( dABS(T-TSAVE) .LT. EPS
     *    .AND. dABS((D-DSAVE)/D) .LT. EPS ) THEN
       FNRDT=FNRDTS
       RETURN
      END IF
C
      FNRDT=0.D0
C
      IF( dABS( TSAV - T )     .GT. EPS ) CALL TFUNC(T)
      IF( dABS( DSAV - D )/D  .GT. EPS ) CALL DFUNC(D)
C
        DO 10 I=1,IMAXF(0)
         FNRDT= FNRDT + (ITPOT(I)/FACTOR)*TF(I)*IDPOT(I)*DF(IDPOT(I)-1)
  10    CONTINUE
C
      DO 30 J=1,IEX
       IF(IMAXF(J-1).EQ.IMAXF(J)) GOTO 30
        EXDN=EX(J)*DF(-1)
        DO 20 I=IMAXF(J-1)+1,IMAXF(J)
        FNRDT=FNRDT+(ITPOT(I)/FACTOR)*TF(I)*(EXD(J)
     1        +EXDN*IDPOT(I))*DF(IDPOT(I))
  20    CONTINUE
  30  CONTINUE
C
      FNRDT=FNRDT*(T/TNORM)
C
      FNRDTS=FNRDT
      TSAVE=T
      DSAVE=D
C
      RETURN
      END
C****************************************************************************
      DOUBLEPRECISION FUNCTION FNRTT(T,D)
C*****************************************************************************
C
C    THIS FUNCTION CALCULATES THE 2ND TN-
C    DERIVATIVE OF THE F'S NORMALIZED REAL PART.
C
      IMPLICIT REAL*8(A-H,O-Z)
      COMMON/EQU/G(58),IDPOT(58),ITPOT(58),IMAXF(-1:6),IEX,NT
      COMMON/CFUNC/TF(58),TSAV,DF(-1:13),DSAV
     *             ,EX(0:6),EXD(0:6),EXDD(0:6)
      COMMON /CEPS/ EPS
      COMMON/CNORM/TNORM,DNORM
      COMMON/CFAC/FACTOR
      SAVE TSAVE,DSAVE,FNRTTS
C
      IF( dABS(T-TSAVE) .LT. EPS
     *    .AND. dABS((D-DSAVE)/D) .LT. EPS ) THEN
       FNRTT=FNRTTS
       RETURN
      END IF
C
      FNRTT=0.D0
C
      IF( dABS( TSAV - T )     .GT. EPS ) CALL TFUNC(T)
      IF( dABS( DSAV - D )/D  .GT. EPS ) CALL DFUNC(D)
C
      DO 30 J=0,IEX
       IF(IMAXF(J-1).EQ.IMAXF(J)) GOTO 30
        H=0.D0
        DO 20 I=IMAXF(J-1)+1,IMAXF(J)
         H=H+(ITPOT(I)/FACTOR)*((ITPOT(I)/FACTOR)-1)*TF(I)*DF(IDPOT(I))
  20    CONTINUE
        FNRTT = FNRTT + H*EX(J)
  30  CONTINUE
C
      FNRTT=FNRTT*(T/TNORM)**2
C
      FNRTTS=FNRTT
      TSAVE=T
      DSAVE=D
C
      RETURN
      END
C****************************************************************************
      BLOCKDATA SBSTCE
C*****************************************************************************
C
C
C   THIS SUBROUTINE SETS SUBSTANCE PARAMETERS FOR H2O
C
      IMPLICIT REAL*8(A-H,O-Z)
      CHARACTER*8 HSUB
C
      COMMON/CSUB1/HSUB
      COMMON/CSUB2/RG,XMOL,TC,PC,DC
      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB
      COMMON/CSUB4/FW,FC
C
      DATA HSUB /'WATER   '/
      DATA RG /0.46151805D-03/, XMOL /18.0152D0/
     *     TC /647.14D0/, DC /322.D0/, PC /22.064D0/
      DATA TTR /273.16D0/, PTR /.611646D-3/, DLTR /999.789D0/,
     *     DVTR /0.00485195D0/, TB /373.15D0/, PB/.101325D0/,
     *     DLB /958.364D0/, DVB /0.597209D0/
      DATA FW /1.D6/, FC /1.D3/
C
      END
C
C**********************************************************************************
      DOUBLEPRECISION FUNCTION DB(T,P)
C**********************************************************************************
C
C  THIS FUNCTION CALCULATES THE DENSITY FOR GIVEN P,T
C
      IMPLICIT REAL*8 (A-H,O-Z)
      COMMON/CEPS/EPSE
      COMMON/CSUB2/R,XMOL,TC,PC,DC
      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB
      COMMON/COUT/NIN,NOUT
C
      DB=0.D0
      IF( T .LE. 230.D0 .OR. P .LE. 0.D0 ) THEN
       WRITE(NOUT,1001) T,P
 1001  FORMAT('<DB> T=',F8.3,'or P=',D10.4,'out of range of validity')
       RETURN
      END IF
C
      IF(PMELT(T,2) .LT. P) THEN
       WRITE(NOUT,1002)T,P
       RETURN
      END IF
C
      IF( T .LT. TTR) THEN
       PMELT1=PMELT(T,1)
       PMELT2=PMELT(T,2)
       IF(PMELT1 .LE. P .AND. P .LE. PMELT2) THEN
        DEST= DLTR
        GOTO 100
       ELSE
        WRITE(NOUT,1002) T,P
 1002   FORMAT('<DB> T= ',F8.3,' and P= ',D10.4,' in solid phase')
        RETURN
       END IF
      END IF
C
      IF( T .LT. TC) THEN
       CALL VPEQ(T,PS)
C
       IF(dABS(P - PS)/PS .LT. 2.5D-4 ) THEN
        CALL SATT(T,DV,DEST,PS)
        IF( P .LT. PS ) DEST=DV
       ELSE
C
        IF ( P .LT. PS )  DEST = BDENS(T,P,2)
        IF ( P .GT. PS )  DEST = BDENS(T,P,1)
       END IF
C
      ELSE
       DEST= BDENS(T,P,2)
      END IF
C
C  EXACT CALCULATION OF DENSITY
C
 100  EPS = 1.D2*EPSE
      IF ( T .GT. 374.D0 ) EPS = 1.D4*EPSE
C
      DB= DENS(P,T,DEST,EPS)
C
      RETURN
      END
C***********************************************************************
      DOUBLEPRECISION FUNCTION PB(T,D)
C***********************************************************************
C
C     PRESSURE
C
      IMPLICIT REAL * 8 (A-H,O-Z)
C
      COMMON/CSUB2/R,XMOL,TC,PC,DC
      COMMON/CNORM/TNORM,DNORM
C
      PB=0.D0
      IF( T .LT. 1.D0 ) RETURN
      IF( D .LT. 1.D-10) RETURN
C
      DN=D/DNORM
C
      PB=D*R*T*(1.D0+DN*FNRD(T,D))
C
      RETURN
      END
C***********************************************************************
      DOUBLEPRECISION FUNCTION DPDTB(T,D)
C***********************************************************************
C
C      DP/DT
C
      IMPLICIT REAL * 8 (A-H,O-Z)
C
      COMMON/CSUB2/R,XMOL,TC,PC,DC
      COMMON/CNORM/TNORM,DNORM
C
      DPDTB=0.D0
      IF( T .LT. 1.D0 ) RETURN
      IF( D .LT. 1.D-10) RETURN
C
      TN=TNORM/T
      DN=D/DNORM
C
      DPDTB=D*R*(1.D0+DN*FNRD(T,D)-DN*TN*FNRDT(T,D))
C
      RETURN
      END
C***********************************************************************
      DOUBLEPRECISION FUNCTION DPDDB(T,D)
C***********************************************************************
C
C     DP/DD
C
      IMPLICIT REAL * 8 (A-H,O-Z)
C
      COMMON/CSUB2/R,XMOL,TC,PC,DC
      COMMON/CNORM/TNORM,DNORM
C
      DPDDB=0.D0
      IF( T .LT. 1.D0 ) RETURN
      IF( D .LT. 1.D-10) RETURN
C
      DN=D/DNORM
C
      DPDDB=R*T*(1.D0+2.D0*DN*FNRD(T,D)+DN**2*FNRDD(T,D))
C
      RETURN
      END
C***********************************************************************
      DOUBLEPRECISION FUNCTION CVB(T,D)
C***********************************************************************
C
C     ISOCHORIC HEAT CAPACITY
C
      IMPLICIT REAL * 8 (A-H,O-Z)
      COMMON/CSUB2/R,XMOL,TC,PC,DC
      COMMON/CSUB4/FW,FC
      COMMON/CNORM/TNORM,DNORM
C

      CVB=0.D0

      IF( T .LT. 1.D0 ) RETURN

      IF( D .LT. 1.D-10) RETURN

C

      TN=TNORM/T

C

      CVB=-FC*R*TN**2*(FNITT(T,D)+FNRTT(T,D))

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION CPB(T,D)

C***********************************************************************

C

C     ISOBARIC HEAT CAPACITY

C

      IMPLICIT REAL * 8 (A-H,O-Z)

C

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      COMMON/CSUB4/FW,FC

      COMMON/CNORM/TNORM,DNORM

C

      CPB=0.D0

      IF( T .LT. 1.D0 ) RETURN

      IF( D .LT. 1.D-10) RETURN

C

      TN=TNORM/T

      DN=D/DNORM

C

      CPB=CVB(T,D)+FC*R*(1.D0+DN*FNRD(T,D)-DN*TN*FNRDT(T,D))**2/

     1    (1.D0+2.D0*DN*FNRD(T,D)+DN**2*FNRDD(T,D))

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION WB(T,D)

C***********************************************************************

C

C     VELOCITY OF SOUND

C

      IMPLICIT REAL * 8 (A-H,O-Z)

C

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      COMMON/CSUB4/FW,FC

      COMMON/CNORM/TNORM,DNORM

C

      WB=0.D0

      IF( T .LT. 1.D0 ) RETURN

      IF( D .LT. 1.D-10) RETURN

C

      TN=TNORM/T

      DN=D/DNORM

C

      WB2=CPB(T,D)/CVB(T,D)*(1.D0+2.D0*DN*FNRD(T,D)+DN**2*FNRDD(T,D))

C

      IF(WB2 .GT. 0.D0) THEN

       WB=SQRT(WB2*R*FW*T)

      ELSE

       WB=0.D0

      END IF

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION FB(T,D)

C***********************************************************************

C

C     HELMHOLTZ FUNCTION

C

      IMPLICIT REAL * 8 (A-H,O-Z)

C

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      COMMON/CNORM/TNORM,DNORM

      COMMON/CSUB4/FW,FC

      COMMON /CNULLP/T0,D0,F0,H0,U0,S0,G0

C

      FB=0.D0

      IF( T .LT. 1.D0 ) RETURN

      IF( D .LT. 1.D-10) RETURN

C

      FB=R*FC*T * (FNR(T,D) + FNI(T,D))

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION HB(T,D)

C***********************************************************************

C

C     ENTHALPY

C

      IMPLICIT REAL * 8 (A-H,O-Z)

C

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      COMMON/CNORM/TNORM,DNORM

      COMMON/CSUB4/FW,FC

      COMMON /CNULLP/T0,D0,F0,H0,U0,S0,G0

C

      HB=0.D0

      IF( T .LT. 1.D0 ) RETURN

      IF( D .LT. 1.D-10) RETURN

C

      TN=TNORM/T

      DN=D/DNORM

C

      HB=R*FC*T* (1.D0 + DN*FNRD(T,D) + TN*( FNIT(T,D) + FNRT(T,D)))

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION SB(T,D)

C***********************************************************************

C

C     ENTROPY

C

      IMPLICIT REAL * 8 (A-H,O-Z)

C

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      COMMON/CNORM/TNORM,DNORM

      COMMON/CSUB4/FW,FC

      COMMON /CNULLP/T0,D0,F0,H0,U0,S0,G0

C

      SB=0.D0

      IF( T .LT. 1.D0 ) RETURN

      IF( D .LT. 1.D-10) RETURN

C

      TN=TNORM/T

C

      SB=R*FC * ( TN*(FNIT(T,D)+FNRT(T,D)) - (FNI(T,D)+FNR(T,D)) )

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION UB(T,D)

C***********************************************************************

C

C     INTERNAL ENERGY

C

      IMPLICIT REAL * 8 (A-H,O-Z)

C

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      COMMON/CNORM/TNORM,DNORM

      COMMON/CSUB4/FW,FC

      COMMON /CNULLP/T0,D0,F0,H0,U0,S0,G0

C

      UB=0.D0

      IF( T .LT. 1.D0 ) RETURN

      IF( D .LT. 1.D-10) RETURN

C

      TN=TNORM/T

C

      UB=R*FC*T * TN*(FNIT(T,D)+FNRT(T,D))

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION GB(T,D)

C***********************************************************************

C

C     GIBBS ENERGY

C

      IMPLICIT REAL * 8 (A-H,O-Z)

C

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      COMMON/CNORM/TNORM,DNORM

      COMMON/CSUB4/FW,FC

      COMMON /CNULLP/T0,D0,F0,H0,U0,S0,G0

C

      GB=0.D0

      IF( T .LT. 1.D0 ) RETURN

      IF( D .LT. 1.D-10) RETURN

C

      TN=TNORM/T

      DN=D/DNORM

C

      GB=R*FC*T * (1.D0+DN*FNRD(T,D)+FNI(T,D)+FNR(T,D))

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION ALPHAB(T1,DL1,DV1,T2,DL2,DV2)

C***********************************************************************

C

C     ALPHA BETWEEN T1 AND T2

C     (CF. OSBORNE ET AL., 1930)

C

      IMPLICIT REAL * 8 (A-H,O-Z)

      COMMON/CSUB4/FW,FC

      COMMON/CSUB2/RG,XMOL,TC,PC,DC

      COMMON/COUT/NIN,NOUT

C

      ALPHAB=0.D0

      IF( T1 .LT. 1.D0 ) RETURN

      IF( DL1 .LT. 1.D-10) RETURN

      IF( DV1 .LT. 1.D-10) RETURN

      IF( T2 .LT. 1.D0 ) RETURN

      IF( DL2 .LT. 1.D-10) RETURN

      IF( DV2 .LT. 1.D-10) RETURN

C

      IF( T1 .GT. TC .OR. T1 .GT. TC )THEN

       WRITE(NOUT,*)'<ALPHAB> T1 or T2 greater than TC . Alpha not cal'

     *,'culated !'

       RETURN

      END IF

C

      BETA1=FC*T1/DL1*DPSDTB(T1,DL1,DV1)

      BETA2=FC*T2/DL2*DPSDTB(T2,DL2,DV2)

C

      ALPHAB=(HB(T2,DL2)-BETA2)-(HB(T1,DL1)-BETA1)

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION DPSDTB(T,DL,DV)

C***********************************************************************

C

C     VAPOR PRESSURE CURVE DPS/DT

C

      IMPLICIT REAL * 8 (A-H,O-Z)

C

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      COMMON/CSUB4/FW,FC

      COMMON/CNORM/TNORM,DNORM

C

      DPSDTB=0.D0

      IF( T .LT. 1.D0 ) RETURN

      IF( DL .LT. 1.D-10) RETURN

      IF( DV .LT. 1.D-10) RETURN

C

      TN=TNORM/T

C

      DPSDTB=DL*DV/(DV-DL)*R*(LOG(DV/DL)+FNR(T,DV)-FNR(T,DL)

     *       -TN*(FNRT(T,DV)-FNRT(T,DL)))

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION BETASB(T,D)

C***********************************************************************

C

C     ISENTROPIC TEMPERATURE-PRESSURE

C     COEFFICIENT BETAS=(DT/DP)s

C

      IMPLICIT REAL * 8 (A-H,O-Z)

C

      COMMON/CSUB2/R,XMOL,TC,PC,DC

C

      BETASB=0.D0

      IF( T .LT. 1.D0 ) RETURN

      IF( D .LT. 1.D-10) RETURN

C

      BETASB=T/D**2*DPDTB(T,D)/(CPB(T,D)*DPDDB(T,D))

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION BB(T)

C***********************************************************************

C

C     2. VIRIALCOEFFICIENT B

C

      IMPLICIT REAL * 8 (A-H,O-Z)

      COMMON/CNORM/TNORM,DNORM

      DATA D /1.D-200/

C

      BB=FNRD(T,D)/DNORM

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION CB(T)

C***********************************************************************

C

C     3. VIRIALCOEFFICIENT C

C

      IMPLICIT REAL * 8 (A-H,O-Z)

      COMMON/CNORM/TNORM,DNORM

      DATA D /1.D-200/

C

      CB=FNRDD(T,D)/DNORM**2

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION RJTB(T,D)

C***********************************************************************

C

C     Joule Thomson Coefficient

C

      IMPLICIT REAL * 8 (A-H,O-Z)

C

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      COMMON/CSUB4/FW,FC

      COMMON/CNORM/TNORM,DNORM

C

      RJTB=0.D0

      IF( T .LT. 1.D0 ) RETURN

      IF( D .LT. 1.D-10) RETURN

C

      TN=TNORM/T

      DN=D/DNORM

C

      CVBN=-TN**2*(FNITT(T,D)+FNRTT(T,D))

      DPDDN=1.D0+2.D0*DN*FNRD(T,D)+DN**2*FNRDD(T,D)

C

      RJTB=-((D*R)**(-1))*(DN*FNRD(T,D)+DN**2*FNRDD(T,D)

     *        +DN*TN*FNRDT(T,D))/

     *     ((1.D0+DN*FNRD(T,D)-DN*TN*FNRDT(T,D))**2+CVBN*DPDDN)

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION DTB(T,D)

C***********************************************************************

C

C     Isothermal throttling coefficient

C

      IMPLICIT REAL * 8 (A-H,O-Z)

C

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      COMMON/CNORM/TNORM,DNORM

C

      DTB=0.D0

      IF( T .LT. 1.D0 ) RETURN

      IF( D .LT. 1.D-10) RETURN

C

      TN=TNORM/T

      DN=D/DNORM

C

      DPDDN=1.D0+2.D0*DN*FNRD(T,D)+DN**2*FNRDD(T,D)

      DPDTN=1.D0+DN*FNRD(T,D)-DN*TN*FNRDT(T,D)

C

      DTB=D**(-1)*(1.D0-DPDTN/DPDDN)

C

      RETURN

      END

C************************************************************************

      DOUBLEPRECISION FUNCTION DENS(P,T,DEST,EPSH)

C************************************************************************

C

C CALCULATING DENSITY FOR GIVEN T,P,DEST

C

      IMPLICIT REAL*8(A-H,O-Z)

      REAL*8 NULLF

      COMMON/CSUB2/RG,XMOL,TC,PC,DC

      EXTERNAL NULLF

C

      EPS=EPSH

      IF ((DEST.GT.(2.D0*DC)).AND.(T.LT.(TC-100.D0))) THEN

       DD=.003D0*DEST

      ELSE IF(DEST.GT.2.D0*DC) THEN

       DD=.01D0*DEST

      ELSE

       DD=0.05D0*DEST

      END IF

C

      D1=DEST

C

      IF(DEST .GT. DC) THEN

       D2=D1+DD

      ELSE

       D2=D1-DD

      END IF

C

      IF(EPS. LT. 1.D-8) EPS=1.D-8

C

      CALL WNULL3(D1,D2,NULLF,P,T,EPS,X,IX)

C

      IF( IX .LE. 0 ) THEN

        DENS=X

      ELSE

        DENS=0.D0

      END IF

 999  RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION NULLF(D,T,P)

C***********************************************************************

C

      IMPLICIT REAL*8 (A-H,O-Z)

C

      NULLF=PB(T,D)-P

  999 RETURN

      END

C******************************************************************

      SUBROUTINE SATT(T,DV,DL,P)

C******************************************************************

C

C     CALCULATING DV,DL,P FOR A GIVEN T

C

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON /CEPS/ EPSE

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      COMMON/COUT/NIN,NOUT

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PBOIL,DLB,DVB

      SAVE TSAV,DLSAV,DVSAV,PSAV

C

      IF( T .GT. TC ) GOTO 500

      IF( T .LT. TTR ) GOTO 500

C

      EPS = 1.D2*EPSE

      IF ( T .GT. 374.D0 ) EPS = 1.D4*EPSE

      EPSD=.33D0*EPS

C

      IF( dABS(TC - T) .LT. EPSE ) THEN

        DL=DC

        DV=DC

        P=PC

        RETURN

      END IF

C

      IF( dABS(TSAV-T) .LT. EPSE ) THEN

        DL=DLSAV

        DV=DVSAV

        P=PSAV

        RETURN

      END IF

C

C     INITIAL VALUES

C

      CALL DVEQ(T,DV)

      IF(DV .LT. 1.D-20 ) GOTO 500

      CALL DLEQ(T,DL)

      CALL VPEQ(T,P)

C

C  *** MAXWELL-LOOP ***

C

      DO 31 I=1,10

C

        DL=DENS(P,T,DL,EPSD)

        IF(DL.LT.1.D-20) GOTO 500

        FNRL=FNR(T,DL)

C

        DV=DENS(P,T,DV,EPSD)

        IF(DV.LT.1.D-20) GOTO 500

        FNRV=FNR(T,DV)

C

        IF( dABS((DL-DV)/DV) .LE. EPSD) GOTO 500

C

        IF( T .GT. 647.139D0) GOTO 999

        P0=P

        P=(FNRL-FNRV+LOG(DL/DV))*R*T/(1.D0/DV-1.D0/DL)

C

        IF(dABS((P-P0)/P) .LT. EPS) GOTO 999

C

   31 CONTINUE

C

      WRITE(NOUT,*)'<SATT> Did not converge at T=',T,'K'

C

 500  CONTINUE

      DL=0.D0

      DV=0.D0

      P=0.D0

      IF( T .LT. TTR )

     *   WRITE(NOUT,*)'<SATT> T=',T,'K is below the triple-point'

      IF(T .GT. TC)WRITE(NOUT,*)'<SATT> T=',T,'K is supercritical'

  999 CONTINUE

C

      TSAV=T

      DLSAV=DL

      DVSAV=DV

      PSAV=P

C

      RETURN

      END

C******************************************************************

      SUBROUTINE SATP(T,DV,DL,P)

C******************************************************************

C

C     CALCULATING T,DV,DL FOR A GIVEN P

C

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON /CEPS/ EPSE

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PBOIL,DLB,DVB

      COMMON/COUT/NIN,NOUT

      SAVE TSAV,DLSAV,DVSAV,PSAV

C

      IF( P .GT. PC ) GOTO 500

      IF( P .LT. PTR ) GOTO 500

C

      EPS = 1.D2*EPSE

      IF ( P .GT. 374.D0 ) EPS = 1.D4*EPSE

      EPSD=.33D0*EPS

C

      IF( dABS(PC - P)/P .LT. EPSE ) THEN

        DL=DC

        DV=DC

        T=TC

        RETURN

      END IF

C

      IF( dABS(PSAV-P) .LT. EPSE ) THEN

        DL=DLSAV

        DV=DVSAV

        T=TSAV

        RETURN

      END IF

C

C     INITIAL VALUES

C

      T = TSEQ(P)

      IF(T .LT. 1.D-20 .OR. T .GT. TC) GOTO 500

      CALL DVEQ(T,DV)

      CALL DLEQ(T,DL)

      CALL DPDTEQ(T,DPDT)

C

C  *** MAXWELL-LOOP ***

C

      DO 31 I=1,10

C

        DL=DENS(P,T,DL,EPSD)

        IF(DL.LT.1.D-20) GOTO 500

        FNRL=FNR(T,DL)

C

        DV=DENS(P,T,DV,EPSD)

        IF(DV.LT.1.D-20) GOTO 500

        FNRV=FNR(T,DV)

C

        IF( dABS((DL-DV)/DV) .LE. EPSD) GOTO 500

C

        IF( T .GT. 647.135D0) GOTO 999

        T0=T

        DP=P - (FNRL-FNRV+dLOG(DL/DV))*R*T/(1.D0/DV-1.D0/DL)

        T=T0 + DP/DPDT

C

        IF(dABS(T-T0) .LT. EPS) GOTO 999

C

   31 CONTINUE

C

      WRITE(NOUT,*)'<SATP> Did not converge at p=',P,'MPa'

C

 500  CONTINUE

      DL=0.D0

      DV=0.D0

      T=0.D0

      IF( P .LT. PTR )

     *   WRITE(NOUT,*)'<SATP> p=',P,'MPa is below the triple-point'

      IF(P .GT. PC)WRITE(NOUT,*)'<SATP> p=',P,'MPa is supercritical'

  999 CONTINUE

C

      TSAV=T

      DLSAV=DL

      DVSAV=DV

      PSAV=P

C

      RETURN

      END

C*******************************************************************

      SUBROUTINE WNULL3(XA,XB,F,P,T,EPS,X,IX)

C*******************************************************************

C

C               F(X,T,P)=0

C

C*************************************************************************

C

      IMPLICIT REAL*8(A-H,O-Z)

C

      X1=XA

      F1=F(X1,T,P)

      X3=XB

      F3=F(X3,T,P)

      IX=0

C

      DO 100 I=1,40

C

C   REGULA FALSI

C

      IF( F1 .NE. F3 ) THEN

       X=X1+(X3-X1)*F1/(F1-F3)

      ELSE

       GOTO 10

      END IF

C

      IF(X .LT. 0.D0) X=(X1+X3)/2.D0

C

      IF(ABS(X) .LT. 1.D-8) THEN

        IF(ABS(X-X1).LT.EPS) RETURN

      ELSE

        IF(ABS((X-X1)/X).LT.EPS) RETURN

      END IF

C

      F2=F(X,T,P)

C

      X2=X1-(X1-X3)/2.D0

C

      IF(F2*F1 .LE.F2*F3) THEN

        X3=X1

        F3=F1

      END IF

      X1=X

      F1=F2

C

      IF((X2-X3)*(X2-X1) .GE. 0.D0) GOTO 100

      X=(X1+X3)/2.D0

      F2=F(X,T,P)

C

      IF(F2*F1 .LE. F2*F3) THEN

        X3=X1

        F3=F1

      END IF

C

      X1=X

      F1=F2

C

 100  CONTINUE

C

  10  IX=1

 999  RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION BDENS(T,P,IREG)

C***********************************************************************

C

C     ESTIMATING DENSITY FOR GIVEN T AND P

C

C             IREG- PARAMETER FOR THE REGION

C                   1: LIQUID

C                   2: GASEOUS

C                   0: NOT KNOWN

C

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON/CSUB2/RG,XMOL,TC,PC,DC

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PBOIL,DLB,DVB

C

      IREGH=IREG

      IF(IREG .EQ. 0 .OR. T .GT. TC) THEN

C

       IREGH=1

       IF(T .LT. TC .AND. T .GE. TTR ) THEN

        CALL VPEQ(T,PT)

        PS=PT

       ELSE

        PT=1.D10

       END IF

       IF(T .LT. TTR) PT=PTR

       IF(P .LT. PT) IREGH=2

      END IF

C

      IF(IREGH .EQ. 1) THEN

       IF(T .LT. TTR) THEN

        BDENS=DLTR

        RETURN

       END IF

C

       IF(T .LT. .7*TC ) THEN

        CALL DLEQ(T,DL)

        BDENS=DL+0.243D0*(P-PS)

       ELSE

        BDENS=DSOAVE(T,P,IREGH)+200.D0

        IF(T .LT. TC) THEN

         CALL DLEQ(T,DL)

         IF(DL .GT. BDENS) BDENS=DL

        END IF

       END IF

      ELSE

       BDENS=DSOAVE(T,P,IREGH)

       IF(BDENS .GT. 222.0431D0) BDENS=BDENS+200.D0

       IF(T .LT. TC) THEN

        CALL DVEQ(T,DV)

        IF(DV .LT. BDENS) BDENS=DV

       END IF

      END IF

C

      IF( P .GT. 1000.D0 .OR. BDENS .LT. 0.D0 ) THEN

       DMAX= 1400.D0 + (1000.D0/dLOG10(24000.D0))*(dLOG10(P) - 3.D0 )

       IF( DMAX .LT. BDENS .OR. BDENS .LT. 0.D0) BDENS = DMAX

      END IF

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION DSOAVE(T,P,IREG)

C***********************************************************************

C

C     ESTIMATING DENSITY WITH THE SOAVE EQUATION

C

      IMPLICIT REAL*8 (A-H,O-Z)

      DIMENSION Y(3)

      COMMON/CSUB2/ RG,XMOL,TC,PC,DC

C

      DSOAVE=0.D0

C

C

      IF(P.LT.0.D0.OR.T.LT.0.D0) THEN

      WRITE(1,1000)

 1000 FORMAT('<BDENS> ERROR ON P,T ')

      GOTO 999

      ENDIF

C

      PI= dACOS(0.D0)*2.D0

      ATC= .42748025D0*(RG*TC)**2/PC

      B= .08664035D0*RG*TC/PC

C

      TSOAVE= .7D0*TC

      CALL VPEQ(TSOAVE,PSOAVE)

      PRSOAV= PSOAVE/PC

C

      OMEGA= -LOG10(PRSOAV) -1.D0

C

      EM= .47979D0 +1.576D0*OMEGA -.1925D0*OMEGA**2 +.025D0*OMEGA**3

      ALPHA=(1.D0+ EM*(1.D0-(T/TC)**.5D0))**2

C

      A= ALPHA*ATC

C

C  Y**3 + BETA*Y**2 + GAMMA*Y + DELTA = 0

C

      BETA= -(RG*T)/P

      GAMMA= -(B**2)-(B*RG*T)/P+A/P

      DELTA= -(A*B)/P

C

      Q= (BETA**3)/27.D0-(BETA*GAMMA)/6.D0+DELTA/2.D0

      PE= (GAMMA-(BETA**2)/3.D0)/3.D0

      DISK= (Q**2)+(PE**3)

C

      IF(dABS(PE).LT.1.D-20) THEN

       Y(1)= ((dABS(2.D0*Q))**(1.D0/3.D0))

       IF(Q.GT.0.D0) Y(1)=-Y(1)

       Y(2)= 0.D0

       Y(3)= 0.D0

       KK=1

       GOTO 500

      ENDIF

C

      IF(DISK.LT.0.D0) THEN

       R= ((ABS(PE))**.5D0)

      IF(Q.LT.0.D0) R=-R

       PHI= dACOS(Q/(R**3))

       Y(1)= -(2.D0*R)*DCOS(PHI/3.D0)

       Y(2)=  (2.D0*R)*DCOS((PI/3.D0)-(PHI/3.D0))

       Y(3)=  (2.D0*R)*DCOS((PI/3.D0)+(PHI/3.D0))

       KK= 3

      ELSE

C

       DISKN=(DISK**.5D0)

       SUM1= -Q+DISKN

        IF(SUM1.LT.0.D0) THEN

         U=-((ABS(SUM1))**(1.D0/3.D0))

        ELSE

         U= (SUM1**(1.D0/3.D0))

        ENDIF

       SUM2= -Q-DISKN

        IF(SUM2.LT.0.D0)THEN

         V=-((ABS(SUM2))**(1.D0/3.D0))

        ELSE

         V= (SUM2**(1.D0/3.D0))

        ENDIF

       Y(1)= U+V

       Y(2)= 0.D0

       Y(3)= 0.D0

       KK=1

      ENDIF

  500 CONTINUE

C

      DMAX=0.D0

      DMIN=1.D100

C

      DO 50 I=1,KK

       D=1.D0/(Y(I)-BETA/3.D0)

       IF(D.GT.DMAX) DMAX=D

       IF(D.LT.DMIN) DMIN=D

   50 CONTINUE

C

      DSOAVE=DMIN

      IREGH=IREG

C

      IF(T .LT. TC) THEN

       IF(IREG .EQ. 0) THEN

        CALL VPEQ(T,PS)

        IREGH=2

        IF(P .GT. PS) IREGH=1

       END IF

C

       IF(IREGH .EQ. 1) THEN

        DSOAVE=DMAX

       ELSE

        DSOAVE=DMIN

       END IF

C

      END IF

C

  999 CONTINUE

      RETURN

      END

C**********************************************************************************

      DOUBLEPRECISION FUNCTION TSEQ(P)

C**********************************************************************************

C

C     CALCULATING TS FOR A GIVEN P FROM SAT-EQUATION

C

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON /CEPS/ EPS

      COMMON/CSUB2/RG,XMOL,TC,PC,DC

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TBB,PBB,DLBB,DVBB

      COMMON/COUT/NIN,NOUT

      EXTERNAL RNUFU

C

      TSEQ=0.D0

C

      IF( ABS(P-PC) .LT. 1.D-6 ) THEN

       TSEQ=TC

       RETURN

      END IF

C

      IF(P.GT.PC) THEN

       WRITE(NOUT,*)'<TSEQ> P IS GREATER THAN PC'

       RETURN

      ENDIF

C

      IF(P.LT.PTR) THEN

       WRITE(NOUT,*)'<TSEQ> P IS LESS THAN PTR'

       RETURN

      ENDIF

C

      XKONST= dLOG(PC/PTR)/(1.D0/TTR-1.D0/TC)

      T1=(1.D0/TC-1.D0/XKONST*dLOG(P/PC))**(-1)

      T2= T1-2.D0

C

      CALL WNULL3(T1,T2,RNUFU,P,DUMMY,EPS,TS,IX)

C

      IF( IX .LE. 0 ) THEN

        TSEQ=TS

      ELSE

        WRITE(NOUT,*)'<TSEQ> did not converge at P =',P

      END IF

C

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION RNUFU(T,DUMMY,P)

C***********************************************************************

      IMPLICIT REAL*8 (A-H,O-Z)

      CALL VPEQL(T,PS)

      RNUFU= PS-P

      RETURN

      END

C***********************************************************************

      SUBROUTINE VPEQL(T,P)

C***********************************************************************

C

      IMPLICIT REAL*8 (A-H,O-Z)

      COMMON/CSUB2/R,XMOL,TC,PC,DC

      SAVE DPDT

      DATA DPDT/0.D0/

C

      IF(T.GT.TC) THEN

       IF( DPDT .LT. 1.D-10 ) CALL DPDTEQ(TC,DPDT)

       P=PC+DPDT*(T-TC)

      ELSE

       CALL VPEQ(T,P)

      END IF

C

      RETURN

      END

C***********************************************************************

      SUBROUTINE SLEQ(T,SL)

C***********************************************************************

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON/CSUB4/FW,FC

      COMMON/CSUB2/RG,XMOL,TC,PC,DC

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB

      COMMON/COUT/NIN,NOUT

C

C  CALCULATION OF SATURATED LIQUID ENTROPY WITH HELP OF PHI

C

      IF( T .GT. TC )THEN

       WRITE(NOUT,*)

     * '<SLEQ> T > TC. S.L.Entropy will not be calculated !'

       RETURN

      END IF

C

      IF( T .LT. TTR)THEN

       WRITE(NOUT,*)

     * '<SLEQ> T <TTR. S.L.Entropy will not be calculated !'

       RETURN

      END IF

C

      CALL DLEQ(T,DL)

C

      IF( DL .GT. 0.D0  ) THEN

       CALL DPDTEQ(T,DPDT)

       CALL PHIEQ(T,PHI)

       SL= PHI + FC/DL*DPDT

      ELSE

       SL= 0.D0

      END IF

C

      END

C***********************************************************************

      SUBROUTINE SVEQ(T,SV)

C***********************************************************************

      IMPLICIT REAL*8 (A-H,O-Z)

      COMMON/CSUB4/FW,FC

      COMMON/CSUB2/RG,XMOL,TC,PC,DC

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB

      COMMON/COUT/NIN,NOUT

C

C  CALCULATION OF SATURATED VAPOR ENTROPY WITH HELP OF PHI

C

      IF( T .GT. TC )THEN

       WRITE(NOUT,*)'<SVEQ> T > TC. S.V.Entropy',

     +              ' will not be calculated !'

       RETURN

      END IF

C

      IF( T .LT. TTR)THEN

       WRITE(NOUT,*)'<SVEQ> T <TTR. S.V.Entropy',

     +              ' will not be calculated !'

       RETURN

      END IF

C

      CALL DVEQ(T,DV)

C

      IF( DV .GT. 0.D0) THEN

       CALL PHIEQ(T,PHI)

       CALL DPDTEQ(T,DPDT)

       SV= PHI + FC/DV*DPDT

      ELSE

       SV=0.D0

      END IF

C

      END

C***********************************************************************

      SUBROUTINE HLEQ(T,HL)

C***********************************************************************

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON/CSUB4/FW,FC

      COMMON/CSUB2/RG,XMOL,TC,PC,DC

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB

      COMMON/COUT/NIN,NOUT

C

C  CALCULATION OF SATURATED LIQUID ENTHALPY WITH HELP OF ALP

C

      IF( T .GT. TC )THEN

       WRITE(NOUT,*)'<HLEQ> T > TC. S.L.Enthalpy',

     +              ' will not be calculated !'

       RETURN

      END IF

C

      IF( T .LT. TTR)THEN

       WRITE(NOUT,*)'<HLEQ> T <TTR. S.L.Enthalpy',

     +              ' will not be calculated !'

       RETURN

      END IF

C

      CALL DLEQ(T,DL)

C

      IF( DL .GT. 0.D0) THEN

       CALL ALPEQ(T,ALP)

       CALL DPDTEQ(T,DPDT)

       HL= ALP+ FC* T/DL*DPDT

      ELSE

       HL=0.D0

      END IF

C

      END

C***********************************************************************

      SUBROUTINE HVEQ(T,HV)

C***********************************************************************

      IMPLICIT REAL*8 (A-H,O-Z)

      COMMON/CSUB4/FW,FC

      COMMON/CSUB2/RG,XMOL,TC,PC,DC

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB

      COMMON/COUT/NIN,NOUT

C

C  CALCULATION OF SATURATED VAPOR ENTHALPY WITH HELP OF ALPHA

C

      IF( T .GT. TC )THEN

       WRITE(NOUT,*)'<HVEQ> T > TC. S.V.Enthalpy',

     +              ' will not be calculated !'

       RETURN

      END IF

C

      IF( T .LT. TTR)THEN

       WRITE(NOUT,*)'<HVEQ> T <TTR. S.V.Enthalpy',

     +              ' will not be calculated !'

       RETURN

      END IF

C

      CALL DVEQ(T,DV)

C

      IF( DV .GT. 0.D0) THEN

       CALL ALPEQ(T,ALP)

       CALL DPDTEQ(T,DPDT)

       HV= ALP + FC*T/DV*DPDT

      ELSE

       HV=0.D0

      END IF

C

      END

C***********************************************************************

      SUBROUTINE VPEQ(T,P)

C***********************************************************************

      IMPLICIT REAL*8(A-H,O-Z)

C

C     VAPOUR PRESSURE

C

      COMMON /CVPEQ/G(6),TPOT(6),TC,PC,N

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB

      COMMON/COUT/NIN,NOUT

C

      TAU=1.D0-T/TC

      P=0.D0

C

      IF(T .LT. TTR)THEN

      WRITE(NOUT,*)'<VPEQ> T= ',T,'<TTR .Vapour pressure will not be',

     *' calculated !'

      RETURN

      END IF

C

      IF(TAU .LT. 0.D0) THEN

      WRITE(NOUT,*)'<VPEQ> T= ',T,'>TC. Vapour pressure will not be',

     *' calculated !'

      RETURN

      END IF



C

      IF(TAU .LT. 1.D-8) THEN

       P=PC

       RETURN

      ENDIF

C

      DO 10 I=1,N

  10   P=P+G(I)*TAU**TPOT(I)

C

      P=PC*EXP(P*TC/T)

C

      RETURN

      END

C***********************************************************************

      BLOCKDATA BLVPEQ

C***********************************************************************

      IMPLICIT REAL*8(A-H,O-Z)

C

C     VAPOUR PRESSURE

C

      COMMON /CVPEQ/G(6),TPOT(6),TC,PC,N

C

      DATA TC/647.14D0/, PC/22.064D0/,N/6/

     *      TPOT/1.D0,1.5D0,3.D0,3.5D0,4.D0,7.5D0/,

     *      G/-.785823D01, .183991D01,-.117811D02,

     *         .226705D02,-.159393D02, .177516D01/

      END

C

C***********************************************************************

      SUBROUTINE DLEQ(T,DL)

C***********************************************************************

C

C     SATURATED LIQUID DENSITY

C

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB

      COMMON/COUT/NIN,NOUT

      DIMENSION G(6),TPOT(6)

C

C     SATURATED LIQUID DENSITY

C

      DATA TC/647.14D0/,  DC/322.000D0/, N/6/

     *     TPOT/ .33333333333333D00, .66666666666667D00,

     *           .16666666666667D01, .53333333333333D01,

     *           .14333333333333D02, .36666666666667D02/,

     *     G   / .199206D01, .110123D01,-.512506D00,

     *          -.175263D01,-.454485D02,-.675615D06/

C

      TAU=1.D0-T/TC

      DL=0.D0

C

      IF(T .LT. TTR)THEN

      WRITE(NOUT,*)'<DLEQ> T= ',T,'<TTR. Density will not be',

     *' calculated !'

      RETURN

      END IF

C

      IF (TAU.LT.0.D0) THEN

      WRITE(NOUT,*)'<DLEQ> T= ',T,'>TC. Density will not be',

     *' calculated !'

      RETURN

      END IF

C

      IF (TAU .LT. 1.D-8) THEN

       DL=DC

       RETURN

      ENDIF

C

      DO 10 I=1,N

  10   DL=DL+G(I)*TAU**TPOT(I)

C

      DL=(DL+1.D0)*DC

C

      RETURN

      END

C***********************************************************************

      SUBROUTINE DVEQ(T,DV)

C***********************************************************************

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB

      COMMON/COUT/NIN,NOUT

      DIMENSION G(6),TPOT(6)

C

C     SATURATED VAPOUR DENSITY

C

      DATA TC/647.14D0/,  DC/322.000D0/, N/6/

     *    TPOT/ .33333333333333D00, .66666666666667D00,

     *          .13333333333333D01, .30000000000000D01,

     *          .61666666666667D01, .11833333333333D02/

     *    G  / -.202957D01,-.268781D01,-.538107D01,

     *         -.173151D02,-.446384D02,-.643486D02/

C

      TAU=1.D0-T/TC

      DV=0.D0

C

      IF(T .LT. TTR)THEN

      WRITE(NOUT,*)'<DVEQ> T= ',T,'<TTR. Density will not be',

     *' calculated !'

      RETURN

      END IF

C

      IF (TAU .LT. 0.D0) THEN

      WRITE(NOUT,*)'<DVEQ> T= ',T,'>TC. Density will not be',

     *' calculated !'

      RETURN

      END IF

C

      IF(TAU .LT. 1.D-8) THEN

       DV=DC

       RETURN

      ENDIF

C

      DO 10 I=1,N

  10  DV=DV+G(I)*TAU**TPOT(I)

C

      DV=DC*dEXP(DV)

C

      RETURN

      END

C***********************************************************************

      SUBROUTINE DPDTEQ(T,DPDT)

C***********************************************************************

      IMPLICIT REAL*8 (A-H,O-Z)

      COMMON /CVPEQ/G(6),TPOT(6),TC,PC,N

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB

      COMMON/COUT/NIN,NOUT

C

C  FIRST DERIVATIVE OF VAPORPRESSURE P WITH RESP. TO TEMPERATURE T

C

      TAU= 1.D0- T/TC

      DPDT=0.D0

      P=0.D0

C

      IF(T .LT. TTR)THEN

      WRITE(NOUT,*)'<DPDTEQ> T= ',T,'<TTR. Derivative will not be',

     *' calculated !'

      RETURN

      END IF

C

      IF (TAU .LT. 0.D0) THEN

      WRITE(NOUT,*)'<DPDTEQ> T= ',T,'>TC. Derivative will not be',

     *' calculated !'

      RETURN

      END IF

C

      IF (TAU .LE. 1.D-8) THEN

       IF(dABS(TPOT(1)-1.D0).LT. 1.D-8) DPDT= -PC/TC*G(1)

       RETURN

      ENDIF

C

      DO 10 I=1,N

       DPDT= DPDT + G(I)*TPOT(I)*TAU**(TPOT(I)-1.D0)

       P=P + G(I)*TAU**TPOT(I)

   10 CONTINUE

C

      P=PC*dEXP(P*TC/T)

      DPDT= (DPDT+dLOG(P/PC))*(-P/T)

C

      RETURN

      END

C***********************************************************************

      SUBROUTINE ALPEQ(T,ALP)

C***********************************************************************

      IMPLICIT REAL*8 (A-H,O-Z)

      COMMON /CALPEQ/G(5),TPOT(5),TC,A0,DA0,DPHI0,N

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB

      COMMON/COUT/NIN,NOUT

C

C  ALPHA VALUE USED TO CALCULATE SATURATED LIQUID ENTHALPY AND

C  SATURATED VAPOR ENTHALPY

C

      TETA= T/TC

      ALP=0.D0

C

      IF(T .LT. TTR)THEN

      WRITE(NOUT,*)'<ALPHA> T= ',T,'<TTR. Alpha will not be',

     *' calculated !'

      RETURN

      END IF

C

      IF( TETA .GT. 1.D0) THEN

      WRITE(NOUT,*)'<ALPHA> T= ',T,'>TC. Alpha will not be',

     *' calculated !'

      RETURN

      END IF

C

C

      ALP= DA0

C

      DO 10 I=1,N

       ALP= ALP + G(I)*TETA**TPOT(I)

   10 CONTINUE

C

      ALP=ALP*A0

C

      RETURN

      END

C***********************************************************************

      BLOCKDATA BALPEQ

C***********************************************************************

      IMPLICIT REAL*8 (A-H,O-Z)

      COMMON /CALPEQ/G(5),TPOT(5),TC,A0,DA0,DPHI0,N

C

C  ALPHA VALUE USED TO CALCULATE SATURATED LIQUID ENTHALPY AND

C  SATURATED VAPOR ENTHALPY

C

C

      DATA  TC/647.14 D0/,A0/1.D0/,DA0/ -1135.481615639 D0/,

     *      DPHI0/2318.9142D0/,N/5/,

     *      TPOT/ -19.D0,1.D0,4.5D0,5.D0,54.5D0/

     *         G/ - .571756D-7 , .268981D4, .129889D3,

     *            - .137181D3  , .968874D0/

C

      END

C***********************************************************************

      SUBROUTINE PHIEQ(T,PHI)

C***********************************************************************

      IMPLICIT REAL*8 (A-H,O-Z)

      COMMON /CALPEQ/G(5),TPOT(5),TC,A0,DA0,DPHI0,N

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB

      COMMON/COUT/NIN,NOUT

C

C  PHI VALUE USED TO CALCULATE SATURATED LIQUID ENTROPY AND

C  SATURATED VAPOR ENTROPY

C

C  REFERENCE VALUE:

C

      PHI0=A0/TC

C

      TETA= T/TC

      PHI= 0.D0

C

      IF(T .LT. TTR)THEN

      WRITE(NOUT,*)'<PHI> T= ',T,'<TTR. Phi will not be',

     *' calculated !'

      RETURN

      END IF

C

      IF( TETA .GT. 1.D0) THEN

      WRITE(NOUT,*)'<PHI> T= ',T,'>TC. Phi will not be',

     *' calculated !'

      RETURN

      END IF

C

      DO 10 I=1,N

       TPT=TPOT(I)

       IF(ABS(TPT-1.D0) .LT. 1.D-8) THEN

        PHI= PHI + G(I)*LOG(TETA)

       ELSE

        PHI= PHI + G(I)*TPT/(TPT-1.D0)*TETA**(TPT-1.D0)

       END IF

   10 CONTINUE

C

      PHI= (PHI + DPHI0)*PHI0

C

      RETURN

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION PMELT(T,IST)

C***********************************************************************

C

C     MELTING PRESSURE FOR GIVEN TEMPERATURE

C

C     IST .EQ. 1 => lower pressure  T<273.16

C     IST .NE. 1 => higher pressure T<273.16

C

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON /CMELTEQ/G(7),TP(7),TT(7),PT(7),IG(7)

      COMMON/COUT/NIN,NOUT

C

      IF( T .LT. TT(3) ) THEN

       PMELT=1.D-10

       WRITE(NOUT,*)'<PMELT> T= ',T,' <',TT(3),'. No calculation',

     * ' possible !'

       RETURN

      END IF

C

      IF( IST .EQ. 1 .AND. T .LE. TT(1)) THEN

       I=1

       GOTO 20

      END IF

C

      DO 10 J=3,7

       I=10-J

       IF( IG(I) .EQ. 0 ) GOTO 10

       IF( T .GE. TT(I) ) GOTO 20

   10 CONTINUE

C

   20 CONTINUE

C

      IF( T .EQ. TT(I)) THEN

       PMELT=PT(I)

       RETURN

      END IF

C

      PI=G(I)*(1.D0 - (T/TT(I))**TP(I))

C

      IF( IG(I) .EQ. 1 ) THEN

       PMELT=PT(I)*(PI+1.D0)

      ELSE

       PMELT=PT(I)*EXP(PI)

      END IF

C

      RETURN

      END

C**********************************************************************************

      SUBROUTINE TMELT(TS,P)

C**********************************************************************************

C

C     MELTING TEMPERATURE FOR GIVEN PRESSURE

C

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON /CMELTEQ/G(7),TP(7),TT(7),PT(7),IG(7)

      COMMON/CSUB3/TTR,PTR,DLTR,DVTR,TB,PB,DLB,DVB

      COMMON/COUT/NIN,NOUT

C

      IF(P .LT. PTR)THEN

      WRITE(NOUT,*)'<TMELT> P= ',P,'<PTR. TS will not be',

     *' calculated !'

      RETURN

      END IF

C

      DO 10 J=2,7

       IF( IG(J) .EQ. 0 ) GOTO 10

       IF( P .LT. PT(J) ) THEN

        I=J-1

        IF( IG(I) .EQ. 0 ) I=J-2

        GOTO 20

       END IF

       I=J

   10 CONTINUE

C

   20 CONTINUE

C

      IF( P .EQ. PT(I)) THEN

       TS=TT(I)

       RETURN

      END IF

C

      IF( IG(I) .EQ. 1 ) THEN

       PI=P/PT(I)-1.D0

      ELSE

       PI=dLOG(P/PT(I))

      END IF

C

      TS=TT(I)*(1.D0 - PI/G(I))**(1.D0/TP(I))

C

  999 RETURN

      END

C***********************************************************************

      BLOCKDATA BLMELT

C***********************************************************************

C

C     MELTING PRESSURE

C

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON /CMELTEQ/G(7),TP(7),TT(7),PT(7),IG(7)

      DATA

C         ICE-I       ICE-III         ICE-V     ICE-VI       ICE-VII

     * G/6.04D5,0.D0,-.295123D0,0.D0,-1.18685D0,-1.07476D0,-.814894D0/

     *TP/ 10.D0,0.D0,     60.D0,0.D0,      8.D0,     4.6D0,    1.92D0/

     *TT/273.16D0,0.,  251.16D0,0.D0,  256.16D0,  273.31D0,    355.D0/

     *PT/.611659D-3,0., 209.9D0,0.D0,   350.1D0,   632.4D0,   2216.D0/

     *IG/       1, 0,         1,   0,         1,         1,         2/

C

      END

C***********************************************************************

      DOUBLEPRECISION FUNCTION PSUBL(T)

C***********************************************************************

C

C     SUBLIMATION-PRESSURE:

C

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON/COUT/NIN,NOUT

      DIMENSION G(3),TP(3)

      DATA  TT/273.16D0/, PT/.611659D-3/

     * G/ 0.192933313D+02,-0.382215108D+01, 0.165283160D+01/

     *TP/-1.D0,3.D0,5.D0/

C

      IF( T .LE. 0.D0 )THEN

       WRITE(NOUT,*)'<PSUBL> T < O . Psubl will not be calculated !'

       RETURN

       END IF

C

      IF ( T .GT. TT ) THEN

       WRITE(NOUT,*)'<PSUBL> T= ',T,' > TTR . Psubl will not be'

     *,' calculated !'

       RETURN

       END IF

C

      IF( T .EQ. TT) THEN

       PSUBL=PT

       RETURN

      END IF

C

      PI=0.D0

C

      DO 10 I=1,3

   10   PI=PI + G(I)*(1.D0 - (T/TT)**TP(I))

C

      PSUBL=PT*dEXP(PI)

C

      RETURN

      END

**********************************************************************

C***************************************************************************

           DOUBLEPRECISION FUNCTION FNI(T,D)

C***************************************************************************

C

C THIS FUNCTION CALCULATES F'S NORMALIZED IDEAL PART

C FOR EINSTEIN-TYPE CP0'S.

C

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON /CFNI/B2,B(7),TPID(7),NPOL,N

      COMMON/CNORM/TNORM,DNORM

      COMMON /CEPS/ EPS

      SAVE TSAVE,DSAVE,FNIS

C

      IF( dABS(T-TSAVE) .LT. EPS ) THEN

       FNI=dLOG(D/DSAVE) + FNIS

       RETURN

      END IF

C

      DN= D/DNORM

      TN= TNORM/T

C

      FNI= dLOG(DN) + B2*dLOG(TN) + B(1) + B(2)*TN

C

      DO 20 I= NPOL+1,N

       FNI= FNI + B(I) * dLOG(1.D0 - dEXP(-TPID(I)*TN))

   20 CONTINUE

C

  999 CONTINUE

C

      TSAVE=T

      DSAVE=D

      FNIS=FNI

C

      RETURN

      END

C******************************************************************************

      DOUBLEPRECISION FUNCTION FNIT(T,D)

C******************************************************************************

C

C  THIS SUBROUTINE CALCULATES THE 1ST TN-DERIVATIVE OF F'S NORMALIZED

C  IDEAL PART

C

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON /CFNI/B2,B(7),TPID(7),NPOL,N

      COMMON/CNORM/TNORM,DNORM

      COMMON /CEPS/ EPS

C

      IF( dABS(T-TSAVE) .LT. EPS ) THEN

       FNIT = FNITS

       RETURN

      END IF

C

      DN= D/DNORM

      TN= TNORM/T

C

      FNIT =  B2/TN + B(2)

C

      DO 20 I= NPOL+1,N

       FNIT= FNIT + TPID(I)*B(I)

     *              *((1.D0-dEXP(-TPID(I)*TN))**(-1) - 1.D0)

   20 CONTINUE

C

      TSAVE=T

      DSAVE=D

      FNITS=FNIT

C

      RETURN

      END

C***************************************************************************

      DOUBLEPRECISION FUNCTION FNITT(T,D)

C*******************************************************************************

C

C THIS FUNCTION CALCULATES THE 2ND TN-DERIVATIVE OF

C F'S NORMALIZED IDEAL PART

C

      IMPLICIT REAL*8(A-H,O-Z)

      COMMON /CFNI/B2,B(7),TPID(7),NPOL,N

      COMMON/CNORM/TNORM,DNORM

      COMMON /CEPS/ EPS

C

      IF( dABS(T-TSAVE) .LT. EPS ) THEN

       FNITT = FNITTS

       RETURN

      END IF

C

      DN= D/DNORM

      TN= TNORM/T

C

      FNITT =  -  B2/TN**2

C

      DO 20 I= NPOL+1,N

       EX=dEXP(-TPID(I)*TN)

       FNITT= FNITT- TPID(I)**2*B(I) * (1.D0- EX)**(-2) *  EX

   20 CONTINUE

C

      TSAVE=T

      DSAVE=D

      FNITTS=FNITT

C

      RETURN

      END

C**********************************************************************
c     BLOCKDATA FNICOO
C**********************************************************************
C      IMPLICIT REAL*8(A-H,O-Z)
C
C
C THIS ROUTINE SETS COEFFICIENTS FOR F'S NORMALIZED IDEAL PART OF WATER
C OF COOPER'S EQUATION
C
C   Cooper, J.R. (1982):
C             Representation of the Ideal-Gas Thermodynamic Properties
C             of Water. Int. J. Therm. 3, 35 (1982).
C
c     COMMON /CFNI/  B2, B(7), TPID(7), NPOL, N
c     COMMON /CNULLP/T0,D0,F0,H0,U0,S0,G0
c     DATA F0/0.D0/,H0/0.D0/, U0/0.D0/,S0/0.D0/,G0/0.D0/,NPOL/2/,N/7/
C
c     DATA B2/3.00632D0/
C
C     THERE MAY BE MACHINEDEPENDANT PROBLEMS TO YIELD ZERO VALUES FOR
C     ENTROPY (S) AND INTERNAL ENERGY (U) AT THE TRIPLE POINT.
C     IN ORDER TO YIELD U=0 AND S=0 AT THE TRIPLEPOINT IN THE LIQUID,
C     ONE HAS TO ADJUST THE COEFFS. B(1) AND B(2) BY A CALL OF FNULLP.
C
c     DATA (B(I),I=3,7)/ .012436D0,.97315D0,1.27950D0,
c    *                   .969560D0,.24873D0/,
c    *  (TPID(I),I=1,7)/  0.D0,1.D0,
c    *           0.1287202151D+01,0.3537101709D+01,0.7740210774D+01,
c    *           0.9243749421D+01,0.2750564020D+02/
c     END
C***********************************************************************

      SUBROUTINE FNULLP

C***********************************************************************

C

C     THIS ROUTINE WILL ADJUST THE COEFS. OF THE IDEAL GAS FUNCTION

C     IN ORDER TO YIELD S=U=0 AT THE TRIPLEPOINT

C

      IMPLICIT REAL*8 (A-H,O-Z)

C

      COMMON /CFNI/  B2, B(7), TPID(7), NPOL, N

      COMMON /CNULLP/T0,D0,F0,H0,U0,S0,G0

      B(2)=B(2) - (FNIT(T0,D0) + FNRT(T0,D0))

      B(1)=B(1) - (FNI (T0,D0) + FNR(T0,D0) )

      WRITE (*,*) '         B(1)=',B(1),'B(2)=',B(2)

      RETURN

       END
