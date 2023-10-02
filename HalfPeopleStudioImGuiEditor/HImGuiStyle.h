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
	std::vector<unsigned int> font;
	//	std::vector<int> font_Buff;
	float font_size = 20.f;
	size_t Fontfile_size = 0;
	ImFont* FontBuff;
	ImFontAtlas* font_atlas;
	std::string LoadFontPath;
	// will auto applay
	bool LoadFontFile(std::string font_path)
	{
		font.clear();
		std::ifstream font_file(font_path, std::ios::binary);
		if (!font_file)
			return false;

		font_file.seekg(0, std::ios::end);
		Fontfile_size = font_file.tellg();
		font_file.seekg(0, std::ios::beg);

		// 创建std::vector<int>对象，并分配足够的内存来保存文件数据
		font.resize(Fontfile_size / sizeof(unsigned int));

		// 读取文件数据到std::vector<int>对象中
		font_file.read(reinterpret_cast<char*>(font.data()), Fontfile_size);

		return true;
	}
	bool NeedUpdata = false;
	void WiteDrawEnd(BaceHWindows* RootWindow)
	{
		if (!NeedUpdata)
			return;
		NeedUpdata = false;
		font_atlas->Clear();
		font_atlas->AddFontFromFileTTF("DependentFile\\kaiu.ttf", 20, 0, font_atlas->GetGlyphRangesChineseFull());
		if (font.empty())
		{
			ImFontConfig cfg;
			cfg.SizePixels = font_size;
			FontBuff = font_atlas->AddFontDefault(&cfg);
		}
		else
		{
			if (LoadFontPath.empty())
			{
				FontBuff = font_atlas->AddFontFromMemoryTTF(static_cast<void*>(font.data()), Fontfile_size, font_size, 0, font_atlas->GetGlyphRangesChineseFull());
			}
			else
			{
				FontBuff = font_atlas->AddFontFromFileTTF(LoadFontPath.c_str(), font_size, 0, font_atlas->GetGlyphRangesChineseFull());
			}
		}

		font_atlas->Build();
		RootWindow->ReCreateObject();
	}
	void ClearFont()
	{
		font.clear();
	}
	void Init()
	{
		font_atlas = ImGui::GetIO().Fonts;
		//font_atlas->AddFontDefault();
		ImFontConfig cfg;
		cfg.SizePixels = font_size;
		FontBuff = font_atlas->AddFontDefault(&cfg);
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
