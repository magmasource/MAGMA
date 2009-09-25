      PROGRAM SUPERFL
c      IMPLICIT DOUBLE PRECISION (A-H, O-Z)
      PARAMETER (NGAS = 13)
      PARAMETER (EPCCOMP=1.0E-30)

      DOUBLE PRECISION XX(NGAS), GGI(NGAS), TT, PP, VV, GG, GAMA, FUG
      DOUBLE PRECISION X(NGAS)
      DOUBLE PRECISION XT
      DIMENSION GI(NGAS), GAMA(NGAS), XPURE(NGAS), 
     *            FUG(NGAS)
      CHARACTER*3 NAME(NGAS)
      CHARACTER*1 YN
C
      DATA NAME /'H2O','CO2','CH4',' CO',' O2',' H2',' S2','SO2',
     *           'COS','H2S',' N2','NH3',' Ar'/
c     OPEN (UNIT=10, FILE='SUPER.OUT', ACCESS='APPEND')
      OPEN (UNIT=10, FILE='SUPER.OUT')

C
      WRITE (6,*)
      WRITE (6,*)
      WRITE (6,'(13x,a)') '$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$' 
      WRITE (6,'(13x,a)') '$$$    $$$  $$  $$     $$$      $$     $$$'
      WRITE (6,'(13x,a)') '$$  $$  $$  $$  $$  $$  $$  $$$$$$  $$  $$'
      WRITE (6,'(13x,a)') '$$  $$$$$$  $$  $$  $$  $$  $$$$$$  $$  $$'
      WRITE (6,'(13x,a)') '$$$  $$$$$  $$  $$     $$$      $$     $$$'
      WRITE (6,'(13x,a)') '$$$$  $$$$  $$  $$  $$$$$$  $$$$$$  $  $$$'
      WRITE (6,'(13x,a)') '$$  $$  $$  $$  $$  $$$$$$  $$$$$$  $$  $$'
      WRITE (6,'(13x,a)') '$$$    $$$$    $$$  $$$$$$      $$  $$$ $$'
      WRITE (6,'(13x,a)') '$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$'

      WRITE (6,*)
      WRITE (6,*) 
     *'               WELCOME TO USE THE SUPERFLUID PROGRAM !   '
      WRITE (6,*)
      WRITE (6,*)
     *'                --- Calculation of P-V-T Relations '
      WRITE (6,*) 
     *'                        and a-f-G Properties '
      WRITE (6,*) 
     *'             in C-H-O-S-N-Ar Supercritical Fluid System '
      WRITE (6,*) 
     *'             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  '
      WRITE (6,*) 
     *'             Authors:  Benoloshko AB, Shi PF, Saxena SK '
      WRITE (6,*) 
     *'                       1992, Uppsala University, Sweden  '
      WRITE (6,*) 
     *'             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  '
      WRITE (6,*)
      WRITE (6,*) '           NOTES:   '
      WRITE (6,*) 
     *'             Input pressure in BAR and temperature in K '
      WRITE (6,*) 
     *'             Number of gas:     from 1 to 13 '
      WRITE (6,*) 
     *'             Mole fraction of gas must be from 0 to 1 '
      WRITE (6,*) 
     *'             Sum of X must be equal to 1.0 '
      WRITE (6,*) 
     *'             Mole fraction of fluid equals to 0 on default '
      WRITE (6,*) 
     *'             Type negative number to finish composition input '
      WRITE (6,*) 
     *'             All calculated data will be saved in SUPER.OUT'
      WRITE (6,*) 
     *'             ------------------------------------------------ '
      WRITE (6,*)
C        
      WRITE(10,*)
      WRITE(10,*)
      WRITE(10,*) '       THERMODYNAMIC CALCULATION OF '
      WRITE(10,*) '    THE C-H-O-S-N-Ar SUPERCRITCAL FLUIDS '
      WRITE(10,*) '    - using SUPERFLUID (Uppsala, 1992) - '      
      WRITE(10,*) ' --------------------------------------- '
      WRITE(10,*)

      WRITE( 6,*) ' **************** '
      WRITE(10,*) ' *** '

      III = 3

