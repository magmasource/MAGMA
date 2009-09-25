            subroutine fder (xx,tt,pp,vv,gg,ggi)
            PARAMETER (NGAS=13)
            double precision xx,tt,pp,vv,gg,ggi
            dimension x(NGAS), gnder (NGAS),gi(NGAS),
     >      xx(NGAS), ggi(NGAS)
            t = tt
            p = pp
	    xstep = 1.e-8
            do 3 i = 1, ngas
	    if ( xx(i) .gt. 0.d0 .and. xx(i) .le. xstep) then 
		 x(i) = xstep
            else
                 x(i) = real (xx(i))
            end if
   3        continue
            call flder ( x, t, p, v, g, gnder)
            do 77 ii = 1,ngas
            if ( xx(ii) .gt. 0.0) g=g+xx(ii)*dlog(xx(ii))*8.31451*T
 77          continue
            gg = 0.0
            do 2 i = 1,NGAS
            gi(i) = gnder(i) 
   2        continue
            vv = v
            gg = g
            do 4 i = 1, ngas
	    if ( xx(i).gt. 0.0) then
	      ggi(i) = gi(i) + dlog(xx(i))*8.31451*t
	      else
              ggi(i) = gi(i)
	    endif
   4        continue
            return
            end
c
           subroutine flder( x, t, p, v, g, gnder)
           parameter (NGAS=13)
           dimension x(ngas), gnder (ngas), xdxi(ngas)
c           common /xeps/ xeps
c
c Calculation of Gibbs enery partial derivatives on composition
c Result: GXDER (1:NGAS, 1:NGAS)
c
           xeps = 2.e-8
           xexist = 1.e-45
c
           call fluid (x,t,p,v,g)
	   prod = 1000.0
	   dni = 0.001
           do 1 i = 1,ngas
	   gnder(i) = 0.0
	   if ( x(i) .gt. xexist) then 
           call xtoxdx (i,x,xdxi,dni,prod)
               call fluid (xdxi,t,p, vd, gplus)
              gnder(i) = (gplus*(1+dni)-g)/dni
            end if
  1        continue
c
           return
           end

           subroutine xtoxdx (j,x,xdxj,dnj,prod)
	   parameter (ngas=13)
	   dimension x(ngas),xdxj(ngas), bulk(ngas)
           s = 0.0
	   do 1 i = 1,ngas
	   bulk (i) = x(i)*prod
	   s = s + bulk(i)
  1        continue
	   bulk(j) = bulk(j) + dnj*prod
	   s = s + dnj*prod
	   do 2 i = 1,ngas
	   xdxj(i) = bulk(i)/s
  2        continue
	   return
	   end


