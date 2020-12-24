cmake_minimum_required(VERSION 3.10)

include_directories(${PROJECT_SOURCE_DIR}/helper_functions)
link_directories(${PROJECT_SOURCE_DIR}/helper_functions)

add_executable(${PROJECT_NAME}_day08 day08.cpp)
target_link_libraries(${PROJECT_NAME}_day08 helper_functions)
