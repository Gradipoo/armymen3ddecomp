cmake_minimum_required(VERSION 3.16)

project(am3d LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(am3d_exe STATIC components/exe/load.cpp)
target_include_directories(am3d_exe PUBLIC components/exe)

add_library(am3d_input STATIC components/input/keyboard.cpp)
target_include_directories(am3d_input PUBLIC components/input)

add_library(am3d_net STATIC components/net/browser.cpp)
target_include_directories(am3d_net PUBLIC components/net)

add_library(am3d_mods STATIC components/mods/overlay.cpp)
target_include_directories(am3d_mods PUBLIC components/mods)

add_executable(am3d src/main.cpp)
target_link_libraries(am3d PRIVATE am3d_exe am3d_input am3d_net am3d_mods)
