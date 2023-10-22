#pragma once
#include <vector>
#include <nlohmann/json.hpp>
#include "imgui_neo_sequencer.h"
#include <iostream>
#include <string>
#include <sstream>

static std::string GetRandText(int srand_, int Long = 5)
{
	srand(srand_);
	static const char Buff[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	std::string tmp_s;
	tmp_s.reserve(Long);
	for (size_t i = 0; i < Long; i++)
	{
		tmp_s += Buff[rand() % (sizeof(Buff) - 1)];
	}
	return tmp_s;
}
class HWidget;
class HValue;
namespace HAnimation
{
	//CallBack
	static void (*WidgetRemoveTimeLine)(HWidget* Widget);
	static void (*TimeLineAddFrame)(HWidget* Widget, HValue* Value);
	static std::string(*GetWidgetName)(HWidget* Widget);

	static void* CurrentSequencer = 0;

	//Interpolation Tool
	static float SimpleBezierInterpolation(float p0, float p3, float t)
	{
		float u = 1.0f - t;
		float tt = t * t;
		float uu = u * u;
		float uuu = uu * u;
		float ttt = tt * t;

		float p = uuu * p0 + ttt * p3;
		return p;
	}
	static float LinearInterpolation(float a, float b, float t)
	{
		return a + (b - a) * t;
	}
	static int CurrentSequenFrame = 0;
	static enum KeyFlag
	{
		KeyFlag_None,
		KeyFlag_LinearInterpolation,
		KeyFlag_SimpleBezierInterpolation
	};

	struct InterpolationInfo
	{
		size_t PreviousKey = 0;
		size_t LastOneKey = 0;
		float alpha = 0;
	};
	namespace CodeExportTool
	{
		static std::string DataSwitching(std::vector<int>& keys, std::vector<void*>& datas, HValue* value, HWidget* Widget);
		namespace Interpolation
		{
			static std::string DataInterpolation(std::string VariableType,std::vector<int>& key, std::vector<void*>& datas, HValue* value, HWidget* Widget);
			//IsKey : false = get datas , true = get keys
			static std::string GetVectorName(HValue* value, HWidget* Widget, bool IsKeys);
			static enum HInfoDataFlage_
			{
				HInfoDataFlage_PreviousKey,
				HInfoDataFlage_LastOneKey,
				HInfoDataFlage_alpha
			};
			static std::string GetInfoData(HValue* value, HWidget* Widget, HInfoDataFlage_ flag);
			static std::string GetLinearInterpolationCode(std::string ValueUse, HValue* value, HWidget* Widget)
			{
				std::string ExportBuffer;
				ExportBuffer += "LinearInterpolation( ";
				ExportBuffer += GetVectorName(value, Widget, false);
				ExportBuffer += "[";
				ExportBuffer += GetInfoData(value, Widget, HInfoDataFlage_PreviousKey);
				ExportBuffer += "]";
				ExportBuffer += ValueUse;
				ExportBuffer += " , ";
				ExportBuffer += GetVectorName(value, Widget, false);
				ExportBuffer += "[";
				ExportBuffer += GetInfoData(value, Widget, HInfoDataFlage_LastOneKey);
				ExportBuffer += "]";
				ExportBuffer += ValueUse;
				ExportBuffer += " , ";
				ExportBuffer += GetInfoData(value, Widget, HInfoDataFlage_alpha);
				ExportBuffer += " );";
				return ExportBuffer;
			}
			static std::string GetSimpleBezierInterpolationCode(std::string ValueUse, HValue* value, HWidget* Widget)
			{
				std::string ExportBuffer;
				ExportBuffer += "SimpleBezierInterpolation( ";
				ExportBuffer += GetVectorName(value, Widget, false);
				ExportBuffer += "[";
				ExportBuffer += GetInfoData(value, Widget, HInfoDataFlage_PreviousKey);
				ExportBuffer += "]";
				ExportBuffer += ValueUse;
				ExportBuffer += " , ";
				ExportBuffer += GetVectorName(value, Widget, false);
				ExportBuffer += "[";
				ExportBuffer += GetInfoData(value, Widget, HInfoDataFlage_LastOneKey);
				ExportBuffer += "]";
				ExportBuffer += ValueUse;
				ExportBuffer += " , ";
				ExportBuffer += GetInfoData(value, Widget, HInfoDataFlage_alpha);
				ExportBuffer += " );";
				return ExportBuffer;
			}
		}


		// this code by GPT-4
		//I don’t want to write it because it’s too simple. ;)
		static void sortKeysAndValues(std::vector<int>& keys, std::vector<void*>& values) {
			std::vector<std::pair<int, void*>> pairs;

			// 將鍵和值組成一對並存儲在 pairs 中
			for (size_t i = 0; i < keys.size(); ++i) {
				pairs.emplace_back(keys[i], values[i]);
			}

			// 根據鍵進行排序
			std::sort(pairs.begin(), pairs.end(), [](const auto& a, const auto& b) {
				return a.first < b.first;
			});

			// 將排序後的鍵和值存回原始的鍵和值變量
			for (size_t i = 0; i < pairs.size(); ++i) {
				keys[i] = pairs[i].first;
				values[i] = pairs[i].second;
			}
		}

		static std::string InterpolationToolFunction()
		{
			return R"(//HInterpolation Tool
static float SimpleBezierInterpolation(float p0, float p3, float t)
{
	float u = 1.0f - t;
	float tt = t * t;
	float uu = u * u;
	float uuu = uu * u;
	float ttt = tt * t;

	float p = uuu * p0 + ttt * p3;
	return p;
}
static float LinearInterpolation(float a, float b, float t)
{
	return a + (b - a) * t;
}
struct H_InterpolationInfo
{
	size_t PreviousKey = 0;
	size_t LastOneKey = 0;
	float alpha = 0;
};
H_InterpolationInfo H_GetInterpolationInfoFromKeys(const std::vector<int> keys, int Frame)
{
	H_InterpolationInfo info;

	// Binary search finds the closest key
	auto upper = std::upper_bound(keys.begin(), keys.end(), Frame);
	info.LastOneKey = std::distance(keys.begin(), upper);
	info.PreviousKey = info.LastOneKey - 1;

	if (info.LastOneKey < keys.size() && info.PreviousKey >= 0) {
		int32_t max = keys[info.LastOneKey];
		int32_t min = keys[info.PreviousKey];

		if (max != min) {
			info.alpha = static_cast<float>(Frame - min) / (max - min);
		}
	}
	return info;
}


class HAnimationPlayer
{
public:
	void Play(void (*Animation)(int32_t Frame), size_t StartFram, size_t EndFrame, int FramePerSeconds, bool IsLoop)
	{
		Loop = IsLoop;
		PlayingAnimation = Animation;
		S_Fram = StartFram;
		E_Fram = EndFrame;
		FPS = FramePerSeconds;
		CurrentFrame = StartFram;
		DeltaTimeCalculateBuffer = 0;
	}

	void Stop()
	{
		PlayingAnimation = 0;
		Loop = false;
		DeltaTimeCalculateBuffer = 0;
		CurrentFrame = 0;
	}

	bool IsPlaying()
	{
		return PlayingAnimation;
	}

	//This function has been automatically called.
	void updata(float DeltaTime)
	{
		if (!PlayingAnimation)
			return;
		if (DeltaTimeCalculateBuffer >= 1.f / FPS)
		{
			DeltaTimeCalculateBuffer = 0;
			CurrentFrame++;
			if (CurrentFrame > E_Fram)
				if (Loop)
					CurrentFrame = S_Fram;
				else
					Stop();
			if(PlayingAnimation)
				PlayingAnimation(CurrentFrame);
		}
		else
		{
			DeltaTimeCalculateBuffer += DeltaTime;
		}
	}
private:
	void (*PlayingAnimation)(int32_t Frame);
	bool Loop;
	size_t S_Fram, E_Fram, CurrentFrame;
	int FPS;
	float DeltaTimeCalculateBuffer;
};
HAnimationPlayer AnimationPlayer;
)";
		}
	}
}

