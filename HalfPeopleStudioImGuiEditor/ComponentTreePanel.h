#pragma once
#include "HTranslate.h"
#include "HImGuiWindows.h"
//#include "DeleteWidgetPanel.h"
static std::string ComponentTreeTitle = "ComponentTreePanel";


#define InitComponentTreePanel TranslateObject.push_back(&ComponentTreeTitle);
static int ComponentTreeID = 1;
static void ComponentTreeItems(HWidget* Widget,ImDrawList* DL)
{

	if (Widget->WidgetID)
	{
		if (ImGui::Selectable(std::string(*Widget->WidgetName).append("  --  ").append(Widget->WidgetID).append("###").append(std::to_string((int)Widget)).c_str(), SelectWidget == Widget))
		{
			SelectWidget = Widget;
		}
	}
	else
	{
		if (ImGui::Selectable(std::string(*Widget->WidgetName).append("###").append(std::to_string((int)Widget)).c_str(), SelectWidget == Widget))
		{
			SelectWidget = Widget;
		}
	}

	if (ImGui::BeginDragDropTarget())
	{
		ImVec2 SaveNextWidgetPos = ImGui::GetCursorScreenPos();
		SaveNextWidgetPos.y += 5;
		DL->AddLine(SaveNextWidgetPos,ImVec2(SaveNextWidgetPos.x+ImGui::GetWindowSize().x, SaveNextWidgetPos.y),ImColor(255,255,255,200),2.5);
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragWidget"))
		{
			if (SelectWidget != Widget)
			{
				HWidget* SaveDragWidget = SelectWidget;
				if (SaveDragWidget->Flag == HWidgetFlag_Content || SaveDragWidget->Flag == HWidgetFlag_WindowRootWidget || SaveDragWidget->Flag == HWidgetFlag_WindowRootWidgetAndMove)
				{
					Widget->MoveWidget_RD(SaveDragWidget, HWidgetFlag_Null);
				}
				else
				{
					Widget->MoveWidget_RD(SaveDragWidget, SaveDragWidget->Flag);
				}
			}

		}
		ImGui::EndDragDropTarget();
	}


	if (ImGui::BeginDragDropSource())
	{
		if (Widget)
		{
			Widget->DrawIconForControlPanel();
			//SelectWidget = this;
			ImGui::Text(Widget->WidgetName->c_str());
			//DragDropAcceptFrameCount
			SelectWidget = Widget;
			ImGui::SetDragDropPayload("DragWidget", Widget, sizeof(HWidget*));
		}

		//std::cout << "\n False";
		//ImGui::SetDragDropPayload("DragWidget", &i, sizeof(int));

		ImGui::EndDragDropSource();
	}

	AddRightClickMenu(Widget);
}	

static void ComponentTreeAnalyzeChildren(HWidget* Widget,ImDrawList * DrawList)
{
	if (!Widget)
		return;
	if (Widget->Content)
	{
		//ImGui::BeginGroup();
		//if (Widget == SelectWidget && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
		//{
		//	ImGui::SetNextItemOpen(false);
		//}
		bool Open = ImGui::TreeNode(std::string("##").append(std::to_string((int)Widget)).c_str());
		ImGui::SameLine();
		float StartY = ImGui::GetCursorScreenPos().y;//ImGui::GetCursorPosY();
		ComponentTreeItems(Widget,DrawList);		
		if(Open)
		{
			ComponentTreeAnalyzeChildren(Widget->Content,DrawList);

			ImGui::TreePop();

			ImVec2 EndPos = ImGui::GetCursorScreenPos();
			EndPos.x += 13.7;
			EndPos.y -= 13.7;
			//StartY += ImGui::GetWindowPos().y;
			DrawList->AddLine(ImVec2(EndPos.x, StartY+15), EndPos,ImColor(255,255,255,125),1.5);
			DrawList->AddLine(EndPos, ImVec2(EndPos.x + 7, EndPos.y), ImColor(255, 255, 255, 125),1.5);
		}

		//ImGui::EndGroup();
	}
	else
	{
		ComponentTreeItems(Widget,DrawList);
	}

	if (Widget->Subclass)
	{
		ComponentTreeAnalyzeChildren(Widget->Subclass,DrawList);
	}
	ComponentTreeID++;
}

static void DrawComponentTreePanel()
{
	if (ImGui::Begin(std::string(ComponentTreeTitle).append("###ComponentTreePanel").c_str()))
	{

		HImGuiWindows* SelectWindow =  ImGuiWindows.at(SelectHImGuiWindows);
		ImDrawList* DL = ImGui::GetWindowDrawList();
		float x1 = ImGui::GetCurrentWindow()->WorkRect.Min.x;
		float x2 = ImGui::GetCurrentWindow()->WorkRect.Max.x;
		float item_spacing_y = ImGui::GetStyle().ItemSpacing.y;
		float item_offset_y = -item_spacing_y * 0.5f;
		float line_height = ImGui::GetTextLineHeight() + item_spacing_y;
		ImGui::DrawRowsBackground(ComponentTreeID-1, line_height, x1, x2, item_offset_y, 0, ImGui::GetColorU32(ImVec4(0.2f, 0.2f, 0.2f, 0.25f)));
		ComponentTreeID = 1;
		for (size_t i = 0; i < SelectWindow->Widget.size(); i++)
		{
			ComponentTreeAnalyzeChildren(SelectWindow->Widget.at(i),DL);
		}
	}
	ImGui::End();


}
