cmake_minimum_required(VERSION 3.10)

include_directories(${PROJECT_SOURCE_DIR}/helper_functions)
link_directories(${PROJECT_SOURCE_DIR}/helper_functions)

add_executable(day13 day13.cpp)

target_link_libraries(day13 helper_functions)
set_property(TARGET day13 PROPERTY CXX_STANDARD 17)
