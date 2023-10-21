# im-neo-sequencer

## Description
Im-neo-sequencer is my own implementation if animation sequencer for imgui, it was made for my friend who is making his own engine and wasn't happy with [imsequencer](https://github.com/CedricGuillemet/ImGuizmo). Right now it only supports keyframe animations with single frame keyframes, but I'm open for more development in future.  

## Visuals
![im-neo-sequencer](screenshots/screenshot.png "Basic im-nep-sequencer")

## Installation
Its just drag and drop to your project, maybe fix includes but thats all there is to it

## Usage
Using im-neo-sequencer is simple and should follow ImGui API style   
To create empty sequencer we use Begin and End functions:

```cpp
    int32_t currentFrame = 0;
    int32_t startFrame = -10;
    int32_t endFrame = 64;

    if(ImGui::BeginNeoSequencer("Sequencer", &currentFrame, &startFrame, &endFrame)) {
        // Timeline code here
        ImGui::EndNeoSequencer();
    }
```

To add timeline, you either use BeginNeoTimeline or if you want collapsable Timeline you can use BeginNeoGroup:

```cpp
    int32_t currentFrame = 0;
        int32_t startFrame = -10;
        int32_t endFrame = 64;
        static bool transformOpen = false;

        if(ImGui::BeginNeoSequencer("Sequencer", &currentFrame, &startFrame, &endFrame)) {
            if(ImGui::BeginNeoGroup("Transform",&transformOpen)) {
                std::vector<ImGui::FrameIndexType> keys = {0, 10, 24};
                if(ImGui::BeginNeoTimeline("Position", keys )) {
                    ImGui::EndNeoTimeLine();
                }
                ImGui::EndNeoGroup();
            }

            ImGui::EndNeoSequencer();
        }
```
NOTE: There is C interface for BeginNeoTimeline, but I use C++ one for clarity.  
NOTE: I'm planning on making im-neo-sequencer support for C soon, but now I'm using some C++ features in it (context is held in unordered_map)

There is also support for multiselect, deletion and dragging of keyframes
Simple code example below.

```cpp
    int32_t currentFrame = 0;
    int32_t startFrame = -10;
    int32_t endFrame = 64;
    static bool transformOpen = false;
    std::vector<ImGui::FrameIndexType> keys = {0, 10, 24};
    bool doDelete = false;

    if (ImGui::BeginNeoSequencer("Sequencer", &currentFrame, &startFrame, &endFrame, {0, 0},
                                 ImGuiNeoSequencerFlags_EnableSelection |
                                 ImGuiNeoSequencerFlags_Selection_EnableDragging |
                                 ImGuiNeoSequencerFlags_Selection_EnableDeletion))
    {
        if (ImGui::BeginNeoGroup("Transform", &transformOpen))
        {

            if (ImGui::BeginNeoTimelineEx("Position"))
            {
                for (auto&& v: keys)
                {
                    ImGui::NeoKeyframe(&v);
                    // Per keyframe code here
                }


                if (doDelete)
                {
                    uint32_t count = ImGui::GetNeoKeyframeSelectionSize();

                    ImGui::FrameIndexType * toRemove = new ImGui::FrameIndexType[count];

                    ImGui::GetNeoKeyframeSelection(toRemove);

                    //Delete keyframes from your structure
                }
                ImGui::EndNeoTimeLine();
            }
            ImGui::EndNeoGroup();
        }

        ImGui::EndNeoSequencer();
    }
```

## Contributing
Feel free to contribute, I'm always open for fixes and improvements

## Authors and acknowledgment
My friend [Simon Gido](https://github.com/SimonGido) who I made this project for and with.

## License
MIT

## Project status
Right now, im-neo-sequencer is in early development, I'm making breaking changes to API and it may be broken, feel free to submit your bugs.
