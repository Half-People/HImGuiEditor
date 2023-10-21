#pragma once

#include "exception.hpp"
#include "interface.hpp"

#include <memory>
#include <string>

#ifdef WINDOWS
    #include <windows.h>

namespace clipboardxx {

class ClipboardWindows : public ClipboardInterface {
public:
    void copy(const std::string &text) const override {
        OpenCloseClipboardRaii clipboard_raii;

        empty_clipboard();
        std::unique_ptr<char, WindowsPtrDeleter> buffer = allocate_memory_with_size(text.size() + 1);
        write_string_to_memory_null_terminated(text, buffer.get());
        set_clipboard_data_from_memory(std::move(buffer));
    }

    std::string paste() const noexcept override {
        OpenCloseClipboardRaii clipboard_raii;
        return get_clipboard_data();
    }

private:
    class OpenCloseClipboardRaii {
    public:
        OpenCloseClipboardRaii() {
            if (!OpenClipboard(0))
                throw WindowsException("Cannot open clipboard");
        }

        ~OpenCloseClipboardRaii() { CloseClipboard(); }
    };

    class WindowsException : public exception {
    public:
        WindowsException(const std::string &reason) : exception(reason + " (" + get_last_windows_error() + ")"){};

    private:
        std::string get_last_windows_error() const {
            DWORD error = GetLastError();
            if (error) {
                LPVOID buffer = nullptr;
                DWORD buffer_len = FormatMessage(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    nullptr, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPTSTR>(&buffer), 0, nullptr);

                if (buffer_len) {
                    LPTSTR buffer_char = reinterpret_cast<LPTSTR>(buffer);
                    std::string result(buffer_char, buffer_char + buffer_len);
                    LocalFree(buffer);
                    return result;
                }
            }

            return std::string("unknown windows error");
        }
    };

    class WindowsPtrDeleter {
    public:
        void operator()(char* ptr) { GlobalFree(ptr); }
    };

    void empty_clipboard() const {
        BOOL succeed = EmptyClipboard();
        if (!succeed)
            throw WindowsException("Cannot empty clipboard");
    }

    std::unique_ptr<char, WindowsPtrDeleter> allocate_memory_with_size(size_t size) const {
        std::unique_ptr<char, WindowsPtrDeleter> global(
            reinterpret_cast<char*>(GlobalAlloc(GMEM_FIXED, sizeof(char) * size)));
        if (!global)
            throw WindowsException("Cannot allocate memory for copying text");

        return global;
    }

    void write_string_to_memory_null_terminated(const std::string &text, char* memory) const {
        std::copy(text.begin(), text.end(), memory);
        memory[text.size()] = '\0';
    }

    void set_clipboard_data_from_memory(std::unique_ptr<char, WindowsPtrDeleter> buffer) const {
        if (SetClipboardData(CF_TEXT, buffer.get())) {
            // from now on the system owns the buffer
            buffer.release();
        } else {
            throw WindowsException("Cannot set clipboard data");
        }
    }

    std::string get_clipboard_data() const {
        char* result = reinterpret_cast<char*>(GetClipboardData(CF_TEXT));
        if (!result)
            return std::string("");
        return std::string(result);
    }
};

} // namespace clipboardxx

#endif
