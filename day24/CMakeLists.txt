cmake_minimum_required(VERSION 3.10)

include_directories(${PROJECT_SOURCE_DIR}/helper_functions ${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/helper_functions)

add_executable(day24 day24.cpp)

target_link_libraries(day24 helper_functions)
