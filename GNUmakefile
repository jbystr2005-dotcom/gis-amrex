AMREX_HOME = ../../amrex

DIM = 2
COMP = gnu
DEBUG = TRUE
USE_MPI = FALSE
USE_OMP = FALSE

include $(AMREX_HOME)/Tools/GNUMake/Make.defs

VPATH += ./src
VPATH += ./include

INCLUDE_LOCATIONS += ./include

include Make.package

CXXFLAGS += $(shell gdal-config --cflags)
LIBRARIES += $(shell gdal-config --libs)

include $(AMREX_HOME)/Src/Base/Make.package
include $(AMREX_HOME)/Src/Boundary/Make.package
include $(AMREX_HOME)/Src/AmrCore/Make.package

include $(AMREX_HOME)/Tools/GNUMake/Make.rules