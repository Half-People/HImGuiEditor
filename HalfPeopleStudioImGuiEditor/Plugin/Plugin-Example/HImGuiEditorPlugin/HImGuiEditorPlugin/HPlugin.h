#pragma once
#include "HWidget.h"
#include "ImGuiTextEdit/ImGuiColorTextEdit-master/TextEditor.h"

namespace ToggleButtonV
{
	static std::string DefaultWidgetToggleButton = "ToggleButton";
	static std::string DefaultWidgetToggleButtonID = "ToggleButton";
	static std::vector<std::string> HInculd = { "#include <imgui_internal.h>" ,"#include <imgui.h>" };
	//static std::string ThirdPartyLibraryPartialPath;
	static std::string HFunction =
		"\nnamespace ImGui"
		"\n{"
		"\n	static bool ToggleButton(const char* str_id, bool* v, float ANIM_SPEED = 0.08f)"
		"\n	{"
		"\n		bool Updata = false;"
		"\n		ImVec2 p = ImGui::GetCursorScreenPos();"
		"\n		ImDrawList* draw_list = ImGui::GetWindowDrawList();"
		"\n		"
		"\n		float height = ImGui::GetFrameHeight();	"
		"\n		float width = height * 1.55f;"
		"\n		float radius = height * 0.50f;"
		"\n		"
		"\n		ImGui::InvisibleButton(str_id, ImVec2(width, height));"
		"\n		if (ImGui::IsItemClicked())"
		"\n		{"
		"\n			*v = !*v;"
		"\n			Updata = true;"
		"\n		}"
		"\n		"
		"\n		float t = *v ? 1.0f : 0.0f;"
		"\n		"
		"\n		ImGuiContext& g = *GImGui;"
		"\n		"
		"\n		if (g.LastActiveId == g.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)"
		"\n		{"
		"\n			float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);"
		"\n			t = *v ? (t_anim) : (1.0f - t_anim);"
		"\n		}"
		"\n		"
		"\n		ImU32 col_bg;"
		"\n		if (ImGui::IsItemHovered())"
		"\n			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 1.0f), ImVec4(0.64f, 0.83f, 0.34f, 1.0f), t));"
		"\n		else"
		"\n			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), ImVec4(0.56f, 0.83f, 0.26f, 1.0f), t));"
		"\n		"
		"\n		draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);"
		"\n		draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));"
		"\n		return Updata;"
		"\n	}"
		"\n}\0";
}

bool DemoToggleButton(const char* str_id, bool* v, float ANIM_SPEED = 0.08f)
{
	bool Updata = false;
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	float height = ImGui::GetFrameHeight();
	float width = height * 1.55f;
	float radius = height * 0.50f;

	ImGui::InvisibleButton(str_id, ImVec2(width, height));
	if (ImGui::IsItemClicked())
	{
		*v = !*v;
		Updata = true;
	}

	float t = *v ? 1.0f : 0.0f;

	ImGuiContext& g = *GImGui;

	if (g.LastActiveId == g.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
	{
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = *v ? (t_anim) : (1.0f - t_anim);
	}

	ImU32 col_bg;
	if (ImGui::IsItemHovered())
		col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 1.0f), ImVec4(0.64f, 0.83f, 0.34f, 1.0f), t));
	else
		col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), ImVec4(0.56f, 0.83f, 0.26f, 1.0f), t));

	draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
	draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
	return Updata;
}

class ToggleButton :public HWidget
{
public:
	ToggleButton()
	{
		WidgetName = &ToggleButtonV::DefaultWidgetToggleButton;
		WidgetNameID = &ToggleButtonV::DefaultWidgetToggleButtonID;
		HArrowFlag = HArrow_SizeFlag_NotResize;
		this->Function = &ToggleButtonV::HFunction;
		Inculd = &ToggleButtonV::HInculd;
		strcpy_s(ToggleButtonID, GetRandText((int)this).c_str());
		WidgetID = ToggleButtonID;
	}

