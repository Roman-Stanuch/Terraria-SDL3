#pragma once

namespace Terraria
{
	enum MouseButton
	{
		MouseButtonLeft = 0,
		MouseButtonRight = 1,
		MouseButtonMiddle = 2
	};

	enum MouseScroll
	{
		MouseScrollUp = 0,
		MouseScrollDown = 1
	};

	// Updates the input state. Must be called every frame.
	void PollInput(bool logFPS = false);

	// Updates the input state with new scroll values. Called from the SDL event handler.
	void UpdateMouseScroll(float amount);

	// Returns true if the given mouse button is pressed. Enabling checkAgainstUI will return false if the player is hovering
	// over an ImGui element.
	bool GetMouseButtonDown(MouseButton button, bool checkAgainstUI = false);

	bool GetMouseScroll(MouseScroll direction);

	// Returns true if the given key is pressed. Uses SDL_SCANCODE_x for keys.
	bool GetKeyDown(int key);

	void GetMousePosition(float& x, float& y);
}