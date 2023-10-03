#pragma once
#include <imgui.h>
#include "HTranslate.h"
#include "Porject.h"
#include "HImGuiWindows.h"
#include "HWindows.h"
#include "HImGuiStyle.h"
#include "Plugin.h"
#define VSPorjectCPP "stdcpp17"

namespace ExportCodeNS
{
	std::string GetExportStyle()
	{
		std::string SaveExportText;
		//	IMGUI_CHECKVERSION();
		SaveExportText.append("\n").append("	IMGUI_CHECKVERSION();");
		//	ImGui::CreateContext(NULL);
		SaveExportText.append("\n").append("	ImGui::CreateContext(NULL);");
		//	ImGuiIO& io = ImGui::GetIO(); (void)io;
		SaveExportText.append("\n").append("	ImGuiIO& io = ImGui::GetIO(); (void)io;");
		if (!FontBuff.OutputUsingSeparateFontFiles && !FontBuff.font.empty())
		{
			SaveExportText.append("\n	io.Fonts->AddFontFromMemoryCompressedTTF(Font_data, Font_size, ").append(std::to_string(FontBuff.font_size)).append(", 0, io.Fonts->GetGlyphRangesChineseFull());");
		}
		else
		{
			if (FontBuff.font.empty())
			{
				SaveExportText.append("\n	ImFontConfig FontConfig;");
				SaveExportText.append("\n	FontConfig.SizePixels = ").append(std::to_string(FontBuff.font_size)).append(";");
				SaveExportText.append("\n	FontBuff = io.Fonts->AddFontDefault(&FontConfig);");
			}
			else if (FontBuff.OutputUsingSeparateFontFiles)
			{
				SaveExportText.append("\n").append("	io.Fonts->AddFontFromFileTTF(\"").append(FontBuff.FontFileName).append("\", ").append(std::to_string(FontBuff.font_size)).append(", NULL, io.Fonts->GetGlyphRangesChineseFull()); ");
			}
		}

		if (NeedDocking)
		{
			//	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
			SaveExportText.append("\n").append("	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;");
			//	io.ConfigFlags |= ImGuiViewportFlags_NoDecoration;
			SaveExportText.append("\n").append("	io.ConfigFlags |= ImGuiViewportFlags_NoDecoration;");
			//	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
			SaveExportText.append("\n").append("	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;");
			//	io.ConfigFlags |= ImGuiCol_DockingEmptyBg;
			SaveExportText.append("\n").append("	io.ConfigFlags |= ImGuiCol_DockingEmptyBg;");
		}
		//	ImGui::StyleColorsDark();
		SaveExportText.append("\n").append("	ImGui::StyleColorsDark();");
		//	ImGuiStyle& style = ImGui::GetStyle();
		SaveExportText.append("\n").append("	ImGuiStyle& style = ImGui::GetStyle();");
		//	ImVec4* colors = style.Colors;
		SaveExportText.append("\n").append("	ImVec4* colors = style.Colors;");
		SaveExportText.append("\n\n//Set Color Style\n");
		for (size_t i = 0; i < ImGuiCol_COUNT; i++)
		{
			SaveExportText.append("\n").append("	colors[ImGuiCol_").append(ImGui::GetStyleColorName(i)).append("] = ImVec4(").append(std::to_string(GUIStyle.Colors[i].x)).append(",").append(std::to_string(GUIStyle.Colors[i].y)).append(",").append(std::to_string(GUIStyle.Colors[i].z)).append(",").append(std::to_string(GUIStyle.Colors[i].w)).append(");");
		}

		SaveExportText.append("\n\n//Set Style\n");
		//	 style.WindowPadding                = ImVec2(_THV_,_THV_);
		SaveExportText.append("\n").append("	 style.WindowPadding                = ImVec2(").append(std::to_string(GUIStyle.WindowPadding.x)).append(",").append(std::to_string(GUIStyle.WindowPadding.y)).append(");");
		//	 style.WindowRounding               = _THV_;
		SaveExportText.append("\n").append("	 style.WindowRounding               = ").append(std::to_string(GUIStyle.WindowRounding)).append(";");
		//	 style.WindowBorderSize             = _THV_;
		SaveExportText.append("\n").append("	 style.WindowBorderSize             = ").append(std::to_string(GUIStyle.WindowBorderSize)).append(";");
		//	 style.WindowMinSize                = ImVec2(_THV_,_THV_);
		SaveExportText.append("\n").append("	 style.WindowMinSize                = ImVec2(").append(std::to_string(GUIStyle.WindowMinSize.x)).append(",").append(std::to_string(GUIStyle.WindowMinSize.y)).append(");");
		//	 style.WindowTitleAlign             = ImVec2(_THV_,_THV_);
		SaveExportText.append("\n").append("	 style.WindowTitleAlign             = ImVec2(").append(std::to_string(GUIStyle.WindowTitleAlign.x)).append(",").append(std::to_string(GUIStyle.WindowTitleAlign.y)).append(");");
		//	 style.WindowMenuButtonPosition     = _THV_;
		SaveExportText.append("\n").append("	 style.WindowMenuButtonPosition     = ").append(std::to_string(GUIStyle.WindowMenuButtonPosition /*Variable*/)).append(";");
		//	 style.ChildRounding                = _THV_;
		SaveExportText.append("\n").append("	 style.ChildRounding                = ").append(std::to_string(GUIStyle.ChildRounding /*Variable*/)).append(";");
		//	 style.ChildBorderSize              = _THV_;
		SaveExportText.append("\n").append("	 style.ChildBorderSize              = ").append(std::to_string(GUIStyle.ChildBorderSize /*Variable*/)).append(";");
		//	 style.PopupRounding                = _THV_;
		SaveExportText.append("\n").append("	 style.PopupRounding                = ").append(std::to_string(GUIStyle.PopupRounding /*Variable*/)).append(";");
		//	 style.PopupBorderSize              = _THV_;
		SaveExportText.append("\n").append("	 style.PopupBorderSize              = ").append(std::to_string(GUIStyle.PopupBorderSize /*Variable*/)).append(";");
		//	 style.FramePadding                 = ImVec2(_THV_,_THV_);
		SaveExportText.append("\n").append("	 style.FramePadding                 = ImVec2(").append(std::to_string(GUIStyle.FramePadding.x /*Variable*/)).append(",").append(std::to_string(GUIStyle.FramePadding.y /*Variable*/)).append(");");
		//	 style.FrameRounding                = _THV_;
		SaveExportText.append("\n").append("	 style.FrameRounding                = ").append(std::to_string(GUIStyle.FrameRounding /*Variable*/)).append(";");
		//	 style.FrameBorderSize              = _THV_;
		SaveExportText.append("\n").append("	 style.FrameBorderSize              = ").append(std::to_string(GUIStyle.FrameBorderSize /*Variable*/)).append(";");
		//	 style.ItemSpacing                  = ImVec2(_THV_,_THV_);
		SaveExportText.append("\n").append("	 style.ItemSpacing                  = ImVec2(").append(std::to_string(GUIStyle.ItemSpacing.x /*Variable*/)).append(",").append(std::to_string(GUIStyle.ItemSpacing.y /*Variable*/)).append(");");
		//	 style.ItemInnerSpacing             = ImVec2(_THV_,_THV_);
		SaveExportText.append("\n").append("	 style.ItemInnerSpacing             = ImVec2(").append(std::to_string(GUIStyle.ItemInnerSpacing.x /*Variable*/)).append(",").append(std::to_string(GUIStyle.ItemInnerSpacing.y /*Variable*/)).append(");");
		//	 style.CellPadding                  = ImVec2(_THV_,_THV_);
		SaveExportText.append("\n").append("	 style.CellPadding                  = ImVec2(").append(std::to_string(GUIStyle.CellPadding.x/*Variable*/)).append(",").append(std::to_string(GUIStyle.CellPadding.y/*Variable*/)).append(");");
		//	 style.TouchExtraPadding            = ImVec2(_THV_,_THV_);
		SaveExportText.append("\n").append("	 style.TouchExtraPadding            = ImVec2(").append(std::to_string(GUIStyle.TouchExtraPadding.x /*Variable*/)).append(",").append(std::to_string(GUIStyle.TouchExtraPadding.y /*Variable*/)).append(");");
		//	 style.IndentSpacing                = _THV_;
		SaveExportText.append("\n").append("	 style.IndentSpacing                = ").append(std::to_string(GUIStyle.IndentSpacing /*Variable*/)).append(";");
		//	 style.ColumnsMinSpacing            = _THV_;
		SaveExportText.append("\n").append("	 style.ColumnsMinSpacing            = ").append(std::to_string(GUIStyle.ColumnsMinSpacing /*Variable*/)).append(";");
		//	 style.ScrollbarSize                = _THV_;
		SaveExportText.append("\n").append("	 style.ScrollbarSize                = ").append(std::to_string(GUIStyle.ScrollbarSize /*Variable*/)).append(";");
		//	 style.ScrollbarRounding            = _THV_;
		SaveExportText.append("\n").append("	 style.ScrollbarRounding            = ").append(std::to_string(GUIStyle.ScrollbarRounding /*Variable*/)).append(";");
		//	 style.GrabMinSize                  = _THV_;
		SaveExportText.append("\n").append("	 style.GrabMinSize                  = ").append(std::to_string(GUIStyle.GrabMinSize/*Variable*/)).append(";");
		//	 style.GrabRounding                 = _THV_;
		SaveExportText.append("\n").append("	 style.GrabRounding                 = ").append(std::to_string(GUIStyle.GrabRounding /*Variable*/)).append(";");
		//	 style.LogSliderDeadzone            = _THV_
		SaveExportText.append("\n").append("	 style.LogSliderDeadzone            = ").append(std::to_string(GUIStyle.LogSliderDeadzone /*Variable*/)).append(";");
		//	 style.TabRounding                  = _THV_;
		SaveExportText.append("\n").append("	 style.TabRounding                  = ").append(std::to_string(GUIStyle.TabRounding /*Variable*/)).append(";");
		//	 style.TabBorderSize                = _THV_;
		SaveExportText.append("\n").append("	 style.TabBorderSize                = ").append(std::to_string(GUIStyle.TabBorderSize /*Variable*/)).append(";");
		//	 style.TabMinWidthForCloseButton    = _THV_;
		SaveExportText.append("\n").append("	 style.TabMinWidthForCloseButton    = ").append(std::to_string(GUIStyle.TabMinWidthForCloseButton /*Variable*/)).append(";");
		//	 style.ColorButtonPosition          = _THV_;
		SaveExportText.append("\n").append("	 style.ColorButtonPosition          = ").append(std::to_string(GUIStyle.ColorButtonPosition/*Variable*/)).append(";");
		//	 style.ButtonTextAlign              = ImVec2(_THV_,_THV_);
		SaveExportText.append("\n").append("	 style.ButtonTextAlign              = ImVec2(").append(std::to_string(GUIStyle.ButtonTextAlign.x /*Variable*/)).append(",").append(std::to_string(GUIStyle.ButtonTextAlign.y /*Variable*/)).append(");");
		//	 style.SelectableTextAlign          = ImVec2(_THV_,_THV_);
		SaveExportText.append("\n").append("	 style.SelectableTextAlign          = ImVec2(").append(std::to_string(GUIStyle.SelectableTextAlign.x /*Variable*/)).append(",").append(std::to_string(GUIStyle.SelectableTextAlign.y  /*Variable*/)).append(");");
		//	 style.DisplayWindowPadding         = ImVec2(_THV_,_THV_);
		SaveExportText.append("\n").append("	 style.DisplayWindowPadding         = ImVec2(").append(std::to_string(GUIStyle.DisplayWindowPadding.x /*Variable*/)).append(",").append(std::to_string(GUIStyle.DisplayWindowPadding.y  /*Variable*/)).append(");");
		//	 style.DisplaySafeAreaPadding       = ImVec2(_THV_,_THV_);
		SaveExportText.append("\n").append("	 style.DisplaySafeAreaPadding       = ImVec2(").append(std::to_string(GUIStyle.DisplaySafeAreaPadding.x /*Variable*/)).append(",").append(std::to_string(GUIStyle.DisplaySafeAreaPadding.y  /*Variable*/)).append(");");
		return SaveExportText;
	}

