cmake_minimum_required(VERSION 3.10)

project(shortest-path-visulization-sdl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

file(GLOB SOURCES *.cc)
add_executable(shortest-path-visulization-sdl ${SOURCES})

add_library(argparse INTERFACE)
target_include_directories(argparse INTERFACE 3rd-party)

find_package(SDL2_image)
find_package(SDL2_ttf)
find_package(SDL2)
find_package(spdlog)
target_link_libraries(shortest-path-visulization-sdl SDL2_image::SDL2_image
    sdl_ttf::sdl_ttf SDL2::SDL2main spdlog::spdlog argparse)
