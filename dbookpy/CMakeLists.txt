# dbookpy build system
# $Id$

PROJECT(dbookpy)
SET(CMAKE_VERBOSE_MAKEFILE ON)
OPTION(BUILD_SHARED_LIBS "turn OFF for .a libs" ON)

# Standard places we might find stuff
LINK_DIRECTORIES("${CMAKE_INSTALL_PREFIX}/lib")
INCLUDE_DIRECTORIES("${CMAKE_INSTALL_PREFIX}/include")

# Where we will find libdbook if not 'make installed'.
# This assumes the build was done in a 'build/' directory
LINK_DIRECTORIES("../../libdbook/build/src/")
INCLUDE_DIRECTORIES("../libdbook/src")

# Find Python
FIND_PACKAGE(PythonInterp)
FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES("${PYTHON_INCLUDE_PATH}")

ADD_LIBRARY(dbookpy dbookpy)
SET_TARGET_PROPERTIES(dbookpy PROPERTIES LINKER_LANGUAGE C)
TARGET_LINK_LIBRARIES(dbookpy dbook)
SET_TARGET_PROPERTIES(dbookpy
PROPERTIES
        SOVERSION 0.1
        VERSION 0.1
)

# Rename library properly. Can't just copy!!!
GET_TARGET_PROPERTY(LIB_NAME dbookpy LOCATION)
ADD_CUSTOM_COMMAND(
	TARGET dbookpy 
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy ${LIB_NAME} dbookpy.so
	COMMAND rm libdbookpy.so*
)
