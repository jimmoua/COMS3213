project(AVL)

file(GLOB sources *.cpp)

add_executable(run ${sources})

add_definitions("-Wfatal-errors -std=c++11")
