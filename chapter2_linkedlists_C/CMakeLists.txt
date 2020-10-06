cmake_minimum_required(VERSION 3.0)

project(linked_lists_test CXX)

# set(CMAKE_BUILD_TYPE Debug)

add_library(linked_lists linked_lists.cpp)
add_executable(linked_lists_test main.cpp)
target_link_libraries(linked_lists_test linked_lists)