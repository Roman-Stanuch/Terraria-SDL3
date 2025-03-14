﻿cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 17)

project(Terraria)

add_executable(Terraria src/main.cpp
 "src/terraria.h"
 "src/resource/resources.h"
 "src/resource/resources.cpp"
 "src/world/world.h"
 "src/world/world.cpp"
 "src/entity/character.h"
 "src/entity/character.cpp"
 "src/helper/conversion.h"
 "src/helper/conversion.cpp"
 "src/user_interface/imguihelper.h"
 "src/user_interface/imguihelper.cpp"
 "src/user_interface/hud.h" 
 "src/user_interface/hud.cpp"  
 "src/input/input.h" 
 "src/input/input.cpp" 

 "vendor/includes/ImGui/imconfig.h"
 "vendor/includes/ImGui/imgui.h"
 "vendor/includes/ImGui/imgui.cpp"
 "vendor/includes/ImGui/imgui_demo.cpp"
 "vendor/includes/ImGui/imgui_draw.cpp"
 "vendor/includes/ImGui/imgui_tables.cpp"
 "vendor/includes/ImGui/imgui_widgets.cpp"
 "vendor/includes/ImGui/imgui_impl_sdlrenderer3.h"
 "vendor/includes/ImGui/imgui_impl_sdlrenderer3.cpp"
 "vendor/includes/ImGui/imgui_impl_sdl3.h"
 "vendor/includes/ImGui/imgui_impl_sdl3.cpp"
 "vendor/includes/ImGui/imgui_internal.h"
 "vendor/includes/ImGui/imstb_rectpack.h"
 "vendor/includes/ImGui/imstb_textedit.h"
 "vendor/includes/ImGui/imstb_truetype.h"
)

find_library(SDL3 SDL3 vendor/libraries/SDL3)
find_library(SDL3_IMAGE SDL3_image vendor/libraries/SDL3)
target_link_libraries(Terraria
    PRIVATE
        ${SDL3}
        ${SDL3_IMAGE}
)

target_include_directories(Terraria
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/vendor/includes
)