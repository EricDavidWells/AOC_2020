cmake_minimum_required(VERSION 3.10)

include_directories(${PROJECT_SOURCE_DIR}/helper_functions ${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/helper_functions)

add_executable(day20 day20.cpp)

target_link_libraries(day20 helper_functions)
