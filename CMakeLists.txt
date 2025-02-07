cmake_minimum_required(VERSION 3.22)
project(TelltaleHydra)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

add_library(hydra)
add_subdirectory(src)
add_subdirectory(extern)


if(NOT DEFINED LOG_LEVEL)
    set(LOG_LEVEL 3)
endif()
target_compile_definitions(hydra PRIVATE TTE_LOG_LEVEL=${LOG_LEVEL})
target_compile_options(hydra PRIVATE -Wall)
target_include_directories(hydra PUBLIC include)
target_link_libraries(hydra twdde)

set (USE_ADDRESS_SANITIZER OFF CACHE BOOL "Should the Address Sanitizer tool be enabled?")
if (USE_ADDRESS_SANITIZER)
  target_compile_options(hydra PRIVATE -fsanitize=address)
  target_link_options(hydra PRIVATE -fsanitize=address)
endif()