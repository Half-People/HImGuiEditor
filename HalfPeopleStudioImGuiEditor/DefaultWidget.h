#pragma once
#include "HWidget.h"
#include "HImGuiWidgetItem.h"

static std::string DefaultWidgetButton = "Button";
static std::string DefaultWidgetButtonID = "Button";
class Button :public HWidget
{
public:
	Button()
	{
		WidgetName = &DefaultWidgetButton;
		WidgetNameID = &DefaultWidgetButtonID;
		WidgetID = Text;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Move;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Null;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_TurnRight;
	}

	virtual void DrawIconForControlPanel()override
	{
		ImGui::Button("Button");
		return;
	}
	virtual std::string Export(std::string Offset) override
	{
		if (WidgetSize.x == 0 && WidgetSize.y == 0)
		{
			return std::string(Offset).append("ImGui::Button( \"").append(GetID()).append("\" );");
		}

		return std::string(Offset).append("ImGui::Button( \"").append(GetID())/*.append("##").append(std::to_string(ID_))*/.append("\" , ImVec2( ").append(std::to_string(WidgetSize.x)).append(" , ").append(std::to_string(WidgetSize.y)).append(" ));");
	}
	virtual void Draw()override
	{
		DrawPreLogic();
		ImGui::Button(GetID().c_str(), WidgetSize);
		DrawLogicTick();
		return;
	}
	virtual void DetailPanelWidget()override
	{
		//char Save[200] = {};
		//strncpy(Save, Text.c_str(), sizeof(Save));

		ImGui::InputText("Button Text", Text, 200);
		//ImGui::DragFloat2("Button Size", (float*)&WidgetSize, 0.2, 5);
		return;
	}
	virtual HWidget* CreateSelfClass()override {
		return new Button();
	}

	virtual json Copy()override {
		json J;
		PreCopy(J);
		J["WidgetName"] = Text;
		return J;
	}
	virtual void Paste(json Data)override {
		PrePaste(Data);

		std::string Name = Data["WidgetName"];
		strcpy_s(Text, Name.c_str());
		return;
	}

private:
	//std::string Text = "Button";
	char Text[200] = { "Button" };
	//ImVec2 Size = ImVec2(0, 0);
};
static std::string DefaultWidgetText = "Text";
static std::string DefaultWidgetTextID = "Text";
class Text :public HWidget
{
public:
	Text()
	{
		WidgetName = &DefaultWidgetText;
		WidgetNameID = &DefaultWidgetTextID;
		WidgetID = TextData;
		HArrowFlag = HArrow_SizeFlag_NotResize;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Move;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Null;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_TurnRight;
	}

	virtual void DrawIconForControlPanel()override
	{
		ImGui::Text("Text");
		return;
	}
	virtual std::string Export(std::string Offset) override
	{
		return std::string("\n").append(Offset).append("ImGui::Text(\"").append(TextData).append("\"); ");
	}
	virtual void Draw()override
	{
		DrawPreLogic();
		ImGui::Text(TextData);
		DrawLogicTick();
		return;
	}
	virtual void DetailPanelWidget()override
	{
		//char Save[200] = {};
		//strncpy(Save, Text.c_str(), sizeof(Save));

		ImGui::InputText("TextData", TextData, sizeof(TextData));

		return;
	}
	virtual HWidget* CreateSelfClass()override { return new Text(); }

	virtual json Copy()override {
		json J;
		PreCopy(J);
		J["WidgetText"] = TextData;
		return J;
	}
	virtual void Paste(json Data)override {
		PrePaste(Data);
		std::string ST = Data["WidgetText"];

		strcpy_s(TextData, 200, ST.c_str());

		return;
	}
private:
	//std::string Text = "Button";
	char TextData[200] = { "Text" };
};
static std::string DefaultWidgetTreeNode = "TreeNode";
static std::string DefaultWidgetTreeNodeID = "TreeNode";
class TreeNode :public HWidget
{
public:
	TreeNode()
	{
		WidgetName = &DefaultWidgetTreeNode;
		WidgetNameID = &DefaultWidgetTreeNodeID;
		WidgetID = TreeName;
		HArrowFlag = HArrow_SizeFlag_NotResize;
	}

	virtual void DrawIconForControlPanel()override
	{
		if (ImGui::TreeNode("TreeNode"))
		{
			ImGui::Text("Null");
			ImGui::TreePop();
		}

		return;
	}
	virtual std::string Export(std::string Offset) override
	{
		return std::string(Offset).append("if(ImGui::TreeNode(\"").append(GetID()).append("\"))\n").append(Offset).append("{\n").append(GetItemsExport(Offset)).append("\n").append(Offset).append("	ImGui::TreePop();").append("\n").append(Offset).append("}");
	}
	virtual void Draw()override
	{
		DrawPreLogic();

		if (ImGui::TreeNode(GetID().c_str()))
		{
			//if (!Content)
			//{
			//	ImGui::Text("DragSpace");
			//	Content = HWidgetDragSpace();
			//	//if (Content)
			//	//{
			//	//	Content =Content->CreateSelfClass();
			//	//	Content->Father = this;
			//	//	Content->Flag = HWidgetFlag_Content;
			//	//}
			//}
			//else
			//{
			//	Content->Draw();
			//}
			HWidgetDragSpace(Content);

			ImGui::TreePop();
			ShowDragSpace = false;
		}
		else
		{
			ShowDragSpace = true;
		}
		DrawLogicTick();
		return;
	}
	virtual void DetailPanelWidget()override
	{
		//char Save[200] = {};
		//strncpy(Save, Text.c_str(), sizeof(Save));

		ImGui::InputText("TreeName", TreeName, 200);

		return;
	}
	virtual HWidget* CreateSelfClass()override { return new TreeNode(); }

