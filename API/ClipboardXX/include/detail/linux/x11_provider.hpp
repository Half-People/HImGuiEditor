#pragma once

#include "../exception.hpp"
#include "provider.hpp"
#include "x11_event_handler.hpp"
#include "xcb/xcb.hpp"

#include <memory>

namespace clipboardxx {

constexpr const char* kClipboardAtomName = "CLIPBOARD";

class X11Provider : public LinuxClipboardProvider {
public:
    X11Provider()
        : m_xcb(std::make_shared<xcb::Xcb>()), m_clipboard_atom(m_xcb->create_atom(kClipboardAtomName)),
          m_event_handler(X11EventHandler(m_xcb)) {}

    void copy(const std::string &text) override {
        m_xcb->become_selection_owner(m_clipboard_atom);
        m_event_handler.set_copy_data(text);
    }

    std::string paste() override { return m_event_handler.get_paste_data(); }

private:
    const std::shared_ptr<xcb::Xcb> m_xcb;
    const xcb::Xcb::Atom m_clipboard_atom;
    X11EventHandler m_event_handler;
};

} // namespace clipboardxx
