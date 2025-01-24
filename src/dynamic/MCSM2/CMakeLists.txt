add_library(mcsm2)
add_subdirectory(src)
target_include_directories(mcsm2 PRIVATE include)
target_include_directories(mcsm2 PRIVATE ../../../include)