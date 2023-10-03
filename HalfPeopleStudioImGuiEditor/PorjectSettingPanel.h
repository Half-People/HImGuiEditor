#pragma once
#include "HTranslate.h"
#include "HImGuiWidgetItem.h"
#include "MainMenuBarVar.h"
#include "SettingPanel.h"
#include "HWindows.h"
#include "Porject.h"

//#include "HFileBrowser.h"

namespace PorjectSettingTranslateList
{
	std::string PorjectSetting = "project settings";
	std::string MainWindow = "MainWindow";
}

static void LoadFont(json J, HFont& font)
{
	try
	{
		font.font = J["FontData"].get<std::vector<unsigned int>>();
		font.Fontfile_size = J["FontFileSize"];
		font.font_size = J["FontSize"];
		font.ApplayFont();
	}
	catch (const json::exception& e)
	{
		std::cout << "\nPorjectSettingPanel -> LoadFont ->Json->Error -> ErrorMessage : " << e.what();
	}
}

static json HFontToJson(HFont& font)
{
	json J;
	J["FontData"] = font.font;
	J["FontSize"] = font.font_size;
	J["FontFileSize"] = font.Fontfile_size;
	return J;
}

static void InitPorjectSetting() {
	TranslateObject.push_back(&PorjectSettingTranslateList::PorjectSetting);
	TranslateObject.push_back(&PorjectSettingTranslateList::MainWindow);
}

