#pragma once
#include <imgui.h>
#include <string>
#include <vector>
#include "HWidget.h"
//#include "PagingPanel.h"
#include <iostream>

static ImTextureID EditViewBg,MouseModeImg,ArrowModeImg;
class HImGuiWindows;
static std::vector<HImGuiWindows*> ImGuiWindows;
static int SelectHImGuiWindows = 0;
class HImGuiWindows
{
public:
	HImGuiWindows()
	{
		HImGuiWidnowsWidgetList = &Widget;
	}
	~HImGuiWindows()
	{
		for (size_t i = 0; i < Widget.size(); i++)
		{
			HWidget* SaveWidget = Widget.at(i);
			//Widget.erase(Widget.begin() + i);
			Widget.at(i) = 0;
			while (SaveWidget)
			{
				HWidget* RemoveWidget = SaveWidget;
				SaveWidget->RemoveContent();
				SaveWidget = SaveWidget->Subclass;
				delete SaveWidget;
			}
		}
		Widget.clear();
	}

	void Draw()
	{
		if (DrawInit())
			return;
		if (!Visible)
			return;

		if(HaveClose)
			ImGui::Begin(std::string(Title).append("### HWindows").c_str(), &Visible, WindowFlags);
		else
			ImGui::Begin(std::string(Title).append("### HWindows").c_str(), 0, WindowFlags);

		for (size_t i = 0; i < Widget.size(); i++)
		{
			Widget.at(i)->Draw();
		}

		if (EdMode == EditMode_ArrowMove)
		{
			ImGui::BeginChild((int)this);
			ImGui::EndChild();

			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragWidget"))
				{
					HWidget* SaveWidget = (HWidget*)payload->Data;//WidgetList.at(*(const int*)payload->Data);
					Widget.push_back(SaveWidget->CreateSelfClass());
					Widget.back()->Father = (HWidget*)this;
					Widget.back()->Flag = HWidgetFlag_WindowRootWidgetAndMove;
					Widget.back()->MovePos.x = ImGui::GetMousePos().x - ImGui::GetWindowPos().x;
					Widget.back()->MovePos.y = ImGui::GetMousePos().y - ImGui::GetWindowPos().y;
					Widget.back()->ID_ = Widget.size() - 1;
				}
				ImGui::EndDragDropTarget();
			}
		}
		else if (Widget.empty())
		{
			ImGui::Text("DropTarget");

			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragWidget"))
				{
					HWidget* SaveWidget = (HWidget*)payload->Data;//WidgetList.at(*(const int*)payload->Data);
					Widget.push_back(SaveWidget->CreateSelfClass());
					Widget.back()->Father = (HWidget*)this;
					Widget.back()->Flag = HWidgetFlag_WindowRootWidget;
					Widget.back()->ID_ = Widget.size() - 1;
				}
				ImGui::EndDragDropTarget();
			}
		}


		ImGui::End();
	}

	HWidgetExport Export(std::string Offset)
	{
		HWidgetExport ExBuff;
		ExBuff.ExportCode = "static ImGuiWindowFlags H_ImGuiWindowFlag_";
		ExBuff.ExportCode.append(GetRandText((int)this)).append(" = ").append(std::to_string(WindowFlags)).append(";");
		std::string OffsetBuff;
		if (HaveClose)
		{
			ExBuff.ExportCode.append("\n").append(Offset).append("static bool ").append(GetRandText((int)this)).append("_IsVisible = ").append(BoolToString(DefaultOpen)).append(";");
			ExBuff.ExportCode.append("\n").append(Offset).append("if(").append(GetRandText((int)this)).append("_IsVisible )\n").append(Offset).append("{\n");
			OffsetBuff = Offset;
			Offset = Offset.append("	");

			ExBuff.ExportCode.append("\n			// Draw ImGuiWindow ( ").append(Title).append(" )\n").append(Offset);
			ExBuff.ExportCode.append("if (ImGui::Begin(").append("\"").append(Title).append("###").append(GetRandText((int)this)).append("\"").append(" , 0 , ").append("H_ImGuiWindowFlag_").append(GetRandText((int)this)).append("))\n").append(Offset).append("{\n");
		}
		else
		{
			ExBuff.ExportCode.append("\n		// Draw ImGuiWindow ( ").append(Title).append(" )\n").append(Offset);
			ExBuff.ExportCode.append("if (ImGui::Begin(").append("\"").append(Title).append("###").append(GetRandText((int)this)).append("\"").append(" , 0 , ").append("H_ImGuiWindowFlag_").append(GetRandText((int)this)).append("))\n").append(Offset).append("{\n");
		}


		std::string NewOffset = Offset;
		NewOffset.append("	");
		for (size_t i = 0; i < Widget.size(); i++)
		{
			HWidgetExport Buff = Widget.at(i)->ExportWidget(NewOffset);
			ExBuff.ExportCode.append(Buff.ExportCode);

			bool buff_B;

			if (!Buff.Inculd.empty())
			{
				for (size_t i = 0; i < Buff.Inculd.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < ExBuff.Inculd.size(); q++)
					{
						if (ExBuff.Inculd.at(q) == Buff.Inculd.at(i))
						{
							buff_B = false;
							q = ExBuff.Inculd.size();
						}
					}
					if (buff_B)
						ExBuff.Inculd.push_back(Buff.Inculd.at(i));
				}
			}

			if (!Buff.Function.empty())
			{
				for (size_t i = 0; i < Buff.Function.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < ExBuff.Function.size(); q++)
					{
						if (ExBuff.Function.at(q) == Buff.Function.at(i))
						{
							buff_B = false;
							q = ExBuff.Function.size();
						}
					}
					if (buff_B)
						ExBuff.Function.push_back(Buff.Function.at(i));
				}
			}

			if (!Buff.RequestCompileFile.empty())
			{
				for (size_t i = 0; i < Buff.RequestCompileFile.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < ExBuff.RequestCompileFile.size(); q++)
					{
						if (ExBuff.RequestCompileFile.at(q) == Buff.RequestCompileFile.at(i))
						{
							buff_B = false;
							q = ExBuff.RequestCompileFile.size();
						}
					}
					if (buff_B)
						ExBuff.RequestCompileFile.push_back(Buff.RequestCompileFile.at(i));
				}
			}

			if (!Buff.Lib.empty())
			{
				for (size_t i = 0; i < Buff.Lib.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < ExBuff.Lib.size(); q++)
					{
						if (ExBuff.Lib.at(q) == Buff.Lib.at(i))
						{
							buff_B = false;
							q = ExBuff.Lib.size();
						}
					}
					if (buff_B)
						ExBuff.Lib.push_back(Buff.Lib.at(i));
				}
			}

			if (!Buff.LibPath.empty())
			{
				for (size_t i = 0; i < Buff.LibPath.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < ExBuff.LibPath.size(); q++)
					{
						if (ExBuff.LibPath.at(q) == Buff.LibPath.at(i))
						{
							buff_B = false;
							q = ExBuff.LibPath.size();
						}
					}
					if (buff_B)
						ExBuff.LibPath.push_back(Buff.LibPath.at(i));
				}
			}

			if (!Buff.InculdPath.empty())
			{
				for (size_t i = 0; i < Buff.InculdPath.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < ExBuff.InculdPath.size(); q++)
					{
						if (ExBuff.InculdPath.at(q) == Buff.InculdPath.at(i))
						{
							buff_B = false;
							q = ExBuff.InculdPath.size();
						}
					}
					if (buff_B)
						ExBuff.InculdPath.push_back(Buff.InculdPath.at(i));
				}
			}

		}
		ExBuff.ExportCode.append("\n").append(Offset).append("}\n");
		ExBuff.ExportCode.append(Offset).append("ImGui::End();\n");
		if(HaveClose)
			ExBuff.ExportCode.append(OffsetBuff).append("}");
		return ExBuff;
	}

	ImGuiWindowFlags WindowFlags = ImGuiWindowFlags_NoDocking;

	json Save()
	{
		json WindowSave;
		json WidgetList;
		// ---Save Widget List

		// Load Widget 
		for (size_t i = 0; i < Widget.size(); i++)
		{
			HWidget* SaveWidget = Widget.at(i);
			while (SaveWidget)
			{
				json WidgetData;
				WidgetData["WidgetData"] = SaveWidget->Copy();
				if (SaveWidget->Content)
					WidgetData["WidgetContent"] = SaveWidget->CopyContent();

				WidgetList.push_back(WidgetData);
				SaveWidget = SaveWidget->Subclass;
			}
		}
		// -- Save ImGuiWindow Data
		json WindowData;
		WindowData["Flags"] = WindowFlags;
		WindowData["Title"] = Title;
		WindowData["HaveClose"] = HaveClose;
		WindowData["DefaultOpen"] = DefaultOpen;

		//-- Save ImGuiWindow Data And WidgetList In Window Save
		WindowSave["WindowData"] = WindowData;
		WindowSave["WidgetList"] = WidgetList;
		return WindowSave;
	}

	HWidget* LastWidget;
	void FindAndCreateWidget(json WidgetData)
	{
		for (size_t wl = 0; wl < WidgetList.size(); wl++)
		{
			if (*WidgetList.at(wl)->WidgetNameID == WidgetData["WidgetData"]["ID"])
			{
				HWidget* LoadWidgetSave = WidgetList.at(wl)->CreateSelfClass();
				LoadWidgetSave->Paste(WidgetData["WidgetData"]);


				if (LoadWidgetSave->Flag == HWidgetFlag_WindowRootWidget || LoadWidgetSave->Flag == HWidgetFlag_WindowRootWidgetAndMove)
				{
					Widget.push_back(LoadWidgetSave);
					LoadWidgetSave->Father = (HWidget*)this;
				}
				else
				{
					LastWidget->Subclass = LoadWidgetSave;
					LoadWidgetSave->Father = LastWidget;
				}

				if (!WidgetData["WidgetContent"].is_null())
					LoadWidgetSave->PasteContent(WidgetData["WidgetContent"]);

				LastWidget = LoadWidgetSave;
				wl = WidgetList.size();
			}
		}
	}

	void Load(json J)
	{
		//-- Load WindowData And Widget List
		json WindowData, WidgetListJ;
		WindowData = J["WindowData"];
		WidgetListJ = J["WidgetList"];

		//-- Load WidgetList Data
		for (size_t i = 0; i < WidgetListJ.size(); i++)
		{
			FindAndCreateWidget(WidgetListJ.at(i));
		}

		//-- Load Window Data
		std::string WindowTitleBuff = WindowData["Title"];
		strcpy_s(Title, WindowTitleBuff.c_str());
		WindowFlags = WindowData["Flags"];
		HaveClose = WindowData["HaveClose"];
		DefaultOpen = WindowData["DefaultOpen"];
		Visible = DefaultOpen;
	}

	std::vector<HWidget*> Widget;
	char Title[120] = {"Debug"};
	bool HaveClose = false;
	bool DefaultOpen = true;
	bool Visible = true;
