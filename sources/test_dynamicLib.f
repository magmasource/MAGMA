!
! Minimal test routines for MELTS dynamic library package
!
program test
!
! storage for meltsgetoxidenames and meltsgetphasenames
!
  character*20 oxides(50), phases(50)
  integer numoxides, numphases, phaseIndices(50)

!
! storage for meltsprocess and meltsgetphaseproperties
!  
  character*20 phasenames(20)
  character*100 errorString
  integer node, mode, iterations, status
  double precision pressure, temperature, enthalpy, bulk(19), properties(33,20)
!
! storage for meltsgetendmemberproperties
!  
  double precision endprops(3, 20)        
!     
! local storage
!
  integer i, j, k
  
  print *, "Press 1 then return when ready ..."
  read *, i
!
! meltsgetoxidenames
!   character*n oxides(19) [ pre-allocate, must exceed numoxides in length ]
!   integer n
!   integer numoxides [ return ]
!  
  print *, "Before call to meltsgetoxidenames..."
  call meltsgetoxidenames(oxides, 20, numoxides)
  print *, "Return from meltsgetoxidenames with result:"
  do i=1,numoxides
    print *, oxides(i)
  end do
  print *, "numxides = ", numoxides
!
! meltsgetphasenames
!   character*n phases(50) [ pre-allocate, must exceed numphases in length ]
!   int n
!   int numphases [ return ]
!   int phaseIndices(50)
! 
  print *, "Before call to meltsgetphasenames..."
  call meltsgetphasenames(phases, 20, numphases, phaseIndices)
  print *, "Return from meltsgetphasenames with result:"
  do i=1,numphases
    print *, phases(i), phaseIndices(i)
  end do
  print *, "numphases = ", numphases
  
  print *, "Before first call to meltsprocess..."
  node = 1;
  mode = 1;
  pressure = 1000.0
  temperature = 1400.0
  enthalpy = 0.0
  bulk( 1) = 48.68   
  bulk( 2) =  1.01   
  bulk( 3) = 17.64   
  bulk( 4) =  0.89   
  bulk( 5) =  0.0425 
  bulk( 6) =  7.59   
  bulk( 7) =  0.0    
  bulk( 8) =  9.10   
  bulk( 9) =  0.0
  bulk(10) =  0.0
  bulk(11) = 12.45   
  bulk(12) =  2.65   
  bulk(13) =  0.03   
  bulk(14) =  0.08   
  bulk(15) =  0.2    
  bulk(16) =  0.0
  bulk(17) =  0.0
  bulk(18) =  0.0
  bulk(19) =  0.0
!
! meltsprocess
!   integer node [ input ]
!   integer mode [ input, 2 = isenthalpic continuing run, 1 = initial run or update run ]
!   double precision pressure
!   double precision bulk(19) [ input composition of the system ]
!   double precision enthalpy [ return if mode == 1, input if mode == 2]
!   double precision temperature [ return if mode == 2, input if mode == 1 ]
!   character*n phasenames(20) [ pre-allocated memory, must be large enough to hold names of all stable phases in system ]
!   integer n
!   integer numphases [ return ]
!   integer iterations [ return ]
!   integer status [ return, pass to meltsgeterrorstring ]
!   double precision properties (11+numoxides+3, 20) [ pre-allocated memory, column dimension must be large enough to hold 
!                                                      all stable phases in system ]
!   integer phaseIndices(20) [return] [ pre-allocated memory, column dimension must be large enough to hold 
!                                                      all stable phases in system ]
!
  call meltsprocess(node, mode, pressure, bulk, enthalpy, temperature, phasenames, 20, numphases, &
  iterations, status, properties, phaseIndices)
  print *, "... node = ", node
  print *, "... mode = ", mode
  do i=1,numoxides
    print *, "... input ", oxides(i), " = ", bulk(i)
  end do
  print *, "... enthalpy = ", enthalpy
  print *, "... temperature = ", temperature
  do i=1,numphases
    print *, "... stable phases: ", phasenames(i)
    print *, "... index:", phaseIndices(i)
    print *, "...... g       = ", properties( 1, i)
    print *, "...... h       = ", properties( 2, i)
    print *, "...... s       = ", properties( 3, i)
    print *, "...... v       = ", properties( 4, i)
    print *, "...... cp      = ", properties( 5, i)
    print *, "...... dcpdt   = ", properties( 6, i)
    print *, "...... dvdt    = ", properties( 7, i)
    print *, "...... dvdp    = ", properties( 8, i)
    print *, "...... d2vdt2  = ", properties( 9, i)
    print *, "...... d2vdtdp = ", properties(10, i)
    print *, "...... d2vdp2  = ", properties(11, i)
    do j=1,numoxides
      print *, "...... composition ", oxides(j), " = ", properties(11+j, i)
    end do
    print *, "...... volume fraction  = ", properties(11+numoxides+1, i)
    print *, "...... density (kg/m^3) = ", properties(11+numoxides+2, i)
    print *, "...... viscosity (Pa-s) = ", properties(11+numoxides+3, i)
  end do
  print *, "... iterations = ", iterations
  print *, "... status = ", status
  
  print *, "Before call to meltsgeterrorstring..."
