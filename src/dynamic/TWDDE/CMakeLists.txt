add_library(twdde)
add_subdirectory(src)
target_include_directories(twdde PRIVATE include)
target_include_directories(twdde PRIVATE ../../../include)