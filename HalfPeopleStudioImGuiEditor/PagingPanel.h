#pragma once
#include <imgui.h>
#include <vector>
//#include "HFileBrowser.h"
#include "Porject.h"
#include "MainMenuBarVar.h"

static ImTextureID PluginImage,PorjectSettingImage,SaveImage;
static std::string PagingPanelWindowTitle = "Paging Panel";

namespace PagingPanelRemoveWindow
{
	static std::string RemoveWindows = "RemoveWindows";
	static std::string Text = "Are you sure to delete this window and the data will disappear after saving";
}
#define InitPagingPanel TranslateObject.push_back(&PagingPanelWindowTitle);\
TranslateObject.push_back(&PagingPanelRemoveWindow::RemoveWindows);\
TranslateObject.push_back(&PagingPanelRemoveWindow::Text);
static void SelectFolderCallBack(std::string Path)
{
	printf("\n SelectPath : ");
	printf(Path.c_str());
}

static void DrawPagingPanel()
{
	if (ImGui::Begin(std::string(PagingPanelWindowTitle).append("###PagingPanel").c_str(), 0,ImGuiWindowFlags_NoMove))// ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar))
	{
		ImVec2 WindowSizeSave = ImGui::GetWindowSize();
		WindowSizeSave.y -= 60;//50
		WindowSizeSave.y -= ImGui::GetTextLineHeight();

		if (WindowSizeSave.x > WindowSizeSave.y)
			WindowSizeSave.x = WindowSizeSave.y;
		else
			WindowSizeSave.y = WindowSizeSave.x;

		ImGui::BeginGroup();
		if(ImGui::ImageButton(PluginImage, WindowSizeSave,ImVec2(0,0),ImVec2(1,1),-1,ImVec4(0.1,0.1,0.1,0.5)))
		{
			ShowPluginPanel = !ShowPluginPanel;
		}
		ImGui::SameLine();
		if (ImGui::ImageButton(PorjectSettingImage,WindowSizeSave))
		{
			ShowPorjectSettingPanel = !ShowPorjectSettingPanel;
		}
		ImGui::SameLine();
		if (ImGui::ImageButton(SaveImage,WindowSizeSave))
		{
			//FileBrowser::OpenBrowser(SelectFolderCallBack,true);
			if (Porject::PorjectPath.empty())
			{
				Porject::CreatePorject();
			}
			else
			{
				Porject::SavePorject();
			}
		}
		Porject::DrawCreatePorject();
		ImGui::EndGroup();
		//FileBrowser::DrawFileBrowser();

		if (ImGui::BeginTabBar("WindowList",ImGuiTabBarFlags_::ImGuiTabBarFlags_FittingPolicyScroll))
		{
			if (ImGui::TabItemButton("+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip))
			{
				ImGuiWindows.push_back(new HImGuiWindows);
			}

			bool HaveMoreImGuiWindow = ImGuiWindows.size() > 1;
			for (size_t i = 0; i < ImGuiWindows.size(); i++)
			{
				if (HaveMoreImGuiWindow)
				{
					bool wopen = true;
					if (ImGui::BeginTabItem(std::string(ImGuiWindows.at(i)->Title).append("###Tab").append(std::to_string(i + 1)).c_str(), &wopen))
					{
						SelectHImGuiWindows = i;
						ImGui::EndTabItem();
					}
					if (!wopen)
					{
						ImGui::OpenPopup(std::string(PagingPanelRemoveWindow::RemoveWindows).append("###RemoveWindows").append(std::to_string(i)).c_str());
					}
					if (ImGui::BeginPopupModal(std::string(PagingPanelRemoveWindow::RemoveWindows).append("###RemoveWindows").append(std::to_string(i)).c_str()))
					{
						ImGui::Text(PagingPanelRemoveWindow::Text.c_str());
						ImGui::Separator();
						float WindowHalfSizeX = ImGui::GetWindowSize().x/2;
						if (ImGui::Button(HT_Cancel,ImVec2(WindowHalfSizeX,0)))
						{
							ImGui::CloseCurrentPopup();
						}
						ImGui::SameLine();
						if (ImGui::Button(HT_Confirm, ImVec2(WindowHalfSizeX, 0)))
						{
							HImGuiWindows* Buff = ImGuiWindows.at(i);
							ImGuiWindows.erase(ImGuiWindows.begin() + i);
							delete Buff;
							ImGui::CloseCurrentPopup();
						}
						ImGui::EndPopup();
					}
				}
				else
				{
					if (ImGui::BeginTabItem(ImGuiWindows.at(i)->Title,0, ImGuiTabItemFlags_None))
					{
						SelectHImGuiWindows = i;
						ImGui::EndTabItem();
					}
				}
			}

			ImGui::EndTabBar();
		}


	}
	ImGui::End();
}