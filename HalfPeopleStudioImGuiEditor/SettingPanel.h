#pragma once

#ifndef SettingPanel
#define SettingPanel
#include <imgui.h>
#include <string>
//#include "MainMenuBar.h"
#include "HTranslate.h"
#include "File.h"
#include "HImGuiWidgetItem.h"
#include "HImGuiStyle.h"

namespace PreferencesVar
{
	static bool ShowFPS = false;
	namespace TranslateText
	{
		static std::vector<std::string> TranslateData
		{
			"Preferences",
			"Interface",
			"Translate",
			"Language",
			"Translate Schedule",
			"Theme",
			"Main",//6
			"SaveStyle",
			"SelectStyle",//8
			//"WillReplaceTheCurrentStyleFile"
			"will replace the current style file",//9
			"ResetStyle",
			"Color",
			"Sizes",//12
			"Optimization",//13
			"Reduce the number of rounded corners (Improve IDE speed)",
			"Show fps",//15
			"Auto save",//16
			"Auto save interval ( minute )"//17
		};
		static std::vector<std::string> ThemeTranslateData
		{
			"Text",
			"TextDisabled",
			"WindowBackground",
			"ChildWindowBackground",
			"PopupWindowBackground",
			"Border",
			"BorderShadow",
			"FrameBackground",
			"FrameBackgroundHovered",
			"FrameBackgroundFocus",
			"TitleBackground",
			"TitleBackgroundFocus",
			"TitleBackgroundCollapsed",
			"MenuBarBackground",
			"ScrollbarBackground",
			"ScrollbarGrab",
			"ScrollbarGrabHovered",
			"ScrollbarGrabFocus",
			"CheckMark",
			"SliderGrab",
			"SliderGrabFocus",
			"Button",
			"ButtonHovered",
			"ButtonFocus",
			"Header",
			"HeaderHovered",
			"HeaderFocus",
			"Separator",
			"SeparatorHovered",
			"SeparatorFocus",
			"Resize",
			"ResizeHovered",
			"ResizeFocus",
			"Tab",
			"Tab(Hovered)",
			"TabFocus",
			"Tab(Unfocused)",
			"Tab(UnfocusedFocus)",
			"DockingPreview",
			"DockingEmptyBackground",
			"PlotLines",
			"PlotLinesHovered",
			"PlotHistogram",
			"PlotHistogram(Hovered)",
			"TableHeaderBackground",
			"TableBorderStrong",
			"TableBorderLight",
			"TableRowBackground",
			"TableRowBackgroundAlt",
			"TextSelectBackground",
			"DragDropTarget",
			"NavHighlight",
			"NavWindowHighlight",
			"NavWindowDimBackground",
			"ModalWindowDimBackground",//55



			"WindowPadding",
			"Frame Padding",
			"CellPadding",
			"ItemSpacing",
			"ItemInnerSpacing",
			"Touch Extra Padding", //6
			"IndentSpacing",
			"ScrollbarSize",
			"Grab MinSize", //9
			"Borders",
			"WindowBorderSize",
			"ChildWindowBorderSize",//12
			"PopupBorderSize",
			"FrameBorderSize",
			"Tab BorderSize",//15
			"Angle Rounded", //16
			"Window Angle Rounded",//17
			"ChildWindow Angle Rounded",//18
			"Frame Angle Rounded",//19
			"Popup Angle Rounded",//20
			"Scrollbar Angle Rounded",//21
			"Grab Angle Rounded",//22
			"Log Slider Deadzone",
			"Tab (Angle Rounded)",//24
			"Align",
			"WindowTitleAlign",
			"WindowMenuButtonPosition",
			"ColorButtonPosition",
			"ButtonTextAlign",
			"SelectableTextAlign",
			"Safe Area Padding",
			"DisplaySafeAreaPadding",
		};
	}
}
static bool ShowSettingPanel = false;
static int SettingSelectIndex = 0;
static json SettingSave;
namespace AutoSave {
	static bool AutoSave;
	static float Interval = 5;
}
static void LoadSettingData()
{
	std::ifstream file("DependentFile\\configuration file\\Preferences.json");
	if(file.is_open())
		SettingSave = json::parse(file);
	file.close();
	TranslateTargetLang = SettingSave["TranslateTargetLang"];
	AutoSave::Interval = SettingSave["AutoSaveInterval"];
	AutoSave::AutoSave = SettingSave["AutoSave"];
}
static void PostTranslationInit()
{
	ImGui::GetStyle().CircleTessellationMaxError = SettingSave["CircleTessellationMaxError"];
	PreferencesVar::ShowFPS = SettingSave["ShowFPS"];
	//PreferencesVar::TranslateText::TranslateData.at(0).append("###Preferences");
}
static void SaveSettingData()
{
	std::ofstream file("DependentFile\\configuration file\\Preferences.json");
	if (file.is_open())
	{
		file << SettingSave;
	}
	file.close();
}


