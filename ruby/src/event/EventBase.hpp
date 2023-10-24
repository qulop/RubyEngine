#pragma once

#include <core/Core.hpp>


namespace Ruby
{
    enum class EventType
    {
        NONE_EVENT                  = 0,
        MOUSE_BUTTON_PRESSED_EVENT  = (1 << 1),
        MOUSE_BUTTON_RELEASED_EVENT = (1 << 2),
        MOUSE_MOVED_EVENT           = (1 << 3),
        MOUSE_SCROLLED_EVENT        = (1 << 4),
        KEY_PRESSED_EVENT           = (1 << 5),
        KEY_RELEASED_EVENT          = (1 << 6),
        TOUCHPAD_PRESSED_EVENT      = (1 << 7),
        TOUCHPAD_RELEASED_EVENT     = (1 << 8),
        TOUCHPAD_MOVED_EVENT        = (1 << 9)
    };



    class RUBY_API Event
    {
    public:
        EventType GetType(void) const
        {
            RUBY_ASSERT(m_type != EventType::NONE_EVENT);
            return m_type; 
        }


    protected:
        Event(EventType type) :
            m_type(type) {}

    private:
        EventType m_type = EventType::NONE_EVENT;
    };
}

