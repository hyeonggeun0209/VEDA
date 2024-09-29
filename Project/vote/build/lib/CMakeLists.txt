add_library(cast STATIC cast.cpp)
add_library(common STATIC common.cpp)
add_library(vector_cast STATIC vector_cast.cpp)
add_library(vector_viewer STATIC vector_viewer.cpp)
add_library(viewer STATIC viewer.cpp)
add_library(community STATIC community.cpp)

install(TARGETS cast common vector_cast vector_viewer viewer community
ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../lib)

install(TARGETS common community
ARCHIVE DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