	virtual json Copy()override {
		json J;
		PreCopy(J);
		J["WidgetName"] = TreeName;
		return J;
	}
	virtual void Paste(json Data)override {
		PrePaste(Data);
		std::string TrreNameS = Data["WidgetName"];

		strcpy_s(TreeName, TrreNameS.c_str());
		return;
	}

private:
	//std::string Text = "Button";
	//HWidget* HWidgetList;
	char TreeName[200] = { "TreeNode" };
};
static std::string DefaultWidgetGroup = "Group";
static std::string DefaultWidgetGroupID = "Group";
class Group :public HWidget
{
public:
	Group()
	{
		WidgetName = &DefaultWidgetGroup;
		WidgetNameID = &DefaultWidgetGroupID;
		CanSelectWidget = false;
		//WidgetID = TextData;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Move;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Null;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_TurnRight;
	}

	virtual void DrawIconForControlPanel()override
	{
		//ImGui::Text("Text");
		return;
	}
	virtual std::string Export(std::string Offset) override
	{
		return std::string(Offset).append("ImGui::BeginGroup();\n").append(GetItemsExport(Offset)).append("\n").append(Offset).append("ImGui::EndGroup();\n");
	}
	virtual void Draw()override
	{
		DrawPreLogic();
		ImGui::BeginGroup();

		//if (!Content)
		//{
		//	ImGui::Text("DragSpace");
		//	Content = HWidgetDragSpace();
		//	//if (Content)
		//	//{
		//	//	Content = Content->CreateSelfClass();
		//	//}
		//}
		//else
		//{
		//	Content->Draw();
		//}
		HWidgetDragSpace(Content);

		ImGui::EndGroup();
		DrawLogicTick();
		return;
	}
	virtual void DetailPanelWidget()override
	{
		//char Save[200] = {};
		//strncpy(Save, Text.c_str(), sizeof(Save));

		//ImGui::InputText("TextData", TextData, sizeof(TextData));

		return;
	}
	virtual HWidget* CreateSelfClass()override { return new Group(); }

	virtual json Copy()override {
		json J;
		PreCopy(J);
		return J;//ST;
	}
	virtual void Paste(json Data)override {
		PrePaste(Data);

		return;
	}
private:
	//std::string Text = "Button";
	//char TextData[200] = { "Text" };
};
static std::string DefaultWidgetChild = "ChildWindow";
static std::string DefaultWidgetChildID = "ChildWindow";
class Child :public HWidget
{
public:
	Child()
	{
		WidgetName = &DefaultWidgetChild;
		WidgetNameID = &DefaultWidgetChildID;
		CanSelectWidget = false;
		WidgetID = TextData;
	}