using namespace nlohmann;

struct HVariableExport
{
	std::string VariableCode;
	std::string Comment;
};

class HValue
{
public:
	const char* Name_;
	const bool CanAddToTimeLine = true;
	bool HaveFlagMode = false;
	bool ExposedAsVariable;
	bool CanExposedAsVariable;
	bool ExporsedVariableToDefault = true;
	//clear value data
	~HValue()
	{
		if (Data)
		{
			delete Data;
			Data = 0;
		}
	}
	//new self
	virtual HValue* CreateSelf(const char* Name) {
		std::cout << "\n HValue - > Error -> pls add \n\"" << R"(	virtual HWidgetValue* CreateSelf(const char* Name) {
		std::cout << "\n HValue - > Error -> pls add "
		return new /*Your Class*/;
	};)" << "\n in your HValue class";
		return new HValue;
	};
	//get this value the type
	virtual std::string GetType() {
		return	"--";
	};
	//using this draw widget in your HWidget
	virtual void Draw(const char* label, HWidget* Widget/*this*/)
	{
		if (CanExposedAsVariable)
		{
			ImGui::Checkbox(std::string("###exposed as variable").append(std::to_string((int)this)).c_str(), &ExposedAsVariable);
			if (ImGui::IsItemHovered())
			{
				if (ImGui::BeginTooltip())
				{
					ImGui::Text("exposed as variable");
					ImGui::EndTooltip();
				}
			}
			ImGui::SameLine();
		}

		DrawWidgetCallBack(label);
		if (CanAddToTimeLine && HAnimation::CurrentSequencer && ExposedAsVariable)
		{
			ImGui::SameLine();
			if (ImGui::Button(std::string(" + ###AddToTimeLine").append(std::to_string((int)this)).c_str()))
			{
				HAnimation::TimeLineAddFrame(Widget, this);
				std::cout << "\n Add Frame Button Down";
				if (HAnimation::TimeLineAddFrame == 0)
				{
					std::cout << "\n HValue-> Draw-> Error -> HAnimation::TimeLineAddFrame Function is : Null";
				}
			}
		}
	}
	//pls dont use this function to draw your widget.
	//use "void Draw(const char* label)"
	virtual void DrawWidgetCallBack(const char* label)
	{
		ImGui::Text("pls add \"virtual void DrawWidgetCallBack()\n{\n	/*your widget*/\n}\"  in your HValue class");
	}
	//timeline updata the value while use this function call back data.
	//pls use datas and keys to updata your HValue the Data
	virtual void TimeLineUpdataValueCallBack(std::vector<void*> datas, std::vector<int>keys, HAnimation::KeyFlag flag)
	{
		std::cout << "\n pls add \"virtual void TimeLineUpdataValueCallBack(std::vector<std::vector<void*>> datas, std::vector<std::vector<int>>keys, std::vector<HAnimation::KeyFlag> flag)\" this function in your HValue class .to updata timeline value call back";
	}
	//Export Current Value To string
	virtual std::string GetValue(void* TargetData)
	{
		std::cout << "\n pls add \"virtual std::string GetValue()\" this function in your HValue class .to updata get the export value data string";
		return std::string();
	}
	//Export Variable create code (internal use)
	virtual HVariableExport GetVariableExport(HWidget* Widget, bool InitVariable = true, bool UseStatic = true)
	{
		std::cout << "\n pls add \"virtual HVariableExport GetVariableExport(std::string VariableName, bool InitVariable = true, bool UseStatic = true)\" this function in your HValue class .to export your variable \n e.g." << R"(
			//Example code :
			HVariableExport ExportBuffer;
			ExportBuffer.Comment = "--NULL--";
			ExportBuffer.VariableCode = std::string("\n	"/*\n <-This have a TAB*/);
			if (UseStatic)
				ExportBuffer.VariableCode.append("static ");
			ExportBuffer.VariableCode.append("void");//<-----your value type
			ExportBuffer.VariableCode.append(" ").append(GetVariableName(Widget));
			if (InitVariable && InitData)
				ExportBuffer.VariableCode.append(" = ").append(GetValue(Data));
			ExportBuffer.VariableCode.append(";");
			return ExportBuffer;)";
		//Example code :
		HVariableExport ExportBuffer;
		ExportBuffer.Comment = "--NULL--";
		ExportBuffer.VariableCode = std::string("\n	"/*\n <-This have a TAB*/);
		if (UseStatic)
			ExportBuffer.VariableCode.append("static ");
		ExportBuffer.VariableCode.append("void");//<-----your value type
		ExportBuffer.VariableCode.append(" ").append(GetVariableName(Widget));
		if (InitVariable && InitData)
			ExportBuffer.VariableCode.append(" = ").append(GetValue(Data));
		ExportBuffer.VariableCode.append(";");
		return ExportBuffer;
	}
	//This function will automatically output the variable name or value, which will be affected by whether the output is used as a variable.
	std::string AutoGetOutputValue(HWidget*widget)
	{
		if (ExposedAsVariable)
		{
			return GetVariableName(widget);
		}
		else
		{
			return GetValue(Data);
		}
	}
	//SaveValue
	virtual json Save()
	{
		std::cout << "\n pls add \"virtual json Save()\" this function in your HValue class .to save your value";
		return json();
	}
	//SaveData
	virtual json OnlySaveData(void* data)
	{
		std::cout << "\n pls add \"virtual json OnlySaveData()\" this function in your HValue class .to save your value at TimeList";
		return json();
	}
	//LoadData
	virtual void* OnlyLoadData(json J)
	{
		std::cout << "\n pls add \"virtual json OnlySaveData()\" this function in your HValue class .to load your value at TimeList";
		return 0;
	}
	//LoadValue
	virtual void Load(json J)
	{
		std::cout << "\n pls add \"virtual void Load(json J)\" this function in your HValue class .to load your value";
	}
	//DrawTimeLine
	virtual void TimeLineDrawKey_CallBack(std::vector<int>& keys, std::vector<void*>& datas, HAnimation::KeyFlag& flag, bool& Open)
	{
		if (!keys.empty() || !datas.empty())
			if (ImGui::BeginNeoTimelineEx(std::string(Name_).append("###").append(std::to_string((int)this)).c_str()))
			{
				for (auto&& v : keys)
				{
					ImGui::NeoKeyframe(&v);

					if (ImGui::IsNeoKeyframeHovered() && ImGui::IsNeoKeyframeSelected() && ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Delete))
					{
						for (size_t i = 0; i < keys.size(); i++)
						{
							if (keys[i] == v)
							{
								keys.erase(keys.begin() + i);
								datas.erase(datas.begin() + i);
								i = keys.size();
							}
						}
					}
				}

				if (ImGui::IsNeoTimelineSelected() && ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Delete))
				{
					keys.clear();
					datas.clear();// << Having memory is risky
				}

				if (HaveFlagMode)
				{
					if (ImGui::IsNeoTimelineSelected())
					{
						if (ImGui::IsMouseClicked(ImGuiMouseButton_::ImGuiMouseButton_Right))
						{
							ImGui::OpenPopup(std::string("SelectTimeLineMode").append(std::to_string((int)this)).c_str());
						}

						if (ImGui::BeginPopupContextWindow(std::string("SelectTimeLineMode").append(std::to_string((int)this)).c_str()))
						{
							if (ImGui::Selectable("None", flag == HAnimation::KeyFlag_None))
							{
								flag = HAnimation::KeyFlag_None;
								ImGui::CloseCurrentPopup();
							}
							if (ImGui::Selectable("LinearInterpolation", flag == HAnimation::KeyFlag_LinearInterpolation))
							{
								flag = HAnimation::KeyFlag_LinearInterpolation;
								ImGui::CloseCurrentPopup();
							}
							if (ImGui::Selectable("SimpleBezierInterpolation", flag == HAnimation::KeyFlag_SimpleBezierInterpolation))
							{
								flag = HAnimation::KeyFlag_SimpleBezierInterpolation;
								ImGui::CloseCurrentPopup();
							}
							if (ImGui::Button("close"))
							{
								ImGui::CloseCurrentPopup();
							}
							ImGui::EndPopup();
						}
					}
				}

				ImGui::EndNeoTimeLine();
			}
	}
	//Export Time Line Code
	virtual std::string ExportTimeLineCode(std::vector<int>& keys, std::vector<void*>& datas, HAnimation::KeyFlag flag, HWidget* Widget)
	{
		std::cout << "\n pls add \"std::string ExportTimeLineCode(std::vector<int>& keys, std::vector<void*>& datas, HAnimation::KeyFlag flag, HWidget* Widget)\" this function in your HValue class .to build TimeList code";
		return "";
	}
	//GetVariable Name (internal use)
	virtual std::string GetVariableName(HWidget* Widget)
	{
		std::string WidgetName = HAnimation::GetWidgetName(Widget);
		std::replace(WidgetName.begin(), WidgetName.end(), ' ', '_');
		return GetRandText((int)this).append("_").append(WidgetName).append("_").append(Name_);
	}
	// HTool
	void* UseKeyFindData(std::vector<void*> datas, std::vector<int> keys, int key, size_t Index = 0)
	{
		int i = -1;
		for (int& k : keys)
		{
			if (k == key)
			{
				i++;
				if (keys.size() >= i)
					return datas[i];
			}
			i++;
		}
		return 0;
	}
	HAnimation::InterpolationInfo UseKeyFindT(const std::vector<int>& keys, int key)
	{
		HAnimation::InterpolationInfo info;

		for (size_t i = 1; i < keys.size(); i++)
		{
			if (keys[i] > key)
			{
				info.LastOneKey = i;
				break;
			}
			else
			{
				info.PreviousKey = i;
			}
		}

		if (info.LastOneKey > 0)
		{
			int32_t max = keys[info.LastOneKey];
			int32_t min = keys[info.PreviousKey];

			if (max != min)
			{
				info.alpha = static_cast<float>(key - min) / (max - min);
			}
		}

		return info;
	}
	//variables
	//value variable buffer
	void* Data;
	void* InitData;
