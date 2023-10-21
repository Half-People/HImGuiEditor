#pragma once

#include <string>

namespace clipboardxx {

class LinuxClipboardProvider {
public:
    virtual void copy(const std::string &text) = 0;
    virtual std::string paste() = 0;
    virtual ~LinuxClipboardProvider() = default;
};

} // namespace clipboardxx
