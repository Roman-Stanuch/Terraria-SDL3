cmake_minimum_required (VERSION 3.8)

project(Terraria)

add_executable(Terraria src/main.cpp)

target_link_libraries(Terraria
    PRIVATE 
        SDL3
)

target_include_directories(Terraria
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/vendor/includes
)