	void SpawnWindowCPP(std::string Path)
	{
		std::string SaveCode = "// Inculde\n";
		SaveCode.append(RootWindows->GetCod_Inculd());
		SaveCode.append("\n// Inculd HImGuiWindow");
		SaveCode.append("\n#include \"HImGuiWidget.h\"");
		//
		//LoadImageFunction
		//
		SaveCode.append("\n\nbool HLoadImage_CB(const unsigned char* imageData, ImTextureID & ImageBuffer, ImVec2 ImageSize)\n{");
		SaveCode.append(R"(
	int image_width = ImageSize.x;
	int image_height = ImageSize.y;

	if (imageData == NULL)
		return false;

	glGenTextures(1, reinterpret_cast<GLuint*>(&ImageBuffer));
	glBindTexture(GL_TEXTURE_2D, reinterpret_cast<GLuint>(ImageBuffer));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F); // Same

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	return true;
)");
		SaveCode.append("\n}");

		SaveCode.append("\n\n// Main");
		SaveCode.append("\nint main()\n{\n");
		SaveCode.append("\n	// SetHLoadImage CallBack");
		SaveCode.append("\n	HLoadImage = HLoadImage_CB;");
		SaveCode.append("\n	// Init Window\n");
		SaveCode.append(RootWindows->GetCod_InitWindows());
		SaveCode.append("\n	// CreateWindow\n");
		SaveCode.append(RootWindows->GetCod_CreateWindows());
		std::cout << "\n Test Export Create Window Function : " << RootWindows->GetCod_CreateWindows();
		//
		// Add Style
		SaveCode.append(GetExportStyle());
		//
		SaveCode.append("\n	// InitializeBeforeRendering");
		SaveCode.append(RootWindows->GetCod_InitializeBeforeRendering());

