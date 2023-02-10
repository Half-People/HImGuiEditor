#pragma once
//#ifndef H_PORJECT
//#define H_PORJECT

#include <string>
#include "HFileBrowser.h"

#include "HImGuiWindows.h"
#include "PorjectSettingPanel.h"
namespace Porject
{
	static std::string PorjectPath;//= "G:\\HalfPeopleStudioC++ Porject\\HalfPeopleStudioImGuiEditor\\TestPorject";
	static char PorjectName[50] = {"PorjectName"};
	static bool NeedShowFileBrowser = false;

	static void UpdataRecentlyOpenedPorject()
	{
		json RecentlyOpenedPorject;
		std::ifstream fileR("DependentFile\\configuration file\\RecentlyOpenedPorject.json");
		if (fileR.is_open())
			RecentlyOpenedPorject = json::parse(fileR);
		fileR.close();

		bool HaveFind = false;
		json Buff;
		for (size_t i = 0; i < RecentlyOpenedPorject.size(); i++)
		{
			if (RecentlyOpenedPorject.at(i)["PorjectPath"] == PorjectPath)
			{
				HaveFind = true;
				json Data;
				Data["PorjectPath"] = PorjectPath;
				Data["Title"] = std::string(PorjectPath).substr(PorjectPath.rfind("\\")+1, 10000000);
				Data["OpenTime"] = GetTime();

				Buff.push_back(Data);
				i = RecentlyOpenedPorject.size();
			}
		}
		if (!HaveFind)
		{
			json Data;
			Data["PorjectPath"] = PorjectPath;
			Data["Title"] = std::string(PorjectPath).substr(PorjectPath.rfind("\\")+1, 10000000);
			Data["OpenTime"] = GetTime();

			Buff.push_back(Data);
		}

		if (HaveFind)
		{
			for (size_t i = 0; i < RecentlyOpenedPorject.size(); i++)
			{
				if (RecentlyOpenedPorject.at(i)["PorjectPath"] != PorjectPath)
				{
					Buff.push_back(RecentlyOpenedPorject.at(i));
				}
			}
		}
		else
		{
			for (size_t i = 0; i < RecentlyOpenedPorject.size(); i++)
			{
				Buff.push_back(RecentlyOpenedPorject.at(i));
			}
		}




		std::ofstream fileS("DependentFile\\configuration file\\RecentlyOpenedPorject.json");
		if (fileS.is_open())
		{
			fileS << Buff.dump(4);
		}
		fileS.close();
	}

	static void SavePorject()
	{
		if (PorjectPath.empty())
			return;
		json PorjectData;

		PorjectData["PorjectSetting"] = SavePorjectSetting();
		for (size_t i = 0; i < ImGuiWindows.size(); i++)
		{
			PorjectData["ImGuiWindows"].push_back(ImGuiWindows.at(i)->Save());
		}
		PorjectData["SelectWindow"] = SelectHImGuiWindows;

		std::ofstream file(PorjectPath);
		if (file.is_open())
		{
			file << PorjectData;//.dump(4);
		}
		file.close();

		UpdataRecentlyOpenedPorject();
	}

	static void LoadPorject()
	{
		if (PorjectPath.empty())
			return;
		json PorjectData;
		std::ifstream file(PorjectPath);
		if (file.is_open())
			PorjectData = json::parse(file);
		else
			return;
		if (PorjectData.is_null())
			return;
		file.close();


		SelectHImGuiWindows = PorjectData["SelectWindow"];

		LoadPorjectSetting(PorjectData["PorjectSetting"]);

		RemoveAllHImGuiWindows();
		
		for (size_t i = 0; i < PorjectData["ImGuiWindows"].size(); i++)
		{
			ImGuiWindows.push_back(new HImGuiWindows);
			ImGuiWindows.back()->Load(PorjectData["ImGuiWindows"].at(i));
		}
		UpdataRecentlyOpenedPorject();
	}

	static void CreatePorjectCallBack(std::string path)
	{
		// Save Porject
		PorjectPath = path.append("\\").append(PorjectName).append(".H_ImGui_PJ");

		SavePorject();
	}

	static void CreatePorject()
	{
		ImGui::OpenPopup("CreatePorject");
	}

	static void DrawCreatePorject(const char* id = "Porject")
	{
		if (ImGui::BeginPopupModal("CreatePorject",0))
		{
			ImGui::SetNextItemWidth(250);
			if (ImGui::InputText("PorjectName", PorjectName, 50))
			{
				if (std::string(PorjectName).empty())
				{
					strcpy_s(PorjectName, "PorjectName");
				}
			}
			if (ImGui::Button(HT_Cancel))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button(HT_Confirm))
			{
				NeedShowFileBrowser = true;

				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}

		if (NeedShowFileBrowser)
		{
			FileBrowser::OpenBrowser(CreatePorjectCallBack,true,id);
			NeedShowFileBrowser = false;
		}

		FileBrowser::DrawFileBrowser(id);
	}
}

//#endif // !H_PORJECT