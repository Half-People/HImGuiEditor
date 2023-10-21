#pragma once
#include "imgui_neo_sequencer.h"
#include <nlohmann/json.hpp>
#include <vector>
#include "HWidget.h"
#include <clipboardxx.hpp>

struct HSequencerValue
{
	void clear()
	{
		// "values"  have a memory leak
		values.clear();
		keys.clear();
	}

	std::vector<void*> values;
	std::vector<int> keys;
	HAnimation::KeyFlag Flag = HAnimation::KeyFlag_None;
	bool Open;
	HValue* TargetHValue;
	json Save()
	{
		json J, k, v;
		if (keys.size() != values.size())
			return json();
		for (size_t i = 0; i < keys.size(); i++)
		{
			v.push_back(TargetHValue->OnlySaveData(values[i]));
			k.push_back(keys[i]);
		}
		J["k"] = k;
		J["v"] = v;
		J["o"] = Open;
		J["f"] = Flag;
		return J;
	}

	void Load(json J)
	{
		json k, v;
		k = J["k"];
		v = J["v"];
		Flag = J["f"];
		Open = J["o"];

		for (size_t i = 0; i < k.size(); i++)
		{
			values.push_back(TargetHValue->OnlyLoadData(v[i]));
			keys.push_back(k[i]);
		}
	}
	bool empty()
	{
		return keys.empty();
	}
};

struct HSequencerWidgetValues
{
	std::vector<HSequencerValue> Values;
	//	size_t WidgetID;
	HWidget* WidgetTarget;

	void clear()
	{
		for (size_t i = 0; i < Values.size(); i++)
		{
			Values.at(i).clear();
		}
	}

	void Updata()
	{
		for (HSequencerValue& Value : Values)
		{
			Value.TargetHValue->TimeLineUpdataValueCallBack(Value.values, Value.keys, Value.Flag);
		}
	}


	int GetWidgetIndex(int& Index, HWidget* Widget)
	{
		while (Widget)
		{
			if (Widget == WidgetTarget)
				return Index;

			if (Widget->Content)
			{
				Index++;
				int IndexBuffer = GetWidgetIndex(Index, Widget->Content);
				if (IndexBuffer != -1)
					return IndexBuffer;
			}

			Widget = Widget->Subclass;
			Index++;
		}
		return -1;
	}

	HWidget* GetWidgetFromIndex(HWidget*Widget, int Index,int& CurrentIndex)
	{
		while (Widget)
		{
			if (Index == CurrentIndex)
				return Widget;
			HWidget* WidgetBuffer = 0;
			if (Widget->Content)
				WidgetBuffer = GetWidgetFromIndex(Widget->Content,Index, CurrentIndex);
			if (WidgetBuffer != 0)
				return WidgetBuffer;
			Widget = Widget->Subclass;
			CurrentIndex++;
		}
		return 0;
	}

	json Save()
	{
		json J, v;

		J["Open"] = Open;

		for (HSequencerValue& Value : Values)
		{
			v.push_back(Value.Save());
		}
		J["Values"] = v;

		int Index = 0;
		for (HWidget*& W : *HImGuiWidnowsWidgetList)
		{
			int RtBuffer = GetWidgetIndex(Index, W);
			if (RtBuffer != -1)
			{
				J["WidgetIndex"] = RtBuffer;
				return J;
			}
		}
		J["WidgetIndex"] = -1;
		return J;
	}