static json SavePorjectSetting()
{
	json PorjectSettingSave;

	json Style;
	ImGuiStyle& style = GUIStyle;
	ImVec4* colors = style.Colors;

	json Color, Colors, Sizes;

	for (size_t i = 0; i < 55; i++)
	{
		Color["R"] = colors[i].x;
		Color["G"] = colors[i].y;
		Color["B"] = colors[i].z;
		Color["A"] = colors[i].w;
		Colors[ImGui::GetStyleColorName(i)] = Color;
	}

	Sizes["WindowPadding"] = PreferencesFun::ImVec2ToJson(style.WindowPadding);
	Sizes["WindowRounding"] = style.WindowRounding;
	Sizes["WindowBorderSize"] = style.WindowBorderSize;
	Sizes["WindowMinSize"] = PreferencesFun::ImVec2ToJson(style.WindowMinSize);
	Sizes["WindowTitleAlign"] = PreferencesFun::ImVec2ToJson(style.WindowTitleAlign);
	Sizes["WindowMenuButtonPosition"] = style.WindowMenuButtonPosition;
	Sizes["ChildRounding"] = style.ChildRounding;
	Sizes["ChildBorderSize"] = style.ChildBorderSize;
	Sizes["PopupRounding"] = style.PopupRounding;
	Sizes["PopupBorderSize"] = style.PopupBorderSize;
	Sizes["FramePadding"] = PreferencesFun::ImVec2ToJson(style.FramePadding);
	Sizes["FrameRounding"] = style.FrameRounding;
	Sizes["FrameBorderSize"] = style.FrameBorderSize;
	Sizes["ItemSpacing"] = PreferencesFun::ImVec2ToJson(style.ItemSpacing);
	Sizes["ItemInnerSpacing"] = PreferencesFun::ImVec2ToJson(style.ItemInnerSpacing);
	Sizes["CellPadding"] = PreferencesFun::ImVec2ToJson(style.CellPadding);
	Sizes["TouchExtraPadding"] = PreferencesFun::ImVec2ToJson(style.TouchExtraPadding);
	Sizes["IndentSpacing"] = style.IndentSpacing;
	Sizes["ColumnsMinSpacing"] = style.ColumnsMinSpacing;
	Sizes["ScrollbarSize"] = style.ScrollbarSize;
	Sizes["ScrollbarRounding"] = style.ScrollbarRounding;
	Sizes["GrabMinSize"] = style.GrabMinSize;
	Sizes["GrabRounding"] = style.GrabRounding;
	Sizes["LogSliderDeadzone"] = style.LogSliderDeadzone;
	Sizes["TabRounding"] = style.TabRounding;
	Sizes["TabBorderSize"] = style.TabBorderSize;
	Sizes["TabMinWidthForCloseButton"] = style.TabMinWidthForCloseButton;
	Sizes["ColorButtonPosition"] = style.ColorButtonPosition;
	Sizes["ButtonTextAlign"] = PreferencesFun::ImVec2ToJson(style.ButtonTextAlign);
	Sizes["SelectableTextAlign"] = PreferencesFun::ImVec2ToJson(style.SelectableTextAlign);
	Sizes["DisplayWindowPadding"] = PreferencesFun::ImVec2ToJson(style.DisplayWindowPadding);
	Sizes["DisplaySafeAreaPadding"] = PreferencesFun::ImVec2ToJson(style.DisplaySafeAreaPadding);
	//Sizes["CurveTessellationTol"]       =       style.CurveTessellationTol;
	//Sizes["CircleTessellationMaxError"] =       style.CircleTessellationMaxError;

	Style["Style"] = Sizes;
	Style["Colors"] = Colors;

	PorjectSettingSave["Style"] = Style;
	PorjectSettingSave["RootWindowSetting"] = RootWindows->DrawPorjectSettingSave();

	PorjectSettingSave["Font"] = HFontToJson(FontBuff);

	PorjectSettingSave["OutputUsingSeparateFontFiles"] = FontBuff.OutputUsingSeparateFontFiles;
	PorjectSettingSave["FoontFileName"] = FontBuff.FontFileName;
	return PorjectSettingSave;
}
static void LoadPorjectSetting(json PorjectSettingSave)
{
	try
	{
		if (PorjectSettingSave.is_null())
			return;
		json Style, Color, Colors, Sizes;

		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;

		LoadFont(PorjectSettingSave["Font"], FontBuff);

		Style = PorjectSettingSave["Style"];
		RootWindows->DrawPorjectSettingLoad(PorjectSettingSave["RootWindowSetting"]);

		Colors = Style["Colors"];
		Sizes = Style["Style"];
		for (size_t i = 0; i < Colors.size(); i++)
		{
			Color = Colors[ImGui::GetStyleColorName(i)];
			colors[i].x = Color["R"];
			colors[i].y = Color["G"];
			colors[i].z = Color["B"];
			colors[i].w = Color["A"];
		}

		style.WindowPadding = PreferencesFun::JsonToImVec2(Sizes["WindowPadding"]);
		style.WindowRounding = Sizes["WindowRounding"];
		style.WindowBorderSize = Sizes["WindowBorderSize"];
		style.WindowMinSize = PreferencesFun::JsonToImVec2(Sizes["WindowMinSize"]);
		style.WindowTitleAlign = PreferencesFun::JsonToImVec2(Sizes["WindowTitleAlign"]);
		style.WindowMenuButtonPosition = Sizes["WindowMenuButtonPosition"];
		style.ChildRounding = Sizes["ChildRounding"];
		style.ChildBorderSize = Sizes["ChildBorderSize"];
		style.PopupRounding = Sizes["PopupRounding"];
		style.PopupBorderSize = Sizes["PopupBorderSize"];
		style.FramePadding = PreferencesFun::JsonToImVec2(Sizes["FramePadding"]);
		style.FrameRounding = Sizes["FrameRounding"];
		style.FrameBorderSize = Sizes["FrameBorderSize"];
		style.ItemSpacing = PreferencesFun::JsonToImVec2(Sizes["ItemSpacing"]);
		style.ItemInnerSpacing = PreferencesFun::JsonToImVec2(Sizes["ItemInnerSpacing"]);
		style.CellPadding = PreferencesFun::JsonToImVec2(Sizes["CellPadding"]);
		style.TouchExtraPadding = PreferencesFun::JsonToImVec2(Sizes["TouchExtraPadding"]);
		style.IndentSpacing = Sizes["IndentSpacing"];
		style.ColumnsMinSpacing = Sizes["ColumnsMinSpacing"];
		style.ScrollbarSize = Sizes["ScrollbarSize"];
		style.ScrollbarRounding = Sizes["ScrollbarRounding"];
		style.GrabMinSize = Sizes["GrabMinSize"];
		style.GrabRounding = Sizes["GrabRounding"];
		style.LogSliderDeadzone = Sizes["LogSliderDeadzone"];
		style.TabRounding = Sizes["TabRounding"];
		style.TabBorderSize = Sizes["TabBorderSize"];
		style.TabMinWidthForCloseButton = Sizes["TabMinWidthForCloseButton"];
		style.ColorButtonPosition = Sizes["ColorButtonPosition"];
		style.ButtonTextAlign = PreferencesFun::JsonToImVec2(Sizes["ButtonTextAlign"]);
		style.SelectableTextAlign = PreferencesFun::JsonToImVec2(Sizes["SelectableTextAlign"]);
		style.DisplayWindowPadding = PreferencesFun::JsonToImVec2(Sizes["DisplayWindowPadding"]);
		style.DisplaySafeAreaPadding = PreferencesFun::JsonToImVec2(Sizes["DisplaySafeAreaPadding"]);

		FontBuff.OutputUsingSeparateFontFiles = PorjectSettingSave["OutputUsingSeparateFontFiles"];
		FontBuff.FontFileName = PorjectSettingSave["FoontFileName"];
		//style.CurveTessellationTol						      =              Sizes["CurveTessellationTol"]       		  ;
		//style.CircleTessellationMaxError					  =              Sizes["CircleTessellationMaxError"] 		  ;

		GUIStyle = style;
	}
	catch (const json::exception& e)
	{
		std::cout << "\n PorjectSettingPanel->LoadPorjectSetting->Json->Error->Error Message : " << e.what();
	}
}

