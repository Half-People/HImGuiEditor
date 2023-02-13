#pragma once
#include "Plugin.h"
#include <imgui.h>

//#include <vector>
//#include <string>
//#include "File.h"
//#include <fstream>
//#include "MainMenuBar.h"
//
//struct HPluginInfo
//{
//	std::string DllPath;
//	std::string PluginName;
//	std::vector<std::string> CallWidgetFunction;
//	std::string Info;
//
//	ImTextureID Image;
//};
//
//std::vector <HPluginInfo> PluginInfo;
//
//void FindWidgetPlugin()
//{
//PluginInfo.clear();
//std::vector<std::string> SavePath;
//getFileNames("Plugin\\Widget", SavePath);
//for (size_t i = 0; i < SavePath.size(); i++)
//{
//	std::fstream file(std::string(SavePath.at(i)).append("\\Info.ini"));
//	if (file.is_open())
//	{
//		PluginInfo.push_back({});
//		std::string SaveLine;
//		while (std::getline(file, SaveLine))
//		{
//			if (SaveLine.find("DllName:") < 10000000)
//			{
//				PluginInfo.back().DllPath = std::string(SavePath.at(i)).append("\\").append(SaveLine.substr(SaveLine.find(":") + 1, 10000000));
//			}
//			else if (SaveLine.find("PluginName:") < 10000000)
//			{
//				PluginInfo.back().PluginName = SaveLine.substr(SaveLine.find(":") + 1, 100000);
//			}
//			else if (SaveLine.find("CreateClassFunction:") < 10000000)
//			{
//				SaveLine.substr(SaveLine.find(":") + 1, 10000000000);
//				while (SaveLine.find("<|Next|>") < 100000000)
//				{
//					std::string Save = SaveLine.substr(0, SaveLine.find("<|Next|>"));
//					SaveLine = SaveLine.substr(SaveLine.find("<|Next|>") + 8, 100000000);
//					PluginInfo.back().CallWidgetFunction.push_back(Save);
//				}
//				PluginInfo.back().CallWidgetFunction.push_back(SaveLine);
//			}
//			else if (SaveLine.find("Info:") < 10000000)
//			{
//				PluginInfo.back().Info = SaveLine.substr(SaveLine.find(":") + 1, 10000000);
//			}
//			else
//			{
//				PluginInfo.back().Info.append("\n").append(SaveLine);
//			}
//		}
//		//PluginInfo.back().Image;
//
//		if (!HLoadImage(std::string(SavePath.at(i)).append("\\PluginImage.png").c_str(), PluginInfo.back().Image))
//		{
//			PluginInfo.back().Image = DefaultLogo;
//		}
//	}
//	file.close();
//}
//}
//
//void DrawPluginPanel()
//{
//	if (!ShowPluginPanel)
//		return;
//
//	if (ImGui::Begin("Plugin Panel", &ShowPluginPanel))
//	{
//		if (ImGui::Button("Load Plugin"))
//		{
//			FindWidgetPlugin();
//		}
//		ImGui::SameLine();
//		if (ImGui::Button("Import Plugin"))
//		{
//
//		}
//
//
//
//		for (size_t i = 0; i < PluginInfo.size(); i++)
//		{
//			if(ImGui::BeginChild(i+1, ImVec2(0, 80), true))
//			{
//
//				ImGui::Image(PluginInfo.at(i).Image, ImVec2(60, 60));
//				ImGui::SameLine();
//
//				ImGui::BeginGroup();
//				ImGui::Text(PluginInfo.at(i).PluginName.c_str());
//				ImGui::Text(PluginInfo.at(i).Info.c_str());
//				ImGui::EndGroup();
//
//				ImGui::SameLine();
//
//				float SaveNextCursorPos = ImGui::GetWindowSize().x - 125;
//				if (SaveNextCursorPos > ImGui::GetCursorPosX())
//				{
//					ImGui::SetCursorPosX(SaveNextCursorPos);
//				}
//
//
//				ImGui::BeginGroup();
//				if (ImGui::Button("OpenFolder"))
//				{
//					//std::cout << "\n " << std::string("start ").append(PluginInfo.at(i).DllPath.substr(0, PluginInfo.at(i).DllPath.rfind("\\"))).c_str();
//					system(std::string("\"start ").append(PluginInfo.at(i).DllPath.substr(0, PluginInfo.at(i).DllPath.rfind("\\"))).append("\"").c_str());
//				}
//				ImGui::Button("Remove Plugin");
//				ImGui::EndGroup();
//			}
//			ImGui::EndChild();
//		}
//	}
//	ImGui::End();
//}
std::string PluginPanelWindowTitle = "Plugin Panel";
#define InitPluginPanel TranslateObject.push_back(&PluginPanelWindowTitle);

static void DrawPluginPanel()
{
	
	if (!ShowPluginPanel)
		return;
	if (ImGui::Begin(std::string(PluginPanelWindowTitle).append("###Plugin Panel").c_str(), &ShowPluginPanel))
	{
		for (size_t i = 0; i < HPluginInfo.size(); i++)
		{
			if (ImGui::BeginChild(i + 2, ImVec2(0, 80), true))
			{
				ImGui::Image(DefaultLogo, ImVec2(60, 60));
				ImGui::SameLine();
				ImGui::BeginGroup();
				std::string ST = HPluginInfo.at(i)["PluginName"];
				ImGui::Text(ST.c_str());
				ST = HPluginInfo.at(i)["Path"];
				ImGui::Text(ST.c_str());
				ImGui::EndGroup();
			}
			ImGui::EndChild();
		}
	}
	ImGui::End();
}