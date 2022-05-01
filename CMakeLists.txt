cmake_minimum_required(VERSION 3.23.1)

project(Ascii-Graphics)

add_executable(${PROJECT_NAME} ascii-graphics.cpp)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} agm)
target_link_libraries(${PROJECT_NAME} Camera)
target_link_libraries(${PROJECT_NAME} Lights)
target_link_libraries(${PROJECT_NAME} Mesh)
target_link_libraries(${PROJECT_NAME} Screen)

