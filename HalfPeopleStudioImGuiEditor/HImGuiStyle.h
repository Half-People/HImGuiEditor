#pragma once

#ifndef HImGuiStyle
#define HImGuiStyle
#include <sstream>
#include <imgui.h>
#include <imgui_internal.h>

#include <vector>
#include <thread>
#include <string>
#include "H_stb.h"

static std::string ExtractFileNameAndExtension(const std::string& full_path)
{
	std::size_t last_slash = full_path.find_last_of("/\\");

	// 提取文件名和扩展名
	std::string file_name = full_path.substr(last_slash + 1);

	return file_name;
}

struct HFont
{
	std::vector<unsigned int> font;
	//	std::vector<int> font_Buff;
	bool OutputUsingSeparateFontFiles = true;
	float font_size = 20.f;
	size_t Fontfile_size = 0;
	ImFont* FontBuff;
	ImFontAtlas* font_atlas;
	std::string FontFileName;
	std::string LoadFontPath;
	// will auto applay
	bool LoadFontFile(std::string font_path)
	{
		LoadFontPath = font_path;
		FontFileName = ExtractFileNameAndExtension(LoadFontPath);
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
	bool SaveFontFile(std::string font_path)
	{
		printf("\n Output : Font Cache Path : %s", font_path.c_str());
		std::ofstream font_file(font_path, std::ios::binary);
		if (!font_file.good())
		{
			std::cout << "\n HImGuiStyle - > HFont -> SaveFontFile -> ofstream ->Error -> Save File Not Good";
			return false;
		}

		// 获取字体数据的大小
		std::size_t font_size = font.size() * sizeof(unsigned int);

		// 将字体数据写入文件
		font_file.write(reinterpret_cast<char*>(font.data()), font_size);

		return true;
	}
	char Encode85Byte(unsigned int x)
	{
		x = (x % 85) + 35;
		return (char)((x >= '\\') ? x + 1 : x);
	}
	std::string binary_to_compressed_c(bool use_compression = true, bool use_static = true)
	{
		std::string result;

		// 计算数据大小
		int data_sz = font.size() * sizeof(unsigned int);

		// 将数据转换为 char* 类型
		const char* data = reinterpret_cast<const char*>(font.data());

		// Compress
		int maxlen = data_sz + 512 + (data_sz >> 2) + sizeof(int); // total guess
		char* compressed = use_compression ? new char[maxlen] : const_cast<char*>(data);
		int compressed_sz = use_compression ? stb_compress((stb_uchar*)compressed, (stb_uchar*)data, data_sz) : data_sz;
		if (use_compression)
			memset(compressed + compressed_sz, 0, maxlen - compressed_sz);

		//Using Base85 encoded
		if (false)
		{
			// Output as Base85 encoded
			result += "// Exported using HImGuiEditor   \n";
			const char* static_str = use_static ? "static " : "";
			const char* compressed_str = use_compression ? "compressed_" : "";

			result += static_str;
			result += "const char ";
			result += "Font";
			result += "_";
			result += "data_[";
			result += std::to_string((int)((compressed_sz + 3) / 4) * 5);
			result += "+1] =\n    \"";

			char prev_c = 0;
			for (int src_i = 0; src_i < compressed_sz; src_i += 4)
			{
				// This is made a little more complicated by the fact that ??X sequences are interpreted as trigraphs by old C/C++ compilers. So we need to escape pairs of ??.
				unsigned int d = *(unsigned int*)(compressed + src_i);
				for (unsigned int n5 = 0; n5 < 5; n5++, d /= 85)
				{
					char c = Encode85Byte(d);
					result += (c == '?' && prev_c == '?') ? "\\%c" : std::string(1, c);
					prev_c = c;
				}
				if ((src_i % 112) == 112 - 4)
					result += "\"\n    \"";
			}
			result += "\";\n\n";
		}
		else
		{
			std::string symbol = "Font_";
			result += "// Exported using HImGuiEditor   \n";
			const char* static_str = use_static ? "static " : "";
			const char* compressed_str = use_compression ? "compressed_" : "";

			int column = 0;
			std::stringstream ss;

			ss << static_str << "const unsigned int " << symbol << "size = " << (int)compressed_sz << ";\n";

			ss << static_str << "const unsigned int " << symbol << "data[" << ((compressed_sz + 3) / 4) << "] =\n{";

			for (int i = 0; i < compressed_sz; i += 4)
			{
				unsigned int d = *(unsigned int*)(compressed + i);
				if ((column++ % 12) == 0)
					ss << "\n    ";
				else
					ss << " ";
				ss << "0x" << std::hex << std::setfill('0') << std::setw(8) << d << ",";
			}

			ss << "\n};\n\n";

			result += ss.str();
		}

		// Cleanup
		if (use_compression)
			delete[] compressed;

		return result;
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
				//FontBuff = font_atlas->AddFontFromMemoryTTF(static_cast<void*>(font.data()), Fontfile_size, font_size, 0, font_atlas->GetGlyphRangesChineseFull());
				//std::cout << "\n HImGuiStyle -> HFont -> WiteDrawEnd - > warn -> LoadFontPath Is NULL";
				//
				//ImFontConfig cfg;
				//cfg.SizePixels = font_size;
				//FontBuff = font_atlas->AddFontDefault(&cfg);

				if (SaveFontFile(std::string("DependentFile\\configuration file\\").append(FontFileName)))
					FontBuff = font_atlas->AddFontFromFileTTF(std::string("DependentFile\\configuration file\\").append(FontFileName).c_str(), font_size, 0, font_atlas->GetGlyphRangesChineseFull());
				else
				{
					printf("\nHImGuiStyle -> HFont -> WiteDrawEnd -> Error -> SaveFontFile");
					ImFontConfig cfg;
					cfg.SizePixels = font_size;
					FontBuff = font_atlas->AddFontDefault(&cfg);
				}
			}
			else
			{
				if (std::filesystem::exists(std::string("DependentFile\\configuration file\\").append(FontFileName)))
				{
					FontBuff = font_atlas->AddFontFromFileTTF(std::string("DependentFile\\configuration file\\").append(FontFileName).c_str(), font_size, 0, font_atlas->GetGlyphRangesChineseFull());
				}
				else
				{
					if (SaveFontFile(std::string("DependentFile\\configuration file\\").append(FontFileName)))
						FontBuff = font_atlas->AddFontFromFileTTF(std::string("DependentFile\\configuration file\\").append(FontFileName).c_str(), font_size, 0, font_atlas->GetGlyphRangesChineseFull());
					else
					{
						printf("\nHImGuiStyle -> HFont -> WiteDrawEnd -> Error -> SaveFontFile");
						ImFontConfig cfg;
						cfg.SizePixels = font_size;
						FontBuff = font_atlas->AddFontDefault(&cfg);
					}
				}
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
