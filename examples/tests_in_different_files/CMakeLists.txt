project( Tests_In_Different_Files )

#set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -E" )

add_executable( Tests_In_Different_Files ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/test_sample.cpp ${PROJECT_SOURCE_DIR}/test_sample.hpp )

target_include_directories( Tests_In_Different_Files PRIVATE ${PROJECT_SOURCE_DIR}/../../src/ )

