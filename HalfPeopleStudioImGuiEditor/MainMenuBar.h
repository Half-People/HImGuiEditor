#pragma once

//#ifndef H_MainMenuBar
//#define H_MainMenuBar

#include "MainMenuBarVar.h"
#include "SettingPanel.h"
#include "Porject.h"
#include "ExportCode.h"

#include "PorjectSettingPanel.h"
#include "PluginPanel.h"
#include "ControlPanel.h"
#include "DeleteWidgetPanel.h"

void LoadPorjectCallBack(std::string Path)
{
	Porject::PorjectPath = Path;
	Porject::LoadPorject();
}
namespace MainMenuBarT {
	static std::string File = "File";
	static std::string SavePorject = "SavePorject";
	static std::string OpenPorject = "OpenPorject";
	static std::string Edit = "Editor";
	static std::string Windows = "Windows";
	static std::string Help = "Help";
	static std::string Abou = "about";

	static std::string AbouData1 = "About The Author :";
	static std::string AbouData2 = "Why we develop this product.";
	static std::string AbouData3 = " The purpose is to make editing";
	static std::string AbouData4 = " ImGui clearer and easier for users.";
	static std::string AbouData5 = " thus speeding up development";
	static std::string AbouData6 = " Sponsor";
	static std::string AbouData7 = "APIs used";

	static std::string Tool = "Tool";
	static std::string ShowStackTool = "ShowStackTool";
	static std::string ShowMetricsWindow = "ShowMetricsWindow";
	static std::string ShowImGuiDemoWindow = "Show ImGui Demo Window";
}

#define InitMainMenuBar TranslateObject.push_back(&MainMenuBarT::File);\
TranslateObject.push_back(&MainMenuBarT::SavePorject);\
TranslateObject.push_back(&MainMenuBarT::OpenPorject);\
TranslateObject.push_back(&MainMenuBarT::Edit);\
TranslateObject.push_back(&MainMenuBarT::Windows);\
TranslateObject.push_back(&MainMenuBarT::Help);\
TranslateObject.push_back(&MainMenuBarT::Abou);\
TranslateObject.push_back(&MainMenuBarT::AbouData1);\
TranslateObject.push_back(&MainMenuBarT::AbouData2);\
TranslateObject.push_back(&MainMenuBarT::AbouData3);\
TranslateObject.push_back(&MainMenuBarT::AbouData4);\
TranslateObject.push_back(&MainMenuBarT::AbouData5);\
TranslateObject.push_back(&MainMenuBarT::AbouData6);\
TranslateObject.push_back(&MainMenuBarT::AbouData7);\
TranslateObject.push_back(&MainMenuBarT::Tool);\
TranslateObject.push_back(&MainMenuBarT::ShowStackTool);\
TranslateObject.push_back(&MainMenuBarT::ShowImGuiDemoWindow);\
TranslateObject.push_back(&MainMenuBarT::ShowMetricsWindow);\


