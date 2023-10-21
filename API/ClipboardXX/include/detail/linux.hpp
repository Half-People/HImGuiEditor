#pragma once

#ifdef LINUX
    #include "exception.hpp"
    #include "interface.hpp"
    #include "linux/x11_provider.hpp"

namespace clipboardxx {

class ClipboardLinux : public ClipboardInterface {
public:
    ClipboardLinux() : m_provider(std::make_unique<X11Provider>()) {}

    void copy(const std::string &text) const override {
        try {
            m_provider->copy(text);
        } catch (const exception &error) {
            throw exception("XCB Error: " + std::string(error.what()));
        }
    }

    std::string paste() const override { return m_provider->paste(); }

private:
    const std::unique_ptr<LinuxClipboardProvider> m_provider;
};

} // namespace clipboardxx

#endif
