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
	typedef void(_cdecl* Init)(ImGuiContext* CT, HWidget** Select, EditMode* EdMode_, std::vector<HWidget*>** HImGuiWidnowsWidgetList_, std::vector<HWidget*>* WidgetList_);
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
	PluginType::Init InitFu = (PluginType::Init)GetProcAddress(module, "InitHPlugin");
	if ((!Fu) || (!InitFu))
	{
		FreeLibrary(module);
		return;
	}
	else
	{
		(*InitFu)(GImGui, &SelectWidget, &EdMode, &HImGuiWidnowsWidgetList, &WidgetList);
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
