#pragma once
#include <imgui_internal.h>
#include <imgui.h>
#include <string>
#include <vector>
#include <iostream>
#include "HArrow/HArrow.h"
#include "HTranslate.h"
#include "HValue.h"
//#define GImGui  ((ImGuiContext*)GImGuiExtended) // To use custom extended context

#ifdef Editor
#define HPlugin_API __declspec(dllimport)
#else
#define HPlugin_API __declspec(dllexport)
#endif

//bool HaveWidgetFocused = false;
class HWidget;
//HWidget* (*GetWidgetData)(int Index);
//Deprecated Please use "Value"
static std::vector<HVariableExport> EVariable;
static std::vector<HVariableExport> ECacheVariable;
static std::vector<std::string> InitializationCodes;
static HWidget* SelectWidget;
static std::vector<HWidget*> WidgetList;
static std::vector<HWidget*>* HImGuiWidnowsWidgetList;
static std::string BoolToString(bool B)
{
	if (B)
		return "true";
	return "false";
}
static void AddRightClickMenu(HWidget* Widget);
static int Positioning = 10;
static json ImVec2ToJson(ImVec2& Vec)
{
	json J;
	J["X"] = Vec.x;
	J["Y"] = Vec.y;
	return J;
}

static ImVec2 JsonToImVec2(json J)
{
	ImVec2 Vec;
	Vec.x = J["X"];
	Vec.y = J["Y"];
	return Vec;
}

enum EditMode
{
	EditMode_Mouse,
	EditMode_ArrowMove
};
static EditMode EdMode = EditMode_Mouse;
enum HWidgetFlag
{
	HWidgetFlag_Null,
	HWidgetFlag_TurnRight,
	HWidgetFlag_Move,
	HWidgetFlag_WindowRootWidget,
	HWidgetFlag_WindowRootWidgetAndMove,
	HWidgetFlag_Content,
	HWidgetFlag_ContentMove,
	HWidgetFlag_MenuBar
};
struct HRect
{
	float top = 0;
	float left = 0;
	float right = 0;
	float below = 0;
};

struct HWidgetExport
{
	std::vector<std::string> Inculd;
	std::vector<std::string> RequestCompileFile;
	std::vector<std::string> Lib;
	std::vector<std::string*> Function;
	std::vector<std::string> InculdPath;
	std::vector<std::string> LibPath;
	std::string ExportCode;
};

class HWidget
{
public:
	HWidget()
	{
		if (!WidgetSize)
			WidgetSize = new HVImVec2("HSize");
		if (!MovePos)
			MovePos = new HVImVec2("HPos");

		HValues.AddHValue(MovePos);
		HValues.AddHValue(WidgetSize);
	}
	~HWidget()
	{
		HAnimation::WidgetRemoveTimeLine(this);
		//if(WidgetID > 0)
		//	delete WidgetID;
	}

	virtual void DrawIconForControlPanel() { return; }
	virtual std::string Export(std::string Offset) { return ""; }
	virtual void Draw() { return; }
	virtual void DetailPanelWidget() { return; }
	virtual HWidget* CreateSelfClass() { return NULL; }
	virtual json Copy() { return NULL; }
	virtual void Paste(json Data) { return; }

	int ID_;
	HWidget* Content = NULL;
	HWidget* Father = NULL;
	HWidget* Subclass = NULL;
	HWidgetFlag Flag = HWidgetFlag_Null;
	//int AvailableFlags = 0;
	std::string* WidgetName = NULL;
	std::string* WidgetNameID = NULL;
	std::vector<std::string>* Inculd;
	std::vector<std::string>* RequestCompileFile;
	HWidgetValues HValues;
	std::string* Lib;
	std::string* Function;
	std::string* LibPath;
	std::string* InculdPath;
	char* WidgetID;
	bool ShowDragSpace = true;
	bool CanSelectWidget = true;
	HVImVec2* MovePos;
	HVImVec2* WidgetSize;
	HArrow_SizeFlag HArrowFlag = HArrow_SizeFlag_Default;
	void DrawPreLogic()
	{
		if (Flag == HWidgetFlag_TurnRight)
		{
			ImGui::SameLine();
		}
		else if (Flag == HWidgetFlag_Move || Flag == HWidgetFlag_ContentMove || Flag == HWidgetFlag_WindowRootWidgetAndMove)
		{
			ImGui::SetCursorPos(*MovePos->Get());
		}
		else if (B)
		{
			ImVec2 SavePos = ImGui::GetCursorPos();
			SavePos.x += 15;
			SavePos.y += 15;
			ImGui::SetCursorPos(SavePos);
		}
		//if (MovePos.x == 0 && MovePos.y == 0)
		//{
		*MovePos->Get() = ImGui::GetCursorPos();
		//}

		ImGui::BeginGroup();
	}

	void DrawLogicTick()
	{
		AddRightClickMenu(this);

		if (CanSelectWidget && ImGui::IsItemHovered() && ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_MouseLeft) && !ImGui::IsMouseDragging(ImGuiMouseButton_Left))
			//if(CanSelectWidget&& !ImGui::IsMouseDragging(ImGuiMouseButton_Left)&&ImGui::IsItemActive())
		{
			DrawWidgetRect();
			if (ShowDragSpace)
				SelectWidget = this;

			//if (MovePos.x == 0 && MovePos.y == 0)
			//{
			//	MovePos = ImGui::GetCursorPos();
			//	MovePos.x -= ImGui::GetItemRectSize().x;
			//	MovePos.y -= ImGui::GetItemRectSize().y;
			//}
		}