private:
};

std::string HAnimation::CodeExportTool::DataSwitching(std::vector<int>& keys, std::vector<void*>& datas, HValue* value, HWidget* Widget)
{
	std::string ExportBuffer;
	ExportBuffer += R"(	switch (Frame)
	{)";
	for (size_t i = 0; i < keys.size(); i++)
	{
		ExportBuffer += "\n	case ";
		ExportBuffer += std::to_string(keys.at(i));
		ExportBuffer += ":\n		";
		ExportBuffer += value->GetVariableName(Widget);
		ExportBuffer += " = ";
		ExportBuffer += value->GetValue(datas.at(i));
		ExportBuffer += ";\n		break;";
	}
	ExportBuffer += R"(
	default:
		break;
	})";
	return ExportBuffer;
}
std::string HAnimation::CodeExportTool::Interpolation::DataInterpolation(std::string VariableType, std::vector<int>& key, std::vector<void*>& datas, HValue* value, HWidget* Widget)
{
	HAnimation::CodeExportTool::sortKeysAndValues(key, datas);
	std::string ExportBuffer;
	ExportBuffer += "\n	const std::vector<int> ";
	ExportBuffer += value->GetVariableName(Widget);
	ExportBuffer += "_keys = { ";
	for (int32_t& k : key)
	{
		ExportBuffer += " ";
		ExportBuffer += std::to_string(k);
		if (k != key.back())
			ExportBuffer += " ,";
	}
	ExportBuffer += " };";

	ExportBuffer += "\n	const std::vector<";
	ExportBuffer += VariableType;
	ExportBuffer += "> ";
	ExportBuffer += value->GetVariableName(Widget);
	ExportBuffer += "_values = { ";
	for (void*& d : datas)
	{
		ExportBuffer += " ";
		ExportBuffer += value->GetValue(d);
		if (d != datas.back())
			ExportBuffer += " ,";
	}
	ExportBuffer += " };";

	ExportBuffer += "\n	H_InterpolationInfo ";
	ExportBuffer += value->GetVariableName(Widget);
	ExportBuffer += "_info = H_GetInterpolationInfoFromKeys(";
	ExportBuffer += value->GetVariableName(Widget);
	ExportBuffer += "_keys , Frame );";

	return ExportBuffer;
}
std::string HAnimation::CodeExportTool::Interpolation::GetVectorName(HValue* value, HWidget* Widget, bool IsKeys)
{
	if (IsKeys)
		return value->GetVariableName(Widget).append("_keys");
	return value->GetVariableName(Widget).append("_values");
}
std::string HAnimation::CodeExportTool::Interpolation::GetInfoData(HValue* value, HWidget* Widget, HInfoDataFlage_ flag)
{
	switch (flag)
	{
	case HAnimation::CodeExportTool::Interpolation::HInfoDataFlage_PreviousKey:
		return  value->GetVariableName(Widget).append("_info.PreviousKey");
		break;
	case HAnimation::CodeExportTool::Interpolation::HInfoDataFlage_LastOneKey:
		return value->GetVariableName(Widget).append("_info.LastOneKey");
		break;
	case HAnimation::CodeExportTool::Interpolation::HInfoDataFlage_alpha:
		return value->GetVariableName(Widget).append("_info.alpha");
		break;
	default:
		break;
	}
}
class HWidgetValues
{
public:
	HWidgetValues()
	{
	}
	~HWidgetValues()
	{
	}
	size_t AddHValue(HValue* HValueTarget)
	{
		HValues.push_back(HValueTarget);
		return HValues.size();
	}
	json Save()
	{
		json J;
		for (size_t i = 0; i < HValues.size(); i++)
		{
			json JI;
			JI = HValues.at(i)->Save();
			JI["Exposed"] = HValues.at(i)->ExposedAsVariable;
			J.push_back(JI);
		}
		return J;
	}
	void Load(json J)
	{
		if (J.size() == HValues.size())
			for (size_t i = 0; i < J.size(); i++)
			{
				HValues.at(i)->Load(J[i]);
				if(HValues[i]->CanExposedAsVariable)
					HValues.at(i)->ExposedAsVariable = J[i]["Exposed"];
			}
		else
			std::cout << "\n HValue.h -> HWidgetValues -> Load -> Error : json size != HValues size";
	}
	void ExportValue(HWidget* widget,std::vector<HVariableExport>& EVariable ,std::vector<HVariableExport>& ECacheVariable)
	{
		for (HValue*& v:HValues)
		{
			if (v->ExposedAsVariable)
			{
				if (v->ExporsedVariableToDefault)
				{
					EVariable.push_back(v->GetVariableExport(widget));
				}
				else
				{
					ECacheVariable.push_back(v->GetVariableExport(widget));
				}
			}
		}
	}
	std::vector <HValue*> HValues;
private:
};

