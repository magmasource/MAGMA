# =================================================================================
# Makefile for build of the xMELTS package on Intel (MacOS X - 10.8)
# =================================================================================

MAKEFILE	= Makefile.ML

# Compilation options
# ===================

PROTO   = XTFUNCPROTO
VLIST   = _NO_DRAWINGA_VLIST_PARENT
ENTRYC  = _NO_WHITE_TEXTW
ACEPLT  =     GRACE_PIPE

# Environment variable defaults
# =============================

MELTS_AUTHOR_LIST      = Mark S. Ghiorso, Marc M. Hirschmann, Paul D. Asimow 
MELTS_DATA_DIR         = .
MELTS_DATA_SUFFIX      = *.xml
MELTS_HARDWARE_VERSION = 3.4 GHz Quad Core Intel i7 
MELTS_INPUT_DIR        = .
MELTS_INPUT_SUFFIX     = *.melts
MELTS_MOTIF_VERSION    = 3.0
MELTS_OS_VERSION       = Mac OS X - 10.8.0
MELTS_OUTPUT_FILE      = melts.out
MELTS_WWW_BROWSER      = 
MELTS_WWW_CALCULATOR   = http://melts.ofm-research.org/
MELTS_WWW_MANUAL       = http://melts.ofm-research.org/
MELTS_X_VERSION        = X11R6/OpenMotif3
MELTS_RELEASE_DATE     = August 2013
MELTS_RELEASE_VERSION  = 5.6.1 ()(p)(x), V1.0.2 (rhyolite) (Mac OS X - 10.8.4, clang 3.0, 64 bit)

# Include files for Motif (INCXM), Xt (INCXT), X11 (INCX), and the ANSI C library (INCC)
# ======================================================================================

INCC   = /opt/local/include
INCXM  = /opt/local/include
INCX   = /usr/X11R6/include
INCF2C = .
INCXML = /usr/include/libxml2

# Compiler choice and flags - Do not delete the $(BATCH) macro
# ============================================================

AR       = ar
ARFLAGS  = rv
DYFLAGS	 = xv
CC       = clang
FC       = gfortran
CFLAGS   = -ansi -c -O3 $(BATCH) -mmacosx-version-min=10.7 \
           -D$(VLIST) -D$(ACEPLT) -D$(ENTRYC) -I./includes -I$(INCC) -I$(INCXM) -I$(INCX) -I$(INCXML) -I$(INCF2C) -D__osf__
FFLAGS   = -O3
RANLIB   = ranlib
RANLIBFG = -s
RM       = rm
RMFLAGS  = -f
MPICC      = mpicc
MPICCFLAGS = -D_REENTRANT -DUSE_MPI -DDO_NOT_USE_LAM_XLED -I/usr/include
MPILDFLAGS = -L/usr/lib -lmpi

# Loader flags (default is shared, add -non_shared)
# =================================================

LDFLAGS = 
SONAME	= dylib
ifneq ($(DYNAMIC),)
override DYNAMIC = -dynamiclib
endif

# Libraries for grace_np, Mrm, Motif, Xt and X11, c functions and math functions 
# ========================================================================================================

LIBS    = -L/opt/local/lib -lMrm -lXm -lgrace_np -lXt -lXp -lX11 -lXext -lXpm -lXmu ../port3/libport.a
PUBLIBS = /opt/local/lib/libMrm.a /opt/local/lib/libXm.a /opt/local/lib/libXft.a /opt/local/lib/libgrace_np.a /opt/local/lib/libXt.a /opt/local/lib/libXp.a \
          /opt/local/lib/libSM.a /opt/local/lib/libICE.a /opt/local/lib/libX11.a /opt/local/lib/libXext.a /opt/local/lib/libXpm.a /opt/local/lib/libXmu.a \
          /opt/local/lib/libXRender.a /opt/local/lib/libXau.a /opt/local/lib/libXdmcp.a /opt/local/lib/libjpeg.a /opt/local/lib/libpng.a /opt/local/lib/libpng14.a \
          /opt/local/lib/libexpat.a /opt/local/lib/libz.a /opt/local/lib/libbz2.a /opt/local/lib/libfreetype.a /opt/local/lib/libcharset.a /opt/local/lib/libfontconfig.a \
          /opt/local/lib/libiconv.a /opt/local/lib/libX11-xcb.a /opt/local/lib/libxcb.a ../port3/libport.a /usr/local/gfortran/lib/libgfortran.a \
          /usr/local/gfortran/lib/libquadmath.a /usr/local/gfortran/lib/gcc/x86_64-apple-darwin11/4.6.2/libgcc.a
LIBF2C = 
LIBXML = -L/usr/lib -lxml2
LIBBATCH = -L/usr/lib -lxml2 -lz -liconv

# Set environment variable for backwards deployment to Mac OS X 10.7
# ==================================================================
export MACOSX_DEPLOYMENT_TARGET := 10.7

include Makefile.common

# end of Makefile
# ===============
