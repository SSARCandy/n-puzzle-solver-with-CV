cmake_minimum_required(VERSION 3.0)

project( n-puzzle-solver-with-CV )

find_package( OpenCV REQUIRED )


FIND_PACKAGE(wxWidgets REQUIRED)
INCLUDE(${wxWidgets_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable( N-puzzleSolver
"${PROJECT_SOURCE_DIR}/src/main.cpp" 
"${PROJECT_SOURCE_DIR}/src/gui.cpp"  
"${PROJECT_SOURCE_DIR}/src/puzzle.cpp"  
"${PROJECT_SOURCE_DIR}/src/analyzePuzzle.cpp"  
"${PROJECT_SOURCE_DIR}/include/gui.h" 
"${PROJECT_SOURCE_DIR}/include/analyzePuzzle.h" 
"${PROJECT_SOURCE_DIR}/include/puzzle.h" 
)

target_link_libraries( N-puzzleSolver ${OpenCV_LIBS} ${wxWidgets_LIBRARIES} )