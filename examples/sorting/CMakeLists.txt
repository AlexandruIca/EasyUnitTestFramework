project( Sorting )

add_executable( Sorting ${PROJECT_SOURCE_DIR}/main.cpp
			${PROJECT_SOURCE_DIR}/quicksort.hpp
			${PROJECT_SOURCE_DIR}/quicksort.cpp
		        ${PROJECT_SOURCE_DIR}/../../src/EUTF.hpp )

target_include_directories( Sorting PRIVATE ${PROJECT_SOURCE_DIR}/../../src/ )

