#pragma once

#include "ImGui/imgui.h"

namespace Terraria
{
	static constexpr auto DEFAULT_ITEM_BOX_COLOR = ImVec4(0.25f, 0.27f, 0.67f, 0.9f);
	static constexpr auto DEFAULT_SELECTED_ITEM_BOX_COLOR = ImVec4(0.91f, 0.84f, 0.07f, 1.f);

	// Draws the item bar with each box being itemBoxSize in width and height. The box at selectedItemIndex will be colored yellow.
	// No box will be yellow if the selectedItemIndex is outside the range 0-9.
	void DrawItemBar(float itemBoxSize, bool& openBool, int selectedItemIndex = -1, const ImVec4& itemBoxColor = DEFAULT_ITEM_BOX_COLOR);
}