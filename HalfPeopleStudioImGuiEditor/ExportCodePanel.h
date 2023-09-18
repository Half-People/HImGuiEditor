#pragma once
#include <imgui.h>
#include "ImGuiColorTextEdit/TextEditor.h"
#include "HImGuiWindows.h"
#include "HWindows.h"
static TextEditor* ExportCode;
static bool HaveExportHWindowCode = false;
static void InitexportCode()
{
	ExportCode = new TextEditor;
	ExportCode->SetHandleKeyboardInputs(false);
}

static void DrawExportCode()
{
	if (ImGui::Begin("ExportCodePanel"))
	{
		if (ImGui::Button("Updata"))
		{
			std::string SaveCode;
			if (HaveExportHWindowCode)
			{
				HWidgetExport ExBuff = ImGuiWindows.at(SelectHImGuiWindows)->Export("		");

				SaveCode = "// Inculde\n";
				SaveCode.append(RootWindows->GetCod_Inculd());

				for (size_t i = 0; i < ExBuff.Inculd.size(); i++)
				{
					SaveCode.append("\n");
					SaveCode.append(ExBuff.Inculd.at(i));
				}

				if (!ExBuff.Function.empty())
				{
					SaveCode.append("\n// Function");
					for (size_t i = 0; i < ExBuff.Function.size(); i++)
					{
						SaveCode.append("\n\n");
						SaveCode.append(*ExBuff.Function.at(i));
					}
				}

				SaveCode.append("\nint main()\n{\n");
				SaveCode.append("\n	// Init Window\n");
				SaveCode.append(RootWindows->GetCod_InitWindows());
				SaveCode.append("\n	// CreateWindow\n");
				SaveCode.append(RootWindows->GetCod_CreateWindows());
				//
				// Add Style
				//
				SaveCode.append("\n	// InitializeBeforeRendering");
				SaveCode.append(RootWindows->GetCod_InitializeBeforeRendering());
				SaveCode.append("\n	// Draw Loop\n");
				SaveCode.append("\n	while(").append(RootWindows->GetCod_WhetherToEnableRenderingLoop()).append(")\n	{\n	");
				SaveCode.append("\n		// FrameInit\n");
				SaveCode.append(RootWindows->GetCod_FrameInit());

				SaveCode.append(ExBuff.ExportCode);
			}
			else
			{
				HWidgetExport ExBuff = ImGuiWindows.at(SelectHImGuiWindows)->Export("");
				SaveCode.append("// Inculd");
				for (size_t i = 0; i < ExBuff.Inculd.size(); i++)
				{
					SaveCode.append("\n");
					SaveCode.append(ExBuff.Inculd.at(i));
				}

				if (!ExBuff.Function.empty())
				{
					SaveCode.append("\n// Function");
					for (size_t i = 0; i < ExBuff.Function.size(); i++)
					{
						SaveCode.append("\n\n");
						SaveCode.append(*ExBuff.Function.at(i));
					}
				}

				SaveCode.append(ExBuff.ExportCode);
			}

			if (HaveExportHWindowCode)
			{
				SaveCode.append("\n		// FrameEnd");
				SaveCode.append(RootWindows->GetCod_FrameEnd());
				SaveCode.append("\n	}\n}");
			}

			ExportCode->SetText(SaveCode);
		}
		ImGui::SameLine();
		ImGui::Checkbox("HaveExportWindowCode", &HaveExportHWindowCode);

		ExportCode->Render("ExportCode", ImVec2(), true);
	}
	ImGui::End();
}