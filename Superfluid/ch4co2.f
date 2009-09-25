c      PROGRAM AAA

c1     WRITE (*,*) ' T P '

c      READ  (*,*) T,P

c      CALL CO2 (T,P,V,G)

c      WRITE (*,*) ' T P V G',T,P,V,G,G/4184.0

c      CALL CH4 (T,P,V,G)

c      WRITE (*,*) ' T P V G',T,P,V,G,G/4184.0

c      GO TO 1

c      END



       SUBROUTINE KJCO2 (x,T,V,P)
       PARAMETER ( NGAS = 13 )
       dimension x(ngas)
       CT =  (28.31 + 0.10721*T -8.81*1.E-6*T**2)*1.E6
       DT =  (9380.0 - 8.53*T + 1.189*1.E-3*T**2)*1.E6
       ET =  (-368654.0 + 715.9*T + 0.1534*T**2)*1.E6
C
       AV = CT + DT/V + ET/V**2
       B  = 58.0
       R  = 83.14
       Y  = B/4.0/V
C
       P = R*T*(1+Y+Y**2-Y**3)/V/(1.0-Y)**3 - AV/V/(V+B)/SQRT(T)
       RETURN
       END
C
       SUBROUTINE KJCO2G (T,P,V,G)
       CT =  (28.31 + 0.10721*T -8.81*1.E-6*T**2)*1.E6
       DT =  (9380.0 - 8.53*T + 1.189*1.E-3*T**2)*1.E6
       ET =  (-368654.0 + 715.9*T + 0.1534*T**2)*1.E6
C
       AV = CT + DT/V + ET/V**2
       B  = 58.0
       R  = 83.1451
       Y  = B/4.0/V
C
       PP = R*T*(1+Y+Y**2-Y**3)/V/(1.0-Y)**3 - AV/V/(V+B)/SQRT(T)
       ZZ = PP*V/R/T
C       WRITE (*,*) ' ZZ= ',ZZ
       RT32 = R*T**1.5
       VB   = V+B
       G = Y*(8.0-9.0*Y+3.0*Y*Y)/(1.0-Y)**3 - ALOG(ZZ) - CT/RT32/VB
     >     -DT/RT32/V/VB-ET/RT32/V/V/VB + CT/RT32/B*ALOG(V/VB)
     >     -DT/RT32/B/V + DT/RT32/B/B*ALOG(VB/V) - ET/RT32/2.0/B/V/V
     >     +ET/RT32/B/B/V -ET/RT32/B/B/B*ALOG(VB/V)
       G = (G*R*T +R*T*ALOG(P))/10.0
       RETURN
       END
C
      SUBROUTINE CO2 (T,P,V,G)
      PARAMETER (NGAS = 13)
      DIMENSION X(NGAS)
      EXTERNAL KJCO2
      IF (P .LE. 10.0) THEN
         V = 83.1451*T/P
         G = 8.31451*T*ALOG(P)
         RETURN
      END IF
      IF (P .LE. 10              ) V0 = 10000.0
      IF (P .Ge. 10 .AND. P.LE.60) V0 =  200.0
      IF (P .GT. 60              ) V0 =   20.0
      EPS = 0.001
      CALL NR (KJCO2, 0.002, X,T,P, V0, V)
      CALL KJCO2G (T,P,V,G)
      RETURN
      END
C

c     SUBROUTINE NR (FUNCT, EPS, X,T,P,V0,V)

c     PARAMETER (NGAS = 13)

c     DIMENSION X(NGAS)

c     EXTERNAL FUNCT

c       VJ  = V0

c       PTRUE = P

c1       CALL FUNCT (X, T,VJ, PJ)

c       CALL FUNCTS(FUNCT, X, T,VJ, PJS)

c       VJ1 = (PTRUE - PJ)/PJS + VJ

C        WRITE (*,*) ' VJ1= ',VJ1

c       IF ( ABS((VJ-VJ1)/VJ1) .LT. EPS) THEN

c              V = VJ1

c              RETURN

c       ELSE

c              VJ = VJ1

c              GOTO 1

c       END IF

c       RETURN

c       END

C

c       SUBROUTINE FUNCTS ( FUNCT,X, T, V, PS)

c        PARAMETER (NGAS = 13)

c        DIMENSION X(NGAS)

c        EXTERNAL FUNCT

c       DV = 0.002

c       VM = V -DV

c       VP = V +DV

c       CALL FUNCT (X, T, VM, PM)

c       CALL FUNCT (X, T, VP, PP)

c       PS = (PP-PM)/2.0/DV

c       RETURN

c       END

C

       SUBROUTINE KJCH4 (X,T,V,P)

       PARAMETER (NGAS = 13)

       DIMENSION X(NGAS)

       CT = 13.403 *1.E6  + 9.28 *1.E4*T + 2.7       *T**2

       DT =  5.216 *1.E9  - 6.80 *1.E6*T + 3.28 *1.E3*T**2

       ET = -2.3322*1.E11 + 6.738*1.E8*T + 3.179*1.E5*T**2

C

       AV = CT + DT/V + ET/V**2

       B  = 60.0

       R  = 83.1451

       Y  = B/4.0/V

C

       P = R*T*(1+Y+Y**2-Y**3)/V/(1.0-Y)**3 - AV/V/(V+B)/SQRT(T)

       RETURN

       END

C

       SUBROUTINE KJCH4G (T,P,V,G)

       CT = 13.403 *1.E6  + 9.28 *1.E4*T + 2.7       *T**2

       DT =  5.216 *1.E9  - 6.80 *1.E6*T + 3.28 *1.E3*T**2

       ET = -2.3322*1.E11 + 6.738*1.E8*T + 3.179*1.E5*T**2

C

       AV = CT + DT/V + ET/V**2

       B  = 60.0

       R  = 83.1451

       Y  = B/4.0/V

C

       PP = R*T*(1+Y+Y**2-Y**3)/V/(1.0-Y)**3 - AV/V/(V+B)/SQRT(T)

       ZZ = PP*V/R/T

C       WRITE (*,*) ' ZZ= ',ZZ

       RT32 = R*T**1.5

       VB   = V+B

       G = Y*(8.0-9.0*Y+3.0*Y*Y)/(1.0-Y)**3 - ALOG(ZZ) - CT/RT32/VB

     >     -DT/RT32/V/VB-ET/RT32/V/V/VB + CT/RT32/B*ALOG(V/VB)

     >     -DT/RT32/B/V + DT/RT32/B/B*ALOG(VB/V) - ET/RT32/2.0/B/V/V

     >     +ET/RT32/B/B/V -ET/RT32/B/B/B*ALOG(VB/V)

       G = (G*R*T +R*T*ALOG(P))/10.0

       RETURN

       END

C

      SUBROUTINE CH4 (T,P,V,G)
      PARAMETER ( NGAS = 13 )
      DIMENSION X (NGAS)
      EXTERNAL KJCH4

      IF (P .LE. 6.0) THEN

         V = 83.1451*T/P

         G = 8.31451*T*ALOG(P)

         RETURN

      END IF

      IF (P .LE. 10              ) V0 = 1000.0

      IF (P .GT. 10 .AND. P.LE.60) V0 =  200.0

      IF (P .GT. 60              ) V0 =   20.0

      EPS = 0.002

      CALL NR (KJCH4, EPS, X,T,P, V0, V)

      CALL KJCH4G (T,P,V,G)

      RETURN

      END