!
! meltsgeterrorstring
!   integer status [ input, number returned from meltsprocess ]
!   character*n errorstring [ return ]
!   integer n
!
  call meltsgeterrorstring(status, errorString, 100)
  print *, "... Error string: ", errorString
  
!     do k=1,1000
  do k=1,1
    print *, "Before second call to meltsprocess..."
    node = 1;
    mode = 2;
    enthalpy = enthalpy - 1.0
!
! example of a continuation call, enthalpy/pressure specified
!
    call meltsprocess(node, mode, pressure, bulk, enthalpy, temperature, phasenames, 20, numphases, &
    iterations, status, properties, phaseIndices)
    print *, "... node = ", node
    print *, "... mode = ", mode
    do i=1,numoxides
      print *, "... input ", oxides(i), " = ", bulk(i)
    end do
    print *, "... enthalpy = ", enthalpy
    print *, "... temperature = ", temperature
    do i=1,numphases
      print *, "... stable phases: ", phasenames(i)
      print *, "... index:", phaseIndices(i)
      print *, "...... g       = ", properties( 1, i)
      print *, "...... h       = ", properties( 2, i)
      print *, "...... s       = ", properties( 3, i)
      print *, "...... v       = ", properties( 4, i)
      print *, "...... cp      = ", properties( 5, i)
      print *, "...... dcpdt   = ", properties( 6, i)
      print *, "...... dvdt    = ", properties( 7, i)
      print *, "...... dvdp    = ", properties( 8, i)
      print *, "...... d2vdt2  = ", properties( 9, i)
      print *, "...... d2vdtdp = ", properties(10, i)
      print *, "...... d2vdp2  = ", properties(11, i)
      do j=1,numoxides
        print *, "...... composition ", oxides(j), " = ", properties(11+j, i)
      end do
      print *, "...... volume fraction  = ", properties(11+numoxides+1, i)
      print *, "...... density (kg/m^3) = ", properties(11+numoxides+2, i)
      print *, "...... viscosity (Pa-s) = ", properties(11+numoxides+3, i)
    end do
    print *, "... iterations = ", iterations
    print *, "... status = ", status
  
    print *, "Before call to meltsgeterrorstring..."
    call meltsgeterrorstring(status, errorString, 100)
    print *, "... Error string: ", errorString
  end do
    
  print *, "Before call to meltsgetphaseproperties..."
!
! meltsgetphaseproperties
!   character*n phaseName [ input, zero byte deliminated string ]
!   double precision temperature [ input]
!   double precision pressure [ input ]
!   double precision bulk(19) [ input, composition of phase in oxides ]
!   double precision properties(11) [ return, memory must be pre-allocated ]
!
  call meltsgetphaseproperties('liquid'//char(0), temperature, pressure, bulk, properties)
  print *, "...... g	   = ", properties( 1, 1)
  print *, "...... h	   = ", properties( 2, 1)
  print *, "...... s	   = ", properties( 3, 1)
  print *, "...... v	   = ", properties( 4, 1)
  print *, "...... cp	   = ", properties( 5, 1)
  print *, "...... dcpdt   = ", properties( 6, 1)
  print *, "...... dvdt    = ", properties( 7, 1)
  print *, "...... dvdp    = ", properties( 8, 1)
  print *, "...... d2vdt2  = ", properties( 9, 1)
  print *, "...... d2vdtdp = ", properties(10, 1)
  print *, "...... d2vdp2  = ", properties(11, 1)

  print *, "Before call to meltsgetendmemberproperties..."

!   double precision pressure
!   double precision bulk(19) [ input, composition of phase in oxides ]
!   double precision temperature
!   character*n phasenames(20) [ pre-allocated memory, must be large enough to hold names of all endmembers in phase ]
!   integer numphases [ return number of end members, plus one for solution phases]
!   double precision properties (3, 20) [ pre-allocated memory, column dimension must be large enough to hol
!                                                      all endmembers in phase, plus one ]

!     
    call meltsgetendmemberproperties('liquid'//char(0), temperature, pressure, bulk, &
      phasenames, 20, numphases, endprops)
    print *, "numendmembers = ", numphases-1
      print *, "... phase: ", phasenames(1)
      print *, "...... g (molar) = ", endprops( 3, 1)
      print *, "...... g0        = ", endprops( 2, 1)
      print *, "...... gmix      = ", endprops( 3, 1)-endprops( 2, 1)

    do i=2,numphases
      print *, "... endmembers: ", phasenames(i)
      print *, "...... X         = ", endprops( 1, i)
      print *, "...... mu0       = ", endprops( 2, i)
      print *, "...... mu        = ", endprops( 3, i)
    end do
      
end program test
