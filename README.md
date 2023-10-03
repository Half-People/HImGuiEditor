
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
- Visual ImGui editing is not just free to set.Can be arranged in the style of ImGui
- Have plugin system (You can use the third-party ImGui library)
- All-in-one storage system (only one file is required .Saved all project content)
- It can be directly exported as a VisualStudio project .Automatically configure lib inculde... (Just open the project run and it will be successful)

 ![image](https://user-images.githubusercontent.com/56476339/218198311-d9673fe5-d839-4fdb-8487-0bb8fa448c91.gif)

Future Ideas
----------------------------------------


> - Future Ideas Development premise :
> - The number of users increases (maybe 60Star) or I have nothing to do

- [ ] Add other underlying rendering methods (OpenGL - SDL)
- [ ] Add other underlying rendering methods (Vulkan - GLFW)
- [ ] Add other underlying rendering methods (Vulkan - SDL)
- [ ] Add `Widget` creation tools (Use low-level methods)
- [ ] Organize and optimize the output project file structure   ---90%
- [ ] Add `Nod Editor` to interact with `Widget`
- [ ] Add animation system

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

There is also imgui API in the project
--------------------------------------------------------------------------

[ImGui](https://github.com/ocornut/imgui)

[ImGuiColorTextEdit](https://github.com/BalazsJako/ImGuiColorTextEdit)
