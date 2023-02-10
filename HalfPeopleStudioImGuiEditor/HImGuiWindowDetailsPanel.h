#pragma once
#include "HImGuiWindows.h"

namespace WindowDetailsPanelSave
{

}

static void DrawWindowDetailsPanel()
{
	if (ImGui::Begin("WindowDetailsPanel"))
	{
		ImGui::InputText("WindowTitle", ImGuiWindows.at(SelectHImGuiWindows)->Title,120);

		ImGui::Checkbox("HaveClose", &ImGuiWindows.at(SelectHImGuiWindows)->HaveClose);
		if (ImGuiWindows.at(SelectHImGuiWindows)->HaveClose) {
			ImGui::Checkbox("DefaultOpen", &ImGuiWindows.at(SelectHImGuiWindows)->DefaultOpen);
			if (!ImGuiWindows.at(SelectHImGuiWindows)->Visible)
				if (ImGui::Button("(for debug) SetVisible"))
					ImGuiWindows.at(SelectHImGuiWindows)->Visible = true;
		}


		if (ImGui::TreeNode("Flags"))
		{
			ImGui::CheckboxFlags("None                     ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_None);
			ImGui::CheckboxFlags("NoTitleBar               ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoTitleBar);
			ImGui::CheckboxFlags("NoResize                 ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoResize);
			ImGui::CheckboxFlags("NoMove                   ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoMove);
			ImGui::CheckboxFlags("NoScrollbar              ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoScrollbar);
			ImGui::CheckboxFlags("NoScrollWithMouse        ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoScrollWithMouse);
			ImGui::CheckboxFlags("NoCollapse               ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoCollapse);
			ImGui::CheckboxFlags("AlwaysAutoResize         ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::CheckboxFlags("NoBackground             ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoBackground);
			ImGui::CheckboxFlags("NoSavedSettings          ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoSavedSettings);
			ImGui::CheckboxFlags("NoMouseInputs            ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoMouseInputs);
			ImGui::CheckboxFlags("MenuBar                  ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_MenuBar);
			ImGui::CheckboxFlags("HorizontalScrollbar      ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_HorizontalScrollbar);
			ImGui::CheckboxFlags("NoFocusOnAppearing       ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoFocusOnAppearing);
			ImGui::CheckboxFlags("NoBringToFrontOnFocus    ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoBringToFrontOnFocus);
			ImGui::CheckboxFlags("AlwaysVerticalScrollbar  ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_AlwaysVerticalScrollbar);
			ImGui::CheckboxFlags("AlwaysHorizontalScrollbar", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
			ImGui::CheckboxFlags("AlwaysUseWindowPadding   ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_AlwaysUseWindowPadding);
			ImGui::CheckboxFlags("NoNavInputs              ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoNavInputs);
			ImGui::CheckboxFlags("NoNavFocus               ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoNavFocus);
			ImGui::CheckboxFlags("UnsavedDocument          ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_UnsavedDocument);
			ImGui::CheckboxFlags("NoDocking                ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoDocking);
			ImGui::TreePop();
		}
	}
	ImGui::End();
}