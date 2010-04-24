program test
  character*20 oxides(50), phases(50)
  integer i, numoxides, numphases
  
  print *, "Before call to meltsgetoxidenames..."
  call meltsgetoxidenames(oxides, 20, numoxides)
  print *, "Return from meltsgetoxidenames with result:"
  do i=1,numoxides
    print *, oxides(i)
  end do
  print *, "numxides = ", numoxides
  
  print *, "Before call to meltsgetphasenames..."
  call meltsgetphasenames(phases, 20, numphases)
  print *, "Return from meltsgetphasenames with result:"
  do i=1,numphases
    print *, phases(i)
  end do
  print *, "numphases = ", numphases
  
  print *, "Before call to meltsprocess..."
  
  print *, "Before call to meltsgeterrorstring..."
  
  print *, "Before call to meltsgetphaseproperties..."
end program test
