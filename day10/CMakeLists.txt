cmake_minimum_required(VERSION 3.10)

include_directories(${PROJECT_SOURCE_DIR}/helper_functions)
link_directories(${PROJECT_SOURCE_DIR}/helper_functions)

add_executable(${PROJECT_NAME}_day10 day10.cpp)
target_link_libraries(${PROJECT_NAME}_day10 helper_functions)
