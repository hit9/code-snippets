cmake_minimum_required(VERSION 3.10)
project(binarytree_tests CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Find or Download package Catch 2
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 # or a later release
  GIT_PROGRESS TRUE
  FIND_PACKAGE_ARGS NAMES Catch2)

FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

# Targets
file(GLOB TEST_SOURCES *_test.cc *_test.cpp)
add_executable(tests ${TEST_SOURCES} binarytree.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_custom_target(
  runtests
  COMMAND tests
  DEPENDS tests
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

include(CTest)
include(Catch)
catch_discover_tests(tests)