	bool Load(json J)
	{
		Open = J["Open"];
		size_t WidgetIndex = J["WidgetIndex"];
		int IndexBuffer = 0;
		for (HWidget*& W :  *HImGuiWidnowsWidgetList)
		{
			WidgetTarget = GetWidgetFromIndex(W, WidgetIndex, IndexBuffer);
			if (WidgetTarget != 0)
				break;
		}

		//WidgetTarget = HImGuiWidnowsWidgetList->at(WidgetIndex);
		if (WidgetTarget == NULL)
		{
			std::cout << "\n HAnimationSequencerPanel.h -> HSequencerWidgetValues -> Load -> Error-> Message : WidgetTarget is null";
			return false;
		}
		json v;
		v = J["Values"];
		for (size_t i = 0; i < v.size(); i++)
		{
			Values.push_back(HSequencerValue());
			if (WidgetTarget->HValues.HValues.size() >= i)
			{
				Values.back().TargetHValue = WidgetTarget->HValues.HValues.at(i);
			}
			if (Values.back().TargetHValue)
			{
				Values.back().Load(v[i]);
			}
		}
		return true;
	}

	std::string GetExportCode()
	{
		std::string Buffer = "\n//---    ";
		Buffer += *WidgetTarget->WidgetName;
		for (HSequencerValue& Value : Values)
		{
			if (!Value.keys.empty())
			{
				Buffer.append("\n//").append(Value.TargetHValue->Name_).append("\n");
				std::cout << "Buffer : " << Buffer;

				Buffer.append(Value.TargetHValue->ExportTimeLineCode(Value.keys, Value.values, Value.Flag, WidgetTarget));
			}
		}
		return Buffer;
	}
	bool empty()
	{
		for (HSequencerValue& v : Values)
		{
			if (!v.empty())
			{
				return false;
			}
		}
		return true;
	}
	bool Open;
};

static int32_t HAnimationSequencerPreviousFrame = 0;

