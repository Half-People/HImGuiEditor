//#define _NO_CRT_STDIO_INLINE
#include "HWindows.h"

#include <iostream>
#include "File.h"
#include "MainMenuBar.h"
#include "ControlPanel.h"
#include "DetailsPanel.h"
#include "PagingPanel.h"
#include "PluginPanel.h"
#include "ComponentTreePanel.h"
#include "HImGuiWindowDetailsPanel.h"
#include "PorjectSettingPanel.h"
//#include "SettingPanel.h"
#include "HImGuiWindows.h"
#include "DeleteWidgetPanel.h"
#include "ExportCodePanel.h"
#include "SplashScreenPanel.h"
#include "Plugin.h"
#include "KeyAndAutoSave.h"
#include "ImFileDialogTool.h"

int main()
{
	switch (0)// Select Windows Mode
	{
	case 0:
		RootWindows = new HOpenGLWindow;
		break;
	default:
		RootWindows = new HOpenGLWindow;
		break;
	}

	ImGuiWindows.push_back(new HImGuiWindows);

	RootWindows->InitWindows();

	RootWindows->CreateWindows("HalfPeopleStudio ImGui Editor", 1920, 1080);

	//Updata Bg image
	if (HHaveFile("DependentFile\\Image\\EditViewBg.HBG_Bff"))
	{
		remove("DependentFile\\Image\\EditViewBg.HBG");
		rename("DependentFile\\Image\\EditViewBg.HBG_Bff", "DependentFile\\Image\\EditViewBg.HBG");
	}

	HLoadImage("DependentFile\\DFL.HLogo", DefaultLogo);
	HLoadImage("DependentFile\\Image\\Delete.png", DeleteIcon);
	HLoadImage("DependentFile\\Image\\Plugin.png", PluginImage);
	HLoadImage("DependentFile\\Image\\Setting.png", PorjectSettingImage);
	HLoadImage("DependentFile\\Image\\Save.png", SaveImage);
	HLoadImage("DependentFile\\Image\\EditViewBg.HBG", EditViewBg);
	HLoadImage("DependentFile\\Image\\Mouse.png", MouseModeImg);
	HLoadImage("DependentFile\\Image\\Move.png", ArrowModeImg);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext(NULL);

	ImGuiIO& io = ImGui::GetIO();

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiViewportFlags_NoDecoration;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiCol_DockingEmptyBg;

	ImGui::StyleColorsDark();
	GUIStyle = ImGui::GetStyle();

	io.Fonts->AddFontFromFileTTF("DependentFile\\kaiu.ttf", 20, NULL, io.Fonts->GetGlyphRangesChineseFull());
	//GUIFont = io.Fonts->AddFontDefault();
	FontBuff.Init();

	std::cout << "\n InitializeBeforeRendering" << RootWindows->InitializeBeforeRendering();

	//Init FileCallBack
	FileCallBack::DefaultLogo = &DefaultLogo;
	FileCallBack::HLoadImage1 = HLoadImage;
	FileCallBack::HLoadImage2 = HLoadImage1;
	FileCallBack::HLoadImage3 = HLoadImage2;
	FileCallBack::OsOpenInShell = OsOpenInShell;

	CreateDefaulWidget();
	LoadWidgetPlugin();
	VerifyHWidgetList();
	InitImFileDialog

		InitSettingPanel();
	InitexportCode();
	InitPorjectSetting();
	SplashScreenInit
		InitComponentTreePanel
		InitPluginPanel
		InitPagingPanel
		InitMainMenuBar
		InitFlagList();
	InitWindowDetailsPanel
		InitDetailsPanel
		InitControlPanel
		InitDeleteWidgetPanel
		InitEditViewport
		ExportMenuInit
		RightClickMenuInit
		TranslateAllObject();
	PostTranslationInit();

	EditorStyle = ImGui::GetStyle();
	AutoSaveInit();
	while (RootWindows->WhetherToEnableRenderingLoop())
	{
		ImGui::GetStyle() = EditorStyle;
		FontBuff.WiteDrawEnd(RootWindows);

		RootWindows->FrameInit();
		ImGui::DockSpaceOverViewport();
		SplashScreen::DrawSplashScreen();
		KeyTick();
		DrawMainMenuBar();

		DrawSettingPanel();
		DrawControlPanel();
		DrawDetailsPanel();

		DrawPluginPanel();
		DrawPagingPanel();
		DrawComponentTreePanel();
		DrawDeleteWidgetPanel();
		DrawWindowDetailsPanel();
		DrawExportCode();

		ImGuiWindows.at(SelectHImGuiWindows)->Draw(); //PopFont in HImGuiWindowDrawInit function
		DrawPorjectSetting();

		RootWindows->FrameEnd();
		//FontBuff.DelayedApplicationFontsInMainLoop(io);
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
	AutoSaveThread.detach();
}