		if (ImGui::IsItemVisible() && ShowDragSpace && EdMode == EditMode_Mouse)
		{
			//ImGuiContext& g = *GImGui;
			if (BeginDragDropTargetForHWidget())
			{
				B = true;
				//ImGui::EndDragDropTarget();
			}

			//if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && ImGui::IsItemFocused())
			//{
			//	B = true;
			//}

			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID))
			{
				SelectWidget->DrawIconForControlPanel();
				//SelectWidget = this;
				ImGui::Text(SelectWidget->WidgetName->c_str());
				//DragDropAcceptFrameCount

				ImGui::SetDragDropPayload("DragWidget", SelectWidget, sizeof(HWidget*));

				//std::cout << "\n False";
				//ImGui::SetDragDropPayload("DragWidget", &i, sizeof(int));

				ImGui::EndDragDropSource();
			}

			if (B)
			{
				ImVec2 WidgetSize = ImGui::GetItemRectSize();
				ImVec2 WidgetPos = ImGui::GetCursorPos();
				ImVec2 SaveVec = ImGui::GetCursorScreenPos();
				//WidgetPos.y -= WidgetSize.y + 5;
				HRect RootChildRect;
				RootChildRect.top = WidgetPos.y - WidgetSize.y;
				RootChildRect.right = WidgetPos.x + WidgetSize.x;
				RootChildRect.below = (WidgetPos.y - 5);

				ImGui::SetCursorPos(ImVec2(WidgetPos.x - 20, RootChildRect.top - 20));
				ImGui::BeginChild(2 + (int)this, ImVec2(WidgetSize.x + 40, WidgetSize.y + 40));

				ImGui::EndChild();

				if (!BeginDragDropTargetForHWidget())
				{
					//ImGui::EndDragDropTarget();
					B = false;
				}

				// Create Right Box

				ImGui::SetCursorPos(ImVec2(RootChildRect.right, WidgetPos.y - WidgetSize.y - 5));
				ImGui::BeginChild((int)this, ImVec2(20, WidgetSize.y), true);
				ImGui::EndChild();

				CreateHWidgetCreateAndMoveDrageTarget_RD(&SaveVec, &WidgetSize, HWidgetFlag_TurnRight);

				// Create Below Box
				//if (!Subclass || Subclass->Flag== HWidgetFlag_Null)
				//{
				ImGui::SetCursorPosY(RootChildRect.below);//可能之后有问题
				ImGui::BeginChild(1 + (int)this, ImVec2(WidgetSize.x, 20), true);

				ImGui::EndChild();

				CreateHWidgetCreateAndMoveDrageTarget_RD(&SaveVec, &WidgetSize, HWidgetFlag_Null);
				//}

				// Create Top Box
				//if ((Flag == HWidgetFlag_WindowRootWidget || Flag == HWidgetFlag_WindowRootWidgetAndMove) || Father->Flag == HWidgetFlag_Null) // << --
				//{
				ImGui::SetCursorPosY(RootChildRect.top - 20);
				ImGui::BeginChild(3 + (int)this, ImVec2(WidgetSize.x, 20), true);
				ImGui::EndChild();
				CreateHWidgetCreateAndMoveDrageTarget_LT(&SaveVec, &WidgetSize, HWidgetFlag_Null);
				//}

				// Create L Box
				//if ((Flag == HWidgetFlag_WindowRootWidget || Flag == HWidgetFlag_WindowRootWidgetAndMove) || Father->Flag == HWidgetFlag_TurnRight)
				//{
				ImGui::SetCursorPos(ImVec2(WidgetPos.x - 20, WidgetPos.y - WidgetSize.y - 5));
				ImGui::BeginChild(4 + (int)this, ImVec2(20, WidgetSize.y), true);

				ImGui::EndChild();

				CreateHWidgetCreateAndMoveDrageTarget_LT(&SaveVec, &WidgetSize, HWidgetFlag_TurnRight);
				//}
			}
			else
			{
				if (SelectWidget == this)
				{
					DrawWidgetRect();
					//if(Flag == HWidgetFlag_Move)
					//	HArray(MovePos, Positioning);
					HResize(*MovePos->Get(), *WidgetSize->Get(), Positioning, HArrowFlag);
				}
			}
		}
		else if (EdMode == EditMode_ArrowMove)
		{
			if (SelectWidget == this)
			{
				if (HArrow(*MovePos->Get(), Positioning))
				{
					if (Flag == HWidgetFlag_Content)
					{
						Flag = HWidgetFlag_ContentMove;
					}
					else if (Flag == HWidgetFlag_WindowRootWidget)
					{
						Flag = HWidgetFlag_WindowRootWidgetAndMove;
					}
					else if (Flag == HWidgetFlag_Null || Flag == HWidgetFlag_TurnRight)
					{
						Flag = HWidgetFlag_Move;
					}
				}
			}
		}

		ImGui::EndGroup();

		if (Subclass)
		{
			Subclass->Draw();
		}
	}

	void DrawWidgetRect()
	{
		ImDrawList* DL = ImGui::GetWindowDrawList();
		ImVec2 Start = ImGui::GetCursorScreenPos();

		ImVec2 End = ImGui::GetItemRectSize();
		float Y_Offset = End.y + 3;

		End.x += Start.x + 3;
		End.y += Start.y + 3 - Y_Offset;
		Start.x -= 3;
		Start.y -= 3 + Y_Offset;

		DL->AddRect(Start, End, ImColor(0, 200, 255, 50), 5, 0, 5);
	}

	void HWidgetDragSpace(HWidget*& Widget)
	{
		if (Widget == 0)
		{
			ImGui::Text("DragSpace");
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragWidget"))
				{
					if (SelectWidget != this)
					{
						HWidget* SaveWidget = SelectWidget;// (HWidget*)payload->Data;
						if (SaveWidget->Father)
						{
							//if (SaveWidget->Subclass)
							//{
							if ((SaveWidget->Flag == HWidgetFlag_WindowRootWidget || Flag == HWidgetFlag_WindowRootWidgetAndMove) && SaveWidget->Subclass)
							{
								HImGuiWidnowsWidgetList->at(SaveWidget->ID_) = SaveWidget->Subclass;
								SaveWidget->Subclass->ID_ = SaveWidget->ID_;
								SaveWidget->Subclass->Flag = SaveWidget->Flag;
							}
							else if (SaveWidget->Flag == HWidgetFlag_Content || SaveWidget->Flag == HWidgetFlag_ContentMove)
							{
								SaveWidget->Father->Content = SaveWidget->Subclass;
							}
							else
							{
								SaveWidget->Father->Subclass = SaveWidget->Subclass;
							}

							if (SaveWidget->Subclass)
							{
								SaveWidget->Subclass->Flag = SaveWidget->Flag;// << --
								SaveWidget->Flag = HWidgetFlag_Content;

								SaveWidget->Subclass->Father = SaveWidget->Father;
							}
							else
							{
								SaveWidget->Flag = HWidgetFlag_Content;
							}

							SaveWidget->Subclass = NULL;
							SaveWidget->Father = this;
							//}

							Widget = SaveWidget;
							return;
						}
						else
						{
							SaveWidget = SaveWidget->CreateSelfClass();
							SaveWidget->Father = this;
							SaveWidget->Flag = HWidgetFlag_Content;
							Widget = SaveWidget;
							return;
						}
					}
				}
				ImGui::EndDragDropTarget();
			}
		}
		else
		{
			if (EdMode == EditMode_ArrowMove)
			{
				ImVec2 SaveWidgetPos = ImGui::GetCursorPos();
				Widget->Draw();

				if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) || ImGui::IsMouseReleased(ImGuiMouseButton_Left))
				{
					float SaveYSize = (ImGui::GetCursorPosY() + ImGui::GetItemRectSize().y) - SaveWidgetPos.y;

					ImGui::SetCursorPos(SaveWidgetPos);
					if (ImGui::BeginChild((int)Widget, ImVec2(0, SaveYSize)))
						ImGui::EndChild();
				}

				if (ImGui::BeginDragDropTarget())
				{
					if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragWidget"))
					{
						if (SelectWidget != this)
						{
							HWidget* SaveWidget = SelectWidget;// (HWidget*)payload->Data;
							if (!SaveWidget->Father)
							{
								HWidget* Target = Widget->GetLastWidget();
								SaveWidget = SaveWidget->CreateSelfClass();
								SaveWidget->Father = Target;

								if (Target->Flag == HWidgetFlag_ContentMove || Target->Flag == HWidgetFlag_Content)
								{
									SaveWidget->Flag = HWidgetFlag_ContentMove;
								}
								else if (Target->Flag == HWidgetFlag_WindowRootWidget || Target->Flag == HWidgetFlag_WindowRootWidgetAndMove)
								{
									SaveWidget->Flag = HWidgetFlag_WindowRootWidgetAndMove;
								}
								else
								{
									SaveWidget->Flag = HWidgetFlag_Move;
								}

								SaveWidget->MovePos->Get()->x = ImGui::GetMousePos().x - ImGui::GetWindowPos().x;
								SaveWidget->MovePos->Get()->y = ImGui::GetMousePos().y - ImGui::GetWindowPos().y;

								Target->Subclass = SaveWidget;
								return;
							}
						}
					}
					ImGui::EndDragDropTarget();
				}
			}
			else
			{
				Widget->Draw();
			}
		}

		return;
	}

	void PreCopy(json& J)
	{
		//J["WidgetPos"] = ImVec2ToJson(MovePos->Get());
		//J["WidgetSize"] = ImVec2ToJson(WidgetSize);
		J["Flag"] = Flag;
		J["ID"] = *WidgetNameID;
		J["HValues"] = HValues.Save();
	}

	void PrePaste(json J)
	{
		//MovePos = JsonToImVec2(J["WidgetPos"]);
		//WidgetSize = JsonToImVec2(J["WidgetSize"]);
		Flag = J["Flag"];
		HValues.Load(J["HValues"]);
	}

	json CopyContent()
	{
		HWidget* SaveContent = Content;
		json OutData;
		while (SaveContent)
		{
			json JsonContent;
			//ContentItems Sdata;
			//Sdata.ID = *SaveContent->WidgetNameID;
			JsonContent["Data"] = SaveContent->Copy();
			//Sdata.Flag = SaveContent->Flag;
			//Sdata.Pos = SaveContent->MovePos;
			if (SaveContent->Content)
				JsonContent["SubclassContent"] = SaveContent->CopyContent();

			SaveContent = SaveContent->Subclass;

			OutData.push_back(JsonContent);
		}
		return OutData;
	}

	void PasteContent(json In)
	{
		HWidget* SaveWidget = NULL;// = Content;
		for (size_t Q = 0; Q < In.size(); Q++)
		{
			json JsonContent = In.at(Q);

			for (size_t i = 0; i < WidgetList.size(); i++)
			{
				json Widget = JsonContent["Data"];
				if (*WidgetList.at(i)->WidgetNameID == Widget["ID"])
				{
					HWidget* NowWidget = SaveWidget;

					SaveWidget = WidgetList.at(i)->CreateSelfClass();
					SaveWidget->Paste(Widget);
					SaveWidget->Flag = Widget["Flag"];
					//SaveWidget->MovePos = Sdata->Pos;
					if (!JsonContent["SubclassContent"].is_null())
					{
						SaveWidget->PasteContent(JsonContent["SubclassContent"]);
					}

					if (Q == 0)
					{
						Content = SaveWidget;
						SaveWidget->Father = this;
					}
					else
					{
						NowWidget->Subclass = SaveWidget;
						SaveWidget->Father = NowWidget;
					}

					i = WidgetList.size();
				}
			}
		}
	}

	void RemoveContent()
	{
		HWidget* SaveWidget = Content;

		while (SaveWidget)
		{
			if (SaveWidget->Content)
				SaveWidget->RemoveContent();

			HWidget* SaveSaveWidget = SaveWidget;
			SaveWidget = SaveWidget->Subclass;
			delete SaveSaveWidget;
		}
	}

	void MoveWidget_RD(HWidget* Target, HWidgetFlag NewFlag)
	{
		HWidget* SaveWidget = Target;
		if (SelectWidget->Content)
		{
			if (SelectWidget->Content->Find(this))
			{
				return;
			}
		}

		if (SelectWidget->Father)
		{
			SaveWidget = SelectWidget;
			if (SaveWidget != Subclass)
			{
				if (SaveWidget->Subclass)
				{
					if (SaveWidget->Flag == HWidgetFlag_WindowRootWidget || SaveWidget->Flag == HWidgetFlag_WindowRootWidgetAndMove)
					{
						HImGuiWidnowsWidgetList->at(SaveWidget->ID_) = SaveWidget->Subclass;
						SaveWidget->Subclass->ID_ = SaveWidget->ID_;
						SaveWidget->Subclass->Flag = SaveWidget->Flag;
					}
					else
					{
						if (SaveWidget->Flag == HWidgetFlag_Content || SaveWidget->Flag == HWidgetFlag_ContentMove)
						{
							SaveWidget->Subclass->Flag = SaveWidget->Flag;
							//SaveWidget->Father->Content = SaveWidget->Subclass;
						}
						//else
						//	SaveWidget->Father->Subclass = SaveWidget->Subclass;
					}

					SaveWidget->Subclass->Father = SaveWidget->Father;
				}

				if (SaveWidget->Flag == HWidgetFlag_Content || SaveWidget->Flag == HWidgetFlag_ContentMove)
				{
					SaveWidget->Father->Content = SaveWidget->Subclass;
					//SaveWidget->Subclass->Father = SaveWidget->Father;
				}
				else
					SaveWidget->Father->Subclass = SaveWidget->Subclass;

				if (Subclass)
				{
					if (SaveWidget->Flag == HWidgetFlag_Content || SaveWidget->Flag == HWidgetFlag_ContentMove)
						SaveWidget->Father->Content = SaveWidget->Subclass;
					else
						SaveWidget->Father->Subclass = SaveWidget->Subclass;

					HWidget* SubclassSave;
					SubclassSave = SaveWidget->CreateSelfClass();
					SubclassSave->Father = this;

					SubclassSave->Paste(SaveWidget->Copy());
					if (SaveWidget->Content) // << --
					{
						SubclassSave->PasteContent(SaveWidget->CopyContent());
						SaveWidget->RemoveContent();
					}
					SubclassSave->Flag = NewFlag;
					SubclassSave->Subclass = Subclass;

					Subclass->Father = SubclassSave;//

					Subclass = SubclassSave;
				}
				else
				{
					Subclass = SaveWidget->CreateSelfClass();

					Subclass->Father = this;

					Subclass->Paste(SaveWidget->Copy());
					Subclass->Flag = NewFlag;
					if (SaveWidget->Content)
					{
						Subclass->PasteContent(SaveWidget->CopyContent());
						SaveWidget->RemoveContent();
					}
				}

				SelectWidget = NULL;
				delete SaveWidget;
			}
			else if (SaveWidget->Flag != NewFlag)
			{
				SaveWidget->Flag = NewFlag;
			}
		}
		else
		{
			SaveWidget = SaveWidget->CreateSelfClass();

			SaveWidget->Flag = NewFlag;

			if (Subclass)
			{
				SaveWidget->Subclass = Subclass;
				SaveWidget->Father = this;

				Subclass->Father = SaveWidget;
				Subclass = SaveWidget;
			}
			else
			{
				SaveWidget->Father = this;
				Subclass = SaveWidget;
			}
		}
	}

	void MoveWidget_LT(HWidget* Target, HWidgetFlag NewFlag)
	{
		HWidget* SaveWidget = Target;
		if (SelectWidget->Content)
		{
			if (SelectWidget->Content->Find(this))
			{
				return;
			}
		}
		if (SelectWidget->Father)
		{
			SaveWidget = SelectWidget;
			if (SaveWidget != Father)
			{
				if (Flag == HWidgetFlag_WindowRootWidget || Flag == HWidgetFlag_WindowRootWidgetAndMove)
				{
					HWidget* SaveCreateWidget = SaveWidget->CreateSelfClass();

					SaveCreateWidget->Paste(SaveWidget->Copy());
					if (SaveWidget->Content)
					{
						SaveCreateWidget->PasteContent(SaveWidget->CopyContent());
						SaveWidget->RemoveContent();
					}

					if (SaveWidget->Father)
					{
						if (SaveWidget->Flag == HWidgetFlag_Content || SaveWidget->Flag == HWidgetFlag_ContentMove)
						{
							SaveWidget->Father->Content = SaveWidget->Subclass;
						}
						else
							SaveWidget->Father->Subclass = SaveWidget->Subclass;
					}

					SaveCreateWidget->Father = Father;

					HImGuiWidnowsWidgetList->at(ID_) = SaveCreateWidget;
					SaveCreateWidget->ID_ = ID_;
					SaveCreateWidget->Flag = Flag;

					Flag = NewFlag;
					SaveCreateWidget->Subclass = this;
					Father = SaveCreateWidget;
				}
				else
				{
					HWidget* SaveCreateWidget = SaveWidget->CreateSelfClass();

					SaveCreateWidget->Father = Father;

					if (SaveWidget->Father)
					{
						if (SaveWidget->Flag == HWidgetFlag_WindowRootWidget || SaveWidget->Flag == HWidgetFlag_WindowRootWidgetAndMove)
						{
							HImGuiWidnowsWidgetList->at(SaveWidget->ID_) = SaveWidget->Subclass;
							SaveWidget->Subclass->ID_ = SaveWidget->ID_;
							SaveWidget->Subclass->Flag = SaveWidget->Flag;
						}
						else if (SaveWidget->Father->Flag == HWidgetFlag_Content || SaveWidget->Father->Flag == HWidgetFlag_ContentMove)
						{
							SaveWidget->Father->Content = SaveWidget->Subclass;
						}
						//else if (SaveWidget->Flag == HWidgetFlag_Content)
						//{
						//	SaveWidget->Father->Content = SaveWidget->Subclass;
						//}
						else
							SaveWidget->Father->Subclass = SaveWidget->Subclass;
					}

					SaveCreateWidget->Paste(SaveWidget->Copy());
					if (SaveWidget->Content)
					{
						SaveCreateWidget->PasteContent(SaveWidget->CopyContent());
						SaveWidget->RemoveContent();
						//SaveWidget->Content = NULL;
					}

					SaveCreateWidget->Flag = Flag;
					Flag = NewFlag;
					SaveCreateWidget->Subclass = this;

					if (SaveCreateWidget->Flag == HWidgetFlag_Content || SaveCreateWidget->Flag == HWidgetFlag_ContentMove)
						Father->Content = SaveCreateWidget;
					else
						Father->Subclass = SaveCreateWidget;
					//if(Flag == HWidgetFlag_Content)
					//	Father->Content = SaveCreateWidget;
					//else
					Subclass = SaveWidget->Subclass; // << -- Test
					Father = SaveCreateWidget;
				}

				SelectWidget = NULL;
				delete SaveWidget;
			}
			else if (!(SaveWidget->Flag == HWidgetFlag_WindowRootWidget || SaveWidget->Flag == HWidgetFlag_WindowRootWidgetAndMove || SaveWidget->Flag == HWidgetFlag_Content || SaveWidget->Flag == HWidgetFlag_ContentMove) && SaveWidget->Flag != NewFlag)
			{
				SaveWidget->Flag = NewFlag;
			}
		}
		else
		{
			SaveWidget = SaveWidget->CreateSelfClass();

			if (Flag == HWidgetFlag_WindowRootWidget || Flag == HWidgetFlag_WindowRootWidgetAndMove)
			{
				HImGuiWidnowsWidgetList->at(ID_) = SaveWidget;
				SaveWidget->ID_ = ID_;
				SaveWidget->Flag = Flag;
			}
			SaveWidget->Father = Father;
			if (Flag == HWidgetFlag_Content || Flag == HWidgetFlag_ContentMove)
				SaveWidget->Flag = Flag;
			Flag = NewFlag;

			SaveWidget->Subclass = this;
			if (SaveWidget->Flag == HWidgetFlag_Content || SaveWidget->Flag == HWidgetFlag_ContentMove)
				Father->Content = SaveWidget;
			else
				Father->Subclass = SaveWidget;
			Father = SaveWidget;
		}
	}

	std::string GetID()
	{
		if (WidgetID)
			return std::string(WidgetID).append("###").append(*WidgetNameID).append(std::to_string((int)this));
		return "Not Widget ID";
	}

	std::string GetItemsExport(std::string Offset)
	{
		if (Content)
		{
			ContentExcessiveData = new HWidgetExport(Content->ExportWidget(Offset.append("	")));

			return ContentExcessiveData->ExportCode;
		}

		return std::string(Offset).append("\n").append(Offset).append("\n");
	}

	HWidgetExport ExportWidget(std::string Offset)
	{
		HValues.ExportValue(this, EVariable, ECacheVariable);
		HWidgetExport Save;
		//std::string Save;
		if (Flag == HWidgetFlag_TurnRight)
		{
			Save.ExportCode.append("\n").append(Offset);
			Save.ExportCode.append("ImGui::SameLine();\n");
		}
		else if (Flag == HWidgetFlag_Move || Flag == HWidgetFlag_ContentMove || Flag == HWidgetFlag_WindowRootWidgetAndMove)
		{
			//EVariable.push_back(MovePos->GetVariableExport(this));
			Save.ExportCode.append("\n").append(Offset);
			Save.ExportCode.append("ImGui::SetCursorPos(");
			Save.ExportCode.append(MovePos->AutoGetOutputValue(this));
			Save.ExportCode.append(");\n");
		}

		Save.ExportCode.append(Export(Offset));
		Save.ExportCode.append("\n");//.append(Offset);
		bool buff_B = true;
		if (Subclass || Content)
		{
			HWidgetExport Buff;
			if (Subclass)
			{
				Buff = Subclass->ExportWidget(Offset);
				if (Content)
				{
					for (size_t i = 0; i < ContentExcessiveData->Function.size(); i++)
					{
						Buff.Function.push_back(ContentExcessiveData->Function.at(i));
					}
					for (size_t i = 0; i < ContentExcessiveData->Inculd.size(); i++)
					{
						Buff.Inculd.push_back(ContentExcessiveData->Inculd.at(i));
					}
					for (size_t i = 0; i < ContentExcessiveData->RequestCompileFile.size(); i++)
					{
						Buff.RequestCompileFile.push_back(ContentExcessiveData->RequestCompileFile.at(i));
					}
					for (size_t i = 0; i < ContentExcessiveData->Lib.size(); i++)
					{
						Buff.Lib.push_back(ContentExcessiveData->Lib.at(i));
					}
					for (size_t i = 0; i < ContentExcessiveData->LibPath.size(); i++)
					{
						Buff.LibPath.push_back(ContentExcessiveData->LibPath.at(i));
					}
					for (size_t i = 0; i < ContentExcessiveData->InculdPath.size(); i++)
					{
						Buff.InculdPath.push_back(ContentExcessiveData->InculdPath.at(i));
					}
				}
			}
			else
			{
				Buff = *ContentExcessiveData;
				delete ContentExcessiveData;
				ContentExcessiveData = 0;
			}

			Save.ExportCode.append(Buff.ExportCode);

			if (!Buff.Function.empty())
			{
				for (size_t i = 0; i < Buff.Function.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < Save.Function.size(); q++)
					{
						if (Save.Function.at(q) == Buff.Function.at(i))
						{
							buff_B = false;
							q = Save.Function.size();
						}
					}
					if (buff_B)
						Save.Function.push_back(Buff.Function.at(i));
				}
			}

			if (!Buff.Inculd.empty())
			{
				for (size_t i = 0; i < Buff.Inculd.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < Save.Inculd.size(); q++)
					{
						if (Save.Inculd.at(q) == Buff.Inculd.at(i))
						{
							buff_B = false;
							q = Save.Inculd.size();
						}
					}
					if (buff_B)
						Save.Inculd.push_back(Buff.Inculd.at(i));
				}
			}

			if (!Buff.Lib.empty())
			{
				for (size_t i = 0; i < Buff.Lib.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < Save.Lib.size(); q++)
					{
						if (Save.Lib.at(q) == Buff.Lib.at(i))
						{
							buff_B = false;
							q = Save.Lib.size();
						}
					}
					if (buff_B)
						Save.Lib.push_back(Buff.Lib.at(i));
				}
			}
			if (!Buff.LibPath.empty())
			{
				for (size_t i = 0; i < Buff.LibPath.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < Save.LibPath.size(); q++)
					{
						if (Save.LibPath.at(q) == Buff.LibPath.at(i))
						{
							buff_B = false;
							q = Save.LibPath.size();
						}
					}
					if (buff_B)
						Save.LibPath.push_back(Buff.LibPath.at(i));
				}
			}
			if (!Buff.InculdPath.empty())
			{
				for (size_t i = 0; i < Buff.InculdPath.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < Save.InculdPath.size(); q++)
					{
						if (Save.InculdPath.at(q) == Buff.InculdPath.at(i))
						{
							buff_B = false;
							q = Save.InculdPath.size();
						}
					}
					if (buff_B)
						Save.InculdPath.push_back(Buff.InculdPath.at(i));
				}
			}

			if (!Buff.RequestCompileFile.empty())
			{
				for (size_t i = 0; i < Buff.RequestCompileFile.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < Save.RequestCompileFile.size(); q++)
					{
						if (Save.RequestCompileFile.at(q) == Buff.RequestCompileFile.at(i))
						{
							buff_B = false;
							q = Save.RequestCompileFile.size();
						}
					}
					if (buff_B)
						Save.RequestCompileFile.push_back(Buff.RequestCompileFile.at(i));
				}
			}
		}
		if (Function)
		{
			buff_B = true;
			for (size_t i = 0; i < Save.Function.size(); i++)
			{
				if (Save.Function.at(i) == Function)
				{
					buff_B = false;
					i = Save.Function.size();
				}
			}
			if (buff_B)
			{
				Save.Function.push_back(Function);
			}
		}
		if (Inculd)
		{
			for (size_t i = 0; i < Inculd->size(); i++)
			{
				buff_B = true;
				for (size_t q = 0; q < Save.Inculd.size(); q++)
				{
					if (Save.Inculd.at(q) == Inculd->at(i))
					{
						buff_B = false;
						q = Save.Inculd.size();
					}
				}
				if (buff_B)
					Save.Inculd.push_back(Inculd->at(i));
			}
		}
		if (Lib)
		{
			buff_B = true;
			for (size_t i = 0; i < Save.Lib.size(); i++)
			{
				if (Save.Lib.at(i) == *Lib)
				{
					buff_B = false;
					i = Save.Lib.size();
				}
			}
			if (buff_B)
				Save.Lib.push_back(*Lib);
		}
		if (LibPath)
		{
			buff_B = true;
			for (size_t i = 0; i < Save.LibPath.size(); i++)
			{
				if (Save.LibPath.at(i) == *LibPath)
				{
					buff_B = false;
					i = Save.LibPath.size();
				}
			}
			if (buff_B)
				Save.LibPath.push_back(*LibPath);
		}
		if (InculdPath)
		{
			buff_B = true;
			for (size_t i = 0; i < Save.InculdPath.size(); i++)
			{
				if (Save.InculdPath.at(i) == *InculdPath)
				{
					buff_B = false;
					i = Save.InculdPath.size();
				}
			}
			if (buff_B)
				Save.InculdPath.push_back(*InculdPath);
		}
		if (RequestCompileFile)
		{
			for (size_t i = 0; i < RequestCompileFile->size(); i++)
			{
				buff_B = true;
				for (size_t q = 0; q < Save.RequestCompileFile.size(); q++)
				{
					if (RequestCompileFile->at(i) == Save.RequestCompileFile.at(q))
					{
						buff_B = false;
						q = Save.RequestCompileFile.size();
					}
				}
				if (buff_B)
					Save.RequestCompileFile.push_back(RequestCompileFile->at(i));
			}
		}

		return Save;
	}

