project( Simple_Setup )

add_executable( Simple_Setup ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/../../src/EUTF.cpp )

target_include_directories( Simple_Setup PRIVATE ${PROJECT_SOURCE_DIR}/../../src/ )

