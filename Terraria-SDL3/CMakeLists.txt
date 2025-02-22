cmake_minimum_required (VERSION 3.8)

project(Terraria)

add_executable(Terraria src/main.cpp
"src/terraria.h"
"src/resourcemanager.h"
"src/resourcemanager.cpp"
"src/world/world.h"
"src/world/world.cpp"
"src/entity/character.h"
"src/entity/character.cpp"
"src/helper/conversion.h"
"src/helper/conversion.cpp"
"src/user_interface/imguihelper.h"
"src/user_interface/imguihelper.cpp"

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