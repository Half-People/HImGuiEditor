#pragma once
#include "File.h"
#include "ControlPanel.h"
#include <vector>

static std::vector<std::string> HPluginList;
static std::vector<json> HPluginInfo;

namespace PluginType
{
	typedef json(_cdecl* GetPluginInfo)();
	typedef std::vector<HWidget*>(_cdecl* GetWidget)();
	typedef void(_cdecl* Init)(int* CurrentSequenFrame_, void** CurrentSequencer_, std::string(*GetWidgetName_)(HWidget* Widget), void (*TimeLineAddFrame_)(HWidget* Widget, HValue* Value), void (*WidgetRemoveTimeLine_)(HWidget* Widget), std::vector<HVariableExport>* EV, std::vector<HVariableExport>* ECV, std::vector<std::string>* initc, ImGuiContext* CT, HWidget** Select, EditMode* EdMode_, std::vector<HWidget*>** HImGuiWidnowsWidgetList_, std::vector<HWidget*>* WidgetList_);
	typedef void(_cdecl* UpdataNeoSequencerFunctions)(const ImVec4& (*GetStyleNeoSequencerColorVec4)(ImGuiNeoSequencerCol idx), ImGuiNeoSequencerStyle& (*GetNeoSequencerStyle)(), void (*PushNeoSequencerStyleColor)(ImGuiNeoSequencerCol idx, ImU32 col), void (*PopNeoSequencerStyleColor)(int count), bool (*BeginNeoSequencer)(const char* id, ImGui::FrameIndexType* frame, ImGui::FrameIndexType* startFrame, ImGui::FrameIndexType* endFrame, const ImVec2& size, ImGuiNeoSequencerFlags flags), void (*EndNeoSequencer)(), bool (*BeginNeoGroup)(const char* label, bool* open), void (*EndNeoGroup)(), bool (*BeginNeoTimeline)(const char* label, ImGui::FrameIndexType** keyframes, uint32_t keyframeCount, bool* open, ImGuiNeoTimelineFlags flags), void (*EndNeoTimeLine)(), bool (*BeginNeoTimelineEx)(const char* label, bool* open, ImGuiNeoTimelineFlags flags), void (*NeoKeyframe)(int32_t* value), bool (*IsNeoKeyframeHovered)(), bool (*IsNeoKeyframeSelected)(), bool (*IsNeoKeyframeRightClicked)(), void (*NeoClearSelection)(), bool (*NeoIsSelecting)(), bool (*NeoHasSelection)(), bool (*NeoIsDraggingSelection)(), bool (*NeoCanDeleteSelection)(), bool (*IsNeoKeyframeSelectionRightClicked)(), uint32_t(*GetNeoKeyframeSelectionSize)(), void (*GetNeoKeyframeSelection)(ImGui::FrameIndexType* selection), void (*SetSelectedTimeline)(const char* timelineLabel), bool (*IsNeoTimelineSelected)(ImGuiNeoTimelineIsSelectedFlags flags));
}

