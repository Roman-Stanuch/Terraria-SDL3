#include "imguihelper.h"

#include "SDL3/SDL.h"

static const char* FONT_PATH = "../../../res/fonts/default.ttf";

namespace Terraria
{
	void InitializeImGui(SDL_Window* sdlWindow, SDL_Renderer* sdlRenderer)
	{
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_None;
        io.FontDefault = io.Fonts->AddFontFromFileTTF(FONT_PATH, 18.f);

        ImGui_ImplSDL3_InitForSDLRenderer(sdlWindow, sdlRenderer);
        ImGui_ImplSDLRenderer3_Init(sdlRenderer);
	}

    void DeinitializeImGui()
    {
        ImGui_ImplSDLRenderer3_Shutdown();
        ImGui_ImplSDL3_Shutdown();
        ImGui::DestroyContext();
    }

    void StartImGuiFrameSDL()
    {
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
    }

    void EndImGuiFrameSDL(SDL_Renderer* sdlRenderer)
    {
        ImGui::End();
        ImGui::Render();
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), sdlRenderer);
    }
}