struct HAnimationSequencer
{
	HAnimationSequencer()
	{
		strcpy_s(SequencerName, RenameVerify(SequencerName).c_str());
	}
	int32_t startFrame = 0;
	int32_t endFrame = 64;
	int FramePerSeconds = 30;
	char SequencerName[100]{ "NewSequencer" };
	std::vector<HSequencerWidgetValues> TimeLists;
	bool Playing = false;
	float FrameBuff = 0;
	void Draw()
	{
		ImGui::SetNextItemWidth(150);
		if (ImGui::InputText("SequencerName", SequencerName, 100))
		{
			strcpy_s(SequencerName, RenameVerify(SequencerName).c_str());
		}
		ImGui::SameLine();
		ImGui::SetNextItemWidth(50);
		ImGui::DragInt("Frame Per Seconds", &FramePerSeconds, 0.1, -1, 1000);
		ImGui::SameLine();
		ImGui::SetNextItemWidth(50);
		ImGui::DragInt("Start", &startFrame, 0.1, 0, endFrame - 1);
		ImGui::SameLine();
		ImGui::SetNextItemWidth(50);
		ImGui::DragInt("End", &endFrame, 0.1, startFrame + 1, 100000000);
		ImGui::SameLine();
		if (ImGui::Button("CopyCode"))
		{
			ImGui::OpenPopup("CopyAnimationCode");
		}

		if (ImGui::BeginPopupContextVoid("CopyAnimationCode"))
		{
			static bool CodeSpawnisLoop = false;
			ImGui::Checkbox("IsLoop", &CodeSpawnisLoop);

			if (ImGui::Button("close"))
			{
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("copy"))
			{
				clipboardxx::clipboard clipboard;
				std::string Buffer = "AnimationPlayer.Play(";
				Buffer += SequencerName;
				Buffer += " , ";
				Buffer += SequencerName;
				Buffer += "_StartFrame , ";
				Buffer += SequencerName;
				Buffer += "_EndFrame , ";
				Buffer += SequencerName;
				Buffer += "_FramePerSeconds , ";
				if (CodeSpawnisLoop)
				{
					Buffer += "true );";
				}
				else
				{
					Buffer += "false );";
				}

				clipboard << Buffer;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}


		ImGui::SameLine();
		float np = ImGui::GetWindowWidth() / 2;
		if (np > ImGui::GetCursorPosX())
		{
			ImGui::SetCursorPosX(np);
		}

		if (Playing)
		{
			if (FrameBuff >= 1.f / FramePerSeconds)
			{
				FrameBuff = 0;
				HAnimation::CurrentSequenFrame++;
				if (HAnimation::CurrentSequenFrame > endFrame)
					HAnimation::CurrentSequenFrame = startFrame;
			}
			else
			{
				FrameBuff += ImGui::GetIO().DeltaTime;
			}

			if (ImGui::Button("Stop"))
			{
				Playing = false;
			}
		}
		else
		{
			if (ImGui::Button("Play"))
			{
				Playing = true;
			}
		}

		ImGui::Separator();

		if (HAnimationSequencerPreviousFrame != HAnimation::CurrentSequenFrame)
		{
			HAnimationSequencerPreviousFrame = HAnimation::CurrentSequenFrame;
			for (HSequencerWidgetValues& Values : TimeLists)
			{
				Values.Updata();
			}
		}

		if (ImGui::BeginNeoSequencer("Sequencer", &HAnimation::CurrentSequenFrame, &startFrame, &endFrame, { 0, 0 },
			ImGuiNeoSequencerFlags_EnableSelection |
			ImGuiNeoSequencerFlags_Selection_EnableDragging |
			ImGuiNeoSequencerFlags_Selection_EnableDeletion))
		{
			for (HSequencerWidgetValues& Vs : TimeLists)
			{
				std::string WidgetNameBuffer = std::string(*Vs.WidgetTarget->WidgetName).append("-").append(Vs.WidgetTarget->WidgetID).append("###").append(std::to_string((int)Vs.WidgetTarget + 1));
				if (ImGui::BeginNeoGroup(WidgetNameBuffer.c_str(), &Vs.Open))
				{
					if (Vs.WidgetTarget->HValues.HValues.size() == Vs.Values.size())
					{
						for (size_t i = 0; i < Vs.Values.size(); i++)
						{
							if (Vs.WidgetTarget->HValues.HValues[i]->Name_)
							{
								Vs.WidgetTarget->HValues.HValues[i]->TimeLineDrawKey_CallBack(Vs.Values[i].keys, Vs.Values[i].values, Vs.Values[i].Flag, Vs.Values[i].Open);
							}
							else
							{
								std::cout << "\nError -> HValue class -> Name_ is: NULL";
							}
						}
					}
					if (ImGui::IsNeoTimelineSelected() && ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Delete))
					{
						for (size_t i = 0; i < TimeLists.size(); i++)
						{
							if (&Vs == &TimeLists[i])
							{
								TimeLists.erase(TimeLists.begin() + i);
							}
						}
					}
					ImGui::EndNeoGroup();
				}
			}

			ImGui::EndNeoSequencer();
		}
	}

	json Save()
	{
		json J, t;
		J["sf"] = startFrame;
		J["ef"] = endFrame;
		J["FPS"] = FramePerSeconds;
		J["SN"] = SequencerName;
		for (HSequencerWidgetValues& TL : TimeLists)
		{
			t.push_back(TL.Save());
		}
		J["TimeLists"] = t;
		return J;
	}

	void Load(json J)
	{
		startFrame = J["sf"];
		endFrame = J["ef"];
		FramePerSeconds = J["FPS"];
		strcpy_s(SequencerName, J["SN"].get<std::string>().c_str());
		json t = J["TimeLists"];
		for (size_t i = 0; i < t.size(); i++)
		{
			TimeLists.push_back(HSequencerWidgetValues());
			TimeLists.back().Load(t[i]);
		}
	}

	std::string GetAnimationFunctionExport()
	{
		std::string Buffer;
		Buffer += "\n#define ";
		Buffer += SequencerName;
		Buffer += "_StartFrame ";
		Buffer += std::to_string(startFrame);

		Buffer += "\n#define ";
		Buffer += SequencerName;
		Buffer += "_EndFrame ";
		Buffer += std::to_string(endFrame);

		Buffer += "\n#define ";
		Buffer += SequencerName;
		Buffer += "_FramePerSeconds ";
		Buffer += std::to_string(FramePerSeconds);

		Buffer += "\nvoid ";
		Buffer += SequencerName;
		Buffer += "(int32_t Frame)\n{\n";
		for (HSequencerWidgetValues& Tl : TimeLists)
		{
			Buffer.append(Tl.GetExportCode());
		}
		Buffer += "\n}\n";

		return Buffer;
	}

