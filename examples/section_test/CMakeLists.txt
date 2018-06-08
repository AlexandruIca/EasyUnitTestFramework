project( Section_Test )

add_executable( Section_Test ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/../../src/EUTF.hpp )

target_include_directories( Section_Test PRIVATE ${PROJECT_SOURCE_DIR}/../../src/ )