	virtual void DrawIconForControlPanel()override
	{
		//ImGui::Text("Text");
		if (ImGui::BeginChild("DID", ImVec2(50, 50), true))
		{
		}
		ImGui::EndChild();
		return;
	}
	virtual std::string Export(std::string Offset) override
	{
		std::string SaveRandText = GetRandText((int)this, 15);
		std::string SaveExportText;
		//ImGuiWindowFlags _HV__ChildFlag = _THV_
		SaveExportText.append("\n").append(Offset).append("ImGuiWindowFlags ").append(SaveRandText).append("_ChildFlag = ").append(std::to_string(ChildFlag)).append(";");
		//if(ImGui::BeginChild(_HV_,ImVec2(_THV_,_THV_),_HV_,))
		SaveExportText.append("\n").append(Offset).append("if(ImGui::BeginChild(\"").append(GetID()).append("\",ImVec2(").append(std::to_string(WidgetSize.x)).append(",").append(std::to_string(WidgetSize.y)).append("),").append(BoolToString(border)).append(",").append(SaveRandText).append("_ChildFlag ))");
		//{
		SaveExportText.append("\n").append(Offset).append("{");
		//	_HV_
		SaveExportText.append("\n").append(GetItemsExport(Offset));
		//}
		SaveExportText.append("\n").append(Offset).append("}");
		//ImGui::EndChild();
		SaveExportText.append("\n").append(Offset).append("ImGui::EndChild();");
		return SaveExportText;

		//return std::string(Offset).append("ImGui::BeginGroup();\n").append(GetItemsExport(Offset)).append("\n").append(Offset).append("ImGui::EndGroup();\n");
	}
	virtual void Draw()override
	{
		DrawPreLogic();
		if (ImGui::BeginChild(GetID().c_str(), WidgetSize, border, ChildFlag))
		{
			HWidgetDragSpace(Content);
			//if (!Content)
			//{
			//	ImGui::Text("DragSpace");
			//	Content = HWidgetDragSpace();
			//}
			//else
			//{
			//	Content->Draw();
			//}
		}
		ImGui::EndChild();
		DrawLogicTick();
		return;
	}
	virtual void DetailPanelWidget()override
	{
		//char Save[200] = {};
		//strncpy(Save, Text.c_str(), sizeof(Save));

		ImGui::InputText("TextData", TextData, sizeof(TextData));
		//ImGui::DragFloat2("Size", (float*)&WidgetSize);
		ImGui::ToggleButton("BD ID", &border);
		ImGui::SameLine();
		ImGui::Text("Border");

		if (ImGui::TreeNode("Flags"))
		{
			ImGui::CheckboxFlags("ImGuiWindowFlags_None                     ", &ChildFlag, ImGuiWindowFlags_None);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoTitleBar               ", &ChildFlag, ImGuiWindowFlags_NoTitleBar);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoResize                 ", &ChildFlag, ImGuiWindowFlags_NoResize);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoMove                   ", &ChildFlag, ImGuiWindowFlags_NoMove);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoScrollbar              ", &ChildFlag, ImGuiWindowFlags_NoScrollbar);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoScrollWithMouse        ", &ChildFlag, ImGuiWindowFlags_NoScrollWithMouse);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoCollapse               ", &ChildFlag, ImGuiWindowFlags_NoCollapse);
			ImGui::CheckboxFlags("ImGuiWindowFlags_AlwaysAutoResize         ", &ChildFlag, ImGuiWindowFlags_AlwaysAutoResize);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoBackground             ", &ChildFlag, ImGuiWindowFlags_NoBackground);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoSavedSettings          ", &ChildFlag, ImGuiWindowFlags_NoSavedSettings);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoMouseInputs            ", &ChildFlag, ImGuiWindowFlags_NoMouseInputs);
			ImGui::CheckboxFlags("ImGuiWindowFlags_MenuBar                  ", &ChildFlag, ImGuiWindowFlags_MenuBar);
			ImGui::CheckboxFlags("ImGuiWindowFlags_HorizontalScrollbar      ", &ChildFlag, ImGuiWindowFlags_HorizontalScrollbar);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoFocusOnAppearing       ", &ChildFlag, ImGuiWindowFlags_NoFocusOnAppearing);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoBringToFrontOnFocus    ", &ChildFlag, ImGuiWindowFlags_NoBringToFrontOnFocus);
			ImGui::CheckboxFlags("ImGuiWindowFlags_AlwaysVerticalScrollbar  ", &ChildFlag, ImGuiWindowFlags_AlwaysVerticalScrollbar);
			ImGui::CheckboxFlags("ImGuiWindowFlags_AlwaysHorizontalScrollbar", &ChildFlag, ImGuiWindowFlags_AlwaysHorizontalScrollbar);
			ImGui::CheckboxFlags("ImGuiWindowFlags_AlwaysUseWindowPadding   ", &ChildFlag, ImGuiWindowFlags_AlwaysUseWindowPadding);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoNavInputs              ", &ChildFlag, ImGuiWindowFlags_NoNavInputs);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoNavFocus               ", &ChildFlag, ImGuiWindowFlags_NoNavFocus);
			ImGui::CheckboxFlags("ImGuiWindowFlags_UnsavedDocument          ", &ChildFlag, ImGuiWindowFlags_UnsavedDocument);
			ImGui::CheckboxFlags("ImGuiWindowFlags_NoDocking                ", &ChildFlag, ImGuiWindowFlags_NoDocking);

			ImGui::TreePop();
		}

		return;
	}
	virtual HWidget* CreateSelfClass()override { return new Child(); }

	virtual json Copy()override {
		json J;
		PreCopy(J);
		J["Border"] = border;
		J["WidgetName"] = TextData;
		return J;
	}
	virtual void Paste(json Data)override {
		border = Data["Border"];
		PrePaste(Data);
		std::string TextS = Data["WidgetName"];
		strcpy_s(TextData, TextS.c_str());
		return;
	}
private:
	//std::string Text = "Button";
	char TextData[200] = { "Child ID" };
	bool border = false;
	ImGuiWindowFlags ChildFlag;
};
static std::string DefaultWidgetInputText = "InputText";
static std::string DefaultWidgetInputTextID = "InputText";
class InputText :public HWidget
{
public:
	InputText()
	{
		WidgetName = &DefaultWidgetInputText;
		WidgetNameID = &DefaultWidgetInputTextID;
		WidgetID = TextData;
		HArrowFlag = HArrow_SizeFlag_OnlyX;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Move;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Null;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_TurnRight;
	}

