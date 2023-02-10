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