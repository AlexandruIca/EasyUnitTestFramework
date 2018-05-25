project( One_Line_Test_Suite )

add_executable( One_Line_Test_Suite ${PROJECT_SOURCE_DIR}/../../src/EUTF.cpp 
		                    ${PROJECT_SOURCE_DIR}/main.cpp )

target_include_directories( One_Line_Test_Suite PRIVATE ${PROJECT_SOURCE_DIR}/../../src/ )

