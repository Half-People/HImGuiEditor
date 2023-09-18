#pragma once
#include <imgui.h>
#include <vector>
#include "MainMenuBarVar.h"
#include "DefaultWidget.h"

//HWidget* GetWidgetList(int Index)
//{
//	return WidgetList.at(Index);
//}

void CreateDefaulWidget()
{
	//GetWidgetData = GetWidgetList;
	WidgetList.push_back(new Button);
	WidgetList.push_back(new Text);
	WidgetList.push_back(new TreeNode);
	WidgetList.push_back(new Group);
	WidgetList.push_back(new Child);
	WidgetList.push_back(new InputText);
	WidgetList.push_back(new InputTextMultiline);
	WidgetList.push_back(new DragFloat);
	WidgetList.push_back(new ColorEdit);
	WidgetList.push_back(new ColorButton);
	WidgetList.push_back(new Image);
}

void VerifyHWidgetList()
{
	for (size_t Q = 0; Q < WidgetList.size(); Q++)
	{
		std::string* SaveName = WidgetList.at(Q)->WidgetName;
		bool HaveTheSame = false;
		do
		{
			std::cout << "\n\n";
			HaveTheSame = false;
			for (size_t i = 0; i < WidgetList.size(); i++)
			{
				// std::cout << "Index : " << i << "     " << *WidgetList.at(i)->WidgetName << "    " << *SaveName;
				std::cout << "\n ControlPanel -> VerifyHWidgetList -> Info -> Verifying :  " << Q + 1 << "/" << WidgetList.size() << "  SubProgress : " << i + 1 << "/" << WidgetList.size() << "    " << *SaveName << " <--> " << *WidgetList.at(i)->WidgetName;
				if (*WidgetList.at(i)->WidgetName == *SaveName && i != Q)
				{
					HaveTheSame = true;
					int pos = SaveName->rfind("_");
					if (pos != -1)
					{
						std::string CP = *SaveName;
						int SaveIndex = atoi(CP.substr(pos + 1, 1000000).c_str());
						*SaveName = SaveName->substr(0, pos + 1);
						*SaveName = SaveName->append(std::to_string(SaveIndex + 1));
					}
					else
					{
						*SaveName = SaveName->append("_1");
					}
				}
			}
		} while (HaveTheSame);
		*WidgetList.at(Q)->WidgetNameID = *SaveName;
		TranslateObject.push_back(SaveName);
	}
}

static std::string ControlPanelTitle = "ControlPanel";
#define InitControlPanel TranslateObject.push_back(&ControlPanelTitle);

void DrawControlPanel()
{
	if (!ShowControlPanel)
		return;
	if (ImGui::Begin(std::string(ControlPanelTitle).append("###ControlPanel").c_str(), &ShowControlPanel))
	{
		float MaxSize = ImGui::GetWindowSize().x + ImGui::GetWindowPos().x;

		for (size_t i = 0; i < WidgetList.size(); i++)
		{
			//ImGui::Button(std::string("###").append(std::to_string(i)).append("ControlPanelItems").c_str(), ImVec2(110, 110));

			//ImGui::BeginGroup();
			ImGui::BeginChild(i + 1, ImVec2(110, 110), false, ImGuiWindowFlags_::ImGuiWindowFlags_NoInputs);

			WidgetList.at(i)->DrawIconForControlPanel();

			ImGui::SetCursorPosY(85);
			ImGui::Text(WidgetList.at(i)->WidgetName->c_str());
			ImGui::EndChild();
			//ImGui::EndGroup();

			ImGui::SameLine();
			ImVec2 SaveButtonOffset = ImGui::GetCursorPos();
			SaveButtonOffset.x -= 120;
			ImGui::SetCursorPos(SaveButtonOffset);
			ImGui::Button(std::string("###").append(std::to_string(i)).append("ControlPanelItems").c_str(), ImVec2(110, 110));

			if (ImGui::BeginDragDropSource())
			{
				WidgetList.at(i)->DrawIconForControlPanel();
				ImGui::Text(WidgetList.at(i)->WidgetName->c_str());
				SelectWidget = WidgetList.at(i);
				//ImGui::SetDragDropPayload("DragWidget", &i, sizeof(int));
				ImGui::SetDragDropPayload("DragWidget", WidgetList.at(i), sizeof(HWidget*));
				ImGui::EndDragDropSource();
			}

			if (i + 1 < WidgetList.size() && ImGui::GetItemRectMax().x + 5 + 110 < MaxSize)
				ImGui::SameLine(0, 5);
		}
	}
	ImGui::End();
}