		SaveCode.append("\n	//Initialize ImGui Widget");
		SaveCode.append("\n	HImGui_Initialization();");

		SaveCode.append("\n	// Draw Loop\n");
		SaveCode.append("\n	while(").append(RootWindows->GetCod_WhetherToEnableRenderingLoop()).append(")\n	{\n	");
		SaveCode.append("\n		// FrameInit\n");
		SaveCode.append(RootWindows->GetCod_FrameInit());

		SaveCode.append("\n		//DrawImGui");
		SaveCode.append("\n		HImGui_GuiDraw();");

		SaveCode.append("\n		// FrameEnd");
		SaveCode.append(RootWindows->GetCod_FrameEnd());

		if (NeedDocking)
		{
			SaveCode.append("\n").append("		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)");
			//		{
			SaveCode.append("\n").append("		{");
			//			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			SaveCode.append("\n").append("			GLFWwindow* backup_current_context = glfwGetCurrentContext();");
			//			ImGui::UpdatePlatformWindows();
			SaveCode.append("\n").append("			ImGui::UpdatePlatformWindows();");
			//			ImGui::RenderPlatformWindowsDefault();
			SaveCode.append("\n").append("			ImGui::RenderPlatformWindowsDefault();");
			//			glfwMakeContextCurrent(backup_current_context);
			SaveCode.append("\n").append("			glfwMakeContextCurrent(backup_current_context);");
			//		}
			SaveCode.append("\n").append("		}");
		}

		SaveCode.append("\n	}\n}");