class HVBool : public HValue
{
public:
	HVBool(const char* Name, bool init = false, bool ExposedAsVariable_ = false, bool CanExposedAsVariable_ = true)
	{
		ExposedAsVariable = ExposedAsVariable_;
		CanExposedAsVariable = CanExposedAsVariable_;
		Name_ = Name;
		InitData = new bool(init);
		Data = new bool(init);
	}
	virtual std::string GetType()override {
		return	"bool";
	};
	virtual void DrawWidgetCallBack(const char* label) override
	{
		ImGui::Checkbox(label, (bool*)Data);
	}
	virtual void TimeLineUpdataValueCallBack(std::vector<void*> datas, std::vector<int>keys, HAnimation::KeyFlag flag) override
	{
		void* buffer = UseKeyFindData(datas, keys, HAnimation::CurrentSequenFrame);
		if (Data && buffer != 0)
		{
			*(bool*)Data = *(bool*)buffer;
		}
	}
	virtual HValue* CreateSelf(const char* Name) override {
		return new HVBool(Name);
	};
	virtual std::string GetValue(void* TargetData) override
	{
		return ToString(TargetData);
	}
	virtual HVariableExport GetVariableExport(HWidget* Widget, bool InitVariable = true, bool UseStatic = true) override
	{
		//Example code :
		HVariableExport ExportBuffer;
		ExportBuffer.Comment = "--bool--";
		ExportBuffer.VariableCode = std::string("\n	"/*\n <-This have a TAB*/);
		if (UseStatic)
			ExportBuffer.VariableCode.append("static ");
		ExportBuffer.VariableCode.append("bool");//<-----your value type
		ExportBuffer.VariableCode.append(" ").append(GetVariableName(Widget));
		if (InitVariable && Data)
			ExportBuffer.VariableCode.append(" = ").append(GetValue(Data));
		ExportBuffer.VariableCode.append(";");
		return ExportBuffer;
	}
	virtual json Save() override
	{
		json J;
		J["Value"] = *(bool*)Data;
		return J;
	}
	virtual void Load(json J) override
	{
		*(bool*)Data = J["Value"];
	}
	virtual json OnlySaveData(void* data)override
	{
		json J;
		J = *(bool*)data;
		return J;
	}
	virtual void* OnlyLoadData(json J)override
	{
		return new bool(J.get<bool>());
	}
	virtual std::string ExportTimeLineCode(std::vector<int>& keys, std::vector<void*>& datas, HAnimation::KeyFlag flag, HWidget* Widget)override
	{
		return HAnimation::CodeExportTool::DataSwitching(keys, datas, this, Widget);
	}
	bool* Get()
	{
		return (bool*)Data;
	}
	//variable
private:
	//get bool data to string e.g. true/false
	std::string ToString(void* Value)
	{
		if (*(bool*)Value)
			return "true";
		return "false";
	}
};

