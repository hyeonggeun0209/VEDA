project(my_project)
cmake_minimum_required(VERSION 3.10)

include_directories(inc)
add_subdirectory(src)
add_subdirectory(lib)

add_dependencies(server community cast vector_cast vector_viewer viewer common)
add_dependencies(client community common)