	virtual void DrawIconForControlPanel()override
	{
		char Buf[] = { "Text" };
		ImGui::InputText("###InputText aaa", Buf, 5);
		return;
	}
	virtual std::string Export(std::string Offset) override
	{
		std::string RandTextSave = GetRandText((int)this);
		std::string SaveExportText;
		//static char _HV__InputTextBuff = { _HV_ };
		SaveExportText.append("\n").append(Offset).append("static char ").append(RandTextSave).append("_InputTextBuff[260] = { \"").append(InputTextDefault).append("\" };");
		//static ImGuiInputTextFlags _HV__InputTextFlag = _HV_;
		SaveExportText.append("\n").append(Offset).append("static ImGuiInputTextFlags ").append(RandTextSave).append("_InputTextFlag = ").append(std::to_string(InputTextFlag)).append(";");
		//if(ImGui::InputText(_HV_,_HV__InputTextBuff,_HV_,))
		SaveExportText.append("\n").append(Offset).append("if(ImGui::InputText(\"").append(GetID()).append("\",").append(RandTextSave).append("_InputTextBuff,").append(std::to_string(260)).append(",").append(RandTextSave).append("_InputTextFlag))");
		//{
		SaveExportText.append("\n").append(Offset).append("{");
		//}
		SaveExportText.append("\n").append(Offset).append("}");
		return SaveExportText;
	}
	virtual void Draw()override
	{
		DrawPreLogic();
		ImGui::SetNextItemWidth(WidgetSize.x);
		ImGui::InputText(GetID().c_str(), InputTextBuff, IM_ARRAYSIZE(InputTextBuff), InputTextFlag);

		DrawLogicTick();
		return;
	}
	virtual void DetailPanelWidget()override
	{
		ImGui::InputText("InputTextLable", TextData, IM_ARRAYSIZE(TextData));
		ImGui::InputText("TextDefault", InputTextDefault, IM_ARRAYSIZE(InputTextDefault));

		if (ImGui::TreeNode("Flags"))
		{
			//ImGuiInputTextFlags_

			ImGui::CheckboxFlags("ImGuiInputTextFlags_None               ", &InputTextFlag, ImGuiInputTextFlags_None);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CharsDecimal       ", &InputTextFlag, ImGuiInputTextFlags_CharsDecimal);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CharsHexadecimal   ", &InputTextFlag, ImGuiInputTextFlags_CharsHexadecimal);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CharsUppercase     ", &InputTextFlag, ImGuiInputTextFlags_CharsUppercase);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CharsNoBlank       ", &InputTextFlag, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_AutoSelectAll      ", &InputTextFlag, ImGuiInputTextFlags_AutoSelectAll);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_EnterReturnsTrue   ", &InputTextFlag, ImGuiInputTextFlags_EnterReturnsTrue);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CallbackCompletion ", &InputTextFlag, ImGuiInputTextFlags_CallbackCompletion);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CallbackHistory    ", &InputTextFlag, ImGuiInputTextFlags_CallbackHistory);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CallbackAlways     ", &InputTextFlag, ImGuiInputTextFlags_CallbackAlways);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CallbackCharFilter ", &InputTextFlag, ImGuiInputTextFlags_CallbackCharFilter);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_AllowTabInput      ", &InputTextFlag, ImGuiInputTextFlags_AllowTabInput);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CtrlEnterForNewLine", &InputTextFlag, ImGuiInputTextFlags_CtrlEnterForNewLine);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_NoHorizontalScroll ", &InputTextFlag, ImGuiInputTextFlags_NoHorizontalScroll);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_AlwaysOverwrite    ", &InputTextFlag, ImGuiInputTextFlags_AlwaysOverwrite);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_ReadOnly           ", &InputTextFlag, ImGuiInputTextFlags_ReadOnly);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_Password           ", &InputTextFlag, ImGuiInputTextFlags_Password);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_NoUndoRedo         ", &InputTextFlag, ImGuiInputTextFlags_NoUndoRedo);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CharsScientific    ", &InputTextFlag, ImGuiInputTextFlags_CharsScientific);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CallbackResize     ", &InputTextFlag, ImGuiInputTextFlags_CallbackResize);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CallbackEdit       ", &InputTextFlag, ImGuiInputTextFlags_CallbackEdit);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_EscapeClearsAll    ", &InputTextFlag, ImGuiInputTextFlags_EscapeClearsAll);

			ImGui::TreePop();
		}

		return;
	}
	virtual HWidget* CreateSelfClass()override { return new InputText(); }

	virtual json Copy()override {
		json J;
		PreCopy(J);
		J["WidgetText"] = TextData;
		J["TextBuff"] = InputTextBuff;
		J["TextDefault"] = InputTextDefault;
		J["Falgs"] = InputTextFlag;
		return J;
	}
	virtual void Paste(json Data)override {
		PrePaste(Data);
		std::string ST = Data["WidgetText"];

		strcpy_s(TextData, 200, ST.c_str());
		ST = Data["TextBuff"];
		strcpy_s(InputTextBuff, 260, ST.c_str());
		ST = Data["TextDefault"];
		strcpy_s(InputTextDefault, 260, ST.c_str());

		InputTextFlag = Data["Falgs"];
		return;
	}
private:
	//std::string Text = "Button";
	char TextData[200] = { "Text" };
	char InputTextBuff[260];
	char InputTextDefault[260] = { "InputText" };
	ImGuiInputTextFlags InputTextFlag;
};
static std::string DefaultWidgetInputTextMultiline = "InputTextMultiline";
static std::string DefaultWidgetInputTextMultilineID = "InputTextMultiline";
class InputTextMultiline :public HWidget
{
public:
	InputTextMultiline()
	{
		WidgetName = &DefaultWidgetInputTextMultiline;
		WidgetNameID = &DefaultWidgetInputTextMultilineID;
		WidgetID = TextData;
		HArrowFlag = HArrow_SizeFlag_Default;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Move;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Null;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_TurnRight;
	}

