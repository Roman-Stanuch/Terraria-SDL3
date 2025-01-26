cmake_minimum_required (VERSION 3.8)

project(Terraria)

add_executable(Terraria src/main.cpp "src/texture.h" "src/texture.cpp" "src/terraria.h" )

target_link_libraries(Terraria
    PRIVATE 
        #SDL3
        #SDL3_image
        ../../../vendor/libraries/SDL3/SDL3
        ../../../vendor/libraries/SDL3/SDL3_image
)

target_include_directories(Terraria
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/vendor/includes
)