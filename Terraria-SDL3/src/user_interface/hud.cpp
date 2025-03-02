#include "hud.h"

namespace Terraria
{
	void DrawItemBar(const float itemBoxSize, bool& openBool, const int selectedItemIndex, const ImVec4& itemBoxColor)
	{
		ImGui::SetNextWindowPos(ImVec2(0.f, 0.f));
		ImGui::Begin(
			"Hotbar",
			&openBool,
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBackground |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_AlwaysAutoResize
		);

		const auto itemBoxSizeVector = ImVec2(itemBoxSize, itemBoxSize);
		for (int i = 0; i < 10; i++)
		{
			if (i != 0) ImGui::SameLine();
			ImGui::PushID(i);

			ImVec4 finalColor = (i == selectedItemIndex) ? DEFAULT_SELECTED_ITEM_BOX_COLOR : itemBoxColor;
			ImGui::PushStyleColor(ImGuiCol_Button, finalColor);
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, finalColor);
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, finalColor);

			ImGui::Button("Item", itemBoxSizeVector);

			ImGui::PopStyleColor(3);
			ImGui::PopID();
		}
	}
}