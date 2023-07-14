#pragma once
#ifndef HWindow
#define HWindow

#include "HTranslate.h"
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#pragma comment(lib,"Opengl32.lib")
#include <vector>

static class BaceHWindows
{
public:
	virtual void InitWindows() { return; }
	virtual void CreateWindows(const char* title, int x, int y) { return; }
	virtual void* GetWindow() { return 0; }
	virtual bool InitializeBeforeRendering() { return 0; }
	virtual bool WhetherToEnableRenderingLoop() { return 0; }
	virtual void FrameInit() { return; }
	virtual void FrameEnd() { return; }
	virtual void ReCreateObject() { return; }

	virtual const char* GetCod_Inculd() { return ""; }
	virtual const char* GetCod_InitWindows() { return ""; }
	virtual const char* GetCod_CreateWindows() { return ""; }
	virtual const char* GetCod_InitializeBeforeRendering() { return ""; }
	virtual const char* GetCod_WhetherToEnableRenderingLoop() { return ""; }
	virtual const char* GetCod_FrameInit() { return ""; }
	virtual const char* GetCod_FrameEnd() { return ""; }

	virtual void DrawPorjectSetting() { return; }
	virtual void DrawPorjectSettingLoad(json Data) { return; }
	virtual json DrawPorjectSettingSave() { return json(); }

	int WindowSize_X = 800;
	int WindowSize_Y = 900;

	char WindowTitle[150] = { "HWindow Title" };

	std::string InculdPathList;
	std::string LibPath;
	std::string Lib;
	std::vector<std::string> CompileFiles;
private:

};
static BaceHWindows* RootWindows;

static class HOpenGLWindow :public BaceHWindows
{
public:
	HOpenGLWindow()
	{
		InculdPathList  = "API\\ImGui;API\\ImGui\\backends;API\\GLFW\\include;";
		LibPath = "API\\GLFW;";
		Lib = "glfw3.lib;%(AdditionalDependencies)";
		CompileFiles = {
			"API\\ImGui\\imconfig.h",
			"API\\ImGui\\imgui.cpp",
			"API\\ImGui\\imgui.h",
			"API\\ImGui\\imgui_demo.cpp",
			"API\\ImGui\\imgui_draw.cpp",
			"API\\ImGui\\imgui_internal.h",
			"API\\ImGui\\imgui_tables.cpp",
			"API\\ImGui\\imgui_widgets.cpp",
			"API\\ImGui\\imstb_rectpack.h",
			"API\\ImGui\\imstb_textedit.h",
			"API\\ImGui\\imstb_truetype.h",
			"API\\ImGui\\backends\\imgui_impl_glfw.cpp",
			"API\\ImGui\\backends\\imgui_impl_glfw.h",
			"API\\ImGui\\backends\\imgui_impl_opengl3.cpp",
			"API\\ImGui\\backends\\imgui_impl_opengl3.h",
			"API\\ImGui\\backends\\imgui_impl_opengl3_loader.h"
		};
	}

	virtual void InitWindows()override;
	virtual void CreateWindows(const char* title, int x, int y)override;
	virtual void* GetWindow()override { return Windows; }
	virtual bool InitializeBeforeRendering()override;
	virtual bool WhetherToEnableRenderingLoop()override;
	virtual void FrameInit()override;
	virtual void FrameEnd()override;
	virtual void ReCreateObject()override;

	virtual const char* GetCod_Inculd()override;
	virtual const char* GetCod_InitWindows()override;
	virtual const char* GetCod_CreateWindows()override;
	virtual const char* GetCod_InitializeBeforeRendering()override;
	virtual const char* GetCod_WhetherToEnableRenderingLoop()override;
	virtual const char* GetCod_FrameInit()override;
	virtual const char* GetCod_FrameEnd()override;

	virtual void DrawPorjectSetting()override;
	virtual void DrawPorjectSettingLoad(json Data)override;
	virtual json DrawPorjectSettingSave()override;
private:
	GLFWwindow* Windows;
};

#endif // !1