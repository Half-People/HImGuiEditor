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

	RootWindows->CreateWindows("HalfPeopleStudio ImGui Editor", 800, 900);

	HLoadImage("DependentFile\\DFL.HLogo", DefaultLogo);
	HLoadImage("DependentFile\\Image\\Delete.png", DeleteIcon);
	HLoadImage("DependentFile\\Image\\Plugin.png", PluginImage);
	HLoadImage("DependentFile\\Image\\Setting.png", PorjectSettingImage);
	HLoadImage("DependentFile\\Image\\Save.png", SaveImage);
	HLoadImage("DependentFile\\Image\\EditViewBg.jpg", EditViewBg);
	HLoadImage("DependentFile\\Image\\Mouse.png", MouseModeImg);
	HLoadImage("DependentFile\\Image\\Move.png", ArrowModeImg);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext(NULL);

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiViewportFlags_NoDecoration;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	io.ConfigFlags |= ImGuiCol_DockingEmptyBg;

	ImGui::StyleColorsDark();
	GUIStyle = ImGui::GetStyle();

	io.Fonts->AddFontFromFileTTF("DependentFile\\kaiu.ttf", 20, NULL, io.Fonts->GetGlyphRangesChineseFull());

	std::cout << "\n InitializeBeforeRendering" << RootWindows->InitializeBeforeRendering();

	CreateDefaulWidget();
	LoadWidgetPlugin();
	VerifyHWidgetList();

	InitSettingPanel();
	InitexportCode();

	InitComponentTreePanel

		TranslateAllObject();

	PostTranslationInit();

	EditorStyle = ImGui::GetStyle();
	AutoSaveInit();
	while (RootWindows->WhetherToEnableRenderingLoop())
	{
		ImGui::GetStyle() = EditorStyle;
		RootWindows->FrameInit();
		ImGui::DockSpaceOverViewport();
		SplashScreen::DrawSplashScreen();
		KeyTick();
		DrawMainMenuBar();

		ImGui::ShowDemoWindow();
		DrawSettingPanel();
		DrawControlPanel();
		DrawDetailsPanel();

		DrawPluginPanel();
		DrawPagingPanel();
		DrawComponentTreePanel();
		DrawDeleteWidgetPanel();
		DrawWindowDetailsPanel();
		DrawExportCode();

		ImGui::GetStyle() = GUIStyle;
		DrawPorjectSetting();

		ImGuiWindows.at(SelectHImGuiWindows)->Draw();

		RootWindows->FrameEnd();

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