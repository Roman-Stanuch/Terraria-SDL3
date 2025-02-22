#include "imguihelper.h"

#include "SDL3/SDL.h"

namespace Terraria
{
	void InitializeImGui(SDL_Window* sdlWindow, SDL_Renderer* sdlRenderer)
	{
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();

        ImGui_ImplSDL3_InitForSDLRenderer(sdlWindow, sdlRenderer);
        ImGui_ImplSDLRenderer3_Init(sdlRenderer);
	}

    void DeinitializeImGui()
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }
}