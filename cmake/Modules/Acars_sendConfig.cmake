INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_ACARS_SEND Acars_send)

FIND_PATH(
    ACARS_SEND_INCLUDE_DIRS
    NAMES Acars_send/api.h
    HINTS $ENV{ACARS_SEND_DIR}/include
        ${PC_ACARS_SEND_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    ACARS_SEND_LIBRARIES
    NAMES gnuradio-Acars_send
    HINTS $ENV{ACARS_SEND_DIR}/lib
        ${PC_ACARS_SEND_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ACARS_SEND DEFAULT_MSG ACARS_SEND_LIBRARIES ACARS_SEND_INCLUDE_DIRS)
MARK_AS_ADVANCED(ACARS_SEND_LIBRARIES ACARS_SEND_INCLUDE_DIRS)