namespace PreferencesFun
{
	static json ImVec2ToJson(ImVec2 In)
	{
		json ImVec;
		ImVec["X"] = In.x;
		ImVec["Y"] = In.y;
		return ImVec;
	}

	static ImVec2 JsonToImVec2(json& js)
	{
		if (!js.is_null())
		{
			ImVec2 Out;
			Out.x = js["X"];
			Out.y = js["Y"];
			return Out;
		}
		std::cout << "\n JsonToImVec2-> JSON -> ERROR -> IsNull";
		return ImVec2(0, 0);
	}

	static void LoadThemeMainStyle()
	{
		json Style,Color,Colors,Sizes;
		std::ifstream file("DependentFile\\configuration file\\UseStyle.json");
		if (file.is_open())
			Style = json::parse(file);
		else
			return;
		file.close();
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;
		Colors = Style["Colors"];
		Sizes = Style["Style"];
		for (size_t i = 0; i < Colors.size(); i++)
		{
			Color= Colors[ImGui::GetStyleColorName(i)];
			colors[i].x = Color["R"];
			colors[i].y = Color["G"];
			colors[i].z = Color["B"];
			colors[i].w = Color["A"];
		}


		 style.WindowPadding                                  = JsonToImVec2(Sizes["WindowPadding"])                      ;
		 style.WindowRounding								  =              Sizes["WindowRounding"]             		  ;
		 style.WindowBorderSize						          =              Sizes["WindowBorderSize"]           		  ;
		 style.WindowMinSize  			                      = JsonToImVec2(Sizes["WindowMinSize"])             		  ;
		 style.WindowTitleAlign		                          = JsonToImVec2(Sizes["WindowTitleAlign"])           		  ;
		 style.WindowMenuButtonPosition				          =              Sizes["WindowMenuButtonPosition"]   		  ;
		 style.ChildRounding								  =              Sizes["ChildRounding"]              		  ;
		 style.ChildBorderSize								  =              Sizes["ChildBorderSize"]            		  ;
		 style.PopupRounding								  =              Sizes["PopupRounding"]              		  ;
		 style.PopupBorderSize								  =              Sizes["PopupBorderSize"]            		  ;
		 style.FramePadding					                  = JsonToImVec2(Sizes["FramePadding"])              		  ;
		 style.FrameRounding								  =              Sizes["FrameRounding"]              		  ;
		 style.FrameBorderSize								  =              Sizes["FrameBorderSize"]            		  ;
		 style.ItemSpacing					                  = JsonToImVec2(Sizes["ItemSpacing"])                		  ;
		 style.ItemInnerSpacing				                  = JsonToImVec2(Sizes["ItemInnerSpacing"])           		  ;
		 style.CellPadding					                  = JsonToImVec2(Sizes["CellPadding"])               		  ;
		 style.TouchExtraPadding				              = JsonToImVec2(Sizes["TouchExtraPadding"])          		  ;
		 style.IndentSpacing								  =              Sizes["IndentSpacing"]              		  ;
		 style.ColumnsMinSpacing							  =              Sizes["ColumnsMinSpacing"]          		  ;
		 style.ScrollbarSize								  =              Sizes["ScrollbarSize"]              		  ;
		 style.ScrollbarRounding							  =              Sizes["ScrollbarRounding"]          		  ;
		 style.GrabMinSize								      =              Sizes["GrabMinSize"]                		  ;
		 style.GrabRounding								      =              Sizes["GrabRounding"]               		  ;
		 style.LogSliderDeadzone							  =              Sizes["LogSliderDeadzone"]          		  ;
		 style.TabRounding									  =              Sizes["TabRounding"]                		  ;
		 style.TabBorderSize								  =              Sizes["TabBorderSize"]              		  ;
		 style.TabMinWidthForCloseButton					  =              Sizes["TabMinWidthForCloseButton"]  		  ;
		 style.ColorButtonPosition							  =              Sizes["ColorButtonPosition"]        		  ;
		 style.ButtonTextAlign				                  = JsonToImVec2(Sizes["ButtonTextAlign"])            		  ;
		 style.SelectableTextAlign			                  = JsonToImVec2(Sizes["SelectableTextAlign"])        		  ;
		 style.DisplayWindowPadding			                  = JsonToImVec2(Sizes["DisplayWindowPadding"])       		  ;
		 style.DisplaySafeAreaPadding		                  = JsonToImVec2(Sizes["DisplaySafeAreaPadding"])     		  ;
		 //style.CurveTessellationTol						      =              Sizes["CurveTessellationTol"]       		  ;
		 //style.CircleTessellationMaxError					  =              Sizes["CircleTessellationMaxError"] 		  ;

		 EditorStyle = style;
	}

