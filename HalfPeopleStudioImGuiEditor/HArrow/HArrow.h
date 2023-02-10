#pragma once
#include <imgui_internal.h>
#define H_MAX(a,b)            (((a) > (b)) ? (a) : (b))
//static float Clamp(float In, float Max, float Min)
//{
//	if (In > Max)
//		return Max;
//	if (In < Min)
//		return Min;
//	return In;
//}

static void HBorder(const char* ID, const ImVec4& col, const ImVec2& size_arg, float rounding = 1)
{
	ImGuiWindow* Windows = ImGui::GetCurrentWindow();
	if (Windows->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	ImGuiID id = Windows->GetID(ID);
	const float default_size = ImGui::GetFrameHeight();
	const ImVec2 size(size_arg.x == 0.0f ? default_size : size_arg.x, size_arg.y == 0.0f ? default_size : size_arg.y);
	const ImRect bb(Windows->DC.CursorPos, ImVec2(Windows->DC.CursorPos.x + size.x, Windows->DC.CursorPos.y + size.y));
	ImGui::ItemSize(bb, (size.y >= default_size) ? g.Style.FramePadding.y : 0.0f);
	if (!ImGui::ItemAdd(bb, id))
		return;

	Windows->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(col), rounding);
}

enum HArrow_SizeFlag
{
	HArrow_SizeFlag_NotResize,
	HArrow_SizeFlag_OnlyX,
	HArrow_SizeFlag_Default
};

static bool HArrow(ImVec2& pos, int Positioning)
{
	ImGuiContext& g = *GImGui;

	ImVec2 SaveStartPos;
	ImVec2 SaveSize;
	static ImVec2 Offset;
	static bool NeedUpdata;
	static int Mode = -1;
	static bool CanUpdata = true;
	ImGuiWindow* Windows = ImGui::GetCurrentWindow();

	if (g.IO.MouseDown[0])
	{
		if (NeedUpdata)
		{
			SaveStartPos = ImGui::GetWindowPos();
			SaveSize = ImGui::GetMousePos();
			Offset = ImVec2((pos.x + SaveStartPos.x) - SaveSize.x, (pos.y + SaveStartPos.y) - SaveSize.y);
			NeedUpdata = false;
		}
	}
	else
	{
		Mode = -1;
		NeedUpdata = true;
		CanUpdata = true;
	}

	SaveStartPos = pos;

	SaveSize = ImGui::GetItemRectSize();
	SaveStartPos.x += SaveSize.x / 2;
	SaveStartPos.y += (SaveSize.y / 2);

	ImGui::SetCursorPos(ImVec2(SaveStartPos.x + 9, SaveStartPos.y - 3));
	HBorder("###X", ImColor(255, 0, 0), ImVec2(41, 8));
	if (CanUpdata && g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect)
	{
		Mode = 0;
		Windows->Flags |= ImGuiWindowFlags_NoMove;
	}


	ImGui::SetCursorPos(ImVec2(SaveStartPos.x - 3, SaveStartPos.y - 41));
	HBorder("###Y", ImColor(0, 255, 0), ImVec2(8, 41));
	if (CanUpdata && g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect)
	{
		Mode = 1;
		Windows->Flags |= ImGuiWindowFlags_NoMove;
	}

	ImGui::SetCursorPos(ImVec2(SaveStartPos.x - 9, SaveStartPos.y - 9));
	HBorder("###Auto", ImColor(255, 255, 255), ImVec2(18, 18));
	if (CanUpdata && g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect)
	{
		Mode = 2;
		Windows->Flags |= ImGuiWindowFlags_NoMove;
	}


	//if (ImGui::IsMouseDragging(0) && (!NeedUpdata) )
	if (!NeedUpdata)
	{


		if (ImGui::IsMouseDragging(0))
		{
			ImVec2 MousePos = ImGui::GetMousePos();
			ImVec2 WinPos = ImGui::GetWindowPos();
			CanUpdata = false;

				ImVec2 WindowSize = ImGui::GetWindowSize();
			if (Positioning)
			{
				ImDrawList* DL = ImGui::GetWindowDrawList();

				for (size_t X = 0; X < WindowSize.x / Positioning; X++)
				{
					float XP = (X * Positioning) + WinPos.x + SaveSize.x / 2;
					DL->AddLine(ImVec2(XP, WinPos.y), ImVec2(XP, WindowSize.y + WinPos.y), ImColor(255, 255, 255, 40));
				}
				for (size_t Y = 0; Y < WindowSize.y / Positioning; Y++)
				{
					float YP = (Y * Positioning) + WinPos.y + SaveSize.y / 2;
					DL->AddLine(ImVec2(WinPos.x, YP), ImVec2(WindowSize.x + WinPos.x, YP), ImColor(255, 255, 255, 40));
				}

			}



			if (Mode == 0)//x
			{
				MousePos.x -= WinPos.x;
				if (Positioning)
				{
					pos.x = ((int)(MousePos.x + Offset.x) / Positioning) * Positioning;
				}
				else
				{
					pos.x = MousePos.x + Offset.x;
				}
			}
			else if (Mode == 1)//y
			{
				MousePos.y -= WinPos.y;
				if (Positioning)
				{
					pos.y = ((int)(MousePos.y + Offset.y) / Positioning) * Positioning;
				}
				else
				{
					pos.y = MousePos.y + Offset.y;
				}
			}
			else if (Mode == 2)//x and y
			{
				MousePos.x -= WinPos.x;
				MousePos.y -= WinPos.y;
				if (Positioning)
				{
					pos.x = ((int)(MousePos.x + Offset.x) / Positioning) * Positioning;
					pos.y = ((int)(MousePos.y + Offset.y) / Positioning) * Positioning;
				}
				else
				{
					pos.x = MousePos.x + Offset.x;
					pos.y = MousePos.y + Offset.y;
				}
			}
			return true;
		}

	}

	return false;

}

