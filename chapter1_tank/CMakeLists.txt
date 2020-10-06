cmake_minimum_required(VERSION 3.0)

project(Tank_test CXX)

add_library(Tank tank.cpp)
add_executable(Tank_test main.cpp)
target_link_libraries(Tank_test Tank)