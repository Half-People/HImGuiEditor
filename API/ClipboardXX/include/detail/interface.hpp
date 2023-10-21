#pragma once

#include <string>

namespace clipboardxx {

class ClipboardInterface {
public:
    virtual ~ClipboardInterface() = default;
    virtual void copy(const std::string &text) const = 0;
    virtual std::string paste() const = 0;
};

} // namespace clipboardxx
