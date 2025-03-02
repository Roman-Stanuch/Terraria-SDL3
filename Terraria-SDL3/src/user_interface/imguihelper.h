#pragma once

#include "ImGui/imgui_impl_sdl3.h"

struct SDL_Window;
struct SDL_Renderer;

namespace Terraria
{
	void InitializeImGui(SDL_Window* sdlWindow, SDL_Renderer* sdlRenderer);
	void DeinitializeImGui();

	void StartImGuiFrameSDL();
	void EndImGuiFrameSDL(SDL_Renderer* sdlRenderer);
}