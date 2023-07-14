#pragma once
#include "HTranslate.h"
#include <imgui.h>

std::vector<std::string> ImGuiWindowFlagListName{
	"isNone",
	"NoTitleBar",
	"NoResize",
	"NoMove",
	"NoScrollbar",
	"NoScrollWithMouse",
	"No Collapse",
	"AlwaysAutoResize",
	"No Background",
	"NoSavedSettings",
	"NoMouseInputs",
	"MenuBar",
	"HorizontalScrollbar",
	"NoFocusOnAppearing",
	"NoBringToFrontOnFocus",
	"AlwaysVerticalScrollbar",
	"AlwaysHorizontalScrollbar",
	"AlwaysUseWindowPadding",
	"NoNavInputs",
	"NoNavFocus",
	"UnsavedDocument",
	"NoDocking"
};

void InitFlagList()
{
	for (size_t i = 0; i < ImGuiWindowFlagListName.size(); i++)
	{
		TranslateObject.push_back(&ImGuiWindowFlagListName.at(i));
	}
}

std::vector<ImGuiWindowFlags> ImGuiWindowFlagListFlag
{
	ImGuiWindowFlags_None,
	ImGuiWindowFlags_NoTitleBar,
	ImGuiWindowFlags_NoResize,
	ImGuiWindowFlags_NoMove,
	ImGuiWindowFlags_NoScrollbar,
	ImGuiWindowFlags_NoScrollWithMouse,
	ImGuiWindowFlags_NoCollapse,
	ImGuiWindowFlags_AlwaysAutoResize,
	ImGuiWindowFlags_NoBackground,
	ImGuiWindowFlags_NoSavedSettings,
	ImGuiWindowFlags_NoMouseInputs,
	ImGuiWindowFlags_MenuBar,
	ImGuiWindowFlags_HorizontalScrollbar,
	ImGuiWindowFlags_NoFocusOnAppearing,
	ImGuiWindowFlags_NoBringToFrontOnFocus,
	ImGuiWindowFlags_AlwaysVerticalScrollbar,
	ImGuiWindowFlags_AlwaysHorizontalScrollbar,
	ImGuiWindowFlags_AlwaysUseWindowPadding,
	ImGuiWindowFlags_NoNavInputs,
	ImGuiWindowFlags_NoNavFocus,
	ImGuiWindowFlags_UnsavedDocument,
	ImGuiWindowFlags_NoDocking
};

void DrawImGuiWindowFlagSetting(ImGuiWindowFlags& Flags)
{
	if (ImGui::TreeNode(HT_Flags))
	{
		for (size_t i = 0; i < ImGuiWindowFlagListName.size(); i++)
		{
			ImGui::CheckboxFlags(ImGuiWindowFlagListName.at(i).c_str(), &Flags, ImGuiWindowFlagListFlag.at(i));
		}
		ImGui::TreePop();
	}
}