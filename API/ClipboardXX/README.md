# ClipboardXX
Header only lightweight library to **copy** and **paste** text from clipboard

## Example
```C++
#include <clipboardxx.hpp>
#include <string>

int main() {
    clipboardxx::clipboard clipboard;

    // copy
    clipboard << "text you wanna copy"; // or clipboard.copy("text you wanna copy")


    // paste
    std::string paste_text;
    clipboard >> paste_text; // or const std::string paste_text = clipboard.paste()
}
```

## Compatibility
What supports:
- Copy pasting utf-8 text in mentioned operating systems
- Windows
- X11 in GNU/Linux based operating systems

What **not** supports:
- MacOS
- Wayland in GNU/Linux based operating systems (maybe soon ...)
- Copy pasting other formats such as images, documents ...

## Usage

#### Windows
Nothing specially need to do, You need all files under `include` directory and then include `clipboardxx.hpp` file and you are good to go 

#### GNU/Linux
As mentioned before, Currently *ClipboardXX* only supports *X11* and needs *xcb* library and header files to communicate with it. So you need to install *xcb* with any way that you prefer. Then you need *cmake* to compile it without any hassle, just add *ClipboardXX* subdirectory in your cmake file:
```cmake
add_subdirectory(ClipboardXX)
target_link_libraries(your_target ClipboardXX)
```

## Similar projects
[clip](https://github.com/dacap/clip) (+has so many formats for copy and paste, -it's not header only)
