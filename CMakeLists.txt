cmake_minimum_required( VERSION 3.5 )

project( EUTF VERSION 1.4 )

set( EUTF_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/ )
set( EUTF_HEADER ${EUTF_INCLUDE_DIR}/EUTF.hpp )

set( EUTF_BUILD_TESTS ON )

if( EUTF_BUILD_TESTS )
    #add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/simple_setup/ )
	#add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/tests_in_different_files/ )
	#add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/one_line_test_suite/ )
	#add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/section_test/ )
	#add_subdirectory( ${PROJECT_SOURCE_DIR}/examples/sorting/ )
    set( TEST_SRC ${CMAKE_CURRENT_SOURCE_DIR}/examples/new/basic_test.cpp )

    add_executable( eutf_tests ${TEST_SRC} )
    target_include_directories( eutf_tests PUBLIC ${EUTF_INCLUDE_DIR} )
    target_link_libraries( eutf_tests PUBLIC pthread )
endif()