	virtual void DrawIconForControlPanel()override
	{
		char Buf[] = { "Text" };
		ImGui::InputTextMultiline("###InputTextMultiline aaa", Buf, 5, ImVec2(0, 40));
		return;
	}
	virtual std::string Export(std::string Offset) override
	{
		std::string RandTextSave = GetRandText((int)this);
		std::string SaveExportText;
		//static char _HV__InputTextBuff = { _HV_ };
		SaveExportText.append("\n").append(Offset).append("static char ").append(RandTextSave).append("_InputTextMultilineBuff[260] = { \"").append(InputTextDefault).append("\" };");
		//static ImGuiInputTextFlags _HV__InputTextFlag = _HV_;
		SaveExportText.append("\n").append(Offset).append("static ImGuiInputTextFlags ").append(RandTextSave).append("_InputTextFlag = ").append(std::to_string(InputTextFlag)).append(";");
		//if(ImGui::InputText(_HV_,_HV__InputTextBuff,_HV_,))
		SaveExportText.append("\n").append(Offset).append("if(ImGui::InputTextMultiline(\"").append(GetID()).append("\",").append(RandTextSave).append("_InputTextBuff,").append(std::to_string(260)).append(",").append("ImVec2(").append(std::to_string(WidgetSize.x)).append(",").append(std::to_string(WidgetSize.y)).append(")").append(",").append(RandTextSave).append("_InputTextFlag))");
		//{
		SaveExportText.append("\n").append(Offset).append("{");
		//}
		SaveExportText.append("\n").append(Offset).append("}");
		return SaveExportText;
	}
	virtual void Draw()override
	{
		DrawPreLogic();
		//ImGui::SetNextItemWidth(WidgetSize.x);
		ImGui::InputTextMultiline(GetID().c_str(), InputTextBuff, IM_ARRAYSIZE(InputTextBuff), WidgetSize, InputTextFlag);

		DrawLogicTick();
		return;
	}
	virtual void DetailPanelWidget()override
	{
		ImGui::InputText("InputTextLable", TextData, IM_ARRAYSIZE(TextData));
		ImGui::InputTextMultiline("TextDefault", InputTextDefault, IM_ARRAYSIZE(InputTextDefault));

		if (ImGui::TreeNode("Flags"))
		{
			//ImGuiInputTextFlags_

			ImGui::CheckboxFlags("ImGuiInputTextFlags_None               ", &InputTextFlag, ImGuiInputTextFlags_None);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CharsDecimal       ", &InputTextFlag, ImGuiInputTextFlags_CharsDecimal);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CharsHexadecimal   ", &InputTextFlag, ImGuiInputTextFlags_CharsHexadecimal);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CharsUppercase     ", &InputTextFlag, ImGuiInputTextFlags_CharsUppercase);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CharsNoBlank       ", &InputTextFlag, ImGuiInputTextFlags_CharsNoBlank);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_AutoSelectAll      ", &InputTextFlag, ImGuiInputTextFlags_AutoSelectAll);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_EnterReturnsTrue   ", &InputTextFlag, ImGuiInputTextFlags_EnterReturnsTrue);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CallbackCompletion ", &InputTextFlag, ImGuiInputTextFlags_CallbackCompletion);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CallbackHistory    ", &InputTextFlag, ImGuiInputTextFlags_CallbackHistory);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CallbackAlways     ", &InputTextFlag, ImGuiInputTextFlags_CallbackAlways);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CallbackCharFilter ", &InputTextFlag, ImGuiInputTextFlags_CallbackCharFilter);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_AllowTabInput      ", &InputTextFlag, ImGuiInputTextFlags_AllowTabInput);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CtrlEnterForNewLine", &InputTextFlag, ImGuiInputTextFlags_CtrlEnterForNewLine);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_NoHorizontalScroll ", &InputTextFlag, ImGuiInputTextFlags_NoHorizontalScroll);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_AlwaysOverwrite    ", &InputTextFlag, ImGuiInputTextFlags_AlwaysOverwrite);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_ReadOnly           ", &InputTextFlag, ImGuiInputTextFlags_ReadOnly);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_Password           ", &InputTextFlag, ImGuiInputTextFlags_Password);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_NoUndoRedo         ", &InputTextFlag, ImGuiInputTextFlags_NoUndoRedo);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CharsScientific    ", &InputTextFlag, ImGuiInputTextFlags_CharsScientific);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CallbackResize     ", &InputTextFlag, ImGuiInputTextFlags_CallbackResize);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_CallbackEdit       ", &InputTextFlag, ImGuiInputTextFlags_CallbackEdit);
			ImGui::CheckboxFlags("ImGuiInputTextFlags_EscapeClearsAll    ", &InputTextFlag, ImGuiInputTextFlags_EscapeClearsAll);

			ImGui::TreePop();
		}

		return;
	}
	virtual HWidget* CreateSelfClass()override { return new InputTextMultiline(); }

	virtual json Copy()override {
		json J;
		PreCopy(J);
		J["WidgetText"] = TextData;
		J["TextBuff"] = InputTextBuff;
		J["TextDefault"] = InputTextDefault;
		J["Falgs"] = InputTextFlag;
		return J;
	}
	virtual void Paste(json Data)override {
		PrePaste(Data);
		std::string ST = Data["WidgetText"];

		strcpy_s(TextData, 200, ST.c_str());
		ST = Data["TextBuff"];
		strcpy_s(InputTextBuff, 260, ST.c_str());
		ST = Data["TextDefault"];
		strcpy_s(InputTextDefault, 260, ST.c_str());

		InputTextFlag = Data["Falgs"];
		return;
	}
private:
	//std::string Text = "Button";
	char TextData[200] = { "Text" };
	char InputTextBuff[260];
	char InputTextDefault[260] = { "InputText" };
	ImGuiInputTextFlags InputTextFlag;
};
static std::string DefaultWidgetDragFloat = "DragFloat";
static std::string DefaultWidgetDragFloatID = "DragFloat";
class DragFloat :public HWidget
{
public:
	DragFloat()
	{
		WidgetName = &DefaultWidgetDragFloat;
		WidgetNameID = &DefaultWidgetDragFloatID;
		WidgetID = TextData;
		HArrowFlag = HArrow_SizeFlag_OnlyX;
	}