	virtual void DrawIconForControlPanel()override
	{
		DemoToggleButton(std::to_string((int)this).c_str(), &Save);
		return;
	}
	virtual std::string Export(std::string Offset) override
	{
		std::string RT;
		RT = Offset;
		RT.append("static bool ").append(GetRandText((int)this)).append(" = ").append(BoolToString(DefaultState)).append(";");
		RT.append("\n").append(Offset);
		RT.append("if(ImGui::ToggleButton(\"").append(GetID()).append("\" , &").append(GetRandText((int)this)).append(" , ").append(std::to_string(AnimationSpeed)).append("))");
		RT.append("\n").append(Offset).append("{");
		RT.append("\n").append(Offset);
		RT.append("\n").append(Offset);
		RT.append("\n").append(Offset).append("}");

		return RT;
	}
	virtual void Draw()override
	{
		DrawPreLogic();

		DemoToggleButton(GetID().c_str(), &Save, AnimationSpeed);

		DrawLogicTick();
		return;
	}
	virtual void DetailPanelWidget()override
	{
		ImGui::InputText("ToggleButtonID", ToggleButtonID, 200);
		ImGui::DragFloat("AnimationSpeed", &AnimationSpeed, 0.01, 0, 1);
		ImGui::Text("DefaultState : ");
		ImGui::SameLine();
		DemoToggleButton("ajkwdhauwd", &DefaultState);

		return;
	}
	virtual HWidget* CreateSelfClass()override { return new ToggleButton(); }

	virtual json Copy()override {
		json J;
		PreCopy(J);
		J["WidgetName"] = ToggleButtonID;
		J["AnimationSpeed"] = AnimationSpeed;
		J["DefaultState"] = DefaultState;
		J["Save"] = Save;
		return J;
	}
	virtual void Paste(json Data)override {
		PrePaste(Data);
		std::string TrreNameS = Data["WidgetName"];

		AnimationSpeed = Data["AnimationSpeed"];
		DefaultState = Data["DefaultState"];
		Save = Data["Save"];

		strcpy_s(ToggleButtonID, TrreNameS.c_str());
		return;
	}

private:
	float AnimationSpeed = 0.08;
	char ToggleButtonID[200];// = { "ToggleButton ID" };
	bool Save = false;
	bool DefaultState = false;
};

namespace TextEditorV
{
	static std::string DefaultWidgetTextEditor = "ImGui Color TextEdit";
	static std::string DefaultWidgetTextEditorID = "ImGui Color TextEdit";
	static std::vector<std::string> HInculd = { "#include <TextEditor.h>" ,"#include <imgui.h>" };
	static std::vector<std::string> HRequestCompileFile = { "Content\\ImGuiColorTextEdit-master\\TextEditor.h","Content\\ImGuiColorTextEdit-master\\TextEditor.cpp" };
	static std::string HInculdPath = "Content\\ImGuiColorTextEdit-master";
	static std::vector<std::string> LanguageDefinitionList = { "CPlusPlus",
																"HLSL",
																"GLSL",
																"C",
																"SQL",
																"AngelScript",
																"Lua"
	};
}

class HTextEditor :public HWidget
{
public:
	HTextEditor()
	{
		WidgetName = &TextEditorV::DefaultWidgetTextEditor;
		WidgetNameID = &TextEditorV::DefaultWidgetTextEditorID;

		HArrowFlag = HArrow_SizeFlag_Default;
		InculdPath = &TextEditorV::HInculdPath;
		this->RequestCompileFile = &TextEditorV::HRequestCompileFile;
		Inculd = &TextEditorV::HInculd;
		Ed = new TextEditor();
		Ed->SetText("#include <iostream>\n\nint main()\n{\n\n	std::cout << \"\\n Hello World\" ;\n\n}");

		TextEditorTitleID = new HVString("TextEditorTitleID", "TextEditor", 0, true, false);
		Border = new HVBool("Border");

		HValues.AddHValue(TextEditorTitleID);
		HValues.AddHValue(Border);

		WidgetID = TextEditorTitleID->Get().data();
	}
	~HTextEditor()
	{
		Ed->~TextEditor();
	}