	static void SaveThemeMainStyle()
	{
		json Style;
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec4* colors = style.Colors;

		json Color,Colors,Sizes;

		for (size_t i = 0; i < 55; i++)
		{
			Color["R"] = colors[i].x;
			Color["G"] = colors[i].y;
			Color["B"] = colors[i].z;
			Color["A"] = colors[i].w;
			Colors[ImGui::GetStyleColorName(i)] = Color;
		}

		Sizes["WindowPadding"]              =       ImVec2ToJson(style.WindowPadding);
		Sizes["WindowRounding"]             =       style.WindowRounding;
		Sizes["WindowBorderSize"]           =       style.WindowBorderSize;
		Sizes["WindowMinSize"]              =       ImVec2ToJson(style.WindowMinSize);
		Sizes["WindowTitleAlign"]           =       ImVec2ToJson(style.WindowTitleAlign);
		Sizes["WindowMenuButtonPosition"]   =       style.WindowMenuButtonPosition;
		Sizes["ChildRounding"]              =       style.ChildRounding;
		Sizes["ChildBorderSize"]            =       style.ChildBorderSize;
		Sizes["PopupRounding"]              =       style.PopupRounding;
		Sizes["PopupBorderSize"]            =       style.PopupBorderSize;
		Sizes["FramePadding"]               =       ImVec2ToJson(style.FramePadding);
		Sizes["FrameRounding"]              =       style.FrameRounding;
		Sizes["FrameBorderSize"]            =       style.FrameBorderSize;
		Sizes["ItemSpacing"]                =       ImVec2ToJson(style.ItemSpacing);
		Sizes["ItemInnerSpacing"]           =       ImVec2ToJson(style.ItemInnerSpacing);
		Sizes["CellPadding"]                =       ImVec2ToJson(style.CellPadding);
		Sizes["TouchExtraPadding"]          =       ImVec2ToJson(style.TouchExtraPadding);
		Sizes["IndentSpacing"]              =       style.IndentSpacing;
		Sizes["ColumnsMinSpacing"]          =       style.ColumnsMinSpacing;
		Sizes["ScrollbarSize"]              =       style.ScrollbarSize;
		Sizes["ScrollbarRounding"]          =       style.ScrollbarRounding;
		Sizes["GrabMinSize"]                =       style.GrabMinSize;
		Sizes["GrabRounding"]               =       style.GrabRounding;
		Sizes["LogSliderDeadzone"]          =       style.LogSliderDeadzone;
		Sizes["TabRounding"]                =       style.TabRounding;
		Sizes["TabBorderSize"]              =       style.TabBorderSize;
		Sizes["TabMinWidthForCloseButton"]  =       style.TabMinWidthForCloseButton;
		Sizes["ColorButtonPosition"]        =       style.ColorButtonPosition;
		Sizes["ButtonTextAlign"]            =       ImVec2ToJson(style.ButtonTextAlign);
		Sizes["SelectableTextAlign"]        =       ImVec2ToJson(style.SelectableTextAlign);
		Sizes["DisplayWindowPadding"]       =       ImVec2ToJson(style.DisplayWindowPadding);
		Sizes["DisplaySafeAreaPadding"]     =       ImVec2ToJson(style.DisplaySafeAreaPadding);
		//Sizes["CurveTessellationTol"]       =       style.CurveTessellationTol;
		//Sizes["CircleTessellationMaxError"] =       style.CircleTessellationMaxError;



		Style["Style"] = Sizes;
		Style["Colors"] = Colors;
		std::ofstream file("DependentFile\\configuration file\\UseStyle.json");
		if (file.is_open())
		{
			file << Style;
		}
		file.close();
		//EditorIO = ImGui::GetIO();
		EditorStyle = ImGui::GetStyle();
	}

