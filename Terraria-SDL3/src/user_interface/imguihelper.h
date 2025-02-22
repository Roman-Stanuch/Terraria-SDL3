#pragma once

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_sdl3.h"
#include "ImGui/imgui_impl_sdlrenderer3.h"

struct SDL_Window;
struct SDL_Renderer;

namespace Terraria
{
	void InitializeImGui(SDL_Window* sdlWindow, SDL_Renderer* sdlRenderer);
	void DeinitializeImGui();
}