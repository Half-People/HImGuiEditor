#pragma once
#include "HWidget.h"
#include "MainMenuBar.h"
#include "HImGuiWindows.h"
#include <imgui.h>

ImTextureID DeleteIcon;

float Min(ImVec2 In)
{
	if (In.x > In.y)
		return In.y;
	return In.x;
}


static void DrawDeleteWidgetPanel()
{
	if (ImGui::Begin("DeleteWidgetPanel"))
	{
		ImVec2 ChildSize = ImGui::GetWindowSize();
		ChildSize.x -= 20;
		ChildSize.y -= 45;
		if (ImGui::BeginChild("DeleteWidgetPanelC", ChildSize))
		{
			int MinSize = Min(ChildSize);
			MinSize -= 200;
			if (MinSize > 20)
			{
				ImVec2 SaveWindowsSize = ImGui::GetWindowSize();
				ImGui::SetCursorPos(ImVec2((SaveWindowsSize.x - MinSize) / 2, (SaveWindowsSize.y - MinSize) / 2));
				ImGui::Image(DeleteIcon, ImVec2(MinSize, MinSize));
			}
		}
		ImGui::EndChild();
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragWidget"))
			{
				DeleteWidget(SelectWidget);
			}
			ImGui::EndDragDropTarget();
		}
	}
	ImGui::End();
}