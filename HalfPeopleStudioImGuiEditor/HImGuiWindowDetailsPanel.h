#pragma once
#include "HImGuiWindows.h"
#include "FlagsList.h"

namespace WindowDetailsPanelSave
{
	static std::string WindowDetailsPanel = "WindowDetailsPanel";
	static std::string WindowTitle = "WindowTitle";
	static std::string HaveClose = "HaveClose";
	static std::string DefaultOpen = "DefaultOpen";
	static std::string SetVisible = "(Debug) SetVisible";
}

#define InitWindowDetailsPanel TranslateObject.push_back(&WindowDetailsPanelSave::WindowDetailsPanel);\
TranslateObject.push_back(&WindowDetailsPanelSave::WindowTitle);\
TranslateObject.push_back(&WindowDetailsPanelSave::HaveClose);\
TranslateObject.push_back(&WindowDetailsPanelSave::DefaultOpen);\
TranslateObject.push_back(&WindowDetailsPanelSave::SetVisible);\

static void DrawWindowDetailsPanel()
{
	if (ImGui::Begin(std::string(WindowDetailsPanelSave::WindowDetailsPanel).append("###WindowDetailsPanel").c_str()))
	{
		ImGui::InputText(WindowDetailsPanelSave::WindowTitle.c_str(), ImGuiWindows.at(SelectHImGuiWindows)->Title,120);

		ImGui::Checkbox(WindowDetailsPanelSave::HaveClose.c_str(), &ImGuiWindows.at(SelectHImGuiWindows)->HaveClose);
		if (ImGuiWindows.at(SelectHImGuiWindows)->HaveClose) {
			ImGui::Checkbox(WindowDetailsPanelSave::DefaultOpen.c_str(), &ImGuiWindows.at(SelectHImGuiWindows)->DefaultOpen);
			if (!ImGuiWindows.at(SelectHImGuiWindows)->Visible)
				if (ImGui::Button(WindowDetailsPanelSave::SetVisible.c_str()))
					ImGuiWindows.at(SelectHImGuiWindows)->Visible = true;
		}



		DrawImGuiWindowFlagSetting(ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags);

		//if (ImGui::TreeNode("Flags"))
		//{
		//	ImGui::CheckboxFlags("None                     ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_None);
		//	ImGui::CheckboxFlags("NoTitleBar               ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoTitleBar);
		//	ImGui::CheckboxFlags("NoResize                 ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoResize);
		//	ImGui::CheckboxFlags("NoMove                   ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoMove);
		//	ImGui::CheckboxFlags("NoScrollbar              ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoScrollbar);
		//	ImGui::CheckboxFlags("NoScrollWithMouse        ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoScrollWithMouse);
		//	ImGui::CheckboxFlags("NoCollapse               ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoCollapse);
		//	ImGui::CheckboxFlags("AlwaysAutoResize         ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_AlwaysAutoResize);
		//	ImGui::CheckboxFlags("NoBackground             ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoBackground);
		//	ImGui::CheckboxFlags("NoSavedSettings          ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoSavedSettings);
		//	ImGui::CheckboxFlags("NoMouseInputs            ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoMouseInputs);
		//	ImGui::CheckboxFlags("MenuBar                  ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_MenuBar);
		//	ImGui::CheckboxFlags("HorizontalScrollbar      ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_HorizontalScrollbar);
		//	ImGui::CheckboxFlags("NoFocusOnAppearing       ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoFocusOnAppearing);
		//	ImGui::CheckboxFlags("NoBringToFrontOnFocus    ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoBringToFrontOnFocus);
		//	ImGui::CheckboxFlags("AlwaysVerticalScrollbar  ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_AlwaysVerticalScrollbar);
		//	ImGui::CheckboxFlags("AlwaysHorizontalScrollbar", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
		//	ImGui::CheckboxFlags("AlwaysUseWindowPadding   ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_AlwaysUseWindowPadding);
		//	ImGui::CheckboxFlags("NoNavInputs              ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoNavInputs);
		//	ImGui::CheckboxFlags("NoNavFocus               ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoNavFocus);
		//	ImGui::CheckboxFlags("UnsavedDocument          ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_UnsavedDocument);
		//	ImGui::CheckboxFlags("NoDocking                ", &ImGuiWindows.at(SelectHImGuiWindows)->WindowFlags, ImGuiWindowFlags_NoDocking);
		//	ImGui::TreePop();
		//}
	}
	ImGui::End();
}