cmake_minimum_required( VERSION 3.5 )

project( EUTF_Usage )

set( CMAKE_CXX_STANDARD 11 )

#
# Let's say we want to build the tests
#
# Otherwise set EUTF_BUILD_TESTS to OFF
#
set( EUTF_BUILD_TESTS ON )
add_subdirectory( ${PROJECT_SOURCE_DIR}/dependencies/EUTF/ )

add_executable( EUTF_Usage ${PROJECT_SOURCE_DIR}/main.cpp ${EUTF_HEADER} )
target_include_directories( EUTF_Usage PRIVATE ${EUTF_INCLUDE_DIR} )
target_link_libraries( EUTF_Usage EUTF_lib )