static void HResize(ImVec2 WidgetPos,ImVec2& size, int Positioning, HArrow_SizeFlag Flag)
{
	if (Flag == HArrow_SizeFlag_NotResize)
		return;

	ImGuiContext& g = *GImGui;

	ImVec2 SaveStartPos;
	ImVec2 SaveSize;
	static bool NeedUpdata;
	static int Mode = -1;
	static bool CanUpdata = true;
	ImGuiWindow* Windows = ImGui::GetCurrentWindow();

	if (g.IO.MouseDown[0])
	{
		if (NeedUpdata)
		{
			NeedUpdata = false;
		}
	}
	else
	{
		Mode = -1;
		NeedUpdata = true;
		CanUpdata = true;
	}

	SaveStartPos = WidgetPos;

	SaveSize = ImGui::GetItemRectSize();
	SaveStartPos.x += SaveSize.x-5;
	SaveStartPos.y += SaveSize.y-5;


	if (Flag == HArrow_SizeFlag_Default)
	{
		ImGui::SetCursorPos(SaveStartPos);
		HBorder("##SizeAuto", ImColor(200, 200, 200), ImVec2(10, 10));
		if (CanUpdata && g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect)
		{
			Mode = 0;
			Windows->Flags |= ImGuiWindowFlags_NoMove;
		}

		ImGui::SetCursorPos(ImVec2(SaveStartPos.x,WidgetPos.y + (SaveSize.y/2 -5)));
		HBorder("##SizeX", ImColor(200, 200, 200), ImVec2(10, 10));
		if (CanUpdata && g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect)
		{
			Mode = 1;
			Windows->Flags |= ImGuiWindowFlags_NoMove;
		}

		ImGui::SetCursorPos(ImVec2(WidgetPos.x + (SaveSize.x/2 - 5),SaveStartPos.y));
		HBorder("##SizeY", ImColor(200, 200, 200), ImVec2(10, 10));
		if (CanUpdata && g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect)
		{
			Mode = 2;
			Windows->Flags |= ImGuiWindowFlags_NoMove;
		}

	}
	else
	{
		ImGui::SetCursorPos(ImVec2(SaveStartPos.x, WidgetPos.y + (SaveSize.y / 2 - 5)));
		HBorder("##SizeX", ImColor(200, 200, 200), ImVec2(10, 10));
		if (CanUpdata && g.LastItemData.StatusFlags & ImGuiItemStatusFlags_HoveredRect)
		{
			Mode = 1;
			Windows->Flags |= ImGuiWindowFlags_NoMove;
		}
	}



	if (!NeedUpdata)
	{
		if (ImGui::IsMouseDragging(0))
		{
			ImVec2 MousePos = ImGui::GetMousePos();
			ImVec2 WinPos = ImGui::GetWindowPos();
			CanUpdata = false;

			ImVec2 WindowSize = ImGui::GetWindowSize();
			if (Positioning)
			{
				ImDrawList* DL = ImGui::GetWindowDrawList();

				for (size_t X = 0; X < WindowSize.x / Positioning; X++)
				{
					float XP = (X * Positioning) + WinPos.x + WidgetPos.x ;
					DL->AddLine(ImVec2(XP, WinPos.y), ImVec2(XP, WindowSize.y + WinPos.y), ImColor(255, 255, 255, 40));
				}
				for (size_t Y = 0; Y < WindowSize.y / Positioning; Y++)
				{
					float YP = (Y * Positioning) + WinPos.y + WidgetPos.y ;
					DL->AddLine(ImVec2(WinPos.x, YP), ImVec2(WindowSize.x + WinPos.x, YP), ImColor(255, 255, 255, 40));
				}
			}



			if (Mode == 0)//x and y
			{
				MousePos.y -= WinPos.y + WidgetPos.y; 
				MousePos.x -= WinPos.x + WidgetPos.x;
				if (Positioning)
				{
					size.x = H_MAX(0,((int)(MousePos.x) / Positioning)* Positioning);
					size.y = H_MAX(0,((int)(MousePos.y) / Positioning) * Positioning);
				}
				else
				{
					size.x = H_MAX(0,MousePos.x);
					size.y = H_MAX(0,MousePos.y);
				}
			}
			else if (Mode == 1)//x 
			{
				//MousePos.y -= WinPos.y + WidgetPos.y;
				MousePos.x -= WinPos.x + WidgetPos.x;
				if (Positioning)
				{
					size.x = H_MAX(0, ((int)(MousePos.x) / Positioning) * Positioning);
					//size.y = H_MAX(0, ((int)(MousePos.y) / Positioning) * Positioning);
				}
				else
				{
					size.x = H_MAX(0, MousePos.x);
					//size.y = H_MAX(0, MousePos.y);
				}
			}
			else if (Mode == 2)// y
			{
				MousePos.y -= WinPos.y + WidgetPos.y;
				//MousePos.x -= WinPos.x + WidgetPos.x;
				if (Positioning)
				{
					//size.x = H_MAX(0, ((int)(MousePos.x) / Positioning) * Positioning);
					size.y = H_MAX(0, ((int)(MousePos.y) / Positioning) * Positioning);
				}
				else
				{
					//size.x = H_MAX(0, MousePos.x);
					size.y = H_MAX(0, MousePos.y);
				}
			}
		}

	}
}