private:
	bool B = false;

	HWidgetExport* ContentExcessiveData = 0;

	bool BeginDragDropTargetForHWidget()
	{
		ImGuiContext& g = *GImGui;
		if (!g.DragDropActive)
			return false;

		ImGuiWindow* window = g.CurrentWindow;
		if (!(g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect))
			return false;

		ImGuiWindow* hovered_window = g.HoveredWindowUnderMovingWindow;
		if (hovered_window == NULL || window->RootWindowDockTree != hovered_window->RootWindowDockTree || window->SkipItems)
			return false;
		if (SelectWidget == this)
			return false;
		return true;
	}

	void CreateHWidgetCreateAndMoveDrageTarget_RD(ImVec2* SaveVec, ImVec2* WidgetSize, HWidgetFlag NewFlag)
	{
		if (ImGui::BeginDragDropTarget())
		{
			ImDrawList* DL = ImGui::GetForegroundDrawList();
			if (NewFlag == HWidgetFlag_TurnRight)
			{
				DL->AddLine(ImVec2(SaveVec->x + WidgetSize->x + 10, SaveVec->y - (WidgetSize->y + 5)), ImVec2(SaveVec->x + WidgetSize->x + 10, SaveVec->y), ImColor(255, 255, 255), 2);
			}
			else if (NewFlag == HWidgetFlag_Null)
			{
				DL->AddLine(ImVec2(SaveVec->x, SaveVec->y + 5), ImVec2(SaveVec->x + WidgetSize->x, SaveVec->y + 5), ImColor(255, 255, 255), 2);
			}

			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragWidget"))
			{
				MoveWidget_RD((HWidget*)payload->Data, NewFlag);
			}
			ImGui::EndDragDropTarget();
		}
	}

	void CreateHWidgetCreateAndMoveDrageTarget_LT(ImVec2* SaveVec, ImVec2* WidgetSize, HWidgetFlag NewFlag)
	{
		if (ImGui::BeginDragDropTarget())
		{
			ImDrawList* DL = ImGui::GetForegroundDrawList();
			if (NewFlag == HWidgetFlag_TurnRight)
			{
				DL->AddLine(ImVec2(SaveVec->x - 10, SaveVec->y - (WidgetSize->y + 5)), ImVec2(SaveVec->x - 10, SaveVec->y), ImColor(255, 255, 255), 2);
			}
			else if (NewFlag == HWidgetFlag_Null)
			{
				DL->AddLine(ImVec2(SaveVec->x, SaveVec->y - (WidgetSize->y + 5)), ImVec2(SaveVec->x + WidgetSize->x, SaveVec->y - (WidgetSize->y + 5)), ImColor(255, 255, 255), 2);
			}

			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DragWidget"))
			{
				MoveWidget_LT((HWidget*)payload->Data, NewFlag);
			}
			ImGui::EndDragDropTarget();
		}
	}

	bool Find(HWidget* Target)
	{
		if (this == Target)
			return true;
		if (Content)
			if (Content->Find(Target))
				return true;
		if (Subclass)
			if (Subclass->Find(Target))
				return true;
		return false;
	}

	HWidget* GetLastWidget()
	{
		if (Subclass)
		{
			return Subclass->GetLastWidget();
		}
		else
		{
			return this;
		}
	}
};

