cmake_minimum_required( VERSION 3.5 )

project( EUTF VERSION 1.0 )

set( EUTF_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/ )
set( EUTF_HEADER ${PROJECT_SOURCE_DIR}/src/EUTF.hpp )

if( EUTF_BUILD_TESTS )
	add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/simple_setup/ )
	add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/tests_in_different_files/ )
	add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/one_line_test_suite/ )
endif()

add_library( EUTF_lib STATIC ${PROJECT_SOURCE_DIR}/src/EUTF.cpp ${PROJECT_SOURCE_DIR}/src/EUTF.hpp )
target_include_directories( EUTF_lib PUBLIC ${EUTF_INCLUDE_DIR} )