private:

	bool DrawInit()
	{
		bool Save = true;
		if (ImGui::Begin("EditViewport"))
		{
			Save = false;
			ImDrawList * DL = ImGui::GetWindowDrawList();
			ImVec2 WindowSize = ImGui::GetWindowSize();
			ImVec2 WindowPos = ImGui::GetWindowPos();




			//ImVec2 SaveStartPos = ImVec2(WindowSize.x - 110,WindowPos.y);


			if (WindowSize.x < WindowSize.y)
			{
				WindowPos.x += (WindowSize.x - WindowSize.y)/2;

				WindowSize.x = WindowSize.y;
				WindowSize.x += WindowPos.x;
				WindowSize.y += WindowPos.y;
			}
			else
			{
				WindowPos.y += (WindowSize.y - WindowSize.x)/2;

				WindowSize.y = WindowSize.x;
				WindowSize.x += WindowPos.x;
				WindowSize.y += WindowPos.y;
			}

			DL->AddImage(EditViewBg, WindowPos, WindowSize);


			WindowSize = ImGui::GetWindowSize();
			WindowPos = ImGui::GetWindowPos();
			ImGui::SetCursorPosX(WindowSize.x - 110);

			WindowPos.x += WindowSize.x;

			DL->AddRectFilled(ImVec2(WindowPos.x-115, WindowPos.y+30), ImVec2(WindowPos.x-5, WindowPos.y+65),ImColor(15,15,15),5);

			if(EdMode == EditMode_Mouse)
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2, 0.2, 0.2, 1));
			bool BTS = ImGui::ImageButton(MouseModeImg, ImVec2(20, 20));
			if(EdMode == EditMode_Mouse)
				ImGui::PopStyleColor();
			if(BTS)
				EdMode = EditMode_Mouse;
			
			ImGui::SameLine();

			if (EdMode == EditMode_ArrowMove)
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2, 0.2, 0.2, 1));
			BTS = ImGui::ImageButton(ArrowModeImg, ImVec2(20, 20));
			if (EdMode == EditMode_ArrowMove)
				ImGui::PopStyleColor();
			if (BTS)
				EdMode = EditMode_ArrowMove;
			ImGui::SameLine();
			if (ImGui::BeginCombo("###ArrowMoveSize","",ImGuiComboFlags_NoPreview))
			{
				ImGui::Text("Positioning");
				ImGui::SetNextItemWidth(50);
				ImGui::DragInt("##Positioning", &Positioning, 0.5, 0, 500, "Size :%d");

				ImGui::EndCombo();
			}

			//ImGui::SetCursorPos(ImVec2(12,30));
			//if (ImGui::BeginTabBar("HImGuiWindowsList"))
			//{
			//	for (size_t i = 0; i < ImGuiWindows.size(); i++)
			//	{
			//		ImGui::TabItemButton(ImGuiWindows.at(i)->Title);
			//	}
			//}
			//ImGui::EndTabBar();
			
		}
		ImGui::End();
		return Save;
	}
};


static void RemoveAllHImGuiWindows()
{
	for (size_t i = 0; i < ImGuiWindows.size(); i++)
	{
		HImGuiWindows* SaveWindow = ImGuiWindows.at(i);
		ImGuiWindows.at(i) = 0;
		delete SaveWindow;
	}
	ImGuiWindows.clear();
}