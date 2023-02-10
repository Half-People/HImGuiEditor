#pragma once
#include <imgui.h>
#include "imgui-notify/src/imgui_notify.h"
#include "imgui-notify/tahoma.h"

namespace ImGui
{
	static void InitNotify()
	{
		ImGuiIO* io = &ImGui::GetIO();

		// We must load a font before loading notify, because we cannot merge font-awesome with default font
		// FontDataOwnedByAtlas = false is required (also in ImGui::MergeIconsWithLatestFont())
		// because otherwise ImGui will call free() while freeing resources which will lead into a crash
		// since tahoma is defined as readonly and wasn't allocated with malloc()
		ImFontConfig font_cfg;
		font_cfg.FontDataOwnedByAtlas = false;
		io->Fonts->AddFontFromMemoryTTF((void*)tahoma, sizeof(tahoma), 17.f, &font_cfg);

		// Initialize notify
		ImGui::MergeIconsWithLatestFont(16.f, false);
	}

	static void DrawNotify()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
		ImGui::RenderNotifications();
		ImGui::PopStyleVar(1); // Don't forget to Pop()
		ImGui::PopStyleColor(1);
	}
}