	virtual void DrawIconForControlPanel()override
	{
		float F = 1.95;
		ImGui::DragFloat("Text", &F);
		return;
	}
	virtual std::string Export(std::string Offset) override
	{
		std::string RandText = GetRandText((int)this);
		std::string SaveExportText;
		//static float DragFloat__HV_ = _THV_;
		SaveExportText.append("\n").append(Offset).append("static float DragFloat_").append(RandText).append(" = ").append(std::to_string(0)).append(";");
		//if(DragFloat(_HV_,DragFloat__HV_ ,_THV_,_THV_,_THV_,_HV_,_THV_))
		SaveExportText.append("\n").append(Offset).append("if(DragFloat(").append(TextData).append(",&DragFloat_").append(RandText).append(" ,").append(std::to_string(Speed)).append(",").append(std::to_string(Mmin)).append(",").append(std::to_string(Mmax)).append(",\"").append(Mformat).append("\",").append(std::to_string(Mflage)).append("))");
		//{
		SaveExportText.append("\n").append(Offset).append("{");
		//}
		SaveExportText.append("\n").append(Offset).append("}");
		return SaveExportText;
	}
	virtual void Draw()override
	{
		DrawPreLogic();
		ImGui::SetNextItemWidth(WidgetSize.x);
		ImGui::DragFloat(GetID().c_str(), &DragBuff, Speed, Mmin, Mmax, Mformat, Mflage);
		DrawLogicTick();
		return;
	}
	virtual void DetailPanelWidget()override
	{
		//char Save[200] = {};
		//strncpy(Save, Text.c_str(), sizeof(Save));

		ImGui::InputText("TextData", TextData, sizeof(TextData));
		ImGui::DragFloat("Speed", &Speed, 0.1, 0.01, 100000);
		ImGui::DragFloat("min", &Mmin, 0.1, 0, 100000);
		ImGui::DragFloat("max", &Mmax, 0.1, 0, 100000);
		ImGui::InputText("format", Mformat, sizeof(Mformat));

		if (ImGui::TreeNode("Flags"))
		{
			ImGui::CheckboxFlags("ImGuiSliderFlags_None           ", &Mflage, ImGuiSliderFlags_None);
			ImGui::CheckboxFlags("ImGuiSliderFlags_AlwaysClamp    ", &Mflage, ImGuiSliderFlags_AlwaysClamp);
			ImGui::CheckboxFlags("ImGuiSliderFlags_Logarithmic    ", &Mflage, ImGuiSliderFlags_Logarithmic);
			ImGui::CheckboxFlags("ImGuiSliderFlags_NoRoundToFormat", &Mflage, ImGuiSliderFlags_NoRoundToFormat);
			ImGui::CheckboxFlags("ImGuiSliderFlags_NoInput        ", &Mflage, ImGuiSliderFlags_NoInput);
			ImGui::CheckboxFlags("ImGuiSliderFlags_InvalidMask_   ", &Mflage, ImGuiSliderFlags_InvalidMask_);
			ImGui::TreePop();
		}

		return;
	}
	virtual HWidget* CreateSelfClass()override { return new DragFloat(); }

	virtual json Copy()override {
		json J;
		PreCopy(J);
		J["WidgetText"] = TextData;
		J["Buff"] = DragBuff;
		J["MSpeed"] = Speed;
		J["SMin"] = Mmin;
		J["SMax"] = Mmax;
		J["Format"] = Mformat;
		J["Flage"] = Mflage;
		return J;
	}
	virtual void Paste(json Data)override {
		PrePaste(Data);
		std::string ST = Data["WidgetText"];
		strcpy_s(TextData, 200, ST.c_str());

		DragBuff = Data["Buff"];
		Speed = Data["MSpeed"];
		Mmin = Data["SMin"];
		Mmax = Data["SMax"];
		ST = Data["Format"];
		strcpy_s(Mformat, ST.c_str());

		Mflage = Data["Flage"];

		return;
	}
private:
	//std::string Text = "Button";
	char TextData[200] = { "Text" };
	float DragBuff;
	float Speed = 1;
	float Mmin = 0;
	float Mmax = 1;
	char Mformat[200] = { "% .3f" };
	ImGuiSliderFlags Mflage;
};
static std::string DefaultWidgetColorEdit = "ColorEdit";
static std::string DefaultWidgetColorEditID = "ColorEdit";
class ColorEdit :public HWidget
{
public:
	ColorEdit()
	{
		HArrowFlag = HArrow_SizeFlag::HArrow_SizeFlag_OnlyX;
		WidgetName = &DefaultWidgetColorEdit;
		WidgetNameID = &DefaultWidgetColorEditID;
		WidgetID = Text;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Move;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Null;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_TurnRight;
	}