//static void ExportPorjectSettingCallback(std::string path)
//{
//	std::ofstream file(path.append("\\PorjectSetting.HEditorPorjectSetting.json"));
//	if (file.is_open())
//	{
//		file << SavePorjectSetting();
//	}
//	file.close();
//}

//static void ImportPorjectSettingCallback(std::string path)
//{
//	std::ifstream file(path);
//	if (file.is_open())
//		LoadPorjectSetting(json::parse(file));
//	file.close();
//}

static void DrawPorjectSetting()
{
	if (!ShowPorjectSettingPanel)
		return;

	if (ImGui::Begin(std::string(PorjectSettingTranslateList::PorjectSetting).append("###Porject Setting").c_str(), &ShowPorjectSettingPanel))
	{
		ImGui::BeginChild("PorjectSettingSelect", ImVec2(150, 0), true);
		if (ImGui::Selectable(PreferencesVar::TranslateText::TranslateData.at(5).c_str(), SettingSelectIndex == 0))
			SettingSelectIndex = 0;
		if (ImGui::Selectable(std::string(PorjectSettingTranslateList::MainWindow).append("##Main Window").c_str(), SettingSelectIndex == 1))
			SettingSelectIndex = 1;

		ImGui::EndChild();
		ImGui::SameLine(0, 5);
		ImGui::BeginGroup();
		if (ImGui::Button(HT_Export))
		{
			//FileBrowser::OpenBrowser(ExportPorjectSettingCallback,true);
			ifd::FileDialog::Instance().Save("Export_Porject_Setting", PorjectSettingTranslateList::PorjectSetting, "*.HEditorPorjectSetting {.HEditorPorjectSetting}");
		}
		ImGui::SameLine();
		if (ImGui::Button(HT_Import))
		{
			//LoadPorjectSetting();
			//FileBrowser::OpenBrowser(ImportPorjectSettingCallback, false, ".HEditorPorjectSetting.");
			ifd::FileDialog::Instance().Open("Import_Porject_Setting", PorjectSettingTranslateList::PorjectSetting, "*.HEditorPorjectSetting {.HEditorPorjectSetting}");
		}
		//FileBrowser::DrawFileBrowser();
		if (ifd::FileDialog::Instance().IsDone("Export_Porject_Setting")) {
			if (ifd::FileDialog::Instance().HasResult()) {
				std::string res = ifd::FileDialog::Instance().GetResult().u8string();
				std::ofstream file(res);
				if (file.is_open())
				{
					file << SavePorjectSetting();
				}
				file.close();
			}
			ifd::FileDialog::Instance().Close();
		}
		if (ifd::FileDialog::Instance().IsDone("Import_Porject_Setting")) {
			if (ifd::FileDialog::Instance().HasResult()) {
				std::string res = ifd::FileDialog::Instance().GetResult().u8string();
				std::ifstream file(res);
				if (file.is_open())
					LoadPorjectSetting(json::parse(file));
				file.close();
			}
			ifd::FileDialog::Instance().Close();
		}
		switch (SettingSelectIndex)
		{
		case 0:
			if (ImGui::Button("Select font"))
			{
				ifd::FileDialog::Instance().Open("Select_Font", PorjectSettingTranslateList::PorjectSetting, "*.ttf {.ttf}");
			}

			ImGui::SameLine();
			ImGui::SetNextItemWidth(120);
			ImGui::DragFloat("Font Size", &FontBuff.font_size, 0.5, 1, 1000, "%.2f px");

			if (FontBuff.FontBuff->FontSize != FontBuff.font_size)
			{
				ImGui::SameLine();
				if (FontBuff.font.empty())
				{
					if (ImGui::Button("Updata Font Size"))
					{
						FontBuff.NeedUpdata = true;
					}
				}
				else
				{
					if (ImGui::Button("Updata Font Size"))
					{
						if (std::filesystem::exists(FontBuff.LoadFontPath))
						{
							FontBuff.NeedUpdata = true;
						}
					}
				}
			}

			ImGui::Checkbox("Output using separate font files", &FontBuff.OutputUsingSeparateFontFiles);

			if (ifd::FileDialog::Instance().IsDone("Select_Font")) {
				if (ifd::FileDialog::Instance().HasResult()) {
					std::string res = ifd::FileDialog::Instance().GetResult().u8string();
					FontBuff.LoadFontFile(res);
					FontBuff.LoadFontPath = res;
					FontBuff.NeedUpdata = true;
				}
				ifd::FileDialog::Instance().Close();
			}

			if (ImGui::TreeNode(std::string(PreferencesVar::TranslateText::TranslateData.at(6)).append("###Main").c_str()))
			{
				//if (ImGui::Button(PreferencesVar::TranslateText::TranslateData.at(7).c_str()))
				//{
				//	ImGui::OpenPopup(PreferencesVar::TranslateText::TranslateData.at(7).c_str());
				//}
				//if (ImGui::BeginPopupModal(PreferencesVar::TranslateText::TranslateData.at(7).c_str(), 0, ImGuiWindowFlags_NoResize))
				//{
				//	ImGui::Text(PreferencesVar::TranslateText::TranslateData.at(9).c_str());
				//
				//	if (ImGui::Button(HT_Confirm, ImVec2(150, 0)))
				//	{
				//		PreferencesFun::SaveThemeMainStyle();
				//		ImGui::CloseCurrentPopup();
				//	}
				//	ImGui::SameLine();
				//	if (ImGui::Button(HT_Cancel, ImVec2(150, 0)))
				//		ImGui::CloseCurrentPopup();
				//
				//	ImGui::EndPopup();
				//}
				//ImGui::SameLine();
				//if (ImGui::Button(PreferencesVar::TranslateText::TranslateData.at(10).c_str()))
				//	PreferencesFun::LoadThemeMainStyle();
				//ImGui::SameLine();
				//static std::string* SelectStyleFile = NULL;
				//if (ImGui::BeginCombo(PreferencesVar::TranslateText::TranslateData.at(8).c_str(), "", ImGuiComboFlags_::ImGuiComboFlags_NoPreview))
				//{
				//	std::vector<std::string> StyleFilePath;
				//	getFileNames("DependentFile\\configuration file\\Style", StyleFilePath);
				//	for (size_t i = 0; i < StyleFilePath.size(); i++)
				//	{
				//		if (ImGui::Selectable(StyleFilePath.at(i).substr(39, 60).c_str()))
				//		{
				//			if (SelectStyleFile)
				//				delete SelectStyleFile;
				//			SelectStyleFile = new std::string(StyleFilePath.at(i));
				//			//ImGui::OpenPopup("Test");//std::string(PreferencesVar::TranslateText::TranslateData.at(8)).append("###Popup").c_str());
				//			std::cout << "\n Down";
				//		}
				//
				//
				//	}
				//	ImGui::EndCombo();
				//	if (SelectStyleFile)
				//		ImGui::OpenPopup(std::string(PreferencesVar::TranslateText::TranslateData.at(8)).append("###Popup").c_str());
				//}
				//if (ImGui::BeginPopupModal(std::string(PreferencesVar::TranslateText::TranslateData.at(8)).append("###Popup").c_str(), 0, ImGuiWindowFlags_NoResize))
				//{
				//	//ImGui::CloseCurrentPopup();
				//	ImGui::Text(PreferencesVar::TranslateText::TranslateData.at(9).c_str());
				//
				//	if (ImGui::Button(HT_Confirm, ImVec2(150, 0)))
				//	{
				//		//PreferencesFun::SaveThemeMainStyle();
				//		HCopyFile(*SelectStyleFile, "DependentFile\\configuration file\\UseStyle.json");
				//		PreferencesFun::LoadThemeMainStyle();
				//		delete SelectStyleFile;
				//		SelectStyleFile = NULL;
				//		ImGui::CloseCurrentPopup();
				//	}
				//	ImGui::SameLine();
				//	if (ImGui::Button(HT_Cancel, ImVec2(150, 0)))
				//	{
				//		delete SelectStyleFile;
				//		SelectStyleFile = NULL;
				//		ImGui::CloseCurrentPopup();
				//	}
				//
				//
				//	ImGui::EndPopup();
				//}
				if (ImGui::TreeNode(std::string(PreferencesVar::TranslateText::TranslateData.at(11)).append("###Color").c_str()))
				{
					PreferencesFun::ThemeMain();

					ImGui::TreePop();
				}
				if (ImGui::TreeNode(std::string(PreferencesVar::TranslateText::TranslateData.at(12)).append("###Sizes").c_str()))
				{
					ImGuiStyle& style = ImGui::GetStyle();

					ImGui::Text(PreferencesVar::TranslateText::TranslateData.at(6).c_str());
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat2(PreferencesVar::TranslateText::ThemeTranslateData.at(55).c_str()/*"WindowPadding",      */, (float*)&style.WindowPadding, 0.0f, 20.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat2(PreferencesVar::TranslateText::ThemeTranslateData.at(56).c_str()/*"FramePadding",       */, (float*)&style.FramePadding, 0.0f, 20.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat2(PreferencesVar::TranslateText::ThemeTranslateData.at(57).c_str()/*"CellPadding",        */, (float*)&style.CellPadding, 0.0f, 20.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat2(PreferencesVar::TranslateText::ThemeTranslateData.at(58).c_str()/*"ItemSpacing",        */, (float*)&style.ItemSpacing, 0.0f, 20.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat2(PreferencesVar::TranslateText::ThemeTranslateData.at(59).c_str()/*"ItemInnerSpacing",   */, (float*)&style.ItemInnerSpacing, 0.0f, 20.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat2(PreferencesVar::TranslateText::ThemeTranslateData.at(60).c_str()/*"TouchExtraPadding",  */, (float*)&style.TouchExtraPadding, 0.0f, 10.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(61).c_str()/*"IndentSpacing",      */, &style.IndentSpacing, 0.0f, 30.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(62).c_str()/*"ScrollbarSize",      */, &style.ScrollbarSize, 1.0f, 20.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(63).c_str()/*"GrabMinSize",        */, &style.GrabMinSize, 1.0f, 20.0f, "%.0f");
					ImGui::Text(PreferencesVar::TranslateText::ThemeTranslateData.at(64).c_str()/*"Borders"             */);
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(65).c_str()/*"WindowBorderSize",   */, &style.WindowBorderSize, 0.0f, 1.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(66).c_str()/*"ChildBorderSize",    */, &style.ChildBorderSize, 0.0f, 1.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(67).c_str()/*"PopupBorderSize",    */, &style.PopupBorderSize, 0.0f, 1.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(68).c_str()/*"FrameBorderSize",    */, &style.FrameBorderSize, 0.0f, 1.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(69).c_str()/*"TabBorderSize",      */, &style.TabBorderSize, 0.0f, 1.0f, "%.0f");
					ImGui::Text(PreferencesVar::TranslateText::ThemeTranslateData.at(70).c_str()/*"Rounding"            */);
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(71).c_str()/*"WindowRounding",     */, &style.WindowRounding, 0.0f, 12.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(72).c_str()/*"ChildRounding",      */, &style.ChildRounding, 0.0f, 12.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(73).c_str()/*"FrameRounding",      */, &style.FrameRounding, 0.0f, 12.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(74).c_str()/*"PopupRounding",      */, &style.PopupRounding, 0.0f, 12.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(75).c_str()/*"ScrollbarRounding",  */, &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(76).c_str()/*"GrabRounding",       */, &style.GrabRounding, 0.0f, 12.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(77).c_str()/*"LogSliderDeadzone",  */, &style.LogSliderDeadzone, 0.0f, 12.0f, "%.0f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat(PreferencesVar::TranslateText::ThemeTranslateData.at(78).c_str()/*"TabRounding",        */, &style.TabRounding, 0.0f, 12.0f, "%.0f");
					ImGui::Text(PreferencesVar::TranslateText::ThemeTranslateData.at(79).c_str()/*"Alignment"           */);
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat2(PreferencesVar::TranslateText::ThemeTranslateData.at(80).c_str()/*"WindowTitleAlign",   */, (float*)&style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
					int window_menu_button_position = style.WindowMenuButtonPosition + 1;
					ImGui::SetNextItemWidth(250);
					if (ImGui::Combo(PreferencesVar::TranslateText::ThemeTranslateData.at(81).c_str()/*"WindowMenuButtonPosition",*/, (int*)&window_menu_button_position, "None\0Left\0Right\0"))
						style.WindowMenuButtonPosition = window_menu_button_position - 1;
					ImGui::SetNextItemWidth(250);
					ImGui::Combo(PreferencesVar::TranslateText::ThemeTranslateData.at(82).c_str()/*"ColorButtonPosition",   */, (int*)&style.ColorButtonPosition, "Left\0Right\0");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat2(PreferencesVar::TranslateText::ThemeTranslateData.at(83).c_str()/*"ButtonTextAlign",       */, (float*)&style.ButtonTextAlign, 0.0f, 1.0f, "%.2f");
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat2(PreferencesVar::TranslateText::ThemeTranslateData.at(84).c_str()/*"SelectableTextAlign",   */, (float*)&style.SelectableTextAlign, 0.0f, 1.0f, "%.2f");
					//ImGui::SameLine();
					ImGui::Text(PreferencesVar::TranslateText::ThemeTranslateData.at(85).c_str()/*"Safe Area Padding"      */);
					ImGui::SetNextItemWidth(250);
					ImGui::SliderFloat2(PreferencesVar::TranslateText::ThemeTranslateData.at(86).c_str()/*"DisplaySafeAreaPadding",*/, (float*)&style.DisplaySafeAreaPadding, 0.0f, 30.0f, "%.0f");
					ImGui::TreePop();
				}

				GUIStyle = ImGui::GetStyle();
				ImGui::TreePop();
			}
			break;
		case 1:
			RootWindows->DrawPorjectSetting();
			break;
		default:
			break;
		}

		ImGui::EndGroup();
	}
	ImGui::End();
}