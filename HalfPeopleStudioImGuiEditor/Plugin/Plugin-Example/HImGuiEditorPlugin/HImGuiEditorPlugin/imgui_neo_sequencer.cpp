//Function interface
//Created by HalfPeopleStudio - HalfPeople  on 2023-10-22
//
#include "ImNeoSequenc\imgui_neo_sequencer.h"

HImguiEditorNeoSequencerFunctionInterface I;

extern "C" __declspec(dllexport) void UpdataNeoSequencerFunction(
    const ImVec4 & (*GetStyleNeoSequencerColorVec4)(ImGuiNeoSequencerCol idx),
    ImGuiNeoSequencerStyle & (*GetNeoSequencerStyle)(),
    void (*PushNeoSequencerStyleColor)(ImGuiNeoSequencerCol idx, ImU32 col),
    void (*PopNeoSequencerStyleColor)(int count),
    bool (*BeginNeoSequencer)(const char* id, ImGui::FrameIndexType * frame, ImGui::FrameIndexType * startFrame, ImGui::FrameIndexType * endFrame, const ImVec2 & size, ImGuiNeoSequencerFlags flags),
    void (*EndNeoSequencer)(),
    bool (*BeginNeoGroup)(const char* label, bool* open),
    void (*EndNeoGroup)(),
    bool (*BeginNeoTimeline)(const char* label, ImGui::FrameIndexType * *keyframes, uint32_t keyframeCount, bool* open, ImGuiNeoTimelineFlags flags),
    void (*EndNeoTimeLine)(),
    bool (*BeginNeoTimelineEx)(const char* label, bool* open, ImGuiNeoTimelineFlags flags),
    void (*NeoKeyframe)(int32_t * value),
    bool (*IsNeoKeyframeHovered)(),
    bool (*IsNeoKeyframeSelected)(),
    bool (*IsNeoKeyframeRightClicked)(),
    void (*NeoClearSelection)(),
    bool (*NeoIsSelecting)(),
    bool (*NeoHasSelection)(),
    bool (*NeoIsDraggingSelection)(),
    bool (*NeoCanDeleteSelection)(),
    bool (*IsNeoKeyframeSelectionRightClicked)(),
    uint32_t(*GetNeoKeyframeSelectionSize)(),
    void (*GetNeoKeyframeSelection)(ImGui::FrameIndexType * selection),
    void (*SetSelectedTimeline)(const char* timelineLabel),
    bool (*IsNeoTimelineSelected)(ImGuiNeoTimelineIsSelectedFlags flags)
)
{
   I. GetStyleNeoSequencerColorVec4= GetStyleNeoSequencerColorVec4                                               ;
       I.GetNeoSequencerStyle = GetNeoSequencerStyle                                                             ;
       I.PushNeoSequencerStyleColor = PushNeoSequencerStyleColor                                                 ;                                    
       I.PopNeoSequencerStyleColor = PopNeoSequencerStyleColor                                                   ;
       I.BeginNeoSequencer = BeginNeoSequencer                                                                   ;
       I.EndNeoSequencer = EndNeoSequencer                                                                       ;
       I.BeginNeoGroup = BeginNeoGroup                                                                           ;
       I.EndNeoGroup = EndNeoGroup                                                                               ;
       I.BeginNeoTimeline = BeginNeoTimeline                                                                     ;
       I.EndNeoTimeLine = EndNeoTimeLine                                                                         ;
       I.BeginNeoTimelineEx = BeginNeoTimelineEx                                                                 ;
       I.NeoKeyframe = NeoKeyframe                                                                               ;
       I.IsNeoKeyframeHovered = IsNeoKeyframeHovered                                                             ;
       I.IsNeoKeyframeSelected = IsNeoKeyframeSelected                                                           ;
       I.IsNeoKeyframeRightClicked = IsNeoKeyframeRightClicked                                                   ;
       I.NeoClearSelection = NeoClearSelection                                                                   ;
       I.NeoIsSelecting = NeoIsSelecting                                                                         ;
       I.NeoHasSelection = NeoHasSelection                                                                       ;
       I.NeoIsDraggingSelection = NeoIsDraggingSelection                                                         ;
       I.NeoCanDeleteSelection = NeoCanDeleteSelection                                                           ;
       I.IsNeoKeyframeSelectionRightClicked = IsNeoKeyframeSelectionRightClicked                                 ;
       I.GetNeoKeyframeSelectionSize = GetNeoKeyframeSelectionSize                                               ;
       I.GetNeoKeyframeSelection = GetNeoKeyframeSelection                                                       ;
       I.SetSelectedTimeline = SetSelectedTimeline                                                               ;
       I.IsNeoTimelineSelected = IsNeoTimelineSelected                                                           ;
}

 const ImVec4& ImGui::GetStyleNeoSequencerColorVec4(ImGuiNeoSequencerCol idx)
{
     return I.GetStyleNeoSequencerColorVec4(idx);
}

 ImGuiNeoSequencerStyle& ImGui::GetNeoSequencerStyle()
{
     return I.GetNeoSequencerStyle();
}

 void ImGui::PushNeoSequencerStyleColor(ImGuiNeoSequencerCol idx, ImU32 col)
{
     return I.PushNeoSequencerStyleColor(idx, col);
}

 void ImGui::PushNeoSequencerStyleColor(ImGuiNeoSequencerCol idx, const ImVec4& col)
{
    return I.PushNeoSequencerStyleColor(idx, ImColor(col));
}

 void ImGui::PopNeoSequencerStyleColor(int count)
{
     return I.PopNeoSequencerStyleColor(count);
}

 bool ImGui::BeginNeoSequencer(const char* id, FrameIndexType* frame, FrameIndexType* startFrame, FrameIndexType* endFrame, const ImVec2& size, ImGuiNeoSequencerFlags flags)
{
     return I.BeginNeoSequencer(id, frame, startFrame, endFrame, size, flags);
}

 void ImGui::EndNeoSequencer()
{
     return  I.EndNeoSequencer();
}