	virtual void DrawIconForControlPanel()override
	{
		//DemoToggleButton(std::to_string((int)this).c_str(), &Save);
		Ed->Render(std::to_string((int)this).c_str(), ImVec2(0, 80), true);
		return;
	}
	virtual std::string Export(std::string Offset) override
	{
		std::string SaveExportText;
		std::string SaveRandText = GetRandText((int)this);
		//static TextEditor* _HV_;
		HVariableExport HV;
		HV.VariableCode.append("\n").append(Offset).append("static TextEditor* ").append(SaveRandText).append("_TEdit;");
		HV.Comment = "HPlugin - TextEditor";
		EVariable->push_back(HV);

		SaveExportText.append("\n// Init TextEditor");
		SaveExportText.append("\n").append(SaveRandText).append("_TEdit = new TextEditor;");
		SaveExportText.append("\n").append(SaveRandText).append("_TEdit->SetShowWhitespaces(").append(BoolToString(ShowWhitespaces)).append(");");
		SaveExportText.append("\n").append(SaveRandText).append("_TEdit->SetLanguageDefinition(").append(LanguageDefinitionListToString(LanguageDefinitionListIndex)).append(");\n");

		InitializationCodes->push_back(SaveExportText); // << Add to InitializationFunction

		SaveExportText.clear();

		SaveExportText.append("\n").append(Offset).append("").append(SaveRandText).append("_TEdit->Render(\"").append(GetID()).append("\",ImVec2(").append(std::to_string(WidgetSize->Get()->x)).append(",").append(std::to_string(WidgetSize->Get()->y)).append("),").append(BoolToString(Border)).append(");");
		return SaveExportText;
	}
	virtual void Draw()override
	{
		DrawPreLogic();

		Ed->Render(TextEditorTitleID->Get().c_str(), *WidgetSize->Get(), *Border->Get());

		DrawLogicTick();
		return;
	}
	virtual void DetailPanelWidget()override
	{
		Border->Draw("Border", this);
		TextEditorTitleID->Draw("TextEditorTitle ID", this);
		//ImGui::Checkbox("Border", Border->Get());
		if (ImGui::Checkbox("ShowWhitespaces", &ShowWhitespaces))
			Ed->SetShowWhitespaces(ShowWhitespaces);
		if (ImGui::BeginCombo("LanguageDefinition", TextEditorV::LanguageDefinitionList.at(LanguageDefinitionListIndex).c_str()))
		{
			for (size_t i = 0; i < TextEditorV::LanguageDefinitionList.size(); i++)
			{
				if (ImGui::Selectable(TextEditorV::LanguageDefinitionList.at(i).c_str(), i == LanguageDefinitionListIndex))
				{
					LanguageDefinitionListIndex = i;
					Ed->SetLanguageDefinition(LanguageDefinitionListToFunction(i));
				}
			}

			ImGui::EndCombo();
		}

		//Ed->SetLanguageDefinition(TextEditor::LanguageDefinition::AngelScript());
		return;
	}
	virtual HWidget* CreateSelfClass()override { return new HTextEditor(); }

	virtual json Copy()override {
		json J;
		PreCopy(J);
		J["ShowWhitespaces"] = ShowWhitespaces;
		J["LanguageDefinitionListIndex"] = LanguageDefinitionListIndex;
		return J;
	}
	virtual void Paste(json Data)override {
		PrePaste(Data);
		ShowWhitespaces = Data["ShowWhitespaces"];
		LanguageDefinitionListIndex = Data["LanguageDefinitionListIndex"];
		Ed->SetLanguageDefinition(LanguageDefinitionListToFunction(LanguageDefinitionListIndex));

		return;
	}

private:
	TextEditor::LanguageDefinition LanguageDefinitionListToFunction(int INDEX)
	{
		switch (INDEX)
		{
		case 0:
			return TextEditor::LanguageDefinition::CPlusPlus();
			break;
		case 1:
			return TextEditor::LanguageDefinition::HLSL();
			break;
		case 2:
			return TextEditor::LanguageDefinition::GLSL();
			break;
		case 3:
			return TextEditor::LanguageDefinition::C();
			break;
		case 4:
			return TextEditor::LanguageDefinition::SQL();
			break;
		case 5:
			return TextEditor::LanguageDefinition::AngelScript();
			break;
		case 6:
			return TextEditor::LanguageDefinition::Lua();
			break;
		default:
			break;
		}
	}
	std::string LanguageDefinitionListToString(int INDEX)
	{
		switch (INDEX)
		{
		case 0:
			return "TextEditor::LanguageDefinition::CPlusPlus()";
			break;
		case 1:
			return "TextEditor::LanguageDefinition::HLSL()";
			break;
		case 2:
			return "TextEditor::LanguageDefinition::GLSL()";
			break;
		case 3:
			return "TextEditor::LanguageDefinition::C()";
			break;
		case 4:
			return "TextEditor::LanguageDefinition::SQL()";
			break;
		case 5:
			return "TextEditor::LanguageDefinition::AngelScript()";
			break;
		case 6:
			return "TextEditor::LanguageDefinition::Lua()";
			break;
		default:
			break;
		}
	}

	//char TextEditorTitleID[200];// = { "ToggleButton ID" };
	//bool Border;
	//bool ShowWhitespaces;

	HVString* TextEditorTitleID;
	HVBool* Border;
	bool ShowWhitespaces;
	int LanguageDefinitionListIndex = 0;
	TextEditor* Ed;
};

extern "C" __declspec(dllexport)std::vector< HWidget*> GetWidget()
{
	return { new ToggleButton ,new HTextEditor };
}

extern "C" __declspec(dllexport) json GetPluginInfo()
{
	json Info;
	Info["PluginName"] = "ToggleButton";//mandatory
	Info["Info"] = "";//mandatory
	Info["API_Folder"] = "Content";//Optional
	return Info;
}