	virtual void DrawIconForControlPanel()override
	{
		static ImVec4 Color;
		ImGui::ColorEdit3("ColorEdit", (float*)&Color);
		//ImGui::Button("Button");
		return;
	}
	virtual std::string Export(std::string Offset) override
	{
		std::string RandText = GetRandText((int)this);
		std::string SaveExportText;
		//static ImVec4 ColorEditor3__HV_ = ImVec4(_THV_,_THV_,_THV_,_THV_);
		SaveExportText.append("\n").append(Offset).append("static ImVec4 ColorEditor3_").append(RandText).append(" = ImVec4(").append(std::to_string(DFColor.x)).append(",").append(std::to_string(DFColor.y)).append(",").append(std::to_string(DFColor.z)).append(",").append(std::to_string(DFColor.w)).append(");");
		//if(ColorEdit3(_HV_,(float*)&ColorEditor3__HV_  ,_THV_))
		SaveExportText.append("\n").append(Offset).append("if(ColorEdit3(\"").append(GetID()).append("\",(float*)&ColorEditor3_").append(RandText).append("  ,").append(std::to_string(Cflags)).append("))");
		//{
		SaveExportText.append("\n").append(Offset).append("{");
		//}
		SaveExportText.append("\n").append(Offset).append("}");
		return SaveExportText;
	}
	virtual void Draw()override
	{
		DrawPreLogic();
		ImGui::ColorEdit3(GetID().c_str(), (float*)&XColor, Cflags);
		DrawLogicTick();
		return;
	}
	virtual void DetailPanelWidget()override
	{
		ImGui::InputText("Button Text", Text, 200);
		ImGui::ColorEdit3("DFColor", (float*)&DFColor);

		if (ImGui::TreeNode("Flags"))
		{
			ImGui::CheckboxFlags("ImGuiColorEditFlags_None           ", &Cflags, ImGuiColorEditFlags_None);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoAlpha        ", &Cflags, ImGuiColorEditFlags_NoAlpha);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoPicker       ", &Cflags, ImGuiColorEditFlags_NoPicker);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoOptions      ", &Cflags, ImGuiColorEditFlags_NoOptions);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoSmallPreview ", &Cflags, ImGuiColorEditFlags_NoSmallPreview);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoInputs       ", &Cflags, ImGuiColorEditFlags_NoInputs);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoTooltip      ", &Cflags, ImGuiColorEditFlags_NoTooltip);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoLabel        ", &Cflags, ImGuiColorEditFlags_NoLabel);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoSidePreview  ", &Cflags, ImGuiColorEditFlags_NoSidePreview);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoDragDrop     ", &Cflags, ImGuiColorEditFlags_NoDragDrop);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoBorder       ", &Cflags, ImGuiColorEditFlags_NoBorder);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_AlphaBar        ", &Cflags, ImGuiColorEditFlags_AlphaBar);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_AlphaPreview    ", &Cflags, ImGuiColorEditFlags_AlphaPreview);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_AlphaPreviewHalf", &Cflags, ImGuiColorEditFlags_AlphaPreviewHalf);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_HDR             ", &Cflags, ImGuiColorEditFlags_HDR);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_DisplayRGB      ", &Cflags, ImGuiColorEditFlags_DisplayRGB);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_DisplayHSV      ", &Cflags, ImGuiColorEditFlags_DisplayHSV);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_DisplayHex      ", &Cflags, ImGuiColorEditFlags_DisplayHex);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_Uint8           ", &Cflags, ImGuiColorEditFlags_Uint8);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_Float           ", &Cflags, ImGuiColorEditFlags_Float);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_PickerHueBar    ", &Cflags, ImGuiColorEditFlags_PickerHueBar);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_PickerHueWheel  ", &Cflags, ImGuiColorEditFlags_PickerHueWheel);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_InputRGB        ", &Cflags, ImGuiColorEditFlags_InputRGB);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_InputHSV        ", &Cflags, ImGuiColorEditFlags_InputHSV);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_DefaultOptions_", &Cflags, ImGuiColorEditFlags_DefaultOptions_);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_DisplayMask_ ", &Cflags, ImGuiColorEditFlags_DisplayMask_);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_DataTypeMask_", &Cflags, ImGuiColorEditFlags_DataTypeMask_);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_PickerMask_  ", &Cflags, ImGuiColorEditFlags_PickerMask_);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_InputMask_   ", &Cflags, ImGuiColorEditFlags_InputMask_);
			ImGui::TreePop();
		}
		return;
	}
	virtual HWidget* CreateSelfClass()override {
		return new ColorEdit();
	}

	virtual json Copy()override {
		json J;
		PreCopy(J);
		J["WidgetName"] = Text;
		json color;
		color["r"] = XColor.x;
		color["g"] = XColor.y;
		color["b"] = XColor.z;
		color["a"] = XColor.w;
		J["Color"] = color;

		color["r"] = DFColor.x;
		color["g"] = DFColor.y;
		color["b"] = DFColor.z;
		color["a"] = DFColor.w;
		J["DFColor"] = color;

		J["flags"] = Cflags;
		return J;
	}
	virtual void Paste(json Data)override {
		PrePaste(Data);

		std::string Name = Data["WidgetName"];
		strcpy_s(Text, Name.c_str());
		json color = Data["Color"];
		XColor.x = color["r"];
		XColor.y = color["g"];
		XColor.z = color["b"];
		XColor.w = color["a"];

		color = Data["DFColor"];
		DFColor.x = color["r"];
		DFColor.y = color["g"];
		DFColor.z = color["b"];
		DFColor.w = color["a"];

		Cflags = Data["flags"];

		//ImGuiColorEditFlags_
		return;
	}

private:
	//std::string Text = "Button";
	char Text[200] = { "Button" };
	ImGuiColorEditFlags Cflags;
	ImVec4 XColor;
	ImVec4 DFColor;
	//ImVec2 Size = ImVec2(0, 0);
};
static std::string DefaultWidgetColorButton = "ColorButton";
static std::string DefaultWidgetColorButtonID = "ColorButton";
class ColorButton :public HWidget
{
public:
	ColorButton()
	{
		WidgetName = &DefaultWidgetColorButton;
		WidgetNameID = &DefaultWidgetColorButtonID;
		WidgetID = Text;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Move;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_Null;
		//AvailableFlags |= HWidgetFlag::HWidgetFlag_TurnRight;
	}

