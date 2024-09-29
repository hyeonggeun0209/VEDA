add_executable(server server.cpp)
add_executable(client client.cpp)

target_link_libraries(client community common)
install(TARGETS client
RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin)

target_link_libraries(server community cast common vector_cast vector_viewer viewer)
install(TARGETS server
RUNTIME DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../bin)
