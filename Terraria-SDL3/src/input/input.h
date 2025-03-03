#pragma once

#include <cstdint>

namespace Terraria
{
	enum MouseButton : uint8_t
	{
		MouseButtonLeft = 0,
		MouseButtonRight = 1,
		MouseButtonMiddle = 2
	};

	enum MouseScroll : uint8_t
	{
		MouseScrollUp = 0,
		MouseScrollDown = 1
	};

	struct InputState
	{
		// Keyboard input
		const bool* keyboardState = nullptr;

		// Mouse Input
		float mousePosX = 0.f;
		float mousePosY = 0.f;
		uint32_t mouseState = 0;
		bool scrolledThisFrame = false;
		bool scrollingUp = false;
		bool scrollingDown = false;
		bool hoveringOverUI = false;
	};

	// Updates the input state. Must be called every frame.
	void PollInput(InputState& inputState, bool logFPS = false);

	// Updates the input state with new scroll values. Called from the SDL event handler.
	void UpdateMouseScroll(InputState& inputState, float amount);

	// Returns true if the given mouse button is pressed. Enabling checkAgainstUI will return false if the player is hovering
	// over an ImGui element.
	bool GetMouseButtonDown(const InputState& inputState, MouseButton button, bool checkAgainstUI = false);

	bool GetMouseScroll(const InputState& inputState, MouseScroll direction);

	// Returns true if the given key is pressed. Uses SDL_SCANCODE_x for keys.
	bool GetKeyDown(const InputState& inputState, int key);

	void GetMousePosition(const InputState& inputState, float& x, float& y);
}
