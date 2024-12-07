cmake_minimum_required(VERSION 3.10)
project(TelltaleHydra)

set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCES
    src/main.cpp
)

add_executable(hydra ${SOURCES})
target_compile_options(hydra PRIVATE -Wall)
target_include_directories(hydra PRIVATE include)