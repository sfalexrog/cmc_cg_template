cmake_minimum_required(VERSION 3.1)
project(cmc_cg_template)

set(CMAKE_CXX_STANDARD 14)

# Thanks, Windows!
if (WIN32)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
    set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
endif()

add_subdirectory(vendor)
# Validate shaders on build
add_subdirectory(data)
add_subdirectory(src)