	std::string RenameVerify(std::string Name);

	bool empty()
	{
		for (HSequencerWidgetValues &v: TimeLists)
		{
			if (!v.empty())
			{
				return false;
			}
		}
		return true;
	}


	void clear()
	{
		for (HSequencerWidgetValues& v : TimeLists)
		{
			v.clear();
		}
	}
};
//Sequencer Var

//static HAnimationSequencer* CurrentSequencer = 0;
static std::vector<HAnimationSequencer>* SequencerLists = 0;

std::string HAnimationSequencer::RenameVerify(std::string Name)
{
	bool isFind = false;
	int index = 0;
	std::replace(Name.begin(), Name.end(), ' ', '_');
	std::string NameBuffer = Name;
	do
	{
		isFind = false;
		for (HAnimationSequencer& SL : *SequencerLists)
		{
			if (SL.SequencerName == NameBuffer && &SL != this)
			{
				isFind = true;
				NameBuffer = Name;
				NameBuffer.append("_").append(std::to_string(index));
				std::cout << "\n HAnimationSequencer::RenameVerify : " << NameBuffer;
				index++;
			}
		}
	} while (isFind);
	return NameBuffer;
}

static void WidgetRemoveTimeLine_CallBack(HWidget* Widget)
{
	for (HAnimationSequencer& Sequencer : *SequencerLists)
	{
		size_t index = 0;
		for (HSequencerWidgetValues& Values : Sequencer.TimeLists)
		{
			if (Values.WidgetTarget == Widget)
			{
				Values.clear();
				Sequencer.TimeLists.erase(Sequencer.TimeLists.begin() + index);
			}
			index++;
		}
	}
}

static void TimeLineAddFrame_CallBack(HWidget* Widget, HValue* Value)
{
	std::cout << "\n log - > Add Frame -> Widget :" << std::hex << Widget;
	std::cout << "    ---    Value :" << std::hex << Value;
	//Try to find this widget and value in time lines
	int isFind = 0;//This is flag  e.g. 0 = not find   1 = Only find the widget   2 = is find
	for (HSequencerWidgetValues& Values : ((HAnimationSequencer*)HAnimation::CurrentSequencer)->TimeLists)
	{
		if (Values.WidgetTarget == Widget)
		{
			isFind = 1;
			for (HSequencerValue& V : Values.Values)
			{
				if (V.TargetHValue == Value)
				{
					isFind = 2;
					bool IsFindFrame = false;
					for (size_t i = 0; i < V.keys.size(); i++)
					{
						if (V.keys.at(i) == HAnimation::CurrentSequenFrame)
						{
							IsFindFrame = true;
							//memory leak
							// 
							//void** ValueBuffer = &V.values.at(i);
							//if (*ValueBuffer)
							//	delete* ValueBuffer;
							HValue* HVBuffer = V.TargetHValue->CreateSelf("");
							HVBuffer->Load(Value->Save());
							//*ValueBuffer = HVBuffer->Data;
							V.values.at(i) = HVBuffer->Data;
							HVBuffer->Data = 0;
							delete HVBuffer;
							std::cout << "\nlog->HAnimationSequencerPanel.h->TimeLineAddFrame_CallBack ->Successfully replaced the current frame";
							return;
						}
					}
					if (!IsFindFrame)
					{
						V.keys.push_back(HAnimation::CurrentSequenFrame);
						HValue* HVBuffer = V.TargetHValue->CreateSelf("");
						HVBuffer->Load(Value->Save());
						V.values.push_back(HVBuffer->Data);
						HVBuffer->Data = 0;
						delete HVBuffer;
						std::cout << "\nlog->HAnimationSequencerPanel.h->TimeLineAddFrame_CallBack ->The widget exists and Create a current frame";
						return;
					}
				}
			}
		}
	}
	if (isFind == 0)
	{
		std::vector<HSequencerWidgetValues>* TimeLines = &((HAnimationSequencer*)HAnimation::CurrentSequencer)->TimeLists;
		HSequencerWidgetValues Values;
		Values.WidgetTarget = Widget;
		for (HValue* WV : Widget->HValues.HValues)
		{
			HSequencerValue ValueBuffer;
			if (WV == Value)
			{
				ValueBuffer.keys.push_back(HAnimation::CurrentSequenFrame);
				HValue* HVBuffer = Value->CreateSelf("");
				HVBuffer->Load(Value->Save());
				ValueBuffer.values.push_back(&HVBuffer->Data);
				HVBuffer->Data = 0;
				delete HVBuffer;
			}
			ValueBuffer.TargetHValue = WV;
			Values.Values.push_back(ValueBuffer);
		}

		TimeLines->push_back(Values);
		std::cout << "\nlog->HAnimationSequencerPanel.h->TimeLineAddFrame_CallBack ->Create widgets and frames";
		return;
	}
	else if (isFind == 1)
	{
		std::cout << "\n HAnimationSequencerPath.h - > TimeLineAddFrame_CallBack-> Error ->  Only find the widget";
	}
}
static std::string GetWidgetName_CallBack(HWidget* Widget)
{
	return *Widget->WidgetName;
}
static void InitAnimationSequencer()
{
	HAnimation::WidgetRemoveTimeLine = WidgetRemoveTimeLine_CallBack;
	HAnimation::TimeLineAddFrame = TimeLineAddFrame_CallBack;
	HAnimation::GetWidgetName = GetWidgetName_CallBack;
}