static char HVStringInputBuffer[MAX_PATH] = {""};
class HVString : public HValue
{
public:
	HVString(const char* Name, std::string init = "",bool AppendRandID = false,size_t size_ = 0,bool ExposedAsVariable_ = false,bool CanExposedAsVariable_ = true)
	{
		size = size_;
		ExposedAsVariable = ExposedAsVariable_;
		CanExposedAsVariable = CanExposedAsVariable_;
		Name_ = Name;
		appendrandid = AppendRandID;
		InitData = new std::string(appendID(init));
		Data = new std::string(appendID(init));
		if (size_ > 0)
			((std::string*)Data)->resize(size_);
	}

	virtual void Draw(const char* label, HWidget* Widget/*this*/)override
	{
		if (CanExposedAsVariable)
		{
			ImGui::Checkbox(std::string("###exposed as variable").append(std::to_string((int)this)).c_str(), &ExposedAsVariable);
			if (ImGui::IsItemHovered())
			{
				if (ImGui::BeginTooltip())
				{
					ImGui::Text("exposed as variable");
					ImGui::EndTooltip();
				}
			}
			ImGui::SameLine();
		}

		DrawWidgetCallBack(label);
		if (CanAddToTimeLine && HAnimation::CurrentSequencer && ExposedAsVariable && size == 0)
		{
			ImGui::SameLine();
			if (ImGui::Button(std::string(" + ###AddToTimeLine").append(std::to_string((int)this)).c_str()))
			{
				HAnimation::TimeLineAddFrame(Widget, this);
				std::cout << "\n Add Frame Button Down";
				if (HAnimation::TimeLineAddFrame == 0)
				{
					std::cout << "\n HValue-> Draw-> Error -> HAnimation::TimeLineAddFrame Function is : Null";
				}
			}
		}
	}
	virtual std::string GetType()override {
		return	"std::string";
	};
	virtual void DrawWidgetCallBack(const char* label) override
	{
		strcpy_s(HVStringInputBuffer, ((std::string*)Data)->data());
		if (ImGui::InputText(label, HVStringInputBuffer, MAX_PATH))
		{
			*(std::string*)Data = appendID(HVStringInputBuffer);
		}
	}
	virtual void TimeLineUpdataValueCallBack(std::vector<void*> datas, std::vector<int>keys, HAnimation::KeyFlag flag) override
	{
		void* buffer = UseKeyFindData(datas, keys, HAnimation::CurrentSequenFrame);
		if (Data && buffer != 0)
		{
			*(std::string*)Data = *(std::string*)buffer;
		}
	}
	virtual HValue* CreateSelf(const char* Name) override {
		return new HVString(Name);
	};
	virtual std::string GetValue(void* TargetData) override
	{
		return std::string("\"").append( * (std::string*)(TargetData)).append("\"");
	}
	virtual HVariableExport GetVariableExport(HWidget* Widget, bool InitVariable = true, bool UseStatic = true) override
	{
		//Example code :
		HVariableExport ExportBuffer;
		ExportBuffer.Comment = "--std::string--";
		ExportBuffer.VariableCode = std::string("\n	"/*\n <-This have a TAB*/);
		if (UseStatic)
			ExportBuffer.VariableCode.append("static ");
		ExportBuffer.VariableCode.append("std::string");//<-----your value type
		ExportBuffer.VariableCode.append(" ").append(GetVariableName(Widget));
		if (InitVariable && Data)
			ExportBuffer.VariableCode.append(" = ").append(GetValue(Data));
		ExportBuffer.VariableCode.append(";");
		if (size > 0)
			ExportBuffer.VariableCode.append("\n").append(GetVariableName(Widget)).append(".resize(").append(std::to_string(size)).append(");");
		return ExportBuffer;
	}
	virtual json Save() override
	{
		json J;
		J["Value"] = *(std::string*)Data;
		return J;
	}
	virtual void Load(json J) override
	{
		*(std::string*)Data = J["Value"];
	}
	virtual json OnlySaveData(void* data)override
	{
		json J;
		J = *(std::string*)data;
		return J;
	}
	virtual void* OnlyLoadData(json J)override
	{
		return new std::string(J.get<std::string>());
	}
	virtual std::string ExportTimeLineCode(std::vector<int>& keys, std::vector<void*>& datas, HAnimation::KeyFlag flag, HWidget* Widget)override
	{
		return HAnimation::CodeExportTool::DataSwitching(keys, datas, this, Widget);
	}
	virtual std::string GetVariableName(HWidget* Widget) override
	{
		std::string WidgetName = HAnimation::GetWidgetName(Widget);
		std::replace(WidgetName.begin(), WidgetName.end(), ' ', '_');
		return GetRandText((int)this).append("_").append(WidgetName).append("_").append(Name_).append(".data()");
	}
	std::string& Get()
	{
		return *(std::string*)Data;
	}
	//variable
private:
	size_t size;
	bool appendrandid;
	std::string appendID(std::string in)
	{
		if (appendrandid)
			return std::string(in).append("###").append(std::to_string((int)this));
		else
			return in;
	}
};

