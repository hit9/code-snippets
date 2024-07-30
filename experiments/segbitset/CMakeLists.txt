cmake_minimum_required(VERSION 3.10)

project(segbitset)

option(SEGBITSET_TEST "Enables testing" OFF)

add_library(segbitset INTERFACE)
set_target_properties(segbitset PROPERTIES PUBLIC_HEADER "segbitset.h")

if(SEGBITSET_TEST)
    enable_testing()
    find_package(Catch2 CONFIG REQUIRED)
    add_executable(segbitset_tests segbitset_test.cc)
    add_executable(segbitset_benchmark segbitset_benchmark.cc)
    target_link_libraries(segbitset_tests PRIVATE Catch2::Catch2WithMain)
    target_link_libraries(segbitset_benchmark PRIVATE Catch2::Catch2WithMain)
    include(CTest)
    include(Catch)
    catch_discover_tests(segbitset_tests)
endif()

install(
    TARGETS segbitset
    LIBRARY DESTINATION ${CMAK_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
