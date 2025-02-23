#include "input/input.h"

#include "SDL3/SDL.h"
#include "ImGui/imgui.h"

static struct InputState
{
	float mousePosX = 0.f;
	float mousePosY = 0.f;
	SDL_MouseButtonFlags mouseState = 0;
	bool hoveringOverUI = false;
	const bool* keyboardState = nullptr;
} inputState;

namespace Terraria
{
	void PollInput(bool logFPS)
	{
		// Update SDL related input
		inputState.mouseState = SDL_GetMouseState(&inputState.mousePosX, &inputState.mousePosY);
		inputState.keyboardState = SDL_GetKeyboardState(NULL);

		// Update ImGui related input
		auto io = ImGui::GetIO();
		inputState.hoveringOverUI = io.WantCaptureMouse;
		if (logFPS) SDL_Log("%f", io.Framerate);
	}

	bool Terraria::GetMouseButtonDown(MouseButton button, bool checkAgainstUI)
	{
		if (checkAgainstUI && inputState.hoveringOverUI) return false;
		return inputState.mouseState & (button + 1); // SDL Button codes are 1 more than ImGui and ours
	}

	bool GetKeyDown(int key)
	{
		if (inputState.keyboardState == nullptr) return false;
		return inputState.keyboardState[key];
	}

	void GetMousePosition(float& x, float& y)
	{
		x = inputState.mousePosX;
		y = inputState.mousePosY;
	}

}
