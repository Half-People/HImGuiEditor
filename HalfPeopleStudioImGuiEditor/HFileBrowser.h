#pragma once
#include "File.h"
#include "HTranslate.h"
#include <imgui.h>

namespace FileBrowser
{
	static void(*BrowserCallBack)(std::string ReturnPath);
	static std::string SavePath;
	static std::string filter;
	static std::vector<std::string> AllDrives;
	static std::vector<std::string> Files;
	static std::vector<std::string> FileNames;
	static bool OnlyShowFolder;
	static int SelectDrivesID = 0;
	static int SelectFileID = -1;

	static void UpdataFiles(std::string Path)
	{
		Files.clear();
		FileNames.clear();
		if (OnlyShowFolder)
		{
			getFolderNames(Path, Files, FileNames);
		}
		else
		{
			getFileNames(Path, Files, FileNames, filter);
		}
	}

	static void OpenBrowser(void(*BrowserCallBack_)(std::string ReturnPath),bool OnlyShowFolder_, const char* ID = "FileBrowser")
	{
		filter = "";
		OnlyShowFolder = OnlyShowFolder_;
		BrowserCallBack = BrowserCallBack_;
		ImGui::OpenPopup(ID);
		AllDrives = getListOfDrives();
		if (SavePath.empty())
		{
			SelectDrivesID = 0;
			SavePath = AllDrives.at(SelectDrivesID);

		}
		UpdataFiles(SavePath);
	}

	static void OpenBrowser(void(*BrowserCallBack_)(std::string ReturnPath), bool OnlyShowFolder_,std::string filter_, const char* ID = "FileBrowser")
	{
		filter = filter_;
		OnlyShowFolder = OnlyShowFolder_;
		BrowserCallBack = BrowserCallBack_;
		ImGui::OpenPopup(ID);
		AllDrives = getListOfDrives();
		if (SavePath.empty())
		{
			SelectDrivesID = 0;
			SavePath = AllDrives.at(SelectDrivesID);

		}
		UpdataFiles(SavePath);
	}


	static void DrawFileBrowser(const char* ID = "FileBrowser")
	{
		if (ImGui::BeginPopupModal(ID))
		{
			ImGui::BeginGroup();
			if (ImGui::BeginChild("FileBrowserHDD",ImVec2(150,ImGui::GetWindowSize().y - 75),true))
			{
				for (size_t i = 0; i < AllDrives.size(); i++)
				{
					if (ImGui::Selectable(AllDrives.at(i).c_str(), SelectDrivesID == i))
					{
						SelectDrivesID = i;
						SavePath = AllDrives.at(i);
						UpdataFiles(SavePath);
					}
				}
			}
			ImGui::EndChild();
			if (ImGui::Button(HT_Cancel))
			{
				Files.clear();
				FileNames.clear();
				AllDrives.clear();
				filter.clear();
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button(HT_Confirm))
			{
				if (OnlyShowFolder)
				{
					BrowserCallBack(SavePath);
				}
				else
				{
					if (SelectFileID != -1)
					{
						BrowserCallBack(Files.at(SelectFileID));
					}
				}
				filter.clear();
				Files.clear();
				FileNames.clear();
				AllDrives.clear();
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndGroup();

			ImGui::SameLine();

			ImGui::BeginGroup();
			if (ImGui::Button("<-"))
			{
				std::string Save = SavePath;
				SavePath = Save.substr(0, Save.rfind("\\"));
				UpdataFiles(SavePath);
			}
			ImGui::SameLine();
			if (ImGui::Button("Reload"))
			{
				UpdataFiles(SavePath);
			}

			if (ImGui::BeginChild("Files", ImVec2(0, 0), true))
			{
				for (size_t i = 0; i < Files.size(); i++)
				{
					if (ImGui::Selectable(FileNames.at(i).c_str(),i == SelectFileID))
					{
						if (OnlyShowFolder)
						{
							SavePath = Files.at(i);
							UpdataFiles(SavePath);
						}
						else
						{
							if (FileNames.at(i).find(".") < 100000)
							{
								SelectFileID = i;
							}
							else
							{
								SelectFileID = -1;
								SavePath = Files.at(i);
								UpdataFiles(SavePath);
							}
						}

					}
				}
			}

			ImGui::EndChild();
			ImGui::EndGroup();
			ImGui::EndPopup();
		}
	}
}