		std::ofstream file(Path.append("\\HImGui_Main.cpp"));
		file << SaveCode;
		file.close();
	}

	void SpawnImGuiH_FunctionH(HWidgetExport& CodeBuff, std::string Path)
	{
		std::string SaveCode = "// Inculde Widget Inculd";

		SaveCode.append("\n#include <imgui.h>");
		SaveCode.append("\n#include <vector>\n");
		SaveCode.append("\n//HLoadImage CallBack");
		SaveCode.append("\nbool(*HLoadImage)(const unsigned char* imageData, ImTextureID & ImageBuffer, ImVec2 ImageSize);\n");

		for (size_t i = 0; i < CodeBuff.Inculd.size(); i++)
		{
			SaveCode.append("\n");
			SaveCode.append(CodeBuff.Inculd.at(i));
		}

		if (!CodeBuff.Function.empty())
		{
			SaveCode.append("\n\n\n// Widget Function");
			for (size_t i = 0; i < CodeBuff.Function.size(); i++)
			{
				SaveCode.append("\n\n");
				SaveCode.append(*CodeBuff.Function.at(i));
			}
		}

		std::ofstream file(Path.append("\\HImGui_Widget_includeAndFunction.h"));
		file << SaveCode;
		file.close();
	}

	void SpawnImGuiH_VariableH(std::string Path)
	{
		std::string SaveCode = "\n#include \"HImGui_Widget_includeAndFunction.h\"";
		for (size_t i = 0; i < EVariable.size(); i++)
		{
			SaveCode.append("\n\n//").append(EVariable.at(i).Comment);
			SaveCode.append("\n").append(EVariable.at(i).VariableCode);
		}
		SaveCode.append("\n\n\n\n//--------------CacheVariable---------------------------------\n");
		for (size_t i = 0; i < ECacheVariable.size(); i++)
		{
			SaveCode.append("\n\n//").append(ECacheVariable.at(i).Comment);
			SaveCode.append("\n").append(ECacheVariable.at(i).VariableCode);
		}

		if (!FontBuff.OutputUsingSeparateFontFiles && !FontBuff.font.empty())
		{
			SaveCode.append("\n\n\n\n//--------------Font -  ").append(FontBuff.FontFileName);
			SaveCode.append("\n").append(FontBuff.binary_to_compressed_c());
		}

		std::ofstream file(Path.append("\\HImGui_Widget_Variable.h"));
		file << SaveCode;
		file.close();
	}

	namespace SpawnVSPorjectTool
	{
		void SpawnFilters(std::string Path, std::vector<std::string>& FileList)
		{
			std::string SaveExportText = "<?xml version=\"1.0\" encoding=\"utf-8\"?>";
			//<Project ToolsVersion="4.0" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
			SaveExportText.append("\n").append("<Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">");
			//  <ItemGroup>
			SaveExportText.append("\n").append("  <ItemGroup>");
			//    <Filter Include="SourceFile">
			SaveExportText.append("\n").append("    <Filter Include=\"SourceFile\">");
			//      <UniqueIdentifier>{4FC737F1-C7A5-4376-A066-2A32D752A2FF}</UniqueIdentifier>
			SaveExportText.append("\n").append("      <UniqueIdentifier>{4FC737F1-C7A5-4376-A066-2A32D752A2FF}</UniqueIdentifier>");
			//      <Extensions>cpp;c;cc;cxx;c++;cppm;ixx;def;odl;idl;hpj;bat;asm;asmx</Extensions>
			SaveExportText.append("\n").append("      <Extensions>cpp;c;cc;cxx;c++;cppm;ixx;def;odl;idl;hpj;bat;asm;asmx</Extensions>");
			//    </Filter>
			SaveExportText.append("\n").append("    </Filter>");
			//    <Filter Include="HeaderFile">
			SaveExportText.append("\n").append("    <Filter Include=\"HeaderFile\">");
			//      <UniqueIdentifier>{93995380-89BD-4b04-88EB-625FBE52EBFB}</UniqueIdentifier>
			SaveExportText.append("\n").append("      <UniqueIdentifier>{93995380-89BD-4b04-88EB-625FBE52EBFB}</UniqueIdentifier>");
			//      <Extensions>h;hh;hpp;hxx;h++;hm;inl;inc;ipp;xsd</Extensions>
			SaveExportText.append("\n").append("      <Extensions>h;hh;hpp;hxx;h++;hm;inl;inc;ipp;xsd</Extensions>");
			//    </Filter>
			SaveExportText.append("\n").append("    </Filter>");
			//    <Filter Include="ResourceFile">
			SaveExportText.append("\n").append("    <Filter Include=\"ResourceFile\">");
			//      <UniqueIdentifier>{67DA6AB6-F800-4c08-8B7A-83BB121AAD01}</UniqueIdentifier>
			SaveExportText.append("\n").append("      <UniqueIdentifier>{67DA6AB6-F800-4c08-8B7A-83BB121AAD01}</UniqueIdentifier>");
			//      <Extensions>rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav;mfcribbon-ms</Extensions>
			SaveExportText.append("\n").append("      <Extensions>rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe;resx;tiff;tif;png;wav;mfcribbon-ms</Extensions>");
			//    </Filter>
			SaveExportText.append("\n").append("    </Filter>");
			//    <Filter Include="ImGui">
			SaveExportText.append("\n").append("    <Filter Include=\"ImGui\">");
			//      <UniqueIdentifier>{0fea3374-feff-4304-b00e-347b4ef6e491}</UniqueIdentifier>
			SaveExportText.append("\n").append("      <UniqueIdentifier>{0fea3374-feff-4304-b00e-347b4ef6e491}</UniqueIdentifier>");
			//    </Filter>
			SaveExportText.append("\n").append("    </Filter>");
			//    <Filter Include="Main">
			SaveExportText.append("\n").append("    <Filter Include=\"Main\">");
			//      <UniqueIdentifier>{342f0269-87ea-4997-af1f-df935006f469}</UniqueIdentifier>
			SaveExportText.append("\n").append("      <UniqueIdentifier>{342f0269-87ea-4997-af1f-df935006f469}</UniqueIdentifier>");
			//    </Filter>
			SaveExportText.append("\n").append("    </Filter>");
			//  </ItemGroup>
			SaveExportText.append("\n").append("  </ItemGroup>");
			//  <ItemGroup>
			SaveExportText.append("\n").append("  <ItemGroup>");

			SaveExportText.append("\n").append("    <ClCompile Include=\"").append("HImGui_Main.cpp").append("\">");
			SaveExportText.append("\n").append("      <Filter>Main</Filter>");
			SaveExportText.append("\n").append("    </ClCompile>");

			for (size_t i = 0; i < FileList.size(); i++)
			{
				if (FileList.at(i).rfind(".h") < 100000)
				{
					SaveExportText.append("\n").append("    <ClCompile Include=\"").append(FileList.at(i)).append("\">");
					SaveExportText.append("\n").append("      <Filter>SourceFile</Filter>");
					SaveExportText.append("\n").append("    </ClCompile>");
				}
			}

			SaveExportText.append("\n").append("  </ItemGroup>");
			//  <ItemGroup>
			SaveExportText.append("\n").append("  <ItemGroup>");

			SaveExportText.append("\n").append("    <ClInclude Include=\"").append("HImGui_Widget_includeAndFunction.h").append("\">");
			SaveExportText.append("\n").append("      <Filter>Main</Filter>");
			SaveExportText.append("\n").append("    </ClInclude>");

			SaveExportText.append("\n").append("    <ClInclude Include=\"").append("HImGui_Widget_Variable.h").append("\">");
			SaveExportText.append("\n").append("      <Filter>Main</Filter>");
			SaveExportText.append("\n").append("    </ClInclude>");

			SaveExportText.append("\n").append("    <ClInclude Include=\"").append("HImGuiWidget.h").append("\">");
			SaveExportText.append("\n").append("      <Filter>Main</Filter>");
			SaveExportText.append("\n").append("    </ClInclude>");

			for (size_t i = 0; i < FileList.size(); i++)
			{
				if (FileList.at(i).rfind(".h") < 100000)
				{
					SaveExportText.append("\n").append("    <ClInclude Include=\"").append(FileList.at(i)).append("\">");
					SaveExportText.append("\n").append("      <Filter>HeaderFile</Filter>");
					SaveExportText.append("\n").append("    </ClInclude>");
				}
			}
			SaveExportText.append("\n").append("  </ItemGroup>");

			//</Project>
			SaveExportText.append("\n").append("</Project>");

			std::ofstream file(Path.append("\\").append(RootWindows->PorjectName).append(".vcxproj.filters"));
			file << SaveExportText;
			file.close();
		}

		std::string SpawnVCXPROJ_File(std::string IncludeDirectories, std::string LibraryDirectories, std::string LibFile, std::vector<std::string>& FileList)
		{
			std::string SaveExportText;
			//<?xml version="1.0" encoding="utf-8"?>
			SaveExportText.append("<?xml version=\"1.0\" encoding=\"utf-8\"?>");
			//<Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
			SaveExportText.append("\n").append("<Project DefaultTargets=\"Build\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">");
			//  <ItemGroup Label="ProjectConfigurations">
			SaveExportText.append("\n").append("  <ItemGroup Label=\"ProjectConfigurations\">");
			//    <ProjectConfiguration Include="Debug|x64">
			SaveExportText.append("\n").append("    <ProjectConfiguration Include=\"Debug|x64\">");
			//      <Configuration>Debug</Configuration>
			SaveExportText.append("\n").append("      <Configuration>Debug</Configuration>");
			//      <Platform>x64</Platform>
			SaveExportText.append("\n").append("      <Platform>x64</Platform>");
			//    </ProjectConfiguration>
			SaveExportText.append("\n").append("    </ProjectConfiguration>");
			//    <ProjectConfiguration Include="Release|x64">
			SaveExportText.append("\n").append("    <ProjectConfiguration Include=\"Release|x64\">");
			//      <Configuration>Release</Configuration>
			SaveExportText.append("\n").append("      <Configuration>Release</Configuration>");
			//      <Platform>x64</Platform>
			SaveExportText.append("\n").append("      <Platform>x64</Platform>");
			//    </ProjectConfiguration>
			SaveExportText.append("\n").append("    </ProjectConfiguration>");
			//  </ItemGroup>
			SaveExportText.append("\n").append("  </ItemGroup>");
			//  <PropertyGroup Label="Globals">
			SaveExportText.append("\n").append("  <PropertyGroup Label=\"Globals\">");
			//    <VCProjectVersion>16.0</VCProjectVersion>
			SaveExportText.append("\n").append("    <VCProjectVersion>16.0</VCProjectVersion>");
			//    <Keyword>Win32Proj</Keyword>
			SaveExportText.append("\n").append("    <Keyword>Win32Proj</Keyword>");
			//    <ProjectGuid>{1a116941-cc13-48a9-8a96-5d6fcdfb93bd}</ProjectGuid>
			SaveExportText.append("\n").append("    <ProjectGuid>{1a116941-cc13-48a9-8a96-5d6fcdfb93bd}</ProjectGuid>");
			//    <RootNamespace>MSNUILDTEST</RootNamespace>
			SaveExportText.append("\n").append("    <RootNamespace>").append(RootWindows->PorjectName).append("</RootNamespace>");
			//    <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>
			SaveExportText.append("\n").append("    <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>");
			//  </PropertyGroup>
			SaveExportText.append("\n").append("  </PropertyGroup>");
			//  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
			SaveExportText.append("\n").append("  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.Default.props\" />");
			//  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'" Label="Configuration">
			SaveExportText.append("\n").append("  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)' == 'Debug|x64'\" Label=\"Configuration\">");
			//    <ConfigurationType>Application</ConfigurationType>
			SaveExportText.append("\n").append("    <ConfigurationType>Application</ConfigurationType>");
			//    <UseDebugLibraries>true</UseDebugLibraries>
			SaveExportText.append("\n").append("    <UseDebugLibraries>true</UseDebugLibraries>");
			//    <PlatformToolset>v142</PlatformToolset>
			SaveExportText.append("\n").append("    <PlatformToolset>v142</PlatformToolset>");
			//    <CharacterSet>Unicode</CharacterSet>
			SaveExportText.append("\n").append("    <CharacterSet>Unicode</CharacterSet>");
			//  </PropertyGroup>
			SaveExportText.append("\n").append("  </PropertyGroup>");
			//  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'" Label="Configuration">
			SaveExportText.append("\n").append("  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)' == 'Release|x64'\" Label=\"Configuration\">");
			//    <ConfigurationType>Application</ConfigurationType>
			SaveExportText.append("\n").append("    <ConfigurationType>Application</ConfigurationType>");
			//    <UseDebugLibraries>false</UseDebugLibraries>
			SaveExportText.append("\n").append("    <UseDebugLibraries>false</UseDebugLibraries>");
			//    <PlatformToolset>v142</PlatformToolset>
			SaveExportText.append("\n").append("    <PlatformToolset>v142</PlatformToolset>");
			//    <WholeProgramOptimization>true</WholeProgramOptimization>
			SaveExportText.append("\n").append("    <WholeProgramOptimization>true</WholeProgramOptimization>");
			//    <CharacterSet>Unicode</CharacterSet>
			SaveExportText.append("\n").append("    <CharacterSet>Unicode</CharacterSet>");
			//  </PropertyGroup>
			SaveExportText.append("\n").append("  </PropertyGroup>");
			//  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.props" />
			SaveExportText.append("\n").append("  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.props\" />");
			//  <ImportGroup Label="ExtensionSettings">
			SaveExportText.append("\n").append("  <ImportGroup Label=\"ExtensionSettings\">");
			//  </ImportGroup>
			SaveExportText.append("\n").append("  </ImportGroup>");
			//  <ImportGroup Label="Shared">
			SaveExportText.append("\n").append("  <ImportGroup Label=\"Shared\">");
			//  </ImportGroup>
			SaveExportText.append("\n").append("  </ImportGroup>");
			//  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
			SaveExportText.append("\n").append("  <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)' == 'Debug|x64'\">");
			//    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
			SaveExportText.append("\n").append("    <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />");
			//  </ImportGroup>
			SaveExportText.append("\n").append("  </ImportGroup>");
			//  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
			SaveExportText.append("\n").append("  <ImportGroup Label=\"PropertySheets\" Condition=\"'$(Configuration)|$(Platform)' == 'Release|x64'\">");
			//    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
			SaveExportText.append("\n").append("    <Import Project=\"$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props\" Condition=\"exists('$(UserRootDir)\\Microsoft.Cpp.$(Platform).user.props')\" Label=\"LocalAppDataPlatform\" />");
			//  </ImportGroup>
			SaveExportText.append("\n").append("  </ImportGroup>");
			//  <PropertyGroup Label="UserMacros" />
			SaveExportText.append("\n").append("  <PropertyGroup Label=\"UserMacros\" />");
			//  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
			SaveExportText.append("\n").append("  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)' == 'Debug|x64'\">");
			//    <LinkIncremental>true</LinkIncremental>
			SaveExportText.append("\n").append("    <LinkIncremental>true</LinkIncremental>");
			//  </PropertyGroup>
			SaveExportText.append("\n").append("  </PropertyGroup>");
			//  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
			SaveExportText.append("\n").append("  <PropertyGroup Condition=\"'$(Configuration)|$(Platform)' == 'Release|x64'\">");
			//    <LinkIncremental>false</LinkIncremental>
			SaveExportText.append("\n").append("    <LinkIncremental>false</LinkIncremental>");
			//  </PropertyGroup>
			SaveExportText.append("\n").append("  </PropertyGroup>");
			//  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
			SaveExportText.append("\n").append("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)' == 'Debug|x64'\">");
			//    <ClCompile>
			SaveExportText.append("\n").append("    <ClCompile>");
			//      <WarningLevel>Level3</WarningLevel>
			SaveExportText.append("\n").append("      <WarningLevel>Level3</WarningLevel>");
			//      <SDLCheck>true</SDLCheck>
			SaveExportText.append("\n").append("      <SDLCheck>true</SDLCheck>");
			//      <PreprocessorDefinitions>_DEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
			SaveExportText.append("\n").append("      <PreprocessorDefinitions>_DEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>");
			//      <ConformanceMode>true</ConformanceMode>
			SaveExportText.append("\n").append("      <ConformanceMode>true</ConformanceMode>");
			//      <AdditionalIncludeDirectories>_HV_</AdditionalIncludeDirectories>
			SaveExportText.append("\n").append("      <AdditionalIncludeDirectories>").append(IncludeDirectories).append("</AdditionalIncludeDirectories>");
			//		<LanguageStandard>stdcpp17</LanguageStandard>
			SaveExportText.append("\n").append("		<LanguageStandard>").append(VSPorjectCPP).append("</LanguageStandard>");
			//    </ClCompile>
			SaveExportText.append("\n").append("    </ClCompile>");
			//    <Link>
			SaveExportText.append("\n").append("    <Link>");
			//      <SubSystem>Console</SubSystem>
			SaveExportText.append("\n").append("      <SubSystem>Console</SubSystem>");
			//      <GenerateDebugInformation>true</GenerateDebugInformation>
			SaveExportText.append("\n").append("      <GenerateDebugInformation>true</GenerateDebugInformation>");
			//      <AdditionalLibraryDirectories>_HV_</AdditionalLibraryDirectories>
			SaveExportText.append("\n").append("      <AdditionalLibraryDirectories>").append(LibraryDirectories).append("</AdditionalLibraryDirectories>");
			//      <AdditionalDependencies>_HV_;%(AdditionalDependencies)</AdditionalDependencies>
			SaveExportText.append("\n").append("      <AdditionalDependencies>").append(LibFile).append(";%(AdditionalDependencies)</AdditionalDependencies>");
			//    </Link>
			SaveExportText.append("\n").append("    </Link>");
			//  </ItemDefinitionGroup>
			SaveExportText.append("\n").append("  </ItemDefinitionGroup>");
			//  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
			SaveExportText.append("\n").append("  <ItemDefinitionGroup Condition=\"'$(Configuration)|$(Platform)' == 'Release|x64'\">");
			//    <ClCompile>
			SaveExportText.append("\n").append("    <ClCompile>");
			//      <WarningLevel>Level3</WarningLevel>
			SaveExportText.append("\n").append("      <WarningLevel>Level3</WarningLevel>");
			//      <FunctionLevelLinking>true</FunctionLevelLinking>
			SaveExportText.append("\n").append("      <FunctionLevelLinking>true</FunctionLevelLinking>");
			//      <IntrinsicFunctions>true</IntrinsicFunctions>
			SaveExportText.append("\n").append("      <IntrinsicFunctions>true</IntrinsicFunctions>");
			//      <SDLCheck>true</SDLCheck>
			SaveExportText.append("\n").append("      <SDLCheck>true</SDLCheck>");
			//      <PreprocessorDefinitions>NDEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
			SaveExportText.append("\n").append("      <PreprocessorDefinitions>NDEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>");
			//      <ConformanceMode>true</ConformanceMode>
			SaveExportText.append("\n").append("      <ConformanceMode>true</ConformanceMode>");
			//      <AdditionalIncludeDirectories>_HV_</AdditionalIncludeDirectories>
			SaveExportText.append("\n").append("      <AdditionalIncludeDirectories>").append(IncludeDirectories).append("</AdditionalIncludeDirectories>");
			//		<LanguageStandard>stdcpp17</LanguageStandard>
			SaveExportText.append("\n").append("		<LanguageStandard>").append(VSPorjectCPP).append("</LanguageStandard>");
			//    </ClCompile>
			SaveExportText.append("\n").append("    </ClCompile>");
			//    <Link>
			SaveExportText.append("\n").append("    <Link>");
			//      <SubSystem>Console</SubSystem>
			SaveExportText.append("\n").append("      <SubSystem>Console</SubSystem>");
			//      <EnableCOMDATFolding>true</EnableCOMDATFolding>
			SaveExportText.append("\n").append("      <EnableCOMDATFolding>true</EnableCOMDATFolding>");
			//      <OptimizeReferences>true</OptimizeReferences>
			SaveExportText.append("\n").append("      <OptimizeReferences>true</OptimizeReferences>");
			//      <GenerateDebugInformation>true</GenerateDebugInformation>
			SaveExportText.append("\n").append("      <GenerateDebugInformation>true</GenerateDebugInformation>");
			//      <AdditionalLibraryDirectories>_HV_</AdditionalLibraryDirectories>
			SaveExportText.append("\n").append("      <AdditionalLibraryDirectories>").append(LibraryDirectories).append("</AdditionalLibraryDirectories>");
			//      <AdditionalDependencies>_HV_;%(AdditionalDependencies)</AdditionalDependencies>
			SaveExportText.append("\n").append("      <AdditionalDependencies>").append(LibFile).append(";%(AdditionalDependencies)</AdditionalDependencies>");
			//    </Link>
			SaveExportText.append("\n").append("    </Link>");
			//  </ItemDefinitionGroup>
			SaveExportText.append("\n").append("  </ItemDefinitionGroup>");

			SaveExportText.append("\n").append("  <ItemGroup>");
			SaveExportText.append("\n").append("    <ClCompile Include=\"").append("HImGui_Main.cpp").append("\" />");

			for (size_t i = 0; i < FileList.size(); i++)
			{
				if (FileList.at(i).rfind(".cpp") < 100000)
					SaveExportText.append("\n").append("    <ClCompile Include=\"").append(FileList.at(i)).append("\" />");
				//SpawnCompileFile(FileList.at(i), true);
			}

			SaveExportText.append("\n").append("  </ItemGroup>");
			SaveExportText.append("\n").append("  <ItemGroup>");
			SaveExportText.append("\n").append("    <ClInclude Include=\"").append("HImGui_Widget_includeAndFunction.h").append("\" />");
			SaveExportText.append("\n").append("    <ClInclude Include=\"").append("HImGui_Widget_Variable.h").append("\" />");
			SaveExportText.append("\n").append("    <ClInclude Include=\"").append("HImGuiWidget.h").append("\" />");

			for (size_t i = 0; i < FileList.size(); i++)
			{
				if (FileList.at(i).rfind(".h") < 100000)
					SaveExportText.append("\n").append("    <ClInclude Include=\"").append(FileList.at(i)).append("\" />");
				//SpawnCompileFile(FileList.at(i), false);
			}

			SaveExportText.append("\n").append("  </ItemGroup>");

			//  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />
			SaveExportText.append("\n").append("  <Import Project=\"$(VCTargetsPath)\\Microsoft.Cpp.targets\" />");
			//  <ImportGroup Label="ExtensionTargets">
			SaveExportText.append("\n").append("  <ImportGroup Label=\"ExtensionTargets\">");
			//  </ImportGroup>
			SaveExportText.append("\n").append("  </ImportGroup>");
			//</Project>
			SaveExportText.append("\n").append("</Project>");
			return SaveExportText;
		}

		void SpawnSHL_File(std::string Path)
		{
			std::string SaveExportText;
			//Microsoft Visual Studio Solution File, Format Version 12.00
			SaveExportText.append("\n").append("Microsoft Visual Studio Solution File, Format Version 12.00");
			//# Visual Studio Version 16
			SaveExportText.append("\n").append("# Visual Studio Version 16");
			//VisualStudioVersion = 16.0.32106.194
			SaveExportText.append("\n").append("VisualStudioVersion = 16.0.32106.194");
			//MinimumVisualStudioVersion = 10.0.40219.1
			SaveExportText.append("\n").append("MinimumVisualStudioVersion = 10.0.40219.1");
			//Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "HImGui", "ExportPorject\HImGui.vcxproj", "{1A116941-CC13-48A9-8A96-5D6FCDFB93BD}"
			SaveExportText.append("\n").append("Project(\"{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}\") = \"").append(RootWindows->PorjectName).append("\", \"ExportPorject\\").append(RootWindows->PorjectName).append(".vcxproj\", \"{1A116941-CC13-48A9-8A96-5D6FCDFB93BD}\"");
			//EndProject
			SaveExportText.append("\n").append("EndProject");
			//Global
			SaveExportText.append("\n").append("Global");
			//	GlobalSection(SolutionConfigurationPlatforms) = preSolution
			SaveExportText.append("\n").append("	GlobalSection(SolutionConfigurationPlatforms) = preSolution");
			//		Debug|x64 = Debug|x64
			SaveExportText.append("\n").append("		Debug|x64 = Debug|x64");
			//		Release|x64 = Release|x64
			SaveExportText.append("\n").append("		Release|x64 = Release|x64");
			//	EndGlobalSection
			SaveExportText.append("\n").append("	EndGlobalSection");
			//	GlobalSection(ProjectConfigurationPlatforms) = postSolution
			SaveExportText.append("\n").append("	GlobalSection(ProjectConfigurationPlatforms) = postSolution");
			//		{1A116941-CC13-48A9-8A96-5D6FCDFB93BD}.Debug|x64.ActiveCfg = Debug|x64
			SaveExportText.append("\n").append("		{1A116941-CC13-48A9-8A96-5D6FCDFB93BD}.Debug|x64.ActiveCfg = Debug|x64");
			//		{1A116941-CC13-48A9-8A96-5D6FCDFB93BD}.Debug|x64.Build.0 = Debug|x64
			SaveExportText.append("\n").append("		{1A116941-CC13-48A9-8A96-5D6FCDFB93BD}.Debug|x64.Build.0 = Debug|x64");
			//		{1A116941-CC13-48A9-8A96-5D6FCDFB93BD}.Release|x64.ActiveCfg = Release|x64
			SaveExportText.append("\n").append("		{1A116941-CC13-48A9-8A96-5D6FCDFB93BD}.Release|x64.ActiveCfg = Release|x64");
			//		{1A116941-CC13-48A9-8A96-5D6FCDFB93BD}.Release|x64.Build.0 = Release|x64
			SaveExportText.append("\n").append("		{1A116941-CC13-48A9-8A96-5D6FCDFB93BD}.Release|x64.Build.0 = Release|x64");
			//	EndGlobalSection
			SaveExportText.append("\n").append("	EndGlobalSection");
			//	GlobalSection(SolutionProperties) = preSolution
			SaveExportText.append("\n").append("	GlobalSection(SolutionProperties) = preSolution");
			//		HideSolutionNode = FALSE
			SaveExportText.append("\n").append("		HideSolutionNode = FALSE");
			//	EndGlobalSection
			SaveExportText.append("\n").append("	EndGlobalSection");
			//	GlobalSection(ExtensibilityGlobals) = postSolution
			SaveExportText.append("\n").append("	GlobalSection(ExtensibilityGlobals) = postSolution");
			//		SolutionGuid = {2CD34E31-C368-4FA2-A1C5-522DAFA10FC3}
			SaveExportText.append("\n").append("		SolutionGuid = {2CD34E31-C368-4FA2-A1C5-522DAFA10FC3}");
			//	EndGlobalSection
			SaveExportText.append("\n").append("	EndGlobalSection");
			//EndGlobal
			SaveExportText.append("\n").append("EndGlobal");

			std::ofstream file(Path.append("\\").append(RootWindows->PorjectName).append(".sln"));
			file << SaveExportText;
			file.close();
		}

		void CopyBinFileToPath(std::string TargetPath)
		{
			std::vector<std::string> SavePath;
			getFileNames("DependentFile\\Bin", SavePath);
			for (size_t i = 0; i < SavePath.size(); i++)
			{
				std::string FileName = TargetPath;
				FileName = FileName.append(SavePath.at(i).substr(SavePath.at(i).rfind("\\"), 10000000));

				std::cout << "\n Out : " << FileName;

				try
				{
					HCopyFolder(SavePath.at(i), FileName);
				}
				catch (const std::filesystem::filesystem_error& e)
				{
					std::cout << "\n CopyBinFileToPath -> Error : " << e.what();
				}
			}

			for (size_t i = 0; i < HPluginInfo.size(); i++)
			{
				if (!HPluginInfo.at(i)["HaveBin"].is_null())
				{
					std::string Target = HPluginInfo.at(i)["Path"];
					Target = Target.substr(0, Target.rfind("\\") + 1);
					Target.append("Bin");

					getFileNames(Target, SavePath);
					for (size_t c = 0; c < SavePath.size(); c++)
					{
						std::string FileName = SavePath.at(c).substr(SavePath.at(c).rfind("\\") + 1, 10000000);

						try
						{
							HCopyFolder(SavePath.at(c), std::string(TargetPath).append(FileName));
						}
						catch (const std::filesystem::filesystem_error& e)
						{
						}
					}
				}
			}
		}
	}

	void SpawnVSPorject(std::string path, HWidgetExport& Buff)
	{
		try
		{
			HCopyFolder("DependentFile\\API\\", std::string(path).append("\\API\\"));
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cout << "\n ExportCode -> SpawnVSPorject -> HCopyFolder -> \"DependentFile\\API\\\" To  \"Target\\API\" -> Error : " << e.what();
		}

		for (size_t i = 0; i < HPluginInfo.size(); i++)
		{
			if (!HPluginInfo.at(i)["API_Folder"].is_null())
			{
				std::string PluginFolderName = HPluginInfo.at(i)["Path"];
				PluginFolderName = PluginFolderName.substr(0, PluginFolderName.rfind("\\"));
				PluginFolderName = PluginFolderName.substr(PluginFolderName.rfind("\\"), 100000);

				_mkdir(std::string(path).append("\\API").append(PluginFolderName).c_str());
				try
				{
					HCopyFolder(std::string("Plugin\\Widget").append(PluginFolderName).append("\\").append(HPluginInfo.at(i)["API_Folder"]), std::string(path).append("\\API").append(PluginFolderName).append("\\").append(HPluginInfo.at(i)["API_Folder"]));
				}
				catch (const std::filesystem::filesystem_error& e)
				{
					std::cout << "\n ExportCode -> SpawnVSPorject -> HCopyFolder -> PluginAPI To  \"Target\\API\\PluginName\" -> Error : " << e.what();
				}
			}
		}

		std::string InculdPathSave;

		for (size_t i = 0; i < Buff.InculdPath.size(); i++)
		{
			InculdPathSave.append(Buff.InculdPath.at(i)).append(";");
		}
		InculdPathSave.append(RootWindows->InculdPathList);

		std::string LibPath;

		for (size_t i = 0; i < Buff.LibPath.size(); i++)
		{
			LibPath.append(Buff.LibPath.at(i)).append(";");
		}
		LibPath.append(RootWindows->LibPath);

		std::string LibFile;
		for (size_t i = 0; i < Buff.Lib.size(); i++)
		{
			LibFile.append(Buff.Lib.at(i)).append(";");
		}
		LibFile.append(RootWindows->Lib);

		std::vector<std::string> Files = Buff.RequestCompileFile;

		for (size_t i = 0; i < RootWindows->CompileFiles.size(); i++)
		{
			Files.push_back(RootWindows->CompileFiles.at(i));
		}

		std::string SaveExportText = SpawnVSPorjectTool::SpawnVCXPROJ_File(InculdPathSave, LibPath, LibFile, Files);
		SpawnVSPorjectTool::SpawnFilters(path, Files);
		std::ofstream file(path.append("\\").append(RootWindows->PorjectName).append(".vcxproj"));
		file << SaveExportText;
		file.close();
	}

	HWidgetExport SpawnImGuiH(std::string Path)
	{
		std::string SaveCode, FunctionCodeBuffer;

		SaveCode.append("\n\n\n");
		SaveCode.append("// Draw ImGui Window And Widget");
		SaveCode.append("\nvoid HImGui_GuiDraw()\n{\n");
		HWidgetExport OutBuff;

		for (size_t i = 0; i < ImGuiWindows.size(); i++)
		{
			SaveCode.append("\n\n\n");
			HWidgetExport ExBuff = ImGuiWindows.at(i)->Export("	");
			SaveCode.append(ExBuff.ExportCode);

			bool buff_B;
			if (!ExBuff.Inculd.empty())
			{
				for (size_t i = 0; i < ExBuff.Inculd.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < OutBuff.Inculd.size(); q++)
					{
						if (OutBuff.Inculd.at(q) == ExBuff.Inculd.at(i))
						{
							buff_B = false;
							q = OutBuff.Inculd.size();
						}
					}
					if (buff_B)
						OutBuff.Inculd.push_back(ExBuff.Inculd.at(i));
				}
			}

			if (!ExBuff.Function.empty())
			{
				for (size_t i = 0; i < ExBuff.Function.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < OutBuff.Function.size(); q++)
					{
						if (OutBuff.Function.at(q) == ExBuff.Function.at(i))
						{
							buff_B = false;
							q = OutBuff.Function.size();
						}
					}
					if (buff_B)
						OutBuff.Function.push_back(ExBuff.Function.at(i));
				}
			}

			if (!ExBuff.RequestCompileFile.empty())
			{
				for (size_t i = 0; i < ExBuff.RequestCompileFile.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < OutBuff.RequestCompileFile.size(); q++)
					{
						if (OutBuff.RequestCompileFile.at(q) == ExBuff.RequestCompileFile.at(i))
						{
							buff_B = false;
							q = OutBuff.RequestCompileFile.size();
						}
					}
					if (buff_B)
						OutBuff.RequestCompileFile.push_back(ExBuff.RequestCompileFile.at(i));
				}
			}

			if (!ExBuff.Lib.empty())
			{
				for (size_t i = 0; i < ExBuff.Lib.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < OutBuff.Lib.size(); q++)
					{
						if (ExBuff.Lib.at(q) == ExBuff.Lib.at(i))
						{
							buff_B = false;
							q = OutBuff.Lib.size();
						}
					}
					if (buff_B)
						OutBuff.Lib.push_back(ExBuff.Lib.at(i));
				}
			}

			if (!ExBuff.LibPath.empty())
			{
				for (size_t i = 0; i < ExBuff.LibPath.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < OutBuff.LibPath.size(); q++)
					{
						if (ExBuff.LibPath.at(q) == ExBuff.LibPath.at(i))
						{
							buff_B = false;
							q = OutBuff.LibPath.size();
						}
					}
					if (buff_B)
						OutBuff.LibPath.push_back(ExBuff.LibPath.at(i));
				}
			}

			if (!ExBuff.InculdPath.empty())
			{
				for (size_t i = 0; i < ExBuff.InculdPath.size(); i++)
				{
					buff_B = true;
					for (size_t q = 0; q < OutBuff.InculdPath.size(); q++)
					{
						if (OutBuff.InculdPath.at(q) == ExBuff.InculdPath.at(i))
						{
							buff_B = false;
							q = OutBuff.InculdPath.size();
						}
					}
					if (buff_B)
						OutBuff.InculdPath.push_back(ExBuff.InculdPath.at(i));
				}
			}
		}

		SpawnImGuiH_FunctionH(OutBuff, Path);
		SpawnImGuiH_VariableH(Path);
		SaveCode.append("\n}");

		FunctionCodeBuffer.append("// Inculd  HImGui Widget Inculde And Function");
		FunctionCodeBuffer.append("\n#include \"HImGui_Widget_Variable.h\"");

		FunctionCodeBuffer.append("\n\n\n");
		FunctionCodeBuffer.append("// Initialization Widget");
		FunctionCodeBuffer.append("\nvoid HImGui_Initialization(){\n");
		for (size_t i = 0; i < InitializationCodes.size(); i++)
		{
			FunctionCodeBuffer.append("\n\n");
			FunctionCodeBuffer.append(InitializationCodes.at(i));
		}
		FunctionCodeBuffer.append("\n}");

		std::ofstream file(Path.append("\\HImGuiWidget.h"));
		file << FunctionCodeBuffer << SaveCode;
		file.close();
		return OutBuff;
	}

	void ExportVS2019PorjectCallBack(std::string Path)
	{
		std::string ExportDir = std::string(Path).append("\\HImGuiEdit_Export_VS2019Porject");
		_mkdir(ExportDir.c_str());
		SpawnVSPorjectTool::SpawnSHL_File(ExportDir);
		ExportDir = ExportDir.append("\\ExportPorject");
		_mkdir(ExportDir.c_str());
		SpawnVSPorjectTool::CopyBinFileToPath(ExportDir);
		std::string SaveTargetPath = std::string(Path).append("\\HImGuiEdit_Export_VS2019Porject");
		_mkdir(std::string(ExportDir).append("\\x64").c_str());
		_mkdir(std::string(ExportDir).append("\\x64\\Release").c_str());

		SaveTargetPath = SaveTargetPath.append("\\x64\\Release");
		SpawnVSPorjectTool::CopyBinFileToPath(SaveTargetPath);

		SpawnWindowCPP(ExportDir);
		HWidgetExport Buff = SpawnImGuiH(ExportDir);
		SpawnVSPorject(ExportDir, Buff);
	}

	void ExportSourceCode(std::string Path)
	{
		std::string ExportDir = std::string(Path).append("\\HImGuiEdit_Export_SourceCode");
		_mkdir(ExportDir.c_str());

		try
		{
			HCopyFolder("DependentFile\\API\\", std::string(Path).append("\\API\\"));
		}
		catch (const std::filesystem::filesystem_error& e)
		{
			std::cout << "\n ExportCode -> ExportSourceCode -> HCopyFolder -> \"DependentFile\\API\\\" To  \"Target\\API\" -> Error : " << e.what();
		}

		SpawnWindowCPP(ExportDir);
		HWidgetExport ep = SpawnImGuiH(ExportDir);
	}

	static bool CanOpenBrowser = false;
	void (*NextBrowserCallBack)(std::string Path);
}

