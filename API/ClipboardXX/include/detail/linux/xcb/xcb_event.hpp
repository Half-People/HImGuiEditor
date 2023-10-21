#pragma once

#include <xcb/xcb.h>

namespace clipboardxx {
namespace xcb {

using Atom = xcb_atom_t;
using Window = xcb_window_t;

class Event {
public:
    enum Type { kNone = 0, kRequestSelection, kSelectionClear, kSelectionNotify };

    Event(Type type) : m_type(type) {}

    Type get_type() const { return m_type; }

private:
    Type m_type;
};

class RequestSelectionEvent : public Event {
public:
    RequestSelectionEvent(Window requestor, Window owner, Atom selection, Atom target, Atom property)
        : Event(Type::kRequestSelection), m_requestor(requestor), m_owner(owner), m_selection(selection),
          m_target(target), m_property(property) {}

    const Window m_requestor, m_owner;
    const Atom m_selection, m_target, m_property;
};

class SelectionNotifyEvent : public Event {
public:
    SelectionNotifyEvent(Window requestor, Atom selection, Atom target, Atom property)
        : Event(Type::kSelectionNotify), m_requestor(requestor), m_selection(selection), m_target(target),
          m_property(property) {}

    const Window m_requestor;
    const Atom m_selection, m_target, m_property;
};

class SelectionClearEvent : public Event {
public:
    SelectionClearEvent(Atom selection) : Event(Type::kSelectionClear), m_selection(selection) {}

    const Atom m_selection;
};

} // namespace xcb
} // namespace clipboardxx