	static void ThemeMain()
	{
		
		ImVec4* colors = ImGui::GetStyle().Colors;


		for (size_t i = 0; i < 54; i++)
		{
			ImGui::ColorEdit4(PreferencesVar::TranslateText::ThemeTranslateData.at(i).c_str(), (float*)&colors[i],ImGuiColorEditFlags_NoInputs);
		}
	}
}

static void InitSettingPanel()
{
	LoadSettingData();
	PreferencesFun::LoadThemeMainStyle();

	for (size_t i = 0; i < PreferencesVar::TranslateText::TranslateData.size(); i++)
	{
		TranslateObject.push_back(&PreferencesVar::TranslateText::TranslateData.at(i));
	}
	for (size_t i = 0; i < PreferencesVar::TranslateText::ThemeTranslateData.size(); i++)
	{
		TranslateObject.push_back(&PreferencesVar::TranslateText::ThemeTranslateData.at(i));
	}
}

static void DrawSettingPanel()
{
	if (!ShowSettingPanel)
		return;
	if (ImGui::Begin(std::string(PreferencesVar::TranslateText::TranslateData.at(0)).append("###Preferences").c_str(), &ShowSettingPanel))
	{
		ImGui::BeginChild("SettingSelect",ImVec2(150,0),true);
		if (ImGui::Selectable(PreferencesVar::TranslateText::TranslateData.at(1).c_str(), SettingSelectIndex == 0))
			SettingSelectIndex = 0;
		if (ImGui::Selectable(PreferencesVar::TranslateText::TranslateData.at(5).c_str(), SettingSelectIndex == 1))
			SettingSelectIndex = 1;

		ImGui::EndChild();
		ImGui::SameLine(0, 5);
		ImGui::BeginGroup();

		switch (SettingSelectIndex)
		{
		case 0:

			if (ImGui::TreeNode(std::string(PreferencesVar::TranslateText::TranslateData.at(2)).append("###Translate").c_str()))
			{
				
				ImGui::SetNextItemWidth(250);
				if (ImGui::BeginCombo(PreferencesVar::TranslateText::TranslateData.at(3).c_str(), GetTranslateTargetLang(TranslateTargetLang)))
				{
					for (size_t i = 0; i < GetLangsText.size(); i++)
					{
						if (ImGui::Selectable(GetTranslateTargetLang(i), i == TranslateTargetLang))
						{
							TranslateTargetLang = i;
							SettingSave["TranslateTargetLang"] = TranslateTargetLang;
							UpdataTranslateObject();
							SaveSettingData();
						}
					}
					ImGui::EndCombo();
				}
				ImGui::SameLine();
				if (ImGui::Button(HT_Reset))
				{
					TranslateTargetLang = -1;
					SettingSave["TranslateTargetLang"] = TranslateTargetLang;
					UpdataTranslateObject();
					SaveSettingData();
				}
				ImGui::Text(PreferencesVar::TranslateText::TranslateData.at(4).c_str());
				ImGui::BufferingBar("TranslateBar", Schedule,ImVec2(250,5),ImColor(0,100,210),ImColor(0,210,200));
				ImGui::TreePop();
			}
			if (ImGui::TreeNode(std::string(PreferencesVar::TranslateText::TranslateData.at(13)).append("###Optimization").c_str()))
			{
				//style.CircleTessellationMaxError;
				ImGui::SetNextItemWidth(250);
				if (ImGui::DragFloat("###CircleTessellationMaxError", &ImGui::GetStyle().CircleTessellationMaxError, 0.1, 0.1, 10))
				{
					SettingSave["CircleTessellationMaxError"] = ImGui::GetStyle().CircleTessellationMaxError;
					EditorStyle = ImGui::GetStyle();
					SaveSettingData();
				}
				ImGui::Text(PreferencesVar::TranslateText::TranslateData.at(14).c_str());



				ImGui::TreePop();
			}
			if (ImGui::TreeNode(std::string(PreferencesVar::TranslateText::TranslateData.at(1)).append("###GUI").c_str()))
			{
				ImGui::Text(PreferencesVar::TranslateText::TranslateData.at(15).c_str());
				ImGui::SameLine();
				if (ImGui::ToggleButton("ShowFPS", &PreferencesVar::ShowFPS))
				{
					SettingSave["ShowFPS"] = PreferencesVar::ShowFPS;
					SaveSettingData();
				}
				ImGui::TreePop();
			}
			if (ImGui::TreeNode(std::string(PreferencesVar::TranslateText::TranslateData.at(16)).append("###AutoSave").c_str()))
			{
				if (ImGui::Checkbox(PreferencesVar::TranslateText::TranslateData.at(16).c_str(), &AutoSave::AutoSave))
				{
					SettingSave["AutoSave"] = AutoSave::AutoSave;
					SaveSettingData();
				}
				ImGui::SetNextItemWidth(250);
				if (ImGui::DragFloat(PreferencesVar::TranslateText::TranslateData.at(17).c_str(), &AutoSave::Interval, 0.01, 0.001, 1440))
				{
					SettingSave["AutoSaveInterval"] = AutoSave::Interval;
					SaveSettingData();
				}

				ImGui::TreePop();
			}

			break;
		case 1:
			if (ImGui::TreeNode(std::string(PreferencesVar::TranslateText::TranslateData.at(6)).append("###Main").c_str()))
			{
				if (ImGui::Button(PreferencesVar::TranslateText::TranslateData.at(7).c_str()))
				{
					ImGui::OpenPopup(PreferencesVar::TranslateText::TranslateData.at(7).c_str());
					//SaveThemeMainStyle();
				}
				if (ImGui::BeginPopupModal(PreferencesVar::TranslateText::TranslateData.at(7).c_str(), 0,  ImGuiWindowFlags_NoResize))
				{
					//ImGui::CloseCurrentPopup();
					ImGui::Text(PreferencesVar::TranslateText::TranslateData.at(9).c_str());

					if (ImGui::Button(HT_Confirm, ImVec2(150, 0)))
					{
						PreferencesFun::SaveThemeMainStyle();
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();
					if (ImGui::Button(HT_Cancel, ImVec2(150, 0)))
						ImGui::CloseCurrentPopup();

					ImGui::EndPopup();
				}
				ImGui::SameLine();
				if (ImGui::Button(PreferencesVar::TranslateText::TranslateData.at(10).c_str()))
					PreferencesFun::LoadThemeMainStyle();
				ImGui::SameLine();
				static std::string* SelectStyleFile = NULL;
				if (ImGui::BeginCombo(PreferencesVar::TranslateText::TranslateData.at(8).c_str(), "", ImGuiComboFlags_::ImGuiComboFlags_NoPreview))
				{
					std::vector<std::string> StyleFilePath;
					getFileNames("DependentFile\\configuration file\\Style", StyleFilePath);
					for (size_t i = 0; i < StyleFilePath.size(); i++)
					{
						if (ImGui::Selectable(StyleFilePath.at(i).substr(39,60).c_str()))
						{
							if (SelectStyleFile)
								delete SelectStyleFile;
							SelectStyleFile = new std::string(StyleFilePath.at(i));
							//ImGui::OpenPopup("Test");//std::string(PreferencesVar::TranslateText::TranslateData.at(8)).append("###Popup").c_str());
							std::cout << "\n Down";
						}


					}
					ImGui::EndCombo();
					if(SelectStyleFile)
						ImGui::OpenPopup(std::string(PreferencesVar::TranslateText::TranslateData.at(8)).append("###Popup").c_str());
				}
				if (ImGui::BeginPopupModal(std::string(PreferencesVar::TranslateText::TranslateData.at(8)).append("###Popup").c_str(), 0,   ImGuiWindowFlags_NoResize))
				{
					//ImGui::CloseCurrentPopup();
					ImGui::Text(PreferencesVar::TranslateText::TranslateData.at(9).c_str());

					if (ImGui::Button(HT_Confirm, ImVec2(150, 0)))
					{
						//PreferencesFun::SaveThemeMainStyle();
						HCopyFile(*SelectStyleFile, "DependentFile\\configuration file\\UseStyle.json");
						PreferencesFun::LoadThemeMainStyle();
						delete SelectStyleFile;
						SelectStyleFile = NULL;
						ImGui::CloseCurrentPopup();
					}
					ImGui::SameLine();
					if (ImGui::Button(HT_Cancel, ImVec2(150, 0)))
					{
						delete SelectStyleFile;
						SelectStyleFile = NULL;
						ImGui::CloseCurrentPopup();
					}


					ImGui::EndPopup();
				}
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

				EditorStyle = ImGui::GetStyle();
				ImGui::TreePop();
			}


			break;
		default:
			break;
		}

		ImGui::EndGroup();
	}
	ImGui::End();
}

#endif // !SettingPanel