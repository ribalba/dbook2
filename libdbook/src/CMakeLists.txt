# LIBDBOOK2 build system
# $Id$

# libdistdbook is disabled in the build until someone fixes it
OPTION(BUILD_SHARED_LIBS "turn OFF for .a libs" ON)
ADD_LIBRARY(dbook libdbook liblocaldbook) # libdistdbook
SET_TARGET_PROPERTIES(dbook PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(dbook 
PROPERTIES
	SOVERSION 0.1
	VERSION 0.1
)

INSTALL(FILES libdbook.h DESTINATION include)

INSTALL(TARGETS dbook
	LIBRARY DESTINATION lib
)