void DrawMainMenuBar()
{
	static bool ShowAbou = false;
	static bool ShowStackToolWindow_B = false, ShowMetricsWindow_B = false, ShowDemoWindow_B=false;
	int FileBrowseMode = 0;
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu(MainMenuBarT::File.c_str()))
		{
			if (ImGui::MenuItem(MainMenuBarT::SavePorject.c_str()))
			{
				if (Porject::PorjectPath.empty())
				{
					FileBrowseMode = 1;
				}
				else
				{
					Porject::SavePorject();
				}
			}

			if (ImGui::MenuItem(MainMenuBarT::OpenPorject.c_str()))
			{
				FileBrowseMode = 2;
			}

			DrawExportMenu();

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu(MainMenuBarT::Edit.c_str()))
		{
			if (ImGui::MenuItem(PreferencesVar::TranslateText::TranslateData.at(0).c_str(), "", &ShowSettingPanel))
			{
				if(ShowSettingPanel)
					LoadSettingData();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu(MainMenuBarT::Windows.c_str()))
		{
			ImGui::MenuItem(PorjectSettingTranslateList::PorjectSetting.c_str(), "ShowPorjectSettingPanel", &ShowPorjectSettingPanel);
			ImGui::MenuItem(ControlPanelTitle.c_str(), "ShowControlPanel", &ShowControlPanel);
			ImGui::MenuItem(PluginPanelWindowTitle.c_str(), "ShowPluginPanel", &ShowPluginPanel);
			ImGui::MenuItem(DeleteWidgetPanelTitle.c_str(), "ShowDeleteWidgetPanel", &ShowDeleteWidgetPanel);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu(MainMenuBarT::Help.c_str()))
		{
			ImGui::MenuItem(MainMenuBarT::Abou.c_str(), "Abou",&ShowAbou);

			if (ImGui::BeginMenu(MainMenuBarT::Tool.c_str(),"Tools"))
			{
				ImGui::MenuItem(MainMenuBarT::ShowStackTool.c_str(), "ShowStackTool", &ShowStackToolWindow_B);
				ImGui::MenuItem(MainMenuBarT::ShowMetricsWindow.c_str(), "ShowMetricsWindow", &ShowMetricsWindow_B);
				ImGui::MenuItem(MainMenuBarT::ShowImGuiDemoWindow.c_str(), "Show ImGui Demo Window", &ShowDemoWindow_B);
				ImGui::EndMenu();
			}

			ImGui::EndMenu();
		}

		if (PreferencesVar::ShowFPS)
		{
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x-90);
			ImGui::Text("FPS : %d", (int)ImGui::GetIO().Framerate);
		}
			ImGui::EndMainMenuBar();
	}

	if(ShowStackToolWindow_B)
		ImGui::ShowStackToolWindow(&ShowStackToolWindow_B);
	if (ShowMetricsWindow_B)
		ImGui::ShowMetricsWindow(&ShowMetricsWindow_B);
	if(ShowDemoWindow_B)
		ImGui::ShowDemoWindow(&ShowDemoWindow_B);
	DrawExportBrowser();

	if (FileBrowseMode == 1)
	{
		Porject::CreatePorject();
	}
	else if (FileBrowseMode == 2)
	{
		FileBrowser::OpenBrowser(LoadPorjectCallBack,false,".H_ImGui_PJ","HImGuiEditot_Porject");
	}
	Porject::DrawCreatePorject("HImGuiEditot_Porject");

	// DrawAbou
	if (ShowAbou)
	{

		if (ImGui::Begin(MainMenuBarT::Abou.c_str(),&ShowAbou,ImGuiWindowFlags_NoResize))
		{
			//ImGui::SetWindowSize(ImVec2(910,388));
			//std::cout << "\nWindowSize" << ImGui::GetWindowSize().x << "  " << ImGui::GetWindowSize().y;
			ImGui::Text(MainMenuBarT::AbouData1.c_str());
			ImGui::Separator();
			ImGui::Text(" HalfPeopleStudio - HalfPeople (Hong Kong independent game developer)\n");
			ImGui::Text(std::string(MainMenuBarT::AbouData2).c_str());
			ImGui::Separator();
			ImGui::Text(std::string(MainMenuBarT::AbouData3).c_str());
			ImGui::Text(std::string(MainMenuBarT::AbouData4).c_str());
			ImGui::Text(std::string(MainMenuBarT::AbouData5).c_str());
//			ImGui::Text(" Why we develop this product.\n The purpose is to make editing\n ImGui clearer and easier for users.\n thus speeding up development");
			if (ImGui::Button("HalfPeopleStudio "))
				OsOpenInShell("https://half-people.github.io/HalfPeopleStudioWeb/");
			ImGui::SameLine();
			if (ImGui::Button(" YouTube "))
				OsOpenInShell("https://www.youtube.com/channel/UCKv63XONExN6JtUriTqP9Ew");
			ImGui::SameLine();
			if(ImGui::Button(" BiliBili "))
				OsOpenInShell("https://space.bilibili.com/443124242");
			ImGui::Text(" ");
			ImGui::Text(std::string(MainMenuBarT::AbouData7).c_str());
			ImGui::Separator();
			if(ImGui::Button(" ImGui "))
				OsOpenInShell("https://github.com/ocornut/imgui");
			ImGui::SameLine();
			if (ImGui::Button(" ImGuiColorTextEdit "))
				OsOpenInShell("https://github.com/BalazsJako/ImGuiColorTextEdit");
			ImGui::SameLine();
			if (ImGui::Button(" Curl "))
				OsOpenInShell("https://github.com/curl/curl");
			//ImGui::SameLine();
			if (ImGui::Button(" GLFW "))
				OsOpenInShell("https://www.glfw.org/");
			ImGui::SameLine();
			if (ImGui::Button(" JSON for Modern C++ "))
				OsOpenInShell("https://github.com/nlohmann/json");
			ImGui::SameLine();
			if (ImGui::Button("stb_image "))
				OsOpenInShell("https://github.com/nothings/stb");

			ImGui::Separator();
			if (ImGui::Button(std::string(MainMenuBarT::AbouData6).c_str()))
			{
				OsOpenInShell("https://half-people.github.io/HalfPeopleStudioWeb/%E8%B4%8A%E5%8A%A9/Sponsor.html");
			}

			ImDrawList* DL =  ImGui::GetWindowDrawList();

			ImVec2 Start = ImGui::GetWindowPos();
			ImVec2 End = ImVec2(910, 388);
			End.x += Start.x;
			End.y += Start.y;
			Start.x = End.x - 150;
			Start.y = End.y - 150;
			DL->AddImage(DefaultLogo, Start, End);
		}
		ImGui::End();
	}

}


//#endif // !H_MainMenuBar