namespace ExportMenuT
{
	static std::string ExportVisualStudioPorject = "Export VisualStudio Porject";
	static std::string OnlyExportSourceCode = "Only Export Source Code";
}
#define ExportMenuInit TranslateObject.push_back(&ExportMenuT::ExportVisualStudioPorject);\
TranslateObject.push_back(&ExportMenuT::OnlyExportSourceCode);\

static void DrawExportMenu()
{
	if (ImGui::BeginMenu(HT_Export))
	{
		if (ImGui::Selectable(ExportMenuT::ExportVisualStudioPorject.c_str()))
		{
			//ExportCodeNS::NextBrowserCallBack = ExportCodeNS::ExportVS2019PorjectCallBack;
			//ExportCodeNS::CanOpenBrowser = true;
			ifd::FileDialog::Instance().Open("ExportVS2019PorjectDialog", ExportMenuT::ExportVisualStudioPorject.c_str(), "");
		}

		if (ImGui::Selectable(ExportMenuT::OnlyExportSourceCode.c_str()))
		{
			//ExportCodeNS::NextBrowserCallBack = ExportCodeNS::ExportSourceCode;
			//ExportCodeNS::CanOpenBrowser = true;
			ifd::FileDialog::Instance().Open("OnlyExportSourceCode", ExportMenuT::OnlyExportSourceCode.c_str(), "");
		}

		ImGui::EndMenu();
	}
}

static void DrawExportBrowser()
{
	//if (ExportCodeNS::CanOpenBrowser)
	//{
	//	FileBrowser::OpenBrowser(ExportCodeNS::NextBrowserCallBack, true, "ExportCode");
	//	ExportCodeNS::CanOpenBrowser = false;
	//}
	//FileBrowser::DrawFileBrowser("ExportCode");

	if (ifd::FileDialog::Instance().IsDone("ExportVS2019PorjectDialog")) {
		if (ifd::FileDialog::Instance().HasResult()) {
			std::string res = ifd::FileDialog::Instance().GetResult().u8string();
			printf("Export[%s]\n", res.c_str());
			ExportCodeNS::ExportVS2019PorjectCallBack(res);
		}
		ifd::FileDialog::Instance().Close();
	}

	if (ifd::FileDialog::Instance().IsDone("OnlyExportSourceCode")) {
		if (ifd::FileDialog::Instance().HasResult()) {
			std::string res = ifd::FileDialog::Instance().GetResult().u8string();
			printf("Export[%s]\n", res.c_str());
			ExportCodeNS::ExportSourceCode(res);
		}
		ifd::FileDialog::Instance().Close();
	}
}