	virtual void DrawIconForControlPanel()override
	{
		static ImVec4 Color;
		ImGui::ColorButton("ColorButton", Color);
		//ImGui::Button("Button");
		return;
	}
	virtual std::string Export(std::string Offset) override
	{
		std::string RandText = GetRandText((int)this);
		std::string SaveExportText;
		//static ImVec4 ColorEditor3__HV_ = ImVec4(_THV_,_THV_,_THV_,_THV_);
		//if(ColorEdit3(_HV_,(float*)&ColorEditor3__HV_  ,_THV_))
		SaveExportText.append("\n").append(Offset).append("if(ColorButton(\"").append(Text).append("###").append(GetID()).append("\",ImVec4(").append(std::to_string(DFColor.x)).append(",").append(std::to_string(DFColor.y)).append(",").append(std::to_string(DFColor.z)).append(",").append(std::to_string(DFColor.w)).append(")").append("  ,").append(std::to_string(Cflags)).append("))");
		//{
		SaveExportText.append("\n").append(Offset).append("{");
		//}
		SaveExportText.append("\n").append(Offset).append("}");
		return SaveExportText;
	}
	virtual void Draw()override
	{
		DrawPreLogic();
		ImGui::ColorButton(std::string(Text).append("###").append(WidgetID).c_str(), DFColor, Cflags, WidgetSize);
		DrawLogicTick();
		return;
	}
	virtual void DetailPanelWidget()override
	{
		ImGui::InputText("Button Text", Text, 200);
		ImGui::ColorEdit3("DFColor", (float*)&DFColor);

		if (ImGui::TreeNode("Flags"))
		{
			ImGui::CheckboxFlags("ImGuiColorEditFlags_None           ", &Cflags, ImGuiColorEditFlags_None);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoAlpha        ", &Cflags, ImGuiColorEditFlags_NoAlpha);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoPicker       ", &Cflags, ImGuiColorEditFlags_NoPicker);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoOptions      ", &Cflags, ImGuiColorEditFlags_NoOptions);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoSmallPreview ", &Cflags, ImGuiColorEditFlags_NoSmallPreview);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoInputs       ", &Cflags, ImGuiColorEditFlags_NoInputs);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoTooltip      ", &Cflags, ImGuiColorEditFlags_NoTooltip);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoLabel        ", &Cflags, ImGuiColorEditFlags_NoLabel);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoSidePreview  ", &Cflags, ImGuiColorEditFlags_NoSidePreview);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoDragDrop     ", &Cflags, ImGuiColorEditFlags_NoDragDrop);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_NoBorder       ", &Cflags, ImGuiColorEditFlags_NoBorder);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_AlphaBar        ", &Cflags, ImGuiColorEditFlags_AlphaBar);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_AlphaPreview    ", &Cflags, ImGuiColorEditFlags_AlphaPreview);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_AlphaPreviewHalf", &Cflags, ImGuiColorEditFlags_AlphaPreviewHalf);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_HDR             ", &Cflags, ImGuiColorEditFlags_HDR);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_DisplayRGB      ", &Cflags, ImGuiColorEditFlags_DisplayRGB);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_DisplayHSV      ", &Cflags, ImGuiColorEditFlags_DisplayHSV);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_DisplayHex      ", &Cflags, ImGuiColorEditFlags_DisplayHex);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_Uint8           ", &Cflags, ImGuiColorEditFlags_Uint8);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_Float           ", &Cflags, ImGuiColorEditFlags_Float);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_PickerHueBar    ", &Cflags, ImGuiColorEditFlags_PickerHueBar);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_PickerHueWheel  ", &Cflags, ImGuiColorEditFlags_PickerHueWheel);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_InputRGB        ", &Cflags, ImGuiColorEditFlags_InputRGB);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_InputHSV        ", &Cflags, ImGuiColorEditFlags_InputHSV);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_DefaultOptions_", &Cflags, ImGuiColorEditFlags_DefaultOptions_);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_DisplayMask_ ", &Cflags, ImGuiColorEditFlags_DisplayMask_);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_DataTypeMask_", &Cflags, ImGuiColorEditFlags_DataTypeMask_);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_PickerMask_  ", &Cflags, ImGuiColorEditFlags_PickerMask_);
			ImGui::CheckboxFlags("ImGuiColorEditFlags_InputMask_   ", &Cflags, ImGuiColorEditFlags_InputMask_);
			ImGui::TreePop();
		}
		return;
	}
	virtual HWidget* CreateSelfClass()override {
		return new ColorButton();
	}

	virtual json Copy()override {
		json J;
		PreCopy(J);
		J["WidgetName"] = Text;
		json color;

		color["r"] = DFColor.x;
		color["g"] = DFColor.y;
		color["b"] = DFColor.z;
		color["a"] = DFColor.w;
		J["DFColor"] = color;

		J["flags"] = Cflags;
		return J;
	}
	virtual void Paste(json Data)override {
		PrePaste(Data);

		std::string Name = Data["WidgetName"];
		strcpy_s(Text, Name.c_str());
		json color;

		color = Data["DFColor"];
		DFColor.x = color["r"];
		DFColor.y = color["g"];
		DFColor.z = color["b"];
		DFColor.w = color["a"];

		Cflags = Data["flags"];

		//ImGuiColorEditFlags_
		return;
	}

private:
	//std::string Text = "Button";
	char Text[200] = { "Button" };
	ImGuiColorEditFlags Cflags;
	ImVec4 DFColor;
	//ImVec2 Size = ImVec2(0, 0);
};
//static ImVec4 Color;
//ImGui::ColorEdit3("ColorEdit", (float*)&Color);