cmake_minimum_required(VERSION 3.10)

project(test VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCE_FILES "*.cc" "*.hpp")
add_executable(regex_test ${SOURCE_FILES})
