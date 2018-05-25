project( Test_In_Different_Files )

add_executable( Test_In_Different_Files ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/test_sample.cpp ${PROJECT_SOURCE_DIR}/test_sample.hpp ${PROJECT_SOURCE_DIR}/../../src/EUTF.cpp )

target_include_directories( Test_In_Different_Files PRIVATE ${PROJECT_SOURCE_DIR}/../../src/ )