static void DeleteWidget(HWidget* SaveWidget)
{
	if (SaveWidget->Father != NULL)
	{
		if (SaveWidget->Subclass != NULL)
		{
			if (SaveWidget->Flag == HWidgetFlag_WindowRootWidget || SaveWidget->Flag == HWidgetFlag_WindowRootWidgetAndMove)
			{
				//HImGuiWindows* ImguiWindows = (HImGuiWindows*)SaveWidget->Father;
				SaveWidget->Subclass->ID_ = SaveWidget->ID_;
				SaveWidget->Subclass->Father = SaveWidget->Father;
				SaveWidget->Subclass->Flag = SaveWidget->Flag;

				HImGuiWidnowsWidgetList->at(SaveWidget->ID_) = SaveWidget->Subclass;
			}
			else
			{
				if (SaveWidget->Flag == HWidgetFlag_Content || SaveWidget->Flag == HWidgetFlag_ContentMove)
					SaveWidget->Father->Content = SaveWidget->Subclass;
				else
					SaveWidget->Father->Subclass = SaveWidget->Subclass;
				SaveWidget->Subclass->Father = SaveWidget->Father;
				SaveWidget->Subclass->Flag = SaveWidget->Flag;
			}
		}
		else
		{
			if (SaveWidget->Flag == HWidgetFlag_WindowRootWidget || SaveWidget->Flag == HWidgetFlag_WindowRootWidgetAndMove)
			{
				//HImGuiWindows* ImguiWindows = (HImGuiWindows*)SaveWidget->Father;
				HImGuiWidnowsWidgetList->erase(HImGuiWidnowsWidgetList->begin() + SaveWidget->ID_);

				for (size_t i = 0; i < HImGuiWidnowsWidgetList->size(); i++)
				{
					HImGuiWidnowsWidgetList->at(i)->ID_ = i;
				}
			}
			else if (SaveWidget->Flag == HWidgetFlag_Content || SaveWidget->Flag == HWidgetFlag_ContentMove)
			{
				SaveWidget->Father->Content = NULL;
			}
			else
			{
				SaveWidget->Father->Subclass = NULL;
			}
		}

		if (SaveWidget->Content)
			SaveWidget->RemoveContent();
		delete SaveWidget;
		SelectWidget = NULL;
	}
}

