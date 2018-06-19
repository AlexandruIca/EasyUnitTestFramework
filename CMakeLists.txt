cmake_minimum_required( VERSION 3.5 )

project( EUTF VERSION 1.3 )

set( EUTF_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/src/ )
set( EUTF_HEADER ${PROJECT_SOURCE_DIR}/src/EUTF.hpp )

if( EUTF_BUILD_TESTS )
	add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/simple_setup/ )
	add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/tests_in_different_files/ )
	add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/one_line_test_suite/ )
	add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/section_test/ )
	add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/sorting/ )
endif()

#
# These will probably be used in the future for xml and json output
# For now they are useless since the library is header only
#
# add_library( EUTF_lib STATIC ${PROJECT_SOURCE_DIR}/src/EUTF.cpp ${PROJECT_SOURCE_DIR}/src/EUTF.hpp )
# target_include_directories( EUTF_lib PUBLIC ${EUTF_INCLUDE_DIR} )

