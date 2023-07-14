#pragma once


#ifndef HImGuiStyle
#define HImGuiStyle
#include <sstream>
#include <imgui.h>
#include <imgui_internal.h>
#include <vector>
#include "HWindows.h"

struct HFont
{
	std::vector<int> font;
	float font_size = 20.f;
	size_t Fontfile_size;
	ImFont* FontBuff;
	ImFontAtlas* font_atlas;
	// will auto applay
	bool LoadFontFile(std::string font_path)
	{
		std::ifstream font_file(font_path, std::ios::binary);
		if (!font_file)
			return false;

		font_file.seekg(0, std::ios::end);
		Fontfile_size = font_file.tellg();
		font_file.seekg(0, std::ios::beg);

		// 创建std::vector<int>对象，并分配足够的内存来保存文件数据
		font.resize(Fontfile_size /sizeof(int));

		// 读取文件数据到std::vector<int>对象中
		font_file.read(reinterpret_cast<char*>(font.data()), Fontfile_size);
		return true;
	}
	bool NeedUpdata = false;
	void WiteDrawEnd(BaceHWindows * RootWindow)
	{
		if (!NeedUpdata)
			return;

		NeedUpdata = false;	
		font_atlas->Clear();
		font_atlas->AddFontFromFileTTF("DependentFile\\kaiu.ttf", 20, NULL);
		FontBuff = font_atlas->AddFontFromMemoryTTF(font.data(), Fontfile_size, font_size);// &config);
		font_atlas->Build();
		
		RootWindow->ReCreateObject();
	}
	void Init()
	{
		font_atlas = ImGui::GetIO().Fonts;
		//font_atlas->AddFontDefault();
		FontBuff = font_atlas->AddFontDefault();
	}
	void ApplayFont()
	{
		NeedUpdata = true;
	}
	ImFont* GetFont()
	{
		return FontBuff;
	}

	void PushFont()
	{
		if (FontBuff)
			ImGui::PushFont(FontBuff);
	}
	void PopFont()
	{
		if (FontBuff)
			ImGui::PopFont();
	}
};
static HFont FontBuff;
static ImGuiStyle EditorStyle;
static ImGuiStyle GUIStyle;
//static ImFont *GUIFont;
//static float GuiFontSize = 20.f;
static bool NeedDocking = true;



#endif // !1
