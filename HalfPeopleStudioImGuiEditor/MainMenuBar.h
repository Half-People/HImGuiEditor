#pragma once

//#ifndef H_MainMenuBar
//#define H_MainMenuBar

#include "MainMenuBarVar.h"
#include "SettingPanel.h"
#include "Porject.h"
#include "ExportCode.h"

void LoadPorjectCallBack(std::string Path)
{
	Porject::PorjectPath = Path;
	Porject::LoadPorject();
}


void DrawMainMenuBar()
{
	static bool ShowAbou = false;
	int FileBrowseMode = 0;
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("SavePorject"))
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

			if (ImGui::MenuItem("OpenPorject"))
			{
				FileBrowseMode = 2;
			}

			DrawExportMenu();

			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem(PreferencesVar::TranslateText::TranslateData.at(0).c_str(), "", &ShowSettingPanel))
			{
				if(ShowSettingPanel)
					LoadSettingData();
			}

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Windows"))
		{
			ImGui::MenuItem("PorjectSettingPanel", "ShowPorjectSettingPanel", &ShowPorjectSettingPanel);
			ImGui::MenuItem("ControlPanel", "ShowControlPanel", &ShowControlPanel);
			ImGui::MenuItem("PluginPanel", "ShowPluginPanel", &ShowPluginPanel);
			ImGui::MenuItem("DeleteWidgetPanel", "ShowDeleteWidgetPanel", &ShowDeleteWidgetPanel);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("Abou", "Abou",&ShowAbou);
			ImGui::EndMenu();
		}

		if (PreferencesVar::ShowFPS)
		{
			ImGui::SetCursorPosX(ImGui::GetWindowSize().x-90);
			ImGui::Text("FPS : %d", (int)ImGui::GetIO().Framerate);
		}
			ImGui::EndMainMenuBar();
	}

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

		if (ImGui::Begin("Abou",&ShowAbou,ImGuiWindowFlags_NoResize))
		{
			//ImGui::SetWindowSize(ImVec2(910,388));
			//std::cout << "\nWindowSize" << ImGui::GetWindowSize().x << "  " << ImGui::GetWindowSize().y;
			ImGui::Text("About The Author :");
			ImGui::Text(" HalfPeopleStudio - HalfPeople (Hong Kong independent game developer)\n");
			ImGui::Text(" Why we develop this product.\n The purpose is to make editing\n ImGui clearer and easier for users.\n thus speeding up development");
			if (ImGui::Button("HalfPeopleStudio "))
				OsOpenInShell("https://half-people.github.io/HalfPeopleStudioWeb/");
			ImGui::SameLine();
			if (ImGui::Button(" YouTube "))
				OsOpenInShell("https://www.youtube.com/channel/UCKv63XONExN6JtUriTqP9Ew");
			ImGui::SameLine();
			if(ImGui::Button(" BiliBili "))
				OsOpenInShell("https://space.bilibili.com/443124242");

			ImGui::Text("\nAPIs used");
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

			ImGui::Text("\nSponsor (QwQ)");
			if (ImGui::Button(" Sponsor"))
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