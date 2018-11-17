cmake_minimum_required(VERSION 3.2)
project(cmc_cg_vendor)

add_subdirectory(SDL2)

add_library(_SDL2_LIB INTERFACE)
target_link_libraries(_SDL2_LIB INTERFACE SDL2main SDL2)
add_library(SDL2::SDL2 ALIAS _SDL2_LIB)

add_subdirectory(glbinding)
add_subdirectory(glm)
add_library(glm::glm ALIAS glm)

# RapidJSON's CMakeLists.txt does not help much, unfortunately
#add_subdirectory(rapidjson)
add_library(rapidjson INTERFACE)
target_include_directories(rapidjson INTERFACE rapidjson/include)
add_library(rapidjson::rapidjson ALIAS rapidjson)

# Having SKIP_GLSLANG_INSTALL defaulted to OFF breaks our config/build process
set(SKIP_GLSLANG_INSTALL ON)
add_subdirectory(glslang)

