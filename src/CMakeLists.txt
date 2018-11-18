cmake_minimum_required(VERSION 3.2)
project(cmc_cg_template_src)

add_executable(cmc_cg
        main.cpp
        )

target_sources(cmc_cg PRIVATE
        imgui_impl/imgui_impl_sdl.cpp
        imgui_impl/imgui_impl_opengl3.cpp
        )


if (WIN32 AND MINGW)
    target_link_libraries(cmc_cg PRIVATE
            mingw32
            )
endif()

target_link_libraries(cmc_cg PRIVATE
        SDL2::SDL2
        glbinding::glbinding
        glbinding::glbinding-aux
        imgui::imgui
        )
# glbinding messes up with output paths, so we have to copy the resulting .dll by hand
# Using static linkage made build times unbearable, absolutely not suitable for rapid prototyping
if (TARGET glbinding)
    add_custom_command(TARGET cmc_cg POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glbinding> ${LIBRARY_OUTPUT_PATH}
            )
endif()
if (TARGET glbinding-aux)
    add_custom_command(TARGET cmc_cg POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:glbinding-aux> ${LIBRARY_OUTPUT_PATH}
            )
endif()

# Add shader checking as a dependency
add_dependencies(cmc_cg Shaders)