#if _WIN32
#include <Windows.h>
static std::vector<HINSTANCE> PluginModuleBuff;
static void AddWidgetformPlugin(std::string Path)
{
	HINSTANCE module = LoadLibraryA(Path.c_str());
	if (!module)
	{
		FreeLibrary(module);
		return;
	}
	PluginType::GetWidget Fu = (PluginType::GetWidget)GetProcAddress(module, "GetWidget");
	PluginType::Init InitFu = (PluginType::Init)GetProcAddress(module, "InitHPlugin");//UpdataNeoSequencerFunction
	PluginType::UpdataNeoSequencerFunctions UpdataNeoSequencerFunctionsFu = (PluginType::UpdataNeoSequencerFunctions)GetProcAddress(module, "UpdataNeoSequencerFunction");
	if ((!Fu) || (!InitFu))
	{
		FreeLibrary(module);
		return;
	}
	else
	{
		if (UpdataNeoSequencerFunctionsFu)
		{
			(*UpdataNeoSequencerFunctionsFu)(&ImGui::GetStyleNeoSequencerColorVec4,
				&ImGui::GetNeoSequencerStyle,
				&ImGui::PushNeoSequencerStyleColor,
				&ImGui::PopNeoSequencerStyleColor,
				&ImGui::BeginNeoSequencer,
				&ImGui::EndNeoSequencer,
				&ImGui::BeginNeoGroup,
				&ImGui::EndNeoGroup,
				&ImGui::BeginNeoTimeline,
				&ImGui::EndNeoTimeLine,
				&ImGui::BeginNeoTimelineEx,
				&ImGui::NeoKeyframe,
				&ImGui::IsNeoKeyframeHovered,
				&ImGui::IsNeoKeyframeSelected,
				&ImGui::IsNeoKeyframeRightClicked,
				&ImGui::NeoClearSelection,
				&ImGui::NeoIsSelecting,
				&ImGui::NeoHasSelection,
				&ImGui::NeoIsDraggingSelection,
				&ImGui::NeoCanDeleteSelection,
				&ImGui::IsNeoKeyframeSelectionRightClicked,
				&ImGui::GetNeoKeyframeSelectionSize,
				&ImGui::GetNeoKeyframeSelection,
				&ImGui::SetSelectedTimeline,
				&ImGui::IsNeoTimelineSelected);
		}
		else
			std::cout << "\nThe plug-in is outdated and lacks the timeline but does not affect its use";

		(*InitFu)(&HAnimation::CurrentSequenFrame,&HAnimation::CurrentSequencer,&GetWidgetName_CallBack,&TimeLineAddFrame_CallBack,&WidgetRemoveTimeLine_CallBack,&EVariable,&ECacheVariable,&InitializationCodes,GImGui, &SelectWidget, &EdMode, &HImGuiWidnowsWidgetList, &WidgetList);
		std::vector<HWidget*> Buff = (*Fu)();

		std::string PluginFolderName = Path.substr(0, Path.rfind("\\"));
		PluginFolderName = PluginFolderName.substr(PluginFolderName.rfind("\\"), 100000);
		for (size_t i = 0; i < Buff.size(); i++)
		{
			if (Buff.at(i)->InculdPath)
			{
				*Buff.at(i)->InculdPath = std::string("API\\").append(PluginFolderName).append("\\").append(*Buff.at(i)->InculdPath);
			}
			if (Buff.at(i)->RequestCompileFile)
			{
				for (size_t q = 0; q < Buff.at(i)->RequestCompileFile->size(); q++)
				{
					Buff.at(i)->RequestCompileFile->at(q) = std::string("API\\").append(PluginFolderName).append("\\").append(Buff.at(i)->RequestCompileFile->at(q));
				}
			}
			if (Buff.at(i)->LibPath)
			{
				*Buff.at(i)->LibPath = std::string("API\\").append(PluginFolderName).append("\\").append(*Buff.at(i)->LibPath);
			}

			WidgetList.push_back(Buff.at(i));
		}
		PluginModuleBuff.push_back(module);
		//FreeLibrary(module);
		return;
	}
}
static json GetPluginInfo(std::string Path)
{
	HINSTANCE module = LoadLibraryA(Path.c_str());
	if (!module)
	{
		FreeLibrary(module);
		std::cout << "\n HPlugin -> GetPluginInfo -> LoadLibrary -> WARN -> Module == NULL";
		return json();
	}
	PluginType::GetPluginInfo Fu = (PluginType::GetPluginInfo)GetProcAddress(module, "GetPluginInfo");
	if (!Fu)
	{
		FreeLibrary(module);
		std::cout << "\n HPlugin -> GetPluginInfo -> GetProcAddress -> WARN -> Function == NULL";
		return json();
	}
	else
	{
		json Buff = (*Fu)();
		FreeLibrary(module);
		std::cout << "\n HPlugin -> GetPluginInfo -> GetProcAddress -> Info : Load PluginInfo";
		return Buff;
	}
}

#endif // _WIN32

static void LoadWidgetPlugin()
{
	std::vector<std::string> PathBuff;
	getFileNames("Plugin\\Widget", PathBuff);

	std::vector<std::string>Buff;
	for (size_t i = 0; i < PathBuff.size(); i++)
	{
		getFileNames(PathBuff.at(i), Buff);

		int DllPos = -1;
		bool HaveBin = false;

		for (size_t c = 0; c < Buff.size(); c++)
		{
			if (Buff.at(c).find(".dll") < 100000000)
			{
				DllPos = c;
			}
			else if (Buff.at(c) == "Bin")
			{
				HaveBin = true;
			}
		}

		if (DllPos != -1)
		{
			json JBuff = GetPluginInfo(Buff.at(DllPos));
			if (!JBuff["PluginName"].is_null())
			{
				JBuff["Path"] = Buff.at(DllPos);
				JBuff["HaveBin"] = HaveBin;
				HPluginInfo.push_back(JBuff);
				AddWidgetformPlugin(Buff.at(DllPos));
			}
		}
	}
}