namespace RightClickMenuT
{
	static std::string RemoveWidget = "Remove Widget";
	static std::string layout = "layout";
	static std::string Default = "Default";
	static std::string Move = "Move";
	static std::string SortRight = "Sort Right";
	static std::string ShowDragSpace = "ShowDragSpace";
	static std::string CanSelect = "Can Select";
}
#define RightClickMenuInit TranslateObject.push_back(&RightClickMenuT::RemoveWidget);\
TranslateObject.push_back(&RightClickMenuT::layout);\
TranslateObject.push_back(&RightClickMenuT::Default);\
TranslateObject.push_back(&RightClickMenuT::Move);\
TranslateObject.push_back(&RightClickMenuT::SortRight);\
TranslateObject.push_back(&RightClickMenuT::ShowDragSpace);\
TranslateObject.push_back(&RightClickMenuT::CanSelect);

void AddRightClickMenu(HWidget* Widget)
{
	if (!Widget)
		return;

	if (ImGui::BeginPopupContextItem(std::to_string((int)Widget).c_str()))
	{
		ImGui::Text(Widget->WidgetName->c_str());
		ImGui::Separator();
		if (ImGui::MenuItem(RightClickMenuT::RemoveWidget.c_str()))
		{
			DeleteWidget(Widget);
		}

		if (ImGui::BeginMenu(RightClickMenuT::layout.c_str()))
		{
			if (Widget->Flag == HWidgetFlag_ContentMove || Widget->Flag == HWidgetFlag_Content)
			{
				if (ImGui::MenuItem(RightClickMenuT::Default.c_str(), "", Widget->Flag == HWidgetFlag_Content))
				{
					Widget->Flag = HWidgetFlag_Content;
				}
				if (ImGui::MenuItem(RightClickMenuT::Move.c_str(), "", Widget->Flag == HWidgetFlag_ContentMove))
				{
					Widget->Flag = HWidgetFlag_ContentMove;
				}
			}
			else if (Widget->Flag == HWidgetFlag_WindowRootWidget || Widget->Flag == HWidgetFlag_WindowRootWidgetAndMove)
			{
				if (ImGui::MenuItem(RightClickMenuT::Default.c_str(), "", Widget->Flag == HWidgetFlag_WindowRootWidget))
				{
					Widget->Flag = HWidgetFlag_WindowRootWidget;
				}
				if (ImGui::Selectable(RightClickMenuT::Move.c_str(), Widget->Flag == HWidgetFlag_WindowRootWidgetAndMove))
				{
					Widget->Flag = HWidgetFlag_WindowRootWidgetAndMove;
				}
			}
			else
			{
				if (ImGui::Selectable(RightClickMenuT::SortRight.c_str(), Widget->Flag == HWidgetFlag_TurnRight))
				{
					Widget->Flag = HWidgetFlag_TurnRight;
				}
				if (ImGui::Selectable(RightClickMenuT::Default.c_str(), Widget->Flag == HWidgetFlag_Null))
				{
					Widget->Flag = HWidgetFlag_Null;
				}
				if (ImGui::Selectable(RightClickMenuT::Move.c_str(), Widget->Flag == HWidgetFlag_Move))
				{
					Widget->Flag = HWidgetFlag_Move;
					//Widget->MovePos = ImGui::GetCursorPos();
				}
			}

			ImGui::EndMenu();
		}

		ImGui::MenuItem(RightClickMenuT::ShowDragSpace.c_str(), "", &Widget->ShowDragSpace);

		ImGui::MenuItem(RightClickMenuT::CanSelect.c_str(), "", &Widget->CanSelectWidget);

		ImGui::EndPopup();
	}
}