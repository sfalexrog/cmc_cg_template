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

# glm is a header-only library, no need to include it as a subdirectory
# (also, it seems to break some things)
#add_subdirectory(glm)
add_library(glm INTERFACE)
target_include_directories(glm INTERFACE glm)
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
target_compile_definitions(imgui PUBLIC
        IMGUI_DISABLE_OBSOLETE_FUNCTIONS
        )

add_library(imgui::imgui ALIAS imgui)

# Add assimp library
# Build it as a shared library (because link times are not fun)
set(BUILD_SHARED_LIBS ON)
# Disable some of the unused importers (fails to build on windows due to string table limitations)
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF)
set(ASSIMP_BUILD_OBJ_IMPORTER ON)
add_subdirectory(assimp)
