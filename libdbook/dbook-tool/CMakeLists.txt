FIND_PACKAGE(LibXml2)

# XXX proper -L/path/to/libs

INCLUDE_DIRECTORIES(
    "${CMAKE_INSTALL_PREFIX}/include"
    "${LIBXML2_INCLUDE_DIR}"
)


ADD_EXECUTABLE(dbook-tool dbook-tool.c)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src) 
TARGET_LINK_LIBRARIES(dbook-tool dbook xml2)

INSTALL(TARGETS dbook-tool
        RUNTIME DESTINATION bin
)

