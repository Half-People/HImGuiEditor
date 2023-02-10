#include "HWindows.h"
#include <string>
//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void HOpenGLWindow::InitWindows()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void HOpenGLWindow::CreateWindows(const char* title, int x, int y)
{
	Windows = glfwCreateWindow(900, 800, "HImGuiEditor (By HalfPeopleStudio ,this is open source tool)", NULL, NULL);
	GLFWimage icons[1];
	icons[0].pixels =  stbi_load("DependentFile\\DFL.HLogo", &icons[0].width, &icons[0].height, 0, 4);
	glfwSetWindowIcon(Windows, 1, icons);
	stbi_image_free(icons[0].pixels);


	glfwMakeContextCurrent(Windows);
	//glfwSwapInterval(0);
}

bool HOpenGLWindow::InitializeBeforeRendering()
{
	if (!ImGui_ImplGlfw_InitForOpenGL(Windows, true))
		return false;
	if (!ImGui_ImplOpenGL3_Init("#version 330"))
		return false;
	return true;
}

bool HOpenGLWindow::WhetherToEnableRenderingLoop()
{
	return (!(bool)glfwWindowShouldClose(Windows));
}

void HOpenGLWindow::FrameInit()
{
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void HOpenGLWindow::FrameEnd()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(Windows);
	glfwPollEvents();
}

const char* HOpenGLWindow::GetCod_Inculd()
{
	return "\n#pragma comment(lib,\"Opengl32.lib\")\n#include <GLFW/glfw3.h>\n#include <imgui_impl_glfw.h>\n#include <imgui_impl_opengl3.h>";
}

const char* HOpenGLWindow::GetCod_InitWindows()
{
	return "	\n	glfwInit();\n	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);\n	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);\n	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); ";
}

const char* HOpenGLWindow::GetCod_CreateWindows()
{
	return std::string("\n	GLFWwindow* Windows;\n	Windows = glfwCreateWindow(").append(std::to_string(WindowSize_X)).append(",").append(std::to_string(WindowSize_Y)).append(",\"").append(WindowTitle).append("\", NULL, NULL); \n	glfwMakeContextCurrent(Windows); \n	glfwSwapInterval(0); ").c_str();
}

const char* HOpenGLWindow::GetCod_InitializeBeforeRendering()
{
	return "\n	ImGui_ImplGlfw_InitForOpenGL(Windows, true);\n	ImGui_ImplOpenGL3_Init(\"#version 330\"); ";
}

const char* HOpenGLWindow::GetCod_WhetherToEnableRenderingLoop()
{
	return "!glfwWindowShouldClose(Windows)";
}

const char* HOpenGLWindow::GetCod_FrameInit()
{
	return "\n		glClear(GL_COLOR_BUFFER_BIT);\n		ImGui_ImplOpenGL3_NewFrame();\n		ImGui_ImplGlfw_NewFrame();\n		ImGui::NewFrame(); ";
}

const char* HOpenGLWindow::GetCod_FrameEnd()
{
	return "\n		ImGui::Render();\n		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());\n\n		glfwSwapBuffers(Windows);\n		glfwPollEvents(); ";
}

void HOpenGLWindow::DrawPorjectSetting()
{
	ImGui::SetNextItemWidth(250);
	ImGui::InputText("Window Title", WindowTitle, 150);
	ImGui::Text("Window Size");
	ImGui::SetNextItemWidth(125);
	ImGui::DragInt("X", &WindowSize_X, 1, 1);
	ImGui::SameLine();
	ImGui::SetNextItemWidth(125);
	ImGui::DragInt("Y", &WindowSize_Y, 1, 1);
}

void HOpenGLWindow::DrawPorjectSettingLoad(json Data)
{
	std::string Save = Data["WindowTitle"];
	strcpy_s(WindowTitle, Save.c_str());
	WindowSize_X = Data["WindowSize_X"];
	WindowSize_Y = Data["WindowSize_Y"];
}

json HOpenGLWindow::DrawPorjectSettingSave()
{
	json S;
	S["WindowTitle"] = WindowTitle;
	S["WindowSize_X"] = WindowSize_X;
	S["WindowSize_Y"] = WindowSize_Y;
	return S;
}
