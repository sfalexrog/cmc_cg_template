cmake_minimum_required(VERSION 3.2)
project(cmc_cg_vendor)

add_subdirectory(SDL2)

add_library(_SDL2_LIB INTERFACE)
target_link_libraries(_SDL2_LIB INTERFACE SDL2main SDL2)
add_library(SDL2::SDL2 ALIAS _SDL2_LIB)

# Build glbinding as a shared library, since it's quite large and static linkage increases build times considerably
set(BUILD_SHARED_LIBS ON)
add_subdirectory(glbinding)
add_library(glbinding::glbinding ALIAS glbinding)
add_library(glbinding::glbinding-aux ALIAS glbinding-aux)

add_subdirectory(glm)
add_library(glm::glm ALIAS glm)

# RapidJSON's CMakeLists.txt does not help much, unfortunately
#add_subdirectory(rapidjson)
add_library(rapidjson INTERFACE)
target_include_directories(rapidjson INTERFACE rapidjson/include)
add_library(rapidjson::rapidjson ALIAS rapidjson)

# Having SKIP_GLSLANG_INSTALL defaulted to OFF breaks our config/build process
set(SKIP_GLSLANG_INSTALL ON)
# BUILD_SHARED_LIBS is set by glbinding to ON, which breaks glslang build process
set(BUILD_SHARED_LIBS OFF)
add_subdirectory(glslang)

# dear imgui does not provide a CMake project, but is very compact, so it's not a big deal to include it here
add_library(imgui STATIC
        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        )
target_include_directories(imgui PUBLIC
        imgui
        )

add_library(imgui::imgui ALIAS imgui)