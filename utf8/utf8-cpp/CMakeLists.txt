cmake_minimum_required(VERSION 3.10)

project(test)

set(CMAKE_CXX_STANDARD 11)

add_executable(test test.cc utf8.cc)