C
 44   WRITE(6,*)
      WRITE(6,*) ' GIVING T(K) and P(bar) : '
      WRITE(6,*) ' ------------------------ '

      WRITE (6,'(a18,$)') '         T, P =   '
      READ  (5,*)   T, P

      PP = P
      TT = T

      RT = 8.31451*T
      P1BAR = 1.0

      IF (III .EQ. 3) GO TO 4
      IF (III .EQ. 2) GO TO 3

 4        DO 1 I = 1, NGAS
	  XX(i) = 0.0D0
          X(I) = 0.0D0
 1        XPURE(I) = 0.0D0

      XT = 0.0D0

      WRITE(6,*)
      WRITE(6,*) ' GIVING COMPOSITION X(I): '
      WRITE(6,*) ' ------------------------ '
      WRITE(6,*) '       List of The C-H-O-S-N-Ar Fluid Species: '
      WRITE (6,*) 
     *  '       ---------------------------------------------------'
      WRITE (6,12)
 12   FORMAT
     *('         1   2   3   4   5   6   7   8   9  10  11  12  13 ')
      WRITE (6,'(6X,13(A4))') (NAME(I),I=1,NGAS)

 54   XT = 0.0D0
      DO I = 1, NGAS
	  XX(I) = 0.0D0
          X(I) = 0.0D0
          XPURE(I) = 0.0D0
      ENDDO

      WRITE (6,*) 
     *'       ---------------------------------------------------'

 6    WRITE (6,'(A22,$)') '               IGAS = '
      READ  (5,*) IGAS

      IF (IGAS .GE. 14 .OR. IGAS .EQ. 0) THEN
      WRITE (6,*) 
     *'                 !!!    The IGAS number is 0 or larger than 13'
    
      GOTO 6
      ELSE
       GOTO 66
      ENDIF

 66   IF ( IGAS .LT. 0 ) GO TO 33
      WRITE (6,'(A31,A3,A4,$)') 
     *'                            X(',name(igas),') = '
      READ (5,*) X(IGAS)
      XX(IGAS) = X(IGAS)
      XT = XT + X(IGAS)

      IF (XT .GT. 1.0+EPCCOMP) THEN
        WRITE(6,*) '         SORRY!!!    Your X(total) is > 1.0 '
        WRITE(6,*) '                     You have to give them again!'
        GO TO 54
      ELSE
        GO TO 6
      END IF

 33   IF (XT .LT. 1.0-EPCCOMP) THEN
        WRITE(6,*) '         SORRY!!!    Your X(total) is < 1.0 '
        WRITE(6,*) '                     You have to give them again!'
        GO TO 54
      ELSE
        GO TO 3
      END IF

 3    WRITE (6,*) 
      WRITE (6,*) 
      WRITE (6,*) ' LISTING THE CALCULATED RESULT at GIVEN T-P-X: '
      WRITE (6,*) ' --------------------------------------------- '

C
C  CALCULATING ......
C

        CALL FDER (XX, TT, PP, VV, GG, GGI)

        V = real(VV)
        G = real(GG)

	DO I = 1, NGAS
              GI(I) = real(GGI(I))
        ENDDO

	GSUM = 0.0

        DO 2 I = 1, NGAS

 	  GSUM = GSUM + GI(I)*X(I)
	  GAMA(I) = 1.0
          XPURE(I) = 1.0

          CALL FLUID (XPURE, T, P1BAR, V1BAR, G1BAR)
	  CALL FLUID (XPURE, T, P,     VBAR,  GBAR)

	  XPURE(I) = 0.0

          IF (X(I) .GT. 0.0) THEN
                  GAMA(I) = (GI(I) - G1BAR - RT*LOG(P))
                  FUG(I)  = (GBAR - G1BAR - RT*LOG(P))
          END IF

	  IF (X(I) .GT. 0.0 .AND. X(I) .LT. 1.0) THEN
              GAMA(I) = DEXP(GAMA(I)/RT)
              GAMA(I) = GAMA(I)/X(I)
	      FUG(I)  = DEXP(FUG(I)/RT)
	      GAMA(I) = GAMA(I)/FUG(I)
	  ELSE
	      GAMA(I) = 1.0
	      FUG(I)  = DEXP(FUG(I)/RT)
          END IF

          XPURE(I) = 0.0

 2        CONTINUE