bool ImGui::BeginNeoGroup(const char* label, bool* open)
{
    return I.BeginNeoGroup(label, open);
}

void ImGui::EndNeoGroup()
{
    I.EndNeoGroup();
}

uint32_t ImGui::GetNeoKeyframeSelectionSize()
{
    return I.GetNeoKeyframeSelectionSize();
}

void ImGui::GetNeoKeyframeSelection(FrameIndexType* selection)
{
    return I.GetNeoKeyframeSelection(selection);
}

void ImGui::SetSelectedTimeline(const char* timelineLabel)
{
    I.SetSelectedTimeline(timelineLabel);
}

bool ImGui::IsNeoTimelineSelected(ImGuiNeoTimelineIsSelectedFlags flags)
{
    return I.IsNeoTimelineSelected(flags);
}


bool ImGui::BeginNeoTimeline(const char* label, FrameIndexType** keyframes, uint32_t keyframeCount, bool* open, ImGuiNeoTimelineFlags flags)
{
    return I.BeginNeoTimeline(label,keyframes,keyframeCount,open,flags);
}

void ImGui::EndNeoTimeLine()
{
    return I.EndNeoTimeLine();
}

bool ImGui::BeginNeoTimelineEx(const char* label, bool* open, ImGuiNeoTimelineFlags flags)
{
    return I.BeginNeoTimelineEx(label,open,flags);
}

void ImGui::NeoKeyframe(int32_t* value)
{
    return I.NeoKeyframe(value);
}

bool ImGui::IsNeoKeyframeHovered()
{
    return I.IsNeoKeyframeHovered();
}

bool ImGui::IsNeoKeyframeSelected()
{
    return I.IsNeoKeyframeSelected();
}

bool ImGui::IsNeoKeyframeRightClicked()
{
    return I.IsNeoKeyframeRightClicked();
}

void ImGui::NeoClearSelection()
{
    I.NeoClearSelection();
}

bool ImGui::NeoIsSelecting()
{
    return I.NeoIsSelecting();
}

bool ImGui::NeoHasSelection()
{
    return I.NeoHasSelection();
}

bool ImGui::NeoIsDraggingSelection()
{
    return I.NeoIsDraggingSelection();
}

bool ImGui::NeoCanDeleteSelection()
{
    return I.NeoCanDeleteSelection();
}

bool ImGui::IsNeoKeyframeSelectionRightClicked()
{
    return I.IsNeoKeyframeSelectionRightClicked();
}