static void DrawAnimationSequencerList()
{
	if (ImGui::Begin("AnimationSequencerList"))
	{
		if (ImGui::Button(" + ###AddAnimationSequencer"))
		{
			SequencerLists->push_back(HAnimationSequencer());
			HAnimation::CurrentSequencer = &SequencerLists->back();
		}
		ImGui::Separator();
		if (ImGui::Selectable("None###NoneHAnimationSequencer", (HAnimation::CurrentSequencer == NULL)))
		{
			HAnimation::CurrentSequencer = NULL;
		}
		for (HAnimationSequencer& Sequencer : *SequencerLists)
		{
			if (&Sequencer == HAnimation::CurrentSequencer)
			{
				ImGui::Selectable(Sequencer.SequencerName, true,0,ImVec2(ImGui::GetWindowWidth()-50,0));
				ImGui::SameLine();
				if (ImGui::Button(std::string(" x ###Remove").append(std::to_string((int)&Sequencer)).c_str()))
				{
					for (size_t i = 0; i < SequencerLists->size(); i++)
					{
						if (&Sequencer == &SequencerLists->at(i))
						{
							Sequencer.clear();
							SequencerLists->erase(SequencerLists->begin() + i);
							if (!SequencerLists->empty())
							{
								if (i+1 < SequencerLists->size())
								{
									HAnimation::CurrentSequencer = &SequencerLists->at(i + 1);
								}
								else
								{
									HAnimation::CurrentSequencer = &SequencerLists->front();
								}
							}
							else
							{
								HAnimation::CurrentSequencer = 0;
							}
						}
					}
				}
			}
			else
			{
				if (ImGui::Selectable(Sequencer.SequencerName))
				{
					HAnimation::CurrentSequencer = &Sequencer;
				}
			}
		}
	}
	ImGui::End();
	if (ImGui::Begin("AnimationSequencer"))
	{
		if (HAnimation::CurrentSequencer)
		{
			((HAnimationSequencer*)HAnimation::CurrentSequencer)->Draw();
		}
	}
	ImGui::End();
}