C
C  WRITE OUT THE RESULT on SCREEN and OUTPUT FILE 'SUPER.OUT'
C

      WRITE ( 6,35) T
      WRITE ( 6,36) P
      WRITE ( 6,37) V
      WRITE ( 6,38) G

      WRITE (10,35) T
      WRITE (10,36) P
      WRITE (10,37) V
      WRITE (10,38) G

 35   FORMAT ('               T = ', F14.2, '   (K) ')
 36   FORMAT ('               P = ', F14.2, '   (bar) ')
 37   FORMAT ('               V = ', F16.4, ' (cm^3/mol) ')
 38   FORMAT ('               G = ', F14.2, '   (J/mol) ')

       WRITE ( 6,303) 
       WRITE (10,303)
       WRITE ( 6,302)
       WRITE (10,302)
       WRITE ( 6,303) 
       WRITE (10,303)

 301  FORMAT(1X, I2, 2X, A3, F8.4, F10.6, E13.5, F12.2, E15.6)
 302  FORMAT
     *('  N  Name    Xi     Gamma     FugCoeff       Gi', 8X,
     * ' Fugacity')
 303  FORMAT
     *(' ---------------------------------------------------------------
     *---')

       DO 199 I = 1, NGAS
	 IF (X(I) .GT. 0.0) THEN
            WRITE ( 6,301) I, NAME(I), X(I), GAMA(I), FUG(I), GI(I),
     *                       FUG(I)*GAMA(I)*X(I)*P
            WRITE (10,301) I, NAME(I), X(I), GAMA(I), FUG(I), GI(I),
     *                       FUG(I)*GAMA(I)*X(I)*P
         END IF
199    CONTINUE

	  WRITE ( 6,*)
     >(' ===============================================================
     >===')
	  WRITE ( 10,*)
     >(' ===============================================================
     >===')

        WRITE (6,*)
        WRITE (6,*) '       DO YOU WANT TO HAVE OTHER CALCULATIONS '
        WRITE (6,*) '           at other T-P-X conditions (Y/N)? '
        WRITE (6,*) '       -------------------------------------- '
       
 24     READ (5,'(A)') YN

      IF (YN .EQ. 'y' .OR. YN .EQ. 'Y') THEN
        WRITE(6,*)
        WRITE (6,*) '         THREE OPTIONS:  '
        WRITE (6,*) '             1.   SAME  T-P, but DIFFERENT X(I); '
        WRITE (6,*) '             2.   SAME X(I), but DIFFERENT  T-P; '
        WRITE (6,*) '             3.   DIFFERENT  T-P-X(I). '
        WRITE (6,*) '         WHICH ONE DO YOU WANT TO CHOOSE (1/2/3)?'
 34     READ  (5,*) III
        IF (III .EQ. 1) THEN
              WRITE( 6,*) ' **************** '
              WRITE(10,*) ' *** '
              WRITE(6,*)
              WRITE(6,*) '          LISTING DEFINED T(K) and P(bar): '
              WRITE (6,'(10X,A12,F10.2,F14.2)') '     T, P = ',T,P
              GO TO 4
        ELSEIF (III .EQ. 2) THEN
              WRITE( 6,*) ' **************** '
              WRITE(10,*) ' *** '
              WRITE(6,*)
              WRITE(6,*) '          LISTING DEFINED COMPOSITION X(I): '
              DO I = 1, NGAS
                IF (X(I) .GT. 0.0) THEN
                   WRITE(6,'(15X,I2,4X,A3,2X,F10.4)') I, NAME(I), X(I)
                END IF
              ENDDO
              GO TO 44
        ELSEIF (III .EQ. 3) THEN
              WRITE( 6,*) ' **************** '
              WRITE(10,*) ' *** '
      GO TO 44
        ELSE
              WRITE(6,*) '           PLEASE CHOOSE THE CORRECT OPTION !'
              GO TO 34
        END IF
      ELSEIF (YN .EQ. 'n' .OR. YN .EQ. 'N') THEN
             GO TO 14
      ELSE
             GO TO 24
      END IF

 14     WRITE (6,*) 
        WRITE (6,*) '       The calculated results are stored in SUPER.O
     *UT ' 
        WRITE (6,*) '                                            *******
     *** '
        WRITE (6,*) 
        WRITE (6,*) '       HAVE A NICE DAY! '
        WRITE (6,*) 

      END

