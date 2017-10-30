# ============================================================================
#  Name	 : build_help.mk
#  Part of  : Ellipse
# ============================================================================
#  Name	 : build_help.mk
#  Part of  : Ellipse
#
#  Description: This make file will build the application help file (.hlp)
# 
# ============================================================================

do_nothing :
	@rem do_nothing

# build the help from the MAKMAKE step so the header file generated
# will be found by cpp.exe when calculating the dependency information
# in the mmp makefiles.

MAKMAKE : Ellipse_0xe8381f31.hlp
Ellipse_0xe8381f31.hlp : Ellipse.xml Ellipse.cshlp Custom.xml
	cshlpcmp.bat Ellipse.cshlp
ifeq (WINSCW,$(findstring WINSCW, $(PLATFORM)))
	md $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy Ellipse_0xe8381f31.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del Ellipse_0xe8381f31.hlp
	del Ellipse_0xe8381f31.hlp.hrh

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo Ellipse_0xe8381f31.hlp

FINAL : do_nothing
