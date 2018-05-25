project( Output_File )

add_executable( Output_File ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/../../src/EUTF.cpp )

target_include_directories( Output_File PRIVATE ${PROJECT_SOURCE_DIR}/../../src/ )

