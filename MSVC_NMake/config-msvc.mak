# NMake Makefile portion for enabling features for Windows builds

# These are the base minimum libraries required for building glibmm.
BASE_INCLUDES =	/I$(PREFIX)\include

# Please do not change anything beneath this line unless maintaining the NMake Makefiles
LIBXMLXX_MAJOR_VERSION = 5
LIBXMLXX_MINOR_VERSION = 0

!if "$(CFG)" == "debug" || "$(CFG)" == "Debug"
DEBUG_SUFFIX = -d
!else
DEBUG_SUFFIX =
!endif

LIBXMLXX_BASE_CFLAGS =			\
	/I.\libxml++ /I.. /EHsc	\
	/FImsvc_recommended_pragmas.h	\
	/std:c++17


LIBXMLXX_EXTRA_INCLUDES =	\
	/I$(PREFIX)\include\libxml2	\
	/I$(PREFIX)\include

LIBXMLXX_CFLAGS = /DLIBXMLPP_BUILD $(LIBXMLXX_BASE_CFLAGS) $(LIBXMLXX_EXTRA_INCLUDES)
LIBXMLXX_EX_CFLAGS = $(LIBXMLXX_BASE_CFLAGS) $(LIBXMLXX_EXTRA_INCLUDES)

# We build xml++-vc$(VSVER_LIB)-$(LIBXMLXX_MAJOR_VERSION)_$(LIBXMLXX_MINOR_VERSION).dll or
#          xml++-vc$(VSVER_LIB)-d-$(LIBXMLXX_MAJOR_VERSION)_$(LIBXMLXX_MINOR_VERSION).dll at least

!if "$(USE_COMPAT_LIBS)" != ""
VSVER_LIB = $(VSVER)0
MSVC_VSVER_LIB =
!else
VSVER_LIB = $(PDBVER)$(VSVER_SUFFIX)
MSVC_VSVER_LIB = -vc$(VSVER_LIB)
!endif

!ifdef USE_MESON_LIBS
LIBXMLXX_LIBNAME = xml++$(MSVC_VSVER_LIB)-$(LIBXMLXX_MAJOR_VERSION).$(LIBXMLXX_MINOR_VERSION)
LIBXMLXX_DLLNAME = $(LIBXMLXX_LIBNAME)-1
!else
LIBXMLXX_LIBNAME = xml++-vc$(VSVER_LIB)$(DEBUG_SUFFIX)-$(LIBXMLXX_MAJOR_VERSION)_$(LIBXMLXX_MINOR_VERSION)
LIBXMLXX_DLLNAME = $(LIBXMLXX_LIBNAME)
!endif

LIBXMLXX_DLL = vs$(VSVER)\$(CFG)\$(PLAT)\$(LIBXMLXX_DLLNAME).dll
LIBXMLXX_LIB = vs$(VSVER)\$(CFG)\$(PLAT)\$(LIBXMLXX_LIBNAME).lib

LIBXML2_LIBS = libxml2.lib
