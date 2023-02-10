#pragma once
#include <imgui.h>
#include "HTranslate.h"
#include "Porject.h"

namespace SplashScreen
{
	//void OpenSplashScreen()
	//{
	//	ImGui::OpenPopup("SplashScreen");
	//	//ImGui::SetNextWindowSize(ImVec2(300, 300));
	//}

	static bool NeedOpenSplashScreen = true;
	static json RecentlyOpenedPorject;

	static json VerifyProjectContent(json J)
	{
		json Buff;
		for (size_t i = 0; i < J.size(); i++)
		{
			std::ifstream file(J.at(i)["PorjectPath"].get<std::string>());
			if (file)
				Buff.push_back(J.at(i));
			file.close();
		}
		return Buff;
	}


	static void DrawSplashScreen()
	{
		if (NeedOpenSplashScreen)
		{
			std::ifstream fileR("DependentFile\\configuration file\\RecentlyOpenedPorject.json");
			if (fileR.is_open())
			{
				RecentlyOpenedPorject = VerifyProjectContent(json::parse(fileR));
				ImGui::OpenPopup("SplashScreen");
				NeedOpenSplashScreen = false;
			}
			fileR.close();
		}

		if (ImGui::BeginPopupModal("SplashScreen"))
		{
			static int SelectIndex = -1;
			ImGui::BeginChild("xm",ImVec2(0,ImGui::GetWindowSize().y - 75));
			
			for (size_t i = 0; i < RecentlyOpenedPorject.size(); i++)
			{
				if(SelectIndex == i)
					ImGui::PushStyleColor(ImGuiCol_Border,ImVec4(0.5,1,0.5,0.5));
				if (ImGui::BeginChild(i+15,ImVec2(0,60),true))
				{
					std::string SaveText = RecentlyOpenedPorject.at(i)["Title"];
					ImGui::Text(SaveText.c_str());

					float TimePos = ImGui::GetWindowSize().x - 180;
					if (ImGui::GetItemRectSize().x < TimePos)
					{
						ImGui::SameLine();
						ImGui::SetCursorPosX(TimePos);
						SaveText = RecentlyOpenedPorject.at(i)["OpenTime"];
						ImGui::Text(SaveText.c_str());
					}


					SaveText = RecentlyOpenedPorject.at(i)["PorjectPath"];
					ImGui::Text(SaveText.c_str());
				}
				ImGui::EndChild();
				if (ImGui::IsItemClicked())
				{
					Porject::PorjectPath = RecentlyOpenedPorject.at(i)["PorjectPath"];
					Porject::LoadPorject();
					ImGui::CloseCurrentPopup();
				}
				if(SelectIndex == i)
					ImGui::PopStyleColor();
				if (ImGui::IsItemHovered())
				{
					SelectIndex = i;
				}
			}

			ImGui::EndChild();
			if (ImGui::Button(HT_Cancel))
			{
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}

	}

}