cmake_minimum_required(VERSION 3.2)
project(cmc_cg_template_src)

add_executable(cmc_cg
        main.cpp
        )

if (WIN32 AND MINGW)
    target_link_libraries(cmc_cg PRIVATE
            mingw32
            )
endif()

target_link_libraries(cmc_cg PRIVATE
        SDL2::SDL2
        )