class HVFloat : public HValue
{
public:
	HVFloat(const char* Name, float init = 0, bool ExposedAsVariable_ = false, bool CanExposedAsVariable_ = true)
	{
		ExposedAsVariable = ExposedAsVariable_;
		CanExposedAsVariable = CanExposedAsVariable_;
		Name_ = Name;
		InitData = new float(init);
		Data = new float(init);
		HaveFlagMode = true;
	}
	virtual std::string GetType()override {
		return	"float";
	};
	virtual void DrawWidgetCallBack(const char* label) override
	{
		ImGui::DragFloat(label, (float*)Data);
	}
	virtual void TimeLineUpdataValueCallBack(std::vector<void*> datas, std::vector<int>keys, HAnimation::KeyFlag flag) override
	{
		if (flag == HAnimation::KeyFlag_None)
		{
			void* buffer = UseKeyFindData(datas, keys, HAnimation::CurrentSequenFrame);
			if (Data && buffer != 0)
			{
				*(float*)Data = *(float*)buffer;
			}
		}
		else if (flag == HAnimation::KeyFlag_LinearInterpolation)
		{
			HAnimation::InterpolationInfo info = UseKeyFindT(keys, HAnimation::CurrentSequenFrame);
			*(float*)Data = HAnimation::LinearInterpolation(*(float*)datas[info.PreviousKey], *(float*)datas[info.LastOneKey], info.alpha);
		}
		else if (flag == HAnimation::KeyFlag_SimpleBezierInterpolation)
		{
			HAnimation::InterpolationInfo info = UseKeyFindT(keys, HAnimation::CurrentSequenFrame);
			*(float*)Data = HAnimation::SimpleBezierInterpolation(*(float*)datas[info.PreviousKey], *(float*)datas[info.LastOneKey], info.alpha);
		}
	}
	virtual HValue* CreateSelf(const char* Name) override {
		return new HVFloat(Name);
	};
	virtual std::string GetValue(void* TargetData) override
	{
		return std::to_string(*(float*)TargetData);
	}
	virtual HVariableExport GetVariableExport(HWidget* Widget, bool InitVariable = true, bool UseStatic = true) override
	{
		//Example code :
		HVariableExport ExportBuffer;
		ExportBuffer.Comment = "--float--";
		ExportBuffer.VariableCode = std::string("\n	"/*\n <-This have a TAB*/);
		if (UseStatic)
			ExportBuffer.VariableCode.append("static ");
		ExportBuffer.VariableCode.append("float");//<-----your value type
		ExportBuffer.VariableCode.append(" ").append(GetVariableName(Widget));
		if (InitVariable && Data)
			ExportBuffer.VariableCode.append(" = ").append(GetValue(Data));
		ExportBuffer.VariableCode.append(";");
		return ExportBuffer;
	}
	virtual json Save() override
	{
		json J;
		J["Value"] = *(float*)Data;
		return J;
	}
	virtual void Load(json J) override
	{
		*(float*)Data = J["Value"];
	}
	virtual json OnlySaveData(void* data)override
	{
		json J;
		J = *(float*)data;
		return J;
	}
	virtual void* OnlyLoadData(json J)override
	{
		return new float(J.get<float>());
	}
	virtual std::string ExportTimeLineCode(std::vector<int>& keys, std::vector<void*>& datas, HAnimation::KeyFlag flag, HWidget* Widget) override
	{
		std::string ExportBuffer , buffer;
		switch (flag)
		{
		case HAnimation::KeyFlag_None:
			return HAnimation::CodeExportTool::DataSwitching(keys, datas, this, Widget);
			break;
		case HAnimation::KeyFlag_LinearInterpolation:
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::DataInterpolation("float", keys, datas, this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += " = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetLinearInterpolationCode("", this, Widget);
			break;
		case HAnimation::KeyFlag_SimpleBezierInterpolation:
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::DataInterpolation("float", keys, datas, this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += " = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetSimpleBezierInterpolationCode("", this, Widget);
			break;
		default:
			break;
		}
		return ExportBuffer;
	}

	float* Get()
	{
		return (float*)Data;
	}
	//variable
private:
};

class HVInt : public HValue
{
public:
	HVInt(const char* Name, int init = 0, bool ExposedAsVariable_ = false, bool CanExposedAsVariable_ = true)
	{
		ExposedAsVariable = ExposedAsVariable_;
		CanExposedAsVariable = CanExposedAsVariable_;
		Name_ = Name;
		InitData = new int(init);
		Data = new int(init);
		HaveFlagMode = true;
	}
	virtual std::string GetType()override {
		return	"int";
	};
	virtual void DrawWidgetCallBack(const char* label) override
	{
		ImGui::DragInt(label, (int*)Data);
	}
	virtual void TimeLineUpdataValueCallBack(std::vector<void*> datas, std::vector<int>keys, HAnimation::KeyFlag flag) override
	{
		if (flag == HAnimation::KeyFlag_None)
		{
			void* buffer = UseKeyFindData(datas, keys, HAnimation::CurrentSequenFrame);
			if (Data && buffer != 0)
			{
				*(int*)Data = *(int*)buffer;
			}
		}
		else if (flag == HAnimation::KeyFlag_LinearInterpolation)
		{
			HAnimation::InterpolationInfo info = UseKeyFindT(keys, HAnimation::CurrentSequenFrame);
			*(int*)Data = HAnimation::LinearInterpolation(*(int*)datas[info.PreviousKey], *(int*)datas[info.LastOneKey], info.alpha);
		}
		else if (flag == HAnimation::KeyFlag_SimpleBezierInterpolation)
		{
			HAnimation::InterpolationInfo info = UseKeyFindT(keys, HAnimation::CurrentSequenFrame);
			*(int*)Data = HAnimation::SimpleBezierInterpolation(*(int*)datas[info.PreviousKey], *(int*)datas[info.LastOneKey], info.alpha);
		}
	}
	virtual HValue* CreateSelf(const char* Name) override {
		return new HVInt(Name);
	};
	virtual std::string GetValue(void* TargetData) override
	{
		return std::to_string(*(int*)TargetData);
	}
	virtual HVariableExport GetVariableExport(HWidget* Widget, bool InitVariable = true, bool UseStatic = true) override
	{
		//Example code :
		HVariableExport ExportBuffer;
		ExportBuffer.Comment = "--int--";
		ExportBuffer.VariableCode = std::string("\n	"/*\n <-This have a TAB*/);
		if (UseStatic)
			ExportBuffer.VariableCode.append("static ");
		ExportBuffer.VariableCode.append("int");//<-----your value type
		ExportBuffer.VariableCode.append(" ").append(GetVariableName(Widget));
		if (InitVariable && Data)
			ExportBuffer.VariableCode.append(" = ").append(GetValue(Data));
		ExportBuffer.VariableCode.append(";");
		return ExportBuffer;
	}
	virtual json Save() override
	{
		json J;
		J["Value"] = *(int*)Data;
		return J;
	}
	virtual void Load(json J) override
	{
		*(int*)Data = J["Value"];
	}
	virtual json OnlySaveData(void* data)override
	{
		json J;
		J = *(int*)data;
		return J;
	}
	virtual void* OnlyLoadData(json J)override
	{
		return new int(J.get<int>());
	}
	virtual std::string ExportTimeLineCode(std::vector<int>& keys, std::vector<void*>& datas, HAnimation::KeyFlag flag, HWidget* Widget) override
	{
		std::string ExportBuffer, buffer;
		switch (flag)
		{
		case HAnimation::KeyFlag_None:
			return HAnimation::CodeExportTool::DataSwitching(keys, datas, this, Widget);
			break;
		case HAnimation::KeyFlag_LinearInterpolation:
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::DataInterpolation("int", keys, datas, this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += " = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetLinearInterpolationCode("", this, Widget);
			break;
		case HAnimation::KeyFlag_SimpleBezierInterpolation:
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::DataInterpolation("int", keys, datas, this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += " = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetSimpleBezierInterpolationCode("", this, Widget);
			break;
		default:
			break;
		}
		return ExportBuffer;
	}

	int* Get()
	{
		return (int*)Data;
	}
	//variable
private:
};

class HVImVec2 : public HValue
{
public:
	HVImVec2(const char* Name, ImVec2 init = ImVec2(), bool ExposedAsVariable_ = false, bool CanExposedAsVariable_ = true)
	{
		ExposedAsVariable = ExposedAsVariable_;
		CanExposedAsVariable = CanExposedAsVariable_;
		Name_ = Name;
		InitData = new ImVec2(init);
		Data = new ImVec2(init);
		HaveFlagMode = true;
	}
	virtual std::string GetType()override {
		return	"ImVec2";
	};
	virtual void DrawWidgetCallBack(const char* label) override
	{
		ImGui::DragFloat2(label, (float*)Data);
	}
	virtual void TimeLineUpdataValueCallBack(std::vector<void*> datas, std::vector<int>keys, HAnimation::KeyFlag flag) override
	{
		if (flag == HAnimation::KeyFlag_None)
		{
			void* buffer = UseKeyFindData(datas, keys, HAnimation::CurrentSequenFrame);
			if (Data && buffer != 0)
			{
				*(ImVec2*)Data = *(ImVec2*)buffer;
			}
		}
		else if (flag == HAnimation::KeyFlag_LinearInterpolation)
		{
			HAnimation::InterpolationInfo info = UseKeyFindT(keys, HAnimation::CurrentSequenFrame);
			(*(ImVec2*)Data).x = HAnimation::LinearInterpolation((*(ImVec2*)datas[info.PreviousKey]).x, (*(ImVec2*)datas[info.LastOneKey]).x, info.alpha);
			(*(ImVec2*)Data).y = HAnimation::LinearInterpolation((*(ImVec2*)datas[info.PreviousKey]).y, (*(ImVec2*)datas[info.LastOneKey]).y, info.alpha);
		}
		else if (flag == HAnimation::KeyFlag_SimpleBezierInterpolation)
		{
			HAnimation::InterpolationInfo info = UseKeyFindT(keys, HAnimation::CurrentSequenFrame);
			(*(ImVec2*)Data).x = HAnimation::SimpleBezierInterpolation((*(ImVec2*)datas[info.PreviousKey]).x, (*(ImVec2*)datas[info.LastOneKey]).x, info.alpha);
			(*(ImVec2*)Data).y = HAnimation::SimpleBezierInterpolation((*(ImVec2*)datas[info.PreviousKey]).y, (*(ImVec2*)datas[info.LastOneKey]).y, info.alpha);
		}
	}
	virtual HValue* CreateSelf(const char* Name) override {
		return new HVImVec2(Name);
	};
	virtual std::string GetValue(void* TargetData) override
	{
		return std::string("ImVec2(").append(std::to_string((*(ImVec2*)TargetData).x)).append(",").append(std::to_string((*(ImVec2*)TargetData).y)).append(")");
	}
	virtual HVariableExport GetVariableExport(HWidget* Widget, bool InitVariable = true, bool UseStatic = true) override
	{
		//Example code :
		HVariableExport ExportBuffer;
		ExportBuffer.Comment = "--ImVec2--";
		ExportBuffer.VariableCode = std::string("\n	"/*\n <-This have a TAB*/);
		if (UseStatic)
			ExportBuffer.VariableCode.append("static ");
		ExportBuffer.VariableCode.append("ImVec2");//<-----your value type
		ExportBuffer.VariableCode.append(" ").append(GetVariableName(Widget));
		if (InitVariable && Data)
			ExportBuffer.VariableCode.append(" = ").append(GetValue(Data));
		ExportBuffer.VariableCode.append(";");
		return ExportBuffer;
	}
	virtual json Save() override
	{
		json J,v;
		v["x"] =  (* (ImVec2*)Data).x;
		v["y"] = (*(ImVec2*)Data).y;
		J["Value"] = v;
		return J;
	}
	virtual void Load(json J) override
	{
		json v= J["Value"];
		(*(ImVec2*)Data).x = v["x"];
		(*(ImVec2*)Data).y = v["y"];
	}
	virtual json OnlySaveData(void* data)override
	{
		json J, v;
		v["x"] = (*(ImVec2*)data).x;
		v["y"] = (*(ImVec2*)data).y;
		J["Value"] = v;
		return J;
	}
	virtual void* OnlyLoadData(json J)override
	{
		json v = J["Value"];
		return new ImVec2(v["x"], v["y"]);
	}
	virtual std::string ExportTimeLineCode(std::vector<int>& keys, std::vector<void*>& datas, HAnimation::KeyFlag flag, HWidget* Widget) override
	{
		std::string ExportBuffer, buffer;
		switch (flag)
		{
		case HAnimation::KeyFlag_None:
			return HAnimation::CodeExportTool::DataSwitching(keys, datas, this, Widget);
			break;
		case HAnimation::KeyFlag_LinearInterpolation:
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::DataInterpolation("ImVec2", keys, datas, this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += ".x = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetLinearInterpolationCode(".x", this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += ".y = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetLinearInterpolationCode(".y", this, Widget);
			break;
		case HAnimation::KeyFlag_SimpleBezierInterpolation:
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::DataInterpolation("ImVec2", keys, datas, this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += ".x = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetSimpleBezierInterpolationCode(".x", this, Widget);
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += ".y = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetSimpleBezierInterpolationCode(".y", this, Widget);
			break;
		default:
			break;
		}
		return ExportBuffer;
	}

	ImVec2* Get()
	{
		return (ImVec2*)Data;
	}
	//variable
private:
};

class HVImVec4 : public HValue
{
public:
	bool usecoloredit = false;
	HVImVec4(const char* Name, ImVec4 init = ImVec4(), bool UseColorEdit = false, bool ExposedAsVariable_ = false, bool CanExposedAsVariable_ = true)
	{
		ExposedAsVariable = ExposedAsVariable_;
		CanExposedAsVariable = CanExposedAsVariable_;
		Name_ = Name;
		InitData = new ImVec4(init);
		Data = new ImVec4(init);
		HaveFlagMode = true;
		usecoloredit = UseColorEdit;
	}
	virtual std::string GetType()override {
		return	"ImVec4";
	};
	virtual void DrawWidgetCallBack(const char* label) override
	{
		if (usecoloredit)
			ImGui::ColorEdit4(label, (float*)Data,ImGuiColorEditFlags_::ImGuiColorEditFlags_AlphaBar);
		else
			ImGui::DragFloat4(label, (float*)Data);
	}
	virtual void TimeLineUpdataValueCallBack(std::vector<void*> datas, std::vector<int>keys, HAnimation::KeyFlag flag) override
	{
		if (flag == HAnimation::KeyFlag_None)
		{
			void* buffer = UseKeyFindData(datas, keys, HAnimation::CurrentSequenFrame);
			if (Data && buffer != 0)
			{
				*(ImVec4*)Data = *(ImVec4*)buffer;
			}
		}
		else if (flag == HAnimation::KeyFlag_LinearInterpolation)
		{
			HAnimation::InterpolationInfo info = UseKeyFindT(keys, HAnimation::CurrentSequenFrame);
			(*(ImVec4*)Data).x = HAnimation::LinearInterpolation((*(ImVec4*)datas[info.PreviousKey]).x, (*(ImVec4*)datas[info.LastOneKey]).x, info.alpha);
			(*(ImVec4*)Data).y = HAnimation::LinearInterpolation((*(ImVec4*)datas[info.PreviousKey]).y, (*(ImVec4*)datas[info.LastOneKey]).y, info.alpha);
			(*(ImVec4*)Data).z = HAnimation::LinearInterpolation((*(ImVec4*)datas[info.PreviousKey]).z, (*(ImVec4*)datas[info.LastOneKey]).z, info.alpha);
			(*(ImVec4*)Data).w = HAnimation::LinearInterpolation((*(ImVec4*)datas[info.PreviousKey]).w, (*(ImVec4*)datas[info.LastOneKey]).w, info.alpha);
		}
		else if (flag == HAnimation::KeyFlag_SimpleBezierInterpolation)
		{
			HAnimation::InterpolationInfo info = UseKeyFindT(keys, HAnimation::CurrentSequenFrame);
			(*(ImVec4*)Data).x = HAnimation::SimpleBezierInterpolation((*(ImVec4*)datas[info.PreviousKey]).x, (*(ImVec4*)datas[info.LastOneKey]).x, info.alpha);
			(*(ImVec4*)Data).y = HAnimation::SimpleBezierInterpolation((*(ImVec4*)datas[info.PreviousKey]).y, (*(ImVec4*)datas[info.LastOneKey]).y, info.alpha);
			(*(ImVec4*)Data).z = HAnimation::SimpleBezierInterpolation((*(ImVec4*)datas[info.PreviousKey]).z, (*(ImVec4*)datas[info.LastOneKey]).z, info.alpha);
			(*(ImVec4*)Data).w = HAnimation::SimpleBezierInterpolation((*(ImVec4*)datas[info.PreviousKey]).w, (*(ImVec4*)datas[info.LastOneKey]).w, info.alpha);
		}
	}
	virtual HValue* CreateSelf(const char* Name) override {
		return new HVImVec4(Name);
	};
	virtual std::string GetValue(void* TargetData) override
	{
		return std::string("ImVec4(").append(std::to_string((*(ImVec4*)TargetData).x)).append(",").append(std::to_string((*(ImVec4*)TargetData).y)).append(",").append(std::to_string((*(ImVec4*)TargetData).z)).append(",").append(std::to_string((*(ImVec4*)TargetData).w)).append(")");
	}
	virtual HVariableExport GetVariableExport(HWidget* Widget, bool InitVariable = true, bool UseStatic = true) override
	{
		//Example code :
		HVariableExport ExportBuffer;
		ExportBuffer.Comment = "--ImVec4--";
		ExportBuffer.VariableCode = std::string("\n	"/*\n <-This have a TAB*/);
		if (UseStatic)
			ExportBuffer.VariableCode.append("static ");
		ExportBuffer.VariableCode.append("ImVec4");//<-----your value type
		ExportBuffer.VariableCode.append(" ").append(GetVariableName(Widget));
		if (InitVariable && Data)
			ExportBuffer.VariableCode.append(" = ").append(GetValue(Data));
		ExportBuffer.VariableCode.append(";");
		return ExportBuffer;
	}
	virtual json Save() override
	{
		json J, v;
		v["x"] = (*(ImVec4*)Data).x;
		v["y"] = (*(ImVec4*)Data).y;
		v["z"] = (*(ImVec4*)Data).z;
		v["w"] = (*(ImVec4*)Data).w;
		J["Value"] = v;
		return J;
	}
	virtual void Load(json J) override
	{
		json v = J["Value"];
		(*(ImVec4*)Data).x = v["x"];
		(*(ImVec4*)Data).y = v["y"];
		(*(ImVec4*)Data).y = v["z"];
		(*(ImVec4*)Data).y = v["w"];
	}
	virtual json OnlySaveData(void* data)override
	{
		json J, v;
		v["x"] = (*(ImVec4*)Data).x;
		v["y"] = (*(ImVec4*)Data).y;
		v["z"] = (*(ImVec4*)Data).z;
		v["w"] = (*(ImVec4*)Data).w;
		J["Value"] = v;
		return J;
	}
	virtual void* OnlyLoadData(json J)override
	{
		json v = J["Value"];
		return new ImVec4(v["x"], v["y"],v["z"],v["w"]);
	}
	virtual std::string ExportTimeLineCode(std::vector<int>& keys, std::vector<void*>& datas, HAnimation::KeyFlag flag, HWidget* Widget) override
	{
		std::string ExportBuffer, buffer;
		switch (flag)
		{
		case HAnimation::KeyFlag_None:
			return HAnimation::CodeExportTool::DataSwitching(keys, datas, this, Widget);
			break;
		case HAnimation::KeyFlag_LinearInterpolation:
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::DataInterpolation("ImVec4", keys, datas, this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += ".x = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetLinearInterpolationCode(".x", this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += ".y = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetLinearInterpolationCode(".y", this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += ".z = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetLinearInterpolationCode(".z", this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += ".w = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetLinearInterpolationCode(".w", this, Widget);
			break;
		case HAnimation::KeyFlag_SimpleBezierInterpolation:
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::DataInterpolation("ImVec4", keys, datas, this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += ".x = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetSimpleBezierInterpolationCode(".x", this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += ".y = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetSimpleBezierInterpolationCode(".y", this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += ".z = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetSimpleBezierInterpolationCode(".z", this, Widget);
			ExportBuffer += "\n	";
			ExportBuffer += GetVariableName(Widget);
			ExportBuffer += ".w = ";
			ExportBuffer += HAnimation::CodeExportTool::Interpolation::GetSimpleBezierInterpolationCode(".w", this, Widget);
			break;
		default:
			break;
		}
		return ExportBuffer;
	}

	ImVec4* Get()
	{
		return (ImVec4*)Data;
	}
	//variable
private:
};