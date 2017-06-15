# Copyright 2011,2012,2016 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
#
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.

########################################################################
# Setup library
########################################################################
include(GrPlatform) #define LIB_SUFFIX

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

list(APPEND Acars_send_sources
    acars_gen_impl.cc
)

set(Acars_send_sources "${Acars_send_sources}" PARENT_SCOPE)
if(NOT Acars_send_sources)
	MESSAGE(STATUS "No C++ sources... skipping lib/")
	return()
endif(NOT Acars_send_sources)

add_library(gnuradio-Acars_send SHARED ${Acars_send_sources})
target_link_libraries(gnuradio-Acars_send ${Boost_LIBRARIES} ${GNURADIO_ALL_LIBRARIES})
set_target_properties(gnuradio-Acars_send PROPERTIES DEFINE_SYMBOL "gnuradio_Acars_send_EXPORTS")

if(APPLE)
    set_target_properties(gnuradio-Acars_send PROPERTIES
        INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib"
    )
endif(APPLE)

########################################################################
# Install built library files
########################################################################
include(GrMiscUtils)
GR_LIBRARY_FOO(gnuradio-Acars_send RUNTIME_COMPONENT "Acars_send_runtime" DEVEL_COMPONENT "Acars_send_devel")

########################################################################
# Build and register unit test
########################################################################
include(GrTest)

include_directories(${CPPUNIT_INCLUDE_DIRS})

list(APPEND test_Acars_send_sources
    ${CMAKE_CURRENT_SOURCE_DIR}/test_Acars_send.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_Acars_send.cc
    ${CMAKE_CURRENT_SOURCE_DIR}/qa_acars_gen.cc
)

add_executable(test-Acars_send ${test_Acars_send_sources})

target_link_libraries(
  test-Acars_send
  ${GNURADIO_RUNTIME_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CPPUNIT_LIBRARIES}
  gnuradio-Acars_send
)

GR_ADD_TEST(test_Acars_send test-Acars_send)

########################################################################
# Print summary
########################################################################
message(STATUS "Using install prefix: ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Building for version: ${VERSION} / ${LIBVER}")

