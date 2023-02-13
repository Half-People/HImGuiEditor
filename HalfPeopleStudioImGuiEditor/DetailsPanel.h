#pragma once
#include <imgui.h>
#include "MainMenuBar.h"
#include "HWidget.h"

namespace DetailsPanelT {
	static std::string WindowTitle = "DetailsPanel";
	static std::string SizeAndPos = "Size And Pos";
	static std::string WidgetSize = "Widget Size";
	static std::string WidgetPos = "WidgetPos";
	static std::string WidgetDebugInfo = "Widget Debug Info";
}

#define InitDetailsPanel TranslateObject.push_back(&DetailsPanelT::WindowTitle);\
 TranslateObject.push_back(&DetailsPanelT::SizeAndPos);\
 TranslateObject.push_back(&DetailsPanelT::WidgetSize);\
 TranslateObject.push_back(&DetailsPanelT::WidgetPos);\
 TranslateObject.push_back(&DetailsPanelT::WidgetDebugInfo);\

void DrawDetailsPanel()
{
	if (!ShowDetailsPanel)
		return;
	if (ImGui::Begin(std::string(DetailsPanelT::WindowTitle).append("###DetailsPanel").c_str(), &ShowDetailsPanel))
	{
		if (SelectWidget)
		{
			if (!SelectWidget->Father)
			{
				ImGui::End();
				return;
			}


			if (ImGui::TreeNode(DetailsPanelT::SizeAndPos.c_str()))
			{
				if (SelectWidget->HArrowFlag == HArrow_SizeFlag_OnlyX)
				{
					ImGui::DragFloat("Widget Size", &SelectWidget->WidgetSize.x,0.5,0,100000);
				}
				else
				{
					if(SelectWidget->HArrowFlag == HArrow_SizeFlag_Default)
						ImGui::DragFloat2(DetailsPanelT::WidgetSize.c_str(), (float*)&SelectWidget->WidgetSize,0.5,0,10000);
				}

				if(SelectWidget->Flag == HWidgetFlag_ContentMove || SelectWidget->Flag == HWidgetFlag_Move || SelectWidget->Flag == HWidgetFlag_WindowRootWidgetAndMove)
					ImGui::DragFloat2(DetailsPanelT::WidgetPos.c_str(), (float*)&SelectWidget->MovePos,0.5,0,1000000);



				ImGui::TreePop();
			}





			SelectWidget->DetailPanelWidget();

			static bool ShowInfo;

			if (ShowInfo)
			{
				ImGui::SetCursorPosY(ImGui::GetWindowSize().y-215);
			}
			else
			{
				ImGui::SetCursorPosY(ImGui::GetWindowSize().y - 30);
			}

			ShowInfo = ImGui::TreeNode(DetailsPanelT::WidgetDebugInfo.c_str());

			if(ShowInfo)
			{
				ImGui::BeginChild("c", ImVec2(0, 0), true);
				ImGui::Text("Self : %X", SelectWidget);
				ImGui::Text("Flag : %d", SelectWidget->Flag);
				ImGui::Text("ID : %d", SelectWidget->ID_);
				ImGui::Text(std::string("Widget Name : ").append(*SelectWidget->WidgetName).c_str());
				ImGui::Text("Subclass : %X", SelectWidget->Subclass);
				ImGui::Text("Father : %X", SelectWidget->Father);
				ImGui::Text("Content : %X", SelectWidget->Content);
				ImGui::EndChild();
				ImGui::TreePop();
			}

		}
	}
	ImGui::End();
}