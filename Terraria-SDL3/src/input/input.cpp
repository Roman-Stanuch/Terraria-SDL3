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
		
		uint8_t mouseButtonMask = 0;
		switch (button)
		{
		case MouseButtonLeft:
			mouseButtonMask = SDL_BUTTON_LMASK;
			break;
		case MouseButtonMiddle:
			mouseButtonMask = SDL_BUTTON_MMASK;
			break;
		case MouseButtonRight:
			mouseButtonMask = SDL_BUTTON_RMASK;
			break;
		}

		return inputState.mouseState & mouseButtonMask;
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
