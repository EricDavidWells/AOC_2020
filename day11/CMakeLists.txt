cmake_minimum_required(VERSION 3.10)

include_directories(${PROJECT_SOURCE_DIR}/helper_functions)
link_directories(${PROJECT_SOURCE_DIR}/helper_functions)

add_executable(day11 day11.cpp)
target_link_libraries(day11 helper_functions)
