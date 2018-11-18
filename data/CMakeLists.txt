# Create a "phony" target that will depend on our shaders being compiled
add_custom_target(Shaders)

if (TARGET glslangValidator)
    message(STATUS "Will perform shader validation")
    file(GLOB GLSL_SOURCE_FILES
            shaders/*.vert
            shaders/*.frag
            )
    foreach(GLSL ${GLSL_SOURCE_FILES})
        string(REGEX REPLACE "[/\\:]" "_" GLSL_SAFE ${GLSL})
        add_custom_target(Check_shader_${GLSL_SAFE}
                COMMAND glslangValidator ${GLSL}
                DEPENDS ${GLSL}
                )
        add_dependencies(Shaders Check_shader_${GLSL_SAFE})
    endforeach()
else()
    message(STATUS "Not validating shaders; consider including glslang as a dependency")
endif()