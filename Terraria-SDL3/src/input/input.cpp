#include "input/input.h"

#include "SDL3/SDL.h"
#include "ImGui/imgui.h"

#include <cmath>

static constexpr float MIN_SCROLL = 0.01f;

namespace Terraria
{
	void PollInput(InputState& inputState, const bool logFPS)
	{
		// Update SDL related input
		inputState.mouseState = SDL_GetMouseState(&inputState.mousePosX, &inputState.mousePosY);
		inputState.keyboardState = SDL_GetKeyboardState(nullptr);
		if (!inputState.scrolledThisFrame)
			UpdateMouseScroll(inputState, 0.f);
		else
			inputState.scrolledThisFrame = false;

		// Update ImGui related input
		const auto io = ImGui::GetIO();
		inputState.hoveringOverUI = io.WantCaptureMouse;
		if (logFPS) SDL_Log("%f", io.Framerate);
	}

	void UpdateMouseScroll(InputState& inputState, const float amount)
	{
		if (abs(amount) < MIN_SCROLL)
		{
			inputState.scrollingUp = false;
			inputState.scrollingDown = false;
			return;
		}

		inputState.scrolledThisFrame = true;
		if (amount > 0)
		{
			inputState.scrollingUp = true;
			inputState.scrollingDown = false;
		}
		else if (amount < 0)
		{
			inputState.scrollingUp = false;
			inputState.scrollingDown = true;
		}
	}

	bool GetMouseButtonDown(const InputState& inputState, const MouseButton button, const bool checkAgainstUI)
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

	bool GetMouseScroll(const InputState& inputState, const MouseScroll direction)
	{
		switch (direction)
		{
		case MouseScrollUp:
			return inputState.scrollingUp;
			break;
		case MouseScrollDown:
			return inputState.scrollingDown;
			break;
		default:
			return false;
			break;
		}
	}

	bool GetKeyDown(const InputState& inputState, const int key)
	{
		if (inputState.keyboardState == nullptr) return false;
		return inputState.keyboardState[key];
	}

	void GetMousePosition(const InputState& inputState, float& x, float& y)
	{
		x = inputState.mousePosX;
		y = inputState.mousePosY;
	}
}
