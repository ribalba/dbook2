# LIBDBOOK2 build system
# $Id$

PROJECT(libdbook)

# XXX not right, work out how to do properly
LINK_DIRECTORIES(
    "${CMAKE_INSTALL_PREFIX}/lib"
    "/usr/local/lib"
    "/usr/lib"
)

#SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_C_FLAGS -Wall)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(dbook-tool)

