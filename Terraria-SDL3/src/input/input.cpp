#include "input/input.h"

#include "SDL3/SDL.h"
#include "ImGui/imgui.h"

#include <cmath>

static constexpr float MIN_SCROLL = 0.01f;

static struct InputState
{
	// Mouse Input
	float mousePosX = 0.f;
	float mousePosY = 0.f;
	SDL_MouseButtonFlags mouseState = 0;
	bool scrolledThisFrame = false;
	bool scrollingUp = false;
	bool scrollingDown = false;
	bool hoveringOverUI = false;

	// Keyboard input
	const bool* keyboardState = nullptr;
} inputState;

namespace Terraria
{
	void PollInput(const bool logFPS)
	{
		// Update SDL related input
		inputState.mouseState = SDL_GetMouseState(&inputState.mousePosX, &inputState.mousePosY);
		inputState.keyboardState = SDL_GetKeyboardState(nullptr);
		if (!inputState.scrolledThisFrame)
			UpdateMouseScroll(0.f);
		else
			inputState.scrolledThisFrame = false;

		// Update ImGui related input
		const auto io = ImGui::GetIO();
		inputState.hoveringOverUI = io.WantCaptureMouse;
		if (logFPS) SDL_Log("%f", io.Framerate);
	}

	void UpdateMouseScroll(const float amount)
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

	bool GetMouseButtonDown(const MouseButton button, const bool checkAgainstUI)
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

	bool GetMouseScroll(const MouseScroll direction)
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

	bool GetKeyDown(const int key)
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
