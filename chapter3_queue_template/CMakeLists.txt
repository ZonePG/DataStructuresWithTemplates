cmake_minimum_required(VERSION 3.0.0)
project(queue_test VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(queue_test main.cpp)
add_executable()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
