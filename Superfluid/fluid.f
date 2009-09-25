       SUBROUTINE FLUID (X, T, P, V, G)
C
       PARAMETER (NGAS = 13)
       DIMENSION X(NGAS), GI(NGAS)
CC
CC**********************************************************************
C       X (NGAS) - MOLE FRACTIONS OF GASES
C       T        - TEMPERATURE         (K)
C       P        - PRESSURE            (BAR)
C       V        - VOLUME OF MIXTURE   (CM3/MOLE)
C       G        - GIBBS ENERGY        (J/MOLE)
C       GDIVP    - FUGACITY OF MIXTURE COUNTING FROM 5000 BAR (J/MOLE)
CC --------------------------------------------------------------------
C         1 - H2O, 2 - CO2,  3 - CH4,  4 - CO,    5 - O2, 
C         6 - H2,  7 - S2,   8 - SO2,  9 - COS,  10 - H2S,
C        11 - N2, 12 - NH3, 13 - Ar
CC**********************************************************************
CC
        PDIV = 4999.0
        TDIV = 400.0
        IF ( X(1) .GT. 0.0000001) TDIV = 700.0
C
        IF ( T .LT. TDIV .OR. P .LT. PDIV) THEN
                CALL SHI   (X, T, P, V, G, GI)
                RETURN
        ELSE
                CALL SHI   (X, T, PDIV, VDIV, GDIV, GI)
                CALL TOLJA (X, T, P, V, GDIVP)
                G = GDIV + GDIVP
        END IF
C
        RETURN
        END









