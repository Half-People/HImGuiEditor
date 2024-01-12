> # The current situation
> Recently, due to academic problems, the project update date will be postponed. sorry

[Discord](https://discord.gg/JpkSc6EJQ7)

Wiki
---------------------------------------
[Wiki](https://github.com/Half-People/HImGuiEditor/wiki)

Download
----------------------------------------
[Download Release](https://github.com/Half-People/HImGuiEditor/releases)

Contents
----------------------------------------
- Built-in translation function can translate more than 100 languages
- Visual ImGui editing
- Visual ImGui editing is not just free to set.Can be arranged in the style of ImGui (Use it the way ImGui wants it to be used)
- Have plugin system (You can use the third-party ImGui library)
- All-in-one storage system (only one file is required .Saved all project content)
- It can be directly exported as a VisualStudio project .Automatically configure lib inculde... (Just open the project run and it will be successful)
- Animation System 

![ezgif-2-1adf2f309b](https://github.com/Half-People/HImGuiEditor/assets/56476339/50228b87-e047-415b-abb3-467839e6ad41)

how to use ?!
----------------------------------------
1.Setup Porject And Style

![ezgif-3-d55757c0af](https://github.com/Half-People/HImGuiEditor/assets/56476339/f12415b6-0b2a-4ebb-ae21-552c54493cba)


2.Edit your ui

![ezgif-3-b87597a306](https://github.com/Half-People/HImGuiEditor/assets/56476339/b07e63cb-227b-4625-a4b2-faf50446841c)

3.Export and build

Future Ideas
----------------------------------------


> - Future Ideas Development premise :
> - The number of users increases (maybe 60Star) or I have nothing to do

- [ ] Add other underlying rendering methods (OpenGL - SDL)
- [ ] Add other underlying rendering methods (Vulkan - GLFW)
- [ ] Add other underlying rendering methods (Vulkan - SDL)
- [ ] Add `Widget` creation tools (Use low-level methods)
- [x] Organize and optimize the output project file structure
- [ ] Add `Nod Editor` to interact with `Widget` (using `node` to codeing `c++`)
- [x] Add animation system
- [ ] Add post processing

Update schedule
-------------------------------------
1. Update HVString ID flashing bug in widget (Need to update files `HValue.h` , `DefaultWidget.h`)
2. Update Translation function cannot be used Bug (Need to update files `HTranslation.h`) least important

# Why we develop this product.

 The purpose is to make editing
 ImGui clearer and easier for users.
 thus speeding up development

# APIs
I'm not very familiar with Github so I can't pull the API directly into my project

The following are the APIs used
------------------------------------------------------------------------

[CURL  The call I use to make the translation function](https://curl.se/)

[GLEW  I used to create OpenGL](https://glew.sourceforge.net/)

[GLFW  I use for window creation](https://www.glfw.org/)

[JSON  I use in project save and translation cache](https://json.nlohmann.me/)

[stb_image I use image loading](https://github.com/nothings/stb/blob/master/stb_image.h)

[lz4 I use in Image compression when saving](https://github.com/lz4/lz4)

[ClipboardXX for simple code copying](https://github.com/Arian8j2/ClipboardXX)

There is also imgui API in the project
--------------------------------------------------------------------------

[ImGui](https://github.com/ocornut/imgui)

[ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit)
