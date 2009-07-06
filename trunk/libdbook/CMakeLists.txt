# LIBDBOOK2 build system
# $Id$

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

PROJECT(libdbook)

LINK_DIRECTORIES(
    "${CMAKE_INSTALL_PREFIX}/lib"
    "/usr/local/lib"
    "/usr/lib"
)

FIND_PACKAGE(LibXml2)

INCLUDE_DIRECTORIES(
    "${CMAKE_INSTALL_PREFIX}/include"
    "${LIBXML2_INCLUDE_DIR}"
)

# XXX when you break the build system, set this
#SET(CMAKE_VERBOSE_MAKEFILE ON)

SET(CMAKE_C_FLAGS -Wall)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(dbook-tool)

